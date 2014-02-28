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

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_PHASE_2 = 1,
    SAY_SLAY    = 2,
    SAY_DEATH   = 3,
};

enum Spells
{
    // Barim
    SPELL_HEAVENS_FURY_SUMMON           = 81939,

    SPELL_SUMMON_BLAZE_OF_THE_HEAVENS   = 91180,
    SPELL_SUMMON_BLAZE_DUMMY            = 91181,

    SPELL_FIFTY_LASHINGS                = 82506,

    // Heavens Fury
    SPELL_HEAVENS_FURY_VISUAL           = 81940,
    SPELL_HEAVENS_FURY_AURA             = 81941,

    // Blaze of the Heaven
    SPELL_BLAZE_SUMMON_VISUAL           = 91179,
    SPELL_BLAZE_OF_THE_HEAVENS          = 95248,
    SPELL_SUMMON_BLAZE_FIRE_DUMMY       = 91185,
    SPELL_BLAZE_FIRE_AURA               = 91195,
};

enum Events
{
    EVENT_SUMMON_BLAZE_OF_THE_HEAVENS = 1,
    EVENT_FIFTY_LASHINGS,
    EVENT_PLAGUE_OF_AGES,
    EVENT_HEAVENS_FURY,

    EVENT_REPENTANCE_CAST,
    EVENT_REPENTANCE_PULL,
    EVENT_REPENTANCE_KNOCKBACK,
};

class boss_high_prophet_barim : public CreatureScript
{
public:
    boss_high_prophet_barim() : CreatureScript("boss_high_prophet_barim") { }

    struct boss_high_prophet_barimAI : public BossAI
    {
        boss_high_prophet_barimAI(Creature* creature) : BossAI(creature, DATA_HIGH_PROPHET_BARIM)
        {
        }

        void Reset()
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_HEAVENS_FURY, 8000);
            events.ScheduleEvent(EVENT_FIFTY_LASHINGS, 9500);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
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
                    case EVENT_HEAVENS_FURY:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_HEAVENS_FURY_SUMMON);
                        events.ScheduleEvent(EVENT_HEAVENS_FURY, 75000);
                        break;
                    case EVENT_FIFTY_LASHINGS:
                        DoCastAOE(SPELL_FIFTY_LASHINGS);
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
        return new boss_high_prophet_barimAI(creature);
    }
};

class npc_lct_heavens_fury : public CreatureScript
{
    public:
        npc_lct_heavens_fury() :  CreatureScript("npc_lct_heavens_fury") { }

        struct npc_lct_heavens_furyAI : public ScriptedAI
        {
            npc_lct_heavens_furyAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetReactState(REACT_PASSIVE);
                SetCombatMovement(false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                DoCastAOE(SPELL_HEAVENS_FURY_VISUAL);
                DoCastAOE(SPELL_HEAVENS_FURY_AURA);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_heavens_furyAI(creature);
        }
};

class spell_lct_fifty_lashings : public SpellScriptLoader
{
    public:
        spell_lct_fifty_lashings() : SpellScriptLoader("spell_lct_fifty_lashings") { }

    private:
        class spell_lct_fifty_lashings_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lct_fifty_lashings_AuraScript)

            void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetCaster()->CastSpell(GetCaster()->getVictim(), GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_lct_fifty_lashings_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lct_fifty_lashings_AuraScript();
        }
};

void AddSC_boss_high_prophet_barim()
{
    new boss_high_prophet_barim();
    new npc_lct_heavens_fury();
    new spell_lct_fifty_lashings();
}
