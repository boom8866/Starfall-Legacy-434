
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "well_of_eternity.h"

enum Texts
{
    SAY_INTRO_1     = 1,
    SAY_INTRO_2     = 2,
    SAY_INTRO_3     = 3,

};

enum Spells
{
    SPELL_CAMOUFLAGE    = 105341,
};

enum Events
{
    EVENT_TALK_INTRO_2 = 1,
    EVENT_TALK_INTRO_3,
    EVENT_INTRO_4,
    EVENT_MOVE_1,
};

enum Actions
{
    ACTION_START_INTRO = 1,
};

enum Phases
{
    PHASE_INTRO = 1,
    PHASE_COMBAT,
};

Position const IntroPos = {3250.977f, -4892.050f, 181.021f};

class boss_perotharn : public CreatureScript
{
public:
    boss_perotharn() : CreatureScript("boss_perotharn") { }

    struct boss_perotharnAI : public BossAI
    {
        boss_perotharnAI(Creature* creature) : BossAI(creature, DATA_PEROTHARN)
        {
            introStarted = false;
        }

        bool introStarted;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_INTRO:
                    if (!introStarted)
                    {
                        TalkToMap(SAY_INTRO_1);
                        introStarted = true;
                        events.SetPhase(PHASE_INTRO);
                        events.ScheduleEvent(EVENT_TALK_INTRO_2, 6000, 0, PHASE_INTRO);
                    }
                    break;
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void Reset()
        {
            _Reset();
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            _DespawnAtEvade();
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);
            
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_INTRO_2:
                        TalkToMap(SAY_INTRO_2);
                        events.ScheduleEvent(EVENT_TALK_INTRO_3, 4000, 0, PHASE_INTRO);

                        if (Creature* legion = me->FindNearestCreature(NPC_LEGION_DEMON_1, 100.0f, true))
                        {
                            me->SetFacingToObject(legion);
                            legion->AI()->DoAction(1);
                        }
                        break;
                    case EVENT_TALK_INTRO_3:
                        TalkToMap(SAY_INTRO_3);
                        events.ScheduleEvent(EVENT_INTRO_4, 4500, 0, PHASE_INTRO);
                        me->SetFacingTo(5.166174f);
                        break;
                    case EVENT_INTRO_4:
                    {
                        me->RemoveAllAuras();
                        DoCastAOE(SPELL_CAMOUFLAGE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                        me->DespawnOrUnsummon(15000);

                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_CORRUPTED_ARCANIST, 50.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_DREADLORD_DEFENDER, 50.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->SetFacingToObject(me);
                            (*itr)->GetMotionMaster()->MovePoint(0, (*itr)->GetPositionX()+cos((*itr)->GetOrientation())*100, (*itr)->GetPositionY()+sin((*itr)->GetOrientation())*100, me->GetPositionZ(), true);
                        }
                        events.ScheduleEvent(EVENT_MOVE_1, 4000, 0, PHASE_INTRO);
                        break;
                    }
                    case EVENT_MOVE_1:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_CORRUPTED_ARCANIST, 50.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_DREADLORD_DEFENDER, 50.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->GetMotionMaster()->MovePoint(0, IntroPos);
                            (*itr)->DespawnOrUnsummon(6000);
                        }
                        break;
                    }
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_perotharnAI(creature);
    }
};

void AddSC_boss_perotharn()
{
    new boss_perotharn();
};
