
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "World.h"
#include "PetAI.h"
#include "PassiveAI.h"
#include "CombatAI.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "SpellAuras.h"
#include "Pet.h"

enum GruntyMisc
{
    EVENT_CHECK_ZERGLING = 1,
    EVENT_CAST_ATTACK,
    EVENT_KILL_PETS,

    NPC_ZERGLING = 11327,
    SPELL_ZERGLING_ATTACK = 67400,
};

class npc_pet_grunty : public CreatureScript
{
public:
    npc_pet_grunty() : CreatureScript("npc_pet_grunty") {}

    struct npc_pet_gruntyAI : public ScriptedAI
    {
        npc_pet_gruntyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_CHECK_ZERGLING, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ZERGLING:
                        if (Creature* zergling = me->FindNearestCreature(NPC_ZERGLING, 15.0f, true))
                        {
                            zergling->AI()->AttackStart(me);
                            me->SetFacingToObject(zergling);
                            events.ScheduleEvent(EVENT_CAST_ATTACK, 2000);
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_ZERGLING, 1000);
                        break;
                    case EVENT_CAST_ATTACK:
                        if (Creature* zergling = me->FindNearestCreature(NPC_ZERGLING, 15.0f, true))
                            zergling->CastSpell(me, SPELL_ZERGLING_ATTACK);
                        events.ScheduleEvent(EVENT_KILL_PETS, 2000);
                        break;
                    case EVENT_KILL_PETS:
                        if (Creature* zergling = me->FindNearestCreature(NPC_ZERGLING, 15.0f, true))
                        {
                            me->Kill(zergling);
                            zergling->DespawnOrUnsummon(5000);
                        }
                        me->Kill(me);
                        me->DespawnOrUnsummon(5000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pet_gruntyAI(creature);
    }
};

enum SunfloerStuff
{
    SPELL_SINGING_SUNFLOWER     = 93972,
    SOUND_SING = 23503,
    EVENT_SING = 1,
};

class npc_pet_sunflower : public CreatureScript
{
public:
    npc_pet_sunflower() : CreatureScript("npc_pet_sunflower") {}

    struct npc_pet_sunflowerAI : public ScriptedAI
    {
        npc_pet_sunflowerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SING, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SING:
                        DoCastAOE(SPELL_SINGING_SUNFLOWER);
                        me->PlayDistanceSound(SOUND_SING);
                        events.ScheduleEvent(EVENT_SING, 60000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pet_sunflowerAI(creature);
    }
};

void AddSC_pet_scripts()
{
    new npc_pet_grunty();
    new npc_pet_sunflower();
}
