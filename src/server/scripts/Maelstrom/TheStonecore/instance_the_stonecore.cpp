
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "the_stonecore.h"

DoorData const doorData[] =
{
    {GO_STONEWALL,               DATA_SLABHIDE,            DOOR_TYPE_ROOM,    BOUNDARY_NONE},
    {0,                          0,                        DOOR_TYPE_ROOM,    BOUNDARY_NONE}
};

class instance_the_stonecore : public InstanceMapScript
{
public:
    instance_the_stonecore() : InstanceMapScript("instance_the_stonecore", 725) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_the_stonecore_InstanceMapScript(map);
    }

    struct instance_the_stonecore_InstanceMapScript : public InstanceScript
    {
        instance_the_stonecore_InstanceMapScript(Map* map) : InstanceScript(map) {};

        uint64 uiCorborus;
        uint64 uiSlabhide;
        uint64 uiOzruk;
        uint64 uiHighPriestessAzil;

        uint64 uiBrokenRockDoor;

        uint32 isCorborusPreEventDone;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);
            LoadDoorData(doorData);

            uiCorborus = 0;
            uiSlabhide = 0;
            uiOzruk    = 0;
            uiHighPriestessAzil = 0;

            uiBrokenRockDoor    = 0;

            isCorborusPreEventDone = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case BOSS_CORBORUS:
                uiCorborus = creature->GetGUID();
                break;
            case BOSS_SLABHIDE:
                uiSlabhide = creature->GetGUID();
                break;
            case BOSS_OZRUK:
                uiOzruk = creature->GetGUID();
                break;
            case BOSS_HIGH_PRIESTESS_AZIL:
                uiHighPriestessAzil = creature->GetGUID();
                break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch(go->GetEntry())
            {
            case GO_BROKEN_ROCKDOOR:
                {
                    uiBrokenRockDoor = go->GetGUID();
                    if (isCorborusPreEventDone)
                        go->SetGoState(GO_STATE_ACTIVE);
                    break;
                }
            case GO_STONEWALL:
                {
                    AddDoor(go, true);
                    break;
                }
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
            case BOSS_CORBORUS:             return uiCorborus;
            case BOSS_SLABHIDE:             return uiSlabhide;
            case BOSS_OZRUK:                return uiOzruk;
            case BOSS_HIGH_PRIESTESS_AZIL:  return uiHighPriestessAzil;

            case GO_BROKEN_ROCKDOOR:        return uiBrokenRockDoor;
            }

            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
            case DATA_CORBORUS_PRE_EVENT:
                isCorborusPreEventDone = data;
                SaveToDB();
                break;
            }
        }

        uint32 GetData(uint32 type) const
        {
            switch(type)
            {
            case DATA_CORBORUS_PRE_EVENT:
                return (uint32)isCorborusPreEventDone;
            }

            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "T S " << GetBossSaveData() << " " << isCorborusPreEventDone;

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'T' && dataHead2 == 'S')
            {
                for (uint8 i = 0; i < ENCOUNTER_COUNT; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    loadStream >> isCorborusPreEventDone;

                    SetBossState(i, EncounterState(tmpState));
                }

            } else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_the_stonecore()
{
    new instance_the_stonecore();
}
