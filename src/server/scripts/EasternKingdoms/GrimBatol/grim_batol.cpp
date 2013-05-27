
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
                        if(!uiEnemyGUID)
                        {
                            if(Creature* enemy = me->FindNearestCreature((me->GetEntry() == NPC_TWILIGHT_DRAKE ? NPC_BATTERED_RED_DRAKE : NPC_TWILIGHT_DRAKE), 4.f))
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
                        if(uiEnemyGUID)
                        {
                            Creature* enemy = me->GetCreature(*me, uiEnemyGUID);

                            // Enemy is dead or Despawned
                            if(!enemy || enemy->isDead())
                            {
                                uiEnemyGUID = NULL;
                                me->DespawnOrUnsummon(5000);
                                return;
                            }

                            if(me->GetEntry() == NPC_TWILIGHT_DRAKE && roll_chance_i(35))
                            {
                                me->CastSpell(enemy, SPELL_TWILIGHT_BREATH);

                            }else
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
            if(!isInvolvedInFolowEvent && !uiEnemyGUID)
                if(Creature* enemy = me->GetCreature(*me, guid))
                {
                    uiEnemyGUID = guid;
                    events.ScheduleEvent(EVENT_ATTACK_ENEMY, 2000);

                    enemy->GetMotionMaster()->MovementExpired();
                }
        }

        void DoAction(int32 action)
        {
            if(action == ACTION_DRAGON_IS_IN_FOLLOWER_EVENT)
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

enum BatteredredDrakeEvent
{
    SAY_HELP,
    SAY_DESTROY,
    SAY_INSTRUCTIONS,

    SPELL_NET                           = 79377,
    SPELL_RIDE_VEHICLE                  = 80343,
    SPELL_BOMBING_RUN_PROTECTION        = 80364,
    SPELL_BOMBING_RUN_PROTECTION_EFFECT = 80366
};

static Position const batteredDrakePositions[4] =
{
    {-423.5f, -688.512f, 304.048f, 0},
    {-596.3f, -701.383f, 302.581f, 0},
    {-455.5f, -354.694f, 290.681f, 0},
    {-378.43f, -607.011f, 302.55f, 0}
};

class npc_battered_red_drake_event : public CreatureScript
{
public:
    npc_battered_red_drake_event() : CreatureScript("npc_battered_red_drake_event") { }

    struct npc_battered_red_drake_eventAI : public npc_escortAI
    {
        npc_battered_red_drake_eventAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 phase;

        void Reset()
        {
            DoCast(SPELL_NET);
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if(apply && who->GetTypeId() == TYPEID_PLAYER)
            {
                who->MonsterSay("ok");
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetHover(true);
                Talk(SAY_DESTROY, who->GetGUID());
                TalkWithDelay(1500, SAY_INSTRUCTIONS, who->GetGUID());
                // me->SetSpeedAll(2.4f, true);
                Start(false, true, who->GetGUID());
                instance->ProcessEvent(me, ACTION_START_DRAGON_EVENT);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            }
        }

        void OnCharmed(bool /*apply*/) {}

        void WaypointReached(uint32 /*point*/) {}
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

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_netAI (creature);
    }

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

                if(target->GetEntry() == NPC_BATTERED_RED_DRAKE_EVENT)
                {
                    target->AI()->Talk(SAY_HELP);
                    target->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                }

                me->DespawnOrUnsummon(200);
            }
        }
    };
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

// 74040 Engulfing Flames
class spell_engulfing_flames : public SpellScriptLoader
{
public:
    spell_engulfing_flames() : SpellScriptLoader("spell_engulfing_flames") { }

    class spell_engulfing_flames_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_engulfing_flames_SpellScript);

        void HandleReset(SpellEffIndex effIndex)
        {
            if (Creature* creature = GetHitCreature())
            {
                creature->CombatStop();
                creature->getHostileRefManager().deleteReferences();

                creature->m_Events.KillAllEvents(false);
                creature->m_Events.AddEvent(new ResetCreature(creature), creature->m_Events.CalculateTime(1000));
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_engulfing_flames_SpellScript::HandleReset, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_engulfing_flames_SpellScript();
    }
};

void AddSC_grim_batol()
{
    new npc_gb_flying_drake();
    new npc_battered_red_drake_event();
    new npc_gb_net();
    new spell_engulfing_flames();
}
