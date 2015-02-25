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

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
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
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(5.0f))
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
            if (who->GetTypeId() == TYPEID_PLAYER && roll_chance_f(10))
                Talk(0);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
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
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(5.0f))
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

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
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

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
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
            if (!UpdateVictim() && me->isInCombat())
                return;

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
            if (!UpdateVictim() && me->isInCombat())
                return;

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
        QUEST_SCOUTING_THE_SHORE_A      = 27341,
        QUEST_SCOUTING_THE_SHORE_H      = 27610
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && (player->GetQuestStatus(QUEST_SCOUTING_THE_SHORE_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_SCOUTING_THE_SHORE_H) == QUEST_STATUS_INCOMPLETE))
        {
            player->CompleteQuest(QUEST_SCOUTING_THE_SHORE_A);
            player->CompleteQuest(QUEST_SCOUTING_THE_SHORE_H);
        }
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
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY) || (*iter)->GetGUIDLow() == 755184)
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
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY) || (*iter)->GetGUIDLow() == 755184)
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
                if ((*iter)->HasAura(SPELL_INCOMING_ARTILLERY) || (*iter)->GetGUIDLow() == 755184)
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
                            if (me->GetHealth() >= me->GetMaxHealth() * 0.75f)
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
        QUEST_EYE_SPY_A     = 28244,
        QUEST_EYE_SPY_H     = 27955
    };

    enum npcId
    {
        NPC_EYE_OF_TWILIGHT_VEHICLE     = 47273
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_EYE_SPY_A) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(60191, player);
            player->SummonCreature(NPC_EYE_OF_TWILIGHT_VEHICLE, -3183.00f, -5059.83f, 120.99f, 6.01f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }
        if (player->GetQuestStatus(QUEST_EYE_SPY_H) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(60191, player);
            player->SummonCreature(NPC_EYE_OF_TWILIGHT_VEHICLE, -3658.64f, -5241.72f, 42.13f, 4.40f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
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
            NPC_GARONA      = 47274,
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
                                Creature* garona = me->FindNearestCreature(NPC_GARONA, 40.0f);
                                if (blundy || garona)
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
                        {
                            if (owner->getRaceMask() & RACEMASK_ALLIANCE)
                                TalkWithDelay(1000, 0, owner->GetGUID());
                            else
                                Talk(2, owner->GetGUID());
                        }
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

                                    if (player->getRaceMask() & RACEMASK_ALLIANCE)
                                        (*iter)->AI()->TalkWithDelay(9000, 1, player->GetGUID());
                                    else
                                        (*iter)->AI()->TalkWithDelay(8000, 6, player->GetGUID());

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
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->SummonCreature(NPC_EYE, -5088.91f, -4669.11f, 356.37f, 5.18f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
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
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
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
            EVENT_CHECK_BUFF        = 1,
            EVENT_FOLLOW_MASTER,
            EVENT_STORMSTRIKE,
            EVENT_LAVA_LASH,
            EVENT_HEALING_WAVE,
            EVENT_LIGHTNING_BOLT,
            EVENT_MAGMA_TOTEM,
            EVENT_THUNDERSTORM,
            EVENT_WATER_SHIELD,
            EVENT_LAVA_BURST,
            EVENT_EARTH_SHIELD,
            EVENT_FROST_SHOCK,
            EVENT_CHAIN_HEAL,
            EVENT_ATTACK_BRAIN
        };

        enum spellId
        {
            SPELL_FIELD_OF_RESTORATION  = 90736,

            // Dimblaze
            SPELL_STORMSTRIKE           = 78144,
            SPELL_LAVA_LASH             = 78146,

            // Jalara & Mylra
            SPELL_HEALING_WAVE          = 91017,
            SPELL_LIGHTNING_BOLT        = 79884,
            SPELL_MAGMA_TOTEM           = 78770,
            SPELL_THUNDERSTORM          = 79797,
            SPELL_WATER_SHIELD          = 79949,
            SPELL_LAVA_BURST            = 79886,

            // Duarn
            SPELL_EARTH_SHIELD          = 79927,
            SPELL_FROST_SHOCK           = 79925,
            SPELL_CHAIN_HEAL            = 91018,

            SPELL_UNIQUE_PHASING        = 60191
        };

        enum npcId
        {
            NPC_DIMBLAZE    = 48731,
            NPC_JALARA      = 48732,
            NPC_DUARN       = 48733,
            NPC_MYLRA       = 48734,
            NPC_BRAIN       = 47960
        };

        void IsSummonedBy(Unit* owner)
        {
            if (me->GetPhaseMask() >= 2048)
            {
                events.ScheduleEvent(EVENT_ATTACK_BRAIN, 6000);
                owner->AddAura(SPELL_UNIQUE_PHASING, me);
            }
            else
            {
                TalkWithDelay(2000, 1);
                events.ScheduleEvent(EVENT_CHECK_BUFF, 2000);
                events.ScheduleEvent(EVENT_FOLLOW_MASTER, 1000);
            }

            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 75 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 75 + me->getLevel())));
        }

        void EnterCombat(Unit* /*who*/)
        {
            switch (me->GetEntry())
            {
                case NPC_DIMBLAZE:
                {
                    events.ScheduleEvent(EVENT_STORMSTRIKE, 1000);
                    events.ScheduleEvent(EVENT_LAVA_LASH, 2500);
                    break;
                }
                case NPC_JALARA:
                case NPC_MYLRA:
                {
                    events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 1000);
                    events.ScheduleEvent(EVENT_LAVA_BURST, 5000);
                    if (!me->HasAura(SPELL_WATER_SHIELD))
                        DoCast(SPELL_WATER_SHIELD);
                    DoCast(SPELL_MAGMA_TOTEM);
                    events.ScheduleEvent(EVENT_THUNDERSTORM, 8000);
                    events.ScheduleEvent(EVENT_HEALING_WAVE, 10000);
                    break;
                }
                case NPC_DUARN:
                {
                    if (!me->HasAura(SPELL_EARTH_SHIELD))
                        DoCast(SPELL_EARTH_SHIELD);
                    events.ScheduleEvent(EVENT_FROST_SHOCK, 1000);
                    events.ScheduleEvent(EVENT_CHAIN_HEAL, 6000);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
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
                            Talk(0);
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
                            if (owner->GetDistance(me) > 15.0f && owner->GetPhaseMask() < 2048)
                            {
                                me->GetMotionMaster()->MovementExpired(false);
                                me->GetMotionMaster()->MoveFollow(owner, 2.0f, urand(1, 4));
                            }
                            if (owner->GetDistance(me) > 80.0f && owner->GetPhaseMask() >= 2048)
                            {
                                me->GetMotionMaster()->MovementExpired(false);
                                me->GetMotionMaster()->MoveFollow(owner, 1.5f, urand(1, 4));
                            }
                        }
                        events.RescheduleEvent(EVENT_FOLLOW_MASTER, 5000);
                        break;
                    }
                    case EVENT_CHAIN_HEAL:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* owner = me->ToTempSummon()->GetSummoner())
                        {
                            if (owner->GetHealth() <= owner->GetMaxHealth() * 0.65f)
                                DoCast(owner, SPELL_CHAIN_HEAL);
                        }
                        events.RescheduleEvent(EVENT_CHAIN_HEAL, 6000);
                        break;
                    }
                    case EVENT_LAVA_BURST:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_LAVA_BURST);
                        events.RescheduleEvent(EVENT_LAVA_BURST, 3000);
                        break;
                    }
                    case EVENT_LIGHTNING_BOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_LIGHTNING_BOLT);
                        events.RescheduleEvent(EVENT_LIGHTNING_BOLT, urand(3500, 7000));
                        break;
                    }
                    case EVENT_STORMSTRIKE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_STORMSTRIKE);
                        events.RescheduleEvent(EVENT_STORMSTRIKE, urand(3500, 5000));
                        break;
                    }
                    case EVENT_LAVA_LASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_LAVA_LASH);
                        events.RescheduleEvent(EVENT_LAVA_LASH, urand(3500, 5000));
                        break;
                    }
                    case EVENT_HEALING_WAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* owner = me->ToTempSummon()->GetSummoner())
                        {
                            if (owner->GetHealth() <= (owner->GetMaxHealth() * 0.65f))
                                DoCast(owner, SPELL_HEALING_WAVE);
                        }
                        events.RescheduleEvent(EVENT_HEALING_WAVE, 10000);
                        break;
                    }
                    case EVENT_THUNDERSTORM:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* nearestVictim = me->SelectNearbyTarget(me, 5.0f))
                            DoCast(SPELL_THUNDERSTORM);
                        events.RescheduleEvent(EVENT_THUNDERSTORM, 15000);
                        break;
                    }
                    case EVENT_FROST_SHOCK:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_FROST_SHOCK);
                        events.RescheduleEvent(EVENT_FROST_SHOCK, urand(3500, 5000));
                        break;
                    }
                    case EVENT_ATTACK_BRAIN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_BRAIN, 800.0f);
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
                        events.CancelEvent(EVENT_ATTACK_BRAIN);
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

class npc_th_earthcaller_yevaa : public CreatureScript
{
public:
    npc_th_earthcaller_yevaa() : CreatureScript("npc_th_earthcaller_yevaa")
    {
    }

    enum questId
    {
        QUEST_THE_TERRORS_OF_ISO_RATH   = 27379,
        QUEST_NIGHTMARE                 = 27380
    };

    enum npcId
    {
        NPC_BRAIN_OF_ISO_RATH   = 47960,
        NPC_DIMBLAZE            = 48731,
        NPC_JALARA              = 48732,
        NPC_DUARN               = 48733,
        NPC_MYLRA               = 48734
    };

    enum spellId
    {
        SPELL_DEATH_PING_YEVAA      = 89660,
        SPELL_DIGESTIVE_CORROSION   = 90782,
        SPELL_UNIQUE_PHASING        = 60191
    };


    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_NIGHTMARE)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 800.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(800.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && (*itr)->GetEntry() == NPC_BRAIN_OF_ISO_RATH)
                        return false;
                }
            }
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->SummonCreature(NPC_BRAIN_OF_ISO_RATH, -2666.88f, -4982.06f, -128.80f, 3.40f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
            player->SummonCreature(creature->GetEntry(), creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
            player->SummonCreature(NPC_DIMBLAZE, -2733.77f, -5004.10f, -127.89f, 2.89f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
            player->SummonCreature(NPC_DUARN, -2735.32f, -4999.94f, -127.49f, 4.07f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
            player->SummonCreature(NPC_JALARA, -2737.35f, -4999.38f, -127.42f, 4.68f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
            player->SummonCreature(NPC_MYLRA, -2740.72f, -5000.21f, -127.12f, 4.68f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
            return false;
        }
        return true;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_THE_TERRORS_OF_ISO_RATH:
            {
                // Cleanup summons
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(player, 100.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                player->VisitNearbyObject(100.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                    }
                }
                return true;
            }
            case QUEST_NIGHTMARE:
            {
                player->RemoveAurasDueToSpell(SPELL_DIGESTIVE_CORROSION);
                return true;
            }
            default:
                break;
        }
        return true;
    }

    struct npc_th_earthcaller_yevaaAI : public ScriptedAI
    {
        npc_th_earthcaller_yevaaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DEATH_PING_YEVAA:
                {
                    Talk(0, caster->GetGUID());
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_earthcaller_yevaaAI(creature);
    }
};

class npc_th_brain_of_iso_rath : public CreatureScript
{
public:
    npc_th_brain_of_iso_rath() : CreatureScript("npc_th_brain_of_iso_rath")
    {
    }

    enum eventId
    {
        EVENT_MIND_FLAY     = 1
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING        = 60191,
        SPELL_DIGESTIVE_BURST       = 91100,
        SPELL_MIND_FLAY             = 91134,
        SPELL_SUMMON_EXIT_GRYPHON   = 89823
    };

    enum creditId
    {
        CREDIT_BRAIN_OF_ISO_RATH    = 47960
    };

    struct npc_th_brain_of_iso_rathAI : public ScriptedAI
    {
        npc_th_brain_of_iso_rathAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            me->SetFloatValue(UNIT_FIELD_COMBATREACH, 7);
            me->SetControlled(true, UNIT_STATE_ROOT);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
            {
                if (invoker->GetTypeId() == TYPEID_PLAYER)
                {
                    invoker->ToPlayer()->KilledMonsterCredit(CREDIT_BRAIN_OF_ISO_RATH);
                    invoker->CastSpell(invoker, SPELL_SUMMON_EXIT_GRYPHON, true);
                }
            }
            me->DespawnOrUnsummon(20000);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                TalkWithDelay(2500, 0, invoker->GetGUID());

            DoCast(SPELL_DIGESTIVE_BURST);
            events.ScheduleEvent(EVENT_MIND_FLAY, 10000);
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
                    case EVENT_MIND_FLAY:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_MIND_FLAY);
                        events.RescheduleEvent(EVENT_MIND_FLAY, urand(6000, 9000));
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
        return new npc_th_brain_of_iso_rathAI(creature);
    }
};

class npc_th_earthen_ring_gryphon_exit : public CreatureScript
{
public:
    npc_th_earthen_ring_gryphon_exit() : CreatureScript("npc_th_earthen_ring_gryphon_exit")
    {
    }

    enum actionId
    {
        ACTION_WP_START = 1,
    };

    enum eventId
    {
        EVENT_RIDE_INVOKER  = 1
    };

    enum spellId
    {
        SPELL_DIGESTIVE_CORROSION   = 90782
    };

    struct npc_th_earthen_ring_gryphon_exitAI : public npc_escortAI
    {
        npc_th_earthen_ring_gryphon_exitAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->AddUnitState(UNIT_STATE_ROTATING | UNIT_STATE_ROAMING_MOVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 6000);
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
                case 3: // Dismount
                {
                    if (Vehicle* vehicle = me->GetVehicle())
                        vehicle->RemoveAllPassengers();
                    me->DespawnOrUnsummon(2000);
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
                    Start(false, true, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                    {
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
                            passenger->MonsterSay("You're truly a force to be reckoned with. The beast is done with. Let's get out of here.", 0, invoker->GetGUID());
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
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RIDE_INVOKER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() == TYPEID_PLAYER && !invoker->isAlive())
                                invoker->ToPlayer()->ResurrectPlayer(100, false);
                            invoker->ClearInCombat();
                            invoker->RemoveAurasDueToSpell(SPELL_DIGESTIVE_CORROSION);
                            invoker->EnterVehicle(me, 0);
                        }
                        events.CancelEvent(EVENT_RIDE_INVOKER);
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
        return new npc_th_earthen_ring_gryphon_exitAI(creature);
    }
};

class npc_th_vermillion_sentinel : public CreatureScript
{
public:
    npc_th_vermillion_sentinel() : CreatureScript("npc_th_vermillion_sentinel")
    {
    }

    enum actionId
    {
        ACTION_WP_START     = 1,
    };

    enum eventId
    {
        EVENT_RIDE_INVOKER      = 1,
        EVENT_MOVE_TO_INVOKER
    };

    enum spellId
    {
        SPELL_SUMMON_LIRASTRASZA    = 85270
    };

    enum pointId
    {
        POINT_INVOKER   = 1
    };

    struct npc_th_vermillion_sentinelAI : public npc_escortAI
    {
        npc_th_vermillion_sentinelAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
            me->SetSpeed(MOVE_RUN, 4.5f, true);
            me->SetSpeed(MOVE_WALK, 4.5f, true);
            me->SetWalk(false);
            events.ScheduleEvent(EVENT_MOVE_TO_INVOKER, 500);
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1000);
        }

        void EnterEvadeMode()
        {
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                {
                    me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
                    me->SetSpeed(MOVE_RUN, 4.5f, true);
                    me->SetSpeed(MOVE_WALK, 4.5f, true);
                    break;
                }
                case 6: // Dismount
                {
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        invoker->CastSpell(invoker, SPELL_SUMMON_LIRASTRASZA, true);
                    if (Vehicle* vehicle = me->GetVehicle())
                        vehicle->RemoveAllPassengers();
                    me->DespawnOrUnsummon(500);
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
                    Start(false, true, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_TO_INVOKER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            me->NearTeleportTo(invoker->GetPositionX(), invoker->GetPositionY(), invoker->GetPositionZ(), invoker->GetOrientation());
                            events.ScheduleEvent(EVENT_RIDE_INVOKER, 100);
                        }
                        events.CancelEvent(EVENT_MOVE_TO_INVOKER);
                        break;
                    }
                    case EVENT_RIDE_INVOKER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (me->GetDistance(invoker) < 25)
                            {
                                if (invoker->GetTypeId() == TYPEID_PLAYER && !invoker->isAlive())
                                    invoker->ToPlayer()->ResurrectPlayer(100, false);
                                invoker->ClearInCombat();
                                invoker->Dismount();
                                invoker->EnterVehicle(me, 0);
                                DoAction(ACTION_WP_START);
                                me->SetSpeed(MOVE_FLIGHT, 2.4f, true);
                                me->SetSpeed(MOVE_RUN, 2.4f, true);
                                me->SetSpeed(MOVE_WALK, 2.4f, true);
                                events.CancelEvent(EVENT_RIDE_INVOKER);
                                break;
                            }
                            else
                            {
                                me->NearTeleportTo(invoker->GetPositionX(), invoker->GetPositionY(), invoker->GetPositionZ(), invoker->GetOrientation());
                                events.RescheduleEvent(EVENT_RIDE_INVOKER, 500);
                            }
                        }
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
        return new npc_th_vermillion_sentinelAI(creature);
    }
};

class npc_th_lirastrasza_summoned : public CreatureScript
{
public:
    npc_th_lirastrasza_summoned() : CreatureScript("npc_th_lirastrasza_summoned")
    {
    }

    enum eventId
    {
        EVENT_LAND          = 1,
        EVENT_MOVE_AWAY,
        EVENT_MOVE_TAKEOFF
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING        = 60191,
        SPELL_TRANSFORM_LIRA        = 85271,
        SPELL_DISABLING_IMPACT      = 85328,
        SPELL_LIRASTRASZA_CREDIT    = 85332
    };

    enum pointId
    {
        POINT_LAND      = 1,
        POINT_AWAY,
        POINT_TAKEOFF
    };

    struct npc_th_lirastrasza_summonedAI : public ScriptedAI
    {
        npc_th_lirastrasza_summonedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->CastSpell(owner, SPELL_DISABLING_IMPACT, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->SetWalk(true);
            events.ScheduleEvent(EVENT_LAND, 1000);
        }

        void EnterEvadeMode()
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LAND:
                    {
                        x = -2896.23f;
                        y = -3892.21f;
                        z = 265.60f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        DoCast(SPELL_LIRASTRASZA_CREDIT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -2880.28f, -3893.02f, 264.18f);
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        break;
                    }
                    case EVENT_MOVE_TAKEOFF:
                    {
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 30.0f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        events.CancelEvent(EVENT_MOVE_TAKEOFF);
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
                case POINT_LAND:
                {
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->SetHover(false);
                    me->CastWithDelay(1000, me, SPELL_TRANSFORM_LIRA);
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                    {
                        TalkWithDelay(2500, 0, invoker->GetGUID());
                        TalkWithDelay(9000, 1);
                        TalkWithDelay(16000, 2);
                        TalkWithDelay(24000, 3, invoker->GetGUID());
                    }
                    events.ScheduleEvent(EVENT_MOVE_AWAY, 23000);
                    break;
                }
                case POINT_AWAY:
                {
                    DoCast(SPELL_TRANSFORM_LIRA);
                    me->RemoveAurasDueToSpell(SPELL_TRANSFORM_LIRA);
                    events.ScheduleEvent(EVENT_MOVE_TAKEOFF, 1000);
                    break;
                }
                case POINT_TAKEOFF:
                {
                    me->DespawnOrUnsummon(5000);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_lirastrasza_summonedAI(creature);
    }
};

class npc_th_vermillion_mender : public CreatureScript
{
public:
    npc_th_vermillion_mender() : CreatureScript("npc_th_vermillion_mender")
    {
    }

    struct npc_th_vermillion_menderAI : public ScriptedAI
    {
        npc_th_vermillion_menderAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void JustDied(Unit* killer)
        {
            if (killer->GetTypeId() == TYPEID_PLAYER)
                killer->ToPlayer()->KilledMonsterCredit(45746);
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
                        if (Unit* victim = me->SelectNearestTarget(50.0f))
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
        return new npc_th_vermillion_menderAI(creature);
    }
};

class spell_th_ruby_seeds : public SpellScriptLoader
{
public:
    spell_th_ruby_seeds() : SpellScriptLoader("spell_th_ruby_seeds")
    {
    }

    class spell_th_ruby_seeds_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_ruby_seeds_SpellScript);

        enum Id
        {
            NPC_TWILIGHT_WYRMKILLER     = 45748,
            SPELL_RETURN_TO_EARTH       = 85390,
            CREDIT_RETURNED             = 45503
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->GetTypeId() != TYPEID_UNIT)
                        return SPELL_FAILED_BAD_TARGETS;
                    if (target->ToCreature()->GetEntry() != 45748 || target->HasAura(SPELL_RETURN_TO_EARTH))
                        return SPELL_FAILED_BAD_TARGETS;
                    else
                        return SPELL_CAST_OK;
                }
            }
            return SPELL_FAILED_BAD_TARGETS;
        }

        void HandleLaunchSeedEffect()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    target->CastSpell(target, SPELL_RETURN_TO_EARTH, true);

                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->ToPlayer()->KilledMonsterCredit(CREDIT_RETURNED);

                    target->ToCreature()->DespawnOrUnsummon(10000);
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_ruby_seeds_SpellScript::CheckCast);
            AfterCast += SpellCastFn(spell_th_ruby_seeds_SpellScript::HandleLaunchSeedEffect);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_ruby_seeds_SpellScript();
    }
};

class npc_th_dragonmaw_pass_fighter : public CreatureScript
{
public:
    npc_th_dragonmaw_pass_fighter() : CreatureScript("npc_th_dragonmaw_pass_fighter")
    {
    }

    struct npc_th_dragonmaw_pass_fighterAI : public ScriptedAI
    {
        npc_th_dragonmaw_pass_fighterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1,
            EVENT_FAKE_SHOT
        };

        enum spellId
        {
            SPELL_FAKE_SHOT     = 69509
        };

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void Reset()
        {
            if (me->GetPositionZ() >= 81.75f || me->GetGUIDLow() == 841897 || me->GetGUIDLow() == 841892 ||
                me->GetGUIDLow() == 841898 || me->GetGUIDLow() == 841891 || me->GetGUIDLow() == 841901 || me->GetGUIDLow() == 841895 ||
                me->GetGUIDLow() == 764279 || me->GetGUIDLow() == 764280 || me->GetGUIDLow() == 764291 || me->GetGUIDLow() == 764304 ||
                me->GetGUIDLow() == 764301 || me->GetGUIDLow() == 764281 || me->GetGUIDLow() == 764300 || me->GetGUIDLow() == 764288 ||
                me->GetGUIDLow() == 764305 || me->GetGUIDLow() == 764289 || me->GetGUIDLow() == 764299 || me->GetGUIDLow() == 764290)
            {
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_FAKE_SHOT, urand(1000, 3000));
            }
            else
                events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
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
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(6.0f))
                        {
                            if (me->GetPositionZ() < 79.0f)
                                AttackStart(victim);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_FAKE_SHOT:
                    {
                        DoCast(SPELL_FAKE_SHOT);
                        events.RescheduleEvent(EVENT_FAKE_SHOT, urand(5000, 8500));
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
        return new npc_th_dragonmaw_pass_fighterAI(creature);
    }
};

class npc_th_master_mathias_shaw : public CreatureScript
{
public:
    npc_th_master_mathias_shaw() : CreatureScript("npc_th_master_mathias_shaw")
    {
    }

    enum questId
    {
        QUEST_IF_THE_KEY_FITS   = 28108,
        QUEST_PRESSING_FORWARD  = 28109
    };

    enum npcId
    {
        NPC_LIEUTENANT  = 47611
    };

    enum spellId
    {
        SPELL_SUMMON_SNIPER         = 88707,
        SPELL_SUMMON_DEMOLITIONIST  = 88708,
        SPELL_SUMMON_LIEUTENANT     = 88709,
        SPELL_SUMMON_MEDIC          = 88710,
        SPELL_SUMMON_MARINE         = 88711
    };


    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_IF_THE_KEY_FITS)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 800.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(800.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && (*itr)->GetEntry() == NPC_LIEUTENANT)
                        return false;
                }
            }
            player->CastSpell(player, SPELL_SUMMON_SNIPER, true);
            player->CastSpell(player, SPELL_SUMMON_DEMOLITIONIST, true);
            player->CastSpell(player, SPELL_SUMMON_LIEUTENANT, true);
            player->CastSpell(player, SPELL_SUMMON_MEDIC, true);
            player->CastSpell(player, SPELL_SUMMON_MARINE, true);
            creature->AI()->TalkWithDelay(5000, 0);
            return false;
        }
        return true;
    }

    #define GOSSIP_SQUADRON "Where is gone my squadron??"

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_IF_THE_KEY_FITS) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUADRON, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_IF_THE_KEY_FITS) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(player, 800.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                player->VisitNearbyObject(800.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && (*itr)->GetEntry() == NPC_LIEUTENANT)
                            return false;
                    }
                }
                player->CastSpell(player, SPELL_SUMMON_SNIPER, true);
                player->CastSpell(player, SPELL_SUMMON_DEMOLITIONIST, true);
                player->CastSpell(player, SPELL_SUMMON_LIEUTENANT, true);
                player->CastSpell(player, SPELL_SUMMON_MEDIC, true);
                player->CastSpell(player, SPELL_SUMMON_MARINE, true);
                creature->AI()->TalkWithDelay(5000, 0);
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
        return false;
    }

    struct npc_th_master_mathias_shawAI : public ScriptedAI
    {
        npc_th_master_mathias_shawAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_master_mathias_shawAI(creature);
    }
};

class npc_th_mathias_squadron : public CreatureScript
{
public:
    npc_th_mathias_squadron() : CreatureScript("npc_th_mathias_squadron")
    {
    }

    enum questId
    {
        QUEST_IF_THE_KEY_FITS_A     = 28108,
        QUEST_PRESSING_FORWARD_A    = 28109,
        QUEST_IF_THE_KEY_FITS_H     = 28092,
        QUEST_PRESSING_FORWARD_H    = 28093,
    };

    enum npcId
    {
        // Alliance
        NPC_LIEUTENANT      = 47611,
        NPC_DEMOLTIONIST    = 47612,
        NPC_MEDIC           = 47613,
        NPC_SNIPER          = 47614,
        NPC_MARINE          = 47615,
        NPC_GUARDSMAN       = 47394,

        // Horde
        NPC_VOLT            = 47377,
        NPC_TICKER          = 47375,
        NPC_PATCH           = 47374,
        NPC_NEWT            = 47376,
        NPC_GRIT            = 47378
    };

    enum eventId
    {
        EVENT_SEARCH_FOR_GATE       = 1,
        EVENT_FOLLOW_OWNER,
        EVENT_START_TALK,
        EVENT_INIT_MEDIC,
        EVENT_INIT_DEMOLITIONIST,
        EVENT_SUMMON_ASSAULTERS,
        EVENT_DEMOLITIONIST_DONE,
        EVENT_HOOKED_NET,
        EVENT_LOB_FIRE,
        EVENT_GRENADE,
        EVENT_HEAL,
        EVENT_SHOOT
    };

    enum spellId
    {
        SPELL_HOOKED_NET    = 88393,
        SPELL_SHOOT         = 88376,
        SPELL_LOB_FIRE      = 88392,
        SPELL_GRENADE       = 88408,
        SPELL_HEAL          = 88788
    };

    enum goId
    {
        GO_ENTRY_PHASED_GATE     = 206657
    };

    enum pointId
    {
        POINT_GATE              = 1,
        POINT_GATE_2,
        POINT_COVER_MEDIC,
        POINT_COVER_LIEUTENANT,
        POINT_COVER_SNIPER,
        POINT_COVER_MARINE
    };


    #define GOSSIP_GESTURES     "Make a series of complicated hand gestures."

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if ((player->GetQuestStatus(QUEST_IF_THE_KEY_FITS_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD_A) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_IF_THE_KEY_FITS_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD_H) == QUEST_STATUS_INCOMPLETE) &&
            creature->GetEntry() != NPC_LIEUTENANT && creature->GetEntry() != NPC_PATCH)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GESTURES, 0, 1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 1)
        {
            if (player->GetQuestStatus(QUEST_IF_THE_KEY_FITS_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD_A) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_IF_THE_KEY_FITS_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD_H) == QUEST_STATUS_INCOMPLETE)
            {
                switch (creature->GetEntry())
                {
                    case NPC_LIEUTENANT:
                    case NPC_PATCH:
                        creature->AI()->Talk(6);
                        break;
                    case NPC_MEDIC:
                    case NPC_SNIPER:
                    case NPC_GRIT:
                    case NPC_NEWT:
                        creature->AI()->Talk(1);
                        break;
                    case NPC_DEMOLTIONIST:
                    case NPC_TICKER:
                        creature->AI()->Talk(3);
                        break;
                    case NPC_MARINE:
                    case NPC_VOLT:
                        creature->AI()->Talk(0);
                        break;
                    default:
                        break;
                }
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
        return false;
    }

    struct npc_th_mathias_squadronAI : public ScriptedAI
    {
        npc_th_mathias_squadronAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            switch (me->GetEntry())
            {
                case NPC_LIEUTENANT:
                case NPC_PATCH:
                {
                    Talk(0);
                    TalkWithDelay(2000, 1);
                    TalkWithDelay(3500, 2);
                    events.ScheduleEvent(EVENT_SEARCH_FOR_GATE, 2000);
                    break;
                }
                default:
                    break;
            }
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 125 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 125 + me->getLevel())));
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_HOOKED_NET, 1000);
            if (me->GetEntry() == NPC_MARINE)
            {
                events.ScheduleEvent(EVENT_LOB_FIRE, 500);
                events.ScheduleEvent(EVENT_GRENADE, 2000);
            }
            if (me->GetEntry() == NPC_MEDIC)
                events.ScheduleEvent(EVENT_HEAL, urand(8000, 12000));
            events.ScheduleEvent(EVENT_SHOOT, 5000);
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
                    case EVENT_SHOOT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SHOOT, true);
                        events.RescheduleEvent(EVENT_SHOOT, urand(3000, 4500));
                        break;
                    }
                    case EVENT_LOB_FIRE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_LOB_FIRE, true);
                        events.RescheduleEvent(EVENT_SHOOT, urand(8000, 20000));
                        break;
                    }
                    case EVENT_GRENADE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_GRENADE, true);
                        events.RescheduleEvent(EVENT_GRENADE, urand(9000, 15000));
                        break;
                    }
                    case EVENT_HEAL:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (!me->isInCombat())
                        {
                            events.RescheduleEvent(EVENT_HEAL, 10000);
                            break;
                        }
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            DoCast(invoker, SPELL_HEAL);
                        events.RescheduleEvent(EVENT_HEAL, 10000);
                        break;
                    }
                    case EVENT_HOOKED_NET:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HOOKED_NET);
                        events.RescheduleEvent(EVENT_HOOKED_NET, urand(12500, 13000));
                        break;
                    }
                    case EVENT_SEARCH_FOR_GATE:
                    {
                        if (GameObject* gate = me->FindNearestGameObject(GO_ENTRY_PHASED_GATE, 80.0f))
                        {
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovementExpired(false);
                            me->GetMotionMaster()->MovePoint(POINT_GATE, -3972.73f, -3991.29f, 175.08f);
                            events.CancelEvent(EVENT_SEARCH_FOR_GATE);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_GATE, 2000);
                        break;
                    }
                    case EVENT_FOLLOW_OWNER:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(player, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                            player->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                                    {
                                        switch ((*itr)->GetEntry())
                                        {
                                            case NPC_MEDIC:
                                            case NPC_LIEUTENANT:
                                            case NPC_SNIPER:
                                            case NPC_MARINE:
                                            case NPC_DEMOLTIONIST:
                                            case NPC_NEWT:
                                            case NPC_GRIT:
                                            case NPC_VOLT:
                                            case NPC_PATCH:
                                            case NPC_TICKER:
                                            {
                                                (*itr)->GetMotionMaster()->MoveFollow(player, 2.0f, urand(1, 4));
                                                break;
                                            }
                                            default:
                                                break;
                                        }
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_FOLLOW_OWNER);
                        break;
                    }
                    case EVENT_START_TALK:
                    {
                        Talk(3);
                        TalkWithDelay(12000, 4);
                        TalkWithDelay(18000, 5);
                        // Cleanup squadron movements
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(player, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                            player->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                                    {
                                        (*itr)->GetMotionMaster()->Clear();
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_INIT_MEDIC, 6000);
                        events.ScheduleEvent(EVENT_INIT_DEMOLITIONIST, 20000);
                        events.CancelEvent(EVENT_START_TALK);
                        break;
                    }
                    case EVENT_INIT_MEDIC:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(player, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                            player->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && ((*itr)->GetEntry() == NPC_MEDIC || (*itr)->GetEntry() == NPC_NEWT))
                                    {
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_GATE_2, -3974.88f, -3989.00f, 175.41f);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(1500, 0);
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_INIT_MEDIC);
                        break;
                    }
                    case EVENT_INIT_DEMOLITIONIST:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(player, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                            player->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                                    {
                                        switch ((*itr)->GetEntry())
                                        {
                                            case NPC_DEMOLTIONIST:
                                            case NPC_TICKER:
                                            {
                                                (*itr)->ToCreature()->SetReactState(REACT_PASSIVE);
                                                (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                                                (*itr)->GetMotionMaster()->MovePoint(POINT_GATE_2, -3974.88f, -3989.00f, 175.41f);
                                                (*itr)->ToCreature()->AI()->TalkWithDelay(500, 0);
                                                (*itr)->ToCreature()->AI()->TalkWithDelay(20000, 1);
                                                (*itr)->ToCreature()->AI()->TalkWithDelay(40000, 2);
                                                (*itr)->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
                                                events.ScheduleEvent(EVENT_DEMOLITIONIST_DONE, 40000);
                                                events.ScheduleEvent(EVENT_SUMMON_ASSAULTERS, 2000);
                                                break;
                                            }
                                            case NPC_MEDIC:
                                            case NPC_GRIT:
                                            {
                                                (*itr)->ToCreature()->SetReactState(REACT_DEFENSIVE);
                                                (*itr)->GetMotionMaster()->MovementExpired(false);
                                                (*itr)->GetMotionMaster()->MovePoint(POINT_COVER_MEDIC, -3977.33f, -4010.12f, 174.52f);
                                                break;
                                            }
                                            case NPC_MARINE:
                                            case NPC_NEWT:
                                            {
                                                (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                                                (*itr)->GetMotionMaster()->MovementExpired(false);
                                                (*itr)->GetMotionMaster()->MovePoint(POINT_COVER_MARINE, -3950.72f, -4000.15f, 172.96f);
                                                break;
                                            }
                                            case NPC_SNIPER:
                                            case NPC_VOLT:
                                            {
                                                (*itr)->ToCreature()->SetReactState(REACT_PASSIVE);
                                                (*itr)->GetMotionMaster()->MovementExpired(false);
                                                (*itr)->GetMotionMaster()->MovePoint(POINT_COVER_SNIPER, -3968.16f, -4026.30f, 173.40f);
                                                break;
                                            }
                                            case NPC_LIEUTENANT:
                                            case NPC_PATCH:
                                            {
                                                (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                                                (*itr)->GetMotionMaster()->MovementExpired(false);
                                                (*itr)->GetMotionMaster()->MovePoint(POINT_COVER_LIEUTENANT, -3964.90f, -4008.86f, 173.08f);
                                                break;
                                            }
                                            default:
                                                break;
                                        }
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_INIT_MEDIC);
                        break;
                    }
                    case EVENT_SUMMON_ASSAULTERS:
                    {
                        me->SummonCreature(NPC_GUARDSMAN, -3917.54f, -4014.48f, 169.57f, 3.02f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        me->SummonCreature(NPC_GUARDSMAN, -3915.76f, -4029.01f, 167.34f, 2.85f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        me->SummonCreature(NPC_GUARDSMAN, -3923.07f, -4048.07f, 169.55f, 2.30f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.RescheduleEvent(EVENT_SUMMON_ASSAULTERS, urand(8000, 10000));
                        break;
                    }
                    case EVENT_DEMOLITIONIST_DONE:
                    {
                        if (Unit* player = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(player, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                            player->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && ((*itr)->GetEntry() == NPC_DEMOLTIONIST || (*itr)->GetEntry() == NPC_TICKER))
                                    {
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                        (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                                        if (player->GetTypeId() == TYPEID_PLAYER)
                                            player->ToPlayer()->KilledMonsterCredit(47539);
                                        (*itr)->HandleEmoteCommand(EMOTE_STATE_STAND);
                                        (*itr)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                                    }
                                }
                            }
                            me->GetMotionMaster()->MoveFollow(player, 1.0f, urand(1, 4));
                            events.ScheduleEvent(EVENT_FOLLOW_OWNER, 1000);
                        }
                        events.CancelEvent(EVENT_SUMMON_ASSAULTERS);
                        events.CancelEvent(EVENT_DEMOLITIONIST_DONE);
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
                case POINT_GATE:
                {
                    events.ScheduleEvent(EVENT_START_TALK, 1000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_mathias_squadronAI(creature);
    }
};

class npc_th_wyrms_bend_fighter : public CreatureScript
{
public:
    npc_th_wyrms_bend_fighter() : CreatureScript("npc_th_wyrms_bend_fighter")
    {
    }

    struct npc_th_wyrms_bend_fighterAI : public ScriptedAI
    {
        npc_th_wyrms_bend_fighterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1,

            // Spells
            EVENT_RAPID_SHOT,
            EVENT_FROSTBOLT,
            EVENT_FROST_NOVA,
            EVENT_ICE_LANCE,
            EVENT_BLIZZARD,
            EVENT_LAVA_BURST,
            EVENT_HEMORRHAGE,
            EVENT_BACKSTAB
        };

        enum spellId
        {
            SPELL_RAPID_SHOT    = 88679,
            SPELL_FROST_ARMOR   = 79865,
            SPELL_FROSTBOLT     = 79858,
            SPELL_FROST_NOVA    = 79850,
            SPELL_ICE_LANCE     = 79859,
            SPELL_BLIZZARD      = 79860,
            SPELL_EARTH_SHIELD  = 79928,
            SPELL_LAVA_BURST    = 79886,
            SPELL_BACKSTAB      = 79862,
            SPELL_HEMORRHAGE    = 79863,
            SPELL_SHADOWSTEP    = 79864
        };

        enum npcId
        {
            NPC_SENTINEL    = 47406,
            NPC_CRYOMAGUS   = 47409,
            NPC_EARTHBINDER = 47407,
            NPC_STALKER     = 47401
        };

        void IsSummonedBy(Unit* owner)
        {
            AttackStart(owner);
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            switch (me->GetEntry())
            {
                case NPC_SENTINEL:
                {
                    events.ScheduleEvent(EVENT_RAPID_SHOT, urand(6000, 18000));
                    break;
                }
                case NPC_CRYOMAGUS:
                {
                    if (!me->HasAura(SPELL_FROST_ARMOR))
                        DoCast(SPELL_FROST_ARMOR);

                    events.ScheduleEvent(EVENT_FROSTBOLT, urand(3000, 6500));
                    events.ScheduleEvent(EVENT_ICE_LANCE, urand(5000, 7000));
                    events.ScheduleEvent(EVENT_BLIZZARD, urand(15000, 20000));
                    events.ScheduleEvent(EVENT_FROST_NOVA, 8000);
                    break;
                }
                case NPC_EARTHBINDER:
                {
                    if (!me->HasAura(SPELL_FROST_ARMOR))
                        DoCast(SPELL_FROST_ARMOR);

                    events.ScheduleEvent(EVENT_LAVA_BURST, urand(3000, 4000));
                    break;
                }
                case NPC_STALKER:
                {
                    if (Unit* victim = me->getVictim())
                        DoCast(victim, SPELL_SHADOWSTEP);
                    events.ScheduleEvent(EVENT_HEMORRHAGE, urand(2000, 5000));
                    events.ScheduleEvent(EVENT_BACKSTAB, urand(5000, 7500));
                    break;
                }
                default:
                    break;
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet() && !attacker->ToTempSummon())
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
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(6.0f))
                        {
                            AttackStart(victim);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_ENEMY, 2000);
                        break;
                    }
                    case EVENT_FROSTBOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_FROSTBOLT);
                        events.RescheduleEvent(EVENT_FROSTBOLT, urand(5000, 8000));
                        break;
                    }
                    case EVENT_FROST_NOVA:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                        {
                            if (victim->IsWithinCombatRange(me, 5.0f))
                                DoCast(SPELL_FROST_NOVA);
                        }
                        events.RescheduleEvent(EVENT_FROST_NOVA, urand(4000, 10000));
                        break;
                    }
                    case EVENT_LAVA_BURST:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_LAVA_BURST);
                        events.RescheduleEvent(EVENT_LAVA_BURST, urand(3500, 4500));
                        break;
                    }
                    case EVENT_BLIZZARD:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BLIZZARD);
                        events.RescheduleEvent(EVENT_BLIZZARD, urand(5000, 8500));
                        break;
                    }
                    case EVENT_RAPID_SHOT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_RAPID_SHOT);
                        events.RescheduleEvent(EVENT_RAPID_SHOT, urand(10000, 15500));
                        break;
                    }
                    case EVENT_ICE_LANCE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_ICE_LANCE);
                        events.RescheduleEvent(EVENT_ICE_LANCE, urand(2500, 5000));
                        break;
                    }
                    case EVENT_BACKSTAB:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BACKSTAB);
                        events.RescheduleEvent(EVENT_BACKSTAB, urand(2500, 5000));
                        break;
                    }
                    case EVENT_HEMORRHAGE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HEMORRHAGE);
                        events.RescheduleEvent(EVENT_HEMORRHAGE, urand(4000, 6500));
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
        return new npc_th_wyrms_bend_fighterAI(creature);
    }
};

class areatrigger_th_grim_batol : public AreaTriggerScript
{
public:
    areatrigger_th_grim_batol() : AreaTriggerScript("at_th_grim_batol")
    {
    }

    enum questId
    {
        QUEST_PRESSING_FORWARD_A    = 28109,
        QUEST_PRESSING_FORWARD_H    = 28093
    };

    enum npcId
    {
        // Alliance
        NPC_LIEUTENANT      = 47611,
        NPC_DEMOLTIONIST    = 47612,
        NPC_MEDIC           = 47613,
        NPC_SNIPER          = 47614,
        NPC_MARINE          = 47615,
        NPC_CALEN           = 47605,

        // Horde
        NPC_VOLT            = 47377,
        NPC_TICKER          = 47375,
        NPC_PATCH           = 47374,
        NPC_NEWT            = 47376,
        NPC_GRIT            = 47378
    };

    enum creditId
    {
        QUEST_CREDIT_PRESSING_FORWARD   = 47566
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->isAlive() && (player->GetQuestStatus(QUEST_PRESSING_FORWARD_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD_H) == QUEST_STATUS_INCOMPLETE))
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 300.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(300.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_MEDIC:
                            case NPC_LIEUTENANT:
                            case NPC_SNIPER:
                            case NPC_MARINE:
                            case NPC_DEMOLTIONIST:
                            case NPC_PATCH:
                            case NPC_NEWT:
                            case NPC_TICKER:
                            case NPC_GRIT:
                            case NPC_VOLT:
                            {
                                (*itr)->GetMotionMaster()->Clear();
                                (*itr)->GetMotionMaster()->MovementExpired(false);
                                (*itr)->GetMotionMaster()->MovePoint(10, -4122.99f, -3562.01f, 226.84f);
                                (*itr)->ToCreature()->DespawnOrUnsummon(3500);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
            player->KilledMonsterCredit(QUEST_CREDIT_PRESSING_FORWARD);
            if (Creature* calen = player->FindNearestCreature(NPC_CALEN, 100.0f, true))
                calen->AI()->Talk(0, player->GetGUID());
        }
        return false;
    }
};

class npc_th_lirastrasza_dq_event : public CreatureScript
{
public:
    npc_th_lirastrasza_dq_event() : CreatureScript("npc_th_lirastrasza_dq_event")
    {
    }

    enum questId
    {
        QUEST_ENTER_THE_DRAGON_QUEEN    = 28712
    };

    enum npcId
    {
        NPC_CAMERA_1    = 51041
    };

    enum spellId
    {
        SPELL_FADE_TO_BLACK         = 94394
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_ENTER_THE_DRAGON_QUEEN)
        {
            player->SetPhaseMask(2, true);
            player->AddAura(60191, player);
            // Cleanup before restart!
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 500.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(500.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                {
                    if ((*itr) == creature)
                        continue;

                    (*itr)->ToCreature()->DespawnOrUnsummon(1);
                }
            }

            player->CastSpell(player, SPELL_FADE_TO_BLACK, true);
            player->SummonCreature(NPC_CAMERA_1, -2699.79f, -3260.87f, 209.62f, 2.04f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }
        return true;
    }
};

class npc_th_dq_first_camera : public CreatureScript
{
public:
    npc_th_dq_first_camera() : CreatureScript("npc_th_dq_first_camera")
    {
    }

    struct npc_th_dq_first_cameraAI : public ScriptedAI
    {
        npc_th_dq_first_cameraAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_FOCUS_ALEXSTRASZA,
            EVENT_MOVE_TO_FIRST,
            EVENT_MOVE_TO_SECOND,
            EVENT_MOVE_TO_THIRD,
            EVENT_MOVE_TO_FOURTH,
            EVENT_FADE_TO_BLACK,
            EVENT_FINISH_ALL
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_SUMMON_ALEXSTRASZA    = 95195,
            SPELL_SUMMON_CALEN          = 95196,
            SPELL_SUMMON_MIRROR         = 95198,
            SPELL_FADE_TO_BLACK         = 94394
        };

        enum pointId
        {
            POINT_FIRST     = 1,
            POINT_SECOND,
            POINT_THIRD,
            POINT_FOURTH
        };

        enum npcId
        {
            NPC_ALEXSTRASZA     = 51354,
            NPC_DEATHWING       = 51355
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

        void Reset()
        {
            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
            {
                invoker->AddAura(60191, me);
                invoker->RemoveAurasDueToSpell(60922);
            }
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FIRST:
                {
                    me->SetSpeed(MOVE_WALK, 0.15f, true);
                    me->SetSpeed(MOVE_RUN, 0.15f, true);
                    me->SetSpeed(MOVE_FLIGHT, 0.15f, true);
                    events.ScheduleEvent(EVENT_MOVE_TO_SECOND, 18000);
                    break;
                }
                case POINT_SECOND:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_THIRD, 1000);
                    break;
                }
                case POINT_THIRD:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_FOURTH, 1);
                    break;
                }
                case POINT_FOURTH:
                {
                    events.ScheduleEvent(EVENT_FADE_TO_BLACK, 25000);
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
                                invoker->CastSpell(invoker, SPELL_SUMMON_ALEXSTRASZA, true);
                                invoker->CastSpell(invoker, SPELL_SUMMON_CALEN, true);
                                invoker->CastSpell(invoker, SPELL_SUMMON_MIRROR, true);
                                invoker->EnterVehicle(me, 1);
                            }
                        }
                        me->SetSpeed(MOVE_WALK, 0.25f, true);
                        me->SetSpeed(MOVE_RUN, 0.25f, true);
                        me->SetSpeed(MOVE_FLIGHT, 0.25f, true);
                        events.ScheduleEvent(EVENT_FOCUS_ALEXSTRASZA, 500);
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        break;
                    }
                    case EVENT_FOCUS_ALEXSTRASZA:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA, 500.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_FIRST, 11500);
                        events.CancelEvent(EVENT_FOCUS_ALEXSTRASZA);
                        break;
                    }
                    case EVENT_MOVE_TO_FIRST:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FIRST, -2718.25f, -3221.28f, 180.65f);
                        events.CancelEvent(EVENT_MOVE_TO_FIRST);
                        break;
                    }
                    case EVENT_MOVE_TO_SECOND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_SECOND, -2714.98f, -3211.65f, 183.67f);
                        events.CancelEvent(EVENT_MOVE_TO_SECOND);
                        break;
                    }
                    case EVENT_MOVE_TO_THIRD:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_THIRD, -2673.52f, -3204.07f, 196.96f);
                        events.CancelEvent(EVENT_MOVE_TO_THIRD);
                        break;
                    }
                    case EVENT_MOVE_TO_FOURTH:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_DEATHWING, 800.0f);
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
                                }
                            }
                        }

                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FOURTH, -2718.98f, -3244.38f, 185.04f);
                        events.CancelEvent(EVENT_MOVE_TO_FOURTH);
                        break;
                    }
                    case EVENT_FADE_TO_BLACK:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->CastSpell(invoker, SPELL_FADE_TO_BLACK, true);
                        events.ScheduleEvent(EVENT_FINISH_ALL, 2000);
                        events.CancelEvent(EVENT_FADE_TO_BLACK);
                        break;
                    }
                    case EVENT_FINISH_ALL:
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                            vehicle->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        events.CancelEvent(EVENT_FINISH_ALL);
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
        return new npc_th_dq_first_cameraAI(creature);
    }
};

class npc_th_alexstrasza_dq_first_event : public CreatureScript
{
public:
    npc_th_alexstrasza_dq_first_event() : CreatureScript("npc_th_alexstrasza_dq_first_event")
    {
    }

    struct npc_th_alexstrasza_dq_first_eventAI : public ScriptedAI
    {
        npc_th_alexstrasza_dq_first_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_LAND  = 1,
            EVENT_LAND,
            EVENT_TRANSFORM,
            EVENT_FIRST_MOVE,
            EVENT_START_TO_TALK,
            EVENT_ADJUST_FACING_1,
            EVENT_MOVE_TO_CENTER,
            EVENT_CAST_LIFE,
            EVENT_SUMMON_DEATHWING,
            EVENT_TAKEOFF,
            EVENT_MOVE_AWAY
        };

        enum spellId
        {
            SPELL_ALEXSTRASZA_HUMAN     = 95171,
            SPELL_ALEXSTRASZA_DRAKE     = 92147,
            SPELL_LIFE_CALL             = 92249,
            SPELL_SUMMON_DEATHWING      = 95273
        };

        enum pointId
        {
            POINT_LAND      = 1,
            POINT_LANDED,
            POINT_FIRST,
            POINT_CENTER,
            POINT_TAKEOFF,
            POINT_AWAY
        };

        enum npcId
        {
            NPC_CALEN   = 51356,
            NPC_CAMERA  = 51041,
            NPC_MIRROR  = 51357
        };

        enum actionId
        {
            ACTION_TAKEOFF  = 1
        };

        enum soundId
        {
            PLAY_MUSIC_AFTERMATH    = 22146
        };

        void InitializeAI()
        {
            me->AddAura(60191, me);
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->SetHover(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetWalk(false);
            events.ScheduleEvent(EVENT_MOVE_TO_LAND, 1000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TAKEOFF:
                {
                    me->RemoveAurasDueToSpell(SPELL_ALEXSTRASZA_HUMAN);
                    me->RemoveAurasDueToSpell(SPELL_ALEXSTRASZA_DRAKE);
                    events.ScheduleEvent(EVENT_TAKEOFF, 3000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LAND:
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                case POINT_LANDED:
                    events.ScheduleEvent(EVENT_TRANSFORM, 4000);
                    break;
                case POINT_FIRST:
                    events.ScheduleEvent(EVENT_START_TO_TALK, 4000);
                    break;
                case POINT_CENTER:
                    events.ScheduleEvent(EVENT_CAST_LIFE, 1000);
                    break;
                case POINT_TAKEOFF:
                    events.ScheduleEvent(EVENT_MOVE_AWAY, 1000);
                    break;
                case POINT_AWAY:
                    me->DespawnOrUnsummon(1);
                    break;
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
                    case EVENT_MOVE_TO_LAND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_LAND, -2744.88f, -3177.65f, 200.81f);
                        events.CancelEvent(EVENT_MOVE_TO_LAND);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        x = -2737.20f;
                        y = -3200.02f;
                        z = 177.47f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LANDED, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_TRANSFORM:
                    {
                        DoCast(SPELL_ALEXSTRASZA_HUMAN);
                        me->SetWalk(true);
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->Relocate(-2737.20f, -3200.02f, 178.47f, me->GetOrientation());
                        events.ScheduleEvent(EVENT_FIRST_MOVE, 5000);
                        events.CancelEvent(EVENT_TRANSFORM);
                        break;
                    }
                    case EVENT_FIRST_MOVE:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FIRST, -2725.84f, -3210.82f, 178.86f);
                        events.CancelEvent(EVENT_FIRST_MOVE);
                        break;
                    }
                    case EVENT_START_TO_TALK:
                    {
                        Talk(0);

                        // Init Calen
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CALEN, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->ToCreature()->AI()->DoAction(1);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(9000, 0);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(26000, 1);
                                }
                            }
                        }

                        TalkWithDelay(15000, 1);
                        events.ScheduleEvent(EVENT_ADJUST_FACING_1, 14500);
                        events.ScheduleEvent(EVENT_MOVE_TO_CENTER, 28500);
                        events.CancelEvent(EVENT_START_TO_TALK);
                        break;
                    }
                    case EVENT_ADJUST_FACING_1:
                    {
                        me->SetFacingTo(6.13f);
                        events.CancelEvent(EVENT_ADJUST_FACING_1);
                        break;
                    }
                    case EVENT_MOVE_TO_CENTER:
                    {
                        // Adjust Mirror
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_MIRROR, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(1);

                                if (invoker->GetTypeId() == TYPEID_PLAYER)
                                    invoker->PlayDirectSound(PLAY_MUSIC_AFTERMATH, invoker->ToPlayer());
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_CENTER, -2733.33f, -3218.80f, 178.89f);
                        events.CancelEvent(EVENT_MOVE_TO_CENTER);
                        break;
                    }
                    case EVENT_CAST_LIFE:
                    {
                        DoCast(SPELL_LIFE_CALL);
                        events.ScheduleEvent(EVENT_SUMMON_DEATHWING, 24000);
                        events.CancelEvent(EVENT_CAST_LIFE);
                        break;
                    }
                    case EVENT_SUMMON_DEATHWING:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->CastSpell(invoker, SPELL_SUMMON_DEATHWING, true);
                        events.CancelEvent(EVENT_SUMMON_DEATHWING);
                        break;
                    }
                    case EVENT_TAKEOFF:
                    {
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);

                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 21.5f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        events.CancelEvent(EVENT_TAKEOFF);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->SetSpeed(MOVE_WALK, 2.0f, true);
                        me->SetSpeed(MOVE_RUN, 2.0f, true);
                        me->SetSpeed(MOVE_FLIGHT, 2.0f, true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -2833.29f, -3078.76f, 313.55f);
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_alexstrasza_dq_first_eventAI(creature);
    }
};

class npc_th_calen_dq_first_event : public CreatureScript
{
public:
    npc_th_calen_dq_first_event() : CreatureScript("npc_th_calen_dq_first_event")
    {
    }

    struct npc_th_calen_dq_first_eventAI : public ScriptedAI
    {
        npc_th_calen_dq_first_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_LAND  = 1,
            EVENT_LAND,
            EVENT_TRANSFORM,
            EVENT_FIRST_MOVE
        };

        enum spellId
        {
            SPELL_CALEN_HUMAN   = 95241
        };

        enum pointId
        {
            POINT_LAND      = 1,
            POINT_LANDED,
            POINT_FIRST
        };

        enum actionId
        {
            ACTION_FIRST_MOVE   = 1
        };

        void InitializeAI()
        {
            me->AddAura(60191, me);
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->SetHover(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetWalk(false);
            events.ScheduleEvent(EVENT_MOVE_TO_LAND, 12000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FIRST_MOVE:
                {
                    events.ScheduleEvent(EVENT_FIRST_MOVE, 1);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LAND:
                {
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                }
                case POINT_LANDED:
                {
                    events.ScheduleEvent(EVENT_TRANSFORM, 4000);
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
                    case EVENT_MOVE_TO_LAND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_LAND, -2705.55f, -3202.80f, 200.68f);
                        events.CancelEvent(EVENT_MOVE_TO_LAND);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        x = -2714.67f;
                        y = -3208.14f;
                        z = 177.86f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LANDED, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_TRANSFORM:
                    {
                        DoCast(SPELL_CALEN_HUMAN);
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->Relocate(-2714.67f, -3208.14f, 177.86f, me->GetOrientation());
                        events.CancelEvent(EVENT_TRANSFORM);
                        break;
                    }
                    case EVENT_FIRST_MOVE:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FIRST, -2720.54f, -3210.10f, 178.86f);
                        events.CancelEvent(EVENT_FIRST_MOVE);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_calen_dq_first_eventAI(creature);
    }
};

class npc_th_dq_first_mirror : public CreatureScript
{
public:
    npc_th_dq_first_mirror() : CreatureScript("npc_th_dq_first_mirror")
    {
    }

    struct npc_th_dq_first_mirrorAI : public ScriptedAI
    {
        npc_th_dq_first_mirrorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_FIRST_MOVE        = 1,
            EVENT_ADJUST_FACING_1,
            EVENT_ADJUST_FACING_2
        };

        enum actionId
        {
            ACTION_ROTATE   = 1
        };

        enum spellId
        {
            SPELL_MIRROR_IMAGE_AURA     = 94551
        };

        enum pointId
        {
            POINT_FIRST     = 1
        };

        enum npcId
        {
            NPC_ALEXSTRASZA = 51354
        };

        void IsSummonedBy(Unit* owner)
        {
            me->AddAura(60191, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetWalk(true);
            owner->CastSpell(me, SPELL_MIRROR_IMAGE_AURA, true);
            events.ScheduleEvent(EVENT_FIRST_MOVE, 1);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FIRST:
                    events.ScheduleEvent(EVENT_ADJUST_FACING_1, 1);
                    break;
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ROTATE:
                {
                    events.ScheduleEvent(EVENT_ADJUST_FACING_2, 4500);
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
                    case EVENT_FIRST_MOVE:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_FIRST, -2720.82f, -3216.68f, 178.87f);
                        events.CancelEvent(EVENT_FIRST_MOVE);
                        break;
                    }
                    case EVENT_ADJUST_FACING_1:
                    {
                        me->SetFacingTo(2.17f);
                        events.CancelEvent(EVENT_ADJUST_FACING_1);
                        break;
                    }
                    case EVENT_ADJUST_FACING_2:
                    {
                        me->SetFacingTo(3.28f);
                        events.CancelEvent(EVENT_ADJUST_FACING_2);
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
        return new npc_th_dq_first_mirrorAI(creature);
    }
};

class npc_th_deathwing_dq_event : public CreatureScript
{
public:
    npc_th_deathwing_dq_event() : CreatureScript("npc_th_deathwing_dq_event")
    {
    }

    struct npc_th_deathwing_dq_eventAI : public ScriptedAI
    {
        npc_th_deathwing_dq_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_LAND          = 1,
            EVENT_LAND,
            EVENT_INFORM_ALEXSTRASZA,
            EVENT_TAKEOFF,
            EVENT_MOVE_AWAY
        };

        enum spellId
        {
            SPELL_DEATHWING_FIRE    = 95292,
            SPELL_DEATHWING_BREATH  = 95470,
            SPELL_DEATHWING_FWALL   = 92304,
            SPELL_DEATHWING_APPEARS = 92313,
            SPELL_DEATHWING_SMOKE   = 95843
        };

        enum pointId
        {
            POINT_LAND      = 1,
            POINT_LANDED,
            POINT_TAKEOFF,
            POINT_AWAY
        };

        enum npcId
        {
            NPC_ALEXSTRASZA     = 51354,
            NPC_CAMERA          = 51041
        };

        void InitializeAI()
        {
            me->AddAura(60191, me);
            me->CastSpell(me, SPELL_DEATHWING_APPEARS, true);
            me->CastSpell(me, SPELL_DEATHWING_SMOKE, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetWalk(false);
            events.ScheduleEvent(EVENT_MOVE_TO_LAND, 1000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LAND:
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                case POINT_LANDED:
                    DoCast(me, SPELL_DEATHWING_FWALL, true);
                    break;
                case POINT_TAKEOFF:
                    events.ScheduleEvent(EVENT_MOVE_AWAY, 2000);
                    break;
                case POINT_AWAY:
                    me->DespawnOrUnsummon(1);
                    break;
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
                    case EVENT_MOVE_TO_LAND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_LAND, -2752.69f, -3229.50f, 188.03f);
                        events.CancelEvent(EVENT_MOVE_TO_LAND);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        x = -2750.11f;
                        y = -3228.11f;
                        z = 178.88f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LANDED, moveLand);
                        Talk(0);
                        TalkWithDelay(18000, 1);
                        TalkWithDelay(30000, 2);
                        TalkWithDelay(38000, 3);
                        TalkWithDelay(47000, 4);
                        TalkWithDelay(66000, 5);
                        events.ScheduleEvent(EVENT_TAKEOFF, 71000);
                        events.ScheduleEvent(EVENT_INFORM_ALEXSTRASZA, 11000);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_INFORM_ALEXSTRASZA:
                    {
                        // Talk Alexstrasza
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->ToCreature()->AI()->Talk(2);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(47000, 3);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_INFORM_ALEXSTRASZA);
                        break;
                    }
                    case EVENT_TAKEOFF:
                    {
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 20.5f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        me->RemoveAurasDueToSpell(SPELL_DEATHWING_FWALL);
                        // Move Camera Final
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CAMERA, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                invoker->CastWithDelay(1000, invoker, 60922, true);
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->SetSpeed(MOVE_WALK, 1.0f, true);
                                    (*iter)->SetSpeed(MOVE_RUN, 1.0f, true);
                                    (*iter)->SetSpeed(MOVE_FLIGHT, 1.0f, true);
                                    (*iter)->GetMotionMaster()->MovementExpired(false);
                                    (*iter)->GetMotionMaster()->MovePoint(50, -2706.24f, -3260.33f, 195.64f);
                                }
                            }
                        }
                        DoCast(SPELL_DEATHWING_BREATH);
                        events.CancelEvent(EVENT_TAKEOFF);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->SetSpeed(MOVE_WALK, 2.0f, true);
                        me->SetSpeed(MOVE_RUN, 2.0f, true);
                        me->SetSpeed(MOVE_FLIGHT, 2.0f, true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -2833.29f, -3078.76f, 313.55f);

                        // Takeoff Alexstrasza
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_deathwing_dq_eventAI(creature);
    }
};

class npc_th_vermillion_summoner : public CreatureScript
{
public:
    npc_th_vermillion_summoner() : CreatureScript("npc_th_vermillion_summoner")
    {
    }

    enum questId
    {
        QUEST_BATTLE_OF_LIFE_AND_DEATH  = 28758
    };

    enum spellId
    {
        SPELL_SUMMON_VERMILLION     = 92932
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_BATTLE_OF_LIFE_AND_DEATH) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, SPELL_SUMMON_VERMILLION, true);
            return true;
        }
        return true;
    }
};

class npc_th_vermillion_escort : public CreatureScript
{
public:
    npc_th_vermillion_escort() : CreatureScript("npc_th_vermillion_escort")
    {
    }

    enum actionId
    {
        ACTION_WP_START = 1
    };

    enum eventId
    {
        EVENT_CHECK_QUEST_COMPLETE  = 1,
        EVENT_TELEPORT_TO_CAMERA,
        EVENT_CHECK_AREA,
        EVENT_KILL_INVOKER
    };

    enum questId
    {
        QUEST_BATTLE_OF_LIFE_AND_DEATH  = 28758
    };

    enum npcId
    {
        NPC_BATTLE_VEHICLE_CUTSCENE     = 51148
    };

    enum spellId
    {
        SPELL_FADE_TO_BLACK     = 94394,
        SPELL_SUMMON_CAMERA     = 94295,
        SPELL_TELEPORT_SCENE    = 94301,
        SPELL_ALEXSTRASZA_DW    = 94344,
        SPELL_SUMMON_CALEN      = 94327,
        SPELL_ALEXSTRASZA_VB    = 94362
    };

    struct npc_th_vermillion_escortAI : public npc_escortAI
    {
        npc_th_vermillion_escortAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            wpInProgress = false;
            warned = false;
            me->SetCanFly(true);
            me->SetHover(true);
            me->SetDisableGravity(true);
            events.ScheduleEvent(EVENT_CHECK_QUEST_COMPLETE, 10000);
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
                case 3:
                {
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        Talk(0, invoker->GetGUID());
                    break;
                }
                case 4:
                {
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        Talk(1, invoker->GetGUID());
                    break;
                }
                case 5:
                {
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        Talk(2, invoker->GetGUID());
                    break;
                }
                case 7:
                {
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        Talk(3, invoker->GetGUID());
                    break;
                }
                case 9:
                {
                    events.ScheduleEvent(EVENT_CHECK_AREA, 2000);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_QUEST_COMPLETE:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                            {
                                if (invoker->ToPlayer()->GetQuestStatus(QUEST_BATTLE_OF_LIFE_AND_DEATH) == QUEST_STATUS_COMPLETE)
                                {
                                    events.CancelEvent(EVENT_CHECK_QUEST_COMPLETE);
                                    invoker->CastSpell(invoker, SPELL_FADE_TO_BLACK, true);
                                    events.ScheduleEvent(EVENT_TELEPORT_TO_CAMERA, 2500);
                                    break;
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_QUEST_COMPLETE, 2000);
                        break;
                    }
                    case EVENT_TELEPORT_TO_CAMERA:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->ExitVehicle();
                            invoker->CastSpell(invoker, SPELL_SUMMON_CAMERA, true);
                            invoker->CastSpell(invoker, SPELL_TELEPORT_SCENE, true);
                            invoker->CastSpell(invoker, SPELL_SUMMON_CALEN, true);
                            invoker->CastSpell(invoker, SPELL_ALEXSTRASZA_VB, true);
                            invoker->CastSpell(invoker, SPELL_ALEXSTRASZA_DW, true);
                            invoker->SummonCreature(NPC_BATTLE_VEHICLE_CUTSCENE, -3935.64f, -3467.62f, 669.86f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            me->DespawnOrUnsummon(5000);
                        }
                        events.CancelEvent(EVENT_TELEPORT_TO_CAMERA);
                        break;
                    }
                    case EVENT_CHECK_AREA:
                    {
                        Creature* alexstrasza = me->FindNearestCreature(49818, 250.0f);
                        if (!alexstrasza)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if (warned == true)
                                {
                                    invoker->Kill(invoker, true);
                                    me->DespawnOrUnsummon(1000);
                                }
                                else
                                {
                                    invoker->MonsterWhisper("You are leaving the battlefield, return back to Alexstrasza!", invoker->GetGUID(), true);
                                    warned = true;
                                }
                            }
                        }
                        else
                            warned = false;

                        events.RescheduleEvent(EVENT_CHECK_AREA, 10000);
                        break;
                    }
                    default:
                        break;
                }
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
                    me->SetSpeed(MOVE_FLIGHT, 3.4f, true);
                    me->SetSpeed(MOVE_RUN, 3.4f, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        bool wpInProgress;
        bool warned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_vermillion_escortAI(creature);
    }
};

class npc_th_battle_vehicle_event : public CreatureScript
{
public:
    npc_th_battle_vehicle_event() : CreatureScript("npc_th_battle_vehicle_event")
    {
    }

    enum actionId
    {
    };

    enum eventId
    {
        EVENT_ADJUST_ORIENTATION    = 1,
        EVENT_FALL_ON_GROUND
    };

    enum questId
    {
    };

    enum spellId
    {
    };

    enum pointId
    {
        POINT_GROUND    = 1
    };

    struct npc_th_battle_vehicle_eventAI : public ScriptedAI
    {
        npc_th_battle_vehicle_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            me->AddUnitState(UNIT_STATE_ROTATING);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            owner->AddAura(60191, me);
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_ADJUST_ORIENTATION, 2000);
            events.ScheduleEvent(EVENT_FALL_ON_GROUND, 4000);
        }

        void EnterEvadeMode()
        {
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
                        me->GetVehicleKit()->RelocatePassengers();
                        events.CancelEvent(EVENT_ADJUST_ORIENTATION);
                        break;
                    }
                    case EVENT_FALL_ON_GROUND:
                    {
                        if (Unit* alexstrasza = me->GetVehicleKit()->GetPassenger(3))
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                alexstrasza->ToCreature()->MonsterSay("Neltharion! Look at yourself. Misshapen. Twisted. You're coming apart.", 0, invoker->GetGUID());
                                if (invoker->GetTypeId() == TYPEID_PLAYER)
                                    invoker->PlayDirectSound(21049, invoker->ToPlayer());
                            }
                        }
                        me->GetMotionMaster()->MoveJump(-4247.83f, -3354.41f, 241.09f, 50.0f, 50.0f, POINT_GROUND);
                        me->DespawnOrUnsummon(10000);
                        events.CancelEvent(EVENT_FALL_ON_GROUND);
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
        return new npc_th_battle_vehicle_eventAI(creature);
    }
};

class npc_th_battle_camera_event : public CreatureScript
{
public:
    npc_th_battle_camera_event() : CreatureScript("npc_th_battle_camera_event")
    {
    }

    struct npc_th_battle_camera_eventAI : public ScriptedAI
    {
        npc_th_battle_camera_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER  = 1,
            EVENT_FOCUS_SKY,
            EVENT_MOVE_TO_FIRST
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552
        };

        enum pointId
        {
            POINT_FIRST     = 1,
            POINT_DOWNED
        };

        enum npcId
        {
            NPC_TARGET_SKY  = 51039
        };

        void DespawnAllSummons()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 800.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(800.0f, searcher);
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

        void IsSummonedBy(Unit* /*owner*/)
        {
            DespawnAllSummons();

            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
            {
                invoker->AddAura(60191, me);
                invoker->SummonCreature(NPC_TARGET_SKY, -3935.84f, -3429.41f, 669.86f, 3.25f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                invoker->AddAura(60191, me);
            }

            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FIRST:
                    break;
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
                                invoker->EnterVehicle(me, 1);
                        }
                        me->SetSpeed(MOVE_WALK, 0.25f, true);
                        me->SetSpeed(MOVE_RUN, 0.25f, true);
                        me->SetSpeed(MOVE_FLIGHT, 0.25f, true);
                        events.ScheduleEvent(EVENT_FOCUS_SKY, 500);
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        break;
                    }
                    case EVENT_FOCUS_SKY:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TARGET_SKY, 500.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    me->CastSpell((*iter), SPELL_CAMERA_CHANNELING, true);
                                    (*iter)->GetMotionMaster()->MoveJump(-4067.93f, -3457.03f, 289.28f, 15.0f, 15.0f, 1);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_FIRST, 3000);
                        events.CancelEvent(EVENT_FOCUS_SKY);
                        break;
                    }
                    case EVENT_MOVE_TO_FIRST:
                    {
                        me->GetMotionMaster()->MoveJump(-4141.29f, -3483.03f, 290.00f, 20.0f, 20.0f, POINT_DOWNED);
                        events.CancelEvent(EVENT_MOVE_TO_FIRST);
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
        return new npc_th_battle_camera_eventAI(creature);
    }
};

class npc_th_battle_calen_event : public CreatureScript
{
public:
    npc_th_battle_calen_event() : CreatureScript("npc_th_battle_calen_event")
    {
    }

    struct npc_th_battle_calen_eventAI : public ScriptedAI
    {
        npc_th_battle_calen_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum actionId
        {
            ACTION_FINALIZE     = 1
        };

        enum eventId
        {
            EVENT_MOVE_TO_TREE              = 1,
            EVENT_INFORM_CAMERA_FIRST,
            EVENT_TELEPORT_CAMERA_TARGET,
            EVENT_REFOCUS_TARGET,
            EVENT_MOVE_TO_ALEXSTRASZA,
            EVENT_LAND,
            EVENT_MOVE_TO_DOWNED,
            EVENT_ENABLE_ALEX_2,
            EVENT_TRANSFORM_DISTRACT
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING = 88552,
            SPELL_CALEN_HUMAN       = 92178,
            SPELL_DRAKE_DOUBLE      = 94350
        };

        enum pointId
        {
            POINT_TREE      = 1,
            POINT_ALEX,
            POINT_LAND,
            POINT_DOWNED,
            POINT_TAKEOFF   = 20
        };

        enum npcId
        {
            NPC_TARGET_SKY  = 51039,
            NPC_CAMERA      = 51038,
            NPC_DEATHWING   = 52869,
            NPC_ALEXSTRASZA = 51171
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FINALIZE:
                {
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetHover(true);
                    me->SetSpeed(MOVE_WALK, 2.0f);
                    me->SetSpeed(MOVE_RUN, 2.0f);
                    me->SetSpeed(MOVE_FLIGHT, 2.0f);
                    events.ScheduleEvent(EVENT_TRANSFORM_DISTRACT, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            events.ScheduleEvent(EVENT_MOVE_TO_TREE, 20000);
            owner->AddAura(60191, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            eventExecuted = false;
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TREE:
                {
                    Talk(0);
                    events.ScheduleEvent(EVENT_INFORM_CAMERA_FIRST, 1000);
                    break;
                }
                case POINT_ALEX:
                {
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                }
                case POINT_LAND:
                {
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->SetHover(false);
                    DoCast(me, SPELL_CALEN_HUMAN, true);
                    events.ScheduleEvent(EVENT_MOVE_TO_DOWNED, 1);
                    break;
                }
                case POINT_DOWNED:
                {
                    if (eventExecuted == true)
                        break;

                    TalkWithDelay(3000, 1);
                    me->SetStandState(UNIT_STAND_STATE_KNEEL);
                    events.ScheduleEvent(EVENT_ENABLE_ALEX_2, 8000);
                    break;
                }
                case POINT_TAKEOFF:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MoveRandom(30.0f);
                    me->DespawnOrUnsummon(18000);
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
                    case EVENT_MOVE_TO_TREE:
                    {
                        me->SetWalk(false);
                        me->SetSpeed(MOVE_WALK, 2.4f);
                        me->SetSpeed(MOVE_RUN, 2.4f);
                        me->SetSpeed(MOVE_FLIGHT, 2.4f);
                        me->GetMotionMaster()->MovePoint(POINT_TREE, -4081.93f, -3446.50f, 329.62f);
                        events.CancelEvent(EVENT_MOVE_TO_TREE);
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                                invoker->PlayDirectSound(22637, invoker->ToPlayer());
                        }
                        break;
                    }
                    case EVENT_INFORM_CAMERA_FIRST:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CAMERA, 500.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->CastStop();
                                    (*iter)->CastSpell(me, SPELL_CAMERA_CHANNELING, true);
                                    (*iter)->GetMotionMaster()->MoveJump(-4212.63f, -3405.74f, 230.57f, 10.0f, 10.0f, 10);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_TELEPORT_CAMERA_TARGET, 500);
                        events.CancelEvent(EVENT_INFORM_CAMERA_FIRST);
                        break;
                    }
                    case EVENT_TELEPORT_CAMERA_TARGET:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TARGET_SKY, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->GetMotionMaster()->MoveJump(-4215.49f, -3349.12f, 239.21f, 15.0f, 15.0f, 20);
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_ALEXSTRASZA, 1500);
                        events.ScheduleEvent(EVENT_REFOCUS_TARGET, 2500);
                        events.CancelEvent(EVENT_TELEPORT_CAMERA_TARGET);
                        break;
                    }
                    case EVENT_REFOCUS_TARGET:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CAMERA, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->CastStop();

                                    std::list<Creature*> creatures;
                                    GetCreatureListWithEntryInGrid(creatures, me, NPC_TARGET_SKY, 800.0f);
                                    if (creatures.empty())
                                        return;

                                    for (std::list<Creature*>::iterator sky = creatures.begin(); sky != creatures.end(); ++sky)
                                    {
                                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                            (*iter)->CastSpell(*sky, SPELL_CAMERA_CHANNELING, true);
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_REFOCUS_TARGET);
                        break;
                    }
                    case EVENT_MOVE_TO_ALEXSTRASZA:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_ALEX, -4250.96f, -3371.35f, 240.54f);
                        events.CancelEvent(EVENT_MOVE_TO_ALEXSTRASZA);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        x = me->GetPositionX();
                        y = me->GetPositionY();
                        z = 231.54f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->SummonCreature(NPC_DEATHWING, -4223.69f, -3174.06f, 496.24f, 4.69f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            invoker->CastSpell(invoker, SPELL_DRAKE_DOUBLE, true);
                        }
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_MOVE_TO_DOWNED:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_DOWNED, -4218.16f, -3387.54f, 230.69f);
                        events.CancelEvent(EVENT_MOVE_TO_DOWNED);
                        break;
                    }
                    case EVENT_ENABLE_ALEX_2:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(2);
                            }
                        }
                        events.CancelEvent(EVENT_ENABLE_ALEX_2);
                        break;
                    }
                    case EVENT_TRANSFORM_DISTRACT:
                    {
                        me->RemoveAurasDueToSpell(SPELL_CALEN_HUMAN);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);

                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 20.5f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_DEATHWING, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(2);
                            }
                        }
                        events.CancelEvent(EVENT_TRANSFORM_DISTRACT);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        protected:
            float x, y, z;
            bool eventExecuted;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_battle_calen_eventAI(creature);
    }
};

class npc_th_battle_deathwing_event : public CreatureScript
{
public:
    npc_th_battle_deathwing_event() : CreatureScript("npc_th_battle_deathwing_event")
    {
    }

    struct npc_th_battle_deathwing_eventAI : public ScriptedAI
    {
        npc_th_battle_deathwing_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum actionId
        {
            ACTION_REVIVE   = 1,
            ACTION_TAKEOFF
        };

        enum eventId
        {
            EVENT_MOVE_FALL             = 1,
            EVENT_MOVE_TO_ALEXSTRASZA,
            EVENT_LAND,
            EVENT_INFORM_CALEN,
            EVENT_MOVE_TO_DEATHWING,
            EVENT_CALL_DRAKE,
            EVENT_RIDE_DRAKE,
            EVENT_TAKEOFF,
            EVENT_FINALIZE,
            EVENT_SOUND_PLAYER
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_DEATHWING_AFLAME      = 94341,
            SPELL_DEATHWING_FWALL       = 92304,
            SPELL_FADE_TO_BLACK         = 94394
        };

        enum pointId
        {
            POINT_FALL          = 1,
            POINT_ALEX,
            POINT_LAND,
            POINT_DEATHWING,
            POINT_ALEX_FINAL,
            POINT_TAKEOFF       = 30,
            POINT_AWAY
        };

        enum npcId
        {
            NPC_TARGET_SKY      = 51039,
            NPC_CAMERA          = 51038,
            NPC_ALEXSTRASZA_VB  = 51186,
            NPC_CALEN           = 51159,
            NPC_DRAKE           = 51173,
            NPC_MIRROR          = 51172,
            NPC_ALEXSTRASZA     = 51171
        };

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() == TYPEID_PLAYER)
            {
                owner->AddAura(60191, me);
                DoCast(me, SPELL_DEATHWING_AFLAME, true);
                me->SetStandState(UNIT_STAND_STATE_DEAD);
                me->SetObjectScale(me->GetObjectScale() / 2);
                events.ScheduleEvent(EVENT_MOVE_FALL, 1);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                alreadyLanded = false;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_REVIVE:
                {
                    me->SetObjectScale(0.2f);
                    events.ScheduleEvent(EVENT_MOVE_TO_ALEXSTRASZA, 1);
                    break;
                }
                case ACTION_TAKEOFF:
                {
                    events.ScheduleEvent(EVENT_TAKEOFF, 1);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ALEX:
                {
                    events.ScheduleEvent(EVENT_LAND, 1000);
                    break;
                }
                case POINT_LAND:
                {
                    if (alreadyLanded == true)
                        break;

                    DoCast(me, SPELL_DEATHWING_FWALL);
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA_VB, 800.0f);
                    if (creatures.empty())
                        return;

                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                            {
                                (*iter)->ToCreature()->AI()->TalkWithDelay(1500, 3);
                                (*iter)->ToCreature()->AI()->TalkWithDelay(18500, 4);

                                std::list<Creature*> creatures;
                                GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZA, 800.0f);
                                if (creatures.empty())
                                    return;

                                for (std::list<Creature*>::iterator vb = creatures.begin(); vb != creatures.end(); ++vb)
                                {
                                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                    {
                                        if ((*vb)->ToTempSummon() && (*vb)->ToTempSummon()->GetSummoner() == invoker)
                                        {
                                            (*vb)->SetFacingTo(6.22f);
                                            (*vb)->SetStandState(UNIT_STAND_STATE_SIT);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    events.ScheduleEvent(EVENT_INFORM_CALEN, 4000);
                    alreadyLanded = true;
                    break;
                }
                case POINT_TAKEOFF:
                {
                    events.ScheduleEvent(EVENT_FINALIZE, 500);
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
                    case EVENT_MOVE_FALL:
                    {
                        me->SetWalk(false);
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->SetSpeed(MOVE_WALK, 3.5f, true);
                        me->SetSpeed(MOVE_RUN, 3.5f, true);
                        me->SetSpeed(MOVE_FLIGHT, 3.5f, true);
                        me->GetMotionMaster()->MovePoint(POINT_FALL, me->GetPositionX(), me->GetPositionY(), 188.42f, false);
                        events.CancelEvent(EVENT_MOVE_FALL);
                        break;
                    }
                    case EVENT_MOVE_TO_ALEXSTRASZA:
                    {
                        me->SetSpeed(MOVE_WALK, 3.1f, true);
                        me->SetSpeed(MOVE_RUN, 3.1f, true);
                        me->SetSpeed(MOVE_FLIGHT, 3.1f, true);
                        me->GetMotionMaster()->MovePoint(POINT_ALEX, -4220.83f, -3308.03f, 258.67f);
                        events.CancelEvent(EVENT_MOVE_TO_ALEXSTRASZA);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        x = -4220.77f;
                        y = -3310.34f;
                        z = 238.76f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_INFORM_CALEN:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CALEN, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->SetFacingTo(6.22f);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(500, 3);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(10000, 4);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_CALL_DRAKE, 3500);
                        events.CancelEvent(EVENT_INFORM_CALEN);
                        break;
                    }
                    case EVENT_MOVE_TO_DEATHWING:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CALEN, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->GetMotionMaster()->MovementExpired(false);
                                    (*iter)->GetMotionMaster()->MovePoint(6, -4220.84f, -3362.54f, 231.92f);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MOVE_TO_DEATHWING);
                        break;
                    }
                    case EVENT_CALL_DRAKE:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_DRAKE, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->SetWalk(true);
                                    (*iter)->SetHover(false);
                                    (*iter)->SetCanFly(false);
                                    (*iter)->SetDisableGravity(false);
                                    (*iter)->GetMotionMaster()->MovementExpired(false);
                                    (*iter)->GetMotionMaster()->MovePoint(POINT_ALEX_FINAL, -4208.62f, -3389.84f, 230.58f);
                                    events.ScheduleEvent(EVENT_RIDE_DRAKE, 2000);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_DEATHWING, 4000);
                        events.CancelEvent(EVENT_CALL_DRAKE);
                        break;
                    }
                    case EVENT_RIDE_DRAKE:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_DRAKE, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                        break;
                    }
                    case EVENT_TAKEOFF:
                    {
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 35.5f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        me->RemoveAurasDueToSpell(SPELL_DEATHWING_FWALL);
                        events.CancelEvent(EVENT_TAKEOFF);
                        break;
                    }
                    case EVENT_FINALIZE:
                    {
                        me->SetSpeed(MOVE_WALK, 1.4f, true);
                        me->SetSpeed(MOVE_RUN, 1.4f, true);
                        me->SetSpeed(MOVE_FLIGHT, 1.4f, true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -4218.48f, -3445.17f, 269.99f);
                        TalkWithDelay(3000, 0);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CAMERA, 800.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->GetMotionMaster()->MoveJump(-4221.25f, -3456.32f, 245.45f, 20.0f, 20.0f, 50);
                                    (*iter)->CastStop();
                                    (*iter)->CastSpell(me, SPELL_CAMERA_CHANNELING, true);
                                    invoker->CastWithDelay(10000, invoker, SPELL_FADE_TO_BLACK, true);
                                    (*iter)->DespawnOrUnsummon(14000);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_SOUND_PLAYER, 3000);
                        events.CancelEvent(EVENT_FINALIZE);
                        break;
                    }
                    case EVENT_SOUND_PLAYER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                                invoker->PlayDirectSound(20279, invoker->ToPlayer());
                        }
                        me->DespawnOrUnsummon(20000);
                        events.CancelEvent(EVENT_SOUND_PLAYER);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        float x, y, z;
        bool alreadyLanded;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_battle_deathwing_eventAI(creature);
    }
};

class npc_th_battle_alexstrasza_event : public CreatureScript
{
public:
    npc_th_battle_alexstrasza_event() : CreatureScript("npc_th_battle_alexstrasza_event")
    {
    }

    struct npc_th_battle_alexstrasza_eventAI : public ScriptedAI
    {
        npc_th_battle_alexstrasza_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum actionId
        {
            ACTION_START_TALK   = 1,
            ACTION_TALK_2
        };

        enum eventId
        {
            EVENT_REVIVE_DEATHWING  = 1
        };

        enum spellId
        {
        };

        enum pointId
        {
        };

        enum npcId
        {
            NPC_VOICE       = 51186,
            NPC_DEATHWING   = 52869,
            NPC_CALEN       = 51159,
            NPC_MIRROR      = 51172
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_TALK:
                {
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, me, NPC_VOICE, 50.0f);
                    if (creatures.empty())
                        return;

                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                (*iter)->ToCreature()->AI()->Talk(0);
                        }
                    }
                    break;
                }
                case ACTION_TALK_2:
                {
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, me, NPC_VOICE, 50.0f);
                    if (creatures.empty())
                        return;

                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                            {
                                (*iter)->ToCreature()->AI()->Talk(1);
                                (*iter)->ToCreature()->AI()->TalkWithDelay(11000, 2);
                                events.ScheduleEvent(EVENT_REVIVE_DEATHWING, 18000);
                            }
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() == TYPEID_PLAYER)
            {
                me->SetStandState(UNIT_STAND_STATE_DEAD);
                owner->AddAura(60191, me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_REVIVE_DEATHWING:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 1000.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(1000.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_DEATHWING:
                                    {
                                        (*itr)->SetWalk(false);
                                        (*itr)->SetStandState(UNIT_STAND_STATE_STAND);
                                        (*itr)->SetCanFly(true);
                                        (*itr)->SetDisableGravity(true);
                                        (*itr)->SetHover(true);
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                        break;
                                    }
                                    case NPC_CALEN:
                                    {
                                        (*itr)->SetFacingTo(1.27f);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(3000, 2);
                                        (*itr)->SetStandState(UNIT_STAND_STATE_STAND);
                                        break;
                                    }
                                    case NPC_MIRROR:
                                    {
                                        (*itr)->SetStandState(UNIT_STAND_STATE_STAND);
                                        (*itr)->SetFacingTo(1.27f);
                                        (*itr)->HandleEmoteCommand(EMOTE_STATE_READY1H);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_REVIVE_DEATHWING);
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
        return new npc_th_battle_alexstrasza_eventAI(creature);
    }
};

class npc_th_battle_drake_double_event : public CreatureScript
{
public:
    npc_th_battle_drake_double_event() : CreatureScript("npc_th_battle_drake_double_event")
    {
    }

    struct npc_th_battle_drake_double_eventAI : public ScriptedAI
    {
        npc_th_battle_drake_double_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_LAND      = 1,
            EVENT_LAND,
            EVENT_SUMMON_MIRROR,
            EVENT_RIDE_ALEX,
            EVENT_RIDE_MIRROR,
            EVENT_MOVE_AWAY,
            EVENT_POINT_AWAY
        };

        enum pointId
        {
            POINT_LAND      = 1,
            POINT_LANDED,
            POINT_TAKEOFF   = 10,
            POINT_AWAY
        };

        enum npcId
        {
            NPC_MIRROR      = 51172,
            NPC_ALEX        = 51171,
            NPC_CALEN       = 51159,
            NPC_DEATHWING   = 52869
        };

        enum actionId
        {
            ACTION_RIDE     = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(false);
            me->SetSpeed(MOVE_WALK, 4.0f, true);
            me->SetSpeed(MOVE_RUN, 4.0f, true);
            me->SetSpeed(MOVE_FLIGHT, 4.0f, true);
            if (owner->GetTypeId() == TYPEID_PLAYER)
            {
                events.ScheduleEvent(EVENT_MOVE_TO_LAND, 1);
                owner->AddAura(60191, me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LAND:
                {
                    events.ScheduleEvent(EVENT_LAND, 2000);
                    break;
                }
                case POINT_LANDED:
                {
                    events.ScheduleEvent(EVENT_SUMMON_MIRROR, 2000);
                    break;
                }
                case POINT_TAKEOFF:
                {
                    events.ScheduleEvent(EVENT_POINT_AWAY, 1);
                    break;
                }
                case POINT_AWAY:
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
                case ACTION_RIDE:
                {
                    events.ScheduleEvent(EVENT_RIDE_ALEX, 1000);
                    events.ScheduleEvent(EVENT_RIDE_MIRROR, 2500);
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
                    case EVENT_MOVE_TO_LAND:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_LAND, -4207.52f, -3369.23f, 233.98f);
                        events.CancelEvent(EVENT_MOVE_TO_LAND);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        x = me->GetPositionX();
                        y = me->GetPositionY();
                        z = 231.60f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LANDED, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_SUMMON_MIRROR:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->SummonCreature(NPC_MIRROR, -4203.48f, -3368.85f, 231.63f, 4.51f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_SUMMON_MIRROR);
                        break;
                    }
                    case EVENT_RIDE_ALEX:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEX, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    (*iter)->SetStandState(UNIT_STAND_STATE_STAND);
                                    (*iter)->EnterVehicle(me, 1);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_RIDE_ALEX);
                        break;
                    }
                    case EVENT_RIDE_MIRROR:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_MIRROR, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->EnterVehicle(me, 0);
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_AWAY, 6000);
                        events.CancelEvent(EVENT_RIDE_MIRROR);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);

                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 10.5f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_ALEX:
                                    case NPC_MIRROR:
                                        (*itr)->ToCreature()->DespawnOrUnsummon(15000);
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        break;
                    }
                    case EVENT_POINT_AWAY:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CALEN, 100.0f);
                        if (creatures.empty())
                            return;

                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    (*iter)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -4213.08f, -3469.98f, 239.20f);
                        events.CancelEvent(EVENT_POINT_AWAY);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_battle_drake_double_eventAI(creature);
    }
};

class npc_th_battle_mirror_event : public CreatureScript
{
public:
    npc_th_battle_mirror_event() : CreatureScript("npc_th_battle_mirror_event")
    {
    }

    struct npc_th_battle_mirror_eventAI : public ScriptedAI
    {
        npc_th_battle_mirror_eventAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_ALEX  = 1,
            EVENT_KNEEL
        };

        enum spellId
        {
            SPELL_MIRROR_AURA   = 94348
        };

        enum pointId
        {
            POINT_ALEX  = 1
        };

        enum npcId
        {
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(false);
            if (owner->GetTypeId() == TYPEID_PLAYER)
            {
                events.ScheduleEvent(EVENT_MOVE_TO_ALEX, 2000);
                owner->CastSpell(owner, SPELL_MIRROR_AURA, true);
                owner->AddAura(60191, me);
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ALEX:
                {
                    events.ScheduleEvent(EVENT_KNEEL, 10000);
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
                    case EVENT_MOVE_TO_ALEX:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_ALEX, -4211.07f, -3385.74f, 230.84f);
                        events.CancelEvent(EVENT_MOVE_TO_ALEX);
                        break;
                    }
                    case EVENT_KNEEL:
                    {
                        me->SetStandState(UNIT_STAND_STATE_KNEEL);
                        events.CancelEvent(EVENT_KNEEL);
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
        return new npc_th_battle_mirror_eventAI(creature);
    }
};

class npc_th_vermillion_skyscreamer : public CreatureScript
{
public:
    npc_th_vermillion_skyscreamer() : CreatureScript("npc_th_vermillion_skyscreamer")
    {
    }

    enum actionId
    {
        ACTION_WP_START     = 1
    };

    enum questId
    {
        QUEST_AND_THE_SKY_STREAKED_RED  = 28171
    };

    struct npc_th_vermillion_skyscreamerAI : public npc_escortAI
    {
        npc_th_vermillion_skyscreamerAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
            me->SetReactState(REACT_PASSIVE);
            wpInProgress = false;
            me->SetCanFly(true);
            me->SetHover(true);
            me->SetDisableGravity(true);
            owner->EnterVehicle(me, 0);
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
                case 12:
                {
                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        invoker->ExitVehicle();
                    me->DespawnOrUnsummon(2000);
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
                    me->SetSpeed(MOVE_FLIGHT, 5.5f, true);
                    me->SetSpeed(MOVE_RUN, 5.5f, true);
                    SetDespawnAtEnd(true);
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
        return new npc_th_vermillion_skyscreamerAI(creature);
    }
};

class spell_th_alexstrasza_tear : public SpellScriptLoader
{
public:
    spell_th_alexstrasza_tear() : SpellScriptLoader("spell_th_alexstrasza_tear")
    {
    }

    class spell_th_alexstrasza_tear_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_alexstrasza_tear_SpellScript);

        enum Id
        {
            NPC_FLOWER_BUNNY    = 47876
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* flowerBunny = caster->FindNearestCreature(NPC_FLOWER_BUNNY, 3.0f, true))
                    return SPELL_CAST_OK;
            }
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_alexstrasza_tear_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_alexstrasza_tear_SpellScript();
    }
};

class npc_th_obsidian_pyrewing : public CreatureScript
{
public:
    npc_th_obsidian_pyrewing() : CreatureScript("npc_th_obsidian_pyrewing")
    {
    }

    struct npc_th_obsidian_pyrewingAI : public ScriptedAI
    {
        npc_th_obsidian_pyrewingAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_CHECK_HEALTH  = 1,
            EVENT_TIMED_DEATH
        };

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply)
            {
                events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MovementExpired(false);
                me->GetMotionMaster()->MoveRandom(35.0f);
            }
            else
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->MovementExpired(false);
                me->GetMotionMaster()->MoveRandom(35.0f);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.35f)
                        {
                            if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                                Talk(0, passenger->GetGUID());

                            events.ScheduleEvent(EVENT_TIMED_DEATH, 8000);
                            events.CancelEvent(EVENT_CHECK_HEALTH);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_HEALTH, 2000);
                        break;
                    }
                    case EVENT_TIMED_DEATH:
                    {
                        me->Kill(me, false);
                        events.CancelEvent(EVENT_TIMED_DEATH);
                        events.CancelEvent(EVENT_CHECK_HEALTH);
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
        return new npc_th_obsidian_pyrewingAI(creature);
    }
};

class spell_th_wyrmhunter_hooks : public SpellScriptLoader
{
public:
    spell_th_wyrmhunter_hooks() : SpellScriptLoader("spell_th_wyrmhunter_hooks")
    {
    }

    class spell_th_wyrmhunter_hooks_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_wyrmhunter_hooks_SpellScript);

        enum Id
        {
            NPC_OBSIDIAN_PYREWING   = 46141
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->GetTypeId() == TYPEID_UNIT)
                    {
                        if (target->ToCreature()->GetEntry() == NPC_OBSIDIAN_PYREWING)
                            return SPELL_CAST_OK;
                    }
                }
            }
            return SPELL_FAILED_BAD_TARGETS;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_wyrmhunter_hooks_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_wyrmhunter_hooks_SpellScript();
    }
};

class npc_th_baleflame : public CreatureScript
{
public:
    npc_th_baleflame() : CreatureScript("npc_th_baleflame")
    {
    }

    enum questId
    {
        QUEST_LAST_OF_HER_KIND  = 28247
    };

    enum npcId
    {
        NPC_OBSIDIA     = 47929
    };

    enum spellId
    {
        SPELL_CLEAVE        = 15284,
        SPELL_SHIELD_SLAM   = 15655,
        SPELL_SUNDER_ARMOR  = 16145
    };

    enum eventId
    {
        EVENT_CLEAVE        = 1,
        EVENT_SHIELD_SLAM,
        EVENT_SUNDER_ARMOR
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LAST_OF_HER_KIND)
        {
            Creature* obsidia = player->FindNearestCreature(NPC_OBSIDIA, 500.0f, true);
            if (!obsidia)
                creature->SummonCreature(NPC_OBSIDIA, -5513.77f, -4914.61f, 197.79f, 0.99f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return false;
        }
        return true;
    }

    struct npc_th_baleflameAI : public ScriptedAI
    {
        npc_th_baleflameAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT)
                damage = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CLEAVE, 1000);
            events.ScheduleEvent(EVENT_SHIELD_SLAM, urand(3000, 8000));
            events.ScheduleEvent(EVENT_SUNDER_ARMOR, urand(2500, 5000));
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
                    case EVENT_CLEAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_CLEAVE);
                        events.RescheduleEvent(EVENT_CLEAVE, urand(4000, 7000));
                        events.RescheduleEvent(EVENT_SHIELD_SLAM, urand(9000, 15000));
                        events.RescheduleEvent(EVENT_SUNDER_ARMOR, urand(2500, 5000));
                        break;
                    }
                    case EVENT_SHIELD_SLAM:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SHIELD_SLAM);
                        events.RescheduleEvent(EVENT_SHIELD_SLAM, urand(9000, 15000));
                        break;
                    }
                    case EVENT_SUNDER_ARMOR:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SUNDER_ARMOR);
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
        return new npc_th_baleflameAI(creature);
    }
};

class npc_th_obsidia : public CreatureScript
{
public:
    npc_th_obsidia() : CreatureScript("npc_th_obsidia")
    {
    }

    enum questId
    {
        QUEST_LAST_OF_HER_KIND  = 28247
    };

    enum npcId
    {
        NPC_BALEFLAME   = 47905
    };

    enum spellId
    {
        SPELL_SUMMON_WHELPS     = 93679,
        SPELL_LAVA_POOL         = 93682,
        SPELL_FLAME_BREATH      = 51219
    };

    enum eventId
    {
        // Entering the Cave
        EVENT_MOVE_TO_CAVE  = 1,
        EVENT_INTO_CAVE,
        EVENT_LAND,
        EVENT_ENTER_COMBAT,

        // Spells
        EVENT_SUMMON_WHELPS,
        EVENT_LAVA_POOL,
        EVENT_FLAME_BREATH
    };

    enum pointId
    {
        POINT_CAVE          = 1,
        POINT_INTO_CAVE,
        POINT_LAND
    };

    struct npc_th_obsidiaAI : public ScriptedAI
    {
        npc_th_obsidiaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetWalk(false);
            me->SetSpeed(MOVE_WALK, 2.4f, true);
            me->SetSpeed(MOVE_RUN, 2.4f, true);
            me->SetSpeed(MOVE_FLIGHT, 2.4f, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            events.ScheduleEvent(EVENT_MOVE_TO_CAVE, 1);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_LAVA_POOL, 4000);
            events.ScheduleEvent(EVENT_FLAME_BREATH, 1000);
            events.ScheduleEvent(EVENT_SUMMON_WHELPS, urand(45000, 60000));
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CAVE:
                {
                    events.ScheduleEvent(EVENT_INTO_CAVE, 1);
                    break;
                }
                case POINT_INTO_CAVE:
                {
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                }
                case POINT_LAND:
                {
                    Talk(0);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    events.ScheduleEvent(EVENT_ENTER_COMBAT, 4000);
                    break;
                }
                default:
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(2);

            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_LAST_OF_HER_KIND) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->CompleteQuest(QUEST_LAST_OF_HER_KIND);
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
                    case EVENT_MOVE_TO_CAVE:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_CAVE, -5453.02f, -4839.55f, 146.95f);
                        events.CancelEvent(EVENT_MOVE_TO_CAVE);
                        break;
                    }
                    case EVENT_INTO_CAVE:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_INTO_CAVE, -5400.01f, -4824.84f, 68.29f);
                        events.CancelEvent(EVENT_INTO_CAVE);
                        break;
                    }
                    case EVENT_LAND:
                    {
                        x = -5378.07f;
                        y = -4816.29f;
                        z = 37.06f;
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_ENTER_COMBAT:
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        if (Creature* baleflame = me->FindNearestCreature(NPC_BALEFLAME, 200.0f))
                            AttackStart(baleflame);
                        events.CancelEvent(EVENT_ENTER_COMBAT);
                        break;
                    }
                    case EVENT_FLAME_BREATH:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_FLAME_BREATH);
                        events.RescheduleEvent(EVENT_FLAME_BREATH, urand(6000, 12000));
                        break;
                    }
                    case EVENT_LAVA_POOL:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(me, SPELL_LAVA_POOL, true);
                        events.RescheduleEvent(EVENT_LAVA_POOL, urand(12000, 18000));
                        break;
                    }
                    case EVENT_SUMMON_WHELPS:
                    {
                        RESCHEDULE_IF_CASTING;
                        Talk(1);
                        DoCast(SPELL_SUMMON_WHELPS);
                        events.RescheduleEvent(EVENT_SUMMON_WHELPS, urand(45000, 50000));
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_obsidiaAI(creature);
    }
};

class npc_th_twilight_gate_fighter : public CreatureScript
{
public:
    npc_th_twilight_gate_fighter() : CreatureScript("npc_th_twilight_gate_fighter")
    {
    }

    struct npc_th_twilight_gate_fighterAI : public ScriptedAI
    {
        npc_th_twilight_gate_fighterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY  = 1,
            EVENT_SLAM,
            EVENT_ENRAGE,
            EVENT_HEROIC_STRIKE
        };

        enum spellId
        {
            SPELL_ENRAGE        = 63227,
            SPELL_HEROIC_STRIKE = 57846,
            SPELL_SLAM          = 79881
        };

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (me->GetEntry() == 45787)
            {
                events.ScheduleEvent(EVENT_SLAM, urand(3000, 5000));
                events.ScheduleEvent(EVENT_HEROIC_STRIKE, urand(6000, 9000));
                events.ScheduleEvent(EVENT_ENRAGE, 60000);
            }
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
                    case EVENT_SLAM:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SLAM);
                        events.RescheduleEvent(EVENT_SLAM, urand(3000, 8000));
                        break;
                    }
                    case EVENT_HEROIC_STRIKE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HEROIC_STRIKE);
                        events.RescheduleEvent(EVENT_HEROIC_STRIKE, urand(4000, 6000));
                        break;
                    }
                    case EVENT_ENRAGE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (me->getVictim())
                            DoCast(SPELL_ENRAGE);
                        events.RescheduleEvent(EVENT_ENRAGE,urand(60000, 120000));
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
        return new npc_th_twilight_gate_fighterAI(creature);
    }
};

class npc_th_angus_stillmountain : public CreatureScript
{
public:
    npc_th_angus_stillmountain() : CreatureScript("npc_th_angus_stillmountain")
    {
    }

    enum questId
    {
        QUEST_SI7_DROP      = 27490
    };

    enum spellId
    {
        SPELL_SUMMON_SI7_GRYPHON    = 85552
    };

    enum creditId
    {
        QUEST_CREDIT_SI7    = 45902
    };

    enum npcId
    {
        NPC_SI7_GRYPHON     = 45881
    };

    #define GOSSIP_SI7 "Angus, I'm here to lead the Wildhammer squad and drop off the SI:7 agents."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_SI7_DROP) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, player, NPC_SI7_GRYPHON, 300.0f);
                if (!creatures.empty())
                {
                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                        {
                            player->PlayerTalkClass->SendCloseGossip();
                            return true;
                        }
                    }
                }

                // Need 5 gryphons!
                for (uint32 gryphons = 0; gryphons < 5; ++gryphons)
                    player->CastSpell(player, SPELL_SUMMON_SI7_GRYPHON, true);

                player->KilledMonsterCredit(QUEST_CREDIT_SI7);
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_SI7_DROP) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SI7, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }
};

class npc_th_si7_korkron_trigger : public CreatureScript
{
public:
    npc_th_si7_korkron_trigger() : CreatureScript("npc_th_si7_korkron_trigger")
    {
    }

    struct npc_th_si7_korkron_triggerAI : public ScriptedAI
    {
        npc_th_si7_korkron_triggerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_CHECK_SI7     = 1
        };

        enum spellId
        {
            SPELL_SI7_DROP_TARGET_VISUAL    = 89436
        };

        enum questId
        {
            QUEST_SI7_DROP          = 27490,
            QUEST_KOR_KRON_DROP     = 27491
        };

        enum npcId
        {
            NPC_ALLIANCE_GRYPHON    = 45881,
            NPC_HORDE_WINDRIDER     = 45942
        };

        enum creditId
        {
            QUEST_CREDIT_DROP   = 45877
        };

        void InitializeAI()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            DoCast(me, SPELL_SI7_DROP_TARGET_VISUAL, true);
            events.ScheduleEvent(EVENT_CHECK_SI7, 2000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_SI7:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 40.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(40.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr))
                            {
                                if ((*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    if ((*itr)->ToTempSummon() && ((*itr)->GetEntry() == NPC_ALLIANCE_GRYPHON || (*itr)->GetEntry() == NPC_HORDE_WINDRIDER))
                                    {
                                        Unit* summoner = (*itr)->ToTempSummon()->GetSummoner();
                                        if (summoner && summoner->GetTypeId() == TYPEID_PLAYER)
                                        {
                                            summoner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_DROP);
                                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                        }
                                    }
                                }
                            }
                        }

                        events.RescheduleEvent(EVENT_CHECK_SI7, 2000);
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
        return new npc_th_si7_korkron_triggerAI(creature);
    }
};

class go_th_hidden_explosives : public GameObjectScript
{
public:
    go_th_hidden_explosives() : GameObjectScript("go_th_hidden_explosives")
    {
    }

    enum questId
    {
        QUEST_MOVE_THE_MOUNTAIN_A   = 27494,
        QUEST_MOVE_THE_MOUNTAIN_H   = 27495
    };

    enum npcId
    {
        NPC_FOG_TRIGGER     = 45968,
        NPC_THE_MOUNTAIN    = 45644
    };

    class eventMoveTheMountain : public BasicEvent
    {
    public:
        explicit eventMoveTheMountain(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            creature->GetMotionMaster()->MoveJump(-4450.21f, -4471.44f, 225.08f, 25.0f, 25.0f, 1);
            creature->AI()->TalkWithDelay(6000, 4);
            creature->AI()->TalkWithDelay(12000, 5);
            creature->m_Events.AddEvent(new eventFinalizeMountain(creature), (creature)->m_Events.CalculateTime(11000));
            return true;
        }

    private:
        Creature* creature;
    };

    class eventFinalizeMountain : public BasicEvent
    {
    public:
        explicit eventFinalizeMountain(Creature* creature) : creature(creature)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            creature->GetMotionMaster()->MovePoint(2, -4404.28f, -4427.04f, 286.97f);
            creature->DespawnOrUnsummon(9000);
            return true;
        }

    private:
        Creature* creature;
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_MOVE_THE_MOUNTAIN_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_MOVE_THE_MOUNTAIN_H) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* fogTrigger = player->FindNearestCreature(NPC_FOG_TRIGGER, 200.0f);
            if (!fogTrigger)
            {
                player->SummonCreature(NPC_FOG_TRIGGER, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                if (Creature* theMountain = player->FindNearestCreature(NPC_THE_MOUNTAIN, 200.0f, true))
                {
                    if (theMountain->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                        return false;

                    theMountain->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                    theMountain->AI()->Talk(0, player->GetGUID());
                    theMountain->AI()->TalkWithDelay(1000, 1, player->GetGUID());
                    theMountain->AI()->TalkWithDelay(2000, 2, player->GetGUID());
                    theMountain->AI()->TalkWithDelay(4000, 3);
                    theMountain->SetFacingTo(0.57f);
                    theMountain->m_Events.AddEvent(new eventMoveTheMountain(theMountain), (theMountain)->m_Events.CalculateTime(7500));
                }
                return false;
            }
        }
        return false;
    }
};

class spell_th_attack_signal : public SpellScriptLoader
{
public:
    spell_th_attack_signal() : SpellScriptLoader("spell_th_attack_signal")
    {
    }

    class spell_th_attack_signal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_attack_signal_SpellScript);

        enum Id
        {
            NPC_TOWER_TRIGGER   = 24110
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* towerTrigger = caster->FindNearestCreature(NPC_TOWER_TRIGGER, 15.0f, true))
                    return SPELL_CAST_OK;
            }
            return SPELL_FAILED_NOT_HERE;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_attack_signal_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_attack_signal_SpellScript();
    }
};

class npc_th_cassius_the_white : public CreatureScript
{
public:
    npc_th_cassius_the_white() : CreatureScript("npc_th_cassius_the_white")
    {
    }

    enum questId
    {
        QUEST_UP_TO_THE_CITADEL     = 27502
    };

    enum npcId
    {
        NPC_SI_7_AGENT      = 46113,
        NPC_SI_7_COMMANDER  = 46114
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_UP_TO_THE_CITADEL)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 1000.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(1000.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_SI_7_AGENT:
                            case NPC_SI_7_COMMANDER:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            player->SummonCreature(NPC_SI_7_COMMANDER, -4405.81f, -4489.62f, 207.40f, 4.01f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_SI_7_AGENT, -4401.98f, -4485.24f, 208.48f, 4.07f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_SI_7_AGENT, -4402.36f, -4488.41f, 207.13f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_SI_7_AGENT, -4404.51f, -4484.88f, 209.17f, 4.34f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_SI_7_AGENT, -4407.97f, -4485.52f, 209.65f, 4.34f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_SI_7_AGENT, -4406.22f, -4483.34f, 210.29f, 4.74f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return false;
        }
        return true;
    }
};

class npc_th_si7_commander : public CreatureScript
{
public:
    npc_th_si7_commander() : CreatureScript("npc_th_si7_commander")
    {
    }

    enum actionId
    {
        ACTION_WP_START         = 1,
        ACTION_ATTACK_AND_DIE
    };

    enum questId
    {
        QUEST_UP_TO_THE_CITADEL     = 27502
    };

    enum eventId
    {
        EVENT_START_WP          = 1,
        EVENT_QUEST_COMPLETE,
        EVENT_ENABLE_CHOGALL,
        EVENT_ADJUST_CHOGALL,
        EVENT_DIE
    };

    enum creditId
    {
        CREDIT_TALK_COMMANDER   = 46076,
        CREDIT_ESCORT_COMPLETE  = 46121
    };

    enum npcId
    {
        NPC_CHOGALL     = 46137,
        NPC_SI7_AGENT   = 46113
    };

    #define GOSSIP_TEXT_ESCORT_5 "I'm ready. Commander, let's head up."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_UP_TO_THE_CITADEL) == QUEST_STATUS_INCOMPLETE)
            {
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->DoAction(ACTION_WP_START);
                creature->setFaction(player->getFaction());
                player->KilledMonsterCredit(CREDIT_TALK_COMMANDER);
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_UP_TO_THE_CITADEL) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ESCORT_4, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_si7_commanderAI : public npc_escortAI
    {
        npc_th_si7_commanderAI(Creature* creature) : npc_escortAI(creature)
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
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER && me->ToTempSummon()->GetSummoner() == (*itr))
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_UP_TO_THE_CITADEL) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->KilledMonsterCredit(CREDIT_ESCORT_COMPLETE);
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 2:
                {
                    Talk(1);
                    if (me->ToTempSummon())
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->SummonCreature(NPC_CHOGALL, -4474.40f, -4436.75f, 253.75f, 5.55f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                    }
                    break;
                }
                case 4:
                {
                    Talk(2);
                    events.ScheduleEvent(EVENT_ENABLE_CHOGALL, 1000);
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
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    events.ScheduleEvent(EVENT_START_WP, 2500);
                    break;
                }
                case ACTION_ATTACK_AND_DIE:
                {
                    events.ScheduleEvent(EVENT_QUEST_COMPLETE, 1);
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
                        me->SetReactState(REACT_PASSIVE);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_SI7_AGENT, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*iter)->GetMotionMaster()->MoveFollow(me, urand(3, 6), urand(1, 4));
                            }
                        }
                        events.CancelEvent(EVENT_START_WP);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        CompleteAoE();
                        Talk(3);
                        me->RemoveAllAurasExceptType(SPELL_AURA_MOD_INVISIBILITY);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_SI7_AGENT, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*iter)->RemoveAllAurasExceptType(SPELL_AURA_MOD_INVISIBILITY);
                            }
                        }

                        me->GetMotionMaster()->MovePoint(2, -4473.67f, -4437.45f, 253.38f);
                        events.ScheduleEvent(EVENT_DIE, 1000);
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        break;
                    }
                    case EVENT_ENABLE_CHOGALL:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CHOGALL, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                {
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(1000, 0);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(13000, 1);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(18000, 2);
                                    (*iter)->ToCreature()->CastWithDelay(10000, (*iter), 86027, true);
                                    (*iter)->DespawnOrUnsummon(25000);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 9000);
                        events.CancelEvent(EVENT_ENABLE_CHOGALL);
                        break;
                    }
                    case EVENT_DIE:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_SI7_AGENT, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*iter)->Kill((*iter), false);
                            }
                        }
                        me->Kill(me, false);
                        events.CancelEvent(EVENT_DIE);
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
        return new npc_th_si7_commanderAI(creature);
    }
};

class spell_th_water_of_life : public SpellScriptLoader
{
public:
    spell_th_water_of_life() : SpellScriptLoader("spell_th_water_of_life")
    {
    }

    class spell_th_water_of_life_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_water_of_life_SpellScript);

        enum Id
        {
            NPC_CORPSE_OF_FINLAY    = 46819,
            SPELL_RIBBON_OF_SOULS   = 87254
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* finlay = caster->FindNearestCreature(NPC_CORPSE_OF_FINLAY, 6.0f, true))
                {
                    if (!finlay->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                        return SPELL_CAST_OK;
                }
            }
            return SPELL_FAILED_NOT_HERE;
        }

        void HandleSummon()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* finlay = caster->FindNearestCreature(NPC_CORPSE_OF_FINLAY, 8.0f, true))
                {
                    finlay->CastSpell(finlay, SPELL_RIBBON_OF_SOULS, true);
                    finlay->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_water_of_life_SpellScript::CheckCast);
            AfterCast += SpellCastFn(spell_th_water_of_life_SpellScript::HandleSummon);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_water_of_life_SpellScript();
    }
};

class npc_th_finlay_controller : public CreatureScript
{
public:
    npc_th_finlay_controller() : CreatureScript("npc_th_finlay_controller")
    {
    }

    struct npc_th_finlay_controllerAI : public ScriptedAI
    {
        npc_th_finlay_controllerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_QUEST_COMPLETE    = 1
        };

        enum npcId
        {
            NPC_FINLAY  = 46819
        };

        enum questId
        {
            QUEST_WATER_OF_LIFE_A   = 27719,
            QUEST_WATER_OF_LIFE_H   = 27798
        };

        enum creditId
        {
            CREDIT_WATER_OF_LIFE    = 46819
        };

        void InitializeAI()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            if (Creature* finlay = me->FindNearestCreature(NPC_FINLAY, 60.0f, true))
            {
                finlay->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                finlay->AI()->TalkWithDelay(1000, 0);
                finlay->AI()->TalkWithDelay(5000, 1);
                finlay->AI()->TalkWithDelay(13000, 2);
                finlay->AI()->TalkWithDelay(20000, 3);
                finlay->AI()->TalkWithDelay(28000, 4);
                finlay->AI()->TalkWithDelay(36000, 5);
                finlay->AI()->TalkWithDelay(43000, 6);
                finlay->AI()->TalkWithDelay(51000, 7);
                finlay->AI()->TalkWithDelay(58000, 8);
                events.ScheduleEvent(EVENT_QUEST_COMPLETE, 58000);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_QUEST_COMPLETE:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 45.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(45.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                            {
                                if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_WATER_OF_LIFE_A) == QUEST_STATUS_INCOMPLETE || (*itr)->ToPlayer()->GetQuestStatus(QUEST_WATER_OF_LIFE_H) == QUEST_STATUS_INCOMPLETE)
                                    (*itr)->ToPlayer()->KilledMonsterCredit(CREDIT_WATER_OF_LIFE);
                            }
                        }
                        if (Creature* finlay = me->FindNearestCreature(NPC_FINLAY, 60.0f, true))
                            finlay->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                        events.CancelEvent(EVENT_QUEST_COMPLETE);
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
        return new npc_th_finlay_controllerAI(creature);
    }
};

class go_th_earth_portal_controller : public GameObjectScript
{
public:
    go_th_earth_portal_controller() : GameObjectScript("go_th_earth_portal_controller")
    {
    }

    enum questId
    {
        QUEST_PORTAL_OVERLOAD   = 27659
    };

    enum npcId
    {
        NPC_APEXAR              = 46258,
        NPC_DEBILITATED_APEXAR  = 46273
    };

    enum spellId
    {
        SPELL_DUST_EXPLOSION    = 82831
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_PORTAL_OVERLOAD) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* apexar = player->FindNearestCreature(NPC_APEXAR, 50.0f))
            {
                apexar->CastSpell(apexar, SPELL_DUST_EXPLOSION, true);
                apexar->UpdateEntry(NPC_DEBILITATED_APEXAR);
                return false;
            }
        }
        return false;
    }
};

class go_th_air_portal_controller : public GameObjectScript
{
public:
    go_th_air_portal_controller() : GameObjectScript("go_th_air_portal_controller")
    {
    }

    enum questId
    {
        QUEST_PORTAL_OVERLOAD   = 27659
    };

    enum npcId
    {
        NPC_AETHARON                = 46259,
        NPC_DEBILITATED_AETHARON    = 46270
    };

    enum spellId
    {
        SPELL_DUST_EXPLOSION    = 82831
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_PORTAL_OVERLOAD) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* aetharon = player->FindNearestCreature(NPC_AETHARON, 50.0f))
            {
                aetharon->CastSpell(aetharon, SPELL_DUST_EXPLOSION, true);
                aetharon->UpdateEntry(NPC_DEBILITATED_AETHARON);
                return false;
            }
        }
        return false;
    }
};

class go_th_water_portal_controller : public GameObjectScript
{
public:
    go_th_water_portal_controller() : GameObjectScript("go_th_water_portal_controller")
    {
    }

    enum questId
    {
        QUEST_PORTAL_OVERLOAD   = 27659
    };

    enum npcId
    {
        NPC_EDEMANTUS               = 46256,
        NPC_DEBILITATED_EDEMANTUS   = 46272
    };

    enum spellId
    {
        SPELL_DUST_EXPLOSION = 82831
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_PORTAL_OVERLOAD) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* edemantus = player->FindNearestCreature(NPC_EDEMANTUS, 50.0f))
            {
                edemantus->CastSpell(edemantus, SPELL_DUST_EXPLOSION, true);
                edemantus->UpdateEntry(NPC_DEBILITATED_EDEMANTUS);
                return false;
            }
        }
        return false;
    }
};

class npc_th_debilitated_apexar : public CreatureScript
{
public:
    npc_th_debilitated_apexar() : CreatureScript("npc_th_debilitated_apexar")
    {
    }

    struct npc_th_debilitated_apexarAI : public ScriptedAI
    {
        npc_th_debilitated_apexarAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_HARDENED      = 1,
            EVENT_ROCK_BASH,
            EVENT_SHOCKWAVE,
            EVENT_VULNERABLE
        };

        enum spellId
        {
            SPELL_HARDENED      = 82839,
            SPELL_ROCK_BASH     = 82841,
            SPELL_SHOCKWAVE     = 79872,
            SPELL_VULNERABLE    = 82840
        };

        enum npcId
        {
            NPC_APEXAR  = 46258
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHOCKWAVE, 1);
            events.ScheduleEvent(EVENT_ROCK_BASH, urand(3000, 5000));
            events.ScheduleEvent(EVENT_HARDENED, 1);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->UpdateEntry(NPC_APEXAR);
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
                    case EVENT_SHOCKWAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_SHOCKWAVE);
                        events.RescheduleEvent(EVENT_SHOCKWAVE, urand(10000, 20000));
                        break;
                    }
                    case EVENT_HARDENED:
                    {
                        RESCHEDULE_IF_CASTING;
                        me->RemoveAurasDueToSpell(SPELL_VULNERABLE);
                        DoCast(SPELL_HARDENED);
                        events.ScheduleEvent(EVENT_HARDENED, urand(15000, 18500));
                        break;
                    }
                    case EVENT_VULNERABLE:
                    {
                        RESCHEDULE_IF_CASTING;
                        me->RemoveAurasDueToSpell(SPELL_HARDENED);
                        DoCast(SPELL_VULNERABLE);
                        events.ScheduleEvent(EVENT_VULNERABLE, urand(20000, 35000));
                        break;
                    }
                    case EVENT_ROCK_BASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_ROCK_BASH);
                        events.RescheduleEvent(EVENT_ROCK_BASH, urand(3000, 9500));
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
        return new npc_th_debilitated_apexarAI(creature);
    }
};

class npc_th_debilitated_aetharon : public CreatureScript
{
public:
    npc_th_debilitated_aetharon() : CreatureScript("npc_th_debilitated_aetharon")
    {
    }

    struct npc_th_debilitated_aetharonAI : public ScriptedAI
    {
        npc_th_debilitated_aetharonAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_LIGHTNING_BOLT    = 1,
            EVENT_LIGHTNING_SHIELD,
            EVENT_WIND_SHEAR
        };

        enum spellId
        {
            SPELL_LIGHTNING_BOLT    = 57780,
            SPELL_LIGHTNING_SHIELD  = 19514,
            SPELL_WIND_SHEAR        = 83005
        };

        enum npcId
        {
            NPC_AETHARON    = 46259
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_WIND_SHEAR, 1000);
            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, urand(3000, 5000));
            events.ScheduleEvent(EVENT_LIGHTNING_SHIELD, 1);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->UpdateEntry(NPC_AETHARON);
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
                    case EVENT_WIND_SHEAR:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_WIND_SHEAR);
                        events.RescheduleEvent(EVENT_WIND_SHEAR, urand(10000, 20000));
                        break;
                    }
                    case EVENT_LIGHTNING_SHIELD:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_LIGHTNING_SHIELD);
                        events.ScheduleEvent(EVENT_LIGHTNING_SHIELD, urand(20000, 35000));
                        break;
                    }
                    case EVENT_LIGHTNING_BOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_LIGHTNING_BOLT);
                        events.RescheduleEvent(EVENT_LIGHTNING_BOLT, urand(3000, 9500));
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
        return new npc_th_debilitated_aetharonAI(creature);
    }
};

class npc_th_debilitated_edemantus : public CreatureScript
{
public:
    npc_th_debilitated_edemantus() : CreatureScript("npc_th_debilitated_edemantus")
    {
    }

    struct npc_th_debilitated_edemantusAI : public ScriptedAI
    {
        npc_th_debilitated_edemantusAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SPLASH        = 1,
            EVENT_WATER_BOLT
        };

        enum spellId
        {
            SPELL_SPLASH        = 78542,
            SPELL_WATER_BOLT    = 32011
        };

        enum npcId
        {
            NPC_EDEMANTUS   = 46256
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SPLASH, 1000);
            events.ScheduleEvent(EVENT_WATER_BOLT, urand(3000, 5000));
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->UpdateEntry(NPC_EDEMANTUS);
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
                    case EVENT_SPLASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_SPLASH);
                        events.ScheduleEvent(EVENT_SPLASH, urand(20000, 35000));
                        break;
                    }
                    case EVENT_WATER_BOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_WATER_BOLT);
                        events.RescheduleEvent(EVENT_WATER_BOLT, urand(3000, 9500));
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
        return new npc_th_debilitated_edemantusAI(creature);
    }
};

class npc_th_dame_alys_finnsson : public CreatureScript
{
public:
    npc_th_dame_alys_finnsson() : CreatureScript("npc_th_dame_alys_finnsson")
    {
    }

    struct npc_th_dame_alys_finnssonAI : public ScriptedAI
    {
        npc_th_dame_alys_finnssonAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_FAERIE_FIRE   = 1,
            EVENT_INSECT_SWARM,
            EVENT_STARFALL,
            EVENT_STARFIRE,
            EVENT_SUMMON_HELPER,
            EVENT_ENABLE_HELPER
        };

        enum spellId
        {
            SPELL_FAERIE_FIRE   = 25602,
            SPELL_INSECT_SWARM  = 83017,
            SPELL_STARFALL      = 79823,
            SPELL_STARFIRE      = 78907
        };

        enum npcId
        {
            NPC_GARONA  = 46386,
            NPC_MATHIAS = 46385
        };

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* mathias = me->FindNearestCreature(NPC_MATHIAS, 100.0f, true))
            {
                mathias->AI()->Talk(0);
                mathias->DespawnOrUnsummon(6000);
                mathias->RemoveAllAuras();
            }
            if (Creature* garona = me->FindNearestCreature(NPC_GARONA, 100.0f, true))
            {
                garona->AI()->Talk(0);
                garona->DespawnOrUnsummon(6000);
                garona->RemoveAllAuras();
            }

            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->ToPlayer()->KilledMonsterCredit(46341);
            }

            helperSpawned = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_SUMMON_HELPER, 1000);
            events.ScheduleEvent(EVENT_FAERIE_FIRE, 1);
            events.ScheduleEvent(EVENT_INSECT_SWARM, 1000);
            events.ScheduleEvent(EVENT_STARFALL, urand(3000, 8000));
            events.ScheduleEvent(EVENT_STARFIRE, urand(4000, 6000));
            helperSpawned = false;
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            helperSpawned = false;
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
                    case EVENT_FAERIE_FIRE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_FAERIE_FIRE);
                        events.RescheduleEvent(EVENT_FAERIE_FIRE, urand(10000, 15000));
                        break;
                    }
                    case EVENT_INSECT_SWARM:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_INSECT_SWARM);
                        events.RescheduleEvent(EVENT_INSECT_SWARM, urand(10000, 15000));
                        break;
                    }
                    case EVENT_STARFIRE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_STARFIRE);
                        events.RescheduleEvent(EVENT_STARFIRE, urand(2000, 6000));
                        break;
                    }
                    case EVENT_STARFALL:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_STARFALL);
                        events.RescheduleEvent(EVENT_STARFALL, urand(5000, 8500));
                        break;
                    }
                    case EVENT_SUMMON_HELPER:
                    {
                        if (helperSpawned == false && me->GetHealth() <= me->GetMaxHealth() * 0.20f)
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (victim->getRaceMask() & RACEMASK_ALLIANCE)
                                    me->SummonCreature(NPC_MATHIAS, -5230.02f, -4690.27f, 368.05f, 3.83f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                else
                                    me->SummonCreature(NPC_GARONA, -5230.02f, -4690.27f, 368.05f, 3.83f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

                                events.ScheduleEvent(EVENT_ENABLE_HELPER, 2000);
                                events.CancelEvent(EVENT_SUMMON_HELPER);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_SUMMON_HELPER, 2000);
                        break;
                    }
                    case EVENT_ENABLE_HELPER:
                    {
                        if (Creature* mathias = me->FindNearestCreature(NPC_MATHIAS, 100.0f, true))
                            mathias->AI()->AttackStart(me);
                        if (Creature* garona = me->FindNearestCreature(NPC_GARONA, 100.0f, true))
                            garona->AI()->AttackStart(me);
                        events.CancelEvent(EVENT_ENABLE_HELPER);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        protected:
            bool helperSpawned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_dame_alys_finnssonAI(creature);
    }
};

class npc_th_master_klem : public CreatureScript
{
public:
    npc_th_master_klem() : CreatureScript("npc_th_master_klem")
    {
    }

    struct npc_th_master_klemAI : public ScriptedAI
    {
        npc_th_master_klemAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_BRUTAL_FIST       = 1,
            EVENT_SNAP_KICK,
            EVENT_STEAL_WEAPON,
            EVENT_SWEEPING_WHIRLWIND,
            EVENT_UPPERCUT,
            EVENT_SUMMON_HELPER,
            EVENT_ENABLE_HELPER
        };

        enum spellId
        {
            SPELL_BRUTAL_FIST           = 61041,
            SPELL_SNAP_KICK             = 46182,
            SPELL_STEAL_WEAPON          = 36208,
            SPELL_SWEEPING_WHIRLWIND    = 86374,
            SPELL_UPPERCUT              = 80182
        };

        enum npcId
        {
            NPC_GARONA  = 46386,
            NPC_MATHIAS = 46385
        };

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* mathias = me->FindNearestCreature(NPC_MATHIAS, 100.0f, true))
            {
                mathias->AI()->Talk(2);
                mathias->DespawnOrUnsummon(6000);
                mathias->RemoveAllAuras();
            }
            if (Creature* garona = me->FindNearestCreature(NPC_GARONA, 100.0f, true))
            {
                garona->AI()->Talk(2);
                garona->DespawnOrUnsummon(6000);
                garona->RemoveAllAuras();
            }

            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->ToPlayer()->KilledMonsterCredit(46342);
            }

            helperSpawned = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_SUMMON_HELPER, 1000);
            events.ScheduleEvent(EVENT_BRUTAL_FIST, 1);
            events.ScheduleEvent(EVENT_STEAL_WEAPON, 4000);
            events.ScheduleEvent(EVENT_SWEEPING_WHIRLWIND, urand(3000, 8000));
            events.ScheduleEvent(EVENT_SNAP_KICK, urand(4000, 6000));
            events.ScheduleEvent(EVENT_UPPERCUT, urand(12000, 16000));
            helperSpawned = false;
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            helperSpawned = false;
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
                    case EVENT_STEAL_WEAPON:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_STEAL_WEAPON);
                        events.RescheduleEvent(EVENT_STEAL_WEAPON, urand(10000, 15000));
                        break;
                    }
                    case EVENT_UPPERCUT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_UPPERCUT);
                        events.RescheduleEvent(EVENT_UPPERCUT, urand(10000, 15000));
                        break;
                    }
                    case EVENT_BRUTAL_FIST:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BRUTAL_FIST);
                        events.RescheduleEvent(EVENT_BRUTAL_FIST, urand(2000, 6000));
                        break;
                    }
                    case EVENT_SWEEPING_WHIRLWIND:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_SWEEPING_WHIRLWIND);
                        events.RescheduleEvent(EVENT_SWEEPING_WHIRLWIND, urand(15000, 20000));
                        break;
                    }
                    case EVENT_SUMMON_HELPER:
                    {
                        if (helperSpawned == false && me->GetHealth() <= me->GetMaxHealth() * 0.20f)
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (victim->getRaceMask() & RACEMASK_ALLIANCE)
                                    me->SummonCreature(NPC_MATHIAS, -4648.60f, -4359.02f, 293.63f, 1.51f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                else
                                    me->SummonCreature(NPC_GARONA, -4648.60f, -4359.02f, 293.63f, 1.51f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

                                events.ScheduleEvent(EVENT_ENABLE_HELPER, 2000);
                                events.CancelEvent(EVENT_SUMMON_HELPER);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_SUMMON_HELPER, 2000);
                        break;
                    }
                    case EVENT_ENABLE_HELPER:
                    {
                        if (Creature* mathias = me->FindNearestCreature(NPC_MATHIAS, 100.0f, true))
                            mathias->AI()->AttackStart(me);
                        if (Creature* garona = me->FindNearestCreature(NPC_GARONA, 100.0f, true))
                            garona->AI()->AttackStart(me);
                        events.CancelEvent(EVENT_ENABLE_HELPER);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        bool helperSpawned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_master_klemAI(creature);
    }
};

class npc_th_mia_the_rose : public CreatureScript
{
public:
    npc_th_mia_the_rose() : CreatureScript("npc_th_mia_the_rose")
    {
    }

    struct npc_th_mia_the_roseAI : public ScriptedAI
    {
        npc_th_mia_the_roseAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_BACKSTAB          = 1,
            EVENT_DEADLY_THROW,
            EVENT_HEMORRHAGE,
            EVENT_SHADOWSTEP,
            EVENT_SEDUCTION,
            EVENT_SUMMON_HELPER,
            EVENT_ENABLE_HELPER
        };

        enum spellId
        {
            SPELL_BACKSTAB          = 79862,
            SPELL_DEADLY_THROW      = 79866,
            SPELL_HEMORRHAGE        = 79863,
            SPELL_SEDUCTION         = 86545,
            SPELL_SHADOWSTEP        = 79864
        };

        enum npcId
        {
            NPC_GARONA  = 46386,
            NPC_MATHIAS = 46385
        };

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* mathias = me->FindNearestCreature(NPC_MATHIAS, 100.0f, true))
            {
                mathias->AI()->Talk(1);
                mathias->DespawnOrUnsummon(6000);
                mathias->RemoveAllAuras();
            }
            if (Creature* garona = me->FindNearestCreature(NPC_GARONA, 100.0f, true))
            {
                garona->AI()->Talk(1);
                garona->DespawnOrUnsummon(6000);
                garona->RemoveAllAuras();
            }

            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->ToPlayer()->KilledMonsterCredit(46343);
            }

            helperSpawned = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_SUMMON_HELPER, 1000);
            events.ScheduleEvent(EVENT_SHADOWSTEP, 1);
            events.ScheduleEvent(EVENT_HEMORRHAGE, 4000);
            events.ScheduleEvent(EVENT_BACKSTAB, urand(3000, 8000));
            events.ScheduleEvent(EVENT_DEADLY_THROW, urand(4000, 6000));
            events.ScheduleEvent(EVENT_SEDUCTION, urand(18000, 24000));
            helperSpawned = false;
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            helperSpawned = false;
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
                    case EVENT_SHADOWSTEP:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SHADOWSTEP);
                        events.RescheduleEvent(EVENT_SHADOWSTEP, urand(10000, 15000));
                        break;
                    }
                    case EVENT_SEDUCTION:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SEDUCTION);
                        events.RescheduleEvent(EVENT_SEDUCTION, urand(10000, 15000));
                        break;
                    }
                    case EVENT_HEMORRHAGE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_HEMORRHAGE);
                        events.RescheduleEvent(EVENT_HEMORRHAGE, urand(2000, 6000));
                        break;
                    }
                    case EVENT_BACKSTAB:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BACKSTAB);
                        events.RescheduleEvent(EVENT_BACKSTAB, urand(2000, 6000));
                        break;
                    }
                    case EVENT_DEADLY_THROW:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_DEADLY_THROW);
                        events.RescheduleEvent(EVENT_DEADLY_THROW, urand(15000, 20000));
                        break;
                    }
                    case EVENT_SUMMON_HELPER:
                    {
                        if (helperSpawned == false && me->GetHealth() <= me->GetMaxHealth() * 0.20f)
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (victim->getRaceMask() & RACEMASK_ALLIANCE)
                                    me->SummonCreature(NPC_MATHIAS, -5100.20f, -4660.52f, 378.94f, 5.01f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                else
                                    me->SummonCreature(NPC_GARONA, -5100.20f, -4660.52f, 378.94f, 5.01f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

                                events.ScheduleEvent(EVENT_ENABLE_HELPER, 2000);
                                events.CancelEvent(EVENT_SUMMON_HELPER);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_SUMMON_HELPER, 2000);
                        break;
                    }
                    case EVENT_ENABLE_HELPER:
                    {
                        if (Creature* mathias = me->FindNearestCreature(NPC_MATHIAS, 100.0f, true))
                            mathias->AI()->AttackStart(me);
                        if (Creature* garona = me->FindNearestCreature(NPC_GARONA, 100.0f, true))
                            garona->AI()->AttackStart(me);
                        events.CancelEvent(EVENT_ENABLE_HELPER);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        bool helperSpawned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_mia_the_roseAI(creature);
    }
};

class npc_th_mr_goldmine : public CreatureScript
{
public:
    npc_th_mr_goldmine() : CreatureScript("npc_th_mr_goldmine")
    {
    }

    enum questId
    {
        QUEST_MR_GOLDMINE_WILD_RIDE_A       = 27720,
        QUEST_MR_GOLDMINE_WILD_RIDE_H       = 28885,
        QUEST_A_FIERY_REUNION               = 27745
    };

    enum spellId
    {
        SPELL_SUMMON_MINE_CART  = 86625,
        SPELL_SUMMON_INITIATE   = 86730
    };

    enum creditId
    {
        CREDIT_GOLDMINE_TALK    = 46472
    };

    enum npcId
    {
        NPC_INITIATE    = 46513
    };

    #define GOSSIP_GOLDMINE     "Mr. Goldmine, I'm ready for that wild ride."

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_MR_GOLDMINE_WILD_RIDE_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_MR_GOLDMINE_WILD_RIDE_H) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GOLDMINE, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_MR_GOLDMINE_WILD_RIDE_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_MR_GOLDMINE_WILD_RIDE_H) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(player, 80.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                player->VisitNearbyObject(80.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToTempSummon() && (*itr)->GetEntry() == 46513 && (*itr)->ToTempSummon()->GetSummoner() == player)
                        return false;
                }

                player->KilledMonsterCredit(CREDIT_GOLDMINE_TALK);
                player->AddAura(60191, player);
                player->CastSpell(player, SPELL_SUMMON_MINE_CART, true);
                player->CastSpell(player, SPELL_SUMMON_INITIATE, true);
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_A_FIERY_REUNION)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_INITIATE, 100.0f);
            if (!creatures.empty())
            {
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() && (*iter)->ToTempSummon()->GetSummoner() == player)
                        (*iter)->ToCreature()->DespawnOrUnsummon(1);
                }
            }
            player->RemoveAurasDueToSpell(86739);
        }
        return true;
    }
};

class spell_th_the_elementium_axe : public SpellScriptLoader
{
public:
    spell_th_the_elementium_axe() : SpellScriptLoader("spell_th_the_elementium_axe")
    {
    }

    class spell_th_the_elementium_axe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_the_elementium_axe_SpellScript);

        enum Id
        {
            NPC_CHAINED_LIRASTRASZA     = 46456,
            NPC_UNCHAINED_LIRASTRASZA   = 46452,
            SPELL_QUEST_INVISIBILITY    = 49416
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* lirastrasza = caster->FindNearestCreature(NPC_CHAINED_LIRASTRASZA, 10.0f, true))
                    return SPELL_CAST_OK;
            }
            return SPELL_FAILED_NOT_HERE;
        }

        void HandleSummon()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* lirastrasza = caster->FindNearestCreature(NPC_CHAINED_LIRASTRASZA, 10.0f, true))
                {
                    caster->RemoveAurasDueToSpell(SPELL_QUEST_INVISIBILITY);
                    caster->SummonCreature(NPC_UNCHAINED_LIRASTRASZA, lirastrasza->GetPositionX(), lirastrasza->GetPositionY(), lirastrasza->GetPositionZ(), lirastrasza->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_the_elementium_axe_SpellScript::CheckCast);
            AfterCast += SpellCastFn(spell_th_the_elementium_axe_SpellScript::HandleSummon);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_the_elementium_axe_SpellScript();
    }
};

class npc_th_lirastrasza_unchained : public CreatureScript
{
public:
    npc_th_lirastrasza_unchained() : CreatureScript("npc_th_lirastrasza_unchained")
    {
    }

    struct npc_th_lirastrasza_unchainedAI : public ScriptedAI
    {
        npc_th_lirastrasza_unchainedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_TAKEOFF   = 1,
            EVENT_MOVE_AWAY
        };

        enum pointId
        {
            POINT_TAKEOFF,
            POINT_AWAY
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetHover(false);
            owner->AddAura(60191, me);
            TalkWithDelay(500, 0, owner->GetGUID());
            events.ScheduleEvent(EVENT_TAKEOFF, 4000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TAKEOFF:
                {
                    me->SetWalk(false);
                    me->SetSpeed(MOVE_WALK, 3.0f, true);
                    me->SetSpeed(MOVE_RUN, 3.0f, true);
                    me->SetSpeed(MOVE_FLIGHT, 3.0f, true);
                    TalkWithDelay(5000, 1);
                    events.ScheduleEvent(EVENT_MOVE_AWAY, 8000);
                    break;
                }
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
                    case EVENT_TAKEOFF:
                    {
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);

                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 20.5f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        events.CancelEvent(EVENT_TAKEOFF);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -4470.68f, -4270.00f, 417.74f);
                        events.CancelEvent(EVENT_MOVE_AWAY);
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
        return new npc_th_lirastrasza_unchainedAI(creature);
    }
};

class npc_th_twilight_skyterror : public CreatureScript
{
public:
    npc_th_twilight_skyterror() : CreatureScript("npc_th_twilight_skyterror")
    {
    }

    enum questId
    {
        QUEST_COUP_DE_GRACE_A   = 27702,
        QUEST_COUP_DE_GRACE_H   = 27703
    };

    enum spellId
    {
        SPELL_COUP_DE_GRACE     = 86485
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_COUP_DE_GRACE_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_COUP_DE_GRACE_H) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(creature, SPELL_COUP_DE_GRACE);
            creature->Kill(creature, false);
            player->KilledMonsterCredit(creature->GetEntry());
            creature->DespawnOrUnsummon(1);
            return true;
        }
        return true;
    }
};

class npc_th_goldmine_cart : public CreatureScript
{
public:
    npc_th_goldmine_cart() : CreatureScript("npc_th_goldmine_cart")
    {
    }

    enum actionId
    {
        ACTION_WP_START = 1
    };

    enum spellId
    {
        SPELL_MINE_CART_VISUAL  = 87955
    };

    enum eventId
    {
        EVENT_RIDE_INITIATE     = 1
    };

    enum npcId
    {
        NPC_INITIATE    = 46513
    };

    enum pointId
    {
        POINT_FIRST_JUMP    = 18
    };

    struct npc_th_goldmine_cartAI : public npc_escortAI
    {
        npc_th_goldmine_cartAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
            owner->AddAura(60191, owner);
            owner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->CastSpell(me, SPELL_MINE_CART_VISUAL, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            wpInProgress = false;
            events.ScheduleEvent(EVENT_RIDE_INITIATE, 1000);
            if (owner->GetTypeId() == TYPEID_PLAYER)
                owner->PlayDirectSound(23546, owner->ToPlayer());
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
                case 1:
                {
                    if (Unit* initiate = me->GetVehicleKit()->GetPassenger(1))
                        initiate->ToCreature()->AI()->Talk(0);
                    if (Unit* invoker = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (invoker->GetTypeId() == TYPEID_PLAYER)
                            invoker->PlayDirectSound(11743, invoker->ToPlayer());
                    }
                    break;
                }
                case 2:
                {
                    if (Unit* initiate = me->GetVehicleKit()->GetPassenger(1))
                        initiate->ToCreature()->AI()->Talk(1);
                    me->SetWalk(false);
                    break;
                }
                case 16:
                {
                    if (Unit* initiate = me->GetVehicleKit()->GetPassenger(1))
                        initiate->ToCreature()->AI()->Talk(2);
                    break;
                }
                case 17:
                {
                    me->GetMotionMaster()->MoveJump(-5446.46f, -4504.80f, 331.78f, 25.0f, 25.0f, POINT_FIRST_JUMP);
                    break;
                }
                case 20:
                {
                    if (Unit* initiate = me->GetVehicleKit()->GetPassenger(1))
                    {
                        initiate->ToCreature()->AI()->Talk(3);
                        initiate->ExitVehicle();
                        initiate->GetMotionMaster()->MoveJump(initiate->GetPositionX(), initiate->GetPositionY(), initiate->GetPositionZ(), 10.0f, 10.0f, 1);
                    }

                    if (Unit* player = me->GetVehicleKit()->GetPassenger(0))
                    {
                        player->ToPlayer()->KilledMonsterCredit(46459);
                        player->RemoveAurasDueToSpell(60191);
                        player->ExitVehicle();
                        player->GetMotionMaster()->MoveJump(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 10.0f, 10.0f, 1);
                        player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                    }

                    me->DespawnOrUnsummon(15000);
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
                    me->SetWalk(true);
                    Start(false, false, NULL, NULL, false, true);
                    me->SetSpeed(MOVE_FLIGHT, 1.75f, true);
                    me->SetSpeed(MOVE_RUN, 1.75f, true);
                    SetDespawnAtEnd(true);
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
                    case EVENT_RIDE_INITIATE:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            // For Initiate
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_INITIATE, 100.0f);
                            if (!creatures.empty())
                            {
                                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                    {
                                        (*iter)->EnterVehicle(me, 1);
                                        (*iter)->AddAura(60191, (*iter));
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_RIDE_INITIATE);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool wpInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_goldmine_cartAI(creature);
    }
};

class npc_th_twilight_rune_of_earth : public CreatureScript
{
public:
    npc_th_twilight_rune_of_earth() : CreatureScript("npc_th_twilight_rune_of_earth")
    {
    }

    enum questId
    {
        QUEST_RUNE_RUINATION    = 27744
    };

    enum npcId
    {
        NPC_INITIATE    = 46513
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_RUNE_RUINATION)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_INITIATE, 70.0f);
            if (!creatures.empty())
            {
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                    {
                        (*iter)->ToCreature()->AI()->TalkWithDelay(1500, 4);
                        (*iter)->ToCreature()->AI()->TalkWithDelay(7500, 5);
                    }
                }
            }
            creature->CastSpell(creature, 86957, true);
            player->KilledMonsterCredit(creature->GetEntry());
        }
        return true;
    }
};

class go_th_twilight_rune_of_water : public GameObjectScript
{
public:
    go_th_twilight_rune_of_water() : GameObjectScript("go_th_twilight_rune_of_water")
    {
    }

    enum questId
    {
        QUEST_RUNE_RUINATION    = 27744
    };

    enum npcId
    {
        NPC_INITIATE    = 46513
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_RUNE_RUINATION) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_INITIATE, 70.0f);
            if (!creatures.empty())
            {
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                        (*iter)->ToCreature()->AI()->TalkWithDelay(1500, 6);
                }
            }
            go->CastSpell(player, 86955);
        }
        return false;
    }
};

class go_th_twilight_rune_of_air : public GameObjectScript
{
public:
    go_th_twilight_rune_of_air() : GameObjectScript("go_th_twilight_rune_of_air")
    {
    }

    enum questId
    {
        QUEST_RUNE_RUINATION = 27744
    };

    enum npcId
    {
        NPC_INITIATE = 46513
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_RUNE_RUINATION) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_INITIATE, 70.0f);
            if (!creatures.empty())
            {
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                        (*iter)->ToCreature()->AI()->TalkWithDelay(1500, 7);
                }
            }
            go->CastSpell(player, 86946);
        }
        return false;
    }
};

class go_th_twilight_rune_of_fire : public GameObjectScript
{
public:
    go_th_twilight_rune_of_fire() : GameObjectScript("go_th_twilight_rune_of_fire")
    {
    }

    enum questId
    {
        QUEST_RUNE_RUINATION = 27744
    };

    enum npcId
    {
        NPC_INITIATE = 46513
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_RUNE_RUINATION) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_INITIATE, 70.0f);
            if (!creatures.empty())
            {
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                        (*iter)->ToCreature()->AI()->TalkWithDelay(1500, 8);
                }
            }
            go->CastSpell(player, 86945);
        }
        return false;
    }
};

class npc_th_magmatooth : public CreatureScript
{
public:
    npc_th_magmatooth() : CreatureScript("npc_th_magmatooth")
    {
    }

    struct npc_th_magmatoothAI : public ScriptedAI
    {
        npc_th_magmatoothAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_INITIATE   = 1,
            EVENT_FLAME_SHOCK,
            EVENT_MAGMA_WAVE,
            EVENT_RUSH_OF_FLAME,
            EVENT_ENTER_COMBAT,
            EVENT_ENRAGE_MAGMATOOTH
        };

        enum spellId
        {
            SPELL_FLAME_SHOCK           = 13729,
            SPELL_MAGMA_WAVE            = 83018,
            SPELL_RUSH_OF_FLAME         = 75024,
            SPELL_RUSH_OF_FLAME_CHARGE  = 75025,
            SPELL_ROCKET_BELT           = 66306
        };

        enum npcId
        {
            NPC_INITIATE    = 46513
        };

        enum questId
        {
            QUEST_A_FIERY_REUNION   = 27745
        };

        void InitializeAI()
        {
            initiateFound = false;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            events.ScheduleEvent(EVENT_SEARCH_FOR_INITIATE, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }

        void EnterCombat(Unit* who)
        {
            initiateFound = true;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            events.CancelEvent(EVENT_SEARCH_FOR_INITIATE);
            events.ScheduleEvent(EVENT_RUSH_OF_FLAME, 1);
            events.ScheduleEvent(EVENT_FLAME_SHOCK, urand(2000, 3000));
            events.ScheduleEvent(EVENT_MAGMA_WAVE, urand(6000, 10000));
            Talk(1);

            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, NPC_INITIATE, 50.0f);
                if (!creatures.empty())
                {
                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() && (*iter)->ToTempSummon()->GetSummoner() == who)
                        {
                            if (who->ToPlayer()->GetQuestStatus(QUEST_A_FIERY_REUNION) == QUEST_STATUS_INCOMPLETE)
                            {
                                (*iter)->ToCreature()->AI()->TalkWithDelay(5000, 10);
                                (*iter)->ToCreature()->AI()->TalkWithDelay(8000, 11);
                                (*iter)->CastWithDelay(12000, me, SPELL_ROCKET_BELT, true);
                                (*iter)->SetFacingToObject(me);
                                events.ScheduleEvent(EVENT_ENRAGE_MAGMATOOTH, 20000);
                            }
                        }
                    }
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(4);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            initiateFound = false;
            me->GetMotionMaster()->MoveTargetedHome();
            events.ScheduleEvent(EVENT_SEARCH_FOR_INITIATE, 5000);
            events.Reset();
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
                    case EVENT_SEARCH_FOR_INITIATE:
                    {
                        if (initiateFound == true)
                        {
                            events.CancelEvent(EVENT_SEARCH_FOR_INITIATE);
                            break;
                        }

                        // Enable Initiate
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_INITIATE, 25.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() && (*iter)->ToTempSummon()->GetSummoner()->GetTypeId() == TYPEID_PLAYER)
                                {
                                    if ((*iter)->ToTempSummon()->GetSummoner()->ToPlayer()->GetQuestStatus(QUEST_A_FIERY_REUNION) == QUEST_STATUS_INCOMPLETE)
                                    {
                                        initiateFound = true;
                                        (*iter)->GetMotionMaster()->Clear();
                                        (*iter)->GetMotionMaster()->MovementExpired(false);
                                        (*iter)->GetMotionMaster()->MovePoint(1, -5115.21f, -4348.61f, 294.91f, true);
                                        (*iter)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_PACIFIED | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
                                        (*iter)->SetReactState(REACT_DEFENSIVE);
                                        (*iter)->ToCreature()->AI()->Talk(9);
                                        TalkWithDelay(5000, 0);
                                        events.ScheduleEvent(EVENT_ENTER_COMBAT, 10000);
                                    }
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_SEARCH_FOR_INITIATE, 2000);
                        break;
                    }
                    case EVENT_RUSH_OF_FLAME:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                        {
                            me->CastWithDelay(500, me, SPELL_RUSH_OF_FLAME, true);
                            DoCast(victim, SPELL_RUSH_OF_FLAME_CHARGE, true);
                        }
                        events.CancelEvent(EVENT_RUSH_OF_FLAME);
                        break;
                    }
                    case EVENT_FLAME_SHOCK:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_FLAME_SHOCK);
                        events.ScheduleEvent(EVENT_FLAME_SHOCK, urand(3000, 4500));
                        break;
                    }
                    case EVENT_MAGMA_WAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_MAGMA_WAVE);
                        events.ScheduleEvent(EVENT_MAGMA_WAVE, urand(6000, 12000));
                        break;
                    }
                    case EVENT_ENTER_COMBAT:
                    {
                        if (Player* player = me->FindNearestPlayer(60.0f, true))
                        {
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            AttackStart(player);
                        }
                        events.CancelEvent(EVENT_ENTER_COMBAT);
                        break;
                    }
                    case EVENT_ENRAGE_MAGMATOOTH:
                    {
                        TalkWithDelay(500, 2);
                        TalkWithDelay(6500, 3);
                        events.CancelEvent(EVENT_ENRAGE_MAGMATOOTH);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        protected:
            bool initiateFound;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_magmatoothAI(creature);
    }
};

class spell_th_fire_portal_controller : public SpellScriptLoader
{
public:
    spell_th_fire_portal_controller() : SpellScriptLoader("spell_th_fire_portal_controller")
    {
    }

    class spell_th_fire_portal_controller_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_fire_portal_controller_SpellScript);

        enum Id
        {
            NPC_PORTAL_TRIGGER  = 38984,
            NPC_INITIATE        = 46513
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* portalTrigger = caster->FindNearestCreature(NPC_PORTAL_TRIGGER, 4.0f, true))
                    return SPELL_CAST_OK;
            }
            return SPELL_FAILED_NOT_HERE;
        }

        void DespawnInitiate()
        {
            if (Unit* caster = GetCaster())
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, caster, NPC_INITIATE, 1000.0f);
                if (!creatures.empty())
                {
                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() && (*iter)->ToTempSummon()->GetSummoner() == caster)
                            (*iter)->ToCreature()->DespawnOrUnsummon(1);
                    }
                }
                caster->RemoveAurasDueToSpell(86739);
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_fire_portal_controller_SpellScript::CheckCast);
            AfterCast += SpellCastFn(spell_th_fire_portal_controller_SpellScript::DespawnInitiate);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_fire_portal_controller_SpellScript();
    }
};

/*# THE CRUCIBLE OF CARNAGE - START #*/
class npc_th_gurgthock : public CreatureScript
{
public:
    npc_th_gurgthock() : CreatureScript("npc_th_gurgthock")
    {
    }

    enum actionId
    {
        ACTION_BLOODEYE     = 1,
        ACTION_DRAGONMAW,
        ACTION_WILDHAMMER,
        ACTION_CALDER,
        ACTION_EARL,
        ACTION_TERROR
    };

    enum questId
    {
        QUEST_THE_BLOODEYE_BRUISER          = 27863,
        QUEST_THE_DEADLY_DRAGONMAW          = 27864,
        QUEST_THE_WAYWARD_WILDHAMMER        = 27865,
        QUEST_CALDER_CREATION               = 27866,
        QUEST_THE_EARL_OF_EVISCERATION      = 27867,
        QUEST_THE_TWILIGHT_TERROR           = 27868
    };

    enum eventId
    {
        EVENT_BLOODEYE      = 1,
        EVENT_DRAGONMAW,
        EVENT_WILDHAMMER,
        EVENT_CALDER,
        EVENT_EARL,
        EVENT_TERROR
    };

    enum npcId
    {
        NPC_HURP_DERP   = 46944,
        NPC_DRAKEFLAYER = 46945,
        NPC_GLOOMWING   = 47476,
        NPC_KNEECAPPER  = 46946,
        NPC_NOBBLY      = 47482,
        NPC_CADAVER     = 46947,
        NPC_CALDER      = 52266,
        NPC_TULVAN      = 46948,
        NPC_HARNESS     = 47521,
        NPC_HORSE       = 47522,
        NPC_STAGECOACH  = 47523,
        NPC_EMBERSCAR   = 46949
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_THE_BLOODEYE_BRUISER:
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(creature, 1000.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
                creature->VisitNearbyObject(1000.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_HURP_DERP:
                            case NPC_DRAKEFLAYER:
                            case NPC_GLOOMWING:
                            case NPC_KNEECAPPER:
                            case NPC_NOBBLY:
                            case NPC_CADAVER:
                            case NPC_CALDER:
                            case NPC_TULVAN:
                            case NPC_HARNESS:
                            case NPC_STAGECOACH:
                            case NPC_HORSE:
                            case NPC_EMBERSCAR:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->TalkWithDelay(8000, 1, player->GetGUID());
                creature->AI()->TalkWithDelay(20000, 2, player->GetGUID());
                creature->AI()->DoAction(ACTION_BLOODEYE);
                break;
            }
            case QUEST_THE_DEADLY_DRAGONMAW:
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(creature, 1000.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
                creature->VisitNearbyObject(1000.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_HURP_DERP:
                            case NPC_DRAKEFLAYER:
                            case NPC_GLOOMWING:
                            case NPC_KNEECAPPER:
                            case NPC_NOBBLY:
                            case NPC_CADAVER:
                            case NPC_CALDER:
                            case NPC_TULVAN:
                            case NPC_HARNESS:
                            case NPC_STAGECOACH:
                            case NPC_HORSE:
                            case NPC_EMBERSCAR:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->TalkWithDelay(8000, 4, player->GetGUID());
                creature->AI()->DoAction(ACTION_DRAGONMAW);
                break;
            }
            case QUEST_THE_WAYWARD_WILDHAMMER:
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(creature, 1000.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
                creature->VisitNearbyObject(1000.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_HURP_DERP:
                            case NPC_DRAKEFLAYER:
                            case NPC_GLOOMWING:
                            case NPC_KNEECAPPER:
                            case NPC_NOBBLY:
                            case NPC_CADAVER:
                            case NPC_CALDER:
                            case NPC_TULVAN:
                            case NPC_HARNESS:
                            case NPC_STAGECOACH:
                            case NPC_HORSE:
                            case NPC_EMBERSCAR:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->TalkWithDelay(8000, 6, player->GetGUID());
                creature->AI()->DoAction(ACTION_WILDHAMMER);
                break;
            }
            case QUEST_CALDER_CREATION:
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(creature, 1000.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
                creature->VisitNearbyObject(1000.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_HURP_DERP:
                            case NPC_DRAKEFLAYER:
                            case NPC_GLOOMWING:
                            case NPC_KNEECAPPER:
                            case NPC_NOBBLY:
                            case NPC_CADAVER:
                            case NPC_CALDER:
                            case NPC_TULVAN:
                            case NPC_HARNESS:
                            case NPC_STAGECOACH:
                            case NPC_HORSE:
                            case NPC_EMBERSCAR:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->TalkWithDelay(8000, 7, player->GetGUID());
                creature->AI()->TalkWithDelay(16000, 8, player->GetGUID());
                creature->AI()->DoAction(ACTION_CALDER);
                break;
            }
            case QUEST_THE_EARL_OF_EVISCERATION:
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(creature, 1000.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
                creature->VisitNearbyObject(1000.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_HURP_DERP:
                            case NPC_DRAKEFLAYER:
                            case NPC_GLOOMWING:
                            case NPC_KNEECAPPER:
                            case NPC_NOBBLY:
                            case NPC_CADAVER:
                            case NPC_CALDER:
                            case NPC_TULVAN:
                            case NPC_HARNESS:
                            case NPC_STAGECOACH:
                            case NPC_HORSE:
                            case NPC_EMBERSCAR:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->TalkWithDelay(8000, 11, player->GetGUID());
                creature->AI()->DoAction(ACTION_EARL);
                break;
            }
            case QUEST_THE_TWILIGHT_TERROR:
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(creature, 1000.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
                creature->VisitNearbyObject(1000.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_HURP_DERP:
                            case NPC_DRAKEFLAYER:
                            case NPC_GLOOMWING:
                            case NPC_KNEECAPPER:
                            case NPC_NOBBLY:
                            case NPC_CADAVER:
                            case NPC_CALDER:
                            case NPC_TULVAN:
                            case NPC_HARNESS:
                            case NPC_STAGECOACH:
                            case NPC_HORSE:
                            case NPC_EMBERSCAR:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->TalkWithDelay(8000, 14, player->GetGUID());
                creature->AI()->TalkWithDelay(16000, 15, player->GetGUID());
                creature->AI()->DoAction(ACTION_TERROR);
                break;
            }
            default:
                break;
        }

        return false;
    }

    struct npc_th_gurgthockAI : public ScriptedAI
    {
        npc_th_gurgthockAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_BLOODEYE:
                {
                    events.ScheduleEvent(EVENT_BLOODEYE, 25000);
                    break;
                }
                case ACTION_DRAGONMAW:
                {
                    events.ScheduleEvent(EVENT_DRAGONMAW, 18000);
                    break;
                }
                case ACTION_WILDHAMMER:
                {
                    events.ScheduleEvent(EVENT_WILDHAMMER, 18000);
                    break;
                }
                case ACTION_CALDER:
                {
                    events.ScheduleEvent(EVENT_CALDER, 22500);
                    break;
                }
                case ACTION_EARL:
                {
                    events.ScheduleEvent(EVENT_EARL, 18000);
                    break;
                }
                case ACTION_TERROR:
                {
                    events.ScheduleEvent(EVENT_TERROR, 22500);
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
                    case EVENT_BLOODEYE:
                    {
                        me->SummonCreature(NPC_HURP_DERP, -4128.78f, -5195.94f, -9.64f, 2.45f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_BLOODEYE);
                        break;
                    }
                    case EVENT_DRAGONMAW:
                    {
                        me->SummonCreature(NPC_DRAKEFLAYER, -4139.75f, -5138.85f, 37.09f, 3.37f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        me->SummonCreature(NPC_GLOOMWING, -4176.74f, -5147.00f, 27.71f, 0.09f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_DRAGONMAW);
                        break;
                    }
                    case EVENT_WILDHAMMER:
                    {
                        me->SummonCreature(NPC_KNEECAPPER, -4139.75f, -5138.85f, 37.09f, 3.37f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        me->SummonCreature(NPC_NOBBLY, -4176.74f, -5147.00f, 27.71f, 0.09f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_WILDHAMMER);
                        break;
                    }
                    case EVENT_CALDER:
                    {
                        me->SummonCreature(NPC_CADAVER, -4166.27f, -5096.18f, -10.84f, 3.85f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        me->SummonCreature(NPC_CALDER, -4164.06f, -5126.35f, 6.18f, 3.72f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_CALDER);
                        break;
                    }
                    case EVENT_EARL:
                    {
                        me->SummonCreature(NPC_HARNESS, -4128.78f, -5195.94f, -9.64f, 2.45f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_EARL);
                        break;
                    }
                    case EVENT_TERROR:
                    {
                        me->SummonCreature(NPC_EMBERSCAR, -4132.62f, -5190.41f, -9.45f, 2.33f, TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_EARL);
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
        return new npc_th_gurgthockAI(creature);
    }
};

class npc_th_hurp_derp : public CreatureScript
{
public:
    npc_th_hurp_derp() : CreatureScript("npc_th_hurp_derp")
    {
    }

    enum actionId
    {
        ACTION_FAIL     = 1,
        ACTION_SUCCESS
    };

    enum pointId
    {
        POINT_CENTER    = 1
    };

    enum eventId
    {
        EVENT_INTIMIDATING_ROAR     = 1,
        EVENT_OVERHEAD_SMASH,
        EVENT_WHIRLWIND,
        EVENT_CHECK_EVADE
    };

    enum spellId
    {
        SPELL_INTIMIDATING_ROAR     = 91933,
        SPELL_OVERHEAD_SMASH        = 88482,
        SPELL_WHIRLWIND             = 83016
    };

    enum npcId
    {
        NPC_GURGTHOCK   = 46935
    };

    struct npc_th_hurp_derpAI : public ScriptedAI
    {
        npc_th_hurp_derpAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FAIL:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_SUCCESS:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                    {
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        gurgthock->AI()->TalkWithDelay(1000, 3);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetWalk(false);
            me->GetMotionMaster()->MovePoint(POINT_CENTER, -4182.39f, -5148.45f, -7.73f, false);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_CHECK_EVADE, 20000);
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 8 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 8 + me->getLevel())));
        }

        void JustDied(Unit* /*killer*/)
        {
            DoAction(ACTION_SUCCESS);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(5000);
            events.Reset();
            DoAction(ACTION_FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_WHIRLWIND, urand(4000, 6000));
            events.ScheduleEvent(EVENT_OVERHEAD_SMASH, 17500);
            events.ScheduleEvent(EVENT_INTIMIDATING_ROAR, 15000);
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
                    case EVENT_WHIRLWIND:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_WHIRLWIND);
                        events.RescheduleEvent(EVENT_WHIRLWIND, urand(15000, 24000));
                        break;
                    }
                    case EVENT_OVERHEAD_SMASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_OVERHEAD_SMASH);
                        events.RescheduleEvent(EVENT_OVERHEAD_SMASH, 37500);
                        break;
                    }
                    case EVENT_INTIMIDATING_ROAR:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_INTIMIDATING_ROAR);
                        events.RescheduleEvent(EVENT_INTIMIDATING_ROAR, 35000);
                        break;
                    }
                    case EVENT_CHECK_EVADE:
                    {
                        if (!me->isInCombat())
                        {
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_EVADE, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            // Safety distance check to prevent exit arena
            if (me->GetDistance2d(-4184.26f, -5152.62f) > 90)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_hurp_derpAI(creature);
    }
};

class npc_th_torg_drakeflayer : public CreatureScript
{
public:
    npc_th_torg_drakeflayer() : CreatureScript("npc_th_torg_drakeflayer")
    {
    }

    enum actionId
    {
        ACTION_FAIL     = 1,
        ACTION_SUCCESS
    };

    enum pointId
    {
        POINT_CENTER    = 1
    };

    enum eventId
    {
        EVENT_CHARGE        = 1,
        EVENT_UPPERCUT,
        EVENT_HP_40,
        EVENT_CHECK_EVADE
    };

    enum spellId
    {
        SPELL_CHARGE    = 88288,
        SPELL_UPPERCUT  = 80182
    };

    enum npcId
    {
        NPC_GURGTHOCK   = 46935,
        NPC_GLOOMWING   = 47476
    };

    struct npc_th_torg_drakeflayerAI : public ScriptedAI
    {
        npc_th_torg_drakeflayerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FAIL:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_SUCCESS:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                    {
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        gurgthock->AI()->TalkWithDelay(1000, 5);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetWalk(false);
            me->GetMotionMaster()->MoveJump(-4174.35f, -5142.40f, -7.73f, 30.0f, 30.0f, POINT_CENTER);
            TalkWithDelay(3000, 0);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_CHECK_EVADE, 20000);
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 9 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 9 + me->getLevel())));
        }

        void JustDied(Unit* /*killer*/)
        {
            DoAction(ACTION_SUCCESS);
            if (Creature* gloomwing = me->FindNearestCreature(NPC_GLOOMWING, 1000.0f, true))
                gloomwing->DespawnOrUnsummon(1);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(5000);
            if (Creature* gloomwing = me->FindNearestCreature(NPC_GLOOMWING, 1000.0f, true))
                gloomwing->DespawnOrUnsummon(1);
            events.Reset();
            DoAction(ACTION_FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_UPPERCUT, urand(15000, 30000));
            events.ScheduleEvent(EVENT_CHARGE, 1);
            events.ScheduleEvent(EVENT_HP_40, 2000);
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
                    case EVENT_CHARGE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 100.0f, true))
                        {
                            me->getThreatManager().clearReferences();
                            DoCast(target, SPELL_CHARGE);
                            me->AddThreat(target, 100);
                        }
                        events.RescheduleEvent(EVENT_CHARGE, urand(15000, 30000));
                        break;
                    }
                    case EVENT_UPPERCUT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_UPPERCUT);
                        events.RescheduleEvent(EVENT_CHARGE, urand(18000, 25000));
                        break;
                    }
                    case EVENT_HP_40:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.40f)
                        {
                            Talk(1);
                            events.CancelEvent(EVENT_HP_40);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_40, 2000);
                        break;
                    }
                    case EVENT_CHECK_EVADE:
                    {
                        if (!me->isInCombat())
                        {
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_EVADE, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            // Safety distance check to prevent exit arena
            if (me->GetDistance2d(-4184.26f, -5152.62f) > 90)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_torg_drakeflayerAI(creature);
    }
};

class npc_th_sully_kneecapper : public CreatureScript
{
public:
    npc_th_sully_kneecapper() : CreatureScript("npc_th_sully_kneecapper")
    {
    }

    enum actionId
    {
        ACTION_FAIL     = 1,
        ACTION_SUCCESS
    };

    enum pointId
    {
        POINT_CENTER    = 1
    };

    enum eventId
    {
        EVENT_CHARGE        = 1,
        EVENT_UPPERCUT,
        EVENT_HP_40,
        EVENT_CHECK_EVADE
    };

    enum spellId
    {
        SPELL_CHARGE    = 88288,
        SPELL_UPPERCUT  = 80182
    };

    enum npcId
    {
        NPC_GURGTHOCK   = 46935,
        NPC_NOBBLY      = 47482
    };

    struct npc_th_sully_kneecapperAI : public ScriptedAI
    {
        npc_th_sully_kneecapperAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FAIL:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_SUCCESS:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                    {
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        gurgthock->AI()->TalkWithDelay(1000, 5);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetWalk(false);
            me->GetMotionMaster()->MoveJump(-4174.35f, -5142.40f, -7.73f, 30.0f, 30.0f, POINT_CENTER);
            TalkWithDelay(3000, 0);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_CHECK_EVADE, 20000);
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 9 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 9 + me->getLevel())));
        }

        void JustDied(Unit* /*killer*/)
        {
            DoAction(ACTION_SUCCESS);
            if (Creature* nobbly = me->FindNearestCreature(NPC_NOBBLY, 1000.0f, true))
                nobbly->DespawnOrUnsummon(1);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(5000);
            if (Creature* nobbly = me->FindNearestCreature(NPC_NOBBLY, 1000.0f, true))
                nobbly->DespawnOrUnsummon(1);
            events.Reset();
            DoAction(ACTION_FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_UPPERCUT, urand(15000, 30000));
            events.ScheduleEvent(EVENT_CHARGE, 1);
            events.ScheduleEvent(EVENT_HP_40, 2000);
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
                    case EVENT_CHARGE:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 100.0f, true))
                        {
                            me->getThreatManager().clearReferences();
                            DoCast(target, SPELL_CHARGE);
                            me->AddThreat(target, 100);
                        }
                        events.RescheduleEvent(EVENT_CHARGE, urand(15000, 30000));
                        break;
                    }
                    case EVENT_UPPERCUT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_UPPERCUT);
                        events.RescheduleEvent(EVENT_CHARGE, urand(18000, 25000));
                        break;
                    }
                    case EVENT_HP_40:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.40f)
                        {
                            Talk(1);
                            events.CancelEvent(EVENT_HP_40);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_40, 2000);
                        break;
                    }
                    case EVENT_CHECK_EVADE:
                    {
                        if (!me->isInCombat())
                        {
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_EVADE, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            // Safety distance check to prevent exit arena
            if (me->GetDistance2d(-4184.26f, -5152.62f) > 90)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_sully_kneecapperAI(creature);
    }
};

class npc_th_cadaver_collage : public CreatureScript
{
public:
    npc_th_cadaver_collage() : CreatureScript("npc_th_cadaver_collage")
    {
    }

    enum actionId
    {
        ACTION_FAIL     = 1,
        ACTION_SUCCESS
    };

    enum pointId
    {
        POINT_CENTER    = 1,
        POINT_UP
    };

    enum eventId
    {
        EVENT_ENTER_COMBAT      = 1,
        EVENT_REPULSIVE_KICK,
        EVENT_BELCH,
        EVENT_PLAGUE_EXPLOSION,
        EVENT_POISON_CLOUD,
        EVENT_INHALE,
        EVENT_FULLY,
        EVENT_SET_DROWNED,
        EVENT_EXPLODE,
        EVENT_DIE_AND_DESPAWN,
        EVENT_HP_40,
        EVENT_CHECK_EVADE
    };

    enum spellId
    {
        SPELL_BELCH             = 88607,
        SPELL_INHALE            = 88615,
        SPELL_PLAGUE_EXPLOSION  = 88614,
        SPELL_POISON_CLOUD      = 90447,
        SPELL_REPULSIVE_KICK    = 88605,
        SPELL_FLOATING_DEATH    = 88613,
        SPELL_CORPSE_EXPLOSION  = 73163
    };

    enum npcId
    {
        NPC_GURGTHOCK       = 46935,
        NPC_CALDER          = 52266,
        NPC_POISON_CLOUDS   = 48591
    };

    struct npc_th_cadaver_collageAI : public ScriptedAI
    {
        npc_th_cadaver_collageAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FAIL:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_SUCCESS:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                    {
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        gurgthock->AI()->TalkWithDelay(1000, 5);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetWalk(false);
            me->GetMotionMaster()->MovePoint(POINT_CENTER, -4190.28f, -5144.91f, -7.73f);
            TalkWithDelay(12000, 0);
            events.ScheduleEvent(EVENT_ENTER_COMBAT, 17000);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_CHECK_EVADE, 20000);
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 10 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 10 + me->getLevel())));
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(5000);
            if (Creature* calder = me->FindNearestCreature(NPC_CALDER, 1000.0f, true))
                calder->DespawnOrUnsummon(1);
            events.Reset();
            DoAction(ACTION_FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_REPULSIVE_KICK, urand(20000, 30000));
            events.ScheduleEvent(EVENT_BELCH, urand(8000, 12500));
            events.ScheduleEvent(EVENT_POISON_CLOUD, 15000);
            events.ScheduleEvent(EVENT_HP_40, 2000);
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
                    case EVENT_ENTER_COMBAT:
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        events.CancelEvent(EVENT_ENTER_COMBAT);
                        break;
                    }
                    case EVENT_REPULSIVE_KICK:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        {
                            DoCast(target, SPELL_REPULSIVE_KICK);
                            Talk(1);
                        }
                        events.RescheduleEvent(EVENT_REPULSIVE_KICK, urand(20000, 25000));
                        break;
                    }
                    case EVENT_POISON_CLOUD:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_POISON_CLOUD);
                        events.RescheduleEvent(EVENT_POISON_CLOUD, 12000);
                        break;
                    }
                    case EVENT_BELCH:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_BELCH);
                        events.RescheduleEvent(EVENT_BELCH, urand(8000, 12000));
                        break;
                    }
                    case EVENT_HP_40:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.40f)
                        {
                            if (Creature* calder = me->FindNearestCreature(NPC_CALDER, 1000.0f, true))
                            {
                                calder->AI()->Talk(1);
                                events.ScheduleEvent(EVENT_INHALE, 6000);
                            }
                            events.CancelEvent(EVENT_CHECK_EVADE);
                            events.CancelEvent(EVENT_HP_40);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_40, 2000);
                        break;
                    }
                    case EVENT_INHALE:
                    {
                        Talk(2);
                        me->CombatStop();
                        me->AttackStop();
                        me->CastStop();
                        me->SetReactState(REACT_PASSIVE);
                        DoCast(SPELL_INHALE);
                        events.ScheduleEvent(EVENT_FULLY, 5000);
                        // Cleanup events
                        events.CancelEvent(EVENT_INHALE);
                        events.CancelEvent(EVENT_BELCH);
                        events.CancelEvent(EVENT_REPULSIVE_KICK);
                        events.CancelEvent(EVENT_POISON_CLOUD);
                        events.CancelEvent(EVENT_CHECK_EVADE);
                        break;
                    }
                    case EVENT_FULLY:
                    {
                        Talk(3);
                        if (Creature* calder = me->FindNearestCreature(NPC_CALDER, 1000.0f, true))
                        {
                            calder->AI()->TalkWithDelay(5000, 2);
                            calder->AI()->TalkWithDelay(18000, 3);
                            calder->AI()->TalkWithDelay(26000, 4);
                            calder->DespawnOrUnsummon(33000);
                        }
                        if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        {
                            gurgthock->AI()->TalkWithDelay(10000, 9);
                            gurgthock->AI()->TalkWithDelay(33000, 10);
                        }
                        me->HandleEmoteCommand(EMOTE_ONESHOT_DROWN);
                        me->DespawnCreaturesInArea(NPC_POISON_CLOUDS, 500.0f);
                        events.ScheduleEvent(EVENT_SET_DROWNED, 4000);
                        events.CancelEvent(EVENT_FULLY);
                        break;
                    }
                    case EVENT_SET_DROWNED:
                    {
                        me->SetSpeed(MOVE_WALK, 1.0f, true);
                        me->SetSpeed(MOVE_FLIGHT, 1.0f, true);
                        me->SetWalk(true);
                        me->SetDisableGravity(true);
                        me->HandleEmoteCommand(EMOTE_STATE_DROWNED);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 25, 1.0f, 1.0f, POINT_UP);
                        me->RemoveUnitMovementFlag(MOVEMENTFLAG_ASCENDING | MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_FLYING | MOVEMENTFLAG_HOVER | MOVEMENTFLAG_PITCH_UP | MOVEMENTFLAG_SPLINE_ELEVATION);
                        events.ScheduleEvent(EVENT_EXPLODE, 10000);
                        events.CancelEvent(EVENT_SET_DROWNED);
                        break;
                    }
                    case EVENT_EXPLODE:
                    {
                        DoCast(me, SPELL_PLAGUE_EXPLOSION, true);
                        DoCast(me, SPELL_CORPSE_EXPLOSION, true);
                        events.ScheduleEvent(EVENT_DIE_AND_DESPAWN, 1500);
                        events.CancelEvent(EVENT_EXPLODE);
                        break;
                    }
                    case EVENT_DIE_AND_DESPAWN:
                    {
                        if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                            gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        me->Kill(me, false);
                        me->DespawnOrUnsummon(1500);
                        events.CancelEvent(EVENT_DIE_AND_DESPAWN);
                        break;
                    }
                    case EVENT_CHECK_EVADE:
                    {
                        if (!me->isInCombat())
                        {
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_EVADE, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            // Safety distance check to prevent exit arena
            if (me->GetDistance2d(-4184.26f, -5152.62f) > 90)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_cadaver_collageAI(creature);
    }
};

class npc_th_geoffery_harness : public CreatureScript
{
public:
    npc_th_geoffery_harness() : CreatureScript("npc_th_geoffery_harness")
    {
    }

    enum pointId
    {
        POINT_CENTER    = 1
    };

    enum eventId
    {
        EVENT_TALK_GEOFFERY     = 1,
        EVENT_JUMP_GEOFFERY
    };

    enum npcId
    {
        NPC_TULVAN  = 46948
    };

    struct npc_th_geoffery_harnessAI : public ScriptedAI
    {
        npc_th_geoffery_harnessAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetWalk(true);
            me->GetMotionMaster()->MovePoint(POINT_CENTER, -4161.79f, -5169.60f, -7.73f, false);
            events.ScheduleEvent(EVENT_TALK_GEOFFERY, 5000);
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_GEOFFERY:
                    {
                        if (Creature* geoffery = me->FindNearestCreature(NPC_TULVAN, 80.0f, true))
                            geoffery->AI()->Talk(0);

                        events.ScheduleEvent(EVENT_JUMP_GEOFFERY, 3500);
                        events.CancelEvent(EVENT_TALK_GEOFFERY);
                        break;
                    }
                    case EVENT_JUMP_GEOFFERY:
                    {
                        if (Creature* geoffery = me->FindNearestCreature(NPC_TULVAN, 80.0f, true))
                        {
                            geoffery->ExitVehicle();
                            geoffery->GetMotionMaster()->Clear();
                            geoffery->GetMotionMaster()->MovementExpired(false);
                            geoffery->GetMotionMaster()->MoveJump(-4155.55f, -5161.90f, -7.75f, 8.0f, 8.0f, 10);
                            geoffery->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            geoffery->AI()->DoAction(3);
                        }
                        events.CancelEvent(EVENT_JUMP_GEOFFERY);
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
        return new npc_th_geoffery_harnessAI(creature);
    }
};

class npc_th_lord_geoffery_tulvan : public CreatureScript
{
public:
    npc_th_lord_geoffery_tulvan() : CreatureScript("npc_th_lord_geoffery_tulvan")
    {
    }

    enum actionId
    {
        ACTION_FAIL     = 1,
        ACTION_SUCCESS,
        ACTION_ENGAGE
    };

    enum pointId
    {
        POINT_CENTER    = 1,
        POINT_CARRIAGE
    };

    enum eventId
    {
        EVENT_ENGAGE            = 1,
        EVENT_DEATH_BY_PEASANT,
        EVENT_UNDYING_FRENZY,
        EVENT_UPPERCUT,
        EVENT_TRANSFORM,
        EVENT_TO_CARRIAGE,
        EVENT_RELEASE_HORSES,
        EVENT_TAKE_CARRIAGE,
        EVENT_RETURN_AGGRESSIVE,
        EVENT_LAUNCH_CARRIAGE,
        EVENT_HP_60,
        EVENT_CHECK_EVADE
    };

    enum spellId
    {
        SPELL_DEATH_BY_PEASANT  = 88619,
        SPELL_UNDYING_FRENZY    = 88616,
        SPELL_UPPERCUT          = 80182
    };

    enum npcId
    {
        NPC_GURGTHOCK   = 46935,
        NPC_HARNESS     = 47521,
        NPC_HORSE       = 47522,
        NPC_CARRIAGE    = 47523,
        NPC_WILDWOLF    = 47517
    };

    struct npc_th_lord_geoffery_tulvanAI : public ScriptedAI
    {
        npc_th_lord_geoffery_tulvanAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FAIL:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_SUCCESS:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                    {
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        gurgthock->AI()->TalkWithDelay(1000, 12);
                        gurgthock->AI()->TalkWithDelay(10000, 13);
                    }
                    break;
                }
                case ACTION_ENGAGE:
                {
                    events.ScheduleEvent(EVENT_ENGAGE, 2000);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            eventCarriageDone = false;
            me->SetHealth(me->GetMaxHealth());
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 10 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 10 + me->getLevel())));
        }

        void JustDied(Unit* /*killer*/)
        {
            DoAction(ACTION_SUCCESS);
            me->DespawnCreaturesInArea(NPC_CARRIAGE, 500.0f);
            me->DespawnCreaturesInArea(NPC_HARNESS, 500.0f);
            me->DespawnCreaturesInArea(NPC_HORSE, 500.0f);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(5000);
            me->DespawnCreaturesInArea(NPC_CARRIAGE, 500.0f);
            me->DespawnCreaturesInArea(NPC_HARNESS, 500.0f);
            me->DespawnCreaturesInArea(NPC_HORSE, 500.0f);
            eventCarriageDone = false;
            events.Reset();
            DoAction(ACTION_FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_HP_60, 2000);
            events.ScheduleEvent(EVENT_UPPERCUT, urand(8000, 12000));
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CARRIAGE:
                {
                    events.ScheduleEvent(EVENT_RELEASE_HORSES, 1000);
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
                    case EVENT_ENGAGE:
                    {
                        me->SetWalk(false);
                        if (Player* player = me->FindNearestPlayer(100.0f, true))
                            AttackStart(player);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        events.ScheduleEvent(EVENT_CHECK_EVADE, 20000);
                        break;
                    }
                    case EVENT_UPPERCUT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                            DoCast(target, SPELL_UPPERCUT);
                        events.RescheduleEvent(EVENT_UPPERCUT, urand(20000, 25000));
                        break;
                    }
                    case EVENT_UNDYING_FRENZY:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_UNDYING_FRENZY);
                        events.RescheduleEvent(EVENT_UNDYING_FRENZY, urand(8000, 12500));
                        break;
                    }
                    case EVENT_HP_60:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.60f && eventCarriageDone == false)
                        {
                            Talk(1);
                            events.ScheduleEvent(EVENT_TRANSFORM, 2500);
                            events.CancelEvent(EVENT_HP_60);
                            eventCarriageDone = true;
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_60, 2000);
                        break;
                    }
                    case EVENT_TRANSFORM:
                    {
                        DoCast(me, 81908, true);
                        me->SetDisplayId(34367);
                        me->SetName("Lord Geoffery Wildwolf");
                        if (Creature* carriage = me->FindNearestCreature(NPC_CARRIAGE, 500.0f, true))
                            carriage->ExitVehicle();
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        TalkWithDelay(2500, 2);
                        events.ScheduleEvent(EVENT_TO_CARRIAGE, 8000);
                        events.CancelEvent(EVENT_TRANSFORM);
                        break;
                    }
                    case EVENT_TO_CARRIAGE:
                    {
                        events.CancelEvent(EVENT_UPPERCUT);
                        TalkWithDelay(1000, 3);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->CastStop();
                        me->CombatStop();
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_CARRIAGE, -4161.00f, -5166.35f, -7.73f);
                        events.CancelEvent(EVENT_CHECK_EVADE);
                        events.CancelEvent(EVENT_TO_CARRIAGE);
                        break;
                    }
                    case EVENT_RELEASE_HORSES:
                    {
                        if (Creature* harness = me->FindNearestCreature(NPC_HARNESS, 200.0f, true))
                        {
                            harness->GetMotionMaster()->MovementExpired(false);
                            harness->SetWalk(false);
                            harness->GetMotionMaster()->MovePoint(50, -4232.78f, -5134.83f, -6.08f);
                            if (Unit* horseFirst = me->GetVehicleKit()->GetPassenger(0))
                            {
                                if (horseFirst->ToCreature())
                                    horseFirst->ToCreature()->DespawnOrUnsummon(8000);
                            }
                            if (Unit* horseSecond = me->GetVehicleKit()->GetPassenger(1))
                            {
                                if (horseSecond->ToCreature())
                                    horseSecond->ToCreature()->DespawnOrUnsummon(8000);
                            }
                            harness->DespawnOrUnsummon(8000);
                        }
                        DoCast(me, SPELL_DEATH_BY_PEASANT, true);
                        events.ScheduleEvent(EVENT_TAKE_CARRIAGE, 2500);
                        events.CancelEvent(EVENT_RELEASE_HORSES);
                        break;
                    }
                    case EVENT_TAKE_CARRIAGE:
                    {
                        if (Creature* carriage = me->FindNearestCreature(NPC_CARRIAGE, 200.0f, true))
                            carriage->EnterVehicle(me, 0);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        events.ScheduleEvent(EVENT_UNDYING_FRENZY, urand(5000, 7500));
                        events.ScheduleEvent(EVENT_RETURN_AGGRESSIVE, 3000);
                        events.CancelEvent(EVENT_TAKE_CARRIAGE);
                        break;
                    }
                    case EVENT_RETURN_AGGRESSIVE:
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Player* player = me->FindNearestPlayer(100.0f, true))
                            AttackStart(player);
                        events.ScheduleEvent(EVENT_LAUNCH_CARRIAGE, 8000);
                        events.CancelEvent(EVENT_RETURN_AGGRESSIVE);
                        break;
                    }
                    case EVENT_LAUNCH_CARRIAGE:
                    {
                        if (Creature* carriage = me->FindNearestCreature(NPC_CARRIAGE, 100.0f, true))
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                carriage->ExitVehicle();
                                carriage->GetMotionMaster()->MovementExpired(false);
                                carriage->GetMotionMaster()->MoveJump(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 8.5f, 8.5f, 100);
                                carriage->CastWithDelay(2000, carriage, 107629, true);
                                carriage->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                carriage->DespawnOrUnsummon(4000);
                            }
                        }
                        events.CancelEvent(EVENT_LAUNCH_CARRIAGE);
                        break;
                    }
                    case EVENT_CHECK_EVADE:
                    {
                        if (!me->isInCombat())
                        {
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_EVADE, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            // Safety distance check to prevent exit arena
            if (me->GetDistance2d(-4184.26f, -5152.62f) > 90)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }

        protected:
            bool eventCarriageDone;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_lord_geoffery_tulvanAI(creature);
    }
};

class npc_th_emberscar_the_devourer : public CreatureScript
{
public:
    npc_th_emberscar_the_devourer() : CreatureScript("npc_th_emberscar_the_devourer")
    {
    }

    enum actionId
    {
        ACTION_FAIL     = 1,
        ACTION_SUCCESS
    };

    enum pointId
    {
        POINT_CENTER    = 1
    };

    enum eventId
    {
        EVENT_ENGAGE            = 1,
        EVENT_FIREBALL,
        EVENT_MAGMATIC_FAULT,
        EVENT_ACTIVATE_POOLS,
        EVENT_AOE_FIREBALL,
        EVENT_HP_10,
        EVENT_CHECK_EVADE
    };

    enum spellId
    {
        SPELL_FIREBALL          = 90446,
        SPELL_MAGMATIC_FAULT    = 90333,
        SPELL_LAVA_RIVER        = 90373,
        SPELL_LAVA_POOL         = 90391,
        SPELL_VOLCANIC          = 90418,
        SPELL_AOE_FIREBALL      = 88515
    };

    enum npcId
    {
        NPC_GURGTHOCK   = 46935,
        NPC_LAVA_RIVER  = 48538,
        NPC_LAVA_POOL   = 48549
    };

    struct npc_th_emberscar_the_devourerAI : public ScriptedAI
    {
        npc_th_emberscar_the_devourerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DisablePools()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(200.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_LAVA_RIVER:
                        {
                            (*itr)->RemoveAurasDueToSpell(SPELL_LAVA_RIVER);
                            break;
                        }
                        case NPC_LAVA_POOL:
                        {
                            (*itr)->ToCreature()->AI()->DoAction(2);
                            (*itr)->ToCreature()->AI()->DoAction(4);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        void EnablePoolsFireball()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(200.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_LAVA_POOL:
                        {
                            (*itr)->ToCreature()->AI()->DoAction(3);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        void DisableBurningSkies()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(200.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->RemoveAurasDueToSpell(SPELL_VOLCANIC);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FAIL:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_SUCCESS:
                {
                    if (Creature* gurgthock = me->FindNearestCreature(NPC_GURGTHOCK, 1000.0f, true))
                    {
                        gurgthock->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        gurgthock->AI()->TalkWithDelay(1000, 3);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetWalk(false);
            me->GetMotionMaster()->MovePoint(POINT_CENTER, -4179.63f, -5146.09f, -7.73f, false);
            TalkWithDelay(9000, 0);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_ENGAGE, 17000);
            events.ScheduleEvent(EVENT_CHECK_EVADE, 30000);
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((me->getLevel() * 12 - me->getLevel())));
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((me->getLevel() * 12 + me->getLevel())));
        }

        void JustDied(Unit* /*killer*/)
        {
            DoAction(ACTION_SUCCESS);
            DisablePools();
            DisableBurningSkies();
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(5000);
            DisablePools();
            DisableBurningSkies();
            events.Reset();
            DoAction(ACTION_FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FIREBALL, urand(2000, 5000));
            events.ScheduleEvent(EVENT_ACTIVATE_POOLS, 20000);
            events.ScheduleEvent(EVENT_HP_10, 5000);
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
                    case EVENT_ENGAGE:
                    {
                        me->SetWalk(false);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Player* player = me->FindNearestPlayer(100.0f, true))
                            AttackStart(player);

                        events.ScheduleEvent(EVENT_CHECK_EVADE, 20000);
                        break;
                    }
                    case EVENT_ACTIVATE_POOLS:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(200.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_LAVA_RIVER:
                                    {
                                        (*itr)->AddAura(SPELL_LAVA_RIVER, (*itr));
                                        break;
                                    }
                                    case NPC_LAVA_POOL:
                                    {
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_ACTIVATE_POOLS);
                        break;
                    }
                    case EVENT_FIREBALL:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCastVictim(SPELL_FIREBALL);
                        events.RescheduleEvent(EVENT_FIREBALL, urand(4000, 7000));
                        break;
                    }
                    case EVENT_AOE_FIREBALL:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(me, SPELL_AOE_FIREBALL, true);
                        events.RescheduleEvent(EVENT_AOE_FIREBALL, 1500);
                        break;
                    }
                    case EVENT_HP_10:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.10f)
                        {
                            Talk(2);
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(100.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                                    (*itr)->AddAura(SPELL_VOLCANIC, (*itr));
                            }
                            EnablePoolsFireball();
                            events.ScheduleEvent(EVENT_AOE_FIREBALL, 2000);
                            events.CancelEvent(EVENT_FIREBALL);
                            events.CancelEvent(EVENT_HP_10);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_10, 2000);
                        break;
                    }
                    case EVENT_CHECK_EVADE:
                    {
                        if (!me->isInCombat())
                        {
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_EVADE, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            // Safety distance check to prevent exit arena
            if (me->GetDistance2d(-4184.26f, -5152.62f) > 150)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_emberscar_the_devourerAI(creature);
    }
};

class npc_th_lava_pool : public CreatureScript
{
public:
    npc_th_lava_pool() : CreatureScript("npc_th_lava_pool")
    {
    }

    enum actionId
    {
        ACTION_ENABLE_LAVA      = 1,
        ACTION_DISABLE_LAVA,
        ACTION_ENABLE_AOE,
        ACTION_DISABLE_AOE
    };

    enum spellId
    {
        SPELL_LAVA_POOL     = 93519,
        SPELL_AOE_FIREBALL  = 88515
    };

    enum eventId
    {
        EVENT_AOE_FIREBALL  = 1
    };

    struct npc_th_lava_poolAI : public ScriptedAI
    {
        npc_th_lava_poolAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
        }

        void EnterEvadeMode()
        {
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENABLE_LAVA:
                {
                    DoCast(SPELL_LAVA_POOL);
                    if (DynamicObject* lavaPool = me->GetDynObject(SPELL_LAVA_POOL))
                        lavaPool->SetObjectScale(1.4f);
                    break;
                }
                case ACTION_DISABLE_LAVA:
                {
                    if (DynamicObject* lavaPool = me->GetDynObject(SPELL_LAVA_POOL))
                        lavaPool->Remove();
                    break;
                }
                case ACTION_ENABLE_AOE:
                    events.ScheduleEvent(EVENT_AOE_FIREBALL, 1);
                    break;
                case ACTION_DISABLE_AOE:
                    events.CancelEvent(EVENT_AOE_FIREBALL);
                    break;
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
                    case EVENT_AOE_FIREBALL:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(me, SPELL_AOE_FIREBALL, true);
                        events.RescheduleEvent(EVENT_AOE_FIREBALL, 1000);
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
        return new npc_th_lava_poolAI(creature);
    }
};

class npc_th_the_hammer_of_twilight : public CreatureScript
{
public:
    npc_th_the_hammer_of_twilight() : CreatureScript("npc_th_the_hammer_of_twilight")
    {
    }

    enum questId
    {
        QUEST_SKULLCRUSHER_THE_MOUNTAIN_A   = 27787,
        QUEST_SKULLCRUSHER_THE_MOUNTAIN_H   = 27788
    };

    enum npcId
    {
        NPC_INITIATE = 46513
    };

    enum spellId
    {
        SPELL_SUMMON_CAMERA     = 87363,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SKULLCRUSHER_THE_MOUNTAIN_A || quest->GetQuestId() == QUEST_SKULLCRUSHER_THE_MOUNTAIN_H)
        {
            player->SetPhaseMask(8192, true);
            player->CastSpell(player, SPELL_SUMMON_CAMERA, true);
        }
        return true;
    }
};

class npc_th_skullcrusher_camera : public CreatureScript
{
public:
    npc_th_skullcrusher_camera() : CreatureScript("npc_th_skullcrusher_camera")
    {
    }

    struct npc_th_skullcrusher_cameraAI : public ScriptedAI
    {
        npc_th_skullcrusher_cameraAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER  = 1,
            EVENT_FOCUS_TARGET,
            EVENT_CHOGALL_EQUIP,
            EVENT_TAKE_HAMMER,
            EVENT_MOVE_TO,
            EVENT_FOCUS_CHOGALL,
            EVENT_MOVE_SECOND,
            EVENT_MOVE_FINAL,
            EVENT_MOUNTAIN_BACKHAND,
            EVENT_MIRROR_AWAY
        };

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_SUMMON_SKULLCRUSHER   = 87357,
            SPELL_SUMMON_CHOGALL        = 87358,
            SPELL_SUMMON_MIRROR         = 87362,
            SPELL_SKULLCRUSHER_BACKHAND = 87448,
            SPELL_STORM_CLOUD           = 87685,
            SPELL_CLONE_MIRROR          = 91712,
            SPELL_QUEST_DETECTION       = 94567,
            SPELL_COSMETIC_TELEPORT     = 52096,
            SPELL_FADE_TO_BLACK         = 94425
        };

        enum pointId
        {
            POINT_FIRST     = 1,
            POINT_SECOND,
            POINT_THIRD
        };

        enum npcId
        {
            NPC_TARGET_SKY  = 51039,
            NPC_CHOGALL     = 46900,
            NPC_MOUNTAIN    = 46899,
            NPC_MIRROR      = 46905
        };

        enum npcCombatId
        {
            NPC_SKULLCRUSHER    = 46732,
            NPC_A_SHADOW        = 50640,
            NPC_A_FROST         = 50636,
            NPC_A_EARTH         = 50638,
            NPC_A_FLAME         = 50635,
            NPC_A_AIR           = 50643,

            // Alliance
            NPC_KURDRAN         = 46895,
            NPC_CASSIUS         = 45669,
            NPC_SHAW            = 46892,

            // Horde
            NPC_COZWYNN         = 47039,
            NPC_GARONA          = 46893,
            NPC_ZAELA           = 46897
        };

        enum emoteId
        {
            EMOTE_TAKE_HAMMER   = 25
        };

        class eventTalkToPlayer : public BasicEvent
        {
        public:
            explicit eventTalkToPlayer(Player* player) : player(player)
            {
            }

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (player && player->IsInWorld())
                    player->MonsterTextEmote("Get back up there and get into the fight!", player->GetGUID(), true);
                return true;
            }

        private:
            Player* player;
        };

        class eventPlayerChangePhase : public BasicEvent
        {
        public:
            explicit eventPlayerChangePhase(Player* player) : player(player)
            {
            }

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (player && player->IsInWorld())
                {
                    player->RemoveAurasDueToSpell(79041);
                    player->SetPhaseMask(16384, true);

                    Creature* skullcrusher = player->FindNearestCreature(NPC_SKULLCRUSHER, 1000.0f, true);
                    if (!skullcrusher)
                    {
                        if (player->getRaceMask() & RACEMASK_ALLIANCE)
                        {
                            player->SummonCreature(NPC_SKULLCRUSHER, -5248.08f, -4829.97f, 444.47f, 0.99f, TEMPSUMMON_CORPSE_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(NPC_KURDRAN, -5242.06f, -4833.35f, 444.53f, 2.63f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(NPC_CASSIUS, -5244.56f, -4824.20f, 444.56f, 4.16f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(NPC_SHAW, -5253.70f, -4825.95f, 444.57f, 5.66f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        }
                        else
                        {
                            player->SummonCreature(NPC_SKULLCRUSHER, -5248.08f, -4829.97f, 444.47f, 0.99f, TEMPSUMMON_CORPSE_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(NPC_ZAELA, -5242.06f, -4833.35f, 444.53f, 2.63f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(NPC_COZWYNN, -5244.56f, -4824.20f, 444.56f, 4.16f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            player->SummonCreature(NPC_GARONA, -5253.70f, -4825.95f, 444.57f, 5.66f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        }

                        // Altars
                        player->SummonCreature(NPC_A_SHADOW, -5226.58f, -4820.45f, 445.63f, 3.63f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        player->SummonCreature(NPC_A_FROST, -5232.41f, -4847.02f, 445.51f, 2.30f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        player->SummonCreature(NPC_A_AIR, -5258.72f, -4848.62f, 445.60f, 1.02f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        player->SummonCreature(NPC_A_FLAME, -5269.35f, -4824.56f, 445.68f, 3.00f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        player->SummonCreature(NPC_A_EARTH, -5248.50f, -4806.79f, 445.58f, 1.72f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                    }
                }
                return true;
            }

        private:
            Player* player;
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 500);
        }

        void OnCharmed(bool apply)
        {
        }

        void EnterEvadeMode()
        {
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FIRST:
                {
                    events.ScheduleEvent(EVENT_FOCUS_CHOGALL, 3000);
                    events.ScheduleEvent(EVENT_MOVE_SECOND, 2000);
                    break;
                }
                case POINT_THIRD:
                {
                    events.ScheduleEvent(EVENT_MOUNTAIN_BACKHAND, 1000);
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
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->CastSpell(invoker, SPELL_SUMMON_CHOGALL, true);
                            invoker->CastSpell(invoker, SPELL_SUMMON_MIRROR, true);
                            invoker->CastSpell(invoker, SPELL_SUMMON_SKULLCRUSHER, true);
                            invoker->SummonCreature(NPC_TARGET_SKY, -5229.58f, -4814.11f, 444.17f, 4.41f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            invoker->EnterVehicle(me, 0);
                            events.ScheduleEvent(EVENT_FOCUS_TARGET, 2500);
                            events.CancelEvent(EVENT_RIDE_INVOKER);
                            break;
                        }
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        break;
                    }
                    case EVENT_FOCUS_TARGET:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(invoker, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(invoker, targets, u_check);
                            invoker->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() && (*itr)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_TARGET_SKY:
                                        {
                                            (*itr)->GetMotionMaster()->MovePoint(0, -5246.35f, -4846.47f, 444.42f);
                                            me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                            break;
                                        }
                                        case NPC_MOUNTAIN:
                                        {
                                            (*itr)->GetMotionMaster()->MovePoint(0, -5246.35f, -4846.47f, 444.42f);
                                            break;
                                        }
                                        case NPC_CHOGALL:
                                        {
                                            events.ScheduleEvent(EVENT_CHOGALL_EQUIP, 16500);
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(8000, 0);
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(14000, 1);
                                            (*itr)->CastWithDelay(30000, (*itr), SPELL_STORM_CLOUD, true);
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(32000, 2);
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(49000, 3);
                                            (*itr)->CastWithDelay(57000, (*itr), SPELL_COSMETIC_TELEPORT, true);
                                            (*itr)->ToCreature()->DespawnOrUnsummon(58500);
                                            events.ScheduleEvent(EVENT_MOVE_FINAL, 58000);
                                            break;
                                        }
                                        case NPC_MIRROR:
                                        {
                                            invoker->AddAura(SPELL_CLONE_MIRROR, (*itr));
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO, 1500);
                        events.CancelEvent(EVENT_FOCUS_TARGET);
                        break;
                    }
                    case EVENT_MOVE_TO:
                    {
                        me->SetWalk(false);
                        me->SetSpeed(MOVE_RUN, 2.4f, true);
                        me->SetSpeed(MOVE_FLIGHT, 2.4f, true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-5210.08f, -4817.80f, 444.85f, 25.0f, 25.0f, POINT_FIRST);
                        events.CancelEvent(EVENT_MOVE_TO);
                        break;
                    }
                    case EVENT_FOCUS_CHOGALL:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                if ((*itr)->GetEntry() != NPC_TARGET_SKY)
                                    continue;

                                (*itr)->GetMotionMaster()->MovementExpired(false);
                                (*itr)->GetMotionMaster()->MoveJump(-5249.86f, -4827.90f, 441.41f, 25.5f, 10.0f, 2);
                            }
                        }
                        events.CancelEvent(EVENT_FOCUS_CHOGALL);
                        break;
                    }
                    case EVENT_MOVE_SECOND:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(invoker, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(invoker, targets, u_check);
                            invoker->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() && (*itr)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    if ((*itr)->GetEntry() == NPC_MOUNTAIN)
                                    {
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                        (*itr)->GetMotionMaster()->MovePoint(2, -5241.37f, -4837.55f, 444.42f);
                                        (*itr)->SetFacingTo(1.78f);
                                    }
                                }
                            }
                        }
                        me->GetMotionMaster()->MoveJump(-5221.52f, -4817.80f, 444.85f, 1.0f, 1.0f, POINT_SECOND);
                        events.CancelEvent(EVENT_MOVE_SECOND);
                        break;
                    }
                    case EVENT_CHOGALL_EQUIP:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(invoker, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(invoker, targets, u_check);
                            invoker->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() && (*itr)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    if ((*itr)->GetEntry() == NPC_CHOGALL)
                                    {
                                        (*itr)->HandleEmoteCommand(EMOTE_TAKE_HAMMER);
                                        events.ScheduleEvent(EVENT_TAKE_HAMMER, 2000);
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_CHOGALL_EQUIP);
                        break;
                    }
                    case EVENT_TAKE_HAMMER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(invoker, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(invoker, targets, u_check);
                            invoker->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() && (*itr)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    if ((*itr)->GetEntry() == NPC_CHOGALL)
                                    {
                                        (*itr)->ToCreature()->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 65090);
                                        invoker->RemoveAurasDueToSpell(SPELL_QUEST_DETECTION);
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_TAKE_HAMMER);
                        break;
                    }
                    case EVENT_MOVE_FINAL:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-5267.02f, -4831.28f, 450.79f, 10.0f, 10.0f, POINT_THIRD);
                        events.CancelEvent(EVENT_MOVE_FINAL);
                        break;
                    }
                    case EVENT_MOUNTAIN_BACKHAND:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(invoker, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(invoker, targets, u_check);
                            invoker->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() && (*itr)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    if ((*itr)->GetEntry() == NPC_MOUNTAIN)
                                    {
                                        (*itr)->CastSpell((*itr), SPELL_SKULLCRUSHER_BACKHAND);
                                        events.ScheduleEvent(EVENT_MIRROR_AWAY, 1000);
                                        (*itr)->ToCreature()->DespawnOrUnsummon(8000);
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MOUNTAIN_BACKHAND);
                        break;
                    }
                    case EVENT_MIRROR_AWAY:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(invoker, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(invoker, targets, u_check);
                            invoker->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() && (*itr)->ToTempSummon()->GetSummoner() == invoker)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_MIRROR:
                                        {
                                            (*itr)->GetMotionMaster()->MoveJump(-5177.74f, -4735.80f, 456.45f, 25.0f, 25.0f, 10);
                                            (*itr)->ToCreature()->DespawnOrUnsummon(3000);
                                            invoker->CastWithDelay(2000, invoker, SPELL_FADE_TO_BLACK, true);
                                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                                            {
                                                invoker->ToPlayer()->m_Events.AddEvent(new eventTalkToPlayer(invoker->ToPlayer()), (invoker->ToPlayer())->m_Events.CalculateTime(14000));
                                                invoker->ToPlayer()->m_Events.AddEvent(new eventPlayerChangePhase(invoker->ToPlayer()), (invoker->ToPlayer())->m_Events.CalculateTime(17000));
                                            }
                                            me->DespawnOrUnsummon(6000);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MOUNTAIN_BACKHAND);
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
        return new npc_th_skullcrusher_cameraAI(creature);
    }
};

class npc_th_skullcrusher_fight : public CreatureScript
{
public:
    npc_th_skullcrusher_fight() : CreatureScript("npc_th_skullcrusher_fight")
    {
    }

    enum eventId
    {
        EVENT_MASSIVE_SHOCKWAVE     = 1,
        EVENT_GROUND_POUND,
        EVENT_FIST_OF_CHOGALL,
        EVENT_ADRENALINE,
        EVENT_HP_85,
        EVENT_ENABLE_ALTARS,
        EVENT_KNOCK_KURDRAN,
        EVENT_FINALIZE
    };

    enum spellId
    {
        SPELL_MASSIVE_SHOCKWAVE     = 93760,
        SPELL_GROUND_POUND          = 93767,
        SPELL_FIST_OF_CHOGALL       = 93764,
        SPELL_BLESSING_OF_CHOGALL   = 93835,
        SPELL_ADRENALINE            = 93822,
        SPELL_CLICK_ME              = 94557
    };

    enum npcCombatId
    {
        NPC_SKULLCRUSHER    = 46732,
        NPC_A_SHADOW        = 50640,
        NPC_A_FROST         = 50636,
        NPC_A_EARTH         = 50638,
        NPC_A_FLAME         = 50635,
        NPC_A_AIR           = 50643,

        // Alliance
        NPC_KURDRAN         = 46895,
        NPC_CASSIUS         = 45669,
        NPC_SHAW            = 46892,

        // Horde
        NPC_COZWYNN         = 47039,
        NPC_GARONA          = 46893,
        NPC_ZAELA           = 46897,

        // Horn & Drums
        NPC_WILDHAMMER_HORN = 50653,
        NPC_DRAGONMAW_DRUMS = 50655
    };

    struct npc_th_skullcrusher_fightAI : public ScriptedAI
    {
        npc_th_skullcrusher_fightAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void EnableAltars()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_A_AIR:
                        case NPC_A_EARTH:
                        case NPC_A_SHADOW:
                        case NPC_A_FLAME:
                        case NPC_A_FROST:
                            (*itr)->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->ToPlayer()->KilledMonsterCredit(46732);
            }

            me->DespawnCreaturesInArea(NPC_CASSIUS);
            me->DespawnCreaturesInArea(NPC_SHAW);
            me->DespawnCreaturesInArea(NPC_KURDRAN);
            me->DespawnCreaturesInArea(NPC_WILDHAMMER_HORN);
            me->DespawnCreaturesInArea(NPC_DRAGONMAW_DRUMS);
            me->DespawnCreaturesInArea(NPC_ZAELA);
            me->DespawnCreaturesInArea(NPC_COZWYNN);
            me->DespawnCreaturesInArea(NPC_GARONA);
            me->DespawnCreaturesInArea(NPC_A_AIR);
            me->DespawnCreaturesInArea(NPC_A_EARTH);
            me->DespawnCreaturesInArea(NPC_A_FLAME);
            me->DespawnCreaturesInArea(NPC_A_FROST);
            me->DespawnCreaturesInArea(NPC_A_SHADOW);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(20000);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_MASSIVE_SHOCKWAVE, 5000);
            events.ScheduleEvent(EVENT_GROUND_POUND, 12000);
            events.ScheduleEvent(EVENT_HP_85, 5000);
            events.ScheduleEvent(EVENT_FINALIZE, 5000);
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
                    case EVENT_MASSIVE_SHOCKWAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_MASSIVE_SHOCKWAVE);
                        events.RescheduleEvent(EVENT_MASSIVE_SHOCKWAVE, urand(8000, 16000));
                        break;
                    }
                    case EVENT_GROUND_POUND:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                            DoCast(target, SPELL_GROUND_POUND, true);
                        events.RescheduleEvent(EVENT_GROUND_POUND, urand(10000, 18000));
                        break;
                    }
                    case EVENT_HP_85:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.85f)
                        {
                            if (Creature* cassius = me->FindNearestCreature(NPC_CASSIUS, 100.0f, true))
                                cassius->AI()->Talk(0);

                            if (Creature* cozwynn = me->FindNearestCreature(NPC_COZWYNN, 100.0f, true))
                                cozwynn->AI()->Talk(0);

                            events.ScheduleEvent(EVENT_ENABLE_ALTARS, 8000);
                            events.CancelEvent(EVENT_HP_85);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_85, 2000);
                        break;
                    }
                    case EVENT_ENABLE_ALTARS:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                                (*itr)->MonsterTextEmote("Activate the altars to gain the blessings of the elements, but avoid the deadly shadow altar!", (*itr)->GetGUID(), true);
                        }
                        EnableAltars();
                        events.ScheduleEvent(EVENT_FIST_OF_CHOGALL, 60000);
                        events.CancelEvent(EVENT_ENABLE_ALTARS);
                        break;
                    }
                    case EVENT_FIST_OF_CHOGALL:
                    {
                        if (Creature* kurdran = me->FindNearestCreature(NPC_KURDRAN, 100.0f, true))
                        {
                            DoCast(kurdran, SPELL_FIST_OF_CHOGALL);
                            events.ScheduleEvent(EVENT_KNOCK_KURDRAN, 2000);
                        }
                        if (Creature* zaela = me->FindNearestCreature(NPC_ZAELA, 100.0f, true))
                        {
                            DoCast(zaela, SPELL_FIST_OF_CHOGALL);
                            events.ScheduleEvent(EVENT_KNOCK_KURDRAN, 2000);
                        }

                        if (Creature* cassius = me->FindNearestCreature(NPC_CASSIUS, 100.0f, true))
                            cassius->ToCreature()->AI()->TalkWithDelay(2000, 1);

                        if (Creature* cozwynn = me->FindNearestCreature(NPC_COZWYNN, 100.0f, true))
                            cozwynn->ToCreature()->AI()->TalkWithDelay(2000, 1);

                        events.RescheduleEvent(EVENT_FIST_OF_CHOGALL, urand(50000, 60000));
                        break;
                    }
                    case EVENT_KNOCK_KURDRAN:
                    {
                        if (Creature* kurdran = me->FindNearestCreature(NPC_KURDRAN, 100.0f, true))
                        {
                            kurdran->CastSpell(kurdran, SPELL_CLICK_ME, true);
                            kurdran->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            kurdran->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            kurdran->SetReactState(REACT_PASSIVE);
                            kurdran->AttackStop();
                            kurdran->CombatStop();
                            kurdran->SetStandState(UNIT_STAND_STATE_DEAD);
                            events.ScheduleEvent(EVENT_KNOCK_KURDRAN, 2000);
                        }
                        if (Creature* zaela = me->FindNearestCreature(NPC_ZAELA, 100.0f, true))
                        {
                            zaela->CastSpell(zaela, SPELL_CLICK_ME, true);
                            zaela->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            zaela->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            zaela->SetReactState(REACT_PASSIVE);
                            zaela->AttackStop();
                            zaela->CombatStop();
                            zaela->SetStandState(UNIT_STAND_STATE_DEAD);
                            events.ScheduleEvent(EVENT_KNOCK_KURDRAN, 2000);
                        }
                        events.CancelEvent(EVENT_KNOCK_KURDRAN);
                        break;
                    }
                    case EVENT_FINALIZE:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.10f)
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(100.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_KURDRAN:
                                        case NPC_SHAW:
                                        case NPC_CASSIUS:
                                        case NPC_ZAELA:
                                        case NPC_GARONA:
                                        case NPC_COZWYNN:
                                        {
                                            (*itr)->ToCreature()->SetReactState(REACT_PASSIVE);
                                            (*itr)->AttackStop();
                                            (*itr)->SetStandState(UNIT_STAND_STATE_DEAD);
                                            if ((*itr)->GetEntry() == NPC_CASSIUS || (*itr)->GetEntry() == NPC_COZWYNN)
                                            {
                                                (*itr)->ToCreature()->AI()->Talk(2);
                                                (*itr)->ToCreature()->AI()->TalkWithDelay(7000, 3);
                                            }
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }

                            Talk(0);
                            TalkWithDelay(2000, 1);

                            if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            {
                                if (invoker->getRaceMask() & RACEMASK_ALLIANCE)
                                    invoker->SummonCreature(NPC_WILDHAMMER_HORN, -5243.41f, -4831.87f, 444.41f, 1.37f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                else
                                    invoker->SummonCreature(NPC_DRAGONMAW_DRUMS, -5243.41f, -4831.87f, 444.41f, 1.37f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            }

                            // Enable Horn
                            if (Creature* horn = me->FindNearestCreature(NPC_WILDHAMMER_HORN, 100.0f, true))
                                horn->CastSpell(horn, SPELL_CLICK_ME, true);

                            // Enable Drums
                            if (Creature* drums = me->FindNearestCreature(NPC_DRAGONMAW_DRUMS, 100.0f, true))
                                drums->CastSpell(drums, SPELL_CLICK_ME, true);

                            DoCast(SPELL_BLESSING_OF_CHOGALL);
                            events.CancelEvent(EVENT_FINALIZE);
                            break;
                        }
                        events.RescheduleEvent(EVENT_FINALIZE, 2000);
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
        return new npc_th_skullcrusher_fightAI(creature);
    }
};

class npc_th_skullcrusher_fighters : public CreatureScript
{
public:
    npc_th_skullcrusher_fighters() : CreatureScript("npc_th_skullcrusher_fighters")
    {
    }

    enum eventId
    {
        EVENT_CHARGE            = 1,
        EVENT_MOCKING_BLOW,
        EVENT_SHOCKWAVE,
        EVENT_SUNDER_ARMOR,
        EVENT_GREATER_HEAL
    };

    enum spellId
    {
        SPELL_CHARGE            = 22120,
        SPELL_MOCKING_BLOW      = 21008,
        SPELL_SHOCKWAVE         = 79872,
        SPELL_SUNDER_ARMOR      = 11971,
        SPELL_COMMANDING_SHOUT  = 80983,
        SPELL_CLICK_ME          = 94557,
        SPELL_HEALING_WAVE      = 77472
    };

    enum npcCombatId
    {
        NPC_SKULLCRUSHER    = 46732,
        NPC_A_SHADOW        = 50640,
        NPC_A_FROST         = 50636,
        NPC_A_EARTH         = 50638,
        NPC_A_FLAME         = 50635,
        NPC_A_AIR           = 50643,

        // Alliance
        NPC_KURDRAN         = 46895,
        NPC_CASSIUS         = 45669,
        NPC_SHAW            = 46892,

        // Horde
        NPC_COZWYNN         = 47039,
        NPC_GARONA          = 46893,
        NPC_ZAELA           = 46897
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->HasAura(SPELL_CLICK_ME))
        {
            creature->SetStandState(UNIT_STAND_STATE_STAND);
            creature->SetReactState(REACT_AGGRESSIVE);
            creature->RemoveAurasDueToSpell(SPELL_CLICK_ME);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            if (Creature* skullcrusher = creature->FindNearestCreature(NPC_SKULLCRUSHER, 100.0f, true))
                creature->AI()->AttackStart(skullcrusher);
            return true;
        }
        return true;
    }

    struct npc_th_skullcrusher_fightersAI : public ScriptedAI
    {
        npc_th_skullcrusher_fightersAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void JustDied(Unit* /*killer*/)
        {
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->DespawnOrUnsummon(20000);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            switch (me->GetEntry())
            {
                case NPC_KURDRAN:
                case NPC_ZAELA:
                {
                    DoCast(SPELL_COMMANDING_SHOUT);
                    events.ScheduleEvent(EVENT_CHARGE, 1);
                    events.ScheduleEvent(EVENT_MOCKING_BLOW, urand(3000, 10000));
                    events.ScheduleEvent(EVENT_SUNDER_ARMOR, urand(5000, 6000));
                    events.ScheduleEvent(EVENT_SHOCKWAVE, urand(8000, 20000));
                    break;
                }
                case NPC_CASSIUS:
                case NPC_COZWYNN:
                {
                    events.ScheduleEvent(EVENT_GREATER_HEAL, 10000);
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
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHARGE:
                    {
                        if (Unit* victim = me->getVictim())
                        {
                            DoCast(victim, SPELL_CHARGE);
                            victim->AddThreat(me, 10000.0f);
                        }
                        events.CancelEvent(EVENT_CHARGE);
                        break;
                    }
                    case EVENT_MOCKING_BLOW:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCastVictim(SPELL_MOCKING_BLOW);
                        events.RescheduleEvent(EVENT_MOCKING_BLOW, urand(3000, 10000));
                        break;
                    }
                    case EVENT_SUNDER_ARMOR:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCastVictim(SPELL_SUNDER_ARMOR);
                        events.RescheduleEvent(EVENT_SUNDER_ARMOR, 5000);
                        break;
                    }
                    case EVENT_SHOCKWAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_SHOCKWAVE);
                        events.RescheduleEvent(EVENT_SHOCKWAVE, urand(10000, 20000));
                        break;
                    }
                    case EVENT_GREATER_HEAL:
                    {
                        RESCHEDULE_IF_CASTING;
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                            {
                                if ((*itr)->GetHealth() > (*itr)->GetMaxHealth() * 0.90f)
                                    continue;

                                DoCast((*itr), SPELL_HEALING_WAVE, true);
                            }
                        }

                        events.RescheduleEvent(EVENT_GREATER_HEAL, urand(6500, 9000));
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
        return new npc_th_skullcrusher_fightersAI(creature);
    }
};

class npc_th_elemental_altars : public CreatureScript
{
public:
    npc_th_elemental_altars() : CreatureScript("npc_th_elemental_altars")
    {
    }

    enum questId
    {
        QUEST_SKULLCRUSHER_THE_MOUNTAIN_A   = 27787,
        QUEST_SKULLCRUSHER_THE_MOUNTAIN_H   = 27788
    };

    enum spellId
    {
        // Earth
        SPELL_A_EARTH_PLAYER    = 93790,
        SPELL_A_EARTH_ALTAR     = 93792,

        // Air
        SPELL_A_AIR_PLAYER      = 93787,
        SPELL_A_AIR_ALTAR       = 93788,

        // Flame
        SPELL_A_FLAME_PLAYER    = 93778,
        SPELL_A_FLAME_ALTAR     = 93779,

        // Frost
        SPELL_A_FROST_PLAYER    = 93782,
        SPELL_A_FROST_ALTAR     = 93781,

        // Shadow
        SPELL_A_SHADOW_PLAYER   = 93796,
        SPELL_A_SHADOW_ALTAR    = 93798
    };

    enum altarId
    {
        NPC_A_SHADOW    = 50640,
        NPC_A_FROST     = 50636,
        NPC_A_EARTH     = 50638,
        NPC_A_FLAME     = 50635,
        NPC_A_AIR       = 50643
    };

    enum combatNpcId
    {
        // Alliance
        NPC_KURDRAN         = 46895,
        NPC_CASSIUS         = 45669,
        NPC_SHAW            = 46892,

        // Horde
        NPC_COZWYNN         = 47039,
        NPC_GARONA          = 46893,
        NPC_ZAELA           = 46897
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_SKULLCRUSHER_THE_MOUNTAIN_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_SKULLCRUSHER_THE_MOUNTAIN_H) == QUEST_STATUS_INCOMPLETE)
        {
            if (creature->HasAura(SPELL_A_EARTH_ALTAR) || creature->HasAura(SPELL_A_FLAME_ALTAR) ||
                creature->HasAura(SPELL_A_AIR_ALTAR) || creature->HasAura(SPELL_A_FROST_ALTAR))
                return true;

            switch (creature->GetEntry())
            {
                case NPC_A_SHADOW:
                {
                    player->CastSpell(player, SPELL_A_SHADOW_PLAYER);
                    creature->AddAura(SPELL_A_SHADOW_ALTAR, creature);
                    break;
                }
                case NPC_A_FLAME:
                {
                    player->CastSpell(player, SPELL_A_FLAME_PLAYER);
                    creature->AddAura(SPELL_A_FLAME_ALTAR, creature);
                    if (Creature* cassius = creature->FindNearestCreature(NPC_CASSIUS, 100.0f, true))
                    {
                        cassius->CastSpell(cassius, SPELL_A_FLAME_PLAYER, true);
                        cassius->AddAura(SPELL_A_FLAME_PLAYER, cassius);
                    }
                    if (Creature* kurdran = creature->FindNearestCreature(NPC_KURDRAN, 100.0f, true))
                    {
                        kurdran->CastSpell(kurdran, SPELL_A_FLAME_PLAYER, true);
                        kurdran->AddAura(SPELL_A_FLAME_PLAYER, kurdran);
                    }
                    if (Creature* shaw = creature->FindNearestCreature(NPC_SHAW, 100.0f, true))
                    {
                        shaw->CastSpell(shaw, SPELL_A_FLAME_PLAYER, true);
                        shaw->AddAura(SPELL_A_FLAME_PLAYER, shaw);
                    }
                    if (Creature* cozwynn = creature->FindNearestCreature(NPC_COZWYNN, 100.0f, true))
                    {
                        cozwynn->CastSpell(cozwynn, SPELL_A_FLAME_PLAYER, true);
                        cozwynn->AddAura(SPELL_A_FLAME_PLAYER, cozwynn);
                    }
                    if (Creature* zaela = creature->FindNearestCreature(NPC_ZAELA, 100.0f, true))
                    {
                        zaela->CastSpell(zaela, SPELL_A_FLAME_PLAYER, true);
                        zaela->AddAura(SPELL_A_FLAME_PLAYER, zaela);
                    }
                    if (Creature* garona = creature->FindNearestCreature(NPC_GARONA, 100.0f, true))
                    {
                        garona->CastSpell(garona, SPELL_A_FLAME_PLAYER, true);
                        garona->AddAura(SPELL_A_FLAME_PLAYER, garona);
                    }
                    break;
                }
                case NPC_A_EARTH:
                {
                    player->CastSpell(player, SPELL_A_EARTH_PLAYER);
                    creature->AddAura(SPELL_A_EARTH_ALTAR, creature);
                    if (Creature* cassius = creature->FindNearestCreature(NPC_CASSIUS, 100.0f, true))
                    {
                        cassius->CastSpell(cassius, SPELL_A_EARTH_PLAYER, true);
                        cassius->AddAura(SPELL_A_EARTH_PLAYER, cassius);
                    }
                    if (Creature* kurdran = creature->FindNearestCreature(NPC_KURDRAN, 100.0f, true))
                    {
                        kurdran->CastSpell(kurdran, SPELL_A_EARTH_PLAYER, true);
                        kurdran->AddAura(SPELL_A_EARTH_PLAYER, kurdran);
                    }
                    if (Creature* shaw = creature->FindNearestCreature(NPC_SHAW, 100.0f, true))
                    {
                        shaw->CastSpell(shaw, SPELL_A_EARTH_PLAYER, true);
                        shaw->AddAura(SPELL_A_EARTH_PLAYER, shaw);
                    }
                    if (Creature* cozwynn = creature->FindNearestCreature(NPC_COZWYNN, 100.0f, true))
                    {
                        cozwynn->CastSpell(cozwynn, SPELL_A_FLAME_PLAYER, true);
                        cozwynn->AddAura(SPELL_A_FLAME_PLAYER, cozwynn);
                    }
                    if (Creature* zaela = creature->FindNearestCreature(NPC_ZAELA, 100.0f, true))
                    {
                        zaela->CastSpell(zaela, SPELL_A_FLAME_PLAYER, true);
                        zaela->AddAura(SPELL_A_FLAME_PLAYER, zaela);
                    }
                    if (Creature* garona = creature->FindNearestCreature(NPC_GARONA, 100.0f, true))
                    {
                        garona->CastSpell(garona, SPELL_A_FLAME_PLAYER, true);
                        garona->AddAura(SPELL_A_FLAME_PLAYER, garona);
                    }
                    break;
                }
                case NPC_A_AIR:
                {
                    player->CastSpell(player, SPELL_A_AIR_PLAYER);
                    creature->AddAura(SPELL_A_AIR_ALTAR, creature);
                    if (Creature* cassius = creature->FindNearestCreature(NPC_CASSIUS, 100.0f, true))
                    {
                        cassius->CastSpell(cassius, SPELL_A_AIR_PLAYER, true);
                        cassius->AddAura(SPELL_A_AIR_PLAYER, cassius);
                    }
                    if (Creature* kurdran = creature->FindNearestCreature(NPC_KURDRAN, 100.0f, true))
                    {
                        kurdran->CastSpell(kurdran, SPELL_A_AIR_PLAYER, true);
                        kurdran->AddAura(SPELL_A_AIR_PLAYER, kurdran);
                    }
                    if (Creature* shaw = creature->FindNearestCreature(NPC_SHAW, 100.0f, true))
                    {
                        shaw->CastSpell(shaw, SPELL_A_AIR_PLAYER, true);
                        shaw->AddAura(SPELL_A_AIR_PLAYER, shaw);
                    }
                    if (Creature* cozwynn = creature->FindNearestCreature(NPC_COZWYNN, 100.0f, true))
                    {
                        cozwynn->CastSpell(cozwynn, SPELL_A_FLAME_PLAYER, true);
                        cozwynn->AddAura(SPELL_A_FLAME_PLAYER, cozwynn);
                    }
                    if (Creature* zaela = creature->FindNearestCreature(NPC_ZAELA, 100.0f, true))
                    {
                        zaela->CastSpell(zaela, SPELL_A_FLAME_PLAYER, true);
                        zaela->AddAura(SPELL_A_FLAME_PLAYER, zaela);
                    }
                    if (Creature* garona = creature->FindNearestCreature(NPC_GARONA, 100.0f, true))
                    {
                        garona->CastSpell(garona, SPELL_A_FLAME_PLAYER, true);
                        garona->AddAura(SPELL_A_FLAME_PLAYER, garona);
                    }
                    break;
                }
                case NPC_A_FROST:
                {
                    player->CastSpell(player, SPELL_A_FROST_PLAYER);
                    creature->AddAura(SPELL_A_FROST_ALTAR, creature);
                    if (Creature* cassius = creature->FindNearestCreature(NPC_CASSIUS, 100.0f, true))
                    {
                        cassius->CastSpell(cassius, SPELL_A_FROST_PLAYER, true);
                        cassius->AddAura(SPELL_A_FROST_PLAYER, cassius);
                    }
                    if (Creature* kurdran = creature->FindNearestCreature(NPC_KURDRAN, 100.0f, true))
                    {
                        kurdran->CastSpell(kurdran, SPELL_A_FROST_PLAYER, true);
                        kurdran->AddAura(SPELL_A_FROST_PLAYER, kurdran);
                    }
                    if (Creature* shaw = creature->FindNearestCreature(NPC_SHAW, 100.0f, true))
                    {
                        shaw->CastSpell(shaw, SPELL_A_FROST_PLAYER, true);
                        shaw->AddAura(SPELL_A_FROST_PLAYER, shaw);
                    }
                    if (Creature* cozwynn = creature->FindNearestCreature(NPC_COZWYNN, 100.0f, true))
                    {
                        cozwynn->CastSpell(cozwynn, SPELL_A_FLAME_PLAYER, true);
                        cozwynn->AddAura(SPELL_A_FLAME_PLAYER, cozwynn);
                    }
                    if (Creature* zaela = creature->FindNearestCreature(NPC_ZAELA, 100.0f, true))
                    {
                        zaela->CastSpell(zaela, SPELL_A_FLAME_PLAYER, true);
                        zaela->AddAura(SPELL_A_FLAME_PLAYER, zaela);
                    }
                    if (Creature* garona = creature->FindNearestCreature(NPC_GARONA, 100.0f, true))
                    {
                        garona->CastSpell(garona, SPELL_A_FLAME_PLAYER, true);
                        garona->AddAura(SPELL_A_FLAME_PLAYER, garona);
                    }
                    break;
                }
                default:
                    break;
            }
            return true;
        }
        return true;
    }
};

class npc_th_horn_and_drums : public CreatureScript
{
public:
    npc_th_horn_and_drums() : CreatureScript("npc_th_horn_and_drums")
    {
    }

    enum questId
    {
        QUEST_SKULLCRUSHER_THE_MOUNTAIN_A   = 27787,
        QUEST_SKULLCRUSHER_THE_MOUNTAIN_H   = 27788
    };

    enum spellId
    {
        SPELL_CLICK_ME  = 94557,
        SPELL_HEROISM   = 78151
    };

    enum combatNpcId
    {
        // Alliance
        NPC_KURDRAN             = 46895,
        NPC_CASSIUS             = 45669,
        NPC_SHAW                = 46892,

        // Horde
        NPC_COZWYNN             = 47039,
        NPC_GARONA              = 46893,
        NPC_ZAELA               = 46897,

        // Drakes
        NPC_WILDHAMMER_GRYPHON  = 50612,
        NPC_DRAGONMAW_DRAKE     = 50599,

        // Horn & Drums
        NPC_WILDHAMMER_HORN     = 50653,
        NPC_DRAGONMAW_DRUMS     = 50655
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_SKULLCRUSHER_THE_MOUNTAIN_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_SKULLCRUSHER_THE_MOUNTAIN_H) == QUEST_STATUS_INCOMPLETE)
        {
            if (!creature->HasAura(SPELL_CLICK_ME))
                return true;

            if (creature->GetEntry() == NPC_WILDHAMMER_HORN)
            {
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5223.50f, -4819.47f, 458.65f, 3.54f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5228.89f, -4846.22f, 458.39f, 2.39f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5245.20f, -4854.70f, 454.55f, 1.65f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5268.31f, -4835.75f, 458.46f, 0.26f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5271.33f, -4822.75f, 453.57f, 5.96f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5223.50f, -4819.47f, 458.65f, 3.54f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_WILDHAMMER_GRYPHON, -5247.62f, -4801.89f, 457.64f, 4.66f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->RemoveAurasDueToSpell(SPELL_CLICK_ME);
            }

            if (creature->GetEntry() == NPC_DRAGONMAW_DRUMS)
            {
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5223.50f, -4819.47f, 458.65f, 3.54f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5228.89f, -4846.22f, 458.39f, 2.39f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5245.20f, -4854.70f, 454.55f, 1.65f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5268.31f, -4835.75f, 458.46f, 0.26f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5271.33f, -4822.75f, 453.57f, 5.96f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5223.50f, -4819.47f, 458.65f, 3.54f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->SummonCreature(NPC_DRAGONMAW_DRAKE, -5247.62f, -4801.89f, 457.64f, 4.66f, TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->RemoveAurasDueToSpell(SPELL_CLICK_ME);
            }

            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(100.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_KURDRAN:
                        case NPC_SHAW:
                        case NPC_CASSIUS:
                        case NPC_COZWYNN:
                        case NPC_ZAELA:
                        case NPC_GARONA:
                        {
                            (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                            (*itr)->SetStandState(UNIT_STAND_STATE_STAND);
                            if ((*itr)->GetEntry() == NPC_CASSIUS || (*itr)->GetEntry() == NPC_COZWYNN)
                                (*itr)->CastSpell((*itr), SPELL_HEROISM, true);

                            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            creature->DespawnOrUnsummon(10000);
            return true;
        }
        return true;
    }
};

class go_th_rope_ladder : public GameObjectScript
{
public:
    go_th_rope_ladder() : GameObjectScript("go_th_rope_ladder")
    {
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        player->GetMotionMaster()->MoveJump(-3928.29f, -6781.80f, 6.87f, 10.0f, 10.0f, 0);
        return false;
    }
};

class npc_th_frizz_groundspin : public CreatureScript
{
public:
    npc_th_frizz_groundspin() : CreatureScript("npc_th_frizz_groundspin")
    {
    }

    enum questId
    {
        QUEST_TWILIGHT_SKIES    = 26388
    };

    enum spellId
    {
        SPELL_FADE_TO_BLACK     = 94198,
        SPELL_PARACHUTE         = 70988
    };

    enum creditId
    {
        QUEST_CREDIT_SKIES  = 42977
    };

    class eventTeleportTH : public BasicEvent
    {
    public:
        explicit eventTeleportTH(Player* player) : player(player)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            if (player && player->IsInWorld())
            {
                player->TeleportTo(0, -3912.44f, -6783.81f, 146.73f, 1.81f);
                player->AddAura(SPELL_PARACHUTE, player);
            }
            return true;
        }

    private:
        Player* player;
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_TWILIGHT_SKIES)
        {
            player->KilledMonsterCredit(QUEST_CREDIT_SKIES);
            player->CastSpell(player, SPELL_FADE_TO_BLACK, true);
            player->m_Events.AddEvent(new eventTeleportTH(player), (player)->m_Events.CalculateTime(3000));
            return false;
        }
        return true;
    }
};

class npc_th_madness_trigger : public CreatureScript
{
public:
    npc_th_madness_trigger() : CreatureScript("npc_th_madness_trigger")
    {
    }

    enum eventId
    {
        EVENT_CHECK_PLAYER  = 1
    };

    enum npcId
    {
        NPC_WARCHIEF    = 43189,
        NPC_FELBLADE    = 43271,
        NPC_NEGOTIATOR  = 43238
    };

    enum spellId
    {
        SPELL_SUMMON_HORDE_NEGOTIATOR   = 80790,
        SPELL_UNIQUE_PHASING            = 60191,
        SPELL_ESCORTING_NEGOTIATOR      = 80788
    };

    struct npc_th_madness_triggerAI : public ScriptedAI
    {
        npc_th_madness_triggerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void InitializeAI()
        {
            if (me->GetPhaseMask() == 2)
                events.ScheduleEvent(EVENT_CHECK_PLAYER, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PLAYER:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(60.0f, searcher);
                        for (std::list<Unit*>::const_iterator player = targets.begin(); player != targets.end(); ++player)
                        {
                            if ((*player) && (*player)->GetTypeId() == TYPEID_PLAYER)
                            {
                                if ((*player)->HasAura(60191) || (*player)->ToPlayer()->GetQuestStatus(26549) != QUEST_STATUS_INCOMPLETE)
                                    continue;

                                (*player)->AddAura(SPELL_UNIQUE_PHASING, (*player));
                                (*player)->AddAura(SPELL_ESCORTING_NEGOTIATOR, (*player));
                                (*player)->CastSpell((*player), SPELL_SUMMON_HORDE_NEGOTIATOR, true);
                                (*player)->SummonCreature(NPC_WARCHIEF, -4111.87f, -6416.00f, 37.78f, 0.45f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                (*player)->SummonCreature(NPC_FELBLADE, -4110.73f, -6420.47f, 37.70f, 0.45f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                (*player)->SummonCreature(NPC_FELBLADE, -4114.74f, -6412.41f, 37.69f, 0.46f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                                events.RescheduleEvent(EVENT_CHECK_PLAYER, 5000);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_PLAYER, 2000);
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
        return new npc_th_madness_triggerAI(creature);
    }
};

class npc_th_warchief_madness : public CreatureScript
{
public:
    npc_th_warchief_madness() : CreatureScript("npc_th_warchief_madness")
    {
    }

    enum eventId
    {
        EVENT_CHECK_NEGOTIATOR  = 1,
        EVENT_MOVE_FORWARD,
        EVENT_KILL_NEGOTIATOR,
        EVENT_MOVE_TO_PLAYER,
        EVENT_TELEPORT_PLAYER,
        EVENT_FADE_TO_BLACK,

        // Events (Phase 4)
        EVENT_FEL_RAGAMANIA,
        EVENT_FURY,
        EVENT_MORGHOR_SLAM,
        EVENT_SPINEBUSTER,
        EVENT_HP_80,
        EVENT_HP_30,
        EVENT_SET_AGGRESSIVE,
        EVENT_SUMMON_ZAELA,
        EVENT_TRIGGER_SLAM
    };

    enum npcId
    {
        NPC_NEGOTIATOR      = 43238,
        NPC_ZAELA           = 43190,
        NPC_ZAELA_COMBAT    = 43949
    };

    enum spellId
    {
        SPELL_FEL_STOMP             = 80920,
        SPELL_UNIQUE_PHASING        = 60191,
        SPELL_KICK_FIRE             = 80930,
        SPELL_ESCORTING_NEGOTIATOR  = 80788,
        SPELL_FADE_TO_BLACK         = 88629,

        // Spells (Phase 4)
        SPELL_FEL_RAGAMANIA         = 82033,
        SPELL_FURY                  = 82032,
        SPELL_MORGHOR_SLAM          = 82049,
        SPELL_SPINEBUSTER           = 82036
    };

    enum pointId
    {
        POINT_JUMP_FIRST        = 5,
        POINT_JUMP_SECOND,
        POINT_TARGET
    };

    class eventTalkZaela : public BasicEvent
    {
    public:
        explicit eventTalkZaela(Player* player) : player(player)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            if (Creature* zaela = player->FindNearestCreature(NPC_ZAELA, 20.0f, true))
            {
                zaela->AI()->TalkWithDelay(1000, 0);
                zaela->AI()->TalkWithDelay(7000, 1);
            }
            return true;
        }

    private:
        Player* player;
    };

    struct npc_th_warchief_madnessAI : public ScriptedAI
    {
        npc_th_warchief_madnessAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TARGET:
                {
                    DoCast(me, 82050, true);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterEvadeMode()
        {
            if (me->GetPhaseMask() == 4)
            {
                _EnterEvadeMode();
                me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                me->GetMotionMaster()->MoveTargetedHome();
                events.Reset();
            }
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            if (me->GetPhaseMask() == 2)
            {
                me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                me->SetWalk(true);
                events.ScheduleEvent(EVENT_CHECK_NEGOTIATOR, 5000);
                me->AddAura(SPELL_UNIQUE_PHASING, me);
                me->setFaction(35);
                eventInProgress = false;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (me->GetPhaseMask() == 4)
            {
                me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                events.ScheduleEvent(EVENT_HP_30, 2000);
                events.ScheduleEvent(EVENT_HP_80, 2000);
                events.ScheduleEvent(EVENT_FEL_RAGAMANIA, urand(4000, 8000));
                Talk(7);
            }
        }

        void Reset()
        {
            if (me->GetPhaseMask() == 4)
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(10);
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->ToPlayer()->KilledMonsterCredit(me->GetEntry());
            }

            me->DespawnCreaturesInArea(43577, 60.0f);
            me->DespawnCreaturesInArea(43578, 60.0f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat() && me->GetPhaseMask() == 4)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_NEGOTIATOR:
                    {
                        if (eventInProgress == true)
                        {
                            events.CancelEvent(EVENT_CHECK_NEGOTIATOR);
                            break;
                        }

                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 10.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(10.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->GetEntry() == NPC_NEGOTIATOR && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner() && (*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                                {
                                    if (eventInProgress == true)
                                    {
                                        events.CancelEvent(EVENT_CHECK_NEGOTIATOR);
                                        break;
                                    }

                                    TalkWithDelay(5000, 0);
                                    (*itr)->SetFacingToObject(me);
                                    (*itr)->ToCreature()->AI()->TalkWithDelay(15000, 6);
                                    TalkWithDelay(25000, 1);
                                    (*itr)->ToCreature()->AI()->TalkWithDelay(35000, 7);
                                    TalkWithDelay(45000, 2);
                                    me->CastWithDelay(47000, me, SPELL_FEL_STOMP);
                                    (*itr)->ToCreature()->AI()->TalkWithDelay(49000, 8);
                                    (*itr)->CastWithDelay(51000, (*itr), SPELL_KICK_FIRE, true);
                                    TalkWithDelay(55000, 3);
                                    TalkWithDelay(58000, 4);
                                    if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                    {
                                        invoker->NearTeleportTo(-4105.84f, -6408.43f, 37.68f, 3.90f);
                                        invoker->SetControlled(true, UNIT_STATE_ROOT);
                                    }
                                    events.ScheduleEvent(EVENT_MOVE_FORWARD, 50000);
                                    events.ScheduleEvent(EVENT_KILL_NEGOTIATOR, 51500);
                                    events.CancelEvent(EVENT_CHECK_NEGOTIATOR);
                                    eventInProgress = true;
                                    break;
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_NEGOTIATOR, 2000);
                        break;
                    }
                    case EVENT_MOVE_FORWARD:
                    {
                        me->GetMotionMaster()->MovePoint(1, -4109.90f, -6415.17f, 37.70f);
                        events.CancelEvent(EVENT_MOVE_FORWARD);
                        break;
                    }
                    case EVENT_KILL_NEGOTIATOR:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 15.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(15.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                            {
                                if ((*itr)->ToTempSummon() && (*itr)->GetEntry() == NPC_NEGOTIATOR && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    me->Kill((*itr), false);
                            }
                        }
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->RemoveAurasDueToSpell(SPELL_ESCORTING_NEGOTIATOR);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
                        events.ScheduleEvent(EVENT_MOVE_TO_PLAYER, 7000);
                        events.CancelEvent(EVENT_KILL_NEGOTIATOR);
                        break;
                    }
                    case EVENT_MOVE_TO_PLAYER:
                    {
                        me->GetMotionMaster()->MovePoint(2, -4107.96f, -6411.03f, 37.68f, false);
                        TalkWithDelay(5000, 5);
                        TalkWithDelay(13000, 6);
                        events.ScheduleEvent(EVENT_FADE_TO_BLACK, 18000);
                        events.ScheduleEvent(EVENT_TELEPORT_PLAYER, 21000);
                        events.CancelEvent(EVENT_MOVE_TO_PLAYER);
                        break;
                    }
                    case EVENT_FADE_TO_BLACK:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->AddAura(SPELL_FADE_TO_BLACK, invoker);
                        events.CancelEvent(EVENT_FADE_TO_BLACK);
                        break;
                    }
                    case EVENT_TELEPORT_PLAYER:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->NearTeleportTo(-3892.81f, -6472.46f, 15.38f, 3.23f);
                            invoker->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
                            invoker->SetControlled(false, UNIT_STATE_ROOT);
                            invoker->AddAura(SPELL_FEL_STOMP, invoker);
                            if (Aura* aur = me->GetAura(SPELL_FEL_STOMP))
                                aur->SetDuration(15000);
                            if (invoker->GetTypeId() == TYPEID_PLAYER)
                            {
                                invoker->ToPlayer()->KilledMonsterCredit(43243);
                                invoker->ToPlayer()->m_Events.AddEvent(new eventTalkZaela(invoker->ToPlayer()), (invoker->ToPlayer())->m_Events.CalculateTime(5000));
                            }
                            me->DespawnOrUnsummon(5000);
                        }
                        events.CancelEvent(EVENT_TELEPORT_PLAYER);
                        break;
                    }
                    case EVENT_FEL_RAGAMANIA:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_FEL_RAGAMANIA);
                        events.RescheduleEvent(EVENT_FEL_RAGAMANIA, urand(8000, 18000));
                        break;
                    }
                    case EVENT_FURY:
                    {
                        RESCHEDULE_IF_CASTING;
                        Talk(9);
                        DoCast(SPELL_FURY);
                        events.CancelEvent(EVENT_FURY);
                        break;
                    }
                    case EVENT_MORGHOR_SLAM:
                    {
                        RESCHEDULE_IF_CASTING;
                        Talk(8);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {
                            DoCast(target, SPELL_MORGHOR_SLAM);
                            events.ScheduleEvent(EVENT_TRIGGER_SLAM, 3000);
                            me->SetFacingToObject(target);
                        }
                        events.CancelEvent(EVENT_MORGHOR_SLAM);
                        break;
                    }
                    case EVENT_TRIGGER_SLAM:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            me->GetMotionMaster()->MoveJump(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 18.0f, 18.0f, POINT_TARGET);
                        events.CancelEvent(EVENT_TRIGGER_SLAM);
                        break;
                    }
                    case EVENT_SPINEBUSTER:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SPINEBUSTER);
                        events.CancelEvent(EVENT_SPINEBUSTER);
                        break;
                    }
                    case EVENT_HP_80:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.80f)
                        {
                            me->GetMotionMaster()->MovementExpired(false);
                            me->AttackStop();
                            me->SetReactState(REACT_PASSIVE);
                            me->GetMotionMaster()->MoveJump(-4105.19f, -6434.42f, 43.04f, 15.0f, 15.0f, POINT_JUMP_FIRST);
                            events.ScheduleEvent(EVENT_MORGHOR_SLAM, 3000);
                            events.ScheduleEvent(EVENT_SET_AGGRESSIVE, 6000);
                            events.ScheduleEvent(EVENT_SUMMON_ZAELA, 7000);
                            events.CancelEvent(EVENT_HP_80);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_80, 2000);
                        break;
                    }
                    case EVENT_HP_30:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.30f)
                        {
                            me->GetMotionMaster()->MovementExpired(false);
                            me->AttackStop();
                            me->SetReactState(REACT_PASSIVE);
                            me->GetMotionMaster()->MoveJump(-4119.97f, -6400.67f, 42.25f, 15.0f, 15.0f, POINT_JUMP_SECOND);
                            events.ScheduleEvent(EVENT_MORGHOR_SLAM, 3000);
                            events.ScheduleEvent(EVENT_SET_AGGRESSIVE, 6000);
                            events.ScheduleEvent(EVENT_FURY, 7000);
                            events.CancelEvent(EVENT_HP_30);
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_30, 2000);
                        break;
                    }
                    case EVENT_SET_AGGRESSIVE:
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        events.CancelEvent(EVENT_SET_AGGRESSIVE);
                        break;
                    }
                    case EVENT_SUMMON_ZAELA:
                    {
                        me->SummonCreature(NPC_ZAELA, -4099.25f, -6394.29f, 38.72f, 2.95f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.CancelEvent(EVENT_SUMMON_ZAELA);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        bool eventInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_warchief_madnessAI(creature);
    }
};

class npc_th_dragonmaw_fighters : public CreatureScript
{
public:
    npc_th_dragonmaw_fighters() : CreatureScript("npc_th_dragonmaw_fighters")
    {
    }

    struct npc_th_dragonmaw_fightersAI : public ScriptedAI
    {
        npc_th_dragonmaw_fightersAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY  = 1
        };

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
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
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(10.0f))
                        {
                            AttackStart(victim);
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
        return new npc_th_dragonmaw_fightersAI(creature);
    }
};

class npc_th_dragonmaw_civilian : public CreatureScript
{
public:
    npc_th_dragonmaw_civilian() : CreatureScript("npc_th_dragonmaw_civilian")
    {
    }

    enum questId
    {
        QUEST_INSURRECTION      = 26621,
        QUEST_DEATH_TO_MORGHOR  = 26622
    };

    enum creditId
    {
        QUEST_CREDIT_RECRUIT    = 43654
    };

    enum spellId
    {
        SPELL_SHAMAN_HEAL       = 83564,
        SPELL_WARRIOR_CLEAVE    = 81502,
        SPELL_HORDE_BANNER      = 81679
    };

    enum eventId
    {
        EVENT_HEAL_PLAYER   = 1,
        EVENT_CLEAVE,
        EVENT_CHECK_OWNER
    };

    enum actionId
    {
        ACTION_WARRIOR = 0,
        ACTION_SHAMAN
    };

    enum npcId
    {
        NPC_WORKER      = 43577,
        NPC_MERCHANT    = 43578 
    };

    #define GOSSIP_RECRUIT_1 "Fight with me! Take up this blade and be a warrior."
    #define GOSSIP_RECRUIT_2 "Support and heal me! Take up this warhammer and be a shaman."

    bool OnGossipHello(Player* player, Creature* creature)
    {
        uint8 recruitCount = 0;

        std::list<Unit*> targets;
        Trinity::AnyUnitInObjectRangeCheck u_check(creature, 200.0f);
        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(creature, targets, u_check);
        creature->VisitNearbyObject(200.0f, searcher);
        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
        {
            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
            {
                if ((*itr)->ToCreature() && (*itr)->GetOwnerGUID() == player->GetGUID())
                {
                    if ((*itr)->GetEntry() != NPC_WORKER && (*itr)->GetEntry() != NPC_MERCHANT)
                        continue;

                    recruitCount++;
                    if (recruitCount >= 3)
                        return false;
                }
            }
        }

        if (player->GetQuestStatus(QUEST_INSURRECTION) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_DEATH_TO_MORGHOR) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RECRUIT_1, 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RECRUIT_2, 0, 1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (player->GetQuestStatus(QUEST_INSURRECTION) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_DEATH_TO_MORGHOR) == QUEST_STATUS_INCOMPLETE)
        {
            switch (action)
            {
                case ACTION_WARRIOR:
                {
                    creature->CastSpell(creature, SPELL_HORDE_BANNER);
                    creature->setFaction(player->getFaction());
                    creature->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    creature->AI()->DoAction(ACTION_WARRIOR);
                    creature->SetOwnerGUID(player->GetGUID());
                    player->KilledMonsterCredit(QUEST_CREDIT_RECRUIT);
                    creature->GetMotionMaster()->MoveFollow(player, 2.0f, urand(0, 4));
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                case ACTION_SHAMAN:
                {
                    creature->CastSpell(creature, SPELL_HORDE_BANNER);
                    creature->setFaction(player->getFaction());
                    creature->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    creature->AI()->DoAction(ACTION_SHAMAN);
                    creature->SetOwnerGUID(player->GetGUID());
                    player->KilledMonsterCredit(QUEST_CREDIT_RECRUIT);
                    creature->GetMotionMaster()->MoveFollow(player, 2.0f, urand(0, 4));
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                default:
                    break;
            }

            return true;
        }
        return true;
    }

    struct npc_th_dragonmaw_civilianAI : public ScriptedAI
    {
        npc_th_dragonmaw_civilianAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void EnterEvadeMode()
        {
            if (evadeForced == true)
            {
                me->SetWalk(true);
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovementExpired(false);
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetOwnerGUID(0);
                me->setFaction(2305);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 0);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->RemoveAurasDueToSpell(SPELL_HORDE_BANNER);
                evadeForced = false;
                events.Reset();
                _EnterEvadeMode();
            }
            else
            {
                if (Unit* owner = me->GetOwner())
                    me->GetMotionMaster()->MoveFollow(owner, 2.0f, urand(0, 4));
                else
                    me->RemoveAurasDueToSpell(SPELL_HORDE_BANNER);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            me->SetWalk(true);
            me->SetOwnerGUID(0);
            me->setFaction(2305);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 0);
            me->RemoveAurasDueToSpell(SPELL_HORDE_BANNER);
        }

        void Reset()
        {
            if (Unit* owner = me->GetOwner())
                me->GetMotionMaster()->MoveFollow(owner, 2.0f, urand(0, 4));
            else
                me->RemoveAurasDueToSpell(SPELL_HORDE_BANNER);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = urand(521, 784);
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
                    case EVENT_CLEAVE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_WARRIOR_CLEAVE, true);
                        events.RescheduleEvent(EVENT_CLEAVE, urand(8000, 12000));
                        break;
                    }
                    case EVENT_HEAL_PLAYER:
                    {
                        if (Unit* follower = me->FindNearestPlayer(25.0f, true))
                        {
                            if (follower->GetHealth() <= follower->GetMaxHealth() * 0.90f)
                                DoCast(follower, SPELL_SHAMAN_HEAL, true);
                        }
                        events.RescheduleEvent(EVENT_HEAL_PLAYER, 2000);
                        break;
                    }
                    case EVENT_CHECK_OWNER:
                    {
                        if (me->GetOwnerGUID() == 0 || (me->GetOwner() && me->GetOwner()->isDead()) ||
                            (me->GetOwner() && me->GetOwner()->GetDistance2d(me) > 50) || !me->GetOwner())
                        {
                            evadeForced = true;
                            me->SetOwnerGUID(0);
                            EnterEvadeMode();
                            events.CancelEvent(EVENT_CHECK_OWNER);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_OWNER, 2000);
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
                case ACTION_WARRIOR:
                {
                    me->MonsterSay("For the Horde!", 0);
                    me->SetWalk(false);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 53008);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    events.ScheduleEvent(EVENT_CLEAVE, 2000);
                    events.ScheduleEvent(EVENT_CHECK_OWNER, 2000);
                    evadeForced = false;
                    break;
                }
                case ACTION_SHAMAN:
                {
                    me->SetWalk(false);
                    me->MonsterSay("For the Horde!", 0);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 29410);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    events.ScheduleEvent(EVENT_HEAL_PLAYER, 1000);
                    events.ScheduleEvent(EVENT_CHECK_OWNER, 2000);
                    evadeForced = false;
                    break;
                }
                default:
                    break;
            }
        }

        protected:
            bool evadeForced;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_dragonmaw_civilianAI(creature);
    }
};

class npc_th_dragonmaw_portal_to_orgrimmar : public CreatureScript
{
public:
    npc_th_dragonmaw_portal_to_orgrimmar() : CreatureScript("npc_th_dragonmaw_portal_to_orgrimmar")
    {
    }

    enum eventId
    {
        EVENT_TELEPORT_PLAYER   = 1
    };

    enum spellId
    {
        SPELL_TELEPORT_ORGRIMMAR    = 82450
    };

    enum questId
    {
        QUEST_THE_WARCHIEF_WILL_BE_PLEASED   = 26798
    };

    struct npc_th_dragonmaw_portal_to_orgrimmarAI : public ScriptedAI
    {
        npc_th_dragonmaw_portal_to_orgrimmarAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void InitializeAI()
        {
            events.ScheduleEvent(EVENT_TELEPORT_PLAYER, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TELEPORT_PLAYER:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 4.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(4.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                            {
                                if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_WARCHIEF_WILL_BE_PLEASED) == QUEST_STATUS_COMPLETE ||
                                    (*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_WARCHIEF_WILL_BE_PLEASED) == QUEST_STATUS_REWARDED)
                                    (*itr)->CastSpell((*itr), SPELL_TELEPORT_ORGRIMMAR, true);
                            }
                        }
                        events.ScheduleEvent(EVENT_TELEPORT_PLAYER, 2000);
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
        return new npc_th_dragonmaw_portal_to_orgrimmarAI(creature);
    }
};

class npc_th_salvageable_shredder : public CreatureScript
{
public:
    npc_th_salvageable_shredder() : CreatureScript("npc_th_salvageable_shredder")
    {
    }

    enum eventId
    {
        EVENT_CHECK_HEALTH      = 1,
        EVENT_SUMMON_AMBUSHERS
    };

    enum spellId
    {
        SPELL_FEIGN_DEATH       = 51329,
        SPELL_SIGNAL_FLARE      = 70048,
        SPELL_REPAIRS           = 85910,
        SPELL_SUMMON_SKIRMISHER = 85899
    };

    enum questId
    {
        QUEST_MO_BETTER_SHREDDER    = 27622
    };

    enum npcId
    {
        NPC_BILGEWATER_EXPERT   = 46112
    };

    enum creditID
    {
        QUEST_CREDIT_DISCOVERED     = 46108,
        QUEST_CREDIT_REPAIRED       = 46109
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_MO_BETTER_SHREDDER) == QUEST_STATUS_INCOMPLETE)
        {
            player->MonsterTextEmote("This shredder looks like it can be repaired. You fire off a signal.", player->GetGUID());
            player->CastSpell(player, SPELL_SIGNAL_FLARE, true);
            player->KilledMonsterCredit(QUEST_CREDIT_DISCOVERED);
            player->SummonCreature(NPC_BILGEWATER_EXPERT, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ() + 30, player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            return true;
        }
        return false;
    }

    struct npc_th_salvageable_shredderAI : public ScriptedAI
    {
        npc_th_salvageable_shredderAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetHealth(me->GetMaxHealth() * 0.015f);
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_REPAIRS:
                {
                    events.ScheduleEvent(EVENT_SUMMON_AMBUSHERS, 8000);
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
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealth() >= me->GetMaxHealth() * 0.57f)
                        {
                            me->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);

                            TalkWithDelay(6000, 0);

                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 45.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(45.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                                    (*itr)->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_REPAIRED);
                            }

                            if (Creature* expert = me->FindNearestCreature(NPC_BILGEWATER_EXPERT, 45.0f, true))
                            {
                                expert->AI()->Talk(2);
                                expert->DespawnOrUnsummon(15000);
                                expert->SetStandState(UNIT_STAND_STATE_STAND);
                            }

                            events.CancelEvent(EVENT_SUMMON_AMBUSHERS);
                            events.CancelEvent(EVENT_CHECK_HEALTH);
                            me->DespawnOrUnsummon(15000);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_HEALTH, 2000);
                        break;
                    }
                    case EVENT_SUMMON_AMBUSHERS:
                    {
                        DoCast(SPELL_SUMMON_SKIRMISHER);
                        events.RescheduleEvent(EVENT_SUMMON_AMBUSHERS, 10000);
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
        return new npc_th_salvageable_shredderAI(creature);
    }
};

class npc_th_bilgewater_expert : public CreatureScript
{
public:
    npc_th_bilgewater_expert() : CreatureScript("npc_th_bilgewater_expert")
    {
    }

    enum eventId
    {
        EVENT_CHECK_HEALTH      = 1,
        EVENT_CHECK_PARACHUTE
    };

    enum spellId
    {
        SPELL_PARACHUTE     = 70988,
        SPELL_REPAIRS       = 85910
    };

    enum npcId
    {
        NPC_BILGEWATER_EXPERT   = 46112,
        NPC_SHREDDER            = 46100
    };

    struct npc_th_bilgewater_expertAI : public ScriptedAI
    {
        npc_th_bilgewater_expertAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->AddAura(SPELL_PARACHUTE, me);
            events.ScheduleEvent(EVENT_CHECK_PARACHUTE, 5000);
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PARACHUTE:
                    {
                        if (Creature* shredder = me->FindNearestCreature(NPC_SHREDDER, 50.0f, true))
                        {
                            me->RemoveAurasDueToSpell(SPELL_PARACHUTE);
                            DoCast(shredder, SPELL_REPAIRS);
                            Talk(0);
                            TalkWithDelay(8000, 1);
                            me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
                        }
                        events.CancelEvent(EVENT_CHECK_PARACHUTE);
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
        return new npc_th_bilgewater_expertAI(creature);
    }
};

class npc_th_mortar_beach_triggering : public CreatureScript
{
public:
    npc_th_mortar_beach_triggering() : CreatureScript("npc_th_mortar_beach_triggering")
    {
    }

    enum npcId
    {
        NPC_ENTRY_MORTAR_GROUND     = 35845,
        NPC_BLACKSCALE_RAIDER       = 45984
    };

    enum spellId
    {
        SPELL_INCOMING_ARTILLERY    = 84841,
        SPELL_ARTILLERY_LAUNCH      = 84858,
        SPELL_ART_IMPACT            = 84864,
        SPELL_ART_INCOMING          = 84841
    };

    struct npc_th_mortar_beach_triggeringAI : public ScriptedAI
    {
        npc_th_mortar_beach_triggeringAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SELECT_VICTIM     = 1,
            EVENT_SUMMON_NAGA
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SELECT_VICTIM, 1);
            switch (me->GetGUIDLow())
            {
                case 763978:
                case 736966:
                case 763962:
                case 763972:
                    events.ScheduleEvent(EVENT_SUMMON_NAGA, 2000);
                    break;
                default:
                    break;
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
                case SPELL_ART_IMPACT:
                {
                    me->RemoveAurasDueToSpell(SPELL_ART_INCOMING);
                    break;
                }
                default:
                    break;
            }
        }

        void SelectGroundPoint()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ENTRY_MORTAR_GROUND, 300.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (roll_chance_f(0.25f))
                    (*iter)->CastSpell(me, SPELL_ARTILLERY_LAUNCH, true);
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
                        events.RescheduleEvent(EVENT_SELECT_VICTIM, urand(15000, 30000));
                        break;
                    }
                    case EVENT_SUMMON_NAGA:
                    {
                        me->SummonCreature(NPC_BLACKSCALE_RAIDER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(),TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.RescheduleEvent(EVENT_SUMMON_NAGA, urand(30000, 45000));
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
        return new npc_th_mortar_beach_triggeringAI(creature);
    }
};

class npc_th_krazzwork_fighters : public CreatureScript
{
public:
    npc_th_krazzwork_fighters() : CreatureScript("npc_th_krazzwork_fighters")
    {
    }

    struct npc_th_krazzwork_fightersAI : public ScriptedAI
    {
        npc_th_krazzwork_fightersAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_SEARCH_FOR_ENEMY = 1
        };

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_FOR_ENEMY, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
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
                    case EVENT_SEARCH_FOR_ENEMY:
                    {
                        if (Unit* victim = me->SelectNearestTarget(10.0f))
                        {
                            AttackStart(victim);
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
        return new npc_th_krazzwork_fightersAI(creature);
    }
};

class npc_th_fathom_lotd_heth_jatar : public CreatureScript
{
public:
    npc_th_fathom_lotd_heth_jatar() : CreatureScript("npc_th_fathom_lotd_heth_jatar")
    {
    }

    struct npc_th_fathom_lotd_heth_jatarAI : public ScriptedAI
    {
        npc_th_fathom_lotd_heth_jatarAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_START_ARTILLERY   = 1,
            EVENT_IMPALING_PULL,
            EVENT_MORTAL_STRIKE
        };

        enum spellId
        {
            SPELL_MORTAL_STRIKE     = 13737,
            SPELL_IMPALING_PULL     = 82742,
            SPELL_BATTLE_SHOUT      = 32064,
            SPELL_ART_INCOMING      = 84841,
            SPELL_ART_IMPACT        = 84864
        };

        enum questId
        {
            QUEST_BLAST_HIM     = 27606
        };

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->DespawnOrUnsummon(1000);
            events.Reset();
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_IMPALING_PULL, 1000);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (!me->HasAura(SPELL_BATTLE_SHOUT))
                DoCast(me, SPELL_BATTLE_SHOUT, true);

            events.ScheduleEvent(EVENT_START_ARTILLERY, 20000);
            events.ScheduleEvent(EVENT_MORTAL_STRIKE, 3000);
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
                    case EVENT_MORTAL_STRIKE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_MORTAL_STRIKE, true);
                        events.RescheduleEvent(EVENT_MORTAL_STRIKE, urand(6000, 8000));
                        break;
                    }
                    case EVENT_IMPALING_PULL:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER && (*itr)->isAlive())
                            {
                                if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_BLAST_HIM) == QUEST_STATUS_INCOMPLETE)
                                {
                                    DoCast((*itr), SPELL_IMPALING_PULL, true);
                                    (*itr)->GetMotionMaster()->MoveJump(me->GetPositionX() - 1, me->GetPositionY() - 1, me->GetPositionZ(), 25.0f, 5.0f, 0);
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_IMPALING_PULL, urand(15000, 25000));
                        break;
                    }
                    case EVENT_START_ARTILLERY:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 25.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(25.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->GetEntry() == 46015)
                            {
                                if ((*itr)->HasAura(SPELL_ART_INCOMING))
                                    continue;

                                (*itr)->AddAura(SPELL_ART_INCOMING, (*itr));
                                (*itr)->CastWithDelay(urand(5000, 7500), (*itr), SPELL_ART_IMPACT, true);
                            }
                        }
                        Talk(0);
                        events.RescheduleEvent(EVENT_START_ARTILLERY, 20000);
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
        return new npc_th_fathom_lotd_heth_jatarAI(creature);
    }
};

class npc_th_krazzworks_laborer : public CreatureScript
{
public:
    npc_th_krazzworks_laborer() : CreatureScript("npc_th_krazzworks_laborer")
    {
    }

    struct npc_th_krazzworks_laborerAI : public ScriptedAI
    {
        npc_th_krazzworks_laborerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_EMERGENCY_POOL_PONY   = 92317,
            SPELL_POOL_PONY             = 92335,
            SPELL_DROWNING              = 89662
        };

        enum creditId
        {
            QUEST_CREDIT_RESCUED    = 49548
        };

        enum eventId
        {
            EVENT_RANDOM_TALK   = 1
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_EMERGENCY_POOL_PONY:
                {
                    if (!me->HasAura(SPELL_DROWNING))
                        break;

                    if (!caster)
                        break;

                    TalkWithDelay(1500, 1, caster->GetGUID());
                    me->RemoveAurasDueToSpell(SPELL_DROWNING);
                    me->CastWithDelay(500, me, SPELL_POOL_PONY, true);
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_RESCUED);
                    me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 0.1f, 10.0f, 2.0f, 0);
                    me->DespawnOrUnsummon(15000);
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
                    case EVENT_RANDOM_TALK:
                    {
                        Talk(0);
                        events.RescheduleEvent(EVENT_RANDOM_TALK, urand(15000, 4500));
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
        return new npc_th_krazzworks_laborerAI(creature);
    }
};

class npc_th_thundermar_war_gryphon : public CreatureScript
{
public:
    npc_th_thundermar_war_gryphon() : CreatureScript("npc_th_thundermar_war_gryphon")
    {
    }

    struct npc_th_thundermar_war_gryphonAI : public ScriptedAI
    {
        npc_th_thundermar_war_gryphonAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        enum spellId
        {
            SPELL_BARBED_FLESHOOK   = 87937
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_BARBED_FLESHOOK:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        passenger->ExitVehicle();
                        if (passenger->GetTypeId() == TYPEID_UNIT && caster)
                        {
                            passenger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                            passenger->GetMotionMaster()->MoveJump(caster->GetPositionX() - 1, caster->GetPositionY() - 1, caster->GetPositionZ(), 25.0f, 25.0f, 0);
                            passenger->ToCreature()->AI()->AttackStart(caster);
                            passenger->ToCreature()->DespawnOrUnsummon(120000);
                        }
                    }
                    me->DespawnOrUnsummon(3000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_thundermar_war_gryphonAI(creature);
    }
};

class go_th_wildhammer_keg : public GameObjectScript
{
public:
    go_th_wildhammer_keg() : GameObjectScript("go_th_wildhammer_keg")
    {
    }

    enum questId
    {
        QUEST_TOTAL_WAR_D       = 28872,
        QUEST_TOTAL_WAR         = 27747
    };

    enum spellId
    {
        SPELL_DUSTY_EXPLOSION      = 85543
    };

    enum creditID
    {
        QUEST_CREDIT_KEG    = 46551
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_TOTAL_WAR) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_TOTAL_WAR_D) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, SPELL_DUSTY_EXPLOSION, true);
            player->KilledMonsterCredit(QUEST_CREDIT_KEG);
            go->DestroyForPlayer(player);
            return true;
        }
        return false;
    }
};

class npc_th_grisly_gryphon_guts : public CreatureScript
{
public:
    npc_th_grisly_gryphon_guts() : CreatureScript("npc_th_grisly_gryphon_guts")
    {
    }

    struct npc_th_grisly_gryphon_gutsAI : public ScriptedAI
    {
        npc_th_grisly_gryphon_gutsAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        enum npcId
        {
            NPC_HIGHLAND_BLACK_DRAKE    = 47391
        };

        enum spellId
        {
            SPELL_BLOODY_EXPLOSION  = 86438
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_BLOODY_EXPLOSION, true);
            owner->SummonCreature(NPC_HIGHLAND_BLACK_DRAKE, -4381.36f, -4961.17f, 174.14f, 1.40f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_grisly_gryphon_gutsAI(creature);
    }
};

class npc_th_highland_black_drake : public CreatureScript
{
public:
    npc_th_highland_black_drake() : CreatureScript("npc_th_highland_black_drake")
    {
    }

    struct npc_th_highland_black_drakeAI : public ScriptedAI
    {
        npc_th_highland_black_drakeAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum npcId
        {
            NPC_HIGHLAND_BLACK_DRAKE    = 47422
        };

        enum spellId
        {
            SPELL_FLAME_BREATH  = 8873
        };

        enum pointId
        {
            POINT_OWNER     = 1,
            POINT_LAND
        };

        enum eventId
        {
            EVENT_LAND          = 1,
            EVENT_HP_35,
            EVENT_FLAME_BREATH
        };

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_OWNER:
                {
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                }
                case POINT_LAND:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_HP_35, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            x = owner->GetPositionX();
            y = owner->GetPositionY();
            z = owner->GetPositionZ();

            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MovePoint(POINT_OWNER, x, y - 1, z + 5);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void EnterCombat(Unit* who)
        {
            if (me->ToTempSummon())
                Talk(0, who->GetGUID());
            events.ScheduleEvent(EVENT_FLAME_BREATH, 2000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
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
                    case EVENT_LAND:
                    {
                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_HP_35:
                    {
                        if (me->GetHealth() <= me->GetMaxHealth() * 0.35f)
                        {
                            me->setFaction(35);
                            DoStopAttack();
                            me->CastStop();
                            if (me->ToTempSummon())
                            {
                                if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                                {
                                    invoker->SummonCreature(NPC_HIGHLAND_BLACK_DRAKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+2, me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                                    TalkWithDelay(2500, 1, invoker->GetGUID());
                                    me->SetVisible(false);
                                    me->DespawnOrUnsummon(8000);
                                    events.CancelEvent(EVENT_HP_35);
                                }
                                else
                                    me->DespawnOrUnsummon(1);
                            }
                            break;
                        }
                        events.RescheduleEvent(EVENT_HP_35, 1000);
                        break;
                    }
                    case EVENT_FLAME_BREATH:
                    {
                        DoCast(SPELL_FLAME_BREATH);
                        events.RescheduleEvent(EVENT_FLAME_BREATH, urand(6000, 12000));
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_highland_black_drakeAI(creature);
    }
};

class npc_th_highland_black_drake_cinematic : public CreatureScript
{
public:
    npc_th_highland_black_drake_cinematic() : CreatureScript("npc_th_highland_black_drake_cinematic")
    {
    }

    struct npc_th_highland_black_drake_cinematicAI : public npc_escortAI
    {
        npc_th_highland_black_drake_cinematicAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_DEMON_CHAIN           = 88780
        };

        enum actionId
        {
            ACTION_WP_START     = 1,
            ACTION_RIDE_OWNER
        };

        enum pointId
        {
            POINT_LAND      = 9,
            POINT_DRAKE,
            POINT_AWAY
        };

        enum eventId
        {
            EVENT_LAND              = 1,
            EVENT_SUMMON_ACTORS,
            EVENT_MOVE_ACTORS,
            EVENT_TALK_ACTORS,
            EVENT_RUN_NARKRALL,
            EVENT_RUN_ZAELA,
            EVENT_FINISH
        };

        enum npcId
        {
            NPC_ZAELA       = 47557,
            NPC_NARKRALL    = 47559
        };

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
            owner->AddAura(60191, owner);
            me->AddAura(60191, me);
            owner->CastSpell(me, 63313, true);
            DoAction(ACTION_WP_START);
        }

        void EnterEvadeMode()
        {
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 8:
                {
                    if (me->ToTempSummon())
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->CastSpell(me, 63314, true);
                    }
                    events.ScheduleEvent(EVENT_LAND, 100);
                    events.ScheduleEvent(EVENT_SUMMON_ACTORS, 2500);
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
                    me->SetWalk(false);
                    Start(false, true, NULL, NULL, false, true);
                    me->SetSpeed(MOVE_FLIGHT, 2.45f, true);
                    me->SetSpeed(MOVE_RUN, 2.45f, true);
                    SetDespawnAtEnd(false);
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
                    case EVENT_LAND:
                    {
                        x = -3687.15f;
                        y = -5291.71f;
                        z = 38.47f;

                        Position const moveLand = { x, y, z };
                        me->SetFacingTo(2.88f);
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_SUMMON_ACTORS:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            invoker->SummonCreature(NPC_NARKRALL, -3717.79f, -5281.91f, 37.23f, 6.10f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                            invoker->SummonCreature(NPC_ZAELA, -3718.50f, -5285.76f, 37.30f, 6.10f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                        }
                        events.ScheduleEvent(EVENT_MOVE_ACTORS, 2000);
                        events.CancelEvent(EVENT_SUMMON_ACTORS);
                        break;
                    }
                    case EVENT_MOVE_ACTORS:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_NARKRALL:
                                    {
                                        (*itr)->AddAura(60191, (*itr));
                                        (*itr)->SetWalk(false);
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_DRAKE, -3700.13f, -5285.53f, 35.76f);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(2000, 0);
                                        (*itr)->CastWithDelay(4500, me, SPELL_DEMON_CHAIN);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(8000, 1);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(26000, 2);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(40000, 3);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(54000, 4);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(64000, 5);
                                        events.ScheduleEvent(EVENT_RUN_NARKRALL, 68000);
                                        (*itr)->ToCreature()->DespawnOrUnsummon(75000);
                                        break;
                                    }
                                    case NPC_ZAELA:
                                    {
                                        (*itr)->AddAura(60191, (*itr));
                                        (*itr)->SetWalk(false);
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_DRAKE, -3702.60f, -5290.39f, 35.76f);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(14000, 0);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(20000, 1);
                                        events.ScheduleEvent(EVENT_TALK_ACTORS, 25000);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(32000, 2);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(46000, 3);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(70000, 4);
                                        events.ScheduleEvent(EVENT_RUN_ZAELA, 75000);
                                        (*itr)->ToCreature()->DespawnOrUnsummon(80000);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_MOVE_ACTORS);
                        break;
                    }
                    case EVENT_TALK_ACTORS:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_NARKRALL:
                                    {
                                        (*itr)->CastStop();
                                        (*itr)->SetFacingTo(4.78f);
                                        break;
                                    }
                                    case NPC_ZAELA:
                                    {
                                        (*itr)->SetFacingTo(1.63f);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_TALK_ACTORS);
                        break;
                    }
                    case EVENT_RUN_NARKRALL:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_NARKRALL:
                                    {
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_AWAY, -3727.79f, -5298.61f, 35.79f);
                                        break;
                                    }
                                    case NPC_ZAELA:
                                    {
                                        (*itr)->SetFacingTo(3.29f);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_RUN_NARKRALL);
                        break;
                    }
                    case EVENT_RUN_ZAELA:
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_ZAELA:
                                    {
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_AWAY, -3727.79f, -5298.61f, 35.79f);
                                        events.ScheduleEvent(EVENT_FINISH, 2000);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_RUN_NARKRALL);
                        break;
                    }
                    case EVENT_FINISH:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            if (invoker->GetTypeId() != TYPEID_PLAYER)
                                break;

                            invoker->ToPlayer()->KilledMonsterCredit(47416);
                            invoker->CastSpell(invoker, 100025, true);
                            invoker->RemoveAurasDueToSpell(60191);
                            invoker->NearTeleportTo(-3694.74f, -5303.68f, 35.77f, 2.67f);
                            invoker->ExitVehicle();
                            me->DespawnOrUnsummon(3000);
                        }
                        events.CancelEvent(EVENT_FINISH);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool wpInProgress;
        float x, y, z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_highland_black_drake_cinematicAI(creature);
    }
};

class npc_th_torth_zaela : public CreatureScript
{
public:
    npc_th_torth_zaela() : CreatureScript("npc_th_torth_zaela")
    {
    }

    struct npc_th_torth_zaelaAI : public ScriptedAI
    {
        npc_th_torth_zaelaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum npcId
        {
            NPC_ZAELA   = 47671
        };

        enum spellId
        {
            SPELL_FLAME_BREATH  = 37638,
            SPELL_DEMON_CHAIN   = 88780
        };

        enum pointId
        {
            POINT_OWNER = 1,
            POINT_LAND
        };

        enum eventId
        {
            EVENT_LAND              = 1,
            EVENT_FLAME_BREATH,
            EVENT_DEMON_CHAIN
        };

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_OWNER:
                {
                    events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                }
                case POINT_LAND:
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->SetHomePosition(-3498.74f, -4369.45f, 210.49f, 2.35f);
                    if (alreadyTalked == false)
                    {
                        Talk(0);
                        alreadyTalked = true;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            alreadyTalked = false;
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MovePoint(POINT_OWNER, -3491.52f, -4377.88f, 214.81f);
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_FLAME_BREATH, 8000);
            events.ScheduleEvent(EVENT_DEMON_CHAIN, 12500);
            me->AddAura(49416, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->ToPlayer()->KilledMonsterCredit(me->GetEntry());
            }

            if (Creature* zaela = me->FindNearestCreature(NPC_ZAELA, 200.0f))
                zaela->AI()->Talk(3);

            me->DespawnOrUnsummon(6000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->DespawnOrUnsummon(2000);
            events.Reset();
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
                    case EVENT_LAND:
                    {
                        x = -3491.52f;
                        y = -4377.88f;
                        z = 210.49f;

                        Position const moveLand = { x, y, z };
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        events.CancelEvent(EVENT_LAND);
                        break;
                    }
                    case EVENT_FLAME_BREATH:
                    {
                        DoCast(SPELL_FLAME_BREATH);
                        events.RescheduleEvent(EVENT_FLAME_BREATH, urand(6000, 15000));
                        break;
                    }
                    case EVENT_DEMON_CHAIN:
                    {
                        if (Creature* zaela = me->FindNearestCreature(NPC_ZAELA, 200.0f, true))
                        {
                            zaela->SetReactState(REACT_PASSIVE);
                            zaela->AI()->Talk(1);
                            zaela->AI()->TalkWithDelay(16000, 2);
                            TalkWithDelay(10000, 1);
                            zaela->AI()->DoCast(me, SPELL_DEMON_CHAIN);
                            me->AddAura(SPELL_DEMON_CHAIN, me);
                        }
                        events.CancelEvent(EVENT_DEMON_CHAIN);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        protected:
            float x, y, z;
            bool alreadyTalked;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_torth_zaelaAI(creature);
    }
};

class npc_th_zaela_at_cave : public CreatureScript
{
public:
    npc_th_zaela_at_cave() : CreatureScript("npc_th_zaela_at_cave")
    {
    }

    enum questId
    {
        QUEST_FURY_UNBOUND  = 28133
    };

    enum npcId
    {
        NPC_TORTH   = 47669
    };

    #define GOSSIP_TORTH    "I am ready to fight Torth!"

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_FURY_UNBOUND) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TORTH, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_FURY_UNBOUND) == QUEST_STATUS_INCOMPLETE)
            {
                Creature* torth = player->FindNearestCreature(NPC_TORTH, 200.0f, true);
                if (!torth)
                {
                    creature->AI()->Talk(0, player->GetGUID());
                    player->SummonCreature(NPC_TORTH, -3473.09f, -4418.12f, 229.95f, 1.92f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
        return false;
    }
};

class npc_th_uchek_in_cave : public CreatureScript
{
public:
    npc_th_uchek_in_cave() : CreatureScript("npc_th_uchek_in_cave")
    {
    }

    enum questId
    {
        QUEST_NIGHT_TERRORS     = 28170
    };

    enum spellId
    {
        SPELL_SPIRIT_REALM = 88981
    };

    #define GOSSIP_UCHEK    "I am ready, Uchek!"

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UCHEK, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE)
            {
                creature->CastSpell(player, SPELL_SPIRIT_REALM, true);
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
        return false;
    }
};

class areatrigger_th_first_shrine : public AreaTriggerScript
{
public:
    areatrigger_th_first_shrine() : AreaTriggerScript("at_th_first_shrine")
    {
    }

    enum questId
    {
        QUEST_NIGHT_TERRORS = 28170
    };

    enum spellId
    {
        SPELL_SPIRIT_REALM      = 88981,
        SPELL_PURIFYING_LIGHT   = 88983,
        SPELL_HOLY_FIRE         = 17140,
        SPELL_HOLY_NOVA         = 35740
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        /*if (player->isAlive() && player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE && player->HasAura(SPELL_SPIRIT_REALM))
        {
            player->KilledMonsterCredit(47838);

            player->CastSpell(player, SPELL_PURIFYING_LIGHT, true);
            player->CastSpell(player, SPELL_HOLY_NOVA, true);
        }
        if (player->isAlive() && player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_COMPLETE)
            player->RemoveAurasDueToSpell(SPELL_SPIRIT_REALM);*/
        return false;
    }
};

class areatrigger_th_second_shrine : public AreaTriggerScript
{
public:
    areatrigger_th_second_shrine() : AreaTriggerScript("at_th_second_shrine")
    {
    }

    enum questId
    {
        QUEST_NIGHT_TERRORS     = 28170
    };

    enum spellId
    {
        SPELL_SPIRIT_REALM      = 88981,
        SPELL_PURIFYING_LIGHT   = 88983,
        SPELL_HOLY_FIRE         = 17140,
        SPELL_HOLY_NOVA         = 35740
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        /*if (player->isAlive() && player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE && player->HasAura(SPELL_SPIRIT_REALM))
        {
            player->KilledMonsterCredit(47839);

            player->CastSpell(player, SPELL_PURIFYING_LIGHT, true);
            player->CastSpell(player, SPELL_HOLY_NOVA);
        }
        if (player->isAlive() && player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_COMPLETE)
            player->RemoveAurasDueToSpell(SPELL_SPIRIT_REALM);*/
        return false;
    }
};

class areatrigger_th_third_shrine : public AreaTriggerScript
{
public:
    areatrigger_th_third_shrine() : AreaTriggerScript("at_th_third_shrine")
    {
    }

    enum questId
    {
        QUEST_NIGHT_TERRORS = 28170
    };

    enum spellId
    {
        SPELL_SPIRIT_REALM      = 88981,
        SPELL_PURIFYING_LIGHT   = 88983,
        SPELL_HOLY_FIRE         = 17140,
        SPELL_HOLY_NOVA         = 35740
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        /*if (player->isAlive() && player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE && player->HasAura(SPELL_SPIRIT_REALM))
        {
            player->KilledMonsterCredit(47840);

            player->CastSpell(player, SPELL_PURIFYING_LIGHT, true);
            player->CastSpell(player, SPELL_HOLY_NOVA, true);
        }
        if (player->isAlive() && player->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_COMPLETE)
            player->RemoveAurasDueToSpell(SPELL_SPIRIT_REALM);*/
        return false;
    }
};

class spell_th_purifying_light : public SpellScriptLoader
{
public:
    spell_th_purifying_light() : SpellScriptLoader("spell_th_purifying_light")
    {
    }

    class spell_th_purifying_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_purifying_light_SpellScript);

        enum triggerId
        {
            NPC_GENERIC_AREATRIGGER     = 4
        };

        enum triggerGUID
        {
            AREATRIGGER_3   = 706656,
            AREATRIGGER_2   = 706655,
            AREATRIGGER_1   = 706654
        };

        enum spellId
        {
            SPELL_SPIRIT_REALM      = 88981,
            SPELL_HOLY_FIRE         = 17140,
            SPELL_HOLY_NOVA         = 35740
        };

        enum questId
        {
            QUEST_NIGHT_TERRORS     = 28170
        };

        enum creditID
        {
            CREDIT_THIRD_SHRINE     = 47840,
            CREDIT_SECOND_SHRINE    = 47839,
            CREDIT_FIRST_SHRINE     = 47838
        };

        void CheckTrigger()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (Creature* shrine = caster->FindNearestCreature(NPC_GENERIC_AREATRIGGER, 10.0f, true))
                {
                    switch (shrine->GetGUIDLow())
                    {
                        case AREATRIGGER_3:
                        {
                            if (caster->isAlive() && caster->ToPlayer()->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE && caster->HasAura(SPELL_SPIRIT_REALM))
                            {
                                caster->ToPlayer()->KilledMonsterCredit(CREDIT_THIRD_SHRINE);
                                caster->CastSpell(caster, SPELL_HOLY_NOVA, true);
                            }
                            if (caster->isAlive() && caster->ToPlayer()->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_COMPLETE)
                                caster->RemoveAurasDueToSpell(SPELL_SPIRIT_REALM);
                            break;
                        }
                        case AREATRIGGER_2:
                        {
                            if (caster->isAlive() && caster->ToPlayer()->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE && caster->HasAura(SPELL_SPIRIT_REALM))
                            {
                                caster->ToPlayer()->KilledMonsterCredit(CREDIT_SECOND_SHRINE);
                                caster->CastSpell(caster, SPELL_HOLY_NOVA, true);
                            }
                            if (caster->isAlive() && caster->ToPlayer()->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_COMPLETE)
                                caster->RemoveAurasDueToSpell(SPELL_SPIRIT_REALM);
                            break;
                        }
                        case AREATRIGGER_1:
                        {
                            if (caster->isAlive() && caster->ToPlayer()->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_INCOMPLETE && caster->HasAura(SPELL_SPIRIT_REALM))
                            {
                                caster->ToPlayer()->KilledMonsterCredit(CREDIT_FIRST_SHRINE);
                                caster->CastSpell(caster, SPELL_HOLY_NOVA, true);
                            }
                            if (caster->isAlive() && caster->ToPlayer()->GetQuestStatus(QUEST_NIGHT_TERRORS) == QUEST_STATUS_COMPLETE)
                                caster->RemoveAurasDueToSpell(SPELL_SPIRIT_REALM);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_th_purifying_light_SpellScript::CheckTrigger);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_purifying_light_SpellScript();
    }
};  

class npc_th_warlord_krogg_pass : public CreatureScript
{
public:
    npc_th_warlord_krogg_pass() : CreatureScript("npc_th_warlord_krogg_pass")
    {
    }

    enum questId
    {
        QUEST_IF_THE_KEY_FITS   = 28092,
        QUEST_PRESSING_FORWARD  = 28093
    };

    enum npcId
    {
        NPC_PATCH   = 47374
    };

    enum spellId
    {
        SPELL_SUMMON_VOLT       = 88380,
        SPELL_SUMMON_TICKER     = 88381,
        SPELL_SUMMON_PATCH      = 88382,
        SPELL_SUMMON_NEWT       = 88383,
        SPELL_SUMMON_GRIT       = 88384
    };


    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_IF_THE_KEY_FITS)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 800.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(800.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && (*itr)->GetEntry() == NPC_PATCH)
                        return false;
                }
            }
            player->CastSpell(player, SPELL_SUMMON_VOLT, true);
            player->CastSpell(player, SPELL_SUMMON_TICKER, true);
            player->CastSpell(player, SPELL_SUMMON_PATCH, true);
            player->CastSpell(player, SPELL_SUMMON_NEWT, true);
            player->CastSpell(player, SPELL_SUMMON_GRIT, true);
            creature->AI()->TalkWithDelay(5000, 0);
            return false;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_IF_THE_KEY_FITS) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUADRON, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_IF_THE_KEY_FITS) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_PRESSING_FORWARD) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(player, 800.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                player->VisitNearbyObject(800.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                    {
                        if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player && (*itr)->GetEntry() == NPC_PATCH)
                            return false;
                    }
                }
                player->CastSpell(player, SPELL_SUMMON_VOLT, true);
                player->CastSpell(player, SPELL_SUMMON_TICKER, true);
                player->CastSpell(player, SPELL_SUMMON_PATCH, true);
                player->CastSpell(player, SPELL_SUMMON_NEWT, true);
                player->CastSpell(player, SPELL_SUMMON_GRIT, true);
                creature->AI()->TalkWithDelay(5000, 0);
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
        return false;
    }

    struct npc_th_warlord_krogg_passAI : public ScriptedAI
    {
        npc_th_warlord_krogg_passAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                damage = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_warlord_krogg_passAI(creature);
    }
};

class npc_th_lady_cozwynn : public CreatureScript
{
public:
    npc_th_lady_cozwynn() : CreatureScript("npc_th_lady_cozwynn")
    {
    }

    enum questId
    {
        QUEST_UP_TO_THE_CITADEL = 27503
    };

    enum npcId
    {
        NPC_KOR_KRON_ASSASSIN   = 46118,
        NPC_KOR_KRON_COMMANDER  = 46119
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_UP_TO_THE_CITADEL)
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 1000.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(1000.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == player)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_KOR_KRON_ASSASSIN:
                            case NPC_KOR_KRON_COMMANDER:
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            player->SummonCreature(NPC_KOR_KRON_COMMANDER, -4405.81f, -4489.62f, 207.40f, 4.01f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_KOR_KRON_ASSASSIN, -4401.98f, -4485.24f, 208.48f, 4.07f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_KOR_KRON_ASSASSIN, -4402.36f, -4488.41f, 207.13f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_KOR_KRON_ASSASSIN, -4404.51f, -4484.88f, 209.17f, 4.34f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_KOR_KRON_ASSASSIN, -4407.97f, -4485.52f, 209.65f, 4.34f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_KOR_KRON_ASSASSIN, -4406.22f, -4483.34f, 210.29f, 4.74f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return false;
        }
        return true;
    }
};

class npc_th_jon_jon_jellyneck : public CreatureScript
{
public:
    npc_th_jon_jon_jellyneck() : CreatureScript("npc_th_jon_jon_jellyneck")
    {
    }

    enum questId
    {
        QUEST_KOR_KRON_DROP     = 27491
    };

    enum spellId
    {
        SPELL_SUMMON_CRUSHBLOW_WINDRIDER    = 85631
    };

    enum creditId
    {
        QUEST_CREDIT_KOR_KRON   = 45902
    };

    enum npcId
    {
        NPC_CRUSHBLOW_WINDRIDER     = 45942
    };

    #define GOSSIP_KOR_KRON "Jon-Jon, I'm here to lead your wind rider squad and drop off the Kor'kron assassins."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_KOR_KRON_DROP) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, player, NPC_CRUSHBLOW_WINDRIDER, 300.0f);
                if (!creatures.empty())
                {
                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == player)
                        {
                            player->PlayerTalkClass->SendCloseGossip();
                            return true;
                        }
                    }
                }

                // Need 5 gryphons!
                for (uint32 gryphons = 0; gryphons < 5; ++gryphons)
                    player->CastSpell(player, SPELL_SUMMON_CRUSHBLOW_WINDRIDER, true);

                player->KilledMonsterCredit(QUEST_CREDIT_KOR_KRON);
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_KOR_KRON_DROP) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_KOR_KRON, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }
};

class npc_th_kor_kron_commander : public CreatureScript
{
public:
    npc_th_kor_kron_commander() : CreatureScript("npc_th_kor_kron_commander")
    {
    }

    enum actionId
    {
        ACTION_WP_START         = 1,
        ACTION_ATTACK_AND_DIE
    };

    enum questId
    {
        QUEST_UP_TO_THE_CITADEL     = 27503
    };

    enum eventId
    {
        EVENT_START_WP          = 1,
        EVENT_QUEST_COMPLETE,
        EVENT_ENABLE_CHOGALL,
        EVENT_ADJUST_CHOGALL,
        EVENT_DIE
    };

    enum creditId
    {
        CREDIT_TALK_COMMANDER   = 46117,
        CREDIT_ESCORT_COMPLETE  = 46121
    };

    enum npcId
    {
        NPC_CHOGALL             = 46137,
        NPC_KOR_KRON_ASSASSIN   = 46118
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_UP_TO_THE_CITADEL) == QUEST_STATUS_INCOMPLETE)
            {
                creature->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                creature->AI()->DoAction(ACTION_WP_START);
                creature->setFaction(player->getFaction());
                player->KilledMonsterCredit(CREDIT_TALK_COMMANDER);
                return true;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_UP_TO_THE_CITADEL) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ESCORT_4, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_th_kor_kron_commanderAI : public npc_escortAI
    {
        npc_th_kor_kron_commanderAI(Creature* creature) : npc_escortAI(creature)
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
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER && me->ToTempSummon()->GetSummoner() == (*itr))
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_UP_TO_THE_CITADEL) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->KilledMonsterCredit(CREDIT_ESCORT_COMPLETE);
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 2:
                {
                    Talk(1);
                    if (me->ToTempSummon())
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                            invoker->SummonCreature(NPC_CHOGALL, -4474.40f, -4436.75f, 253.75f, 5.55f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)), true);
                    }
                    break;
                }
                case 4:
                {
                    Talk(2);
                    events.ScheduleEvent(EVENT_ENABLE_CHOGALL, 1000);
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
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    events.ScheduleEvent(EVENT_START_WP, 2500);
                    break;
                }
                case ACTION_ATTACK_AND_DIE:
                {
                    events.ScheduleEvent(EVENT_QUEST_COMPLETE, 1);
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
                        me->SetReactState(REACT_PASSIVE);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KOR_KRON_ASSASSIN, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*iter)->GetMotionMaster()->MoveFollow(me, urand(3, 6), urand(1, 4));
                            }
                        }
                        events.CancelEvent(EVENT_START_WP);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        CompleteAoE();
                        Talk(3);
                        me->RemoveAllAurasExceptType(SPELL_AURA_MOD_INVISIBILITY);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KOR_KRON_ASSASSIN, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*iter)->RemoveAllAurasExceptType(SPELL_AURA_MOD_INVISIBILITY);
                            }
                        }

                        me->GetMotionMaster()->MovePoint(2, -4473.67f, -4437.45f, 253.38f);
                        events.ScheduleEvent(EVENT_DIE, 1000);
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        break;
                    }
                    case EVENT_ENABLE_CHOGALL:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_CHOGALL, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                {
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(1000, 3);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(13000, 1);
                                    (*iter)->ToCreature()->AI()->TalkWithDelay(18000, 2);
                                    (*iter)->ToCreature()->CastWithDelay(10000, (*iter), 86027, true);
                                    (*iter)->DespawnOrUnsummon(25000);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 9000);
                        events.CancelEvent(EVENT_ENABLE_CHOGALL);
                        break;
                    }
                    case EVENT_DIE:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_KOR_KRON_ASSASSIN, 50.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == me->ToTempSummon()->GetSummoner())
                                    (*iter)->Kill((*iter), false);
                            }
                        }
                        me->Kill(me, false);
                        events.CancelEvent(EVENT_DIE);
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
        return new npc_th_kor_kron_commanderAI(creature);
    }
};

class npc_th_skyshredder_turret : public CreatureScript
{
public:
    npc_th_skyshredder_turret() : CreatureScript("npc_th_skyshredder_turret")
    {
    }

    enum questId
    {
        QUEST_OFF_THE_WALL  = 28591
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        Unit* passenger = creature->GetVehicleKit()->GetPassenger(0);
        if (!passenger)
        {
            if (player->GetQuestStatus(QUEST_OFF_THE_WALL) == QUEST_STATUS_INCOMPLETE)
                player->EnterVehicle(creature, 0);
            return true;
        }
        return true;
    }

    struct npc_th_skyshredder_turretAI : public ScriptedAI
    {
        npc_th_skyshredder_turretAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetControlled(true, UNIT_STATE_ROOT);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_th_skyshredder_turretAI(creature);
    }
};

class spell_th_place_ticker_explosives : public SpellScriptLoader
{
public:
    spell_th_place_ticker_explosives() : SpellScriptLoader("spell_th_place_ticker_explosives")
    {
    }

    class spell_th_place_ticker_explosives_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_th_place_ticker_explosives_SpellScript);

        enum Id
        {
            NPC_BOAT_TRIGGER    = 49381,
            NPC_KEEP_TRIGGER    = 49380,
            NPC_TOWER_TRIGGER   = 49144
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                Creature* boatTrigger = caster->FindNearestCreature(NPC_BOAT_TRIGGER, 10.0f, true);
                Creature* keepTrigger = caster->FindNearestCreature(NPC_KEEP_TRIGGER, 10.0f, true);
                Creature* towerTrigger = caster->FindNearestCreature(NPC_TOWER_TRIGGER, 10.0f, true);
                if (towerTrigger)
                {
                    caster->ToPlayer()->KilledMonsterCredit(NPC_TOWER_TRIGGER);
                    caster->CastWithDelay(4100, caster, 70966, true);
                    return SPELL_CAST_OK;
                }
                if (keepTrigger)
                {
                    caster->ToPlayer()->KilledMonsterCredit(NPC_KEEP_TRIGGER);
                    caster->CastWithDelay(4100, caster, 70966, true);
                    return SPELL_CAST_OK;
                }
                if (boatTrigger)
                {
                    caster->ToPlayer()->KilledMonsterCredit(NPC_BOAT_TRIGGER);
                    caster->CastWithDelay(4100, caster, 70966, true);
                    return SPELL_CAST_OK;
                }
            }
            return SPELL_FAILED_NOT_HERE;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_th_place_ticker_explosives_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_th_place_ticker_explosives_SpellScript();
    }
};

class go_th_induction_samophlange : public GameObjectScript
{
public:
    go_th_induction_samophlange() : GameObjectScript("go_th_induction_samophlange")
    {
    }

    enum questId
    {
        QUEST_OF_UTMOST_IMPORTANCE  = 28593
    };

    enum npcId
    {
        NPC_BLIGEWATER_PRISONER     = 49018
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_OF_UTMOST_IMPORTANCE) == QUEST_STATUS_INCOMPLETE)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, player, NPC_BLIGEWATER_PRISONER, 25.0f);
            if (!creatures.empty())
            {
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    if ((*iter))
                    {
                        switch ((*iter)->GetGUIDLow())
                        {
                            case 764258:
                                (*iter)->ToCreature()->AI()->Talk(0);
                                break;
                            case 764256:
                                (*iter)->ToCreature()->AI()->TalkWithDelay(6000, 1);
                                break;
                            case 764261:
                                (*iter)->ToCreature()->AI()->TalkWithDelay(12000, 2);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            return false;
        }

        return false;
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
    new npc_th_earthcaller_yevaa();
    new npc_th_brain_of_iso_rath();
    new npc_th_earthen_ring_gryphon_exit();
    new npc_th_vermillion_sentinel();
    new npc_th_lirastrasza_summoned();
    new npc_th_vermillion_mender();
    new spell_th_ruby_seeds();
    new npc_th_dragonmaw_pass_fighter();
    new npc_th_master_mathias_shaw();
    new npc_th_mathias_squadron();
    new npc_th_wyrms_bend_fighter();
    new areatrigger_th_grim_batol();
    new npc_th_lirastrasza_dq_event();
    new npc_th_dq_first_camera();
    new npc_th_alexstrasza_dq_first_event();
    new npc_th_calen_dq_first_event();
    new npc_th_dq_first_mirror();
    new npc_th_deathwing_dq_event();
    new npc_th_vermillion_summoner();
    new npc_th_vermillion_escort();
    new npc_th_battle_vehicle_event();
    new npc_th_battle_camera_event();
    new npc_th_battle_calen_event();
    new npc_th_battle_deathwing_event();
    new npc_th_battle_alexstrasza_event();
    new npc_th_battle_drake_double_event();
    new npc_th_battle_mirror_event();
    new npc_th_vermillion_skyscreamer();
    new spell_th_alexstrasza_tear();
    new npc_th_obsidian_pyrewing();
    new spell_th_wyrmhunter_hooks();
    new npc_th_baleflame();
    new npc_th_obsidia();
    new npc_th_twilight_gate_fighter();
    new npc_th_angus_stillmountain();
    new npc_th_si7_korkron_trigger();
    new go_th_hidden_explosives();
    new spell_th_attack_signal();
    new npc_th_cassius_the_white();
    new npc_th_si7_commander();
    new spell_th_water_of_life();
    new npc_th_finlay_controller();
    new go_th_earth_portal_controller();
    new go_th_air_portal_controller();
    new go_th_water_portal_controller();
    new npc_th_debilitated_apexar();
    new npc_th_debilitated_aetharon();
    new npc_th_debilitated_edemantus();
    new npc_th_dame_alys_finnsson();
    new npc_th_master_klem();
    new npc_th_mia_the_rose();
    new npc_th_mr_goldmine();
    new spell_th_the_elementium_axe();
    new npc_th_lirastrasza_unchained();
    new npc_th_twilight_skyterror();
    new npc_th_goldmine_cart();
    new npc_th_twilight_rune_of_earth();
    new go_th_twilight_rune_of_water();
    new go_th_twilight_rune_of_air();
    new go_th_twilight_rune_of_fire();
    new npc_th_magmatooth();
    new spell_th_fire_portal_controller();
    /* The Crucible of Carnage - START */
    new npc_th_gurgthock();
    new npc_th_hurp_derp();
    new npc_th_torg_drakeflayer();
    new npc_th_sully_kneecapper();
    new npc_th_cadaver_collage();
    new npc_th_geoffery_harness();
    new npc_th_lord_geoffery_tulvan();
    new npc_th_emberscar_the_devourer();
    new npc_th_lava_pool();
    /* The Crucible of Carnage - END   */
    new npc_th_the_hammer_of_twilight();
    new npc_th_skullcrusher_camera();
    new npc_th_skullcrusher_fight();
    new npc_th_skullcrusher_fighters();
    new npc_th_elemental_altars();
    new npc_th_horn_and_drums();
    new go_th_rope_ladder();
    new npc_th_frizz_groundspin();
    new npc_th_madness_trigger();
    new npc_th_warchief_madness();
    new npc_th_dragonmaw_fighters();
    new npc_th_dragonmaw_civilian();
    new npc_th_dragonmaw_portal_to_orgrimmar();
    new npc_th_salvageable_shredder();
    new npc_th_bilgewater_expert();
    new npc_th_mortar_beach_triggering();
    new npc_th_krazzwork_fighters();
    new npc_th_fathom_lotd_heth_jatar();
    new npc_th_krazzworks_laborer();
    new npc_th_thundermar_war_gryphon();
    new go_th_wildhammer_keg();
    new npc_th_grisly_gryphon_guts();
    new npc_th_highland_black_drake();
    new npc_th_highland_black_drake_cinematic();
    new npc_th_torth_zaela();
    new npc_th_zaela_at_cave();
    new npc_th_uchek_in_cave();
    new areatrigger_th_first_shrine();
    new areatrigger_th_second_shrine();
    new areatrigger_th_third_shrine();
    new spell_th_purifying_light();
    new npc_th_warlord_krogg_pass();
    new npc_th_lady_cozwynn();
    new npc_th_jon_jon_jellyneck();
    new npc_th_kor_kron_commander();
    new npc_th_skyshredder_turret();
    new spell_th_place_ticker_explosives();
    new go_th_induction_samophlange();
}
