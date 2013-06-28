
#include "shadowfang_keep.h"

enum Spells
{
    // Baron Ashbury
    SPELL_ASPHYXIATE                = 93423,
    SPELL_ASPHYXIATE_ROOT           = 93422,
    SPELL_ASPHYXIATE_DAMAGE         = 93424,
    SPELL_STAY_OF_EXECUTION         = 93468,
    SPELL_PAIN_AND_SUFFERING        = 93581,
    SPELL_PAIN_AND_SUFFERING_DUMMY  = 93605,

    // Wings
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
};

enum Texts
{
    SAY_AGGRO           = 1,
    SAY_ASPHYXIATE      = 2,
    SAY_ANNOUNCE_STAY   = 3,
    SAY_STAY_EXECUTION  = 4,
    SAY_ARCHANGEL       = 5,
    SAY_DEATH           = 6,
};

enum Events
{
    EVENT_ASPHYXIATE = 1,
    EVENT_STAY_OF_EXECUTION,
    EVENT_PAIN_AND_SUFFERING,
};

class boss_baron_ashbury : public CreatureScript
{
public:
    boss_baron_ashbury() : CreatureScript("boss_baron_ashbury") { }

    struct boss_baron_ashburyAI : public BossAI
    {
        boss_baron_ashburyAI(Creature* creature) : BossAI(creature, DATA_BARON_ASHBURY)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void Reset()
        {
            _Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_ASPHYXIATE, 20000);
            events.ScheduleEvent(EVENT_PAIN_AND_SUFFERING, 6500);
        }

        void SpellHitUnit(Unit* unit, const SpellEntry* spell)
        {
            if (unit->GetTypeId() == TYPEID_PLAYER)
                if (spell->Id == SPELL_ASPHYXIATE)
                    unit->AddAura(SPELL_ASPHYXIATE_ROOT, unit);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_PASSIVE);
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
                    case EVENT_ASPHYXIATE:
                        Talk(SAY_ASPHYXIATE);
                        DoCastAOE(SPELL_ASPHYXIATE);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        events.ScheduleEvent(EVENT_STAY_OF_EXECUTION, 7000);
                        break;
                    case EVENT_STAY_OF_EXECUTION:
                        Talk(SAY_STAY_EXECUTION);
                        Talk(SAY_ANNOUNCE_STAY);
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoCastAOE(SPELL_STAY_OF_EXECUTION);
                        events.ScheduleEvent(EVENT_ASPHYXIATE, 20000);
                        break;
                    case EVENT_PAIN_AND_SUFFERING:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_PAIN_AND_SUFFERING);

                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            Talk(SAY_DEATH);
        }
    };
    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_baron_ashburyAI (creature);
    }
};

class spell_sfk_asphyxiate_damage : public SpellScriptLoader
{
    public:
        spell_sfk_asphyxiate_damage() : SpellScriptLoader("spell_sfk_asphyxiate_damage") { }

        class spell_sfk_asphyxiate_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sfk_asphyxiate_damage_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ASPHYXIATE_DAMAGE))
                    return false;
                return true;
            }

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                uint32 damage;
                if (Unit* target = GetHitPlayer())
                {
                    damage = target->GetMaxHealth() / 6;
                    if (damage > target->GetHealth())
                        damage = target->GetHealth() - 1;

                    SetHitDamage(damage);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sfk_asphyxiate_damage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sfk_asphyxiate_damage_SpellScript();
        }
};

void AddSC_boss_baron_ashbury()
{
    new boss_baron_ashbury();
    new spell_sfk_asphyxiate_damage();
}
