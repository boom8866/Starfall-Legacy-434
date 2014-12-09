#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "halls_of_origination.h"

enum Spells
{
    //Ammunae
    SPELL_ZERO_ENERGY                   = 72242,
    SPELL_WITHER                        = 76043,

    SPELL_CONSUME_LIFE_ENERGY           = 75725,
    SPELL_CONSUME_LIFE_ENERGY_LEECH     = 79768,
    SPELL_CONSUME_LIFE_ENERGY_BURN      = 75666,
    SPELL_CONSUME_LIFE_ENERGY_ENERGIZE  = 75665,

    SPELL_RAMPANT_GROWTH                = 75790,
    SPELL_SUMMON_BLODPETAL_BLOSSOM      = 75774,

    //Seedling Pod
    SPELL_ENERGIZE                      = 75657,
    SPELL_ENERGIZING_GROWTH             = 75624,

    SPELL_SEEDLING_POD_VISUAL           = 75687, // casted by 2nd pod

    //Bloodpetal Blossom
    SPELL_THORN_SLASH                   = 76044,

    //Spore
    SPELL_NOXIOUS_SPORE                 = 75702,
    SPELL_SPORE_CLOUD                   = 75701,
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
    EVENT_APPLY_IMMUNITY,
    EVENT_CONSUME_LIFE_ENERGY,
    EVENT_SUMMON_SEEDLING_POD,

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
                MakeInterruptable(false);
                me->AddAura(SPELL_ZERO_ENERGY, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_WITHER, 7000);
                events.ScheduleEvent(EVENT_SUMMON_SEEDLING_POD, 7000);
                events.ScheduleEvent(EVENT_CONSUME_LIFE_ENERGY, 20000);
            }

            void JustReachedHome()
            {
                me->AddAura(SPELL_ZERO_ENERGY, me);
                me->SetPower(POWER_ENERGY, 0);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void EnterEvadeMode()
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->GetMotionMaster()->MoveTargetedHome();
                summons.DespawnAll();
                events.Reset();
                _EnterEvadeMode();
            }

            void JustDied(Unit* /*who*/)
            {
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                summons.DespawnAll();
                _JustDied();
            }

            void JustSummoned(Creature* summon)
            {
                switch (summon->GetEntry())
                {
                    case NPC_SEEDLING_POD_1:
                        summon->AI()->DoCast(SPELL_ENERGIZE);
                        summon->AI()->DoCast(SPELL_ENERGIZING_GROWTH);
                        summons.Summon(summon);
                        break;
                    case NPC_SEEDLING_POD_2:
                        summon->AI()->DoCast(SPELL_SEEDLING_POD_VISUAL);
                        summons.Summon(summon);
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

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_WITHER:
                            MakeInterruptable(true);
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_WITHER);
                            events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 1500);
                            events.ScheduleEvent(EVENT_WITHER, 20500);
                            break;
                        case EVENT_APPLY_IMMUNITY:
                            MakeInterruptable(false);
                            break;
                        case EVENT_CONSUME_LIFE_ENERGY:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_CONSUME_LIFE_ENERGY);
                            events.ScheduleEvent(EVENT_CONSUME_LIFE_ENERGY, 10500);
                            break;
                        case EVENT_SUMMON_SEEDLING_POD:
                        {
                            float ori = frand(0.0f, M_PI * 2);
                            float distance = me->GetFloatValue(UNIT_FIELD_COMBATREACH) + 14.0f;
                            float x = me->GetPositionX() + cos(ori) * distance;
                            float y = me->GetPositionY() + sin(ori) * distance;
                            float z = me->GetPositionZ();
                            me->SummonCreature(NPC_SEEDLING_POD_1, x, y, z, ori, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_SEEDLING_POD_2, x, y, z, ori, TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_SUMMON_SEEDLING_POD, 7200);
                            break;
                        }
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void MakeInterruptable(bool apply)
            {
                if (apply)
                {
                    me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                }
                else
                {
                    me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                }
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

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetInCombatWithZone();
        }

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
