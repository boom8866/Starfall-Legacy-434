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

#include "LFGMgr.h"
#include "ObjectMgr.h"
#include "Group.h"
#include "Player.h"
#include "Opcodes.h"
#include "WorldPacket.h"
#include "WorldSession.h"

void BuildPlayerLockDungeonBlock(WorldPacket& data, lfg::LfgLockMap const& lock)
{
    data << uint32(lock.size());                           // Size of lock dungeons
    for (lfg::LfgLockMap::const_iterator it = lock.begin(); it != lock.end(); ++it)
    {
        data << uint32(it->first);                         // Dungeon entry (id + type)
        data << uint32(it->second.locktyp);                // Lock status
        data << uint32(it->second.neededItemlevel);        // needed ILvL
        data << uint32(it->second.averageItemlevel);       // player ILvL
    }
}

void BuildPartyLockDungeonBlock(WorldPacket& data, lfg::LfgLockPartyMap const& lockMap)
{
    data << uint8(lockMap.size());
    for (lfg::LfgLockPartyMap::const_iterator it = lockMap.begin(); it != lockMap.end(); ++it)
    {
        data << uint64(it->first);                         // Player guid
        BuildPlayerLockDungeonBlock(data, it->second);
    }
}

void WorldSession::HandleLfgJoinOpcode(WorldPacket& recvData)
{
    if (!sLFGMgr->isOptionEnabled(lfg::LFG_OPTION_ENABLE_DUNGEON_FINDER | lfg::LFG_OPTION_ENABLE_RAID_BROWSER) ||
        (GetPlayer()->GetGroup() && GetPlayer()->GetGroup()->GetLeaderGUID() != GetPlayer()->GetGUID() &&
        (GetPlayer()->GetGroup()->GetMembersCount() == MAXGROUPSIZE || !GetPlayer()->GetGroup()->isLFGGroup())))
    {
        recvData.rfinish();
        return;
    }

    uint32 dungeon;
    uint32 roles;
    uint32 unk;
    std::string comment;

    recvData >> roles;

    for (int8 i = 0; i < 3; ++i)
    {
        recvData >> unk; // Unknown.
    }

    uint32 length = recvData.ReadBits(9);
    uint32 count  = recvData.ReadBits(24);

    comment = recvData.ReadString(length);

    if (!count) // numDungeons.
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_JOIN [" UI64FMTD "] no dungeons selected", GetPlayer()->GetGUID());
        recvData.rfinish();
        return;
    }

    lfg::LfgDungeonSet newDungeons; // numfields
    for (uint32 i = 0; i < count; ++i)
    {
        recvData >> dungeon; // dungeonentry
        newDungeons.insert((dungeon & 0x00FFFFFF));       // remove the type from the dungeon entry
    }

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_JOIN [" UI64FMTD "] roles: %u, Dungeons: %u, Comment: %s", GetPlayer()->GetGUID(), roles, uint8(newDungeons.size()), comment.c_str());

    sLFGMgr->JoinLfg(GetPlayer(), uint8(roles), newDungeons, comment);
}

void WorldSession::HandleLfgLeaveOpcode(WorldPacket&  recvData)
{
    Group* grp = GetPlayer()->GetGroup();
    Group* group = GetPlayer()->GetGroup();
    uint64 guid = GetPlayer()->GetGUID();
    uint64 gguid = grp ? grp->GetGUID() : guid;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_LEAVE [" UI64FMTD "] in group: %u", GetPlayer()->GetGUID(), grp ? 1 : 0);

    uint32 roles, time, reason, instanceid;

    recvData >> roles;
    recvData >> time;
    recvData >> reason;
    recvData >> instanceid;

    recvData.rfinish();

    // Check cheating - only leader can leave the queue
    if (!grp || grp->GetLeaderGUID() == GetPlayer()->GetGUID())

        sLFGMgr->LeaveLfg(GetPlayer()->GetGUID());
}

void WorldSession::HandleLfgProposalResultOpcode(WorldPacket& recvData)
{
    ObjectGuid guid;          // Instance guid.
    ObjectGuid guid2;         // Player guid

    uint32 lfgGroupID;        // Internal lfgGroupID
    uint32 time;
    uint32 roles;
    uint8 accept;             // Accept to join? is actually a bool.
    uint32 unk;               // Unknown

    recvData >> lfgGroupID;
    recvData >> time;
    recvData >> roles;
    recvData >> unk;

    // Player guid
    guid2[4] = recvData.ReadBit();
    guid2[5] = recvData.ReadBit();
    guid2[0] = recvData.ReadBit();
    guid2[6] = recvData.ReadBit();
    guid2[2] = recvData.ReadBit();
    guid2[7] = recvData.ReadBit();
    guid2[1] = recvData.ReadBit();
    guid2[3] = recvData.ReadBit();

    recvData.ReadByteSeq(guid2[7]);
    recvData.ReadByteSeq(guid2[4]);
    recvData.ReadByteSeq(guid2[3]);
    recvData.ReadByteSeq(guid2[2]);
    recvData.ReadByteSeq(guid2[6]);
    recvData.ReadByteSeq(guid2[0]);
    recvData.ReadByteSeq(guid2[1]);
    recvData.ReadByteSeq(guid2[5]);

    // Instance guid - var guid = new byte[8]; ? vector?
    guid[7] = recvData.ReadBit();
    recvData >> accept;
    guid[1] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[2]);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_PROPOSAL_RESULT [" UI64FMTD "] proposal: %u accept: %u", GetPlayer()->GetGUID(), lfgGroupID, accept ? 1 : 0);
    sLFGMgr->UpdateProposal(lfgGroupID, GetPlayer()->GetGUID(), accept);
}

void WorldSession::HandleLfgSetRolesOpcode(WorldPacket& recvData)
{
    uint8 roles;
    recvData >> roles;                                     // Player Group Roles
    uint64 guid = GetPlayer()->GetGUID();
    Group* group = GetPlayer()->GetGroup();
    if (!group)
    {
        sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_SET_ROLES %s Not in group",
            GetPlayerInfo().c_str());
        return;
    }
    uint64 gguid = group->GetGUID();
    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_SET_ROLES: Group %u, Player %s, Roles: %u",
        GUID_LOPART(gguid), GetPlayerInfo().c_str(), roles);
    sLFGMgr->UpdateRoleCheck(gguid, guid, roles);
}

void WorldSession::HandleLfgSetCommentOpcode(WorldPacket&  recvData)
{
    std::string comment;
    recvData >> comment;

    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_SET_COMMENT %s comment: %s",
        GetPlayerInfo().c_str(), comment.c_str());

    sLFGMgr->SetComment(GetPlayer()->GetGUID(), comment);
}

void WorldSession::HandleLfgSetBootVoteOpcode(WorldPacket& recvData)
{
    bool agree;                                            // Agree to kick player
    recvData >> agree;

    uint64 guid = GetPlayer()->GetGUID();
    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_SET_BOOT_VOTE %s agree: %u",
        GetPlayerInfo().c_str(), agree ? 1 : 0);
    sLFGMgr->UpdateBoot(guid, agree);
}

void WorldSession::HandleLfgTeleportOpcode(WorldPacket& recvData)
{
    bool out;
    recvData >> out;

    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_TELEPORT %s out: %u",
        GetPlayerInfo().c_str(), out ? 1 : 0);
    sLFGMgr->TeleportPlayer(GetPlayer(), out, true);
}

void WorldSession::HandleLfgPlayerLockInfoRequestOpcode(WorldPacket& recvData)
{
    uint64 guid = GetPlayer()->GetGUID();
    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_PLAYER_LOCK_INFO_REQUEST %s",
        GetPlayerInfo().c_str());

    // Get Random dungeons that can be done at a certain level and expansion
    uint8 level = GetPlayer()->getLevel();
    lfg::LfgDungeonSet const& randomDungeons =
        sLFGMgr->GetRandomAndSeasonalDungeons(level, GetPlayer()->GetSession()->Expansion());

    // Get player locked Dungeons
    lfg::LfgLockMap const& lock = sLFGMgr->GetLockedDungeons(guid);
    uint32 rsize = uint32(randomDungeons.size());
    uint32 lsize = uint32(lock.size());

    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_PLAYER_INFO %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_PLAYER_INFO, 1 + rsize * (4 + 1 + 4 + 4 + 4 + 4 + 1 + 4 + 4 + 4) + 4 + lsize * (1 + 4 + 4 + 4 + 4 + 1 + 4 + 4 + 4));

    data << uint8(randomDungeons.size());                  // Random Dungeon count
    for (lfg::LfgDungeonSet::const_iterator it = randomDungeons.begin(); it != randomDungeons.end(); ++it)
    {
        data << uint32(*it);                               // Dungeon Entry (id + type)
        lfg::LfgReward const* reward = sLFGMgr->GetRandomDungeonReward(*it, level);
        Quest const* quest = NULL;
        bool done = false;
        if (reward)
        {
            quest = sObjectMgr->GetQuestTemplate(reward->firstQuest);
            if (quest)
            {
                done = !GetPlayer()->CanRewardQuest(quest, false);
                if (done)
                    quest = sObjectMgr->GetQuestTemplate(reward->otherQuest);
            }
        }

        if (quest)
        {
            data << uint8(done);
            data << uint32(quest->RewardCurrencyCount[0] * LFG_MULTYPLIER);
            data << uint32(quest->XPValue(GetPlayer()));
            data << uint32(0);
            data << uint32(0);
            data << uint8(quest->GetRewItemsCount());
            if (quest->GetRewItemsCount())
            {
                for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
                    if (uint32 itemId = quest->RewardItemId[i])
                    {
                        ItemTemplate const* item = sObjectMgr->GetItemTemplate(itemId);
                        data << uint32(itemId);
                        data << uint32(item ? item->DisplayInfoID : 0);
                        data << uint32(quest->RewardItemIdCount[i]);
                    }
            }
        }
        else
        {
            data << uint8(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint8(0);
        }
    }
    BuildPlayerLockDungeonBlock(data, lock);
    SendPacket(&data);
}

void WorldSession::HandleLfgPartyLockInfoRequestOpcode(WorldPacket&  recvData)
{
    uint64 guid = GetPlayer()->GetGUID();
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFD_PARTY_LOCK_INFO_REQUEST [" UI64FMTD "]", guid);

    Group* group = GetPlayer()->GetGroup();
    if (!group)
        return;

    // Get the locked dungeons of the other party members
    lfg::LfgLockPartyMap lockMap;
    for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* plrg = itr->getSource();
        if (!plrg)
            continue;

        uint64 pguid = plrg->GetGUID();
        if (pguid == guid)
            continue;

        lockMap[pguid] = sLFGMgr->GetLockedDungeons(pguid);
    }

    uint32 size = 0;
    for (lfg::LfgLockPartyMap::const_iterator it = lockMap.begin(); it != lockMap.end(); ++it)
        size += 8 + 4 + uint32(it->second.size()) * (4 + 4 + 4 + 4);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_PARTY_INFO [" UI64FMTD "]", guid);
    WorldPacket data(SMSG_LFG_PARTY_INFO, 1 + size);
    BuildPartyLockDungeonBlock(data, lockMap);
    SendPacket(&data);
}

void WorldSession::HandleLfrJoinOpcode(WorldPacket& recvData)
{
    uint32 entry;                                          // Raid id to search
    recvData >> entry;
    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_LFR_JOIN %s dungeon entry: %u",
        GetPlayerInfo().c_str(), entry);
    //SendLfrUpdateListOpcode(entry);
}

void WorldSession::HandleLfrLeaveOpcode(WorldPacket& recvData)
{
    uint32 dungeonId;                                      // Raid id queue to leave
    recvData >> dungeonId;
    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_LFR_LEAVE %s dungeonId: %u",
        GetPlayerInfo().c_str(), dungeonId);
    //sLFGMgr->LeaveLfr(GetPlayer(), dungeonId);
}

void WorldSession::HandleLfgGetStatus(WorldPacket& /*recvData*/)
{
    sLog->outDebug(LOG_FILTER_LFG, "CMSG_LFG_GET_STATUS %s", GetPlayerInfo().c_str());

    uint64 guid = GetPlayer()->GetGUID();
    lfg::LfgUpdateData updateData = sLFGMgr->GetLfgStatus(guid);

    SendLfgUpdateStatus(updateData,GetPlayer()->GetGroup() ? 1 : 0);
}

void WorldSession::SendLfgUpdateStatus(const lfg::LfgUpdateData& updateData, bool isParty)
{
    sLog->outDebug(LOG_FILTER_LFG, "Send SendLfgUpdateStatus");
    bool queued = false;
    bool joined = false;
    bool LFGJoined = false;
    bool UnkBit = false;
    uint8 UnkByte64 = 15; //RESEARCH

    switch (updateData.updateType)
    {
       /* case LFG_UPDATETYPE_JOIN_PROPOSAL:
            joined = true;
            if(!isParty)
            queued = true;
            break;
        case LFG_UPDATETYPE_CLEAR_LOCK_LIST:
            // join = true;  // TODO: Sometimes queued and extrainfo - Check ocurrences...
            queued = true;
            break;*/
        case lfg::LFG_UPDATETYPE_PROPOSAL_BEGIN: 
            joined = true;
            if(isParty)
                LFGJoined = true;
            break;
        case lfg::LFG_UPDATETYPE_ADDED_TO_QUEUE:
            joined = true;
            queued = true;
            if(isParty)
                LFGJoined = true;
            break;
        case lfg::LFG_UPDATETYPE_GROUP_FOUND:
            UnkBit = true;
            break;
        default:
            break;
    }

    uint8 size = uint8(updateData.dungeons.size());

    //LFGQueue& queue = GetQueue(GetPlayer()->GetGUID());

    ObjectGuid guid = GetPlayer()->GetGUID();
    // sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_UPDATE_STATUS [" UI64FMTD "] updatetype: %u", guid, updateData.updateType);

    WorldPacket data(SMSG_LFG_UPDATE_STATUS);

    data.WriteBit(guid[1]);
    data.WriteBit(UnkBit);        //UnkBit 65 TODO

    data.WriteBits(size,24); //Dungeon Count 
    
    data.WriteBit(guid[6]);
    data.WriteBit(joined);        //Joined TODO
    data.WriteBits(updateData.comment.length(),9);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[2]);
    data.WriteBit(LFGJoined);          //LFG Joined TODO
    data.WriteBit(guid[0]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[5]);
    data.WriteBit(queued);     //Queded
    data.FlushBits();

    data << uint8(UnkByte64);         //Unk Byte 64 TODO
    data.WriteString(updateData.comment);
    data << uint32(GetPlayer()->GetTeam());      //Queue Id TODO
    data << uint32(time(NULL));      //Join Date
   
    data.WriteByteSeq(guid[6]);

    for(int i = 0; i < 3;++i)
        data << uint8(0);



    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[0]);

    data << int32(3);           // Same value than "Unk_UInt32_1" in SMSG_LFG_JOIN_RESULT - Only seen 3

    data.WriteByteSeq(guid[7]);

    for (lfg::LfgDungeonSet::const_iterator it = updateData.dungeons.begin(); it != updateData.dungeons.end(); ++it)
    {
        LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(*it);
            
        sLog->outInfo(LOG_FILTER_SERVER_LOADING,"Dungeon : %u",*it);

        data << uint32(dungeon->Entry());

    }

    SendPacket(&data);   
}

void WorldSession::SendLfgRoleChosen(uint64 guid, uint8 roles)
{
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_ROLE_CHOSEN %s guid: %u roles: %u",
        GetPlayerInfo().c_str(), GUID_LOPART(guid), roles);

    WorldPacket data(SMSG_LFG_ROLE_CHOSEN, 8 + 1 + 4);
    data << uint64(guid);                                  // Guid
    data << uint8(roles > 0);                              // Ready
    data << uint32(roles);                                 // Roles
    SendPacket(&data);
}

void WorldSession::SendLfgRoleCheckUpdate(lfg::LfgRoleCheck const& roleCheck)
{
    lfg::LfgDungeonSet dungeons;
    if (roleCheck.rDungeonId)
        dungeons.insert(roleCheck.rDungeonId);
    else
        dungeons = roleCheck.dungeons;

    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_ROLE_CHECK_UPDATE %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_ROLE_CHECK_UPDATE, 4 + 1 + 1 + dungeons.size() * 4 + 1 + roleCheck.roles.size() * (8 + 1 + 4 + 1));

    data << uint32(roleCheck.state);                       // Check result
    data << uint8(roleCheck.state == lfg::LFG_ROLECHECK_INITIALITING);
    data << uint8(dungeons.size());                        // Number of dungeons
    if (!dungeons.empty())
        for (lfg::LfgDungeonSet::iterator it = dungeons.begin(); it != dungeons.end(); ++it)
            data << uint32(sLFGMgr->GetLFGDungeonEntry(*it)); // Dungeon

    data << uint8(roleCheck.roles.size());                 // Players in group
    if (!roleCheck.roles.empty())
    {
        // Leader info MUST be sent 1st :S
        uint64 guid = roleCheck.leader;
        uint8 roles = roleCheck.roles.find(guid)->second;
        data << uint64(guid);                              // Guid
        data << uint8(roles > 0);                          // Ready
        data << uint32(roles);                             // Roles
        Player* player = ObjectAccessor::FindPlayer(guid);
        data << uint8(player ? player->getLevel() : 0);    // Level

        for (lfg::LfgRolesMap::const_iterator it = roleCheck.roles.begin(); it != roleCheck.roles.end(); ++it)
        {
            if (it->first == roleCheck.leader)
                continue;

            guid = it->first;
            roles = it->second;
            data << uint64(guid);                          // Guid
            data << uint8(roles > 0);                      // Ready
            data << uint32(roles);                         // Roles
            player = ObjectAccessor::FindPlayer(guid);
            data << uint8(player ? player->getLevel() : 0);// Level
        }
    }
    SendPacket(&data);
}

void WorldSession::SendLfgJoinResult(lfg::LfgJoinResultData const& joinData)
{
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_JOIN_RESULT %s checkResult: %u checkValue: %u",
        GetPlayerInfo().c_str(), joinData.result, joinData.state);

    WorldPacket data(SMSG_LFG_JOIN_RESULT);
    data << uint32(3);                                      // used in SMSG_LFG_UPDATE_STATUS and SMSG_LFG_QUEUE_STATUS
    data << uint8(joinData.result);                       // Check Result
    data << uint32(GetPlayer()->GetTeam());               // queue ID
    data << uint8(joinData.state);                        // Check Value
    data << uint32(time(NULL));                             //joindate

    ObjectGuid guid = GetPlayer()->GetGUID();

    data.WriteBit(guid[2]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[0]);

    uint8 count = joinData.lockmap.size();

    data.WriteBits(count,24);

    for (lfg::LfgLockPartyMap::const_iterator it = joinData.lockmap.begin(); it != joinData.lockmap.end(); ++it)
    {
        ObjectGuid gguid = it->first;                         // Player guid

        data.WriteBit(gguid[7]);
        data.WriteBit(gguid[5]);
        data.WriteBit(gguid[3]);
        data.WriteBit(gguid[6]);
        data.WriteBit(gguid[0]);
        data.WriteBit(gguid[2]);
        data.WriteBit(gguid[4]);
        data.WriteBit(gguid[1]);

        data.WriteBits(it->second.size(),22);
    }

    data.WriteBit(guid[4]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[6]);

    for (lfg::LfgLockPartyMap::const_iterator it = joinData.lockmap.begin(); it != joinData.lockmap.end(); ++it)
    {
        ObjectGuid gguid = it->first;                         // Player guid

        for (lfg::LfgLockMap::const_iterator its = it->second.begin(); its != it->second.end(); ++its)
        {
            data << uint32(its->first);                         // Dungeon entry (id + type)
            data << uint32(its->second.locktyp);                // Lock status
            data << uint32(its->second.neededItemlevel);        // needed ILvL
            data << uint32(its->second.averageItemlevel);       // player ILvL
        }

        data.WriteByteSeq(gguid[2]);
        data.WriteByteSeq(gguid[5]);
        data.WriteByteSeq(gguid[1]);
        data.WriteByteSeq(gguid[0]);
        data.WriteByteSeq(gguid[4]);
        data.WriteByteSeq(gguid[3]);
        data.WriteByteSeq(gguid[6]);
        data.WriteByteSeq(gguid[7]);

        data.WriteBits(it->second.size(),22);
    }

    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[6]);
    
    /*if (!joinData.lockmap.empty())
        BuildPartyLockDungeonBlock(data, joinData.lockmap);*/

    SendPacket(&data);
}

void WorldSession::SendLfgQueueStatus(lfg::LfgQueueStatusData const& queueData)
{
    ObjectGuid guid = GetPlayer()->GetGUID();        
    
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_QUEUE_STATUS %s dungeon: %u, waitTime: %d, "
        "avgWaitTime: %d, waitTimeTanks: %d, waitTimeHealer: %d, waitTimeDps: %d, "
        "queuedTime: %u, tanks: %u, healers: %u, dps: %u",
        GetPlayerInfo().c_str(), queueData.dungeonId, queueData.waitTime, queueData.waitTimeAvg,
        queueData.waitTimeTank, queueData.waitTimeHealer, queueData.waitTimeDps,
        queueData.queuedTime, queueData.tanks, queueData.healers, queueData.dps);

    WorldPacket data(SMSG_LFG_QUEUE_STATUS);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[0]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[4]);

    data.FlushBits();

    data.WriteByteSeq(guid[0]);
    
    data << uint8(queueData.tanks);                        // Tanks needed
    data << int32(-1);                                    // Wait Tanks
    data << uint8(queueData.healers);                      // Healers needed
    data << int32(-1);                                    // Wait Healers
    data << uint8(queueData.dps);                          // Dps needed
    data << int32(-1);                                    // Wait Dps
    
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[6]);

    data << int32(queueData.waitTimeAvg);                                     // Average Wait time
    data << int32(queueData.jointime);                     // JoinTime
    data << int32(queueData.dungeonId);                   // Dungeon
    data << int32(queueData.queuedTime);                  // Player wait time in queue

    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[3]);

    data << int32(queueData.queueID);

    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[2]);

    data << int32(-1); //Wait Time
    data << int32(3); //Wait Time  

    sLog->outInfo(LOG_FILTER_SERVER_LOADING,"%u",data.GetOpcode());

    SendPacket(&data);
}

void WorldSession::SendLfgBootProposalUpdate(lfg::LfgPlayerBoot const& boot)
{
    uint64 guid = GetPlayer()->GetGUID();
    lfg::LfgAnswer playerVote = boot.votes.find(guid)->second;
    uint8 votesNum = 0;
    uint8 agreeNum = 0;
    uint32 secsleft = uint8((boot.cancelTime - time(NULL)) / 1000);
    for (lfg::LfgAnswerContainer::const_iterator it = boot.votes.begin(); it != boot.votes.end(); ++it)
    {
        if (it->second != lfg::LFG_ANSWER_PENDING)
        {
            ++votesNum;
            if (it->second == lfg::LFG_ANSWER_AGREE)
                ++agreeNum;
        }
    }
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_BOOT_PROPOSAL_UPDATE %s inProgress: %u - "
        "didVote: %u - agree: %u - victim: %u votes: %u - agrees: %u - left: %u - "
        "needed: %u - reason %s",
        GetPlayerInfo().c_str(), uint8(boot.inProgress), uint8(playerVote != lfg::LFG_ANSWER_PENDING),
        uint8(playerVote == lfg::LFG_ANSWER_AGREE), GUID_LOPART(boot.victim), votesNum, agreeNum,
        secsleft, lfg::LFG_GROUP_KICK_VOTES_NEEDED, boot.reason.c_str());
    WorldPacket data(SMSG_LFG_BOOT_PROPOSAL_UPDATE, 1 + 1 + 1 + 1 + 8 + 4 + 4 + 4 + 4 + boot.reason.length());
    data << uint8(boot.inProgress);                        // Vote in progress
    data << uint8(playerVote != lfg::LFG_ANSWER_PENDING);       // Did Vote
    data << uint8(playerVote == lfg::LFG_ANSWER_AGREE);         // Agree
    data << uint8(0);                                      // Unknown 4.2.2
    data << uint64(boot.victim);                           // Victim GUID
    data << uint32(votesNum);                              // Total Votes
    data << uint32(agreeNum);                              // Agree Count
    data << uint32(secsleft);                              // Time Left
    data << uint32(lfg::LFG_GROUP_KICK_VOTES_NEEDED);      // Needed Votes
    data << boot.reason.c_str();                           // Kick reason
    SendPacket(&data);
}

void WorldSession::SendLfgUpdateProposal(lfg::LfgProposal const& proposal)
{
    uint64 guid = GetPlayer()->GetGUID();
    uint64 gguid = proposal.players.find(guid)->second.group;
    bool silent = !proposal.isNew && gguid == proposal.group;
    uint32 dungeonEntry = proposal.dungeonId;

    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_PROPOSAL_UPDATE %s state: %u",
        GetPlayerInfo().c_str(), proposal.state);

    // show random dungeon if player selected random dungeon and it's not lfg group
    if (!silent)
    {
        lfg::LfgDungeonSet const& playerDungeons = sLFGMgr->GetSelectedDungeons(guid);
        if (playerDungeons.find(proposal.dungeonId) == playerDungeons.end())
            dungeonEntry = (*playerDungeons.begin());
    }

    dungeonEntry = sLFGMgr->GetLFGDungeonEntry(dungeonEntry);

    WorldPacket data(SMSG_LFG_PROPOSAL_UPDATE, 4 + 1 + 4 + 4 + 1 + 1 + proposal.players.size() * (4 + 1 + 1 + 1 + 1 +1));
    data << uint32(dungeonEntry);                          // Dungeon
    data << uint8(proposal.state);                         // Proposal state
    data << uint32(proposal.id);                           // Proposal ID
    data << uint32(proposal.encounters);                   // encounters done
    data << uint8(silent);                                 // Show proposal window
    data << uint8(proposal.players.size());                // Group size

    for (lfg::LfgProposalPlayerContainer::const_iterator it = proposal.players.begin(); it != proposal.players.end(); ++it)
    {
        lfg::LfgProposalPlayer const& player = it->second;
        data << uint32(player.role);                       // Role
        data << uint8(it->first == guid);                  // Self player
        if (!player.group)                                 // Player not it a group
        {
            data << uint8(0);                              // Not in dungeon
            data << uint8(0);                              // Not same group
        }
        else
        {
            data << uint8(player.group == proposal.group); // In dungeon (silent)
            data << uint8(player.group == gguid);          // Same Group than player
        }
        data << uint8(player.accept != lfg::LFG_ANSWER_PENDING);// Answered
        data << uint8(player.accept == lfg::LFG_ANSWER_AGREE);  // Accepted
    }
    SendPacket(&data);
}

void WorldSession::SendLfgLfrList(bool update)
{
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_LFR_LIST %s update: %u",
        GetPlayerInfo().c_str(), update ? 1 : 0);
    WorldPacket data(SMSG_LFG_UPDATE_SEARCH, 1);
    data << uint8(update);                                 // In Lfg Queue?
    SendPacket(&data);
}

void WorldSession::SendLfgDisabled()
{
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_DISABLED %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_DISABLED, 0);
    SendPacket(&data);
}

void WorldSession::SendLfgOfferContinue(uint32 dungeonEntry)
{
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_OFFER_CONTINUE %s dungeon entry: %u",
        GetPlayerInfo().c_str(), dungeonEntry);
    WorldPacket data(SMSG_LFG_OFFER_CONTINUE, 4);
    data << uint32(dungeonEntry);
    SendPacket(&data);
}

void WorldSession::SendLfgTeleportError(uint8 err)
{
    sLog->outDebug(LOG_FILTER_LFG, "SMSG_LFG_TELEPORT_DENIED %s reason: %u",
        GetPlayerInfo().c_str(), err);
    WorldPacket data(SMSG_LFG_TELEPORT_DENIED, 4);
    data << uint32(err);                                   // Error
    SendPacket(&data);
}

/*
void WorldSession::SendLfrUpdateListOpcode(uint32 dungeonEntry)
{
    sLog->outDebug(LOG_FILTER_PACKETIO, "SMSG_LFG_UPDATE_LIST %s dungeon entry: %u",
        GetPlayerInfo().c_str(), dungeonEntry);
    WorldPacket data(SMSG_LFG_UPDATE_LIST);
    SendPacket(&data);
}
*/

void WorldSession::HandleDungeonFinderGetSystemInfo(WorldPacket& recvData)
{
    bool unk1 = recvData.ReadBit();
    recvData.hexlike();
}
