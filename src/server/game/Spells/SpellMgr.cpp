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

#include "SpellMgr.h"
#include "SpellInfo.h"
#include "ObjectMgr.h"
#include "SpellAuras.h"
#include "SpellAuraDefines.h"
#include "SharedDefines.h"
#include "DBCStores.h"
#include "World.h"
#include "Chat.h"
#include "Spell.h"
#include "BattlegroundMgr.h"
#include "CreatureAI.h"
#include "MapManager.h"
#include "BattlegroundIC.h"
#include "BattlefieldWG.h"
#include "BattlefieldMgr.h"
#include "Player.h"

bool IsPrimaryProfessionSkill(uint32 skill)
{
    SkillLineEntry const* pSkill = sSkillLineStore.LookupEntry(skill);
    return pSkill && pSkill->categoryId == SKILL_CATEGORY_PROFESSION;
}

bool IsWeaponSkill(uint32 skill)
{
    SkillLineEntry const* pSkill = sSkillLineStore.LookupEntry(skill);
    return pSkill && pSkill->categoryId == SKILL_CATEGORY_WEAPON;
}

bool IsPartOfSkillLine(uint32 skillId, uint32 spellId)
{
    SkillLineAbilityMapBounds skillBounds = sSpellMgr->GetSkillLineAbilityMapBounds(spellId);
    for (SkillLineAbilityMap::const_iterator itr = skillBounds.first; itr != skillBounds.second; ++itr)
        if (itr->second->skillId == skillId)
            return true;

    return false;
}

DiminishingGroup GetDiminishingReturnsGroupForSpell(SpellInfo const* spellproto, bool triggered)
{
    if (spellproto->IsPositive())
        return DIMINISHING_NONE;

    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (spellproto->Effects[i].ApplyAuraName == SPELL_AURA_MOD_TAUNT)
            return DIMINISHING_TAUNT;
    }

    // Explicit Diminishing Groups
    switch (spellproto->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            // Pet charge effects (Infernal Awakening, Demon Charge)
            if (spellproto->SpellVisual[0] == 2816 && spellproto->SpellIconID == 15)
                return DIMINISHING_CONTROLLED_STUN;
            // Frost Tomb
            else if (spellproto->Id == 48400)
                return DIMINISHING_NONE;
            // Gnaw
            else if (spellproto->Id == 47481)
                return DIMINISHING_CONTROLLED_STUN;
            // ToC Icehowl Arctic Breath
            else if (spellproto->SpellVisual[0] == 14153)
                return DIMINISHING_NONE;
            break;
        }
        // Event spells
        case SPELLFAMILY_UNK1:
            return DIMINISHING_NONE;
        case SPELLFAMILY_MAGE:
        {
            // Frostbite
            if (spellproto->SpellFamilyFlags[1] & 0x80000000)
                return DIMINISHING_ROOT;
            // Shattered Barrier
            else if (spellproto->SpellVisual[0] == 12297)
                return DIMINISHING_ROOT;
            // Deep Freeze
            else if (spellproto->SpellIconID == 2939 && spellproto->SpellVisual[0] == 9963)
                return DIMINISHING_CONTROLLED_STUN;
            // Frost Nova / Freeze (Water Elemental)
            else if (spellproto->SpellIconID == 193)
                return DIMINISHING_CONTROLLED_ROOT;
            // Dragon's Breath
            else if (spellproto->SpellFamilyFlags[0] & 0x800000)
                return DIMINISHING_DRAGONS_BREATH;
            // Ring of Frost and Deep Freeze
            else if (spellproto->Id == 82691 || spellproto->Id == 44572)
                return DIMINISHING_CONTROLLED_STUN;
            break;
        }
        case SPELLFAMILY_WARRIOR:
        {
            // Hamstring - limit duration to 10s in PvP
            if (spellproto->SpellFamilyFlags[0] & 0x2)
                return DIMINISHING_LIMITONLY;
            // Charge Stun (own diminishing)
            else if (spellproto->SpellFamilyFlags[0] & 0x01000000)
                return DIMINISHING_CHARGE;
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            // Curses/etc
            if ((spellproto->SpellFamilyFlags[0] & 0x80000000) || (spellproto->SpellFamilyFlags[1] & 0x200))
                return DIMINISHING_LIMITONLY;
            // Seduction
            else if (spellproto->SpellFamilyFlags[1] & 0x10000000)
                return DIMINISHING_FEAR;
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            // Solar Beam
            if (spellproto->Id == 81261)
                return DIMINISHING_NONE;
            // Cyclone
            else if (spellproto->SpellFamilyFlags[1] & 0x20)
                return DIMINISHING_CYCLONE;
            // Entangling Roots
            // Nature's Grasp
            else if (spellproto->SpellFamilyFlags[0] & 0x00000200)
                return DIMINISHING_CONTROLLED_ROOT;
            // Faerie Fire
            else if (spellproto->SpellFamilyFlags[0] & 0x400)
                return DIMINISHING_LIMITONLY;
            break;
        }
        case SPELLFAMILY_ROGUE:
        {
            // Gouge
            if (spellproto->SpellFamilyFlags[0] & 0x8)
                return DIMINISHING_DISORIENT;
            // Blind
            else if (spellproto->SpellFamilyFlags[0] & 0x1000000)
                return DIMINISHING_FEAR;
            // Crippling poison - Limit to 10 seconds in PvP (No SpellFamilyFlags)
            else if (spellproto->SpellIconID == 163)
                return DIMINISHING_LIMITONLY;
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            // Hunter's Mark
            if ((spellproto->SpellFamilyFlags[0] & 0x400) && spellproto->SpellIconID == 538)
                return DIMINISHING_LIMITONLY;
            // Scatter Shot (own diminishing)
            else if ((spellproto->SpellFamilyFlags[0] & 0x40000) && spellproto->SpellIconID == 132)
                return DIMINISHING_SCATTER_SHOT;
            // Entrapment (own diminishing)
            else if (spellproto->SpellVisual[0] == 7484 && spellproto->SpellIconID == 20)
                return DIMINISHING_ENTRAPMENT;
            // Wyvern Sting mechanic is MECHANIC_SLEEP but the diminishing is DIMINISHING_DISORIENT
            else if ((spellproto->SpellFamilyFlags[1] & 0x1000) && spellproto->SpellIconID == 1721)
                return DIMINISHING_DISORIENT;
            // Freezing Arrow
            else if (spellproto->SpellFamilyFlags[0] & 0x8)
                return DIMINISHING_DISORIENT;
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            // Judgement of Justice - limit duration to 10s in PvP
            if (spellproto->SpellFamilyFlags[0] & 0x100000)
                return DIMINISHING_LIMITONLY;
            // Turn Evil
            else if ((spellproto->SpellFamilyFlags[1] & 0x804000) && spellproto->SpellIconID == 309)
                return DIMINISHING_FEAR;
            break;
        }
        case SPELLFAMILY_DEATHKNIGHT:
        {
            // Hungering Cold (no flags)
            if (spellproto->SpellIconID == 2797)
                return DIMINISHING_DISORIENT;
            // Mark of Blood
            else if ((spellproto->SpellFamilyFlags[0] & 0x10000000) && spellproto->SpellIconID == 2285)
                return DIMINISHING_LIMITONLY;
            break;
        }
        case SPELLFAMILY_SHAMAN:
        {
            // Bash (Feral Spirit Ability)
            if (spellproto->Id == 58861)
                return DIMINISHING_NONE;
            break;
        }
        default:
            break;
    }

    // Lastly - Set diminishing depending on mechanic
    uint32 mechanic = spellproto->GetAllEffectsMechanicMask();
    if (mechanic & (1 << MECHANIC_CHARM))
        return DIMINISHING_MIND_CONTROL;
    if (mechanic & (1 << MECHANIC_SILENCE))
        return DIMINISHING_SILENCE;
    if (mechanic & (1 << MECHANIC_SLEEP))
        return DIMINISHING_SLEEP;
    if (mechanic & ((1 << MECHANIC_SAPPED) | (1 << MECHANIC_POLYMORPH) | (1 << MECHANIC_SHACKLE)))
        return DIMINISHING_DISORIENT;
    // Mechanic Knockout, except Blast Wave
    if (mechanic & (1 << MECHANIC_KNOCKOUT) && spellproto->SpellIconID != 292)
        return DIMINISHING_DISORIENT;
    if (mechanic & (1 << MECHANIC_DISARM))
        return DIMINISHING_DISARM;
    if (mechanic & (1 << MECHANIC_FEAR))
        return DIMINISHING_FEAR;
    if (mechanic & (1 << MECHANIC_STUN))
        return triggered ? DIMINISHING_STUN : DIMINISHING_CONTROLLED_STUN;
    if (mechanic & (1 << MECHANIC_BANISH))
        return DIMINISHING_BANISH;
    if (mechanic & (1 << MECHANIC_ROOT))
        return triggered ? DIMINISHING_ROOT : DIMINISHING_CONTROLLED_ROOT;
    if (mechanic & (1 << MECHANIC_HORROR))
        return DIMINISHING_HORROR;

    return DIMINISHING_NONE;
}

DiminishingReturnsType GetDiminishingReturnsGroupType(DiminishingGroup group)
{
    switch (group)
    {
        case DIMINISHING_TAUNT:
        case DIMINISHING_CONTROLLED_STUN:
        case DIMINISHING_STUN:
        case DIMINISHING_OPENING_STUN:
        case DIMINISHING_CYCLONE:
        case DIMINISHING_CHARGE:
            return DRTYPE_ALL;
        case DIMINISHING_LIMITONLY:
        case DIMINISHING_NONE:
            return DRTYPE_NONE;
        default:
            return DRTYPE_PLAYER;
    }
}

DiminishingLevels GetDiminishingReturnsMaxLevel(DiminishingGroup group)
{
    switch (group)
    {
        case DIMINISHING_TAUNT:
            return DIMINISHING_LEVEL_TAUNT_IMMUNE;
        default:
            return DIMINISHING_LEVEL_IMMUNE;
    }
}

int32 GetDiminishingReturnsLimitDuration(DiminishingGroup group, SpellInfo const* spellproto)
{
    if (!IsDiminishingReturnsGroupDurationLimited(group))
        return 0;

    // Explicit diminishing duration
    switch (spellproto->SpellFamilyName)
    {
        case SPELLFAMILY_DRUID:
        {
            // Faerie Fire - limit to 40 seconds in PvP (3.1)
            if (spellproto->SpellFamilyFlags[0] & 0x400)
                return 40 * IN_MILLISECONDS;
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            // Wyvern Sting
            if (spellproto->SpellFamilyFlags[1] & 0x1000)
                return 6 * IN_MILLISECONDS;
            // Hunter's Mark
            if (spellproto->SpellFamilyFlags[0] & 0x400)
                return 30 * IN_MILLISECONDS;
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            // Repentance - limit to 6 seconds in PvP
            if (spellproto->SpellFamilyFlags[0] & 0x4)
                return 6 * IN_MILLISECONDS;
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            // Banish - limit to 6 seconds in PvP
            if (spellproto->SpellFamilyFlags[1] & 0x8000000)
                return 6 * IN_MILLISECONDS;
            // Curse of Tongues - limit to 12 seconds in PvP
            else if (spellproto->SpellFamilyFlags[2] & 0x800)
                return 12 * IN_MILLISECONDS;
            // Curse of Elements - limit to 120 seconds in PvP
            else if (spellproto->SpellFamilyFlags[1] & 0x200)
               return 120 * IN_MILLISECONDS;
            break;
        }
        default:
            break;
    }

    return 8 * IN_MILLISECONDS;
}

bool IsDiminishingReturnsGroupDurationLimited(DiminishingGroup group)
{
    switch (group)
    {
        case DIMINISHING_BANISH:
        case DIMINISHING_CONTROLLED_STUN:
        case DIMINISHING_CONTROLLED_ROOT:
        case DIMINISHING_CYCLONE:
        case DIMINISHING_DISORIENT:
        case DIMINISHING_ENTRAPMENT:
        case DIMINISHING_FEAR:
        case DIMINISHING_HORROR:
        case DIMINISHING_MIND_CONTROL:
        case DIMINISHING_OPENING_STUN:
        case DIMINISHING_ROOT:
        case DIMINISHING_STUN:
        case DIMINISHING_SLEEP:
        case DIMINISHING_LIMITONLY:
            return true;
        default:
            return false;
    }
}

SpellMgr::SpellMgr()
{
}

SpellMgr::~SpellMgr()
{
    UnloadSpellInfoStore();
}

/// Some checks for spells, to prevent adding deprecated/broken spells for trainers, spell book, etc
bool SpellMgr::IsSpellValid(SpellInfo const* spellInfo, Player* player, bool msg)
{
    // not exist
    if (!spellInfo)
        return false;

    bool need_check_reagents = false;

    // check effects
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        switch (spellInfo->Effects[i].Effect)
        {
            case 0:
                continue;

            // craft spell for crafting non-existed item (break client recipes list show)
            case SPELL_EFFECT_CREATE_ITEM:
            case SPELL_EFFECT_CREATE_ITEM_2:
            {
                if (spellInfo->Effects[i].ItemType == 0)
                {
                    // skip auto-loot crafting spells, its not need explicit item info (but have special fake items sometime)
                    if (!spellInfo->IsLootCrafting())
                    {
                        if (msg)
                        {
                            if (player)
                                ChatHandler(player->GetSession()).PSendSysMessage("Craft spell %u not have create item entry.", spellInfo->Id);
                            else
                                sLog->outError(LOG_FILTER_SQL, "Craft spell %u not have create item entry.", spellInfo->Id);
                        }
                        return false;
                    }

                }
                // also possible IsLootCrafting case but fake item must exist anyway
                else if (!sObjectMgr->GetItemTemplate(spellInfo->Effects[i].ItemType))
                {
                    if (msg)
                    {
                        if (player)
                            ChatHandler(player->GetSession()).PSendSysMessage("Craft spell %u create not-exist in DB item (Entry: %u) and then...", spellInfo->Id, spellInfo->Effects[i].ItemType);
                        else
                            sLog->outError(LOG_FILTER_SQL, "Craft spell %u create not-exist in DB item (Entry: %u) and then...", spellInfo->Id, spellInfo->Effects[i].ItemType);
                    }
                    return false;
                }

                need_check_reagents = true;
                break;
            }
            case SPELL_EFFECT_LEARN_SPELL:
            {
                SpellInfo const* spellInfo2 = sSpellMgr->GetSpellInfo(spellInfo->Effects[i].TriggerSpell);
                if (!IsSpellValid(spellInfo2, player, msg))
                {
                    if (msg)
                    {
                        if (player)
                            ChatHandler(player->GetSession()).PSendSysMessage("Spell %u learn to broken spell %u, and then...", spellInfo->Id, spellInfo->Effects[i].TriggerSpell);
                        else
                            sLog->outError(LOG_FILTER_SQL, "Spell %u learn to invalid spell %u, and then...", spellInfo->Id, spellInfo->Effects[i].TriggerSpell);
                    }
                    return false;
                }
                break;
            }
        }
    }

    if (need_check_reagents)
    {
        for (uint8 j = 0; j < MAX_SPELL_REAGENTS; ++j)
        {
            if (spellInfo->Reagent[j] > 0 && !sObjectMgr->GetItemTemplate(spellInfo->Reagent[j]))
            {
                if (msg)
                {
                    if (player)
                        ChatHandler(player->GetSession()).PSendSysMessage("Craft spell %u have not-exist reagent in DB item (Entry: %u) and then...", spellInfo->Id, spellInfo->Reagent[j]);
                    else
                        sLog->outError(LOG_FILTER_SQL, "Craft spell %u have not-exist reagent in DB item (Entry: %u) and then...", spellInfo->Id, spellInfo->Reagent[j]);
                }
                return false;
            }
        }
    }

    return true;
}

uint32 SpellMgr::GetSpellDifficultyId(uint32 spellId) const
{
    SpellDifficultySearcherMap::const_iterator i = mSpellDifficultySearcherMap.find(spellId);
    return i == mSpellDifficultySearcherMap.end() ? 0 : (*i).second;
}

void SpellMgr::SetSpellDifficultyId(uint32 spellId, uint32 id)
{
    mSpellDifficultySearcherMap[spellId] = id;
}

uint32 SpellMgr::GetSpellIdForDifficulty(uint32 spellId, Unit const* caster) const
{
    if (!GetSpellInfo(spellId))
        return spellId;

    if (!caster || !caster->GetMap() || !caster->GetMap()->IsDungeon())
        return spellId;

    uint32 mode = uint32(caster->GetMap()->GetSpawnMode());
    if (mode >= MAX_DIFFICULTY)
    {
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "SpellMgr::GetSpellIdForDifficulty: Incorrect Difficulty for spell %u.", spellId);
        return spellId; //return source spell
    }

    uint32 difficultyId = GetSpellDifficultyId(spellId);
    if (!difficultyId)
        return spellId; //return source spell, it has only REGULAR_DIFFICULTY

    SpellDifficultyEntry const* difficultyEntry = sSpellDifficultyStore.LookupEntry(difficultyId);
    if (!difficultyEntry)
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "SpellMgr::GetSpellIdForDifficulty: SpellDifficultyEntry not found for spell %u. This should never happen.", spellId);
        return spellId; //return source spell
    }

    if (difficultyEntry->SpellID[mode] <= 0 && mode > DUNGEON_DIFFICULTY_HEROIC)
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "SpellMgr::GetSpellIdForDifficulty: spell %u mode %u spell is NULL, using mode %u", spellId, mode, mode - 2);
        mode -= 2;
    }

    if (difficultyEntry->SpellID[mode] <= 0)
    {
        sLog->outError(LOG_FILTER_SQL, "SpellMgr::GetSpellIdForDifficulty: spell %u mode %u spell is 0. Check spelldifficulty_dbc!", spellId, mode);
        return spellId;
    }

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "SpellMgr::GetSpellIdForDifficulty: spellid for spell %u in mode %u is %d", spellId, mode, difficultyEntry->SpellID[mode]);
    return uint32(difficultyEntry->SpellID[mode]);
}

SpellInfo const* SpellMgr::GetSpellForDifficultyFromSpell(SpellInfo const* spell, Unit const* caster) const
{
    uint32 newSpellId = GetSpellIdForDifficulty(spell->Id, caster);
    SpellInfo const* newSpell = GetSpellInfo(newSpellId);
    if (!newSpell)
    {
        sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "SpellMgr::GetSpellForDifficultyFromSpell: spell %u not found. Check spelldifficulty_dbc!", newSpellId);
        return spell;
    }

    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "SpellMgr::GetSpellForDifficultyFromSpell: Spell id for instance mode is %u (original %u)", newSpell->Id, spell->Id);
    return newSpell;
}

SpellChainNode const* SpellMgr::GetSpellChainNode(uint32 spell_id) const
{
    SpellChainMap::const_iterator itr = mSpellChains.find(spell_id);
    if (itr == mSpellChains.end())
        return NULL;

    return &itr->second;
}

uint32 SpellMgr::GetFirstSpellInChain(uint32 spell_id) const
{
    if (SpellChainNode const* node = GetSpellChainNode(spell_id))
        return node->first->Id;

    return spell_id;
}

uint32 SpellMgr::GetLastSpellInChain(uint32 spell_id) const
{
    if (SpellChainNode const* node = GetSpellChainNode(spell_id))
        return node->last->Id;

    return spell_id;
}

uint32 SpellMgr::GetNextSpellInChain(uint32 spell_id) const
{
    if (SpellChainNode const* node = GetSpellChainNode(spell_id))
        if (node->next)
            return node->next->Id;

    return 0;
}

uint32 SpellMgr::GetPrevSpellInChain(uint32 spell_id) const
{
    if (SpellChainNode const* node = GetSpellChainNode(spell_id))
        if (node->prev)
            return node->prev->Id;

    return 0;
}

uint8 SpellMgr::GetSpellRank(uint32 spell_id) const
{
    if (SpellChainNode const* node = GetSpellChainNode(spell_id))
        return node->rank;

    return 0;
}

uint32 SpellMgr::GetSpellWithRank(uint32 spell_id, uint32 rank, bool strict) const
{
    if (SpellChainNode const* node = GetSpellChainNode(spell_id))
    {
        if (rank != node->rank)
            return GetSpellWithRank(node->rank < rank ? node->next->Id : node->prev->Id, rank, strict);
    }
    else if (strict && rank > 1)
        return 0;
    return spell_id;
}

SpellRequiredMapBounds SpellMgr::GetSpellsRequiredForSpellBounds(uint32 spell_id) const
{
    return mSpellReq.equal_range(spell_id);
}

SpellsRequiringSpellMapBounds SpellMgr::GetSpellsRequiringSpellBounds(uint32 spell_id) const
{
    return mSpellsReqSpell.equal_range(spell_id);
}

bool SpellMgr::IsSpellRequiringSpell(uint32 spellid, uint32 req_spellid) const
{
    SpellsRequiringSpellMapBounds spellsRequiringSpell = GetSpellsRequiringSpellBounds(req_spellid);
    for (SpellsRequiringSpellMap::const_iterator itr = spellsRequiringSpell.first; itr != spellsRequiringSpell.second; ++itr)
    {
        if (itr->second == spellid)
            return true;
    }
    return false;
}

SpellLearnSkillNode const* SpellMgr::GetSpellLearnSkill(uint32 spell_id) const
{
    SpellLearnSkillMap::const_iterator itr = mSpellLearnSkills.find(spell_id);
    if (itr != mSpellLearnSkills.end())
        return &itr->second;
    else
        return NULL;
}

SpellLearnSpellMapBounds SpellMgr::GetSpellLearnSpellMapBounds(uint32 spell_id) const
{
    return mSpellLearnSpells.equal_range(spell_id);
}

bool SpellMgr::IsSpellLearnSpell(uint32 spell_id) const
{
    return mSpellLearnSpells.find(spell_id) != mSpellLearnSpells.end();
}

bool SpellMgr::IsSpellLearnToSpell(uint32 spell_id1, uint32 spell_id2) const
{
    SpellLearnSpellMapBounds bounds = GetSpellLearnSpellMapBounds(spell_id1);
    for (SpellLearnSpellMap::const_iterator i = bounds.first; i != bounds.second; ++i)
        if (i->second.spell == spell_id2)
            return true;
    return false;
}

SpellTargetPosition const* SpellMgr::GetSpellTargetPosition(uint32 spell_id, SpellEffIndex effIndex) const
{
    SpellTargetPositionMap::const_iterator itr = mSpellTargetPositions.find(std::make_pair(spell_id, effIndex));
    if (itr != mSpellTargetPositions.end())
        return &itr->second;
    return NULL;
}

SpellSpellGroupMapBounds SpellMgr::GetSpellSpellGroupMapBounds(uint32 spell_id) const
{
    spell_id = GetFirstSpellInChain(spell_id);
    return mSpellSpellGroup.equal_range(spell_id);
}

bool SpellMgr::IsSpellMemberOfSpellGroup(uint32 spellid, SpellGroup groupid) const
{
    SpellSpellGroupMapBounds spellGroup = GetSpellSpellGroupMapBounds(spellid);
    for (SpellSpellGroupMap::const_iterator itr = spellGroup.first; itr != spellGroup.second; ++itr)
    {
        if (itr->second == groupid)
            return true;
    }
    return false;
}

SpellGroupSpellMapBounds SpellMgr::GetSpellGroupSpellMapBounds(SpellGroup group_id) const
{
    return mSpellGroupSpell.equal_range(group_id);
}

void SpellMgr::GetSetOfSpellsInSpellGroup(SpellGroup group_id, std::set<uint32>& foundSpells) const
{
    std::set<SpellGroup> usedGroups;
    GetSetOfSpellsInSpellGroup(group_id, foundSpells, usedGroups);
}

void SpellMgr::GetSetOfSpellsInSpellGroup(SpellGroup group_id, std::set<uint32>& foundSpells, std::set<SpellGroup>& usedGroups) const
{
    if (usedGroups.find(group_id) != usedGroups.end())
        return;
    usedGroups.insert(group_id);

    SpellGroupSpellMapBounds groupSpell = GetSpellGroupSpellMapBounds(group_id);
    for (SpellGroupSpellMap::const_iterator itr = groupSpell.first; itr != groupSpell.second; ++itr)
    {
        if (itr->second < 0)
        {
            SpellGroup currGroup = (SpellGroup)abs(itr->second);
            GetSetOfSpellsInSpellGroup(currGroup, foundSpells, usedGroups);
        }
        else
        {
            foundSpells.insert(itr->second);
        }
    }
}

bool SpellMgr::AddSameEffectStackRuleSpellGroups(SpellInfo const* spellInfo, int32 amount, std::map<SpellGroup, int32>& groups) const
{
    uint32 spellId = spellInfo->GetFirstRankSpell()->Id;
    SpellSpellGroupMapBounds spellGroup = GetSpellSpellGroupMapBounds(spellId);
    // Find group with SPELL_GROUP_STACK_RULE_EXCLUSIVE_SAME_EFFECT if it belongs to one
    for (SpellSpellGroupMap::const_iterator itr = spellGroup.first; itr != spellGroup.second; ++itr)
    {
        SpellGroup group = itr->second;
        SpellGroupStackMap::const_iterator found = mSpellGroupStack.find(group);
        if (found != mSpellGroupStack.end())
        {
            if (found->second == SPELL_GROUP_STACK_RULE_EXCLUSIVE_SAME_EFFECT)
            {
                // Put the highest amount in the map
                if (groups.find(group) == groups.end())
                    groups[group] = amount;
                else
                {
                    int32 curr_amount = groups[group];
                    // Take absolute value because this also counts for the highest negative aura
                    if (abs(curr_amount) < abs(amount))
                        groups[group] = amount;
                }
                // return because a spell should be in only one SPELL_GROUP_STACK_RULE_EXCLUSIVE_SAME_EFFECT group
                return true;
            }
        }
    }
    // Not in a SPELL_GROUP_STACK_RULE_EXCLUSIVE_SAME_EFFECT group, so return false
    return false;
}

SpellGroupStackRule SpellMgr::CheckSpellGroupStackRules(SpellInfo const* spellInfo1, SpellInfo const* spellInfo2) const
{
    uint32 spellid_1 = spellInfo1->GetFirstRankSpell()->Id;
    uint32 spellid_2 = spellInfo2->GetFirstRankSpell()->Id;
    if (spellid_1 == spellid_2)
        return SPELL_GROUP_STACK_RULE_DEFAULT;
    // find SpellGroups which are common for both spells
    SpellSpellGroupMapBounds spellGroup1 = GetSpellSpellGroupMapBounds(spellid_1);
    std::set<SpellGroup> groups;
    for (SpellSpellGroupMap::const_iterator itr = spellGroup1.first; itr != spellGroup1.second; ++itr)
    {
        if (IsSpellMemberOfSpellGroup(spellid_2, itr->second))
        {
            bool add = true;
            SpellGroupSpellMapBounds groupSpell = GetSpellGroupSpellMapBounds(itr->second);
            for (SpellGroupSpellMap::const_iterator itr2 = groupSpell.first; itr2 != groupSpell.second; ++itr2)
            {
                if (itr2->second < 0)
                {
                    SpellGroup currGroup = (SpellGroup)abs(itr2->second);
                    if (IsSpellMemberOfSpellGroup(spellid_1, currGroup) && IsSpellMemberOfSpellGroup(spellid_2, currGroup))
                    {
                        add = false;
                        break;
                    }
                }
            }
            if (add)
                groups.insert(itr->second);
        }
    }

    SpellGroupStackRule rule = SPELL_GROUP_STACK_RULE_DEFAULT;

    for (std::set<SpellGroup>::iterator itr = groups.begin(); itr!= groups.end(); ++itr)
    {
        SpellGroupStackMap::const_iterator found = mSpellGroupStack.find(*itr);
        if (found != mSpellGroupStack.end())
            rule = found->second;
        if (rule)
            break;
    }
    return rule;
}

SpellGroupStackRule SpellMgr::GetSpellGroupStackRule(SpellGroup group) const
{
    SpellGroupStackMap::const_iterator itr = mSpellGroupStack.find(group);
    if (itr != mSpellGroupStack.end())
       return itr->second;

    return SPELL_GROUP_STACK_RULE_DEFAULT;
}

SpellProcEventEntry const* SpellMgr::GetSpellProcEvent(uint32 spellId) const
{
    SpellProcEventMap::const_iterator itr = mSpellProcEventMap.find(spellId);
    if (itr != mSpellProcEventMap.end())
        return &itr->second;
    return NULL;
}

bool SpellMgr::IsSpellProcEventCanTriggeredBy(SpellProcEventEntry const* spellProcEvent, uint32 EventProcFlag, SpellInfo const* procSpell, uint32 procFlags, uint32 procExtra, bool active) const
{
    // No extra req need
    uint32 procEvent_procEx = PROC_EX_NONE;

    // check prockFlags for condition
    if ((procFlags & EventProcFlag) == 0)
        return false;

    bool hasFamilyMask = false;

    /* Check Periodic Auras

    *Dots can trigger if spell has no PROC_FLAG_SUCCESSFUL_NEGATIVE_MAGIC_SPELL
        nor PROC_FLAG_TAKEN_POSITIVE_MAGIC_SPELL

    *Only Hots can trigger if spell has PROC_FLAG_TAKEN_POSITIVE_MAGIC_SPELL

    *Only dots can trigger if spell has both positivity flags or PROC_FLAG_SUCCESSFUL_NEGATIVE_MAGIC_SPELL

    *Aura has to have PROC_FLAG_TAKEN_POSITIVE_MAGIC_SPELL or spellfamily specified to trigger from Hot

    */

    if (procFlags & PROC_FLAG_DONE_PERIODIC)
    {
        if (EventProcFlag & PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_NEG)
        {
            if (!(procExtra & PROC_EX_INTERNAL_DOT))
                return false;
        }
        else if (procExtra & PROC_EX_INTERNAL_HOT)
            procExtra |= PROC_EX_INTERNAL_REQ_FAMILY;
        else if (EventProcFlag & PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_POS)


            return false;
    }

    if (procFlags & PROC_FLAG_TAKEN_PERIODIC)
    {
        if (EventProcFlag & PROC_FLAG_TAKEN_SPELL_MAGIC_DMG_CLASS_POS)
        {
            if (!(procExtra & PROC_EX_INTERNAL_HOT))
                return false;
        }
        else if (procExtra & PROC_EX_INTERNAL_HOT)
            procExtra |= PROC_EX_INTERNAL_REQ_FAMILY;
        else if (EventProcFlag & PROC_FLAG_TAKEN_SPELL_NONE_DMG_CLASS_POS)
            return false;
    }
    // Trap casts are active by default
    if (procFlags & PROC_FLAG_DONE_TRAP_ACTIVATION)
        active = true;

    // Always trigger for this
    if (procFlags & (PROC_FLAG_KILLED | PROC_FLAG_KILL | PROC_FLAG_DEATH))
        return true;

    if (spellProcEvent)     // Exist event data
    {
        // Store extra req
        procEvent_procEx = spellProcEvent->procEx;

        // For melee triggers
        if (procSpell == NULL)
        {
            // Check (if set) for school (melee attack have Normal school)
            if (spellProcEvent->schoolMask && (spellProcEvent->schoolMask & SPELL_SCHOOL_MASK_NORMAL) == 0)
                return false;
        }
        else // For spells need check school/spell family/family mask
        {
            // Check (if set) for school
            if (spellProcEvent->schoolMask && (spellProcEvent->schoolMask & procSpell->SchoolMask) == 0)
                return false;

            // Check (if set) for spellFamilyName
            if (spellProcEvent->spellFamilyName && (spellProcEvent->spellFamilyName != procSpell->SpellFamilyName))
                return false;

            // spellFamilyName is Ok need check for spellFamilyMask if present
            if (spellProcEvent->spellFamilyMask)
            {
                if (!(spellProcEvent->spellFamilyMask & procSpell->SpellFamilyFlags))
                    return false;
                hasFamilyMask = true;
                // Some spells are not considered as active even with have spellfamilyflags
                if (!(procEvent_procEx & PROC_EX_ONLY_ACTIVE_SPELL))
                    active = true;
            }
        }
    }

    if (procExtra & (PROC_EX_INTERNAL_REQ_FAMILY))
    {
        if (!hasFamilyMask)
            return false;
    }

    // Check for extra req (if none) and hit/crit
    if (procEvent_procEx == PROC_EX_NONE)
    {
        // No extra req, so can trigger only for hit/crit - spell has to be active
        if ((procExtra & (PROC_EX_NORMAL_HIT|PROC_EX_CRITICAL_HIT)) && active)
            return true;
    }
    else // Passive spells hits here only if resist/reflect/immune/evade
    {
        if (procExtra & AURA_SPELL_PROC_EX_MASK)
        {
            // if spell marked as procing only from not active spells
            if (active && procEvent_procEx & PROC_EX_NOT_ACTIVE_SPELL)
                return false;
            // if spell marked as procing only from active spells
            if (!active && procEvent_procEx & PROC_EX_ONLY_ACTIVE_SPELL)
                return false;
            // Exist req for PROC_EX_EX_TRIGGER_ALWAYS
            if (procEvent_procEx & PROC_EX_EX_TRIGGER_ALWAYS)
                return true;
            // PROC_EX_NOT_ACTIVE_SPELL and PROC_EX_ONLY_ACTIVE_SPELL flags handle: if passed checks before
            if ((procExtra & (PROC_EX_NORMAL_HIT|PROC_EX_CRITICAL_HIT)) && ((procEvent_procEx & (AURA_SPELL_PROC_EX_MASK)) == 0))
                return true;
        }
        // Check Extra Requirement like (hit/crit/miss/resist/parry/dodge/block/immune/reflect/absorb and other)
        if (procEvent_procEx & procExtra)
            return true;
    }
    return false;
}

SpellProcEntry const* SpellMgr::GetSpellProcEntry(uint32 spellId) const
{
    SpellProcMap::const_iterator itr = mSpellProcMap.find(spellId);
    if (itr != mSpellProcMap.end())
        return &itr->second;
    return NULL;
}

bool SpellMgr::CanSpellTriggerProcOnEvent(SpellProcEntry const& procEntry, ProcEventInfo& eventInfo) const
{
    // proc type doesn't match
    if (!(eventInfo.GetTypeMask() & procEntry.typeMask))
        return false;

    // check XP or honor target requirement
    if (procEntry.attributesMask & PROC_ATTR_REQ_EXP_OR_HONOR)
        if (Player* actor = eventInfo.GetActor()->ToPlayer())
            if (eventInfo.GetActionTarget() && !actor->isHonorOrXPTarget(eventInfo.GetActionTarget()))
                return false;

    // always trigger for these types
    if (eventInfo.GetTypeMask() & (PROC_FLAG_KILLED | PROC_FLAG_KILL | PROC_FLAG_DEATH))
        return true;

    // check school mask (if set) for other trigger types
    if (procEntry.schoolMask && !(eventInfo.GetSchoolMask() & procEntry.schoolMask))
        return false;

    // check spell family name/flags (if set) for spells
    if (eventInfo.GetTypeMask() & (PERIODIC_PROC_FLAG_MASK | SPELL_PROC_FLAG_MASK | PROC_FLAG_DONE_TRAP_ACTIVATION))
    {
        if (procEntry.spellFamilyName && (procEntry.spellFamilyName != eventInfo.GetSpellInfo()->SpellFamilyName))
            return false;

        if (procEntry.spellFamilyMask && !(procEntry.spellFamilyMask & eventInfo.GetSpellInfo()->SpellFamilyFlags))
            return false;
    }

    // check spell type mask (if set)
    if (eventInfo.GetTypeMask() & (SPELL_PROC_FLAG_MASK | PERIODIC_PROC_FLAG_MASK))
    {
        if (procEntry.spellTypeMask && !(eventInfo.GetSpellTypeMask() & procEntry.spellTypeMask))
            return false;
    }

    // check spell phase mask
    if (eventInfo.GetTypeMask() & REQ_SPELL_PHASE_PROC_FLAG_MASK)
    {
        if (!(eventInfo.GetSpellPhaseMask() & procEntry.spellPhaseMask))
            return false;
    }

    // check hit mask (on taken hit or on done hit, but not on spell cast phase)
    if ((eventInfo.GetTypeMask() & TAKEN_HIT_PROC_FLAG_MASK) || ((eventInfo.GetTypeMask() & DONE_HIT_PROC_FLAG_MASK) && !(eventInfo.GetSpellPhaseMask() & PROC_SPELL_PHASE_CAST)))
    {
        uint32 hitMask = procEntry.hitMask;
        // get default values if hit mask not set
        if (!hitMask)
        {
            // for taken procs allow normal + critical hits by default
            if (eventInfo.GetTypeMask() & TAKEN_HIT_PROC_FLAG_MASK)
                hitMask |= PROC_HIT_NORMAL | PROC_HIT_CRITICAL;
            // for done procs allow normal + critical + absorbs by default
            else
                hitMask |= PROC_HIT_NORMAL | PROC_HIT_CRITICAL | PROC_HIT_ABSORB;
        }
        if (!(eventInfo.GetHitMask() & hitMask))
            return false;
    }

    return true;
}

SpellBonusEntry const* SpellMgr::GetSpellBonusData(uint32 spellId) const
{
    // Lookup data
    SpellBonusMap::const_iterator itr = mSpellBonusMap.find(spellId);
    if (itr != mSpellBonusMap.end())
        return &itr->second;
    // Not found, try lookup for 1 spell rank if exist
    if (uint32 rank_1 = GetFirstSpellInChain(spellId))
    {
        SpellBonusMap::const_iterator itr2 = mSpellBonusMap.find(rank_1);
        if (itr2 != mSpellBonusMap.end())
            return &itr2->second;
    }
    return NULL;
}

SpellThreatEntry const* SpellMgr::GetSpellThreatEntry(uint32 spellID) const
{
    SpellThreatMap::const_iterator itr = mSpellThreatMap.find(spellID);
    if (itr != mSpellThreatMap.end())
        return &itr->second;
    else
    {
        uint32 firstSpell = GetFirstSpellInChain(spellID);
        itr = mSpellThreatMap.find(firstSpell);
        if (itr != mSpellThreatMap.end())
            return &itr->second;
    }
    return NULL;
}

SkillLineAbilityMapBounds SpellMgr::GetSkillLineAbilityMapBounds(uint32 spell_id) const
{
    return mSkillLineAbilityMap.equal_range(spell_id);
}

PetAura const* SpellMgr::GetPetAura(uint32 spell_id, uint8 eff) const
{
    SpellPetAuraMap::const_iterator itr = mSpellPetAuraMap.find((spell_id<<8) + eff);
    if (itr != mSpellPetAuraMap.end())
        return &itr->second;
    else
        return NULL;
}

SpellEnchantProcEntry const* SpellMgr::GetSpellEnchantProcEvent(uint32 enchId) const
{
    SpellEnchantProcEventMap::const_iterator itr = mSpellEnchantProcEventMap.find(enchId);
    if (itr != mSpellEnchantProcEventMap.end())
        return &itr->second;
    return NULL;
}

bool SpellMgr::IsArenaAllowedEnchancment(uint32 ench_id) const
{
    return mEnchantCustomAttr[ench_id];
}

const std::vector<int32>* SpellMgr::GetSpellLinked(int32 spell_id) const
{
    SpellLinkedMap::const_iterator itr = mSpellLinkedMap.find(spell_id);
    return itr != mSpellLinkedMap.end() ? &(itr->second) : NULL;
}

PetLevelupSpellSet const* SpellMgr::GetPetLevelupSpellList(uint32 petFamily) const
{
    PetLevelupSpellMap::const_iterator itr = mPetLevelupSpellMap.find(petFamily);
    if (itr != mPetLevelupSpellMap.end())
        return &itr->second;
    else
        return NULL;
}

PetDefaultSpellsEntry const* SpellMgr::GetPetDefaultSpellsEntry(int32 id) const
{
    PetDefaultSpellsMap::const_iterator itr = mPetDefaultSpellsMap.find(id);
    if (itr != mPetDefaultSpellsMap.end())
        return &itr->second;
    return NULL;
}

SpellAreaMapBounds SpellMgr::GetSpellAreaMapBounds(uint32 spell_id) const
{
    return mSpellAreaMap.equal_range(spell_id);
}

SpellAreaForQuestMapBounds SpellMgr::GetSpellAreaForQuestMapBounds(uint32 quest_id) const
{
    return mSpellAreaForQuestMap.equal_range(quest_id);
}

SpellAreaForQuestMapBounds SpellMgr::GetSpellAreaForQuestEndMapBounds(uint32 quest_id) const
{
    return mSpellAreaForQuestEndMap.equal_range(quest_id);
}

SpellAreaForAuraMapBounds SpellMgr::GetSpellAreaForAuraMapBounds(uint32 spell_id) const
{
    return mSpellAreaForAuraMap.equal_range(spell_id);
}

SpellAreaForAreaMapBounds SpellMgr::GetSpellAreaForAreaMapBounds(uint32 area_id) const
{
    return mSpellAreaForAreaMap.equal_range(area_id);
}

bool SpellArea::IsFitToRequirements(Player const* player, uint32 newZone, uint32 newArea) const
{
    if (gender != GENDER_NONE)                   // not in expected gender
        if (!player || gender != player->getGender())
            return false;

    if (raceMask)                                // not in expected race
        if (!player || !(raceMask & player->getRaceMask()))
            return false;

    if (areaId)                                  // not in expected zone
        if (newZone != areaId && newArea != areaId)
            return false;

    if (questStart)                              // not in expected required quest state
        if (!player || (((1 << player->GetQuestStatus(questStart)) & questStartStatus) == 0))
            return false;

    if (questEnd)                                // not in expected forbidden quest state
        if (!player || (((1 << player->GetQuestStatus(questEnd)) & questEndStatus) == 0))
            return false;

    if (auraSpell)                               // not have expected aura
        if (!player || (auraSpell > 0 && !player->HasAura(auraSpell)) || (auraSpell < 0 && player->HasAura(-auraSpell)))
            return false;

    // Extra conditions -- leaving the possibility add extra conditions...
    switch (spellId)
    {
        case 91604: // No fly Zone - Wintergrasp
        {
            if (!player)
                return false;

            Battlefield* Bf = sBattlefieldMgr->GetBattlefieldToZoneId(player->GetZoneId());
            if (!Bf || Bf->CanFlyIn() || (!player->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) && !player->HasAuraType(SPELL_AURA_FLY)))
                return false;
            break;
        }
        case 68719: // Oil Refinery - Isle of Conquest.
        case 68720: // Quarry - Isle of Conquest.
        {
            if (!player || player->GetBattlegroundTypeId() != BATTLEGROUND_IC || !player->GetBattleground())
                return false;

            uint8 nodeType = spellId == 68719 ? NODE_TYPE_REFINERY : NODE_TYPE_QUARRY;
            uint8 nodeState = player->GetTeamId() == TEAM_ALLIANCE ? NODE_STATE_CONTROLLED_A : NODE_STATE_CONTROLLED_H;

            BattlegroundIC* pIC = static_cast<BattlegroundIC*>(player->GetBattleground());
            if (pIC->GetNodeState(nodeType) == nodeState)
                return true;

            return false;
        }
        case 56618: // Horde Controls Factory Phase Shift
        case 56617: // Alliance Controls Factory Phase Shift
        {
            if (!player)
                return false;

            Battlefield* bf = sBattlefieldMgr->GetBattlefieldToZoneId(player->GetZoneId());

            if (!bf || bf->GetTypeId() != BATTLEFIELD_WG)
                return false;

            // team that controls the workshop in the specified area
            uint32 team = bf->GetData(newArea);

            if (team == TEAM_HORDE)
                return spellId == 56618;
            else if (team == TEAM_ALLIANCE)
                return spellId == 56617;
            break;
        }
        case 57940: // Essence of Wintergrasp - Northrend
        case 58045: // Essence of Wintergrasp - Wintergrasp
        {
            if (!player)
                return false;

            if (Battlefield* battlefieldWG = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_WG))
                return battlefieldWG->IsEnabled() && (player->GetTeamId() == battlefieldWG->GetDefenderTeam()) && !battlefieldWG->IsWarTime();
            break;
        }
        case 74411: // Battleground - Dampening
        {
            if (!player)
                return false;

            if (Battlefield* bf = sBattlefieldMgr->GetBattlefieldToZoneId(player->GetZoneId()))
                return bf->IsWarTime();
            break;
        }

    }

    return true;
}

void SpellMgr::LoadSpellRanks()
{
    uint32 oldMSTime = getMSTime();

    // cleanup core data before reload - remove reference to ChainNode from SpellInfo
    for (SpellChainMap::iterator itr = mSpellChains.begin(); itr != mSpellChains.end(); ++itr)
    {
        mSpellInfoMap[itr->first]->ChainEntry = NULL;
    }
    mSpellChains.clear();
    //                                                     0             1      2
    QueryResult result = WorldDatabase.Query("SELECT first_spell_id, spell_id, rank from spell_ranks ORDER BY first_spell_id, rank");

    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell rank records. DB table `spell_ranks` is empty.");

        return;
    }

    uint32 count = 0;
    bool finished = false;

    do
    {
                        // spellid, rank
        std::list < std::pair < int32, int32 > > rankChain;
        int32 currentSpell = -1;
        int32 lastSpell = -1;

        // fill one chain
        while (currentSpell == lastSpell && !finished)
        {
            Field* fields = result->Fetch();

            currentSpell = fields[0].GetUInt32();
            if (lastSpell == -1)
                lastSpell = currentSpell;
            uint32 spell_id = fields[1].GetUInt32();
            uint32 rank = fields[2].GetUInt8();

            // don't drop the row if we're moving to the next rank
            if (currentSpell == lastSpell)
            {
                rankChain.push_back(std::make_pair(spell_id, rank));
                if (!result->NextRow())
                    finished = true;
            }
            else
                break;
        }
        // check if chain is made with valid first spell
        SpellInfo const* first = GetSpellInfo(lastSpell);
        if (!first)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell rank identifier(first_spell_id) %u listed in `spell_ranks` does not exist!", lastSpell);
            continue;
        }
        // check if chain is long enough
        if (rankChain.size() < 2)
        {
            sLog->outError(LOG_FILTER_SQL, "There is only 1 spell rank for identifier(first_spell_id) %u in `spell_ranks`, entry is not needed!", lastSpell);
            continue;
        }
        int32 curRank = 0;
        bool valid = true;
        // check spells in chain
        for (std::list<std::pair<int32, int32> >::iterator itr = rankChain.begin(); itr!= rankChain.end(); ++itr)
        {
            SpellInfo const* spell = GetSpellInfo(itr->first);
            if (!spell)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u (rank %u) listed in `spell_ranks` for chain %u does not exist!", itr->first, itr->second, lastSpell);
                valid = false;
                break;
            }
            ++curRank;
            if (itr->second != curRank)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u (rank %u) listed in `spell_ranks` for chain %u does not have proper rank value(should be %u)!", itr->first, itr->second, lastSpell, curRank);
                valid = false;
                break;
            }
        }
        if (!valid)
            continue;
        int32 prevRank = 0;
        // insert the chain
        std::list<std::pair<int32, int32> >::iterator itr = rankChain.begin();
        do
        {
            ++count;
            int32 addedSpell = itr->first;
            mSpellChains[addedSpell].first = GetSpellInfo(lastSpell);
            mSpellChains[addedSpell].last = GetSpellInfo(rankChain.back().first);
            mSpellChains[addedSpell].rank = itr->second;
            mSpellChains[addedSpell].prev = GetSpellInfo(prevRank);
            mSpellInfoMap[addedSpell]->ChainEntry = &mSpellChains[addedSpell];
            prevRank = addedSpell;
            ++itr;

            if (itr == rankChain.end())
            {
                mSpellChains[addedSpell].next = NULL;
                break;
            }
            else
                mSpellChains[addedSpell].next = GetSpellInfo(itr->first);
        }
        while (true);
    } while (!finished);

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell rank records in %u ms", count, GetMSTimeDiffToNow(oldMSTime));

}

void SpellMgr::LoadSpellRequired()
{
    uint32 oldMSTime = getMSTime();

    mSpellsReqSpell.clear();                                   // need for reload case
    mSpellReq.clear();                                         // need for reload case

    //                                                   0        1
    QueryResult result = WorldDatabase.Query("SELECT spell_id, req_spell from spell_required");

    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell required records. DB table `spell_required` is empty.");

        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 spell_id = fields[0].GetUInt32();
        uint32 spell_req = fields[1].GetUInt32();

        // check if chain is made with valid first spell
        SpellInfo const* spell = GetSpellInfo(spell_id);
        if (!spell)
        {
            sLog->outError(LOG_FILTER_SQL, "spell_id %u in `spell_required` table is not found in dbcs, skipped", spell_id);
            continue;
        }

        SpellInfo const* req_spell = GetSpellInfo(spell_req);
        if (!req_spell)
        {
            sLog->outError(LOG_FILTER_SQL, "req_spell %u in `spell_required` table is not found in dbcs, skipped", spell_req);
            continue;
        }

        if (GetFirstSpellInChain(spell_id) == GetFirstSpellInChain(spell_req))
        {
            sLog->outError(LOG_FILTER_SQL, "req_spell %u and spell_id %u in `spell_required` table are ranks of the same spell, entry not needed, skipped", spell_req, spell_id);
            continue;
        }

        if (IsSpellRequiringSpell(spell_id, spell_req))
        {
            sLog->outError(LOG_FILTER_SQL, "duplicated entry of req_spell %u and spell_id %u in `spell_required`, skipped", spell_req, spell_id);
            continue;
        }

        mSpellReq.insert (std::pair<uint32, uint32>(spell_id, spell_req));
        mSpellsReqSpell.insert (std::pair<uint32, uint32>(spell_req, spell_id));
        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell required records in %u ms", count, GetMSTimeDiffToNow(oldMSTime));

}

void SpellMgr::LoadSpellLearnSkills()
{
    uint32 oldMSTime = getMSTime();

    mSpellLearnSkills.clear();                              // need for reload case

    // search auto-learned skills and add its to map also for use in unlearn spells/talents
    uint32 dbc_count = 0;
    for (uint32 spell = 0; spell < GetSpellInfoStoreSize(); ++spell)
    {
        SpellInfo const* entry = GetSpellInfo(spell);

        if (!entry)
            continue;

        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (entry->Effects[i].Effect == SPELL_EFFECT_SKILL)
            {
                SpellLearnSkillNode dbc_node;
                dbc_node.skill = entry->Effects[i].MiscValue;
                dbc_node.step  = entry->Effects[i].CalcValue();
                if (dbc_node.skill != SKILL_RIDING)
                    dbc_node.value = 1;
                else
                    dbc_node.value = dbc_node.step * 75;
                dbc_node.maxvalue = dbc_node.step * 75;
                mSpellLearnSkills[spell] = dbc_node;
                ++dbc_count;
                break;
            }
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u Spell Learn Skills from DBC in %u ms", dbc_count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellLearnSpells()
{
    uint32 oldMSTime = getMSTime();

    mSpellLearnSpells.clear();                              // need for reload case

    //                                                  0      1        2
    QueryResult result = WorldDatabase.Query("SELECT entry, SpellID, Active FROM spell_learn_spell");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell learn spells. DB table `spell_learn_spell` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 spell_id = fields[0].GetUInt32();

        SpellLearnSpellNode node;
        node.spell       = fields[1].GetUInt32();
        node.active      = fields[2].GetBool();
        node.autoLearned = false;

        if (!GetSpellInfo(spell_id))
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_learn_spell` does not exist", spell_id);
            continue;
        }

        if (!GetSpellInfo(node.spell))
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_learn_spell` learning not existed spell %u", spell_id, node.spell);
            continue;
        }

        if (GetTalentSpellCost(node.spell))
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_learn_spell` attempt learning talent spell %u, skipped", spell_id, node.spell);
            continue;
        }

        mSpellLearnSpells.insert(SpellLearnSpellMap::value_type(spell_id, node));

        ++count;
    } while (result->NextRow());

    // search auto-learned spells and add its to map also for use in unlearn spells/talents
    uint32 dbc_count = 0;
    for (uint32 spell = 0; spell < GetSpellInfoStoreSize(); ++spell)
    {
        SpellInfo const* entry = GetSpellInfo(spell);

        if (!entry)
            continue;

        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (entry->Effects[i].Effect == SPELL_EFFECT_LEARN_SPELL)
            {
                SpellLearnSpellNode dbc_node;
                dbc_node.spell = entry->Effects[i].TriggerSpell;
                dbc_node.active = true;                     // all dbc based learned spells is active (show in spell book or hide by client itself)

                // ignore learning not existed spells (broken/outdated/or generic learnig spell 483
                if (!GetSpellInfo(dbc_node.spell))
                    continue;

                // talent or passive spells or skill-step spells auto-casted and not need dependent learning,
                // pet teaching spells must not be dependent learning (casted)
                // other required explicit dependent learning
                dbc_node.autoLearned = entry->Effects[i].TargetA.GetTarget() == TARGET_UNIT_PET || GetTalentSpellCost(spell) > 0 || entry->IsPassive() || entry->HasEffect(SPELL_EFFECT_SKILL_STEP);

                SpellLearnSpellMapBounds db_node_bounds = GetSpellLearnSpellMapBounds(spell);

                bool found = false;
                for (SpellLearnSpellMap::const_iterator itr = db_node_bounds.first; itr != db_node_bounds.second; ++itr)
                {
                    if (itr->second.spell == dbc_node.spell)
                    {
                        sLog->outError(LOG_FILTER_SQL, "Spell %u auto-learn spell %u in spell.dbc then the record in `spell_learn_spell` is redundant, please fix DB.",
                            spell, dbc_node.spell);
                        found = true;
                        break;
                    }
                }

                if (!found)                                  // add new spell-spell pair if not found
                {
                    mSpellLearnSpells.insert(SpellLearnSpellMap::value_type(spell, dbc_node));
                    ++dbc_count;
                }
            }
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell learn spells + %u found in DBC in %u ms", count, dbc_count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellTargetPositions()
{
    uint32 oldMSTime = getMSTime();

    mSpellTargetPositions.clear();                                // need for reload case

    //                                                0      1          2             3                  4                  5                   6
    QueryResult result = WorldDatabase.Query("SELECT id, effIndex, target_map, target_position_x, target_position_y, target_position_z, target_orientation FROM spell_target_position");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell target coordinates. DB table `spell_target_position` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 Spell_ID = fields[0].GetUInt32();
        SpellEffIndex effIndex = SpellEffIndex(fields[1].GetUInt8());

        SpellTargetPosition st;

        st.target_mapId       = fields[2].GetUInt16();
        st.target_X           = fields[3].GetFloat();
        st.target_Y           = fields[4].GetFloat();
        st.target_Z           = fields[5].GetFloat();
        st.target_Orientation = fields[6].GetFloat();

        MapEntry const* mapEntry = sMapStore.LookupEntry(st.target_mapId);
        if (!mapEntry)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell (Id: %u, effIndex: %u) target map (ID: %u) does not exist in `Map.dbc`.", Spell_ID, effIndex, st.target_mapId);
            continue;
        }

        if (st.target_X==0 && st.target_Y==0 && st.target_Z==0)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell (Id: %u, effIndex: %u) target coordinates not provided.", Spell_ID, effIndex);
            continue;
        }

        SpellInfo const* spellInfo = GetSpellInfo(Spell_ID);
        if (!spellInfo)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell (ID:%u) listed in `spell_target_position` does not exist.", Spell_ID);
            continue;
        }

        if (spellInfo->Effects[effIndex].TargetA.GetTarget() == TARGET_DEST_DB || spellInfo->Effects[effIndex].TargetB.GetTarget() == TARGET_DEST_DB)
        {
            std::pair<uint32, SpellEffIndex> key = std::make_pair(Spell_ID, effIndex);
            mSpellTargetPositions[key] = st;
            ++count;
        }
        else
        {
            sLog->outError(LOG_FILTER_SQL, "Spell (Id: %u, effIndex: %u) listed in `spell_target_position` does not have target TARGET_DEST_DB (17).", Spell_ID, effIndex);
            continue;
        }

    } while (result->NextRow());

    /*
    // Check all spells
    for (uint32 i = 1; i < GetSpellInfoStoreSize; ++i)
    {
        SpellInfo const* spellInfo = GetSpellInfo(i);
        if (!spellInfo)
            continue;

        bool found = false;
        for (int j = 0; j < MAX_SPELL_EFFECTS; ++j)
        {
            switch (spellInfo->Effects[j].TargetA)
            {
                case TARGET_DEST_DB:
                    found = true;
                    break;
            }
            if (found)
                break;
            switch (spellInfo->Effects[j].TargetB)
            {
                case TARGET_DEST_DB:
                    found = true;
                    break;
            }
            if (found)
                break;
        }
        if (found)
        {
            if (!sSpellMgr->GetSpellTargetPosition(i))
                sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "Spell (ID: %u) does not have record in `spell_target_position`", i);
        }
    }*/

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell teleport coordinates in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellGroups()
{
    uint32 oldMSTime = getMSTime();

    mSpellSpellGroup.clear();                                  // need for reload case
    mSpellGroupSpell.clear();

    //                                                0     1
    QueryResult result = WorldDatabase.Query("SELECT id, spell_id FROM spell_group");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell group definitions. DB table `spell_group` is empty.");
        return;
    }

    std::set<uint32> groups;
    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 group_id = fields[0].GetUInt32();
        if (group_id <= SPELL_GROUP_DB_RANGE_MIN && group_id >= SPELL_GROUP_CORE_RANGE_MAX)
        {
            sLog->outError(LOG_FILTER_SQL, "SpellGroup id %u listed in `spell_group` is in core range, but is not defined in core!", group_id);
            continue;
        }
        int32 spell_id = fields[1].GetInt32();

        groups.insert(std::set<uint32>::value_type(group_id));
        mSpellGroupSpell.insert(SpellGroupSpellMap::value_type((SpellGroup)group_id, spell_id));

    } while (result->NextRow());

    for (SpellGroupSpellMap::iterator itr = mSpellGroupSpell.begin(); itr!= mSpellGroupSpell.end();)
    {
        if (itr->second < 0)
        {
            if (groups.find(abs(itr->second)) == groups.end())
            {
                sLog->outError(LOG_FILTER_SQL, "SpellGroup id %u listed in `spell_group` does not exist", abs(itr->second));
                mSpellGroupSpell.erase(itr++);
            }
            else
                ++itr;
        }
        else
        {
            SpellInfo const* spellInfo = GetSpellInfo(itr->second);

            if (!spellInfo)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_group` does not exist", itr->second);
                mSpellGroupSpell.erase(itr++);
            }
            else if (spellInfo->GetRank() > 1)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_group` is not first rank of spell", itr->second);
                mSpellGroupSpell.erase(itr++);
            }
            else
                ++itr;
        }
    }

    for (std::set<uint32>::iterator groupItr = groups.begin(); groupItr != groups.end(); ++groupItr)
    {
        std::set<uint32> spells;
        GetSetOfSpellsInSpellGroup(SpellGroup(*groupItr), spells);

        for (std::set<uint32>::iterator spellItr = spells.begin(); spellItr != spells.end(); ++spellItr)
        {
            ++count;
            mSpellSpellGroup.insert(SpellSpellGroupMap::value_type(*spellItr, SpellGroup(*groupItr)));
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell group definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellGroupStackRules()
{
    uint32 oldMSTime = getMSTime();

    mSpellGroupStack.clear();                                  // need for reload case

    //                                                       0         1
    QueryResult result = WorldDatabase.Query("SELECT group_id, stack_rule FROM spell_group_stack_rules");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell group stack rules. DB table `spell_group_stack_rules` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 group_id = fields[0].GetUInt32();
        uint8 stack_rule = fields[1].GetInt8();
        if (stack_rule >= SPELL_GROUP_STACK_RULE_MAX)
        {
            sLog->outError(LOG_FILTER_SQL, "SpellGroupStackRule %u listed in `spell_group_stack_rules` does not exist", stack_rule);
            continue;
        }

        SpellGroupSpellMapBounds spellGroup = GetSpellGroupSpellMapBounds((SpellGroup)group_id);

        if (spellGroup.first == spellGroup.second)
        {
            sLog->outError(LOG_FILTER_SQL, "SpellGroup id %u listed in `spell_group_stack_rules` does not exist", group_id);
            continue;
        }

        mSpellGroupStack[(SpellGroup)group_id] = (SpellGroupStackRule)stack_rule;

        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell group stack rules in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellProcEvents()
{
    uint32 oldMSTime = getMSTime();

    mSpellProcEventMap.clear();                             // need for reload case

    //                                                0      1           2                3                 4                 5                 6          7       8        9             10
    QueryResult result = WorldDatabase.Query("SELECT entry, SchoolMask, SpellFamilyName, SpellFamilyMask0, SpellFamilyMask1, SpellFamilyMask2, procFlags, procEx, ppmRate, CustomChance, Cooldown FROM spell_proc_event");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell proc event conditions. DB table `spell_proc_event` is empty.");
        return;
    }

    uint32 count = 0;
    uint32 customProc = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 entry = fields[0].GetUInt32();

        SpellInfo const* spell = GetSpellInfo(entry);
        if (!spell)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_proc_event` does not exist", entry);
            continue;
        }

        SpellProcEventEntry spe;

        spe.schoolMask      = fields[1].GetInt8();
        spe.spellFamilyName = fields[2].GetUInt16();
        spe.spellFamilyMask[0] = fields[3].GetUInt32();
        spe.spellFamilyMask[1] = fields[4].GetUInt32();
        spe.spellFamilyMask[2] = fields[5].GetUInt32();
        spe.procFlags       = fields[6].GetUInt32();
        spe.procEx          = fields[7].GetUInt32();
        spe.ppmRate         = fields[8].GetFloat();
        spe.customChance    = fields[9].GetFloat();
        spe.cooldown        = fields[10].GetUInt32();

        mSpellProcEventMap[entry] = spe;

        if (spell->ProcFlags == 0)
        {
            if (spe.procFlags == 0)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_proc_event` probally not triggered spell", entry);
                continue;
            }
            customProc++;
        }
        ++count;
    } while (result->NextRow());

    if (customProc)
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u extra and %u custom spell proc event conditions in %u ms",  count, customProc, GetMSTimeDiffToNow(oldMSTime));
    else
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u extra spell proc event conditions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));

}

void SpellMgr::LoadSpellProcs()
{
    uint32 oldMSTime = getMSTime();

    mSpellProcMap.clear();                             // need for reload case

    //                                                 0        1           2                3                 4                 5                 6         7              8               9        10              11             12      13        14
    QueryResult result = WorldDatabase.Query("SELECT spellId, schoolMask, spellFamilyName, spellFamilyMask0, spellFamilyMask1, spellFamilyMask2, typeMask, spellTypeMask, spellPhaseMask, hitMask, attributesMask, ratePerMinute, chance, cooldown, charges FROM spell_proc");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell proc conditions and data. DB table `spell_proc` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        int32 spellId = fields[0].GetInt32();

        bool allRanks = false;
        if (spellId < 0)
        {
            allRanks = true;
            spellId = -spellId;
        }

        SpellInfo const* spellInfo = GetSpellInfo(spellId);
        if (!spellInfo)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_proc` does not exist", spellId);
            continue;
        }

        if (allRanks)
        {
            if (spellInfo->GetFirstRankSpell()->Id != uint32(spellId))
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_proc` is not first rank of spell.", spellId);
                continue;
            }
        }

        SpellProcEntry baseProcEntry;

        baseProcEntry.schoolMask      = fields[1].GetInt8();
        baseProcEntry.spellFamilyName = fields[2].GetUInt16();
        baseProcEntry.spellFamilyMask[0] = fields[3].GetUInt32();
        baseProcEntry.spellFamilyMask[1] = fields[4].GetUInt32();
        baseProcEntry.spellFamilyMask[2] = fields[5].GetUInt32();
        baseProcEntry.typeMask        = fields[6].GetUInt32();
        baseProcEntry.spellTypeMask   = fields[7].GetUInt32();
        baseProcEntry.spellPhaseMask  = fields[8].GetUInt32();
        baseProcEntry.hitMask         = fields[9].GetUInt32();
        baseProcEntry.attributesMask  = fields[10].GetUInt32();
        baseProcEntry.ratePerMinute   = fields[11].GetFloat();
        baseProcEntry.chance          = fields[12].GetFloat();
        float cooldown                = fields[13].GetFloat();
        baseProcEntry.cooldown        = uint32(cooldown);
        baseProcEntry.charges         = fields[14].GetUInt32();

        while (spellInfo)
        {
            if (mSpellProcMap.find(spellInfo->Id) != mSpellProcMap.end())
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_proc` has duplicate entry in the table", spellInfo->Id);
                break;
            }
            SpellProcEntry procEntry = SpellProcEntry(baseProcEntry);

            // take defaults from dbcs
            if (!procEntry.typeMask)
                procEntry.typeMask = spellInfo->ProcFlags;
            if (!procEntry.charges)
                procEntry.charges = spellInfo->ProcCharges;
            if (!procEntry.chance && !procEntry.ratePerMinute)
                procEntry.chance = float(spellInfo->ProcChance);

            // validate data
            if (procEntry.schoolMask & ~SPELL_SCHOOL_MASK_ALL)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has wrong `schoolMask` set: %u", spellInfo->Id, procEntry.schoolMask);
            if (procEntry.spellFamilyName && (procEntry.spellFamilyName < 3 || procEntry.spellFamilyName > 17 || procEntry.spellFamilyName == 14 || procEntry.spellFamilyName == 16))
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has wrong `spellFamilyName` set: %u", spellInfo->Id, procEntry.spellFamilyName);
            if (procEntry.chance < 0)
            {
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has negative value in `chance` field", spellInfo->Id);
                procEntry.chance = 0;
            }
            if (procEntry.ratePerMinute < 0)
            {
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has negative value in `ratePerMinute` field", spellInfo->Id);
                procEntry.ratePerMinute = 0;
            }
            if (cooldown < 0)
            {
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has negative value in `cooldown` field", spellInfo->Id);
                procEntry.cooldown = 0;
            }
            if (procEntry.chance == 0 && procEntry.ratePerMinute == 0)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u doesn't have `chance` and `ratePerMinute` values defined, proc will not be triggered", spellInfo->Id);
            if (procEntry.charges > 99)
            {
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has too big value in `charges` field", spellInfo->Id);
                procEntry.charges = 99;
            }
            if (!procEntry.typeMask)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u doesn't have `typeMask` value defined, proc will not be triggered", spellInfo->Id);
            if (procEntry.spellTypeMask & ~PROC_SPELL_TYPE_MASK_ALL)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has wrong `spellTypeMask` set: %u", spellInfo->Id, procEntry.spellTypeMask);
            if (procEntry.spellTypeMask && !(procEntry.typeMask & (SPELL_PROC_FLAG_MASK | PERIODIC_PROC_FLAG_MASK)))
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has `spellTypeMask` value defined, but it won't be used for defined `typeMask` value", spellInfo->Id);
            if (!procEntry.spellPhaseMask && procEntry.typeMask & REQ_SPELL_PHASE_PROC_FLAG_MASK)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u doesn't have `spellPhaseMask` value defined, but it's required for defined `typeMask` value, proc will not be triggered", spellInfo->Id);
            if (procEntry.spellPhaseMask & ~PROC_SPELL_PHASE_MASK_ALL)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has wrong `spellPhaseMask` set: %u", spellInfo->Id, procEntry.spellPhaseMask);
            if (procEntry.spellPhaseMask && !(procEntry.typeMask & REQ_SPELL_PHASE_PROC_FLAG_MASK))
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has `spellPhaseMask` value defined, but it won't be used for defined `typeMask` value", spellInfo->Id);
            if (procEntry.hitMask & ~PROC_HIT_MASK_ALL)
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has wrong `hitMask` set: %u", spellInfo->Id, procEntry.hitMask);
            if (procEntry.hitMask && !(procEntry.typeMask & TAKEN_HIT_PROC_FLAG_MASK || (procEntry.typeMask & DONE_HIT_PROC_FLAG_MASK && (!procEntry.spellPhaseMask || procEntry.spellPhaseMask & (PROC_SPELL_PHASE_HIT | PROC_SPELL_PHASE_FINISH)))))
                sLog->outError(LOG_FILTER_SQL, "`spell_proc` table entry for spellId %u has `hitMask` value defined, but it won't be used for defined `typeMask` and `spellPhaseMask` values", spellInfo->Id);

            mSpellProcMap[spellInfo->Id] = procEntry;

            if (allRanks)
                spellInfo = spellInfo->GetNextRankSpell();
            else
                break;
        }
        ++count;
    }
    while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell proc conditions and data in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellBonusess()
{
    uint32 oldMSTime = getMSTime();

    mSpellBonusMap.clear();                             // need for reload case

    //                                                0      1             2          3         4
    QueryResult result = WorldDatabase.Query("SELECT entry, direct_bonus, dot_bonus, ap_bonus, ap_dot_bonus FROM spell_bonus_data");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell bonus data. DB table `spell_bonus_data` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();
        uint32 entry = fields[0].GetUInt32();

        SpellInfo const* spell = GetSpellInfo(entry);
        if (!spell)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_bonus_data` does not exist", entry);
            continue;
        }

        SpellBonusEntry& sbe = mSpellBonusMap[entry];
        sbe.direct_damage = fields[1].GetFloat();
        sbe.dot_damage    = fields[2].GetFloat();
        sbe.ap_bonus      = fields[3].GetFloat();
        sbe.ap_dot_bonus   = fields[4].GetFloat();

        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u extra spell bonus data in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellThreats()
{
    uint32 oldMSTime = getMSTime();

    mSpellThreatMap.clear();                                // need for reload case

    //                                                0      1        2       3
    QueryResult result = WorldDatabase.Query("SELECT entry, flatMod, pctMod, apPctMod FROM spell_threat");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 aggro generating spells. DB table `spell_threat` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 entry = fields[0].GetUInt32();

        if (!GetSpellInfo(entry))
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_threat` does not exist", entry);
            continue;
        }

        SpellThreatEntry ste;
        ste.flatMod  = fields[1].GetInt32();
        ste.pctMod   = fields[2].GetFloat();
        ste.apPctMod = fields[3].GetFloat();

        mSpellThreatMap[entry] = ste;
        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u SpellThreatEntries in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSkillLineAbilityMap()
{
    uint32 oldMSTime = getMSTime();

    mSkillLineAbilityMap.clear();

    uint32 count = 0;

    for (uint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i)
    {
        SkillLineAbilityEntry const* SkillInfo = sSkillLineAbilityStore.LookupEntry(i);
        if (!SkillInfo)
            continue;

        mSkillLineAbilityMap.insert(SkillLineAbilityMap::value_type(SkillInfo->spellId, SkillInfo));
        ++count;
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u SkillLineAbility MultiMap Data in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellPetAuras()
{
    uint32 oldMSTime = getMSTime();

    mSpellPetAuraMap.clear();                                  // need for reload case

    //                                                  0       1       2    3
    QueryResult result = WorldDatabase.Query("SELECT spell, effectId, pet, aura FROM spell_pet_auras");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell pet auras. DB table `spell_pet_auras` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 spell = fields[0].GetUInt32();
        uint8 eff = fields[1].GetUInt8();
        uint32 pet = fields[2].GetUInt32();
        uint32 aura = fields[3].GetUInt32();

        SpellPetAuraMap::iterator itr = mSpellPetAuraMap.find((spell<<8) + eff);
        if (itr != mSpellPetAuraMap.end())
            itr->second.AddAura(pet, aura);
        else
        {
            SpellInfo const* spellInfo = GetSpellInfo(spell);
            if (!spellInfo)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_pet_auras` does not exist", spell);
                continue;
            }
            if (spellInfo->Effects[eff].Effect != SPELL_EFFECT_DUMMY &&
               (spellInfo->Effects[eff].Effect != SPELL_EFFECT_APPLY_AURA ||
                spellInfo->Effects[eff].ApplyAuraName != SPELL_AURA_DUMMY))
            {
                sLog->outError(LOG_FILTER_SPELLS_AURAS, "Spell %u listed in `spell_pet_auras` does not have dummy aura or dummy effect", spell);
                continue;
            }

            SpellInfo const* spellInfo2 = GetSpellInfo(aura);
            if (!spellInfo2)
            {
                sLog->outError(LOG_FILTER_SQL, "Aura %u listed in `spell_pet_auras` does not exist", aura);
                continue;
            }

            PetAura pa(pet, aura, spellInfo->Effects[eff].TargetA.GetTarget() == TARGET_UNIT_PET, spellInfo->Effects[eff].CalcValue());
            mSpellPetAuraMap[(spell<<8) + eff] = pa;
        }

        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell pet auras in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// Fill custom data about enchancments
void SpellMgr::LoadEnchantCustomAttr()
{
    uint32 oldMSTime = getMSTime();

    uint32 size = sSpellItemEnchantmentStore.GetNumRows();
    mEnchantCustomAttr.resize(size);

    for (uint32 i = 0; i < size; ++i)
       mEnchantCustomAttr[i] = 0;

    uint32 count = 0;
    for (uint32 i = 0; i < GetSpellInfoStoreSize(); ++i)
    {
        SpellInfo const* spellInfo = GetSpellInfo(i);
        if (!spellInfo)
            continue;

        // TODO: find a better check
        if (!(spellInfo->AttributesEx2 & SPELL_ATTR2_PRESERVE_ENCHANT_IN_ARENA) || !(spellInfo->Attributes & SPELL_ATTR0_NOT_SHAPESHIFT))
            continue;

        for (uint32 j = 0; j < MAX_SPELL_EFFECTS; ++j)
        {
            if (spellInfo->Effects[j].Effect == SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY)
            {
                uint32 enchId = spellInfo->Effects[j].MiscValue;
                SpellItemEnchantmentEntry const* ench = sSpellItemEnchantmentStore.LookupEntry(enchId);
                if (!ench)
                    continue;
                mEnchantCustomAttr[enchId] = true;
                ++count;
                break;
            }
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u custom enchant attributes in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellEnchantProcData()
{
    uint32 oldMSTime = getMSTime();

    mSpellEnchantProcEventMap.clear();                             // need for reload case

    //                                                  0         1           2         3
    QueryResult result = WorldDatabase.Query("SELECT entry, customChance, PPMChance, procEx FROM spell_enchant_proc_data");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell enchant proc event conditions. DB table `spell_enchant_proc_data` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 enchantId = fields[0].GetUInt32();

        SpellItemEnchantmentEntry const* ench = sSpellItemEnchantmentStore.LookupEntry(enchantId);
        if (!ench)
        {
            sLog->outError(LOG_FILTER_SQL, "Enchancment %u listed in `spell_enchant_proc_data` does not exist", enchantId);
            continue;
        }

        SpellEnchantProcEntry spe;

        spe.customChance = fields[1].GetUInt32();
        spe.PPMChance = fields[2].GetFloat();
        spe.procEx = fields[3].GetUInt32();

        mSpellEnchantProcEventMap[enchantId] = spe;

        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u enchant proc data definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellLinked()
{
    uint32 oldMSTime = getMSTime();

    mSpellLinkedMap.clear();    // need for reload case

    //                                                0              1             2
    QueryResult result = WorldDatabase.Query("SELECT spell_trigger, spell_effect, type FROM spell_linked_spell");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 linked spells. DB table `spell_linked_spell` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        int32 trigger = fields[0].GetInt32();
        int32 effect = fields[1].GetInt32();
        int32 type = fields[2].GetUInt8();

        SpellInfo const* spellInfo = GetSpellInfo(abs(trigger));
        if (!spellInfo)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_linked_spell` does not exist", abs(trigger));
            continue;
        }
        spellInfo = GetSpellInfo(abs(effect));
        if (!spellInfo)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_linked_spell` does not exist", abs(effect));
            continue;
        }

        if (type) //we will find a better way when more types are needed
        {
            if (trigger > 0)
                trigger += SPELL_LINKED_MAX_SPELLS * type;
            else
                trigger -= SPELL_LINKED_MAX_SPELLS * type;
        }
        mSpellLinkedMap[trigger].push_back(effect);

        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u linked spells in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadPetLevelupSpellMap()
{
    uint32 oldMSTime = getMSTime();

    mPetLevelupSpellMap.clear();                                   // need for reload case

    uint32 count = 0;
    uint32 family_count = 0;

    for (uint32 i = 0; i < sCreatureFamilyStore.GetNumRows(); ++i)
    {
        CreatureFamilyEntry const* creatureFamily = sCreatureFamilyStore.LookupEntry(i);
        if (!creatureFamily)                                     // not exist
            continue;

        for (uint8 j = 0; j < 2; ++j)
        {
            if (!creatureFamily->skillLine[j])
                continue;

            for (uint32 k = 0; k < sSkillLineAbilityStore.GetNumRows(); ++k)
            {
                SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(k);
                if (!skillLine)
                    continue;

                //if (skillLine->skillId != creatureFamily->skillLine[0] &&
                //    (!creatureFamily->skillLine[1] || skillLine->skillId != creatureFamily->skillLine[1]))
                //    continue;

                if (skillLine->skillId != creatureFamily->skillLine[j])
                    continue;

                if (skillLine->learnOnGetSkill != ABILITY_LEARNED_ON_GET_RACE_OR_CLASS_SKILL)
                    continue;

                SpellInfo const* spell = GetSpellInfo(skillLine->spellId);
                if (!spell) // not exist or triggered or talent
                    continue;

                if (!spell->SpellLevel)
                    continue;

                PetLevelupSpellSet& spellSet = mPetLevelupSpellMap[creatureFamily->ID];
                if (spellSet.empty())
                    ++family_count;

                spellSet.insert(PetLevelupSpellSet::value_type(spell->SpellLevel, spell->Id));
                ++count;
            }
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u pet levelup and default spells for %u families in %u ms", count, family_count, GetMSTimeDiffToNow(oldMSTime));
}

bool LoadPetDefaultSpells_helper(CreatureTemplate const* cInfo, PetDefaultSpellsEntry& petDefSpells)
{
    // skip empty list;
    bool have_spell = false;
    for (uint8 j = 0; j < MAX_CREATURE_SPELL_DATA_SLOT; ++j)
    {
        if (petDefSpells.spellid[j])
        {
            have_spell = true;
            break;
        }
    }
    if (!have_spell)
        return false;

    // remove duplicates with levelupSpells if any
    if (PetLevelupSpellSet const* levelupSpells = cInfo->family ? sSpellMgr->GetPetLevelupSpellList(cInfo->family) : NULL)
    {
        for (uint8 j = 0; j < MAX_CREATURE_SPELL_DATA_SLOT; ++j)
        {
            if (!petDefSpells.spellid[j])
                continue;

            for (PetLevelupSpellSet::const_iterator itr = levelupSpells->begin(); itr != levelupSpells->end(); ++itr)
            {
                if (itr->second == petDefSpells.spellid[j])
                {
                    petDefSpells.spellid[j] = 0;
                    break;
                }
            }
        }
    }

    // skip empty list;
    have_spell = false;
    for (uint8 j = 0; j < MAX_CREATURE_SPELL_DATA_SLOT; ++j)
    {
        if (petDefSpells.spellid[j])
        {
            have_spell = true;
            break;
        }
    }

    return have_spell;
}

void SpellMgr::LoadPetDefaultSpells()
{
    uint32 oldMSTime = getMSTime();

    mPetDefaultSpellsMap.clear();

    uint32 countCreature = 0;
    uint32 countData = 0;

    CreatureTemplateContainer const* ctc = sObjectMgr->GetCreatureTemplates();
    for (CreatureTemplateContainer::const_iterator itr = ctc->begin(); itr != ctc->end(); ++itr)
    {

        if (!itr->second.PetSpellDataId)
            continue;

        // for creature with PetSpellDataId get default pet spells from dbc
        CreatureSpellDataEntry const* spellDataEntry = sCreatureSpellDataStore.LookupEntry(itr->second.PetSpellDataId);
        if (!spellDataEntry)
            continue;

        int32 petSpellsId = -int32(itr->second.PetSpellDataId);
        PetDefaultSpellsEntry petDefSpells;
        for (uint8 j = 0; j < MAX_CREATURE_SPELL_DATA_SLOT; ++j)
            petDefSpells.spellid[j] = spellDataEntry->spellId[j];

        if (LoadPetDefaultSpells_helper(&itr->second, petDefSpells))
        {
            mPetDefaultSpellsMap[petSpellsId] = petDefSpells;
            ++countData;
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded addition spells for %u pet spell data entries in %u ms", countData, GetMSTimeDiffToNow(oldMSTime));

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, "Loading summonable creature templates...");
    oldMSTime = getMSTime();

    // different summon spells
    for (uint32 i = 0; i < GetSpellInfoStoreSize(); ++i)
    {
        SpellInfo const* spellEntry = GetSpellInfo(i);
        if (!spellEntry)
            continue;

        for (uint8 k = 0; k < MAX_SPELL_EFFECTS; ++k)
        {
            if (spellEntry->Effects[k].Effect == SPELL_EFFECT_SUMMON || spellEntry->Effects[k].Effect == SPELL_EFFECT_SUMMON_PET)
            {
                uint32 creature_id = spellEntry->Effects[k].MiscValue;
                CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(creature_id);
                if (!cInfo)
                    continue;

                // already loaded
                if (cInfo->PetSpellDataId)
                    continue;

                // for creature without PetSpellDataId get default pet spells from creature_template
                int32 petSpellsId = cInfo->Entry;
                if (mPetDefaultSpellsMap.find(cInfo->Entry) != mPetDefaultSpellsMap.end())
                    continue;

                PetDefaultSpellsEntry petDefSpells;
                for (uint8 j = 0; j < MAX_CREATURE_SPELL_DATA_SLOT; ++j)
                    petDefSpells.spellid[j] = cInfo->spells[j];

                if (LoadPetDefaultSpells_helper(cInfo, petDefSpells))
                {
                    mPetDefaultSpellsMap[petSpellsId] = petDefSpells;
                    ++countCreature;
                }
            }
        }
    }

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u summonable creature templates in %u ms", countCreature, GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellAreas()
{
    uint32 oldMSTime = getMSTime();

    mSpellAreaMap.clear();                                  // need for reload case
    mSpellAreaForQuestMap.clear();
    mSpellAreaForQuestEndMap.clear();
    mSpellAreaForAuraMap.clear();

    //                                                  0     1         2              3               4                 5          6          7       8         9
    QueryResult result = WorldDatabase.Query("SELECT spell, area, quest_start, quest_start_status, quest_end_status, quest_end, aura_spell, racemask, gender, autocast FROM spell_area");
    if (!result)
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 spell area requirements. DB table `spell_area` is empty.");

        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 spell = fields[0].GetUInt32();
        SpellArea spellArea;
        spellArea.spellId             = spell;
        spellArea.areaId              = fields[1].GetUInt32();
        spellArea.questStart          = fields[2].GetUInt32();
        spellArea.questStartStatus    = fields[3].GetUInt32();
        spellArea.questEndStatus      = fields[4].GetUInt32();
        spellArea.questEnd            = fields[5].GetUInt32();
        spellArea.auraSpell           = fields[6].GetInt32();
        spellArea.raceMask            = fields[7].GetUInt32();
        spellArea.gender              = Gender(fields[8].GetUInt8());
        spellArea.autocast            = fields[9].GetBool();

        if (SpellInfo const* spellInfo = GetSpellInfo(spell))
        {
            if (spellArea.autocast)
                const_cast<SpellInfo*>(spellInfo)->Attributes |= SPELL_ATTR0_CANT_CANCEL;
        }
        else
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` does not exist", spell);
            continue;
        }

        {
            bool ok = true;
            SpellAreaMapBounds sa_bounds = GetSpellAreaMapBounds(spellArea.spellId);
            for (SpellAreaMap::const_iterator itr = sa_bounds.first; itr != sa_bounds.second; ++itr)
            {
                if (spellArea.spellId != itr->second.spellId)
                    continue;
                if (spellArea.areaId != itr->second.areaId)
                    continue;
                if (spellArea.questStart != itr->second.questStart)
                    continue;
                if (spellArea.auraSpell != itr->second.auraSpell)
                    continue;
                if ((spellArea.raceMask & itr->second.raceMask) == 0)
                    continue;
                if (spellArea.gender != itr->second.gender)
                    continue;

                // duplicate by requirements
                ok = false;
                break;
            }

            if (!ok)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` already listed with similar requirements.", spell);
                continue;
            }
        }

        if (spellArea.areaId && !GetAreaEntryByAreaID(spellArea.areaId))
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have wrong area (%u) requirement", spell, spellArea.areaId);
            continue;
        }

        if (spellArea.questStart && !sObjectMgr->GetQuestTemplate(spellArea.questStart))
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have wrong start quest (%u) requirement", spell, spellArea.questStart);
            continue;
        }

        if (spellArea.questEnd)
        {
            if (!sObjectMgr->GetQuestTemplate(spellArea.questEnd))
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have wrong end quest (%u) requirement", spell, spellArea.questEnd);
                continue;
            }
        }

        if (spellArea.auraSpell)
        {
            SpellInfo const* spellInfo = GetSpellInfo(abs(spellArea.auraSpell));
            if (!spellInfo)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have wrong aura spell (%u) requirement", spell, abs(spellArea.auraSpell));
                continue;
            }

            if (uint32(abs(spellArea.auraSpell)) == spellArea.spellId)
            {
                sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have aura spell (%u) requirement for itself", spell, abs(spellArea.auraSpell));
                continue;
            }

            // not allow autocast chains by auraSpell field (but allow use as alternative if not present)
            if (spellArea.autocast && spellArea.auraSpell > 0)
            {
                bool chain = false;
                SpellAreaForAuraMapBounds saBound = GetSpellAreaForAuraMapBounds(spellArea.spellId);
                for (SpellAreaForAuraMap::const_iterator itr = saBound.first; itr != saBound.second; ++itr)
                {
                    if (itr->second->autocast && itr->second->auraSpell > 0)
                    {
                        chain = true;
                        break;
                    }
                }

                if (chain)
                {
                    sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have aura spell (%u) requirement that itself autocast from aura", spell, spellArea.auraSpell);
                    continue;
                }

                SpellAreaMapBounds saBound2 = GetSpellAreaMapBounds(spellArea.auraSpell);
                for (SpellAreaMap::const_iterator itr2 = saBound2.first; itr2 != saBound2.second; ++itr2)
                {
                    if (itr2->second.autocast && itr2->second.auraSpell > 0)
                    {
                        chain = true;
                        break;
                    }
                }

                if (chain)
                {
                    sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have aura spell (%u) requirement that itself autocast from aura", spell, spellArea.auraSpell);
                    continue;
                }
            }
        }

        if (spellArea.raceMask && (spellArea.raceMask & RACEMASK_ALL_PLAYABLE) == 0)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have wrong race mask (%u) requirement", spell, spellArea.raceMask);
            continue;
        }

        if (spellArea.gender != GENDER_NONE && spellArea.gender != GENDER_FEMALE && spellArea.gender != GENDER_MALE)
        {
            sLog->outError(LOG_FILTER_SQL, "Spell %u listed in `spell_area` have wrong gender (%u) requirement", spell, spellArea.gender);
            continue;
        }

        SpellArea const* sa = &mSpellAreaMap.insert(SpellAreaMap::value_type(spell, spellArea))->second;

        // for search by current zone/subzone at zone/subzone change
        if (spellArea.areaId)
            mSpellAreaForAreaMap.insert(SpellAreaForAreaMap::value_type(spellArea.areaId, sa));

        // for search at quest start/reward
        if (spellArea.questStart)
            mSpellAreaForQuestMap.insert(SpellAreaForQuestMap::value_type(spellArea.questStart, sa));

        // for search at quest start/reward
        if (spellArea.questEnd)
            mSpellAreaForQuestEndMap.insert(SpellAreaForQuestMap::value_type(spellArea.questEnd, sa));

        // for search at aura apply
        if (spellArea.auraSpell)
            mSpellAreaForAuraMap.insert(SpellAreaForAuraMap::value_type(abs(spellArea.auraSpell), sa));

        ++count;
    } while (result->NextRow());

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spell area requirements in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// Temporary structure to hold spell effect entries for faster loading
struct SpellEffectArray
{
    SpellEffectArray()
    {
        effects[0] = NULL;
        effects[1] = NULL;
        effects[2] = NULL;
    }

    SpellEffectEntry const* effects[MAX_SPELL_EFFECTS];
};

void SpellMgr::LoadSpellInfoStore()
{
    uint32 oldMSTime = getMSTime();

    UnloadSpellInfoStore();
    mSpellInfoMap.resize(sSpellStore.GetNumRows(), NULL);

    std::map<uint32, SpellEffectArray> effectsBySpell;

    for (uint32 i = 0; i < sSpellEffectStore.GetNumRows(); ++i)
    {
        SpellEffectEntry const* effect = sSpellEffectStore.LookupEntry(i);
        if (!effect)
            continue;

        effectsBySpell[effect->EffectSpellId].effects[effect->EffectIndex] = effect;
    }

    for (uint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
        if (SpellEntry const* spellEntry = sSpellStore.LookupEntry(i))
            mSpellInfoMap[i] = new SpellInfo(spellEntry, effectsBySpell[i].effects);

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded spell info store in %u ms", GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::UnloadSpellInfoStore()
{
    for (uint32 i = 0; i < mSpellInfoMap.size(); ++i)
    {
        if (mSpellInfoMap[i])
            delete mSpellInfoMap[i];
    }
    mSpellInfoMap.clear();
}

void SpellMgr::UnloadSpellInfoImplicitTargetConditionLists()
{
    for (uint32 i = 0; i < mSpellInfoMap.size(); ++i)
    {
        if (mSpellInfoMap[i])
            mSpellInfoMap[i]->_UnloadImplicitTargetConditionLists();
    }
}

void SpellMgr::LoadSpellCustomAttr()
{
    uint32 oldMSTime = getMSTime();

    SpellInfo* spellInfo = NULL;
    for (uint32 i = 0; i < GetSpellInfoStoreSize(); ++i)
    {
        spellInfo = mSpellInfoMap[i];
        if (!spellInfo)
            continue;

        for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
        {
            switch (spellInfo->Effects[j].ApplyAuraName)
            {
                case SPELL_AURA_MOD_POSSESS:
                case SPELL_AURA_MOD_CONFUSE:
                case SPELL_AURA_MOD_CHARM:
                case SPELL_AURA_AOE_CHARM:
                case SPELL_AURA_MOD_FEAR:
                case SPELL_AURA_MOD_STUN:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_AURA_CC;
                case SPELL_AURA_MOD_DECREASE_SPEED:
                case SPELL_AURA_MOD_SPEED_SLOW_ALL:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_BINARY;
                    break;
                case SPELL_AURA_PERIODIC_MANA_LEECH:
                case SPELL_AURA_POWER_BURN:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_NO_INITIAL_THREAT;
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_BINARY;
                    break;
                case SPELL_AURA_PERIODIC_HEAL:
                case SPELL_AURA_PERIODIC_DAMAGE:
                case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
                case SPELL_AURA_PERIODIC_LEECH:
                case SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
                case SPELL_AURA_PERIODIC_ENERGIZE:
                case SPELL_AURA_OBS_MOD_HEALTH:
                case SPELL_AURA_OBS_MOD_POWER:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_NO_INITIAL_THREAT;
                    break;
            }

            switch (spellInfo->Effects[j].Effect)
            {
                case SPELL_EFFECT_DISPEL:
                case SPELL_EFFECT_DISPEL_MECHANIC:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_BINARY;
                    break;
                case SPELL_EFFECT_POWER_DRAIN:
                case SPELL_EFFECT_POWER_BURN:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_NO_INITIAL_THREAT;
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_BINARY;
                    break;
                case SPELL_EFFECT_SCHOOL_DAMAGE:
                case SPELL_EFFECT_WEAPON_DAMAGE:
                case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
                case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
                case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
                case SPELL_EFFECT_HEAL:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_DIRECT_DAMAGE;
                    break;
                case SPELL_EFFECT_HEAL_MAX_HEALTH:
                case SPELL_EFFECT_HEALTH_LEECH:
                case SPELL_EFFECT_HEAL_PCT:
                case SPELL_EFFECT_ENERGIZE_PCT:
                case SPELL_EFFECT_ENERGIZE:
                case SPELL_EFFECT_HEAL_MECHANICAL:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_NO_INITIAL_THREAT;
                    break;
                case SPELL_EFFECT_CHARGE:
                case SPELL_EFFECT_CHARGE_DEST:
                case SPELL_EFFECT_JUMP:
                case SPELL_EFFECT_JUMP_DEST:
                case SPELL_EFFECT_LEAP_BACK:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_CHARGE;
                    break;
                case SPELL_EFFECT_PICKPOCKET:
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_PICKPOCKET;
                    break;
                case SPELL_EFFECT_ENCHANT_ITEM:
                case SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY:
                case SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC:
                case SPELL_EFFECT_ENCHANT_HELD_ITEM:
                {
                    // only enchanting profession enchantments procs can stack
                    if (IsPartOfSkillLine(SKILL_ENCHANTING, i))
                    {
                        uint32 enchantId = spellInfo->Effects[j].MiscValue;
                        SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(enchantId);
                        for (uint8 s = 0; s < MAX_ITEM_ENCHANTMENT_EFFECTS; ++s)
                        {
                            if (enchant->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                                continue;

                            SpellInfo* procInfo = (SpellInfo*)GetSpellInfo(enchant->spellid[s]);
                            if (!procInfo)
                                continue;

                            // if proced directly from enchantment, not via proc aura
                            // NOTE: Enchant Weapon - Blade Ward also has proc aura spell and is proced directly
                            // however its not expected to stack so this check is good
                            if (procInfo->HasAura(SPELL_AURA_PROC_TRIGGER_SPELL))
                                continue;

                            procInfo->AttributesCu |= SPELL_ATTR0_CU_ENCHANT_PROC;
                        }
                    }
                    break;
                }
            }
        }

        if (!spellInfo->_IsPositiveEffect(EFFECT_0, false))
            spellInfo->AttributesCu |= SPELL_ATTR0_CU_NEGATIVE_EFF0;

        if (!spellInfo->_IsPositiveEffect(EFFECT_1, false))
            spellInfo->AttributesCu |= SPELL_ATTR0_CU_NEGATIVE_EFF1;

        if (!spellInfo->_IsPositiveEffect(EFFECT_2, false))
            spellInfo->AttributesCu |= SPELL_ATTR0_CU_NEGATIVE_EFF2;

        if (spellInfo->SpellVisual[0] == 3879)
            spellInfo->AttributesCu |= SPELL_ATTR0_CU_CONE_BACK;

        switch (spellInfo->Id)
        {
            case 60256:
                //Crashes client on pressing ESC (Maybe because of ReqSpellFocus and GameObject)
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                break;
            case 96942:  // Gaze of Occu'thar
            case 101009: // Gaze of Occu'thar
                spellInfo->AttributesEx &= ~SPELL_ATTR1_CHANNELED_1;
                break;
            case 1776: // Gouge
            case 1777:
            case 8629:
            case 11285:
            case 11286:
            case 12540:
            case 13579:
            case 24698:
            case 28456:
            case 29425:
            case 34940:
            case 36862:
            case 38764:
            case 38863:
            case 52743: // Head Smack
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_REQ_TARGET_FACING_CASTER;
                break;
            case 53: // Backstab
            case 2589:
            case 2590:
            case 2591:
            case 8721:
            case 11279:
            case 11280:
            case 11281:
            case 25300:
            case 26863:
            case 48656:
            case 48657:
            case 703: // Garrote
            case 8631:
            case 8632:
            case 8633:
            case 11289:
            case 11290:
            case 26839:
            case 26884:
            case 48675:
            case 48676:
            case 5221: // Shred
            case 6800:
            case 8992:
            case 9829:
            case 9830:
            case 27001:
            case 27002:
            case 48571:
            case 48572:
            case 8676: // Ambush
            case 8724:
            case 8725:
            case 11267:
            case 11268:
            case 11269:
            case 27441:
            case 48689:
            case 48690:
            case 48691:
            case 6785: // Ravage
            case 6787:
            case 9866:
            case 9867:
            case 27005:
            case 48578:
            case 48579:
            case 21987: // Lash of Pain
            case 23959: // Test Stab R50
            case 24825: // Test Backstab
            case 58563: // Assassinate Restless Lookout
            case 81371: // Chloroform
            case 81372: // Chloroform
            case 82579: // Chloroform
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_REQ_CASTER_BEHIND_TARGET;
                break;
            case 26029: // Dark Glare
            case 37433: // Spout
            case 43140: // Flame Breath
            case 43215: // Flame Breath
            case 70461: // Coldflame Trap
            case 72133: // Pain and Suffering
            case 73788: // Pain and Suffering
            case 73789: // Pain and Suffering
            case 73790: // Pain and Suffering
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_CONE_LINE;
                break;
            case 24340: // Meteor
            case 26558: // Meteor
            case 28884: // Meteor
            case 36837: // Meteor
            case 38903: // Meteor
            case 41276: // Meteor
            case 57467: // Meteor
            case 26789: // Shard of the Fallen Star
            case 31436: // Malevolent Cleave
            case 35181: // Dive Bomb
            case 40810: // Saber Lash
            case 43267: // Saber Lash
            case 43268: // Saber Lash
            case 42384: // Brutal Swipe
            case 45150: // Meteor Slash
            case 64688: // Sonic Screech
            case 72373: // Shared Suffering
            case 71904: // Chaos Bane
            case 70492: // Ooze Eruption
            case 72505: // Ooze Eruption
            case 72624: // Ooze Eruption
            case 72625: // Ooze Eruption
            case 86014: // Thwilight Meteorite
            case 92863:
            case 92864:
            case 92865:
                // ONLY SPELLS WITH SPELLFAMILY_GENERIC and EFFECT_SCHOOL_DAMAGE
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_SHARE_DAMAGE;
                break;
            case 18500: // Wing Buffet
            case 33086: // Wild Bite
            case 49749: // Piercing Blow
            case 52890: // Penetrating Strike
            case 53454: // Impale
            case 59446: // Impale
            case 62383: // Shatter
            case 64777: // Machine Gun
            case 65239: // Machine Gun
            case 65919: // Impale
            case 67858: // Impale
            case 67859: // Impale
            case 67860: // Impale
            case 69293: // Wing Buffet
            case 74439: // Machine Gun
            case 63278: // Mark of the Faceless (General Vezax)
            case 62544: // Thrust (Argent Tournament)
            case 64588: // Thrust (Argent Tournament)
            case 66479: // Thrust (Argent Tournament)
            case 68505: // Thrust (Argent Tournament)
            case 62709: // Counterattack! (Argent Tournament)
            case 62626: // Break-Shield (Argent Tournament, Player)
            case 64590: // Break-Shield (Argent Tournament, Player)
            case 64342: // Break-Shield (Argent Tournament, NPC)
            case 64686: // Break-Shield (Argent Tournament, NPC)
            case 65147: // Break-Shield (Argent Tournament, NPC)
            case 68504: // Break-Shield (Argent Tournament, NPC)
            case 62874: // Charge (Argent Tournament, Player)
            case 68498: // Charge (Argent Tournament, Player)
            case 64591: // Charge (Argent Tournament, Player)
            case 63003: // Charge (Argent Tournament, NPC)
            case 63010: // Charge (Argent Tournament, NPC)
            case 68321: // Charge (Argent Tournament, NPC)
            case 72255: // Mark of the Fallen Champion (Deathbringer Saurfang)
            case 72444: // Mark of the Fallen Champion (Deathbringer Saurfang)
            case 72445: // Mark of the Fallen Champion (Deathbringer Saurfang)
            case 72446: // Mark of the Fallen Champion (Deathbringer Saurfang)
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_IGNORE_ARMOR;
                break;
            case 64422: // Sonic Screech (Auriaya)
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_SHARE_DAMAGE;
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_IGNORE_ARMOR;
                break;
            case 72293: // Mark of the Fallen Champion (Deathbringer Saurfang)
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_NEGATIVE_EFF0;
                break;
            default:
                break;
        }

        switch (spellInfo->SpellFamilyName)
        {
            case SPELLFAMILY_WARRIOR:
                // Shout
                if (spellInfo->SpellFamilyFlags[0] & 0x20000 || spellInfo->SpellFamilyFlags[1] & 0x20)
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_AURA_CC;
                break;
            case SPELLFAMILY_DRUID:
                // Roar
                if (spellInfo->SpellFamilyFlags[0] & 0x8)
                    spellInfo->AttributesCu |= SPELL_ATTR0_CU_AURA_CC;
                break;
            case SPELLFAMILY_WARLOCK:
                // Nether Ward
                if (spellInfo->Id == 687 || spellInfo->Id == 28176)
                    spellInfo->Effects[2].BasePoints = 6229;
                break;
            default:
                break;
        }
    }

    CreatureAI::FillAISpellInfo();

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded spell custom attributes in %u ms", GetMSTimeDiffToNow(oldMSTime));
}

void SpellMgr::LoadSpellInfoCorrections()
{
    uint32 oldMSTime = getMSTime();

    SpellInfo* spellInfo = NULL;
    for (uint32 i = 0; i < mSpellInfoMap.size(); ++i)
    {
        spellInfo = (SpellInfo*)mSpellInfoMap[i];
        if (!spellInfo)
            continue;

        for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
        {
            switch (spellInfo->Effects[j].Effect)
            {
                case SPELL_EFFECT_CHARGE:
                case SPELL_EFFECT_CHARGE_DEST:
                case SPELL_EFFECT_JUMP:
                case SPELL_EFFECT_JUMP_DEST:
                case SPELL_EFFECT_LEAP_BACK:
                    if (!spellInfo->Speed && !spellInfo->SpellFamilyName)
                        spellInfo->Speed = SPEED_CHARGE;
                    break;
            }
        }

        if (spellInfo->ActiveIconID == 2158)  // flight
            spellInfo->Attributes |= SPELL_ATTR0_PASSIVE;

        switch (spellInfo->Id)
        {
            case 53096: // Quetz'lun's Judgment
            case 68591: // Burning Brock
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 42730:
                spellInfo->Effects[EFFECT_1].TriggerSpell = 42739;
                break;
            case 59735:
                spellInfo->Effects[EFFECT_1].TriggerSpell = 59736;
                break;
            case 52611: // Summon Skeletons
            case 52612: // Summon Skeletons
                spellInfo->Effects[EFFECT_0].MiscValueB = 64;
                break;
            case 40244: // Simon Game Visual
            case 40245: // Simon Game Visual
            case 40246: // Simon Game Visual
            case 40247: // Simon Game Visual
            case 42835: // Spout, remove damage effect, only anim is needed
                spellInfo->Effects[EFFECT_0].Effect = 0;
                break;
            case 30657: // Quake
                spellInfo->Effects[EFFECT_0].TriggerSpell = 30571;
                break;
            case 63665: // Charge (Argent Tournament emote on riders)
            case 31298: // Sleep (needs target selection script)
            case 51904: // Summon Ghouls On Scarlet Crusade (this should use conditions table, script for this spell needs to be fixed)
            case 2895:  // Wrath of Air Totem rank 1 (Aura)
            case 68933: // Wrath of Air Totem rank 2 (Aura)
            case 29200: // Purify Helboar Meat
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_CASTER);
                break;
            case 31344: // Howl of Azgalor
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_100_YARDS); // 100yards instead of 50000?!
                break;
            case 42818: // Headless Horseman - Wisp Flight Port
            case 42821: // Headless Horseman - Wisp Flight Missile
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(6); // 100 yards
                break;
            case 36350: //They Must Burn Bomb Aura (self)
                spellInfo->Effects[EFFECT_0].TriggerSpell = 36325; // They Must Burn Bomb Drop (DND)
                break;
            case 49838: // Stop Time
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_INITIAL_AGGRO;
                break;
            case 61407: // Energize Cores
            case 62136: // Energize Cores
            case 54069: // Energize Cores
            case 56251: // Energize Cores
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_SRC_AREA_ENTRY);
                break;
            case 50785: // Energize Cores
            case 59372: // Energize Cores
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_SRC_AREA_ENEMY);
                break;
            case 8494: // Mana Shield (rank 2)
                // because of bug in dbc
                spellInfo->ProcChance = 0;
                break;
            case 20335: // Heart of the Crusader
            case 20336:
            case 20337:
            case 63320: // Glyph of Life Tap
                // Entries were not updated after spell effect change, we have to do that manually :/
                spellInfo->AttributesEx3 |= SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED;
                break;
            case 59725: // Improved Spell Reflection - aoe aura
                // Target entry seems to be wrong for this spell :/
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_CASTER_AREA_PARTY);
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_10_YARDS_2);
                break;
            case 44978: // Wild Magic
            case 45001:
            case 45002:
            case 45004:
            case 45006:
            case 45010:
            case 31347: // Doom
            case 41635: // Prayer of Mending
            case 44869: // Spectral Blast
            case 45027: // Revitalize
            case 45976: // Muru Portal Channel
            case 39365: // Thundering Storm
            case 41071: // Raise Dead (HACK)
            case 52124: // Sky Darkener Assault
            case 42442: // Vengeance Landing Cannonfire
            case 45863: // Cosmetic - Incinerate to Random Target
            case 25425: // Shoot
            case 45761: // Shoot
            case 42611: // Shoot
            case 61588: // Blazing Harpoon
            case 52479: // Gift of the Harvester
            case 48246: // Ball of Flame
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 36384: // Skartax Purple Beam
                spellInfo->MaxAffectedTargets = 2;
                break;
            case 41376: // Spite
            case 39992: // Needle Spine
            case 29576: // Multi-Shot
            case 40816: // Saber Lash
            case 37790: // Spread Shot
            case 46771: // Flame Sear
            case 45248: // Shadow Blades
            case 41303: // Soul Drain
            case 54172: // Divine Storm (heal)
            case 29213: // Curse of the Plaguebringer - Noth
            case 28542: // Life Drain - Sapphiron
            case 66588: // Flaming Spear
            case 54171: // Divine Storm
            case 44461: // Living Bomb (Damage)
                spellInfo->MaxAffectedTargets = 3;
                break;
            case 38310: // Multi-Shot
                spellInfo->MaxAffectedTargets = 4;
                break;
            case 53385: // Divine Storm (Damage)
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                break;
            case 42005: // Bloodboil
            case 38296: // Spitfire Totem
            case 37676: // Insidious Whisper
            case 46008: // Negative Energy
            case 45641: // Fire Bloom
            case 55665: // Life Drain - Sapphiron (H)
            case 28796: // Poison Bolt Volly - Faerlina
                spellInfo->MaxAffectedTargets = 5;
                break;
            case 40827: // Sinful Beam
            case 40859: // Sinister Beam
            case 40860: // Vile Beam
            case 40861: // Wicked Beam
            case 54835: // Curse of the Plaguebringer - Noth (H)
            case 54098: // Poison Bolt Volly - Faerlina (H)
                spellInfo->MaxAffectedTargets = 10;
                break;
            case 50312: // Unholy Frenzy
                spellInfo->MaxAffectedTargets = 15;
                break;
            case 33711: // Murmur's Touch
            case 38794:
                spellInfo->MaxAffectedTargets = 1;
                spellInfo->Effects[EFFECT_0].TriggerSpell = 33760;
                break;
            case 17941: // Shadow Trance
            case 22008: // Netherwind Focus
            case 31834: // Light's Grace
            case 34754: // Clearcasting
            case 34936: // Backlash
            case 48108: // Hot Streak
            case 51124: // Killing Machine
            case 54741: // Firestarter
            case 57761: // Fireball!
            case 39805: // Lightning Overload
            case 64823: // Item - Druid T8 Balance 4P Bonus
            case 34477: // Misdirection
            case 44401: // Missile Barrage
                spellInfo->ProcCharges = 1;
                break;
            case 8188:  // Magma Totem
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_INITIAL_AGGRO;
                break;
            case 44544: // Fingers of Frost
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(685904631, 1151048, 0);
                break;
            case 74396: // Fingers of Frost visual buff
                spellInfo->ProcCharges = 2;
                spellInfo->StackAmount = 0;
                break;
            case 28200: // Ascendance (Talisman of Ascendance trinket)
                spellInfo->ProcCharges = 6;
                break;
            case 54785: // Demon Leap
                spellInfo->Effects[EFFECT_0].MiscValue = 75;
                spellInfo->Effects[EFFECT_0].MiscValueB = 15;
                break;
            case 47201: // Everlasting Affliction
            case 47202:
            case 47203:
            case 47204:
            case 47205:
                // add corruption to affected spells
                spellInfo->Effects[1].SpellClassMask[0] |= 2;
                break;
            case 51852: // The Eye of Acherus (no spawn in phase 2 in db)
                spellInfo->Effects[0].MiscValue |= 1;
                break;
            case 51912: // Crafty's Ultra-Advanced Proto-Typical Shortening Blaster
                spellInfo->Effects[0].Amplitude = 3000;
                break;
            case 29809: // Desecration Arm - 36 instead of 37 - typo? :/
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_7_YARDS);
                break;
            // Master Shapeshifter: missing stance data for forms other than bear - bear version has correct data
            // To prevent aura staying on target after talent unlearned
            case 48420:
                spellInfo->Stances = 1 << (FORM_CAT - 1);
                break;
            case 48421:
                spellInfo->Stances = 1 << (FORM_MOONKIN - 1);
                break;
            case 48422:
                spellInfo->Stances = 1 << (FORM_TREE - 1);
                break;
            case 51466: // Elemental Oath (Rank 1)
            case 51470: // Elemental Oath (Rank 2)
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_ADD_FLAT_MODIFIER;
                spellInfo->Effects[EFFECT_1].MiscValue = SPELLMOD_EFFECT2;
                spellInfo->Effects[EFFECT_1].SpellClassMask = flag96(0x00000000, 0x00004000, 0x00000000);
                break;
            case 47569: // Improved Shadowform (Rank 1)
                // with this spell atrribute aura can be stacked several times
                spellInfo->Attributes &= ~SPELL_ATTR0_NOT_SHAPESHIFT;
                break;
            case 64904: // Hymn of Hope
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT;
                spellInfo->AttributesEx3 |= SPELL_ATTR3_STACK_FOR_DIFF_CASTERS;
                break;
            case 30421: // Nether Portal - Perseverence
                spellInfo->Effects[2].BasePoints += 30000;
                break;
            case 30294: // Soul Leech
                spellInfo->Effects[0].BasePoints = 2;
                spellInfo->Effects[1].BasePoints = 2;
                break;
            case 41913: // Parasitic Shadowfiend Passive
                spellInfo->Effects[0].ApplyAuraName = SPELL_AURA_DUMMY; // proc debuff, and summon infinite fiends
                break;
            case 27892: // To Anchor 1
            case 27928: // To Anchor 1
            case 27935: // To Anchor 1
            case 27915: // Anchor to Skulls
            case 27931: // Anchor to Skulls
            case 27937: // Anchor to Skulls
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(13);
                break;
            // target allys instead of enemies, target A is src_caster, spells with effect like that have ally target
            // this is the only known exception, probably just wrong data
            case 29214: // Wrath of the Plaguebringer
            case 54836: // Wrath of the Plaguebringer
                spellInfo->Effects[EFFECT_0].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_SRC_AREA_ALLY);
                spellInfo->Effects[EFFECT_1].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_SRC_AREA_ALLY);
                break;
            case 63675: // Improved Devouring Plague
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_DONE_BONUS;
                break;
            case 8145: // Tremor Totem (instant pulse)
            case 6474: // Earthbind Totem (instant pulse)
                spellInfo->AttributesEx5 |= SPELL_ATTR5_START_PERIODIC_AT_APPLY;
                break;
            case 8143:  // Tremor Totem (Instant)
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_NONE;
                break;
            case 53241: // Marked for Death (Rank 1)
            case 53243: // Marked for Death (Rank 2)
            case 53244: // Marked for Death (Rank 3)
            case 53245: // Marked for Death (Rank 4)
            case 53246: // Marked for Death (Rank 5)
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(0x00067801, 0x10820001, 0x00000801);
                break;
            case 50365: // Improved Blood Presence
            case 50371:
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE;
                break;
            case 7328:  // Redemption
                spellInfo->AttributesEx5 |= SPELL_ATTR5_HASTE_AFFECT_DURATION;
                spellInfo->SpellFamilyName = SPELLFAMILY_PALADIN;
                break;
            case 5176:  // Wrath
            case 2912:  // Starfire
            case 78674: // Starsurge
                spellInfo->Effects[1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[1].TargetA = TARGET_UNIT_CASTER;
                break;
            case 70728: // Exploit Weakness (needs target selection script)
            case 70840: // Devious Minds (needs target selection script)
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_CASTER);
                spellInfo->Effects[EFFECT_0].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_PET);
                break;
            case 70893: // Culling The Herd (needs target selection script)
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_CASTER);
                spellInfo->Effects[EFFECT_0].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_MASTER);
                break;
            case 54800: // Sigil of the Frozen Conscience - change class mask to custom extended flags of Icy Touch
                        // this is done because another spell also uses the same SpellFamilyFlags as Icy Touch
                        // SpellFamilyFlags[0] & 0x00000040 in SPELLFAMILY_DEATHKNIGHT is currently unused (3.3.5a)
                        // this needs research on modifier applying rules, does not seem to be in Attributes fields
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(0x00000040, 0x00000000, 0x00000000);
                break;
            case 64949: // Idol of the Flourishing Life
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(0x00000000, 0x02000000, 0x00000000);
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_ADD_FLAT_MODIFIER;
                break;
            case 34231: // Libram of the Lightbringer
            case 60792: // Libram of Tolerance
            case 64956: // Libram of the Resolute
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(0x80000000, 0x00000000, 0x00000000);
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_ADD_FLAT_MODIFIER;
                break;
            case 28851: // Libram of Light
            case 28853: // Libram of Divinity
            case 32403: // Blessed Book of Nagrand
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(0x40000000, 0x00000000, 0x00000000);
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_ADD_FLAT_MODIFIER;
                break;
            case 45602: // Ride Carpet
                spellInfo->Effects[EFFECT_0].BasePoints = 0; // force seat 0, vehicle doesn't have the required seat flags for "no seat specified (-1)"
                break;
            case 64745: // Item - Death Knight T8 Tank 4P Bonus
            case 64936: // Item - Warrior T8 Protection 4P Bonus
                spellInfo->Effects[0].BasePoints = 100; // 100% chance of procc'ing, not -10% (chance calculated in PrepareTriggersExecutedOnHit)
                break;
            case 59414: // Pulsing Shockwave Aura (Loken)
                // this flag breaks movement, remove it
                spellInfo->AttributesEx &= ~SPELL_ATTR1_CHANNELED_1;
                break;
            case 61719: // Easter Lay Noblegarden Egg Aura - Interrupt flags copied from aura which this aura is linked with
                spellInfo->AuraInterruptFlags = AURA_INTERRUPT_FLAG_HITBYSPELL | AURA_INTERRUPT_FLAG_TAKE_DAMAGE;
                break;
            case 70650: // Death Knight T10 Tank 2P Bonus
                spellInfo->Effects[0].ApplyAuraName = SPELL_AURA_ADD_PCT_MODIFIER;
                break;
            case 71838: // Drain Life - Bryntroll Normal
            case 71839: // Drain Life - Bryntroll Heroic
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CANT_CRIT;
                break;
            case 34471: // The Beast Within
                spellInfo->AttributesEx5 |= SPELL_ATTR5_USABLE_WHILE_CONFUSED | SPELL_ATTR5_USABLE_WHILE_FEARED | SPELL_ATTR5_USABLE_WHILE_STUNNED;
                break;
            case 81751: // Atonement
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                break;
            case 26022: // Pursuit of Justice
            case 26023:
                spellInfo->SpellFamilyName = SPELLFAMILY_PALADIN;
                break;
            case 12289: // Improved Hamstring
            case 12668:
                spellInfo->Effects[EFFECT_0].TriggerSpell = 0;
                break;
            // NAXXRAMAS SPELLS
            //
            case 29125: // Hopeless (Razuvious)
                spellInfo->MaxAffectedTargets = 4;
                break;
            case 28111: // Chain 
            case 28096:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS);
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            // ENDOF NAXXRAMAS SPELLS
            // ULDUAR SPELLS
            //
            case 62374: // Pursued (Flame Leviathan)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS);   // 50000yd
                break;
            case 63342: // Focused Eyebeam Summon Trigger (Kologarn)
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 62716: // Growth of Nature (Freya)
            case 65584: // Growth of Nature (Freya)
            case 64381: // Strength of the Pack (Auriaya)
                spellInfo->AttributesEx3 |= SPELL_ATTR3_STACK_FOR_DIFF_CASTERS;
                break;
            case 63018: // Searing Light (XT-002)
            case 65121: // Searing Light (25m) (XT-002)
            case 63024: // Gravity Bomb (XT-002)
            case 64234: // Gravity Bomb (25m) (XT-002)
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 62834: // Boom (XT-002)
            // This hack is here because we suspect our implementation of spell effect execution on targets
            // is done in the wrong order. We suspect that EFFECT_0 needs to be applied on all targets,
            // then EFFECT_1, etc - instead of applying each effect on target1, then target2, etc.
            // The above situation causes the visual for this spell to be bugged, so we remove the instakill
            // effect and implement a script hack for that.
                spellInfo->Effects[EFFECT_1].Effect = 0;
                break;
            case 64386: // Terrifying Screech (Auriaya)
            case 64389: // Sentinel Blast (Auriaya)
            case 64678: // Sentinel Blast (Auriaya)
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(28); // 5 seconds, wrong DBC data?
                break;
            case 64321: // Potent Pheromones (Freya)
                // spell should dispel area aura, but doesn't have the attribute
                // may be db data bug, or blizz may keep reapplying area auras every update with checking immunity
                // that will be clear if we get more spells with problem like this
                spellInfo->AttributesEx |= SPELL_ATTR1_DISPEL_AURAS_ON_IMMUNITY;
                break;
            case 62301: // Cosmic Smash (Algalon the Observer)
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 64598: // Cosmic Smash (Algalon the Observer)
                spellInfo->MaxAffectedTargets = 3;
                break;
            case 62293: // Cosmic Smash (Algalon the Observer)
                spellInfo->Effects[EFFECT_0].TargetB = SpellImplicitTargetInfo(TARGET_DEST_CASTER);
                break;
            case 62311: // Cosmic Smash (Algalon the Observer)
            case 64596: // Cosmic Smash (Algalon the Observer)
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(6);  // 100yd
                break;
            case 64014: // Expedition Base Camp Teleport
            case 64024: // Conservatory Teleport
            case 64025: // Halls of Invention Teleport
            case 64028: // Colossal Forge Teleport
            case 64029: // Shattered Walkway Teleport
            case 64030: // Antechamber Teleport
            case 64031: // Scrapyard Teleport
            case 64032: // Formation Grounds Teleport
            case 65042: // Prison of Yogg-Saron Teleport
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_DEST_DB);
                break;
            // ENDOF ULDUAR SPELLS
            //
            // TRIAL OF THE CRUSADER SPELLS
            //
            case 66258: // Infernal Eruption (10N)
            case 67901: // Infernal Eruption (25N)
                // increase duration from 15 to 18 seconds because caster is already
                // unsummoned when spell missile hits the ground so nothing happen in result
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(85);
                break;
            // ENDOF TRIAL OF THE CRUSADER SPELLS
            //
            // ICECROWN CITADEL SPELLS
            //
            // THESE SPELLS ARE WORKING CORRECTLY EVEN WITHOUT THIS HACK
            // THE ONLY REASON ITS HERE IS THAT CURRENT GRID SYSTEM
            // DOES NOT ALLOW FAR OBJECT SELECTION (dist > 333)
            case 70781: // Light's Hammer Teleport
            case 70856: // Oratory of the Damned Teleport
            case 70857: // Rampart of Skulls Teleport
            case 70858: // Deathbringer's Rise Teleport
            case 70859: // Upper Spire Teleport
            case 70860: // Frozen Throne Teleport
            case 70861: // Sindragosa's Lair Teleport
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_DEST_DB);
                break;
            case 69055: // Saber Lash (Lord Marrowgar)
            case 70814: // Saber Lash (Lord Marrowgar)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_8_YARDS); // 8yd
                break;
            case 69075: // Bone Storm (Lord Marrowgar)
            case 70834: // Bone Storm (Lord Marrowgar)
            case 70835: // Bone Storm (Lord Marrowgar)
            case 70836: // Bone Storm (Lord Marrowgar)
            case 72864: // Death Plague (Rotting Frost Giant)
            case 71160: // Plague Stench (Stinky)
            case 71161: // Plague Stench (Stinky)
            case 71123: // Decimate (Stinky & Precious)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_100_YARDS); // 100yd
                break;
            case 71169: // Shadow's Fate
                spellInfo->AttributesEx3 |= SPELL_ATTR3_STACK_FOR_DIFF_CASTERS;
                break;
            case 72378: // Blood Nova (Deathbringer Saurfang)
            case 73058: // Blood Nova (Deathbringer Saurfang)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);
                break;
            case 72769: // Scent of Blood (Deathbringer Saurfang)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);
                // no break
            case 72771: // Scent of Blood (Deathbringer Saurfang)
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);
                break;
            case 72723: // Resistant Skin (Deathbringer Saurfang adds)
                // this spell initially granted Shadow damage immunity, however it was removed but the data was left in client
                spellInfo->Effects[EFFECT_2].Effect = 0;
                break;
            case 70460: // Coldflame Jets (Traps after Saurfang)
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(1); // 10 seconds
                break;
            case 71412: // Green Ooze Summon (Professor Putricide)
            case 71415: // Orange Ooze Summon (Professor Putricide)
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_UNIT_TARGET_ANY);
                break;
            case 71159: // Awaken Plagued Zombies
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(21);
                break;
            case 70530: // Volatile Ooze Beam Protection (Professor Putricide)
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_APPLY_AURA; // for an unknown reason this was SPELL_EFFECT_APPLY_AREA_AURA_RAID
                break;
            // THIS IS HERE BECAUSE COOLDOWN ON CREATURE PROCS IS NOT IMPLEMENTED
            case 71604: // Mutated Strength (Professor Putricide)
            case 72673: // Mutated Strength (Professor Putricide)
            case 72674: // Mutated Strength (Professor Putricide)
            case 72675: // Mutated Strength (Professor Putricide)
                spellInfo->Effects[EFFECT_1].Effect = 0;
                break;
            case 72454: // Mutated Plague (Professor Putricide)
            case 72464: // Mutated Plague (Professor Putricide)
            case 72506: // Mutated Plague (Professor Putricide)
            case 72507: // Mutated Plague (Professor Putricide)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                break;
            case 70911: // Unbound Plague (Professor Putricide) (needs target selection script)
            case 72854: // Unbound Plague (Professor Putricide) (needs target selection script)
            case 72855: // Unbound Plague (Professor Putricide) (needs target selection script)
            case 72856: // Unbound Plague (Professor Putricide) (needs target selection script)
                spellInfo->Effects[EFFECT_0].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_TARGET_ENEMY);
                break;
            case 71518: // Unholy Infusion Quest Credit (Professor Putricide)
            case 72934: // Blood Infusion Quest Credit (Blood-Queen Lana'thel)
            case 72289: // Frost Infusion Quest Credit (Sindragosa)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // another missing radius
                break;
            case 71708: // Empowered Flare (Blood Prince Council)
            case 72785: // Empowered Flare (Blood Prince Council)
            case 72786: // Empowered Flare (Blood Prince Council)
            case 72787: // Empowered Flare (Blood Prince Council)
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_DONE_BONUS;
                break;
            case 71266: // Swarming Shadows
            case 72890: // Swarming Shadows
                spellInfo->AreaGroupId = 0; // originally, these require area 4522, which is... outside of Icecrown Citadel
                break;
            case 70602: // Corruption
            case 48278: // Paralyze
                spellInfo->AttributesEx3 |= SPELL_ATTR3_STACK_FOR_DIFF_CASTERS;
                break;
            case 70715: // Column of Frost (visual marker)
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(32); // 6 seconds (missing)
                break;
            case 71085: // Mana Void (periodic aura)
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(9); // 30 seconds (missing)
                break;
            case 72015: // Frostbolt Volley (only heroic)
            case 72016: // Frostbolt Volley (only heroic)
                spellInfo->Effects[EFFECT_2].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_40_YARDS);
                break;
            case 72706: // Achievement Check (Valithria Dreamwalker)
            case 71357: // Order Whelp
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);   // 200yd
                break;
            case 70598: // Sindragosa's Fury
                spellInfo->Effects[EFFECT_0].TargetA = SpellImplicitTargetInfo(TARGET_DEST_DEST);
                break;
            case 69846: // Frost Bomb
                spellInfo->Speed = 0.0f;    // This spell's summon happens instantly
                break;
            case 71614: // Ice Lock
                spellInfo->Mechanic = MECHANIC_STUN;
                break;
            case 72762: // Defile
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(559); // 53 seconds
                break;
            case 72743: // Defile
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(22); // 45 seconds
                break;
            case 72754: // Defile
            case 73708: // Defile
            case 73709: // Defile
            case 73710: // Defile
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                break;
            case 69030: // Val'kyr Target Search
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                break;
            case 69198: // Raging Spirit Visual
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(13); // 50000yd
                break;
            case 73654: // Harvest Souls
            case 74295: // Harvest Souls
            case 74296: // Harvest Souls
            case 74297: // Harvest Souls
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                spellInfo->Effects[EFFECT_2].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                break;
            case 73655: // Harvest Soul
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_DONE_BONUS;
                break;
            case 73540: // Summon Shadow Trap
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(23); // 90 seconds
                break;
            case 73530: // Shadow Trap (visual)
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(28); // 5 seconds
                break;
            case 73529: // Shadow Trap
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_10_YARDS); // 10yd
                break;
            case 74282: // Shadow Trap (searcher)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_3_YARDS); // 3yd
                break;
            case 72595: // Restore Soul
            case 73650: // Restore Soul
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                break;
            case 74086: // Destroy Soul
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                break;
            case 74302: // Summon Spirit Bomb
            case 74342: // Summon Spirit Bomb
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 74341: // Summon Spirit Bomb
            case 74343: // Summon Spirit Bomb
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                spellInfo->MaxAffectedTargets = 3;
                break;
            case 73579: // Summon Spirit Bomb
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_25_YARDS); // 25yd
                break;
            case 72350: // Fury of Frostmourne
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                break;
            case 75127: // Kill Frostmourne Players
            case 72351: // Fury of Frostmourne
            case 72431: // Jump (removes Fury of Frostmourne debuff)
            case 72429: // Mass Resurrection
            case 73159: // Play Movie
            case 73582: // Trigger Vile Spirit (Inside, Heroic)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                break;
            case 72376: // Raise Dead
                spellInfo->MaxAffectedTargets = 3;
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS); // 50000yd
                break;
            case 71809: // Jump
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(3); // 20yd
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_25_YARDS); // 25yd
                break;
            case 72405: // Broken Frostmourne
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS); // 200yd
                break;
            // ENDOF ICECROWN CITADEL SPELLS
            //
            // RUBY SANCTUM SPELLS
            //
            case 74769: // Twilight Cutter
            case 77844: // Twilight Cutter
            case 77845: // Twilight Cutter
            case 77846: // Twilight Cutter
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_100_YARDS); // 100yd
                break;
            case 75509: // Twilight Mending
                spellInfo->AttributesEx6 |= SPELL_ATTR6_CAN_TARGET_INVISIBLE;
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            case 75888: // Awaken Flames
            case 75889: // Awaken Flames
                spellInfo->AttributesEx |= SPELL_ATTR1_CANT_TARGET_SELF;
                break;
            // ENDOF RUBY SANCTUM SPELLS
            //
            // EYE OF ETERNITY SPELLS
            // All spells below work even without these changes. The LOS attribute is due to problem
            // from collision between maps & gos with active destroyed state.
            case 57473: // Arcane Storm bonus explicit visual spell
            case 57431: // Summon Static Field
            case 56091: // Flame Spike (Wyrmrest Skytalon)
            case 56092: // Engulf in Flames (Wyrmrest Skytalon)
            case 57090: // Revivify (Wyrmrest Skytalon)
            case 57143: // Life Burst (Wyrmrest Skytalon)
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            // This would never crit on retail and it has attribute for SPELL_ATTR3_NO_DONE_BONUS because is handled from player,
            // until someone figures how to make scions not critting without hack and without making them main casters this should stay here.
            case 63934: // Arcane Barrage (casted by players and NONMELEEDAMAGELOG with caster Scion of Eternity (original caster)).
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CANT_CRIT;
                break;
            // ENDOF EYE OF ETERNITY SPELLS
            //
            // OCULUS SPELLS
            // The spells below are here because their effect 1 is giving warning due to
            // triggered spell not found in any dbc and is missing from encounter source* of data.
            // Even judged as clientside these spells can't be guessed for* now.
            case 49462: // Call Ruby Drake
            case 49461: // Call Amber Drake
            case 49345: // Call Emerald Drake
                spellInfo->Effects[EFFECT_1].Effect = 0;
                break;
            // ENDOF OCULUS SPELLS
            //
            case 40055: // Introspection
            case 40165: // Introspection
            case 40166: // Introspection
            case 40167: // Introspection
                spellInfo->Attributes |= SPELL_ATTR0_NEGATIVE_1;
                break;
            case 2378: // Minor Fortitude
                spellInfo->ManaCost = 0;
                spellInfo->ManaPerSecond = 0;
                break;
            case 24314: // Threatening Gaze
                spellInfo->AuraInterruptFlags |= AURA_INTERRUPT_FLAG_CAST | AURA_INTERRUPT_FLAG_MOVE | AURA_INTERRUPT_FLAG_JUMP;
                break;
            case 5420: // Tree of Life (Passive)
                spellInfo->Stances = 1 << (FORM_TREE - 1);
                break;
            case 45257: // Using Steam Tonk Controller
            case 45440: // Steam Tonk Controller
            case 60256: // Collect Sample
            case 82580: // Bravo Company Field Kit
            case 82587: // Bravo Company Field Kit
            case 88026: // Silversnap Swim Tonic
            case 94441: // Twilight Speech Linked Aura [INTERNAL]
            case 74934: // Inspire!
            case 74935: // Incite!
            case 74937: // Pander!
            case 74947: // Step Down
            case 76607: // Drums of the Turtle God
            case 80675: // Rockslide Reagent
            case 83699: // Trogg Crate
            case 79688: // Elementium Grapple Line
            case 67526: // Amazing G-Ray
            case 67508: // Blastcrackers
            case 67524: // Ear-O-Scope
            case 67525: // Infinifold Lockpick
            case 67522: // Kaja'mite Drill
            case 94652: // Aeonaxx Whelp Summon
            case 80524: // Summon Jade Crystal Composte
            case 66393: // Rolling with my Homies: Summon Hot Rod
            case 66611: // Rolling with my Homies: Hot Rod - Exit Spell
            case 66392: // Hot Rod
            case 91957: // Ping Signal Flare
            case 89821: // Helcular's Rod
            case 89824: // Helcular's Ire
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                break;
            case 68376: // Infrared Heat Focals
            case 69303: // Infrared Heat Focals
            case 77396: // Infrared Heat Focals
            case 77397: // Infrared Heat Focals
            case 78049: // Infrared Heat Focals
            case 78050: // Infrared Heat Focals
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                spellInfo->Attributes &= ~SPELL_ATTR0_CANT_CANCEL;
                break;
            case 68386: // Precious Cargo: Quest Accept
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER;
                spellInfo->StartRecoveryCategory = 5000;
                spellInfo->StartRecoveryTime = 5000;
                break;
            case 91551: // Keys to the Hot Rod
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER|TARGET_UNIT_CASTER;
                spellInfo->Effects[EFFECT_0].TargetB = TARGET_UNIT_CASTER|TARGET_UNIT_CASTER;
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                break;
            case 84069: // Summon Therazane
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_1].MiscValue = 0;
                spellInfo->Effects[EFFECT_1].MiscValueB = 0;
                break;
            case 82044: // Goldmine's Fire Totem
                spellInfo->RequiresSpellFocus = 0;
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                break;
            case 89447: // Razor-Sharp Scorpid Barb
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_NEARBY_ENTRY;
                break;
            case 95403: // Summon Azil
            case 95397: // Summon Millhouse
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 80678: // Summon Jaspertrip Crystal-gorger
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_RANDOM;
                break;
            case 81318: // Tombshroom Explosion
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_2_YARDS);
                break;
            case 72072: // Place Territorial Fetish
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(9);
                break;
            case 66600: // Rolling with my Homies: Summon Izzy
            case 66597: // Rolling with my Homies: Summon Ace
            case 66599: // Rolling with my Homies: Summon Gobber
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 74070: // Volcano: Fiery Boulder
            case 74072:
            case 74076:
            case 74085:
            case 70097:
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DEST_RANDOM|TARGET_DEST_DEST_RANDOM;
                spellInfo->Effects[EFFECT_0].TargetB = TARGET_DEST_DEST_RANDOM|TARGET_DEST_DEST_RANDOM;
                break;
            case 72768: // Throw Boulder
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_FRONT | TARGET_DEST_CASTER_FRONT;
                spellInfo->Effects[EFFECT_0].TargetB = TARGET_DEST_CASTER_FRONT | TARGET_DEST_CASTER_FRONT;
                break;
            case 68059: // Miner Troubles: Summon Frightened Miner
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 70649: // Capturing The Unknown: Player's Screen Effect
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(28);
                break;
            case 74425: // Cosmetic - Lightning Strike
                spellInfo->CastTimeEntry = sSpellCastTimesStore.LookupEntry(16);
                break;
            case 71091: // It's A Town-In-A-Box: Town-In-A-Box Plunger - Effect 2
                spellInfo->Effects[EFFECT_0].TriggerSpell = 0;
                spellInfo->Effects[EFFECT_1].TriggerSpell = 75740;
                break;
            case 71648: // Mechashark X-Steam
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB|TARGET_DEST_DB;
                break;
            case 71857: // Bilgewater Cartel Banner
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_FRONT|TARGET_DEST_CASTER_FRONT;
                break;
            case 72971: // Rockin' Powder Infused Rocket Boots
                spellInfo->RequiresSpellFocus = 0;
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(86);
                break;
            case 74474: // Spirit of Goldrinn
            case 74475: // Spirit of Lo'Gosh
                spellInfo->CastTimeEntry = sSpellCastTimesStore.LookupEntry(1);
                break;
            case 94979: // Engineering Discovery (DND)
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_SCRIPT_EFFECT;
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_NONE;
                break;
            // Slave Pens Spells
            // * Frost Lord Ahune
            case 46363: // Midsummer - Beam Attack against Ahune
                spellInfo->TargetA = TARGET_SRC_CASTER;
                spellInfo->TargetB = TARGET_UNIT_TARGET_ANY;
                break;
            // Halls Of Origination spells
            // * Temple Guardian Anhuur
            case 76606: // Disable Beacon Beams L
            case 76608: // Disable Beacon Beams R
                // Little hack, Increase the radius so it can hit the Cave In Stalkers in the platform.
                spellInfo->Effects[EFFECT_0].MaxRadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_45_YARDS);
                break;
            case 75115: // Searing Light
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 75322: // Reverberating Hymn
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_IGNORE_OTHER_CASTS;
                break;
            case 75323: // Reverberating Hymn Periodic
            case 90008:
                // Aura is refreshed at 3 seconds, and the tick should happen at the fourth.
                spellInfo->AttributesEx8 |= SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER;
                spellInfo->AttributesEx5 |= SPELL_ATTR5_USABLE_WHILE_STUNNED;
                break;
            // * Ammunae
            case 75657: // Ammunaes Buff should only target himself
            case 94970:
                spellInfo->Effects[0].TargetB = 0;
                spellInfo->Effects[1].TargetB = 0;
                break;
            case 89124: // Ammunae Heal
                spellInfo->Effects[0].TargetA = TARGET_UNIT_NEARBY_ENTRY;
                spellInfo->Effects[0].TargetB = 0;
                break;
            case 75702: // Noxious Spores
            case 89889:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                spellInfo->Effects[EFFECT_2].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                break;
            // * Setesh
            case 76681: // Setesh Chaos Blast Aura Radius
            case 89875:
                spellInfo->Effects[0].RadiusEntry = sSpellRadiusStore.LookupEntry(32);
                break;
            case 76684: // Chaos Burn Triggger
            case 89874:
                spellInfo->Effects[0].RadiusEntry = sSpellRadiusStore.LookupEntry(13);
                break;
            case 76784: // Chaos Portal Channel
                spellInfo->MaxAffectedTargets = 1;
                break;
            // * Rajh
            case 87653: // Inferno Leap
                 spellInfo->Effects[0].Effect = SPELL_EFFECT_JUMP;
                 spellInfo->Effects[0].ApplyAuraName = SPELL_AURA_NONE;
                break;
            case 74108: // Solar Fire Damage Aura
            case 89130:
            case 89133: //Solar Fire Damage Aura
            case 89878:
                spellInfo->Effects[0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_4_YARDS);
                spellInfo->Effects[1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_4_YARDS);
                break;
            // Vortex Pinnacle Spells
                // *Altairus
            case 88282: // Upwind of Altairus
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS);
                break;
            case 88314: // Altairus Tornado Range
                spellInfo->Effects[0].RadiusEntry = sSpellRadiusStore.LookupEntry(7);
                spellInfo->Effects[1].RadiusEntry = sSpellRadiusStore.LookupEntry(7);
                spellInfo->Effects[2].RadiusEntry = sSpellRadiusStore.LookupEntry(7);
                break;
            case 85158: // Howling Gale (Knockback)
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_16_YARDS);
                break;
            // CATACLYSM
            // SPELLS CLASSES
            // Druid
            case 94338: // Eclipse (Solar)
                spellInfo->Effects[EFFECT_0].BasePoints = 93402;
                break;
            case 16870: // Omen of Clarity
                spellInfo->ProcChance = 5.0f;
                break;
            case 78675: // Solar Beam
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(8);
                break;
            case 81261: // Solar Beam
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(8);
                break;
            // Priest
            case 73510: // Mind Spike
                spellInfo->Effects[EFFECT_0].TriggerSpell = 0;
                spellInfo->Effects[EFFECT_2].TargetA = TARGET_UNIT_TARGET_ENEMY;
                break;
            case 88667: // Holy Word: Sanctuary 3yd Dummy
                spellInfo->SpellFamilyName = SPELLFAMILY_PRIEST;
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(15);
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(85);
                break;
            case 88668: // Holy Word: Sanctuary 3yd Heal
                spellInfo->SpellFamilyName = SPELLFAMILY_PRIEST;
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(15);
                break;
            case 88685: // Holy Word: Sanctuary 6yd Dummy
            case 88686: // Holy Word: Sanctuary 6yd Heal
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(29);
                break;
            case 81782: // Power Word: Barrier
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(39);
                break;
            case 89485: // Inner Focus
                spellInfo->ProcCharges = 1;
                break;
            case 34709: // Shadow Sight
                spellInfo->Attributes |= SPELL_ATTR0_CANT_CANCEL;
                break;
            // Paladin
            case 85117:
            case 86172:
                spellInfo->ProcFlags = PROC_FLAG_DONE_SPELL_MELEE_DMG_CLASS |
                    PROC_FLAG_DONE_SPELL_RANGED_DMG_CLASS |
                    PROC_FLAG_DONE_SPELL_NONE_DMG_CLASS_POS |
                    PROC_FLAG_DONE_SPELL_NONE_DMG_CLASS_NEG |
                    PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_POS |
                    PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_NEG;
                spellInfo->ProcChance = 100;
                break;
            case 87168:
            case 87172:
                spellInfo->ProcFlags = PROC_FLAG_DONE_SPELL_MELEE_DMG_CLASS |
                    PROC_FLAG_DONE_SPELL_RANGED_DMG_CLASS |
                    PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_NEG;
                spellInfo->ProcChance = 100;
                break;
            // Mage
            case 79684: // Arcane Missiles Proc
                spellInfo->ProcChance = 40.0f;
                break;
            case 5143: // Arcane Missiles
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_INITIAL_AGGRO;
                break;
            case 11213: // Arcane Concentration Rank 1
            case 49018: // Onrushing Damnation Rank 1
                spellInfo->ProcChance = 3.0f;
                break;
            case 12574: // Arcane Concentration Rank 2
            case 49529: // Onrushing Damnation Rank 2
                spellInfo->ProcChance = 6.0f;
                break;
            case 12575: // Arcane Concentration Rank 3
            case 49530: // Onrushing Damnation Rank 3
                spellInfo->ProcChance = 10.0f;
                break;
            case 84722: // Invocation Rank 1 and 2
            case 84723:
                spellInfo->ProcChance = 0.0f;
                break;
            case 51755: // Camouflage
                spellInfo->AuraInterruptFlags = AURA_INTERRUPT_FLAG_TAKE_DAMAGE|AURA_INTERRUPT_FLAG_CAST|AURA_INTERRUPT_FLAG_TALK|AURA_INTERRUPT_FLAG_MELEE_ATTACK|AURA_INTERRUPT_FLAG_MOUNT;
                spellInfo->Effects[0].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_PET);
                spellInfo->Effects[1].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_PET);
                spellInfo->Effects[2].TargetB = SpellImplicitTargetInfo(TARGET_UNIT_PET);
                break;
            case 66:    // Invisibility
                spellInfo->Effects[EFFECT_1].TriggerSpell = 0;
                break;
            case 93983: // Skull Bash (Charge)
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(6);
                break;
            // Shaman
            case 77223: // Enhanced Elements
                spellInfo->Effects[EFFECT_1].BasePoints = 0;
                spellInfo->SpellFamilyName = SPELLFAMILY_SHAMAN;
                break;
            // Warlock
            case 54424: // Fel Intelligence
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);
                spellInfo->Effects[EFFECT_1].MaxRadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_200_YARDS);
                break;
            case 6789:  // Death Coil
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CANT_CRIT;
                break;
            case 77215: // Potent Afflictions
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                break;
            case 79268: // Warlock Harvest Soul Tick Timing
                spellInfo->Effects[EFFECT_0].Amplitude = 3000;
                break;
            case 65142: // Ebon Plague
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
                spellInfo->Effects[EFFECT_1].MiscValue = SPELL_SCHOOL_MASK_MAGIC;
                break;
            case 78788: // Fungal Growth Rank 1
                spellInfo->Effects[EFFECT_0].MiscValue = 81289;
                break;
            case 78789: // Fungal Growth Rank 2
                spellInfo->Effects[EFFECT_0].MiscValue = 81282;
                break;
            case 34433: // Shadowfiend
                spellInfo->Effects[EFFECT_0].MiscValueB = 67;
                break;
            // Hunter
            case 19263: // Deterrence
                spellInfo->Effects[EFFECT_2].ApplyAuraName = SPELL_AURA_MOD_PACIFY;
                break;
            // SPELLS GENERETIC
            case 73701: // Vashj'ir - Sea Legs (due to buggy liquid level calculation in vashjir)
                spellInfo->AuraInterruptFlags         = 0;
                spellInfo->SpellCastingRequirementsId = 0;
                spellInfo->SpellInterruptsId          = 0;
                spellInfo->SpellClassOptionsId        = 0;
                break;
            case 97992: // Slam (Off-Hand)
                spellInfo->StartRecoveryCategory = 0;
                spellInfo->StartRecoveryTime = 0;
                spellInfo->CastTimeEntry = sSpellCastTimesStore.LookupEntry(1);
                break;
            case 16086: // Seasoned Winds (Rank 1)
                spellInfo->Effects[EFFECT_0].BasePoints = 97;
                break;
            case 16544: // Seasoned Winds (Rank 2)
                spellInfo->Effects[EFFECT_0].BasePoints = 195;
                break;
            case 90174: // Divine Purpose
                spellInfo->ProcCharges = 1;
                break;
            case 53709: // Sacred Duty r1
                spellInfo->Effects[EFFECT_0].BasePoints = 25;
                break;
            case 53710: // Sacred Duty r2
                spellInfo->Effects[EFFECT_0].BasePoints = 50;
                break;
            case 49575: // Death Grip
                spellInfo->Effects[EFFECT_0].MiscValueB = 15;
                break;
            case 92832: // Leap of Faith
            case 97817:
                spellInfo->Effects[EFFECT_0].MiscValueB = 55;
                break;
            case 92652: // Big Cauldron of Battle
            case 92654:
                spellInfo->Effects[EFFECT_0].MiscValue = 207364;
                break;
            case 33881: // Nature's Ward
            case 33882:
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_PROC_TRIGGER_SPELL;
                break;
            case 87934: // Serpent Spread
            case 87935:
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_DUMMY;
                break;
            case 88453: // Serpent Sting
                spellInfo->Effects[EFFECT_0].TargetB = SpellImplicitTargetInfo();
                spellInfo->Effects[EFFECT_1].TargetB = SpellImplicitTargetInfo();
                break;
            case 1515:  // Tame Beast
            case 13481:
                spellInfo->SpellFamilyName = SPELLFAMILY_HUNTER;
                spellInfo->AttributesEx5 &= ~SPELL_ATTR5_HASTE_AFFECT_DURATION;
                break;
           case 51723: // Fan of Knives
                spellInfo->Effects[0].RadiusEntry = sSpellRadiusStore.LookupEntry(14);   // 8yd
                spellInfo->ExcludeCasterAuraSpell = 0;
                break;
           case 51690: // Killing Spree
                spellInfo->Effects[1].RadiusEntry = sSpellRadiusStore.LookupEntry(13);   // 10yd
                break;
           case 26679: // Deadly Throw
                spellInfo->ExcludeCasterAuraSpell = 0;
                break;
           case 1120: // Drain Soul
               spellInfo->Effects[EFFECT_2].Effect = SPELL_EFFECT_APPLY_AURA;
               spellInfo->Effects[EFFECT_2].ApplyAuraName = SPELL_AURA_CHANNEL_DEATH_ITEM;
               spellInfo->Effects[EFFECT_2].BasePoints = 3;
               break;
           case 85767: // Dark Intent (Target)
               spellInfo->SpellFamilyName = SPELLFAMILY_GENERIC;
               break;
           case 85768: // Dark Intent (Self)
               spellInfo->SpellFamilyName = SPELLFAMILY_WARLOCK;
               break;
           case 29341: // Shadowburn
               spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_CHANNEL_DEATH_ITEM;
               break;
            case 18703: // Health Funnel
                spellInfo->Effects[EFFECT_0].BasePoints = 10;
                break;
            case 18704: // Health Funnel
                spellInfo->Effects[EFFECT_0].BasePoints = 20;
                break;
            case 85103: // Cremation
                spellInfo->Effects[EFFECT_1].BasePoints = 50;
                break;
            case 85104: // Cremation
                spellInfo->Effects[EFFECT_1].BasePoints = 100;
                break;
            case 85526: // Hand of Gul'Dan (Aura Visual)
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(8);
                break;
            case 93974: // Aura of Foreboding
            case 93975:
            case 93986:
            case 93987:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(26);
                break;
            case 14168: // Improved Expose Armor
                spellInfo->Effects[EFFECT_0].BasePoints = 50;
                break;
            case 14169: // Improved Expose Armor
                spellInfo->Effects[EFFECT_0].BasePoints = 100;
                break;
            case 76547: // Mana Adept - Mage Mastery
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_ADD_PCT_MODIFIER;
                spellInfo->Effects[EFFECT_0].MiscValue = SPELLMOD_DAMAGE;
                break;
            case 56807: // Glyph of Hemorrhage
            case 32215: // Victorious State
                spellInfo->Effects[EFFECT_0].TriggerSpell = NULL;
                break;
            case 56226: // Glyph of Soul Swap
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_ADD_FLAT_MODIFIER;
                spellInfo->Effects[EFFECT_0].BasePoints = 30000;
                spellInfo->Effects[EFFECT_0].MiscValue = SPELLMOD_COOLDOWN;
                spellInfo->Effects[EFFECT_0].SpellClassMask = flag96(0x00000000, 0x00000000, 0x01000000);
                break;
            case 81291: // Fungal Growth
            case 81283:
                spellInfo->RecoveryTime = 0;
                spellInfo->StartRecoveryTime = 0;
                break;
            case 50516: // Typhoon
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_FRONT;
                break;
            case 74434: // Soulburn
                spellInfo->ProcCharges = 1;
                break;
            case 90164: // Astral Alignment
                spellInfo->ProcCharges = 255;
                break;
            case 51271: // Pillar of Frost
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_SCRIPT_EFFECT;
                spellInfo->Effects[EFFECT_1].MiscValue = 0;
                break;
            case 96268: // Death's Advance
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(21);
                break;
            case 51698: // Honor Among Thieves
                spellInfo->SpellFamilyName = SPELLFAMILY_ROGUE;
                break;
            case 2818: // Deadly Poison
                spellInfo->AttributesEx8 |= SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER;
                break;
            case 51460: // Runic Corruption
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_NONE;
                spellInfo->Effects[EFFECT_0].MiscValueB = 2;
                break;
            case 62758: // Wild Hunt
            case 62762:
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_DUMMY;
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_DUMMY;
                break;
            case 83967: // Have Group, Will Travel
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_DUMMY;
                break;
            case 92294: // Frostfire Orb
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(21);
                spellInfo->AttributesEx3 |= SPELL_ATTR3_DEATH_PERSISTENT;
                break;
            case 87204: // Sin and Punishment
                spellInfo->SpellFamilyName = SPELLFAMILY_PRIEST;
                break;
            case 4524:  // Demonic Immolation
                spellInfo->SpellFamilyName = SPELLFAMILY_WARLOCK;
                break;
            case 31803: // Censure
                spellInfo->AttributesEx4 |= SPELL_ATTR4_DAMAGE_DOESNT_BREAK_AURAS;
                break;
            case 50796: // Chaos Bolt
                spellInfo->AttributesEx4 |= SPELL_ATTR4_IGNORE_RESISTANCES;
                break;
            case 82691: // Ring of Frost
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(8);   // 5 yd
                break;
            case 57416: // Immune to Daze
                spellInfo->AttributesEx3 |= SPELL_ATTR3_DEATH_PERSISTENT;
                break;
            case 118:   // Polymorph
            case 61305: // Polymorph (other animal)
            case 28272: // Polymorph (other animal)
            case 61721: // Polymorph (other animal)
            case 61780: // Polymorph (other animal)
            case 28271: // Polymorph (other animal)
            case 20511: // Intimidating Shout
                spellInfo->AuraInterruptFlags = AURA_INTERRUPT_FLAG_TAKE_DAMAGE;
                break;
            case 75141: // Dream of Skywall
            case 75142: // Dream of Deepholm
            case 75144: // Dream of Hyjal
            case 75145: // Dream of Ragnaros
            case 75146: // Dream of Azshara
            case 94743: // Dream of Destruction
                spellInfo->SpellCooldownsId = 1439; // 7 Days
                spellInfo->CategoryRecoveryTime = 604800000; // 7 Days
                spellInfo->RecoveryTime = 0;
                spellInfo->StartRecoveryTime = 0;
                break;
            // SPELLS QUESTS
            case 95869: // Wyvern Ride Aura [INTERNAL]
                spellInfo->Effects[EFFECT_1].Effect = 0;
                spellInfo->Effects[EFFECT_1].ApplyAuraName = 0;
                break;
            case 71898: // Funeral Offering
            case 73817: // Thonk's Spyglass
            case 62081: // Frenzied Cyclone Bracers
            case 65300: // Ping for Artifact
            case 65207: // Disrupting the Artifact
            case 66204: // Blow Pirate Signal Horn
            case 62772: // Summon Gorat's Spirit
            case 64074: // Throw Accursed Ore
            case 63797: // Throw Blood
            case 63829: // Throw Signal Powder
            case 64605: // Splintertree Axe
            case 65196: // Create Mystlash Oil
            case 65514: // Unbathed Concoction
            case 79262: // Summon Lou's House
            case 82029: // Call Stalvan
            case 91085: // Place Goblin Pocket-Nuke
            case 82585: // Plant Seaforium
            case 83176: // Place Dithers' Drum
            case 84964: // Rayne's Seed
            case 85308: // Trial of the Crypt
            case 85327: // Destroy Thresh'jin's Body
            case 70155: // Blow Horn of Challenge
            case 71030: // Burning Pitch
            case 42356: // Burn Direhorn Post
            case 75689: // Pirate's Crowbar
            case 77390: // Setup an Oil Drilling Rig
            case 77327: // Splithoof Brand
            case 84925: // Shu'Halo Artifacts
            case 77041: // Summon Marion Wormwing
            case 89314: // Orb of the Stars
            case 85720: // Attack Signal
            case 86499: // Water of Life
                spellInfo->RequiresSpellFocus = 0;
                break;
            case 83836: // Summon Twilight Striker
            case 85899: // Summon Highbank Skirmisher
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DEST_RANDOM;
                break;
            case 85910: // Repairs
                spellInfo->Effects[EFFECT_0].BasePoints = 4250;
                break;
            case 73133: // Frightened Tadpole
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_DEST_AREA_ENTRY;
                break;
            case 83903: // Bush Chicken Explosion!
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_SRC_CASTER;
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(7);   // 2 yd
                spellInfo->Effects[EFFECT_2].RadiusEntry = sSpellRadiusStore.LookupEntry(7);   // 2 yd
                break;
            case 84574: // Rocket Blast
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(27);   // 50 yd
                break;
            case 64340: // Blessing of the Moonstalker
            case 64341: // Blessing of the Stag
            case 64329: // Blessing of the Thistle Bear
                spellInfo->AttributesEx3 |= SPELL_ATTR3_DEATH_PERSISTENT;
                break;
            case 62624: // Torch Shatterspear Supplies
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_NEARBY_ENEMY;
                break;
            case 62684: // Depth Charge Countdown Pulse
                spellInfo->CategoryRecoveryTime = 10000; // 10 secs
                spellInfo->RecoveryTime = 10000;
                spellInfo->StartRecoveryTime = 10000;
                break;
            case 58354: // Chapter V
                spellInfo->Effects[EFFECT_0].MiscValue = 32768;
                break;
            case 65581: // Snared in Net
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_NONE;
                break;
            case 63704: // Imp Disguise
                spellInfo->Effects[EFFECT_1].MiscValue = 32768;
                break;
            case 65551: // Blastranaar Impact
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                spellInfo->Effects[EFFECT_0].MiscValue = 0;
                break;
            case 28888: // Blastranaar Explosive Impact
                spellInfo->Effects[EFFECT_1].BasePoints = 0;
                spellInfo->Effects[EFFECT_1].MiscValue = 0;
                break;
            case 85214: // Summon Axebite Grunt
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DEST_RANDOM;
                break;
            case 64711: // Throw Glaive
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(12);   // 100 yd
                spellInfo->Effects[EFFECT_0].MaxRadiusEntry = sSpellRadiusStore.LookupEntry(12);   // 100 yd
                break;
            case 65535: // Playing Possum
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_DEST_AREA_ENTRY;
                break;
            case 79436: // Wake Harvest Golem
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_1].MiscValue = 0;
                spellInfo->Effects[EFFECT_1].MiscValueB = 0;
                break;
            case 79587: // Vision of the Past (Ride)
                spellInfo->Effects[EFFECT_2].MiscValue = 2;
                break;
            case 79821: // Zul'Gurub Mind Vision
            case 70593: // Nightmare Scar
                spellInfo->Effects[EFFECT_0].MiscValue = 2;
                break;
            case 44531: // Dash
                spellInfo->CategoryRecoveryTime = 10000; // 10 secs
                spellInfo->RecoveryTime = 10000;
                spellInfo->StartRecoveryTime = 10000;
                break;
            case 80885: // High Priestess Jeklik: Zanzil Teleport 01
            case 80884: // High Priestess Jeklik: Zanzil Teleport 02
            case 80883: // High Priestess Jeklik: Zanzil Teleport 03
            case 80882: // High Priestess Jeklik: Zanzil Teleport 04
            case 80853: // High Priestess Jeklik: Zanzil Teleport 05
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER | TARGET_DEST_DB;
                break;
            case 81310: // Getting In With the Bloodsail: Set Bloodsail Faction Friendly
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_FORCE_REACTION;
                spellInfo->Effects[EFFECT_0].MiscValue = 87;
                spellInfo->Effects[EFFECT_0].BasePoints = 4;
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(21);
                break;
            case 81743: // Doublerum: Apply Phase Aura with Boom
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_APPLY_AURA;
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_PHASE;
                spellInfo->Effects[EFFECT_0].MiscValue = 32768;
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(21);
                spellInfo->Attributes |= SPELL_ATTR0_HIDDEN_CLIENTSIDE;
                break;
            case 84940: // Despawn All Summons
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER;
                break;
            case 85197: // Raise Forsaken
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CONE_ENTRY;
                spellInfo->Effects[EFFECT_1].TargetA = TARGET_UNIT_CONE_ENTRY;
                spellInfo->Effects[EFFECT_2].TargetA = TARGET_UNIT_CONE_ENTRY;
                break;
            case 85411: // Raise Forsaken
            case 85950:
            case 87293: // Marked for Retrieval
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_NEARBY_ENTRY;
                break;
            case 85871: // Summon Daschla
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_BACK_LEFT;
                break;
            case 85870: // Summon Agatha
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_BACK;
                break;
            case 85869: // Summon Arthura
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_BACK_RIGHT;
                break;
            case 88543: // Ride Skeletal Steed
            case 89970: // Orkus Camera
                spellInfo->Effects[EFFECT_2].MiscValue = 2;
                break;
            case 88476: // Quest Giver
                spellInfo->Effects[EFFECT_1].Effect = 0;
                spellInfo->Effects[EFFECT_1].ApplyAuraName = 0;
                break;
            case 89089: // Shovel
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_DUMMY;
                break;
            case 87969: // Paralytic Poison
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_DUMMY;
                break;
            case 89295: // Summon Lydon
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_BACK_LEFT;
                break;
            case 89296: // Summon Johnny
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_BACK_RIGHT;
                break;
            case 89450: // Smash
                spellInfo->Effects[EFFECT_2].Effect = SPELL_EFFECT_DUMMY;
                break;
            case 90122: // Ride to Purgation
                spellInfo->Effects[EFFECT_2].MiscValue = 2;
                spellInfo->Effects[EFFECT_0].BasePoints = 2;
                break;
            case 90205: // Summon Orkus
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_MOD_INVISIBILITY;
                spellInfo->Effects[EFFECT_1].BasePoints = 1;
                spellInfo->Effects[EFFECT_1].MiscValue = 4;
                break;
            case 72165: // Return to Nablya
                spellInfo->Effects[EFFECT_1].TargetA = TARGET_UNIT_CASTER;
                spellInfo->Effects[EFFECT_1].TargetB = TARGET_UNIT_CASTER;
                break;
            case 71775: // Throw Meat
                spellInfo->Effects[EFFECT_0].Effect = 0;
                break;
            case 90206: // Summon Purgation Controller
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_SUMMON;
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].MiscValue = 48515;
                spellInfo->Effects[EFFECT_0].MiscValueB = 3079;
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(6);
                break;
            case 90271: // Heroic Leap
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_NEARBY_ENEMY;
                spellInfo->Effects[EFFECT_1].TargetA = TARGET_UNIT_NEARBY_ENEMY;
                break;
            case 90209: // Purgation Isle (Summons)
            case 90210:
            case 90211:
            case 90278:
            case 90407:
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(6);
                break;
            case 91608: // Apocalypse Camera
            case 81243: // Summon Keeshan's Boat
                spellInfo->Effects[EFFECT_0].BasePoints = 46598;
                break;
            case 91393: // Summon Lilith
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(6);
                break;
            case 81607: // Render's Valley Camera
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                break;
            case 81639: // Render's Valley Explosion (NUKE)
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_1].BasePoints = 0;
                break;
            case 81808: // Summon Bravo Company Siege Tank
            case 87436: // RG: Master Force Phase/Invis
                spellInfo->Effects[EFFECT_0].MiscValue = 2;
                break;
            case 82068: // Darkblaze
                spellInfo->Effects[EFFECT_0].BasePoints = 1;
                break;
            case 88291: // Summon Lunk
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(21);
                spellInfo->Effects[EFFECT_0].MiscValueB = 2924;
                break;
            case 88498: // Summon Brotherhood Flying Machine
                spellInfo->Effects[EFFECT_0].BasePoints = 63313;
                break;
            case 88496: // Shoot
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(199); // 100yd
                break;
            case 89562: // Blackrock Cudgel of Discipline
                spellInfo->Effects[EFFECT_1].TargetA = TARGET_UNIT_TARGET_ANY;
                break;
            case 89947: // AODR: Summon Camera/Phase
                spellInfo->Effects[EFFECT_0].BasePoints = 46598;
                spellInfo->Effects[EFFECT_1].MiscValue = 32768;
                break;
            case 90069: // Summon Obsidian-Cloaked Dragon
                spellInfo->Effects[EFFECT_1].TriggerSpell = 0;
                break;
            case 77371: // Demon Hunter's Resolve
                spellInfo->Effects[EFFECT_0].TriggerSpell = 0;
                break;
            case 86557: // TDDC 1: Summon Theldurin
                spellInfo->Effects[EFFECT_0].MiscValue = 2;
                break;
            case 87737: // TDDC 2: Summon Lucien
                spellInfo->Effects[EFFECT_0].MiscValue = 4;
                break;
            case 86675: // TDDC 3: Summon Martek's Hog
                spellInfo->Effects[EFFECT_0].MiscValue = 8;
                break;
            case 84336: // Ride Vehicle - Seat 5
            case 84319: // Ride Vehicle - Seat 4
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(40);
                break;
            case 87843: // Cave In
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(1);
                spellInfo->Effects[EFFECT_1].TriggerSpell = 0;
                break;
            case 87593: // Jurrix's Fiery Blast
                spellInfo->DmgClass = SPELL_DAMAGE_CLASS_MAGIC;
                spellInfo->Attributes &= ~SPELL_ATTR0_REQ_AMMO;
                break;
            case 83605: // Whinny
                spellInfo->CategoryRecoveryTime = 6000; // 6 secs
                spellInfo->RecoveryTime = 6000;
                spellInfo->StartRecoveryTime = 6000;
                break;
            case 83994: // Summon Ebon Gargoyle
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_0_5_YARDS);
                break;
            case 84009: // Release Ebon Gargoyle
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_0_5_YARDS);
                spellInfo->Effects[EFFECT_1].TriggerSpell = 0;
                break;
            case 84198: // Summon Enthralled Valkyr
                spellInfo->Effects[EFFECT_0].MiscValueB = 3032;
                break;
            case 84252: // The Reckoning: Force Phase
                spellInfo->Effects[EFFECT_0].MiscValue = 8;
                break;
            case 84208: // The Reckoning (Event)
            case 84209:
            case 84211:
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(565);
                break;
            case 85218: // Summon Gidwin Goldbraids
                spellInfo->Effects[EFFECT_0].MiscValue = 46173;
                break;
            case 85217: // Summon Tarenar Sunstrike
                spellInfo->Effects[EFFECT_0].MiscValue = 45957;
                break;
            case 85651: // GFR: Summon Tarenar Sunstrike
                spellInfo->Effects[EFFECT_0].MiscValue = 46199;
                break;
            case 85652: // GFR: Summon Fiona
                spellInfo->Effects[EFFECT_0].MiscValue = 46201;
                break;
            case 85655: // GFR: Summon Argus Highbeacon
                spellInfo->Effects[EFFECT_0].MiscValue = 46200;
                break;
            case 73720: // See Frazzlecraz Cave-In
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_DUMMY;
                break;
            case 75859: // Pirate Accuracy Increasing: Summon River Boat
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].BasePoints = 63314;
                break;
            case 75976: // Circle the Wagons, Er... Boats: Summon River Boat
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].MiscValue = 40658;
                spellInfo->Effects[EFFECT_0].BasePoints = 63314;
                break;
            case 76203: // River Boat
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER;
                break;
            case 88857: // The Elder Crone: Controller Disabled
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 75357: // Two If By Boat: Force Cast from Gossip - Alliance
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].BasePoints = 46598;
                break;
            case 76835: // Ambushed by Thisalee
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER;
                break;
            case 74359: // Extinguish Flames
                spellInfo->Effects[EFFECT_2].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_2].MiscValue = 0;
                break;
            case 88258: // Summon Possessed Firebeard Gryphon
                spellInfo->Effects[EFFECT_0].BasePoints = 63313;
                break;
            case 74973: // Power Word: Fortitude (Kezan)
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            case 84101: // Deepholm Intro Taxi
                spellInfo->Effects[EFFECT_0].BasePoints = 63313;
                break;
            case 82297: // Exploding Thunder Stone
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_15_YARDS_2);
                break;
            case 75922: // Searing Stone
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                break;
            case 79528: // Potion of Shrouding
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER;
                spellInfo->Effects[EFFECT_1].TargetA = TARGET_UNIT_CASTER;
                break;
            case 79586: // Vision of the Past
                spellInfo->RequiresSpellFocus = 0;
                break;
            case 89679: // Summon Blood of Iso'rath (Aura)
            case 89680:
            case 89681:
            case 89682:
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(4);
                break;
            case 89675: // Summon Blood of Iso'rath (Summons)
            case 89676:
            case 89677:
            case 89678:
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DEST_RANDOM;
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_60_YARDS);
                spellInfo->Effects[EFFECT_0].MaxRadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_60_YARDS);
                break;
            case 89823: // Summon Earthen Ring Gryphon Exit
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 84448: // Searing Breath
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_2_YARDS);
                spellInfo->Effects[EFFECT_0].BasePoints = 5;
                break;
            case 82138: // Summon Earthcaller Torunscar
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 83659: // Summon Temple Finale Camera
                spellInfo->Effects[EFFECT_0].BasePoints = 46598;
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 94614: // Summon Young Stone Drake
                spellInfo->Effects[EFFECT_0].MiscValueB = 64;
                break;
            case 85270: // Summon Lirastrasza
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 94551: // Mirror Image Aura [INTERNAL ONLY]
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_NEARBY_ENTRY;
                break;
            case 69971: // Necessary Roughness: Summon Steamwheedle Shark
            case 69976:
            case 69977:
            case 69978:
            case 69979:
            case 69980:
            case 69981:
            case 69982:
            case 70075: // Fourth and Goal: Summon Bilgewater Buccaneer
            case 66322: // Fourth and Goal: Summon Deathwing
            case 89360: // Summon Harrison
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 85018: // Summon Harrison 02
            case 84624: // Summon Staff Bunny
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(5);
                break;
            case 84600: // Summon Harrison 01
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 87694: // Summon Meteor
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB|TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].TargetB = TARGET_DEST_DB|TARGET_DEST_DB;
                break;
            case 87701: // Meteor Impact
                spellInfo->Effects[EFFECT_1].BasePoints = 300;
                break;
            case 87755: // Blazing Eruption
                spellInfo->Effects[EFFECT_0].BasePoints = 200;
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(8);
                break;
            case 70256: // 447: Gasbot Gas Stream
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER|TARGET_UNIT_CASTER;
                break;
            case 70226: // 447: Overloaded Generator Visual
            case 70236: // 447: Stove Leak Visual
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(6);
                break;
            case 73105: // Old Friends: Summon Flying Bomber
            case 73746: // Wild Mine Cart Ride: Summon Mine Cart
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 89327: // Summon Adarrah - Breakout
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(25);
                break;
            case 88510: // Summon Lost City Intro Betrayal Camera
            case 88489: // Summon High Prophet
            case 88487: // Summon Ramkahet Traitor
            case 88488: // Summon Ramkahet Traitor
            case 88523: // Summon Ramkahet Traitor
            case 89101: // Summon Adarrah - Mantaur Event
            case 89074: // Summon Lost City Intro MANTAUR Camera
            case 89077: // Summon Prince Nadun
            case 89075: // Summon Mantaur 01
            case 89076: // Summon Mantaur 02
            case 91974: // Summon High Commander Kamses
            case 91630: // Summon Phaoris
            case 91643: // Summon Vizier
            case 91708: // Summon Envoy
            case 91634: // Summon High Priest
            case 94261: // Summon Sun's Radiance [INTERNAL]
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 91628: // Summon High Council Event Camera
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                break;
            case 88561: // Lost City - Transform Channel
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(1);
                break;
            case 89082: // MANTAUR Custom Ride
                spellInfo->Effects[EFFECT_0].BasePoints = 3;
                break;
            case 94834: // Escape from the Lost City Exit Spell [INTERNAL]
                spellInfo->TargetA = TARGET_UNIT_CASTER;
                break;
            case 91377: // Summon Post-Orsis Event Camera
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].BasePoints = 63314;
                break;
            case 94696: // Fusion Core Ride Aura [INTERNAL]
                spellInfo->Effects[EFFECT_1].Effect = 0;
                break;
            case 91956: // Summon Fall of Neferset Camera
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].BasePoints = 0;
                break;
            case 85142: // Tipping The Balance (Quest)
            case 85887:
            case 85896:
            case 85908:
            case 85019:
            case 85885:
            case 85895:
            case 85907:
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(6);
                break;
            case 88891: // Cannon
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_65_YARDS);
                break;
            case 94189: // Summon Camera Bunny
            case 94052: // Summon Camera Bunny
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_1].MiscValueB = 0;
                break;
            case 90435: // Lunar Strike
                spellInfo->Effects[EFFECT_0].BasePoints = 2500;
                break;
            case 90727: // Summon Harrison
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 91055: // Designate Target
                spellInfo->RangeEntry = sSpellRangeStore.LookupEntry(13);
                break;
            case 87991: // Shadow Storm
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_8_YARDS);
                spellInfo->Effects[EFFECT_0].BasePoints = 1000;
                break;
            case 94270: // Summon Camera Bunny
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_1].MiscValueB = 0;
                break;
            case 94536: // Summon Camera Bunny
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_1].MiscValueB = 0;
                break;
            case 94537: // Summon Clone
            case 94572: // Summon Camera Bunny
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 79412: // Summon Multi-Bot
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_RIGHT;
                break;
            case 84941: // Summon Arthura
                spellInfo->Effects[EFFECT_0].MiscValue = 45611;
                break;
            case 80964: // Skull Bash
            case 80965:
            case 82364:
            case 82365:
                spellInfo->AttributesEx3 |= SPELL_ATTR3_IGNORE_HIT_RESULT;
                break;
            case 88027: // Storm Shield
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                break;
            case 92916: // Lifebinder's Boon
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_VEHICLE | TARGET_UNIT_CASTER;
                break;
            case 89040: // Alexstrasza's Tear
                spellInfo->AttributesEx4 &= ~SPELL_ATTR4_TRIGGERED;
                spellInfo->RequiresSpellFocus = 0;
                break;
            case 89008: // Mother's Flame
                spellInfo->Effects[EFFECT_0].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_UNIT_CASTER|TARGET_UNIT_CASTER;
                spellInfo->Effects[EFFECT_0].TargetB = TARGET_UNIT_CASTER | TARGET_UNIT_CASTER;
                spellInfo->Effects[EFFECT_1].TargetA = TARGET_UNIT_CASTER | TARGET_UNIT_CASTER;
                spellInfo->Effects[EFFECT_1].TargetB = TARGET_UNIT_CASTER | TARGET_UNIT_CASTER;
                break;
            case 86625: // Mr. Goldmine's Wild Ride: Summon Mine Cart
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 86466: // The Elementium Axe
                spellInfo->Effects[EFFECT_1].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->Effects[EFFECT_2].Effect = SPELL_EFFECT_DUMMY;
                spellInfo->RequiresSpellFocus = 0;
                break;
            case 86873: // Fire Portal Controller
                spellInfo->RequiresSpellFocus = 0;
                break;
            case 88524: // Liquid Flame
            case 88534: // Stormhammer
                spellInfo->Effects[EFFECT_0].BasePoints = 500;
                break;
            case 88609: // Belch
                spellInfo->Effects[EFFECT_0].BasePoints = 200;
                break;
            case 93519: // Lava Pool
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_20_YARDS);
                break;
            case 93721: // Lava Pool
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_NONE;
                break;
            case 87357: // STM: Summon Skullcrusher
            case 87358: // STM: Summon Chogall
            case 87362: // STM: Summon Mirror
            case 87363: // STM: Summon Camera
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB;
                break;
            case 88981: // Spirit Realm
                spellInfo->Effects[EFFECT_0].MiscValueB = 0;
                spellInfo->Effects[EFFECT_0].MiscValue = 395;
                break;
            case 92272: // Item - Collecting Mana
                spellInfo->Effects[EFFECT_1].BasePoints = 0;
                break;
            case 91976: // Place Ticker's Explosives
                spellInfo->RequiresSpellFocus = 0;
                break;
            // INSTANCES
            // Blackrock Caverns
            case 74852: // Lava Strike
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_80_YARDS);
                break;
            case 82192: // Chains of Woe
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(18);
                break;
            // * Corla, Herald of Twilight
            case 75650: // Nether Dragon Essence
            case 75653:
            case 75654:
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_CASTER_RADIUS;
                break;
            case 75732: // Twilight Evolution
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_NONE;
                break;
            case 75610: // Evolution
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(28);
                break;
            // * Karsh Steelbender
            case 90406: // Lava Pool
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                break;
            case 76007: // Lava Spout N
            case 93565: // Lava Spout H
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_5_YARDS);
                break;
            // Shadowfang Keep
            // * Commander Springvale
            case 67802: // Desecration Arm
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_7_YARDS);
                break;
            case 93691: // Desecration Damage
            case 94370:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                break;
            // * Lord Walden
            case 93505: // Conjure Frost Mixture
            case 93702:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_45_YARDS);
                break;
            case 93535: // Frost Shard Damage
            case 93703:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_2_YARDS);
                break;
            case 93617: // Mixture Debuff
                spellInfo->AuraInterruptFlags = AURA_INTERRUPT_FLAG_MOVE;
                break;
            // * Lord Godfrey
            case 96344: // Pistol Barrage Summon
                spellInfo->MaxAffectedTargets = 1;
                break;
            // Stormwind Stockade
            // * Randolph Moloch
            case 55964: // Vanish
                break;
            // The Deadmines
            // * Glubtok
            // The Stonecore
            // * Corborus
            case 92111: // Random taunt
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 81828: // Thrashing Charge
            case 92651:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_40_YARDS);
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_40_YARDS);
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_CONE_LINE;
                break;
            case 82415: // Dampening Wave
            case 92650:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_60_YARDS);
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_60_YARDS);
                break;
            // * Slabhide
            case 82530: // Face Random Player
                spellInfo->MaxAffectedTargets = 1;
                break;
            // * High Priestess Azil
            case 79354: // Force Grip
                spellInfo->Effects[EFFECT_0].BasePoints = 3;
                break;
            case 79021: // Seismic Shard
                spellInfo->AttributesEx4 |= SPELL_ATTR4_FIXED_DAMAGE;
                break;
            // The Lost City of the Tol'Vir
            // * Lockmaw and Augh
            case 84799: // Paralytic Blow Dart
            case 89989:
                spellInfo->MaxAffectedTargets = 1;
                break;
            // * High Prophet Barim
            case 81942: // Heavens Fury
            case 90040:
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_4_YARDS);
                break;
            case 91196: // Blaze of the Hevans Fire Damage
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_3_YARDS);
                spellInfo->Effects[EFFECT_1].Effect = 0;
                spellInfo->Effects[EFFECT_2].TriggerSpell = 0;
                break;
            case 88814: // Hollowed Ground
            case 90010:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_13_YARDS);
                break;
            // * General Husam
            case 83112:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_2_YARDS);
                break;
            case 83454: // Shockwave Damage
            case 90029:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_4_YARDS);
                break;
            // * Siamat
            case 83566: // Wailing Winds Knockback
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_INITIAL_AGGRO;
                break;
            case 83446: // Cloud Burst
            case 90030:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_6_YARDS);
                break;
            case 83151: // Absorb Storms
                spellInfo->MaxAffectedTargets = 1;
                spellInfo->Effects[EFFECT_0].TriggerSpell = 0;
                break;
            case 84987: // Gathered Storms Damage
                spellInfo->MaxAffectedTargets = 2;
                break;
            // Grim Batol
            // * General Umbriss
            case 74040: // Engulfing Flames
            case 90904:
                spellInfo->AttributesEx3 |= SPELL_ATTR3_NO_INITIAL_AGGRO;
                break;
            case 74039:
                spellInfo->RecoveryTime = 1000;
                spellInfo->CategoryRecoveryTime = 1000;
                spellInfo->StartRecoveryTime = 1000;
                break;
            // * Forgemaster Throngus
            case 90764:
                spellInfo->AttributesEx8 |= SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER;
                break;
            // * Drahga Shadowburner
            case 82850: // Flaming Fixate
                spellInfo->AttributesEx4 |= SPELL_ATTR4_TRIGGERED;
                break;
            case 43671: // Ride Vehicle
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            // * Erudax
            case 75694: // Speed Debuff
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_100_YARDS);
                break;
            case 75520: // Twilight Corruption
            case 91049:
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 75809: // Shield of Nightmares
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_50000_YARDS);
                break;
            // RAIDS
            // Firelands
            // * Ragnaros
            case 99510: // Raise Lava Damage
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_CONE_LINE;
                break;
            // Blackwing Descent
            // * Magmaw
            case 77917: // Launch Hook
            case 77941:
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            case 78936: // Summon Lava Parasite
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_3_YARDS);
                break;
            // * Omnotron Defense System
            case 78740: // Activated
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_DUMMY;
                break;
            case 79710: // Arkane Anhilator
            case 91540:
            case 91541:
            case 91542:
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CANT_CRIT;
                break;
            // * Atramedes
            case 77672: // Sonar Pulse NH
            case 92411:
                spellInfo->MaxAffectedTargets = 4;
                break;
            case 92412: // Sonar Pulse HC
            case 92413:
                spellInfo->MaxAffectedTargets = 7;
                break;
            // Throne of the Tides
            case 75700: // Geyser
                spellInfo->Effects[EFFECT_2].Effect = 0;
                break;
            case 76609: // Void Rip
                spellInfo->Effects[EFFECT_0].MiscValue = 200;
                break;
            case 76953: // Purify
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_99_YARDS);
                break;
            case 99816: // Fiery Tornado
            case 100734:
            case 100733:
            case 100735:
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_5_YARDS);
                spellInfo->Effects[EFFECT_1].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_5_YARDS);
                break;
            case 83441:
            case 83437:
            case 83648:
            case 83360:
                spellInfo->MaxAffectedTargets = 1;
                break;
            case 95284: // Throne of the Tides Teleportes
            case 95285:
                spellInfo->Effects[EFFECT_0].TargetA = TARGET_DEST_DB|TARGET_DEST_DB;
                spellInfo->Effects[EFFECT_0].TargetB = TARGET_DEST_DB|TARGET_DEST_DB;
                break;
            case 83561: // Blight of Ozumat
            case 91495:
                spellInfo->AttributesEx8 |= SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER;
                break;
            // Bastion of Twilight
            // * Halfus Wyrmbreaker
            case 83710:
            case 86169:
            case 86170:
            case 86171: // Furious Roar
                spellInfo->AttributesEx2 |= SPELL_ATTR6_IGNORE_CASTER_AURAS;
                break;
            // * Theralion and Valiona
            case 86622: // Engulfing Magic
            case 95639:
            case 95640:
            case 95641:
                spellInfo->ProcChance = 100;
                break;
            case 86825: // Blackout
            case 92879:
            case 92880:
            case 92881:
                spellInfo->AttributesCu |= SPELL_ATTR0_CU_SHARE_DAMAGE;
                break;
            // Throne of the four Winds
            //  * Conclave of Wind
            case 85422: // Anshal - Nurture (due to some visual bugs)
                spellInfo->Effects[EFFECT_0].ApplyAuraName = SPELL_AURA_PERIODIC_DUMMY;
                break;
            case 84638: // Anshal - Zephyr
                spellInfo->Effects[EFFECT_1].Effect = 0;
                spellInfo->Effects[EFFECT_1].ApplyAuraName = 0;
                break;
            case 86282: // Anshal - Toxic Spores
            case 93120:
            case 93121:
            case 93122:
            case 86111: // Nezir - Ice Patch
                spellInfo->AttributesEx3 |= SPELL_ATTR3_STACK_FOR_DIFF_CASTERS;
                break;
            case 84645: // Nezir - Wind Chill
                spellInfo->Effects[EFFECT_0].RadiusEntry = sSpellRadiusStore.LookupEntry(EFFECT_RADIUS_90_YARDS);
                break;
            case 84644: // Nezir  - Sleet Storm
            case 84643: // Rohash - Hurricane
                spellInfo->Effects[EFFECT_2].Effect = 0;
                spellInfo->Effects[EFFECT_2].ApplyAuraName = 0;
                break;
            case 98982:
            case 100295:
            case 100296:
            case 100297:
                spellInfo->DurationEntry = sSpellDurationStore.LookupEntry(23);
                break;
            case 101423: // Seal of Righteousness
                spellInfo->Effects[0].RadiusEntry = sSpellRadiusStore.LookupEntry(14);   // 8yd
                break;
            // * Al'Akir
            case 88427: // Electrocute
                spellInfo->AttributesEx8 |= SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER;
                break;
            case 88230: // Lightning Strike Visual
            case 88214: // Lightning Strike Cone Damage
            case 93255:
            case 93256:
            case 93257:
                spellInfo->AttributesEx2 |= SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS;
                break;
            // Gilneas
            case 67350: // Summon Josiah
                spellInfo->Effects[0].MiscValue = 0;
                spellInfo->Effects[0].MiscValueB = 0;
                spellInfo->Effects[2].MiscValue = 0;
                spellInfo->Effects[2].MiscValueB = 0;
                break;
            case 67805: // Attack Lurker, remove jumping effect
                spellInfo->Effects[EFFECT_0].Effect = 0;
                break;
            case 67063: // Throw Torch
                spellInfo->Effects[1].BasePoints = 68;
                spellInfo->Effects[2].BasePoints = 18;
                break;
            case 69123: // Curse of the Worgen
                spellInfo->Effects[0].Effect = 0; // Ignore summon effect its done on 68630 spell
                break;
            /*This is because SPELL_EFFECT_TRIGGER_SPELL is now processed before SPELL_EFFECT_INTERRUPT_CAST,
            so spell is silenced before the interruption. */
            case 24259: // Spell Lock silence
                spellInfo->Speed = 80;
                break;
            case 94984: // Dark Simulacrum dummy aura
                spellInfo->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_DUMMY;
                break;
            default:
                break;
        }

        switch (spellInfo->SpellFamilyName)
        {
            case SPELLFAMILY_PALADIN:
            {
                // Seals of the Pure should affect Seal of Righteousness
                if (spellInfo->SpellIconID == 25 && spellInfo->Attributes & SPELL_ATTR0_PASSIVE)
                    spellInfo->Effects[EFFECT_0].SpellClassMask[1] |= 0x20000000;
                break;
            }
            case SPELLFAMILY_DEATHKNIGHT:
            {
                // Icy Touch - extend FamilyFlags (unused value) for Sigil of the Frozen Conscience to use
                if (spellInfo->SpellIconID == 2721 && spellInfo->SpellFamilyFlags[0] & 0x2)
                    spellInfo->SpellFamilyFlags[0] |= 0x40;
                break;
            }
        }
    }

    SummonPropertiesEntry* properties = const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(121));
    properties->Type = SUMMON_TYPE_TOTEM;
    properties = const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(647)); // 52893
    properties->Type = SUMMON_TYPE_TOTEM;

    sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded SpellInfo corrections in %u ms", GetMSTimeDiffToNow(oldMSTime));
}
