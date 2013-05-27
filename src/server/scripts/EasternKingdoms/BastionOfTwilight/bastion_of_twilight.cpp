/*Copyright (C) 2012 SkyMist Project.
*
* Script complete 60%. ToDo: yells, resonating crystal, visual for black blood (some npc runs with aura summ every 12 sec?)
*
* This file is NOT free software. Third-party users can NOT redistribute it or modify it :). 
* If you find it, you are either hacking something, or very lucky (presuming someone else managed to hack it).
*/

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

enum Says
{
};

class npc_chogall_halfus : public CreatureScript // 49580
{
public:
    npc_chogall_halfus() : CreatureScript("npc_chogall_halfus") { }

    struct npc_chogall_halfusAI : public ScriptedAI
    {
        npc_chogall_halfusAI(Creature* creature) : ScriptedAI(creature)
        {
            timer = 1000;
            introSaid = false;
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        uint32 timer;
        bool introSaid;

        void UpdateAI(uint32 diff) 
        {
            if (timer <= diff)
            {
                if (Player* target = me->FindNearestPlayer(20.0f, true))
                {
                    if (target->GetDistance(me) <= 20.0f && !introSaid)
                    {
                        //if(!me->GetMap()->IsHeroic())
                            //Talk(SAY_INTRO_NORMAL);
                        //else
                            //Talk(SAY_INTRO_HEROIC);

                        introSaid = true;

                        me->DespawnOrUnsummon(15000);
                    } else
                        timer = 1000;
                }
                else
                    timer = 1000;

            } else timer -= diff;
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chogall_halfusAI(creature);
    }
};

class npc_chogall_valiona : public CreatureScript
{
public:
    npc_chogall_valiona() : CreatureScript("npc_chogall_valiona") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chogall_valionaAI (creature);
    }

    struct npc_chogall_valionaAI : public ScriptedAI
    {
        npc_chogall_valionaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    };
};

class npc_chogall_ascendants : public CreatureScript
{
public:
    npc_chogall_ascendants() : CreatureScript("npc_chogall_ascendants") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chogall_ascendantsAI (creature);
    }

    struct npc_chogall_ascendantsAI : public ScriptedAI
    {
        npc_chogall_ascendantsAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    };
};

void AddSC_bastion_of_twilight()
{
    new npc_chogall_halfus();
    new npc_chogall_valiona();
    new npc_chogall_ascendants();
}