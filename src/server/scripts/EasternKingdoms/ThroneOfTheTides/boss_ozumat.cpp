
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptedGossip.h"
#include "ScriptPCH.h"
#include "throne_of_the_tides.h"
#include "Group.h"

enum Spells
{
    SPELL_PURIFY                    = 76952,
    SPELL_OZUMAT_RIDE_AURA          = 83119,
    SPELL_BLIGHT_OF_OZUMAT          = 83506, // Triggers 83524
    SPELL_BLIGHT_OF_OZUMAT_UNK2     = 83518, // Script Effect
    SPELL_BLIGHT_OF_OZUMAT_UNK3     = 83585, // Triggers 83518
    SPELL_BLIGHT_OF_OZUMAT_UNK4     = 83606, // Summons 44834 (Blight of Ozumat)
    SPELL_SUMMON_BLIGHT_OF_OZUMAT   = 83524, // Summons blight of Ozumat
    SPELL_BLIGHT_OF_OZUMAT_CHANNEL  = 83672, // Visual Effects
    SPELL_OZUMAT_GLOBAL_IMPACT      = 83120,
    SPELL_JUMP_FROM_WINDOW          = 83240,
    SPELL_JUMP_WATER_VISUAL         = 74048,
    SPELL_TIDAL_SURGE               = 76133,
    SPELL_PURE_WATER                = 84037,

    // Faceless Sappers
    SPELL_WATER_EXPLOSION           = 83479,
    SPELL_ENTANGLING_GRASP          = 83463,

    // Spawn Spells
    // Phase 1
    SPELL_SUMMON_UNY_BEHEMOTH       = 83437,
    SPELL_SUMMON_MINDLASHER         = 83440,
    SPELL_SUMMON_MURLOCS            = 83416,

    // Phase 2
    SPELL_SUMMON_BLIGHT_BEATS       = 83648,
    SPELL_ENCOUNTER_COMPLETE        = 95673
};

enum Achievement
{
    SPELL_KILL_OZUMAT   = 95673
};

enum Gossips
{
    GOSSIP_NEPTULON                 = 15997
};

enum Timers
{
    TIMER_PHASE_ONE                 = 93000,
    TIMER_PHASE_ONE_SPAWN           = 46500,
    TIMER_PHASE_TWO_SPAWN           = 16000
};

enum Events
{
    EVENT_CHECK_IN_COMBAT           = 1,
    EVENT_FIRST_PHASE_SPAWN,
    EVENT_FIRST_PHASE_YELL_1,
    EVENT_FIRST_PHASE_YELL_2,
    EVENT_FIRST_PHASE_IMPACT,
    EVENT_SECOND_PHASE_START,
    EVENT_SECOND_PHASE_SPAWN,
    EVENT_BLIGHT_OF_OZUMAT,
    EVENT_PURE_WATER
};

enum EventGroup
{
    EVENTGROUP_PHASE_ALL,
    EVENTGROUP_PHASE_1,
    EVENTGROUP_PHASE_2,
    EVENTGROUP_PHASE_3
};

enum Yells
{
    SAY_INTRO,
    SAY_PHASE_1,
    SAY_WATCH_OUT,
    SAY_NEAR_COMPLETE_PHASE_1,
    SAY_PHASE_2,
    SAY_NEAR_COMPLETE_PHASE_2,
    SAY_PHASE_3,
    SAY_PHASE_3_INTRO,
    SAY_PHASE_OZUMAT_ATTACK
};

enum npcId
{
    NPC_ENTRY_NEPTULON  = 40792,
    NPC_ENTRY_WINDOW    = 36171
};

// 3 X 1 NPC_FACELESS_SAPPER
Position const FacelessSapperSpawnPositions[3] =
{
    {-166.064f, 1005.38f, 306.000f, 5.39307f},
    {-125.307f, 1004.49f, 306.000f, 3.89208f},
    {-168.227f, 963.314f, 306.000f, 0.48872f}
};

Position const OzumatPosition[3] =
{
    {-154.037f, 960.586f, 314.759f, 1.20000f},
    {-154.037f, 960.586f, 290.759f, 1.20000f},
    {156.8000f, 615.354f, 342.009f, 2.24570f}
};

class CastEntanglingGrasp : public BasicEvent
{
public:
    CastEntanglingGrasp(Unit* _me) : me(_me) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        me->CastSpell(me, SPELL_ENTANGLING_GRASP, true);
        return true;
    }

private:
    Unit* me;
};

class SayDelayEvent : public BasicEvent
{
public:
    SayDelayEvent(Creature* _me, uint32 _textId) : me(_me), textId(_textId) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        me->AI()->Talk(textId);
        return true;
    }

private:
    Creature* me;
    uint32 textId;
};

namespace Ozumat
{
    void DespawnMinions(Creature* me)
    {
        me->DespawnCreaturesInArea(NPC_FACELESS_SAPPER, 250.f);
        me->DespawnCreaturesInArea(NPC_BLIGHT_OF_OZUMAT, 250.f);
        me->DespawnCreaturesInArea(NPC_BLIGHT_BEAST, 250.f);

        me->DespawnCreaturesInArea(NPC_DEEP_MURLOC_INVADER, 250.f);
        me->DespawnCreaturesInArea(NPC_UNYIELDING_BEHEMOTH, 250.f);
        me->DespawnCreaturesInArea(NPC_VICIOUS_MINDLASHER, 250.f);
    }
}

class npc_neptulon : public CreatureScript
{
public:
    npc_neptulon() : CreatureScript("npc_neptulon") { }

    struct npc_neptulonAI : public ScriptedAI
    {
        npc_neptulonAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()), IsIntroDone(false), facelessSappersLeft(3)
        {
            creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        InstanceScript* instance;
        EventMap events;

        bool IsIntroDone;

        uint8 facelessSappersLeft;

        void Reset() {}

        void DoAction(int32 action)
        {
            switch (action)
            {
                case INST_ACTION_START_OZUMAT_EVENT:
                {
                    instance->SetBossState(DATA_OZUMAT, IN_PROGRESS);
                    if (GameObject* ozumatDoor = me->FindNearestGameObject(GO_OZUMAT_DOOR, 150.0f))
                        ozumatDoor->SetGoState(GO_STATE_READY);
                    SetCombatMovement(false);
                    me->SetReactState(REACT_PASSIVE);
                    AddEncounterFrame();
                    events.Reset();
                    events.ScheduleEvent(EVENT_CHECK_IN_COMBAT, 1000);
                    events.ScheduleEvent(EVENT_SECOND_PHASE_START, TIMER_PHASE_ONE);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_SPAWN, 30000, EVENTGROUP_PHASE_1);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_YELL_1, TIMER_PHASE_ONE / 3, EVENTGROUP_PHASE_1);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_YELL_2, ((TIMER_PHASE_ONE / 3) * 2), EVENTGROUP_PHASE_1);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_IMPACT, urand(17000, 25000), EVENTGROUP_PHASE_1);
                    DoCast(me, SPELL_SUMMON_MURLOCS, true);

                    // After 5 seconds summon Mindlashers
                    me->CastWithDelay(5000, me, SPELL_SUMMON_MINDLASHER, true);
                    me->CastWithDelay(6000, me, SPELL_SUMMON_MINDLASHER, true);

                    // After 15 seconds summon Behemoth
                    me->CastWithDelay(15000, me, SPELL_SUMMON_UNY_BEHEMOTH, true);

                    Talk(SAY_PHASE_1);
                    DoCast(SPELL_PURIFY);
                    break;
                }
                case INST_ACTION_NEPTULON_DO_INTRO:
                {
                    if (!IsIntroDone)
                    {
                        IsIntroDone = true;
                        Talk(SAY_INTRO);
                    }
                    break;
                }
                case INST_ACTION_NEPTULON_COMPLETED:
                {
                    RemoveEncounterFrame();
                    if (GameObject* ozumatDoor = me->FindNearestGameObject(GO_OZUMAT_DOOR, 150.0f))
                        ozumatDoor->SetGoState(GO_STATE_ACTIVE);
                    me->ClearInCombat();
                    me->DespawnOrUnsummon(2000);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (instance->GetBossState(DATA_OZUMAT) != IN_PROGRESS)
                return;

            if (instance->GetBossState(DATA_OZUMAT) == DONE)
                RemoveEncounterFrame();

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_IN_COMBAT:
                    {
                        if (instance->AreAllPlayersDead())
                        {
                            me->ClearInCombat();
                            RemoveEncounterFrame();
                            if (me->GetHealth() < me->GetMaxHealth())
                                me->SetHealth(me->GetMaxHealth());
                            me->InterruptNonMeleeSpells(false);
                            me->RemoveAllAuras();
                            Ozumat::DespawnMinions(me);
                            me->m_Events.KillAllEvents(false);
                            instance->SetBossState(DATA_OZUMAT, NOT_STARTED);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            IsIntroDone = false;

                            if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                                ozumat->AI()->DoAction(INST_ACTION_OZUMAT_RESET_EVENT);
                            if (GameObject* ozumatDoor = me->FindNearestGameObject(GO_OZUMAT_DOOR, 150.0f))
                                ozumatDoor->SetGoState(GO_STATE_ACTIVE);
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_IN_COMBAT, 1000);
                        break;
                    }
                    case EVENT_FIRST_PHASE_YELL_1:
                    {
                        Talk(SAY_WATCH_OUT);
                        events.RescheduleEvent(EVENT_FIRST_PHASE_IMPACT, 500, EVENTGROUP_PHASE_1);
                        break;
                    }
                    case EVENT_FIRST_PHASE_YELL_2:
                    {
                        Talk(SAY_NEAR_COMPLETE_PHASE_1);
                        events.RescheduleEvent(EVENT_FIRST_PHASE_IMPACT, 500, EVENTGROUP_PHASE_1);
                        break;
                    }
                    case EVENT_FIRST_PHASE_SPAWN:
                    {
                        events.CancelEvent(EVENT_FIRST_PHASE_SPAWN);
                        DoCast(me, SPELL_SUMMON_MURLOCS, true);
                        DoCast(me, SPELL_SUMMON_MINDLASHER, true);
                        break;
                    }
                    case EVENT_FIRST_PHASE_IMPACT:
                    {
                        if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                            ozumat->CastSpell(ozumat, SPELL_OZUMAT_GLOBAL_IMPACT, true);
                        events.RescheduleEvent(EVENT_FIRST_PHASE_IMPACT, urand(17000, 25000), EVENTGROUP_PHASE_1);
                        break;
                    }
                    case EVENT_SECOND_PHASE_START:
                    {
                        me->RemoveAllAuras();
                        Talk(SAY_PHASE_2);
                        events.CancelEventGroup(EVENTGROUP_PHASE_1);
                        facelessSappersLeft = 3;
                        events.ScheduleEvent(EVENT_SECOND_PHASE_SPAWN, 10000, EVENTGROUP_PHASE_2);
                        events.ScheduleEvent(EVENT_BLIGHT_OF_OZUMAT, 7000, EVENTGROUP_PHASE_2);

                        for (uint8 i = 0; i < 3; ++i)
                        {
                            if (Creature* facelessSapper = me->SummonCreature(NPC_FACELESS_SAPPER, FacelessSapperSpawnPositions[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, urand(3000, 10000)))
                            {
                                facelessSapper->SetReactState(REACT_PASSIVE);
                                facelessSapper->m_Events.AddEvent(new CastEntanglingGrasp(facelessSapper), facelessSapper->m_Events.CalculateTime(4000));
                                facelessSapper->GetMotionMaster()->MoveJump(FacelessSapperSpawnPositions[i].m_positionX, FacelessSapperSpawnPositions[i].m_positionY, 230.38f, 24.f, 24.f);
                            }
                        }

                        if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                            ozumat->CastSpell(ozumat, SPELL_BLIGHT_OF_OZUMAT_CHANNEL, true);

                        me->m_Events.AddEvent(new SayDelayEvent(me, SAY_NEAR_COMPLETE_PHASE_2), me->m_Events.CalculateTime(15000));
                        break;
                    }
                    case EVENT_SECOND_PHASE_SPAWN:
                    {
                        DoCast(me, SPELL_SUMMON_BLIGHT_BEATS);
                        events.ScheduleEvent(EVENT_SECOND_PHASE_SPAWN, TIMER_PHASE_TWO_SPAWN, EVENTGROUP_PHASE_2);
                        break;
                    }
                    case EVENT_BLIGHT_OF_OZUMAT:
                    {
                        std::list<Player*> playerList = me->GetNearestPlayersList(200.f, true);
                        if (!playerList.empty())
                        {
                            if (Player* target = SelectRandomContainerElement(playerList))
                            {
                                if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                                    ozumat->CastSpell(target, SPELL_BLIGHT_OF_OZUMAT, true);
                            }
                        }
                        events.ScheduleEvent(EVENT_BLIGHT_OF_OZUMAT, 15000, EVENTGROUP_PHASE_2);
                        break;
                    }
                    case EVENT_PURE_WATER:
                    {
                        DoCast(SPELL_PURE_WATER);
                        events.ScheduleEvent(EVENT_PURE_WATER, urand(7000, 10000), EVENTGROUP_PHASE_3);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            if (summon->GetEntry() == NPC_FACELESS_SAPPER)
            {
                if(facelessSappersLeft && --facelessSappersLeft <= 0)
                {
                    me->DespawnCreaturesInArea(NPC_BLIGHT_OF_OZUMAT, 250.f);

                    me->InterruptNonMeleeSpells(false);
                    me->RemoveAllAuras();

                    events.CancelEventGroup(EVENTGROUP_PHASE_2);
                    Talk(SAY_PHASE_3);

                    me->m_Events.AddEvent(new SayDelayEvent(me, SAY_PHASE_3_INTRO), me->m_Events.CalculateTime(5000));
                    me->m_Events.AddEvent(new SayDelayEvent(me, SAY_PHASE_OZUMAT_ATTACK), me->m_Events.CalculateTime(10000));

                    events.ScheduleEvent(EVENT_PURE_WATER, 17000, EVENTGROUP_PHASE_3);

                    instance->DoCastSpellOnPlayers(SPELL_TIDAL_SURGE);

                    if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                        ozumat->AI()->DoAction(INST_ACTION_OZUMAT_START_PHASE);
                }
            }
        }

        void JustDied(Unit* /*Killer*/)
        {
            Ozumat::DespawnMinions(me);
            me->m_Events.KillAllEvents(false);
            instance->SetBossState(DATA_OZUMAT, NOT_STARTED);
            RemoveEncounterFrame();
            me->Respawn(true);

            if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                ozumat->AI()->DoAction(INST_ACTION_OZUMAT_RESET_EVENT);
            if (GameObject* ozumatDoor = me->FindNearestGameObject(GO_OZUMAT_DOOR, 150.0f))
                ozumatDoor->SetGoState(GO_STATE_ACTIVE);
        }
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action == GOSSIP_ACTION_INFO_DEF + 1 && sender == GOSSIP_SENDER_MAIN)
        {
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->AI()->DoAction(INST_ACTION_START_OZUMAT_EVENT);
            creature->SetInCombatWithZone();
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We are ready!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->SEND_GOSSIP_MENU(GOSSIP_NEPTULON, creature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature *creature) const
    {
        return new npc_neptulonAI (creature);
    }
};

class npc_ozumat_add_spawner : public CreatureScript
{
public:
    npc_ozumat_add_spawner() : CreatureScript("npc_ozumat_add_spawner") { }

    enum pointId
    {
        POINT_WINDOW    = 1,
        POINT_GROUND
    };

    struct npc_ozumat_add_spawnerAI : public ScriptedAI
    {
        npc_ozumat_add_spawnerAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_DEEP_MURLOC_INVADER:
                case NPC_UNYIELDING_BEHEMOTH:
                case NPC_VICIOUS_MINDLASHER:
                case NPC_BLIGHT_BEAST:
                {
                    class enableToCombat : public BasicEvent
                    {
                    public:
                        explicit enableToCombat(Creature* creature) : creature(creature) {}

                        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
                        {
                            creature->GetMotionMaster()->MovementExpired(false);
                            creature->GetMotionMaster()->MoveJump(creature->GetPositionX(), creature->GetPositionY(), 231.0f, 36.5f, 36.5f, POINT_GROUND);
                            creature->CastSpell(creature, SPELL_JUMP_FROM_WINDOW);
                            creature->SetReactState(REACT_AGGRESSIVE);
                            return true;
                        }

                    private:
                        Creature* creature;
                    };

                    class removeSwimMovement : public BasicEvent
                    {
                    public:
                        explicit removeSwimMovement(Creature* creature) : creature(creature) {}

                        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
                        {
                            creature->SetCanFly(false);
                            creature->RemoveAurasDueToSpell(SPELL_JUMP_WATER_VISUAL);
                            creature->SetSpeed(MOVE_RUN, creature->GetCreatureTemplate()->speed_run, true);

                            if (creature->GetEntry() == NPC_BLIGHT_BEAST)
                            {
                                std::list<Player*> targets;
                                Trinity::AnyPlayerInObjectRangeCheck u_check(creature, 250.0f);
                                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(creature, targets, u_check);
                                creature->VisitNearbyObject(250.0f, searcher);
                                for (std::list<Player*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                {
                                    if ((*itr) && (*itr)->isAlive())
                                    {
                                        creature->GetMotionMaster()->MoveJump((*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), 20.0f, 20.0f, 0);
                                        creature->AI()->AttackStart((*itr));
                                    }
                                }
                                return true;
                            }

                            if (Creature* neptulon = creature->FindNearestCreature(NPC_ENTRY_NEPTULON, 500.0f, true))
                            {
                                creature->AddThreat(neptulon, 10.0f);
                                creature->AI()->AttackStart(neptulon);
                            }
                            return true;
                        }

                    private:
                        Creature* creature;
                    };

                    if (Creature* neptulon = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_NEPTULON)))
                    {
                        summon->SetFacingToObject(neptulon);
                        summon->SetSpeed(MOVE_RUN, 1.14286f, true);
                        summon->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                        summon->SetCanFly(true);
                        summon->CastSpell(summon, SPELL_JUMP_WATER_VISUAL, true);
                        if (Creature* window = summon->FindNearestCreature(NPC_ENTRY_WINDOW, 500.0f, true))
                            summon->GetMotionMaster()->MoveCharge(window->GetPositionX(), window->GetPositionY(), window->GetPositionZ(), 25.5f, POINT_WINDOW, false);
                        summon->m_Events.AddEvent(new enableToCombat(summon), (summon)->m_Events.CalculateTime(3000));
                        summon->m_Events.AddEvent(new removeSwimMovement(summon), (summon)->m_Events.CalculateTime(6000));
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ozumat_add_spawnerAI (creature);
    }
};

class boss_ozumat : public CreatureScript
{
public:
    boss_ozumat() : CreatureScript("boss_ozumat") { }

    struct boss_ozumatAI : public ScriptedAI
    {
        boss_ozumatAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
            creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_CUSTOM_SPELL_01);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            creature->SetHealth(creature->GetMaxHealth());
            SetCombatMovement(false);
        }

        InstanceScript* instance;

        void Reset()
        {
        }

        void EnterEvadeMode()
        {
        }

        void DoAction(int32 action)
        {
            me->InterruptNonMeleeSpells(false);

            switch (action)
            {
                case INST_ACTION_OZUMAT_START_PHASE:
                {
                    me->GetMotionMaster()->MovePoint(1, OzumatPosition[1]);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    if (Creature* neptulon = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_NEPTULON)))
                        me->SetFacingToObject(neptulon);
                    me->SetFloatValue(UNIT_FIELD_COMBATREACH, 100);
                    break;
                }
                case INST_ACTION_OZUMAT_RESET_EVENT:
                {
                    me->RemoveAllAuras();
                    me->GetMotionMaster()->MovePoint(0, OzumatPosition[0]);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_CUSTOM_SPELL_01);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetHealth(me->GetMaxHealth());

                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            i->getSource()->RemoveAura(SPELL_TIDAL_SURGE);
                            i->getSource()->RemoveAura(76155);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void CompleteEncounter()
        {
            if (instance)
            {
                // Achievement
                instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_KILL_OZUMAT, 0, me);
                instance->UpdateEncounterState(ENCOUNTER_CREDIT_CAST_SPELL, SPELL_ENCOUNTER_COMPLETE, me); 
                instance->SetBossState(DATA_OZUMAT, DONE);
                _FinishDungeon();
                if (me->GetMap()->IsHeroic())
                {
                    if (GameObject* neptulonCacheHc = me->FindNearestGameObject(GO_NEPTULONS_CACHE_HC, 1000.0f))
                        neptulonCacheHc->SetPhaseMask(1, true);
                }
                else
                {
                    if (GameObject* neptulonCacheNh = me->FindNearestGameObject(GO_NEPTULONS_CACHE_NH, 1000.0f))
                        neptulonCacheNh->SetPhaseMask(1, true);
                }
                me->CombatStop(true);
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (me->GetHealth() <= damage)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                Ozumat::DespawnMinions(me);
                damage = 0;

                me->DespawnOrUnsummon(25000);
                me->GetMotionMaster()->MovePoint(0, OzumatPosition[2]);

                // Cleanup frame and combat
                if (Creature* neptulon = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_NEPTULON)))
                    neptulon->AI()->DoAction(INST_ACTION_NEPTULON_COMPLETED);

                Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                if (!PlayerList.isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        i->getSource()->RemoveAura(SPELL_TIDAL_SURGE);
                        i->getSource()->RemoveAura(76155);
                    }
                }
                CompleteEncounter();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ozumatAI (creature);
    }
};

void AddSC_boss_ozumat()
{
    new npc_neptulon();
    new npc_ozumat_add_spawner();
    new boss_ozumat();
}
