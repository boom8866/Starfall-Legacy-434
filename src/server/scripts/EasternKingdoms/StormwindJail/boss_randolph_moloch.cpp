
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
            _vanishCounter = 0;
        }

        uint8 _vanishCounter;

        void Reset()
        {
            _Reset();
            _vanishCounter = 0;
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
            _vanishCounter = 0;
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(70) && !me->HasUnitState(UNIT_STATE_CASTING) && _vanishCounter == 0)
            {
                _vanishCounter++;
                events.ScheduleEvent(EVENT_VANISH, 1);
                Talk(SAY_FADE);
            }
            else if (me->HealthBelowPct(40) && !me->HasUnitState(UNIT_STATE_CASTING) && _vanishCounter == 1)
            {
                _vanishCounter++;
                events.ScheduleEvent(EVENT_VANISH, 1);
                Talk(SAY_FADE);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !me->HasAura(SPELL_VANISH))
                return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_VANISH:
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        DoCast(SPELL_VANISH);
                        events.ScheduleEvent(EVENT_TELEPORT, 2450);
                        break;
                    case EVENT_TELEPORT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            float ori = target->GetOrientation() * (M_PI / 2);
                            float x = target->GetPositionX();
                            float y = target->GetPositionY();
                            float z = target->GetPositionZ();
                            me->NearTeleportTo(x + cos(ori)*3, y+sin(ori)*3, z, target->GetOrientation(), false);
                            me->Attack(target, true);
                            me->SetReactState(REACT_AGGRESSIVE);
                        }
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
