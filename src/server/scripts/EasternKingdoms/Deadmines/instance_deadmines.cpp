
#include "ScriptPCH.h"
#include "deadmines.h"

DoorData const doorData[] =
{
    {GO_FACTORY_DOOR,                   DATA_GLUBTOK,                   DOOR_TYPE_PASSAGE,      BOUNDARY_N      },
    {GO_HEAVY_DOOR_HELIX,               DATA_HELIX_GEARBREAKER,         DOOR_TYPE_PASSAGE,      BOUNDARY_N      },
    {0,                                 0,                              DOOR_TYPE_ROOM,         BOUNDARY_NONE   }, // END
};

class instance_deadmines : public InstanceMapScript
{
    public:
        instance_deadmines() : InstanceMapScript("instance_deadmines", 36){ }

        struct instance_deadmines_InstanceMapScript : public InstanceScript
        {
            instance_deadmines_InstanceMapScript(Map* map) : InstanceScript(map) 
            { 
                Initialize();
            };

            uint64 _glubtokGUID;
            uint64 _helixGearbreakerGUID;
            uint64 _foeReaper5000GUID;
            uint64 _admiralKnipsnarlGUID;
            uint64 _captainCookieGUID;
            uint64 _vanessaVanCleefGUID;

            uint32 _instanceFaction;

            void Initialize()
            { 
                SetBossNumber(MAX_ENCOUNTER);

                _glubtokGUID = 0;
                _helixGearbreakerGUID = 0;
                _foeReaper5000GUID = 0;
                _admiralKnipsnarlGUID = 0;
                _captainCookieGUID = 0;
                _vanessaVanCleefGUID = 0;
                _instanceFaction = 0;
                LoadDoorData(doorData);
            }

            void OnPlayerEnter(Player* player)
            {
                if (!GetData(DATA_TEAM_IN_INSTANCE))
                    SetData(DATA_TEAM_IN_INSTANCE, player->GetTeamId());
            }

            void OnCreatureCreate(Creature* creature)
            {

                switch (creature->GetEntry())
                {
                    case BOSS_GLUBTOK:
                        _glubtokGUID = creature->GetGUID();
                        break;
                    case BOSS_HELIX_GEARBREAKER:
                        _helixGearbreakerGUID = creature->GetGUID();
                        break;
                    case BOSS_FOE_REAPER_5000:
                        _foeReaper5000GUID = creature->GetGUID();
                        break;
                    case BOSS_ADMIRAL_RIPSNARL:
                        _admiralKnipsnarlGUID = creature->GetGUID();
                        break;
                    case BOSS_CAPTAIN_COOKIE:
                        _captainCookieGUID = creature->GetGUID();
                        break;
                    case BOSS_VANESSA_VAN_CLEEF:
                        _vanessaVanCleefGUID = creature->GetGUID();
                        break;
                    /*
                    case 46889: // Kagtha
                        if (_instanceFaction == TEAM_ALLIANCE)
                            creature->UpdateEntry(42308, ALLIANCE); // Lieutenant Horatio Laine
                        break;
                    case 46902: // Miss Mayhem
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(491, ALLIANCE); // Quartermaster Lewis <Quartermaster>
                        break;
                    case 46903: // Mayhem Reaper Prototype
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(1, ALLIANCE); // GM WAYPOINT
                        break;
                    case 46906: // Slinky Sharpshiv
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(46612, ALLIANCE); // Lieutenant Horatio Laine
                        break;
                    case 46613: // Crime Scene Alarm-O-Bot
                        if (TeamInInstance == HORDE)
                            creature->UpdateEntry(1, HORDE); // GM WAYPOINT
                        break;
                    case 50595: // Stormwind Defender
                        if (TeamInInstance == HORDE)
                            creature->UpdateEntry(46890, HORDE); // Shattered Hand Assassin
                        break;
                    case 46614: // Stormwind Investigator
                        if (TeamInInstance == HORDE)
                            creature->UpdateEntry(1, HORDE); // GM WAYPOINT
                        break;
                    */
                    default:
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_FACTORY_DOOR:
                    case GO_HEAVY_DOOR_HELIX:
                        AddDoor(go, true);
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

            void SetData(uint32 type, uint32 value)
            {
                switch (type)
                {
                    case DATA_TEAM_IN_INSTANCE:
                        _instanceFaction = value;
                        SaveToDB();
                        break;
                }
            }

            uint64 GetData64(uint32 data) const
            {
                switch (data)
                {
                    case DATA_GLUBTOK:
                        return _glubtokGUID;
                    case DATA_HELIX_GEARBREAKER:
                        return _helixGearbreakerGUID;
                    case DATA_FOE_REAPER_5000:
                        return _foeReaper5000GUID;
                    case DATA_ADMIRAL_RIPSNARL:
                        return _admiralKnipsnarlGUID;
                    case DATA_CAPTAIN_COOKIE:
                        return _captainCookieGUID;
                    case DATA_VANESSA_VAN_CLEEF:
                        return _vanessaVanCleefGUID;
                }
                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "D M " << GetBossSaveData() << " " <<_instanceFaction;

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


                if (dataHead1 == 'D' && dataHead2 == 'M')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

                        loadStream >> _instanceFaction;

                        SetBossState(i, EncounterState(tmpState));
                    }
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_deadmines_InstanceMapScript(map);
        }
};

void AddSC_instance_deadmines()
{
    new instance_deadmines();
}
