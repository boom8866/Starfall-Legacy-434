
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "stormwind_jail.h"
#include "TemporarySummon.h"

class instance_stormwind_jail : public InstanceMapScript
{
public:
    instance_stormwind_jail() : InstanceMapScript("instance_stormwind_jail", 34) { }

    struct instance_stormwind_jail_InstanceScript : public InstanceScript
    {
        instance_stormwind_jail_InstanceScript(Map* map) : InstanceScript(map)
        {
            Initialize();
        }

        uint64 _randolphGUID;
        uint64 _lordOverheatGUID;
        uint64 _hoggerGUID;

        uint32 _instanceFaction;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
            _randolphGUID = 0;
            _lordOverheatGUID = 0;
            _hoggerGUID = 0;

            _instanceFaction = 0;
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
                case BOSS_RANDOLPH_MOLOCH:
                    _randolphGUID = creature->GetGUID();
                    break;
                case BOSS_LORD_OVERHEAT:
                    _lordOverheatGUID = creature->GetGUID();
                    break;
                case BOSS_HOGGER:
                    _hoggerGUID = creature->GetGUID();
                    break;
                case NPC_STOCKADE_GUARD:
                case NPC_STOCKADE_RIFLEMAN:
                case NPC_INJURED_STOCKADE_GUARD:
                case NPC_INJURED_STOCKADE_RIFLEMAN:
                case NPC_NURSE_LILLIAN:
                case NPC_LILLIANS_LIGHTWELL:
                case NPC_MORTIMER_MOLOCH:
                case NPC_WARDEN_THELWATER:
                case NPC_RIFLE_COMMANDER_COE:
                    if (TeamInInstance == HORDE)
                        creature->SetVisible(false);
                    break;
                default:
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
        }

        void OnGameObjectRemove(GameObject* go)
        {
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
                case DATA_RANDOLPH_MOLOCH:
                    return _randolphGUID;
                    break;
                case DATA_LORD_OVERHEAT:
                    return _lordOverheatGUID;
                    break;
                case DATA_HOGGER:
                    return _hoggerGUID;
                    break;
                default:
                    break;
            }
            return 0;
        }


        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "S J " << GetBossSaveData() << " " <<_instanceFaction;

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


            if (dataHead1 == 'S' && dataHead2 == 'J')
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
        return new instance_stormwind_jail_InstanceScript(map);
    }
};

void AddSC_instance_stormwind_jail()
{
    new instance_stormwind_jail();
}
