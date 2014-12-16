
#include "bastion_of_twilight.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_ABILITY = 2,
    SAY_DEATH   = 3,
};

enum Spells
{
};

enum Events
{
    // Feludius

    // Ignacious
    EVENT_TALK_INTRO = 1,


};

enum Actions
{
    ACTION_INTRO_1,
    ACTION_INTRO_2,
    ACTION_INTRO_3,
};

class at_ascendant_council_1 : public AreaTriggerScript
{
public:
    at_ascendant_council_1() : AreaTriggerScript("at_ascendant_council_1") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_1);
        return true;
    }
};

class at_ascendant_council_2 : public AreaTriggerScript
{
public:
    at_ascendant_council_2() : AreaTriggerScript("at_ascendant_council_2") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_2);
        return true;
    }
};

class at_ascendant_council_3 : public AreaTriggerScript
{
public:
    at_ascendant_council_3() : AreaTriggerScript("at_ascendant_council_3") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_3);
        return true;
    }
};

class boss_feludius : public CreatureScript
{
public:
    boss_feludius() : CreatureScript("boss_feludius") { }

    struct boss_feludiusAI : public BossAI
    {
        boss_feludiusAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL)
        {
        }

        void Reset()
        {
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                ignacious->AI()->AttackStart(who);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_feludiusAI(creature);
    }
};

class boss_ignacious : public CreatureScript
{
public:
    boss_ignacious() : CreatureScript("boss_ignacious") { }

    struct boss_ignaciousAI : public BossAI
    {
        boss_ignaciousAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL)
        {
        }

        void Reset()
        {
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TALK_INTRO, 4000);
            if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                feludius->AI()->AttackStart(who);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_INTRO:
                        Talk(SAY_AGGRO);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ignaciousAI(creature);
    }
};

class npc_ascendant_council_controller : public CreatureScript
{
public:
    npc_ascendant_council_controller() : CreatureScript("npc_ascendant_council_controller") { }

    struct npc_ascendant_council_controllerAI : public ScriptedAI
    {
        npc_ascendant_council_controllerAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
            _intro1Done = false;
            _intro2Done = false;
            _intro3Done = false;
        }

        InstanceScript* instance;
        SummonList summons;
        EventMap events;
        bool _intro1Done;
        bool _intro2Done;
        bool _intro3Done;

        void Reset()
        {
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INTRO_1:
                    if (!_intro1Done)
                    {
                        if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                            chogall->AI()->TalkToMap(4);
                        _intro1Done = true;
                    }
                    break;
                case ACTION_INTRO_2:
                    if (!_intro2Done)
                    {
                        if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                            chogall->AI()->TalkToMap(5);
                        _intro2Done = true;
                    }
                    break;
                case ACTION_INTRO_3:
                    if (!_intro3Done)
                    {
                        if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                            chogall->AI()->TalkToMap(6);
                        _intro3Done = true;
                    }
                    break;
                default:
                    break;
            }
        }


        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ascendant_council_controllerAI(creature);
    }
};


void AddSC_boss_ascendant_council()
{
    new at_ascendant_council_1();
    new at_ascendant_council_2();
    new at_ascendant_council_3();
    new boss_feludius();
    new boss_ignacious();
    new npc_ascendant_council_controller();
}
