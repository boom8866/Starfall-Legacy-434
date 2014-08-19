#include "ScriptPCH.h"
#include "Vehicle.h"
#include "the_stonecore.h"

enum Texts
{
    SAY_AGGRO           = 0,
    SAY_THROW_BOULDER   = 1,
    SAY_SLAY            = 2,
    SAY_DEATH           = 3,
};


enum Spells
{
    // Azil
    SPELL_AZIL_VISUAL               = 85654,
    SPELL_ENERGY_SHIELD             = 82858,
    SPELL_SUMMON_GRAVITY_WELL       = 79340,
    SPELL_CURSE_OF_BLOOD            = 79345,

    SPELL_FORCE_GRIP                = 79351,
    SPELL_FORCE_GRIP_SCRIPT         = 79354,

    SPELL_FORCE_GRIP_SMASH          = 79359,
    SPELL_FORCE_GRIP_SMASH_SCRIPT   = 79357,

    SPELL_FORCE_GRIP_DAMAGE         = 79358,
    SPELL_FORCE_GRIP_DAMAGE_HC      = 92664,

    // Gravity Well
    SPELL_GRAVITY_WELL_VISUAL_1     = 79245,
    SPELL_GRAVITY_WELL_PULL         = 79332,
};

enum Events
{
    // Intro
    EVENT_MOVE_DOWN = 1,
    EVENT_ATTACK,

    // Azil
    EVENT_SUMMON_GRAVITY_WELL,
    EVENT_CURSE_OF_BLOOD,
    EVENT_FORCE_GRIP,
    EVENT_FORCE_GRIP_SMASH,
    EVENT_APPLY_IMMUNITY,
};

enum Points
{
    POINT_HOVER_UP = 1,
    POINT_HOVER_DOWN,
};

Position const TakeoffPos = {1335.648f, 971.510f, 217.951f, 1.824f};
Position const LandPos = {1333.195f, 980.509f, 208.039f, 1.816f};

class boss_high_priestess_azil : public CreatureScript
{
public:
    boss_high_priestess_azil() : CreatureScript("boss_high_priestess_azil") { }

    struct boss_high_priestess_azilAI : public BossAI
    {
        boss_high_priestess_azilAI(Creature* creature) : BossAI(creature, DATA_HIGH_PRIESTESS_AZIL), vehicle(creature->GetVehicleKit())
        {
            griped = false;
        }

        Vehicle* vehicle;
        bool griped;

        void Reset()
        {
            DoCast(me, SPELL_AZIL_VISUAL);
            me->SetReactState(REACT_PASSIVE);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            griped = false;
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            DoCastAOE(SPELL_ENERGY_SHIELD);
            events.ScheduleEvent(EVENT_MOVE_DOWN, 2100);
            events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, 10000);
            events.ScheduleEvent(EVENT_FORCE_GRIP, 15500);
            events.ScheduleEvent(EVENT_SUMMON_GRAVITY_WELL, 6000);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            _FinishDungeon();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            summons.DespawnAll();
            events.Reset();
            _EnterEvadeMode();
            _DespawnAtEvade();
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case POINT_HOVER_DOWN:
                    events.ScheduleEvent(EVENT_ATTACK, 1);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_FORCE_GRIP:
                    me->CastWithDelay(1000, target, SPELL_FORCE_GRIP_SMASH, true);
                    break;
                case SPELL_FORCE_GRIP_SMASH:
                    if (target->GetVehicleCreatureBase())
                    {
                        target->ChangeSeat(4);
                        me->CastWithDelay(1000, target, SPELL_FORCE_GRIP_DAMAGE, true);
                    }
                    break;
                case SPELL_FORCE_GRIP_DAMAGE:
                case SPELL_FORCE_GRIP_DAMAGE_HC:
                    if (target->GetVehicleCreatureBase())
                    {
                        target->ChangeSeat(3, false);
                        me->CastWithDelay(1000, target, SPELL_FORCE_GRIP_SMASH, true);
                    }
                    break;
                default:
                    break;
            }
        }

        void OnCharmed(bool apply)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !griped)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_DOWN:
                        me->GetMotionMaster()->MoveJump(LandPos, 5.0f, 15.0f, POINT_HOVER_DOWN);
                        break;
                    case EVENT_ATTACK:
                        me->RemoveAura(SPELL_ENERGY_SHIELD);
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    case EVENT_CURSE_OF_BLOOD:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_CURSE_OF_BLOOD);
                        events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, 17500);
                        break;
                    case EVENT_FORCE_GRIP:
                        griped = true;
                        DoCastVictim(SPELL_FORCE_GRIP);
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                        events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 6500);
                        break;
                    case EVENT_APPLY_IMMUNITY:
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                        break;
                    case EVENT_SUMMON_GRAVITY_WELL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_SUMMON_GRAVITY_WELL);
                        events.ScheduleEvent(EVENT_SUMMON_GRAVITY_WELL, urand(5000, 5500));
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
        return new boss_high_priestess_azilAI (creature);
    }
};



class spell_tsc_force_grip : public SpellScriptLoader
{
public:
    spell_tsc_force_grip() : SpellScriptLoader("spell_tsc_force_grip") { }

    class spell_tsc_force_grip_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tsc_force_grip_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* player = GetOwner()->ToUnit())
                    player->EnterVehicle(caster, 3);
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(3))
                    passenger->ExitVehicle();
                else if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(4))
                    passenger->ExitVehicle();
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_tsc_force_grip_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_tsc_force_grip_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tsc_force_grip_AuraScript();
    }
};

void AddSC_boss_high_priestess_azil()
{
    new boss_high_priestess_azil();
    new spell_tsc_force_grip();
}
