
#include "shadowfang_keep.h"
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

enum Texts
{
    SAY_AGGRO_ALLIANCE              = 0,
    SAY_AGGRO_HORDE                 = 1,
    SAY_SLAY                        = 2,
    SAY_ANNOUNCE_PISTOL_BARRAGE     = 3,
    SAY_DEATH                       = 4,
};

enum Events
{
    // Lord Godfrey
    EVENT_CURSED_BULLETS = 1,
    EVENT_MORTAL_WOUND,
    EVENT_SUMMON_BLOODTHIRSTY_GHOULS,
    EVENT_PISTOL_BARRAGE,
    EVENT_PISTOL_BARRAGE_CAST,

    // Bloodthirsty Ghoul
    EVENT_ATTACK,
};

enum Spells
{
    SPELL_CURSED_BULLESTS                           = 93629,
    SPELL_MORTAL_WOUND                              = 93675,
    SPELL_SUMMON_BLOODTHIRSTY_GHOULS_AURA           = 93707,
    SPELL_SUMMON_BLOODTHIRSTY_GHOULS_TRIGGERED_1    = 93709,
    SPELL_SUMMON_BLOODTHIRSTY_GHOULS_TRIGGERED_2    = 93714,

    SPELL_PISTOL_BARRAGE_FORCE_CAST                 = 96344,
    SPELL_PISTOL_BARRAGE_CAST                       = 93520,

    SPELL_PISTOL_BARRAGE_TRIGGER_1                  = 93566,
    SPELL_PISTOL_BARRAGE_TRIGGER_2                  = 93558,
};

class boss_lord_godfrey : public CreatureScript
{
public:
    boss_lord_godfrey() : CreatureScript("boss_lord_godfrey") { }

    struct boss_lord_godfreyAI : public BossAI
    {
        boss_lord_godfreyAI(Creature* creature) : BossAI(creature, DATA_LORD_GODFREY)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (Player* player = me->FindNearestPlayer(200.0f, true))
            {
                if (instance->GetData(DATA_TEAM_IN_INSTANCE) == TEAM_ALLIANCE)
                    Talk(SAY_AGGRO_ALLIANCE);
                else
                    Talk(SAY_AGGRO_HORDE);
            }
            _EnterCombat();
            me->ApplySpellImmune(0, IMMUNITY_ID, 93564, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 93784, true);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_CURSED_BULLETS, 10800);
            events.ScheduleEvent(EVENT_MORTAL_WOUND, 3500);
            events.ScheduleEvent(EVENT_SUMMON_BLOODTHIRSTY_GHOULS, 6000);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_PISTOL_BARRAGE, 12500);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void KilledUnit(Unit* target)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            summons.DespawnAll();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _DespawnAtEvade();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case 0:
                    break;
                default:
                    summons.Summon(summon);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (me->HasAura(SPELL_PISTOL_BARRAGE_TRIGGER_2))
                return;

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CURSED_BULLETS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_CURSED_BULLESTS);
                        events.ScheduleEvent(EVENT_CURSED_BULLETS, 12000);
                        break;
                    case EVENT_MORTAL_WOUND:
                        DoCastVictim(SPELL_MORTAL_WOUND);
                        events.ScheduleEvent(EVENT_MORTAL_WOUND, 6000);
                        break;
                    case EVENT_SUMMON_BLOODTHIRSTY_GHOULS:
                        DoCastAOE(SPELL_SUMMON_BLOODTHIRSTY_GHOULS_AURA, true);
                        events.ScheduleEvent(EVENT_SUMMON_BLOODTHIRSTY_GHOULS, 30000);
                        break;
                    case EVENT_PISTOL_BARRAGE:
                        me->AttackStop();
                        me->ToCreature()->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        DoCastAOE(SPELL_PISTOL_BARRAGE_FORCE_CAST);
                        events.ScheduleEvent(EVENT_PISTOL_BARRAGE_CAST, 500);
                        break;
                    case EVENT_PISTOL_BARRAGE_CAST:
                        if (Creature* target = me->FindNearestCreature(NPC_PISTOL_BARRAGE_DUMMY, 500.0f, true))
                        {
                            Talk(SAY_ANNOUNCE_PISTOL_BARRAGE);
                            me->SetFacingToObject(target);
                            DoCastAOE(SPELL_PISTOL_BARRAGE_CAST);
                        }
                        events.ScheduleEvent(EVENT_PISTOL_BARRAGE, 30100);
                        break;
                    default:
                        break;
                }
            }
            if (!me->HasUnitState(UNIT_STATE_CASTING) && !me->HasAura(SPELL_PISTOL_BARRAGE_TRIGGER_2))
                DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_lord_godfreyAI (creature);
    }
};

class npc_sfk_bloodthirsty_ghoul : public CreatureScript
{
public:
    npc_sfk_bloodthirsty_ghoul() :  CreatureScript("npc_sfk_bloodthirsty_ghoul") { }

    struct npc_sfk_bloodthirsty_ghoulAI : public ScriptedAI
    {
        npc_sfk_bloodthirsty_ghoulAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
            DoZoneInCombat();
            events.ScheduleEvent(EVENT_ATTACK, 5000);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        if (Creature* godfrey = me->FindNearestCreature(BOSS_LORD_GODFREY, 200.0f, true))
                            me->GetMotionMaster()->MovePoint(0, godfrey->GetPositionX(), godfrey->GetPositionY(), godfrey->GetPositionZ(), true);
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
        return new npc_sfk_bloodthirsty_ghoulAI(creature);
    }
};

class spell_sfk_summon_bloodthirsty_ghouls : public SpellScriptLoader
{
public:
    spell_sfk_summon_bloodthirsty_ghouls() : SpellScriptLoader("spell_sfk_summon_bloodthirsty_ghouls") { }

    class spell_sfk_summon_bloodthirsty_ghouls_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sfk_summon_bloodthirsty_ghouls_AuraScript);

        void OnPeriodic(AuraEffect const* /*aurEff*/)
        {
            switch (urand(0, 1))
            {
                case 0:
                    GetCaster()->CastSpell((Unit*)NULL, SPELL_SUMMON_BLOODTHIRSTY_GHOULS_TRIGGERED_1, true);
                    break;
                case 1:
                    GetCaster()->CastSpell((Unit*)NULL, SPELL_SUMMON_BLOODTHIRSTY_GHOULS_TRIGGERED_2, true);
                    break;
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sfk_summon_bloodthirsty_ghouls_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sfk_summon_bloodthirsty_ghouls_AuraScript();
    }
};

class spell_sfk_pistol_barrage : public SpellScriptLoader
{
public:
    spell_sfk_pistol_barrage() : SpellScriptLoader("spell_sfk_pistol_barrage") { }

    class spell_sfk_pistol_barrage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sfk_pistol_barrage_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                caster->AddAura(SPELL_PISTOL_BARRAGE_TRIGGER_1, caster);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                caster->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                caster->RemoveAurasDueToSpell(SPELL_PISTOL_BARRAGE_TRIGGER_1);
            }
        }

        void OnPeriodic(AuraEffect const* /*aurEff*/)
        {
            if (Unit* caster = GetCaster())
            {
                float ori = caster->GetOrientation();
                float posX = caster->GetPositionX() + cos(ori + frand(-0.499f, 0.499f)) * 200;
                float posY = caster->GetPositionY() + sin(ori + frand(-0.499f, 0.499f)) * 200;
                float posZ = caster->GetPositionZ();
                GetCaster()->CastSpell(posX, posY, posZ, SPELL_PISTOL_BARRAGE_TRIGGER_2, true);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_sfk_pistol_barrage_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_sfk_pistol_barrage_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sfk_pistol_barrage_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sfk_pistol_barrage_AuraScript();
    }
};

void AddSC_boss_lord_godfrey()
{
    new boss_lord_godfrey();
    new npc_sfk_bloodthirsty_ghoul();
    new spell_sfk_summon_bloodthirsty_ghouls();
    new spell_sfk_pistol_barrage();
}
