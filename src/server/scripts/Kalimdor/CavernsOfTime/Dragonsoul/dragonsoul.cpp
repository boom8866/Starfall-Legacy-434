
#include "dragonsoul.h"

enum Texts
{
    // Lord Afrasastrasz
    SAY_INTRO_1 = 0,
    SAY_INTRO_2 = 1,
    SAY_INTRO_3 = 2,
    SAY_INTRO_4 = 3,

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

    // Generic Spells
    SPELL_WYRMREST_AGGRO            = 108488,
    SPELL_WYRMREST_DEFENSE_NUKE     = 108536,
};

enum Events
{
    // Lord Afrasastrasz
    EVENT_MOVE_TO_FIRST_LOCATION_1 = 1,
    EVENT_MOVE_TO_FIRST_LOCATION_2,
    EVENT_MOVE_TO_SECOND_LOCATION_1,
    EVENT_MOVE_TO_SECOND_LOCATION_2,
    EVENT_TALK_INTRO_4,
    EVENT_AGGRO_ALLIES,

    EVENT_SUMMON_IMAGE_OF_TYRYGOSA,
    EVENT_TALK_INTRO_2,
    EVENT_SCHEDULE_MORCHOK_TALK_2,
    EVENT_SCHEDULE_MORCHOK_TALK_4,

    // Image of Tyrygosa
    EVENT_TALK_IMAGE_1,
    EVENT_TALK_IMAGE_2,
    EVENT_CAST_IMAGE_EFFECT,

    // Wyrmrest Captain
    EVENT_ENGAGE_COMBAT,
};

enum Actions
{
    // Lord Afrasastrasz
    ACTION_COUNT_MORCHOK_GAUNTLET = 1,

    // Morchok
    ACTION_TRIGGER_FIRST_INTRO = 1,
    ACTION_TRIGGER_SECOND_INTRO,
    ACTION_TRIGGER_THIRD_INTRO,
    ACTION_TRIGGER_FOURTH_INTRO,

    // Wyrmrest Captain
    ACTION_MOVE_TO_COMBAT,
    ACTION_ADANCE_TO_FRONT,
};

enum MovePoints
{
    // Lord Afrasastrasz
    POINT_INTRO_1 = 1,
    POINT_INTRO_2,
    POINT_INTRO_3,
    POINT_INTRO_4,

    // Wyrmrest Captain
    POINT_COMBAT_1,
    POINT_COMBAT_2,
};

Position const AfrasastraszWaypoints[] =
{
    { -2278.106f, -2399.724f, 80.13097f },
    { -2233.105f, -2397.879f, 85.71294f },
    { -2169.329f, -2396.872f, 80.0222f  },
    { -2141.175f, -2398.826f, 80.2487f  },
};

Position const WyrmrestCaptainLeftComparisionPosition = { -2281.760f, -2367.352f, 83.591f };
Position const WyrmrestCaptainLeftWaypoints[] =
{
    { -2222.689f, -2351.419f, 80.4443f },
};

Position const WyrmrestCaptainRightWaypoints[] =
{
    {0.0f},
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
                    else if (_gauntletCount == 6)
                    {
                        events.ScheduleEvent(EVENT_MOVE_TO_SECOND_LOCATION_1, 10000);
                        if (Creature* morchok = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MORCHOK)))
                            morchok->AI()->DoAction(ACTION_TRIGGER_THIRD_INTRO);
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
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_CRIMSON_LIFEBINDER, 10.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_DEFENDER_1, 10.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_DEFENDER_2, 10.0f);
                        if (!units.empty())
                            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                (*itr)->GetMotionMaster()->MoveFollow(me, (*itr)->GetDistance2d(me), ((*itr)->GetAngle(me->GetPositionX(), me->GetPositionY()) + M_PI));
                        units.clear();

                        // Build Wyrmrest Captain Formations and move them.
                        GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_CAPTAIN, 50.0f);
                        if (!units.empty())
                            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                (*itr)->AI()->DoAction(ACTION_MOVE_TO_COMBAT);

                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_1, AfrasastraszWaypoints[0]);
                        Talk(SAY_INTRO_1);
                        break;
                    }
                    case EVENT_MOVE_TO_FIRST_LOCATION_2:
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_2, AfrasastraszWaypoints[1]);
                        break;
                    case EVENT_SUMMON_IMAGE_OF_TYRYGOSA:
                        DoCast(me, SPELL_SUMMON_IMAGE_OF_TYRYGOSA, true);
                        events.ScheduleEvent(EVENT_TALK_INTRO_2, 20500);
                        events.ScheduleEvent(EVENT_SCHEDULE_MORCHOK_TALK_2, 24000);
                        events.ScheduleEvent(EVENT_AGGRO_ALLIES, 2000);
                        break;
                    case EVENT_TALK_INTRO_2:
                        Talk(SAY_INTRO_2);
                        break;
                    case EVENT_SCHEDULE_MORCHOK_TALK_2:
                        if (Creature* morchok = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MORCHOK)))
                            morchok->AI()->DoAction(ACTION_TRIGGER_SECOND_INTRO);
                        break;
                    case EVENT_MOVE_TO_SECOND_LOCATION_1:
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_3, AfrasastraszWaypoints[2]);
                        Talk(SAY_INTRO_3);
                        break;
                    case EVENT_MOVE_TO_SECOND_LOCATION_2:
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_4, AfrasastraszWaypoints[3]);
                        break;
                    case EVENT_TALK_INTRO_4:
                        Talk(SAY_INTRO_4);
                        events.ScheduleEvent(EVENT_SCHEDULE_MORCHOK_TALK_4, 8000);
                        break;
                    case EVENT_SCHEDULE_MORCHOK_TALK_4:
                        if (Creature* morchok = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MORCHOK)))
                            morchok->AI()->DoAction(ACTION_TRIGGER_FOURTH_INTRO);
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
                case POINT_INTRO_3:
                    events.ScheduleEvent(EVENT_MOVE_TO_SECOND_LOCATION_2, 1);
                    break;
                case POINT_INTRO_4:
                    events.ScheduleEvent(EVENT_TALK_INTRO_4, 1);
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

class npc_ds_wyrmrest_captain : public CreatureScript
{
public:
    npc_ds_wyrmrest_captain() : CreatureScript("npc_ds_wyrmrest_captain") { }

    struct npc_ds_wyrmrest_captainAI : public ScriptedAI
    {
        npc_ds_wyrmrest_captainAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void DamageTaken(Unit* /*damager*/, uint32& damage)
        {
            damage = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_MOVE_TO_COMBAT:
            {
                std::list<Creature*> units;
                GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_PROTECTOR, 10.0f);
                GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_DEFENDER_1, 10.0f);
                GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_DEFENDER_2, 10.0f);
                if (!units.empty())
                    for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        (*itr)->GetMotionMaster()->MoveFollow(me, (*itr)->GetDistance2d(me), ((*itr)->GetAngle(me->GetPositionX(), me->GetPositionY()) + M_PI));
                me->SetWalk(false);
                if (me->GetDistance2d(WyrmrestCaptainLeftComparisionPosition.GetPositionX(), WyrmrestCaptainLeftComparisionPosition.GetPositionY() <= 15.0f))
                    me->GetMotionMaster()->MovePoint(POINT_COMBAT_1, WyrmrestCaptainLeftWaypoints[0]);
                    break;
                }
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
                    case EVENT_ENGAGE_COMBAT:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_PROTECTOR, 10.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_DEFENDER_1, 10.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_WYRMREST_DEFENDER_2, 10.0f);
                        if (!units.empty())
                            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                (*itr)->AI()->DoCast((*itr), SPELL_WYRMREST_AGGRO, true);
                        break;
                    }
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
                case POINT_COMBAT_1:
                    events.ScheduleEvent(EVENT_ENGAGE_COMBAT, 1);
                    break;
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_wyrmrest_captainAI(creature);
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
    new npc_ds_wyrmrest_captain();
    new npc_ds_earthen_destroyer();
    new npc_ds_ancient_water_lord();
}
