
/*
* Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
*
* THIS particular file is NOT free software.
* You are not allowed to share or redistribute it.
*/

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"
#include "Vehicle.h"

enum spellId
{
    SPELL_SHOCK_BLAST               = 76008,
    SPELL_SHOCK_BLAST_HC            = 91477,
    SPELL_FUNGAL_SPORES             = 76001,
    SPELL_GEYSER                    = 75722,
    SPELL_GEYSER_VISUAL             = 75699,
    SPELL_GEYSER_EFFECT             = 75700,
    SPELL_GEYSER_DAMAGE_NPC_HC      = 94047,
    SPELL_GEYSER_DAMAGE_NPC         = 94046,
    SPELL_WATERSPOUT                = 75683,
    SPELL_WATERSPOUT_SUMMON         = 90495,
    SPELL_WATERSPOUT_SUMMON_HC      = 90497,
    SPELL_WATERSPOUT_VISUAL         = 90440,
    SPELL_WATERSPOUT_DEBUFF         = 90479,
    SPELL_WATERSPOUT_CHARGE         = 90461,
    SPELL_TELEPORT                  = 87328
};

enum yellsId
{
    // Lady Naz'jar
    SAY_AGGRO       = 0,
    SAY_66_PRECENT,
    SAY_33_PRECENT,
    SAY_KILL_1,
    SAY_KILL_2,
    SAY_DEATH
};

enum eventId
{
    EVENT_GEYSER                = 1,
    EVENT_FUNGAL_SPORES,
    EVENT_SHOCK_BLAST,
    EVENT_LEAVE_CLEAR_DREAMES,
    EVENT_WATERSPOUT_CAST,
    EVENT_CHECK_BUFF
};

class boss_lady_nazjar : public CreatureScript
{
public:
    boss_lady_nazjar() : CreatureScript("boss_lady_nazjar") { }

    struct boss_lady_nazjarAI : public BossAI
    {
        boss_lady_nazjarAI(Creature* creature) : BossAI(creature, DATA_LADY_NAZJAR) {}

        uint8 minionsLeft;
        uint8 phase;
        uint8 spoutCount;

        void Reset()
        {
            _Reset();
            LeaveDreamesPhase();
            phase = 1;
            minionsLeft = 0;
            spoutCount = 0;
            DespawnMinions();

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1|UNIT_FIELD_FLAGS|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_PACIFIED);
            me->SetReactState(REACT_AGGRESSIVE);
            RemoveEncounterFrame();

            if (GameObject* ladyDoor = me->FindNearestGameObject(GO_LADY_NAZJAR_DOOR, 150.0f))
                ladyDoor->SetGoState(GO_STATE_ACTIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            phase = 1;
            spoutCount = 0;
            _EnterCombat();
            Talk(SAY_AGGRO);
            AddEncounterFrame();
            phase = 1;
            events.ScheduleEvent(EVENT_GEYSER, 11000);
            events.ScheduleEvent(EVENT_FUNGAL_SPORES, urand(14000, 15000));
            events.ScheduleEvent(EVENT_SHOCK_BLAST, 13000);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(RAND(SAY_KILL_1, SAY_KILL_2));
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            if (summon->GetEntry() == NPC_SUMMONED_WITCH || summon->GetEntry() == NPC_SUMMONED_GUARD)
            {
                if (minionsLeft && --minionsLeft <= 0)
                    LeaveDreamesPhase();
            }
        }

        void EnterDreamsPhase()
        {
            ++phase;
            me->InterruptNonMeleeSpells(false);
            me->FinishSpell(CURRENT_CHANNELED_SPELL, false);

            // Enter clear dreams phase
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            DoTeleportTo(191.812f, 802.43f, 807.721f);
            DoCast(me, SPELL_TELEPORT);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1);
            events.ScheduleEvent(EVENT_WATERSPOUT_CAST, 100);
            events.ScheduleEvent(EVENT_CHECK_BUFF, 1000);
            spoutCount++;
        }

        void LeaveDreamesPhase()
        {
            // Leave clear dreams phase
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1);
            me->RemoveAurasDueToSpell(DUNGEON_MODE(SPELL_WATERSPOUT_SUMMON, SPELL_WATERSPOUT_SUMMON_HC));
            me->InterruptNonMeleeSpells(false);
            me->SetReactState(REACT_AGGRESSIVE);
            if (Unit* victim = me->getVictim())
                me->GetMotionMaster()->MoveChase(victim);
            events.CancelEvent(EVENT_CHECK_BUFF);
        }

        void JustSummoned(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_SUMMONED_WITCH:
                case NPC_SUMMONED_GUARD:
                {
                    summon->AI()->DoZoneInCombat(summon);
                    break;
                }
                default:
                    break;
            }
        }

        void SpawnMinions()
        {
            for (uint8 i = 0; i <= 2; ++i)
            {
                Position pos;
                me->GetRandomNearPosition(pos, frand(20.f, 30.f));
                pos.m_positionZ = me->GetPositionZ();
                me->SummonCreature(i ? NPC_SUMMONED_WITCH : NPC_SUMMONED_GUARD, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
            }

            minionsLeft += 3;
        }

        void UpdateAI(uint32 diff)
        {
            if (me->isInCombat())
                events.Update(diff);

            float pct = 100.0f;
            switch (phase)
            {
                case 1:
                    pct = 60.0f;
                    break;
                case 2:
                    pct = 30.0f;
                    break;
                default:
                    break;
            }
            if (me->HealthBelowPct(pct))
            {
                if (me->isInCombat() && (spoutCount == 0 || spoutCount == 1))
                {
                    EnterDreamsPhase();
                    return;
                }
            }

            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GEYSER:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50, true))
                            DoCast(target, SPELL_GEYSER);

                        events.ScheduleEvent(EVENT_GEYSER, urand(14000,17000));
                        break;
                    }
                    case EVENT_FUNGAL_SPORES:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60, true))
                            DoCast(target, SPELL_FUNGAL_SPORES);

                        events.ScheduleEvent(EVENT_FUNGAL_SPORES, urand(14000, 15000));
                        break;
                    }
                    case EVENT_SHOCK_BLAST:
                    {
                        DoCastVictim(DUNGEON_MODE(SPELL_SHOCK_BLAST, SPELL_SHOCK_BLAST_HC));
                        events.ScheduleEvent(EVENT_SHOCK_BLAST, 13000);
                        break;
                    }
                    case EVENT_WATERSPOUT_CAST:
                    {
                        me->SetReactState(REACT_PASSIVE);
                        if (me->HealthBelowPct(61) && me->HealthAbovePct(58))
                            Talk(SAY_66_PRECENT);

                        if (me->HealthBelowPct(31) && me->HealthAbovePct(28))
                            Talk(SAY_33_PRECENT);

                        DoCastAOE(SPELL_WATERSPOUT);
                        DoCastAOE(DUNGEON_MODE(SPELL_WATERSPOUT_SUMMON, SPELL_WATERSPOUT_SUMMON_HC), true);
                        SpawnMinions();
                        break;
                    }
                    case EVENT_CHECK_BUFF:
                    {
                        if (!me->HasAura(SPELL_WATERSPOUT))
                        {
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1);
                            if (Unit* victim = me->getVictim())
                                me->GetMotionMaster()->MoveChase(victim);
                            events.CancelEvent(EVENT_CHECK_BUFF);
                        }
                        else
                            events.RescheduleEvent(EVENT_CHECK_BUFF, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            RemoveEncounterFrame();
            if (GameObject* ladyDoor = me->FindNearestGameObject(GO_LADY_NAZJAR_DOOR, 200.0f))
                ladyDoor->SetGoState(GO_STATE_READY);
            if (GameObject* console = me->FindNearestGameObject(GO_CONTROL_SYSTEM, 150.0f))
                console->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            DespawnMinions();
            _JustDied();
        }

        void DespawnMinions()
        {
            me->DespawnCreaturesInArea(NPC_SUMMONED_WITCH);
            me->DespawnCreaturesInArea(NPC_SUMMONED_GUARD);
            me->DespawnCreaturesInArea(NPC_SUMMONED_WATERSPOUT);
            me->DespawnCreaturesInArea(NPC_SUMMONED_GEYSER);
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_lady_nazjarAI (creature);
    }
};

class npc_geyser : public CreatureScript
{
public:
    npc_geyser() : CreatureScript("npc_geyser") { }

    struct npc_geyserAI : public ScriptedAI
    {
        npc_geyserAI(Creature* creature) : ScriptedAI(creature), _instance(creature->GetInstanceScript())
        {
            uiErrupt = 6000;
            isErrupted = false;
            SetCombatMovement(false);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_GEYSER_DAMAGE_NPC_HC, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_GEYSER_DAMAGE_NPC, true);
        }

        uint32 uiErrupt;
        bool isErrupted;

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC); 
        }

        void KilledUnit(Unit* victim)
        {
            if (IsHeroic() && (victim->GetEntry() == NPC_SUMMONED_WITCH || victim->GetEntry() == NPC_SUMMONED_GUARD))
                _instance->DoCompleteAchievement(ACHIEVEMENT_OLD_FAITHFUL);
        }

        void NpcKillCheck(uint32 entry, uint32 npc)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 5.0f);
            GetCreatureListWithEntryInGrid(creatures, me, npc, 5.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                me->CastSpell((*iter), SPELL_GEYSER_DAMAGE_NPC, true);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!isErrupted && uiErrupt <= diff)
            {
                isErrupted = true;
                DoCastAOE(SPELL_GEYSER_EFFECT, true);
                NpcKillCheck(NPC_SUMMONED_WITCH, NPC_SUMMONED_GUARD);
                me->DespawnOrUnsummon(3000);
            }
            else
                uiErrupt -= diff;
        }

    private:
        InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new npc_geyserAI (creature);
    }
};

class npc_waterspout : public CreatureScript
{
public:
    npc_waterspout() : CreatureScript("npc_waterspout") { }

    struct npc_waterspoutAI : public ScriptedAI
    {
        npc_waterspoutAI(Creature* creature) : ScriptedAI(creature) {me->DespawnOrUnsummon(9000);}

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC); 
        }

        void IsSummonedBy(Unit* creator)
        {
            me->SetReactState(REACT_PASSIVE);
            if (creator->GetEntry() == BOSS_LADY_NAZJAR)
            {
                Position pos = *creator;
                me->MovePosition(pos, 42.f, frand(0, 2.f));
                pos.m_positionZ = creator->GetPositionZ();
                me->GetMotionMaster()->MovePoint(0, pos);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if(Unit* target = GetPlayerAtMinimumRange(0.3f))
            {
                if (me->GetDistance(target) < 1.5f)
                    DoCast(target, SPELL_WATERSPOUT_DEBUFF, true);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_waterspoutAI (creature);
    }
};

class KnockbackTargetSelector
{
public:
    KnockbackTargetSelector() { }

    bool operator()(WorldObject* object) const
    {
        if (object->GetTypeId() != TYPEID_PLAYER)
            return true;

        return false;
    }
};

//  Waterspout 75690
class spell_tot_waterspout_knockback : public SpellScriptLoader
{
public:
    spell_tot_waterspout_knockback() : SpellScriptLoader("spell_tot_waterspout_knockback") { }

    class spell_tot_waterspout_knockback_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tot_waterspout_knockback_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if(KnockbackTargetSelector());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tot_waterspout_knockback_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tot_waterspout_knockback_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tot_waterspout_knockback_SpellScript();
    }
};

// 90479 Waterspout
class spell_tot_waterspout_vehicle : public SpellScriptLoader
{
public:
    spell_tot_waterspout_vehicle() : SpellScriptLoader("spell_tot_waterspout_vehicle") { }

    class spell_tot_waterspout_vehicle_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tot_waterspout_vehicle_AuraScript);

        void HandleEffectApply(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (Unit* caster = GetCaster())
                {
                    if (Vehicle* vehicle = caster->GetVehicleKit())
                        target->EnterVehicle(caster, 0);
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_tot_waterspout_vehicle_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_CONTROL_VEHICLE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tot_waterspout_vehicle_AuraScript();
    }
};

void AddSC_boss_lady_nazjar()
{
    new boss_lady_nazjar();
    new npc_geyser();
    new npc_waterspout();
    new spell_tot_waterspout_knockback();
    new spell_tot_waterspout_vehicle();
}
