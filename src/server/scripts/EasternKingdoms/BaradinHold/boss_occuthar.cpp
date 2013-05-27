/*
* Copyright (C) 2011-2013 Devastion Cataclysm <http://www.cataclysm-wow.eu/>
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

/*
Author: NorthStrider
Complete: 90%
todo:
-test the focused fire eye caster if they work on multiplayer raid
-correct timers
*/

#include "ScriptPCH.h"
#include "Vehicle.h"
#include "baradin_hold.h"

enum Spells
{
    // Occu'thar
    SPELL_SEARING_SHADOWS           = 101007,
    SPELL_FOCUSED_FIRE              = 96884,
    SPELL_FOCUSED_FIRE_SUMMON       = 96873,
    SPELL_EYES_OF_OCCUTHAR          = 101006,
    SPELL_EYES_OF_OCCUTHAR_DUMMY    = 96932,
    SPELL_BERSERK                   = 47008,

    // Eye
    SPELL_GAZE_OF_OCCUTHAR          = 97028,
    SPELL_EYE_EXPLODE               = 96968,
    SPELL_EYE_VISUAL                = 96995,
};

enum Events
{
    EVENT_SEARING_SHADOWS   = 1,
    EVENT_FOCUSED_FIRE_1    = 2,
    EVENT_FOCUSED_FIRE_2    = 3,
    EVENT_EYE_OF_OCCUTHAR   = 4,
    EVENT_EYE_SUMMON        = 5,
    EVENT_BERSERK           = 6,
    EVENT_EYE_EXPLOSION     = 7,
};

class boss_occuthar : public CreatureScript
{
public:
    boss_occuthar() : CreatureScript("boss_occuthar") { }

    struct boss_occutharAI : public BossAI
    {
        boss_occutharAI(Creature* creature) : BossAI(creature, DATA_OCCUTHAR), vehicle(creature->GetVehicleKit())
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        Vehicle* vehicle;
        bool SummonedEyes;

        void Reset()
        {
            _Reset();
            SummonedEyes = false;
            DoCastAOE(96812);
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (Creature* eye1 = me->SummonCreature(NPC_OCCUTHAR_EYE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                eye1->CastSpell(me, 84495);
            if (Creature* eye2 = me->SummonCreature(NPC_OCCUTHAR_EYE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                eye2->CastSpell(me, 84495);
            if (Creature* eye3 = me->SummonCreature(NPC_OCCUTHAR_EYE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                eye3->CastSpell(me, 84495);
            if (Creature* eye4 = me->SummonCreature(NPC_OCCUTHAR_EYE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                eye4->CastSpell(me, 84495);
            if (Creature* eye5 = me->SummonCreature(NPC_OCCUTHAR_EYE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                eye5->CastSpell(me, 84495);
            events.ScheduleEvent(EVENT_SEARING_SHADOWS, 20000);
            events.ScheduleEvent(EVENT_FOCUSED_FIRE_1, 15000);
            events.ScheduleEvent(EVENT_EYE_OF_OCCUTHAR, 7000);
            events.ScheduleEvent(EVENT_BERSERK, 300000);
            SummonedEyes = false;
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            _DespawnAtEvade();
        }

        void JustDied(Unit* killer)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EYE_OF_OCCUTHAR:
                        DoCastAOE(SPELL_EYES_OF_OCCUTHAR);
                        SummonedEyes = true;
                        events.ScheduleEvent(EVENT_EYE_SUMMON, 2100);
                        events.ScheduleEvent(EVENT_EYE_OF_OCCUTHAR, urand(55000, 65000));
                        break;
                    case EVENT_EYE_SUMMON:
                        {
                            if (SummonedEyes)
                            {
                                std::list<Unit*> targetList;
                                {
                                    const std::list<HostileReference*>& threatlist = me->getThreatManager().getThreatList();
                                    for (std::list<HostileReference*>::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                                        if ((*itr)->getTarget()->GetTypeId() == TYPEID_PLAYER)
                                            targetList.push_back((*itr)->getTarget());
                                }

                                for (std::list<Unit*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                                {
                                    DoCast(*itr, SPELL_EYES_OF_OCCUTHAR_DUMMY);
                                    me->SummonCreature(NPC_EYE_OF_OCCUTHAR, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN);
                                }
                                SummonedEyes = false;
                            }
                        }
                        break;
                    case EVENT_FOCUSED_FIRE_1:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_FOCUSED_FIRE_SUMMON);
                        events.ScheduleEvent(EVENT_FOCUSED_FIRE_2, 1000);
                        events.ScheduleEvent(EVENT_FOCUSED_FIRE_1, 15000);
                        break;
                    case EVENT_FOCUSED_FIRE_2:
                        for (SeatMap::iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end(); ++itr)
                            if (Unit* passenger = ObjectAccessor::GetUnit(*vehicle->GetBase(), itr->second.Passenger))
                            {
                                if (Creature* dummy = me->FindNearestCreature(NPC_FOCUS_FIRE_DUMMY, 200.0f))
                                    passenger->CastSpell(dummy, SPELL_FOCUSED_FIRE, false);
                            }
                        break;
                    case EVENT_SEARING_SHADOWS:
                        DoCastVictim(SPELL_SEARING_SHADOWS);
                        events.ScheduleEvent(EVENT_SEARING_SHADOWS, 20000);
                        break;
                    case EVENT_BERSERK:
                        DoCastAOE(SPELL_BERSERK);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_occutharAI(creature);
    }
};

class npc_eye_of_occuthar : public CreatureScript
{
public:
    npc_eye_of_occuthar() : CreatureScript("npc_eye_of_occuthar") { }

    struct npc_eye_of_occutharAI : public ScriptedAI
    {
        npc_eye_of_occutharAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetReactState(REACT_AGGRESSIVE);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
            events.Reset();
        }

        void EnterCombat(Unit* who)
        {
            DoCastAOE(SPELL_EYE_VISUAL);
            DoCast(who, SPELL_GAZE_OF_OCCUTHAR);
            events.ScheduleEvent(EVENT_EYE_EXPLOSION, 10000);
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
                    case EVENT_EYE_EXPLOSION:
                        DoCastAOE(SPELL_EYE_EXPLODE);
                        me->DespawnOrUnsummon(500);
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_eye_of_occutharAI(creature);
    }
};

void AddSC_boss_occuthar()
{
    new boss_occuthar();
    new npc_eye_of_occuthar();
}