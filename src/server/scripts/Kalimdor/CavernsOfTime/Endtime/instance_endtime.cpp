#include "endtime.h"

class instance_endtime : public InstanceMapScript
{
    public:
        instance_endtime() : InstanceMapScript("instance_endtime", 671) { }

        struct instance_endtime_InstanceMapScript : public InstanceScript
        {
            instance_endtime_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetBossNumber(MAX_ENCOUNTERS);
                _murozondGUID           = 0;
                _echoOfJainaGUID        = 0;
                _echoOfBaineGUID        = 0;
                _echoOfSylvanasGUID     = 0;
                _echoOfTyrandeGUID      = 0;
                _temporalCacheGUID      = 0;
                _hourglassOfTimeGUID    = 0;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case BOSS_MUROZOND:
                        _murozondGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_TEMPORAL_CACHE:
                        _temporalCacheGUID = go->GetGUID();
                        go->SetPhaseMask(2, true);
                        break;
                    case GO_HOURGLASS_OF_TIME:
                        _hourglassOfTimeGUID = go->GetGUID();
                        break;
                }
            }

            void SetData(uint32 type, uint32 data)
            {
            }

            uint32 GetData(uint32 data) const
            {
                /*
                switch (data)
                {
                }
                */
                return 0;
            }

            uint64 GetData64(uint32 type) const
            {
                switch (type)
                {
                    case DATA_MUROZOND:
                        return _murozondGUID;
                    case DATA_TEMPORAL_CACHE:
                        return _temporalCacheGUID;
                    case DATA_HOURGLASS_OF_TIME:
                        return _hourglassOfTimeGUID;
                }
                return NULL;
            }

            bool SetBossState(uint32 data, EncounterState state) 
            {
                if (!InstanceScript::SetBossState(data, state))
                    return false;

                return true;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "E T " << GetBossSaveData();

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

                if (dataHead1 == 'E ' && dataHead2 == 'T ')
                {
                    for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }
                    uint32 tmp;
                    loadStream >> tmp;
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

        protected:
            uint64 _murozondGUID;
            uint64 _echoOfJainaGUID;
            uint64 _echoOfBaineGUID;
            uint64 _echoOfSylvanasGUID;
            uint64 _echoOfTyrandeGUID;
            uint64 _temporalCacheGUID;
            uint64 _hourglassOfTimeGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_endtime_InstanceMapScript(map);
        }
};

void AddSC_instance_endtime()
{
    new instance_endtime();
}
