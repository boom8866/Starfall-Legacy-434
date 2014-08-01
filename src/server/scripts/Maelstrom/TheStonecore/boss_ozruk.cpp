#include "ScriptPCH.h"
#include "the_stonecore.h"

enum Texts
{
    SAY_AGGRO                       = 0,
    SAY_ANNOUNCE_ELEMENTIUM_BULWARK = 1,
    SAY_SHIELD                      = 2,
    SAY_ANNOUNCE_ENRAGE             = 3,
    SAY_SLAY                        = 4,
    SAY_DEATH                       = 5,
};

enum Spells
{
    // Ozruk
    SPELL_GROUND_SLAM               = 78903,
    SPELL_ELEMENTIUM_BULWARK        = 78939,
    SPELL_ELEMENTIUM_SPIKE_SHIELD   = 78835,
    SPELL_SHATTER                   = 78807,
    SPELL_PARALIZE                  = 92426,
    SPELL_ENRAGE                    = 80467,

    // Rupture Controller
    SPELL_RUPTURE_TRIGGER_SUMMON    = 92383,
    SPELL_RUPTURE_AURA              = 92393,

    // Rupture Dummy
    SPELL_RUPTURE_KNOCKBACK         = 92381,

    // Spell Bouncer Spike
    SPELL_RIDE_VEHICLE              = 46598,
};

enum Events
{
    // Ozruk
    EVENT_GROUND_SLAM = 1,
    EVENT_ELEMENTIUM_BULWARK,
    EVENT_ELEMENTIUM_SPIKE_SHIELD,
    EVENT_SHATTER,
    EVENT_PARALYZE,
    EVENT_ENRAGE,
    EVENT_MOVE,

    // Rupture
    EVENT_RUPTURE_SUMMON,
    EVENT_KNOCKBACK,
    EVENT_SUBMERGE,
};

class boss_ozruk : public CreatureScript
{
public:
    boss_ozruk() : CreatureScript("boss_ozruk") { }

    struct boss_ozrukAI : public BossAI
    {
        boss_ozrukAI(Creature* creature) : BossAI(creature, DATA_OZRUK)
        {
            enraged = false;
        }

        bool enraged;

        void Reset()
        {
            _Reset();
            enraged = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            _EnterCombat();
            events.ScheduleEvent(EVENT_GROUND_SLAM, 12000);
            events.ScheduleEvent(EVENT_ELEMENTIUM_BULWARK, 6000);
            events.ScheduleEvent(EVENT_ELEMENTIUM_SPIKE_SHIELD, 11000);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            _JustDied();
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _EnterEvadeMode();
            enraged = false;
            summons.DespawnAll();
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_BOUNCER_SPIKE:
                case NPC_BOUNCER_SPIKE_SMALL:
                    summon->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                    summon->setFaction(35);
                    summons.Summon(summon);
                    break;
            }
        }

        void SummonSpikes()
        {
            if (Creature* spike0 = me->SummonCreature(NPC_BOUNCER_SPIKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike0->EnterVehicle(me, 0);
            if (Creature* spike1 = me->SummonCreature(NPC_BOUNCER_SPIKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike1->EnterVehicle(me, 1);
            if (Creature* spike2 = me->SummonCreature(NPC_BOUNCER_SPIKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike2->EnterVehicle(me, 2);
            if (Creature* spike3 = me->SummonCreature(NPC_BOUNCER_SPIKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike3->EnterVehicle(me, 3);
            if (Creature* spike4 = me->SummonCreature(NPC_BOUNCER_SPIKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike4->EnterVehicle(me, 4);
            if (Creature* spike5 = me->SummonCreature(NPC_BOUNCER_SPIKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike5->EnterVehicle(me, 5);
            if (Creature* spike6 = me->SummonCreature(NPC_BOUNCER_SPIKE_SMALL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike6->EnterVehicle(me, 6);
            if (Creature* spike7 = me->SummonCreature(NPC_BOUNCER_SPIKE_SMALL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 11000))
                spike7->EnterVehicle(me, 7);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(25) && !enraged)
            {
                enraged = true;
                events.ScheduleEvent(EVENT_ENRAGE, 1);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if(!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GROUND_SLAM:
                        DoCastAOE(SPELL_GROUND_SLAM);
                        me->GetMotionMaster()->Clear();
                        me->AddUnitState(UNIT_STATE_CANNOT_TURN);
                        events.ScheduleEvent(EVENT_GROUND_SLAM, 18000);
                        events.ScheduleEvent(EVENT_MOVE, 3100);
                        break;
                    case EVENT_ELEMENTIUM_BULWARK:
                        Talk(SAY_ANNOUNCE_ELEMENTIUM_BULWARK);
                        DoCastAOE(SPELL_ELEMENTIUM_BULWARK);
                        events.ScheduleEvent(EVENT_ELEMENTIUM_BULWARK, 20000);
                        break;
                    case EVENT_ELEMENTIUM_SPIKE_SHIELD:
                        Talk(SAY_SHIELD);
                        SummonSpikes();
                        DoCastAOE(SPELL_ELEMENTIUM_SPIKE_SHIELD);
                        events.ScheduleEvent(EVENT_ELEMENTIUM_SPIKE_SHIELD, 23000);
                        events.ScheduleEvent(EVENT_SHATTER, 11000);
                        if (IsHeroic())
                            events.ScheduleEvent(EVENT_PARALYZE, 8000);
                        break;
                    case EVENT_PARALYZE:
                        DoCastAOE(SPELL_PARALIZE);
                        break;
                    case EVENT_SHATTER:
                        DoCastAOE(SPELL_SHATTER);
                        break;
                    case EVENT_ENRAGE:
                        Talk(SAY_ANNOUNCE_ENRAGE);
                        DoCastAOE(SPELL_ENRAGE);
                        break;
                    case EVENT_MOVE:
                        me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
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
        return new boss_ozrukAI (creature);
    }
};

class npc_tsc_rupture_controller : public CreatureScript
{
public:
    npc_tsc_rupture_controller() : CreatureScript("npc_tsc_rupture_controller") { }

    struct npc_tsc_rupture_controllerAI : public ScriptedAI
    {
        npc_tsc_rupture_controllerAI(Creature* creature) : ScriptedAI(creature) 
        {
            _counter = 0;
        }

        EventMap events;
        uint8 _counter;

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void IsSummonedBy(Unit* summoner)
        {
            events.ScheduleEvent(EVENT_RUPTURE_SUMMON, 100);
            if (summoner->GetEntry() == BOSS_OZRUK)
            {
                me->SummonCreature(NPC_RUPTURE_CONTROLLER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation() + 0.25f);
                me->SummonCreature(NPC_RUPTURE_CONTROLLER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation() - 0.25f);
            }
        }
        
        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RUPTURE_SUMMON:
                        if (_counter <= 10)
                        {
                            _counter ++;
                            me->CastSpell(me->GetPositionX()+cos(me->GetOrientation())*(_counter * 5), me->GetPositionY()+sin(me->GetOrientation())*(_counter * 5), me->GetPositionZ(), SPELL_RUPTURE_TRIGGER_SUMMON, true);
                            events.ScheduleEvent(EVENT_RUPTURE_SUMMON, 100);
                        }
                        else
                            me->DespawnOrUnsummon(1);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tsc_rupture_controllerAI(creature);
    }
};


class npc_tsc_rupture : public CreatureScript
{
public:
    npc_tsc_rupture() : CreatureScript("npc_tsc_rupture") { }

    struct npc_tsc_ruptureAI : public ScriptedAI
    {
        npc_tsc_ruptureAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
            events.ScheduleEvent(EVENT_KNOCKBACK, 1);
            events.ScheduleEvent(EVENT_SUBMERGE, 3000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_KNOCKBACK:
                        DoCastAOE(SPELL_RUPTURE_KNOCKBACK);
                        break;
                    case EVENT_SUBMERGE:
                        me->DespawnOrUnsummon(100);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tsc_ruptureAI(creature);
    }
};

void AddSC_boss_ozruk()
{
    new boss_ozruk();
    new npc_tsc_rupture_controller();
    new npc_tsc_rupture();
}
