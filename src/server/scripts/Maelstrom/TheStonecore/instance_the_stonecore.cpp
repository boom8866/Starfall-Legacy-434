
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
        instance_the_stonecore_InstanceMapScript(Map* map) : InstanceScript(map)
        {
            Initialize();
        }

        uint64 _corborusGUID;
        uint64 _slabhideGUID;
        uint64 _ozrukGUID;
        uint64 _azilGUID;
        uint32 _corborusIntroDone;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);
            LoadDoorData(doorData);
            _corborusGUID = 0;
            _slabhideGUID = 0;
            _ozrukGUID = 0;
            _azilGUID = 0;
            _corborusIntroDone = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case BOSS_CORBORUS:
                _corborusGUID = creature->GetGUID();
                if (GetData(DATA_CORBORUS_PRE_EVENT))
                {
                    creature->SetHomePosition(1154.55f, 878.843f, 286.0f, 3.2216f);
                    creature->GetMotionMaster()->MoveTargetedHome();
                    creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                }
                break;
            case BOSS_SLABHIDE:
                _slabhideGUID = creature->GetGUID();
                break;
            case BOSS_OZRUK:
                _ozrukGUID = creature->GetGUID();
                break;
            case BOSS_HIGH_PRIESTESS_AZIL:
                _azilGUID = creature->GetGUID();
                break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch(go->GetEntry())
            {
                case GO_ROCKDOOR:
                    if (GetData(DATA_CORBORUS_PRE_EVENT))
                        go->SetGoState(GO_STATE_ACTIVE);
                    break;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
            case BOSS_CORBORUS:
                return _corborusGUID;
            case BOSS_SLABHIDE:
                return _slabhideGUID;
            case BOSS_OZRUK:
                return _ozrukGUID;
            case BOSS_HIGH_PRIESTESS_AZIL:
                return _azilGUID;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_CORBORUS_PRE_EVENT:
                    _corborusIntroDone = data;
                    SaveToDB();
                    break;
            }
        }

        uint32 GetData(uint32 type) const
        {
            switch(type)
            {
                case DATA_CORBORUS_PRE_EVENT:
                    return (uint32)_corborusIntroDone;
            }

            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "T S " << GetBossSaveData() << " " << _corborusIntroDone;

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

                    loadStream >> _corborusIntroDone;

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
