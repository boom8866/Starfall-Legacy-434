
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#ifndef DEF_THRONEOFTHETIDES_H
#define DEF_THRONEOFTHETIDES_H

enum Data
{
    DATA_LADY_NAZJAR,
    DATA_COMMANDER_ULTHOK,
    DATA_MINDEBENDER_GHURSHA,
    DATA_OZUMAT,
    ENCOUNTER_COUNT,
    DATA_EVENT_DONE_LOWER_SPAWN,    // done (bool)
    DATA_EVENT_DONE_NAZJAR_PRE,     // done (bool)
    DATA_EVENT_DONE_SHOCK_DEFENSE,  // done (bool)
};

enum Npcs
{
    // Bosses
    BOSS_LADY_NAZJAR                = 40586,
    BOSS_COMMANDER_ULTHOK           = 40765,
    BOSS_MINDBENDER_GHURSHA         = 40788,
    BOSS_OZUMAT                     = 44566,

    // Lady Naz'jar
    NPC_SUMMONED_WITCH              = 40634,
    NPC_SUMMONED_GUARD              = 40633,
    NPC_SUMMONED_WATERSPOUT         = 48571,
    NPC_SUMMONED_WATERSPOUT_HC      = 49108,
    NPC_SUMMONED_GEYSER             = 40597,
    NPC_NAZJAR_COMBAT_TRIGGER       = 48983,

    // Commander Ulthok
    NPC_DARK_FISSURE                = 40784,

    // Erunak Stonespeaker & Mindbender Ghur'sha
    NPC_ERUNAK_STONESPEAKER         = 40825,
    NPC_EARTH_SHARD                 = 45469,
    NPC_MIND_FOG                    = 40861,

    // Ozumat
    NPC_NEPTULON                    = 40792,
    NPC_DEEP_MURLOC_INVADER         = 44658,
    NPC_VICIOUS_MINDLASHER          = 44715,
    NPC_UNYIELDING_BEHEMOTH         = 44648,
    NPC_FACELESS_SAPPER             = 44752,
    NPC_BLIGHT_BEAST                = 44841,
    NPC_BLIGHT_OF_OZUMAT            = 44801,
    NPC_OZUMAT_VISUAL_TRIGGER       = 44809,

    // Permanent Spawning
    NPC_NAZJAR_SOLDIER              = 45672,
    NPC_ELEMENTAL_GUARD             = 45621,

    // Events
    NPC_NAZJAR_EVENT_DOUBLE         = 39959,
    NPC_SHOCK_DEFENSE_TRIGGER       = 36171,
    NPC_WORLD_TRIGGER               = 22515,

    // Other
    NPC_TELEPORTER_UPPER            = 51395,
    NPC_TELEPORTER_LOWER            = 51391,
};

enum Gameobjects
{
    GO_COMMANDER_ULTHOK_DOOR        = 204338,
    GO_CORALES                      = 205542,
    GO_LADY_NAZJAR_DOOR             = 204339,
    GO_MINDEBENDER_GHURSA_DOOR      = 204340,
    GO_OZUMAT_DOOR                  = 204341,
    GO_NEPTULONS_CACHE_NH           = 205216,
    GO_NEPTULONS_CACHE_HC           = 207973,
    GO_TENTACLE_RIGHT               = 208302,
    GO_TENTACLE_LEFT                = 208301,
    GO_INVISIBLE_DOOR_L             = 207998,
    GO_INVISIBLE_DOOR_R             = 207997,
    GO_CONTROL_SYSTEM               = 203199,
    GO_TEMP_SUMMON_ROCKS            = 202742,
};

enum Achievements
{
    ACHIEVEMENT_OLD_FAITHFUL        = 5285,
};

enum InstanceSpells
{
    SPELL_LADY_NAZJAR_COMBAT_VISUAL = 91349,
    SPELL_ULTHOK_INTRO              = 82960,
    SPELL_SUMMON_FALLING_ROCKS      = 74465,
    SPELL_TENTACLE_KNOCKBACK        = 84566,
    SPELL_WATER_WINDOW_JUMP_VISUAL  = 74048,
    SPELL_SHOCK_DEFENSE_SMALL       = 86635,
    SPELL_SHOCK_DEFENSE_BIG         = 85170,
    SPELL_SHOCK_DEFENSE_UNK1        = 86611,
    SPELL_SHOCK_DEFENSE_UNK2        = 86613,
    SPELL_SHOCK_DEFENSE_UNK3        = 86614,
    SPELL_SHOCK_DEFENSE_OZUMAT_UNK1 = 94490,
    SPELL_SHOCK_DEFENSE_OZUMAT_UNK2 = 96042,
    SPELL_TELEPORTER_ACTIVE         = 95296,
    SPELL_TELEPORT_TO_LOW           = 95284,
    SPELL_TELEPORT_TO_UPPER         = 95285,
};

enum InstanceActions
{
    INST_ACTION_START_ULTHOK_EVENT,
    INST_ACTION_START_OZUMAT_EVENT,
    INST_ACTION_OZUMAT_START_PHASE,
    INST_ACTION_OZUMAT_RESET_EVENT,
    INST_ACTION_NEPTULON_DO_INTRO,
};

#endif
