
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

enum Texts
{
};

enum Spells
{
    SPELL_ENERGIZE      = 99191,
    SPELL_RIDE_VEHICLE  = 99372,
};

enum Events
{
};

enum AnimKits
{
};

class boss_bethilac : public CreatureScript
{
public:
    boss_bethilac() : CreatureScript("boss_bethilac") { }

    struct boss_bethilacAI : public BossAI
    {
        boss_bethilacAI(Creature* creature) : BossAI(creature, DATA_BETHILAC)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->AddAura(SPELL_ENERGIZE, me);
        }

        void Reset()
        {
            _Reset();
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            _DespawnAtEvade();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bethilacAI(creature);
    }
};

void AddSC_boss_bethilac()
{
    new boss_bethilac();
}