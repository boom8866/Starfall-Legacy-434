
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
    // Beauty
    SPELL_TRANSFORMATION            = 76196,
    SPELL_BERSERK                   = 82395,
    SPELL_CHARGE                    = 76030,
    SPELL_FLAMEBREAK                = 76032,
    SPELL_MAGMA_SPIT                = 76031,
    SPELL_TERRIFYNG_ROAR            = 76028,

    // Whelps
    // +- Runty
    SPELL_ALMOST_FEROCIOUS          = 77783,

    // +- Others
    SPELL_LAVA_DOOL                 = 76628,
    SPELL_LITTLE_BREATH             = 76665
};

enum Events
{
    // Beauty
    EVENT_BERSERK                   = 1,
    EVENT_BERSEKER_CHARGE           = 2,
    EVENT_FLAMEBREAK                = 3,
    EVENT_MAGMA_SPIT                = 4,
    EVENT_TERRIFYNG_ROAR            = 5,

    // Whelps
    EVENT_LAVA_DROOL                = 6,
    EVENT_LITTLE_BREATH             = 7
};

enum Actions
{
    ACTION_BEAUTY_BERSERK   = 1
};

class boss_beauty : public CreatureScript
{
public:
    boss_beauty() : CreatureScript("boss_beauty") { }

    struct boss_beautyAI : public BossAI
    {
        boss_beautyAI(Creature* creature) : BossAI(creature, DATA_BEAUTY) {}

        void Reset()
        {
            _Reset();
            RemoveEncounterFrame();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_BERSEKER_CHARGE, urand(15000, 24000), 0, 0);
            events.ScheduleEvent(EVENT_FLAMEBREAK, urand(10000, 21000), 0, 0);
            events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(9000, 13000), 0, 0);
            events.ScheduleEvent(EVENT_TERRIFYNG_ROAR, urand(15000, 22000), 0, 0);
        }

        void DoAction(int32 action)
        {
            if (action == ACTION_BEAUTY_BERSERK && !me->HasAura(SPELL_BERSERK))
            {
                DoCast(me, SPELL_BERSERK);
                events.ScheduleEvent(EVENT_BERSERK, 1000, 0, 0);
            }
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
                    case EVENT_BERSEKER_CHARGE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        {
                            me->CastSpell(target, SPELL_CHARGE, true);
                            events.ScheduleEvent(EVENT_BERSEKER_CHARGE, urand(12000, 20000), 0, 0);
                        }
                        break;
                    }
                    case EVENT_FLAMEBREAK:
                    {
                        DoCastAOE(SPELL_FLAMEBREAK);
                        events.ScheduleEvent(EVENT_FLAMEBREAK, urand(5000, 9000), 0, 0);
                        break;
                    }
                    case EVENT_MAGMA_SPIT:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        {
                            me->CastSpell(target, SPELL_MAGMA_SPIT);
                            events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(9000, 13000), 0, 0);
                        }
                        break;
                    }
                    case SPELL_TERRIFYNG_ROAR:
                    {
                        DoCastAOE(SPELL_TERRIFYNG_ROAR);
                        events.ScheduleEvent(EVENT_TERRIFYNG_ROAR, urand(15000, 22000), 0, 0);
                        break;
                    }
                    case EVENT_BERSERK:
                    {
                        DoCast(me, SPELL_BERSERK);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            RemoveEncounterFrame();

            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_beautyAI (creature);
    }
};

class npc_runty : public CreatureScript
{
public:
    npc_runty() : CreatureScript("npc_runty") { }

    struct npc_runtyAI : public ScriptedAI
    {
        npc_runtyAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;

        void Reset()
        {
            me->RemoveAurasDueToSpell(SPELL_ALMOST_FEROCIOUS);
        }

        void EnterCombat(Unit* who)
        {
            DoCast(me, SPELL_ALMOST_FEROCIOUS);

            if (instance && me->GetMap()->IsHeroic())
            {
                if (Creature* beauty = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_BEAUTY)))
                    beauty->AI()->DoAction(ACTION_BEAUTY_BERSERK);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_runtyAI (creature);
    }
};

class npc_beauty_whelp : public CreatureScript
{
public:
    npc_beauty_whelp() : CreatureScript("npc_beauty_whelp") { }

    struct npc_beauty_whelpAI : public ScriptedAI
    {
        npc_beauty_whelpAI(Creature* creature) : ScriptedAI(creature), instance(me->GetInstanceScript()) {}

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* who)
        {
            if (instance && me->GetMap()->IsHeroic())
            {
                if (Creature* beauty = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_BEAUTY)))
                {
                    beauty->SetInCombatWithZone();
                    beauty->GetMotionMaster()->MoveChase(who, 2.0f, 0.0f);
                }
            }
            events.ScheduleEvent(EVENT_LAVA_DROOL, urand(10000, 20000), 0, 0);
            events.ScheduleEvent(EVENT_LITTLE_BREATH, urand(6000, 12000), 0, 0);
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
                case EVENT_LAVA_DROOL:
                    {
                        DoCast(me, SPELL_LAVA_DOOL);
                        events.ScheduleEvent(EVENT_LAVA_DROOL, urand(10000, 20000), 0, 0);
                        break;
                    }
                case EVENT_LITTLE_BREATH:
                    {
                        DoCastVictim(SPELL_LITTLE_BREATH);
                        events.ScheduleEvent(EVENT_LITTLE_BREATH, urand(6000, 12000), 0, 0);
                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_beauty_whelpAI (creature);
    }
};

void AddSC_boss_beauty()
{
    new boss_beauty();
    new npc_runty();
    new npc_beauty_whelp();
}
