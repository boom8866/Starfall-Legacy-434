
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
        uint64 _kalecgosMadnessGUID;
        uint64 _yseraMadnessGUID;
        uint64 _nozdormuMadnessGUID;
        uint64 _alexstraszaMadnessGUID;
        uint64 _thrallMadnessGUID;
        
        uint64 _lordAfrasastraszGUID;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
            _morchokGUID = 0;
            _ultraxionGUID = 0;
            _madnessOfDeathwingGUID = 0;
            _kalecgosMadnessGUID = 0;
            _yseraMadnessGUID = 0;
            _nozdormuMadnessGUID = 0;
            _alexstraszaMadnessGUID = 0;
            _thrallMadnessGUID = 0;
            _lordAfrasastraszGUID = 0;
            SetBossState(DATA_HAGARA, DONE);
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
                case NPC_ALEXSTRASZA_MADNESS:
                    _alexstraszaMadnessGUID = creature->GetGUID();
                    break;
                case NPC_KALECGOS_MADNESS:
                    _kalecgosMadnessGUID = creature->GetGUID();
                    break;
                case NPC_YSERA_MADNESS:
                    _yseraMadnessGUID = creature->GetGUID();
                    break;
                case NPC_NOZDORMU_MADNESS:
                    _nozdormuMadnessGUID = creature->GetGUID();
                    break;
                case NPC_THRALL_MADNESS:
                    _thrallMadnessGUID = creature->GetGUID();
                    break;
                case NPC_LORD_AFRASASTRASZ:
                    _lordAfrasastraszGUID = creature->GetGUID();
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
                case DATA_ALEXSTRASZA_MADNESS:
                    return _alexstraszaMadnessGUID;
                case DATA_YSERA_MADNESS:
                    return _yseraMadnessGUID;
                case DATA_KALECGOS_MADNESS:
                    return _kalecgosMadnessGUID;
                case DATA_NOZDORMU_MADNESS:
                    return _nozdormuMadnessGUID;
                case DATA_THRALL_MADNESS:
                    return _thrallMadnessGUID;
                case DATA_LORD_AFRASASTRASZ:
                    return _lordAfrasastraszGUID;
                default:
                    break;
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
