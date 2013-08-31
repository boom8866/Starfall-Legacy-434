
#include "dragonsoul.h"

enum Spells
{
    // Deathwing Intro
    SPELL_MOLTEN_METEOR             = 105022,

    // Ultraxion
    SPELL_TWILIGHT_SHIFT            = 106368,
    SPELL_LIGHTNING_COSMETIC        = 105592,
    SPELL_LIGHTNING_INTRO_SCRIPT    = 109399,

    SPELL_LIGHTNING_INTRO_AURA      = 109402,
};

enum Events
{
    // Deathwing Intro
    EVENT_MOVE_1 = 1,
    EVENT_MOVE_2,
    EVENT_MOVE_3,
    EVENT_MOVE_TO_PLATFORM,

    EVENT_ULTRAXION_ACTIVATE,
    EVENT_TALK_ANNOUNCE,
    EVENT_TALK_ANNOUNCE_2,
    EVENT_TALK_1,
    EVENT_TALK_2,
    EVENT_CAST_FINAL_MOVE,
};

enum Points
{
    POINT_1 = 1,
    POINT_2,
    POINT_3,
};

enum Texts
{
    SAY_INTRO_1 = 1,
    SAY_INTRO_2 = 2,
    SAY_ANNOUNCE_SHIFT  = 3,
};

enum Actions
{
    ACTION_START_ULTRAXION_GAUNTLET = 1,
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

class npc_ds_kelacgos : public CreatureScript
{
public:
    npc_ds_kelacgos() : CreatureScript("npc_ds_kalecgos")
    {
        started = false;
    }

    bool started;

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!started)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We are ready!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        creature->AI()->DoAction(ACTION_START_ULTRAXION_GAUNTLET);
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        if (Creature* ysera = creature->FindNearestCreature(NPC_YSERA_ULTRAXION, 100.0f, true))
            ysera->AI()->Talk(1);
        return true;
    }

    struct npc_ds_kelacgosAI : public ScriptedAI
    {
        npc_ds_kelacgosAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_ULTRAXION_GAUNTLET:
                    events.ScheduleEvent(EVENT_ULTRAXION_ACTIVATE, 10000);
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
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ULTRAXION_ACTIVATE:
                    {

                        if (InstanceScript* instance = me->GetInstanceScript())
                        {
                            if (Creature* ultraxion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ULTRAXION)))
                            {
                                ultraxion->AI()->DoAction(2);
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_kelacgosAI(creature);
    }
};

class boss_ultraxion : public CreatureScript
{
public:
    boss_ultraxion() : CreatureScript("boss_ultraxion") { }

    struct boss_ultraxionAI : public BossAI
    {
        boss_ultraxionAI(Creature* creature) : BossAI(creature, DATA_ULTRAXION)
        {
        }

        void Reset()
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case 2:
                    me->SetPhaseMask(1, true);
                    Talk(SAY_INTRO_1);
                    events.ScheduleEvent(EVENT_TALK_ANNOUNCE, 7000);
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
                    case EVENT_TALK_ANNOUNCE:
                        instance->DoCastSpellOnPlayers(SPELL_TWILIGHT_SHIFT);
                        if (Creature* alex = me->FindNearestCreature(56630, 500.0f, true))
                            alex->SetPhaseMask(16, true);
                        if (Creature* ysera = me->FindNearestCreature(NPC_YSERA_ULTRAXION, 500.0f, true))
                            ysera->SetPhaseMask(16, true);
                        if (Creature* noz = me->FindNearestCreature(56666, 500.0f, true))
                            noz->SetPhaseMask(16, true);
                        if (Creature* thrall = me->FindNearestCreature(56667, 500.0f, true))
                            thrall->SetPhaseMask(16, true);
                        if (Creature* soul = me->FindNearestCreature(NPC_THE_DRAGONSOUL_1, 500.0f, true))
                            soul->SetPhaseMask(16, true);
                        events.ScheduleEvent(EVENT_TALK_ANNOUNCE_2, 1000);
                        me->SetPhaseMask(16, true);
                        break;
                    case EVENT_TALK_ANNOUNCE_2:
                        Talk(SAY_ANNOUNCE_SHIFT);
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
        return new boss_ultraxionAI(creature);
    }
};

void AddSC_boss_ultraxion()
{
    new npc_deathwing_ultraxion();
    new npc_ds_kelacgos();
    new boss_ultraxion();
}
