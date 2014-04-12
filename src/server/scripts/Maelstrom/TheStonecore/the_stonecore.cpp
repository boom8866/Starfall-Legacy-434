
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "the_stonecore.h"

// 6076 - Corborus Event
class at_tsc_corborus_event : public AreaTriggerScript
{
public:
    at_tsc_corborus_event() : AreaTriggerScript("at_tsc_corborus_event") {}

    bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/)
    {
        if (InstanceScript* instance = player->GetInstanceScript())
        {
            if (!instance->GetData(DATA_CORBORUS_PRE_EVENT) && !player->isGameMaster())
                if (Creature* corborus = ObjectAccessor::GetCreature(*player, instance->GetData64(BOSS_CORBORUS)))
                {
                    instance->SetData(DATA_CORBORUS_PRE_EVENT, 1);
                    corborus->AI()->DoAction(ACTION_CORBORUS_DO_INTRO);

                    return true;
                }
        }

        return false;
    }
};

void AddSC_the_stonecore()
{
    new at_tsc_corborus_event();
}
