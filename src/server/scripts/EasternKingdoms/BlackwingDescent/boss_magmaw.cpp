
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */


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
    ////////////////////////////////////////////
    // General
    SPELL_LAVA_SPEW                     = 77689,
    SPELL_MAGMA_SPIT                    = 78359,
    SPELL_MOLTEN_TANTRUM                = 78403,

    SPELL_EMOTE_LAVA_SPLASH             = 79461,
    SPELL_EMOTE_CAST_DIRECT             = 20718,
    SPELL_FAKED_DEATH                   = 79153,

    ////////////////////////////////////////////
    // Lava Parasites ToDo: überprüfen
    SPELL_PILLAR_OF_FLAME               = 78006,
    SPELL_PILLAR_OF_FLAME_VISUAL_AURA   = 78017,
    SPELL_PILLAR_OF_FLAME_EFFECT        = 77970,
    SPELL_PILLAR_TRIGGER_SUMMON         = 77995,
    SPELL_LAVA_EFFECT                   = 77971,
    SPELL_PARASITIC_INFECTION           = 78941,

    ////////////////////////////////////////////
    // Rodeo Phase
    SPELL_MASSIVE_CRASH                 = 88253,
    SPELL_MASSIVE_CRASH_EFFECT          = 88287,

    SPELL_SWELTERING_ARMOR              = 78199,
    SPELL_MANGLE                        = 89773,
    SPELL_MANGLED_LIFELESS              = 78412, // Triggers after 29s 78362 (mangled lifeless effect)

    SPELL_LAUNCH_HOOK_LEFT              = 77917, // Sniff Verified
    SPELL_LAUNCH_HOOK_RIGHT             = 77941, // Sniff Verified

    SPELL_CHAIN_VISUAL_PRE_FIGHT        = 79026, // SPELL_EFFECT_TRIGGER_SPELL (88200) - Verified
    SPELL_CAPTURED                      = 88200, // Sniff Verified (Channels on Magmaw)
    SPELL_CHAIN_VISUAL_RIGHT            = 77940, // Sniff Verified (Channels on Magmaw)
    SPELL_CHAIN_VISUAL_LEFT             = 77929, // Sniff Verified (Channels on Magmaw)

    SPELL_IMPALE_SELF                   = 77907, // Sniff Verified

    ////////////////////////////////////////////
    //  From Sniffs
    //
    //  20718 Emote - SpellCastDirected
    //  79461 Emote - Magmaw Lava Splash
    //  89743 Ride Vehicle
    //  79010 Point of Vulnerability
    //  91925 Magma Spit 
    //  95280 Magma Spit
    //  77839 Lava Spew
    //  91931 Lava Spew
    //  77998 Pillar of Flame
    //  78006 Pillar of Flame
    //  85667 Guardian Taunt
    //  52205 Eject Passenger 3
    //  88067 Clear All Status Ailments
    //  94616 Mangle
    //  88253 Massive Crash
    //
};

enum Events
{
    EVENT_MAGMA_SPIT                    = 1,
    EVENT_PILLAR_OF_FLAME               = 2,
    EVENT_LAVA_SPEW                     = 3,
    EVENT_IN_RANGE_CHECK                = 4,
    EVENT_MANGLE                        = 5,
    EVENT_MASSIVE_CRASH                 = 6,
    EVENT_REMOVE_RODEO_PLAYERS          = 7,
    EVENT_LEAVE_SPIKE_PHASE             = 8,

    EVENT_BERSERK                       = 9,

    EVENT_FAKED_RODEO_PHASE             = 10
};

enum Actions
{
    ACTION_ENTER_SPIKE_PHASE,
    ACTION_EXIT_SPIKE_PHASE,
};

enum Phases
{
    PHASE_NORMAL,
    PHASE_MANGLE,
    PHASE_MASSIVE_CRASH_1,
    PHASE_MASSIVE_CRASH_2,
    PHASE_SPIKED,
};

enum Yells
{
    SAY_LAVA_PARASITE_WARNING,
    SAY_RODEO_PHASE,
    SAY_SPIKE_SELF
};

enum PassengerList
{
    PASSENGER_NPC_PINCER_R,
    PASSENGER_NPC_PINCER_L,
    PASSENGER_PLAYER_MANGLE_TARGET,
    PASSENGER_NPC_HEAD,
    PASSENGER_UNK2,
    PASSENGER_UNK1,
};

uint32 const MinionList[6] =
{
    NPC_PINCER_R, NPC_PINCER_L, 0, NPC_MAGMAWS_HEAD, 0, 0
};

class boss_magmaw : public CreatureScript
{
public:
    boss_magmaw() : CreatureScript("boss_magmaw") { }

    struct boss_magmawAI : public BossAI
    {
        boss_magmawAI(Creature* creature) : BossAI(creature, DATA_MAGMAW), isEncounterDone(false), vehicle(creature->GetVehicleKit()) {}

        Vehicle* vehicle;

        uint32 emoteTimer;
        uint8 phase;
        bool isEncounterDone;

        void Reset()
        {
            isEncounterDone = instance->GetBossState(DATA_MAGMAW) == DONE;

            if (isEncounterDone)
            {
                Unit* passenger = vehicle->GetPassenger(PASSENGER_NPC_HEAD);
                if (!passenger)
                {
                    passenger = me->SummonCreature(NPC_MAGMAWS_HEAD, *me);
                    passenger->EnterVehicle(me, PASSENGER_NPC_HEAD);
                }

                if (!me->HasAura(SPELL_FAKED_DEATH))
                    me->AddAura(SPELL_FAKED_DEATH, me);

                return;
            }

            _Reset();

            DespawnMinions();

            emoteTimer = 20000;
            phase = PHASE_NORMAL;
            me->SetReactState(REACT_AGGRESSIVE);

            // This can't be done in the db due to some skyfire vehicle bugs
            for (uint8 i = 0; i <= 5; i++)
            {
                if (MinionList[i] == 0 || vehicle->GetPassenger(i))
                {
                    if (MinionList[i] == 0)
                        if (Unit* passenger = vehicle->GetPassenger(i))
                            vehicle->RemovePassenger(passenger);

                    continue;
                }

                Creature* minion = me->FindNearestCreature(MinionList[i], 100.f);

                if (!minion)
                    minion = me->SummonCreature(MinionList[i], *me);

                if (minion->isDead())
                    minion->Respawn();

                minion->EnterVehicle(me, i);
            }

            if (Creature* stalker = me->GetCreature(*me, instance->GetData64(NPC_SPIKE_STALKER)))
                stalker->CastSpell(stalker, SPELL_CHAIN_VISUAL_PRE_FIGHT);

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();

            if (Creature* head = me->GetCreature(*me, instance->GetData64(NPC_MAGMAWS_HEAD)))
                head->SetInCombatWithZone();

            if (Creature* stalker = me->GetCreature(*me, instance->GetData64(NPC_SPIKE_STALKER)))
                stalker->RemoveAllAuras();

            events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 40000);
            events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(14000,17000));
            events.ScheduleEvent(EVENT_LAVA_SPEW, urand(7000, 9000));
            events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 5000);
            events.ScheduleEvent(EVENT_BERSERK, 600000);
            // events.ScheduleEvent(EVENT_MANGLE, 50000);
            // events.ScheduleEvent(EVENT_MASSIVE_CRASH, 7000);

            events.ScheduleEvent(EVENT_FAKED_RODEO_PHASE, 100000);

            me->MonsterYell("Info: Dieser Boss ist in der Testphase. Er enthaelt Tapferkeitspunkte jedoch keinen Loot. Wir bitten Euch Bugs im Bugtracker zu reporten.");
        }

        void UpdateAI(uint32 diff)
        {
            if (isEncounterDone)
                return;

            if (!me->isInCombat())
            {
                if (emoteTimer <= diff)
                {
                    DoCast(SPELL_EMOTE_LAVA_SPLASH);
                    emoteTimer = urand(30000, 45000);

                } else
                    emoteTimer -= diff;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            //_DoAggroPulse(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    ///////////////////////////////////////////////////////////
                    // General
                case EVENT_MAGMA_SPIT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                        DoCast(target, SPELL_MAGMA_SPIT);

                    events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(15000, 17000));
                    break;
                case EVENT_LAVA_SPEW:
                    DoCast(me, SPELL_LAVA_SPEW);
                    events.ScheduleEvent(EVENT_LAVA_SPEW, urand(23000, 26000));
                    break;
                case EVENT_IN_RANGE_CHECK:
                    {
                        if (Unit* victim = me->getVictim())
                        {
                            if (!me->IsWithinMeleeRange(victim))
                                DoCast(me, SPELL_MOLTEN_TANTRUM, true);
                        } else
                            DoCast(me, SPELL_MOLTEN_TANTRUM);

                        events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 3000);
                    }
                    break;
                case EVENT_PILLAR_OF_FLAME:
                    DoCast(SPELL_PILLAR_OF_FLAME);
                    Talk(SAY_LAVA_PARASITE_WARNING);

                    events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 40000);
                    break;
                case EVENT_BERSERK:
                    // ToDo: Find out the correct Berserk spell
                    break;

                    ///////////////////////////////////////////////////////////
                    // Rodeo
                case EVENT_FAKED_RODEO_PHASE:
                    Talk(SAY_SPIKE_SELF);

                    if (Creature* stalker = me->GetCreature(*me, instance->GetData64(NPC_SPIKE_STALKER)))
                    {
                        stalker->CastSpell(me, SPELL_CHAIN_VISUAL_LEFT);
                        stalker->CastSpell(me, SPELL_CHAIN_VISUAL_RIGHT);
                    }

                    DoCast(SPELL_IMPALE_SELF);

                    events.DelayEvents(35000);
                    events.ScheduleEvent(EVENT_FAKED_RODEO_PHASE, 95000);
                    break;

                case EVENT_MANGLE:
                    {
                        phase = PHASE_MANGLE;

                        if (Unit* victim = me->getVictim())
                            me->AddAura(SPELL_SWELTERING_ARMOR, victim);

                        DoCastVictim(SPELL_MANGLE);

                        events.CancelEvent(EVENT_PILLAR_OF_FLAME);
                        events.CancelEvent(EVENT_IN_RANGE_CHECK);
                        events.CancelEvent(EVENT_IN_RANGE_CHECK);
                        events.ScheduleEvent(EVENT_MASSIVE_CRASH, 7000);
                        events.ScheduleEvent(EVENT_REMOVE_RODEO_PLAYERS, 30000);
                        events.ScheduleEvent(EVENT_MANGLE, 90000);
                        break;
                    }
                case EVENT_MASSIVE_CRASH:
                    {
                        Talk(SAY_RODEO_PHASE);
                        events.RescheduleEvent(EVENT_MAGMA_SPIT, 10000);
                        events.RescheduleEvent(EVENT_LAVA_SPEW, 10000);
                        DoCast(SPELL_MASSIVE_CRASH);
                        break;
                    }
                case EVENT_REMOVE_RODEO_PLAYERS:
                    {
                        if (phase != PHASE_MANGLE)
                            break;

                        for (uint8 i = PASSENGER_NPC_PINCER_R; i != PASSENGER_NPC_PINCER_L; ++i)
                            if (Unit* pincer = vehicle->GetPassenger(i))
                                if (Vehicle* pincersVehicle = pincer->GetVehicleKit())
                                    pincersVehicle->RemoveAllPassengers();

                        events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 22000);
                        events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 5000);
                        break;
                    }
                }
            }

            if (!isInManglePhase())
                DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_ENTER_SPIKE_PHASE:
                {
                    Talk(SAY_SPIKE_SELF);
                    phase = PHASE_SPIKED;

                    if (Creature* stalker = me->GetCreature(*me, instance->GetData64(NPC_SPIKE_STALKER)))
                    {
                        stalker->CastSpell(me, SPELL_CHAIN_VISUAL_LEFT, true);
                        stalker->CastSpell(me, SPELL_CHAIN_VISUAL_RIGHT, true);
                    }

                    events.RescheduleEvent(EVENT_MAGMA_SPIT, urand(38000, 43000));
                    events.RescheduleEvent(EVENT_LAVA_SPEW, urand(38000, 43000));
                    break;
                }
            case ACTION_EXIT_SPIKE_PHASE:
                {
                    phase = PHASE_NORMAL;

                    events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 22000);
                    events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 5000);
                    break;
                }
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (isEncounterDone)
            {
                damage = 0;
            }
            else if (me->GetHealth() <= damage)
            {
                damage = 0;
                isEncounterDone = true;
                JustDied(who);
            }
        }

        void JustDied(Unit* killer)
        {
            for (uint8 i = PASSENGER_NPC_PINCER_R; i <= PASSENGER_PLAYER_MANGLE_TARGET; i++)
            {
                if (Unit* passenger = vehicle->GetPassenger(i))
                {
                    if (Vehicle* passengersVehicle = passenger->GetVehicleKit())
                        passengersVehicle->RemoveAllPassengers();

                    passenger->ExitVehicle();

                    if (Creature* creature = passenger->ToCreature())
                        creature->DespawnOrUnsummon();
                }
            }

            RemoveEncounterFrame();
            DespawnMinions();

            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED | UNIT_FLAG_STUNNED);          
            me->getHostileRefManager().deleteReferences();
            me->CombatStop();
            me->DeleteThreatList();

            if (Unit* head = vehicle->GetPassenger(PASSENGER_NPC_HEAD))
            {
                head->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                head->getHostileRefManager().deleteReferences();
                head->CombatStop();
                head->DeleteThreatList();
            }

            instance->SetBossState(DATA_MAGMAW, DONE);

            if (!me->HasAura(SPELL_FAKED_DEATH))
                me->AddAura(SPELL_FAKED_DEATH, me);

            // MakeLootVisible(killer);
            me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
        }

        bool isInManglePhase()
        {
            return (phase != PHASE_NORMAL);
        }

        void DespawnMinions()
        {
            me->DespawnCreaturesInArea(NPC_IGNITION_TRIGGER, 200.f);
            me->DespawnCreaturesInArea(NPC_PILLAR_OF_FLAME_TRIGGER, 200.f);
            me->DespawnCreaturesInArea(NPC_LAVA_PARASITE, 200.f);
            me->DespawnCreaturesInArea(NPC_LAVA_PARASITE_SUMMONED, 200.f);
            me->DespawnCreaturesInArea(NPC_BLAZING_BONE_CONSTRUCT, 200.f);
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
                damage *= 2;

                magmaw->LowerPlayerDamageReq(damage);
                magmaw->DealDamage(magmaw, damage);
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

        uint32 uiErruptTime;
        uint8 step;
        Unit* summoner;

        void Reset()
        {
            uiErruptTime = 2100;
            step = 0;
        }

        void IsSummonedBy(Unit* unit)
        {
            summoner = unit;
        }

        void UpdateAI(uint32 diff)
        {
            if (step >= 2)
                return;

            if (uiErruptTime <= diff)
            {
                if (step == 0)
                {
                    if (summoner)
                        me->NearTeleportTo(*summoner, false);

                    me->AddAura(SPELL_PILLAR_OF_FLAME_VISUAL_AURA, me);
                    uiErruptTime = 6000;

                }
                else if (step == 1)
                {
                    DoCast(SPELL_PILLAR_OF_FLAME_EFFECT);
                    me->DespawnOrUnsummon(4000);
                }

                step++;

            } else uiErruptTime -= diff;
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

            if (Unit* victim = me->getVictim())
                if (victim->IsWithinMeleeRange(me))
                    if (!victim->GetAura(SPELL_PARASITIC_INFECTION))
                        DoCast(victim, SPELL_PARASITIC_INFECTION);

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lava_parasiteAI (creature);
    }
};

class PillarTargetSelector
{
public:
    PillarTargetSelector(Unit* unit) : me(unit) {}

    bool operator() (Unit* unit)
    {
        return unit != me;
    }
private:
    Unit* me;
};

Unit* SelectTargetForPillarOfFlame(Unit* unit)
{
    // Try to prefer ranged targets
    Map::PlayerList const &list = unit->GetMap()->GetPlayers();
    std::list<Player*> targets;
    std::list<Player*> notargets;

    for (Map::PlayerList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
    {
        if (unit->GetDistance2d(itr->getSource()) > 25.f)
            targets.push_back(itr->getSource());
        else
            notargets.push_back(itr->getSource());
    }

    if (!targets.empty())
        return SelectRandomContainerElement(targets);
    else if (!notargets.empty())
        return SelectRandomContainerElement(notargets);

    return NULL;
}

class spell_pillar_of_flame : public SpellScriptLoader
{
public:
    spell_pillar_of_flame() : SpellScriptLoader("spell_pillar_of_flame") { }

    class spell_pillar_of_flame_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pillar_of_flame_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            if (Unit* unit = GetCaster())
                if (Unit* target = SelectTargetForPillarOfFlame(unit))
                {
                    target->SummonCreature(NPC_PILLAR_OF_FLAME_TRIGGER, *target);
                    //unitList.remove_if (PillarTargetSelector(target));
                }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pillar_of_flame_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pillar_of_flame_SpellScript();
    }
};

class spell_launch_hook : public SpellScriptLoader
{
public:
    spell_launch_hook() : SpellScriptLoader("spell_launch_hook") {}

    class spell_launch_hook_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_launch_hook_AuraScript);

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                if (Creature* spikeStalker = target->ToCreature())
                    if (spikeStalker->GetEntry() == NPC_SPIKE_STALKER)
                    {
                        if (spikeStalker->HasAura(GetSpellInfo()->Id == SPELL_LAUNCH_HOOK_RIGHT ? SPELL_LAUNCH_HOOK_LEFT : SPELL_LAUNCH_HOOK_RIGHT))
                            if (Creature* magmaw = spikeStalker->FindNearestCreature(BOSS_MAGMAW, 70.f))
                            {
                                magmaw->AI()->DoAction(ACTION_ENTER_SPIKE_PHASE);
                                magmaw->CastSpell(magmaw, SPELL_IMPALE_SELF, true);
                            }
                    }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_launch_hook_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_launch_hook_AuraScript();
    }
};

class spell_impale_self : public SpellScriptLoader
{
public:
    spell_impale_self() : SpellScriptLoader("spell_impale_self") { }

    class spell_impale_self_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_impale_self_AuraScript);

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* me = caster->ToCreature())
                {
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_STUNNED);

                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* head = vehicle->GetPassenger(PASSENGER_NPC_HEAD))
                        {
                            head->SetMaxHealth(me->GetMaxHealth());
                            head->SetFullHealth();
                            head->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

                            if (Creature* headCreature = head->ToCreature())
                                headCreature->SetInCombatWithZone();
                        }
                }
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* me = caster->ToCreature())
                    if (InstanceScript* instance = caster->GetInstanceScript())
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_STUNNED);

                        if (Vehicle* vehicle = me->GetVehicleKit())
                        {
                            if (Unit* head = vehicle->GetPassenger(PASSENGER_NPC_HEAD))
                            {
                                head->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                head->RemoveAllAuras();
                                head->SetMaxHealth(me->GetMaxHealth());
                                head->SetFullHealth();
                            }

                            if (Creature* stalker = me->GetCreature(*me, instance->GetData64(NPC_SPIKE_STALKER)))
                                stalker->RemoveAllAuras();
                        }
                    }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_impale_self_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectApplyFn(spell_impale_self_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_impale_self_AuraScript();
    }
};

void AddSC_boss_magmaw()
{
    new boss_magmaw();
    new npc_exposed_head_of_magmaw();
    new npc_pillar_of_flame_trigger();
    new npc_lava_parasite();
    new spell_pillar_of_flame();
    new spell_launch_hook();
    new spell_impale_self();
}
