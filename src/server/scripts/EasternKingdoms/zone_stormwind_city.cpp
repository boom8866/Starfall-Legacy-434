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

#include "ScriptPCH.h"

class npc_th_anduinn_wrynn : public CreatureScript
{
public:
    npc_th_anduinn_wrynn() : CreatureScript("npc_th_anduinn_wrynn")
    {
    }

    struct npc_th_anduinn_wrynnAI : public ScriptedAI
    {
        npc_th_anduinn_wrynnAI(Creature* creature) : ScriptedAI(creature)
        {
            playerOwner = NULL;
        }

        EventMap events;

        enum eventId
        {
            EVENT_CHECK_AREA_BEFORE_FOLLOW  = 1,
            EVENT_CHECK_FOR_MOUNT,
            EVENT_CHECK_FOR_OWNER,
            EVENT_CHECK_WORKERS
        };

        enum mountId
        {
            MOUNT_ANDUIN_STEED      = 33819,
            MOUNT_ANDUIN_GRYPHON    = 33805
        };

        enum pointIìd
        {
            POINT_OWNER     = 1
        };

        enum spellId
        {
            SPELL_GRILLING          = 83577,
            SPELL_WORKER_PACIFIED   = 6462,
            SPELL_ROOTED_GRILLING   = 93960
        };

        enum questId
        {
            QUEST_THE_USUAL_SUSPECTS  = 26997
        };

        enum npcId
        {
            NPC_ENTRY_WORKER    = 29152
        };

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() != TYPEID_PLAYER)
                return;

            me->SetSeerGUID(owner->GetGUID());
            playerOwner = owner;
            events.ScheduleEvent(EVENT_CHECK_AREA_BEFORE_FOLLOW, 2000);
            events.ScheduleEvent(EVENT_CHECK_FOR_MOUNT, 1000);
            events.ScheduleEvent(EVENT_CHECK_FOR_OWNER, 2000);
            events.ScheduleEvent(EVENT_CHECK_WORKERS, 2000);

            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetHover(false);
            ground = true;
            air = false;
        };

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_OWNER:
                {
                    events.ScheduleEvent(EVENT_CHECK_FOR_MOUNT, 1250);
                    events.ScheduleEvent(EVENT_CHECK_AREA_BEFORE_FOLLOW, 1500);
                    break;
                }
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_AREA_BEFORE_FOLLOW:
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            if (playerOwner->GetDistance2d(me) > 8)
                            {
                                me->GetMotionMaster()->MoveFollow(playerOwner, 3.0f, 0);
                                events.CancelEvent(EVENT_CHECK_AREA_BEFORE_FOLLOW);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_AREA_BEFORE_FOLLOW, 2000);
                        break;
                    }
                    case EVENT_CHECK_FOR_MOUNT:
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            if (playerOwner->IsMounted())
                            {
                                if (playerOwner->IsFlying() && ground == true)
                                {
                                    me->Mount(MOUNT_ANDUIN_GRYPHON);
                                    me->SetSpeed(MOVE_RUN, 5.0f, true);
                                    me->SetSpeed(MOVE_FLIGHT, 5.0f, true);
                                    me->SetCanFly(true);
                                    me->SetDisableGravity(true);
                                    me->SetHover(true);
                                    ground = false;
                                    air = true;
                                }
                                if (!playerOwner->IsFlying() && (air == true || ground == true))
                                {
                                    me->Mount(MOUNT_ANDUIN_STEED);
                                    me->SetDisableGravity(false);
                                    me->SetCanFly(false);
                                    me->SetHover(false);
                                    air = false;
                                    ground = true;
                                }
                            }
                            else
                            {
                                if (ground == true)
                                {
                                    if (me->IsMounted())
                                        me->Dismount();

                                    me->SetCanFly(false);
                                    me->SetDisableGravity(false);
                                    me->SetHover(false);
                                    ground = true;
                                    air = false;
                                    events.RescheduleEvent(EVENT_CHECK_FOR_MOUNT, 1000);
                                    break;
                                }
                                else
                                {
                                    if (me->GetPositionZ() != playerOwner->GetPositionZ() && me->IsFlying() && air == true && !playerOwner->IsFlying() && !playerOwner->HasUnitMovementFlag(MOVEMENTFLAG_FALLING))
                                    {
                                        me->GetMotionMaster()->Clear();
                                        me->GetMotionMaster()->MoveJump(playerOwner->GetPositionX(), playerOwner->GetPositionY(), playerOwner->GetPositionZ(), 12.5f, 12.5f, POINT_OWNER);
                                        events.CancelEvent(EVENT_CHECK_FOR_MOUNT);
                                        ground = true;
                                        break;
                                    }
                                }
                            }

                            events.RescheduleEvent(EVENT_CHECK_FOR_MOUNT, 1000);
                        }
                        break;
                    }
                    case EVENT_CHECK_FOR_OWNER:
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            if (playerOwner->GetMapId() != me->GetMapId())
                            {
                                me->DespawnOrUnsummon(1);
                                break;
                            }
                            if (me->GetDistance(playerOwner) > 100)
                                me->NearTeleportTo(playerOwner->GetPositionX(), playerOwner->GetPositionY(), playerOwner->GetPositionZ(), 0);
                        }
                        events.RescheduleEvent(EVENT_CHECK_FOR_OWNER, 1000);
                        break;
                    }
                    case EVENT_CHECK_WORKERS:
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            if (playerOwner->ToPlayer()->GetQuestStatus(QUEST_THE_USUAL_SUSPECTS) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (Creature* worker = playerOwner->FindNearestCreature(NPC_ENTRY_WORKER, 6.0f, true))
                                {
                                    if (worker->HasAura(SPELL_WORKER_PACIFIED))
                                    {
                                        events.RescheduleEvent(EVENT_CHECK_WORKERS, 2000);
                                        break;
                                    }
                                    if (playerOwner->isInFront(worker))
                                    {
                                        worker->AddAura(SPELL_WORKER_PACIFIED, worker);
                                        playerOwner->CastSpell(playerOwner, SPELL_ROOTED_GRILLING, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_GRILLING);
                                        worker->SetControlled(true, UNIT_STATE_ROOT);
                                        worker->SetFacingToObject(playerOwner);
                                        worker->AI()->TalkWithDelay(2500, 0);
                                        playerOwner->ToPlayer()->KilledMonsterCredit(44827);
                                        worker->GetMotionMaster()->Clear();
                                        worker->HandleEmoteCommand(EMOTE_STATE_COWER);
                                        worker->DespawnOrUnsummon(10000);
                                    }
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_WORKERS, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
        bool ground;
        bool air;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_anduinn_wrynnAI(creature);
    }
};

class areatrigger_th_stormwind_graves : public AreaTriggerScript
{
public:
    areatrigger_th_stormwind_graves() : AreaTriggerScript("at_stormwind_graves")
    {
    }

    enum npcId
    {
        NPC_ANDUIN_WRYNN    = 44293
    };

    enum questId
    {
        QUEST_RALLYING_THE_FLEET    = 26975
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_RALLYING_THE_FLEET) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_ANDUIN_WRYNN, 85.0f);
            if (creatures.empty())
                return false;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                    player->CompleteQuest(QUEST_RALLYING_THE_FLEET);
            }
        }
        return false;
    }
};

class areatrigger_th_wollerton_stead : public AreaTriggerScript
{
public:
    areatrigger_th_wollerton_stead() : AreaTriggerScript("areatrigger_th_wollerton_stead")
    {
    }

    enum npcId
    {
        NPC_ANDUIN_WRYNN = 44293
    };

    enum questId
    {
        QUEST_PEASANT_PROBLEMS  = 27044
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_PEASANT_PROBLEMS) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_ANDUIN_WRYNN, 85.0f);
            if (creatures.empty())
                return false;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                    player->CompleteQuest(QUEST_PEASANT_PROBLEMS);
            }
        }
        return false;
    }
};

class areatrigger_th_crime_scene : public AreaTriggerScript
{
public:
    areatrigger_th_crime_scene() : AreaTriggerScript("areatrigger_th_crime_scene")
    {
    }

    enum npcId
    {
        NPC_ANDUIN_WRYNN = 44293
    };

    enum questId
    {
        QUEST_UNHOLY_COW    = 27060
    };

    enum creditId
    {
        QUEST_CREDIT_CRIME_SCENE_DISCOVERED     = 44909
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_UNHOLY_COW) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_ANDUIN_WRYNN, 85.0f);
            if (creatures.empty())
                return false;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                    player->KilledMonsterCredit(QUEST_CREDIT_CRIME_SCENE_DISCOVERED);
            }
        }
        return false;
    }
};

void AddSC_stormwind_city()
{
    new npc_th_anduinn_wrynn();
    new areatrigger_th_stormwind_graves();
    new areatrigger_th_wollerton_stead();
    new areatrigger_th_crime_scene();
}
