
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "blackwing_descent.h"

enum Spells
{
    // Omnotron
    SPELL_INACTIVE                      = 78726,
    SPELL_SHUTTING_DOWN                 = 78746,
    SPELL_ACTIVATED                     = 78740,
    SPELL_DISCHARGE                     = 75641,

    // Electron
    SPELL_LIGHTNING_CONDUCTOR           = 79888,
    SPELL_ELECTRICAL_DISCHARGE          = 91465,
    SPELL_UNSTABLE_SHIELD               = 91447,
    SPELL_RECHARGING_ELECTRON           = 78697,

    // Toxitron
    SPELL_CHEMICAL_BOMB                 = 80157,
    SPELL_POISON_SOAKED_SHELL           = 91501,
    SPELL_POISON_PROTOCOL               = 91513,
    SPELL_RECHARGING_TOXITRON           = 78700,

    // Magmatron
    SPELL_BARRIER                       = 79582,
    SPELL_ACQUIRING_TARGET              = 79501,
    SPELL_FLAMETHROWER                  = 79504,
    SPELL_INCINERATION_SECURITY_MEASURE = 79023,
    SPELL_RECHARGING_MAGMATRON          = 78698,

    // Arcanotron
    SPELL_POWER_GENERATOR               = 79626,
    SPELL_ARCANE_ANNIHILATOR            = 79710,
    SPELL_POWER_CONVERSION              = 79729,
    SPELL_RECHARGING_ARCANOTRON         = 78699,

    // Poisonbomb
    SPELL_FIXATE                        = 80094,
    SPELL_POISONBOMB                    = 80092
};

enum Events
{
    // Omnotron
    EVENT_ACTIVATE_NEXT_CONSTRUCT       = 1,
    EVENT_RESET_CHECK                   = 2,
    EVENT_SYNC_DAMAGE                   = 3,
    // Magmatron
    EVENT_ACQUIRING_TARGET              = 4,
    EVENT_INCINERATION_SECURITY_MEASURE = 5,
    // Toxitron
    EVENT_CHEMICAL_BOMB                 = 6,
    EVENT_POISON_PROTOCOL               = 7,
    // Electron
    EVENT_LIGHTNING_CONDUCTOR           = 8,
    EVENT_ELECTRICAL_DISCHARGE          = 9,
    // Arcanotron
    EVENT_POWER_GENERATOR               = 10,
    EVENT_ARCANE_ANNIHILATOR            = 11
};

enum Texts
{
    // Omnotron
    SAY_INTRO                           = 0,
    SAY_ARKANOTRON_ACTIVE               = 1,
    SAY_ARKANOTRON_SHIELDS_ACTIVE       = 2,
    SAY_TOXITRON_ACTIVE                 = 3,
    SAY_TOXITRON_SHIELDS_ACTIVE         = 4,
    SAY_ELEKTRON_ACTIVE                 = 5,
    SAY_ELEKTRON_SHIELDS_ACTIVE         = 6,
    SAY_MAGMATRON_ACTIVE                = 7,
    SAY_MAGMATRON_SHIELDS_ACTIVE        = 8,
    SAY_MAGMATRON_SPECIAL               = 9,
    SAY_DEFEATED                        = 10,
    // Magmatron
    SAY_FOCUSES_HIS_EYE                 = 0,
    SAY_BARRIER                         = 1,
    // Elektron
    SAY_LIGHTNING_CONDUCTOR             = 0,
    SAY_UNSTABLE_SHIELD                 = 1,
    // Arkanotron
    SAY_ARCANE_CONVERSATION             = 0,
    // Toxitron
    SAY_POISON_SOAKED_SHELL             = 0
};

enum Actions
{
    ACTION_OMNOTRON_START_EVENT,
    ACTION_TRON_ACTIVATE,
    ACTION_DEACTIVATE
};

enum Constants
{
    DIPSLAYID_INACIVE                   = 33492,

    TRON_TOCITRON                       = 0,
    TRON_ARCANOTRON                     = 1,
    TRON_ELEKTRON                       = 2,
    TRON_MAGMATRON                      = 3
};

struct OmontronData
{
    uint32 entry;
    Position spawnPosition;
};

OmontronData const omontronData[4] =
{
    {NPC_TOXITRON,   {-333.632f, -411.866f, 214.1353f, 1.291544f}},
    {NPC_ARCANOTRON, {-315.415f, -412.474f, 214.0963f, 1.832596f}},
    {NPC_ELECTRON,   {-342.519f, -405.134f, 214.0583f, 0.942478f}},
    {NPC_MAGMATRON,  {-308.807f, -405.278f, 214.0873f, 2.111848f}}
};

namespace Omnotron
{
    void DespawnMinions(Creature* me)
    {
        me->DespawnCreaturesInArea(NPC_POISON_BOMB, 200.f);
        me->DespawnCreaturesInArea(NPC_POISON_CLOUD, 200.f);
        me->DespawnCreaturesInArea(NPC_POWER_GENERATOR, 200.f);
    }

    uint8 GetTronIdByEntry(uint32 const entry)
    {
        switch (entry)
        {
            case NPC_TOXITRON:
                return TRON_TOCITRON;
            case NPC_ARCANOTRON:
                return TRON_ARCANOTRON;
            case NPC_ELECTRON:
                return TRON_ELEKTRON;
            case NPC_MAGMATRON:
                return TRON_MAGMATRON;
            default:
                return 0;
        }
    }
}

class npc_omnotron_controller : public CreatureScript
{
public:
    npc_omnotron_controller() : CreatureScript("npc_omnotron_controller") { }

    struct npc_omnotron_controllerAI : public ScriptedAI
    {
        npc_omnotron_controllerAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()), IsResetLocked(false) {}

        InstanceScript* instance;
        EventMap events;

        std::vector<uint64> trons;
        uint32 damageDealt[4];

        bool IsResetLocked; // Locks the Reset method

        void Reset()
        {
            if (IsResetLocked || instance->GetBossState(DATA_OMNOTRON_DEFENSE_SYSTEM) == DONE)
                return;

            IsResetLocked = true;

            events.Reset();

            me->InterruptNonMeleeSpells(false);
            me->RemoveAllAuras();

            instance->SetBossState(DATA_OMNOTRON_DEFENSE_SYSTEM, NOT_STARTED);

            for (std::vector<uint64>::const_iterator itr = trons.begin(); itr != trons.end(); ++itr)
                if (Creature* tron = me->GetCreature(*me, *itr))
                {
                    tron->AI()->RemoveEncounterFrame();
                    tron->DespawnOrUnsummon();
                }

                trons.clear();
                Omnotron::DespawnMinions(me);

                for (uint8 i = 0; i < 4; ++i)
                {
                    damageDealt[i] = 0;

                    if (Creature* tron = me->SummonCreature(omontronData[i].entry, omontronData[i].spawnPosition, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 600*IN_MILLISECONDS))
                    {
                        tron->AddAura(SPELL_INACTIVE, tron);
                        tron->SetDisplayId(DIPSLAYID_INACIVE);
                        tron->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        tron->SetPower(POWER_ENERGY, 100);
                        trons.push_back(tron->GetGUID());
                    }
                }

                // Randomize the Trons
                for (uint8 i = 0; i < 15; ++i)
                {
                    uint32 pos = urand(0, trons.size() - 1);

                    uint64 const guid = *(trons.begin() + pos);

                    trons.erase(trons.begin() + pos);
                    trons.push_back(guid);
                }

                if (Creature* nextTron = GetNextTron())
                    nextTron->AI()->SetData(DATA_IS_FIRST_TRON, true);

                IsResetLocked = false;
        }

        Creature* GetNextTron() const
        {
            ASSERT(trons.size() && "Omnotron Defense System: Tron minion underflow... aborted");
            return me->GetCreature(*me, *trons.begin());
        }

        void RechargeNextTron()
        {
            if (Creature* tron = GetNextTron())
            {
                switch (tron->GetEntry())
                {
                    case NPC_MAGMATRON:
                        DoCast(SPELL_RECHARGING_MAGMATRON);
                        break;
                    case NPC_ELECTRON:
                        DoCast(SPELL_RECHARGING_ELECTRON);
                        break;
                    case NPC_TOXITRON:
                        DoCast(SPELL_RECHARGING_TOXITRON);
                        break;
                    case NPC_ARCANOTRON:
                        DoCast(SPELL_RECHARGING_ARCANOTRON);
                        break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ACTIVATE_NEXT_CONSTRUCT:
                    {
                        if (Creature* tron = GetNextTron())
                        {
                            // Activate
                            tron->AI()->DoAction(ACTION_TRON_ACTIVATE);

                            trons.erase(trons.begin());
                            trons.push_back(tron->GetGUID());

                            // Recharge Next
                            RechargeNextTron();
                        }

                        events.ScheduleEvent(EVENT_ACTIVATE_NEXT_CONSTRUCT, 45000);
                        break;
                    }
                    case EVENT_RESET_CHECK:
                    {
                        if (instance->AreAllPlayersDead())
                            Reset();
                        else
                            events.ScheduleEvent(EVENT_RESET_CHECK, 3000);
                        break;
                    }
                    case EVENT_SYNC_DAMAGE:
                    {
                        for (std::vector<uint64>::const_iterator itr = trons.begin(); itr != trons.end(); ++itr)
                        {
                            if (Creature* tron = me->GetCreature(*me, *itr))
                            {
                                uint8 const id = Omnotron::GetTronIdByEntry(tron->GetEntry());

                                if (damageDealt[id])
                                {
                                    tron->DealDamage(tron, damageDealt[id]);
                                    tron->LowerPlayerDamageReq(damageDealt[id]);
                                    damageDealt[id] = 0;
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_SYNC_DAMAGE, 1500);
                        break;
                    }
                }
            }		
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_OMNOTRON_START_EVENT:
                {
                    if (instance)
                        instance->SetBossState(DATA_OMNOTRON_DEFENSE_SYSTEM, IN_PROGRESS);

                    if (Creature const* tron = GetNextTron())
                    {
                        trons.erase(trons.begin());
                        trons.push_back(tron->GetGUID());
                    }

                    for (std::vector<uint64>::const_iterator itr = trons.begin(); itr != trons.end(); ++itr)
                        if (Creature* tron = me->GetCreature(*me, *itr))
                            tron->SetInCombatWithZone();

                    RechargeNextTron();

                    events.ScheduleEvent(EVENT_RESET_CHECK, 3000);
                    events.ScheduleEvent(EVENT_SYNC_DAMAGE, 1500);
                    events.ScheduleEvent(EVENT_ACTIVATE_NEXT_CONSTRUCT, 45000);
                    break;
                }
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type > 3)
                return;

            for (uint8 i = 0; i < 4; ++i)
                if (type != i)
                    damageDealt[i] += data;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_omnotron_controllerAI (creature);
    }
};

class boss_omnotron_defense_system : public CreatureScript
{
public:
    boss_omnotron_defense_system() : CreatureScript("boss_omnotron_defense_system") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_omnotron_defense_systemAI (creature);
    }

    struct boss_omnotron_defense_systemAI : public ScriptedAI
    {
        boss_omnotron_defense_systemAI(Creature* creature) : ScriptedAI(creature), isActive(false), isFirstTron(false), shieldCasted(false), originalDisplayId(creature->GetDisplayId()), tronId(Omnotron::GetTronIdByEntry(creature->GetEntry())), uiFlameThrowerTarget(0)
        {
            instance = creature->GetInstanceScript();

            creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            creature->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
        }

        InstanceScript* instance;
        EventMap events;

        bool isActive;
        bool isFirstTron;
        bool shieldCasted;

        uint32 originalDisplayId;

        Creature* omnotron;
        std::list<uint64> trons;
        uint8 const tronId;

        uint64 uiFlameThrowerTarget;

        void EnterCombat(Unit * who)
        {   
            omnotron = me->GetCreature(*me, instance->GetData64(BOSS_OMNOTRON));

            trons.clear();

            for (uint8 i = 0; i < 4; ++i)
                if (omontronData[i].entry != me->GetEntry())
                    trons.push_back(instance->GetData64(omontronData[i].entry));

            if (isFirstTron)
            {
                me->GetMotionMaster()->InitDefault();

                if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                    omnotron->AI()->DoAction(ACTION_OMNOTRON_START_EVENT);

                DoAction(ACTION_TRON_ACTIVATE);
            }
        }

        void Reset()
        {
            uiFlameThrowerTarget = 0;

            if (instance->AreAllPlayersDead())
                if (Creature* omnotron = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OMNOTRON)))
                    omnotron->AI()->Reset();
        };

        void DoAction(int32 action)
        {
            events.Reset();

            switch (action)
            {
                case ACTION_TRON_ACTIVATE:
                {
                    me->RemoveAllAuras();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoZoneInCombat(me);
                    me->AddAura(SPELL_ACTIVATED, me);
                    isActive = true;
                    shieldCasted = false;
                    me->SetDisplayId(originalDisplayId);

                    if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                        omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON));

                    // Intialize Events
                    switch (me->GetEntry())
                    {

                        case NPC_MAGMATRON:
                            if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                                omnotron->AI()->Talk(SAY_MAGMATRON_ACTIVE);
                            events.ScheduleEvent(EVENT_ACQUIRING_TARGET, 15000);
                            events.ScheduleEvent(EVENT_INCINERATION_SECURITY_MEASURE, 27000);
                            break;

                        case NPC_TOXITRON:
                            if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                                omnotron->AI()->Talk(SAY_TOXITRON_ACTIVE);
                            events.ScheduleEvent(EVENT_CHEMICAL_BOMB, 25000);
                            events.ScheduleEvent(EVENT_POISON_PROTOCOL, 3800);
                            break;

                        case NPC_ELECTRON:
                            if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                                omnotron->AI()->Talk(SAY_ELEKTRON_ACTIVE);
                            events.ScheduleEvent(EVENT_LIGHTNING_CONDUCTOR, 10000);
                            events.ScheduleEvent(EVENT_ELECTRICAL_DISCHARGE, 25000);
                            break;

                        case NPC_ARCANOTRON:
                            if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                                omnotron->AI()->Talk(SAY_ARKANOTRON_ACTIVE);
                            events.ScheduleEvent(EVENT_POWER_GENERATOR, 30000);
                            events.ScheduleEvent(EVENT_ARCANE_ANNIHILATOR, 8000);
                            break;
                    }

                    AddEncounterFrame();
                    return;
                }
                case ACTION_DEACTIVATE:
                {
                    events.Reset();
                    isActive = false;
                    me->InterruptNonMeleeSpells(false);
                    me->AttackStop();
                    DoCast(SPELL_SHUTTING_DOWN);
                    break;
                }
            }
        }

        uint64 GetGUID(int32 /*id*/ = 0) const
        {
            return uiFlameThrowerTarget;
        }

        void UpdateAI(uint32 diff)
        {
            if (!isActive || !me->isInCombat())
                return;

            if (me->GetPower(POWER_ENERGY) == 0)
            {
                isActive = false;
                DoAction(ACTION_DEACTIVATE);
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            if (!shieldCasted && me->GetPower(POWER_ENERGY) <= 50)
            {
                shieldCasted = true;
                switch (me->GetEntry())
                {

                    case NPC_MAGMATRON:
                        DoCast(me, SPELL_BARRIER);
                        Talk(SAY_BARRIER, me->GetGUID());

                        if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                            omnotron->AI()->Talk(SAY_MAGMATRON_SHIELDS_ACTIVE);
                        break;

                    case NPC_TOXITRON:
                        Talk(SAY_POISON_SOAKED_SHELL, me->GetGUID());
                        DoCast(me, SPELL_POISON_SOAKED_SHELL);
                        if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                            omnotron->AI()->Talk(SAY_TOXITRON_SHIELDS_ACTIVE);
                        break;

                    case NPC_ELECTRON:
                        Talk(SAY_UNSTABLE_SHIELD, me->GetGUID());
                        DoCast(me, SPELL_UNSTABLE_SHIELD);
                        if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                            omnotron->AI()->Talk(SAY_ELEKTRON_SHIELDS_ACTIVE);
                        break;

                    case NPC_ARCANOTRON:
                        Talk(SAY_ARCANE_CONVERSATION, me->GetGUID());
                        DoCast(me, SPELL_POWER_CONVERSION);
                        if (Creature* omnotron = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_OMNOTRON)))
                            omnotron->AI()->Talk(SAY_ARKANOTRON_SHIELDS_ACTIVE);
                        break;
                }
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // Magmatron
                    case EVENT_ACQUIRING_TARGET:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.f, true))
                        {
                            uiFlameThrowerTarget = target->GetGUID();
                            Talk(SAY_FOCUSES_HIS_EYE, uiFlameThrowerTarget);

                            DoCast(target, SPELL_ACQUIRING_TARGET);
                        }
                        events.ScheduleEvent(EVENT_ACQUIRING_TARGET, urand(25000, 30000));
                        return;
                    }
                    case EVENT_INCINERATION_SECURITY_MEASURE:
                    {
                        if (Creature* omnotron = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OMNOTRON)))
                            omnotron->AI()->Talk(SAY_MAGMATRON_SPECIAL);

                        DoCastAOE(SPELL_INCINERATION_SECURITY_MEASURE);
                        events.ScheduleEvent(EVENT_INCINERATION_SECURITY_MEASURE, urand(30000, 35000));
                        return;
                    }
                    // Toxitron
                    case EVENT_CHEMICAL_BOMB:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.f, true))
                            DoCast(target, SPELL_CHEMICAL_BOMB);
                        events.ScheduleEvent(EVENT_CHEMICAL_BOMB, 30000);
                        return;
                    }
                    case EVENT_POISON_PROTOCOL:
                    {
                        DoCast(me, SPELL_POISON_PROTOCOL);

                        events.ScheduleEvent(EVENT_POISON_PROTOCOL, 38000);
                        return;
                    }
                    // Electron
                    case EVENT_LIGHTNING_CONDUCTOR:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.f, true))
                        {
                            Talk(SAY_LIGHTNING_CONDUCTOR, target->GetGUID());
                            DoCast(target, SPELL_LIGHTNING_CONDUCTOR);
                        }

                        events.ScheduleEvent(EVENT_LIGHTNING_CONDUCTOR,10000);
                        return;
                    }
                    case EVENT_ELECTRICAL_DISCHARGE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.f, true))
                            DoCast(target, SPELL_ELECTRICAL_DISCHARGE);

                        events.ScheduleEvent(EVENT_ELECTRICAL_DISCHARGE, 25000);
                        return;
                    }
                    // Arcanotron
                    case EVENT_POWER_GENERATOR:
                    {
                        DoCast(me, SPELL_POWER_GENERATOR, true);
                        events.ScheduleEvent(EVENT_POWER_GENERATOR, 30000);
                        return;
                    }
                    case EVENT_ARCANE_ANNIHILATOR:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                            DoCast(target, SPELL_ARCANE_ANNIHILATOR);

                        events.ScheduleEvent(EVENT_ARCANE_ANNIHILATOR, 8000);
                        return;
                    }
                }
            }


            DoMeleeAttackIfReady();
        }

        void SetData(uint32 type, uint32 /*data*/)
        {
            if (type == DATA_IS_FIRST_TRON)
            {
                isFirstTron = true;
                me->RemoveAllAuras();
                me->SetDisplayId(originalDisplayId);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

                if (Creature* omnotron = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OMNOTRON)))
                    me->GetMotionMaster()->MovePath(omnotron->GetDBTableGUIDLow() * 10, true);
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (!who || !omnotron)
            {
                damage = 0;
                return;
            }

            if (damage >= me->GetHealth())
            {
                // The Encounter is Done
                instance->SetBossState(DATA_OMNOTRON_DEFENSE_SYSTEM, DONE);

                for (std::list<uint64>::const_iterator itr = trons.begin(); itr != trons.end(); ++itr)
                {
                    if (Creature* tron = me->GetCreature(*me, *itr))
                        if (tron != me)
                        {
                            tron->AI()->RemoveEncounterFrame();
                            tron->RemoveAllAuras();
                            tron->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            tron->SetLootMode(32);
                            me->Kill(tron);
                        }
                }

                Omnotron::DespawnMinions(me);
                RemoveEncounterFrame();
                me->RemoveAllAuras();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                omnotron->AI()->Talk(SAY_DEFEATED);
                omnotron->DespawnOrUnsummon();
            }
            else if (me != who)
                omnotron->AI()->SetData(tronId, damage);
        }

        void JustSummoned(Creature* summon)
        {
            summon->setFaction(me->getFaction());
            summon->SetInCombatWithZone();

            switch (summon->GetEntry())
            {
                case NPC_POWER_GENERATOR:
                    summon->SetReactState(REACT_PASSIVE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    summon->DespawnOrUnsummon(30000);
                    break;
            }
        }
    };
};

class npc_poison_bomb : public CreatureScript
{
public:
    npc_poison_bomb() : CreatureScript("npc_poison_bomb") { }

    struct npc_poison_bombAI : public ScriptedAI
    {
        npc_poison_bombAI(Creature * pCreature) : ScriptedAI(pCreature) {}

        uint32 uiFixe;
        uint32 uiBombeFixe;

        void Reset()
        {
            uiFixe = 2000;
            uiBombeFixe = 20000;
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiFixe <= uiDiff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.f, true))
                    DoCast(target, SPELL_FIXATE);
                uiFixe = 2000;
            } else uiFixe -= uiDiff;

            if (uiBombeFixe <= uiDiff)
            {
                DoCastAOE(SPELL_POISONBOMB);
                uiBombeFixe = 20000;
            } else uiBombeFixe -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_poison_bombAI(creature);
    }
};

class spell_activated : public SpellScriptLoader
{
public:
    spell_activated() : SpellScriptLoader("spell_activated") {}

    class spell_activated_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_activated_AuraScript);

        void HandleEffectCalcPeriodic(AuraEffect const * /*aurEff*/, bool & isPeriodic, int32 & amplitude)
        {
            isPeriodic = true;
            amplitude = 900;
        }

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (Creature* owner = GetOwner()->ToCreature())
            {
                uint32 energy = owner->GetPower(POWER_ENERGY);
                if (energy)
                    owner->SetPower(POWER_ENERGY, energy-1);
            }
        }

        void Register()
        {
            DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_activated_AuraScript::HandleEffectCalcPeriodic, EFFECT_1, SPELL_AURA_DUMMY);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_activated_AuraScript::HandlePeriodic, EFFECT_1, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_activated_AuraScript();
    }
};

class spell_shutting_down : public SpellScriptLoader
{
public:
    spell_shutting_down() : SpellScriptLoader("spell_shutting_down") { }

    class spell_shutting_down_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_shutting_down_SpellScript);

        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* c = GetCaster())
                if (Creature* caster = c->ToCreature())
                {
                    caster->AI()->RemoveEncounterFrame();
                    caster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    caster->SetDisplayId(33492);
                    caster->SetPower(POWER_ENERGY, 0);
                }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_shutting_down_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_shutting_down_SpellScript();
    }
};

class FlameThrowerTargetSelector
{
public:
    FlameThrowerTargetSelector(Unit* unit) : me(unit) {}

    bool operator() (WorldObject* object)
    {
        return object != me;
    }
private:
    Unit* me;
};

// 79505 Flamethrower
class spell_flamethrower : public SpellScriptLoader
{
public:
    spell_flamethrower() : SpellScriptLoader("spell_flamethrower") { }

    class spell_flamethrower_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_flamethrower_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            if (Unit* caster = GetCaster())
                if (Creature* me = caster->ToCreature())
                {
                    if (Player* target = Unit::GetPlayer(*me, me->AI()->GetGUID()))
                        unitList.remove_if (FlameThrowerTargetSelector(target));
                }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_flamethrower_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CHANNEL_TARGET);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_flamethrower_SpellScript();
    }
};

void AddSC_boss_omnotron_defense_system()
{
    new npc_omnotron_controller();
    new boss_omnotron_defense_system();
    new npc_poison_bomb();
    new spell_activated();
    new spell_shutting_down();
    new spell_flamethrower();
}
