
#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "blackwing_descent.h"

enum Spells
{
    // Exposed Head of Magmaw
    SPELL_POINT_OF_VULNERABILITY    = 79011,
    SPELL_RIDE_VEHICLE              = 89743,

    // Pincers
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
};

enum Events
{
    EVENT_MAGMA_SPIT = 1,
    EVENT_PILLAR_OF_FLAME,
};

enum PassengerSeats
{
    PASSENGER_NPC_PINCER_R = 0,
    PASSENGER_NPC_PINCER_L,
    PASSENGER_PLAYER_MANGLE_TARGET,
    PASSENGER_NPC_HEAD,
    PASSENGER_UNK2,
    PASSENGER_UNK1,
};

class boss_magmaw : public CreatureScript
{
public:
    boss_magmaw() : CreatureScript("boss_magmaw") { }

    struct boss_magmawAI : public BossAI
    {
        boss_magmawAI(Creature* creature) : BossAI(creature, DATA_MAGMAW), vehicle(creature->GetVehicleKit()) { }

        Vehicle* vehicle;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case 0:
                    break;
                default:
                    break;
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
        }

        void JustDied(Unit* killer)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_magmawAI (creature);
    }
};

class npc_exposed_head_of_magmaw : public CreatureScript
{
public:
    npc_exposed_head_of_magmaw() : CreatureScript("npc_exposed_head_of_magmaw") { }

    struct npc_exposed_head_of_magmawAI : public ScriptedAI
    {
        npc_exposed_head_of_magmawAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()), vehicle(creature->GetVehicleKit()) {}

        InstanceScript* instance;
        Vehicle* vehicle;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if (Creature* magmaw = me->GetCreature(*me, instance->GetData64(BOSS_MAGMAW)))
            {
                uint32 newdamage = damage * 2;
                magmaw->DealDamage(magmaw, newdamage);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_exposed_head_of_magmawAI (creature);
    }
};

class npc_pillar_of_flame_trigger : public CreatureScript
{
public:
    npc_pillar_of_flame_trigger() : CreatureScript("npc_pillar_of_flame_trigger") { }

    struct npc_pillar_of_flame_triggerAI : public ScriptedAI
    {
        npc_pillar_of_flame_triggerAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
        }

        void IsSummonedBy(Unit* unit)
        {
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pillar_of_flame_triggerAI (creature);
    }
};

class npc_lava_parasite : public CreatureScript
{
public:
    npc_lava_parasite() : CreatureScript("npc_lava_parasite") { }

    struct npc_lava_parasiteAI : public ScriptedAI
    {
        npc_lava_parasiteAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetInCombatWithZone();
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
        return new npc_lava_parasiteAI (creature);
    }
};

void AddSC_boss_magmaw()
{
    new boss_magmaw();
    new npc_exposed_head_of_magmaw();
    new npc_pillar_of_flame_trigger();
    new npc_lava_parasite();
}
