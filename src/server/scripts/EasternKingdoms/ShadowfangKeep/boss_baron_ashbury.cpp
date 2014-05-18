
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
    SPELL_WRACKING_PAIN             = 93720,
    SPELL_DARK_ARCHANGEL            = 93757,
    SPELL_CALAMITY_CHANNEL          = 93812,

    // Wings
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
    SPELL_CALAMITY_AURA             = 93766,
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
    EVENT_WRACKING_PAIN,
    EVENT_DARK_ARCHANGEL,
    EVENT_ROOT_PLAYERS,
    EVENT_APPLY_IMMUNITY,
};

class boss_baron_ashbury : public CreatureScript
{
public:
    boss_baron_ashbury() : CreatureScript("boss_baron_ashbury") { }

    struct boss_baron_ashburyAI : public BossAI
    {
        boss_baron_ashburyAI(Creature* creature) : BossAI(creature, DATA_BARON_ASHBURY)
        {
            _isArchangel = false;
            _canAttack = true;
        }

        bool _isArchangel;
        bool _canAttack;

        void Reset()
        {
            _Reset();
            _isArchangel = false;
            _canAttack = true;
            me->SetReactState(REACT_PASSIVE);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_ASPHYXIATE, 20000);
            events.ScheduleEvent(EVENT_PAIN_AND_SUFFERING, 5500);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_WRACKING_PAIN, 14000);
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
            _isArchangel = false;
            _canAttack = true;
            summons.DespawnAll();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WRACKING_PAIN);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(25) && !_isArchangel && !me->HasUnitState(UNIT_STATE_CASTING) && IsHeroic())
            {
                events.Reset();
                events.ScheduleEvent(EVENT_DARK_ARCHANGEL, 1);
                _isArchangel = true;
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
                    case EVENT_ASPHYXIATE:
                        Talk(SAY_ASPHYXIATE);
                        DoCastAOE(SPELL_ASPHYXIATE);
                        events.ScheduleEvent(EVENT_ROOT_PLAYERS, 1000);
                        events.ScheduleEvent(EVENT_STAY_OF_EXECUTION, 7000);
                        _canAttack = false;
                        break;
                    case EVENT_ROOT_PLAYERS:          
                    {
                        Map::PlayerList const& player = me->GetMap()->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = player.begin(); itr != player.end(); ++itr)
                            if (Player* player = itr->getSource())
                                player->AddAura(SPELL_ASPHYXIATE_ROOT, player);
                        break;
                    }
                    case EVENT_STAY_OF_EXECUTION:
                        if (IsHeroic())
                        {
                            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                            events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 8100);
                        }
                        Talk(SAY_STAY_EXECUTION);
                        Talk(SAY_ANNOUNCE_STAY);
                        DoCastAOE(SPELL_STAY_OF_EXECUTION);
                        events.ScheduleEvent(EVENT_ASPHYXIATE, 45000);
                        _canAttack = true;
                        break;
                    case EVENT_PAIN_AND_SUFFERING:
                        if (!me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                        }
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            DoCast(target, SPELL_PAIN_AND_SUFFERING);
                        }
                        events.ScheduleEvent(EVENT_PAIN_AND_SUFFERING, 26500);
                        break;
                    case EVENT_WRACKING_PAIN:
                        DoCastAOE(SPELL_WRACKING_PAIN);
                        events.ScheduleEvent(EVENT_WRACKING_PAIN, 26500);
                        break;
                    case EVENT_DARK_ARCHANGEL:
                    {
                        Talk(SAY_ARCHANGEL);
                        me->CastStop();
                        DoCastAOE(SPELL_DARK_ARCHANGEL);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                        if (Creature* wings = me->SummonCreature(NPC_ASHBURY_WINGS, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN))
                            wings->CastSpell(me, SPELL_RIDE_VEHICLE_HARDCODED);
                        break;
                    case EVENT_APPLY_IMMUNITY:
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                        break;
                    }
                    default:
                        break;
                }
            }
            if (_canAttack)
                DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WRACKING_PAIN);
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
                uint64 damage;
                if (Unit* target = GetHitPlayer())
                {
                    damage = target->GetMaxHealth() / GetSpellInfo()->GetMaxTicks();
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

class spell_sfk_pain_and_suffering : public SpellScriptLoader
{
    public:
        spell_sfk_pain_and_suffering() : SpellScriptLoader("spell_sfk_pain_and_suffering") { }

        class spell_sfk_pain_and_suffering_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sfk_pain_and_suffering_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                if (Unit* owner = GetOwner()->ToUnit())
                    if (Creature* ashbury = owner->FindNearestCreature(BOSS_BARON_ASHBURY, 100.0f, true))
                        owner->CastSpell(ashbury, SPELL_PAIN_AND_SUFFERING_DUMMY, false);

                uint64 damage;
                damage = aurEff->GetBaseAmount() * aurEff->GetTickNumber();
                this->GetEffect(EFFECT_0)->ChangeAmount(damage);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sfk_pain_and_suffering_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sfk_pain_and_suffering_AuraScript();
        }
};

void AddSC_boss_baron_ashbury()
{
    new boss_baron_ashbury();
    new spell_sfk_asphyxiate_damage();
    new spell_sfk_pain_and_suffering();
}
