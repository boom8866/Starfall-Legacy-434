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

class areatrigger_th_glopgut_hollow : public AreaTriggerScript
{
public:
    areatrigger_th_glopgut_hollow() : AreaTriggerScript("th_glopgut_hollow")
    {
    }

    enum questId
    {
        QUEST_FIND_FANNY     = 28378
    };

    enum npcId
    {
        NPC_FANNY   = 48013,
        NPC_KEEGAN  = 48500,
        NPC_GLOPGUT = 48480
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && player->GetQuestStatus(QUEST_FIND_FANNY) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* fanny = player->FindNearestCreature(NPC_FANNY, 200.0f, true);
            Creature* brogg = player->FindNearestCreature(NPC_GLOPGUT, 200.0f, true);
            if (!fanny && !brogg)
            {
                player->SummonCreature(NPC_FANNY, -3254.84f, -4297.48f, 159.97f, 3.29f, TEMPSUMMON_MANUAL_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                player->SummonCreature(NPC_KEEGAN, -3263.56f, -4296.28f, 159.52f, 6.00f, TEMPSUMMON_MANUAL_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            }
        }
        return false;
    }
};

class npc_th_russel_brower : public CreatureScript
{
public:
    npc_th_russel_brower() : CreatureScript("npc_th_russel_brower")
    {
    }

    uint8 selectFirst;
    uint8 selectSecond;
    uint8 selectThird;

    enum actionId
    {
        ACTION_START        = 1,
        ACTION_WISE,
        ACTION_PINT_SIZED,
        ACTION_THIGHS,
        ACTION_BLESSED,
        ACTION_ARREST,
        ACTION_CHEST,
        ACTION_ALIGHT,
        ACTION_KNIFEFIGHT,
        ACTION_TIGHT
    };

    enum choiseId
    {
        FIRST_CHOICE    = 17516,
        SECOND_CHOICE   = 17517,
        THIRD_CHOICE    = 17518
    };

    enum soundId
    {
        PLAY_SOUND_MUSIC    = 23556
    };

    enum spellId
    {
        SPELL_LUTE_ON_BACK  = 90353,
        SPELL_LUTE_IN_USE   = 90716
    };

    enum creditId
    {
        QUEST_CREDIT_MUSIC  = 48712
    };

    enum questId
    {
        QUEST_WORDS_AND_MUSIC_BY    = 28413
    };

    class eventReset : public BasicEvent
    {
    public:
        explicit eventReset(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            creature->RemoveAurasDueToSpell(SPELL_LUTE_IN_USE);
            creature->CastSpell(creature, SPELL_LUTE_ON_BACK, true);
            return true;
        }

    private:
        Creature* creature;
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_WORDS_AND_MUSIC_BY) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm ready, Russel. Let's write a song!", GOSSIP_SENDER_MAIN, ACTION_START);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch (action)
        {
            case ACTION_START:
            {
                // Reset selections
                selectFirst = 0;
                selectSecond = 0;
                selectThird = 0;

                // First Choice
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Romantic:] Wise.", GOSSIP_SENDER_MAIN, ACTION_WISE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Silly:] Pint-Sized.", GOSSIP_SENDER_MAIN, ACTION_PINT_SIZED);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Bawdy:] Thighs!", GOSSIP_SENDER_MAIN, ACTION_THIGHS);
                player->SEND_GOSSIP_MENU(FIRST_CHOICE, creature->GetGUID());
                break;
            }
            case ACTION_WISE:
            case ACTION_PINT_SIZED:
            case ACTION_THIGHS:
            {
                // Second Choice
                player->PlayerTalkClass->ClearMenus();
                switch (action)
                {
                    case ACTION_WISE:
                        selectFirst = 1;
                        break;
                    case ACTION_PINT_SIZED:
                        selectFirst = 2;
                        break;
                    case ACTION_THIGHS:
                        selectFirst = 3;
                        break;
                    default:
                        break;
                }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Romantic:] Blessed.", GOSSIP_SENDER_MAIN, ACTION_BLESSED);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Silly:] Arrest.", GOSSIP_SENDER_MAIN, ACTION_ARREST);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Bawdy:] ...Chest?", GOSSIP_SENDER_MAIN, ACTION_CHEST);
                player->SEND_GOSSIP_MENU(SECOND_CHOICE, creature->GetGUID());
                break;
            }
            case ACTION_BLESSED:
            case ACTION_ARREST:
            case ACTION_CHEST:
            {
                // Third Choice
                player->PlayerTalkClass->ClearMenus();
                switch (action)
                {
                    case ACTION_BLESSED:
                        selectSecond = 1;
                        break;
                    case ACTION_ARREST:
                        selectSecond = 2;
                        break;
                    case ACTION_CHEST:
                        selectSecond = 3;
                        break;
                    default:
                        break;
                }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Romantic:] Alight.", GOSSIP_SENDER_MAIN, ACTION_ALIGHT);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Silly:] Knifefight.", GOSSIP_SENDER_MAIN, ACTION_KNIFEFIGHT);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Bawdy:] Tight!", GOSSIP_SENDER_MAIN, ACTION_TIGHT);
                player->SEND_GOSSIP_MENU(THIRD_CHOICE, creature->GetGUID());
                break;
            }
            case ACTION_ALIGHT:
            case ACTION_KNIFEFIGHT:
            case ACTION_TIGHT:
            {
                player->PlayerTalkClass->SendCloseGossip();
                switch (action)
                {
                    case ACTION_ALIGHT:
                        selectThird = 1;
                        break;
                    case ACTION_KNIFEFIGHT:
                        selectThird = 2;
                        break;
                    case ACTION_TIGHT:
                        selectThird = 3;
                        break;
                    default:
                        break;
                }
                creature->PlayDirectSound(PLAY_SOUND_MUSIC, player);
                creature->RemoveAurasDueToSpell(SPELL_LUTE_ON_BACK);
                creature->CastSpell(creature, SPELL_LUTE_IN_USE);
                player->KilledMonsterCredit(QUEST_CREDIT_MUSIC);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                switch (selectFirst)
                {
                    case 1: // Wise
                    {
                        creature->AI()->TalkWithDelay(3000, 0);
                        creature->AI()->TalkWithDelay(6000, 1);
                        creature->AI()->TalkWithDelay(9000, 2);
                        creature->AI()->TalkWithDelay(12000, 3);
                        break;
                    }
                    case 2: // Pint-Sized
                    {
                        creature->AI()->TalkWithDelay(3000, 4);
                        creature->AI()->TalkWithDelay(6000, 5);
                        creature->AI()->TalkWithDelay(9000, 6);
                        creature->AI()->TalkWithDelay(12000, 7);
                        break;
                    }
                    case 3: // Thighs!
                    {
                        creature->AI()->TalkWithDelay(3000, 8);
                        creature->AI()->TalkWithDelay(6000, 9);
                        creature->AI()->TalkWithDelay(9000, 10);
                        creature->AI()->TalkWithDelay(12000, 11);
                        break;
                    }
                    default:
                        break;
                }
                switch (selectSecond)
                {
                    case 1: // Blessed
                    {
                        creature->AI()->TalkWithDelay(15000, 12);
                        creature->AI()->TalkWithDelay(19000, 13);
                        creature->AI()->TalkWithDelay(22000, 14);
                        creature->AI()->TalkWithDelay(25000, 15);
                        break;
                    }
                    case 2: // Arrest
                    {
                        creature->AI()->TalkWithDelay(15000, 16);
                        creature->AI()->TalkWithDelay(19000, 17);
                        creature->AI()->TalkWithDelay(22000, 18);
                        creature->AI()->TalkWithDelay(25000, 19);
                        break;
                    }
                    case 3: // ...Chest?
                    {
                        creature->AI()->TalkWithDelay(15000, 20);
                        creature->AI()->TalkWithDelay(19000, 21);
                        creature->AI()->TalkWithDelay(22000, 22);
                        creature->AI()->TalkWithDelay(25000, 23);
                        break;
                    }
                    default:
                        break;
                }
                switch (selectThird)
                {
                    case 1: // Alight
                    {
                        creature->AI()->TalkWithDelay(30000, 24);
                        creature->AI()->TalkWithDelay(33000, 25);
                        creature->AI()->TalkWithDelay(36000, 26);
                        creature->AI()->TalkWithDelay(39000, 27);
                        break;
                    }
                    case 2: // Knifefight
                    {
                        creature->AI()->TalkWithDelay(30000, 28);
                        creature->AI()->TalkWithDelay(33000, 29);
                        creature->AI()->TalkWithDelay(36000, 30);
                        creature->AI()->TalkWithDelay(39000, 31);
                        break;
                    }
                    case 3: // Tight!
                    {
                        creature->AI()->TalkWithDelay(30000, 32);
                        creature->AI()->TalkWithDelay(33000, 33);
                        creature->AI()->TalkWithDelay(36000, 34);
                        creature->AI()->TalkWithDelay(39000, 35);
                        break;
                    }
                    default:
                        break;
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->m_Events.AddEvent(new eventReset(creature), (creature)->m_Events.CalculateTime(46000));
                break;
            }
            default:
                break;
        }
        return true;
    }
};

class npc_th_hammelhand : public CreatureScript
{
public:
    npc_th_hammelhand() : CreatureScript("npc_th_hammelhand")
    {
    }

    enum actionId
    {
        ACTION_START    = 0
    };

    enum questId
    {
        QUEST_SOMETHING_BREWED  = 28409,
        QUEST_BEER_RUN          = 28864
    };

    enum npcId
    {
        NPC_WHEELBARROW     = 46706,
        NPC_LOOKOUT         = 48917
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_SOMETHING_BREWED) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_BEER_RUN) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm here to escort a delivery to Kirthaven.", GOSSIP_SENDER_MAIN, ACTION_START);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch (action)
        {
            case ACTION_START:
            {
                creature->AI()->TalkWithDelay(5000, 0, player->GetGUID());
                Creature* wheelbarrow = player->FindNearestCreature(NPC_WHEELBARROW, 80.0f, true);
                Creature* lookout = player->FindNearestCreature(NPC_LOOKOUT, 80.0f, true);
                if (!wheelbarrow && !lookout)
                {
                    player->SummonCreature(NPC_WHEELBARROW, -2952.73f, -5825.85f, 140.29f, 1.33f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    player->SummonCreature(NPC_WHEELBARROW, -2954.03f, -5832.55f, 137.58f, 1.30f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    player->SummonCreature(NPC_LOOKOUT, -2951.47f, -5835.05f, 136.92f, 1.64f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
                else
                    player->MonsterTextEmote("An escort was already started, try to reach and protect it on the road!", player->GetGUID(), true);

                player->CLOSE_GOSSIP_MENU();
                break;
            }
            default:
                break;
        }
        return true;
    }
};

class npc_th_grundy_mcgraff : public CreatureScript
{
public:
    npc_th_grundy_mcgraff() : CreatureScript("npc_th_grundy_mcgraff")
    {
    }

    enum actionId
    {
        ACTION_START = 0
    };

    enum questId
    {
        QUEST_WILD_WILD_WILDHAMMER_WEDDING  = 28655
    };

    enum npcId
    {
        NPC_WEDDING_CAMERA  = 49163
    };

    enum spellId
    {
        SPELL_FADE_TO_BLACK     = 94394
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_WILD_WILD_WILDHAMMER_WEDDING) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'll keep my eyes open, Grundy. Let the wedding commence!", GOSSIP_SENDER_MAIN, ACTION_START);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch (action)
        {
            case ACTION_START:
            {
                player->CastSpell(player, SPELL_FADE_TO_BLACK, true);
                player->SetPhaseMask(128, true);
                player->SummonCreature(NPC_WEDDING_CAMERA, -2779.24f, -5331.34f, 173.78f, 2.85f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                break;
            }
            default:
                break;
        }
        return true;
    }
};

class npc_th_wedding_veh : public CreatureScript
{
public:
    npc_th_wedding_veh() : CreatureScript("npc_th_wedding_veh")
    {
    }

    struct npc_th_wedding_vehAI : public ScriptedAI
    {
        npc_th_wedding_vehAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_FOCUS_RUSSELL,
            EVENT_FOCUS_GUESTS,
            EVENT_MUSIC_PERPETUE,
            EVENT_FOCUS_KURDRAN,
            EVENT_ENABLE_KEEGAN,
            EVENT_SUMMON_FANNY,
            EVENT_FOCUS_FANNY,
            EVENT_CENTER_WEDDING,
            EVENT_FOCUS_GRUNDY
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_LUTE_IN_USE           = 90716,
            SPELL_MIRROR_ESCORT         = 86784
        };

        enum questId
        {
        };

        enum pointId
        {
            POINT_GUESTS    = 1,
            POINT_WEDDING,
            POINT_RIGHT,
            POINT_CENTERED,
            POINT_GRUNDY
        };

        enum soundId
        {
            PLAY_SOUND_MUSIC    = 23556
        };

        enum npcId
        {
            // Singer
            NPC_RUSSELL_BROWER      = 49016,

            // Sit Npc
            NPC_EOIN_DUNWALD        = 49013,
            NPC_KEELY_DUNWALD       = 49012,
            NPC_FLYNN_DUNWALD       = 49011,
            NPC_CLIFF_THUNDERMAR    = 49015,
            NPC_COLIN_THUNDERMAR    = 49010,
            NPC_IAIN_FIREBEARD      = 49014,
            NPC_CAILIN_LONGFELLOW   = 49021,
            NPC_BEAK                = 49371,
            NPC_DONNELLY_DUNWALD    = 49017,

            // Near Altar
            NPC_KURDRAN_WILDHAMMER  = 49026,
            NPC_KEEGAN_FIREBEARD    = 49027,
            NPC_GRUNDY_MACGRAFF     = 49034,

            // Arriving
            NPC_FANNY_THUNDERMAR    = 49032,
            NPC_PLAYER_ESCORTER     = 51337,        // Need sniffs, not sure about it!

            // Camera
            NPC_CAMERA_GUEST        = 57758
        };

        void DespawnAllSummons()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                {
                    if ((*itr) == me)
                        continue;

                    (*itr)->ToCreature()->DespawnOrUnsummon(1);
                }
            }
        }

        void SitAllGuests()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToCreature()->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                {
                    switch ((*itr)->GetEntry())
                    {
                        // Sit Npc
                        case NPC_EOIN_DUNWALD:
                        case NPC_KEELY_DUNWALD:
                        case NPC_FLYNN_DUNWALD:
                        case NPC_CLIFF_THUNDERMAR:
                        case NPC_IAIN_FIREBEARD:
                        case NPC_CAILIN_LONGFELLOW:
                        case NPC_DONNELLY_DUNWALD:
                            (*itr)->SetStandState(UNIT_STAND_STATE_SIT_HIGH_CHAIR);
                            break;
                        default:
                            continue;
                    }
                }
            }
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_GUESTS:
                {
                    events.ScheduleEvent(EVENT_FOCUS_KURDRAN, 1);
                    events.ScheduleEvent(EVENT_ENABLE_KEEGAN, 1);
                    break;
                }
                case POINT_WEDDING:
                {
                    events.ScheduleEvent(EVENT_CENTER_WEDDING, 1);
                    break;
                }
                case POINT_CENTERED:
                {
                    events.ScheduleEvent(EVENT_FOCUS_GRUNDY, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void InformKeeganToAltar()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_KEEGAN_FIREBEARD, 100.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                    {
                        (*iter)->SetWalk(true);
                        (*iter)->GetMotionMaster()->MovePoint(POINT_RIGHT, -2773.24f, -5341.48f, 173.94f);
                    }
                }
            }
        }

        void InformKurdranToRotate()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_KURDRAN_WILDHAMMER, 100.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                        (*iter)->SetFacingTo(2.27f);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                        if (me->ToTempSummon())
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                invoker->EnterVehicle(me, 1);
                                invoker->SummonCreature(NPC_RUSSELL_BROWER, -2784.82f, -5330.56f, 173.71f, 6.26f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_CLIFF_THUNDERMAR, -2779.75f, -5339.58f, 173.74f, 0.59f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_KEELY_DUNWALD, -2782.92f, -5339.70f, 173.76f, 0.55f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_FLYNN_DUNWALD, -2782.33f, -5341.10f, 173.76f, 0.55f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_EOIN_DUNWALD, -2785.47f, -5341.00f, 173.73f, 0.56f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_COLIN_THUNDERMAR, -2771.30f, -5341.20f, 174.22f, 3.93f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_IAIN_FIREBEARD, -2774.53f, -5345.18f, 173.64f, 1.05f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_CAILIN_LONGFELLOW, -2773.16f, -5346.04f, 173.64f, 0.97f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_BEAK, -2777.23f, -5346.97f, 174.95f, 1.30f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                invoker->SummonCreature(NPC_DONNELLY_DUNWALD, -2776.06f, -5347.68f, 173.64f, 0.97f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            }
                        }
                        me->SetSpeed(MOVE_WALK, 0.3f, true);
                        me->SetSpeed(MOVE_RUN, 0.3f, true);
                        me->SetSpeed(MOVE_FLIGHT, 0.3f, true);
                        events.ScheduleEvent(EVENT_FOCUS_RUSSELL, 500);
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        break;
                    }
                    case EVENT_FOCUS_RUSSELL:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_RUSSELL_BROWER, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->CastSpell((*iter), SPELL_LUTE_IN_USE, true);
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                    events.ScheduleEvent(EVENT_MUSIC_PERPETUE, 1);
                                }
                            }
                        }

                        SitAllGuests();
                        events.ScheduleEvent(EVENT_FOCUS_GUESTS, 8000);
                        events.CancelEvent(EVENT_FOCUS_RUSSELL);
                        break;
                    }
                    case EVENT_FOCUS_GUESTS:
                    {
                        me->CastStop();
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->SummonCreature(NPC_KURDRAN_WILDHAMMER, -2767.88f, -5347.89f, 173.79f, 0.76f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            invoker->SummonCreature(NPC_KEEGAN_FIREBEARD, -2765.18f, -5345.91f, 173.76f, 3.73f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        me->SetWalk(true);
                        if (Creature* cameraGuest = me->FindNearestCreature(NPC_CAMERA_GUEST, 200.0f, true))
                            me->CastSpell(cameraGuest, SPELL_CAMERA_CHANNELING, true);
                        me->GetMotionMaster()->MovePoint(POINT_GUESTS, -2773.08f, -5342.60f, 173.81f);
                        events.CancelEvent(EVENT_FOCUS_GUESTS);
                        break;
                    }
                    case EVENT_MUSIC_PERPETUE:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                                invoker->PlayDirectSound(PLAY_SOUND_MUSIC, invoker->ToPlayer());
                        }
                        events.RescheduleEvent(EVENT_MUSIC_PERPETUE, 48000);
                        break;
                    }
                    case EVENT_FOCUS_KURDRAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KURDRAN_WILDHAMMER, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                    (*iter)->AI()->TalkWithDelay(2000, 0);
                                    (*iter)->AI()->TalkWithDelay(14000, 1);
                                    (*iter)->AI()->TalkWithDelay(20000, 2);
                                    (*iter)->AI()->TalkWithDelay(32000, 3);
                                    (*iter)->AI()->TalkWithDelay(38000, 4);
                                    (*iter)->AI()->TalkWithDelay(47000, 5, invoker->GetGUID());
                                }
                            }
                        }

                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->ChangeSeat(1, true);

                        events.ScheduleEvent(EVENT_SUMMON_FANNY, 47000);
                        events.ScheduleEvent(EVENT_FOCUS_FANNY, 53000);
                        events.CancelEvent(EVENT_FOCUS_KURDRAN);
                        break;
                    }
                    case EVENT_ENABLE_KEEGAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KEEGAN_FIREBEARD, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->AI()->TalkWithDelay(8000, 0);
                                    (*iter)->AI()->TalkWithDelay(26000, 1);
                                    (*iter)->AI()->TalkWithDelay(42000, 2);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_ENABLE_KEEGAN);
                        break;
                    }
                    case EVENT_SUMMON_FANNY:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->SummonCreature(NPC_FANNY_THUNDERMAR, -2785.74f, -5351.98f, 174.02f, 0.71f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            invoker->SummonCreature(NPC_PLAYER_ESCORTER, -2787.56f, -5349.87f, 174.27f, 0.71f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            invoker->SummonCreature(NPC_GRUNDY_MACGRAFF, -2773.42f, -5339.20f, 174.57f, 3.90f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        events.CancelEvent(EVENT_SUMMON_FANNY);
                        break;
                    }
                    case EVENT_FOCUS_FANNY:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_FANNY_THUNDERMAR, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    me->CastStop();
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                    invoker->CastSpell(invoker, SPELL_MIRROR_ESCORT, true);
                                    me->GetMotionMaster()->MoveJump(-2784.94f, -5355.54f, 176.15f, 1.5f, 1.5f, POINT_WEDDING);
                                    InformKeeganToAltar();
                                    InformKurdranToRotate();
                                }
                            }
                        }
                        events.CancelEvent(EVENT_FOCUS_FANNY);
                        break;
                    }
                    case EVENT_CENTER_WEDDING:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-2787.23f, -5353.04f, 177.79f, 1.5f, 1.5f, POINT_CENTERED);
                        events.CancelEvent(EVENT_CENTER_WEDDING);
                        break;
                    }
                    case EVENT_FOCUS_GRUNDY:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_GRUNDY_MACGRAFF, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    me->CastStop();
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                    me->GetMotionMaster()->MoveJump(-2779.25f, -5344.07f, 174.75f, 1.0f, 1.0f, POINT_GRUNDY);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MUSIC_PERPETUE);
                        events.CancelEvent(EVENT_FOCUS_GRUNDY);
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
        return new npc_th_wedding_vehAI(creature);
    }
};

class npc_th_wedding_fanny : public CreatureScript
{
public:
    npc_th_wedding_fanny() : CreatureScript("npc_th_wedding_fanny")
    {
    }

    struct npc_th_wedding_fannyAI : public ScriptedAI
    {
        npc_th_wedding_fannyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_ALTAR     = 1,
            EVENT_MOVE_TO_LEFT,
            EVENT_ENABLE_GRUNDY,
            EVENT_TALK_KEEGAN,
            EVENT_REMOVE_VEHICLE,
            EVENT_BE_SCARED,
            EVENT_ROTATE_KEEGAN
        };

        enum spellId
        {
            SPELL_GOES_ENRAGE           = 91844,
            SPELL_TWILIGHT_EXPLOSION    = 84207,
            SPELL_TRANSFORMATION        = 91848,
            SPELL_WEDDING_HYMN          = 93653
        };

        enum pointId
        {
            POINT_ALTAR =   1,
            POINT_LEFT
        };

        enum npcId
        {
            NPC_GRUNDY_MACGRAFF     = 49034,
            NPC_KEEGAN_FIREBEARD    = 49027,
            NPC_WEDDING_CAMERA      = 49163,
            NPC_WEDDING_MIRROR      = 51337
        };

        enum guestId
        {
            // Singer
            NPC_RUSSELL_BROWER      = 49016,

            // Sit Npc
            NPC_EOIN_DUNWALD        = 49013,
            NPC_KEELY_DUNWALD       = 49012,
            NPC_FLYNN_DUNWALD       = 49011,
            NPC_CLIFF_THUNDERMAR    = 49015,
            NPC_COLIN_THUNDERMAR    = 49010,
            NPC_IAIN_FIREBEARD      = 49014,
            NPC_CAILIN_LONGFELLOW   = 49021,
            NPC_BEAK                = 49371,
            NPC_DONNELLY_DUNWALD    = 49017,

            // Near Altar
            NPC_KURDRAN_WILDHAMMER  = 49026,

            // Arriving
            NPC_FANNY_THUNDERMAR    = 49032,
            NPC_PLAYER_ESCORTER     = 51337,        // Need sniffs, not sure about it!,

            NPC_THE_BEAST_UNLEASHED = 49234
        };

        void SetGuestsInCombat()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_IAIN_FIREBEARD:
                        case NPC_KEELY_DUNWALD:
                        case NPC_CLIFF_THUNDERMAR:
                        case NPC_DONNELLY_DUNWALD:
                        {
                            (*itr)->ToCreature()->AI()->DoAction(1);
                            (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500, 1500), 0);
                            break;
                        }
                        case NPC_FLYNN_DUNWALD:
                        case NPC_EOIN_DUNWALD:
                        case NPC_COLIN_THUNDERMAR:
                        case NPC_CAILIN_LONGFELLOW:
                        case NPC_KURDRAN_WILDHAMMER:
                        {
                            (*itr)->ToCreature()->AI()->DoAction(1);
                            break;
                        }
                        case NPC_RUSSELL_BROWER:
                        {
                            (*itr)->GetMotionMaster()->MovePoint(20, -2783.38f, -5351.26f, 173.86f);
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                (*itr)->SetControlled(true, UNIT_STATE_ROOT);
                                (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                                (*itr)->ToCreature()->AI()->TalkWithDelay(12000, 0, invoker->GetGUID());
                                (*itr)->CastWithDelay(15000, (*itr), SPELL_WEDDING_HYMN, true);
                                (*itr)->MonsterYell("For the Wildhammer!", 0);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        class eventEnrageEmote : public BasicEvent
        {
        public:
            explicit eventEnrageEmote(Creature* creature) : creature(creature)
            {
            }

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                return true;
            }

        private:
            Creature* creature;
        };

        class eventUnleashBeast : public BasicEvent
        {
        public:
            explicit eventUnleashBeast(Creature* creature) : creature(creature)
            {
            }

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Unit* invoker = creature->ToTempSummon()->GetSummoner())
                {
                    invoker->SummonCreature(NPC_THE_BEAST_UNLEASHED, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    creature->DespawnOrUnsummon(100);
                }
                return true;
            }

        private:
            Creature* creature;
        };

        void Reset()
        {
            me->SetWalk(true);
            me->SetSpeed(MOVE_WALK, 0.5f, true);
            events.ScheduleEvent(EVENT_MOVE_TO_ALTAR, 3000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ALTAR:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_LEFT, 1);
                    break;
                }
                case POINT_LEFT:
                {
                    me->SetFacingTo(5.44f);
                    events.ScheduleEvent(EVENT_ENABLE_GRUNDY, 2500);
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
                    case EVENT_MOVE_TO_ALTAR:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_ALTAR, -2775.68f, -5342.23f, 173.71f);
                        events.CancelEvent(EVENT_MOVE_TO_ALTAR);
                        break;
                    }
                    case EVENT_MOVE_TO_LEFT:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_LEFT, -2775.76f, -5338.70f, 174.23f);
                        events.CancelEvent(EVENT_MOVE_TO_LEFT);
                        break;
                    }
                    case EVENT_ENABLE_GRUNDY:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_GRUNDY_MACGRAFF, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->AI()->TalkWithDelay(2000, 0);
                                    (*iter)->AI()->TalkWithDelay(10000, 1);
                                    (*iter)->AI()->TalkWithDelay(20000, 2);
                                    TalkWithDelay(28000, 0);
                                    events.ScheduleEvent(EVENT_TALK_KEEGAN, 28000);
                                    (*iter)->AI()->TalkWithDelay(34000, 3);
                                    (*iter)->CastWithDelay(37500, (*iter), SPELL_GOES_ENRAGE);
                                    (*iter)->AI()->TalkWithDelay(38500, 4);
                                    (*iter)->m_Events.AddEvent(new eventEnrageEmote((*iter)), ((*iter))->m_Events.CalculateTime(39000));
                                    (*iter)->CastWithDelay(40000, (*iter), SPELL_TWILIGHT_EXPLOSION);
                                    (*iter)->CastWithDelay(41000, (*iter), SPELL_TRANSFORMATION);
                                    (*iter)->AI()->TalkWithDelay(45500, 5);
                                    (*iter)->m_Events.AddEvent(new eventUnleashBeast((*iter)), ((*iter))->m_Events.CalculateTime(48500));
                                    events.ScheduleEvent(EVENT_BE_SCARED, 39500);
                                    events.ScheduleEvent(EVENT_REMOVE_VEHICLE, 50000);
                                    me->AI()->TalkWithDelay(52000, 1, invoker->GetGUID());
                                }
                            }
                        }
                        events.CancelEvent(EVENT_ENABLE_GRUNDY);
                        break;
                    }
                    case EVENT_BE_SCARED:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_WEDDING_MIRROR, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->SetWalk(false);
                                    (*iter)->GetMotionMaster()->MovePoint(50, -2785.22f, -5331.19f, 173.71f);
                                    (*iter)->DespawnOrUnsummon(5000);
                                }
                            }
                        }
                        me->HandleEmoteCommand(EMOTE_STATE_COWER);
                        events.ScheduleEvent(EVENT_ROTATE_KEEGAN, 500);
                        events.CancelEvent(EVENT_BE_SCARED);
                        break;
                    }
                    case EVENT_ROTATE_KEEGAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KEEGAN_FIREBEARD, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->SetWalk(false);
                                    (*iter)->SetFacingTo(0.89f);
                                    (*iter)->HandleEmoteCommand(EMOTE_STATE_READY1H);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_ROTATE_KEEGAN);
                        break;
                    }
                    case EVENT_TALK_KEEGAN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KEEGAN_FIREBEARD, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->AI()->Talk(3);
                            }
                        }
                        events.CancelEvent(EVENT_TALK_KEEGAN);
                        break;
                    }
                    case EVENT_REMOVE_VEHICLE:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_WEDDING_CAMERA, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->DespawnOrUnsummon(1);
                            }
                        }
                        SetGuestsInCombat();
                        me->DespawnOrUnsummon(5000);
                        events.CancelEvent(EVENT_REMOVE_VEHICLE);
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
        return new npc_th_wedding_fannyAI(creature);
    }
};

class npc_th_wedding_mirror : public CreatureScript
{
public:
    npc_th_wedding_mirror() : CreatureScript("npc_th_wedding_mirror")
    {
    }

    struct npc_th_wedding_mirrorAI : public ScriptedAI
    {
        npc_th_wedding_mirrorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_ALTAR = 1,
            EVENT_MOVE_TO_LEFT
        };

        enum pointId
        {
            POINT_ALTAR = 1,
            POINT_LEFT
        };

        void Reset()
        {
            if (me->GetZoneId() == 4922 && me->GetAreaId() == 5143)
            {
                me->SetWalk(true);
                me->SetSpeed(MOVE_WALK, 0.5f, true);
                me->RemoveAurasDueToSpell(69676);
                me->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, 0);
                events.ScheduleEvent(EVENT_MOVE_TO_ALTAR, 2900);
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ALTAR:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_LEFT, 1);
                    break;
                }
                case POINT_LEFT:
                {
                    me->SetFacingTo(4.28f);
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
                    case EVENT_MOVE_TO_ALTAR:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_ALTAR, -2776.19f, -5339.73f, 173.88f);
                        events.CancelEvent(EVENT_MOVE_TO_ALTAR);
                        break;
                    }
                    case EVENT_MOVE_TO_LEFT:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_LEFT, -2775.55f, -5335.99f, 174.56f);
                        events.CancelEvent(EVENT_MOVE_TO_LEFT);
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
        return new npc_th_wedding_mirrorAI(creature);
    }
};

class npc_th_wedding_guests : public CreatureScript
{
public:
    npc_th_wedding_guests() : CreatureScript("npc_th_wedding_guests")
    {
    }

    struct npc_th_wedding_guestsAI : public ScriptedAI
    {
        npc_th_wedding_guestsAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_TRAITOR    = 1,
            EVENT_SET_IN_FEAR
        };

        enum actionId
        {
            ACTION_ENGAGE   = 1,
            ACTION_STOP
        };

        enum npcId
        {
            NPC_THE_BEAST_UNLEASHED     = 49234
        };

        enum spellId
        {
            SPELL_FEAR          = 91979,
            SPELL_COLD_FEET     = 93708
        };

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT)
                damage = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENGAGE:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                    events.ScheduleEvent(EVENT_SEARCH_FOR_TRAITOR, 1500);
                    events.ScheduleEvent(EVENT_SET_IN_FEAR, 1500);
                    break;
                }
                case ACTION_STOP:
                {
                    me->HandleEmoteCommand(EMOTE_STATE_DANCE);
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        invoker->SummonCreature(49358, -2766.55f, -5347.82f, 173.92f, 2.38f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    events.Reset();
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
                    case EVENT_SEARCH_FOR_TRAITOR:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_THE_BEAST_UNLEASHED, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    AttackStart((*iter));
                            }
                        }
                        events.CancelEvent(EVENT_SEARCH_FOR_TRAITOR);
                        break;
                    }
                    case EVENT_SET_IN_FEAR:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_THE_BEAST_UNLEASHED, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    if (!(*iter)->isAlive())
                                        events.Reset();
                            }
                        }
                        if (roll_chance_f(25) && !me->HasAura(SPELL_COLD_FEET) && me->isInCombat())
                            me->AddAura(SPELL_FEAR, me);
                        events.RescheduleEvent(EVENT_SET_IN_FEAR, urand(14000, 20000));
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
        return new npc_th_wedding_guestsAI(creature);
    }
};

class npc_th_wedding_beast : public CreatureScript
{
public:
    npc_th_wedding_beast() : CreatureScript("npc_th_wedding_beast")
    {
    }

    struct npc_th_wedding_beastAI : public ScriptedAI
    {
        npc_th_wedding_beastAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SHADOW_BOLT_VOLLEY    = 1,
            EVENT_WEDDING_CRASH,
            EVENT_AURA_OF_DARKNESS,
            EVENT_REMOVE_AOD,
            EVENT_KNOCKBACK_GUESTS,
            EVENT_REMOVE_FREEZE
        };

        enum actionId
        {
            ACTION_JITTERS  = 1
        };

        enum npcId
        {
            NPC_UNINVITED_TENTACLE  = 49259,
            NPC_EOIN_DUNWALD        = 49013,
            NPC_KEELY_DUNWALD       = 49012,
            NPC_FLYNN_DUNWALD       = 49011,
            NPC_CLIFF_THUNDERMAR    = 49015,
            NPC_COLIN_THUNDERMAR    = 49010,
            NPC_IAIN_FIREBEARD      = 49014,
            NPC_CAILIN_LONGFELLOW   = 49021,
            NPC_DONNELLY_DUNWALD    = 49017,
            NPC_KURDRAN_WILDHAMMER  = 49026,
            NPC_RUSSELL_BROWER      = 49016,
            NPC_THE_BEAST_UNLEASHED = 49234
        };

        enum spellId
        {
            SPELL_AURA_OF_DARKNESS      = 93717,
            SPELL_DARKNESS_AROUND       = 93719,
            SPELL_SHADOW_BOLT_VOLLEY    = 9081,
            SPELL_WEDDING_CRASH         = 91977,
            SPELL_WEDDING_JITTERS       = 91979,
            SPELL_TENTACLE_SWEEP        = 93708,
            SPELL_COLD_FEET             = 91978
        };

        void RemoveFreezeFromGuests()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 600.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_IAIN_FIREBEARD:
                        case NPC_KEELY_DUNWALD:
                        case NPC_CLIFF_THUNDERMAR:
                        case NPC_DONNELLY_DUNWALD:
                        case NPC_FLYNN_DUNWALD:
                        case NPC_EOIN_DUNWALD:
                        case NPC_COLIN_THUNDERMAR:
                        case NPC_CAILIN_LONGFELLOW:
                        case NPC_KURDRAN_WILDHAMMER:
                        {
                            (*itr)->RemoveAurasDueToSpell(SPELL_COLD_FEET);
                            (*itr)->MonsterYell("For the Wildhammer!", 0);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        void DespawnAllSummons()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_UNINVITED_TENTACLE:
                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                            break;
                        case NPC_RUSSELL_BROWER:
                            (*itr)->RemoveAurasDueToSpell(90716);
                            (*itr)->RemoveAurasDueToSpell(93653);
                            (*itr)->AddAura(90353, (*itr));
                            (*itr)->ToCreature()->DespawnOrUnsummon(10000);
                            break;
                        default:
                            (*itr)->ToCreature()->AI()->DoAction(2);
                            (*itr)->ToCreature()->DespawnOrUnsummon(180000);
                            break;
                    }
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
            {
                invoker->RemoveAurasDueToSpell(SPELL_DARKNESS_AROUND);
                if (invoker->GetTypeId() == TYPEID_PLAYER)
                    invoker->ToPlayer()->KilledMonsterCredit(me->GetEntry());
            }
            DespawnAllSummons();
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT)
                damage = urand(456, 1123);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
            {
                invoker->SummonCreature(NPC_UNINVITED_TENTACLE, -2768.78f, -5338.71f, 174.60f, 3.91f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                invoker->SummonCreature(NPC_UNINVITED_TENTACLE, -2773.17f, -5333.63f, 174.43f, 3.75f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            }
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.ScheduleEvent(EVENT_AURA_OF_DARKNESS, 10000);
            events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, 500);
            events.ScheduleEvent(EVENT_WEDDING_CRASH, 3000);
            events.ScheduleEvent(EVENT_KNOCKBACK_GUESTS, 17500);
        }

        void KnockbackAndFreeze()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_UNINVITED_TENTACLE:
                        {
                            (*itr)->CastSpell((*itr), SPELL_TENTACLE_SWEEP, true);
                            (*itr)->CastWithDelay(3000, (*itr), SPELL_COLD_FEET, true);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                TalkWithDelay(3100, 1, invoker->GetGUID());

            events.ScheduleEvent(EVENT_REMOVE_FREEZE, 20000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_JITTERS:
                {
                    DoCast(SPELL_WEDDING_JITTERS);
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
                    case EVENT_SHADOW_BOLT_VOLLEY:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_SHADOW_BOLT_VOLLEY);
                        events.RescheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, urand(3000, 8000));
                        break;
                    }
                    case EVENT_WEDDING_CRASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_WEDDING_CRASH);
                        events.RescheduleEvent(EVENT_WEDDING_CRASH, urand(4500, 9000));
                        break;
                    }
                    case EVENT_AURA_OF_DARKNESS:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_AURA_OF_DARKNESS);
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->AddAura(SPELL_DARKNESS_AROUND, invoker);
                        events.RescheduleEvent(EVENT_AURA_OF_DARKNESS, 60000);
                        events.ScheduleEvent(EVENT_REMOVE_AOD, 10000);
                        break;
                    }
                    case EVENT_REMOVE_AOD:
                    {
                        me->RemoveAurasDueToSpell(SPELL_AURA_OF_DARKNESS);
                        events.CancelEvent(EVENT_REMOVE_AOD);
                        break;
                    }
                    case EVENT_KNOCKBACK_GUESTS:
                    {
                        KnockbackAndFreeze();
                        events.CancelEvent(EVENT_KNOCKBACK_GUESTS);
                        break;
                    }
                    case EVENT_REMOVE_FREEZE:
                    {
                        RemoveFreezeFromGuests();
                        events.CancelEvent(EVENT_REMOVE_FREEZE);
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
        return new npc_th_wedding_beastAI(creature);
    }
};

class npc_th_wedding_kurdran : public CreatureScript
{
public:
    npc_th_wedding_kurdran() : CreatureScript("npc_th_wedding_kurdran")
    {
    }

    enum questId
    {
        QUEST_WILD_WILD_WILDHAMMER_WEDDING  = 28655
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_WILD_WILD_WILDHAMMER_WEDDING)
        {
            player->SetPhaseMask(9, true);
            return true;
        }
        return true;
    }
};

class npc_th_twilight_shadowshifter : public CreatureScript
{
public:
    npc_th_twilight_shadowshifter() : CreatureScript("npc_th_twilight_shadowshifter")
    {
    }

    struct npc_th_twilight_shadowshifterAI : public ScriptedAI
    {
        npc_th_twilight_shadowshifterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SPIRIT_BURST  = 1,
            EVENT_CHANNELING
        };

        enum actionId
        {
            ACTION_RESPAWN  = 1
        };

        enum spellId
        {
            SPELL_DARK_EMPOWERMENT  = 93747,
            SPELL_SPIRIT_BURST      = 69900
        };

        enum npcId
        {
            NPC_DARUNGA     = 46624
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            if (Creature* darunga = me->FindNearestCreature(NPC_DARUNGA, 100.0f, true))
                DoCast(SPELL_DARK_EMPOWERMENT);
            events.ScheduleEvent(EVENT_CHANNELING, 1000);
            events.ScheduleEvent(EVENT_SPIRIT_BURST, 10000);
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_RESPAWN:
                {
                    me->Respawn(true);
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
                    case EVENT_SPIRIT_BURST:
                    {
                        Creature* darunga = me->FindNearestCreature(NPC_DARUNGA, 100.0f, true);
                        if (darunga)
                            DoCast(me, SPELL_SPIRIT_BURST, true);
                        events.RescheduleEvent(EVENT_SPIRIT_BURST, urand(5000, 15500));
                        break;
                    }
                    case EVENT_CHANNELING:
                    {
                        Creature* darunga = me->FindNearestCreature(NPC_DARUNGA, 100.0f, true);
                        if (!me->HasUnitState(UNIT_STATE_CASTING) && darunga)
                            DoCast(SPELL_DARK_EMPOWERMENT);
                        events.RescheduleEvent(EVENT_CHANNELING, 1000);
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
        return new npc_th_twilight_shadowshifterAI(creature);
    }
};

class npc_th_darunga : public CreatureScript
{
public:
    npc_th_darunga() : CreatureScript("npc_th_darunga")
    {
    }

    struct npc_th_darungaAI : public ScriptedAI
    {
        npc_th_darungaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_HEAVING_STOMP     = 1,
            EVENT_HURL_BOULDER,
            EVENT_JUMP_CAYDEN,
            EVENT_CAYDEN_ATTACK,
            EVENT_TALK_DONNELLY,
            EVENT_TALK_CAYDEN,
            EVENT_TALK_EOIN,
            EVENT_TALK_CAYDEN_2,
            EVENT_LAUNCH_MUG
        };

        enum spellId
        {
            SPELL_HEAVING_STOMP     = 93738,
            SPELL_HURL_BOULDER      = 52272,
            SPELL_CONJURE_MUG       = 93785
        };

        enum questId
        {
            QUEST_DOING_IT_LIKE_A_DUNWALD   = 27651
        };

        enum npcId
        {
            NPC_TWILIGHT_SHADOWSHIFTER  = 50593,
            NPC_DONNELLY                = 46626,
            NPC_FLYNN                   = 46628,
            NPC_EOIN                    = 46627,
            NPC_CAYDEN                  = 46625
        };

        enum pointId
        {
            POINT_BACK  = 1
        };

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT)
                damage = urand(456, 967);
        }

        void EnterEvadeMode()
        {
        }

        void OnCharmed(bool apply)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_JUMP_CAYDEN, 2000);
            events.ScheduleEvent(EVENT_HEAVING_STOMP, 12500);
            events.ScheduleEvent(EVENT_HURL_BOULDER, 5000);
            events.ScheduleEvent(EVENT_TALK_DONNELLY, 8000);
            events.ScheduleEvent(EVENT_TALK_CAYDEN, 16000);
            events.ScheduleEvent(EVENT_TALK_EOIN, 24000);
            events.ScheduleEvent(EVENT_TALK_CAYDEN_2, 30000);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustDied(Unit* /*who*/)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr))
                {
                    if ((*itr)->GetTypeId() == TYPEID_PLAYER)
                    {
                        if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_DOING_IT_LIKE_A_DUNWALD) == QUEST_STATUS_INCOMPLETE)
                            (*itr)->ToPlayer()->KilledMonsterCredit(me->GetEntry());
                    }
                    if ((*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_FLYNN:
                                (*itr)->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                                break;
                            case NPC_TWILIGHT_SHADOWSHIFTER:
                                (*itr)->Kill((*itr), false);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_PASSIVE);
            events.Reset();
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
                    case EVENT_HEAVING_STOMP:
                    {
                        RESCHEDULE_IF_CASTING;
                        Talk(0);
                        DoCast(SPELL_HEAVING_STOMP);
                        events.RescheduleEvent(EVENT_HEAVING_STOMP, urand(10000, 25000));
                        break;
                    }
                    case EVENT_HURL_BOULDER:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_HURL_BOULDER);
                        events.RescheduleEvent(EVENT_HURL_BOULDER, urand(4500, 15000));
                        break;
                    }
                    case EVENT_JUMP_CAYDEN:
                    {
                        if (Creature* cayden = me->FindNearestCreature(NPC_CAYDEN, 150.0f, true))
                            cayden->GetMotionMaster()->MoveJump(-4662.31f, -5077.62f, 128.42f, 15.5f, 15.5f, POINT_BACK);
                        events.ScheduleEvent(EVENT_CAYDEN_ATTACK, 4000);
                        events.CancelEvent(EVENT_JUMP_CAYDEN);
                        break;
                    }
                    case EVENT_CAYDEN_ATTACK:
                    {
                        if (Creature* cayden = me->FindNearestCreature(NPC_CAYDEN, 150.0f, true))
                        {
                            cayden->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            cayden->AI()->AttackStart(me);
                        }
                        events.CancelEvent(EVENT_CAYDEN_ATTACK);
                        break;
                    }
                    case EVENT_TALK_DONNELLY:
                    {
                        if (Creature* donnelly = me->FindNearestCreature(NPC_DONNELLY, 150.0f, true))
                            donnelly->AI()->Talk(0);
                        events.CancelEvent(EVENT_TALK_DONNELLY);
                        break;
                    }
                    case EVENT_TALK_CAYDEN:
                    {
                        if (Creature* cayden = me->FindNearestCreature(NPC_CAYDEN, 150.0f, true))
                            cayden->AI()->Talk(0);
                        events.CancelEvent(EVENT_TALK_CAYDEN);
                        break;
                    }
                    case EVENT_TALK_EOIN:
                    {
                        if (Creature* eoin = me->FindNearestCreature(NPC_EOIN, 150.0f, true))
                        {
                            eoin->AI()->Talk(0);
                            eoin->AI()->TalkWithDelay(10000, 1);
                            eoin->AI()->TalkWithDelay(13500, 2);
                            eoin->CastWithDelay(13500, eoin, SPELL_CONJURE_MUG);
                            events.ScheduleEvent(EVENT_LAUNCH_MUG, urand(8500, 15000));
                        }
                        events.CancelEvent(EVENT_TALK_EOIN);
                        break;
                    }
                    case EVENT_TALK_CAYDEN_2:
                    {
                        if (Creature* cayden = me->FindNearestCreature(NPC_CAYDEN, 150.0f, true))
                            cayden->AI()->Talk(1);
                        events.CancelEvent(EVENT_TALK_CAYDEN);
                        break;
                    }
                    case EVENT_LAUNCH_MUG:
                    {
                        if (Creature* eoin = me->FindNearestCreature(NPC_EOIN, 150.0f, true))
                            eoin->CastSpell(eoin, SPELL_CONJURE_MUG);
                        events.RescheduleEvent(EVENT_LAUNCH_MUG, urand(15000, 17000));
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
        return new npc_th_darungaAI(creature);
    }
};

class npc_th_flynn_dunwald_darunga : public CreatureScript
{
public:
    npc_th_flynn_dunwald_darunga() : CreatureScript("npc_th_flynn_dunwald_darunga")
    {
    }

    enum questId
    {
        QUEST_DOING_IT_LIKE_A_DUNWALD   = 27651
    };

    enum npcId
    {
        NPC_DARUNGA     = 46624
    };

    enum spellId
    {
        SPELL_FADE_TO_BLACK     = 89321
    };

    class eventAttackDarunga : public BasicEvent
    {
    public:
        explicit eventAttackDarunga(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            if (Creature* darunga = creature->FindNearestCreature(NPC_DARUNGA, 200.0f, true))
            {
                darunga->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                darunga->SetReactState(REACT_AGGRESSIVE);
                creature->AI()->AttackStart(darunga);
            }
            return true;
        }

    private:
        Creature* creature;
    };

    class eventTeleportPlayer : public BasicEvent
    {
    public:
        explicit eventTeleportPlayer(Player* player) : player(player)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            if (player && player->IsInWorld())
                player->TeleportTo(0, -4460.05f, -4862.12f, 123.18f, 1.13f);
            return true;
        }

    private:
        Player* player;
    };

    #define GOSSIP_DARUNGA "I'm in."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_DOING_IT_LIKE_A_DUNWALD) == QUEST_STATUS_INCOMPLETE)
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(500, 0);
                creature->AI()->TalkWithDelay(4000, 1);
                creature->m_Events.AddEvent(new eventAttackDarunga(creature), (creature)->m_Events.CalculateTime(4000));
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_DOING_IT_LIKE_A_DUNWALD) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* darunga = creature->FindNearestCreature(NPC_DARUNGA, 200.0f, true))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DARUNGA, 0, 0);

            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_DOING_IT_LIKE_A_DUNWALD)
        {
            player->AddAura(SPELL_FADE_TO_BLACK, player);
            player->m_Events.AddEvent(new eventTeleportPlayer(player), (player)->m_Events.CalculateTime(2000));
            return true;
        }
        return true;
    }
};

class npc_th_earthen_ring_gryphon : public CreatureScript
{
public:
    npc_th_earthen_ring_gryphon() : CreatureScript("npc_th_earthen_ring_gryphon")
    {
    }

    enum questId
    {
        QUEST_THE_MAW_OF_ISO_RATH   = 27376
    };

    enum spellId
    {
        SPELL_SUMMON_EARTHEN_RING_GRYPHON   = 91271
    };

    enum creditId
    {
        QUEST_CREDIT_ISO_RATH_RIDE = 48281
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_MAW_OF_ISO_RATH) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, SPELL_SUMMON_EARTHEN_RING_GRYPHON, true);
            player->KilledMonsterCredit(QUEST_CREDIT_ISO_RATH_RIDE);
            return true;
        }
        return true;
    }
};

class npc_th_earthen_ring_gryphon_summoned : public CreatureScript
{
public:
    npc_th_earthen_ring_gryphon_summoned() : CreatureScript("npc_th_earthen_ring_gryphon_summoned")
    {
    }

    enum actionId
    {
        ACTION_WP_START     = 1,
    };

    enum npcId
    {
        NPC_TENTACLE_OF_ISO_RATH    = 45693
    };

    enum pointId
    {
    };

    struct npc_th_earthen_ring_gryphon_summonedAI : public npc_escortAI
    {
        npc_th_earthen_ring_gryphon_summonedAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            me->AddUnitState(UNIT_STATE_ROTATING | UNIT_STATE_ROAMING_MOVE);
        }

        void EnterEvadeMode()
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER && seatId == 0)
                DoAction(ACTION_WP_START);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                {
                    if (Unit* mylra = me->GetVehicleKit()->GetPassenger(1))
                    {
                        if (mylra->ToCreature())
                            mylra->ToCreature()->AI()->Talk(0);
                    }
                    break;
                }
                case 7:
                {
                    if (Unit* mylra = me->GetVehicleKit()->GetPassenger(1))
                    {
                        if (mylra->ToCreature())
                            mylra->ToCreature()->AI()->Talk(1);
                    }
                    if (Unit* playerPassenger = me->GetVehicleKit()->GetPassenger(0))
                        playerPassenger->SummonCreature(NPC_TENTACLE_OF_ISO_RATH, -2722.86f, -5002.25f, 139.86f, 0.83f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    break;
                }
                case 10:
                {
                    if (Unit* playerPassenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        playerPassenger->ExitVehicle();
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TENTACLE_OF_ISO_RATH, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    playerPassenger->EnterVehicle((*iter));
                            }
                        }
                    }
                    me->DespawnOrUnsummon(10000);
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
                    Start(false, true, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_earthen_ring_gryphon_summonedAI(creature);
    }
};

class npc_th_tentacle_of_iso_rath_veh : public CreatureScript
{
public:
    npc_th_tentacle_of_iso_rath_veh() : CreatureScript("npc_th_tentacle_of_iso_rath_veh")
    {
    }

    struct npc_th_tentacle_of_iso_rath_vehAI : public ScriptedAI
    {
        npc_th_tentacle_of_iso_rath_vehAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_DROP_PLAYER   = 1
        };

        enum pointId
        {
            POINT_HOLE  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_TENTACLE_EXIT     = 94499,
            SPELL_TENTACLE_FALL     = 89761
        };

        void EnterEvadeMode()
        {
        }

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER && seatId == 0)
                events.ScheduleEvent(EVENT_DROP_PLAYER, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DROP_PLAYER:
                    {
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                        {
                            passenger->ExitVehicle();
                            passenger->CastSpell(passenger, SPELL_TENTACLE_EXIT, true);
                            passenger->CastSpell(passenger, SPELL_TENTACLE_FALL, true);
                        }
                        me->DespawnOrUnsummon(10000);
                        events.CancelEvent(EVENT_DROP_PLAYER);
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
        return new npc_th_tentacle_of_iso_rath_vehAI(creature);
    }
};

class spell_th_iso_rath_blood : public SpellScriptLoader
{
public:
    spell_th_iso_rath_blood() : SpellScriptLoader("spell_th_iso_rath_blood")
    {
    }

    enum creditId
    {
        QUEST_CREDIT_DEVOURED  = 48108
    };

    enum spellId
    {
        SPELL_FADE_TO_BLACK         = 89404,
        SPELL_NIGHTMARE_TELEPORT    = 89471
    };

    class spell_th_iso_rath_blood_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_th_iso_rath_blood_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    target->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_DEVOURED);
                    target->CastWithDelay(2000, target, SPELL_FADE_TO_BLACK, true);
                    target->CastWithDelay(3000, target, SPELL_NIGHTMARE_TELEPORT, true);
                }
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_th_iso_rath_blood_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }

    };

    AuraScript* GetAuraScript() const
    {
        return new spell_th_iso_rath_blood_AuraScript();
    }
};

class npc_th_thrall_maelstrom : public CreatureScript
{
public:
    npc_th_thrall_maelstrom() : CreatureScript("npc_th_thrall_maelstrom")
    {
    }

    enum questId
    {
        QUEST_THE_WORLDBREAKER  = 27378
    };

    enum eventId
    {
        EVENT_SEARCH_FOR_PLAYERS    = 1,
        EVENT_SEARCH_FOR_WB
    };

    enum npcId
    {
        NPC_DEATHWING   = 48005,
        NPC_NOBUNDO     = 48079,
        NPC_AGGRA       = 48076,
        NPC_MULN        = 48084,
        NPC_ROCKS       = 48202
    };

    enum spellId
    {
        SPELL_MAELSTROM_NIGHTMARE   = 89471,
        SPELL_ANCESTRAL_SPIRIT      = 89474,
        SPELL_CALL_OF_THE_ELEMENTS  = 89631,
        SPELL_UNIQUE_PHASING        = 60191
    };

    struct npc_th_thrall_maelstromAI : public ScriptedAI
    {
        npc_th_thrall_maelstromAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            DoCast(SPELL_CALL_OF_THE_ELEMENTS);
            if (!me->ToTempSummon())
            {
                events.ScheduleEvent(EVENT_SEARCH_FOR_PLAYERS, 2000);
                events.ScheduleEvent(EVENT_SEARCH_FOR_WB, 2000);
            }
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            events.CancelEvent(EVENT_SEARCH_FOR_PLAYERS);
            events.CancelEvent(EVENT_SEARCH_FOR_WB);
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
                    case EVENT_SEARCH_FOR_PLAYERS:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 15.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(15.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                            {
                                if ((*itr)->HasAura(SPELL_MAELSTROM_NIGHTMARE) && me->GetPhaseMask() == 2 && !(*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SERVER_CONTROLLED))
                                {
                                    (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SERVER_CONTROLLED);
                                    Talk(0, (*itr)->GetGUID());
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_PLAYERS, 2000);
                        break;
                    }
                    case EVENT_SEARCH_FOR_WB:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 45.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(45.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                            {
                                if (!(*itr)->HasAura(SPELL_MAELSTROM_NIGHTMARE) && me->GetPhaseMask() == 2 && (*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_WORLDBREAKER) == QUEST_STATUS_INCOMPLETE)
                                {
                                    (*itr)->SetPhaseMask(4, true);
                                    (*itr)->AddAura(SPELL_UNIQUE_PHASING, (*itr));
                                    Creature* thrall = (*itr)->FindNearestCreature(me->GetEntry(), 100.0f, true);
                                    if (!thrall)
                                    {
                                        (*itr)->SummonCreature(me->GetEntry(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_DEATHWING, 927.48f, 882.57f, 6.08f, 3.91f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_NOBUNDO, 822.44f, 653.03f, -8.58f, 1.39f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_MULN, 722.82f, 823.13f, 129.73f, 0.63f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_AGGRA, 1083.57f, 745.93f, 95.91f, 2.88f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);

                                        // Rocks
                                        (*itr)->SummonCreature(NPC_ROCKS, 927.48f + urand(2, 8), 882.57f - urand(2, 8), 6.08f + urand(2, 8), 3.91f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_ROCKS, 822.44f - urand(2, 8), 653.03f + urand(2, 8), -8.58f + urand(2, 8), 1.39f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_ROCKS, 722.82f + urand(2, 8), 823.13f - urand(2, 8), 129.73f, 0.63f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                        (*itr)->SummonCreature(NPC_ROCKS, 1083.57f - urand(2, 8), 745.93f + urand(2, 8), 95.91f, 2.88f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                    }
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_WB, 2000);
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
        return new npc_th_thrall_maelstromAI(creature);
    }
};

class npc_th_deathwing_maelstrom : public CreatureScript
{
public:
    npc_th_deathwing_maelstrom() : CreatureScript("npc_th_deathwing_maelstrom")
    {
    }

    enum eventId
    {
        EVENT_MOVE_TO_NOBUNDO   = 1,
        EVENT_KILL_NOBUNDO,
        EVENT_THRALL_NOBUNDO,
        EVENT_MOVE_TO_AGGRA,
        EVENT_KILL_AGGRA,
        EVENT_THRALL_AGGRA,
        EVENT_MOVE_TO_MULN,
        EVENT_KILL_MULN,
        EVENT_THRALL_MULN,
        EVENT_MOVE_TO_PLATFORM,
        EVENT_KILL_PLAYER,
        EVENT_DESPAWN_ALL
    };

    enum pointId
    {
        POINT_NOBUNDO   = 1,
        POINT_AGGRA,
        POINT_MULN,
        POINT_PLATFORM
    };

    enum npcId
    {
        NPC_NOBUNDO     = 48079,
        NPC_AGGRA       = 48076,
        NPC_MULN        = 48084,
        NPC_THRALL      = 48051
    };

    enum spellId
    {
        SPELL_FIREBURST_LAUNCH  = 89580,
        SPELL_FIREBURST_EFFECT  = 95470,
        SPELL_NIGHTMARE_CREDIT  = 89656
    };

    struct npc_th_deathwing_maelstromAI : public ScriptedAI
    {
        npc_th_deathwing_maelstromAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetWalk(false);
            me->SetCanFly(true);
            me->SetHover(true);
            me->SetDisableGravity(true);
            events.ScheduleEvent(EVENT_MOVE_TO_NOBUNDO, 5000);
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
                    case EVENT_MOVE_TO_NOBUNDO:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_NOBUNDO, 855.36f, 753.03f, 4.36f, false);
                        events.CancelEvent(EVENT_MOVE_TO_NOBUNDO);
                        break;
                    }
                    case EVENT_KILL_NOBUNDO:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_NOBUNDO, 500.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                        (*iter)->Kill((*iter), false);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_THRALL_NOBUNDO, 500);
                        events.CancelEvent(EVENT_KILL_NOBUNDO);
                        break;
                    }
                    case EVENT_THRALL_NOBUNDO:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_THRALL, 500.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    {
                                        (*iter)->AI()->Talk(1);
                                        (*iter)->AI()->TalkWithDelay(5000, 2, invoker->GetGUID());
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_AGGRA, 10000);
                        events.CancelEvent(EVENT_THRALL_NOBUNDO);
                        break;
                    }
                    case EVENT_MOVE_TO_AGGRA:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AGGRA, 997.36f, 748.27f, 116.95f, false);
                        events.CancelEvent(EVENT_MOVE_TO_AGGRA);
                        break;
                    }
                    case EVENT_KILL_AGGRA:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_AGGRA, 1000.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                        (*iter)->Kill((*iter), false);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_THRALL_AGGRA, 500);
                        events.CancelEvent(EVENT_KILL_AGGRA);
                        break;
                    }
                    case EVENT_THRALL_AGGRA:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_THRALL, 500.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    {
                                        (*iter)->AI()->Talk(3);
                                        (*iter)->AI()->TalkWithDelay(5000, 4, invoker->GetGUID());
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_MULN, 10000);
                        events.CancelEvent(EVENT_THRALL_AGGRA);
                        break;
                    }
                    case EVENT_MOVE_TO_MULN:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_MULN, 786.34f, 825.72f, 158.18f, false);
                        events.CancelEvent(EVENT_MOVE_TO_MULN);
                        break;
                    }
                    case EVENT_KILL_MULN:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_MULN, 500.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                        (*iter)->Kill((*iter), false);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_THRALL_MULN, 500);
                        events.CancelEvent(EVENT_KILL_MULN);
                        break;
                    }
                    case EVENT_THRALL_MULN:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_THRALL, 500.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    {
                                        (*iter)->AI()->Talk(5);
                                        (*iter)->AI()->TalkWithDelay(5000, 6, invoker->GetGUID());
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_PLATFORM, 10000);
                        events.CancelEvent(EVENT_THRALL_MULN);
                        break;
                    }
                    case EVENT_MOVE_TO_PLATFORM:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_PLATFORM, 873.09f, 970.67f, 22.02f, false);
                        events.CancelEvent(EVENT_MOVE_TO_PLATFORM);
                        break;
                    }
                    case EVENT_KILL_PLAYER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                                invoker->CastWithDelay(250, invoker, SPELL_NIGHTMARE_CREDIT);

                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_THRALL, 100.0f);
                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                        (*iter)->AI()->Talk(7);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_DESPAWN_ALL, 8000);
                        events.CancelEvent(EVENT_KILL_PLAYER);
                        break;
                    }
                    case EVENT_DESPAWN_ALL:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 1000.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(1000.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*itr)->ToCreature()->DespawnOrUnsummon(1);
                            }
                        }
                        me->DespawnOrUnsummon(10000);
                        events.CancelEvent(EVENT_DESPAWN_ALL);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_NOBUNDO:
                {
                    me->SetFacingTo(4.36f);
                    DoCast(SPELL_FIREBURST_LAUNCH);
                    me->CastWithDelay(3100, me, SPELL_FIREBURST_EFFECT, true);
                    events.ScheduleEvent(EVENT_KILL_NOBUNDO, 3500);
                    break;
                }
                case POINT_AGGRA:
                {
                    me->SetFacingTo(6.25f);
                    DoCast(SPELL_FIREBURST_LAUNCH);
                    me->CastWithDelay(3100, me, SPELL_FIREBURST_EFFECT, true);
                    events.ScheduleEvent(EVENT_KILL_AGGRA, 3500);
                    break;
                }
                case POINT_MULN:
                {
                    me->SetFacingTo(3.17f);
                    DoCast(SPELL_FIREBURST_LAUNCH);
                    me->CastWithDelay(3100, me, SPELL_FIREBURST_EFFECT, true);
                    events.ScheduleEvent(EVENT_KILL_MULN, 3500);
                    break;
                }
                case POINT_PLATFORM:
                {
                    me->SetFacingTo(1.83f);
                    DoCast(SPELL_FIREBURST_LAUNCH);
                    me->CastWithDelay(3100, me, SPELL_FIREBURST_EFFECT, true);
                    events.ScheduleEvent(EVENT_KILL_PLAYER, 3500);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_deathwing_maelstromAI(creature);
    }
};

class npc_th_tentacle_of_iso_rath_stomach : public CreatureScript
{
public:
    npc_th_tentacle_of_iso_rath_stomach() : CreatureScript("npc_th_tentacle_of_iso_rath_stomach")
    {
    }

    struct npc_th_tentacle_of_iso_rath_stomachAI : public ScriptedAI
    {
        npc_th_tentacle_of_iso_rath_stomachAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_THWOMP    = 1
        };

        enum spellId
        {
            SPELL_THWOMP            = 89918,
            SPELL_SUMMON_JALARA     = 90820,
            SPELL_SUMMON_DIMBLAZE   = 90813,
            SPELL_SUMMON_DUARN      = 90822,
            SPELL_SUMMON_MYLRA      = 90823
        };

        enum entryId
        {
            NPC_ENTRY_DUARN     = 48794,
            NPC_ENTRY_DIMBLAZE  = 48739,
            NPC_ENTRY_JALARA    = 48790,
            NPC_ENTRY_MYLRA     = 48796
        };

        void EnterEvadeMode()
        {
            events.Reset();
        }

        void OnCharmed(bool apply)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.ScheduleEvent(EVENT_THWOMP, 1000);
        }

        void JustDied(Unit* killer)
        {
            if (killer->GetTypeId() == TYPEID_PLAYER)
            {
                switch (me->GetEntry())
                {
                    case NPC_ENTRY_DIMBLAZE:
                        killer->CastSpell(me, SPELL_SUMMON_DIMBLAZE, true);
                        break;
                    case NPC_ENTRY_DUARN:
                        killer->CastSpell(me, SPELL_SUMMON_DUARN, true);
                        break;
                    case NPC_ENTRY_JALARA:
                        killer->CastSpell(me, SPELL_SUMMON_JALARA, true);
                        break;
                    case NPC_ENTRY_MYLRA:
                        killer->CastSpell(me, SPELL_SUMMON_MYLRA, true);
                        break;
                    default:
                        break;
                }
            }
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
                    case EVENT_THWOMP:
                    {
                        events.RescheduleEvent(EVENT_THWOMP, urand(4000, 6000));
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
        return new npc_th_tentacle_of_iso_rath_stomachAI(creature);
    }
};

class npc_th_iso_rath_rescued : public CreatureScript
{
public:
    npc_th_iso_rath_rescued() : CreatureScript("npc_th_iso_rath_rescued")
    {
    }

    struct npc_th_iso_rath_rescuedAI : public ScriptedAI
    {
        npc_th_iso_rath_rescuedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_CHECK_BUFF    = 1,
            EVENT_FOLLOW_MASTER
        };

        enum spellId
        {
            SPELL_FIELD_OF_RESTORATION  = 90736
        };

        enum npcId
        {
            NPC_DIMBLAZE    = 48731,
            NPC_JALARA      = 48732,
            NPC_DUARN       = 48733,
            NPC_MYLRA       = 48734
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            events.ScheduleEvent(EVENT_CHECK_BUFF, 2000);
            events.ScheduleEvent(EVENT_FOLLOW_MASTER, 1000);
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 75 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 75 + me->getLevel())));
        }

        void CompleteCreditAoE()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    switch (me->GetEntry())
                    {
                        case NPC_DIMBLAZE:
                            (*itr)->ToPlayer()->KilledMonsterCredit(NPC_DIMBLAZE);
                            break;
                        case NPC_JALARA:
                            (*itr)->ToPlayer()->KilledMonsterCredit(NPC_JALARA);
                            break;
                        case NPC_DUARN:
                            (*itr)->ToPlayer()->KilledMonsterCredit(NPC_DUARN);
                            break;
                        case NPC_MYLRA:
                            (*itr)->ToPlayer()->KilledMonsterCredit(NPC_MYLRA);
                            break;
                        default:
                            break;
                    }
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
                    case EVENT_CHECK_BUFF:
                    {
                        if (me->HasAura(SPELL_FIELD_OF_RESTORATION))
                        {
                            CompleteCreditAoE();
                            events.CancelEvent(EVENT_CHECK_BUFF);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_BUFF, 2000);
                        break;
                    }
                    case EVENT_FOLLOW_MASTER:
                    {
                        if (Unit* owner = me->ToTempSummon()->GetSummoner())
                        {
                            if (owner->GetDistance(me) > 10.0f)
                            {
                                me->GetMotionMaster()->MovementExpired(false);
                                me->GetMotionMaster()->MoveFollow(owner, 3.0f, urand(1, 4));
                            }
                        }
                        events.RescheduleEvent(EVENT_FOLLOW_MASTER, 5000);
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
        return new npc_th_iso_rath_rescuedAI(creature);
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
    new areatrigger_th_glopgut_hollow();
    new npc_th_russel_brower();
    new npc_th_hammelhand();
    new npc_th_grundy_mcgraff();
    new npc_th_wedding_veh();
    new npc_th_wedding_mirror();
    new npc_th_wedding_fanny();
    new npc_th_wedding_guests();
    new npc_th_wedding_beast();
    new npc_th_wedding_kurdran();
    new npc_th_twilight_shadowshifter();
    new npc_th_darunga();
    new npc_th_flynn_dunwald_darunga();
    new npc_th_earthen_ring_gryphon();
    new npc_th_earthen_ring_gryphon_summoned();
    new npc_th_tentacle_of_iso_rath_veh();
    new spell_th_iso_rath_blood();
    new npc_th_thrall_maelstrom();
    new npc_th_deathwing_maelstrom();
    new npc_th_tentacle_of_iso_rath_stomach();
    new npc_th_iso_rath_rescued();
}
