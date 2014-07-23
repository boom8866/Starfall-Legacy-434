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

#ifndef _MOVEMENT_STRUCTURES_H
#define _MOVEMENT_STRUCTURES_H

enum MovementStatusElements
{
    MSEHasGuidByte0 = 0,
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasMovementFlags,
    MSEHasMovementFlags2,
    MSEHasTimestamp,
    MSEHasOrientation,
    MSEHasTransportData,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte7,
    MSEHasTransportTime2,
    MSEHasTransportTime3,
    MSEHasPitch,
    MSEHasFallData,
    MSEHasFallDirection,
    MSEHasSplineElevation,
    MSEHasSpline,

    MSEGuidByte0,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSETimestamp,
    MSEPositionX,
    MSEPositionY,
    MSEPositionZ,
    MSEOrientation,
    MSETransportGuidByte0,
    MSETransportGuidByte1,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportGuidByte4,
    MSETransportGuidByte5,
    MSETransportGuidByte6,
    MSETransportGuidByte7,
    MSETransportPositionX,
    MSETransportPositionY,
    MSETransportPositionZ,
    MSETransportOrientation,
    MSETransportSeat,
    MSETransportTime,
    MSETransportTime2,
    MSETransportTime3,
    MSEPitch,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSESplineElevation,

    // Some more specific fields that are not present in all the opcodes
    MSEUnknownDword,
    MSEUnknownFloat,

    MSEFlyingSpeed,

    // Special
    MSEZeroBit, // writes bit value 1 or skips read bit
    MSEOneBit,  // writes bit value 0 or skips read bit
    MSEEnd,     // marks end of parsing
    MSE_COUNT
};

extern MovementStatusElements PlayerMoveSequence[];
extern MovementStatusElements MovementFallLandSequence[];
extern MovementStatusElements MovementHeartBeatSequence[];
extern MovementStatusElements MovementJumpSequence[];
extern MovementStatusElements MovementSetFacingSequence[];
extern MovementStatusElements MovementSetPitchSequence[];
extern MovementStatusElements MovementStartBackwardSequence[];
extern MovementStatusElements MovementStartForwardSequence[];
extern MovementStatusElements MovementStartStrafeLeftSequence[];
extern MovementStatusElements MovementStartStrafeRightSequence[];
extern MovementStatusElements MovementStartTurnLeftSequence[];
extern MovementStatusElements MovementStartTurnRightSequence[];
extern MovementStatusElements MovementStopSequence[];
extern MovementStatusElements MovementStopStrafeSequence[];
extern MovementStatusElements MovementStopTurnSequence[];
extern MovementStatusElements MovementStartAscendSequence[];
extern MovementStatusElements MovementStartDescendSequence[];
extern MovementStatusElements MovementStartSwimSequence[];
extern MovementStatusElements MovementStopSwimSequence[];
extern MovementStatusElements MovementStopAscendSequence[];
extern MovementStatusElements MovementStopPitchSequence[];
extern MovementStatusElements MovementStartPitchDownSequence[];
extern MovementStatusElements MovementStartPitchUpSequence[];
extern MovementStatusElements MoveChngTransport[];
extern MovementStatusElements MoveSplineDone[];
extern MovementStatusElements MoveNotActiveMover[];
extern MovementStatusElements DismissControlledVehicle[];
extern MovementStatusElements MoveUpdateTeleport[];
extern MovementStatusElements MoveSetCanFly[];
extern MovementStatusElements MoveSetCanFlyAck[];
extern MovementStatusElements UpdateFlightSpeed[];
extern MovementStatusElements CastSpellEmbeddedMovement[];

inline MovementStatusElements* GetMovementStatusElementsSequence(Opcodes opcode)
{
    switch (opcode)
    {
        case MSG_MOVE_FALL_LAND:
            return MovementFallLandSequence;
        case MSG_MOVE_HEARTBEAT:
            return MovementHeartBeatSequence;
        case MSG_MOVE_JUMP:
            return MovementJumpSequence;
        case MSG_MOVE_SET_FACING:
            return MovementSetFacingSequence;
        case MSG_MOVE_SET_PITCH:
            return MovementSetPitchSequence;
        case MSG_MOVE_START_ASCEND:
            return MovementStartAscendSequence;
        case MSG_MOVE_START_BACKWARD:
            return MovementStartBackwardSequence;
        case MSG_MOVE_START_DESCEND:
            return MovementStartDescendSequence;
        case MSG_MOVE_START_FORWARD:
            return MovementStartForwardSequence;
        case MSG_MOVE_START_PITCH_DOWN:
            return MovementStartPitchDownSequence;
        case MSG_MOVE_START_PITCH_UP:
            return MovementStartPitchUpSequence;
        case MSG_MOVE_START_STRAFE_LEFT:
            return MovementStartStrafeLeftSequence;
        case MSG_MOVE_START_STRAFE_RIGHT:
            return MovementStartStrafeRightSequence;
        case MSG_MOVE_START_SWIM:
            return MovementStartSwimSequence;
        case MSG_MOVE_START_TURN_LEFT:
            return MovementStartTurnLeftSequence;
        case MSG_MOVE_START_TURN_RIGHT:
            return MovementStartTurnRightSequence;
        case MSG_MOVE_STOP:
            return MovementStopSequence;
        case MSG_MOVE_STOP_ASCEND:
            return MovementStopAscendSequence;
        case MSG_MOVE_STOP_PITCH:
            return MovementStopPitchSequence;
        case MSG_MOVE_STOP_STRAFE:
            return MovementStopStrafeSequence;
        case MSG_MOVE_STOP_SWIM:
            return MovementStopSwimSequence;
        case MSG_MOVE_STOP_TURN:
            return MovementStopTurnSequence;
        case SMSG_PLAYER_MOVE:
            return PlayerMoveSequence;
        case CMSG_MOVE_CHNG_TRANSPORT:
            return MoveChngTransport;
        case CMSG_MOVE_SPLINE_DONE:
            return MoveSplineDone;
        case CMSG_MOVE_NOT_ACTIVE_MOVER:
            return MoveNotActiveMover;
        case CMSG_DISMISS_CONTROLLED_VEHICLE:
            return DismissControlledVehicle;
        case MSG_MOVE_UPDATE_TELEPORT:
            return MoveUpdateTeleport;
        case CMSG_MOVE_SET_CAN_FLY:
            return MoveSetCanFly;
        case CMSG_MOVE_SET_CAN_FLY_ACK:
            return MoveSetCanFlyAck;
        case MSG_MOVE_UPDATE_FLIGHT_SPEED:
            return UpdateFlightSpeed;
        case CMSG_CAST_SPELL:
        case CMSG_PET_CAST_SPELL:
        case CMSG_USE_ITEM:
            return CastSpellEmbeddedMovement;
        default:
            break;
    }

    return NULL;
};

#endif
