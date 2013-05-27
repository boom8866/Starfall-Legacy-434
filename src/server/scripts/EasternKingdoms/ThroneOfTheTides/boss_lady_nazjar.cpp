
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"

enum Spells
{
    SPELL_SHOCK_BLAST               = 76008,
    SPELL_FUNGAL_SPORES             = 76001,

    SPELL_GEYSER                    = 75722,
    SPELL_GEYSER_VISUAL             = 75699,
    SPELL_GEYSER_EFFECT             = 75700,

    SPELL_WATERSPOUT                = 75683,
    SPELL_WATERSPOUT_SUMMON         = 90495,
    SPELL_WATERSPOUT_SUMMON_HC      = 90497,
    SPELL_WATERSPOUT_VISUAL         = 90440,
    SPELL_WATERSPOUT_DEBUFF         = 90479,
    SPELL_WATERSPOUT_CHARGE         = 90461,
};

enum Yells
{
    SAY_AGGRO,
    SAY_CLEAR_DREAMS,
    SAY_DEATH
};

enum Events
{
    EVENT_GEYSER                = 1,
    EVENT_FUNGAL_SPORES         = 2,
    EVENT_SHOCK_BLAST           = 3,
    EVENT_LEAVE_CLEAR_DREAMES   = 4,
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

        void Reset()
        {
            _Reset();

            minionsLeft = 0;
            DespawnMinions();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            Talk(SAY_AGGRO);

            events.ScheduleEvent(EVENT_GEYSER, 11000);
            events.ScheduleEvent(EVENT_FUNGAL_SPORES, urand(14000, 15000));
            events.ScheduleEvent(EVENT_SHOCK_BLAST, 13000);
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            if (summon->GetEntry() == NPC_SUMMONED_WITCH || summon->GetEntry() == NPC_SUMMONED_GUARD)
                if(minionsLeft && --minionsLeft <= 0)
                {
                    // Leave clear dreams phase
                    me->RemoveAurasDueToSpell((SPELL_WATERSPOUT_SUMMON, SPELL_WATERSPOUT_SUMMON_HC));
                    me->InterruptNonMeleeSpells(false);

                    if (Unit* victim = me->getVictim())
                        me->GetMotionMaster()->MoveChase(victim);
                }
        }

        void JustSummoned(Creature* summon)
        {
            if (summon->GetEntry() == NPC_SUMMONED_WATERSPOUT)
            {
                Position pos = *me;
                me->MovePosition(pos, 42.f, frand(0, 2.f));
                pos.m_positionZ = me->GetPositionZ();

                summon->GetMotionMaster()->MovePoint(0, pos);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (me->isInCombat())
            {
                events.Update(diff);
                // _DoAggroPulse(diff);
            }

            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            float const pct = 100.f - (phase * 33.3f);
            if (pct < 30.f ? false : me->HealthBelowPct(pct))
            {
                ++phase;
                events.Reset();

                // Enter clear dreams phase
                me->NearTeleportTo(me->GetHomePosition());
                me->DestroyForNearbyPlayers();

                for (uint8 i = 0; i <= 2; ++i)
                {
                    Position pos;
                    me->GetRandomNearPosition(pos, frand(20.f, 30.f));
                    pos.m_positionZ = me->GetPositionZ();

                    me->SummonCreature(i ? NPC_SUMMONED_WITCH : NPC_SUMMONED_GUARD, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                }

                minionsLeft = 3;
                Talk(SAY_CLEAR_DREAMS);

                DoCast(me, DUNGEON_MODE(SPELL_WATERSPOUT_SUMMON, SPELL_WATERSPOUT_SUMMON_HC), true);
                DoCast(me, SPELL_WATERSPOUT);
                return;
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GEYSER:
                    {
                        DoCast(me, SPELL_GEYSER);
                        events.ScheduleEvent(EVENT_GEYSER, urand(14000,17000));
                        break;
                    }
                    case EVENT_FUNGAL_SPORES:
                    {
                        DoCastVictim(SPELL_FUNGAL_SPORES);
                        events.ScheduleEvent(EVENT_FUNGAL_SPORES, urand(14000, 15000));
                        break;
                    }
                    case EVENT_SHOCK_BLAST:
                    {
                        DoCast(me, SPELL_SHOCK_BLAST);
                        events.ScheduleEvent(EVENT_SHOCK_BLAST, 13000);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);

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
        }

        uint32 uiErrupt;
        bool isErrupted;

        void Reset()
        {
            me->DespawnOrUnsummon(13000);

            // DoCastAOE(SPELL_WATERSPOUT_CHARGE, true);
        }

        void KilledUnit(Unit* victim)
        {
            if(IsHeroic() && (victim->GetEntry() == NPC_SUMMONED_WITCH || victim->GetEntry() == NPC_SUMMONED_GUARD))
                _instance->DoCompleteAchievement(ACHIEVEMENT_OLD_FAITHFUL);
        }

        void UpdateAI(uint32 diff)
        {
            if (!isErrupted && uiErrupt <= diff)
            {
                isErrupted = true;
                DoCastAOE(SPELL_GEYSER_EFFECT, true);

            } else uiErrupt -= diff;
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
        npc_waterspoutAI(Creature* creature) : ScriptedAI(creature)
        {
            me->DespawnOrUnsummon(9000);
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

void AddSC_boss_lady_nazjar()
{
    new boss_lady_nazjar();
    new npc_geyser();
    new npc_waterspout();
}
