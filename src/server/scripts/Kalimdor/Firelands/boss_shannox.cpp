
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "firelands.h"

enum Texts
{
    // Shannox
    SAY_INTRO           = 0,
    SAY_AGGRO           = 1,
    SAY_SLAY            = 2,
    SAY_HURL_SPEAR      = 3,
    SAY_RIPLIMB_KILLED  = 4,
    SAY_RAGEFACE_KILLED = 5,
    SAY_ENRAGE          = 6,
    SAY_DEATH           = 7,

    // Shannox Controller
    SAY_HORN_1          = 0,
    SAY_HORN_2          = 1,
};

enum Spells
{
    // Shannox
    SPELL_THROW_CRYSTAL_TRAP    = 99836,
    SPELL_THROW_IMMOLATION_TRAP = 99839,
    SPELL_ARCING_SLASH          = 99931,
    SPELL_HURL_SPEAR_SUMMON     = 99978,
    SPELL_HURL_SPEAR_DUMMY      = 100031,
    SPELL_HURL_SPEAR_THROW      = 100002,
    SPELL_MAGMA_FLARE           = 100495,
    SPELL_MAGMA_RUPTURE         = 99841,
    SPELL_FRENZIED_DEVOTION     = 100064,
    SPELL_FRENZY                = 100522,

    // Shannox Spear
    SPELL_SPEAR_TARGET          = 99988,
    SPELL_SPEAR_VISUAL          = 100005,
    SPELL_DEATH_GRIP            = 49575,

    // Riplimb
    SPELL_WARY                  = 100167,
    SPELL_LIMB_RIP              = 99832,
    SPELL_FEEDING_FRENZY        = 100655,

    // Rageface
    SPELL_FACE_RAGE             = 99945,

    // Crystal Prison Trap
    SPELL_PRISON_EFFECT         = 99837,

    // Immolation Trap
    SPELL_IMMOLATION_EFFECT     = 99838,
};

enum Events
{
    // Shannox
    EVENT_TALK_INTRO = 1,
    EVENT_THROW_CRYSTAL_TRAP,
    EVENT_THROW_IMMOLATION_TRAP,
    EVENT_ARCING_SLASH,
    EVENT_HURL_SPEAR,
    EVENT_DISARM,
    EVENT_ARM,
    EVENT_ORDER_SPEAR,
    EVENT_REVIVE_RIPLIMB,
    EVENT_REVIVE_RAGEFACE,

    // Riplimb
    EVENT_TAKE_SPEAR,
    EVENT_THROW_SPEAR,
    EVENT_LIMB_RIP,

    // Rageface
    EVENT_FACE_RAGE,
    EVENT_CHANGE_TARGET,

    // Traps
    EVENT_ARM_TRAP,
    EVENT_CHECK_TRAP,

};

enum Actions
{
    ACTION_TRASH_KILLED = 1,
    ACTION_BRING_SPEAR,
    ACTION_SPEAR_THROWN,
    ACTION_RIPLIMB_KILLED,
    ACTION_RAGEFACE_KILLED,
};

enum Phases
{
    PHASE_INTRO     = 1,
    PHASE_COMBAT    = 2,
};

enum Points
{
    POINT_INTRO     = 1,
    POINT_SPEAR,
};

enum Equipment
{
    EQUIP_SPEAR     = 70693,
};

Position const ShannoxSpawnPos = {14.40601f, -64.01636f, 55.22266f, 4.469716f};
Position const RagefaceSpawnPos = {29.51563f, -54.70139f, 54.58546f, 4.469716f};
Position const RiplimpSpawnPos = {29.15799f,-73.91146f, 54.78453f, 4.469716f};
Position const ShannoxMovePos = {-55.36111f, -58.91667f, 57.69878f};

class boss_shannox : public CreatureScript
{
public:
    boss_shannox() : CreatureScript("boss_shannox") { }

    struct boss_shannoxAI : public BossAI
    {
        boss_shannoxAI(Creature* creature) : BossAI(creature, DATA_SHANNOX)
        {
            _riplimbSlain = false;
            _isArmed = true;
            _dogsFrenzied = false;
        }

        Creature* riplimb;  // Define them as public creature to have a full controll everywherre
        Creature* rageface;

        bool _riplimbSlain; // needed later for heroic encounter
        bool _isArmed;
        bool _dogsFrenzied;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.SetPhase(PHASE_INTRO);

            if (riplimb = me->SummonCreature(NPC_RIPLIMB, RiplimpSpawnPos, TEMPSUMMON_MANUAL_DESPAWN))
            {
                riplimb->GetMotionMaster()->MoveFollow(me, 5.0f, 90.0f);
                riplimb->SetReactState(REACT_PASSIVE);
            }
            if (rageface = me->SummonCreature(NPC_RAGEFACE, RagefaceSpawnPos, TEMPSUMMON_MANUAL_DESPAWN))
            {
                rageface->GetMotionMaster()->MoveFollow(me, 5.0f, 270.0f);
                rageface->SetReactState(REACT_PASSIVE);
            }

            if (GameObject* door = me->FindNearestGameObject(GO_BALEROC_DOOR, 200.0f))
                door->SetGoState(GO_STATE_ACTIVE);

            me->GetMotionMaster()->MovePoint(POINT_INTRO, ShannoxMovePos.GetPositionX(), ShannoxMovePos.GetPositionY(), ShannoxMovePos.GetPositionZ(), false);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_HURL_SPEAR_TARGET:
                    me->AddAura(SPELL_SPEAR_TARGET, summon);
                    DoCast(summon, SPELL_HURL_SPEAR_THROW);
                    break;
                case NPC_CRYSTAL_TRAP:
                case NPC_IMMOLATION_TRAP:
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                    break;
                default:
                    break;
            }
        }

        void Reset()
        {
            events.Reset();
            instance->SetBossState(DATA_SHANNOX, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);

            if (Unit* victim = me->getVictim())
            {
                riplimb->Attack(victim, true);
                rageface->Attack(victim, true);
                riplimb->GetMotionMaster()->MoveChase(victim);
                rageface->GetMotionMaster()->MoveChase(victim);
            }

            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, riplimb);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, rageface);
            events.SetPhase(PHASE_COMBAT);
            events.ScheduleEvent(EVENT_THROW_CRYSTAL_TRAP, 9950, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_THROW_IMMOLATION_TRAP, 16500, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_ARCING_SLASH, 6900, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_HURL_SPEAR, 23500, 0, PHASE_COMBAT);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_INTRO:
                    events.ScheduleEvent(EVENT_TALK_INTRO, 100, 0, PHASE_INTRO);
                    break;
                default:
                    break;
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(30) && !_dogsFrenzied)
            {
                _dogsFrenzied = true;
                if (riplimb->isAlive())
                    riplimb->CastSpell(riplimb, SPELL_FRENZIED_DEVOTION);

                if (rageface->isAlive())
                    rageface->CastSpell(rageface, SPELL_FRENZIED_DEVOTION);
            }
        }

        void KilledUnit(Unit* killed) 
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, riplimb);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, rageface);
            Talk(SAY_DEATH);
            _JustDied();
        }

        void EnterEvadeMode()
        {
            if (!riplimb->isAlive())
                riplimb->Respawn();

            if (!rageface->isAlive())
                rageface->Respawn();

            riplimb->GetMotionMaster()->MoveFollow(me, 5.0f, 90.0f);
            riplimb->SetReactState(REACT_PASSIVE);
            rageface->GetMotionMaster()->MoveFollow(me, 5.0f, 270.0f);
            rageface->SetReactState(REACT_PASSIVE);

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, riplimb);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, rageface);
            me->SetCurrentEquipmentId(me->GetEntry());
            _isArmed = true;
            _dogsFrenzied = false;
            _riplimbSlain = false;
            me->RemoveAllAuras();
            Reset();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SPEAR_THROWN:
                    events.ScheduleEvent(EVENT_ARM, 2000, 0, PHASE_COMBAT);
                   break;
                case ACTION_RIPLIMB_KILLED:
                    Talk(SAY_RIPLIMB_KILLED);
                    Talk(SAY_ENRAGE);
                    DoCast(me, SPELL_FRENZY);
                    _riplimbSlain = true;
                    break;
                case ACTION_RAGEFACE_KILLED:
                    Talk(SAY_RAGEFACE_KILLED);
                    Talk(SAY_ENRAGE);
                    DoCast(me, SPELL_FRENZY);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_INTRO:
                        TalkToFar(SAY_INTRO, TEXT_RANGE_MAP);
                        if (GameObject* door = me->FindNearestGameObject(GO_BALEROC_DOOR, 200.0f))
                            door->SetGoState(GO_STATE_READY);
                        break;
                    case EVENT_THROW_CRYSTAL_TRAP:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_THROW_CRYSTAL_TRAP);
                        events.ScheduleEvent(EVENT_THROW_CRYSTAL_TRAP, 26500, 0, PHASE_COMBAT);
                        break;
                    case EVENT_THROW_IMMOLATION_TRAP:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_THROW_IMMOLATION_TRAP);
                        events.ScheduleEvent(EVENT_THROW_IMMOLATION_TRAP, 9700, 0, PHASE_COMBAT);
                        break;
                    case EVENT_ARCING_SLASH:
                        DoCastVictim(SPELL_ARCING_SLASH);
                        events.ScheduleEvent(EVENT_ARCING_SLASH, 12000, 0, PHASE_COMBAT);
                        break;
                    case EVENT_HURL_SPEAR:
                        if (_isArmed)
                        {
                            DoCast(riplimb, SPELL_HURL_SPEAR_SUMMON);
                            if (!_riplimbSlain)
                            {
                                DoCastAOE(SPELL_HURL_SPEAR_DUMMY);
                                Talk(SAY_HURL_SPEAR);
                                events.ScheduleEvent(EVENT_DISARM, 2100, 0, PHASE_COMBAT);
                                events.ScheduleEvent(EVENT_ORDER_SPEAR, 5000, 0, PHASE_COMBAT);
                            }
                            else
                                DoCastVictim(SPELL_MAGMA_RUPTURE);

                            events.ScheduleEvent(EVENT_HURL_SPEAR, 53000, 0, PHASE_COMBAT);
                        }
                        else
                            events.ScheduleEvent(EVENT_HURL_SPEAR, 53000, 0, PHASE_COMBAT);
                        break;
                    case EVENT_DISARM:
                        SetEquipmentSlots(false, 0, 0, 0);
                        _isArmed = false;
                        break;
                    case EVENT_ARM:
                        SetEquipmentSlots(false, EQUIP_SPEAR, 0, 0);
                        _isArmed = true;
                        break;
                    case EVENT_ORDER_SPEAR:
                        if (riplimb->isAlive())
                            riplimb->AI()->DoAction(ACTION_BRING_SPEAR);
                        else
                            events.ScheduleEvent(EVENT_ORDER_SPEAR, 5000, 0, PHASE_COMBAT); // If riplimb is dead we reschedule the event until he can bring it
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new boss_shannoxAI (Creature);
    }
};

class npc_fl_riplimb : public CreatureScript
{
    public:
        npc_fl_riplimb() :  CreatureScript("npc_fl_riplimb") { }

        struct npc_fl_riplimbAI : public ScriptedAI
        {
            npc_fl_riplimbAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_BRING_SPEAR:
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        if (Creature* spear = me->FindNearestCreature(NPC_HURL_SPEAR_TARGET, 100.0f, true))
                            me->GetMotionMaster()->MovePoint(POINT_SPEAR, spear->GetPositionX(), spear->GetPositionY(), spear->GetPositionZ());
                        events.Reset();
                        events.ScheduleEvent(EVENT_TAKE_SPEAR, 1000); // debug to keep him moving
                       break;
                    default:
                        break;
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                DoCast(me, SPELL_FEEDING_FRENZY);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
                ScheduleEvents();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* shannox = me->FindNearestCreature(BOSS_SHANNOX, 200.0f, true))
                    shannox->AI()->DoAction(ACTION_RAGEFACE_KILLED);
            }

            void ScheduleEvents()
            {
                events.ScheduleEvent(EVENT_LIMB_RIP, 9700);
            }

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case POINT_SPEAR:
                        events.ScheduleEvent(EVENT_THROW_SPEAR, 1000);
                        events.CancelEvent(EVENT_TAKE_SPEAR);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TAKE_SPEAR:
                            if (Creature* spear = me->FindNearestCreature(NPC_SHANNOX_SPEAR, 100.0f, true))
                                me->GetMotionMaster()->MovePoint(POINT_SPEAR, spear->GetPositionX(), spear->GetPositionY(), spear->GetPositionZ());
                            events.ScheduleEvent(EVENT_TAKE_SPEAR, 1000);
                            break;
                        case EVENT_THROW_SPEAR:
                            if (Creature* spear = me->FindNearestCreature(NPC_SHANNOX_SPEAR, 5.0f, true))
                            {
                                if (Creature* shannox = me->FindNearestCreature(BOSS_SHANNOX, 100.0f, true))
                                {
                                    spear->CastSpell(shannox, SPELL_DEATH_GRIP);
                                    spear->CastSpell(spear, SPELL_SPEAR_VISUAL);
                                    spear->DespawnOrUnsummon(2000);
                                    shannox->AI()->DoAction(ACTION_SPEAR_THROWN);
                                }
                            }
                            ScheduleEvents();
                            me->SetReactState(REACT_AGGRESSIVE);
                            break;
                        case EVENT_LIMB_RIP:
                            DoCastVictim(SPELL_LIMB_RIP);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_riplimbAI(creature);
        }
};

class npc_fl_rageface : public CreatureScript
{
    public:
        npc_fl_rageface() :  CreatureScript("npc_fl_rageface") { }

        struct npc_fl_ragefaceAI : public ScriptedAI
        {
            npc_fl_ragefaceAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void EnterCombat(Unit* /*who*/)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                DoCast(me, SPELL_FEEDING_FRENZY);
                events.ScheduleEvent(EVENT_FACE_RAGE, 15000);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* shannox = me->FindNearestCreature(BOSS_SHANNOX, 200.0f, true))
                    shannox->AI()->DoAction(ACTION_RAGEFACE_KILLED);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FACE_RAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_FACE_RAGE);
                            events.ScheduleEvent(EVENT_FACE_RAGE, 40000);
                            break;
                        case EVENT_CHANGE_TARGET:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                me->Attack(target, true);
                            events.ScheduleEvent(EVENT_CHANGE_TARGET, 10000);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_ragefaceAI(creature);
        }
};

class npc_fl_shannox_controller : public CreatureScript
{
    public:
        npc_fl_shannox_controller() :  CreatureScript("npc_fl_shannox_controller") { }

        struct npc_fl_shannox_controllerAI : public ScriptedAI
        {
            npc_fl_shannox_controllerAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
                _shannoxSummoned = false;
                _trashKilled = 0;
                me->setActive(true);
            }

            InstanceScript* instance;
            bool _shannoxSummoned;
            uint8 _trashKilled;

            void Reset()
            {
                me->setActive(true);
            }

            void UpdateAI(uint32 diff)
            {
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_TRASH_KILLED:
                        _trashKilled++;
                        if (_trashKilled == 5)
                            TalkToFar(SAY_HORN_1, TEXT_RANGE_MAP);
                        else if (_trashKilled == 10)
                            TalkToFar(SAY_HORN_2, TEXT_RANGE_MAP);
                        else if (_trashKilled == 15 && !_shannoxSummoned)
                            if (Creature* shannox = me->SummonCreature(BOSS_SHANNOX, ShannoxSpawnPos, TEMPSUMMON_MANUAL_DESPAWN))
                                _shannoxSummoned = true;
                        break;
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_shannox_controllerAI(creature);
        }
};

class npc_fl_immolation_trap : public CreatureScript
{
    public:
        npc_fl_immolation_trap() :  CreatureScript("npc_fl_immolation_trap") { }

        struct npc_fl_immolation_trapAI : public ScriptedAI
        {
            npc_fl_immolation_trapAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                events.ScheduleEvent(EVENT_ARM_TRAP, 2000); // WoW Head: arms after 2 seconds
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ARM_TRAP:
                            events.ScheduleEvent(EVENT_CHECK_TRAP, 1000); // Check every seconds if a unit is inside the trap
                            break;
                        case EVENT_CHECK_TRAP:
                            if (Unit* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 0.5f, true))
                            {
                                if (!riplimb->HasAura(SPELL_WARY))
                                {
                                    DoCast(riplimb, SPELL_IMMOLATION_EFFECT);
                                    me->DespawnOrUnsummon(1000);
                                    me->Kill(me);
                                }
                            }
                            else if (Unit* rageface = me->FindNearestCreature(NPC_RAGEFACE, 0.5f, true))
                            {
                                if (!rageface->HasAura(SPELL_WARY))
                                {
                                    DoCast(rageface, SPELL_IMMOLATION_EFFECT);
                                    me->DespawnOrUnsummon(1000);
                                    me->Kill(me);
                                }
                            }
                            else if (Unit* player = me->FindNearestPlayer(0.5f, true))
                            {
                                me->setFaction(16);
                                DoCast(player, SPELL_IMMOLATION_EFFECT);
                                me->DespawnOrUnsummon(1000);
                                me->Kill(me);
                            }
                            events.ScheduleEvent(EVENT_CHECK_TRAP, 1000);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_immolation_trapAI(creature);
        }
};

class npc_fl_crystal_trap : public CreatureScript
{
    public:
        npc_fl_crystal_trap() :  CreatureScript("npc_fl_crystal_trap") { }

        struct npc_fl_crystal_trapAI : public ScriptedAI
        {
            npc_fl_crystal_trapAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                events.ScheduleEvent(EVENT_ARM_TRAP, 2000); // WoW Head: arms after 2 seconds
            }

            void JustSummoned(Creature* summon)
            {
                switch (summon->GetEntry())
                {
                    case NPC_CRYSTAL_PRISON:
                        summon->SetReactState(REACT_PASSIVE);
                        summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ARM_TRAP:
                            events.ScheduleEvent(EVENT_CHECK_TRAP, 1000); // Check every seconds if a unit is inside the trap
                            break;
                        case EVENT_CHECK_TRAP:
                            if (Unit* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 0.5f, true))
                            {
                                if (!riplimb->HasAura(SPELL_WARY))
                                {
                                    Unit* creature = me->SummonCreature(NPC_CRYSTAL_PRISON, riplimb->GetPositionX(), riplimb->GetPositionY(), riplimb->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                                    DoCast(riplimb, SPELL_PRISON_EFFECT);
                                    me->DespawnOrUnsummon(1000);
                                    me->Kill(me);
                                }
                            }
                            else if (Unit* rageface = me->FindNearestCreature(NPC_RAGEFACE, 0.5f, true))
                            {
                                if (!rageface->HasAura(SPELL_WARY))
                                {
                                    Unit* creature = me->SummonCreature(NPC_CRYSTAL_PRISON, rageface->GetPositionX(), rageface->GetPositionY(), rageface->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                                    DoCast(rageface, SPELL_PRISON_EFFECT);
                                    me->DespawnOrUnsummon(1000);
                                    me->Kill(me);
                                }
                            }
                            else if (Unit* player = me->FindNearestPlayer(0.5f, true))
                            {
                                Unit* creature = me->SummonCreature(NPC_CRYSTAL_PRISON, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                                me->setFaction(16);
                                DoCast(player, SPELL_PRISON_EFFECT);
                                me->DespawnOrUnsummon(1000);
                                me->Kill(me);
                            }
                            events.ScheduleEvent(EVENT_CHECK_TRAP, 1000);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_crystal_trapAI(creature);
        }
};

class npc_fl_crystal_prison : public CreatureScript
{
    public:
        npc_fl_crystal_prison() :  CreatureScript("npc_fl_crystal_prison") { }

        struct npc_fl_crystal_prisonAI : public ScriptedAI
        {
            npc_fl_crystal_prisonAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Unit* riplimb = me->FindNearestCreature(NPC_RIPLIMB, 1.0f, true))
                    if (riplimb->HasAura(SPELL_PRISON_EFFECT))
                        riplimb->RemoveAurasDueToSpell(SPELL_PRISON_EFFECT);

                if (Unit* rageface = me->FindNearestCreature(NPC_RAGEFACE, 1.0f, true))
                    if (rageface->HasAura(SPELL_PRISON_EFFECT))
                        rageface->RemoveAurasDueToSpell(SPELL_PRISON_EFFECT);

                if (Unit* player = me->FindNearestPlayer(1.0f, true))
                    if (player->HasAura(SPELL_PRISON_EFFECT))
                        player->RemoveAurasDueToSpell(SPELL_PRISON_EFFECT);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_crystal_prisonAI(creature);
        }
};

class spell_fl_hurl_spear : public SpellScriptLoader
{
public:
    spell_fl_hurl_spear() : SpellScriptLoader("spell_fl_hurl_spear") { }

    class spell_fl_hurl_spear_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_hurl_spear_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                target->setFaction(16);
                target->CastSpell(target, SPELL_MAGMA_FLARE);
                Creature* spear = target->SummonCreature(NPC_SHANNOX_SPEAR, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), GetCaster()->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                target->CastSpell(target, SPELL_SPEAR_VISUAL);
                target->RemoveAurasDueToSpell(SPELL_SPEAR_TARGET);

                for (float r = 0; r <= 30; r = r + 10)
                {
                    for (float x = 0; x <= r * 2; x = x + 2)
                    {
                        target->CastSpell(target->GetPositionX() + cos(x) * r, target->GetPositionY() + sin(x) * r, target->GetPositionZ(), SPELL_MAGMA_RUPTURE, true);
                        target->CastSpell(target->GetPositionX() - cos(x) * r, target->GetPositionY() - sin(x) * r, target->GetPositionZ(), SPELL_MAGMA_RUPTURE, true);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_hurl_spear_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_hurl_spear_SpellScript();
    }
};

void AddSC_boss_shannox()
{
    new npc_fl_shannox_controller();
    new boss_shannox();
    new npc_fl_riplimb();
    new npc_fl_rageface();
    new npc_fl_immolation_trap();
    new npc_fl_crystal_trap();
    new npc_fl_crystal_prison();
    new spell_fl_hurl_spear();
}