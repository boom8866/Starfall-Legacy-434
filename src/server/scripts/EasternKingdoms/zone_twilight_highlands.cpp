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
        NPC_ENTRY_ARTILLERY_GROUND_2    = 45406,
        NPC_ENTRY_ARTILLERY_GROUND_3    = 38821
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
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_ARTILLERY_GROUND, 600.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                // Already targeted
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY))
                    continue;

                if (roll_chance_f(25.0f))
                {
                    (*iter)->AddAura(SPELL_INCOMING_ARTILLERY, (*iter));
                    me->CastSpell((*iter), SPELL_ARTILLERY_LAUNCH, true);
                }
            }
        }

        void SelectGroundPointSecondary()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_ARTILLERY_GROUND_2, 600.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                // Already targeted
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY))
                    continue;

                if (roll_chance_f(25.0f))
                {
                    (*iter)->AddAura(SPELL_INCOMING_ARTILLERY, (*iter));
                    me->CastSpell((*iter), SPELL_ARTILLERY_LAUNCH, true);
                }
            }
        }

        void SelectGroundPointOptional()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_ARTILLERY_GROUND_3, 600.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                // Already targeted
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY))
                    continue;

                if (roll_chance_f(10.0f))
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
                        SelectGroundPointOptional();
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
                if (!roll_chance_f(5.0f))
                    continue;

                if (!(*iter)->HasAura(SPELL_FIRE_AURA))
                    continue;

                if ((*iter)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                    continue;

                me->AddAura(SPELL_AURA_BUCKET, me);
                me->GetMotionMaster()->MovePoint(POINT_FIRE, (*iter)->GetPositionX(), (*iter)->GetPositionY(), (*iter)->GetPositionZ(), (*iter)->GetOrientation());
                (*iter)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                events.ScheduleEvent(EVENT_CHECK_FIRE_DISTANCE, 5000);
                isExtinguishing = true;
                return;
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
                        {
                            SelectRandomFire();
                            events.CancelEvent(EVENT_SEARCH_FOR_FIRE);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_FIRE, urand(2000, 5000));
                        break;
                    }
                    case EVENT_CHECK_FIRE_DISTANCE:
                    {
                        if (Creature* fire = me->FindNearestCreature(NPC_ENTRY_FIRE, 200.0f))
                        {
                            if (fire->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                            {
                                isExtinguishing = false;
                                events.RescheduleEvent(EVENT_SEARCH_FOR_FIRE, 500);
                                events.CancelEvent(EVENT_CHECK_FIRE_DISTANCE);
                                break;
                            }
                            if (me->GetDistance(fire) < 8.0f)
                            {
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MovementExpired(false);
                                fire->CastSpell(fire, SPELL_DOUSE_FIRE, true);
                                me->CastSpell(fire, SPELL_DOUSE_FIRE, true);
                                fire->DespawnOrUnsummon(3000);
                                events.ScheduleEvent(EVENT_RECHARGE_BUCKET, 1000);
                                events.CancelEvent(EVENT_CHECK_FIRE_DISTANCE);
                                me->RemoveAurasDueToSpell(SPELL_AURA_BUCKET);
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_FIRE_DISTANCE, urand(1500, 2000));
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

class npc_th_mullan_gryphon_trapped : public CreatureScript
{
public:
    npc_th_mullan_gryphon_trapped() : CreatureScript("npc_th_mullan_gryphon_trapped")
    {
    }

    enum creditId
    {
        QUEST_CREDIT_FREED  = 46968
    };

    enum spellId
    {
        SPELL_COSMETIC_CHAINS   = 75844
    };

    struct npc_th_mullan_gryphon_trappedAI : public ScriptedAI
    {
        npc_th_mullan_gryphon_trappedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_ENABLE_TRAPS      = 1,
            EVENT_CHECK_FOR_TRAPS,
            EVENT_MOVE_AWAY,
            EVENT_RANDOM_EMOTE
        };

        enum pointId
        {
            POINT_AWAY  = 1
        };

        enum npcId
        {
            NPC_ENTRY_TRAPS = 46975
        };

        enum questId
        {
            QUEST_THE_SCENT_OF_BATTLE   = 27811
        };

        void RewardNearbyPlayers()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 30.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(30.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_SCENT_OF_BATTLE) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FREED);
                }
            }
        }

        void EnableTraps()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_TRAPS, 10.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (!(*iter)->isAlive())
                    (*iter)->Respawn(true);

                (*iter)->CastWithDelay(2000, me, SPELL_COSMETIC_CHAINS, true);
            }
        }

        void CheckDeadTraps()
        {
            killedTrapCount = 0;
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_TRAPS, 10.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (!(*iter)->isAlive())
                    killedTrapCount++;

                if (killedTrapCount >= 4)
                    isStillTrapped = false;
            }
        }

        void Reset()
        {
            isStillTrapped = true;
            killedTrapCount = 0;
            me->SetReactState(REACT_PASSIVE);
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetHover(false);
            events.ScheduleEvent(EVENT_ENABLE_TRAPS, 2000);
            events.ScheduleEvent(EVENT_CHECK_FOR_TRAPS, 1500);
            events.ScheduleEvent(EVENT_RANDOM_EMOTE, 1500);
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
                    case EVENT_RANDOM_EMOTE:
                    {
                        if (Player* player = me->FindNearestPlayer(15.0f, true))
                        {
                            Talk(0);
                            events.RescheduleEvent(EVENT_RANDOM_EMOTE, urand(20000, 30000));
                            break;
                        }
                        events.RescheduleEvent(EVENT_RANDOM_EMOTE, 20000);
                        break;
                    }
                    case EVENT_CHECK_FOR_TRAPS:
                    {
                        CheckDeadTraps();
                        if (isStillTrapped == true)
                            events.RescheduleEvent(EVENT_CHECK_FOR_TRAPS, 1000);
                        else
                        {
                            Talk(1);
                            events.CancelEvent(EVENT_CHECK_FOR_TRAPS);
                            events.ScheduleEvent(EVENT_MOVE_AWAY, 5000);
                        }
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);
                        me->SetWalk(false);
                        me->SetSpeed(MOVE_RUN, 2.0f, true);
                        me->SetSpeed(MOVE_FLIGHT, 2.0f, true);
                        me->RemoveAllAuras();
                        RewardNearbyPlayers();
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -4327.76f, -5549.32f, 149.03f);
                        killedTrapCount = 0;
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        break;
                    }
                    case EVENT_ENABLE_TRAPS:
                    {
                        EnableTraps();
                        events.CancelEvent(EVENT_ENABLE_TRAPS);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        protected:
            bool isStillTrapped;
            uint8 killedTrapCount;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_mullan_gryphon_trappedAI(creature);
    }
};

class npc_th_mullan_gryphon_injuried : public CreatureScript
{
public:
    npc_th_mullan_gryphon_injuried() : CreatureScript("npc_th_mullan_gryphon_injuried")
    {
    }

    enum questId
    {
        QUEST_THE_SCENT_OF_BATTLE   = 27811
    };

    enum pointId
    {
        POINT_AWAY = 1
    };

    enum creditId
    {
        QUEST_CREDIT_HEAL   = 46968
    };

    #define GOSSIP_TEXT_HEAL "Let the gryphon smell the piece of charred highland birch."

    class eventFlyAway : public BasicEvent
    {
    public:
        explicit eventFlyAway(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            creature->GetMotionMaster()->MovePoint(POINT_AWAY, -4327.76f, -5549.32f, 149.03f);
            return true;
        }

    private:
        Creature* creature;
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_THE_SCENT_OF_BATTLE) == QUEST_STATUS_INCOMPLETE)
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->SetCanFly(true);
                creature->SetDisableGravity(true);
                creature->SetHover(true);
                creature->SetSpeed(MOVE_RUN, 2.0f, true);
                creature->SetSpeed(MOVE_FLIGHT, 2.0f, true);
                creature->SetWalk(false);
                player->KilledMonsterCredit(QUEST_CREDIT_HEAL);
                creature->m_Events.AddEvent(new eventFlyAway(creature), (creature)->m_Events.CalculateTime(3000));
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_SCENT_OF_BATTLE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HEAL, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_mullan_gryphon_injuriedAI : public ScriptedAI
    {
        npc_th_mullan_gryphon_injuriedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_AWAY:
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->SetHover(false);
                    me->DespawnOrUnsummon(200);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_mullan_gryphon_injuriedAI(creature);
    }
};

class npc_th_firebeard_gryphon_mount : public CreatureScript
{
public:
    npc_th_firebeard_gryphon_mount() : CreatureScript("npc_th_firebeard_gryphon_mount")
    {
    }

    enum questId
    {
        QUEST_DROPPING_THE_HAMMER   = 27817
    };

    enum spellId
    {
        SPELL_SUMMON_FIREBEARD_GRYPHON  = 88258
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_DROPPING_THE_HAMMER) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, SPELL_SUMMON_FIREBEARD_GRYPHON, true);
        return true;
    }
};

class npc_th_firebeard_gryphon_summoned : public CreatureScript
{
public:
    npc_th_firebeard_gryphon_summoned() : CreatureScript("npc_th_firebeard_gryphon_summoned")
    {
    }

    enum actionId
    {
        ACTION_WP_START     = 1,
        ACTION_INC_KILL,
        ACTION_DISMOUNT,
        ACTION_WP_RETURN
    };

    enum eventId
    {
        EVENT_CHECK_KILL_COUNTER    = 1,
        EVENT_MOVE_JUMP_1,
        EVENT_MOVE_JUMP_2
    };

    enum pointId
    {
        POINT_END       = 49,
        POINT_RETURN
    };

    struct npc_th_firebeard_gryphon_summonedAI : public npc_escortAI
    {
        npc_th_firebeard_gryphon_summonedAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            wpInProgress = false;
            questCredited = false;
            bossUnder50 = false;
            killCounter = 0;
        }

        void EnterEvadeMode()
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER && seatId == 1)
            {
                if (wpInProgress == false)
                {
                    if (me->GetPositionZ() > 230.0f)
                        DoAction(ACTION_WP_RETURN);
                    else
                        DoAction(ACTION_WP_START);
                    wpInProgress = true;
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 4:     // First talk with icon
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                        Talk(0, owner->GetGUID());
                    break;
                }
                case 11:    // In case of quest credited
                {
                    if (questCredited == true)
                        SetNextWaypoint(12, true);
                    else
                        SetNextWaypoint(4, false);
                    break;
                }
                case 18:    // Check for Boss HP
                {
                    if (questCredited == true)
                    {
                        if (Creature* boss = me->FindNearestCreature(46839, 100.0f))
                        {
                            if (boss->GetHealth() > boss->GetMaxHealth() * 0.50f)
                                SetNextWaypoint(13, true);
                            else
                            {
                                me->GetMotionMaster()->MovementExpired(false);
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MoveJump(-3971.09f, -5538.34f, 236.33f, 20.0f, 20.0f, 30);
                                me->DespawnOrUnsummon(2500);
                            }
                        }
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
                    Start(false, true, NULL, NULL, false, true);
                    events.ScheduleEvent(EVENT_CHECK_KILL_COUNTER, 5000);
                    me->SetSpeed(MOVE_FLIGHT, 1.8f, true);
                    me->SetSpeed(MOVE_RUN, 1.8f, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                case ACTION_INC_KILL:
                {
                    killCounter++;
                    break;
                }
                case ACTION_DISMOUNT:
                {
                    bossUnder50 = true;
                    break;
                }
                case ACTION_WP_RETURN:
                {
                    events.ScheduleEvent(EVENT_MOVE_JUMP_1, 1000);
                    me->DespawnOrUnsummon(20000);
                    me->SetCanFly(true);
                    me->SetSpeed(MOVE_FLIGHT, 2.5f, true);
                    me->SetSpeed(MOVE_RUN, 2.5f, true);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_KILL_COUNTER:
                    {
                        if (killCounter >= 12)
                        {
                            questCredited = true;
                            if (Unit* owner = me->GetCharmerOrOwner())
                                Talk(1, owner->GetGUID());
                            events.CancelEvent(EVENT_CHECK_KILL_COUNTER);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_KILL_COUNTER, 2000);
                        break;
                    }
                    case EVENT_MOVE_JUMP_1:
                    {
                        me->GetMotionMaster()->MoveJump(-4001.78f, -5546.88f, 256.21f, 18.5f, 18.5f, POINT_RETURN);
                        events.ScheduleEvent(EVENT_MOVE_JUMP_2, 1000);
                        events.CancelEvent(EVENT_MOVE_JUMP_1);
                        break;
                    }
                    case EVENT_MOVE_JUMP_2:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_END, -4182.16f, -5602.01f, 29.13f);
                        events.CancelEvent(EVENT_MOVE_JUMP_2);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool wpInProgress;
        bool questCredited;
        bool bossUnder50;
        uint8 killCounter;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_firebeard_gryphon_summonedAI(creature);
    }
};

class npc_th_twilight_stormbender : public CreatureScript
{
public:
    npc_th_twilight_stormbender() : CreatureScript("npc_th_twilight_stormbender")
    {
    }

    struct npc_th_twilight_stormbenderAI : public ScriptedAI
    {
        npc_th_twilight_stormbenderAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_STATIC_CHARGE     = 1,
            EVENT_TWILIGHT_BOLT,
            EVENT_THUNDERSTORM,
            EVENT_CHECK_PLAYERS,
            EVENT_CHECK_COMBAT
        };

        enum spellId
        {
            SPELL_STATIC_CHARGE     = 88043,
            SPELL_TWILIGHT_BOLT     = 88106,
            SPELL_THUNDERSTORM      = 53071,
            SPELL_TWILIGHT_CHANNEL  = 88113
        };

        void Reset()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->CastSpell(me, SPELL_TWILIGHT_CHANNEL, true);
            if (!me->isInCombat())
                events.ScheduleEvent(EVENT_CHECK_PLAYERS, 1000);
        }

        void JustDied(Unit* killer)
        {
            if (killer->GetTypeId() == TYPEID_UNIT)
            {
                if (killer->ToCreature())
                    killer->ToCreature()->AI()->DoAction(2);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_STATIC_CHARGE, urand(3000, 7000));
            events.ScheduleEvent(EVENT_TWILIGHT_BOLT, 4100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PLAYERS:
                    {
                        if (Player* player = me->FindNearestPlayer(60.0f, true))
                        {
                            AttackStart(player);
                            me->CastStop();
                            me->RemoveAllAuras();
                            events.CancelEvent(EVENT_CHECK_PLAYERS);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_PLAYERS, 2000);
                        break;
                    }
                    case EVENT_STATIC_CHARGE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (roll_chance_f(30.0f))
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (!victim->HasAura(SPELL_STATIC_CHARGE))
                                    DoCast(victim, SPELL_STATIC_CHARGE);
                            }
                        }
                        events.RescheduleEvent(EVENT_STATIC_CHARGE, urand(6500, 12000));
                        break;
                    }
                    case EVENT_TWILIGHT_BOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_TWILIGHT_BOLT);
                        events.RescheduleEvent(EVENT_TWILIGHT_BOLT, urand(6000, 15000));
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
        return new npc_th_twilight_stormbenderAI(creature);
    }
};

class npc_th_servias_windterror : public CreatureScript
{
public:
    npc_th_servias_windterror() : CreatureScript("npc_th_servias_windterror")
    {
    }

    struct npc_th_servias_windterrorAI : public ScriptedAI
    {
        npc_th_servias_windterrorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_STATIC_FLUX               = 1,
            EVENT_COMING_OF_THE_WINDTERROR,
            EVENT_CHECK_HEALTH,
            EVENT_CHECK_PLAYERS
        };

        enum spellId
        {
            SPELL_COMING_OF_THE_WINDTERROR  = 88247,
            SPELL_STATIC_FLUX               = 88189,
            SPELL_CALL_GRYPHON              = 88258
        };

        enum questId
        {
            QUEST_DROPPING_THE_HAMMER   = 27817
        };

        void InformPlayersToReturn()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(60.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    if ((*itr)->GetPositionZ() < 235.0f)
                        continue;

                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_DROPPING_THE_HAMMER) != QUEST_STATUS_NONE)
                    {
                        (*itr)->ToPlayer()->KilledMonsterCredit(me->GetEntry());
                        if (!(*itr)->GetVehicle())
                            (*itr)->CastWithDelay(5000, (*itr), SPELL_CALL_GRYPHON, true);
                    }
                }
            }
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_CHECK_PLAYERS, 2000);
            me->SetHealth(me->GetMaxHealth());
        }

        void JustDied(Unit* /*killer*/)
        {
            InformPlayersToReturn();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_STATIC_FLUX, 4000);
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_STATIC_FLUX:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                        {
                            if (me->GetHealth() <= me->GetMaxHealth() * 0.50f)
                                DoCast(victim, SPELL_STATIC_FLUX);
                        }
                        events.RescheduleEvent(EVENT_STATIC_FLUX, 6000);
                        break;
                    }
                    case EVENT_COMING_OF_THE_WINDTERROR:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.CancelEvent(EVENT_STATIC_FLUX);
                        events.CancelEvent(EVENT_COMING_OF_THE_WINDTERROR);
                        break;
                    }
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.50f)
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (Vehicle* vehicle = victim->GetVehicle())
                                {
                                    me->CastStop();
                                    vehicle->GetBase()->ToCreature()->AI()->DoAction(3);
                                }
                            }
                            events.ScheduleEvent(EVENT_COMING_OF_THE_WINDTERROR, 30000);
                            events.CancelEvent(EVENT_CHECK_HEALTH);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_HEALTH, 2000);
                        break;
                    }
                    case EVENT_CHECK_PLAYERS:
                    {
                        if (Player* player = me->FindNearestPlayer(35.0f, true))
                        {
                            AttackStart(player);
                            me->CastStop();
                            me->RemoveAllAuras();
                            events.CancelEvent(EVENT_CHECK_PLAYERS);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_PLAYERS, 2000);
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
        return new npc_th_servias_windterrorAI(creature);
    }
};

class go_th_sacred_ale_tap : public GameObjectScript
{
public:
    go_th_sacred_ale_tap() : GameObjectScript("go_th_sacred_ale_tap")
    {
    }

    enum questId
    {
        QUEST_ANYTHING_BUT_WATER = 27647
    };

    enum npcId
    {
        NPC_TWILIGHT_AMBUSHER       = 46527,
        NPC_TWILIGHT_SHADOWPROWLER  = 46526,
        NPC_EOIN_DUNWALD            = 46583
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_ANYTHING_BUT_WATER) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* ambusher = player->FindNearestCreature(NPC_TWILIGHT_AMBUSHER, 50.0f);
            Creature* shadowprowler = player->FindNearestCreature(NPC_TWILIGHT_AMBUSHER, 50.0f);
            Creature* eoin = player->FindNearestCreature(NPC_EOIN_DUNWALD, 50.0f);
            if (!ambusher && !shadowprowler)
            {
                player->SummonCreature(NPC_TWILIGHT_AMBUSHER, -4605.53f, -5211.01f, 99.59f, 5.45f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000);
                player->SummonCreature(NPC_TWILIGHT_AMBUSHER, -4619.95f, -5225.50f, 99.36f, 5.46f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000);
                if (!eoin)
                {
                    player->SummonCreature(NPC_EOIN_DUNWALD, -4628.08f, -5200.02f, 108.56f, 4.50f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    player->SummonCreature(NPC_TWILIGHT_SHADOWPROWLER, -4628.34f, -5202.90f, 108.48f, 1.53f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
                return false;
            }
        }
        return false;
    }
};

class npc_th_cayden_dunwald_escort : public CreatureScript
{
public:
    npc_th_cayden_dunwald_escort() : CreatureScript("npc_th_cayden_dunwald_escort")
    {
    }

    enum actionId
    {
        ACTION_WP_START = 1
    };

    enum questId
    {
        QUEST_ONCE_MORE_INTO_THE_FIRE   = 27648
    };

    enum eventId
    {
        EVENT_START_WP  = 1
    };

    enum spellId
    {
        QUEST_CREDIT_AOE    = 86417
    };

    enum npcId
    {
        NPC_TWILIGHT_PILLAGER   = 46144
    };

    #define GOSSIP_TEXT_ESCORT_4 "Well, let's get to it then."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ONCE_MORE_INTO_THE_FIRE) == QUEST_STATUS_INCOMPLETE)
            {
                creature->AI()->TalkWithDelay(2000, 0);
                creature->AI()->DoAction(ACTION_WP_START);
                creature->setFaction(player->getFaction());
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ONCE_MORE_INTO_THE_FIRE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ESCORT_4, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_cayden_dunwald_escortAI : public npc_escortAI
    {
        npc_th_cayden_dunwald_escortAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void CompleteAoE()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_ONCE_MORE_INTO_THE_FIRE) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->CastSpell((*itr), QUEST_CREDIT_AOE, true);
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 3: // First Attack
                {
                    // SUMMON NPC
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4689.94f, -4886.74f, 155.44f, 2.97f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4719.35f, -4873.33f, 162.89f, 5.56f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4710.73f, -4900.25f, 156.03f, 1.59f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    break;
                }
                case 4: // Just Talk
                {
                    Talk(1);
                    break;
                }
                case 5: // Second Attack
                {
                    // SUMMON NPC
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4726.93f, -4899.02f, 156.31f, 4.90f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4709.70f, -4894.68f, 156.12f, 3.93f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4710.07f, -4909.15f, 156.86f, 2.92f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    break;
                }
                case 6: // Just Talk
                {
                    Talk(2);
                    break;
                }
                case 7: // Final Attack
                {
                    // SUMMON NPC
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4746.52f, -4944.83f, 158.10f, 2.53f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4756.97f, -4929.38f, 158.74f, 5.82f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    me->SummonCreature(NPC_TWILIGHT_PILLAGER, -4761.84f, -4944.80f, 158.63f, 0.75f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    break;
                }
                case 8: // Just Talk
                {
                    Talk(3);
                    break;
                }
                case 9: // Finish
                {
                    CompleteAoE();
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->DespawnOrUnsummon(60000);
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
                    me->RemoveAllAuras();
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    events.ScheduleEvent(EVENT_START_WP, 2500);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_WP:
                    {
                        Start(true, true, NULL, NULL, false, false);
                        SetDespawnAtEnd(false);
                        SetDespawnAtFar(false);
                        me->SetReactState(REACT_AGGRESSIVE);
                        events.CancelEvent(EVENT_START_WP);
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
        return new npc_th_cayden_dunwald_escortAI(creature);
    }
};

class areatrigger_th_south_dunwald_hovel : public AreaTriggerScript
{
public:
    areatrigger_th_south_dunwald_hovel() : AreaTriggerScript("th_south_dunwald_hovel")
    {
    }

    enum questId
    {
        QUEST_FINDING_BEAK  = 27646,
        CREDIT_FINDING      = 46599
    };

    enum spellId
    {
        SPELL_SUMMON_BEAK   = 87011
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_FINDING_BEAK) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(CREDIT_FINDING);
            player->MonsterWhisper("Someone took refuge here after the attack, but no sign of Beak.", player->GetGUID(), true);
        }
        if (player->isAlive() && player->GetQuestStatus(QUEST_FINDING_BEAK) == QUEST_STATUS_COMPLETE)
            player->CastSpell(player, SPELL_SUMMON_BEAK, true);
        return false;
    }
};

class areatrigger_th_north_dunwald_hovel : public AreaTriggerScript
{
public:
    areatrigger_th_north_dunwald_hovel() : AreaTriggerScript("th_north_dunwald_hovel")
    {
    }

    enum questId
    {
        QUEST_FINDING_BEAK  = 27646,
        CREDIT_FINDING      = 46599
    };

    enum spellId
    {
        SPELL_SUMMON_BEAK   = 87011
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_FINDING_BEAK) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(CREDIT_FINDING + 1);
            player->MonsterWhisper("This room reeks of a massacre. No sign of Beak.", player->GetGUID(), true);
        }
        if (player->isAlive() && player->GetQuestStatus(QUEST_FINDING_BEAK) == QUEST_STATUS_COMPLETE)
            player->CastSpell(player, SPELL_SUMMON_BEAK, true);
        return false;
    }
};

class areatrigger_th_east_dunwald_hovel : public AreaTriggerScript
{
public:
    areatrigger_th_east_dunwald_hovel() : AreaTriggerScript("th_east_dunwald_hovel")
    {
    }

    enum questId
    {
        QUEST_FINDING_BEAK  = 27646,
        CREDIT_FINDING      = 46599
    };

    enum spellId
    {
        SPELL_SUMMON_BEAK   = 87011
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_FINDING_BEAK) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(CREDIT_FINDING + 2);
            player->MonsterWhisper("These buildings lie entirely in ruin. Nowhere for Beak to hide here.", player->GetGUID(), true);
        }
        if (player->isAlive() && player->GetQuestStatus(QUEST_FINDING_BEAK) == QUEST_STATUS_COMPLETE)
            player->CastSpell(player, SPELL_SUMMON_BEAK, true);
        return false;
    }
};

class npc_th_eye_of_twilight_spy : public CreatureScript
{
public:
    npc_th_eye_of_twilight_spy() : CreatureScript("npc_th_eye_of_twilight_spy")
    {
    }

    enum questId
    {
        QUEST_EYE_SPY   = 28244
    };

    enum npcId
    {
        NPC_EYE_OF_TWILIGHT_VEHICLE     = 47273
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_EYE_SPY) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(60191, player);
            player->SummonCreature(NPC_EYE_OF_TWILIGHT_VEHICLE, -3183.00f, -5059.83f, 120.99f, 6.01f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }
        return true;
    }
};

class npc_th_eye_of_twilight_veh : public CreatureScript
{
public:
    npc_th_eye_of_twilight_veh() : CreatureScript("npc_th_eye_of_twilight_veh")
    {
    }

    struct npc_th_eye_of_twilight_vehAI : public ScriptedAI
    {
        npc_th_eye_of_twilight_vehAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER          = 1,
            EVENT_TELEPORT_TO_CHOGALL,
            EVENT_POINT_CHOGALL,
            EVENT_FOCUS_MOUNTAIN,
            EVENT_DONE
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552
        };

        enum questId
        {
            QUEST_EYE_SPY   = 28244
        };

        enum pointId
        {
            POINT_CITADEL   = 1,
            POINT_CHOGALL,
            POINT_ESCAPE_1  = 6
        };

        enum npcId
        {
            NPC_CHO_GALL    = 48142,
            NPC_SHAMAN      = 48010,
            NPC_EYE         = 48116,
            NPC_SERVANT     = 48145,
            NPC_BLINDEYE    = 46399,
            NPC_MOUNTAIN    = 46732,
            NPC_CAM_TARGET  = 51039
        };

        class eventFakeAttack : public BasicEvent
        {
        public:
            explicit eventFakeAttack(Creature* creature) : creature(creature)
            {
            }

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                creature->DespawnOrUnsummon(10000);
                return true;
            }

        private:
            Creature* creature;
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ESCAPE_1:
                {
                    if (Unit* player = me->ToTempSummon()->GetSummoner())
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_BLINDEYE, 200.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (!(*iter)->ToTempSummon())
                                continue;

                            if ((*iter)->ToTempSummon()->GetSummoner() == player)
                            {
                                me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                (*iter)->m_Events.AddEvent(new eventFakeAttack((*iter)), ((*iter))->m_Events.CalculateTime(2500));
                                events.ScheduleEvent(EVENT_FOCUS_MOUNTAIN, 3500);
                            }
                        }

                        if (Creature* cameraTarget = me->FindNearestCreature(NPC_CAM_TARGET, 200.0f, true))
                        {
                            me->CastStop();
                            me->CastSpell(cameraTarget, SPELL_CAMERA_CHANNELING, true);
                        }
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
                    case EVENT_RIDE_INVOKER:
                    {
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                        if (me->ToTempSummon())
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if (invoker->GetDistance(me) < 10.0f)
                                    invoker->EnterVehicle(me, 0);
                                else
                                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);

                                Creature* blundy = me->FindNearestCreature(NPC_SHAMAN, 40.0f);
                                if (blundy)
                                    events.ScheduleEvent(EVENT_TELEPORT_TO_CHOGALL, 5000);
                                else
                                    events.ScheduleEvent(EVENT_POINT_CHOGALL, 5000);
                            }
                        }
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        break;
                    }
                    case EVENT_TELEPORT_TO_CHOGALL:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            me->NearTeleportTo(-5095.94f, -4661.88f, 356.40f, 3.66f);
                            me->Relocate(-5095.94f, -4661.88f, 356.40f, 3.66f);
                            player->ExitVehicle();
                            player->NearTeleportTo(-5095.94f, -4661.88f, 356.40f, 3.66f);
                            player->SummonCreature(NPC_EYE, -5100.89f, -4664.92f, 356.40f, 0.39f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(me->GetEntry(), -5095.94f, -4661.88f, 356.40f, 3.66f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            player->SummonCreature(me->GetEntry(), -5084.03f, -4677.52f, 364.45f, 2.09f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            player->SummonCreature(NPC_CHO_GALL, -5084.99f, -4676.94f, 357.67f, 2.01f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            player->SummonCreature(NPC_SERVANT, -5094.93f, -4657.10f, 356.50f, 5.16f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            me->DespawnOrUnsummon(1);
                        }
                        events.CancelEvent(EVENT_TELEPORT_TO_CHOGALL);
                        break;
                    }
                    case EVENT_POINT_CHOGALL:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, me->GetEntry(), 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter) == me)
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    player->ChangeSeat(1, true);
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_POINT_CHOGALL);
                        break;
                    }
                    case EVENT_FOCUS_MOUNTAIN:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_MOUNTAIN, 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    me->CastStop();
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                    (*iter)->m_Events.AddEvent(new eventFakeAttack((*iter)), ((*iter))->m_Events.CalculateTime(2500));
                                    events.ScheduleEvent(EVENT_DONE, 4000);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_FOCUS_MOUNTAIN);
                        break;
                    }
                    case EVENT_DONE:
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                        {
                            vehicle->RemoveAllPassengers();
                            me->DespawnOrUnsummon(5000);
                        }
                        events.CancelEvent(EVENT_DONE);
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
        return new npc_th_eye_of_twilight_vehAI(creature);
    }
};

class npc_th_eye_spy_twilight_servant : public CreatureScript
{
public:
    npc_th_eye_spy_twilight_servant() : CreatureScript("npc_th_eye_spy_twilight_servant")
    {
    }

    struct npc_th_eye_spy_twilight_servantAI : public ScriptedAI
    {
        npc_th_eye_spy_twilight_servantAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_CHOGALL   = 1,
            EVENT_KNEEL_AND_TALK,
            EVENT_ENABLE_CHOGALL,
            EVENT_SERVANT_TAKE_EYE,
            EVENT_RETURN_TO_CHOGALL,
            EVENT_PLACE_EYE,
            EVENT_UNCOVERED,
            EVENT_MOVE_CAMERA,
            EVENT_CHOGALL_FINAL,
            EVENT_FINALIZE
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING = 88552,
            SPELL_CARRY_EYE         = 88237,
            SPELL_SHADOW_CHANNELING = 74036
        };

        enum pointId
        {
            POINT_CHOGALL   = 1,
            POINT_EYE,
            POINT_CHOGALL_2,
            POINT_DISTANT,
            POINT_FACE,
            POINT_ESCAPE_1,
            POINT_ESCAPE_2
        };

        enum npcId
        {
            NPC_CHO_GALL    = 48142,
            NPC_EYE         = 48116,
            NPC_EYE_VEH     = 47273,
            NPC_BLINDEYE    = 46399,
            NPC_MOUNTAIN    = 46732
        };

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void Reset()
        {
            me->SetWalk(true);
            events.ScheduleEvent(EVENT_MOVE_TO_CHOGALL, 3000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CHOGALL:
                {
                    events.ScheduleEvent(EVENT_KNEEL_AND_TALK, 100);
                    break;
                }
                case POINT_EYE:
                {
                    me->SetWalk(true);
                    me->AddAura(SPELL_CARRY_EYE, me);
                    if (Unit* player = me->ToTempSummon()->GetSummoner())
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_EYE, 200.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (!(*iter)->ToTempSummon())
                                continue;

                            if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                (*iter)->DespawnOrUnsummon(1);
                        }
                    }
                    break;
                }
                case POINT_CHOGALL_2:
                {
                    me->SetFacingTo(5.47f);
                    break;
                }
                case POINT_DISTANT:
                {
                    me->SetFacingTo(0.77f);
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
                    case EVENT_MOVE_TO_CHOGALL:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_CHOGALL, -5088.54f, -4669.88f, 356.37f);
                        events.CancelEvent(EVENT_MOVE_TO_CHOGALL);
                        break;
                    }
                    case EVENT_KNEEL_AND_TALK:
                    {
                        me->SetStandState(UNIT_STAND_STATE_KNEEL);
                        if (Unit* owner = me->ToTempSummon()->GetSummoner())
                            TalkWithDelay(1000, 0, owner->GetGUID());
                        events.ScheduleEvent(EVENT_ENABLE_CHOGALL, 10000);
                        events.CancelEvent(EVENT_KNEEL_AND_TALK);
                        break;
                    }
                    case EVENT_ENABLE_CHOGALL:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_CHO_GALL, 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter) == me)
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    (*iter)->AI()->Talk(0, player->GetGUID());
                                    (*iter)->AI()->TalkWithDelay(9000, 1, player->GetGUID());
                                    TalkWithDelay(17000, 1, player->GetGUID());
                                    (*iter)->AI()->TalkWithDelay(23000, 2, player->GetGUID());
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_SERVANT_TAKE_EYE, 24500);
                        events.ScheduleEvent(EVENT_PLACE_EYE, 39000);
                        events.CancelEvent(EVENT_ENABLE_CHOGALL);
                        break;
                    }
                    case EVENT_SERVANT_TAKE_EYE:
                    {
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_COWER);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_EYE, -5099.32f, -4665.77f, 356.39f);
                        events.ScheduleEvent(EVENT_RETURN_TO_CHOGALL, 3500);
                        events.CancelEvent(EVENT_SERVANT_TAKE_EYE);
                        break;
                    }
                    case EVENT_RETURN_TO_CHOGALL:
                    {
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_CHOGALL_2, -5090.80f, -4669.53f, 356.37f);
                        events.CancelEvent(EVENT_RETURN_TO_CHOGALL);
                        break;
                    }
                    case EVENT_PLACE_EYE:
                    {
                        me->HandleEmoteCommand(EMOTE_ONESHOT_OPEN);
                        me->RemoveAurasDueToSpell(SPELL_CARRY_EYE);
                        me->SummonCreature(NPC_EYE, -5088.91f, -4669.11f, 356.37f, 5.18f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);
                        events.ScheduleEvent(EVENT_UNCOVERED, 2500);
                        me->SetWalk(true);
                        events.CancelEvent(EVENT_PLACE_EYE);
                        break;
                    }
                    case EVENT_UNCOVERED:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_DISTANT, -5091.69f, -4671.36f, 356.37f);
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_CHO_GALL, 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    (*iter)->AI()->Talk(3, player->GetGUID());
                                    (*iter)->CastSpell((*iter), SPELL_SHADOW_CHANNELING, true);
                                    (*iter)->SetStandState(UNIT_STAND_STATE_KNEEL);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_CAMERA, 1000);
                        events.ScheduleEvent(EVENT_CHOGALL_FINAL, 14000);
                        events.CancelEvent(EVENT_UNCOVERED);
                        break;
                    }
                    case EVENT_MOVE_CAMERA:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_EYE_VEH, 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter)->GetPositionZ() > 360.0f)
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    (*iter)->SetWalk(true);
                                    (*iter)->GetMotionMaster()->MovePoint(POINT_FACE, -5090.50f, -4665.74f, 361.14f);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MOVE_CAMERA);
                        break;
                    }
                    case EVENT_CHOGALL_FINAL:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_CHO_GALL, 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    (*iter)->CastStop();
                                    (*iter)->HandleEmoteCommand(EMOTE_STATE_STAND);
                                    (*iter)->AI()->Talk(4, player->GetGUID());
                                    (*iter)->AI()->TalkWithDelay(14500, 5, player->GetGUID());
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_FINALIZE, 19500);
                        events.CancelEvent(EVENT_CHOGALL_FINAL);
                        break;
                    }
                    case EVENT_FINALIZE:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_EYE_VEH, 200.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (!(*iter)->ToTempSummon())
                                    continue;

                                if ((*iter)->GetPositionZ() > 364.0f)
                                    continue;

                                if ((*iter)->ToTempSummon()->GetSummoner() == player)
                                {
                                    (*iter)->GetMotionMaster()->MovementExpired(false);
                                    (*iter)->GetMotionMaster()->MoveJump(-5113.16f, -4604.77f, 356.83f, 37.5f, 3.5f, POINT_ESCAPE_1);
                                    player->SummonCreature(NPC_BLINDEYE, -5113.02f, -4592.89f, 357.91f, 4.71f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                    player->SummonCreature(NPC_MOUNTAIN, -5146.30f, -4616.87f, 355.13f, 0.04f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_FINALIZE);
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
        return new npc_th_eye_spy_twilight_servantAI(creature);
    }
};

class npc_th_thundermar_defender : public CreatureScript
{
public:
    npc_th_thundermar_defender() : CreatureScript("npc_th_thundermar_defender")
    {
    }

    struct npc_th_thundermar_defenderAI : public ScriptedAI
    {
        npc_th_thundermar_defenderAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1
        };

        enum spellId
        {
            SPELL_BATTLE_SHOUT  = 32064,
            SPELL_CHARGE        = 22120
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void EnterCombat(Unit* who)
        {
            if (!me->HasAura(SPELL_BATTLE_SHOUT))
            {
                DoCast(SPELL_BATTLE_SHOUT);
                DoCast(who, SPELL_CHARGE, true);
            }
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
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_thundermar_defenderAI(creature);
    }
};

class npc_th_dragonmaw_skyclaw : public CreatureScript
{
public:
    npc_th_dragonmaw_skyclaw() : CreatureScript("npc_th_dragonmaw_skyclaw")
    {
    }

    struct npc_th_dragonmaw_skyclawAI : public ScriptedAI
    {
        npc_th_dragonmaw_skyclawAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY  = 1,
            EVENT_BLOOD_FURY,
            EVENT_SUNDER_ARMOR
        };

        enum spellId
        {
            SPELL_BLOOD_FURY    = 82836,
            SPELL_SUNDER_ARMOR  = 11971
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void EnterCombat(Unit* who)
        {
            events.CancelEvent(EVENT_SEARCH_FOR_ENEMY);
            events.ScheduleEvent(EVENT_SUNDER_ARMOR, urand(1500, 3500));
            events.ScheduleEvent(EVENT_BLOOD_FURY, 8000);
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
                    case EVENT_BLOOD_FURY:
                    {
                        DoCast(me, SPELL_BLOOD_FURY, true);
                        events.RescheduleEvent(EVENT_BLOOD_FURY, 20000);
                        break;
                    }
                    case EVENT_SUNDER_ARMOR:
                    {
                        events.RescheduleEvent(EVENT_SUNDER_ARMOR, urand(2500, 5000));
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
        return new npc_th_dragonmaw_skyclawAI(creature);
    }
};

class spell_th_drake_dropper : public SpellScriptLoader
{
public:
    spell_th_drake_dropper() : SpellScriptLoader("spell_th_drake_dropper")
    {
    }

    class spell_th_drake_dropper_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_drake_dropper_SpellScript);

        enum Id
        {
            NPC_DRAGONMAW_BLACK_DRAKE = 48197
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->GetTypeId() != TYPEID_PLAYER)
                    {
                        if (target->ToCreature()->GetEntry() == NPC_DRAGONMAW_BLACK_DRAKE)
                            return SPELL_CAST_OK;
                    }
                }
            }
            return SPELL_FAILED_BAD_TARGETS;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_drake_dropper_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_drake_dropper_SpellScript();
    }
};

class npc_th_colin_thundermar : public CreatureScript
{
public:
    npc_th_colin_thundermar() : CreatureScript("npc_th_colin_thundermar")
    {
    }

    enum questId
    {
        QUEST_NARKRALL_THE_DRAKE_TAMER  = 28282
    };

    enum eventId
    {
        EVENT_SEARCH_FOR_NARKRALL   = 1,
        EVENT_CHECK_COMBAT
    };

    enum actionId
    {
        ACTION_PREPARATION  = 1
    };

    enum npcId
    {
        NPC_NARKRALL    = 48257,
        NPC_DRAKE       = 52025
    };

    enum pointId
    {
        POINT_EVADE     = 1
    };

    #define GOSSIP_SUMMON_NARKRALL "I'm ready to fight him!"

    class eventSummonNarkral : public BasicEvent
    {
    public:
        explicit eventSummonNarkral(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            Creature* narkrall = creature->FindNearestCreature(NPC_NARKRALL, 300.0f, true);
            Creature* drake = creature->FindNearestCreature(NPC_DRAKE, 300.0f, true);
            if (!narkrall && !drake)
                creature->SummonCreature(NPC_DRAKE, -3205.40f, -4964.89f, 138.37f, 4.86f, TEMPSUMMON_MANUAL_DESPAWN, 60000);
            return true;
        }

    private:
        Creature* creature;
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_NARKRALL_THE_DRAKE_TAMER) == QUEST_STATUS_INCOMPLETE)
            {
                Creature* narkrall = creature->FindNearestCreature(NPC_NARKRALL, 300.0f, true);
                Creature* drake = creature->FindNearestCreature(NPC_DRAKE, 300.0f, true);
                if (narkrall || drake)
                    return true;

                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->AI()->Talk(0, player->GetGUID());
                creature->HandleEmoteCommand(EMOTE_STATE_READY1H);
                creature->m_Events.AddEvent(new eventSummonNarkral(creature), (creature)->m_Events.CalculateTime(1000));
                creature->AI()->DoAction(ACTION_PREPARATION);
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_NARKRALL_THE_DRAKE_TAMER) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SUMMON_NARKRALL, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_colin_thundermarAI : public ScriptedAI
    {
        npc_th_colin_thundermarAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_PREPARATION:
                {
                    me->SetHealth(me->GetMaxHealth());
                    events.ScheduleEvent(EVENT_SEARCH_FOR_NARKRALL, 6000);
                    events.ScheduleEvent(EVENT_CHECK_COMBAT, 20000);
                    break;
                }
                default:
                    break;
            }
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
                    case EVENT_SEARCH_FOR_NARKRALL:
                    {
                        if (Creature* narkrall = me->FindNearestCreature(NPC_NARKRALL, 200.0f))
                        {
                            if (!narkrall->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC) && !narkrall->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC))
                            {
                                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                                me->Attack(narkrall, true);
                                me->SetInCombatWith(narkrall);
                                me->AddThreat(narkrall, 1000.0f);
                                events.CancelEvent(EVENT_SEARCH_FOR_NARKRALL);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_NARKRALL, 1000);
                        break;
                    }
                    case EVENT_CHECK_COMBAT:
                    {
                        Creature* narkrall = me->FindNearestCreature(NPC_NARKRALL, 300.0f, true);
                        Creature* drake = me->FindNearestCreature(NPC_DRAKE, 300.0f, true);
                        if (!narkrall && !drake)
                        {
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                            me->ClearInCombat();
                            me->AttackStop();
                            me->getHostileRefManager().clearReferences();
                            me->getThreatManager().clearReferences();
                            me->GetMotionMaster()->MovePoint(POINT_EVADE, -3202.53f, -5020.91f, 119.89f);
                            events.CancelEvent(EVENT_CHECK_COMBAT);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_COMBAT, 2000);
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
        return new npc_th_colin_thundermarAI(creature);
    }
};

class npc_th_narkral_drake : public CreatureScript
{
public:
    npc_th_narkral_drake() : CreatureScript("npc_th_narkral_drake")
    {
    }

    enum pointId
    {
        POINT_TO_LEAVE  = 1,
        POINT_BATTLE,
        POINT_AWAY
    };

    enum npcId
    {
        NPC_COLIN   = 48173
    };

    struct npc_th_narkral_drakeAI : public ScriptedAI
    {
        npc_th_narkral_drakeAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_ADVANCE   = 1,
            EVENT_MOVE_AWAY
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            events.ScheduleEvent(EVENT_ADVANCE, 500);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_LEAVE:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        passenger->ExitVehicle();
                        passenger->GetMotionMaster()->MovementExpired(false);
                        passenger->GetMotionMaster()->MoveJump(-3203.91f, -5012.02f, 120.00f, 12.5f, 12.5f, POINT_BATTLE);
                        passenger->Relocate(-3203.91f, -5012.02f, 120.00f);
                        if (passenger->ToCreature())
                            passenger->ToCreature()->SetHomePosition(-3203.91f, -5012.02f, 120.00f, 5.08f);
                        if (Creature* colin = me->FindNearestCreature(NPC_COLIN, 200.0f, true))
                        {
                            colin->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                            passenger->Attack(colin, true);
                            passenger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        }
                        events.ScheduleEvent(EVENT_MOVE_AWAY, 2000);
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
                    case EVENT_ADVANCE:
                    {
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(POINT_TO_LEAVE, -3208.53f, -5000.74f, 126.71f);
                        events.CancelEvent(EVENT_ADVANCE);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, 3200.00f, -4975.09f, 151.10f);
                        me->DespawnOrUnsummon(6000);
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
        return new npc_th_narkral_drakeAI(creature);
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
    new npc_th_mullan_gryphon_trapped();
    new npc_th_mullan_gryphon_injuried();
    new npc_th_firebeard_gryphon_mount();
    new npc_th_firebeard_gryphon_summoned();
    new npc_th_twilight_stormbender();
    new npc_th_servias_windterror();
    new go_th_sacred_ale_tap();
    new npc_th_cayden_dunwald_escort();
    new areatrigger_th_south_dunwald_hovel();
    new areatrigger_th_north_dunwald_hovel();
    new areatrigger_th_east_dunwald_hovel();
    new npc_th_eye_of_twilight_spy();
    new npc_th_eye_of_twilight_veh();
    new npc_th_eye_spy_twilight_servant();
    new npc_th_thundermar_defender();
    new npc_th_dragonmaw_skyclaw();
    new spell_th_drake_dropper();
    new npc_th_colin_thundermar();
    new npc_th_narkral_drake();
}
