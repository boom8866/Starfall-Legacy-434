
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
    // Magmaw
    SPELL_MAGMA_SPIT                = 78359,
    SPELL_MAGMA_SPIT_NO_TARGET      = 78068,
    SPELL_PILLAR_OF_FLAME_AOE       = 77998,
    SPELL_PILLAR_OF_FLAME_MISSILE   = 78010,
    SPELL_LAVA_SPEW                 = 77839,

    // Exposed Head of Magmaw
    SPELL_POINT_OF_VULNERABILITY    = 79011,
    SPELL_RIDE_VEHICLE              = 89743,

    // Pincers
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,

    // Pillar of Flame
    SPELL_PILLAR_OF_FLAME_DUMMY     = 78017,
    SPELL_PILLAR_OF_FLAME_SUMMON    = 77973,

    // Lava Parasite
    SPELL_PARASITIC_INFECTION_1     = 78097,
    SPELL_PARASITIC_INFECTION_2     = 78941,
    SPELL_LAVA_PARASITE             = 78020,
};

enum Events
{
    EVENT_MAGMA_SPIT = 1,
    EVENT_PILLAR_OF_FLAME,
    EVENT_LAVA_SPEW,
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
        boss_magmawAI(Creature* creature) : BossAI(creature, DATA_MAGMAW), vehicle(creature->GetVehicleKit())
        {
        }

        Vehicle* vehicle;

        void Reset()
        {
            _Reset();
            SetCombatMovement(false);
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_MAGMA_SPIT, 10000);
            events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000);
            events.ScheduleEvent(EVENT_LAVA_SPEW, 18000);
        }

        void JustDied(Unit* killer)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            if (Unit* head = me->GetVehicleKit()->GetPassenger(3))
                head->ToCreature()->AI()->EnterEvadeMode();
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_PILLAR_OF_FLAME_DUMMY:
                    DoCast(SPELL_PILLAR_OF_FLAME_MISSILE);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_PILLAR_OF_FLAME_MISSILE:
                    target->CastSpell(target, SPELL_PILLAR_OF_FLAME_SUMMON);
                    target->ToCreature()->DespawnOrUnsummon(2600);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_MAGMA_SPIT:
                    {
                        Map::PlayerList const& playerList = me->GetMap()->GetPlayers();

                        if (playerList.isEmpty())
                            return;

                        for (uint8 i = 0; i <= (Is25ManRaid() ? 8 : 3); i++)
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, i))
                            {
                                if (!me->IsWithinDistInMap(me->getVictim(), me->GetFloatValue(UNIT_FIELD_COMBATREACH)))
                                    DoCast(target, SPELL_MAGMA_SPIT_NO_TARGET);
                                else
                                    DoCast(target, SPELL_MAGMA_SPIT);
                            }
                        }
                        events.ScheduleEvent(EVENT_MAGMA_SPIT, 10000);
                        break;
                    }
                    case EVENT_PILLAR_OF_FLAME:
                        DoCast(SPELL_PILLAR_OF_FLAME_AOE);
                        events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000, 40000);
                        break;
                    case EVENT_LAVA_SPEW:
                        DoCast(SPELL_LAVA_SPEW);
                        events.ScheduleEvent(EVENT_LAVA_SPEW, 22000);
                        break;
                    default:
                        break;
                }
            }
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
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if (Creature* magmaw = me->GetCreature(*me, instance->GetData64(BOSS_MAGMAW)))
            {
                uint32 newdamage = damage * 2;
                magmaw->DealDamage(magmaw, newdamage);
            }
        }
         
        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_exposed_head_of_magmawAI (creature);
    }
};

class npc_bwd_pillar_of_flame : public CreatureScript
{
public:
    npc_bwd_pillar_of_flame() : CreatureScript("npc_bwd_pillar_of_flame") { }

    struct npc_bwd_pillar_of_flameAI : public ScriptedAI
    {
        npc_bwd_pillar_of_flameAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCast(SPELL_PILLAR_OF_FLAME_DUMMY);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bwd_pillar_of_flameAI (creature);
    }
};

class npc_bwd_lava_parasite : public CreatureScript
{
public:
    npc_bwd_lava_parasite() : CreatureScript("npc_bwd_lava_parasite") { }

    struct npc_bwd_lava_parasiteAI : public ScriptedAI
    {
        npc_bwd_lava_parasiteAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetInCombatWithZone();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(3000);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_PARASITIC_INFECTION_1:
                    me->DespawnOrUnsummon(100);
                    DoCast(target, SPELL_LAVA_PARASITE);
                    DoCast(target, SPELL_PARASITIC_INFECTION_2);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoSpellAttackIfReady(SPELL_PARASITIC_INFECTION_1);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bwd_lava_parasiteAI (creature);
    }
};

class spell_bwd_pillar_of_flame_aoe : public SpellScriptLoader
{
public:
    spell_bwd_pillar_of_flame_aoe() : SpellScriptLoader("spell_bwd_pillar_of_flame_aoe") { }

    class spell_bwd_pillar_of_flame_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bwd_pillar_of_flame_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            std::list<WorldObject*>::iterator it = targets.begin();

            while (it != targets.end())
            {
                if (!GetCaster())
                    return;

                WorldObject* unit = *it;

                if (!unit)
                    continue;

                if (unit->GetDistance2d(GetCaster()) <= 15.0f)
                    it = targets.erase(it);
                else
                    it++;
            }

            if (targets.size() != 0)
                Trinity::Containers::RandomResizeList(targets, 1);
            else
                targets.push_back(GetCaster()->ToCreature()->AI()->SelectTarget(SELECT_TARGET_NEAREST));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_bwd_pillar_of_flame_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bwd_pillar_of_flame_aoe_SpellScript();
    }
};

void AddSC_boss_magmaw()
{
    new boss_magmaw();
    new npc_exposed_head_of_magmaw();
    new npc_bwd_pillar_of_flame();
    new npc_bwd_lava_parasite();
    new spell_bwd_pillar_of_flame_aoe();
}
