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
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"

enum DruidSpells
{
    SPELL_DRUID_WRATH                       = 5176,
    SPELL_DRUID_STARFIRE                    = 2912,
    SPELL_DRUID_STARSURGE                   = 78674,
    SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE    = 89265,
    SPELL_DRUID_STARSURGE_ENERGIZE          = 86605,
    SPELL_DRUID_LUNAR_ECLIPSE_MARKER        = 67484, // Will make the yellow arrow on eclipse bar point to the blue side (lunar)
    SPELL_DRUID_SOLAR_ECLIPSE_MARKER        = 67483, // Will make the yellow arrow on eclipse bar point to the yellow side (solar)
    SPELL_DRUID_SOLAR_ECLIPSE               = 48517,
    SPELL_DRUID_LUNAR_ECLIPSE               = 48518,
    SPELL_DRUID_MOONFIRE                    = 8921,
    SPELL_DRUID_SUNFIRE                     = 93402,
    SPELL_DRUID_ENRAGE_MOD_DAMAGE           = 51185,
    SPELL_DRUID_GLYPH_OF_TYPHOON            = 62135,
    SPELL_DRUID_IDOL_OF_FERAL_SHADOWS       = 34241,
    SPELL_DRUID_IDOL_OF_WORSHIP             = 60774,
    SPELL_DRUID_INCREASED_MOONFIRE_DURATION = 38414,
    SPELL_DRUID_KING_OF_THE_JUNGLE          = 48492,
    SPELL_DRUID_LIFEBLOOM_ENERGIZE          = 64372,
    SPELL_DRUID_LIFEBLOOM_FINAL_HEAL        = 33778,
    SPELL_DRUID_LIVING_SEED_HEAL            = 48503,
    SPELL_DRUID_LIVING_SEED_PROC            = 48504,
    SPELL_DRUID_NATURES_SPLENDOR            = 57865,
    SPELL_DRUID_SURVIVAL_INSTINCTS          = 50322,
    SPELL_DRUID_SAVAGE_ROAR                 = 62071,
    SPELL_DRUID_TIGER_S_FURY_ENERGIZE       = 51178,
    SPELL_DRUID_ITEM_T8_BALANCE_RELIC       = 64950,
    DRUID_NPC_WILD_MUSHROOM                 = 47649,
    DRUID_NPC_FUNGAL_GROWTH_1               = 43497,
    DRUID_NPC_FUNGAL_GROWTH_2               = 43484,
    DRUID_TALENT_FUNGAL_GROWTH_1            = 78788,
    DRUID_TALENT_FUNGAL_GROWTH_2            = 78789,
    DRUID_SPELL_FUNGAL_GROWTH_1             = 81291,
    DRUID_SPELL_FUNGAL_GROWTH_2             = 81283,
    DRUID_SPELL_WILD_MUSHROOM_SUICIDE       = 92853,
    DRUID_SPELL_WILD_MUSHROOM_DAMAGE        = 78777,
    DRUID_SPELL_REGROWTH                    = 8936,
    DRUID_SPELL_REGROWTH_REFRESH            = 93036
};

// 2912, 5176, 78674 - Starfire, Wrath, and Starsurge
class spell_dru_eclipse_energize : public SpellScriptLoader
{
public:
    spell_dru_eclipse_energize() : SpellScriptLoader("spell_dru_eclipse_energize") { }

    class spell_dru_eclipse_energize_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_eclipse_energize_SpellScript);

        int32 energizeAmount;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_DRUID)
                return false;

            energizeAmount = 0;

            return true;
        }

        void HandleEnergize(SpellEffIndex effIndex)
        {
            if(!GetCaster())
                return;

            Player* caster = GetCaster()->ToPlayer();
            if (!caster)
                return;

            // No boomy, no deal.
            if (caster->GetPrimaryTalentTree(caster->GetActiveSpec()) != TALENT_TREE_DRUID_BALANCE)
                return;

            switch (GetSpellInfo()->Id)
            {
                case SPELL_DRUID_WRATH:
                {
                    if (caster->HasAura(48518))
                        return;

                    energizeAmount = -GetSpellInfo()->Effects[effIndex].BasePoints; // -13

                    // Euphoria
                    if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_DRUID, 4431, 0))
                    {
                        if (!caster->HasAura(48517))
                        {
                            if (roll_chance_i(aurEff->GetAmount()))
                                energizeAmount *= 2;
                        }
                    }

                    // If we are set to fill the lunar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster, SPELL_DRUID_LUNAR_ECLIPSE_MARKER, true);
                    }
                    // The energizing effect brought us out of the solar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) <= 0)
                    {
                        caster->RemoveAurasDueToSpell(SPELL_DRUID_SOLAR_ECLIPSE);
                        caster->RemoveAura(94338);
                    }
                    break;
                }
                case SPELL_DRUID_STARFIRE:
                {
                    if (caster->HasAura(48517) || caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                        return;

                    energizeAmount = GetSpellInfo()->Effects[effIndex].BasePoints; // 20

                    // Euphoria
                    if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_DRUID, 4431, 0))
                    {
                        if (!caster->HasAura(48518))
                        {
                            if (roll_chance_i(aurEff->GetAmount()))
                                energizeAmount *= 2;
                        }
                    }

                    // If we are set to fill the solar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        caster->CastCustomSpell(caster, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, &energizeAmount, 0, 0, true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster, SPELL_DRUID_SOLAR_ECLIPSE_MARKER, true);
                    }
                    // The energizing effect brought us out of the lunar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) >= 0)
                        caster->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);

                    // Operation done the the Druid reaches 100 Solar Energy with starfire
                    if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) == 100)
                    {
                        caster->CastSpell(caster, SPELL_DRUID_SOLAR_ECLIPSE, true);
                        caster->RemoveAurasDueToSpell(SPELL_DRUID_SOLAR_ECLIPSE_MARKER);
                        caster->CastSpell(caster, SPELL_DRUID_LUNAR_ECLIPSE_MARKER, true);

                        // Sunfire
                        if (AuraEffect* aura = caster->GetDummyAuraEffect(SPELLFAMILY_DRUID, 3262, 0))
                            caster->CastSpell(caster, 94338, true);
                    }
                    break;
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_eclipse_energize_SpellScript::HandleEnergize, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_eclipse_energize_SpellScript;
    }
};

// -1850 - Dash
class spell_dru_dash : public SpellScriptLoader
{
    public:
        spell_dru_dash() : SpellScriptLoader("spell_dru_dash") { }

        class spell_dru_dash_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_dash_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                // do not set speed if not in cat form
                if (GetUnitOwner()->GetShapeshiftForm() != FORM_CAT)
                    amount = 0;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_dash_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_dash_AuraScript();
        }
};

// -5229 - Enrage
class spell_dru_enrage : public SpellScriptLoader
{
    public:
        spell_dru_enrage() : SpellScriptLoader("spell_dru_enrage") { }

        class spell_dru_enrage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_enrage_SpellScript);

            void OnHit()
            {
                if (AuraEffect const* aurEff = GetHitUnit()->GetAuraEffectOfRankedSpell(SPELL_DRUID_KING_OF_THE_JUNGLE, EFFECT_0))
                    GetHitUnit()->CastCustomSpell(SPELL_DRUID_ENRAGE_MOD_DAMAGE, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), GetHitUnit(), true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_dru_enrage_SpellScript::OnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_enrage_SpellScript();
        }
};

// 34246 - Idol of the Emerald Queen
// 60779 - Idol of Lush Moss
class spell_dru_idol_lifebloom : public SpellScriptLoader
{
    public:
        spell_dru_idol_lifebloom() : SpellScriptLoader("spell_dru_idol_lifebloom") { }

        class spell_dru_idol_lifebloom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_idol_lifebloom_AuraScript);

            void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
            {
                if (!spellMod)
                {
                    spellMod = new SpellModifier(GetAura());
                    spellMod->op = SPELLMOD_DOT;
                    spellMod->type = SPELLMOD_FLAT;
                    spellMod->spellId = GetId();
                    spellMod->mask = GetSpellInfo()->Effects[aurEff->GetEffIndex()].SpellClassMask;
                }
                spellMod->value = aurEff->GetAmount() / 7;
            }

            void Register()
            {
                DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_dru_idol_lifebloom_AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_idol_lifebloom_AuraScript();
        }
};

// 29166 - Innervate
// Updated - 4.3.4
class spell_dru_innervate : public SpellScriptLoader
{
    public:
        spell_dru_innervate() : SpellScriptLoader("spell_dru_innervate") { }

        class spell_dru_innervate_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_innervate_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (GetUnitOwner() && GetUnitOwner()->GetTypeId() == TYPEID_PLAYER)
                        amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.05f / aurEff->GetTotalTicks();

                    // Additional 15% of amount if target is caster
                    if (GetUnitOwner() && GetUnitOwner() == GetCaster())
                        amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.20f / aurEff->GetTotalTicks();

                    // Dreamstate
                    if (caster->HasAura(33597))         // Dreamstate R1
                    {
                        if (GetUnitOwner() && GetUnitOwner() == GetCaster())
                            amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.35f / aurEff->GetTotalTicks();
                        else
                            amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.20f / aurEff->GetTotalTicks();
                    }
                    else if (caster->HasAura(33599))    // Dreamstate R2
                    {
                        if (GetUnitOwner() && GetUnitOwner() == GetCaster())
                            amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.50f / aurEff->GetTotalTicks();
                        else
                            amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.35f / aurEff->GetTotalTicks();
                    }

                    // Glyph of Innervate
                    if (caster->HasAura(54832) && GetUnitOwner() && GetUnitOwner() != GetCaster())
                        caster->CastSpell(caster, 54833, true);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_innervate_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_innervate_AuraScript();
        }
};

// -5570 - Insect Swarm
class spell_dru_insect_swarm : public SpellScriptLoader
{
    public:
        spell_dru_insect_swarm() : SpellScriptLoader("spell_dru_insect_swarm") { }

        class spell_dru_insect_swarm_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_insect_swarm_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect const* relicAurEff = caster->GetAuraEffect(SPELL_DRUID_ITEM_T8_BALANCE_RELIC, EFFECT_0))
                        amount += relicAurEff->GetAmount() / aurEff->GetTotalTicks();
                }
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_insect_swarm_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_insect_swarm_AuraScript();
        }
};

// -33763 - Lifebloom
class spell_dru_lifebloom : public SpellScriptLoader
{
    public:
        spell_dru_lifebloom() : SpellScriptLoader("spell_dru_lifebloom") { }

        class spell_dru_lifebloom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_lifebloom_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_LIFEBLOOM_FINAL_HEAL))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                // Final heal only on duration end
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                    return;

                // final heal
                int32 stack = GetStackAmount();
                int32 healAmount = aurEff->GetAmount();
                if (Unit* caster = GetCaster())
                {
                    healAmount = caster->SpellHealingBonusDone(GetTarget(), GetSpellInfo(), healAmount, HEAL, stack);
                    healAmount = GetTarget()->SpellHealingBonusTaken(caster, GetSpellInfo(), healAmount, HEAL, stack);

                    GetTarget()->CastCustomSpell(GetTarget(), SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
                    return;
                }

                GetTarget()->CastCustomSpell(GetTarget(), SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* target = GetUnitOwner())
                {
                    if (AuraEffect const* aurEff = GetEffect(EFFECT_1))
                    {
                        // final heal
                        int32 healAmount = aurEff->GetAmount();
                        if (Unit* caster = GetCaster())
                        {
                            healAmount = caster->SpellHealingBonusDone(target, GetSpellInfo(), healAmount, HEAL, dispelInfo->GetRemovedCharges());
                            healAmount = target->SpellHealingBonusTaken(caster, GetSpellInfo(), healAmount, HEAL, dispelInfo->GetRemovedCharges());
                            target->CastCustomSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, NULL, GetCasterGUID());

                            // restore mana
                            int32 returnMana = CalculatePct(caster->GetCreateMana(), GetSpellInfo()->ManaCostPercentage) * dispelInfo->GetRemovedCharges() / 2;
                            caster->CastCustomSpell(caster, SPELL_DRUID_LIFEBLOOM_ENERGIZE, &returnMana, NULL, NULL, true, NULL, NULL, GetCasterGUID());
                            return;
                        }

                        target->CastCustomSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, NULL, GetCasterGUID());
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_lifebloom_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterDispel += AuraDispelFn(spell_dru_lifebloom_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_lifebloom_AuraScript();
        }
};

// -48496 - Living Seed
class spell_dru_living_seed : public SpellScriptLoader
{
    public:
        spell_dru_living_seed() : SpellScriptLoader("spell_dru_living_seed") { }

        class spell_dru_living_seed_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_living_seed_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_LIVING_SEED_PROC))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                int32 amount = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), aurEff->GetAmount());
                GetTarget()->CastCustomSpell(SPELL_DRUID_LIVING_SEED_PROC, SPELLVALUE_BASE_POINT0, amount, eventInfo.GetProcTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_dru_living_seed_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_living_seed_AuraScript();
        }
};

// 48504 - Living Seed (Proc)
class spell_dru_living_seed_proc : public SpellScriptLoader
{
    public:
        spell_dru_living_seed_proc() : SpellScriptLoader("spell_dru_living_seed_proc") { }

        class spell_dru_living_seed_proc_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_living_seed_proc_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_LIVING_SEED_HEAL))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastCustomSpell(SPELL_DRUID_LIVING_SEED_HEAL, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), GetTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_dru_living_seed_proc_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_living_seed_proc_AuraScript();
        }
};

// 48391 - Owlkin Frenzy
class spell_dru_owlkin_frenzy : public SpellScriptLoader
{
    public:
        spell_dru_owlkin_frenzy() : SpellScriptLoader("spell_dru_owlkin_frenzy") { }

        class spell_dru_owlkin_frenzy_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_owlkin_frenzy_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = CalculatePct(GetUnitOwner()->GetCreatePowers(POWER_MANA), amount);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_owlkin_frenzy_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_PERIODIC_ENERGIZE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_owlkin_frenzy_AuraScript();
        }
};

// -16972 - Predatory Strikes
class spell_dru_predatory_strikes : public SpellScriptLoader
{
    public:
        spell_dru_predatory_strikes() : SpellScriptLoader("spell_dru_predatory_strikes") { }

        class spell_dru_predatory_strikes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_predatory_strikes_AuraScript);

            void UpdateAmount(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* target = GetTarget()->ToPlayer())
                    target->UpdateAttackPowerAndDamage();
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_predatory_strikes_AuraScript::UpdateAmount, EFFECT_ALL, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_predatory_strikes_AuraScript::UpdateAmount, EFFECT_ALL, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_predatory_strikes_AuraScript();
        }
};

// 33851 - Primal Tenacity
class spell_dru_primal_tenacity : public SpellScriptLoader
{
    public:
        spell_dru_primal_tenacity() : SpellScriptLoader("spell_dru_primal_tenacity") { }

        class spell_dru_primal_tenacity_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_primal_tenacity_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                // reduces all damage taken while Stunned in Cat Form
                if (GetTarget()->GetShapeshiftForm() == FORM_CAT && GetTarget()->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED) && GetTarget()->HasAuraWithMechanic(1<<MECHANIC_STUN))
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_primal_tenacity_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dru_primal_tenacity_AuraScript::Absorb, EFFECT_1);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_primal_tenacity_AuraScript();
        }
};

// -1079 - Rip
class spell_dru_rip : public SpellScriptLoader
{
    public:
        spell_dru_rip() : SpellScriptLoader("spell_dru_rip") { }

        class spell_dru_rip_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_rip_AuraScript);

            bool Load()
            {
                Unit* caster = GetCaster();
                return caster && caster->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = true;

                if (Unit* caster = GetCaster())
                {
                  /*1 point:  (56 + 161 * 1 + 0.0207 * AP) * 8 damage over 16 seconds.
                    2 points: (56 + 161 * 2 + 0.0414 * AP) * 8 damage over 16 seconds.
                    3 points: (56 + 161 * 3 + 0.0621 * AP) * 8 damage over 16 seconds.
                    4 points: (56 + 161 * 4 + 0.0828 * AP) * 8 damage over 16 seconds.
                    5 points: (56 + 161 * 5 + 0.1035 * AP) * 8 damage over 16 seconds.*/
                    uint8 cp = caster->ToPlayer()->GetComboPoints();
                    uint32 ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                    amount = uint32(56 + 161 * cp) + (0.0207 * cp * ap) * 8 / aurEff->GetTotalTicks();

                    // Idol of Feral Shadows. Can't be handled as SpellMod due its dependency from CPs
                    if (AuraEffect const* idol = caster->GetAuraEffect(SPELL_DRUID_IDOL_OF_FERAL_SHADOWS, EFFECT_0))
                        amount += cp * idol->GetAmount();
                    // Idol of Worship. Can't be handled as SpellMod due its dependency from CPs
                    else if (AuraEffect const* idol = caster->GetAuraEffect(SPELL_DRUID_IDOL_OF_WORSHIP, EFFECT_0))
                        amount += cp * idol->GetAmount();
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_rip_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_rip_AuraScript();
        }
};

// 52610 - Savage Roar
class spell_dru_savage_roar : public SpellScriptLoader
{
    public:
        spell_dru_savage_roar() : SpellScriptLoader("spell_dru_savage_roar") { }

        class spell_dru_savage_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_savage_roar_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (caster->GetShapeshiftForm() != FORM_CAT)
                    return SPELL_FAILED_ONLY_SHAPESHIFT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_savage_roar_SpellScript::CheckCast);
            }
        };

        class spell_dru_savage_roar_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_savage_roar_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_SAVAGE_ROAR))
                    return false;
                return true;
            }

            void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->CastSpell(target, SPELL_DRUID_SAVAGE_ROAR, true, NULL, aurEff, GetCasterGUID());
            }

            void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_SAVAGE_ROAR);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_savage_roar_AuraScript::AfterApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_savage_roar_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_savage_roar_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_savage_roar_AuraScript();
        }
};

// -50294 - Starfall (AOE)
class spell_dru_starfall_aoe : public SpellScriptLoader
{
    public:
        spell_dru_starfall_aoe() : SpellScriptLoader("spell_dru_starfall_aoe") { }

        class spell_dru_starfall_aoe_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_starfall_aoe_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove(GetExplTargetUnit());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_starfall_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_starfall_aoe_SpellScript();
        }
};

// -50286 - Starfall (Dummy)
class spell_dru_starfall_dummy : public SpellScriptLoader
{
    public:
        spell_dru_starfall_dummy() : SpellScriptLoader("spell_dru_starfall_dummy") { }

        class spell_dru_starfall_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_starfall_dummy_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Trinity::Containers::RandomResizeList(targets, 2);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                // Shapeshifting into an animal form or mounting cancels the effect
                if (caster->GetCreatureType() == CREATURE_TYPE_BEAST || caster->IsMounted())
                {
                    if (SpellInfo const* spellInfo = GetTriggeringSpell())
                        caster->RemoveAurasDueToSpell(spellInfo->Id);
                    return;
                }

                // Any effect which causes you to lose control of your character will supress the starfall effect.
                if (caster->HasUnitState(UNIT_STATE_CONTROLLED))
                    return;

                caster->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_starfall_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_dru_starfall_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_starfall_dummy_SpellScript();
        }
};

// 61336 - Survival Instincts
class spell_dru_survival_instincts : public SpellScriptLoader
{
    public:
        spell_dru_survival_instincts() : SpellScriptLoader("spell_dru_survival_instincts") { }

        class spell_dru_survival_instincts_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_survival_instincts_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (!caster->IsInFeralForm())
                    return SPELL_FAILED_ONLY_SHAPESHIFT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_survival_instincts_SpellScript::CheckCast);
            }
        };

        class spell_dru_survival_instincts_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_survival_instincts_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_SURVIVAL_INSTINCTS))
                    return false;
                return true;
            }

            void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                int32 bp0 = -aurEff->GetAmount();
                target->CastCustomSpell(target, SPELL_DRUID_SURVIVAL_INSTINCTS, &bp0, NULL, NULL, true);
            }

            void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_SURVIVAL_INSTINCTS);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_survival_instincts_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_survival_instincts_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_survival_instincts_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_survival_instincts_AuraScript();
        }
};

// 40121 - Swift Flight Form (Passive)
class spell_dru_swift_flight_passive : public SpellScriptLoader
{
    public:
        spell_dru_swift_flight_passive() : SpellScriptLoader("spell_dru_swift_flight_passive") { }

        class spell_dru_swift_flight_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_swift_flight_passive_AuraScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                        amount = 310;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_swift_flight_passive_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_swift_flight_passive_AuraScript();
        }
};

// -5217 - Tiger's Fury
class spell_dru_tiger_s_fury : public SpellScriptLoader
{
    public:
        spell_dru_tiger_s_fury() : SpellScriptLoader("spell_dru_tiger_s_fury") { }

        class spell_dru_tiger_s_fury_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_tiger_s_fury_SpellScript);

            void OnHit()
            {
                if (AuraEffect const* aurEff = GetHitUnit()->GetAuraEffectOfRankedSpell(SPELL_DRUID_KING_OF_THE_JUNGLE, EFFECT_1))
                    GetHitUnit()->CastCustomSpell(SPELL_DRUID_TIGER_S_FURY_ENERGIZE, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), GetHitUnit(), true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_dru_tiger_s_fury_SpellScript::OnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_tiger_s_fury_SpellScript();
        }
};

// -61391 - Typhoon
class spell_dru_typhoon : public SpellScriptLoader
{
    public:
        spell_dru_typhoon() : SpellScriptLoader("spell_dru_typhoon") { }

        class spell_dru_typhoon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_typhoon_SpellScript);

            void HandleKnockBack(SpellEffIndex effIndex)
            {
                // Glyph of Typhoon
                if (GetCaster()->HasAura(SPELL_DRUID_GLYPH_OF_TYPHOON))
                    PreventHitDefaultEffect(effIndex);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dru_typhoon_SpellScript::HandleKnockBack, EFFECT_0, SPELL_EFFECT_KNOCK_BACK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_typhoon_SpellScript();
        }
};

// 70691 - Item T10 Restoration 4P Bonus
class spell_dru_t10_restoration_4p_bonus : public SpellScriptLoader
{
    public:
        spell_dru_t10_restoration_4p_bonus() : SpellScriptLoader("spell_dru_t10_restoration_4p_bonus") { }

        class spell_dru_t10_restoration_4p_bonus_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_t10_restoration_4p_bonus_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (!GetCaster()->ToPlayer()->GetGroup())
                {
                    targets.clear();
                    targets.push_back(GetCaster());
                }
                else
                {
                    targets.remove(GetExplTargetUnit());
                    std::list<Unit*> tempTargets;
                    for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        if ((*itr)->GetTypeId() == TYPEID_PLAYER && GetCaster()->IsInRaidWith((*itr)->ToUnit()))
                            tempTargets.push_back((*itr)->ToUnit());

                    if (tempTargets.empty())
                    {
                        targets.clear();
                        FinishCast(SPELL_FAILED_DONT_REPORT);
                        return;
                    }

                    Unit* target = Trinity::Containers::SelectRandomContainerElement(tempTargets);
                    targets.clear();
                    targets.push_back(target);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_t10_restoration_4p_bonus_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_t10_restoration_4p_bonus_SpellScript();
        }
};

// 88747 - Wild mushroom
class spell_druid_wild_mushroom : public SpellScriptLoader
{
public:
    spell_druid_wild_mushroom() : SpellScriptLoader("spell_druid_wild_mushroom") { }

    class spell_druid_wild_mushroom_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_druid_wild_mushroom_SpellScript)

        void HandleSummon(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            Unit* caster = GetCaster();
            WorldLocation const* targetDest = GetExplTargetDest();
            SpellInfo const* spellInfo = GetSpellInfo();

            if (caster && targetDest)
            {
                if (Player* player = caster->ToPlayer())
                {
                    Position pos;
                    std::list<Creature*> list;

                    Trinity::AnyUnfriendlyCreatureInUnitRangeCheck check(player, DRUID_NPC_WILD_MUSHROOM, 100.0f);
                    Trinity::CreatureListSearcher<Trinity::AnyUnfriendlyCreatureInUnitRangeCheck> searcher(player, list, check);
                    player->VisitNearbyGridObject(100.0f, searcher);

                    // Max 3 Wild Mushroom
                    if ((int32)list.size() >= GetEffectValue())
                    {
                        if (list.back())
                        {
                            if (TempSummon* temp = list.back()->ToTempSummon())
                                temp->UnSummon();
                        }
                    }

                    // Summon position
                    targetDest->GetPosition(&pos);

                    // Summon properties
                    const SummonPropertiesEntry* properties = sSummonPropertiesStore.LookupEntry(spellInfo->Effects[effIndex].MiscValueB);
                    TempSummon* summon = player->SummonCreature(spellInfo->Effects[0].MiscValue, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, spellInfo->GetDuration());
                    if (!summon)
                        return;

                    summon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, player->GetGUID());
                    summon->setFaction(player->getFaction());
                    summon->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetSpellInfo()->Id);
                    summon->SetMaxHealth(5);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    summon->StopMoving();
                    summon->SetControlled(true, UNIT_STATE_STUNNED);
                }
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_druid_wild_mushroom_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_druid_wild_mushroom_SpellScript();
    }
};

// 88751 - Wild mushroom : Detonate
class spell_druid_wild_mushroom_detonate : public SpellScriptLoader
{
public:
    spell_druid_wild_mushroom_detonate() : SpellScriptLoader("spell_druid_wild_mushroom_detonate") { }

    class spell_druid_wild_mushroom_detonate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_druid_wild_mushroom_detonate_SpellScript)

        bool Load()
        {
            spellRange = GetSpellInfo()->GetMaxRange();
            if (!spellRange)
                return false;

            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    std::list<Creature*> list;

                    Trinity::AnyUnfriendlyCreatureInUnitRangeCheck check(player, DRUID_NPC_WILD_MUSHROOM, 100.0f);
                    Trinity::CreatureListSearcher<Trinity::AnyUnfriendlyCreatureInUnitRangeCheck> searcher(player, mushroomList, check);
                    player->VisitNearbyGridObject(100.0f, searcher);

                    return true;
                }
            }

            return false;
        }

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    if (mushroomList.empty())
                        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                    bool inRange = false;

                    for (std::list<Creature*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); i)
                    {
                        if((*i))
                        {
                            Position pos;
                            (*i)->GetPosition(&pos);

                            // Must have at least one mushroom within 40 yards
                            if (player->IsWithinDist3d(&pos, spellRange))
                                return SPELL_CAST_OK;
                        }
                        i++;
                    }

                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_TARGET_TOO_FAR);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }
            }
            return SPELL_FAILED_CASTER_DEAD;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    for (std::list<Creature*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); i)
                    {
                        Position pos;
                        Creature* tempMushroom = (*i);
                        if (tempMushroom)
                        {
                            tempMushroom->GetPosition(&pos);

                            if (player->HasAura(DRUID_TALENT_FUNGAL_GROWTH_1))  // Fungal Growth Rank 1
                                player->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), DRUID_SPELL_FUNGAL_GROWTH_1, false);
                            else if (player->HasAura(DRUID_TALENT_FUNGAL_GROWTH_2))     // Fungal Growth Rank 2
                                player->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), DRUID_SPELL_FUNGAL_GROWTH_2, false);
                        }
                        i++;
                    }

                    // Frees the memory
                    mushroomList.clear();
                }
            }
        }

    private:
        float spellRange;
        std::list<Creature*> mushroomList;

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_druid_wild_mushroom_detonate_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_druid_wild_mushroom_detonate_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_druid_wild_mushroom_detonate_SpellScript();
    }
};

// 54743 Glyph of Regrowth
// Upgraded 4.3.4
class spell_dru_glyph_of_regrowth : public SpellScriptLoader
{
public:
    spell_dru_glyph_of_regrowth() : SpellScriptLoader("spell_dru_glyph_of_regrowth") { }

    class spell_dru_glyph_of_regrowth_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_glyph_of_regrowth_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return sSpellMgr->GetSpellInfo(DRUID_SPELL_REGROWTH);
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            Unit* target = eventInfo.GetActionTarget();
            if (!target || target->GetHealthPct() > 50.f)
                return;

            if (Aura* aura = target->GetAura(DRUID_SPELL_REGROWTH, GetOwner()->GetGUID()))
                aura->RefreshDuration();
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_dru_glyph_of_regrowth_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dru_glyph_of_regrowth_AuraScript();
    }
};

// 81262 - Efflorescence
class spell_dru_efflorescence: public SpellScriptLoader
{
public:
    spell_dru_efflorescence() :  SpellScriptLoader("spell_dru_efflorescence") { }

    class spell_dru_efflorescence_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_dru_efflorescence_AuraScript);

        void OnTick(AuraEffect const* aurEff)
        {
            if (DynamicObject* dynObj = GetCaster()->GetDynObject(81262))
            {
                float x,y,z;
                dynObj->GetPosition(x, y, z);

                if (GetCaster()->GetMapId() == dynObj->GetMapId())
                    GetCaster()->CastSpell(x, y, z, 81269, true);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_efflorescence_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dru_efflorescence_AuraScript();
    }
};

// 80313 - Pulverize
class spell_dru_pulverize : public SpellScriptLoader
{
public:
    spell_dru_pulverize() : SpellScriptLoader("spell_dru_pulverize") { }

    class spell_dru_pulverize_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_pulverize_SpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    // Lacerate
                    if (Aura* lacerate = target->GetAura(33745, caster->GetGUID()))
                    {
                        stackAmount = 3;
                        SetHitDamage(GetHitDamage() * stackAmount);
                        stackAmount *= lacerate->GetStackAmount();
                        caster->CastCustomSpell(caster, 80951, &stackAmount, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                        lacerate->Remove();
                    }
                    else
                        SetHitDamage(GetHitDamage() / 2);
                }
            }
        }

    protected:
        int32 stackAmount;

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_pulverize_SpellScript::CalculateDamage, EFFECT_2, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_pulverize_SpellScript();
    }
};

// 22568 - Ferocious Bite
class spell_dru_ferocious_bite : public SpellScriptLoader
{
    public:
        spell_dru_ferocious_bite() : SpellScriptLoader("spell_dru_ferocious_bite") { }

        class spell_dru_ferocious_bite_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_ferocious_bite_SpellScript);

            void HandleBeforeCast()
            {
                spellCost = GetSpell()->GetPowerCost();
                if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                    comboPoints = GetCaster()->ToPlayer()->GetComboPoints();
            }

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    Unit* target = GetHitUnit();
                    if (!target)
                        return;

                    // Blood in the Water
                    if (Aura* aur = target->GetAura(1079))
                    {
                        if (target->GetHealthPct() <= 25)
                        {
                            if (caster->HasAura(80318) && roll_chance_i(50))
                                aur->RefreshDuration();
                            else if (caster->HasAura(80319))
                                aur->RefreshDuration();
                        }
                    }
                    // Converts each extra point of energy ( up to 35 energy ) into additional damage
                    int32 energy = -(caster->ModifyPower(POWER_ENERGY, -35));
                    int32 attackPower = GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.109f;
                    // 1 point: ${$m1+$b1*1*$<mult>+0.109*$AP*$<mult>}-${$M1+$b1*1*$<mult>+0.109*$AP*$<mult>} damage
                    SetHitDamage(GetHitDamage() + (attackPower * comboPoints));
                    int32 damage = GetHitDamage();
                    // 35 energy = 100% more damage
                    AddPct(damage, energy * 4);

                    SetHitDamage(damage);

                    // Glyph of Ferocious Bite
                    if (caster->HasAura(67598))
                    {
                        int32 casterMaxHP = caster->GetMaxHealth();
                        int32 energyFinal = energy + spellCost;
                        if (energyFinal >= 30 && energyFinal < 40)
                            energyFinal = 30;
                        else if (energyFinal >= 40 && energyFinal < 50)
                            energyFinal = 40;
                        else if (energyFinal >= 50 && energyFinal < 60)
                            energyFinal = 50;
                        else if (energyFinal >= 60 && energyFinal < 70)
                            energyFinal = 60;
                        else if (energyFinal >= 70)
                            energyFinal = 70;
                        caster->HealBySpell(caster, GetSpellInfo(), (casterMaxHP * energyFinal / 1000));
                    }
                }
            }
        private:
            int16 spellCost;
            int8 comboPoints;

            void Register()
            {
                BeforeCast += SpellCastFn(spell_dru_ferocious_bite_SpellScript::HandleBeforeCast);
                OnEffectHitTarget += SpellEffectFn(spell_dru_ferocious_bite_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_ferocious_bite_SpellScript();
        }
};

// 46832 - Sudden Eclipse
class spell_dru_pvpset_4p_balance: public SpellScriptLoader
{
public:
    spell_dru_pvpset_4p_balance() :  SpellScriptLoader("spell_dru_pvpset_4p_balance") { }

    class spell_dru_pvpset_4p_balance_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_dru_pvpset_4p_balance_AuraScript);

        enum Spells
        {
            SPELL_DRUID_PVP_SET_4P_BALANCE      = 46832,
            SPELL_DRUID_PVP_SET_4P_TRIGGER      = 95746
        };

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (caster->HasAura(SPELL_DRUID_PVP_SET_4P_BALANCE))
                {
                    if (caster->ToPlayer()->HasSpellCooldown(SPELL_DRUID_PVP_SET_4P_TRIGGER))
                        return;

                    if (caster->GetPower(POWER_ECLIPSE) >= 0)
                    {
                        caster->EnergizeBySpell(caster, SPELL_DRUID_PVP_SET_4P_TRIGGER, 20, POWER_ECLIPSE);
                        caster->ToPlayer()->AddSpellCooldown(SPELL_DRUID_PVP_SET_4P_TRIGGER, 0, time(NULL) + 6);
                    }
                    else
                    {
                        caster->EnergizeBySpell(caster, SPELL_DRUID_PVP_SET_4P_TRIGGER, -13, POWER_ECLIPSE);
                        caster->ToPlayer()->AddSpellCooldown(SPELL_DRUID_PVP_SET_4P_TRIGGER, 0, time(NULL) + 6);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_dru_pvpset_4p_balance_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dru_pvpset_4p_balance_AuraScript();
    }
};

class spell_dru_maul : public SpellScriptLoader
{
    public:
        spell_dru_maul() : SpellScriptLoader("spell_dru_maul") { }

        class spell_dru_maul_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_maul_SpellScript);

            uint64 targetGUID;

            void HandleBeforeCast()
            {
                Unit* target = GetExplTargetUnit();
                Unit* caster = GetCaster();

                if (!caster || !target)
                    return;

                targetGUID = target->GetGUID();
            }

            void HandleOnHit()
            {
                Unit* target = GetHitUnit();
                Unit* caster = GetCaster();

                if (!caster || !target || !targetGUID)
                    return;

                if (target->GetGUID() == targetGUID)
                    SetHitDamage(GetHitDamage());
                else
                    SetHitDamage(GetHitDamage() / 2);

                // Bleed effect damage taken increased
                if (target->HasAuraTypeWithMiscvalue(SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT, 15))
                    SetHitDamage(GetHitDamage() + GetHitDamage() * 0.20f);
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_dru_maul_SpellScript::HandleBeforeCast);
                OnHit += SpellHitFn(spell_dru_maul_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_maul_SpellScript();
        }
};

class spell_dru_thrash : public SpellScriptLoader
{
public:
    spell_dru_thrash() : SpellScriptLoader("spell_dru_thrash") { }

    class spell_dru_thrash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_thrash_SpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 attackPower = caster->ToPlayer()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.0982f;
                        SetHitDamage((GetHitDamage() + attackPower) * 1.04f);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_thrash_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_thrash_SpellScript();
    }
};

class spell_dru_rake : public SpellScriptLoader
{
public:
    spell_dru_rake() : SpellScriptLoader("spell_dru_rake")
    {
    }

    class spell_dru_rake_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_rake_AuraScript);

        bool Load()
        {
            Unit* caster = GetCaster();
            return caster && caster->GetTypeId() == TYPEID_PLAYER;
        }

        void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
        {
            canBeRecalculated = false;

            if (Unit* caster = GetCaster())
            {
                /* (56 * 3 + AP * 0.441) */
                uint32 ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                amount = uint32(56 * 3 + ap * 0.441) / aurEff->GetTotalTicks();
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_rake_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dru_rake_AuraScript();
    }
};

class spell_dru_ravage_stampede : public SpellScriptLoader
{
public:
    spell_dru_ravage_stampede() : SpellScriptLoader("spell_dru_ravage_stampede")
    {
    }

    class spell_dru_ravage_stampede_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_ravage_stampede_SpellScript);

        enum spellId
        {
            SPELL_CLEARCASTING_BUFF     = 16870
        };

        bool Load()
        {
            isClearCasting = false;
            buffDuration = 0;
            return true;
        }

        void CheckBeforeCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Aura* aur = caster->GetAura(SPELL_CLEARCASTING_BUFF, caster->GetGUID()))
                {
                    isClearCasting = true;
                    buffDuration = aur->GetDuration();
                }
            }
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (isClearCasting == true && buffDuration > 0)
                {
                    caster->AddAura(SPELL_CLEARCASTING_BUFF, caster);
                    if (Aura* aur = caster->GetAura(SPELL_CLEARCASTING_BUFF, caster->GetGUID()))
                        aur->SetDuration(buffDuration);
                }
                isClearCasting = false;
            }
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_dru_ravage_stampede_SpellScript::CheckBeforeCast);
            AfterCast += SpellCastFn(spell_dru_ravage_stampede_SpellScript::HandleAfterCast);
        }

    private:
        bool isClearCasting;
        uint32 buffDuration;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_ravage_stampede_SpellScript();
    }
};

class spell_dru_cyclone : public SpellScriptLoader
{
public:
    spell_dru_cyclone() : SpellScriptLoader("spell_dru_cyclone")
    {
    }

    class spell_dru_cyclone_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_cyclone_AuraScript);

        void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (Unit* target = GetTarget())
                target->ApplySpellImmune(GetSpellInfo()->Id, IMMUNITY_ID, GetSpellInfo()->Id, true);
        }

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (Unit* target = GetTarget())
                target->ApplySpellImmune(GetSpellInfo()->Id, IMMUNITY_ID, GetSpellInfo()->Id, false);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_dru_cyclone_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            AfterEffectRemove += AuraEffectRemoveFn(spell_dru_cyclone_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dru_cyclone_AuraScript();
    }
};

class spell_dru_mangle_cat : public SpellScriptLoader
{
public:
    spell_dru_mangle_cat() : SpellScriptLoader("spell_dru_mangle_cat")
    {
    }

    class spell_dru_mangle_cat_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_mangle_cat_SpellScript);

        enum spellId
        {
            SPELL_DRU_T11_FERAL_4P          = 90165,
            SPELL_STRENGTH_OF_THE_PANTHER   = 90166
        };

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_DRU_T11_FERAL_4P))
                    caster->CastSpell(caster, SPELL_STRENGTH_OF_THE_PANTHER, true);
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_dru_mangle_cat_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_mangle_cat_SpellScript();
    }
};

class spell_dru_rejuvenation : public SpellScriptLoader
{
public:
    spell_dru_rejuvenation() : SpellScriptLoader("spell_dru_rejuvenation")
    {
    }

    class spell_dru_rejuvenation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dru_rejuvenation_AuraScript);

        enum spellId
        {
            SPELL_DRUID_REJUVENATION_INSTANT    = 64801
        };

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();

            if (!caster || !target)
                return;

            // Gift of the Earthmother
            if (caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 3186, EFFECT_0))
            {
                if (Aura* rejuvenation = target->GetAura(GetSpellInfo()->Id, caster->GetGUID()))
                {
                    if (AuraEffect* earthmother = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 3186, EFFECT_1))
                    {
                        int32 rejHeal = caster->SpellHealingBonusDone(target, rejuvenation->GetSpellInfo(), rejuvenation->GetEffect(EFFECT_0)->GetAmount(), HEAL);
                        int32 hpAmount = (rejHeal * rejuvenation->GetEffect(EFFECT_0)->GetTotalTicks()) * earthmother->GetAmount() / 100;

                        caster->CastCustomSpell(target, SPELL_DRUID_REJUVENATION_INSTANT, &hpAmount, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                    }
                }
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_dru_rejuvenation_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dru_rejuvenation_AuraScript();
    }
};

void AddSC_druid_spell_scripts()
{
    new spell_dru_dash();
    new spell_dru_eclipse_energize();
    new spell_dru_enrage();
    new spell_dru_idol_lifebloom();
    new spell_dru_innervate();
    new spell_dru_insect_swarm();
    new spell_dru_lifebloom();
    new spell_dru_living_seed();
    new spell_dru_living_seed_proc();
    new spell_dru_owlkin_frenzy();
    new spell_dru_predatory_strikes();
    new spell_dru_primal_tenacity();
    new spell_dru_rip();
    new spell_dru_savage_roar();
    new spell_dru_starfall_aoe();
    new spell_dru_starfall_dummy();
    new spell_dru_survival_instincts();
    new spell_dru_swift_flight_passive();
    new spell_dru_tiger_s_fury();
    new spell_dru_typhoon();
    new spell_dru_t10_restoration_4p_bonus();
    new spell_druid_wild_mushroom();
    new spell_druid_wild_mushroom_detonate();
    new spell_dru_glyph_of_regrowth();
    new spell_dru_efflorescence();
    new spell_dru_pulverize();
    new spell_dru_ferocious_bite();
    new spell_dru_pvpset_4p_balance();
    new spell_dru_maul();
    new spell_dru_thrash();
    new spell_dru_ravage_stampede();
    new spell_dru_cyclone();
    new spell_dru_mangle_cat();
    new spell_dru_rejuvenation();
}
