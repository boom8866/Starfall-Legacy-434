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
    SPELL_STORM_BOLT            = 73564,
    SPELL_DEFLECTING_WINDS      = 84589,
    SPELL_STATIC_SHOCK_1        = 84546,
    SPELL_STATIC_SHOCK_2        = 84555,
    SPELL_STATIC_SHOCK_3        = 84556,
    SPELL_WAILING_WINDS         = 83066,
    SPELL_WAILING_WINDS_DAMAGE  = 83094,

    // Generic
    SPELL_WEATHER_RAIN          = 82651,

    // Wind Tunnel
    SPELL_WIND_TUNNEL           = 89698,
    SPELL_RIDE_VEHICLE          = 93970,
    SPELL_SLIPSTREAM            = 85016,
    SPELL_SLIPSTREAM_TRIGGERED  = 85017,
    SPELL_SLIPSTREAM_DUMMY      = 85063,
};

enum Events
{
    // Siamat
    EVENT_STORM_BOLT = 1,
    EVENT_DEFLECTING_WINDS,
    EVENT_STATIC_SHOCK_PREPARE,
    EVENT_STATIC_SHOCK_CAST,


    // Slipstream
    EVENT_CHECK_BOSSES,
    EVENT_ENABLE_STREAM,
    EVENT_THROW_PLAYER,
    EVENT_DROP_PLAYER,
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
            _servantCounter = 0;
            _shockCounter = 0;
        }

        bool _introDone;
        bool _shockReady;
        uint8 _servantCounter;
        uint8 _shockCounter;

        void Reset()
        {
            _Reset();
            _introDone = false;
            _shockReady = true;
            _servantCounter = 0;
            _shockCounter = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            TalkToMap(SAY_AGGRO);
            _EnterCombat();
            events.ScheduleEvent(EVENT_STATIC_SHOCK_CAST, 200);
            events.ScheduleEvent(EVENT_STORM_BOLT, 500);
            events.ScheduleEvent(EVENT_DEFLECTING_WINDS, 6000);
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
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            _servantCounter = 0;
            _shockCounter = 0;
            _shockReady = true;
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
                        me->CastStop();
                        me->RemoveAurasDueToSpell(SPELL_DEFLECTING_WINDS);
                        DoCastAOE(SPELL_WAILING_WINDS);
                        events.RescheduleEvent(EVENT_STORM_BOLT, 18000);
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
                            DoCast(target, SPELL_STORM_BOLT);
                        events.ScheduleEvent(EVENT_STORM_BOLT, 2500);
                        events.ScheduleEvent(EVENT_STATIC_SHOCK_CAST, 2300);
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
                    default:
                        break;
                }
            }
        }
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
            }

            EventMap events;
            InstanceScript* instance;

            void EnterCombat(Unit* /*who*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
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

            void UpdateAI(uint32 diff)
            {
                if (UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case 0:
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_servant_of_siamatAI(creature);
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
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveAllAuras();

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
                                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                me->RemoveAllAuras();
                            }
                            events.ScheduleEvent(EVENT_CHECK_BOSSES, 1000);
                            break;
                        case EVENT_ENABLE_STREAM:
                            DoCast(me, SPELL_WIND_TUNNEL);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
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
                GetCaster()->CastSpell(GetCaster(), SPELL_WAILING_WINDS_DAMAGE, false);
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

class spell_lct_wailing_winds_jump : public SpellScriptLoader
{
    public:
        spell_lct_wailing_winds_jump() : SpellScriptLoader("spell_lct_wailing_winds_jump") { }

        class spell_lct_wailing_winds_jump_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lct_wailing_winds_jump_SpellScript);

            void EffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    float x = target->GetPositionX();
                    float y = target->GetPositionY();
                    GetCaster()->GetMotionMaster()->MoveKnockbackFrom(x, y, 19.2911f, 6.0f);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_lct_wailing_winds_jump_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lct_wailing_winds_jump_SpellScript();
        }
};

void AddSC_boss_siamat()
{
    new boss_siamat();
    new npc_lct_servant_of_siamat();
    new npc_lct_slipstream();
    new spell_lct_wailing_winds();
    // new spell_lct_wailing_winds_jump();
}
