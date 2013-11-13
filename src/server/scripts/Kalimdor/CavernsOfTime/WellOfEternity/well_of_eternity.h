
#ifndef DEF_WELL_OF_ETERNITY_H
#define DEF_WELL_OF_ETERNITY_H

#include "Map.h"
#include "CreatureAI.h"

#define MAX_ENCOUNTERS 4

enum Datas
{
    DATA_PEROTHARN = 1,
    DATA_AZSHARA,
    DATA_VAROTHEN,
    DATA_MANNOROTH,
};

enum GameObjects
{
    GO_TRANSIT_SERVICE      = 209998,
    GO_COURTYARD_DOOR       = 210084,
    GO_COURTYARD_FIREWALL   = 210234,
};

enum Creatures
{
    BOSS_PEROTHARN      = 55085,
    BOSS_MANNOROTH      = 54969,

    // Misc
    NPC_THE_DRAGON_SOUL     = 55078,
    NPC_WELL_PORTAL         = 56087,

    NPC_CORRUPTED_ARCANIST  = 55654,
    NPC_DREADLORD_DEFENDER  = 55656,
    NPC_LEGION_DEMON_1      = 55503, // Intro Demon at the entrance
    NPC_FIRE_WALL_STALKER   = 56096,

};

#endif
