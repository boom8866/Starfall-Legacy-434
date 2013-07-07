/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
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

/*
 * Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pal_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Group.h"
#include "Object.h"

#include <list>

enum PaladinSpells
{
    SPELL_PALADIN_DIVINE_PLEA                    = 54428,
    SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF     = 67480,
    SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE = 57319,

    SPELL_PALADIN_HOLY_SHOCK_R1                  = 20473,
    SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE           = 25912,
    SPELL_PALADIN_HOLY_SHOCK_R1_HEALING          = 25914,

    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID   = 37878,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN = 37879,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST  = 37880,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN  = 37881,

    SPELL_PALADIN_DIVINE_STORM                   = 53385,
    SPELL_PALADIN_DIVINE_STORM_DUMMY             = 54171,
    SPELL_PALADIN_DIVINE_STORM_HEAL              = 54172,

    SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE          = 25997,

    SPELL_PALADIN_FORBEARANCE                    = 25771,
    SPELL_PALADIN_AVENGING_WRATH_MARKER          = 61987,
    SPELL_PALADIN_IMMUNE_SHIELD_MARKER           = 61988,

    SPELL_PALADIN_HAND_OF_SACRIFICE              = 6940,
    SPELL_PALADIN_DIVINE_SACRIFICE               = 64205,

    SPELL_PALADIN_DIVINE_PURPOSE_PROC            = 90174,

    SPELL_PALADIN_CONSECRATION_SUMMON            = 82366,
    SPELL_PALADIN_CONSECRATION_DAMAGE            = 81297,

    SPELL_PALADIN_RETRI_GUARDIAN                 = 86698,
    SPELL_PALADIN_HOLY_GUARDIAN                  = 86669,
    SPELL_PALADIN_PROT_GUARDIAN                  = 86659,
    SPELL_PALADIN_ANCIENT_CRUSADER               = 86701,
    SPELL_PALADIN_ANCIENT_CRUSADER_GUARDIAN      = 86703,
    SPELL_PALADIN_ANCIENT_POWER                  = 86700,
    SPELL_PALADIN_ANCIENT_FURY                   = 86704,
    SPELL_PALADIN_ANCIENT_HEALER                 = 86674,

    SPELL_PALADIN_GLYPH_OF_SALVATION             = 63225,

    SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT        = 31790,

    SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS          = 25742,

    SPELL_GENERIC_ARENA_DAMPENING                = 74410,
    SPELL_GENERIC_BATTLEGROUND_DAMPENING         = 74411,

    SPELL_GLYPH_OF_THE_LONG_WORD                 = 93466,
    SPELL_TALENT_ETERNAL_GLORY_R1                = 87163,
    SPELL_TALENT_ETERNAL_GLORY_R2                = 87164,
    SPELL_EFFECT_ETERNAL_GLORY                   = 88676,
};

// 31850 - Ardent Defender
class spell_pal_ardent_defender : public SpellScriptLoader
{
    public:
        spell_pal_ardent_defender() : SpellScriptLoader("spell_pal_ardent_defender") { }

        class spell_pal_ardent_defender_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_ardent_defender_AuraScript);

            uint32 absorbPct, healPct;

            enum
            {
                PAL_SPELL_ARDENT_DEFENDER_HEAL = 66235,
            };

            bool Load()
            {
                healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
                return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* victim = GetTarget();
                int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();

                if (remainingHealth > 0)
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
                else if (!victim->ToPlayer()->HasSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL))
                {
                    // Cast healing spell, completely avoid damage
                    absorbAmount = dmgInfo.GetDamage();

                    int32 healAmount = int32(victim->CountPctFromMaxHealth(healPct));
                    victim->CastCustomSpell(victim, PAL_SPELL_ARDENT_DEFENDER_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff);
                    victim->ToPlayer()->AddSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL, 0, time(NULL) + 60);
                }
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_ardent_defender_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_ardent_defender_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_ardent_defender_AuraScript();
        }
};

// 37877 - Blessing of Faith
class spell_pal_blessing_of_faith : public SpellScriptLoader
{
    public:
        spell_pal_blessing_of_faith() : SpellScriptLoader("spell_pal_blessing_of_faith") { }

        class spell_pal_blessing_of_faith_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_blessing_of_faith_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    uint32 spell_id = 0;
                    switch (unitTarget->getClass())
                    {
                        case CLASS_DRUID:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID;
                            break;
                        case CLASS_PALADIN:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN;
                            break;
                        case CLASS_PRIEST:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST;
                            break;
                        case CLASS_SHAMAN:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN;
                            break;
                        default:
                            return; // ignore for non-healing classes
                    }
                    Unit* caster = GetCaster();
                    caster->CastSpell(caster, spell_id, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pal_blessing_of_faith_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_blessing_of_faith_SpellScript();
        }
};

// spell_pal_blessing_of_sanctuary is deprecated

// 64205 - Divine Sacrifice
class spell_pal_divine_sacrifice : public SpellScriptLoader
{
    public:
        spell_pal_divine_sacrifice() : SpellScriptLoader("spell_pal_divine_sacrifice") { }

        class spell_pal_divine_sacrifice_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_divine_sacrifice_AuraScript);

            uint32 groupSize, minHpPct;
            int32 remainingAmount;

            bool Load()
            {

                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetGroup())
                            groupSize = caster->ToPlayer()->GetGroup()->GetMembersCount();
                        else
                            groupSize = 1;
                    }
                    else
                        return false;

                    remainingAmount = (caster->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue(caster)) * groupSize);
                    minHpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(caster);
                    return true;
                }
                return false;
            }

            void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)
            {
                remainingAmount -= splitAmount;
                // break when absorbed everything it could, or if the casters hp drops below 20%
                if (Unit* caster = GetCaster())
                    if (remainingAmount <= 0 || (caster->GetHealthPct() < minHpPct))
                        caster->RemoveAura(SPELL_PALADIN_DIVINE_SACRIFICE);
            }

            void Register()
            {
                OnEffectSplit += AuraEffectSplitFn(spell_pal_divine_sacrifice_AuraScript::Split, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_divine_sacrifice_AuraScript();
        }
};

// 53385 - Divine Storm
class spell_pal_divine_storm : public SpellScriptLoader
{
    public:
        spell_pal_divine_storm() : SpellScriptLoader("spell_pal_divine_storm") { }

        class spell_pal_divine_storm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_divine_storm_SpellScript);

            uint32 healPct;

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_STORM_DUMMY))
                    return false;
                return true;
            }

            bool Load()
            {
                healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                return true;
            }

            void TriggerHeal()
            {
                Unit* caster = GetCaster();
                caster->CastCustomSpell(SPELL_PALADIN_DIVINE_STORM_DUMMY, SPELLVALUE_BASE_POINT0, (GetHitDamage() * healPct) / 100, caster, true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targetCount = 0;

                if (targets.empty())
                    return;

                for (std::list<WorldObject*>::iterator i = targets.begin(); i != targets.end();)
                {
                    WorldObject *obj = (*i);
                    if (obj)
                    {
                        ++i;
                        targetCount++;
                    }
                    else
                        targets.erase(i++);

                    if (targetCount >= 4)
                        HandleEnergize();
                }
            }

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (!caster || !GetHitUnit())
                    return;

                // Mastery: Hand of Light
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3022, 1))
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        int32 amount = GetHitDamage() * (0.168f + (0.021f * masteryPoints));
                        caster->CastCustomSpell(GetHitUnit(), 96172, &amount, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                    }
                }
            }

            void HandleEnergize()
            {
                GetCaster()->EnergizeBySpell(GetCaster(), SPELL_PALADIN_DIVINE_STORM_DUMMY, 1, POWER_HOLY_POWER);
                targetCount = 0;
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_divine_storm_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm_SpellScript::CalculateDamage, EFFECT_2, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
                AfterHit += SpellHitFn(spell_pal_divine_storm_SpellScript::TriggerHeal);
            }

        private:
            uint32 targetCount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_divine_storm_SpellScript();
        }
};

// 54171 - Divine Storm (Dummy)
class spell_pal_divine_storm_dummy : public SpellScriptLoader
{
    public:
        spell_pal_divine_storm_dummy() : SpellScriptLoader("spell_pal_divine_storm_dummy") { }

        class spell_pal_divine_storm_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_divine_storm_dummy_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_STORM_HEAL))
                    return false;
                return true;
            }

            void CountTargets(std::list<WorldObject*>& targetList)
            {
                _targetCount = targetList.size();
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (!_targetCount || ! GetHitUnit())
                    return;

                int32 heal = GetEffectValue() / _targetCount;
                GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_PALADIN_DIVINE_STORM_HEAL, &heal, NULL, NULL, true);
            }
        private:
            uint32 _targetCount;

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_divine_storm_dummy_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_divine_storm_dummy_SpellScript();
        }
};

// 33695 - Exorcism and Holy Wrath Damage
class spell_pal_exorcism_and_holy_wrath_damage : public SpellScriptLoader
{
    public:
        spell_pal_exorcism_and_holy_wrath_damage() : SpellScriptLoader("spell_pal_exorcism_and_holy_wrath_damage") { }

        class spell_pal_exorcism_and_holy_wrath_damage_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_exorcism_and_holy_wrath_damage_AuraScript);

            void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
            {
                if (!spellMod)
                {
                    spellMod = new SpellModifier(aurEff->GetBase());
                    spellMod->op = SPELLMOD_DAMAGE;
                    spellMod->type = SPELLMOD_FLAT;
                    spellMod->spellId = GetId();
                    spellMod->mask[1] = 0x200002;
                }

                spellMod->value = aurEff->GetAmount();
            }

            void Register()
            {
                DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_pal_exorcism_and_holy_wrath_damage_AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_exorcism_and_holy_wrath_damage_AuraScript();
        }
};

// spell_pal_guarded_by_the_light is deprecated

// -9799 - Eye for an Eye
class spell_pal_eye_for_an_eye : public SpellScriptLoader
{
    public:
        spell_pal_eye_for_an_eye() : SpellScriptLoader("spell_pal_eye_for_an_eye") { }

        class spell_pal_eye_for_an_eye_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_eye_for_an_eye_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE))
                    return false;
                return true;
            }

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                // return damage % to attacker but < 50% own total health
                int32 damage = int32(std::min(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()), GetTarget()->GetMaxHealth() / 2));
                GetTarget()->CastCustomSpell(SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetProcTarget(), true, NULL, aurEff);
            }

            void OnProcSecond(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                // return damage % to attacker but < 50% own total health
                int32 damage = int32(std::min(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()), GetTarget()->GetMaxHealth() / 2));
                GetTarget()->CastCustomSpell(SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetProcTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_pal_eye_for_an_eye_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
                OnEffectProc += AuraEffectProcFn(spell_pal_eye_for_an_eye_AuraScript::OnProcSecond, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_eye_for_an_eye_AuraScript();
        }
};

// 6940 - Hand of Sacrifice
class spell_pal_hand_of_sacrifice : public SpellScriptLoader
{
    public:
        spell_pal_hand_of_sacrifice() : SpellScriptLoader("spell_pal_hand_of_sacrifice") { }

        class spell_pal_hand_of_sacrifice_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_hand_of_sacrifice_AuraScript);

            int32 remainingAmount;

            bool Load()
            {
                if (Unit* caster = GetCaster())
                {
                    remainingAmount = caster->GetMaxHealth();
                    return true;
                }
                return false;
            }

            void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)
            {
                remainingAmount -= splitAmount;

                if (remainingAmount <= 0)
                {
                    GetTarget()->RemoveAura(SPELL_PALADIN_HAND_OF_SACRIFICE);
                }
            }

            void Register()
            {
                OnEffectSplit += AuraEffectSplitFn(spell_pal_hand_of_sacrifice_AuraScript::Split, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_hand_of_sacrifice_AuraScript();
        }
};

// -20473 - Holy Shock
class spell_pal_holy_shock : public SpellScriptLoader
{
    public:
        spell_pal_holy_shock() : SpellScriptLoader("spell_pal_holy_shock") { }

        class spell_pal_holy_shock_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_holy_shock_SpellScript);

            bool Validate(SpellInfo const* spell)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_HOLY_SHOCK_R1))
                    return false;

                // can't use other spell than holy shock due to spell_ranks dependency
                if (sSpellMgr->GetFirstSpellInChain(SPELL_PALADIN_HOLY_SHOCK_R1) != sSpellMgr->GetFirstSpellInChain(spell->Id))
                    return false;

                uint8 rank = sSpellMgr->GetSpellRank(spell->Id);
                if (!sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank, true) || !sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank, true))
                    return false;

                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    uint8 rank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);
                    if (caster->IsFriendlyTo(unitTarget))
                        caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank), true, 0);
                    else
                        caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank), true, 0);
                }
            }

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetExplTargetUnit())
                {
                    if (!caster->IsFriendlyTo(target))
                    {
                        if (!caster->IsValidAttackTarget(target))
                            return SPELL_FAILED_BAD_TARGETS;

                        if (!caster->isInFront(target))
                            return SPELL_FAILED_UNIT_NOT_INFRONT;
                    }
                }
                else
                    return SPELL_FAILED_BAD_TARGETS;
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_pal_holy_shock_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_holy_shock_SpellScript();
        }
};

// 31789 - Righteous Defense
class spell_pal_righteous_defense : public SpellScriptLoader
{
    public:
        spell_pal_righteous_defense() : SpellScriptLoader("spell_pal_righteous_defense") { }

        class spell_pal_righteous_defense_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_righteous_defense_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT))
                    return false;
                return true;
            }

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                if (Unit* target = GetExplTargetUnit())
                {
                    if (!target->IsFriendlyTo(caster) || target->getAttackers().empty())
                        return SPELL_FAILED_BAD_TARGETS;
                }
                else
                    return SPELL_FAILED_BAD_TARGETS;

                return SPELL_CAST_OK;
            }

            void HandleTriggerSpellLaunch(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
            }

            void HandleTriggerSpellHit(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_pal_righteous_defense_SpellScript::CheckCast);
                //! WORKAROUND
                //! target select will be executed in hitphase of effect 0
                //! so we must handle trigger spell also in hit phase (default execution in launch phase)
                //! see issue #3718
                OnEffectLaunchTarget += SpellEffectFn(spell_pal_righteous_defense_SpellScript::HandleTriggerSpellLaunch, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
                OnEffectHitTarget += SpellEffectFn(spell_pal_righteous_defense_SpellScript::HandleTriggerSpellHit, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_righteous_defense_SpellScript();
        }
};

// 26573 Consecration
/// Updated 4.0.6
class spell_pal_consecration : public SpellScriptLoader
{
public:
    spell_pal_consecration() : SpellScriptLoader("spell_pal_consecration") { }

    class spell_pal_consecration_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_consecration_AuraScript);

        float x, y, z;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            return true;
        }

        bool Validate (SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_CONSECRATION_DAMAGE) ||
                !sSpellMgr->GetSpellInfo(SPELL_PALADIN_CONSECRATION_SUMMON))
                return false;

            return true;
        }

        void HandlePeriodicDummy(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Unit* consecrationNpc = ObjectAccessor::GetCreature(*caster, caster->m_SummonSlot[1]);
            if (!consecrationNpc)
                return;

            consecrationNpc->GetPosition(x, y, z);

            caster->CastSpell(x, y, z, SPELL_PALADIN_CONSECRATION_DAMAGE, true, NULL, aurEff, caster->GetGUID());
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pal_consecration_AuraScript::HandlePeriodicDummy, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_consecration_AuraScript();
    }
};

// 86150 Guardian of Ancient Kings
// Updated 4.3.4
class spell_pal_guardian_ancient_kings : public SpellScriptLoader
{
public:
    spell_pal_guardian_ancient_kings() : SpellScriptLoader("spell_pal_guardian_ancient_kings") { }

    class spell_pal_guardian_ancient_kings_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_guardian_ancient_kings_SpellScript);

        bool Load()
        {
            return (GetCaster()->GetTypeId() == TYPEID_PLAYER);
        }

        bool Validate (SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_HOLY_GUARDIAN)  ||
                !sSpellMgr->GetSpellInfo(SPELL_PALADIN_RETRI_GUARDIAN) ||
                !sSpellMgr->GetSpellInfo(SPELL_PALADIN_PROT_GUARDIAN))
                return false;

            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Player const* const player = caster->ToPlayer();

            switch (player->GetPrimaryTalentTree(player->GetActiveSpec()))
            {
                case TALENT_TREE_PALADIN_HOLY:
                    caster->CastSpell(caster, SPELL_PALADIN_ANCIENT_HEALER, TRIGGERED_FULL_MASK);
                    caster->CastSpell(caster, SPELL_PALADIN_HOLY_GUARDIAN, TRIGGERED_FULL_MASK);
                    break;
                case TALENT_TREE_PALADIN_PROTECTION:
                    caster->CastSpell(caster, SPELL_PALADIN_PROT_GUARDIAN, TRIGGERED_FULL_MASK);
                    break;
                case TALENT_TREE_PALADIN_RETRIBUTION:
                    caster->CastSpell(caster, SPELL_PALADIN_RETRI_GUARDIAN, TRIGGERED_FULL_MASK);
                    caster->CastSpell(caster, SPELL_PALADIN_ANCIENT_CRUSADER, TRIGGERED_FULL_MASK);
                    break;
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_pal_guardian_ancient_kings_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_guardian_ancient_kings_SpellScript();
    }
};

// 86703 Ancient Crusader
// Updated 4.3.4
class spell_pal_ancient_crusader : public SpellScriptLoader
{
public:
    spell_pal_ancient_crusader() : SpellScriptLoader("spell_pal_ancient_crusader") { }

    class spell_pal_ancient_crusader_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_ancient_crusader_AuraScript);

        bool Validate(SpellInfo const* /*entry*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_PALADIN_ANCIENT_FURY)
                && sSpellMgr->GetSpellInfo(SPELL_PALADIN_ANCIENT_POWER);
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            if (Unit* owner = GetTarget()->GetOwner())
                owner->CastSpell(owner, SPELL_PALADIN_ANCIENT_POWER, TRIGGERED_FULL_MASK);
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (!(mode & AURA_EFFECT_HANDLE_REAL))
                return;

            SpellInfo const* ancientFurySpellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_ANCIENT_FURY);

            Unit* me = GetTarget();
            Unit* owner = me->GetOwner();
            if (!owner)
                return;

            uint32 stacks = 0;

            if (Aura* aura = me->GetAura(SPELL_PALADIN_ANCIENT_POWER))
                stacks += aura->GetStackAmount();

            if (Aura* aura = owner->GetAura(SPELL_PALADIN_ANCIENT_POWER))
            {
                stacks += aura->GetStackAmount();
                aura->Remove();
            }

            owner->RemoveAura(SPELL_PALADIN_ANCIENT_CRUSADER);
            owner->CastCustomSpell(SPELL_PALADIN_ANCIENT_FURY, SPELLVALUE_BASE_POINT0, std::max<uint32>(1, ancientFurySpellInfo->Effects[EFFECT_0].BasePoints * stacks),
                me, TRIGGERED_FULL_MASK);
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_ancient_crusader_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            OnEffectRemove += AuraEffectRemoveFn(spell_pal_ancient_crusader_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_ancient_crusader_AuraScript();
    }
};

//2812 - Holy Wrath
class spell_pal_holy_wrath : public SpellScriptLoader
{
    public:
        spell_pal_holy_wrath() : SpellScriptLoader("spell_pal_holy_wrath") { }

        class spell_pal_holy_wrath_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_holy_wrath_SpellScript);

            enum
            {
                GLYPH_OF_HOLY_WRATH = 56420
            };

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targetCount = 0;

                if (targets.empty())
                     return;

                for (std::list<WorldObject*>::iterator i = targets.begin(); i != targets.end();)
                {
                    WorldObject *obj = (*i);

                    if (obj && !(obj->ToCreature() && obj->ToCreature()->GetCreatureType() == CREATURE_TYPE_CRITTER))
                    {
                        ++i;
                        targetCount++;
                    }
                    else
                        targets.erase(i++);
                }
            }

            void FilterTargetsStun(std::list<WorldObject*>& targets)
            {
                Unit* caster = GetCaster();

                bool hasGlyph = GetCaster() ? GetCaster()->HasAura(GLYPH_OF_HOLY_WRATH) : false;

                for (std::list<WorldObject*>::iterator i = targets.begin(); i != targets.end();)
                {
                    switch ((*i)->ToCreature()->GetCreatureType())
                    {
                        case CREATURE_TYPE_DEMON:
                        case CREATURE_TYPE_UNDEAD:
                        {
                            ++i;
                            break;
                        }
                        case CREATURE_TYPE_ELEMENTAL:
                        case CREATURE_TYPE_DRAGONKIN:
                        {
                            if (hasGlyph)
                                ++i;
                            else
                                targets.erase(i++);
                            break;
                        }
                        default:
                            targets.erase(i++);
                    }
                }
            }

            // Does not work :(
            void DivideDamage(SpellEffIndex effIndex)
            {
                if (targetCount == 0)
                    return;

                SetHitDamage(GetHitDamage() / targetCount);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_holy_wrath_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_holy_wrath_SpellScript::FilterTargetsStun, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_pal_holy_wrath_SpellScript::DivideDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }

            private:
                uint32 targetCount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_holy_wrath_SpellScript();
        }
};

// 20154 - Seal of Righteousness
class spell_pal_seal_of_righteousness : public SpellScriptLoader
{
public:
    spell_pal_seal_of_righteousness() : SpellScriptLoader("spell_pal_seal_of_righteousness") { }

    class spell_pal_seal_of_righteousness_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_seal_of_righteousness_AuraScript);

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            Unit* target = GetTarget();
            Unit* caster = GetCaster();
            if (!target || !caster)
                return;

            target->CastSpell(eventInfo.GetActionTarget(), SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS, true);
            targetHit = false;
            // Seals of Command
            if (caster->HasAura(85126))
            {
                // Spread Seal of Righteousness effect to all target in 5yd
                for (int8 targets = 0; targets < 5; targets++)
                {
                    if (targetHit == true)
                        continue;

                    if (Unit* nearbyTarget = caster->SelectNearbyTarget(target, 5.0f))
                    {
                        caster->CastSpell(nearbyTarget, SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS, true, 0, 0, caster->GetGUID());
                        targetHit = true;
                    }
                }
            }
        }
    private:
        bool targetHit;

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_righteousness_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_seal_of_righteousness_AuraScript();
    }
};

// 25742 - Seal of Righteousness Damage
class spell_pal_seal_of_righteousness_damage : public SpellScriptLoader
{
    public:
        spell_pal_seal_of_righteousness_damage() : SpellScriptLoader("spell_pal_seal_of_righteousness_damage") { }

        class spell_pal_seal_of_righteousness_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_seal_of_righteousness_damage_SpellScript);

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    SetHitDamage(int32((caster->GetBaseAttackTime(BASE_ATTACK) * GetHitDamage()) / 1000));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pal_seal_of_righteousness_damage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_seal_of_righteousness_damage_SpellScript();
        }
};

// 879 Exorcism
// Updated 4.3.4
class spell_pal_exorcism : public SpellScriptLoader
{
public:
    spell_pal_exorcism() : SpellScriptLoader("spell_pal_exorcism") { }

    class spell_pal_exorcism_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_exorcism_SpellScript)

        enum
        {
            GLYPH_EXORCISM  = 54934
        };

        void CheckGlyph()
        {
            Unit *caster = GetCaster();

            if (!caster)
                return;

            if (!caster->HasAura(GLYPH_EXORCISM))
                PreventHitAura();
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_pal_exorcism_SpellScript::CheckGlyph);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_exorcism_SpellScript();
    }
};

// 31801 Seal of Truth
// Updated 4.3.4
class spell_pal_seal_of_truth : public SpellScriptLoader
{
public:
    spell_pal_seal_of_truth() : SpellScriptLoader("spell_pal_seal_of_truth") { }

    class spell_pal_seal_of_truth_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_seal_of_truth_AuraScript);

        enum
        {
            SPELL_CENSURE                   = 31803,
            SPELL_SEAL_OF_TRUTH_TRIGGERED   = 42463,
            GLYPH_SEAL_OF_TRUTH             = 56416
        };

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            const SpellInfo *spellInfo = eventInfo.GetSpellInfo();
            DamageInfo *dmgInfo = eventInfo.GetDamageInfo();
            Unit *target = eventInfo.GetActionTarget();
            Unit *caster = GetCaster();

            if (!dmgInfo || !target || !caster)
                return;

            if (!spellInfo || spellInfo->IsSingleTarget())
            {
                Aura *aura = target->GetAura(SPELL_CENSURE, caster->GetGUID());
                if (!aura)
                    caster->CastSpell(target, SPELL_CENSURE, true);
                else if (aura->GetStackAmount() < 5)
                {
                    aura->ModStackAmount(1);
                    aura->RefreshDuration();
                }
                else
                {
                    aura->RefreshDuration();
                    caster->CastSpell(target, SPELL_SEAL_OF_TRUTH_TRIGGERED, true);
                }
            }
        }

        void CalculateAmount(AuraEffect const* aurEff, int32 &amount, bool &canBeRecalculated)
        {
            Unit *caster = GetCaster();

            if (!caster)
                return;

            Aura *aura = caster->GetAura(GLYPH_SEAL_OF_TRUTH);

            if (!aura)
                return;

            amount = aura->GetEffect(EFFECT_0)->GetAmount();
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_truth_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_seal_of_truth_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_EXPERTISE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_seal_of_truth_AuraScript();
    }
};

// 85256 - Templar's Verdict
class spell_pal_templar_s_verdict : public SpellScriptLoader
{
    public:
        spell_pal_templar_s_verdict() : SpellScriptLoader("spell_pal_templar_s_verdict") { }

        class spell_pal_templar_s_verdict_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_templar_s_verdict_SpellScript);

            void HandleAfterHit()
            {
                Unit* caster = GetCaster();
                if (!caster || !GetHitUnit())
                    return;

                // Mastery: Hand of Light
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3022, 1))
                {
                    int32 amount = GetHitDamage();
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        amount += amount * (0.168f + (0.021f * masteryPoints));
                    }
                    caster->CastCustomSpell(GetHitUnit(), 96172, &amount, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_pal_templar_s_verdict_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_templar_s_verdict_SpellScript();
        }
};

// 53600 - Shield of the Righteous
class spell_pal_shield_of_righteous : public SpellScriptLoader
{
public:
    spell_pal_shield_of_righteous() : SpellScriptLoader("spell_pal_shield_of_righteous") { }

    class spell_pal_shield_of_righteous_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_shield_of_righteous_SpellScript)

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            int32 baseAmount = GetSpellInfo()->Effects[EFFECT_0].BasePoints;

            if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                baseAmount += baseAmount * 6.0f;
            switch (GetSpell()->GetPowerCost())
            {
                case 2:
                    baseAmount += baseAmount * 3.0f;
                    break;
                case 3:
                    baseAmount += baseAmount * 6.0f;
                    break;
            }

        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_shield_of_righteous_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_shield_of_righteous_SpellScript();
    }
};

// 85222 - Light of Dawn
class spell_pal_ligh_of_dawn : public SpellScriptLoader
{
    public:
        spell_pal_ligh_of_dawn() : SpellScriptLoader("spell_pal_ligh_of_dawn") { }

        class spell_pal_ligh_of_dawn_SpellScript : public SpellScript
        {
            public:
                PrepareSpellScript(spell_pal_ligh_of_dawn_SpellScript);

                enum
                {
                    GLYPH_LIGHT_OF_DAWN = 54940
                };

                bool Load()
                {
                    count = 0;
                    if (Unit *caster = GetCaster())
                        glyphed = caster->HasAura(GLYPH_LIGHT_OF_DAWN);
                    else
                        return false;

                    return true;
                }

                struct sort_lostHealt
                {
                    bool operator()(WorldObject *first, WorldObject *second)
                    {
                        uint32 delta1 = 0;
                        uint32 delta2 = 0;

                        if (WorldObject *obj = first)
                            if (Unit *unit = obj->ToUnit())
                                delta1 = unit->GetMaxHealth() - unit->GetHealth();

                        if (WorldObject *obj = second)
                            if (Unit *unit = obj->ToUnit())
                                delta2 = unit->GetMaxHealth() - unit->GetHealth();

                        return delta1 < delta2;
                    }
                };

                void SelectTargets(std::list <WorldObject *> &targets)
                {
                    if (targets.size() <= (glyphed ? 4 : 6))
                    {
                        count = targets.size();
                        return;
                    }

                    targets.sort(sort_lostHealt());

                    while (targets.size() > (glyphed ? 4 : 6))
                        targets.pop_front();

                    count = (glyphed ? 4 : 6);
                }

                void CalculateHeal(SpellEffIndex effIndex)
                {
                    Unit *caster = GetCaster();

                    if (!caster)
                        return;

                    if (effIndex == EFFECT_1 && count >= (glyphed ? 4 : 6))
                        PreventHitEffect(EFFECT_1);

                    if (glyphed)
                        SetHitHeal(CalculatePct(GetHitHeal(), 125));

                    if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                        SetHitHeal(GetHitHeal() * 3);
                    else if (GetSpell())
                        SetHitHeal(GetHitHeal() * GetSpell()->GetPowerCost());
                }

                void Register()
                {
                    OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_ligh_of_dawn_SpellScript::SelectTargets, EFFECT_0, TARGET_UNIT_CONE_ALLY);
                    OnEffectHitTarget += SpellEffectFn(spell_pal_ligh_of_dawn_SpellScript::CalculateHeal, EFFECT_0, SPELL_EFFECT_HEAL);
                    OnEffectHitTarget += SpellEffectFn(spell_pal_ligh_of_dawn_SpellScript::CalculateHeal, EFFECT_1, SPELL_EFFECT_HEAL);
                }

            private:
                uint8 count;
                bool glyphed;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_ligh_of_dawn_SpellScript();
        }
};

// 85673 - Word of Glory
class spell_pal_word_of_glory: public SpellScriptLoader
{
public:
    spell_pal_word_of_glory() : SpellScriptLoader("spell_pal_word_of_glory"){}

    class spell_pal_word_of_glory_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_pal_word_of_glory_SpellScript);
        uint32 totHeal;
        int32 powerCost;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void ImproveHealing(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (GetCaster()->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
            {
                totHeal = GetHitHeal() * 3;

                SetHitHeal(totHeal);
                return;
            }

            switch (caster->GetPower(POWER_HOLY_POWER))
            {
                case 0:
                    totHeal = GetHitHeal();
                    powerCost = 1;
                    break;
                case 1:
                    totHeal = GetHitHeal() * 2;
                    powerCost = 2;
                    break;
                case 2:
                    totHeal = GetHitHeal() * 3;
                    powerCost = 3;
                    break;
                default:
                    break;
            }
            // Selfless Healer
            if (AuraEffect const* auraEff = caster->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 3924, EFFECT_0))
            {
                if (target != caster)
                    totHeal += totHeal + (totHeal * auraEff->GetAmount()) / 100;
            }

            SetHitHeal(totHeal);
        }

        void HandlePeriodic()
        {
            Aura *aura = GetCaster()->GetAura(SPELL_GLYPH_OF_THE_LONG_WORD);
            if (!aura)
                PreventHitAura();
            else if (AuraEffect *aurEff = aura->GetEffect(EFFECT_0))
                aurEff->SetAmount(CalculatePct(GetHitHeal(),aurEff->GetAmount()));
        }

        void HandleAfterCast()
        {
            // Eternal Glory
            if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 2944, 0))
            {
                int32 chance = aurEff->GetAmount();
                if (roll_chance_i(chance))
                    GetCaster()->CastCustomSpell(GetCaster(), SPELL_EFFECT_ETERNAL_GLORY, &powerCost, NULL, NULL, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_word_of_glory_SpellScript::ImproveHealing, EFFECT_0, SPELL_EFFECT_HEAL);
            AfterCast += SpellCastFn(spell_pal_word_of_glory_SpellScript::HandleAfterCast);
            AfterHit += SpellHitFn(spell_pal_word_of_glory_SpellScript::HandlePeriodic);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_word_of_glory_SpellScript();
    }
};

// 20271 - Judgement
class spell_pal_judgement : public SpellScriptLoader
{
public:
    spell_pal_judgement() : SpellScriptLoader("spell_pal_judgement") { }

    class spell_pal_judgement_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_judgement_SpellScript)

        enum
        {
            SPELL_JUDGEMENT_DAMAGE  = 54158,
            TALENT_COMMUNION        = 31876,
            SPELL_REFRESH           = 57669,
            TALENT_JUDGEMENT_BOLD   = 89901,
            SPELL_JUDGEMENT_BOLD    = 89906,
            TALENT_JUDGEMENT_WISE   = 31878,
            SPELL_JUDGEMENT_WISE    = 31930,
        };

        void HandleDummy(SpellEffIndex indx)
        {
            Unit *caster = GetCaster();
            Unit *target = GetHitUnit();

            if (!target || !caster)
                return;

            caster->CastSpell(target, SPELL_JUDGEMENT_DAMAGE, true);

            if (caster->HasAura(TALENT_COMMUNION))
                caster->CastSpell(caster, SPELL_REFRESH, true);

            if (caster->HasAura(TALENT_JUDGEMENT_BOLD))
                caster->CastSpell(caster, SPELL_JUDGEMENT_BOLD, true);

            if (caster->HasAura(TALENT_JUDGEMENT_WISE))
                caster->CastSpell(caster, SPELL_JUDGEMENT_WISE, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_judgement_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_judgement_SpellScript();
    }
};

// 35395 - spell_pal_crusader_strike
class spell_pal_crusader_strike : public SpellScriptLoader
{
    public:
        spell_pal_crusader_strike() : SpellScriptLoader("spell_pal_crusader_strike") { }

        class spell_pal_crusader_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_crusader_strike_SpellScript);

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (!caster || !GetHitUnit())
                    return;

                // Mastery: Hand of Light
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3022, 1))
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        int32 amount = GetHitDamage() * (0.168f + (0.021f * masteryPoints));
                        caster->CastCustomSpell(GetHitUnit(), 96172, &amount, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pal_crusader_strike_SpellScript::CalculateDamage, EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pal_crusader_strike_SpellScript();
        }
};

void AddSC_paladin_spell_scripts()
{
    new spell_pal_ardent_defender();
    new spell_pal_divine_sacrifice();
    new spell_pal_divine_storm();
    new spell_pal_divine_storm_dummy();
    new spell_pal_exorcism_and_holy_wrath_damage();
    new spell_pal_eye_for_an_eye();
    new spell_pal_hand_of_sacrifice();
    new spell_pal_holy_shock();
    new spell_pal_righteous_defense();
    new spell_pal_consecration();
    new spell_pal_guardian_ancient_kings();
    new spell_pal_ancient_crusader();
    new spell_pal_holy_wrath();
    new spell_pal_seal_of_righteousness();
    new spell_pal_exorcism();
    new spell_pal_seal_of_truth();
    new spell_pal_judgement();
    new spell_pal_templar_s_verdict();
    new spell_pal_word_of_glory();
    new spell_pal_shield_of_righteous();
    new spell_pal_ligh_of_dawn();
    new spell_pal_seal_of_righteousness_damage();
    new spell_pal_crusader_strike();
}
