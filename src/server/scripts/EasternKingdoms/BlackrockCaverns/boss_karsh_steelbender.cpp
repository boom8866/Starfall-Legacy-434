
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

#define SPELL_SUPERHEATED_ARMOR RAID_MODE(75846, 93567)

enum Spells
{
    SPELL_QUICKSILVER_ARMOR         = 75842,

    SPELL_HEAT_WAVE                 = 75851,
    SPELL_BURNING_METAL             = 76002,
    SPELL_CLEAVE                    = 15284,
    SPELL_LAVA_SPOUT_N              = 76007,
    SPELL_LAVA_SPOUT_H              = 93565,

    SPELL_SUMMON_LAVA_POOLS         = 93547
};

enum Events
{
    EVENT_CLEAVE                    = 1,
    EVENT_CHECK_HEAT_SPOT,
    EVENT_ERRUPT_VISUAL,
    EVENT_SUMMON_ADDS
};

enum Texts
{
    SAY_AGGRO,
    SAY_FIRE,
    SAY_WARNING,
    SAY_IMPURITY,
    SAY_DEATH
};

enum actionId
{
    ACTION_DO_COMPLETE_ACHIEVEMENT  = 1,
    ACTION_LAVA_ERUPT
};

enum achievementId
{
    ACHIEVEMENT_ENTRY_TOO_HOT_TO_HANDLE     = 5283
};

Position const middlePos = {237.166f, 785.067f, 95.67f, 0};

class ErruptTriggerSelector
{
public:
    bool operator() (Unit* unit)
    {
        return unit->GetDistance(middlePos) > 40.f;
    }
};

class boss_karsh_steelbender : public CreatureScript
{
public:
    boss_karsh_steelbender() : CreatureScript("boss_karsh_steelbender") { }

    struct boss_karsh_steelbenderAI : public BossAI
    {
        boss_karsh_steelbenderAI(Creature* creature) : BossAI(creature, DATA_KARSH_STEELBENDER) {}

        bool sentWarning;

        enum npcId
        {
            NPC_LAVA_POOL_TRIGGER   = 50423
        };

        void Reset()
        {
            _Reset();
            RemoveEncounterFrame();

            me->RemoveAllAuras();
            me->DespawnCreaturesInArea(NPC_BOUND_FLAMES);
            me->DespawnCreaturesInArea(NPC_LAVA_POOL);
            sentWarning = false;
            eligibleForAchievement = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            AddEncounterFrame();

            Talk(SAY_AGGRO);
            DoCast(me, SPELL_QUICKSILVER_ARMOR);

            events.ScheduleEvent(EVENT_CLEAVE, urand(15000,18000));
            events.ScheduleEvent(EVENT_CHECK_HEAT_SPOT, 1000);
            eligibleForAchievement = false;
        }

        bool IsInHeatSpot()
        {
            if (me->GetDistance(middlePos) < 3.0f)
                return true;

            if (Creature* pool = me->FindNearestCreature(NPC_LAVA_POOL_TRIGGER, 5.0f, true))
            {
                if (pool->GetDistance(me) < 2.5f)
                    return true;
            }

            return false;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!(me->HasAura(SPELL_QUICKSILVER_ARMOR) || me->HasAura(SPELL_SUPERHEATED_ARMOR)))
            {
                DoLavaErrupt();
                sentWarning = false;
                Talk(SAY_FIRE);

                DoCast(me, SPELL_QUICKSILVER_ARMOR);

                if (!me->GetMap()->IsHeroic())
                    return;

                events.ScheduleEvent(EVENT_SUMMON_ADDS, 2500);
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CLEAVE:
                    {
                        Talk(SAY_IMPURITY);
                        DoCastVictim(SPELL_CLEAVE);
                        events.ScheduleEvent(EVENT_CLEAVE, urand(15000, 18000));
                        break;
                    }
                    case EVENT_CHECK_HEAT_SPOT:
                    {
                        if (IsInHeatSpot())
                        {
                            if (me->HasAura(SPELL_QUICKSILVER_ARMOR))
                                me->RemoveAura(SPELL_QUICKSILVER_ARMOR);

                            DoCast(me, SPELL_SUPERHEATED_ARMOR);

                            // Achievement: Too Hot To Handle (Heroic)
                            if (Aura* armor = me->GetAura(SPELL_SUPERHEATED_ARMOR))
                            {
                                if (armor->GetStackAmount() >= 15)
                                    eligibleForAchievement = true;
                            }

                            DoCastAOE(SPELL_HEAT_WAVE);

                            if (!sentWarning)
                            {
                                sentWarning = true;
                                Talk(SAY_WARNING);
                            }
                        }

                        events.ScheduleEvent(EVENT_CHECK_HEAT_SPOT, 1000);
                        break;
                    }
                    case EVENT_ERRUPT_VISUAL:
                    {
                        DoLavaErrupt();
                        break;
                    }
                    case EVENT_SUMMON_ADDS:
                    {
                        // Heroic: Summon Adds
                        for (uint8 i = 0; i <= 2; i++)
                        {
                            Position pos;
                            me->GetRandomNearPosition(pos, 35.f);
                            me->SummonCreature(NPC_BOUND_FLAMES, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                        }
                        events.CancelEvent(EVENT_SUMMON_ADDS);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType)
        {
            if (victim && damage > 0 && damageType == DIRECT_DAMAGE)
            {
                if (Aura* aura = me->GetAura(SPELL_SUPERHEATED_ARMOR))
                {
                    int32 basePoints = RAID_MODE(1000, 2000);
                    me->CastCustomSpell(SPELL_BURNING_METAL, SPELLVALUE_BASE_POINT0, basePoints * aura->GetStackAmount(), victim);
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);

            me->DespawnCreaturesInArea(NPC_BOUND_FLAMES);
            me->DespawnCreaturesInArea(NPC_LAVA_POOL);
            DoLavaErrupt();
            RemoveEncounterFrame();

            if (instance && eligibleForAchievement == true && me->GetMap()->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
                instance->DoCompleteAchievement(ACHIEVEMENT_ENTRY_TOO_HOT_TO_HANDLE);

            if (instance)
                instance->SetBossState(DATA_KARSH_STEELBENDER, DONE);

            _JustDied();
        }

        void DoLavaErrupt()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_LAVA_SPOUT_TRIGGER, 300.0f);

            if (creatures.empty())
                return;

            creatures.remove_if (ErruptTriggerSelector());

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->CastSpell((*iter), DUNGEON_MODE(SPELL_LAVA_SPOUT_N, SPELL_LAVA_SPOUT_H), true);

            events.CancelEvent(EVENT_ERRUPT_VISUAL);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DO_COMPLETE_ACHIEVEMENT:
                {
                    eligibleForAchievement = true;
                    break;
                }
                case ACTION_LAVA_ERUPT:
                {
                    events.ScheduleEvent(EVENT_ERRUPT_VISUAL, 1);
                    break;
                }
                default:
                    break;
            }
        }

        protected:
            bool eligibleForAchievement;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_karsh_steelbenderAI (creature);
    }
};

class npc_brc_quicksilver : public CreatureScript
{
public:
    npc_brc_quicksilver() : CreatureScript("npc_brc_quicksilver")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brc_quicksilverAI(creature);
    }

    struct npc_brc_quicksilverAI : public ScriptedAI
    {
        npc_brc_quicksilverAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        #define SPELL_FLAME_BUFFET RAID_MODE(76621, 87379)

        enum spellId
        {
            SPELL_COOLED        = 82287,
            SPELL_BURNING_HEAT  = 82301
        };

        enum eventId
        {
            EVENT_CHECK_COMBAT  = 1,
            EVENT_FLAME_BUFFET
        };

        void Reset()
        {
            me->CastSpell(me, SPELL_COOLED, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FLAME_BUFFET, 100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_COMBAT:
                    {
                        if (me->isInCombat() && !me->HasAura(SPELL_COOLED))
                        {
                            if (Aura* heat = me->GetAura(SPELL_BURNING_HEAT))
                                heat->RefreshDuration();
                            events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
                            break;
                        }

                        if (!me->isInCombat() && !me->HasAura(SPELL_COOLED))
                            me->CastSpell(me, SPELL_COOLED, true);

                        events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
                        break;
                    }
                    case EVENT_FLAME_BUFFET:
                    {
                        if (!me->HasAura(SPELL_COOLED))
                            DoCastVictim(SPELL_FLAME_BUFFET, true);
                        events.RescheduleEvent(EVENT_FLAME_BUFFET, 1500);
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!me->HasAura(SPELL_COOLED))
                DoMeleeAttackIfReady();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_BURNING_HEAT:
                {
                    me->RemoveAurasDueToSpell(SPELL_COOLED);
                    me->GetMotionMaster()->MoveRandom(10.0f);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                case SPELL_COOLED:
                {
                    DoStopAttack();
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_PASSIVE);
                    me->DeleteThreatList();
                    me->CombatStop(true);
                    me->SetLootRecipient(NULL);
                    me->ResetPlayerDamageReq();
                    break;
                }
            }
        }
    };
};

class npc_brc_bound_flames : public CreatureScript
{
public:
    npc_brc_bound_flames() : CreatureScript("npc_brc_bound_flames")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brc_bound_flamesAI(creature);
    }

    struct npc_brc_bound_flamesAI : public ScriptedAI
    {
        npc_brc_bound_flamesAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        enum npcId
        {
            SPELL_LAVA_POOL     = 93547
        };

        void JustDied(Unit* /*killer*/)
        {
            me->CastSpell(me, SPELL_LAVA_POOL, true);
            me->DespawnOrUnsummon(30000);
        }
    };
};

class npc_brc_lava_pool : public CreatureScript
{
public:
    npc_brc_lava_pool() : CreatureScript("npc_brc_lava_pool")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brc_lava_poolAI(creature);
    }

    struct npc_brc_lava_poolAI : public ScriptedAI
    {
        npc_brc_lava_poolAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetReactState(REACT_PASSIVE);
        }
    };
};

class achievement_brc_too_hot_to_handle : public AchievementCriteriaScript
{
public:
    achievement_brc_too_hot_to_handle() : AchievementCriteriaScript("achievement_brc_too_hot_to_handle")
    {
    }

    bool OnCheck(Player* player, Unit* /*target*/)
    {
        return false;
    }
};

class spell_brc_superheated_qa : public SpellScriptLoader
{
public:
    spell_brc_superheated_qa() : SpellScriptLoader("spell_brc_superheated_qa")
    {
    }

    class spell_brc_superheated_qa_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_brc_superheated_qa_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetUnitOwner())
            {
                // Only in Blackrock Caverns
                if (owner->GetTypeId() == TYPEID_UNIT && owner->GetMapId() == 645)
                    owner->ToCreature()->AI()->DoAction(ACTION_LAVA_ERUPT);
            }
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_brc_superheated_qa_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_brc_superheated_qa_AuraScript();
    }
};

void AddSC_boss_karsh_steelbender()
{
    new boss_karsh_steelbender();
    new npc_brc_quicksilver();
    new npc_brc_bound_flames();
    new npc_brc_lava_pool();
    new achievement_brc_too_hot_to_handle();
    new spell_brc_superheated_qa();
}
