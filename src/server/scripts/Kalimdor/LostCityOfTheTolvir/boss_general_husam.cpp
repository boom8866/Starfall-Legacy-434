/*
 * Copyright (C) 2014 NorthStrider
 */

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
#include "lost_city_of_the_tolvir.h"

enum Spells
{
    // General Husam
    SPELL_SUMMON_SHOCKWAVE_DUMMY_N      = 83131,
    SPELL_SUMMON_SHOCKWAVE_DUMMY_S      = 83132,
    SPELL_SUMMON_SHOCKWAVE_DUMMY_E      = 83133,
    SPELL_SUMMON_SHOCKWAVE_DUMMY_W      = 83134,
    SPELL_SUMMON_SHOCKWAVE_VISUAL       = 83128,
    SPELL_SHOCKWAVE                     = 83445,
    SPELL_SHOCKWAVE_MISSILE             = 83130,
    SPELL_SHOCKWAVE_DAMAGE              = 83454,
    SPELL_SHOCKWAVE_VISUAL_SUMMON       = 83129,
    SPELL_SUMMON_MYSTIC_TRAP            = 83644,
    SPELL_THROW_LANDMINES               = 83122,
    SPELL_THROW_LAND_MINES_TARGET       = 83646,
    SPELL_DETONATE_TRAPS                = 91263,
    SPELL_BAD_INTENTIONS                = 83113,
    SPELL_THROW_PILLAR                  = 81350,
    SPELL_HARD_IMPACT                   = 83339,
    SPELL_HAMMER_FIST                   = 83654,

    // Traps
    SPELL_LAND_MINE_EXPLODE             = 83171,
    SPELL_LAND_MINE_VISUAL              = 83110,
    SPELL_LAND_MINE_SEARCH              = 83111,
    SPELL_LAND_MINE_SEARCH_TRIGGERED    = 83112,
    SPELL_LAND_MINE_ACTIVATE            = 85523,

    SPELL_RIDE_VEHICLE_HARDCODED        = 46598,
};

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_SHOCKWAVE           = 1,
    SAY_ANNOUNCE_SHOCKWAVE  = 2,
    SAY_TRAP                = 3,
    SAY_DEATH               = 4,
    SAY_SLAY                = 5,
};

enum Events
{
    // General Husam
    EVENT_SHOCKWAVE = 1,
    EVENT_SUMMON_MYSTIC_TRAP,
    EVENT_SEARCH_MINES,
    EVENT_DETONATE_TRAPS,
    EVENT_BAD_INTENTIONS,
    EVENT_THROW_PLAYER,
    EVENT_DAMAGE_PLAYER,
    EVENT_HAMMER_FIST,

    // Shockwave Visual
    EVENT_SHOCKWAVE_DAMAGE,

    // Traps
    EVENT_PREPARE_TRAP,
    EVENT_SCHEDULE_EXPLODE,
    EVENT_EXPLODE,
    EVENT_SUMMON_TRAP,
};

enum Actions
{
    ACTION_DETONATE = 1,
};

class boss_general_husam : public CreatureScript
{
public:
    boss_general_husam() : CreatureScript("boss_general_husam") { }

    struct boss_general_husamAI : public BossAI
    {
        boss_general_husamAI(Creature* creature) : BossAI(creature, DATA_GENERAL_HUSAM)
        {
            triggerCount = 0;
            player = NULL;
        }

        uint8 triggerCount;
        Unit* player;

        void Reset()
        {
            _Reset();
            triggerCount = 0;
            player = NULL;
            me->SetWalk(true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_SHOCKWAVE, 18000);
            events.ScheduleEvent(EVENT_SUMMON_MYSTIC_TRAP, 7500);
            events.ScheduleEvent(EVENT_BAD_INTENTIONS, 12000);
            events.ScheduleEvent(EVENT_HAMMER_FIST, 9800);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_DETONATE_TRAPS, 26000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            triggerCount = 0;
            Cleanup();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_SHOCKWAVE_TRIGGER:
                    triggerCount++;
                    summon->SetSpeed(MOVE_RUN, 1.5f);
                    if (triggerCount == 1)
                        summon->SetPosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                    else if (triggerCount == 2)
                        summon->SetOrientation(me->GetOrientation() + M_PI);
                    else if (triggerCount == 3)
                        summon->SetOrientation(me->GetOrientation() + M_PI/2);
                    else if (triggerCount == 4)
                        summon->SetOrientation(me->GetOrientation() - M_PI/2);

                    summon->GetMotionMaster()->MovePoint(0, summon->GetPositionX()+cos(summon->GetOrientation()) * 200, summon->GetPositionY()+sin(summon->GetOrientation()) * 200, summon->GetPositionZ(), false);
                    if (triggerCount > 3)
                    {
                        DoCastAOE(SPELL_SHOCKWAVE);
                        triggerCount = 0;
                    }
                    summons.Summon(summon);
                    break;
                default:
                    summons.Summon(summon);
                    break;

            }
        }

        void JustDied(Unit* /*who*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            Cleanup();
        }

        void Cleanup()
        {
            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_TOLVIR_LANDMINE_DUMMY, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_TOLVIR_LANDMINE_PASSENGER, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_TOLVIR_LANDMINE_VEHICLE, 500.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon(1);

        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->GetAreaId() != 5635)
            {
                EnterEvadeMode();
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHOCKWAVE:
                        Talk(SAY_SHOCKWAVE);
                        Talk(SAY_ANNOUNCE_SHOCKWAVE);
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_N);
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_S);
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_E);
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_W);
                        events.ScheduleEvent(EVENT_SHOCKWAVE, 39500);
                        break;
                    case EVENT_SUMMON_MYSTIC_TRAP:
                        DoCastAOE(SPELL_SUMMON_MYSTIC_TRAP);
                        events.ScheduleEvent(EVENT_SUMMON_MYSTIC_TRAP, 16500);
                        events.ScheduleEvent(EVENT_SEARCH_MINES, 300);
                        break;
                    case EVENT_SEARCH_MINES:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_TOLVIR_LANDMINE_DUMMY, 500.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                            me->CastSpell(*itr, SPELL_THROW_LANDMINES);
                        break;
                    }
                    case EVENT_BAD_INTENTIONS:
                        if (player = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        {
                            DoCast(player, SPELL_BAD_INTENTIONS);
                            player->CastSpell(me, SPELL_RIDE_VEHICLE_HARDCODED);
                            events.ScheduleEvent(EVENT_THROW_PLAYER, 500);
                        }
                        events.ScheduleEvent(EVENT_BAD_INTENTIONS, 25000);
                        break;
                    case EVENT_THROW_PLAYER:
                        if (Creature* dummy = me->FindNearestCreature(NPC_BAD_INTENTIONS_TARGET, 200.0f))
                        {
                            me->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE_HARDCODED);
                            player->CastSpell(dummy, SPELL_RIDE_VEHICLE_HARDCODED);
                            DoCastAOE(SPELL_THROW_PILLAR);
                        }
                        break;
                    case EVENT_DAMAGE_PLAYER:
                        DoCast(player, SPELL_HARD_IMPACT);
                        break;
                    case EVENT_DETONATE_TRAPS:
                        DoCastAOE(SPELL_DETONATE_TRAPS);
                        events.ScheduleEvent(EVENT_DETONATE_TRAPS, 90000);
                        break;
                    case EVENT_HAMMER_FIST:
                        DoCastAOE(SPELL_HAMMER_FIST);
                        events.ScheduleEvent(EVENT_HAMMER_FIST, 20000);
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
        return new boss_general_husamAI(creature);
    }
};

class npc_lct_shockwave_visual : public CreatureScript
{
    public:
        npc_lct_shockwave_visual() :  CreatureScript("npc_lct_shockwave_visual") { }

        struct npc_lct_shockwave_visualAI : public ScriptedAI
        {
            npc_lct_shockwave_visualAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                events.ScheduleEvent(EVENT_SHOCKWAVE_DAMAGE, 4500);
                me->SetReactState(REACT_PASSIVE);
                SetCombatMovement(false);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SHOCKWAVE_DAMAGE:
                            DoCastAOE(SPELL_SHOCKWAVE_DAMAGE);
                            me->DespawnOrUnsummon(500);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_shockwave_visualAI(creature);
        }
};

class npc_lct_landmine_vehicle : public CreatureScript
{
    public:
        npc_lct_landmine_vehicle() :  CreatureScript("npc_lct_landmine_vehicle") { }

        struct npc_lct_landmine_vehicleAI : public ScriptedAI
        {
            npc_lct_landmine_vehicleAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetReactState(REACT_PASSIVE);
                SetCombatMovement(false);
                events.ScheduleEvent(EVENT_SUMMON_TRAP, 1000);
            }

            void PassengerRemoved(Unit* /*passenger*/, bool /*apply*/)
            {
                me->DespawnOrUnsummon(1);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUMMON_TRAP:
                            if (Creature* mine = me->SummonCreature(NPC_TOLVIR_LANDMINE_PASSENGER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN))
                                mine->AI()->DoCast(me, SPELL_RIDE_VEHICLE_HARDCODED);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_landmine_vehicleAI(creature);
        }
};

class npc_lct_landmine_passenger : public CreatureScript
{
    public:
        npc_lct_landmine_passenger() :  CreatureScript("npc_lct_landmine_passenger") { }

        struct npc_lct_landmine_passengerAI : public ScriptedAI
        {
            npc_lct_landmine_passengerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetReactState(REACT_PASSIVE);
                SetCombatMovement(false);
                events.ScheduleEvent(EVENT_PREPARE_TRAP, 2000);
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_DETONATE:
                        me->RemoveAurasDueToSpell(SPELL_LAND_MINE_SEARCH);
                        me->RemoveAurasDueToSpell(SPELL_LAND_MINE_VISUAL);
                        DoCastAOE(SPELL_LAND_MINE_ACTIVATE);
                        events.ScheduleEvent(EVENT_EXPLODE, 10000);
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
                        case EVENT_PREPARE_TRAP:
                            DoCastAOE(SPELL_LAND_MINE_SEARCH);
                            DoCastAOE(SPELL_LAND_MINE_VISUAL);
                            break;
                        case EVENT_EXPLODE:
                            me->DespawnOrUnsummon(1);
                            break;
                        default:
                            break;
                    }
                }
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_LAND_MINE_SEARCH_TRIGGERED && target->GetTypeId() == TYPEID_PLAYER)
                {
                    me->RemoveAurasDueToSpell(SPELL_LAND_MINE_SEARCH);
                    me->RemoveAurasDueToSpell(SPELL_LAND_MINE_VISUAL);
                    DoCastAOE(SPELL_LAND_MINE_ACTIVATE);
                    events.ScheduleEvent(EVENT_EXPLODE, 10000);
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_landmine_passengerAI(creature);
        }
};

class npc_lct_bad_intentions_vehicle : public CreatureScript
{
    public:
        npc_lct_bad_intentions_vehicle() :  CreatureScript("npc_lct_bad_intentions_vehicle") { }

        struct npc_lct_bad_intentions_vehicleAI : public ScriptedAI
        {
            npc_lct_bad_intentions_vehicleAI(Creature* creature) : ScriptedAI(creature), vehicle(creature->GetVehicleKit())
            {
            }

            EventMap events;
            Vehicle* vehicle;
            Unit* player;

            void PassengerBoarded(Unit* passenger, int8 /*SeatId*/, bool /*apply*/)
            {
                player = passenger;
                sLog->outError(LOG_FILTER_SQL, "inentions vehicle entered");
                if (Creature* husam = me->FindNearestCreature(BOSS_GENERAL_HUSAM, 100.0f))
                {
                    uint32 event_time = me->GetExactDist2d(husam->GetPositionX(), husam->GetPositionY()) * 20;
                    events.ScheduleEvent(EVENT_DAMAGE_PLAYER, event_time);
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DAMAGE_PLAYER:
                            player->CastSpell(player, SPELL_HARD_IMPACT);
                            me->RemoveAllAuras();
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_bad_intentions_vehicleAI(creature);
        }
};

class spell_lct_shockwave_summon : public SpellScriptLoader
{
    public:
        spell_lct_shockwave_summon() : SpellScriptLoader("spell_lct_shockwave_visual_summon") { }

        class spell_lct_shockwave_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lct_shockwave_summon_AuraScript);

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_SUMMON_SHOCKWAVE_VISUAL);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_lct_shockwave_summon_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lct_shockwave_summon_AuraScript();
        }
};

class spell_lct_shockwave : public SpellScriptLoader
{
    public:
        spell_lct_shockwave() : SpellScriptLoader("spell_lct_shockwave") { }

        class spell_lct_shockwave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lct_shockwave_SpellScript);

            void EffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHOCKWAVE_MISSILE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_lct_shockwave_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lct_shockwave_SpellScript();
        }
};

class spell_lct_bad_intentions : public SpellScriptLoader
{
public:
    spell_lct_bad_intentions() : SpellScriptLoader("spell_lct_bad_intentions") { }

    class spell_lct_bad_intentions_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_lct_bad_intentions_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetCaster(), SPELL_RIDE_VEHICLE_HARDCODED);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_lct_bad_intentions_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_lct_bad_intentions_SpellScript();
    }
};

class spell_lct_detonate_traps : public SpellScriptLoader
{
    public:
        spell_lct_detonate_traps() : SpellScriptLoader("spell_lct_detonate_traps") { }

        class spell_lct_detonate_traps_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lct_detonate_traps_SpellScript);

            void EffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                GetHitUnit()->ToCreature()->AI()->DoAction(ACTION_DETONATE);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_lct_detonate_traps_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lct_detonate_traps_SpellScript();
        }
};

class spell_lct_hammer_fist : public SpellScriptLoader
{
    public:
        spell_lct_hammer_fist() : SpellScriptLoader("spell_lct_hammer_fist") { }

    private:
        class spell_lct_hammer_fist_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lct_hammer_fist_AuraScript)

            void HandleTick(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                GetCaster()->CastSpell(GetCaster()->getVictim(), GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_lct_hammer_fist_AuraScript::HandleTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lct_hammer_fist_AuraScript();
        }
};

void AddSC_boss_general_husam()
{
    new boss_general_husam();
    new npc_lct_shockwave_visual();
    new npc_lct_landmine_vehicle();
    new npc_lct_landmine_passenger();
    new npc_lct_bad_intentions_vehicle();
    new spell_lct_shockwave_summon();
    new spell_lct_shockwave();
    new spell_lct_bad_intentions();
    new spell_lct_detonate_traps();
    new spell_lct_hammer_fist();
}
