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
 * Scripts for spells with SPELLFAMILY_HUNTER, SPELLFAMILY_PET and SPELLFAMILY_GENERIC spells used by hunter players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_hun_".
 */

#include "Pet.h"
#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum HunterSpells
{
    SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET            = 61669,
    SPELL_HUNTER_ASPECT_OF_THE_VIPER_ENERGIZE       = 34075,
    SPELL_HUNTER_BESTIAL_WRATH                      = 19574,
    SPELL_HUNTER_CHIMERA_SHOT_SERPENT               = 53353,
    SPELL_HUNTER_CHIMERA_SHOT_VIPER                 = 53358,
    SPELL_HUNTER_CHIMERA_SHOT_SCORPID               = 53359,
    SPELL_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER       = 56851,
    SPELL_HUNTER_INVIGORATION_TRIGGERED             = 53398,
    SPELL_HUNTER_MASTERS_CALL_TRIGGERED             = 62305,
    SPELL_HUNTER_MISDIRECTION_PROC                  = 35079,
    SPELL_HUNTER_PET_LAST_STAND_TRIGGERED           = 53479,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX           = 55709,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED = 54114,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF    = 55711,
    SPELL_HUNTER_PET_CARRION_FEEDER_TRIGGERED       = 54045,
    SPELL_HUNTER_READINESS                          = 23989,
    SPELL_HUNTER_SNIPER_TRAINING_R1                 = 53302,
    SPELL_HUNTER_SNIPER_TRAINING_BUFF_R1            = 64418,
    SPELL_DRAENEI_GIFT_OF_THE_NAARU                 = 59543,

    SPELL_HUNTER_SERPENT_STING                      = 1978,
    SPELL_HUNTER_KILL_COMMAND                       = 34026,
    SPELL_HUNTER_KILL_COMMAND_TRIGGER               = 83381,
    SPELL_HUNTER_FOCUS_FIRE                         = 82692,
    HUNTER_PET_SPELL_FRENZY                         = 19615,
    HUNTER_PET_SPELL_FOCUS_FIRE_REGEN               = 83468,
    HUNTER_VISUAL_FOCUS_FIRE                        = 88843,
    HUNTER_PET_AURA_FRENZY_TRIGGER                  = 20784, // Tamed Pet Passive 07 (DND)

    SPELL_HUNTER_COBRA_SHOT_ENERGIZE                = 91954,
    SPELL_HUNTER_STEADY_SHOT                        = 56641,
    SPELL_HUNTER_STEADY_SHOT_ENERGIZE               = 77443,
    SPELL_HUNTER_STEADY_SHOT_ATTACK_SPEED           = 53220,

    SPELL_HUNTER_POSTHASTE                          = 83559,
    SPELL_HUNTER_ENERGIZE                           = 82716,

    SPELL_HUN_GLYPH_OF_SILENCING_SHOT               = 56836,

    SPELL_ITEM_HUNTER_T11_4P_TRIGGER                = 95933,
    SPELL_ITEM_HUNTER_T11_4P                        = 89925
};


// 13161 - Aspect of the Beast
class spell_hun_aspect_of_the_beast : public SpellScriptLoader
{
    public:
        spell_hun_aspect_of_the_beast() : SpellScriptLoader("spell_hun_aspect_of_the_beast") { }

        class spell_hun_aspect_of_the_beast_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_aspect_of_the_beast_AuraScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET))
                    return false;
                return true;
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    if (Pet* pet = caster->GetPet())
                        pet->RemoveAurasDueToSpell(SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET);
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetPet())
                        caster->CastSpell(caster, SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET, true);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_hun_aspect_of_the_beast_AuraScript::OnApply, EFFECT_0, SPELL_AURA_UNTRACKABLE, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_hun_aspect_of_the_beast_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_UNTRACKABLE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_aspect_of_the_beast_AuraScript();
        }
};

// 34074 - Aspect of the Viper
class spell_hun_ascpect_of_the_viper : public SpellScriptLoader
{
    public:
        spell_hun_ascpect_of_the_viper() : SpellScriptLoader("spell_hun_ascpect_of_the_viper") { }

        class spell_hun_ascpect_of_the_viper_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_ascpect_of_the_viper_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_ASPECT_OF_THE_VIPER_ENERGIZE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();

                uint32 maxMana = GetTarget()->GetMaxPower(POWER_MANA);
                int32 mana = CalculatePct(maxMana, GetTarget()->GetBaseAttackTime(RANGED_ATTACK) / 1000.0f);

                if (AuraEffect const* glyph = GetTarget()->GetAuraEffect(SPELL_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER, EFFECT_0))
                    AddPct(mana, glyph->GetAmount());

                GetTarget()->CastCustomSpell(SPELL_HUNTER_ASPECT_OF_THE_VIPER_ENERGIZE, SPELLVALUE_BASE_POINT0, mana, GetTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_hun_ascpect_of_the_viper_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_OBS_MOD_POWER);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_ascpect_of_the_viper_AuraScript();
        }
};

// 781 - Disengage
class spell_hun_disengage : public SpellScriptLoader
{
    public:
        spell_hun_disengage() : SpellScriptLoader("spell_hun_disengage") { }

        class spell_hun_disengage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_disengage_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (caster->GetTypeId() == TYPEID_PLAYER && !caster->isInCombat())
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                return SPELL_CAST_OK;
            }

            void HandlePostHaste(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Posthaste
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_HUNTER, 5094, 1))
                    {
                        int32 bp0 = aurEff->GetAmount();
                        caster->CastCustomSpell(caster, SPELL_HUNTER_POSTHASTE, &bp0, NULL, NULL, true, NULL);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_hun_disengage_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_hun_disengage_SpellScript::HandlePostHaste, EFFECT_0, SPELL_EFFECT_LEAP_BACK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_disengage_SpellScript();
        }
};

// 53412 - Invigoration
class spell_hun_invigoration : public SpellScriptLoader
{
    public:
        spell_hun_invigoration() : SpellScriptLoader("spell_hun_invigoration") { }

        class spell_hun_invigoration_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_invigoration_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_INVIGORATION_TRIGGERED))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                    if (AuraEffect* aurEff = unitTarget->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 3487, 0))
                        if (roll_chance_i(aurEff->GetAmount()))
                            unitTarget->CastSpell(unitTarget, SPELL_HUNTER_INVIGORATION_TRIGGERED, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_invigoration_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_invigoration_SpellScript();
        }
};

// 53478 - Last Stand Pet
class spell_hun_last_stand_pet : public SpellScriptLoader
{
    public:
        spell_hun_last_stand_pet() : SpellScriptLoader("spell_hun_last_stand_pet") { }

        class spell_hun_last_stand_pet_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_last_stand_pet_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_PET_LAST_STAND_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(30));
                caster->CastCustomSpell(caster, SPELL_HUNTER_PET_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_last_stand_pet_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_last_stand_pet_SpellScript();
        }
};

// 53271 - Masters Call
class spell_hun_masters_call : public SpellScriptLoader
{
    public:
        spell_hun_masters_call() : SpellScriptLoader("spell_hun_masters_call") { }

        class spell_hun_masters_call_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_masters_call_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* ally = GetHitUnit())
                    if (Player* caster = GetCaster()->ToPlayer())
                        if (Pet* target = caster->GetPet())
                        {
                            TriggerCastFlags castMask = TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_IGNORE_CASTER_AURASTATE);
                            target->CastSpell(ally, GetEffectValue(), castMask);
                            target->CastSpell(ally, GetSpellInfo()->Effects[EFFECT_0].CalcValue(), castMask);
                        }
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    // Cannot be processed while pet is dead
                    TriggerCastFlags castMask = TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_IGNORE_CASTER_AURASTATE);
                    target->CastSpell(target, SPELL_HUNTER_MASTERS_CALL_TRIGGERED, castMask);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_masters_call_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnEffectHitTarget += SpellEffectFn(spell_hun_masters_call_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_masters_call_SpellScript();
        }
};

// 34477 - Misdirection
class spell_hun_misdirection : public SpellScriptLoader
{
    public:
        spell_hun_misdirection() : SpellScriptLoader("spell_hun_misdirection") { }

        class spell_hun_misdirection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_misdirection_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_MISDIRECTION_PROC))
                    return false;
                return true;
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEFAULT)
                    GetTarget()->ResetRedirectThreat();
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                return GetTarget()->GetRedirectThreatTarget();
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_MISDIRECTION_PROC, true, NULL, aurEff);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_hun_misdirection_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                DoCheckProc += AuraCheckProcFn(spell_hun_misdirection_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_hun_misdirection_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_misdirection_AuraScript();
        }
};

// 35079 - Misdirection (Proc)
class spell_hun_misdirection_proc : public SpellScriptLoader
{
    public:
        spell_hun_misdirection_proc() : SpellScriptLoader("spell_hun_misdirection_proc") { }

        class spell_hun_misdirection_proc_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_misdirection_proc_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->ResetRedirectThreat();
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_hun_misdirection_proc_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_misdirection_proc_AuraScript();
        }
};

// 54044 - Pet Carrion Feeder
class spell_hun_pet_carrion_feeder : public SpellScriptLoader
{
    public:
        spell_hun_pet_carrion_feeder() : SpellScriptLoader("spell_hun_pet_carrion_feeder") { }

        class spell_hun_pet_carrion_feeder_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_pet_carrion_feeder_SpellScript);

            bool Load()
            {
                if (!GetCaster()->isPet())
                    return false;
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_PET_CARRION_FEEDER_TRIGGERED))
                    return false;
                return true;
            }

            SpellCastResult CheckIfCorpseNear()
            {
                Unit* caster = GetCaster();
                float max_range = GetSpellInfo()->GetMaxRange(false);
                WorldObject* result = NULL;
                // search for nearby enemy corpse in range
                Trinity::AnyDeadUnitSpellTargetInRangeCheck check(caster, max_range, GetSpellInfo(), TARGET_CHECK_ENEMY);
                Trinity::WorldObjectSearcher<Trinity::AnyDeadUnitSpellTargetInRangeCheck> searcher(caster, result, check);
                caster->GetMap()->VisitFirstFound(caster->m_positionX, caster->m_positionY, max_range, searcher);
                if (!result)
                    return SPELL_FAILED_NO_EDIBLE_CORPSES;
                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                caster->CastSpell(caster, SPELL_HUNTER_PET_CARRION_FEEDER_TRIGGERED, false);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_hun_pet_carrion_feeder_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_hun_pet_carrion_feeder_SpellScript::CheckIfCorpseNear);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_pet_carrion_feeder_SpellScript();
        }
};

// 55709 - Pet Heart of the Phoenix
class spell_hun_pet_heart_of_the_phoenix : public SpellScriptLoader
{
    public:
        spell_hun_pet_heart_of_the_phoenix() : SpellScriptLoader("spell_hun_pet_heart_of_the_phoenix") { }

        class spell_hun_pet_heart_of_the_phoenix_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_pet_heart_of_the_phoenix_SpellScript);

            bool Load()
            {
                if (!GetCaster()->isPet())
                    return false;
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED) || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* owner = caster->GetOwner())
                    if (!caster->HasAura(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF))
                    {
                        owner->CastCustomSpell(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED, SPELLVALUE_BASE_POINT0, 100, caster, true);
                        caster->CastSpell(caster, SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF, true);
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_pet_heart_of_the_phoenix_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_pet_heart_of_the_phoenix_SpellScript();
        }
};

// 23989 - Readiness
class spell_hun_readiness : public SpellScriptLoader
{
    public:
        spell_hun_readiness() : SpellScriptLoader("spell_hun_readiness") { }

        class spell_hun_readiness_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_readiness_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                // immediately finishes the cooldown on your other Hunter abilities except Bestial Wrath
                const SpellCooldowns& cm = caster->ToPlayer()->GetSpellCooldownMap();
                for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
                {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first);

                    ///! If spellId in cooldown map isn't valid, the above will return a null pointer.
                    if (spellInfo &&
                        spellInfo->SpellFamilyName == SPELLFAMILY_HUNTER &&
                        spellInfo->Id != SPELL_HUNTER_READINESS &&
                        spellInfo->Id != SPELL_HUNTER_BESTIAL_WRATH &&
                        spellInfo->Id != SPELL_DRAENEI_GIFT_OF_THE_NAARU &&
                        spellInfo->GetRecoveryTime() > 0)
                        caster->RemoveSpellCooldown((itr++)->first, true);
                    else
                        ++itr;
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_readiness_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_readiness_SpellScript();
        }
};

// 37506 - Scatter Shot
class spell_hun_scatter_shot : public SpellScriptLoader
{
    public:
        spell_hun_scatter_shot() : SpellScriptLoader("spell_hun_scatter_shot") { }

        class spell_hun_scatter_shot_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_scatter_shot_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                // break Auto Shot and autohit
                caster->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
                caster->AttackStop();
                caster->SendAttackSwingCancelAttack();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_scatter_shot_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_scatter_shot_SpellScript();
        }
};

// -53302 - Sniper Training
class spell_hun_sniper_training : public SpellScriptLoader
{
    public:
        spell_hun_sniper_training() : SpellScriptLoader("spell_hun_sniper_training") { }

        class spell_hun_sniper_training_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_sniper_training_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_SNIPER_TRAINING_R1) || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_SNIPER_TRAINING_BUFF_R1))
                    return false;
                return true;
            }

            void HandlePeriodic(AuraEffect const* aurEff)
            {
                PreventDefaultAction();
                if (aurEff->GetAmount() <= 0)
                {
                    Unit* caster = GetCaster();
                    if (!caster)
                        return;

                    uint32 spellId = SPELL_HUNTER_SNIPER_TRAINING_BUFF_R1 + GetId() - SPELL_HUNTER_SNIPER_TRAINING_R1;
                    if (Unit* target = GetTarget())
                    {
                        if (Aura* aur = target->GetAura(spellId, caster->GetGUID()))
                        {
                            if (aur->GetDuration() < (aur->GetMaxDuration() / 2))
                            {
                                SpellInfo const* triggeredSpellInfo = sSpellMgr->GetSpellInfo(spellId);
                                Unit* triggerCaster = triggeredSpellInfo->NeedsToBeTriggeredByCaster() ? caster : target;
                                if (triggerCaster)
                                    triggerCaster->CastSpell(target, triggeredSpellInfo, true, 0, aurEff);
                            }
                        }
                        else
                        {
                            SpellInfo const* triggeredSpellInfo = sSpellMgr->GetSpellInfo(spellId);
                            Unit* triggerCaster = triggeredSpellInfo->NeedsToBeTriggeredByCaster() ? caster : target;
                            if (triggerCaster)
                                triggerCaster->CastSpell(target, triggeredSpellInfo, true, 0, aurEff);
                        }
                    }
                }
            }

            void HandleUpdatePeriodic(AuraEffect* aurEff)
            {
                if (Player* playerTarget = GetUnitOwner()->ToPlayer())
                {
                    int32 baseAmount = aurEff->GetBaseAmount();
                    int32 amount = playerTarget->isMoving() ?
                    playerTarget->CalculateSpellDamage(playerTarget, GetSpellInfo(), aurEff->GetEffIndex(), &baseAmount) :
                    aurEff->GetAmount() - 1;
                    aurEff->SetAmount(amount);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_sniper_training_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_hun_sniper_training_AuraScript::HandleUpdatePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_sniper_training_AuraScript();
        }
};

// 1515 - Tame Beast
class spell_hun_tame_beast : public SpellScriptLoader
{
    public:
        spell_hun_tame_beast() : SpellScriptLoader("spell_hun_tame_beast") { }

        class spell_hun_tame_beast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_tame_beast_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                if (!GetExplTargetUnit())
                    return SPELL_FAILED_BAD_IMPLICIT_TARGETS;

                if (Creature* target = GetExplTargetUnit()->ToCreature())
                {
                    if (target->getLevel() > caster->getLevel())
                        return SPELL_FAILED_HIGHLEVEL;

                    // use SMSG_PET_TAME_FAILURE?
                    if (!target->GetCreatureTemplate()->isTameable(caster->ToPlayer()->CanTameExoticPets()))
                        return SPELL_FAILED_BAD_TARGETS;

                    if (caster->GetPetGUID())
                        return SPELL_FAILED_ALREADY_HAVE_SUMMON;

                    if (caster->GetCharmGUID())
                        return SPELL_FAILED_ALREADY_HAVE_CHARM;
                    if (caster->ToPlayer()->IsPetListFull())
                    {
                        caster->ToPlayer()->SendPetTameError(PET_TAME_ERROR_TOO_MANY_PETS);
                        return SPELL_FAILED_DONT_REPORT;
                    }
                }
                else
                    return SPELL_FAILED_BAD_IMPLICIT_TARGETS;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_hun_tame_beast_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_tame_beast_SpellScript();
        }
};

//34026 - KIll Command
class spell_hun_kill_command: public SpellScriptLoader
{
public:
    spell_hun_kill_command() : SpellScriptLoader("spell_hun_kill_command") { }

    class spell_hun_kill_command_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_hun_kill_command_SpellScript)

        SpellCastResult CheckCast()
        {
            Pet* pet = GetCaster()->ToPlayer()->GetPet();

            if (!pet || pet->isDead())
                return SPELL_FAILED_NO_PET;

            if (!pet->IsWithinMeleeRange(pet->getVictim()))
                return SPELL_FAILED_OUT_OF_RANGE;

            return SPELL_CAST_OK;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (Pet* pet = caster->ToPlayer()->GetPet())
                {
                    if (Unit* victim = pet->getVictim())
                        pet->CastCustomSpell(victim, (uint32)GetEffectValue(), 0, NULL, NULL, true, NULL, NULL, pet->GetGUID());
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_hun_kill_command_SpellScript::CheckCast);
            OnEffectHit += SpellEffectFn(spell_hun_kill_command_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_kill_command_SpellScript();
    }
};

// 77767 Cobra Shot
/// Updated 4.0.6
class spell_hun_cobra_shot : public SpellScriptLoader
{
public:
    spell_hun_cobra_shot() : SpellScriptLoader("spell_hun_cobra_shot") { }

    class spell_hun_cobra_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_cobra_shot_SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_COBRA_SHOT_ENERGIZE))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* target = GetHitUnit();

            if (!target)
                return;

            // Get normal serpent sting or Serpent Spread's proc result one
            if (AuraEffect* serpentSting = target->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_HUNTER, 16384, 0, 0, GetCaster()->GetGUID()))
            {
                serpentSting->GetBase()->SetDuration(serpentSting->GetBase()->GetDuration() + (GetSpellInfo()->Effects[EFFECT_1].BasePoints * 1000));
                if (serpentSting->GetBase()->GetDuration() >= 15000)
                    serpentSting->GetBase()->SetDuration(15000);
            }
        }

        void HandleFocusRegen(SpellEffIndex /*effIndex*/)
        {
            Unit* target = GetHitUnit();

            if (!target)
                return;

            // Glyph of the Dazzled Prey
            if (GetCaster()->HasAura(56856) && target->HasAuraWithMechanic(MECHANIC_DAZE))
            {
                basePoints0 = 11;
                GetCaster()->CastCustomSpell(GetCaster(), SPELL_HUNTER_COBRA_SHOT_ENERGIZE, &basePoints0, NULL, NULL, true, NULL, NULL, GetCaster()->GetGUID());
            }
            else
                GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_COBRA_SHOT_ENERGIZE, true);
        }

    private:
        int32 basePoints0;

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_cobra_shot_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            OnEffectLaunchTarget += SpellEffectFn(spell_hun_cobra_shot_SpellScript::HandleFocusRegen, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_cobra_shot_SpellScript();
    }
};

// 56641 Steady Shot
/// Updated 4.3.4
class spell_hun_steady_shot : public SpellScriptLoader
{
public:
    spell_hun_steady_shot() : SpellScriptLoader("spell_hun_steady_shot") { }

    class spell_hun_steady_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_steady_shot_SpellScript);
        int8 castCount;
        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_STEADY_SHOT_ENERGIZE))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            castCount++;
            if (castCount > 1)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->ToPlayer()->KilledMonsterCredit(44175, 0);
                }
                castCount = 0;
            }
        }

        void HandleFocusRegen(SpellEffIndex /*effIndex*/)
        {
            Unit* target = GetHitUnit();

            if (!target)
                return;

            // Glyph of the Dazzled Prey
            if (GetCaster()->HasAura(56856) && target->HasAuraWithMechanic(MECHANIC_DAZE))
            {
                basePoints0 = 11;
                GetCaster()->CastCustomSpell(GetCaster(), SPELL_HUNTER_STEADY_SHOT_ENERGIZE, &basePoints0, NULL, NULL, true, NULL, NULL, GetCaster()->GetGUID());
            }
            else
                GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_STEADY_SHOT_ENERGIZE, true);
        }

    private:
        int32 basePoints0;

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_steady_shot_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
            OnEffectLaunchTarget += SpellEffectFn(spell_hun_steady_shot_SpellScript::HandleFocusRegen, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_steady_shot_SpellScript();
    }
};

// 82692 Focus Fire
class spell_hun_focus_fire : public SpellScriptLoader
{
public:
    spell_hun_focus_fire() : SpellScriptLoader("spell_hun_focus_fire") { }

    // SpellScript
    class spell_hun_focus_fire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_focus_fire_SpellScript)

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_FOCUS_FIRE))
                return false;
            return true;
        }

        SpellCastResult CheckFrenzyStack()
        {
            Unit * pet = GetCaster()->GetGuardianPet();
            if (!pet)
                return SPELL_FAILED_NO_PET;

            if (pet->HasAura(HUNTER_PET_SPELL_FRENZY))
                return SPELL_CAST_OK;
            else
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        }

        void RemoveFrenzyStacks()
        {
            if (Unit* pet = GetCaster()->GetGuardianPet())
                pet->RemoveAura(HUNTER_PET_SPELL_FRENZY);
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_hun_focus_fire_SpellScript::CheckFrenzyStack);
            AfterHit += SpellHitFn(spell_hun_focus_fire_SpellScript::RemoveFrenzyStacks);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_focus_fire_SpellScript();
    }

    // AuraScript
    class spell_hun_focus_fire_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_focus_fire_AuraScript);

        uint32 GetFrenzyStackCount()
        {
            if (Unit* pet = GetUnitOwner()->GetGuardianPet())
            {
                if (pet->HasAura(HUNTER_PET_SPELL_FRENZY))
                    return pet->GetAuraCount(HUNTER_PET_SPELL_FRENZY);
                else
                    return 0;
            }
            return 0;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            if (Unit* caster = GetUnitOwner())
                amount = GetSpellInfo()->Effects[0].BasePoints * GetFrenzyStackCount();
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetUnitOwner())
            {
                if (Unit* pet = caster->GetGuardianPet())
                {
                    int32 basepoint0 = GetAura()->GetEffect(1)->GetAmount() * GetFrenzyStackCount();
                    caster->CastCustomSpell(pet, HUNTER_PET_SPELL_FOCUS_FIRE_REGEN, &basepoint0, NULL, NULL, true);
                }
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_focus_fire_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_RANGED_HASTE);
            OnEffectApply += AuraEffectApplyFn(spell_hun_focus_fire_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_focus_fire_AuraScript();
    }
};

// 19615 Frenzy Effect
class spell_hun_frenzy_effect : public SpellScriptLoader
{
public:
    spell_hun_frenzy_effect() : SpellScriptLoader("spell_hun_frenzy_effect") { }

    class spell_hun_frenzy_effect_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_frenzy_effect_AuraScript)

        int32 GetHasteValue()
        {
            if (Unit* pet = GetUnitOwner())
            {
                if (pet->HasAura(HUNTER_PET_AURA_FRENZY_TRIGGER))
                {
                    if (Aura* frenzyAura = pet->GetAura(HUNTER_PET_AURA_FRENZY_TRIGGER))
                        return frenzyAura->GetEffect(0)->GetAmount();
                }
                else
                    return 0;
            }
            return 0;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            if (Unit* pet = GetUnitOwner())
            {
                Unit* petOwner = pet->GetOwner();
                if (!petOwner)
                    return;

                amount = GetHasteValue();
            }
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            // Apply UI Visual when at 5 stack
            if (Unit* petOwner = GetUnitOwner()->GetOwner())
            {
                if (GetStackAmount() >= GetSpellInfo()->StackAmount)
                    petOwner->AddAura(HUNTER_VISUAL_FOCUS_FIRE, petOwner);
            }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* pet = GetUnitOwner())
            {
                if (Unit * petOwner = pet->GetOwner())
                    petOwner->RemoveAura(HUNTER_VISUAL_FOCUS_FIRE);
            }
        }


        void Register()
        {
             AfterEffectApply += AuraEffectApplyFn(spell_hun_frenzy_effect_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_MELEE_HASTE_3, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
             AfterEffectRemove += AuraEffectApplyFn(spell_hun_frenzy_effect_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_MELEE_HASTE_3, AURA_EFFECT_HANDLE_REAL);
             DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_frenzy_effect_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_MELEE_HASTE_3);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_frenzy_effect_AuraScript();
    }
};

// 1978 Serpent Sting
class spell_hun_serpent_sting : public SpellScriptLoader
{
public:
    spell_hun_serpent_sting() : SpellScriptLoader("spell_hun_serpent_sting") { }

    class spell_hun_serpent_sting_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_serpent_sting_AuraScript)

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            if (Unit* target = GetTarget())
            {
                if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_HUNTER, 536, EFFECT_0))
                {
                    int32 bp0 = aurEff->GetAmount() * GetAura()->GetEffect(EFFECT_0)->GetTotalTicks() * caster->SpellDamageBonusDone(target, GetSpellInfo(), GetAura()->GetEffect(EFFECT_0)->GetAmount(), DOT) / 100;
                    caster->CastCustomSpell(target, 83077, &bp0, NULL, NULL, true, NULL, GetAura()->GetEffect(EFFECT_0));
                }
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_hun_serpent_sting_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_serpent_sting_AuraScript();
    }
};

class spell_hunt_wyvern_sting : public SpellScriptLoader
{
    public:
        spell_hunt_wyvern_sting() : SpellScriptLoader("spell_hunt_wyvern_sting") { }

        class spell_hunt_wyvern_sting_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hunt_wyvern_sting_AuraScript);

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_OVERRIDE_CLASS_SCRIPTS, SPELLFAMILY_HUNTER, 3521, 1))
                        caster->CastSpell(dispelInfo->GetDispeller(), 24131, true);
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_hunt_wyvern_sting_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hunt_wyvern_sting_AuraScript();
        }
};

class spell_hun_target_only_pet_and_owner : public SpellScriptLoader
{
    public:
        spell_hun_target_only_pet_and_owner() : SpellScriptLoader("spell_hun_target_only_pet_and_owner") { }

        class spell_hun_target_only_pet_and_owner_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_target_only_pet_and_owner_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.clear();
                targets.push_back(GetCaster());
                if (Unit* owner = GetCaster()->GetOwner())
                    targets.push_back(owner);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_target_only_pet_and_owner_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_target_only_pet_and_owner_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_target_only_pet_and_owner_SpellScript();
        }
};

class spell_hun_trap_launcher_trap : public SpellScriptLoader
{
    public:
        spell_hun_trap_launcher_trap() : SpellScriptLoader("spell_hun_trap_launcher_trap") { }

        class spell_hun_trap_launcher_trap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_trap_launcher_trap_SpellScript);

            void HandleDummy()
            {
               if(Unit* caster = GetCaster())
               {
                   caster->RemoveAurasDueToSpell(77769);
                   caster->RemoveAurasDueToSpell(82946);
               }
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_hun_trap_launcher_trap_SpellScript::HandleDummy);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_trap_launcher_trap_SpellScript();
        }
};

// 76838 - wild quiver
class spell_hun_wild_quiver : public SpellScriptLoader
{
    public:
       spell_hun_wild_quiver() : SpellScriptLoader("spell_hun_wild_quiver") { }

       class spell_hun_wild_quiver_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_hun_wild_quiver_AuraScript);

           enum effectWildQuiver
           {
                SPELL_WILD_QUIVER_TRIGGERED = 76663
           };

           void HandleProc(AuraEffect const* aurEff, ProcEventInfo &procInfo)
           {
               // aurEff->GetAmount() % Chance to proc the event ...
               if (urand(0,99) >= uint32(aurEff->GetAmount()))
                   return;

               Unit *caster = GetCaster();
               Unit *target = procInfo.GetActionTarget();

               // Cast only for Hunters that have Wild Quiver mastery active
               if (!caster->HasAura(76659))
                   return;

               if (caster && target)
                   caster->CastSpell(target, SPELL_WILD_QUIVER_TRIGGERED, true, NULL, aurEff);
           }

           void Register()
           {
                OnEffectProc += AuraEffectProcFn(spell_hun_wild_quiver_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_hun_wild_quiver_AuraScript();
       }
};

// 34485, 34486, 34487 - Master Marksman
class spell_hun_master_marksman : public SpellScriptLoader
{
    public:
        spell_hun_master_marksman() : SpellScriptLoader("spell_hun_master_marksman") { }

        class spell_hun_master_marksman_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_master_marksman_AuraScript);

            enum effectsMarksman
            {
                SPELL_STEADY_SHOT   = 56641,
                AURA_READY_SET_AIM  = 82925,
                AURA_FIRE           = 82926
            };

            bool CheckProc(ProcEventInfo &procInfo)
            {
                if (DamageInfo *damageInfo = procInfo.GetDamageInfo())
                    if (const SpellInfo *spellInfo = damageInfo->GetSpellInfo())
                        return (spellInfo->Id == SPELL_STEADY_SHOT);

                return false;
            }

            void AfterProc(AuraEffect const* /*aurEff*/, ProcEventInfo &/*procInfo*/)
            {
                if (Unit *caster = GetCaster())
                {
                    if (Aura *aura = caster->GetAura(AURA_READY_SET_AIM))
                    {
                        if (aura->GetStackAmount() >= 5)
                        {
                            caster->CastSpell(caster, AURA_FIRE, true);
                            caster->RemoveAura(AURA_READY_SET_AIM);
                        }
                    }
                }
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_hun_master_marksman_AuraScript::CheckProc);
                AfterEffectProc += AuraEffectProcFn(spell_hun_master_marksman_AuraScript::AfterProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_master_marksman_AuraScript();
        }
};

// 82926 - Fire!
class spell_hun_fire : public SpellScriptLoader
{
    public:
        spell_hun_fire() : SpellScriptLoader("spell_hun_fire") { }

        class spell_hun_fire_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_fire_AuraScript);

            enum effectAimedShot
            {
                SPELL_AIMED_SHOT_MASTER_MARKSMAN    = 82928
            };

            bool CheckProc(ProcEventInfo &procInfo)
            {
                if (DamageInfo *damageInfo = procInfo.GetDamageInfo())
                    if (const SpellInfo *spellInfo = damageInfo->GetSpellInfo())
                        return (spellInfo->Id == SPELL_AIMED_SHOT_MASTER_MARKSMAN);

                return false;
            }

            void CalcSpellMod(AuraEffect const* aurEff, SpellModifier* &modInfo)
            {
                modInfo = new SpellModifier(aurEff->GetBase());
                modInfo->spellId = SPELL_AIMED_SHOT_MASTER_MARKSMAN;
                modInfo->value = -1000;
                modInfo->op = SPELLMOD_CASTING_TIME;
                modInfo->type = SPELLMOD_PCT;
                modInfo->mask[0] = 0x00020000;
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_hun_fire_AuraScript::CheckProc);
                DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_hun_fire_AuraScript::CalcSpellMod, EFFECT_1, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS_2);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_fire_AuraScript();
        }
};

// 35104, 35110 - Bombardement
class spell_hun_bombardement : public SpellScriptLoader
{
    public:
        spell_hun_bombardement() : SpellScriptLoader("spell_hun_bombardement") { }

        class spell_hun_bombardement_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_bombardement_AuraScript);

            enum effectMultishot
            {
                SPELL_MULTISHOT = 2643
            };

            bool CheckProc(ProcEventInfo &procInfo)
            {
                if (DamageInfo *damageInfo = procInfo.GetDamageInfo())
                    if (const SpellInfo *spellInfo = damageInfo->GetSpellInfo())
                        if (spellInfo->Id == SPELL_MULTISHOT)
                            return PROC_EX_CRITICAL_HIT == (procInfo.GetHitMask() & PROC_EX_CRITICAL_HIT);

                return false;
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_hun_bombardement_AuraScript::CheckProc);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_bombardement_AuraScript();
        }
};

// 53241, 53243 - Marked For Death
class spell_hun_marked_for_death : public SpellScriptLoader
{
    public:
        spell_hun_marked_for_death() : SpellScriptLoader("spell_hun_marked_for_death") { }

        class spell_hun_marked_for_death_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_marked_for_death_AuraScript);

            enum effectsMarkedForDeath
            {
                SPELL_ARCANE_SHOT           = 3044,
                SPELL_CHIMERA_SHOT          = 53209,
                AURA_MARKED_FOR_DEATH       = 88691
            };

            bool CheckProc(ProcEventInfo &procInfo)
            {
                if (DamageInfo *damageInfo = procInfo.GetDamageInfo())
                    if (const SpellInfo *spellInfo = damageInfo->GetSpellInfo())
                        return (spellInfo->Id == SPELL_ARCANE_SHOT || spellInfo->Id == SPELL_CHIMERA_SHOT);

                return false;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo &procInfo)
            {
                if (!aurEff)
                    return;

                Unit *caster = GetCaster();

                if (!caster)
                    return;

                if (irand(0, 99) < aurEff->GetAmount())
                    caster->CastSpell(procInfo.GetActionTarget(), AURA_MARKED_FOR_DEATH, true);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_hun_marked_for_death_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_hun_marked_for_death_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_marked_for_death_AuraScript();
        }
};

// 53351 Kill Shot
class spell_hun_kill_shot: public SpellScriptLoader
{
    public:
        spell_hun_kill_shot() : SpellScriptLoader("spell_hun_kill_shot") { }

        class spell_hun_kill_shot_SpellScript: public SpellScript
        {
            PrepareSpellScript(spell_hun_kill_shot_SpellScript)

            void HandleGlyphEffect(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!caster && !target)
                    return;

                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                // Glyph of Kill Shot
                if (caster->HasAura(63067) && target->isAlive())
                {
                    if (!caster->ToPlayer()->HasSpellCooldown(90967))
                    {
                        if (GetHitDamage() < int32(target->GetHealth()))
                        {
                            caster->ToPlayer()->RemoveSpellCooldown(53351, true);
                            caster->CastSpell(caster, 90967, true);
                            caster->ToPlayer()->AddSpellCooldown(90967, 0, time(NULL) + 6);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_kill_shot_SpellScript::HandleGlyphEffect, EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_kill_shot_SpellScript();
        }
};

// 3355 - Freezing Trap
class spell_hun_freezing_trap : public SpellScriptLoader
{
    public:
        spell_hun_freezing_trap() : SpellScriptLoader("spell_hun_freezing_trap") { }

        class spell_hun_freezing_trap_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_freezing_trap_AuraScript);

            enum Spells
            {
                SPELL_HUN_FREEZING_TRAP                 = 3355,
                SPELL_HUN_GLYPH_OF_FREEZING_TRAP        = 56845,
                SPELL_HUN_GLYPH_OF_FREEZING_TRAP_TRIG   = 61394
            };

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        // Glyph of Freezing Trap
                        if (caster->HasAura(SPELL_HUN_GLYPH_OF_FREEZING_TRAP))
                            caster->CastSpell(target, SPELL_HUN_GLYPH_OF_FREEZING_TRAP_TRIG, true);
                    }
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_hun_freezing_trap_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_freezing_trap_AuraScript();
        }
};

// 34490 Silencing Shot
class spell_hun_silencing_shot: public SpellScriptLoader
{
    public:
        spell_hun_silencing_shot() : SpellScriptLoader("spell_hun_silencing_shot") { }

        class spell_hun_silencing_shot_SpellScript: public SpellScript
        {
            PrepareSpellScript(spell_hun_silencing_shot_SpellScript)

            void HandleGlyphEffect()
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!caster && !target)
                    return;

                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                // Glyph of Silencing Shot
                if (caster->HasAura(SPELL_HUN_GLYPH_OF_SILENCING_SHOT))
                    caster->EnergizeBySpell(caster, SPELL_HUNTER_ENERGIZE, 10, POWER_FOCUS);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_hun_silencing_shot_SpellScript::HandleGlyphEffect);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_silencing_shot_SpellScript();
        }
};

// 34490 Black Arrow
class spell_hun_black_arrow: public SpellScriptLoader
{
    public:
        spell_hun_black_arrow() : SpellScriptLoader("spell_hun_black_arrow") { }

        class spell_hun_black_arrow_SpellScript: public SpellScript
        {
            PrepareSpellScript(spell_hun_black_arrow_SpellScript)

            void HandleSetEffect()
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!caster && !target)
                    return;

                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                // Item - Hunter T11 4P Bonus
                if (caster->HasAura(SPELL_ITEM_HUNTER_T11_4P))
                    caster->CastSpell(target, SPELL_ITEM_HUNTER_T11_4P_TRIGGER, true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_hun_black_arrow_SpellScript::HandleSetEffect);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_black_arrow_SpellScript();
        }
};

// 982 - Revive Pet
class spell_hun_revive_pet : public SpellScriptLoader
{
    public:
        spell_hun_revive_pet() : SpellScriptLoader("spell_hun_revive_pet") { }

        class spell_hun_revive_pet_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_revive_pet_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        Pet* ownerPet = caster->ToPlayer()->GetPet();
                        if (!ownerPet)
                            return SPELL_FAILED_NO_PET;
                        if (ownerPet && ownerPet->isAlive())
                            return SPELL_FAILED_BAD_TARGETS;
                    }
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_hun_revive_pet_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_revive_pet_SpellScript();
        }
};

// 80326 Camouflage
class spell_hun_camouflage: public SpellScriptLoader
{
public:
    spell_hun_camouflage() : SpellScriptLoader("spell_hun_camouflage"){ }

    enum Id
    {
        SPELL_CAMOUFLAGE_STEALTH    = 80325
    };

    class spell_hun_camouflage_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_hun_camouflage_AuraScript)

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            PreventDefaultAction();

            if(Unit * target = GetTarget())
            {
                if (!target->ToPlayer() && !target->ToPet())
                    return;

                if(!target->isMoving())
                {
                    if(!target->HasAura(SPELL_CAMOUFLAGE_STEALTH))
                        target->AddAura(SPELL_CAMOUFLAGE_STEALTH, target);
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_camouflage_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_camouflage_AuraScript();
    }
};

// 1543 - Flare
class spell_hun_flare : public SpellScriptLoader
{
public:
    spell_hun_flare() : SpellScriptLoader("spell_hun_flare") { }

    class spell_hun_flare_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_flare_AuraScript);

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetAuraEffectsByType(SPELL_AURA_MOD_CAMOUFLAGE).size())
                    PreventDefaultAction();
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_hun_flare_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DISPEL_IMMUNITY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };


    AuraScript* GetAuraScript() const
    {
        return new spell_hun_flare_AuraScript();
    }
};

class spell_hun_snake_trap : public SpellScriptLoader
{
    public:
        spell_hun_snake_trap() : SpellScriptLoader("spell_hun_snake_trap") { }

        enum spellId
        {
            SPELL_TALENT_TRAP_MASTERY   = 19376
        };

        class spell_hun_snake_trap_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hun_snake_trap_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect* trapMastery = caster->GetAuraEffectOfRankedSpell(SPELL_TALENT_TRAP_MASTERY, EFFECT_2))
                        amount += (trapMastery->GetAmount());
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_snake_trap_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_ADD_FLAT_MODIFIER);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hun_snake_trap_AuraScript();
        }
};

class spell_hun_lock_and_load : public SpellScriptLoader
{
    public:
        spell_hun_lock_and_load() : SpellScriptLoader("spell_hun_lock_and_load") { }

        enum spellId
        {
            SPELL_HUNTER_EXPLOSIVE_SHOT     = 53301
        };

        class spell_hun_lock_and_load_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hun_lock_and_load_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    caster->RemoveSpellCooldown(SPELL_HUNTER_EXPLOSIVE_SHOT, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hun_lock_and_load_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hun_lock_and_load_SpellScript();
        }
};

class spell_hun_attack_basic : public SpellScriptLoader
{
public:
    spell_hun_attack_basic() : SpellScriptLoader("spell_hun_attack_basic")
    {
    }

    class spell_hun_attack_basic_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_attack_basic_SpellScript);

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster())
            {
                // Wild Hunt (Damage Increasing)
                if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PET, 3748, EFFECT_0))
                {
                    int32 damageIncreased = GetHitDamage() * aurEff->GetAmount() / 100;
                    SetHitDamage(GetHitDamage() + damageIncreased);
                }
            }
        }

        void HandleDummyEffect()
        {
            if (Unit* caster = GetCaster())
            {
                // Wild Hunt (Cost Increasing)
                if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PET, 3748, EFFECT_1))
                {
                    if (SpellInfo const* spellProto = GetSpellInfo())
                    {
                        if (caster->GetPower(POWER_FOCUS) + spellProto->CalcPowerCost(caster, spellProto->GetSchoolMask()) >= 50)
                            caster->SetPower(POWER_FOCUS, caster->GetPower(POWER_FOCUS) - spellProto->CalcPowerCost(caster, spellProto->GetSchoolMask()));
                    }
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_hun_attack_basic_SpellScript::HandleDummyEffect);
            OnHit += SpellHitFn(spell_hun_attack_basic_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_attack_basic_SpellScript();
    }
};

void AddSC_hunter_spell_scripts()
{
    new spell_hun_aspect_of_the_beast();
    new spell_hun_ascpect_of_the_viper();
    new spell_hun_disengage();
    new spell_hun_invigoration();
    new spell_hun_last_stand_pet();
    new spell_hun_masters_call();
    new spell_hun_misdirection();
    new spell_hun_misdirection_proc();
    new spell_hun_pet_carrion_feeder();
    new spell_hun_pet_heart_of_the_phoenix();
    new spell_hun_readiness();
    new spell_hun_scatter_shot();
    new spell_hun_sniper_training();
    new spell_hun_tame_beast();
    new spell_hun_cobra_shot();
    new spell_hun_steady_shot();
    new spell_hun_kill_command();
    new spell_hun_focus_fire();
    new spell_hun_frenzy_effect();
    new spell_hun_serpent_sting();
    new spell_hun_target_only_pet_and_owner();
    new spell_hun_trap_launcher_trap();
    new spell_hunt_wyvern_sting();
    new spell_hun_wild_quiver();
    new spell_hun_fire();
    new spell_hun_marked_for_death();
    new spell_hun_bombardement();
    new spell_hun_master_marksman();
    new spell_hun_kill_shot();
    new spell_hun_freezing_trap();
    new spell_hun_silencing_shot();
    new spell_hun_black_arrow();
    new spell_hun_revive_pet();
    new spell_hun_camouflage();
    new spell_hun_flare();
    new spell_hun_snake_trap();
    new spell_hun_lock_and_load();
    new spell_hun_attack_basic();
}
