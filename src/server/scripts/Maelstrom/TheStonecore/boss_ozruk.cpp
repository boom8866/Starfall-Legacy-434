
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

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

class boss_ozruk : public CreatureScript
{
public:
    boss_ozruk() : CreatureScript("boss_ozruk") { }

    struct boss_ozrukAI : public BossAI
    {
        boss_ozrukAI(Creature* creature) : BossAI(creature, DATA_OZRUK) {}

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
        return new boss_ozrukAI (creature);
    }
};

void AddSC_boss_ozruk()
{
    new boss_ozruk();
}
