
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

class instance_blackrock_caverns : public InstanceMapScript
{
public:
    instance_blackrock_caverns() : InstanceMapScript("instance_blackrock_caverns", 645) { }

    struct instance_blackrock_cavernsInstanceMapScript : public InstanceScript
    {
        instance_blackrock_cavernsInstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        uint64 uiRomoggBonecrusher;
        uint64 uiCorla;
        uint64 uiKarshSteelbender;
        uint64 uiBeauty;
        uint64 uiAscendantLordObsidius;
        uint64 uiRazTheCrazed;
        uint64 uiFinkleEinhorn;
        uint64 uiNetherEssenceTrigger;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);

            uiRomoggBonecrusher     = 0;
            uiCorla                 = 0;
            uiKarshSteelbender      = 0;
            uiBeauty                = 0;
            uiAscendantLordObsidius = 0;
            uiRazTheCrazed          = 0;
            uiFinkleEinhorn         = 0;
            uiNetherEssenceTrigger  = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_ROMOGG_BONECRUSHER:
                    uiRomoggBonecrusher = creature->GetGUID();
                    break;
                case BOSS_CORLA:
                    uiCorla = creature->GetGUID();
                    break;
                case BOSS_KARSH_STEELBENDER:
                    uiKarshSteelbender = creature->GetGUID();
                    break;
                case BOSS_BEAUTY:
                    uiBeauty = creature->GetGUID();
                    break;
                case BOSS_ASCENDANT_LORD_OBSIDIUS:
                    uiAscendantLordObsidius = creature->GetGUID();
                    break;
                case NPC_RAZ_THE_CRAZED:
                    uiRazTheCrazed = creature->GetGUID();
                    break;
                case NPC_FINKLE_EINHORN:
                    if (creature->GetDistance(instancePositions[0]) < 20.f)
                        uiFinkleEinhorn = creature->GetGUID();
                    break;
                case NPC_NETHER_ESSENCE_TRIGGER:
                    if (creature->GetDistance(instancePositions[1]) < 20.f)
                        uiNetherEssenceTrigger = creature->GetGUID();
                    break;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
                case BOSS_ROMOGG_BONECRUSHER:
                    return uiRomoggBonecrusher;
                case BOSS_CORLA:
                    return uiCorla;
                case BOSS_KARSH_STEELBENDER:
                    return uiKarshSteelbender;
                case BOSS_BEAUTY:
                    return uiBeauty;
                case BOSS_ASCENDANT_LORD_OBSIDIUS:
                    return uiAscendantLordObsidius;
                case NPC_RAZ_THE_CRAZED:
                    return uiRazTheCrazed;
                case NPC_FINKLE_EINHORN:
                    return uiFinkleEinhorn;
                case NPC_NETHER_ESSENCE_TRIGGER:
                    return uiNetherEssenceTrigger;
                default:
                    return 0;
            }
            
        }

        bool SetBossState(uint32 data, EncounterState state)
        {
            if (!InstanceScript::SetBossState(data, state))
                return false;

            if (state == DONE)
            {
                if (data == DATA_ROMOGG_BONECRUSHER)
                {
                    if (Creature* raz = instance->GetCreature(uiRazTheCrazed))
                        raz->AI()->DoAction(INST_ACTION_RAZ_START_EVENT);

                }
                else if (data == DATA_ASCENDANT_LORD_OBSIDIUS)
                {
                    if (Creature* finkle = instance->GetCreature(uiFinkleEinhorn))
                    {
                        finkle->SetPhaseMask(PHASEMASK_NORMAL, true);
                        finkle->GetMotionMaster()->MovePoint(0, instancePositions[2]);
                        finkle->AI()->Talk(0);
                    }
                }
            }
            return true;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "B C " << GetBossSaveData();

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

            if (dataHead1 == 'B' && dataHead2 == 'C')
            {
                for (uint8 i = 0; i < ENCOUNTER_COUNT; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }

            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_blackrock_cavernsInstanceMapScript(map);
    }
};

void AddSC_instance_blackrock_caverns()
{
    new instance_blackrock_caverns();
}
