
#include "halls_of_origination.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellMgr.h"
#include "LFGMgr.h"
#include "Player.h"
#include "Group.h"
#include "SpellInfo.h"

enum Spells
{
    // Rajh
    SPELL_SUN_STRIKE                = 73872,
    SPELL_SUMMON_SOLAR_WINDS        = 74104,
    SPELL_SUMMON_SUN_ORB            = 80352,
    SPELL_BLESSING_OF_THE_SUN       = 76352,
    SPELL_SUMMON_INFERNO_LEAP       = 87650,

    // Solar Winds
    SPELL_SOLAR_WINDS_PERIODIC      = 74107,

    // Inferno Leap
    SPELL_INFERNO_LEAP              = 87653,
    SPELL_INFERNO_LEAP_EXPLOSION    = 87647,

    // Sun Orb
    SPELL_SUN_LEAP                  = 82856,
    SPELL_SUMMON_METEORITE          = 76375,
    SPELL_RIDE_VEHICLE              = 43671, // hits blazing inferno

    // Blazing Inferno
    SPELL_BLAZING_INFERNO          = 76195, // Hit orb of the sun
};

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_BLESSING_OF_THE_SUN = 1,
    SAY_SLAY                = 2,
    SAY_DEATH               = 3,
};

enum Events
{
    // Rajh
    EVENT_SUN_STRIKE = 1,
    EVENT_SUMMON_SOLAR_WINDS_1,
    EVENT_SUMMON_SOLAR_WINDS_2,
    EVENT_MOVE_TO_CENTER,
    EVENT_BLESSING_OF_THE_SUN,
    EVENT_TALK_BLESSING_OF_THE_SUN,
    EVENT_SUMMON_SUN_ORB,
    EVENT_APPLY_IMMUNITY,
    EVENT_INFERNO_LEAP,

    // Inferno Leap
    EVENT_LEAP_EXPLOSION,

    // Solar Winds
    EVENT_MOVE_ARROUND,

    //Sun Orb
    EVENT_LEAP,
};

enum Actions
{
    ACTION_BLESSING_DONE = 1,
};

enum Points
{
    POINT_CENTER    = 1,
    POINT_UP        = 2,
    POINT_SUN_EXP   = 3,
};

enum AchievementData
{
    DATA_SUN_OF_A = 1,
};

Position const CenterPos = {-318.5936f, 192.8621f, 343.9443f};

class boss_rajh : public CreatureScript
{
public:
    boss_rajh() : CreatureScript("boss_rajh") { }

    struct boss_rajhAI : public BossAI
    {
        boss_rajhAI(Creature* creature) : BossAI(creature, DATA_RAJH)
        {
            _achievement = true;
            _energized   = true;
        }

        bool _achievement;
        bool _energized;

        void Reset()
        {
            _Reset();
            _achievement = true;
            _energized = true;
            me->SetPower(POWER_ENERGY, 100);
            MakeInterruptable(false);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            me->SetPower(POWER_ENERGY, 100);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_SUN_STRIKE, 20000);
            events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 9800);
            events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);
            events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS_1, 5800);

        }

        void JustDied(Unit* /*who*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            _FinishDungeon();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            summons.DespawnAll();
            Reset();
            MakeInterruptable(false);
        }

        uint32 GetData(uint32 type) const
        {
            return type == DATA_SUN_OF_A ? _achievement : 0;
        }

        void JustSummoned(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_SOLAR_WINDS_FACING:
                    me->SetFacingToObject(summon);
                    events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS_2, 1);
                    summons.Summon(summon);
                    break;
                case NPC_SOLAR_WINDS:
                case NPC_SOLAR_FIRE:
                case NPC_ORB_OF_THE_SUN:
                case NPC_INFERNO_LEAP:
                    summons.Summon(summon);
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case POINT_CENTER:
                    events.ScheduleEvent(EVENT_BLESSING_OF_THE_SUN, 1);
                    break;
                default:
                    break;
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
                case ACTION_BLESSING_DONE:
                    _energized = true;
                    _achievement = false;
                    me->GetMotionMaster()->MovementExpired();
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_SUN_STRIKE, 20000);
                    events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);
                    events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 9800);
                    events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS_1, 5800);
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
                    case EVENT_SUN_STRIKE:
                        DoCastVictim(SPELL_SUN_STRIKE);
                        events.ScheduleEvent(EVENT_SUN_STRIKE, 28000);
                        events.ScheduleEvent(EVENT_MOVE_TO_CENTER, 500);
                        break;
                    case EVENT_SUMMON_SOLAR_WINDS_1:
                        DoCastVictim(SPELL_SUMMON_SOLAR_WINDS);
                        events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS_1, 28000);
                        break;
                    case EVENT_SUMMON_SOLAR_WINDS_2:
                    {
                        float x = me->GetPositionX();
                        float y = me->GetPositionY();
                        float z = me->GetPositionZ();
                        float ori = me->GetOrientation();
                        float dist = me->GetFloatValue(UNIT_FIELD_COMBATREACH);
                        me->SummonCreature(NPC_SOLAR_WINDS, x + cos(ori) * dist, y + sin(ori) * dist, z, ori, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    }
                    case EVENT_BLESSING_OF_THE_SUN:
                        DoCast(SPELL_BLESSING_OF_THE_SUN);
                        events.ScheduleEvent(EVENT_TALK_BLESSING_OF_THE_SUN, 1500);
                        break;
                    case EVENT_TALK_BLESSING_OF_THE_SUN:
                        Talk(SAY_BLESSING_OF_THE_SUN);
                        break;
                    case EVENT_SUMMON_SUN_ORB:
                        me->GetMotionMaster()->MovementExpired();
                        MakeInterruptable(true);
                        DoCast(SPELL_SUMMON_SUN_ORB);
                        events.ScheduleEvent(EVENT_MOVE_TO_CENTER, 3500);
                        events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 3000);
                        break;
                    case EVENT_INFERNO_LEAP:
                        me->GetMotionMaster()->MovementExpired();
                        MakeInterruptable(true);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_SUMMON_INFERNO_LEAP);
                        DoCastAOE(SPELL_INFERNO_LEAP);
                        events.ScheduleEvent(EVENT_MOVE_TO_CENTER, 4000);
                        events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 1500);
                        events.ScheduleEvent(EVENT_INFERNO_LEAP, 28000);
                        break;
                    case EVENT_APPLY_IMMUNITY:
                        MakeInterruptable(false);
                        break;
                    case EVENT_MOVE_TO_CENTER:
                        if (me->GetPower(POWER_ENERGY) <= 10 && _energized)
                        {
                            me->SetPower(POWER_ENERGY, 0);
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            events.Reset();
                            me->GetMotionMaster()->MovePoint(POINT_CENTER, CenterPos);
                            _energized = false;
                        }
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
        return new boss_rajhAI(creature);
    }
};

class npc_solar_winds : public CreatureScript
{
public:
    npc_solar_winds() : CreatureScript("npc_solar_winds") { }

    struct npc_solar_windsAI : public ScriptedAI
    {
        npc_solar_windsAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;
        Creature* rajh;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetWalk(true);
            rajh = summoner->ToCreature();
            events.ScheduleEvent(EVENT_MOVE_ARROUND, 3500);
        }

        void JustSummoned(Creature* summon)
        {
            rajh->AI()->JustSummoned(summon);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_ARROUND:
                        if (!me->HasAura(SPELL_SOLAR_WINDS_PERIODIC))
                            DoCast(SPELL_SOLAR_WINDS_PERIODIC);
                        me->GetMotionMaster()->MoveRandom(50.0f);
                        events.ScheduleEvent(EVENT_MOVE_ARROUND, 10000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_solar_windsAI(creature);
    }
};

class npc_orb_of_the_sun : public CreatureScript
{
public:
    npc_orb_of_the_sun() : CreatureScript("npc_orb_of_the_sun") { }

    struct npc_orb_of_the_sunAI : public ScriptedAI
    {
        npc_orb_of_the_sunAI(Creature* creature) : ScriptedAI(creature) 
        {
            event_time = 0;
        }

        EventMap events;
        uint32 event_time;

        void IsSummonedBy(Unit* summoner)
        {
            summoner->ToCreature()->AI()->JustSummoned(me);
            me->GetMotionMaster()->MovePoint(POINT_UP, me->GetPositionX(), me->GetPositionY(), 370.448f, false);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_SUMMON_METEORITE)
            {
                event_time = me->GetExactDist2d(target->GetPositionX(), target->GetPositionY()) * 20;
                if (Creature* inferno = me->SummonCreature(NPC_BLAZING_INFERNO, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000))
                    DoCast(inferno, SPELL_RIDE_VEHICLE);
            }
            else if (spell->Id == SPELL_RIDE_VEHICLE)
                target->CastWithDelay(event_time, me, SPELL_BLAZING_INFERNO);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_UP:
                    events.ScheduleEvent(EVENT_LEAP, 5000);
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
                    case EVENT_LEAP:
                        DoCast(SPELL_SUMMON_METEORITE);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_orb_of_the_sunAI(creature);
    }
};

class npc_inferno_leap : public CreatureScript
{
public:
    npc_inferno_leap() : CreatureScript("npc_inferno_leap") { }

    struct npc_inferno_leapAI : public ScriptedAI
    {
        npc_inferno_leapAI(Creature* creature) : ScriptedAI(creature) 
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        Creature* rajh;

        void IsSummonedBy(Unit* summoner)
        {
            summoner->ToCreature()->AI()->JustSummoned(me);
            rajh = summoner->ToCreature();
            events.ScheduleEvent(EVENT_LEAP_EXPLOSION, 1450);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LEAP_EXPLOSION:
                        if (rajh->HasUnitState(UNIT_STATE_CASTING))
                            me->CastWithDelay(1000, me, SPELL_INFERNO_LEAP_EXPLOSION);
                        me->DespawnOrUnsummon(1500);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_inferno_leapAI(creature);
    }
};

class spell_blessing_of_the_sun : public SpellScriptLoader
{
public:
    spell_blessing_of_the_sun() : SpellScriptLoader("spell_blessing_of_the_sun") { }

    class spell_blessing_of_the_sun_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_blessing_of_the_sun_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->SetFacingTo(3.124139f);
                caster->SetUInt32Value(UNIT_NPC_EMOTESTATE, 474);
            }
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                caster->ToCreature()->AI()->DoAction(ACTION_BLESSING_DONE);
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_blessing_of_the_sun_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_blessing_of_the_sun_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_blessing_of_the_sun_AuraScript();
    }
};

class spell_summon_meteorite_aoe : public SpellScriptLoader
{
public:
    spell_summon_meteorite_aoe() : SpellScriptLoader("spell_summon_meteorite_aoe") { }

    class spell_summon_meteorite_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_summon_meteorite_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_summon_meteorite_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_summon_meteorite_aoe_SpellScript();
    }
};

class achievement_sun_of_a : public AchievementCriteriaScript
{
    public:
        achievement_sun_of_a() : AchievementCriteriaScript("achievement_sun_of_a") { }

        bool OnCheck(Player* /*source*/, Unit* target)
        {
            if (!target)
                return false;

            if (target->GetMap()->IsHeroic())
                return target->GetAI()->GetData(DATA_SUN_OF_A);

            return false;
        }
};

void AddSC_boss_rajh()
{
    new boss_rajh();
    new npc_solar_winds();
    new npc_orb_of_the_sun();
    new npc_inferno_leap();
    new spell_blessing_of_the_sun();
    new spell_summon_meteorite_aoe();
    new achievement_sun_of_a();
}
