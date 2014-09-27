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

class npc_ambermill_event_generator : public CreatureScript
{
public:
    npc_ambermill_event_generator() : CreatureScript("npc_ambermill_event_generator") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ambermill_event_generatorAI (creature);
    }

    enum Id
    {
        NPC_HILLSBRAD_WORGEN            = 45270
    };

    struct npc_ambermill_event_generatorAI : public ScriptedAI
    {
        npc_ambermill_event_generatorAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            NPC_ENTRY_ARCHMAGE_ATAERIC  = 2120,
            NPC_ENTRY_DASCHLA           = 45775
        };

        void Reset()
        {
            checkTimer = 3000;
            checkTimer_2 = 5000;
            powerStep_1 = false;
            powerStep_2 = false;
            powerStep_3 = false;
            powerStep_4 = false;
            powerStep_5 = false;
            finalStep = false;
        }

        void UpdateAI(uint32 diff)
        {
            if (UpdateVictim())
                return;

            if (checkTimer <= diff)
            {
                if (Creature* archmageAtaeric = me->FindNearestCreature(NPC_ENTRY_ARCHMAGE_ATAERIC, 100.0f, true))
                {
                    // If is not in combat reset energy and steps
                    if (!archmageAtaeric->isInCombat())
                    {
                        archmageAtaeric->SetPower(POWER_ENERGY, 0);
                        archmageAtaeric->ClearUnitState(UNIT_STATE_EVADE);
                        powerStep_1 = false;
                        powerStep_2 = false;
                        powerStep_3 = false;
                        powerStep_4 = false;
                        powerStep_5 = false;
                    }

                    if (archmageAtaeric->GetPower(POWER_ENERGY) >= 20 && !powerStep_1 && !powerStep_2 && !powerStep_3 && !powerStep_4 && !powerStep_5)
                    {
                        archmageAtaeric->AI()->Talk(2);
                        powerStep_1 = true;
                    }
                    if (archmageAtaeric->GetPower(POWER_ENERGY) >= 40 && powerStep_1 && !powerStep_2 && !powerStep_3 && !powerStep_4 && !powerStep_5)
                    {
                        archmageAtaeric->AI()->Talk(3);
                        powerStep_2 = true;
                    }
                    if (archmageAtaeric->GetPower(POWER_ENERGY) >= 60 && powerStep_1 && powerStep_2 && !powerStep_3 && !powerStep_4 && !powerStep_5)
                    {
                        archmageAtaeric->AI()->Talk(4);
                        powerStep_3 = true;
                    }
                    if (archmageAtaeric->GetPower(POWER_ENERGY) >= 80 && powerStep_1 && powerStep_2 && powerStep_3 && !powerStep_4 && !powerStep_5)
                    {
                        archmageAtaeric->AI()->Talk(5);
                        powerStep_4 = true;
                    }
                    if (archmageAtaeric->GetPower(POWER_ENERGY) >= 95 && powerStep_1 && powerStep_2 && powerStep_3 && powerStep_4 && !powerStep_5)
                    {
                        archmageAtaeric->AI()->Talk(6);
                        powerStep_5 = true;
                    }
                    if (archmageAtaeric->GetPower(POWER_ENERGY) >= 100 && powerStep_1 && powerStep_2 && powerStep_3 && powerStep_4 && powerStep_5)
                        archmageAtaeric->Kill(archmageAtaeric, false);
                }
                checkTimer = 3000;
            }
            else
                checkTimer -= diff;

            if (checkTimer <= diff)
            {
                if (Creature* archmageAtaeric = me->FindNearestCreature(NPC_ENTRY_ARCHMAGE_ATAERIC, 100.0f, false))
                {
                    if (finalStep)
                        return;

                    if (Creature* daschla = me->FindNearestCreature(NPC_ENTRY_DASCHLA, 100.0f, true))
                    {
                        daschla->AI()->SetData(0, 1);
                        finalStep = true;
                    }
                    archmageAtaeric->Respawn(true);
                }
                checkTimer_2 = 5000;
            }
            else
                checkTimer_2 -= diff;
        }

    protected:
        uint16 checkTimer;
        uint16 checkTimer_2;
        bool powerStep_1;
        bool powerStep_2;
        bool powerStep_3;
        bool powerStep_4;
        bool powerStep_5;
        bool finalStep;
    };
};

class npc_pyrewood_trigger : public CreatureScript
{
public:
    npc_pyrewood_trigger() : CreatureScript("npc_pyrewood_trigger") { }

    struct npc_pyrewood_triggerAI : public ScriptedAI
    {
        npc_pyrewood_triggerAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            // Npc
            NPC_ENTRY_TRIGGER_1 = 45937,
            NPC_ENTRY_TRIGGER_2 = 45938,
            NPC_ENTRY_TRIGGER_3 = 45939,

            // Spell
            SPELL_THROW_TORCH   = 85600,

            // GameObjects
            GO_ENTRY_FIRE       = 205578
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (!me->getVictim() && spell->Id == SPELL_THROW_TORCH)
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    switch (me->GetEntry())
                    {
                        case NPC_ENTRY_TRIGGER_1:
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_TRIGGER_1);
                            std::list<GameObject*> fire;
                            me->GetGameObjectListWithEntryInGrid(fire, GO_ENTRY_FIRE, 85.0f);
                            if (!fire.empty())
                            {
                                for (std::list<GameObject*>::const_iterator itr = fire.begin(); itr != fire.end(); ++itr)
                                {
                                    if ((*itr)->GetPhaseMask() != 1)
                                        (*itr)->SetPhaseMask(1, true);
                                }
                            }
                            break;
                        }
                        case NPC_ENTRY_TRIGGER_2:
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_TRIGGER_2);
                            std::list<GameObject*> fire;
                            me->GetGameObjectListWithEntryInGrid(fire, GO_ENTRY_FIRE, 85.0f);
                            if (!fire.empty())
                            {
                                for (std::list<GameObject*>::const_iterator itr = fire.begin(); itr != fire.end(); ++itr)
                                {
                                    if ((*itr)->GetPhaseMask() != 1)
                                        (*itr)->SetPhaseMask(1, true);
                                }
                            }
                            break;
                        }
                        case NPC_ENTRY_TRIGGER_3:
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_TRIGGER_3);
                            std::list<GameObject*> fire;
                            me->GetGameObjectListWithEntryInGrid(fire, GO_ENTRY_FIRE, 85.0f);
                            if (!fire.empty())
                            {
                                for (std::list<GameObject*>::const_iterator itr = fire.begin(); itr != fire.end(); ++itr)
                                {
                                    if ((*itr)->GetPhaseMask() != 1)
                                        (*itr)->SetPhaseMask(1, true);
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pyrewood_triggerAI (creature);
    }
};

/*######
## AddSC
######*/

void AddSC_silverpine_forest()
{
    new npc_deathstalker_erland();
    new npc_hillsbrad_worgens_trigger();
    new npc_ambermill_event_generator();
    new npc_pyrewood_trigger();
}
