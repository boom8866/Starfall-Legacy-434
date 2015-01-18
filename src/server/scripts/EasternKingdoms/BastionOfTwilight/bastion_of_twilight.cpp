#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

enum TwisterMisc
{
    SPELL_PHASED_BURN   = 85799,
    SPELL_TWIST_PHASE   = 84737,
};

class npc_twilight_phase_twister : public CreatureScript
{
public:
    npc_twilight_phase_twister() : CreatureScript("npc_twilight_phase_twister") { }

    struct npc_twilight_phase_twisterAI : public ScriptedAI
    {
        npc_twilight_phase_twisterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void UpdateAI(uint32 diff) 
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_phase_twisterAI(creature);
    }
};

void AddSC_bastion_of_twilight()
{
    new npc_twilight_phase_twister();
}
