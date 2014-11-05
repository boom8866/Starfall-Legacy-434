
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
    SPELL_CALL_FOR_HELP             = 82137,
    SPELL_THUNDERCLAP               = 76186,
    SPELL_TWILIGHT_CORRUPTION       = 93613,
    SPELL_STONE_BLOW                = 76185,
    SPELL_SHADOWY_CORRUPTION        = 75054
};

enum Events
{
    EVENT_THUNDERCLAP               = 1,
    EVENT_TWILIGHT_CORRUPTION       = 2,
    EVENT_STONE_BLOW                = 3
};

enum Texts
{
    SAY_AGGRO,
    SAY_STONE_BLOW,
    SAY_TRANSFORM,
    SAY_PLACE,
    SAY_DEATH
};

class boss_ascendant_lord_obsidius : public CreatureScript
{
public:
    boss_ascendant_lord_obsidius() : CreatureScript("boss_ascendant_lord_obsidius") { }

    struct boss_ascendant_lord_obsidiusAI : public BossAI
    {
        boss_ascendant_lord_obsidiusAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_LORD_OBSIDIUS) {}

        uint8 phase;
        uint8 warning;
        uint32 uiCheckAura;
        uint64 shadowGuidCache;

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
        }

        void EnterCombat(Unit* /*who*/) 
        {
            _EnterCombat();

            Talk(SAY_AGGRO);
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_TWILIGHT_CORRUPTION, 10000);
            events.ScheduleEvent(EVENT_STONE_BLOW, 13000);

            if (me->GetMap()->IsHeroic())
                events.ScheduleEvent(EVENT_THUNDERCLAP, 7000);
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
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            RemoveEncounterFrame();

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
            GetCreatureListWithEntryInGrid(shadowsOfObsidius, me, NPC_SHADOW_OF_OBSIDIUS, 50.f);
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

                if (me->FindNearestCreature(NPC_TWILIGHT_GUARD, 20.f))
                {
                    if (!(*itr)->HasAura(SPELL_SHADOWY_CORRUPTION))
                        (*itr)->AddAura(SPELL_SHADOWY_CORRUPTION, *itr);
                }
                else if ((*itr)->HasAura(SPELL_SHADOWY_CORRUPTION))
                    (*itr)->RemoveAllAuras();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ascendant_lord_obsidiusAI (creature);
    }

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
                if (Unit* casterUnit = GetCaster())
                    if (Creature* caster = casterUnit->ToCreature())
                        if (me->GetEntry() == NPC_SHADOW_OF_OBSIDIUS && caster->GetEntry() == BOSS_ASCENDANT_LORD_OBSIDIUS && !caster->AI()->GetGUID())
                        { // Target is one of Obsidius Shadows

                            caster->AI()->SetGUID(me->GetGUID());
                            me->CastSpell(me, SPELL_TRANSFORMATION_WHIRL, true);
                            me->CastSpell(me, SPELL_TRANSFORMATION_TRIGGERED, true);
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

void AddSC_boss_ascendant_lord_obsidius()
{
    new boss_ascendant_lord_obsidius();
    new spell_transformation();
    new spell_transformation_dummy();
}
