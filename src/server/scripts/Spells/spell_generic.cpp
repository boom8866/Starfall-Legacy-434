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
 * Scripts for spells with SPELLFAMILY_GENERIC which cannot be included in AI script file
 * of creature using it or can't be bound to any player class.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_gen_"
 */

#include "ScriptMgr.h"
#include "Battleground.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "InstanceScript.h"
#include "LFGMgr.h"
#include "Pet.h"
#include "ReputationMgr.h"
#include "SkillDiscovery.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Group.h"

class spell_gen_absorb0_hitlimit1 : public SpellScriptLoader
{
    public:
        spell_gen_absorb0_hitlimit1() : SpellScriptLoader("spell_gen_absorb0_hitlimit1") { }

        class spell_gen_absorb0_hitlimit1_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_absorb0_hitlimit1_AuraScript);

            uint32 limit;

            bool Load()
            {
                // Max absorb stored in 1 dummy effect
                limit = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
                return true;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
            {
                absorbAmount = std::min(limit, absorbAmount);
            }

            void Register()
            {
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_gen_absorb0_hitlimit1_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_absorb0_hitlimit1_AuraScript();
        }
};

// 28764 - Adaptive Warding (Frostfire Regalia Set)
enum AdaptiveWarding
{
    SPELL_GEN_ADAPTIVE_WARDING_FIRE     = 28765,
    SPELL_GEN_ADAPTIVE_WARDING_NATURE   = 28768,
    SPELL_GEN_ADAPTIVE_WARDING_FROST    = 28766,
    SPELL_GEN_ADAPTIVE_WARDING_SHADOW   = 28769,
    SPELL_GEN_ADAPTIVE_WARDING_ARCANE   = 28770
};

class spell_gen_adaptive_warding : public SpellScriptLoader
{
    public:
        spell_gen_adaptive_warding() : SpellScriptLoader("spell_gen_adaptive_warding") { }

        class spell_gen_adaptive_warding_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_adaptive_warding_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_GEN_ADAPTIVE_WARDING_FIRE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_ADAPTIVE_WARDING_NATURE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_ADAPTIVE_WARDING_FROST) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_ADAPTIVE_WARDING_SHADOW) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_ADAPTIVE_WARDING_ARCANE))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                if (eventInfo.GetDamageInfo()->GetSpellInfo()) // eventInfo.GetSpellInfo()
                    return false;

                // find Mage Armor
                if (!GetTarget()->GetAuraEffect(SPELL_AURA_MOD_MANA_REGEN_INTERRUPT, SPELLFAMILY_MAGE, 0x10000000, 0x0, 0x0))
                    return false;

                switch (GetFirstSchoolInMask(eventInfo.GetSchoolMask()))
                {
                    case SPELL_SCHOOL_NORMAL:
                    case SPELL_SCHOOL_HOLY:
                        return false;
                    default:
                        break;
                }
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                uint32 spellId = 0;
                switch (GetFirstSchoolInMask(eventInfo.GetSchoolMask()))
                {
                    case SPELL_SCHOOL_FIRE:
                        spellId = SPELL_GEN_ADAPTIVE_WARDING_FIRE;
                        break;
                    case SPELL_SCHOOL_NATURE:
                        spellId = SPELL_GEN_ADAPTIVE_WARDING_NATURE;
                        break;
                    case SPELL_SCHOOL_FROST:
                        spellId = SPELL_GEN_ADAPTIVE_WARDING_FROST;
                        break;
                    case SPELL_SCHOOL_SHADOW:
                        spellId = SPELL_GEN_ADAPTIVE_WARDING_SHADOW;
                        break;
                    case SPELL_SCHOOL_ARCANE:
                        spellId = SPELL_GEN_ADAPTIVE_WARDING_ARCANE;
                        break;
                    default:
                        return;
                }
                GetTarget()->CastSpell(GetTarget(), spellId, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_gen_adaptive_warding_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_gen_adaptive_warding_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_adaptive_warding_AuraScript();
        }
};

// 41337 Aura of Anger
class spell_gen_aura_of_anger : public SpellScriptLoader
{
    public:
        spell_gen_aura_of_anger() : SpellScriptLoader("spell_gen_aura_of_anger") { }

        class spell_gen_aura_of_anger_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_aura_of_anger_AuraScript);

            void HandleEffectPeriodicUpdate(AuraEffect* aurEff)
            {
                if (AuraEffect* aurEff1 = aurEff->GetBase()->GetEffect(EFFECT_1))
                    aurEff1->ChangeAmount(aurEff1->GetAmount() + 5);
                aurEff->SetAmount(100 * aurEff->GetTickNumber());
            }

            void Register()
            {
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_gen_aura_of_anger_AuraScript::HandleEffectPeriodicUpdate, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_aura_of_anger_AuraScript();
        }
};

class spell_gen_av_drekthar_presence : public SpellScriptLoader
{
    public:
        spell_gen_av_drekthar_presence() : SpellScriptLoader("spell_gen_av_drekthar_presence") { }

        class spell_gen_av_drekthar_presence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_av_drekthar_presence_AuraScript);

            bool CheckAreaTarget(Unit* target)
            {
                switch (target->GetEntry())
                {
                    // alliance
                    case 14762: // Dun Baldar North Marshal
                    case 14763: // Dun Baldar South Marshal
                    case 14764: // Icewing Marshal
                    case 14765: // Stonehearth Marshal
                    case 11948: // Vandar Stormspike
                    // horde
                    case 14772: // East Frostwolf Warmaster
                    case 14776: // Tower Point Warmaster
                    case 14773: // Iceblood Warmaster
                    case 14777: // West Frostwolf Warmaster
                    case 11946: // Drek'thar
                        return true;
                    default:
                        return false;
                        break;
                }
            }
            void Register()
            {
                DoCheckAreaTarget += AuraCheckAreaTargetFn(spell_gen_av_drekthar_presence_AuraScript::CheckAreaTarget);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_av_drekthar_presence_AuraScript();
        }
};

// 46394 Brutallus Burn
class spell_gen_burn_brutallus : public SpellScriptLoader
{
    public:
        spell_gen_burn_brutallus() : SpellScriptLoader("spell_gen_burn_brutallus") { }

        class spell_gen_burn_brutallus_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_burn_brutallus_AuraScript);

            void HandleEffectPeriodicUpdate(AuraEffect* aurEff)
            {
                if (aurEff->GetTickNumber() % 11 == 0)
                    aurEff->SetAmount(aurEff->GetAmount() * 2);
            }

            void Register()
            {
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_gen_burn_brutallus_AuraScript::HandleEffectPeriodicUpdate, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_burn_brutallus_AuraScript();
        }
};

enum CannibalizeSpells
{
    SPELL_CANNIBALIZE_TRIGGERED = 20578,
};

class spell_gen_cannibalize : public SpellScriptLoader
{
    public:
        spell_gen_cannibalize() : SpellScriptLoader("spell_gen_cannibalize") { }

        class spell_gen_cannibalize_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_cannibalize_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CANNIBALIZE_TRIGGERED))
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
                caster->CastSpell(caster, SPELL_CANNIBALIZE_TRIGGERED, false);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_gen_cannibalize_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_gen_cannibalize_SpellScript::CheckIfCorpseNear);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_cannibalize_SpellScript();
        }
};

// 63845 - Create Lance
enum CreateLanceSpells
{
    SPELL_CREATE_LANCE_ALLIANCE = 63914,
    SPELL_CREATE_LANCE_HORDE    = 63919
};

class spell_gen_create_lance : public SpellScriptLoader
{
    public:
        spell_gen_create_lance() : SpellScriptLoader("spell_gen_create_lance") { }

        class spell_gen_create_lance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_create_lance_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CREATE_LANCE_ALLIANCE) || !sSpellMgr->GetSpellInfo(SPELL_CREATE_LANCE_HORDE))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* target = GetHitPlayer())
                {
                    if (target->GetTeam() == ALLIANCE)
                        GetCaster()->CastSpell(target, SPELL_CREATE_LANCE_ALLIANCE, true);
                    else
                        GetCaster()->CastSpell(target, SPELL_CREATE_LANCE_HORDE, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_create_lance_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_create_lance_SpellScript();
        }
};

// 28702 - Netherbloom
enum Netherbloom
{
    SPELL_NETHERBLOOM_POLLEN_1 = 28703
};

class spell_gen_netherbloom : public SpellScriptLoader
{
    public:
        spell_gen_netherbloom() : SpellScriptLoader("spell_gen_netherbloom") { }

        class spell_gen_netherbloom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_netherbloom_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                for (uint8 i = 0; i < 5; ++i)
                    if (!sSpellMgr->GetSpellInfo(SPELL_NETHERBLOOM_POLLEN_1 + i))
                        return false;
                return true;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                {
                    // 25% chance of casting a random buff
                    if (roll_chance_i(75))
                        return;

                    // triggered spells are 28703 to 28707
                    // Note: some sources say, that there was the possibility of
                    //       receiving a debuff. However, this seems to be removed by a patch.

                    // don't overwrite an existing aura
                    for (uint8 i = 0; i < 5; ++i)
                        if (target->HasAura(SPELL_NETHERBLOOM_POLLEN_1 + i))
                            return;

                    target->CastSpell(target, SPELL_NETHERBLOOM_POLLEN_1 + urand(0, 4), true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_netherbloom_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_netherbloom_SpellScript();
        }
};

// 28720 - Nightmare Vine
enum NightmareVine
{
    SPELL_NIGHTMARE_POLLEN  = 28721
};

class spell_gen_nightmare_vine : public SpellScriptLoader
{
    public:
        spell_gen_nightmare_vine() : SpellScriptLoader("spell_gen_nightmare_vine") { }

        class spell_gen_nightmare_vine_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_nightmare_vine_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_NIGHTMARE_POLLEN))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                {
                    // 25% chance of casting Nightmare Pollen
                    if (roll_chance_i(25))
                        target->CastSpell(target, SPELL_NIGHTMARE_POLLEN, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_nightmare_vine_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_nightmare_vine_SpellScript();
        }
};

// 27539 - Obsidian Armor
enum ObsidianArmor
{
    SPELL_GEN_OBSIDIAN_ARMOR_HOLY       = 27536,
    SPELL_GEN_OBSIDIAN_ARMOR_FIRE       = 27533,
    SPELL_GEN_OBSIDIAN_ARMOR_NATURE     = 27538,
    SPELL_GEN_OBSIDIAN_ARMOR_FROST      = 27534,
    SPELL_GEN_OBSIDIAN_ARMOR_SHADOW     = 27535,
    SPELL_GEN_OBSIDIAN_ARMOR_ARCANE     = 27540
};

class spell_gen_obsidian_armor : public SpellScriptLoader
{
    public:
        spell_gen_obsidian_armor() : SpellScriptLoader("spell_gen_obsidian_armor") { }

        class spell_gen_obsidian_armor_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_obsidian_armor_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_GEN_OBSIDIAN_ARMOR_HOLY) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_OBSIDIAN_ARMOR_FIRE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_OBSIDIAN_ARMOR_NATURE) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_OBSIDIAN_ARMOR_FROST) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_OBSIDIAN_ARMOR_SHADOW) ||
                    !sSpellMgr->GetSpellInfo(SPELL_GEN_OBSIDIAN_ARMOR_ARCANE))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                if (eventInfo.GetDamageInfo()->GetSpellInfo()) // eventInfo.GetSpellInfo()
                    return false;

                if (GetFirstSchoolInMask(eventInfo.GetSchoolMask()) == SPELL_SCHOOL_NORMAL)
                    return false;

                return true;
            }

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                uint32 spellId = 0;
                switch (GetFirstSchoolInMask(eventInfo.GetSchoolMask()))
                {
                    case SPELL_SCHOOL_HOLY:
                        spellId = SPELL_GEN_OBSIDIAN_ARMOR_HOLY;
                        break;
                    case SPELL_SCHOOL_FIRE:
                        spellId = SPELL_GEN_OBSIDIAN_ARMOR_FIRE;
                        break;
                    case SPELL_SCHOOL_NATURE:
                        spellId = SPELL_GEN_OBSIDIAN_ARMOR_NATURE;
                        break;
                    case SPELL_SCHOOL_FROST:
                        spellId = SPELL_GEN_OBSIDIAN_ARMOR_FROST;
                        break;
                    case SPELL_SCHOOL_SHADOW:
                        spellId = SPELL_GEN_OBSIDIAN_ARMOR_SHADOW;
                        break;
                    case SPELL_SCHOOL_ARCANE:
                        spellId = SPELL_GEN_OBSIDIAN_ARMOR_ARCANE;
                        break;
                    default:
                        return;
                }
                GetTarget()->CastSpell(GetTarget(), spellId, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_gen_obsidian_armor_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_gen_obsidian_armor_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_obsidian_armor_AuraScript();
        }
};

// 45472 Parachute
enum ParachuteSpells
{
    SPELL_PARACHUTE         = 45472,
    SPELL_PARACHUTE_BUFF    = 44795,
};

class spell_gen_parachute : public SpellScriptLoader
{
    public:
        spell_gen_parachute() : SpellScriptLoader("spell_gen_parachute") { }

        class spell_gen_parachute_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_parachute_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PARACHUTE) || !sSpellMgr->GetSpellInfo(SPELL_PARACHUTE_BUFF))
                    return false;
                return true;
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (Player* target = GetTarget()->ToPlayer())
                    if (target->IsFalling())
                    {
                        target->RemoveAurasDueToSpell(SPELL_PARACHUTE);
                        target->CastSpell(target, SPELL_PARACHUTE_BUFF, true);
                    }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_gen_parachute_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_parachute_AuraScript();
        }
};

class spell_gen_remove_flight_auras : public SpellScriptLoader
{
    public:
        spell_gen_remove_flight_auras() : SpellScriptLoader("spell_gen_remove_flight_auras") {}

        class spell_gen_remove_flight_auras_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_remove_flight_auras_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    target->RemoveAurasByType(SPELL_AURA_FLY);
                    target->RemoveAurasByType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_remove_flight_auras_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_remove_flight_auras_SpellScript();
        }
};

enum EluneCandle
{
    NPC_OMEN                       = 15467,

    SPELL_ELUNE_CANDLE_OMEN_HEAD   = 26622,
    SPELL_ELUNE_CANDLE_OMEN_CHEST  = 26624,
    SPELL_ELUNE_CANDLE_OMEN_HAND_R = 26625,
    SPELL_ELUNE_CANDLE_OMEN_HAND_L = 26649,
    SPELL_ELUNE_CANDLE_NORMAL      = 26636,
};

class spell_gen_elune_candle : public SpellScriptLoader
{
    public:
        spell_gen_elune_candle() : SpellScriptLoader("spell_gen_elune_candle") {}

        class spell_gen_elune_candle_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_elune_candle_SpellScript);
            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ELUNE_CANDLE_OMEN_HEAD))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_ELUNE_CANDLE_OMEN_CHEST))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_ELUNE_CANDLE_OMEN_HAND_R))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_ELUNE_CANDLE_OMEN_HAND_L))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_ELUNE_CANDLE_NORMAL))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                uint32 spellId = 0;

                if (GetHitUnit()->GetEntry() == NPC_OMEN)
                {
                    switch (urand(0, 3))
                    {
                        case 0: spellId = SPELL_ELUNE_CANDLE_OMEN_HEAD; break;
                        case 1: spellId = SPELL_ELUNE_CANDLE_OMEN_CHEST; break;
                        case 2: spellId = SPELL_ELUNE_CANDLE_OMEN_HAND_R; break;
                        case 3: spellId = SPELL_ELUNE_CANDLE_OMEN_HAND_L; break;
                    }
                }
                else
                    spellId = SPELL_ELUNE_CANDLE_NORMAL;

                GetCaster()->CastSpell(GetHitUnit(), spellId, true, NULL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_elune_candle_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_elune_candle_SpellScript();
        }
};

class spell_creature_permanent_feign_death : public SpellScriptLoader
{
    public:
        spell_creature_permanent_feign_death() : SpellScriptLoader("spell_creature_permanent_feign_death") { }

        class spell_creature_permanent_feign_death_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_creature_permanent_feign_death_AuraScript);

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                target->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);

                if (target->GetTypeId() == TYPEID_UNIT)
                    target->ToCreature()->SetReactState(REACT_PASSIVE);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_creature_permanent_feign_death_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_creature_permanent_feign_death_AuraScript();
        }
};

enum PvPTrinketTriggeredSpells
{
    SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER         = 72752,
    SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER_WOTF    = 72757,
};

class spell_pvp_trinket_wotf_shared_cd : public SpellScriptLoader
{
    public:
        spell_pvp_trinket_wotf_shared_cd() : SpellScriptLoader("spell_pvp_trinket_wotf_shared_cd") {}

        class spell_pvp_trinket_wotf_shared_cd_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pvp_trinket_wotf_shared_cd_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER) || !sSpellMgr->GetSpellInfo(SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER_WOTF))
                    return false;
                return true;
            }

            void HandleScript()
            {
                // This is only needed because spells cast from spell_linked_spell are triggered by default
                // Spell::SendSpellCooldown() skips all spells with TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD
                GetCaster()->ToPlayer()->AddSpellAndCategoryCooldowns(GetSpellInfo(), GetCastItem() ? GetCastItem()->GetEntry() : 0, GetSpell());
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_pvp_trinket_wotf_shared_cd_SpellScript::HandleScript);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pvp_trinket_wotf_shared_cd_SpellScript();
        }
};

enum AnimalBloodPoolSpell
{
    SPELL_ANIMAL_BLOOD      = 46221,
    SPELL_SPAWN_BLOOD_POOL  = 63471,
};

class spell_gen_animal_blood : public SpellScriptLoader
{
    public:
        spell_gen_animal_blood() : SpellScriptLoader("spell_gen_animal_blood") { }

        class spell_gen_animal_blood_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_animal_blood_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SPAWN_BLOOD_POOL))
                    return false;
                return true;
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                // Remove all auras with spell id 46221, except the one currently being applied
                while (Aura* aur = GetUnitOwner()->GetOwnedAura(SPELL_ANIMAL_BLOOD, 0, 0, 0, GetAura()))
                    GetUnitOwner()->RemoveOwnedAura(aur);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* owner = GetUnitOwner())
                    if (owner->IsInWater())
                        owner->CastSpell(owner, SPELL_SPAWN_BLOOD_POOL, true);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectRemoveFn(spell_gen_animal_blood_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_gen_animal_blood_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_animal_blood_AuraScript();
        }
};

enum DivineStormSpell
{
    SPELL_DIVINE_STORM  = 53385,
};

// 70769 Divine Storm!
class spell_gen_divine_storm_cd_reset : public SpellScriptLoader
{
    public:
        spell_gen_divine_storm_cd_reset() : SpellScriptLoader("spell_gen_divine_storm_cd_reset") {}

        class spell_gen_divine_storm_cd_reset_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_divine_storm_cd_reset_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DIVINE_STORM))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                if (caster->HasSpellCooldown(SPELL_DIVINE_STORM))
                    caster->RemoveSpellCooldown(SPELL_DIVINE_STORM, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_divine_storm_cd_reset_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_divine_storm_cd_reset_SpellScript();
        }
};

class spell_gen_gunship_portal : public SpellScriptLoader
{
    public:
        spell_gen_gunship_portal() : SpellScriptLoader("spell_gen_gunship_portal") { }

        class spell_gen_gunship_portal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_gunship_portal_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                if (Battleground* bg = caster->GetBattleground())
                    if (bg->GetTypeID(true) == BATTLEGROUND_IC)
                        bg->DoAction(1, caster->GetGUID());
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_gunship_portal_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_gunship_portal_SpellScript();
        }
};

enum parachuteIC
{
    SPELL_PARACHUTE_IC = 66657,
};

class spell_gen_parachute_ic : public SpellScriptLoader
{
    public:
        spell_gen_parachute_ic() : SpellScriptLoader("spell_gen_parachute_ic") { }

        class spell_gen_parachute_ic_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_parachute_ic_AuraScript)

            void HandleTriggerSpell(AuraEffect const* /*aurEff*/)
            {
                if (Player* target = GetTarget()->ToPlayer())
                    if (target->m_movementInfo.fallTime > 2000)
                        target->CastSpell(target, SPELL_PARACHUTE_IC, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_gen_parachute_ic_AuraScript::HandleTriggerSpell, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_parachute_ic_AuraScript();
        }
};

class spell_gen_dungeon_credit : public SpellScriptLoader
{
    public:
        spell_gen_dungeon_credit() : SpellScriptLoader("spell_gen_dungeon_credit") { }

        class spell_gen_dungeon_credit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_dungeon_credit_SpellScript);

            bool Load()
            {
                _handled = false;
                return GetCaster()->GetTypeId() == TYPEID_UNIT;
            }

            void CreditEncounter()
            {
                // This hook is executed for every target, make sure we only credit instance once
                if (_handled)
                    return;

                _handled = true;
                Unit* caster = GetCaster();
                if (InstanceScript* instance = caster->GetInstanceScript())
                    instance->UpdateEncounterState(ENCOUNTER_CREDIT_CAST_SPELL, GetSpellInfo()->Id, caster);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_gen_dungeon_credit_SpellScript::CreditEncounter);
            }

            bool _handled;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_dungeon_credit_SpellScript();
        }
};

class spell_gen_profession_research : public SpellScriptLoader
{
    public:
        spell_gen_profession_research() : SpellScriptLoader("spell_gen_profession_research") {}

        class spell_gen_profession_research_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_profession_research_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            SpellCastResult CheckRequirement()
            {
                if (HasDiscoveredAllSpells(GetSpellInfo()->Id, GetCaster()->ToPlayer()))
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_NOTHING_TO_DISCOVER);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                uint32 spellId = GetSpellInfo()->Id;

                // learn random explicit discovery recipe (if any)
                if (uint32 discoveredSpellId = GetExplicitDiscoverySpell(spellId, caster))
                    caster->learnSpell(discoveredSpellId, false);

                caster->UpdateCraftSkill(spellId);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gen_profession_research_SpellScript::CheckRequirement);
                OnEffectHitTarget += SpellEffectFn(spell_gen_profession_research_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_profession_research_SpellScript();
        }
};

class spell_generic_clone : public SpellScriptLoader
{
    public:
        spell_generic_clone() : SpellScriptLoader("spell_generic_clone") { }

        class spell_generic_clone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_generic_clone_SpellScript);

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                uint32 spellId = uint32(GetSpellInfo()->Effects[effIndex].CalcValue());
                GetHitUnit()->CastSpell(GetCaster(), spellId, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_generic_clone_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
                OnEffectHitTarget += SpellEffectFn(spell_generic_clone_SpellScript::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_generic_clone_SpellScript();
        }
};

enum CloneWeaponSpells
{
    SPELL_COPY_WEAPON_AURA       = 41054,
    SPELL_COPY_WEAPON_2_AURA     = 63418,
    SPELL_COPY_WEAPON_3_AURA     = 69893,

    SPELL_COPY_OFFHAND_AURA      = 45205,
    SPELL_COPY_OFFHAND_2_AURA    = 69896,

    SPELL_COPY_RANGED_AURA       = 57594
};

class spell_generic_clone_weapon : public SpellScriptLoader
{
    public:
        spell_generic_clone_weapon() : SpellScriptLoader("spell_generic_clone_weapon") { }

        class spell_generic_clone_weapon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_generic_clone_weapon_SpellScript);

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();

                if (Unit* target = GetHitUnit())
                {

                    uint32 spellId = uint32(GetSpellInfo()->Effects[EFFECT_0].CalcValue());
                    caster->CastSpell(target, spellId, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_generic_clone_weapon_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_generic_clone_weapon_SpellScript();
        }
};

class spell_gen_clone_weapon_aura : public SpellScriptLoader
{
    public:
        spell_gen_clone_weapon_aura() : SpellScriptLoader("spell_gen_clone_weapon_aura") { }

        class spell_gen_clone_weapon_auraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_clone_weapon_auraScript);

            uint32 prevItem;

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_COPY_WEAPON_AURA) || !sSpellMgr->GetSpellInfo(SPELL_COPY_WEAPON_2_AURA) || !sSpellMgr->GetSpellInfo(SPELL_COPY_WEAPON_3_AURA)
                    || !sSpellMgr->GetSpellInfo(SPELL_COPY_OFFHAND_AURA) || !sSpellMgr->GetSpellInfo(SPELL_COPY_OFFHAND_2_AURA) || !sSpellMgr->GetSpellInfo(SPELL_COPY_RANGED_AURA))
                    return false;
                return true;
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();

                if (!caster)
                    return;

                switch (GetSpellInfo()->Id)
                {
                    case SPELL_COPY_WEAPON_AURA:
                    case SPELL_COPY_WEAPON_2_AURA:
                    case SPELL_COPY_WEAPON_3_AURA:
                    {
                        prevItem = target->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID);

                        if (Player* player = caster->ToPlayer())
                        {
                            if (Item* mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
                                target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, mainItem->GetEntry());
                        }
                        else
                            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID));
                        break;
                    }
                    case SPELL_COPY_OFFHAND_AURA:
                    case SPELL_COPY_OFFHAND_2_AURA:
                    {
                        prevItem = target->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID) + 1;

                        if (Player* player = caster->ToPlayer())
                        {
                            if (Item* offItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
                                target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, offItem->GetEntry());
                        }
                        else
                            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1));
                        break;
                    }
                    case SPELL_COPY_RANGED_AURA:
                    {
                        prevItem = target->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID) + 2;

                        if (Player* player = caster->ToPlayer())
                        {
                            if (Item* rangedItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
                                target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2, rangedItem->GetEntry());
                        }
                        else
                            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2, caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2));
                        break;
                    }
                    default:
                        break;
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();

                switch (GetSpellInfo()->Id)
                {
                    case SPELL_COPY_WEAPON_AURA:
                    case SPELL_COPY_WEAPON_2_AURA:
                    case SPELL_COPY_WEAPON_3_AURA:
                    {
                        target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, prevItem);
                        break;
                    }
                    case SPELL_COPY_OFFHAND_AURA:
                    case SPELL_COPY_OFFHAND_2_AURA:
                    {
                        target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, prevItem);
                        break;
                    }
                    case SPELL_COPY_RANGED_AURA:
                    {
                        target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2, prevItem);
                        break;
                    }
                    default:
                        break;
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_gen_clone_weapon_auraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_gen_clone_weapon_auraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_clone_weapon_auraScript();
        }
};

enum SeaforiumSpells
{
    SPELL_PLANT_CHARGES_CREDIT_ACHIEVEMENT = 60937,
};

class spell_gen_seaforium_blast : public SpellScriptLoader
{
    public:
        spell_gen_seaforium_blast() : SpellScriptLoader("spell_gen_seaforium_blast") {}

        class spell_gen_seaforium_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_seaforium_blast_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PLANT_CHARGES_CREDIT_ACHIEVEMENT))
                    return false;
                return true;
            }

            bool Load()
            {
                // OriginalCaster is always available in Spell::prepare
                return GetOriginalCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void AchievementCredit(SpellEffIndex /*effIndex*/)
            {
                // but in effect handling OriginalCaster can become NULL
                if (Unit* originalCaster = GetOriginalCaster())
                    if (GameObject* go = GetHitGObj())
                        if (go->GetGOInfo()->type == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
                            originalCaster->CastSpell(originalCaster, SPELL_PLANT_CHARGES_CREDIT_ACHIEVEMENT, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_seaforium_blast_SpellScript::AchievementCredit, EFFECT_1, SPELL_EFFECT_GAMEOBJECT_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_seaforium_blast_SpellScript();
        }
};

enum FriendOrFowl
{
    SPELL_TURKEY_VENGEANCE  = 25285,
};

class spell_gen_turkey_marker : public SpellScriptLoader
{
    public:
        spell_gen_turkey_marker() : SpellScriptLoader("spell_gen_turkey_marker") { }

        class spell_gen_turkey_marker_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_turkey_marker_AuraScript);

            void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                // store stack apply times, so we can pop them while they expire
                _applyTimes.push_back(getMSTime());
                Unit* target = GetTarget();

                // on stack 15 cast the achievement crediting spell
                if (GetStackAmount() >= 15)
                    target->CastSpell(target, SPELL_TURKEY_VENGEANCE, true, NULL, aurEff, GetCasterGUID());
            }

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (_applyTimes.empty())
                    return;

                // pop stack if it expired for us
                if (_applyTimes.front() + GetMaxDuration() < getMSTime())
                    ModStackAmount(-1, AURA_REMOVE_BY_EXPIRE);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_gen_turkey_marker_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_gen_turkey_marker_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }

            std::list<uint32> _applyTimes;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_turkey_marker_AuraScript();
        }
};

class spell_gen_lifeblood : public SpellScriptLoader
{
    public:
        spell_gen_lifeblood() : SpellScriptLoader("spell_gen_lifeblood") { }

        class spell_gen_lifeblood_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_lifeblood_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* owner = GetUnitOwner())
                    amount += int32(CalculatePct(owner->GetMaxHealth(), 1.5f / aurEff->GetTotalTicks()));
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_lifeblood_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_lifeblood_AuraScript();
        }
};

enum MagicRoosterSpells
{
    SPELL_MAGIC_ROOSTER_NORMAL          = 66122,
    SPELL_MAGIC_ROOSTER_DRAENEI_MALE    = 66123,
    SPELL_MAGIC_ROOSTER_TAUREN_MALE     = 66124,
};

class spell_gen_magic_rooster : public SpellScriptLoader
{
    public:
        spell_gen_magic_rooster() : SpellScriptLoader("spell_gen_magic_rooster") { }

        class spell_gen_magic_rooster_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_magic_rooster_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Player* target = GetHitPlayer())
                {
                    // prevent client crashes from stacking mounts
                    target->RemoveAurasByType(SPELL_AURA_MOUNTED);

                    uint32 spellId = SPELL_MAGIC_ROOSTER_NORMAL;
                    switch (target->getRace())
                    {
                        case RACE_DRAENEI:
                            if (target->getGender() == GENDER_MALE)
                                spellId = SPELL_MAGIC_ROOSTER_DRAENEI_MALE;
                            break;
                        case RACE_TAUREN:
                            if (target->getGender() == GENDER_MALE)
                                spellId = SPELL_MAGIC_ROOSTER_TAUREN_MALE;
                            break;
                        default:
                            break;
                    }

                    target->CastSpell(target, spellId, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_magic_rooster_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_magic_rooster_SpellScript();
        }
};

class spell_gen_allow_cast_from_item_only : public SpellScriptLoader
{
    public:
        spell_gen_allow_cast_from_item_only() : SpellScriptLoader("spell_gen_allow_cast_from_item_only") { }

        class spell_gen_allow_cast_from_item_only_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_allow_cast_from_item_only_SpellScript);

            SpellCastResult CheckRequirement()
            {
                if (!GetCastItem())
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gen_allow_cast_from_item_only_SpellScript::CheckRequirement);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_allow_cast_from_item_only_SpellScript();
        }
};

enum Launch
{
    SPELL_LAUNCH_NO_FALLING_DAMAGE = 66251
};

class spell_gen_launch : public SpellScriptLoader
{
    public:
        spell_gen_launch() : SpellScriptLoader("spell_gen_launch") {}

        class spell_gen_launch_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_launch_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Player* player = GetHitPlayer())
                    player->AddAura(SPELL_LAUNCH_NO_FALLING_DAMAGE, player); // prevents falling damage
            }

            void Launch()
            {
                WorldLocation const* const position = GetExplTargetDest();

                if (Player* player = GetHitPlayer())
                {
                    player->ExitVehicle();

                    // A better research is needed
                    // There is no spell for this, the following calculation was based on void Spell::CalculateJumpSpeeds

                    float speedZ = 10.0f;
                    float dist = position->GetExactDist2d(player->GetPositionX(), player->GetPositionY());
                    float speedXY = dist;

                    player->GetMotionMaster()->MoveJump(position->GetPositionX(), position->GetPositionY(), position->GetPositionZ(), speedXY, speedZ);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_launch_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_FORCE_CAST);
                AfterHit += SpellHitFn(spell_gen_launch_SpellScript::Launch);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_launch_SpellScript();
        }
};

enum VehicleScaling
{
    SPELL_GEAR_SCALING      = 66668,
};

class spell_gen_vehicle_scaling : public SpellScriptLoader
{
    public:
        spell_gen_vehicle_scaling() : SpellScriptLoader("spell_gen_vehicle_scaling") { }

        class spell_gen_vehicle_scaling_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_vehicle_scaling_AuraScript);

            bool Load()
            {
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                Unit* caster = GetCaster();
                float factor;
                uint16 baseItemLevel;

                // TODO: Reserach coeffs for different vehicles
                switch (GetId())
                {
                    case SPELL_GEAR_SCALING:
                        factor = 1.0f;
                        baseItemLevel = 205;
                        break;
                    default:
                        factor = 1.0f;
                        baseItemLevel = 170;
                        break;
                }

                float avgILvl = caster->ToPlayer()->GetAverageItemLevel();
                if (avgILvl < baseItemLevel)
                    return;                     // TODO: Research possibility of scaling down

                amount = uint16((avgILvl - baseItemLevel) * factor);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_vehicle_scaling_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_HEALING_PCT);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_vehicle_scaling_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_vehicle_scaling_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_vehicle_scaling_AuraScript();
        }
};


class spell_gen_oracle_wolvar_reputation : public SpellScriptLoader
{
    public:
        spell_gen_oracle_wolvar_reputation() : SpellScriptLoader("spell_gen_oracle_wolvar_reputation") { }

        class spell_gen_oracle_wolvar_reputation_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_oracle_wolvar_reputation_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                Player* player = GetCaster()->ToPlayer();
                uint32 factionId = GetSpellInfo()->Effects[effIndex].CalcValue();
                int32  repChange =  GetSpellInfo()->Effects[EFFECT_1].CalcValue();

                FactionEntry const* factionEntry = sFactionStore.LookupEntry(factionId);

                if (!factionEntry)
                    return;

                // Set rep to baserep + basepoints (expecting spillover for oposite faction -> become hated)
                // Not when player already has equal or higher rep with this faction
                if (player->GetReputationMgr().GetBaseReputation(factionEntry) < repChange)
                    player->GetReputationMgr().SetReputation(factionEntry, repChange);

                // EFFECT_INDEX_2 most likely update at war state, we already handle this in SetReputation
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_gen_oracle_wolvar_reputation_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_oracle_wolvar_reputation_SpellScript();
        }
};

enum DummyTrigger
{
    SPELL_PERSISTANT_SHIELD_TRIGGERED       = 26470,
    SPELL_PERSISTANT_SHIELD                 = 26467,
};

class spell_gen_dummy_trigger : public SpellScriptLoader
{
    public:
        spell_gen_dummy_trigger() : SpellScriptLoader("spell_gen_dummy_trigger") { }

        class spell_gen_dummy_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_dummy_trigger_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_PERSISTANT_SHIELD_TRIGGERED) || !sSpellMgr->GetSpellInfo(SPELL_PERSISTANT_SHIELD))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                int32 damage = GetEffectValue();
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                    if (SpellInfo const* triggeredByAuraSpell = GetTriggeringSpell())
                        if (triggeredByAuraSpell->Id == SPELL_PERSISTANT_SHIELD_TRIGGERED)
                            caster->CastCustomSpell(target, SPELL_PERSISTANT_SHIELD_TRIGGERED, &damage, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_dummy_trigger_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_dummy_trigger_SpellScript();
        }

};

class spell_gen_spirit_healer_res : public SpellScriptLoader
{
    public:
        spell_gen_spirit_healer_res(): SpellScriptLoader("spell_gen_spirit_healer_res") { }

        class spell_gen_spirit_healer_res_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_spirit_healer_res_SpellScript);

            bool Load()
            {
                return GetOriginalCaster() && GetOriginalCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                Player* originalCaster = GetOriginalCaster()->ToPlayer();
                if (Unit* target = GetHitUnit())
                {
                    WorldPacket data(SMSG_SPIRIT_HEALER_CONFIRM, 8);
                    data << uint64(target->GetGUID());
                    originalCaster->GetSession()->SendPacket(&data);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_spirit_healer_res_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_spirit_healer_res_SpellScript();
        }
};

enum TransporterBackfires
{
    SPELL_TRANSPORTER_MALFUNCTION_POLYMORPH     = 23444,
    SPELL_TRANSPORTER_EVIL_TWIN                 = 23445,
    SPELL_TRANSPORTER_MALFUNCTION_MISS          = 36902,
};

class spell_gen_gadgetzan_transporter_backfire : public SpellScriptLoader
{
    public:
        spell_gen_gadgetzan_transporter_backfire() : SpellScriptLoader("spell_gen_gadgetzan_transporter_backfire") { }

        class spell_gen_gadgetzan_transporter_backfire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_gadgetzan_transporter_backfire_SpellScript)

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_TRANSPORTER_MALFUNCTION_POLYMORPH) || !sSpellMgr->GetSpellInfo(SPELL_TRANSPORTER_EVIL_TWIN)
                    || !sSpellMgr->GetSpellInfo(SPELL_TRANSPORTER_MALFUNCTION_MISS))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                Unit* caster = GetCaster();
                int32 r = irand(0, 119);
                if (r < 20)                           // Transporter Malfunction - 1/6 polymorph
                    caster->CastSpell(caster, SPELL_TRANSPORTER_MALFUNCTION_POLYMORPH, true);
                else if (r < 100)                     // Evil Twin               - 4/6 evil twin
                    caster->CastSpell(caster, SPELL_TRANSPORTER_EVIL_TWIN, true);
                else                                    // Transporter Malfunction - 1/6 miss the target
                    caster->CastSpell(caster, SPELL_TRANSPORTER_MALFUNCTION_MISS, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_gadgetzan_transporter_backfire_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_gadgetzan_transporter_backfire_SpellScript();
        }
};

enum GnomishTransporter
{
    SPELL_TRANSPORTER_SUCCESS                   = 23441,
    SPELL_TRANSPORTER_FAILURE                   = 23446,
};

class spell_gen_gnomish_transporter : public SpellScriptLoader
{
    public:
        spell_gen_gnomish_transporter() : SpellScriptLoader("spell_gen_gnomish_transporter") { }

        class spell_gen_gnomish_transporter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_gnomish_transporter_SpellScript)

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_TRANSPORTER_SUCCESS) || !sSpellMgr->GetSpellInfo(SPELL_TRANSPORTER_FAILURE))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                Unit* caster = GetCaster();
                caster->CastSpell(caster, roll_chance_i(50) ? SPELL_TRANSPORTER_SUCCESS : SPELL_TRANSPORTER_FAILURE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_gnomish_transporter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_gnomish_transporter_SpellScript();
        }
};

enum DalaranDisguiseSpells
{
    SPELL_SUNREAVER_DISGUISE_TRIGGER       = 69672,
    SPELL_SUNREAVER_DISGUISE_FEMALE        = 70973,
    SPELL_SUNREAVER_DISGUISE_MALE          = 70974,

    SPELL_SILVER_COVENANT_DISGUISE_TRIGGER = 69673,
    SPELL_SILVER_COVENANT_DISGUISE_FEMALE  = 70971,
    SPELL_SILVER_COVENANT_DISGUISE_MALE    = 70972,
};

class spell_gen_dalaran_disguise : public SpellScriptLoader
{
    public:
        spell_gen_dalaran_disguise(const char* name) : SpellScriptLoader(name) {}

        class spell_gen_dalaran_disguise_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_dalaran_disguise_SpellScript);
            bool Validate(SpellInfo const* spellEntry)
            {
                switch (spellEntry->Id)
                {
                    case SPELL_SUNREAVER_DISGUISE_TRIGGER:
                        if (!sSpellMgr->GetSpellInfo(SPELL_SUNREAVER_DISGUISE_FEMALE) || !sSpellMgr->GetSpellInfo(SPELL_SUNREAVER_DISGUISE_MALE))
                            return false;
                        break;
                    case SPELL_SILVER_COVENANT_DISGUISE_TRIGGER:
                        if (!sSpellMgr->GetSpellInfo(SPELL_SILVER_COVENANT_DISGUISE_FEMALE) || !sSpellMgr->GetSpellInfo(SPELL_SILVER_COVENANT_DISGUISE_MALE))
                            return false;
                        break;
                }
                return true;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Player* player = GetHitPlayer())
                {
                    uint8 gender = player->getGender();

                    uint32 spellId = GetSpellInfo()->Id;

                    switch (spellId)
                    {
                        case SPELL_SUNREAVER_DISGUISE_TRIGGER:
                            spellId = gender ? SPELL_SUNREAVER_DISGUISE_FEMALE : SPELL_SUNREAVER_DISGUISE_MALE;
                            break;
                        case SPELL_SILVER_COVENANT_DISGUISE_TRIGGER:
                            spellId = gender ? SPELL_SILVER_COVENANT_DISGUISE_FEMALE : SPELL_SILVER_COVENANT_DISGUISE_MALE;
                            break;
                        default:
                            break;
                    }
                    GetCaster()->CastSpell(player, spellId, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_dalaran_disguise_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_dalaran_disguise_SpellScript();
        }
};

/* DOCUMENTATION: Break-Shield spells
    Break-Shield spells can be classified in three groups:

        - Spells on vehicle bar used by players:
            + EFFECT_0: SCRIPT_EFFECT
            + EFFECT_1: NONE
            + EFFECT_2: NONE
        - Spells casted by players triggered by script:
            + EFFECT_0: SCHOOL_DAMAGE
            + EFFECT_1: SCRIPT_EFFECT
            + EFFECT_2: FORCE_CAST
        - Spells casted by NPCs on players:
            + EFFECT_0: SCHOOL_DAMAGE
            + EFFECT_1: SCRIPT_EFFECT
            + EFFECT_2: NONE

    In the following script we handle the SCRIPT_EFFECT for effIndex EFFECT_0 and EFFECT_1.
        - When handling EFFECT_0 we're in the "Spells on vehicle bar used by players" case
          and we'll trigger "Spells casted by players triggered by script"
        - When handling EFFECT_1 we're in the "Spells casted by players triggered by script"
          or "Spells casted by NPCs on players" so we'll search for the first defend layer and drop it.
*/

enum BreakShieldSpells
{
    SPELL_BREAK_SHIELD_DAMAGE_2K                 = 62626,
    SPELL_BREAK_SHIELD_DAMAGE_10K                = 64590,

    SPELL_BREAK_SHIELD_TRIGGER_FACTION_MOUNTS    = 62575, // Also on ToC5 mounts
    SPELL_BREAK_SHIELD_TRIGGER_CAMPAING_WARHORSE = 64595,
    SPELL_BREAK_SHIELD_TRIGGER_UNK               = 66480,
};

class spell_gen_break_shield: public SpellScriptLoader
{
    public:
        spell_gen_break_shield(const char* name) : SpellScriptLoader(name) {}

        class spell_gen_break_shield_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_break_shield_SpellScript)

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                Unit* target = GetHitUnit();

                switch (effIndex)
                {
                    case EFFECT_0: // On spells wich trigger the damaging spell (and also the visual)
                    {
                        uint32 spellId;

                        switch (GetSpellInfo()->Id)
                        {
                            case SPELL_BREAK_SHIELD_TRIGGER_UNK:
                            case SPELL_BREAK_SHIELD_TRIGGER_CAMPAING_WARHORSE:
                                spellId = SPELL_BREAK_SHIELD_DAMAGE_10K;
                                break;
                            case SPELL_BREAK_SHIELD_TRIGGER_FACTION_MOUNTS:
                                spellId = SPELL_BREAK_SHIELD_DAMAGE_2K;
                                break;
                            default:
                                return;
                        }

                        if (Unit* rider = GetCaster()->GetCharmer())
                            rider->CastSpell(target, spellId, false);
                        else
                            GetCaster()->CastSpell(target, spellId, false);
                        break;
                    }
                    case EFFECT_1: // On damaging spells, for removing a defend layer
                    {
                        Unit::AuraApplicationMap const& auras = target->GetAppliedAuras();
                        for (Unit::AuraApplicationMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                        {
                            if (Aura* aura = itr->second->GetBase())
                            {
                                SpellInfo const* auraInfo = aura->GetSpellInfo();
                                if (auraInfo && auraInfo->SpellIconID == 2007 && aura->HasEffectType(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN))
                                {
                                    aura->ModStackAmount(-1, AURA_REMOVE_BY_ENEMY_SPELL);
                                    // Remove dummys from rider (Necessary for updating visual shields)
                                    if (Unit* rider = target->GetCharmer())
                                        if (Aura* defend = rider->GetAura(aura->GetId()))
                                            defend->ModStackAmount(-1, AURA_REMOVE_BY_ENEMY_SPELL);
                                    break;
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
                OnEffectHitTarget += SpellEffectFn(spell_gen_break_shield_SpellScript::HandleScriptEffect, EFFECT_FIRST_FOUND, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_break_shield_SpellScript();
        }
};

/* DOCUMENTATION: Charge spells
    Charge spells can be classified in four groups:

        - Spells on vehicle bar used by players:
            + EFFECT_0: SCRIPT_EFFECT
            + EFFECT_1: TRIGGER_SPELL
            + EFFECT_2: NONE
        - Spells casted by player's mounts triggered by script:
            + EFFECT_0: CHARGE
            + EFFECT_1: TRIGGER_SPELL
            + EFFECT_2: APPLY_AURA
        - Spells casted by players on the target triggered by script:
            + EFFECT_0: SCHOOL_DAMAGE
            + EFFECT_1: SCRIPT_EFFECT
            + EFFECT_2: NONE
        - Spells casted by NPCs on players:
            + EFFECT_0: SCHOOL_DAMAGE
            + EFFECT_1: CHARGE
            + EFFECT_2: SCRIPT_EFFECT

    In the following script we handle the SCRIPT_EFFECT and CHARGE
        - When handling SCRIPT_EFFECT:
            + EFFECT_0: Corresponds to "Spells on vehicle bar used by players" and we make player's mount cast
              the charge effect on the current target ("Spells casted by player's mounts triggered by script").
            + EFFECT_1 and EFFECT_2: Triggered when "Spells casted by player's mounts triggered by script" hits target,
              corresponding to "Spells casted by players on the target triggered by script" and "Spells casted by
              NPCs on players" and we check Defend layers and drop a charge of the first found.
        - When handling CHARGE:
            + Only launched for "Spells casted by player's mounts triggered by script", makes the player cast the
              damaging spell on target with a small chance of failing it.
*/

enum ChargeSpells
{
    SPELL_CHARGE_DAMAGE_8K5             = 62874,
    SPELL_CHARGE_DAMAGE_20K             = 68498,
    SPELL_CHARGE_DAMAGE_45K             = 64591,

    SPELL_CHARGE_CHARGING_EFFECT_8K5    = 63661,
    SPELL_CHARGE_CHARGING_EFFECT_20K_1  = 68284,
    SPELL_CHARGE_CHARGING_EFFECT_20K_2  = 68501,
    SPELL_CHARGE_CHARGING_EFFECT_45K_1  = 62563,
    SPELL_CHARGE_CHARGING_EFFECT_45K_2  = 66481,

    SPELL_CHARGE_TRIGGER_FACTION_MOUNTS = 62960,
    SPELL_CHARGE_TRIGGER_TRIAL_CHAMPION = 68282,

    SPELL_CHARGE_MISS_EFFECT            = 62977,
};

class spell_gen_mounted_charge: public SpellScriptLoader
{
    public:
        spell_gen_mounted_charge() : SpellScriptLoader("spell_gen_mounted_charge") { }

        class spell_gen_mounted_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_mounted_charge_SpellScript)

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                Unit* target = GetHitUnit();

                switch (effIndex)
                {
                    case EFFECT_0: // On spells wich trigger the damaging spell (and also the visual)
                    {
                        uint32 spellId;

                        switch (GetSpellInfo()->Id)
                        {
                            case SPELL_CHARGE_TRIGGER_TRIAL_CHAMPION:
                                spellId = SPELL_CHARGE_CHARGING_EFFECT_20K_1;
                                break;
                            case SPELL_CHARGE_TRIGGER_FACTION_MOUNTS:
                                spellId = SPELL_CHARGE_CHARGING_EFFECT_8K5;
                                break;
                            default:
                                return;
                        }

                        // If target isn't a training dummy there's a chance of failing the charge
                        if (!target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE) && roll_chance_f(12.5f))
                            spellId = SPELL_CHARGE_MISS_EFFECT;

                        if (Unit* vehicle = GetCaster()->GetVehicleBase())
                            vehicle->CastSpell(target, spellId, false);
                        else
                            GetCaster()->CastSpell(target, spellId, false);
                        break;
                    }
                    case EFFECT_1: // On damaging spells, for removing a defend layer
                    case EFFECT_2:
                    {
                        Unit::AuraApplicationMap const& auras = target->GetAppliedAuras();
                        for (Unit::AuraApplicationMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                        {
                            if (Aura* aura = itr->second->GetBase())
                            {
                                SpellInfo const* auraInfo = aura->GetSpellInfo();
                                if (auraInfo && auraInfo->SpellIconID == 2007 && aura->HasEffectType(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN))
                                {
                                    aura->ModStackAmount(-1, AURA_REMOVE_BY_ENEMY_SPELL);
                                    // Remove dummys from rider (Necessary for updating visual shields)
                                    if (Unit* rider = target->GetCharmer())
                                        if (Aura* defend = rider->GetAura(aura->GetId()))
                                            defend->ModStackAmount(-1, AURA_REMOVE_BY_ENEMY_SPELL);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }

            void HandleChargeEffect(SpellEffIndex /*effIndex*/)
            {
                uint32 spellId;

                switch (GetSpellInfo()->Id)
                {
                    case SPELL_CHARGE_CHARGING_EFFECT_8K5:
                        spellId = SPELL_CHARGE_DAMAGE_8K5;
                        break;
                    case SPELL_CHARGE_CHARGING_EFFECT_20K_1:
                    case SPELL_CHARGE_CHARGING_EFFECT_20K_2:
                        spellId = SPELL_CHARGE_DAMAGE_20K;
                        break;
                    case SPELL_CHARGE_CHARGING_EFFECT_45K_1:
                    case SPELL_CHARGE_CHARGING_EFFECT_45K_2:
                        spellId = SPELL_CHARGE_DAMAGE_45K;
                        break;
                    default:
                        return;
                }

                if (Unit* rider = GetCaster()->GetCharmer())
                    rider->CastSpell(GetHitUnit(), spellId, false);
                else
                    GetCaster()->CastSpell(GetHitUnit(), spellId, false);
            }

            void Register()
            {
                SpellInfo const* spell = sSpellMgr->GetSpellInfo(m_scriptSpellId);

                if (spell->HasEffect(SPELL_EFFECT_SCRIPT_EFFECT))
                    OnEffectHitTarget += SpellEffectFn(spell_gen_mounted_charge_SpellScript::HandleScriptEffect, EFFECT_FIRST_FOUND, SPELL_EFFECT_SCRIPT_EFFECT);

                if (spell->Effects[EFFECT_0].Effect == SPELL_EFFECT_CHARGE)
                    OnEffectHitTarget += SpellEffectFn(spell_gen_mounted_charge_SpellScript::HandleChargeEffect, EFFECT_0, SPELL_EFFECT_CHARGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_mounted_charge_SpellScript();
        }
};

enum DefendVisuals
{
    SPELL_VISUAL_SHIELD_1 = 63130,
    SPELL_VISUAL_SHIELD_2 = 63131,
    SPELL_VISUAL_SHIELD_3 = 63132,
};

class spell_gen_defend : public SpellScriptLoader
{
    public:
        spell_gen_defend() : SpellScriptLoader("spell_gen_defend") { }

        class spell_gen_defend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_defend_AuraScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_VISUAL_SHIELD_1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_VISUAL_SHIELD_2))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_VISUAL_SHIELD_3))
                    return false;
                return true;
            }

            void RefreshVisualShields(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster())
                {
                    Unit* target = GetTarget();

                    for (uint8 i = 0; i < GetSpellInfo()->StackAmount; ++i)
                        target->RemoveAurasDueToSpell(SPELL_VISUAL_SHIELD_1 + i);

                    target->CastSpell(target, SPELL_VISUAL_SHIELD_1 + GetAura()->GetStackAmount() - 1, true, NULL, aurEff);
                }
                else
                    GetTarget()->RemoveAurasDueToSpell(GetId());
            }

            void RemoveVisualShields(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                for (uint8 i = 0; i < GetSpellInfo()->StackAmount; ++i)
                    GetTarget()->RemoveAurasDueToSpell(SPELL_VISUAL_SHIELD_1 + i);
            }

            void RemoveDummyFromDriver(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (TempSummon* vehicle = caster->ToTempSummon())
                        if (Unit* rider = vehicle->GetSummoner())
                            rider->RemoveAurasDueToSpell(GetId());
            }

            void Register()
            {
                SpellInfo const* spell = sSpellMgr->GetSpellInfo(m_scriptSpellId);

                // Defend spells casted by NPCs (add visuals)
                if (spell->Effects[EFFECT_0].ApplyAuraName == SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN)
                {
                    AfterEffectApply += AuraEffectApplyFn(spell_gen_defend_AuraScript::RefreshVisualShields, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                    OnEffectRemove += AuraEffectRemoveFn(spell_gen_defend_AuraScript::RemoveVisualShields, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                }

                // Remove Defend spell from player when he dismounts
                if (spell->Effects[EFFECT_2].ApplyAuraName == SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN)
                    OnEffectRemove += AuraEffectRemoveFn(spell_gen_defend_AuraScript::RemoveDummyFromDriver, EFFECT_2, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);

                // Defend spells casted by players (add/remove visuals)
                if (spell->Effects[EFFECT_1].ApplyAuraName == SPELL_AURA_DUMMY)
                {
                    AfterEffectApply += AuraEffectApplyFn(spell_gen_defend_AuraScript::RefreshVisualShields, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                    OnEffectRemove += AuraEffectRemoveFn(spell_gen_defend_AuraScript::RemoveVisualShields, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                }
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_defend_AuraScript();
        }
};

enum MountedDuelSpells
{
    SPELL_ON_TOURNAMENT_MOUNT = 63034,
    SPELL_MOUNTED_DUEL        = 62875,
};

class spell_gen_tournament_duel : public SpellScriptLoader
{
    public:
        spell_gen_tournament_duel() : SpellScriptLoader("spell_gen_tournament_duel") { }

        class spell_gen_tournament_duel_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_tournament_duel_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ON_TOURNAMENT_MOUNT))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MOUNTED_DUEL))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* rider = GetCaster()->GetCharmer())
                {
                    if (Player* plrTarget = GetHitPlayer())
                    {
                        if (plrTarget->HasAura(SPELL_ON_TOURNAMENT_MOUNT) && plrTarget->GetVehicleBase())
                            rider->CastSpell(plrTarget, SPELL_MOUNTED_DUEL, true);
                    }
                    else if (Unit* unitTarget = GetHitUnit())
                    {
                        if (unitTarget->GetCharmer() && unitTarget->GetCharmer()->GetTypeId() == TYPEID_PLAYER && unitTarget->GetCharmer()->HasAura(SPELL_ON_TOURNAMENT_MOUNT))
                            rider->CastSpell(unitTarget->GetCharmer(), SPELL_MOUNTED_DUEL, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_tournament_duel_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_tournament_duel_SpellScript();
        }
};

enum TournamentMountsSpells
{
    SPELL_LANCE_EQUIPPED = 62853,
};

class spell_gen_summon_tournament_mount : public SpellScriptLoader
{
    public:
        spell_gen_summon_tournament_mount() : SpellScriptLoader("spell_gen_summon_tournament_mount") { }

        class spell_gen_summon_tournament_mount_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_summon_tournament_mount_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_LANCE_EQUIPPED))
                    return false;
                return true;
            }

            SpellCastResult CheckIfLanceEquiped()
            {
                if (GetCaster()->IsInDisallowedMountForm())
                    GetCaster()->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

                if (!GetCaster()->HasAura(SPELL_LANCE_EQUIPPED))
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gen_summon_tournament_mount_SpellScript::CheckIfLanceEquiped);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_summon_tournament_mount_SpellScript();
        }
};

enum TournamentPennantSpells
{
    SPELL_PENNANT_STORMWIND_ASPIRANT      = 62595,
    SPELL_PENNANT_STORMWIND_VALIANT       = 62596,
    SPELL_PENNANT_STORMWIND_CHAMPION      = 62594,
    SPELL_PENNANT_GNOMEREGAN_ASPIRANT     = 63394,
    SPELL_PENNANT_GNOMEREGAN_VALIANT      = 63395,
    SPELL_PENNANT_GNOMEREGAN_CHAMPION     = 63396,
    SPELL_PENNANT_SEN_JIN_ASPIRANT        = 63397,
    SPELL_PENNANT_SEN_JIN_VALIANT         = 63398,
    SPELL_PENNANT_SEN_JIN_CHAMPION        = 63399,
    SPELL_PENNANT_SILVERMOON_ASPIRANT     = 63401,
    SPELL_PENNANT_SILVERMOON_VALIANT      = 63402,
    SPELL_PENNANT_SILVERMOON_CHAMPION     = 63403,
    SPELL_PENNANT_DARNASSUS_ASPIRANT      = 63404,
    SPELL_PENNANT_DARNASSUS_VALIANT       = 63405,
    SPELL_PENNANT_DARNASSUS_CHAMPION      = 63406,
    SPELL_PENNANT_EXODAR_ASPIRANT         = 63421,
    SPELL_PENNANT_EXODAR_VALIANT          = 63422,
    SPELL_PENNANT_EXODAR_CHAMPION         = 63423,
    SPELL_PENNANT_IRONFORGE_ASPIRANT      = 63425,
    SPELL_PENNANT_IRONFORGE_VALIANT       = 63426,
    SPELL_PENNANT_IRONFORGE_CHAMPION      = 63427,
    SPELL_PENNANT_UNDERCITY_ASPIRANT      = 63428,
    SPELL_PENNANT_UNDERCITY_VALIANT       = 63429,
    SPELL_PENNANT_UNDERCITY_CHAMPION      = 63430,
    SPELL_PENNANT_ORGRIMMAR_ASPIRANT      = 63431,
    SPELL_PENNANT_ORGRIMMAR_VALIANT       = 63432,
    SPELL_PENNANT_ORGRIMMAR_CHAMPION      = 63433,
    SPELL_PENNANT_THUNDER_BLUFF_ASPIRANT  = 63434,
    SPELL_PENNANT_THUNDER_BLUFF_VALIANT   = 63435,
    SPELL_PENNANT_THUNDER_BLUFF_CHAMPION  = 63436,
    SPELL_PENNANT_ARGENT_CRUSADE_ASPIRANT = 63606,
    SPELL_PENNANT_ARGENT_CRUSADE_VALIANT  = 63500,
    SPELL_PENNANT_ARGENT_CRUSADE_CHAMPION = 63501,
    SPELL_PENNANT_EBON_BLADE_ASPIRANT     = 63607,
    SPELL_PENNANT_EBON_BLADE_VALIANT      = 63608,
    SPELL_PENNANT_EBON_BLADE_CHAMPION     = 63609,
};

enum TournamentMounts
{
    NPC_STORMWIND_STEED             = 33217,
    NPC_IRONFORGE_RAM               = 33316,
    NPC_GNOMEREGAN_MECHANOSTRIDER   = 33317,
    NPC_EXODAR_ELEKK                = 33318,
    NPC_DARNASSIAN_NIGHTSABER       = 33319,
    NPC_ORGRIMMAR_WOLF              = 33320,
    NPC_DARK_SPEAR_RAPTOR           = 33321,
    NPC_THUNDER_BLUFF_KODO          = 33322,
    NPC_SILVERMOON_HAWKSTRIDER      = 33323,
    NPC_FORSAKEN_WARHORSE           = 33324,
    NPC_ARGENT_WARHORSE             = 33782,
    NPC_ARGENT_STEED_ASPIRANT       = 33845,
    NPC_ARGENT_HAWKSTRIDER_ASPIRANT = 33844,
};

enum TournamentQuestsAchievements
{
    ACHIEVEMENT_CHAMPION_STORMWIND     = 2781,
    ACHIEVEMENT_CHAMPION_DARNASSUS     = 2777,
    ACHIEVEMENT_CHAMPION_IRONFORGE     = 2780,
    ACHIEVEMENT_CHAMPION_GNOMEREGAN    = 2779,
    ACHIEVEMENT_CHAMPION_THE_EXODAR    = 2778,
    ACHIEVEMENT_CHAMPION_ORGRIMMAR     = 2783,
    ACHIEVEMENT_CHAMPION_SEN_JIN       = 2784,
    ACHIEVEMENT_CHAMPION_THUNDER_BLUFF = 2786,
    ACHIEVEMENT_CHAMPION_UNDERCITY     = 2787,
    ACHIEVEMENT_CHAMPION_SILVERMOON    = 2785,
    ACHIEVEMENT_ARGENT_VALOR           = 2758,
    ACHIEVEMENT_CHAMPION_ALLIANCE      = 2782,
    ACHIEVEMENT_CHAMPION_HORDE         = 2788,

    QUEST_VALIANT_OF_STORMWIND         = 13593,
    QUEST_A_VALIANT_OF_STORMWIND       = 13684,
    QUEST_VALIANT_OF_DARNASSUS         = 13706,
    QUEST_A_VALIANT_OF_DARNASSUS       = 13689,
    QUEST_VALIANT_OF_IRONFORGE         = 13703,
    QUEST_A_VALIANT_OF_IRONFORGE       = 13685,
    QUEST_VALIANT_OF_GNOMEREGAN        = 13704,
    QUEST_A_VALIANT_OF_GNOMEREGAN      = 13688,
    QUEST_VALIANT_OF_THE_EXODAR        = 13705,
    QUEST_A_VALIANT_OF_THE_EXODAR      = 13690,
    QUEST_VALIANT_OF_ORGRIMMAR         = 13707,
    QUEST_A_VALIANT_OF_ORGRIMMAR       = 13691,
    QUEST_VALIANT_OF_SEN_JIN           = 13708,
    QUEST_A_VALIANT_OF_SEN_JIN         = 13693,
    QUEST_VALIANT_OF_THUNDER_BLUFF     = 13709,
    QUEST_A_VALIANT_OF_THUNDER_BLUFF   = 13694,
    QUEST_VALIANT_OF_UNDERCITY         = 13710,
    QUEST_A_VALIANT_OF_UNDERCITY       = 13695,
    QUEST_VALIANT_OF_SILVERMOON        = 13711,
    QUEST_A_VALIANT_OF_SILVERMOON      = 13696,
};

class spell_gen_on_tournament_mount : public SpellScriptLoader
{
    public:
        spell_gen_on_tournament_mount() : SpellScriptLoader("spell_gen_on_tournament_mount") { }

        class spell_gen_on_tournament_mount_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_on_tournament_mount_AuraScript);

            uint32 _pennantSpellId;

            bool Load()
            {
                _pennantSpellId = 0;
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* vehicle = caster->GetVehicleBase())
                    {
                        _pennantSpellId = GetPennatSpellId(caster->ToPlayer(), vehicle);
                        caster->CastSpell(caster, _pennantSpellId, true);
                    }
                }
            }

            void HandleRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    caster->RemoveAurasDueToSpell(_pennantSpellId);
            }

            uint32 GetPennatSpellId(Player* player, Unit* mount)
            {
                switch (mount->GetEntry())
                {
                    case NPC_ARGENT_STEED_ASPIRANT:
                    case NPC_STORMWIND_STEED:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_STORMWIND))
                            return SPELL_PENNANT_STORMWIND_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_STORMWIND) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_STORMWIND))
                            return SPELL_PENNANT_STORMWIND_VALIANT;
                        else
                            return SPELL_PENNANT_STORMWIND_ASPIRANT;
                    }
                    case NPC_GNOMEREGAN_MECHANOSTRIDER:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_GNOMEREGAN))
                            return SPELL_PENNANT_GNOMEREGAN_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_GNOMEREGAN) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_GNOMEREGAN))
                            return SPELL_PENNANT_GNOMEREGAN_VALIANT;
                        else
                            return SPELL_PENNANT_GNOMEREGAN_ASPIRANT;
                    }
                    case NPC_DARK_SPEAR_RAPTOR:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_SEN_JIN))
                            return SPELL_PENNANT_SEN_JIN_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_SEN_JIN) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_SEN_JIN))
                            return SPELL_PENNANT_SEN_JIN_VALIANT;
                        else
                            return SPELL_PENNANT_SEN_JIN_ASPIRANT;
                    }
                    case NPC_ARGENT_HAWKSTRIDER_ASPIRANT:
                    case NPC_SILVERMOON_HAWKSTRIDER:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_SILVERMOON))
                            return SPELL_PENNANT_SILVERMOON_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_SILVERMOON) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_SILVERMOON))
                            return SPELL_PENNANT_SILVERMOON_VALIANT;
                        else
                            return SPELL_PENNANT_SILVERMOON_ASPIRANT;
                    }
                    case NPC_DARNASSIAN_NIGHTSABER:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_DARNASSUS))
                            return SPELL_PENNANT_DARNASSUS_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_DARNASSUS) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_DARNASSUS))
                            return SPELL_PENNANT_DARNASSUS_VALIANT;
                        else
                            return SPELL_PENNANT_DARNASSUS_ASPIRANT;
                    }
                    case NPC_EXODAR_ELEKK:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_THE_EXODAR))
                            return SPELL_PENNANT_EXODAR_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_THE_EXODAR) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_THE_EXODAR))
                            return SPELL_PENNANT_EXODAR_VALIANT;
                        else
                            return SPELL_PENNANT_EXODAR_ASPIRANT;
                    }
                    case NPC_IRONFORGE_RAM:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_IRONFORGE))
                            return SPELL_PENNANT_IRONFORGE_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_IRONFORGE) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_IRONFORGE))
                            return SPELL_PENNANT_IRONFORGE_VALIANT;
                        else
                            return SPELL_PENNANT_IRONFORGE_ASPIRANT;
                    }
                    case NPC_FORSAKEN_WARHORSE:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_UNDERCITY))
                            return SPELL_PENNANT_UNDERCITY_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_UNDERCITY) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_UNDERCITY))
                            return SPELL_PENNANT_UNDERCITY_VALIANT;
                        else
                            return SPELL_PENNANT_UNDERCITY_ASPIRANT;
                    }
                    case NPC_ORGRIMMAR_WOLF:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_ORGRIMMAR))
                            return SPELL_PENNANT_ORGRIMMAR_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_ORGRIMMAR) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_ORGRIMMAR))
                            return SPELL_PENNANT_ORGRIMMAR_VALIANT;
                        else
                            return SPELL_PENNANT_ORGRIMMAR_ASPIRANT;
                    }
                    case NPC_THUNDER_BLUFF_KODO:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_THUNDER_BLUFF))
                            return SPELL_PENNANT_THUNDER_BLUFF_CHAMPION;
                        else if (player->GetQuestRewardStatus(QUEST_VALIANT_OF_THUNDER_BLUFF) || player->GetQuestRewardStatus(QUEST_A_VALIANT_OF_THUNDER_BLUFF))
                            return SPELL_PENNANT_THUNDER_BLUFF_VALIANT;
                        else
                            return SPELL_PENNANT_THUNDER_BLUFF_ASPIRANT;
                    }
                    case NPC_ARGENT_WARHORSE:
                    {
                        if (player->HasAchieved(ACHIEVEMENT_CHAMPION_ALLIANCE) || player->HasAchieved(ACHIEVEMENT_CHAMPION_HORDE))
                            return player->getClass() == CLASS_DEATH_KNIGHT ? SPELL_PENNANT_EBON_BLADE_CHAMPION : SPELL_PENNANT_ARGENT_CRUSADE_CHAMPION;
                        else if (player->HasAchieved(ACHIEVEMENT_ARGENT_VALOR))
                            return player->getClass() == CLASS_DEATH_KNIGHT ? SPELL_PENNANT_EBON_BLADE_VALIANT : SPELL_PENNANT_ARGENT_CRUSADE_VALIANT;
                        else
                            return player->getClass() == CLASS_DEATH_KNIGHT ? SPELL_PENNANT_EBON_BLADE_ASPIRANT : SPELL_PENNANT_ARGENT_CRUSADE_ASPIRANT;
                    }
                    default:
                        return 0;
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_gen_on_tournament_mount_AuraScript::HandleApplyEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_gen_on_tournament_mount_AuraScript::HandleRemoveEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_on_tournament_mount_AuraScript();
        }
};

class spell_gen_tournament_pennant : public SpellScriptLoader
{
    public:
        spell_gen_tournament_pennant() : SpellScriptLoader("spell_gen_tournament_pennant") { }

        class spell_gen_tournament_pennant_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_tournament_pennant_AuraScript);

            bool Load()
            {
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (!caster->GetVehicleBase())
                        caster->RemoveAurasDueToSpell(GetId());
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_gen_tournament_pennant_AuraScript::HandleApplyEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_tournament_pennant_AuraScript();
        }
};

enum ChaosBlast
{
    SPELL_CHAOS_BLAST   = 37675,
};

class spell_gen_chaos_blast : public SpellScriptLoader
{
    public:
        spell_gen_chaos_blast() : SpellScriptLoader("spell_gen_chaos_blast") { }

        class spell_gen_chaos_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_chaos_blast_SpellScript)

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CHAOS_BLAST))
                    return false;
                return true;
            }
            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                int32 basepoints0 = 100;
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                    caster->CastCustomSpell(target, SPELL_CHAOS_BLAST, &basepoints0, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_chaos_blast_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_chaos_blast_SpellScript();
        }

};

class spell_gen_ds_flush_knockback : public SpellScriptLoader
{
    public:
        spell_gen_ds_flush_knockback() : SpellScriptLoader("spell_gen_ds_flush_knockback") {}

        class spell_gen_ds_flush_knockback_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_ds_flush_knockback_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                // Here the target is the water spout and determines the position where the player is knocked from
                if (Unit* target = GetHitUnit())
                {
                    if (Player* player = GetCaster()->ToPlayer())
                    {
                        float horizontalSpeed = 20.0f + (40.0f - GetCaster()->GetDistance(target));
                        float verticalSpeed = 8.0f;
                        // This method relies on the Dalaran Sewer map disposition and Water Spout position
                        // What we do is knock the player from a position exactly behind him and at the end of the pipe
                        player->KnockbackFrom(target->GetPositionX(), player->GetPositionY(), horizontalSpeed, verticalSpeed);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_ds_flush_knockback_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_ds_flush_knockback_SpellScript();
        }
};

class spell_gen_wg_water : public SpellScriptLoader
{
    public:
        spell_gen_wg_water() : SpellScriptLoader("spell_gen_wg_water") {}

        class spell_gen_wg_water_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_wg_water_SpellScript);

            SpellCastResult CheckCast()
            {
                if (!GetSpellInfo()->CheckTargetCreatureType(GetCaster()))
                    return SPELL_FAILED_DONT_REPORT;
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gen_wg_water_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_wg_water_SpellScript();
        }
};

class spell_gen_count_pct_from_max_hp : public SpellScriptLoader
{
    public:
        spell_gen_count_pct_from_max_hp(char const* name, int32 damagePct = 0) : SpellScriptLoader(name), _damagePct(damagePct) { }

        class spell_gen_count_pct_from_max_hp_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_count_pct_from_max_hp_SpellScript)

        public:
            spell_gen_count_pct_from_max_hp_SpellScript(int32 damagePct) : SpellScript(), _damagePct(damagePct) { }

            void RecalculateDamage()
            {
                if (!_damagePct)
                    _damagePct = GetHitDamage();

                SetHitDamage(GetHitUnit()->CountPctFromMaxHealth(_damagePct));
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_gen_count_pct_from_max_hp_SpellScript::RecalculateDamage);
            }

        private:
            int32 _damagePct;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_count_pct_from_max_hp_SpellScript(_damagePct);
        }

    private:
        int32 _damagePct;
};

class spell_gen_despawn_self : public SpellScriptLoader
{
public:
    spell_gen_despawn_self() : SpellScriptLoader("spell_gen_despawn_self") { }

    class spell_gen_despawn_self_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gen_despawn_self_SpellScript);

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_UNIT;
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            if (GetSpellInfo()->Effects[effIndex].Effect == SPELL_EFFECT_DUMMY || GetSpellInfo()->Effects[effIndex].Effect == SPELL_EFFECT_SCRIPT_EFFECT)
                GetCaster()->ToCreature()->DespawnOrUnsummon();
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gen_despawn_self_SpellScript::HandleDummy, EFFECT_ALL, SPELL_EFFECT_ANY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_despawn_self_SpellScript();
    }
};

class spell_gen_touch_the_nightmare : public SpellScriptLoader
{
public:
    spell_gen_touch_the_nightmare() : SpellScriptLoader("spell_gen_touch_the_nightmare") { }

    class spell_gen_touch_the_nightmare_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gen_touch_the_nightmare_SpellScript);

        void HandleDamageCalc(SpellEffIndex /*effIndex*/)
        {
            uint32 bp = GetCaster()->GetMaxHealth() * 0.3f;
            SetHitDamage(bp);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gen_touch_the_nightmare_SpellScript::HandleDamageCalc, EFFECT_2, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_touch_the_nightmare_SpellScript();
    }
};

class spell_gen_dream_funnel: public SpellScriptLoader
{
public:
    spell_gen_dream_funnel() : SpellScriptLoader("spell_gen_dream_funnel") { }

    class spell_gen_dream_funnel_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_gen_dream_funnel_AuraScript);

        void HandleEffectCalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
        {
            if (GetCaster())
                amount = GetCaster()->GetMaxHealth() * 0.05f;

            canBeRecalculated = false;
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_dream_funnel_AuraScript::HandleEffectCalcAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_dream_funnel_AuraScript::HandleEffectCalcAmount, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_gen_dream_funnel_AuraScript();
    }
};

enum GenericBandage
{
    SPELL_RECENTLY_BANDAGED = 11196,
};

class spell_gen_bandage : public SpellScriptLoader
{
    public:
        spell_gen_bandage() : SpellScriptLoader("spell_gen_bandage") { }

        class spell_gen_bandage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_bandage_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_RECENTLY_BANDAGED))
                    return false;
                return true;
            }

            SpellCastResult CheckCast()
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->HasAura(SPELL_RECENTLY_BANDAGED))
                        return SPELL_FAILED_TARGET_AURASTATE;
                }
                return SPELL_CAST_OK;
            }

            void HandleScript()
            {
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, SPELL_RECENTLY_BANDAGED, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gen_bandage_SpellScript::CheckCast);
                AfterHit += SpellHitFn(spell_gen_bandage_SpellScript::HandleScript);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_bandage_SpellScript();
        }
};

enum GenericLifebloom
{
    SPELL_HEXLORD_MALACRASS_LIFEBLOOM_FINAL_HEAL        = 43422,
    SPELL_TUR_RAGEPAW_LIFEBLOOM_FINAL_HEAL              = 52552,
    SPELL_CENARION_SCOUT_LIFEBLOOM_FINAL_HEAL           = 53692,
    SPELL_TWISTED_VISAGE_LIFEBLOOM_FINAL_HEAL           = 57763,
    SPELL_FACTION_CHAMPIONS_DRU_LIFEBLOOM_FINAL_HEAL    = 66094,
};

class spell_gen_lifebloom : public SpellScriptLoader
{
    public:
        spell_gen_lifebloom(const char* name, uint32 spellId) : SpellScriptLoader(name), _spellId(spellId) { }

        class spell_gen_lifebloom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_lifebloom_AuraScript);

        public:
            spell_gen_lifebloom_AuraScript(uint32 spellId) : AuraScript(), _spellId(spellId) { }

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(_spellId))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                // Final heal only on duration end
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE && GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_ENEMY_SPELL)
                    return;

                // final heal
                GetTarget()->CastSpell(GetTarget(), _spellId, true, NULL, aurEff, GetCasterGUID());
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_gen_lifebloom_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
            }

        private:
            uint32 _spellId;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_lifebloom_AuraScript(_spellId);
        }

    private:
        uint32 _spellId;
};

enum SummonElemental
{
    SPELL_SUMMON_FIRE_ELEMENTAL  = 8985,
    SPELL_SUMMON_EARTH_ELEMENTAL = 19704
};

class spell_gen_summon_elemental : public SpellScriptLoader
{
    public:
        spell_gen_summon_elemental(const char* name, uint32 spellId) : SpellScriptLoader(name), _spellId(spellId) { }

        class spell_gen_summon_elemental_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_summon_elemental_AuraScript);

        public:
            spell_gen_summon_elemental_AuraScript(uint32 spellId) : AuraScript(), _spellId(spellId) { }

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(_spellId))
                    return false;
                return true;
            }

            void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster())
                    if (Unit* owner = GetCaster()->GetOwner())
                        owner->CastSpell(owner, _spellId, true);
            }

            void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster())
                    if (Unit* owner = GetCaster()->GetOwner())
                        if (owner->GetTypeId() == TYPEID_PLAYER) // todo: this check is maybe wrong
                            owner->ToPlayer()->RemoveCurrentPet();
            }

            void Register()
            {
                 AfterEffectApply += AuraEffectApplyFn(spell_gen_summon_elemental_AuraScript::AfterApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                 AfterEffectRemove += AuraEffectRemoveFn(spell_gen_summon_elemental_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }

        private:
            uint32 _spellId;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_summon_elemental_AuraScript(_spellId);
        }

    private:
        uint32 _spellId;
};

enum FoamSword
{
    ITEM_FOAM_SWORD_GREEN   = 45061,
    ITEM_FOAM_SWORD_PINK    = 45176,
    ITEM_FOAM_SWORD_BLUE    = 45177,
    ITEM_FOAM_SWORD_RED     = 45178,
    ITEM_FOAM_SWORD_YELLOW  = 45179,

    SPELL_BONKED            = 62991,
    SPELL_FOAM_SWORD_DEFEAT = 62994,
    SPELL_ON_GUARD          = 62972,
};

class spell_gen_upper_deck_create_foam_sword : public SpellScriptLoader
{
    public:
        spell_gen_upper_deck_create_foam_sword() : SpellScriptLoader("spell_gen_upper_deck_create_foam_sword") { }

        class spell_gen_upper_deck_create_foam_sword_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_upper_deck_create_foam_sword_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                if (Player* player = GetHitPlayer())
                {
                    static uint32 const itemId[5] = { ITEM_FOAM_SWORD_GREEN, ITEM_FOAM_SWORD_PINK, ITEM_FOAM_SWORD_BLUE, ITEM_FOAM_SWORD_RED, ITEM_FOAM_SWORD_YELLOW };
                    // player can only have one of these items
                    for (uint8 i = 0; i < 5; ++i)
                    {
                        if (player->HasItemCount(itemId[i], 1, true))
                            return;
                    }

                    CreateItem(effIndex, itemId[urand(0, 4)]);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_upper_deck_create_foam_sword_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_upper_deck_create_foam_sword_SpellScript();
        }
};

class spell_gen_bonked : public SpellScriptLoader
{
    public:
        spell_gen_bonked() : SpellScriptLoader("spell_gen_bonked") { }

        class spell_gen_bonked_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_bonked_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Player* target = GetHitPlayer())
                {
                    Aura const* aura = GetHitAura();
                    if (!(aura && aura->GetStackAmount() == 3))
                        return;

                    target->CastSpell(target, SPELL_FOAM_SWORD_DEFEAT, true);
                    target->RemoveAurasDueToSpell(SPELL_BONKED);

                    if (Aura const* aura = target->GetAura(SPELL_ON_GUARD))
                    {
                        if (Item* item = target->GetItemByGuid(aura->GetCastItemGUID()))
                            target->DestroyItemCount(item->GetEntry(), 1, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_bonked_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_bonked_SpellScript();
        }
};

class spell_gen_gift_of_naaru : public SpellScriptLoader
{
    public:
        spell_gen_gift_of_naaru() : SpellScriptLoader("spell_gen_gift_of_naaru") { }

        class spell_gen_gift_of_naaru_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_gift_of_naaru_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (!GetCaster())
                    return;

                float heal = 0.0f;
                switch (GetSpellInfo()->SpellFamilyName)
                {
                    case SPELLFAMILY_MAGE:
                    case SPELLFAMILY_WARLOCK:
                    case SPELLFAMILY_PRIEST:
                        heal = 1.885f * float(GetCaster()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()));
                        break;
                    case SPELLFAMILY_PALADIN:
                    case SPELLFAMILY_SHAMAN:
                        heal = std::max(1.885f * float(GetCaster()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask())), 1.1f * float(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK)));
                        break;
                    case SPELLFAMILY_WARRIOR:
                    case SPELLFAMILY_HUNTER:
                    case SPELLFAMILY_DEATHKNIGHT:
                        heal = 1.1f * float(std::max(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK), GetCaster()->GetTotalAttackPowerValue(RANGED_ATTACK)));
                        break;
                    case SPELLFAMILY_GENERIC:
                    default:
                        break;
                }

                int32 healTick = floor(heal / aurEff->GetTotalTicks());
                amount += int32(std::max(healTick, 0));
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_gift_of_naaru_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_gift_of_naaru_AuraScript();
        }
};

class spell_gen_increase_stats_buff : public SpellScriptLoader
{
    public:
        spell_gen_increase_stats_buff(char const* scriptName) : SpellScriptLoader(scriptName) { }

        class spell_gen_increase_stats_buff_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_increase_stats_buff_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player *caster;
                Player *target;

                if (Unit *_target = GetHitUnit())
                    target = _target->ToPlayer();

                if (Unit *_caster = GetCaster())
                    caster = _caster->ToPlayer();

                if (!target || !caster)
                    return;

                if (Group *cgroup = caster->GetGroup())
                {
                    if (Group *tgroup = target->GetGroup())
                        if (tgroup->GetGUID() == cgroup->GetGUID())
                        {
                            caster->CastSpell(target, GetEffectValue() + 1, true);
                            cgroup->BuffApplied(caster->GetGUID(), GetEffectValue() + 1);
                            return;
                        }
                }

                if (target->GetGUID() == caster->GetGUID())
                {
                    caster->CastSpell(target, GetEffectValue() + 1, true);
                    return;
                }

                caster->CastSpell(target, GetEffectValue(), true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_increase_stats_buff_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_increase_stats_buff_SpellScript();
        }
};

enum RaidHasteSpellsBuffsAndDebuffs
{
    SPELL_BUFF_BLOODLUST                = 2825,
    SPELL_DEBUFF_SATED                  = 57724,

    SPELL_BUFF_HEROISM                  = 32182,
    SPELL_DEBUFF_EXHAUSTION             = 57723,

    SPELL_BUFF_TIME_WARP                = 80353,
    SPELL_DEBUFF_TEMPORAL_DISPLACEMENT  = 80354,

    SPELL_BUFF_ANCIENT_HYSTERIA         = 90355,
    SPELL_DEBUFF_INSANITY               = 95809,
};

// Filter targets for Ancient Hysteria, Bloodlust, Heroism, and Time Warp.
class spell_gen_raid_haste : public SpellScriptLoader
{
public:
    spell_gen_raid_haste(char const* scriptName) : SpellScriptLoader(scriptName) { }

    class spell_gen_raid_SPELL_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gen_raid_SPELL_SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DEBUFF_SATED) ||
                !sSpellMgr->GetSpellInfo(SPELL_DEBUFF_EXHAUSTION) ||
                !sSpellMgr->GetSpellInfo(SPELL_DEBUFF_TEMPORAL_DISPLACEMENT) ||
                !sSpellMgr->GetSpellInfo(SPELL_DEBUFF_INSANITY))
                return false;
            return true;
        }

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_DEBUFF_SATED));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_DEBUFF_EXHAUSTION));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_DEBUFF_TEMPORAL_DISPLACEMENT));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_DEBUFF_INSANITY));
        }

        void ApplyDebuff()
        {
            switch (GetSpellInfo()->Id)
            {
                case SPELL_BUFF_BLOODLUST:
                    GetHitUnit()->CastSpell(GetHitUnit(), SPELL_DEBUFF_SATED, true);
                    break;
                case SPELL_BUFF_HEROISM:
                    GetHitUnit()->CastSpell(GetHitUnit(), SPELL_DEBUFF_EXHAUSTION, true);
                    break;
                case SPELL_BUFF_TIME_WARP:
                    GetHitUnit()->CastSpell(GetHitUnit(), SPELL_DEBUFF_TEMPORAL_DISPLACEMENT, true);
                    break;
                case SPELL_BUFF_ANCIENT_HYSTERIA:
                    GetHitUnit()->CastSpell(GetHitUnit(), SPELL_DEBUFF_INSANITY, true);
                    break;
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gen_raid_SPELL_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gen_raid_SPELL_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gen_raid_SPELL_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
            AfterHit += SpellHitFn(spell_gen_raid_SPELL_SpellScript::ApplyDebuff);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_raid_SPELL_SpellScript();
    }
};

enum Replenishment
{
    SPELL_REPLENISHMENT             = 57669,
    SPELL_INFINITE_REPLENISHMENT    = 61782
};

class spell_gen_replenishment : public SpellScriptLoader
{
    public:
        spell_gen_replenishment() : SpellScriptLoader("spell_gen_replenishment") { }

        class spell_gen_replenishment_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_replenishment_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_REPLENISHMENT) ||
                   !sSpellMgr->GetSpellInfo(SPELL_INFINITE_REPLENISHMENT))
                    return false;
                return true;
            }

            bool Load()
            {
                return GetUnitOwner()->GetPower(POWER_MANA);
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                switch (GetSpellInfo()->Id)
                {
                    case SPELL_REPLENISHMENT:
                        amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.01f;
                        break;
                    case SPELL_INFINITE_REPLENISHMENT:
                        amount = GetUnitOwner()->GetMaxPower(POWER_MANA) * 0.001f;
                        break;
                    default:
                        break;
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_replenishment_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_replenishment_AuraScript();
        }
};

enum RunningWildMountIds
{
    RUNNING_WILD_MODEL_MALE     = 29422,
    RUNNING_WILD_MODEL_FEMALE   = 29423,
    SPELL_ALTERED_FORM          = 97709,
};

class spell_gen_running_wild : public SpellScriptLoader
{
    public:
        spell_gen_running_wild() : SpellScriptLoader("spell_gen_running_wild") { }

        class spell_gen_running_wild_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_running_wild_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sCreatureDisplayInfoStore.LookupEntry(RUNNING_WILD_MODEL_MALE))
                    return false;
                if (!sCreatureDisplayInfoStore.LookupEntry(RUNNING_WILD_MODEL_FEMALE))
                    return false;
                return true;
            }

            void HandleMount(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                PreventDefaultAction();

                target->Mount(target->getGender() == GENDER_FEMALE ? RUNNING_WILD_MODEL_FEMALE : RUNNING_WILD_MODEL_MALE, 0, 0);

                // cast speed aura
                if (MountCapabilityEntry const* mountCapability = sMountCapabilityStore.LookupEntry(aurEff->GetAmount()))
                    target->CastSpell(target, mountCapability->SpeedModSpell, TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_gen_running_wild_AuraScript::HandleMount, EFFECT_1, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL);
            }
        };

        class spell_gen_running_wild_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_running_wild_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ALTERED_FORM))
                    return false;
                return true;
            }

            bool Load()
            {
                // Definitely not a good thing, but currently the only way to do something at cast start
                // Should be replaced as soon as possible with a new hook: BeforeCastStart
                GetCaster()->CastSpell(GetCaster(), SPELL_ALTERED_FORM, TRIGGERED_FULL_MASK);
                return false;
            }

            void Register()
            {
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_running_wild_AuraScript();
        }

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_running_wild_SpellScript();
        }
};

class spell_gen_two_forms : public SpellScriptLoader
{
    public:
        spell_gen_two_forms() : SpellScriptLoader("spell_gen_two_forms") { }

        class spell_gen_two_forms_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_two_forms_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->isInCombat())
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_CANT_TRANSFORM);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                // Player cannot transform to human form if he is forced to be worgen for some reason (Darkflight)
                if (GetCaster()->GetAuraEffectsByType(SPELL_AURA_WORGEN_ALTERED_FORM).size() > 1)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_CANT_TRANSFORM);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleTransform(SpellEffIndex effIndex)
            {
                Unit* target = GetHitUnit();
                PreventHitDefaultEffect(effIndex);
                if (target->HasAuraType(SPELL_AURA_WORGEN_ALTERED_FORM))
                    target->RemoveAurasByType(SPELL_AURA_WORGEN_ALTERED_FORM);
                else    // Basepoints 1 for this aura control whether to trigger transform transition animation or not.
                    target->CastCustomSpell(SPELL_ALTERED_FORM, SPELLVALUE_BASE_POINT0, 1, target, TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gen_two_forms_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_gen_two_forms_SpellScript::HandleTransform, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_two_forms_SpellScript();
        }
};

class spell_gen_darkflight : public SpellScriptLoader
{
    public:
        spell_gen_darkflight() : SpellScriptLoader("spell_gen_darkflight") { }

        class spell_gen_darkflight_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_darkflight_SpellScript);

            void TriggerTransform()
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_ALTERED_FORM, TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_gen_darkflight_SpellScript::TriggerTransform);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_darkflight_SpellScript();
        }
};

enum ArmorSpecialization
{
    // Leather
    SPELL_DRUID_ARMOR_SPECIALIZATION        = 86530,
    SPELL_ROGUE_ARMOR_SPECIALIZATION        = 86531,
    // Mail
    SPELL_SHAMAN_ARMOR_SPECIALIZATION       = 86529,
    SPELL_HUNTER_ARMOR_SPECIALIZATION       = 86528,
    // Plate
    SPELL_PALADIN_ARMOR_SPECIALIZATION      = 86525,
    SPELL_DK_ARMOR_SPECIALIZATION           = 86524,
    SPELL_WARRIOR_ARMOR_SPECIALIZATION      = 86526
};

class spell_gen_armor_specialization : public SpellScriptLoader
{
    public:
        spell_gen_armor_specialization(char* scriptName) : SpellScriptLoader(scriptName) { }

        class spell_gen_armor_specialization_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_armor_specialization_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* player = GetHitPlayer();
                if (!player)
                    return;

                uint32 spellId = 0;

                switch(player->GetPrimaryTalentTree(player->GetActiveSpec()))
                {
                    case TALENT_TREE_WARRIOR_ARMS:
                        spellId = 86110;
                        break;
                    case TALENT_TREE_WARRIOR_FURY:
                        spellId = 86101;
                        break;
                    case TALENT_TREE_WARRIOR_PROTECTION:
                        spellId = 86535;
                        break;
                    case TALENT_TREE_PALADIN_HOLY:
                        spellId = 86103;
                        break;
                    case TALENT_TREE_PALADIN_PROTECTION:
                        spellId = 86102;
                        break;
                    case TALENT_TREE_PALADIN_RETRIBUTION:
                        spellId = 86539;
                        break;
                    case TALENT_TREE_HUNTER_BEAST_MASTERY:
                    case TALENT_TREE_HUNTER_MARKSMANSHIP:
                    case TALENT_TREE_HUNTER_SURVIVAL:
                        spellId = 86538;
                        break;
                    case TALENT_TREE_ROGUE_ASSASSINATION:
                    case TALENT_TREE_ROGUE_COMBAT:
                    case TALENT_TREE_ROGUE_SUBTLETY:
                        spellId = 86092;
                        break;
                    case TALENT_TREE_DEATH_KNIGHT_BLOOD:
                        spellId = 86537;
                        break;
                    case TALENT_TREE_DEATH_KNIGHT_FROST:
                        spellId = 86536;
                        break;
                    case TALENT_TREE_DEATH_KNIGHT_UNHOLY:
                        spellId = 86113;
                        break;
                    case TALENT_TREE_SHAMAN_ELEMENTAL:
                        spellId = 86100;
                        break;
                    case TALENT_TREE_SHAMAN_ENHANCEMENT:
                        spellId = 86099;
                        break;
                    case TALENT_TREE_SHAMAN_RESTORATION:
                        spellId = 86108;
                        break;
                    case TALENT_TREE_DRUID_BALANCE:
                        spellId = 86093;
                        break;
                    case TALENT_TREE_DRUID_FERAL_COMBAT:
                    {
                        if(player->GetShapeshiftForm() == FORM_BEAR)
                            spellId = 86096;
                        else
                            spellId = 86097;
                        break;
                    }
                    case TALENT_TREE_DRUID_RESTORATION:
                        spellId = 86104;
                        break;
                    default:
                        return;
                }

                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
                if (spellInfo && player->HasItemFitToSpellRequirements(spellInfo))
                    player->CastSpell(player, spellId, TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_armor_specialization_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_armor_specialization_SpellScript();
        }
};

class spell_mage_dalaran_brilliance : public SpellScriptLoader
{
public:
    spell_mage_dalaran_brilliance() : SpellScriptLoader("spell_mage_dalaran_brilliance") { }

    class spell_mage_dalaran_brilliance_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_dalaran_brilliance_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetHitUnit()->IsInRaidWith(GetCaster()))
                GetCaster()->CastSpell(GetCaster(), GetEffectValue() - 1, true); // raid buff
            else
                GetCaster()->CastSpell(GetHitUnit(), GetEffectValue(), true); // single-target buff
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_mage_dalaran_brilliance_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_dalaran_brilliance_SpellScript();
    }
};

class spell_log_in_effect : public SpellScriptLoader
{
public:
    spell_log_in_effect() : SpellScriptLoader("spell_log_in_effect") { }

    class spell_log_in_effect_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_log_in_effect_SpellScript);

        void HandleLogIn(SpellEffIndex /*effIndex*/)
        {
            // Reset Checks
            if (Unit* caster = GetCaster())
            {
                caster->m_ragganFlag = 0;
                caster->m_teklaFlag = 0;
                caster->m_mishaFlag = 0;
                caster->m_zentajiFlag = 0;
            }

            if (Player* player = GetCaster()->ToPlayer())
            {
                // Vengeance of Elune
                if (player->HasAura(65602))
                    player->CastSpell(player, 66166, false);

                // Lilith Controller
                if (player->HasAura(91391))
                    player->RemoveAurasDueToSpell(91391);

                // Zul'Gurub Mind Vision
                if (player->HasAura(79821))
                {
                    if (player->GetTeam() == TEAM_ALLIANCE)
                        player->CastWithDelay(2000, player, 82399);
                    else
                        player->CastWithDelay(2000, player, 82401);

                    player->RemoveAurasDueToSpell(79821);
                }

                // Getting In With the Bloodsail: Set Bloodsail Faction Friendly
                if (player->HasAura(81310))
                {
                    player->RemoveAurasDueToSpell(81310);
                    player->CastSpell(player, 81310, true);
                }

                // Quest Giver
                if (player->HasAura(88476))
                    player->RemoveAurasDueToSpell(88476);

                // Ride Skeletal Steed
                if (player->HasAura(88543))
                    player->RemoveAurasDueToSpell(88543);

                // Quest Chain: Protocol (Hillsbrad Foothills)
                if (player->IsActiveQuest(28230) || player->IsActiveQuest(28235) || player->IsActiveQuest(28237) || player->IsActiveQuest(28251))
                {
                    player->CastSpell(player, 89296, true);
                    player->CastSpell(player, 89295, true);
                }

                // Studies in Lethality
                if (player->HasAura(88375))
                {
                    player->RemoveAurasDueToSpell(88375);
                    if (player->GetQuestStatus(28324) == QUEST_STATUS_INCOMPLETE)
                        player->CastSpell(player, 88375, true);
                }

                // Quest Chain: The Road to Purgation
                if (player->HasAura(90132) || player->GetQuestStatus(28375) == QUEST_STATUS_COMPLETE || player->GetQuestStatus(28397) == QUEST_STATUS_COMPLETE ||
                    (player->GetQuestStatus(28375) == QUEST_STATUS_REWARDED && player->GetQuestStatus(28397) == QUEST_STATUS_NONE))
                {
                    player->RemoveAurasDueToSpell(90132);
                    player->CastSpell(player, 90132, true);
                }
                if (player->HasAura(90205) || player->GetQuestStatus(28400) == QUEST_STATUS_INCOMPLETE || (player->GetQuestStatus(28400) == QUEST_STATUS_NONE && player->GetQuestStatus(28397) == QUEST_STATUS_REWARDED))
                {
                    player->RemoveAurasDueToSpell(90132);
                    player->RemoveAurasDueToSpell(90205);
                    player->CastSpell(player, 90414, true);
                    player->CastSpell(player, 90205, true);
                }

                // Summon Messner
                if (player->HasAura(80893))
                    player->RemoveAurasDueToSpell(80893);
                // Summon Jorgensen
                if (player->HasAura(80940))
                    player->RemoveAurasDueToSpell(80940);
                // Summon Krakauer
                if (player->HasAura(80941))
                    player->RemoveAurasDueToSpell(80941);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_log_in_effect_SpellScript::HandleLogIn, EFFECT_0, SPELL_EFFECT_SPAWN);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_log_in_effect_SpellScript();
    }
};

class spell_funeral_offering : public SpellScriptLoader
{
public:
    spell_funeral_offering() : SpellScriptLoader("spell_funeral_offering") { }

    class spell_funeral_offering_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_funeral_offering_SpellScript);

        enum Id
        {
            NPC_GREATMOTHER_HAWKIND = 2991,
            QUEST_LAST_RITES_FIRST_RITES = 24861
        };

        void HandleDummy()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (caster->ToPlayer()->GetQuestStatus(QUEST_LAST_RITES_FIRST_RITES) == QUEST_STATUS_INCOMPLETE)
                        caster->ToPlayer()->CompleteQuest(QUEST_LAST_RITES_FIRST_RITES);
                }
            }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_funeral_offering_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_funeral_offering_SpellScript();
    }
};

class spell_bloodtalon_whistle : public SpellScriptLoader
{
public:
    spell_bloodtalon_whistle() : SpellScriptLoader("spell_bloodtalon_whistle") { }

    class spell_bloodtalon_whistle_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bloodtalon_whistle_SpellScript);

        enum Id
        {
            NPC_BLOODTALON_HATCHLING            = 37960,
            NPC_LOST_BLOODTALON_HATCHLING       = 39157,
            QUEST_SAVING_THE_YOUNG              = 24623,
            QUEST_CREDIT_BLOODTALON             = 39157,
            NPC_FACTION_TROLL                   = 877
        };

        void HandleDummy()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (caster->ToPlayer()->GetQuestStatus(QUEST_SAVING_THE_YOUNG) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (Creature* hatchling = caster->FindNearestCreature(NPC_BLOODTALON_HATCHLING, 15.0f, true))
                        {
                            if (hatchling->getFaction() == NPC_FACTION_TROLL)
                                return;

                            hatchling->GetMotionMaster()->MoveFollow(caster, 2.5f, caster->GetOrientation());
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_BLOODTALON);
                            hatchling->DespawnOrUnsummon(5000);
                            hatchling->setFaction(NPC_FACTION_TROLL);
                        }
                        if (Creature* lostHatchling = caster->FindNearestCreature(NPC_LOST_BLOODTALON_HATCHLING, 15.0f, true))
                        {
                            if (lostHatchling->getFaction() == NPC_FACTION_TROLL)
                                return;

                            lostHatchling->GetMotionMaster()->MoveFollow(caster, 2.5f, caster->GetOrientation());
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_BLOODTALON);
                            lostHatchling->DespawnOrUnsummon(5000);
                            lostHatchling->setFaction(NPC_FACTION_TROLL);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_bloodtalon_whistle_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bloodtalon_whistle_SpellScript();
    }
};

class spell_bloodtalon_lasso : public SpellScriptLoader
{
public:
    spell_bloodtalon_lasso() : SpellScriptLoader("spell_bloodtalon_lasso") { }

    class spell_bloodtalon_lasso_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bloodtalon_lasso_SpellScript);

        enum Id
        {
            NPC_SWIFTCLAW                       = 37989,
            QUEST_YOUNG_AND_VICIOUS             = 24626,
            QUEST_CREDIT_BLOODTALON_RIDE        = 37989,
            QUEST_CREDIT_BLOODTALON_ESCORTED    = 38002
        };

        void HandleDummy()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (caster->ToPlayer()->GetQuestStatus(QUEST_YOUNG_AND_VICIOUS) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (Creature* swiftclaw = caster->FindNearestCreature(NPC_SWIFTCLAW, 10.0f, true))
                        {
                            caster->EnterVehicle(swiftclaw, 0);
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_BLOODTALON_RIDE);
                            swiftclaw->AI()->Talk(0);
                            swiftclaw->SetReactState(REACT_PASSIVE);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_bloodtalon_lasso_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bloodtalon_lasso_SpellScript();
    }
};

class spell_territorial_fetish : public SpellScriptLoader
{
    public:
        spell_territorial_fetish() : SpellScriptLoader("spell_territorial_fetish") { }

        enum Id
        {
            GO_SPITESCALE_FLAG          = 202113,
            NPC_SPITESCALE_FLAG         = 38560,
            SPELL_TERRITORIAL_FETISH    = 72072
        };

        class spell_territorial_fetish_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_territorial_fetish_SpellScript);

            SpellCastResult CheckCast()
            {
                GameObject* spitescaleFlag = GetCaster()->FindNearestGameObject(GO_SPITESCALE_FLAG, 2.0f);
                if (spitescaleFlag)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleApplyMask(SpellEffIndex effIndex)
            {
                if (Unit* spitescaleFlag = GetCaster()->FindNearestCreature(NPC_SPITESCALE_FLAG, 2.0f))
                    spitescaleFlag->CastSpell(spitescaleFlag, SPELL_TERRITORIAL_FETISH);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_territorial_fetish_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_territorial_fetish_SpellScript::HandleApplyMask, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_territorial_fetish_SpellScript();
        }
};

class spell_thonk_spyglass : public SpellScriptLoader
{
    public:
        spell_thonk_spyglass() : SpellScriptLoader("spell_thonk_spyglass") { }

        enum Id
        {
            NPC_THONK                   = 39323,
            NPC_CAMERA_RAGGARAN         = 39320,
            NPC_CAMERA_TEKLA            = 39345,
            NPC_CAMERA_MISHA            = 39346,
            NPC_CAMERA_ZENTAJI          = 39347,
            SPELL_JUMP_IN_CAMERA        = 83788   // Check for correct ID
        };

        class spell_thonk_spyglass_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_thonk_spyglass_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* thonk = GetCaster()->FindNearestCreature(NPC_THONK, 3.0f);
                if (thonk)
                    return SPELL_CAST_OK;

                return SPELL_FAILED_NOT_HERE;
            }

            void HandleStartCinematic(SpellEffIndex effIndex)
            {
                if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                {
                    Unit* raggaranCamera = GetCaster()->FindNearestCreature(NPC_CAMERA_RAGGARAN, 10.0f);
                    Unit* teklaCamera = GetCaster()->FindNearestCreature(NPC_CAMERA_TEKLA, 10.0f);
                    Unit* mishaCamera = GetCaster()->FindNearestCreature(NPC_CAMERA_MISHA, 10.0f);
                    Unit* zentajiCamera = GetCaster()->FindNearestCreature(NPC_CAMERA_ZENTAJI, 10.0f);

                    if (GetCaster()->m_ragganFlag == 0)
                    {
                        GetCaster()->SummonCreature(NPC_CAMERA_RAGGARAN, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ());
                        if (raggaranCamera)
                        {
                            raggaranCamera->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                            GetCaster()->CastSpell(raggaranCamera, SPELL_JUMP_IN_CAMERA, true);
                            GetCaster()->m_ragganFlag = 1;
                        }
                        return;
                    }
                    if (GetCaster()->m_ragganFlag > 0 && GetCaster()->m_teklaFlag == 0)
                    {
                        GetCaster()->SummonCreature(NPC_CAMERA_TEKLA, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ());
                        if (teklaCamera)
                        {
                            teklaCamera->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                            GetCaster()->CastSpell(teklaCamera, SPELL_JUMP_IN_CAMERA, true);
                            GetCaster()->m_teklaFlag = 1;
                        }
                        return;
                    }
                    if (GetCaster()->m_ragganFlag > 0 && GetCaster()->m_teklaFlag > 0 && GetCaster()->m_mishaFlag == 0)
                    {
                        GetCaster()->SummonCreature(NPC_CAMERA_MISHA, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ());
                        if (mishaCamera)
                        {
                            mishaCamera->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                            GetCaster()->CastSpell(mishaCamera, SPELL_JUMP_IN_CAMERA, true);
                            GetCaster()->m_mishaFlag = 1;
                        }
                        return;
                    }
                    if (GetCaster()->m_ragganFlag > 0 && GetCaster()->m_teklaFlag > 0 && GetCaster()->m_mishaFlag > 0 && GetCaster()->m_zentajiFlag == 0)
                    {
                        GetCaster()->SummonCreature(NPC_CAMERA_ZENTAJI, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ());
                        if (zentajiCamera)
                        {
                            zentajiCamera->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                            GetCaster()->CastSpell(zentajiCamera, SPELL_JUMP_IN_CAMERA, true);
                            GetCaster()->m_zentajiFlag = 1;
                        }
                        return;
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_thonk_spyglass_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_thonk_spyglass_SpellScript::HandleStartCinematic, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_thonk_spyglass_SpellScript();
        }
};

class spell_burn_constriction_totem : public SpellScriptLoader
{
    public:
        spell_burn_constriction_totem() : SpellScriptLoader("spell_burn_constriction_totem") { }

        enum Id
        {
            NPC_CONSTRICTION_TOTEM              = 41202,
            SPELL_BURN_CONSTRICTION_TOTEM       = 77314
        };

        class spell_burn_constriction_totem_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_burn_constriction_totem_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* constrictionTotem = GetCaster()->FindNearestCreature(NPC_CONSTRICTION_TOTEM, 2.0f);
                if (constrictionTotem)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleBurnTotem(SpellEffIndex effIndex)
            {
                if (Creature* constrictionTotem = GetCaster()->FindNearestCreature(NPC_CONSTRICTION_TOTEM, 2.0f))
                {
                    constrictionTotem->CastSpell(constrictionTotem, SPELL_BURN_CONSTRICTION_TOTEM);
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_CONSTRICTION_TOTEM);
                    constrictionTotem->Kill(constrictionTotem, false);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_burn_constriction_totem_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_burn_constriction_totem_SpellScript::HandleBurnTotem, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_burn_constriction_totem_SpellScript();
        }
};

class spell_rune_of_return : public SpellScriptLoader
{
    public:
        spell_rune_of_return() : SpellScriptLoader("spell_rune_of_return") { }

        enum Id
        {
            NPC_TRAPPED_MINER                   = 41671,
            SPELL_RUNE_OF_RETURN                = 77819
        };

        class spell_rune_of_return_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rune_of_return_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* trappedMiner = GetCaster()->FindNearestCreature(NPC_TRAPPED_MINER, 2.0f);
                if (trappedMiner)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleReturnRune(SpellEffIndex effIndex)
            {
                if (Creature* trappedMiner = GetCaster()->FindNearestCreature(NPC_TRAPPED_MINER, 2.0f))
                {
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_TRAPPED_MINER);
                    trappedMiner->AI()->Talk(0);
                    trappedMiner->DespawnOrUnsummon(3000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_rune_of_return_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_rune_of_return_SpellScript::HandleReturnRune, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rune_of_return_SpellScript();
        }
};

class spell_signal_flare : public SpellScriptLoader
{
    public:
        spell_signal_flare() : SpellScriptLoader("spell_signal_flare") { }

        enum Id
        {
            NPC_COVERT_OPS_FLYING_MACHINE           = 41382,
            SPELL_SIGNAL_FLARE                      = 77488,
            ZONE_TRIGGER                            = 182090,
            NPC_INVISIBLE_TRIGGER                   = 144952,
            QUEST_CREDIT_SOUTH                      = 41373,
            QUEST_CREDIT_NORTH                      = 41372
        };

        class spell_signal_flare_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_signal_flare_SpellScript);

            SpellCastResult CheckCast()
            {
                GameObject* zoneTrigger = GetCaster()->FindNearestGameObject(ZONE_TRIGGER, 100.0f);
                if (zoneTrigger)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleCallCovertOps(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    GameObject* zoneTrigger = GetCaster()->FindNearestGameObject(ZONE_TRIGGER, 100.0f);
                    if (zoneTrigger)
                    {
                        caster->SummonCreature(NPC_COVERT_OPS_FLYING_MACHINE, caster->GetPositionX(), caster->GetPositionY()+5, caster->GetPositionZ()+8, caster->GetOrientation());
                        caster->SummonCreature(NPC_COVERT_OPS_FLYING_MACHINE, caster->GetPositionX(), caster->GetPositionY()-5, caster->GetPositionZ()+8, caster->GetOrientation());
                        caster->SummonCreature(NPC_INVISIBLE_TRIGGER, zoneTrigger->GetPositionX(), zoneTrigger->GetPositionY(), zoneTrigger->GetPositionZ(), zoneTrigger->GetOrientation())->UnSummon(20000);
                        switch (zoneTrigger->GetGUIDLow())
                        {
                            case 68749:
                            case 68750:
                                caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_SOUTH);
                                break;
                            case 68740:
                            case 68742:
                            case 68743:
                            case 68744:
                                caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_NORTH);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_signal_flare_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_signal_flare_SpellScript::HandleCallCovertOps, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_signal_flare_SpellScript();
        }
};

class spell_extinguish_fire : public SpellScriptLoader
{
    public:
        spell_extinguish_fire() : SpellScriptLoader("spell_extinguish_fire") { }

        enum Id
        {
            NPC_FIRE_TRIGGER    = 42046
        };

        class spell_extinguish_fire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_extinguish_fire_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* fireTrigger = GetCaster()->FindNearestCreature(NPC_FIRE_TRIGGER, 5.0f);
                if (fireTrigger)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleExtinguishFire(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Creature* fire = caster->FindNearestCreature(NPC_FIRE_TRIGGER, 5.0f))
                    {
                        caster->ToPlayer()->KilledMonsterCredit(NPC_FIRE_TRIGGER);
                        fire->DespawnOrUnsummon(1);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_extinguish_fire_SpellScript::CheckCast);
                OnEffectHit += SpellEffectFn(spell_extinguish_fire_SpellScript::HandleExtinguishFire, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_extinguish_fire_SpellScript();
        }
};

class spell_ironforge_banner : public SpellScriptLoader
{
    public:
        spell_ironforge_banner() : SpellScriptLoader("spell_ironforge_banner") { }

        enum Id
        {
            GO_LOOSE_SNOW           = 203452,
            GO_IRONFORGE_BANNER     = 203451
        };

        class spell_ironforge_banner_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ironforge_banner_SpellScript);

            void HandlePlantBanner(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (GameObject* looseSnow = caster->FindNearestGameObject(GO_LOOSE_SNOW, 10.0f))
                        caster->SummonGameObject(GO_IRONFORGE_BANNER, looseSnow->GetPositionX(), looseSnow->GetPositionY(), looseSnow->GetPositionZ(), looseSnow->GetOrientation(), 0, 0, 0, 0, 10);
                }
                return;
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_ironforge_banner_SpellScript::HandlePlantBanner, EFFECT_0, SPELL_EFFECT_TRANS_DOOR);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ironforge_banner_SpellScript();
        }
};

class spell_cancel_vengeance_of_elune : public SpellScriptLoader
{
    public:
        spell_cancel_vengeance_of_elune() : SpellScriptLoader("spell_cancel_vengeance_of_elune") { }

        enum Id
        {
            SPELL_VENGEANCE_OF_ELUNE        = 65602
        };

        class spell_cancel_vengeance_of_elune_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_cancel_vengeance_of_elune_SpellScript);

            void HandleRemover(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                    GetHitUnit()->RemoveAurasDueToSpell(SPELL_VENGEANCE_OF_ELUNE);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_cancel_vengeance_of_elune_SpellScript::HandleRemover, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_cancel_vengeance_of_elune_SpellScript();
        }
};

class spell_moonsurge : public SpellScriptLoader
{
    public:
        spell_moonsurge() : SpellScriptLoader("spell_moonsurge") { }

        enum Id
        {
            NPC_SHATTERSPEAR_BUILDING_TRIGGER   = 33913
        };

        class spell_moonsurge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_moonsurge_SpellScript);

            void HandleCheckTrigger()
            {
                if (Unit* caster = GetCaster())
                {
                    if (!caster->GetCharmerOrOwner())
                        return;

                    if (caster->GetCharmerOrOwner()->GetTypeId() != TYPEID_PLAYER)
                        return;

                    Unit* trigger = caster->FindNearestCreature(NPC_SHATTERSPEAR_BUILDING_TRIGGER, 8.0f, true);
                    if (trigger)
                        caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(NPC_SHATTERSPEAR_BUILDING_TRIGGER);
                }
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_moonsurge_SpellScript::HandleCheckTrigger);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_moonsurge_SpellScript();
        }
};

class spell_shattershield_arrow : public SpellScriptLoader
{
    public:
        spell_shattershield_arrow() : SpellScriptLoader("spell_shattershield_arrow") { }

        enum Id
        {
            NPC_JOR_KIL_THE_SOULRIPPER        = 32862,
            SPELL_AEGIS_OF_THE_SHATTERSPEAR   = 64549
        };

        class spell_shattershield_arrow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shattershield_arrow_SpellScript);

            void HandleRemover(SpellEffIndex effIndex)
            {
                if (!GetCaster())
                    return;

                if (Unit* target = GetCaster()->FindNearestCreature(NPC_JOR_KIL_THE_SOULRIPPER, 100.0f, true))
                {
                    target->Attack(GetCaster(), true);
                    target->RemoveAllAuras();
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_shattershield_arrow_SpellScript::HandleRemover, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_shattershield_arrow_SpellScript();
        }
};

class spell_petrified_root : public SpellScriptLoader
{
    public:
        spell_petrified_root() : SpellScriptLoader("spell_petrified_root") { }

        enum Id
        {
            NPC_DARKSCALE_SCOUT    = 33206,
            QUEST_CREDIT_ENT       = 34010
        };

        class spell_petrified_root_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_petrified_root_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* darkscaleScout = GetCaster()->FindNearestCreature(NPC_DARKSCALE_SCOUT, 0.5f, false);
                if (darkscaleScout)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleSummonEnt(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Creature* darkscaleScout = GetCaster()->FindNearestCreature(NPC_DARKSCALE_SCOUT, 0.5f, false))
                    {
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ENT);
                        darkscaleScout->DespawnOrUnsummon(1);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_petrified_root_SpellScript::CheckCast);
                OnEffectHit += SpellEffectFn(spell_petrified_root_SpellScript::HandleSummonEnt, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_petrified_root_SpellScript();
        }
};

class spell_torch_shatterspear_supplies : public SpellScriptLoader
{
    public:
        spell_torch_shatterspear_supplies() : SpellScriptLoader("spell_torch_shatterspear_supplies") { }

        enum Id
        {
            NPC_SUPPLIES_TRIGGER        = 33056,
            SPELL_SHATTERSPEAR_BUFF     = 62624
        };

        class spell_torch_shatterspear_supplies_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_torch_shatterspear_supplies_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* suppliesTrigger = GetCaster()->FindNearestCreature(NPC_SUPPLIES_TRIGGER, 5.0f);
                if (suppliesTrigger && !suppliesTrigger->HasAura(SPELL_SHATTERSPEAR_BUFF))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleBurnSupplies()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Creature* supplies = caster->FindNearestCreature(NPC_SUPPLIES_TRIGGER, 5.0f))
                    {
                        supplies->AddAura(SPELL_SHATTERSPEAR_BUFF, supplies);
                        caster->ToPlayer()->KilledMonsterCredit(NPC_SUPPLIES_TRIGGER);
                    }
                }
                return;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_torch_shatterspear_supplies_SpellScript::CheckCast);
                OnCast += SpellCastFn(spell_torch_shatterspear_supplies_SpellScript::HandleBurnSupplies);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_torch_shatterspear_supplies_SpellScript();
        }
};

class spell_elune_presence : public SpellScriptLoader
{
    public:
        spell_elune_presence() : SpellScriptLoader("spell_elune_presence") { }

        enum Id
        {
            NPC_ENRAGED_TIDAL_SPIRIT        = 32890
        };

        class spell_elune_presence_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_elune_presence_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* tidalSpirit = GetCaster()->FindNearestCreature(NPC_ENRAGED_TIDAL_SPIRIT, 1.0f, false);
                if (tidalSpirit)
                {
                    tidalSpirit->DespawnOrUnsummon(6000);
                    return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_elune_presence_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_elune_presence_SpellScript();
        }
};

class spell_frenzied_cyclone_braciers : public SpellScriptLoader
{
    public:
        spell_frenzied_cyclone_braciers() : SpellScriptLoader("spell_frenzied_cyclone_braciers") { }

        enum Id
        {
            GO_AUBERDINE_MOONWELL        = 174795,
        };

        class spell_frenzied_cyclone_braciers_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_frenzied_cyclone_braciers_SpellScript);

            SpellCastResult CheckCast()
            {
                GameObject* auberdineMoonwell = GetCaster()->FindNearestGameObject(GO_AUBERDINE_MOONWELL, 5.0f);
                if (auberdineMoonwell)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_frenzied_cyclone_braciers_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_frenzied_cyclone_braciers_SpellScript();
        }
};

class spell_constructing : public SpellScriptLoader
{
    public:
        spell_constructing() : SpellScriptLoader("spell_constructing") { }

        enum Id
        {
            SPELL_CONSTRUCTING          = 65275
        };

        class spell_constructing_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_constructing_SpellScript);

            void HandleBuildHut()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->CastSpell(caster, SPELL_CONSTRUCTING, false);
                }
                return;
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_constructing_SpellScript::HandleBuildHut);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_constructing_SpellScript();
        }
};

class spell_constructing_spawning : public SpellScriptLoader
{
    public:
        spell_constructing_spawning() : SpellScriptLoader("spell_constructing_spawning") { }

        enum Id
        {
            GO_GREYMIST_MURLOC_HUT_1            = 195044,
            GO_GREYMIST_MURLOC_HUT_2            = 195045,
            GO_MURLOC_BUILD_SITE                = 195043
        };

        class spell_constructing_spawning_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_constructing_spawning_SpellScript);

            void HandleSpawnHut()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    GameObject* murlocHut1 = caster->FindNearestGameObject(GO_GREYMIST_MURLOC_HUT_1, 50.0f);
                    GameObject* murlocHut2 = caster->FindNearestGameObject(GO_GREYMIST_MURLOC_HUT_2, 50.0f);

                    if (murlocHut1)
                        murlocHut1->RemoveFromWorld();

                    for (int i = 0; i < 2; i++)
                    {
                        if (murlocHut2)
                            murlocHut2->RemoveFromWorld();
                    }

                    if (GameObject* murlocSite = caster->FindNearestGameObject(GO_MURLOC_BUILD_SITE, 20.0f))
                        murlocSite->SummonGameObject(GO_GREYMIST_MURLOC_HUT_1, 4690.67f, 695.279f, 1.15692f, 3.927f, 0, 0, 0, 0, 40);
                }
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_constructing_spawning_SpellScript::HandleSpawnHut);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_constructing_spawning_SpellScript();
        }
};

class spell_ping_for_artifacts : public SpellScriptLoader
{
    public:
        spell_ping_for_artifacts() : SpellScriptLoader("spell_ping_for_artifacts") { }

        class spell_ping_for_artifacts_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ping_for_artifacts_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetZoneId() == 148 && GetCaster()->GetAreaId() == 450)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_ping_for_artifacts_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ping_for_artifacts_SpellScript();
        }
};

class spell_disrupting_the_artifact : public SpellScriptLoader
{
    public:
        spell_disrupting_the_artifact() : SpellScriptLoader("spell_disrupting_the_artifact") { }

        enum Id
        {
            GO_DEVOURING_ARTIFACT = 195057
        };

        class spell_disrupting_the_artifact_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_disrupting_the_artifact_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GameObject* devouringArtifact = GetCaster()->FindNearestGameObject(GO_DEVOURING_ARTIFACT, 50.0f))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_disrupting_the_artifact_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_disrupting_the_artifact_SpellScript();
        }
};

class spell_horn_of_the_ancients : public SpellScriptLoader
{
    public:
        spell_horn_of_the_ancients() : SpellScriptLoader("spell_horn_of_the_ancients") { }

        enum Id
        {
            // Zone ID
            ID_AREA_MASTER_GLAIVE = 449,
            ID_ZONE_DARKSHORE     = 148,

            // Npc
            NPC_AWAKENED_ANCIENT  = 34486,
            NPC_AVATAR_OF_SOGGOTH = 34485
        };

        class spell_horn_of_the_ancients_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_horn_of_the_ancients_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetZoneId() == ID_ZONE_DARKSHORE && GetCaster()->GetAreaId() == ID_AREA_MASTER_GLAIVE)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleSpawns()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->SummonCreature(NPC_AWAKENED_ANCIENT, caster->GetPositionX(), caster->GetPositionY()+4, caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30);
                    caster->SummonCreature(NPC_AWAKENED_ANCIENT, caster->GetPositionX(), caster->GetPositionY()+6, caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30);
                    caster->SummonCreature(NPC_AWAKENED_ANCIENT, caster->GetPositionX(), caster->GetPositionY()-4, caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30);
                    caster->SummonCreature(NPC_AWAKENED_ANCIENT, caster->GetPositionX(), caster->GetPositionY()-6, caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30);
                    caster->SummonCreature(NPC_AVATAR_OF_SOGGOTH, caster->GetPositionX()+6, caster->GetPositionY(), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_horn_of_the_ancients_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_horn_of_the_ancients_SpellScript::HandleSpawns);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_horn_of_the_ancients_SpellScript();
        }
};

class spell_calling_the_caravan : public SpellScriptLoader
{
    public:
        spell_calling_the_caravan() : SpellScriptLoader("spell_calling_the_caravan") { }

        enum Id
        {
            // Npc
            NPC_HALGA_BLOODEYE          = 34258,
            NPC_ROCCO_CROSSROADS        = 34578,
            NPC_ROCCO_MORSHAN           = 52220,
            NPC_NAGALA_WHIPSHANK        = 52207,
            NPC_FAR_WATCH_CARAVAN_KODO  = 34432,
            NPC_LEAD_CARAVAN_KODO       = 34430,
            NPC_HEAD_CARAVAN_KODO       = 34577,
            NPC_CROSSROADS_CARAVAN_KODO = 34576,
            NPC_CARAVAN_CART            = 52316,
            NPC_CARAVAN_KODO_MORSHAN    = 52212,
            NPC_MASTER_CARAVAN_KODO     = 52314,

            // Sound
            SOUND_PLAY_CALL_CARAVAN     = 3980
        };

        class spell_calling_the_caravan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_calling_the_caravan_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* leadCaravan = GetCaster()->FindNearestCreature(NPC_LEAD_CARAVAN_KODO, 30.0f, true))
                {
                    if (leadCaravan->GetPhaseMask() == 1)
                        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                }
                if (Creature* headCaravan = GetCaster()->FindNearestCreature(NPC_HEAD_CARAVAN_KODO, 30.0f, true))
                {
                    if (headCaravan->GetPhaseMask() == 1)
                        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                }
                return SPELL_CAST_OK;
            }

            void HandleSummonCaravans()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->PlayDirectSound(SOUND_PLAY_CALL_CARAVAN);
                    if (caster->GetTypeId() != TYPEID_PLAYER && caster->ToCreature())
                    {
                        switch (caster->ToCreature()->GetEntry())
                        {
                            // Halga Bloodeye
                            case NPC_HALGA_BLOODEYE:
                                caster->SummonCreature(NPC_FAR_WATCH_CARAVAN_KODO, 314.76f, -3711.60f, 26.56f, 1.49f);
                                caster->SummonCreature(NPC_LEAD_CARAVAN_KODO, 316.35f, -3699.61f, 26.88f, 1.43f);
                                break;
                            // Rocco Whipshank (To Crossroads)
                            case NPC_ROCCO_CROSSROADS:
                                caster->SummonCreature(NPC_HEAD_CARAVAN_KODO, 219.23f, -2964.53f, 91.88f, 2.73f);
                                caster->SummonCreature(NPC_CROSSROADS_CARAVAN_KODO, 228.73f, -2970.47f, 91.89f, 2.57f);
                                break;
                            case NPC_ROCCO_MORSHAN:
                                caster->SummonCreature(NPC_CARAVAN_CART, -379.23f, -2679.30f, 95.76f, 6.18f);
                                break;
                            case NPC_NAGALA_WHIPSHANK:
                                caster->SummonCreature(NPC_MASTER_CARAVAN_KODO, 315.03f, -2541.74f, 91.69f, 3.11f);
                                caster->SummonCreature(NPC_CARAVAN_KODO_MORSHAN, 329.21f, -2541.01f, 91.90f, 3.20f);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_calling_the_caravan_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_calling_the_caravan_SpellScript::HandleSummonCaravans);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_calling_the_caravan_SpellScript();
        }
};

class spell_snared_in_net : public SpellScriptLoader
{
    public:
        spell_snared_in_net() : SpellScriptLoader("spell_snared_in_net") { }

        class spell_snared_in_net_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_snared_in_net_SpellScript);

            enum Id
            {
                SPELL_COSMETIC_CHAINS       = 88964,
                SPELL_GROL_DOM_NET          = 65581,
                SPELL_DRAGGING_RAZORMANE    = 65601,
                SPELL_SNARE_SECONDARY       = 65609
            };

            void HandleAdditionalEffect(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                {
                    GetCaster()->CastSpell(GetCaster(), SPELL_DRAGGING_RAZORMANE, true);
                    GetCaster()->CastSpell(target, SPELL_COSMETIC_CHAINS, true);
                    GetCaster()->CastSpell(target, SPELL_GROL_DOM_NET, true);
                    GetCaster()->RemoveAurasDueToSpell(SPELL_GROL_DOM_NET);
                    target->CastSpell(target, SPELL_GROL_DOM_NET, target);
                    target->SetStandState(UNIT_STAND_STATE_DEAD);
                    target->GetMotionMaster()->MoveChase(GetCaster(), 2.0f, GetCaster()->GetOrientation());
                    target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_snared_in_net_SpellScript::HandleAdditionalEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_snared_in_net_SpellScript();
        }
};

class spell_snared_secondary_effect : public SpellScriptLoader
{
    public:
        spell_snared_secondary_effect() : SpellScriptLoader("spell_snared_secondary_effect") { }

        class spell_snared_secondary_effect_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_snared_secondary_effect_SpellScript);

            enum Id
            {
                SPELL_COSMETIC_CHAINS       = 88964,
                SPELL_GROL_DOM_NET          = 65581
            };

            void HandleCleanup(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (!target->HasAura(SPELL_GROL_DOM_NET))
                        return;

                    target->SetStandState(UNIT_STAND_STATE_STAND);
                    target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                    target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    target->RemoveAurasDueToSpell(SPELL_COSMETIC_CHAINS);
                    target->RemoveAurasDueToSpell(SPELL_GROL_DOM_NET);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_snared_secondary_effect_SpellScript::HandleCleanup, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_snared_secondary_effect_SpellScript();
        }
};

class spell_placing_raptor_feather : public SpellScriptLoader
{
    public:
        spell_placing_raptor_feather() : SpellScriptLoader("spell_placing_raptor_feather") { }

        class spell_placing_raptor_feather_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_placing_raptor_feather_SpellScript);

            enum Id
            {
                // GameObject
                GO_RAPTOR_FEATHER           = 195317,

                // Npc
                NPC_RAPTOR_NEST_BUNNY       = 34967,

                // GUID
                GUID_NEST_RED_BUNNY         = 149797,
                GUID_NEST_YELLOW_BUNNY      = 149725,
                GUID_NEST_BLUE_BUNNY        = 149808,

                // Credits
                CREDIT_RED_BUNNY            = 34964,
                CREDIT_YELLOW_BUNNY         = 34962,
                CREDIT_BLUE_BUNNY           = 34963
            };

            SpellCastResult CheckCast()
            {
                if (Creature* nestBunny = GetCaster()->FindNearestCreature(NPC_RAPTOR_NEST_BUNNY, 5.0f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleSpawnFeather()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (Creature* nestBunny = caster->FindNearestCreature(NPC_RAPTOR_NEST_BUNNY, 5.0f, true))
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    switch (nestBunny->GetGUIDLow())
                    {
                        case GUID_NEST_RED_BUNNY:
                        {
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_RED_BUNNY);
                            break;
                        }
                        case GUID_NEST_YELLOW_BUNNY:
                        {
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_YELLOW_BUNNY);
                            break;
                        }
                        case GUID_NEST_BLUE_BUNNY:
                        {
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_BLUE_BUNNY);
                            break;
                        }
                        default:
                            break;
                    }

                    caster->SummonGameObject(GO_RAPTOR_FEATHER, nestBunny->GetPositionX(), nestBunny->GetPositionY(), nestBunny->GetPositionZ()-1, nestBunny->GetOrientation(), 0, 0, 0, 0, NULL);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_placing_raptor_feather_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_placing_raptor_feather_SpellScript::HandleSpawnFeather);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_placing_raptor_feather_SpellScript();
        }
};

class spell_summon_echeyakee : public SpellScriptLoader
{
    public:
        spell_summon_echeyakee() : SpellScriptLoader("spell_summon_echeyakee") { }

        class spell_summon_echeyakee_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_echeyakee_SpellScript);

            enum Id
            {
                // Npc
                NPC_ECHEYAKEE       = 3475
            };

            void HandleSummonEcheyakee()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                caster->SummonCreature(NPC_ECHEYAKEE, -21.51f, -2358.14f, 91.66f, 4.68f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_summon_echeyakee_SpellScript::HandleSummonEcheyakee);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_echeyakee_SpellScript();
        }
};

class spell_waptor_twap_scweech : public SpellScriptLoader
{
    public:
        spell_waptor_twap_scweech() : SpellScriptLoader("spell_waptor_twap_scweech") { }

        class spell_waptor_twap_scweech_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_waptor_twap_scweech_SpellScript);

            enum Id
            {
                // Npc
                NPC_SUNSCALE_SCYTHECLAW       = 3256,
                NPC_SUNSCALE_RAVAGER          = 44164
            };

            void HandleAttractRaptor()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (caster->GetTypeId() == TYPEID_UNIT && caster->ToCreature())
                {
                    if (Creature* raptor = caster->FindNearestCreature(NPC_SUNSCALE_SCYTHECLAW, 35.0f, true))
                        raptor->GetMotionMaster()->MoveChase(caster, 0.5f);
                    else if (Creature* raptor = caster->FindNearestCreature(NPC_SUNSCALE_RAVAGER, 35.0f, true))
                        raptor->GetMotionMaster()->MoveChase(caster, 0.5f);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_waptor_twap_scweech_SpellScript::HandleAttractRaptor);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_waptor_twap_scweech_SpellScript();
        }
};

class spell_waptor_shrink : public SpellScriptLoader
{
    public:
        spell_waptor_shrink() : SpellScriptLoader("spell_waptor_shrink") { }

        class spell_waptor_shrink_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_waptor_shrink_SpellScript);

            enum Id
            {
                SPELL_TWAP_FILLED   = 66286
            };

            void HandleDespawn()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (caster->GetTypeId() == TYPEID_UNIT && caster->ToCreature())
                {
                    caster->CastSpell(caster, SPELL_TWAP_FILLED, true);
                    caster->ToCreature()->DespawnOrUnsummon(1000);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_waptor_shrink_SpellScript::HandleDespawn);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_waptor_shrink_SpellScript();
        }
};

class spell_pirate_signal_horn : public SpellScriptLoader
{
    public:
        spell_pirate_signal_horn() : SpellScriptLoader("spell_pirate_signal_horn") { }

        enum Id
        {
            // Npc
            NPC_SOUTHSEA_MUTINEER  = 34790,
            NPC_TONY_TWO_TUSK      = 34749
        };

        class spell_pirate_signal_horn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pirate_signal_horn_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetMapId() == 1 && caster->GetZoneId() == 17 && caster->GetAreaId() == 720)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleSummonMutineers()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->SummonCreature(NPC_SOUTHSEA_MUTINEER, caster->GetPositionX(), caster->GetPositionY()+2, caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    caster->SummonCreature(NPC_SOUTHSEA_MUTINEER, caster->GetPositionX(), caster->GetPositionY()-2, caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    caster->SummonCreature(NPC_TONY_TWO_TUSK, caster->GetPositionX()+2, caster->GetPositionY(), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_pirate_signal_horn_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_pirate_signal_horn_SpellScript::HandleSummonMutineers);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pirate_signal_horn_SpellScript();
        }
};

class spell_apply_salve : public SpellScriptLoader
{
    public:
        spell_apply_salve() : SpellScriptLoader("spell_apply_salve") { }

        class spell_apply_salve_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_apply_salve_SpellScript);

            enum Id
            {
                NPC_WOUNDED_DEFENDER    = 33266
            };

            SpellCastResult CheckCast()
            {
                if (Creature* woundedDefender = GetCaster()->FindNearestCreature(NPC_WOUNDED_DEFENDER, 0.20f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_OUT_OF_RANGE;
            }

            void HandleApplySalve()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                // Wounded Mor'shan Defender
                if (Creature* woundedDefender = caster->FindNearestCreature(NPC_WOUNDED_DEFENDER, 0.20f, true))
                {
                    woundedDefender->AI()->TalkWithDelay(1500, 0);
                    woundedDefender->DespawnOrUnsummon(4500);
                    woundedDefender->HandleEmoteCommand(EMOTE_STATE_STAND);
                    caster->ToPlayer()->KilledMonsterCredit(NPC_WOUNDED_DEFENDER);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_apply_salve_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_apply_salve_SpellScript::HandleApplySalve);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_apply_salve_SpellScript();
        }
};

class spell_summon_brutusk_2 : public SpellScriptLoader
{
    public:
        spell_summon_brutusk_2() : SpellScriptLoader("spell_summon_brutusk_2") { }

        class spell_summon_brutusk_2_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_brutusk_2_SpellScript);

            enum Id
            {
                // Sound
                SOUND_PLAY_CALL_BRUTUSK = 3980,
                EMOTE_CALL_BRUTUSK      = 7
            };

            void HandlePlaySound()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                caster->PlayDirectSound(SOUND_PLAY_CALL_BRUTUSK);
                caster->HandleEmoteCommand(EMOTE_CALL_BRUTUSK);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_summon_brutusk_2_SpellScript::HandlePlaySound);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_brutusk_2_SpellScript();
        }
};

class spell_summon_gorat_spirit : public SpellScriptLoader
{
    public:
        spell_summon_gorat_spirit() : SpellScriptLoader("spell_summon_gorat_spirit") { }

        class spell_summon_gorat_spirit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_gorat_spirit_SpellScript);

            enum Id
            {
                NPC_GORAT_CORPSE    = 33294
            };

            SpellCastResult CheckCast()
            {
                if (Creature* goratCorpse = GetCaster()->FindNearestCreature(NPC_GORAT_CORPSE, 0.6f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_gorat_spirit_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_gorat_spirit_SpellScript();
        }
};

class spell_summon_burning_blade_flyer : public SpellScriptLoader
{
    public:
        spell_summon_burning_blade_flyer() : SpellScriptLoader("spell_summon_burning_blade_flyer") { }

        class spell_summon_burning_blade_flyer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_burning_blade_flyer_SpellScript);

            enum Id
            {
                // Sound
                SOUND_PLAY_CALL_FLYER   = 3980,
                EMOTE_CALL_FLYER        = 7
            };

            void HandlePlaySound()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (caster->GetTypeId() == TYPEID_UNIT && caster->ToCreature())
                {
                    caster->PlayDirectSound(SOUND_PLAY_CALL_FLYER);
                    caster->HandleEmoteCommand(EMOTE_CALL_FLYER);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_summon_burning_blade_flyer_SpellScript::HandlePlaySound);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_burning_blade_flyer_SpellScript();
        }
};

class spell_cancel_imp_disguise : public SpellScriptLoader
{
    public:
        spell_cancel_imp_disguise() : SpellScriptLoader("spell_cancel_imp_disguise") { }

        class spell_cancel_imp_disguise_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_cancel_imp_disguise_SpellScript);

            enum Id
            {
                SPELL_IMP_DISGUISE       = 63704
            };

            void HandleRemoveDisguise(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (!target->HasAura(SPELL_IMP_DISGUISE))
                        return;

                    target->RemoveAurasDueToSpell(SPELL_IMP_DISGUISE);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_cancel_imp_disguise_SpellScript::HandleRemoveDisguise, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_cancel_imp_disguise_SpellScript();
        }
};

class spell_throw_accursed_ore : public SpellScriptLoader
{
    public:
        spell_throw_accursed_ore() : SpellScriptLoader("spell_throw_accursed_ore") { }

        class spell_throw_accursed_ore_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_throw_accursed_ore_SpellScript);

            enum Id
            {
                NPC_TOWER_TRIGGER       = 33697,
                NPC_TOWER_TRIGGER_GUID  = 177717
            };

            SpellCastResult CheckCast()
            {
                if (Creature* towerTrigger = GetCaster()->FindNearestCreature(NPC_TOWER_TRIGGER, 200.0f, true))
                {
                    if (towerTrigger->GetGUIDLow() == NPC_TOWER_TRIGGER_GUID)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_throw_accursed_ore_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_throw_accursed_ore_SpellScript();
        }
};

class spell_throw_blood : public SpellScriptLoader
{
    public:
        spell_throw_blood() : SpellScriptLoader("spell_throw_blood") { }

        class spell_throw_blood_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_throw_blood_SpellScript);

            enum Id
            {
                GO_THE_FOREST_HEART    = 194549
            };

            SpellCastResult CheckCast()
            {
                if (GameObject* forestHeart = GetCaster()->FindNearestGameObject(GO_THE_FOREST_HEART, 2.0f))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_throw_blood_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_throw_blood_SpellScript();
        }
};

class spell_throw_signal_powder : public SpellScriptLoader
{
    public:
        spell_throw_signal_powder() : SpellScriptLoader("spell_throw_signal_powder") { }

        class spell_throw_signal_powder_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_throw_signal_powder_SpellScript);

            enum Id
            {
                NPC_SMOLDERING_BRAZIER_TRIGGER  = 33859
            };

            SpellCastResult CheckCast()
            {
                if (Creature* smolderingBrazier = GetCaster()->FindNearestCreature(NPC_SMOLDERING_BRAZIER_TRIGGER, 2.0f))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_throw_signal_powder_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_throw_signal_powder_SpellScript();
        }
};

class spell_chop_tree : public SpellScriptLoader
{
    public:
        spell_chop_tree() : SpellScriptLoader("spell_chop_tree") { }

        class spell_chop_tree_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_chop_tree_SpellScript);

            enum Id
            {
                NPC_SPLINTERTREE_OAK  = 34167,
                QUEST_CREDIT_OAK      = 34138
            };

            SpellCastResult CheckCast()
            {
                if (Creature* splintertreeOak = GetCaster()->FindNearestCreature(NPC_SPLINTERTREE_OAK, 2.0f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleChopDown()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Creature* splintertreeOak = GetCaster()->FindNearestCreature(NPC_SPLINTERTREE_OAK, 3.0f, true))
                        {
                            splintertreeOak->Kill(splintertreeOak, false);
                            GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_OAK);
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_chop_tree_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_chop_tree_SpellScript::HandleChopDown);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_chop_tree_SpellScript();
        }
};

class spell_gift_of_the_earth : public SpellScriptLoader
{
    public:
        spell_gift_of_the_earth() : SpellScriptLoader("spell_gift_of_the_earth") { }

        class spell_gift_of_the_earth_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gift_of_the_earth_SpellScript);

            enum Id
            {
                NPC_LAVA_FISSURE            = 43242,
                SPELL_GIFT_OF_THE_EARTH     = 65132
            };

            SpellCastResult CheckCast()
            {
                if (Creature* lavaFissure = GetCaster()->FindNearestCreature(NPC_LAVA_FISSURE, 3.0f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleCastSecondGift()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Creature* lavaFissure = caster->FindNearestCreature(NPC_LAVA_FISSURE, 5.0f, true))
                            caster->CastSpell(lavaFissure, SPELL_GIFT_OF_THE_EARTH, false);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gift_of_the_earth_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_gift_of_the_earth_SpellScript::HandleCastSecondGift);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gift_of_the_earth_SpellScript();
        }
};

class spell_gift_of_the_earth_second : public SpellScriptLoader
{
    public:
        spell_gift_of_the_earth_second() : SpellScriptLoader("spell_gift_of_the_earth_second") { }

        class spell_gift_of_the_earth_second_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gift_of_the_earth_second_SpellScript);

            enum Id
            {
                NPC_LAVA_FISSURE    = 43242,
            };

            void HandleCloseFissure()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Creature* lavaFissure = caster->FindNearestCreature(NPC_LAVA_FISSURE, 3.0f, true))
                        {
                            caster->Kill(lavaFissure, false);
                            caster->ToPlayer()->KilledMonsterCredit(NPC_LAVA_FISSURE);
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_gift_of_the_earth_second_SpellScript::HandleCloseFissure);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gift_of_the_earth_second_SpellScript();
        }
};

class spell_return_to_the_vortex : public SpellScriptLoader
{
    public:
        spell_return_to_the_vortex() : SpellScriptLoader("spell_return_to_the_vortex") { }

        class spell_return_to_the_vortex_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_return_to_the_vortex_SpellScript);

            enum Id
            {
                NPC_LORD_MAGMATHAR  = 34295
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    Creature* lordMagmatharAlive = caster->FindNearestCreature(NPC_LORD_MAGMATHAR, 150.0f, true);
                    Creature* lordMagmatharDead = caster->FindNearestCreature(NPC_LORD_MAGMATHAR, 150.0f, false);
                    if (lordMagmatharAlive || lordMagmatharDead)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleReturnMovement()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        caster->GetMotionMaster()->MovePoint(2, 2489.92f, -1318.29f, 135.18f, false);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_return_to_the_vortex_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_return_to_the_vortex_SpellScript::HandleReturnMovement);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_return_to_the_vortex_SpellScript();
        }
};

class spell_return_to_base : public SpellScriptLoader
{
    public:
        spell_return_to_base() : SpellScriptLoader("spell_return_to_base") { }

        class spell_return_to_base_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_return_to_base_SpellScript);

            void HandleReturnMovement()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                    {
                        caster->GetMotionMaster()->Clear();
                        caster->GetMotionMaster()->MovePoint(9, 3043.52f, -503.67f, 217.05f, true);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_return_to_base_SpellScript::HandleReturnMovement);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_return_to_base_SpellScript();
        }
};

class spell_unbathed_concotion : public SpellScriptLoader
{
    public:
        spell_unbathed_concotion() : SpellScriptLoader("spell_unbathed_concotion") { }

        class spell_unbathed_concotion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_unbathed_concotion_SpellScript);

            enum Id
            {
                GO_LIGHT_OF_ELUNE    = 194651
            };

            SpellCastResult CheckCast()
            {
                if (GameObject* lightOfElune = GetCaster()->FindNearestGameObject(GO_LIGHT_OF_ELUNE, 6.0f))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_unbathed_concotion_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_unbathed_concotion_SpellScript();
        }
};

class spell_cleanse_elune_tear : public SpellScriptLoader
{
    public:
        spell_cleanse_elune_tear() : SpellScriptLoader("spell_cleanse_elune_tear") { }

        class spell_cleanse_elune_tear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_cleanse_elune_tear_SpellScript);

            enum Id
            {
                NPC_MOONWELL_OF_PURITY_TRIGGER      = 25670,
                MOONWELL_OF_PURITY_TRIGGER_GUID     = 177232,
                NPC_AVRUS_ILLWHISPER                = 34335,
                SPELL_SEE_INVISIBILITY_QUEST_1      = 65315
            };

            SpellCastResult CheckCast()
            {
                if (Creature* lightOfElune = GetCaster()->FindNearestCreature(NPC_MOONWELL_OF_PURITY_TRIGGER, 6.0f))
                {
                    if (lightOfElune->GetGUIDLow() == MOONWELL_OF_PURITY_TRIGGER_GUID)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleSpawnQuestEnder()
            {
                if (Unit* caster = GetCaster())
                {
                    Creature* avrus = caster->FindNearestCreature(NPC_AVRUS_ILLWHISPER, 50.0f);
                    if (!avrus)
                        caster->SummonCreature(NPC_AVRUS_ILLWHISPER, 2897.87f, -1387.34f, 207.33f, 6.05f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(120000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_cleanse_elune_tear_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_cleanse_elune_tear_SpellScript::HandleSpawnQuestEnder);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_cleanse_elune_tear_SpellScript();
        }
};

class spell_playing_possum : public SpellScriptLoader
{
    public:
        spell_playing_possum() : SpellScriptLoader("spell_playing_possum") { }

        class spell_playing_possum_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_playing_possum_SpellScript);

            enum Id
            {
                NPC_ORSO_BRAMBLESCAR                = 34499,
                SPELL_PLAYING_POSSUM                = 65535
            };

            void HandlePossumEffect()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* orsoBramblescar = caster->FindNearestCreature(NPC_ORSO_BRAMBLESCAR, 50.0f, true))
                        orsoBramblescar->AddAura(SPELL_PLAYING_POSSUM, orsoBramblescar);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_playing_possum_SpellScript::HandlePossumEffect);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_playing_possum_SpellScript();
        }
};

class spell_summon_lou_house : public SpellScriptLoader
{
    public:
        spell_summon_lou_house() : SpellScriptLoader("spell_summon_lou_house") { }

        class spell_summon_lou_house_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_lou_house_SpellScript);

            enum Id
            {
                GO_TRIGGER_JANGOLODE_MINE   = 1731,
                GO_TRIGGER_MINE_GUID        = 7973
            };

            SpellCastResult CheckCast()
            {
                if (GameObject* mineTrigger = GetCaster()->FindNearestGameObject(GO_TRIGGER_JANGOLODE_MINE, 15.0f))
                {
                    if (mineTrigger->GetGUIDLow() == GO_TRIGGER_MINE_GUID)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_lou_house_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_lou_house_SpellScript();
        }
};

class spell_wake_harvest_golem : public SpellScriptLoader
{
    public:
        spell_wake_harvest_golem() : SpellScriptLoader("spell_wake_harvest_golem") { }

        class spell_wake_harvest_golem_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_wake_harvest_golem_SpellScript);

            enum Id
            {
                NPC_ENTRY_OVERLOADED_HARVEST_GOLEM  = 42381
            };

            SpellCastResult CheckCast()
            {
                if (Creature* overloadedGolem = GetCaster()->FindNearestCreature(NPC_ENTRY_OVERLOADED_HARVEST_GOLEM, 5.0f, true))
                    return SPELL_CAST_OK;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_wake_harvest_golem_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_wake_harvest_golem_SpellScript();
        }
};

class spell_vision_of_the_past_deadmines : public SpellScriptLoader
{
    public:
        spell_vision_of_the_past_deadmines() : SpellScriptLoader("spell_vision_of_the_past_deadmines") { }

        class spell_vision_of_the_past_deadmines_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_vision_of_the_past_deadmines_SpellScript);

            enum Id
            {
                GO_INSTANCE_DEADMINES_PORTAL    = 208516,
                SPELL_VISION_OF_THE_PAST_RIDE   = 79587,
                NPC_ENTRY_VISION_OF_THE_PAST    = 42693
            };

            SpellCastResult CheckCast()
            {
                if (GameObject* instancePortal = GetCaster()->FindNearestGameObject(GO_INSTANCE_DEADMINES_PORTAL, 10.0f))
                    return SPELL_CAST_OK;

                return SPELL_FAILED_NOT_HERE;
            }

            void AfterCastSpell()
            {
                if (Unit* caster = GetCaster())
                    caster->NearTeleportTo(-95.44f, -703.92f, 8.89f, 4.66f);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_vision_of_the_past_deadmines_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_vision_of_the_past_deadmines_SpellScript::AfterCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_vision_of_the_past_deadmines_SpellScript();
        }
};

class spell_call_stalvan : public SpellScriptLoader
{
    public:
        spell_call_stalvan() : SpellScriptLoader("spell_call_stalvan") { }

        class spell_call_stalvan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_call_stalvan_SpellScript);

            enum Id
            {
                NPC_ENTRY_STALVAN   = 315,
                NPC_ENTRY_TOBIAS    = 43904,
                GO_ENTRY_TRIGGER    = 20689,
                GO_TRIGGER_GUID     = 5573
            };

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetMapId() == 0 && GetCaster()->GetZoneId() == 10 && GetCaster()->GetAreaId() == 1098)
                {
                    if (Creature* tobias = GetCaster()->FindNearestCreature(NPC_ENTRY_TOBIAS, 60.0f, true))
                        return SPELL_FAILED_NOT_HERE;

                    if (GameObject* trigger = GetCaster()->FindNearestGameObject(GO_ENTRY_TRIGGER, 15.0f))
                    {
                        if (trigger->GetGUIDLow() == GO_TRIGGER_GUID)
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void AfterCastSpell()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->SummonCreature(NPC_ENTRY_STALVAN, -10372.10f, -1251.83f, 35.90f, 5.38f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    caster->SummonCreature(NPC_ENTRY_TOBIAS, -10357.42f, -1258.42f, 35.30f, 2.76f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_call_stalvan_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_call_stalvan_SpellScript::AfterCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_call_stalvan_SpellScript();
        }
};

class spell_sacred_cleansing_bane : public SpellScriptLoader
{
    public:
        spell_sacred_cleansing_bane() : SpellScriptLoader("spell_sacred_cleansing_bane") { }

        class spell_sacred_cleansing_bane_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sacred_cleansing_bane_SpellScript);

            enum Id
            {
                NPC_ENTRY_MORBENT_FEL   = 43761,
                SPELL_UNHOLY_SHIELD     = 8909
            };

            SpellCastResult CheckCast()
            {
                if (Creature* morbentFel = GetCaster()->FindNearestCreature(NPC_ENTRY_MORBENT_FEL, 50.0f, true))
                    return SPELL_CAST_OK;

                return SPELL_FAILED_NOT_HERE;
            }

            void AfterCastSpell()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* morbentFel = caster->FindNearestCreature(NPC_ENTRY_MORBENT_FEL, 50.0f, true))
                    {
                        morbentFel->RemoveAurasDueToSpell(SPELL_UNHOLY_SHIELD);
                        morbentFel->AI()->AttackStart(caster);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_sacred_cleansing_bane_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_sacred_cleansing_bane_SpellScript::AfterCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sacred_cleansing_bane_SpellScript();
        }
};

class spell_harris_ampule : public SpellScriptLoader
{
    public:
        spell_harris_ampule() : SpellScriptLoader("spell_harris_ampule") { }

        class spell_harris_ampule_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_harris_ampule_SpellScript);

            enum Id
            {
                NPC_ENTRY_LURKERING_WORGEN      = 43814,
                QUEST_CREDIT_LURKERING_WORGEN   = 43860
            };

            SpellCastResult CheckCast()
            {
                if (Creature* lurkeringWorgen = GetCaster()->FindNearestCreature(NPC_ENTRY_LURKERING_WORGEN, 6.0f, true))
                {
                    if (lurkeringWorgen->GetHealthPct() <= 25)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void AfterCastSpell()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* lurkeringWorgen = caster->FindNearestCreature(NPC_ENTRY_LURKERING_WORGEN, 5.0f, true))
                    {
                        lurkeringWorgen->DespawnOrUnsummon(1);
                        if (caster->GetTypeId() == TYPEID_PLAYER)
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_LURKERING_WORGEN);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_harris_ampule_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_harris_ampule_SpellScript::AfterCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_harris_ampule_SpellScript();
        }
};

class spell_return_to_booty_bay : public SpellScriptLoader
{
    public:
        spell_return_to_booty_bay() : SpellScriptLoader("spell_return_to_booty_bay") { }

        class spell_return_to_booty_bay_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_return_to_booty_bay_SpellScript);

            void HandleReturnMovement()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                    {
                        caster->GetMotionMaster()->Clear();
                        caster->GetMotionMaster()->MovePoint(10, -14447.89f, 512.56f, 26.33f, false);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_return_to_booty_bay_SpellScript::HandleReturnMovement);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_return_to_booty_bay_SpellScript();
        }
};

class spell_teleport_zulgurub : public SpellScriptLoader
{
    public:
        spell_teleport_zulgurub() : SpellScriptLoader("spell_teleport_zulgurub") { }

        class spell_teleport_zulgurub_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_teleport_zulgurub_SpellScript);

            enum Id
            {
                QUEST_THROUGH_THE_TROLL_HOLE_H  = 26552,
                QUEST_THROUGH_THE_TROLL_HOLE_A  = 26811
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_THROUGH_THE_TROLL_HOLE_H) == QUEST_STATUS_INCOMPLETE ||
                            caster->ToPlayer()->GetQuestStatus(QUEST_THROUGH_THE_TROLL_HOLE_H) == QUEST_STATUS_COMPLETE ||
                            caster->ToPlayer()->GetQuestStatus(QUEST_THROUGH_THE_TROLL_HOLE_A) == QUEST_STATUS_INCOMPLETE ||
                            caster->ToPlayer()->GetQuestStatus(QUEST_THROUGH_THE_TROLL_HOLE_A) == QUEST_STATUS_COMPLETE)
                            return SPELL_CAST_OK;
                        else
                            ChatHandler(caster->ToPlayer()->GetSession()).PSendSysMessage("You need quest: Through the Troll Hole");
                    }
                }
                return SPELL_FAILED_DONT_REPORT;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_teleport_zulgurub_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_teleport_zulgurub_SpellScript();
        }
};

class spell_gen_blackout_effect : public SpellScriptLoader
{
    public:
        spell_gen_blackout_effect() : SpellScriptLoader("spell_gen_blackout_effect") { }

        class spell_gen_blackout_effect_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_blackout_effect_SpellScript);

            enum Id
            {
                // Quest
                QUEST_FALL_BACK = 27405
            };

            void HandleTeleportBlackout()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_FALL_BACK) == QUEST_STATUS_COMPLETE)
                            caster->NearTeleportTo(-1171.13f, 1146.61f, 24.28f, 6.13f);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_gen_blackout_effect_SpellScript::HandleTeleportBlackout);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_blackout_effect_SpellScript();
        }

        class spell_gen_blackout_effect_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_blackout_effect_AuraScript);

            enum Id
            {
                // Quest
                QUEST_TRANSDIMENSIONAL_WARFARE_CHAPTER_III  = 27518
            };

            void DoTeleportBack(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (target->ToPlayer()->GetQuestStatus(QUEST_TRANSDIMENSIONAL_WARFARE_CHAPTER_III) == QUEST_STATUS_COMPLETE)
                        {
                            // Only in Ambermill
                            if (target->GetAreaId() == 233)
                                target->NearTeleportTo(-157.14f, 1270.39f, 51.09f, 6.26f);
                        }
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_gen_blackout_effect_AuraScript::DoTeleportBack, EFFECT_0, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_blackout_effect_AuraScript();
        }
};

class spell_gen_despawn_all_summons : public SpellScriptLoader
{
    public:
        spell_gen_despawn_all_summons() : SpellScriptLoader("spell_gen_despawn_all_summons") { }

        class spell_gen_despawn_all_summons_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_despawn_all_summons_SpellScript);

            enum Id
            {
                NPC_ENTRY_ARTHURA   = 45474,
                NPC_ENTRY_BELMONT   = 45473,
                NPC_ENTRY_GODFREY   = 45878,
                NPC_ENTRY_ASHBURY   = 45880,
                NPC_ENTRY_WALDEN    = 45879,

                SPELL_AURA_BATTLEFRONT = 85516
            };

            void HandleRemoveSummoned()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 250.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(250.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_ARTHURA:
                                    case NPC_ENTRY_BELMONT:
                                    case NPC_ENTRY_GODFREY:
                                    case NPC_ENTRY_ASHBURY:
                                    case NPC_ENTRY_WALDEN:
                                        ((*itr)->ToTempSummon()->UnSummon());
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                        if (caster->HasAura(SPELL_AURA_BATTLEFRONT))
                            caster->RemoveAurasDueToSpell(SPELL_AURA_BATTLEFRONT);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_gen_despawn_all_summons_SpellScript::HandleRemoveSummoned);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_despawn_all_summons_SpellScript();
        }
};

class spell_the_great_escape_init : public SpellScriptLoader
{
    public:
        spell_the_great_escape_init() : SpellScriptLoader("spell_the_great_escape_init") { }

        class spell_the_great_escape_init_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_the_great_escape_init_SpellScript);

            enum Id
            {
                // NPC
                NPC_ENTRY_ARTHURA   = 45314,
                NPC_ENTRY_GODFREY   = 44369,

                // Phase Auras
                SPELL_DETECT_INVISIBILITY_11      = 85039
            };

            void HandleInitEvent(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        caster->RemoveAurasDueToSpell(SPELL_DETECT_INVISIBILITY_11);
                        caster->SummonCreature(NPC_ENTRY_ARTHURA, -2122.62f, 935.10f, 6.85f, 4.75f, TEMPSUMMON_MANUAL_DESPAWN);
                    }
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_the_great_escape_init_SpellScript::HandleInitEvent, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_the_great_escape_init_SpellScript();
        }
};

class spell_raise_forsaken_agatha : public SpellScriptLoader
{
    public:
        spell_raise_forsaken_agatha() : SpellScriptLoader("spell_raise_forsaken_agatha") { }

        class spell_raise_forsaken_agatha_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_raise_forsaken_agatha_AuraScript);

            enum Id
            {
                // NPC
                NPC_ENTRY_LORD_GODFREY  = 45576,
                NPC_ENTRY_LORD_WALDEN   = 45578,
                NPC_ENTRY_LORD_ASHBURY  = 45577,

                // Spells
                SPELL_TRANSFORM_GODFREY = 85198,
                SPELL_TRANSFORM_WALDEN  = 85201,
                SPELL_TRANSFORM_ASHBURY = 85200,
                SPELL_AURA_FEIGN_DEATH  = 75511
            };

            void ApplyTransformation(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->GetTypeId() == TYPEID_UNIT)
                {
                    switch (GetTarget()->GetEntry())
                    {
                        case NPC_ENTRY_LORD_GODFREY:
                        {
                            GetTarget()->RemoveAurasDueToSpell(SPELL_AURA_FEIGN_DEATH);
                            GetTarget()->CastSpell(GetTarget(), SPELL_TRANSFORM_GODFREY, true);
                            GetTarget()->GetAI()->SetData(0, 1);
                            break;
                        }
                        case NPC_ENTRY_LORD_WALDEN:
                        {
                            GetTarget()->RemoveAurasDueToSpell(SPELL_AURA_FEIGN_DEATH);
                            GetTarget()->CastSpell(GetTarget(), SPELL_TRANSFORM_WALDEN, true);
                            break;
                        }
                        case NPC_ENTRY_LORD_ASHBURY:
                        {
                            GetTarget()->RemoveAurasDueToSpell(SPELL_AURA_FEIGN_DEATH);
                            GetTarget()->CastSpell(GetTarget(), SPELL_TRANSFORM_ASHBURY, true);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_raise_forsaken_agatha_AuraScript::ApplyTransformation, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_raise_forsaken_agatha_AuraScript();
        }
};

class spell_raise_forsaken_dashla : public SpellScriptLoader
{
    public:
        spell_raise_forsaken_dashla() : SpellScriptLoader("spell_raise_forsaken_dashla") { }

        class spell_raise_forsaken_dashla_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_raise_forsaken_dashla_AuraScript);

            enum Id
            {
                // NPC
                NPC_ENTRY_ARCHMAGE_ATAERIC_DEAD = 45779,
                NPC_ENTRY_ARCHMAGE_ATAERIC      = 45803
            };

            void ApplyTransformation(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->GetTypeId() == TYPEID_UNIT)
                {
                    switch (GetTarget()->GetEntry())
                    {
                        case NPC_ENTRY_ARCHMAGE_ATAERIC_DEAD:
                        {
                            GetTarget()->ToCreature()->DespawnOrUnsummon(1);
                            GetCaster()->SummonCreature(NPC_ENTRY_ARCHMAGE_ATAERIC, -136.10f, 1067.64f, 66.29f, 1.55f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_raise_forsaken_dashla_AuraScript::ApplyTransformation, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_raise_forsaken_dashla_AuraScript();
        }
};

class spell_battlefront_broadcast : public SpellScriptLoader
{
    public:
        spell_battlefront_broadcast() : SpellScriptLoader("spell_battlefront_broadcast") { }

        class spell_battlefront_broadcast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_battlefront_broadcast_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_GODFREY   = 45878,
                NPC_ENTRY_ASHBURY   = 45880,
                NPC_ENTRY_WALDEN    = 45879,

                // Spells
                SPELL_SUMMON_GODFREY = 85517,
                SPELL_SUMMON_WALDEN  = 85518,
                SPELL_SUMMON_ASHBURY = 85519
            };

            void HandleBroadcast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 250.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_GODFREY:
                                    case NPC_ENTRY_ASHBURY:
                                    case NPC_ENTRY_WALDEN:
                                        return;
                                    default:
                                        break;
                                }
                            }
                        }

                        // Do summon creatures for quests (Only in Silverpine Forest)
                        if (caster->GetMapId() == 0 && caster->GetZoneId() == 130)
                        {
                            caster->CastSpell(caster->GetPositionX(), caster->GetPositionY()-2, caster->GetPositionZ(), SPELL_SUMMON_GODFREY, true);
                            caster->CastSpell(caster->GetPositionX()+2, caster->GetPositionY(), caster->GetPositionZ(), SPELL_SUMMON_ASHBURY, true);
                            caster->CastSpell(caster->GetPositionX()-2, caster->GetPositionY(), caster->GetPositionZ(), SPELL_SUMMON_WALDEN, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_battlefront_broadcast_SpellScript::HandleBroadcast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_battlefront_broadcast_SpellScript();
        }
};

class spell_silverpine_finale_master : public SpellScriptLoader
{
    public:
        spell_silverpine_finale_master() : SpellScriptLoader("spell_silverpine_finale_master") { }

        class spell_silverpine_finale_master_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_silverpine_finale_master_SpellScript);

            /*  85868 - Summon Cromush
                85869 - Summon Arthura
                85870 - Summon Agatha
                85871 - Summon Daschla
                85872 - Silverpine Finale Master Summon Script
                85874 - Song of Sylvanas
                85864 - Summon Sylvanas
            */

            enum Id
            {
                // Spells
                SPELL_SUMMON_CROMUSH    = 85868,
                SPELL_SUMMON_ARTHURA    = 85869,
                SPELL_SUMMON_AGATHA     = 85870,
                SPELL_SUMMON_DASCHLA    = 85871,
                SPELL_SUMMON_SYLVANAS   = 85864,

                // Music
                MUSIC_LAMENT_OF_THE_HIGHBORNE = 10896
            };

            void HandleBroadcast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        // Do summon creatures for quests (Only in Silverpine Forest)
                        if (caster->GetMapId() == 0 && caster->GetZoneId() == 130)
                        {
                            caster->SetPhaseMask(2, true);
                            caster->CastSpell(caster, SPELL_SUMMON_SYLVANAS, true);
                            caster->CastSpell(caster, SPELL_SUMMON_DASCHLA, true);
                            caster->CastSpell(caster, SPELL_SUMMON_AGATHA, true);
                            caster->CastSpell(caster, SPELL_SUMMON_ARTHURA, true);
                            caster->CastSpell(caster, SPELL_SUMMON_CROMUSH, true);
                            caster->PlayDirectSound(MUSIC_LAMENT_OF_THE_HIGHBORNE, caster->ToPlayer());
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_silverpine_finale_master_SpellScript::HandleBroadcast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_silverpine_finale_master_SpellScript();
        }
};

class spell_raise_forsaken_arthura : public SpellScriptLoader
{
    public:
        spell_raise_forsaken_arthura() : SpellScriptLoader("spell_raise_forsaken_arthura") { }

        class spell_raise_forsaken_arthura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_raise_forsaken_arthura_AuraScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_LADY_SYLVANAS = 46026,
                NPC_ENTRY_ARTHURA       = 46032,
                NPC_ENTRY_CROMUSH       = 46031,
                NPC_ENTRY_DASCHLA       = 46033,
                NPC_ENTRY_AGATHA        = 46034,

                // Spell
                SPELL_ENTRY_FEIGN_DEATH = 90359
            };

            void ResurrectSylvanas(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->GetTypeId() == TYPEID_UNIT)
                {
                    switch (GetTarget()->GetEntry())
                    {
                        case NPC_ENTRY_LADY_SYLVANAS:
                        {
                            if (GetCaster()->GetTypeId() == TYPEID_UNIT)
                            {
                                if (GetCaster()->ToCreature()->GetEntry() == NPC_ENTRY_ARTHURA)
                                {
                                    GetTarget()->RemoveAurasDueToSpell(SPELL_ENTRY_FEIGN_DEATH);
                                    GetTarget()->ToCreature()->AI()->TalkWithDelay(1500, 20);
                                    GetTarget()->ToCreature()->AI()->TalkWithDelay(7500, 21);
                                    GetTarget()->ToCreature()->AI()->TalkWithDelay(13500, 22);
                                    GetTarget()->ToCreature()->AI()->TalkWithDelay(19500, 23);
                                    GetTarget()->ToCreature()->DespawnOrUnsummon(45500);
                                }
                            }

                            GetCaster()->SetHover(false);
                            GetCaster()->Kill(GetCaster(), false);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_raise_forsaken_arthura_AuraScript::ResurrectSylvanas, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_raise_forsaken_arthura_AuraScript();
        }
};

class spell_quest_giver : public SpellScriptLoader
{
    public:
        spell_quest_giver() : SpellScriptLoader("spell_quest_giver") { }

        class spell_quest_giver_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_quest_giver_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_DUMASS        = 47444,
                NPC_ENTRY_ORKUS         = 47443,
                NPC_ENTRY_JOHNNY        = 47442,
                NPC_ENTRY_DARTHALIA     = 47499
            };

            void HandleRemoveSummons()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 150.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetSummoner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_DUMASS:
                                    case NPC_ENTRY_ORKUS:
                                    case NPC_ENTRY_JOHNNY:
                                    case NPC_ENTRY_DARTHALIA:
                                        (*itr)->ToTempSummon()->UnSummon();
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_quest_giver_SpellScript::HandleRemoveSummons);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_quest_giver_SpellScript();
        }
};

class spell_shackle : public SpellScriptLoader
{
    public:
        spell_shackle() : SpellScriptLoader("spell_shackle") { }

        class spell_shackle_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shackle_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_HILLSBRAD_SENTRY  = 2270
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Creature* hillsbradSentry = GetCaster()->FindNearestCreature(NPC_ENTRY_HILLSBRAD_SENTRY, 6.0f, true))
                        {
                            if (hillsbradSentry->GetHealthPct() <= 30)
                                return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_TARGET_AURASTATE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_shackle_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_shackle_SpellScript();
        }
};

class spell_helcular_rod : public SpellScriptLoader
{
    public:
        spell_helcular_rod() : SpellScriptLoader("spell_helcular_rod") { }

        class spell_helcular_rod_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_helcular_rod_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_DARK_RANGER  = 48269,

                // Spell
                SPELL_HELCULAR_IRE     = 89824
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Creature* darkRanger = GetCaster()->FindNearestCreature(NPC_ENTRY_DARK_RANGER, 8.0f, true))
                        {
                            if (!darkRanger->HasAura(SPELL_HELCULAR_IRE))
                                return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_TARGET_AURASTATE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_helcular_rod_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_helcular_rod_SpellScript();
        }
};

class spell_collect_specimen : public SpellScriptLoader
{
    public:
        spell_collect_specimen() : SpellScriptLoader("spell_collect_specimen") { }

        class spell_collect_specimen_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_collect_specimen_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_BLIGHT_SLIME  = 48136,
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Unit* target = GetExplTargetUnit())
                        {
                            if (target->GetTypeId() == TYPEID_UNIT && target->GetEntry() == NPC_ENTRY_BLIGHT_SLIME)
                                return SPELL_CAST_OK;
                            else
                                return SPELL_FAILED_BAD_TARGETS;
                        }
                    }
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_collect_specimen_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_collect_specimen_SpellScript();
        }
};

class spell_summon_orkus : public SpellScriptLoader
{
    public:
        spell_summon_orkus() : SpellScriptLoader("spell_summon_orkus") { }

        class spell_summon_orkus_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_orkus_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        return SPELL_CAST_OK;
                    else
                        return SPELL_FAILED_DONT_REPORT;
                }
                return SPELL_FAILED_DONT_REPORT;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_orkus_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_orkus_SpellScript();
        }
};

class spell_duskingdawn_blessing : public SpellScriptLoader
{
    public:
        spell_duskingdawn_blessing() : SpellScriptLoader("spell_duskingdawn_blessing") { }

        class spell_duskingdawn_blessing_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_duskingdawn_blessing_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_HILL_FAWN  = 48187,

                // Spell
                SPELL_DUSKINGDAWN_BLESSING_TRANSFORMATION = 90685,
                SPELL_FAWNPLODE                           = 90686,

                // Credit
                QUEST_CREDIT_HILL_FAWN                    = 48684
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Creature* target = caster->FindNearestCreature(NPC_ENTRY_HILL_FAWN, 10.0f, true))
                        {
                            if (!target->HasAura(SPELL_DUSKINGDAWN_BLESSING_TRANSFORMATION))
                            {
                                target->CastSpell(target, SPELL_DUSKINGDAWN_BLESSING_TRANSFORMATION, true);
                                caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_HILL_FAWN);
                                return SPELL_CAST_OK;
                            }
                            else
                            {
                                target->CastSpell(target, SPELL_FAWNPLODE, true);
                                return SPELL_CAST_OK;
                            }
                        }
                    }
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_duskingdawn_blessing_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_duskingdawn_blessing_SpellScript();
        }
};

class spell_place_goblin_pocket_nuke : public SpellScriptLoader
{
    public:
        spell_place_goblin_pocket_nuke() : SpellScriptLoader("spell_place_goblin_pocket_nuke") { }

        class spell_place_goblin_pocket_nuke_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_place_goblin_pocket_nuke_SpellScript);

            enum Id
            {
                // Areas
                AREA_ENTRY_GAVIN    = 1677,
                AREA_ENTRY_SOFERA   = 1678,
                AREA_ENTRY_CORRAHN  = 1679,
                AREA_ENTRY_HEADLAND = 1680,

                // Credits
                CREDIT_GAVIN        = 48867,
                CREDIT_SOFERA       = 48862,
                CREDIT_CORRAHN      = 48864,
                CREDIT_HEADLAND     = 48865
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        switch (caster->GetAreaId())
                        {
                            case AREA_ENTRY_SOFERA:
                            case AREA_ENTRY_GAVIN:
                            case AREA_ENTRY_CORRAHN:
                            case AREA_ENTRY_HEADLAND:
                                return SPELL_CAST_OK;
                            default:
                                return SPELL_FAILED_NOT_HERE;
                        }
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleKillCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    switch (caster->GetAreaId())
                    {
                        case AREA_ENTRY_SOFERA:
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_SOFERA);
                            break;
                        case AREA_ENTRY_GAVIN:
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_GAVIN);
                            break;
                        case AREA_ENTRY_CORRAHN:
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_CORRAHN);
                            break;
                        case AREA_ENTRY_HEADLAND:
                            caster->ToPlayer()->KilledMonsterCredit(CREDIT_HEADLAND);
                            break;
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_place_goblin_pocket_nuke_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_place_goblin_pocket_nuke_SpellScript::HandleKillCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_place_goblin_pocket_nuke_SpellScript();
        }
};

class spell_control_ettin : public SpellScriptLoader
{
    public:
        spell_control_ettin() : SpellScriptLoader("spell_control_ettin") { }

        class spell_control_ettin_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_control_ettin_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_CANYON_ETTIN = 43094,

                // Spells
                SPELL_ENTRY_CANYON_ETTIN_SPAWN = 82558
            };


            void HandleSubdueEttin(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* ettin = caster->FindNearestCreature(NPC_ENTRY_CANYON_ETTIN, ATTACK_DISTANCE, true))
                    {
                        if (ettin->ToCreature())
                        {
                            caster->CastSpell(caster, SPELL_ENTRY_CANYON_ETTIN_SPAWN, true);
                            ettin->ToCreature()->DespawnOrUnsummon(100);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_control_ettin_SpellScript::HandleSubdueEttin, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_control_ettin_SpellScript();
        }
};

class spell_summon_lilith : public SpellScriptLoader
{
    public:
        spell_summon_lilith() : SpellScriptLoader("spell_summon_lilith") { }

        class spell_summon_lilith_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_lilith_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_LILITH = 49035
            };

            void BeforeCastSpell()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 100.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(100.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && (*itr)->ToTempSummon()->GetCharmerOrOwner() == caster)
                        {
                            // Lilith
                            if ((*itr)->ToTempSummon()->GetEntry() == NPC_ENTRY_LILITH)
                                (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                        }
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_summon_lilith_SpellScript::BeforeCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_lilith_SpellScript();
        }
};

class spell_lunar_invitation : public SpellScriptLoader
{
    public:
        spell_lunar_invitation() : SpellScriptLoader("spell_lunar_invitation") { }

        class spell_lunar_invitation_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lunar_invitation_SpellScript);

            void HandleTeleportCaster()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->ToPlayer()->TeleportTo(1, 7588.59f, -2226.26f, 470.87f, 6.25f);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_lunar_invitation_SpellScript::HandleTeleportCaster);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lunar_invitation_SpellScript();
        }
};

class spell_summon_generic_controller : public SpellScriptLoader
{
    public:
        spell_summon_generic_controller() : SpellScriptLoader("spell_summon_generic_controller") { }

        class spell_summon_generic_controller_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_generic_controller_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_MESSNER   = 43300,
                NPC_ENTRY_JORGENSEN = 43305,
                NPC_ENTRY_KRAKAUER  = 43303,

                // Spell
                SPELL_SUMMON_MESSNER    = 80893,
                SPELL_SUMMON_JORGENSEN  = 80940,
                SPELL_SUMMON_KRAKAUER   = 80941
            };

            void BeforeCastSpell()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 300.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(300.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && (*itr)->ToTempSummon()->GetCharmerOrOwner() == caster)
                        {
                            switch ((*itr)->ToTempSummon()->GetEntry())
                            {
                                case NPC_ENTRY_MESSNER:
                                {
                                    if (GetSpellInfo()->Id == SPELL_SUMMON_MESSNER)
                                        (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                                    break;
                                }
                                case NPC_ENTRY_JORGENSEN:
                                {
                                    if (GetSpellInfo()->Id == SPELL_SUMMON_JORGENSEN)
                                        (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                                    break;
                                }
                                case NPC_ENTRY_KRAKAUER:
                                {
                                    if (GetSpellInfo()->Id == SPELL_SUMMON_KRAKAUER)
                                        (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_summon_generic_controller_SpellScript::BeforeCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_generic_controller_SpellScript();
        }
};

void AddSC_generic_spell_scripts()
{
    new spell_gen_absorb0_hitlimit1();
    new spell_gen_aura_of_anger();
    new spell_gen_av_drekthar_presence();
    new spell_gen_burn_brutallus();
    new spell_gen_cannibalize();
    new spell_gen_parachute();
    new spell_gen_remove_flight_auras();
    new spell_creature_permanent_feign_death();
    new spell_pvp_trinket_wotf_shared_cd();
    new spell_gen_animal_blood();
    new spell_gen_divine_storm_cd_reset();
    new spell_gen_parachute_ic();
    new spell_gen_gunship_portal();
    new spell_gen_dungeon_credit();
    new spell_gen_profession_research();
    new spell_generic_clone();
    new spell_generic_clone_weapon();
    new spell_gen_clone_weapon_aura();
    new spell_gen_seaforium_blast();
    new spell_gen_turkey_marker();
    new spell_gen_lifeblood();
    new spell_gen_magic_rooster();
    new spell_gen_allow_cast_from_item_only();
    new spell_gen_launch();
    new spell_gen_vehicle_scaling();
    new spell_gen_oracle_wolvar_reputation();
    new spell_gen_dummy_trigger();
    new spell_gen_spirit_healer_res();
    new spell_gen_gadgetzan_transporter_backfire();
    new spell_gen_gnomish_transporter();
    new spell_gen_dalaran_disguise("spell_gen_sunreaver_disguise");
    new spell_gen_dalaran_disguise("spell_gen_silver_covenant_disguise");
    new spell_gen_elune_candle();
    new spell_gen_break_shield("spell_gen_break_shield");
    new spell_gen_break_shield("spell_gen_tournament_counterattack");
    new spell_gen_mounted_charge();
    new spell_gen_defend();
    new spell_gen_tournament_duel();
    new spell_gen_summon_tournament_mount();
    new spell_gen_on_tournament_mount();
    new spell_gen_tournament_pennant();
    new spell_gen_chaos_blast();
    new spell_gen_ds_flush_knockback();
    new spell_gen_wg_water();
    new spell_gen_count_pct_from_max_hp("spell_gen_default_count_pct_from_max_hp");
    new spell_gen_count_pct_from_max_hp("spell_gen_50pct_count_pct_from_max_hp", 50);
    new spell_gen_despawn_self();
    new spell_gen_touch_the_nightmare();
    new spell_gen_dream_funnel();
    new spell_gen_bandage();
    new spell_gen_lifebloom("spell_hexlord_lifebloom", SPELL_HEXLORD_MALACRASS_LIFEBLOOM_FINAL_HEAL);
    new spell_gen_lifebloom("spell_tur_ragepaw_lifebloom", SPELL_TUR_RAGEPAW_LIFEBLOOM_FINAL_HEAL);
    new spell_gen_lifebloom("spell_cenarion_scout_lifebloom", SPELL_CENARION_SCOUT_LIFEBLOOM_FINAL_HEAL);
    new spell_gen_lifebloom("spell_twisted_visage_lifebloom", SPELL_TWISTED_VISAGE_LIFEBLOOM_FINAL_HEAL);
    new spell_gen_lifebloom("spell_faction_champion_dru_lifebloom", SPELL_FACTION_CHAMPIONS_DRU_LIFEBLOOM_FINAL_HEAL);
    new spell_gen_summon_elemental("spell_gen_summon_fire_elemental", SPELL_SUMMON_FIRE_ELEMENTAL);
    new spell_gen_summon_elemental("spell_gen_summon_earth_elemental", SPELL_SUMMON_EARTH_ELEMENTAL);
    new spell_gen_upper_deck_create_foam_sword();
    new spell_gen_bonked();
    new spell_gen_gift_of_naaru();
    new spell_gen_increase_stats_buff("spell_pal_blessing_of_kings");
    new spell_gen_increase_stats_buff("spell_pal_blessing_of_might");
    new spell_gen_increase_stats_buff("spell_dru_mark_of_the_wild");
    new spell_gen_increase_stats_buff("spell_pri_power_word_fortitude");
    new spell_gen_increase_stats_buff("spell_pri_shadow_protection");
    new spell_gen_increase_stats_buff("spell_mage_arcane_brilliance");
    new spell_gen_raid_haste("spell_bloodlust");
    new spell_gen_raid_haste("spell_heroism");
    new spell_gen_raid_haste("spell_time_warp");
    new spell_gen_raid_haste("spell_ancient_hysteria");
    new spell_gen_replenishment();
    new spell_gen_armor_specialization("spell_dru_armor_specialization");
    new spell_gen_armor_specialization("spell_rog_armor_specialization");
    new spell_gen_armor_specialization("spell_sha_armor_specialization");
    new spell_gen_armor_specialization("spell_hun_armor_specialization");
    new spell_gen_armor_specialization("spell_pal_armor_specialization");
    new spell_gen_armor_specialization("spell_dk_armor_specialization");
    new spell_gen_armor_specialization("spell_war_armor_specialization");
    new spell_gen_running_wild();
    new spell_gen_two_forms();
    new spell_gen_darkflight();
    new spell_mage_dalaran_brilliance();
    new spell_log_in_effect();
    new spell_funeral_offering();
    new spell_bloodtalon_whistle();
    new spell_bloodtalon_lasso();
    new spell_territorial_fetish();
    new spell_thonk_spyglass();
    new spell_burn_constriction_totem();
    new spell_rune_of_return();
    new spell_signal_flare();
    new spell_extinguish_fire();
    new spell_ironforge_banner();
    new spell_cancel_vengeance_of_elune();
    new spell_moonsurge();
    new spell_shattershield_arrow();
    new spell_petrified_root();
    new spell_torch_shatterspear_supplies();
    new spell_elune_presence();
    new spell_frenzied_cyclone_braciers();
    new spell_constructing();
    new spell_constructing_spawning();
    new spell_ping_for_artifacts();
    new spell_disrupting_the_artifact();
    new spell_horn_of_the_ancients();
    new spell_calling_the_caravan();
    new spell_snared_in_net();
    new spell_snared_secondary_effect();
    new spell_placing_raptor_feather();
    new spell_summon_echeyakee();
    new spell_waptor_twap_scweech();
    new spell_waptor_shrink();
    new spell_pirate_signal_horn();
    new spell_apply_salve();
    new spell_summon_gorat_spirit();
    new spell_summon_brutusk_2();
    new spell_summon_burning_blade_flyer();
    new spell_cancel_imp_disguise();
    new spell_throw_accursed_ore();
    new spell_throw_blood();
    new spell_throw_signal_powder();
    new spell_chop_tree();
    new spell_gift_of_the_earth();
    new spell_gift_of_the_earth_second();
    new spell_return_to_the_vortex();
    new spell_return_to_base();
    new spell_unbathed_concotion();
    new spell_cleanse_elune_tear();
    new spell_playing_possum();
    new spell_summon_lou_house();
    new spell_vision_of_the_past_deadmines();
    new spell_call_stalvan();
    new spell_sacred_cleansing_bane();
    new spell_harris_ampule();
    new spell_return_to_booty_bay();
    new spell_teleport_zulgurub();
    new spell_gen_blackout_effect();
    new spell_gen_despawn_all_summons();
    new spell_the_great_escape_init();
    new spell_raise_forsaken_agatha();
    new spell_raise_forsaken_dashla();
    new spell_battlefront_broadcast();
    new spell_silverpine_finale_master();
    new spell_raise_forsaken_arthura();
    new spell_quest_giver();
    new spell_shackle();
    new spell_helcular_rod();
    new spell_collect_specimen();
    new spell_summon_orkus();
    new spell_duskingdawn_blessing();
    new spell_lunar_invitation();
    new spell_place_goblin_pocket_nuke();
    new spell_summon_lilith();
    new spell_control_ettin();
    new spell_summon_generic_controller();
}
