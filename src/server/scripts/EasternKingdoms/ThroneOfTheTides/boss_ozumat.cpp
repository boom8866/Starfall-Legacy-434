
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

    SPELL_CHARGE_TO_WINDOW          = 83240,

    SPELL_TIDAL_SURGE               = 76133,

    SPELL_PURE_WATER                = 84037,

    // Faceless Sappers
    SPELL_WATER_EXPLOSION           = 83479,
    SPELL_ENTANGLING_GRASP          = 83463,

    // Spawn Spells
    // Phase 1
    SPELL_SUMMON_UNY_BEHEMOTH       = 83440,
    SPELL_SUMMON_MINDELASHER        = 83436,
    SPELL_SUMMON_MURLOCS            = 83416,

    // Phase 2
    SPELL_SUMMON_BLIGHT_BEATS       = 83648,
    SPELL_ENCOUNTER_COMPLETE        = 95673,
};

enum Achievement
{
    SPELL_KILL_OZUMAT   = 95673,
};

enum Gossips
{
    GOSSIP_NEPTULON                 = 15997,
};

enum Timers
{
    TIMER_PHASE_ONE                 = 99000,
    TIMER_PHASE_ONE_SPAWN           = 15000,
    TIMER_PHASE_TWO_SPAWN           = 17000,
};

#define GROUND_Z                      230.38f

enum Events
{
    EVENT_CHECK_IN_COMBAT           = 1,
    EVENT_FIRST_PHASE_SPAWN         = 2,
    EVENT_FIRST_PHASE_YELL_1        = 3,
    EVENT_FIRST_PHASE_YELL_2        = 4,
    EVENT_FIRST_PHASE_IMPACT        = 5,
    EVENT_SECOND_PHASE_START        = 6,
    EVENT_SECOND_PHASE_SPAWN        = 7,
    EVENT_BLIGHT_OF_OZUMAT          = 8,
    EVENT_PURE_WATER                = 9
};

enum EventGroup
{
    EVENTGROUP_PHASE_ALL,
    EVENTGROUP_PHASE_1,
    EVENTGROUP_PHASE_2,
    EVENTGROUP_PHASE_3,
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
    SAY_PHASE_OZUMAT_ATTACK,
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
    {-179.783f, 956.263f, 230.771f, 0.85200f},
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
            SetCombatMovement(false);
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

                    AddEncounterFrame();

                    events.Reset();
                    events.ScheduleEvent(EVENT_CHECK_IN_COMBAT, 1000);
                    events.ScheduleEvent(EVENT_SECOND_PHASE_START, TIMER_PHASE_ONE);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_SPAWN, 7000, EVENTGROUP_PHASE_1);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_YELL_1, TIMER_PHASE_ONE / 3, EVENTGROUP_PHASE_1);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_YELL_2, ((TIMER_PHASE_ONE / 3) *2), EVENTGROUP_PHASE_1);
                    events.ScheduleEvent(EVENT_FIRST_PHASE_IMPACT, urand(17000, 25000), EVENTGROUP_PHASE_1);
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
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (instance->GetBossState(DATA_OZUMAT) != IN_PROGRESS)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_IN_COMBAT:
                    {
                        if (instance->AreAllPlayersDead())
                        {
                            me->InterruptNonMeleeSpells(false);
                            me->RemoveAllAuras();
                            Ozumat::DespawnMinions(me);

                            me->m_Events.KillAllEvents(false);

                            instance->SetBossState(DATA_OZUMAT, NOT_STARTED);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            IsIntroDone = false;

                            if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                                ozumat->AI()->DoAction(INST_ACTION_OZUMAT_RESET_EVENT);
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
                        DoCast(me, RAND(SPELL_SUMMON_UNY_BEHEMOTH, SPELL_SUMMON_MINDELASHER, SPELL_SUMMON_MURLOCS), true);

                        events.ScheduleEvent(EVENT_FIRST_PHASE_SPAWN, TIMER_PHASE_ONE_SPAWN, EVENTGROUP_PHASE_1);
                        break;
                    }
                case EVENT_FIRST_PHASE_IMPACT:
                    {
                        if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                            ozumat->CastSpell(ozumat, SPELL_OZUMAT_GLOBAL_IMPACT, true);

                        events.ScheduleEvent(EVENT_FIRST_PHASE_IMPACT, urand(17000, 25000), EVENTGROUP_PHASE_1);
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
                                // facelessSapper->CastSpell(facelessSapper, SPELL_WATER_EXPLOSION, true);
                                facelessSapper->m_Events.AddEvent(new CastEntanglingGrasp(facelessSapper), facelessSapper->m_Events.CalculateTime(4000));
                                facelessSapper->GetMotionMaster()->MoveJump(FacelessSapperSpawnPositions[i].m_positionX, FacelessSapperSpawnPositions[i].m_positionY, GROUND_Z, 24.f, 24.f);
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
                                if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                                    ozumat->CastSpell(target, SPELL_BLIGHT_OF_OZUMAT);
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

            if (Creature* ozumat = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_OZUMAT)))
                ozumat->AI()->DoAction(INST_ACTION_OZUMAT_RESET_EVENT);
        }
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action == GOSSIP_ACTION_INFO_DEF + 1 && sender == GOSSIP_SENDER_MAIN)
        {
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->AI()->DoAction(INST_ACTION_START_OZUMAT_EVENT);
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

    struct npc_ozumat_add_spawnerAI : public ScriptedAI
    {
        npc_ozumat_add_spawnerAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;

        Player* GetRandomPlayer()
        {
            std::list<Player*> pAliveList;
            Map::PlayerList const &pPlayerList = me->GetMap()->GetPlayers();
            if (!pPlayerList.isEmpty())
                for (Map::PlayerList::const_iterator itr = pPlayerList.begin(); itr != pPlayerList.end(); ++itr)
                    if (itr->getSource()->isAlive())
                        pAliveList.push_back(itr->getSource());

            if (!pAliveList.empty())
            {
                std::list<Player*>::const_iterator itr = pAliveList.begin();
                std::advance(itr, rand() % pAliveList.size());
                return (*itr);
            }
            return NULL;
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
            case NPC_DEEP_MURLOC_INVADER:
            case NPC_UNYIELDING_BEHEMOTH:
            case NPC_VICIOUS_MINDLASHER:
            case NPC_BLIGHT_BEAST:
                {
                    DoCast(SPELL_CHARGE_TO_WINDOW);

                    if (Creature* neptulon = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_NEPTULON)))
                    {
                        summon->SetFacingToObject(neptulon);

                        Position pos = *summon;
                        summon->MovePosition(pos, 0.4f, 0);
                        pos.m_positionZ = GROUND_Z;

                        if (pos.IsPositionValid())
                            summon->GetMotionMaster()->MoveJumpTo(0, 20.f, 20.f);

                        if(summon->GetEntry() != NPC_BLIGHT_BEAST)
                        {
                            summon->AddThreat(neptulon, 10.0f);
                            summon->AI()->AttackStart(neptulon);
                        }
                        else
                            if (Player* pTarget = GetRandomPlayer())
                                summon->AI()->AttackStart(pTarget);
                    }
                    break;
                }
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
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        InstanceScript* instance;

        void DoAction(int32 action)
        {
            me->InterruptNonMeleeSpells(false);

            switch (action)
            {
            case INST_ACTION_OZUMAT_START_PHASE:
                {
                    me->GetMotionMaster()->MovePoint(0, OzumatPosition[1]);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    break;
                }
            case INST_ACTION_OZUMAT_RESET_EVENT:
                {
                    me->RemoveAllAuras();
                    me->GetMotionMaster()->MovePoint(0, OzumatPosition[0]);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_CUSTOM_SPELL_01);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            i->getSource()->RemoveAura(SPELL_TIDAL_SURGE);
                            i->getSource()->RemoveAura(76155);
                        }
                    break;
                }
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
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if(me->GetHealth() <= damage)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                Ozumat::DespawnMinions(me);
                damage = 0;

                me->DespawnOrUnsummon(25000);
                me->GetMotionMaster()->MovePoint(0, OzumatPosition[2]);

                if (Creature* neptulon = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_NEPTULON)))
                    neptulon->DespawnOrUnsummon();

                Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        i->getSource()->RemoveAura(SPELL_TIDAL_SURGE);
                        i->getSource()->RemoveAura(76155);
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
