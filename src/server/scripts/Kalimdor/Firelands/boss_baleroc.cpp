
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
    SAY_SLAY                        = 1,
    SAY_BLAZE                       = 2,
    SAY_ANNOUNCE_DECIMATION_BLADE   = 3,
    SAY_ANNOUNCE_INFERNO_BLADE      = 4,
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

void AddSC_boss_baleroc()
{
}
