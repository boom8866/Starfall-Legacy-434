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
    SPELL_ENERGY_SHIELD             = 82858,
    SPELL_SUMMON_GRAVITY_WELL       = 79340,
    SPELL_CURSE_OF_BLOOD            = 79345,

    SPELL_FORCE_GRIP                = 79351,
    SPELL_FORCE_GRIP_SCRIPT         = 79354,

    SPELL_FORCE_GRIP_SMASH          = 79359,
    SPELL_FORCE_GRIP_SMASH_SCRIPT   = 79357,
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
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
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
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
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
            summons.DespawnAll();
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
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        break;
                    case EVENT_CURSE_OF_BLOOD:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_CURSE_OF_BLOOD);
                        events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, 17500);
                        break;
                    case EVENT_FORCE_GRIP:
                        griped = true;
                        DoCastVictim(SPELL_FORCE_GRIP);
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

    class spell_tsc_force_grip_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tsc_force_grip_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->EnterVehicle(GetCaster(), 4);
            //GetHitUnit()->CastSpell(GetCaster(), VEHICLE_SPELL_RIDE_HARDCODED, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_tsc_force_grip_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tsc_force_grip_SpellScript();
    }
};

/*
class spell_tsc_force_grip : public SpellScriptLoader
{
public:
    spell_tsc_force_grip() : SpellScriptLoader("spell_tsc_force_grip") { }

    class spell_tsc_force_grip_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tsc_force_grip_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*)
        {
            GetCaster()->CastSpell(GetHitUnit(), SPELL_INVOKE_SONS_MISSILE, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_tsc_force_grip_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tsc_force_grip_SpellScript();
    }
};
*/

void AddSC_boss_high_priestess_azil()
{
    new boss_high_priestess_azil();
    new spell_tsc_force_grip();
}
