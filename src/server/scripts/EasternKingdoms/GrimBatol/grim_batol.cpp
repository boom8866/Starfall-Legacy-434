
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "grim_batol.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

enum FlyingDrake
{
    // Twilight Drake
    SPELL_TWILIGHT_BREATH               = 76817,

    EVENT_CHECK_ENEMY_IN_RANGE          = 1,
    EVENT_ATTACK_ENEMY                  = 2,
};

enum BatteredredDrakeEvent
{
    SPELL_NET   = 79377
};

static Position const batteredDrakePositions[4] =
{
    {-423.5f, -688.512f, 304.048f, 0},
    {-596.3f, -701.383f, 302.581f, 0},
    {-455.5f, -354.694f, 290.681f, 0},
    {-378.43f, -607.011f, 302.55f, 0}
};

class npc_gb_flying_drake : public CreatureScript
{
public:
    npc_gb_flying_drake() : CreatureScript("npc_gb_flying_drake") { }

    struct npc_gb_flying_drakeAI : public ScriptedAI
    {
        npc_gb_flying_drakeAI(Creature* creature) : ScriptedAI(creature)
        {
            isInvolvedInFolowEvent = false;
            events.ScheduleEvent(EVENT_CHECK_ENEMY_IN_RANGE, 10000);
        }

        bool isInvolvedInFolowEvent;
        uint64 uiEnemyGUID;

        EventMap events;

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ENEMY_IN_RANGE:
                    {
                        if (!uiEnemyGUID)
                        {
                            if (Creature* enemy = me->FindNearestCreature((me->GetEntry() == NPC_TWILIGHT_DRAKE ? NPC_BATTERED_RED_DRAKE : NPC_TWILIGHT_DRAKE), 4.f))
                            {
                                SetGUID(enemy->GetGUID());
                                enemy->AI()->SetGUID(me->GetGUID());

                                me->GetMotionMaster()->MoveChase(enemy, 2.f);
                            }
                        }
                        events.ScheduleEvent(EVENT_CHECK_ENEMY_IN_RANGE, 2000);
                        break;
                    }
                    case EVENT_ATTACK_ENEMY:
                    {
                        if (uiEnemyGUID)
                        {
                            Creature* enemy = me->GetCreature(*me, uiEnemyGUID);
                            // Enemy is dead or Despawned
                            if (!enemy || enemy->isDead())
                            {
                                uiEnemyGUID = NULL;
                                me->DespawnOrUnsummon(5000);
                                return;
                            }

                            if (me->GetEntry() == NPC_TWILIGHT_DRAKE && roll_chance_i(35))
                                me->CastSpell(enemy, SPELL_TWILIGHT_BREATH);
                            else
                                me->Attack(enemy, true);

                            events.ScheduleEvent(EVENT_CHECK_ENEMY_IN_RANGE, urand(4000, 6000));
                        }
                        break;
                    }
                }
            }
        }

        void SetGUID(uint64 guid, int32 /*id*/ = 0)
        {
            if (!isInvolvedInFolowEvent && !uiEnemyGUID)
            {
                if (Creature* enemy = me->GetCreature(*me, guid))
                {
                    uiEnemyGUID = guid;
                    events.ScheduleEvent(EVENT_ATTACK_ENEMY, 2000);
                    enemy->GetMotionMaster()->MovementExpired();
                }
            }
        }

        void DoAction(int32 action)
        {
            if (action == ACTION_DRAGON_IS_IN_FOLLOWER_EVENT)
            {
                isInvolvedInFolowEvent = true;
                events.Reset();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_flying_drakeAI (creature);
    }
};

class npc_battered_red_drake_event : public CreatureScript
{
public:
    npc_battered_red_drake_event() : CreatureScript("npc_battered_red_drake_event") { }

    enum eventId
    {
        EVENT_ASK_FOR_HELP      = 1,
        EVENT_CHECK_FOR_NET,
        EVENT_WHISPER_PASSENGER,
        EVENT_MOVE_TAKEOFF,
        EVENT_DISABLE_GRAVITY
    };

    enum actionId
    {
        ACTION_FREED    = 1
    };

    enum pointId
    {
        POINT_TAKEOFF   = 50
    };

    struct npc_battered_red_drake_eventAI : public npc_escortAI
    {
        npc_battered_red_drake_eventAI(Creature* creature) : npc_escortAI(creature) {instance = creature->GetInstanceScript();}

        InstanceScript* instance;
        EventMap events;

        void OnCharmed(bool /*apply*/) {}

        void WaypointReached(uint32 /*point*/) {}

        void EnterEvadeMode() {}

        void Reset()
        {
            playerPassenger = NULL;
            me->SetReactState(REACT_PASSIVE);
            DoCast(SPELL_NET);
            me->SetCanFly(true);
            me->SetDisableGravity(false);
            me->SetHover(false);
            events.ScheduleEvent(EVENT_ASK_FOR_HELP, urand(30000, 75000));
            events.ScheduleEvent(EVENT_CHECK_FOR_NET, 2000);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if(apply && who->GetTypeId() == TYPEID_PLAYER)
            {
                playerPassenger = who;
                instance->ProcessEvent(me, ACTION_START_DRAGON_EVENT);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                events.ScheduleEvent(EVENT_WHISPER_PASSENGER, 2000);
                events.ScheduleEvent(EVENT_MOVE_TAKEOFF, 1000);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FREED:
                {
                    Talk(2);
                    events.CancelEvent(EVENT_ASK_FOR_HELP);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ASK_FOR_HELP:
                    {
                        if (me->HasAura(SPELL_NET))
                        {
                            Talk(1);
                            events.RescheduleEvent(EVENT_ASK_FOR_HELP, urand(30000, 75000));
                        }
                        else
                            events.CancelEvent(EVENT_ASK_FOR_HELP);
                        break;
                    }
                    case EVENT_CHECK_FOR_NET:
                    {
                        if (!me->HasAura(SPELL_NET))
                        {
                            DoAction(ACTION_FREED);
                            events.CancelEvent(EVENT_CHECK_FOR_NET);
                        }
                        else
                            events.RescheduleEvent(EVENT_CHECK_FOR_NET, 2000);
                        break;
                    }
                    case EVENT_WHISPER_PASSENGER:
                    {
                        events.CancelEvent(EVENT_WHISPER_PASSENGER);
                        if (playerPassenger && playerPassenger != NULL)
                            me->MonsterWhisper("Welcome, friend. Let's ride through Grim Batol and strike a blow against Deathwing that he won't soon forget!", playerPassenger->GetGUID(), false);

                        Start(false, true, NULL, NULL, false, false, true);
                        break;
                    }
                    case EVENT_MOVE_TAKEOFF:
                    {
                        events.CancelEvent(EVENT_MOVE_TAKEOFF);
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 20.0f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        events.ScheduleEvent(EVENT_DISABLE_GRAVITY, 2000);
                        me->SetDisableGravity(true);
                        break;
                    }
                    case EVENT_DISABLE_GRAVITY:
                    {
                        events.CancelEvent(EVENT_DISABLE_GRAVITY);
                        me->SetSpeed(MOVE_FLIGHT, 2.0f, true);
                        break;
                    }
                    default:
                        break;
                }
            }

            npc_escortAI::UpdateAI(diff);
        }

    protected:
        Unit* playerPassenger;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_battered_red_drake_eventAI (creature);
    }
};

class npc_gb_net : public CreatureScript
{
public:
    npc_gb_net() : CreatureScript("npc_gb_net") { }

    struct npc_gb_netAI : public ScriptedAI
    {
        npc_gb_netAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 uiTargetGUID;

        void IsSummonedBy(Unit* summoner)
        {
            uiTargetGUID = summoner->GetGUID();
        }

        void JustDied(Unit* /*killer*/)
        {
            if(Creature* target = me->GetCreature(*me, uiTargetGUID))
            {
                target->RemoveAurasDueToSpell(SPELL_NET);

                if (target->GetEntry() == NPC_BATTERED_RED_DRAKE_EVENT)
                    target->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);

                me->DespawnOrUnsummon(200);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_netAI (creature);
    }
};

// 74040 Engulfing Flames
class spell_gb_engulfing_flames : public SpellScriptLoader
{
public:
    spell_gb_engulfing_flames() : SpellScriptLoader("spell_gb_engulfing_flames")
    {
    }

    class spell_gb_engulfing_flames_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_engulfing_flames_SpellScript);

        void HandleBlockReset(SpellEffIndex /*effIndex*/)
        {
            if (Unit* victim = GetHitUnit())
            {
                if (victim->ToCreature() && victim->ToCreature()->GetAIName() == "SmartAI")
                {
                    victim->getThreatManager().clearReferences();
                    victim->AttackStop();
                    victim->ClearInCombat();
                    victim->ToCreature()->setRegeneratingHealth(false);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gb_engulfing_flames_SpellScript::HandleBlockReset, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_engulfing_flames_SpellScript();
    }
};

class npc_gb_twilight_wyrmcaller : public CreatureScript
{
public:
    npc_gb_twilight_wyrmcaller() : CreatureScript("npc_gb_twilight_wyrmcaller")
    {
    }

    enum Spells
    {
        SPELL_FEED_PET_H    = 90872,
        SPELL_FEED_PET_N    = 76816
    };

    enum eventId
    {
        EVENT_FEED_PET  = 1
    };

    struct npc_gb_twilight_wyrmcallerAI : public ScriptedAI
    {
        npc_gb_twilight_wyrmcallerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_FEED_PET, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FEED_PET:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TWILIGHT_DRAKE, 25.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                if ((*iter))
                                {
                                    DoCast((*iter), IsHeroic() ? SPELL_FEED_PET_H : SPELL_FEED_PET_N, true);
                                    events.RescheduleEvent(EVENT_FEED_PET, 10000);
                                }
                            }
                        }
                        else
                            events.RescheduleEvent(EVENT_FEED_PET, 3000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_twilight_wyrmcallerAI(creature);
    }
};

class npc_gb_twilight_drake : public CreatureScript
{
public:
    npc_gb_twilight_drake() : CreatureScript("npc_gb_twilight_drake")
    {
    }

    enum Spells
    {
        SPELL_TWILIGHT_FLAMES   = 75931,
        SPELL_TWILIGHT_BREATH   = 90875
    };

    enum eventId
    {
        EVENT_TWILIGHT_FLAMES   = 1,
        EVENT_TWILIGHT_BREATH
    };

    struct npc_gb_twilight_drakeAI : public ScriptedAI
    {
        npc_gb_twilight_drakeAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_TWILIGHT_FLAMES, 4000);
            events.ScheduleEvent(EVENT_TWILIGHT_BREATH, 9000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TWILIGHT_FLAMES:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_TWILIGHT_FLAMES);

                        events.RescheduleEvent(EVENT_TWILIGHT_FLAMES, 9000);
                        break;
                    }
                    case EVENT_TWILIGHT_BREATH:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 200, true))
                            DoCast(target, SPELL_TWILIGHT_BREATH);

                        events.RescheduleEvent(EVENT_TWILIGHT_BREATH, 9000);
                        break;
                    }
                    default:
                        break;
                }
            }

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_twilight_drakeAI(creature);
    }
};

void AddSC_grim_batol()
{
    new npc_gb_flying_drake();
    new npc_battered_red_drake_event();
    new npc_gb_net();
    new spell_gb_engulfing_flames();
    new npc_gb_twilight_wyrmcaller();
    new npc_gb_twilight_drake();
}
