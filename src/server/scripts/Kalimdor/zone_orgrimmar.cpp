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
SDName: Orgrimmar
SD%Complete: 0
SDComment: Quest support:
SDCategory: Orgrimmar
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

class npc_th_hellscream_demolisher : public CreatureScript
{
public:
    npc_th_hellscream_demolisher() : CreatureScript("npc_th_hellscream_demolisher")
    {
    }

    enum questId
    {
        QUEST_WEAPONS_OF_MASS_DYSFUNCTION   = 26294
    };

    enum demolisherGUID
    {
        GUID_DEMOLISHER_ONE     = 161932,
        GUID_DEMOLISHER_TWO     = 161917,
        GUID_DEMOLISHER_THREE   = 161916
    };

    enum spellId
    {
        SPELL_INSPECT_DEMOLISHER    = 79545
    };

    enum npcId
    {
        NPC_CHIEF_ENGINEER     = 42671
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_WEAPONS_OF_MASS_DYSFUNCTION) == QUEST_STATUS_INCOMPLETE)
        {
            if (player->HasUnitState(UNIT_STATE_CASTING))
                return true;

            player->CastSpell(creature, SPELL_INSPECT_DEMOLISHER);

            if (Creature* chief = creature->FindNearestCreature(NPC_CHIEF_ENGINEER, 10.0f, true))
            {
                switch (creature->GetGUIDLow())
                {
                    case GUID_DEMOLISHER_ONE:
                    {
                        chief->AI()->Talk(0);
                        break;
                    }
                    case GUID_DEMOLISHER_TWO:
                    {
                        chief->AI()->Talk(2);
                        break;
                    }
                    case GUID_DEMOLISHER_THREE:
                    {
                        chief->AI()->Talk(4);
                        break;
                    }
                    default:
                        break;
                }
            }
            return true;
        }
        return true;
    }

    struct npc_th_hellscream_demolisherAI : public ScriptedAI
    {
        npc_th_hellscream_demolisherAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* chief = me->FindNearestCreature(NPC_CHIEF_ENGINEER, 10.0f, true))
            {
                chief->AI()->DoAction(1);
                chief->AI()->DoAction(2);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_INSPECT_DEMOLISHER:
                {
                    if (Creature* chief = me->FindNearestCreature(NPC_CHIEF_ENGINEER, 10.0f, true))
                    {
                        switch (me->GetGUIDLow())
                        {
                            case GUID_DEMOLISHER_ONE:
                            {
                                chief->AI()->TalkWithDelay(1000, 1);
                                break;
                            }
                            case GUID_DEMOLISHER_TWO:
                            {
                                chief->AI()->TalkWithDelay(1000, 3);
                                break;
                            }
                            case GUID_DEMOLISHER_THREE:
                            {
                                me->Kill(me, false);

                                if (caster->GetTypeId() == TYPEID_PLAYER)
                                    caster->ToPlayer()->KilledMonsterCredit(42674);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_hellscream_demolisherAI(creature);
    }
};

class npc_th_chief_engineer : public CreatureScript
{
public:
    npc_th_chief_engineer() : CreatureScript("npc_th_chief_engineer")
    {
    }

    enum questId
    {
        QUEST_WEAPONS_OF_MASS_DYSFUNCTION   = 26294
    };

    enum spellId
    {
        SPELL_DISCIPLINE    = 79568
    };

    enum npcId
    {
        NPC_CHIEF_ENGINEER      = 42671,
        NPC_DEMOLISHER          = 42673,
        NPC_GOBLIN_SIEGEWORKER  = 42650
    };

    enum eventId
    {
        EVENT_CHECK_FOR_EVADE       = 1,
        EVENT_CAN_BE_DISCIPLINED
    };

    enum actionId
    {
        ACTION_EVADE_TIMER          = 1,
        ACTION_ENABLE_DISCIPLINE
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_WEAPONS_OF_MASS_DYSFUNCTION) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(creature, SPELL_DISCIPLINE);
            if (Creature* demolisher = creature->FindNearestCreature(NPC_DEMOLISHER, 10.0f, false))
                demolisher->DespawnOrUnsummon(3000);

            creature->DespawnOrUnsummon(3000);
            return true;
        }
        return true;
    }

    struct npc_th_chief_engineerAI : public ScriptedAI
    {
        npc_th_chief_engineerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_EVADE_TIMER:
                {
                    me->AI()->TalkWithDelay(1000, 5);
                    me->AI()->TalkWithDelay(7000, 6);
                    me->AI()->TalkWithDelay(14000, 7);
                    me->AI()->TalkWithDelay(21000, 8);
                    me->AI()->TalkWithDelay(28000, 9);
                    me->AI()->TalkWithDelay(35000, 10);
                    me->AI()->TalkWithDelay(42000, 11);
                    me->AI()->TalkWithDelay(49000, 12);
                    events.ScheduleEvent(EVENT_CHECK_FOR_EVADE, 60000);
                    break;
                }
                case ACTION_ENABLE_DISCIPLINE:
                    events.ScheduleEvent(EVENT_CAN_BE_DISCIPLINED, 18000);
                    break;
                default:
                    break;
            }
        }

        void Reset()
        {
            events.Reset();
            me->m_Events.KillAllEvents(true);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DISCIPLINE:
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->ToPlayer()->KilledMonsterCredit(42675);

                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 35.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(35.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                        {
                            if ((*itr)->GetEntry() != NPC_GOBLIN_SIEGEWORKER)
                                continue;

                            (*itr)->ToCreature()->AI()->TalkWithDelay(1500, 0);
                        }
                    }
                    events.Reset();
                    me->m_Events.KillAllEvents(true);
                    me->DespawnOrUnsummon(4000);
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
                    case EVENT_CHECK_FOR_EVADE:
                    {
                        me->MonsterTextEmote("Chief Engineer takes off running.", 0, false);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(50, 2352.27f, -4736.54f, 120.82f);
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        events.Reset();
                        me->m_Events.KillAllEvents(true);
                        me->DespawnOrUnsummon(5000);
                        events.CancelEvent(EVENT_CHECK_FOR_EVADE);
                        break;
                    }
                    case EVENT_CAN_BE_DISCIPLINED:
                    {
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        events.CancelEvent(EVENT_CAN_BE_DISCIPLINED);
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
        return new npc_th_chief_engineerAI(creature);
    }
};

class npc_th_awol_grunt : public CreatureScript
{
public:
    npc_th_awol_grunt() : CreatureScript("npc_th_awol_grunt")
    {
    }

    enum questId
    {
        QUEST_READY_THE_GROUND_TROOPS   = 26374
    };

    enum spellId
    {
        SPELL_DISCIPLINE =  80017
    };

    enum npcId
    {
    };

    enum eventId
    {
        EVENT_CHECK_HEALTH  = 1
    };

    enum actionId
    {
        ACTION_ENEMY    = 1
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_READY_THE_GROUND_TROOPS) == QUEST_STATUS_INCOMPLETE)
        {
            if (player->HasUnitState(UNIT_STATE_CASTING) || creature->getFaction() != 125)
                return true;

            player->CastSpell(creature, SPELL_DISCIPLINE);
            return true;
        }
        return true;
    }

    struct npc_th_awol_gruntAI : public ScriptedAI
    {
        npc_th_awol_gruntAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENEMY:
                {
                    me->setFaction(14);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    Talk(1);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 100);
        }

        void EnterEvadeMode()
        {
            me->setFaction(125);
            me->CombatStop();
            me->CastStop();
            me->SetHealth(me->GetMaxHealth());
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DISCIPLINE:
                {
                    if (roll_chance_f(25))
                        DoAction(ACTION_ENEMY);
                    else
                    {
                        Talk(0);
                        if (caster->GetTypeId() == TYPEID_PLAYER)
                            caster->ToPlayer()->KilledMonsterCredit(42893);

                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        me->DespawnOrUnsummon(8000);
                        me->RemoveAurasDueToSpell(80109);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.65f)
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (victim->GetTypeId() == TYPEID_PLAYER)
                                    victim->ToPlayer()->KilledMonsterCredit(42893);
                            }
                            me->setFaction(125);
                            me->CombatStop();
                            me->CastStop();
                            me->SetHealth(me->GetMaxHealth());
                            Talk(2);
                            me->DespawnOrUnsummon(8000);
                            me->RemoveAurasDueToSpell(80109);
                            events.CancelEvent(EVENT_CHECK_HEALTH);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_HEALTH, 1000);
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
        return new npc_th_awol_gruntAI(creature);
    }
};

class npc_th_bilgewater_foreman : public CreatureScript
{
public:
    npc_th_bilgewater_foreman() : CreatureScript("npc_th_bilgewater_foreman")
    {
    }

    enum questId
    {
        QUEST_BEATING_THE_MARKET    = 26337
    };

    enum spellId
    {
        SPELL_CLEAVE    = 15284,
        SPELL_STRIKE    = 11976
    };

    enum eventId
    {
        EVENT_CHECK_TIMER = 1,
        EVENT_CLEAVE,
        EVENT_STRIKE
    };

    #define GOSSIP_MARKET "Nobody shorts Garrosh Hellscream. You finish those ships - and finish them right - or this gets personal."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_BEATING_THE_MARKET) == QUEST_STATUS_INCOMPLETE)
            {
                creature->setFaction(14);
                creature->AI()->AttackStart(player);
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_BEATING_THE_MARKET) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_MARKET, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_bilgewater_foremanAI : public ScriptedAI
    {
        npc_th_bilgewater_foremanAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CHECK_TIMER, 35000);
            events.ScheduleEvent(EVENT_CLEAVE, urand(3000, 5000));
            events.ScheduleEvent(EVENT_STRIKE, 1);
            Talk(0);
            TalkWithDelay(7000, 1);
            TalkWithDelay(14000, 2);
            TalkWithDelay(21000, 3);
            TalkWithDelay(28000, 4);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        void EnterEvadeMode()
        {
            me->setFaction(2160);
            me->CombatStop();
            me->CastStop();
            me->SetHealth(me->GetMaxHealth());
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_TIMER:
                    {
                        if (Unit* victim = me->getVictim())
                        {
                            if (victim->GetTypeId() == TYPEID_PLAYER)
                                victim->ToPlayer()->KilledMonsterCredit(42798);
                        }
                        me->setFaction(125);
                        me->CombatStop();
                        me->CastStop();
                        me->SetHealth(me->GetMaxHealth());
                        Talk(5);
                        TalkWithDelay(7000, 6);
                        me->DespawnOrUnsummon(16000);
                        events.CancelEvent(EVENT_CHECK_TIMER);
                        break;
                    }
                    case EVENT_STRIKE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_STRIKE, true);
                        events.RescheduleEvent(EVENT_STRIKE, urand(12000, 15000));
                        break;
                    }
                    case EVENT_CLEAVE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_CLEAVE, true);
                        events.RescheduleEvent(EVENT_CLEAVE, urand(17000, 22000));
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
        return new npc_th_bilgewater_foremanAI(creature);
    }
};

class go_th_h_portal_to_twilight_highlands : public GameObjectScript
{
public:
    go_th_h_portal_to_twilight_highlands() : GameObjectScript("go_th_h_portal_to_twilight_highlands")
    {
    }

    enum questId
    {
        QUEST_TRAITORS_BAIT     = 26830
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_TRAITORS_BAIT) == QUEST_STATUS_REWARDED)
            return false;
        return true;
    }
};

void AddSC_orgrimmar()
{
    new npc_th_hellscream_demolisher();
    new npc_th_chief_engineer();
    new npc_th_awol_grunt();
    new npc_th_bilgewater_foreman();
    new go_th_h_portal_to_twilight_highlands();
}
