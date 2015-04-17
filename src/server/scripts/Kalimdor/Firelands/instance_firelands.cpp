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

#include "firelands.h"

DoorData const doorData[] =
{
    {GO_BALEROC_DOOR,                   DATA_BALEROC,                   DOOR_TYPE_ROOM,         BOUNDARY_N      },
    {GO_MAJODOMO_DOOR,                  DATA_MAJORDOMO_STANGHELM,       DOOR_TYPE_PASSAGE,      BOUNDARY_N      },
    {0,                                 0,                              DOOR_TYPE_ROOM,         BOUNDARY_NONE   }, // END
};

class instance_firelands : public InstanceMapScript
{
public:
    instance_firelands() : InstanceMapScript("instance_firelands", 720) { }

    struct instance_firelands_InstanceMapScript : public InstanceScript
    {
        instance_firelands_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetBossNumber(MAX_ENCOUNTERS);
            LoadDoorData(doorData);
            _ragnarosGUID = 0;
            _shannoxGUID = 0;
            _bethilacGUID = 0;
            _lordRhyolithGUID = 0;
            _majordomoGUID = 0;
            _alysrazorGUID = 0;
            _balerocGUID = 0;
            _shannoxControllerGUID = 0;
            _cacheOfTheFirelordGUID = 0;
            _ragnarosDoorGUID = 0;

            _bridgeEventDone = 0;
            _ragnarosSummoned = 0;
            _ragnarosFirstTimeSummoned = true;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_RAGNAROS:
                    _ragnarosGUID = creature->GetGUID();
                    break;
                case NPC_SMOULDERING_HATCHLING:
                    // Cannot directly start attacking here as the creature is not yet on map
                    creature->m_Events.AddEvent(new DelayedAttackStartEvent(creature), creature->m_Events.CalculateTime(500));
                    break;
                case BOSS_SHANNOX:
                    _shannoxGUID = creature->GetGUID();
                    break;
                case NPC_SHANNOX_CONTROLLER:
                    _shannoxControllerGUID = creature->GetGUID();
                    break;
                case BOSS_BETHILAC:
                    _bethilacGUID = creature->GetGUID();
                    break;
                case BOSS_LORD_RHYOLITH:
                    _lordRhyolithGUID = creature->GetGUID();
                    break;
                case BOSS_MAJORDOMO_STAGHELM:
                    _majordomoGUID = creature->GetGUID();
                    break;
                case BOSS_BALEROC:
                    _balerocGUID = creature->GetGUID();
                    break;
                case BOSS_ALYSRAZOR:
                    _alysrazorGUID = creature->GetGUID();
                    break;
                default:
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_BRIDGE_DOOR:
                    if (GetData(DATA_FIRELANDS_BRIDGE))
                        go->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_FIRELANDS_BRIDGE:
                    if (GetData(DATA_FIRELANDS_BRIDGE))
                        go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                    break;
                case GO_BALEROC_DOOR:
                case GO_MAJODOMO_DOOR:
                    AddDoor(go, true);
                    break;
                case GO_RAGNAROS_DOOR:
                    _ragnarosDoorGUID = go->GetGUID();
                    break;
                case GO_CACHE_OF_THE_FIRELORD:
                case GO_CACHE_OF_THE_FIRELORD_HC:
                    _cacheOfTheFirelordGUID = go->GetGUID();
                    break;
                default:
                    break;
            }
        }

        void OnGameObjectRemove(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_RAGNAROS_DOOR:
                case GO_MAJODOMO_DOOR:
                case GO_BALEROC_DOOR:
                    AddDoor(go, false);
                    break;
                default:
                    break;
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_FIRELANDS_BRIDGE:
                    _bridgeEventDone = data;
                    SaveToDB();
                    break;
                case DATA_FIRST_RAGNAROS_SUMMON:
                    _ragnarosFirstTimeSummoned = data;
                    break;
                case DATA_RAGNAROS_SUMMONED:
                    if (data == 1)
                    {
                        if (Creature* ragnaros = instance->SummonCreature(BOSS_RAGNAROS, RagnarosSummonPosition, 0))
                            ragnaros->AI()->DoAction(1);
                    }
                    else if (data == 4)
                        Events.ScheduleEvent(EVENT_SUMMON_RAGNAROS, 30000);

                    _ragnarosSummoned = data;
                    break;
                default:
                    break;
            }
        }

        uint32 GetData(uint32 type) const
        {
            switch(type)
            {
                case DATA_FIRELANDS_BRIDGE:
                    return (uint32)_bridgeEventDone;

                case DATA_RAGNAROS_SUMMONED:
                    return (uint32)_ragnarosSummoned;
                case DATA_FIRST_RAGNAROS_SUMMON:
                    return (uint32)_ragnarosFirstTimeSummoned;
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const
        {
            switch (data)
            {
                case DATA_RAGNAROS:
                    return _ragnarosGUID;
                case DATA_SHANNOX:
                    return _shannoxGUID;
                case DATA_SHANNOX_CONTROLLER:
                    return _shannoxControllerGUID;
                case DATA_BETHILAC:
                    return _bethilacGUID;
                case DATA_LORD_RHYOLITH:
                    return _lordRhyolithGUID;
                case DATA_MAJORDOMO_STANGHELM:
                    return _majordomoGUID;
                case DATA_BALEROC:
                    return _balerocGUID;
                case DATA_ALYSRAZOR:
                    return _alysrazorGUID;
                case DATA_RAGNAROS_DOOR:
                    return _ragnarosDoorGUID;
                case DATA_CACHE_OF_THE_FIRE_LORD:
                    return _cacheOfTheFirelordGUID;
                default:
                    break;
            }
            return 0;
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case DATA_BALEROC:
                    if (state == DONE)
                        if (Creature* majodomo = instance->GetCreature(_majordomoGUID))
                            majodomo->AI()->DoAction(1);
                    break;
                default:
                    break;
            }

            return true;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "F L " << GetBossSaveData() << _bridgeEventDone;

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* str)
        {
            if (!str)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(str);

            char dataHead1, dataHead2;

            std::istringstream loadStream(str);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'F' && dataHead2 == 'L')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    SetBossState(i, EncounterState(tmpState));
                }

                // Loading saved bridge event
                uint32 temp = 0;
                loadStream >> temp;
                SetData(DATA_FIRELANDS_BRIDGE, temp);
            }
            else
                OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void Update(uint32 diff)
        {
            Events.Update(diff);

            while (uint32 eventId = Events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_RAGNAROS:
                        if (Creature* ragnaros = instance->SummonCreature(BOSS_RAGNAROS, RagnarosSummonPosition, 0))
                            ragnaros->AI()->DoAction(1);
                        break;
                    default:
                        break;
                }
            }
        }
        protected:
            EventMap Events;
            uint64 _ragnarosGUID;
            uint64 _shannoxGUID;
            uint64 _bethilacGUID;
            uint64 _lordRhyolithGUID;
            uint64 _majordomoGUID;
            uint64 _alysrazorGUID;
            uint64 _balerocGUID;
            uint64 _shannoxControllerGUID;
            uint64 _cacheOfTheFirelordGUID;
            uint64 _ragnarosDoorGUID;

            uint8 _bridgeEventDone;
            uint8 _ragnarosSummoned;
            uint8 _ragnarosKilled;
            bool _ragnarosFirstTimeSummoned;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_firelands_InstanceMapScript(map);
    }
};

void AddSC_instance_firelands()
{
    new instance_firelands();
}