
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
    // Feludius
    SPELL_WATER_BOMB            = 82699,
    SPELL_WATER_BOMB_TRIGGERED  = 82700,

    // Ignacious
    SPELL_AEGIS_OF_FLAME        = 82631,
    SPELL_RISING_FLAMES         = 82636,
};

enum Events
{
    // Feludius
    EVENT_WATER_BOMB = 1,

    // Ignacious
    EVENT_TALK_INTRO,
    EVENT_AEGIS_OF_FLAME,
    EVENT_RISING_FLAMES,

};

enum Actions
{
    ACTION_INTRO_1 = 1,
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
        boss_feludiusAI(Creature* creature) : BossAI(creature, DATA_FELUDIUS)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                ignacious->AI()->AttackStart(who);

            events.ScheduleEvent(EVENT_WATER_BOMB, 15000); // 33-35 seconds cooldown
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
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
                    case EVENT_WATER_BOMB:
                        for (uint8 i = 0; i < 16; i++)
                        {
                            float distance = frand(2.0f, 50.0f);
                            float ori = frand(0.0f, M_PI * 2);
                            float x = me->GetPositionX() + cos(ori) * distance;
                            float y = me->GetPositionY() + sin(ori) * distance;
                            float z = me->GetPositionZ();
                            me->SummonCreature(NPC_WATER_BOMB, x, y, z, ori, TEMPSUMMON_TIMED_DESPAWN, 15000);
                        }
                        DoCast(SPELL_WATER_BOMB);
                        events.ScheduleEvent(EVENT_WATER_BOMB, urand(33000, 35000));
                        break;
                    default:
                        break;
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
        boss_ignaciousAI(Creature* creature) : BossAI(creature, DATA_IGNACIOUS)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TALK_INTRO, 4000);
            events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, 31000);
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
                    case EVENT_AEGIS_OF_FLAME:
                        DoCast(me, SPELL_AEGIS_OF_FLAME);
                        events.ScheduleEvent(EVENT_RISING_FLAMES, 1600);
                        break;
                    case EVENT_RISING_FLAMES:
                        DoCast(me, SPELL_RISING_FLAMES);
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

class boss_terrastra : public CreatureScript
{
public:
    boss_terrastra() : CreatureScript("boss_terrastra") { }

    struct boss_terrastraAI : public BossAI
    {
        boss_terrastraAI(Creature* creature) : BossAI(creature, DATA_TERRASTRA)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
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
        return new boss_terrastraAI(creature);
    }
};

class boss_arion : public CreatureScript
{
public:
    boss_arion() : CreatureScript("boss_arion") { }

    struct boss_arionAI : public BossAI
    {
        boss_arionAI(Creature* creature) : BossAI(creature, DATA_ARION)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
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
        return new boss_arionAI(creature);
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

class spell_ac_water_bomb : public SpellScriptLoader
{
public:
    spell_ac_water_bomb() : SpellScriptLoader("spell_ac_water_bomb") { }

    class spell_ac_water_bomb_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_water_bomb_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_WATER_BOMB_TRIGGERED, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_water_bomb_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_water_bomb_SpellScript();
    }
};

void AddSC_boss_ascendant_council()
{
    new at_ascendant_council_1();
    new at_ascendant_council_2();
    new at_ascendant_council_3();
    new boss_feludius();
    new boss_ignacious();
    new boss_terrastra();
    new boss_arion();
    new npc_ascendant_council_controller();
    new spell_ac_water_bomb();
}
