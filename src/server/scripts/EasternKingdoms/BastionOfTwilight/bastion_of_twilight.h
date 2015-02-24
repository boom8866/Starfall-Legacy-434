
#ifndef DEF_BASTION_OF_TWILIGHT_H
#define DEF_BASTION_OF_TWILIGHT_H

#define BOTScriptName "instance_bastion_of_twilight"
#define MAX_ENCOUNTER 5

enum DataTypes
{
    // Encounters
    DATA_HALFUS_WYRMBREAKER = 1,
    DATA_THERALION_AND_VALIONA,
    DATA_ASCENDANT_COUNCIL,
    DATA_CHOGALL,
    DATA_SINESTRA,

    // NPC GUIDs
    DATA_FELUDIUS,
    DATA_IGNACIOUS,
    DATA_ARION,
    DATA_TERRASTRA,
    DATA_ELEMENTIUM_MONSTROSITY,
    DATA_ASCENDANT_COUNCIL_CONTROLLER,
    DATA_PROTO_BEHEMOTH,
    DATA_NETHER_SCION,
    DATA_SLATE_DRAGON,
    DATA_TIME_WARDEN,
    DATA_WHELPS,
    DATA_STORM_RIDER,
    DATA_CAGE,
    DATA_VALIONA,
    DATA_THERALION,
    DATA_CHOGALL_HALFUS_INTRO,
    DATA_CHOGALL_TAV_INTRO,

    // Encounter Datas
    DATA_ELECTRICAL_INSTABILITY_CHARGES,

    // Instance Datas
    DATA_DRAGONS_PICKED,
};

enum Creatures
{
    // Bosses
    BOSS_HALFUS_WYRMBREAKER         = 44600,
    BOSS_VALIONA                    = 45992,
    BOSS_THERALION                  = 45993,
    BOSS_FELUDIUS                   = 43687,
    BOSS_IGNACIOUS                  = 43686,
    BOSS_ARION                      = 43688,
    BOSS_TERRASTRA                  = 43689,
    BOSS_ELEMENTIUM_MONSTROSITY     = 43735,
    BOSS_CHOGALL                    = 43324,
    BOSS_SINESTRA                   = 45213,

    // First Trash Room
    NPC_CATACLYSM_STALKER           = 42098,
    NPC_TWILIGHT_PHASE_TWISTER      = 45267,

    // Halfus
    NPC_PROTO_BEHEMOTH              = 44687,
    NPC_SLATE_DRAGON                = 44652,
    NPC_NETHER_SCION                = 44645,
    NPC_STORM_RIDER                 = 44650,
    NPC_TIME_WARDEN                 = 44797,
    NPC_ORPHANED_EMERALD_WHELP      = 44641,
    NPC_SPIKE                       = 44765,

    // Valiona and Theralion
    NPC_TWILIGHT_SENTRY             = 50008,
    NPC_DAZZ_DESTRUCTION_STALKER    = 46374,
    NPC_UNSTABLE_TWILIGHT           = 46304,
    NPC_TWILIGHT_RIFT               = 50014,
    NPC_TWILIGHT_FLAME              = 46147,
    NPC_THERALION_FLIGHT_STALKER    = 46364,
    NPC_DEVOURING_FLAMES_STALKER    = 46588,
    NPC_FABULOUS_FLAME_STALKER      = 46448,
    NPC_COLLAPSING_TWILIGHT_PORTAL  = 46301,

    // Ascendant Lord Council
    NPC_ASCENDANT_COUNCIL           = 45420,
    NPC_ASCENDANT_CONTROLLER        = 43691,
    NPC_WATER_BOMB                  = 44201,
    NPC_INFERNO_RUSH                = 47501,
    NPC_VIOLENT_CYCLONE             = 44747,
    NPC_LIQUID_ICE                  = 45452,
    NPC_ERUPTION_TARGET             = 44845,
    NPC_GRAVITY_CRUSH               = 45476,
    NPC_GRAVITY_WELL                = 44824,
    NPC_TARGET_STALKER              = 44553,

    // Cho'Gall
    NPC_FIRE_PORTAL                 = 43393,
    NPC_FIRE_ELEMENTAL              = 43406,
    NPC_BLAZE                       = 43585,

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
