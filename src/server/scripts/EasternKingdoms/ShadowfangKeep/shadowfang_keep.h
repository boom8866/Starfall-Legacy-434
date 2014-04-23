
#ifndef DEF_SHADOWFANG_H
#define DEF_SHADOWFANG_H

#define MAX_ENCOUNTER 5

enum Creatures
{
    // Baron Ashbury
    BOSS_BARON_ASHBURY              = 46962,
    NPC_ASHBURY_WINGS               = 50604,

    // Baron Silverlaine
    BOSS_BARON_SILVERLAINE          = 3887,

    NPC_NANDOS_DUMMY                = 51047,
    NPC_WOLF_MASTER_NANDOS          = 50851,
    NPC_LUPINE_SPECTRE              = 50923,

    NPC_ODO_DUMMY                   = 50934,
    NPC_ODO_THE_BLINDWATCHER        = 50857,

    NPC_RAZORCLAW_DUMMY             = 51080,
    NPC_RAZORCLAW_THE_BUTCHER       = 50869,

    NPC_RETHILGORE_DUMMY            = 51085,
    NPC_RETHILGORE                  = 50834,

    // Commander Springvale
    BOSS_COMMANDER_SPRINGVALE       = 4278,
    NPC_TORMENTED_OFFICER           = 50615,
    NPC_WAILING_GUARDSMAN           = 50613,
    NPC_SHIELD_FOCUS                = 50547,
    NPC_DESECRATION_STALKER         = 50503,

    // Lord Walden
    BOSS_LORD_WALDEN                = 46963,
    NPC_MYSTERY_MIXTURE             = 50522,

    // Lord Godfrey
    BOSS_LORD_GODFREY               = 46964,
    NPC_BLOODTHIRSTY_GHOUL          = 50561,
    NPC_PISTOL_BARRAGE_DUMMY        = 52065,

    NPC_VETERAN_FORSAKEN_TROOPER    = 47030,
    NPC_COMMANDER_BELMONT           = 47293,
    NPC_FORSAKEN_BLIGHTSPREADER     = 47031,
    NPC_HIGH_WARLORD_CROMUSH        = 47294,
    NPC_DISEASE_BUNNY               = 23837,
    NPC_FORSAKEN_TROOPER            = 47865,
};

enum GameObjectIds
{
    GO_COURTYARD_DOOR   = 18895,
    GO_SORCERER_DOOR    = 18972,
    GO_ARUGAL_DOOR      = 18971,
};

enum Achievements
{
    ACHIEV_PARDON_DENIED              = 5503,
    ACHIEV_TO_THE_GROUND              = 5504,
    ACHIEV_BULLET_TIME                = 5505,
};

enum Data
{
    DATA_BARON_ASHBURY          = 1,
    DATA_BARON_SILVERLAINE      = 2,
    DATA_COMMANDER_SPRINGVALE   = 3,
    DATA_LORD_WALDEN            = 4,
    DATA_LORD_GODFREY           = 5,

    DATA_TEAM_IN_INSTANCE       = 6,
};

#endif
