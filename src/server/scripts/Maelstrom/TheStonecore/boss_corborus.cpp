
#include "ScriptPCH.h"
#include "the_stonecore.h"

enum Spells
{
    SPELL_RING_WYRM_CHARGE      = 81237,
    SPELL_RING_WYRM_KNOCKBACK   = 81235,
};

enum Events
{
    EVENT_INTRO = 1,
    EVENT_KNOCKBACK,
};

enum Actions
{
    ACTION_INTRO = 1,
};

enum Phases
{
    PHASE_INTRO = 1,
    PHASE_BATTLE = 2,
};

Position const HomePos = {1154.55f, 878.843f, 286.0f, 3.2216f};

class boss_corborus : public CreatureScript
{
public:
    boss_corborus() : CreatureScript("boss_corborus") { }

    struct boss_corborusAI : public BossAI
    {
        boss_corborusAI(Creature* creature) : BossAI(creature, DATA_CORBORUS)
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
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->GetMotionMaster()->MoveTargetedHome();
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
                    case EVENT_INTRO:
                        if (GameObject* wall = me->FindNearestGameObject(GO_ROCKDOOR, 300.0f))
                            wall->SetGoState(GO_STATE_ACTIVE);
                        me->SetHomePosition(HomePos);
                        DoCastAOE(SPELL_RING_WYRM_CHARGE);
                        events.ScheduleEvent(EVENT_KNOCKBACK, 700);
                        break;
                    case EVENT_KNOCKBACK:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_STONECORE_BERSERKER, 200.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_STONECORE_EARTHSHAPER, 200.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_STONECORE_WARBRINGER, 200.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_MILLHOUSE_MANASTORM, 200.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->CastStop();
                            (*itr)->DespawnOrUnsummon(3000);
                            (*itr)->AI()->DoCastAOE(SPELL_RING_WYRM_KNOCKBACK);
                        }
                        events.SetPhase(PHASE_BATTLE);
                        EnterEvadeMode();
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INTRO:
                    events.SetPhase(PHASE_INTRO);
                    events.ScheduleEvent(EVENT_INTRO, 2600);
                    sLog->outError(LOG_FILTER_SQL, "intro event (Corborus script) activated!");
                    break;
            }
        }

        void JustSummoned(Creature* summon)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_corborusAI (creature);
    }
};

void AddSC_boss_corborus()
{
    new boss_corborus();
}
