/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#ifndef DEF_FIRELANDS_H
#define DEF_FIRELANDS_H

#include "Map.h"
#include "CreatureAI.h"

#define MAX_ENCOUNTERS 7

enum Datas
{
    DATA_BETHILAC               = 1,
    DATA_LORD_RHYOLITH          = 2,
    DATA_ALYSRAZOR              = 3,
    DATA_SHANNOX                = 4,
    DATA_BALEROC                = 5,
    DATA_MAJORDOMO_STANGHELM    = 6,
    DATA_RAGNAROS               = 7,

    DATA_SHANNOX_CONTROLLER     = 8,
};

enum GameObjectIds
{
    GO_ALYSRAZOR_VOLCANO        = 209253,
    GO_MOLTEN_GROUND            = 209252,

    GO_RAGNAROS_DOOR            = 209073,
    GO_RAGNAROS_PLATFORM        = 208835,
    GO_CACHE_OF_THE_FIRELORD    = 209261,
    GO_CACHE_OF_THE_FIRELORD_HC = 208967,

    GO_BALEROC_DOOR             = 209066,

    GO_FIRELANDS_BRIDGE         = 209251,
    GO_BRIDGE_DOOR              = 209277,

    GO_MAJODOMO_DOOR            = 208906,
};

enum CreatureIds
{
    // Bosses
    BOSS_RAGNAROS                   = 52409,
    BOSS_SHANNOX                    = 53691,
    BOSS_LORD_RHYOLITH              = 52558,
    BOSS_BETHILAC                   = 52498,
    BOSS_MAJORDOMO_STAGHELM         = 52571,
    BOSS_BALEROC                    = 53494,
    BOSS_ALYSRAZOR                  = 52530,

    // Ragnaros Encounter
    NPC_SULFURAS_SMASH_TRIGGER      = 53266,
    NPC_SULFURAS_SMASH_TARGET       = 53268,
    NPC_LAVA_WAVE                   = 53363,
    NPC_ENGULFING_FLAMES_TRIGGER    = 53485,
    NPC_SPLITTING_BLOW_TRIGGER      = 53393,
    NPC_MAGMA_POOL_TRIGGER          = 53729,
    NPC_PLATFORM_TRIGGER            = 53952,
    NPC_MAGMA_TRAP                  = 53086,
    NPC_SULFURAS_HAND_OF_RAGNAROS   = 53420,
    NPC_SON_OF_FLAME                = 53140,
    NPC_MOLTEN_ERUPTER              = 53617,
    NPC_MOLTEN_SPEWER               = 53545,
    NPC_MOLTEN_ELEMENTAL            = 53189,
    NPC_MOLTEN_SEED_CASTER          = 53186,
    NPC_LAVA_SCION                  = 53231,
    NPC_BLAZING_HEAT                = 53473,
    NPC_LIVING_METEOR               = 53500,
    NPC_DREADFLAME                  = 54127,
    NPC_DREADFLAME_SPAWN            = 54203,
    NPC_CLOUDBURST                  = 54147,
    NPC_ENTRAPPING_ROOTS            = 54074,
    NPC_BREADTH_OF_FROST            = 53953,
    NPC_HEART_OF_RAGNAROS           = 54293,

    NPC_CENARIUS                    = 53872,
    NPC_HAMUUL                      = 53876,
    NPC_MALFURION                   = 53875,

    // Shannox Encounter
    NPC_RAGEFACE                    = 53695,
    NPC_RIPLIMB                     = 53694,
    NPC_SHANNOX_CONTROLLER          = 53910,
    NPC_IMMOLATION_TRAP             = 53724,
    NPC_CRYSTAL_TRAP                = 53713,
    NPC_CRYSTAL_PRISON              = 53819,
    NPC_HURL_SPEAR_TARGET           = 53752,
    NPC_SHANNOX_SPEAR               = 54112,

    // Beth'ilac Encounter
    NPC_LIFT_OFF                    = 53529,

    // Lord Rhyolith Encounter
    NPC_LEFT_FOOT                   = 52577,
    NPC_RIGHT_FOOT                  = 53087,
    NPC_MOVEMENT_CONTROLLER         = 52659,
    NPC_VOLCANO                     = 52582,

    // Firelands Stuff
    NPC_BLAZING_MONSTROSITY_LEFT    = 53786,
    NPC_BLAZING_MONSTROSITY_RIGHT   = 53791,
    NPC_EGG_PILE                    = 53795,
    NPC_HARBINGER_OF_FLAME          = 53793,
	NPC_MOLTEN_EGG_TRASH            = 53914,	
    NPC_SMOULDERING_HATCHLING       = 53794,

    // Firelands Trash
    NPC_MOLTEN_LORD                 = 53115,
    NPC_LAVA_DUMMY                  = 53585,

    // Bridge Cinematic
    NPC_BRIDGE_TRIGGER              = 42098,

    // Majordomo Encounter
    NPC_DRUID_OF_THE_FLAME          = 53619,
    NPC_SPIRIT_OF_THE_FLAME         = 52593,

    // Alysrazor
    NPC_VOLCANO_DUMMY               = 53154,
    NPC_VOLCANO_TARGET              = 53158,
    NPC_INCINDIARY_CLOUD            = 53541,
    NPC_PURPOSE_BUNNY               = 45979,
    NPC_TIMING_BUNNY                = 53723,
    NPC_FIERY_VORTEX                = 53693,
    NPC_FIERY_TORNADO               = 53698,
    NPC_BLAZING_TALON_CLAWSHAPER    = 53734,
};

enum FirelandsMisc
{
    CINEMATIC_BRIDGE_FORMING    = 197,
};

class DelayedAttackStartEvent : public BasicEvent
{
    public:
        DelayedAttackStartEvent(Creature* owner) : _owner(owner) { }

        bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
        {
            _owner->AI()->DoZoneInCombat(_owner, 200.0f);
            return true;
        }

    private:
        Creature* _owner;
};

/*
template<class AI>
CreatureAI* GetFirelandsAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(FirelandsScriptName))
                return new AI(creature);
    return NULL;
}
*/

#endif // FIRELANDS_H_
