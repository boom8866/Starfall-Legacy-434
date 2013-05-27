
#ifndef ANTICHEAT_CONFIG_H
#define ANTICHEAT_CONFIG_H

#define ANTICHEAT_CHECK_PARAMETERS  2
#define ANTICHEAT_ACTION_PARAMETERS 2

enum AntiCheatCheck
{
    CHECK_NULL              = 0,
    CHECK_MOVEMENT          = 1,
    CHECK_SPELL             = 2,
    CHECK_QUEST             = 3,
    CHECK_TRANSPORT         = 4,
    CHECK_DAMAGE            = 5,
    CHECK_ITEM              = 6,
    CHECK_WARDEN            = 7,
    CHECK_MOVEMENT_SPEED        = 100 * CHECK_MOVEMENT + 1,
    CHECK_MOVEMENT_FLY          = 100 * CHECK_MOVEMENT + 2,
    CHECK_MOVEMENT_MOUNTAIN     = 100 * CHECK_MOVEMENT + 3,
    CHECK_MOVEMENT_WATERWALKING = 100 * CHECK_MOVEMENT + 4,
    CHECK_MOVEMENT_TP2PLANE     = 100 * CHECK_MOVEMENT + 5,
    CHECK_MOVEMENT_AIRJUMP      = 100 * CHECK_MOVEMENT + 6,
    CHECK_MOVEMENT_TELEPORT     = 100 * CHECK_MOVEMENT + 7,
    CHECK_MOVEMENT_FALL         = 100 * CHECK_MOVEMENT + 8,
    CHECK_MOVEMENT_ZAXIS        = 100 * CHECK_MOVEMENT + 9,
    CHECK_SPELL_VALID           = 100 * CHECK_SPELL + 1,
    CHECK_SPELL_ONDEATH         = 100 * CHECK_SPELL + 2,
    CHECK_SPELL_FAMILY          = 100 * CHECK_SPELL + 3,
    CHECK_SPELL_INBOOK          = 100 * CHECK_SPELL + 4,
    CHECK_DAMAGE_SPELL          = 100 * CHECK_DAMAGE + 1,
    CHECK_DAMAGE_MELEE          = 100 * CHECK_DAMAGE + 2,
    CHECK_ITEM_UPDATE           = 100 * CHECK_ITEM   + 1,
    CHECK_WARDEN_MEMORY         = 100 * CHECK_WARDEN + 1,
    CHECK_WARDEN_KEY            = 100 * CHECK_WARDEN + 2,
    CHECK_WARDEN_CHECKSUM       = 100 * CHECK_WARDEN + 3,
    CHECK_WARDEN_TIMEOUT        = 100 * CHECK_WARDEN + 4,
    CHECK_MAX
};

enum AntiCheatAction
{
    ANTICHEAT_ACTION_NULL             = 0,
    ANTICHEAT_ACTION_LOG              = 1,
    ANTICHEAT_ACTION_ANNOUNCE_GM      = 2,
    ANTICHEAT_ACTION_ANNOUNCE_ALL     = 3,
    ANTICHEAT_ACTION_KICK             = 4,
    ANTICHEAT_ACTION_BAN              = 5,
    ANTICHEAT_ACTION_SHEEP            = 6,
    ANTICHEAT_ACTION_STUN             = 7,
    ANTICHEAT_ACTION_SICKNESS         = 8,
    MAX_ANTICHEAT_ACTIONS
};

struct AntiCheatConfig
{
    AntiCheatConfig() : checkType(0), alarmsCount(0),disableOperation(false), messageNum(0)
    {
        memset(&actionType,      0, sizeof(actionType));
        memset(&actionParam,     0, sizeof(actionParam));
        memset(&checkParam,      0, sizeof(checkParam));
        memset(&checkFloatParam, 0, sizeof(checkFloatParam));
    }

    uint32 checkType;
    uint32 checkPeriod;
    uint32 alarmsCount;
    bool   disableOperation;
    uint32 messageNum;
    uint32 checkParam[ANTICHEAT_CHECK_PARAMETERS];
    float  checkFloatParam[ANTICHEAT_CHECK_PARAMETERS];
    uint32 actionType[ANTICHEAT_ACTION_PARAMETERS];
    uint32 actionParam[ANTICHEAT_ACTION_PARAMETERS];
    std::string description;
};

#endif
