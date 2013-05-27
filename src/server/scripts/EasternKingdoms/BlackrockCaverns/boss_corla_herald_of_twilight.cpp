
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
    SPELL_EVOLUTION                 = 75610, // Channel Spell
    SPELL_EVOLUTION_AURA            = 75697, // Aura Stacks (Dummy)
    SPELL_TWILIGHT_EVOLUTION        = 75732, // If 100 Stacks on the target are reached
    SPELL_AURA_OF_ACCELERATION      = 75817,
    SPELL_DARK_COMMAND              = 75823,
    SPELL_KNEELING_IN_SUPPLICATION  = 75608,
    SPELL_DRAIN_ESSENCE             = 75645,
    SPELL_FORCE_BLAST               = 76522, // Twilight Zaelots
    SPELL_GRAVITY_STRIKE            = 76561,
    SPELL_GRIEVOUS_WHIRL            = 93658,
    SPELL_SHADOW_STRIKE             = 66134
};

enum Events
{
    EVENT_DARK_COMMAND              = 1, // Corla   
    EVENT_EVOLUTION                 = 2, // Twilight Zaelots
    EVENT_FORCE_BLAST               = 3,
    EVENT_GRAVITY_STRIKE            = 4,
    EVENT_GRIEVOUS_WHIRL            = 5,
    EVENT_SHADOW_STRIKE             = 6
};

enum Texts
{
    SAY_AGGRO,
    SAY_POWER,
    SAY_WARNING,
    SAY_ENLIGHTENED,
    SAY_DEATH
};

class boss_corla_herald_of_twilight : public CreatureScript
{
public:
    boss_corla_herald_of_twilight() : CreatureScript("boss_corla_herald_of_twilight") { }  

    struct boss_corla_herald_of_twilightAI : public BossAI
    {
        boss_corla_herald_of_twilightAI(Creature* creature) : BossAI(creature, DATA_CORLA_HERALD_OF_TWILIGHT) {}

        uint32 uiEssenceChannelTimer;

        void Reset()
        {
            _Reset();
            RemoveEncounterFrame();

            uiEssenceChannelTimer = 6000;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_DARK_COMMAND, 20000);
            Talk(SAY_AGGRO);
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isInCombat())
            {
                if (uiEssenceChannelTimer <= diff)
                {
                    DoCast(SPELL_DRAIN_ESSENCE);

                    uiEssenceChannelTimer = urand(13000, 17000);
                } else uiEssenceChannelTimer -= diff;
            }

            if (!UpdateVictim())
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

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            RemoveEncounterFrame();

            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_corla_herald_of_twilightAI (creature);
    }
};

class npc_twilight_zealot : public CreatureScript
{
public:
    npc_twilight_zealot() : CreatureScript("npc_twilight_zealot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_zealotAI (creature);
    }

    struct npc_twilight_zealotAI : public ScriptedAI
    {
        npc_twilight_zealotAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        EventMap events;
        InstanceScript* instance;

        Creature* netheressenzTrigger;

        void Reset()
        {
            if (!me->HasAura(SPELL_KNEELING_IN_SUPPLICATION))
                DoCast(me, SPELL_KNEELING_IN_SUPPLICATION);
            
            me->RemoveAurasDueToSpell(SPELL_TWILIGHT_EVOLUTION);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            netheressenzTrigger = me->GetCreature(*me, instance->GetData64(NPC_NETHER_ESSENCE_TRIGGER));
            if (netheressenzTrigger)
            {
                events.ScheduleEvent(EVENT_EVOLUTION, 1000);
            }
        }

        void UpdateAI(uint32 Diff)
        {

            if (!me->isInCombat())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_EVOLUTION:
                    {
                        netheressenzTrigger->CastSpell(me, SPELL_EVOLUTION, true);
                        events.ScheduleEvent(EVENT_EVOLUTION, urand(800, 1100));
                        break;
                    }
                case EVENT_FORCE_BLAST:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target,SPELL_FORCE_BLAST);

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
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_corla_herald_of_twilight()
{
    new boss_corla_herald_of_twilight();
    //new npc_twilight_zealot();
}
