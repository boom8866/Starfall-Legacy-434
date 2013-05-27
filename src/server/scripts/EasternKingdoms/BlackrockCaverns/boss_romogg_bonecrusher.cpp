
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
    SPELL_CALL_FOR_HELP             = 82137,
    SPELL_QUAKE                     = 75272,
    SPELL_QUAKE_SUMMON              = 75372,
    SPELL_THE_SKULLCRACKER          = 75543,
    SPELL_WOUNDING_STRIKE           = 69651,

    SPELL_CHAINS_OF_WOE             = 75539,
    SPELL_CHAINS_OF_WOE_INITIAL     = 75437,
    SPELL_CHAINS_OF_WOE_TELEPORT    = 75464,
    SPELL_CHAINS_OF_WOE_VISUAL      = 75441,
    SPELL_CHAINS_OF_WOE_TRIGGERED   = 82189,
    SPELL_CHAINS_OF_WOE_ROOT_AURA   = 82192

};

enum Events
{
    EVENT_QUAKE                     = 1,
    EVENT_CHAINS_OF_WOE             = 2,
    EVENT_THE_SCULLCRACKER          = 3,
    EVENT_WOUNDING_STRIKE           = 4
};

enum Timers
{
    TIMER_QUAKE                     = 25000,
    TIMER_CHAINS_OF_WOE             = 40000,
    TIMER_WOUNDING_STRIKE           = 15000
};

enum Texts
{
    SAY_AGGRO,
    SAY_HELP,
    SAY_SKULLCRACKER,
    SAY_WARNING,
    SAY_WHAT_YOU_GET,
    SAY_DEATH
};

uint32 const helpers[4] =
{
    NPC_TWILIGHT_TORTURER,
    NPC_TWILIGHT_SADIST,
    NPC_CRAZED_MAGE,
    NPC_MAD_PRISONER
};

class boss_romogg_bonecrusher : public CreatureScript
{
public:
    boss_romogg_bonecrusher() : CreatureScript("boss_romogg_bonecrusher") { }

    struct boss_romogg_bonecrusherAI : public BossAI
    {
        boss_romogg_bonecrusherAI(Creature* creature) : BossAI(creature, DATA_ROMOGG_BONECRUSHER) {}

        void Reset()
        {   
            _Reset();
            RemoveEncounterFrame();

            me->DespawnCreaturesInArea(NPC_CHAINS_OF_WOE);
            me->DespawnCreaturesInArea(NPC_ANGERED_EARTH);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_QUAKE, 13000);
            events.ScheduleEvent(EVENT_CHAINS_OF_WOE, 17000);
            events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 7000);

            DoCast(SPELL_CALL_FOR_HELP);
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
                case EVENT_QUAKE:
                    {
                        DoCastAOE(SPELL_QUAKE);
                        if (me->GetMap()->IsHeroic())
                            for (uint8 i = 0; i < 3; i++)
                                DoCast(me, SPELL_QUAKE_SUMMON, true);

                        events.ScheduleEvent(EVENT_QUAKE, TIMER_QUAKE);
                        break;
                    }
                case EVENT_CHAINS_OF_WOE:
                    {
                        events.DelayEvents(EVENT_QUAKE, 10000);
                        events.ScheduleEvent(EVENT_THE_SCULLCRACKER, 2500);
                        events.ScheduleEvent(EVENT_CHAINS_OF_WOE, TIMER_CHAINS_OF_WOE);

                        Talk(SAY_WARNING, me->GetGUID());
                        DoCast(SPELL_CHAINS_OF_WOE);
                        break;
                    }

                case EVENT_THE_SCULLCRACKER:
                    {
                        Talk(SAY_SKULLCRACKER);
                        DoCastVictim(SPELL_THE_SKULLCRACKER);
                        break;
                    }
                case EVENT_WOUNDING_STRIKE:
                    {
                        Talk(SAY_WHAT_YOU_GET);
                        DoCastVictim(SPELL_WOUNDING_STRIKE);
                        events.ScheduleEvent(EVENT_WOUNDING_STRIKE, TIMER_WOUNDING_STRIKE);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            if (summon->GetEntry() == NPC_CHAINS_OF_WOE)
            {
                Map::PlayerList const &players = me->GetMap()->GetPlayers();
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    if (!itr->getSource()->isGameMaster())
                    {
                        Position pos;
                        summon->GetNearPosition(pos, frand(0.3f, 3.f), frand(0, 6.f));
                        itr->getSource()->NearTeleportTo(pos.m_positionX, pos.m_positionY, summon->GetPositionZ(), frand(0, 6.f));
                    }
            }
        }

        void JustDied(Unit * /*victim*/)
        {
            me->DespawnCreaturesInArea(NPC_CHAINS_OF_WOE);
            me->DespawnCreaturesInArea(NPC_ANGERED_EARTH);
            RemoveEncounterFrame();

            Talk(SAY_DEATH);

            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_romogg_bonecrusherAI (creature);
    }
};

// 82189 Chains of Woe
class spell_chains_of_woe : public SpellScriptLoader
{
public:
    spell_chains_of_woe() : SpellScriptLoader("spell_chains_of_woe") { }

    class spell_chains_of_woe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_chains_of_woe_SpellScript);

        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                Map::PlayerList const &players = caster->GetMap()->GetPlayers();

                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    if (!itr->getSource()->isGameMaster())
                        caster->AddAura(SPELL_CHAINS_OF_WOE_ROOT_AURA, itr->getSource());
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_chains_of_woe_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_chains_of_woe_SpellScript();
    }
};

// 82137 Call for Help
class spell_call_for_help : public SpellScriptLoader
{
public:
    spell_call_for_help() : SpellScriptLoader("spell_call_for_help") { }

    class spell_call_for_help_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_call_for_help_SpellScript);

        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                Creature* me = caster->ToCreature();
                if (!me)
                    return;

                Unit* victim = me->getVictim();
                if (!victim)
                    return;

                std::list<Creature*> helperList;
                for (uint8 i = 0; i < sizeof(helpers); ++i)
                {
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, me, helpers[i], 52.f);

                    for (std::list<Creature*>::const_iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                        if ((*itr)->isAlive())
                            helperList.push_back(*itr);
                }

                me->AI()->DoZoneInCombat();
                for (std::list<Creature*>::const_iterator itr = helperList.begin(); itr != helperList.end(); ++itr)
                {
                    (*itr)->SetInCombatWithZone();
                    (*itr)->GetMotionMaster()->MoveChase(victim);
                }

                if (me->GetEntry() == BOSS_ROMOGG_BONECRUSHER)
                    me->AI()->Talk(SAY_HELP, me->GetGUID());
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_call_for_help_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_call_for_help_SpellScript();
    }
};

void AddSC_boss_romogg_bonecrusher()
{
    new boss_romogg_bonecrusher();
    new spell_chains_of_woe();
    new spell_call_for_help();
}