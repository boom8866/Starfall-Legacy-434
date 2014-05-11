#include "ScriptPCH.h"
#include "the_stonecore.h"

enum Spells
{

};

enum Events
{

};

enum Yells
{

};

class boss_high_priestess_azil : public CreatureScript
{
public:
    boss_high_priestess_azil() : CreatureScript("boss_high_priestess_azil") { }

    struct boss_high_priestess_azilAI : public BossAI
    {
        boss_high_priestess_azilAI(Creature* creature) : BossAI(creature, DATA_HIGH_PRIESTESS_AZIL) {}

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!events.Empty())
                events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                /*
                switch (eventId)
                {
                case EVENT_
                    {
                        events.ScheduleEvent(EVENT_, 10000);
                        break;
                    }
                }
                */
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_high_priestess_azilAI (creature);
    }
};

void AddSC_boss_high_priestess_azil()
{
    new boss_high_priestess_azil();
}
