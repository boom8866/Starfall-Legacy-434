
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#ifndef DEF_THRONE_OF_THE_FOUR_WINDS_H
#define DEF_THRONE_OF_THE_FOUR_WINDS_H

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "MapManager.h"
#include "Player.h"
#include "CreatureTextMgr.h"

// Config
// Max radius
#define PLATFORM_RADIUS 75.f
// Max Orientation difference between the player and the winddraft (idiot test)
#define WINDDRAFT_DIFF_O 0.11f

enum Data
{
    DATA_CONCLAVE_OF_WIND = 1,
    DATA_ALAKIR,
    ENCOUNTER_COUNT,

    DATA_IS_ULTIMATE_IN_PROGRESS,
    DATA_PLAYER_HIT_BY_HURRICANE,
    DATA_HURRICANE_ENDED,
    DATA_CONCLAVE_MEMBER_FALLEN,
    DATA_IS_CONCLAVE_IN_BERSERK,
    DATA_PLAYER_UNDER_MAP,
    DATA_WIND_BLAST_TICK,
};

enum Types
{
    TYPE_ANSHAL = 1,
    TYPE_NEZIR,
    TYPE_ROHASH,
    CONCLAVE_MEMBERS
};

enum CreatureIds
{
    BOSS_ANSHAL                     = 45870,
    BOSS_NEZIR                      = 45871,
    BOSS_ROHASH                     = 45872,

    BOSS_ALAKIR                     = 46753,

    // Conclave of Wind
    NPC_WESTWIND                    = 47925,
    NPC_NORTHWIND                   = 47926,
    NPC_EASTWIND                    = 47924,
    // *- Anshal
    NPC_SOOTHING_BREEZE             = 46246,
    NPC_RAVENOUS_CREEPER            = 45812,
    NPC_RAVENOUS_CREEPER_TRIGGER    = 45813,
    // *- Nezir
    NPC_ICE_PATCH                   = 46186,
    // *- Rohash
    NPC_HURRICANE                   = 46207,
    NPC_HURRICANE_STALKER           = 46419,

    // Al'Akir
    NPC_SLIPSTREAM                  = 47066,

    NPC_SQUALL_LINE_VEHICLE_SW      = 47034,

    NPC_SQUALL_LINE_SW              = 48854, // spawned 8 times
    NPC_SQUALL_LINE_SE              = 48855, // spawned 16 times ??


    NPC_ICE_STORM                   = 46734,
    NPC_ICE_STORM_GROUND            = 46973,
    NPC_ICE_STORM_TRIGGER           = 46766,
};

uint32 const ConclaveMembers[CONCLAVE_MEMBERS] =
{
    BOSS_ANSHAL,
    BOSS_NEZIR,
    BOSS_ROHASH
};

uint32 const ConclaveTriggers[CONCLAVE_MEMBERS] =
{
    NPC_WESTWIND,
    NPC_NORTHWIND,
    NPC_EASTWIND
};

enum GameobjectIds
{
    GOB_WIND_DRAFTEFFECT_CENTER     = 207922,
    GOB_RAIDPLATFORM                = 207737,

    GOB_WIND_DRAFTEFFECT_1          = 207923,
    GOB_WIND_DRAFTEFFECT_2          = 207924,
    GOB_WIND_DRAFTEFFECT_3          = 207925,
    GOB_WIND_DRAFTEFFECT_4          = 207926,
    GOB_WIND_DRAFTEFFECT_5          = 207929,
    GOB_WIND_DRAFTEFFECT_6          = 207930,
    GOB_WIND_DRAFTEFFECT_7          = 207927,
    GOB_WIND_DRAFTEFFECT_8          = 207928,

    GOB_DEIJING_HEALING             = 206699,
    GOB_DEIJING_FROST               = 206700,
    GOB_DEIJING_TORNADO             = 206701
};

uint32 const UltimateGameobjects[CONCLAVE_MEMBERS] =
{
    GOB_DEIJING_HEALING,
    GOB_DEIJING_FROST,
    GOB_DEIJING_TORNADO
};

struct WindDraftData
{
    uint32 entry;
    uint32 areatrigger;
    uint32 targetWindDraft;
};

WindDraftData const windDrafts[8] =
{
    {GOB_WIND_DRAFTEFFECT_1, 6290, GOB_WIND_DRAFTEFFECT_6},
    {GOB_WIND_DRAFTEFFECT_2, 6274, GOB_WIND_DRAFTEFFECT_3},
    {GOB_WIND_DRAFTEFFECT_3, 6275, GOB_WIND_DRAFTEFFECT_2},
    {GOB_WIND_DRAFTEFFECT_4, 6276, GOB_WIND_DRAFTEFFECT_7},
    {GOB_WIND_DRAFTEFFECT_5, 6279, GOB_WIND_DRAFTEFFECT_8},
    {GOB_WIND_DRAFTEFFECT_6, 6280, GOB_WIND_DRAFTEFFECT_1},
    {GOB_WIND_DRAFTEFFECT_7, 6277, GOB_WIND_DRAFTEFFECT_4},
    {GOB_WIND_DRAFTEFFECT_8, 6278, GOB_WIND_DRAFTEFFECT_5}
};

enum InstanceSpells
{
    // Pre Combat Effects
    SPELL_PRE_COMBAT_EFFECT_ANSHAL  = 85537,
    SPELL_PRE_COMBAT_EFFECT_NEZIR   = 85532,
    SPELL_PRE_COMBAT_EFFECT_ROHASH  = 85538,

    // Other
    SPELL_TELEPORT_VISUAL           = 83369,

    // Debuffs
    SPELL_WIND_DISTANCE_CHECKER     = 85763,

    SPELL_WITHERING_WINDS           = 89137,
    SPELL_WITHERING_WINDS_EFFECT    = 85576,
    SPELL_WITHERING_WINDS_DAMAGE    = 93168,

    SPELL_CHILLING_WINDS            = 89135,
    SPELL_CHILLING_WINDS_EFFECT     = 85578,
    SPELL_CHILLING_WINDS_DAMAGE     = 93163,

    SPELL_DEAFING_WINDS             = 89136,
    SPELL_DEAFING_WINDS_EFFECT      = 85573,
    SPELL_DEAFING_WINDS_DAMAGE      = 93166,

    // Ultimates
    SPELL_ZEPHYR_ULTIMATE           = 84638,
    SPELL_SLEET_STORM_ULTIMATE      = 84644,
    SPELL_HURRICANE_ULTIMATE        = 84643,

    SPELL_WINDDRAFT                 = 84576,
    SPELL_JETSTREAM_PREVENT         = 89771,
    SPELL_BERSERK                   = 82395,
    SPELL_SLIPSTREAM                = 87740,
    SPELL_SLIPSTREAM_VISUAL         = 85063,

    SPELL_WIND_PRE_EFFECT_WARNING   = 96508,

    // Achievements
    SPELL_ACHIEVEMENT_CONCLAVE      = 88835,
};

uint32 const SpellPreCombat[3]      = { SPELL_PRE_COMBAT_EFFECT_ANSHAL,
                                        SPELL_PRE_COMBAT_EFFECT_NEZIR,
                                        SPELL_PRE_COMBAT_EFFECT_ROHASH };

uint32 const SpellWindDebuffs[3]    = { SPELL_WITHERING_WINDS_EFFECT,
                                        SPELL_CHILLING_WINDS_EFFECT,
                                        SPELL_DEAFING_WINDS_EFFECT };

uint32 const SpellUltimates[3]      = { SPELL_ZEPHYR_ULTIMATE,
                                        SPELL_SLEET_STORM_ULTIMATE,
                                        SPELL_HURRICANE_ULTIMATE };

enum ThroneTexts
{
    // Conclave of Wind Yells
    SAY_CONCLAVE_INTRO              = 0,
    SAY_CONCLAVE_SLAY_OR_ABILITY    = 1,
    SAY_CONCLAVE_FULL_POWER         = 2,
    SAY_CONCLAVE_LOW_HEALTH         = 3,
    SAY_CONCLAVE_PLATFORM_EMPTY     = 4,
    SAY_CONCLAVE_DEATH_WARNING      = 5,
};

enum InstanceActions
{
    ACTION_WINDDRAFT_IN_COMBAT      = 0,
    ACTION_WINDDRAFT_OUT_OF_COMBAT  = 1,
    ACTION_WINDDRAFT_ULTIMATE_BEGIN = 2,
    ACTION_WINDDRAFT_ULTIMATE_END   = 3,
    ACTION_CONCLAVE_RESSURECT       = 4,
};

Position const platformPosition[CONCLAVE_MEMBERS] =
{
    {-49.01f, 106.89f, 199.49f, 0}, // POSITION_ANSHAL_PLATFORM
    {187.70f, 813.42f, 199.49f, 0}, // POSITION_NEZIR_PLATFORM
    {-52.80f, 578.04f, 199.49f, 0}  // POSITION_ROHASH_PLATFORM
};

inline uint8 GetConclaveTypeByEntry(uint32 entry)
{
    switch (entry)
    {
        case BOSS_ANSHAL:
        case NPC_WESTWIND:
            return TYPE_ANSHAL;
        case BOSS_NEZIR:
        case NPC_NORTHWIND:
            return TYPE_NEZIR;
        case BOSS_ROHASH:
        case NPC_EASTWIND:
            return TYPE_ROHASH;
        default:
            return 0;
    }
}

#endif
