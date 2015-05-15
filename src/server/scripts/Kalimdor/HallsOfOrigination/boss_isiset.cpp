/*
    Copyright 2014-2015 - Northstrider & john2308
*/

#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "halls_of_origination.h"

enum isisetYells
{
    SAY_AGGRO               = 0,
    SAY_SUPERNOVA,
    SAY_KILL,
    SAY_DEATH,
    SAY_SUPERNOVA_WARNING
};

enum isisetSpells
{
    SPELL_SUPERNOVA             = 74136,
    SPELL_ASTRAL_RAIN_FIRST     = 74134,
    SPELL_ASTRAL_RAIN_SECOND    = 74365,
    SPELL_ASTRAL_RAIN_THIRD     = 74371,
    SPELL_CELESTIAL_CALL_FIRST  = 74362,
    SPELL_CELESTIAL_CALL_SECOND = 74355,
    SPELL_CELESTIAL_CALL_THIRD  = 74364,
    SPELL_VEIL_OF_SKY_FIRST     = 74133,
    SPELL_VEIL_OF_SKY_SECOND    = 74372,
    SPELL_VEIL_OF_SKY_THIRD     = 74373,
    SPELL_ARCANE_BARRAGE_N      = 74374,
    SPELL_ARCANE_BARRAGE_H      = 89886,
    SPELL_VEIL_SKY_N            = 74133,
    SPELL_VEIL_SKY_H            = 90760,
    SPELL_VEIL_OF_SKY_REFLECT   = 79370,
    SPELL_CALL_OF_SKY           = 90750
};

enum isisetEvents
{
    EVENT_ASTRAL_RAIN_PHASE_ONE = 1,
    EVENT_ASTRAL_RAIN_PHASE_TWO,
    EVENT_ASTRAL_RAIN_PHASE_THREE,
    EVENT_CELESTIAL_CALL_PHASE_ONE,
    EVENT_CELESTIAL_CALL_PHASE_TWO,
    EVENT_CELESTIAL_CALL_PHASE_THREE,
    EVENT_VEIL_SKY_PHASE_ONE,
    EVENT_VEIL_SKY_PHASE_TWO,
    EVENT_VEIL_SKY_PHASE_THREE,
    EVENT_SUPERNOVA,
    EVENT_CHECK_PHASING_HEALTH
};

enum spellVisuals
{
    SPELL_STATE_ASTRAL_RAIN         = 74289,
    SPELL_ASTRAL_SHIFT_VISUAL       = 74333,
    SPELL_STARRY_SKY_VISUAL         = 74149,
    SPELL_FAMILIAR_VISUAL           = 74356,
};

enum actionId
{
    ACTION_HIDE_MIRROR  = 1,
    ACTION_CALL_MIRROR
};

enum phaseId
{
    PHASE_ONE   = 1,
    PHASE_TWO,
    PHASE_THREE
};

class boss_isiset : public CreatureScript
{
public:
    boss_isiset() : CreatureScript("boss_isiset")
    {
    }

    struct boss_isisetAI : public BossAI
    {
        boss_isisetAI(Creature* creature) : BossAI(creature, DATA_ISISET)
        {
            instance = creature->GetInstanceScript();
            SetCombatMovement(true);
        }

        InstanceScript* instance;
        EventMap events;
        std::list<uint64> SummonList;

        bool astralRain, veilSky, celestialCall;

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            events.SetPhase(1);
            astralRain = false;
            veilSky = false;
            celestialCall = false;
            me->SetVisible(true);
            Talk(SAY_AGGRO);

            // Init events for phase one
            events.ScheduleEvent(EVENT_ASTRAL_RAIN_PHASE_ONE, 3000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_CELESTIAL_CALL_PHASE_ONE, 5000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_VEIL_SKY_PHASE_ONE, 8000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_SUPERNOVA, 18000);
            events.ScheduleEvent(EVENT_CHECK_PHASING_HEALTH, 1);

            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            // Sniffs revealed this spell casted on enter combat
            DoCast(me, SPELL_CALL_OF_SKY);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_KILL);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            RemoveSummons();
            me->SetVisible(true);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_ISISET, FAIL);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetVisible(true);
            events.Reset();
            _DespawnAtEvade();
        }

        void Reset()
        {
            me->SetPhaseMask(3, true);
            RemoveSummons();
            me->SetVisible(true);
            astralRain = false;
            veilSky = false;
            celestialCall = false;
            _Reset();
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case 39720: // Mirror: Astral Rain
                    astralRain = false;
                    break;
                case 39721: // Mirror: Celestial Call
                    celestialCall = false;
                    break;
                case 39722: // Mirror: Veil of Sky
                    veilSky = false;
                    break;
                default:
                    break;
            }
        }

        void RemoveSummons()
        {
            if (SummonList.empty())
                return;

            for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                if (Creature* tempSummon = Unit::GetCreature(*me, *itr))
                    if (tempSummon)
                    {
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, tempSummon);
                        tempSummon->DisappearAndDie();
                    }

            SummonList.clear();
        }

        void JustSummoned(Creature* summon)
        {
            SummonList.push_back(summon->GetGUID());
            summon->AI()->DoZoneInCombat();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_HIDE_MIRROR:
                {
                    SwitchImagePhase(2);
                    me->SetVisible(true);
                    me->RemoveAllAuras();
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                    break;
                }
                case ACTION_CALL_MIRROR:
                {
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    events.CancelEventGroup(0);

                    me->StopMoving();
                    me->SendMovementFlagUpdate(false);
                    me->RemoveAllAuras();
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));

                    Position pos;
                    me->GetPosition(&pos);

                    if (events.IsInPhase(2))
                    {
                        me->SummonCreature(NPC_ASTRAL_RAIN, pos, TEMPSUMMON_CORPSE_DESPAWN, 1);
                        me->SummonCreature(NPC_CELESTIAL_CALL, pos, TEMPSUMMON_CORPSE_DESPAWN, 1);
                        me->SummonCreature(NPC_VEIL_OF_SKY, pos, TEMPSUMMON_CORPSE_DESPAWN, 1);

                        DoCast(me, SPELL_ASTRAL_SHIFT_VISUAL, true);

                        SwitchImagePhase(1);

                        astralRain = true;
                        veilSky = true;
                        celestialCall = true;

                        // Init events for phase two
                        events.ScheduleEvent(EVENT_ASTRAL_RAIN_PHASE_TWO, 3000, 0, PHASE_TWO);
                        events.ScheduleEvent(EVENT_CELESTIAL_CALL_PHASE_TWO, 5000, 0, PHASE_TWO);
                        events.ScheduleEvent(EVENT_VEIL_SKY_PHASE_TWO, 8000, 0, PHASE_TWO);
                        events.ScheduleEvent(EVENT_SUPERNOVA, 18000);
                        events.ScheduleEvent(EVENT_CHECK_PHASING_HEALTH, 1);
                    }

                    if (events.IsInPhase(3))
                    {
                        DoCast(me, SPELL_ASTRAL_SHIFT_VISUAL, true);

                        SwitchImagePhase(1);

                        // Init events for phase three
                        events.ScheduleEvent(EVENT_ASTRAL_RAIN_PHASE_THREE, 3000, 0, PHASE_THREE);
                        events.ScheduleEvent(EVENT_CELESTIAL_CALL_PHASE_THREE, 5000, 0, PHASE_THREE);
                        events.ScheduleEvent(EVENT_VEIL_SKY_PHASE_THREE, 8000, 0, PHASE_THREE);
                        events.ScheduleEvent(EVENT_SUPERNOVA, 18000);
                    }

                    me->SetVisible(false);
                    break;
                }
                default:
                    break;
            }
        }

        void SwitchImagePhase(uint32 phase)
        {
            std::list<Unit*> targets;
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if (!(*itr)->ToCreature())
                    continue;

                switch ((*itr)->ToCreature()->GetEntry())
                {
                    case NPC_VEIL_OF_SKY:
                    case NPC_CELESTIAL_CALL:
                    case NPC_ASTRAL_RAIN:
                    {
                        (*itr)->SetPhaseMask(phase, true);

                        if (phase == 2)
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, (*itr));
                        else
                        {
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, (*itr));
                            if (Creature* isiset = (*itr)->FindNearestCreature(BOSS_ISISET, 500.0f))
                            {
                                Position pos;
                                isiset->GetPosition(&pos);
                                (*itr)->NearTeleportTo(pos, true);
                                (*itr)->SetHealth((*itr)->GetMaxHealth());
                                (*itr)->SetPower((*itr)->getPowerType(), (*itr)->GetMaxPower((*itr)->getPowerType()));
                                (*itr)->RemoveAllAuras();
                            }
                        }
                        break;
                    }
                    default:
                        continue;
                }
            }        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || !CheckInRoom())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PHASING_HEALTH:
                    {
                        if (me->GetHealthPct() < 66 && me->isInCombat() && events.IsInPhase(1))
                        {
                            events.SetPhase(2);
                            events.CancelEvent(EVENT_CHECK_PHASING_HEALTH);
                            DoAction(ACTION_CALL_MIRROR);
                            break;
                        }
                        if (me->GetHealthPct() < 33 && me->isInCombat() && events.IsInPhase(2))
                        {
                            events.SetPhase(3);
                            events.CancelEvent(EVENT_CHECK_PHASING_HEALTH);
                            DoAction(ACTION_CALL_MIRROR);
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_PHASING_HEALTH, 2000);
                        break;
                    }
                    case EVENT_CELESTIAL_CALL_PHASE_ONE:
                    {
                        DoCast(me, SPELL_CELESTIAL_CALL_FIRST);
                        events.RescheduleEvent(EVENT_CELESTIAL_CALL_PHASE_ONE, urand(15000, 20000), 0, PHASE_ONE);
                        break;
                    }
                    case EVENT_VEIL_SKY_PHASE_ONE:
                    {
                        DoCast(me, SPELL_VEIL_OF_SKY_FIRST);
                        events.RescheduleEvent(EVENT_VEIL_SKY_PHASE_ONE, 40000, 0, PHASE_ONE);
                        break;
                    }
                    case EVENT_ASTRAL_RAIN_PHASE_ONE:
                    {
                        DoCast(SPELL_ASTRAL_RAIN_FIRST);
                        events.RescheduleEvent(EVENT_ASTRAL_RAIN_PHASE_ONE, 35000, 0, PHASE_ONE);
                        break;
                    }
                    case EVENT_VEIL_SKY_PHASE_TWO:
                    {
                        if (!veilSky)
                            break;

                        DoCast(me, SPELL_VEIL_OF_SKY_SECOND);
                        events.CancelEvent(EVENT_VEIL_SKY_PHASE_ONE);
                        events.RescheduleEvent(EVENT_VEIL_SKY_PHASE_TWO, 40000, 0, PHASE_TWO);
                        break;
                    }
                    case EVENT_ASTRAL_RAIN_PHASE_TWO:
                    {
                        if (!astralRain)
                            break;

                        DoCast(SPELL_ASTRAL_RAIN_SECOND);
                        events.RescheduleEvent(EVENT_ASTRAL_RAIN_PHASE_TWO, 35000, 0, PHASE_TWO);
                        break;
                    }
                    case EVENT_CELESTIAL_CALL_PHASE_TWO:
                    {
                        if (!celestialCall)
                            break;

                        DoCast(me, SPELL_CELESTIAL_CALL_SECOND);
                        events.RescheduleEvent(EVENT_CELESTIAL_CALL_PHASE_TWO, urand(15000, 20000), 0, PHASE_TWO);
                        break;
                    }
                    case EVENT_VEIL_SKY_PHASE_THREE:
                    {
                        if (!veilSky)
                            break;

                        DoCast(me, SPELL_VEIL_OF_SKY_THIRD);
                        events.CancelEvent(EVENT_VEIL_SKY_PHASE_ONE);
                        events.CancelEvent(EVENT_VEIL_SKY_PHASE_TWO);
                        events.RescheduleEvent(EVENT_VEIL_SKY_PHASE_THREE, 40000, 0, PHASE_THREE);
                        break;
                    }
                    case EVENT_ASTRAL_RAIN_PHASE_THREE:
                    {
                        if (!astralRain)
                            break;

                        DoCast(SPELL_ASTRAL_RAIN_THIRD);
                        events.RescheduleEvent(EVENT_ASTRAL_RAIN_PHASE_THREE, 35000, 0, PHASE_THREE);
                        break;
                    }
                    case EVENT_CELESTIAL_CALL_PHASE_THREE:
                    {
                        if (!celestialCall)
                            break;

                        DoCast(me, SPELL_CELESTIAL_CALL_THIRD);
                        events.RescheduleEvent(EVENT_CELESTIAL_CALL_PHASE_THREE, urand(15000, 20000), 0, PHASE_THREE);
                        break;
                    }
                    case EVENT_SUPERNOVA:
                    {
                        if (me->IsVisible())
                        {
                            Talk(SAY_SUPERNOVA);
                            Talk(SAY_SUPERNOVA_WARNING);
                            if (Unit* victim = me->getVictim())
                                DoCast(victim, SPELL_SUPERNOVA);

                            events.RescheduleEvent(EVENT_SUPERNOVA, 42000);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SUPERNOVA, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }

            if (me->IsVisible())
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_isisetAI(creature);
    }
};

class OrientationCheck : public std::unary_function < Unit*, bool >
{
public:
    explicit OrientationCheck(Unit* _caster) : caster(_caster)
    {
    }

    bool operator() (WorldObject* object) const
    {
        Unit* unit = object->ToUnit();
        return unit->isInFront(caster, 2.5f) ? false : true;
    }

private:
    Unit* caster;
};

class spell_hoo_supernova : public SpellScriptLoader
{
public:
    spell_hoo_supernova() : SpellScriptLoader("spell_hoo_supernova")
    {
    }
    class spell_hoo_supernova_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_supernova_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(OrientationCheck(GetCaster()));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_supernova_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_hoo_supernova_SpellScript();
    }
};

class spell_hoo_supernova_damage : public SpellScriptLoader
{
public:
    spell_hoo_supernova_damage() : SpellScriptLoader("spell_hoo_supernova_damage")
    {
    }
    class spell_hoo_supernova_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_supernova_damage_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(OrientationCheck(GetCaster()));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_supernova_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_hoo_supernova_damage_SpellScript();
    }
};

class npc_hoo_celestial_familiar : public CreatureScript
{
public:
    npc_hoo_celestial_familiar() : CreatureScript("npc_hoo_celestial_familiar")
    {
    }

    enum eventId
    {
        EVENT_BARRAGE   = 1
    };

    struct npc_hoo_celestial_familiarAI : public ScriptedAI
    {
        npc_hoo_celestial_familiarAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(me, SPELL_FAMILIAR_VISUAL, true);
            events.ScheduleEvent(EVENT_BARRAGE, 1000);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->RemoveAura(SPELL_FAMILIAR_VISUAL);
            me->RemoveCorpse(false);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BARRAGE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, IsHeroic() ? SPELL_ARCANE_BARRAGE_H : SPELL_ARCANE_BARRAGE_N);
                        events.RescheduleEvent(EVENT_BARRAGE, urand(2000, 3000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_celestial_familiarAI(creature);
    }
};

class npc_hoo_veil_sky : public CreatureScript
{
public:
    npc_hoo_veil_sky() : CreatureScript("npc_hoo_veil_sky")
    {
    }

    enum eventId
    {
        EVENT_VEIL_SKY  = 1
    };

    struct npc_hoo_veil_skyAI : public ScriptedAI
    {
        npc_hoo_veil_skyAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        EventMap events;
        InstanceScript* instance;

        void Reset()
        {
            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetPower(POWER_ENERGY, 100);
            events.Reset();
        }

        void EnterEvadeMode()
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (Creature* isiset = me->FindNearestCreature(BOSS_ISISET, 500.0f))
                isiset->AI()->DoAction(ACTION_HIDE_MIRROR);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_VEIL_SKY, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_VEIL_SKY:
                    {
                        DoCast(me, IsHeroic() ? SPELL_VEIL_SKY_H : SPELL_VEIL_SKY_N);
                        events.RescheduleEvent(EVENT_VEIL_SKY, 60000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_veil_skyAI(creature);
    }
};

class npc_hoo_celestial_call : public CreatureScript
{
public:
    npc_hoo_celestial_call() : CreatureScript("npc_hoo_celestial_call")
    {
    }

    enum eventId
    {
        EVENT_BARRAGE   = 1
    };

    struct npc_hoo_celestial_callAI : public ScriptedAI
    {
        npc_hoo_celestial_callAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        EventMap events;
        InstanceScript* instance;

        void Reset()
        {
            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetPower(POWER_ENERGY, 100);
            events.Reset();
        }

        void EnterEvadeMode()
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (Creature* isiset = me->FindNearestCreature(BOSS_ISISET, 500.0f))
                isiset->AI()->DoAction(ACTION_HIDE_MIRROR);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_BARRAGE, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BARRAGE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, IsHeroic() ? SPELL_ARCANE_BARRAGE_H : SPELL_ARCANE_BARRAGE_N);
                        events.RescheduleEvent(EVENT_BARRAGE, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_celestial_callAI(creature);
    }
};

class npc_hoo_astral_rain : public CreatureScript
{
public:
    npc_hoo_astral_rain() : CreatureScript("npc_hoo_astral_rain")
    {
    }

    enum eventId
    {
        EVENT_ASTRAL_RAIN   = 1
    };

    struct npc_hoo_astral_rainAI : public ScriptedAI
    {
        npc_hoo_astral_rainAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        EventMap events;
        InstanceScript* instance;

        void Reset()
        {
            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetPower(POWER_ENERGY, 100);
            events.Reset();
        }

        void EnterEvadeMode()
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (Creature* isiset = me->FindNearestCreature(BOSS_ISISET, 500.0f))
                isiset->AI()->DoAction(ACTION_HIDE_MIRROR);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ASTRAL_RAIN, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ASTRAL_RAIN:
                    {
                        Creature* celestialCall = me->FindNearestCreature(39721, 100);
                        Creature* veilSky = me->FindNearestCreature(39722, 100);
                        if (celestialCall && veilSky)
                            DoCast(SPELL_ASTRAL_RAIN_FIRST);
                        else
                            DoCast(SPELL_ASTRAL_RAIN_SECOND);
                        events.RescheduleEvent(EVENT_ASTRAL_RAIN, 8000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_astral_rainAI(creature);
    }
};

class spell_hoo_veil_of_sky : public SpellScriptLoader
{
public:
    spell_hoo_veil_of_sky() : SpellScriptLoader("spell_hoo_veil_of_sky")
    {
    }

    enum spellId
    {
        SPELL_VEIL_OF_SKY_FIRST_H   = 90760,
        SPELL_VEIL_OF_SKY_SECOND_H  = 90761,
        SPELL_VEIL_OF_SKY_THIRD_H   = 90762
    };

    class spell_hoo_veil_of_sky_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hoo_veil_of_sky_AuraScript);

        void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            if (Unit* owner = dmgInfo.GetVictim())
            {
                if (dmgInfo.GetAbsorb() > 0 && dmgInfo.GetSchoolMask() & SPELL_SCHOOL_MASK_MAGIC)
                {
                    if (Aura* aur = owner->GetAura(GetSpellInfo()->Id, owner->GetGUID()))
                    {
                        int32 absorbPct = 1;
                        switch (GetSpellInfo()->Id)
                        {
                            case SPELL_VEIL_OF_SKY_FIRST:
                            case SPELL_VEIL_OF_SKY_FIRST_H:
                                absorbPct = 20;
                                break;
                            case SPELL_VEIL_OF_SKY_SECOND:
                            case SPELL_VEIL_OF_SKY_SECOND_H:
                                absorbPct = 40;
                                break;
                            case SPELL_VEIL_OF_SKY_THIRD:
                            case SPELL_VEIL_OF_SKY_THIRD_H:
                                absorbPct = 60;
                                break;
                            default:
                                break;
                        }
                        int32 bp0 = absorbAmount * absorbPct / 100;
                        if (Unit* target = dmgInfo.GetAttacker())
                            owner->CastCustomSpell(target, SPELL_VEIL_OF_SKY_REFLECT, &bp0, NULL, NULL, true);
                    }
                }
            }
        }

        void Register()
        {
            AfterEffectManaShield += AuraEffectManaShieldFn(spell_hoo_veil_of_sky_AuraScript::HandleAbsorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hoo_veil_of_sky_AuraScript();
    }
};

class npc_hoo_spatial_flux : public CreatureScript
{
public:
    npc_hoo_spatial_flux() : CreatureScript("npc_hoo_spatial_flux")
    {
    }

    enum eventId
    {
        EVENT_SUMMON_FLUX   = 1,
        EVENT_ENERGY_FLUX
    };

    enum spellId
    {
        SPELL_SUMMON_ENERGY_FLUX_N      = 82382,
        SPELL_SUMMON_ENERGY_FLUX_H      = 90735,
        SPELL_ENERGY_FLUX_VISUAL        = 74043
    };

    struct npc_hoo_spatial_fluxAI : public ScriptedAI
    {
        npc_hoo_spatial_fluxAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_SUMMON_FLUX, 15000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_FLUX:
                    {
                        DoCast(IsHeroic() ? SPELL_SUMMON_ENERGY_FLUX_H : SPELL_SUMMON_ENERGY_FLUX_N);
                        events.RescheduleEvent(EVENT_SUMMON_FLUX, 15000);
                        events.ScheduleEvent(EVENT_ENERGY_FLUX, 1);
                        break;
                    }
                    case EVENT_ENERGY_FLUX:
                    {
                        DoCast(SPELL_ENERGY_FLUX_VISUAL);
                        events.CancelEvent(EVENT_ENERGY_FLUX);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_spatial_fluxAI(creature);
    }
};

class npc_hoo_energy_flux : public CreatureScript
{
public:
    npc_hoo_energy_flux() : CreatureScript("npc_hoo_energy_flux")
    {
    }

    enum spellId
    {
        SPELL_ENERGY_FLUX_PERIODIC  = 74044
    };

    struct npc_hoo_energy_fluxAI : public ScriptedAI
    {
        npc_hoo_energy_fluxAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            DoCast(me, SPELL_ENERGY_FLUX_PERIODIC, true);
            if (Player* player = me->FindNearestPlayer(300.0f, true))
                AttackStart(player);
        }

        // Northmaster trick :D
        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_energy_fluxAI(creature);
    }
};

class spell_hoo_call_of_the_sky : public SpellScriptLoader
{
public:
    spell_hoo_call_of_the_sky() : SpellScriptLoader("spell_hoo_call_of_the_sky")
    {
    }

    enum npcId
    {
        NPC_SPATIAL_FLUX    = 48707
    };

    class spell_hoo_call_of_the_sky_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_call_of_the_sky_SpellScript);

        void HandleSummonPortal()
        {
            if (WorldLocation const* const position = GetExplTargetDest())
                if (Unit* caster = GetCaster())
                    caster->SummonCreature(NPC_SPATIAL_FLUX, position->GetPositionX(), position->GetPositionY(), position->GetPositionZ(), 3.14f, TEMPSUMMON_MANUAL_DESPAWN, 600000);
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_hoo_call_of_the_sky_SpellScript::HandleSummonPortal);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_call_of_the_sky_SpellScript();
    }
};

class npc_hoo_spatial_flux_trash : public CreatureScript
{
public:
    npc_hoo_spatial_flux_trash() : CreatureScript("npc_hoo_spatial_flux_trash")
    {
    }

    enum eventId
    {
        EVENT_SUMMON_FLUX   = 1,
        EVENT_ENERGY_FLUX
    };

    enum spellId
    {
        SPELL_SUMMON_ENERGY_FLUX_N  = 82382,
        SPELL_SUMMON_ENERGY_FLUX_H  = 90735,
        SPELL_ENERGY_FLUX_VISUAL    = 74043
    };

    struct npc_hoo_spatial_flux_trashAI : public ScriptedAI
    {
        npc_hoo_spatial_flux_trashAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_FLUX, urand(15000, 18500));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_FLUX:
                    {
                        DoCast(IsHeroic() ? SPELL_SUMMON_ENERGY_FLUX_H : SPELL_SUMMON_ENERGY_FLUX_N);
                        events.RescheduleEvent(EVENT_SUMMON_FLUX, 15000);
                        events.ScheduleEvent(EVENT_ENERGY_FLUX, 1);
                        break;
                    }
                    case EVENT_ENERGY_FLUX:
                    {
                        DoCast(SPELL_ENERGY_FLUX_VISUAL);
                        events.CancelEvent(EVENT_ENERGY_FLUX);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_spatial_flux_trashAI(creature);
    }
};

class npc_hoo_star_shard : public CreatureScript
{
public:
    npc_hoo_star_shard() : CreatureScript("npc_hoo_star_shard")
    {
    }

    enum Spells
    {
        SPELL_STAR_SHARD_STATE  = 74780,
        SPELL_STAR_SHOCK_N      = 74791,
        SPELL_STAR_SHOCK_H      = 89860
    };

    enum eventId
    {
        EVENT_CHANGE_TARGET     = 1,
        EVENT_STAR_SHOCK
    };

    struct npc_hoo_star_shardAI : public ScriptedAI
    {
        npc_hoo_star_shardAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;
        Unit* target;

        void Reset()
        {
            target = NULL;
            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetPower(POWER_ENERGY, 100);
            events.Reset();
        }

        void EnterCombat(Unit* who)
        {
            me->AddAura(SPELL_STAR_SHARD_STATE, me);
            target = who;

            events.ScheduleEvent(EVENT_CHANGE_TARGET, 15000);
            events.ScheduleEvent(EVENT_STAR_SHOCK, 2000);

        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHANGE_TARGET:
                    {
                        if (target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            events.RescheduleEvent(EVENT_CHANGE_TARGET, 15000);
                        break;
                    }
                    case EVENT_STAR_SHOCK:
                    {
                        if (target && target != NULL && target->IsInWorld())
                            DoCast(target, IsHeroic() ? SPELL_STAR_SHOCK_H : SPELL_STAR_SHOCK_N, true);
                        events.RescheduleEvent(EVENT_STAR_SHOCK, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_star_shardAI(creature);
    }
};

class npc_hoo_flux_animator : public CreatureScript
{
public:
    npc_hoo_flux_animator() : CreatureScript("npc_hoo_flux_animator")
    {
    }

    enum Spells
    {
        SPELL_ARCANE_BARRAGE = 81013
    };

    enum eventId
    {
        EVENT_ARCANE_BARRAGE = 1
    };

    struct npc_hoo_flux_animatorAI : public ScriptedAI
    {
        npc_hoo_flux_animatorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetPower(POWER_ENERGY, 100);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ARCANE_BARRAGE, 9000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ARCANE_BARRAGE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 200, true))
                            DoCast(target, SPELL_ARCANE_BARRAGE);
                        events.RescheduleEvent(EVENT_ARCANE_BARRAGE, 9000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_flux_animatorAI(creature);
    }
};

class npc_hoo_spatial_anomaly : public CreatureScript
{
public:
    npc_hoo_spatial_anomaly() : CreatureScript("npc_hoo_spatial_anomaly")
    {
    }

    enum Spells
    {
        SPELL_ARCANE_BURST  = 74888
    };

    enum eventId
    {
        EVENT_ARCANE_BURST  = 1
    };

    enum creatureGUID
    {
        GUID_ANOMALY_RIGHT  = 218421,
        GUID_ANOMALY_LEFT   = 218358,
        GUID_FLUX_RIGHT     = 218688,
        GUID_FLUX_LEFT      = 218687
    };

    struct npc_hoo_spatial_anomalyAI : public ScriptedAI
    {
        npc_hoo_spatial_anomalyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetPower(POWER_ENERGY, 100);
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            switch (me->GetDBTableGUIDLow())
            {
                case GUID_ANOMALY_LEFT:
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                    me->VisitNearbyObject(300.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature())
                        {
                            if ((*itr)->ToCreature()->GetDBTableGUIDLow() == GUID_FLUX_LEFT)
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                        }
                    }
                    break;
                }
                case GUID_ANOMALY_RIGHT:
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                    me->VisitNearbyObject(300.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature())
                        {
                            if ((*itr)->ToCreature()->GetDBTableGUIDLow() == GUID_FLUX_RIGHT)
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ARCANE_BURST, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ARCANE_BURST:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 200, true))
                            DoCast(target, SPELL_ARCANE_BURST);
                        events.RescheduleEvent(EVENT_ARCANE_BURST, 10000);
                        break;
                    }
                    default:
                        break;
                }
            }

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_spatial_anomalyAI(creature);
    }
};

class spell_hoo_energy_flux : public SpellScriptLoader
{
public:
    spell_hoo_energy_flux() : SpellScriptLoader("spell_hoo_energy_flux")
    {
    }

    class spell_hoo_energy_flux_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_energy_flux_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_energy_flux_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_energy_flux_SpellScript();
    }
};

void AddSC_boss_isiset()
{
    new boss_isiset();
    new spell_hoo_supernova();
    new npc_hoo_celestial_familiar();
    new npc_hoo_celestial_call();
    new npc_hoo_veil_sky();
    new npc_hoo_astral_rain();
    new spell_hoo_veil_of_sky();
    new spell_hoo_supernova_damage();
    new npc_hoo_spatial_flux();
    new npc_hoo_energy_flux();
    new spell_hoo_call_of_the_sky();
    new npc_hoo_spatial_flux_trash();
    new npc_hoo_star_shard();
    new npc_hoo_flux_animator();
    new npc_hoo_spatial_anomaly();
    new spell_hoo_energy_flux();
}
