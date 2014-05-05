#include "ScriptPCH.h"
#include "deadmines.h"
#include "Vehicle.h"

enum Spells
{
    // Helix
    SPELL_OAFQUARD                  = 90546,
    SPELL_HELIX_RIDE                = 88337,
    SPELL_RIDE_VEHICLE              = 52391,
    SPELL_EMOTE_CHEST_BOMB          = 91572, // Hits the enemy and triggers the bomb spells
    SPELL_THROW_BOMB_MISSILE        = 88264,

    // Lumbering Oaf
    SPELL_OAF_GRAB_TARGETING        = 88289,
    SPELL_RIDE_OAF                  = 88277,
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
    SPELL_OAF_CHARGE                = 88288,
    SPELL_OAF_SMASH                 = 88295,
    SPELL_OAF_THROW                 = 88374,
    SPELL_EJECT_PASSENGER           = 62539,

    // Sticky Bomb
    SPELL_STICKY_BOMB_EXPLODE_AURA  = 88329,
    SPELL_STICKY_BOMB_EXPLODE       = 88321,
    SPELL_ARMING_VISUAL_YELLOW      = 88315,
    SPELL_ARMING_VISUAL_ORANGE      = 88316,
    SPELL_ARMING_VISUAL_RED         = 88317,
    SPELL_ARMED_STATE               = 88319,

    // Chest Bomb
    SPELL_CHEST_BOMB_EXPLOSION      = 88250,
    SPELL_CHEST_BOMB                = 88352,

    // Helix Crew
    SPELL_BOMB_TARGETING            = 88268, // better use random target selector
};

const Position OafPos[2] = 
{
    {-289.809f, -527.215f, 49.8021f, 0},
    {-289.587f, -489.575f, 49.9126f, 0},
};

enum Texts
{
    // Helix Gearbreaker
    SAY_AGGRO           = 0,
    SAY_THROW_BOMB      = 1,
    SAY_THROW_HELIX     = 2,
    SAY_ATTACH_BOMB     = 3,
    SAY_OAF_DEAD        = 4,
    SAY_SLAY            = 5,
    SAY_DEATH           = 6,

    // Helix Crew
    SAY_CREW            = 0,

    // Lumbering Oaf
    SAY_OAF_CHARGE_1    = 0,
    SAY_OAF_CHARGE_2    = 1,
    SAY_DEATH_OAF       = 2,
};

enum Events
{
    // Helix Gearbreaker
    EVENT_CHEST_BOMB = 1,
    EVENT_THROW_BOMB,
    EVENT_CREW_BOMB,
    EVENT_MOUNT_OAF,
    EVENT_THROW_HELIX,
    EVENT_SWITCH_PLAYER,

    // Lumbering Oaf
    EVENT_FINISH,
    EVENT_OAF_THROW,
    EVENT_TALK_CRUSH,
    EVENT_CRASH,

    // Sticky Bomb
    EVENT_TICK,
    EVENT_DETONATE,
    EVENT_CHECK_PLAYER,
};

enum Actions
{
    ACTION_THROW_HELIX  = 1,
    ACTION_MOUNT_BACK,
    ACTION_START_CRUSH,
    ACTION_OAF_KILLED,
};

enum Points
{
    POINT_CHARGE    = 0,
    POINT_CRASH     = 1,
};

enum Phases
{
    PHASE_OAF   = 1,
    PHASE_HELIX = 2,
};

const Position CrewPos1[] =
{
    {-287.479f, -503.270f, 60.448f, 1.67f},
    {-289.832f, -503.406f, 60.363f, 1.67f},
    {-285.868f, -503.825f, 60.553f, 5.00f},
    {-291.078f, -504.093f, 60.251f, 5.00f},
};

const Position CrewPos2[] =
{
    {-283.843f, -503.369f, 60.512f, 1.67f},
    {-294.162f, -503.233f, 60.125f, 1.67f},
    {-292.678f, -503.726f, 60.273f, 5.00f},
    {-282.264f, -503.833f, 60.602f, 5.00f},
};

class boss_helix_gearbreaker : public CreatureScript
{
public:
    boss_helix_gearbreaker() : CreatureScript("boss_helix_gearbreaker") { }

    struct boss_helix_gearbreakerAI : public BossAI
    {
        boss_helix_gearbreakerAI(Creature* creature) : BossAI(creature, DATA_HELIX)
        {
        }

        void Reset()
        {
            _Reset();
            SetupOaf();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_THROW_BOMB, 5500);
            events.ScheduleEvent(EVENT_THROW_HELIX, 34500);
            if (IsHeroic())
                for (uint8 i = 0; i < 4; i++)
                    me->SummonCreature(NPC_HELIX_CREW, CrewPos1[i], TEMPSUMMON_MANUAL_DESPAWN);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void SetupOaf()
        {
            if (Creature* oldOaf = me->FindNearestCreature(NPC_LUMBERING_OAF, 200.0f, true))
            {
                oldOaf->DespawnOrUnsummon(1);
                if (Creature* newOaf = me->SummonCreature(NPC_LUMBERING_OAF, me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), me->GetHomePosition().GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN))
                {
                    DoCast(newOaf, SPELL_RIDE_VEHICLE_HARDCODED);
                    DoCast(me, SPELL_OAFQUARD);
                    me->SetFlag(UNIT_FIELD_FLAGS, 33587264);
                    me->SetReactState(REACT_PASSIVE);
                    events.SetPhase(PHASE_OAF);
                }
            }
            else
                if (Creature* newOaf = me->SummonCreature(NPC_LUMBERING_OAF, me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), me->GetHomePosition().GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN))
                {
                    DoCast(newOaf, SPELL_RIDE_VEHICLE_HARDCODED);
                    DoCast(me, SPELL_OAFQUARD);
                    me->SetFlag(UNIT_FIELD_FLAGS, 33587264);
                    me->SetReactState(REACT_PASSIVE);
                    events.SetPhase(PHASE_OAF);
                }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOUNT_BACK:
                    events.CancelEvent(EVENT_THROW_BOMB);
                    events.ScheduleEvent(EVENT_MOUNT_OAF, 10000);
                    break;
                case ACTION_OAF_KILLED:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    events.CancelEvent(EVENT_THROW_BOMB);
                    events.CancelEvent(EVENT_THROW_HELIX);
                    me->RemoveAura(SPELL_OAFQUARD);
                    Talk(SAY_OAF_DEAD);
                    DoCastAOE(SPELL_HELIX_RIDE);
                    if (IsHeroic())
                    {
                        for (uint8 i = 0; i < 4; i++)
                            me->SummonCreature(NPC_HELIX_CREW, CrewPos2[i], TEMPSUMMON_MANUAL_DESPAWN);
                        events.ScheduleEvent(EVENT_CHEST_BOMB, 10000);

                    }

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    {
                        DoCast(target, SPELL_RIDE_VEHICLE);
                        me->Attack(target, true);
                    }
                    events.ScheduleEvent(EVENT_CHEST_BOMB, 10000);
                    events.SetPhase(PHASE_HELIX);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (events.IsInPhase(PHASE_HELIX))
                if (!UpdateVictim()) 
                    return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_THROW_BOMB:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_THROW_BOMB_MISSILE);
                        events.ScheduleEvent(EVENT_THROW_BOMB, 3500);
                        break;
                    case EVENT_THROW_HELIX:
                        Talk(SAY_THROW_HELIX);
                        if (Creature* oaf = me->FindNearestCreature(NPC_LUMBERING_OAF, 200.0f, true))
                            oaf->AI()->DoAction(ACTION_THROW_HELIX);
                        break;
                    case EVENT_MOUNT_OAF:
                        me->SetFlag(UNIT_FIELD_FLAGS, 33587264);
                        me->AttackStop();
                        if (me->GetVehicleBase())
                            me->GetVehicleBase()->ToPlayer()->RemoveAura(SPELL_RIDE_VEHICLE);

                        if (Creature* oaf = me->FindNearestCreature(NPC_LUMBERING_OAF, 200.0f, true))
                        {
                            DoCast(oaf, SPELL_RIDE_VEHICLE_HARDCODED);
                            events.ScheduleEvent(EVENT_THROW_BOMB, 5500);
                        }
                        break;
                    case EVENT_CHEST_BOMB:
                        if (me->GetVehicleBase())
                        {
                            DoCast(me->GetVehicleBase(), SPELL_CHEST_BOMB);
                            Talk(SAY_ATTACH_BOMB, me->GetVehicleBase()->GetGUID());
                        }
                        events.ScheduleEvent(EVENT_SWITCH_PLAYER, 3000);
                        break;
                    case EVENT_SWITCH_PLAYER:
                        if (me->GetVehicleBase())
                            me->GetVehicleBase()->RemoveAura(SPELL_RIDE_VEHICLE);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        {
                            DoCast(target, SPELL_RIDE_VEHICLE);
                            me->Attack(target, true);
                        }
                        events.ScheduleEvent(EVENT_CHEST_BOMB, 100000);
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
        return new boss_helix_gearbreakerAI (creature);
    }
};

Position const ChargePos = {-289.809f, -527.215f, 49.8021f};

class npc_lumbering_oaf : public CreatureScript
{
public:
    npc_lumbering_oaf() : CreatureScript("npc_lumbering_oaf") { }

    struct npc_lumbering_oafAI : public ScriptedAI
    {
        npc_lumbering_oafAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            charging = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool charging;

        void EnterCombat(Unit* who)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (Creature* helix = me->FindNearestCreature(BOSS_HELIX_GEARBREAKER, 50.0f, true))
                helix->SetInCombatWithZone();
            events.ScheduleEvent(EVENT_CHARGE, 16000);
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (Creature* helix = me->FindNearestCreature(BOSS_HELIX_GEARBREAKER, 50.0f, true))
                helix->AI()->EnterEvadeMode();
            me->DespawnOrUnsummon(1);
        }

        void JustDied(Unit* /*who*/)
        {
            Talk(SAY_DEATH_OAF);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (Creature* helix = me->FindNearestCreature(BOSS_HELIX_GEARBREAKER, 200.0f, true))
                helix->AI()->DoAction(ACTION_OAF_KILLED);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_EJECT_PASSENGER)
            {
                me->RemoveAurasDueToSpell(SPELL_RIDE_OAF);
                charging = false;
                me->GetMotionMaster()->MoveChase(me->getVictim(), 0.0f, 0.0f);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_THROW_HELIX:
                    events.ScheduleEvent(EVENT_OAF_THROW, 2200);
                    break;
                case ACTION_START_CRUSH:
                    me->GetMotionMaster()->MovePoint(POINT_CHARGE, ChargePos);
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CHARGE:
                    events.ScheduleEvent(EVENT_CRASH, 1000);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!charging)
                if (!UpdateVictim())
                    return;

            events.Update(diff);
                
            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_OAF_THROW:
                        DoCastAOE(SPELL_OAF_THROW);
                        if (Creature* helix = me->FindNearestCreature(BOSS_HELIX_GEARBREAKER, 200.0f, true))
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            {
                                helix->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                                me->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE_HARDCODED);
                                helix->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE_HARDCODED);
                                helix->AddAura(SPELL_HELIX_RIDE, target);
                                helix->CastSpell(target, SPELL_RIDE_VEHICLE);
                                helix->Attack(target, true);
                                helix->AI()->DoAction(ACTION_MOUNT_BACK);
                                helix->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                            }
                        break;
                    case EVENT_CHARGE:
                        Talk(SAY_OAF_CHARGE_1);
                        charging = true;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_OAF_CHARGE);
                        events.ScheduleEvent(EVENT_TALK_CRUSH, 1000);
                        events.ScheduleEvent(EVENT_CHARGE, 52000);
                        break;
                    case EVENT_TALK_CRUSH:
                        Talk(SAY_OAF_CHARGE_2);
                        break;
                    case EVENT_CRASH:
                        DoCastAOE(SPELL_OAF_SMASH);
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
        return new npc_lumbering_oafAI(creature);
    }
};

class npc_sticky_bomb : public CreatureScript
{
public:
    npc_sticky_bomb() : CreatureScript("npc_sticky_bomb") { }

    struct npc_sticky_bombAI : public ScriptedAI
    {
        npc_sticky_bombAI(Creature* creature) : ScriptedAI(creature)
        {
            ticker = 0;
        }

        EventMap events;
        uint8 ticker;

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE); 
        }

        void IsSummonedBy(Unit* summoner)
        {
            events.ScheduleEvent(EVENT_TICK, 1200);
            if (summoner->GetEntry() == NPC_HELIX_CREW)
                ticker = 1;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_TICK:
                        if (ticker == 0)
                            DoCastAOE(SPELL_ARMING_VISUAL_YELLOW);
                        else if (ticker == 1)
                            DoCastAOE(SPELL_ARMING_VISUAL_ORANGE);
                        else if (ticker == 2)
                            DoCastAOE(SPELL_ARMING_VISUAL_RED);
                        else if (ticker == 3)
                        {
                            DoCastAOE(SPELL_ARMED_STATE);
                            events.ScheduleEvent(EVENT_CHECK_PLAYER, 100);
                            events.ScheduleEvent(EVENT_DETONATE, 18000);
                        }

                        if (ticker <= 3)
                        {
                            events.ScheduleEvent(EVENT_TICK, 1200);
                            ticker++;
                        }
                        break;
                    case EVENT_CHECK_PLAYER:
                        if (me->FindNearestPlayer(1.0f, true))
                        {
                            DoCastAOE(SPELL_STICKY_BOMB_EXPLODE);
                            events.CancelEvent(EVENT_DETONATE);
                            me->GetMotionMaster()->Clear();
                            me->DespawnOrUnsummon(500);
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_PLAYER, 100);
                        break;
                    case EVENT_DETONATE:
                        events.CancelEvent(EVENT_CHECK_PLAYER);
                        DoCastAOE(SPELL_STICKY_BOMB_EXPLODE);
                        me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 0.1f, false);
                        me->DespawnOrUnsummon(100);
                        break;
                    default:
                        break;
                }
            }

        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sticky_bombAI (creature);
    }
};

class npc_helix_crew : public CreatureScript
{
public:
    npc_helix_crew() : CreatureScript("npc_helix_crew") { }

    struct npc_helix_crewAI : public ScriptedAI
    {
        npc_helix_crewAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetInCombatWithZone();
            events.ScheduleEvent(EVENT_THROW_BOMB, urand(3000, 5500));
        }

        void Reset()
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_THROW_BOMB:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_THROW_BOMB_MISSILE);
                        events.ScheduleEvent(EVENT_THROW_BOMB, urand(3000, 5500));
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_helix_crewAI (creature);
    }
};

class spell_dm_chest_bomb : public SpellScriptLoader
{
    public:
        spell_dm_chest_bomb() :  SpellScriptLoader("spell_dm_chest_bomb") { }

        class spell_dm_chest_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dm_chest_bomb_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CHEST_BOMB))
                    return false;
                return true;
            }

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                GetTarget()->CastSpell(GetCaster(), SPELL_CHEST_BOMB_EXPLOSION);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dm_chest_bomb_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dm_chest_bomb_AuraScript();
        }
};

class spell_dm_ride_oaf : public SpellScriptLoader
{
public:
    spell_dm_ride_oaf() : SpellScriptLoader("spell_dm_ride_oaf") { }

    class spell_dm_ride_oaf_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dm_ride_oaf_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Creature* oaf = GetHitUnit()->FindNearestCreature(NPC_LUMBERING_OAF, 200.0f, true))
            {
                GetHitUnit()->CastSpell(oaf, SPELL_RIDE_OAF);
                oaf->AI()->DoAction(ACTION_START_CRUSH);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dm_ride_oaf_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dm_ride_oaf_SpellScript();
    }
};

void AddSC_boss_helix_gearbreaker()
{
    new boss_helix_gearbreaker();
    new npc_lumbering_oaf();
    new npc_sticky_bomb();
    new npc_helix_crew();
    new spell_dm_chest_bomb();
    new spell_dm_ride_oaf();
}
