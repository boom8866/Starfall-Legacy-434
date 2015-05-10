/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "DatabaseEnv.h"
#include "WorldPacket.h"
#include "Opcodes.h"
#include "Log.h"
#include "UpdateMask.h"
#include "World.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "Player.h"
#include "SkillExtraItems.h"
#include "Unit.h"
#include "Spell.h"
#include "DynamicObject.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Group.h"
#include "UpdateData.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "SharedDefines.h"
#include "Pet.h"
#include "GameObject.h"
#include "GossipDef.h"
#include "Creature.h"
#include "Totem.h"
#include "CreatureAI.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "BattlegroundEY.h"
#include "BattlegroundWS.h"
#include "OutdoorPvPMgr.h"
#include "Language.h"
#include "SocialMgr.h"
#include "Util.h"
#include "VMapFactory.h"
#include "TemporarySummon.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SkillDiscovery.h"
#include "Formulas.h"
#include "Vehicle.h"
#include "ScriptMgr.h"
#include "GameObjectAI.h"
#include "AccountMgr.h"
#include "InstanceScript.h"
#include "PathGenerator.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "ReputationMgr.h"

pEffect SpellEffects[TOTAL_SPELL_EFFECTS] =
{ &Spell::EffectNULL,               //  0
&Spell::EffectInstaKill,            //  1 SPELL_EFFECT_INSTAKILL
&Spell::EffectSchoolDMG,            //  2 SPELL_EFFECT_SCHOOL_DAMAGE
&Spell::EffectDummy,                //  3 SPELL_EFFECT_DUMMY
&Spell::EffectUnused,               //  4 SPELL_EFFECT_PORTAL_TELEPORT          unused
&Spell::EffectTeleportUnits,        //  5 SPELL_EFFECT_TELEPORT_UNITS
&Spell::EffectApplyAura,            //  6 SPELL_EFFECT_APPLY_AURA
&Spell::EffectEnvironmentalDMG,     //  7 SPELL_EFFECT_ENVIRONMENTAL_DAMAGE
&Spell::EffectPowerDrain,           //  8 SPELL_EFFECT_POWER_DRAIN
&Spell::EffectHealthLeech,          //  9 SPELL_EFFECT_HEALTH_LEECH
&Spell::EffectHeal,                 // 10 SPELL_EFFECT_HEAL
&Spell::EffectBind,                 // 11 SPELL_EFFECT_BIND
&Spell::EffectNULL,                 // 12 SPELL_EFFECT_PORTAL
&Spell::EffectUnused,               // 13 SPELL_EFFECT_RITUAL_BASE              unused
&Spell::EffectUnused,               // 14 SPELL_EFFECT_RITUAL_SPECIALIZE        unused
&Spell::EffectUnused,               // 15 SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL   unused
&Spell::EffectQuestComplete,        // 16 SPELL_EFFECT_QUEST_COMPLETE
&Spell::EffectWeaponDmg,            // 17 SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL
&Spell::EffectResurrect,            // 18 SPELL_EFFECT_RESURRECT
&Spell::EffectAddExtraAttacks,      // 19 SPELL_EFFECT_ADD_EXTRA_ATTACKS
&Spell::EffectUnused,               // 20 SPELL_EFFECT_DODGE                    one spell: Dodge
&Spell::EffectUnused,               // 21 SPELL_EFFECT_EVADE                    one spell: Evade (DND)
&Spell::EffectParry,                // 22 SPELL_EFFECT_PARRY
&Spell::EffectBlock,                // 23 SPELL_EFFECT_BLOCK                    one spell: Block
&Spell::EffectCreateItem,           // 24 SPELL_EFFECT_CREATE_ITEM
&Spell::EffectUnused,               // 25 SPELL_EFFECT_WEAPON
&Spell::EffectUnused,               // 26 SPELL_EFFECT_DEFENSE                  one spell: Defense
&Spell::EffectPersistentAA,         // 27 SPELL_EFFECT_PERSISTENT_AREA_AURA
&Spell::EffectSummonType,           // 28 SPELL_EFFECT_SUMMON
&Spell::EffectLeap,                 // 29 SPELL_EFFECT_LEAP
&Spell::EffectEnergize,             // 30 SPELL_EFFECT_ENERGIZE
&Spell::EffectWeaponDmg,            // 31 SPELL_EFFECT_WEAPON_PERCENT_DAMAGE
&Spell::EffectTriggerMissileSpell,  // 32 SPELL_EFFECT_TRIGGER_MISSILE
&Spell::EffectOpenLock,             // 33 SPELL_EFFECT_OPEN_LOCK
&Spell::EffectSummonChangeItem,     // 34 SPELL_EFFECT_SUMMON_CHANGE_ITEM
&Spell::EffectApplyAreaAura,        // 35 SPELL_EFFECT_APPLY_AREA_AURA_PARTY
&Spell::EffectLearnSpell,           // 36 SPELL_EFFECT_LEARN_SPELL
&Spell::EffectUnused,               // 37 SPELL_EFFECT_SPELL_DEFENSE            one spell: SPELLDEFENSE (DND)
&Spell::EffectDispel,               // 38 SPELL_EFFECT_DISPEL
&Spell::EffectUnused,               // 39 SPELL_EFFECT_LANGUAGE
&Spell::EffectDualWield,            // 40 SPELL_EFFECT_DUAL_WIELD
&Spell::EffectJump,                 // 41 SPELL_EFFECT_JUMP
&Spell::EffectJumpDest,             // 42 SPELL_EFFECT_JUMP_DEST
&Spell::EffectTeleUnitsFaceCaster,  // 43 SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER
&Spell::EffectLearnSkill,           // 44 SPELL_EFFECT_SKILL_STEP
&Spell::EffectPlayMovie,            // 45 SPELL_EFFECT_PLAY_MOVIE
&Spell::EffectUnused,               // 46 SPELL_EFFECT_SPAWN clientside, unit appears as if it was just spawned
&Spell::EffectTradeSkill,           // 47 SPELL_EFFECT_TRADE_SKILL
&Spell::EffectUnused,               // 48 SPELL_EFFECT_STEALTH                  one spell: Base Stealth
&Spell::EffectUnused,               // 49 SPELL_EFFECT_DETECT                   one spell: Detect
&Spell::EffectTransmitted,          // 50 SPELL_EFFECT_TRANS_DOOR
&Spell::EffectUnused,               // 51 SPELL_EFFECT_FORCE_CRITICAL_HIT       unused
&Spell::EffectUnused,               // 52 SPELL_EFFECT_GUARANTEE_HIT            unused
&Spell::EffectEnchantItemPerm,      // 53 SPELL_EFFECT_ENCHANT_ITEM
&Spell::EffectEnchantItemTmp,       // 54 SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY
&Spell::EffectTameCreature,         // 55 SPELL_EFFECT_TAMECREATURE
&Spell::EffectSummonPet,            // 56 SPELL_EFFECT_SUMMON_PET
&Spell::EffectLearnPetSpell,        // 57 SPELL_EFFECT_LEARN_PET_SPELL
&Spell::EffectWeaponDmg,            // 58 SPELL_EFFECT_WEAPON_DAMAGE
&Spell::EffectCreateRandomItem,     // 59 SPELL_EFFECT_CREATE_RANDOM_ITEM       create item base at spell specific loot
&Spell::EffectProficiency,          // 60 SPELL_EFFECT_PROFICIENCY
&Spell::EffectSendEvent,            // 61 SPELL_EFFECT_SEND_EVENT
&Spell::EffectPowerBurn,            // 62 SPELL_EFFECT_POWER_BURN
&Spell::EffectThreat,               // 63 SPELL_EFFECT_THREAT
&Spell::EffectTriggerSpell,         // 64 SPELL_EFFECT_TRIGGER_SPELL
&Spell::EffectApplyAreaAura,        // 65 SPELL_EFFECT_APPLY_AREA_AURA_RAID
&Spell::EffectRechargeManaGem,      // 66 SPELL_EFFECT_CREATE_MANA_GEM          (possibly recharge it, misc - is item ID)
&Spell::EffectHealMaxHealth,        // 67 SPELL_EFFECT_HEAL_MAX_HEALTH
&Spell::EffectInterruptCast,        // 68 SPELL_EFFECT_INTERRUPT_CAST
&Spell::EffectDistract,             // 69 SPELL_EFFECT_DISTRACT
&Spell::EffectPull,                 // 70 SPELL_EFFECT_PULL                     one spell: Distract Move
&Spell::EffectPickPocket,           // 71 SPELL_EFFECT_PICKPOCKET
&Spell::EffectAddFarsight,          // 72 SPELL_EFFECT_ADD_FARSIGHT
&Spell::EffectUntrainTalents,       // 73 SPELL_EFFECT_UNTRAIN_TALENTS
&Spell::EffectApplyGlyph,           // 74 SPELL_EFFECT_APPLY_GLYPH
&Spell::EffectHealMechanical,       // 75 SPELL_EFFECT_HEAL_MECHANICAL          one spell: Mechanical Patch Kit
&Spell::EffectSummonObjectWild,     // 76 SPELL_EFFECT_SUMMON_OBJECT_WILD
&Spell::EffectScriptEffect,         // 77 SPELL_EFFECT_SCRIPT_EFFECT
&Spell::EffectUnused,               // 78 SPELL_EFFECT_ATTACK
&Spell::EffectSanctuary,            // 79 SPELL_EFFECT_SANCTUARY
&Spell::EffectAddComboPoints,       // 80 SPELL_EFFECT_ADD_COMBO_POINTS
&Spell::EffectUnused,               // 81 SPELL_EFFECT_CREATE_HOUSE             one spell: Create House (TEST)
&Spell::EffectNULL,                 // 82 SPELL_EFFECT_BIND_SIGHT
&Spell::EffectDuel,                 // 83 SPELL_EFFECT_DUEL
&Spell::EffectStuck,                // 84 SPELL_EFFECT_STUCK
&Spell::EffectSummonPlayer,         // 85 SPELL_EFFECT_SUMMON_PLAYER
&Spell::EffectActivateObject,       // 86 SPELL_EFFECT_ACTIVATE_OBJECT
&Spell::EffectGameObjectDamage,     // 87 SPELL_EFFECT_GAMEOBJECT_DAMAGE
&Spell::EffectGameObjectRepair,     // 88 SPELL_EFFECT_GAMEOBJECT_REPAIR
&Spell::EffectGameObjectSetDestructionState,          // 89 SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE
&Spell::EffectKillCreditPersonal,   // 90 SPELL_EFFECT_KILL_CREDIT              Kill credit but only for single person
&Spell::EffectUnused,               // 91 SPELL_EFFECT_THREAT_ALL               one spell: zzOLDBrainwash
&Spell::EffectEnchantHeldItem,      // 92 SPELL_EFFECT_ENCHANT_HELD_ITEM
&Spell::EffectForceDeselect,        // 93 SPELL_EFFECT_FORCE_DESELECT
&Spell::EffectSelfResurrect,        // 94 SPELL_EFFECT_SELF_RESURRECT
&Spell::EffectSkinning,             // 95 SPELL_EFFECT_SKINNING
&Spell::EffectCharge,               // 96 SPELL_EFFECT_CHARGE
&Spell::EffectCastButtons,          // 97 SPELL_EFFECT_CAST_BUTTON (totem bar since 3.2.2a)
&Spell::EffectKnockBack,            // 98 SPELL_EFFECT_KNOCK_BACK
&Spell::EffectDisEnchant,           // 99 SPELL_EFFECT_DISENCHANT
&Spell::EffectInebriate,            //100 SPELL_EFFECT_INEBRIATE
&Spell::EffectFeedPet,              //101 SPELL_EFFECT_FEED_PET
&Spell::EffectDismissPet,           //102 SPELL_EFFECT_DISMISS_PET
&Spell::EffectReputation,           //103 SPELL_EFFECT_REPUTATION
&Spell::EffectSummonObject,         //104 SPELL_EFFECT_SUMMON_OBJECT_SLOT1
&Spell::EffectSurvey,               //105 SPELL_EFFECT_SUMMON_OBJECT_SLOT2
&Spell::EffectRaidMarker,           //106 SPELL_EFFECT_RAID_MARKER
&Spell::EffectSummonObject,         //107 SPELL_EFFECT_SUMMON_OBJECT_SLOT4
&Spell::EffectDispelMechanic,       //108 SPELL_EFFECT_DISPEL_MECHANIC
&Spell::EffectSummonDeadPet,        //109 SPELL_EFFECT_SUMMON_DEAD_PET
&Spell::EffectDestroyAllTotems,     //110 SPELL_EFFECT_DESTROY_ALL_TOTEMS
&Spell::EffectDurabilityDamage,     //111 SPELL_EFFECT_DURABILITY_DAMAGE
&Spell::EffectUnused,               //112 SPELL_EFFECT_112
&Spell::EffectResurrectNew,         //113 SPELL_EFFECT_RESURRECT_NEW
&Spell::EffectTaunt,                //114 SPELL_EFFECT_ATTACK_ME
&Spell::EffectDurabilityDamagePCT,  //115 SPELL_EFFECT_DURABILITY_DAMAGE_PCT
&Spell::EffectSkinPlayerCorpse,     //116 SPELL_EFFECT_SKIN_PLAYER_CORPSE       one spell: Remove Insignia, bg usage, required special corpse flags...
&Spell::EffectSpiritHeal,           //117 SPELL_EFFECT_SPIRIT_HEAL              one spell: Spirit Heal
&Spell::EffectSkill,                //118 SPELL_EFFECT_SKILL                    professions and more
&Spell::EffectApplyAreaAura,        //119 SPELL_EFFECT_APPLY_AREA_AURA_PET
&Spell::EffectUnused,               //120 SPELL_EFFECT_TELEPORT_GRAVEYARD       one spell: Graveyard Teleport Test
&Spell::EffectWeaponDmg,            //121 SPELL_EFFECT_NORMALIZED_WEAPON_DMG
&Spell::EffectUnused,               //122 SPELL_EFFECT_122                      unused
&Spell::EffectSendTaxi,             //123 SPELL_EFFECT_SEND_TAXI                taxi/flight related (misc value is taxi path id)
&Spell::EffectPullTowards,          //124 SPELL_EFFECT_PULL_TOWARDS
&Spell::EffectModifyThreatPercent,  //125 SPELL_EFFECT_MODIFY_THREAT_PERCENT
&Spell::EffectStealBeneficialBuff,  //126 SPELL_EFFECT_STEAL_BENEFICIAL_BUFF    spell steal effect?
&Spell::EffectProspecting,          //127 SPELL_EFFECT_PROSPECTING              Prospecting spell
&Spell::EffectApplyAreaAura,        //128 SPELL_EFFECT_APPLY_AREA_AURA_FRIEND
&Spell::EffectApplyAreaAura,        //129 SPELL_EFFECT_APPLY_AREA_AURA_ENEMY
&Spell::EffectRedirectThreat,       //130 SPELL_EFFECT_REDIRECT_THREAT
&Spell::EffectPlaySound,            //131 SPELL_EFFECT_PLAY_SOUND               sound id in misc value (SoundEntries.dbc)
&Spell::EffectPlayMusic,            //132 SPELL_EFFECT_PLAY_MUSIC               sound id in misc value (SoundEntries.dbc)
&Spell::EffectUnlearnSpecialization,          //133 SPELL_EFFECT_UNLEARN_SPECIALIZATION   unlearn profession specialization
&Spell::EffectKillCredit,           //134 SPELL_EFFECT_KILL_CREDIT              misc value is creature entry
&Spell::EffectNULL,                 //135 SPELL_EFFECT_CALL_PET
&Spell::EffectHealPct,              //136 SPELL_EFFECT_HEAL_PCT
&Spell::EffectEnergizePct,          //137 SPELL_EFFECT_ENERGIZE_PCT
&Spell::EffectLeapBack,             //138 SPELL_EFFECT_LEAP_BACK                Leap back
&Spell::EffectQuestClear,           //139 SPELL_EFFECT_CLEAR_QUEST              Reset quest status (miscValue - quest ID)
&Spell::EffectForceCast,            //140 SPELL_EFFECT_FORCE_CAST
&Spell::EffectForceCast,            //141 SPELL_EFFECT_FORCE_CAST_WITH_VALUE
&Spell::EffectTriggerSpell,         //142 SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE
&Spell::EffectApplyAreaAura,        //143 SPELL_EFFECT_APPLY_AREA_AURA_OWNER
&Spell::EffectKnockBack,            //144 SPELL_EFFECT_KNOCK_BACK_DEST
&Spell::EffectPullTowards,          //145 SPELL_EFFECT_PULL_TOWARDS_DEST                      Black Hole Effect
&Spell::EffectActivateRune,         //146 SPELL_EFFECT_ACTIVATE_RUNE
&Spell::EffectQuestFail,            //147 SPELL_EFFECT_QUEST_FAIL               quest fail
&Spell::EffectTriggerMissileSpell,          //148 SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE
&Spell::EffectChargeDest,           //149 SPELL_EFFECT_CHARGE_DEST
&Spell::EffectQuestStart,           //150 SPELL_EFFECT_QUEST_START
&Spell::EffectTriggerRitualOfSummoning,          //151 SPELL_EFFECT_TRIGGER_SPELL_2
&Spell::EffectSummonRaFFriend,      //152 SPELL_EFFECT_SUMMON_RAF_FRIEND        summon Refer-a-Friend
&Spell::EffectCreateTamedPet,       //153 SPELL_EFFECT_CREATE_TAMED_PET         misc value is creature entry
&Spell::EffectDiscoverTaxi,         //154 SPELL_EFFECT_DISCOVER_TAXI
&Spell::EffectTitanGrip,            //155 SPELL_EFFECT_TITAN_GRIP Allows you to equip two-handed axes, maces and swords in one hand, but you attack $49152s1% slower than normal.
&Spell::EffectEnchantItemPrismatic,          //156 SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC
&Spell::EffectCreateItem2,          //157 SPELL_EFFECT_CREATE_ITEM_2            create item or create item template and replace by some randon spell loot item
&Spell::EffectMilling,              //158 SPELL_EFFECT_MILLING                  milling
&Spell::EffectRenamePet,            //159 SPELL_EFFECT_ALLOW_RENAME_PET         allow rename pet once again
&Spell::EffectNULL,                 //160 SPELL_EFFECT_160                      1 spell - 45534
&Spell::EffectSpecCount,            //161 SPELL_EFFECT_TALENT_SPEC_COUNT        second talent spec (learn/revert)
&Spell::EffectActivateSpec,         //162 SPELL_EFFECT_TALENT_SPEC_SELECT       activate primary/secondary spec
&Spell::EffectUnused,               //163 SPELL_EFFECT_163  unused
&Spell::EffectRemoveAura,           //164 SPELL_EFFECT_REMOVE_AURA
&Spell::EffectDamageFromMaxHealthPCT,          //165 SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT
&Spell::EffectGiveCurrency,         //166 SPELL_EFFECT_GIVE_CURRENCY
&Spell::EffectNULL,                 //167 SPELL_EFFECT_167
&Spell::EffectNULL,                 //168 SPELL_EFFECT_168
&Spell::EffectNULL,                 //169 SPELL_EFFECT_DESTROY_ITEM
&Spell::EffectNULL,                 //170 SPELL_EFFECT_170
&Spell::EffectNULL,                 //171 SPELL_EFFECT_171
&Spell::EffectResurrectWithAura,    //172 SPELL_EFFECT_RESURRECT_WITH_AURA
&Spell::EffectUnlockGuildVaultTab,  //173 SPELL_EFFECT_UNLOCK_GUILD_VAULT_TAB
&Spell::EffectNULL,                 //174 SPELL_EFFECT_174
&Spell::EffectUnused,               //175 SPELL_EFFECT_175  unused
&Spell::EffectNULL,                 //176 SPELL_EFFECT_176
&Spell::EffectNULL,                 //177 SPELL_EFFECT_177
&Spell::EffectUnused,               //178 SPELL_EFFECT_178 unused
&Spell::EffectNULL,                 //179 SPELL_EFFECT_CREATE_AREATRIGGER
&Spell::EffectUnused,               //180 SPELL_EFFECT_180 unused
&Spell::EffectUnused,               //181 SPELL_EFFECT_181 unused
&Spell::EffectNULL,                 //182 SPELL_EFFECT_182
};

void Spell::EffectNULL (SpellEffIndex /*effIndex*/)
{
    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "WORLD: Spell Effect DUMMY");
}

void Spell::EffectUnused (SpellEffIndex /*effIndex*/)
{
    // NOT USED BY ANY SPELL OR USELESS OR IMPLEMENTED IN DIFFERENT WAY IN TRINITY
}

void Spell::EffectResurrectNew (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->isAlive())
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    if (!unitTarget->IsInWorld())
        return;

    Player* target = unitTarget->ToPlayer();

    if (target->IsRessurectRequested())          // already have one active request
        return;

    uint32 health = damage;
    uint32 mana = m_spellInfo->Effects[effIndex].MiscValue;
    ExecuteLogEffectResurrect(effIndex, target);
    target->SetResurrectRequestData(m_caster, health, mana, 0);
    SendResurrectRequest(target);
}

void Spell::EffectInstaKill (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive())
        return;

    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
        if (unitTarget->ToPlayer()->GetCommandStatus(CHEAT_GOD))
            return;

    if (m_caster == unitTarget)          // prevent interrupt message
        finish();

    WorldPacket data(SMSG_SPELLINSTAKILLLOG, 8 + 8 + 4);
    data << uint64(m_caster->GetGUID());
    data << uint64(unitTarget->GetGUID());
    data << uint32(m_spellInfo->Id);
    m_caster->SendMessageToSet(&data, true);

    m_caster->DealDamage(unitTarget, unitTarget->GetHealth(), NULL, NODAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
}

void Spell::EffectEnvironmentalDMG (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive())
        return;

    uint32 absorb = 0;
    uint32 resist = 0;

    m_caster->CalcAbsorbResist(unitTarget, m_spellInfo->GetSchoolMask(), SPELL_DIRECT_DAMAGE, damage, &absorb, &resist, m_spellInfo);

    m_caster->SendSpellNonMeleeDamageLog(unitTarget, m_spellInfo->Id, damage, m_spellInfo->GetSchoolMask(), absorb, resist, false, 0, false);
    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
        unitTarget->ToPlayer()->EnvironmentalDamage(DAMAGE_FIRE, damage);
}

void Spell::EffectSchoolDMG (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
        return;

    if (unitTarget && unitTarget->isAlive())
    {
        if (m_caster->ToTempSummon())
            if (!m_caster->canSeeOrDetect(unitTarget) && m_caster->ToTempSummon()->GetSummoner() != unitTarget)
                return;

        // AoE LoS rule for dynamic objects to prevent application out of Line of Sight
        // This will only prevent the aura application if the Z is major/minor of 2 yards between dynobj and target
        if (m_caster->GetTypeId() == TYPEID_PLAYER || m_caster->GetTypeId() == TYPEID_DYNAMICOBJECT)
            if (m_spellInfo && m_spellInfo->Targets & TARGET_FLAG_DEST_LOCATION && m_spellInfo->SpellFamilyName != SPELLFAMILY_GENERIC && m_targets.GetDst())
                if (unitTarget->GetPositionZ() > (m_targets.GetDstPos()->GetPositionZ() + 2) || unitTarget->GetPositionZ() < (m_targets.GetDstPos()->GetPositionZ() - 2))
                    return;

        bool apply_direct_bonus = true;

        switch (m_spellInfo->SpellFamilyName)
        {
            case SPELLFAMILY_GENERIC:
            {
                // Meteor like spells (divided damage to targets)
                if (m_spellInfo->AttributesCu & SPELL_ATTR0_CU_SHARE_DAMAGE)
                {
                    uint32 count = 0;
                    for (std::list<TargetInfo>::iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ihit)
                        if (ihit->effectMask & (1 << effIndex))
                            ++count;

                    damage /= count;          // divide to all targets
                }

                // better way to check unknown
                switch (m_spellInfo->Id)
                {
                    case 28865: // Consumption
                        damage = (((InstanceMap*)m_caster->GetMap())->GetDifficulty() == REGULAR_DIFFICULTY ? 2750 : 4250);
                        break;
                    case 53349: // Arrow Assault & Ballista Assault
                    case 53118:
                        if (unitTarget)
                            if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                                damage = 0;
                            else
                                damage = urand(99, 140);
                        break;
                    case 25599: // Thundercrash
                        damage = unitTarget->GetHealth() / 2;
                        if (damage < 200)
                            damage = 200;
                        break;
                    case 45072: // arcane charge. must only affect demons (also undead?)
                        if (unitTarget->GetCreatureType() != CREATURE_TYPE_DEMON && unitTarget->GetCreatureType() != CREATURE_TYPE_UNDEAD)
                            return;
                        break;
                    case 51963: // Gargoyle Strike
                        if (Unit* owner = m_caster->GetCharmerOrOwner())
                        {
                            int32 ap = m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.333f;
                            damage = 120 + ap;
                        }
                        break;
                    case 65063: // Emerald Barrage
                        // Return anyway if target is not pointing at creature
                        if (!unitTarget->ToCreature())
                            return;

                        // Cast only on specific targets!
                        if (unitTarget->GetEntry() != 34316 && unitTarget->GetEntry() != 34282)
                            return;
                        break;
                    case 82068: // Darkblaze
                        if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
                        {
                            // Caster and Keeshan are both immune
                            if (unitTarget->GetEntry() != 43812 && unitTarget != m_caster)
                                unitTarget->Kill(unitTarget, false);
                        }
                        break;
                    case 86563: // TDDC 1: Knockback Elemental
                        if (unitTarget && unitTarget->ToCreature())
                        {
                            switch (unitTarget->ToCreature()->GetEntry())
                            {
                                case 46466: // Theldurin the Lost
                                case 46471: // Deathwing
                                    damage = 0;
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;
                    case 87608: // Amakkar's Kidney Shot & Eric's Charge
                    case 87278:
                        if (Vehicle* vehicle = m_caster->GetVehicleKit())
                            for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                                if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                    player->KilledMonsterCredit(46862);
                        break;
                    case 38382: // Fiery Blast & Baelog's Valhalla Shot
                    case 87276:
                        if (Vehicle* vehicle = m_caster->GetVehicleKit())
                            for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                                if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                    player->KilledMonsterCredit(46865);
                        break;
                    case 81318: // Tombshroom Explosion
                        // Set not eligible for achievement
                        if (unitTarget && unitTarget->ToPlayer())
                            unitTarget->ToPlayer()->m_damagedByShroom = 1;
                        break;
                    case 81507: // Fire! Effect
                        if (unitTarget && unitTarget->ToCreature())
                            if (unitTarget->ToCreature()->GetEntry() == 43560)
                                if (m_caster->ToPlayer())
                                    m_caster->ToPlayer()->KilledMonsterCredit(43560);
                        break;
                    case 68213: // Weed Whacker
                        if (m_caster)
                            m_caster->SetHealth(m_caster->GetMaxHealth());
                        break;
                    case 69041: // Rocket Barrage
                        if (m_caster)
                            if (Player* player = m_caster->ToPlayer())
                            {
                                uint32 ap = player->GetTotalAttackPowerValue(MAX_ATTACK) * 0.25f;
                                uint32 sp = player->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_MAGIC) * 0.429f;
                                damage = 1 + ap + sp + (player->getLevel() * 2);
                            }
                        break;
                    case 79021: // Seismic Shard
                        if (m_caster->GetTypeId() == TYPEID_PLAYER)
                            break;

                        if (unitTarget == m_caster)
                        {
                            damage = 0;
                            m_caster->ToCreature()->DespawnOrUnsummon(1000);
                        }
                        break;
                    case 87997: // Storm Hammer
                        if (unitTarget->GetTypeId() == TYPEID_PLAYER || unitTarget == m_caster)
                            damage = 0;
                        break;
                    case 88048: // Static Charge impact
                        // Storm Shield
                        if (unitTarget->HasAura(88027))
                            damage = 0;

                        if (Vehicle* vehicle = unitTarget->GetVehicle())
                            if (vehicle->GetBase()->HasAura(88027))
                            {
                                unitTarget->AddAura(88050, unitTarget);
                                damage = 0;
                            }
                        break;
                    case 75851: // Heat Wave
                    {
                        Aura* superheatedN = m_caster->GetAura(75846);
                        Aura* superheatedH = m_caster->GetAura(93567);
                        if (superheatedN)
                            damage *= superheatedN->GetStackAmount();
                        if (superheatedH)
                            damage *= superheatedH->GetStackAmount();
                        break;
                    }
                    case 84864: // Artillery Barrage
                        if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER)
                            damage = 0;
                        break;
                    case 92734: // Exploding Stuff
                        if (unitTarget)
                        {
                            if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                                damage = 0;

                            if (unitTarget->GetTypeId() == TYPEID_UNIT)
                                if (unitTarget->GetEntry() != 49683)
                                    damage = 0;
                        }
                        break;
                    case 92601: // Detonate Mana
                        if (m_caster && m_caster->GetTypeId() == TYPEID_PLAYER)
                            // Tyrande's Favorite Doll
                            if (Aura* TFD = m_caster->GetAura(92272))
                            {
                                uint32 manaPower = uint32(TFD->GetEffect(EFFECT_1)->GetAmount());
                                damage = manaPower;
                            }
                        break;
                    case 91571: // Shredder Round
                    case 91574: // Destroyer Round
                        if (m_caster && unitTarget)
                            if (unitTarget->GetTypeId() == TYPEID_UNIT)
                            {
                                if (unitTarget->ToCreature()->GetEntry() != 49060 && unitTarget->GetEntry() != 49025 && unitTarget->GetEntry() != 49124)
                                    damage = 0;
                                else
                                {
                                    if (m_spellInfo->Id == 91571)
                                        damage = 28499;
                                    if (m_spellInfo->Id == 91574)
                                        damage = 240000;
                                }
                            }
                            else
                                damage = 0;
                        break;
                    case 86704: // Ancient Fury
                        if (Aura* aur = m_caster->GetAura(86700))
                            damage *= aur->GetStackAmount();
                        break;
                    case 76370: // Warped Twilight
                    case 97300:
                        if (unitTarget)
                            damage = damage * unitTarget->GetMaxHealth() / 100;
                        break;
                    case 74817: // Inferno (Baron Geddon)
                        if (Aura* aur = m_caster->GetAura(74813))
                        {
                            int32 duration = aur->GetDuration() / 1000;
                            int32 maxDuration = aur->GetMaxDuration() / 1000;
                            damage += damage * (maxDuration - duration);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }
            case SPELLFAMILY_WARRIOR:
            {
                switch (m_spellInfo->Id)
                {
                    case 34428: // Victory Rush
                        ApplyPct(damage, m_caster->GetTotalAttackPowerValue(BASE_ATTACK));
                        break;
                    case 46968: // Shockwave
                    {
                        int32 pct = m_caster->CalculateSpellDamage(unitTarget, m_spellInfo, 2);
                        if (pct > 0)
                            damage += int32(CalculatePct(m_caster->GetTotalAttackPowerValue(BASE_ATTACK), pct));
                        break;
                    }
                    case 57755: // Heroic Throw
                    {
                        // Glyph of Heroic Throw
                        if (m_caster->HasAura(58357) && m_caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            if (Aura* aur = unitTarget->GetAura(58567, m_caster->GetGUID()))
                            {
                                if (aur->GetStackAmount() < 3)
                                    aur->SetStackAmount(aur->GetStackAmount() + 1);
                                aur->RefreshDuration();
                            }
                            else
                                m_caster->CastSpell(unitTarget, 58567, true);
                        }

                        // Throws your weapon at the enemy causing $m1 damage (based on attack power) {ap*75/100}
                        damage = int32(12 + m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.75f);
                        break;
                    }
                }
                break;
            }
            case SPELLFAMILY_PALADIN:
            {
                switch (m_spellInfo->Id)
                {
                    case 879: // Exorcism
                        if (m_caster->GetTypeId() == TYPEID_PLAYER)
                            if (m_caster->GetTotalAttackPowerValue(BASE_ATTACK) > m_caster->ToPlayer()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()))
                                damage += m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.344f;
                            else
                                damage += m_caster->ToPlayer()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()) * 0.344f;
                        break;
                    case 81297: // Consecration
                    {
                        float ap = m_caster->GetTotalAttackPowerValue(BASE_ATTACK);
                        int32 holy = m_caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_HOLY);
                        int8 divideCoeff = 10;

                        // Glyph of Consecration
                        if (m_caster->HasAura(54928))
                            divideCoeff += 2;

                        damage += (8 * (0.04f * holy + 0.04f * ap) / divideCoeff);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SPELLFAMILY_WARLOCK:
            {
                // Incinerate Rank 1 & 2
                if ((m_spellInfo->SpellFamilyFlags[1] & 0x000040) && m_spellInfo->SpellIconID == 2128)
                    // Shadow and Flame
                    if (m_caster->HasAura(17793) && roll_chance_i(33))
                        m_caster->AddAura(17800, unitTarget);
                    else if (m_caster->HasAura(17796) && roll_chance_i(66))
                        m_caster->AddAura(17800, unitTarget);
                    else if (m_caster->HasAura(17801))
                        m_caster->AddAura(17800, unitTarget);

                switch (m_spellInfo->Id)
                {
                    case 42223: // Rain of Fire
                        // Aftermath r1
                        if (m_caster->HasAura(85113) && roll_chance_i(6))
                            m_caster->CastSpell(unitTarget, 85387, true);
                        // Aftermath r2
                        else if (m_caster->HasAura(85114) && roll_chance_i(12))
                            m_caster->CastSpell(unitTarget, 85387, true);
                        break;
                    case 17962: // Conflagrate
                        // Aftermath r1
                        if (m_caster->HasAura(85113) && roll_chance_i(50))
                            m_caster->CastSpell(unitTarget, 18118, true);
                        // Aftermath r2
                        else if (m_caster->HasAura(85114))
                            m_caster->CastSpell(unitTarget, 18118, true);
                        break;
                    case 3110: // Imp's Firebolt
                        if (m_caster->isPet())
                        {
                            if (m_caster->GetOwner())
                            {
                                if (m_caster->GetCharmerOrOwner())
                                {
                                    float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_FIRE));
                                    damage += int32(1.20f * ((spellpower * 0.50f) * 0.657f));
                                }
                                if (AuraEffect* aurEff2 = m_caster->GetOwner()->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 3171, 0))
                                {
                                    float chance = aurEff2->GetAmount();
                                    if (roll_chance_f(chance))
                                        m_caster->GetOwner()->AddAura(47283, m_caster->GetOwner());
                                }
                                // Burning Embers (For Pet)
                                if (AuraEffect* aurEff = m_caster->GetOwner()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 5116, EFFECT_0))
                                {
                                    float threshold = aurEff->GetId() == 85112 ? 1.4f : 0.7f;
                                    int32 damageInPastSecs = m_caster->GetDamageDoneInPastSecs(7);
                                    int32 basePoints = int32(ApplyPct(damageInPastSecs, aurEff->GetAmount()) / 7);
                                    if (Unit* owner = m_caster->GetCharmerOrOwner())
                                    {
                                        int32 dmgThreshold = int32(owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_MAGIC) * threshold);
                                        int32 bp0 = basePoints > dmgThreshold ? dmgThreshold : basePoints;

                                        m_caster->CastCustomSpell(unitTarget, 85421, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                                    }
                                }
                            }
                        }
                        break;
                    case 3716:  // Torment
                    case 6360:  // Whiplash
                        if (m_caster->GetCharmerOrOwner())
                        {
                            float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                            damage += int32((spellpower * 0.80f) / 2);
                        }
                        break;
                    case 7814:  // Lash of Pain
                        if (m_caster->GetCharmerOrOwner())
                        {
                            float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                            damage += int32((spellpower * 0.306f));
                        }
                        break;
                    case 54049: // Shadow Bite
                        if (m_caster->GetCharmerOrOwner())
                        {
                            float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                            damage += int32((spellpower * 0.614f));
                        }
                        break;
                    case 85692: // Doom Bolt
                        if (m_caster->GetCharmerOrOwner())
                        {
                            float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                            damage += int32((spellpower * 1.2855f));
                        }
                        break;
                    case 31117: // Unstable Affliction (dispel)
                        float spellpower = (float)(m_caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW)) * 1.80f;
                        damage = int32((damage + spellpower) * 2);
                        break;
                }
                break;
            }
            case SPELLFAMILY_PRIEST:
            {
                // Improved Mind Blast (Mind Blast in shadow form bonus)
                if (m_caster->GetShapeshiftForm() == FORM_SHADOW && (m_spellInfo->SpellFamilyFlags[0] & 0x00002000))
                {
                    Unit::AuraEffectList const& ImprMindBlast = m_caster->GetAuraEffectsByType(SPELL_AURA_ADD_FLAT_MODIFIER);
                    for (Unit::AuraEffectList::const_iterator i = ImprMindBlast.begin(); i != ImprMindBlast.end(); ++i)
                        if ((*i)->GetSpellInfo()->SpellFamilyName == SPELLFAMILY_PRIEST && ((*i)->GetSpellInfo()->SpellIconID == 95))
                        {
                            int chance = (*i)->GetSpellInfo()->Effects[EFFECT_1].CalcValue(m_caster);

                            if (roll_chance_i(chance))
                                m_caster->CastSpell(unitTarget, 48301, true, 0);
                            break;
                        }
                }
                switch (m_spellInfo->Id)
                {
                    case 73510: // Mind Spike
                        // Chakra state
                        if (m_caster->HasAura(14751))
                            m_caster->CastSpell(m_caster, 81209, true);  // Chakra: Chastise

                        m_caster->RemoveAurasDueToSpell(14751);
                        break;
                    case 87532: // Shadowy Apparitions
                        if (unitTarget)
                            if (m_caster->GetCharmerOrOwner())
                            {
                                float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                                damage += int32(spellpower * 0.515f);
                            }
                        break;
                    default:
                        break;
                }
                break;
            }
            case SPELLFAMILY_DRUID:
            {
                switch (m_spellInfo->Id)
                {
                    // Sunfire
                    case 93402:
                        // If we are set to fill the solar side or we've just logged in with 0 power..
                        if ((!m_caster->HasAura(67483) && m_caster->HasAura(67484)))
                        {
                            // Lunar Shower
                            if (m_caster->HasAura(33603) || m_caster->HasAura(33604) || m_caster->HasAura(33605))
                                m_caster->EnergizeBySpell(m_caster, 89265, -8, POWER_ECLIPSE);
                            // If the energize was due to 0 power, cast the eclipse marker aura
                            if (!m_caster->HasAura(67484))
                            {
                                m_caster->RemoveAurasDueToSpell(67483);
                                m_caster->CastSpell(m_caster, 67484, true);
                            }
                        }
                        // The energizing effect brought us out of the solar eclipse, remove the aura
                        if (m_caster->HasAura(48517) && m_caster->GetPower(POWER_ECLIPSE) <= 0)
                            m_caster->RemoveAurasDueToSpell(48517);
                        break;
                    // Moonfire
                    case 8921:
                        // If we are set to fill the lunar side or we've just logged in with 0 power..
                        if (!m_caster->HasAura(67484) && m_caster->HasAura(67483))
                            // Lunar Shower
                            if (m_caster->HasAura(33603) || m_caster->HasAura(33604) || m_caster->HasAura(33605))
                                m_caster->EnergizeBySpell(m_caster, 89265, 8, POWER_ECLIPSE);
                        // The energizing effect brought us out of the solar eclipse, remove the aura
                        if (m_caster->HasAura(48518) && m_caster->GetPower(POWER_ECLIPSE) >= 0)
                            m_caster->RemoveAurasDueToSpell(48518);

                        // Shooting Stars
                        if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_DRUID, 3376, EFFECT_0))
                        {
                            int32 chance = aurEff->GetAmount();
                            if (roll_chance_f(chance))
                                m_caster->CastSpell(m_caster, 93400, true);
                        }

                        if (!m_caster->HasAura(48517) && m_caster->HasAura(93401) && m_caster->GetPower(POWER_ECLIPSE) >= 100)
                            m_caster->CastSpell(m_caster, 94338, true);
                        break;
                    case 78777: // Wild Mushroom
                        // Earth and Moon
                        if (m_caster->HasAura(48506) && unitTarget)
                            m_caster->CastSpell(unitTarget, 60433, true);
                        break;
                    case 2912: // Starfire
                        // Glyph of Starfire
                        if (m_caster->HasAura(54845))
                            if (AuraEffect const* aurEff = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DRUID, 0x00000002, 0, 0, m_caster->GetGUID()))
                            {
                                Aura* aura = aurEff->GetBase();
                                if (!aura)
                                    return;

                                uint32 countMin = aura->GetMaxDuration();
                                uint32 countMax = aura->GetSpellInfo()->GetMaxDuration() + 9000;
                                if (m_caster->HasAura(38414, m_caster->GetGUID()))
                                    countMax += 3000;
                                if (m_caster->HasAura(57865, m_caster->GetGUID()))
                                    countMax += 3000;

                                if (countMin < countMax)
                                {
                                    aura->SetDuration(uint32(aura->GetDuration() + 3000));
                                    aura->SetMaxDuration(countMin + 3000);
                                }
                            }
                        break;
                }
                break;
            }
            case SPELLFAMILY_ROGUE:
            {
                switch (m_spellInfo->Id)
                {
                    // Envenom
                    case 32645:
                    {
                        int32 rollChance = 0;
                        if (Player* player = m_caster->ToPlayer())
                        {
                            // consume from stack dozes not more that have combo-points
                            if (uint32 combo = player->GetComboPoints())
                            {
                                // Lookup for Deadly poison (only attacker applied)
                                if (AuraEffect const* aurEff = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_ROGUE, 0x00010000, 0, 0, m_caster->GetGUID()))
                                {
                                    // count consumed deadly poison doses at target
                                    bool needConsume = true;
                                    uint32 spellId = aurEff->GetId();

                                    uint32 doses = aurEff->GetBase()->GetStackAmount();
                                    if (doses > combo)
                                        doses = combo;

                                    // Master Poisoner
                                    Unit::AuraEffectList const& auraList = player->GetAuraEffectsByType(SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK);
                                    for (Unit::AuraEffectList::const_iterator iter = auraList.begin(); iter != auraList.end(); ++iter)
                                    {
                                        if ((*iter)->GetSpellInfo()->SpellFamilyName == SPELLFAMILY_ROGUE && (*iter)->GetSpellInfo()->SpellIconID == 1960)
                                        {
                                            uint32 chance = (*iter)->GetSpellInfo()->Effects[EFFECT_2].CalcValue(m_caster);
                                            if (chance && roll_chance_i(chance))
                                                needConsume = false;
                                            break;
                                        }
                                    }

                                    if (needConsume)
                                        for (uint32 i = 0; i < doses; ++i)
                                            unitTarget->RemoveAuraFromStack(spellId);

                                    damage *= doses;
                                    damage += int32(player->GetTotalAttackPowerValue(BASE_ATTACK) * 0.09f * combo);
                                }

                                // Eviscerate and Envenom Bonus Damage (item set effect)
                                if (m_caster->HasAura(37169))
                                    damage += combo * 40;

                                // Relentless Strikes Rank 1
                                if (m_caster->HasAura(14179))
                                {
                                    rollChance = 7 * combo;
                                    if (roll_chance_i(rollChance))
                                        m_caster->CastSpell(m_caster, 98440, true);
                                }
                                // Relentless Strikes Rank 2
                                else if (m_caster->HasAura(58422))
                                {
                                    rollChance = 14 * combo;
                                    if (roll_chance_i(rollChance))
                                        m_caster->CastSpell(m_caster, 98440, true);
                                }
                                // Relentless Strikes Rank 3
                                else if (m_caster->HasAura(58423))
                                {
                                    rollChance = 20 * combo;
                                    if (roll_chance_i(rollChance))
                                        m_caster->CastSpell(m_caster, 98440, true);
                                }

                                // Mastery: Potent Poisons
                                if (player->HasAura(76803))
                                {
                                    float masteryPoints = player->GetRatingBonusValue(CR_MASTERY);
                                    damage += damage * (0.28f + (0.035f * masteryPoints));
                                }
                            }
                        }
                        break;
                    }
                    // Eviscerate
                    case 2098:
                    {
                        if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            if (uint32 combo = ((Player*) m_caster)->GetComboPoints())
                            {
                                // Serrated Blades
                                if (Aura* effectRupture = unitTarget->GetAura(1943, m_caster->GetGUID()))
                                {
                                    if (AuraEffect const* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_ROGUE, 2004, EFFECT_0))
                                    {
                                        int32 chance = aurEff->GetAmount();
                                        chance *= combo;
                                        if (roll_chance_i(chance))
                                            effectRupture->RefreshDuration();
                                    }
                                }
                                float ap = m_caster->GetTotalAttackPowerValue(BASE_ATTACK);

                                if (combo)
                                    damage += int32(ap * (0.091f * combo));

                                // Eviscerate and Envenom Bonus Damage (item set effect)
                                if (m_caster->HasAura(37169))
                                    damage += combo * 40;
                            }
                        }
                        break;
                    }
                    // Instant Poisons
                    case 8680:
                    {
                        if (m_caster->GetTypeId() != TYPEID_PLAYER)
                            return;

                        // Mastery: Potent Poisons
                        if (m_caster->HasAura(76803))
                        {
                            float masteryPoints = m_caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                            damage += damage * (0.28f + (0.035f * masteryPoints));
                        }

                        if (unitTarget)
                        {
                            // Master Poisoner
                            if (unitTarget->HasAura(93068, m_caster->GetGUID()))
                                damage += damage * 0.08f;
                        }
                        break;
                    }
                }
                // Mastery: Executioner
                if (m_spellInfo->NeedsComboPoints())
                {
                    if (m_caster->HasAura(76808))
                    {
                        float masteryPoints = m_caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        damage += damage * (0.20f + (0.025f * masteryPoints));
                    }
                }
                break;
            }
            case SPELLFAMILY_HUNTER:
            {
                //Gore
                if (m_spellInfo->SpellIconID == 1578)
                {
                    if (m_caster->HasAura(57627))          // Charge 6 sec post-affect
                        damage *= 2;
                }
                switch (m_spellInfo->Id)
                {
                    case 83381: // Kill Command
                    {
                        Unit* owner = m_caster->GetOwner();
                        if (!owner)
                            return;

                        if (owner->HasAura(94006))
                            owner->RemoveAurasDueToSpell(94006);
                        if (owner->HasAura(94007))
                            owner->RemoveAurasDueToSpell(94007);

                        bool isCrit = owner->isSpellCrit(unitTarget, m_spellInfo, m_spellInfo->GetSchoolMask());
                        if (isCrit)
                            ++owner->m_kStreakCount;
                        else
                            owner->m_kStreakCount = 0;

                        if (owner->m_kStreakCount > 1)
                        {
                            if (owner->HasAura(82748)) // Killing Streak r1
                                owner->CastSpell(owner, 94006, false, 0, 0, owner->GetGUID());
                            else if (owner->HasAura(82749)) // Killing Streak r2
                                owner->CastSpell(owner, 94007, false, 0, 0, owner->GetGUID());
                            owner->m_kStreakCount = 0;
                        }

                        int32 attackPower = owner->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.516f;
                        damage += attackPower;
                        break;
                    }
                    case 17253: // Bite  (Basic Attack)
                    case 16827: // Claw  (Basic Attack)
                    case 49966: // Smack (Basic Attack)
                    {
                        if (!m_caster->GetOwner())
                            return;

                        Unit* owner = m_caster->GetOwner();
                        if (!owner)
                            return;

                        bool isCrit = m_caster->isSpellCrit(unitTarget, m_spellInfo, m_spellInfo->GetSchoolMask());

                        // Frenzy
                        if (AuraEffect* aurEff = owner->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_HUNTER, 1562, 0))
                        {
                            int32 bp0 = aurEff->GetAmount();
                            m_caster->CastCustomSpell(m_caster, 19615, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                        }

                        // Sic 'Em!
                        if (owner->HasAura(83359))
                            owner->RemoveAurasDueToSpell(83359);
                        else if (owner->HasAura(89388))
                            owner->RemoveAurasDueToSpell(89388);

                        // Cobra Strikes
                        if (owner->HasAura(53257))
                            owner->RemoveAuraFromStack(53257, owner->GetGUID());

                        if (isCrit)
                        {
                            // Invigoration
                            if (AuraEffect* aurEff = owner->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_HUNTER, 3487, 0))
                            {
                                int32 bp0 = aurEff->GetAmount();
                                owner->CastCustomSpell(owner, 53398, &bp0, NULL, NULL, true, NULL, NULL, owner->GetGUID());
                            }
                        }
                        break;
                    }
                    case 13812: // Explosive Trap
                    {
                        if (m_caster)
                            damage += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.010f;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SPELLFAMILY_DEATHKNIGHT:
            {
                switch (m_spellInfo->Id)
                {
                    case 45477: // Icy touch
                    {
                        if (!unitTarget || !m_caster)
                            return;

                        // Ebon Plaguebringer
                        if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 1766, 0))
                            m_caster->CastSpell(unitTarget, 65142, true);

                        damage += int32(m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.20f);
                        break;
                    }
                    case 45524: // Chains of Ice
                    {
                        if (!unitTarget || !m_caster)
                            return;

                        // Ebon Plaguebringer
                        if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 1766, 0))
                            m_caster->CastSpell(unitTarget, 65142, true);

                        // Glyph of Chains of Ice
                        if (m_spellInfo->Id == 45524 && m_caster->HasAura(58620))
                            m_caster->CastSpell(unitTarget, 58621, true);
                        break;
                    }
                    case 49184: // Howling Blast
                    {
                        if (!m_caster)
                            return;

                        damage += int32(m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.44f);

                        if (unitTarget->HealthBelowPct(35))
                        {
                            // Merciless Combat
                            if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 2656, 0))
                                damage += damage * aurEff->GetAmount() / 100;
                        }

                        if (m_caster->HasAura(49149)) // Chill of the Grave rank 1
                        {
                            int32 bp = 5;
                            m_caster->CastCustomSpell(m_caster, 50480, &bp, NULL, NULL, true);
                        }
                        if (m_caster->HasAura(50115)) // Chill of the Grave rank 2
                        {
                            int32 bp = 10;
                            m_caster->CastCustomSpell(m_caster, 50480, &bp, NULL, NULL, true);
                        }
                        break;
                    }
                    case 52212: // Death and Decay Damage
                        damage += int32(m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.064f);
                        break;
                    default:
                        break;
                }
                // Blood Boil - bonus for diseased targets
                if (m_spellInfo->SpellFamilyFlags[0] & 0x00040000)
                {
                    damage += CalculatePct(m_caster->GetTotalAttackPowerValue(BASE_ATTACK), 6);
                    if (unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DEATHKNIGHT, 0, 0, 0x00000002, m_caster->GetGUID()))
                        AddPct(damage, 50);
                }
                break;
            }
            case SPELLFAMILY_SHAMAN:
            {
                // Searing Bolt (Totem)
                if (m_spellInfo->Id == 3606)
                {
                    if (m_caster->GetCharmerOrOwner())
                    {
                        float spellpower = (float)(m_caster->GetCharmerOrOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_FIRE));
                        damage += int32((spellpower * 0.167f));
                    }
                }
                break;
            }
            case SPELLFAMILY_MAGE:
            {
                switch (m_spellInfo->Id)
                {
                    // Flame Orb & Fire Power explosion
                    case 82739:
                    case 83619:
                    {
                        // To prevent crashes apply this only on Orbs
                        if (!m_caster->ToTempSummon())
                            return;

                        if (Unit* owner = m_caster->GetCharmerOrOwner())
                        {
                            if (owner->GetTypeId() == TYPEID_PLAYER)
                            {
                                float spellpower = (float)(owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_FIRE));
                                if (m_caster->isSummon() && owner)
                                {
                                    switch (m_spellInfo->Id)
                                    {
                                        case 82739:
                                        {
                                            damage += spellpower * 0.134f;
                                            break;
                                        }
                                        case 83619:
                                        {
                                            damage += spellpower * 0.193f;
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }

                                // Fire Power
                                if (AuraEffect* aurEff = owner->GetAuraEffect(SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, SPELLFAMILY_MAGE, 31, 0))
                                    damage += damage * aurEff->GetAmount() / 100;

                                // Fire Specialization
                                if (AuraEffect* fireSpecialization = owner->GetAuraEffect(84668, EFFECT_0))
                                    damage += damage * fireSpecialization->GetAmount() / 100;
                            }
                        }
                        break;
                    }
                    // Frost Orb
                    case 95969:
                    case 84721:
                    {
                        // To prevent crashes apply this only on Orbs
                        if (!m_caster->ToTempSummon())
                            return;

                        if (Unit* owner = m_caster->ToTempSummon()->GetCharmerOrOwner())
                        {
                            if (owner->GetTypeId() == TYPEID_PLAYER)
                            {
                                float spellpower = (float)(owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FROST) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_FROST));
                                if (m_caster->isSummon() && owner)
                                    damage += spellpower * 0.134f;

                                // Mastery: Frostburn
                                if (owner->HasAura(76613))
                                    damage += owner->GetAura(76613)->GetEffect(EFFECT_0)->GetAmount() * damage / 100;

                                // Frost Specialization
                                if (AuraEffect* frostSpecialization = owner->GetAuraEffect(84669, EFFECT_0))
                                    damage += damage * frostSpecialization->GetAmount() / 100;
                            }
                        }
                        break;
                    }
                    // Cone of Cold
                    case 120:
                    {
                        // Improved Cone of Cold
                        if (m_caster->HasAura(11190))
                            unitTarget->CastSpell(unitTarget, 83301, true, 0, 0, m_caster->GetGUID());
                        else if (m_caster->HasAura(12489))
                            unitTarget->CastSpell(unitTarget, 83302, true, 0, 0, m_caster->GetGUID());
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
        }

        if (m_originalCaster && damage > 0 && apply_direct_bonus)
        {
            damage = m_originalCaster->SpellDamageBonusDone(unitTarget, m_spellInfo, (uint32) damage, SPELL_DIRECT_DAMAGE);
            damage = unitTarget->SpellDamageBonusTaken(m_originalCaster, m_spellInfo, (uint32) damage, SPELL_DIRECT_DAMAGE);
        }

        // Mastery: Master of Beasts
        if (m_caster->GetTypeId() == TYPEID_UNIT && m_spellInfo && damage > 0)
        {
            if (m_caster->isPet())
            {
                if (Unit* owner = m_caster->GetCharmerOrOwner())
                {
                    if (owner->HasAura(76657) && owner->GetTypeId() == TYPEID_PLAYER && owner->getClass() == CLASS_HUNTER)
                    {
                        float masteryPoints = owner->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        damage += damage * (0.13f + (0.0167f * masteryPoints));
                    }
                }
            }
        }

        // Mastery: Master Demonologist
        if (m_caster->GetCharmerOrOwner() && m_caster->GetCharmerOrOwner()->HasAura(77219) && m_caster->GetCharmerOrOwner()->GetTypeId() == TYPEID_PLAYER)
        {
            float masteryPoints = m_caster->GetCharmerOrOwner()->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
            damage += damage * (0.18f + (0.023f * masteryPoints));
        }

        m_damage += damage;
    }
}

void Spell::EffectDummy (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget && !gameObjTarget && !itemTarget)
        return;

    uint32 spell_id = 0;
    int32 bp = 0;
    bool triggered = true;
    SpellCastTargets targets;

    // selection by spell family
    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            switch (m_spellInfo->Id)
            {
                // Feral Swiftness clear effect
                case 97985:
                {
                    if (m_caster->HasAura(17002) && roll_chance_i(50))
                        m_caster->RemoveMovementImpairingAuras();
                    else if (m_caster->HasAura(24866))
                        m_caster->RemoveMovementImpairingAuras();
                    break;
                }
                // Darkshore Wisp Sparkle
                case 65127:
                {
                    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                        unitTarget->ToPlayer()->AddItem(46355, 1);
                    break;
                }
                // Protected from the Consumption
                case 65193:
                {
                    if (unitTarget->GetTypeId() != TYPEID_PLAYER && m_caster->GetTypeId() != TYPEID_PLAYER)
                    {
                        if (m_caster->ToCreature() && unitTarget->ToCreature())
                        {
                            if (unitTarget->ToCreature()->isAlive())
                            {
                                switch (unitTarget->ToCreature()->GetEntry())
                                {
                                    case 2071:  // Moonstalker Matriarch
                                    case 2165:  // Grizzled Thistle Bear
                                    case 2237:  // Moonstalker Sire
                                    case 34318: // Whitetail Stag
                                    {
                                        unitTarget->setFaction(35);
                                        unitTarget->CombatStop();
                                        unitTarget->GetMotionMaster()->MoveFleeing(m_caster, sWorld->getIntConfig(CONFIG_CREATURE_FAMILY_FLEE_DELAY));
                                        unitTarget->ToCreature()->DespawnOrUnsummon(5000);
                                        m_caster->ToCreature()->AI()->Talk(0);
                                        if (Player* player = m_caster->FindNearestPlayer(50.0f, true))
                                            player->KilledMonsterCredit(34373);
                                        break;
                                    }
                                    default:
                                        // Cast before and check then
                                        if (Unit* creatureTarget = m_caster->SelectNearbyTarget(m_caster, 25.0f))
                                            creatureTarget->CastSpell(creatureTarget, 65193, false);
                                        break;
                                }
                            }
                        }
                    }
                    break;
                }
                // Extinguish Flames
                case 65232:
                {
                    // Remove Lordly Immolate
                    if (m_caster->HasAura(65214))
                        m_caster->RemoveAurasDueToSpell(65214);
                    break;
                }
                // Create Soul Gem
                case 3660:
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (m_caster->ToPlayer()->GetQuestStatus(26305) == QUEST_STATUS_INCOMPLETE || m_caster->ToPlayer()->GetQuestStatus(592) == QUEST_STATUS_INCOMPLETE)
                            m_caster->ToPlayer()->AddItem(3913, 1);
                    }
                    break;
                }
                // Lydon/Johnny Broadcast
                case 89293:
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        // Only in Hillsbrad Foothills
                        if (m_caster->GetZoneId() != 267 && m_caster->GetAreaId() != 286)
                            return;

                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(m_caster, m_caster, 80.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(m_caster, targets, u_check);
                        m_caster->VisitNearbyObject(80.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == m_caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    // Johnny and Lyadon
                                    case 48020:
                                    case 48021:
                                        return;
                                    default:
                                        break;
                                }
                            }
                        }

                        // Summon Johnny and Lydon
                        m_caster->CastSpell(m_caster, 89295, true);
                        m_caster->CastSpell(m_caster, 89296, true);
                    }
                    break;
                }
                // Break Marl's Trance
                case 78985:
                {
                    if (!m_caster)
                        return;

                    if (Creature* marl = m_caster->FindNearestCreature(42334, 10.0f, true))
                    {
                        marl->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        marl->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                        marl->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                        marl->AI()->AttackStart(m_caster);
                        marl->RemoveAurasDueToSpell(78986);
                    }
                    break;
                }
                // Hand Grenade
                case 83108:
                {
                    if (!m_caster)
                        return;

                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // The Endless Flow
                    if (m_caster->ToPlayer()->GetQuestStatus(27161) == QUEST_STATUS_INCOMPLETE || m_caster->ToPlayer()->GetQuestStatus(26922) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (GameObject* scourgeBoneAnimus = m_caster->FindNearestGameObject(204966, 20.0f))
                            m_caster->ToPlayer()->KilledMonsterCredit(44360);
                    }
                    break;
                }
                // Call to Arms
                case 84155:
                {
                    if (!m_caster)
                        return;

                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        return;

                    if (!m_caster->GetCharmerOrOwner())
                        return;

                    if (m_caster->GetCharmerOrOwner()->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (m_caster->GetCharmerOrOwner()->ToPlayer()->GetQuestStatus(26938) == QUEST_STATUS_INCOMPLETE || m_caster->GetCharmerOrOwner()->ToPlayer()->GetQuestStatus(27089) == QUEST_STATUS_INCOMPLETE)
                        {
                            // Combat Training
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45085, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45090);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(120000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45050, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45090);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(120000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45049, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45090);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(120000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45085, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45090);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(120000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45241, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45103);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(60000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45242, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45103);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(60000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                            if (Creature* forsakenTrooper = m_caster->FindNearestCreature(45243, 30.0f, true))
                            {
                                if (forsakenTrooper->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                    return;

                                m_caster->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(45103);
                                forsakenTrooper->GetMotionMaster()->MoveFollow(m_caster, 3, m_caster->GetOrientation());
                                forsakenTrooper->DespawnOrUnsummon(60000);
                                forsakenTrooper->SetReactState(REACT_PASSIVE);
                                forsakenTrooper->SetWalk(false);
                                forsakenTrooper->MonsterSay("For the Horde!", 0);
                                forsakenTrooper->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                m_caster->CastSpell(m_caster, 57906, true);
                            }
                        }
                    }
                    break;
                }
                case 81778: // Trial of the Crypt: Set Argent Dawn Faction To Min Revered
                {
                    if (m_caster && m_caster->ToPlayer())
                        m_caster->ToPlayer()->SetReputation(529, 21000);
                    break;
                }
                case 85431: // Duskwing's Flare
                {
                    if (m_caster)
                    {
                        if (Creature* duskwing = m_caster->FindNearestCreature(11897, 50.0f, true))
                            duskwing->AI()->AttackStart(m_caster);
                    }
                    break;
                }
                case 88983: // Purifying Light
                {
                    if (m_caster && unitTarget)
                    {
                        m_caster->DealDamage(unitTarget, urand(123442, 254333));
                        m_caster->DealHeal(m_caster, m_caster->GetMaxHealth());
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            switch (m_spellInfo->Id)
            {
                case 34026: // Kill Command
                {
                    // Resistance is Futile
                    if (m_caster->HasAura(82897))
                    {
                        m_caster->CastSpell(m_caster, 86316, true);
                        m_caster->RemoveAurasDueToSpell(82897);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case SPELLFAMILY_MAGE:
        {
            switch (m_spellInfo->Id)
            {
                case 82731:          // Flame Orb
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        m_caster->CastSpell(m_caster, 84765, true);          // Summon Flame Orb
                    break;
                }
                case 92283:          // Frostfire Orb
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        m_caster->CastSpell(m_caster, 84714, true);          // Summon Frostfire Orb
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case SPELLFAMILY_PRIEST:
        {
            switch (m_spellInfo->Id)
            {
                case 527:            // Dispel
                {
                    if (m_caster->IsFriendlyTo(unitTarget))
                    {
                        int32 bp = 0;

                        if (m_caster->HasAura(33167))
                            bp = 2;
                        else
                            bp = 1;
                        m_caster->CastCustomSpell(unitTarget,15090,&bp,NULL,NULL,true);

                        // Glyph of Dispel Magic
                        if (m_caster->HasAura(55677))
                        {
                            int32 basepoints0 = int32(unitTarget->CountPctFromMaxHealth(3));
                            m_caster->CastCustomSpell(unitTarget, 56131, &basepoints0, NULL, NULL, true, NULL);
                        }
                    }
                    else
                        m_caster->CastSpell(unitTarget,15090,true);
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            switch (m_spellInfo->Id)
            {
                case 31789:          // Righteous Defense (step 1)
                {
                    // Clear targets for eff 1
                    for (std::list<TargetInfo>::iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ihit)
                        ihit->effectMask &= ~(1 << 1);

                    // not empty (checked), copy
                    Unit::AttackerSet attackers = unitTarget->getAttackers();

                    // remove invalid attackers
                    for (Unit::AttackerSet::iterator aItr = attackers.begin(); aItr != attackers.end();)
                        if (!(*aItr)->IsValidAttackTarget(m_caster))
                            attackers.erase(aItr++);
                        else
                            ++aItr;

                    // selected from list 3
                    uint32 maxTargets = std::min<uint32>(3, attackers.size());
                    for (uint32 i = 0; i < maxTargets; ++i)
                    {
                        Unit* attacker = Trinity::Containers::SelectRandomContainerElement(attackers);
                        AddUnitTarget(attacker, 1 << 1);
                        attackers.erase(attacker);
                    }

                    // now let next effect cast spell at each target.
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            switch (m_spellInfo->Id)
            {
                case 88751: // Wild Mushrooms: Detonate
                {
                    std::list<Creature*> templist;

                    CellCoord pair(Trinity::ComputeCellCoord(m_caster->GetPositionX(), m_caster->GetPositionY()));
                    Cell cell(pair);
                    cell.SetNoCreate();

                    Trinity::AllFriendlyCreaturesInGrid check(m_caster);
                    Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> searcher(m_caster, templist, check);

                    TypeContainerVisitor<Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid>, GridTypeMapContainer> cSearcher(searcher);

                    cell.Visit(pair, cSearcher, *(m_caster->GetMap()), *m_caster, m_caster->GetGridActivationRange());

                    if (!templist.empty())
                    {
                        for (std::list<Creature*>::const_iterator itr = templist.begin(); itr != templist.end(); ++itr)
                        {
                            if (!(*itr)->ToCreature())
                                continue;

                            if ((*itr)->ToCreature()->GetEntry() != 47649)
                                continue;

                            // You cannot detonate other people's mushrooms
                            if ((*itr)->GetOwner() != m_caster || !(*itr)->IsVisible())
                                continue;

                            if ((*itr)->GetOwner())
                                (*itr)->GetOwner()->CastSpell((*itr), 78777);

                            // Suicide spell
                            (*itr)->CastSpell((*itr), 92853, true);
                            (*itr)->SetDisplayId(35760);
                            (*itr)->DespawnOrUnsummon(60000);
                        }

                        templist.clear();
                    }
                    break;
                }
                case 80964: // Skull Bash
                case 80965:
                {
                    m_caster->CastSpell(unitTarget, 93983, true);
                    m_caster->CastSpell(unitTarget, 93985, true);

                    if (m_caster->HasAura(16940)) // Brutal Impact r1
                        m_caster->CastSpell(unitTarget, 82364, true);
                    else if (m_caster->HasAura(16941)) // Brutal Impact r2
                        m_caster->CastSpell(unitTarget, 82365, true);
                    break;
                }
                case 50516: // Typhoon
                {
                    if (unitTarget && unitTarget == m_caster)
                        return;
                    break;
                }
                default:
                    break;
            }
            break;
        }

        //spells triggered by dummy effect should not miss
        if (spell_id)
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell_id);

            if (!spellInfo)
            {
                sLog->outError(LOG_FILTER_SPELLS_AURAS, "EffectDummy of spell %u: triggering unknown spell id %i\n", m_spellInfo->Id, spell_id);
                return;
            }

            targets.SetUnitTarget(unitTarget);
            Spell* spell = new Spell(m_caster, spellInfo, triggered ? TRIGGERED_FULL_MASK : TRIGGERED_NONE, m_originalCasterGUID, true);
            if (bp) spell->SetSpellValue(SPELLVALUE_BASE_POINT0, bp);
            spell->prepare(&targets);
        }

        // pet auras
        if (PetAura const* petSpell = sSpellMgr->GetPetAura(m_spellInfo->Id, effIndex))
        {
            m_caster->AddPetAura(petSpell);
            return;
        }

        // normal DB scripted effect
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell ScriptStart spellid %u in EffectDummy(%u)", m_spellInfo->Id, effIndex);
        m_caster->GetMap()->ScriptsStart(sSpellScripts, uint32(m_spellInfo->Id | (effIndex << 24)), m_caster, unitTarget);

        // Script based implementation. Must be used only for not good for implementation in core spell effects
        // So called only for not proccessed cases
        if (gameObjTarget)
            sScriptMgr->OnDummyEffect(m_caster, m_spellInfo->Id, effIndex, gameObjTarget);
        else if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
            sScriptMgr->OnDummyEffect(m_caster, m_spellInfo->Id, effIndex, unitTarget->ToCreature());
        else if (itemTarget)
            sScriptMgr->OnDummyEffect(m_caster, m_spellInfo->Id, effIndex, itemTarget);
    }
}

void Spell::EffectTriggerSpell (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH_TARGET && effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH)
        return;

    uint32 triggered_spell_id = m_spellInfo->Effects[effIndex].TriggerSpell;

    // todo: move those to spell scripts
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_TRIGGER_SPELL && effectHandleMode == SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
    {
        // special cases
        switch (triggered_spell_id)
        {
            // Soulstone Resurrection
            case 6203:
            {
                if (m_caster && unitTarget && unitTarget->isDead())
                {
                    unitTarget->CastSpell(unitTarget, 3026, true);
                    return;
                }
                break;
            }
            // Vanish (not exist)
            case 18461:
            {
                unitTarget->RemoveMovementImpairingAuras();
                unitTarget->RemoveAurasByType(SPELL_AURA_MOD_STALKED);

                // If this spell is given to an NPC, it must handle the rest using its own AI
                if (unitTarget->GetTypeId() != TYPEID_PLAYER)
                    return;

                // See if we already are stealthed. If so, we're done.
                if (unitTarget->HasAura(1784))
                    return;

                // Reset cooldown on stealth if needed
                if (unitTarget->ToPlayer()->HasSpellCooldown(1784))
                    unitTarget->ToPlayer()->RemoveSpellCooldown(1784, true);
                return;
            }
            // Demonic Empowerment -- succubus
            case 54437:
            {
                unitTarget->RemoveMovementImpairingAuras();
                unitTarget->RemoveAurasByType(SPELL_AURA_MOD_STALKED);
                unitTarget->RemoveAurasByType(SPELL_AURA_MOD_STUN);

                // Cast Lesser Invisibility
                unitTarget->CastSpell(unitTarget, 7870, true);
                return;
            }
            // Brittle Armor - (need add max stack of 24575 Brittle Armor)
            case 29284:
            {
                // Brittle Armor
                SpellInfo const* spell = sSpellMgr->GetSpellInfo(24575);
                if (!spell)
                    return;

                for (uint32 j = 0; j < spell->StackAmount; ++j)
                    m_caster->CastSpell(unitTarget, spell->Id, true);
                return;
            }
            // Mercurial Shield - (need add max stack of 26464 Mercurial Shield)
            case 29286:
            {
                // Mercurial Shield
                SpellInfo const* spell = sSpellMgr->GetSpellInfo(26464);
                if (!spell)
                    return;

                for (uint32 j = 0; j < spell->StackAmount; ++j)
                    m_caster->CastSpell(unitTarget, spell->Id, true);
                return;
            }
            // Stormstrike - Main Hand
            case 32175:
            {
                if (m_caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Item* mainHand = m_caster->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
                        m_caster->CastSpell(unitTarget, triggered_spell_id);
                }
                return;
            }
            // Stormstrike - Off Hand
            case 32176:
            {
                if (m_caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Item* offHand = m_caster->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
                        m_caster->CastSpell(unitTarget, triggered_spell_id);
                }
                return;
            }
            // Cloak of Shadows
            case 35729:
            {
                uint32 dispelMask = SpellInfo::GetDispelMask(DISPEL_ALL);
                Unit::AuraApplicationMap& Auras = unitTarget->GetAppliedAuras();
                for (Unit::AuraApplicationMap::iterator iter = Auras.begin(); iter != Auras.end();)
                {
                    // remove all harmful spells on you...
                    SpellInfo const* spell = iter->second->GetBase()->GetSpellInfo();
                    if ((spell->DmgClass == SPELL_DAMAGE_CLASS_MAGIC// only affect magic spells
                        || ((spell->GetDispelMask()) & dispelMask))
                        // ignore positive and passive auras
                        && !iter->second->IsPositive() && !iter->second->GetBase()->IsPassive())
                    {
                        m_caster->RemoveAura(iter);
                    }
                    else
                        ++iter;
                }
                return;
            }
            case 20511:  // Intimidating Shout
            {
                if (!m_caster || unitTarget)
                    return;

                // Glyph of Intimidating Shout
                if (!m_caster->HasAura(63327))
                    return;
            }
        }
    }

    // normal case
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(triggered_spell_id);
    if (!spellInfo)
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell::EffectTriggerSpell spell %u tried to trigger unknown spell %u", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    SpellCastTargets targets;
    if (effectHandleMode == SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
    {
        if (!spellInfo->NeedsToBeTriggeredByCaster())
            return;
        targets.SetUnitTarget(unitTarget);
    }
    else          //if (effectHandleMode == SPELL_EFFECT_HANDLE_LAUNCH)
    {
        if (spellInfo->NeedsToBeTriggeredByCaster() && (m_spellInfo->Effects[effIndex].GetProvidedTargetMask() & TARGET_FLAG_UNIT_MASK))
            return;

        if (spellInfo->GetExplicitTargetMask() & TARGET_FLAG_DEST_LOCATION)
            targets.SetDst(m_targets);

        targets.SetUnitTarget(m_caster);
    }

    CustomSpellValues values;
    // set basepoints for trigger with value effect
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE)
    {
        // maybe need to set value only when basepoints == 0?
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, damage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, damage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT2, damage);
    }

    // Remove spell cooldown (not category) if spell triggering spell with cooldown and same category
    if (m_caster->GetTypeId() == TYPEID_PLAYER && m_spellInfo->CategoryRecoveryTime && spellInfo->CategoryRecoveryTime && m_spellInfo->Category == spellInfo->Category)
        m_caster->ToPlayer()->RemoveSpellCooldown(spellInfo->Id, true);

    // original caster guid only for GO cast
    m_caster->CastSpell(targets, spellInfo, &values, TRIGGERED_FULL_MASK, NULL, NULL, m_originalCasterGUID);
}

void Spell::EffectTriggerMissileSpell (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET && effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    uint32 triggered_spell_id = m_spellInfo->Effects[effIndex].TriggerSpell;
    // normal case
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(triggered_spell_id);
    if (!spellInfo)
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell::EffectTriggerMissileSpell spell %u tried to trigger unknown spell %u", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    SpellCastTargets targets;
    if (effectHandleMode == SPELL_EFFECT_HANDLE_HIT_TARGET)
    {
        if (!spellInfo->NeedsToBeTriggeredByCaster())
            return;
        targets.SetUnitTarget(unitTarget);
    }
    else          //if (effectHandleMode == SPELL_EFFECT_HANDLE_HIT)
    {
        if (spellInfo->NeedsToBeTriggeredByCaster() && (m_spellInfo->Effects[effIndex].GetProvidedTargetMask() & TARGET_FLAG_UNIT_MASK))
            return;

        if (spellInfo->GetExplicitTargetMask() & TARGET_FLAG_DEST_LOCATION)
            targets.SetDst(m_targets);

        if (Unit* target = m_targets.GetUnitTarget())
            targets.SetUnitTarget(target);
        else
            targets.SetUnitTarget(m_caster);
    }

    CustomSpellValues values;
    // set basepoints for trigger with value effect
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE)
    {
        // maybe need to set value only when basepoints == 0?
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, damage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, damage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT2, damage);
    }

    // Remove spell cooldown (not category) if spell triggering spell with cooldown and same category
    if (m_caster->GetTypeId() == TYPEID_PLAYER && m_spellInfo->CategoryRecoveryTime && spellInfo->CategoryRecoveryTime && m_spellInfo->Category == spellInfo->Category)
        m_caster->ToPlayer()->RemoveSpellCooldown(spellInfo->Id, true);

    // original caster guid only for GO cast
    m_caster->CastSpell(targets, spellInfo, &values, TRIGGERED_FULL_MASK, NULL, NULL, m_originalCasterGUID);
}

void Spell::EffectForceCast (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    uint32 triggered_spell_id = m_spellInfo->Effects[effIndex].TriggerSpell;

    // normal case
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(triggered_spell_id);

    if (!spellInfo)
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell::EffectForceCast of spell %u: triggering unknown spell id %i", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    // Switch with damage
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_FORCE_CAST && damage)
    {
        switch (m_spellInfo->Id)
        {
            case 52588:          // Skeletal Gryphon Escape
            case 48598:          // Ride Flamebringer Cue
                unitTarget->RemoveAura(damage);
                break;
            case 52463:          // Hide In Mine Car
            case 52349:          // Overtake
                unitTarget->CastCustomSpell(unitTarget, spellInfo->Id, &damage, NULL, NULL, true, NULL, NULL, m_originalCasterGUID);
                return;
        }
    }

    CustomSpellValues values;
    // set basepoints for trigger with value effect
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_FORCE_CAST_WITH_VALUE)
    {
        // maybe need to set value only when basepoints == 0?
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, damage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, damage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT2, damage);
    }

    SpellCastTargets targets;
    targets.SetUnitTarget(m_caster);

    unitTarget->CastSpell(targets, spellInfo, &values, TRIGGERED_FULL_MASK);
}

void Spell::EffectTriggerRitualOfSummoning (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    uint32 triggered_spell_id = m_spellInfo->Effects[effIndex].TriggerSpell;
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(triggered_spell_id);

    if (!spellInfo)
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "EffectTriggerRitualOfSummoning of spell %u: triggering unknown spell id %i", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    finish();

    m_caster->CastSpell((Unit*) NULL, spellInfo, false);
}

void Spell::EffectJump (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
        return;

    if (m_caster->isInFlight())
        return;

    if (!unitTarget)
        return;

    float x, y, z;
    unitTarget->GetContactPoint(m_caster, x, y, z, CONTACT_DISTANCE);

    float speedXY, speedZ;
    CalculateJumpSpeeds(effIndex, m_caster->GetExactDist2d(x, y), speedXY, speedZ);
    m_caster->GetMotionMaster()->MoveJump(x, y, z, speedXY, speedZ);
}

void Spell::EffectJumpDest (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH)
        return;

    if (m_caster->isInFlight())
        return;

    if (!m_targets.HasDst())
        return;

    // Init dest coordinates
    float x, y, z;
    destTarget->GetPosition(x, y, z);

    float speedXY, speedZ;
    CalculateJumpSpeeds(effIndex, m_caster->GetExactDist2d(x, y), speedXY, speedZ);
    m_caster->GetMotionMaster()->MoveJump(x, y, z, speedXY, speedZ);
}

void Spell::CalculateJumpSpeeds (uint8 i, float dist, float & speedXY, float & speedZ)
{
    if (m_spellInfo->Effects[i].MiscValue)
        speedZ = float(m_spellInfo->Effects[i].MiscValue) / 10;
    else if (m_spellInfo->Effects[i].MiscValueB)
        speedZ = float(m_spellInfo->Effects[i].MiscValueB) / 10;
    else
        speedZ = 10.0f;
    speedXY = dist * 10.0f / speedZ;
}

void Spell::EffectTeleportUnits (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->isInFlight())
        return;

    // Pre effects
    switch (m_spellInfo->Id)
    {
        case 66550: // Teleports Outside (Isle of Conquest)
        {
            if (Player* target = unitTarget->ToPlayer())
            {
                if (target->GetTeamId() == TEAM_ALLIANCE)
                    m_targets.SetDst(442.24f, -835.25f, 44.30f, 0.06f, 628);
                else
                    m_targets.SetDst(1120.43f, -762.11f, 47.92f, 2.94f, 628);
            }
            break;
        }
        case 66551:          // teleports inside (Isle of Conquest)
        {
            if (Player* target = unitTarget->ToPlayer())
            {
                if (target->GetTeamId() == TEAM_ALLIANCE)
                    m_targets.SetDst(389.57f, -832.38f, 48.65f, 3.00f, 628);
                else
                    m_targets.SetDst(1174.85f, -763.24f, 48.72f, 6.26f, 628);
            }
            break;
        }
        default:
            break;
    }

    // If not exist data for dest location - return
    if (!m_targets.HasDst())
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell::EffectTeleportUnits - does not have destination for spellId %u.", m_spellInfo->Id);
        return;
    }

    // Init dest coordinates
    uint32 mapid = destTarget->GetMapId();
    if (mapid == MAPID_INVALID)
        mapid = unitTarget->GetMapId();
    float x, y, z, orientation;
    destTarget->GetPosition(x, y, z, orientation);
    if (!orientation && m_targets.GetUnitTarget())
        orientation = m_targets.GetUnitTarget()->GetOrientation();
    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell::EffectTeleportUnits - teleport unit to %u %f %f %f %f\n", mapid, x, y, z, orientation);

    if (mapid == unitTarget->GetMapId())
        unitTarget->NearTeleportTo(x, y, z, orientation, unitTarget == m_caster);
    else if (unitTarget->GetTypeId() == TYPEID_PLAYER)
        unitTarget->ToPlayer()->TeleportTo(mapid, x, y, z, orientation, unitTarget == m_caster ? TELE_TO_SPELL : 0);

    // post effects for TARGET_DEST_DB
    switch (m_spellInfo->Id)
    {
        // Dimensional Ripper - Everlook
        case 23442:
        {
            int32 r = irand(0, 119);
            if (r >= 70)          // 7/12 success
            {
                if (r < 100)          // 4/12 evil twin
                    m_caster->CastSpell(m_caster, 23445, true);
                else
                    // 1/12 fire
                    m_caster->CastSpell(m_caster, 23449, true);
            }
            return;
        }
        // Ultrasafe Transporter: Toshley's Station
        case 36941:
        {
            if (roll_chance_i(50))          // 50% success
            {
                int32 rand_eff = urand(1, 7);
                switch (rand_eff)
                {
                    case 1:
                        // soul split - evil
                        m_caster->CastSpell(m_caster, 36900, true);
                        break;
                    case 2:
                        // soul split - good
                        m_caster->CastSpell(m_caster, 36901, true);
                        break;
                    case 3:
                        // Increase the size
                        m_caster->CastSpell(m_caster, 36895, true);
                        break;
                    case 4:
                        // Decrease the size
                        m_caster->CastSpell(m_caster, 36893, true);
                        break;
                    case 5:
                    // Transform
                    {
                        if (m_caster->ToPlayer()->GetTeam() == ALLIANCE)
                            m_caster->CastSpell(m_caster, 36897, true);
                        else
                            m_caster->CastSpell(m_caster, 36899, true);
                        break;
                    }
                    case 6:
                        // chicken
                        m_caster->CastSpell(m_caster, 36940, true);
                        break;
                    case 7:
                        // evil twin
                        m_caster->CastSpell(m_caster, 23445, true);
                        break;
                }
            }
            return;
        }
        // Dimensional Ripper - Area 52
        case 36890:
        {
            if (roll_chance_i(50))          // 50% success
            {
                int32 rand_eff = urand(1, 4);
                switch (rand_eff)
                {
                    case 1:
                        // soul split - evil
                        m_caster->CastSpell(m_caster, 36900, true);
                        break;
                    case 2:
                        // soul split - good
                        m_caster->CastSpell(m_caster, 36901, true);
                        break;
                    case 3:
                        // Increase the size
                        m_caster->CastSpell(m_caster, 36895, true);
                        break;
                    case 4:     // Transform
                    {
                        if (m_caster->ToPlayer()->GetTeam() == ALLIANCE)
                            m_caster->CastSpell(m_caster, 36897, true);
                        else
                            m_caster->CastSpell(m_caster, 36899, true);
                        break;
                    }
                }
            }
            return;
        }
    }
}

void Spell::EffectApplyAura (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!m_spellAura || !unitTarget)
        return;

    ASSERT(unitTarget == m_spellAura->GetOwner());

    m_spellAura->_ApplyEffectForTargets(effIndex);

    switch (m_spellInfo->GetEffectMechanic(effIndex))
    {
        case MECHANIC_STUN:
        case MECHANIC_ROOT:
        case MECHANIC_FEAR:
        {
            if (unitTarget)
                if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                    if (!unitTarget->ToPlayer()->HasSpellCooldown(89024))
                    {
                        if (unitTarget->HasAura(26022) && roll_chance_f(0.5f))
                        {
                            unitTarget->CastSpell(unitTarget, 89024, true);
                            unitTarget->ToPlayer()->AddSpellCooldown(89024, 0, time(NULL) + 1);
                        }
                        if (unitTarget->HasAura(26023))
                        {
                            unitTarget->CastSpell(unitTarget, 89024, true);
                            unitTarget->ToPlayer()->AddSpellCooldown(89024, 0, time(NULL) + 1);
                        }
                    }
            break;
        }
    }

    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            // Food buffs cannot stack!
            if (m_spellInfo->AttributesEx2 & SPELL_ATTR2_FOOD_BUFF)
                m_caster->RemoveFoodBuffAurasWithExclusion(m_spellInfo->Id);

            switch (m_spellAura->GetId())
            {
                case 77487: // Shadow Orb
                {
                    // Shadow Orbs!
                    if (m_spellAura->GetStackAmount() >= 3 && !m_caster->HasAura(93683))
                        m_caster->AddAura(93683, m_caster);
                    break;
                }
                case 87606: // Gragal's Mighty Shout
                case 87274: // Olaf's Mighty Shout
                {
                    if (Vehicle* vehicle = m_caster->GetVehicleKit())
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                player->KilledMonsterCredit(46867);
                    break;
                }
                case 87607: // Gragal's Shield Wall
                case 87275: // Olaf's Shield Wall
                {
                    if (Vehicle* vehicle = m_caster->GetVehicleKit())
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                player->KilledMonsterCredit(46866);
                    break;
                }
                case 87609: // Amakkar's Pocket Potion
                case 87279: // Eric's Pocket Potion
                {
                    if (Vehicle* vehicle = m_caster->GetVehicleKit())
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                player->KilledMonsterCredit(46863);
                    break;
                }
                case 87596: // Jurrix's Time Warp
                case 87277: // Baelog's Warcry
                {
                    if (Vehicle* vehicle = m_caster->GetVehicleKit())
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                            if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                player->KilledMonsterCredit(46864);
                    break;
                }
                case 76406: // Water Jet
                {
                    uint32 healthDmg = unitTarget->GetMaxHealth() * 0.35f;
                    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
                    {
                        if (unitTarget->ToCreature()->GetEntry() == 40845)
                            unitTarget->DealDamage(unitTarget, healthDmg);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            switch (m_spellInfo->Id)
            {
                case 48517: // Eclipse (Solar)
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        break;

                    if (m_caster->solarEnabled == true)
                        break;

                    // Euphoria (Mana gain)
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 4431, 2))
                    {
                        int32 amount = aurEff->GetAmount();
                        int32 maxMana = m_caster->GetMaxPower(POWER_MANA);
                        int32 dmg = amount * maxMana / 100;
                        m_caster->EnergizeBySpell(m_caster, 81069, dmg, POWER_MANA);
                    }

                    // Item - Druid T11 Balance 4P Bonus
                    if (m_caster->HasAura(90163) && !m_caster->HasAura(90164))
                    {
                        m_caster->CastSpell(m_caster, 90164, true);
                        if (Aura* aur = m_caster->GetAura(90164, m_caster->GetGUID()))
                            aur->SetStackAmount(3);
                    }

                    // Nature's Grace
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        m_caster->ToPlayer()->RemoveSpellCooldown(16886);

                    // Sunfire
                    if (AuraEffect* aura = m_caster->GetDummyAuraEffect(SPELLFAMILY_DRUID, 3262, 0))
                        m_caster->CastSpell(m_caster, 94338, true);

                    m_caster->solarEnabled = true;
                    m_caster->lunarEnabled = false;
                    break;
                }
                case 48518: // Eclipse (Lunar)
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        break;

                    if (m_caster->lunarEnabled == true)
                        break;

                    // Euphoria (Mana gain)
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 4431, 2))
                    {
                        int32 amount = aurEff->GetAmount();
                        int32 maxMana = m_caster->GetMaxPower(POWER_MANA);
                        int32 dmg = amount * maxMana / 100;
                        m_caster->EnergizeBySpell(m_caster, 81069, dmg, POWER_MANA);
                    }

                    // Item - Druid T11 Balance 4P Bonus
                    if (m_caster->HasAura(90163) && !m_caster->HasAura(90164))
                    {
                        m_caster->CastSpell(m_caster, 90164, true);
                        if (Aura* aur = m_caster->GetAura(90164, m_caster->GetGUID()))
                            aur->SetStackAmount(3);
                    }

                    // Nature's Grace
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        m_caster->ToPlayer()->RemoveSpellCooldown(16886);

                    m_caster->solarEnabled = false;
                    m_caster->lunarEnabled = true;
                    break;
                }
                case 33763: // Lifebloom
                case 94447: // Lifebloom (Tree of Life)
                {
                    // Revitalize add Replenishment effect
                    if (m_caster->HasAura(48539) || m_caster->HasAura(48544))
                        m_caster->CastSpell(m_caster, 57669, true);
                    break;
                }
                case 93622: // Berserk
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        // Mangle reset cooldowns
                        if (m_caster->ToPlayer()->HasSpellCooldown(33878))
                            m_caster->ToPlayer()->RemoveSpellCooldown(33878, true);
                    }
                    break;
                }
                case 1850:  // Dash
                case 77761: // Stampeding Roar (Bear)
                case 77764: // Stampeding Roar (Cat)
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (m_caster->HasSpell(17002) && roll_chance_i(50))
                        {
                            m_caster->RemoveMovementImpairingAuras();
                            if (unitTarget)
                                unitTarget->RemoveMovementImpairingAuras();
                        }
                        if (m_caster->HasSpell(24866))
                        {
                            m_caster->RemoveMovementImpairingAuras();
                            if (unitTarget)
                                unitTarget->RemoveMovementImpairingAuras();
                        }
                    }
                    break;
                }
                case 9005: // Pounce
                {
                    if (!m_caster)
                        break;

                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (unitTarget)
                        {
                            // Brutal Impact - Increase Pounce duration
                            if (Aura* pounce = unitTarget->GetAura(9005, m_caster->GetGUID()))
                            {
                                if (m_caster->HasAura(16940))
                                {
                                    pounce->SetMaxDuration(pounce->GetMaxDuration()+500);
                                    pounce->SetDuration(pounce->GetDuration()+500);
                                }
                                else if (m_caster->HasAura(16941))
                                {
                                    pounce->SetMaxDuration(pounce->GetMaxDuration()+1000);
                                    pounce->SetDuration(pounce->GetDuration()+1000);
                                }
                            }
                        }
                    }
                    break;
                }
                case 8921:  // Moonfire
                {
                    if (!m_caster)
                        break;

                    if (unitTarget)
                    {
                        if (Aura* sunfire = unitTarget->GetAura(93402, m_caster->GetGUID()))
                            sunfire->Remove(AURA_REMOVE_BY_CANCEL);
                    }
                    break;
                }
                case 93402:  // Sunfire
                {
                    if (!m_caster)
                        break;

                    if (unitTarget)
                    {
                        if (Aura* moonfire = unitTarget->GetAura(8921, m_caster->GetGUID()))
                            moonfire->Remove(AURA_REMOVE_BY_CANCEL);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_MAGE:
        {
            switch (m_spellInfo->Id)
            {
                case 12472: // Icy Veins
                {
                    // Glyph of Icy Veins
                    if (m_caster->HasAura(56374))
                    {
                        // Remove slow effects and cast slow effects!
                        m_caster->RemoveAurasByType(SPELL_AURA_HASTE_SPELLS, 0, 0, true, false);
                        m_caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
                    }
                    break;
                }
                case 32612: // Invisibility
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        // Glyph of Invisibility
                        if (m_caster->HasAura(56366))
                            m_caster->CastSpell(m_caster, 87833, true); // Increase movement speed by 40%
                    }
                    break;
                }
                case 118: // Polymorph
                {
                    if (!unitTarget || !m_caster)
                        return;

                    // Glyph of Polymorph
                    if (m_caster->HasAura(56375))
                    {
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409));
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            switch (m_spellInfo->Id)
            {
                case 498: // Divine Protection
                {
                    // Speed of Light
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 5062, 1))
                    {
                        int32 bp = aurEff->GetAmount();
                        m_caster->CastCustomSpell(unitTarget, 85497, &bp, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                    }
                    break;
                }
                case 31884: // Avenging Wrath
                {
                    // Sanctified Wrath
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_PALADIN, 3029, 0))
                        m_caster->CastSpell(m_caster, 57318, true);
                    break;
                }
                case 85416: // Grand Crusader
                {
                    // Reset Avenger's Shield cooldown
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (m_caster->ToPlayer()->HasSpellCooldown(31935))
                            m_caster->ToPlayer()->RemoveSpellCooldown(31935, true);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            switch (m_spellInfo->Id)
            {
                case 53257: // Cobra Strikes
                {
                    m_caster->AddAura(53257, m_caster);
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_DEATHKNIGHT:
        {
            switch (m_spellInfo->Id)
            {
                case 45524: // Chains of Ice
                {
                    if (unitTarget)
                    {
                        if (m_caster->HasAura(50040)) // Chilblains r1
                            m_caster->CastSpell(unitTarget, 96293, true);
                        else if (m_caster->HasAura(50041)) // Chilblains r2
                            m_caster->CastSpell(unitTarget, 96294, true);
                    }
                    break;
                }
                case 51124: // Killing Machine
                {
                    // Item - Death Knight T11 DPS 4P Bonus
                    if (m_caster->HasAura(90459))
                        m_caster->CastSpell(m_caster, 90507, true);
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_ROGUE:
        {
            switch (m_spellInfo->Dispel)
            {
                case DISPEL_POISON:
                {
                    // Avoid to apply poisons or Savage Combat on caster
                    if (m_caster != unitTarget)
                    {
                        // Savage Combat r1
                        if (AuraEffect* savageCombat = m_caster->GetAuraEffect(51682, EFFECT_0))
                            m_caster->CastSpell(unitTarget, 58684, true, NULL, savageCombat);
                        // Savage Combat r2
                        if (AuraEffect* savageCombat = m_caster->GetAuraEffect(58413, EFFECT_0))
                            m_caster->CastSpell(unitTarget, 58683, true, NULL, savageCombat);
                        // Master Poisoner
                        if (AuraEffect* masterPoisoner = m_caster->GetAuraEffect(58410, EFFECT_0))
                            m_caster->CastSpell(unitTarget, 93068, true, NULL, masterPoisoner);
                    }
                    break;
                }
            }
            switch (m_spellInfo->Id)
            {
                case 1784: // Stealth
                {
                    // Overkill
                    if (m_caster->HasAura(58426))
                        m_caster->AddAura(58427, m_caster);
                    break;
                }
                case 2094: // Blind
                {
                    // Glyph of Blind
                    if (m_caster->HasAura(91299))
                    {
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409));
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                    }
                    break;
                }
                case 84590: // Deadly Momentum
                {
                    if (Aura* sliceAndDice = unitTarget->GetAura(5171))
                        sliceAndDice->SetDuration(sliceAndDice->GetMaxDuration());
                    if (Aura* recuperate = unitTarget->GetAura(73651))
                        recuperate->SetDuration(recuperate->GetMaxDuration());
                    break;
                }
                case 84601: // Assassin's Resolve
                {
                    if (m_caster)
                    {
                        m_caster->ModifyAurOnWeaponChange(BASE_ATTACK, true);
                        m_caster->ModifyAurOnWeaponChange(OFF_ATTACK, true);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            switch (m_spellInfo->Id)
            {
                case 6358: // Seduction
                {
                    if (!unitTarget || !m_caster)
                        return;

                    // Glyph of Seduction
                    if (m_caster->GetOwner() && m_caster->GetOwner()->HasAura(56250))
                    {
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409));
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_PRIEST:
        {
            switch (m_spellInfo->Id)
            {
                case 17: // Power Word: Shield
                {
                    // PvP Set Effect (Holy Walk)
                    if (m_caster->HasAura(33333) && unitTarget == m_caster)
                        m_caster->CastSpell(m_caster, 96219, true);
                    break;
                }
                case 41635: // Prayer of Mending
                {
                    // Chakra: Sanctuary
                    if (m_caster && m_caster->HasAura(14751, m_caster->GetGUID()))
                    {
                        m_caster->CastSpell(m_caster, 81206, true);
                        m_caster->RemoveAurasDueToSpell(14751);
                    }
                    break;
                }
            }
            switch (m_spellAura->GetId())
            {
                case 81660: // Evangelism r1
                case 81661: // Evangelism r2
                case 87117: // Dark Evangelism r1
                case 87118: // Dark Evangelism r2
                {
                    // Archangel!
                    if (m_spellAura->GetStackAmount() >= 5 && !m_caster->HasAura(94709))
                        m_caster->AddAura(94709, m_caster);
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_WARRIOR:
        {
            switch (m_spellInfo->Id)
            {
                case 18499: // Berserker Rage
                {
                    // Glyph of Berserker Rage
                    if (m_caster->HasAura(58096) && m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (!m_caster->ToPlayer()->HasSpellCooldown(23690))
                        {
                            m_caster->CastSpell(m_caster, 23690, true);
                            m_caster->ToPlayer()->AddSpellCooldown(23690, 0, time(NULL) + 1);
                        }
                    }
                    break;
                }
                case 86346: // Colossus Smash
                {
                    // Glyph of Colossus Smash
                    if (m_caster->HasAura(89003) && m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (Aura* aur = unitTarget->GetAura(58567, m_caster->GetGUID()))
                        {
                            if (aur->GetStackAmount() < 3)
                                aur->SetStackAmount(aur->GetStackAmount() + 1);
                            aur->RefreshDuration();
                        }
                        else
                            m_caster->CastSpell(unitTarget, 7386, true);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_POTION:
        {
            switch (m_spellInfo->Id)
            {
                case 79469: // Flask of Steelskin
                case 79472: // Flask of Titanic Strength
                case 79471: // Flask of the Winds
                case 94160: // Flask of Flowing Water
                case 79470: // Flask of the Draconic Mind
                {
                    // Chug-A-Lug
                    if (Aura* cauldronFlask = m_caster->GetAura(m_spellInfo->Id, m_caster->GetGUID()))
                    {
                        if (m_caster->HasAura(83961))       // Rank 2
                            cauldronFlask->SetDuration(cauldronFlask->GetDuration() * 2);
                        else if (m_caster->HasAura(83945))  // Rank 1
                            cauldronFlask->SetDuration(cauldronFlask->GetDuration() + (cauldronFlask->GetDuration() * 0.50f));
                    }
                }
                default:
                    break;
            }
            break;
        }
    }
}

void Spell::EffectApplyAreaAura (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!m_spellAura || !unitTarget)
        return;

    ASSERT (unitTarget == m_spellAura->GetOwner());
    m_spellAura->_ApplyEffectForTargets(effIndex);
}

void Spell::EffectUnlearnSpecialization (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = unitTarget->ToPlayer();
    uint32 spellToUnlearn = m_spellInfo->Effects[effIndex].TriggerSpell;

    player->removeSpell(spellToUnlearn);

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell: Player %u has unlearned spell %u from NpcGUID: %u", player->GetGUIDLow(), spellToUnlearn, m_caster->GetGUIDLow());
}

void Spell::EffectPowerDrain (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_spellInfo->Effects[effIndex].MiscValue < 0 || m_spellInfo->Effects[effIndex].MiscValue >= int8(MAX_POWERS))
        return;

    Powers powerType = Powers(m_spellInfo->Effects[effIndex].MiscValue);

    if (!unitTarget || !unitTarget->isAlive() || unitTarget->getPowerType() != powerType || damage < 0)
        return;

    // add spell damage bonus
    damage = m_caster->SpellDamageBonusDone(unitTarget, m_spellInfo, uint32(damage), SPELL_DIRECT_DAMAGE);
    damage = unitTarget->SpellDamageBonusTaken(m_caster, m_spellInfo, uint32(damage), SPELL_DIRECT_DAMAGE);

    int32 newDamage = -(unitTarget->ModifyPower(powerType, -damage));

    float gainMultiplier = 0.0f;

    // Don't restore from self drain
    if (m_caster != unitTarget)
    {
        gainMultiplier = m_spellInfo->Effects[effIndex].CalcValueMultiplier(m_originalCaster, this);

        int32 gain = int32(newDamage * gainMultiplier);

        m_caster->EnergizeBySpell(m_caster, m_spellInfo->Id, gain, powerType);
    }
    ExecuteLogEffectTakeTargetPower(effIndex, unitTarget, powerType, newDamage, gainMultiplier);
}

void Spell::EffectSendEvent (SpellEffIndex effIndex)
{
    // we do not handle a flag dropping or clicking on flag in battleground by sendevent system
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET && effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    WorldObject* target = NULL;

    // call events for object target if present
    if (effectHandleMode == SPELL_EFFECT_HANDLE_HIT_TARGET)
    {
        if (unitTarget)
            target = unitTarget;
        else if (gameObjTarget)
            target = gameObjTarget;
    }
    else          // if (effectHandleMode == SPELL_EFFECT_HANDLE_HIT)
    {
        // let's prevent executing effect handler twice in case when spell effect is capable of targeting an object
        // this check was requested by scripters, but it has some downsides:
        // now it's impossible to script (using sEventScripts) a cast which misses all targets
        // or to have an ability to script the moment spell hits dest (in a case when there are object targets present)
        if (m_spellInfo->Effects[effIndex].GetProvidedTargetMask() & (TARGET_FLAG_UNIT_MASK | TARGET_FLAG_GAMEOBJECT_MASK))
            return;
        // some spells have no target entries in dbc and they use focus target
        if (focusObject)
            target = focusObject;
        // TODO: there should be a possibility to pass dest target to event script
    }

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell ScriptStart %u for spellid %u in EffectSendEvent ", m_spellInfo->Effects[effIndex].MiscValue, m_spellInfo->Id);

    if (ZoneScript* zoneScript = m_caster->GetZoneScript())
        zoneScript->ProcessEvent(target, m_spellInfo->Effects[effIndex].MiscValue);
    else if (InstanceScript* instanceScript = m_caster->GetInstanceScript())          // needed in case Player is the caster
        instanceScript->ProcessEvent(target, m_spellInfo->Effects[effIndex].MiscValue);

    m_caster->GetMap()->ScriptsStart(sEventScripts, m_spellInfo->Effects[effIndex].MiscValue, m_caster, target);
}

void Spell::EffectPowerBurn (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_spellInfo->Effects[effIndex].MiscValue < 0 || m_spellInfo->Effects[effIndex].MiscValue >= int8(MAX_POWERS))
        return;

    Powers powerType = Powers(m_spellInfo->Effects[effIndex].MiscValue);

    if (!unitTarget || !unitTarget->isAlive() || unitTarget->getPowerType() != powerType || damage < 0)
        return;

    // burn x% of target's mana, up to maximum of 2x% of caster's mana (Mana Burn)
    if (m_spellInfo->Id == 8129)
    {
        int32 maxDamage = int32(CalculatePct(m_caster->GetMaxPower(powerType), damage * 2));
        damage = int32(CalculatePct(unitTarget->GetMaxPower(powerType), damage));
        damage = std::min(damage, maxDamage);
    }

    int32 newDamage = -(unitTarget->ModifyPower(powerType, -damage));

    // NO - Not a typo - EffectPowerBurn uses effect value multiplier - not effect damage multiplier
    float dmgMultiplier = m_spellInfo->Effects[effIndex].CalcValueMultiplier(m_originalCaster, this);

    // add log data before multiplication (need power amount, not damage)
    ExecuteLogEffectTakeTargetPower(effIndex, unitTarget, powerType, newDamage, 0.0f);

    newDamage = int32(newDamage * dmgMultiplier);

    m_damage += newDamage;
}

void Spell::EffectHeal (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
        return;

    if (unitTarget && unitTarget->isAlive() && damage >= 0)
    {
        // Try to get original caster
        Unit* caster = m_originalCasterGUID ? m_originalCaster : m_caster;

        // Skip if m_originalCaster not available
        if (!caster)
            return;

        int32 addhealth = damage;

        // Vessel of the Naaru (Vial of the Sunwell trinket)
        if (m_spellInfo->Id == 45064)
        {
            // Amount of heal - depends from stacked Holy Energy
            int damageAmount = 0;
            if (AuraEffect const* aurEff = m_caster->GetAuraEffect(45062, 0))
            {
                damageAmount += aurEff->GetAmount();
                m_caster->RemoveAurasDueToSpell(45062);
            }

            addhealth += damageAmount;
        }
        // Runic Healing Injector (heal increased by 25% for engineers - 3.2.0 patch change)
        else if (m_spellInfo->Id == 67489)
        {
            if (Player* player = m_caster->ToPlayer())
                if (player->HasSkill(SKILL_ENGINEERING))
                    AddPct(addhealth, 25);
        }
        // Swiftmend - consumes Regrowth or Rejuvenation
        else if (m_spellInfo->TargetAuraState == AURA_STATE_SWIFTMEND && unitTarget->HasAuraState(AURA_STATE_SWIFTMEND, m_spellInfo, m_caster))
        {
            Unit::AuraEffectList const& RejorRegr = unitTarget->GetAuraEffectsByType(SPELL_AURA_PERIODIC_HEAL);
            // find most short by duration
            AuraEffect* targetAura = NULL;
            for (Unit::AuraEffectList::const_iterator i = RejorRegr.begin(); i != RejorRegr.end(); ++i)
            {
                if ((*i)->GetSpellInfo()->SpellFamilyName == SPELLFAMILY_DRUID && (*i)->GetSpellInfo()->SpellFamilyFlags[0] & 0x50)
                {
                    if (!targetAura || (*i)->GetBase()->GetDuration() < targetAura->GetBase()->GetDuration())
                        targetAura = *i;
                }
            }

            if (!targetAura)
            {
                sLog->outError(LOG_FILTER_SPELLS_AURAS, "Target(GUID:" UI64FMTD ") has aurastate AURA_STATE_SWIFTMEND but no matching aura.", unitTarget->GetGUID());
                return;
            }

            // Glyph of Swiftmend
            if (!caster->HasAura(54824))
                unitTarget->RemoveAura(targetAura->GetId(), targetAura->GetCasterGUID());

            addhealth = caster->SpellHealingBonusDone(unitTarget, m_spellInfo, addhealth, HEAL);
        }
        // Bloodworms heal
        else if (m_spellInfo->Id == 81280)
            addhealth += damage * unitTarget->GetMaxHealth() / 100;
        // Death Pact - return pct of max health to caster
        else if (m_spellInfo->SpellFamilyName == SPELLFAMILY_DEATHKNIGHT && m_spellInfo->SpellFamilyFlags[0] & 0x00080000)
            addhealth = caster->SpellHealingBonusDone(unitTarget, m_spellInfo, int32(caster->CountPctFromMaxHealth(damage)), HEAL);
        else
            addhealth = caster->SpellHealingBonusDone(unitTarget, m_spellInfo, addhealth, HEAL);

        addhealth = unitTarget->SpellHealingBonusTaken(caster, m_spellInfo, addhealth, HEAL);

        // Remove Grievious bite if fully healed
        if (unitTarget->HasAura(48920) && (unitTarget->GetHealth() + addhealth >= unitTarget->GetMaxHealth()))
            unitTarget->RemoveAura(48920);

        // Init switch for special spell procs
        switch (m_spellInfo->Id)
        {
            case 61295: // Riptide
            {
                // Only Direct Heal
                if (m_spellInfo->IsPeriodicDamage())
                    break;

                // Nature's Blessing
                if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, 2012, EFFECT_0))
                {
                    // Earth Shield
                    if (unitTarget && unitTarget->HasAura(974))
                    {
                        int32 healAmount = aurEff->GetAmount();
                        addhealth += (addhealth * healAmount) / 100;
                    }
                }
                break;
            }
            case 20167: // Seal of Insight
            {
                int32 ap = caster->ToPlayer()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.155f;
                addhealth += ap;
                break;
            }
            case 87188: // Enlightened Judgements
            case 87189:
            {
                int32 incrementalHeal = 0;

                // Walk in the Light
                if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_ADD_PCT_MODIFIER, SPELLFAMILY_PALADIN, 1946, 1))
                    incrementalHeal = CalculatePct(addhealth, aurEff->GetAmount());

                addhealth += incrementalHeal;
                break;
            }
            case 34299: // Leader of the Pack
            {
                int32 maxHealth = caster->GetMaxHealth() * 0.04f;
                addhealth = maxHealth;
                break;
            }
            case 19750: // Flash of Light
            case 82326: // Divine Light
            {
                // Tower of Radiance
                if (caster->HasAura(84800) || caster->HasAura(85511) || caster->HasAura(85512))
                {
                    // Cast only if target is Beacon
                    if (unitTarget && unitTarget->HasAura(53563))
                        caster->CastSpell(caster, 88852, true);
                }
                break;
            }
            case 81269: // Efflorescence
            {
                addhealth += addhealth;
                break;
            }
            case 5185:  // Healing Touch
            case 8936:  // Regrowth
            case 18562: // Swiftmend
            case 50464: // Nourish
            {
                // Only for player casters
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    break;

                // Need Mastery
                if (!caster->HasAura(86470))
                    break;

                // Increase direct healing by 10% and 1.25% bonus per mastery points
                float masteryPoints = caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                addhealth += addhealth * (0.10f + (0.0125f * masteryPoints));

                // Mastery: Harmony
                if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 1929, 1))
                {
                    int32 bp0 = aurEff->GetAmount();
                    m_caster->CastCustomSpell(m_caster, 100977, &bp0, NULL, NULL, true, NULL, NULL, caster->GetGUID());
                }
                break;
            }
            case 32546: // Binding Heal
            {
                if (m_caster && m_caster->HasAura(14751, m_caster->GetGUID()))
                {
                    m_caster->CastSpell(m_caster, 81208, true);
                    m_caster->RemoveAurasDueToSpell(14751);
                }
                break;
            }
        }

        // Nature's Blessing (Only for direct heal spells)
        if (m_caster->GetTypeId() == TYPEID_PLAYER && m_caster->getClass() == CLASS_SHAMAN && m_spellInfo->AttributesEx8 == SPELL_ATTR8_HEALING_SPELL)
        {
            if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, 2012, EFFECT_0))
            {
                // Earth Shield
                if (unitTarget && unitTarget->HasAura(974))
                {
                    int32 healAmount = aurEff->GetAmount();
                    addhealth += (addhealth * healAmount) / 100;
                }
            }
        }

        m_damage -= addhealth;
    }
}

void Spell::EffectHealPct (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive() || damage < 0)
        return;

    // Skip if m_originalCaster not available
    if (!m_originalCaster)
        return;

    int32 halfHP = 0;
    uint32 heal = m_originalCaster->SpellHealingBonusDone(unitTarget, m_spellInfo, unitTarget->CountPctFromMaxHealth(damage), HEAL);
    heal = unitTarget->SpellHealingBonusTaken(m_originalCaster, m_spellInfo, heal, HEAL);

    switch (m_spellInfo->Id)
    {
        // Victory Rush
        case 34428:
        {
            // Impending Victory
            if (m_originalCaster->HasAura(82368))
                halfHP = m_originalCaster->GetMaxHealth() * 0.05f;
            else
                halfHP = m_originalCaster->GetMaxHealth() * 0.20f;

            // Glyph of Victory Rush
            if (m_originalCaster->HasAura(58382))
                heal += heal * 0.50f;

            // Final Heal
            heal = halfHP;
            break;
        }
        // Feed Pet
        case 1539:
        {
            halfHP = unitTarget->GetMaxHealth() * 0.5f;
            heal = halfHP;
            break;
        }
        // Sun's Radiance Effect
        case 90118:
        {
            heal = unitTarget->GetMaxHealth() * 0.10f;
            break;
        }
        // Return to Nablya
        case 72165:
        {
            unitTarget->RemoveAurasDueToSpell(72181);
            unitTarget->RemoveAurasDueToSpell(71833);
            unitTarget->RemoveAurasDueToSpell(72156);
            unitTarget->RemoveAurasDueToSpell(72174);
            unitTarget->RemoveAurasDueToSpell(72210);
            unitTarget->RemoveAurasDueToSpell(72189);
            heal = unitTarget->GetMaxHealth();
            break;
        }
    }

    m_healing += heal;
}

void Spell::EffectHealMechanical (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive() || damage < 0)
        return;

    // Skip if m_originalCaster not available
    if (!m_originalCaster)
        return;

    uint32 heal = m_originalCaster->SpellHealingBonusDone(unitTarget, m_spellInfo, uint32(damage), HEAL);

    m_healing += unitTarget->SpellHealingBonusTaken(m_originalCaster, m_spellInfo, heal, HEAL);
}

void Spell::EffectHealthLeech (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive() || damage < 0)
        return;

    damage = m_caster->SpellDamageBonusDone(unitTarget, m_spellInfo, uint32(damage), SPELL_DIRECT_DAMAGE);
    damage = unitTarget->SpellDamageBonusTaken(m_caster, m_spellInfo, uint32(damage), SPELL_DIRECT_DAMAGE);

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "HealthLeech :%i", damage);

    float healMultiplier = m_spellInfo->Effects[effIndex].CalcValueMultiplier(m_originalCaster, this);

    m_damage += damage;
    // get max possible damage, don't count overkill for heal
    uint32 healthGain = uint32(-unitTarget->GetHealthGain(-damage) * healMultiplier);

    if (m_caster->isAlive())
    {
        healthGain = m_caster->SpellHealingBonusDone(m_caster, m_spellInfo, healthGain, HEAL);
        healthGain = m_caster->SpellHealingBonusTaken(m_caster, m_spellInfo, healthGain, HEAL);

        m_caster->HealBySpell(m_caster, m_spellInfo, uint32(healthGain));
    }
}

void Spell::DoCreateItem (uint32 /*i*/, uint32 itemtype)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = unitTarget->ToPlayer();

    uint32 newitemid = itemtype;
    ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(newitemid);
    if (!pProto)
    {
        player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }

    // bg reward have some special in code work
    uint32 bgType = 0;
    switch (m_spellInfo->Id)
    {
    case SPELL_AV_MARK_WINNER:
    case SPELL_AV_MARK_LOSER:
        bgType = BATTLEGROUND_AV;
        break;
    case SPELL_WS_MARK_WINNER:
    case SPELL_WS_MARK_LOSER:
        bgType = BATTLEGROUND_WS;
        break;
    case SPELL_AB_MARK_WINNER:
    case SPELL_AB_MARK_LOSER:
        bgType = BATTLEGROUND_AB;
        break;
    default:
        break;
    }

    uint32 num_to_add = damage;

    if (num_to_add < 1)
        num_to_add = 1;
    if (num_to_add > pProto->GetMaxStackSize())
        num_to_add = pProto->GetMaxStackSize();

    // init items_count to 1, since 1 item will be created regardless of specialization
    int items_count = 1;
    // the chance to create additional items
    float additionalCreateChance = 0.0f;
    // the maximum number of created additional items
    uint8 additionalMaxNum = 0;
    // get the chance and maximum number for creating extra items
    if (canCreateExtraItems(player, m_spellInfo->Id, additionalCreateChance, additionalMaxNum))
    {
        // roll with this chance till we roll not to create or we create the max num
        while (roll_chance_f(additionalCreateChance) && items_count <= additionalMaxNum)
            ++items_count;
    }

    // really will be created more items
    num_to_add *= items_count;

    // can the player store the new item?
    ItemPosCountVec dest;
    uint32 no_space = 0;
    InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newitemid, num_to_add, &no_space);
    if (msg != EQUIP_ERR_OK)
    {
        // convert to possible store amount
        if (msg == EQUIP_ERR_INV_FULL || msg == EQUIP_ERR_ITEM_MAX_COUNT)
            num_to_add -= no_space;
        else
        {
            // if not created by another reason from full inventory or unique items amount limitation
            player->SendEquipError(msg, NULL, NULL, newitemid);
            return;
        }
    }

    if (num_to_add)
    {
        uint32 projectId = GetSpellInfo()->ResearchProject;

        if (projectId && !player->ArchProjectCompleteable(projectId))
        {
            player->SendEquipError(EQUIP_ERR_SPELL_FAILED_REAGENTS_GENERIC, NULL, NULL);
            return;
        }

        // create the new item and store it
        Item* pItem = player->StoreNewItem(dest, newitemid, true, Item::GenerateItemRandomPropertyId(newitemid));

        // was it successful? return error if not
        if (!pItem)
        {
            player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
            return;
        }

        if (projectId)
            player->CompleteArchProject(projectId);

        // set the "Crafted by ..." property of the item
        if (pItem->GetTemplate()->Class != ITEM_CLASS_CONSUMABLE && pItem->GetTemplate()->Class != ITEM_CLASS_QUEST && newitemid != 6265 && newitemid != 6948)
            pItem->SetUInt32Value(ITEM_FIELD_CREATOR, player->GetGUIDLow());

        // send info to the client
        player->SendNewItem(pItem, num_to_add, true, bgType == 0);

        if (pProto->Quality > ITEM_QUALITY_EPIC || (pProto->Quality == ITEM_QUALITY_EPIC && pProto->ItemLevel >= MinNewsItemLevel[sWorld->getIntConfig(CONFIG_EXPANSION)]))
            if (Guild* guild = player->GetGuild())
                guild->AddGuildNews(GUILD_NEWS_ITEM_CRAFTED, player->GetGUID(), 0, pProto->ItemId);

        // Mix Master (Guild Achievement) (NFY - Check why this update also other criterias with same type)
        /*if (Guild* guild = player->GetGuild())
        {
            switch (m_spellInfo->Id)
            {
                case 94162: // Flask of Flowing Water
                case 80721: // Flask of the Winds
                case 80723: // Flask of Titanic Strength
                case 80720: // Flask of the Draconic Mind
                case 80719: // Flask of Steelskin
                {
                    guild->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_CRAFT_ITEMS_GUILD, 0, 5465, 0, NULL, player);
                    break;
                }
                default:
                    break;
            }
        }*/

        // we succeeded in creating at least one item, so a levelup is possible
        if (bgType == 0)
            player->UpdateCraftSkill(m_spellInfo->Id);
    }

    /*
     // for battleground marks send by mail if not add all expected
     if (no_space > 0 && bgType)
     {
     if (Battleground* bg = sBattlegroundMgr->GetBattlegroundTemplate(BattlegroundTypeId(bgType)))
     bg->SendRewardMarkByMail(player, newitemid, no_space);
     }
     */
}

void Spell::EffectCreateItem (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    DoCreateItem(effIndex, m_spellInfo->Effects[effIndex].ItemType);
    ExecuteLogEffectCreateItem(effIndex, m_spellInfo->Effects[effIndex].ItemType);
}

void Spell::EffectCreateItem2 (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = unitTarget->ToPlayer();

    uint32 item_id = m_spellInfo->Effects[effIndex].ItemType;

    // Random Volatile Element
    if (item_id == 54464)
    {
        uint32 volatiles[4] = {52325, 52326, 52327, 52328};
        item_id = volatiles[urand(0, 3)];
    }

    if (item_id)
        DoCreateItem(effIndex, item_id);

    // special case: fake item replaced by generate using spell_loot_template
    if (m_spellInfo->IsLootCrafting())
    {
        if (item_id)
        {
            if (!player->HasItemCount(item_id))
                return;

            // remove reagent
            uint32 count = 1;
            player->DestroyItemCount(item_id, count, true);

            // create some random items
            player->AutoStoreLoot(m_spellInfo->Id, LootTemplates_Spell);
        }
        else
            player->AutoStoreLoot(m_spellInfo->Id, LootTemplates_Spell);          // create some random items
    }

    // Jewelcrafting Daily Quests
    if (m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        switch (m_spellInfo->Id)
        {
            case 73227: // Solid Zephyrite
                m_caster->ToPlayer()->KilledMonsterCredit(39221);
                break;
            case 73274: // Jagged Jasper
                m_caster->ToPlayer()->KilledMonsterCredit(39223);
                break;
            case 73243: // Timeless Nightstone
                m_caster->ToPlayer()->KilledMonsterCredit(39222);
                break;
            default:
                break;
        }
    }

    // TODO: ExecuteLogEffectCreateItem(i, m_spellInfo->Effects[i].ItemType);
}

void Spell::EffectCreateRandomItem (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* player = unitTarget->ToPlayer();

    // create some random items
    player->AutoStoreLoot(m_spellInfo->Id, LootTemplates_Spell);
    // TODO: ExecuteLogEffectCreateItem(i, m_spellInfo->Effects[i].ItemType);
}

void Spell::EffectPersistentAA (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (!m_spellAura)
    {
        Unit* caster = m_caster->GetEntry() == WORLD_TRIGGER ? m_originalCaster : m_caster;
        if (!caster)
            return;

        if (!m_spellInfo)
            return;
        float radius = m_spellInfo->Effects[effIndex].CalcRadius(caster);

        // Caster not in world, might be spell triggered from aura removal
        if (!caster->IsInWorld())
            return;

        DynamicObject* dynObj = new DynamicObject(false);
        if (!dynObj->CreateDynamicObject(sObjectMgr->GenerateLowGuid(HIGHGUID_DYNAMICOBJECT), caster, m_spellInfo, *destTarget, radius, DYNAMIC_OBJECT_AREA_SPELL))
        {
            delete dynObj;
            return;
        }

        if (Aura* aura = Aura::TryCreate(m_spellInfo, MAX_EFFECT_MASK, dynObj, caster, &m_spellValue->EffectBasePoints[EFFECT_0]))
        {
            m_spellAura = aura;
            m_spellAura->_RegisterForTargets();
        }
        else
            return;
    }

    ASSERT(m_spellAura->GetDynobjOwner());

    m_spellAura->_ApplyEffectForTargets(effIndex);
}

void Spell::EffectEnergize (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    if (!unitTarget->isAlive())
        return;

    if (m_spellInfo->Effects[effIndex].MiscValue < 0 || m_spellInfo->Effects[effIndex].MiscValue >= int8(MAX_POWERS))
        return;

    Powers power = Powers(m_spellInfo->Effects[effIndex].MiscValue);

    // Some level depends spells
    int level_multiplier = 0;
    int level_diff = 0;
    switch (m_spellInfo->Id)
    {
        case 9512:          // Restore Energy
            level_diff = m_caster->getLevel() - 40;
            level_multiplier = 2;
            break;
        case 24571:          // Blood Fury
            level_diff = m_caster->getLevel() - 60;
            level_multiplier = 10;
            break;
        case 24532:          // Burst of Energy
            level_diff = m_caster->getLevel() - 60;
            level_multiplier = 4;
            break;
        case 31930:          // Judgements of the Wise
        case 63375:          // Primal Wisdom
        case 68082:          // Glyph of Seal of Command
        case 20167:          // Seal of Insight
        case 99131:          // Divine Fire
            damage = int32(CalculatePct(unitTarget->GetCreateMana(), damage));
            break;
        case 68285:         // Leader of the Pack
            damage = int32(CalculatePct(m_caster->GetMaxPower(POWER_MANA), damage));
            break;
        case 67490:          // Runic Mana Injector (mana gain increased by 25% for engineers - 3.2.0 patch change)
        {
            if (Player* player = m_caster->ToPlayer())
                if (player->HasSkill(SKILL_ENGINEERING))
                    AddPct(damage, 25);
            break;
        }
        case 90765:         // Digestive Juice
        {
            if (Player* player = m_caster->ToPlayer())
            {
                uint32 altPower = player->GetPower(POWER_ALTERNATE_POWER);
                if (player->isGameMaster())
                    damage = 0;

                // Field of Restoration
                if (player->HasAura(90736))
                {
                    damage = 0;
                    player->EnergizeBySpell(player, m_spellInfo->Id, -45, POWER_ALTERNATE_POWER);

                    // Cleanup secondary effect
                    if (altPower <= 74)                             // Digestive stage 1
                        player->RemoveAurasDueToSpell(90803);
                    if (altPower <= 150)                            // Digestive stage 2
                        player->RemoveAurasDueToSpell(90804);
                    if (altPower <= 224)                             // Digestive stage 3
                        player->RemoveAurasDueToSpell(90805);
                }

                // Apply secondary effect
                if (altPower >= 75 && altPower < 150 && !player->HasAura(90803))            // Digestive stage 1
                    player->CastSpell(player, 90803, true);
                if (altPower >= 150 && altPower < 225 && !player->HasAura(90804))           // Digestive stage 2
                    player->CastSpell(player, 90804, true);
                if (altPower >= 225 && !player->HasAura(90805))                             // Digestive stage 3
                    player->CastSpell(player, 90805, true);

                // Kill Player
                if (altPower >= 300)
                {
                    player->RemoveAurasDueToSpell(90803);
                    player->RemoveAurasDueToSpell(90804);
                    player->RemoveAurasDueToSpell(90805);
                    player->RemoveAurasDueToSpell(90782);
                    player->Kill(player, false);
                }
            }
            break;
        }
        case 92601: // Detonate Mana
        {
            if (m_caster && m_caster->GetTypeId() == TYPEID_PLAYER)
            {
                // Tyrande's Favorite Doll
                if (Aura* TFD = m_caster->GetAura(92272))
                {
                    uint32 manaPower = uint32(TFD->GetEffect(EFFECT_1)->GetAmount());
                    m_caster->EnergizeBySpell(m_caster, m_spellInfo->Id, manaPower, POWER_MANA);
                    TFD->GetEffect(EFFECT_1)->SetAmount(0);
                    return;
                }
            }
            break;
        }
        default:
            break;
    }

    if (level_diff > 0)
        damage -= level_multiplier * level_diff;

    if (damage < 0 && power != POWER_ECLIPSE)
        return;

    if (unitTarget->GetMaxPower(power) == 0)
        return;

    switch (m_spellInfo->Id)
    {
        case 2912:  // Starfire
        case 5176:  // Wrath
        case 35395: // Crusader Strike
        case 25912: // Holy Shock
        case 53595: // Hammer of the Righteous
        case 78674: // Starsurge
            break;
        default:
            m_caster->EnergizeBySpell(unitTarget, m_spellInfo->Id, damage, power);
            break;
    }

    // Mad Alchemist's Potion
    if (m_spellInfo->Id == 45051)
    {
        // find elixirs on target
        bool guardianFound = false;
        bool battleFound = false;
        Unit::AuraApplicationMap& Auras = unitTarget->GetAppliedAuras();
        for (Unit::AuraApplicationMap::iterator itr = Auras.begin(); itr != Auras.end(); ++itr)
        {
            uint32 spell_id = itr->second->GetBase()->GetId();
            if (!guardianFound)
                if (sSpellMgr->IsSpellMemberOfSpellGroup(spell_id, SPELL_GROUP_ELIXIR_GUARDIAN))
                guardianFound = true;
            if (!battleFound)
                if (sSpellMgr->IsSpellMemberOfSpellGroup(spell_id, SPELL_GROUP_ELIXIR_BATTLE))
                battleFound = true;
            if (battleFound && guardianFound)
                break;
        }

        // get all available elixirs by mask and spell level
        std::set<uint32> avalibleElixirs;
        if (!guardianFound)
            sSpellMgr->GetSetOfSpellsInSpellGroup(SPELL_GROUP_ELIXIR_GUARDIAN, avalibleElixirs);
        if (!battleFound)
            sSpellMgr->GetSetOfSpellsInSpellGroup(SPELL_GROUP_ELIXIR_BATTLE, avalibleElixirs);
        for (std::set<uint32>::iterator itr = avalibleElixirs.begin(); itr != avalibleElixirs.end();)
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(*itr);
            if (spellInfo->SpellLevel < m_spellInfo->SpellLevel || spellInfo->SpellLevel > unitTarget->getLevel())
            avalibleElixirs.erase(itr++);
            else if (sSpellMgr->IsSpellMemberOfSpellGroup(*itr, SPELL_GROUP_ELIXIR_SHATTRATH))
            avalibleElixirs.erase(itr++);
            else if (sSpellMgr->IsSpellMemberOfSpellGroup(*itr, SPELL_GROUP_ELIXIR_UNSTABLE))
            avalibleElixirs.erase(itr++);
            else
            ++itr;
        }

        if (!avalibleElixirs.empty())
        {
            // cast random elixir on target
            m_caster->CastSpell(unitTarget, Trinity::Containers::SelectRandomContainerElement(avalibleElixirs), true, m_CastItem);
        }
    }
}

void Spell::EffectEnergizePct (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;
    if (!unitTarget->isAlive())
        return;

    if (m_spellInfo->Effects[effIndex].MiscValue < 0 || m_spellInfo->Effects[effIndex].MiscValue >= int8(MAX_POWERS))
        return;

    Powers power = Powers(m_spellInfo->Effects[effIndex].MiscValue);

    uint32 maxPower = unitTarget->GetMaxPower(power);
    // For Masochism
    uint32 masochismR1 = m_caster->GetMaxPower(POWER_MANA) * 0.05f;
    uint32 masochismR2 = m_caster->GetMaxPower(POWER_MANA) * 0.10f;
    if (maxPower == 0)
        return;

    switch (m_spellInfo->Id)
    {
        case 89007: // Masochism (Effect)
        {
            if (m_caster->HasAura(88994))
            {
                m_caster->EnergizeBySpell(unitTarget, m_spellInfo->Id, masochismR1, power);
                return;
            }
            else if (m_caster->HasAura(88995))
            {
                m_caster->EnergizeBySpell(unitTarget, m_spellInfo->Id, masochismR2, power);
                return;
            }
            break;
        }
    }

    uint32 gain = CalculatePct(maxPower, damage);
    m_caster->EnergizeBySpell(unitTarget, m_spellInfo->Id, gain, power);
}

void Spell::SendLoot (uint64 guid, LootType loottype)
{
    Player* player = m_caster->ToPlayer();
    if (!player)
        return;

    if (gameObjTarget)
    {
        // Players shouldn't be able to loot gameobjects that are currently despawned
        if (!gameObjTarget->isSpawned() && !player->isGameMaster())
        {
            sLog->outError(LOG_FILTER_SPELLS_AURAS, "Possible hacking attempt: Player %s [guid: %u] tried to loot a gameobject [entry: %u id: %u] which is on respawn time without being in GM mode!",
                player->GetName().c_str(), player->GetGUIDLow(), gameObjTarget->GetEntry(), gameObjTarget->GetGUIDLow());
            return;
        }
        // special case, already has GossipHello inside so return and avoid calling twice
        if (gameObjTarget->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        {
            gameObjTarget->Use(m_caster);
            return;
        }

        if (sScriptMgr->OnGossipHello(player, gameObjTarget))
            return;

        if (gameObjTarget->AI()->GossipHello(player))
            return;

        switch (gameObjTarget->GetGoType())
        {
            case GAMEOBJECT_TYPE_DOOR:
            case GAMEOBJECT_TYPE_BUTTON:
            {
                gameObjTarget->UseDoorOrButton(0, false, player);
                return;
            }
            case GAMEOBJECT_TYPE_QUESTGIVER:
            {
                player->PrepareGossipMenu(gameObjTarget, gameObjTarget->GetGOInfo()->questgiver.gossipID);
                player->SendPreparedGossip(gameObjTarget);
                return;
            }
            case GAMEOBJECT_TYPE_SPELL_FOCUS:
            {
                // triggering linked GO
                if (uint32 trapEntry = gameObjTarget->GetGOInfo()->spellFocus.linkedTrapId)
                    gameObjTarget->TriggeringLinkedGameObject(trapEntry, m_caster);
                return;
            }
            case GAMEOBJECT_TYPE_CHEST:
            {
                // TODO: possible must be moved to loot release (in different from linked triggering)
                if (gameObjTarget->GetGOInfo()->chest.eventId)
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Chest ScriptStart id %u for GO %u", gameObjTarget->GetGOInfo()->chest.eventId, gameObjTarget->GetDBTableGUIDLow());
                    player->GetMap()->ScriptsStart(sEventScripts, gameObjTarget->GetGOInfo()->chest.eventId, player, gameObjTarget);
                }
            }

            // triggering linked GO
            if (uint32 trapEntry = gameObjTarget->GetGOInfo()->chest.linkedTrapId)
                gameObjTarget->TriggeringLinkedGameObject(trapEntry, m_caster);
            // Don't return, let loots been taken
            default:
                break;
        }
    }

    // Send loot
    player->SendLoot(guid, loottype);
}

void Spell::EffectOpenLock (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "WORLD: Open Lock - No Player Caster!");
        return;
    }

    Player* player = m_caster->ToPlayer();

    uint32 lockId = 0;
    uint64 guid = 0;

    // Get lockId
    if (gameObjTarget)
    {
        GameObjectTemplate const* goInfo = gameObjTarget->GetGOInfo();
        // Arathi Basin banner opening. // TODO: Verify correctness of this check
        if ((goInfo->type == GAMEOBJECT_TYPE_BUTTON && goInfo->button.noDamageImmune) || (goInfo->type == GAMEOBJECT_TYPE_GOOBER && goInfo->goober.losOK))
        {
            //CanUseBattlegroundObject() already called in CheckCast()
            // in battleground check
            if (Battleground* bg = player->GetBattleground())
            {
                bg->EventPlayerClickedOnFlag(player, gameObjTarget);
                return;
            }
        }
        else if (goInfo->type == GAMEOBJECT_TYPE_FLAGSTAND)
        {
            //CanUseBattlegroundObject() already called in CheckCast()
            // in battleground check
            if (Battleground* bg = player->GetBattleground())
            {
                if (bg->GetTypeID(true) == BATTLEGROUND_EY)
                    bg->EventPlayerClickedOnFlag(player, gameObjTarget);
                return;
            }
        }
        else if (m_spellInfo->Id == 1842 && gameObjTarget->GetGOInfo()->type == GAMEOBJECT_TYPE_TRAP && gameObjTarget->GetOwner())
        {
            gameObjTarget->SetLootState(GO_JUST_DEACTIVATED);
            return;
        }
        // TODO: Add script for spell 41920 - Filling, becouse server it freze when use this spell
        // handle outdoor pvp object opening, return true if go was registered for handling
        // these objects must have been spawned by outdoorpvp!
        else if (gameObjTarget->GetGOInfo()->type == GAMEOBJECT_TYPE_GOOBER && sOutdoorPvPMgr->HandleOpenGo(player, gameObjTarget->GetGUID()))
        return;
        lockId = goInfo->GetLockId();
        guid = gameObjTarget->GetGUID();
    }
    else if (itemTarget)
    {
        lockId = itemTarget->GetTemplate()->LockID;
        guid = itemTarget->GetGUID();
    }
    else
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "WORLD: Open Lock - No GameObject/Item Target!");
        return;
    }

    SkillType skillId = SKILL_NONE;
    int32 reqSkillValue = 0;
    int32 skillValue;

    SpellCastResult res = CanOpenLock(effIndex, lockId, skillId, reqSkillValue, skillValue);
    if (res != SPELL_CAST_OK)
    {
        SendCastResult(res);
        return;
    }

    if (gameObjTarget)
    {
        if (skillId == SKILL_ARCHAEOLOGY)
            SendLoot(guid, LOOT_ARCHAEOLOGY);
        else
            SendLoot(guid, LOOT_SKINNING);
    }
    else if (itemTarget)
        itemTarget->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_UNLOCKED);

    // not allow use skill grow at item base open
    if (!m_CastItem && skillId != SKILL_NONE)
    {
        // update skill if really known
        if (uint32 pureSkillValue = player->GetPureSkillValue(skillId))
        {
            if (gameObjTarget)
            {
                // Allow one skill-up until respawned
                if (!gameObjTarget->IsInSkillupList(player->GetGUIDLow()) && player->UpdateGatherSkill(skillId, pureSkillValue, reqSkillValue))
                {
                    gameObjTarget->AddToSkillupList(player->GetGUIDLow());
                    player->GiveXpForGather(skillId, reqSkillValue);
                }
            }
            else if (itemTarget)
            {
                // Do one skill-up
                player->UpdateGatherSkill(skillId, pureSkillValue, reqSkillValue);
            }
        }
    }
    ExecuteLogEffectOpenLock(effIndex, gameObjTarget ? (Object*) gameObjTarget : (Object*) itemTarget);
}

void Spell::EffectSummonChangeItem (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = m_caster->ToPlayer();

    // applied only to using item
    if (!m_CastItem)
        return;

    // ... only to item in own inventory/bank/equip_slot
    if (m_CastItem->GetOwnerGUID() != player->GetGUID())
        return;

    uint32 newitemid = m_spellInfo->Effects[effIndex].ItemType;
    if (!newitemid)
        return;

    uint16 pos = m_CastItem->GetPos();

    Item* pNewItem = Item::CreateItem(newitemid, 1, player);
    if (!pNewItem)
        return;

    for (uint8 j = PERM_ENCHANTMENT_SLOT; j <= TEMP_ENCHANTMENT_SLOT; ++j)
        if (m_CastItem->GetEnchantmentId(EnchantmentSlot(j)))
            pNewItem->SetEnchantment(EnchantmentSlot(j), m_CastItem->GetEnchantmentId(EnchantmentSlot(j)), m_CastItem->GetEnchantmentDuration(EnchantmentSlot(j)), m_CastItem->GetEnchantmentCharges(EnchantmentSlot(j)));

    if (m_CastItem->GetUInt32Value(ITEM_FIELD_DURABILITY) < m_CastItem->GetUInt32Value(ITEM_FIELD_MAXDURABILITY))
    {
        double lossPercent = 1 - m_CastItem->GetUInt32Value(ITEM_FIELD_DURABILITY) / double(m_CastItem->GetUInt32Value(ITEM_FIELD_MAXDURABILITY));
        player->DurabilityLoss(pNewItem, lossPercent);
    }

    if (player->IsInventoryPos(pos))
    {
        ItemPosCountVec dest;
        InventoryResult msg = player->CanStoreItem(m_CastItem->GetBagSlot(), m_CastItem->GetSlot(), dest, pNewItem, true);
        if (msg == EQUIP_ERR_OK)
        {
            player->DestroyItem(m_CastItem->GetBagSlot(), m_CastItem->GetSlot(), true);

            // prevent crash at access and unexpected charges counting with item update queue corrupt
            if (m_CastItem == m_targets.GetItemTarget())
                m_targets.SetItemTarget(NULL);

            m_CastItem = NULL;
            m_castItemGUID = 0;

            player->StoreItem(dest, pNewItem, true);
            return;
        }
    }
    else if (player->IsBankPos(pos))
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanBankItem(m_CastItem->GetBagSlot(), m_CastItem->GetSlot(), dest, pNewItem, true);
        if (msg == EQUIP_ERR_OK)
        {
            player->DestroyItem(m_CastItem->GetBagSlot(), m_CastItem->GetSlot(), true);

            // prevent crash at access and unexpected charges counting with item update queue corrupt
            if (m_CastItem == m_targets.GetItemTarget())
                m_targets.SetItemTarget(NULL);

            m_CastItem = NULL;
            m_castItemGUID = 0;

            player->BankItem(dest, pNewItem, true);
            return;
        }
    }
    else if (player->IsEquipmentPos(pos))
    {
        uint16 dest;

        player->DestroyItem(m_CastItem->GetBagSlot(), m_CastItem->GetSlot(), true);

        uint8 msg = player->CanEquipItem(m_CastItem->GetSlot(), dest, pNewItem, true);

        if (msg == EQUIP_ERR_OK || msg == EQUIP_ERR_CLIENT_LOCKED_OUT)
        {
            if (msg == EQUIP_ERR_CLIENT_LOCKED_OUT)
                dest = EQUIPMENT_SLOT_MAINHAND;

            // prevent crash at access and unexpected charges counting with item update queue corrupt
            if (m_CastItem == m_targets.GetItemTarget())
                m_targets.SetItemTarget(NULL);

            m_CastItem = NULL;
            m_castItemGUID = 0;

            player->EquipItem(dest, pNewItem, true);
            player->AutoUnequipOffhandIfNeed();
            return;
        }
    }

    // fail
    delete pNewItem;
}

void Spell::EffectProficiency (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* p_target = m_caster->ToPlayer();

    uint32 subClassMask = m_spellInfo->EquippedItemSubClassMask;
    if (m_spellInfo->EquippedItemClass == ITEM_CLASS_WEAPON && !(p_target->GetWeaponProficiency() & subClassMask))
    {
        p_target->AddWeaponProficiency(subClassMask);
        p_target->SendProficiency(ITEM_CLASS_WEAPON, p_target->GetWeaponProficiency());
    }
    if (m_spellInfo->EquippedItemClass == ITEM_CLASS_ARMOR && !(p_target->GetArmorProficiency() & subClassMask))
    {
        p_target->AddArmorProficiency(subClassMask);
        p_target->SendProficiency(ITEM_CLASS_ARMOR, p_target->GetArmorProficiency());
    }
}

void Spell::EffectSummonType (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    uint32 entry = m_spellInfo->Effects[effIndex].MiscValue;
    if (!entry)
        return;

    SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(m_spellInfo->Effects[effIndex].MiscValueB);
    if (!properties)
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "EffectSummonType: Unhandled summon type %u", m_spellInfo->Effects[effIndex].MiscValueB);
        return;
    }

    if (!m_originalCaster)
        return;

    int32 duration = m_spellInfo->GetDuration();
    if (Player* modOwner = m_originalCaster->GetSpellModOwner())
        modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_DURATION, duration);

    TempSummon* summon = NULL;

    // determine how many units should be summoned
    uint32 numSummons;

    // some spells need to summon many units, for those spells number of summons is stored in effect value
    // however so far noone found a generic check to find all of those (there's no related data in summonproperties.dbc
    // and in spell attributes, possibly we need to add a table for those)
    // so here's a list of MiscValueB values, which is currently most generic check
    switch (properties->Id)
    {
    case 64:
    case 61:
    case 1101:
    case 66:
    case 648:
    case 2301:
    case 1061:
    case 1261:
    case 629:
    case 181:
    case 715:
    case 1562:
    case 833:
    case 1161:
    case 2929:
    case 3097:
        numSummons = (damage > 0) ? damage : 1;
        break;
    default:
        numSummons = 1;
        break;
    }

    switch (properties->Category)
    {
    case SUMMON_CATEGORY_WILD:
    case SUMMON_CATEGORY_ALLY:
    case SUMMON_CATEGORY_UNK:
        if (properties->Flags & 512)
        {
            SummonGuardian(effIndex, entry, properties, numSummons);
            break;
        }
        switch (properties->Type)
        {
        case SUMMON_TYPE_PET:
        case SUMMON_TYPE_GUARDIAN:
        case SUMMON_TYPE_GUARDIAN2:
        case SUMMON_TYPE_MINION:
            SummonGuardian(effIndex, entry, properties, numSummons);
            break;
            // Summons a vehicle, but doesn't force anyone to enter it (see SUMMON_CATEGORY_VEHICLE)
        case SUMMON_TYPE_VEHICLE:
        case SUMMON_TYPE_VEHICLE2:
            summon = m_caster->GetMap()->SummonCreature(entry, *destTarget, properties, duration, m_originalCaster, m_spellInfo->Id);
            break;
        case SUMMON_TYPE_LIGHTWELL:
        case SUMMON_TYPE_TOTEM:
        {
            summon = m_caster->GetMap()->SummonCreature(entry, *destTarget, properties, duration, m_originalCaster, m_spellInfo->Id);
            if (!summon || !summon->isTotem())
                return;

            // Mana Tide Totem
            if (m_spellInfo->Id == 16190)
                damage = m_caster->CountPctFromMaxHealth(10);

            // Lightwell
            if (m_spellInfo->Id == 724)
                damage = m_caster->CountPctFromMaxHealth(30);

            if (damage)          // if not spell info, DB values used
            {
                summon->SetMaxHealth(damage);
                summon->SetHealth(damage);
            }
            break;
        }
        case SUMMON_TYPE_MINIPET:
        {
            summon = m_caster->GetMap()->SummonCreature(entry, *destTarget, properties, duration, m_originalCaster, m_spellInfo->Id);
            if (!summon || !summon->HasUnitTypeMask(UNIT_MASK_MINION))
                return;

            summon->SelectLevel(summon->GetCreatureTemplate());          // some summoned creaters have different from 1 DB data for level/hp
            summon->SetUInt32Value(UNIT_NPC_FLAGS, summon->GetCreatureTemplate()->npcflag);

            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);

            summon->AI()->EnterEvadeMode();
            break;
        }
        default:
        {
            float radius = m_spellInfo->Effects[effIndex].CalcRadius();

            TempSummonType summonType = (duration == 0) ? TEMPSUMMON_DEAD_DESPAWN : TEMPSUMMON_TIMED_DESPAWN;

            for (uint32 count = 0; count < numSummons; ++count)
            {
                Position pos;
                if (count == 0)
                    pos = *destTarget;
                else
                    // randomize position for multiple summons
                    m_caster->GetRandomPoint(*destTarget, radius, pos);

                summon = m_originalCaster->SummonCreature(entry, pos, summonType, duration, 0, properties);
                if (!summon)
                    continue;

                if (properties->Category == SUMMON_CATEGORY_ALLY)
                {
                    summon->SetOwnerGUID(m_originalCaster->GetGUID());
                    summon->setFaction(m_originalCaster->getFaction());
                    summon->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);
                }

                ExecuteLogEffectSummonObject(effIndex, summon);
            }
            return;
        }
        }          //switch
        break;
    case SUMMON_CATEGORY_PET:
        SummonGuardian(effIndex, entry, properties, numSummons);
        break;
    case SUMMON_CATEGORY_PUPPET:
        summon = m_caster->GetMap()->SummonCreature(entry, *destTarget, properties, duration, m_originalCaster, m_spellInfo->Id);
        break;
    case SUMMON_CATEGORY_VEHICLE:
        // Summoning spells (usually triggered by npc_spellclick) that spawn a vehicle and that cause the clicker
        // to cast a ride vehicle spell on the summoned unit.
        float x, y, z;
        m_caster->GetClosePoint(x, y, z, DEFAULT_WORLD_OBJECT_SIZE);
        summon = m_originalCaster->GetMap()->SummonCreature(entry, *destTarget, properties, duration, m_caster, m_spellInfo->Id);
        if (!summon || !summon->IsVehicle())
            return;

        // The spell that this effect will trigger. It has SPELL_AURA_CONTROL_VEHICLE
        uint32 spellId = VEHICLE_SPELL_RIDE_HARDCODED;
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(m_spellInfo->Effects[effIndex].CalcValue());
        if (spellInfo && spellInfo->HasAura(SPELL_AURA_CONTROL_VEHICLE))
        spellId = spellInfo->Id;

        // Hard coded enter vehicle spell
        m_originalCaster->CastSpell(summon, spellId, true);

        uint32 faction = properties->Faction;
        if (!faction)
        faction = m_originalCaster->getFaction();

        summon->setFaction(faction);
        break;
    }

    if (summon)
    {
        summon->SetCreatorGUID(m_originalCaster->GetGUID());
        ExecuteLogEffectSummonObject(effIndex, summon);
    }
}

void Spell::EffectLearnSpell (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
    {
        if (unitTarget->ToPet())
            EffectLearnPetSpell(effIndex);
        return;
    }

    Player* player = unitTarget->ToPlayer();

    uint32 spellToLearn = (m_spellInfo->Id == 483 || m_spellInfo->Id == 55884) ? damage : m_spellInfo->Effects[effIndex].TriggerSpell;
    player->learnSpell(spellToLearn, false);

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell: Player %u has learned spell %u from NpcGUID=%u", player->GetGUIDLow(), spellToLearn, m_caster->GetGUIDLow());
}

typedef std::list<std::pair<uint32, uint64> > DispelList;
void Spell::EffectDispel (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    // Create dispel mask by dispel type
    uint32 dispel_type = m_spellInfo->Effects[effIndex].MiscValue;
    uint32 dispelMask = SpellInfo::GetDispelMask(DispelType(dispel_type));

    DispelChargesList dispel_list;
    unitTarget->GetDispellableAuraList(m_caster, dispelMask, dispel_list);
    if (dispel_list.empty())
        return;

    // Ok if exist some buffs for dispel try dispel it
    uint32 failCount = 0;
    DispelChargesList success_list;
    WorldPacket dataFail(SMSG_DISPEL_FAILED, 8 + 8 + 4 + 4 + damage * 4);
    // dispel N = damage buffs (or while exist buffs for dispel)
    for (int32 count = 0; count < damage && !dispel_list.empty();)
    {
        // Random select buff for dispel
        DispelChargesList::iterator itr = dispel_list.begin();
        std::advance(itr, urand(0, dispel_list.size() - 1));

        int32 chance = itr->first->CalcDispelChance(unitTarget, !unitTarget->IsFriendlyTo(m_caster));
        // 2.4.3 Patch Notes: "Dispel effects will no longer attempt to remove effects that have 100% dispel resistance."
        if (!chance)
        {
            dispel_list.erase(itr);
            continue;
        }
        else
        {
            if (roll_chance_i(chance))
            {
                bool alreadyListed = false;
                for (DispelChargesList::iterator successItr = success_list.begin(); successItr != success_list.end(); ++successItr)
                {
                    if (successItr->first->GetId() == itr->first->GetId())
                    {
                        ++successItr->second;
                        alreadyListed = true;
                    }
                }
                if (!alreadyListed)
                    success_list.push_back(std::make_pair(itr->first, 1));
                --itr->second;
                if (itr->second <= 0)
                    dispel_list.erase(itr);
            }
            else
            {
                if (!failCount)
                {
                    // Failed to dispell
                    dataFail << uint64(m_caster->GetGUID());          // Caster GUID
                    dataFail << uint64(unitTarget->GetGUID());          // Victim GUID
                    dataFail << uint32(m_spellInfo->Id);          // dispel spell id
                }
                ++failCount;
                dataFail << uint32(itr->first->GetId());          // Spell Id
            }
            ++count;
        }
    }

    if (failCount)
        m_caster->SendMessageToSet(&dataFail, true);

    if (success_list.empty())
        return;

    WorldPacket dataSuccess(SMSG_SPELLDISPELLOG, 8 + 8 + 4 + 1 + 4 + success_list.size() * 5);
    // Send packet header
    dataSuccess.append(unitTarget->GetPackGUID());          // Victim GUID
    dataSuccess.append(m_caster->GetPackGUID());          // Caster GUID
    dataSuccess << uint32(m_spellInfo->Id);          // dispel spell id
    dataSuccess << uint8(0);          // not used
    dataSuccess << uint32(success_list.size());          // count
    for (DispelChargesList::iterator itr = success_list.begin(); itr != success_list.end(); ++itr)
    {
        // Send dispelled spell info
        dataSuccess << uint32(itr->first->GetId());          // Spell Id
        dataSuccess << uint8(0);          // 0 - dispelled !=0 cleansed
        unitTarget->RemoveAurasDueToSpellByDispel(itr->first->GetId(), m_spellInfo->Id, itr->first->GetCasterGUID(), m_caster, itr->second);
    }
    m_caster->SendMessageToSet(&dataSuccess, true);

    // On success dispel
    // Devour Magic
    if (m_spellInfo->SpellFamilyName == SPELLFAMILY_WARLOCK && m_spellInfo->Category == SPELLCATEGORY_DEVOUR_MAGIC)
    {
        int32 heal_amount = m_spellInfo->Effects[EFFECT_1].CalcValue(m_caster);
        m_caster->CastCustomSpell(m_caster, 19658, &heal_amount, NULL, NULL, true);
        // Glyph of Felhunter
        if (Unit* owner = m_caster->GetOwner())
            if (owner->GetAura(56249))
                owner->CastCustomSpell(owner, 19658, &heal_amount, NULL, NULL, true);
    }

    switch (m_spellInfo->Id)
    {
        // Cleanse Spirit
        case 51886:
        {
             if (m_caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Cleansing Waters r1
            if (m_caster->HasAura(86959))
            {
                if (!m_caster->ToPlayer()->HasSpellCooldown(86961))
                {
                    m_caster->CastSpell(unitTarget, 86961, true);
                    m_caster->ToPlayer()->AddSpellCooldown(86961, 0, time(NULL) + 6);
                }
            }
            // Cleansing Waters r2
            else if (m_caster->HasAura(86962))
            {
                if (!m_caster->ToPlayer()->HasSpellCooldown(86958))
                {
                    m_caster->CastSpell(unitTarget, 86958, true);
                    m_caster->ToPlayer()->AddSpellCooldown(86958, 0, time(NULL) + 6);
                }
            }
            break;
        }
        default:
            break;
    }
}

void Spell::EffectDualWield (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    unitTarget->SetCanDualWield(true);
}

void Spell::EffectPull (SpellEffIndex effIndex)
{
    // TODO: create a proper pull towards distract spell center for distract
    EffectNULL(effIndex);
}

void Spell::EffectDistract (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    // Check for possible target
    if (!unitTarget || unitTarget->isInCombat())
        return;

    // target must be OK to do this
    if (unitTarget->HasUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_STUNNED | UNIT_STATE_FLEEING))
        return;

    // Check if vision is obscured for that target
    if (m_caster && m_caster->IsVisionObscured(unitTarget))
        return;

    unitTarget->SetFacingTo(unitTarget->GetAngle(destTarget));
    unitTarget->ClearUnitState(UNIT_STATE_MOVING);

    if (unitTarget->GetTypeId() == TYPEID_UNIT)
        unitTarget->GetMotionMaster()->MoveDistract(damage * IN_MILLISECONDS);
}

void Spell::EffectPickPocket (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    // victim must be creature and attackable
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->IsFriendlyTo(unitTarget))
        return;

    // victim have to be alive and humanoid or undead
    if (unitTarget->isAlive() && (unitTarget->GetCreatureTypeMask() & CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD) != 0)
        m_caster->ToPlayer()->SendLoot(unitTarget->GetGUID(), LOOT_PICKPOCKETING);
}

void Spell::EffectAddFarsight (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    float radius = m_spellInfo->Effects[effIndex].CalcRadius();
    int32 duration = m_spellInfo->GetDuration();
    // Caster not in world, might be spell triggered from aura removal
    if (!m_caster->IsInWorld())
        return;

    DynamicObject* dynObj = new DynamicObject(true);
    if (!dynObj->CreateDynamicObject(sObjectMgr->GenerateLowGuid(HIGHGUID_DYNAMICOBJECT), m_caster, m_spellInfo, *destTarget, radius, DYNAMIC_OBJECT_FARSIGHT_FOCUS))
    {
        delete dynObj;
        return;
    }

    dynObj->SetDuration(duration);
    dynObj->SetCasterViewpoint();
}

void Spell::EffectUntrainTalents (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || m_caster->GetTypeId() == TYPEID_PLAYER)
        return;

    if (uint64 guid = m_caster->GetGUID())          // the trainer is the caster
        unitTarget->ToPlayer()->SendTalentWipeConfirm(guid);
}

void Spell::EffectTeleUnitsFaceCaster (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    if (unitTarget->isInFlight())
        return;

    float dis = m_spellInfo->Effects[effIndex].CalcRadius(m_caster);

    float fx, fy, fz;
    m_caster->GetClosePoint(fx, fy, fz, unitTarget->GetObjectSize(), dis);

    unitTarget->NearTeleportTo(fx, fy, fz, -m_caster->GetOrientation(), unitTarget == m_caster);
}

void Spell::EffectLearnSkill (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    if (damage < 0)
        return;

    uint32 skillid = m_spellInfo->Effects[effIndex].MiscValue;
    uint16 skillval = unitTarget->ToPlayer()->GetPureSkillValue(skillid);
    unitTarget->ToPlayer()->SetSkill(skillid, m_spellInfo->Effects[effIndex].CalcValue(), skillval ? skillval : 1, damage * 75);
}

void Spell::EffectPlayMovie (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    uint32 movieId = GetSpellInfo()->Effects[effIndex].MiscValue;
    if (!sMovieStore.LookupEntry(movieId))
        return;

    unitTarget->ToPlayer()->SendMovieStart(movieId);
}

void Spell::EffectTradeSkill (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    // uint32 skillid =  m_spellInfo->Effects[i].MiscValue;
    // uint16 skillmax = unitTarget->ToPlayer()->(skillid);
    // m_caster->ToPlayer()->SetSkill(skillid, skillval?skillval:1, skillmax+75);
}

void Spell::EffectEnchantItemPerm (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    if (!itemTarget)
        return;

    Player* p_caster = (Player*) m_caster;

    // Handle vellums
    if (itemTarget->IsVellum())
    {
        // destroy one vellum from stack
        uint32 count = 1;
        p_caster->DestroyItemCount(itemTarget, count, true);
        unitTarget = p_caster;
        // and add a scroll
        DoCreateItem(effIndex, m_spellInfo->Effects[effIndex].ItemType);
        itemTarget = NULL;
        m_targets.SetItemTarget(NULL);
    }
    else
    {
        // do not increase skill if vellum used
        if (!(m_CastItem && m_CastItem->GetTemplate()->Flags & ITEM_PROTO_FLAG_TRIGGERED_CAST))
            p_caster->UpdateCraftSkill(m_spellInfo->Id);

        uint32 enchant_id = m_spellInfo->Effects[effIndex].MiscValue;
        if (!enchant_id)
            return;

        SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
        if (!pEnchant)
            return;

        // item can be in trade slot and have owner diff. from caster
        Player* item_owner = itemTarget->GetOwner();
        if (!item_owner)
            return;

        if (item_owner != p_caster && !AccountMgr::IsPlayerAccount(p_caster->GetSession()->GetSecurity()) && sWorld->getBoolConfig(CONFIG_GM_LOG_TRADE))
        {
            sLog->outCommand(p_caster->GetSession()->GetAccountId(), "GM %s (Account: %u) enchanting(perm): %s (Entry: %d) for player: %s (Account: %u)",
            p_caster->GetName().c_str(), p_caster->GetSession()->GetAccountId(),
            itemTarget->GetTemplate()->Name1.c_str(), itemTarget->GetEntry(),
            item_owner->GetName().c_str(), item_owner->GetSession()->GetAccountId());
        }

        // remove old enchanting before applying new if equipped
        item_owner->ApplyEnchantment(itemTarget, PERM_ENCHANTMENT_SLOT, false);

        itemTarget->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchant_id, 0, 0, m_caster->GetGUID()); 

        // add new enchanting if equipped
        item_owner->ApplyEnchantment(itemTarget, PERM_ENCHANTMENT_SLOT, true);

        item_owner->RemoveTradeableItem(itemTarget);
        itemTarget->ClearSoulboundTradeable(item_owner);
    }
}

void Spell::EffectEnchantItemPrismatic (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    if (!itemTarget)
        return;

    Player* p_caster = (Player*) m_caster;

    uint32 enchant_id = m_spellInfo->Effects[effIndex].MiscValue;
    if (!enchant_id)
        return;

    SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
    if (!pEnchant)
        return;

    // support only enchantings with add socket in this slot
    {
        bool add_socket = false;
        for (uint8 i = 0; i < MAX_ITEM_ENCHANTMENT_EFFECTS; ++i)
        {
            if (pEnchant->type[i] == ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET)
            {
                add_socket = true;
                break;
            }
        }
        if (!add_socket)
        {
            sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell::EffectEnchantItemPrismatic: attempt apply enchant spell %u with SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC (%u) but without ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET (%u), not suppoted yet.",
                    m_spellInfo->Id, SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC, ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET);
            return;
        }
    }

    // item can be in trade slot and have owner diff. from caster
    Player* item_owner = itemTarget->GetOwner();
    if (!item_owner)
        return;

    if (item_owner != p_caster && !AccountMgr::IsPlayerAccount(p_caster->GetSession()->GetSecurity()) && sWorld->getBoolConfig(CONFIG_GM_LOG_TRADE))
    {
        sLog->outCommand(p_caster->GetSession()->GetAccountId(), "GM %s (Account: %u) enchanting(perm): %s (Entry: %d) for player: %s (Account: %u)",
        p_caster->GetName().c_str(), p_caster->GetSession()->GetAccountId(),
        itemTarget->GetTemplate()->Name1.c_str(), itemTarget->GetEntry(),
        item_owner->GetName().c_str(), item_owner->GetSession()->GetAccountId());
    }

    // remove old enchanting before applying new if equipped
    item_owner->ApplyEnchantment(itemTarget, PRISMATIC_ENCHANTMENT_SLOT, false);

    itemTarget->SetEnchantment(PRISMATIC_ENCHANTMENT_SLOT, enchant_id, 0, 0, m_caster->GetGUID()); 

    // add new enchanting if equipped
    item_owner->ApplyEnchantment(itemTarget, PRISMATIC_ENCHANTMENT_SLOT, true);

    item_owner->RemoveTradeableItem(itemTarget);
    itemTarget->ClearSoulboundTradeable(item_owner);
}

void Spell::EffectEnchantItemTmp (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* p_caster = (Player*) m_caster;

    if (!itemTarget)
        return;

    // Rogue Poisons
    if (p_caster && m_spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE)
    {
        // Need Poison (Passive) active
        if (!p_caster->HasAura(2842))
            return;
    }

    uint32 enchant_id = m_spellInfo->Effects[effIndex].MiscValue;

    if (!enchant_id)
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell %u Effect %u (SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY) have 0 as enchanting id", m_spellInfo->Id, effIndex);
        return;
    }

    SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
    if (!pEnchant)
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell %u Effect %u (SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY) have not existed enchanting id %u ", m_spellInfo->Id, effIndex, enchant_id);
        return;
    }

    // select enchantment duration
    uint32 duration;

    // rogue family enchantments exception by duration
    if (m_spellInfo->Id == 38615)
        duration = 1800;          // 30 mins
    // other rogue family enchantments always 1 hour (some have spell damage=0, but some have wrong data in EffBasePoints)
    else if (m_spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE)
        duration = 3600;          // 1 hour
    // shaman family enchantments
    else if (m_spellInfo->SpellFamilyName == SPELLFAMILY_SHAMAN)
        duration = 1800;          // 30 mins
    // other cases with this SpellVisual already selected
    else if (m_spellInfo->SpellVisual[0] == 215)
        duration = 1800;          // 30 mins
    // some fishing pole bonuses except Glow Worm which lasts full hour
    else if (m_spellInfo->SpellVisual[0] == 563 && m_spellInfo->Id != 64401)
        duration = 600;          // 10 mins
    // shaman rockbiter enchantments
    else if (m_spellInfo->SpellVisual[0] == 0)
        duration = 1800;          // 30 mins
    else if (m_spellInfo->Id == 29702)
        duration = 300;          // 5 mins
    else if (m_spellInfo->Id == 37360)
        duration = 300;          // 5 mins
    // default case
    else
        duration = 3600;          // 1 hour

    // item can be in trade slot and have owner diff. from caster
    Player* item_owner = itemTarget->GetOwner();
    if (!item_owner)
        return;

    if (item_owner != p_caster && !AccountMgr::IsPlayerAccount(p_caster->GetSession()->GetSecurity()) && sWorld->getBoolConfig(CONFIG_GM_LOG_TRADE))
    {
        sLog->outCommand(p_caster->GetSession()->GetAccountId(), "GM %s (Account: %u) enchanting(temp): %s (Entry: %d) for player: %s (Account: %u)",
        p_caster->GetName().c_str(), p_caster->GetSession()->GetAccountId(),
        itemTarget->GetTemplate()->Name1.c_str(), itemTarget->GetEntry(),
        item_owner->GetName().c_str(), item_owner->GetSession()->GetAccountId());
    }

    // remove old enchanting before applying new if equipped
    item_owner->ApplyEnchantment(itemTarget, TEMP_ENCHANTMENT_SLOT, false);

    itemTarget->SetEnchantment(TEMP_ENCHANTMENT_SLOT, enchant_id, duration * 1000, 0, m_caster->GetGUID()); 

    // add new enchanting if equipped
    item_owner->ApplyEnchantment(itemTarget, TEMP_ENCHANTMENT_SLOT, true);
}

void Spell::EffectTameCreature (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetPetGUID())
        return;

    Creature* creature = unitTarget->ToCreature();

    if (creature->isPet())
        return;

    PetTameResult result = m_caster->ToPlayer()->TamePet(creature->GetEntry(), m_spellInfo->Id, creature->getLevel());

    if (result != PET_TAME_ERROR_NO_ERROR)
        m_caster->ToPlayer()->SendPetTameError(result);

    creature->DespawnOrUnsummon();
}

void Spell::EffectSummonPet (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    Player* owner = NULL;
    if (m_originalCaster)
    {
        owner = m_originalCaster->ToPlayer();
        if (!owner && m_originalCaster->ToCreature()->isTotem())
            owner = m_originalCaster->GetCharmerOrOwnerPlayerOrPlayerItself();
    }

    uint32 petentry = m_spellInfo->Effects[effIndex].MiscValue;

    if (!owner)
    {
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(67);
        if (properties)
            SummonGuardian(effIndex, petentry, properties, 1);
        return;
    }

    if (Pet* currentPet = owner->GetPet())
    {
        if (petentry == 0 || currentPet->GetEntry() == petentry)
        {
            // pet in corpse state can't be summoned
            if (currentPet->isDead())
                return;

            ASSERT(currentPet->GetMap() == owner->GetMap());

            float px, py, pz;
            owner->GetClosePoint(px, py, pz, currentPet->GetObjectSize());
            currentPet->NearTeleportTo(px, py, pz, currentPet->GetOrientation());

            //Resummon part
            owner->TemporaryUnsummonPet();
            owner->ResummonTemporaryUnsummonedPet();
            return;
        }
        else if (owner->GetTypeId() == TYPEID_PLAYER)
            owner->RemoveCurrentPet();
        else
            return;
    }

    if (owner->getClass() == CLASS_HUNTER && m_spellInfo->SpellIconID == 455)
    {
        owner->SummonPet((PetSlot)m_spellInfo->Effects[effIndex].BasePoints);
        return;
    }

    if (Pet *pet = owner->SummonPet(PET_SLOT_APPROPRIATE_SLOT, petentry))
    {
        pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

        if (m_caster->GetTypeId() == TYPEID_UNIT)
        {
            if (m_caster->ToCreature()->isTotem())
                pet->SetReactState(REACT_AGGRESSIVE);
            else
                pet->SetReactState(REACT_DEFENSIVE);
        }

        ExecuteLogEffectSummonObject(effIndex, pet);

        if (pet->IsPetGhoul())
        {
            pet->setPowerType(POWER_ENERGY);
            pet->SetMaxPower(POWER_ENERGY, 100);
            pet->SetPower(POWER_ENERGY, 100);
        }
    }

    // Camouflage
    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        if (m_caster->getClass() == CLASS_HUNTER)
            if (m_caster->HasAuraType(SPELL_AURA_MOD_CAMOUFLAGE))
                m_caster->RemoveAurasByType(SPELL_AURA_MOD_CAMOUFLAGE);
}

void Spell::EffectLearnPetSpell (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    if (unitTarget->ToPlayer())
    {
        EffectLearnSpell(effIndex);
        return;
    }
    Pet* pet = unitTarget->ToPet();
    if (!pet)
        return;

    SpellInfo const* learn_spellproto = sSpellMgr->GetSpellInfo(m_spellInfo->Effects[effIndex].TriggerSpell);
    if (!learn_spellproto)
        return;

    pet->learnSpell(learn_spellproto->Id);
    //pet->GetOwner()->SynchPetData(pet);
    pet->GetOwner()->PetSpellInitialize();
}

void Spell::EffectTaunt (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    // Army of the Dead Taunt (Not useable in dungeons/raid)
    if (m_spellInfo->Id == 29060)
        if (unitTarget->GetMap() && unitTarget->GetMap()->Instanceable())
            return;

    // this effect use before aura Taunt apply for prevent taunt already attacking target
    // for spell as marked "non effective at already attacking target"
    if (!unitTarget || !unitTarget->CanHaveThreatList() || unitTarget->getVictim() == m_caster)
    {
        SendCastResult(SPELL_FAILED_DONT_REPORT);
        return;
    }

    // Also use this effect to set the taunter's threat to the taunted creature's highest value
    if (unitTarget->getThreatManager().getCurrentVictim())
    {
        float myThreat = unitTarget->getThreatManager().getThreat(m_caster);
        float itsThreat = unitTarget->getThreatManager().getCurrentVictim()->getThreat();
        if (itsThreat > myThreat)
            unitTarget->getThreatManager().addThreat(m_caster, itsThreat - myThreat);
    }

    //Set aggro victim to caster
    if (!unitTarget->getThreatManager().getOnlineContainer().empty())
        if (HostileReference* forcedVictim = unitTarget->getThreatManager().getOnlineContainer().getReferenceByTarget(m_caster))
            unitTarget->getThreatManager().setCurrentVictim(forcedVictim);

    if (unitTarget->ToCreature()->IsAIEnabled && !unitTarget->ToCreature()->HasReactState(REACT_PASSIVE))
        unitTarget->ToCreature()->AI()->AttackStart(m_caster);
}

void Spell::EffectWeaponDmg (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive())
        return;

    // multiple weapon dmg effect workaround
    // execute only the last weapon damage
    // and handle all effects at once
    for (uint32 j = effIndex + 1; j < MAX_SPELL_EFFECTS; ++j)
    {
        switch (m_spellInfo->Effects[j].Effect)
        {
            case SPELL_EFFECT_WEAPON_DAMAGE:
            case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
            case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
            case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
            {
                return;
                break;
            }
            default:
                break;
        }
    }

    // Spell modifiers
    float totalDamagePercentMod = 1.0f;         // Final Bonus + Weapon Damage
    int32 fixed_bonus           = 0;            // Fixed Bonus (Unused??)
    int32 spell_bonus           = 0;            // Bonus specific for spells

    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_WARRIOR:
        {
            // Devastate (player ones)
            if (m_spellInfo->SpellFamilyFlags[1] & 0x40)
            {
                // Player can apply only 58567 Sunder Armor effect.
                bool needCast = !unitTarget->HasAura(58567, m_caster->GetGUID());
                if (needCast)
                    m_caster->CastSpell(unitTarget, 58567, true);

                if (Aura* aur = unitTarget->GetAura(58567, m_caster->GetGUID()))
                {
                    if (int32 num = (needCast ? 0 : 1))
                        aur->ModStackAmount(num);
                }
            }

            switch (m_spellInfo->Id)
            {
                // Slam
                case 50782:
                case 97992:
                {
                    // Bloodsurge
                    if (GetCaster()->HasAura(46916))
                        totalDamagePercentMod += totalDamagePercentMod * 0.20f;
                    break;
                }
                // Raging Blow
                case 85384:
                case 96103:
                {
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                    {
                        // Mastery: Unshackled Fury
                        float masteryPoints = GetCaster()->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        if (GetCaster()->HasAura(76856))
                            totalDamagePercentMod += totalDamagePercentMod * (0.110f + (0.0560f * masteryPoints));
                    }
                    break;
                }
                // Devastate
                case 20243:
                {
                    if (!unitTarget || !m_caster)
                        break;

                    // Sunder Armor
                    if (Aura* aur = unitTarget->GetAura(58567, m_caster->GetGUID()))
                        totalDamagePercentMod += totalDamagePercentMod * aur->GetStackAmount() / 5;
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_ROGUE:
        {
            // Hemorrhage
            if (m_spellInfo->SpellFamilyFlags[0] & 0x2000000)
            {
                if (!m_caster || !unitTarget)
                    return;

                if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    m_caster->ToPlayer()->AddComboPoints(unitTarget, 1, this);

                // 50% more damage with daggers
                if (m_caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Item* item = m_caster->ToPlayer()->GetWeaponForAttack(m_attackType, true))
                    {
                        if (item->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_DAGGER)
                            totalDamagePercentMod *= 1.5f;
                    }
                }
            }
            break;
        }
        case SPELLFAMILY_SHAMAN:
        {
            // Skyshatter Harness item set bonus
            // Stormstrike
            if (m_caster)
                if (AuraEffect* aurEff = m_caster->IsScriptOverriden(m_spellInfo, 5634))
                    m_caster->CastSpell(m_caster, 38430, true, NULL, aurEff);

            switch (m_spellInfo->Id)
            {
                case 60103: // Lava Lash
                {
                    if (!m_caster)
                        return;

                    // Damage is increased by 40% if your off-hand weapon is enchanted with Flametongue.
                    if (m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, 0x200000, 0, 0))
                        totalDamagePercentMod += totalDamagePercentMod * 0.40f;

                    // Each points of Mastery increases damage by an additional 2.5%
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        float masteryPoints = m_caster->ToPlayer()->GetRatingBonusValue(CR_MASTERY);
                        if (m_caster->HasAura(77223, m_caster->GetGUID()))
                            totalDamagePercentMod += 0.025f * masteryPoints;
                    }

                    // Improved Lava Lash
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, 4780, EFFECT_1))
                    {
                        int32 bp0 = aurEff->GetAmount();

                        // Check for target first
                        if (!unitTarget)
                            return;

                        // Searing Flames
                        if (Aura* searingFlames = unitTarget->GetAura(77661, m_caster->GetGUID()))
                        {
                            int8 stack = searingFlames->GetStackAmount();
                            int32 pct = bp0 * stack;

                            // Add damage pct based on Improved Lava Lash effect per Searing Flames stacks
                            totalDamagePercentMod += totalDamagePercentMod * pct / 100;

                            // Consume it!
                            searingFlames->Remove();
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            // Mangle (Cat): CP
            if (m_spellInfo->SpellFamilyFlags[1] & 0x400)
            {
                if (m_caster && m_caster->GetTypeId() == TYPEID_PLAYER)
                    if (unitTarget)
                        m_caster->ToPlayer()->AddComboPoints(unitTarget, 1, this);
            }
            // Shred, Maul - Rend and Tear
            else if (unitTarget && m_spellInfo->SpellFamilyFlags[0] & 0x00008800 && unitTarget->HasAuraState(AURA_STATE_BLEEDING))
            {
                if (AuraEffect const* rendAndTear = m_caster->GetDummyAuraEffect(SPELLFAMILY_DRUID, 2859, 0))
                    AddPct(totalDamagePercentMod, rendAndTear->GetAmount());
            }
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            //Templar's Verdict
            if (m_spellInfo->Id == 85256)
            {
                if (!m_caster)
                    return;

                // Divine Purpose
                if (m_caster->HasAura(90174))
                {
                    totalDamagePercentMod += totalDamagePercentMod * 7.82f;
                    break;
                }
                switch (m_caster->GetPower(POWER_HOLY_POWER))
                {
                    case 0: // 1 Holy Power
                        totalDamagePercentMod += totalDamagePercentMod * 0.36f;
                        break;
                    case 1: // 2 Holy Power
                        totalDamagePercentMod += totalDamagePercentMod * 3.0f;
                        break;
                    case 2: // 3 Holy Power
                        totalDamagePercentMod += totalDamagePercentMod * 7.82f;
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            switch (m_spellInfo->Id)
            {
                // Aimed Shot
                case 19434:
                case 82928:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.724f;
                    if (unitTarget)
                    {
                        // Hunter's Mark
                        if (AuraEffect* hunterMark = unitTarget->GetAuraEffect(1130, EFFECT_1))
                            fixed_bonus += fixed_bonus * uint32(hunterMark->GetAmount() / 100) / 100;
                    }
                    break;
                }
                // Arcane Shot
                case 3044:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.0483f;
                    if (unitTarget)
                    {
                        // Hunter's Mark
                        if (AuraEffect* hunterMark = unitTarget->GetAuraEffect(1130, EFFECT_1))
                            fixed_bonus += fixed_bonus * uint32(hunterMark->GetAmount() / 100) / 100;
                    }
                    break;
                }
                // Black Arrow
                case 3674:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.0665f;
                    break;
                }
                // Chimera Shot
                case 53209:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.732f;
                    if (unitTarget)
                    {
                        // Hunter's Mark
                        if (AuraEffect* hunterMark = unitTarget->GetAuraEffect(1130, EFFECT_1))
                            fixed_bonus += fixed_bonus * uint32(hunterMark->GetAmount() / 100) / 100;
                    }
                    break;
                }
                // Cobra Shot
                case 77767:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.017f;
                    if (unitTarget)
                    {
                        // Hunter's Mark
                        if (AuraEffect* hunterMark = unitTarget->GetAuraEffect(1130, EFFECT_1))
                            fixed_bonus += fixed_bonus * uint32(hunterMark->GetAmount() / 100) / 100;
                    }
                    break;
                }
                // Explosive Shot
                case 53301:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.15f;
                    break;
                }
                // Kill Shot
                case 53351:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.45f;
                    break;
                }
                // Steady Shot
                case 56641:
                {
                    fixed_bonus += m_caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.021f;
                    if (unitTarget)
                    {
                        // Hunter's Mark
                        if (AuraEffect* hunterMark = unitTarget->GetAuraEffect(1130, EFFECT_1))
                            fixed_bonus += fixed_bonus * uint32(hunterMark->GetAmount() / 100) / 100;
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            // Felstorm
            if (Unit* owner = m_caster->GetCharmerOrOwner())
            {
                switch (m_spellInfo->Id)
                {
                    case 89753: // Felstorm
                    {
                        if (unitTarget)
                        {
                            float spellPower = (float)(owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                            fixed_bonus += uint32(spellPower * 0.50f);
                        }
                        break;
                    }
                    case 30213: // Legion Strike
                    {
                        if (m_caster->GetCharmerOrOwner())
                        {
                            if (unitTarget)
                            {
                                float spellPower = (float)(owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW) + unitTarget->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_SHADOW));
                                fixed_bonus += uint32(spellPower * 0.38f);
                                // Glyph of Felguard
                                if (owner->HasAura(56246))
                                    damage += damage * 0.05f;
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        case SPELLFAMILY_DEATHKNIGHT:
        {
            // Blood Strike
            if (m_spellInfo->SpellFamilyFlags[0] & 0x400000)
            {
                float bonusPct = m_spellInfo->Effects[EFFECT_2].CalcValue(m_caster) * unitTarget->GetDiseasesByCaster(m_caster->GetGUID()) / 10;
                // Death Knight T8 Melee 4P Bonus
                if (AuraEffect const* aurEff = m_caster->GetAuraEffect(64736, EFFECT_0))
                    AddPct(bonusPct, aurEff->GetAmount());
                AddPct(totalDamagePercentMod, bonusPct);
            }
            // Death Strike
            if (m_spellInfo->SpellFamilyFlags[0] & 0x10)
            {
                // Glyph of Death Strike
                // 2% more damage per 5 runic power, up to a maximum of 40%
                if (AuraEffect const* aurEff = m_caster->GetAuraEffect(59336, EFFECT_0))
                    if (uint32 runic = std::min<uint32>(uint32(m_caster->GetPower(POWER_RUNIC_POWER) / 25.0f), aurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue(m_caster)))
                        AddPct(totalDamagePercentMod, runic);
            }
            // Obliterate (12.5% more damage per disease)
            if (m_spellInfo->SpellFamilyFlags[1] & 0x20000)
            {
                float bonusPct = m_spellInfo->Effects[EFFECT_2].CalcValue(m_caster) * unitTarget->GetDiseasesByCaster(m_caster->GetGUID(), false) / 2.0f;
                // Death Knight T8 Melee 4P Bonus
                if (AuraEffect const* aurEff = m_caster->GetAuraEffect(64736, EFFECT_0))
                    AddPct(bonusPct, aurEff->GetAmount());

                // Merciless Combat
                if (AuraEffect* mCombat = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 2656, 0))
                {
                    if (unitTarget->HealthBelowPct(35))
                        AddPct(totalDamagePercentMod, mCombat->GetAmount());
                }

                AddPct(totalDamagePercentMod, bonusPct);
                break;
            }
            // Blood-Caked Strike - Blood-Caked Blade
            if (m_spellInfo->SpellIconID == 1736)
                AddPct(totalDamagePercentMod, unitTarget->GetDiseasesByCaster(m_caster->GetGUID()) * 12.5f);

            // Heart Strike
            if (m_spellInfo->SpellFamilyFlags[0] & 0x1000000)
            {
                float bonusPct = m_spellInfo->Effects[EFFECT_2].CalcValue(m_caster) * unitTarget->GetDiseasesByCaster(m_caster->GetGUID());
                // Death Knight T8 Melee 4P Bonus
                if (AuraEffect const* aurEff = m_caster->GetAuraEffect(64736, EFFECT_0))
                    AddPct(bonusPct, aurEff->GetAmount());

                AddPct(totalDamagePercentMod, bonusPct);
            }
            // Plague Strike
            if (m_spellInfo->Id == 45462)
            {
                if (!unitTarget)
                    break;

                // Ebon Plaguebringer
                if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 1766, 0))
                    m_caster->CastSpell(unitTarget, 65142, true);
            }
            break;
        }
    }

    bool normalized = false;
    float weaponDamagePercentMod = 1.0f;
    for (int j = 0; j < MAX_SPELL_EFFECTS; ++j)
    {
        switch (m_spellInfo->Effects[j].Effect)
        {
        case SPELL_EFFECT_WEAPON_DAMAGE:
        case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
            fixed_bonus += CalculateDamage(j, unitTarget);
            break;
        case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
            fixed_bonus += CalculateDamage(j, unitTarget);
            normalized = true;
            break;
        case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
            ApplyPct(weaponDamagePercentMod, CalculateDamage(j, unitTarget));
            break;
        default:
            break;          // not weapon damage effect, just skip
        }
    }

    // apply to non-weapon bonus weapon total pct effect, weapon total flat effect included in weapon damage
    if (fixed_bonus || spell_bonus)
    {
        UnitMods unitMod;
        switch (m_attackType)
        {
        default:
        case BASE_ATTACK:
            unitMod = UNIT_MOD_DAMAGE_MAINHAND;
            break;
        case OFF_ATTACK:
            unitMod = UNIT_MOD_DAMAGE_OFFHAND;
            break;
        case RANGED_ATTACK:
            unitMod = UNIT_MOD_DAMAGE_RANGED;
            break;
        }

        float weapon_total_pct = 1.0f;
        if (m_spellInfo->SchoolMask & SPELL_SCHOOL_MASK_NORMAL)
            weapon_total_pct = m_caster->GetModifierValue(unitMod, TOTAL_PCT);

        if (fixed_bonus)
            fixed_bonus = int32(fixed_bonus * weapon_total_pct);
        if (spell_bonus)
            spell_bonus = int32(spell_bonus * weapon_total_pct);
    }

    int32 weaponDamage = m_caster->CalculateDamage(m_attackType, normalized, true);

    // Sequence is important
    for (int j = 0; j < MAX_SPELL_EFFECTS; ++j)
    {
        // We assume that a spell have at most one fixed_bonus
        // and at most one weaponDamagePercentMod
        switch (m_spellInfo->Effects[j].Effect)
        {
        case SPELL_EFFECT_WEAPON_DAMAGE:
        case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
        case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
            weaponDamage += fixed_bonus;
            break;
        case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
            weaponDamage = int32(weaponDamage * weaponDamagePercentMod);
        default:
            break;          // not weapon damage effect, just skip
        }
    }

    if (spell_bonus)
        weaponDamage += spell_bonus;

    if (totalDamagePercentMod != 1.0f)
        weaponDamage = int32(weaponDamage * totalDamagePercentMod);

    // prevent negative damage
    uint32 eff_damage(std::max(weaponDamage, 0));

    // Add melee damage bonuses (also check for negative)
    uint32 damage = m_caster->MeleeDamageBonusDone(unitTarget, eff_damage, m_attackType, m_spellInfo);

    m_damage += unitTarget->MeleeDamageBonusTaken(m_caster, damage, m_attackType, m_spellInfo);
}

void Spell::EffectThreat (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive() || !m_caster->isAlive())
        return;

    if (!unitTarget->CanHaveThreatList())
        return;

    unitTarget->AddThreat(m_caster, float(damage));
}

void Spell::EffectHealMaxHealth (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive())
        return;

    int32 addhealth = 0;

    // damage == 0 - heal for caster max health
    if (damage == 0)
        addhealth = m_caster->GetMaxHealth();
    else
        addhealth = unitTarget->GetMaxHealth() - unitTarget->GetHealth();

    m_healing += addhealth;

    switch (m_spellInfo->Id)
    {
        case 633: // Lay on Hands
        {
            // Glyph of Divinity
            if (m_caster->HasAura(54939))
                m_caster->CastSpell(m_caster, 54986, true);
            break;
        }
    }

    Unit::AuraEffectList const &aurEff = unitTarget->GetAuraEffectsByType(SPELL_AURA_MOD_HEALING_PCT);
    for (Unit::AuraEffectList::const_iterator i = aurEff.begin(); i != aurEff.end(); ++i)
    {
        if (aurEff.empty())
            continue;

        // Only for hostile buffs
        if (aurEff.front()->GetCaster() && !aurEff.front()->GetCaster()->IsHostileTo(unitTarget))
            continue;

        int32 healingReduction = int32(-aurEff.front()->GetAmount());
        m_healing -= m_healing * healingReduction / 100;
        return;
    }
}

void Spell::EffectInterruptCast (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive())
        return;

    // TODO: not all spells that used this effect apply cooldown at school spells
    // also exist case: apply cooldown to interrupted cast only and to all spells
    // there is no CURRENT_AUTOREPEAT_SPELL spells that can be interrupted
    for (uint32 i = CURRENT_FIRST_NON_MELEE_SPELL; i < CURRENT_AUTOREPEAT_SPELL; ++i)
    {
        if (Spell* spell = unitTarget->GetCurrentSpell(CurrentSpellTypes(i)))
        {
            SpellInfo const* curSpellInfo = spell->m_spellInfo;
            // check if we can interrupt spell
            if ((spell->getState() == SPELL_STATE_CASTING || (spell->getState() == SPELL_STATE_PREPARING && spell->GetCastTime() > 0.0f)) && (curSpellInfo->PreventionType == SPELL_PREVENTION_TYPE_SILENCE || curSpellInfo->PreventionType == SPELL_PREVENTION_TYPE_UNK) && ((i == CURRENT_GENERIC_SPELL && curSpellInfo->InterruptFlags & SPELL_INTERRUPT_FLAG_INTERRUPT) || (i == CURRENT_CHANNELED_SPELL && curSpellInfo->ChannelInterruptFlags & CHANNEL_INTERRUPT_FLAG_INTERRUPT)))
            {
                if (m_originalCaster)
                {
                    int32 duration = m_spellInfo->GetDuration();
                    unitTarget->ProhibitSpellSchool(curSpellInfo->GetSchoolMask(), unitTarget->ModSpellDuration(m_spellInfo, unitTarget, duration, false, 1 << effIndex));
                }
                ExecuteLogEffectInterruptCast(effIndex, unitTarget, curSpellInfo->Id);
                unitTarget->InterruptSpellWithSource(CurrentSpellTypes(i), m_originalCaster, false);

                switch (m_spellInfo->Id)
                {
                    // Counterspell
                    case 2139:
                    {
                        // Invocation rank 1
                        if (m_caster->HasAura(84722))
                        {
                            int32 bp = 5;
                            m_caster->CastCustomSpell(m_caster, 87098, &bp, NULL, NULL, true);
                        }
                        // Invocation rank 2
                        if (m_caster->HasAura(84723))
                        {
                            int32 bp = 10;
                            m_caster->CastCustomSpell(m_caster, 87098, &bp, NULL, NULL, true);
                        }
                        break;
                    }
                    // Wind Shear
                    case 87994:
                    {
                        // Seasoned Winds
                        if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, 2016, 0))
                        {
                            int32 bp0 = aurEff->GetAmount();
                            switch (spell->m_spellSchoolMask)
                            {
                                case SPELL_SCHOOL_MASK_ARCANE:
                                    m_caster->CastCustomSpell(m_caster, 97621, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                                    break;
                                case SPELL_SCHOOL_MASK_FIRE:
                                    m_caster->CastCustomSpell(m_caster, 97618, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                                    break;
                                case SPELL_SCHOOL_MASK_FROST:
                                    m_caster->CastCustomSpell(m_caster, 97619, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                                    break;
                                case SPELL_SCHOOL_MASK_NATURE:
                                    m_caster->CastCustomSpell(m_caster, 97620, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                                    break;
                                case SPELL_SCHOOL_MASK_SHADOW:
                                    m_caster->CastCustomSpell(m_caster, 97622, &bp0, NULL, NULL, true, NULL, NULL, m_caster->GetGUID());
                                    break;
                            }
                        }
                        break;
                    }
                    // Kick
                    case 1766:
                    {
                        if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            // Glyph of Kick
                            if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_ROGUE, 246, 1))
                            {
                                int32 amount = aurEff->GetAmount() / 1000;
                                m_caster->ToPlayer()->UpdateSpellCooldown(1766, -amount);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Spell::EffectSummonObjectWild (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    uint32 gameobject_id = m_spellInfo->Effects[effIndex].MiscValue;

    GameObject* pGameObj = new GameObject;

    WorldObject* target = focusObject;
    if (!target)
        target = m_caster;

    float x, y, z;
    if (m_targets.HasDst())
        destTarget->GetPosition(x, y, z);
    else
        m_caster->GetClosePoint(x, y, z, DEFAULT_WORLD_OBJECT_SIZE);

    Map* map = target->GetMap();

    if (!pGameObj->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), gameobject_id, map,
    m_caster->GetPhaseMask(), x, y, z, target->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 100, GO_STATE_READY))
    {
        delete pGameObj;
        return;
    }

    int32 duration = m_spellInfo->GetDuration();

    pGameObj->SetRespawnTime(duration > 0 ? duration / IN_MILLISECONDS : 0);
    pGameObj->SetSpellId(m_spellInfo->Id);

    ExecuteLogEffectSummonObject(effIndex, pGameObj);

    // Wild object not have owner and check clickable by players
    map->AddToMap(pGameObj);

    if (pGameObj->GetGoType() == GAMEOBJECT_TYPE_FLAGDROP)
        if (Player* player = m_caster->ToPlayer())
            if (Battleground* bg = player->GetBattleground())
                bg->SetDroppedFlagGUID(pGameObj->GetGUID(), player->GetTeam() == ALLIANCE ? TEAM_HORDE : TEAM_ALLIANCE);

    if (uint32 linkedEntry = pGameObj->GetGOInfo()->GetLinkedGameObjectEntry())
    {
        GameObject* linkedGO = new GameObject;
        if (linkedGO->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), linkedEntry, map,
        m_caster->GetPhaseMask(), x, y, z, target->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 100, GO_STATE_READY))
        {
            linkedGO->SetRespawnTime(duration > 0 ? duration/IN_MILLISECONDS : 0);
            linkedGO->SetSpellId(m_spellInfo->Id);

            ExecuteLogEffectSummonObject(effIndex, linkedGO);

            // Wild object not have owner and check clickable by players
            map->AddToMap(linkedGO);
        }
        else
        {
            delete linkedGO;
            linkedGO = NULL;
            return;
        }
    }
}

void Spell::EffectScriptEffect (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    // TODO: we must implement hunter pet summon at login there (spell 6962)

    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            switch (m_spellInfo->Id)
            {
                // Glyph of Backstab
                case 63975:
                {
                    // search our Rupture aura on target
                    if (AuraEffect const* aurEff = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_ROGUE, 0x00100000, 0, 0, m_caster->GetGUID()))
                    {
                        uint32 countMin = aurEff->GetBase()->GetMaxDuration();
                        uint32 countMax = 12000;          // this can be wrong, duration should be based on combo-points
                        countMax += m_caster->HasAura(56801) ? 4000 : 0;

                        if (countMin < countMax)
                        {
                            aurEff->GetBase()->SetDuration(uint32(aurEff->GetBase()->GetDuration() + 3000));
                            aurEff->GetBase()->SetMaxDuration(countMin + 2000);
                        }

                    }
                    return;
                }
                // Glyph of Scourge Strike
                case 69961:
                {
                    Unit::AuraEffectList const &mPeriodic = unitTarget->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
                    for (Unit::AuraEffectList::const_iterator i = mPeriodic.begin(); i != mPeriodic.end(); ++i)
                    {
                        AuraEffect const* aurEff = *i;
                        SpellInfo const* spellInfo = aurEff->GetSpellInfo();
                        // search our Blood Plague and Frost Fever on target
                        if (spellInfo->SpellFamilyName == SPELLFAMILY_DEATHKNIGHT && spellInfo->SpellFamilyFlags[2] & 0x2 && aurEff->GetCasterGUID() == m_caster->GetGUID())
                        {
                            uint32 countMin = aurEff->GetBase()->GetMaxDuration();
                            uint32 countMax = spellInfo->GetMaxDuration();

                            // this Glyph
                            countMax += 9000;
                            // talent Epidemic
                            if (AuraEffect const* epidemic = m_caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_DEATHKNIGHT, 234, EFFECT_0))
                                countMax += epidemic->GetAmount();

                            if (countMin < countMax)
                            {
                                aurEff->GetBase()->SetDuration(aurEff->GetBase()->GetDuration() + 3000);
                                aurEff->GetBase()->SetMaxDuration(countMin + 3000);
                            }
                        }
                    }
                    return;
                }
                case 45204:          // Clone Me!
                    m_caster->CastSpell(unitTarget, damage, true);
                    break;
                case 55693:          // Remove Collapsing Cave Aura
                    if (!unitTarget)
                        return;
                    unitTarget->RemoveAurasDueToSpell(m_spellInfo->Effects[effIndex].CalcValue());
                    break;
                // Bending Shinbone
                case 8856:
                {
                    if (!itemTarget && m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spell_id = roll_chance_i(20) ? 8854 : 8855;

                    m_caster->CastSpell(m_caster, spell_id, true, NULL);
                    return;
                }
                // Brittle Armor - need remove one 24575 Brittle Armor aura
                case 24590:
                    unitTarget->RemoveAuraFromStack(24575);
                    return;
                // Mercurial Shield - need remove one 26464 Mercurial Shield aura
                case 26465:
                    unitTarget->RemoveAuraFromStack(26464);
                    return;
                // Shadow Flame (All script effects, not just end ones to prevent player from dodging the last triggered spell)
                case 22539:
                case 22972:
                case 22975:
                case 22976:
                case 22977:
                case 22978:
                case 22979:
                case 22980:
                case 22981:
                case 22982:
                case 22983:
                case 22984:
                case 22985:
                {
                    if (!unitTarget || !unitTarget->isAlive())
                        return;

                    // Onyxia Scale Cloak
                    if (unitTarget->HasAura(22683))
                        return;

                    // Shadow Flame
                    m_caster->CastSpell(unitTarget, 22682, true);
                    return;
                }
                // Decimate
                case 28374:
                case 54426:
                {
                    if (unitTarget)
                    {
                        int32 damage = int32(unitTarget->GetHealth()) - int32(unitTarget->CountPctFromMaxHealth(5));
                        if (damage > 0)
                            m_caster->CastCustomSpell(28375, SPELLVALUE_BASE_POINT0, damage, unitTarget);
                    }
                    return;
                }
                // Mirren's Drinking Hat
                case 29830:
                {
                    uint32 item = 0;
                    switch (urand(1, 6))
                    {
                    case 1:
                    case 2:
                    case 3:
                        item = 23584;
                        break;          // Loch Modan Lager
                    case 4:
                    case 5:
                        item = 23585;
                        break;          // Stouthammer Lite
                    case 6:
                        item = 23586;
                        break;          // Aerie Peak Pale Ale
                    }
                    if (item)
                        DoCreateItem(effIndex, item);
                    break;
                }
                case 20589:          // Escape artist
                case 30918:          // Improved Sprint
                {
                    // Removes snares and roots.
                    unitTarget->RemoveMovementImpairingAuras();
                    break;
                }
                // Plant Warmaul Ogre Banner
                case 32307:
                {
                    if (Player* caster = m_caster->ToPlayer())
                    {
                        caster->RewardPlayerAndGroupAtEvent(18388, unitTarget);
                        if (Creature* target = unitTarget->ToCreature())
                        {
                            target->setDeathState(CORPSE);
                            target->RemoveCorpse();
                        }
                    }
                    break;
                }
                // Mug Transformation
                case 41931:
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint8 bag = 19;
                    uint8 slot = 0;
                    Item* item = NULL;

                    while (bag)          // 256 = 0 due to var type
                    {
                        item = m_caster->ToPlayer()->GetItemByPos(bag, slot);
                        if (item && item->GetEntry() == 38587)
                            break;

                        ++slot;
                        if (slot == 39)
                        {
                            slot = 0;
                            ++bag;
                        }
                    }
                    if (bag)
                    {
                        if (m_caster->ToPlayer()->GetItemByPos(bag, slot)->GetCount() == 1)
                            m_caster->ToPlayer()->RemoveItem(bag, slot, true);
                        else
                            m_caster->ToPlayer()->GetItemByPos(bag, slot)->SetCount(m_caster->ToPlayer()->GetItemByPos(bag, slot)->GetCount() - 1);
                        // Spell 42518 (Braufest - Gratisprobe des Braufest herstellen)
                        m_caster->CastSpell(m_caster, 42518, true);
                        return;
                    }
                    break;
                }
                // Brutallus - Burn
                case 45141:
                case 45151:
                {
                    //Workaround for Range ... should be global for every ScriptEffect
                    float radius = m_spellInfo->Effects[effIndex].CalcRadius();
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER && unitTarget->GetDistance(m_caster) >= radius && !unitTarget->HasAura(46394) && unitTarget != m_caster)
                        unitTarget->CastSpell(unitTarget, 46394, true);

                    break;
                }
                // Goblin Weather Machine
                case 46203:
                {
                    if (!unitTarget)
                        return;

                    uint32 spellId = 0;
                    switch (rand() % 4)
                    {
                    case 0:
                        spellId = 46740;
                        break;
                    case 1:
                        spellId = 46739;
                        break;
                    case 2:
                        spellId = 46738;
                        break;
                    case 3:
                        spellId = 46736;
                        break;
                    }
                    unitTarget->CastSpell(unitTarget, spellId, true);
                    break;
                }
                // 5, 000 Gold
                case 46642:
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->ToPlayer()->ModifyMoney(5000 * GOLD);
                    break;
                }
                // Roll Dice - Decahedral Dwarven Dice
                case 47770:
                {
                    char buf[128];
                    const char *gender = "his";
                    if (m_caster->getGender() > 0)
                        gender = "her";
                    sprintf(buf, "%s rubs %s [Decahedral Dwarven Dice] between %s hands and rolls. One %u and one %u.", m_caster->GetName().c_str(), gender, gender, urand(1, 10), urand(1, 10));
                    m_caster->MonsterTextEmote(buf, 0);
                    break;
                }
                // Roll 'dem Bones - Worn Troll Dice
                case 47776:
                {
                    char buf[128];
                    const char *gender = "his";
                    if (m_caster->getGender() > 0)
                        gender = "her";
                    sprintf(buf, "%s causually tosses %s [Worn Troll Dice]. One %u and one %u.", m_caster->GetName().c_str(), gender, urand(1, 6), urand(1, 6));
                    m_caster->MonsterTextEmote(buf, 0);
                    break;
                }
                // Death Knight Initiate Visual
                case 51519:
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    uint32 iTmpSpellId = 0;
                    switch (unitTarget->GetDisplayId())
                    {
                    case 25369:
                        iTmpSpellId = 51552;
                        break;          // bloodelf female
                    case 25373:
                        iTmpSpellId = 51551;
                        break;          // bloodelf male
                    case 25363:
                        iTmpSpellId = 51542;
                        break;          // draenei female
                    case 25357:
                        iTmpSpellId = 51541;
                        break;          // draenei male
                    case 25361:
                        iTmpSpellId = 51537;
                        break;          // dwarf female
                    case 25356:
                        iTmpSpellId = 51538;
                        break;          // dwarf male
                    case 25372:
                        iTmpSpellId = 51550;
                        break;          // forsaken female
                    case 25367:
                        iTmpSpellId = 51549;
                        break;          // forsaken male
                    case 25362:
                        iTmpSpellId = 51540;
                        break;          // gnome female
                    case 25359:
                        iTmpSpellId = 51539;
                        break;          // gnome male
                    case 25355:
                        iTmpSpellId = 51534;
                        break;          // human female
                    case 25354:
                        iTmpSpellId = 51520;
                        break;          // human male
                    case 25360:
                        iTmpSpellId = 51536;
                        break;          // nightelf female
                    case 25358:
                        iTmpSpellId = 51535;
                        break;          // nightelf male
                    case 25368:
                        iTmpSpellId = 51544;
                        break;          // orc female
                    case 25364:
                        iTmpSpellId = 51543;
                        break;          // orc male
                    case 25371:
                        iTmpSpellId = 51548;
                        break;          // tauren female
                    case 25366:
                        iTmpSpellId = 51547;
                        break;          // tauren male
                    case 25370:
                        iTmpSpellId = 51545;
                        break;          // troll female
                    case 25365:
                        iTmpSpellId = 51546;
                        break;          // troll male
                    default:
                        return;
                    }

                    unitTarget->CastSpell(unitTarget, iTmpSpellId, true);
                    Creature* npc = unitTarget->ToCreature();
                    npc->LoadEquipment();
                    return;
                }
                // Emblazon Runeblade
                case 51770:
                {
                    if (!m_originalCaster)
                        return;

                    m_originalCaster->CastSpell(m_originalCaster, damage, false);
                    break;
                }
                // Deathbolt from Thalgran Blightbringer
                // reflected by Freya's Ward
                // Retribution by Sevenfold Retribution
                case 51854:
                {
                    if (!unitTarget)
                        return;
                    if (unitTarget->HasAura(51845))
                        unitTarget->CastSpell(m_caster, 51856, true);
                    else
                        m_caster->CastSpell(unitTarget, 51855, true);
                    break;
                }
                // Summon Ghouls On Scarlet Crusade
                case 51904:
                {
                    if (!m_targets.HasDst())
                        return;

                    float x, y, z;
                    float radius = m_spellInfo->Effects[effIndex].CalcRadius();
                    for (uint8 i = 0; i < 15; ++i)
                    {
                        m_caster->GetRandomPoint(*destTarget, radius, x, y, z);
                        m_caster->CastSpell(x, y, z, 54522, true);
                    }
                    break;
                }
                case 52173:          // Coyote Spirit Despawn
                case 60243:          // Blood Parrot Despawn
                {
                    if (unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->ToCreature()->isSummon())
                        unitTarget->ToTempSummon()->UnSummon();
                    return;
                }
                case 52479:          // Gift of the Harvester
                {
                    if (unitTarget && m_originalCaster)
                        m_originalCaster->CastSpell(unitTarget, urand(0, 1) ? damage : 52505, true);
                    return;
                }
                case 53110:          // Devour Humanoid
                {
                    if (unitTarget)
                        unitTarget->CastSpell(m_caster, damage, true);
                    return;
                }
                case 57347:          // Retrieving (Wintergrasp RP-GG pickup spell)
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->ToCreature()->DespawnOrUnsummon();
                    return;
                }
                case 57349:          // Drop RP-GG (Wintergrasp RP-GG at death drop spell)
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Delete item from inventory at death
                    m_caster->ToPlayer()->DestroyItemCount(damage, 5, true);
                    return;
                }
                case 58418:          // Portal to Orgrimmar
                case 58420:          // Portal to Stormwind
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER || effIndex != 0)
                        return;

                    uint32 spellID = m_spellInfo->Effects[EFFECT_0].CalcValue();
                    uint32 questID = m_spellInfo->Effects[EFFECT_1].CalcValue();

                    if (unitTarget->ToPlayer()->GetQuestStatus(questID) == QUEST_STATUS_COMPLETE)
                        unitTarget->CastSpell(unitTarget, spellID, true);
                    return;
                }
                case 58941:          // Rock Shards
                {
                    if (unitTarget && m_originalCaster)
                    {
                        for (uint32 i = 0; i < 3; ++i)
                        {
                            m_originalCaster->CastSpell(unitTarget, 58689, true);
                            m_originalCaster->CastSpell(unitTarget, 58692, true);
                        }
                        if (((InstanceMap*) m_originalCaster->GetMap())->GetDifficulty() == REGULAR_DIFFICULTY)
                        {
                            m_originalCaster->CastSpell(unitTarget, 58695, true);
                            m_originalCaster->CastSpell(unitTarget, 58696, true);
                        }
                        else
                        {
                            m_originalCaster->CastSpell(unitTarget, 60883, true);
                            m_originalCaster->CastSpell(unitTarget, 60884, true);
                        }
                    }
                    return;
                }
                case 58983:          // Big Blizzard Bear
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Prevent stacking of mounts and client crashes upon dismounting
                    unitTarget->RemoveAurasByType(SPELL_AURA_MOUNTED);

                    // Triggered spell id dependent on riding skill
                    if (uint16 skillval = unitTarget->ToPlayer()->GetSkillValue(SKILL_RIDING))
                    {
                        if (skillval >= 150)
                            unitTarget->CastSpell(unitTarget, 58999, true);
                        else
                            unitTarget->CastSpell(unitTarget, 58997, true);
                    }
                    return;
                }
                case 59317:          // Teleporting
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // return from top
                    if (unitTarget->ToPlayer()->GetAreaId() == 4637)
                        unitTarget->CastSpell(unitTarget, 59316, true);
                    // teleport atop
                    else
                        unitTarget->CastSpell(unitTarget, 59314, true);
                    return;
                }
                case 12355: // Impact
                {
                    if (!unitTarget || !m_caster)
                        return;

                    if (unitTarget->IsInWorld() && m_caster->IsInWorld())
                    {
                        if (Unit* stunned = m_targets.GetUnitTarget())
                        {
                            Unit::AuraEffectList const& dotList = stunned->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
                            if (dotList.empty())
                                return;

                            for (Unit::AuraEffectList::const_iterator itr = dotList.begin(); itr != dotList.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetCaster() && (*itr)->GetCaster()->IsInWorld())
                                {
                                    if ((*itr)->GetCaster()->GetGUID() == m_caster->GetGUID())
                                    {
                                        uint32 duration = (*itr)->GetBase()->GetDuration();
                                        uint32 spellId = (*itr)->GetId();
                                        int32 damage = (*itr)->GetAmount();

                                        if (spellId != 2120 && duration > 0 && damage > 0)
                                        {
                                            if (spellId == 92315 || spellId == 11366 || spellId == 44614)
                                                m_caster->AddAura(spellId, unitTarget);
                                            else
                                                m_caster->CastCustomSpell(unitTarget, spellId, &damage, NULL, NULL, true);

                                            if (Aura* aur = unitTarget->GetAura(spellId, m_caster->GetGUID()))
                                                aur->SetDuration(duration);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case 62482:          // Grab Crate
                {
                    if (unitTarget)
                    {
                        if (Unit* seat = m_caster->GetVehicleBase())
                        {
                            if (Unit* parent = seat->GetVehicleBase())
                            {
                                // TODO: a hack, range = 11, should after some time cast, otherwise too far
                                m_caster->CastSpell(parent, 62496, true);
                                unitTarget->CastSpell(parent, m_spellInfo->Effects[EFFECT_0].CalcValue());
                            }
                        }
                    }
                    return;
                }
                case 14181:         // Relentless Strikes
                {
                    m_caster->CastSpell(m_caster, 98440, true);
                    return;
                }
                case 60123:          // Lightwell
                {
                    if (m_caster->GetTypeId() != TYPEID_UNIT || !m_caster->ToCreature()->isSummon())
                        return;

                    uint32 spell_heal;
                    switch (m_caster->GetEntry())
                    {
                        case 31897:
                            spell_heal = 7001;
                            break;
                        case 31896:
                            spell_heal = 27873;
                            break;
                        case 31895:
                            spell_heal = 27874;
                            break;
                        case 31894:
                            spell_heal = 28276;
                            break;
                        case 31893:
                            spell_heal = 48084;
                            break;
                        case 31883:
                            spell_heal = 48085;
                            break;
                        default:
                            sLog->outError(LOG_FILTER_SPELLS_AURAS, "Unknown Lightwell spell caster %u", m_caster->GetEntry());
                            return;
                    }
                    // proc a spellcast
                    if (Aura* chargesAura = m_caster->GetAura(59907))
                    {
                        m_caster->CastSpell(unitTarget, spell_heal, true, NULL, NULL, m_caster->ToTempSummon()->GetSummonerGUID());
                        if (chargesAura->ModCharges(-1))
                            m_caster->ToTempSummon()->UnSummon();
                    }
                    return;
                }
                // Stoneclaw Totem
                case 55328:          // Rank 1
                case 55329:          // Rank 2
                case 55330:          // Rank 3
                case 55332:          // Rank 4
                case 55333:          // Rank 5
                case 55335:          // Rank 6
                case 55278:          // Rank 7
                case 58589:          // Rank 8
                case 58590:          // Rank 9
                case 58591:          // Rank 10
                {
                    int32 basepoints0 = damage;
                    // Cast Absorb on totems
                    for (uint8 slot = SUMMON_SLOT_TOTEM; slot < MAX_TOTEM_SLOT; ++slot)
                    {
                        if (!unitTarget->m_SummonSlot[slot])
                            continue;

                        Creature* totem = unitTarget->GetMap()->GetCreature(unitTarget->m_SummonSlot[slot]);
                        if (totem && totem->isTotem())
                        {
                            m_caster->CastCustomSpell(totem, 55277, &basepoints0, NULL, NULL, true);
                        }
                    }
                    // Glyph of Stoneclaw Totem
                    if (AuraEffect* aur = unitTarget->GetAuraEffect(63298, 0))
                    {
                        basepoints0 *= aur->GetAmount();
                        m_caster->CastCustomSpell(unitTarget, 55277, &basepoints0, NULL, NULL, true);
                    }
                    break;
                }
                case 66545:          //Summon Memory
                {
                    uint8 uiRandom = urand(0, 25);
                    uint32 uiSpells[26] =
                    { 66704, 66705, 66706, 66707, 66709, 66710, 66711, 66712, 66713, 66714, 66715, 66708, 66708, 66691, 66692, 66694, 66695, 66696, 66697, 66698, 66699, 66700, 66701, 66702, 66703, 66543 };

                    m_caster->CastSpell(m_caster, uiSpells[uiRandom], true);
                    break;
                }
                case 45668:          // Ultra-Advanced Proto-Typical Shortening Blaster
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    if (roll_chance_i(50))          // chance unknown, using 50
                        return;

                    static uint32 const spellPlayer[5] =
                    {
                        45674,          // Bigger!
                        45675,          // Shrunk
                        45678,          // Yellow
                        45682,          // Ghost
                        45684           // Polymorph
                    };

                    static uint32 const spellTarget[5] =
                    {
                        45673,          // Bigger!
                        45672,          // Shrunk
                        45677,          // Yellow
                        45681,          // Ghost
                        45683           // Polymorph
                    };

                    m_caster->CastSpell(m_caster, spellPlayer[urand(0, 4)], true);
                    unitTarget->CastSpell(unitTarget, spellTarget[urand(0, 4)], true);
                    break;
                }
                case 65731:     // The Last Stand: Quest Complete
                {
                    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                        unitTarget->RemoveAurasDueToSpell(65727);
                    break;
                }
                case 64578:     // Return Fire: Quest Complete
                {
                    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                        unitTarget->RemoveAurasDueToSpell(64572);
                    break;
                }
                case 65465:     // Defend the Tree!: Quest Completion - Exit Shade of Shadumbra
                {
                    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                        unitTarget->RemoveAurasDueToSpell(65396);
                    break;
                }
                case 79436:     // Wake Harvest Golem
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->ToCreature())
                    {
                        if (!unitTarget)
                            return;

                        m_caster->CastSpell(unitTarget, 89202, true);
                        m_caster->SummonCreature(42601, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(), unitTarget->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                        unitTarget->ToCreature()->DespawnOrUnsummon(1000);
                        m_caster->ToPlayer()->KilledMonsterCredit(42601);
                    }
                    break;
                }
                case 80814:     // Backdoor Dealings: Force Summon Wings of Hir'eek and Credit
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->CastSpell(m_caster, 80789, true);
                    break;
                }
                case 88763:     // Despawn All Summons
                {
                    if (!m_caster)
                        return;

                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(m_caster, m_caster, 500.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(m_caster, targets, u_check);
                    m_caster->VisitNearbyObject(500.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == m_caster))
                        {
                            // Hungry Mine Creeper
                            if ((*itr)->ToTempSummon()->GetEntry() == 47662)
                                (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                            // Johnny and Lyadon
                            if ((*itr)->ToTempSummon()->GetEntry() == 48020 || (*itr)->ToTempSummon()->GetEntry() == 48021)
                                (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                        }
                    }
                    // Hungry Mine Creeper Aura
                    if (m_caster->HasAura(88762))
                        m_caster->RemoveAurasDueToSpell(88762);
                    // Lethality Analizer
                    if (m_caster->HasAura(88375))
                        m_caster->RemoveAurasDueToSpell(88375);
                    break;
                }
                case 88794:     // Despawn All Summons
                {
                    if (!m_caster)
                        return;

                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(m_caster, m_caster, 100.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(m_caster, targets, u_check);
                    m_caster->VisitNearbyObject(100.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == m_caster))
                        {
                            // Captured Hillsbrad Human
                            if ((*itr)->ToTempSummon()->GetEntry() == 47694)
                                (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                        }
                    }
                    break;
                }
                case 90414:     // Despawn All Summons
                {
                    if (!m_caster)
                        return;

                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(m_caster, 1000.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(m_caster, targets, u_check);
                    m_caster->VisitNearbyObject(1000.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == m_caster))
                        {
                            // Purgation Isle
                            switch ((*itr)->ToTempSummon()->GetEntry())
                            {
                                case 48503:
                                case 48504:
                                case 48507:
                                case 48508:
                                case 48515:
                                case 48485:
                                case 48557:
                                case 48470:
                                    (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    break;
                }
                case 82580: // Bravo Company Field Kit
                {
                    if (!m_caster)
                        return;

                    m_caster->MonsterWhisper("Bravo Company Field Kit ACTIVE. New abilities are now available on your action bar. Toggle Bravo Company Field Kit to DEACTIVATE.", m_caster->GetGUID(), true);
                    break;
                }
                case 82587: // Bravo Company Field Kit (2)
                {
                    if (!m_caster)
                        return;

                    m_caster->MonsterWhisper("Bravo Company Field Kit ACTIVE. Plant Seaforium is now available on your action bar. Toggle Bravo Company Field Kit to DEACTIVATE.", m_caster->GetGUID(), true);
                    break;
                }
                case 87743: // Shrink the World
                {
                    // Check for aura stacks
                    int8 stacks = 4;
                    if (Aura* aur = m_caster->GetAura(87743, m_caster->GetGUID()))
                    {
                        if (aur->GetStackAmount() > stacks)
                        {
                            // Add Quest Credit for ID: 27714
                            if (Vehicle* vehicle = m_caster->GetVehicleKit())
                            {
                                for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                                    if (Player* player = ObjectAccessor::FindPlayer(itr->second.Passenger.Guid))
                                        player->KilledMonsterCredit(47080);
                            }
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            // chimera shot health effect + serpent sting refresh
            if (m_spellInfo->SpellFamilyFlags[2] & 0x1)
            {
                m_caster->CastSpell(m_caster, 53353, true);
                if (unitTarget->GetAura(1978))
                    unitTarget->GetAura(1978)->RefreshDuration();
            }
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            // Cremation (Script Effect)
            if (m_spellInfo->Id == 89603)
            {
                // Check for Immolate aura
                if (Aura* immolate = unitTarget->GetAura(348, m_caster->GetGUID()))
                {
                    // Cremation
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_WARLOCK, 5006, 1))
                    {
                        switch (aurEff->GetId())
                        {
                            case 85103: // Rank 1
                            {
                                if (roll_chance_f(50.0f))
                                    immolate->RefreshDuration();
                                break;
                            }
                            case 85104: // Rank 2
                            {
                                immolate->RefreshDuration();
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
            break;
        }
        case SPELLFAMILY_MAGE:
        {
            // Combustion
            if (m_spellInfo->Id == 11129)
            {
                int32 bonus = 0;
                Unit::AuraEffectList const &checkPE = unitTarget->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
                for (Unit::AuraEffectList::const_iterator i = checkPE.begin(); i != checkPE.end(); ++i)
                    if ((*i)->GetCasterGUID() == m_caster->GetGUID())
                        bonus += (*i)->GetAmount();
                m_caster->CastCustomSpell(unitTarget, 83853, &bonus, NULL, NULL, true);
            }
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            // Empowered Touch (Script Effect)
            if (m_spellInfo->Id == 88433)
            {
                if (unitTarget && m_caster)
                {
                    // Empowered Touch (Talent)
                    if (AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 2251, EFFECT_1))
                    {
                        // Check for Lifebloom
                        Aura* lifeBloom = unitTarget->GetAura(33763, m_caster->GetGUID());
                        Aura* lifeBloomToL = unitTarget->GetAura(94447, m_caster->GetGUID());
                        if (roll_chance_i(aurEff->GetAmount()))
                        {
                            if (lifeBloom && !lifeBloomToL)
                            {
                                lifeBloom->RefreshDuration();
                                // Revitalize
                                if (m_caster->HasAura(48539) || m_caster->HasAura(48544))
                                    m_caster->CastSpell(m_caster, 57669, true);
                            }
                            else if (lifeBloomToL && !lifeBloom)
                            {
                                lifeBloomToL->RefreshDuration();
                                // Revitalize
                                if (m_caster->HasAura(48539) || m_caster->HasAura(48544))
                                    m_caster->CastSpell(m_caster, 57669, true);
                            }
                            /* Empowered Touch now also affects Regrowth. In addition, after Tree of Life is no longer active, this talent will only
                               refresh the most recently cast or refreshed Lifebloom, and will not refresh other copies of Lifebloom. */
                            else if (lifeBloomToL && lifeBloom)
                            {
                                if (lifeBloomToL->GetDuration() >= lifeBloom->GetDuration())
                                    lifeBloomToL->RefreshDuration();
                                if (lifeBloom->GetDuration() >= lifeBloomToL->GetDuration())
                                    lifeBloom->RefreshDuration();
                            }
                        }
                    }
                }
            }
            break;
        }
        case SPELLFAMILY_WARRIOR:
        {
            // Shattering Throw
            if (m_spellInfo->SpellFamilyFlags[1] & 0x00400000)
            {
                if (!unitTarget)
                    return;

                // Remove Immunities
                unitTarget->RemoveAurasDueToSpell(642);     // Divine Shield
                unitTarget->RemoveAurasDueToSpell(1022);    // Hand of Protection rank 1
                unitTarget->RemoveAurasDueToSpell(45438);   // Ice Block
                return;
            }
            break;
        }
        case SPELLFAMILY_DEATHKNIGHT:
        {
            switch (m_spellInfo->Id)
            {
                // Pestilence
                case 50842:
                {
                    if (m_spellInfo->SpellFamilyFlags[1] & 0x10000)
                    {
                        // Get diseases on target of spell
                        if (m_targets.GetUnitTarget() && (m_targets.GetUnitTarget() != unitTarget))
                        {
                            AuraEffect* aurEff = m_caster->GetAuraEffect(SPELL_AURA_ADD_PCT_MODIFIER, SPELLFAMILY_DEATHKNIGHT, 97, EFFECT_0);
                            int32 bp0 = aurEff ? (aurEff->GetAmount()) : 0;

                            // Blood Plague
                            if (AuraEffect* bloodPlague = m_targets.GetUnitTarget()->GetAuraEffect(55078, EFFECT_0, m_caster->GetGUID()))
                            {
                                bp0 += bp0 * bloodPlague->GetAmount() / 100;
                                m_caster->CastCustomSpell(unitTarget, 55078, &bp0, NULL, NULL, true);
                            }
                            // Frost Fever
                            if (AuraEffect* frostFever = m_targets.GetUnitTarget()->GetAuraEffect(55095, EFFECT_0, m_caster->GetGUID()))
                            {
                                bp0 += bp0 * frostFever->GetAmount() / 100;
                                m_caster->CastCustomSpell(unitTarget, 55095, &bp0, NULL, NULL, true);
                            }
                            // Ebon Plague
                            if (AuraEffect* ebonPlague = m_targets.GetUnitTarget()->GetAuraEffect(65142, EFFECT_0, m_caster->GetGUID()))
                                m_caster->CastSpell(unitTarget, 65142, true);

                            // Spread visual effect!
                            m_caster->CastSpell(unitTarget, 91939, true);
                        }
                    }
                    break;
                }
                // Festering Strike
                case 85948:
                {
                    if (!unitTarget || !m_caster)
                        return;

                    // Chains of Ice
                    if (unitTarget->HasAura(45524, m_caster->GetGUID()))
                    {
                        if (Aura* coi = unitTarget->GetAura(45524, m_caster->GetGUID()))
                        {
                            if (coi->GetDuration() >= (coi->GetMaxDuration()+6000))
                                coi->SetDuration(coi->GetMaxDuration()+6000);
                            else
                                coi->SetDuration(coi->GetDuration()+6000);
                        }
                    }
                    // Frost Fever
                    if (unitTarget->HasAura(55095, m_caster->GetGUID()))
                    {
                        if (Aura* ff = unitTarget->GetAura(55095, m_caster->GetGUID()))
                        {
                            if (ff->GetDuration() >= (ff->GetMaxDuration()+6000))
                                ff->SetDuration(ff->GetMaxDuration()+6000);
                            else
                                ff->SetDuration(ff->GetDuration()+6000);
                        }
                    }
                    // Blood Plague
                    if (unitTarget->HasAura(55078, m_caster->GetGUID()))
                    {
                        if (Aura* bp = unitTarget->GetAura(55078))
                        {
                            if (bp->GetDuration() >= (bp->GetMaxDuration()+6000))
                                bp->SetDuration(bp->GetMaxDuration()+6000);
                            else
                                bp->SetDuration(bp->GetDuration()+6000);
                        }
                    }
                    // Ebon Plague
                    if (unitTarget->HasAura(65142, m_caster->GetGUID()))
                    {
                        if (Aura* bp = unitTarget->GetAura(65142, m_caster->GetGUID()))
                        {
                            if (bp->GetDuration() >= (bp->GetMaxDuration() + 6000))
                                bp->SetDuration(bp->GetMaxDuration() + 6000);
                            else
                                bp->SetDuration(bp->GetDuration() + 6000);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    // normal DB scripted effect
    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell ScriptStart spellid %u in EffectScriptEffect(%u)", m_spellInfo->Id, effIndex);
    m_caster->GetMap()->ScriptsStart(sSpellScripts, uint32(m_spellInfo->Id | (effIndex << 24)), m_caster, unitTarget);
}

void Spell::EffectSanctuary (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    unitTarget->getHostileRefManager().UpdateVisibility();

    Unit::AttackerSet const& attackers = unitTarget->getAttackers();
    for (Unit::AttackerSet::const_iterator itr = attackers.begin(); itr != attackers.end();)
    {
        if (!(*itr)->canSeeOrDetect(unitTarget))
            (*(itr++))->AttackStop();
        else
            ++itr;
    }

    unitTarget->m_lastSanctuaryTime = getMSTime();

    // Vanish allows to remove all threat and cast regular stealth so other spells can be used
    if (m_caster->GetTypeId() == TYPEID_PLAYER && m_spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE && (m_spellInfo->SpellFamilyFlags[0] & SPELLFAMILYFLAG_ROGUE_VANISH))
    {
        m_caster->ToPlayer()->RemoveAurasByType(SPELL_AURA_MOD_ROOT);
        // Overkill
        if (m_caster->ToPlayer()->HasSpell(58426))
            m_caster->CastSpell(m_caster, 58427, true);
    }
}

void Spell::EffectAddComboPoints (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    if (!m_caster->m_movedPlayer)
        return;

    Player* player = m_caster->m_movedPlayer;

    if (damage <= 0)
    {
        // Redirect
        if (GetSpellInfo()->Id == 73981 && player->GetComboPoints() > 0 && player->GetComboTarget())
        {
            if (unitTarget && (player->GetComboTarget() != unitTarget->GetGUID()))
                player->AddComboPoints(unitTarget, player->GetComboPoints(), this);
        }
        else
        {
            // Effect negated, reset counter and cleanup buffs (Bandit's Guile)
            m_caster->RemoveAurasDueToSpell(84745); // Shallow Insight
            m_caster->RemoveAurasDueToSpell(84746); // Moderate Insight
            m_caster->RemoveAurasDueToSpell(84747); // Deep Insight
            m_caster->m_bGuilesCount = 0;
        }
    }
    else
    {
        player->AddComboPoints(unitTarget, damage, this);
        // Sinister Strike and Revealing Strike
        if (m_spellInfo->Id == 1752 || m_spellInfo->Id == 84617)
        {
            m_caster->m_bGuilesCount += m_caster->GetTimesCastedInRow(1752);
            m_caster->m_bGuilesCount += m_caster->GetTimesCastedInRow(84617);

            // We have the last effect active, wait for it's end before restar counter
            if (m_caster->HasAura(84747))
                return;

            // Bandit's Guile Rank 1
            if (m_caster->HasAura(84652) && roll_chance_i(33))
                ++m_caster->m_bGuilesCount;
            // Bandit's Guile Rank 2
            else if (m_caster->HasAura(84653) && roll_chance_i(66))
                    ++m_caster->m_bGuilesCount;
            // Bandit's Guile Rank 3
            else if (m_caster->HasAura(84654))
                ++m_caster->m_bGuilesCount;

            switch (m_caster->m_bGuilesCount)
            {
                if (!unitTarget)
                    return;

                case 4: // 4 Hits
                {
                    // Shallow Insight
                    unitTarget->AddAura(84745, m_caster);
                    break;
                }
                case 8: // 8 Hits
                {
                    // Moderate Insight
                    unitTarget->AddAura(84746, m_caster);
                    // Found previous effect, cleanup!
                    if (m_caster->HasAura(84745))
                        m_caster->RemoveAurasDueToSpell(84745);
                    break;
                }
                case 12: // 12 Hits
                {
                    // Deep Insight
                    unitTarget->AddAura(84747, m_caster);
                    // Found previous effect, cleanup!
                    if (m_caster->HasAura(84746))
                        m_caster->RemoveAurasDueToSpell(84746);
                    // Reset the counter!!
                    m_caster->m_bGuilesCount = 0;
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void Spell::EffectDuel (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || m_caster->GetTypeId() != TYPEID_PLAYER || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* caster = m_caster->ToPlayer();
    Player* target = unitTarget->ToPlayer();

    // caster or target already have requested duel
    if (caster->duel || target->duel || !target->GetSocial() || target->GetSocial()->HasIgnore(caster->GetGUIDLow()))
        return;

    // Players can only fight a duel in zones with this flag
    AreaTableEntry const* casterAreaEntry = GetAreaEntryByAreaID(caster->GetAreaId());
    if (casterAreaEntry && !(casterAreaEntry->flags & AREA_FLAG_ALLOW_DUELS))
    {
        SendCastResult(SPELL_FAILED_NO_DUELING);          // Dueling isn't allowed here
        return;
    }

    AreaTableEntry const* targetAreaEntry = GetAreaEntryByAreaID(target->GetAreaId());
    if (targetAreaEntry && !(targetAreaEntry->flags & AREA_FLAG_ALLOW_DUELS))
    {
        SendCastResult(SPELL_FAILED_NO_DUELING);          // Dueling isn't allowed here
        return;
    }

    //CREATE DUEL FLAG OBJECT
    GameObject* pGameObj = new GameObject;

    uint32 gameobject_id = m_spellInfo->Effects[effIndex].MiscValue;

    Map* map = m_caster->GetMap();
    if (!pGameObj->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), gameobject_id,
    map, m_caster->GetPhaseMask(),
    m_caster->GetPositionX()+(unitTarget->GetPositionX()-m_caster->GetPositionX())/2,
    m_caster->GetPositionY()+(unitTarget->GetPositionY()-m_caster->GetPositionY())/2,
    m_caster->GetPositionZ(),
    m_caster->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
    {
        delete pGameObj;
        return;
    }

    pGameObj->SetUInt32Value(GAMEOBJECT_FACTION, m_caster->getFaction());
    pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel() + 1);
    int32 duration = m_spellInfo->GetDuration();
    pGameObj->SetRespawnTime(duration > 0 ? duration / IN_MILLISECONDS : 0);
    pGameObj->SetSpellId(m_spellInfo->Id);

    ExecuteLogEffectSummonObject(effIndex, pGameObj);

    m_caster->AddGameObject(pGameObj);
    map->AddToMap(pGameObj);
    //END

    // Send request
    WorldPacket data(SMSG_DUEL_REQUESTED, 8 + 8);
    data << uint64(pGameObj->GetGUID());
    data << uint64(caster->GetGUID());
    caster->GetSession()->SendPacket(&data);
    target->GetSession()->SendPacket(&data);

    // create duel-info
    DuelInfo* duel = new DuelInfo;
    duel->initiator = caster;
    duel->opponent = target;
    duel->startTime = 0;
    duel->startTimer = 0;
    duel->isMounted = (GetSpellInfo()->Id == 62875);          // Mounted Duel
    caster->duel = duel;

    DuelInfo* duel2 = new DuelInfo;
    duel2->initiator = caster;
    duel2->opponent = caster;
    duel2->startTime = 0;
    duel2->startTimer = 0;
    duel2->isMounted = (GetSpellInfo()->Id == 62875);          // Mounted Duel
    target->duel = duel2;

    caster->SetUInt64Value(PLAYER_DUEL_ARBITER, pGameObj->GetGUID());
    target->SetUInt64Value(PLAYER_DUEL_ARBITER, pGameObj->GetGUID());

    sScriptMgr->OnPlayerDuelRequest(target, caster);
}

void Spell::EffectStuck (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (!m_caster || m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    if (!sWorld->getBoolConfig(CONFIG_CAST_UNSTUCK))
    return;

    Player* target = (Player*) m_caster;

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell Effect: Stuck");
    sLog->outInfo(LOG_FILTER_SPELLS_AURAS, "Player %s (guid %u) used auto-unstuck future at map %u (%f, %f, %f)", target->GetName().c_str(), target->GetGUIDLow(), m_caster->GetMapId(), m_caster->GetPositionX(), target->GetPositionY(), target->GetPositionZ());

    if (target->isInFlight())
        return;

    // if player is dead without death timer is teleported to graveyard, otherwise not apply the effect
    if (target->isDead())
    {
        if (!target->GetDeathTimer())
            target->RepopAtGraveyard();

        return;
    }

    // the player dies
    target->Kill(target);

    // Stuck spell trigger Hearthstone cooldown
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(8690);
    if (!spellInfo)
        return;
    Spell spell(target, spellInfo, TRIGGERED_FULL_MASK);
    spell.SendSpellCooldown();
}

void Spell::EffectSummonPlayer (SpellEffIndex /*effIndex*/)
{
    // workaround - this effect should not use target map
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    // Evil Twin (ignore player summon, but hide this for summoner)
    if (unitTarget->HasAura(23445))
        return;

    float x, y, z;
    m_caster->GetPosition(x, y, z);

    unitTarget->ToPlayer()->SetSummonPoint(m_caster->GetMapId(), x, y, z);

    WorldPacket data(SMSG_SUMMON_REQUEST, 8 + 4 + 4);
    data << uint64(m_caster->GetGUID());          // summoner guid
    data << uint32(m_caster->GetZoneId());          // summoner zone
    data << uint32(MAX_PLAYER_SUMMON_DELAY * IN_MILLISECONDS);          // auto decline after msecs
    unitTarget->ToPlayer()->GetSession()->SendPacket(&data);
}

void Spell::EffectActivateObject (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!gameObjTarget)
        return;

    ScriptInfo activateCommand;
    activateCommand.command = SCRIPT_COMMAND_ACTIVATE_OBJECT;

    // int32 unk = m_spellInfo->Effects[effIndex].MiscValue; // This is set for EffectActivateObject spells; needs research

    gameObjTarget->GetMap()->ScriptCommandStart(activateCommand, 0, m_caster, gameObjTarget);
}

void Spell::EffectApplyGlyph (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER || m_glyphIndex >= MAX_GLYPH_SLOT_INDEX)
        return;

    Player* player = (Player*) m_caster;

    // glyph sockets level requirement
    uint8 minLevel = 0;
    switch (m_glyphIndex)
    {
    case 0:
    case 1:
    case 6:
        minLevel = 25;
        break;
    case 2:
    case 3:
    case 7:
        minLevel = 50;
        break;
    case 4:
    case 5:
    case 8:
        minLevel = 75;
        break;
    }

    if (minLevel && m_caster->getLevel() < minLevel)
    {
        SendCastResult(SPELL_FAILED_GLYPH_SOCKET_LOCKED);
        return;
    }

    // apply new one
    if (uint32 newGlyph = m_spellInfo->Effects[effIndex].MiscValue)
    {
        if (GlyphPropertiesEntry const* newGlyphProperties = sGlyphPropertiesStore.LookupEntry(newGlyph))
        {
            if (GlyphSlotEntry const* newGlyphSlot = sGlyphSlotStore.LookupEntry(player->GetGlyphSlot(m_glyphIndex)))
            {
                if (newGlyphProperties->TypeFlags != newGlyphSlot->TypeFlags)
                {
                    SendCastResult(SPELL_FAILED_INVALID_GLYPH);
                    return;          // glyph slot mismatch
                }
            }

            // remove old glyph
            if (uint32 oldGlyph = player->GetGlyph(player->GetActiveSpec(), m_glyphIndex))
            {
                if (GlyphPropertiesEntry const* oldGlyphProperties = sGlyphPropertiesStore.LookupEntry(oldGlyph))
                {
                    player->RemoveAurasDueToSpell(oldGlyphProperties->SpellId);
                    player->SetGlyph(m_glyphIndex, 0);
                }
            }

            player->CastSpell(m_caster, newGlyphProperties->SpellId, true);
            player->SetGlyph(m_glyphIndex, newGlyph);
            player->SendTalentsInfoData(false);
        }
    }
    else if (uint32 oldGlyph = player->GetGlyph(player->GetActiveSpec(), m_glyphIndex)) // Removing the glyph, get the old one
    {
        if (GlyphPropertiesEntry const* oldGlyphProperties = sGlyphPropertiesStore.LookupEntry(oldGlyph))
        {
            player->RemoveAurasDueToSpell(oldGlyphProperties->SpellId);
            player->SetGlyph(m_glyphIndex, 0);
            player->SendTalentsInfoData(false);
        }
    }
}

void Spell::EffectEnchantHeldItem (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    // this is only item spell effect applied to main-hand weapon of target player (players in area)
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* item_owner = unitTarget->ToPlayer();
    Item* item = item_owner->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

    if (!item)
        return;

    // must be equipped
    if (!item->IsEquipped())
        return;

    if (m_spellInfo->Effects[effIndex].MiscValue)
    {
        uint32 enchant_id = m_spellInfo->Effects[effIndex].MiscValue;
        int32 duration = m_spellInfo->GetDuration();          //Try duration index first ..
        if (!duration)
            duration = damage;          //+1;            //Base points after ..
        if (!duration)
            duration = 10;          //10 seconds for enchants which don't have listed duration

        SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
        if (!pEnchant)
            return;

        // Always go to temp enchantment slot
        EnchantmentSlot slot = TEMP_ENCHANTMENT_SLOT;

        // Enchantment will not be applied if a different one already exists
        if (item->GetEnchantmentId(slot) && item->GetEnchantmentId(slot) != enchant_id)
            return;

        // Apply the temporary enchantment
        item->SetEnchantment(slot, enchant_id, duration*IN_MILLISECONDS, 0, m_caster->GetGUID());
        item_owner->ApplyEnchantment(item, slot, true);
    }
}

void Spell::EffectDisEnchant (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!itemTarget || !itemTarget->GetTemplate()->DisenchantID)
        return;

    if (Player* caster = m_caster->ToPlayer())
    {
        caster->UpdateCraftSkill(m_spellInfo->Id);
        caster->SendLoot(itemTarget->GetGUID(), LOOT_DISENCHANTING);
    }

    // item will be removed at disenchanting end
}

void Spell::EffectInebriate (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = unitTarget->ToPlayer();
    uint8 currentDrunk = player->GetDrunkValue();
    uint8 drunkMod = damage;
    if (currentDrunk + drunkMod > 100)
    {
        currentDrunk = 100;
        if (rand_chance() < 25.0f)
            player->CastSpell(player, 67468, false);          // Drunken Vomit
    }
    else
        currentDrunk += drunkMod;

    switch (m_spellInfo->Id)
    {
        case 87648: // Starfire Espresso
            player->SetDrunkValue(0);
            break;
        default:
            player->SetDrunkValue(currentDrunk, m_CastItem ? m_CastItem->GetEntry() : 0);
            break;
    }
}

void Spell::EffectFeedPet (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    Player* player = m_caster->ToPlayer();
    if (!player)
        return;

    Item* foodItem = itemTarget;
    if (!foodItem)
        return;

    Pet* pet = player->GetPet();
    if (!pet)
        return;

    if (!pet->isAlive())
        return;

    int32 benefit = pet->GetCurrentFoodBenefitLevel(foodItem->GetTemplate()->ItemLevel);
    if (benefit <= 0)
        return;

    ExecuteLogEffectDestroyItem(effIndex, foodItem->GetEntry());

    uint32 count = 1;
    player->DestroyItemCount(foodItem, count, true);
    // TODO: fix crash when a spell has two effects, both pointed at the same item target

    m_caster->CastCustomSpell(pet, m_spellInfo->Effects[effIndex].TriggerSpell, &benefit, NULL, NULL, true);
}

void Spell::EffectDismissPet (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isPet())
        return;

    Player* owner = NULL;
    if (m_originalCaster)
    {
        owner = m_originalCaster->ToPlayer();
        if (!owner && m_originalCaster->ToCreature()->isTotem())
            owner = m_originalCaster->GetCharmerOrOwnerPlayerOrPlayerItself();
    }

    Pet* pet = unitTarget->ToPet();

    ExecuteLogEffectUnsummonObject(effIndex, pet);
    pet->GetOwner()->RemoveCurrentPet();

    // Camouflage
    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        if (m_caster->getClass() == CLASS_HUNTER)
            if (m_caster->HasAuraType(SPELL_AURA_MOD_CAMOUFLAGE))
                m_caster->RemoveAurasByType(SPELL_AURA_MOD_CAMOUFLAGE);
}

void Spell::EffectSummonObject (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    uint32 go_id = m_spellInfo->Effects[effIndex].MiscValue;

    uint8 slot = 0;
    switch (m_spellInfo->Effects[effIndex].Effect)
    {
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT1:
            slot = 0;
            break;
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT2:
            slot = 1;
            break;
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT3:
            slot = 2;
            break;
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT4:
            slot = 3;
            break;
        default:
            return;
    }

    uint64 guid = m_caster->m_ObjectSlot[slot];
    if (guid != 0)
    {
        GameObject* obj = NULL;
        if (m_caster)
            obj = m_caster->GetMap()->GetGameObject(guid);

        if (obj)
        {
            // Recast case - null spell id to make auras not be removed on object remove from world
            if (m_spellInfo->Id == obj->GetSpellId())
                obj->SetSpellId(0);

            if (m_spellInfo->SpellFamilyName != SPELLFAMILY_HUNTER)
                m_caster->RemoveGameObject(obj, true);
        }
        m_caster->m_ObjectSlot[slot] = 0;
    }

    GameObject* pGameObj = new GameObject;

    float x, y, z;
    // If dest location if present
    if (m_targets.HasDst())
        destTarget->GetPosition(x, y, z);
    // Summon in random point all other units if location present
    else
        m_caster->GetClosePoint(x, y, z, DEFAULT_WORLD_OBJECT_SIZE);

    Map* map = m_caster->GetMap();
    if (!pGameObj->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), go_id, map,
        m_caster->GetPhaseMask(), x, y, z, m_caster->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
    {
        delete pGameObj;
        return;
    }

    //pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel());
    int32 duration = m_spellInfo->GetDuration();
    pGameObj->SetRespawnTime(duration > 0 ? duration / IN_MILLISECONDS : 0);
    pGameObj->SetSpellId(m_spellInfo->Id);
    m_caster->AddGameObject(pGameObj);

    ExecuteLogEffectSummonObject(effIndex, pGameObj);

    map->AddToMap(pGameObj);

    m_caster->m_ObjectSlot[slot] = pGameObj->GetGUID();
}

void Spell::EffectSurvey (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH)
        return;

    if (!m_caster || m_spellInfo->Id != uint32(80451) || effIndex != EFFECT_0)
        return;

    if (Player *player = m_caster->ToPlayer())
        if (player->HasSkill(SKILL_ARCHAEOLOGY))
            player->SurveyDigSite();
}

void Spell::EffectRaidMarker (SpellEffIndex effIndex)
{
    Player* player = NULL;
    Group* group = NULL;

    if (!(player = m_caster->ToPlayer()))
        return;

    if (!(group = player->GetGroup()))
        return;

    Position pos;
    m_targets.GetDstPos()->GetPosition(&pos);

    switch (m_spellInfo->Id)
    {
        case 84996:          //RaidMarker 1
            group->SetMarker(1, pos, m_caster, GetSpellInfo());
            break;
        case 84997:          //RaidMarker 2
            group->SetMarker(2, pos, m_caster, GetSpellInfo());
            break;
        case 84998:          //RaidMarker 3
            group->SetMarker(3, pos, m_caster, GetSpellInfo());
            break;
        case 84999:          //RaidMarker 4
            group->SetMarker(4, pos, m_caster, GetSpellInfo());
            break;
        case 85000:          //RaidMarker 5
            group->SetMarker(5, pos, m_caster, GetSpellInfo());
            break;
        default:
            break;
    }
}

void Spell::EffectResurrect (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    if (unitTarget->isAlive() || !unitTarget->IsInWorld())
        return;

    Player* target = unitTarget->ToPlayer();

    if (target->IsRessurectRequested())          // already have one active request
        return;

    uint32 health = target->CountPctFromMaxHealth(damage);
    uint32 mana = CalculatePct(target->GetMaxPower(POWER_MANA), damage);

    // The Quick and the Dead
    if (m_caster && m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        if (m_caster->ToPlayer()->GetGuild())
            if (m_caster->ToPlayer()->GetGuildId() == target->ToPlayer()->GetGuildId())
                if (target->HasAura(83950))
                    AddPct(health, 50);
    }

    // Battle Ress System
    switch (m_spellInfo->Id)
    {
        case 20484: // Rebirth
        case 61999: // Raise Ally
        {
            // Players only!
            if (m_caster->GetTypeId() != TYPEID_PLAYER)
                break;

            Player* caster = m_caster->ToPlayer();
            if (!caster)
                break;

            if (!caster->GetInstanceScript())
                break;

            if (caster->GetMap()->GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL || caster->GetMap()->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC)
            {
                if (caster->m_bressCount > 0 && caster->GetInstanceScript()->IsEncounterInProgress())
                {
                    caster->GetSession()->SendNotification("You can no longer resurrect during combat!");
                    caster->RemoveSpellCooldown(m_spellInfo->Id, true);

                    // Rebirth (Maple Seed)
                    if (m_spellInfo->Id == 20484)
                        caster->AddItem(17034, 1);
                    return;
                }
                else
                {
                    if (caster->GetInstanceScript()->IsEncounterInProgress())
                        caster->m_bressCount++;
                }
            }

            if (caster->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || caster->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
            {
                if (caster->m_bressCount > 2 && caster->GetInstanceScript()->IsEncounterInProgress())
                {
                    caster->GetSession()->SendNotification("You can no longer resurrect during combat!");
                    caster->RemoveSpellCooldown(m_spellInfo->Id, true);

                    // Rebirth (Maple Seed)
                    if (m_spellInfo->Id == 20484)
                        caster->AddItem(17034, 1);
                    return;
                }
                else
                {
                    if (caster->GetInstanceScript()->IsEncounterInProgress())
                        caster->m_bressCount++;
                }
            }
            break;
        }
        default:
            break;
    }

    ExecuteLogEffectResurrect(effIndex, target);

    target->SetResurrectRequestData(m_caster, health, mana, 0);
    SendResurrectRequest(target);
}

void Spell::EffectAddExtraAttacks (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || !unitTarget->isAlive() || !unitTarget->getVictim())
        return;

    if (unitTarget->m_extraAttacks)
        return;

    unitTarget->m_extraAttacks = damage;

    ExecuteLogEffectExtraAttacks(effIndex, unitTarget->getVictim(), damage);
}

void Spell::EffectParry (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        m_caster->ToPlayer()->SetCanParry(true);
}

void Spell::EffectBlock (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        m_caster->ToPlayer()->SetCanBlock(true);
}

void Spell::EffectLeap (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->isInFlight())
        return;

    if (!m_targets.HasDst())
        return;

    Position pos;
    destTarget->GetPosition(&pos);
    unitTarget->GetFirstCollisionPosition(pos, unitTarget->GetDistance(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 2.0f), 0.0f);
    unitTarget->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), unitTarget == m_caster);
}

void Spell::EffectReputation (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = unitTarget->ToPlayer();

    int32 repChange = damage;

    uint32 factionId = m_spellInfo->Effects[effIndex].MiscValue;

    FactionEntry const* factionEntry = sFactionStore.LookupEntry(factionId);
    if (!factionEntry)
        return;

    repChange = player->CalculateReputationGain(REPUTATION_SOURCE_SPELL, 0, repChange, factionId);

    player->GetReputationMgr().ModifyReputation(factionEntry, repChange);
}

void Spell::EffectQuestComplete (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* player = unitTarget->ToPlayer();

    uint32 questId = m_spellInfo->Effects[effIndex].MiscValue;
    if (questId)
    {
        Quest const* quest = sObjectMgr->GetQuestTemplate(questId);
        if (!quest)
        return;

        uint16 logSlot = player->FindQuestSlot(questId);
        if (logSlot < MAX_QUEST_LOG_SIZE)
        player->AreaExploredOrEventHappens(questId);
        else if (player->CanTakeQuest(quest, false))          // never rewarded before
        player->CompleteQuest(questId);// quest not in log - for internal use
    }
}

void Spell::EffectForceDeselect (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    WorldPacket data(SMSG_CLEAR_TARGET, 8);
    data << uint64(m_caster->GetGUID());
    m_caster->SendMessageToSet(&data, true);
}

void Spell::EffectSelfResurrect (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (!m_caster || m_caster->isAlive())
        return;
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    if (!m_caster->IsInWorld())
        return;

    uint32 health = 0;
    uint32 mana = 0;

    // flat case
    if (damage < 0)
    {
        health = uint32(-damage);
        mana = m_spellInfo->Effects[effIndex].MiscValue;
    }
    // percent case
    else
    {
        health = m_caster->CountPctFromMaxHealth(damage);
        if (m_caster->GetMaxPower(POWER_MANA) > 0)
            mana = CalculatePct(m_caster->GetMaxPower(POWER_MANA), damage);
    }

    Player* player = m_caster->ToPlayer();
    player->ResurrectPlayer(0.0f);

    player->SetHealth(health);
    player->SetPower(POWER_MANA, mana);
    player->SetPower(POWER_RAGE, 0);
    player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));
    player->SetPower(POWER_FOCUS, 0);

    player->SpawnCorpseBones();
}

void Spell::EffectSkinning (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (unitTarget->GetTypeId() != TYPEID_UNIT)
        return;
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Creature* creature = unitTarget->ToCreature();
    int32 targetLevel = creature->getLevel();

    uint32 skill = creature->GetCreatureTemplate()->GetRequiredLootSkill();

    m_caster->ToPlayer()->SendLoot(creature->GetGUID(), LOOT_SKINNING);
    creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);

    int32 reqValue = targetLevel < 10 ? 0 : targetLevel < 20 ? (targetLevel - 10) * 10 : targetLevel * 5;

    int32 skillValue = m_caster->ToPlayer()->GetPureSkillValue(skill);

    // Double chances for elites
    m_caster->ToPlayer()->UpdateGatherSkill(skill, skillValue, reqValue, creature->isElite() ? 2 : 1);
}

void Spell::EffectCharge (SpellEffIndex /*effIndex*/)
{
    if (!unitTarget)
        return;

    if (effectHandleMode == SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
    {
        // Spell is not using explicit target - no generated path
        if (m_preGeneratedPath.GetPathType() == PATHFIND_BLANK)
        {
            Position pos;
            unitTarget->GetContactPoint(m_caster, pos.m_positionX, pos.m_positionY, pos.m_positionZ);
            unitTarget->GetFirstCollisionPosition(pos, unitTarget->GetObjectSize(), unitTarget->GetRelativeAngle(m_caster));
            m_caster->GetMotionMaster()->MoveCharge(pos.m_positionX, pos.m_positionY, pos.m_positionZ);
        }
        else
            m_caster->GetMotionMaster()->MoveCharge(m_preGeneratedPath);
    }

    if (effectHandleMode == SPELL_EFFECT_HANDLE_HIT_TARGET)
    {
        // not all charge effects used in negative spells
        if (!m_spellInfo->IsPositive() && m_caster->GetTypeId() == TYPEID_PLAYER)
            m_caster->Attack(unitTarget, true);
    }
}

void Spell::EffectChargeDest (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH)
        return;

    if (m_targets.HasDst())
    {
        Position pos;
        destTarget->GetPosition(&pos);
        float angle = m_caster->GetRelativeAngle(pos.GetPositionX(), pos.GetPositionY());
        float dist = m_caster->GetDistance(pos);
        m_caster->GetFirstCollisionPosition(pos, dist, angle);
        m_caster->GetMotionMaster()->MoveCharge(pos.m_positionX, pos.m_positionY, pos.m_positionZ);
    }
}

void Spell::EffectKnockBack (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    // Artillery (Twilight Highlands)
    switch (m_spellInfo->Id)
    {
        case 84864: // Artillery
        {
            if (unitTarget->GetTypeId() == TYPEID_UNIT)
                return;
            if (unitTarget->GetTypeId() == TYPEID_PLAYER && unitTarget->GetAreaId() == 5479)
                return;
            break;
        }
        case 92734: // Exploding Stuff
            return;
        default:
            break;
    }

    if (m_caster->ToTempSummon())
    {
        if (!m_caster->canSeeOrDetect(unitTarget) && m_caster->ToTempSummon()->GetSummoner() != unitTarget)
            return;
    }

    if (Creature* creatureTarget = unitTarget->ToCreature())
    {
        if (creatureTarget->isWorldBoss() || creatureTarget->IsDungeonBoss())
            return;
    }

    // Spells with SPELL_EFFECT_KNOCK_BACK (like Thunderstorm) can't knockback target if target is rooted
    if (unitTarget->HasUnitState(UNIT_STATE_ROOT))
        return;

    // Pillar of Frost (Immune to Knockback)
    if (unitTarget->HasAura(51271))
        return;

    // Use that switch to handle specific knockback/movements instead of standard spline usage (to prevent bugs in some spells)
    switch (m_spellInfo->Id)
    {
        case 51490: // Thunderstorm
        {
            // Glyph of Thunderstorm
            if (m_caster != unitTarget && m_caster->HasAura(62132))
                return;
            break;
        }
        default:
            break;
    }

    // Instantly interrupt non melee spells being casted
    if (unitTarget->IsNonMeleeSpellCasted(true))
        unitTarget->InterruptNonMeleeSpells(true);

    float ratio = 0.1f;
    float speedxy = float(m_spellInfo->Effects[effIndex].MiscValue) * ratio;
    float speedz = float(damage) * ratio;
    if (speedxy < 0.1f && speedz < 0.1f)
        return;

    float x, y;
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_KNOCK_BACK_DEST)
    {
        if (m_targets.HasDst())
            destTarget->GetPosition(x, y);
        else
            return;
    }
    else          //if (m_spellInfo->Effects[i].Effect == SPELL_EFFECT_KNOCK_BACK)
    {
        m_caster->GetPosition(x, y);
    }

    // Rolling with my Homies: Hot Rod - Knockback
    if (m_spellInfo->Id == 66301 && unitTarget)
    {
        if (unitTarget->ToCreature())
        {
            switch (unitTarget->GetEntry())
            {
                // Kezan Citizen
                case 35063:
                case 38745:
                case 35075:
                {
                    unitTarget->KnockbackFrom(x, y, speedxy, speedz);
                    return;
                }
                // Hired Looter
                case 35234:
                {
                    unitTarget->KnockbackFrom(x, y, speedxy, speedz);
                    if (m_caster)
                    {
                        if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            if (m_caster->ToPlayer()->GetQuestStatus(14121) == QUEST_STATUS_INCOMPLETE)
                                unitTarget->CastSpell(m_caster, 67041, true);
                        }
                    }
                    return;
                }
                default:
                    return;
            }
        }
    }

    unitTarget->KnockbackFrom(x, y, speedxy, speedz);
}

void Spell::EffectLeapBack (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH_TARGET)
        return;

    if (!unitTarget)
        return;

    float speedxy = m_spellInfo->Effects[effIndex].MiscValue / 10.0f;
    float speedz = damage / 10.0f;

    //1891: Disengage
    if (GetSpellInfo()->Effects[effIndex].TargetB.GetTarget() == TARGET_UNIT_SRC_AREA_ENEMY)
        unitTarget->JumpTo(speedxy, speedz, false);
    else if (GetSpellInfo()->Effects[effIndex].TargetB.GetTarget() == TARGET_UNIT_DEST_AREA_ENEMY)
        unitTarget->JumpTo(speedxy, speedz, false);
    else
        m_caster->JumpTo(speedxy, speedz, m_spellInfo->SpellIconID != 1891);
}

void Spell::EffectQuestClear (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* player = unitTarget->ToPlayer();

    uint32 quest_id = m_spellInfo->Effects[effIndex].MiscValue;

    Quest const* quest = sObjectMgr->GetQuestTemplate(quest_id);

    if (!quest)
        return;

    // Player has never done this quest
    if (player->GetQuestStatus(quest_id) == QUEST_STATUS_NONE)
        return;

    // remove all quest entries for 'entry' from quest log
    for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 logQuest = player->GetQuestSlotQuestId(slot);
        if (logQuest == quest_id)
        {
            player->SetQuestSlot(slot, 0);

            // we ignore unequippable quest items in this case, it's still be equipped
            player->TakeQuestSourceItem(logQuest, false);

            if (quest->HasFlag(QUEST_FLAGS_FLAGS_PVP))
            {
                player->pvpInfo.IsHostile = player->pvpInfo.IsInHostileArea || player->HasPvPForcingQuest();
                player->UpdatePvPState();
            }
        }
    }

    player->RemoveActiveQuest(quest_id);
    player->RemoveRewardedQuest(quest_id);
}

void Spell::EffectSendTaxi (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    unitTarget->ToPlayer()->ActivateTaxiPathTo(m_spellInfo->Effects[effIndex].MiscValue, m_spellInfo->Id);
}

void Spell::EffectPullTowards (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    float speedZ = (float) (m_spellInfo->Effects[effIndex].CalcValue() / 10);
    float speedXY = (float) (m_spellInfo->Effects[effIndex].MiscValue / 10);
    Position pos;
    if (m_spellInfo->Effects[effIndex].Effect == SPELL_EFFECT_PULL_TOWARDS_DEST)
    {
        if (m_targets.HasDst())
            pos.Relocate(*destTarget);
        else
            return;
    }
    else          //if (m_spellInfo->Effects[i].Effect == SPELL_EFFECT_PULL_TOWARDS)
    {
        pos.Relocate(m_caster);
    }

    unitTarget->GetMotionMaster()->MoveJump(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), speedXY, speedZ);
}

void Spell::EffectDispelMechanic (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    uint32 mechanic = m_spellInfo->Effects[effIndex].MiscValue;

    std::queue<std::pair<uint32, uint64> > dispel_list;

    Unit::AuraMap const& auras = unitTarget->GetOwnedAuras();
    for (Unit::AuraMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
    {
        Aura* aura = itr->second;
        if (!aura->GetApplicationOfTarget(unitTarget->GetGUID()))
            continue;
        if (roll_chance_i(aura->CalcDispelChance(unitTarget, !unitTarget->IsFriendlyTo(m_caster))))
            if ((aura->GetSpellInfo()->GetAllEffectsMechanicMask() & (1 << mechanic)))
                dispel_list.push(std::make_pair(aura->GetId(), aura->GetCasterGUID()));
    }

    for (; dispel_list.size(); dispel_list.pop())
    {
        unitTarget->RemoveAura(dispel_list.front().first, dispel_list.front().second, 0, AURA_REMOVE_BY_ENEMY_SPELL);
    }
}

void Spell::EffectSummonDeadPet (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    Player* player = m_caster->ToPlayer();
    if (!player)
        return;

    Pet* pet = player->GetPet();
    if (pet && pet->isAlive())
        return;

    if (damage < 0)
        return;

    float x, y, z;
    player->GetPosition(x, y, z);
    if (!pet)
        return;

    player->GetMap()->CreatureRelocation(pet, x, y, z, player->GetOrientation());

    pet->SetUInt32Value(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_NONE);
    pet->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
    pet->setDeathState(ALIVE);
    pet->ClearUnitState(uint32(UNIT_STATE_ALL_STATE));
    pet->SetHealth(pet->CountPctFromMaxHealth(damage));

    //pet->AIM_Initialize();
}

void Spell::EffectDestroyAllTotems (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    int32 mana = 0;
    for (uint8 slot = SUMMON_SLOT_TOTEM; slot < MAX_TOTEM_SLOT; ++slot)
    {
        if (!m_caster->m_SummonSlot[slot])
            continue;

        Creature* totem = m_caster->GetMap()->GetCreature(m_caster->m_SummonSlot[slot]);
        if (totem && totem->isTotem())
        {
            uint32 spell_id = totem->GetUInt32Value(UNIT_CREATED_BY_SPELL);
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell_id);
            if (spellInfo)
            {
                mana += spellInfo->ManaCost;
                mana += int32(CalculatePct(m_caster->GetCreateMana(), spellInfo->ManaCostPercentage));
            }
            totem->ToTotem()->UnSummon();
        }
    }

    AddPct(mana, damage);

    // Glyph of Totemic Recall
    if (!m_caster->HasAura(55438))
        mana -= mana * 0.95f;
    else
        mana -= mana * 0.925f;

    if (mana)
        m_caster->CastCustomSpell(m_caster, 39104, &mana, NULL, NULL, true);
}

void Spell::EffectDurabilityDamage (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 slot = m_spellInfo->Effects[effIndex].MiscValue;

    // -1 means all player equipped items and -2 all items
    if (slot < 0)
    {
        unitTarget->ToPlayer()->DurabilityPointsLossAll(damage, (slot < -1));
        ExecuteLogEffectDurabilityDamage(effIndex, unitTarget, -1, -1);
        return;
    }

    // invalid slot value
    if (slot >= INVENTORY_SLOT_BAG_END)
        return;

    if (Item* item = unitTarget->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
    {
        unitTarget->ToPlayer()->DurabilityPointsLoss(item, damage);
        ExecuteLogEffectDurabilityDamage(effIndex, unitTarget, item->GetEntry(), slot);
    }
}

void Spell::EffectDurabilityDamagePCT (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 slot = m_spellInfo->Effects[effIndex].MiscValue;

    // FIXME: some spells effects have value -1/-2
    // Possibly its mean -1 all player equipped items and -2 all items
    if (slot < 0)
    {
        unitTarget->ToPlayer()->DurabilityLossAll(float(damage) / 100.0f, (slot < -1));
        return;
    }

    // invalid slot value
    if (slot >= INVENTORY_SLOT_BAG_END)
        return;

    if (damage <= 0)
        return;

    if (Item* item = unitTarget->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
        unitTarget->ToPlayer()->DurabilityLoss(item, float(damage) / 100.0f);
}

void Spell::EffectModifyThreatPercent (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    unitTarget->getThreatManager().modifyThreatPercent(m_caster, damage);
}

void Spell::EffectTransmitted (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    uint32 name_id = m_spellInfo->Effects[effIndex].MiscValue;

    GameObjectTemplate const* goinfo = sObjectMgr->GetGameObjectTemplate(name_id);

    if (!goinfo)
    {
        sLog->outError(LOG_FILTER_SQL, "Gameobject (Entry: %u) not exist and not created at spell (ID: %u) cast", name_id, m_spellInfo->Id);
        return;
    }

    float fx, fy, fz;

    if (m_targets.HasDst())
        destTarget->GetPosition(fx, fy, fz);
    //FIXME: this can be better check for most objects but still hack
    else if (m_spellInfo->Effects[effIndex].HasRadius() && m_spellInfo->Speed == 0)
    {
        float dis = m_spellInfo->Effects[effIndex].CalcRadius(m_originalCaster);
        m_caster->GetClosePoint(fx, fy, fz, DEFAULT_WORLD_OBJECT_SIZE, dis);
    }
    else
    {
        //GO is always friendly to it's creator, get range for friends
        float min_dis = m_spellInfo->GetMinRange(true);
        float max_dis = m_spellInfo->GetMaxRange(true);
        float dis = (float) rand_norm() * (max_dis - min_dis) + min_dis;

        m_caster->GetClosePoint(fx, fy, fz, DEFAULT_WORLD_OBJECT_SIZE, dis);
    }

    Map* cMap = m_caster->GetMap();
    // if gameobject is summoning object, it should be spawned right on caster's position
    if (goinfo->type == GAMEOBJECT_TYPE_SUMMONING_RITUAL)
        m_caster->GetPosition(fx, fy, fz);

    GameObject* pGameObj = new GameObject;

    if (!pGameObj->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), name_id, cMap,
    m_caster->GetPhaseMask(), fx, fy, fz, m_caster->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 100, GO_STATE_READY))
    {
        delete pGameObj;
        return;
    }

    int32 duration = m_spellInfo->GetDuration();

    switch (goinfo->type)
    {
    case GAMEOBJECT_TYPE_FISHINGNODE:
    {
        m_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, pGameObj->GetGUID());
        m_caster->AddGameObject(pGameObj);          // will removed at spell cancel

        // end time of range when possible catch fish (FISHING_BOBBER_READY_TIME..GetDuration(m_spellInfo))
        // start time == fish-FISHING_BOBBER_READY_TIME (0..GetDuration(m_spellInfo)-FISHING_BOBBER_READY_TIME)
        int32 lastSec = 0;
        switch (urand(0, 3))
        {
        case 0:
            lastSec = 3;
            break;
        case 1:
            lastSec = 7;
            break;
        case 2:
            lastSec = 13;
            break;
        case 3:
            lastSec = 17;
            break;
        }

        duration = duration - lastSec * IN_MILLISECONDS + FISHING_BOBBER_READY_TIME * IN_MILLISECONDS;
        break;
    }
    case GAMEOBJECT_TYPE_SUMMONING_RITUAL:
    {
        if (m_caster->GetTypeId() == TYPEID_PLAYER)
        {
            pGameObj->AddUniqueUse(m_caster->ToPlayer());
            m_caster->AddGameObject(pGameObj);          // will be removed at spell cancel
        }
        break;
    }
    case GAMEOBJECT_TYPE_DUEL_ARBITER:          // 52991
        m_caster->AddGameObject(pGameObj);
        break;
    case GAMEOBJECT_TYPE_FISHINGHOLE:
    case GAMEOBJECT_TYPE_CHEST:
    default:
        break;
    }

    pGameObj->SetRespawnTime(duration > 0 ? duration / IN_MILLISECONDS : 0);

    pGameObj->SetOwnerGUID(m_caster->GetGUID());

    //pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel());
    pGameObj->SetSpellId(m_spellInfo->Id);

    ExecuteLogEffectSummonObject(effIndex, pGameObj);

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "AddObject at SpellEfects.cpp EffectTransmitted");
    //m_caster->AddGameObject(pGameObj);
    //m_ObjToDel.push_back(pGameObj);

    cMap->AddToMap(pGameObj);

    if (uint32 linkedEntry = pGameObj->GetGOInfo()->GetLinkedGameObjectEntry())
    {
        GameObject* linkedGO = new GameObject;
        if (linkedGO->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), linkedEntry, cMap,
        m_caster->GetPhaseMask(), fx, fy, fz, m_caster->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 100, GO_STATE_READY))
        {
            linkedGO->SetRespawnTime(duration > 0 ? duration/IN_MILLISECONDS : 0);
            //linkedGO->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel());
            linkedGO->SetSpellId(m_spellInfo->Id);
            linkedGO->SetOwnerGUID(m_caster->GetGUID());

            ExecuteLogEffectSummonObject(effIndex, linkedGO);

            linkedGO->GetMap()->AddToMap(linkedGO);
        }
        else
        {
            delete linkedGO;
            linkedGO = NULL;
            return;
        }
    }
}

void Spell::EffectProspecting (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* p_caster = (Player*) m_caster;
    if (!itemTarget || !(itemTarget->GetTemplate()->Flags & ITEM_PROTO_FLAG_PROSPECTABLE))
        return;

    if (itemTarget->GetCount() < 5)
        return;

    if (sWorld->getBoolConfig(CONFIG_SKILL_PROSPECTING))
    {
        uint32 SkillValue = p_caster->GetPureSkillValue(SKILL_JEWELCRAFTING);
        uint32 reqSkillValue = itemTarget->GetTemplate()->RequiredSkillRank;
        p_caster->UpdateGatherSkill(SKILL_JEWELCRAFTING, SkillValue, reqSkillValue);
    }

    m_caster->ToPlayer()->SendLoot(itemTarget->GetGUID(), LOOT_PROSPECTING);
}

void Spell::EffectMilling (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* p_caster = (Player*) m_caster;
    if (!itemTarget || !(itemTarget->GetTemplate()->Flags & ITEM_PROTO_FLAG_MILLABLE))
        return;

    if (itemTarget->GetCount() < 5)
        return;

    if (sWorld->getBoolConfig(CONFIG_SKILL_MILLING))
    {
        uint32 SkillValue = p_caster->GetPureSkillValue(SKILL_INSCRIPTION);
        uint32 reqSkillValue = itemTarget->GetTemplate()->RequiredSkillRank;
        p_caster->UpdateGatherSkill(SKILL_INSCRIPTION, SkillValue, reqSkillValue);
    }

    m_caster->ToPlayer()->SendLoot(itemTarget->GetGUID(), LOOT_MILLING);
}

void Spell::EffectSkill (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "WORLD: SkillEFFECT");
}

/* There is currently no need for this effect. We handle it in Battleground.cpp
 If we would handle the resurrection here, the spiritguide would instantly disappear as the
 player revives, and so we wouldn't see the spirit heal visual effect on the npc.
 This is why we use a half sec delay between the visual effect and the resurrection itself */
void Spell::EffectSpiritHeal (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    /*
     if (unitTarget->GetTypeId() != TYPEID_PLAYER)
     return;
     if (!unitTarget->IsInWorld())
     return;

     //m_spellInfo->Effects[i].BasePoints; == 99 (percent?)
     //unitTarget->ToPlayer()->setResurrect(m_caster->GetGUID(), unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(), unitTarget->GetMaxHealth(), unitTarget->GetMaxPower(POWER_MANA));
     unitTarget->ToPlayer()->ResurrectPlayer(1.0f);
     unitTarget->ToPlayer()->SpawnCorpseBones();
     */
}

// remove insignia spell effect
void Spell::EffectSkinPlayerCorpse (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Effect: SkinPlayerCorpse");
    if ((m_caster->GetTypeId() != TYPEID_PLAYER) || (unitTarget->GetTypeId() != TYPEID_PLAYER) || (unitTarget->isAlive()))
        return;

    unitTarget->ToPlayer()->RemovedInsignia((Player*) m_caster);
}

void Spell::EffectStealBeneficialBuff (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Effect: StealBeneficialBuff");

    if (!unitTarget || unitTarget == m_caster)          // can't steal from self
        return;

    DispelChargesList steal_list;

    // Create dispel mask by dispel type
    uint32 dispelMask = SpellInfo::GetDispelMask(DispelType(m_spellInfo->Effects[effIndex].MiscValue));
    Unit::AuraMap const& auras = unitTarget->GetOwnedAuras();
    for (Unit::AuraMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
    {
        Aura* aura = itr->second;
        AuraApplication * aurApp = aura->GetApplicationOfTarget(unitTarget->GetGUID());
        if (!aurApp)
            continue;

        if ((aura->GetSpellInfo()->GetDispelMask()) & dispelMask)
        {
            // Need check for passive? this
            if (!aurApp->IsPositive() || aura->IsPassive() || aura->GetSpellInfo()->AttributesEx4 & SPELL_ATTR4_NOT_STEALABLE)
                continue;

            // The charges / stack amounts don't count towards the total number of auras that can be dispelled.
            // Ie: A dispel on a target with 5 stacks of Winters Chill and a Polymorph has 1 / (1 + 1) -> 50% chance to dispell
            // Polymorph instead of 1 / (5 + 1) -> 16%.
            bool dispel_charges = aura->GetSpellInfo()->AttributesEx7 & SPELL_ATTR7_DISPEL_CHARGES;
            uint8 charges = dispel_charges ? aura->GetCharges() : aura->GetStackAmount();
            if (charges > 0)
                steal_list.push_back(std::make_pair(aura, charges));
        }
    }

    if (steal_list.empty())
        return;

    // Ok if exist some buffs for dispel try dispel it
    uint32 failCount = 0;
    DispelList success_list;
    WorldPacket dataFail(SMSG_DISPEL_FAILED, 8 + 8 + 4 + 4 + damage * 4);
    // dispel N = damage buffs (or while exist buffs for dispel)
    for (int32 count = 0; count < damage && !steal_list.empty();)
    {
        // Random select buff for dispel
        DispelChargesList::iterator itr = steal_list.begin();
        std::advance(itr, urand(0, steal_list.size() - 1));

        int32 chance = itr->first->CalcDispelChance(unitTarget, !unitTarget->IsFriendlyTo(m_caster));
        // 2.4.3 Patch Notes: "Dispel effects will no longer attempt to remove effects that have 100% dispel resistance."
        if (!chance)
        {
            steal_list.erase(itr);
            continue;
        }
        else
        {
            if (roll_chance_i(chance))
            {
                success_list.push_back(std::make_pair(itr->first->GetId(), itr->first->GetCasterGUID()));
                --itr->second;
                if (itr->second <= 0)
                    steal_list.erase(itr);
            }
            else
            {
                if (!failCount)
                {
                    // Failed to dispell
                    dataFail << uint64(m_caster->GetGUID());          // Caster GUID
                    dataFail << uint64(unitTarget->GetGUID());          // Victim GUID
                    dataFail << uint32(m_spellInfo->Id);          // dispel spell id
                }
                ++failCount;
                dataFail << uint32(itr->first->GetId());          // Spell Id
            }
            ++count;
        }
    }

    if (failCount)
        m_caster->SendMessageToSet(&dataFail, true);

    if (success_list.empty())
        return;

    WorldPacket dataSuccess(SMSG_SPELLSTEALLOG, 8 + 8 + 4 + 1 + 4 + damage * 5);
    dataSuccess.append(unitTarget->GetPackGUID());          // Victim GUID
    dataSuccess.append(m_caster->GetPackGUID());          // Caster GUID
    dataSuccess << uint32(m_spellInfo->Id);          // dispel spell id
    dataSuccess << uint8(0);          // not used
    dataSuccess << uint32(success_list.size());          // count
    for (DispelList::iterator itr = success_list.begin(); itr != success_list.end(); ++itr)
    {
        dataSuccess << uint32(itr->first);          // Spell Id
        dataSuccess << uint8(0);          // 0 - steals !=0 transfers
        unitTarget->RemoveAurasDueToSpellBySteal(itr->first, itr->second, m_caster);
    }
    m_caster->SendMessageToSet(&dataSuccess, true);
}

void Spell::EffectKillCreditPersonal (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    unitTarget->ToPlayer()->KilledMonsterCredit(m_spellInfo->Effects[effIndex].MiscValue, 0);
}

void Spell::EffectKillCredit (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 creatureEntry = m_spellInfo->Effects[effIndex].MiscValue;
    if (!creatureEntry)
    {
        if (m_spellInfo->Id == 42793)          // Burn Body
            creatureEntry = 24008;          // Fallen Combatant
    }

    if (creatureEntry)
        unitTarget->ToPlayer()->RewardPlayerAndGroupAtEvent(creatureEntry, unitTarget);
}

void Spell::EffectQuestFail (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    unitTarget->ToPlayer()->FailQuest(m_spellInfo->Effects[effIndex].MiscValue);
}

void Spell::EffectQuestStart(SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    Player* player = unitTarget->ToPlayer();
    if (!player)
        return;

    if (Quest const* quest = sObjectMgr->GetQuestTemplate(m_spellInfo->Effects[effIndex].MiscValue))
    {
        if (!player->CanTakeQuest(quest, false))
            return;

        if (quest->IsAutoAccept() && player->CanAddQuest(quest, false))
            player->AddQuestAndCheckCompletion(quest, player);

        player->PlayerTalkClass->SendQuestGiverQuestDetails(quest, player->GetGUID(), true);
    }
}

void Spell::EffectActivateRune (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_LAUNCH)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = m_caster->ToPlayer();

    if (player->getClass() != CLASS_DEATH_KNIGHT)
        return;

    // needed later
    m_runesState = m_caster->ToPlayer()->GetRunesState();

    uint32 count = damage;
    if (count == 0)
        count = 1;
    for (uint32 j = 0; j < MAX_RUNES && count > 0; ++j)
    {
        if (player->GetRuneCooldown(j) && player->GetCurrentRune(j) == RuneType(m_spellInfo->Effects[effIndex].MiscValue))
        {
            if (m_spellInfo->Id == 45529)
                if (player->GetBaseRune(j) != RuneType(m_spellInfo->Effects[effIndex].MiscValueB))
                    continue;
            player->SetRuneCooldown(j, 0);
            --count;
       }
    }

    // Blood Tap
    if (m_spellInfo->Id == 45529 && count > 0)
    {
        for (uint32 l = 0; l < MAX_RUNES && count > 0; ++l)
        {
            // Check if both runes are on cd as that is the only time when this needs to come into effect
            if ((player->GetRuneCooldown(l) && player->GetCurrentRune(l) == RuneType(m_spellInfo->Effects[effIndex].MiscValueB)) && (player->GetRuneCooldown(l + 1) && player->GetCurrentRune(l + 1) == RuneType(m_spellInfo->Effects[effIndex].MiscValueB)))
            {
                // Should always update the rune with the lowest cd
                if (player->GetRuneCooldown(l) >= player->GetRuneCooldown(l + 1))
                    l++;
                player->SetRuneCooldown(l, 0);
                --count;
                // is needed to push through to the client that the rune is active
                player->ResyncRunes(MAX_RUNES);
            }
            else
                break;
        }
    }

    // Empower rune weapon
    if (m_spellInfo->Id == 47568)
    {
        // Need to do this just once
        if (effIndex != 0)
            return;

        for (uint32 i = 0; i < MAX_RUNES; ++i)
        {
            if (player->GetRuneCooldown(i) && (player->GetCurrentRune(i) == RUNE_FROST || player->GetCurrentRune(i) == RUNE_DEATH))
                player->SetRuneCooldown(i, 0);
        }
    }
}

void Spell::EffectCreateTamedPet (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player *player = unitTarget->ToPlayer();

    PetTameResult result = player->TamePet(m_spellInfo->Effects[effIndex].MiscValue, m_spellInfo->Id);

    if (m_caster && m_caster->ToPlayer() && result != PET_TAME_ERROR_NO_ERROR)
        m_caster->ToPlayer()->SendPetTameError(result);
}

void Spell::EffectDiscoverTaxi (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    uint32 nodeid = m_spellInfo->Effects[effIndex].MiscValue;
    if (sTaxiNodesStore.LookupEntry(nodeid))
        unitTarget->ToPlayer()->GetSession()->SendDiscoverNewTaxiNode(nodeid);
}

void Spell::EffectTitanGrip (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        m_caster->ToPlayer()->SetCanTitanGrip(true);
}

void Spell::EffectRedirectThreat (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (unitTarget)
        m_caster->SetRedirectThreat(unitTarget->GetGUID(), uint32(damage));
}

void Spell::EffectGameObjectDamage (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!gameObjTarget)
        return;

    Unit* caster = m_originalCaster;
    if (!caster)
        return;

    FactionTemplateEntry const* casterFaction = caster->getFactionTemplateEntry();
    FactionTemplateEntry const* targetFaction = sFactionTemplateStore.LookupEntry(gameObjTarget->GetUInt32Value(GAMEOBJECT_FACTION));
    // Do not allow to damage GO's of friendly factions (ie: Wintergrasp Walls/Ulduar Storm Beacons)
    if ((casterFaction && targetFaction && !casterFaction->IsFriendlyTo(*targetFaction)) || !targetFaction)
        gameObjTarget->ModifyHealth(-damage, caster, GetSpellInfo()->Id);
}

void Spell::EffectGameObjectRepair (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!gameObjTarget)
        return;

    gameObjTarget->ModifyHealth(damage, m_caster);
}

void Spell::EffectGameObjectSetDestructionState (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!gameObjTarget || !m_originalCaster)
        return;

    Player* player = m_originalCaster->GetCharmerOrOwnerPlayerOrPlayerItself();
    gameObjTarget->SetDestructibleState(GameObjectDestructibleState(m_spellInfo->Effects[effIndex].MiscValue), player, true);
}

void Spell::SummonGuardian (uint32 i, uint32 entry, SummonPropertiesEntry const* properties, uint32 numGuardians)
{
    Unit* caster = m_originalCaster;
    if (!caster)
        return;

    if (caster->isTotem())
        caster = caster->ToTotem()->GetOwner();

    // in another case summon new
    uint8 level = caster->getLevel();

    // level of pet summoned using engineering item based at engineering skill level
    if (m_CastItem && caster->GetTypeId() == TYPEID_PLAYER)
        if (ItemTemplate const* proto = m_CastItem->GetTemplate())
            if (proto->RequiredSkill == SKILL_ENGINEERING)
                if (uint16 skill202 = caster->ToPlayer()->GetSkillValue(SKILL_ENGINEERING))
                    level = skill202 / 5;

    float radius = 5.0f;
    int32 duration = m_spellInfo->GetDuration();

    if (Player* modOwner = m_originalCaster->GetSpellModOwner())
        modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_DURATION, duration);

    //TempSummonType summonType = (duration == 0) ? TEMPSUMMON_DEAD_DESPAWN : TEMPSUMMON_TIMED_DESPAWN;
    Map* map = caster->GetMap();

    for (uint32 count = 0; count < numGuardians; ++count)
    {
        Position pos;
        if (count == 0)
            pos = *destTarget;
        else
            // randomize position for multiple summons
            m_caster->GetRandomPoint(*destTarget, radius, pos);

        TempSummon* summon = map->SummonCreature(entry, pos, properties, duration, caster, m_spellInfo->Id);
        if (!summon)
            return;
        if (summon->HasUnitTypeMask(UNIT_MASK_GUARDIAN))
            ((Guardian*) summon)->InitStatsForLevel(level);

        if (properties && properties->Category == SUMMON_CATEGORY_ALLY)
            summon->setFaction(caster->getFaction());

        if (summon->HasUnitTypeMask(UNIT_MASK_MINION) && m_targets.HasDst())
            ((Minion*) summon)->SetFollowAngle(m_caster->GetAngle(summon));

        if (summon->GetEntry() == 27893)
        {
            if (uint32 weapon = m_caster->GetUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID))
            {
                summon->SetDisplayId(11686);
                summon->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, weapon);
            }
            else
                summon->SetDisplayId(1126);
        }

        summon->AI()->EnterEvadeMode();

        ExecuteLogEffectSummonObject(i, summon);
    }
}

void Spell::EffectRenamePet (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || !unitTarget->ToCreature()->isPet() || ((Pet*) unitTarget)->getPetType() != HUNTER_PET)
        return;

    unitTarget->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
}

void Spell::EffectPlayMusic (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    uint32 soundid = m_spellInfo->Effects[effIndex].MiscValue;

    if (!sSoundEntriesStore.LookupEntry(soundid))
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "EffectPlayMusic: Sound (Id: %u) not exist in spell %u.", soundid, m_spellInfo->Id);
        return;
    }

    WorldPacket data(SMSG_PLAY_MUSIC, 4);
    data << uint32(soundid);
    data << uint64(unitTarget->GetGUID());
    unitTarget->ToPlayer()->GetSession()->SendPacket(&data);
}

void Spell::EffectSpecCount (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    unitTarget->ToPlayer()->UpdateSpecCount(damage);
}

void Spell::EffectActivateSpec (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    unitTarget->ToPlayer()->ActivateSpec(damage - 1);          // damage is 1 or 2, spec is 0 or 1
}

void Spell::EffectPlaySound (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    switch (m_spellInfo->Id)
    {
    case 91604:          // Restricted Flight Area
        unitTarget->ToPlayer()->GetSession()->SendNotification(LANG_ZONE_NOFLYZONE);
        break;
    default:
        break;
    }

    uint32 soundId = m_spellInfo->Effects[effIndex].MiscValue;

    if (!sSoundEntriesStore.LookupEntry(soundId))
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "EffectPlaySound: Sound (Id: %u) not exist in spell %u.", soundId, m_spellInfo->Id);
        return;
    }

    WorldPacket data(SMSG_PLAY_SOUND, 4);
    data << uint32(soundId);
    data << uint64(m_caster->GetGUID());
    unitTarget->ToPlayer()->GetSession()->SendPacket(&data);
}

void Spell::EffectRemoveAura (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    // there may be need of specifying casterguid of removed auras
    unitTarget->RemoveAurasDueToSpell(m_spellInfo->Effects[effIndex].TriggerSpell);
}

void Spell::EffectDamageFromMaxHealthPCT (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    switch (m_spellInfo->Id)
    {
        case 90765: // Digestive Juice
        {
            // Exclude GM's
            if (unitTarget->GetTypeId() == TYPEID_PLAYER && unitTarget->ToPlayer()->isGameMaster())
                damage = 0;

            // Field of Restoration
            if (unitTarget->HasAura(90736))
                m_damage = 0;
            else
            {
                m_damage = unitTarget->CountPctFromMaxHealth(damage);
                m_damage += m_damage * unitTarget->GetPower(POWER_ALTERNATE_POWER) / 10;
            }
            return;
        }
        default:
            break;
    }

    m_damage += unitTarget->CountPctFromMaxHealth(damage);
}

void Spell::EffectGiveCurrency (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    unitTarget->ToPlayer()->ModifyCurrency(m_spellInfo->Effects[effIndex].MiscValue, damage);
}

void Spell::EffectCastButtons (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* p_caster = m_caster->ToPlayer();
    uint32 button_id = m_spellInfo->Effects[effIndex].MiscValue + 132;
    uint32 n_buttons = m_spellInfo->Effects[effIndex].MiscValueB;

    for (; n_buttons; --n_buttons, ++button_id)
    {
        ActionButton const* ab = p_caster->GetActionButton(button_id);
        if (!ab || ab->GetType() != ACTION_BUTTON_SPELL)
            continue;

        //! Action button data is unverified when it's set so it can be "hacked"
        //! to contain invalid spells, so filter here.
        uint32 spell_id = ab->GetAction();
        if (!spell_id)
            continue;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell_id);
        if (!spellInfo)
            continue;

        if (!p_caster->HasSpell(spell_id) || p_caster->HasSpellCooldown(spell_id))
            continue;

        if (!(spellInfo->AttributesEx9 & SPELL_ATTR9_SUMMON_PLAYER_TOTEM))
            continue;

        int32 cost = spellInfo->CalcPowerCost(m_caster, spellInfo->GetSchoolMask());
        if (m_caster->GetPower(POWER_MANA) < cost)
            continue;

        TriggerCastFlags triggerFlags = TriggerCastFlags(TRIGGERED_IGNORE_GCD | TRIGGERED_IGNORE_CAST_IN_PROGRESS | TRIGGERED_CAST_DIRECTLY);
        m_caster->CastSpell(m_caster, spell_id, triggerFlags);
    }
}

void Spell::EffectRechargeManaGem (SpellEffIndex /*effIndex*/)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = m_caster->ToPlayer();

    if (!player)
        return;

    uint32 item_id = m_spellInfo->Effects[EFFECT_0].ItemType;

    ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(item_id);
    if (!pProto)
    {
        player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }

    if (Item* pItem = player->GetItemByEntry(item_id))
    {
        for (int x = 0; x < MAX_ITEM_PROTO_SPELLS; ++x)
            pItem->SetSpellCharges(x, pProto->Spells[x].SpellCharges);
        pItem->SetState(ITEM_CHANGED, player);
    }
}

void Spell::EffectBind (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = unitTarget->ToPlayer();

    WorldLocation homeLoc;
    uint32 areaId = player->GetAreaId();

    if (m_spellInfo->Effects[effIndex].MiscValue)
        areaId = m_spellInfo->Effects[effIndex].MiscValue;

    if (m_targets.HasDst())
        homeLoc.WorldRelocate(*destTarget);
    else
    {
        player->GetPosition(&homeLoc);
        homeLoc.m_mapId = player->GetMapId();
    }

    player->SetHomebind(homeLoc, areaId);

    // binding
    WorldPacket data(SMSG_BINDPOINTUPDATE, 4 + 4 + 4 + 4 + 4);
    data << float(homeLoc.GetPositionX());
    data << float(homeLoc.GetPositionY());
    data << float(homeLoc.GetPositionZ());
    data << uint32(homeLoc.GetMapId());
    data << uint32(areaId);
    player->SendDirectMessage(&data);

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "EffectBind: New homebind X: %f, Y: %f, Z: %f, MapId: %u, AreaId: %u",
            homeLoc.GetPositionX(), homeLoc.GetPositionY(), homeLoc.GetPositionZ(), homeLoc.GetMapId(), areaId);

    // zone update
    data.Initialize(SMSG_PLAYERBOUND, 8 + 4);
    data << uint64(m_caster->GetGUID());
    data << uint32(areaId);
    player->SendDirectMessage(&data);
}

void Spell::EffectSummonRaFFriend (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER || !unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    m_caster->CastSpell(unitTarget, m_spellInfo->Effects[effIndex].TriggerSpell, true);
}

void Spell::EffectUnlockGuildVaultTab(SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT)
        return;

    // Safety checks done in Spell::CheckCast
    Player* caster = m_caster->ToPlayer();
    if (Guild* guild = caster->GetGuild())
        guild->HandleBuyBankTab(caster->GetSession(), m_spellInfo->Effects[effIndex].BasePoints - 1); // Bank tabs start at zero internally
}

void Spell::EffectResurrectWithAura (SpellEffIndex effIndex)
{
    if (effectHandleMode != SPELL_EFFECT_HANDLE_HIT_TARGET)
        return;

    if (!unitTarget)
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    if (Player* caster = unitTarget->ToPlayer())
    {
        if (Group* group = caster->GetGroup())
        {
            // Initialize group/raid check
            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                if (Player* almostDied = itr->getSource())
                {
                    // Preliminary checks to prevent exploits
                    if (!almostDied->IsInWorld() || almostDied->isAlive() || almostDied->IsRessurectRequested())
                        continue;

                    // Cannot be useable in Battleground or Arena
                    if (almostDied->GetMap() && almostDied->GetMap()->IsBattlegroundOrArena())
                        continue;

                    // Limit to 100yd
                    if (almostDied->GetDistance2d(caster) > 100)
                        continue;

                    uint32 health = almostDied->CountPctFromMaxHealth(damage);
                    uint32 mana = CalculatePct(almostDied->GetMaxPower(POWER_MANA), damage);
                    uint32 resurrectAura = 0;

                    // The Quick and the Dead
                    if (m_caster && m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (m_caster->ToPlayer()->GetGuild())
                            if (m_caster->ToPlayer()->GetGuildId() == unitTarget->ToPlayer()->GetGuildId())
                                if (unitTarget->HasAura(83950))
                                    AddPct(health, 50);
                    }

                    // Add Mass Resurrection debuff to prevent other resurrections for 10 mins
                    if (sSpellMgr->GetSpellInfo(GetSpellInfo()->Effects[effIndex].TriggerSpell))
                        resurrectAura = GetSpellInfo()->Effects[effIndex].TriggerSpell;

                    // Don't apply if target is already resurrecting
                    if (resurrectAura && almostDied->HasAura(resurrectAura))
                        continue;

                    // Send resurrect request
                    ExecuteLogEffectResurrect(effIndex, almostDied);
                    almostDied->SetResurrectRequestData(m_caster, health, mana, resurrectAura);
                    SendResurrectRequest(almostDied);

                    // Apply resurrection visual effect
                    almostDied->CastSpell(almostDied, 32343, false);
                }
            }
        }
    }
}
