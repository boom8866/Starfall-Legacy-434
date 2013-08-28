
#include "dragonsoul.h"

enum Spells
{
    // Deathwing Intro
    SPELL_MOLTEN_METEOR         = 105022,
};

enum Events
{
    // Deathwing Intro
    EVENT_MOVE_1 = 1,
    EVENT_MOVE_2,
    EVENT_MOVE_3,
};

enum Points
{
    POINT_1 = 1,
    POINT_2,
    POINT_3,
};

Position const DeathwingPos1 = {-1416.439f, -2191.300f, 374.454f};
Position const DeathwingPos2 = {-1528.270f, -2420.429f, 397.546f};
Position const DeathwingPos3 = {-1589.730f, -2030.362f, 388.266f};

class npc_deathwing_ultraxion : public CreatureScript
{
public:
    npc_deathwing_ultraxion() : CreatureScript("npc_deathwing_ultraxion") { }

    struct npc_deathwing_ultraxionAI  : public ScriptedAI
    {
        npc_deathwing_ultraxionAI (Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetSpeed(MOVE_RUN, 1.66f);
            me->setActive(true);
            events.ScheduleEvent(EVENT_MOVE_1, 1);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case 0:
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_1:
                    if (Creature* target = me->FindNearestCreature(56665, 1000.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_MOLTEN_METEOR);
                    }
                    events.ScheduleEvent(EVENT_MOVE_1, 10000);
                    break;
                case POINT_2:
                    if (Creature* target = me->FindNearestCreature(56665, 1000.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_MOLTEN_METEOR);
                    }
                    events.ScheduleEvent(EVENT_MOVE_2, 10000);
                    break;
                case POINT_3:
                    if (Creature* target = me->FindNearestCreature(56665, 1000.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_MOLTEN_METEOR);
                    }
                    events.ScheduleEvent(EVENT_MOVE_3, 10000);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_1:
                        me->GetMotionMaster()->MovePoint(POINT_2, DeathwingPos2);
                        break;
                    case EVENT_MOVE_2:
                        me->GetMotionMaster()->MovePoint(POINT_3, DeathwingPos1);
                        break;
                    case EVENT_MOVE_3:
                        me->GetMotionMaster()->MovePoint(POINT_1, DeathwingPos3);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new npc_deathwing_ultraxionAI (Creature);
    }
};

void AddSC_boss_ultraxion()
{
    new npc_deathwing_ultraxion();
}
