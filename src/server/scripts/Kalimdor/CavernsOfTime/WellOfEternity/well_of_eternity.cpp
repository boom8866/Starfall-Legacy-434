
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

class at_woe_illidan_intro : public AreaTriggerScript //7066
{
    public:
        at_woe_illidan_intro() : AreaTriggerScript("at_woe_illidan_intro") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (Creature* illidan = player->FindNearestCreature(NPC_ILLIDAN, 200.0f, true))
                illidan->AI()->DoAction(1);
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
    EVENT_PLAY_MARCH_SOUND,
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

enum Courtevents
{
    EVENT_MOVE_1 = 1,
    EVENT_MOVE_2,
    EVENT_MOVE_3,
    EVENT_KILL_PLAYER,
};

const Position LegionSpawn[] =
{
    {3454.300f, -5084.906f, 213.6803f, 2.146755f}, // left demon
    {3460.269f, -5080.965f, 213.6476f, 2.146755f}, // right demon
};

class npc_legion_demon : public CreatureScript
{
    public:
        npc_legion_demon() : CreatureScript("npc_legion_demon") { }

        struct npc_legion_demonAI : public ScriptedAI
        {
            npc_legion_demonAI(Creature* creature) : ScriptedAI(creature)
            {
                _moveCounter = 0;
            }

            EventMap events;
            Creature* follower;
            uint8 _moveCounter;

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
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
                    case 0: // Middle 1
                        events.ScheduleEvent(EVENT_MOVE_1, 1);
                        break;
                    case 1: // Middle 1
                        events.ScheduleEvent(EVENT_MOVE_2, 1);
                        break;
                    case 2: // Middle 1
                        events.ScheduleEvent(EVENT_MOVE_3, 1);
                        break;
                    default:
                        break;
                }
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                if (summoner->GetEntry() == BOSS_PEROTHARN)
                {
                    if (follower = me->SummonCreature(NPC_LEGION_DEMON_2, LegionSpawn[1], TEMPSUMMON_TIMED_DESPAWN, 180000))
                        follower->GetMotionMaster()->MoveFollow(me, 3.0f, 270.0f);
                    events.SetPhase(PHASE_INTRO);
                    events.ScheduleEvent(EVENT_KILL_PLAYER, 500, 0, PHASE_INTRO);
                }
                events.ScheduleEvent(EVENT_PLAY_MARCH_SOUND, 3000, 0, PHASE_INTRO);
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
                        case EVENT_MOVE_1:
                            _moveCounter++;
                            if (_moveCounter == 1)
                                me->GetMotionMaster()->MovePoint(0, 3425.416f, -5037.641f, 196.782f, false);
                            else if (_moveCounter == 2)
                                me->GetMotionMaster()->MovePoint(0, 3388.032f, -4978.755f, 196.782f, false);
                            else if (_moveCounter == 3)
                                me->GetMotionMaster()->MovePoint(0, 3374.894f, -4957.670f, 181.182f, false);
                            else if (_moveCounter == 4)
                                me->GetMotionMaster()->MovePoint(0, 3335.971f, -4896.179f, 181.077f, false);
                            else if (_moveCounter == 5)
                            {
                                follower->SetSpeed(MOVE_RUN, 0.5f);
                                me->SetSpeed(MOVE_RUN, 0.5f);
                                me->GetMotionMaster()->MovePoint(0, 3285.551f, -4817.690f, 181.471f, false);
                            }
                            else if (_moveCounter == 6)
                            {
                                follower->DespawnOrUnsummon(3000);
                                me->DespawnOrUnsummon(0);
                            }
                            break;
                        case EVENT_MOVE_2:
                            _moveCounter++;
                            if (_moveCounter == 1)
                                me->GetMotionMaster()->MovePoint(1, 3425.416f, -5037.641f, 196.782f, false);
                            else if (_moveCounter == 2)
                                me->GetMotionMaster()->MovePoint(1, 3388.032f, -4978.755f, 196.782f, false);
                            else if (_moveCounter == 3)
                                me->GetMotionMaster()->MovePoint(1, 3374.894f, -4957.670f, 181.182f, false);
                            else if (_moveCounter == 4)
                                me->GetMotionMaster()->MovePoint(1, 3335.971f, -4896.179f, 181.077f, false);
                            else if (_moveCounter == 5)
                            {
                                follower->SetSpeed(MOVE_RUN, 0.5f);
                                me->SetSpeed(MOVE_RUN, 0.5f);
                                me->GetMotionMaster()->MovePoint(1, 3257.634f, -4943.845f, 181.679f, false);
                            }
                            else if (_moveCounter == 6)
                            {
                                follower->DespawnOrUnsummon(3000);
                                me->DespawnOrUnsummon(0);
                            }
                            break;
                        case EVENT_MOVE_3:
                            _moveCounter++;
                            if (_moveCounter == 1)
                                me->GetMotionMaster()->MovePoint(2, 3425.416f, -5037.641f, 196.782f, false);
                            else if (_moveCounter == 2)
                                me->GetMotionMaster()->MovePoint(2, 3388.032f, -4978.755f, 196.782f, false);
                            else if (_moveCounter == 3)
                                me->GetMotionMaster()->MovePoint(2, 3374.894f, -4957.670f, 181.182f, false);
                            else if (_moveCounter == 4)
                                me->GetMotionMaster()->MovePoint(2, 3335.971f, -4896.179f, 181.077f, false);
                            else if (_moveCounter == 5)
                                me->GetMotionMaster()->MovePoint(2, 3341.745f, -4882.559f, 181.078f, false);
                            else if (_moveCounter == 6)
                            {
                                follower->SetSpeed(MOVE_RUN, 0.5f);
                                me->SetSpeed(MOVE_RUN, 0.5f);
                                me->GetMotionMaster()->MovePoint(2, 3413.006f, -4842.002f, 181.704f, false);
                            }
                            else if (_moveCounter == 7)
                            {
                                follower->DespawnOrUnsummon(3000);
                                me->DespawnOrUnsummon(0);
                            }
                            break;
                        case EVENT_KILL_PLAYER:
                            if (Player* player = me->FindNearestPlayer(0.1f, true))
                                player->Kill(player);
                            events.ScheduleEvent(EVENT_KILL_PLAYER, 500, 0, PHASE_INTRO);
                            break;
                        case EVENT_PLAY_MARCH_SOUND:
                            me->AddAura(110249, me);
                            events.ScheduleEvent(EVENT_PLAY_MARCH_SOUND, 3000, 0, PHASE_INTRO);
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
        return new npc_legion_demonAI(creature);
    }
};

enum IllidanEvents
{
    EVENT_CLOAK_PLAYERS = 5,
    EVENT_TALK_1,
    EVENT_TALK_2,
};

enum IllidanSpells
{
    SPELL_SHADOWCLOAK           = 105915,
    SPELL_SHADOW_HELPER         = 105924,
    SPELL_SHADOW_VISUAL         = 102951,
    SPELL_AGGRO_CHECK           = 103793,
    SPELL_AGGRO_CLEAR           = 103319,
    SPELL_SHADOW_WALK           = 103020,
    SPELL_RIDE_VEHICLE          = 46598,
    SPELL_SET_VEHICLE_ID        = 105915,

    SPELL_SHADOWCLOOAK_PLAYER   = 110231,
    // 103004 

};

class npc_woe_illidan : public CreatureScript
{
    public:
        npc_woe_illidan() : CreatureScript("npc_woe_illidan") { }

        struct npc_woe_illidanAI : public ScriptedAI
        {
            npc_woe_illidanAI(Creature* creature) : ScriptedAI(creature)
            {
                started = false;
                _moveCounter = 0;
            }

            bool started;
            EventMap events;
            uint8 _moveCounter;

            void Reset()
            {
                me->SetVisible(false);
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case 1:
                        if (!started)
                        {
                            me->SetVisible(true);
                            me->AddAura(SPELL_SHADOWCLOAK, me);
                            me->AddAura(SPELL_SHADOW_HELPER, me);
                            events.ScheduleEvent(EVENT_MOVE_1, 2000);
                            events.ScheduleEvent(EVENT_TALK_1, 4000);
                            TalkToMap(1);
                            started = true;
                        }
                        break;
                    default:
                        break;
                }
            }

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case 0:
                        events.ScheduleEvent(EVENT_MOVE_2, 1);
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
                        case EVENT_MOVE_1:
                            me->GetMotionMaster()->MovePoint(0, 3191.888f, -4895.561f, 194.356f, false);
                            break;
                        case EVENT_MOVE_2:
                            me->RemoveAllAuras();
                            break;
                        case EVENT_TALK_1:
                            TalkToMap(2); // 3285.167f, -4903.393f, 181.211f
                            break;
                        case EVENT_TALK_2:
                        {
                            Map::PlayerList const& player = me->GetMap()->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = player.begin(); itr != player.end(); ++itr)
                                if (Player* player = itr->getSource())
                                    player->AddAura(SPELL_SHADOWCLOAK, player);
                            TalkToMap(3);
                            break;
                        }
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_woe_illidanAI(creature);
    }
};

void AddSC_well_of_eternity()
{
    new at_woe_intro();
    new at_woe_illidan_intro();
    new npc_legion_demon_intro();
    new npc_legion_demon();
    new npc_woe_illidan();
}
