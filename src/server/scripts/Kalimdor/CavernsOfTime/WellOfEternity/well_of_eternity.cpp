
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
#include "well_of_eternity.h"

class at_woe_intro : public AreaTriggerScript // 7029
{
    public:
        at_woe_intro() : AreaTriggerScript("at_woe_intro") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (Creature* perotharn = player->FindNearestCreature(BOSS_PEROTHARN, 200.0f, true))
                perotharn->AI()->DoAction(1);
            return true;
        }
};

Position const LegionIntroPos = {3196.917f, -4942.768f, 189.5243f};

enum LegionSpells
{
    SPELL_SUMMON_FIREWALL       = 105243,
    SPELL_FELL_FIRE_COSMETIC    = 105250,
    SPELL_CALL_FEAR             = 103913,
    SPELL_CRUSHING_LEAP         = 108474,
};

enum LegionEvents
{
    EVENT_MOVE_WALL = 1,
    EVENT_SCHEDULE_FIREWALL_1,
    EVENT_PREPARE_FOR_FIGHT,
    EVENT_CALL_FEAR,
    EVENT_SHATTERING_STOMP,
};

enum LegionActions
{
    ACTION_MOVE_WALL = 1,
};

enum Phases
{
    PHASE_INTRO = 1,
    PHASE_COMBAT,
};

class npc_legion_demon_intro : public CreatureScript
{
    public:
        npc_legion_demon_intro() : CreatureScript("npc_legion_demon_intro") { }

        struct npc_legion_demon_introAI : public ScriptedAI
        {
            npc_legion_demon_introAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_CALL_FEAR, 7000);
                events.ScheduleEvent(EVENT_SHATTERING_STOMP, 10000);
            }

            void EnterEvadeMode()
            {
                me->GetMotionMaster()->MoveTargetedHome();
                events.Reset();
                events.SetPhase(PHASE_COMBAT);
            }

            void JustDied(Unit* /*killer*/)
            {
                if (GameObject* firewall = me->FindNearestGameObject(GO_COURTYARD_FIREWALL, 100.0f))
                    firewall->SetGoState(GO_STATE_ACTIVE);
                if (GameObject* firewall = me->FindNearestGameObject(GO_COURTYARD_DOOR, 100.0f))
                    firewall->SetGoState(GO_STATE_ACTIVE);
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_MOVE_WALL:
                        me->HandleEmoteCommand(113);
                        events.SetPhase(PHASE_INTRO);
                        events.ScheduleEvent(EVENT_MOVE_WALL, 18000, 0, PHASE_INTRO);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!(events.IsInPhase(PHASE_INTRO)))
                    if (!UpdateVictim())
                        return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE_WALL:
                            me->GetMotionMaster()->MovePoint(0, LegionIntroPos);
                            events.ScheduleEvent(EVENT_SCHEDULE_FIREWALL_1, 3500);
                            break;
                        case EVENT_SCHEDULE_FIREWALL_1:
                        {
                            if (GameObject* firewall = me->FindNearestGameObject(GO_COURTYARD_FIREWALL, 50.0f))
                                firewall->SetGoState(GO_STATE_READY);

                            std::list<Creature*> units;
                            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_STALKER, 500.0f);
                            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                (*itr)->CastSpell((*itr), SPELL_FELL_FIRE_COSMETIC);

                            DoCastAOE(SPELL_SUMMON_FIREWALL);
                            me->SetFacingTo(5.166174f);
                            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 5.166174f);
                            events.ScheduleEvent(EVENT_PREPARE_FOR_FIGHT, 4000, 0, PHASE_INTRO);
                            break;
                        }
                        case EVENT_PREPARE_FOR_FIGHT:
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                            me->SetReactState(REACT_AGGRESSIVE);
                            events.SetPhase(PHASE_COMBAT);
                            break;
                        case EVENT_CALL_FEAR:
                            DoCastAOE(SPELL_CALL_FEAR);
                            events.ScheduleEvent(EVENT_CALL_FEAR, 7000);
                            break;
                        case EVENT_SHATTERING_STOMP:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_CRUSHING_LEAP);
                            events.ScheduleEvent(EVENT_SHATTERING_STOMP, 7000);
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
        return new npc_legion_demon_introAI(creature);
    }
};

void AddSC_well_of_eternity()
{
    new at_woe_intro();
    new npc_legion_demon_intro();
}
