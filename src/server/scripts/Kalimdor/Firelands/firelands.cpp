
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

enum BridgeStuff
{
    SPELL_TRIGGER_BRIDGE_CINEMATIC  = 101034,
    SPELL_FORM_BRDGE_VISUAL         = 101035,

    SOUND_FORM_BRDGE                = 25339,
};

enum BridgeActions
{
    ACTION_TRIGGER_EVENT    = 1,
};

enum BridgeEvents
{
    EVENT_CAST_VISUAL       = 1,
    EVENT_SET_BRIDGE_STATE  = 2,
};

class npc_fl_molten_orb : public CreatureScript
{
public:
    npc_fl_molten_orb() : CreatureScript("npc_fl_molten_orb")
    {
        started = false;
    }

    bool started;

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!started)
        {
            if (Creature* bridgetrigger = creature->FindNearestCreature(NPC_BRIDGE_TRIGGER, 200.0f, true))
                bridgetrigger->AI()->DoCastAOE(SPELL_TRIGGER_BRIDGE_CINEMATIC);
            creature->AI()->DoAction(ACTION_TRIGGER_EVENT);
            started = true;
        }
        return true;
    }

    struct npc_fl_molten_orbAI : public ScriptedAI
    {
        npc_fl_molten_orbAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TRIGGER_EVENT:
                    events.ScheduleEvent(EVENT_CAST_VISUAL, 4300);
                    break;
                default:
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
                    case EVENT_CAST_VISUAL:
                        if (Creature* bridgetrigger = me->FindNearestCreature(NPC_BRIDGE_TRIGGER, 200.0f, true))
                        {
                            bridgetrigger->AI()->DoCastAOE(SPELL_FORM_BRDGE_VISUAL);
                            bridgetrigger->PlayDistanceSound(SOUND_FORM_BRDGE);
                        }
                        events.ScheduleEvent(EVENT_SET_BRIDGE_STATE, 16100);
                        break;
                    case EVENT_SET_BRIDGE_STATE:
                        if (GameObject* bridge = me->FindNearestGameObject(GO_FIRELANDS_BRIDGE, 500.0f))
                            bridge->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                        if (GameObject* door = me->FindNearestGameObject(GO_BRIDGE_DOOR, 100.0f))
                            door->SetGoState(GO_STATE_ACTIVE);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_molten_orbAI(creature);
    }
};

class spell_fl_trigger_bridge_cinematic : public SpellScriptLoader
{
public:
    spell_fl_trigger_bridge_cinematic() : SpellScriptLoader("spell_fl_trigger_bridge_cinematic") { }

    class spell_fl_trigger_bridge_cinematic_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_trigger_bridge_cinematic_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (target->GetTypeId() == TYPEID_PLAYER)
                    target->ToPlayer()->SendCinematicStart(CINEMATIC_BRIDGE_FORMING);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_trigger_bridge_cinematic_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_trigger_bridge_cinematic_SpellScript();
    }
};

void AddSC_firelands()
{
    new npc_fl_shannox_trash();
    new npc_fl_molten_lord();
    new npc_fl_molten_orb();
    new spell_fl_trigger_bridge_cinematic();
}