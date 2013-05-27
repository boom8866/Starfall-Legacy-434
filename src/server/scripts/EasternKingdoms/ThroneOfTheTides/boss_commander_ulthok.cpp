
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"
#include "Vehicle.h"

enum Spells
{
    SPELL_ULTHOK_INTRO_STATE    = 76017,
    SPELL_ULTHOK_INTRO_JUMP     = 82960,
    SPELL_ULTHOK_INTRO_IMPACT   = 76018,
    SPELL_ULTHOK_INTRO_C_IMPACT = 76021,

    SPELL_CURSE_OF_FATIGUE      = 76094,
    SPELL_DARK_FISSURE          = 76047,
    SPELL_SQUEEZE               = 76026,
    SPELL_ENRAGE                = 76100,
    SPELL_PULL_TARGET           = 49576,
    SPELL_DARK_FISSURE_AURA     = 76066,
};

enum Events
{
    EVENT_CURSE_OF_FATIGUE      = 1,
    EVENT_DARK_FISSURE          = 2,
    EVENT_SQUEEZE               = 3,
    EVENT_ENRAGE                = 4,
};

enum Yells
{
    SAY_AGGRO,
    SAY_SQUEEZE,
    SAY_FISSURE,
    SAY_DEATH
};

#define GROUND_Z                   806.317f

class boss_commander_ulthok : public CreatureScript
{
public:
    boss_commander_ulthok() : CreatureScript("boss_commander_ulthok") { }

    struct boss_commander_ulthokAI : public BossAI
    {
        boss_commander_ulthokAI(Creature* creature) : BossAI(creature, DATA_COMMANDER_ULTHOK), isIntroDone(false)
        {
            creature->SetDisableGravity(true);
        }

        bool isIntroDone;

        void Reset()
        {
            _Reset();

            me->DespawnCreaturesInArea(NPC_DARK_FISSURE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            me->RemoveAllAuras();
            me->SetDisableGravity(false);

            me->DespawnCreaturesInArea(NPC_DARK_FISSURE);

            Talk(SAY_AGGRO);

            events.ScheduleEvent(EVENT_DARK_FISSURE, 20000);
            events.ScheduleEvent(EVENT_ENRAGE, 10000);
            events.ScheduleEvent(EVENT_SQUEEZE, 30000);
            events.ScheduleEvent(EVENT_CURSE_OF_FATIGUE, 14000);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);

            _JustDied();
        }

        void DoAction(int32 action)
        {
            if (action == INST_ACTION_START_ULTHOK_EVENT && !isIntroDone)
            {
                me->SetDisableGravity(false);
                isIntroDone = true;

                Position pos = *me;
                pos.m_positionZ = GROUND_Z;

                me->SetHomePosition(pos);

                if (Creature* trigger = me->FindNearestCreature(NPC_SHOCK_DEFENSE_TRIGGER, 20.f))
                    trigger->CastSpell(trigger, SPELL_ULTHOK_INTRO_C_IMPACT, true);

                DoCast(SPELL_ULTHOK_INTRO_JUMP);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DARK_FISSURE:
                    {
                        Talk(SAY_FISSURE);

                        DoCastVictim(SPELL_DARK_FISSURE);
                        events.ScheduleEvent(EVENT_DARK_FISSURE, 20000);
                        break;
                    }
                case EVENT_ENRAGE:
                    {
                        DoCast(me, SPELL_ENRAGE);
                        events.ScheduleEvent(EVENT_ENRAGE, 10000);
                        break;
                    }
                case EVENT_SQUEEZE:
                    {
                        Talk(SAY_SQUEEZE);

                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60, true))
                            DoCast(target, SPELL_SQUEEZE);

                        events.ScheduleEvent(EVENT_SQUEEZE, 30000);
                        break;
                    }
                case EVENT_CURSE_OF_FATIGUE:
                    {
                        DoCastVictim(SPELL_CURSE_OF_FATIGUE, true);
                        events.ScheduleEvent(EVENT_CURSE_OF_FATIGUE, 14000);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_commander_ulthokAI (creature);
    }
};

class ExactDistanceCheck
{
    public:
        ExactDistanceCheck(WorldObject* source, float dist) : _source(source), _dist(dist) {}

        bool operator()(WorldObject* unit)
        {
            return _source->GetExactDist2d(unit) > _dist;
        }

    private:
        WorldObject* _source;
        float _dist;
};

class spell_dark_fissure_heroic : public SpellScriptLoader
{
public:
    spell_dark_fissure_heroic() : SpellScriptLoader("spell_dark_fissure_heroic") { }

    class spell_dark_fissure_heroic_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dark_fissure_heroic_SpellScript);

        void CorrectRange(std::list<WorldObject*>& targets)
        {
            targets.remove_if(ExactDistanceCheck(GetCaster(), 7.0f * GetCaster()->GetFloatValue(OBJECT_FIELD_SCALE_X)));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dark_fissure_heroic_SpellScript::CorrectRange, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dark_fissure_heroic_SpellScript();
    }
};

class spell_ulthok_jump_impact : public SpellScriptLoader
{
public:
    spell_ulthok_jump_impact() : SpellScriptLoader("spell_ulthok_jump_impact") { }

    class spell_ulthok_jump_impact_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ulthok_jump_impact_SpellScript);

        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                caster->CastSpell(caster, SPELL_ULTHOK_INTRO_STATE, true);

                if (InstanceScript* instance = caster->GetInstanceScript())
                    if (GameObject* corales = ObjectAccessor::GetGameObject(*caster, instance->GetData64(GO_CORALES)))
                    {
                        corales->SendObjectDeSpawnAnim(corales->GetGUID());
                        corales->RemoveFromWorld();
                    }
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_ulthok_jump_impact_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ulthok_jump_impact_SpellScript();
    }
};

class spell_ulthok_squeeze : public SpellScriptLoader
{
public:
    spell_ulthok_squeeze() : SpellScriptLoader("spell_ulthok_squeeze") { }

    class spell_ulthok_squeeze_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ulthok_squeeze_AuraScript);

        void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                if (Unit* caster = GetCaster())
                    target->EnterVehicle(caster, 0);
        }

        void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Vehicle* vehicle = caster->GetVehicleKit())
                    vehicle->RemoveAllPassengers();
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_ulthok_squeeze_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_ulthok_squeeze_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ulthok_squeeze_AuraScript();
    }
};

void AddSC_boss_commander_ulthok()
{
    new boss_commander_ulthok();
    new spell_dark_fissure_heroic();
    new spell_ulthok_jump_impact();
    new spell_ulthok_squeeze();
}
