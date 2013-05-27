/*
 * Copyright (C) 2011-2013 NorthStrider
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include"lost_city_of_the_tolvir.h"
#include "SpellScript.h"

enum Spells
{
    SPELL_SUMMON_SHOCKWAVE_DUMMY_N  = 83131,
    SPELL_SUMMON_SHOCKWAVE_DUMMY_S  = 83132,
    SPELL_SUMMON_SHOCKWAVE_DUMMY_E  = 83133,
    SPELL_SUMMON_SHOCKWAVE_DUMMY_W  = 83134,
    SPELL_SUMMON_SHOCKWAVE_VISUAL   = 83128,
    SPELL_SHOCKWAVE                 = 83445,
    SPELL_SHOCKWAVE_MISSILE         = 83130,
    SPELL_SHOCKWAVE_DAMAGE          = 83454,
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
    EVENT_SHOCKWAVE     = 1,
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
        }

        uint8 triggerCount;

        void Reset()
        {
            _Reset();
            triggerCount = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_SHOCKWAVE, 10000);
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
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
                    if (triggerCount == 1)
                        summon->SetOrientation(me->GetOrientation() * 0.50f);
                    else if (triggerCount == 2)
                        summon->SetOrientation(me->GetOrientation() * 0.25f);
                    else if (triggerCount == 3)
                        summon->SetOrientation(me->GetOrientation() * 0.75f);

                    summon->GetMotionMaster()->MovePoint(0, summon->GetPositionX()+cos(summon->GetOrientation()) * 50, summon->GetPositionY()+sin(summon->GetOrientation()) * 50, summon->GetPositionZ());
                    break;
            }
        }

        void JustDied(Unit* /*who*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
                    case EVENT_SHOCKWAVE:
                        Talk(SAY_SHOCKWAVE);
                        Talk(SAY_ANNOUNCE_SHOCKWAVE);
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_N);
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_S);
                        triggerCount++;
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_E);
                        triggerCount++;
                        DoCastAOE(SPELL_SUMMON_SHOCKWAVE_DUMMY_W);
                        triggerCount++;
                        DoCastAOE(SPELL_SHOCKWAVE);
                        triggerCount = 0;
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

class spell_general_husam_shockwave_summon : public SpellScriptLoader
{
    public:
        spell_general_husam_shockwave_summon() : SpellScriptLoader("spell_general_husam_shockwave_summon") { }

        class spell_general_husam_shockwave_summon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_general_husam_shockwave_summon_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_SUMMON_SHOCKWAVE_VISUAL, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_general_husam_shockwave_summon_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_general_husam_shockwave_summon_SpellScript();
        }
};

class spell_general_husam_shockwave : public SpellScriptLoader
{
    public:
        spell_general_husam_shockwave() : SpellScriptLoader("spell_general_husam_shockwave") { }

        class spell_general_husam_shockwave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_general_husam_shockwave_SpellScript);

            void EffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHOCKWAVE_MISSILE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_general_husam_shockwave_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_general_husam_shockwave_SpellScript();
        }
};

void AddSC_boss_general_husam()
{
    new boss_general_husam();
    new spell_general_husam_shockwave_summon();
    new spell_general_husam_shockwave();
}
