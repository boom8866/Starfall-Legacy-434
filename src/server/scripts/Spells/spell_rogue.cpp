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
 * Scripts for spells with SPELLFAMILY_ROGUE and SPELLFAMILY_GENERIC spells used by rogue players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_rog_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum RogueSpells
{
    SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK        = 22482,
    SPELL_ROGUE_CHEAT_DEATH_COOLDOWN             = 31231,
    SPELL_ROGUE_GLYPH_OF_PREPARATION             = 56819,
    SPELL_ROGUE_PREY_ON_THE_WEAK                 = 58670,
    SPELL_ROGUE_SHIV_TRIGGERED                   = 5940,
    SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST    = 57933,
    SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC         = 59628,
    SPELL_ROGUE_GLYPH_OF_HEMORRHAGE_TRIGGERED    = 89775,
    SPELL_ROGUE_GLYPH_OF_HEMORRHAGE              = 56807,
    SPELL_ROGUE_GLYPH_OF_SINISTER_STRIKE         = 56821,
    SPELL_ROGUE_GLYPH_OF_SINISTER_STRIKE_TRIG    = 14189,
    SPELL_ROGUE_CHEATING_DEATH                   = 45182
};

enum RogueSpellIcons
{
    ICON_ROGUE_IMPROVED_RECUPERATE               = 4819
};

// 31228 - Cheat Death
class spell_rog_cheat_death : public SpellScriptLoader
{
    public:
        spell_rog_cheat_death() : SpellScriptLoader("spell_rog_cheat_death") { }

        class spell_rog_cheat_death_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_cheat_death_AuraScript);

            uint32 absorbChance;

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN))
                    return false;
                return true;
            }

            bool Load()
            {
                absorbChance = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
                return GetUnitOwner()->ToPlayer();
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Player* target = GetTarget()->ToPlayer();
                if (!target)
                    return;

                if (dmgInfo.GetDamage() < target->GetHealth() || target->HasSpellCooldown(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN) ||  !roll_chance_i(absorbChance))
                    return;

                target->CastSpell(target, SPELL_ROGUE_CHEAT_DEATH_COOLDOWN, true);
                target->AddSpellCooldown(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN, 0, time(NULL) + 60);

                uint32 health10 = target->CountPctFromMaxHealth(10);

                // hp > 10% - absorb hp till 10%
                if (target->GetHealth() > health10)
                    absorbAmount = dmgInfo.GetDamage() - target->GetHealth() + health10;
                // hp lower than 10% - absorb everything
                else
                    absorbAmount = dmgInfo.GetDamage();

                target->CastSpell(target, SPELL_ROGUE_CHEATING_DEATH, true);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_cheat_death_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_rog_cheat_death_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_cheat_death_AuraScript();
        }
};

// 2818 - Deadly Poison
class spell_rog_deadly_poison : public SpellScriptLoader
{
    public:
        spell_rog_deadly_poison() : SpellScriptLoader("spell_rog_deadly_poison") { }

        class spell_rog_deadly_poison_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_deadly_poison_SpellScript);

            bool Load()
            {
                _stackAmount = 0;
                // at this point CastItem must already be initialized
                return GetCaster()->GetTypeId() == TYPEID_PLAYER && GetCastItem();
            }

            void HandleBeforeHit()
            {
                if (Unit* target = GetHitUnit())
                    // Deadly Poison
                    if (AuraEffect const* aurEff = target->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_ROGUE, 0x10000, 0x80000, 0, GetCaster()->GetGUID()))
                        _stackAmount = aurEff->GetBase()->GetStackAmount();
            }

            void HandleAfterHit()
            {
                if (_stackAmount < 5)
                    return;

                Player* player = GetCaster()->ToPlayer();

                if (Unit* target = GetHitUnit())
                {

                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

                    if (item == GetCastItem())
                        item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

                    if (!item)
                        return;

                    // item combat enchantments
                    for (uint8 slot = 0; slot < MAX_ENCHANTMENT_SLOT; ++slot)
                    {
                        if (slot > PRISMATIC_ENCHANTMENT_SLOT && slot < PROP_ENCHANTMENT_SLOT_0)    // not holding enchantment id
                            continue;

                        SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(item->GetEnchantmentId(EnchantmentSlot(slot)));
                        if (!enchant)
                            continue;

                        for (uint8 s = 0; s < 3; ++s)
                        {
                            if (enchant->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                                continue;

                            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(enchant->spellid[s]);
                            if (!spellInfo)
                            {
                                sLog->outError(LOG_FILTER_SPELLS_AURAS, "Player::CastItemCombatSpell Enchant %i, player (Name: %s, GUID: %u) cast unknown spell %i", enchant->ID, player->GetName().c_str(), player->GetGUIDLow(), enchant->spellid[s]);
                                continue;
                            }

                            // Proc only rogue poisons
                            if (spellInfo->SpellFamilyName != SPELLFAMILY_ROGUE || spellInfo->Dispel != DISPEL_POISON)
                                continue;

                            // Do not reproc deadly
                            if (spellInfo->SpellFamilyFlags.IsEqual(0x10000, 0x80000, 0))
                                continue;

                            if (spellInfo->IsPositive())
                                player->CastSpell(player, enchant->spellid[s], true, item);
                            else
                                player->CastSpell(target, enchant->spellid[s], true, item);
                        }
                    }
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_rog_deadly_poison_SpellScript::HandleBeforeHit);
                AfterHit += SpellHitFn(spell_rog_deadly_poison_SpellScript::HandleAfterHit);
            }

            uint8 _stackAmount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rog_deadly_poison_SpellScript();
        }
};

// 31130 - Nerves of Steel
class spell_rog_nerves_of_steel : public SpellScriptLoader
{
    public:
        spell_rog_nerves_of_steel() : SpellScriptLoader("spell_rog_nerves_of_steel") { }

        class spell_rog_nerves_of_steel_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_nerves_of_steel_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                // reduces all damage taken while stun or fear
                if (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_FLEEING) || (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_STUNNED) && GetTarget()->HasAuraWithMechanic(1<<MECHANIC_STUN)))
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_nerves_of_steel_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_rog_nerves_of_steel_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_nerves_of_steel_AuraScript();
        }
};

// 14185 - Preparation
class spell_rog_preparation : public SpellScriptLoader
{
    public:
        spell_rog_preparation() : SpellScriptLoader("spell_rog_preparation") { }

        enum spellId
        {
            SPELL_ROGUE_SPRINT      = 2983,
            SPELL_ROGUE_VANISH      = 1856,
            SPELL_ROGUE_SHADOWSTEP  = 36554
        };

        class spell_rog_preparation_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_preparation_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_GLYPH_OF_PREPARATION))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                if (!caster)
                    return;

                // immediately finishes the cooldown on certain Rogue abilities
                const SpellCooldowns& cm = caster->GetSpellCooldownMap();
                for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
                {
                    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first))
                    {
                        if (spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE)
                        {
                            if (spellInfo->Id == SPELL_ROGUE_SPRINT || spellInfo->Id == SPELL_ROGUE_VANISH || spellInfo->Id == SPELL_ROGUE_SHADOWSTEP)     // Sprint, Vanish, Shadowstep
                                caster->RemoveSpellCooldown((itr++)->first, true);

                            if (caster->HasAura(SPELL_ROGUE_GLYPH_OF_PREPARATION))
                            {
                                if (spellInfo->SpellFamilyFlags[1] & SPELLFAMILYFLAG1_ROGUE_DISMANTLE ||        // Dismantle
                                    spellInfo->SpellFamilyFlags[0] & SPELLFAMILYFLAG_ROGUE_KICK ||              // Kick
                                    spellInfo->SpellFamilyFlags[1] & SPELLFAMILYFLAG1_ROGUE_SMOKE_BOMB ||       // Smoke Bomb
                                    (spellInfo->SpellFamilyFlags[0] & SPELLFAMILYFLAG_ROGUE_BLADE_FLURRY &&     // Blade Flurry
                                    spellInfo->SpellFamilyFlags[1] & SPELLFAMILYFLAG1_ROGUE_BLADE_FLURRY))
                                    caster->RemoveSpellCooldown((itr++)->first, true);
                                else
                                    ++itr;
                            }
                            else
                                ++itr;
                        }
                        else
                            ++itr;
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_rog_preparation_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rog_preparation_SpellScript();
        }
};

// 51685 - Prey on the Weak
class spell_rog_prey_on_the_weak : public SpellScriptLoader
{
    public:
        spell_rog_prey_on_the_weak() : SpellScriptLoader("spell_rog_prey_on_the_weak") { }

        class spell_rog_prey_on_the_weak_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_prey_on_the_weak_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_PREY_ON_THE_WEAK))
                    return false;
                return true;
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                Unit* target = GetTarget();
                Unit* victim = target->getVictim();
                if (victim && (target->GetHealthPct() > victim->GetHealthPct()))
                {
                    if (!target->HasAura(SPELL_ROGUE_PREY_ON_THE_WEAK))
                    {
                        int32 bp = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
                        target->CastCustomSpell(target, SPELL_ROGUE_PREY_ON_THE_WEAK, &bp, 0, 0, true);
                    }
                }
                else
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_PREY_ON_THE_WEAK);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_prey_on_the_weak_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_prey_on_the_weak_AuraScript();
        }
};

// 73651 - Recuperate
class spell_rog_recuperate : public SpellScriptLoader
{
    public:
        spell_rog_recuperate() : SpellScriptLoader("spell_rog_recuperate") { }

        class spell_rog_recuperate_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_recuperate_AuraScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect* effect = GetAura()->GetEffect(EFFECT_0))
                        effect->RecalculateAmount(caster);
            }

            void CalculateBonus(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    int32 baseAmount = GetSpellInfo()->Effects[EFFECT_0].CalcValue(caster) * 1000;
                    // Improved Recuperate
                    if (AuraEffect const* auraEffect = caster->GetDummyAuraEffect(SPELLFAMILY_ROGUE, ICON_ROGUE_IMPROVED_RECUPERATE, EFFECT_0))
                        baseAmount += auraEffect->GetAmount();

                    amount = CalculatePct(caster->GetMaxHealth(), float(baseAmount) / 1000.0f);

                    // Quickening
                    if (AuraEffect const* auraEffect = caster->GetAuraEffectOfRankedSpell(31208, EFFECT_0, caster->GetGUID()))
                        amount += amount * auraEffect->GetAmount() / 100;
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_recuperate_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_recuperate_AuraScript::CalculateBonus, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_recuperate_AuraScript();
        }
};

// 1943 - Rupture
class spell_rog_rupture : public SpellScriptLoader
{
    public:
        spell_rog_rupture() : SpellScriptLoader("spell_rog_rupture") { }

        class spell_rog_rupture_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_rupture_AuraScript);

            enum VenomousWounds
            {
                SPELL_TALENT_VENOMOUS_WOUNDS_R1 = 79133,
                SPELL_TALENT_VENOMOUS_WOUNDS_R2 = 79134,
                SPELL_VENOMOUS_WOUND_TRIGGERED  = 79136
            };

            bool Load()
            {
                Unit* caster = GetCaster();
                return caster && caster->GetTypeId() == TYPEID_PLAYER;
            }
            
            void EffectApplyRupture(AuraEffect const* aurEff, AuraEffectHandleModes /* mode*/)
            {
                amount = aurEff->GetBase()->GetDuration() / 1000;

                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        int8 comboPoints = caster->ToPlayer()->GetComboPoints();
                        int32 amount = 0;

                        // Restless Blades
                        if (AuraEffect* aurEff = caster->ToPlayer()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_ROGUE, 4897, 0))
                        {
                            amount += (aurEff->GetAmount() * comboPoints / 1000);
                            // Adrenaline Rush
                            caster->ToPlayer()->UpdateSpellCooldown(13750, -amount);
                            // Killing Spree
                            caster->ToPlayer()->UpdateSpellCooldown(51690, -amount);
                            // Redirect
                            caster->ToPlayer()->UpdateSpellCooldown(73981, -amount);
                            // Sprint
                            caster->ToPlayer()->UpdateSpellCooldown(2983, -amount);
                            amount = 0;
                            comboPoints = 0;
                        }
                    }
                }
            }

            void HandleEffectPeriodicUpdate(AuraEffect* aurEff)
            {
                amount = aurEff->GetBase()->GetDuration() / 1000;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* caster = GetCaster())
                {
                    canBeRecalculated = false;

                    float const attackpowerPerCombo[6] =
                    {
                        0.0f,
                        0.015f,         // 1 point:  ${($m1 + $b1*1 + 0.015 * $AP) * 4} damage over 8 secs
                        0.024f,         // 2 points: ${($m1 + $b1*2 + 0.024 * $AP) * 5} damage over 10 secs
                        0.03f,          // 3 points: ${($m1 + $b1*3 + 0.03 * $AP) * 6} damage over 12 secs
                        0.03428571f,    // 4 points: ${($m1 + $b1*4 + 0.03428571 * $AP) * 7} damage over 14 secs
                        0.0375f         // 5 points: ${($m1 + $b1*5 + 0.0375 * $AP) * 8} damage over 16 secs
                    };

                    uint8 cp = caster->ToPlayer()->GetComboPoints();
                    if (cp > 5)
                        cp = 5;

                    amount += int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * attackpowerPerCombo[cp]);
                }
            }

            void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();
                if (!caster || !target)
                    return;

                // Venomous Wounds
                if (caster->HasAura(SPELL_TALENT_VENOMOUS_WOUNDS_R1) || caster->HasAura(SPELL_TALENT_VENOMOUS_WOUNDS_R2))
                {
                    if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                        caster->EnergizeBySpell(caster, SPELL_VENOMOUS_WOUND_TRIGGERED, amount, POWER_ENERGY);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_rog_rupture_AuraScript::EffectApplyRupture, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_rupture_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_rupture_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_rog_rupture_AuraScript::HandleEffectPeriodicUpdate, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }

        private:
            int32 amount;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_rupture_AuraScript();
        }
};

// 5938 - Shiv
class spell_rog_shiv : public SpellScriptLoader
{
    public:
        spell_rog_shiv() : SpellScriptLoader("spell_rog_shiv") { }

        class spell_rog_shiv_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_shiv_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_SHIV_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                    caster->CastSpell(unitTarget, SPELL_ROGUE_SHIV_TRIGGERED, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_rog_shiv_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rog_shiv_SpellScript();
        }
};

// 57934 - Tricks of the Trade
class spell_rog_tricks_of_the_trade : public SpellScriptLoader
{
    public:
        spell_rog_tricks_of_the_trade() : SpellScriptLoader("spell_rog_tricks_of_the_trade") { }

        class spell_rog_tricks_of_the_trade_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_tricks_of_the_trade_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC))
                    return false;
                return true;
            }

            bool Load()
            {
                _redirectTarget = NULL;
                return true;
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEFAULT)
                    GetTarget()->ResetRedirectThreat();
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                _redirectTarget = GetTarget()->GetRedirectThreatTarget();
                return _redirectTarget;
            }

            void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();

                Unit* target = GetTarget();
                target->CastSpell(_redirectTarget, SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST, true);
                target->CastSpell(target, SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC, true);
                Remove(AURA_REMOVE_BY_DEFAULT); // maybe handle by proc charges
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_tricks_of_the_trade_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                DoCheckProc += AuraCheckProcFn(spell_rog_tricks_of_the_trade_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_rog_tricks_of_the_trade_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _redirectTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_tricks_of_the_trade_AuraScript();
        }
};

// 59628 - Tricks of the Trade (Proc)
class spell_rog_tricks_of_the_trade_proc : public SpellScriptLoader
{
    public:
        spell_rog_tricks_of_the_trade_proc() : SpellScriptLoader("spell_rog_tricks_of_the_trade_proc") { }

        class spell_rog_tricks_of_the_trade_proc_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_tricks_of_the_trade_proc_AuraScript);

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->ResetRedirectThreat();
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_tricks_of_the_trade_proc_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_tricks_of_the_trade_proc_AuraScript();
        }
};

// 76806 - main Gauche
class spell_rog_main_gauche : public SpellScriptLoader
{
    public:
       spell_rog_main_gauche() : SpellScriptLoader("spell_rog_main_gauche") { }

       class spell_rog_main_gauche_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_rog_main_gauche_AuraScript);

           enum spellId
           {
                SPELL_MAIN_GAUCHE_TRIGGERED = 86392
           };

           void HandleProc(AuraEffect const* aurEff, ProcEventInfo &procInfo)
           {
               if (!roll_chance_i(aurEff->GetAmount()))
                   return;

               if (!GetCaster()->ToPlayer())
                   return;

               // Procs only from Main Hand
               if (!(procInfo.GetTypeMask() & PROC_FLAG_DONE_MAINHAND_ATTACK))
                   return;

               if (procInfo.GetSpellInfo())
                   return;

               // If no weapon found in main hand, avoid to proc
               Item* mainHand = GetCaster()->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
               if (!mainHand)
                   return;

               if (Unit *caster = GetCaster())
               {
                   caster->CastSpell(procInfo.GetActionTarget(), SPELL_MAIN_GAUCHE_TRIGGERED, true, NULL, aurEff);

                   // Combat Potency
                   if (roll_chance_i(20))
                   {
                       if (caster->HasAura(35541))
                           caster->CastSpell(caster, 35542, true);
                       else if (caster->HasAura(35550))
                           caster->CastSpell(caster, 35545, true);
                       else if (caster->HasAura(35551))
                           caster->CastSpell(caster, 35546, true);
                   }
               }
           }

           void Register()
           {
                OnEffectProc += AuraEffectProcFn(spell_rog_main_gauche_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_rog_main_gauche_AuraScript();
       }
};

// 6770 - Sap
class spell_rog_sap : public SpellScriptLoader
{
    public:
       spell_rog_sap() : SpellScriptLoader("spell_rog_sap") { }

       class spell_rog_sap_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_rog_sap_AuraScript);

           enum Blackjack
           {
                SPELL_TALENT_BLACKJACK_R1 = 79123,
                SPELL_TALENT_BLACKJACK_R2 = 79125,
                SPELL_BLACKJACK_GROGGY_R1 = 79124,
                SPELL_BLACKJACK_GROGGY_R2 = 79126
           };

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();
                if (!caster || !target)
                    return;
                // Blackjack
                if (caster->HasAura(SPELL_TALENT_BLACKJACK_R1))
                    caster->CastSpell(target, SPELL_BLACKJACK_GROGGY_R1, true);
                else if (caster->HasAura(SPELL_TALENT_BLACKJACK_R2))
                    caster->CastSpell(target, SPELL_BLACKJACK_GROGGY_R2, true);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_sap_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_rog_sap_AuraScript();
       }
};

// 8647 - Expose Armor
class spell_rog_expose_armor : public SpellScriptLoader
{
public:
    spell_rog_expose_armor() : SpellScriptLoader("spell_rog_expose_armor") { }

    class spell_rog_expose_armor_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_expose_armor_SpellScript);

        enum ImprovedExposeArmor
        {
            SPELL_TALENT_IMPROVED_EXPOSE_ARMOR_R1 = 79123,
            SPELL_TALENT_IMPROVED_EXPOSE_ARMOR_R2 = 79125,
            SPELL_IMPROVED_EXPOSE_ARMOR_TRIGGERED = 79128
        };

        bool Load()
        {
            comboPoints = 0;
            return true;
        }

        void HandleBeforeCast()
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;
            comboPoints = player->GetComboPoints();
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Improved Expose Armor
            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_ROGUE, 563, 0))
            {
                int32 chance = aurEff->GetAmount();
                if (roll_chance_i(chance))
                    caster->CastCustomSpell(target, SPELL_IMPROVED_EXPOSE_ARMOR_TRIGGERED, &comboPoints, NULL, NULL, true, NULL, NULL, caster->GetGUID());
            }
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_rog_expose_armor_SpellScript::HandleBeforeCast);
            AfterCast += SpellCastFn(spell_rog_expose_armor_SpellScript::HandleAfterCast);
        }

    private:
        int32 comboPoints;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_expose_armor_SpellScript();
    }
};

// 53 - Backstab
class spell_rog_backstab : public SpellScriptLoader
{
public:
    spell_rog_backstab() : SpellScriptLoader("spell_rog_backstab") { }

    class spell_rog_backstab_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_backstab_SpellScript);

        enum MurderousIntent
        {
            SPELL_TALENT_MURDEROUS_INTENT_R1 = 14158,
            SPELL_TALENT_MURDEROUS_INTENT_R2 = 14159,
            SPELL_MURDEROUS_INTENT_TRIGGERED = 79132
        };

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();
            if (!caster || !target)
                return;

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Murderous Intent
            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_ROGUE, 134, 0))
            {
                int32 bp0 = aurEff->GetAmount();
                if (target->HealthBelowPct(35))
                    caster->EnergizeBySpell(caster, SPELL_MURDEROUS_INTENT_TRIGGERED, bp0, POWER_ENERGY);
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_rog_backstab_SpellScript::HandleAfterCast);
        }

    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_backstab_SpellScript();
    }
};

// 53 - Fan of Knives
class spell_rog_fan_of_knives : public SpellScriptLoader
{
public:
    spell_rog_fan_of_knives() : SpellScriptLoader("spell_rog_fan_of_knives") { }

    class spell_rog_fan_of_knives_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_fan_of_knives_SpellScript);

        void HandleVilePoisons(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            // Only for player casters
            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Vile Poisons
            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_ROGUE, 857, 2))
            {
                int32 chance = aurEff->GetAmount();
                if (roll_chance_i(chance))
                {
                    Item* mainHand = caster->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                    Item* offHand = caster->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                    EnchantmentSlot slot = TEMP_ENCHANTMENT_SLOT;
                    if(!slot)
                        return;

                    if (mainHand)
                        mPoison = mainHand->GetEnchantmentId(EnchantmentSlot(slot));

                    if (offHand)
                        oPoison = offHand->GetEnchantmentId(EnchantmentSlot(slot));

                    SpellItemEnchantmentEntry const* enchant_main = sSpellItemEnchantmentStore.LookupEntry(mPoison);
                    SpellItemEnchantmentEntry const* enchant_off = sSpellItemEnchantmentStore.LookupEntry(oPoison);
                    if (!enchant_main || !enchant_off)
                        return;

                    for (uint8 s = 0; s < MAX_ITEM_ENCHANTMENT_EFFECTS; ++s)
                    {
                        if (enchant_main->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                            continue;
                        if (enchant_off->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                            continue;

                        SpellInfo const* spellInfo_main = sSpellMgr->GetSpellInfo(enchant_main->spellid[s]);
                        SpellInfo const* spellInfo_off = sSpellMgr->GetSpellInfo(enchant_off->spellid[s]);
                        if (!spellInfo_main || !spellInfo_off)
                            continue;

                        if (spellInfo_main->Dispel != DISPEL_POISON || spellInfo_off->Dispel != DISPEL_POISON)
                            continue;

                        caster->CastSpell(target, spellInfo_main, true, mainHand);
                        caster->CastSpell(target, spellInfo_off, true, offHand);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_rog_fan_of_knives_SpellScript::HandleVilePoisons, EFFECT_0, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
        }

    private:
        uint32 mPoison;
        uint32 oPoison;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_fan_of_knives_SpellScript();
    }
};

// 16511 - Hemorrhage
class spell_rog_hemorrhage : public SpellScriptLoader
{
    public:
        spell_rog_hemorrhage() : SpellScriptLoader("spell_rog_hemorrhage") { }

        class spell_rog_hemorrhage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_hemorrhage_SpellScript);

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                damage = 0;
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Glyph of Hemorrhage
                        if (!caster->HasAura(SPELL_ROGUE_GLYPH_OF_HEMORRHAGE))
                            return;

                        damage = (GetHitDamage() * 0.40f) / 8;
                    }
                }
            }

            void HandleGlyph()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                        caster->CastCustomSpell(target, SPELL_ROGUE_GLYPH_OF_HEMORRHAGE_TRIGGERED, &damage, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                }
            }

            protected:
                int32 damage;

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_rog_hemorrhage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
                AfterHit += SpellHitFn(spell_rog_hemorrhage_SpellScript::HandleGlyph);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rog_hemorrhage_SpellScript();
        }
};

// 1752 - Sinister Strike
class spell_rog_sinister_strike : public SpellScriptLoader
{
    public:
        spell_rog_sinister_strike() : SpellScriptLoader("spell_rog_sinister_strike") { }

        class spell_rog_sinister_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_sinister_strike_SpellScript);

            void HandleComboPoints(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Glyph of Sinister Strike
                        if (!caster->HasAura(SPELL_ROGUE_GLYPH_OF_SINISTER_STRIKE))
                            return;

                        if (roll_chance_i(20))
                            caster->CastSpell(target, SPELL_ROGUE_GLYPH_OF_SINISTER_STRIKE_TRIG, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_rog_sinister_strike_SpellScript::HandleComboPoints, EFFECT_1, SPELL_EFFECT_ADD_COMBO_POINTS);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rog_sinister_strike_SpellScript();
        }
};

class spell_rog_vanish_secondary: public SpellScriptLoader 
{
public:
    spell_rog_vanish_secondary() : SpellScriptLoader("spell_rog_vanish_secondary") {}

    class spell_rog_vanish_secondary_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_rog_vanish_secondary_AuraScript);

        enum spellId
        {
            SPELL_STEALTH_EFFECT    = 1784
        };

        void HandleCleanup(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->isAlive())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->HasSpellCooldown(SPELL_STEALTH_EFFECT))
                            caster->ToPlayer()->RemoveSpellCooldown(SPELL_STEALTH_EFFECT, true);

                        caster->CastSpell(caster, SPELL_STEALTH_EFFECT, true);
                        caster->AddUnitMovementFlag(MOVEMENTFLAG_MASK_MOVING);
                        caster->RemoveUnitMovementFlag(MOVEMENTFLAG_MASK_MOVING);
                    }
                }
            }
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_rog_vanish_secondary_AuraScript::HandleCleanup, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_rog_vanish_secondary_AuraScript();
    }
};

class spell_rog_revealing_strike : public SpellScriptLoader
{
    public:
        spell_rog_revealing_strike() : SpellScriptLoader("spell_rog_revealing_strike") { }

        enum spellId
        {
            SPELL_ROGUE_KIDNEY_SHOT     = 408,
            GLYPH_OF_REVEALING_STRIKE   = 56814,
            SPELL_ROGUE_RUPTURE         = 1943,
            SPELL_ROGUE_EXPOSE_ARMOR    = 8647
        };

        class spell_rog_revealing_strike_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_revealing_strike_AuraScript);

            void EffectRemoveStrike(AuraEffect const* aurEff, AuraEffectHandleModes mode)
            {
                if (mode != AURA_REMOVE_BY_DEFAULT)
                    return;

                if (Unit* target = GetTarget())
                {
                    if (Unit* caster = GetCaster())
                    {
                        // Kidney Shot
                        if (Aura* kidneyShot = target->GetAura(SPELL_ROGUE_KIDNEY_SHOT, caster->GetGUID()))
                        {
                            uint32 duration = kidneyShot->GetDuration();
                            caster->HasAura(GLYPH_OF_REVEALING_STRIKE) ? AddPct(duration, 45) : AddPct(duration, 35);
                            kidneyShot->SetDuration(duration);
                        }
                        // Rupture
                        if (Aura* rupture = target->GetAura(SPELL_ROGUE_RUPTURE, caster->GetGUID()))
                        {
                            uint32 dmg = rupture->GetEffect(EFFECT_0)->GetAmount();
                            caster->HasAura(GLYPH_OF_REVEALING_STRIKE) ? AddPct(dmg, 45) : AddPct(dmg, 35);
                            rupture->GetEffect(EFFECT_0)->SetAmount(dmg);
                        }
                        // Expose Armor
                        if (Aura* exposeArmor = target->GetAura(SPELL_ROGUE_EXPOSE_ARMOR, caster->GetGUID()))
                        {
                            uint32 duration = exposeArmor->GetDuration();
                            caster->HasAura(GLYPH_OF_REVEALING_STRIKE) ? AddPct(duration, 45) : AddPct(duration, 35);
                            exposeArmor->SetDuration(duration);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_rog_revealing_strike_AuraScript::EffectRemoveStrike, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_revealing_strike_AuraScript();
        }
};

class spell_rog_bandits_guile : public SpellScriptLoader
{
public:
    spell_rog_bandits_guile() : SpellScriptLoader("spell_rog_bandits_guile")
    {
    }

    class spell_rog_bandits_guile_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_bandits_guile_AuraScript);

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (Unit* target = GetTarget())
            {
                if (mode == AURA_REMOVE_BY_EXPIRE)
                    target->m_bGuilesCount = 0;
            }
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_rog_bandits_guile_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_bandits_guile_AuraScript();
    }
};

class spell_rog_smoke_bomb : public SpellScriptLoader
{
public:
    spell_rog_smoke_bomb() : SpellScriptLoader("spell_rog_smoke_bomb")
    {
    }

    class spell_rog_smoke_bomb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_smoke_bomb_AuraScript);

        void ApplySmoke(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    if (target->HasAuraType(SPELL_AURA_MOD_STEALTH))
                        target->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_rog_smoke_bomb_AuraScript::ApplySmoke, EFFECT_0, SPELL_AURA_INTERFERE_TARGETTING, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_smoke_bomb_AuraScript();
    }
};

class spell_rog_blade_flurry : public SpellScriptLoader
{
public:
    spell_rog_blade_flurry() : SpellScriptLoader("spell_rog_blade_flurry")
    {
    }

    class spell_rog_blade_flurry_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_blade_flurry_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK))
                return false;
            return true;
        }

        bool Load()
        {
            _procTarget = NULL;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            _procTarget = eventInfo.GetActor()->SelectNearbyTarget(eventInfo.GetProcTarget());

            if (!_procTarget)
                return false;

            if (eventInfo.GetDamageInfo())
            {
                int32 damage = eventInfo.GetDamageInfo()->GetDamage();
                if (GetTarget())
                    GetTarget()->CastCustomSpell(SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK, SPELLVALUE_BASE_POINT0, damage, _procTarget, true, NULL, NULL);
            }
            return _procTarget;
        }

        void Register()
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_blade_flurry_AuraScript::CheckProc);
        }

    private:
        Unit* _procTarget;
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_blade_flurry_AuraScript();
    }
};

void AddSC_rogue_spell_scripts()
{
    new spell_rog_cheat_death();
    new spell_rog_deadly_poison();
    new spell_rog_nerves_of_steel();
    new spell_rog_preparation();
    new spell_rog_prey_on_the_weak();
    new spell_rog_recuperate();
    new spell_rog_rupture();
    new spell_rog_shiv();
    new spell_rog_tricks_of_the_trade();
    new spell_rog_tricks_of_the_trade_proc();
    new spell_rog_main_gauche();
    new spell_rog_sap();
    new spell_rog_expose_armor();
    new spell_rog_backstab();
    new spell_rog_fan_of_knives();
    new spell_rog_hemorrhage();
    new spell_rog_sinister_strike();
    new spell_rog_vanish_secondary();
    new spell_rog_revealing_strike();
    new spell_rog_bandits_guile();
    new spell_rog_smoke_bomb();
    new spell_rog_blade_flurry();
}
