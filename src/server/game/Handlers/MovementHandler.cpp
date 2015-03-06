/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "Corpse.h"
#include "Player.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Transport.h"
#include "Battleground.h"
#include "WaypointMovementGenerator.h"
#include "InstanceSaveMgr.h"
#include "ObjectMgr.h"
#include "InstanceScript.h"
#include "MovementStructures.h"
#include "Vehicle.h"

#define MOVEMENT_PACKET_TIME_DELAY 0

void WorldSession::HandleMoveWorldportAckOpcode(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: got MSG_MOVE_WORLDPORT_ACK.");
    HandleMoveWorldportAckOpcode();
}

void WorldSession::HandleMoveWorldportAckOpcode()
{
    // ignore unexpected far teleports
    if (!GetPlayer()->IsBeingTeleportedFar())
        return;

    GetPlayer()->SetSemaphoreTeleportFar(false);

    // get the teleport destination
    WorldLocation const& loc = GetPlayer()->GetTeleportDest();

    // possible errors in the coordinate validity check
    if (!MapManager::IsValidMapCoord(loc))
    {
        LogoutPlayer(false);
        return;
    }

    // get the destination map entry, not the current one, this will fix homebind and reset greeting
    MapEntry const* mEntry = sMapStore.LookupEntry(loc.GetMapId());
    InstanceTemplate const* mInstance = sObjectMgr->GetInstanceTemplate(loc.GetMapId());

    // reset instance validity, except if going to an instance inside an instance
    if (GetPlayer()->m_InstanceValid == false && !mInstance)
        GetPlayer()->m_InstanceValid = true;

    Map* oldMap = GetPlayer()->GetMap();
    if (GetPlayer()->IsInWorld())
    {
        sLog->outError(LOG_FILTER_NETWORKIO, "Player (Name %s) is still in world when teleported from map %u to new map %u", GetPlayer()->GetName().c_str(), oldMap->GetId(), loc.GetMapId());
        oldMap->RemovePlayerFromMap(GetPlayer(), false);
    }

    // relocate the player to the teleport destination
    Map* newMap = sMapMgr->CreateMap(loc.GetMapId(), GetPlayer());
    // the CanEnter checks are done in TeleporTo but conditions may change
    // while the player is in transit, for example the map may get full
    if (!newMap || !newMap->CanEnter(GetPlayer()))
    {
        sLog->outError(LOG_FILTER_NETWORKIO, "Map %d could not be created for player %d, porting player to homebind", loc.GetMapId(), GetPlayer()->GetGUIDLow());
        GetPlayer()->TeleportTo(GetPlayer()->m_homebindMapId, GetPlayer()->m_homebindX, GetPlayer()->m_homebindY, GetPlayer()->m_homebindZ, GetPlayer()->GetOrientation());
        return;
    }
    else
        GetPlayer()->Relocate(&loc);

    GetPlayer()->ResetMap();
    GetPlayer()->SetMap(newMap);
    GetPlayer()->SendInitialPacketsBeforeAddToMap();

    if (!GetPlayer()->GetMap()->AddPlayerToMap(GetPlayer()))
    {
        sLog->outError(LOG_FILTER_NETWORKIO, "WORLD: failed to teleport player %s (%d) to map %d because of unknown reason!",
            GetPlayer()->GetName().c_str(), GetPlayer()->GetGUIDLow(), loc.GetMapId());
        GetPlayer()->ResetMap();
        GetPlayer()->SetMap(oldMap);
        GetPlayer()->TeleportTo(GetPlayer()->m_homebindMapId, GetPlayer()->m_homebindX, GetPlayer()->m_homebindY, GetPlayer()->m_homebindZ, GetPlayer()->GetOrientation());
        return;
    }

    // battleground state prepare (in case join to BG), at relogin/tele player not invited
    // only add to bg group and object, if the player was invited (else he entered through command)
    if (_player->InBattleground())
    {
        // cleanup setting if outdated
        if (!mEntry->IsBattlegroundOrArena())
        {
            // We're not in BG
            _player->SetBattlegroundId(0, BATTLEGROUND_TYPE_NONE);
            // reset destination bg team
            _player->SetBGTeam(0);
        }
        // join to bg case
        else if (Battleground* bg = _player->GetBattleground())
        {
            if (_player->IsInvitedForBattlegroundInstance(_player->GetBattlegroundId()))
                bg->AddPlayer(_player);
        }
    }

    GetPlayer()->SendInitialPacketsAfterAddToMap();

    // flight fast teleport case
    if (GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE)
    {
        if (!_player->InBattleground())
        {
            // short preparations to continue flight
            FlightPathMovementGenerator* flight = (FlightPathMovementGenerator*)(GetPlayer()->GetMotionMaster()->top());
            flight->Initialize(GetPlayer());
            return;
        }

        // battleground state prepare, stop flight
        GetPlayer()->GetMotionMaster()->MovementExpired();
        GetPlayer()->CleanupAfterTaxiFlight();
    }

    // resurrect character at enter into instance where his corpse exist after add to map
    Corpse* corpse = GetPlayer()->GetCorpse();
    if (corpse && corpse->GetType() != CORPSE_BONES && corpse->GetMapId() == GetPlayer()->GetMapId())
    {
        if (mEntry->IsDungeon())
        {
            GetPlayer()->ResurrectPlayer(0.5f, false);
            GetPlayer()->SpawnCorpseBones();
        }
    }

    bool allowMount = !mEntry->IsDungeon() || mEntry->IsBattlegroundOrArena();
    if (mInstance)
    {
        Difficulty diff = GetPlayer()->GetDifficulty(mEntry->IsRaid());
        if (MapDifficulty const* mapDiff = GetMapDifficultyData(mEntry->MapID, diff))
        {
            if (mapDiff->resetTime)
            {
                if (time_t timeReset = sInstanceSaveMgr->GetResetTimeFor(mEntry->MapID, diff))
                {
                    uint32 timeleft = uint32(timeReset - time(NULL));
                    GetPlayer()->SendInstanceResetWarning(mEntry->MapID, diff, timeleft);
                }
            }
        }
        allowMount = mInstance->AllowMount;
    }

    // mount allow check
    if (!allowMount)
        _player->RemoveAurasByType(SPELL_AURA_MOUNTED);

    // update zone immediately, otherwise leave channel will cause crash in mtmap
    uint32 newzone, newarea;
    GetPlayer()->GetZoneAndAreaId(newzone, newarea);
    GetPlayer()->UpdateZone(newzone, newarea);

    // honorless target
    if (GetPlayer()->pvpInfo.IsHostile)
        GetPlayer()->CastSpell(GetPlayer(), 2479, true);

    // in friendly area
    else if (GetPlayer()->IsPvP() && !GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
        GetPlayer()->UpdatePvP(false, false);

    // resummon pet
    GetPlayer()->ResummonTemporaryUnsummonedPet();

    //lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();

    MovementInfo movementInfo = GetPlayer()->m_movementInfo;
    ExtraMovementInfo extraMovementInfo;

    movementInfo.time = getMSTime();
    movementInfo.guid = GetPlayer()->GetGUID();

    extraMovementInfo.flySpeed = GetPlayer()->GetSpeed(MOVE_FLIGHT);
    extraMovementInfo.flyBackSpeed = GetPlayer()->GetSpeed(MOVE_FLIGHT_BACK);

    WorldPacket teleUpdate(MSG_MOVE_UPDATE_TELEPORT);
    WriteMovementInfo(teleUpdate);

    WorldPacket speedUpdate(MSG_MOVE_UPDATE_FLIGHT_SPEED);
    WriteMovementInfo(speedUpdate, &extraMovementInfo);

    packetBlock packets;
    packets.push_back(&teleUpdate);
    packets.push_back(&speedUpdate);

    WorldPacket data = BuildMultiplePackets(packets);

    GetPlayer()->SendMessageToSet(&data, true);

    GetPlayer()->SendMovementSetCanFly(GetPlayer()->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) ? true : false);
}

void WorldSession::HandleMoveTeleportAck(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "MSG_MOVE_TELEPORT_ACK");

    ObjectGuid guid;
    uint32 flags, time;
    recvPacket >> flags >> time;

    guid[5] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[0]);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Guid " UI64FMTD, uint64(guid));
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Flags %u, time %u", flags, time/IN_MILLISECONDS);

    Player* plMover = _player->m_mover->ToPlayer();

    if (!plMover || !plMover->IsBeingTeleportedNear())
        return;

    if (guid != plMover->GetGUID())
        return;

    plMover->SetSemaphoreTeleportNear(false);

    uint32 old_zone = plMover->GetZoneId();

    WorldLocation const& dest = plMover->GetTeleportDest();

    plMover->UpdatePosition(dest, true);

    uint32 newzone, newarea;
    plMover->GetZoneAndAreaId(newzone, newarea);
    plMover->UpdateZone(newzone, newarea);

    // new zone
    if (old_zone != newzone)
    {
        // honorless target
        if (plMover->pvpInfo.IsHostile)
            plMover->CastSpell(plMover, 2479, true);

        // in friendly area
        else if (plMover->IsPvP() && !plMover->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
            plMover->UpdatePvP(false, false);
    }

    // resummon pet
    GetPlayer()->ResummonTemporaryUnsummonedPet();

    //lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();
}

void WorldSession::HandleMovementOpcodes(WorldPacket& recvPacket)
{
    uint16 opcode = recvPacket.GetOpcode();

    Unit* mover = _player->m_mover;

    ASSERT(mover != NULL);                      // there must always be a mover

    Player* plrMover = mover->ToPlayer();

    // ignore, waiting processing in WorldSession::HandleMoveWorldportAckOpcode and WorldSession::HandleMoveTeleportAck
    if (plrMover && plrMover->IsBeingTeleported())
    {
        recvPacket.rfinish();                     // prevent warnings spam
        return;
    }

    /* extract packet */
    MovementInfo movementInfo;
    ExtraMovementInfo emi;
    ReadMovementInfo(recvPacket, &movementInfo, &emi);
    recvPacket.rfinish();

    // prevent tampered movement data
    if (movementInfo.guid != mover->GetGUID())
        return;

    if (!movementInfo.pos.IsPositionValid())
    {
        sLog->outError(LOG_FILTER_NETWORKIO, "HandleMovementOpcodes: Invalid Position");
        return;
    }

    /* handle special cases */
    if (movementInfo.t_guid)
    {
        // transports size limited
        // (also received at zeppelin leave by some reason with t_* as absolute in continent coordinates, can be safely skipped)
        if (movementInfo.t_pos.GetPositionX() > 50 || movementInfo.t_pos.GetPositionY() > 50 || movementInfo.t_pos.GetPositionZ() > 50)
            return;

        if (!Trinity::IsValidMapCoord(movementInfo.pos.GetPositionX() + movementInfo.t_pos.GetPositionX(), movementInfo.pos.GetPositionY() + movementInfo.t_pos.GetPositionY(),
            movementInfo.pos.GetPositionZ() + movementInfo.t_pos.GetPositionZ(), movementInfo.pos.GetOrientation() + movementInfo.t_pos.GetOrientation()))
            return;

        // if we boarded a transport, add us to it
        if (plrMover)
        {
            if (!plrMover->GetTransport())
            {
                // Anticheat Check
                GetPlayer()->GetAntiCheat().DoAntiCheatCheck(CHECK_TRANSPORT, movementInfo);

                // elevators also cause the client to send MOVEMENTFLAG_ONTRANSPORT - just dismount if the guid can be found in the transport list
                for (MapManager::TransportSet::const_iterator iter = sMapMgr->m_Transports.begin(); iter != sMapMgr->m_Transports.end(); ++iter)
                {
                    if ((*iter)->GetGUID() == movementInfo.t_guid)
                    {
                        plrMover->m_transport = *iter;
                        (*iter)->AddPassenger(plrMover);
                        break;
                    }
                }
            }
            else if (plrMover->GetTransport()->GetGUID() != movementInfo.t_guid)
            {
                bool foundNewTransport = false;
                plrMover->m_transport->RemovePassenger(plrMover);
                for (MapManager::TransportSet::const_iterator iter = sMapMgr->m_Transports.begin(); iter != sMapMgr->m_Transports.end(); ++iter)
                {
                    if ((*iter)->GetGUID() == movementInfo.t_guid)
                    {
                        foundNewTransport = true;
                        plrMover->m_transport = *iter;
                        (*iter)->AddPassenger(plrMover);
                        break;
                    }
                }

                if (!foundNewTransport)
                {
                    plrMover->m_transport = NULL;
                    movementInfo.t_pos.Relocate(0.0f, 0.0f, 0.0f, 0.0f);
                    movementInfo.t_time = 0;
                    movementInfo.t_seat = -1;
                }
            }
        }

        if (!mover->GetTransport() && !mover->GetVehicle())
        {
            GameObject* go = mover->GetMap()->GetGameObject(movementInfo.t_guid);
            if (!go || go->GetGoType() != GAMEOBJECT_TYPE_TRANSPORT)
                movementInfo.t_guid = 0;
        }
    }
    else if (plrMover && plrMover->GetTransport())                // if we were on a transport, leave
    {
        plrMover->m_transport->RemovePassenger(plrMover);
        plrMover->m_transport = NULL;
        movementInfo.t_pos.Relocate(0.0f, 0.0f, 0.0f, 0.0f);
        movementInfo.t_time = 0;
        movementInfo.t_seat = -1;
    }

    // fall damage generation (ignore in flight case that can be triggered also at lags in moment teleportation to another map).
    if (opcode == MSG_MOVE_FALL_LAND && plrMover && !plrMover->isInFlight())
        plrMover->HandleFall(movementInfo);

    // Anticheat Check
    GetPlayer()->GetAntiCheat().DoAntiCheatCheck(CHECK_MOVEMENT, movementInfo, Opcodes(opcode));

    if (GetPlayer()->GetUInt32Value(UNIT_NPC_EMOTESTATE))
    {
        EmotesEntry const* emote = sEmotesStore.LookupEntry(GetPlayer()->GetUInt32Value(UNIT_NPC_EMOTESTATE));
        if (!emote || !emote->IsMovementAllowed())
            GetPlayer()->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
    }

    if (plrMover && ((movementInfo.flags & MOVEMENTFLAG_SWIMMING) != 0) != plrMover->IsInWater())
    {
        // now client not include swimming flag in case jumping under water
        plrMover->SetInWater(!plrMover->IsInWater() || plrMover->GetBaseMap()->IsUnderWater(movementInfo.pos.GetPositionX(), movementInfo.pos.GetPositionY(), movementInfo.pos.GetPositionZ()));
    }

    movementInfo.time = movementInfo.time + m_clientTimeDelay + MOVEMENT_PACKET_TIME_DELAY;
    movementInfo.guid = mover->GetGUID();
    mover->m_movementInfo = movementInfo;

    //Package defined here
    WorldPacket data(SMSG_PLAYER_MOVE, recvPacket.size());
    // Some vehicles allow the passenger to turn by himself
    if (Vehicle* vehicle = mover->GetVehicle())
    {
        if (VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(mover))
        {
            if (seat->m_flags & VEHICLE_SEAT_FLAG_ALLOW_TURNING)
            {
                if (movementInfo.pos.GetOrientation() != mover->GetOrientation())
                {
                    mover->SetOrientation(movementInfo.pos.GetOrientation());
                    mover->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_TURNING);
                }
            }
        }
        return;
    }

    mover->UpdatePosition(movementInfo.pos);

    if (plrMover)                                            // nothing is charmed, or player charmed
    {
        plrMover->UpdateFallInformationIfNeed(movementInfo, opcode);

        // Quest: Rocket Rescue
        if (plrMover->HasUnitMovementFlag(MOVEMENTFLAG_FALLING))
        {
            if (Aura* rocket = plrMover->GetAura(75730))
            {
                rocket->Remove(AURA_REMOVE_BY_DEFAULT);
                plrMover->AddAura(85883, plrMover);   // Parachute
            }
        }

        AreaTableEntry const* zone = GetAreaEntryByAreaID(plrMover->GetAreaId());
        float depth = zone ? zone->MaxDepth : -500.0f;

        // Exeption for Throne of the four Winds
        if (zone && zone->ID == 5638)
            depth = 180.f;

        class teleportToEntrance : public BasicEvent
        {
        public:
            explicit teleportToEntrance(Player* player) : player(player)
            {
            }

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                player->RemoveAurasDueToSpell(85734);
                player->TeleportTo(657, -358.21f, -7.45f, 632.78f, 3.93f);
                player->SetStandState(UNIT_STAND_STATE_STAND);
                return true;
            }

        private:
            Player* player;
        };

        switch (plrMover->GetMapId())
        {
            case 657:  // The Vortex Pinnacle
            {
                if (movementInfo.pos.GetPositionZ() < 575.0f && !plrMover->isGameMaster())
                {
                    plrMover->AddAura(85734, plrMover);
                    plrMover->GetMotionMaster()->MoveJump(plrMover->GetPositionX(), plrMover->GetPositionY(), 640.0f, 15.0f, 22.5f, 0);
                    plrMover->HandleEmoteCommand(EMOTE_STATE_WHIRLWIND);
                    plrMover->m_Events.AddEvent(new teleportToEntrance(plrMover), (plrMover)->m_Events.CalculateTime(6000));
                }
                break;
            }
            default:
                break;
        }

        if (movementInfo.pos.GetPositionZ() < depth)
        {
            if (!(plrMover->GetBattleground() && plrMover->GetBattleground()->HandlePlayerUnderMap(_player)))
            {
                // NOTE: this is actually called many times while falling
                // even after the player has been teleported away
                // TODO: discard movement packets after the player is rooted
                if (plrMover->isAlive())
                {
                    // Throne of the Four Winds: Back Teleport
                    if (plrMover->GetMapId() == 754 && plrMover->GetHealthPct() > 50.f && !plrMover->isGameMaster())
                        if (InstanceScript* instance = plrMover->GetInstanceScript())
                        {
                            instance->SetData64(8 /*DATA_PLAYER_UNDER_MAP*/, plrMover->GetGUID());
                            //NOTE Send befor we get outa here
                            WriteMovementInfo(data, &emi);
                            mover->SendMessageToSet(&data, _player);
                            return;
                        }

                    plrMover->EnvironmentalDamage(DAMAGE_FALL_TO_VOID, GetPlayer()->GetMaxHealth());
                    // player can be alive if GM/etc
                    // change the death state to CORPSE to prevent the death timer from
                    // starting in the next player update
                    if (!plrMover->isAlive())
                        plrMover->KillPlayer();
                }
            }
        }
    }

    //NOTE Here we send normally our datas to da set
    WriteMovementInfo(data, &emi);
    mover->SendMessageToSet(&data, _player);
}

void WorldSession::HandleForceSpeedChangeAck(WorldPacket &recvData)
{
    uint32 opcode = recvData.GetOpcode();

    /* extract packet */
    uint64 guid;
    uint32 unk1;
    float  newspeed;

    recvData.readPackGUID(guid);

    // now can skip not our packet
    if (_player->GetGUID() != guid)
    {
        recvData.rfinish();                   // prevent warnings spam
        return;
    }

    // continue parse packet

    recvData >> unk1;                                      // counter or moveEvent

    MovementInfo movementInfo;
    movementInfo.guid = guid;
    ReadMovementInfo(recvData, &movementInfo);

    recvData >> newspeed;
    /*----------------*/

    // client ACK send one packet for mounted/run case and need skip all except last from its
    // in other cases anti-cheat check can be fail in false case
    UnitMoveType move_type;
    UnitMoveType force_move_type;

    static char const* move_type_name[MAX_MOVE_TYPE] = {  "Walk", "Run", "RunBack", "Swim", "SwimBack", "TurnRate", "Flight", "FlightBack", "PitchRate" };

    switch (opcode)
    {
        
        case CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK:
            move_type = MOVE_WALK;
            force_move_type = MOVE_WALK;
            break;
        case CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK:
            move_type = MOVE_RUN;
            force_move_type = MOVE_RUN;
            break;
        case CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK: 
            move_type = MOVE_RUN_BACK;
            force_move_type = MOVE_RUN_BACK;
            break;
        case CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK:
            move_type = MOVE_SWIM;
            force_move_type = MOVE_SWIM;
            break;
        case CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK:
            move_type = MOVE_SWIM_BACK;
            force_move_type = MOVE_SWIM_BACK;
            break;
        case CMSG_MOVE_FORCE_TURN_RATE_CHANGE_ACK:
            move_type = MOVE_TURN_RATE;
            force_move_type = MOVE_TURN_RATE;
            break;
        case CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK:
            move_type = MOVE_FLIGHT;
            force_move_type = MOVE_FLIGHT;
            break;
        case CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK:
            move_type = MOVE_FLIGHT_BACK;
            force_move_type = MOVE_FLIGHT_BACK;
            break;
        case CMSG_MOVE_FORCE_PITCH_RATE_CHANGE_ACK:
            move_type = MOVE_PITCH_RATE;
            force_move_type = MOVE_PITCH_RATE;
            break;
        
        default:
            sLog->outError(LOG_FILTER_NETWORKIO, "WorldSession::HandleForceSpeedChangeAck: Unknown move type opcode: %u", opcode);
            return;
    }

    sLog->outError(LOG_FILTER_NETWORKIO, "WorldSession::HandleForceSpeedChangeAck: Unknown move type opcode: %u", opcode);
    return;

    // skip all forced speed changes except last and unexpected
    // in run/mounted case used one ACK and it must be skipped.m_forced_speed_changes[MOVE_RUN} store both.
    if (_player->m_forced_speed_changes[force_move_type] > 0)
    {
        --_player->m_forced_speed_changes[force_move_type];
        if (_player->m_forced_speed_changes[force_move_type] > 0)
            return;
    }

    if (!_player->GetTransport() && fabs(_player->GetSpeed(move_type) - newspeed) > 0.01f)
    {
        if (_player->GetSpeed(move_type) > newspeed)         // must be greater - just correct
        {
            sLog->outError(LOG_FILTER_NETWORKIO, "%sSpeedChange player %s is NOT correct (must be %f instead %f), force set to correct value",
                move_type_name[move_type], _player->GetName().c_str(), _player->GetSpeed(move_type), newspeed);
            _player->SetSpeed(move_type, _player->GetSpeedRate(move_type), true);
        }
        else                                                // must be lesser - cheating
        {
            sLog->outDebug(LOG_FILTER_GENERAL, "Player %s from account id %u kicked for incorrect speed (must be %f instead %f)",
                _player->GetName().c_str(), _player->GetSession()->GetAccountId(), _player->GetSpeed(move_type), newspeed);
            _player->GetSession()->KickPlayer();
        }
    }
}

void WorldSession::HandleSetActiveMoverOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd CMSG_SET_ACTIVE_MOVER");

    ObjectGuid guid;

    guid[7] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[7]);

    if (GetPlayer()->IsInWorld())
    {
        if (_player->m_mover->GetGUID() != guid)
            sLog->outError(LOG_FILTER_NETWORKIO, "HandleSetActiveMoverOpcode: incorrect mover guid: mover is " UI64FMTD " (%s - Entry: %u) and should be " UI64FMTD, uint64(guid), GetLogNameForGuid(guid), GUID_ENPART(guid), _player->m_mover->GetGUID());
    }
}

void WorldSession::HandleMoveNotActiveMover(WorldPacket &recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd CMSG_MOVE_NOT_ACTIVE_MOVER");

    MovementInfo mi;
    ReadMovementInfo(recvData, &mi);

    _player->m_movementInfo = mi;
}

void WorldSession::HandleMountSpecialAnimOpcode(WorldPacket& /*recvData*/)
{
    WorldPacket data(SMSG_MOUNTSPECIAL_ANIM, 8);
    data << uint64(GetPlayer()->GetGUID());

    GetPlayer()->SendMessageToSet(&data, false);
}

void WorldSession::HandleMoveSetCanFlyAckOpcode(WorldPacket& recvData)
{
    // fly mode on/off
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_MOVE_SET_CAN_FLY_ACK");

    MovementInfo movementInfo;
    ExtraMovementInfo extraMovementInfo;
    ReadMovementInfo(recvData, &movementInfo, &extraMovementInfo);

    _player->m_mover->m_movementInfo.flags = movementInfo.GetMovementFlags();
    SendSplineFlags(MOVEMENTFLAG_FLYING);
}

void WorldSession::HandleMoveKnockBackAck(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_KNOCK_BACK_ACK");

    MovementInfo movementInfo;
    ReadMovementInfo(recvData, &movementInfo);

    if (_player->m_mover->GetGUID() != movementInfo.guid)
        return;

    _player->m_movementInfo = movementInfo;

    WorldPacket data(SMSG_MOVE_UPDATE_KNOCK_BACK, 66);
    data.appendPackGUID(movementInfo.guid);
    _player->BuildMovementPacket(&data);

    // knockback specific info
    data << movementInfo.j_sinAngle;
    data << movementInfo.j_cosAngle;
    data << movementInfo.j_xyspeed;
    data << movementInfo.j_zspeed;

    _player->SendMessageToSet(&data, false);
}

void WorldSession::HandleMoveHoverAck(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_HOVER_ACK");

    uint64 guid;                                            // guid - unused
    recvData.readPackGUID(guid);

    recvData.read_skip<uint32>();                          // unk

    MovementInfo movementInfo;
    ReadMovementInfo(recvData, &movementInfo);

    recvData.read_skip<uint32>();                          // unk2
}

void WorldSession::HandleMoveWaterWalkAck(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_WATER_WALK_ACK");

    uint64 guid;                                            // guid - unused
    recvData.readPackGUID(guid);

    recvData.read_skip<uint32>();                          // unk

    MovementInfo movementInfo;
    ReadMovementInfo(recvData, &movementInfo);

    recvData.read_skip<uint32>();                          // unk2
}

void WorldSession::HandleSummonResponseOpcode(WorldPacket& recvData)
{
    if (!_player->isAlive() || _player->isInCombat())
        return;

    uint64 summonerGuid;
    bool agree;
    recvData >> summonerGuid;
    recvData >> agree;

    _player->SummonIfPossible(agree);
}

void WorldSession::SendSplineFlags(uint32 flag)
{
    bool hasFlag = GetPlayer()->HasUnitMovementFlag(flag);
    ObjectGuid playerGuid = GetPlayer()->GetGUID();

    switch(flag)
    {
        case MOVEMENTFLAG_CAN_FLY:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_FLYING);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[5]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[2]);
                SendPacket(&data);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_UNSET_FLYING);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[6]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[0]);
                SendPacket(&data);
            }
            break;
        }
        case MOVEMENTFLAG_HOVER:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_HOVER);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[5]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[6]);
                SendPacket(&data);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_UNSET_HOVER);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[2]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[1]);
                SendPacket(&data);
            }
            break;
        }

    }
}
