
#include "dragonsoul.h"

class instance_dragonsoul : public InstanceMapScript
{
public:
    instance_dragonsoul() : InstanceMapScript("instance_dragonsoul", 967) { }

    struct instance_dragonsoul_InstanceMapScript : public InstanceScript
    {
        instance_dragonsoul_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        uint64 _morchokGUID;
        uint64 _ultraxionGUID;
        uint64 _madnessOfDeathwingGUID;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
            _morchokGUID = 0;
            _ultraxionGUID = 0;
            _madnessOfDeathwingGUID = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_MORCHOK:
                    _morchokGUID = creature->GetGUID();
                    break;
                case BOSS_ULTRAXION:
                    _ultraxionGUID = creature->GetGUID();
                    break;
                case BOSS_MADNESS_OF_DEATHWING:
                    _madnessOfDeathwingGUID = creature->GetGUID();
                    break;
                default:
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            //switch (go->GetEntry())
            //{
            //}
        }

        bool SetBossState(uint32 data, EncounterState state)
        {
            if (!InstanceScript::SetBossState(data, state))
                return false;

            return true;
        }

        uint64 GetData64(uint32 data) const
        {
            switch (data)
            {
                case DATA_MORCHOK:
                    return _morchokGUID;
                case DATA_ULTRAXION:
                    return _ultraxionGUID;
                case DATA_MADNESS_OF_DEATHWING:
                    return _madnessOfDeathwingGUID;
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "D S " << GetBossSaveData();

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

            if (dataHead1 == 'D' && dataHead2 == 'S')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
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
        return new instance_dragonsoul_InstanceMapScript(map);
    }
};

void AddSC_instance_dragonsoul()
{
    new instance_dragonsoul();
}
