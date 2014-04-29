
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "the_stonecore.h"

enum MillhouseTexts
{
    SAY_FLEE                = 0,
    SAY_IMPENDING_DOOM_1    = 1,
    SAY_IMPENDING_DOOM_2    = 2,
};

enum MillhouseSpells
{
    SPELL_CLEAR_ALL_DEBUFFS             = 34098,
    SPELL_SHADOW_BOLT                   = 92641,
    SPELL_IMPENDING_DOOOOOM             = 86838,
    SPELL_IMPENDING_DOOOOOM_CHANNEL     = 86830,
    SPELL_SPECIAL_BLEND                 = 81220,
};

enum MillhouseEvents
{
    EVENT_SHADOW_BOLT = 1,
    EVENT_IMPENDING_DOOM,
    EVENT_RESET_FLEE,
};

// 6076 - Corborus Event
class at_tsc_corborus_intro : public AreaTriggerScript
{
public:
    at_tsc_corborus_intro() : AreaTriggerScript("at_tsc_corborus_intro") {}

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*at*/)
    {
        if (InstanceScript* instance = player->GetInstanceScript())
        {
            if (!instance->GetData(DATA_CORBORUS_PRE_EVENT))
            {
                if (Creature* corborus = ObjectAccessor::GetCreature(*player, instance->GetData64(BOSS_CORBORUS)))
                {
                    instance->SetData(DATA_CORBORUS_PRE_EVENT, 1);
                    corborus->AI()->DoAction(1);
                }

                if (Creature* millhouse = player->FindNearestCreature(NPC_MILLHOUSE_MANASTORM, 800.0f, true))
                {
                    millhouse->AI()->TalkToMap(SAY_IMPENDING_DOOM_1);
                    millhouse->AI()->DoCastAOE(SPELL_IMPENDING_DOOOOOM);
                    millhouse->AI()->DoCastAOE(SPELL_IMPENDING_DOOOOOM_CHANNEL);
                }
            }
        }

        return false;
    }
};

Position const FleePos1 = {983.460f,  890.184f,  304.664f,  2.044f};
Position const FleePos2 = {1049.774f, 871.2968f, 295.0014f, 2.943f};
Position const FleePos3 = {1149.040f, 884.4310f, 284.9406f, 3.142f};

class npc_tsc_millhouse_manastorm : public CreatureScript
{
public:
    npc_tsc_millhouse_manastorm() : CreatureScript("npc_tsc_millhouse_manastorm") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tsc_millhouse_manastormAI(creature);
    }

    struct npc_tsc_millhouse_manastormAI : public ScriptedAI 
    {
        npc_tsc_millhouse_manastormAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            _running = false;
            _stepsDone = 0;
        }

        InstanceScript* instance;
        EventMap events;
        bool _running;
        uint8 _stepsDone;

        void Reset()
        {
            events.Reset();
            _running = false;
        }

        void JustReachedHome()
        {
            _running = false;
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_BOLT, 1);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
            if (me->HealthBelowPct(50) && !_running && _stepsDone <= 3)
            {
                if (_stepsDone == 0)
                {
                    DoCast(me, SPELL_CLEAR_ALL_DEBUFFS, false);
                    me->SetHomePosition(FleePos1);
                    Talk(SAY_FLEE);
                    me->AI()->EnterEvadeMode();
                    me->CombatStop(true);
                }
                if (_stepsDone == 1)
                {
                    DoCast(me, SPELL_CLEAR_ALL_DEBUFFS, false);
                    me->SetHomePosition(FleePos2);
                    Talk(SAY_FLEE);
                    me->AI()->EnterEvadeMode();
                    me->CombatStop(true);
                }
                if (_stepsDone == 2)
                {
                    DoCast(me, SPELL_CLEAR_ALL_DEBUFFS, false);
                    me->SetHomePosition(FleePos3);
                    Talk(SAY_FLEE);
                    me->AI()->EnterEvadeMode();
                    me->CombatStop(true);
                }

                me->DeleteThreatList();
                events.CancelEvent(EVENT_SHADOW_BOLT);
                _stepsDone++;
                _running = true;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHADOW_BOLT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, 2100);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_the_stonecore()
{
    new at_tsc_corborus_intro();
    new npc_tsc_millhouse_manastorm();
}
