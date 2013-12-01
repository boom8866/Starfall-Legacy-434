
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
#include "firelands.h"
#include "Creature.h"

enum Texts
{
    SAY_INTRO_1             = 0,
    SAY_INTRO_2             = 1,
    SAY_INTRO_3             = 2,

    SAY_READY               = 3,

    SAY_TRANSFORM           = 4,
    SAY_ANNOUNCE_SCORPION   = 5,
    SAY_ANNOUNCE_CAT        = 6,

    SAY_SLAY                = 7,
    SAY_ORB                 = 8,
    SAY_ANNOUNCE_ORB        = 9,
    SAY_SEED                = 10,
    SAY_ANNOUNCE_SEED       = 11,
    SAY_DEATH               = 12,
};

enum Spells
{
    SPELL_ZERO_ENERGY           = 72242,
    SPELL_CLUMP_CHECK           = 98399, // player cluster check
    SPELL_SCORPION_FORM         = 98379,
    SPELL_CAT_FORM              = 98374,
    SPELL_FURY                  = 97235,
    SPELL_ADRENALINE            = 97238,

    // Cat form
    SPELL_LEAPING_FLAMES_SUMMON = 101222,
    SPELL_LEAPING_FLAMES        = 98476,
    SPELL_LEAPING_FLAMES_DUMMY  = 101165, // target selector
    SPELL_LEAPING_FLAMES_AURA   = 98535,

    // Scorpion Form
    SPELL_FLAME_SCYTHE          = 98474,
};

enum Events
{
    EVENT_CHECK_PLAYER_INTRO = 1,
    EVENT_TALK_INTRO_1,
    EVENT_TALK_INTRO_2,
    EVENT_TALK_INTRO_3,
    EVENT_FINISH_PRE_EVENT,
    EVENT_CHECK_CLUSTER,
    EVENT_LEAPING_FLAMES,
    EVENT_LEAPING_FLAMES_AURA,
    EVENT_FLAME_SCYTHE,
};

enum Actions
{
    ACTION_TALK_INTRO = 1,
};

enum Phases
{
    PHASE_INTRO = 1,
    PHASE_COMBAT,
};

Position const HomePos = {523.4965f, -61.98785f, 83.94701f, 3.141593f};

class boss_majordomo_staghelm : public CreatureScript
{
public:
    boss_majordomo_staghelm() : CreatureScript("boss_majordomo_staghelm") { }

    struct boss_majordomo_staghelmAI : public BossAI
    {
        boss_majordomo_staghelmAI(Creature* creature) : BossAI(creature, DATA_MAJORDOMO_STANGHELM)
        {
            isInCatForm = false;
            isInScorpionForm = false;
            isInNightElfForm = false;
            preEventDone = false;
            leaped = false;
            deadDruidCounter = 0;
            clusterCounter = 0;
            transformCounter = 0;
        }

        bool isInCatForm;
        bool isInScorpionForm;
        bool isInNightElfForm;
        bool preEventDone;
        bool leaped;
        uint8 deadDruidCounter;
        uint8 clusterCounter;
        uint8 transformCounter;

        void Reset()
        {
            _Reset();
            DoCast(me, SPELL_ZERO_ENERGY);
            events.SetPhase(PHASE_INTRO);
            events.ScheduleEvent(EVENT_CHECK_PLAYER_INTRO, 100, 0 , PHASE_INTRO);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.SetPhase(PHASE_COMBAT);
            events.ScheduleEvent(EVENT_CHECK_CLUSTER, 3000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveDynObjectInDistance(SPELL_LEAPING_FLAMES_AURA, 500.0f);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            DoCast(me, SPELL_ZERO_ENERGY);
            isInCatForm = false;
            isInScorpionForm = false;
            isInNightElfForm = false;
            leaped = false;
            clusterCounter = 0;
            transformCounter = 0;
        }

        void JustReachedHome()
        {
            DoCast(me, SPELL_ZERO_ENERGY);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->RemoveDynObjectInDistance(SPELL_LEAPING_FLAMES_AURA, 500.0f);
        }

        void KilledUnit(Unit* /*target*/)
        {
            Talk(SAY_SLAY);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TALK_INTRO:
                    me->setActive(true);
                    events.ScheduleEvent(EVENT_TALK_INTRO_1, 5000, 0, PHASE_INTRO);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_CLUMP_CHECK && target->GetTypeId() == TYPEID_PLAYER && transformCounter < 3)
            {
                clusterCounter++;
                if (!Is25ManRaid() && clusterCounter > 6 && !isInScorpionForm)
                {
                    isInCatForm = false;
                    isInScorpionForm = true;
                    DoCastAOE(SPELL_SCORPION_FORM);
                    DoCastAOE(SPELL_FURY);
                    me->RemoveAurasDueToSpell(SPELL_ADRENALINE);
                    me->SetMaxPower(POWER_ENERGY, 100);
                    me->SetPower(POWER_ENERGY, 0);
                    Talk(SAY_TRANSFORM);
                    Talk(SAY_ANNOUNCE_SCORPION);
                    events.CancelEvent(EVENT_LEAPING_FLAMES);
                    events.ScheduleEvent(EVENT_FLAME_SCYTHE, 1000);
                    transformCounter++;
                }
                else if (Is25ManRaid() && clusterCounter > 17 && !isInScorpionForm && transformCounter < 3)
                {
                    isInCatForm = false;
                    isInScorpionForm = true;
                    DoCastAOE(SPELL_SCORPION_FORM);
                    DoCastAOE(SPELL_FURY);
                    me->RemoveAurasDueToSpell(SPELL_ADRENALINE);
                    me->SetMaxPower(POWER_ENERGY, 100);
                    me->SetPower(POWER_ENERGY, 0);
                    Talk(SAY_TRANSFORM);
                    Talk(SAY_ANNOUNCE_SCORPION);
                    events.CancelEvent(EVENT_LEAPING_FLAMES);
                    events.ScheduleEvent(EVENT_FLAME_SCYTHE, 1000);
                    transformCounter++;
                }
                else if (!isInCatForm && transformCounter < 3)
                {
                    isInCatForm = true;
                    isInScorpionForm = false;
                    DoCastAOE(SPELL_CAT_FORM);
                    DoCastAOE(SPELL_FURY);
                    me->RemoveAurasDueToSpell(SPELL_ADRENALINE);
                    me->SetMaxPower(POWER_ENERGY, 100);
                    me->SetPower(POWER_ENERGY, 0);
                    Talk(SAY_TRANSFORM);
                    Talk(SAY_ANNOUNCE_CAT);
                    events.CancelEvent(EVENT_FLAME_SCYTHE);
                    events.ScheduleEvent(EVENT_LEAPING_FLAMES, 1000);
                    transformCounter++;
                }
                else if (!isInNightElfForm && transformCounter > 2)
                {
                    isInCatForm = false;
                    isInScorpionForm = false;
                    isInNightElfForm = true;
                    me->RemoveAurasDueToSpell(SPELL_SCORPION_FORM);
                    me->RemoveAurasDueToSpell(SPELL_CAT_FORM);
                }
            }
            else if (spell->Id == SPELL_LEAPING_FLAMES_DUMMY && !leaped)
            {
                leaped = true;
                DoCast(target, SPELL_LEAPING_FLAMES_SUMMON);
                DoCast(target, SPELL_LEAPING_FLAMES);
                DoCast(target, SPELL_LEAPING_FLAMES_AURA);
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
                    case EVENT_CHECK_PLAYER_INTRO:
                        {
                            events.ScheduleEvent(EVENT_CHECK_PLAYER_INTRO, 1000, 0 , PHASE_INTRO);

                            if (!preEventDone)
                            {
                                if (deadDruidCounter < 3) // Prevent multiple counter for a single dead druid
                                    deadDruidCounter = 0;

                                std::list<Creature*> units;
                                GetCreatureListWithEntryInGrid(units, me, NPC_DRUID_OF_THE_FLAME, 300.0f);
                                for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                {
                                    if ((*itr)->isDead())
                                    {
                                        deadDruidCounter++;
                                        if (deadDruidCounter == 3)
                                        {
                                            events.ScheduleEvent(EVENT_FINISH_PRE_EVENT, 3000);
                                            preEventDone = true;
                                        }
                                    }
                                }
                            }
                            else
                                events.CancelEvent(EVENT_CHECK_PLAYER_INTRO);
                            break;
                        }
                    case EVENT_TALK_INTRO_1:
                        TalkToMap(SAY_INTRO_1);
                        events.ScheduleEvent(EVENT_TALK_INTRO_2, 11000);
                        break;
                    case EVENT_TALK_INTRO_2:
                        TalkToMap(SAY_INTRO_2);
                        events.ScheduleEvent(EVENT_TALK_INTRO_3, 10600);
                        break;
                    case EVENT_TALK_INTRO_3:
                        TalkToMap(SAY_INTRO_3);
                        break;
                    case EVENT_FINISH_PRE_EVENT:
                        Talk(SAY_READY);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);   
                        me->GetMotionMaster()->MovePoint(0, 523.4965f, -61.98785f, 83.94701f, true);
                        me->SetHomePosition(HomePos);
                        break;
                    case EVENT_CHECK_CLUSTER:
                        clusterCounter = 0;
                        DoCastAOE(SPELL_CLUMP_CHECK);
                        events.ScheduleEvent(EVENT_CHECK_CLUSTER, urand(700, 800));
                        break;
                    case EVENT_LEAPING_FLAMES:
                        leaped = false;
                        if (me->GetPower(POWER_ENERGY) == 100)
                            DoCastAOE(SPELL_LEAPING_FLAMES_DUMMY);
                        events.ScheduleEvent(EVENT_LEAPING_FLAMES, 1000);
                        break;
                    case EVENT_FLAME_SCYTHE:
                        if (me->GetPower(POWER_ENERGY) == 100)
                            DoCastVictim(SPELL_FLAME_SCYTHE);
                        events.ScheduleEvent(EVENT_FLAME_SCYTHE, 1000);
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
        return new boss_majordomo_staghelmAI(creature);
    }
};

void AddSC_boss_majordomo_staghelm()
{
    new boss_majordomo_staghelm();
}
