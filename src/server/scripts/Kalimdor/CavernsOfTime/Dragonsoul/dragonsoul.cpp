
#include "dragonsoul.h"

enum Texts
{
    // Lord Afrasastrasz
    SAY_INTRO_1 = 0,
    SAY_INTRO_2 = 1,

    // Image of Tyrygosa
    SAY_IMAGE_1 = 0,
    SAY_IMAGE_2 = 1,
};

enum Spells
{
    // Lord Afrasastrasz
    SPELL_SUMMON_IMAGE_OF_TYRYGOSA  = 108924,

    // Image of Tyrygosa
    SPELL_IMAGE_EFFECT              = 108841,
};

enum Events
{
    // Lord Afrasastrasz
    EVENT_MOVE_TO_FIRST_LOCATION_1 = 1,
    EVENT_MOVE_TO_FIRST_LOCATION_2,
    EVENT_SUMMON_IMAGE_OF_TYRYGOSA,
    EVENT_TALK_INTRO_2,
    EVENT_SCHEDULE_MORCHOK_TALK_2,

    // Image of Tyrygosa
    EVENT_TALK_IMAGE_1,
    EVENT_TALK_IMAGE_2,
    EVENT_CAST_IMAGE_EFFECT,
};

enum Actions
{
    ACTION_COUNT_MORCHOK_GAUNTLET = 1,
    ACTION_TRIGGER_FIRST_INTRO = 1,
    ACTION_TRIGGER_SECOND_INTRO,
};

enum MovePoints
{
    POINT_INTRO_1 = 1,
    POINT_INTRO_2,
    POINT_INTRO_3,
};

Position const AfrasastraszWaypoints[] =
{
    {-2278.106f, -2399.724f, 80.13097f },
    {-2233.105f, -2397.879f, 85.71294f },
};

// We're using following position to decide between the required and the optional waves
Position const FirstWaveComparisionLocation = { -2226.900f, -2400.812f, 85.263f };
Position const SecondWaveComparisionLocation = { -2054.193f, -2407.005f, 73.233f };

class npc_ds_lord_afrasastrasz : public CreatureScript
{
public:
    npc_ds_lord_afrasastrasz() : CreatureScript("npc_ds_lord_afrasastrasz") { }

    struct npc_ds_lord_afrasastraszAI : public ScriptedAI
    {
        npc_ds_lord_afrasastraszAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            _gauntletCount = 0;
        }

        InstanceScript* instance;
        EventMap events;
        uint8 _gauntletCount;

        void DamageTaken(Unit* /*damager*/, uint32& damage)
        {
            damage = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_COUNT_MORCHOK_GAUNTLET:
                    _gauntletCount++;
                    if (_gauntletCount == 2)
                    {
                        events.ScheduleEvent(EVENT_MOVE_TO_FIRST_LOCATION_1, 10000);
                        if (Creature* morchok = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MORCHOK)))
                            morchok->AI()->DoAction(ACTION_TRIGGER_FIRST_INTRO);
                    }
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
                    case EVENT_MOVE_TO_FIRST_LOCATION_1:
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_1, AfrasastraszWaypoints[0]);
                        Talk(SAY_INTRO_1);
                        break;
                    case EVENT_MOVE_TO_FIRST_LOCATION_2:
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_2, AfrasastraszWaypoints[1]);
                        break;
                    case EVENT_SUMMON_IMAGE_OF_TYRYGOSA:
                        DoCast(me, SPELL_SUMMON_IMAGE_OF_TYRYGOSA, true);
                        events.ScheduleEvent(EVENT_TALK_INTRO_2, 20500);
                        events.ScheduleEvent(EVENT_SCHEDULE_MORCHOK_TALK_2, 24000);
                        break;
                    case EVENT_TALK_INTRO_2:
                        Talk(SAY_INTRO_2);
                        break;
                    case EVENT_SCHEDULE_MORCHOK_TALK_2:
                        if (Creature* morchok = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MORCHOK)))
                            morchok->AI()->DoAction(ACTION_TRIGGER_SECOND_INTRO);
                        break;
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case POINT_INTRO_1:
                    events.ScheduleEvent(EVENT_MOVE_TO_FIRST_LOCATION_2, 1);
                    break;
                case POINT_INTRO_2:
                    events.ScheduleEvent(EVENT_SUMMON_IMAGE_OF_TYRYGOSA, 1);
                    break;
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_lord_afrasastraszAI(creature);
    }
};

class npc_ds_image_of_tyrygosa : public CreatureScript
{
public:
    npc_ds_image_of_tyrygosa() : CreatureScript("npc_ds_image_of_tyrygosa") { }

    struct npc_ds_image_of_tyrygosaAI : public ScriptedAI
    {
        npc_ds_image_of_tyrygosaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetFacingToObject(summoner);
            events.ScheduleEvent(EVENT_TALK_IMAGE_1, 3000);
            events.ScheduleEvent(EVENT_CAST_IMAGE_EFFECT, 100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_IMAGE_EFFECT:
                        DoCast(me, SPELL_IMAGE_EFFECT, true);
                        break;
                    case EVENT_TALK_IMAGE_1:
                        Talk(SAY_IMAGE_1);
                        events.ScheduleEvent(EVENT_TALK_IMAGE_2, 11000);
                        break;
                    case EVENT_TALK_IMAGE_2:
                        Talk(SAY_IMAGE_2);
                        me->DespawnOrUnsummon(10000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_image_of_tyrygosaAI(creature);
    }
};

class npc_ds_earthen_destroyer : public CreatureScript
{
public:
    npc_ds_earthen_destroyer() : CreatureScript("npc_ds_earthen_destroyer") { }

    struct npc_ds_earthen_destroyerAI : public ScriptedAI
    {
        npc_ds_earthen_destroyerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*victim*/)
        {
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            if (me->GetHomePosition().GetExactDist2d(FirstWaveComparisionLocation.GetPositionX(), FirstWaveComparisionLocation.GetPositionY() <= 30.0f))
            {
                if (Creature* afrasastrasz = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_LORD_AFRASASTRASZ)))
                    afrasastrasz->AI()->DoAction(ACTION_COUNT_MORCHOK_GAUNTLET);
            }
            else if (me->GetHomePosition().GetExactDist2d(SecondWaveComparisionLocation.GetPositionX(), SecondWaveComparisionLocation.GetPositionY() <= 30.0f))
            {
               if (Creature* afrasastrasz = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_LORD_AFRASASTRASZ)))
                    afrasastrasz->AI()->DoAction(ACTION_COUNT_MORCHOK_GAUNTLET);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_earthen_destroyerAI(creature);
    }
};

class npc_ds_ancient_water_lord : public CreatureScript
{
public:
    npc_ds_ancient_water_lord() : CreatureScript("npc_ds_ancient_water_lord") { }

    struct npc_ds_ancient_water_lordAI : public ScriptedAI
    {
        npc_ds_ancient_water_lordAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*victim*/)
        {
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            if (me->GetHomePosition().GetExactDist2d(FirstWaveComparisionLocation.GetPositionX(), FirstWaveComparisionLocation.GetPositionY() <= 30.0f))
                if (Creature* afrasastrasz = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_LORD_AFRASASTRASZ)))
                    afrasastrasz->AI()->DoAction(ACTION_COUNT_MORCHOK_GAUNTLET);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_ancient_water_lordAI(creature);
    }
};

void AddSC_dragonsoul()
{
    new npc_ds_lord_afrasastrasz();
    new npc_ds_image_of_tyrygosa();
    new npc_ds_earthen_destroyer();
    new npc_ds_ancient_water_lord();
}
