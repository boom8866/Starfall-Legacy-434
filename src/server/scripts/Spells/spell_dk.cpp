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
 * Scripts for spells with SPELLFAMILY_DEATHKNIGHT and SPELLFAMILY_GENERIC spells used by deathknight players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dk_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum DeathKnightSpells
{
    SPELL_DK_DEATH_GRIP                         = 49576,
    SPELL_DK_GLYPH_OF_RESILIENT_GRIP            = 59309,
    SPELL_DK_ANTI_MAGIC_SHELL_TALENT            = 51052,
    SPELL_DK_BLACK_ICE_R1                       = 49140,
    SPELL_DK_BLOOD_BOIL_TRIGGERED               = 65658,
    SPELL_DK_BLOOD_GORGED_HEAL                  = 50454,
    SPELL_DK_BLOODSHIELD                        = 77513,
    SPELL_DK_BLOODSHIELD_ABSORB                 = 77535,
    SPELL_DK_CORPSE_EXPLOSION_TRIGGERED         = 43999,
    SPELL_DK_CORPSE_EXPLOSION_VISUAL            = 51270,
    SPELL_DK_DARK_SUCCOR                        = 101568,
    SPELL_DK_DEATH_COIL_DAMAGE                  = 47632,
    SPELL_DK_DEATH_COIL_HEAL                    = 47633,
    SPELL_DK_DEATH_STRIKE_HEAL                  = 45470,
    DK_SPELL_FROST_PRESENCE                     = 48266,
    DK_SPELL_IMPROVED_FROST_PRESENCE_TRIGGERED  = 63621,
    SPELL_DK_GHOUL_EXPLODE                      = 47496,
    SPELL_DK_GLYPH_OF_ICEBOUND_FORTITUDE        = 58625,
    SPELL_DK_RUNIC_POWER_ENERGIZE               = 49088,
    SPELL_DK_SCOURGE_STRIKE_TRIGGERED           = 70890,
    SPELL_DK_WILL_OF_THE_NECROPOLIS_TALENT_R1   = 49189,
    SPELL_DK_WILL_OF_THE_NECROPOLIS_AURA_R1     = 52284,
    SPELL_DK_BLOOD_PRESENCE                     = 48263,
    SPELL_DK_IMPROVED_BLOOD_PRESENCE_TRIGGERED  = 63611,
    SPELL_DK_UNHOLY_PRESENCE                    = 48265,
    SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED = 63622,
    SPELL_DK_ITEM_SIGIL_VENGEFUL_HEART          = 64962,
    SPELL_DK_ITEM_T8_MELEE_4P_BONUS             = 64736,
    SPELL_DK_MASTER_OF_GHOULS                   = 52143,
    SPELL_DK_RUNIC_CORRUPTION_TRIGGER           = 51460,
    SPELL_DK_RUNIC_CORRUPTION_R1                = 51459,
    SPELL_DK_RUNIC_CORRUPTION_R2                = 51462,
    SPELL_DK_DEATH_COIL_CAST                    = 47541,
    SPELL_DK_FROST_STRIKE                       = 49143,
    SPELL_DK_RUNE_STRIKE                        = 56815,

    SPELL_RAISE_DEAD_TALENT                     = 0,
};

enum DeathKnightSpellIcons
{
    DK_ICON_ID_IMPROVED_DEATH_STRIKE            = 2751
};

// 50462 - Anti-Magic Shell (on raid member)
class spell_dk_anti_magic_shell_raid : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_shell_raid() : SpellScriptLoader("spell_dk_anti_magic_shell_raid") { }

        class spell_dk_anti_magic_shell_raid_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_shell_raid_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // TODO: this should absorb limited amount of damage, but no info on calculation formula
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_raid_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_raid_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_anti_magic_shell_raid_AuraScript();
        }
};

// 48707 - Anti-Magic Shell (on self)
class spell_dk_anti_magic_shell_self : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_shell_self() : SpellScriptLoader("spell_dk_anti_magic_shell_self") { }

        class spell_dk_anti_magic_shell_self_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_shell_self_AuraScript);

            uint32 absorbPct, hpPct;
            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                hpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_RUNIC_POWER_ENERGIZE))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                amount = GetCaster()->CountPctFromMaxHealth(hpPct);
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                absorbAmount = std::min(CalculatePct(dmgInfo.GetDamage(), absorbPct), GetTarget()->CountPctFromMaxHealth(hpPct));
            }

            void Trigger(AuraEffect* aurEff, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                // damage absorbed by Anti-Magic Shell energizes the DK with additional runic power.
                // This, if I'm not mistaken, shows that we get back ~20% of the absorbed damage as runic power.
                int32 bp = absorbAmount * 2 / 10;
                // Magic Suppression
                if (target)
                {
                    if (target->HasSpell(49224) || target->HasSpell(49610) || target->HasSpell(49611))
                        target->CastCustomSpell(target, SPELL_DK_RUNIC_POWER_ENERGIZE, &bp, NULL, NULL, true, NULL, aurEff);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_self_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self_AuraScript::Absorb, EFFECT_0);
                AfterEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self_AuraScript::Trigger, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_anti_magic_shell_self_AuraScript();
        }
};

// 50461 - Anti-Magic Zone
class spell_dk_anti_magic_zone : public SpellScriptLoader
{
public:
    spell_dk_anti_magic_zone() : SpellScriptLoader("spell_dk_anti_magic_zone")
    {
    }

    class spell_dk_anti_magic_zone_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_anti_magic_zone_AuraScript);

        uint32 absorbPct;

        bool Load()
        {
            absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
            return true;
        }

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DK_ANTI_MAGIC_SHELL_TALENT))
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 &amount, bool & /*canBeRecalculated*/)
        {
            if (Unit* unit = GetCaster())
            {
                SpellInfo const* talentSpell = sSpellMgr->GetSpellInfo(SPELL_DK_ANTI_MAGIC_SHELL_TALENT);
                amount = talentSpell->Effects[EFFECT_0].CalcValue(unit);

                if (Unit* owner = unit->GetCharmerOrOwner())
                {
                    if (Player* playerOwner = owner->ToPlayer())
                        amount += int32(2 * playerOwner->GetTotalAttackPowerValue(BASE_ATTACK));
                }
            }
        }

        void Absorb(AuraEffect* /*aurEff*/, DamageInfo &dmgInfo, uint32 & absorbAmount)
        {
            absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_zone_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_zone_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_anti_magic_zone_AuraScript();
    }
};

// 48721 - Blood Boil
class spell_dk_blood_boil : public SpellScriptLoader
{
    public:
        spell_dk_blood_boil() : SpellScriptLoader("spell_dk_blood_boil") { }

        class spell_dk_blood_boil_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_blood_boil_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_BOIL_TRIGGERED))
                    return false;
                return true;
            }

            bool Load()
            {
                _executed = false;
                return GetCaster()->GetTypeId() == TYPEID_PLAYER && GetCaster()->getClass() == CLASS_DEATH_KNIGHT;
            }

            void HandleAfterHit()
            {
                if (_executed || !GetHitUnit())
                    return;

                _executed = true;
                GetCaster()->CastSpell(GetCaster(), SPELL_DK_BLOOD_BOIL_TRIGGERED, true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_dk_blood_boil_SpellScript::HandleAfterHit);
            }

            bool _executed;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_blood_boil_SpellScript();
        }
};

// 50453 - Bloodworms Health Leech
class spell_dk_blood_gorged : public SpellScriptLoader
{
    public:
        spell_dk_blood_gorged() : SpellScriptLoader("spell_dk_blood_gorged") { }

        class spell_dk_blood_gorged_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_blood_gorged_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_GORGED_HEAL))
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

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                int32 bp = int32(eventInfo.GetDamageInfo()->GetDamage() * 1.5f);
                GetTarget()->CastCustomSpell(SPELL_DK_BLOOD_GORGED_HEAL, SPELLVALUE_BASE_POINT0, bp, _procTarget, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_dk_blood_gorged_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_dk_blood_gorged_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_blood_gorged_AuraScript();
        }
};

// 49158 - Corpse Explosion (51325, 51326, 51327, 51328)
class spell_dk_corpse_explosion : public SpellScriptLoader
{
    public:
        spell_dk_corpse_explosion() : SpellScriptLoader("spell_dk_corpse_explosion") { }

        class spell_dk_corpse_explosion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_corpse_explosion_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_CORPSE_EXPLOSION_TRIGGERED) || !sSpellMgr->GetSpellInfo(SPELL_DK_GHOUL_EXPLODE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_CORPSE_EXPLOSION_VISUAL))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    int32 bp = 0;
                    if (unitTarget->isAlive())  // Living ghoul as a target
                    {
                        bp = int32(unitTarget->CountPctFromMaxHealth(25));
                        unitTarget->CastCustomSpell(unitTarget, SPELL_DK_GHOUL_EXPLODE, &bp, NULL, NULL, false);
                    }
                    else                        // Some corpse
                    {
                        bp = GetEffectValue();
                        GetCaster()->CastCustomSpell(unitTarget, GetSpellInfo()->Effects[EFFECT_1].CalcValue(), &bp, NULL, NULL, true);
                        // Corpse Explosion (Suicide)
                        unitTarget->CastSpell(unitTarget, SPELL_DK_CORPSE_EXPLOSION_TRIGGERED, true);
                    }
                    // Set corpse look
                    GetCaster()->CastSpell(unitTarget, SPELL_DK_CORPSE_EXPLOSION_VISUAL, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_corpse_explosion_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_corpse_explosion_SpellScript();
        }
};

// -47541, 52375, 59134, -62900 - Death Coil
class spell_dk_death_coil : public SpellScriptLoader
{
    public:
        spell_dk_death_coil() : SpellScriptLoader("spell_dk_death_coil") { }

        class spell_dk_death_coil_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_coil_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_COIL_DAMAGE) || !sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_COIL_HEAL))
                    return false;
                return true;
            }

            enum Spells
            {
                DK_SPELL_DARK_TRANSFORMATION_TRIGGERED  = 93426,
                DK_SPELL_DARK_INFUSION                  = 91342,
                DK_TALENT_SHADOW_INFUSION               = 48965,
                DK_SPELL_DARK_INFUSION_BUFF             = 63560
            };

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (caster->IsFriendlyTo(target))
                    {
                        int32 bp = int32(damage * 1.5f);
                        caster->CastCustomSpell(target, SPELL_DK_DEATH_COIL_HEAL, &bp, NULL, NULL, true);
                    }
                    else
                    {
                        if (AuraEffect const* auraEffect = caster->GetAuraEffect(SPELL_DK_ITEM_SIGIL_VENGEFUL_HEART, EFFECT_1))
                            damage += auraEffect->GetBaseAmount();

                        if (caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            // Mastery: Dreadblade
                            float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                            if (caster->HasAura(77515))
                                damage += damage * (0.200f + (0.0250f * masteryPoints));
                        }

                        caster->CastCustomSpell(target, SPELL_DK_DEATH_COIL_DAMAGE, &damage, NULL, NULL, true);
                    }
                    // Shadow Infusion (Already transformed ghoul can't gain other infusions)
                    if (caster->GetGuardianPet() && !caster->GetGuardianPet()->HasAura(DK_SPELL_DARK_INFUSION_BUFF))
                    {
                        if (caster->HasAura(48965) && roll_chance_f(33)) // Shadow Infusion r1
                            caster->CastSpell(caster, DK_SPELL_DARK_INFUSION, true);
                        if (caster->HasAura(49571) && roll_chance_f(66)) // Shadow Infusion r2
                            caster->CastSpell(caster, DK_SPELL_DARK_INFUSION, true);
                        if (caster->HasAura(49572))                     // Shadow Infusion r3
                            caster->CastSpell(caster, DK_SPELL_DARK_INFUSION, true);
                    }
                    // Dark Transformation
                    if (caster->HasSpell(63560))
                    {
                        if(Unit* pet = caster->GetGuardianPet())
                        {
                            if (Aura const* darkInfusion = pet->GetAura(DK_SPELL_DARK_INFUSION, caster->GetGUID()))
                            {
                                if (darkInfusion->GetStackAmount() >= 5)
                                    caster->CastSpell(caster, DK_SPELL_DARK_TRANSFORMATION_TRIGGERED, true);
                            }
                        }
                    }
                }
            }

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetExplTargetUnit())
                {
                    if (!caster->IsFriendlyTo(target) && !caster->isInFront(target))
                        return SPELL_FAILED_UNIT_NOT_INFRONT;

                    if (target->IsFriendlyTo(caster) && target->GetCreatureType() != CREATURE_TYPE_UNDEAD)
                        return SPELL_FAILED_BAD_TARGETS;
                }
                else
                    return SPELL_FAILED_BAD_TARGETS;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_coil_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_coil_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_death_coil_SpellScript();
        }
};

// 52751 - Death Gate
class spell_dk_death_gate : public SpellScriptLoader
{
    public:
        spell_dk_death_gate() : SpellScriptLoader("spell_dk_death_gate") {}

        class spell_dk_death_gate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_gate_SpellScript);

            SpellCastResult CheckClass()
            {
                if (GetCaster()->getClass() != CLASS_DEATH_KNIGHT)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, GetEffectValue(), false);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_gate_SpellScript::CheckClass);
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_gate_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_death_gate_SpellScript();
        }
};

// 49560 - Death Grip
class spell_dk_death_grip : public SpellScriptLoader
{
    public:
        spell_dk_death_grip() : SpellScriptLoader("spell_dk_death_grip") { }

        class spell_dk_death_grip_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_grip_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Position const* pos = GetExplTargetDest();
                if (Unit* target = GetHitUnit())
                {
                    if (!target->HasAuraType(SPELL_AURA_DEFLECT_SPELLS)) // Deterrence
                        target->CastSpell(pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), damage, true);
                }
            }

            void HandleOnCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (SpellMissInfo missInfo = caster->SpellHitResult(GetExplTargetUnit(), GetSpellInfo(), false))
                        {
                            if (missInfo == SPELL_MISS_IMMUNE)
                            {
                                // Glyph of Resilient Grip
                                if (caster->HasAura(SPELL_DK_GLYPH_OF_RESILIENT_GRIP))
                                    caster->ToPlayer()->RemoveSpellCooldown(SPELL_DK_DEATH_GRIP, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_grip_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCast += SpellCastFn(spell_dk_death_grip_SpellScript::HandleOnCast);
            }

        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_death_grip_SpellScript();
        }
};

// 48743 - Death Pact
class spell_dk_death_pact : public SpellScriptLoader
{
    public:
        spell_dk_death_pact() : SpellScriptLoader("spell_dk_death_pact") { }

        class spell_dk_death_pact_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_pact_SpellScript);

            SpellCastResult CheckCast()
            {
                // Check if we have valid targets, otherwise skip spell casting here
                if (Player* player = GetCaster()->ToPlayer())
                    for (Unit::ControlList::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                        if (Creature* undeadPet = (*itr)->ToCreature())
                            if (undeadPet->isAlive() &&
                                undeadPet->GetOwnerGUID() == player->GetGUID() &&
                                undeadPet->GetCreatureType() == CREATURE_TYPE_UNDEAD &&
                                undeadPet->IsWithinDist(player, 100.0f, false))
                                return SPELL_CAST_OK;

                return SPELL_FAILED_NO_PET;
            }

            void FilterTargets(std::list<WorldObject*>& targetList)
            {
                Unit* target = NULL;
                for (std::list<WorldObject*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    if (Unit* unit = (*itr)->ToUnit())
                        if (unit->GetOwnerGUID() == GetCaster()->GetGUID() && unit->GetCreatureType() == CREATURE_TYPE_UNDEAD)
                        {
                            target = unit;
                            break;
                        }
                }

                targetList.clear();
                if (target)
                    targetList.push_back(target);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_pact_SpellScript::CheckCast);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_death_pact_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_death_pact_SpellScript();
        }
};

// -49998 - Death Strike
class spell_dk_death_strike : public SpellScriptLoader
{
    public:
        spell_dk_death_strike() : SpellScriptLoader("spell_dk_death_strike") { }

        class spell_dk_death_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_strike_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_STRIKE_HEAL))
                    return false;
                return true;
            }

            void HandleDummy()
            {
                int32 damageTaken = 0;
                int32 heal = 0;
                if (Unit* caster = GetCaster())
                {
                    int32 maxHealth = caster->GetMaxHealth();
                    damageTaken = caster->GetDamageTakenInPastSecs(5) * 0.20f;
                    heal += damageTaken;

                    // Dark Succor
                    if (AuraEffect const * aurEff = caster->GetAuraEffect(SPELL_DK_DARK_SUCCOR, EFFECT_0))
                    {
                        // Only in Frost Presence or Unholy Presence
                        if (caster->HasAura(48266) || caster->HasAura(48265))
                            ApplyPct(maxHealth, aurEff->GetAmount());
                    }
                    // Default value
                    else
                        ApplyPct(maxHealth, GetSpellInfo()->Effects[EFFECT_2].BasePoints);

                    // Threat of tassarian, we have two weapons and we need correct heal
                    if (caster->haveOffhandWeapon())
                        heal = heal / 2;

                    heal += maxHealth;

                    // Mastery: Blood Shield
                    if (caster->HasAura(SPELL_DK_BLOODSHIELD) && caster->HasAura(SPELL_DK_BLOOD_PRESENCE))
                    {
                        float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        int32 shield = heal * (0.5f + (0.0625f * masteryPoints));
                        // Increase amount if buff is already present
                        if(AuraEffect* aurEff = caster->GetAuraEffect(SPELL_DK_BLOODSHIELD_ABSORB, 0))
                            shield += aurEff->GetAmount();
                        caster->CastCustomSpell(caster, SPELL_DK_BLOODSHIELD_ABSORB, &shield, NULL, NULL, false);
                    }

                    // Improved Death Strike
                    if (AuraEffect const * aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 2751, 2))
                        AddPct(heal, aurEff->GetAmount());

                    caster->CastCustomSpell(caster, SPELL_DK_DEATH_STRIKE_HEAL, &heal, NULL, NULL, true);
                    // Only in Frost Presence or Unholy Presence
                    if (caster->HasAura(48266) || caster->HasAura(48265))
                        caster->RemoveAurasDueToSpell(SPELL_DK_DARK_SUCCOR);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dk_death_strike_SpellScript::HandleDummy);
            }

        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_death_strike_SpellScript();
        }
};

// 47496 - Explode, Ghoul spell for Corpse Explosion
class spell_dk_ghoul_explode : public SpellScriptLoader
{
    public:
        spell_dk_ghoul_explode() : SpellScriptLoader("spell_dk_ghoul_explode") { }

        class spell_dk_ghoul_explode_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_ghoul_explode_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_CORPSE_EXPLOSION_TRIGGERED))
                    return false;
                return true;
            }

            void Suicide(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    // Corpse Explosion (Suicide)
                    unitTarget->CastSpell(unitTarget, SPELL_DK_CORPSE_EXPLOSION_TRIGGERED, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_ghoul_explode_SpellScript::Suicide, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_ghoul_explode_SpellScript();
        }
};

class spell_dk_howling_blast : public SpellScriptLoader
{
    public:
        spell_dk_howling_blast() : SpellScriptLoader("spell_dk_howling_blast") { }

        class spell_dk_howling_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_howling_blast_SpellScript);

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
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_dk_howling_blast_SpellScript::HandleBeforeCast);
                OnHit += SpellHitFn(spell_dk_howling_blast_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_howling_blast_SpellScript();
        }
};

// 48792 - Icebound Fortitude
class spell_dk_icebound_fortitude : public SpellScriptLoader
{
    public:
        spell_dk_icebound_fortitude() : SpellScriptLoader("spell_dk_icebound_fortitude") { }

        class spell_dk_icebound_fortitude_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_icebound_fortitude_AuraScript);

            bool Load()
            {
                Unit* caster = GetCaster();
                return caster && caster->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 value = amount;
                    uint32 defValue = uint32(caster->ToPlayer()->GetSkillValue(SKILL_DEFENSE) + caster->ToPlayer()->GetRatingBonusValue(CR_DEFENSE_SKILL));

                    if (defValue > 400)
                        value -= int32((defValue - 400) * 0.15);

                    // Glyph of Icebound Fortitude
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_DK_GLYPH_OF_ICEBOUND_FORTITUDE, EFFECT_0))
                    {
                        int32 valMax = -aurEff->GetAmount();
                        if (value > valMax)
                            value = valMax;
                    }
                    amount = value;
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_icebound_fortitude_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_icebound_fortitude_AuraScript();
        }
};

class spell_dk_runic_empowerment : public SpellScriptLoader
{
    public:
        spell_dk_runic_empowerment() : SpellScriptLoader("spell_dk_runic_empowerment") { }

        class spell_dk_runic_empowerment_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_runic_empowerment_AuraScript);

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                switch (eventInfo.GetDamageInfo()->GetSpellInfo()->Id)
                {
                    case SPELL_DK_FROST_STRIKE:
                    case SPELL_DK_DEATH_COIL_DAMAGE:
                    case SPELL_DK_RUNE_STRIKE:
                    {
                        if (Player* owner = GetOwner()->ToPlayer())
                        {
                            // Runic Corruption
                            if (AuraEffect* aurEff = owner->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 4068, EFFECT_0))
                            {
                                int32 bp0 = aurEff->GetAmount();
                                owner->CastCustomSpell(owner, 51460, &bp0, NULL, NULL, true, NULL, NULL, owner->GetGUID());
                                return;
                            }

                            if (roll_chance_i(45))
                            {
                                uint32 cooldownrunes[MAX_RUNES];
                                uint8 runescount = 0;
                                for (uint32 i = 0; i < MAX_RUNES; ++i)
                                {
                                    if (owner->GetRuneCooldown(i))
                                    {
                                        cooldownrunes[runescount] = i;
                                        runescount++;
                                    }
                                }
                                if (runescount > 0)
                                {
                                    uint8 rndrune = urand(0, runescount - 1);
                                    owner->SetRuneCooldown(cooldownrunes[rndrune], 0);
                                    owner->AddRunePower(cooldownrunes[rndrune]);
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_dk_runic_empowerment_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_runic_empowerment_AuraScript();
        }
};

// 55090 - Scourge Strike (55265, 55270, 55271)
class spell_dk_scourge_strike : public SpellScriptLoader
{
    public:
        spell_dk_scourge_strike() : SpellScriptLoader("spell_dk_scourge_strike") { }

        enum spellId
        {
            SPELL_EFFECT_EBON_PLAGUE    = 65142
        };

        class spell_dk_scourge_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_scourge_strike_SpellScript);
            float multiplier;

            bool Load()
            {
                multiplier = 1.0f;
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_SCOURGE_STRIKE_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (Unit* unitTarget = GetHitUnit())
                {
                    multiplier = (GetEffectValue() * unitTarget->GetDiseasesByCaster(caster->GetGUID()) / 100.f);
                    // Death Knight T8 Melee 4P Bonus
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_DK_ITEM_T8_MELEE_4P_BONUS, EFFECT_0))
                        AddPct(multiplier, aurEff->GetAmount());
                }
            }

            void HandleAfterHit()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (Unit* unitTarget = GetHitUnit())
                {
                    int32 bp = GetHitDamage() * multiplier;

                    if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_DK_BLACK_ICE_R1, EFFECT_0))
                        AddPct(bp, aurEff->GetAmount());

                    // Ebon Plague should be also considered as disease
                    if (unitTarget->HasAura(SPELL_EFFECT_EBON_PLAGUE, caster->GetGUID()))
                        AddPct(multiplier, 18);

                    caster->CastCustomSpell(unitTarget, SPELL_DK_SCOURGE_STRIKE_TRIGGERED, &bp, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_scourge_strike_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
                AfterHit += SpellHitFn(spell_dk_scourge_strike_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_scourge_strike_SpellScript();
        }
};

// 49145 - Spell Deflection
class spell_dk_spell_deflection : public SpellScriptLoader
{
    public:
        spell_dk_spell_deflection() : SpellScriptLoader("spell_dk_spell_deflection") { }

        class spell_dk_spell_deflection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_spell_deflection_AuraScript);

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
                // You have a chance equal to your Parry chance
                if ((dmgInfo.GetDamageType() == SPELL_DIRECT_DAMAGE) && roll_chance_f(GetTarget()->GetUnitParryChance()))
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_spell_deflection_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_spell_deflection_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_spell_deflection_AuraScript();
        }
};

// 55233 - Vampiric Blood
class spell_dk_vampiric_blood : public SpellScriptLoader
{
    public:
        spell_dk_vampiric_blood() : SpellScriptLoader("spell_dk_vampiric_blood") { }

        class spell_dk_vampiric_blood_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_vampiric_blood_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = GetUnitOwner()->CountPctFromMaxHealth(amount);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_vampiric_blood_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_HEALTH);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_vampiric_blood_AuraScript();
        }
};

class spell_dk_dark_transformation: public SpellScriptLoader
{
public:
    spell_dk_dark_transformation () : SpellScriptLoader("spell_dk_dark_transformation") {}

    class spell_dk_dark_transformation_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_dk_dark_transformation_SpellScript);

        enum Spells
        {
            DK_SPELL_DARK_TRANSFORMATION = 63560,
            DK_SPELL_DARK_TRANSFORMATION_TRIGGERED = 93426,
            DK_SPELL_DARK_INFUSION = 91342
        };

        bool Validate(SpellInfo const* spellInfo)
        {
            if (!sSpellMgr->GetSpellInfo(DK_SPELL_DARK_TRANSFORMATION))
                return false;
            if (!sSpellMgr->GetSpellInfo(DK_SPELL_DARK_TRANSFORMATION_TRIGGERED))
                return false;
            if (!sSpellMgr->GetSpellInfo(DK_SPELL_DARK_INFUSION))
                return false;

            return true;
        }

        void HandleBeforeHit()
        {
            Unit* caster = GetCaster();
            Unit* pet = caster->GetGuardianPet();

            if (!caster && !pet)
                return;

            // Dark Transformation
            if (!caster->HasSpell(63560))
                return;

            caster->RemoveAura(DK_SPELL_DARK_TRANSFORMATION_TRIGGERED);
            pet->RemoveAura(DK_SPELL_DARK_INFUSION);
            pet->CastSpell(caster, 70895, true);
            caster->CastSpell(pet, 70895, true);
        }

        void Register()
        {
            BeforeHit += SpellHitFn(spell_dk_dark_transformation_SpellScript::HandleBeforeHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_dark_transformation_SpellScript();
    }
};

class spell_dk_raise_dead : public SpellScriptLoader
{
    public:
        spell_dk_raise_dead() : SpellScriptLoader("spell_dk_raise_dead") { }

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_raise_dead_SpellScript();
        }

        class spell_dk_raise_dead_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_raise_dead_SpellScript);

            void TriggerSummon()
            {
                Unit* caster = GetCaster();

                if (!caster)
                    return;

                SpellEffIndex indx = caster->HasAura(52143) ? EFFECT_1 : EFFECT_0;

                uint32 spellId = GetSpellInfo()->Effects[indx].BasePoints;

                caster->CastSpell(caster, spellId);
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_dk_raise_dead_SpellScript::TriggerSummon);
            }
        };
};

// 55095 - Frost Fever
class spell_dk_frost_fever : public SpellScriptLoader
{
    public:
        spell_dk_frost_fever() : SpellScriptLoader("spell_dk_frost_fever") { }

        class spell_dk_frost_fever_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_frost_fever_AuraScript);

            void HandleDispel(DispelInfo* /*dispelInfo*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (!caster)
                        return;

                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 cooldownrunes[MAX_RUNES];
                    uint8 runescount = 0;
                    for (uint32 j = 0; j < MAX_RUNES; ++j)
                    {
                        if (caster->ToPlayer()->GetRuneCooldown(j))
                        {
                            if (caster->ToPlayer()->GetBaseRune(j) != RUNE_FROST)
                                continue;
                            cooldownrunes[runescount] = j;
                            runescount++;
                        }
                    }
                    // Resilient Infection
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 1910, 0))
                    {
                        int32 chance = aurEff->GetAmount();
                        if (roll_chance_i(chance))
                        {
                            if (runescount > 0)
                            {
                                uint8 checkRune = urand(0, runescount-1);
                                caster->ToPlayer()->SetRuneCooldown(cooldownrunes[checkRune], 0);
                                caster->ToPlayer()->AddRunePower(cooldownrunes[checkRune]);
                            }
                            caster->CastSpell(caster, 90721, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_dk_frost_fever_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_frost_fever_AuraScript();
        }
};

// 55078 - Blood Plague
class spell_dk_blood_plague : public SpellScriptLoader
{
    public:
        spell_dk_blood_plague() : SpellScriptLoader("spell_dk_blood_plague") { }

        class spell_dk_blood_plague_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_blood_plague_AuraScript);

            void HandleDispel(DispelInfo* /*dispelInfo*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (!caster)
                        return;

                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 cooldownrunes[MAX_RUNES];
                    uint8 runescount = 0;
                    for (uint32 j = 0; j < MAX_RUNES; ++j)
                    {
                        if (caster->ToPlayer()->GetRuneCooldown(j))
                        {
                            if (caster->ToPlayer()->GetBaseRune(j) != RUNE_UNHOLY)
                                continue;
                            cooldownrunes[runescount] = j;
                            runescount++;
                        }
                    }
                    // Resilient Infection
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 1910, 0))
                    {
                        int32 chance = aurEff->GetAmount();
                        if (roll_chance_i(chance))
                        {
                            if (runescount > 0)
                            {
                                uint8 checkRune = urand(0, runescount-1);
                                caster->ToPlayer()->SetRuneCooldown(cooldownrunes[checkRune], 0);
                                caster->ToPlayer()->AddRunePower(cooldownrunes[checkRune]);
                            }
                            caster->CastSpell(caster, 90721, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_dk_blood_plague_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_blood_plague_AuraScript();
        }
};

// 51271 - Pillar of Frost
class spell_dk_pillar_of_frost : public SpellScriptLoader
{
public:
    spell_dk_pillar_of_frost() : SpellScriptLoader("spell_dk_pillar_of_frost") { }

        class spell_dk_pillar_of_frost_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_pillar_of_frost_AuraScript);

            enum Spells
            {
                DK_SPELL_GLYPH_OF_PILLAR_OF_FROST           = 58635,
                DK_SPELL_GLYPH_OF_PILLAR_OF_FROST_TRIGGERED = 90259
            };

            void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Glyph of Pillar of Frost
                    if (!caster->HasAura(DK_SPELL_GLYPH_OF_PILLAR_OF_FROST))
                        return;

                    if (!caster->HasAura(DK_SPELL_GLYPH_OF_PILLAR_OF_FROST_TRIGGERED))
                        caster->CastSpell(caster, DK_SPELL_GLYPH_OF_PILLAR_OF_FROST_TRIGGERED, false);
                }
            }

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Glyph of Pillar of Frost
                    if (caster->HasAura(DK_SPELL_GLYPH_OF_PILLAR_OF_FROST_TRIGGERED))
                        caster->RemoveAurasDueToSpell(DK_SPELL_GLYPH_OF_PILLAR_OF_FROST_TRIGGERED);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_dk_pillar_of_frost_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dk_pillar_of_frost_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_pillar_of_frost_AuraScript();
        }
};

// 47476 - Strangulate
class spell_dk_strangulate : public SpellScriptLoader
{
    public:
        spell_dk_strangulate() : SpellScriptLoader("spell_dk_strangulate") { }

        class spell_dk_strangulate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_strangulate_SpellScript);

            enum Spells
            {
                SPELL_DK_STRANGULATE            = 47476,
                SPELL_DK_GLYPH_OF_STRANGULATE   = 58618
            };

            void HandleBeforeHit()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->HasUnitState(UNIT_STATE_CASTING))
                        isCasting = true;
                    else
                        isCasting = false;
                }
            }

            void HandleAfterHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Glyph of Strangulate
                        if (Aura* aur = target->GetAura(SPELL_DK_STRANGULATE))
                        {
                            if (isCasting && caster->HasAura(SPELL_DK_GLYPH_OF_STRANGULATE))
                            {
                                aur->SetDuration(aur->GetDuration() + 2*IN_MILLISECONDS);
                                isCasting = false;
                            }
                        }
                    }
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_dk_strangulate_SpellScript::HandleBeforeHit);
                AfterHit += SpellHitFn(spell_dk_strangulate_SpellScript::HandleAfterHit);
            }

        private:
            bool isCasting;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_strangulate_SpellScript();
        }
};

uint32 necroticAmount = 0;

// 73975 - Necrotic Strike
class spell_dk_necrotic_strike : public SpellScriptLoader
{
    public:
        spell_dk_necrotic_strike() : SpellScriptLoader("spell_dk_necrotic_strike") { }

        enum spellId
        {
            SPELL_EFFECT_NECROTIC_STRIKE    = 73975
        };

        class spell_dk_necrotic_strike_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_necrotic_strike_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                    amount = int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.7f) + necroticAmount;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_necrotic_strike_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB);
            }
        };

        class spell_dk_necrotic_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_necrotic_strike_SpellScript);

            enum spellId
            {
                SPELL_DK_TALENT_DESECRATION_R1  = 55666,
                SPELL_DK_TALENT_DESECRATION_R2  = 55667,
                SPELL_DK_DESECRATION_TRIGGER_R1 = 55741,
                SPELL_DK_DESECRATION_TRIGGER_R2 = 68766
            };

            void HandleBeforeHit()
            {
                Unit* caster = GetCaster();
                Unit* target = GetExplTargetUnit();

                if (caster && target)
                {
                    if (AuraEffect* aurEff = target->GetAuraEffect(SPELL_EFFECT_NECROTIC_STRIKE, EFFECT_0, caster->GetGUID()))
                        necroticAmount = aurEff->GetAmount();
                    else
                        necroticAmount = 0;
                }
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (caster->HasAura(SPELL_DK_TALENT_DESECRATION_R1))
                            caster->CastSpell(target, SPELL_DK_DESECRATION_TRIGGER_R1);
                        if (caster->HasAura(SPELL_DK_TALENT_DESECRATION_R2))
                            caster->CastSpell(target, SPELL_DK_DESECRATION_TRIGGER_R2);
                    }
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_dk_necrotic_strike_SpellScript::HandleBeforeHit);
                OnEffectHitTarget += SpellEffectFn(spell_dk_necrotic_strike_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_necrotic_strike_AuraScript();
        }

        SpellScript* GetSpellScript() const
        {
            return new spell_dk_necrotic_strike_SpellScript();
        }
};

// Gnaw
class spell_dk_gnaw : public SpellScriptLoader
{
public:
    spell_dk_gnaw() : SpellScriptLoader("spell_dk_gnaw") { }

    class spell_dk_gnaw_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_gnaw_SpellScript)

        void HandleEffect(SpellEffIndex /*eff*/)
        {
            if (!GetHitUnit())
                return;

            if (Unit *caster = GetCaster())
            {
                if(caster->isPet())
                {
                    if (caster->HasAura(63560))
                        caster->CastSpell(GetHitUnit(), 91797, true);
                    else
                        caster->CastSpell(GetHitUnit(), 91800, true);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_gnaw_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_gnaw_SpellScript();
    }
};

// Claw
class spell_dk_claw : public SpellScriptLoader
{
public:
    spell_dk_claw() : SpellScriptLoader("spell_dk_claw") { }

    class spell_dk_claw_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_claw_SpellScript)

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (Unit *caster = GetCaster())
            {
                if (caster->HasAura(63560))
                    caster->CastSpell(GetHitUnit(), 91778, true);
                else
                    caster->CastSpell(GetHitUnit(), 91776, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_claw_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_claw_SpellScript();
    }
};

// 47482  leap
class spell_dk_leap : public SpellScriptLoader
{
public:
    spell_dk_leap() : SpellScriptLoader("spell_dk_leap") { }

    class spell_dk_leap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_leap_SpellScript)

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (Unit *caster = GetCaster())
            {
                if (caster->HasAura(63560))
                    caster->CastSpell(GetHitUnit(), 91802, true);
                else
                    caster->CastSpell(GetHitUnit(), 91809, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_leap_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_leap_SpellScript();
    }
};

// 47482  Huddle
class spell_dk_huddle : public SpellScriptLoader
{
public:
    spell_dk_huddle() : SpellScriptLoader("spell_dk_huddle") { }

    class spell_dk_huddle_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_huddle_SpellScript)

        void HandleEffect(SpellEffIndex /*eff*/)
        {
            if (!GetHitUnit())
                return;

            if (Unit *caster = GetCaster())
            {
                if(caster->isPet())
                {
                    if (caster->HasAura(63560))
                        caster->CastSpell(GetHitUnit(), 91837, true);
                    else
                        caster->CastSpell(GetHitUnit(), 91838, true);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_huddle_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_huddle_SpellScript();
    }
};

class spell_dk_hungering_cold : public SpellScriptLoader
{
public:
    spell_dk_hungering_cold() : SpellScriptLoader("spell_dk_hungering_cold") { }

    class spell_dk_hungering_cold_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_hungering_cold_SpellScript)

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (Unit *caster = GetCaster())
            {
                int32 damage = (((caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.055f) * 3.30) + caster->getLevel()) * 0.32; // BasePoints = 0 + Level * 0,32
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    // Mastery: Frozen Heart
                    float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                    if (caster->HasAura(77514))
                        damage += damage * (0.160f + (0.020f * masteryPoints));
                }
                // Virulence
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_PCT_MODIFIER, SPELLFAMILY_DEATHKNIGHT, 208, 0))
                    damage += (damage * aurEff->GetAmount()) / 100;

                caster->CastCustomSpell(GetHitUnit(), 55095, NULL, NULL, &damage, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_hungering_cold_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_hungering_cold_SpellScript();
    }
};

class spell_dk_starting_runes : public SpellScriptLoader
{
public:
    spell_dk_starting_runes() : SpellScriptLoader("spell_dk_starting_runes") { }

    enum questId
    {
        QUEST_RUNEFORGING_PREPARATION_FOR_BATTLE    = 12842
    };

    class spell_dk_starting_runes_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_starting_runes_SpellScript)

        void HandleQuestCredit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                    caster->ToPlayer()->CompleteQuest(QUEST_RUNEFORGING_PREPARATION_FOR_BATTLE);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_starting_runes_SpellScript::HandleQuestCredit, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_starting_runes_SpellScript();
    }
};

class spell_dk_blood_presence : public SpellScriptLoader
{
public:
    spell_dk_blood_presence() : SpellScriptLoader("spell_dk_blood_presence")
    {
    }

    enum spellId
    {
        SPELL_IMPROVED_BLOOD_PRESENCE_TRIGGERED = 63611
    };

    class spell_dk_blood_presence_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_blood_presence_SpellScript)

        void HandleImproved()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    // Improved Blood Presence
                    if (AuraEffect* ibp = caster->GetAuraEffectOfRankedSpell(50365, EFFECT_2, caster->GetGUID()))
                        caster->CastSpell(caster, SPELL_IMPROVED_BLOOD_PRESENCE_TRIGGERED, true);
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_dk_blood_presence_SpellScript::HandleImproved);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_blood_presence_SpellScript();
    }
};

void AddSC_deathknight_spell_scripts()
{
    new spell_dk_anti_magic_shell_raid();
    new spell_dk_anti_magic_shell_self();
    new spell_dk_anti_magic_zone();
    new spell_dk_blood_boil();
    new spell_dk_blood_gorged();
    new spell_dk_corpse_explosion();
    new spell_dk_death_coil();
    new spell_dk_death_gate();
    new spell_dk_death_grip();
    new spell_dk_death_pact();
    new spell_dk_death_strike();
    new spell_dk_ghoul_explode();
    new spell_dk_howling_blast();
    new spell_dk_icebound_fortitude();
    new spell_dk_runic_empowerment();
    new spell_dk_scourge_strike();
    new spell_dk_spell_deflection();
    new spell_dk_vampiric_blood();
    new spell_dk_dark_transformation();
    new spell_dk_raise_dead();
    new spell_dk_frost_fever();
    new spell_dk_blood_plague();
    new spell_dk_pillar_of_frost();
    new spell_dk_strangulate();
    new spell_dk_necrotic_strike();
    new spell_dk_gnaw();
    new spell_dk_claw();
    new spell_dk_leap();
    new spell_dk_huddle();
    new spell_dk_hungering_cold();
    new spell_dk_starting_runes();
    new spell_dk_blood_presence();
}
