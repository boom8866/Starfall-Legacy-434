
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "zulaman.h"
#include "Weather.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_STORM   = 2,
    SAY_EAGLE   = 3,
    SAY_DEATH   = 4,
};

enum Spells
{
    SPELL_STATIC_DISRUPTION             = 43622,
    SPELL_GUST_OF_THE_WIND              = 97319,
    SPELL_CALL_LIGHTNING                = 97299,
    SPELL_DISMISS_RUNE_WEAPON           = 50707,
    SPELL_ELECTRICAL_OVERLOAD_PRIMER    = 44735,

    SPELL_GRIPPED                       = 97318,
    SPELL_ELECTRICAL_STORM              = 43648,
};

enum Sounds
{
    SOUND_CRY   = 12196,
};

enum Events
{
    EVENT_STATIC_DISRUPTION = 1,
    EVENT_ELECTRICAL_STORM,
    EVENT_CALL_LIGHTNING,
    EVENT_SUMMON_AMANI_KIDNAPPER,
    EVENT_SUMMON_SOARING_EAGEL,
};

class boss_akilzon : public CreatureScript
{
public:
    boss_akilzon() : CreatureScript("boss_akilzon") { }

    struct boss_akilzonAI : public BossAI
    {
        boss_akilzonAI(Creature* creature) : BossAI(creature, DATA_AKILZON)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void JustKilled(Unit* target)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
                    case EVENT_STATIC_DISRUPTION:
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_akilzonAI(creature);
    }
};

void AddSC_boss_akilzon()
{
    new boss_akilzon();
}
