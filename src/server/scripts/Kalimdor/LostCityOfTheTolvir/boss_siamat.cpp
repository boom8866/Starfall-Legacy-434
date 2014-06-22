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
#include "WeatherMgr.h"
#include "Weather.h"

enum Texts
{
    SAY_INTRO   = 0,
    SAY_AGGRO   = 1,
    SAY_WINDS   = 2,
    SAY_SLAY    = 3,
    SAY_DEATH   = 4,
};

enum Spells
{
    // Siamat
    SPELL_STORM_BOLT_1              = 73564,
    SPELL_STORM_BOLT_2              = 91853,
    SPELL_DEFLECTING_WINDS          = 84589,
    SPELL_STATIC_SHOCK_1            = 84546,
    SPELL_STATIC_SHOCK_2            = 84555,
    SPELL_STATIC_SHOCK_3            = 84556,
    SPELL_WAILING_WINDS             = 83066,
    SPELL_WAILING_WINDS_DAMAGE      = 83094,
    SPELL_CALL_OF_SKY               = 84956,
    SPELL_CLOUDBURST_SUMMON         = 83790,
    SPELL_ABSORB_STORM              = 83151,
    SPELL_GATHERED_STORM_AURA       = 84982,
    SPELL_GATHERED_STORM_TRIGGERED  = 84987,

    // Servant of Siamat
    SPELL_LIGHTNING_NOVA            = 84544,
    SPELL_THUNDER_CRASH             = 84521,
    SPELL_LIGHTNING_CHARGE          = 91872,

    // Minion of Siamat
    SPELL_CHAIN_LIGHTNING           = 83455,
    SPELL_TEMPEST_STORM             = 83446,
    SPELL_TEMPEST_STORM_CLOUD       = 83414,
    SPELL_TEMPEST_STORM_AURA        = 83406,
    SPELL_TRANSFORM                 = 83170,
    SPELL_DEPLETION                 = 84550,

    // Cloudburst
    SPELL_CLOUDBURST                = 83048,
    SPELL_CLOUDBURST_KNOCKBACK      = 83051,

    // Generic
    SPELL_WEATHER_RAIN              = 82651,
    // SPELL_GROWTH_VISUAL          = 59632,

    // Wind Tunnel
    SPELL_WIND_TUNNEL               = 89698,
    SPELL_RIDE_VEHICLE              = 93970,
    SPELL_SLIPSTREAM                = 85016,
    SPELL_SLIPSTREAM_TRIGGERED      = 85017,
    SPELL_SLIPSTREAM_DUMMY          = 85063,
};

enum Events
{
    // Siamat
    EVENT_STORM_BOLT = 1,
    EVENT_DEFLECTING_WINDS,
    EVENT_STATIC_SHOCK_PREPARE,
    EVENT_STATIC_SHOCK_CAST,
    EVENT_CALL_OF_SKY_PREPARE,
    EVENT_CALL_OF_SKY_CAST,
    EVENT_SUMMON_CLOUD_BURST,
    EVENT_ABSORB_STORM_PREPARE,
    EVENT_ABSORB_STORM_CAST,
    EVENT_STORM,

    // Servant of Siamat
    EVENT_LIGHTNING_NOVA,
    EVENT_THUNDER_CRASH,

    // Minion of Siamat
    EVENT_CHAIN_LIGHTNING,
    EVENT_MOVE_ARROUND,

    // Cloud Burst
    EVENT_KNOCKBACK,

    // Slipstream
    EVENT_CHECK_BOSSES,
    EVENT_ENABLE_STREAM,
    EVENT_THROW_PLAYER,
    EVENT_DROP_PLAYER,
};

enum Phases
{
    PHASE_ONE = 1,
    PHASE_TWO,
};

enum Actions
{
    ACTION_BREAK_PLATFORM = 1,
    ACTION_SERVANT_KILLED,
};

class boss_siamat : public CreatureScript
{
public:
    boss_siamat() : CreatureScript("boss_siamat") { }

    struct boss_siamatAI : public BossAI
    {
        boss_siamatAI(Creature* creature) : BossAI(creature, DATA_SIAMAT)
        {
            _introDone = false;
            _shockReady = true;
            _minionReady = false;
            _stormReady = false;
            _servantCounter = 0;
            _shockCounter = 0;
        }

        void Reset()
        {
            _Reset();
            _introDone = false;
            _shockReady = true;
            _minionReady = false;
            _stormReady = false;
            _servantCounter = 0;
            _shockCounter = 0;
            events.SetPhase(PHASE_ONE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (events.IsInPhase(PHASE_ONE))
                TalkToMap(SAY_AGGRO);

            _EnterCombat();
            events.ScheduleEvent(EVENT_STATIC_SHOCK_CAST, 200);
            events.ScheduleEvent(EVENT_STORM_BOLT, 500);
            events.ScheduleEvent(EVENT_DEFLECTING_WINDS, 6000);
            events.ScheduleEvent(EVENT_CALL_OF_SKY_PREPARE, 13000);
            events.ScheduleEvent(EVENT_SUMMON_CLOUD_BURST, 17000);
        }

        void JustDied(Unit* /*killer*/)
        {
            TalkToMap(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            events.Reset();
            events.SetPhase(PHASE_ONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            _servantCounter = 0;
            _shockCounter = 0;
            _shockReady = true;
            _minionReady = false;
            _stormReady = false;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_BREAK_PLATFORM:
                    if (GameObject* platform = me->FindNearestGameObject(GO_SIAMAT_PLATFORM, 500.0f))
                    {
                        if (!_introDone)
                        {
                            platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                            instance->DoCastSpellOnPlayers(SPELL_WEATHER_RAIN);
                            TalkWithDelay(15500, SAY_INTRO);
                            _introDone = true;
                        }
                    }
                    break;
                case ACTION_SERVANT_KILLED:
                    _servantCounter++;
                    if (_servantCounter == 3)
                    {
                        Talk(SAY_WINDS);
                        events.SetPhase(PHASE_TWO);
                        me->CastStop();
                        me->RemoveAurasDueToSpell(SPELL_DEFLECTING_WINDS);
                        DoCastAOE(SPELL_WAILING_WINDS);
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                        events.RescheduleEvent(EVENT_STORM_BOLT, 18000);
                        events.ScheduleEvent(EVENT_ABSORB_STORM_PREPARE, 14000);
                        events.CancelEvent(EVENT_CALL_OF_SKY_PREPARE);
                        events.CancelEvent(EVENT_CALL_OF_SKY_CAST);
                        events.CancelEvent(EVENT_STATIC_SHOCK_CAST);
                        events.CancelEvent(EVENT_STATIC_SHOCK_PREPARE);
                        events.CancelEvent(EVENT_SUMMON_CLOUD_BURST);
                    }
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
                switch(eventId)
                {
                    case EVENT_STORM_BOLT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            if (events.IsInPhase(PHASE_ONE))
                                DoCast(target, SPELL_STORM_BOLT_1);
                            else
                                DoCast(target, SPELL_STORM_BOLT_2);
                        events.ScheduleEvent(EVENT_STORM_BOLT, 2500);
                        events.ScheduleEvent(EVENT_STATIC_SHOCK_CAST, 2300);
                        events.ScheduleEvent(EVENT_CALL_OF_SKY_CAST, 2300);
                        events.ScheduleEvent(EVENT_ABSORB_STORM_CAST, 2300);
                        break;
                    case EVENT_DEFLECTING_WINDS:
                        me->AddAura(SPELL_DEFLECTING_WINDS, me);
                        break;
                    case EVENT_STATIC_SHOCK_PREPARE:
                        if (_shockCounter <= 2)
                        {
                            _shockReady = true;
                            _shockCounter++;
                        }
                        break;
                    case EVENT_STATIC_SHOCK_CAST:
                        if (_shockReady)
                        {
                            if (_shockCounter == 0)
                                DoCastAOE(SPELL_STATIC_SHOCK_1);
                            else if (_shockCounter == 1)
                                DoCastAOE(SPELL_STATIC_SHOCK_2);
                            else if (_shockCounter == 2)
                                DoCastAOE(SPELL_STATIC_SHOCK_3);

                            events.ScheduleEvent(EVENT_STATIC_SHOCK_PREPARE, 22000);
                            _shockReady = false;
                        }
                        break;
                    case EVENT_CALL_OF_SKY_PREPARE:
                        _minionReady = true;
                        break;
                    case EVENT_CALL_OF_SKY_CAST:
                        if (_minionReady)
                        {
                            DoCastAOE(SPELL_CALL_OF_SKY);
                            events.ScheduleEvent(EVENT_CALL_OF_SKY_PREPARE, 31000);
                            _minionReady = false;
                        }
                        break;
                    case EVENT_SUMMON_CLOUD_BURST:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            me->SummonCreature(NPC_CLOUD_BURST, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
                        events.ScheduleEvent(EVENT_SUMMON_CLOUD_BURST, 22500);
                        break;
                    case EVENT_ABSORB_STORM_PREPARE:
                        _stormReady = true;
                        break;
                    case EVENT_ABSORB_STORM_CAST:
                        if (_stormReady)
                        {
                            if (Creature* minion = me->FindNearestCreature(NPC_MINION_OF_SIAMAT, 100.0f, true))
                            {
                                DoCastAOE(SPELL_ABSORB_STORM);
                                events.ScheduleEvent(EVENT_STORM, 3000);
                                events.ScheduleEvent(EVENT_ABSORB_STORM_PREPARE, 31000);
                                _stormReady = false;
                            }
                        }
                        break;
                    case EVENT_STORM:
                        me->AddAura(SPELL_GATHERED_STORM_AURA, me);
                        break;
                    default:
                        break;
                }
            }
        }
        private:
            bool _introDone;
            bool _shockReady;
            bool _minionReady;
            bool _stormReady;
            uint8 _servantCounter;
            uint8 _shockCounter;
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_siamatAI(creature);
    }
};

class npc_lct_servant_of_siamat : public CreatureScript
{
    public:
        npc_lct_servant_of_siamat() :  CreatureScript("npc_lct_servant_of_siamat") { }

        struct npc_lct_servant_of_siamatAI : public ScriptedAI
        {
            npc_lct_servant_of_siamatAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
                _charged = true;
            }

            void EnterCombat(Unit* /*who*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_LIGHTNING_NOVA, 17000);
                events.ScheduleEvent(EVENT_THUNDER_CRASH, 10000);
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (!summoner->isInCombat())
                {
                    me->DespawnOrUnsummon(1);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                }
            }

            void EnterEvadeMode()
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->DespawnOrUnsummon(1);
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->DespawnOrUnsummon(5000);
                if (Creature* siamat = me->FindNearestCreature(BOSS_SIAMAT, 500.0f, true))
                    siamat->AI()->DoAction(ACTION_SERVANT_KILLED);
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                if (me->HealthBelowPct(4) && _charged && IsHeroic() && !me->HasUnitState(UNIT_STATE_CASTING))
                {
                    DoCastAOE(SPELL_LIGHTNING_CHARGE);
                    _charged = false;

                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_LIGHTNING_NOVA:
                            DoCastAOE(SPELL_LIGHTNING_NOVA);
                            events.ScheduleEvent(EVENT_LIGHTNING_NOVA, 22250);
                            break;
                        case EVENT_THUNDER_CRASH:
                            DoCastVictim(SPELL_THUNDER_CRASH);
                            events.ScheduleEvent(EVENT_THUNDER_CRASH, 23000);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            EventMap events;
            InstanceScript* instance;
            bool _charged;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_servant_of_siamatAI(creature);
        }
};

class npc_lct_minion_of_siamat : public CreatureScript
{
    public:
        npc_lct_minion_of_siamat() :  CreatureScript("npc_lct_minion_of_siamat") { }

        struct npc_lct_minion_of_siamatAI : public ScriptedAI
        {
            npc_lct_minion_of_siamatAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
                _tempest = true;
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 3500);
            }

            void IsSummonedBy(Unit* summoner)
            {
                _tempest = true;
                DoCast(me, SPELL_DEPLETION);
                if (!summoner->isInCombat())
                    me->DespawnOrUnsummon(1);
            }

            void EnterEvadeMode()
            {
                me->DespawnOrUnsummon(1);
            }

            void JustDied(Unit* /*killer*/)
            {
                me->DespawnOrUnsummon(5000);
            }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_ABSORB_STORM)
                    me->DespawnOrUnsummon(3100);
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                if (me->HealthBelowPct(6) && _tempest)
                {
                    me->CastStop();
                    me->RemoveAllAuras();
                    DoCastAOE(SPELL_TEMPEST_STORM);
                    DoCastAOE(SPELL_TRANSFORM);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    events.CancelEvent(EVENT_CHAIN_LIGHTNING);
                    events.ScheduleEvent(EVENT_MOVE_ARROUND, 4000);
                    _tempest = false;
                }

                if (damage >= me->GetHealth())
                    damage = me->GetHealth() - 1;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_CHAIN_LIGHTNING:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_CHAIN_LIGHTNING);
                            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 2500);
                            break;
                        case EVENT_MOVE_ARROUND:
                            if (!me->HasAura(SPELL_TEMPEST_STORM_AURA))
                                DoCastAOE(SPELL_TEMPEST_STORM_AURA);
                            me->GetMotionMaster()->MoveRandom(20.0f);
                            events.ScheduleEvent(EVENT_MOVE_ARROUND, 5000);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            EventMap events;
            InstanceScript* instance;
            bool _tempest;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_minion_of_siamatAI(creature);
        }
};

class npc_lct_cloud_burst : public CreatureScript
{
    public:
        npc_lct_cloud_burst() :  CreatureScript("npc_lct_cloud_burst") { }

        struct npc_lct_cloud_burstAI : public ScriptedAI
        {
            npc_lct_cloud_burstAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (!summoner->isInCombat())
                    me->DespawnOrUnsummon(1);
                else
                {
                    DoCastAOE(SPELL_CLOUDBURST);
                    events.ScheduleEvent(EVENT_KNOCKBACK, 5000);
                }
                me->DespawnOrUnsummon(8100);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_KNOCKBACK:
                            DoCastAOE(SPELL_CLOUDBURST_KNOCKBACK);
                            events.ScheduleEvent(EVENT_KNOCKBACK, 2000);
                            break;
                        default:
                            break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_cloud_burstAI(creature);
        }
};

class npc_lct_slipstream : public CreatureScript
{
    public:
        npc_lct_slipstream() :  CreatureScript("npc_lct_slipstream") { }

        struct npc_lct_slipstreamAI : public ScriptedAI
        {
            npc_lct_slipstreamAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            EventMap events;
            InstanceScript* instance;
            Unit* player;

            void InitializeAI()
            {
                if (me->GetEntry() != 48097)
                    me->SetPhaseMask(2, true);

                if (me->GetEntry() != NPC_WIND_TUNNEL_LANDING_ZONE)
                    events.ScheduleEvent(EVENT_CHECK_BOSSES, 1000);

                me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SLIPSTREAM, true);
            }

            void PassengerBoarded(Unit* passenger, int8 /*SeatId*/, bool /*apply*/)
            {
                if (me->GetEntry() == NPC_WIND_TUNNEL)
                {
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    events.ScheduleEvent(EVENT_THROW_PLAYER, 1000);
                }
                else
                    events.ScheduleEvent(EVENT_DROP_PLAYER, 1000);
                player = passenger;
            }

            void UpdateAI(uint32 diff)
            {

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_CHECK_BOSSES:
                            if (instance->GetBossState(DATA_GENERAL_HUSAM) == DONE && instance->GetBossState(DATA_LOCKMAW) == DONE && instance->GetBossState(DATA_HIGH_PROPHET_BARIM) == DONE)
                                events.ScheduleEvent(EVENT_ENABLE_STREAM, 4000);
                            else if (instance->GetBossState(DATA_SIAMAT) == IN_PROGRESS)
                            {
                                me->SetPhaseMask(2, true);
                            }
                            events.ScheduleEvent(EVENT_CHECK_BOSSES, 1000);
                            break;
                        case EVENT_ENABLE_STREAM:
                            DoCast(me, SPELL_WIND_TUNNEL);
                            me->SetPhaseMask(1, true);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            break;
                        case EVENT_THROW_PLAYER:
                            me->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE);
                            player->CastSpell(player, SPELL_SLIPSTREAM_TRIGGERED);
                            player->CastSpell(player, SPELL_SLIPSTREAM_DUMMY);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            break;
                        case EVENT_DROP_PLAYER:
                            me->RemoveAllAuras();
                            player->RemoveAurasDueToSpell(SPELL_SLIPSTREAM_TRIGGERED);
                            player->RemoveAurasDueToSpell(SPELL_SLIPSTREAM_DUMMY);
                            break;
                        default:
                            break;
                    }
                }

            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_slipstreamAI(creature);
        }
};

class spell_lct_wailing_winds : public SpellScriptLoader
{
    public:
        spell_lct_wailing_winds() : SpellScriptLoader("spell_lct_wailing_winds") { }

        class spell_lct_wailing_winds_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lct_wailing_winds_AuraScript);

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_WAILING_WINDS_DAMAGE, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_lct_wailing_winds_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lct_wailing_winds_AuraScript();
        }
};

class spell_lct_wailing_winds_knockback : public SpellScriptLoader
{
public:
    spell_lct_wailing_winds_knockback() : SpellScriptLoader("spell_lct_wailing_winds_knockback") { }

    class spell_lct_wailing_winds_knockback_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_lct_wailing_winds_knockback_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* knocker = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->KnockbackFrom(knocker->GetPositionX(), knocker->GetPositionY(), frand(3.0f, 7.0f), 20.0f);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_lct_wailing_winds_knockback_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_lct_wailing_winds_knockback_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_lct_wailing_winds_knockback_SpellScript();
    }
};

class spell_lct_thunder_crash : public SpellScriptLoader
{
    public:
        spell_lct_thunder_crash() : SpellScriptLoader("spell_lct_thunder_crash") { }

        class spell_lct_thunder_crash_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lct_thunder_crash_AuraScript)

            void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetCaster()->CastSpell(GetCaster()->getVictim(), GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_lct_thunder_crash_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lct_thunder_crash_AuraScript();
        }
};

void AddSC_boss_siamat()
{
    new boss_siamat();
    new npc_lct_servant_of_siamat();
    new npc_lct_minion_of_siamat();
    new npc_lct_cloud_burst();
    new npc_lct_slipstream();
    new spell_lct_wailing_winds();
    new spell_lct_wailing_winds_knockback();
    new spell_lct_thunder_crash();
}
