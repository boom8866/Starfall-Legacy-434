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
 * Scripts for spells with SPELLFAMILY_SHAMAN and SPELLFAMILY_GENERIC spells used by shaman players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_sha_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "GridNotifiers.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum ShamanSpells
{
    SPELL_HUNTER_INSANITY                       = 95809,
    SPELL_MAGE_TEMPORAL_DISPLACEMENT            = 80354,
    SPELL_SHAMAN_ANCESTRAL_AWAKENING_PROC       = 52752,
    SPELL_SHAMAN_BIND_SIGHT                     = 6277,
    SPELL_SHAMAN_EARTH_SHIELD_HEAL              = 379,
    SPELL_SHAMAN_EXHAUSTION                     = 57723,
    SPELL_SHAMAN_FIRE_NOVA_TRIGGERED_R1         = 8349,
    SPELL_SHAMAN_FLAME_SHOCK                    = 8050,
    SPELL_SHAMAN_GLYPH_OF_EARTH_SHIELD          = 63279,
    SPELL_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM  = 55456,
    SPELL_SHAMAN_GLYPH_OF_MANA_TIDE             = 55441,
    SPELL_SHAMAN_GLYPH_OF_THUNDERSTORM          = 62132,
    SPELL_SHAMAN_LAVA_SURGE                     = 77755,
    SPELL_SHAMAN_LAVA_SURGE_TRIGGERED           = 77762,
    SPELL_SHAMAN_LAVA_BURST                     = 51505,
    SPELL_SHAMAN_LAVA_FLOWS_R1                  = 51480,
    SPELL_SHAMAN_LAVA_FLOWS_TRIGGERED_R1        = 65264,
    SPELL_SHAMAN_SATED                          = 57724,
    SPELL_SHAMAN_STORM_EARTH_AND_FIRE           = 51483,
    SPELL_SHAMAN_TOTEM_EARTHBIND_EARTHGRAB      = 64695,
    SPELL_SHAMAN_TOTEM_EARTHBIND_TOTEM          = 6474,
    SPELL_SHAMAN_TOTEM_EARTHEN_POWER            = 59566,
    SPELL_SHAMAN_TOTEM_HEALING_STREAM_HEAL      = 52042,

    SPELL_SHAMAN_HEALING_RAIN                   = 73920,
    SPELL_SHAMAN_HEALING_RAIN_EFFECT            = 73921,

    SPELL_SHAMAN_EARTHQUAKE                     = 61882,
    SPELL_SHAMAN_EARTHQUAKE_EFFECT              = 77478,
    SPELL_SHAMAN_EARTHQUAKE_KNOCKDOWN           = 77505,

    SPELL_SHAMAN_SPIRIT_LINK                    = 98021,

    SPELL_SHAMAN_UNLEASH_WIND                   = 73681,
    SPELL_SHAMAN_UNLEASH_FROST                  = 73682,
    SPELL_SHAMAN_UNLEASH_FLAME                  = 73683,
    SPELL_SHAMAN_UNLEASH_EARTH                  = 73684,
    SPELL_SHAMAN_UNLEASH_LIFE                   = 73685,
    SPELL_SHAMAN_EARTHLIVING_WEAPON             = 52007,
    SPELL_SHAMAN_FLAMETONGUE_WEAPON             = 10400,
    SPELL_SHAMAN_FROSTBRAND_WEAPON              = 8033,
    SPELL_SHAMAN_ROCKBITER_WEAPON               = 36494,
    SPELL_SHAMAN_WINDFURY_WEAPON                = 33757,

    SPELL_SHAMAN_FEEDBACK                       = 86183,
    SPELL_SHAMAN_ELEMENTAL_MASTERY              = 16166,

    SPELL_SHAMAN_FULMINATION                    = 88766,
    SPELL_SHAMAN_FULMINATION_DAMAGE             = 88767,
    SPELL_SHAMAN_FULMINATION_GRAPHIC_EFFECT     = 95774,
    SPELL_SHAMAN_LIGHTNING_SHIELD               = 324,
    SPELL_SHAMAN_LIGHTNING_SHIELD_DAMAGE        = 26364,
    SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH            = 77746,
    SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH_AURA       = 77747,
    SHAMAN_SPELL_SEARING_FLAMES                 = 77661
};

enum ShamanSpellIcons
{
    SHAMAN_ICON_ID_SOOTHING_RAIN                = 2011,
    SHAMAN_ICON_ID_SHAMAN_LAVA_FLOW             = 3087
};

// 52759 - Ancestral Awakening
/// Updated 4.3.4
class spell_sha_ancestral_awakening_proc : public SpellScriptLoader
{
    public:
        spell_sha_ancestral_awakening_proc() : SpellScriptLoader("spell_sha_ancestral_awakening_proc") { }

        class spell_sha_ancestral_awakening_proc_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_ancestral_awakening_proc_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_ANCESTRAL_AWAKENING_PROC))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                if (GetCaster() && GetHitUnit())
                    GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_SHAMAN_ANCESTRAL_AWAKENING_PROC, &damage, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_ancestral_awakening_proc_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_ancestral_awakening_proc_SpellScript();
        }
};

// 2825 - Bloodlust
/// Updated 4.3.4
class spell_sha_bloodlust : public SpellScriptLoader
{
    public:
        spell_sha_bloodlust() : SpellScriptLoader("spell_sha_bloodlust") { }

        class spell_sha_bloodlust_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_bloodlust_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_SATED))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_SATED));
                targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_HUNTER_INSANITY));
                targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SPELL_SHAMAN_SATED, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_sha_bloodlust_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_bloodlust_SpellScript();
        }
};

// 1064 - Chain Heal
/// Updated 4.3.4
class spell_sha_chain_heal : public SpellScriptLoader
{
    public:
        spell_sha_chain_heal() : SpellScriptLoader("spell_sha_chain_heal") { }

        class spell_sha_chain_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_chain_heal_SpellScript);

            bool Load()
            {
                firstHeal = true;
                riptide = false;
                amount = 0;
                return true;
            }

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                if (firstHeal)
                {
                    // Check if the target has Riptide
                    if (AuraEffect* aurEff = GetHitUnit()->GetAuraEffect(SPELL_AURA_PERIODIC_HEAL, SPELLFAMILY_SHAMAN, 0, 0, 0x10, GetCaster()->GetGUID()))
                    {
                        riptide = true;
                        amount = aurEff->GetSpellInfo()->Effects[EFFECT_2].CalcValue();
                        // Consume it
                        GetHitUnit()->RemoveAura(aurEff->GetBase());
                    }
                    firstHeal = false;
                }
                // Riptide increases the Chain Heal effect by 25%
                if (riptide)
                {
                    uint32 bonus = CalculatePct(GetHitHeal(), amount);
                    SetHitHeal(GetHitHeal() + bonus);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_chain_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            }

            bool firstHeal;
            bool riptide;
            uint32 amount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_chain_heal_SpellScript();
        }
};

// 6474 - Earthbind Totem - Fix Talent:Earthen Power, Earth's Grasp
/// Updated 4.3.4
class spell_sha_earthbind_totem : public SpellScriptLoader
{
    public:
        spell_sha_earthbind_totem() : SpellScriptLoader("spell_sha_earthbind_totem") { }

        class spell_sha_earthbind_totem_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_earthbind_totem_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_TOTEM_EARTHBIND_TOTEM) || !sSpellMgr->GetSpellInfo(SPELL_SHAMAN_TOTEM_EARTHEN_POWER))
                    return false;
                return true;
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (!GetCaster())
                    return;
                if (Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself())
                    if (AuraEffect* aur = owner->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, 2289, 0))
                        if (roll_chance_i(aur->GetBaseAmount()))
                            GetTarget()->CastSpell((Unit*)NULL, SPELL_SHAMAN_TOTEM_EARTHEN_POWER, true);
            }

            void Apply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;
                Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself();
                if (!owner)
                    return;
                // Earth's Grasp
                if (AuraEffect* aurEff = owner->GetAuraEffectOfRankedSpell(SPELL_SHAMAN_STORM_EARTH_AND_FIRE, EFFECT_1))
                {
                    if (roll_chance_i(aurEff->GetBaseAmount()))
                        GetCaster()->CastSpell(GetCaster(), SPELL_SHAMAN_TOTEM_EARTHBIND_EARTHGRAB, false);
                }
            }

            void Register()
            {
                 OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthbind_totem_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
                 OnEffectApply += AuraEffectApplyFn(spell_sha_earthbind_totem_AuraScript::Apply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_earthbind_totem_AuraScript();
        }
};

class EarthenPowerTargetSelector
{
    public:
        EarthenPowerTargetSelector() { }

        bool operator() (WorldObject* target)
        {
            if (!target->ToUnit())
                return true;

            if (!target->ToUnit()->HasAuraWithMechanic(1 << MECHANIC_SNARE))
                return true;

            return false;
        }
};

// 59566 - Earthen Power
class spell_sha_earthen_power : public SpellScriptLoader
{
    public:
        spell_sha_earthen_power() : SpellScriptLoader("spell_sha_earthen_power") { }

        class spell_sha_earthen_power_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_earthen_power_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (unitList.empty())
                    return;

                unitList.remove_if(EarthenPowerTargetSelector());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_earthen_power_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_earthen_power_SpellScript();
        }
};

// 1535 Fire Nova
/// Updated 4.3.4
class spell_sha_fire_nova : public SpellScriptLoader
{
    public:
        spell_sha_fire_nova() : SpellScriptLoader("spell_sha_fire_nova") { }

        class spell_sha_fire_nova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_fire_nova_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (target->HasAura(SPELL_SHAMAN_FLAME_SHOCK))
                        caster->CastSpell(target, SPELL_SHAMAN_FIRE_NOVA_TRIGGERED_R1, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_fire_nova_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_fire_nova_SpellScript();
        }
};

// 8050 -Flame Shock
/// Updated 4.3.4
class spell_sha_flame_shock : public SpellScriptLoader
{
    public:
        spell_sha_flame_shock() : SpellScriptLoader("spell_sha_flame_shock") { }

        class spell_sha_flame_shock_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_flame_shock_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LAVA_FLOWS_R1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LAVA_FLOWS_TRIGGERED_R1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LAVA_SURGE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LAVA_SURGE_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* /*dispelInfo*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Lava Flows
                    if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, SHAMAN_ICON_ID_SHAMAN_LAVA_FLOW, EFFECT_0))
                    {
                        if (sSpellMgr->GetFirstSpellInChain(SPELL_SHAMAN_LAVA_FLOWS_R1) != sSpellMgr->GetFirstSpellInChain(aurEff->GetId()))
                            return;

                        int32 basepoints = aurEff->GetBaseAmount();
                        caster->CastCustomSpell(caster, SPELL_SHAMAN_LAVA_FLOWS_TRIGGERED_R1, &basepoints, NULL, NULL, true);
                    }
                }
            }

            void OnTick(AuraEffect const* aurEff)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect* auraEff = caster->GetAuraEffectOfRankedSpell(SPELL_SHAMAN_LAVA_SURGE, EFFECT_0))
                        if (roll_chance_i(auraEff->GetSpellInfo()->ProcChance))
                            caster->CastSpell(caster, SPELL_SHAMAN_LAVA_SURGE_TRIGGERED, false);
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_sha_flame_shock_AuraScript::HandleDispel);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_flame_shock_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_flame_shock_AuraScript();
        }
};

// 52041 - Healing Stream Totem
/// Updated 4.3.4
class spell_sha_healing_stream_totem : public SpellScriptLoader
{
    public:
        spell_sha_healing_stream_totem() : SpellScriptLoader("spell_sha_healing_stream_totem") { }

        class spell_sha_healing_stream_totem_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_healing_stream_totem_SpellScript);

            enum spellId
            {
                GLYPH_OF_HEALING_STREAM_TOTEM       = 55456,
                SPELL_SHAMAN_ELEMENTAL_RESISTANCE   = 8185,
                SPELL_PASSIVE_PURIFICATION          = 16213
            };

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                return sSpellMgr->GetSpellInfo(SPELL_SHAMAN_TOTEM_HEALING_STREAM_HEAL);
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                int32 damage = GetEffectValue();
                SpellInfo const* triggeringSpell = GetTriggeringSpell();
                if (Unit* target = GetHitUnit())
                {
                    if (Unit* caster = GetCaster())
                    {
                        if (Unit* owner = caster->GetOwner())
                        {
                            if (triggeringSpell)
                                damage = int32(owner->SpellHealingBonusDone(target, triggeringSpell, damage, HEAL));

                            // Soothing Rains
                            if (AuraEffect* dummy = owner->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, SHAMAN_ICON_ID_SOOTHING_RAIN, EFFECT_0))
                                AddPct(damage, dummy->GetAmount());

                            // Glyph of Healing Stream Totem
                            if (owner->HasAura(GLYPH_OF_HEALING_STREAM_TOTEM))
                                caster->AddAura(SPELL_SHAMAN_ELEMENTAL_RESISTANCE, caster);

                            damage = int32(target->SpellHealingBonusTaken(owner, triggeringSpell, damage, HEAL));

                            // Restoration - Purification
                            if (owner->HasAura(SPELL_PASSIVE_PURIFICATION))
                                damage += damage * 0.25f;
                        }

                        caster->CastCustomSpell(target, SPELL_SHAMAN_TOTEM_HEALING_STREAM_HEAL, &damage, 0, 0, true, 0, 0, GetOriginalCaster()->GetGUID());
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_healing_stream_totem_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_healing_stream_totem_SpellScript();
        }
};

// 32182 - Heroism
/// Updated 4.3.4
class spell_sha_heroism : public SpellScriptLoader
{
    public:
        spell_sha_heroism() : SpellScriptLoader("spell_sha_heroism") { }

        class spell_sha_heroism_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_heroism_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EXHAUSTION))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_EXHAUSTION));
                targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_HUNTER_INSANITY));
                targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SPELL_SHAMAN_EXHAUSTION, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_sha_heroism_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_heroism_SpellScript();
        }
};

// 16191 - Mana Tide
/// Updated 4.3.4
class spell_sha_mana_tide_totem : public SpellScriptLoader
{
    public:
        spell_sha_mana_tide_totem() : SpellScriptLoader("spell_sha_mana_tide_totem") { }

        class spell_sha_mana_tide_totem_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_mana_tide_totem_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* owner = caster->GetOwner())
                    {
                        std::map<SpellGroup, int32> spellGroups;
                        float spirit = owner->GetStat(STAT_SPIRIT) * 2.0f;
                        Unit::AuraEffectList const& auraList = owner->GetAuraEffectsByType(SPELL_AURA_MOD_STAT);
                        for (Unit::AuraEffectList::const_iterator i = auraList.begin(); i != auraList.end(); ++i)
                        {
                            if ((*i)->GetMiscValue() == UNIT_MOD_STAT_SPIRIT)
                            {
                                if ((*i)->GetBase()->GetDuration() <= 45*IN_MILLISECONDS)
                                {
                                    if (!sSpellMgr->AddSameEffectStackRuleSpellGroups((*i)->GetSpellInfo(), (*i)->GetAmount(), spellGroups))
                                        spirit -= (*i)->GetAmount();
                                }
                            }
                        }

                        for (std::map<SpellGroup, int32>::const_iterator itr = spellGroups.begin(); itr != spellGroups.end(); ++itr)
                            spirit -= itr->second;

                        amount = spirit;
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_mana_tide_totem_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_STAT);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_mana_tide_totem_AuraScript();
        }
};

// 73920 Healing Rain
// Updated 4.3.4
class spell_sha_healing_rain : public SpellScriptLoader
{
public:
    spell_sha_healing_rain() : SpellScriptLoader("spell_sha_healing_rain") { }

    class spell_sha_healing_rain_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_healing_rain_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            return sSpellStore.LookupEntry(SPELL_SHAMAN_HEALING_RAIN_EFFECT);
        }

        void OnTick(AuraEffect const* aurEff)
        {
            if (DynamicObject* dynObj = GetCaster()->GetDynObject(SPELL_SHAMAN_HEALING_RAIN))
                GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_SHAMAN_HEALING_RAIN_EFFECT, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_healing_rain_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_healing_rain_AuraScript();
    }
};

// 61882 Earthquake
// Updated 4.3.4
class spell_sha_earthquake_trigger : public SpellScriptLoader
{
public:
    spell_sha_earthquake_trigger() : SpellScriptLoader("spell_sha_earthquake_trigger") { }

    class spell_sha_earthquake_trigger_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earthquake_trigger_AuraScript);

        enum npcId
        {
            NPC_EARTHQUAKE_VISUAL_DND   = 51239
        };

        bool Load()
        {
            visualTriggered = false;
            return true;
        }

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_EARTHQUAKE_EFFECT))
                return false;
            return true;
        }

        void OnTick(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (DynamicObject* dynObj = caster->GetDynObject(SPELL_SHAMAN_EARTHQUAKE))
            {
                caster->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_SHAMAN_EARTHQUAKE_EFFECT, true);
                if (visualTriggered == false)
                {
                    caster->SummonCreature(NPC_EARTHQUAKE_VISUAL_DND, dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), dynObj->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 9000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    visualTriggered = true;
                }
            }
        }

    protected:
        bool visualTriggered;

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthquake_trigger_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_earthquake_trigger_AuraScript();
    }
};

// 77478 Earthquake
// Updated 4.3.4
class spell_sha_earthquake : public SpellScriptLoader
{
public:
    spell_sha_earthquake() : SpellScriptLoader("spell_sha_earthquake") { }

    class spell_sha_earthquake_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_earthquake_SpellScript);

        int32 chance;

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            return sSpellStore.LookupEntry(SPELL_SHAMAN_EARTHQUAKE_KNOCKDOWN);
        }

        bool Load()
        {
            chance = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (roll_chance_i(chance))
                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHAMAN_EARTHQUAKE_KNOCKDOWN, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_earthquake_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_earthquake_SpellScript();
    }
};

// 98020 Spirit Link
// Updated 4.3.4
class spell_sha_spirit_link : public SpellScriptLoader
{
public:
    spell_sha_spirit_link() : SpellScriptLoader("spell_sha_spirit_link") { }

    class spell_sha_spirit_link_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_spirit_link_SpellScript);

        enum spellId
        {
            SPELL_SMOKE_BOMB_EFFECT     = 88611
        };

        bool Load()
        {
            pct = 0;
            players.clear();
            return true;
        }

        void CalculatePercentage(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if (Player* player = (*itr)->ToPlayer())
                {
                    if (player->HasAura(SPELL_SMOKE_BOMB_EFFECT))
                        continue;

                    pct = ((pct * players.size()) + (player->GetHealthPct() / 100.f)) / float(players.size() + 1);
                    players.insert(player);
                }
            }
        }

        void HandleAfterCast()
        {
            for (std::set<Player*>::iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                int32 damage = 0;
                int32 heal   = 0;

                uint32 const bestValue = uint32((*itr)->GetMaxHealth() * pct);

                if (bestValue > (*itr)->GetHealth())
                    heal = bestValue - (*itr)->GetHealth();
                else
                    damage = (*itr)->GetHealth() - bestValue;

                if (damage + heal > 1)
                    GetCaster()->CastCustomSpell(*itr, SPELL_SHAMAN_SPIRIT_LINK, &damage, &heal, NULL, true);
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_spirit_link_SpellScript::CalculatePercentage, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            AfterCast += SpellCastFn(spell_sha_spirit_link_SpellScript::HandleAfterCast);
        }

    private:
        float pct;
        std::set<Player*> players;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_spirit_link_SpellScript();
    }
};

uint32 const UnleashCheck[5][2] =
{
    {SPELL_SHAMAN_WINDFURY_WEAPON, SPELL_SHAMAN_UNLEASH_WIND},
    {SPELL_SHAMAN_FROSTBRAND_WEAPON, SPELL_SHAMAN_UNLEASH_FROST},
    {SPELL_SHAMAN_FLAMETONGUE_WEAPON, SPELL_SHAMAN_UNLEASH_FLAME},
    {SPELL_SHAMAN_ROCKBITER_WEAPON, SPELL_SHAMAN_UNLEASH_EARTH},
    {SPELL_SHAMAN_EARTHLIVING_WEAPON, SPELL_SHAMAN_UNLEASH_LIFE}
};

// 73680 Unleash Elements
// Updated 4.3.4
class spell_sha_unleash_elements : public SpellScriptLoader
{
public:
    spell_sha_unleash_elements() : SpellScriptLoader("spell_sha_unleash_elements") { }

    class spell_sha_unleash_elements_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_unleash_elements_SpellScript);

        bool Load()
        {
            frostBrandActive = false;
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        SpellCastResult CheckTargetUnit()
        {
            frostBrandActive = false;
            if (Player* player = GetCaster()->ToPlayer())
            {
                // Never on self
                if (GetExplTargetUnit() == player)
                {
                    if (!player->HasAura(SPELL_SHAMAN_EARTHLIVING_WEAPON))
                        return SPELL_FAILED_NO_VALID_TARGETS;
                }

                // Special check for Frostbrand Weapon enchantment
                SpellInfo const* info = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FROSTBRAND_WEAPON);
                EnchantDurationList const& enchantments = player->GetEnchantmentList();
                for (EnchantDurationList::const_iterator itr = enchantments.begin(); itr != enchantments.end(); ++itr)
                {
                    if (itr->item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == info->Effects[EFFECT_0].MiscValue)
                        frostBrandActive = true;
                    else
                        frostBrandActive = false;
                }

                // If there are no enchants return custom error
                if (!player->HasAura(SPELL_SHAMAN_WINDFURY_WEAPON) && frostBrandActive == false &&
                    !player->HasAura(SPELL_SHAMAN_FLAMETONGUE_WEAPON) && !player->HasAura(SPELL_SHAMAN_ROCKBITER_WEAPON) &&
                    !player->HasAura(SPELL_SHAMAN_EARTHLIVING_WEAPON))
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_NO_ACTIVE_ENCHANTMENT);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                // If Earthliving Weapon is not present, unallow to cast it on friendly targets
                if (player->HasAura(SPELL_SHAMAN_WINDFURY_WEAPON) || frostBrandActive == true ||
                    player->HasAura(SPELL_SHAMAN_FLAMETONGUE_WEAPON) || player->HasAura(SPELL_SHAMAN_ROCKBITER_WEAPON))
                {
                    if (!player->HasAura(SPELL_SHAMAN_EARTHLIVING_WEAPON) && GetExplTargetUnit()->IsFriendlyTo(player))
                        return SPELL_FAILED_TARGET_FRIENDLY;
                }

                // Check for Earthliving Weapon enchantment and return error if target is enemy
                if (player->HasAura(SPELL_SHAMAN_EARTHLIVING_WEAPON) && !GetExplTargetUnit()->IsFriendlyTo(player))
                {
                    if (!player->HasAura(SPELL_SHAMAN_WINDFURY_WEAPON) && frostBrandActive == false ||
                        !player->HasAura(SPELL_SHAMAN_FLAMETONGUE_WEAPON) && !player->HasAura(SPELL_SHAMAN_ROCKBITER_WEAPON))
                    return SPELL_FAILED_TARGET_ENEMY;
                }
            }

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                for (uint8 i = 0; i < 5; ++i)
                {
                    switch (UnleashCheck[i][1])
                    {
                        case SPELL_SHAMAN_UNLEASH_WIND:
                        case SPELL_SHAMAN_UNLEASH_EARTH:
                        case SPELL_SHAMAN_UNLEASH_FLAME:
                        {
                            if (player->HasAura(UnleashCheck[i][0]))
                            {
                                if (!GetHitUnit()->IsFriendlyTo(GetCaster()))
                                    GetCaster()->CastSpell(GetHitUnit(), UnleashCheck[i][1], TRIGGERED_FULL_MASK);
                            }
                            break;
                        }
                        case SPELL_SHAMAN_UNLEASH_FROST:
                        {
                            SpellInfo const* info = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FROSTBRAND_WEAPON);
                            EnchantDurationList const& enchantments = player->GetEnchantmentList();

                            for (EnchantDurationList::const_iterator itr = enchantments.begin(); itr != enchantments.end(); ++itr)
                            {
                                if (itr->item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == info->Effects[EFFECT_0].MiscValue)
                                {
                                    if (!GetHitUnit()->IsFriendlyTo(GetCaster()))
                                        GetCaster()->CastSpell(GetHitUnit(), SPELL_SHAMAN_UNLEASH_FROST, TRIGGERED_FULL_MASK);
                                    break;
                                }
                            }
                            break;
                        }
                        case SPELL_SHAMAN_UNLEASH_LIFE:
                        {
                            if (player->HasAura(UnleashCheck[i][0]) && GetHitUnit()->IsFriendlyTo(player))
                                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHAMAN_UNLEASH_LIFE, TRIGGERED_FULL_MASK);
                            break;
                        }
                    }
                }
            }
        }

    protected:
        bool frostBrandActive;

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_sha_unleash_elements_SpellScript::CheckTargetUnit);
            OnEffectHitTarget += SpellEffectFn(spell_sha_unleash_elements_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_unleash_elements_SpellScript();
    }
};

// -51490 - Thunderstorm
class spell_sha_thunderstorm : public SpellScriptLoader
{
    public:
        spell_sha_thunderstorm() : SpellScriptLoader("spell_sha_thunderstorm") { }

        class spell_sha_thunderstorm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_thunderstorm_SpellScript);

            void HandleKnockBack(SpellEffIndex effIndex)
            {
                // Glyph of Thunderstorm
                if (GetCaster()->HasAura(SPELL_SHAMAN_GLYPH_OF_THUNDERSTORM))
                    PreventHitDefaultEffect(effIndex);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_thunderstorm_SpellScript::HandleKnockBack, EFFECT_2, SPELL_EFFECT_KNOCK_BACK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_thunderstorm_SpellScript();
        }
};

// 77762 Lava Surge
/// Updated 4.3.4
class spell_sha_lava_surge : public SpellScriptLoader
{
    public:
        spell_sha_lava_surge() : SpellScriptLoader("spell_sha_lava_surge") { }

        class spell_sha_lava_surge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_lava_surge_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LAVA_BURST))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    caster->ToPlayer()->RemoveSpellCooldown(SPELL_SHAMAN_LAVA_BURST, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_lava_surge_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_lava_surge_SpellScript();
        }
};

// 88766 Fulmination
/// Updated 4.3.4
class spell_sha_earth_shock : public SpellScriptLoader
{
    public:
        spell_sha_earth_shock() : SpellScriptLoader("spell_sha_earth_shock") { }

        class spell_sha_earth_shock_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_earth_shock_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FULMINATION))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FULMINATION_DAMAGE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LIGHTNING_SHIELD))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LIGHTNING_SHIELD_DAMAGE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_SHAMAN_FULMINATION_GRAPHIC_EFFECT))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_SHAMAN_FULMINATION))
                    {
                        if (caster->HasAura(SPELL_SHAMAN_LIGHTNING_SHIELD))
                        {
                            uint32 stacks = caster->GetAura(SPELL_SHAMAN_LIGHTNING_SHIELD)->GetCharges();
                            if (stacks > 3)
                            {
                                uint32 basepoints = (sSpellMgr->GetSpellInfo(SPELL_SHAMAN_LIGHTNING_SHIELD_DAMAGE)->Effects[EFFECT_0].CalcValue(caster) * (stacks - 3));
                                basepoints += caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_MAGIC) + GetHitUnit()->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_MAGIC);
                                caster->CastCustomSpell(SPELL_SHAMAN_FULMINATION_DAMAGE, SPELLVALUE_BASE_POINT0, basepoints, GetHitUnit());
                                caster->GetAura(SPELL_SHAMAN_LIGHTNING_SHIELD)->SetCharges(3);
                                caster->RemoveAurasDueToSpell(SPELL_SHAMAN_FULMINATION_GRAPHIC_EFFECT);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_earth_shock_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_earth_shock_SpellScript();
        }
};

// -77829 Ancestral Resolve
class spell_sha_ancestral_resolve : public SpellScriptLoader
{
public:
    spell_sha_ancestral_resolve() : SpellScriptLoader("spell_sha_ancestral_resolve") {}

    class spell_sha_ancestral_resolve_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_ancestral_resolve_AuraScript);

        int32 absorb;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            absorb = GetSpellInfo()->Effects[0].BasePoints;
            return true;
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorption amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;

            if (!caster->HasUnitState(UNIT_STATE_CASTING))
                return;

            absorbAmount = dmgInfo.GetDamage() * absorb / 100;
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_ancestral_resolve_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_sha_ancestral_resolve_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_ancestral_resolve_AuraScript();
    }
};

// 77746 - Totemic Wrath
class spell_sha_totemic_wrath: public SpellScriptLoader
{
public:
    spell_sha_totemic_wrath() : SpellScriptLoader("spell_sha_totemic_wrath") { }

    class spell_sha_totemic_wrath_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_totemic_wrath_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH))
                return false;
            if (!sSpellMgr->GetSpellInfo(SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH_AURA))
                return false;
            return true;
        }

        void HandleEffectApply(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();

            if (target->ToPlayer())
                return;

            if (Unit* caster = aurEff->GetBase()->GetCaster())
            {
                if (caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 2019, 0))
                    target->CastSpell(target, SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH_AURA, true, NULL, aurEff);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_sha_totemic_wrath_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_sha_totemic_wrath_AuraScript();
    }
};

// 3606 - Searing Bolt
class spell_sha_searing_bolt: public SpellScriptLoader
{
public:
    spell_sha_searing_bolt() : SpellScriptLoader("spell_sha_searing_bolt") { }

    class spell_sha_searing_bolt_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_sha_searing_bolt_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_SEARING_FLAMES))
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster()->GetOwner())
            {
                // Searing Flames
                if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, 680, EFFECT_0))
                {
                    uint32 chance = aurEff->GetAmount();
                    if (roll_chance_i(chance))
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            if (Aura* searingFlames = target->GetAura(SHAMAN_SPELL_SEARING_FLAMES, caster->GetGUID()))
                            {
                                if (searingFlames->GetStackAmount() != 5)
                                    searingFlames->ModStackAmount(1);
                                else
                                    searingFlames->RefreshDuration();
                            }
                            else
                                caster->CastSpell(target, SHAMAN_SPELL_SEARING_FLAMES, true, NULL, NULL, caster->GetGUID());
                        }
                    }
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_sha_searing_bolt_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_searing_bolt_SpellScript;
    }
};

class spell_sha_improved_lava_lash : public SpellScriptLoader
{
    public:
        spell_sha_improved_lava_lash() : SpellScriptLoader("spell_sha_improved_lava_lash") { }

        class spell_sha_improved_lava_lash_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_improved_lava_lash_AuraScript);

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (Unit* caster = GetCaster())
                {
                    if (Unit* procTarget = eventInfo.GetProcTarget())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(procTarget, procTarget, 12.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(procTarget, targets, u_check);
                        procTarget->VisitNearbyObject(12.0f, searcher);

                        targets.remove(procTarget);
                        Trinity::Containers::RandomResizeList(targets, 4);
                        for (std::list<Unit*>::iterator singleTarget = targets.begin(); singleTarget != targets.end(); ++singleTarget)
                        {
                            Unit* target = (*singleTarget);
                            if (target)
                            {
                                if (Aura* procShock = procTarget->GetAura(SPELL_SHAMAN_FLAME_SHOCK, caster->GetGUID()))
                                {
                                    if (!target->HasAura(SPELL_SHAMAN_FLAME_SHOCK, caster->GetGUID()))
                                    {
                                        caster->AddAura(SPELL_SHAMAN_FLAME_SHOCK, target);
                                        if (Aura* targetShock = target->GetAura(SPELL_SHAMAN_FLAME_SHOCK, caster->GetGUID()))
                                            targetShock->SetDuration(procShock->GetDuration());
                                    }
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_improved_lava_lash_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_improved_lava_lash_AuraScript();
        }
};

class spell_sha_earth_shield_heal : public SpellScriptLoader
{
public:
    spell_sha_earth_shield_heal() : SpellScriptLoader("spell_sha_earth_shield_heal")
    {
    }

    class spell_sha_earth_shield_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_earth_shield_heal_SpellScript);

        void HandleGlyph(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->HasAura(SPELL_SHAMAN_GLYPH_OF_EARTH_SHIELD))
                {
                    int32 healGlyph = GetHitHeal() * 0.20f;
                    SetHitHeal(GetHitHeal() + healGlyph);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_earth_shield_heal_SpellScript::HandleGlyph, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_earth_shield_heal_SpellScript();
    }
};

void AddSC_shaman_spell_scripts()
{
    new spell_sha_ancestral_awakening_proc();
    new spell_sha_bloodlust();
    new spell_sha_chain_heal();
    new spell_sha_earthbind_totem();
    new spell_sha_earthen_power();
    new spell_sha_fire_nova();
    new spell_sha_flame_shock();
    new spell_sha_healing_stream_totem();
    new spell_sha_heroism();
    new spell_sha_healing_rain();
    new spell_sha_earthquake_trigger();
    new spell_sha_earthquake();
    new spell_sha_mana_tide_totem();
    new spell_sha_spirit_link();
    new spell_sha_unleash_elements();
    new spell_sha_thunderstorm();
    new spell_sha_lava_surge();
    new spell_sha_earth_shock();
    new spell_sha_ancestral_resolve();
    new spell_sha_totemic_wrath();
    new spell_sha_searing_bolt();
    new spell_sha_improved_lava_lash();
    new spell_sha_earth_shield_heal();
}
