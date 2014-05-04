
#ifndef DEF_DEADMINES_H
#define DEF_DEADMINES_H

enum Data
{
    DATA_GLUBTOK,
    DATA_HELIX,
    DATA_REAPER,
    DATA_RIPSNARL,
    DATA_COOKIE,
    DATA_CANNON_BLAST_TIMER,
    DATA_VANESSA,
    DATA_VANNESSA_NIGHTMARE,
    DATA_NIGHTMARE_HELIX,
    DATA_NIGHTMARE_MECHANICAL,

    MAX_BOSSES
};

enum eCreatures
{
    // Foe Reaper 5000 Encounter
    BOSS_FOE_REAPER_5000            = 43778,
    NPC_DEFIAS_REAPER               = 47403,
    NPC_DEFIAS_WATCHER              = 47404,
    NPC_PROTOTYPE_REAPER            = 49208,

    NPC_OAF                         = 47297,
    NPC_HELIX_GEARBREAKER           = 47296,
    NPC_GENERAL_PURPOSE_BUNNY_JMF   = 45979,
    NPC_GENERAL_PURPOSE_BUNNY_JMF2  = 47242,
    NPC_FIRE_BLOSSOM_DUMMY          = 47282,
    NPC_FROST_BLOSSOM_DUMMY         = 47284,

    NPC_OGRE_HENCHMAN               = 48230,
    NPC_MINE_RAT                    = 51462,
    NPC_ADMIRAL_RIPSNARL            = 47626,
    NPC_VAPOR                       = 47714,

    NPC_FIRE_WALL_CENTER            = 48974,

    // A Platter
    NPC_FIRE_WALL_1A                = 48975, // 2x
    NPC_FIRE_WALL_2A                = 48976, // 4x
    // B Platter
    NPC_FIRE_WALL_1B                = 49039, // 2x
    NPC_FIRE_WALL_2B                = 49041, // 4x
    // C Platter
    NPC_FIRE_WALL_1C                = 49040, // 2x
    NPC_FIRE_WALL_2C                = 49042, // 4x

    NPC_HARVEST_TARGET              = 47468,
    NPC_CAPTAIN_COOKIE              = 47739,
    NPC_VANESSA_VANCLEEF            = 49429,
    NPC_VANESSA_BOSS                = 49541,
    NPC_VANESSA_NOTE                = 49564,
    NPC_SCORCH_MARK_BUNNY_JMF       = 48446,
    NPC_TRAP_BUNNY                  = 49454,
    NPC_STEAM_VALVE                 = 49457,
    NPC_ROPE                        = 49550,
    NPC_ROPE_ANCHOR                 = 49552,

    NPC_DEFIAS_SHADOWGUARD          = 48505,
    NPC_DEFIAS_ENFORCER             = 48502,
    NPC_DEFIAS_BLOODWIZARD          = 48417,
    NPC_DEFIAS_PIRATE               = 48522,
    NPC_HELIX_CREW                  = 49136,

    //Nightmare NPC
    NPC_VANESSA_NIGHTMARE           = 49671,
    NPC_GLUBTOK_NIGHTMARE           = 49670,
    NPC_FIRE_BUNNY                  = 51594,
    NPC_COLAPSING                   = 49481,
    NPC_HELIX_NIGHTMARE             = 49674,
    NPC_NIGHTMARE_SPIDER            = 49493,
    NPC_MAIN_SPIDER                 = 49494,
    NPC_CHATTERING_HORROR           = 49495,
    NPC_SPARK                       = 49520,
    NPC_MECHANICAL_NIGHTMARE        = 49681,

    NPC_ENRAGED_WORGEN              = 49532,
    NPC_EMME_HARRINGTON             = 49534,
    NPC_ERIK_HARRINGTON             = 49535,
    NPC_CALISSA_HARRINGTON          = 49536,
    NPC_JAMES_HARRINGTON            = 49539,

};

enum GameObjects
{
    GO_FACTORY_DOOR                 = 13965, // Door after Glubtok
    GO_IRONCLAD_DOOR                = 16397, // Door before ship
    GO_FOUNDRY_DOOR                 = 16399, // Door after Foe Reaper 5000
    GO_HEAVY_DOOR                   = 17154, // Door before Foe Reaper 5000
    GO_HEAVY_DOOR_HELIX             = 16400, // Door after helix

    GO_DEFIAS_CANNON                = 16398,
    GO_MR_SMITE_CHEST               = 144111
};

enum eSound
{
    SOUND_CANNONFIRE                = 1400,
    SOUND_DESTROYDOOR               = 3079,
};

enum eAcievement
{
    ACHIEVE_RAT_PACK                = 5367,
};

const Position CookieSpawn = {
    -88.1319f, -819.33f, 39.23453f, 0.0f
};

enum Data64
{

};

#endif
