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
 * Scripts for spells with SPELLFAMILY_PRIEST and SPELLFAMILY_GENERIC spells used by priest players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pri_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"

enum PriestSpells
{
    SPELL_PRIEST_DIVINE_AEGIS                       = 47753,
    SPELL_PRIEST_EMPOWERED_RENEW                    = 63544,
    SPELL_PRIEST_GLYPH_OF_LIGHTWELL                 = 55673,
    SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL    = 56161,
    SPELL_PRIEST_GLYPH_OF_SHADOW                    = 107906,
    SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL               = 48153,
    SPELL_PRIEST_LEAP_OF_FAITH                      = 73325,
    SPELL_PRIEST_LEAP_OF_FAITH_EFFECT               = 92832,
    SPELL_PRIEST_LEAP_OF_FAITH_EFFECT_TRIGGER       = 92833,
    SPELL_PRIEST_LEAP_OF_FAITH_TRIGGERED            = 92572,
    SPELL_PRIEST_MANA_LEECH_PROC                    = 34650,
    SPELL_PRIEST_PENANCE                            = 47540,
    SPELL_PRIEST_PENANCE_DAMAGE                     = 47758,
    SPELL_PRIEST_PENANCE_HEAL                       = 47757,
    SPELL_PRIEST_REFLECTIVE_SHIELD_R1               = 33201,
    SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED        = 33619,
    SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH    = 107903,
    SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH       = 107904,
    SPELL_PRIEST_SHADOW_WORD_DEATH                  = 32409,
    SPELL_PRIEST_T9_HEALING_2P                      = 67201,
    SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL              = 64085,

    SPELL_PRIEST_REVELATIONS                        = 88627,
    SPELL_PRIEST_RENEW                              = 139,

    SPELL_PRIEST_SANCTUARY_4YD_DUMMY                = 88667,
    SPELL_PRIEST_SANCTUARY_4YD_HEAL                 = 88668,
    SPELL_PRIEST_SANCTUARY_8YD_DUMMY                = 88685,
    SPELL_PRIEST_SANCTUARY_8YD_HEAL                 = 88686,

    SPELL_PRIEST_SHADOWY_APPARITION_R3              = 78204,
    SPELL_PRIEST_SHADOWY_APPARITION_R1              = 78202,
    SPELL_PRIEST_SHADOWY_APPARITION_R2              = 78203,
    SPELL_PRIEST_SHADOWY_APPARITION_SUMMON          = 87426,

    SPELL_PRIEST_SHADOW_WORD_PAIN                   = 589,

    SPELL_PRIEST_EVANGELISM                         = 81661,
    SPELL_PRIEST_EVANGELISM_2                       = 87154,
    SPELL_PRIEST_ARCHANGEL                          = 87152,
    SPELL_PRIEST_ARCHANGEL_2                        = 81700,

    SPELL_PRIEST_DARK_EVANGELISM                    = 87118,
    SPELL_PRIEST_DARK_ARCHANGEL                     = 87153,

    SPELL_PRIEST_GLYPH_POWER_WORD_BARRIER           = 55689,
    SPELL_PRIEST_SHADOW_ORB_STACK_MARKER            = 77487,
    SPELL_PRIEST_EMPOWERED_SHADOW                   = 95799,

    SPELL_PRIEST_ECHO_OF_LIGHT                      = 77485,
    SPELL_PRIEST_ECHO_OF_LIGHT_EFFECT               = 77489,

    SPELL_PRIEST_BODY_AND_SOUL_R1                   = 64127,
    SPELL_PRIEST_BODY_AND_SOUL_R2                   = 64129,
    SPELL_PRIEST_BODY_AND_SOUL_SPEED_INCREASE_R1    = 64128,
    SPELL_PRIEST_BODY_AND_SOUL_SPEED_INCREASE_R2    = 65081,
    SPELL_PRIEST_BODY_AND_SOUL_DISPEL               = 64136,

    SPELL_PRIEST_CURE_DISEASE                       = 528,
    SPELL_PRIEST_POWER_WORD_SHIELD                  = 17,

    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK           = 27792,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK1          = 27795,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK2          = 27827,
    SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK3          = 62371,

    SPELL_PRIEST_ATONEMENT                          = 81751,

    SPELL_PRIEST_INNER_FOCUS                        = 89485,
    SPELL_PRIEST_GREATER_HEAL                       = 2060,
    SPELL_PRIEST_SMITE                              = 585,

    SPELL_PRIEST_WEAKENED_SOUl                      = 6788,

    SPELL_PRIEST_PRAYER_OF_HEALING                  = 596,

    SPELL_PRIEST_IMPROVED_POWER_WORD_SHIELD_R1		= 14748,
    SPELL_PRIEST_IMPROVED_POWER_WORD_SHIELD_R2		= 14768,
    
    SPELL_PRIEST_FADE                               = 586,
    SPELL_PRIEST_PHANTASM_R1                        = 47569,
    SPELL_PRIEST_PHANTASM_R2                        = 47570,

    SPELL_PRIEST_EVANGELISM_R1                      = 81659,
    SPELL_PRIEST_EVANGELISM_R2                      = 81662,
    SPELL_PRIEST_EVANGELISM_EFFECT_R1               = 81660,
    SPELL_PRIEST_EVANGELISM_EFFECT_R2               = 81661,
    SPELL_PRIEST_GLYPH_OF_POWER_WORD_SHIELD         = 55672,
    SPELL_PRIEST_GLYPH_OF_POWER_WORD_SHIELD_TRIG    = 56160,
    SPELL_PRIEST_GLYPH_OF_SPIRIT_TAP                = 63237,
    SPELL_PRIEST_GLYPH_OF_SPIRIT_TAP_TRIGGERED      = 81301,
    SPELL_PRIEST_GLYPH_OF_SHADOWFORM                = 107906,

    SPELL_PRIEST_T11_HEALER_BONUS_4P                = 89911,
    SPELL_PRIEST_T11_HEALER_BONUS_4P_TRIGGER        = 89913
};

enum PriestSpellIcons
{
    PRIEST_ICON_ID_BORROWED_TIME                    = 2899,
    PRIEST_ICON_ID_EMPOWERED_RENEW_TALENT           = 3021,
    PRIEST_ICON_ID_PAIN_AND_SUFFERING               = 2874,
    PRIEST_ICON_ID_IMPROVED_POWER_WORD_SHIELD       = 566,
    PRIEST_ICON_ID_STRENGTH_OF_SOUL                 = 177,
    PRIEST_ICON_ID_REFLECTIVE_SHIELD                = 4880
};

enum PriestSpec
{
    PRIEST_SPEC_DISCIPLINE  = 760
};

// 47509 Divine Aegis (Rank 1)
// 47511 Divine Aegis (Rank 2)
// 47515 Divine Aegis (Rank 3)
// Upgraded 4.3.4
class spell_pri_divine_aegis : public SpellScriptLoader
{
public:
    spell_pri_divine_aegis() : SpellScriptLoader("spell_pri_divine_aegis") { }

        class spell_pri_divine_aegis_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_divine_aegis_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                return sSpellMgr->GetSpellInfo(SPELL_PRIEST_DIVINE_AEGIS) && sSpellMgr->GetSpellInfo(SPELL_PRIEST_PRAYER_OF_HEALING);
            }

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return (eventInfo.GetHitMask() & PROC_EX_CRITICAL_HIT) || eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_PRIEST_PRAYER_OF_HEALING;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                int32 absorb = CalculatePct(int32(eventInfo.GetHealInfo()->GetHeal()), aurEff->GetAmount());

                // Blizzlike (Twice application on crit)
                if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_PRIEST_PRAYER_OF_HEALING && (eventInfo.GetHitMask() & PROC_EX_CRITICAL_HIT))
                    absorb += CalculatePct(int32(eventInfo.GetHealInfo()->GetHeal() / 2), aurEff->GetAmount());

                // Multiple effects stack, so let's try to find this aura.
                if (AuraEffect const* aegis = eventInfo.GetActionTarget()->GetAuraEffect(SPELL_PRIEST_DIVINE_AEGIS, EFFECT_0))
                {
                    if ((aegis->GetAmount() + absorb) >= eventInfo.GetActionTarget()->GetMaxHealth() * 0.40f)
                        absorb = eventInfo.GetActionTarget()->GetMaxHealth() * 0.40f;
                    else
                        absorb += aegis->GetAmount();
                }

                GetTarget()->CastCustomSpell(SPELL_PRIEST_DIVINE_AEGIS, SPELLVALUE_BASE_POINT0, absorb, eventInfo.GetActionTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_pri_divine_aegis_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_pri_divine_aegis_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_divine_aegis_AuraScript();
        }
};

// 55680 - Glyph of Prayer of Healing
class spell_pri_glyph_of_prayer_of_healing : public SpellScriptLoader
{
    public:
        spell_pri_glyph_of_prayer_of_healing() : SpellScriptLoader("spell_pri_glyph_of_prayer_of_healing") { }

        class spell_pri_glyph_of_prayer_of_healing_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_glyph_of_prayer_of_healing_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                SpellInfo const* triggeredSpellInfo = sSpellMgr->GetSpellInfo(SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL);
                int32 heal = int32(CalculatePct(int32(eventInfo.GetHealInfo()->GetHeal()), aurEff->GetAmount()) / triggeredSpellInfo->GetMaxTicks());
                GetTarget()->CastCustomSpell(SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL, SPELLVALUE_BASE_POINT0, heal, eventInfo.GetProcTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_pri_glyph_of_prayer_of_healing_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_glyph_of_prayer_of_healing_AuraScript();
        }
};

enum PriestNpcs
{
    PRIEST_NPC_SHADOWY_APPARITION                = 46954
};

// 47788 - Guardian Spirit
class spell_pri_guardian_spirit : public SpellScriptLoader
{
    public:
        spell_pri_guardian_spirit() : SpellScriptLoader("spell_pri_guardian_spirit") { }

        class spell_pri_guardian_spirit_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_guardian_spirit_AuraScript);

            uint32 healPct;

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL))
                    return false;
                return true;
            }

            bool Load()
            {
                healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                if (dmgInfo.GetDamage() < target->GetHealth())
                    return;

                int32 healAmount = int32(target->CountPctFromMaxHealth(healPct));
                // remove the aura now, we don't want 40% healing bonus
                Remove(AURA_REMOVE_BY_ENEMY_SPELL);
                target->CastCustomSpell(target, SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL, &healAmount, NULL, NULL, true);
                absorbAmount = dmgInfo.GetDamage();
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_guardian_spirit_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_guardian_spirit_AuraScript::Absorb, EFFECT_1);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_guardian_spirit_AuraScript();
        }
};

// 92833 - Leap of Faith
class spell_pri_leap_of_faith_effect_trigger : public SpellScriptLoader
{
    public:
        spell_pri_leap_of_faith_effect_trigger() : SpellScriptLoader("spell_pri_leap_of_faith_effect_trigger") { }

        class spell_pri_leap_of_faith_effect_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_leap_of_faith_effect_trigger_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_LEAP_OF_FAITH_EFFECT))
                    return false;
                return true;
            }

            void HandleEffectDummy(SpellEffIndex /*effIndex*/)
            {
                Position destPos;
                GetHitDest()->GetPosition(&destPos);

                SpellCastTargets targets;
                targets.SetDst(destPos);
                targets.SetUnitTarget(GetCaster());
                GetHitUnit()->CastSpell(targets, sSpellMgr->GetSpellInfo(GetEffectValue()), NULL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_leap_of_faith_effect_trigger_SpellScript::HandleEffectDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_leap_of_faith_effect_trigger_SpellScript();
        }
};

// -7001 - Lightwell Renew
class spell_pri_lightwell_renew : public SpellScriptLoader
{
    public:
        spell_pri_lightwell_renew() : SpellScriptLoader("spell_pri_lightwell_renew") { }

        class spell_pri_lightwell_renew_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_lightwell_renew_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Bonus from Glyph of Lightwell
                    if (AuraEffect* modHealing = caster->GetAuraEffect(SPELL_PRIEST_GLYPH_OF_LIGHTWELL, EFFECT_0))
                        AddPct(amount, modHealing->GetAmount());
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_lightwell_renew_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_lightwell_renew_AuraScript();
        }
};

// 8129 - Mana Burn
class spell_pri_mana_burn : public SpellScriptLoader
{
    public:
        spell_pri_mana_burn() : SpellScriptLoader("spell_pri_mana_burn") { }

        class spell_pri_mana_burn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_mana_burn_SpellScript);

            void HandleAfterHit()
            {
                if (Unit* unitTarget = GetHitUnit())
                    unitTarget->RemoveAurasWithMechanic((1 << MECHANIC_FEAR) | (1 << MECHANIC_POLYMORPH));
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_pri_mana_burn_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mana_burn_SpellScript;
        }
};

// 28305 - Mana Leech (Passive) (Priest Pet Aura)
class spell_pri_mana_leech : public SpellScriptLoader
{
    public:
        spell_pri_mana_leech() : SpellScriptLoader("spell_pri_mana_leech") { }

        class spell_pri_mana_leech_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_mana_leech_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_MANA_LEECH_PROC))
                    return false;
                return true;
            }

            bool Load()
            {
                _procTarget = NULL;
                return true;
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                _procTarget = GetTarget()->GetOwner();
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(_procTarget, SPELL_PRIEST_MANA_LEECH_PROC, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_pri_mana_leech_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_pri_mana_leech_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_mana_leech_AuraScript();
        }
};

// 49821 - Mind Sear
class spell_pri_mind_sear : public SpellScriptLoader
{
    public:
        spell_pri_mind_sear() : SpellScriptLoader("spell_pri_mind_sear") { }

        class spell_pri_mind_sear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_mind_sear_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(Trinity::ObjectGUIDCheck(GetCaster()->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT)));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_mind_sear_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mind_sear_SpellScript();
        }
};

// 47948 - Pain and Suffering (Proc)
class spell_pri_pain_and_suffering_proc : public SpellScriptLoader
{
    public:
        spell_pri_pain_and_suffering_proc() : SpellScriptLoader("spell_pri_pain_and_suffering_proc") { }

        class spell_pri_pain_and_suffering_proc_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_pain_and_suffering_proc_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                // Refresh Shadow Word: Pain on target
                if (Unit* unitTarget = GetHitUnit())
                    if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, 0x8000, 0, 0, GetCaster()->GetGUID()))
                        aur->GetBase()->RefreshDuration();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_pain_and_suffering_proc_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_pain_and_suffering_proc_SpellScript;
        }
};

// 47540 - Penance
class spell_pri_penance : public SpellScriptLoader
{
    public:
        spell_pri_penance() : SpellScriptLoader("spell_pri_penance") { }

        class spell_pri_penance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_penance_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* spellInfo)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_PENANCE))
                    return false;
                // can't use other spell than this penance due to spell_ranks dependency
                if (sSpellMgr->GetFirstSpellInChain(SPELL_PRIEST_PENANCE) != sSpellMgr->GetFirstSpellInChain(spellInfo->Id))
                    return false;

                uint8 rank = sSpellMgr->GetSpellRank(spellInfo->Id);
                if (!sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_DAMAGE, rank, true))
                    return false;
                if (!sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_HEAL, rank, true))
                    return false;

                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    if (!unitTarget->isAlive())
                        return;

                    uint8 rank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);

                    if (caster->IsFriendlyTo(unitTarget))
                        caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_HEAL, rank), false, 0);
                    else
                        caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_DAMAGE, rank), false, 0);

                    // Item - Priest T11 Healer 4P Bonus
                    if (caster->HasAura(SPELL_PRIEST_T11_HEALER_BONUS_4P))
                        caster->CastSpell(caster, SPELL_PRIEST_T11_HEALER_BONUS_4P_TRIGGER, true);
                }
            }

            SpellCastResult CheckCast()
            {
                Player* caster = GetCaster()->ToPlayer();
                if (Unit* target = GetExplTargetUnit())
                    if (!caster->IsFriendlyTo(target) && !caster->IsValidAttackTarget(target))
                        return SPELL_FAILED_BAD_TARGETS;
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_penance_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_pri_penance_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_penance_SpellScript;
        }
};

// 17 - Power Word: Shield
// Upgraded 4.3.4
class spell_pri_power_word_shield : public SpellScriptLoader
{
    public:
        spell_pri_power_word_shield() : SpellScriptLoader("spell_pri_power_word_shield") { }

        class spell_pri_power_word_shield_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_power_word_shield_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_REFLECTIVE_SHIELD_R1))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    // +80.68% from SP bonus
                    float bonus = 0.8068f;
                    bonus *= caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask());
                    bonus = caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), bonus);
                    bonus *= caster->CalculateLevelPenalty(GetSpellInfo());

                    amount += int32(bonus);

                    // Improved Power Word: Shield r 1
                    if (AuraEffect const* improved = GetCaster()->GetAuraEffect(SPELL_PRIEST_IMPROVED_POWER_WORD_SHIELD_R1, EFFECT_0))
                        AddPct(amount, improved->GetAmount());

                    // Improved Power Word: Shield r2
                    if (AuraEffect const* improved = GetCaster()->GetAuraEffect(SPELL_PRIEST_IMPROVED_POWER_WORD_SHIELD_R2, EFFECT_0))
                        AddPct(amount, improved->GetAmount());

                    // Mastery: Shield Discipline
                    if (caster->GetTypeId() == TYPEID_PLAYER && caster->ToPlayer()->HasAuraType(SPELL_AURA_MASTERY))
                    {
                        if (Player* pCaster = caster->ToPlayer())
                        {
                            float masteryRate = pCaster->GetRatingBonusValue(CR_MASTERY);
                            if (pCaster->getClass() == CLASS_PRIEST)
                            {
                                if (pCaster->GetPrimaryTalentTree(pCaster->GetActiveSpec()) == PRIEST_SPEC_DISCIPLINE)
                                {
                                    int32 bonusTotal = int32(amount * (0.20f + (0.025f * masteryRate)));
                                    amount += bonusTotal;
                                }
                            }
                        }
                    }
                }
            }

            void ReflectDamage(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                Unit* target = GetTarget();
                if (!target)
                    return;

                if (dmgInfo.GetAttacker() == target)
                    return;

                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect* talentAurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, PRIEST_ICON_ID_REFLECTIVE_SHIELD, EFFECT_0))
                    {
                        int32 bp = CalculatePct(absorbAmount, talentAurEff->GetAmount());
                        target->CastCustomSpell(dmgInfo.GetAttacker(), SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
                    }
                }
            }

            void HandleAfterApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();

                if (caster && target && GetEffect(EFFECT_0))
                {
                    // Glyph of Power Word Shield
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_PRIEST_GLYPH_OF_POWER_WORD_SHIELD, EFFECT_0, caster->GetGUID()))
                    {
                        int32 bp0 = CalculatePct(GetEffect(EFFECT_0)->GetAmount(), aurEff->GetAmount());
                        caster->CastCustomSpell(target, SPELL_PRIEST_GLYPH_OF_POWER_WORD_SHIELD_TRIG, &bp0, NULL, NULL, true);
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_power_word_shield_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                AfterEffectAbsorb += AuraEffectAbsorbFn(spell_pri_power_word_shield_AuraScript::ReflectDamage, EFFECT_0);
                AfterEffectApply += AuraEffectApplyFn(spell_pri_power_word_shield_AuraScript::HandleAfterApply, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_power_word_shield_AuraScript();
        }
};

// 33110 - Prayer of Mending Heal
class spell_pri_prayer_of_mending_heal : public SpellScriptLoader
{
    public:
        spell_pri_prayer_of_mending_heal() : SpellScriptLoader("spell_pri_prayer_of_mending_heal") { }

        class spell_pri_prayer_of_mending_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_prayer_of_mending_heal_SpellScript);

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetOriginalCaster())
                {
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_PRIEST_T9_HEALING_2P, EFFECT_0))
                    {
                        int32 heal = GetHitHeal();
                        AddPct(heal, aurEff->GetAmount());
                        SetHitHeal(heal);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_prayer_of_mending_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_prayer_of_mending_heal_SpellScript();
        }
};

// 139 - Renew
// Updated 4.3.4
class spell_pri_renew : public SpellScriptLoader
{
    public:
        spell_pri_renew() : SpellScriptLoader("spell_pri_renew") { }

        class spell_pri_renew_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_renew_AuraScript);

            bool Load()
            {
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleApplyEffect(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Empowered Renew
                    if (AuraEffect const* empoweredRenewAurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, PRIEST_ICON_ID_EMPOWERED_RENEW_TALENT, EFFECT_0))
                    {
                        uint32 heal = caster->SpellHealingBonusDone(GetTarget(), GetSpellInfo(), GetEffect(EFFECT_0)->GetAmount(), DOT);
                        heal = GetTarget()->SpellHealingBonusTaken(caster, GetSpellInfo(), heal, DOT);

                        int32 basepoints0 = empoweredRenewAurEff->GetAmount() * GetEffect(EFFECT_0)->GetTotalTicks() * int32(heal) / 100;
                        caster->CastCustomSpell(GetTarget(), SPELL_PRIEST_EMPOWERED_RENEW, &basepoints0, NULL, NULL, true, NULL, aurEff);
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_pri_renew_AuraScript::HandleApplyEffect, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_renew_AuraScript();
        }
};

// 32379 - Shadow Word Death
// Updated 4.3.4
class spell_pri_shadow_word_death: public SpellScriptLoader
{
public:
    spell_pri_shadow_word_death() : SpellScriptLoader("spell_pri_shadow_word_death") { }

    class spell_pri_shadow_word_death_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_pri_shadow_word_death_SpellScript);

        void HandlePrimaryEffects(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (target->HealthBelowPct(25))
                    {
                        // Mind Melt
                        if (AuraEffect* mindMelt = caster->GetAuraEffectOfRankedSpell(14910, EFFECT_0))
                            SetHitDamage(GetHitDamage() + GetHitDamage() * mindMelt->GetAmount() / 100);

                        SetHitDamage(GetHitDamage() * 3);

                        // Glyph of Shadow Word: Death
                        if (caster->HasAura(55682) && !caster->HasAura(95652))
                        {
                            // Glyph of Shadow Word: Death - Marker
                            caster->AddAura(95652, caster);
                            if (caster->GetTypeId() == TYPEID_PLAYER)
                                caster->ToPlayer()->RemoveSpellCooldown(32379, true);
                        }
                    }

                    SetHitDamage(GetHitDamage());

                    int32 back_damage = GetHitDamage();
                    if (back_damage < int32(target->GetHealth()))
                    {
                        // Pain and Suffering
                        if (caster->HasAura(47580))
                            back_damage -= back_damage * 0.20f;
                        else if (caster->HasAura(47581))
                            back_damage -= back_damage * 0.40f;

                        caster->CastCustomSpell(caster, 32409, &back_damage, NULL, NULL, true);
                    }
                }
            }
        }

        void HandleSpiritTap()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Glyph of Spirit Tap
                    if (!target->isAlive() && caster->HasAura(SPELL_PRIEST_GLYPH_OF_SPIRIT_TAP) && caster->ToPlayer()->isHonorOrXPTarget(target))
                        caster->CastSpell(caster, SPELL_PRIEST_GLYPH_OF_SPIRIT_TAP_TRIGGERED, true);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pri_shadow_word_death_SpellScript::HandlePrimaryEffects, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            AfterHit += SpellHitFn(spell_pri_shadow_word_death_SpellScript::HandleSpiritTap);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pri_shadow_word_death_SpellScript;
    }
};

// 15473 - Shadowform
class spell_pri_shadowform : public SpellScriptLoader
{
    public:
        spell_pri_shadowform() : SpellScriptLoader("spell_pri_shadowform") { }

        class spell_pri_shadowform_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_shadowform_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH) ||
                    !sSpellMgr->GetSpellInfo(SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH) ||
                    !sSpellMgr->GetSpellInfo(SPELL_PRIEST_GLYPH_OF_SHADOW))
                    return false;
                return true;
            }

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (caster->HasAura(SPELL_PRIEST_GLYPH_OF_SHADOW))
                        caster->CastSpell(caster, SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH, true);
                    else
                        caster->CastSpell(caster, SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH, true);
                }
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (caster->HasAura(SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH))
                        caster->RemoveAurasDueToSpell(SPELL_PRIEST_SHADOWFORM_VISUAL_WITH_GLYPH);
                    if (caster->HasAura(SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH))
                        caster->RemoveAurasDueToSpell(SPELL_PRIEST_SHADOWFORM_VISUAL_WITHOUT_GLYPH);
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_pri_shadowform_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_pri_shadowform_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_shadowform_AuraScript();
        }
};

class spell_pri_chakra_swap_supressor : public SpellScriptLoader
{
    public:
        spell_pri_chakra_swap_supressor() : SpellScriptLoader("spell_pri_chakra_swap_supressor") { }

        enum spellId
        {
            SPELL_PRIEST_CHASTISE    = 88625
        };

        class spell_pri_chakra_swap_supressor_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_chakra_swap_supressor_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Revelations
                    if (!caster->HasAura(SPELL_PRIEST_REVELATIONS))
                        amount = SPELL_PRIEST_CHASTISE;
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_chakra_swap_supressor_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_chakra_swap_supressor_AuraScript();
        }
};

// 81585 Chakra: Serenity, Renew spell duration reset
class spell_pri_chakra_serenity_proc : public SpellScriptLoader
{
public:
    spell_pri_chakra_serenity_proc() : SpellScriptLoader("spell_pri_chakra_serenity_proc") {}

    class spell_pri_chakra_serenity_proc_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_chakra_serenity_proc_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (Aura* renew = target->GetAura(SPELL_PRIEST_RENEW, GetCaster()->GetGUID()))
                renew->RefreshDuration();
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pri_chakra_serenity_proc_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pri_chakra_serenity_proc_SpellScript();
    }
};

// 88685, 88687 Chakra: Sanctuary GTAoe effect
class spell_pri_chakra_sanctuary_heal: public SpellScriptLoader
{
public:
    spell_pri_chakra_sanctuary_heal() : SpellScriptLoader("spell_pri_chakra_sanctuary_heal") {}

    class spell_pri_chakra_sanctuary_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_chakra_sanctuary_heal_SpellScript);

        float x, y, z;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            GetExplTargetDest()->GetPosition(x, y, z);
            return true;
        }

        void HandleExtraEffect()
        {
            if (GetSpellInfo()->Id == SPELL_PRIEST_SANCTUARY_8YD_DUMMY)
                GetCaster()->CastSpell(x, y, z, SPELL_PRIEST_SANCTUARY_4YD_DUMMY, true);
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_pri_chakra_sanctuary_heal_SpellScript::HandleExtraEffect);
        }
    };

    class spell_pri_chakra_sanctuary_heal_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_chakra_sanctuary_heal_AuraScript);

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            return true;
        }

        void HandlePeriodicDummy(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();
            DynamicObject* dynObj = caster->GetDynObject(GetSpellInfo()->Id);

            if(caster && dynObj && caster->GetMapId() == dynObj->GetMapId())
            {
                float x, y, z;
                dynObj->GetPosition(x, y, z);

                switch(GetSpellInfo()->Id)
                {
                    case SPELL_PRIEST_SANCTUARY_8YD_DUMMY:
                    {
                        caster->CastSpell(x, y, z, SPELL_PRIEST_SANCTUARY_8YD_HEAL, true);
                        break;
                    }
                    case SPELL_PRIEST_SANCTUARY_4YD_DUMMY:
                    {
                        caster->CastSpell(x, y, z, SPELL_PRIEST_SANCTUARY_4YD_HEAL, true);
                        break;
                    }
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_chakra_sanctuary_heal_AuraScript::HandlePeriodicDummy, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pri_chakra_sanctuary_heal_SpellScript();
    }

    AuraScript* GetAuraScript() const
    {
        return new spell_pri_chakra_sanctuary_heal_AuraScript();
    }
};

class ShadowOrbBaseCalculationScript : public SpellScript
{
protected:
    bool Load()
    {
        return (GetCaster()->GetTypeId() == TYPEID_PLAYER);
    }

    void HandleShadowOrbs(SpellEffIndex /*effIndex*/)
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            if (Aura* aura = player->GetAura(SPELL_PRIEST_SHADOW_ORB_STACK_MARKER))
            {
                int32 bp0 = 5;
                bp0 += bp0 + (1.45 * player->GetFloatValue(PLAYER_MASTERY));
                SetHitDamage(GetHitDamage());
                player->CastCustomSpell(player, SPELL_PRIEST_EMPOWERED_SHADOW, &bp0, &bp0, NULL, true);
                aura->Remove();
            }
        }
    }
};

// 73510 Mind Spike
/// Updated 4.0.6
class spell_pri_mind_spike : public SpellScriptLoader
{
    public:
        spell_pri_mind_spike() : SpellScriptLoader("spell_pri_mind_spike") { }

        class spell_pri_mind_spike_SpellScript : public ShadowOrbBaseCalculationScript
        {
            PrepareSpellScript(spell_pri_mind_spike_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* target = GetHitUnit();

                if (!target)
                    return;

                target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, GetCaster()->GetGUID());
                target->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH, GetCaster()->GetGUID());
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_mind_spike_SpellScript::HandleShadowOrbs, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHitTarget += SpellEffectFn(spell_pri_mind_spike_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mind_spike_SpellScript;
        }
};

// 8092 Mind Blast
/// Updated 4.0.6
class spell_pri_mind_blast : public SpellScriptLoader
{
    public:
        spell_pri_mind_blast() : SpellScriptLoader("spell_pri_mind_blast") { }

        class spell_pri_mind_blast_SpellScript : public ShadowOrbBaseCalculationScript
        {
            PrepareSpellScript(spell_pri_mind_blast_SpellScript);

            void HandleAfterHit()
            {
                Unit* target = GetHitUnit();
                Unit* caster = GetCaster();

                if (!caster || !target)
                    return;

                // Remove Mind Spike debuff
                target->RemoveAurasDueToSpell(87178, GetCaster()->GetGUID());

                // Improved Mind blast - Mind Trauma cast
                if (AuraEffect* improvedMindBlast = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 95, EFFECT_1))
                    if (caster->GetShapeshiftForm() == FORM_SHADOW)
                        if (roll_chance_i(improvedMindBlast->GetAmount()))
                            caster->CastSpell(target, 48301, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_mind_blast_SpellScript::HandleShadowOrbs, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                AfterHit += SpellHitFn(spell_pri_mind_blast_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mind_blast_SpellScript;
        }
};

// 589 Shadow Word Pain (Needed for Shadowy Apparition)
/// Updated 4.3.4
class spell_pri_shadow_word_pain: public SpellScriptLoader
{
public:
    spell_pri_shadow_word_pain() : SpellScriptLoader("spell_pri_shadow_word_pain") {}

    class spell_pri_shadow_word_pain_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_shadow_word_pain_AuraScript);

        bool Load()
        {
            return (GetCaster() && (GetCaster()->GetTypeId() == TYPEID_PLAYER));
        }

        void HandlePeriodicDamage(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return;

            uint32 chance = 0;

            if (caster->HasAura(SPELL_PRIEST_SHADOWY_APPARITION_R3))
                chance = 3;
            else if (caster->HasAura(SPELL_PRIEST_SHADOWY_APPARITION_R1))
                chance = 2;
            else if (caster->HasAura(SPELL_PRIEST_SHADOWY_APPARITION_R2))
                chance = 1;
            else
                return;

            // Let your Apparitions reattack the owner if they have no target
            std::list<Creature*> unitList;
            caster->GetCreatureListWithEntryInGrid(unitList, PRIEST_NPC_SHADOWY_APPARITION, 50.0f);
            uint32 apparitionsCount = 0;

            for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                if ((*itr)->GetOwnerGUID() == caster->GetGUID())
                    ++apparitionsCount;

            if (apparitionsCount >= 4)
                return;

            // Calculate percentage and summon Apparition
            if (caster->isMoving())
                chance *= 20;
            else
                chance *= 4;

            if (roll_chance_i(chance))
            {
                caster->CastSpell(caster, SPELL_PRIEST_SHADOWY_APPARITION_SUMMON, true);

                UnitList targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(caster, 25.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                caster->VisitNearbyObject(25.0f, searcher);
                for (UnitList::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr))
                    {
                        if ((*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == 46954 && (*itr)->GetCharmerOrOwner() == caster)
                        {
                            // Already selected
                            if ((*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                continue;

                            (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            (*itr)->SetWalk(true);
                            (*itr)->ToCreature()->AddThreat(target, 100000.0f);
                            (*itr)->ToCreature()->Attack(target, false);
                            (*itr)->AddThreat(target, 10000.0f);
                            (*itr)->GetMotionMaster()->Clear();
                            (*itr)->GetMotionMaster()->MoveChase(target, 1.0f, 0.0f);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_shadow_word_pain_AuraScript::HandlePeriodicDamage, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pri_shadow_word_pain_AuraScript();
    }
};

class spell_pri_archangel : public SpellScriptLoader
{
public:
    spell_pri_archangel() : SpellScriptLoader("spell_pri_archangel") { }

    class spell_pri_archangel_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_archangel_SpellScript);

        void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (Aura* evangelism = caster->GetAura(SPELL_PRIEST_EVANGELISM))
            {
                int32 bp = int32(evangelism->GetStackAmount());
                caster->CastCustomSpell(caster, SPELL_PRIEST_ARCHANGEL, &bp, NULL, NULL, true, 0, 0, caster->GetGUID());
                bp = 3 * evangelism->GetStackAmount();
                caster->CastCustomSpell(caster, SPELL_PRIEST_ARCHANGEL_2, &bp, NULL, NULL, true, 0, 0, caster->GetGUID());
                caster->RemoveAurasDueToSpell(SPELL_PRIEST_EVANGELISM);
            }
            else if (Aura* darkEvangelism = caster->GetAura(SPELL_PRIEST_DARK_EVANGELISM))
            {
                int32 bp = 5 * int32(darkEvangelism->GetStackAmount());
                caster->CastCustomSpell(caster, SPELL_PRIEST_ARCHANGEL, &bp, NULL, NULL, true, 0, 0, caster->GetGUID());
                bp = 4 * darkEvangelism->GetStackAmount();
                caster->CastCustomSpell(caster, SPELL_PRIEST_DARK_ARCHANGEL, &bp, &bp, NULL, true, 0, 0, caster->GetGUID());
                caster->RemoveAurasDueToSpell(SPELL_PRIEST_DARK_EVANGELISM);
            }

            caster->RemoveAurasDueToSpell(SPELL_PRIEST_EVANGELISM_2);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pri_archangel_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pri_archangel_SpellScript;
    }
};

// 81781 Power Word: Barrier
// Updated 4.3.4
class spell_pri_power_word_barrier: public SpellScriptLoader
{
public:
    spell_pri_power_word_barrier() : SpellScriptLoader("spell_pri_power_word_barrier") {}

    class spell_pri_power_word_barrier_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_power_word_barrier_AuraScript);

        // if the owner of the caster has not the glyph for power word: barrier prevent the glyph effect (1),
        // if he has the glyphe remove the spellscript and the effect is applied
        bool Load()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* me = caster->ToCreature())
                {
                    if (Unit* owner = me->GetOwner())
                    {
                        if (owner->GetTypeId() == TYPEID_PLAYER && owner->HasAura(SPELL_PRIEST_GLYPH_POWER_WORD_BARRIER))
                            return false;
                    }
                }
            }
            return true;
        }

        void HandlePeriodicTriggerSpell(AuraEffect const* aurEff)
        {
            PreventDefaultAction();
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_power_word_barrier_AuraScript::HandlePeriodicTriggerSpell, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pri_power_word_barrier_AuraScript();
    }
};

// 77485 Echo of Light
// Updated 4.3.4
class spell_pri_echo_of_light : public SpellScriptLoader
{
public:
    spell_pri_echo_of_light() : SpellScriptLoader("spell_pri_echo_of_light") { }

    class spell_pri_echo_of_light_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_echo_of_light_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_PRIEST_ECHO_OF_LIGHT_EFFECT);
        }

        void HandleProc(ProcEventInfo& info)
        {
            Unit* target = info.GetActionTarget();
            Unit* caster = GetCaster();
            if (!caster || !target || !info.GetHealInfo()->GetHeal())
                return;

            int32 bp0 = info.GetHealInfo()->GetHeal() * (GetEffect(EFFECT_0)->GetAmount() / 100.f);
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PRIEST_ECHO_OF_LIGHT_EFFECT))
            {
                bp0 /= spellInfo->GetDuration() / spellInfo->Effects[EFFECT_0].Amplitude;
                if (AuraEffect* aurEff = target->GetAuraEffect(SPELL_PRIEST_ECHO_OF_LIGHT_EFFECT, EFFECT_0, caster->GetGUID()))
                {
                    uint32 remainingAmount = aurEff->GetAmount();
                    uint32 tickNumber = aurEff->GetTickNumber();
                    if (tickNumber > 0 && remainingAmount > 0)
                    {
                        remainingAmount /= tickNumber;
                        aurEff->SetAmount(aurEff->GetAmount() + remainingAmount);
                        aurEff->GetBase()->RefreshDuration();
                    }
                    return;
                }
                else
                    caster->CastCustomSpell(target, SPELL_PRIEST_ECHO_OF_LIGHT_EFFECT, &bp0, NULL, NULL, true);
            }
        }

        void Register()
        {
            OnProc += AuraProcFn(spell_pri_echo_of_light_AuraScript::HandleProc);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pri_echo_of_light_AuraScript();
    }
};

// 64127 & 64129 Body and Soul
// Updated 4.3.4
class spell_pri_body_and_soul : public SpellScriptLoader
{
public:
    spell_pri_body_and_soul() : SpellScriptLoader("spell_pri_body_and_soul") { }

    class spell_pri_body_and_soul_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_body_and_soul_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_SPEED_INCREASE_R1)
                && sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_DISPEL)
                && sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_SPEED_INCREASE_R2);
        }

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleSpeedProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            if (Unit* owner = GetCaster())
            {
                if (Unit* target = eventInfo.GetActionTarget())
                {
                    if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_PRIEST_POWER_WORD_SHIELD || eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_PRIEST_LEAP_OF_FAITH)
                    {
                        if (owner->HasAura(SPELL_PRIEST_BODY_AND_SOUL_R1))
                            owner->CastSpell(target, SPELL_PRIEST_BODY_AND_SOUL_SPEED_INCREASE_R1, TRIGGERED_FULL_MASK, NULL, aurEff);
                        else if (owner->HasAura(SPELL_PRIEST_BODY_AND_SOUL_R2))
                            owner->CastSpell(target, SPELL_PRIEST_BODY_AND_SOUL_SPEED_INCREASE_R2, TRIGGERED_FULL_MASK, NULL, aurEff);
                    }
                }
            }
        }

        void HandleDispelProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            if (Unit* owner = GetCaster())
                if (Unit* target = eventInfo.GetActionTarget())
                    if (owner == target && eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_PRIEST_CURE_DISEASE &&
                        roll_chance_i(aurEff->GetAmount()))
                            owner->CastSpell(target, SPELL_PRIEST_BODY_AND_SOUL_DISPEL, TRIGGERED_FULL_MASK, NULL, aurEff);
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_pri_body_and_soul_AuraScript::HandleSpeedProc, EFFECT_0, SPELL_AURA_DUMMY);
            OnEffectProc += AuraEffectProcFn(spell_pri_body_and_soul_AuraScript::HandleDispelProc, EFFECT_1, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pri_body_and_soul_AuraScript();
    }
};

// 20711 Spirit of Redemption
// Upated 4.3.4
class spell_pri_spirit_of_redemption : public SpellScriptLoader
{
    public:
        spell_pri_spirit_of_redemption() : SpellScriptLoader("spell_pri_spirit_of_redemption") { }

        class spell_pri_spirit_of_redemption_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_spirit_of_redemption_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                return sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK)
                    && sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK1)
                    && sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK2)
                    && sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK3);
            }

            bool Load()
            {
                return GetOwner()->GetTypeId() == TYPEID_PLAYER;
            }

            void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                absorbAmount = 0;
                Unit* target = GetTarget();
                if (dmgInfo.GetDamage() < target->GetHealth())
                    return;

                if (target->HasAura(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK1, target->GetGUID()))
                    return;

                absorbAmount = dmgInfo.GetDamage();

                target->CastSpell(target, SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK,  TRIGGERED_FULL_MASK);
                target->CastSpell(target, SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK1, TRIGGERED_FULL_MASK);
                target->CastSpell(target, SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK2, TRIGGERED_FULL_MASK);
                target->CastSpell(target, SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK3, TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_spirit_of_redemption_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_spirit_of_redemption_AuraScript();
        }
};

// 27827 Spirit of Redemption
// Updated 4.3.4
class spell_pri_spirit_of_redemption_kill : public SpellScriptLoader
{
    public:
        spell_pri_spirit_of_redemption_kill() : SpellScriptLoader("spell_pri_spirit_of_redemption_kill") { }

        class spell_pri_spirit_of_redemption_kill_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_spirit_of_redemption_kill_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                return sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK)
                    && sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK1)
                    && sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK2)
                    && sSpellMgr->GetSpellInfo(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK3);
            }

            bool Load()
            {
                return GetOwner()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (!(mode & AURA_EFFECT_HANDLE_REAL))
                    return;

                if (Unit* target = GetTarget())
                {
                    target->SetControlled(true, UNIT_STATE_ROOT);
                    target->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL, true);
                    target->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL_PCT, true);
                    target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1|UNIT_FLAG_NOT_SELECTABLE);
                    target->SetHealth(target->GetMaxHealth());
                    target->SetPower(POWER_MANA, target->GetMaxPower(POWER_MANA));
                }
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (!(mode & AURA_EFFECT_HANDLE_REAL))
                    return;

                if (Unit* target = GetTarget())
                {
                    target->SetControlled(false, UNIT_STATE_ROOT);
                    target->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL, false);
                    target->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL_PCT, false);
                    target->RemoveAura(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK, target->GetGUID());
                    target->RemoveAura(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK2, target->GetGUID());
                    target->RemoveAura(SPELL_PRIEST_SPIRIT_OF_REDEMPTION_UNK3, target->GetGUID());
                    target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1|UNIT_FLAG_NOT_SELECTABLE);
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_pri_spirit_of_redemption_kill_AuraScript::HandleEffectApply, EFFECT_2, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_pri_spirit_of_redemption_kill_AuraScript::HandleEffectRemove, EFFECT_2, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_spirit_of_redemption_kill_AuraScript();
        }
};
// 14523 Atonement (Rank 1)
// 81749 Atonement (Rank 2)
// Upgraded 4.3.4
class spell_pri_atonement : public SpellScriptLoader
{
public:
    spell_pri_atonement() : SpellScriptLoader("spell_pri_atonement") { }

    class spell_pri_atonement_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_atonement_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_PRIEST_ATONEMENT);
        }

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            if (Unit* owner = GetCaster())
            {
                uint32 bp_frac = eventInfo.GetHealInfo()->GetHeal();
                bp_frac = CalculatePct(bp_frac, aurEff->GetAmount());
                int32 bp = bp_frac;
                bp -= bp * 0.061835f;

                if (bp != 0.0f)
                    owner->CastCustomSpell(owner, SPELL_PRIEST_ATONEMENT, &bp, NULL, NULL, true, NULL, aurEff);
            }
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_pri_atonement_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pri_atonement_AuraScript();
    }
};

// 81751 Atonement
// Upgraded 4.3.4
class spell_pri_atonement_heal : public SpellScriptLoader
{
public:
    spell_pri_atonement_heal() : SpellScriptLoader("spell_pri_atonement_heal") { }

    class spell_pri_atonement_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_atonement_heal_SpellScript);

        class ComparePlayersHealth
        {
        public:
            bool operator() (Player*& l, Player*& r) const
            {
                return l->GetHealthPct() < r->GetHealthPct();
            }
        };

        void SelectTarget(std::list<WorldObject*>& targets)
        {
            // Prefer a target that has low health
            std::priority_queue<Player*, std::vector<Player*>, ComparePlayersHealth> lowestHpTargets;
            for (auto const i : targets)
                if (i->GetTypeId() == TYPEID_PLAYER)
                    lowestHpTargets.push(i->ToPlayer());

            targets.clear();

            while (!roll_chance_i(70) && lowestHpTargets.size() > 1)
                lowestHpTargets.pop();

            if (!lowestHpTargets.empty())
                targets.push_back(lowestHpTargets.top());
        }

        void HandleEffectHit(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster() == GetHitUnit())
                SetHitHeal(GetHitHeal() / 2);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_atonement_heal_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_pri_atonement_heal_SpellScript::HandleEffectHit, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pri_atonement_heal_SpellScript();
    }
};

// 89490 Strength of Soul
class spell_pri_strength_of_soul : public SpellScriptLoader
{
    public:
        spell_pri_strength_of_soul() : SpellScriptLoader("spell_pri_strength_of_soul") { }

        class spell_pri_strength_of_soul_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_strength_of_soul_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetOriginalCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (Aura* aura = target->GetAura(SPELL_PRIEST_WEAKENED_SOUl, caster->GetGUID()))
                        {
                            if (AuraEffect const* auraEffect = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_PRIEST, PRIEST_ICON_ID_STRENGTH_OF_SOUL, EFFECT_0))
                            {
                                int32 const reduce = auraEffect->GetAmount() * 1000;
                                if (aura->GetDuration() < reduce)
                                    aura->Remove();
                                else
                                    aura->SetDuration(aura->GetDuration() - reduce);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_strength_of_soul_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_strength_of_soul_SpellScript;
        }
};

// 586 - Fade
class spell_pri_fade : public SpellScriptLoader
{
    public:
        spell_pri_fade() : SpellScriptLoader("spell_pri_fade") { }

        class spell_pri_fade_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_fade_SpellScript);

            void CheckPhantasmTalent(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    // Phantasm
                    if (target->HasAura(SPELL_PRIEST_PHANTASM_R2) || (target->HasAura(SPELL_PRIEST_PHANTASM_R1) && roll_chance_i(50)))
                        target->RemoveMovementImpairingAuras();
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_fade_SpellScript::CheckPhantasmTalent, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_fade_SpellScript;
        }
};

// 14914 - Holy Fire
class spell_pri_holy_fire : public SpellScriptLoader
{
    public:
        spell_pri_holy_fire() : SpellScriptLoader("spell_pri_holy_fire") { }

        class spell_pri_holy_fire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_holy_fire_SpellScript);

            void HandleEvangelism(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (caster->HasAura(SPELL_PRIEST_EVANGELISM_R1))
                            caster->CastSpell(caster, SPELL_PRIEST_EVANGELISM_EFFECT_R1, true);
                        else if (caster->HasAura(SPELL_PRIEST_EVANGELISM_R2))
                            caster->CastSpell(caster, SPELL_PRIEST_EVANGELISM_EFFECT_R2, true);

                        if (Aura* evangelism = target->GetAura(SPELL_PRIEST_EVANGELISM_2))
                            evangelism->RefreshDuration();
                        else
                            caster->AddAura(87154, caster);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_holy_fire_SpellScript::HandleEvangelism, EFFECT_1, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_holy_fire_SpellScript;
        }
};

// 32592 - Mass Dispel
class spell_pri_mass_dispel : public SpellScriptLoader
{
public:
    spell_pri_mass_dispel() : SpellScriptLoader("spell_pri_mass_dispel") { }

    class spell_pri_mass_dispel_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_mass_dispel_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                if(target->HasAura(51755))
                    target->RemoveAura(51755);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pri_mass_dispel_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DISPEL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pri_mass_dispel_SpellScript();
    }
};

class spell_pri_mind_control : public SpellScriptLoader
{
    public:
        spell_pri_mind_control() : SpellScriptLoader("spell_pri_mind_control") { }

        class spell_pri_mind_control_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_mind_control_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                        {
                            target->GetMotionMaster()->Clear();
                            target->AttackStop();
                            target->ClearInCombat();
                        }
                    }
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (target->GetTypeId() != TYPEID_PLAYER)
                    {
                        target->GetMotionMaster()->Clear();
                        target->GetMotionMaster()->InitDefault();
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_pri_mind_control_AuraScript::OnApply, EFFECT_2, SPELL_AURA_MOD_MELEE_HASTE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_pri_mind_control_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_MOD_MELEE_HASTE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_mind_control_AuraScript();
        }
};

class spell_pri_vampiric_embrace : public SpellScriptLoader
{
    public:
        spell_pri_vampiric_embrace() : SpellScriptLoader("spell_pri_vampiric_embrace") { }

        class spell_pri_vampiric_embrace_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_vampiric_embrace_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (GetCaster())
                    unitList.remove(GetCaster());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_vampiric_embrace_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_vampiric_embrace_SpellScript();
        }
};

class spell_pri_inner_fire : public SpellScriptLoader
{
    public:
        spell_pri_inner_fire() : SpellScriptLoader("spell_pri_inner_fire") { }

        enum spellId
        {
            SPELL_INNER_SANCTUM_SPELL_WARDING   = 91724
        };

        class spell_pri_inner_fire_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_inner_fire_AuraScript);

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    // Inner Sanctum
                    if (AuraEffect* aurEff = target->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 51, EFFECT_0))
                    {
                        int32 bp0 = -aurEff->GetAmount();
                        target->CastCustomSpell(target, SPELL_INNER_SANCTUM_SPELL_WARDING, &bp0, NULL, NULL, true);
                    }
                }
           }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (target->HasAura(SPELL_INNER_SANCTUM_SPELL_WARDING))
                        target->RemoveAurasDueToSpell(SPELL_INNER_SANCTUM_SPELL_WARDING);
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_pri_inner_fire_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_RESISTANCE_PCT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_pri_inner_fire_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_RESISTANCE_PCT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_inner_fire_AuraScript();
        }
};

class spell_pri_inner_focus : public SpellScriptLoader
{
    public:
        spell_pri_inner_focus() : SpellScriptLoader("spell_pri_inner_focus") { }

        enum spellId
        {
            SPELL_STRENGTH_OF_SOUL_IMMUNITY     = 96267
        };

        class spell_pri_inner_focus_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_inner_focus_AuraScript);

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                // Strength of Soul
                if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_PRIEST, 177, 0))
                {
                    if (Unit* caster = GetCaster())
                        caster->CastSpell(caster, SPELL_STRENGTH_OF_SOUL_IMMUNITY, true);
                }
            }
            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_pri_inner_focus_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_inner_focus_AuraScript();
        }
};

void AddSC_priest_spell_scripts()
{
    new spell_pri_divine_aegis();
    new spell_pri_glyph_of_prayer_of_healing();
    new spell_pri_guardian_spirit();
    new spell_pri_leap_of_faith_effect_trigger();
    new spell_pri_lightwell_renew();
    new spell_pri_mana_burn();
    new spell_pri_mana_leech();
    new spell_pri_mind_sear();
    new spell_pri_pain_and_suffering_proc();
    new spell_pri_penance();
    new spell_pri_power_word_shield();
    new spell_pri_prayer_of_mending_heal();
    new spell_pri_renew();
    new spell_pri_shadow_word_death();
    new spell_pri_shadowform();
    new spell_pri_chakra_swap_supressor();
    new spell_pri_chakra_serenity_proc();
    new spell_pri_chakra_sanctuary_heal();
    new spell_pri_mind_spike();
    new spell_pri_mind_blast();
    new spell_pri_shadow_word_pain();
    new spell_pri_archangel();
    new spell_pri_power_word_barrier();
    new spell_pri_echo_of_light();
    new spell_pri_body_and_soul();
    new spell_pri_spirit_of_redemption();
    new spell_pri_spirit_of_redemption_kill();
    new spell_pri_atonement();
    new spell_pri_atonement_heal();
    new spell_pri_strength_of_soul();
    new spell_pri_fade();
    new spell_pri_holy_fire();
    new spell_pri_mass_dispel();
    new spell_pri_mind_control();
    new spell_pri_vampiric_embrace();
    new spell_pri_inner_fire();
    new spell_pri_inner_focus();
}
