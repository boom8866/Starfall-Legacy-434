
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "zulaman.h"
#include "Player.h"
#include "TemporarySummon.h"

#define MAX_ENCOUNTERS 6

enum Worldstates
{
    WORLDSTATE_SHOW_TIMER          = 3104,
    WORLDSTATE_TIME_TO_SACRIFICE   = 3106
};

DoorData const doorData[] =
{
    {GO_AKILZON_DOOR,                   DATA_AKILZON,                   DOOR_TYPE_ROOM,         BOUNDARY_N      },
    {0,                                 0,                              DOOR_TYPE_ROOM,         BOUNDARY_NONE   }, // END
};

class instance_zulaman : public InstanceMapScript
{
    public:
        instance_zulaman() : InstanceMapScript("instance_zulaman", 568)
        {
        }

        struct instance_zulaman_InstanceMapScript : public InstanceScript
        {
            instance_zulaman_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                Initialize();
            }

            // Bosses
            uint64 _akilzonGUID;

            uint32 QuestTimer;

            void Initialize()
            {
                SetBossNumber(MAX_ENCOUNTERS);
                LoadDoorData(doorData);
                _akilzonGUID = 0;
            }

            void OnPlayerEnter(Player* /*player*/)
            {
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case BOSS_AKILZON:
                        _akilzonGUID = creature->GetGUID();
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_AKILZON_DOOR:
                        AddDoor(go, true);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_AKILZON_DOOR:
                        AddDoor(go, false);
                        break;
                    default:
                        break;
                }
            }

            bool SetBossState(uint32 data, EncounterState state)
            {
                if (!InstanceScript::SetBossState(data, state))
                    return false;

                return true;
            }

            void SetData(uint32 type, uint32 data)
            {
            }

            uint32 GetData(uint32 type) const
            {
                return 0;
            }

            uint64 GetData64(uint32 data) const
            {
                switch (data)
                {
                    case DATA_AKILZON:
                        return _akilzonGUID;
                    default:
                        break;
                }
                return 0;
            }

            void Update(uint32 diff)
            {
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "Z A " << GetBossSaveData();

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

                if (dataHead1 == 'Z' && dataHead2 == 'A')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

                        SetBossState(i, EncounterState(tmpState));
                    }

                } else OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        };
        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_zulaman_InstanceMapScript(map);
        }
};

void AddSC_instance_zulaman()
{
    new instance_zulaman();
}

