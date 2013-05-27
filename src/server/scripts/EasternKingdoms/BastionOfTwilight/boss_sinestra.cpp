/*Copyright (C) 2012 SkyMist Project.
*
*
* This file is NOT free software. Third-party users can NOT redistribute it or modify it :). 
* If you find it, you are either hacking something, or very lucky (presuming someone else managed to hack it).
*/

#include "ScriptPCH.h"
#include "ScriptPCH.h"
#include "bastion_of_twilight.h"
#include "Vehicle.h"
#include "Unit.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Spell.h"
#include "Player.h"
#include "Map.h"
#include "InstanceScript.h"

enum Yells
{
};

enum Spells
{
 SPELL_BERSERK         = 26662
};

enum Npc
{
};

enum Phases
{
 PHASE_NULL   = 1,
 PHASE_NORMAL,
 PHASE_LAST
};

enum Events
{
 //##### Cho'gall #####
 EVENT_BERSERK,
};

class boss_sinestra : public CreatureScript
{
public:
    boss_sinestra() : CreatureScript("boss_sinestra") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_sinestraAI (creature);
    }

    struct boss_sinestraAI: public BossAI
    {
        boss_sinestraAI(Creature* creature) : BossAI(creature, DATA_SINESTRA)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        Phases phase;
		
        void Reset()
        {
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
            phase = PHASE_NULL;

            _Reset();
        }

        void EnterEvadeMode()
        {
            Reset();

            me->GetMotionMaster()->MoveTargetedHome();

            if (instance)
            {
                instance->SetBossState(DATA_SINESTRA, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void EnterCombat(Unit* /*who*/)
        {
            phase = PHASE_NORMAL;
            events.SetPhase(PHASE_NORMAL);

            if (instance)
            {
                instance->SetBossState(DATA_SINESTRA, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            events.ScheduleEvent(EVENT_BERSERK, 420000);

            _EnterCombat();
        }

        void JustSummoned(Creature* summon)
        {
            summon->AI()->DoZoneInCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (me->GetHealthPct() < 21) // Phase 2
            {
                phase = PHASE_LAST;
                events.SetPhase(PHASE_LAST);
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        return;
                    
                    default:
                        break;
                }
            }		

                DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->RemoveAllAuras();

            if (instance)
            {
                instance->SetBossState(DATA_SINESTRA, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _JustDied();
        }
    };
};

void AddSC_boss_sinestra()
{
    new boss_sinestra();
}