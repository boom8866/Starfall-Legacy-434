
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

// Fire Jugglers
enum JugglerDefines
{
    SPELL_JUGGLE_TORCHES    = 102905,

    EVENT_START_JUGGLE      = 1,
    EVENT_STOP_JUGGLE       = 2,
};

class npc_df_fire_juggler : public CreatureScript
{
public:
    npc_df_fire_juggler() : CreatureScript("npc_df_fire_juggler") { }

    struct npc_df_fire_jugglerAI : public ScriptedAI
    {
        npc_df_fire_jugglerAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_START_JUGGLE, 1);
        }

        EventMap events;

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_JUGGLE:
                        DoCastAOE(SPELL_JUGGLE_TORCHES);
                        events.ScheduleEvent(EVENT_STOP_JUGGLE, 30000);
                        break;
                    case EVENT_STOP_JUGGLE:
                        me->RemoveAllAuras();
                        events.ScheduleEvent(EVENT_START_JUGGLE, 30000);
                        break;
                }
            }           
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_df_fire_jugglerAI(creature);
    }
};

void AddSC_darkmoon_island()
{
    new npc_df_fire_juggler();
}
