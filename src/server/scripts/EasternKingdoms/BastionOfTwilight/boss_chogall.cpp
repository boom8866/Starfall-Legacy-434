
#include "bastion_of_twilight.h"
#include "Vehicle.h"

enum Texts
{
    SAY_INTRO_1     = 1,
};

enum Spells
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
    EVENT_BERSERK = 1,
};

enum Actions
{

};

class boss_chogall : public CreatureScript
{
public:
    boss_chogall() : CreatureScript("boss_chogall") { }

    struct boss_chogallAI: public BossAI
    {
        boss_chogallAI(Creature* creature) : BossAI(creature, DATA_CHOGALL)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SetBossState(DATA_CHOGALL, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _EnterEvadeMode();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void JustSummoned(Creature* summon)
        {
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
                    case EVENT_BERSERK:
                        return; 
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SetBossState(DATA_CHOGALL, DONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_chogallAI(creature);
    }
};

void AddSC_boss_chogall()
{
    new boss_chogall();
}
