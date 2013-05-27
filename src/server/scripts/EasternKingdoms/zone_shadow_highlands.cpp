/*
 * Copyright (C) 2013 Northstrider
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

//-----------------------------[SHADOW HIGHLANDS ARENA QUESTS]------------------------------//
enum ArenaCreatures
{
    NPC_GURGTHOCK   = 46935,
    // Boss 1
    NPC_HURP_DERP   = 46944,
};

enum ArenaEvents
{
    // Boss 1
    EVENT_HEAD_CRUNCHER     = 1,
    EVENT_WHIRLWIND         = 2,
    EVENT_FEARING_YELL      = 3,
};

enum ArenaSpells
{
    // Boss 1
    SPELL_HEAD_CRUNCHER     = 88482,
    SPELL_WHIRWIND          = 83016,
    SPELL_FEARING_YELL      = 91933,
};

enum ArenaActions
{
    ACTION_SUMMON_HURP_DERP     = 1,
};

Position const HurpDerpSpawnPos = {-4135.439f, -5191.270f, -9.427f};
Position const HurpDerpMovePos  = {-4182.390f, -5148.450f, -7.736f};

class npc_gurgthok_cata : public CreatureScript
{
public:
    npc_gurgthok_cata() : CreatureScript("npc_gurgthok_cata") { }

    struct npc_gurgthok_cataAI : public ScriptedAI
    {
        npc_gurgthok_cataAI(Creature* creature) : ScriptedAI(creature)
        {
            currentBoss = false;
        }

        bool currentBoss;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_HURP_DERP:
                    if (!currentBoss)
                    {
                        if (Creature* derp = me->SummonCreature(NPC_HURP_DERP, HurpDerpSpawnPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000))
                        {
                            derp->setActive(true);
                            derp->GetMotionMaster()->MovePoint(0, HurpDerpMovePos);
                            currentBoss = true;
                        }
                    }
                    else
                        currentBoss = false;
                    break;
            }
        }

        void BossClear()
        {
            currentBoss = false;
        }

        void SummonedCreatureDies(Creature* summon , Unit*)
        {
            BossClear();
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gurgthok_cataAI(creature);
    }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
            case 27861:
            case 27862:
            case 27863:
                CAST_AI(npc_gurgthok_cata::npc_gurgthok_cataAI, creature->AI())->DoAction(ACTION_SUMMON_HURP_DERP);
                creature->MonsterYell("DEBUG: quest detected!", LANG_UNIVERSAL, 0);
                break;
        }

        return true;
    }

    bool OnQuestComplete(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 27861 || quest->GetQuestId() == 27862 || quest->GetQuestId() == 27863)
        {
            switch (quest->GetQuestId())
            {
                case 27861:
                case 27862:
                case 27863:
                    if (Creature* gurg = creature->FindNearestCreature(NPC_GURGTHOCK, 50.0f, true))
                        gurg->AI()->DoAction(ACTION_SUMMON_HURP_DERP);
                    break;
            }
        }
        return true;
    }
};

class npc_hurp_derp : public CreatureScript
{
public:
    npc_hurp_derp() : CreatureScript("npc_hurp_derp") { }

    struct npc_hurp_derpAI : public ScriptedAI
    {
        npc_hurp_derpAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_WHIRLWIND, 10000);
            events.ScheduleEvent(EVENT_FEARING_YELL, 20000);
            events.ScheduleEvent(EVENT_HEAD_CRUNCHER, 25000);
            me->GetMotionMaster()->Clear(true);
            me->GetMotionMaster()->MoveChase(who, 50.0f);
        }

        void Reset()
        {
            events.Reset();
        }

        void JustDied(Unit* /*who*/)
        {
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
                    case EVENT_WHIRLWIND:
                        DoCastAOE(SPELL_WHIRWIND);
                        events.ScheduleEvent(EVENT_WHIRLWIND, 30000);
                        break;
                    case EVENT_FEARING_YELL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, false))
                            DoCast(target, SPELL_FEARING_YELL);
                        events.ScheduleEvent(EVENT_FEARING_YELL, 30000);
                        break;
                    case EVENT_HEAD_CRUNCHER:
                        DoCastAOE(SPELL_HEAD_CRUNCHER);
                        events.ScheduleEvent(EVENT_HEAD_CRUNCHER, 30000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon();
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hurp_derpAI(creature);
    }
};

void AddSC_shadow_highlands()
{
    new npc_hurp_derp();
    new npc_gurgthok_cata();
}
