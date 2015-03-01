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
#include "Vehicle.h"
#include "AchievementMgr.h"

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
    SPELL_PARACHUTE_BUFF    = 37897,
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
                {
                    if (target->IsFalling())
                    {
                        target->RemoveAurasDueToSpell(SPELL_PARACHUTE);
                        target->CastSpell(target, SPELL_PARACHUTE_BUFF, true);
                    }
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

                Item* head = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
                Item* shoulders = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
                Item* chest = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                Item* wrist = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                Item* hands = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                Item* waist = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
                Item* legs = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
                Item* feet = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);

                if (!head || !shoulders || !chest || !wrist || !hands || !waist || !legs || !feet)
                    return;

                switch (player->getClass())
                {
                    case CLASS_DEATH_KNIGHT:
                    case CLASS_WARRIOR:
                    case CLASS_PALADIN:
                    {
                        if (!(head->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(shoulders->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(chest->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(wrist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(hands->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(waist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(legs->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE) ||
                            !(feet->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_PLATE))
                            return;
                        break;
                    }
                    case CLASS_ROGUE:
                    case CLASS_DRUID:
                    {
                        if (!(head->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(shoulders->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(chest->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(wrist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(hands->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(waist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(legs->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER) ||
                            !(feet->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER))
                            return;
                        break;
                    }
                    case CLASS_MAGE:
                    case CLASS_PRIEST:
                    case CLASS_WARLOCK:
                    {
                        if (!(head->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(shoulders->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(chest->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(wrist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(hands->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(waist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(legs->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH) ||
                            !(feet->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH))
                            return;
                        break;
                    }
                    case CLASS_SHAMAN:
                    case CLASS_HUNTER:
                    {
                        if (!(head->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(shoulders->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(chest->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(wrist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(hands->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(waist->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(legs->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL) ||
                            !(feet->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_MAIL))
                            return;
                        break;
                    }
                    default:
                        return;
                }

                uint32 spellId = 0;

                switch (player->GetPrimaryTalentTree(player->GetActiveSpec()))
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
                        if (player->GetShapeshiftForm() == FORM_BEAR)
                        {
                            spellId = 86096;
                            break;
                        }
                        if (player->GetShapeshiftForm() == FORM_CAT)
                        {
                            spellId = 86097;
                            break;
                        }
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
                {
                    if (player->HasAura(spellId))
                        player->RemoveAurasDueToSpell(spellId);
                    player->CastSpell(player, spellId, TRIGGERED_FULL_MASK);
                }
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
                caster->m_cloudStacks = 0;
                caster->m_graduationSpeechInspire = 1;
                caster->m_graduationSpeechIncite = 1;
                caster->m_graduationSpeechPander = 1;
            }

            if (Player* player = GetCaster()->ToPlayer())
            {
                // Vengeance of Elune
                if (player->HasAura(65602))
                    player->CastSpell(player, 66166, false);

                // Lilith Controller
                if (player->HasAura(91391))
                    player->RemoveAurasDueToSpell(91391);

                // Twilight Evolution
                if (player->HasAura(75732))
                {
                    player->RemoveAurasDueToSpell(91391);
                    player->Kill(player, true);
                }

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
                    if (player->GetZoneId() == 267)
                    {
                        player->CastSpell(player, 89296, true);
                        player->CastSpell(player, 89295, true);
                    }
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

                // Uldum (Lost City Cage)
                if (player->GetQuestStatus(27003) == QUEST_STATUS_COMPLETE && player->GetZoneId() == 5034)
                {
                    player->SetPhaseMask(298, true);
                    player->SetControlled(true, UNIT_STATE_ROOT);
                }

                // Summon Messner
                player->RemoveAurasDueToSpell(80893);
                // Summon Jorgensen
                player->RemoveAurasDueToSpell(80940);
                // Summon Krakauer
                player->RemoveAurasDueToSpell(80941);
                // Summon Danforth
                player->RemoveAurasDueToSpell(80943);
                // Summon Jorgensen 2
                player->RemoveAurasDueToSpell(81447);
                // Summon Lunk
                player->RemoveAurasDueToSpell(88166);
                // Summon Lunk (2)
                player->RemoveAurasDueToSpell(88291);
                // Summon Personal Guardian (Keeshan 03)
                player->RemoveAurasDueToSpell(89869);
                // Summon Personal Guardian (Ariok 03)
                player->RemoveAurasDueToSpell(90483);
                // AODR: Summon Camera/Phase
                player->RemoveAurasDueToSpell(89947);
                // The Pride Of Kezan: Flight Speed Aura
                player->RemoveAurasDueToSpell(73446);
                // TDDC 1: Summon Theldurin
                player->RemoveAurasDueToSpell(86557);
                // TDDC 2: Summon Lucien
                player->RemoveAurasDueToSpell(87737);
                // TDDC 3: Summon Martek's Hog
                player->RemoveAurasDueToSpell(86675);
                // Ex-KEF: Summon Amakkar
                player->RemoveAurasDueToSpell(87589);
                // Ex-KEF: Summon Gargal
                player->RemoveAurasDueToSpell(87590);
                // Ex-KEF: Summon Jurrix
                player->RemoveAurasDueToSpell(87591);
                // The Lost Vikings: Summon Eric
                player->RemoveAurasDueToSpell(87262);
                // The Lost Vikings: Summon Baelog
                player->RemoveAurasDueToSpell(87263);
                // The Lost Vikings: Summon Olaf
                player->RemoveAurasDueToSpell(87264);
                // RG: Master Force Phase/Invis
                player->RemoveAurasDueToSpell(87436);
                // Summon Provincial Minuteman 1 (Pet)
                player->RemoveAurasDueToSpell(84452);
                // Summon Provincial Minuteman 2
                player->RemoveAurasDueToSpell(84456);
                // Summon Provincial Minuteman 3
                player->RemoveAurasDueToSpell(84457);
                // Summon Provincial Minuteman 4
                player->RemoveAurasDueToSpell(84458);
                // Summon Provincial Minuteman 1 (Guardian)
                player->RemoveAurasDueToSpell(84482);
                // Escorting Zen'Kiki (1)
                player->RemoveAurasDueToSpell(83456);
                // Escorting Zen'Kiki (2)
                player->RemoveAurasDueToSpell(83819);
                // Summon Tarenar Sunstrike
                player->RemoveAurasDueToSpell(84902);
                // Summon Tarenar Sunstrike
                player->RemoveAurasDueToSpell(85217);
                // Summon Gidwin Goldbraids
                player->RemoveAurasDueToSpell(85218);
                // Summon Tarenar Sunstrike
                player->RemoveAurasDueToSpell(85405);
                // Summon Vex'Tul
                player->RemoveAurasDueToSpell(85334);
                // Run for it!
                player->RemoveAurasDueToSpell(71455);
                // Baeldun Phase
                player->RemoveAurasDueToSpell(73592);
                // Freewind Brave
                player->RemoveAurasDueToSpell(84658);
                // Feralas Sentinel
                player->RemoveAurasDueToSpell(84657);
                // Climbing Tree
                player->RemoveAurasDueToSpell(74920);
                // Mental Training
                player->RemoveAurasDueToSpell(73984);
                // Twilight Speech
                player->RemoveAurasDueToSpell(74948);
                // Aeonaxx Whelps
                player->RemoveAurasDueToSpell(94652);
                // Awesome Party Ensemble
                player->RemoveAurasDueToSpell(66908);
                player->RemoveAurasDueToSpell(66927);
                player->RemoveAurasDueToSpell(66928);
                player->RemoveAurasDueToSpell(66985);
                // Miner Troubles
                player->RemoveAurasDueToSpell(68062);
                // Orc Scout
                player->RemoveAurasDueToSpell(68338);
                // Phasing
                player->RemoveAurasDueToSpell(60191);
                // Rocket Fire
                player->RemoveAurasDueToSpell(72885);
                // Uldum Intro
                player->RemoveAurasDueToSpell(86792);
                // Salhet
                player->RemoveAurasDueToSpell(89298);
                player->RemoveAurasDueToSpell(89312);
                // Sunfire
                player->RemoveAurasDueToSpell(94338);
                // Eclipse Markers
                player->RemoveAurasDueToSpell(67484);
                player->RemoveAurasDueToSpell(67483);
                // Digestive Corrosion
                if (player->HasAura(90782))
                {
                    player->RemoveAurasDueToSpell(90782);
                    player->CastWithDelay(500, player, 90782, true);
                }
                player->RemoveAurasDueToSpell(90803);
                player->RemoveAurasDueToSpell(90804);
                player->RemoveAurasDueToSpell(90805);
                player->RemoveAurasDueToSpell(110230);
                player->RemoveAurasDueToSpell(101612);
                player->RemoveAurasDueToSpell(102058);
                player->RemoveAurasDueToSpell(68735);
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
                Unit* spitescaleTrigg = GetCaster()->FindNearestCreature(NPC_SPITESCALE_FLAG, 2.0f);
                if (spitescaleFlag && spitescaleTrigg)
                {
                    if (!spitescaleTrigg->HasAura(SPELL_TERRITORIAL_FETISH))
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleApplyMask(SpellEffIndex effIndex)
            {
                if (Unit* spitescaleFlag = GetCaster()->FindNearestCreature(NPC_SPITESCALE_FLAG, 2.0f))
                {
                    if (!spitescaleFlag->HasAura(SPELL_TERRITORIAL_FETISH))
                        spitescaleFlag->AddAura(SPELL_TERRITORIAL_FETISH, spitescaleFlag);
                }
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

        enum npcId
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
        };

        enum spellId
        {
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
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        return;

                    caster->PlayDirectSound(SOUND_PLAY_CALL_CARAVAN);
                    switch (caster->ToCreature()->GetEntry())
                    {
                        // Halga Bloodeye
                        case NPC_HALGA_BLOODEYE:
                        {
                            caster->SummonCreature(NPC_FAR_WATCH_CARAVAN_KODO, 314.76f, -3711.60f, 26.56f, 1.49f);
                            caster->SummonCreature(NPC_LEAD_CARAVAN_KODO, 316.35f, -3699.61f, 26.88f, 1.43f);
                            break;
                        }
                        // Rocco Whipshank (To Crossroads)
                        case NPC_ROCCO_CROSSROADS:
                        {
                            caster->SummonCreature(NPC_HEAD_CARAVAN_KODO, 219.23f, -2964.53f, 91.88f, 2.73f);
                            caster->SummonCreature(NPC_CROSSROADS_CARAVAN_KODO, 228.73f, -2970.47f, 91.89f, 2.57f);
                            break;
                        }
                        case NPC_ROCCO_MORSHAN:
                        {
                            caster->SummonCreature(NPC_CARAVAN_CART, -379.23f, -2679.30f, 95.76f, 6.18f);
                            break;
                        }
                        case NPC_NAGALA_WHIPSHANK:
                        {
                            caster->SummonCreature(NPC_MASTER_CARAVAN_KODO, 315.03f, -2541.74f, 91.69f, 3.11f);
                            caster->SummonCreature(NPC_CARAVAN_KODO_MORSHAN, 329.21f, -2541.01f, 91.90f, 3.20f);
                            break;
                        }
                        default:
                            break;
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
                MAP_ENTRY_DEADMINES             = 36,
                GO_INSTANCE_DEADMINES_PORTAL    = 208516,
                SPELL_VISION_OF_THE_PAST_RIDE   = 79587,
                NPC_ENTRY_VISION_OF_THE_PAST    = 42693,
                SPELL_CAST_FADE_TO_BLACK        = 89092
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetMapId() == MAP_ENTRY_DEADMINES)
                    {
                        if (GameObject* instancePortal = GetCaster()->FindNearestGameObject(GO_INSTANCE_DEADMINES_PORTAL, 10.0f))
                        {
                            caster->CastSpell(caster, SPELL_CAST_FADE_TO_BLACK, true);
                            caster->NearTeleportTo(-95.44f, -703.92f, 8.89f, 4.66f);
                            return SPELL_FAILED_DONT_REPORT;
                        }
                        else
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_vision_of_the_past_deadmines_SpellScript::CheckCast);
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
                    if (Creature* lurkeringWorgen = caster->FindNearestCreature(NPC_ENTRY_LURKERING_WORGEN, 6.0f, true))
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
                QUEST_FALL_BACK                     = 27405,
                QUEST_WELCOME_TO_THE_BROTHERHOOD    = 28064,
                QUEST_THE_HIDDEN_CLUTCH_H           = 27897,
                QUEST_THE_HIDDEN_CLUTCH_A           = 27832
            };

            void HandleTeleportBlackout()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_FALL_BACK) == QUEST_STATUS_COMPLETE)
                            caster->NearTeleportTo(-1171.13f, 1146.61f, 24.28f, 6.13f);
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_WELCOME_TO_THE_BROTHERHOOD) == QUEST_STATUS_COMPLETE)
                            caster->NearTeleportTo(-6505.92f, -1177.28f, 326.21f, 0.70f);
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_THE_HIDDEN_CLUTCH_H) == QUEST_STATUS_COMPLETE)
                            caster->NearTeleportTo(-6525.17f, -2397.23f, 294.15f, 1.06f);
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_THE_HIDDEN_CLUTCH_A) == QUEST_STATUS_COMPLETE)
                            caster->NearTeleportTo(-6525.17f, -2397.23f, 294.15f, 1.06f);
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
                // Npc
                NPC_ENTRY_ARTHURA       = 45474, NPC_ENTRY_BELMONT       = 45473, NPC_ENTRY_GODFREY       = 45878,
                NPC_ENTRY_ASHBURY       = 45880, NPC_ENTRY_WALDEN        = 45879, NPC_ENTRY_AMAKKAR       = 47021,
                NPC_ENTRY_GARGAL        = 47022, NPC_ENTRY_JURRIX        = 47024, NPC_ENTRY_ERIC          = 46855,
                NPC_ENTRY_BAELOG        = 46856, NPC_ENTRY_OLAF          = 46857, NPC_ENTRY_MINUTEMAN_1   = 45231,
                NPC_ENTRY_MINUTEMAN_2   = 45232, NPC_ENTRY_MINUTEMAN_3   = 45233, NPC_ENTRY_MINUTEMAN_4   = 45234,
                NPC_ENTRY_ZENKIKI_1     = 44269, NPC_ENTRY_ZENKIKI_2     = 44904, NPC_ENTRY_ENTRHALLED_VA = 44492,
                NPC_ENTRY_GIDWIN_1      = 46173, NPC_ENTRY_TARENAR_1     = 45957, NPC_ENTRY_TARENAR_2     = 45794,
                NPC_ENTRY_VEXTUL        = 45741, NPC_ENTRY_CHILD_OF_TORT = 41581, NPC_ENTRY_SMOLDEROS     = 39659,
                NPC_ENTRY_FLINT         = 43047, NPC_ENTRY_WAR_GUARDIAN  = 44118, NPC_ENTRY_ACE           = 34957,
                NPC_ENTRY_GOBBER        = 34958, NPC_ENTRY_IZZY          = 34959,

                // Spells
                SPELL_AURA_BATTLEFRONT  = 85516
            };

            void HandleRemoveSummoned()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 500.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(500.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_ARTHURA:         case NPC_ENTRY_BELMONT:     case NPC_ENTRY_GODFREY:
                                    case NPC_ENTRY_ASHBURY:         case NPC_ENTRY_WALDEN:      case NPC_ENTRY_AMAKKAR:
                                    case NPC_ENTRY_GARGAL:          case NPC_ENTRY_JURRIX:      case NPC_ENTRY_ERIC:
                                    case NPC_ENTRY_BAELOG:          case NPC_ENTRY_OLAF:        case NPC_ENTRY_MINUTEMAN_1:
                                    case NPC_ENTRY_MINUTEMAN_2:     case NPC_ENTRY_MINUTEMAN_3: case NPC_ENTRY_MINUTEMAN_4:
                                    case NPC_ENTRY_ZENKIKI_1:       case NPC_ENTRY_ZENKIKI_2:   case NPC_ENTRY_ENTRHALLED_VA:
                                    case NPC_ENTRY_GIDWIN_1:        case NPC_ENTRY_TARENAR_1:   case NPC_ENTRY_TARENAR_2:
                                    case NPC_ENTRY_CHILD_OF_TORT:   case NPC_ENTRY_SMOLDEROS:   case NPC_ENTRY_FLINT:
                                    case NPC_ENTRY_WAR_GUARDIAN:    case NPC_ENTRY_ACE:         case NPC_ENTRY_GOBBER:
                                    case NPC_ENTRY_IZZY:
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
                NPC_ENTRY_LORD_GODFREY  = 45576, NPC_ENTRY_LORD_WALDEN   = 45578, NPC_ENTRY_LORD_ASHBURY  = 45577,

                // Spells
                SPELL_TRANSFORM_GODFREY = 85198, SPELL_TRANSFORM_WALDEN  = 85201, SPELL_TRANSFORM_ASHBURY = 85200,
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
                NPC_ENTRY_MESSNER       = 43300, NPC_ENTRY_JORGENSEN     = 43305, NPC_ENTRY_KRAKAUER      = 43303,
                NPC_ENTRY_DANFORTH      = 43302, NPC_ENTRY_JORGENSEN_2   = 43546, NPC_ENTRY_KEESHAN       = 48346,
                NPC_ENTRY_ARIOK         = 48567, NPC_ENTRY_AMAKKAR       = 47021, NPC_ENTRY_GARGAL        = 47022,
                NPC_ENTRY_JURRIX        = 47024, NPC_ENTRY_ERIC          = 46855, NPC_ENTRY_BAELOG        = 46856,
                NPC_ENTRY_OLAF          = 46857, NPC_ENTRY_MINUTEMAN_1   = 45231, NPC_ENTRY_MINUTEMAN_2   = 45232,
                NPC_ENTRY_MINUTEMAN_3   = 45233, NPC_ENTRY_MINUTEMAN_4   = 45234, NPC_ENTRY_GIDWIN_1      = 46173,
                NPC_ENTRY_TARENAR_1     = 45957, NPC_ENTRY_TARENAR_2     = 45794, NPC_ENTRY_VEXTUL        = 45741,
                NPC_ENTRY_IZZY          = 34959, NPC_ENTRY_GOBBER        = 34958, NPC_ENTRY_ACE           = 34957,
                NPC_ENTRY_GREELY        = 39199, NPC_ENTRY_GOBBER_COLA   = 39201, NPC_ENTRY_ACE_COLA      = 39198,
                NPC_ENTRY_IZZY_COLA     = 39200, NPC_ENTRY_ANDUIN        = 44293, NPC_ENTRY_JALARA        = 48732,
                NPC_ENTRY_DIMBLAZE      = 48731, NPC_ENTRY_DUARN         = 48733, NPC_ENTRY_MYLRA         = 48734,
                NPC_ENTRY_VERMILLION    = 45706,

                // Spell
                SPELL_SUMMON_MESSNER        = 80893, SPELL_SUMMON_JORGENSEN      = 80940, SPELL_SUMMON_KRAKAUER       = 80941,
                SPELL_SUMMON_DANFORTH       = 80943, SPELL_SUMMON_JORGENSEN_2    = 81447, SPELL_SUMMON_KEESHAN_03     = 89869,
                SPELL_SUMMON_ARIOK_03       = 90483, SPELL_SUMMON_AMAKKAR        = 87589, SPELL_SUMMON_GARGAL         = 87590,
                SPELL_SUMMON_JURRIX         = 87591, SPELL_SUMMON_ERIC           = 87262, SPELL_SUMMON_BAELOG         = 87263,
                SPELL_SUMMON_OLAF           = 87264, SPELL_SUMMON_MINUTEMAN_1    = 84452, SPELL_SUMMON_MINUTEMAN_2    = 84456,
                SPELL_SUMMON_MINUTEMAN_3    = 84457, SPELL_SUMMON_MINUTEMAN_4    = 84458, SPELL_SUMMON_MINUTEMAN_5    = 84482,
                SPELL_SUMMON_GIDWIN_1       = 85218, SPELL_SUMMON_TARENAR_1      = 85217, SPELL_SUMMON_TARENAR_2      = 85405,
                SPELL_SUMMON_VEXTUL         = 85334, SPELL_SUMMON_IZZY           = 66646, SPELL_SUMMON_GOBBER         = 66645,
                SPELL_SUMMON_ACE            = 66644, SPELL_SUMMON_GREELY         = 73603, SPELL_SUMMON_GOBBER_COLA    = 73611,
                SPELL_SUMMON_ACE_COLA       = 73601, SPELL_SUMMON_IZZY_COLA      = 73609, SPELL_SUMMON_ANDUIN         = 82823,
                SPELL_SUMMON_JALARA         = 90820, SPELL_SUMMON_DIMBLAZE       = 90813, SPELL_SUMMON_DUARN          = 90822,
                SPELL_SUMMON_MYLRA          = 90823, SPELL_SUMMON_VERM_SENTINEL  = 85295
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 120.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(120.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && ((*itr)->ToTempSummon() || (*itr)->isSummon()) && (*itr)->ToTempSummon()->GetCharmerOrOwner() == caster)
                        {
                            switch ((*itr)->ToTempSummon()->GetEntry())
                            {
                                case NPC_ENTRY_MESSNER:{if (GetSpellInfo()->Id == SPELL_SUMMON_MESSNER)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_JORGENSEN:{if (GetSpellInfo()->Id == SPELL_SUMMON_JORGENSEN)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_KRAKAUER:{if (GetSpellInfo()->Id == SPELL_SUMMON_KRAKAUER)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_DANFORTH:{if (GetSpellInfo()->Id == SPELL_SUMMON_DANFORTH)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_JORGENSEN_2:{if (GetSpellInfo()->Id == SPELL_SUMMON_JORGENSEN)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_KEESHAN:{if (GetSpellInfo()->Id == SPELL_SUMMON_KEESHAN_03)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_ARIOK:{if (GetSpellInfo()->Id == SPELL_SUMMON_ARIOK_03)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_AMAKKAR:{if (GetSpellInfo()->Id == SPELL_SUMMON_AMAKKAR)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_GARGAL:{if (GetSpellInfo()->Id == SPELL_SUMMON_GARGAL)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_JURRIX:{if (GetSpellInfo()->Id == SPELL_SUMMON_JURRIX)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_ERIC:{if (GetSpellInfo()->Id == SPELL_SUMMON_ERIC)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_BAELOG:{if (GetSpellInfo()->Id == SPELL_SUMMON_BAELOG)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_OLAF:{if (GetSpellInfo()->Id == SPELL_SUMMON_OLAF)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_MINUTEMAN_1:{if (GetSpellInfo()->Id == SPELL_SUMMON_MINUTEMAN_1 || GetSpellInfo()->Id == SPELL_SUMMON_MINUTEMAN_5)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_MINUTEMAN_2:{if (GetSpellInfo()->Id == SPELL_SUMMON_MINUTEMAN_2)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_MINUTEMAN_3:{if (GetSpellInfo()->Id == SPELL_SUMMON_MINUTEMAN_3)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_MINUTEMAN_4:{if (GetSpellInfo()->Id == SPELL_SUMMON_MINUTEMAN_4)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_GIDWIN_1:{if (GetSpellInfo()->Id == SPELL_SUMMON_GIDWIN_1)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_TARENAR_1:{if (GetSpellInfo()->Id == SPELL_SUMMON_TARENAR_1)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_TARENAR_2:{if (GetSpellInfo()->Id == SPELL_SUMMON_TARENAR_2)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_VEXTUL:{if (GetSpellInfo()->Id == SPELL_SUMMON_VEXTUL)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_IZZY:{if (GetSpellInfo()->Id == SPELL_SUMMON_IZZY)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_GOBBER:{if (GetSpellInfo()->Id == SPELL_SUMMON_GOBBER)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_ACE:{if (GetSpellInfo()->Id == SPELL_SUMMON_ACE)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_GREELY:{if (GetSpellInfo()->Id == SPELL_SUMMON_GREELY)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_GOBBER_COLA:{if (GetSpellInfo()->Id == SPELL_SUMMON_GOBBER_COLA)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_ACE_COLA:{if (GetSpellInfo()->Id == SPELL_SUMMON_ACE_COLA)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_IZZY_COLA:{if (GetSpellInfo()->Id == SPELL_SUMMON_IZZY_COLA)return SPELL_FAILED_DONT_REPORT;break;}
                                case NPC_ENTRY_ANDUIN:{if (GetSpellInfo()->Id == SPELL_SUMMON_ANDUIN)return SPELL_FAILED_DONT_REPORT; break; }
                                case NPC_ENTRY_JALARA:{if (GetSpellInfo()->Id == SPELL_SUMMON_JALARA)return SPELL_FAILED_DONT_REPORT; break; }
                                case NPC_ENTRY_DIMBLAZE:{if (GetSpellInfo()->Id == SPELL_SUMMON_DIMBLAZE)return SPELL_FAILED_DONT_REPORT; break; }
                                case NPC_ENTRY_DUARN:{if (GetSpellInfo()->Id == SPELL_SUMMON_DUARN)return SPELL_FAILED_DONT_REPORT; break; }
                                case NPC_ENTRY_MYLRA:{if (GetSpellInfo()->Id == SPELL_SUMMON_MYLRA)return SPELL_FAILED_DONT_REPORT; break; }
                                case NPC_ENTRY_VERMILLION:{if (GetSpellInfo()->Id == SPELL_SUMMON_VERM_SENTINEL)return SPELL_FAILED_DONT_REPORT; break; }
                            }
                        }
                    }
                }
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_generic_controller_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_generic_controller_SpellScript();
        }
};

class spell_chloroform : public SpellScriptLoader
{
    public:
        spell_chloroform() : SpellScriptLoader("spell_chloroform") { }

        class spell_chloroform_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_chloroform_SpellScript);

            enum Id
            {
                // Npc
                NPC_BLACKROCK_GUARD     = 7013,
                NPC_BLACKROCK_HUNTER    = 4462,
                NPC_BLACKROCK_WARDEN    = 43535,

                // Spell
                SPELL_CHLOROFORM    = 82579
            };

            void HandleApplyChloroform()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Unit* guard = caster->FindNearestCreature(NPC_BLACKROCK_GUARD, 5.0f, true))
                            guard->AddAura(SPELL_CHLOROFORM, guard);
                        else if (Unit* hunter = caster->FindNearestCreature(NPC_BLACKROCK_HUNTER, 5.0f, true))
                                hunter->AddAura(SPELL_CHLOROFORM, hunter);
                        else if (Unit* warden = caster->FindNearestCreature(NPC_BLACKROCK_WARDEN, 5.0f, true))
                                warden->AddAura(SPELL_CHLOROFORM, warden);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_chloroform_SpellScript::HandleApplyChloroform);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_chloroform_SpellScript();
        }
};

class spell_blackrock_holding_pen_key : public SpellScriptLoader
{
    public:
        spell_blackrock_holding_pen_key() : SpellScriptLoader("spell_blackrock_holding_pen_key") { }

        class spell_blackrock_holding_pen_key_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_blackrock_holding_pen_key_SpellScript);

            enum Id
            {
                // Npc
                NPC_KIDNAPPED_REDRIDGE_CITIZEN     = 43572,

                // Quest
                QUEST_PRISONERS_OF_WAR             = 43574
            };

            void HandleFree()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 15.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(15.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_KIDNAPPED_REDRIDGE_CITIZEN)
                            {
                                (*itr)->ToCreature()->SetWalk(false);
                                (*itr)->GetMotionMaster()->MovePoint(0, -9575.63f, -3261.35f, 48.91f);
                                (*itr)->ToCreature()->DespawnOrUnsummon(5000);
                            }
                        }
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_PRISONERS_OF_WAR);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_blackrock_holding_pen_key_SpellScript::HandleFree);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_blackrock_holding_pen_key_SpellScript();
        }
};

class spell_plant_seaforium : public SpellScriptLoader
{
    public:
        spell_plant_seaforium() : SpellScriptLoader("spell_plant_seaforium") { }

        class spell_plant_seaforium_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_plant_seaforium_SpellScript);

            enum Id
            {
                // Npc
                NPC_MUNITIONS_DUMP_TRIGGER  = 43589,
                NPC_BLACKROCK_TOWER_TRIGGER = 43590
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->FindNearestCreature(NPC_MUNITIONS_DUMP_TRIGGER, 10.0f, true))
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_MUNITIONS_DUMP_TRIGGER);
                            return SPELL_CAST_OK;
                        }
                        else if (caster->FindNearestCreature(NPC_BLACKROCK_TOWER_TRIGGER, 10.0f, true))
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_BLACKROCK_TOWER_TRIGGER);
                            return SPELL_CAST_OK;
                        }
                        else
                            return SPELL_FAILED_NOT_HERE;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_plant_seaforium_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_plant_seaforium_SpellScript();
        }
};

class spell_bravo_company_broadcast : public SpellScriptLoader
{
    public:
        spell_bravo_company_broadcast() : SpellScriptLoader("spell_bravo_company_broadcast") { }

        class spell_bravo_company_broadcast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bravo_company_broadcast_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_KEESHAN       = 43812,
                NPC_ENTRY_MESSNER       = 43826,
                NPC_ENTRY_JORGENSEN     = 43827,
                NPC_ENTRY_DANFORTH      = 43828,
                NPC_ENTRY_KRAKAUER      = 43829,

                // Spells
                SPELL_SUMMON_KEESHAN    = 82002,
                SPELL_SUMMON_MESSNER    = 82004,
                SPELL_SUMMON_JORGENSEN  = 82005,
                SPELL_SUMMON_DANFORTH   = 82007,
                SPELL_SUMMON_KRAKAUER   = 82008,

                // Quest
                QUEST_DARKBLADE_BROOD_OF_THE_WORLDBREAKER = 26714
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
                        caster->VisitNearbyObject(250.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_KEESHAN:
                                    case NPC_ENTRY_MESSNER:
                                    case NPC_ENTRY_JORGENSEN:
                                    case NPC_ENTRY_DANFORTH:
                                    case NPC_ENTRY_KRAKAUER:
                                    {
                                        if (caster->ToPlayer()->GetQuestStatus(QUEST_DARKBLADE_BROOD_OF_THE_WORLDBREAKER) == QUEST_STATUS_REWARDED ||
                                            caster->ToPlayer()->GetQuestStatus(QUEST_DARKBLADE_BROOD_OF_THE_WORLDBREAKER) == QUEST_STATUS_COMPLETE)
                                        {
                                            caster->RemoveAurasDueToSpell(82010);
                                            (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                                        }
                                        return;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }

                        if (caster->GetTypeId() != TYPEID_PLAYER)
                            return;

                        // Do summon creatures for quests
                        if (caster->GetMapId() == 0 && caster->GetZoneId() == 44)
                        {
                            if (caster->ToPlayer()->GetQuestStatus(QUEST_DARKBLADE_BROOD_OF_THE_WORLDBREAKER) == QUEST_STATUS_REWARDED ||
                                caster->ToPlayer()->GetQuestStatus(QUEST_DARKBLADE_BROOD_OF_THE_WORLDBREAKER) == QUEST_STATUS_COMPLETE)
                                return;

                            caster->CastSpell(caster->GetPositionX(), caster->GetPositionY()-2, caster->GetPositionZ(), SPELL_SUMMON_KEESHAN, true);
                            caster->CastSpell(caster->GetPositionX()+2, caster->GetPositionY(), caster->GetPositionZ(), SPELL_SUMMON_MESSNER, true);
                            caster->CastSpell(caster->GetPositionX()-2, caster->GetPositionY(), caster->GetPositionZ(), SPELL_SUMMON_JORGENSEN, true);
                            caster->CastSpell(caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), SPELL_SUMMON_DANFORTH, true);
                            caster->CastSpell(caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), SPELL_SUMMON_KRAKAUER, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_bravo_company_broadcast_SpellScript::HandleBroadcast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bravo_company_broadcast_SpellScript();
        }
};

class spell_bravo_company_field_kit : public SpellScriptLoader
{
    public:
        spell_bravo_company_field_kit() : SpellScriptLoader("spell_bravo_company_field_kit") { }

        class spell_bravo_company_field_kit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bravo_company_field_kit_SpellScript);

            enum Id
            {
                // Spell
                SPELL_BRAVO_COMPANY_FIELD_KIT_1     =  82580,
                SPELL_BRAVO_COMPANY_FIELD_KIT_2     =  82587
            };

            void BeforeCastSpell()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_BRAVO_COMPANY_FIELD_KIT_1))
                        caster->RemoveAurasDueToSpell(SPELL_BRAVO_COMPANY_FIELD_KIT_1);
                    if (caster->HasAura(SPELL_BRAVO_COMPANY_FIELD_KIT_2))
                        caster->RemoveAurasDueToSpell(SPELL_BRAVO_COMPANY_FIELD_KIT_2);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_bravo_company_field_kit_SpellScript::BeforeCastSpell);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bravo_company_field_kit_SpellScript();
        }
};

class spell_marked_for_retrieval : public SpellScriptLoader
{
    public:
        spell_marked_for_retrieval() : SpellScriptLoader("spell_marked_for_retrieval") { }

        enum Id
        {
            // Npc
            NPC_FALLEN_MARSHTIDE_FOOTMAN    = 46881,
            NPC_FALLEN_STONARD_WARRIOR      = 46882,

            // Spells
            SPELL_MARKED_FOR_RETRIEVAL_A      = 87293,
            SPELL_MARKED_FOR_RETRIEVAL_H      = 87296,

            // Credit
            CREDIT_FALLEN_MARKED_A            = 46909,
            CREDIT_FALLEN_MARKED_H            = 46913
        };

        class spell_marked_for_retrieval_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_marked_for_retrieval_SpellScript);

            SpellCastResult CheckCast()
            {
                Creature* fallenFootman = GetCaster()->FindNearestCreature(NPC_FALLEN_MARSHTIDE_FOOTMAN, 5.0f);
                if (fallenFootman && !fallenFootman->HasAura(SPELL_MARKED_FOR_RETRIEVAL_A))
                {
                    fallenFootman->AddAura(SPELL_MARKED_FOR_RETRIEVAL_A, fallenFootman);
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(CREDIT_FALLEN_MARKED_A);
                    return SPELL_FAILED_DONT_REPORT;
                }

                Creature* fallenOrc = GetCaster()->FindNearestCreature(NPC_FALLEN_STONARD_WARRIOR, 5.0f);
                if (fallenOrc && !fallenOrc->HasAura(SPELL_MARKED_FOR_RETRIEVAL_H))
                {
                    fallenOrc->AddAura(SPELL_MARKED_FOR_RETRIEVAL_H, fallenOrc);
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(CREDIT_FALLEN_MARKED_H);
                    return SPELL_FAILED_DONT_REPORT;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_marked_for_retrieval_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_marked_for_retrieval_SpellScript();
        }
};

class spell_enohar_explosive_arrow : public SpellScriptLoader
{
    public:
        spell_enohar_explosive_arrow() : SpellScriptLoader("spell_enohar_explosive_arrow") { }

        class spell_enohar_explosive_arrow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_enohar_explosive_arrow_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_DARKTAIL_BONEPICKER       = 42235,

                // Spells
                SPELL_FLAMING_ARROW_MISS            = 78836
            };

            void HandleCastArrow()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Unit* target = GetExplTargetUnit())
                        {
                            if (target->ToCreature())
                            {
                                if (target->ToCreature()->GetEntry() != NPC_ENTRY_DARKTAIL_BONEPICKER)
                                    return;

                                caster->CastSpell(target, SPELL_FLAMING_ARROW_MISS, false);
                                target->ToCreature()->AI()->AttackStart(caster);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_enohar_explosive_arrow_SpellScript::HandleCastArrow);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_enohar_explosive_arrow_SpellScript();
        }
};

class spell_amulet_ritual : public SpellScriptLoader
{
    public:
        spell_amulet_ritual() : SpellScriptLoader("spell_amulet_ritual") { }

        class spell_amulet_ritual_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_amulet_ritual_SpellScript);

            enum Id
            {
                QUEST_ENTRY_THE_FINAL_RITUAL = 26170
            };

            void HandleTeleport()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        target->NearTeleportTo(-11456.85f, -2631.93f, 3.79f, 4.64f);
                        target->ToPlayer()->CompleteQuest(QUEST_ENTRY_THE_FINAL_RITUAL);
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_amulet_ritual_SpellScript::HandleTeleport);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_amulet_ritual_SpellScript();
        }
};

class spell_consecrated_tripetricine : public SpellScriptLoader
{
    public:
        spell_consecrated_tripetricine() : SpellScriptLoader("spell_consecrated_tripetricine") { }

        enum Id
        {
            // Npc
            NPC_ARCHDUKE_CALCINDER   = 47462
        };

        class spell_consecrated_tripetricine_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_consecrated_tripetricine_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* archdukeCalcinder = GetCaster()->FindNearestCreature(NPC_ARCHDUKE_CALCINDER, 20.0f))
                {
                    // Allow cast only if Calcinder HP are under of equal to 50%!
                    if (archdukeCalcinder->GetHealthPct() <= 50)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_TARGET_AURASTATE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_consecrated_tripetricine_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_consecrated_tripetricine_SpellScript();
        }
};

enum DisguiseSpells
{
    SPELL_DISGUISE_FIREGUT_OGRE_M   = 89255,
    SPELL_DISGUISE_FIREGUT_OGRE_F   = 89256,
    SPELL_DISGUISE_GOBLIN_MERC_M    = 89257,
    SPELL_DISGUISE_GOBLIN_MERC_F    = 89258,
    SPELL_DISGUISE_SMOLDERTHORN_M   = 89259,
    SPELL_DISGUISE_SMOLDERTHORN_F   = 89260,
    SPELL_DISGUISE_BLACKROCK_ORC_M  = 89253,
    SPELL_DISGUISE_BLACKROCK_ORC_F  = 89254
};

class spell_blackrock_disguise : public SpellScriptLoader
{
    public:
        spell_blackrock_disguise() : SpellScriptLoader("spell_blackrock_disguise") { }

        class spell_blackrock_disguise_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_blackrock_disguise_SpellScript);

            void HandleCastDisguise()
            {
                if (Unit* caster = GetCaster())
                {
                    uint8 gender = caster->getGender();
                    if (gender == GENDER_MALE)
                    {
                        switch (caster->getRace())
                        {
                            case RACE_HUMAN:
                            case RACE_DWARF:
                            case RACE_UNDEAD_PLAYER:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_FIREGUT_OGRE_M, true);
                                break;
                            }
                            case RACE_GNOME:
                            case RACE_GOBLIN:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_GOBLIN_MERC_M, true);
                                break;
                            }
                            case RACE_NIGHTELF:
                            case RACE_BLOODELF:
                            case RACE_TROLL:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_SMOLDERTHORN_M, true);
                                break;
                            }
                            case RACE_DRAENEI:
                            case RACE_WORGEN:
                            case RACE_ORC:
                            case RACE_TAUREN:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_BLACKROCK_ORC_M, true);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch (caster->getRace())
                        {
                            case RACE_HUMAN:
                            case RACE_DWARF:
                            case RACE_UNDEAD_PLAYER:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_FIREGUT_OGRE_F, true);
                                break;
                            }
                            case RACE_GNOME:
                            case RACE_GOBLIN:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_GOBLIN_MERC_F, true);
                                break;
                            }
                            case RACE_NIGHTELF:
                            case RACE_BLOODELF:
                            case RACE_TROLL:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_SMOLDERTHORN_F, true);
                                break;
                            }
                            case RACE_DRAENEI:
                            case RACE_WORGEN:
                            case RACE_ORC:
                            case RACE_TAUREN:
                            {
                                caster->CastSpell(caster, SPELL_DISGUISE_BLACKROCK_ORC_F, true);
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
                AfterCast += SpellCastFn(spell_blackrock_disguise_SpellScript::HandleCastDisguise);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_blackrock_disguise_SpellScript();
        }
};

class spell_razor_sharp_scorpid_barb : public SpellScriptLoader
{
    public:
        spell_razor_sharp_scorpid_barb() : SpellScriptLoader("spell_razor_sharp_scorpid_barb") { }

        enum Id
        {
            // Npc
            NPC_VOODOOIST_TIMAN     = 48100,
            NPC_GORLOP              = 9176,
            NPC_WORGMISTRESS_OTHANA = 48099
        };

        class spell_razor_sharp_scorpid_barb_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_razor_sharp_scorpid_barb_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Creature* voodooistTiman = GetCaster()->FindNearestCreature(NPC_VOODOOIST_TIMAN, 7.0f))
                    {
                        voodooistTiman->Kill(voodooistTiman, false);
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_VOODOOIST_TIMAN);
                        return SPELL_CAST_OK;
                    }
                    if (Creature* npcGorlop = GetCaster()->FindNearestCreature(NPC_GORLOP, 7.0f))
                    {
                        npcGorlop->Kill(npcGorlop, false);
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_GORLOP);
                        return SPELL_CAST_OK;
                    }
                    if (Creature* worgmistressOthana = GetCaster()->FindNearestCreature(NPC_WORGMISTRESS_OTHANA, 7.0f))
                    {
                        worgmistressOthana->Kill(worgmistressOthana, false);
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_WORGMISTRESS_OTHANA);
                        return SPELL_CAST_OK;
                    }
                }

                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_razor_sharp_scorpid_barb_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_razor_sharp_scorpid_barb_SpellScript();
        }
};

class spell_worgsaw : public SpellScriptLoader
{
    public:
        spell_worgsaw() : SpellScriptLoader("spell_worgsaw") { }

        enum Id
        {
            // Npc
            NPC_GIANT_EMBER_WORG   = 9697
        };

        class spell_worgsaw_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_worgsaw_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* giantEmberWorg = GetCaster()->FindNearestCreature(NPC_GIANT_EMBER_WORG, 5.0f, false))
                {
                    giantEmberWorg->DespawnOrUnsummon(3000);
                    return SPELL_CAST_OK;
                }
                return SPELL_FAILED_TARGET_AURASTATE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_worgsaw_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_worgsaw_SpellScript();
        }
};

class spell_remove_blackrock_disguise : public SpellScriptLoader
{
    public:
        spell_remove_blackrock_disguise() : SpellScriptLoader("spell_remove_blackrock_disguise") { }

        enum Id
        {
            NPC_ENTRY_KEESHAN_03    = 48346
        };

        class spell_remove_blackrock_disguise_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_remove_blackrock_disguise_SpellScript);

            void HandleCleanupAll()
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
                                case NPC_ENTRY_KEESHAN_03:
                                {
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
                AfterCast += SpellCastFn(spell_remove_blackrock_disguise_SpellScript::HandleCleanupAll);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_remove_blackrock_disguise_SpellScript();
        }
};

class spell_loramus_demon_grip : public SpellScriptLoader
{
    public:
        spell_loramus_demon_grip() : SpellScriptLoader("spell_loramus_demon_grip") { }

        class spell_loramus_demon_grip_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_loramus_demon_grip_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* target = GetHitPlayer())
                    target->GetMotionMaster()->MoveJump(-11231.04f, -2835.09f, 157.92f, 35.0f, 35.0f);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_loramus_demon_grip_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_loramus_demon_grip_SpellScript();
        }
};

class spell_stone_knife : public SpellScriptLoader
{
    public:
        spell_stone_knife() : SpellScriptLoader("spell_stone_knife") { }

        enum Id
        {
            // Npc
            NPC_LORAMUS_THE_DEFILED   = 41292,

            // Spells
            SPELL_STONE_KNIFE         = 77380,
            SPELL_EXPLOSION_FINAL     = 74605
        };

        class spell_stone_knife_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_stone_knife_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* loramusDefiled = GetCaster()->FindNearestCreature(NPC_LORAMUS_THE_DEFILED, 10.0f, true))
                {
                    if (loramusDefiled->GetHealthPct() <= 10)
                    {
                        HandleFinalCredit();
                        return SPELL_FAILED_DONT_REPORT;
                    }
                    return SPELL_FAILED_TARGET_AURASTATE;
                }
                return SPELL_FAILED_TARGET_AURASTATE;
            }

            void HandleFinalCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Creature* loramusDefiled = GetCaster()->FindNearestCreature(NPC_LORAMUS_THE_DEFILED, 10.0f, true))
                    {
                        caster->CastWithDelay(6000, caster, SPELL_EXPLOSION_FINAL);
                        loramusDefiled->AI()->Talk(3);
                        caster->ToPlayer()->KilledMonsterCredit(NPC_LORAMUS_THE_DEFILED);
                        loramusDefiled->HandleEmoteCommand(EMOTE_STATE_STAND);
                        loramusDefiled->DespawnOrUnsummon(7500);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_stone_knife_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_stone_knife_SpellScript();
        }
};

class spell_billy_goat_blast : public SpellScriptLoader
{
    public:
        spell_billy_goat_blast() : SpellScriptLoader("spell_billy_goat_blast") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_BILLY_GOAT   = 46393
        };

        class spell_billy_goat_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_billy_goat_blast_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* billyGoat = GetCaster()->FindNearestCreature(NPC_ENTRY_BILLY_GOAT, 5.0f, true))
                    return SPELL_CAST_OK;

                if (GetExplTargetUnit() == GetCaster())
                    return SPELL_FAILED_BAD_TARGETS;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_billy_goat_blast_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_billy_goat_blast_SpellScript();
        }
};

class spell_blessed_floodlily : public SpellScriptLoader
{
    public:
        spell_blessed_floodlily() : SpellScriptLoader("spell_blessed_floodlily") { }

        enum Id
        {
            QUEST_CREDIT_FIRE_BUNNY     = 41628
        };

        class spell_blessed_floodlily_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_blessed_floodlily_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* fireBunny = GetCaster()->FindNearestCreature(QUEST_CREDIT_FIRE_BUNNY, 5.0f, true))
                {
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                    {
                        fireBunny->DespawnOrUnsummon(1);
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FIRE_BUNNY);
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_blessed_floodlily_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_blessed_floodlily_SpellScript();
        }
};

class spell_tiki_torch : public SpellScriptLoader
{
    public:
        spell_tiki_torch() : SpellScriptLoader("spell_tiki_torch") { }

        enum Id
        {
            // Npc
            QUEST_CREDIT_FIRE_BUNNY     = 42704,

            // Spell
            SPELL_AURA_BURNING          = 42726
        };

        class spell_tiki_torch_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tiki_torch_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* fireBunny = GetCaster()->FindNearestCreature(QUEST_CREDIT_FIRE_BUNNY, 10.0f, true))
                {
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (fireBunny->HasAura(SPELL_AURA_BURNING))
                            return SPELL_FAILED_DONT_REPORT;

                        fireBunny->AddAura(SPELL_AURA_BURNING, fireBunny);
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FIRE_BUNNY);
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_tiki_torch_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_tiki_torch_SpellScript();
        }
};

class spell_ritual_of_shadra : public SpellScriptLoader
{
    public:
        spell_ritual_of_shadra() : SpellScriptLoader("spell_ritual_of_shadra") { }

        enum Id
        {
            // Npc
            QUEST_CREDIT_ALTAR_NORTH        = 43067,
            QUEST_CREDIT_ALTAR_EAST         = 43069,
            QUEST_CREDIT_ALTAR_SOUTHWEST    = 43068,
        };

        class spell_ritual_of_shadra_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ritual_of_shadra_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* altarBunnyNorth = GetCaster()->FindNearestCreature(QUEST_CREDIT_ALTAR_NORTH, 8.0f, true))
                    return SPELL_CAST_OK;
                else if (Creature* altarBunnyEast = GetCaster()->FindNearestCreature(QUEST_CREDIT_ALTAR_EAST, 8.0f, true))
                    return SPELL_CAST_OK;
                else if (Creature* altarBunnySouthWest = GetCaster()->FindNearestCreature(QUEST_CREDIT_ALTAR_SOUTHWEST, 8.0f, true))
                    return SPELL_CAST_OK;
                else
                    return SPELL_FAILED_INCORRECT_AREA;
            }

            void HandleQuestCredit()
            {
                if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Creature* altarBunnyNorth = GetCaster()->FindNearestCreature(QUEST_CREDIT_ALTAR_NORTH, 8.0f, true))
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ALTAR_NORTH);

                    if (Creature* altarBunnyEast = GetCaster()->FindNearestCreature(QUEST_CREDIT_ALTAR_EAST, 8.0f, true))
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ALTAR_EAST);

                    if (Creature* altarBunnySouthWest = GetCaster()->FindNearestCreature(QUEST_CREDIT_ALTAR_SOUTHWEST, 8.0f, true))
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ALTAR_SOUTHWEST);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_ritual_of_shadra_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_ritual_of_shadra_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ritual_of_shadra_SpellScript();
        }
};

class spell_shadow_prison : public SpellScriptLoader
{
    public:
        spell_shadow_prison() : SpellScriptLoader("spell_shadow_prison") { }

        class spell_shadow_prison_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_shadow_prison_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget())
                {
                    GetTarget()->GetMotionMaster()->MovePoint(0, 1284.73f, -1529.88f, 66.88f, false);
                    GetTarget()->SendGravityDisable();
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget())
                    GetTarget()->SendGravityEnable();
            }

            void Register()
            {
                AfterEffectApply += AuraEffectRemoveFn(spell_shadow_prison_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_shadow_prison_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_shadow_prison_AuraScript();
        }
};

class spell_place_dithers_drum : public SpellScriptLoader
{
    public:
        spell_place_dithers_drum() : SpellScriptLoader("spell_place_dithers_drum") { }

        enum Id
        {
            // GameObjects GUID
            GO_GUID_WINDMILL_1  = 79117,
            GO_GUID_WINDMILL_2  = 79163,
            GO_GUID_GRAIN_SILOS = 79137,
            GO_GUID_RANCH_HOUSE = 79174,
            GO_GUID_BARN        = 79169,

            // GameObject Entry
            GO_ENTRY_DRUM       = 205069,

            // Quest Credit
            QUEST_CREDIT_WINDMILL       = 44622,
            QUEST_CREDIT_GRAIN_SILOS    = 44623,
            QUEST_CREDIT_RANCH_HOUSE    = 44624,
            QUEST_CREDIT_BARN           = 44625
        };

        class spell_place_dithers_drum_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_place_dithers_drum_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                GameObject* drums = NULL;
                Trinity::GameObjectInRangeCheck check(GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ(), 15);
                Trinity::GameObjectLastSearcher<Trinity::GameObjectInRangeCheck> searcher(GetCaster(), drums, check);
                GetCaster()->VisitNearbyGridObject(15, searcher);
                if (drums)
                {
                    switch (drums->GetGUIDLow())
                    {
                        case GO_GUID_WINDMILL_1:
                        case GO_GUID_WINDMILL_2:
                        case GO_GUID_GRAIN_SILOS:
                        case GO_GUID_RANCH_HOUSE:
                        case GO_GUID_BARN:
                            return SPELL_CAST_OK;
                        default:
                            return SPELL_FAILED_NOT_HERE;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleQuestCredit()
            {
                if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                {
                    GameObject* drums = NULL;
                    Trinity::GameObjectInRangeCheck check(GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ(), 10);
                    Trinity::GameObjectLastSearcher<Trinity::GameObjectInRangeCheck> searcher(GetCaster(), drums, check);
                    GetCaster()->VisitNearbyGridObject(10, searcher);
                    if (drums)
                    {
                        switch (drums->GetGUIDLow())
                        {
                            case GO_GUID_WINDMILL_1:
                            case GO_GUID_WINDMILL_2:
                            {
                                GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WINDMILL);
                                break;
                            }
                            case GO_GUID_GRAIN_SILOS:
                            {
                                GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GRAIN_SILOS);
                                break;
                            }
                            case GO_GUID_RANCH_HOUSE:
                            {
                                GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_RANCH_HOUSE);
                                break;
                            }
                            case GO_GUID_BARN:
                            {
                                GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_BARN);
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
                OnCheckCast += SpellCheckCastFn(spell_place_dithers_drum_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_place_dithers_drum_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_place_dithers_drum_SpellScript();
        }
};

class spell_overcharge_effect : public SpellScriptLoader
{
    public:
        spell_overcharge_effect() : SpellScriptLoader("spell_overcharge_effect") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_PLAGUE_DISSEMINATOR               = 45475,
            SPELL_ENTRY_OVERCHARGE_EFFECT               = 84972,
            ITEM_ENTRY_PLAGUE_DISSEMINATOR_CONTROL_RUNE = 61037
        };

        class spell_overcharge_effect_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_overcharge_effect_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                if (Creature* plagueDisseminator = GetCaster()->FindNearestCreature(NPC_ENTRY_PLAGUE_DISSEMINATOR, 75.0f, true))
                {
                    GetCaster()->CastSpell(plagueDisseminator, SPELL_ENTRY_OVERCHARGE_EFFECT, true);
                    GetCaster()->ToPlayer()->DestroyItemCount(ITEM_ENTRY_PLAGUE_DISSEMINATOR_CONTROL_RUNE, 1, true);
                    return SPELL_FAILED_DONT_REPORT;
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_overcharge_effect_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_overcharge_effect_SpellScript();
        }
};

class spell_raynes_seed : public SpellScriptLoader
{
    public:
        spell_raynes_seed() : SpellScriptLoader("spell_raynes_seed") { }

        enum Id
        {
            NPC_TRIGGER_1   = 45486,
            NPC_TRIGGER_2   = 45487,
            NPC_TRIGGER_3   = 45488,
            NPC_FLOWER_TRIG = 45485
        };

        class spell_raynes_seed_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_raynes_seed_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                Creature* trigger1 = GetCaster()->FindNearestCreature(NPC_TRIGGER_1, 30.0f, true);
                Creature* trigger2 = GetCaster()->FindNearestCreature(NPC_TRIGGER_2, 30.0f, true);
                Creature* trigger3 = GetCaster()->FindNearestCreature(NPC_TRIGGER_3, 30.0f, true);
                if (trigger1 || trigger2 || trigger3)
                    return SPELL_CAST_OK;

                return SPELL_FAILED_NOT_HERE;
            }

            void HandleQuestCredit()
            {
                if (GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER)
                {
                    Creature* trigger1 = GetCaster()->FindNearestCreature(NPC_TRIGGER_1, 30.0f, true);
                    Creature* trigger2 = GetCaster()->FindNearestCreature(NPC_TRIGGER_2, 30.0f, true);
                    Creature* trigger3 = GetCaster()->FindNearestCreature(NPC_TRIGGER_3, 30.0f, true);
                    if (trigger1)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_TRIGGER_1);
                    else if (trigger2)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_TRIGGER_2);
                    else if (trigger3)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_TRIGGER_3);

                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(GetCaster(), GetCaster(), 80.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(GetCaster(), targets, u_check);
                    GetCaster()->VisitNearbyObject(80.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if (!(*itr)->ToCreature())
                            continue;

                        if ((*itr)->ToCreature()->GetEntry() != NPC_FLOWER_TRIG)
                            continue;

                        (*itr)->ToCreature()->AI()->SetData(0, 1);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_raynes_seed_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_raynes_seed_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_raynes_seed_SpellScript();
        }
};

class spell_gather_liquid_sample : public SpellScriptLoader
{
    public:
        spell_gather_liquid_sample() : SpellScriptLoader("spell_gather_liquid_sample") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_PLAGUE_RAVAGER    = 8520
        };

        class spell_gather_liquid_sample_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gather_liquid_sample_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* plagueRavager = GetCaster()->FindNearestCreature(NPC_ENTRY_PLAGUE_RAVAGER, 5.0f, false))
                {
                    if (plagueRavager->getDeathState() == CORPSE)
                    {
                        plagueRavager->DespawnOrUnsummon(1);
                        return SPELL_CAST_OK;
                    }
                }

                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_gather_liquid_sample_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gather_liquid_sample_SpellScript();
        }
};

class spell_trial_of_the_crypt : public SpellScriptLoader
{
    public:
        spell_trial_of_the_crypt() : SpellScriptLoader("spell_trial_of_the_crypt") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_LORD_RAYMOND_GEORGE    = 45707
        };

        class spell_trial_of_the_crypt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_trial_of_the_crypt_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* lordRaymond = GetCaster()->FindNearestCreature(NPC_ENTRY_LORD_RAYMOND_GEORGE, 8.0f, true))
                {
                    if (lordRaymond->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_31))
                        return SPELL_FAILED_DONT_REPORT;
                    return SPELL_CAST_OK;
                }

                return SPELL_FAILED_INCORRECT_AREA;
            }

            void HandleInitEvent()
            {
                if (Creature* lordRaymond = GetCaster()->FindNearestCreature(NPC_ENTRY_LORD_RAYMOND_GEORGE, 8.0f, true))
                {
                    // Set Event in Progress and init Lord Raymond George
                    lordRaymond->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_31);
                    lordRaymond->AI()->SetData(0, 1);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_trial_of_the_crypt_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_trial_of_the_crypt_SpellScript::HandleInitEvent);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_trial_of_the_crypt_SpellScript();
        }
};

class spell_bury_blade : public SpellScriptLoader
{
    public:
        spell_bury_blade() : SpellScriptLoader("spell_bury_blade") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_SLAINED_SCOURGE_TROOPER    = 45695,
            SPELL_BURY_BLADE                     = 85252
        };

        class spell_bury_blade_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bury_blade_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetExplTargetUnit() && GetExplTargetUnit()->ToCreature())
                {
                    if (GetExplTargetUnit()->ToCreature()->GetEntry() == NPC_ENTRY_SLAINED_SCOURGE_TROOPER && !GetExplTargetUnit()->HasAura(SPELL_BURY_BLADE))
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_bury_blade_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bury_blade_SpellScript();
        }
};

class spell_destroy_threshjin_body : public SpellScriptLoader
{
    public:
        spell_destroy_threshjin_body() : SpellScriptLoader("spell_destroy_threshjin_body") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_ZIGURRAT_BONFIRE          = 41200,
            QUEST_CREDIT_INTO_THE_FLAMES        = 45738
        };

        class spell_destroy_threshjin_body_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_destroy_threshjin_body_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->FindNearestCreature(NPC_ENTRY_ZIGURRAT_BONFIRE, 10.0f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleQuestCredit()
            {
                if (GetCaster() && GetCaster()->ToPlayer())
                    GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_INTO_THE_FLAMES);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_destroy_threshjin_body_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_destroy_threshjin_body_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_destroy_threshjin_body_SpellScript();
        }
};

class spell_burn_corpse : public SpellScriptLoader
{
    public:
        spell_burn_corpse() : SpellScriptLoader("spell_burn_corpse") { }

        enum Id
        {
            // Npc
            NPC_OVERSTUFFED_GOLEM           = 45851,
            SPELL_ENTRY_BURN_CORPSE         = 85555
        };

        class spell_burn_corpse_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_burn_corpse_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* overstuffedGolem = GetCaster()->FindNearestCreature(NPC_OVERSTUFFED_GOLEM, 7.0f, false))
                {
                    if (!overstuffedGolem->HasAura(SPELL_ENTRY_BURN_CORPSE) && overstuffedGolem->getDeathState() == CORPSE)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_burn_corpse_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_burn_corpse_SpellScript();
        }
};

class spell_summon_argent_lightwell : public SpellScriptLoader
{
    public:
        spell_summon_argent_lightwell() : SpellScriptLoader("spell_summon_argent_lightwell") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_CORPSEBEAST         = 45895,
            NPC_ENTRY_ARGENT_LIGHTWELL      = 45921,

            // Spell
            SPELL_HOLY_OVERLOAD             = 85594
        };

        class spell_summon_argent_lightwell_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_argent_lightwell_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* corpsebeast = GetCaster()->FindNearestCreature(NPC_ENTRY_CORPSEBEAST, 10.0f, true))
                {
                    if (Creature* argentLightwell = GetCaster()->FindNearestCreature(NPC_ENTRY_ARGENT_LIGHTWELL, 10.0f, true))
                        return SPELL_FAILED_NOT_HERE;
                    else
                    {
                        GetCaster()->CastSpell(GetCaster(), SPELL_HOLY_OVERLOAD, true);
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_argent_lightwell_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_argent_lightwell_SpellScript();
        }
};

class spell_gen_cosmetic_rope : public SpellScriptLoader
{
    public:
        spell_gen_cosmetic_rope() : SpellScriptLoader("spell_gen_cosmetic_rope") { }

        class spell_gen_cosmetic_rope_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_cosmetic_rope_AuraScript);

            enum Id
            {
                // Quest
                QUEST_ENTRY_WARRIORS_REDEMPTION     = 24512,

                // Npc
                NPC_ROPE_TRIGGER                    = 37168,

                // GUID
                GUID_ROPE_TRIGGER_UP                = 400900
            };

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster())
                {
                    if (GetCaster()->ToPlayer())
                    {
                        if (GetCaster()->ToPlayer()->GetQuestStatus(QUEST_ENTRY_WARRIORS_REDEMPTION) == QUEST_STATUS_INCOMPLETE ||
                        GetCaster()->ToPlayer()->GetQuestStatus(QUEST_ENTRY_WARRIORS_REDEMPTION) == QUEST_STATUS_COMPLETE)
                        {
                            if (Creature* ropeTrigger = GetCaster()->FindNearestCreature(NPC_ROPE_TRIGGER, 15.0f, true))
                            {
                                if (ropeTrigger->GetGUIDLow() == GUID_ROPE_TRIGGER_UP)
                                    GetCaster()->GetMotionMaster()->MoveJump(-560.66f, -1409.69f, 92.56f, 32.5f, 32.5f);
                                else
                                    GetCaster()->GetMotionMaster()->MoveJump(-616.14f, -1410.87f, 157.68f, 32.5f, 32.5f);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectRemoveFn(spell_gen_cosmetic_rope_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_cosmetic_rope_AuraScript();
        }
};

class spell_blow_horn_of_challenge : public SpellScriptLoader
{
    public:
        spell_blow_horn_of_challenge() : SpellScriptLoader("spell_blow_horn_of_challenge") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_SABERSNOUT   = 37513
        };

        class spell_blow_horn_of_challenge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_blow_horn_of_challenge_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* sabersnout = GetCaster()->FindNearestCreature(NPC_ENTRY_SABERSNOUT, 15.0f, true))
                {
                    sabersnout->AI()->SetData(0, 1);
                    return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_blow_horn_of_challenge_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_blow_horn_of_challenge_SpellScript();
        }
};

class spell_soothing_seeds : public SpellScriptLoader
{
    public:
        spell_soothing_seeds() : SpellScriptLoader("spell_soothing_seeds") { }

        class spell_soothing_seeds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_soothing_seeds_SpellScript);

            enum Id
            {
                NPC_ENTRY_DEVIATE_TERRORTOOTHS  = 37090,
                NPC_ENTRY_DEVIATE_PLAINSTRIDER  = 37091
            };

            SpellCastResult CheckCast()
            {
                // Not on self!
                if (GetExplTargetUnit() && GetExplTargetUnit()->ToCreature() &&
                    (GetExplTargetUnit()->ToCreature()->GetEntry() == NPC_ENTRY_DEVIATE_TERRORTOOTHS ||
                    GetExplTargetUnit()->ToCreature()->GetEntry() == NPC_ENTRY_DEVIATE_PLAINSTRIDER))
                    return SPELL_CAST_OK;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (!target->ToCreature())
                        return;

                    if (!GetCaster()->ToPlayer())
                        return;

                    if (target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
                        return;

                    // Chance Attack Caster
                    if (roll_chance_i(25))
                    {
                        target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        target->setFaction(14);
                        target->ToCreature()->DespawnOrUnsummon(15000);
                        if (GetCaster())
                        {
                            target->ToCreature()->AI()->AttackStart(GetCaster());
                            GetCaster()->ToPlayer()->KilledMonsterCredit(37726);
                        }
                        return;
                    }
                    // Chance Explode!
                    else if (roll_chance_i(45))
                    {
                        target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        target->CastSpell(target, 72942, true);
                        target->Kill(target, false);
                        if (GetCaster())
                            GetCaster()->ToPlayer()->KilledMonsterCredit(37726);
                        target->ToCreature()->DespawnOrUnsummon(10000);
                        return;
                    }
                    else
                    {
                        target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        target->setFaction(35);
                        target->ToCreature()->DespawnOrUnsummon(8000);
                        if (GetCaster())
                            GetCaster()->ToPlayer()->KilledMonsterCredit(37726);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_soothing_seeds_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_soothing_seeds_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_soothing_seeds_SpellScript();
        }
};

class spell_flag_capture : public SpellScriptLoader
{
    public:
        spell_flag_capture() : SpellScriptLoader("spell_flag_capture") { }

        enum Id
        {
            // Npc
            QUEST_CREDIT_FLAG_CAPTURED_H    = 37667,
            QUEST_CREDIT_FLAG_CAPTURED_A    = 39029,
            QUEST_CREDIT_FLAG_DEFENDED_H    = 37668,
            QUEST_CREDIT_FLAG_DEFENDED_A    = 39030,
            NPC_HORDE_FIELD_DEFENDER        = 37659,
            NPC_ALLIANCE_FIELD_DEFENDER     = 39040,

            // GameObjects
            GO_HORDE_FIELD_BANNER       = 201744,
            GO_HORDE_FIELD_BARRICADE    = 201748,
            GO_ALLIANCE_FIELD_BANNER    = 202460,
            GO_ALLIANCE_FIELD_WALL      = 202462,
        };

        class spell_flag_capture_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_flag_capture_SpellScript);

            void HandleStartDefend(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetHitUnit())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->ToPlayer()->MonsterWhisper("Defend the Hill!", caster->ToPlayer()->GetGUID(), true);
                    if (caster->ToPlayer()->GetTeam() == HORDE)
                    {
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FLAG_CAPTURED_H);
                        caster->ToPlayer()->SummonGameObject(GO_HORDE_FIELD_BANNER, -2129.87f, -2080.86f, 99.29f, 1.04f, 0, 0, 0, 3, 75);
                        caster->ToPlayer()->SummonGameObject(GO_HORDE_FIELD_BARRICADE, -2137.42f, -2065.79f, 98.71f, 1.83f, 0, 0, 0.793353f, 0.608762f, 75);
                        caster->ToPlayer()->SummonGameObject(GO_HORDE_FIELD_BARRICADE, -2113.86f, -2075.02f, 97.12f, 0.55f, 0, 0, 0.275637f, 0.961262f, 75);
                        caster->ToPlayer()->SummonGameObject(GO_HORDE_FIELD_BARRICADE, -2134.44f, -2094.07f, 98.72f, 4.32f, 0, 0, 0.829037f, 0.559194f, 75);
                        caster->ToPlayer()->SummonCreature(NPC_HORDE_FIELD_DEFENDER, -2116.24f, -2076.48f, 97.31f, 0.53f, TEMPSUMMON_TIMED_DESPAWN, 75000);
                        caster->ToPlayer()->SummonCreature(NPC_HORDE_FIELD_DEFENDER, -2136.87f, -2067.44f, 98.92f, 1.84f, TEMPSUMMON_TIMED_DESPAWN, 75000);
                        caster->ToPlayer()->SummonCreature(NPC_HORDE_FIELD_DEFENDER, -2133.71f, -2092.01f, 98.88f, 4.36f, TEMPSUMMON_TIMED_DESPAWN, 75000);
                    }
                    else
                    {
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FLAG_CAPTURED_A);
                        caster->ToPlayer()->SummonGameObject(GO_ALLIANCE_FIELD_BANNER, -2466.41f, -2306.98f, 100.23f, 5.48f, 0, 0, 0, 1, 75);
                        caster->ToPlayer()->SummonGameObject(GO_ALLIANCE_FIELD_WALL, -2477.86f, -2315.64f, 98.97f, 3.48f, 0, 0, 0.984994f, -0.17259f, 75);
                        caster->ToPlayer()->SummonGameObject(GO_ALLIANCE_FIELD_WALL, -2458.55f, -2294.49f, 99.45f, 1.44f, 0, 0, 0.661602f, 0.749855f, 75);
                        caster->ToPlayer()->SummonGameObject(GO_ALLIANCE_FIELD_WALL, -2446.58f, -2309.83f, 100.151f, 5.95f, 0, 0, 0.161869f, 0.986812f, 75);
                        caster->ToPlayer()->SummonCreature(NPC_ALLIANCE_FIELD_DEFENDER, -2476.34f, -2314.98f, 99.24f, 3.59f, TEMPSUMMON_TIMED_DESPAWN, 75000);
                        caster->ToPlayer()->SummonCreature(NPC_ALLIANCE_FIELD_DEFENDER, -2458.62f, -2296.13f, 99.68f, 1.58f, TEMPSUMMON_TIMED_DESPAWN, 75000);
                        caster->ToPlayer()->SummonCreature(NPC_ALLIANCE_FIELD_DEFENDER, -2448.89f, -2308.84f, 100.24f, 5.88f, TEMPSUMMON_TIMED_DESPAWN, 75000);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_flag_capture_SpellScript::HandleStartDefend, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_flag_capture_SpellScript();
        }
};

class spell_dismembering : public SpellScriptLoader
{
    public:
        spell_dismembering() : SpellScriptLoader("spell_dismembering") { }

        class spell_dismembering_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dismembering_SpellScript);

            enum Id
            {
                NPC_ENTRY_TRIUMPH_VANGUARD  = 37923,
                SPELL_SUMMON_REMAINS        = 70828
            };

            SpellCastResult CheckCast()
            {
                // Not on self!
                if (GetExplTargetUnit() && GetExplTargetUnit()->ToCreature() &&
                    GetExplTargetUnit()->ToCreature()->GetEntry() == NPC_ENTRY_TRIUMPH_VANGUARD)
                    return SPELL_CAST_OK;

                if (GetExplTargetUnit()->getDeathState() != CORPSE)
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void HandleDismembering()
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (!target->ToCreature())
                        return;

                    if (!GetCaster()->ToPlayer())
                        return;

                    if (target->getDeathState() != CORPSE)
                        return;

                    target->CastSpell(target, SPELL_SUMMON_REMAINS, true);
                    target->ToCreature()->DespawnOrUnsummon(1000);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dismembering_SpellScript::HandleDismembering);
                OnCheckCast += SpellCheckCastFn(spell_dismembering_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dismembering_SpellScript();
        }
};

class spell_burning_pitch : public SpellScriptLoader
{
    public:
        spell_burning_pitch() : SpellScriptLoader("spell_burning_pitch") { }

        class spell_burning_pitch_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_burning_pitch_SpellScript);

            enum Id
            {
                NPC_ENTRY_SILITHID_MOUND_BUNNY  = 38055
            };

            SpellCastResult CheckCast()
            {
                if (Creature* moundBunny = GetCaster()->FindNearestCreature(NPC_ENTRY_SILITHID_MOUND_BUNNY, 15.0f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_burning_pitch_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_burning_pitch_SpellScript();
        }
};

class spell_sabotage_bael_dun : public SpellScriptLoader
{
    public:
        spell_sabotage_bael_dun() : SpellScriptLoader("spell_sabotage_bael_dun") { }

        class spell_sabotage_bael_dun_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sabotage_bael_dun_SpellScript);

            enum Id
            {
                QUEST_CREDIT_ARTILLERY_SHELL_SABOTAGE   = 38250,
                NPC_ENTRY_ARTILLERY_SHELL_1             = 38109,
                NPC_ENTRY_ARTILLERY_SHELL_2             = 38190,
                GO_ENTRY_ARTILLERY_GEAR                 = 201963,
                SPELL_RUN_FOR_IT                        = 71455,
                SOUND_HORN                              = 7234
            };

            void HandleCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ARTILLERY_SHELL_SABOTAGE);
                    if (Creature* artilleryShell = caster->FindNearestCreature(NPC_ENTRY_ARTILLERY_SHELL_1, 10.0f, true))
                    {
                        artilleryShell->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        artilleryShell->GetMotionMaster()->MoveJump(artilleryShell->GetPositionX(), artilleryShell->GetPositionY(), artilleryShell->GetPositionZ()+15, 0.7f, 0.7f);
                        artilleryShell->DespawnOrUnsummon(15000);
                        caster->PlayDirectSound(SOUND_HORN);
                        artilleryShell->AI()->TalkWithDelay(10000, 0, caster->GetGUID());
                        caster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SHEATHE);
                        caster->CastSpell(caster, SPELL_RUN_FOR_IT, true);
                    }
                    if (Creature* artilleryShell = caster->FindNearestCreature(NPC_ENTRY_ARTILLERY_SHELL_2, 10.0f, true))
                    {
                        artilleryShell->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        artilleryShell->GetMotionMaster()->MoveJump(artilleryShell->GetPositionX(), artilleryShell->GetPositionY(), artilleryShell->GetPositionZ()+15, 0.7f, 0.7f);
                        artilleryShell->DespawnOrUnsummon(15000);
                        caster->PlayDirectSound(SOUND_HORN);
                        artilleryShell->AI()->TalkWithDelay(10000, 0, caster->GetGUID());
                        caster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SHEATHE);
                        caster->CastSpell(caster, SPELL_RUN_FOR_IT, true);
                    }
                    if (GameObject* artilleryGears = caster->FindNearestGameObject(GO_ENTRY_ARTILLERY_GEAR, 10.0f))
                        artilleryGears->SetGoState(GO_STATE_ACTIVE);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_sabotage_bael_dun_SpellScript::HandleCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sabotage_bael_dun_SpellScript();
        }
};

class spell_throw_torch_catapult : public SpellScriptLoader
{
    public:
        spell_throw_torch_catapult() : SpellScriptLoader("spell_throw_torch_catapult") { }

        class spell_throw_torch_catapult_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_throw_torch_catapult_SpellScript);

            enum Id
            {
                NPC_ENTRY_RAGEROAR_CATAPULT         = 38818,
                NPC_ENTRY_RAGEROAR_BLADE_THROWER    = 38820,
                SPELL_AURA_FIRE                     = 73119
            };

            SpellCastResult CheckCast()
            {
                if (Creature* rageroarCatapult = GetCaster()->FindNearestCreature(NPC_ENTRY_RAGEROAR_CATAPULT, 10.0f, true))
                {
                    if (!rageroarCatapult->HasAura(SPELL_AURA_FIRE))
                        return SPELL_CAST_OK;
                }
                if (Creature* rageroarBladeThrower = GetCaster()->FindNearestCreature(NPC_ENTRY_RAGEROAR_BLADE_THROWER, 10.0f, true))
                {
                    if (!rageroarBladeThrower->HasAura(SPELL_AURA_FIRE))
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_throw_torch_catapult_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_throw_torch_catapult_SpellScript();
        }
};

class spell_bramblestaff : public SpellScriptLoader
{
    public:
        spell_bramblestaff() : SpellScriptLoader("spell_bramblestaff") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_THREE_TOOTH    = 38941
        };

        class spell_bramblestaff_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bramblestaff_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetExplTargetUnit() && GetExplTargetUnit()->ToCreature() && GetExplTargetUnit()->ToCreature()->GetEntry() == NPC_ENTRY_THREE_TOOTH)
                    return SPELL_CAST_OK;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (!target->ToCreature())
                        return;

                    if (target->ToCreature()->GetEntry() != NPC_ENTRY_THREE_TOOTH)
                        return;

                    if (target->GetHealthPct() <= 50)
                        return;
                    else
                        target->SetHealth(target->GetMaxHealth() / 2);

                    GetCaster()->CastSpell(target, 73136, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_bramblestaff_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_bramblestaff_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bramblestaff_SpellScript();
        }
};

class spell_clap_em_in_irons : public SpellScriptLoader
{
    public:
        spell_clap_em_in_irons() : SpellScriptLoader("spell_clap_em_in_irons") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_TAURAJO_LOOTER    = 37743,
            SPELL_ENTRY_I_AM_THE_LAW    = 73386,

            QUEST_CREDIT_LAW            = 39050
        };

        class spell_clap_em_in_irons_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_clap_em_in_irons_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetExplTargetUnit() && GetExplTargetUnit()->ToCreature() && GetExplTargetUnit()->ToCreature()->GetEntry() == NPC_ENTRY_TAURAJO_LOOTER)
                {
                    if (GetExplTargetUnit()->GetHealthPct() <= 50)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void HandleQuestCredit()
            {
                if (GetCaster() && GetExplTargetUnit())
                {
                    GetCaster()->CastSpell(GetCaster(), SPELL_ENTRY_I_AM_THE_LAW, true);
                    if (GetExplTargetUnit()->ToCreature())
                    {
                        GetExplTargetUnit()->ToCreature()->setFaction(35);
                        GetExplTargetUnit()->ToCreature()->SetStandState(UNIT_STAND_STATE_KNEEL);
                        GetExplTargetUnit()->ToCreature()->SetControlled(true, UNIT_STATE_CANNOT_AUTOATTACK);
                        GetExplTargetUnit()->ToCreature()->DespawnOrUnsummon(2500);
                    }
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_LAW);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_clap_em_in_irons_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_clap_em_in_irons_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_clap_em_in_irons_SpellScript();
        }
};

class spell_frazzlecraz_cave : public SpellScriptLoader
{
    public:
        spell_frazzlecraz_cave() : SpellScriptLoader("spell_frazzlecraz_cave") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_EXPLOSION_BUNNY   = 38821,

            // Spells
            SPELL_EXPLOSION_VISUAL      = 71495,
            SPELL_CAVE_IN               = 96935
        };

        class spell_frazzlecraz_cave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_frazzlecraz_cave_SpellScript);

            void HandleExplodeCave()
            {
                std::list<Unit*> targets;
                Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(GetCaster(), GetCaster(), 150.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(GetCaster(), targets, u_check);
                GetCaster()->VisitNearbyObject(120.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_EXPLOSION_BUNNY)
                    {
                        (*itr)->CastSpell((*itr), SPELL_EXPLOSION_VISUAL, true);
                        (*itr)->CastWithDelay(urand(2500, 4500), (*itr), SPELL_EXPLOSION_VISUAL, true);
                        (*itr)->CastSpell((*itr), SPELL_CAVE_IN, true);
                        (*itr)->CastSpell((*itr), SPELL_CAVE_IN, true);
                        (*itr)->CastSpell((*itr), SPELL_CAVE_IN, true);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_frazzlecraz_cave_SpellScript::HandleExplodeCave);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_frazzlecraz_cave_SpellScript();
        }
};

class spell_burn_direhorn_post : public SpellScriptLoader
{
    public:
        spell_burn_direhorn_post() : SpellScriptLoader("spell_burn_direhorn_post") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_NORT_TENT         = 23751,
            NPC_ENTRY_NORTHEAST_TENT    = 23752,
            NPC_ENTRY_EAST_TENT         = 23753
        };

        class spell_burn_direhorn_post_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_burn_direhorn_post_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* northTent = GetCaster()->FindNearestCreature(NPC_ENTRY_NORT_TENT, 20.0f, true))
                    return SPELL_CAST_OK;
                if (Creature* northEastTent = GetCaster()->FindNearestCreature(NPC_ENTRY_NORTHEAST_TENT, 20.0f, true))
                    return SPELL_CAST_OK;
                if (Creature* eastTent = GetCaster()->FindNearestCreature(NPC_ENTRY_EAST_TENT, 20.0f, true))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_burn_direhorn_post_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_burn_direhorn_post_SpellScript();
        }
};

class spell_redeem_remains : public SpellScriptLoader
{
    public:
        spell_redeem_remains() : SpellScriptLoader("spell_redeem_remains") { }

        enum Id
        {
            // Spell
            SPELL_SUMMON_STONEMAUL_SPIRIT   = 42421
        };

        class spell_redeem_remains_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_redeem_remains_SpellScript);

            void HandleSummonSpirit()
            {
                if (GetCaster())
                    GetCaster()->CastSpell(GetCaster(), SPELL_SUMMON_STONEMAUL_SPIRIT, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_redeem_remains_SpellScript::HandleSummonSpirit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_redeem_remains_SpellScript();
        }
};

class spell_unleash_captured_raptor : public SpellScriptLoader
{
    public:
        spell_unleash_captured_raptor() : SpellScriptLoader("spell_unleash_captured_raptor") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_CAPTURED_RAPTOR       = 23741,

            // Quest
            QUEST_CREDIT_UNLEASH_RAPTOR     = 23727
        };

        class spell_unleash_captured_raptor_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_unleash_captured_raptor_SpellScript);

            void HandleSummonRaptors()
            {
                if (GetCaster())
                {
                    GetCaster()->SummonCreature(NPC_ENTRY_CAPTURED_RAPTOR, -2464.91f, -3197.96f, 35.15f, 1.34f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    GetCaster()->SummonCreature(NPC_ENTRY_CAPTURED_RAPTOR, -2443.14f, -3109.12f, 34.60f, 4.67f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    GetCaster()->SummonCreature(NPC_ENTRY_CAPTURED_RAPTOR, -2408.54f, -3178.24f, 36.09f, 2.69f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    GetCaster()->SummonCreature(NPC_ENTRY_CAPTURED_RAPTOR, -2475.04f, -3178.17f, 33.14f, 0.63f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    GetCaster()->SummonCreature(NPC_ENTRY_CAPTURED_RAPTOR, -2478.06f, -3164.52f, 33.19f, 0.09f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    GetCaster()->SummonCreature(NPC_ENTRY_CAPTURED_RAPTOR, -2507.24f, -3213.37f, 33.00f, 0.84f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    if (GetCaster()->ToPlayer())
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_UNLEASH_RAPTOR);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_unleash_captured_raptor_SpellScript::HandleSummonRaptors);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_unleash_captured_raptor_SpellScript();
        }
};

class spell_lay_wreath : public SpellScriptLoader
{
    public:
        spell_lay_wreath() : SpellScriptLoader("spell_lay_wreath") { }

        enum Id
        {
            // Quest
            QUEST_CREDIT_LAY_WREATH     = 23768,
            GO_COURONNE                 = 186315
        };

        class spell_lay_wreath_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lay_wreath_SpellScript);

            void HandleQuestCredit()
            {
                if (GetCaster())
                {
                    if (GetCaster()->ToPlayer())
                    {
                        GetCaster()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_LAY_WREATH);
                        GetCaster()->SummonGameObject(GO_COURONNE, -3533.67f, -4317.43f, 7.03f, 6.02f, 0, 0, 0.13f, -0.99f, 60);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_lay_wreath_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lay_wreath_SpellScript();
        }
};

class spell_salvage_wreckage : public SpellScriptLoader
{
    public:
        spell_salvage_wreckage() : SpellScriptLoader("spell_salvage_wreckage") { }

        enum Id
        {
            // Quest
            QUEST_ITEM_SALVAGED_STRONGBOX   = 33041,
            GO_SHIPWRECK_DEBRIS             = 11
        };

        class spell_salvage_wreckage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_salvage_wreckage_SpellScript);

            void HandleQuestCredit()
            {
                if (GetCaster())
                {
                    if (GetCaster()->ToPlayer())
                        GetCaster()->ToPlayer()->AddItem(QUEST_ITEM_SALVAGED_STRONGBOX, 1);
                    if (GameObject* shipwreckDebris = GetCaster()->FindNearestGameObject(GO_SHIPWRECK_DEBRIS, 10.0f))
                    {
                        shipwreckDebris->SetGoState(GO_STATE_ACTIVE);
                        shipwreckDebris->RemoveFromWorld();
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_salvage_wreckage_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_salvage_wreckage_SpellScript();
        }
};

class spell_bottle_of_grog : public SpellScriptLoader
{
    public:
        spell_bottle_of_grog() : SpellScriptLoader("spell_bottle_of_grog") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_GNOME_BAR_PATRON_1    = 40529,
            NPC_ENTRY_GNOME_BAR_PATRON_2    = 40483,
            NPC_ENTRY_GOBLIN_BAR_PATRON_1   = 40530,
            NPC_ENTRY_GOBLIN_BAR_PATRON_2   = 40494
        };

        class spell_bottle_of_grog_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bottle_of_grog_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->ToCreature())
                    {
                        switch (target->ToCreature()->GetEntry())
                        {
                            case NPC_ENTRY_GNOME_BAR_PATRON_1:
                            case NPC_ENTRY_GNOME_BAR_PATRON_2:
                            case NPC_ENTRY_GOBLIN_BAR_PATRON_1:
                            case NPC_ENTRY_GOBLIN_BAR_PATRON_2:
                                return SPELL_CAST_OK;
                            default:
                                return SPELL_FAILED_BAD_TARGETS;
                        }
                    }
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_bottle_of_grog_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bottle_of_grog_SpellScript();
        }
};

class spell_pirates_crowbar : public SpellScriptLoader
{
    public:
        spell_pirates_crowbar() : SpellScriptLoader("spell_pirates_crowbar") { }

        enum Id
        {
            // GameObject
            GO_ENTRY_SUBMERGED_OUTHOUSE     = 202975
        };

        class spell_pirates_crowbar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pirates_crowbar_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GameObject* submergedOuthouse = GetCaster()->FindNearestGameObject(GO_ENTRY_SUBMERGED_OUTHOUSE, 5.0f))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_pirates_crowbar_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pirates_crowbar_SpellScript();
        }
};

class spell_setup_an_oil_drilling_rig : public SpellScriptLoader
{
    public:
        spell_setup_an_oil_drilling_rig() : SpellScriptLoader("spell_setup_an_oil_drilling_rig") { }

        enum Id
        {
            // NPC
            NPC_ENTRY_OIL_POOL          = 25781,
            NPC_ENTRY_OIL_DRILLING_RIG  = 41299
        };

        class spell_setup_an_oil_drilling_rig_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_setup_an_oil_drilling_rig_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* oilPool = GetCaster()->FindNearestCreature(NPC_ENTRY_OIL_POOL, 15.0f, true))
                {
                    Creature* oilRig = GetCaster()->FindNearestCreature(NPC_ENTRY_OIL_DRILLING_RIG, 40.0f, true);
                    if (!oilRig)
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_setup_an_oil_drilling_rig_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_setup_an_oil_drilling_rig_SpellScript();
        }
};

class spell_splithoof_brand : public SpellScriptLoader
{
    public:
        spell_splithoof_brand() : SpellScriptLoader("spell_splithoof_brand") { }

        enum Id
        {
            // NPC
            NPC_ENTRY_THE_ANCIENT_BRAZIER_FIRE_BUNNY    = 41242,
            NPC_ENTRY_AQUARIAN                          = 41236,

            // Spells
            SPELL_BUNNY_FLAMES                          = 70415
        };

        class spell_splithoof_brand_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_splithoof_brand_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Creature* brazierFireBunny = GetCaster()->FindNearestCreature(NPC_ENTRY_THE_ANCIENT_BRAZIER_FIRE_BUNNY, 8.0f, true))
                {
                    brazierFireBunny->CastSpell(brazierFireBunny, SPELL_BUNNY_FLAMES, true);
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        GetCaster()->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_THE_ANCIENT_BRAZIER_FIRE_BUNNY);
                    return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void StartEvent()
            {
                if (Player* caster = GetCaster()->ToPlayer())
                {
                    Creature* Aquarian = caster->FindNearestCreature(NPC_ENTRY_AQUARIAN, 200.0f, true);
                    if (!Aquarian)
                        caster->SummonCreature(NPC_ENTRY_AQUARIAN, -4934.35f, -2288.15f, -72.26f, 0.12f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_splithoof_brand_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_splithoof_brand_SpellScript::StartEvent);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_splithoof_brand_SpellScript();
        }
};

class spell_shuhalo_artifacts : public SpellScriptLoader
{
    public:
        spell_shuhalo_artifacts() : SpellScriptLoader("spell_shuhalo_artifacts") { }

        enum Id
        {
            // NPC
            NPC_ENTRY_THE_RATTLE_OF_BONE        = 45463,
            NPC_ENTRY_THE_WRIT_OF_HISTORY       = 45466,
            NPC_ENTRY_THE_DRUMS_OF_WAR          = 45468,
            NPC_ENTRY_ARIKARA                   = 45446,

            // Spells
            SPELL_ENTRY_RATTLE          = 84949,
            SPELL_ENTRY_WRIT            = 84953,
            SPELL_ENTRY_DRUMS           = 84954,

            // AreaID
            AREA_ID_ARIKARA_NEEDLE      = 5675
        };

        class spell_shuhalo_artifacts_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shuhalo_artifacts_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetAreaId() == AREA_ID_ARIKARA_NEEDLE)
                {
                    Creature* rattle = GetCaster()->FindNearestCreature(NPC_ENTRY_THE_RATTLE_OF_BONE, 100.0f, true);
                    Creature* writ = GetCaster()->FindNearestCreature(NPC_ENTRY_THE_WRIT_OF_HISTORY, 100.0f, true);
                    Creature* drums = GetCaster()->FindNearestCreature(NPC_ENTRY_THE_DRUMS_OF_WAR, 100.0f, true);
                    Creature* arikara = GetCaster()->FindNearestCreature(NPC_ENTRY_ARIKARA, 100.0f, true);
                    if (!rattle && !writ && !drums && !arikara)
                        return SPELL_CAST_OK;
                    else
                        return SPELL_FAILED_NOT_HERE;
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void StartEvent()
            {
                if (Player* caster = GetCaster()->ToPlayer())
                {
                    caster->SummonCreature(NPC_ENTRY_THE_DRUMS_OF_WAR, -5004.77f, -2101.19f, 85.05f, 4.75f, TEMPSUMMON_TIMED_DESPAWN, 21000);
                    caster->SummonCreature(NPC_ENTRY_THE_RATTLE_OF_BONE, -5010.13f, -2109.63f, 84.92f, 0.20f, TEMPSUMMON_TIMED_DESPAWN, 21000);
                    caster->SummonCreature(NPC_ENTRY_THE_WRIT_OF_HISTORY, -5000.36f, -2112.87f, 84.72f, 2.29f, TEMPSUMMON_TIMED_DESPAWN, 21000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_shuhalo_artifacts_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_shuhalo_artifacts_SpellScript::StartEvent);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_shuhalo_artifacts_SpellScript();
        }
};

class spell_pry_armor : public SpellScriptLoader
{
    public:
        spell_pry_armor() : SpellScriptLoader("spell_pry_armor") { }

        enum Id
        {
            SPELL_PAINFUL_STASIS    = 77085,
            SPELL_ARMOR_PLATING     = 77224
        };

        class spell_pry_armor_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pry_armor_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetExplTargetUnit()->HasAura(SPELL_PAINFUL_STASIS) || GetExplTargetUnit()->HasAura(SPELL_ARMOR_PLATING))
                {
                    GetExplTargetUnit()->RemoveAurasDueToSpell(SPELL_ARMOR_PLATING);
                    GetExplTargetUnit()->RemoveAurasDueToSpell(SPELL_PAINFUL_STASIS);
                    return SPELL_CAST_OK;
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_pry_armor_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pry_armor_SpellScript();
        }
};

class spell_signal_rocket : public SpellScriptLoader
{
    public:
        spell_signal_rocket() : SpellScriptLoader("spell_signal_rocket") { }

        enum Id
        {
            NPC_ENTRY_DRUID_OF_THE_TALON    = 41287,
            NPC_ENTRY_SETHRIA               = 41255,
            GUID_DRUID_TALON_LEADER         = 735292
        };

        class spell_signal_rocket_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_signal_rocket_SpellScript);

            void EngageDruids()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 400.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(400.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_DRUID_OF_THE_TALON)
                        {
                            // Exclude if in combat!
                            if ((*itr)->isInCombat())
                                continue;

                            if (Creature* Sethria = caster->FindNearestCreature(NPC_ENTRY_SETHRIA, 400.0f, true))
                            {
                                if (Sethria->GetHealthPct() > 67)
                                    continue;

                                // Respawn if creatures are dead
                                if ((*itr)->ToCreature()->isDead())
                                    (*itr)->ToCreature()->SetHealth((*itr)->GetMaxHealth());

                                if ((*itr)->ToCreature()->GetGUIDLow() == GUID_DRUID_TALON_LEADER)
                                    (*itr)->ToCreature()->AI()->Talk(0);

                                (*itr)->ToCreature()->AI()->AttackStart(Sethria);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_signal_rocket_SpellScript::EngageDruids);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_signal_rocket_SpellScript();
        }
};

class spell_climb_up_tree : public SpellScriptLoader
{
    public:
        spell_climb_up_tree() : SpellScriptLoader("spell_climb_up_tree") { }

        enum Id
        {
            SPELL_SWITCH_SEAT_1         = 63221,
            SPELL_SWITCH_SEAT_2         = 63313,
            SPELL_SWITCH_SEAT_3         = 63314,
            SPELL_SWITCH_SEAT_4         = 63315,
            SPELL_SWITCH_SEAT_5         = 63316,
            SPELL_RIDE_TREE_ATOP        = 46598,
            SPELL_CLIMBING_TREE_EFFECT  = 75092,

            NPC_ENTRY_TREE_TOP          = 40250
        };

        class spell_climb_up_tree_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_climb_up_tree_SpellScript);

            void HandleClimbUp()
            {
                if (Unit* vehicleTree = GetCaster())
                {
                    if (Vehicle* vehicle = vehicleTree->GetVehicleKit())
                    {
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                        {
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger))
                            {
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_1))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_1);
                                    player->CastSpell(vehicleTree, SPELL_SWITCH_SEAT_2, true);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_2))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_2);
                                    player->CastSpell(vehicleTree, SPELL_SWITCH_SEAT_3, true);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_3))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_3);
                                    player->CastSpell(vehicleTree, SPELL_SWITCH_SEAT_4, true);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_4))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_4);
                                    if (Creature* treeTop = player->FindNearestCreature(NPC_ENTRY_TREE_TOP, 200.0f, true))
                                        player->CastSpell(treeTop, SPELL_RIDE_TREE_ATOP, true);

                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_climb_up_tree_SpellScript::HandleClimbUp);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_climb_up_tree_SpellScript();
        }
};

class spell_climb_down_tree : public SpellScriptLoader
{
    public:
        spell_climb_down_tree() : SpellScriptLoader("spell_climb_down_tree") { }

        enum Id
        {
            SPELL_SWITCH_SEAT_1         = 63221,
            SPELL_SWITCH_SEAT_2         = 63313,
            SPELL_SWITCH_SEAT_3         = 63314,
            SPELL_SWITCH_SEAT_4         = 63315,
            SPELL_SWITCH_SEAT_5         = 63316,
            SPELL_RIDE_TREE_ATOP        = 46598,
            SPELL_CLIMBING_TREE_EFFECT  = 75092,
            NPC_ENTRY_TREE_BOT          = 40190
        };

        class spell_climb_down_tree_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_climb_down_tree_SpellScript);

            void HandleClimbDown()
            {
                if (Unit* vehicleTree = GetCaster())
                {
                    if (Vehicle* vehicle = vehicleTree->GetVehicleKit())
                    {
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                        {
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger))
                            {
                                if (vehicleTree->HasAura(SPELL_RIDE_TREE_ATOP))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_RIDE_TREE_ATOP);
                                    if (Creature* treeBot = player->FindNearestCreature(NPC_ENTRY_TREE_BOT, 200.0f, true))
                                        player->CastSpell(treeBot, SPELL_SWITCH_SEAT_4, true);

                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_1))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_1);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_2))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_2);
                                    player->CastSpell(vehicleTree, SPELL_SWITCH_SEAT_1, true);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_3))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_3);
                                    player->CastSpell(vehicleTree, SPELL_SWITCH_SEAT_2, true);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                                if (vehicleTree->HasAura(SPELL_SWITCH_SEAT_4))
                                {
                                    vehicleTree->RemoveAurasDueToSpell(SPELL_SWITCH_SEAT_4);
                                    player->CastSpell(vehicleTree, SPELL_SWITCH_SEAT_3, true);
                                    player->CastSpell(player, SPELL_CLIMBING_TREE_EFFECT, true);
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_climb_down_tree_SpellScript::HandleClimbDown);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_climb_down_tree_SpellScript();
        }
};

class spell_chuck_a_bear : public SpellScriptLoader
{
    public:
        spell_chuck_a_bear() : SpellScriptLoader("spell_chuck_a_bear") { }

        enum Id
        {
            ITEM_ENTRY_HYJAL_BEAR_CUB   = 54439,
            QUEST_CREDIT_BEAR           = 40284,
            NPC_ENTRY_SOFT_TRIGGER      = 40242,
            SPELL_BEAR_BOUNCE           = 75119
        };

        class spell_chuck_a_bear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_chuck_a_bear_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* vehicleTree = GetCaster())
                {
                    if (Vehicle* vehicle = vehicleTree->GetVehicleKit())
                    {
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                        {
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger))
                            {
                                if (player->HasItemCount(ITEM_ENTRY_HYJAL_BEAR_CUB, 1, false))
                                    return SPELL_CAST_OK;
                                else
                                    return SPELL_FAILED_REAGENTS;
                            }
                        }
                    }
                }
                return SPELL_FAILED_REAGENTS;
            }

            void RemoveBear()
            {
                if (Unit* vehicleTree = GetCaster())
                {
                    if (Vehicle* vehicle = vehicleTree->GetVehicleKit())
                    {
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                        {
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger))
                            {
                                // Just to be sure check if player still have item
                                if (player->HasItemCount(ITEM_ENTRY_HYJAL_BEAR_CUB, 1, false))
                                {
                                    player->DestroyItemCount(ITEM_ENTRY_HYJAL_BEAR_CUB, 1, true);
                                    player->KilledMonsterCredit(QUEST_CREDIT_BEAR);
                                    if (Creature* softTrigger = player->FindNearestCreature(NPC_ENTRY_SOFT_TRIGGER, 300.0f, true))
                                        softTrigger->CastWithDelay(1000, softTrigger, SPELL_BEAR_BOUNCE, true);
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_chuck_a_bear_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_chuck_a_bear_SpellScript::RemoveBear);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_chuck_a_bear_SpellScript();
        }
};

class spell_flameward_activated : public SpellScriptLoader
{
    public:
        spell_flameward_activated() : SpellScriptLoader("spell_flameward_activated") { }

        enum Id
        {
            SPELL_FLAMEWARD_DEFENDED    = 75471,
            QUEST_CREDIT_FLAMEWARD      = 40462
        };

        class spell_flameward_activated_auraScript : public AuraScript
        {
            PrepareAuraScript(spell_flameward_activated_auraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    target->CastSpell(target, SPELL_FLAMEWARD_DEFENDED, true);
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        target->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FLAMEWARD);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_flameward_activated_auraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_flameward_activated_auraScript();
        }
};

class spell_tortolla_shell : public SpellScriptLoader
{
    public:
        spell_tortolla_shell() : SpellScriptLoader("spell_tortolla_shell") { }

        class spell_tortolla_shell_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tortolla_shell_SpellScript);

            enum Id
            {
                NPC_ENTRY_CHILD_OF_TORTOLLA = 41581,
                SPELL_TORTOLLA_SHELL        = 77770
            };

            void HandleApplyOnTurtle()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 80.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(80.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_CHILD_OF_TORTOLLA:
                                    {
                                        (*itr)->AddAura(SPELL_TORTOLLA_SHELL, (*itr));
                                        break;
                                    }
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
                AfterCast += SpellCastFn(spell_tortolla_shell_SpellScript::HandleApplyOnTurtle);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_tortolla_shell_SpellScript();
        }
};

class spell_hyjal_extinguish_flames : public SpellScriptLoader
{
    public:
        spell_hyjal_extinguish_flames() : SpellScriptLoader("spell_hyjal_extinguish_flames") { }

        enum Id
        {
            SPELL_EXTINGUISH_FLAMES         = 74359,
            SPELL_ENGULFED_IN_FLAMES        = 73876,
            NPC_ENTRY_IMMOLATED_SUPPLICANT  = 39453,
            CREDIT_ENTRY_IMMOLATED_SUPP     = 39806
        };

        class spell_hyjal_extinguish_flames_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hyjal_extinguish_flames_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_EXTINGUISH_FLAMES))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Unit* target = GetHitUnit())
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                        {
                            if (target->GetEntry() == NPC_ENTRY_IMMOLATED_SUPPLICANT && target->HasAura(SPELL_ENGULFED_IN_FLAMES))
                            {
                                caster->ToPlayer()->KilledMonsterCredit(CREDIT_ENTRY_IMMOLATED_SUPP);
                                target->AddAura(SPELL_EXTINGUISH_FLAMES, target);
                                target->RemoveAurasDueToSpell(SPELL_ENGULFED_IN_FLAMES);
                                target->ToCreature()->AI()->TalkWithDelay(1500, 0);
                                target->ToCreature()->DespawnOrUnsummon(10000);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_hyjal_extinguish_flames_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hyjal_extinguish_flames_SpellScript();
        }
};

class spell_answer_yes : public SpellScriptLoader
{
    public:
        spell_answer_yes() : SpellScriptLoader("spell_answer_yes") { }

        class spell_answer_yes_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_answer_yes_SpellScript);

            enum Id
            {
                NPC_ENTRY_ORB_OF_ASCENSION = 39601
            };

            void HandleAnswerOrb()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(30.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster) && (*itr)->ToCreature())
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_ORB_OF_ASCENSION:
                                    {
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                        break;
                                    }
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
                AfterCast += SpellCastFn(spell_answer_yes_SpellScript::HandleAnswerOrb);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_answer_yes_SpellScript();
        }
};

class spell_answer_no : public SpellScriptLoader
{
    public:
        spell_answer_no() : SpellScriptLoader("spell_answer_no") { }

        class spell_answer_no_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_answer_no_SpellScript);

            enum Id
            {
                NPC_ENTRY_ORB_OF_ASCENSION = 39601
            };

            void HandleAnswerOrb()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 80.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(80.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster) && (*itr)->ToCreature())
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_ORB_OF_ASCENSION:
                                    {
                                        (*itr)->ToCreature()->AI()->DoAction(2);
                                        break;
                                    }
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
                AfterCast += SpellCastFn(spell_answer_no_SpellScript::HandleAnswerOrb);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_answer_no_SpellScript();
        }
};

class spell_dismiss_orb_of_ascension : public SpellScriptLoader
{
    public:
        spell_dismiss_orb_of_ascension() : SpellScriptLoader("spell_dismiss_orb_of_ascension") { }

        class spell_dismiss_orb_of_ascension_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dismiss_orb_of_ascension_SpellScript);

            enum Id
            {
                NPC_ENTRY_ORB_OF_ASCENSION = 39601,
                SPELL_MENTAL_TRAINING      = 73984
            };

            void HandleDismissOrb()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 80.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(80.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster) && (*itr)->ToCreature())
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_ORB_OF_ASCENSION:
                                    {
                                        (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    caster->RemoveAurasDueToSpell(SPELL_MENTAL_TRAINING);
                    caster->SetControlled(false, UNIT_STATE_ROOT);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dismiss_orb_of_ascension_SpellScript::HandleDismissOrb);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dismiss_orb_of_ascension_SpellScript();
        }
};

class spell_podium_inspire : public SpellScriptLoader
{
    public:
        spell_podium_inspire() : SpellScriptLoader("spell_podium_inspire") { }

        class spell_podium_inspire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_podium_inspire_SpellScript);

            enum Id
            {
                QUEST_CREDIT_GRADUATION_SPEECH = 40618
            };

            void HandleInspire()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        switch (caster->m_graduationSpeechInspire)
                        {
                            case 1:
                                caster->MonsterSay("There will be no surrender! There will be no escape! There will be no quarter!", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 2:
                                caster->MonsterSay("Look at how far we have come! Yesterday we lived in the shadows of civilization... hunted like rats! But today! HYJAL BURNS!!!", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 3:
                                caster->MonsterSay("It is truly a great time for the Twilight Hammer. The greatest of times. First, Lord Deathwing arrival. And now... now great Ragnaros has returned!", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 4:
                                caster->MonsterSay("Not all of you will ascend to glory. Look to your left. Look to your right. THEY will perish in the end times. But YOU will become immortal.", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 5:
                                caster->MonsterSay("It is in this moment, friends, that we should ask ourselves. What would the Old Gods want us to do?", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 6:
                                caster->MonsterSay("One by one... our enemies will perish! One by one... they will be destroyed!", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 7:
                                caster->MonsterSay("I look upon the symbol that unites us. This hammer. It is the hammer that builds and creates. But it is also the hammer that bludgeons and destroys!", 0);
                                caster->m_graduationSpeechInspire++;
                                break;
                            case 8:
                                caster->MonsterSay("Eons ago, the 'Titans' came here and cast down our Masters. But this is NOT their world, and it never was! Judgment comes at last!", 0);
                                caster->m_graduationSpeechInspire = 1;
                                break;
                            default:
                                break;
                        }

                        // Inspire normal waiting dialogs
                        if (roll_chance_f(15))
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 1, caster->GetGUID());
                                }
                            }
                        }

                        if (roll_chance_f(60)) // Correct
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 4, caster->GetGUID());
                                }
                            }
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GRADUATION_SPEECH);
                            return;
                        }

                        if (roll_chance_f(40)) // Wrong
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 5, caster->GetGUID());
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_podium_inspire_SpellScript::HandleInspire);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_podium_inspire_SpellScript();
        }
};

class spell_podium_incite : public SpellScriptLoader
{
    public:
        spell_podium_incite() : SpellScriptLoader("spell_podium_incite") { }

        class spell_podium_incite_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_podium_incite_SpellScript);

            enum Id
            {
                QUEST_CREDIT_GRADUATION_SPEECH = 40618
            };

            void HandleIncite()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        switch (caster->m_graduationSpeechIncite)
                        {
                            case 1:
                                caster->MonsterSay("But always remember that our movement cannot stay pure if some traitors among you still draw breath. You know who I mean.", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 2:
                                caster->MonsterSay("But a bitter stench blows into our ranks. The answer is to purge! PURGE! Purge until the Twilight Hammer is pure again!", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 3:
                                caster->MonsterSay("We walk the edge of a precipice. Some of us must be pushed over for the rest of us to continue.", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 4:
                                caster->MonsterSay("And to those who call for harmony among our ranks... to them I ask: Does not ALL strife please our masters? Does not ALL bloodlet feed their thirst?", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 5:
                                caster->MonsterSay("Remember the words of Cthun! Remember them well! Your friends will betray you! And betray us they have!", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 6:
                                caster->MonsterSay("And some will preach unity! But does unity prevent a chain from breaking at its weakest link?", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 7:
                                caster->MonsterSay("And these incidents... these divisive acts of hate against other members of our organization. They were cowardly and ugly, yes. But maybe... they were NECESSARY!", 0);
                                caster->m_graduationSpeechIncite++;
                                break;
                            case 8:
                                caster->MonsterSay("And yes, Cho gall might have founded the Twilight  Hammer, but who made it what it is today? Who preached the truth and faced persecution in the orc and human cities?", 0);
                                caster->m_graduationSpeechIncite = 1;
                                break;
                            default:
                                break;
                        }

                        // Incite normal waiting dialogs
                        if (roll_chance_f(15))
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 2, caster->GetGUID());
                                }
                            }
                        }

                        if (roll_chance_f(60)) // Correct
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 4, caster->GetGUID());
                                }
                            }
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GRADUATION_SPEECH);
                            return;
                        }

                        if (roll_chance_f(40)) // Wrong
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 5, caster->GetGUID());
                                }
                            }
                            return;
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_podium_incite_SpellScript::HandleIncite);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_podium_incite_SpellScript();
        }
};

class spell_podium_pander : public SpellScriptLoader
{
    public:
        spell_podium_pander() : SpellScriptLoader("spell_podium_pander") { }

        class spell_podium_pander_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_podium_pander_SpellScript);

            enum Id
            {
                QUEST_CREDIT_GRADUATION_SPEECH = 40618
            };

            void HandlePander()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        switch (caster->m_graduationSpeechPander)
                        {
                            case 1:
                                caster->MonsterSay("Do not think it is luck that brought you here. Luck had nothing to do with it. Our MASTERS WILL brought us here!", 0);
                                caster->m_graduationSpeechPander++;
                                break;
                            case 2:
                                caster->MonsterSay("And there is no hope! There is no hope but in the loss of all hope. That is right, brothers and sisters. Only hopelessness can grant true hope!", 0);
                                caster->m_graduationSpeechPander++;
                                break;
                            case 3:
                                caster->MonsterSay("The blood we shed speaks to us. It says Thank you.", 0);
                                caster->m_graduationSpeechPander++;
                                break;
                            case 4:
                                caster->MonsterSay("Place a plam across your heart and reach forward with your other hand to touch the infinite. Does it feel soft? NO! It feels... immense.", 0);
                                caster->m_graduationSpeechPander++;
                                break;
                            case 5:
                                caster->MonsterSay("Yes, my fellow initiates. The friend of my enemy s enemy... well he is also the enemy of my friend. And yes... he shall perish too!", 0);
                                caster->m_graduationSpeechPander++;
                                break;
                            case 6:
                                caster->MonsterSay("And sometimes you have to ask yourself: Is it worth it? And the answer is plain: Pain is not the cost, but the reward!", 0);
                                caster->m_graduationSpeechPander++;
                                break;
                            case 7:
                                caster->MonsterSay("F tagh nah hat! I mmathan! Sha lub nahab! Sha lub nahab, my friends!", 0);
                                caster->m_graduationSpeechPander = 1;
                                break;
                            default:
                                break;
                        }
                        // Incite normal waiting dialogs
                        if (roll_chance_f(60))
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 3, caster->GetGUID());
                                }
                            }
                        }
                        if (roll_chance_f(50)) // Correct
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(1500,3000), 4, caster->GetGUID());
                                }
                            }
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GRADUATION_SPEECH);
                            return;
                        }
                        if (roll_chance_f(40)) // Wrong
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 30.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(30.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->GetEntry() == 40185)
                                {
                                    if (roll_chance_f(5))
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,3000), 5, caster->GetGUID());
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_podium_pander_SpellScript::HandlePander);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_podium_pander_SpellScript();
        }
};

class spell_horn_of_cenarius : public SpellScriptLoader
{
    public:
        spell_horn_of_cenarius() : SpellScriptLoader("spell_horn_of_cenarius") { }

        class spell_horn_of_cenarius_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_horn_of_cenarius_SpellScript);

            enum Id
            {
                NPC_ENTRY_NORDRASSIL_DRUID  = 40956
            };

            void HandleSummonHelpers()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()+urand(5,15), caster->GetPositionY()+urand(5,15), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()-urand(5,30), caster->GetPositionY()-urand(5,30), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()+urand(5,15), caster->GetPositionY()+urand(5,15), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()-urand(5,30), caster->GetPositionY()-urand(5,30), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()+urand(5,15), caster->GetPositionY()+urand(5,15), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()-urand(5,30), caster->GetPositionY()-urand(5,30), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()+urand(5,15), caster->GetPositionY()+urand(5,15), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()-urand(5,30), caster->GetPositionY()-urand(5,30), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()+urand(5,15), caster->GetPositionY()+urand(5,15), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_NORDRASSIL_DRUID, caster->GetPositionX()-urand(5,30), caster->GetPositionY()-urand(5,30), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_horn_of_cenarius_SpellScript::HandleSummonHelpers);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_horn_of_cenarius_SpellScript();
        }
};

class spell_drums_of_the_turtle_god : public SpellScriptLoader
{
    public:
        spell_drums_of_the_turtle_god() : SpellScriptLoader("spell_drums_of_the_turtle_god") { }

        class spell_drums_of_the_turtle_god_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_drums_of_the_turtle_god_SpellScript);

            enum Id
            {
                NPC_ENTRY_TORTOLLA      = 40999,
                NPC_ENTRY_KING_MOLTRON  = 40998
            };

            void HandleSummonTortolla()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        Creature* tortolla = caster->FindNearestCreature(NPC_ENTRY_TORTOLLA, 200.0f, true);
                        Creature* moltron = caster->FindNearestCreature(NPC_ENTRY_KING_MOLTRON, 50.0f, true);
                        if (!tortolla && moltron)
                            caster->SummonCreature(NPC_ENTRY_TORTOLLA, 3900.27f, -2745.56f, 1000.10f, 3.37f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_drums_of_the_turtle_god_SpellScript::HandleSummonTortolla);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_drums_of_the_turtle_god_SpellScript();
        }
};

class spell_place_drake_skull : public SpellScriptLoader
{
    public:
        spell_place_drake_skull() : SpellScriptLoader("spell_place_drake_skull") { }

        enum Id
        {
            NPC_ENTRY_ARONUS        = 40816,
            NPC_ENTRY_DESPERIONA    = 40974,
            NPC_ENTRY_AVIANA        = 40982,
            GO_ENTRY_SKULL          = 203063,

            QUEST_DEATH_TO_THE_BROODMOTHER = 25553
        };

        class spell_place_drake_skull_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_place_drake_skull_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        Creature* desperiona = caster->FindNearestCreature(NPC_ENTRY_DESPERIONA, 100.0f, true);
                        Creature* aviana = caster->FindNearestCreature(NPC_ENTRY_AVIANA, 100.0f, true);
                        Creature* aronus = caster->FindNearestCreature(NPC_ENTRY_ARONUS, 100.0f, true);
                        GameObject* skullTrigger = caster->FindNearestGameObject(GO_ENTRY_SKULL, 40.0f);
                        if (!skullTrigger)
                            return SPELL_FAILED_NOT_HERE;

                        if (caster->ToPlayer()->GetQuestStatus(QUEST_DEATH_TO_THE_BROODMOTHER) != QUEST_STATUS_INCOMPLETE)
                            return SPELL_FAILED_DONT_REPORT;

                        if (desperiona || aviana || aronus)
                            return SPELL_FAILED_NOT_READY;

                        if (caster->ToPlayer()->HasSpellCooldown(76559))
                            return SPELL_FAILED_NOT_READY;

                        caster->SummonCreature(NPC_ENTRY_ARONUS, 3750.23f, -3266.52f, 991.91f, 0.98f, TEMPSUMMON_TIMED_DESPAWN, 200000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->ToPlayer()->AddSpellCooldown(76559, 0, time(NULL) + 180000);
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_DONT_REPORT;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_place_drake_skull_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_place_drake_skull_SpellScript();
        }
};

class spell_summon_spirit_of_logosh : public SpellScriptLoader
{
    public:
        spell_summon_spirit_of_logosh() : SpellScriptLoader("spell_summon_spirit_of_logosh") { }

        class spell_summon_spirit_of_logosh_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_spirit_of_logosh_SpellScript);

            enum Id
            {
                SPELL_SUMMON_SPIRIT_OF_GOLDRINN     = 74474
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->getRaceMask() & RACEMASK_HORDE)
                        return SPELL_CAST_OK;
                    else
                    {
                        caster->CastSpell(caster, SPELL_SUMMON_SPIRIT_OF_GOLDRINN, true);
                        return SPELL_FAILED_DONT_REPORT;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_spirit_of_logosh_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_spirit_of_logosh_SpellScript();
        }
};

class spell_goldmine_fire_totem : public SpellScriptLoader
{
    public:
        spell_goldmine_fire_totem() : SpellScriptLoader("spell_goldmine_fire_totem") { }

        class spell_goldmine_fire_totem_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_goldmine_fire_totem_SpellScript);

            enum Id
            {
                NPC_ENTRY_LAVA_POOL_TRIGGER     = 50423
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* lavaPool = caster->FindNearestCreature(NPC_ENTRY_LAVA_POOL_TRIGGER, 6.0f))
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_goldmine_fire_totem_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_goldmine_fire_totem_SpellScript();
        }
};

class spell_stonefather_boon_banner : public SpellScriptLoader
{
    public:
        spell_stonefather_boon_banner() : SpellScriptLoader("spell_stonefather_boon_banner") { }

        class spell_stonefather_boon_banner_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_stonefather_boon_banner_SpellScript);

            enum Id
            {
                NPC_ENTRY_STONEHEART_DEFENDER      = 43138,
                NPC_ENTRY_STONEHEART_GEOMANCER     = 43170,
                NPC_ENTRY_STONEHEART_BANNER        = 43163,

                SPELL_STONEFATHER_BOON             = 80668,
                SPELL_SUMMON_BANNER                = 80658
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    Creature* banner = caster->FindNearestCreature(NPC_ENTRY_STONEHEART_BANNER, 8.0f);
                    if (banner)
                        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                    if (Creature* defender = caster->FindNearestCreature(NPC_ENTRY_STONEHEART_DEFENDER, 8.0f))
                    {
                        if (defender->HasAura(SPELL_STONEFATHER_BOON))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        return SPELL_CAST_OK;
                    }
                    if (Creature* geomancer = caster->FindNearestCreature(NPC_ENTRY_STONEHEART_GEOMANCER, 8.0f))
                    {
                        if (geomancer->HasAura(SPELL_STONEFATHER_BOON))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_NOT_HERE;
            }

            void HandleSummonBanner()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->CastSpell(caster, SPELL_SUMMON_BANNER, true);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_stonefather_boon_banner_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_stonefather_boon_banner_SpellScript::HandleSummonBanner);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_stonefather_boon_banner_SpellScript();
        }
};

class spell_rockslide_reagent : public SpellScriptLoader
{
    public:
        spell_rockslide_reagent() : SpellScriptLoader("spell_rockslide_reagent") { }

        class spell_rockslide_reagent_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rockslide_reagent_SpellScript);

            enum Id
            {
                // Entries
                NPC_ENTRY_STONEHEART_GEOMANCER      = 43170,
                GO_ENTRY_SEALING_THE_WAY_ROCKS      = 204343,

                // Credits
                QUEST_CREDIT_SHRINE                 = 43167,
                QUEST_CREDIT_BARRACKS               = 43166,
                QUEST_CREDIT_INN                    = 43165,
                QUEST_CREDIT_ARMORY                 = 43164,

                // GameObject GUIDs
                GO_GUID_SHRINE     =    719145,
                GO_GUID_BARRACKS   =    719144,
                GO_GUID_INN        =    719143,
                GO_GUID_ARMORY     =    719142
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* geomancer = caster->FindNearestCreature(NPC_ENTRY_STONEHEART_GEOMANCER, 10.0f, true))
                    {
                        if (geomancer->isInCombat())
                            return SPELL_FAILED_TARGET_IN_COMBAT;
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleEnableRocks()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* geomancer = caster->FindNearestCreature(NPC_ENTRY_STONEHEART_GEOMANCER, 10.0f, true))
                    {
                        if (GameObject* rocks = caster->FindNearestGameObject(GO_ENTRY_SEALING_THE_WAY_ROCKS, 20.0f))
                        {
                            rocks->SetGoState(GO_STATE_READY);
                            rocks->SetRespawnTime(60000);
                            geomancer->SetOrientation(rocks->GetOrientation());
                            geomancer->HandleEmoteCommand(EMOTE_ONESHOT_SPELL_CAST_OMNI);
                            if (caster->GetTypeId() != TYPEID_PLAYER)
                                return;

                            switch (rocks->GetGUIDLow())
                            {
                                case GO_GUID_SHRINE:
                                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_SHRINE);
                                    break;
                                case GO_GUID_BARRACKS:
                                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_BARRACKS);
                                    break;
                                case GO_GUID_ARMORY:
                                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ARMORY);
                                    break;
                                case GO_GUID_INN:
                                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_INN);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_rockslide_reagent_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_rockslide_reagent_SpellScript::HandleEnableRocks);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rockslide_reagent_SpellScript();
        }
};

class spell_twilight_firelance_equipped : public SpellScriptLoader
{
    public:
        spell_twilight_firelance_equipped() : SpellScriptLoader("spell_twilight_firelance_equipped") { }

        class spell_twilight_firelance_equipped_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_twilight_firelance_equipped_SpellScript);

            enum Id
            {
                QUEST_ENTRY_FLIGHT_IN_THE_FIRELANDS = 25523
            };

            void HandleWarning()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_ENTRY_FLIGHT_IN_THE_FIRELANDS) == QUEST_STATUS_INCOMPLETE)
                            caster->MonsterWhisper("Mount One of Aviana's Guardians", caster->GetGUID(), true);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_twilight_firelance_equipped_SpellScript::HandleWarning);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_twilight_firelance_equipped_SpellScript();
        }
};

class spell_trogg_crate : public SpellScriptLoader
{
    public:
        spell_trogg_crate() : SpellScriptLoader("spell_trogg_crate") { }

        enum Id
        {
            SPELL_ENTRY_SUBMERGED   = 83699
        };

        class spell_trogg_crate_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_trogg_crate_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    target->SetStandFlags(UNIT_STAND_FLAGS_CREEP);
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        target->SetByteFlag(PLAYER_FIELD_BYTES2, 3, PLAYER_FIELD_BYTE2_STEALTH);
                    target->SetVisible(false);
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    target->RemoveStandFlags(UNIT_STAND_FLAGS_CREEP);
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        target->RemoveByteFlag(PLAYER_FIELD_BYTES2, 3, PLAYER_FIELD_BYTE2_STEALTH);
                    target->SetVisible(true);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_trogg_crate_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_trogg_crate_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_trogg_crate_AuraScript();
        }
};

class spell_carve_meat : public SpellScriptLoader
{
    public:
        spell_carve_meat() : SpellScriptLoader("spell_carve_meat") { }

        class spell_carve_meat_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_carve_meat_SpellScript);

            enum Id
            {
                NPC_ENTRY_JADECREST_BASILISK    = 43981
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (Creature* jadecrestBasilisk = caster->FindNearestCreature(NPC_ENTRY_JADECREST_BASILISK, 10.0f, false))
                        {
                            jadecrestBasilisk->DespawnOrUnsummon(3000);
                            return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_carve_meat_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_carve_meat_SpellScript();
        }
};

class spell_place_basilisk_meat : public SpellScriptLoader
{
    public:
        spell_place_basilisk_meat() : SpellScriptLoader("spell_place_basilisk_meat") { }

        class spell_place_basilisk_meat_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_place_basilisk_meat_SpellScript);

            enum Id
            {
                NPC_ENTRY_STONESCALE_MATRIARCH  = 44148
            };

            void HandleSummonMatriarch()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        Creature* matriarch = caster->FindNearestCreature(NPC_ENTRY_STONESCALE_MATRIARCH, 500.0f, true);
                        if (matriarch)
                            return;
                        else
                            caster->SummonCreature(NPC_ENTRY_STONESCALE_MATRIARCH, -115.45f, 542.88f, 246.03f, 4.92f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_place_basilisk_meat_SpellScript::HandleSummonMatriarch);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_place_basilisk_meat_SpellScript();
        }
};

class spell_place_earthen_ring_banner : public SpellScriptLoader
{
    public:
        spell_place_earthen_ring_banner() : SpellScriptLoader("spell_place_earthen_ring_banner") { }

        class spell_place_earthen_ring_banner_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_place_earthen_ring_banner_SpellScript);

            enum Id
            {
                NPC_ENTRY_ABYSSION  = 44289
            };

            void HandleSummonMatriarch()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        Creature* abyssion = caster->FindNearestCreature(NPC_ENTRY_ABYSSION, 500.0f, true);
                        if (abyssion)
                            return;
                        else
                            caster->SummonCreature(NPC_ENTRY_ABYSSION, 128.26f, -405.93f, 222.96f, 5.17f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_place_earthen_ring_banner_SpellScript::HandleSummonMatriarch);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_place_earthen_ring_banner_SpellScript();
        }
};

class spell_elementium_grapple_line : public SpellScriptLoader
{
    public:
        spell_elementium_grapple_line() : SpellScriptLoader("spell_elementium_grapple_line") { }

        enum Id
        {
            SPELL_ENTRY_TRIPPED         = 79764,
            SPELL_ENTRY_ROPE_BEAM       = 79798,
            SPELL_QUEST_CREDIT          = 45083,
            SPELL_SUMMON_SENTINEL       = 79775,

            NPC_SERVANT_OF_THERAZANE_1  = 42479,
            NPC_SERVANT_OF_THERAZANE_2  = 44121,
            NPC_SERVANT_OF_THERAZANE_3  = 42781
        };

        class spell_elementium_grapple_line_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_elementium_grapple_line_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (target->ToCreature())
                        {
                            switch (target->GetEntry())
                            {
                                case NPC_SERVANT_OF_THERAZANE_1:
                                case NPC_SERVANT_OF_THERAZANE_2:
                                case NPC_SERVANT_OF_THERAZANE_3:
                                {
                                    caster->CastSpell(target, SPELL_ENTRY_ROPE_BEAM, true);
                                    target->SetControlled(true, UNIT_STATE_ROOT);
                                    target->ToCreature()->AI()->Talk(0, caster->GetGUID());
                                    break;
                                }
                                default:
                                    break;
                            }
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
                        switch (target->GetEntry())
                        {
                            case NPC_SERVANT_OF_THERAZANE_1:
                            case NPC_SERVANT_OF_THERAZANE_2:
                            case NPC_SERVANT_OF_THERAZANE_3:
                            {
                                target->RemoveAurasDueToSpell(SPELL_ENTRY_ROPE_BEAM);
                                target->CastSpell(target, SPELL_ENTRY_TRIPPED, true);
                                target->CastWithDelay(2500, target, SPELL_SUMMON_SENTINEL, true);
                                target->SetControlled(false, UNIT_STATE_ROOT);
                                target->ToCreature()->DespawnOrUnsummon(45000);

                                if (Unit* caster = GetCaster())
                                {
                                    if (caster->GetTypeId() == TYPEID_PLAYER)
                                        caster->ToPlayer()->KilledMonsterCredit(SPELL_QUEST_CREDIT);
                                }
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
                OnEffectApply += AuraEffectApplyFn(spell_elementium_grapple_line_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_elementium_grapple_line_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_elementium_grapple_line_AuraScript();
        }
};

class spell_pebble_summon_aura : public SpellScriptLoader
{
    public:
        spell_pebble_summon_aura() : SpellScriptLoader("spell_pebble_summon_aura") { }

        enum Id
        {
            SPELL_SUMMON_PEBBLE     = 80665
        };

        class spell_pebble_summon_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pebble_summon_aura_AuraScript);

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (Unit* target = GetTarget())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(target, target, 500.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(target, targets, u_check);
                    target->VisitNearbyObject(500.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && (*itr)->ToTempSummon()->GetCharmerOrOwner() == target)
                        {
                            switch ((*itr)->ToTempSummon()->GetEntry())
                            {
                                case 43116: // Pebble
                                {
                                    return;
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                    }
                    if (!target->IsFlying() && !target->isMoving())
                        target->CastSpell(target, SPELL_SUMMON_PEBBLE, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_pebble_summon_aura_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pebble_summon_aura_AuraScript();
        }
};

class spell_petrifying_gaze : public SpellScriptLoader
{
    public:
        spell_petrifying_gaze() : SpellScriptLoader("spell_petrifying_gaze") { }

        class spell_petrifying_gaze_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_petrifying_gaze_SpellScript);

            enum Id
            {
                GO_ENTRY_COLLISION  = 205364
            };

            bool Load()
            {
                prevented = false;
                return true;
            }

            void PreventHitByLoS()
            {
                if (Unit* target = GetHitUnit())
                {
                    Unit* caster = GetCaster();
                    //Temporary Line of Sight Check
                    std::list<GameObject*> blockList;
                    caster->GetGameObjectListWithEntryInGrid(blockList, GO_ENTRY_COLLISION, 100.0f);
                    if (!blockList.empty())
                    {
                        for (std::list<GameObject*>::const_iterator itr = blockList.begin(); itr != blockList.end(); ++itr)
                        {
                            if (!(*itr)->IsInvisibleDueToDespawn())
                            {
                                if ((*itr)->IsInBetween(caster, target, 4.0f))
                                {
                                    prevented = true;
                                    target->ApplySpellImmune(GetSpellInfo()->Id, IMMUNITY_ID, GetSpellInfo()->Id, true);
                                    PreventHitDefaultEffect(EFFECT_0);
                                    PreventHitDefaultEffect(EFFECT_1);
                                    PreventHitDefaultEffect(EFFECT_2);
                                    PreventHitDamage();
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            void RestoreImmunity()
            {
                if (Unit* target = GetHitUnit())
                {
                    target->ApplySpellImmune(GetSpellInfo()->Id, IMMUNITY_ID, GetSpellInfo()->Id, false);
                    if (prevented)
                        PreventHitAura();
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_petrifying_gaze_SpellScript::PreventHitByLoS);
                AfterHit += SpellHitFn(spell_petrifying_gaze_SpellScript::RestoreImmunity);
            }

            bool prevented;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_petrifying_gaze_SpellScript();
        }
};

class spell_red_mist_aura : public SpellScriptLoader
{
    public:
        spell_red_mist_aura() : SpellScriptLoader("spell_red_mist_aura") { }

        class spell_red_mist_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_red_mist_aura_AuraScript);

            enum Id
            {
                QUEST_ENTRY_A_HEAD_FULL_OF_WIND         = 26581,
                QUEST_CREDIT_A_HEAD_FULL_OF_WIND        = 43370
            };

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                            return;

                        if (target->ToPlayer()->GetQuestStatus(QUEST_ENTRY_A_HEAD_FULL_OF_WIND) == QUEST_STATUS_INCOMPLETE)
                            target->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_A_HEAD_FULL_OF_WIND);
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_red_mist_aura_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SCALE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_red_mist_aura_AuraScript();
        }
};

class spell_strike_resonating_crystal : public SpellScriptLoader
{
    public:
        spell_strike_resonating_crystal() : SpellScriptLoader("spell_strike_resonating_crystal") { }

        class spell_strike_resonating_crystal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_strike_resonating_crystal_SpellScript);

            enum Id
            {
                NPC_ENTRY_AEOSERA   = 43641,
                NPC_ENTRY_TERRATH   = 42466
            };

            void HandleSummonAeosera()
            {
                if (Unit* caster = GetCaster())
                {
                    Creature* aeosera = caster->FindNearestCreature(NPC_ENTRY_AEOSERA, 300.0f, true);
                    if (!aeosera)
                    {
                        caster->SummonCreature(NPC_ENTRY_AEOSERA, 1863.94f, 1450.85f, 312.94f, 5.79f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                        caster->SummonCreature(NPC_ENTRY_TERRATH, 1962.91f, 1447.49f, 188.32f, 5.01f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_strike_resonating_crystal_SpellScript::HandleSummonAeosera);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_strike_resonating_crystal_SpellScript();
        }
};

class spell_searing_breath : public SpellScriptLoader
{
    public:
        spell_searing_breath() : SpellScriptLoader("spell_searing_breath") { }

        enum Id
        {
            NPC_ENTRY_BOULDER_PLATFORM  = 45191
        };

        class spell_searing_breath_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_searing_breath_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (target->ToCreature() && target->ToCreature()->GetEntry() == NPC_ENTRY_BOULDER_PLATFORM)
                            target->ToCreature()->AI()->DoAction(1);
                    }
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (target->ToCreature() && target->ToCreature()->GetEntry() == NPC_ENTRY_BOULDER_PLATFORM)
                        target->ToCreature()->AI()->DoAction(2);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_searing_breath_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_searing_breath_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_searing_breath_AuraScript();
        }
};

class spell_trapcap_achievement : public SpellScriptLoader
{
    public:
        spell_trapcap_achievement() : SpellScriptLoader("spell_trapcap_achievement") { }

        class spell_trapcap_achievement_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_trapcap_achievement_SpellScript);

            enum Id
            {
                SPELL_ENTRY_POOLSTOOL       = 83805,
                SPELL_ENTRY_SHUFFLETRUFFLE  = 83803,
                SPELL_ENTRY_SHRINKSHROOM    = 83747,

                ACHIEVEMENT_ENTRY_FUNGAL_FRENZY     = 5450
            };

            void HandleCompleteAchievement()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (target->HasAura(SPELL_ENTRY_POOLSTOOL) && target->HasAura(SPELL_ENTRY_SHRINKSHROOM) &&
                            target->HasAura(SPELL_ENTRY_SHUFFLETRUFFLE))
                        {
                            if (AchievementEntry const* fungalFrenzy = sAchievementMgr->GetAchievement(ACHIEVEMENT_ENTRY_FUNGAL_FRENZY))
                                target->ToPlayer()->CompletedAchievement(fungalFrenzy);
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_trapcap_achievement_SpellScript::HandleCompleteAchievement);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_trapcap_achievement_SpellScript();
        }
};

class spell_summon_jade_crystal_composte : public SpellScriptLoader
{
    public:
        spell_summon_jade_crystal_composte() : SpellScriptLoader("spell_summon_jade_crystal_composte") { }

        class spell_summon_jade_crystal_composte_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_jade_crystal_composte_SpellScript);

            enum Id
            {
                SPELL_SHATTER_JADE_CRYSTAL  = 80389,
                SPELL_EARTHQUAKE_SHAKE      = 73238
            };

            void HandleSummonNpc()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->CastWithDelay(4000, caster, SPELL_EARTHQUAKE_SHAKE, true);
                    caster->CastWithDelay(8000, caster, SPELL_EARTHQUAKE_SHAKE, true);
                    caster->CastWithDelay(12000, caster, SPELL_SHATTER_JADE_CRYSTAL, true);
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_summon_jade_crystal_composte_SpellScript::HandleSummonNpc);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_jade_crystal_composte_SpellScript();
        }
};

class spell_absorb_fire_soothing_totem : public SpellScriptLoader
{
    public:
        spell_absorb_fire_soothing_totem() : SpellScriptLoader("spell_absorb_fire_soothing_totem") { }

        class spell_absorb_fire_soothing_totem_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_absorb_fire_soothing_totem_SpellScript);

            enum Id
            {
                NPC_UNBOUND_FIRE_ELEMENTAL  = 32999,
                SPELL_FIRE_ABSORB           = 65348
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* unboundFireElemental = caster->FindNearestCreature(NPC_UNBOUND_FIRE_ELEMENTAL, 8.0f, false))
                    {
                        if (!unboundFireElemental->HasAura(SPELL_FIRE_ABSORB))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        else
                        {
                            unboundFireElemental->RemoveAurasDueToSpell(SPELL_FIRE_ABSORB);
                            return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_absorb_fire_soothing_totem_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_absorb_fire_soothing_totem_SpellScript();
        }
};

class spell_blessed_herb_bundle_furbolg : public SpellScriptLoader
{
    public:
        spell_blessed_herb_bundle_furbolg() : SpellScriptLoader("spell_blessed_herb_bundle_furbolg") { }

        class spell_blessed_herb_bundle_furbolg_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_blessed_herb_bundle_furbolg_SpellScript);

            enum Id
            {
                NPC_CORRUPTED_BLACKWOOD = 33044
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                        {
                            if (target->ToCreature()->GetEntry() == NPC_CORRUPTED_BLACKWOOD)
                                return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_BAD_TARGETS;
            }

            void HandleSummonCorruption()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                        {
                            if (target->ToCreature()->GetEntry() == NPC_CORRUPTED_BLACKWOOD)
                                caster->Kill(target, false);
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_blessed_herb_bundle_furbolg_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_blessed_herb_bundle_furbolg_SpellScript::HandleSummonCorruption);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_blessed_herb_bundle_furbolg_SpellScript();
        }
};

class spell_void_rip : public SpellScriptLoader
{
    public:
        spell_void_rip() : SpellScriptLoader("spell_void_rip") { }

        class spell_void_rip_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_void_rip_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                        target->SetControlled(true, UNIT_STATE_CONTROLLED);
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                    target->SetControlled(false, UNIT_STATE_CONTROLLED);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_void_rip_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_void_rip_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_void_rip_AuraScript();
        }
};

class spell_generic_pvp_trinket : public SpellScriptLoader
{
public:
    spell_generic_pvp_trinket() : SpellScriptLoader("spell_generic_pvp_trinket")
    {
    }

    class spell_generic_pvp_trinket_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_generic_pvp_trinket_SpellScript);

        enum Id
        {
            SPELL_PVP_TRINKET_ALLIANCE  = 97403,
            SPELL_PVP_TRINKET_HORDE     = 97404,
            SPELL_PVP_TRINKET_NEUTRAL   = 97979         // We need more information on that neutral effect!
        };

        void HandlePvPTrinketVisual()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    switch (caster->ToPlayer()->GetTeam())
                    {
                        case HORDE:
                            caster->CastSpell(caster, SPELL_PVP_TRINKET_HORDE, true);
                            break;
                        case ALLIANCE:
                            caster->CastSpell(caster, SPELL_PVP_TRINKET_ALLIANCE, true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_generic_pvp_trinket_SpellScript::HandlePvPTrinketVisual);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_generic_pvp_trinket_SpellScript();
    }
};

class spell_taxi_to_ebon_hold : public SpellScriptLoader
{
public:
    spell_taxi_to_ebon_hold() : SpellScriptLoader("spell_taxi_to_ebon_hold")
    {
    }

    class spell_taxi_to_ebon_hold_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_taxi_to_ebon_hold_SpellScript);

        enum Id
        {
            QUEST_THE_SCARLET_APOCALYPSE    = 12778
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                    if (caster->ToPlayer()->GetQuestStatus(QUEST_THE_SCARLET_APOCALYPSE) == QUEST_STATUS_REWARDED)
                        return SPELL_FAILED_DONT_REPORT;
            }
            return SPELL_CAST_OK;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_taxi_to_ebon_hold_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_taxi_to_ebon_hold_SpellScript();
    }
};

class spell_arena_shadow_sight : public SpellScriptLoader
{
public:
    spell_arena_shadow_sight() : SpellScriptLoader("spell_arena_shadow_sight")
    {
    }

    class spell_arena_shadow_sight_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_arena_shadow_sight_AuraScript);

        void BeforeApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->HasAuraType(SPELL_AURA_MOD_STEALTH))
                    target->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_arena_shadow_sight_AuraScript::BeforeApply, EFFECT_0, SPELL_AURA_DETECT_STEALTH, AURA_EFFECT_HANDLE_REAL);
        }

    };

    AuraScript* GetAuraScript() const
    {
        return new spell_arena_shadow_sight_AuraScript();
    }
};

class spell_engineering_research : public SpellScriptLoader
{
public:
    spell_engineering_research() : SpellScriptLoader("spell_engineering_research")
    {
    }

    class spell_engineering_research_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_engineering_research_SpellScript);

        enum researchId
        {
            QUICKFLIP_DEFLECTION_PLATES     = 82177,
            SPINAL_HEALING_INJECTOR         = 82200,
            SYNAPSE_SPRINGS                 = 82175,
            TAZIK_SHOCKER                   = 82180,
            Z50_MANA_GULPER                 = 82201,
            CARDBOARD_ASSASSIN              = 84425,
            GROUNDED_PLASMA_SHIELD          = 84427,
            INVISIBILITY_FIELD              = 84424
        };

        void HandleDiscover()
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    uint32 const discoverSpell[] = { QUICKFLIP_DEFLECTION_PLATES, SPINAL_HEALING_INJECTOR, SYNAPSE_SPRINGS, TAZIK_SHOCKER, Z50_MANA_GULPER, CARDBOARD_ASSASSIN, GROUNDED_PLASMA_SHIELD, INVISIBILITY_FIELD };
                    for (uint8 checkSpell = 0; checkSpell < 8; checkSpell++)
                    {
                        if (player->HasSpell(discoverSpell[checkSpell]))
                            continue;

                        player->learnSpell(discoverSpell[checkSpell], true);
                        return;
                    }
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_engineering_research_SpellScript::HandleDiscover);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_engineering_research_SpellScript();
    }
};

class spell_blackjack_hyjal : public SpellScriptLoader
{
public:
    spell_blackjack_hyjal() : SpellScriptLoader("spell_blackjack_hyjal")
    {
    }

    enum npcId
    {
        NPC_TWILIGHT_RECRUIT    = 39619
    };

    class spell_blackjack_hyjal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_blackjack_hyjal_SpellScript);

        SpellCastResult CheckCast()
        {
            if (Unit* target = GetExplTargetUnit())
            {
                if (target->GetTypeId() == TYPEID_UNIT && target->GetEntry() == NPC_TWILIGHT_RECRUIT)
                    return SPELL_CAST_OK;
            }
            return SPELL_FAILED_BAD_TARGETS;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_blackjack_hyjal_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_blackjack_hyjal_SpellScript();
    }
};

class spell_gen_vengeance_decay : public SpellScriptLoader
{
public:
    spell_gen_vengeance_decay() : SpellScriptLoader("spell_gen_vengeance_decay")
    {
    }

    class spell_gen_vengeance_decay_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_gen_vengeance_decay_AuraScript);

        void OnUpdate(AuraEffect* /*aurEff*/)
        {
            if (Unit* owner = GetUnitOwner())
            {
                if (owner->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (Aura* vengeance = owner->GetAura(GetSpellInfo()->Id, owner->GetGUID(), NULL, EFFECT_0))
                {
                    // Decay rate is 33% of the last damage taken
                    float decayRate = 0.33f;
                    uint32 damageTaken = owner->m_lastDamageTaken;
                    int32 amount = int32(vengeance->GetEffect(EFFECT_0)->GetAmount());
                    int32 decayedAmount = int32(damageTaken * decayRate);
                    int32 finalAmount = int32(amount - decayedAmount);

                    // Update Vengeance Buff
                    if (decayedAmount > 0 && damageTaken > 0 && !owner->GetDamageTakenInPastSecs(3))
                    {
                        owner->ToPlayer()->RemoveSpellCooldown(GetSpellInfo()->Id, true);
                        owner->CastCustomSpell(GetUnitOwner(), GetSpellInfo()->Id, &finalAmount, &finalAmount, NULL, true);
                    }

                    // Cleanups
                    if (amount <= 0)
                    {
                        owner->RemoveAurasDueToSpell(GetSpellInfo()->Id);
                        decayedAmount = 0;
                        damageTaken = 0;
                        finalAmount = 0;
                        owner->m_lastDamageTaken = 0;
                    }
                }
            }
        }

        void Register()
        {
            OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_gen_vengeance_decay_AuraScript::OnUpdate, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_gen_vengeance_decay_AuraScript();
    }
};

class spell_dh_deepvein_patch_kit : public SpellScriptLoader
{
public:
    spell_dh_deepvein_patch_kit() : SpellScriptLoader("spell_dh_deepvein_patch_kit")
    {
    }

    enum npcId
    {
        NPC_INJURED_EARTHEN     = 43229
    };

    class spell_dh_deepvein_patch_kit_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dh_deepvein_patch_kit_SpellScript);

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                    if (target->GetTypeId() == TYPEID_UNIT)
                        if (target->ToCreature() && target->GetEntry() == NPC_INJURED_EARTHEN)
                            return SPELL_CAST_OK;
            }

            return SPELL_FAILED_BAD_TARGETS;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_dh_deepvein_patch_kit_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dh_deepvein_patch_kit_SpellScript();
    }
};

void AddSC_generic_spell_scripts()
{
    new spell_gen_absorb0_hitlimit1();
    new spell_gen_aura_of_anger();
    new spell_gen_av_drekthar_presence();
    new spell_gen_burn_brutallus();
    new spell_gen_cannibalize();
    //new spell_gen_parachute();
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
    new spell_chloroform();
    new spell_blackrock_holding_pen_key();
    new spell_plant_seaforium();
    new spell_bravo_company_broadcast();
    new spell_bravo_company_field_kit();
    new spell_marked_for_retrieval();
    new spell_enohar_explosive_arrow();
    new spell_amulet_ritual();
    new spell_consecrated_tripetricine();
    new spell_blackrock_disguise();
    new spell_razor_sharp_scorpid_barb();
    new spell_worgsaw();
    new spell_remove_blackrock_disguise();
    new spell_loramus_demon_grip();
    new spell_stone_knife();
    new spell_billy_goat_blast();
    new spell_blessed_floodlily();
    new spell_tiki_torch();
    new spell_ritual_of_shadra();
    new spell_shadow_prison();
    new spell_place_dithers_drum();
    new spell_overcharge_effect();
    new spell_raynes_seed();
    new spell_gather_liquid_sample();
    new spell_trial_of_the_crypt();
    new spell_bury_blade();
    new spell_destroy_threshjin_body();
    new spell_burn_corpse();
    new spell_summon_argent_lightwell();
    new spell_gen_cosmetic_rope();
    new spell_blow_horn_of_challenge();
    new spell_soothing_seeds();
    new spell_flag_capture();
    new spell_dismembering();
    new spell_burning_pitch();
    new spell_sabotage_bael_dun();
    new spell_throw_torch_catapult();
    new spell_bramblestaff();
    new spell_clap_em_in_irons();
    new spell_frazzlecraz_cave();
    new spell_burn_direhorn_post();
    new spell_redeem_remains();
    new spell_unleash_captured_raptor();
    new spell_lay_wreath();
    new spell_salvage_wreckage();
    new spell_bottle_of_grog();
    new spell_pirates_crowbar();
    new spell_setup_an_oil_drilling_rig();
    new spell_splithoof_brand();
    new spell_shuhalo_artifacts();
    new spell_pry_armor();
    new spell_signal_rocket();
    new spell_climb_up_tree();
    new spell_climb_down_tree();
    new spell_chuck_a_bear();
    new spell_flameward_activated();
    new spell_tortolla_shell();
    new spell_hyjal_extinguish_flames();
    new spell_answer_yes();
    new spell_answer_no();
    new spell_dismiss_orb_of_ascension();
    new spell_podium_inspire();
    new spell_podium_incite();
    new spell_podium_pander();
    new spell_horn_of_cenarius();
    new spell_place_drake_skull();
    new spell_drums_of_the_turtle_god();
    new spell_summon_spirit_of_logosh();
    new spell_goldmine_fire_totem();
    new spell_stonefather_boon_banner();
    new spell_rockslide_reagent();
    new spell_twilight_firelance_equipped();
    new spell_trogg_crate();
    new spell_carve_meat();
    new spell_place_basilisk_meat();
    new spell_place_earthen_ring_banner();
    new spell_elementium_grapple_line();
    new spell_pebble_summon_aura();
    new spell_petrifying_gaze();
    new spell_red_mist_aura();
    new spell_strike_resonating_crystal();
    new spell_searing_breath();
    new spell_trapcap_achievement();
    new spell_summon_jade_crystal_composte();
    new spell_absorb_fire_soothing_totem();
    new spell_blessed_herb_bundle_furbolg();
    new spell_void_rip();
    new spell_generic_pvp_trinket();
    new spell_taxi_to_ebon_hold();
    new spell_arena_shadow_sight();
    new spell_engineering_research();
    new spell_blackjack_hyjal();
    new spell_gen_vengeance_decay();
    new spell_dh_deepvein_patch_kit();
}
