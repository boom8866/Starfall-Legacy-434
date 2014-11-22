
#include "bastion_of_twilight.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_ABILITY = 2,
    SAY_DEATH   = 3,
};

enum Spells
{
};

enum Events
{
};

enum Actions
{
};

class boss_feludius : public CreatureScript
{
    public:
        boss_feludius() : CreatureScript("boss_feludius") { }

        struct boss_feludiusAI : public BossAI
        {
            boss_feludiusAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL)
            {
            }

            void Reset()
            {
            }

            void EnterEvadeMode()
            {
            }

            void EnterCombat(Unit* /*who*/)
            {
            }


            void JustSummoned(Creature* summon)
            {
            }

            void KilledUnit(Unit* /*victim*/)
            {
            }

            void DamageTaken(Unit* /*who*/, uint32& damage)
            {
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;
            }
        };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_feludiusAI(creature);
    }
};

class npc_ascendant_council_controller : public CreatureScript
{
public:
    npc_ascendant_council_controller() : CreatureScript("npc_ascendant_council_controller") { }

    struct npc_ascendant_council_controllerAI : public ScriptedAI
    {
        npc_ascendant_council_controllerAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        SummonList summons;
        EventMap events;
        bool started;

        void Reset()
        {
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void DoAction(int32 action)
        {
        }


        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ascendant_council_controllerAI(creature);
    }
};


void AddSC_boss_ascendant_council()
{
    new boss_feludius();
    new npc_ascendant_council_controller();
}
