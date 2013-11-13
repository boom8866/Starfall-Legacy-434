#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "halls_of_origination.h"

enum Spells
{
    //Ammunae
    SPELL_WITHER                        = 76043,

    SPELL_CONSUME_LIFE_ENERGY           = 75725,
    SPELL_CONSUME_LIFE_ENERGY_LEECH     = 79768,
    SPELL_CONSUME_LIFE_ENERGY_BURN      = 75666,
    SPELL_CONSUME_LIFE_ENERGY_ENERGIZE  = 75665,

    SPELL_RAMPANT_GROWTH                = 75790,
    SPELL_SUMMON_BLODPETAL_BLOSSOM      = 75774,

    //Seeding Pod
    SPELL_ENERGIZE              = 75657,
    SPELL_ENERGIZING_GROWTH     = 89123,

    //Bloodpetal
    SPELL_THORN_SLASH           = 76044,

    //Spore
    SPELL_NOXIOUS_SPORE         = 75702,
    SPELL_SPORE_CLOUD           = 75701,
};

enum AmunaeTexts
{
    SAY_AGGRO   = 0,
    SAY_GROWTH  = 1,
    SAY_SLAY    = 2,
    SAY_DEATH   = 3,
};

enum Events
{
    //Ammunae
    EVENT_WITHER = 1,
    EVENT_CONSUME_LIFE_ENERGY,
    EVENT_RAMPANT_GROWTH,
    EVENT_RAMPANT_GROWTH_SUMMON,
    EVENT_SUMMON_POD,
    EVENT_SUMMON_SPORE,
    EVENT_ENERGY_TICKER,
    EVENT_ENERGY_TICKER_STOP,
    EVENT_COMBAT,

    //Blossom
    EVENT_THORN_SLASH,
    EVENT_EMERGE,
    EVENT_ATTACK,

    //Seedling Pod
    EVENT_ENERGIZE,
};

class boss_ammunae : public CreatureScript
{
    public:
        boss_ammunae() : CreatureScript("boss_ammunae") { }

        struct boss_ammunaeAI : public BossAI
        {
            boss_ammunaeAI(Creature* creature) : BossAI(creature, DATA_AMMUNAE)
            {
            }

            void Reset()
            {
                _Reset();
                me->SetPower(POWER_ENERGY, 0);
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_WITHER, 7000);
                events.ScheduleEvent(EVENT_CONSUME_LIFE_ENERGY, 20000);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_WITHER:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_WITHER);
                            events.ScheduleEvent(EVENT_WITHER, urand(20000, 22000));
                            break;
                        case EVENT_CONSUME_LIFE_ENERGY:
                            DoCastAOE(SPELL_CONSUME_LIFE_ENERGY);
                            events.ScheduleEvent(EVENT_CONSUME_LIFE_ENERGY, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void JustDied(Unit* /*who*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetPower(POWER_ENERGY, 0);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ammunaeAI(creature);
        }
};

class npc_hoo_bloodpetal_blossom : public CreatureScript
{
public:
    npc_hoo_bloodpetal_blossom() : CreatureScript("npc_hoo_bloodpetal_blossom") { }

    struct npc_hoo_bloodpetal_blossomAI : public ScriptedAI
    {
        npc_hoo_bloodpetal_blossomAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 0:
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_bloodpetal_blossomAI(creature);
    }
};

class npc_hoo_seed_pod : public CreatureScript
{
public:
    npc_hoo_seed_pod() : CreatureScript("npc_hoo_seed_pod") { }

    struct npc_hoo_seed_podAI : public ScriptedAI
    {
        npc_hoo_seed_podAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 0:
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_seed_podAI(creature);
    }
};

class npc_hoo_spore : public CreatureScript
{
public:
    npc_hoo_spore() : CreatureScript("npc_hoo_spore") { }

    struct npc_hoo_sporeAI : public ScriptedAI
    {
        npc_hoo_sporeAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void IsSummonedBy(Unit* creator)
        {
        }

        void UpdateAI(uint32 diff)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_sporeAI(creature);
    }
};

class spell_hoo_consume_life_energy : public SpellScriptLoader
{
public:
    spell_hoo_consume_life_energy() : SpellScriptLoader("spell_hoo_consume_life_energy") { }

    class spell_hoo_consume_life_energy_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_consume_life_energy_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        caster->CastSpell(caster, SPELL_CONSUME_LIFE_ENERGY_ENERGIZE);
                        caster->CastSpell(target, SPELL_CONSUME_LIFE_ENERGY_LEECH);
                        caster->CastSpell(target, SPELL_CONSUME_LIFE_ENERGY_BURN);
                    }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_hoo_consume_life_energy_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_consume_life_energy_SpellScript();
    }
};

void AddSC_boss_ammunae()
{
    new boss_ammunae;
    new npc_hoo_bloodpetal_blossom;
    new npc_hoo_seed_pod;
    new npc_hoo_spore;
    new spell_hoo_consume_life_energy;
}
