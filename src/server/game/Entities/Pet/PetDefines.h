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

#ifndef TRINITYCORE_PET_DEFINES_H
#define TRINITYCORE_PET_DEFINES_H

enum PetType
{
    SUMMON_PET              = 0,
    HUNTER_PET              = 1,
    MAX_PET_TYPE            = 4
};

enum PetState
{
    PET_STATE_NONE              = 0,
    PET_STATE_ALIVE             = 1,
    PET_STATE_DEAD              = 2
};

enum PetTameResult
{
    PET_TAME_ERROR_UNKNOWN_ERROR            = 0,
    PET_TAME_ERROR_INVALID_CREATURE         = 1,
    PET_TAME_ERROR_TOO_MANY_PETS            = 2,
    PET_TAME_ERROR_CREATURE_ALREADY_OWNED   = 3,
    PET_TAME_ERROR_NOT_TAMEABLE             = 4,
    PET_TAME_ERROR_ANOTHER_SUMMON_ACTIVE    = 5,
    PET_TAME_ERROR_YOU_CANT_TAME            = 6,
    PET_TAME_ERROR_NO_PET_AVAILABLE         = 7,
    PET_TAME_ERROR_INTERNAL_ERROR           = 8,
    PET_TAME_ERROR_TOO_HIGH_LEVEL           = 9,
    PET_TAME_ERROR_DEAD                     = 10,
    PET_TAME_ERROR_NOT_DEAD                 = 11,
    PET_TAME_ERROR_CANT_CONTROL_EXOTIC      = 12,
    PET_TAME_ERROR_INVALID_SLOT             = 13 
};

enum PetSlot : int8
{
    PET_SLOT_DEFAULT         =   0,
    //Some not-in-db slots
    PET_SLOT_FULL_LIST       =  -4,        //Used when there is no slot free for tameing

    PET_SLOT_UNK_SLOT        =  -3,        // Used in some scripts.

    PET_SLOT_ACTUAL_PET_SLOT =  -2,        // Save the pet in his actual slot.
    PET_SLOT_DELETED         =  -1,        // Delete the pet
    //Hunter pet slots, sended to client at stable.

    PET_SLOT_HUNTER_FIRST    =   0,        // PetType == HUNTER_PET
    PET_SLOT_HUNTER_LAST     =   4,        // PetType == HUNTER_PET

    PET_SLOT_STABLE_FIRST    =   5,
    PET_SLOT_STABLE_LAST     =  24,
    //Non-hunter pet slot
    PET_SLOT_OTHER_PET       = 100,        // PetType != HUNTER_PET
};

#define MAX_PET_STABLES         PET_SLOT_STABLE_LAST

enum HappinessState
{
    UNHAPPY = 1,
    CONTENT = 2,
    HAPPY   = 3
};

enum PetSpellState
{
    PETSPELL_UNCHANGED = 0,
    PETSPELL_CHANGED   = 1,
    PETSPELL_NEW       = 2,
    PETSPELL_REMOVED   = 3
};

enum PetSpellType
{
    PETSPELL_NORMAL = 0,
    PETSPELL_FAMILY = 1,
    PETSPELL_TALENT = 2
};

enum ActionFeedback
{
    FEEDBACK_NONE            = 0,
    FEEDBACK_PET_DEAD        = 1,
    FEEDBACK_NOTHING_TO_ATT  = 2,
    FEEDBACK_CANT_ATT_TARGET = 3
};

enum PetTalk
{
    PET_TALK_SPECIAL_SPELL  = 0,
    PET_TALK_ATTACK         = 1
};

#define PET_FOLLOW_DIST  1.0f
#define PET_FOLLOW_ANGLE (M_PI/2)

#endif
