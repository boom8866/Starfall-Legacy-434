
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

    SPELL_TRANSFORMATION            = 76196,
    SPELL_TRANSFORMATION_TRIGGERED  = 76200, // Visual Pre-Stage (triggeres: 76211)
    SPELL_TRANSFORMATION_EFFECT     = 76211, // Swap Effect
    SPELL_TRANSFORMATION_STUN       = 76242,
    SPELL_TRANSFORMATION_WHIRL      = 76274,
    SPELL_THUNDERCLAP               = 76186,
    SPELL_TWILIGHT_CORRUPTION       = 93613,
    SPELL_STONE_BLOW                = 76185,
    SPELL_SHADOWY_CORRUPTION        = 75054,

    // Shadow of Obsidius
    SPELL_CREPUSCOLAR_VEIL          = 76189,
    SPELL_TWITCHY                   = 76167,
    SPELL_SHADOW_VISUAL             = 76164
};

enum Events
{
    EVENT_THUNDERCLAP                   = 1,
    EVENT_TWILIGHT_CORRUPTION,
    EVENT_STONE_BLOW,
    EVENT_CHECK_ACHIEVEMENT_CRITERIA,
    EVENT_CHECK_POSITION
};

enum Texts
{
    SAY_AGGRO       = 0,
    SAY_STONE_BLOW,
    SAY_TRANSFORM,
    SAY_PLACE,
    SAY_DEATH
};

enum achievementId
{
    ACHIEVEMENT_ENTRY_ASCENDANT_DESCENDING  = 5284
};

class boss_ascendant_lord_obsidius : public CreatureScript
{
public:
    boss_ascendant_lord_obsidius() : CreatureScript("boss_ascendant_lord_obsidius") { }

    struct boss_ascendant_lord_obsidiusAI : public BossAI
    {
        boss_ascendant_lord_obsidiusAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_LORD_OBSIDIUS) {}

        void Reset()
        {
            _Reset();

            phase   = 1;
            warning = 1;
            uiCheckAura = 5000;
            shadowGuidCache = 0;

            RemoveEncounterFrame();

            me->RemoveAllAuras();
            ResetShadows();
            isEligibleForAchievement = true;
            _EnterEvadeMode();
        }

        void ForceShadowsInCombat()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_SHADOW_OF_OBSIDIUS, 150.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->ToCreature()->AI()->DoAction(1);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            Talk(SAY_AGGRO);
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_TWILIGHT_CORRUPTION, 10000);
            events.ScheduleEvent(EVENT_STONE_BLOW, 13000);
            events.ScheduleEvent(EVENT_CHECK_ACHIEVEMENT_CRITERIA, 1000);
            events.ScheduleEvent(EVENT_CHECK_POSITION, 3000);

            if (me->GetMap()->IsHeroic())
                events.ScheduleEvent(EVENT_THUNDERCLAP, 7000);

            ForceShadowsInCombat();
            isEligibleForAchievement = true;
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isInCombat() || me->HasAura(SPELL_SHADOWY_CORRUPTION))
            {
                if (uiCheckAura <= diff)
                {
                    ResetShadows();
                    uiCheckAura = 2000;
                }
                else
                    uiCheckAura -= diff;
            }

            if (!UpdateVictim() || me->HasAura(SPELL_SHADOWY_CORRUPTION) || me->HasAura(SPELL_TRANSFORMATION))
                return;

            // Transformation warning
            uint32 pct = 105 - (warning * 33.3f);
            if (pct < 30 ? false : me->HealthBelowPct(pct))
            {
                warning++;
                Talk(SAY_TRANSFORM, me->GetGUID());
            }

            // Transform
            pct = 100 - (phase * 33.3);
            if (pct < 30 ? false: me->HealthBelowPct(pct))
            {
                phase++;
                DoCast(SPELL_TRANSFORMATION);
                events.DelayEvents(8000);
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_THUNDERCLAP:
                    {
                        Talk(SAY_PLACE);
                        DoCast(SPELL_THUNDERCLAP);
                        events.ScheduleEvent(EVENT_THUNDERCLAP, urand(25000, 30000));
                        break;
                    }
                    case EVENT_TWILIGHT_CORRUPTION:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_TWILIGHT_CORRUPTION);
                        events.ScheduleEvent(EVENT_TWILIGHT_CORRUPTION, 10000);
                        break;
                    }
                    case EVENT_STONE_BLOW:
                    {
                        Talk(SAY_STONE_BLOW);
                        DoCastVictim(SPELL_STONE_BLOW);
                        events.ScheduleEvent(EVENT_STONE_BLOW, urand(20000, 25000));
                        break;
                    }
                    case EVENT_CHECK_ACHIEVEMENT_CRITERIA:
                    {
                        Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                        if (!PlayerList.isEmpty())
                        {
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            {
                                if (i->getSource()->isInCombat())
                                {
                                    if (Aura* veil = i->getSource()->GetAura(SPELL_CREPUSCOLAR_VEIL))
                                    {
                                        if (veil->GetStackAmount() >= 4)
                                        {
                                            isEligibleForAchievement = false;
                                            events.CancelEvent(EVENT_CHECK_ACHIEVEMENT_CRITERIA);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_ACHIEVEMENT_CRITERIA, 1000);
                        break;
                    }
                    case EVENT_CHECK_POSITION:
                    {
                        // Safety distance check to prevent abuse
                        if (me->getVictim() && me->getVictim()->GetPositionZ() > 72.0f)
                        {
                            ReturnShadows();
                            events.Reset();
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_POSITION, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void ReturnShadows()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_SHADOW_OF_OBSIDIUS, 150.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->ToCreature()->AI()->DoAction(3);
        }

        void RemoveShadowAfterDeath()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_SHADOW_OF_OBSIDIUS, 150.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->ToCreature()->AI()->DoAction(2);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            RemoveEncounterFrame();
            RemoveShadowAfterDeath();

            if (instance && IsHeroic() && isEligibleForAchievement == true)
                instance->DoCompleteAchievement(ACHIEVEMENT_ENTRY_ASCENDANT_DESCENDING);

            if (instance)
                instance->SetBossState(DATA_ASCENDANT_LORD_OBSIDIUS, DONE);

            _FinishDungeon();
            _JustDied();
        }

        void SetGUID(uint64 guid, int32 /*id*/ = 0)
        {
            shadowGuidCache = guid;
        }

        uint64 GetGUID(int32 /*id*/ = 0) const
        {
            return shadowGuidCache;
        }

        void ResetShadows()
        {
            std::list<Creature*> shadowsOfObsidius;
            GetCreatureListWithEntryInGrid(shadowsOfObsidius, me, NPC_SHADOW_OF_OBSIDIUS, 300.f);
            shadowsOfObsidius.push_back(me);

            for (std::list<Creature*>::const_iterator itr = shadowsOfObsidius.begin(); itr != shadowsOfObsidius.end(); ++itr)
            {
                if ((*itr) != me)
                {
                    if ((*itr)->isDead())
                        (*itr)->Respawn();

                    if ((*itr)->GetDistance((*itr)->GetHomePosition()) >= 3.f)
                        (*itr)->GetMotionMaster()->MoveTargetedHome();
                }

                if (me->FindNearestCreature(NPC_TWILIGHT_GUARD, 30.f))
                {
                    if (!(*itr)->HasAura(SPELL_SHADOWY_CORRUPTION))
                        (*itr)->AddAura(SPELL_SHADOWY_CORRUPTION, *itr);
                }
                else if ((*itr)->HasAura(SPELL_SHADOWY_CORRUPTION))
                    (*itr)->RemoveAllAuras();
            }
        }

        protected:
           bool isEligibleForAchievement;

           uint8 phase;
           uint8 warning;
           uint32 uiCheckAura;
           uint64 shadowGuidCache;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ascendant_lord_obsidiusAI (creature);
    }
};

class npc_shadow_of_obsidius : public CreatureScript
{
public:
    npc_shadow_of_obsidius() : CreatureScript("npc_shadow_of_obsidius")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadow_of_obsidiusAI(creature);
    }

    struct npc_shadow_of_obsidiusAI : public ScriptedAI
    {
        npc_shadow_of_obsidiusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        enum eventId
        {
            EVENT_CREPUSCOLAR_VEIL  = 1,
            EVENT_CHECK_POSITION
        };

        enum actionId
        {
            ACTION_FORCE_ENTER_COMBAT   = 1,
            ACTION_FORCE_DESPAWN,
            ACTION_FORCE_EVADE
        };

        enum npcId
        {
            NPC_OBSIDIUS    = 39705
        };

        EventMap events;

        void Reset()
        {
            events.Reset();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->AddAura(SPELL_TWITCHY, me);
            me->AddAura(SPELL_SHADOW_VISUAL, me);
            _EnterEvadeMode();
        }

        void ForceShadowsInCombat()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_SHADOW_OF_OBSIDIUS, 150.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->ToCreature()->AI()->DoAction(1);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CREPUSCOLAR_VEIL, urand(3000, 4000), 0, 0);
            me->AddAura(SPELL_TWITCHY, me);
            me->AddAura(SPELL_SHADOW_VISUAL, me);
            ForceShadowsInCombat();
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
                    case EVENT_CREPUSCOLAR_VEIL:
                    {
                        DoCastVictim(SPELL_CREPUSCOLAR_VEIL);
                        events.ScheduleEvent(EVENT_CREPUSCOLAR_VEIL, urand(3000, 4000), 0, 0);
                        break;
                    }
                    case EVENT_CHECK_POSITION:
                    {
                        // Safety distance check to prevent abuse
                        if (me->getVictim() && me->getVictim()->GetPositionZ() > 72.0f)
                        {
                            if (Creature* obsidius = me->FindNearestCreature(NPC_OBSIDIUS, 300.0f, true))
                            {
                                obsidius->ClearInCombat();
                                obsidius->CombatStop();
                                obsidius->CastStop();
                                obsidius->AI()->EnterEvadeMode();
                            }

                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_PACIFIED);
                            me->ClearInCombat();
                            me->CombatStop();
                            me->CastStop();
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_POSITION, 3000);
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
                case ACTION_FORCE_ENTER_COMBAT:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    DoZoneInCombat();
                    break;
                }
                case ACTION_FORCE_DESPAWN:
                {
                    me->DespawnOrUnsummon(1);
                    break;
                }
                case ACTION_FORCE_EVADE:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                    me->ClearInCombat();
                    me->CombatStop();
                    me->CastStop();
                    EnterEvadeMode();
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        InstanceScript* instance;
    };
};

// 76196 Transformation
class spell_transformation : public SpellScriptLoader
{
public:
    spell_transformation() : SpellScriptLoader("spell_transformation") {}

    class spell_transformation_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_transformation_SpellScript);

        void HandleOnHitDummy(SpellEffIndex /*effIndex*/)
        {
            if (Creature* me = GetHitCreature())
            {
                if (Unit* casterUnit = GetCaster())
                {
                    if (Creature* caster = casterUnit->ToCreature())
                    {
                        if (me->GetEntry() == NPC_SHADOW_OF_OBSIDIUS && caster->GetEntry() == BOSS_ASCENDANT_LORD_OBSIDIUS && !caster->AI()->GetGUID())
                        {
                            // Target is one of Obsidius Shadows
                            caster->AI()->SetGUID(me->GetGUID());
                            me->CastSpell(me, SPELL_TRANSFORMATION_WHIRL);
                            me->CastSpell(me, SPELL_TRANSFORMATION_TRIGGERED);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_transformation_SpellScript::HandleOnHitDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_transformation_SpellScript();
    }
};

// 76211 Transformation
class spell_transformation_dummy : public SpellScriptLoader
{
public:
    spell_transformation_dummy() : SpellScriptLoader("spell_transformation_dummy") {}

    class spell_transformation_dummy_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_transformation_dummy_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* me = caster->ToCreature())
                {
                    if (me->GetEntry() == BOSS_ASCENDANT_LORD_OBSIDIUS)
                    {
                        if (Creature* target = me->GetCreature(*me, me->AI()->GetGUID()))
                        {
                            Position targetPos = *target;
                            target->NearTeleportTo(*me);
                            target->SetInCombatWithZone();

                            me->NearTeleportTo(targetPos);
                            me->SetInCombatWithZone();
                            me->getThreatManager().resetAllAggro();
                            me->getHostileRefManager().deleteReferences();
                            if (Player* player = me->FindNearestPlayer(100.0f, true))
                                me->AI()->AttackStart(player);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_transformation_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_transformation_dummy_SpellScript();
    }
};

class achievement_brc_ascendant_descending : public AchievementCriteriaScript
{
public:
    achievement_brc_ascendant_descending() : AchievementCriteriaScript("achievement_brc_ascendant_descending")
    {
    }

    bool OnCheck(Player* player, Unit* /*target*/)
    {
        return false;
    }
};

void AddSC_boss_ascendant_lord_obsidius()
{
    new boss_ascendant_lord_obsidius();
    new npc_shadow_of_obsidius();
    new spell_transformation();
    new spell_transformation_dummy();
    new achievement_brc_ascendant_descending();
}
