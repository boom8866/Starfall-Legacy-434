/*
 * Copyright (C) 2013-2014 StarfallCore <http://www.wowsoc.org/>
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

/* Automatic rescheduling if creature is already casting */
#define RESCHEDULE_IF_CASTING if (me->HasUnitState(UNIT_STATE_CASTING)) { events.ScheduleEvent(eventId, 1); break; }

class npc_th_anduinn_wrynn : public CreatureScript
{
public:
    npc_th_anduinn_wrynn() : CreatureScript("npc_th_anduinn_wrynn")
    {
    }

    enum questId
    {
        QUEST_THE_USUAL_SUSPECTS    = 26997,
        QUEST_UNHOLY_COW            = 27060
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_UNHOLY_COW)
        {
            creature->AI()->Talk(10, player->GetGUID());
            return true;
        }
        return true;
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
            EVENT_CHECK_WORKERS,
            EVENT_MOVE_AMBUSH,
            EVENT_START_AMBUSH,
            EVENT_HEAL_OWNER,
            EVENT_SUMMON_AMBUSHER,
            EVENT_COMPLETE,
            EVENT_MOVE_EXAMINATE,
            EVENT_FINISH_EXAMINATING
        };

        enum mountId
        {
            MOUNT_ANDUIN_STEED      = 33819,
            MOUNT_ANDUIN_GRYPHON    = 33805
        };

        enum pointIid
        {
            POINT_OWNER         = 1,
            POINT_ALTAR,
            POINT_AMBUSH,
            POINT_EXAMINATE_1,
            POINT_EXAMINATE_2
        };

        enum spellId
        {
            SPELL_GRILLING          = 83577,
            SPELL_WORKER_PACIFIED   = 6462,
            SPELL_ROOTED_GRILLING   = 93960,
            SPELL_PW_SHIELD         = 83842,
            SPELL_FLASH_HEAL        = 83844,
            SPELL_TWILIGHT_STRIKER  = 83836
        };

        enum npcId
        {
            NPC_ENTRY_WORKER    = 29152
        };

        enum actionId
        {
            ACTION_PREPARE_TO_AMBUSH    = 1,
            ACTION_MOVE_AMBUSH,
            ACTION_EXAMINATE
        };

        enum creditId
        {
            QUEST_CREDIT_AMBUSH     = 44910,
            QUEST_CREDIT_PAPERS     = 44921
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
            ambush = false;
            investigating = false;
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
                case POINT_ALTAR:
                {
                    me->Dismount();
                    me->SetWalk(true);
                    TalkWithDelay(1000, 4);
                    events.ScheduleEvent(EVENT_MOVE_AMBUSH, 100);
                    break;
                }
                case POINT_AMBUSH:
                {
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    TalkWithDelay(1500, 5);
                    if (Unit* owner = me->ToTempSummon()->GetSummoner())
                    {
                        me->SetFacingToObject(owner);
                        TalkWithDelay(11000, 6, owner->GetGUID());
                    }
                    TalkWithDelay(27500, 7);
                    TalkWithDelay(44000, 8);
                    events.ScheduleEvent(EVENT_START_AMBUSH, 11000);
                    break;
                }
                case POINT_EXAMINATE_1:
                {
                    if (investigating == false)
                        break;

                    Talk(11);
                    events.ScheduleEvent(EVENT_MOVE_EXAMINATE, 6000);
                    me->SetWalk(true);
                    break;
                }
                case POINT_EXAMINATE_2:
                {
                    if (investigating == false)
                        break;

                    Talk(12);
                    me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
                    me->SetFacingTo(2.31f);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    events.ScheduleEvent(EVENT_FINISH_EXAMINATING, 8500);
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
                case ACTION_PREPARE_TO_AMBUSH:
                {
                    if (ambush == false && me->GetPhaseMask() & 4096)
                    {
                        ambush = true;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovementExpired(false);
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(POINT_ALTAR, -8048.34f, 950.91f, 79.23f);
                        break;
                    }
                }
                case ACTION_MOVE_AMBUSH:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MovePoint(POINT_AMBUSH, -8046.52f, 965.96f, 80.27f);
                    break;
                }
                case ACTION_EXAMINATE:
                {
                    if (investigating == false)
                    {
                        investigating = true;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovementExpired(false);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(POINT_EXAMINATE_1, -8714.76f, 324.08f, 122.11f);
                    }
                    break;
                }
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
                                if (playerOwner->IsFlying() && ground == true && ambush == false && investigating == false)
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
                                if (!playerOwner->IsFlying() && (air == true || ground == true) && ambush == false && investigating == false)
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
                                if (ambush == true || investigating == true)
                                {
                                    events.RescheduleEvent(EVENT_CHECK_FOR_MOUNT, 1000);
                                    break;
                                }

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
                        if (ambush == true || investigating == true)
                        {
                            events.RescheduleEvent(EVENT_CHECK_FOR_OWNER, 1000);
                            break;
                        }

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
                        if (ambush == true || investigating == true)
                        {
                            events.RescheduleEvent(EVENT_CHECK_WORKERS, 2000);
                            break;
                        }

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
                    case EVENT_MOVE_AMBUSH:
                    {
                        DoAction(ACTION_MOVE_AMBUSH);
                        events.CancelEvent(EVENT_MOVE_AMBUSH);
                        break;
                    }
                    case EVENT_START_AMBUSH:
                    {
                        DoCast(me, SPELL_PW_SHIELD, true);
                        DoCast(me, SPELL_TWILIGHT_STRIKER, true);
                        events.ScheduleEvent(EVENT_HEAL_OWNER, 3000);
                        events.ScheduleEvent(EVENT_SUMMON_AMBUSHER, 16500);
                        events.ScheduleEvent(EVENT_COMPLETE, 65000);
                        events.CancelEvent(EVENT_START_AMBUSH);
                        break;
                    }
                    case EVENT_HEAL_OWNER:
                    {
                        if (Unit* owner = me->ToTempSummon()->GetSummoner())
                        {
                            if (!owner->isInCombat())
                            {
                                events.RescheduleEvent(EVENT_HEAL_OWNER, urand(5000, 6000));
                                break;
                            }

                            if (me->GetHealth() < me->GetHealthPct() * 0.85f)
                                DoCast(me, SPELL_FLASH_HEAL);
                            else
                                DoCast(owner, SPELL_FLASH_HEAL);
                        }
                        events.RescheduleEvent(EVENT_HEAL_OWNER, urand(5000, 6000));
                        break;
                    }
                    case EVENT_SUMMON_AMBUSHER:
                    {
                        DoCast(me, SPELL_PW_SHIELD, true);
                        DoCast(me, SPELL_TWILIGHT_STRIKER, true);
                        // Chance to summon a 2nd striker
                        if (roll_chance_f(65.0f))
                            DoCast(me, SPELL_TWILIGHT_STRIKER, true);
                        events.RescheduleEvent(EVENT_SUMMON_AMBUSHER, 16500);
                        break;
                    }
                    case EVENT_COMPLETE:
                    {
                        events.CancelEvent(EVENT_COMPLETE);
                        events.CancelEvent(EVENT_HEAL_OWNER);
                        events.CancelEvent(EVENT_SUMMON_AMBUSHER);
                        if (Unit* owner = me->ToTempSummon()->GetCharmerOrOwner())
                        {
                            owner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_AMBUSH);
                            TalkWithDelay(500, 9, owner->GetGUID());
                            me->SetControlled(false, UNIT_STATE_ROOT);
                            me->GetMotionMaster()->MoveFollow(owner, 3.0f, 0);
                        }
                        ambush = false;
                        break;
                    }
                    case EVENT_MOVE_EXAMINATE:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_EXAMINATE_2, -8714.82f, 328.82f, 122.10f);
                        events.CancelEvent(EVENT_MOVE_EXAMINATE);
                        break;
                    }
                    case EVENT_FINISH_EXAMINATING:
                    {
                        if (Unit* owner = me->ToTempSummon()->GetCharmerOrOwner())
                        {
                            owner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_PAPERS);
                            TalkWithDelay(500, 13, owner->GetGUID());
                            me->SetControlled(false, UNIT_STATE_ROOT);
                            me->SetWalk(false);
                            me->SetFacingToObject(owner);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovementExpired(false);
                            me->GetMotionMaster()->MoveFollow(owner, 3.0f, 0);
                        }
                        me->HandleEmoteCommand(EMOTE_STATE_NONE);
                        me->SetStandState(EMOTE_STATE_STAND);
                        events.CancelEvent(EVENT_FINISH_EXAMINATING);
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        }

    protected:
        Unit* playerOwner;
        bool ground;
        bool air;
        bool ambush;
        bool investigating;
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
                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
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
                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
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
        NPC_ANDUIN_WRYNN = 44293,
        NPC_CULT_SITE    = 50253
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
                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                {
                    player->KilledMonsterCredit(QUEST_CREDIT_CRIME_SCENE_DISCOVERED);
                    (*iter)->AI()->DoAction(1);
                }
            }
        }
        return false;
    }
};

class npc_th_twilight_striker : public CreatureScript
{
public:
    npc_th_twilight_striker() : CreatureScript("npc_th_twilight_striker")
    {
    }

    struct npc_th_twilight_strikerAI : public ScriptedAI
    {
        npc_th_twilight_strikerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_JUMP_TO           = 1,
            EVENT_DEADLY_POISON,
            EVENT_SINISTER_STRIKE
        };

        enum spellId
        {
            SPELL_DEADLY_POISON     = 3583,
            SPELL_SINISTER_STRIKE   = 14873
        };

        void IsSummonedBy(Unit* summoner)
        {
            AttackStart(summoner);
            me->GetMotionMaster()->MoveJump(-8052.62f + 3, 958.88f - 3, 79.33f, 14.5f, 14.5f);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_DEADLY_POISON, 2000);
            events.ScheduleEvent(EVENT_SINISTER_STRIKE, 2200);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEADLY_POISON:
                    {
                        if (Unit* victim = me->getVictim())
                        {
                            if (!victim->HasAura(SPELL_DEADLY_POISON))
                                DoCastVictim(SPELL_DEADLY_POISON, true);
                        }
                        events.RescheduleEvent(EVENT_DEADLY_POISON, 16000);
                        break;
                    }
                    case EVENT_SINISTER_STRIKE:
                    {
                        DoCastVictim(SPELL_SINISTER_STRIKE, true);
                        events.RescheduleEvent(EVENT_SINISTER_STRIKE, urand(3500, 5000));
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_twilight_strikerAI(creature);
    }
};

class areatrigger_th_si7 : public AreaTriggerScript
{
public:
    areatrigger_th_si7() : AreaTriggerScript("areatrigger_th_si7")
    {
    }

    enum npcId
    {
        NPC_ANDUIN_WRYNN = 44293
    };

    enum questId
    {
        QUEST_HES_HOLDING_OUT_ON_US     = 27064
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_HES_HOLDING_OUT_ON_US) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_ANDUIN_WRYNN, 85.0f);
            if (creatures.empty())
                return false;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                    (*iter)->AI()->DoAction(3);
            }
        }
        return false;
    }
};

class npc_th_the_black_bishop : public CreatureScript
{
public:
    npc_th_the_black_bishop() : CreatureScript("npc_th_the_black_bishop")
    {
    }

    struct npc_th_the_black_bishopAI : public ScriptedAI
    {
        npc_th_the_black_bishopAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MIND_BLAST        = 1,
            EVENT_PENANCE,
            EVENT_SHIELD,
            EVENT_DIAGONAL_SLIDE,
            EVENT_CHECK_HP
        };

        enum spellId
        {
            SPELL_AIR_SHIELD        = 84018,
            SPELL_DIAGONAL_SLIDE    = 83991,
            SPELL_INNER_FIRE        = 48168,
            SPELL_MIND_BLAST        = 13860,
            SPELL_PENANCE           = 54518,
            SPELL_POWER_WORD_SHIELD = 11974,
            SPELL_SLIDE_EFFECT      = 83995
        };

        enum goId
        {
            GO_BISHOP_SHIELD    = 205199
        };

        void Reset()
        {
            me->SetControlled(false, UNIT_STATE_ROOT);
            if (me->isAlive())
            {
                if (GameObject* airWall = me->FindNearestGameObject(GO_BISHOP_SHIELD, 150.0f))
                {
                    if (airWall->GetGoState() == GO_STATE_ACTIVE)
                        airWall->SetGoState(GO_STATE_READY);
                }
            }
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_SLIDE_EFFECT:
                {
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    if (teleportCount == 0 || teleportCount == 2 || teleportCount == 4)
                        me->NearTeleportTo(-8494.87f, 836.64f, 72.70f, 0.07f);
                    if (teleportCount == 1 || teleportCount == 3 || teleportCount == 5)
                        me->NearTeleportTo(-8466.56f, 841.64f, 72.70f, 3.11f);
                    teleportCount++;
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    break;
                }
                default:
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(2);
            if (GameObject* airWall = me->FindNearestGameObject(GO_BISHOP_SHIELD, 150.0f))
            {
                if (airWall->GetGoState() == GO_STATE_READY)
                    airWall->SetGoState(GO_STATE_ACTIVE);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.Reset();

            Talk(4);
            teleportCount = 0;
            DoCast(me, SPELL_AIR_SHIELD, true);
            if (me->HasAura(SPELL_INNER_FIRE))
                DoCast(me, SPELL_INNER_FIRE, true);

            events.ScheduleEvent(EVENT_SHIELD, 1);
            events.ScheduleEvent(EVENT_MIND_BLAST, 1000);
            events.ScheduleEvent(EVENT_PENANCE, 4000);
            events.ScheduleEvent(EVENT_DIAGONAL_SLIDE, 12500);
            events.ScheduleEvent(EVENT_CHECK_HP, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHIELD:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(me, SPELL_POWER_WORD_SHIELD);
                        events.RescheduleEvent(EVENT_SHIELD, 12000);
                        break;
                    }
                    case EVENT_MIND_BLAST:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCastVictim(SPELL_MIND_BLAST);
                        events.RescheduleEvent(EVENT_MIND_BLAST, urand(5000, 7500));
                        break;
                    }
                    case EVENT_PENANCE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (roll_chance_f(20))
                            Talk(1);
                        DoCastVictim(SPELL_PENANCE);
                        events.RescheduleEvent(EVENT_PENANCE, urand(5000, 7500));
                        break;
                    }
                    case EVENT_DIAGONAL_SLIDE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (teleportCount > 5)
                        {
                            events.CancelEvent(EVENT_DIAGONAL_SLIDE);
                            break;
                        }
                        Talk(3);
                        DoCast(me, SPELL_DIAGONAL_SLIDE);
                        me->CastWithDelay(500, me, SPELL_SLIDE_EFFECT, true);
                        events.RescheduleEvent(EVENT_DIAGONAL_SLIDE, 16500);
                        break;
                    }
                    case EVENT_CHECK_HP:
                    {
                        if (me->GetHealth() < me->GetMaxHealth() * 0.35f)
                        {
                            Talk(5);
                            teleportCount = 0;
                            DoCast(me, SPELL_DIAGONAL_SLIDE);
                            me->CastWithDelay(500, me, SPELL_SLIDE_EFFECT, true);
                            events.CancelEvent(EVENT_CHECK_HP);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_HP, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        uint8 teleportCount;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_the_black_bishopAI(creature);
    }
};

void AddSC_stormwind_city()
{
    new npc_th_anduinn_wrynn();
    new areatrigger_th_stormwind_graves();
    new areatrigger_th_wollerton_stead();
    new areatrigger_th_crime_scene();
    new npc_th_twilight_striker();
    new areatrigger_th_si7();
    new npc_th_the_black_bishop();
}
