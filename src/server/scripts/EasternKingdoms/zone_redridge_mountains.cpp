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

/* Script Data Start
SDName: Redridge Mountains
SD%Complete: 0
SDComment:
Script Data End */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

class npc_rm_keeshan_riverboat : public CreatureScript
{
public:
    npc_rm_keeshan_riverboat() : CreatureScript("npc_rm_keeshan_riverboat")
    {
    }

    enum questId
    {
        QUEST_ITS_NEVER_OVER    = 26616
    };

    enum spellId
    {
        SPELL_SUMMON_KEESHAN_RIVERBOAT  = 81243,
        SPELL_QUEST_DETECTION_5         = 81004
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ITS_NEVER_OVER) == QUEST_STATUS_INCOMPLETE)
        {
            if (player->GetVehicleBase())
                return true;

            if (player->HasAura(SPELL_QUEST_DETECTION_5))
                player->RemoveAurasDueToSpell(SPELL_QUEST_DETECTION_5);
            player->CastSpell(player, SPELL_SUMMON_KEESHAN_RIVERBOAT, true);
        }
        return false;
    }
};

void AddSC_redridge_mountains()
{
    new npc_rm_keeshan_riverboat();
}
