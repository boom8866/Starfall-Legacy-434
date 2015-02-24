
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

    SPELL_FLAMES_ORDER          = 81171,
    SPELL_ABSORB_FIRE           = 81196,

    SPELL_CONVERSION            = 91303,

};

enum Phases
{
    PHASE_NULL   = 1,
    PHASE_NORMAL,
    PHASE_LAST
};

enum Events
{
    EVENT_BERSERK = 1,
};

enum Actions
{
    ACTION_TALK_INTRO = 1,
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
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SetBossState(DATA_CHOGALL, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_BLOOD_BAR);
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
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

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BERSERK:
                        return; 
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

void AddSC_boss_chogall()
{
    new at_chogall_intro();
    new boss_chogall();
}
