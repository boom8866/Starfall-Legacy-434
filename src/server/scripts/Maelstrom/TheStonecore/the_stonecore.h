
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#ifndef DEF_THE_STONECORE_H
#define DEF_THE_STONECORE_H

enum Data
{
    DATA_CORBORUS,
    DATA_SLABHIDE,
    DATA_OZRUK,
    DATA_HIGH_PRIESTESS_AZIL,
    ENCOUNTER_COUNT,
    DATA_CORBORUS_PRE_EVENT
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

    // Slabhide
    NPC_STALAKTIT_TRIGGER           = 43357,
    NPC_STALAKTIT_TRIGGER_BOSS      = 43159,
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

uint32 const CorborusEventNpcs[3] = {NPC_STONECORE_BERSERKER, NPC_STONECORE_EARTHSHAPER, NPC_STONECORE_WARBRINGER};

enum GameObjectIds
{
    GO_BROKEN_ROCKDOOR              = 207343,
    GO_STALAKTIT                    = 204337,
    GO_STONEWALL                    = 204381,
};

enum Action
{
    ACTION_CORBORUS_DO_INTRO,
    ACTION_CORBORUS_LEAVE_SUBMERGE,
};

#endif
