
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
#include "firelands.h"

enum ShannoxTrashSpells
{
    // Molten Lord
    SPELL_FLAME_STOMP           = 99530,
    SPELL_LAVA_PILLAR_DUMMY     = 99555,
    SPELL_LAVA_PILLAR_EFFECT    = 99538,
    SPELL_MELT_ARMOR            = 99532,
    SPELL_LAVA_STRIKE           = 81884, // wtf?
};

class npc_fl_shannox_trash : public CreatureScript
{
    public:
        npc_fl_shannox_trash() :  CreatureScript("npc_fl_shannox_trash") { }

        struct npc_fl_shannox_trashAI : public ScriptedAI
        {
            npc_fl_shannox_trashAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            EventMap events;
            InstanceScript* instance;

            void EnterCombat(Unit* /*target*/)
            {
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* controller = Unit::GetCreature(*me, instance->GetData64(DATA_SHANNOX_CONTROLLER)))
                    controller->AI()->DoAction(1);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case 0:
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_shannox_trashAI(creature);
        }
};

enum LordEvents
{
    EVENT_FLAME_STOMP   = 1,
    EVENT_MELT_ARMOR,
    EVENT_LAVA_PILLAR,
};

class npc_fl_molten_lord : public CreatureScript
{
    public:
        npc_fl_molten_lord() :  CreatureScript("npc_fl_molten_lord") { }

        struct npc_fl_molten_lordAI : public ScriptedAI
        {
            npc_fl_molten_lordAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void EnterCombat(Unit* /*target*/)
            {
                events.ScheduleEvent(EVENT_FLAME_STOMP, 11000);
                events.ScheduleEvent(EVENT_MELT_ARMOR, 100);
                events.ScheduleEvent(EVENT_LAVA_PILLAR, 6000);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
                events.Reset();
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FLAME_STOMP:
                            DoCastVictim(SPELL_FLAME_STOMP);
                            events.ScheduleEvent(EVENT_FLAME_STOMP, 11000);
                            break;
                        case EVENT_MELT_ARMOR:
                            DoCastVictim(SPELL_MELT_ARMOR);
                            events.ScheduleEvent(EVENT_MELT_ARMOR, 3500);
                            break;
                        case EVENT_LAVA_PILLAR:
                            DoCastAOE(SPELL_LAVA_PILLAR_DUMMY);
                            events.ScheduleEvent(EVENT_LAVA_PILLAR, 13200);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_LAVA_PILLAR_DUMMY)
                    me->CastSpell(target, SPELL_LAVA_PILLAR_EFFECT);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_molten_lordAI(creature);
        }
};

void AddSC_firelands()
{
    new npc_fl_shannox_trash();
    new npc_fl_molten_lord();
}