
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
    SAY_AGGRO                       = 0,
    SAY_SHARD                       = 1,
    SAY_INFERNO_BLADE               = 2,
    SAY_DECIMATION_BLADE            = 3,
    SAY_ANNOUNCE_DECIMATION_BLADE   = 4,
    SAY_ANNOUNCE_INFERNO_BLADE      = 5,
    SAY_SLAY                        = 6,
    SAY_DEATH                       = 7,
    SAY_BERSERK                     = 8,
};

enum Spells
{
    SPELL_INCENDIARY_SOUL               = 99369,
    SPELL_BLAZE_OF_GLORY                = 99252,

    SPELL_DECIMATION_BLADE              = 99352,
    SPELL_DECIMATION_BLADE_TRIGGERED    = 99353,

    SPELL_INFERNO_BLADE                 = 99350,
    SPELL_INFERNO_BLADE_TRIGGERED       = 99351,
};

enum Events
{
};

class boss_baleroc : public CreatureScript
{
public:
    boss_baleroc() : CreatureScript("boss_baleroc") { }

    struct boss_balerocAI : public BossAI
    {
        boss_balerocAI(Creature* creature) : BossAI(creature, DATA_BALEROC)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*victim*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
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

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_balerocAI(creature);
    }
};

void AddSC_boss_baleroc()
{
    new boss_baleroc();
}
