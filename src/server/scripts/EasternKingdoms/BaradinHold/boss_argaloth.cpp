/*
* Copyright (C) 2011-2013 Devastion Cataclysm <http://www.cataclysm-wow.eu/>
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

#include"ScriptPCH.h"
#include"baradin_hold.h"

enum Spells
{
    SPELL_BERSERK               = 47008,
    SPELL_CONSUMING_DARKNESS    = 88954,
    SPELL_METEOR_SLASH          = 88942,
    SPELL_FEL_FIRESTORM         = 88972,
};

enum Events
{
    EVENT_BERSERK               = 1,
    EVENT_CONSUMING_DARKNESS    = 2,
    EVENT_METEOR_SLASH          = 3,
};

class boss_argaloth: public CreatureScript
{
public:
    boss_argaloth() : CreatureScript("boss_argaloth") { }

    struct boss_argalothAI: public BossAI
    {
        boss_argalothAI(Creature* creature) : BossAI(creature, DATA_ARGALOTH) { }

        uint8 FirestormCount;

        void Reset()
        {
            _Reset();
            FirestormCount = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            FirestormCount = 0;
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_BERSERK, 300000);
            events.ScheduleEvent(EVENT_CONSUMING_DARKNESS, 14000);
            events.ScheduleEvent(EVENT_METEOR_SLASH, 10000);
        }

        void JustDied(Unit* /*who*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void JustRespawned()
        {
            instance->SetBossState(DATA_ARGALOTH, NOT_STARTED);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            events.Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_ARGALOTH, FAIL);
            me->GetMotionMaster()->MoveTargetedHome();
            _DespawnAtEvade();
        }

        void DamageTaken(Unit* /*damager*/, uint32& damage)
        {
            if (me->GetHealthPct() < 66 && FirestormCount == 0)
            {
                DoCastAOE(SPELL_FEL_FIRESTORM);
                events.DelayEvents(3000);
                FirestormCount++;
            }

            if (me->GetHealthPct() < 33 && FirestormCount == 1)
            {
                DoCastVictim(SPELL_FEL_FIRESTORM);
                events.DelayEvents(3000);
                FirestormCount++;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CONSUMING_DARKNESS:
                        CastCunsumingDarkness();
                        events.RescheduleEvent(EVENT_CONSUMING_DARKNESS, 22000);
                        break;
                    case EVENT_METEOR_SLASH:
                        DoCast(SPELL_METEOR_SLASH);
                        events.RescheduleEvent(EVENT_METEOR_SLASH, 15000);
                        break;
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void CastCunsumingDarkness()
        {
            std::list<Player*> playerList = me->GetNearestPlayersList(200.f, true);

            // Try to select a Target for Consuming Darkness without the Spell
            for (uint8 i = me->GetMap()->Is25ManRaid() ? 8 : 3 ; i > 0; i--)
            {
                if (playerList.empty())
                    return;

                std::list<Player*>::iterator itr = playerList.begin();
                std::advance(itr, urand(0, playerList.size()-1));

                me->AddAura(SPELL_CONSUMING_DARKNESS, *itr);
                playerList.erase(itr);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_argalothAI(creature);
    }
};

// 88954 / 95173 - Consuming Darkness
class spell_argaloth_consuming_darkness : public SpellScriptLoader
{
    public:
        spell_argaloth_consuming_darkness() : SpellScriptLoader("spell_argaloth_consuming_darkness") { }

        class spell_argaloth_consuming_darkness_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_argaloth_consuming_darkness_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 8 : 3);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_argaloth_consuming_darkness_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_argaloth_consuming_darkness_SpellScript();
        }

        class spell_argaloth_consuming_darkness_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_argaloth_consuming_darkness_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                uint64 damage;
                damage = aurEff->GetBaseAmount() * aurEff->GetTickNumber();
                this->GetEffect(EFFECT_0)->ChangeAmount(damage);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_argaloth_consuming_darkness_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_argaloth_consuming_darkness_AuraScript();
        }
};

// 88942 / 95172 - Meteor Slash
class spell_argaloth_meteor_slash : public SpellScriptLoader
{
    public:
        spell_argaloth_meteor_slash() : SpellScriptLoader("spell_argaloth_meteor_slash") { }

        class spell_argaloth_meteor_slash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_argaloth_meteor_slash_SpellScript);

            bool Load()
            {
                _targetCount = 0;
                return true;
            }

            void CountTargets(std::list<WorldObject*>& targets)
            {
                _targetCount = targets.size();
            }

            void SplitDamage()
            {
                if (!_targetCount)
                    return;

                SetHitDamage(GetHitDamage() / _targetCount);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_argaloth_meteor_slash_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
                OnHit += SpellHitFn(spell_argaloth_meteor_slash_SpellScript::SplitDamage);
            }

        private:
            uint32 _targetCount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_argaloth_meteor_slash_SpellScript();
        }
};

void AddSC_boss_argaloth()
{
    new boss_argaloth();
    new spell_argaloth_consuming_darkness();
    new spell_argaloth_meteor_slash();
}
