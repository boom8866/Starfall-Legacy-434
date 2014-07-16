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

#ifndef BATTLEFIELD_MGR_H_
#define BATTLEFIELD_MGR_H_

#include "Battlefield.h"
#include <ace/Singleton.h>

class Player;
class GameObject;
class Creature;
class ZoneScript;
struct GossipMenuItems;

class BattlefieldQueue
{
    public:
        friend class Battlefield;

        BattlefieldQueue(uint8 battleId) { _queueId = (521142272 ^ battleId); }
        uint64 GetId() { return _queueId; }
        bool HasEnoughSpace() { return _inQueue.size() <= 120 ? true : false ; }
        void AddPlayerToQueue(Player * plr) { _inQueue.push_back(plr); }
        void RemovePlayerFromQueue(Player * plr) { _inQueue.remove(plr); }

        typedef std::list < Player * > PlayerQueue;

    private:
        PlayerQueue     _inQueue;
        uint64          _queueId;
};

// class to handle player enter / leave / areatrigger / GO use events
class BattlefieldMgr
{
    public:
        // ctor
        BattlefieldMgr();
        // dtor
        ~BattlefieldMgr();

        // create battlefield events
        void InitBattlefield();

        // called when a player enters an battlefield area
        void HandlePlayerEnterZone(Player* player, uint32 zoneId);
        // called when player leaves an battlefield area
        void HandlePlayerLeaveZone(Player* player, uint32 zoneId);
        // called when player resurrects
        void HandlePlayerResurrects(Player* player, uint32 zoneId);

        // return assigned battlefield
        Battlefield* GetBattlefieldToZoneId(uint32 zoneId);
        Battlefield* GetBattlefieldByBattleId(uint32 battleId);
        Battlefield* GetBattlefieldByGUID(uint64 guid);

        ZoneScript* GetZoneScript(uint32 zoneId);

        void AddZone(uint32 zoneId, Battlefield* bf);

        void Update(uint32 diff);

        BattlefieldQueue* GetQueueForBattlefield(uint64 guid) { return _queueMap[guid]; }

        void HandleGossipOption(Player * player, uint64 guid, uint32 gossipid);

        bool CanTalkTo(Player * player, Creature * creature, GossipMenuItems gso);

        void HandleDropFlag(Player * player, uint32 spellId);
    private:
        typedef std::vector<Battlefield*> BattlefieldSet;
        typedef std::map<uint32 /*zoneId*/, Battlefield*> BattlefieldMap;
        typedef std::map < uint64, BattlefieldQueue* > BattlefieldQueueMap;
        // contains all initiated battlefield events
        // used when initing / cleaning up
        BattlefieldSet _battlefieldSet;
        // maps the zone ids to an battlefield event
        // used in player event handling
        BattlefieldMap _battlefieldMap;
        // A holder for the queue objects
        BattlefieldQueueMap _queueMap;
        // update interval
        uint32 _updateTimer;
};

#define sBattlefieldMgr ACE_Singleton<BattlefieldMgr, ACE_Null_Mutex>::instance()

#endif
