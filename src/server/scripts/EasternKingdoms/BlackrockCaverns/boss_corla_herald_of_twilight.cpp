
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

enum Spells
{
    SPELL_EVOLUTION_VISUAL          = 75610,    // Channel Spell
    SPELL_EVOLUTION                 = 75697,    // Aura Stacks (Dummy) Normal
    SPELL_EVOLUTION_H               = 87378,    // Aura Stacks (Dummy) Heroic
    SPELL_TWILIGHT_EVOLUTION        = 75732,    // Zealot Transformation

    SPELL_AURA_OF_ACCELERATION      = 75817,    // Corla: Speedup?
    SPELL_DARK_COMMAND              = 75823,    // Corla: Fear

    SPELL_KNEELING_IN_SUPPLICATION  = 75608,    // Zealot kneel block aura
    SPELL_DRAIN_ESSENCE_CHANNELING  = 75645,    // Visual before combat

    SPELL_NETHERESSENCE_AURA        = 75649,    // Trigger Aura
    SPELL_NETHERESSENCE_VISUAL      = 75650,

    SPELL_FORCE_BLAST               = 76522,    // Twilight Zealot: Force Blast
    SPELL_GRAVITY_STRIKE            = 76561,    // Twilight Zealot: Gravity Strike
    SPELL_GRIEVOUS_WHIRL            = 93658,    // Twilight Zealot: Grievous Whirl
    SPELL_SHADOW_STRIKE             = 66134     // Twilight Zealot: Shadow Strike
};

enum Events
{
    EVENT_DARK_COMMAND      = 1,
    EVENT_FORCE_BLAST,
    EVENT_GRAVITY_STRIKE,
    EVENT_GRIEVOUS_WHIRL,
    EVENT_SHADOW_STRIKE
};

enum Actions
{
    ACTION_TRIGGER_START_CHANNELING     = 1,
    ACTION_TRIGGER_STOP_CHANNELING
};

enum Texts
{
    SAY_AGGRO,
    SAY_POWER,
    SAY_WARNING,
    SAY_ENLIGHTENED,
    SAY_DEATH
};

enum achievementId
{
    ACHIEVEMENT_ENTRY_ARRESTED_DEVELOPEMENT     = 5282
};

Position const summonPositions[4] =
{
    // Twilight Zealot Position
    { 565.629f, 983.000f, 155.354f, 0.68912f },
    { 580.919f, 982.981f, 155.354f, 2.05572f },
    { 573.676f, 980.619f, 155.354f, 1.58448f },

    // Nether Essence Position (Ray Triggering)
    //{ 573.711f, 905.179f, 179.154f, 0.00000f },           // This should be blizzlike but is too much distant
    { 573.770f, 945.396f, 168.809f, 1.56939f },
};

class boss_corla_herald_of_twilight : public CreatureScript
{
public:
    boss_corla_herald_of_twilight() : CreatureScript("boss_corla_herald_of_twilight")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_corla_herald_of_twilightAI(creature);
    }

    struct boss_corla_herald_of_twilightAI : public BossAI
    {
        boss_corla_herald_of_twilightAI(Creature* creature) : BossAI(creature, DATA_CORLA_HERALD_OF_TWILIGHT)
        {
            instance = creature->GetInstanceScript();
            for (uint8 i = 0; i <= RAID_MODE(1, 2); i++)
                NetherEssenceTrigger[i] = NULL;
            for (uint8 i = 0; i <= RAID_MODE(1, 2); i++)
                TwilightZealotsList[i] = NULL;

            zealotsKilled = 0;
        }

        enum actionIdAchievement
        {
            ACTION_DO_COMPLETE_ACHIEVEMENT  = 1
        };

        EventMap events;

        void Reset()
        {
            _Reset();
            events.Reset();
            me->RemoveAllAuras();
            me->CastSpell(me, SPELL_DRAIN_ESSENCE_CHANNELING, true);
            RehandleZealots();
            zealotsKilled = 0;
        }

        void EnterEvadeMode()
        {
            me->DespawnCreaturesInArea(NPC_NETHER_ESSENCE_TRIGGER);
            me->DespawnCreaturesInArea(NPC_TWILIGHT_ZEALOT);
            RemoveCharmedPlayers();
            RemoveEncounterFrame();
            zealotsKilled = 0;
            _DespawnAtEvade();
        }

        void RemoveNetherTriggers()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->GetEntry() == NPC_NETHER_ESSENCE_TRIGGER && (*itr)->ToTempSummon())
                    (*itr)->ToCreature()->DespawnOrUnsummon(1000);
            }
        }

        void RehandleZealots()
        {
            for (uint8 i = 0; i <= RAID_MODE(1, 2); i++)
            {
                TwilightZealotsList[i] = me->SummonCreature(NPC_TWILIGHT_ZEALOT, summonPositions[i], TEMPSUMMON_MANUAL_DESPAWN);

                if (me->isInCombat())
                    NetherEssenceTrigger[i] = TwilightZealotsList[i]->SummonCreature(NPC_NETHER_ESSENCE_TRIGGER, summonPositions[3], TEMPSUMMON_MANUAL_DESPAWN);

                TwilightZealotsList[i]->NearTeleportTo(summonPositions[i].GetPositionX(), summonPositions[i].GetPositionY(), summonPositions[i].GetPositionZ(), summonPositions[i].GetOrientation());
                TwilightZealotsList[i]->CastSpell(TwilightZealotsList[i], SPELL_KNEELING_IN_SUPPLICATION, true);
            }
        }

        void RemoveCharmedPlayers()
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    if (i->getSource()->isCharmed())
                    {
                        i->getSource()->RemoveCharmedBy(me);
                        i->getSource()->Kill(i->getSource(), true);
                    }
                }
            }
        }

        void EnterCombat(Unit* /*victim*/)
        {
            me->CastStop();
            me->DespawnCreaturesInArea(NPC_NETHER_ESSENCE_TRIGGER);
            me->DespawnCreaturesInArea(NPC_TWILIGHT_ZEALOT);

            RehandleZealots();

            if (me->getVictim())
                me->GetMotionMaster()->MoveChase(me->getVictim());

            events.ScheduleEvent(EVENT_DARK_COMMAND, 20000);

            for (uint8 i = 0; i <= RAID_MODE(1, 2); i++)
            {
                if (NetherEssenceTrigger[i] && NetherEssenceTrigger[i] != NULL)
                    NetherEssenceTrigger[i]->GetAI()->DoAction(ACTION_TRIGGER_START_CHANNELING);
            }

            if (NetherEssenceTrigger[0] && NetherEssenceTrigger[0] != NULL)
                NetherEssenceTrigger[0]->CastSpell(NetherEssenceTrigger[0], SPELL_NETHERESSENCE_AURA, true);

            me->AddAura(SPELL_AURA_OF_ACCELERATION, me);

            Talk(SAY_AGGRO);
            AddEncounterFrame();

            zealotsKilled = 0;
            _EnterCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || !CheckInRoom())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DARK_COMMAND:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_DARK_COMMAND);
                        events.ScheduleEvent(EVENT_DARK_COMMAND, 20000);
                        break;
                    }
                }
            }

            // Safety distance check to prevent exit area
            if (me->GetDistance2d(573.44f, 987.68f) > 50)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            RemoveCharmedPlayers();
            RemoveEncounterFrame();
            if (instance && zealotsKilled >= 3 && me->GetMap()->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
                instance->DoCompleteAchievement(ACHIEVEMENT_ENTRY_ARRESTED_DEVELOPEMENT);
            if (instance)
                instance->SetBossState(DATA_CORLA_HERALD_OF_TWILIGHT, DONE);
            me->DespawnCreaturesInArea(NPC_NETHER_ESSENCE_TRIGGER);
            me->DespawnCreaturesInArea(NPC_TWILIGHT_ZEALOT);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER && roll_chance_i(75))
                Talk(SAY_ENLIGHTENED);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DO_COMPLETE_ACHIEVEMENT:
                {
                    zealotsKilled++;
                    break;
                }
                default:
                    break;
            }
        }

        protected:
            InstanceScript* instance;
            Creature* TwilightZealotsList[3];
            Creature* NetherEssenceTrigger[3];

            uint8 zealotsKilled;
    };
};

class npc_twilight_zealot : public CreatureScript
{
public:
    npc_twilight_zealot() : CreatureScript("npc_twilight_zealot")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_zealotAI(creature);
    }

    struct npc_twilight_zealotAI : public ScriptedAI
    {
        npc_twilight_zealotAI(Creature* creature) : ScriptedAI(creature), isEvolved(false)
        {
        }

        EventMap events;

        enum actionId
        {
            ACTION_EVOLVE_ZEALOT    = 1
        };

        enum npcId
        {
            NPC_ENTRY_CORLA     = 39679
        };

        void Reset()
        {
            events.Reset();
            isEvolved = false;
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || isEvolved == false || !me->isInCombat() || !me->HasAura(SPELL_TWILIGHT_EVOLUTION))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FORCE_BLAST:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_FORCE_BLAST);
                        events.ScheduleEvent(EVENT_FORCE_BLAST, 10000);
                        break;
                    }
                    case EVENT_GRAVITY_STRIKE:
                    {
                        DoCastVictim(SPELL_GRAVITY_STRIKE);
                        events.ScheduleEvent(EVENT_GRAVITY_STRIKE, 22000);
                        break;
                    }
                    case EVENT_GRIEVOUS_WHIRL:
                    {
                        DoCastAOE(SPELL_GRIEVOUS_WHIRL);
                        events.ScheduleEvent(EVENT_GRIEVOUS_WHIRL, 7000);
                        break;
                    }
                    case EVENT_SHADOW_STRIKE:
                    {
                        DoCastVictim(SPELL_SHADOW_STRIKE);
                        events.ScheduleEvent(EVENT_SHADOW_STRIKE, 14000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_EVOLVE_ZEALOT:
                {
                    if (isEvolved == false && !me->HasAura(SPELL_KNEELING_IN_SUPPLICATION))
                    {
                        events.ScheduleEvent(EVENT_FORCE_BLAST, 10000);
                        events.ScheduleEvent(EVENT_GRAVITY_STRIKE, 22000);
                        events.ScheduleEvent(EVENT_GRIEVOUS_WHIRL, 7000);
                        events.ScheduleEvent(EVENT_SHADOW_STRIKE, 14000);

                        isEvolved = true;

                        me->SetReactState(REACT_AGGRESSIVE);
                        me->GetMotionMaster()->MoveChase(GetPlayerAtMinimumRange(1.0f));
                        me->Attack(GetPlayerAtMinimumRange(1.0f), false);
                    }
                    break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            // For Achievement criteria
            if (Creature* corla = me->FindNearestCreature(NPC_ENTRY_CORLA, 100.0f, true))
            {
                if (isEvolved == true)
                    corla->AI()->DoAction(1);
            }
            me->RemoveAllAuras();
        }

    protected:
        bool isEvolved;
    };
};

class npc_corla_netheressence_trigger : public CreatureScript
{
public:
    npc_corla_netheressence_trigger() : CreatureScript("npc_corla_netheressence_trigger")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_corla_netheressence_triggerAI(creature);
    }

    struct npc_corla_netheressence_triggerAI : public ScriptedAI
    {
        npc_corla_netheressence_triggerAI(Creature* creature) : ScriptedAI(creature)
        {
            channelTarget = NULL;
            lastTarget = NULL;
            zealot = NULL;
            alreadyEmpowered = false;
        }

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_CORLA             = 39679,
            NPC_ENTRY_NETHERESSENCE     = 778370
        };

        enum eventId
        {
            EVENT_CHECK_PLAYER_BETWEEN  = 1,
            EVENT_SEND_NETHER_VISUAL
        };

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
            alreadyEmpowered = false;
        }

        void IsSummonedBy(Unit* summoner)
        {
            zealot = summoner;
            alreadyEmpowered = false;
        }

        void UpdateAI(uint32 diff)
        {
            if (channelTarget == NULL || zealot == NULL)
                return;

            if (zealot && zealot->IsInWorld())
            {
                if (zealot->isAlive())
                {
                    if (zealot->HasAura(SPELL_TWILIGHT_EVOLUTION))
                        return;
                }
                else
                    return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PLAYER_BETWEEN:
                    {
                        if (!zealot)
                        {
                            events.RescheduleEvent(EVENT_CHECK_PLAYER_BETWEEN, 800);
                            break;
                        }
                        channelTarget = zealot;

                        if (channelTarget && channelTarget->IsInWorld() && channelTarget != NULL && !channelTarget->HasAura(SPELL_TWILIGHT_EVOLUTION))
                        {
                            DoCast(channelTarget, SPELL_EVOLUTION_VISUAL, true);

                            // Refresh duration!
                            if (channelTarget && channelTarget->IsInWorld() && channelTarget != NULL && channelTarget->HasAura(SPELL_EVOLUTION))
                                channelTarget->GetAura(SPELL_EVOLUTION)->RefreshDuration();
                            else if (channelTarget && channelTarget->IsInWorld() && channelTarget != NULL && channelTarget->HasAura(SPELL_EVOLUTION_H))
                                channelTarget->GetAura(SPELL_EVOLUTION_H)->RefreshDuration();
                        }

                        // Ritual done, init transformations!
                        if (channelTarget && channelTarget->IsInWorld() && channelTarget != NULL)
                        {
                            if (channelTarget->GetAuraCount(SPELL_EVOLUTION) == 100 || channelTarget->GetAuraCount(SPELL_EVOLUTION_H) == 100)
                            {
                                if (channelTarget == zealot)
                                {
                                    channelTarget->RemoveAllAuras();
                                    zealot->CastSpell(channelTarget, SPELL_TWILIGHT_EVOLUTION, true);
                                    if (Creature* corla = me->FindNearestCreature(NPC_ENTRY_CORLA, 500.0f, true))
                                    {
                                        if (alreadyEmpowered == false)
                                        {
                                            corla->AI()->Talk(SAY_POWER);
                                            alreadyEmpowered = true;
                                        }

                                        corla->AI()->Talk(SAY_WARNING);
                                    }
                                    events.CancelEvent(EVENT_CHECK_PLAYER_BETWEEN);
                                    break;
                                }

                                // Player will be controlled by Corla
                                if (channelTarget->ToPlayer())
                                {
                                    channelTarget->CastSpell(channelTarget, SPELL_TWILIGHT_EVOLUTION, true);
                                    if (Creature* corla = me->FindNearestCreature(NPC_ENTRY_CORLA, 500.0f, true))
                                        channelTarget->SetCharmedBy(corla, CHARM_TYPE_CHARM);

                                    events.CancelEvent(EVENT_CHECK_PLAYER_BETWEEN);
                                    break;
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_PLAYER_BETWEEN, 600);
                        break;
                    }
                    case EVENT_SEND_NETHER_VISUAL:
                    {
                        DoCast(me, SPELL_NETHERESSENCE_VISUAL, true);
                        events.RescheduleEvent(EVENT_SEND_NETHER_VISUAL, urand(3500, 4000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TRIGGER_START_CHANNELING:
                {
                    CharmedPlayerList.clearReferences();
                    channelTarget = zealot;
                    events.ScheduleEvent(EVENT_CHECK_PLAYER_BETWEEN, 1);
                    events.ScheduleEvent(EVENT_SEND_NETHER_VISUAL, 1);
                    lastTarget = me;
                    break;
                }
                case ACTION_TRIGGER_STOP_CHANNELING:
                {
                    lastTarget = channelTarget = NULL;
                    break;
                }
            }
        }

    protected:
        Map::PlayerList CharmedPlayerList;

        Unit* zealot;
        Unit* channelTarget;
        Unit* lastTarget;

        bool alreadyEmpowered;
    };
};

class EvolutionTargetSelector : public std::unary_function<Unit *, bool>
{
public:
    EvolutionTargetSelector(Unit* me, const WorldObject* victim) : _me(me), _victim(victim)
    {
    }

    enum targetId
    {
        NPC_TWILIGHT_ZEALOT_N = 50284,
        NPC_TWILIGHT_ZEALOT_H = 50285
    };

    bool operator() (WorldObject* target)
    {
        if (!target)
            return false;

        // Filtering for Units
        if (target && target->GetTypeId() == TYPEID_UNIT && (target->GetEntry() == NPC_TWILIGHT_ZEALOT_N || target->GetEntry() == NPC_TWILIGHT_ZEALOT_H) && !target->ToUnit()->HasAura(SPELL_TWILIGHT_EVOLUTION) && target->ToUnit()->isAlive())
        {
            Map::PlayerList const &PlayerList = _me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    if (i->getSource()->IsInBetween(_me, target, 1.0f))
                        return true;
                }
            }
            return false;
        }

        // Filtering for Players
        if (target && target->GetTypeId() == TYPEID_PLAYER && !target->ToUnit()->HasAura(SPELL_TWILIGHT_EVOLUTION))
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(target, 80.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(target, targets, u_check);
            target->VisitNearbyObject(80.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && ((*itr)->GetEntry() == NPC_TWILIGHT_ZEALOT_N || (*itr)->GetEntry() == NPC_TWILIGHT_ZEALOT_H) && (*itr)->isAlive())
                {
                    Map::PlayerList const &PlayerList = _me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->getSource()->IsInBetween(_me, target, 1.0f))
                                return true;
                        }
                    }
                    if (target->IsInBetween((*itr), _me, 1.0f))
                        return false;
                }
            }
        }
        return true;
    }

    Unit* _me;
    WorldObject const* _victim;
};

class spell_brc_evolution : public SpellScriptLoader
{
public:
    spell_brc_evolution() : SpellScriptLoader("spell_brc_evolution")
    {
    }

    class spell_brc_evolution_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_brc_evolution_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!targets.empty())
            {
                if (Unit* caster = GetCaster())
                {
                    targets.remove_if(EvolutionTargetSelector(caster, caster->getVictim()));
                    if (WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets))
                    {
                        targets.clear();
                        targets.push_back(target);
                    }
                }
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_brc_evolution_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_brc_evolution_SpellScript();
    }
};

class spell_brc_twilight_evolution : public SpellScriptLoader
{
public:
    spell_brc_twilight_evolution() : SpellScriptLoader("spell_brc_twilight_evolution")
    {
    }

    class spell_brc_twilight_evolution_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_brc_twilight_evolution_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetUnitOwner())
            {
                // Only in Blackrock Caverns
                if (owner->GetTypeId() == TYPEID_UNIT && owner->GetMapId() == 645)
                    owner->ToCreature()->AI()->DoAction(1);
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_brc_twilight_evolution_AuraScript::OnApply, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_brc_twilight_evolution_AuraScript();
    }
};

class achievement_brc_arrested_developement : public AchievementCriteriaScript
{
public:
    achievement_brc_arrested_developement() : AchievementCriteriaScript("achievement_brc_arrested_developement")
    {
    }

    bool OnCheck(Player* /*player*/, Unit* /*target*/)
    {
        return false;
    }
};

void AddSC_boss_corla_herald_of_twilight()
{
    new boss_corla_herald_of_twilight();
    new npc_twilight_zealot();
    new npc_corla_netheressence_trigger();
    new spell_brc_evolution();
    new spell_brc_twilight_evolution();
    new achievement_brc_arrested_developement();
}
