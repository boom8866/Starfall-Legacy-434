
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#ifndef DEF_BLACKWING_DESCENT_H
#define DEF_BLACKWING_DESCENT_H

enum Data
{
    DATA_MAGMAW = 1,
    DATA_OMNOTRON_DEFENSE_SYSTEM,
    DATA_MALORIAK,
    DATA_CHIMAERON,
    DATA_ATRAMEDES,
    DATA_NEFARIAN,
    ENCOUNTER_COUNT,
    DATA_PHASE_MAGMAW_MASSIVE_CRASH,
    DATA_PHASE_NEFARIAN_ACTIVE,
    DATA_ACTIVATE_TRON,
    DATA_IS_FIRST_TRON,
    DATA_TRON_ID,
    DATA_NEFARIAN_HC_FOR_BOSS,
    DATA_SONAR_PULSE_COUNT
};

enum Creatures
{
    BOSS_MAGMAW                     = 41570,
    BOSS_OMNOTRON                   = 42186,
    BOSS_MALORIAK                   = 41378,
    BOSS_ATRAMEDES                  = 41442,
    BOSS_CHIMAERON                  = 43296,
    BOSS_NEFARIAN                   = 41376,

    // Magmaw
    NPC_PILLAR_OF_FLAME             = 41843,
    NPC_LAVA_PARASITE               = 41806,
    NPC_LAVA_PARASITE_HOSTED        = 42321,
    NPC_EXPOSED_HEAD_OF_MAGMAW      = 42347,
    NPC_EXPOSED_HEAD_OF_MAGMAW_2    = 48270,
    NPC_MASSIVE_CRASH               = 47330,
    NPC_ROOM_STALKER                = 47196,

    //NPC_MAGMAWS_HEAD               = 42347,
    NPC_NEFARIAN_STALKER            = 49427,
    NPC_IGNITION_TRIGGER            = 49447,
    NPC_LAVA_PARASITE_SUMMONED      = 42321,
    NPC_SPIKE_STALKER               = 41767,
    NPC_BLAZING_BONE_CONSTRUCT      = 49416,
    NPC_PINCER_L                    = 41620,
    NPC_PINCER_R                    = 41789,
    NPC_DRAGONID_DRUDGE             = 42362,

    // Omnotron Defense System
    NPC_NEFRIAN_OMNOTRON_HC         = 49226,
    //+- Toxitron
    NPC_TOXITRON                    = 42180,
    //+- Poison Bomb
    NPC_POISON_BOMB                 = 42897,
    NPC_POISON_CLOUD                = 42934,
    NPC_POISON_PUDDLE               = 42920,
    //+- Arcanotron
    NPC_ARCANOTRON                  = 42166,
    NPC_POWER_GENERATOR             = 42733,
    //+- Electron
    NPC_ELECTRON                    = 42179,
    //+- Magmatron
    NPC_MAGMATRON                   = 42178,

    // Chimaeron
    NPC_BILE_O_TRON                 = 44418,
    NPC_FINKLE_EINHORN              = 44202,
    NPC_NEFARIAN_CHIMAERON          = 48964,

    // Maloriak
    NPC_ABBERATON                   = 41440,
    NPC_PRIME_SUBJECT               = 41841,
    NPC_CAULDRON_TRIGGER            = 41505,
    NPC_FLASH_FREEZE                = 41576,
    NPC_MAGMA_JET                   = 41901,
    NPC_MAGMA_JET_CONTROLLER        = 50030,
    NPC_ABSOLUTE_ZERO               = 41961,
    NPC_VILE_SWILL                  = 49811,
    NPC_NEFRIAN_MALORIAK_HC         = 49799,

    // Atramedes
    //+- Pre Event
    NPC_PRE_MALORIAK                = 43404,
    NPC_PRE_NEFARIAN                = 43396,
    NPC_PRE_ATRAMEDES               = 43407,
    NPC_MEMORY_FOG                  = 43400,
    NPC_NEFARIUS_THORNE             = 43401,
    //+- Mainfight
    NPC_SONAR_PULSE                 = 49623,
    NPC_ROARING_FLAMES              = 41807,
    NPC_DWARFEN_SHIELD              = 42960,
    NPC_REVERBRATING_FLAME_TRIGGER  = 41962,
    NPC_REVERBRATING_FLAME_DAMAGE   = 42001,
    NPC_NEFRIAN_ATRAMEDES_HC        = 49580,

    // Nefarian
    NPC_ONYXIA                      = 41270,

    // Misc
    NPC_LORD_VICTOR_NEFARIAN        = 41379,
};

enum Gameobjects
{
    GOB_DOOR_PRE_BOSSES             = 205830,
    GOB_ONYXIA_PLATFORM             = 207834,
    GOB_MALORIAKS_CAULDRON          = 203306,
    GOB_INKUBATOR                   = 206704,
    GOB_BIG_INKUBATOR               = 206705,
};

enum Map_id
{
    MAPID_BLACKWING_DESCENT         = 669,
};

#endif
