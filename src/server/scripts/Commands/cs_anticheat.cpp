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

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "Language.h"

class anticheat_commandscript : public CommandScript
{
public:
    anticheat_commandscript() : CommandScript("anticheat_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand anticheatCommandTable[] =
        {
            { "jail",           SEC_GAMEMASTER,     true,  &HandleAnticheatJailCommand,            "", NULL },
            { "reports",        SEC_GAMEMASTER,     true,  &HandleAnticheatGetReportsCommand,      "", NULL },
            { NULL,             0,                  false, NULL,                                   "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "anticheat",      SEC_GAMEMASTER,     true,  NULL,                  "", anticheatCommandTable },
            { NULL,             0,                  false, NULL,                                   "", NULL }
        };

        return commandTable;
    }

    static bool HandleAnticheatJailCommand(ChatHandler* handler, const char* args)
    {
        Player* target = nullptr;

        if (char* command = strtok((char*)args, " "))
        {
            std::string strCommand = command;
            normalizePlayerName(strCommand);

            target = sObjectAccessor->FindPlayerByName(strCommand.c_str());
        }
        else
            target = handler->getSelectedPlayer();

        if (!target)
        {
            handler->SendSysMessage(LANG_NO_PLAYERS_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target == handler->GetSession()->GetPlayer())
            return false;

        // teleport both to jail.
        target->TeleportTo(1, 16226.5f, 16403.6f, -64.5f, 3.2f);
        handler->GetSession()->GetPlayer()->TeleportTo(1, 16226.5f, 16403.6f, -64.5f, 3.2f);

        WorldLocation loc;
        loc.m_mapId       = 1;
        loc.m_positionX   = 16226.5f;
        loc.m_positionY   = 16403.6f;
        loc.m_positionZ   = -64.5f;
        target->SetHomebind(loc, 876);
        return true;
    }

    static bool HandleAnticheatGetReportsCommand(ChatHandler* handler, const char* args)
    {
        static uint32 maxEntrys = 50;

        Player* target;
        uint64 targetGuid;
        std::string targetName;

        uint32 parseGUID = MAKE_NEW_GUID(atol((char*)args), 0, HIGHGUID_PLAYER);

        if (sObjectMgr->GetPlayerNameByGUID(parseGUID, targetName))
        {
            target = sObjectMgr->GetPlayerByLowGUID(parseGUID);
            targetGuid = parseGUID;
        }
        else if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ANTICHEAT_LOG_FOR_PLAYER_GUID);
        stmt->setUInt32(0, GUID_LOPART(targetGuid));
        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        handler->PSendSysMessage("Anticheat Report for Player %s.", targetName.c_str());

        uint32 reportCount = 0;
        std::map<uint32, uint32> reportCountPerCategory;

        if (result)
        {
            do
            {
                Field* fields = result->Fetch();

                uint32 const type       = fields[0].GetUInt32();
                uint32 const alarmtime  = fields[1].GetUInt32();
                uint32 const ival       = fields[2].GetUInt32();
                float  const fval       = fields[3].GetFloat();

                ++reportCountPerCategory[type];

                if (++reportCount == maxEntrys)
                {
                    handler->PSendSysMessage("Can only display max %u/%u of the latest entrys.", maxEntrys, result->GetFieldCount());
                    break;
                }
                else if(reportCount < maxEntrys)
                {
                    if (auto const* ac = sObjectMgr->GetAntiCheatConfig(type))
                        handler->PSendSysMessage("[%s] (%s) ival: %u fval: %f", ac->description.c_str(), TimeToTimestampStr(alarmtime).c_str(), ival, fval);
                }
            }
            while (result->NextRow());

            handler->PSendSysMessage("==================");

            for (auto const& reports : reportCountPerCategory)
            {
                if (auto const* ac = sObjectMgr->GetAntiCheatConfig(reports.first))
                    handler->PSendSysMessage("[%s] - %u Reports", ac->description.c_str(), reports.second);
            }
            handler->PSendSysMessage("= %u Reports", reportCount);
            return true;
        }
        else
        {
            handler->PSendSysMessage("No reports for the selected player exists.");
            return true;
        }
    }
};

void AddSC_anticheat_commandscript()
{
    new anticheat_commandscript();
}
