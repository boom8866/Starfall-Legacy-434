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
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"

enum WarlockSpells
{
    SPELL_WARLOCK_BANE_OF_DOOM_EFFECT               = 18662,
    SPELL_WARLOCK_CURSE_OF_DOOM_EFFECT              = 18662,
    SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST         = 62388,
    SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON             = 48018,
    SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT           = 48020,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD      = 54508,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER     = 54509,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP           = 54444,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS      = 54435,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER    = 54443,
    SPELL_WARLOCK_DEMON_SOUL_IMP                    = 79459,
    SPELL_WARLOCK_DEMON_SOUL_FELHUNTER              = 79460,
    SPELL_WARLOCK_DEMON_SOUL_FELGUARD               = 79462,
    SPELL_WARLOCK_DEMON_SOUL_SUCCUBUS               = 79463,
    SPELL_WARLOCK_DEMON_SOUL_VOIDWALKER             = 79464,
    SPELL_WARLOCK_FEL_SYNERGY_HEAL                  = 54181,
    SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE              = 63106,
    SPELL_WARLOCK_HAUNT                             = 48181,
    SPELL_WARLOCK_HAUNT_HEAL                        = 48210,
    SPELL_WARLOCK_IMMOLATE                          = 348,
    SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1           = 18692,
    SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2           = 18693,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1    = 60955,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2    = 60956,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1         = 18703,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2         = 18704,
    SPELL_WARLOCK_IMPROVED_SOULFIRE                 = 85383,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE                 = 31818,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2               = 32553,
    SPELL_WARLOCK_SIPHON_LIFE_HEAL                  = 63106,
    SPELL_WARLOCK_SOULSHATTER                       = 32835,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION               = 30108,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL        = 31117,
    SPELL_WARLOCK_SOUL_SWAP_EXHALE                  = 86213,
    SPELL_WARLOCK_SOUL_SWAP_OVERWRITE               = 86211,
    SPELL_WARLOCK_SOUL_SWAP_COOLDOWN_MARKER         = 94229,
    SPELL_WARLOCK_SOUL_SWAP                         = 86121,
    SPELL_WARLOCK_SOUL_SWAP_DUMMY                   = 92795,
    SPELL_WARLOCK_GYLPH_OF_SOUL_SWAP                = 56226,
    SPELL_WARLOCK_TALENT_CREMATION_R1               = 85103,
    SPELL_WARLOCK_TALENT_CREMATION_R2               = 85104,
    SPELL_WARLOCK_CREMATION_EFFECT                  = 89603,
    SPELL_WARLOCK_HAND_OF_GUL_DAN_EFFECT            = 85526,
    SPELL_WARLOCK_SUMMON_HAND_OF_GUL_DAN            = 86041,
    SPELL_WARLOCK_SOUL_LINK_BUFF                    = 25228
};

enum WarlockSpellIcons
{
    WARLOCK_ICON_ID_IMPROVED_LIFE_TAP               = 208,
    WARLOCK_ICON_ID_MANA_FEED                       = 1982,
    WARLOCK_ICON_SOULFIRE                           = 184
};

bool isSoulBurnUsed = false;

// 710 - Banish
/// Updated 4.3.4
class spell_warl_banish : public SpellScriptLoader
{
    public:
        spell_warl_banish() : SpellScriptLoader("spell_warl_banish") { }

        enum spellId
        {
            SPELL_BANISH    = 710
        };

        class spell_warl_banish_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_banish_SpellScript);

            bool Load()
            {
                _removed = false;
                return true;
            }

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->HasAura(SPELL_BANISH))
                            return SPELL_FAILED_ALREADY_HAVE_CHARM;
                    }
                }
                return SPELL_CAST_OK;
            }

            void HandleBanish()
            {
                /// Casting Banish on a banished target will cancel the effect
                /// Check if the target already has Banish, if so, do nothing.
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetAuraEffect(SPELL_AURA_SCHOOL_IMMUNITY, SPELLFAMILY_WARLOCK, 0, 0x08000000, 0))
                    {
                        // No need to remove old aura since its removed due to not stack by current Banish aura
                        PreventHitDefaultEffect(EFFECT_0);
                        PreventHitDefaultEffect(EFFECT_1);
                        PreventHitDefaultEffect(EFFECT_2);
                        _removed = true;
                    }
                }
            }

            void RemoveAura()
            {
                if (_removed)
                    PreventHitAura();
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_banish_SpellScript::CheckCast);
                BeforeHit += SpellHitFn(spell_warl_banish_SpellScript::HandleBanish);
                AfterHit += SpellHitFn(spell_warl_banish_SpellScript::RemoveAura);
            }

            bool _removed;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_banish_SpellScript();
        }
};

// 17962 - Conflagrate - Updated to 4.3.4
class spell_warl_conflagrate : public SpellScriptLoader
{
    public:
        spell_warl_conflagrate() : SpellScriptLoader("spell_warl_conflagrate") { }

        class spell_warl_conflagrate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_conflagrate_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_IMMOLATE))
                    return false;
                return true;
            }

            void HandleHit(SpellEffIndex /*effIndex*/)
            {
                if (AuraEffect const* aurEff = GetHitUnit()->GetAuraEffect(SPELL_WARLOCK_IMMOLATE, EFFECT_2, GetCaster()->GetGUID()))
                    SetHitDamage(CalculatePct(GetCaster()->SpellDamageBonusDone(GetHitUnit(), aurEff->GetSpellInfo(), aurEff->GetAmount(), DOT) * aurEff->GetTotalTicks(), GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster())));

                if (Unit* target = GetHitUnit())
                {
                    Unit::AuraEffectList const& dmgPercentTaken = target->GetAuraEffectsByType(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
                    for (Unit::AuraEffectList::const_iterator itr = dmgPercentTaken.begin(); itr != dmgPercentTaken.end(); ++itr)
                    {
                        if ((*itr)->GetMiscValue() & SPELL_SCHOOL_MASK_FIRE)
                            SetHitDamage(GetHitDamage() + (GetHitDamage() * (*itr)->GetAmount() / 100));
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_conflagrate_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_conflagrate_SpellScript();
        }
};

// 6201 - Create Healthstone
class spell_warl_create_healthstone : public SpellScriptLoader
{
    public:
        spell_warl_create_healthstone() : SpellScriptLoader("spell_warl_create_healthstone") { }

        class spell_warl_create_healthstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_create_healthstone_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Player* caster = GetCaster()->ToPlayer())
                {
                    uint8 spellRank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);
                    ItemPosCountVec dest;
                    InventoryResult msg = caster->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 5512, 1, NULL);
                    if (msg != EQUIP_ERR_OK)
                        return SPELL_FAILED_TOO_MANY_OF_ITEM;
                }
                return SPELL_CAST_OK;
            }

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                CreateItem(effIndex, 5512);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_create_healthstone_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnCheckCast += SpellCheckCastFn(spell_warl_create_healthstone_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_create_healthstone_SpellScript();
        }
};

// 603 - Bane of Doom
/// Updated 4.3.4
class spell_warl_bane_of_doom : public SpellScriptLoader
{
    public:
        spell_warl_bane_of_doom() : SpellScriptLoader("spell_warl_bane_of_doom") { }

        class spell_warl_bane_of_doom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_bane_of_doom_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_BANE_OF_DOOM_EFFECT))
                    return false;
                return true;
            }

            bool Load()
            {
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_DEATH || !IsExpired())
                    return;

                if (GetCaster()->ToPlayer()->isHonorOrXPTarget(GetTarget()))
                    GetCaster()->CastSpell(GetTarget(), SPELL_WARLOCK_BANE_OF_DOOM_EFFECT, true, NULL, aurEff);
            }

            void Register()
            {
                 AfterEffectRemove += AuraEffectRemoveFn(spell_warl_bane_of_doom_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_bane_of_doom_AuraScript();
        }
};

// 48018 - Demonic Circle: Summon
/// Updated 4.3.4
class spell_warl_demonic_circle_summon : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_summon() : SpellScriptLoader("spell_warl_demonic_circle_summon") { }

        class spell_warl_demonic_circle_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_summon_AuraScript);

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
            {
                // If effect is removed by expire remove the summoned demonic circle too.
                if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
                    GetTarget()->RemoveGameObject(GetId(), true);

                GetTarget()->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
            }

            void HandleDummyTick(AuraEffect const* /*aurEff*/)
            {
                if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
                {
                    // Here we check if player is in demonic circle teleport range, if so add
                    // WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the WARLOCK_DEMONIC_CIRCLE_TELEPORT.
                    // If not in range remove the WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST.

                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT);

                    if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
                    {
                        if (!GetTarget()->HasAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST))
                            GetTarget()->CastSpell(GetTarget(), SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
                    }
                    else
                        GetTarget()->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_demonic_circle_summon_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_summon_AuraScript();
        }
};

// 48020 - Demonic Circle: Teleport
/// Updated 4.3.4
class spell_warl_demonic_circle_teleport : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_teleport() : SpellScriptLoader("spell_warl_demonic_circle_teleport") { }

        class spell_warl_demonic_circle_teleport_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_teleport_AuraScript);

            void HandleTeleport(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* player = GetTarget()->ToPlayer())
                {
                    if (GameObject* circle = player->GetGameObject(SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON))
                    {
                        player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                        player->RemoveMovementImpairingAuras();
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport_AuraScript::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_teleport_AuraScript();
        }
};

// 77801 - Demon Soul - Updated to 4.3.4
class spell_warl_demon_soul : public SpellScriptLoader
{
    public:
        spell_warl_demon_soul() : SpellScriptLoader("spell_warl_demon_soul") { }

        class spell_warl_demon_soul_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demon_soul_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMON_SOUL_IMP))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMON_SOUL_FELHUNTER))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMON_SOUL_FELGUARD))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMON_SOUL_SUCCUBUS))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMON_SOUL_VOIDWALKER))
                    return false;
                return true;
            }

            void OnHitTarget(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Creature* targetCreature = GetHitCreature())
                {
                    if (targetCreature->isPet())
                    {
                        CreatureTemplate const* ci = sObjectMgr->GetCreatureTemplate(targetCreature->GetEntry());
                        switch (ci->family)
                        {
                            case CREATURE_FAMILY_SUCCUBUS:
                                caster->CastSpell(caster, SPELL_WARLOCK_DEMON_SOUL_SUCCUBUS);
                                break;
                            case CREATURE_FAMILY_VOIDWALKER:
                                caster->CastSpell(caster, SPELL_WARLOCK_DEMON_SOUL_VOIDWALKER);
                                break;
                            case CREATURE_FAMILY_FELGUARD:
                                caster->CastSpell(caster, SPELL_WARLOCK_DEMON_SOUL_FELGUARD);
                                break;
                            case CREATURE_FAMILY_FELHUNTER:
                                caster->CastSpell(caster, SPELL_WARLOCK_DEMON_SOUL_FELHUNTER);
                                break;
                            case CREATURE_FAMILY_IMP:
                                caster->CastSpell(caster, SPELL_WARLOCK_DEMON_SOUL_IMP);
                                break;
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_demon_soul_SpellScript::OnHitTarget, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demon_soul_SpellScript;
        }
};

// 47193 - Demonic Empowerment
/// Updated 4.3.4
class spell_warl_demonic_empowerment : public SpellScriptLoader
{
    public:
        spell_warl_demonic_empowerment() : SpellScriptLoader("spell_warl_demonic_empowerment") { }

        class spell_warl_demonic_empowerment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_empowerment_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Creature* targetCreature = GetHitCreature())
                {
                    if (targetCreature->isPet())
                    {
                        CreatureTemplate const* ci = sObjectMgr->GetCreatureTemplate(targetCreature->GetEntry());
                        switch (ci->family)
                        {
                            case CREATURE_FAMILY_SUCCUBUS:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS, true);
                                break;
                            case CREATURE_FAMILY_VOIDWALKER:
                            {
                                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER);
                                int32 hp = int32(targetCreature->CountPctFromMaxHealth(GetCaster()->CalculateSpellDamage(targetCreature, spellInfo, 0)));
                                targetCreature->CastCustomSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER, &hp, NULL, NULL, true);
                                break;
                            }
                            case CREATURE_FAMILY_FELGUARD:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD, true);
                                break;
                            case CREATURE_FAMILY_FELHUNTER:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER, true);
                                break;
                            case CREATURE_FAMILY_IMP:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP, true);
                                break;
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_demonic_empowerment_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_empowerment_SpellScript();
        }
};

// 47422 - Everlasting Affliction
/// Updated 4.3.4
class spell_warl_everlasting_affliction : public SpellScriptLoader
{
    public:
        spell_warl_everlasting_affliction() : SpellScriptLoader("spell_warl_everlasting_affliction") { }

        class spell_warl_everlasting_affliction_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_everlasting_affliction_SpellScript);

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                    // Refresh corruption on target
                    if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_WARLOCK, 0x2, 0, 0, GetCaster()->GetGUID()))
                        aur->GetBase()->RefreshDuration();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_everlasting_affliction_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_everlasting_affliction_SpellScript();
        }
};

// 77799 - Fel Flame - Updated to 4.3.4
class spell_warl_fel_flame : public SpellScriptLoader
{
    public:
        spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") { }

        class spell_warl_fel_flame_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fel_flame_SpellScript);

            void OnHitTarget(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();
                Aura* aura = target->GetAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION, caster->GetGUID());
                if (!aura)
                    aura = target->GetAura(SPELL_WARLOCK_IMMOLATE, caster->GetGUID());

                if (!aura)
                    return;

                int32 newDuration = aura->GetDuration() + GetSpellInfo()->Effects[EFFECT_1].CalcValue() * 1000;
                aura->SetDuration(std::min(newDuration, aura->GetMaxDuration()));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_fel_flame_SpellScript::OnHitTarget, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fel_flame_SpellScript;
        }
};

// -47230 - Fel Synergy
class spell_warl_fel_synergy : public SpellScriptLoader
{
    public:
        spell_warl_fel_synergy() : SpellScriptLoader("spell_warl_fel_synergy") { }

        class spell_warl_fel_synergy_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_fel_synergy_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_FEL_SYNERGY_HEAL))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return GetTarget()->GetGuardianPet() && eventInfo.GetDamageInfo()->GetDamage();
            }

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                int32 heal = CalculatePct(int32(eventInfo.GetDamageInfo()->GetDamage()), aurEff->GetAmount());
                GetTarget()->CastCustomSpell(SPELL_WARLOCK_FEL_SYNERGY_HEAL, SPELLVALUE_BASE_POINT0, heal, (Unit*)NULL, true, NULL, aurEff); // TARGET_UNIT_PET
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_warl_fel_synergy_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warl_fel_synergy_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_fel_synergy_AuraScript();
        }
};

// 48181 - Haunt
/// Updated 4.3.4
class spell_warl_haunt : public SpellScriptLoader
{
    public:
        spell_warl_haunt() : SpellScriptLoader("spell_warl_haunt") { }

        class spell_warl_haunt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_haunt_SpellScript);

            void HandleAfterHit()
            {
                if (Aura* aura = GetHitAura())
                    if (AuraEffect* aurEff = aura->GetEffect(EFFECT_1))
                        aurEff->SetAmount(CalculatePct(aurEff->GetAmount(), GetHitDamage()));
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_haunt_SpellScript::HandleAfterHit);
            }
        };

        class spell_warl_haunt_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_haunt_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_HAUNT_HEAL))
                    return false;
                return true;
            }

            void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 amount = aurEff->GetAmount();
                    GetTarget()->CastCustomSpell(caster, SPELL_WARLOCK_HAUNT_HEAL, &amount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectApplyFn(spell_warl_haunt_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_haunt_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_haunt_AuraScript();
        }
};

// 755 - Health Funnel
/// Updated 4.3.4
class spell_warl_health_funnel : public SpellScriptLoader
{
    public:
        spell_warl_health_funnel() : SpellScriptLoader("spell_warl_health_funnel") { }

        class spell_warl_health_funnel_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_health_funnel_AuraScript);

            void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                Unit* target = GetTarget();
                if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2))
                    target->CastSpell(target, SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2, true);
                else if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1))
                    target->CastSpell(target, SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1, true);
            }

            void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1);
                target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_health_funnel_AuraScript::RemoveEffect, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
                OnEffectApply += AuraEffectApplyFn(spell_warl_health_funnel_AuraScript::ApplyEffect, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_health_funnel_AuraScript();
        }
};

// 1454 - Life Tap
/// Updated 4.3.4
class spell_warl_life_tap : public SpellScriptLoader
{
    public:
        spell_warl_life_tap() : SpellScriptLoader("spell_warl_life_tap") { }

        class spell_warl_life_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_life_tap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_LIFE_TAP_ENERGIZE) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                if (Unit* target = GetHitUnit())
                {
                    int32 damage = caster->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue());
                    int32 mana = CalculatePct(damage, GetSpellInfo()->Effects[EFFECT_1].CalcValue());

                    // Shouldn't Appear in Combat Log
                    target->ModifyHealth(-damage);

                    // Improved Life Tap mod
                    if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, WARLOCK_ICON_ID_IMPROVED_LIFE_TAP, 0))
                        AddPct(mana, aurEff->GetAmount());

                    caster->CastCustomSpell(target, SPELL_WARLOCK_LIFE_TAP_ENERGIZE, &mana, NULL, NULL, false);

                    // Mana Feed
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, WARLOCK_ICON_ID_MANA_FEED, 0))
                    {
                        int32 manaFeedVal = aurEff->GetAmount();
                        ApplyPct(manaFeedVal, mana);
                        caster->CastCustomSpell(caster, SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2, &manaFeedVal, NULL, NULL, true, NULL);
                    }
                }
            }

            SpellCastResult CheckCast()
            {
                if (int32(GetCaster()->GetHealth()) > int32(GetCaster()->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue())))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_FIZZLE;
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_life_tap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_warl_life_tap_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_life_tap_SpellScript();
        }
};

// 18541 - Ritual of Doom Effect
class spell_warl_ritual_of_doom_effect : public SpellScriptLoader
{
    public:
        spell_warl_ritual_of_doom_effect() : SpellScriptLoader("spell_warl_ritual_of_doom_effect") { }

        class spell_warl_ritual_of_doom_effect_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_ritual_of_doom_effect_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                caster->CastSpell(caster, GetEffectValue(), true);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_warl_ritual_of_doom_effect_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_ritual_of_doom_effect_SpellScript();
        }
};

// 27285 - Seed of Corruption
/// Updated 4.3.4
class spell_warl_seed_of_corruption : public SpellScriptLoader
{
    public:
        spell_warl_seed_of_corruption() : SpellScriptLoader("spell_warl_seed_of_corruption") { }

        enum spellId
        {
            SPELL_WARLOCK_SOULBURN_ENERGIZE     = 87388,
            SPELL_WARLOCK_CORRUPTION            = 172
        };

        class spell_warl_seed_of_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_seed_of_corruption_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                if (Unit* caster = GetCaster())
                {
                    if (isSoulBurnUsed == true)
                    {
                        isSoulBurnUsed = false;
                        caster->CastSpell(caster, SPELL_WARLOCK_SOULBURN_ENERGIZE, true);

                        for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if (*itr)
                                if (Unit* unit = (*itr)->ToUnit())
                                    caster->CastSpell(unit, SPELL_WARLOCK_CORRUPTION, true);
                        }
                    }
                }
                if (GetExplTargetUnit())
                    targets.remove(GetExplTargetUnit());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_seed_of_corruption_SpellScript();
        }
};

// 27243 - Seed of Corruption (Cast)
class spell_warl_seed_of_corruption_cast : public SpellScriptLoader
{
    public:
        spell_warl_seed_of_corruption_cast() : SpellScriptLoader("spell_warl_seed_of_corruption_cast") { }

        class spell_warl_seed_of_corruption_cast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_seed_of_corruption_cast_SpellScript);

            enum spellId
            {
                SPELL_WARLOCK_SOULBURN_EFFECT   = 74434
            };

            void HandleHit(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_WARLOCK_SOULBURN_EFFECT))
                    {
                        isSoulBurnUsed = true;
                        caster->RemoveAurasDueToSpell(SPELL_WARLOCK_SOULBURN_EFFECT);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_seed_of_corruption_cast_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_seed_of_corruption_cast_SpellScript();
        }
};

// 6229/91711 - Shadow Ward/Nether Ward
class spell_warl_shadow_ward : public SpellScriptLoader
{
    public:
        spell_warl_shadow_ward() : SpellScriptLoader("spell_warl_shadow_ward") { }

        class spell_warl_shadow_ward_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_shadow_ward_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    // +0.807% from sp bonus
                    float bonus = 0.807f;

                    bonus *= caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                    bonus *= caster->CalculateLevelPenalty(GetSpellInfo());

                    amount += int32(bonus);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_shadow_ward_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_shadow_ward_AuraScript();
        }
};

// 63108 - Siphon Life
class spell_warl_siphon_life : public SpellScriptLoader
{
    public:
        spell_warl_siphon_life() : SpellScriptLoader("spell_warl_siphon_life") { }

        class spell_warl_siphon_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_siphon_life_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SIPHON_LIFE_HEAL))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return eventInfo.GetDamageInfo()->GetDamage();
            }

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                int32 amount = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()));
                // Glyph of Siphon Life
                if (AuraEffect const* glyph = GetTarget()->GetAuraEffect(SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE, EFFECT_0))
                    AddPct(amount, glyph->GetAmount());

                GetTarget()->CastCustomSpell(SPELL_WARLOCK_SIPHON_LIFE_HEAL, SPELLVALUE_BASE_POINT0, amount, GetTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_warl_siphon_life_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warl_siphon_life_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_siphon_life_AuraScript();
        }
};

// 29858 - Soulshatter
/// Updated 4.3.4
class spell_warl_soulshatter : public SpellScriptLoader
{
    public:
        spell_warl_soulshatter() : SpellScriptLoader("spell_warl_soulshatter") { }

        class spell_warl_soulshatter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulshatter_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOULSHATTER))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                    if (target->CanHaveThreatList() && target->getThreatManager().getThreat(caster) > 0.0f)
                        caster->CastSpell(target, SPELL_WARLOCK_SOULSHATTER, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulshatter_SpellScript();
        }
};

// 30108, 34438, 34439, 35183 - Unstable Affliction
/// Updated 4.3.4
class spell_warl_unstable_affliction : public SpellScriptLoader
{
    public:
        spell_warl_unstable_affliction() : SpellScriptLoader("spell_warl_unstable_affliction") { }

        class spell_warl_unstable_affliction_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_unstable_affliction_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect const* aurEff = GetEffect(EFFECT_1))
                    {
                        int32 damage = aurEff->GetAmount() * 9;
                        // backfire damage and silence
                        caster->CastCustomSpell(dispelInfo->GetDispeller(), SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL, &damage, NULL, NULL, true, NULL, aurEff);
                    }
                }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_warl_unstable_affliction_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_unstable_affliction_AuraScript();
        }
};

// 4.3.4
// Drain Life
class spell_warl_drain_life : public SpellScriptLoader
{
public:
    spell_warl_drain_life() : SpellScriptLoader("spell_warl_drain_life")
    {
    }

    class spell_warl_drain_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_life_AuraScript);

        void OnPeriodic(AuraEffect const* /*aurEff*/)
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return;

            if (!GetCaster()->HasUnitState(UNIT_STATE_CASTING))
                return;

            int32 bp = 0;
            if (GetId() == 689)
                bp = 2; // Normal, restore 2% of health
            else if (GetId() == 89420)
                bp = 5; // Soulburn restore 5% of health

            // Check for Death's Embrace
            if (AuraEffect const* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 3223, EFFECT_0))
            {
                if (GetCaster()->HealthBelowPct(25))
                    bp += int32(aurEff->GetAmount());
            }

            GetCaster()->CastCustomSpell(GetCaster(), 89653, &bp, NULL, NULL, true);
        }

        void OnRemove(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster()->GetTypeId() == TYPEID_PLAYER && GetCaster()->HasAura(74434))
                GetCaster()->RemoveAura(74434);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_drain_life_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_drain_life_AuraScript();
    }
};

// 6353 Soulfire
// Updated 4.3.4
class spell_warl_soulfire : public SpellScriptLoader
{
    public:
        spell_warl_soulfire() : SpellScriptLoader("spell_warl_soulfire") { }

        class spell_warl_soulfire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulfire_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                return sSpellMgr->GetSpellInfo(SPELL_WARLOCK_IMPROVED_SOULFIRE);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, WARLOCK_ICON_SOULFIRE, EFFECT_0))
                    {
                        int32 basepoints = aurEff->GetAmount();
                        caster->CastCustomSpell(caster, SPELL_WARLOCK_IMPROVED_SOULFIRE, &basepoints, NULL, NULL, true);
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soulfire_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulfire_SpellScript();
        }
};

// 86121 Soul Swap
// Updated 4.3.4
class spell_warl_soul_swap : public SpellScriptLoader
{
public:
    spell_warl_soul_swap() : SpellScriptLoader("spell_warl_soul_swap") { }

    class spell_warl_soul_swap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_soul_swap_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_SWAP_EXHALE)
                && sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_SWAP_OVERWRITE)
                && sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_SWAP_COOLDOWN_MARKER);
        }

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* plr = GetCaster())
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    //check for glyph
                    Aura* glyAur = plr->GetAura(SPELL_WARLOCK_GYLPH_OF_SOUL_SWAP);

                    static const AuraType diseaseAuraTypes[] =
                    {
                        SPELL_AURA_PERIODIC_DAMAGE,
                        SPELL_AURA_PERIODIC_DAMAGE_PERCENT,
                        SPELL_AURA_NONE
                    };

                    //visual
                    unitTarget->CastCustomSpell(plr, SPELL_WARLOCK_SOUL_SWAP_DUMMY, NULL, NULL, NULL, true, NULL, NULL, 0);

                    //client spell activation aura
                    unitTarget->AddAura(SPELL_WARLOCK_SOUL_SWAP_OVERWRITE, plr);

                    //clear old
                    plr->soulSwapDots.clear();

                    for (AuraType const* itr = &diseaseAuraTypes[0]; itr && itr[0] != SPELL_AURA_NONE; ++itr)
                    {
                        Unit::AuraEffectList const& auras = unitTarget->GetAuraEffectsByType(*itr);
                        for (Unit::AuraEffectList::const_iterator i = auras.begin(); i != auras.end(); ++i)
                        {
                            // Get auras by caster
                            const SpellInfo* spellinf = (*i)->GetSpellInfo();
                            if (((*i)->GetCasterGUID() == plr->GetGUID()) && (spellinf->SpellFamilyName == SPELLFAMILY_WARLOCK) && (spellinf->GetSchoolMask() & SPELL_SCHOOL_MASK_SHADOW))
                                plr->soulSwapDots.push_back(spellinf->Id);
                        }
                    }

                    if (!glyAur)
                        for (std::list<uint32>::iterator i = plr->soulSwapDots.begin(); i != plr->soulSwapDots.end(); ++i)
                            unitTarget->RemoveAurasDueToSpell(*i);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_soul_swap_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_soul_swap_SpellScript();
    }
};

// 86213 Soul Swap Exhale (Level 85)
// Updated 4.3.4
class spell_warl_soul_swap_exhale : public SpellScriptLoader
{
public:
    spell_warl_soul_swap_exhale() : SpellScriptLoader("spell_warl_soul_swap_exhale") { }

    class spell_warl_soul_swap_exhale_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_soul_swap_exhale_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_SWAP_EXHALE)
                && sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_SWAP_OVERWRITE)
                && sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOUL_SWAP_COOLDOWN_MARKER);
        }

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* plr = GetCaster())
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    Aura* glyAur = plr->GetAura(SPELL_WARLOCK_GYLPH_OF_SOUL_SWAP);

                    for (std::list<uint32>::iterator i = plr->soulSwapDots.begin(); i != plr->soulSwapDots.end(); ++i)
                        plr->AddAura((*i), unitTarget);

                    plr->soulSwapDots.clear();

                    //drop client spell activation aura
                    plr->RemoveAurasDueToSpell(SPELL_WARLOCK_SOUL_SWAP_OVERWRITE);

                    if (glyAur)
                    {
                        if (!plr->ToPlayer()->HasSpellCooldown(SPELL_WARLOCK_SOUL_SWAP))
                            plr->CastSpell(plr, SPELL_WARLOCK_SOUL_SWAP_COOLDOWN_MARKER, TRIGGERED_FULL_MASK);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_soul_swap_exhale_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_soul_swap_exhale_SpellScript();
    }
};


// 71521 - Hand of Gul'Dan
class spell_warl_hand_of_gul_dan : public SpellScriptLoader
{
    public:
        spell_warl_hand_of_gul_dan() : SpellScriptLoader("spell_warl_hand_of_gul_dan") { }

        class spell_warl_hand_of_gul_dan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_hand_of_gul_dan_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleHit(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Cremation effect for Immolate refresh
                        if (caster->HasAura(SPELL_WARLOCK_TALENT_CREMATION_R1) || caster->HasAura(SPELL_WARLOCK_TALENT_CREMATION_R2))
                            caster->CastSpell(target, SPELL_WARLOCK_CREMATION_EFFECT, true);
                        caster->SummonCreature(46157, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 15000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_hand_of_gul_dan_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_hand_of_gul_dan_SpellScript();
        }
};

// 17877 Shadowburn
class spell_warl_shadowburn: public SpellScriptLoader
{
    public:
        spell_warl_shadowburn() : SpellScriptLoader("spell_warl_shadowburn") { }

        class spell_warl_shadowburn_SpellScript: public SpellScript
        {
            PrepareSpellScript(spell_warl_shadowburn_SpellScript)

            void HandleGlyphEffect(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!caster && !target)
                    return;

                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                // Glyph of Shadowburn
                if (caster->HasAura(56229) && target->isAlive())
                {
                    if (!caster->ToPlayer()->HasSpellCooldown(91001))
                    {
                        if (GetHitDamage() < int32(target->GetHealth()))
                        {
                            caster->ToPlayer()->RemoveSpellCooldown(17877, true);
                            caster->CastSpell(caster, 91001, true);
                            caster->ToPlayer()->AddSpellCooldown(91001, 0, time(NULL) + 6);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_shadowburn_SpellScript::HandleGlyphEffect, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_shadowburn_SpellScript();
        }
};

// 19028 Soul Link (Trigger)
class spell_warl_soul_link_trigger: public SpellScriptLoader
{
    public:
        spell_warl_soul_link_trigger() : SpellScriptLoader("spell_warl_soul_link_trigger") { }

        class spell_warl_soul_link_trigger_SpellScript: public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_link_trigger_SpellScript)

            void HandleDummyEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            caster->RemoveAurasDueToSpell(SPELL_WARLOCK_SOUL_LINK_BUFF);
                            target->AddAura(SPELL_WARLOCK_SOUL_LINK_BUFF, target);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soul_link_trigger_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_link_trigger_SpellScript();
        }
};

class spell_warl_hellfire : public SpellScriptLoader
{
public:
    spell_warl_hellfire() : SpellScriptLoader("spell_warl_hellfire")
    {
    }

    class spell_warl_hellfire_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_hellfire_AuraScript);

        enum spellId
        {
            SPELL_TALENT_INFERNO    = 85105
        };

        void HellfireApply(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetTarget())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasSpell(SPELL_TALENT_INFERNO))
                    caster->AddAura(SPELL_TALENT_INFERNO, caster);
            }
        }

        void HellfireRemove(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetTarget())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasAura(SPELL_TALENT_INFERNO))
                    caster->RemoveAurasDueToSpell(SPELL_TALENT_INFERNO);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_hellfire_AuraScript::HellfireApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_hellfire_AuraScript::HellfireRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_hellfire_AuraScript();
    }
};

class CheckCurse
{
public:
    CheckCurse()
    {
    }

    enum spellId
    {
        SPELL_CURSE_OF_THE_ELEMENTS     = 1490
    };

    bool operator()(WorldObject* object)
    {
        return ((object->ToUnit() && object->ToUnit()->HasAura(SPELL_CURSE_OF_THE_ELEMENTS)) || (object->ToPlayer() && object->ToPlayer()->HasAura(SPELL_CURSE_OF_THE_ELEMENTS)));
    }
};

class spell_warl_jinx_filter : public SpellScriptLoader
{
public:
    spell_warl_jinx_filter() : SpellScriptLoader("spell_warl_jinx_filter")
    {
    }

    class spell_warl_jinx_filter_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_jinx_filter_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(CheckCurse());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_jinx_filter_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_jinx_filter_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_jinx_filter_SpellScript();
    }
};

class spell_warl_incinerate : public SpellScriptLoader
{
public:
    spell_warl_incinerate() : SpellScriptLoader("spell_warl_incinerate")
    {
    }

    class spell_warl_incinerate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_incinerate_SpellScript);

        void RecalculateDamage()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            if (GetHitUnit()->HasAura(SPELL_WARLOCK_IMMOLATE, GetCaster()->GetGUID()))
            {
                int32 newDamage = GetHitDamage() + int32(GetHitDamage() / 6);
                SetHitDamage(newDamage);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_incinerate_SpellScript::RecalculateDamage);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_incinerate_SpellScript();
    }
};

void AddSC_warlock_spell_scripts()
{
    new spell_warl_bane_of_doom();
    new spell_warl_banish();
    new spell_warl_conflagrate();
    new spell_warl_create_healthstone();
    new spell_warl_demonic_circle_summon();
    new spell_warl_demonic_circle_teleport();
    new spell_warl_demonic_empowerment();
    new spell_warl_demon_soul();
    new spell_warl_everlasting_affliction();
    new spell_warl_fel_flame();
    new spell_warl_fel_synergy();
    new spell_warl_haunt();
    new spell_warl_health_funnel();
    new spell_warl_life_tap();
    new spell_warl_ritual_of_doom_effect();
    new spell_warl_seed_of_corruption();
    new spell_warl_seed_of_corruption_cast();
    new spell_warl_shadow_ward();
    new spell_warl_siphon_life();
    new spell_warl_soulshatter();
    new spell_warl_unstable_affliction();
    new spell_warl_drain_life();
    new spell_warl_soulfire();
    new spell_warl_soul_swap();
    new spell_warl_soul_swap_exhale();
    new spell_warl_hand_of_gul_dan();
    new spell_warl_shadowburn();
    new spell_warl_soul_link_trigger();
    new spell_warl_hellfire();
    new spell_warl_jinx_filter();
    new spell_warl_incinerate();
}
