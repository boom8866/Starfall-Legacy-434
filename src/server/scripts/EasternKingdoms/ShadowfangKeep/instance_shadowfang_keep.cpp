
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "shadowfang_keep.h"
#include "TemporarySummon.h"

enum Factions
{
    FACTION_FRIENDLY = 35
};

DoorData const doorData[] =
{
    {GO_COURTYARD_DOOR,                 DATA_BARON_ASHBURY,             DOOR_TYPE_PASSAGE,      BOUNDARY_NONE   }, // Temporally unitl Horde/Alliance events are scripted
    {0,                                 0,                              DOOR_TYPE_ROOM,         BOUNDARY_NONE   }, // END
};

class instance_shadowfang_keep : public InstanceMapScript
{
    public:
        instance_shadowfang_keep() : InstanceMapScript("instance_shadowfang_keep", 33) { }

        struct instance_shadowfang_keep_InstanceScript : public InstanceScript
        {
            instance_shadowfang_keep_InstanceScript(Map* map) : InstanceScript(map) 
            {
                Initialize();
            }

            uint64 _baronAshburyGUID;
            uint64 _baronSilverlaineGUID;
            uint64 _commanderSpringvaleGUID;
            uint64 _lordWaldenGUID;
            uint64 _lordGodfreyGUID;

            void Initialize()
            {
                SetBossNumber(MAX_ENCOUNTER);
                LoadDoorData(doorData);
                _baronAshburyGUID          = 0;
                _baronSilverlaineGUID      = 0;
                _commanderSpringvaleGUID   = 0;
                _lordWaldenGUID            = 0;
                _lordGodfreyGUID           = 0;
            }

            void OnCreatureCreate(Creature* creature)
            {
                Map::PlayerList const &players = instance->GetPlayers();
                uint32 TeamInInstance = 0;

                if (!players.isEmpty())
                {
                    if (Player* pPlayer = players.begin()->getSource())
                        TeamInInstance = pPlayer->GetTeam();
                }

                switch (creature->GetEntry())
                {
                    case BOSS_BARON_ASHBURY:
                        _baronAshburyGUID = creature->GetGUID();
                        break;
                    case BOSS_BARON_SILVERLAINE:
                        _baronSilverlaineGUID = creature->GetGUID();
                        break;
                    case BOSS_COMMANDER_SPRINGVALE:
                        _commanderSpringvaleGUID = creature->GetGUID();
                        break;
                    case BOSS_LORD_WALDEN:
                        _lordWaldenGUID = creature->GetGUID();
                        break;
                    case BOSS_LORD_GODFREY:
                        _lordGodfreyGUID = creature->GetGUID();
                        break;
                    case 47293:
                    {
                        if (ServerAllowsTwoSideGroups())
                            creature->setFaction(FACTION_FRIENDLY);
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(47006, ALLIANCE);
                        break;
                    }
                    case 47030:
                    {
                        if (ServerAllowsTwoSideGroups())
                            creature->setFaction(FACTION_FRIENDLY);
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(47027, ALLIANCE);
                        break;
                    }
                    case 47031:
                    {
                        if (ServerAllowsTwoSideGroups())
                            creature->setFaction(FACTION_FRIENDLY);
                        if (TeamInInstance == ALLIANCE)
                            creature->SetVisible(false);
                        break;
                    }
                    case 47294:
                    {
                        if (ServerAllowsTwoSideGroups())
                            creature->setFaction(FACTION_FRIENDLY);
                        if (TeamInInstance == ALLIANCE)
                            creature->SetVisible(false);
                        break;
                    }
                    case 23837:
                        if (TeamInInstance == ALLIANCE)
                            creature->SetVisible(false);
                        break;
                    case 47865:
                        if (TeamInInstance == ALLIANCE)
                            creature->SetVisible(false);
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_COURTYARD_DOOR:
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
                    case GO_COURTYARD_DOOR:
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
                    case DATA_BARON_ASHBURY:
                        return _baronAshburyGUID;
                    case DATA_BARON_SILVERLAINE:
                        return _baronSilverlaineGUID;
                    case DATA_COMMANDER_SPRINGVALE:
                        return _commanderSpringvaleGUID;
                    case DATA_LORD_WALDEN:
                        return _lordWaldenGUID;
                    case DATA_LORD_GODFREY:
                        return _lordGodfreyGUID;
                    default:
                        break;
                }
                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "S F K " << GetBossSaveData();

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

                if (dataHead1 == 'S' && dataHead2 == 'F' && dataHead3 == 'K')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

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
            return new instance_shadowfang_keep_InstanceScript(map);
        }
};

void AddSC_instance_shadowfang_keep()
{
    new instance_shadowfang_keep();
}
