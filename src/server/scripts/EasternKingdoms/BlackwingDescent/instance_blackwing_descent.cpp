
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "InstanceScript.h"
#include "Group.h"
#include "blackwing_descent.h"

class instance_blackwing_descent : public InstanceMapScript
{
public:
    instance_blackwing_descent() : InstanceMapScript("instance_blackwing_descent", 669) { }

    struct instance_blackwing_descent_InstanceMapScript : public InstanceScript
    {
        instance_blackwing_descent_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        // Magmaw
        uint64 uiMagmaw;
        uint64 uiMagmawsHead;
        uint64 uiSpikeStalker;

        // Omnotron Defense System
        uint64 uiOmnotron;
        uint64 uiArcanotron;
        uint64 uiElectron;
        uint64 uiMagmatron;
        uint64 uiToxitron;

        // Maloriak
        uint64 uiMaloriak;
        uint64 uiCauldronTrigger;
        std::set<uint64> uiInkubators;

        // Atramedes
        uint64 uiAtramedes;
        uint64 uiPreNefarian;
        uint64 uiPreAtramedes;
        uint64 uiPreMaloriak;

        // Chimaeron
        uint64 uiChimaeron;
        uint64 uiBileOTron;
        uint64 uiFinkleEinhorn;

        // Nefarian
        uint64 uiNefarian;
        uint64 uiOnyxia;

        uint64 uiNefariansHeroic[ENCOUNTER_COUNT];

        // Gobs
        uint64 gobPreBossDoor;
        uint64 gobMaloriaksCauldron;
        uint64 gobOnyxiaPlatform;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);

            // Magmaw
            uiMagmaw                = 0;
            uiMagmawsHead           = 0;
            uiSpikeStalker          = 0;

            // Omnotron Defense System
            uiOmnotron              = 0;
            uiArcanotron            = 0;
            uiElectron              = 0;
            uiMagmatron             = 0;
            uiToxitron              = 0;

            // Maloriak
            uiMaloriak              = 0;
            uiCauldronTrigger       = 0;

            // Atramedes
            uiAtramedes             = 0;
            uiPreNefarian           = 0;
            uiPreAtramedes          = 0;
            uiPreMaloriak           = 0;

            // Chimaeron
            uiChimaeron             = 0;
            uiBileOTron             = 0;
            uiFinkleEinhorn         = 0;

            // Nefarian
            uiNefarian              = 0;
            uiOnyxia                = 0;

            memset(&uiNefariansHeroic, 0, sizeof(uiNefariansHeroic));

            // Gobs
            gobPreBossDoor          = 0;
            gobMaloriaksCauldron    = 0;
            gobOnyxiaPlatform       = 0;           
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                // Magmaw
                case BOSS_MAGMAW: 
                    uiMagmaw = creature->GetGUID();
                    break;
                case NPC_MAGMAWS_HEAD: 
                    uiMagmawsHead = creature->GetGUID();
                    break;
                case NPC_SPIKE_STALKER:
                    uiSpikeStalker = creature->GetGUID();
                    break;
                    // Omnotron Defense System
                case BOSS_OMNOTRON: 
                    uiOmnotron = creature->GetGUID();
                    break;
                case NPC_ARCANOTRON: 
                    uiArcanotron = creature->GetGUID();
                    break;
                case NPC_ELECTRON: 
                    uiElectron = creature->GetGUID();
                    break;
                case NPC_MAGMATRON: 
                    uiMagmatron = creature->GetGUID();
                    break;
                case NPC_TOXITRON: 
                    uiToxitron = creature->GetGUID();
                    break;
                    // Maloriak
                case BOSS_MALORIAK: 
                    uiMaloriak = creature->GetGUID();
                    break;
                case NPC_CAULDRON_TRIGGER:
                    uiCauldronTrigger = creature->GetGUID();
                    break;
                    // Atramedes
                case BOSS_ATRAMEDES: 
                    uiAtramedes = creature->GetGUID();
                    break;
                case NPC_PRE_NEFARIAN: 
                    uiPreNefarian = creature->GetGUID();
                    break;
                case NPC_PRE_ATRAMEDES: 
                    uiPreAtramedes = creature->GetGUID();
                    break;
                case NPC_PRE_MALORIAK: 
                    uiPreMaloriak = creature->GetGUID();
                    break;
                    // Chimaeron
                case BOSS_CHIMAERON: 
                    uiChimaeron = creature->GetGUID();
                    break;
                case NPC_BILE_O_TRON: 
                    uiBileOTron = creature->GetGUID();
                    break;
                case NPC_FINKLE_EINHORN: 
                    uiFinkleEinhorn = creature->GetGUID();
                    break;
                    // Nefarian
                case BOSS_NEFARIAN: 
                    uiNefarian = creature->GetGUID();
                    break;
                case NPC_ONYXIA: 
                    uiOnyxia = creature->GetGUID();
                    break;
                    // Misc
                case NPC_NEFARIAN_STALKER: 
                    uiNefariansHeroic[DATA_MAGMAW] = creature->GetGUID();
                    break;
                case NPC_NEFRIAN_OMNOTRON_HC: 
                    uiNefariansHeroic[DATA_OMNOTRON_DEFENSE_SYSTEM] = creature->GetGUID();
                    break;
                case NPC_NEFRIAN_MALORIAK_HC: 
                    uiNefariansHeroic[DATA_MALORIAK] = creature->GetGUID();
                    break;
                case NPC_NEFRIAN_ATRAMEDES_HC: 
                    uiNefariansHeroic[DATA_ATRAMEDES] = creature->GetGUID();
                    break;
                case NPC_NEFARIAN_CHIMAERON: 
                    uiNefariansHeroic[DATA_CHIMAERON] = creature->GetGUID();
                    break;
                case NPC_LORD_VICTOR_NEFARIAN: 
                    uiNefariansHeroic[DATA_NEFARIAN] = creature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GOB_DOOR_PRE_BOSSES:
                    gobPreBossDoor = go->GetGUID();
                    HandleGameObject(NULL, CheckRequiredBosses(DATA_MALORIAK), go);
                    break;
                case GOB_MALORIAKS_CAULDRON:
                    gobMaloriaksCauldron = go->GetGUID();
                    break;
                case GOB_ONYXIA_PLATFORM:
                    gobOnyxiaPlatform = go->GetGUID();
                    break;
                case GOB_INKUBATOR:
                case GOB_BIG_INKUBATOR:
                    uiInkubators.insert(go->GetGUID());
                    break;
            }
        }

        bool CheckRequiredBosses(uint32 bossType, Player const* /*player*/ = NULL) const
        {
            switch (bossType)
            {
                case DATA_NEFARIAN:
                    return GetBossState(DATA_MALORIAK) == DONE && GetBossState(DATA_CHIMAERON) == DONE  && GetBossState(DATA_ATRAMEDES) == DONE;
                case DATA_ATRAMEDES:
                case DATA_CHIMAERON:
                case DATA_MALORIAK:
                    return /*GetBossState(DATA_MAGMAW)==DONE && */GetBossState(DATA_OMNOTRON_DEFENSE_SYSTEM)==DONE;
                default:
                    return true;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
                    // Magmaw
                case BOSS_MAGMAW:
                    return uiMagmaw; 
                case NPC_MAGMAWS_HEAD:
                    return uiMagmawsHead; 
                case NPC_SPIKE_STALKER:
                    return uiSpikeStalker;
                    // Omnotron Defense System
                case BOSS_OMNOTRON:
                    return uiOmnotron; 
                case NPC_ARCANOTRON:
                    return uiArcanotron; 
                case NPC_ELECTRON:
                    return uiElectron; 
                case NPC_MAGMATRON:
                    return uiMagmatron; 
                case NPC_TOXITRON:
                    return uiToxitron; 
                    // Maloriak
                case BOSS_MALORIAK:
                    return uiMaloriak; 
                case NPC_CAULDRON_TRIGGER:
                    return uiCauldronTrigger;
                    // Atramedes
                case BOSS_ATRAMEDES:
                    return uiAtramedes; 
                case NPC_PRE_NEFARIAN:
                    return uiPreNefarian; 
                case NPC_PRE_ATRAMEDES:
                    return uiPreAtramedes; 
                case NPC_PRE_MALORIAK:
                    return uiPreMaloriak;
                    // Chimaeron
                case BOSS_CHIMAERON:
                    return uiChimaeron; 
                case NPC_BILE_O_TRON: 
                    return uiBileOTron; 
                case NPC_FINKLE_EINHORN: 
                    return uiFinkleEinhorn; 
                    // Nefarian
                case BOSS_NEFARIAN:
                    return uiNefarian; 
                case NPC_ONYXIA:
                    return uiOnyxia; 
            }

            if (identifier < ENCOUNTER_COUNT)
                return uiNefariansHeroic[identifier];

            return NULL;
        }

        bool SetBossState(uint32 data, EncounterState state)
        {
            // Reset Bile-O-Tron to avoid Bugusing with Finkles Mixture
            if (data != DATA_CHIMAERON && state == IN_PROGRESS)
                if (Creature* bileotron = instance->GetCreature(uiBileOTron))
                    bileotron->AI()->DoAction(3);

            if (!InstanceScript::SetBossState(data, state))
                return false;

            if (state == DONE)
            {
                switch (data)
                {
                    case DATA_MAGMAW:
                    {
                        Map::PlayerList const &PlList = instance->GetPlayers();

                        for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                        {
                            if (i == PlList.begin())
                            {
                                Group* group = i->getSource()->GetGroup();
                                Player* groupLeader = NULL;
                                if (group)
                                    groupLeader = ObjectAccessor::GetPlayer(*i->getSource(), group->GetLeaderGUID());

                                if (!groupLeader)
                                    groupLeader = i->getSource();

                                ((InstanceMap*)instance)->PermBindAllPlayers(groupLeader);
                            }

                            i->getSource()->ModifyCurrency(396, 70);
                        }
                    }
                    case DATA_OMNOTRON_DEFENSE_SYSTEM:
                    {
                        HandleGameObject(gobPreBossDoor, CheckRequiredBosses(DATA_MALORIAK));
                        break;
                    }
                }
            }
            else
            {
                switch (data)
                {
                    case DATA_MALORIAK:
                    {
                        for (auto const& uiGo : uiInkubators)
                            if (GameObject* go = instance->GetGameObject(uiGo))
                                go->SetGoState(GO_STATE_READY);
                        break;
                    }
                }
            }
            return true;
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type == DATA_ACTIVATE_TRON && data)
                if (Creature* tron = instance->GetCreature(uiBileOTron))
                    tron->AI()->DoAction(1);
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "B D " << GetBossSaveData();

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

            if (dataHead1 == 'B' && dataHead2 == 'D')
            {
                for (uint8 i = 0; i < ENCOUNTER_COUNT; ++i)
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
        return new instance_blackwing_descent_InstanceMapScript(map);
    }
};

void AddSC_instance_blackwing_descent()
{
    new instance_blackwing_descent();
}
