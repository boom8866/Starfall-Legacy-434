
#ifndef DEF_BASTION_OF_TWILIGHT_H
#define DEF_BASTION_OF_TWILIGHT_H

#define BOTScriptName "instance_bastion_of_twilight"
#define MAX_ENCOUNTER 5

enum DataTypes
{
    // Encounters
    DATA_HALFUS                     = 1,
    DATA_THERALION_AND_VALIONA      = 2,
    DATA_ASCENDANT_COUNCIL          = 3,
    DATA_CHOGALL                    = 4,
    DATA_SINESTRA                   = 5,

    // NPC GUIDs
    DATA_AC_PHASE                   = 6,
    DATA_FELUDIUS                   = 7,
    DATA_IGNACIOUS                  = 8,
    DATA_ARION                      = 9,
    DATA_TERRASTRA                  = 10,
    DATA_ELEMENTIUM_MONSTROSITY     = 11,

    DATA_PROTO_BEHEMOTH             = 12,
    DATA_NETHER_SCION               = 13,
    DATA_SLATE_DRAGON               = 14,
    DATA_TIME_WARDEN                = 15,
    DATA_WHELPS                     = 16,
    DATA_STORM_RIDER                = 17,
    DATA_CAGE                       = 18,
};

enum Creatures
{
    // Bosses
    BOSS_HALFUS_WYRMBREAKER         = 44600,
    BOSS_VALIONA_BOT                = 45992,
    BOSS_THERALION_BOT              = 45993,
    BOSS_FELUDIUS                   = 43687,
    BOSS_IGNACIOUS                  = 43686,
    BOSS_ARION                      = 43688,
    BOSS_TERRASTRA                  = 43689,
    BOSS_ELEMENTIUM_MONSTROSITY     = 43735,
    BOSS_CHOGALL                    = 43324,
    BOSS_SINESTRA                   = 45213,

    // Halfus
    NPC_PROTO_BEHEMOTH              = 44687,
    NPC_SLATE_DRAGON                = 44652,
    NPC_NETHER_SCION                = 44645,
    NPC_STORM_RIDER                 = 44650,
    NPC_TIME_RIDER                  = 44797,
    NPC_ORPHANED_WHELP              = 44641,

    // Valiona and Theralion
    NPC_TWILIGHT_SENTRY             = 50008,
    NPC_DAZZ_DESTRUCTION_STALKER    = 46374,
    NPC_UNSTABLE_TWILIGHT           = 46304,
    NPC_TWILIGHT_RIFT               = 50014,
    NPC_COLLAPSING_TW_PORTAL        = 46301,
    NPC_TWILIGHT_FLAME              = 40718,

    // Ascendant Lord Council
    NPC_ASCENDANT_COUNCIL           = 45420,
    NPC_ASCENDANT_CONTROLLER        = 43691,
    NPC_WATER_BOMB                  = 44201, // Scripted.
    NPC_INFERNO_RUSH                = 47501, // Scripted on Ignacious boss script.
    NPC_CALL_WINDS                  = 44747, // Scripted.
    NPC_GRAVITY_WELL                = 44824, // Scripted.
    NPC_ERUPTION_TGT                = 44845, // Scripted on Terrastra boss script.
    NPC_FROZEN_ORB                  = 49518, // Gets a target, goes to it casting beacon on it, casts Glaciate if reaches. // Scripted.
    NPC_FLAME_STRIKE                = 49432, // Summ by boss on random target. Puts visual on self then after 5 secs comes damage spell. // Scripted.
    NPC_LIQUID_ICE                  = 45452, // Scripted.
    NPC_LAVA_SEED                   = 48538, // Scripted.
    NPC_GRAVITY_CRUSH               = 45476, // vehicle.

    NPC_CHOGALL_HALFUS              = 46965,
    NPC_CHOGALL_DRAGONS             = 48142,
    NPC_CHOGALL_COUNCIL             = 46900,
};

enum Gameobjects
{
    // Halfus Wyrmbreaker
    GO_HALFUS_ENTRANCE          = 205222,
    GO_HALFUS_ESCAPE            = 205223,
    GO_WELP_CAGE                = 205087,

    // Theralion and Valiona
    GO_TAV_ENTRANCE             = 205224,
    GO_TAV_ESCAPE               = 205225,

    // Council of Ascendents
    GO_COA_ENTRANCE             = 205226,
    GO_COA_ESCAPE               = 205227,

    // Cho'Gall
    GO_CHOGALL_ENTRANCE         = 205228,
};

#endif
