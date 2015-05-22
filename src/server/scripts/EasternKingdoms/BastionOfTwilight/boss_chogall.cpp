
#include "bastion_of_twilight.h"
#include "Vehicle.h"

enum Texts
{
    SAY_INTRO       = 7,
    SAY_AGGRO       = 8,
};

enum Spells
{
    // Cho'Gall
    SPELL_SIT_THRONE            = 88648,
    SPELL_BOSS_HITTIN_YA        = 73878,
    SPELL_CORRUPTED_BLOOD       = 93104,
    SPELL_CORRUPTED_BLOOD_BAR   = 93103,
    SPELL_FLAMES_ORDERS         = 81171,
    SPELL_SHADOWS_ORDERS        = 87575,
    SPELL_ABSORB_FIRE           = 81196,
    SPELL_ABSORB_SHADOW         = 81566,
    SPELL_CONVERSION            = 91303,
    SPELL_BLAZE                 = 81536
};

enum Phases
{
    PHASE_NULL  = 0,
    PHASE_ONE,
    PHASE_TWO
};

enum Events
{
    EVENT_FLAMES_ORDERS      = 1,
    EVENT_SHADOWS_ORDERS,
    EVENT_FURY_OF_CHOGALL,
    EVENT_SUMMON_ADHERENT,
    EVENT_FESTER_BLOOD,
};

enum Actions
{
    ACTION_TALK_INTRO = 1,
};

enum npcId
{
    NPC_FIRE_LORD       = 47017,
    NPC_SHADOW_LORD     = 47016,
};

enum portalEvents
{
    EVENT_SUMMON_FLAME_LORD     = 1,
    EVENT_SUMMON_SHADOW_LORD
};

enum portalSpells
{
    SPELL_FIRE_PORTAL_VISUAL    = 81172,
    SPELL_SUMMON_FLAME_LORD     = 87582,
    SPELL_FO_PERIODIC           = 87581,
    SPELL_SHADOW_PORTAL_VISUAL  = 81559,
    SPELL_SUMMON_SHADOW_LORD    = 87583,
    SPELL_SO_PERIODIC           = 87576
};

class at_chogall_intro : public AreaTriggerScript
{
public:
    at_chogall_intro() : AreaTriggerScript("at_chogall_intro") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(BOSS_CHOGALL, 500.0f, true))
            controller->AI()->DoAction(ACTION_TALK_INTRO);
        return true;
    }
};

class boss_chogall : public CreatureScript
{
public:
    boss_chogall() : CreatureScript("boss_chogall") { }

    struct boss_chogallAI: public BossAI
    {
        boss_chogallAI(Creature* creature) : BossAI(creature, DATA_CHOGALL)
        {
            _introDone = false;
        }

        bool _introDone;

        void Reset()
        {
            _Reset();
            DoCast(me, SPELL_SIT_THRONE, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->RemoveAurasDueToSpell(SPELL_SIT_THRONE);
            DoCast(me, SPELL_CORRUPTED_BLOOD);
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_FLAMES_ORDERS, 5000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_SHADOWS_ORDERS, 15000, 0, PHASE_ONE);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SetBossState(DATA_CHOGALL, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_BLOOD_BAR);
            me->DespawnCreaturesInArea(NPC_BLAZE);
            me->DespawnCreaturesInArea(NPC_FIRE_PORTAL);
            me->DespawnCreaturesInArea(NPC_SHADOW_PORTAL);
            summons.DespawnAll();
            events.Reset();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            events.Reset();
            instance->SetBossState(DATA_CHOGALL, DONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_BLOOD_BAR);
        }

        void JustRespawned()
        {
            Reset();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TALK_INTRO:
                    if (!_introDone)
                    {
                        TalkToMap(SAY_INTRO);
                        _introDone = true;
                    }
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FLAMES_ORDERS:
                        DoCast(SPELL_FLAMES_ORDERS);
                        events.RescheduleEvent(EVENT_FLAMES_ORDERS, 50000, 0, PHASE_ONE);
                        break;
                    case EVENT_SHADOWS_ORDERS:
                        DoCast(SPELL_SHADOWS_ORDERS);
                        events.RescheduleEvent(EVENT_SHADOWS_ORDERS, 50000, 0, PHASE_ONE);
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
        return new boss_chogallAI(creature);
    }
};

class npc_bot_fire_portal : public CreatureScript
{
public:
    npc_bot_fire_portal() : CreatureScript("npc_bot_fire_portal") {}

    struct npc_bot_fire_portalAI : public ScriptedAI
    {
        npc_bot_fire_portalAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            DoCast(SPELL_FIRE_PORTAL_VISUAL);
        }

        InstanceScript* instance;
        EventMap events;

        void JustSummoned(Creature* creature)
        {
            if (creature->GetEntry() == NPC_FIRE_LORD)
            {
                creature->CastSpell(creature, SPELL_ABSORB_FIRE, true);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetSpeed(MOVE_WALK, 0.75f, true);
                creature->SetSpeed(MOVE_RUN, 0.75f, true);
                creature->SetReactState(REACT_PASSIVE);
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_FLAME_LORD, 5500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_FLAME_LORD:
                    {
                        DoCast(me, SPELL_SUMMON_FLAME_LORD);
                        me->DespawnOrUnsummon(5000);
                        return;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_fire_portalAI(creature);
    }
};

class npc_bot_shadow_portal : public CreatureScript
{
public:
    npc_bot_shadow_portal() : CreatureScript("npc_bot_shadow_portal") {}

    struct npc_bot_shadow_portalAI : public ScriptedAI
    {
        npc_bot_shadow_portalAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            DoCast(SPELL_SHADOW_PORTAL_VISUAL);
        }

        InstanceScript* instance;
        EventMap events;

        void JustSummoned(Creature* creature)
        {
            if (creature->GetEntry() == NPC_SHADOW_LORD)
            {
                creature->CastSpell(creature, SPELL_ABSORB_SHADOW, true);
                creature->SetSpeed(MOVE_WALK, 0.75f, true);
                creature->SetSpeed(MOVE_RUN, 0.75f, true);
                creature->SetReactState(REACT_PASSIVE);
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_SHADOW_LORD, 5500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_SHADOW_LORD:
                    {
                        DoCast(me, SPELL_SUMMON_SHADOW_LORD);
                        me->DespawnOrUnsummon(5000);
                        return;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_shadow_portalAI(creature);
    }
};

class npc_bot_blaze : public CreatureScript
{
public:
    npc_bot_blaze() : CreatureScript("npc_bot_blaze") {}

    struct npc_bot_blazeAI : public ScriptedAI
    {

        npc_bot_blazeAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->AddAura(SPELL_BLAZE, me);
            me->DespawnOrUnsummon(25000);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_blazeAI(creature);
    }
};

void AddSC_boss_chogall()
{
    new at_chogall_intro();
    new boss_chogall();
    new npc_bot_fire_portal();
    new npc_bot_shadow_portal();
    new npc_bot_blaze();
}
