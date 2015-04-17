
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "firelands.h"

enum Texts
{
    // Ragnaros
    SAY_ARRIVE                      = 0,
    SAY_AGGRO                       = 1,
    SAY_SLAY                        = 2,
    SAY_WRATH_OF_RAGNAROS           = 3,
    SAY_ANNOUNCE_SULFURAS_SMASH     = 4,
    SAY_ANNOUNCE_MAGMA_TRAP         = 5,
    SAY_SPLITTING_BLOW              = 6,
    SAY_ANNOUNCE_SPLITTING_BLOW     = 7,
    SAY_PHASE_TRANSITION            = 8,
    SAY_EMERGE                      = 9,
    SAY_ANNOUNCE_EMERGE             = 10,
    SAY_ANNOUNCE_ENGULFING_FLAMES   = 11,
    SAY_ANNOUNCE_WORLD_IN_FLAMES    = 12,
    SAY_DEATH_NORMAL                = 13,


    /*
    SAY_DEATH_NORMAL            = 2,
    SAY_DEATH_HEROIC            = 3,
    SAY_ANNOUNCE_SPLIT          = 5,
    SAY_SUBMERGE                = 6,
    SAY_EMERGE                  = 7,
    SAY_SONS_OF_FLAME_1         = 8,
    SAY_SONS_OF_FLAME_2         = 9,
    SAY_ANNOUNCE_EMERGE         = 10,
    SAY_MAGMA_TRAP              = 11,
    SAY_ANNOUNCE_SULFURAS_SMASH = 12,
    SAY_SUBMERGE_HEROIC         = 13,
    SAY_INTRO_HEROIC_1          = 14,
    SAY_INTRO_HEROIC_2          = 15,
    SAY_ENGULFING_FLAMES        = 16,
    SAY_WORLD_IN_FLAMES         = 17,
    SAY_EMPOWER_SULFURAS        = 18,
    SAY_DREADFLAME              = 19,
    */
    // Cenarius
    SAY_CENARIUS_1 = 0,
    SAY_CENARIUS_OUTRO_1 = 1,
    SAY_CENARIUS_OUTRO_2 = 2,
    SAY_CENARIUS_OUTRO_3 = 3,

    // Malfurion
    SAY_MALFURION_1 = 0,
    SAY_MALFURION_OUTRO_1 = 1,
    SAY_MALFURION_OUTRO_2 = 2,

    // Hamuul
    SAY_HAMUUL_OUTRO_1 = 0,
};

enum Spells
{
    // Ragnaros
    SPELL_BASE_VISUAL                       = 98860,
    SPELL_BURNING_WOUNDS_AURA               = 99401,
    SPELL_MAGMA_PERIODIC                    = 99908,
    SPELL_SULFURAS_SMASH_AOE                = 98703,
    SPELL_SULFURAS_SMASH                    = 98710,
    SPELL_SUMMON_SULFURAS_SMASH_TARGET      = 98706,
    SPELL_MAGMA_STRIKE                      = 98313,
    SPELL_HAND_OF_RAGNAROS                  = 98237,
    SPELL_WRATH_OF_RAGNAROS                 = 98263,
    SPELL_SUBMERGE                          = 100051,
    SPELL_SUBMERGE_AURA                     = 98982,
    SPELL_SPLITTING_BLOW_WEST               = 98953,
    SPELL_SPLITTING_BLOW_NORTH              = 98952,
    SPELL_SPLITTING_BLOW_EAST               = 98951,
    SPELL_ENGULFING_FLAMES_MELEE            = 99172,
    SPELL_ENGULFING_FLAMES_CENTER           = 99235,
    SPELL_ENGULFING_FLAMES_RANGE            = 99236,
    SPELL_ENGULFING_FLAMES_VISUAL_MELEE     = 99216,
    SPELL_ENGULFING_FLAMES_VISUAL_CENTER    = 99217,
    SPELL_ENGULFING_FLAMES_VISUAL_RANGE     = 99218,
    SPELL_WOLRD_IN_FLAMES                   = 100171,
    SPELL_LIVING_METEOR                     = 99268,


    // Molten Seed
    SPELL_MOLTEN_SEED                       = 98333,
    SPELL_MOLTEN_SEED_SUMMON                = 100141,
    SPELL_MOLTEN_SEED_MISSILE               = 98495,
    SPELL_MOLTEN_SEED_DAMAGE                = 98498,
    SPELL_UNK_1                             = 98497,

    // Molten Elemental
    SPELL_INVISIBLE_PRE_VISUAL              = 100153,
    SPELL_MOLTEN_SEED_VISUAL                = 98520,
    SPELL_MOLTEN_INFERNO                    = 98518,
    SPELL_MOLTEN_POWER_AURA                 = 100157,
    SPELL_MOLTEN_POWER_PERIODIC             = 100158,

    // Engulfing Flame
    SPELL_ENGULFING_FLAMES_AURA             = 99225,

    // Lava Scion
    SPELL_BLAZING_HEAT                      = 100460,
    SPELL_BLAZING_HEAT_SONAR                = 100459,

    // Blazing Heat
    SPELL_BLAZING_HEAT_AURA                 = 99126,
    SPELL_BLAZING_HEAT_SUMMON               = 99129,
    SPELL_BLAZING_HEAT_DUMMY                = 99125,
    SPELL_BLAZING_HEAT_DAMAGE_AURA          = 99128,

    // Living Meteor
    SPELL_LIVING_METEOR_PERIODIC            = 99269,
    SPELL_COMBUSTIBLE                       = 99296,
    SPELL_FIXATE                            = 99849,
    SPELL_COMBUSTITION                      = 99303,
    SPELL_METEOR_IMPACT                     = 99287,
    SPELL_LIVING_METEOR_DUMMY               = 99279,

    SPELL_LIVING_METEOR_DAMAGE_REDUCTION    = 100904,
    SPELL_LIVING_METEOR_EXPLOSION_TRIGGER   = 99269,
    SPELL_LIVING_METEOR_UNK                 = 99267,
    SPELL_LIVING_METEOR_EXPLOSION           = 99287,
    SPELL_LIVING_METEOR_INCREASE_SPEED      = 100278,

    // Heroic Encounter

    // Ragnaros
    SPELL_LEGS_HEAL                         = 100346,
    SPELL_TRANSFORM                         = 100420,
    SPELL_SUPERHEATED                       = 100593,
    SPELL_SUPERHEATED_TRIGGERED             = 100594,

    SPELL_EMPOWER_SULFURAS                  = 100604,
    SPELL_EMPOWER_SULFURAS_TRIGGER          = 100605,
    SPELL_EMPOWER_SULFURAS_MISSILE          = 100606,

    // Dreadflame
    SPELL_SUMMON_DREADFLAME_PERIODIC        = 100691,
    SPELL_SUMMON_DREADFLAME                 = 100675, //100679
    SPELL_DREADFLAME_CONTROL_AURA_1         = 100695,
    SPELL_DREADFLAME_AURA_1_TRIGERED        = 100966,
    SPELL_DREADFLAME_CONTROL_AURA_2         = 100696, // this triggers another spell which causes a water effect
    SPELL_DREADFLAME_AURA_2_TRIGERED        = 100823,
    SPELL_DREADFLAME_DAMAGE_AURA            = 100692, // area aura (dynobjects)
    SPELL_DREADFLAME_CONTROL_AURA_3         = 100905,
    SPELL_DREADFLAME_AURA_3_TRIGERED        = 100906,
    SPELL_DREADFLAME_DAMAGE                 = 100941,

    SPELL_DREADFLAME_SUMMON_MISSILE         = 100675, // summons the spawn npc for a short while

    // Protection Traps
    SPELL_BREADTH_OF_FROST_SCRIPT           = 100472,
    SPELL_BREADTH_OF_FROST_SUMMON           = 100476,
    SPELL_BREADTH_OF_FROST_AURA             = 100479,
    SPELL_BREADTH_OF_FROST_STUN             = 100567, // condition to target living meteors in all 3 spell effects
    SPELL_BREADTH_OF_FROST_PROTECTION       = 100503, // spell effect script effect needs spellscript for immunity spell id (100594)

    SPELL_ENTRAPPING_ROOTS_AURA_MISSILE     = 100646,
    SPELL_ENTRAPPING_ROOTS_SUMMON           = 100644, // summons dummy to target first
    SPELL_ENTRAPPING_ROOTS_ROOT             = 100653, // condition to target ragnaros

    SPELL_CLOUDBURST_DUMMY                  = 100751, // condition to target platform stalker / triggers summon spell on hit
    SPELL_CLOUDBURST_SUMMON                 = 100714,
    SPELL_CLOUDBURST_DUMMY_AURA             = 100758, // visual for npc
    SPELL_CLOUDBURST_VISUAL_WATER           = 100757,
    SPELL_CLOUDBURST_PLAYER_AURA            = 100713,

    // Hamuul Runetotem
    SPELL_TRANSFORM_HAMUUL                  = 100311,
    SPELL_HAMUL_DRAW_FIRELORD               = 100344,

    // Malfurion Stormrage
    SPELL_TRANSFORM_MALFURION               = 100310,
    SPELL_MALFURION_DRAW_FIRELORD           = 100342,

    // Cenarius
    SPELL_CENARIUS_DRAW_FIRELORD            = 100345,

    // Heart of Ragnaros
    SPELL_RAGE_OF_RAGNAROS                  = 101110,
    SPELL_HEART_OF_RAGNAROS_SUMMON          = 101254, // summons the heart npc
    SPELL_HEART_OF_RAGNAROS_DUMMY_AURA      = 101127,
    SPELL_HEART_OF_RAGNAROS_CREATE_HEART    = 101125,

    // Sulfuras Smash
    SPELL_LAVA_POOL                         = 98712,
    SPELL_SCORCHED_GROUND                   = 98871,
    SPELL_LAVA_WAVE_N                       = 98874,
    SPELL_LAVA_WAVE_E                       = 98875,
    SPELL_LAVA_WAVE_W                       = 98876,

    // Lava Wave
    SPELL_LAVA_WAVE                         = 98873,

    // Magma Trap
    SPELL_MAGMA_TRAP                        = 98164,
    SPELL_MAGMA_TRAP_UNK                    = 98159,
    SPELL_MAGMA_TRAP_VISUAL                 = 98179,
    SPELL_MAGMA_TRAP_PERIODIC               = 98172,
    SPELL_MAGMA_TRAP_PERIODIC_TICK          = 98171,
    SPELL_MAGMA_TRAP_ERUPTION               = 98175,

    // Sulfuras, Hand of Ragnaros
    SPELL_SULFURAS                          = 100456,
    SPELL_INVOKE_SONS_MISSILE               = 99050,

    // Son of Flame
    SPELL_PRE_VISUAL                        = 98983,
    SPELL_BURNING_SPEED                     = 98473,
    SPELL_BURNING_SPEED_STACKS              = 99414,
    SPELL_SUPERNOVA                         = 99112,
};

enum Phases
{
    PHASE_INTRO         = 1,
    PHASE_1             = 2,
    PHASE_2             = 3,
    PHASE_3             = 4,
    PHASE_SUBMERGE_1    = 5,
    PHASE_SUBMERGE_2    = 6,
    PHASE_HEROIC        = 7,
};

enum Events
{
    // Ragnaros
    EVENT_INTRO = 1,
    EVENT_BASE_VISUAL,
    EVENT_ATTACK,
    EVENT_SULFURAS_SMASH_TRIGGER,
    EVENT_SULFURAS_SMASH,
    EVENT_MAGMA_TRAP,
    EVENT_WRATH_OF_RAGNAROS,
    EVENT_HAND_OF_RAGNAROS,
    EVENT_SPLITTING_BLOW,
    EVENT_TALK_TRANSITION,
    EVENT_ANNOUNCE_EMERGE,
    EVENT_EMERGE,
    EVENT_DETONATE_SONS_OF_FLAME,
    EVENT_ENGULFING_FLAMES,
    EVENT_MOLTEN_SEED,
    EVENT_LIVING_METEOR,

    EVENT_ATTACK_HEROIC,

    // Magma Trap
    EVENT_PREPARE_TRAP,

    // Son of Flame
    EVENT_MOVE_HAMMER,

    // Molten Elemental
    EVENT_PREPARE_ELEMENTAL,
    EVENT_ACTIVATE,

    // Lava Scion
    EVENT_BLAZING_HEAT,

    // Living Meteor
    EVENT_STALK_PLAYER,
    EVENT_MAKE_COMBUSTIBLE,

    // Archdruids
    EVENT_SAY_PULL,
    EVENT_SAY_CAUGHT,
    EVENT_DRAW_RAGNAROS,
    EVENT_TRANSFORM,

    // Ragnaros Heroic Events
    EVENT_EMERGE_HEROIC,
    EVENT_TALK,
    EVENT_TAUNT_EMOTE,
    EVENT_STANDUP,
    EVENT_FREEZE_PLATFORM,
    EVENT_BREAK_PLATFORM,
    EVENT_IDLE,
    EVENT_TRANSFORM_RAGNAROS,
    EVENT_SUMMON_DREADFLAME,
    EVENT_SCHEDULE_EMPOWER,
    EVENT_EMPOWER_SULFURAS,

    // Cenarius
    EVENT_BREADTH_OF_FROST,
    EVENT_TALK_CENARIUS_1,
    EVENT_TALK_CENARIUS_2,
    EVENT_TALK_CENARIUS_3,

    // Hamuul
    EVENT_ENTRAPPING_ROOTS,
    EVENT_TALK_HAMUUL_1,

    // Malfurion
    EVENT_CLOUDBURST,
    EVENT_TALK_MALFURION_1,
    EVENT_TALK_MALFURION_2,

    // Dreadflame
    EVENT_CHECK_PLAYER,
    EVENT_SPREAD_FLAME,

    // Molten Erupter

    // Molten Spewer
};

enum Actions
{
    // Ragnaros
    ACTION_SUMMONED = 1,
    ACTION_CAST_SULFURAS_SMASH,
    ACTION_SUBMERGE,
    ACTION_SON_OF_FLAME_KILLED,
    ACTION_ACTIVATE_SON_OF_FLAME,
    ACTION_CAST_ENGULFING_FLAMES,

    ACTION_ACTIVATE_HEROIC,

    // Archdruids
    ACTION_SCHEDULE_CLOUDBURST,
    ACTION_SCHEDULE_ROOTS,
    ACTION_SCHEDULE_BREADTH,
    ACTION_SCHEDULE_OUTRO,

    // Molten Worms
    ACTION_EMERGE_WORM,
};

enum AnimKits
{
    // Ragnaros
    ANIM_KIT_RESURFACE  = 1465,
    ANIM_KIT_EMERGE     = 1467,
    ANIM_KIT_TAUNT      = 1468,
    ANIM_KIT_STAND_UP   = 1486,
    ANIM_KIT_SUBMERGE   = 1522,
    // Malfurion
    ANIM_KIT_TALK       = 1523,

    // Son of Flame
    ANIM_KIT_UNK_1      = 1370,
};

enum SplittingBlowSides
{
    SIDE_EAST   = 0,
    SIDE_WEST   = 1,
    SIDE_CENTER = 2,
};

enum RagnarosQuest
{
    QUEST_HEART_OF_FIRE = 29307,
};

Position const SplittingTriggerNorth  = { 1023.55f,  -57.158f,   55.4215f,   3.12414f    };
Position const SplittingTriggerEast   = { 1035.45f,  -25.3646f,  55.4924f,   2.49582f    };
Position const SplittingTriggerWest   = { 1036.27f,  -89.2396f,  55.5098f,   3.83972f    };

Position const CenariusSummonPosition = { 795.504f,  -60.138f,   83.652f,    0.02050f    };
Position const HamuulSummonPosition   = { 790.017f,  -50.393f,   97.115f,    6.22572f    };
Position const MalfurionSummonPosition = {781.208f,  -69.534f,   98.061f,    3.89547f    };

Position const MalfurionPoint         = { 984.996f,  -73.638f,   55.348f   };
Position const CenariusPoint          = { 984.1371f, -57.65625f, 55.36652f };
Position const HamuulPoint            = { 982.9132f, -43.22049f, 55.35419f };

const Position SonsOfFlameWest[] =
{
    {999.533f,  -45.74826f, 55.56229f, 5.009095f},
    {1065.372f, -108.8698f, 55.56829f, 2.373648f},
    {1034.168f, -15.93056f, 55.60827f, 4.049164f},
    {1051.76f,  0.1284722f, 55.44715f, 4.031711f},
    {1014.134f, -43.94445f, 55.42412f, 3.979351f},
    {1068.151f, -101.3924f, 55.56828f, 2.565634f},
    {1051.497f, -113.7292f, 55.44935f, 2.391101f},
    {1074.866f, -100.7882f, 55.42414f, 2.600541f},
};

const Position SonsOfFlameNorth[] =
{
    {1065.372f, -108.8698f, 55.56829f, 2.373648f},
    {1030.372f, -23.63715f, 55.44154f, 4.049164f},
    {1014.325f, -88.80209f, 55.52722f, 1.919862f},
    {1051.760f, 0.1284722f, 55.44715f, 4.031711f},
    {1012.120f, -26.89063f, 55.564f,   4.398230f},
    {1055.556f, -8.875f,    55.43348f, 3.874631f},
    {1040.394f, -91.81944f, 55.42585f, 2.234021f},
    {1065.257f, -6.946181f, 55.56818f, 3.839724f},
};

const Position SonsOfFlameEast[] =
{
    {1013.458f, -68.08507f, 55.42097f, 2.513274f},
    {1065.372f, -108.8698f, 55.56829f, 2.373648f},
    {1042.033f, -114.9132f, 55.44709f, 1.919862f},
    {1051.76f,  0.1284722f, 55.44715f, 4.031711f},
    {1061.34f,  -16.74132f, 55.56819f, 3.769911f},
    {1051.497f, -113.7292f, 55.44935f, 2.391101f},
    {1024.845f, -97.67882f, 55.52884f, 2.234021f},
    {1074.866f, -100.7882f, 55.42414f, 2.600541f},
};

/*
    Positions for engulfing flames
*/

Position const EngulfingFlamesMelee[] =
{
    {1086.55f, -18.0885f, 55.4228f},
    {1091.83f, -21.9254f, 55.4241f},
    {1092.52f, -92.3924f, 55.4241f},
    {1079.15f, -15.5312f, 55.4230f},
    {1078.01f, -97.7760f, 55.4227f},
    {1065.44f, -17.7049f, 55.4250f},
    {1063.59f, -97.0573f, 55.4934f},
    {1051.80f, -24.0903f, 55.4258f},
    {1049.27f, -90.6892f, 55.4259f},
    {1042.34f, -32.1059f, 55.4254f},
    {1041.26f, -81.4340f, 55.4240f},
    {1036.82f, -44.3385f, 55.4425f},
    {1036.34f, -69.8281f, 55.4425f},
    {1034.76f, -63.9583f, 55.4397f},
    {1033.93f, -57.0920f, 55.4225f},
    {1086.42f, -96.7812f, 55.4226f},
};

Position const EngulfingFlamesRange[] =
{
    {1052.58f, -120.561f, 55.4561f},
    {1049.73f, -118.396f, 55.5661f},
    {1035.56f, -114.155f, 55.4471f},
    {1024.91f, -106.851f, 55.4471f},
    {1012.09f, -97.5121f, 55.4570f},
    {1005.48f, -86.4569f, 55.4275f},
    {1003.44f, -74.0243f, 55.4063f},
    {1003.07f, -66.4913f, 55.4067f},
    {1002.00f, -58.2396f, 55.4331f},
    {1002.21f, -49.7048f, 55.4075f},
    {1002.71f, -40.7430f, 55.4063f},
    {1006.09f, -27.3680f, 55.4277f},
    {1014.15f, -17.3281f, 55.4628f},
    {1024.44f, -8.1388f,  55.4469f},
    {1035.91f, 0.9097f,   55.4469f},
    {1049.32f, 5.0434f,   55.4632f},
    {1055.33f, 5.0677f,   55.4471f},
    {1032.47f, 13.2708f,  55.4468f},
    {1023.83f, 12.9774f,  55.4469f},
    {1019.59f, 7.7691f,   55.4469f},
    {1012.70f, -4.8333f,  55.6050f},
    {1005.79f, -8.8177f,  55.4672f},
    {1000.80f, -14.5069f, 55.4566f},
    {991.79f,  -25.0955f, 55.4440f},
    {986.60f,  -37.7655f, 55.4411f},
    {988.20f,  -50.3646f, 55.4291f},
    {980.92f,  -58.2655f, 55.4542f},
    {989.86f,  -66.0868f, 55.4331f},
    {985.17f,  -77.3785f, 55.4408f},
    {991.73f,  -87.1632f, 55.4445f},
    {999.75f,  -98.4792f, 55.4426f},
    {1009.55f, -108.161f, 55.4697f},
    {1018.28f, -117.833f, 55.4471f},
    {1023.04f, -128.257f, 55.4471f},
    {1035.17f, -125.646f, 55.4471f},
};

Position const EngulfingFlamesCenter[] =
{
    {1069.66f, -4.5399f,  55.4308f},
    {1062.93f, -4.3420f,  55.5681f},
    {1057.03f, -4.1041f,  55.4258f},
    {1049.97f, -7.2239f,  55.4537f},
    {1036.90f, -14.6181f, 55.5714f},
    {1025.33f, -25.8472f, 55.4068f},
    {1021.84f, -33.7482f, 55.4239f},
    {1018.46f, -43.7673f, 55.4217f},
    {1016.98f, -57.5642f, 55.4133f},
    {1018.28f, -70.1875f, 55.4231f},
    {1021.48f, -79.6075f, 55.4261f},
    {1025.29f, -86.2325f, 55.4071f},
    {1030.21f, -92.8403f, 55.4343f},
    {1038.53f, -100.253f, 55.6012f},
    {1049.66f, -104.905f, 55.4556f},
    {1062.13f, -109.004f, 55.4259f},
    {1069.91f, -109.651f, 55.4277f},
};

Position const LavaScionPos[] =
{
    {1027.306f, -121.7465f, 55.4471f, 1.361f},
    {1026.861f, 5.895833f, 55.44697f, 4.904f},
};

class EngulfingFlamesCheck
{
public:
    EngulfingFlamesCheck() { }

    bool operator()(WorldObject* object)
    {
        return (object->ToUnit()->HasAura(sSpellMgr->GetSpellIdForDifficulty(SPELL_ENGULFING_FLAMES_AURA, object->ToUnit())));
    }
};

class at_sulfuron_keep : public AreaTriggerScript
{
    public:
        at_sulfuron_keep() : AreaTriggerScript("at_sulfuron_keep") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
                if (instance->GetBossState(DATA_RAGNAROS) != DONE)
                    if (!instance->GetData(DATA_RAGNAROS_SUMMONED))
                        instance->SetData(DATA_RAGNAROS_SUMMONED, 1);
            return true;
        }
};

class boss_ragnaros_cata : public CreatureScript
{
public:
    boss_ragnaros_cata() : CreatureScript("boss_ragnaros_cata") { }

    struct boss_ragnaros_cataAI : public BossAI
    {
        boss_ragnaros_cataAI(Creature* creature) : BossAI(creature, DATA_RAGNAROS)
        {
            _submergeCounter = 0;
            _killedSons = 0;
            _lastPlatformFlamed = 0;
            _heartQuest = false;
            _encounterDone = false;
        }

        uint8 _submergeCounter;
        uint8 _killedSons;
        uint8 _lastPlatformFlamed;
        Unit* magma;
        bool _heartQuest;
        bool _encounterDone;

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->SetReactState(REACT_AGGRESSIVE);
            DoCast(me, SPELL_BURNING_WOUNDS_AURA, true);
            events.SetPhase(PHASE_1);
            events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 6000);
            events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 18000);
            events.ScheduleEvent(EVENT_SULFURAS_SMASH, 31000);
            events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 25000);
            events.ScheduleEvent(EVENT_MAGMA_TRAP, 16000);
            HandleDoor(true);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetData(DATA_RAGNAROS_SUMMONED, SPECIAL);
            instance->SetBossState(DATA_RAGNAROS, FAIL);
            summons.DespawnAll();

            if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS_HAND_OF_RAGNAROS, 100.0f, true))
                sulfuras->DespawnOrUnsummon(1);

            if (Creature* lava = me->FindNearestCreature(NPC_MAGMA_POOL_TRIGGER, 100.0f, true))
                if (!lava->HasAura(SPELL_MAGMA_PERIODIC))
                    lava->CastSpell(lava, SPELL_MAGMA_PERIODIC, true);

            HandleDoor(false);
            me->DespawnOrUnsummon(1);
        }

        void JustDied(Unit* killer)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();

            if (!IsHeroic())
            {
                Talk(SAY_DEATH_NORMAL);
                if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS_HAND_OF_RAGNAROS, 100.0f, true))
                    sulfuras->DespawnOrUnsummon(1);

                if (GameObject* cache = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_CACHE_OF_THE_FIRE_LORD)))
                {
                    cache->SetPhaseMask(1, true);
                    cache->SetLootState(GO_READY);
                }

                me->SetHealth(1);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                me->SetStandState(UNIT_STAND_STATE_SUBMERGED);
                me->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);
                me->DespawnOrUnsummon(6000);
            }

            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_LAVA_SCION, 500.0f);

            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->AI()->EnterEvadeMode();

            HandleDoor(false);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_LAVA_SCION: // We handle the despawn of the Lava Scions in a special case due to the encounter frame thing
                    break;
                default:
                    summons.Summon(summon);
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            if (me->HealthBelowPct(70) && _submergeCounter == 0)
            {
                _submergeCounter++;
                events.Reset();
                events.SetPhase(PHASE_SUBMERGE_1);
                events.ScheduleEvent(EVENT_SPLITTING_BLOW, 1);
            }
            else if (me->HealthBelowPct(40) && _submergeCounter == 1)
            {
                _submergeCounter++;
                events.Reset();
                events.SetPhase(PHASE_SUBMERGE_2);
                events.ScheduleEvent(EVENT_SPLITTING_BLOW, 1);
            }
            else if (me->HealthBelowPct(10) && _submergeCounter == 2)
            {
                _submergeCounter++;
                if (!IsHeroic() && !_encounterDone)
                {
                    me->Kill(me);
                    _encounterDone = true;
                }
                else
                    DoAction(ACTION_ACTIVATE_HEROIC);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMONED:
                    me->SetReactState(REACT_PASSIVE);
                    events.SetPhase(PHASE_INTRO);
                    events.ScheduleEvent(EVENT_BASE_VISUAL, 1000, 0);
                    if (instance->GetData(DATA_FIRST_RAGNAROS_SUMMON) == 1)
                    {
                        events.ScheduleEvent(EVENT_INTRO, 5700, 0);
                        instance->SetData(DATA_FIRST_RAGNAROS_SUMMON, 0);
                    }

                    if (Creature* lava = me->FindNearestCreature(NPC_MAGMA_POOL_TRIGGER, 100.0f, true))
                        if (!lava->HasAura(SPELL_MAGMA_PERIODIC))
                            lava->CastSpell(lava, SPELL_MAGMA_PERIODIC, true);

                    me->setActive(true);
                    me->PlayOneShotAnimKit(ANIM_KIT_EMERGE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetHover(true);
                    me->SetDisableGravity(true);
                    break;
                case ACTION_CAST_SULFURAS_SMASH:
                    Talk(SAY_ANNOUNCE_SULFURAS_SMASH);
                    DoCast(me, SPELL_SULFURAS_SMASH);
                    events.ScheduleEvent(EVENT_ATTACK, 6000);
                    break;
                case ACTION_SUBMERGE:
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    break;
                case ACTION_SON_OF_FLAME_KILLED:
                    _killedSons++;
                    if (_killedSons == 8)
                    {
                        events.CancelEvent(EVENT_DETONATE_SONS_OF_FLAME);
                        events.CancelEvent(EVENT_ANNOUNCE_EMERGE);
                        events.ScheduleEvent(EVENT_EMERGE, 1000);
                    }
                    break;
                case ACTION_CAST_ENGULFING_FLAMES:
                    me->ClearUnitState(UNIT_STATE_CASTING);
                    CastEngulfingFlames();
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);
            
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INTRO:
                        Talk(SAY_ARRIVE);
                        me->AddAura(SPELL_BURNING_WOUNDS_AURA, me);
                        me->PlayOneShotAnimKit(ANIM_KIT_TAUNT);
                        break;
                    case EVENT_BASE_VISUAL:
                        me->AddAura(SPELL_BASE_VISUAL, me);
                        break;
                    case EVENT_WRATH_OF_RAGNAROS:
                        Talk(SAY_WRATH_OF_RAGNAROS);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_WRATH_OF_RAGNAROS);
                        break;
                    case EVENT_SULFURAS_SMASH:
                        DoCast(me, SPELL_SULFURAS_SMASH_AOE);
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, !events.IsInPhase(PHASE_2) ? 31000 : 41000);
                        if (events.IsInPhase(PHASE_1))
                        {
                            events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 6000);
                            events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 18000);
                        }
                        break;
                    case EVENT_HAND_OF_RAGNAROS:
                        DoCast(me, SPELL_HAND_OF_RAGNAROS);
                        events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 25000, 0, PHASE_1);
                        break;
                    case EVENT_MAGMA_TRAP:
                        Talk(SAY_ANNOUNCE_MAGMA_TRAP);
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 0, true, 0))
                            DoCast(target, SPELL_MAGMA_TRAP);
                        events.ScheduleEvent(EVENT_MAGMA_TRAP, 25000);
                        break;
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS_HAND_OF_RAGNAROS, 100.0f, true))
                            sulfuras->DespawnOrUnsummon(1);
                        break;
                    case EVENT_SPLITTING_BLOW:
                        Talk(SAY_SPLITTING_BLOW);
                        Talk(SAY_ANNOUNCE_SPLITTING_BLOW);
                        CastSplittingBlow(urand(SIDE_EAST, SIDE_CENTER));
                        events.ScheduleEvent(EVENT_TALK_TRANSITION, 10000);
                        events.ScheduleEvent(EVENT_ANNOUNCE_EMERGE, 35000);
                        events.ScheduleEvent(EVENT_DETONATE_SONS_OF_FLAME, 45000);
                        break;
                    case EVENT_TALK_TRANSITION:
                        me->RemoveAurasDueToSpell(SPELL_BASE_VISUAL);
                        Talk(SAY_PHASE_TRANSITION);
                        if (events.IsInPhase(PHASE_SUBMERGE_2))
                            for (uint8 i = 0; i < 2; i++)
                                me->SummonCreature(NPC_LAVA_SCION, LavaScionPos[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
                        break;
                    case EVENT_ANNOUNCE_EMERGE:
                        Talk(SAY_ANNOUNCE_EMERGE);
                        break;
                    case EVENT_DETONATE_SONS_OF_FLAME:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_SON_OF_FLAME, 200.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                            if ((*itr)->isAlive())
                            {
                                (*itr)->AI()->DoCast(SPELL_SUPERNOVA);
                                (*itr)->Kill((*itr), false);
                            }
                        break;
                    }
                    case EVENT_EMERGE:
                        me->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(SPELL_SUBMERGE_AURA, me));
                        DoCast(me, SPELL_BASE_VISUAL, true);
                        me->PlayOneShotAnimKit(ANIM_KIT_RESURFACE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_ATTACK, 4000);
                        Talk(SAY_EMERGE);
                        if (events.IsInPhase(PHASE_SUBMERGE_1))
                        {
                            events.SetPhase(PHASE_2);
                            events.ScheduleEvent(EVENT_ENGULFING_FLAMES, 40000);
                            events.ScheduleEvent(EVENT_SULFURAS_SMASH, IsHeroic() ? 6000 : 16000);
                            events.ScheduleEvent(EVENT_MOLTEN_SEED, IsHeroic() ? 15000 : 22000);

                        }
                        else
                        {
                            events.SetPhase(PHASE_3);
                            events.ScheduleEvent(EVENT_ENGULFING_FLAMES, 30000);
                            events.ScheduleEvent(EVENT_SULFURAS_SMASH, 16000);
                            events.ScheduleEvent(EVENT_LIVING_METEOR, 45000);
                        }
                        break;
                    case EVENT_MOLTEN_SEED:
                        DoCast(me, SPELL_MOLTEN_SEED);
                        events.ScheduleEvent(EVENT_MOLTEN_SEED, 60000);
                        break;
                    case EVENT_ENGULFING_FLAMES:
                        _lastPlatformFlamed = urand (0, 2);
                        if (IsHeroic())
                        {
                            Talk(SAY_ANNOUNCE_WORLD_IN_FLAMES);
                            DoCast(me, SPELL_WOLRD_IN_FLAMES);
                        }
                        else
                        {
                            Talk(SAY_ANNOUNCE_ENGULFING_FLAMES);
                            CastEngulfingFlames();
                        }
                        events.ScheduleEvent(EVENT_ENGULFING_FLAMES, events.IsInPhase(PHASE_2) ? 60000 : 30000);
                        break;
                    case EVENT_LIVING_METEOR:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_LIVING_METEOR);
                        events.ScheduleEvent(EVENT_LIVING_METEOR, 45000);
                        break;
                    default:
                        break;
                }
            }
            if (Unit* victim = me->getVictim())
                if (victim->IsWithinMeleeRange(me))
                    DoMeleeAttackIfReady();
                else
                    DoSpellAttackIfReady(SPELL_MAGMA_STRIKE);
        }

        void CastSplittingBlow(uint8 side)
        {
            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
            DoCast(me, SPELL_SUBMERGE, true);
            _killedSons = 0;

            switch (side)
            {
                case SIDE_EAST:
                    if (Creature* splittingBlow = me->SummonCreature(NPC_SPLITTING_BLOW, SplittingTriggerEast, TEMPSUMMON_TIMED_DESPAWN, 20000))
                    {
                        me->SetFacingToObject(splittingBlow);
                        DoCast(me, SPELL_SPLITTING_BLOW_EAST);
                        for (uint8 i = 0; i < 8; i++)
                            me->SummonCreature(NPC_SON_OF_FLAME, SonsOfFlameEast[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    }
                    break;
                case SIDE_WEST:
                    if (Creature* splittingBlow = me->SummonCreature(NPC_SPLITTING_BLOW, SplittingTriggerWest, TEMPSUMMON_TIMED_DESPAWN, 20000))
                    {
                        me->SetFacingToObject(splittingBlow);
                        DoCast(me, SPELL_SPLITTING_BLOW_WEST);
                        for (uint8 i = 0; i < 8; i++)
                            me->SummonCreature(NPC_SON_OF_FLAME, SonsOfFlameWest[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    }
                    break;
                case SIDE_CENTER:
                    if (Creature* splittingBlow = me->SummonCreature(NPC_SPLITTING_BLOW, SplittingTriggerNorth, TEMPSUMMON_TIMED_DESPAWN, 20000))
                    {
                        me->SetFacingToObject(splittingBlow);
                        DoCast(me, SPELL_SPLITTING_BLOW_NORTH);
                        for (uint8 i = 0; i < 8; i++)
                            me->SummonCreature(NPC_SON_OF_FLAME, SonsOfFlameNorth[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    }
                    break;
                default:
                    break;
            }
        }

        void CastEngulfingFlames()
        {
            if (_lastPlatformFlamed == 2)
            {
                for (uint8 i = 0; i < 16; i++)
                    me->SummonCreature(NPC_ENGULFING_FLAME, EngulfingFlamesMelee[i], TEMPSUMMON_TIMED_DESPAWN, 5400);

                DoCast(me, SPELL_ENGULFING_FLAMES_VISUAL_MELEE, true);
                DoCast(me, SPELL_ENGULFING_FLAMES_MELEE);
                _lastPlatformFlamed = 0;
            }
            else if (_lastPlatformFlamed == 0)
            {
                for (uint8 i = 0; i < 17; i++)
                    me->SummonCreature(NPC_ENGULFING_FLAME, EngulfingFlamesCenter[i], TEMPSUMMON_TIMED_DESPAWN, 5400);

                DoCast(me, SPELL_ENGULFING_FLAMES_VISUAL_CENTER, true);
                DoCast(me, SPELL_ENGULFING_FLAMES_CENTER);
                _lastPlatformFlamed = 1;
            }
            else if (_lastPlatformFlamed == 1)
            {
                for (uint8 i = 0; i < 35; i++)
                    me->SummonCreature(NPC_ENGULFING_FLAME, EngulfingFlamesRange[i], TEMPSUMMON_TIMED_DESPAWN, 5400);

                DoCast(me, SPELL_ENGULFING_FLAMES_VISUAL_RANGE, true);
                DoCast(me, SPELL_ENGULFING_FLAMES_RANGE);
                _lastPlatformFlamed = 2;
            }
        }

        // For some reason Blizzard is using the opposite states for this door.
        void HandleDoor(bool close)
        {
            if (GameObject* door = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_RAGNAROS_DOOR)))
                if (close)
                    door->SetGoState(GO_STATE_READY);
                else
                    door->SetGoState(GO_STATE_ACTIVE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ragnaros_cataAI(creature);
    }
};

class npc_fl_magma_trap : public CreatureScript
{
    public:
        npc_fl_magma_trap() :  CreatureScript("npc_fl_magma_trap") { }

        struct npc_fl_magma_trapAI : public ScriptedAI
        {
            npc_fl_magma_trapAI(Creature* creature) : ScriptedAI(creature)
            {
                _exploded = false;
            }

            bool _exploded;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                events.ScheduleEvent(EVENT_PREPARE_TRAP, 1000);
                me->AddAura(SPELL_MAGMA_TRAP_VISUAL, me);
                me->SetReactState(REACT_PASSIVE);
                if (me->GetPositionZ() >= 56.0f)
                    me->GetMotionMaster()->MoveFall();
            }

            void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_MAGMA_TRAP_PERIODIC_TICK && !_exploded)
                {
                    DoCastAOE(SPELL_MAGMA_TRAP_ERUPTION);
                    me->RemoveAurasDueToSpell(SPELL_MAGMA_TRAP_VISUAL);
                    _exploded = true;
                    me->DespawnOrUnsummon(3000);
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PREPARE_TRAP:
                            DoCast(SPELL_MAGMA_TRAP_PERIODIC);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_magma_trapAI(creature);
        }
};

class npc_fl_sulfuras_smash : public CreatureScript
{
    public:
        npc_fl_sulfuras_smash() :  CreatureScript("npc_fl_sulfuras_smash") { }

        struct npc_fl_sulfuras_smashAI : public ScriptedAI
        {
            npc_fl_sulfuras_smashAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }
            InstanceScript* instance;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 100.0f))
                {
                    ragnaros->SetFacingToObject(me);
                    ragnaros->AI()->DoCast(ragnaros, SPELL_SUMMON_SULFURAS_SMASH_TARGET);
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_sulfuras_smashAI(creature);
        }
};

class npc_fl_sulfuras_smash_target : public CreatureScript
{
public:
    npc_fl_sulfuras_smash_target() : CreatureScript("npc_fl_sulfuras_smash_target") { }

    struct npc_fl_sulfuras_smash_targetAI : public ScriptedAI
    {
        npc_fl_sulfuras_smash_targetAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCast(me, SPELL_LAVA_POOL);
            if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 100.0f))
            {
                ragnaros->SetReactState(REACT_PASSIVE);
                ragnaros->AttackStop();
                ragnaros->SetFacingToObject(me);
                ragnaros->AI()->DoAction(ACTION_CAST_SULFURAS_SMASH);
                DoCast(me, SPELL_LAVA_WAVE_N, true);
                DoCast(me, SPELL_LAVA_WAVE_E, true);
                DoCast(me, SPELL_LAVA_WAVE_W, true);
            }
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_sulfuras_smash_targetAI(creature);
    }
};

class npc_fl_lava_wave : public CreatureScript
{
    public:
        npc_fl_lava_wave() :  CreatureScript("npc_fl_lava_wave") { }

        struct npc_fl_lava_waveAI : public ScriptedAI
        {
            npc_fl_lava_waveAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetSpeed(MOVE_RUN, 2.0f, true);
                me->SetFacingTo(summoner->GetAngle(me->GetPositionX(), me->GetPositionY()));
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_lava_waveAI(creature);
        }
};

class npc_fl_son_of_flame : public CreatureScript
{
    public:
        npc_fl_son_of_flame() :  CreatureScript("npc_fl_son_of_flame") { }

        struct npc_fl_son_of_flameAI : public ScriptedAI
        {
            npc_fl_son_of_flameAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* summoner)
            {
                DoCast(me, SPELL_PRE_VISUAL, true);
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0f, true))
                    ragnaros->AI()->DoAction(ACTION_SON_OF_FLAME_KILLED);
            }

            void DamageTaken(Unit* /*damager*/, uint32& damage)
            {
                if (me->HealthBelowPct(95))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 9);
                else if (me->HealthBelowPct(90))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 8);
                else if (me->HealthBelowPct(85))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 7);
                else if (me->HealthBelowPct(80))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 6);
                else if (me->HealthBelowPct(75))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 5);
                else if (me->HealthBelowPct(70))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 4);
                else if (me->HealthBelowPct(65))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 3);
                else if (me->HealthBelowPct(60))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 2);
                else if (me->HealthBelowPct(55))
                    me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 1);
                else if (me->HealthBelowPct(50))
                {
                    me->RemoveAurasDueToSpell(SPELL_BURNING_SPEED_STACKS);
                    me->RemoveAurasDueToSpell(SPELL_BURNING_SPEED);
                }
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_ACTIVATE_SON_OF_FLAME:
                        me->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(SPELL_PRE_VISUAL, me));
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_IMMUNE_TO_PC);
                        me->SetInCombatWithZone();
                        me->AddAura(SPELL_BURNING_SPEED, me);
                        me->AddAura(SPELL_BURNING_SPEED_STACKS, me);
                        me->SetAuraStack(SPELL_BURNING_SPEED_STACKS, me, 10);
                        me->PlayOneShotAnimKit(ANIM_KIT_UNK_1);

                        if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS_HAND_OF_RAGNAROS, 200.0f))
                            me->GetMotionMaster()->MovePoint(0, sulfuras->GetPositionX(), sulfuras->GetPositionY(), sulfuras->GetPositionZ(), false);
                        events.ScheduleEvent(EVENT_MOVE_HAMMER, 1000);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE_HAMMER:
                            if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS_HAND_OF_RAGNAROS, 200.0f))
                                if (me->IsWithinMeleeRange(sulfuras, 3.0f))
                                {
                                    DoCast(me, SPELL_SUPERNOVA, true);
                                    me->Kill(me, false);
                                }
                                else
                                    me->GetMotionMaster()->MovePoint(0, sulfuras->GetPositionX(), sulfuras->GetPositionY(), sulfuras->GetPositionZ(), false);

                            events.ScheduleEvent(EVENT_MOVE_HAMMER, 1000);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_son_of_flameAI(creature);
        }
};

class npc_fl_molten_elemental : public CreatureScript
{
    public:
        npc_fl_molten_elemental() :  CreatureScript("npc_fl_molten_elemental") { }

        struct npc_fl_molten_elementalAI : public ScriptedAI
        {
            npc_fl_molten_elementalAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCast(me, SPELL_INVISIBLE_PRE_VISUAL);
                events.ScheduleEvent(EVENT_PREPARE_ELEMENTAL, 2000);

                if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0f, true))
                    ragnaros->AI()->JustSummoned(me);

                if (Creature* seedCaster = me->FindNearestCreature(NPC_MOLTEN_SEED_CASTER, 100.0f, true))
                    seedCaster->CastSpell(me, SPELL_MOLTEN_SEED_MISSILE);
            }

            void JustDied(Unit* /*killer*/)
            {
                me->DespawnOrUnsummon(5000);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PREPARE_ELEMENTAL:
                            me->RemoveAurasDueToSpell(SPELL_INVISIBLE_PRE_VISUAL);
                            DoCast(me, SPELL_MOLTEN_SEED_VISUAL);
                            events.ScheduleEvent(EVENT_ACTIVATE, 10000);
                            break;
                        case EVENT_ACTIVATE:
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
                            me->SetReactState(REACT_AGGRESSIVE);
                            if (Unit* player = me->FindNearestPlayer(200.0f, true))
                                me->AI()->AttackStart(player);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_molten_elementalAI(creature);
        }
};

class npc_fl_lava_scion : public CreatureScript
{
    public:
        npc_fl_lava_scion() :  CreatureScript("npc_fl_lava_scion") { }

        struct npc_fl_lava_scionAI : public ScriptedAI
        {
            npc_fl_lava_scionAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (Unit* player = me->FindNearestPlayer(200.0f, true))
                    me->AI()->AttackStart(player);
            }

            void EnterCombat(Unit* /*victim*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_BLAZING_HEAT, 12000);
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

            void EnterEvadeMode()
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->DespawnOrUnsummon(1);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BLAZING_HEAT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_BLAZING_HEAT);
                            events.ScheduleEvent(EVENT_BLAZING_HEAT, 21000);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_lava_scionAI(creature);
        }
};

class npc_fl_blazing_heat : public CreatureScript
{
    public:
        npc_fl_blazing_heat() :  CreatureScript("npc_fl_blazing_heat") { }

        struct npc_fl_blazing_heatAI : public ScriptedAI
        {
            npc_fl_blazing_heatAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 150.0f, true))
                    ragnaros->AI()->JustSummoned(me);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_blazing_heatAI(creature);
        }
};

class npc_fl_living_meteor : public CreatureScript
{
    public:
        npc_fl_living_meteor() :  CreatureScript("npc_fl_living_meteor") { }

        struct npc_fl_living_meteorAI : public ScriptedAI
        {
            npc_fl_living_meteorAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            Unit* target;
            EventMap events;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void JustKilled(Unit* killed)
            {
                if (Unit* target = me->getVictim())
                    if (target == killed)
                    {
                        me->StopMoving();
                        if (target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            DoCast(target, SPELL_FIXATE);
                            events.ScheduleEvent(EVENT_STALK_PLAYER, 1);
                        }
                    }
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetInCombatWithZone();
                if (IsHeroic())
                    me->AddAura(SPELL_LIVING_METEOR_DAMAGE_REDUCTION, me);

                if (target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                    me->CastSpell(target, SPELL_FIXATE, false);

                events.ScheduleEvent(EVENT_STALK_PLAYER, 2500);    
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_LIVING_METEOR_DUMMY)
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        DoCast(me, SPELL_METEOR_IMPACT, true);
                        me->RemoveAllAuras();
                        me->StopMoving();

                        if (target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            DoCast(target, SPELL_FIXATE);
                            events.ScheduleEvent(EVENT_STALK_PLAYER, 2500);
                        }
                    }
            }

            void DamageTaken(Unit* attacker, uint32& /*damage*/)
            {
                if (me->HasAura(SPELL_COMBUSTIBLE))
                {
                    me->RemoveAllAuras();
                    me->StopMoving();
                    DoCast(attacker, SPELL_COMBUSTITION);

                    if (target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                    {
                        DoCast(target, SPELL_FIXATE);
                        events.ScheduleEvent(EVENT_STALK_PLAYER, 2500);
                    }

                    if (IsHeroic())
                        me->AddAura(SPELL_LIVING_METEOR_DAMAGE_REDUCTION, me);
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_STALK_PLAYER:
                            me->ClearUnitState(UNIT_STATE_CASTING);
                            me->GetMotionMaster()->MoveFollow(target, 0.0f, 0.0f);
                            events.ScheduleEvent(EVENT_MAKE_COMBUSTIBLE, 2500);
                            break;
                        case EVENT_MAKE_COMBUSTIBLE:
                            DoCast(me, SPELL_LIVING_METEOR_PERIODIC, true);
                            DoCast(me, SPELL_COMBUSTIBLE, true);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_living_meteorAI(creature);
        }
};

class npc_fl_archdruids : public CreatureScript
{
    public:
        npc_fl_archdruids() :  CreatureScript("npc_fl_archdruids") { }

        struct npc_fl_archdruidsAI : public ScriptedAI
        {
            npc_fl_archdruidsAI(Creature* creature) : ScriptedAI(creature)
            {
                casted = false;
            }

            bool casted;

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_CLOUDBURST_DUMMY)
                {
                    if (!casted)
                    {
                        if (target->GetEntry() == NPC_PLATFORM_TRIGGER)
                        {
                            if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0f, true))
                                if (Unit* player = ragnaros->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                    if (Unit* burst = player->FindNearestCreature(NPC_PLATFORM_TRIGGER, 200.0f, true))
                                        DoCast(burst, SPELL_CLOUDBURST_SUMMON);
                            casted = true;
                        }
                    }
                }
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_SCHEDULE_CLOUDBURST:
                        events.ScheduleEvent(EVENT_CLOUDBURST, 23000);
                        break;
                    case ACTION_SCHEDULE_ROOTS:
                        events.ScheduleEvent(EVENT_ENTRAPPING_ROOTS, 1);
                        break;
                    case ACTION_SCHEDULE_BREADTH:
                        events.ScheduleEvent(EVENT_BREADTH_OF_FROST, 6000);
                        break;
                    case ACTION_SCHEDULE_OUTRO:
                        me->CastStop();
                        events.CancelEvent(EVENT_CLOUDBURST);
                        events.CancelEvent(EVENT_ENTRAPPING_ROOTS);
                        events.CancelEvent(EVENT_BREADTH_OF_FROST);
                        if (me->GetEntry() == NPC_MALFURION)
                            events.ScheduleEvent(EVENT_TALK_MALFURION_1, 7000);
                        if (me->GetEntry() == NPC_CENARIUS)
                            events.ScheduleEvent(EVENT_TALK_CENARIUS_1, 10000);
                        if (me->GetEntry() == NPC_HAMUUL)
                            events.ScheduleEvent(EVENT_TALK_HAMUUL_1, 26000);

                        break;
                    default:
                        break;
                }
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (me->GetEntry() == NPC_CENARIUS)
                {
                    me->SetHover(true);
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetSpeed(MOVE_RUN, 10.0f, true);
                    me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                    me->GetMotionMaster()->MovePoint(1, CenariusPoint.GetPositionX(), CenariusPoint.GetPositionY(), CenariusPoint.GetPositionZ(), false);
                }
                else if (me->GetEntry() == NPC_MALFURION)
                {
                    me->SetHover(true);
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetSpeed(MOVE_RUN, 10.0f, true);
                    me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                    me->GetMotionMaster()->MovePoint(1, MalfurionPoint.GetPositionX(), MalfurionPoint.GetPositionY(), MalfurionPoint.GetPositionZ(), false);
                }
                else if (me->GetEntry() == NPC_HAMUUL)
                {
                    me->SetHover(true);
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetSpeed(MOVE_RUN, 10.0f, true);
                    me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                    me->GetMotionMaster()->MovePoint(1, HamuulPoint.GetPositionX(), HamuulPoint.GetPositionY(), HamuulPoint.GetPositionZ(), false);
                }
            }

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case 1:
                        me->SetHover(false);
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        if (me->GetEntry() == NPC_CENARIUS)
                        {
                            if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0f, true))
                                ragnaros->AI()->DoAction(ACTION_SUBMERGE);
                            events.ScheduleEvent(EVENT_SAY_PULL, 3700);
                            events.ScheduleEvent(EVENT_DRAW_RAGNAROS, 9600);
                        }
                        else if (me->GetEntry() == NPC_MALFURION)
                        {
                            DoCastAOE(SPELL_TRANSFORM_MALFURION);
                            events.ScheduleEvent(EVENT_TRANSFORM, 1000);
                            events.ScheduleEvent(EVENT_DRAW_RAGNAROS, 8300);
                        }
                        else if (me->GetEntry() == NPC_HAMUUL)
                        {
                            DoCastAOE(SPELL_TRANSFORM_HAMUUL);
                            events.ScheduleEvent(EVENT_TRANSFORM, 1000);
                            events.ScheduleEvent(EVENT_DRAW_RAGNAROS, 7100);
                        }
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SAY_PULL:
                            Talk(SAY_CENARIUS_1);
                            break;
                        case EVENT_DRAW_RAGNAROS:
                            if (me->GetEntry() == NPC_CENARIUS)
                                DoCastAOE(SPELL_CENARIUS_DRAW_FIRELORD);
                            if (me->GetEntry() == NPC_HAMUUL)
                                DoCastAOE(SPELL_HAMUL_DRAW_FIRELORD);
                            if (me->GetEntry() == NPC_MALFURION)
                            {
                                DoCastAOE(SPELL_MALFURION_DRAW_FIRELORD);
                                events.ScheduleEvent(EVENT_SAY_CAUGHT, 14500);
                            }
                            break;
                        case EVENT_TRANSFORM:
                            if (me->GetEntry() == NPC_MALFURION)
                                DoCastAOE(SPELL_TRANSFORM_MALFURION);
                            else if (me->GetEntry() == NPC_HAMUUL)
                                DoCastAOE(SPELL_TRANSFORM_HAMUUL);
                            break;
                        case EVENT_SAY_CAUGHT:
                            Talk(SAY_MALFURION_1);
                            break;
                        case EVENT_CLOUDBURST:
                            casted = false;
                            DoCastAOE(SPELL_CLOUDBURST_DUMMY); 
                            break;
                        case EVENT_ENTRAPPING_ROOTS:
                            if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0f, true))
                                if (Unit* player = ragnaros->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                    if (Unit* root = player->FindNearestCreature(NPC_PLATFORM_TRIGGER, 200.0f, true))
                                        if (Creature* trap = me->SummonCreature(NPC_ENTRAPPING_ROOTS, root->GetPositionX(), root->GetPositionY(), root->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 120000))
                                            DoCast(trap, SPELL_ENTRAPPING_ROOTS_AURA_MISSILE);
                            break;
                        case EVENT_BREADTH_OF_FROST:
                            if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0f, true))
                                if (Unit* player = ragnaros->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                    if (Unit* root = player->FindNearestCreature(NPC_PLATFORM_TRIGGER, 200.0f, true))
                                        if (Creature* trap = me->SummonCreature(NPC_BREADTH_OF_FROST, root->GetPositionX(), root->GetPositionY(), root->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 120000))
                                            DoCast(trap, SPELL_BREADTH_OF_FROST_AURA);
                            break;
                        case EVENT_TALK_MALFURION_1:
                            Talk(SAY_MALFURION_OUTRO_1);
                            events.ScheduleEvent(EVENT_TALK_MALFURION_2, 5000);
                            break;
                        case EVENT_TALK_MALFURION_2:
                            Talk(SAY_MALFURION_OUTRO_2);
                            break;
                        case EVENT_TALK_CENARIUS_1:
                            Talk(SAY_CENARIUS_OUTRO_1);
                            events.ScheduleEvent(EVENT_TALK_CENARIUS_2, 6000);
                            events.ScheduleEvent(EVENT_TALK_CENARIUS_3, 28000);
                            break;
                        case EVENT_TALK_CENARIUS_2:
                            Talk(SAY_CENARIUS_OUTRO_2);
                            break;
                        case EVENT_TALK_CENARIUS_3:
                            Talk(SAY_CENARIUS_OUTRO_3);
                            break;
                        case EVENT_TALK_HAMUUL_1:
                            Talk(SAY_HAMUUL_OUTRO_1);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_archdruidsAI(creature);
        }
};

class npc_fl_dreadflame : public CreatureScript
{
    public:
        npc_fl_dreadflame() : CreatureScript("npc_fl_dreadflame") { }

        struct npc_fl_dreadflameAI : public ScriptedAI
        {
            npc_fl_dreadflameAI(Creature* creature) : ScriptedAI(creature)
            {
                casted = false;
            }

            EventMap events;
            bool casted;

            void InitializeAI()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_DISABLE_MOVE);
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (Creature* ragnaros = me->FindNearestCreature(BOSS_RAGNAROS, 200.0, false))
                {
                    if (ragnaros->isDead())
                        me->DespawnOrUnsummon(0);
                }
                else
                {
                    me->SetReactState(REACT_PASSIVE);
                    if (summoner->GetEntry() == BOSS_RAGNAROS)
                    {
                        me->setFaction(summoner->getFaction());
                        me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 10000);
                    }
                    else
                    {
                        events.ScheduleEvent(EVENT_CHECK_PLAYER, 500);
                        events.ScheduleEvent(EVENT_SPREAD_FLAME, 5000);
                        me->setFaction(summoner->getFaction());
                        DoCastAOE(SPELL_DREADFLAME_DAMAGE_AURA);
                    }
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_PLAYER:
                        {
                            std::list<Creature*> units;
                            GetCreatureListWithEntryInGrid(units, me, NPC_DREADFLAME_SPAWN, 0.1f);
                            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                if ((*itr)->GetGUID() != me->GetGUID())
                                    (*itr)->DespawnOrUnsummon(1);

                            if (Player* player = me->FindNearestPlayer(0.0f, true))
                            {
                                if (player->HasAura(SPELL_CLOUDBURST_PLAYER_AURA) && !casted)
                                {
                                    events.Reset();
                                    DoCastAOE(SPELL_CLOUDBURST_VISUAL_WATER);
                                    me->DespawnOrUnsummon(3000);
                                    casted = true;
                                }
                            }
                            events.ScheduleEvent(EVENT_CHECK_PLAYER, 500);
                            break;
                        }
                        case EVENT_SPREAD_FLAME:
                        {
                            switch (urand(0, 4))
                            {
                                case 0:
                                    me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX()+5, me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 10000);
                                    break;
                                case 1:
                                    me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX()-5, me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 10000);
                                    break;
                                case 2:
                                    me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX(), me->GetPositionY()+5, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 10000);
                                    break;
                                case 3:
                                    me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX(), me->GetPositionY()-5, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 10000);
                                    break;
                                case 4:
                                    break;
                                default:
                                    break;
                            }
                            events.ScheduleEvent(EVENT_SPREAD_FLAME, 5000);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_dreadflameAI(creature);
    }
};

class npc_fl_cloudburst : public CreatureScript
{
    public:
        npc_fl_cloudburst() : CreatureScript("npc_fl_cloudburst") { }

        struct npc_fl_cloudburstAI : public ScriptedAI
        {
            npc_fl_cloudburstAI(Creature* creature) : ScriptedAI(creature)
            {
                _playerCount = 0;
            }

            EventMap events;
            uint8 _playerCount;

            void IsSummonedBy(Unit* summoner)
            {
                me->AddAura(SPELL_CLOUDBURST_DUMMY_AURA, me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                events.ScheduleEvent(EVENT_CHECK_PLAYER, 500);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_PLAYER:
                            if (Player* player = me->FindNearestPlayer(1.0f, true))
                            {
                                if (me->HasAura(SPELL_CLOUDBURST_DUMMY_AURA))
                                {
                                    if (Is25ManRaid()) // 25 Player Mode: 3 Players can use a single cloudburst
                                    {
                                        if (_playerCount < 3)
                                        {
                                            player->AddAura(SPELL_CLOUDBURST_PLAYER_AURA, player);
                                            _playerCount++;
                                        }
                                        else
                                        {
                                            player->AddAura(SPELL_CLOUDBURST_PLAYER_AURA, player);
                                            me->DespawnOrUnsummon(100);
                                            events.Reset();
                                        }

                                    }
                                    else
                                    {
                                        player->AddAura(SPELL_CLOUDBURST_PLAYER_AURA, player);
                                        me->DespawnOrUnsummon(100);
                                        events.Reset();
                                    }
                                }
                            }
                            else
                                events.ScheduleEvent(EVENT_CHECK_PLAYER, 500);
                            break;
                        default:
                            break;
                    }
                }
            }

        };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_cloudburstAI(creature);
    }
};

class spell_fl_sulfuras_smash_aoe : public SpellScriptLoader
{
public:
    spell_fl_sulfuras_smash_aoe() : SpellScriptLoader("spell_fl_sulfuras_smash_aoe") { }

    class spell_fl_sulfuras_smash_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_sulfuras_smash_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_sulfuras_smash_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_sulfuras_smash_aoe_SpellScript();
    }
};

class spell_fl_sulfuras_smash : public SpellScriptLoader
{
public:
    spell_fl_sulfuras_smash() : SpellScriptLoader("spell_fl_sulfuras_smash") { }

    class spell_fl_sulfuras_smash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_sulfuras_smash_SpellScript);

        void HandleSulfurasSmash(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->RemoveAurasDueToSpell(SPELL_LAVA_POOL);
                target->CastSpell(target, SPELL_SCORCHED_GROUND, false);
            }
        }

        void HandleLavaWave(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->CastSpell(target, SPELL_LAVA_WAVE, true);
                target->GetMotionMaster()->MovePoint(0, target->GetPositionX() + cos(target->GetOrientation()) * 100,
                    target->GetPositionY() + sin(target->GetOrientation()) * 100, target->GetPositionZ(), false);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_sulfuras_smash_SpellScript::HandleSulfurasSmash, EFFECT_1, SPELL_EFFECT_DUMMY);
            OnEffectHitTarget += SpellEffectFn(spell_fl_sulfuras_smash_SpellScript::HandleLavaWave, EFFECT_2, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_sulfuras_smash_SpellScript();
    }
};

class spell_fl_splitting_blow : public SpellScriptLoader
{
public:
    spell_fl_splitting_blow() : SpellScriptLoader("spell_fl_splitting_blow") { }

    class spell_fl_splitting_blow_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_splitting_blow_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_0].BasePoints, true);
                target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_1].BasePoints, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_splitting_blow_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_splitting_blow_SpellScript();
    }
};

class spell_fl_invoke_sons : public SpellScriptLoader
{
public:
    spell_fl_invoke_sons() : SpellScriptLoader("spell_fl_invoke_sons") { }

    class spell_fl_invoke_sons_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_invoke_sons_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    caster->CastSpell(target, SPELL_INVOKE_SONS_MISSILE, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_invoke_sons_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_invoke_sons_SpellScript();
    }
};

class spell_fl_invoke_sons_triggered : public SpellScriptLoader
{
public:
    spell_fl_invoke_sons_triggered() : SpellScriptLoader("spell_fl_invoke_sons_triggered") { }

    class spell_fl_invoke_sons_triggered_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_invoke_sons_triggered_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Creature* son = GetHitCreature())
                son->AI()->DoAction(ACTION_ACTIVATE_SON_OF_FLAME);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_invoke_sons_triggered_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_invoke_sons_triggered_SpellScript();
    }
};

class spell_fl_lava_bolt : public SpellScriptLoader
{
public:
    spell_fl_lava_bolt() : SpellScriptLoader("spell_fl_lava_bolt") { }

    class spell_fl_lava_bolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_lava_bolt_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 10 : 4);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_lava_bolt_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_lava_bolt_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_lava_bolt_SpellScript();
    }
};

class spell_fl_submerge : public SpellScriptLoader
{
public:
    spell_fl_submerge() : SpellScriptLoader("spell_fl_submerge") { }

    class spell_fl_submerge_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_submerge_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Creature* ragnaros = GetHitCreature())
                ragnaros->AI()->DoAction(ACTION_SUBMERGE);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_submerge_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_submerge_SpellScript();
    }
};

class spell_fl_molten_seed_aoe : public SpellScriptLoader
{
public:
    spell_fl_molten_seed_aoe() : SpellScriptLoader("spell_fl_molten_seed_aoe") { }

    class spell_fl_molten_seed_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_molten_seed_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 20 : 10);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_molten_seed_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_molten_seed_aoe_SpellScript();
    }
};

class spell_fl_molten_inferno : public SpellScriptLoader
{
public:
    spell_fl_molten_inferno() : SpellScriptLoader("spell_fl_molten_inferno") { }

    class spell_fl_molten_inferno_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_molten_inferno_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            int32 damage = GetEffectValue();

            if (Unit* target = GetHitUnit())
            {
                float distance = GetCaster()->GetDistance2d(target->GetPositionX(), target->GetPositionY());
                SetHitDamage(damage / distance);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_molten_inferno_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_molten_inferno_SpellScript();
    }
};

class spell_fl_blazing_heat : public SpellScriptLoader
{
    public:
        spell_fl_blazing_heat() :  SpellScriptLoader("spell_fl_blazing_heat") { }

        class spell_fl_blazing_heat_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_fl_blazing_heat_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BLAZING_HEAT_AURA))
                    return false;
                return true;
            }

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_BLAZING_HEAT_SUMMON, false);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_fl_blazing_heat_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_fl_blazing_heat_AuraScript();
        }
};

class spell_fl_world_in_flames : public SpellScriptLoader
{
public:
    spell_fl_world_in_flames() : SpellScriptLoader("spell_fl_world_in_flames") { }

    class spell_fl_world_in_flames_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_world_in_flames_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Creature* caster = GetHitCreature())
                caster->AI()->DoAction(ACTION_CAST_ENGULFING_FLAMES);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_world_in_flames_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_world_in_flames_SpellScript();
    }
};

class spell_fl_engulfing_flames : public SpellScriptLoader
{
public:
    spell_fl_engulfing_flames() : SpellScriptLoader("spell_fl_engulfing_flames") { }

    class spell_fl_engulfing_flames_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_engulfing_flames_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(EngulfingFlamesCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_engulfing_flames_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_engulfing_flames_SpellScript();
    }
};

class spell_fl_lavalogged : public SpellScriptLoader
{
public:
    spell_fl_lavalogged() : SpellScriptLoader("spell_fl_lavalogged") { }

    class spell_fl_lavalogged_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_fl_lavalogged_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget()->ToUnit())
                target->AddAura(SPELL_LIVING_METEOR_INCREASE_SPEED, target);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_fl_lavalogged_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_fl_lavalogged_AuraScript();
    }
};

class spell_fl_empower_sulfuras : public SpellScriptLoader
{
    public:
        spell_fl_empower_sulfuras() : SpellScriptLoader("spell_fl_empower_sulfuras") { }

        class spell_fl_empower_sulfuras_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_fl_empower_sulfuras_AuraScript);

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                switch (urand(0, 2))
                {
                    case 0:
                    case 1:
                        break;
                    case 2:
                        GetCaster()->CastSpell(GetCaster(), SPELL_EMPOWER_SULFURAS_MISSILE);
                        break;
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_fl_empower_sulfuras_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_fl_empower_sulfuras_AuraScript();
        }
};

class spell_fl_breadth_of_frost : public SpellScriptLoader
{
public:
    spell_fl_breadth_of_frost() : SpellScriptLoader("spell_fl_breadth_of_frost") { }

    class spell_fl_breadth_of_frost_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_fl_breadth_of_frost_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                caster->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SUPERHEATED_TRIGGERED, true);
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                caster->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SUPERHEATED_TRIGGERED, false);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_fl_breadth_of_frost_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_fl_breadth_of_frost_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    class spell_fl_breadth_of_frost_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_breadth_of_frost_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->RemoveAurasDueToSpell(SPELL_SUPERHEATED_TRIGGERED);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_breadth_of_frost_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_breadth_of_frost_SpellScript();
    }

    AuraScript* GetAuraScript() const
    {
        return new spell_fl_breadth_of_frost_AuraScript();
    }
};

class spell_fl_breadth_of_frost_freeze : public SpellScriptLoader
{
public:
    spell_fl_breadth_of_frost_freeze() : SpellScriptLoader("spell_fl_breadth_of_frost_freeze") { }

    class spell_fl_breadth_of_frost_freeze_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_fl_breadth_of_frost_freeze_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* meteor = GetOwner()->ToUnit())
                if (Creature* trap = meteor->FindNearestCreature(NPC_BREADTH_OF_FROST, 1.0f, true))
                    trap->DespawnOrUnsummon(1);  
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_fl_breadth_of_frost_freeze_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_fl_breadth_of_frost_freeze_AuraScript();
    }
};

class spell_fl_entrapping_roots : public SpellScriptLoader
{
public:
    spell_fl_entrapping_roots() : SpellScriptLoader("spell_fl_entrapping_roots") { }

    class spell_fl_entrapping_roots_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_fl_entrapping_roots_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* ragnaros = GetOwner()->ToUnit())
                if (Creature* trap = ragnaros->FindNearestCreature(NPC_ENTRAPPING_ROOTS, 1.0f, true))
                    trap->DespawnOrUnsummon(1);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_fl_entrapping_roots_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_fl_entrapping_roots_AuraScript();
    }
};

class spell_fl_deluge : public SpellScriptLoader
{
public:
    spell_fl_deluge() : SpellScriptLoader("spell_fl_deluge") { }

    class spell_fl_deluge_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_fl_deluge_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SUPERHEATED_TRIGGERED, true);
                caster->ApplySpellImmune(0, IMMUNITY_ID, SPELL_DREADFLAME_DAMAGE, true);
            }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SUPERHEATED_TRIGGERED, false);
                caster->ApplySpellImmune(0, IMMUNITY_ID, SPELL_DREADFLAME_DAMAGE, false);
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_fl_deluge_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_fl_deluge_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_fl_deluge_AuraScript();
    }
};

void AddSC_boss_ragnaros_cata()
{
    new at_sulfuron_keep();
    new boss_ragnaros_cata();
    new npc_fl_magma_trap();
    new npc_fl_sulfuras_smash();
    new npc_fl_sulfuras_smash_target();
    new npc_fl_lava_wave();
    new npc_fl_son_of_flame();
    new npc_fl_molten_elemental();
    new npc_fl_lava_scion();
    new npc_fl_blazing_heat();
    new npc_fl_living_meteor();

    /* Rewrites required */
    new npc_fl_archdruids();
    new npc_fl_dreadflame();
    new npc_fl_cloudburst();

    new spell_fl_sulfuras_smash_aoe();
    new spell_fl_sulfuras_smash();
    new spell_fl_splitting_blow();
    new spell_fl_invoke_sons();
    new spell_fl_invoke_sons_triggered();
    new spell_fl_lava_bolt();
    new spell_fl_submerge();
    new spell_fl_molten_seed_aoe();
    new spell_fl_world_in_flames();
    new spell_fl_engulfing_flames();
    new spell_fl_blazing_heat();
    new spell_fl_lavalogged();

    /* Rewrites required */
    new spell_fl_empower_sulfuras();
    new spell_fl_breadth_of_frost();
    new spell_fl_breadth_of_frost_freeze();
    new spell_fl_entrapping_roots();
    new spell_fl_molten_inferno();
    new spell_fl_deluge();
}
