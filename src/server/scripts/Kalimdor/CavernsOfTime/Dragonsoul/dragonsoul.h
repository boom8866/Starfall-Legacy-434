
#ifndef DEF_DRAGONSOUL_H
#define DEF_DRAGONSOUL_H

#define MAX_ENCOUNTER 8

enum Datas
{
    DATA_MORCHOK = 1,
    DATA_ZONOZZ,
    DATA_YORSAHJ,
    DATA_HAGARA,
    DATA_ULTRAXION,
    DATA_WARMASTER_BLACKHORN,
    DATA_DEATHWINGS_BACK,
    DATA_MADNESS_OF_DEATHWING,

    DATA_KALECGOS_MADNESS,
    DATA_ALEXSTRASZA_MADNESS,
    DATA_YSERA_MADNESS,
    DATA_NOZDORMU_MADNESS,
    DATA_THRALL_MADNESS,

    DATA_LORD_AFRASASTRASZ,
};

enum CreatureIds
{
    // Generic Events
    NPC_SIEGE_BREAKER_DUMMY         = 57261,
    NPC_LORD_AFRASASTRASZ           = 55476,
    NPC_IMAGE_OF_TYRYGOSA           = 57684,
    NPC_ANCIENT_WATER_LORD          = 57160,
    NPC_EARTHEN_DESTROYER           = 57158,

    // Bosses
    BOSS_MORCHOK                    = 55265,
    BOSS_ULTRAXION                  = 55294,

    BOSS_MADNESS_OF_DEATHWING       = 56173,
    BOSS_MADNESS_OF_DEATHWING_HP    = 57962,

    // Morchok
    NPC_SIEGE_TARGET                = 56126,
    NPC_RESONATING_CRYSTAL          = 55346,
    NPC_EARTHEN_VORTEX_VEHICLE      = 55723,

    // Ultraxion Part
    NPC_YSERA_ULTRAXION             = 56630,
    NPC_THE_DRAGONSOUL_1            = 56668,

    // Madness of Deathwing
    NPC_ARM_TENTACLE_1              = 56167,
    NPC_ARM_TENTACLE_2              = 56846,
    NPC_WING_TENTACLE               = 56168,
    NPC_TAIL_TENTACLE               = 56844,
    NPC_TAIL_TENTACLE_TARGET        = 56519,
    NPC_MUTATED_CORRUPTION          = 56471,
    NPC_CRUSH_TARGET                = 56581,
    NPC_PLATFORM_STALKER            = 56307,
    NPC_ELEMENTIUM_BOLT             = 56262,
    NPC_JUMP_PAD                    = 56699,
    NPC_COSMETIC_TENTACLE           = 57693,

    NPC_THRALL_MADNESS              = 56103,
    NPC_KALECGOS_MADNESS            = 56101,
    NPC_YSERA_MADNESS               = 56100,
    NPC_NOZDORMU_MADNESS            = 56102,
    NPC_ALEXSTRASZA_MADNESS         = 56099,
};

#endif