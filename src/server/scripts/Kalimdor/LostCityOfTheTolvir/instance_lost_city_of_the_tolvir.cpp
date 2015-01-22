#include "lost_city_of_the_tolvir.h"

#define MAX_ENCOUNTERS 4

class instance_lost_city_of_the_tolvir : public InstanceMapScript
{
public:
    instance_lost_city_of_the_tolvir() : InstanceMapScript("instance_lost_city_of_the_tolvir", 755) { }

    struct instance_lost_city_of_the_tolvir_InstanceMapScript: public InstanceScript
    {
        instance_lost_city_of_the_tolvir_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTERS);
            _generalHusamGUID = 0;
            _lockmawGUID = 0;
            _highProphetBarinGUID = 0;
            _siamatGUID = 0;

            for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
                SetBossState(i, NOT_STARTED);
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                 case BOSS_GENERAL_HUSAM:
                     _generalHusamGUID = creature->GetGUID();
                     break;
                 case BOSS_LOCKMAW:
                     _lockmawGUID = creature->GetGUID();
                     break;
                 case BOSS_HIGH_PROPHET_BARIM:
                     _highProphetBarinGUID = creature->GetGUID();
                     break;
                 case BOSS_SIAMAT:
                     _siamatGUID = creature->GetGUID();
                     if (GetBossState(DATA_GENERAL_HUSAM) == DONE && GetBossState(DATA_LOCKMAW) == DONE && GetBossState(DATA_HIGH_PROPHET_BARIM) == DONE)
                         creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                     else
                         creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
                     break;
                 default:
                     break;

            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_SIAMAT_PLATFORM:
                    if (GetBossState(DATA_GENERAL_HUSAM) == DONE && GetBossState(DATA_LOCKMAW) == DONE && GetBossState(DATA_HIGH_PROPHET_BARIM) == DONE)
                        go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                    break;
                default:
                    break;
            }
        }

        uint64 getData64(uint32 identifier) const
        {
            switch (identifier)
            {
                case DATA_GENERAL_HUSAM:
                    return _generalHusamGUID;
                    break;
                case DATA_LOCKMAW:
                    return _lockmawGUID;
                    break;
                case DATA_HIGH_PROPHET_BARIM:
                    return _highProphetBarinGUID;
                    break;
                case DATA_SIAMAT:
                    return _siamatGUID;
                    break;
            }
            return 0;
        }

        bool IsEncounterInProgress() const
        {
            for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
                if (GetBossState(i) == IN_PROGRESS)
                    return true;
            
            return false;
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            if (GetBossState(DATA_GENERAL_HUSAM) == DONE && GetBossState(DATA_LOCKMAW) == DONE && GetBossState(DATA_HIGH_PROPHET_BARIM) == DONE)
                if (Creature* siamat = instance->GetCreature(_siamatGUID))
                {
                    siamat->AI()->DoAction(1);
                    siamat->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
                }

            return true;
        }

        void SetData(uint32 type, uint32 data)
        {
            SetBossState(type, EncounterState(data));

            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type) const
        {
            return GetBossState(type);
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "T V " << GetBossSaveData();

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

            if (dataHead1 == 'T' && dataHead2 == 'V')
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
    private:
        uint64 _generalHusamGUID;
        uint64 _lockmawGUID;
        uint64 _highProphetBarinGUID;
        uint64 _siamatGUID;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_lost_city_of_the_tolvir_InstanceMapScript(map);
    }
};

void AddSC_instance_lost_city_of_the_tolvir()
{
    new instance_lost_city_of_the_tolvir();
}