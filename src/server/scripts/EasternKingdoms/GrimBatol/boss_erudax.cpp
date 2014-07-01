#include "ScriptPCH.h"
#include "grim_batol.h"

enum Spells
{
};

enum Texts
{
    SAY_AGGRO                           = 0,
    SAY_ANNOUNCE_SHADOW_GALE            = 1,
    SAY_SHADOW_GALE                     = 2,
    SAY_FACELESS_CORRUPTORS             = 3,
    SAY_ANNOUNCE_GUARDIANS              = 4,
    SAY_ANNOUNCE_SHIELD_OF_NIGHTMARES   = 5,
    SAY_SLAY                            = 6,
    SAY_DEATH                           = 7,
};

enum Events
{
};

enum Points
{
    POINT_FACELESS_IS_AT_AN_EGG = 1,
    POINT_ERUDAX_USE_SHADOW_GALE,
};

class boss_erudax: public CreatureScript
{
public:
    boss_erudax() : CreatureScript("boss_erudax") { }

    struct boss_erudaxAI : public BossAI
    {
        boss_erudaxAI(Creature* creature) : BossAI(creature, DATA_ERUDAX)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            events.Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
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
                    case 0:
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
        return new boss_erudaxAI(creature);
    }
};

void AddSC_boss_erudax()
{
    new boss_erudax();
}
