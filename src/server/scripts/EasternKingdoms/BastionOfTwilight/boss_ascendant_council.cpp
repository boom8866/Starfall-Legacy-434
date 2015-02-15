
#include "bastion_of_twilight.h"

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_SLAY                = 1,
    SAY_ABILITY             = 2,
    SAY_ANNOUNCE_ABILITY    = 3,
    SAY_FUSE_INTRO          = 4,
    SAY_FUSE                = 5,
    SAY_DEATH               = 6,
};

enum ControllerTexts
{
    ANNOUNCE_QUAKE          = 0,
    ANNOUNCE_THUNDERSHOCK   = 1,
};

enum Spells
{
    // General Spells
    SPELL_CLEAR_ALL_DEBUFFS             = 34098,

    // Feludius
    SPELL_TELEPORT_RB                   = 81799,
    SPELL_TELEPORT_WATER                = 82332,
    SPELL_FROST_EXPLSION                = 94739,
    SPELL_WATER_BOMB                    = 82699,
    SPELL_WATER_BOMB_TRIGGERED          = 82700,
    SPELL_WATERLOGGED                   = 82762,
    SPELL_HYDRO_LANCE                   = 82752,
    SPELL_GLACIATE                      = 82746,
    SPELL_FROZEN                        = 82772,
    SPELL_HEART_OF_ICE                  = 82665,
    SPELL_FROST_IMBUED                  = 82666,

    // Ignacious
    SPELL_TELEPORT_LB                   = 81800,
    SPELL_TELEPORT_FIRE                 = 82331,
    SPELL_FIRE_EXPLOSION                = 94738,
    SPELL_AEGIS_OF_FLAME                = 82631,
    SPELL_RISING_FLAMES                 = 82636,
    SPELL_INFERNO_LEAP                  = 82856,
    SPELL_INFERNO_LEAP_TRIGGERED        = 82857,
    SPELL_INFERNO_RUSH_CHARGE           = 82859,
    SPELL_BURNING_BLOOD                 = 82660,
    SPELL_FLAME_IMBUED                  = 82663,
    SPELL_FLAME_TORRENT                 = 82777,

    // Arion
    SPELL_TELEPORT_LF                   = 81796,
    SPELL_TELEPORT_AIR                  = 82330,
    SPELL_CALL_WINDS                    = 83491,
    
    // Terrastra
    SPELL_TELEPORT_RF                   = 81798,
    SPELL_TELEPORT_EARTH                = 82329,
    SPELL_ELEMENTAL_STASIS              = 82285,
    SPELL_ERUPTION                      = 83675,
    SPELL_SUMMON_ERUPTION               = 83661, // casted 5 times
    SPELL_ERUPTION_DAMAGE               = 83692,

    // Elementium Monstrosity
    SPELL_TWILIGHT_EXPLOSION            = 95789,
    SPELL_CRYOGENIC_AURA                = 84918,
    SPELL_LIQUID_ICE_GROWTH             = 84917,
    SPELL_ELECTRIC_INSTABILITY          = 84526,
    SPELL_ELECTRIC_INSTABILITY_DAMAGE   = 84529,
    SPELL_ELECTRIC_INSTABILITY_DUMMY    = 84527,
    SPELL_GRAVITY_CRUSH                 = 84948,
    SPELL_GRAVITY_CRUSH_VEHICLE         = 84952,

    SPELL_LAVA_SEED                     = 84913,

    // Inferno Rush
    SPELL_INFERNO_RUSH_AURA             = 88579,

    // Liquid Ice
    SPELL_LIQUID_ICE                    = 84914,
    SPELL_LIQUID_ICE_DUMMY              = 84915,

    // Eruption Target
    SPELL_ERUPTION_VISUAL               = 83662,

    // Ascendant Council Plume Stalker
    SPELL_LAVA_SEED_DUMMY               = 84911,
    SPELL_LAVA_PLUME                    = 84912,
};

enum Events
{
    // Feludius
    EVENT_WATER_BOMB = 1,
    EVENT_GLACIATE,
    EVENT_HYDRO_LANCE,
    EVENT_HEART_OF_ICE,

    // Ignacious
    EVENT_TALK_INTRO,
    EVENT_AEGIS_OF_FLAME,
    EVENT_RISING_FLAMES,
    EVENT_INFERNO_LEAP,
    EVENT_INFERNO_RUSH,
    EVENT_SUMMON_INFERNO_RUSH,
    EVENT_ACTIVATE_FLAMES,
    EVENT_BURNING_BLOOD,
    EVENT_FLAME_TORRENT,

    // Arion
    EVENT_CALL_WINDS,

    // Terrastra
    EVENT_ERUPTION,
    EVENT_ERUPTION_DAMAGE,

    // Elementium Monstrosity
    EVENT_GRAVITY_CRUSH,
    EVENT_LAVA_SEED,
    EVENT_INCREASE_INSTABILITY_COUNTER,

    // Controller
    EVENT_SUMMON_MONSTROSITY,

    // Misc Events
    EVENT_APPLY_IMMUNITY,
    EVENT_ATTACK,
    EVENT_FACE_CONTROLLER,
    EVENT_MOVE_FUSE,

    // Plume Stalker
    EVENT_LAVA_PLUME,
};

enum Actions
{
    ACTION_INTRO_1 = 1,
    ACTION_INTRO_2,
    ACTION_INTRO_3,
    ACTION_TELEPORT,
    ACTION_TURN_IN,
    ACTION_SWITCH_PHASE_1,
    ACTION_SWITCH_PHASE_2,
    ACTION_PREPARE_FUSE,
    ACTION_ENCOUNTER_START,
    ACTION_RESET_COUNCIL,
    ACTION_ENCOUNTER_DONE,
};

Position const ElementiumMonstrosityPos = { -1009.01f, -582.467f, 831.9843f, 6.265732f };

class LiquidIceRangeCheck
{
public:
    LiquidIceRangeCheck(Unit* caster) : caster(caster) { }

    bool operator()(WorldObject* object)
    {
        return (object->GetExactDist2d(caster->GetPositionX(), caster->GetPositionY()) > (5.0f * caster->GetObjectSize()));
    }
private:
    Unit* caster;
};

class ElementiumMonstrosityCheck
{
public:
    ElementiumMonstrosityCheck() { }

    bool operator()(WorldObject* object)
    {
        return (object->GetEntry() != BOSS_ELEMENTIUM_MONSTROSITY);
    }
};

class at_ascendant_council_1 : public AreaTriggerScript
{
public:
    at_ascendant_council_1() : AreaTriggerScript("at_ascendant_council_1") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_1);
        return true;
    }
};

class at_ascendant_council_2 : public AreaTriggerScript
{
public:
    at_ascendant_council_2() : AreaTriggerScript("at_ascendant_council_2") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_2);
        return true;
    }
};

class at_ascendant_council_3 : public AreaTriggerScript
{
public:
    at_ascendant_council_3() : AreaTriggerScript("at_ascendant_council_3") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_3);
        return true;
    }
};

class RandomDistancePlayerCheck
{
public:
    RandomDistancePlayerCheck(Unit* caster) : caster(caster) { }

    bool operator()(WorldObject* object)
    {
        return (object->GetDistance2d(caster) <= 20.0f);
    }
private:
    Unit* caster;
};

class boss_feludius : public CreatureScript
{
public:
    boss_feludius() : CreatureScript("boss_feludius") { }

    struct boss_feludiusAI : public BossAI
    {
        boss_feludiusAI(Creature* creature) : BossAI(creature, DATA_FELUDIUS)
        {
            _switched = false;
        }

        bool _switched;

        void Reset()
        {
            _Reset();
            _switched = false;
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                ignacious->AI()->AttackStart(who);

            if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                controller->AI()->DoAction(ACTION_ENCOUNTER_START);

            events.ScheduleEvent(EVENT_WATER_BOMB, 15000);
            events.ScheduleEvent(EVENT_GLACIATE, 30000);
            events.ScheduleEvent(EVENT_HYDRO_LANCE, urand(6000, 10000));
            events.ScheduleEvent(EVENT_HEART_OF_ICE, 18000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                controller->AI()->DoAction(ACTION_RESET_COUNCIL);

            events.Reset();
            _switched = false;
            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->HasAura(SPELL_FLAME_IMBUED))
                damage = damage + (damage * 0.5f);

            if (me->HealthBelowPct(25) && !_switched)
            {
                if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                    controller->AI()->DoAction(ACTION_SWITCH_PHASE_1);

                _switched = true;
            }
        }

        void MakeInterruptable(bool apply)
        {
            if (apply)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
            }
            else
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TELEPORT:
                    _switched = true;
                    me->RemoveAllAuras();
                    me->CastStop();
                    events.Reset();
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    DoCast(SPELL_TELEPORT_RB);
                    break;
                case ACTION_PREPARE_FUSE:
                    DoCast(me, SPELL_FROST_EXPLSION);
                    DoCast(me, SPELL_TELEPORT_WATER);
                    events.ScheduleEvent(EVENT_FACE_CONTROLLER, 200);
                    events.ScheduleEvent(EVENT_MOVE_FUSE, 6000);
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
                    case EVENT_WATER_BOMB:
                        for (uint8 i = 0; i < 16; i++)
                        {
                            float distance = frand(2.0f, 50.0f);
                            float ori = frand(0.0f, M_PI * 2);
                            float x = me->GetPositionX() + cos(ori) * distance;
                            float y = me->GetPositionY() + sin(ori) * distance;
                            float z = me->GetPositionZ();
                            me->SummonCreature(NPC_WATER_BOMB, x, y, z, ori, TEMPSUMMON_TIMED_DESPAWN, 15000);
                        }
                        DoCast(me, SPELL_WATER_BOMB);
                        events.ScheduleEvent(EVENT_WATER_BOMB, urand(33000, 35000));
                        break;
                    case EVENT_GLACIATE:
                        Talk(SAY_ANNOUNCE_ABILITY);
                        Talk(SAY_ABILITY);
                        DoCast(me, SPELL_GLACIATE);
                        events.ScheduleEvent(EVENT_GLACIATE, urand(33000, 35000));
                        break;
                    case EVENT_HYDRO_LANCE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            MakeInterruptable(true);
                            DoCast(target, SPELL_HYDRO_LANCE);
                        }
                        events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 1500);
                        events.ScheduleEvent(EVENT_HYDRO_LANCE, 12000);
                        break;
                    case EVENT_APPLY_IMMUNITY:
                        MakeInterruptable(false);
                        break;
                    case EVENT_HEART_OF_ICE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_HEART_OF_ICE);
                        events.ScheduleEvent(EVENT_HEART_OF_ICE, 22000);
                        break;
                    case EVENT_MOVE_FUSE:
                        Talk(SAY_FUSE_INTRO);
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->GetMotionMaster()->MovePoint(0, controller->GetPositionX(), controller->GetPositionY(), controller->GetPositionZ());
                        break;
                    case EVENT_FACE_CONTROLLER:
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->SetFacingToObject(controller);
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
        return new boss_feludiusAI(creature);
    }
};

class boss_ignacious : public CreatureScript
{
public:
    boss_ignacious() : CreatureScript("boss_ignacious") { }

    struct boss_ignaciousAI : public BossAI
    {
        boss_ignaciousAI(Creature* creature) : BossAI(creature, DATA_IGNACIOUS)
        {
            leapTarget = NULL;
            _infernoCounter = 0;
            _switched = false;
        }

        Unit* leapTarget;
        uint8 _infernoCounter;
        Position ignaciousPos;
        Position rushPos;
        bool _switched;

        void Reset()
        {
            _Reset();
            MakeInterruptable(true);
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TALK_INTRO, 4000);
            events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, 31000);
            events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);
            events.ScheduleEvent(EVENT_BURNING_BLOOD, 28000);
            events.ScheduleEvent(EVENT_FLAME_TORRENT, urand(6000, 10000));

            if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                feludius->AI()->AttackStart(who);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
            leapTarget = NULL;
            _infernoCounter = 0;
            _switched = false;
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->HasAura(SPELL_FROST_IMBUED))
                damage = damage + (damage * 0.5f);

            if (me->HealthBelowPct(25) && !_switched)
            {
                if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                    controller->AI()->DoAction(ACTION_SWITCH_PHASE_1);
                _switched = true;
            }
        }

        void MakeInterruptable(bool apply)
        {
            if (apply)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
            }
            else
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TELEPORT:
                    _switched = true;
                    me->RemoveAllAuras();
                    me->CastStop();
                    events.Reset();
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    DoCast(SPELL_TELEPORT_LB);
                    break;
                case ACTION_PREPARE_FUSE:
                    DoCast(me, SPELL_FIRE_EXPLOSION);
                    DoCast(me, SPELL_TELEPORT_FIRE);
                    events.ScheduleEvent(EVENT_FACE_CONTROLLER, 200);
                    events.ScheduleEvent(EVENT_MOVE_FUSE, 10000);
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
                    case EVENT_TALK_INTRO:
                        Talk(SAY_AGGRO);
                        break;
                    case EVENT_AEGIS_OF_FLAME:
                        DoCast(me, SPELL_AEGIS_OF_FLAME);
                        events.ScheduleEvent(EVENT_RISING_FLAMES, 2000);
                        break;
                    case EVENT_RISING_FLAMES:
                        Talk(SAY_ANNOUNCE_ABILITY);
                        Talk(SAY_ABILITY);
                        DoCast(me, SPELL_RISING_FLAMES);
                        break;
                    case EVENT_INFERNO_LEAP:
                    {
                        std::list<Player*> targets = me->GetNearestPlayersList(200.0f, true);
                        if (!targets.empty())
                        {
                            leapTarget = me->getVictim();
                            me->AttackStop();
                            me->SetReactState(REACT_PASSIVE);
                            targets.remove_if(RandomDistancePlayerCheck(me));
                            if (targets.empty())
                                break;

                            if (Unit* target = Trinity::Containers::SelectRandomContainerElement(targets))
                            {
                                DoCast(target, SPELL_INFERNO_LEAP);
                                events.ScheduleEvent(EVENT_INFERNO_RUSH, 3000);
                            }
                        }
                        break;
                    }
                    case EVENT_INFERNO_RUSH:
                        if (leapTarget)
                        {
                            _infernoCounter;
                            DoCast(leapTarget, SPELL_INFERNO_RUSH_CHARGE);
                        }
                        events.ScheduleEvent(EVENT_SUMMON_INFERNO_RUSH, 1);
                        break;
                    case EVENT_SUMMON_INFERNO_RUSH:
                        if (me->GetDistance2d(rushPos.GetPositionX(), rushPos.GetPositionY()) > me->GetFloatValue(UNIT_FIELD_COMBATREACH))
                        {
                            if (_infernoCounter == 0)
                            {
                                ignaciousPos.Relocate(me);
                                rushPos.Relocate(leapTarget);
                            }

                            _infernoCounter++;

                            float ori = me->GetAngle(&rushPos);
                            float dist = _infernoCounter * 6.0f;

                            float x = ignaciousPos.GetPositionX() + cos(ori) * dist;
                            float y = ignaciousPos.GetPositionY() + sin(ori) * dist;
                            float z = ignaciousPos.GetPositionZ();

                            me->SummonCreature(NPC_INFERNO_RUSH, x, y, z, ori, TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_SUMMON_INFERNO_RUSH, 250);
                        }
                        else
                        {
                            leapTarget = NULL;
                            me->SetReactState(REACT_AGGRESSIVE);
                            events.ScheduleEvent(EVENT_ACTIVATE_FLAMES, 1000);
                        }
                        break;
                    case EVENT_ACTIVATE_FLAMES:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_INFERNO_RUSH, 500.0f);
                        if (units.empty())
                            break;

                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->AI()->DoCast(SPELL_INFERNO_RUSH_AURA);
                            (*itr)->DespawnOrUnsummon(31000);
                        }
                        break;
                    }
                    case EVENT_BURNING_BLOOD:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_BURNING_BLOOD);
                        events.ScheduleEvent(EVENT_BURNING_BLOOD, 22000);
                        break;
                    case EVENT_FLAME_TORRENT:
                        DoCast(me, SPELL_FLAME_TORRENT);
                        events.ScheduleEvent(EVENT_FLAME_TORRENT, 12000);
                        break;
                    case EVENT_MOVE_FUSE:
                        Talk(SAY_FUSE_INTRO);
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->GetMotionMaster()->MovePoint(0, controller->GetPositionX(), controller->GetPositionY(), controller->GetPositionZ());
                        break;
                    case EVENT_FACE_CONTROLLER:
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->SetFacingToObject(controller);
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
        return new boss_ignaciousAI(creature);
    }
};

class boss_terrastra : public CreatureScript
{
public:
    boss_terrastra() : CreatureScript("boss_terrastra") { }

    struct boss_terrastraAI : public BossAI
    {
        boss_terrastraAI(Creature* creature) : BossAI(creature, DATA_TERRASTRA)
        {
            _switched = false;
            _eruptionCounter = 0;
        }

        bool _switched;
        uint8 _eruptionCounter;

        void Reset()
        {
            _Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_TALK_INTRO, 4000);
            events.ScheduleEvent(EVENT_ERUPTION, 7000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            _switched = false;
            _eruptionCounter = 0;
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_PASSIVE);
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_ERUPTION_TARGET:
                    _eruptionCounter++;
                    if (_eruptionCounter == 5)
                        events.ScheduleEvent(EVENT_ERUPTION_DAMAGE, 3000);
                    summon->DespawnOrUnsummon(5000);
                    break;
                default:
                    break;
            }
            summons.Summon(summon);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(25) && !_switched)
            {
                if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                    controller->AI()->DoAction(ACTION_SWITCH_PHASE_2);
                _switched = true;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TURN_IN:
                    me->SetInCombatWithZone();
                    DoCast(me, SPELL_TELEPORT_RF);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                    events.ScheduleEvent(EVENT_ATTACK, 500);
                    break;
                case ACTION_PREPARE_FUSE:
                    _switched = true;
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->CastStop();
                    DoCast(me, SPELL_ELEMENTAL_STASIS);
                    DoCast(me, SPELL_TELEPORT_EARTH);
                    events.Reset();
                    summons.DespawnAll();
                    events.ScheduleEvent(EVENT_FACE_CONTROLLER, 200);
                    events.ScheduleEvent(EVENT_MOVE_FUSE, 3000);
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
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Player* player = me->FindNearestPlayer(200.0f, true))
                            me->AI()->AttackStart(player);
                        break;
                    case EVENT_TALK_INTRO:
                        Talk(SAY_AGGRO);
                        break;
                    case EVENT_MOVE_FUSE:
                        Talk(SAY_FUSE_INTRO);
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->GetMotionMaster()->MovePoint(0, controller->GetPositionX(), controller->GetPositionY(), controller->GetPositionZ());
                        break;
                    case EVENT_FACE_CONTROLLER:
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->SetFacingToObject(controller);
                        break;
                    case EVENT_ERUPTION:
                        _eruptionCounter = 0;
                        DoCast(me, SPELL_ERUPTION);
                        break;
                    case EVENT_ERUPTION_DAMAGE:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_ERUPTION_TARGET, 10.0f);
                        if (units.empty())
                            break;

                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                            DoCast((*itr), SPELL_ERUPTION_DAMAGE, true);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_terrastraAI(creature);
    }
};

class boss_arion : public CreatureScript
{
public:
    boss_arion() : CreatureScript("boss_arion") { }

    struct boss_arionAI : public BossAI
    {
        boss_arionAI(Creature* creature) : BossAI(creature, DATA_ARION)
        {
            _switched = false;
        }

        bool _switched;

        void Reset()
        {
            _Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            events.ScheduleEvent(EVENT_CALL_WINDS, 7000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            _switched = false;
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_PASSIVE);
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_VIOLENT_CYCLONE:
                    summon->GetMotionMaster()->MoveRandom(20.0f);
                    break;
                default:
                    break;
            }
            summons.Summon(summon);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(25) && !_switched)
            {
                if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                    controller->AI()->DoAction(ACTION_SWITCH_PHASE_2);
                _switched = true;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TURN_IN:
                    me->SetInCombatWithZone();
                    DoCast(me, SPELL_TELEPORT_LF);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                    events.ScheduleEvent(EVENT_ATTACK, 500);
                    break;
                case ACTION_PREPARE_FUSE:
                    _switched = true;
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->CastStop();
                    summons.DespawnAll();
                    events.Reset();
                    DoCast(me, SPELL_TELEPORT_AIR);
                    events.ScheduleEvent(EVENT_MOVE_FUSE, 100);
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
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Player* player = me->FindNearestPlayer(200.0f, true))
                            me->AI()->AttackStart(player);
                        break;
                    case EVENT_CALL_WINDS:
                        Talk(SAY_ABILITY);
                        DoCast(me, SPELL_CALL_WINDS);
                        break;
                    case EVENT_MOVE_FUSE:
                        Talk(SAY_FUSE_INTRO);
                        if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                            me->GetMotionMaster()->MovePoint(0, controller->GetPositionX(), controller->GetPositionY(), controller->GetPositionZ());
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_arionAI(creature);
    }
};

class boss_elementium_monstrosity : public CreatureScript
{
public:
    boss_elementium_monstrosity() : CreatureScript("boss_elementium_monstrosity") { }

    struct boss_elementium_monstrosityAI : public BossAI
    {
        boss_elementium_monstrosityAI(Creature* creature) : BossAI(creature, DATA_ELEMENTIUM_MONSTROSITY)
        {
            _instabilityCharges = 1;
        }

        uint8 _instabilityCharges;

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->SetInCombatWithZone();
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            events.ScheduleEvent(EVENT_ATTACK, 3000);
            events.ScheduleEvent(EVENT_GRAVITY_CRUSH, 7000);
            DoCast(me, SPELL_TWILIGHT_EXPLOSION);
            DoCast(me, SPELL_CRYOGENIC_AURA);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetData(DATA_ELECTRICAL_INSTABILITY_CHARGES, 1);

            if (Creature* controller = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASCENDANT_COUNCIL_CONTROLLER)))
                controller->AI()->DoAction(ACTION_RESET_COUNCIL);

            events.Reset();
            summons.DespawnAll();
            me->DespawnOrUnsummon(100);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            Talk(SAY_DEATH);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_GRAVITY_CRUSH:
                    summon->GetMotionMaster()->MovePoint(0, summon->GetPositionX(), summon->GetPositionY(), 862.9045f, false);
                    break;
                default:
                    break;
            }
            summons.Summon(summon);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case 0:
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
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoCast(me, SPELL_ELECTRIC_INSTABILITY);
                        if (Player* player = me->FindNearestPlayer(200.0f, true))
                            me->AI()->AttackStart(player);
                        events.ScheduleEvent(EVENT_INCREASE_INSTABILITY_COUNTER, 10000);
                        break;
                    case EVENT_GRAVITY_CRUSH:
                        Talk(SAY_ABILITY);
                        DoCast(me, SPELL_GRAVITY_CRUSH);
                        break;
                    case EVENT_INCREASE_INSTABILITY_COUNTER:
                        _instabilityCharges++;
                        if (_instabilityCharges > 10)
                            _instabilityCharges = 10;
                        instance->SetData(DATA_ELECTRICAL_INSTABILITY_CHARGES, _instabilityCharges);
                        events.ScheduleEvent(EVENT_INCREASE_INSTABILITY_COUNTER, 10000);
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
        return new boss_elementium_monstrosityAI(creature);
    }
};

class npc_ascendant_council_controller : public CreatureScript
{
public:
    npc_ascendant_council_controller() : CreatureScript("npc_ascendant_council_controller") { }

    struct npc_ascendant_council_controllerAI : public ScriptedAI
    {
        npc_ascendant_council_controllerAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
            _intro1Done = false;
            _intro2Done = false;
            _intro3Done = false;
            health = 0;
        }

        InstanceScript* instance;
        SummonList summons;
        EventMap events;
        uint64 health;
        bool _intro1Done;
        bool _intro2Done;
        bool _intro3Done;

        void Reset()
        {
            health = 0;
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INTRO_1:
                    if (!_intro1Done)
                    {
                        if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                            chogall->AI()->TalkToMap(4);
                        _intro1Done = true;
                    }
                    break;
                case ACTION_INTRO_2:
                    if (!_intro2Done)
                    {
                        if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                            chogall->AI()->TalkToMap(5);
                        _intro2Done = true;
                    }
                    break;
                case ACTION_INTRO_3:
                    if (!_intro3Done)
                    {
                        if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                            chogall->AI()->TalkToMap(6);
                        _intro3Done = true;
                    }
                    break;
                case ACTION_SWITCH_PHASE_1:
                    health = 0;
                    if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                    {
                        health += feludius->GetHealth();
                        feludius->AI()->DoAction(ACTION_TELEPORT);
                    }

                    if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                    {
                        health += ignacious->GetHealth();
                        ignacious->AI()->DoAction(ACTION_TELEPORT);
                    }

                    if (Creature* arion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ARION)))
                        arion->AI()->DoAction(ACTION_TURN_IN);

                    if (Creature* terrastra = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_TERRASTRA)))
                        terrastra->AI()->DoAction(ACTION_TURN_IN);
                    break;
                case ACTION_SWITCH_PHASE_2:
                    events.ScheduleEvent(EVENT_SUMMON_MONSTROSITY, 15000);
                    if (Creature* arion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ARION)))
                    {
                        health += arion->GetHealth();
                        arion->AI()->DoAction(ACTION_PREPARE_FUSE);
                    }

                    if (Creature* terrastra = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_TERRASTRA)))
                    {
                        health += terrastra->GetHealth();
                        terrastra->AI()->DoAction(ACTION_PREPARE_FUSE);
                    }

                    if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                        feludius->AI()->DoAction(ACTION_PREPARE_FUSE);

                    if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                        ignacious->AI()->DoAction(ACTION_PREPARE_FUSE);
                    break;
                case ACTION_ENCOUNTER_START:
                    instance->SetBossState(DATA_ASCENDANT_COUNCIL, IN_PROGRESS);
                    break;
                case ACTION_RESET_COUNCIL:
                    health = 0;
                    instance->SetBossState(DATA_ASCENDANT_COUNCIL, NOT_STARTED);
                    instance->SetBossState(DATA_FELUDIUS, FAIL);
                    instance->SetBossState(DATA_IGNACIOUS, FAIL);
                    instance->SetBossState(DATA_ARION, FAIL);
                    instance->SetBossState(DATA_TERRASTRA, FAIL);
                    instance->SetBossState(DATA_ELEMENTIUM_MONSTROSITY, FAIL);
                    if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                    {
                        feludius->Respawn();
                        feludius->AI()->EnterEvadeMode();
                    }
                    if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                    {
                        ignacious->Respawn();
                        ignacious->AI()->EnterEvadeMode();
                    }
                    if (Creature* arion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ARION)))
                    {
                        arion->Respawn();
                        arion->AI()->EnterEvadeMode();
                    }
                    if (Creature* terrastra = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_TERRASTRA)))
                    {
                        terrastra->Respawn();
                        terrastra->AI()->EnterEvadeMode();
                    }
                    break;
                case ACTION_ENCOUNTER_DONE:
                    instance->SetBossState(DATA_ASCENDANT_COUNCIL, DONE);
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
                    case EVENT_SUMMON_MONSTROSITY:
                        if (Creature* monstrosity = me->SummonCreature(BOSS_ELEMENTIUM_MONSTROSITY, ElementiumMonstrosityPos, TEMPSUMMON_MANUAL_DESPAWN))
                            monstrosity->SetHealth(health);
                        if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                        {
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, ignacious);
                            ignacious->DespawnOrUnsummon(100);
                        }

                        if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                        {
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, feludius);
                            feludius->DespawnOrUnsummon(100);
                        }

                        if (Creature* arion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ARION)))
                        {
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, arion);
                            arion->DespawnOrUnsummon(100);
                        }

                        if (Creature* terrastra = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_TERRASTRA)))
                        {
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, terrastra);
                            terrastra->DespawnOrUnsummon(100);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ascendant_council_controllerAI(creature);
    }
};

class npc_ac_plume_stalker : public CreatureScript
{
public:
    npc_ac_plume_stalker() : CreatureScript("npc_ac_plume_stalker") { }

    struct npc_ac_plume_stalkerAI : public ScriptedAI
    {
        npc_ac_plume_stalkerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void SpellHit(Unit* /*target*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_LAVA_SEED)
            {
                DoCast(me, SPELL_LAVA_SEED_DUMMY);
                events.ScheduleEvent(EVENT_LAVA_PLUME, 2000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LAVA_PLUME:
                        DoCast(me, SPELL_LAVA_PLUME);
                        me->RemoveAurasDueToSpell(SPELL_LAVA_SEED_DUMMY);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ac_plume_stalkerAI(creature);
    }
};

class spell_ac_water_bomb : public SpellScriptLoader
{
public:
    spell_ac_water_bomb() : SpellScriptLoader("spell_ac_water_bomb") { }

    class spell_ac_water_bomb_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_water_bomb_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_WATER_BOMB_TRIGGERED, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_water_bomb_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_water_bomb_SpellScript();
    }
};

class spell_ac_glaciate : public SpellScriptLoader
{
public:
    spell_ac_glaciate() : SpellScriptLoader("spell_ac_glaciate") { }

    class spell_ac_glaciate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_glaciate_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                {
                    float distance = caster->GetDistance2d(target);
                    if (distance > 1.0f)
                        SetHitDamage(int32(GetHitDamage() - ((caster->GetMap()->Is25ManRaid() ? 10000 : 4000) * distance)));

                    if (GetHitDamage() < 10000)
                        SetHitDamage(10000);
                }
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    if (target->HasAura(SPELL_WATERLOGGED))
                    {
                        target->RemoveAurasDueToSpell(SPELL_WATERLOGGED);
                        caster->CastSpell(target, SPELL_FROZEN, true);
                    }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_glaciate_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_ac_glaciate_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_glaciate_SpellScript();
    }
};

class spell_ac_heart_of_ice : public SpellScriptLoader
{
public:
    spell_ac_heart_of_ice() : SpellScriptLoader("spell_ac_heart_of_ice") { }

    class spell_ac_heart_of_ice_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ac_heart_of_ice_AuraScript);

        void OnPeriodic(AuraEffect const* aurEff)
        {
            uint64 damage;
            damage = aurEff->GetBaseAmount() * aurEff->GetTickNumber();
            GetEffect(EFFECT_0)->ChangeAmount(damage);
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                target->CastSpell(target, SPELL_FROST_IMBUED, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ac_heart_of_ice_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE);
            OnEffectApply += AuraEffectApplyFn(spell_ac_heart_of_ice_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ac_heart_of_ice_AuraScript();
    }
};

class spell_ac_inferno_rush_fire : public SpellScriptLoader
{
public:
    spell_ac_inferno_rush_fire() : SpellScriptLoader("spell_ac_inferno_rush_fire") { }

    class spell_ac_inferno_rush_fire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_inferno_rush_fire_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (target->HasAura(SPELL_WATERLOGGED))
                    target->RemoveAurasDueToSpell(SPELL_WATERLOGGED);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_inferno_rush_fire_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_inferno_rush_fire_SpellScript();
    }
};

class spell_ac_burning_blood : public SpellScriptLoader
{
public:
    spell_ac_burning_blood() : SpellScriptLoader("spell_ac_burning_blood") { }

    class spell_ac_burning_blood_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ac_burning_blood_AuraScript);

        void OnPeriodic(AuraEffect const* aurEff)
        {
            uint64 damage;
            damage = aurEff->GetBaseAmount() * aurEff->GetTickNumber();
            GetEffect(EFFECT_0)->ChangeAmount(damage);
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                target->CastSpell(target, SPELL_FLAME_IMBUED, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ac_burning_blood_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE);
            OnEffectApply += AuraEffectApplyFn(spell_ac_burning_blood_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ac_burning_blood_AuraScript();
    }
};

class spell_ac_cryogenic_aura : public SpellScriptLoader
{
public:
    spell_ac_cryogenic_aura() : SpellScriptLoader("spell_ac_cryogenic_aura") { }

    class spell_ac_cryogenic_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ac_cryogenic_aura_AuraScript);

        void OnPeriodic(AuraEffect const* aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                if (!caster->HasAura(SPELL_LIQUID_ICE_DUMMY))
                    caster->SummonCreature(NPC_LIQUID_ICE, caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);

                if (Creature* ice = caster->FindNearestCreature(NPC_LIQUID_ICE, 200.0f, true))
                    if (caster->GetDistance2d(ice->GetPositionX(), ice->GetPositionY()) < (5.0f * ice->GetObjectSize()))
                        caster->CastSpell(ice, SPELL_LIQUID_ICE_GROWTH, true);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ac_cryogenic_aura_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ac_cryogenic_aura_AuraScript();
    }
};

class spell_ac_liquid_ice : public SpellScriptLoader
{
public:
    spell_ac_liquid_ice() : SpellScriptLoader("spell_ac_liquid_ice") { }

    class spell_ac_liquid_ice_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_liquid_ice_SpellScript);

        void FilterTargetsDamage(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(LiquidIceRangeCheck(GetCaster()));
        }

        void FilterTargetsEntry(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(LiquidIceRangeCheck(GetCaster()));

            if (targets.empty())
                return;

            targets.remove_if(ElementiumMonstrosityCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ac_liquid_ice_SpellScript::FilterTargetsDamage, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ac_liquid_ice_SpellScript::FilterTargetsEntry, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_liquid_ice_SpellScript();
    }
};

class spell_ac_eruption : public SpellScriptLoader
{
public:
    spell_ac_eruption() : SpellScriptLoader("spell_ac_eruption") { }

    class spell_ac_eruption_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_eruption_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->CastSpell(caster, SPELL_SUMMON_ERUPTION, true);
                caster->CastSpell(caster, SPELL_SUMMON_ERUPTION, true);
                caster->CastSpell(caster, SPELL_SUMMON_ERUPTION, true);
                caster->CastSpell(caster, SPELL_SUMMON_ERUPTION, true);
                caster->CastSpell(caster, SPELL_SUMMON_ERUPTION, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_eruption_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_eruption_SpellScript();
    }
};

class spell_ac_electrical_instability : public SpellScriptLoader
{
public:
    spell_ac_electrical_instability() : SpellScriptLoader("spell_ac_electrical_instability") { }

    class spell_ac_electrical_instability_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_electrical_instability_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            uint32 size = GetCaster()->GetInstanceScript()->GetData(DATA_ELECTRICAL_INSTABILITY_CHARGES);

            if (size == 0)
                size = 1;

            Trinity::Containers::RandomResizeList(targets, size);
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->CastSpell(target, SPELL_ELECTRIC_INSTABILITY_DAMAGE, false);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ac_electrical_instability_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_ac_electrical_instability_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_electrical_instability_SpellScript();
    }
};

class spell_ac_gravity_crush : public SpellScriptLoader
{
public:
    spell_ac_gravity_crush() : SpellScriptLoader("spell_ac_gravity_crush") { }

    class spell_ac_gravity_crush_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_gravity_crush_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 3 : 1);
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    if (Creature* crush = caster->SummonCreature(NPC_GRAVITY_CRUSH, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 6600))
                        target->CastSpell(crush, SPELL_GRAVITY_CRUSH_VEHICLE, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ac_gravity_crush_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_ac_gravity_crush_SpellScript::HandleHit, EFFECT_2, SPELL_EFFECT_FORCE_CAST);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_gravity_crush_SpellScript();
    }
};

void AddSC_boss_ascendant_council()
{
    new at_ascendant_council_1();
    new at_ascendant_council_2();
    new at_ascendant_council_3();
    new boss_feludius();
    new boss_ignacious();
    new boss_terrastra();
    new boss_arion();
    new boss_elementium_monstrosity();
    new npc_ascendant_council_controller();
    new npc_ac_plume_stalker();
    new spell_ac_water_bomb();
    new spell_ac_glaciate();
    new spell_ac_heart_of_ice();
    new spell_ac_inferno_rush_fire();
    new spell_ac_burning_blood();
    new spell_ac_cryogenic_aura();
    new spell_ac_liquid_ice();
    new spell_ac_eruption();
    new spell_ac_electrical_instability();
    new spell_ac_gravity_crush();
}
