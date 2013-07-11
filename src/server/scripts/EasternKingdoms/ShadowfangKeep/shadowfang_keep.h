
#ifndef DEF_SHADOWFANG_H
#define DEF_SHADOWFANG_H

#define MAX_ENCOUNTER              5

enum Creatures
{
    // Baron Ashbury
    BOSS_BARON_ASHBURY                = 46962,
    NPC_ASHBURY_WINGS                 = 50604,

    // Baron Silverlaine
    BOSS_BARON_SILVERLAINE            = 3887,

    // Commander Springvale
    BOSS_COMMANDER_SPRINGVALE         = 4278,
    NPC_TORMENTED_OFFICER             = 50615,
    NPC_WAILING_GUARDSMAN             = 50613,

    // Lord Walden
    BOSS_LORD_WALDEN                  = 46963,

    // Lord Godfrey
    BOSS_LORD_GODFREY                 = 46964,
    NPC_BLOODTHIRSTY_GHOUL            = 50561,
};

enum GameObjectIds
{
    GO_COURTYARD_DOOR                   = 18895,
    GO_SORCERER_DOOR                    = 18972,
    GO_ARUGAL_DOOR                      = 18971,
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
};

#endif
