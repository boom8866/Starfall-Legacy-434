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
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Pet.h"

enum MageSpells
{
    SPELL_MAGE_BURNOUT                           = 29077,
    SPELL_MAGE_CAUTERIZE_DAMAGE                  = 87023,
    SPELL_MAGE_COLD_SNAP                         = 11958,
    SPELL_MAGE_FOCUS_MAGIC_PROC                  = 54648,
    SPELL_MAGE_FROST_WARDING_R1                  = 11189,
    SPELL_MAGE_FROST_WARDING_TRIGGERED           = 57776,
    SPELL_MAGE_INCANTERS_ABSORBTION_KNOCKBACK    = 86261,
    SPELL_MAGE_INCANTERS_ABSORBTION_R1           = 44394,
    SPELL_MAGE_INCANTERS_ABSORBTION_R2           = 44395,
    SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED    = 44413,
    SPELL_MAGE_IGNITE                            = 12654,
    SPELL_MAGE_MASTER_OF_ELEMENTS_ENERGIZE       = 29077,
    SPELL_MAGE_SQUIRREL_FORM                     = 32813,
    SPELL_MAGE_GIRAFFE_FORM                      = 32816,
    SPELL_MAGE_SERPENT_FORM                      = 32817,
    SPELL_MAGE_DRAGONHAWK_FORM                   = 32818,
    SPELL_MAGE_WORGEN_FORM                       = 32819,
    SPELL_MAGE_SHEEP_FORM                        = 32820,
    SPELL_MAGE_GLYPH_OF_ETERNAL_WATER            = 70937,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT  = 70908,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY  = 70907,
    SPELL_MAGE_GLYPH_OF_BLAST_WAVE               = 62126,

    SPELL_MAGE_FLAMESTRIKE                       = 2120,

    SPELL_MAGE_CHILLED_R1                        = 12484,
    SPELL_MAGE_CHILLED_R2                        = 12485,

    SPELL_MAGE_SHATTERED_BARRIER_R1              = 44745,
    SPELL_MAGE_SHATTERED_BARRIER_R2              = 54787,
    SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R1       = 55080,
    SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R2       = 83073,

    SPELL_MAGE_IMPROVED_MANA_GEM_TRIGGERED       = 83098,

    SPELL_MAGE_FINGERS_OF_FROST                  = 44544,

    SPELL_MAGE_GLYPH_OF_MIRROR_IMAGE             = 63093,
    SPELL_MAGE_SUMMON_IMAGES_FROST               = 58832,
    SPELL_MAGE_SUMMON_IMAGES_FIRE                = 88092,
    SPELL_MAGE_SUMMON_IMAGES_ARCANE              = 88091,

    SPELL_MAGE_SLOW                              = 31589,
    SPELL_MAGE_NETHERVORTEX_R1                   = 86181,
    SPELL_MAGE_NETHERVORTEX_TRIGGERED            = 86262,

    SPELL_MAGE_MIRROR_IMAGE_TRIGGERED            = 58832,

    SPELL_MAGE_RITUAL_OF_REFRESHMENT_R1          = 74650,
    SPELL_MAGE_RITUAL_OF_REFRESHMENT_R2          = 92824,
    SPELL_MAGE_RITUAL_OF_REFRESHMENT_R3          = 92827,

    SPELL_MAGE_EARLY_FROST_R1                    = 83049,
    SPELL_MAGE_EARLY_FROST_R2                    = 83050,
    SPELL_MAGE_REM_EARLY_FROST_R1                = 83162,
    SPELL_MAGE_REM_EARLY_FROST_R2                = 83239,
    SPELL_MAGE_INVISIBILITY_FADING               = 66,
    SPELL_MAGE_INVISIBILITY_INVISIBLE            = 32612,
    SPELL_MAGE_MOLTEN_SHIELDS                    = 11094,
    SPELL_MAGE_BLAZING_SPEED_R1                  = 31641,
    SPELL_MAGE_BLAZING_SPEED_R2                  = 31642,
    SPELL_MAGE_BLAZING_SPEED_TRIGGERED           = 31643
};

enum MageIcons
{
    ICON_MAGE_SHATTER                            = 976,
    ICON_MAGE_IMPROVED_FLAMESTRIKE               = 37,
    ICON_MAGE_IMPROVED_FREEZE                    = 94,
    ICON_MAGE_INCANTER_S_ABSORPTION              = 2941,
    ICON_MAGE_IMPROVED_MANA_GEM                  = 1036
};

// Incanter's Absorbtion
class spell_mage_incanters_absorbtion_base_AuraScript : public AuraScript
{
    public:
        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION_R1))
                return false;
            return true;
        }

        void Trigger(AuraEffect* aurEff, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
        {
            Unit* target = GetTarget();

            if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_INCANTERS_ABSORBTION_R1, EFFECT_0))
            {
                int32 bp = CalculatePct(absorbAmount, talentAurEff->GetAmount());
                target->CastCustomSpell(target, SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
            }
        }
};

// 11113 - Blast Wave
class spell_mage_blast_wave : public SpellScriptLoader
{
    public:
        spell_mage_blast_wave() : SpellScriptLoader("spell_mage_blast_wave") { }

        class spell_mage_blast_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_blast_wave_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FLAMESTRIKE))
                    return false;
                return true;
            }

            void CountTargets(std::list<WorldObject*>& targetList)
            {
                _targetCount = targetList.size();
            }

            void HandleImprovedFlamestrike()
            {
                if (_targetCount >= 2)
                    if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_IMPROVED_FLAMESTRIKE, EFFECT_0))
                        if (roll_chance_i(aurEff->GetAmount()))
                        {
                            float x, y, z;
                            WorldLocation const* loc = GetExplTargetDest();
                            if (!loc)
                                return;

                            loc->GetPosition(x, y, z);
                            GetCaster()->CastSpell(x, y, z, SPELL_MAGE_FLAMESTRIKE, true);
                        }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_blast_wave_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                AfterCast += SpellCastFn(spell_mage_blast_wave_SpellScript::HandleImprovedFlamestrike);
            }

        private:
            uint32 _targetCount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_blast_wave_SpellScript();
        }
};

// -44449 - Burnout
class spell_mage_burnout : public SpellScriptLoader
{
    public:
        spell_mage_burnout() : SpellScriptLoader("spell_mage_burnout") { }

        class spell_mage_burnout_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_burnout_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_BURNOUT))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return eventInfo.GetDamageInfo()->GetSpellInfo(); // eventInfo.GetSpellInfo()
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                int32 mana = int32(eventInfo.GetDamageInfo()->GetSpellInfo()->CalcPowerCost(GetTarget(), eventInfo.GetDamageInfo()->GetSchoolMask()));
                mana = CalculatePct(mana, aurEff->GetAmount());

                GetTarget()->CastCustomSpell(SPELL_MAGE_BURNOUT, SPELLVALUE_BASE_POINT0, mana, GetTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_mage_burnout_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_mage_burnout_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_burnout_AuraScript();
        }
};

// 42208 - Blizzard
/// Updated 4.3.4
class spell_mage_blizzard : public SpellScriptLoader
{
   public:
       spell_mage_blizzard() : SpellScriptLoader("spell_mage_blizzard") { }

       class spell_mage_blizzard_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_blizzard_SpellScript);

           bool Validate(SpellInfo const* /*spellInfo*/)
           {
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_R1))
                   return false;
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_R2))
                   return false;
               return true;
           }

           void AddChillEffect(SpellEffIndex /*effIndex*/)
           {
               Unit* caster = GetCaster();
               if (Unit* unitTarget = GetHitUnit())
               {
                   if (caster->IsScriptOverriden(GetSpellInfo(), 836))
                       caster->CastSpell(unitTarget, SPELL_MAGE_CHILLED_R1, true);
                   else if (caster->IsScriptOverriden(GetSpellInfo(), 988))
                       caster->CastSpell(unitTarget, SPELL_MAGE_CHILLED_R2, true);
               }
           }

           void Register()
           {
               OnEffectHitTarget += SpellEffectFn(spell_mage_blizzard_SpellScript::AddChillEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
           }
       };

       SpellScript* GetSpellScript() const
       {
           return new spell_mage_blizzard_SpellScript();
       }
};

// Cauterize
class spell_mage_cauterize : public SpellScriptLoader
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") {}

    class spell_mage_cauterize_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_cauterize_AuraScript);

        int32 absorbChance;

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CAUTERIZE_DAMAGE))
                return false;

            return true;
        }

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            absorbChance = GetSpellInfo()->Effects[0].BasePoints;
            return true;
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;

            int32 remainingHealth = caster->GetHealth() - dmgInfo.GetDamage();
            int32 cauterizeHeal = caster->CountPctFromMaxHealth(40);

            if (caster->ToPlayer()->HasSpellCooldown(SPELL_MAGE_CAUTERIZE_DAMAGE))
                return;

            if (!roll_chance_i(absorbChance))
                return;

            if (remainingHealth <= 0)
            {
                absorbAmount = dmgInfo.GetDamage();
                caster->CastCustomSpell(caster,SPELL_MAGE_CAUTERIZE_DAMAGE,NULL,&cauterizeHeal,NULL, true, NULL, aurEff);
                caster->SetHealth(cauterizeHeal);
                caster->ToPlayer()->AddSpellCooldown(SPELL_MAGE_CAUTERIZE_DAMAGE, 0, time(NULL) + 60);
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_cauterize_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_cauterize_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_cauterize_AuraScript();
    }
};

// 11958 - Cold Snap
class spell_mage_cold_snap : public SpellScriptLoader
{
    public:
        spell_mage_cold_snap() : SpellScriptLoader("spell_mage_cold_snap") { }

        class spell_mage_cold_snap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_cold_snap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                // immediately finishes the cooldown on Frost spells
                const SpellCooldowns& cm = caster->GetSpellCooldownMap();
                for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
                {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first);

                    if (spellInfo->SpellFamilyName == SPELLFAMILY_MAGE &&
                        (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FROST) &&
                        spellInfo->Id != SPELL_MAGE_COLD_SNAP && spellInfo->GetRecoveryTime() > 0)
                    {
                        caster->RemoveSpellCooldown((itr++)->first, true);
                    }
                    else
                        ++itr;
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_mage_cold_snap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_cold_snap_SpellScript();
        }
};

// 42955 Conjure Refreshment
/// Updated 4.3.4
struct ConjureRefreshmentData
{
    uint32 minLevel;
    uint32 maxLevel;
    uint32 spellId;
};

uint8 const MAX_CONJURE_REFRESHMENT_SPELLS = 7;
ConjureRefreshmentData const _conjureData[MAX_CONJURE_REFRESHMENT_SPELLS] =
{
    { 33, 43, 92739 },
    { 44, 53, 92799 },
    { 54, 63, 92802 },
    { 64, 73, 92805 },
    { 74, 79, 74625 },
    { 80, 84, 92822 },
    { 85, 85, 92727 }
};

// 42955 - Conjure Refreshment
class spell_mage_conjure_refreshment : public SpellScriptLoader
{
    public:
        spell_mage_conjure_refreshment() : SpellScriptLoader("spell_mage_conjure_refreshment") { }

        class spell_mage_conjure_refreshment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_conjure_refreshment_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                for (uint8 i = 0; i < MAX_CONJURE_REFRESHMENT_SPELLS; ++i)
                    if (!sSpellMgr->GetSpellInfo(_conjureData[i].spellId))
                        return false;
                return true;
            }

            bool Load()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                uint8 level = GetHitUnit()->getLevel();
                for (uint8 i = 0; i < MAX_CONJURE_REFRESHMENT_SPELLS; ++i)
                {
                    ConjureRefreshmentData const& spellData = _conjureData[i];
                    if (level < spellData.minLevel || level > spellData.maxLevel)
                        continue;
                    GetHitUnit()->CastSpell(GetHitUnit(), spellData.spellId);
                    break;
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_conjure_refreshment_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_conjure_refreshment_SpellScript();
        }
};

// -543  - Fire Ward
// -6143 - Frost Ward
class spell_mage_fire_frost_ward : public SpellScriptLoader
{
    public:
        spell_mage_fire_frost_ward() : SpellScriptLoader("spell_mage_fire_frost_ward") { }

        class spell_mage_fire_frost_ward_AuraScript : public spell_mage_incanters_absorbtion_base_AuraScript
        {
            PrepareAuraScript(spell_mage_fire_frost_ward_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_TRIGGERED))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_R1))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    // +80.68% from sp bonus
                    float bonus = 0.8068f;

                    bonus *= caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask());
                    bonus *= caster->CalculateLevelPenalty(GetSpellInfo());

                    amount += int32(bonus);
                }
            }

            void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                Unit* target = GetTarget();
                if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_FROST_WARDING_R1, EFFECT_0))
                {
                    int32 chance = talentAurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue(); // SPELL_EFFECT_DUMMY with NO_TARGET

                    if (roll_chance_i(chance))
                    {
                        int32 bp = dmgInfo.GetDamage();
                        dmgInfo.AbsorbDamage(bp);
                        target->CastCustomSpell(target, SPELL_MAGE_FROST_WARDING_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
                        absorbAmount = 0;
                        PreventDefaultAction();
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_fire_frost_ward_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_fire_frost_ward_AuraScript::Absorb, EFFECT_0);
                AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_fire_frost_ward_AuraScript::Trigger, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_fire_frost_ward_AuraScript();
        }
};

// 54646 - Focus Magic
class spell_mage_focus_magic : public SpellScriptLoader
{
    public:
        spell_mage_focus_magic() : SpellScriptLoader("spell_mage_focus_magic") { }

        class spell_mage_focus_magic_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_focus_magic_AuraScript);

            enum spellId
            {
                SPELL_FOCUS_MAGIC_TALENT    = 54646
            };

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FOCUS_MAGIC_PROC))
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
                _procTarget = GetCaster();
                return _procTarget && _procTarget->isAlive();
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                if (Unit* target = GetTarget())
                {
                    if (Aura* focusMagic = target->GetAura(SPELL_FOCUS_MAGIC_TALENT))
                        if (Unit* fmOwner = focusMagic->GetCaster())
                            fmOwner->CastSpell(fmOwner, SPELL_MAGE_FOCUS_MAGIC_PROC, true, NULL, aurEff);
                }
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_mage_focus_magic_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_mage_focus_magic_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_focus_magic_AuraScript();
        }
};

// 116 - Frostbolt
/// Updated 4.3.4
class spell_mage_frostbolt : public SpellScriptLoader
{
   public:
       spell_mage_frostbolt() : SpellScriptLoader("spell_mage_frostbolt") { }

       class spell_mage_frostbolt_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_frostbolt_SpellScript);

           bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_EARLY_FROST_R1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_EARLY_FROST_R2))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_REM_EARLY_FROST_R1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_REM_EARLY_FROST_R2))
                    return false;
                return true;
            }
           
           void RecalculateDamage(SpellEffIndex /*effIndex*/)
           {
               if (GetHitUnit() && GetHitUnit()->HasAuraState(AURA_STATE_FROZEN, GetSpellInfo(), GetCaster()))
               {
                   if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_SHATTER, EFFECT_1))
                   {
                       int32 damage = GetHitDamage();
                       AddPct(damage, aurEff->GetAmount());
                       SetHitDamage(damage);
                   }
               }
           }

           void HandleOnHit()
           {
               if (Unit* caster = GetCaster())
               {
                    if (AuraEffect* auraEff = caster->GetAuraEffectOfRankedSpell(SPELL_MAGE_EARLY_FROST_R1, EFFECT_0))
                    {
                        switch(auraEff->GetId())
                        {
                            case SPELL_MAGE_EARLY_FROST_R1:
                            {
                                if (!caster->HasAura(SPELL_MAGE_REM_EARLY_FROST_R1))
                                    caster->CastSpell(caster, SPELL_MAGE_REM_EARLY_FROST_R1, true);
                                break;
                            }
                            case SPELL_MAGE_EARLY_FROST_R2:
                            {
                                if (!caster->HasAura(SPELL_MAGE_REM_EARLY_FROST_R2))
                                    caster->CastSpell(caster, SPELL_MAGE_REM_EARLY_FROST_R2, true);
                                break;
                            }
                            default:
                                break;
                        }
                    }
               }
           }

           void Register()
           {
               OnEffectHitTarget += SpellEffectFn(spell_mage_frostbolt_SpellScript::RecalculateDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
               OnCast += SpellCastFn(spell_mage_frostbolt_SpellScript::HandleOnHit);
           }
       };

       SpellScript* GetSpellScript() const
       {
           return new spell_mage_frostbolt_SpellScript();
       }
};

// -44457 - Living Bomb
class spell_mage_living_bomb : public SpellScriptLoader
{
    public:
        spell_mage_living_bomb() : SpellScriptLoader("spell_mage_living_bomb") { }

        class spell_mage_living_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_living_bomb_AuraScript);

            enum spellId
            {
                SPELL_MAGE_LIVING_BOMB  = 44457
            };

            bool Validate(SpellInfo const* spellInfo)
            {
                if (!sSpellMgr->GetSpellInfo(uint32(spellInfo->Effects[EFFECT_1].CalcValue())))
                    return false;
                return true;
            }

            void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Unit* target = GetTarget())
                    {
                        livingTargets = 1;
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(caster, 60.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(target, targets, u_check);
                        target->VisitNearbyObject(60.0, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isAlive() && (*itr)->IsInWorld())
                            {
                                if (Aura* livingBomb = (*itr)->GetAura(SPELL_MAGE_LIVING_BOMB, caster->GetGUID()))
                                {
                                    if (livingTargets <= 0)
                                        continue;

                                    if (livingTargets > 3)
                                    {
                                        livingBomb->Remove(AURA_REMOVE_BY_CANCEL);
                                        livingTargets--;
                                    }
                                    else
                                        livingTargets++;
                                }
                            }
                        }
                    }
                }
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_ENEMY_SPELL && removeMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* caster = GetCaster())
                    caster->CastSpell(GetTarget(), uint32(aurEff->GetAmount()), true, NULL, aurEff);
            }

            void Register()
            {
                //AfterEffectApply += AuraEffectApplyFn(spell_mage_living_bomb_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }

        protected:
            uint16 livingTargets;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_living_bomb_AuraScript();
        }
};

// 11426 - Ice Barrier
/// Updated 4.3.4
class spell_mage_ice_barrier : public SpellScriptLoader
{
   public:
       spell_mage_ice_barrier() : SpellScriptLoader("spell_mage_ice_barrier") { }

       class spell_mage_ice_barrier_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_mage_ice_barrier_AuraScript);

           void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
           {
               if ((GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL) && (GetSpellInfo()->SpellFamilyFlags[EFFECT_1] & 0x00000001) && (GetEffect(EFFECT_0)->GetAmount() <= 0))
               {
                   if (GetTarget()->HasAura(SPELL_MAGE_SHATTERED_BARRIER_R1))
                       GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R1, true);
                   else if (GetTarget()->HasAura(SPELL_MAGE_SHATTERED_BARRIER_R2))
                       GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R2, true);
               }
           }

           void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
           {
               canBeRecalculated = false;
               if (Unit* caster = GetCaster())
               {
                   // 87% SpellPower Bonus
                   float bonus = 0.87f;
                   bonus *= caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                   bonus = caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), bonus);
                   bonus *= caster->CalculateLevelPenalty(GetSpellInfo());
                   amount += int32(bonus);
                   // Glyph of Ice Barrier
                   if (caster->HasAura(63095))
                        amount += amount * 0.30f;
               }
           }

           void Register()
           {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_ice_barrier_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_ice_barrier_AuraScript();
       }
};

// -11119 - Ignite
/// Updated 4.3.4
class spell_mage_ignite : public SpellScriptLoader
{
    public:
        spell_mage_ignite() : SpellScriptLoader("spell_mage_ignite") { }

        class spell_mage_ignite_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_ignite_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_IGNITE))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                storedAmount = 0;
                durationUpdated = false;
                igniteExists = false;
                if (Unit* procTarget = eventInfo.GetProcTarget())
                {
                    if (Aura* ignite = procTarget->GetAura(SPELL_MAGE_IGNITE, eventInfo.GetDamageInfo()->GetAttacker()->GetGUID()))
                    {
                        if (ignite->GetDuration() <= (ignite->GetMaxDuration() - 100) && !igniteExists)
                        {
                            storedAmount += uint32(ignite->GetEffect(EFFECT_0)->GetAmount());
                            durationUpdated = true;
                            igniteExists = true;
                        }
                    }
                }
                return eventInfo.GetProcTarget();
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                uint32 pct = 13;

                // Spells exclusions
                if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetSpellInfo())
                {
                    switch (eventInfo.GetDamageInfo()->GetSpellInfo()->Id)
                    {
                        case 34913: // Molten Armor
                        case 2120:  // Flamestrike
                        case 11113: // Blast Wave
                        case 31661: // Dragon's Breath
                        case 44461: // Living Bomb (Explosion)
                            return;
                        default:
                            break;
                    }
                }

                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, 937, EFFECT_0))
                        pct = aurEff->GetAmount();
                }

                if (SpellInfo const* igniteDot = sSpellMgr->GetSpellInfo(SPELL_MAGE_IGNITE))
                {
                    uint32 amount = uint32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), pct));
                    if (storedAmount > 0)
                        amount += storedAmount;

                    if (Unit* procTarget = eventInfo.GetProcTarget())
                    {
                        if (Unit* target = GetTarget())
                        {
                            amount /= igniteExists ? 3 : 2;
                            if (Unit* caster = GetCaster())
                            {
                                // Mastery: Flashburn
                                if (caster->HasAura(76595))
                                {
                                    float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                                    amount += amount * (0.220f + (0.0280f * masteryPoints));
                                }
                            }

                            target->CastCustomSpell(SPELL_MAGE_IGNITE, SPELLVALUE_BASE_POINT0, amount, eventInfo.GetProcTarget(), true, NULL, aurEff);
                            // Check for existant aura and update the duration to 6 seconds
                            if (Aura* igniteAura = eventInfo.GetProcTarget()->GetAura(SPELL_MAGE_IGNITE, GetCaster()->GetGUID()))
                            {
                                if (durationUpdated)
                                {
                                    igniteAura->SetMaxDuration(6 * IN_MILLISECONDS);
                                    igniteAura->SetDuration(6 * IN_MILLISECONDS);
                                }
                            }
                        }
                    }

                    // Cleanup
                    storedAmount = 0;
                    durationUpdated = false;
                    igniteExists = false;
                }
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_mage_ignite_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_mage_ignite_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        protected:
            uint32 storedAmount;
            bool durationUpdated;
            bool igniteExists;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_ignite_AuraScript();
        }
};

// 543 - Mage Ward
/// Updated 4.3.4
class spell_mage_mage_ward : public SpellScriptLoader
{
   public:
       spell_mage_mage_ward() : SpellScriptLoader("spell_mage_mage_ward") { }

       class spell_mage_mage_ward_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_mage_mage_ward_AuraScript);

           void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
           {
               if (Unit* target = GetTarget())
               {
                   if (AuraEffect* aurEff = GetTarget()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, ICON_MAGE_INCANTER_S_ABSORPTION, EFFECT_0))
                   {
                       int32 bp = CalculatePct(absorbAmount, aurEff->GetAmount());
                       if (!target->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED))
                           target->CastCustomSpell(target, SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true);
                       else
                       {
                           // Get old effect and increase
                           if (AuraEffect* absorption = target->GetAuraEffect(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, 0))
                           {
                               bp += absorption->GetAmount();
                               absorption->SetAmount(bp);
                           }

                           // Refresh duration
                           if (Aura* aur = GetTarget()->GetAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, target->GetGUID()))
                               aur->RefreshDuration();
                       }
                   }
               }
           }

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    // +80.68% from sp bonus
                    float bonus = 0.8068f;
                    bonus *= caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                    amount += int32(bonus);
                }
            }

           void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
           {
               if (Unit* target = GetTarget())
               {
                   if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                   {
                       if (target->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_R1) || target->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_R2))
                           target->CastSpell(target, SPELL_MAGE_INCANTERS_ABSORBTION_KNOCKBACK, true);

                       if (target->HasAura(SPELL_MAGE_MOLTEN_SHIELDS))
                           if (target->HasAura(SPELL_MAGE_BLAZING_SPEED_R1) || target->HasAura(SPELL_MAGE_BLAZING_SPEED_R2))
                                target->CastSpell(target, SPELL_MAGE_BLAZING_SPEED_TRIGGERED, true);
                   }
               }
           }

           void Register()
           {
               DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_mage_ward_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
               AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_mage_ward_AuraScript::HandleAbsorb, EFFECT_0);
               AfterEffectRemove += AuraEffectRemoveFn(spell_mage_mage_ward_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_MANA_SHIELD, AURA_EFFECT_HANDLE_REAL);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_mage_ward_AuraScript();
       }
};

// 1463 - Mana Shield
/// Updated 4.3.4
class spell_mage_mana_shield : public SpellScriptLoader
{
    public:
       spell_mage_mana_shield() : SpellScriptLoader("spell_mage_mana_shield") { }

       class spell_mage_mana_shield_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_mage_mana_shield_AuraScript);

           void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
           {
               if (AuraEffect* aurEff = GetTarget()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, ICON_MAGE_INCANTER_S_ABSORPTION, EFFECT_0))
               {
                   int32 bp = CalculatePct(absorbAmount, aurEff->GetAmount());
                   if (!GetTarget()->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED))
                        GetTarget()->CastCustomSpell(GetTarget(), SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true);
                   else
                   {
                       // Get old effect and increase
                       if (AuraEffect* absorption = GetTarget()->GetAuraEffect(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, 0))
                       {
                           bp += absorption->GetAmount();
                           absorption->SetAmount(bp);
                       }

                       // Refresh duration
                       if (Aura* aur = GetTarget()->GetAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, GetTarget()->GetGUID()))
                           aur->RefreshDuration();
                   }
               }
           }

           void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
           {
               if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
               {
                   if (GetTarget() && GetTarget()->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_R1) || GetTarget()->HasAura(44395))
                       GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_INCANTERS_ABSORBTION_KNOCKBACK, true);
               }
           }

           void Register()
           {
                AfterEffectManaShield += AuraEffectManaShieldFn(spell_mage_mana_shield_AuraScript::HandleAbsorb, EFFECT_0);
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_mana_shield_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_MANA_SHIELD, AURA_EFFECT_HANDLE_REAL);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_mana_shield_AuraScript();
       }
};

enum SilvermoonPolymorph
{
    NPC_AUROSALIA       = 18744
};

// TODO: move out of here and rename - not a mage spell
class spell_mage_polymorph_cast_visual : public SpellScriptLoader
{
    public:
        spell_mage_polymorph_cast_visual() : SpellScriptLoader("spell_mage_polymorph_visual") { }

        class spell_mage_polymorph_cast_visual_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_polymorph_cast_visual_SpellScript);

            static const uint32 PolymorhForms[6];

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                // check if spell ids exist in dbc
                for (uint32 i = 0; i < 6; i++)
                    if (!sSpellMgr->GetSpellInfo(PolymorhForms[i]))
                        return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetCaster()->FindNearestCreature(NPC_AUROSALIA, 30.0f))
                    if (target->GetTypeId() == TYPEID_UNIT)
                        target->CastSpell(target, PolymorhForms[urand(0, 5)], true);
            }

            void Register()
            {
                // add dummy effect spell handler to Polymorph visual
                OnEffectHitTarget += SpellEffectFn(spell_mage_polymorph_cast_visual_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_polymorph_cast_visual_SpellScript();
        }
};

uint32 const spell_mage_polymorph_cast_visual::spell_mage_polymorph_cast_visual_SpellScript::PolymorhForms[6] =
{
    SPELL_MAGE_SQUIRREL_FORM,
    SPELL_MAGE_GIRAFFE_FORM,
    SPELL_MAGE_SERPENT_FORM,
    SPELL_MAGE_DRAGONHAWK_FORM,
    SPELL_MAGE_WORGEN_FORM,
    SPELL_MAGE_SHEEP_FORM
};

// 5405  - Replenish Mana (Mana Gem)
/// Updated 4.3.4
class spell_mage_replenish_mana : public SpellScriptLoader
{
   public:
       spell_mage_replenish_mana() : SpellScriptLoader("spell_mage_replenish_mana") { }

       class spell_mage_replenish_mana_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_replenish_mana_SpellScript);

           bool Validate(SpellInfo const* /*spellInfo*/)
           {
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_IMPROVED_MANA_GEM_TRIGGERED))
                   return false;
               return true;
           }

           void HandleImprovedManaGem()
           {
               if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_IMPROVED_MANA_GEM, EFFECT_0))
               {
                   int32 bp = CalculatePct(GetCaster()->GetMaxPower(POWER_MANA), aurEff->GetAmount());
                   GetCaster()->CastCustomSpell(GetCaster(), SPELL_MAGE_IMPROVED_MANA_GEM_TRIGGERED, &bp, &bp, NULL, true);
               }
           }

           void Register()
           {
               AfterCast += SpellCastFn(spell_mage_replenish_mana_SpellScript::HandleImprovedManaGem);
           }
       };

       SpellScript* GetSpellScript() const
       {
           return new spell_mage_replenish_mana_SpellScript();
       }
};

// 33395 Water Elemental's Freeze
/// Updated 4.3.4
class spell_mage_water_elemental_freeze : public SpellScriptLoader
{
public:
    spell_mage_water_elemental_freeze() : SpellScriptLoader("spell_mage_water_elemental_freeze")
    {
    }

    class spell_mage_water_elemental_freeze_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_water_elemental_freeze_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                return false;
            return true;
        }

        void CountTargets(std::list<WorldObject*>& targetList)
        {
            _didHit = !targetList.empty();
        }

        void HandleImprovedFreeze()
        {
            if (!_didHit)
                return;

            Unit* owner = GetCaster()->GetOwner();
            if (!owner)
                return;

            if (AuraEffect* aurEff = owner->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_IMPROVED_FREEZE, EFFECT_0))
            {
                if (roll_chance_i(aurEff->GetAmount()))
                    owner->CastCustomSpell(SPELL_MAGE_FINGERS_OF_FROST, SPELLVALUE_AURA_STACK, 2, owner, true);
            }

            // Invisibility
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_MAGE_INVISIBILITY_INVISIBLE))
                    caster->RemoveAura(SPELL_MAGE_INVISIBILITY_INVISIBLE);
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_water_elemental_freeze_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            AfterCast += SpellCastFn(spell_mage_water_elemental_freeze_SpellScript::HandleImprovedFreeze);
        }

    private:
        bool _didHit;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_water_elemental_freeze_SpellScript();
    }
};

// 30451 Arcane Blast
/// Updated 4.3.4
class spell_mage_arcane_blast : public SpellScriptLoader
{
public:
    spell_mage_arcane_blast() : SpellScriptLoader("spell_mage_arcane_blast") { }

    class spell_mage_arcane_blast_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_arcane_blast_SpellScript);

        enum spellId
        {
            SPELL_MAGE_NETHER_VORTEX_R1     = 86181,
            SPELL_MAGE_SLOW                 = 31589
        };

        void HandleNetherVortex(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster  || caster->GetTypeId() !=TYPEID_PLAYER)
                return;

            if (Unit* unitTarget = GetHitUnit())
            {
                // Nether Vortex
                if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_MAGE, 2294, EFFECT_0))
                {
                    // Nether Vortex - Rank 1 (Only if chance is triggered)
                    if (aurEff->GetId() == SPELL_MAGE_NETHER_VORTEX_R1 && !roll_chance_i(50))
                        return;

                    bool canSlow = true;

                    // Search for auras
                    Unit::AuraList& auras = caster->GetSingleCastAuras();
                    for (Unit::AuraList::iterator itr = auras.begin(); itr != auras.end();)
                    {
                        if (Aura* aura = *itr)
                        {
                            switch (aura->GetId())
                            {
                                case SPELL_MAGE_SLOW:{canSlow = false;break;}
                                default:break;
                            }
                        }
                        ++itr;
                    }

                    // No auras found, slow it!
                    if (canSlow == true)
                        caster->CastSpell(unitTarget, SPELL_MAGE_SLOW, true);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_mage_arcane_blast_SpellScript::HandleNetherVortex, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_arcane_blast_SpellScript();
    }
};

// 55342 - Mirror Image
/// Updated 4.3.4
class spell_mage_mirror_image : public SpellScriptLoader
{
    public:
        spell_mage_mirror_image() : SpellScriptLoader("spell_mage_mirror_image") { }

        class spell_mage_mirror_image_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_mirror_image_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_GLYPH_OF_MIRROR_IMAGE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_IMAGES_ARCANE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_IMAGES_FIRE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_IMAGES_FROST))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();

                uint32 spellId = SPELL_MAGE_SUMMON_IMAGES_FROST;

                if (Player* player = caster->ToPlayer())
                {
                    bool hasGlyph = false;

                    for (uint32 i = 0; i < MAX_GLYPH_SLOT_INDEX; ++i)
                        if (uint32 glyphId = player->GetGlyph(player->GetActiveSpec(), i))
                            if (GlyphPropertiesEntry const* glyph = sGlyphPropertiesStore.LookupEntry(glyphId))
                                if (glyph->SpellId == SPELL_MAGE_GLYPH_OF_MIRROR_IMAGE)
                                {
                                    hasGlyph = true;
                                    break;
                                }

                    if (hasGlyph)
                    {
                        switch (player->GetPrimaryTalentTree(player->GetActiveSpec()))
                        {

                            case TALENT_TREE_MAGE_ARCANE:
                                spellId = SPELL_MAGE_SUMMON_IMAGES_ARCANE;
                                break;
                            case TALENT_TREE_MAGE_FIRE:
                                spellId = SPELL_MAGE_SUMMON_IMAGES_FIRE;
                                break;
                            case TALENT_TREE_MAGE_FROST:
                                spellId = SPELL_MAGE_SUMMON_IMAGES_FROST;
                                break;
                        }
                    }
                }

                caster->CastSpell(caster, spellId, true);
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_mage_mirror_image_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_mirror_image_SpellScript();
        }
};

// 43987 Ritual of Refreshment
/// Updated 4.3.4
class spell_mage_ritual_of_refreshment : public SpellScriptLoader
{
    public:
        spell_mage_ritual_of_refreshment() : SpellScriptLoader("spell_mage_ritual_of_refreshment") { }

        class spell_mage_ritual_of_refreshment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_ritual_of_refreshment_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RITUAL_OF_REFRESHMENT_R1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RITUAL_OF_REFRESHMENT_R2))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RITUAL_OF_REFRESHMENT_R3))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            caster->ToPlayer()->RemoveSpellCooldown(SPELL_MAGE_RITUAL_OF_REFRESHMENT_R1, true); // Rank 1
                            caster->ToPlayer()->RemoveSpellCooldown(SPELL_MAGE_RITUAL_OF_REFRESHMENT_R2, true); // Rank 2
                            caster->ToPlayer()->RemoveSpellCooldown(SPELL_MAGE_RITUAL_OF_REFRESHMENT_R3, true); // Rank 3

                            if (caster->getLevel() > 75 && caster->getLevel() < 80)
                                caster->CastSpell(caster, SPELL_MAGE_RITUAL_OF_REFRESHMENT_R1, true);

                            if (caster->getLevel() > 80 && caster->getLevel() < 85)
                                caster->CastSpell(caster, SPELL_MAGE_RITUAL_OF_REFRESHMENT_R2, true);

                            if (caster->getLevel() == 85)
                                caster->CastSpell(caster, SPELL_MAGE_RITUAL_OF_REFRESHMENT_R3, true);
                        }
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_mage_ritual_of_refreshment_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_ritual_of_refreshment_SpellScript();
        }
};

// 76547 - Mana Adept (Temp added in Unit::SpellDamageBonusDone till we understand how Zirkon was triggering this)
class spell_mage_mana_adept : public SpellScriptLoader
{
    public:
       spell_mage_mana_adept() : SpellScriptLoader("spell_mage_mana_adept") { }

       class spell_mage_mana_adept_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_mage_mana_adept_AuraScript);

           void Calculate(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
           {
                Unit *caster = aurEff->GetCaster();
                if (!caster)
                    return;

                float masteryValue = caster->GetFloatValue(PLAYER_MASTERY);
                SpellInfo const* spellInfo = aurEff->GetSpellInfo();

                int32 mastery = spellInfo->GetMasteryCoefficient();
                if (!mastery)
                    return;

                ApplyPct(mastery, masteryValue);

                float manaFactor = caster->GetPower(POWER_MANA) / caster->GetMaxPower(POWER_MANA);
                canBeRecalculated = true;
                amount = mastery * manaFactor;
           }

           void Register()
           {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_mana_adept_AuraScript::Calculate, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_mana_adept_AuraScript();
       }
};

class spell_mage_master_of_elements : public SpellScriptLoader
{
    public:
        spell_mage_master_of_elements() : SpellScriptLoader("spell_mage_master_of_elements") { }

        class spell_mage_master_of_elements_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_master_of_elements_AuraScript);

            enum spellId
            {
                SPELL_PROC_MASTER_OF_ELEMENTS       = 29077,
                SPELL_TALENT_MASTER_OF_ELEMENTS_R1  = 29074,
                SPELL_TALENT_MASTER_OF_ELEMENTS_R2  = 29075
            };

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PROC_MASTER_OF_ELEMENTS))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return eventInfo.GetDamageInfo()->GetSpellInfo();
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                int32 mana = int32(eventInfo.GetDamageInfo()->GetSpellInfo()->CalcPowerCost(GetTarget(), eventInfo.GetDamageInfo()->GetSchoolMask()));
                mana = CalculatePct(mana, aurEff->GetAmount());

                if (mana > 0)
                {
                    if (GetTarget()->HasAura(SPELL_TALENT_MASTER_OF_ELEMENTS_R1))
                        GetTarget()->CastCustomSpell(SPELL_PROC_MASTER_OF_ELEMENTS, SPELLVALUE_BASE_POINT0, mana / 2, GetTarget(), true, NULL, aurEff);
                    if (GetTarget()->HasAura(SPELL_TALENT_MASTER_OF_ELEMENTS_R2))
                        GetTarget()->CastCustomSpell(SPELL_PROC_MASTER_OF_ELEMENTS, SPELLVALUE_BASE_POINT0, mana, GetTarget(), true, NULL, aurEff);
                }
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_mage_master_of_elements_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_mage_master_of_elements_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_master_of_elements_AuraScript();
        }
};

// 83154 - Piercing Chill
class spell_mage_piercing_chill : public SpellScriptLoader
{
    public:
        spell_mage_piercing_chill() : SpellScriptLoader("spell_mage_piercing_chill") { }

        class spell_mage_piercing_chill_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_piercing_chill_SpellScript);

            void HandleTargetSelectEff0(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                if(Unit* caster = GetCaster())
                {
                    targets.remove(GetExplTargetUnit());

                   if(AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_MAGE, 4625, EFFECT_0))
                   {
                       Trinity::Containers::RandomResizeList(targets, aurEff->GetAmount());
                       additionalTargets = targets;
                   }
                }
            }

            void RemoveTargetEffect(WorldObject*& target)
            {
                target = NULL;
            }

            void HandleTargetSelectEff2(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                targets.clear();

                if(!additionalTargets.empty())
                    targets = additionalTargets;
            }

        private:
            std::list<WorldObject*> additionalTargets;

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_piercing_chill_SpellScript::HandleTargetSelectEff0, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_mage_piercing_chill_SpellScript::RemoveTargetEffect, EFFECT_2, TARGET_UNIT_TARGET_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_piercing_chill_SpellScript::HandleTargetSelectEff2, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_piercing_chill_SpellScript();
        }
};

// 66 - Invisibility (Fading)
class spell_mage_invisibility_fading : public SpellScriptLoader
{
public:
    spell_mage_invisibility_fading() : SpellScriptLoader("spell_mage_invisibility_fading") { }

    class spell_mage_invisibility_fading_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_invisibility_fading_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_INVISIBILITY_FADING))
                return false;
            return true;
        }

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if(Unit* player = GetTarget()->ToPlayer())
            {
                if(Guardian* pet = player->ToPlayer()->GetGuardianPet())
                {
                    pet->CombatStop();
                    pet->AttackStop();
                    pet->InterruptNonMeleeSpells(false);
                    pet->SendMeleeAttackStop();
                    pet->AddAura(SPELL_MAGE_INVISIBILITY_FADING, pet);
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectRemoveFn(spell_mage_invisibility_fading_AuraScript::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_invisibility_fading_AuraScript();
    }
};

class spell_mage_invisibility_invisible : public SpellScriptLoader
{
public:
    spell_mage_invisibility_invisible() : SpellScriptLoader("spell_mage_invisibility_invisible") { }

    class spell_mage_invisibility_invisible_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_invisibility_invisible_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_INVISIBILITY_INVISIBLE))
                return false;
            return true;
        }

        void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if(Unit* target = GetTarget())
            {
                if(target->isGuardian())
                {
                    // Remove Invisibility from mage when elemental does an action
                    if(Unit* owner = target->GetOwner())
                        owner->RemoveAura(SPELL_MAGE_INVISIBILITY_INVISIBLE);
                }
                else
                {
                    // Remove Invisibility from elemental when mage does an action
                    if(Guardian* elemental = target->ToPlayer()->GetGuardianPet())
                        elemental->RemoveAura(SPELL_MAGE_INVISIBILITY_INVISIBLE);
                }
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_invisibility_invisible_AuraScript::RemoveEffect, EFFECT_1, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_invisibility_invisible_AuraScript();
    }
};

class spell_mage_summon_water_elemental : public SpellScriptLoader
{
    public:
        spell_mage_summon_water_elemental() : SpellScriptLoader("spell_mage_summon_water_elemental") { }

        class spell_mage_summon_water_elemental_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_summon_water_elemental_SpellScript);

            enum spellId
            {
                SPELL_SUMMON_WATER_ELEMENTAL    = 31687
            };

            SpellCastResult CheckRequirement()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->HasSpell(SPELL_SUMMON_WATER_ELEMENTAL))
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_DONT_REPORT;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_mage_summon_water_elemental_SpellScript::CheckRequirement);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_summon_water_elemental_SpellScript();
        }
};

// 44614 - Frostfire Bolt
class spell_mage_frostfire_bolt : public SpellScriptLoader
{
    public:
        spell_mage_frostfire_bolt() : SpellScriptLoader("spell_mage_frostfire_bolt") { }

        enum spellId
        {
            SPELL_GLYPH_OF_FROSTFIRE    = 61205,
            SPELL_FROSTFIRE_ORB_R1      = 84726,
            SPELL_FROSTFIRE_ORB_R2      = 84727
        };

        class spell_mage_frostfire_bolt_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_frostfire_bolt_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Avoid to slow target with glyph active
                    if (caster->HasAura(SPELL_GLYPH_OF_FROSTFIRE))
                        amount = 0;
                }
            }

            void UpdateAmount(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (!caster->HasAura(SPELL_GLYPH_OF_FROSTFIRE))
                        aurEff->GetBase()->SetStackAmount(1);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_frostfire_bolt_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED);
                AfterEffectApply += AuraEffectApplyFn(spell_mage_frostfire_bolt_AuraScript::UpdateAmount, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_frostfire_bolt_AuraScript();
        }
};

class spell_mage_impact_effect : public SpellScriptLoader
{
    public:
        spell_mage_impact_effect() : SpellScriptLoader("spell_mage_impact_effect") { }

        enum spellId
        {
            SPELL_MAGE_FIRE_BLAST   = 2136
        };

        class spell_mage_impact_effect_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_impact_effect_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    caster->RemoveSpellCooldown(SPELL_MAGE_FIRE_BLAST, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_impact_effect_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_impact_effect_SpellScript();
        }
};

class spell_mage_ice_block : public SpellScriptLoader
{
    public:
        spell_mage_ice_block() : SpellScriptLoader("spell_mage_ice_block") { }

        enum spellId
        {
            SPELL_MAGE_GLYPH_OF_ICE_BLOCK   = 56372,
            SPELL_MAGE_FROST_NOVA           = 122
        };

        class spell_mage_ice_block_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_ice_block_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                {
                    if (caster->HasAura(SPELL_MAGE_GLYPH_OF_ICE_BLOCK))
                        caster->RemoveSpellCooldown(SPELL_MAGE_FROST_NOVA, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_ice_block_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_ice_block_SpellScript();
        }
};

class spell_mage_glyph_of_molten_armor : public SpellScriptLoader
{
public:
    spell_mage_glyph_of_molten_armor() : SpellScriptLoader("spell_mage_glyph_of_molten_armor") { }

    class spell_mage_glyph_of_molten_armor_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_glyph_of_molten_armor_AuraScript);

        enum spellId
        {
            SPELL_MAGE_MOLTEN_ARMOR     = 30482
        };

        enum iconId
        {
            ICON_MAGE_MOLTEN_ARMOR  = 2307
        };

        void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                // Glyph of Molten Armor (Safety check)
                if (target->HasAura(SPELL_MAGE_MOLTEN_ARMOR))
                {
                    target->RemoveAurasDueToSpell(SPELL_MAGE_MOLTEN_ARMOR);
                    target->CastSpell(target, SPELL_MAGE_MOLTEN_ARMOR, true);
                }
            }
        }

        void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                // Glyph of Molten Armor (Safety check)
                if (target->HasAura(SPELL_MAGE_MOLTEN_ARMOR))
                {
                    target->RemoveAurasDueToSpell(SPELL_MAGE_MOLTEN_ARMOR);
                    target->CastSpell(target, SPELL_MAGE_MOLTEN_ARMOR, true);
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_mage_glyph_of_molten_armor_AuraScript::ApplyEffect, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_glyph_of_molten_armor_AuraScript::RemoveEffect, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_glyph_of_molten_armor_AuraScript();
    }
};

class spell_mage_pyroblast : public SpellScriptLoader
{
    public:
        spell_mage_pyroblast() : SpellScriptLoader("spell_mage_pyroblast") { }

        enum spellId
        {
            SPELL_MAGE_PYROBLAST_NORMAL     = 11366,
            SPELL_MAGE_PYROBLAST_INSTANT    = 92315
        };

        class spell_mage_pyroblast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_pyroblast_SpellScript);

            void HandlePeriodic(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (!GetSpellInfo())
                    return;

                if (Unit* target = GetHitUnit())
                {
                    switch (GetSpellInfo()->Id)
                    {
                        case SPELL_MAGE_PYROBLAST_NORMAL: // Pyroblast (Normal)
                        {
                            if (target->HasAura(SPELL_MAGE_PYROBLAST_INSTANT, caster->GetGUID()))
                                target->RemoveAurasDueToSpell(SPELL_MAGE_PYROBLAST_INSTANT);
                            break;
                        }
                        case SPELL_MAGE_PYROBLAST_INSTANT: // Pyroblast (Instant)
                        {
                            if (target->HasAura(SPELL_MAGE_PYROBLAST_NORMAL, caster->GetGUID()))
                                target->RemoveAurasDueToSpell(SPELL_MAGE_PYROBLAST_NORMAL);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_pyroblast_SpellScript::HandlePeriodic, EFFECT_1, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_pyroblast_SpellScript();
        }
};

class spell_mage_ring_of_frost : public SpellScriptLoader
{
public:
    spell_mage_ring_of_frost() : SpellScriptLoader("spell_mage_ring_of_frost")
    {
    }

    class spell_mage_ring_of_frost_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_ring_of_frost_SpellScript);

        enum spellId
        {
            SPELL_RING_OF_FROST_FREEZE      = 82691,
            SPELL_RING_OF_FROST_IMMUNITY    = 91264
        };

        enum npcId
        {
            NPC_RING_OF_FROST = 44199
        };

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            std::list<WorldObject*> validTarget;
            for (std::list<WorldObject*>::iterator target = targets.begin(); target != targets.end(); ++target)
            {
                if ((*target))
                {
                    if (Unit* unit = (*target)->ToUnit())
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, GetCaster(), NPC_RING_OF_FROST, 85.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator ring = creatures.begin(); ring != creatures.end(); ++ring)
                        {
                            if ((*ring) && (*ring)->GetCharmerOrOwner() && (*ring)->GetCharmerOrOwner() == GetCaster())
                            {
                                // Exclude all targets with immunity or already frozen
                                if (!unit->HasAura(SPELL_RING_OF_FROST_FREEZE) && !unit->HasAura(SPELL_RING_OF_FROST_IMMUNITY) && (*ring)->IsInRange(unit, 2.0f, 5.0f))
                                    validTarget.push_back((*target));
                            }
                        }
                    }
                }
            }

            targets.clear();

            for (std::list<WorldObject*>::iterator itr = validTarget.begin(); itr != validTarget.end(); ++itr)
                targets.push_back((*itr));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_ring_of_frost_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_ring_of_frost_SpellScript();
    }
};

class spell_mage_flamestrike : public SpellScriptLoader
{
public:
    spell_mage_flamestrike() : SpellScriptLoader("spell_mage_flamestrike")
    {
    }

    class spell_mage_flamestrike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_flamestrike_SpellScript);

        enum spellId
        {
            SPELL_FLAMESTRIKE   = 2120
        };

        void HandleController()
        {
            if (Unit* caster = GetCaster())
            {
                if (WorldLocation const* const position = GetExplTargetDest())
                {
                    if (DynamicObject* flamestrike = caster->GetDynObject(SPELL_FLAMESTRIKE))
                    {
                        if (flamestrike->GetDistance2d(position->GetPositionX(), position->GetPositionY()) < 10.0f)
                            if (flamestrike->GetCaster() && flamestrike->GetCaster() == caster)
                                flamestrike->Remove();
                    }
                }
            }
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_mage_flamestrike_SpellScript::HandleController);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_flamestrike_SpellScript();
    }
};

void AddSC_mage_spell_scripts()
{
    new spell_mage_blast_wave();
    new spell_mage_blizzard();
    new spell_mage_burnout();
    new spell_mage_cauterize();
    new spell_mage_cold_snap();
    new spell_mage_conjure_refreshment();
    new spell_mage_fire_frost_ward();
    new spell_mage_focus_magic();
    new spell_mage_frostbolt();
    new spell_mage_ice_barrier();
    new spell_mage_ignite();
    new spell_mage_living_bomb();
    new spell_mage_mage_ward();
    new spell_mage_mana_shield();
    new spell_mage_polymorph_cast_visual();
    new spell_mage_replenish_mana();
    new spell_mage_water_elemental_freeze();
    new spell_mage_arcane_blast();
    new spell_mage_mirror_image();
    new spell_mage_ritual_of_refreshment();
    new spell_mage_master_of_elements();
    new spell_mage_piercing_chill();
    new spell_mage_invisibility_invisible();
    new spell_mage_invisibility_fading();
    new spell_mage_summon_water_elemental();
    new spell_mage_frostfire_bolt();
    new spell_mage_impact_effect();
    new spell_mage_ice_block();
    new spell_mage_glyph_of_molten_armor();
    new spell_mage_pyroblast();
    new spell_mage_ring_of_frost();
    new spell_mage_flamestrike();
}
