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
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/* Automatic rescheduling if creature is already casting */
#define RESCHEDULE_IF_CASTING if (me->HasUnitState(UNIT_STATE_CASTING)) { events.ScheduleEvent(eventId, 1); break; }

class npc_th_axebite_infantry : public CreatureScript
{
public:
    npc_th_axebite_infantry() : CreatureScript("npc_th_axebite_infantry")
    {
    }

    struct npc_th_axebite_infantryAI : public ScriptedAI
    {
        npc_th_axebite_infantryAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY  = 1
        };

        enum spellId
        {
            SPELL_CHARGE        = 22120,
            SPELL_BATTLE_SHOUT  = 32064
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void EnterCombat(Unit* who)
        {
            if (!me->HasAura(SPELL_BATTLE_SHOUT))
                DoCast(SPELL_BATTLE_SHOUT);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
            DoCast(who, SPELL_CHARGE, true);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(15.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
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
        return new npc_th_axebite_infantryAI(creature);
    }
};

class npc_th_highbank_guardsman : public CreatureScript
{
public:
    npc_th_highbank_guardsman() : CreatureScript("npc_th_highbank_guardsman")
    {
    }

    struct npc_th_highbank_guardsmanAI : public ScriptedAI
    {
        npc_th_highbank_guardsmanAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1,
            EVENT_SHIELD_BASH
        };

        enum spellId
        {
            SPELL_DEMORALIZING_SHOUT    = 13730,
            SPELL_SHIELD_BASH           = 82800
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
            events.CancelEvent(EVENT_SHIELD_BASH);
        }

        void EnterCombat(Unit* who)
        {
            DoCast(SPELL_DEMORALIZING_SHOUT);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
            events.ScheduleEvent(EVENT_SHIELD_BASH, 3000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(15.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_SHIELD_BASH:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SHIELD_BASH, true);
                        events.RescheduleEvent(EVENT_SHIELD_BASH, urand(3000, 6000));
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
        return new npc_th_highbank_guardsmanAI(creature);
    }
};

class npc_th_tidebreaker_sailor : public CreatureScript
{
public:
    npc_th_tidebreaker_sailor() : CreatureScript("npc_th_tidebreaker_sailor")
    {
    }

    struct npc_th_tidebreaker_sailorAI : public ScriptedAI
    {
        npc_th_tidebreaker_sailorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1,
            EVENT_SINISTER_STRIKE
        };

        enum spellId
        {
            SPELL_SINISTER_STRIKE   = 14873
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
            events.CancelEvent(EVENT_SINISTER_STRIKE);
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_SINISTER_STRIKE, 2000);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(15.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_SINISTER_STRIKE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SINISTER_STRIKE, true);
                        events.RescheduleEvent(SPELL_SINISTER_STRIKE, urand(3000, 6000));
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
        return new npc_th_tidebreaker_sailorAI(creature);
    }
};

class npc_th_bilgewater_gunman : public CreatureScript
{
public:
    npc_th_bilgewater_gunman() : CreatureScript("npc_th_bilgewater_gunman")
    {
    }

    struct npc_th_bilgewater_gunmanAI : public ScriptedAI
    {
        npc_th_bilgewater_gunmanAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY  = 1,
            EVENT_SHOOT
        };

        enum spellId
        {
            SPELL_SHOOT     = 85710
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
            events.CancelEvent(SPELL_SHOOT);
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_SHOOT, 1);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(15.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_SHOOT:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SHOOT, true);
                        events.RescheduleEvent(SPELL_SHOOT, urand(2000, 2500));
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
        return new npc_th_bilgewater_gunmanAI(creature);
    }
};

class npc_th_fargo_near_cannon : public CreatureScript
{
public:
    npc_th_fargo_near_cannon() : CreatureScript("npc_th_fargo_near_cannon")
    {
    }

    enum questId
    {
        QUEST_AIMING_HIGH   = 28598
    };

    // TODO: This is temporary until quest aiming high will be properly scripted! (Transports etc...)
    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_AIMING_HIGH)
        {
            player->CastSpell(player, 89147, true);
            player->TeleportTo(0, -4846.79f, -6600.52f, 9.41f, 2.39f);
            return true;
        }
        return true;
    }

    struct npc_th_fargo_near_cannonAI : public ScriptedAI
    {
        npc_th_fargo_near_cannonAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SHOOT = 1
        };

        enum spellId
        {
            SPELL_SHOOT = 33808
        };

        void InitializeAI()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            if (me->GetPhaseMask() == 2)
                events.ScheduleEvent(EVENT_SHOOT, 3000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHOOT:
                    {
                        DoCast(SPELL_SHOOT);
                        events.RescheduleEvent(EVENT_SHOOT, urand(3000, 6000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_fargo_near_cannonAI(creature);
    }
};

class npc_th_cannon_powder_barrel : public CreatureScript
{
public:
    npc_th_cannon_powder_barrel() : CreatureScript("npc_th_cannon_powder_barrel")
    {
    }

    enum questId
    {
        QUEST_BURNIN_AT_BOTH_ENDS   = 28597
    };

    enum spellId
    {
        SPELL_LOOT_GUNPOWDER    = 91587
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_BURNIN_AT_BOTH_ENDS) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, SPELL_LOOT_GUNPOWDER, true);
            creature->DespawnOrUnsummon(1);
            return true;
        }
        return true;
    }
};

class npc_th_highbank_sniper : public CreatureScript
{
public:
    npc_th_highbank_sniper() : CreatureScript("npc_th_highbank_sniper")
    {
    }

    struct npc_th_highbank_sniperAI : public ScriptedAI
    {
        npc_th_highbank_sniperAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SHOOT = 1
        };

        enum spellId
        {
            SPELL_SHOOT = 33808
        };

        void InitializeAI()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.ScheduleEvent(EVENT_SHOOT, urand(1000, 6000));
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHOOT:
                    {
                        DoCast(SPELL_SHOOT);
                        events.RescheduleEvent(EVENT_SHOOT, urand(3500, 7000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_highbank_sniperAI(creature);
    }
};

class npc_th_axebite_marine : public CreatureScript
{
public:
    npc_th_axebite_marine() : CreatureScript("npc_th_axebite_marine")
    {
    }

    struct npc_th_axebite_marineAI : public ScriptedAI
    {
        npc_th_axebite_marineAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY  = 1,
            EVENT_BLOODTHIRST,
            EVENT_CLEAVE
        };

        enum spellId
        {
            SPELL_BLOODTHIRST   = 109464,
            SPELL_CLEAVE        = 15496
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
            events.CancelEvent(EVENT_CLEAVE);
            events.CancelEvent(EVENT_BLOODTHIRST);
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(SPELL_CLEAVE, 5000);
            events.ScheduleEvent(SPELL_BLOODTHIRST, 2500);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(15.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_BLOODTHIRST:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BLOODTHIRST, true);
                        events.RescheduleEvent(EVENT_BLOODTHIRST, urand(4000, 7500));
                        break;
                    }
                    case EVENT_CLEAVE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_CLEAVE, true);
                        events.RescheduleEvent(EVENT_CLEAVE, urand(3500, 8500));
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
        return new npc_th_axebite_marineAI(creature);
    }
};

class areatrigger_th_control_point : public AreaTriggerScript
{
public:
    areatrigger_th_control_point() : AreaTriggerScript("th_control_point")
    {
    }

    enum questId
    {
        QUEST_SCOUTING_THE_SHORE    = 27341
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_SCOUTING_THE_SHORE) == QUEST_STATUS_INCOMPLETE)
            player->CompleteQuest(QUEST_SCOUTING_THE_SHORE);
        return false;
    }
};

class npc_th_ophelia : public CreatureScript
{
public:
    npc_th_ophelia() : CreatureScript("npc_th_ophelia")
    {
    }

    struct npc_th_opheliaAI : public ScriptedAI
    {
        npc_th_opheliaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_UPPER    = 1,
            EVENT_MOVE_FORWARD,
            EVENT_TRANSFORM,
            EVENT_FROST_NOVA,
            EVENT_ACIDIC_SPLASH,
            EVENT_FROSTBOLT,
            EVENT_ICE_LANCE
        };

        enum pointId
        {
            POINT_UPPER     = 1,
            POINT_GROUND,
            POINT_ATTACK
        };

        enum soundId
        {
            MUSIC_QUEST_SIREN   = 23419
        };

        enum spellId
        {
            SPELL_OPHELIA_TRANSFORMATION    = 84400,
            SPELL_OPHELIA_AURA              = 84388,
            SPELL_ACIDIC_SPLASH             = 32139,
            SPELL_FROST_NOVA                = 79850,
            SPELL_FROSTBOLT                 = 79858,
            SPELL_ICE_LANCE                 = 79859
        };

        enum npcId
        {
            NPC_ENTRY_EPHRAM        = 45171,
            NPC_STRANDED_CREWMAN    = 45210,
            NPC_ENTRY_LASHED        = 45224
        };

        enum questId
        {
            QUEST_SIREN_SONG    = 27200
        };

        void JustDied(Unit* /*killer*/)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(60.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_SIREN_SONG) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->CompleteQuest(QUEST_SIREN_SONG);
                }
            }

            RespawnCrewmans();
            RespawnEphram();
            events.Reset();
            me->DespawnOrUnsummon(5000);
        }

        void RespawnEphram()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_EPHRAM, 80.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                (*iter)->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                (*iter)->Respawn(true);
            }
        }

        void RespawnCrewmans()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_STRANDED_CREWMAN, 80.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->Respawn(true);
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->HandleEmoteCommand(EMOTE_STATE_READY_SPELL_OMNI);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->SetHover(true);
            events.ScheduleEvent(EVENT_MOVE_UPPER, 6000);
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_ICE_LANCE, urand(2500, 8000));
            events.ScheduleEvent(EVENT_FROSTBOLT, urand(4000, 12000));
            events.ScheduleEvent(EVENT_FROST_NOVA, urand(6500, 9000));
            events.ScheduleEvent(EVENT_ACIDIC_SPLASH, urand(7000, 14000));
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_UPPER:
                    {
                        DoCast(me, SPELL_OPHELIA_TRANSFORMATION, true);
                        me->RemoveAurasDueToSpell(SPELL_OPHELIA_TRANSFORMATION);
                        DoCast(me, SPELL_OPHELIA_AURA, true);
                        me->HandleEmoteCommand(EMOTE_STATE_READY_SPELL_OMNI);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 7.89f, 1.0f, 1.0f, POINT_UPPER);
                        me->PlayDirectSound(MUSIC_QUEST_SIREN);
                        me->HandleEmoteCommand(EMOTE_STATE_READY_SPELL_OMNI);
                        events.CancelEvent(EVENT_MOVE_UPPER);
                        break;
                    }
                    case EVENT_MOVE_FORWARD:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-4971.44f, -6445.99f, 1.06f, 1.0f, 1.0f, POINT_GROUND);
                        events.CancelEvent(EVENT_MOVE_FORWARD);
                        break;
                    }
                    case EVENT_TRANSFORM:
                    {
                        DoCast(SPELL_OPHELIA_TRANSFORMATION);
                        me->RemoveAurasDueToSpell(SPELL_OPHELIA_AURA);
                        if (Creature* ephram = me->FindNearestCreature(NPC_ENTRY_EPHRAM, 200.0f, true))
                            ephram->AI()->Talk(6);
                        if (Creature* lashed = me->FindNearestCreature(NPC_ENTRY_LASHED, 200.0f, true))
                        {
                            if (Unit* passenger = lashed->GetVehicleKit()->GetPassenger(0))
                            {
                                passenger->ExitVehicle();
                                passenger->GetMotionMaster()->MoveJump(-4964.11f, -6446.97f, 1.74f, 20.0f, 20.0f, POINT_ATTACK);
                            }
                        }
                        KillAllCrewmans();
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->setFaction(14);
                        events.CancelEvent(EVENT_TRANSFORM);
                        break;
                    }
                    case EVENT_FROSTBOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_FROSTBOLT);
                        events.RescheduleEvent(EVENT_FROSTBOLT, urand(4000, 6000));
                        break;
                    }
                    case EVENT_FROST_NOVA:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(me, SPELL_FROST_NOVA, true);
                        events.RescheduleEvent(EVENT_FROST_NOVA, urand(8000, 18000));
                        break;
                    }
                    case EVENT_ACIDIC_SPLASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_ACIDIC_SPLASH);
                        events.RescheduleEvent(EVENT_ACIDIC_SPLASH, urand(9000, 20000));
                        break;
                    }
                    case EVENT_ICE_LANCE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_ICE_LANCE);
                        events.RescheduleEvent(EVENT_ICE_LANCE, urand(2000, 3500));
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_UPPER:
                {
                    events.ScheduleEvent(EVENT_MOVE_FORWARD, 1);
                    break;
                }
                case POINT_GROUND:
                {
                    me->HandleEmoteCommand(EMOTE_STATE_SIT);
                    events.ScheduleEvent(EVENT_TRANSFORM, 3500);
                    break;
                }
                default:
                    break;
            }
        }

        void KillAllCrewmans()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_STRANDED_CREWMAN, 30.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->Kill((*iter), false);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_opheliaAI(creature);
    }
};

class npc_th_ephram_hardstone : public CreatureScript
{
public:
    npc_th_ephram_hardstone() : CreatureScript("npc_th_ephram_hardstone")
    {
    }

    enum questId
    {
        QUEST_SIREN_SONG    = 27200
    };

    enum npcId
    {
        NPC_ENTRY_OPHELIA   = 45183,
        NPC_ENTRY_LASHED    = 45224,
        NPC_ENTRY_CREWMAN   = 45210
    };

    enum spellId
    {
        SPELL_COSMETIC_LOVE = 62011
    };

    enum actionId
    {
        ACTION_INIT_EVENT = 1
    };

    enum crewmanGUID
    {
        FIRST_CREWMAN   = 758987,
        SECOND_CREWMAN  = 758971,
        THIRD_CREWMAN   = 758985,
        FOURTH_CREWMAN  = 758972
    };

    enum pointId
    {
        POINT_PROTECTION = 1,
        POINT_FACING
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SIREN_SONG)
        {
            player->SummonCreature(NPC_ENTRY_OPHELIA, -4991.31f, -6455.29f, -2.12f, 0.42f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            creature->AI()->Talk(5);
            creature->AI()->TalkWithDelay(5000, 4);
            creature->GetMotionMaster()->MovePoint(POINT_PROTECTION, -4962.29f, -6445.81f, 1.74f);
            creature->AI()->DoAction(ACTION_INIT_EVENT);
            if (Creature* lashed = player->FindNearestCreature(NPC_ENTRY_LASHED, 200.0f, true))
                player->EnterVehicle(lashed, 0);
            return false;
        }
        return true;
    }

    struct npc_th_ephram_hardstoneAI : public ScriptedAI
    {
        npc_th_ephram_hardstoneAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_ADJUST_ORIENTATION    = 1,
            EVENT_INIT_FIRST_CREWMAN,
            EVENT_INIT_SECOND_CREWMAN,
            EVENT_INIT_THIRD_CREWMAN,
            EVENT_INIT_FOURTH_CREWMAN
        };

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT)
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ADJUST_ORIENTATION:
                    {
                        me->SetWalk(true);
                        me->SetFacingTo(3.54f);
                        me->GetMotionMaster()->MovePoint(POINT_FACING, -4965.28f, -6446.06f, 1.58f);
                        TalkWithDelay(1000, 0);
                        events.CancelEvent(EVENT_ADJUST_ORIENTATION);
                        events.ScheduleEvent(EVENT_INIT_SECOND_CREWMAN, 5000);
                        events.ScheduleEvent(EVENT_INIT_FIRST_CREWMAN, 10000);
                        events.ScheduleEvent(EVENT_INIT_FOURTH_CREWMAN, 15000);
                        events.ScheduleEvent(EVENT_INIT_THIRD_CREWMAN, 20000);
                        break;
                    }
                    case EVENT_INIT_SECOND_CREWMAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_CREWMAN, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if ((*iter)->GetGUIDLow() != SECOND_CREWMAN)
                                continue;

                            (*iter)->SetWalk(true);
                            (*iter)->SetSpeed(MOVE_WALK, 0.25f);
                            (*iter)->HandleEmoteCommand(EMOTE_STATE_STUN);
                            (*iter)->AddAura(SPELL_COSMETIC_LOVE, (*iter));
                            (*iter)->MonsterSay("She's beautiful...", 0);
                            if (Creature* ophelia = me->FindNearestCreature(NPC_ENTRY_OPHELIA, 80.0f))
                                (*iter)->GetMotionMaster()->MoveFollow(ophelia, 4, 0);
                        }
                        TalkWithDelay(3000, 1);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                        break;
                    }
                    case EVENT_INIT_FIRST_CREWMAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_CREWMAN, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if ((*iter)->GetGUIDLow() != FIRST_CREWMAN)
                                continue;

                            (*iter)->SetWalk(true);
                            (*iter)->SetSpeed(MOVE_WALK, 0.25f);
                            (*iter)->HandleEmoteCommand(EMOTE_STATE_STUN);
                            (*iter)->AddAura(SPELL_COSMETIC_LOVE, (*iter));
                            (*iter)->MonsterSay("Like an angel...", 0);
                            if (Creature* ophelia = me->FindNearestCreature(NPC_ENTRY_OPHELIA, 80.0f))
                                (*iter)->GetMotionMaster()->MoveFollow(ophelia, 4, 1);
                        }
                        TalkWithDelay(3000, 2);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_BEG);
                        break;
                    }
                    case EVENT_INIT_FOURTH_CREWMAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_CREWMAN, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if ((*iter)->GetGUIDLow() != FOURTH_CREWMAN)
                                continue;

                            (*iter)->SetWalk(true);
                            (*iter)->SetSpeed(MOVE_WALK, 0.25f);
                            (*iter)->HandleEmoteCommand(EMOTE_STATE_STUN);
                            (*iter)->AddAura(SPELL_COSMETIC_LOVE, (*iter));
                            if (Creature* ophelia = me->FindNearestCreature(NPC_ENTRY_OPHELIA, 80.0f))
                                (*iter)->GetMotionMaster()->MoveFollow(ophelia, 4, 2);
                        }
                        break;
                    }
                    case EVENT_INIT_THIRD_CREWMAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_CREWMAN, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if ((*iter)->GetGUIDLow() != THIRD_CREWMAN)
                                continue;

                            (*iter)->SetWalk(true);
                            (*iter)->SetSpeed(MOVE_WALK, 0.25f);
                            (*iter)->HandleEmoteCommand(EMOTE_STATE_STUN);
                            (*iter)->AddAura(SPELL_COSMETIC_LOVE, (*iter));
                            if (Creature* ophelia = me->FindNearestCreature(NPC_ENTRY_OPHELIA, 80.0f))
                                (*iter)->GetMotionMaster()->MoveFollow(ophelia, 4, 3);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INIT_EVENT:
                {
                    events.ScheduleEvent(EVENT_ADJUST_ORIENTATION, 9000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_ephram_hardstoneAI(creature);
    }
};

class npc_th_lightning_travel : public CreatureScript
{
public:
    npc_th_lightning_travel() : CreatureScript("npc_th_lightning_travel")
    {
    }

    enum actionId
    {
        ACTION_WP_START = 1
    };

    enum eventId
    {
    };

    enum npcId
    {
        NPC_THORDUN_HAMMERBLOW  = 45770
    };

    enum creditId
    {
        QUEST_CREDIT_WINGS_OVER_HIGHBANK    = 45767
    };

    struct npc_th_lightning_travelAI : public npc_escortAI
    {
        npc_th_lightning_travelAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            wpInProgress = false;
            me->SetCanFly(true);
            me->SetHover(true);
            me->SetDisableGravity(true);
        }

        void EnterEvadeMode()
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER && seatId == 0)
            {
                if (wpInProgress == false)
                {
                    DoAction(ACTION_WP_START);
                    wpInProgress = true;
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 2:
                {
                    if (Unit* thordrun = me->GetVehicleKit()->GetPassenger(1))
                        thordrun->ToCreature()->AI()->Talk(0);
                    break;
                }
                case 11:
                {
                    if (Unit* thordrun = me->GetVehicleKit()->GetPassenger(1))
                    {
                        thordrun->ToCreature()->AI()->Talk(1);
                        thordrun->ExitVehicle();
                        thordrun->ToCreature()->AI()->DoAction(1);
                    }
                    if (Unit* playerPassenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        playerPassenger->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WINGS_OVER_HIGHBANK);
                        me->SummonCreature(me->GetEntry(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000);
                        playerPassenger->ExitVehicle();
                    }
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
                case ACTION_WP_START:
                {
                    me->AddUnitMovementFlag(MOVEMENTFLAG_SPLINE_ELEVATION);
                    Start(false, true, NULL, NULL, false, true);
                    me->SetSpeed(MOVE_FLIGHT, 2.4f, true);
                    me->SetSpeed(MOVE_RUN, 2.4f, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        bool wpInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_lightning_travelAI(creature);
    }
};

class npc_th_thordrun_at_highbank : public CreatureScript
{
public:
    npc_th_thordrun_at_highbank() : CreatureScript("npc_th_thordrun_at_highbank")
    {
    }

    enum actionId
    {
        ACTION_WP_START = 1
    };

    struct npc_th_thordrun_at_highbankAI : public npc_escortAI
    {
        npc_th_thordrun_at_highbankAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 5:
                {
                    me->DespawnOrUnsummon(1);
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
                case ACTION_WP_START:
                {
                    Start(false, true, NULL, NULL, false, true);
                    SetDespawnAtEnd(true);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_thordrun_at_highbankAI(creature);
    }
};

class npc_th_siege_tank_commander : public CreatureScript
{
public:
    npc_th_siege_tank_commander() : CreatureScript("npc_th_siege_tank_commander")
    {
    }

    enum questId
    {
        QUEST_SIEGE_TANK_RESCUE     = 27468
    };

    enum creditId
    {
        QUEST_CREDIT_SPOKEN     = 45580,
        QUEST_CREDIT_END        = 45581
    };

    enum spellId
    {
        SPELL_SUMMON_AXEBITE    = 85214,
        SPELL_COSMETIC_EXPLODE  = 91795
    };

    enum npcId
    {
        NPC_ENTRY_ENGINEER  = 45523,
        NPC_SIEGE_TANK      = 45526
    };

    class eventExplode : public BasicEvent
    {
    public:
        explicit eventExplode(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            creature->AI()->TalkWithDelay(500, 2);
            creature->CastSpell(creature, SPELL_COSMETIC_EXPLODE, true);
            return true;
        }

    private:
        Creature* creature;
    };

    class eventSuccess : public BasicEvent
    {
    public:
        explicit eventSuccess(Creature* creature) : creature(creature)
        {
        }
        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            creature->AI()->TalkWithDelay(500, 3);
            if (Creature* siege = creature->FindNearestCreature(NPC_SIEGE_TANK, 10.0f))
            {
                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->DespawnOrUnsummon(2500);
                if (Unit* vehicle = creature->GetVehicleBase())
                {
                    vehicle->RemoveAurasDueToSpell(46598);
                    vehicle->ToCreature()->DespawnOrUnsummon(6500);
                }
                siege->GetMotionMaster()->MoveRandom(60.0f);
                siege->ToCreature()->DespawnOrUnsummon(6000);
            }
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(creature, 40.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
            creature->VisitNearbyObject(40.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_SIEGE_TANK_RESCUE) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_END);
                }
            }

            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, creature, NPC_ENTRY_ENGINEER, 15.0f);
            if (creatures.empty())
                return true;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon(5000);
            return true;
        }

    private:
        Creature* creature;
    };

    #define GOSSIP_TEXT_PARTS "Here are some spare parts. I'll cover you while you make repairs!"

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_SIEGE_TANK_RESCUE) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(QUEST_CREDIT_SPOKEN);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->AI()->Talk(0);
                creature->AI()->TalkWithDelay(5000, 1, player->GetGUID());
                creature->ChangeSeat(2, true);
                creature->m_Events.AddEvent(new eventExplode(creature), (creature)->m_Events.CalculateTime(28000));
                creature->CastWithDelay(8000, creature, SPELL_SUMMON_AXEBITE, true);
                creature->CastWithDelay(16000, creature, SPELL_SUMMON_AXEBITE, true);
                creature->CastWithDelay(24000, creature, SPELL_SUMMON_AXEBITE, true);
                creature->CastWithDelay(32000, creature, SPELL_SUMMON_AXEBITE, true);
                creature->CastWithDelay(40000, creature, SPELL_SUMMON_AXEBITE, true);
                creature->CastWithDelay(48000, creature, SPELL_SUMMON_AXEBITE, true);
                creature->AI()->TalkWithDelay(52500, 4, player->GetGUID());
                creature->m_Events.AddEvent(new eventSuccess(creature), (creature)->m_Events.CalculateTime(52000));
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_SIEGE_TANK_RESCUE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PARTS, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }
};

class npc_th_cannon_beach_triggering : public CreatureScript
{
public:
    npc_th_cannon_beach_triggering() : CreatureScript("npc_th_cannon_beach_triggering")
    {
    }

    enum npcId
    {
        NPC_ENTRY_ARTILLERY_GROUND      = 45388,
        NPC_ENTRY_ARTILLERY_GROUND_2    = 45406
    };

    enum spellId
    {
        SPELL_INCOMING_ARTILLERY    = 84841,
        SPELL_ARTILLERY_LAUNCH      = 84858
    };

    struct npc_th_cannon_beach_triggeringAI : public ScriptedAI
    {
        npc_th_cannon_beach_triggeringAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SELECT_VICTIM     = 1
        };

        void InitializeAI()
        {
            events.ScheduleEvent(EVENT_SELECT_VICTIM, 1);
        }

        void SelectGroundPoint()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_ARTILLERY_GROUND, 1000.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                // Already targeted
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY))
                    continue;

                if (roll_chance_f(40.0f))
                {
                    (*iter)->AddAura(SPELL_INCOMING_ARTILLERY, (*iter));
                    me->CastSpell((*iter), SPELL_ARTILLERY_LAUNCH, true);
                }
            }
        }

        void SelectGroundPointSecondary()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_ARTILLERY_GROUND_2, 1000.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                // Already targeted
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY))
                    continue;

                if (roll_chance_f(40.0f))
                {
                    (*iter)->AddAura(SPELL_INCOMING_ARTILLERY, (*iter));
                    me->CastSpell((*iter), SPELL_ARTILLERY_LAUNCH, true);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SELECT_VICTIM:
                    {
                        SelectGroundPoint();
                        SelectGroundPointSecondary();
                        events.RescheduleEvent(EVENT_SELECT_VICTIM, urand(15000, 30000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_cannon_beach_triggeringAI(creature);
    }
};

class npc_th_areatrigger_teleport_sw : public AreaTriggerScript
{
public:
    npc_th_areatrigger_teleport_sw() : AreaTriggerScript("th_areatrigger_teleport_sw")
    {
    }

    enum questId
    {
        QUEST_ANY_PORTAL_IN_STORM   = 27537
    };

    enum spellId
    {
        SPELL_TELEPORT_TO_STORMWIND     = 85546
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_ANY_PORTAL_IN_STORM) == QUEST_STATUS_REWARDED)
        {
            if (player->IsMounted())
                player->Dismount();
            player->CastSpell(player, SPELL_TELEPORT_TO_STORMWIND, true);
        }
        return false;
    }
};

class npc_th_firebeard_militia : public CreatureScript
{
public:
    npc_th_firebeard_militia() : CreatureScript("npc_th_firebeard_militia")
    {
    }

    struct npc_th_firebeard_militiaAI : public ScriptedAI
    {
        npc_th_firebeard_militiaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1,
            EVENT_DOUSE_FIRE
        };

        enum spellId
        {
            SPELL_DEMORALIZING_SHOUT = 13730,
            SPELL_DOUSE_FIRE         = 87269
        };

        void InitializeAI()
        {
            me->SetWalk(false);
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void EnterCombat(Unit* who)
        {
            DoCast(SPELL_DEMORALIZING_SHOUT);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(10.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
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
        return new npc_th_firebeard_militiaAI(creature);
    }
};

class npc_th_subjugated_firestarter : public CreatureScript
{
public:
    npc_th_subjugated_firestarter() : CreatureScript("npc_th_subjugated_firestarter")
    {
    }

    struct npc_th_subjugated_firestarterAI : public ScriptedAI
    {
        npc_th_subjugated_firestarterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1,
            EVENT_SCORCH,
            EVENT_FIRE_NOVA
        };

        enum spellId
        {
            SPELL_SCORCH    = 35377,
            SPELL_FIRE_NOVA = 11970
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_SCORCH, 100);
            events.ScheduleEvent(EVENT_FIRE_NOVA, 5000);
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(10.0f))
                        {
                            AttackStart(victim);
                            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_SCORCH:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SCORCH);
                        events.RescheduleEvent(EVENT_SCORCH, urand(2500, 3500));
                        break;
                    }
                    case EVENT_FIRE_NOVA:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (me->getVictim())
                            DoCast(SPELL_FIRE_NOVA);
                        events.RescheduleEvent(EVENT_FIRE_NOVA, urand(7500, 15000));
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
        return new npc_th_subjugated_firestarterAI(creature);
    }
};

class npc_th_firebeard_citizen : public CreatureScript
{
public:
    npc_th_firebeard_citizen() : CreatureScript("npc_th_firebeard_citizen")
    {
    }

    struct npc_th_firebeard_citizenAI : public ScriptedAI
    {
        npc_th_firebeard_citizenAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_FIRE  = 46849
        };

        enum eventId
        {
            EVENT_SEARCH_FOR_FIRE       = 1,
            EVENT_CHECK_FIRE_DISTANCE,
            EVENT_RECHARGE_BUCKET
        };

        enum spellId
        {
            SPELL_DOUSE_FIRE    = 87269,
            SPELL_FIRE_AURA     = 87252,
            SPELL_AURA_BUCKET   = 87270
        };

        enum pointId
        {
            POINT_FIRE      = 1,
            POINT_BUCKET
        };

        void InitializeAI()
        {
            if (me->GetPhaseMask() == 4)
            {
                isExtinguishing = false;
                me->SetReactState(REACT_PASSIVE);
                me->SetWalk(false);
                events.ScheduleEvent(EVENT_SEARCH_FOR_FIRE, 1000);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void SelectRandomFire()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_FIRE, 300.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (!roll_chance_f(25.5f))
                    continue;

                if (!(*iter)->HasAura(SPELL_FIRE_AURA))
                    continue;

                me->AddAura(SPELL_AURA_BUCKET, me);
                me->GetMotionMaster()->MovePoint(POINT_FIRE, (*iter)->GetPositionX(), (*iter)->GetPositionY(), (*iter)->GetPositionZ(), (*iter)->GetOrientation());
                events.ScheduleEvent(EVENT_CHECK_FIRE_DISTANCE, urand(2000, 3500));
                isExtinguishing = true;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_BUCKET:
                {
                    isExtinguishing = false;
                    events.ScheduleEvent(EVENT_SEARCH_FOR_FIRE, 500);
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
                    case EVENT_SEARCH_FOR_FIRE:
                    {
                        if (isExtinguishing == false)
                            SelectRandomFire();
                        events.RescheduleEvent(EVENT_SEARCH_FOR_FIRE, urand(2000, 5000));
                        break;
                    }
                    case EVENT_CHECK_FIRE_DISTANCE:
                    {
                        if (Creature* fire = me->FindNearestCreature(NPC_ENTRY_FIRE, 200.0f))
                        {
                            if (me->GetDistance(fire) < 6.5f)
                            {
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MovementExpired(false);
                                fire->CastSpell(fire, SPELL_DOUSE_FIRE, true);
                                fire->DespawnOrUnsummon(2000);
                                events.ScheduleEvent(EVENT_RECHARGE_BUCKET, 1000);
                                events.CancelEvent(EVENT_CHECK_FIRE_DISTANCE);
                                me->RemoveAurasDueToSpell(SPELL_AURA_BUCKET);
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_FIRE_DISTANCE, urand(1000, 1500));
                        break;
                    }
                    case EVENT_RECHARGE_BUCKET:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_BUCKET, -4184.25, -5603.25f, 25.67f);
                        events.CancelEvent(EVENT_RECHARGE_BUCKET);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        bool isExtinguishing;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_firebeard_citizenAI(creature);
    }
};

class npc_th_mullan_gryphon_rider : public CreatureScript
{
public:
    npc_th_mullan_gryphon_rider() : CreatureScript("npc_th_mullan_gryphon_rider")
    {
    }

    enum questId
    {
        QUEST_THE_FIGHTNING_SPIRIT  = 27810
    };

    enum creditId
    {
        QUEST_CREDIT_DUEL = 46813
    };

    enum spellId
    {
        SPELL_DEMORALIZING_SHOUT    = 13730,
        SPELL_HAMSTRING             = 9080,
        SPELL_HEROIC_STRIKE         = 57846,
        SPELL_MORTAL_STRIKE         = 32736,
        SPELL_RECKLESSNESS          = 79871,
        SPELL_START_DUEL            = 88371
    };

    enum actionId
    {
        ACTION_START_DUEL   = 1
    };

    #define GOSSIP_TEXT_DUEL "Not backing out, are you?"

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_THE_FIGHTNING_SPIRIT) == QUEST_STATUS_INCOMPLETE)
            {
                creature->AI()->TalkWithDelay(1000, 0);
                creature->AI()->TalkWithDelay(7000, 1, player->GetGUID());
                creature->AI()->TalkWithDelay(10000, 2, player->GetGUID());
                creature->AI()->TalkWithDelay(11000, 3, player->GetGUID());
                creature->AI()->TalkWithDelay(12000, 4, player->GetGUID());
                creature->AI()->DoAction(ACTION_START_DUEL);
                creature->SetFacingToObject(player);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                player->CastSpell(creature, SPELL_START_DUEL, true);
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_FIGHTNING_SPIRIT) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DUEL, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_mullan_gryphon_riderAI : public ScriptedAI
    {
        npc_th_mullan_gryphon_riderAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_START_DUEL        = 1,
            EVENT_HEROIC_STRIKE,
            EVENT_HAMSTRING,
            EVENT_MORTAL_STRIKE,
            EVENT_RECKLESSNESS,
            EVENT_CHECK_HP,
            EVENT_MOVE_AWAY
        };

        enum pointId
        {
            POINT_AWAY  = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_DUEL:
                {
                    events.ScheduleEvent(EVENT_START_DUEL, 13000);
                    break;
                }
                default:
                    break;
            }
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CHECK_HP, 500);
            events.ScheduleEvent(EVENT_HAMSTRING, 1000);
            events.ScheduleEvent(EVENT_HEROIC_STRIKE, 3000);
            events.ScheduleEvent(EVENT_MORTAL_STRIKE, 5000);
            events.ScheduleEvent(EVENT_RECKLESSNESS, 10000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_AWAY:
                {
                    me->DespawnOrUnsummon(1);
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
                    case EVENT_START_DUEL:
                    {
                        me->setFaction(14);
                        if (Player* victim = me->FindNearestPlayer(15.0f, true))
                            AttackStart(victim);
                        events.CancelEvent(EVENT_START_DUEL);
                        break;
                    }
                    case EVENT_HEROIC_STRIKE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HEROIC_STRIKE);
                        events.RescheduleEvent(EVENT_HEROIC_STRIKE, urand(3500, 5500));
                        break;
                    }
                    case EVENT_MORTAL_STRIKE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HEROIC_STRIKE);
                        events.RescheduleEvent(EVENT_MORTAL_STRIKE, urand(6000, 8500));
                        break;
                    }
                    case EVENT_RECKLESSNESS:
                    {
                        DoCast(SPELL_RECKLESSNESS);
                        events.RescheduleEvent(EVENT_RECKLESSNESS, 20000);
                        break;
                    }
                    case EVENT_HAMSTRING:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HAMSTRING);
                        events.RescheduleEvent(EVENT_HAMSTRING, urand(2000, 10000));
                        break;
                    }
                    case EVENT_CHECK_HP:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.30f)
                        {
                            if (me->getVictim() && me->getVictim()->GetTypeId() == TYPEID_PLAYER)
                                me->getVictim()->ToPlayer()->KilledMonsterCredit(46813);

                            me->setFaction(2339);
                            me->CombatStop();
                            me->ClearInCombat();
                            me->getHostileRefManager().clearReferences();
                            me->getThreatManager().clearReferences();
                            Talk(5);
                            me->HandleEmoteCommand(EMOTE_ONESHOT_BEG);
                            events.CancelEvent(EVENT_CHECK_HP);
                            events.ScheduleEvent(EVENT_MOVE_AWAY, 6000);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_HP, 500);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -4251.37f, -5119.43f, 12.18f);
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        events.CancelEvent(EVENT_MOVE_AWAY);
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
        return new npc_th_mullan_gryphon_riderAI(creature);
    }
};

void AddSC_twilight_highlands()
{
    new npc_th_axebite_infantry();
    new npc_th_highbank_guardsman();
    new npc_th_tidebreaker_sailor();
    new npc_th_bilgewater_gunman();
    new npc_th_fargo_near_cannon();
    new npc_th_cannon_powder_barrel();
    new npc_th_highbank_sniper();
    new npc_th_axebite_marine();
    new areatrigger_th_control_point();
    new npc_th_ophelia();
    new npc_th_ephram_hardstone();
    new npc_th_lightning_travel();
    new npc_th_thordrun_at_highbank();
    new npc_th_siege_tank_commander();
    new npc_th_cannon_beach_triggering();
    new npc_th_areatrigger_teleport_sw();
    new npc_th_firebeard_militia();
    new npc_th_subjugated_firestarter();
    new npc_th_firebeard_citizen();
    new npc_th_mullan_gryphon_rider();
}
