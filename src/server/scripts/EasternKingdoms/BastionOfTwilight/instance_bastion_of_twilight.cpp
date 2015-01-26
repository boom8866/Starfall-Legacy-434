
#include "bastion_of_twilight.h"

DoorData const doorData[] =
{
    {GO_HALFUS_ENTRANCE,                DATA_HALFUS_WYRMBREAKER,        DOOR_TYPE_ROOM,         BOUNDARY_N      },
    {GO_HALFUS_ESCAPE,                  DATA_HALFUS_WYRMBREAKER,        DOOR_TYPE_PASSAGE,      BOUNDARY_NONE   },
    {GO_TAV_ENTRANCE,                   DATA_THERALION_AND_VALIONA,     DOOR_TYPE_ROOM,         BOUNDARY_N      },
    //{GO_TAV_ESCAPE,                     DATA_THERALION_AND_VALIONA,     DOOR_TYPE_PASSAGE,      BOUNDARY_NONE   },
    {GO_COA_ENTRANCE,                   DATA_ASCENDANT_COUNCIL,         DOOR_TYPE_ROOM,         BOUNDARY_N      },
    {GO_COA_ESCAPE,                     DATA_ASCENDANT_COUNCIL,         DOOR_TYPE_PASSAGE,      BOUNDARY_NONE   },
    {GO_CHOGALL_ENTRANCE,               DATA_CHOGALL,                   DOOR_TYPE_ROOM,         BOUNDARY_N      },
    {0,                                 0,                              DOOR_TYPE_ROOM,         BOUNDARY_NONE   }, // END
};

class instance_bastion_of_twilight : public InstanceMapScript
{
    public:
        instance_bastion_of_twilight() : InstanceMapScript("instance_bastion_of_twilight", 671) { }

        struct instance_bastion_of_twilight_InstanceMapScript : public InstanceScript
        {
            instance_bastion_of_twilight_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetBossNumber(MAX_ENCOUNTER);
                LoadDoorData(doorData);
                _HalfusGUID = 0;
                _BehemothGUID = 0;
                _ValionaGUID = 0;
                _TheralionGUID = 0;
                _AscendantcouncilGUID = 0;
                _FeludiusGUID = 0;
                _IgnaciousGUID = 0;
                _ArionGUID = 0;
                _TerrastraGUID = 0;
                _MonstrosityGUID = 0;
                _ChoGallGUID = 0;
                _SinestraGUID = 0;
                _slateGUID = 0;
                _netherGUID = 0;
                _timeGUID = 0;
                _whelpGUID = 0;
                _stormGUID = 0;
                _cageGUID = 0;
                _chogallHalfusGUID = 0;
                _chogallTAVGUID = 0;
                chogallCouncil = 0;
                _dragonsPicked = 0;
            }

            void OnPlayerEnter(Player* /*player*/)
            {
                if (GetData(DATA_DRAGONS_PICKED) == 0 && (instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL) || instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL)
                    SetData(DATA_DRAGONS_PICKED, urand(1, 10));
                else if (GetData(DATA_DRAGONS_PICKED) == 0)
                    SetData(DATA_DRAGONS_PICKED, 11);
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case BOSS_HALFUS_WYRMBREAKER:
                        _HalfusGUID = creature->GetGUID();
                        break;
                    case NPC_PROTO_BEHEMOTH:
                        _BehemothGUID = creature->GetGUID();
                        break;
                    case BOSS_VALIONA:
                        _ValionaGUID = creature->GetGUID();
                        break;
                    case BOSS_THERALION:
                        _TheralionGUID = creature->GetGUID();
                        break;
                    case NPC_ASCENDANT_COUNCIL:
                        _AscendantcouncilGUID = creature->GetGUID();
                        break;
                    case BOSS_FELUDIUS:
                        _FeludiusGUID = creature->GetGUID();
                        break;
                    case BOSS_IGNACIOUS:
                        _IgnaciousGUID = creature->GetGUID();
                        break;
                    case BOSS_ARION:
                        _ArionGUID = creature->GetGUID();
                        break;
                    case BOSS_TERRASTRA:
                        _TerrastraGUID = creature->GetGUID();
                        break;
                    case BOSS_ELEMENTIUM_MONSTROSITY:
                        _MonstrosityGUID = creature->GetGUID();
                        break;
                    case BOSS_CHOGALL:
                        _ChoGallGUID = creature->GetGUID();
                        creature->setActive(true);
                        break;
                    case BOSS_SINESTRA:
                        _SinestraGUID = creature->GetGUID();
                        break;
                    case NPC_CHOGALL_HALFUS:
                        _chogallHalfusGUID = creature->GetGUID();
                        break;
                    case NPC_CHOGALL_DRAGONS:
                        _chogallTAVGUID = creature->GetGUID();
                        break;
                    case NPC_CHOGALL_COUNCIL:
                        chogallCouncil = creature->GetGUID();
                        break;
                    case NPC_SLATE_DRAGON:
                        _slateGUID = creature->GetGUID();
                        break;
                    case NPC_NETHER_SCION:
                        _netherGUID = creature->GetGUID();
                        break;
                    case NPC_TIME_WARDEN:
                        _timeGUID = creature->GetGUID();
                        break;
                    case NPC_ORPHANED_EMERALD_WHELP:
                        _whelpGUID = creature->GetGUID();
                        break;
                    case NPC_STORM_RIDER:
                        _stormGUID = creature->GetGUID();
                        break;
                    case NPC_FABULOUS_FLAME_STALKER:
                    case NPC_TWILIGHT_FLAME:
                    case NPC_DAZZ_DESTRUCTION_STALKER:
                        creature->SetPhaseMask(1 | 290, false);
                        break;
                    case NPC_UNSTABLE_TWILIGHT:
                        creature->SetPhaseMask(290, false);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_HALFUS_ENTRANCE:
                    case GO_HALFUS_ESCAPE:
                    case GO_TAV_ENTRANCE:
                    case GO_TAV_ESCAPE:
                    case GO_COA_ENTRANCE:
                    case GO_COA_ESCAPE:
                    case GO_CHOGALL_ENTRANCE:
                        AddDoor(go, true);
                        break;
                    case GO_WELP_CAGE:
                        _cageGUID = go->GetGUID();
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_HALFUS_ENTRANCE:
                    case GO_HALFUS_ESCAPE:
                    case GO_TAV_ENTRANCE:
                    case GO_TAV_ESCAPE:
                    case GO_COA_ENTRANCE:
                    case GO_COA_ESCAPE:
                    case GO_CHOGALL_ENTRANCE:
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
                    case DATA_DRAGONS_PICKED:
                        _dragonsPicked = data;
                        sLog->outError(LOG_FILTER_MAPSCRIPTS, "Bastion of Twilight -> Halfus Setup: combination %u picked", data);
                        SaveToDB();
                        break;
                    default:
                        break;
                }
            }

            uint32 GetData(uint32 data) const
            {
                switch (data)
                {
                    case DATA_DRAGONS_PICKED:
                        return _dragonsPicked;
                    default:
                        break;
                }
                return 0;
            }

            uint64 GetData64(uint32 type) const
            {
                switch (type)
                {
                    case DATA_HALFUS_WYRMBREAKER:
                        return _HalfusGUID;
                        break;
                    case DATA_PROTO_BEHEMOTH:
                        return _BehemothGUID;
                        break;
                    case DATA_SLATE_DRAGON:
                        return _slateGUID;
                        break;
                    case DATA_NETHER_SCION:
                        return _netherGUID;
                        break;
                    case DATA_TIME_WARDEN:
                        return _timeGUID;
                        break;
                    case DATA_STORM_RIDER:
                        return _stormGUID;
                        break;
                    case DATA_WHELPS:
                        return _whelpGUID;
                        break;
                    case DATA_CAGE:
                        return _cageGUID;
                        break;
                    case DATA_THERALION_AND_VALIONA:
                        return _ValionaGUID;
                        return _TheralionGUID;
                        break;
                    case DATA_ASCENDANT_COUNCIL:
                        return _AscendantcouncilGUID;
                        return _FeludiusGUID;
                        return _IgnaciousGUID;
                        return _ArionGUID;
                        return _TerrastraGUID;
                        return _MonstrosityGUID;
                        break;
                    case DATA_CHOGALL:
                        return _ChoGallGUID;
                        break;
                    case DATA_SINESTRA:
                        return _SinestraGUID;
                        break;
                    case DATA_CHOGALL_HALFUS_INTRO:
                        return _chogallHalfusGUID;
                        break;
                    case DATA_CHOGALL_TAV_INTRO:
                        return _chogallTAVGUID;
                        break;
                    case NPC_CHOGALL_COUNCIL:
                        return chogallCouncil;
                        break;
                    case DATA_VALIONA:
                        return _ValionaGUID;
                        break;
                    case DATA_THERALION:
                        return _TheralionGUID;
                        break;
                    case DATA_FELUDIUS:
                        return _FeludiusGUID;
                        break;
                    case DATA_IGNACIOUS:
                        return _IgnaciousGUID;
                        break;
                    case DATA_TERRASTRA:
                        return _TerrastraGUID;
                        break;
                    case DATA_ARION:
                        return _ArionGUID;
                        break;
                    default:
                        return 0;
                        break;
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
                saveStream << "B O T " << GetBossSaveData() << ' ' << _dragonsPicked;

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

                char dataHead1, dataHead2, dataHead3;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2 >> dataHead3;

                if (dataHead1 == 'B' && dataHead2 == 'O' && dataHead3 == 'T')
                {
                    for (uint32 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }

                    uint32 temp = 0;
                    loadStream >> temp;
                    _dragonsPicked = temp;
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

        protected:
            uint64 _HalfusGUID;
            uint64 _BehemothGUID;
            uint64 _ValionaGUID;
            uint64 _TheralionGUID;
            uint64 _AscendantcouncilGUID;
            uint64 _FeludiusGUID;
            uint64 _IgnaciousGUID;
            uint64 _ArionGUID;
            uint64 _TerrastraGUID;
            uint64 _MonstrosityGUID;
            uint64 _ChoGallGUID;
            uint64 _SinestraGUID;
            uint64 _slateGUID;
            uint64 _netherGUID;
            uint64 _timeGUID;
            uint64 _whelpGUID;
            uint64 _stormGUID;
            uint64 _cageGUID;
            uint64 _chogallHalfusGUID;
            uint64 _chogallTAVGUID;
            uint64 chogallCouncil;
            uint32 _dragonsPicked;
            uint8 data_phase; 
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_bastion_of_twilight_InstanceMapScript(map);
        }
};

void AddSC_instance_bastion_of_twilight()
{
    new instance_bastion_of_twilight();
}
