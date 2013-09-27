 /*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Silverpine_Forest
SD%Complete: 100
SDComment: Quest support: 435
SDCategory: Silverpine Forest
EndScriptData */

/* ContentData
npc_deathstalker_erland
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

/*######
## npc_deathstalker_erland
######*/

enum eErland
{
    SAY_QUESTACCEPT     = 0,
    SAY_START           = 1,
    SAY_AGGRO           = 2,
    SAY_PROGRESS        = 3,
    SAY_LAST            = 4,

    SAY_RANE            = 0,
    SAY_RANE_ANSWER     = 5,
    SAY_MOVE_QUINN      = 6,

    SAY_QUINN           = 7,
    SAY_QUINN_ANSWER    = 0,
    SAY_BYE             = 8,

    QUEST_ESCORTING     = 435,
    NPC_RANE            = 1950,
    NPC_QUINN           = 1951
};

class npc_deathstalker_erland : public CreatureScript
{
public:
    npc_deathstalker_erland() : CreatureScript("npc_deathstalker_erland") { }

    struct npc_deathstalker_erlandAI : public npc_escortAI
    {
        npc_deathstalker_erlandAI(Creature* creature) : npc_escortAI(creature) {}

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 1:
                    Talk(SAY_START, player->GetGUID());
                    break;
                case 10:
                    Talk(SAY_PROGRESS);
                    break;
                case 13:
                    Talk(SAY_LAST, player->GetGUID());
                    player->GroupEventHappens(QUEST_ESCORTING, me);
                    break;
                case 15:
                    if (Creature* rane = me->FindNearestCreature(NPC_RANE, 20.0f))
                        rane->AI()->Talk(SAY_RANE);
                    break;
                case 16:
                    Talk(SAY_RANE_ANSWER);
                    break;
                case 17:
                    Talk(SAY_MOVE_QUINN);
                    break;
                case 24:
                    Talk(SAY_QUINN);
                    break;
                case 25:
                    if (Creature* quinn = me->FindNearestCreature(NPC_QUINN, 20.0f))
                        quinn->AI()->Talk(SAY_QUINN_ANSWER);
                    break;
                case 26:
                    Talk(SAY_BYE);
                    break;
            }
        }

        void Reset() {}

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO, who->GetGUID());
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ESCORTING)
        {
            creature->AI()->Talk(SAY_QUESTACCEPT, player->GetGUID());

            if (npc_escortAI* pEscortAI = CAST_AI(npc_deathstalker_erland::npc_deathstalker_erlandAI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_deathstalker_erlandAI(creature);
    }
};

class npc_hillsbrad_worgens_trigger : public CreatureScript
{
public:
    npc_hillsbrad_worgens_trigger() : CreatureScript("npc_hillsbrad_worgens_trigger") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hillsbrad_worgens_triggerAI (creature);
    }

    enum Id
    {
        NPC_HILLSBRAD_WORGEN            = 45270
    };

    struct npc_hillsbrad_worgens_triggerAI : public ScriptedAI
    {
        npc_hillsbrad_worgens_triggerAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            spawnTimer = 1000;
        }

        void UpdateAI(uint32 diff)
        {
            if (UpdateVictim())
                return;

            if (spawnTimer <= diff)
            {
                me->SummonCreature(NPC_HILLSBRAD_WORGEN, 764.92f, 741.44f, 30.20f, 1.71f);
                me->SummonCreature(NPC_HILLSBRAD_WORGEN, 784.86f, 743.01f, 30.20f, 1.89f);
                me->SummonCreature(NPC_HILLSBRAD_WORGEN, 753.68f, 740.22f, 30.20f, 1.61f);
                me->SummonCreature(NPC_HILLSBRAD_WORGEN, 699.38f, 726.81f, 31.42f, 1.75f);
                me->SummonCreature(NPC_HILLSBRAD_WORGEN, 689.53f, 725.01f, 31.42f, 1.75f);
                me->SummonCreature(NPC_HILLSBRAD_WORGEN, 680.68f, 722.73f, 31.42f, 1.62f);
                spawnTimer = 6000;
            }
            else
                spawnTimer -= diff;
        }

    protected:
        uint32 spawnTimer;
    };

};

/*######
## AddSC
######*/

void AddSC_silverpine_forest()
{
    new npc_deathstalker_erland();
    new npc_hillsbrad_worgens_trigger();
}
