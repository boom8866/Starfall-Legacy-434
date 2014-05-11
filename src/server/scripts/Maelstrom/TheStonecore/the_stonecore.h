#ifndef DEF_THE_STONECORE_H
#define DEF_THE_STONECORE_H

enum Data
{
    DATA_CORBORUS = 1,
    DATA_SLABHIDE,
    DATA_OZRUK,
    DATA_HIGH_PRIESTESS_AZIL,

    ENCOUNTER_COUNT,

    DATA_CORBORUS_PRE_EVENT,
    DATA_SLABHIDE_PRE_EVENT,
};

enum CreatureIds
{
    // Bosses
    BOSS_CORBORUS                   = 43438,
    BOSS_SLABHIDE                   = 43214,
    BOSS_OZRUK                      = 42188,
    BOSS_HIGH_PRIESTESS_AZIL        = 42333,

    // Corborus
    NPC_TRASHING_CHARGE             = 43743,
    NPC_ROCK_BORER                  = 43917,
    NPC_CRYSTAL_SHARD               = 49267,
    NPC_CRYSTAL_SHARD_PRE_EVENT     = 49473,

    // Slabhide
    NPC_STALACTIT_TRIGGER           = 43357,
    NPC_STALACTIT_TRIGGER_BOSS      = 43159,
    NPC_LAVA_FISSURE                = 43242,

    // Ozruk

    // High Priestess Azil


    // Trash mobs
    NPC_STONECORE_BERSERKER         = 43430,
    NPC_STONECORE_EARTHSHAPER       = 43537,
    NPC_STONECORE_WARBRINGER        = 42696,

    NPC_CRYSTALSPAWN_GIANT          = 42810,
    NPC_IMP                         = 43014,
    NPC_MILLHOUSE_MANASTORM         = 43391,
    NPC_STONECORE_BRUISER           = 42692,
    NPC_STONECORE_FLAYER            = 42808,
    NPC_MAGMALORD                   = 42789,
    NPC_RIFT_CONJURER               = 42691,
    NPC_STONECORE_SENTRY            = 42695,

    // Various NPCs
    NPC_EARTHWARDEN_YRSA            = 50048,
    NPC_STONECORE_TELEPORTER1       = 51396,
    NPC_STONECORE_TELEPORTER2       = 51397,
};

enum GameObjectIds
{
    GO_ROCKDOOR                     = 207343,
    GO_STALAKTIT                    = 204337,
    GO_STONEWALL                    = 204381,
};

#endif
