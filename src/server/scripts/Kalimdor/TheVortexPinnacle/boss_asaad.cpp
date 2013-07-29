/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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

#include "vortex_pinnacle.h"
#include "MapManager.h"
#include "ScriptPCH.h"

enum Yells
{
    SAY_AGGRO       = 0,
    SAY_FIELD       = 1,
    ANNOUNCE_FIELD  = 2,
    SAY_DEATH       = 3,
};

enum Spells
{
    // Asaad
    SPELL_ENERGY_FIELD_CAST         = 86911,
    SPELL_CHAIN_LIGHTNING           = 87622,
    SPELL_LIGHTNING_STORM_CAST      = 86930,
    SPELL_STATIC_ENERGIZE           = 87618,
    SPELL_SUMMON_SKYFALL_STAR       = 96260,
    SPELL_GROUNDING_FIELD_VISUAL    = 87517,

    // Skyfall Star
    SPELL_SHOOT                 = 87854,
};

enum Events
{
    EVENT_CHAIN_LIGHTNING           = 1,
    EVENT_STATIC_ENERGIZE           = 2,
    EVENT_UNSTABLE_GROUNDING_FIELD  = 3,
    EVENT_ATTACK                    = 4,

    // Npc
    EVENT_CORNER                    = 5,
};

enum Points
{
    POINT_CORNER    = 1,
};

class boss_asaad : public CreatureScript
{
public:
    boss_asaad() : CreatureScript("boss_asaad") { }

    struct boss_asaadAI : public BossAI
    {
        boss_asaadAI(Creature* creature) : BossAI(creature, DATA_ASAAD)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            events.Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_ASAAD, NOT_STARTED);
            me->DespawnCreaturesInArea(NPC_GROUNDING_FIELD_TRIGGER);
            me->DespawnCreaturesInArea(NPC_GROUNDING_FIELD_STATIONARY);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            DoZoneInCombat();
            instance->SetBossState(DATA_ASAAD, IN_PROGRESS);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            //events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 14000);
            //events.ScheduleEvent(EVENT_STATIC_ENERGIZE, 42000);
            events.ScheduleEvent(EVENT_UNSTABLE_GROUNDING_FIELD, 10000); // 60000
        }

        void JustDied(Unit* /*Killer*/)
        {
            Talk(SAY_DEATH);
            instance->SetBossState(DATA_ASAAD, DONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->DespawnCreaturesInArea(NPC_GROUNDING_FIELD_TRIGGER);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHAIN_LIGHTNING:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_CHAIN_LIGHTNING);
                        events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 24000);
                        break;
                    case EVENT_STATIC_ENERGIZE:
                        DoCastAOE(SPELL_STATIC_ENERGIZE);
                        DoCastAOE(SPELL_SUMMON_SKYFALL_STAR);
                        events.ScheduleEvent(EVENT_STATIC_ENERGIZE, 16000);
                        break;
                    case EVENT_UNSTABLE_GROUNDING_FIELD:
                        Talk(SAY_FIELD);
                        Talk(ANNOUNCE_FIELD);
                        if (Creature* walker = me->SummonCreature(NPC_GROUNDING_FIELD_TRIGGER, me->GetPositionX()+rand()%20, me->GetPositionY()+rand()%20, me->GetPositionZ()))
                            DoCast(walker, SPELL_ENERGY_FIELD_CAST);
                        events.ScheduleEvent(EVENT_UNSTABLE_GROUNDING_FIELD, 45000);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_asaadAI (creature);
    }
};

class npc_field_walker : public CreatureScript
{
public:
    npc_field_walker() : CreatureScript("npc_field_walker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_field_walkerAI(creature);
    }

    struct npc_field_walkerAI : public ScriptedAI
    {
        npc_field_walkerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        uint8 count;

        void IsSummonedBy(Unit* creator)
        {
            if (creator->GetEntry() == BOSS_ASAAD)
            {
                me->SetFacingToObject(creator);
                count = 0;
                VisualON();
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CORNER:
                    VisualON();
                    break;
            }
        }

        void VisualON()
        {
            me->RemoveAura(SPELL_GROUNDING_FIELD_VISUAL);
            events.ScheduleEvent(EVENT_CORNER, 1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CORNER:
                        me->SummonCreature(NPC_GROUNDING_FIELD_STATIONARY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                        me->SetOrientation((me->GetOrientation()+(M_PI / 1.5)));
                        me->GetMotionMaster()->MovePoint(POINT_CORNER, me->GetPositionX()+cos(me->GetOrientation())*15, me->GetPositionY()+sin(me->GetOrientation())*15, me->GetPositionZ());
                        events.CancelEvent(EVENT_CORNER);
                        break;
                    default:
                        break;
                }
            }
        }
    };
};


class npc_field_stationary : public CreatureScript
{
public:
    npc_field_stationary() : CreatureScript("npc_field_stationary") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_field_stationaryAI(creature);
    }

    struct npc_field_stationaryAI : public ScriptedAI
    {
        npc_field_stationaryAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            SetCombatMovement(false);
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* creator)
        {
            if (creator->GetEntry() == NPC_GROUNDING_FIELD_TRIGGER)
            {
                //me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_PASSIVE);
                if (Creature* walker = me->FindNearestCreature(NPC_GROUNDING_FIELD_TRIGGER, 10.0f, true))
                    walker->CastSpell(me, SPELL_GROUNDING_FIELD_VISUAL, TRIGGERED_IGNORE_AURA_INTERRUPT_FLAGS);
            }
        }
    };
};

// Grounding Field
void AddSC_boss_asaad()
{
    new boss_asaad();
    new npc_field_walker();
    new npc_field_stationary();
}
