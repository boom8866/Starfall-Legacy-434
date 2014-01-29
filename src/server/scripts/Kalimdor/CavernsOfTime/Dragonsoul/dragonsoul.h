
#ifndef DEF_DRAGONSOUL_H
#define DEF_DRAGONSOUL_H

#define MAX_ENCOUNTER 8

enum Datas
{
    DATA_MORCHOK                = 1,
    DATA_ZONOZZ                 = 2,
    DATA_YORSAHJ                = 3,
    DATA_HAGARA                 = 4,
    DATA_ULTRAXION              = 5,
    DATA_WARMASTER_BLACKHORN    = 6,
    DATA_DEATHWINGS_BACK        = 7,
    DATA_MADNESS_OF_DEATHWING   = 8,
};

enum CreatureIds
{
    // Bosses
    BOSS_MORCHOK                    = 55264,
    BOSS_ULTRAXION                  = 55294,
    BOSS_MADNESS_OF_DEATHWING       = 56173,
    BOSS_MADNESS_OF_DEATHWING_HP    = 57962,

    // Morchok
    NPC_SIEGE_TARGET                = 56126,
    NPC_RESONATING_CRYSTAL          = 55346,

    // Ultraxion Part
    NPC_YSERA_ULTRAXION             = 56630,
    NPC_THE_DRAGONSOUL_1            = 56668,

    // Madness of Deathwing
    NPC_ARM_TENTACLE_1              = 56167,
    NPC_ARM_TENTACLE_2              = 56846,
    NPC_WING_TENTACLE               = 56168,
    NPC_TAIL_TENTACLE               = 56844,
    NPC_THRALL_MADNESS              = 56103,
    NPC_TAIL_TENTACLE_TARGET        = 56519,
    NPC_MUTATED_CORRUPTION          = 56471,
    NPC_CRUSH_TARGET                = 56581,
    NPC_PLATFORM_DUMMY              = 56307,

    NPC_KALECGOS_MADNESS            = 56101,
    NPC_YSERA_MADNESS               = 56100,
    NPC_NOZDORMU_MADNESS            = 56102,
    NPC_ALEXTRASZA_MADNESS          = 56099,
};

#endif