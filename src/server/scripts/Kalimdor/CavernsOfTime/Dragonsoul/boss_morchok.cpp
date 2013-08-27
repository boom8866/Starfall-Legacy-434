
#include "dragonsoul.h"

enum Spells
{
    SPELL_SIEGE_MISSILE                 = 110307,
    SPELL_STOMP                         = 103414,

    SPELL_SUMMON_CRYSTAL                = 103640,
    SPELL_CRYSTAL_AURA                  = 103494,
    SPELL_CRYSTAL_EXPLOSION             = 103545,

    SPELL_FALLING_FRAGMENT_KNOCKBACK    = 103174,
    SPELL_FALLING_FRAGMENT              = 103177,

    SPELL_BLOOD_VISUAL                  = 103180,

    SPELL_RAGE                          = 103846,
};

enum Texts
{
    SAY_SIEGE               = 1,
    SAY_AGGRO               = 2,
    SAY_SLAY                = 3,
    SAY_ANNOUNCE_CRYSTAL    = 4,
    SAY_CRYSTAL             = 5,
    SAY_EARTHS_VENGEANCE    = 6,
    SAY_BLOOD_OF_ANCIENTS   = 7,
    SAY_DEATH               = 8,
};

enum Phases
{
    PHASE_INTRO     = 1,
    PHASE_COMBAT    = 2,
};

enum Events
{
    EVENT_SIEGE_INTRO           = 1,
    EVENT_STOMP                 = 2,
    EVENT_RESONATING_CRYSTAL    = 3,
};

enum Actions
{
    ACTION_START_INTRO  = 1,
};

Position const SiegePos1 = {-1874.589f, -2366.159f, 128.197f, 0.0f};
Position const SiegePos2 = {-1861.810f, -2406.899f, 143.921f, 0.0f};
Position const SiegePos3 = {-1869.317f, -2428.761f, 141.404f, 0.0f};

class boss_morchok : public CreatureScript
{
public:
    boss_morchok() : CreatureScript("boss_morchok") { }

    struct boss_morchokAI : public BossAI
    {
        boss_morchokAI(Creature* creature) : BossAI(creature, DATA_MORCHOK)
        {
            _introStarted = false;
        }

        bool _introStarted;

        void Reset()
        {
            DoAction(ACTION_START_INTRO);
            _introStarted = true;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.SetPhase(PHASE_COMBAT);
            events.ScheduleEvent(EVENT_STOMP, 12000, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, 19000, 0, PHASE_COMBAT);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        /*
        void MoveInLineOfSight(Unit* who)
        {
            if (!_introStarted && me->IsWithinDistInMap(who, 400.0f))
            {
                DoAction(ACTION_START_INTRO);
                _introStarted = true;
            }
        }
        */

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_RESONATING_CRYSTAL:
                    summon->AddAura(SPELL_CRYSTAL_AURA, summon);
                    break;
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_INTRO:
                    events.SetPhase(PHASE_INTRO);
                    events.ScheduleEvent(EVENT_SIEGE_INTRO, 10000);
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
                    case EVENT_SIEGE_INTRO:
                        Talk(SAY_SIEGE);
                        switch (urand(0,2))
                        {
                            case 0:
                            {
                                if (Unit* target = me->SummonCreature(NPC_SIEGE_TARGET, SiegePos1, TEMPSUMMON_TIMED_DESPAWN, 10000))
                                    DoCast(target, SPELL_SIEGE_MISSILE);
                                break;
                            }
                            case 1:
                            {
                                if (Unit* target = me->SummonCreature(NPC_SIEGE_TARGET, SiegePos2, TEMPSUMMON_TIMED_DESPAWN, 10000))
                                    DoCast(target, SPELL_SIEGE_MISSILE);
                                break;
                            }
                            case 2:
                            {
                                if (Unit* target = me->SummonCreature(NPC_SIEGE_TARGET, SiegePos3, TEMPSUMMON_TIMED_DESPAWN, 10000))
                                    DoCast(target, SPELL_SIEGE_MISSILE);
                                break;
                            }
                        }
                        events.ScheduleEvent(EVENT_SIEGE_INTRO, 20000, 0, PHASE_INTRO);
                        break;
                    case EVENT_STOMP:
                        DoCastAOE(SPELL_STOMP);
                        events.ScheduleEvent(EVENT_STOMP, 12000, 0, PHASE_COMBAT);
                        break;
                    case EVENT_RESONATING_CRYSTAL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_SUMMON_CRYSTAL);
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
        return new boss_morchokAI(creature);
    }
};

void AddSC_boss_morchok()
{
    new boss_morchok();
}