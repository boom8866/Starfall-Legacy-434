
#ifndef DEF_GRIM_BATOL_H
#define DEF_GRIM_BATOL_H

enum Data
{
    DATA_GENERAL_UMBRISS,
    DATA_FORGEMASTER_THRONGUS,
    DATA_DRAHGA_SHADOWBURNER,
    DATA_ERUDAX,
    ENCOUNTER_COUNT,
    DATA_SHADOW_GALE_STALKER_ACTIVE
};

enum CreatureIds
{
    // Bosses
    BOSS_GENERAL_UMBRISS            = 39625,
    BOSS_FORGEMASTER_THRONGUS       = 40177,
    BOSS_DRAHGA_SHADOWBURNER        = 40319,
    BOSS_ERUDAX                     = 40484,

    //  Various NPCs
    NPC_VELASTRASZA                 = 50390,
    NPC_VALIONA                     = 40320,
    NPC_BALEFLAME                   = 50387,
    NPC_FARSEER_TOORANU             = 50385,

    // General Umbriss
    NPC_BLITZ_DUMMY                 = 40040,
    NPC_SIEGE_DUMMY                 = 40030,
    NPC_MALIGNANT_TROGG             = 39984,
    NPC_TROGG_DWELLER               = 45467,

    // Forgemaster Throngus
    NPC_CAVE_IN_STALKER             = 40228,
    NPC_FIRE_PATCH                  = 48711,
    NPC_TWILIGHT_ARCHER             = 40197,
    NPC_FIXATE_TRIGGER              = 40255,

    // Drahga Shadowburner
    NPC_INVOCATION_OF_FLAME_STALKER = 40355,
    NPC_INVOKED_FLAMING_SPIRIT      = 40357,
    NPC_SEEPING_TWILIGHT_TRIGGER    = 40365,

    // Erudax
    NPC_FACELESS                    = 40600,
    NPC_FACELESS_HC                 = 48844,
    NPC_FACELESS_PORTAL_STALKER     = 44314,
    NPC_ALEXSTRASZAS_EGG            = 40486,
    NPC_TWILIGHT_HATCHLING          = 39388,
    NPC_SHADOW_GALE_CONTROLLER      = 40566,
    NPC_SHADOW_GALE_TRIGGER         = 40567,

    // Trash
    NPC_ASCENDED_FLAMESEEKER        = 39415,
    NPC_ASCENDED_ROCKBREAKER        = 40272,
    NPC_ASCENDED_WATERLASHER        = 40273,
    NPC_ASCENDED_WINDWALKER         = 39414,
    NPC_AZURBORNE_GUARDIAN          = 39854,
    NPC_AZURBORNE_SEER              = 39855,
    NPC_AZURBORNE_WARLORD           = 39909,
    NPC_BATTERED_RED_DRAKE_EVENT    = 39294,
    NPC_BATTERED_RED_DRAKE          = 48523,
    NPC_TWILIGHT_DRAKE              = 39390,
    NPC_CRIMSONBORNE_GUARDIAN       = 39381,
    NPC_CRIMSONBORNE_SEER           = 40290,
    NPC_CRIMSONBORNE_WARLORD        = 39626,
    NPC_ENSLAVED_BURNING_EMBER      = 39892,
    NPC_ENSLAVED_ROCK_ELEMENTAL     = 39900,
    NPC_ENSLAVED_THUNDER_SPIRIT     = 40269,
    NPC_ENSLAVED_GRONN_BRUTE        = 40166,
    NPC_ENSLAVED_WATER_SPIRIT       = 39961,
    NPC_TWILIGHT_FIRE_CATCHER       = 39870,
    NPC_TWILIGHT_SHADOW_WEAVER      = 39954,
    NPC_TWILIGHT_STORM_BREAKER      = 39962,
    NPC_TWILIGHT_THUNDER_CALLER     = 40270,
    NPC_TWILIGHT_WYRM_CALLER        = 39873,
    NPC_TWILIGHT_EARTHSHAPER        = 39890,
    NPC_TWILIGHT_BEGUILER           = 40167,
};

enum GameObjectIds
{
    GO_DWARVEN_BONE_PILE            = 207411,
};

enum InstanceSpells
{
    SPELL_TWILIGHT_FLAMES_TRIGGER   = 75928, // (Triggers: 75933 every 30s)#
    SPELL_NO_HEALTH_REGEN           = 52455,
};

enum InstanceActions
{
    ACTION_DRAGON_IS_IN_FOLLOWER_EVENT = 1,
    ACTION_START_DRAGON_EVENT,
};

struct StairSpawnerData
{
    uint32 entry0;
    uint32 entry1;
    uint32 timeMin;
    uint32 timeMax;
    Position startPosition;
    Position endPosition;
    uint32 duration;
};

#endif
