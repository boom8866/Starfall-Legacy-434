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
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Group.h"

enum WarriorSpells
{
    SPELL_WARRIOR_BLOOD_AND_THUNDER_RANK_1          = 84614,
    SPELL_WARRIOR_BLOOD_AND_THUNDER_RANK_2          = 84615,
    SPELL_WARRIOR_BLOODTHIRST                       = 23885,
    SPELL_WARRIOR_BLOODTHIRST_DAMAGE                = 23881,
    SPELL_WARRIOR_CHARGE                            = 34846,
    SPELL_WARRIOR_CHARGE_STUN                       = 7922,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_1                = 12162,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_2                = 12850,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_3                = 12868,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC         = 12721,
    SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_1           = 81913,
    SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_2           = 81914,
    SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_1_TRIGGERED = 85386,
    SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_2_TRIGGERED = 86624,
    SPELL_WARRIOR_EXECUTE                           = 20647,
    SPELL_WARRIOR_GLYPH_OF_EXECUTION                = 58367,
    SPELL_WARRIOR_GLYPH_OF_VIGILANCE                = 63326,
    SPELL_WARRIOR_HAMSTRING                         = 1715,
    SPELL_WARRIOR_HEROIC_FURY                       = 60970,
    SPELL_WARRIOR_IMPROVED_HAMSTRING_RANK_1         = 12289,
    SPELL_WARRIOR_IMPROVED_HAMSTRING_RANK_2         = 12668,
    SPELL_WARRIOR_IMPROVED_HAMSTRING_TRIGGERED      = 23694,
    SPELL_WARRIOR_INTERCEPT_BS_STANCE               = 20252,
    SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF        = 65156,
    SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT      = 64976,
    SPELL_WARRIOR_LAST_STAND_TRIGGERED              = 12976,
    SPELL_WARRIOR_RALLYING_CRY                      = 97462,
    SPELL_WARRIOR_RALLYING_CRY_BUFF                 = 97463,
    SPELL_WARRIOR_SLAM                              = 50782,
    SPELL_WARRIOR_SLAUGHTER_RANK_1                  = 84584,
    SPELL_WARRIOR_SLAUGHTER_RANK_2                  = 84585,
    SPELL_WARRIOR_SLAUGHTER_RANK_3                  = 84586,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK     = 26654,
    SPELL_WARRIOR_TAUNT                             = 355,
    SPELL_WARRIOR_THUNDER_CLAP                      = 6343,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1        = 46859,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2        = 46860,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1     = 64849,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2     = 64850,
    SPELL_WARRIOR_VIGILANCE_PROC                    = 50725,
    SPELL_WARRIOR_VIGILANCE_REDIRECT_THREAT         = 59665,
    SPELL_WARRIOR_VENGEANCE                         = 76691,
    SPELL_WARRIOR_HEROIC_LEAP                       = 6544,
    SPELL_WARRIOR_IMPROVED_HAMSTRING                = 23694,

    SPELL_PALADIN_BLESSING_OF_SANCTUARY             = 20911,
    SPELL_PALADIN_GREATER_BLESSING_OF_SANCTUARY     = 25899,
    SPELL_PRIEST_RENEWED_HOPE                       = 63944,
    SPELL_GEN_DAMAGE_REDUCTION_AURA                 = 68066,
    
    SPELL_WARRIOR_SECOUND_WIND_PROC_RANK_1          = 29834,
    SPELL_WARRIOR_SECOUND_WIND_PROC_RANK_2          = 29838,
    SPELL_WARRIOR_SECOUND_WIND_TRIGGER_RANK_1       = 29841,
    SPELL_WARRIOR_SECOUND_WIND_TRIGGER_RANK_2       = 29842,
    SPELL_WARRIOR_WHIRLWIND                         = 1680
};

enum WarriorSpellIcons
{
    WARRIOR_ICON_ID_SUDDEN_DEATH                    = 1989,
    WARRIOR_ICON_ID_IMPROVED_HAMSTRING              = 23,
};

/// Updated 4.3.4
class spell_warr_bloodthirst : public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst() : SpellScriptLoader("spell_warr_bloodthirst") { }

        class spell_warr_bloodthirst_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_SpellScript);

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                ApplyPct(damage, GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK));

                if (Unit* target = GetHitUnit())
                {
                    damage = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);
                    damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);
                }
                SetHitDamage(damage);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                GetCaster()->CastCustomSpell(GetCaster(), SPELL_WARRIOR_BLOODTHIRST, &damage, NULL, NULL, true, NULL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_bloodthirst_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHit += SpellEffectFn(spell_warr_bloodthirst_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_bloodthirst_heal : public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst_heal() : SpellScriptLoader("spell_warr_bloodthirst_heal") { }

        class spell_warr_bloodthirst_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_heal_SpellScript);

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOODTHIRST_DAMAGE))
                    SetHitHeal(GetCaster()->CountPctFromMaxHealth(spellInfo->Effects[EFFECT_1].CalcValue(GetCaster())) / 1000);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_bloodthirst_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_heal_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_charge : public SpellScriptLoader
{
    public:
        spell_warr_charge() : SpellScriptLoader("spell_warr_charge") { }

        class spell_warr_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_charge_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(96216) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_CHARGE))
                    return false;
                return true;
            }

            void HandleAfterCast()
            {
                // Juggernaut Shared Cooldown
                if (GetCaster()->HasAura(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT))
                    GetCaster()->CastSpell(GetCaster(), 96216, false);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 chargeBasePoints0 = GetEffectValue();
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                caster->CastCustomSpell(caster, SPELL_WARRIOR_CHARGE, &chargeBasePoints0, NULL, NULL, true);

                // Stuns the target
                Unit* target = GetExplTargetUnit();
                if (!target)
                    return;

                caster->CastCustomSpell(target, SPELL_WARRIOR_CHARGE_STUN, 0, NULL, NULL, true);

                // Check for Blitz
                if (caster->HasAura(80976) || caster->HasAura(80977))
                {
                    caster->ToPlayer()->ModifyPower(POWER_RAGE, 5);
                    std::list<Unit*> nearby_units = target->GetNearestUnitsList(5);

                    // Check if there are other units next to the target
                    if (!nearby_units.empty())
                    {
                        if (!nearby_units.front()->IsFriendlyTo(caster))
                        {
                            caster->CastCustomSpell(nearby_units.front(), SPELL_WARRIOR_CHARGE_STUN, 0, NULL, NULL, true);
                            nearby_units.pop_front();
                        }
                    }
                    if (caster->HasAura(80977)) // Blitz level 2
                    {
                        // Level 2 grants 10 additional rage
                        caster->ToPlayer()->ModifyPower(POWER_RAGE, 5);

                        if (!nearby_units.empty())
                        {
                            if (!nearby_units.front()->IsFriendlyTo(caster))
                                caster->CastCustomSpell(nearby_units.front(), SPELL_WARRIOR_CHARGE_STUN, 0, NULL, NULL, true);
                        }
                    }
                }
                // Juggernaut crit bonus
                if (caster->HasAura(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT))
                    caster->CastSpell(caster, SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warr_charge_SpellScript::HandleAfterCast);
                OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_charge_SpellScript();
        }
};

// Intercept
// Spell Id: 20252
class spell_warr_intercept : public SpellScriptLoader
{
public:
    spell_warr_intercept() : SpellScriptLoader("spell_warr_intercept") { }

    class spell_warr_intercept_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_intercept_SpellScript);

        void HandleAfterCast()
        {
            // Juggernaut Shared Cooldown
            if (GetCaster()->HasAura(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT))
                GetCaster()->CastSpell(GetCaster(), 96215, false);
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_warr_intercept_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_intercept_SpellScript();
    }
};

/// Updated 4.3.4
class spell_warr_concussion_blow : public SpellScriptLoader
{
    public:
        spell_warr_concussion_blow() : SpellScriptLoader("spell_warr_concussion_blow") { }

        class spell_warr_concussion_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_concussion_blow_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                SetHitDamage(CalculatePct(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK), GetEffectValue()));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_concussion_blow_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_concussion_blow_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_deep_wounds : public SpellScriptLoader
{
    public:
        spell_warr_deep_wounds() : SpellScriptLoader("spell_warr_deep_wounds") { }

        class spell_warr_deep_wounds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_deep_wounds_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_1) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_2) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_3))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    float damage;
                    // DW should benefit of attack power, damage percent mods etc.
                    // TODO: check if using offhand damage is correct and if it should be divided by 2
                    if (caster->haveOffhandWeapon() && caster->getAttackTimer(BASE_ATTACK) > caster->getAttackTimer(OFF_ATTACK))
                        damage = (caster->GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE) + caster->GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE))/2;
                    else
                        damage = (caster->GetFloatValue(UNIT_FIELD_MINDAMAGE) + caster->GetFloatValue(UNIT_FIELD_MAXDAMAGE))/2;

                    switch (GetSpellInfo()->Id)
                    {
                        case 12162: damage *= 0.16f; break; // Rank 1
                        case 12850: damage *= 0.32f; break; // Rank 2
                        case 12868: damage *= 0.48f; break; // Rank 3
                        default:
                            sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell::EffectDummy: Spell %u not handled in DW", GetSpellInfo()->Id);
                            return;
                    };

                    // get remaining damage of old Deep Wound aura
                    AuraEffect* deepWound = unitTarget->GetAuraEffect(SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC, 0);
                    if (deepWound)
                    {
                        int32 remainingTicks = deepWound->GetBase()->GetDuration() / deepWound->GetAmplitude();
                        damage += remainingTicks * deepWound->GetAmount();
                    }

                    // 1 tick/sec * 6 sec = 6 ticks
                    int32 deepWoundsDotBasePoints0 = int32(damage / 6);
                    caster->CastCustomSpell(unitTarget, SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC, &deepWoundsDotBasePoints0, NULL, NULL, true, NULL);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_deep_wounds_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_deep_wounds_SpellScript();
        }
};

// 85386 & 86624 - die by the sword
class spell_warr_die_by_the_sword: public SpellScriptLoader
{
    public:
        spell_warr_die_by_the_sword() :
                SpellScriptLoader("spell_warr_die_by_the_sword")
        {
        }

        class spell_warr_die_by_the_sword_SpellScript: public SpellScript
        {
                PrepareSpellScript(spell_warr_die_by_the_sword_SpellScript);

                bool Validate( SpellInfo const* /*spellInfo*/)
                {
                    if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_1_TRIGGERED)
                     || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_2_TRIGGERED))
                        return false;
                    return true;
                }

                SpellCastResult CheckCast()
                {
                    Unit* caster = GetCaster();
                    if (caster->GetMaxHealth() * 0.2f >= caster->GetHealth())
                        return SPELL_CAST_OK;
                    return SPELL_FAILED_DONT_REPORT;
                }

                void OnEffectApplyCooldown(SpellEffIndex /*effIndex*/)
                {
                    if(GetCaster()->HasAura(SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_1))
                        GetCaster()->ToPlayer()->AddSpellCooldown(SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_1_TRIGGERED, 0, time(NULL) + 120);
                    else if(GetCaster()->HasAura(SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_2))
                        GetCaster()->ToPlayer()->AddSpellCooldown(SPELL_WARRIOR_DIE_BY_THE_SWORD_RANK_2_TRIGGERED, 0, time(NULL) + 120);
                }

                void Register()
                {
                    OnCheckCast += SpellCheckCastFn(spell_warr_die_by_the_sword_SpellScript::CheckCast);
                    OnEffectHitTarget += SpellEffectFn(spell_warr_die_by_the_sword_SpellScript::OnEffectApplyCooldown, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
                }
            };

            SpellScript* GetSpellScript() const
            {
                return new spell_warr_die_by_the_sword_SpellScript();
            }
 };

/// Updated 4.3.4
class spell_warr_execute : public SpellScriptLoader
{
    public:
        spell_warr_execute() : SpellScriptLoader("spell_warr_execute") { }

        class spell_warr_execute_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_execute_SpellScript);

            enum spellId
            {
                SPELL_BERSERKER_STANCE_PASSIVE  = 7381
            };

            void HandleEffect(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (GetHitUnit())
                {
                    SpellInfo const* spellInfo = GetSpellInfo();
                    int32 rageUsed = std::min<int32>(300, caster->GetPower(POWER_RAGE));
                    int32 newRage = std::max<int32>(0, caster->GetPower(POWER_RAGE) - rageUsed);

                    // Sudden Death rage save
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_GENERIC, WARRIOR_ICON_ID_SUDDEN_DEATH, EFFECT_0))
                    {
                        int32 ragesave = aurEff->GetSpellInfo()->Effects[EFFECT_0].CalcValue() * 10;
                        newRage = std::max(newRage, ragesave);
                    }

                    caster->SetPower(POWER_RAGE, uint32(newRage));

                    /// Formula taken from the DBC: "${10+$AP*0.437*$m1/100}"
                    int32 baseDamage = int32(10 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.437f * GetEffectValue() / 100.0f);
                    /// Formula taken from the DBC: "${$ap*0.874*$m1/100-1} = 20 rage"
                    int32 moreDamage = int32(rageUsed * (caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.874f * GetEffectValue() / 100.0f - 1) / 200);
                    SetHitDamage(baseDamage + moreDamage);

                    // Berserker Stance
                    if (caster->HasAura(SPELL_BERSERKER_STANCE_PASSIVE))
                        SetHitDamage(GetHitDamage() + (GetHitDamage() * 0.10f));
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_execute_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);

            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_execute_SpellScript();
        }
};

// 60970 - Heroic Fury
class spell_warr_heroic_fury : public SpellScriptLoader
{
public:
    spell_warr_heroic_fury() : SpellScriptLoader("spell_warr_heroic_fury") {}

    class spell_warr_heroic_fury_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_heroic_fury_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if(!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_HEROIC_FURY))
                return false;
            return true;
        }

        void OnEffectResetCooldown(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if(caster->ToPlayer()->HasSpell(20252))
                caster->ToPlayer()->RemoveSpellCooldown(20252, true);
        }

        void Register()
        {
          OnEffectHit += SpellEffectFn(spell_warr_heroic_fury_SpellScript::OnEffectResetCooldown, EFFECT_2, SPELL_EFFECT_APPLY_AURA);
        }

    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_heroic_fury_SpellScript;
    }
};

// 1715 - Hamstring
class spell_warr_hamstring : public SpellScriptLoader
{
    public:
        spell_warr_hamstring() : SpellScriptLoader("spell_warr_hamstring") { }

        class spell_warr_hamstring_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_hamstring_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_IMPROVED_HAMSTRING))
                    return false;
                return true;
            }

            void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();

                if (!caster || !caster->ToPlayer() || !target)
                    return;

                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_WARRIOR, WARRIOR_ICON_ID_IMPROVED_HAMSTRING, EFFECT_0))
                {
                    if(!caster->ToPlayer()->HasSpellCooldown(SPELL_WARRIOR_IMPROVED_HAMSTRING))
                    {
                        caster->CastSpell(target, SPELL_WARRIOR_IMPROVED_HAMSTRING, true);
                        caster->ToPlayer()->AddSpellCooldown(SPELL_WARRIOR_IMPROVED_HAMSTRING, NULL, time(NULL) + aurEff->GetAmount());
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_hamstring_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAPPLY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_hamstring_AuraScript();
        }
};

// 59725 - Improved Spell Reflection
class spell_warr_improved_spell_reflection : public SpellScriptLoader
{
    public:
        spell_warr_improved_spell_reflection() : SpellScriptLoader("spell_warr_improved_spell_reflection") { }

        class spell_warr_improved_spell_reflection_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_improved_spell_reflection_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (GetCaster())
                    unitList.remove(GetCaster());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_improved_spell_reflection_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_improved_spell_reflection_SpellScript();
        }
};

// 5246 - Intimidating Shout
class spell_warr_intimidating_shout : public SpellScriptLoader
{
    public:
        spell_warr_intimidating_shout() : SpellScriptLoader("spell_warr_intimidating_shout") { }

        class spell_warr_intimidating_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_intimidating_shout_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove(GetExplTargetWorldObject());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_intimidating_shout_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_last_stand : public SpellScriptLoader
{
    public:
        spell_warr_last_stand() : SpellScriptLoader("spell_warr_last_stand") { }

        class spell_warr_last_stand_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_last_stand_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_LAST_STAND_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(GetEffectValue()));
                    caster->CastCustomSpell(caster, SPELL_WARRIOR_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
                }
            }

            void Register()
            {
                // add dummy effect spell handler to Last Stand
                OnEffectHit += SpellEffectFn(spell_warr_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_last_stand_SpellScript();
        }
};

// 7384, 7887, 11584, 11585 - Overpower
class spell_warr_overpower : public SpellScriptLoader
{
    public:
        spell_warr_overpower() : SpellScriptLoader("spell_warr_overpower") { }

        class spell_warr_overpower_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_overpower_SpellScript);

            void HandleEffect(SpellEffIndex /*effIndex*/)
            {
                uint32 spellId = 0;
                if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1))
                    spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1;
                else if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2))
                    spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2;

                if (!spellId)
                    return;

                if (Player* target = GetHitPlayer())
                    if (target->HasUnitState(UNIT_STATE_CASTING))
                        target->CastSpell(target, spellId, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_overpower_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_ANY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_overpower_SpellScript();
        }
};

// 97462 - Rallying Cry
class spell_warr_rallying_cry: public SpellScriptLoader
{
public:
    spell_warr_rallying_cry() : SpellScriptLoader("spell_warr_rallying_cry") { }

    class spell_warr_rallying_cry_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warr_rallying_cry_SpellScript);

        bool Validate( SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_RALLYING_CRY))
                return false;
            return true;
        }
        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            if(Group* group = caster->GetGroup())
            {
                for( auto memberslot : group->GetMemberSlots())
                {
                    if (Player* groupmember = ObjectAccessor::FindPlayer(memberslot.guid))
                    {
                        int32 basepoints0 = groupmember->CountPctFromMaxHealth(20);
                        if(caster->IsInRange(groupmember, 0, 30, false))
                            caster->CastCustomSpell(groupmember, SPELL_WARRIOR_RALLYING_CRY_BUFF, &basepoints0, NULL, NULL, true, NULL);
                    }
                }
            }
            else
            {
                int32 basepoints0 = caster->CountPctFromMaxHealth(20);
                caster->CastCustomSpell(caster, SPELL_WARRIOR_RALLYING_CRY_BUFF, &basepoints0 ,NULL, NULL, true, NULL);
            }

        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_warr_rallying_cry_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_rallying_cry_SpellScript();
    }
};

// -772 - Rend
class spell_warr_rend : public SpellScriptLoader
{
    public:
        spell_warr_rend() : SpellScriptLoader("spell_warr_rend") { }

        class spell_warr_rend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_rend_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* caster = GetCaster())
                {
                    canBeRecalculated = false;

                    // $0.2 * (($MWB + $mwb) / 2 + $AP / 14 * $MWS) bonus per tick
                    float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                    int32 mws = caster->GetBaseAttackTime(BASE_ATTACK);
                    float mwbMin = caster->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
                    float mwbMax = caster->GetWeaponDamageRange(BASE_ATTACK, MAXDAMAGE);
                    float mwb = ((mwbMin + mwbMax) / 2 + ap * mws / 14000) * 0.2f;
                    amount += int32(caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), mwb));

                    // "If used while your target is above 75% health, Rend does 35% more damage."
                    // as for 3.1.3 only ranks above 9 (wrong tooltip?)
                    if (GetSpellInfo()->GetRank() >= 9)
                    {
                        if (GetUnitOwner()->HasAuraState(AURA_STATE_HEALTH_ABOVE_75_PERCENT, GetSpellInfo(), caster))
                            AddPct(amount, GetSpellInfo()->Effects[EFFECT_2].CalcValue(caster));
                    }
                }
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_rend_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_rend_AuraScript();
        }
};

// 64380, 65941 - Shattering Throw
class spell_warr_shattering_throw : public SpellScriptLoader
{
    public:
        spell_warr_shattering_throw() : SpellScriptLoader("spell_warr_shattering_throw") { }

        class spell_warr_shattering_throw_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shattering_throw_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                // remove shields, will still display immune to damage part
                if (Unit* target = GetHitUnit())
                    target->RemoveAurasWithMechanic(1 << MECHANIC_IMMUNE_SHIELD, AURA_REMOVE_BY_ENEMY_SPELL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shattering_throw_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_slam : public SpellScriptLoader
{
    public:
        spell_warr_slam() : SpellScriptLoader("spell_warr_slam") { }

        class spell_warr_slam_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_slam_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAM))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 bp0 = GetEffectValue();
                if (GetHitUnit())
                    GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_WARRIOR_SLAM, &bp0, NULL, NULL, true, 0);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_slam_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_slam_SpellScript();
        }
};

// Triggered by Lambs to the Slaughter (84583)
class spell_warr_slaughter : public SpellScriptLoader
{
    public:
        spell_warr_slaughter() : SpellScriptLoader("spell_warr_slaughter") { }

        class spell_warr_slaughter_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_slaughter_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTER_RANK_1) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTER_RANK_2) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAUGHTER_RANK_3))
                    return false;
                return true;
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* _procTarget = caster->getVictim())
                        if (_procTarget && _procTarget->HasAura(94009, caster->GetGUID())) // we check if rend is active on the target
                            _procTarget->GetAura(94009, caster->GetGUID())->RefreshDuration();
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_slaughter_AuraScript::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER,AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_slaughter_AuraScript();
        }
};

// 12328, 18765, 35429 - Sweeping Strikes
class spell_warr_sweeping_strikes : public SpellScriptLoader
{
    public:
        spell_warr_sweeping_strikes() : SpellScriptLoader("spell_warr_sweeping_strikes") { }

        class spell_warr_sweeping_strikes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_sweeping_strikes_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK))
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
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (_procTarget && _procTarget != NULL && caster->IsValidAttackTarget(target))
                            target->CastSpell(_procTarget, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK, true, NULL, aurEff);
                    }
                }
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_warr_sweeping_strikes_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warr_sweeping_strikes_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_sweeping_strikes_AuraScript();
        }
};

// 6343 Thunder Clap (incl. Blood and Thunder)
class spell_warr_thunder_clap: SpellScriptLoader
{
    public:
        spell_warr_thunder_clap() :
                SpellScriptLoader("spell_warr_thunder_clap") { }

        class spell_warr_thunder_clap_SpellScript: public SpellScript
        {
            public:
                spell_warr_thunder_clap_SpellScript() : foundActiveRend(false) { }

            private:
                PrepareSpellScript(spell_warr_thunder_clap_SpellScript);

                bool foundActiveRend;

                bool Validate( SpellInfo const* /*spellInfo*/)
                {
                    if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_THUNDER_CLAP))
                        return false;
                    if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOOD_AND_THUNDER_RANK_1))
                        return false;
                    if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOOD_AND_THUNDER_RANK_2))
                        return false;
                    return true;
                }

                void FindTargets(std::list<WorldObject*>& targets)
                {
                    for(auto element : targets)
                    {
                        if(element && element->ToUnit() && element->ToUnit()->HasAura(94009))
                        {
                            foundActiveRend = true;
                            break;

                        }
                    }
                }

                void HandleTalent()          // Blood and Thunder
                {
                    Player* caster = GetCaster()->ToPlayer();
                    if(foundActiveRend && (caster->HasAura(SPELL_WARRIOR_BLOOD_AND_THUNDER_RANK_2)
                                    || (caster->HasAura(SPELL_WARRIOR_BLOOD_AND_THUNDER_RANK_1) && roll_chance_i(50))))
                    {
                    if(Unit* target = GetHitUnit())
                        caster->CastSpell(target,94009,true);
                    }
                }

                void Register()
                {
                    OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_thunder_clap_SpellScript::FindTargets,EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                    AfterHit += SpellHitFn(spell_warr_thunder_clap_SpellScript::HandleTalent);
                }



            };
        SpellScript* GetSpellScript() const
        {
            return new spell_warr_thunder_clap_SpellScript();
        }
};

// 50720 - Vigilance
class spell_warr_vigilance : public SpellScriptLoader
{
    public:
        spell_warr_vigilance() : SpellScriptLoader("spell_warr_vigilance") { }

        class spell_warr_vigilance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_vigilance_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_VENGEANCE))
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
                _procTarget = GetCaster();
                return _procTarget && eventInfo.GetDamageInfo();
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                int32 damage = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue()));

                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_VIGILANCE_PROC, true, NULL, aurEff);
                _procTarget->CastCustomSpell(_procTarget, SPELL_WARRIOR_VENGEANCE, &damage, &damage, &damage, true, NULL, aurEff);
            }

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_WARRIOR_VENGEANCE))
                        caster->RemoveAurasDueToSpell(SPELL_WARRIOR_VENGEANCE);
                }
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_warr_vigilance_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warr_vigilance_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_vigilance_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_vigilance_AuraScript();
        }
};

// 50725 Vigilance
class spell_warr_vigilance_trigger : public SpellScriptLoader
{
    public:
        spell_warr_vigilance_trigger() : SpellScriptLoader("spell_warr_vigilance_trigger") { }

        class spell_warr_vigilance_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_vigilance_trigger_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                // Remove Taunt cooldown
                if (Player* target = GetHitPlayer())
                    target->RemoveSpellCooldown(SPELL_WARRIOR_TAUNT, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_vigilance_trigger_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_vigilance_trigger_SpellScript();
        }
};

// 76838 - Strikes of Opportuniy
class spell_warr_strikes_of_opportunity : public SpellScriptLoader
{
    public:
       spell_warr_strikes_of_opportunity() : SpellScriptLoader("spell_warr_strikes_of_opportunity") { }

       class spell_warr_strikes_of_opportunity_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_warr_strikes_of_opportunity_AuraScript);

           enum effectStrikesOfOpportunity
           {
                SPELL_STRIKES_OF_OPPORTUNITY_TRIGGERED = 76858
           };

           void HandleProc(AuraEffect const* aurEff, ProcEventInfo &procInfo)
           {
               // aurEff->GetAmount() % Chance to proc the event ...
               if (urand(0,99) >= uint32(aurEff->GetAmount()))
                   return;

               Unit *caster = GetCaster();
               Unit *target = procInfo.GetActionTarget();

               // Cast only for Warriors that have Strikes of Opportunity mastery active
               if (!caster->HasAura(76838))
                   return;

               if (caster && target)
                   caster->CastSpell(target, SPELL_STRIKES_OF_OPPORTUNITY_TRIGGERED, true, NULL, aurEff);
           }

           void Register()
           {
                OnEffectProc += AuraEffectProcFn(spell_warr_strikes_of_opportunity_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_warr_strikes_of_opportunity_AuraScript();
       }
};

class spell_warr_heroic_leap : public SpellScriptLoader
{
public:
    spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

    class spell_warr_heroic_leap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_heroic_leap_SpellScript)

        bool Validate(SpellInfo const * /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_HEROIC_LEAP))
                return false;
            return true;
        }

        bool Load()
        {
            if (!GetCaster())
                return false;

            return true;
        }

        SpellCastResult CheckElevation()
        {
            Unit* caster = GetCaster();
            WorldLocation const* const dest = GetExplTargetDest();

            if (dest->GetPositionZ() > caster->GetPositionZ() + 5.0f) // Cant jump to higher ground
                return SPELL_FAILED_NOPATH;
            return SPELL_CAST_OK;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap_SpellScript::CheckElevation);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_warr_heroic_leap_SpellScript();
    }
};

// 32216 - Victorious
// 82368 - Victorious
class spell_warr_victorious : public SpellScriptLoader
{
    public:
        spell_warr_victorious() : SpellScriptLoader("spell_warr_victorious") { }

        class spell_warr_victorious_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_victorious_AuraScript);

            void HandleEffectProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->RemoveAura(GetId());
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_victorious_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_victorious_AuraScript();
        }
};

class spell_warr_second_wind_proc : public SpellScriptLoader
{
    public:
        spell_warr_second_wind_proc() : SpellScriptLoader("spell_warr_second_wind_proc") { }

        class spell_warr_second_wind_proc_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_second_wind_proc_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SECOUND_WIND_PROC_RANK_1) ||
                    !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SECOUND_WIND_PROC_RANK_2) ||
                    !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SECOUND_WIND_TRIGGER_RANK_1) ||
                    !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SECOUND_WIND_TRIGGER_RANK_2))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                if (eventInfo.GetProcTarget() == GetTarget())
                    return false;
                if (!(eventInfo.GetDamageInfo() || eventInfo.GetDamageInfo()->GetSpellInfo()->GetAllEffectsMechanicMask() & ((1 << MECHANIC_ROOT) | (1 << MECHANIC_STUN))))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                uint32 spellId = 0;

                if (GetSpellInfo()->Id == SPELL_WARRIOR_SECOUND_WIND_PROC_RANK_1)
                    spellId = SPELL_WARRIOR_SECOUND_WIND_TRIGGER_RANK_1;
                else if (GetSpellInfo()->Id == SPELL_WARRIOR_SECOUND_WIND_PROC_RANK_2)
                    spellId = SPELL_WARRIOR_SECOUND_WIND_TRIGGER_RANK_2;
                if (!spellId)
                    return;


                if (GetTarget()->HasAuraWithMechanic((1 << MECHANIC_STUN) | (1 << MECHANIC_ROOT)))
                    GetTarget()->CastSpell(GetTarget(), spellId, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_warr_second_wind_proc_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warr_second_wind_proc_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_second_wind_proc_AuraScript();
        }
};

class spell_warr_second_wind_trigger : public SpellScriptLoader
{
    public:
        spell_warr_second_wind_trigger() : SpellScriptLoader("spell_warr_second_wind_trigger") { }

        class spell_warr_second_wind_trigger_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_second_wind_trigger_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = int32(GetUnitOwner()->CountPctFromMaxHealth(amount));
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_second_wind_trigger_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_second_wind_trigger_AuraScript();
        }
};

class spell_warr_cruelty : public SpellScriptLoader
{
public:
    spell_warr_cruelty() : SpellScriptLoader("spell_warr_cruelty") { }

    class spell_warr_cruelty_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_cruelty_AuraScript);

        void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
        {
            if (!spellMod)
            {
                spellMod = new SpellModifier(GetAura());
                spellMod->op = SPELLMOD_CRITICAL_CHANCE;
                spellMod->type = SPELLMOD_FLAT;
                spellMod->spellId = GetId();
                spellMod->mask = GetSpellInfo()->Effects[aurEff->GetEffIndex()].SpellClassMask;
            }
            spellMod->value = aurEff->GetAmount();
        }

        void Register()
        {
            DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_warr_cruelty_AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_cruelty_AuraScript();
    }
};

/// Updated 4.3.4
// 78 Heroic Strike
class spell_warr_heroic_strike : public SpellScriptLoader
{
public:
    spell_warr_heroic_strike() : SpellScriptLoader("spell_warr_heroic_strike") { }

    class spell_warr_heroic_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_heroic_strike_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // An attack that instantly deals {8+ap*60/100} physical damage. A good attack for moments of excess rage.
            if (Unit* caster = GetCaster())
            {
                int32 damage = int32(8 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.6f);

                if (caster->HasAura(81099) && caster->haveOffhandWeapon()) // Single Minded Fury
                    AddPct(damage, 20);

                // Battle Stance
                if (caster->HasAura(2457))
                    AddPct(damage, 5);

                // Berserker Stance
                if (caster->HasAura(2458))
                    AddPct(damage, 10);

                SetHitDamage(damage);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_heroic_strike_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_heroic_strike_SpellScript();
    }
};

// Warrior - Shattering Throw
// Spell Id: 64382
class spell_warr_shattering_throw_damage : public SpellScriptLoader
{
public:
    spell_warr_shattering_throw_damage() : SpellScriptLoader("spell_warr_shattering_throw_damage") { }

    class spell_warr_shattering_throw_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shattering_throw_damage_SpellScript);

        enum spellId
        {
            SPELL_HEROIC_THROW_DISPEL   = 64340
        };

        void CalculateDamage(SpellEffIndex effect)
        {
            if (Unit* caster = GetCaster())
            {
                // Formula: AttackPower * 0.5
                int32 nHitDamage = int32(12 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.5f);
                SetHitDamage(nHitDamage);
            }
        }

        void HandleRemoveImmunities()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                    caster->CastSpell(target, SPELL_HEROIC_THROW_DISPEL, true);
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_warr_shattering_throw_damage_SpellScript::HandleRemoveImmunities);
            OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_damage::spell_warr_shattering_throw_damage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_shattering_throw_damage_SpellScript();
    }
};

// Cleave
// Spell Id: 845
class spell_warr_cleave : public SpellScriptLoader
{
public:
    spell_warr_cleave() : SpellScriptLoader("spell_warr_cleave") { }

    class spell_warr_cleave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_cleave_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            // Formula: 6 + AttackPower * 0.45
            int32 nHitDamage = int32(6 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.45f);

            // Caster Has Meat Cleaver Buff
            if (Aura* aura = caster->GetAura(85738))
                nHitDamage += nHitDamage * (float(aura->GetSpellInfo()->Effects[0].BasePoints * aura->GetStackAmount())/100);
            else if (Aura* aura = caster->GetAura(85739))
                nHitDamage += nHitDamage * (float(aura->GetSpellInfo()->Effects[0].BasePoints * aura->GetStackAmount())/100);

            // Single Minded Fury
            if (caster->HasAura(81099) && caster->haveOffhandWeapon())
                AddPct(nHitDamage, 20);

            // Battle Stance
            if (caster->HasAura(2457))
                AddPct(nHitDamage, 5);

            // Berserker Stance
            if (caster->HasAura(2458))
                AddPct(nHitDamage, 10);

            SetHitDamage(nHitDamage);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_cleave::spell_warr_cleave_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_cleave_SpellScript();
    }
};

/// Updated 4.3.4
// Spell Id: 52174 Heroic Leap
// Triggered By: 6544
class spell_warr_heroic_leap_damage : public SpellScriptLoader
{
public:
    spell_warr_heroic_leap_damage() : SpellScriptLoader("spell_warr_heroic_leap_damage") { }

    class spell_warr_heroic_leap_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_heroic_leap_damage_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Leap through the air towards a targeted location, slamming down with destructive force to deal 1 + 0.5 * AP damage on all enemies within 8 yards.
            // Formula: 1 + AttackPower * 0.5
            if (Unit* caster = GetCaster())
                SetHitDamage(int32(1 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.5f));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_heroic_leap_damage::spell_warr_heroic_leap_damage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_heroic_leap_damage_SpellScript();
    }
};

// Intercept
// Spell Id: 20253
// Triggered By: 20252
class spell_warr_intercept_triggered : public SpellScriptLoader
{
public:
    spell_warr_intercept_triggered() : SpellScriptLoader("spell_warr_intercept_triggered") { }

    class spell_warr_intercept_triggered_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_intercept_triggered_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Formula: 1 + AttackPower * 0.12
            if (Unit* caster = GetCaster())
                SetHitDamage(int32(1 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.12f));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_intercept_triggered::spell_warr_intercept_triggered_SpellScript::CalculateDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_intercept_triggered_SpellScript();
    }
};

class spell_warr_whirlwind : public SpellScriptLoader
{
public:
    spell_warr_whirlwind() : SpellScriptLoader("spell_warr_whirlwind")
    {
    }

    class spell_warr_whirlwind_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_whirlwind_SpellScript);

        void CheckTargets(std::list<WorldObject*>& targets)
        {
            reduction = targets.size() >= 4 ? true : false;
        }

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (GetCaster()->ToPlayer()->HasSpellCooldown(SPELL_WARRIOR_WHIRLWIND))
                {
                    if (reduction)
                    {
                        uint32 updatedCooldown = caster->ToPlayer()->GetSpellCooldownDelay(SPELL_WARRIOR_WHIRLWIND);
                        if (updatedCooldown <= 6)
                            updatedCooldown = 0;
                        else
                            updatedCooldown -= 6;

                        caster->ToPlayer()->AddSpellCooldown(SPELL_WARRIOR_WHIRLWIND, 0, uint32(time(NULL) + updatedCooldown));

                        WorldPacket data(SMSG_MODIFY_COOLDOWN, 4 + 8 + 4);
                        data << uint32(SPELL_WARRIOR_WHIRLWIND);
                        data << uint64(caster->GetGUID());
                        data << int32(-6000);
                        caster->ToPlayer()->GetSession()->SendPacket(&data);
                    }
                }
            }
        }

    protected:
        bool reduction;

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_whirlwind_SpellScript::CheckTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHit += SpellEffectFn(spell_warr_whirlwind_SpellScript::HandleEffect, EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
        }

    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_whirlwind_SpellScript();
    }
};

class spell_warr_defensive_stance : public SpellScriptLoader
{
public:
    spell_warr_defensive_stance() : SpellScriptLoader("spell_warr_defensive_stance")
    {
    }

    class spell_warr_defensive_stance_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_defensive_stance_AuraScript);

        enum spellId
        {
            SPELL_IMMUNE_TO_DAZE    = 57416,
            SPELL_TALENT_BOD_R1     = 29593,
            SPELL_TALENT_BOD_R2     = 29594
        };

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_TALENT_BOD_R1) || caster->HasAura(SPELL_TALENT_BOD_R2))
                    caster->CastSpell(caster, SPELL_IMMUNE_TO_DAZE, true);
            }
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_IMMUNE_TO_DAZE))
                    caster->RemoveAurasDueToSpell(SPELL_IMMUNE_TO_DAZE);
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectRemoveFn(spell_warr_defensive_stance_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_warr_defensive_stance_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_defensive_stance_AuraScript();
    }
};

void AddSC_warrior_spell_scripts()
{
    new spell_warr_bloodthirst();
    new spell_warr_bloodthirst_heal();
    new spell_warr_charge();
    new spell_warr_intercept();
    new spell_warr_concussion_blow();
    new spell_warr_deep_wounds();
    new spell_warr_die_by_the_sword();
    new spell_warr_execute();
    new spell_warr_heroic_fury();
    new spell_warr_hamstring();
    new spell_warr_improved_spell_reflection();
    new spell_warr_intimidating_shout();
    new spell_warr_last_stand();
    new spell_warr_overpower();
    new spell_warr_rallying_cry();
    new spell_warr_rend();
    new spell_warr_shattering_throw();
    new spell_warr_slam();
    new spell_warr_slaughter();
    new spell_warr_sweeping_strikes();
    new spell_warr_thunder_clap();
    new spell_warr_vigilance();
    new spell_warr_vigilance_trigger();
    new spell_warr_strikes_of_opportunity();
    new spell_warr_heroic_leap();
    new spell_warr_victorious();
    new spell_warr_second_wind_proc();
    new spell_warr_second_wind_trigger();
    new spell_warr_cruelty();
    new spell_warr_heroic_strike();
    new spell_warr_shattering_throw_damage();
    new spell_warr_cleave();
    new spell_warr_heroic_leap_damage();
    new spell_warr_intercept_triggered();
    new spell_warr_whirlwind();
    new spell_warr_defensive_stance();
}
