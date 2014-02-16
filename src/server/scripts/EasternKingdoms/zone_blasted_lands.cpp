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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"

enum Id
{
    // Quest Entry
    QUEST_YOU_ARE_RAKHLIKH_DEMON_A  = 26171,
    QUEST_YOU_ARE_RAKHLIKH_DEMON_H  = 25701,

    // Deathly Usher Spells
    SPELL_TELEPORT_SINGLE           = 12885,

    // Razelikh the Defiler Spells
    SPELL_DECIMATE                  = 13459,
    SPELL_FLAMES_OF_CHAOS           = 10854,
    SPELL_FLAMES_OF_CHAOS_TRIGGER   = 10857,
    SPELL_FRENZY                    = 8269,
    SPELL_STRONG_CLEAVE             = 8255,
    SPELL_SUMMON_MINION             = 77374,

    // Loramus Thalipedes Spells
    SPELL_DEMON_HUNTER_RESOLVE      = 77371,
    SPELL_DEMON_HUNTER_RESOLVE_GRIP = 77372,
    SPELL_SHADOW_BOLT_VOLLEY        = 9081,

    // Npc
    NPC_RAZELIKH_THE_DEFILER        = 41280,
    NPC_LORAMUS_THE_DEFILED         = 41292,
    NPC_LORAMUS_THALIPEDES          = 41279
};

enum thalipedesEvents
{
    EVENT_SUMMONED_TALK             = 1,
    EVENT_UNLOCK_RAZELIKH,
    EVENT_DEMON_HUNTER_RESOLVE,
    EVENT_CAST_SHADOW_BOLT_VOLLEY,
    EVENT_CHECK_HEALTH_FOR_FINISH,
    EVENT_FINAL_PHASE
};

enum defilerEvents
{
    EVENT_CAST_DECIMATE             = 1,
    EVENT_CAST_FLAMES_OF_CHAOS,
    EVENT_CAST_STRONG_CLEAVE,
    EVENT_CAST_SUMMON_MINION,
    EVENT_SWITCH_PHASE,
    EVENT_DEFILER_DIE,
};

enum defiledEvents
{
    EVENT_START_TALK                = 1,
    EVENT_ENTER_COMBAT,
    EVENT_CAST_SHADOW_BOLT_VOLLEY_2
};

#define RESCHEDULE_IF_CASTING if (me->HasUnitState(UNIT_STATE_CASTING)) { events.ScheduleEvent(eventId, 1); break; }

/*######
## Deathly Usher
######*/

#define GOSSIP_ITEM_USHER "I wish to face the Defiler."

class npc_deathly_usher : public CreatureScript
{
public:
    npc_deathly_usher() : CreatureScript("npc_deathly_usher") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF)
        {
            // Don't allow to start the event if another one is already in progress
            if (player->FindNearestCreature(NPC_RAZELIKH_THE_DEFILER, 500.05f, true) ||
                player->FindNearestCreature(NPC_LORAMUS_THALIPEDES, 500.0f, true) ||
                player->FindNearestCreature(NPC_LORAMUS_THE_DEFILED, 500.05f, true))
            {
                creature->MonsterWhisper("I can't allow you to face the Defiler now, try to ask me again later...", player->GetGUID(), true);
                return false;
            }

            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -11230.32f, -2832.27f, 157.93f, 4.15f);

            // Summon Razelikh and Thalipedes
            player->SummonCreature(NPC_RAZELIKH_THE_DEFILER, -11234.14f, -2842.62f, 157.92f, 1.86f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
            player->SummonCreature(NPC_LORAMUS_THALIPEDES, -11237.28f, -2838.03f, 157.92f, 5.22f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_YOU_ARE_RAKHLIKH_DEMON_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_YOU_ARE_RAKHLIKH_DEMON_A) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_USHER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }
};

class npc_loramus_thalipedes : public CreatureScript
{
public:
    npc_loramus_thalipedes() : CreatureScript("npc_loramus_thalipedes") { }

    struct npc_loramus_thalipedesAI : public ScriptedAI
    {
        npc_loramus_thalipedesAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void InitializeAI()
        {
            events.ScheduleEvent(EVENT_SUMMONED_TALK, 6000);
            me->RemoveAurasDueToSpell(SPELL_DEMON_HUNTER_RESOLVE);
            me->ApplySpellImmune(SPELL_FLAMES_OF_CHAOS, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
        }

        void UpdateAI(uint32 diff)
        {
            /*                                      */
            /*Init Event check while out of combat  */
            /*                                      */

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMONED_TALK:
                    {
                        // Set in combat state and start event
                        me->HandleEmoteCommand(EMOTE_STATE_READY2H);
                        Talk(0);
                        TalkWithDelay(6000, 1);
                        TalkWithDelay(12000, 2);
                        events.ScheduleEvent(EVENT_UNLOCK_RAZELIKH, 17000);
                        break;
                    }
                    case EVENT_UNLOCK_RAZELIKH:
                    {
                        if (Creature* razelikh = me->FindNearestCreature(NPC_RAZELIKH_THE_DEFILER, 50.0f, true))
                        {
                            // Remove flags
                            razelikh->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            razelikh->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            razelikh->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                            razelikh->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            razelikh->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);

                            // Attack start focusing Thalipedes
                            razelikh->AI()->AttackStart(me);
                            razelikh->AddThreat(me, 90.0f);
                            if (Player* nearestPlayer = razelikh->FindNearestPlayer(80.0f, true))
                                razelikh->AddThreat(nearestPlayer, 10.0f);
                        }

                        // This should be activated some second after combat start
                        events.ScheduleEvent(EVENT_DEMON_HUNTER_RESOLVE, 5000);
                        break;
                    }
                    default:
                        break;
                }

                /*                                      */
                /*Init Event check while in combat state*/
                /*                                      */

                if (!UpdateVictim())
                    return;

                switch (eventId)
                {
                    case EVENT_DEMON_HUNTER_RESOLVE:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_DEMON_HUNTER_RESOLVE);
                        events.ScheduleEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY, 6000);
                        break;
                    }
                    case EVENT_CAST_SHADOW_BOLT_VOLLEY:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_SHADOW_BOLT_VOLLEY);
                        events.ScheduleEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY, 6000);
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
        return new npc_loramus_thalipedesAI(creature);
    }
};

class npc_razelikh_the_defiler : public CreatureScript
{
public:
    npc_razelikh_the_defiler() : CreatureScript("npc_razelikh_the_defiler") { }

    struct npc_razelikh_the_defilerAI : public ScriptedAI
    {
        npc_razelikh_the_defilerAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void Reset()
        {
            me->ApplySpellImmune(SPELL_FLAMES_OF_CHAOS, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_DEMON_HUNTER_RESOLVE, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_CAST_DECIMATE, urand(6000, 12000));
            events.ScheduleEvent(EVENT_CAST_FLAMES_OF_CHAOS, urand(25500, 35000));
            events.ScheduleEvent(EVENT_CAST_STRONG_CLEAVE, 5000);
            events.ScheduleEvent(EVENT_CAST_SUMMON_MINION, urand(15500, 45000));
            events.ScheduleEvent(EVENT_SWITCH_PHASE, 2500);
            DoCast(me, SPELL_FRENZY);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_DECIMATE:
                    {
                        if (UpdateVictim())
                        {
                            RESCHEDULE_IF_CASTING
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                DoCast(target, SPELL_DECIMATE, true);
                            events.ScheduleEvent(EVENT_CAST_DECIMATE, urand(6000, 12000));
                        }
                        break;
                    }
                    case EVENT_CAST_FLAMES_OF_CHAOS:
                    {
                        if (UpdateVictim())
                        {
                            RESCHEDULE_IF_CASTING
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                            {
                                DoCast(target, SPELL_FLAMES_OF_CHAOS, true);
                                if (Creature* thalipedes = me->FindNearestCreature(NPC_LORAMUS_THALIPEDES, 50.0f, true))
                                {
                                    if (Player* player = thalipedes->FindNearestPlayer(200.0f, true))
                                    {
                                        if (player->HasAura(SPELL_FLAMES_OF_CHAOS_TRIGGER))
                                        {
                                            thalipedes->CastWithDelay(1500, player, SPELL_DEMON_HUNTER_RESOLVE_GRIP, false);
                                            thalipedes->AI()->TalkWithDelay(1500, 3);
                                        }
                                    }
                                }
                            }
                            events.ScheduleEvent(EVENT_CAST_FLAMES_OF_CHAOS, urand(25500, 35000));
                        }
                        break;
                    }
                    case EVENT_CAST_SUMMON_MINION:
                    {
                        if (UpdateVictim())
                        {
                            RESCHEDULE_IF_CASTING
                            DoCast(SPELL_SUMMON_MINION);
                            events.ScheduleEvent(EVENT_CAST_SUMMON_MINION, urand(15500, 45000));
                        }
                        break;
                    }
                    case EVENT_CAST_STRONG_CLEAVE:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_STRONG_CLEAVE);
                        events.ScheduleEvent(EVENT_CAST_STRONG_CLEAVE, 5000);
                        break;
                    }
                    case EVENT_SWITCH_PHASE:
                    {
                        if (me->GetHealthPct() <= 25)
                        {
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                            me->CombatStop();
                            Talk(1);
                            TalkWithDelay(3000, 2);
                            TalkWithDelay(9000, 3);
                            TalkWithDelay(15000, 4);
                            events.ScheduleEvent(EVENT_DEFILER_DIE, 18000);
                        }
                        else
                            events.ScheduleEvent(EVENT_SWITCH_PHASE, 2500);
                        break;
                    }
                    case EVENT_DEFILER_DIE:
                    {
                        if (!UpdateVictim())
                        {
                            me->SummonCreature(NPC_LORAMUS_THE_DEFILED, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                            me->Kill(me, false);
                            me->DespawnOrUnsummon(2000);
                            if (Player* player = me->FindNearestPlayer(100.0f, true))
                                player->KilledMonsterCredit(NPC_RAZELIKH_THE_DEFILER);
                            if (Creature* thalipedes = me->FindNearestCreature(NPC_LORAMUS_THALIPEDES, 100.0f, true))
                                thalipedes->DespawnOrUnsummon(1);
                        }
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
        return new npc_razelikh_the_defilerAI(creature);
    }
};

class npc_loramus_the_defiled : public CreatureScript
{
public:
    npc_loramus_the_defiled() : CreatureScript("npc_loramus_the_defiled") { }

    struct npc_loramus_the_defiledAI : public ScriptedAI
    {
        npc_loramus_the_defiledAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void Reset()
        {
            // Set protection flags
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            events.ScheduleEvent(EVENT_START_TALK, 2500);
            events.ScheduleEvent(EVENT_CHECK_HEALTH_FOR_FINISH, 2500);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CHECK_HEALTH_FOR_FINISH, 2500);
            events.ScheduleEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY_2, 3500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_TALK:
                    {
                        if (!UpdateVictim())
                        {
                            TalkWithDelay(1500, 0);
                            events.ScheduleEvent(EVENT_ENTER_COMBAT, 6000);
                        }
                        break;
                    }
                    case EVENT_ENTER_COMBAT:
                    {
                        if (!UpdateVictim())
                        {
                            // Demonic things...
                            Talk(1);

                            // Cleanup flags
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);

                            // Attack player!
                            if (Player* player = me->FindNearestPlayer(100.0f, true))
                                AttackStart(player);
                        }
                        break;
                    }
                    case EVENT_CAST_SHADOW_BOLT_VOLLEY_2:
                    {
                        if (UpdateVictim())
                        {
                            RESCHEDULE_IF_CASTING
                            DoCastVictim(SPELL_SHADOW_BOLT_VOLLEY);
                            events.ScheduleEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY_2, 6000);
                        }
                        break;
                    }
                    case EVENT_CHECK_HEALTH_FOR_FINISH:
                    {
                        if (UpdateVictim())
                        {
                            if (me->GetHealthPct() <= 10)
                                events.ScheduleEvent(EVENT_FINAL_PHASE, 1);
                            else
                                events.ScheduleEvent(EVENT_CHECK_HEALTH_FOR_FINISH, 2500);
                        }
                        break;
                    }
                    case EVENT_FINAL_PHASE:
                    {
                        if (UpdateVictim())
                        {
                            events.CancelEvent(EVENT_CHECK_HEALTH_FOR_FINISH);
                            // Set protection flags
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetControlled(true, UNIT_STATE_CANNOT_AUTOATTACK);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                            me->HandleEmoteCommand(EMOTE_STATE_DROWNED);
                            TalkWithDelay(1000, 2);
                            events.CancelEvent(EVENT_FINAL_PHASE);
                        }
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
        return new npc_loramus_the_defiledAI(creature);
    }
};

void AddSC_blasted_lands()
{
    new npc_deathly_usher();
    new npc_loramus_thalipedes();
    new npc_loramus_the_defiled();
    new npc_razelikh_the_defiler();
}
