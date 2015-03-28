
#include "zulgurub.h"

enum TikiLordSpells
{
    SPELL_TIKI_TORCH = 96822,
};

class npc_tiki_lord_muloa : public CreatureScript
{
public:
    npc_tiki_lord_muloa() : CreatureScript("npc_tiki_lord_muloa") { }

    struct npc_tiki_lord_muloaAI : public ScriptedAI
    {
        npc_tiki_lord_muloaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoSpellAttackIfReady(SPELL_TIKI_TORCH);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tiki_lord_muloaAI(creature);
    }
};

void AddSC_zulgurub()
{
    new npc_tiki_lord_muloa();
}
