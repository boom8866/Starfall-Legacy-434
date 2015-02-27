/*
 * Copyright (C) 2010 /dev/rsa for MaNGOS <http://getmangos.com/>
 * based on Xeross code
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Anticheat.h"
#include "Language.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "SpellMgr.h"
#include "SpellAuraDefines.h"
#include "WardenWin.h"
#include "WardenMac.h"
#include "World.h"
#include "CreatureAIImpl.h"
#include "Chat.h"

#define ANTICHEAT_DEFAULT_DELTA 2000

static AntiCheatCheckEntry AntiCheatCheckList[] =
{
    { true,  CHECK_NULL,                    &AntiCheat::CheckNull          },
    { true,  CHECK_MOVEMENT,                &AntiCheat::CheckMovement      },
    { true,  CHECK_SPELL,                   &AntiCheat::CheckSpell         },
    { true,  CHECK_QUEST,                   &AntiCheat::CheckQuest         },
    { true,  CHECK_TRANSPORT,               &AntiCheat::CheckOnTransport   },
    { true,  CHECK_DAMAGE,                  &AntiCheat::CheckDamage        },
    { true,  CHECK_ITEM,                    &AntiCheat::CheckItem          },
    { true,  CHECK_WARDEN,                  &AntiCheat::CheckWarden        },
    { true,  CHECK_MOVEMENT_SPEED,          &AntiCheat::CheckSpeed         },
    { true,  CHECK_MOVEMENT_FLY,            &AntiCheat::CheckFly           },
    { true,  CHECK_MOVEMENT_MOUNTAIN,       &AntiCheat::CheckMountain      },
    { true,  CHECK_MOVEMENT_WATERWALKING,   &AntiCheat::CheckWaterWalking  },
    { true,  CHECK_MOVEMENT_TP2PLANE,       &AntiCheat::CheckTp2Plane      },
    { true,  CHECK_MOVEMENT_AIRJUMP,        &AntiCheat::CheckAirJump       },
    { true,  CHECK_MOVEMENT_TELEPORT,       &AntiCheat::CheckTeleport      },
    { true,  CHECK_MOVEMENT_FALL,           &AntiCheat::CheckFall          },
    { true,  CHECK_MOVEMENT_ZAXIS,          &AntiCheat::CheckZAxis         },
    { true,  CHECK_DAMAGE_SPELL,            &AntiCheat::CheckSpellDamage   },
    { true,  CHECK_DAMAGE_MELEE,            &AntiCheat::CheckMeleeDamage   },
    { true,  CHECK_SPELL_VALID,             &AntiCheat::CheckSpellValid    },
    { true,  CHECK_SPELL_ONDEATH,           &AntiCheat::CheckSpellOndeath  },
    { true,  CHECK_SPELL_FAMILY,            &AntiCheat::CheckSpellFamily   },
    { true,  CHECK_SPELL_INBOOK,            &AntiCheat::CheckSpellInbook   },
    { true,  CHECK_ITEM_UPDATE,             &AntiCheat::CheckItemUpdate    },
    { false, CHECK_WARDEN_KEY,              &AntiCheat::CheckWardenKey     },
    { false, CHECK_WARDEN_CHECKSUM,         &AntiCheat::CheckWardenCheckSum},
    { false, CHECK_WARDEN_MEMORY,           &AntiCheat::CheckWardenMemory  },
    { false, CHECK_WARDEN_TIMEOUT,          &AntiCheat::CheckWardenTimeOut },
    { false, CHECK_MAX,                     NULL                           }
};

AntiCheat::AntiCheat(Player* player)
{
    m_player              = player;
    m_MovedLen            = 0.0f;
    m_isFall              = false;
    m_isActiveMover       = true;
    m_currentmovementInfo = NULL;
    m_currentMover        = player;
    m_currentspellID      = 0;
    m_currentOpcode       = NULL_OPCODE;
    m_currentConfig       = NULL;
    m_currentDelta        = 0.0f;
    m_currentDeltaZ       = 0.0f;
    m_lastfalltime        = 0;
    m_lastfallz           = 0.0f;
    m_immuneTime          = getMSTime();
    m_lastClientTime      = getMSTime();
    m_lastLiveState       = ALIVE;
    m_counters.clear();
    m_oldCheckTime.clear();
    m_lastalarmtime.clear();
    m_lastactiontime.clear();
    SetImmune(ANTICHEAT_DEFAULT_DELTA);
}

void AntiCheat::DeleteOldLogs()
{
    uint32 const days = sWorld->getIntConfig(CONFIG_ANTICHEAT_DELETE_LOGS);
    sLog->outInfo(LOG_FILTER_SERVER_LOADING, "Deleting Anticheat DB Logs older than %u Days", days);

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_ANTICHEAT_LOG);
    stmt->setUInt32(0, time(NULL) - (days * DAY));
    CharacterDatabase.Execute(stmt);
}

bool AntiCheat::CheckNull()
{
    sLog->outDebug(LOG_FILTER_ANTICHEAT, "AntiCheat: CheckNull called");
    return true;
}

AntiCheatCheckEntry* AntiCheat::_FindCheck(AntiCheatCheck checktype)
{
    for(uint16 i = 0; AntiCheatCheckList[i].checkType != CHECK_MAX; ++i)
        if (AntiCheatCheckList[i].checkType == checktype)
            return &AntiCheatCheckList[i];
    return NULL;
}

AntiCheatConfig const* AntiCheat::_FindConfig(AntiCheatCheck checkType)
{
    return sObjectMgr->GetAntiCheatConfig(checkType);
}

bool AntiCheat::_DoAntiCheatCheck(AntiCheatCheck checktype)
{
    m_currentConfig = _FindConfig(checktype);

    if (!m_currentConfig)
        return true;

    AntiCheatCheckEntry* _check = _FindCheck(checktype);
    if (!_check)
        return true;

    if (_check->active && CheckTimer(checktype) && CheckNeeded(checktype))
    {
        if (m_counters.find(checktype) == m_counters.end())
            m_counters[checktype] = 0;

        if (!(this->*(_check->Handler))() && !isImmune())
        {
            if (m_currentConfig->disableOperation)
                return false;

            ++m_counters[checktype];

            if (m_lastalarmtime.find(checktype) == m_lastalarmtime.end())
                m_lastalarmtime[checktype] = 0;

            m_lastalarmtime[checktype] = getMSTime();

            if (m_counters[checktype] >= m_currentConfig->alarmsCount)
            {
                DoAntiCheatAction(checktype);
                m_counters[checktype] = 0;
            }
        }
        else
        {
            if (getMSTimeDiff(m_lastalarmtime[checktype], getMSTime()) > 30
                || (m_currentConfig->checkParam[0] > 0 && m_currentConfig->alarmsCount > 1 && getMSTimeDiff(m_lastalarmtime[checktype],getMSTime()) > m_currentConfig->checkParam[0]))
            {
                m_counters[checktype] = 0;
            }
        }
        m_oldCheckTime[checktype] = getMSTime();
    }

    if (checktype < 100 && _check->active && CheckNeeded(checktype))
        for (uint16 i = 1; i < 99; ++i )
        {
            uint32 const subcheck = checktype * 100 + i;
            if (AntiCheatConfig const* config = _FindConfig(AntiCheatCheck(subcheck)))
            {
                if (!_DoAntiCheatCheck(AntiCheatCheck(subcheck)))
                    return false;
            }
            else
                return true;
        }

    return true;
}

bool AntiCheat::CheckTimer(AntiCheatCheck checkType)
{
    AntiCheatConfig const* config = _FindConfig(checkType);
    if (!config->checkPeriod)
        return true;

    uint32 const currentTime = getMSTime();

    if (m_oldCheckTime.find(checkType) == m_oldCheckTime.end())
        m_oldCheckTime[checkType] = currentTime;

    if (currentTime - m_oldCheckTime[checkType] >= config->checkPeriod)
        return true;

    return false;
}

void AntiCheat::DoAntiCheatAction(AntiCheatCheck checkType)
{
    AntiCheatConfig const* config = _FindConfig(checkType);
    if (!config)
        return;

    if (m_lastactiontime.find(checkType) == m_lastactiontime.end())
        m_lastactiontime.insert(std::make_pair(checkType, 0));

    if (getMSTime() - m_lastactiontime[checkType] >= 30000)
    {
        m_lastactiontime[checkType] = getMSTime();

        std::string name = GetPlayer()->GetName();

        for (int i=0; i < ANTICHEAT_ACTION_PARAMETERS; ++i )
        {
            switch (config->actionType[i])
            {
                case ANTICHEAT_ACTION_LOG:
                    sLog->outInfo(LOG_FILTER_ANTICHEAT, "[Anticheat] Account: %u Player: %s - Possible %s (ival: %u, fval: %f)",
                        GetPlayer()->GetSession()->GetAccountId(), name.c_str(), config->description.c_str(), m_currentCheaterData.intvalue, m_currentCheaterData.floatvalue);
                    break;
                case ANTICHEAT_ACTION_ANNOUNCE_GM:
                    sWorld->SendGMText(config->messageNum, name.c_str(), config->description.c_str());
                    break;
                case ANTICHEAT_ACTION_ANNOUNCE_ALL:
                    sWorld->SendWorldText(config->messageNum, name.c_str(), config->description.c_str());
                    break;
                case ANTICHEAT_ACTION_KICK:
                    GetPlayer()->GetSession()->KickPlayer();
                    break;
                case ANTICHEAT_ACTION_BAN:
                {
                    sWorld->BanAccount(BAN_CHARACTER, name.c_str(), TimeToTimestampStr(config->actionParam[i]),
                        std::string("Possible " + config->description).c_str(), "Devastation Anticheat");
                    break;
                }
                case ANTICHEAT_ACTION_SHEEP:
                {
                    if (Aura* aura = GetPlayer()->AddAura(RAND(28272, 118, 28271, 28272, 61025, 61721, 71319), GetPlayer()))
                        aura->SetDuration(config->actionParam[i]);
                    if (checkType == CHECK_MOVEMENT_FLY ||  GetPlayer()->HasAuraType(SPELL_AURA_FLY))
                        GetPlayer()->CastSpell(GetPlayer(), 55001, true);
                    break;
                }
                case ANTICHEAT_ACTION_STUN:
                {
                    if (Aura* aura = GetPlayer()->AddAura(13005, GetPlayer()))
                        aura->SetDuration(config->actionParam[i]);
                    break;
                }
                case ANTICHEAT_ACTION_SICKNESS:
                {
                    if (Aura* aura = GetPlayer()->AddAura(15007, GetPlayer()))
                        aura->SetDuration(config->actionParam[i]);
                    break;
                }
                case ANTICHEAT_ACTION_NULL:
                default:
                    break;
            }
        }

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_ANTICHEAT_LOG);

        stmt->setUInt32(0, GetPlayer()->GetGUIDLow());
        stmt->setUInt32(1, checkType);
        stmt->setUInt32(2, time(NULL));
        stmt->setUInt32(3, m_currentCheaterData.intvalue);
        stmt->setFloat (4, m_currentCheaterData.floatvalue);

        CharacterDatabase.Execute(stmt);
    }
}

bool AntiCheat::CheckNeeded(AntiCheatCheck checktype)
{
    if (!sWorld->getBoolConfig(CONFIG_ANTICHEAT_ENABLED) || !GetPlayer()->IsInWorld() || GetPlayer()->IsBeingTeleported()
        || GetPlayer()->GetSession()->GetSecurity() > int32(sWorld->getIntConfig(CONFIG_ANTICHEAT_GMLEVEL)) ||
            GetMover()->HasAuraType(SPELL_AURA_MOD_CONFUSE))
                return false;

    AntiCheatCheck checkMainType = (checktype >= 100) ? AntiCheatCheck(checktype / 100) : checktype;

    switch (checkMainType)
    {
        case CHECK_NULL:
            return false;
            break;
        case CHECK_MOVEMENT:
        {
            if (GetPlayer()->GetTransport()/* || GetPlayer()->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT)*/ || GetPlayer()->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED) ||
                GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST) || GetMover()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE ||
                GetPlayer()->isInFlight())	//delete GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST) after sur no kick without cheat
                return false;
            break;
        }
        case CHECK_SPELL:
            return false;
            break;
        case CHECK_QUEST:
            return false;
            break;
        case CHECK_TRANSPORT:
        {
            if (!isActiveMover())
                return false;
            break;
        }
        case CHECK_WARDEN:
            return false;
            break;
        case CHECK_DAMAGE:
        case CHECK_ITEM:
            return false;
            break;
        default:
            return false;
    }

    if (checktype < 100 )
        return true;

    switch (checktype)
    {
        case CHECK_MOVEMENT_SPEED:
            if (GetMover()->HasAura(56266))
                return false;
            break;
        case CHECK_MOVEMENT_FLY:
        case CHECK_MOVEMENT_ZAXIS:
            if (isCanFly() || !GetMover())
                return false;
            break;
        case CHECK_MOVEMENT_WATERWALKING:
            if (!m_currentmovementInfo->HasMovementFlag(MOVEMENTFLAG_WATERWALKING))
                return false;
            break;
        case CHECK_MOVEMENT_TP2PLANE:
            if (m_currentmovementInfo->HasMovementFlag(MovementFlags(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING)))
                return false;
            if (GetMover()->HasAura(60068) && GetMover()->GetBaseMap()->IsUnderWater(m_currentmovementInfo->pos.m_positionX, m_currentmovementInfo->pos.m_positionY, m_currentmovementInfo->pos.m_positionZ-5.0f))
                return false;
            break;
        case CHECK_MOVEMENT_AIRJUMP:
            return false;
            break;
        case CHECK_MOVEMENT_TELEPORT:
            if (!isActiveMover() || GetPlayer()->IsBeingTeleported())
                return false;
            break;
        case CHECK_MOVEMENT_FALL:
            if (isCanFly() || !isActiveMover())
                return false;
            break;
        case CHECK_MOVEMENT_MOUNTAIN:
            if (isCanFly() || !isActiveMover())
                return false;
            break;
        default:
            break;
    }

    return true;
}

bool AntiCheat::CheckMovement()
{
    if (GetPlayer()->m_mover != GetPlayer() && isActiveMover())
    {
        SetActiveMover(false);
        m_currentMover  = GetPlayer()->m_mover;
        m_MovedLen = 0.0f;
        SetImmune(ANTICHEAT_DEFAULT_DELTA);
    }
    else if (GetPlayer()->m_mover ==  GetPlayer() && !isActiveMover())
    {
        SetActiveMover(true);
        m_currentMover  = GetPlayer();
        m_MovedLen = 0.0f;
        SetImmune(ANTICHEAT_DEFAULT_DELTA);
    }

    if (GetPlayer()->IsBeingTeleported())
        SetImmune(ANTICHEAT_DEFAULT_DELTA);

    SetLastLiveState(GetPlayer()->getDeathState());

    float delta_x   = GetMover()->GetPositionX() - m_currentmovementInfo->pos.m_positionX;
    float delta_y   = GetMover()->GetPositionY() - m_currentmovementInfo->pos.m_positionY;
    m_currentDeltaZ = GetMover()->GetPositionZ() - m_currentmovementInfo->pos.m_positionX;
    m_currentDelta = sqrt(delta_x * delta_x + delta_y * delta_y);
    m_MovedLen += m_currentDelta;
    return true;
}

bool AntiCheat::CheckSpeed()
{
    float speedRate   = 1.0f;
    int   serverDelta = getMSTimeDiff(m_oldCheckTime[CHECK_MOVEMENT_SPEED],getMSTime());

    if (m_currentTimeSkipped > 0 && (float)m_currentTimeSkipped < serverDelta)
    {
        serverDelta += m_currentTimeSkipped;
        m_currentTimeSkipped = 0;
    }
    else if (m_currentTimeSkipped > 0 && (float)m_currentTimeSkipped > serverDelta)
    {
        m_currentTimeSkipped = 0;
        return true;
    }
    uint32 const clientTime = m_currentmovementInfo->time;
    int32 clientDelta = clientTime - m_lastClientTime;
    m_lastClientTime = clientTime;
    float delta_t = float(std::max(clientDelta,serverDelta));
    float moveSpeed = m_MovedLen / delta_t;

    m_MovedLen = 0.0f;
    std::string mode;

    if (m_currentmovementInfo->HasMovementFlag(MOVEMENTFLAG_FLYING))
    {
        speedRate = GetMover()->GetSpeed(MOVE_FLIGHT);
        mode = "MOVE_FLIGHT";
    }
    else if (m_currentmovementInfo->HasMovementFlag(MOVEMENTFLAG_SWIMMING))
    {
        speedRate = GetMover()->GetSpeed(MOVE_SWIM);
        mode = "MOVE_SWIM";
    }
    else if (m_currentmovementInfo->HasMovementFlag(MOVEMENTFLAG_WALKING))
    {
        speedRate = GetMover()->GetSpeed(MOVE_WALK);
        mode = "MOVE_WALK";
    }
    else
    {
        speedRate = GetMover()->GetSpeed(MOVE_RUN);
        mode = "MOVE_RUN";
    }

    if ( moveSpeed / speedRate <= m_currentConfig->checkFloatParam[0] )
        return true;

    m_currentCheaterData = CheaterData(moveSpeed);
    return false;
}

bool AntiCheat::CheckWaterWalking()
{
    if  (GetMover()->HasAuraType(SPELL_AURA_WATER_WALK)
        || GetMover()->HasAura(60068)
        || GetMover()->HasAura(61081)
        || GetMover()->HasAuraType(SPELL_AURA_GHOST))
        return true;

    m_currentCheaterData = CheaterData();
    return false;
}

bool AntiCheat::CheckTeleport()
{
    if (m_currentDelta < m_currentConfig->checkFloatParam[0])
        return true;

    m_currentCheaterData = CheaterData(m_currentDelta);
    return false;
}

bool AntiCheat::CheckMountain()
{
    if (m_currentmovementInfo->HasMovementFlag(MovementFlags(MOVEMENTFLAG_FLYING | MOVEMENTFLAG_SWIMMING)))
        return true;

    if ( m_currentDeltaZ > 0 )
        return true;

    int32 const serverDelta = getMSTimeDiff(m_oldCheckTime[CHECK_MOVEMENT_MOUNTAIN], getMSTime());
    float const zSpeed = - m_currentDeltaZ / serverDelta;
    float const tg_z = (m_currentDelta > 0.0f) ? (-m_currentDeltaZ / m_currentDelta) : -99999;

    if (tg_z < m_currentConfig->checkFloatParam[1] || zSpeed < m_currentConfig->checkFloatParam[0] )
        return true;

    m_currentCheaterData = CheaterData(uint32(tg_z), zSpeed);
    return false;
}

bool AntiCheat::CheckFall()
{
    if (!m_isFall)
    {
        m_lastfalltime = m_currentmovementInfo->fallTime;
        m_lastfallz    = m_currentmovementInfo->pos.m_positionZ;
        SetInFall(true);
    }
    else
    {
        if (m_lastfallz - m_currentmovementInfo->pos.m_positionZ >= 0.0f)
            SetInFall(false);
    }
    return true;
}

bool AntiCheat::CheckFly()
{
    if (GetMover()->GetBaseMap()->IsUnderWater(m_currentmovementInfo->pos.m_positionX, m_currentmovementInfo->pos.m_positionY, m_currentmovementInfo->pos.m_positionZ - 2.0f))
        return true;

    if (!m_currentmovementInfo->HasMovementFlag(MovementFlags(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING | MOVEMENTFLAG_ROOT)))
        return true;

    if (GetMover()->HasAuraType(SPELL_AURA_FEATHER_FALL))
        return true;

    float ground_z = GetMover()->GetMap()->GetHeight(GetPlayer()->GetPositionX(),GetPlayer()->GetPositionY(),MAX_HEIGHT);
    float floor_z  = GetMover()->GetMap()->GetHeight(GetPlayer()->GetPositionX(),GetPlayer()->GetPositionY(),GetPlayer()->GetPositionZ());
    float map_z    = ((floor_z <= (INVALID_HEIGHT+5.0f)) ? ground_z : floor_z);

    if (map_z + m_currentConfig->checkFloatParam[0] > GetPlayer()->GetPositionZ() && map_z > (INVALID_HEIGHT + m_currentConfig->checkFloatParam[0] + 5.0f))
        return true;

    if (m_currentDeltaZ > 0.0f)
        return true;

    m_currentCheaterData = CheaterData(uint32(map_z + m_currentConfig->checkFloatParam[0]), GetPlayer()->GetPositionZ());
    return false;
}

bool AntiCheat::CheckAirJump()
{
    /*
    if (m_currentOpcode != MSG_MOVE_JUMP)
        return true;
    if (!m_currentmovementInfo->HasMovementFlag(MOVEFLAG_FALLING) || !GetMover()->m_movementInfo.HasMovementFlag(MOVEFLAG_FALLING))
        return true;
    */

    float ground_z = GetMover()->GetMap()->GetHeight(GetMover()->GetPositionX(),GetMover()->GetPositionY(),MAX_HEIGHT);
    float floor_z = GetMover()->GetMap()->GetHeight(GetMover()->GetPositionX(),GetMover()->GetPositionY(),GetMover()->GetPositionZ());
    float map_z = ((floor_z <= (INVALID_HEIGHT+5.0f)) ? ground_z : floor_z);

    if  (!((map_z + m_currentConfig->checkFloatParam[0] + m_currentConfig->checkFloatParam[1] < GetPlayer()->GetPositionZ() &&
            (m_currentmovementInfo->GetMovementFlags() & (MOVEMENTFLAG_FALLING_FAR | MOVEMENTFLAG_PENDING_STOP)) == 0) ||
                (map_z + m_currentConfig->checkFloatParam[0] < GetMover()->GetPositionZ() && m_currentOpcode == MSG_MOVE_JUMP)))
                    return true;

    if (m_currentDeltaZ > 0.0f)
        return true;

    m_currentCheaterData = CheaterData(m_currentDeltaZ);
    return false;
}

bool AntiCheat::CheckTp2Plane()
{
    if (m_currentmovementInfo->pos.m_positionZ > m_currentConfig->checkFloatParam[0] || m_currentmovementInfo->pos.m_positionZ < -m_currentConfig->checkFloatParam[0])
        return true;

    if (GetMover()->HasAuraType(SPELL_AURA_GHOST))
        return true;

    float plane_z = 0.0f;

    plane_z = GetMover()->GetMap()->GetHeight(m_currentmovementInfo->pos.m_positionX, m_currentmovementInfo->pos.m_positionY, MAX_HEIGHT) - m_currentmovementInfo->pos.m_positionZ;
    plane_z = (plane_z < -500.0f) ? 0 : plane_z;
    if(plane_z < m_currentConfig->checkFloatParam[1] && plane_z > -m_currentConfig->checkFloatParam[1])
        return true;

    m_currentCheaterData = CheaterData(plane_z);
    return false;
}

bool AntiCheat::CheckZAxis()
{
    if (m_currentDeltaZ > 0.0f && fabs(GetPlayer()->GetPositionZ()) < MAX_HEIGHT)
        return true;

    float delta_x   = GetPlayer()->GetPositionX() - m_currentmovementInfo->pos.m_positionX;
    float delta_y   = GetPlayer()->GetPositionY() - m_currentmovementInfo->pos.m_positionY;

    if(fabs(delta_x) > m_currentConfig->checkFloatParam[0] || fabs(delta_y) > m_currentConfig->checkFloatParam[0])
        return true;

    float delta_z   = GetPlayer()->GetPositionZ() - m_currentmovementInfo->pos.m_positionZ;

    if (fabs(delta_z) < m_currentConfig->checkFloatParam[1] && fabs(GetPlayer()->GetPositionZ()) < MAX_HEIGHT)
        return true;

    m_currentCheaterData = CheaterData(fabs(delta_z), fabs(GetPlayer()->GetPositionZ()));
    return false;
}

bool AntiCheat::CheckOnTransport()
{
	if (GetMover()->HasAura(56266))
        return true;

    /*
    // transports size limited
    // (also received at zeppelin/lift leave by some reason with t_* as absolute in continent coordinates, can be safely skipped)
    if ( m_currentmovementInfo->GetTransportPos()->x < m_currentConfig->checkFloatParam[1] && 
        m_currentmovementInfo->GetTransportPos()->y < m_currentConfig->checkFloatParam[1] && 
        m_currentmovementInfo->GetTransportPos()->z < 2.0f * m_currentConfig->checkFloatParam[1])
        return true;
    */

    float const trans_rad = sqrt(m_currentmovementInfo->t_pos.m_positionX * m_currentmovementInfo->t_pos.m_positionX + m_currentmovementInfo->t_pos.m_positionY * m_currentmovementInfo->t_pos.m_positionY + m_currentmovementInfo->t_pos.m_positionZ * m_currentmovementInfo->t_pos.m_positionZ);

    if (trans_rad < m_currentConfig->checkFloatParam[0])
        return true;

    m_currentCheaterData = CheaterData(trans_rad);
    return false;
}

bool AntiCheat::CheckSpell()
{
    return true;
}

bool AntiCheat::CheckSpellValid()
{
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(m_currentspellID);
    if (!spellInfo ||
        !spellInfo->IsPassive() ||
        spellInfo->SpellFamilyName == SPELLFAMILY_GENERIC ||
        GetPlayer()->HasSpell(m_currentspellID))
        return true;

    m_currentCheaterData = CheaterData(m_currentspellID);
    return true;
}

bool AntiCheat::CheckSpellOndeath()
{
    if (GetPlayer()->getDeathState() == ALIVE)
        return true;

    m_currentCheaterData = CheaterData(m_currentspellID);
    return false;
}

bool AntiCheat::CheckSpellFamily()
{
    if (!m_currentspellID)
        return true;

    bool checkPassed = true;
    std::string mode = "";

    SkillLineAbilityMapBounds const& skill_bounds = sSpellMgr->GetSkillLineAbilityMapBounds(m_currentspellID);
    for(SkillLineAbilityMap::const_iterator _spell_idx = skill_bounds.first; _spell_idx != skill_bounds.second; ++_spell_idx)
    {
        SkillLineEntry const *pSkill = sSkillLineStore.LookupEntry(_spell_idx->second->skillId);

        if (!pSkill)
            continue;

        if (pSkill->id == 769)
        {
            checkPassed = false;
            mode = " it is GM spell!";
        }
    }

    if (checkPassed)
        return true;

    m_currentCheaterData = CheaterData(m_currentspellID);
    return false;
}

bool AntiCheat::CheckSpellInbook()
{
    // not have spell in spellbook or spell passive and not casted by client
    if (!GetPlayer()->GetUInt16Value(PLAYER_FIELD_BYTES2, 0) == 0 ||
         GetPlayer()->HasActiveSpell(m_currentspellID) ||
            m_currentspellID == 1843)
                return true;

    m_currentCheaterData = CheaterData(m_currentspellID);
    return false;
}

bool AntiCheat::CheckQuest()
{
    return true;
}

bool AntiCheat::CheckDamage()
{
    return true;
}

bool AntiCheat::CheckSpellDamage()
{
    if (!m_currentspellID)
        return true;

    if (m_currentDamage < m_currentConfig->checkParam[1])
        return true;

    m_currentCheaterData = CheaterData(m_currentDamage, float(m_currentspellID));
    return false;
}

bool AntiCheat::CheckMeleeDamage()
{
    if (m_currentspellID)
        return true;

    if (m_currentDamage < m_currentConfig->checkParam[1])
        return true;

    CheaterData(m_currentDamage);
    return false;
}

bool AntiCheat::isCanFly()
{
    if (GetMover()->HasAuraType(SPELL_AURA_FLY)
        || GetMover()->HasAuraType(SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED)
        || GetMover()->HasAuraType(SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED)
        || GetMover()->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED)
        || GetMover()->HasAuraType(SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS)
        || GetMover()->HasAuraType(SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS)
        || GetMover()->HasAuraType(SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK))
        return true;

    return false;
}

bool AntiCheat::isInFall()
{
    return m_isFall;
}

bool AntiCheat::isImmune()
{
    return m_immuneTime > getMSTime();
}

void AntiCheat::SetImmune(uint32 timeDelta)
{
    m_immuneTime = getMSTime() + timeDelta;
}

void AntiCheat::SetLastLiveState(DeathState state)
{
    if (state  != m_lastLiveState)
    {
        m_lastLiveState = state;
        SetImmune(ANTICHEAT_DEFAULT_DELTA);
    }
}

bool AntiCheat::CheckItem()
{
    return true;
}

bool AntiCheat::CheckItemUpdate()
{
    return (m_testitem && m_item && (m_item == m_testitem));
}

bool AntiCheat::CheckWarden()
{
    return true;
}

bool AntiCheat::CheckWardenCheckSum()
{
    return !m_wardenCheckResult;
}

bool AntiCheat::CheckWardenKey()
{
    return !m_wardenCheckResult;
}

bool AntiCheat::CheckWardenMemory()
{
    if (!m_wardenCheckResult)
        return true;

    std::string mode;

    switch (m_wardenCheck)
    {
        case MEM_CHECK:
            mode = "memory check";
            break;
        case PAGE_CHECK_A:
        case PAGE_CHECK_B:
            mode = "page check";
            break;
        case MPQ_CHECK:
            mode = "MPQ check";
            break;
        case LUA_STR_CHECK:
            mode = "LUA check";
            break;
        case DRIVER_CHECK:
            mode = "driver check";
            break;
        case TIMING_CHECK:
            mode = "timing check";
            break;
        case PROC_CHECK:
            mode = "proc check";
            break;
        case MODULE_CHECK:
            mode = "module check";
            break;
        default:
            mode = "unknown check";
            break;
    }

    m_currentCheaterData = CheaterData(m_wardenCheckNum);
    return false;
}

bool AntiCheat::CheckWardenTimeOut()
{
    return !m_wardenCheckResult;
}
