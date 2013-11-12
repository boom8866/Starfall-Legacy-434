
#include "well_of_eternity.h"

DoorData const doorData[] =
{
    {GO_COURTYARD_FIREWALL,         DATA_PEROTHARN,         DOOR_TYPE_ROOM,     BOUNDARY_N},
};

class instance_well_of_eternity : public InstanceMapScript
{
public:
    instance_well_of_eternity() : InstanceMapScript("instance_well_of_eternity", 939) { }

    struct instance_well_of_eternity_InstanceMapScript : public InstanceScript
    {
        instance_well_of_eternity_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        uint64 _perotharnGUID;
        uint64 _azsharaGUID;
        uint64 _varothenGUID;
        uint64 _mannorothGUID;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTERS);
            LoadDoorData(doorData);
            _perotharnGUID = 0;
            _azsharaGUID = 0;
            _varothenGUID = 0;
            _mannorothGUID = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_PEROTHARN:
                    _perotharnGUID = creature->GetGUID();
                    break;
                case BOSS_MANNOROTH:
                    _mannorothGUID = creature->GetGUID();
                    creature->setActive(true);
                    creature->CastSpell(creature, 102920);
                    break;
                case NPC_THE_DRAGON_SOUL:
                    creature->setActive(true);
                    //creature->AI()->DoCastAOE(102919, false);
                    break;
                case NPC_WELL_PORTAL:
                    creature->setActive(true);
                    break;
                default:
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_COURTYARD_FIREWALL:
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
                case GO_COURTYARD_FIREWALL:
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

        uint64 GetData64(uint32 data) const
        {
            switch (data)
            {
                case DATA_PEROTHARN:
                    return _perotharnGUID;
                case DATA_MANNOROTH:
                    return _mannorothGUID;
                default:
                    break;
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "W O E " << GetBossSaveData();

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

            char dataHead1, dataHead2, dataHead3;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> dataHead3;

            if (dataHead1 == 'W' && dataHead2 == 'O' && dataHead3 == 'E')
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
        return new instance_well_of_eternity_InstanceMapScript(map);
    }
};

void AddSC_instance_well_of_eternity()
{
    new instance_well_of_eternity();
}
