
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#ifndef BLACKROCK_CAVERNS_H
#define BLACKROCK_CAVERNS_H

enum Data
{
    DATA_ROMOGG_BONECRUSHER,
    DATA_CORLA_HERALD_OF_TWILIGHT,
    DATA_KARSH_STEELBENDER,
    DATA_BEAUTY,
    DATA_ASCENDANT_LORD_OBSIDIUS,
    ENCOUNTER_COUNT
};

enum Creatures
{
    // Bosses
    BOSS_ROMOGG_BONECRUSHER         = 39665,
    BOSS_CORLA                      = 39679,
    BOSS_KARSH_STEELBENDER          = 39698,
    BOSS_BEAUTY                     = 39700,
    BOSS_ASCENDANT_LORD_OBSIDIUS    = 39705,

    // Romogg Bonecrusher
    NPC_ANGERED_EARTH               = 50376,
    NPC_CHAINS_OF_WOE               = 40447,

    NPC_TWILIGHT_TORTURER           = 39978,
    NPC_TWILIGHT_SADIST             = 39980,
    NPC_CRAZED_MAGE                 = 39982,
    NPC_MAD_PRISONER                = 39985,

    // Corla, Herald of Twilight
    NPC_TWILIGHT_ZEALOT             = 50284,
    NPC_NETHER_ESSENCE_TRIGGER      = 39842,

    // Karsh Steelbender
    NPC_BOUND_FLAMES                = 50417,
    NPC_LAVA_SPOUT_TRIGGER          = 39842,
    NPC_LAVA_POOL                   = 50423,

    // Ascendant Lord  Obsidius
    NPC_SHADOW_OF_OBSIDIUS          = 40817,

    // Various NPCs
    NPC_RAZ_THE_CRAZED              = 39670,
    NPC_FINKLE_EINHORN              = 49476,
    NPC_TWILIGHT_GUARD              = 40017,
    NPC_TWILIGHT_PORTAL             = 51340
};

enum GameObjects
{
    GO_STONE_TABLET                 = 207412
};

enum InstanceActions
{
    INST_ACTION_RAZ_START_EVENT     = 1
};

Position const instancePositions[] =
{
    {292.37796f, 557.551819f, 67.5958f, 0},           // Finkle Einhorn upper spawn position
    {569.f, 909.f, 175.8f, 0},                        // Nether Essence Trigger position
    {315.316986f, 555.721497f, 66.105415f, 6.000578f} // Finkle Einhorn last run position
};

class InstancePlayerCheck
{
public:
    bool operator()(WorldObject* object) const
    {
        if (object->GetTypeId() != TYPEID_PLAYER)
            return true;

        return false;
    }
};
#endif // BLACKROCK_CAVERNS_H
