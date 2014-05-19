#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "MapManager.h"
#include "halls_of_origination.h"

enum Spells
{
    SPELL_CHAOS_BOLT            = 89873,
    SPELL_REIGN_OF_CHAOS_ROOT   = 77053,
    SPELL_REIGN_OF_CHAOS_AURA   = 77023,
    SPELL_REIGN_OF_CHAOS_SUMMON = 77024,

    SPELL_REIGN_OF_CHAOS_DUMMY  = 77026,
    SPELL_REIGN_OF_CHAOS_DAMAGE = 77030,
};

enum Texts
{
    SAY_AGGRO           = 0,
    SAY_REIGN_OF_CHAOS  = 1,
    SAY_SLAY            = 2,
    SAY_DEATH           = 3,
};

enum Events
{
    EVENT_CHAOS_BOLT = 1,
    EVENT_REIGN_OF_CHAOS,
};

enum Points
{
    POINT_PORTAL = 1,
};

class boss_setesh : public CreatureScript
{
    public:
        boss_setesh() : CreatureScript("boss_setesh") { }

        struct boss_seteshAI : public BossAI
        {
            boss_seteshAI(Creature* creature) : BossAI(creature, DATA_SETESH)
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
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_CHAOS_BOLT, 1);
                events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, 32000);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
                me->GetMotionMaster()->MoveTargetedHome();
            }

			void KilledUnit(Unit* killed)
			{
                if (killed->GetTypeId() == TYPEID_PLAYER)
				    Talk(SAY_SLAY);
			}

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

            void JustSummoned(Creature* summon)
            {
                switch (summon->GetEntry())
                {
                    case NPC_REIGN_OF_CHAOS:
                        summon->CastSpell(summon, SPELL_REIGN_OF_CHAOS_DUMMY);
                        summons.Summon(summon);
                        break;
                    default:
                        summons.Summon(summon);
                        break;
                }
            }

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case POINT_PORTAL:
                        break;
                }
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
                        case EVENT_CHAOS_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15.0f, true))
                                DoCast(target, SPELL_CHAOS_BOLT);
                            events.ScheduleEvent(EVENT_CHAOS_BOLT, 2000);
                            break;
                        case EVENT_REIGN_OF_CHAOS:
                            Talk(SAY_REIGN_OF_CHAOS);
                            DoCastAOE(SPELL_REIGN_OF_CHAOS_AURA);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_seteshAI(creature);
        }
};

void AddSC_boss_setesh()
{
    new boss_setesh();
}
