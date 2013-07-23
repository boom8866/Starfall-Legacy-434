/*
 * Copyright (C) 2011 - 2013 Madman <https://github.com/oMadMano>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#ifndef DEF_GILNEAS_H
#define DEF_GILNEAS_H

enum Data
{
};

enum Data64
{
};

enum CreatureIds
{
    NPC_PRINCE_LIAM_GREYMANE                          = 34913,
    NPC_GILNEAS_CITY_GUARD                            = 34916,
    NPC_RAMPAGING_WORGEN_1                            = 34884,
    NPC_RAMPAGING_WORGEN_2                            = 35660,
    NPC_BLOODFANG_WORGEN                              = 35118,
    NPC_SERGEANT_CLEESE                               = 35839,
    NPC_MYRIAM_SPELLWALKER                            = 35872,
    NPC_GILNEAN_ROYAL_GUARD                           = 35232,
    NPC_FRIGHTENED_CITIZEN_1                          = 34981,
    NPC_FRIGHTENED_CITIZEN_2                          = 35836,
    NPC_DARIUS_CROWLEY                                = 35230,
    NPC_NORTHGATE_REBEL_1                             = 36057, // phase 8 outside cathedral
    NPC_NORTHGATE_REBEL_2                             = 41015, // phase 1024 inside cathedral
    NPC_BLOODFANG_STALKER_C1                          = 35229, // Main spawns
    NPC_BLOODFANG_STALKER_C2                          = 51277,
    NPC_BLOODFANG_STALKER_CREDIT                      = 35582,
    NPC_CROWLEY_HORSE                                 = 35231,
    NPC_LORD_DARIUS_CROWLEY_C1                        = 35077, // Quest - By the skin of his teeth start/stop
    NPC_WORGEN_ALPHA_C1                               = 35170, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_ALPHA_C2                               = 35167, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_RUNT_C1                                = 35188, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_RUNT_C2                                = 35456, // Quest - By the skin of his teeth spawns
    NPC_SEAN_DEMPSEY                                  = 35081, // Quest - By the skin of his teeth controller= 35370,
    NPC_JOSIAH_AVERY_P4                               = 35370, // NPC for worgen bite
    NPC_JOSIAH_AVERY_TRIGGER                          = 50415, // Controller for Worgen Bite
    NPC_LORNA_CROWLEY_P4                              = 35378, // Quest - From the Shadows
    NPC_BLOODFANG_RIPPER_P4                           = 35505, // General AI spawns
    NPC_GILNEAN_MASTIFF                               = 35631,
    NPC_GILNEAS_CITY_GUARD_P8                         = 50474,
    NPC_AFFLICTED_GILNEAN_P8                          = 50471,
    NPC_KRENNAN_ARANAS_TREE                           = 35753,
    NPC_GREYMANE_HORSE_P4                             = 35905,
    NPC_MARKER                                        = 28332
};

enum GameObjectIds
{
};

enum QuestIds
{
    QUEST_LOCKDOWN                                     = 14078,
    QUEST_EVAC_MERC_SQUA                               = 14098,
    QUEST_SOMETHINGS_AMISS                             = 14091,
    QUEST_ALL_HELL_BREAKS_LOOSE                        = 14093,
    QUEST_ROYAL_ORDERS                                 = 14099,
    QUEST_BY_THE_SKIN_ON_HIS_TEETH                     = 14154,
    QUEST_SACRIFICES                                   = 14212,
    QUEST_THE_REBEL_LORDS_ARSENAL                      = 14159
};

enum PhaseSpellIds
{
    // Daca de ex avem un npc in phase 6 o sa fi vazut si in phase 2 si phase 4
    // sau in ambele deci phase 1 + phase n npc-ul poate fi vazut in toate phase-urile
    // pe rand sau in suma lor :)
    SPELL_PHASE_2                                      = 78321, // 1
    SPELL_PHASE_4                                      = 59074, // 2
    SPELL_PHASE_1024                                   = 67789, // 4
    SPELL_PHASE_2048                                   = 68480, // 5
    SPELL_PHASE_4096                                   = 68481, // 6
    SPELL_PHASE_8192                                   = 68482, // 7
    SPELL_PHASE_16384                                  = 68483, // 8
    SPELL_PHASE_32768                                  = 69077, // 9
    SPELL_PHASE_65536                                  = 69078, // 10
    SPELL_PHASE_131072                                 = 69484, // 11
    SPELL_PHASE_262144                                 = 69485, // 12
};
enum SpellIds
{
    SPELL_ENRAGE                                       = 8599,
    SPELL_FROSTBOLT_VISUAL_ONLY                        = 74277, // Dummy spell, visual only
    SPELL_SUMMON_CROWLEY                               = 67004,
    SPELL_RIDE_HORSE                                   = 43671,
    SPELL_THROW_TORCH                                  = 67063,
    SPELL_RIDE_VEHICLE_HARDCODED                       = 46598,
    SPELL_LEFT_HOOK                                    = 67825,
    SPELL_SNAP_KICK                                    = 67827,
    SPELL_BY_THE_SKIN_ON_HIS_TEETH                     = 66914,
    SPELL_SHOOT                                        = 6660,
    SPELL_INFECTED_BITE                                = 72872,
    SPELL_GILNEAS_CANNON_CAMERA                        = 93555,
    SPELL_SUMMON_JOSIAH_AVERY                          = 67350,
    SPELL_GET_SHOT                                     = 67349,
    SPELL_SUMMON_JOSIAH                                = 67350,
    SPELL_PHASE_QUEST_2                                = 59073,
    SPELL_SUMMON_GILNEAN_MASTIFF                       = 67807,
    SPELL_DISMISS_GILNEAN_MASTIFF                      = 43511,
    SPELL_PING_GILNEAN_CROW                            = 93275
};

enum NpcTextIds
{
    DELAY_SAY_PRINCE_LIAM_GREYMANE                     = 20000, // 20 seconds repetition time

    DELAY_YELL_PRINCE_LIAM_GREYMANE                    = 2000,

    SAY_KRENNAN_C2                                     = 0,
    SAY_GREYMANE_HORSE                                 = 0,
    SAY_CROWLEY_HORSE_1                                = 0,    // Let''s round up as many of them as we can.  Every worgen chasing us is one less worgen chasing the survivors!
    SAY_CROWLEY_HORSE_2                                = 1,    // You'll never catch us, you blasted mongrels! || Come and get us, you motherless beasts! || Over here, you flea bags!
    SAY_JOSIAH_AVERY_P2                                = 1,
    SAY_JOSAIH_AVERY_P4                                = 1,
    SAY_JOSAIH_AVERY_TRIGGER                           = 1,
    SAY_LORNA_CROWLEY_P4                               = 0,
    SAY_KING_GENN_GREYMANE_P4                          = 1,
    SAY_GILNEAS_CITY_GUARD_P8                          = 1,
    SAY_LORD_GODFREY_P4                                = 0,
    SAY_NPC_KRENNAN_ARANAS_TREE                        = 0
};

enum SoundIds
{
    SOUND_SWORD_FLESH                                 = 143,
    SOUND_SWORD_PLATE                                 = 147,
    SOUND_WORGEN_ATTACK                               = 558,
    DELAY_SOUND                                       = 500,
    DELAY_ANIMATE                                     = 2000
};

struct Waypoint
{
    float X, Y, Z;
};

Waypoint NW_WAYPOINT_LOC1[2]=
{
    { -1630.62f, 1480.55f, 70.40f }, // Worgen Runt 1 top edge of Roof Waypoint
    { -1636.01f, 1475.81f, 64.51f }  // Worgen Runt 1 Edge of Roof Waypoint
};

Waypoint NW_WAYPOINT_LOC2[2]=
{
    { -1637.26f, 1488.86f, 69.95f }, // Worgen Runt 1 top edge of Roof Waypoint
    { -1642.45f, 1482.23f, 64.30f }  // Worgen Runt 1 Edge of Roof Waypoint
};

Waypoint SW_WAYPOINT_LOC1[2]=
{
    { -1718.31f, 1526.62f, 55.91f }, // Worgen Runt 2 Corner where we turn
    { -1717.86f, 1490.77f, 56.61f }  // Worgen Runt 2 Edge of Roof Waypoint
};

Waypoint SW_WAYPOINT_LOC2[2]=
{
    { -1718.31f, 1526.62f, 55.91f }, // Worgen Alpha 1 Corner where we turn
    { -1717.86f, 1487.00f, 57.07f }  // Worgen Alpha 1 Edge of Roof Waypoint
};

Waypoint N_WAYPOINT_LOC[1]=
{
    { -1593.38f, 1408.02f, 72.64f } // Worgen Runt 2 Edge of Roof Waypoint
};

#define DELAY_EMOTE_PANICKED_CITIZEN                  urand(5000, 15000)   // 5-15 second time
#define DELAY_SAY_PANICKED_CITIZEN                    urand(30000, 120000) // 30sec - 1.5min
#define DELAY_SAY_GILNEAS_CITY_GUARD_GATE             urand(30000, 120000) // 30sec - 1.5min
#define PATHS_COUNT_PANICKED_CITIZEN                  8
#define CD_ENRAGE                                     30000
#define SUMMON1_TTL                                   300000
#define PATHS_COUNT                                   2
#define DOOR_TIMER                                    30*IN_MILLISECONDS
#define KRENNAN_END_X                                 -1772.4172f
#define KRENNAN_END_Y                                 1430.6125f
#define KRENNAN_END_Z                                 19.79f
#define KRENNAN_END_O                                 2.79f
#define CROWLEY_SPEED                                 1.85f // if set much lower than this, the horse automatically despawns before reaching the end of his waypoints
#define AI_MIN_HP                                     85
#define Event_Time                                    118500
#define WORGEN_EVENT_SPAWNTIME                        20000 // Default Despawn Timer
#define NW_ROOF_SPAWN_LOC_1                           -1618.86f, 1505.68f, 70.24f, 3.91f
#define NW_ROOF_SPAWN_LOC_2                           -1611.40f, 1498.49f, 69.82f, 3.79f
#define SW_ROOF_SPAWN_LOC_1                           -1732.81f, 1526.34f, 55.39f, 0.01f
#define SW_ROOF_SPAWN_LOC_2                           -1737.49f, 1526.11f, 55.51f, 0.01f
#define N_ROOF_SPAWN_LOC                              -1562.59f, 1409.35f, 71.66f, 3.16f
#define PLATFORM_Z                                    52.29f

#define THE_LAST_STAND_P1                             -1602.970947f, 1528.768311f, 29.233564f, 0.0f
#define THE_LAST_STAND_P2                             -1588.439575f, 1512.532593f, 29.230589f, 0.0f 
#define THE_LAST_STAND_P3                             -1590.162842f, 1527.138916f, 29.232660f, 0.0f

bool BFGC_EVENT;

const Position SpawnMilitaFront[28] =
{
    {-1665.11f,1659.45f,20.5731f,1.81514f},
    {-1670.59f,1661.02f,20.5731f,0.872665f},
    {-1402.84f,1228.7f,35.5595f,1.7851f},
    {-1400.46f,1229.22f,35.5595f,1.7851f},
    {-1408.65f,1236.64f,35.5596f,1.7851f},
    {-1397.4f,1229.88f,35.5595f,1.7851f},
    {-1394.32f,1230.55f,35.5595f,1.7851f},
    {-1407.98f,1233.56f,35.5596f,1.7851f},
    {-1406.25f,1237.16f,35.5596f,1.7851f},
    {-1400.1f,1241.8f,35.6354f,1.7851f},
    {-1407.61f,1240.17f,35.7024f,1.7851f},
    {-1401.06f,1235.06f,35.5596f,1.7851f},
    {-1396.36f,1233.51f,35.5596f,1.7851f},
    {-1398.4f,1242.17f,35.6202f,1.7851f},
    {-1397.99f,1235.73f,35.5596f,1.7851f},
    {-1403.47f,1234.54f,35.5596f,1.7851f},
    {-1406.64f,1231.27f,35.5596f,1.7851f},
    {-1405.56f,1240.61f,35.6839f,1.7851f},
    {-1406.59f,1227.88f,35.5595f,1.7851f},
    {-1409.02f,1230.75f,35.5596f,1.7851f},
    {-1402.81f,1241.21f,35.6598f,1.7851f},
    {-1406.21f,1233.94f,35.5596f,1.7851f},
    {-1404.24f,1231.79f,35.5596f,1.7851f},
    {-1397.71f,1239.02f,35.5596f,1.7851f},
    {-1401.14f,1232.47f,35.5596f,1.7851f},
    {-1400.11f,1238.49f,35.5596f,1.7851f},
    {-1403.52f,1237.75f,35.5596f,1.7851f},
    {-1398.41f,1233.06f,35.5596f,1.7851f},
};

const Position SpawnMilitaBack[27] =
{
    {-1402.24f,1250.57f,36.428f,1.77725f},
    {-1405.83f,1257.99f,36.4282f,1.7323f}, 
    {-1410.25f,1254.62f,36.4278f,1.71049f},
    {-1414.41f,1254.04f,36.4278f,1.71049f},
    {-1414.0f,1251.06f,36.4278f,1.71049f},
    {-1402.96f,1247.05f,36.428f,1.77725f},
    {-1409.79f,1248.99f,36.428f,1.77725f},
    {-1408.24f,1257.51f,36.4278f,2.11104f},
    {-1405.06f,1255.35f,36.4278f,1.71049f},
    {-1398.39f,1245.35f,36.4273f,1.85972f},
    {-1410.77f,1245.47f,36.4278f,1.85972f},
    {-1410.53f,1239.18f,35.6291f,1.85972f},
    {-1402.42f,1244.44f,36.428f,1.7851f},
    {-1405.0f,1250.0f,36.428f,1.77725f},
    {-1411.28f,1256.65f,36.4278f,1.71049f},
    {-1407.75f,1249.42f,36.428f,1.77725f},
    {-1411.32f,1242.5f,36.428f,1.7851f},
    {-1402.56f,1252.67f,36.4278f,1.71049f},
    {-1401.6f,1255.84f,36.4278f,1.71049f},
    {-1400.39f,1247.4f,36.4278f,1.85972f},
    {-1406.05f,1252.18f,36.4278f,1.71049f},
    {-1408.1f,1246.26f,36.4278f,1.85972f},
    {-1407.49f,1255.01f,36.4278f,1.71049f},
    {-1409.84f,1251.65f,36.4278f,1.71049f},
    {-1405.35f,1246.55f,36.428f,1.77725f},
    {-1407.22f,1243.4f,36.428f,1.7851f},
    {-1404.82f,1243.92f,36.428f,1.7851f},
};

#endif