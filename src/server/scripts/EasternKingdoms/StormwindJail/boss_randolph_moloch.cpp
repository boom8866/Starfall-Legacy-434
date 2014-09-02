
#include "stormwind_jail.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_FADE    = 1,
    SAY_DEATH   = 2,
};

enum Spells
{
    SPELL_WILDLY_STABBING   = 86726,
    SPELL_SWEEP             = 86729,
    SPELL_VANISH            = 55964,
};

enum Events
{
    EVENT_WILDLY_STABBLING = 1,
    EVENT_SWEEP,
    EVENT_VANISH,
    EVENT_TELEPORT,
};

class boss_randolph_moloch : public CreatureScript
{
public:
    boss_randolph_moloch() : CreatureScript("boss_randolph_moloch") { }

    struct boss_randolph_molochAI : public BossAI
    {
        boss_randolph_molochAI(Creature* creature) : BossAI(creature, DATA_RANDOLPH_MOLOCH)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            summons.DespawnAll();
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(25) && !me->HasUnitState(UNIT_STATE_CASTING))
            {
            }
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
                    case 0:
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_randolph_molochAI (creature);
    }
};


void AddSC_boss_randolph_moloch()
{
    new boss_randolph_moloch();
}
