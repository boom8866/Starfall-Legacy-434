
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
            events.ScheduleEvent(EVENT_ASK_FOR_HELP, urand(7500, 18500));
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
                            events.RescheduleEvent(EVENT_ASK_FOR_HELP, urand(15000, 25000));
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

class ResetCreature : public BasicEvent
{
public:
    ResetCreature(Creature* _me) : me(_me) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        me->CombatStop();
        me->getHostileRefManager().deleteReferences();
        return true;
    }

private:
    Creature* me;
};

void AddSC_grim_batol()
{
    new npc_gb_flying_drake();
    new npc_battered_red_drake_event();
    new npc_gb_net();
}
