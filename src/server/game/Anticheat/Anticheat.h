/*
 * Copyright (C) 2010 /dev/rsa for MaNGOS <http://getmangos.com/>
 * based on gimly && CWN code
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#ifndef ANTICHEAT_H
#define ANTICHEAT_H
 
#include <string>
#include <sstream>
#include "Common.h"
#include "AnticheatConfig.h"
#include "Opcodes.h"

class Player;
struct MovementInfo;

struct AntiCheatCheckEntry;
struct AntiCheatConfig;

class AntiCheat
{
    public:
        explicit AntiCheat(Player* player);
        ~AntiCheat() {}

        static void DeleteOldLogs();

        // External used for set variables
        void       SetTimeSkipped(uint32 time_skipped) { m_currentTimeSkipped = time_skipped; }
        void       SetInFall(bool isFall) { m_isFall = isFall; }
        bool       isCanFly();
        bool       isInFall();
        bool       isActiveMover() { return m_isActiveMover; }
        void       SetActiveMover(bool isActive) { m_isActiveMover = isActive; }
        bool       isImmune();
        void       SetImmune(uint32 timeDelta);
        void       SetLastLiveState(DeathState state);

        // Checks
        bool CheckNeeded(AntiCheatCheck checktype);

        // Check selectors
        bool DoAntiCheatCheck(AntiCheatCheck checkType, MovementInfo& movementInfo, Opcodes opcode = NULL_OPCODE)
        {
            m_currentmovementInfo = &movementInfo; 
            m_currentOpcode       = opcode;
            return _DoAntiCheatCheck(checkType);
        }

        bool DoAntiCheatCheck(AntiCheatCheck checkType, uint32 spellID, Opcodes opcode = NULL_OPCODE, uint32 damage = 0)
        {
            m_currentspellID = spellID;
            m_currentOpcode  = opcode;
            m_currentDamage  = damage;
            return _DoAntiCheatCheck(checkType);
        }

		bool DoAntiCheatCheck(AntiCheatCheck checkType, Item* item, Item* testitem)
        {
            m_item = item;
            m_testitem = testitem;
            return _DoAntiCheatCheck(checkType);
        }
		
		bool DoAntiCheatCheck(AntiCheatCheck checkType, uint8 wardenType, bool result)
        {
            m_wardenCheck = wardenType;
            m_wardenCheckResult = result;
			m_wardenCheckNum = 0;
            return _DoAntiCheatCheck(checkType);
        }

        bool DoAntiCheatCheck(AntiCheatCheck checkType, uint8 wardenType, uint32 checkNum)
        {
            m_wardenCheck = wardenType;
            m_wardenCheckNum = checkNum;
            m_wardenCheckResult = true;
            return _DoAntiCheatCheck(checkType);
        }

        void DoAntiCheatAction(AntiCheatCheck checkType);

        // Check functions
        bool CheckNull();

        // movement
        bool CheckMovement();
        bool CheckTp2Plane();
        bool CheckFly();
        bool CheckAirJump();
        bool CheckMountain();
        bool CheckWaterWalking();
        bool CheckSpeed();
        bool CheckTeleport();
        bool CheckFall();
		bool CheckZAxis();

        // Transport
        bool CheckOnTransport();

        // quest
        bool CheckQuest();

        // spell
        bool CheckSpell();
        bool CheckSpellValid();
        bool CheckSpellOndeath();
        bool CheckSpellFamily();
        bool CheckSpellInbook();

        // damage
        bool CheckDamage();
        bool CheckSpellDamage();
        bool CheckMeleeDamage();
		
        // Items
        bool CheckItem();
        bool CheckItemUpdate();
		
		// warden
		bool CheckWarden();
        bool CheckWardenKey();
        bool CheckWardenCheckSum();
        bool CheckWardenMemory();
		bool CheckWardenTimeOut();

    private:
        // Internal fuctions
        bool                       CheckTimer(AntiCheatCheck checkType);
        bool                       _DoAntiCheatCheck(AntiCheatCheck checktype);
        AntiCheatCheckEntry*       _FindCheck(AntiCheatCheck checktype);
        AntiCheatConfig const*     _FindConfig(AntiCheatCheck checktype);
        Player*                    GetPlayer() { return m_player;};
        Unit*                      GetMover()  { return m_currentMover;};

        // Saved variables
        float                                   m_MovedLen;          //Length of traveled way
        uint32                                  m_immuneTime;
        bool                                    m_isFall;
        bool                                    m_isTeleported;
        bool                                    m_isActiveMover;
        uint32                                  m_lastfalltime;
        uint32                                  m_lastClientTime;
        DeathState                              m_lastLiveState;
        float                                   m_lastfallz;
        Player*                                 m_player;
        std::map<AntiCheatCheck, uint32>        m_counters;               // counter of alarms
        std::map<AntiCheatCheck, uint32>        m_oldCheckTime;           // last time when check processed
        std::map<AntiCheatCheck, uint32>        m_lastalarmtime;          // last time when alarm generated
        std::map<AntiCheatCheck, uint32>        m_lastactiontime;         // last time when action is called

        // Variables for current check
        Unit*                      m_currentMover;
        MovementInfo*              m_currentmovementInfo;
        uint32                     m_currentDamage;
        uint32                     m_currentspellID;
        Opcodes                    m_currentOpcode;
        uint32                     m_currentTimeSkipped;
        struct CheaterData
        {
            CheaterData() : intvalue(0), floatvalue(0) {}
            CheaterData(uint32 _intvalue) : intvalue(_intvalue), floatvalue(0) {}
            CheaterData(float _floatvalue) : intvalue(0), floatvalue(_floatvalue) {}
            CheaterData(uint32 _intvalue, float _floatvalue) : intvalue(_intvalue), floatvalue(_floatvalue) {}

            uint32 intvalue;
            float  floatvalue;
        };

        CheaterData                m_currentCheaterData;
        AntiCheatConfig const*     m_currentConfig;
        float                      m_currentDelta;
        float                      m_currentDeltaZ;
		Item*                      m_item;
        Item*                      m_testitem;
		uint8                      m_wardenCheck;
        bool                       m_wardenCheckResult;
		uint32                     m_wardenCheckNum;
};

struct AntiCheatCheckEntry
{
    public:
        bool           active;
        AntiCheatCheck checkType;
        bool           (AntiCheat::*Handler)();
};

#endif
