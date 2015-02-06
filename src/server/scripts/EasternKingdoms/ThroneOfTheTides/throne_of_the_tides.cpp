
/*
* Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
*
* THIS particular file is NOT free software.
* You are not allowed to share or redistribute it.
*/

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"
#include "ScriptedEscortAI.h"

enum Creatures
{
    // Nazjar Pre Event
    NPC_NAZJAR_INVADER_UPPER        = 40584,
    NPC_NAZJAR_SPIRITMENDER_UPPER   = 41139,
    NPC_DEEP_MURLOC_DRUDGE          = 39960,

    // Throne of the Tides first spawnwave
    NPC_NAZJAR_INVADER_LOWER        = 39616,
    NPC_NAZJAR_SPIRITMENDER_LOWER   = 41096
};

enum Spells
{
    SPELL_MURLOC_LASH_VISUAL_LEFT   = 74568,
    SPELL_MURLOC_LASH_VISUAL_RIGHT  = 74563
};

enum Side
{
    SIDE_LEFT,
    SIDE_RIGHT,
    MAX_SIDES
};

static uint32 const SpellMurlocLashVisual[MAX_SIDES] = {SPELL_MURLOC_LASH_VISUAL_LEFT, SPELL_MURLOC_LASH_VISUAL_RIGHT};

struct EventSpawn
{
    uint32 entry;
    Position startPosition;
    Position endPosition;
};

static EventSpawn const eventSpawn[4] =
{
    {NPC_NAZJAR_INVADER_LOWER,      {-413.618195f, 826.857910f, 257.100616f, 4.7465f}, {-413.500f, 798.380f, 248.561f, 3.10669f} }, // Left Side
    {NPC_NAZJAR_SPIRITMENDER_LOWER, {-413.618195f, 826.857910f, 257.100616f, 4.7465f}, {-410.087f, 807.931f, 248.335f, 3.10669f} },
    {NPC_NAZJAR_SPIRITMENDER_LOWER, {-406.42627f, 783.56427f, 256.139618f, 1.899435f}, {-409.130f, 802.774f, 248.357f, 3.10669f} }, // Right Side
    {NPC_NAZJAR_INVADER_LOWER,      {-406.42627f, 783.56427f, 256.139618f, 1.899435f}, {-414.969f, 810.604f, 248.433f, 3.10669f} }
};

class MoveHomePos : public BasicEvent
{
public:
    MoveHomePos(Unit* _me) : me(_me) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        me->ToCreature()->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
        me->GetMotionMaster()->MoveTargetedHome();
        me->RemoveAurasDueToSpell(SPELL_WATER_WINDOW_JUMP_VISUAL);
        me->SetCanFly(false);
        me->RemoveUnitMovementFlag(276824832);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1|UNIT_FLAG_IMMUNE_TO_PC);
        return true;
    }

private:
    Unit* me;
};

// 5806
class at_tott_lower_spawn_event : public AreaTriggerScript
{
public:
    at_tott_lower_spawn_event() : AreaTriggerScript("at_tott_lower_spawn_event") {}

    bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/)
    {
        if (Map* map = player->GetMap())
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                if (!instance->GetData(DATA_EVENT_DONE_LOWER_SPAWN) && !player->isGameMaster())
                {
                    instance->SetData(DATA_EVENT_DONE_LOWER_SPAWN, 1);

                    for (uint8 i = 0; i < 4; ++i)
                    {
                        if (Creature* creature = map->SummonCreature(eventSpawn[i].entry, eventSpawn[i].startPosition))
                        {
                            creature->CastWithDelay(750, creature, SPELL_WATER_WINDOW_JUMP_VISUAL, true);
                            creature->CastWithDelay(950, creature, SPELL_WATER_WINDOW_JUMP_VISUAL, true);
                            creature->CastWithDelay(1250, creature, SPELL_WATER_WINDOW_JUMP_VISUAL, true);
                            creature->GetMotionMaster()->MovementExpired(false);
                            creature->GetMotionMaster()->MoveJump(eventSpawn[i].endPosition.m_positionX, eventSpawn[i].endPosition.m_positionY, eventSpawn[i].endPosition.m_positionZ, 10.0f, 10.0f);
                            creature->SetOrientation(eventSpawn[i].endPosition.m_orientation);

                            creature->SetHomePosition(eventSpawn[i].endPosition);
                            creature->m_Events.AddEvent(new MoveHomePos(creature), creature->m_Events.CalculateTime(2000));
                        }
                    }
                }
            }

            return true;
        }
        return false;
    }
};

// 6018L 6017R
class at_tott_tentacle_knockback : public AreaTriggerScript
{
public:
    at_tott_tentacle_knockback() : AreaTriggerScript("at_tott_tentacle_knockback") {}

    enum npcId
    {
        NPC_ENTRY_COMMANDER_ULTHOK  = 40765
    };

    bool OnTrigger(Player* player, const AreaTriggerEntry* at)
    {
        if (InstanceScript* instance = player->GetInstanceScript())
        {
            if (Creature* commanderUlthok = player->FindNearestCreature(NPC_ENTRY_COMMANDER_ULTHOK, 1000.0f, true))
            {
                if (Creature* trigger = player->FindNearestCreature(NPC_WORLD_TRIGGER, 20.f))
                    trigger->CastSpell(player, SPELL_TENTACLE_KNOCKBACK, true);
            }
        }
        return true;
    }
};

static Position const MurlocSpawnPositions[2][5] =
{
    {
        {-32.3524f, 798.160f, 801.728f, 3.12414f}, // Left Side
        {-25.8385f, 796.271f, 805.673f, 3.12414f},
        {-30.2969f, 794.894f, 803.246f, 3.10669f},
        {-25.7517f, 799.009f, 805.759f, 3.14159f},
        {-29.2049f, 799.585f, 803.636f, 3.14159f}
    },
    {
        {-31.1250f, 807.922f, 802.365f, 3.17650f}, // Right Side
        {-29.5174f, 810.255f, 803.281f, 3.19395f},
        {-34.0556f, 810.477f, 801.454f, 3.19395f},
        {-25.7917f, 809.467f, 805.148f, 3.17650f},
        {-27.9514f, 805.736f, 804.056f, 3.15905f}
    }
};


static Position const NazjarMinionJumpPos[6] =
{
    {-132.085f, 798.554f, 796.976f, 3.1555f}, // Invader Spawnpoints
    {-132.030f, 806.990f, 797.000f, 3.0600f},
    {-103.577f, 806.394f, 796.965f, 3.0605f},
    {-72.4102f, 798.265f, 796.970f, 3.1273f}, // Spiritmender Spawnpoints
    {-72.2161f, 806.563f, 796.966f, 3.0958f},
    {-104.031f, 798.420f, 796.957f, 3.1422f}
};

enum Events
{
    EVENT_RELEASE_WAVE      = 1,
    EVENT_SPAWN_WAVE,
    EVENT_CHECK_PROGRESS,
    EVENT_RECHANNEL
};

enum Action
{
    ACTION_START_EVENT = 1
};

enum Yells
{
    SAY_INTRO = 0,
    SAY_OUTRO
};

class npc_lady_nazjar_event : public CreatureScript
{
public:
    npc_lady_nazjar_event() : CreatureScript("npc_lady_nazjar_event") { }

    struct npc_lady_nazjar_eventAI : public npc_escortAI
    {
        npc_lady_nazjar_eventAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;
        EventMap events;

        Side currentSide;
        uint8 minionsLeft;

        bool isEventActive;

        std::map<Side, std::vector<uint64> > uiSides;
        std::vector<uint64> uiHelpers;

        void Reset()
        {
            if (!instance->GetData(DATA_EVENT_DONE_NAZJAR_PRE))
            {
                if (GameObject* door = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_COMMANDER_ULTHOK_DOOR)))
                    door->SetGoState(GO_STATE_READY);

                isEventActive = false;
                events.Reset();
                events.ScheduleEvent(EVENT_RECHANNEL, 50000);
                currentSide = SIDE_LEFT;
                me->DespawnCreaturesInArea(NPC_DEEP_MURLOC_DRUDGE, 500.f);
                uiSides.clear();
                SpawnSide(SIDE_LEFT);
                SpawnSide(SIDE_RIGHT);
                uiHelpers.clear();
                minionsLeft = 6;
            }
            else
            {
                if (GameObject* door = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_COMMANDER_ULTHOK_DOOR)))
                    door->SetGoState(GO_STATE_ACTIVE);
                me->DespawnOrUnsummon();
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_EVENT:
                {
                    if (isEventActive || instance->GetData(DATA_EVENT_DONE_NAZJAR_PRE))
                        return;

                    events.CancelEvent(EVENT_RECHANNEL);
                    isEventActive = true;
                    Talk(SAY_INTRO);
                    IntializeHelpers();
                    events.ScheduleEvent(EVENT_RELEASE_WAVE, 7000);
                    events.ScheduleEvent(EVENT_CHECK_PROGRESS, 2000);
                    break;
                }
            }
        }

        void UpdateEscortAI(uint32 const diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RELEASE_WAVE:
                    {
                        ReleaseSide(currentSide);
                        currentSide = (currentSide == SIDE_LEFT ? SIDE_RIGHT : SIDE_LEFT);
                        events.ScheduleEvent(EVENT_RELEASE_WAVE, 25000);
                        events.ScheduleEvent(EVENT_SPAWN_WAVE, 10000);
                        break;
                    }
                    case EVENT_SPAWN_WAVE:
                    {
                        Side const side = currentSide == SIDE_LEFT ? SIDE_RIGHT : SIDE_LEFT;
                        if (uiSides[side].empty())
                            SpawnSide(side);
                        break;
                    }
                    case EVENT_CHECK_PROGRESS:
                    {
                        if (CheckEventDone())
                        {
                            events.Reset();
                            me->DespawnCreaturesInArea(NPC_DEEP_MURLOC_DRUDGE, 300.f);

                            instance->SetData(DATA_EVENT_DONE_NAZJAR_PRE, 1);
                            instance->SaveToDB();

                            isEventActive = false;
                            uiSides.clear();
                            uiHelpers.clear();

                            if (GameObject* door = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_COMMANDER_ULTHOK_DOOR)))
                                door->SetGoState(GO_STATE_ACTIVE);

                            Talk(SAY_OUTRO);
                            Start(false, true);
                        }
                        else if (instance->AreAllPlayersDead())
                            Reset();
                        else
                            events.ScheduleEvent(EVENT_CHECK_PROGRESS, 2000);
                        break;
                    }
                    case EVENT_RECHANNEL:
                    {
                        for (uint32 side = 0; side < MAX_SIDES; ++side)
                        {
                            for (std::vector<uint64>::const_iterator itr = uiSides[Side(side)].begin(); itr != uiSides[Side(side)].end(); ++itr)
                            {
                                if (Creature* murloc = me->GetCreature(*me, *itr))
                                    murloc->CastSpell(murloc, SpellMurlocLashVisual[side], true);
                            }
                        }
                        events.ScheduleEvent(EVENT_RECHANNEL, 50000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void WaypointReached(uint32 pointId)
        {
            if (pointId == 8)
                me->DespawnOrUnsummon();
        }

    private:
        bool CheckEventDone()
        {
            for (std::vector<uint64>::const_iterator itr = uiHelpers.begin(); itr != uiHelpers.end(); ++itr)
            {
                if (Creature* minion = me->GetCreature(*me, *itr))
                {
                    if (minion->isAlive())
                        return false;
                }
            }
            return true;
        }

        void SpawnSide(Side side)
        {
            for (uint8 i = 0; i < 5; ++i)
            {
                if (Creature* murloc = me->SummonCreature(NPC_DEEP_MURLOC_DRUDGE, MurlocSpawnPositions[side][i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, urand(3000, 5000)))
                {
                    uiSides[side].push_back(murloc->GetGUID());
                    murloc->SetReactState(REACT_PASSIVE);
                    murloc->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    murloc->CastSpell(murloc, SpellMurlocLashVisual[side], true);
                }
            }
        }

        void ReleaseSide(Side side)
        {
            if (Player* player = me->FindNearestPlayer(200.f))
            {
                for (std::vector<uint64>::const_iterator itr = uiSides[side].begin(); itr != uiSides[side].end(); ++itr)
                {
                    if (Creature* murloc = me->GetCreature(*me, *itr))
                    {
                        murloc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        murloc->SetReactState(REACT_AGGRESSIVE);
                        murloc->InterruptNonMeleeSpells(false);
                        murloc->RemoveAllAuras();
                        murloc->GetMotionMaster()->MoveChase(player);
                        murloc->SetInCombatWithZone();
                    }
                }
                uiSides[side].clear();
            }
        }

        void IntializeHelpers()
        {
            uiHelpers.clear();

            for (uint8 i = 0; i < 2; ++i)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, i == 0 ? NPC_NAZJAR_INVADER_UPPER : NPC_NAZJAR_SPIRITMENDER_UPPER, 250.0f);
                for (std::list<Creature*>::const_iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                {
                    uiHelpers.push_back((*itr)->GetGUID());
                    Position position = *me;
                    for (uint8 pos = 0; pos < 6; ++pos)
                    {
                        if ((*itr)->GetDistance(NazjarMinionJumpPos[pos]) < (*itr)->GetDistance(position))
                            position = NazjarMinionJumpPos[pos];
                    }

                    (*itr)->CastSpell((*itr), SPELL_WATER_WINDOW_JUMP_VISUAL, true);
                    (*itr)->CastWithDelay(1000, (*itr), SPELL_WATER_WINDOW_JUMP_VISUAL, true);
                    (*itr)->CastWithDelay(2000, (*itr), SPELL_WATER_WINDOW_JUMP_VISUAL, true);
                    (*itr)->GetMotionMaster()->MoveJump(position.m_positionX, position.m_positionY, position.m_positionZ, 14.5f, 14.5f);
                    (*itr)->m_Events.AddEvent(new MoveHomePos(*itr), (*itr)->m_Events.CalculateTime(3000));
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lady_nazjar_eventAI (creature);
    }
};

// 5834
class at_tott_nazjar_event_informer : public AreaTriggerScript
{
public:
    at_tott_nazjar_event_informer() : AreaTriggerScript("at_tott_nazjar_event_informer") {}

    bool OnTrigger(Player* player, const AreaTriggerEntry* at)
    {
        if (!player->isGameMaster())
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                if (Creature* nazjar = player->GetCreature(*player, instance->GetData64(NPC_NAZJAR_EVENT_DOUBLE)))
                    nazjar->AI()->DoAction(ACTION_START_EVENT);
            }
        }
        return true;
    }
};

enum Cinematics
{
    CINEMATIC_SHOCK_DEFENSE = 169
};

class go_tott_defense_system : public GameObjectScript
{
public:
    go_tott_defense_system() : GameObjectScript("go_tott_defense_system") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
        if (InstanceScript* instance = go->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_LADY_NAZJAR))
            {
                if (!instance->GetData(DATA_EVENT_DONE_SHOCK_DEFENSE))
                {
                    Map::PlayerList const &PlayerList = go->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        i->getSource()->SendCinematicStart(CINEMATIC_SHOCK_DEFENSE);

                    instance->ProcessEvent(go, 0);
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE | GO_FLAG_IN_USE);
                    if (GameObject* ladyDoor = go->FindNearestGameObject(GO_LADY_NAZJAR_DOOR, 150.0f))
                        ladyDoor->SetGoState(GO_STATE_ACTIVE);
                    return false;
                }
            }
        }
        return false;
    }
};

// 5873
class at_tott_ulthok_event_informer : public AreaTriggerScript
{
public:
    at_tott_ulthok_event_informer() : AreaTriggerScript("at_tott_ulthok_event_informer") {}

    bool OnTrigger(Player* player, const AreaTriggerEntry* at)
    {
        if (!player->isGameMaster())
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                if (instance->GetBossState(DATA_COMMANDER_ULTHOK) == NOT_STARTED)
                {
                    if (instance->GetBossState(DATA_LADY_NAZJAR) == DONE)
                    {
                        if (Creature* ulthok = ObjectAccessor::GetCreature(*player, instance->GetData64(BOSS_COMMANDER_ULTHOK)))
                            ulthok->AI()->DoAction(INST_ACTION_START_ULTHOK_EVENT);
                    }
                }
            }
        }
        return true;
    }
};

// 6646
class at_tott_neptulon_intro : public AreaTriggerScript
{
public:
    at_tott_neptulon_intro() : AreaTriggerScript("at_tott_neptulon_intro") {}

    bool OnTrigger(Player* player, const AreaTriggerEntry* at)
    {
        if (!player->isGameMaster())
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                if (instance->GetBossState(DATA_OZUMAT) == NOT_STARTED)
                {
                    if (Creature* neptulon = ObjectAccessor::GetCreature(*player, instance->GetData64(NPC_NEPTULON)))
                        neptulon->AI()->DoAction(INST_ACTION_NEPTULON_DO_INTRO);
                }
            }
        }
        return true;
    }
};

class npc_tott_faceless_sapper : public CreatureScript
{
public:
    npc_tott_faceless_sapper() : CreatureScript("npc_tott_faceless_sapper")
    {
    }

    struct npc_tott_faceless_sapperAI : public ScriptedAI
    {
        npc_tott_faceless_sapperAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_ENTANGLING_GRASP  = 83463
        };

        enum eventId
        {
            EVENT_ENTANGLING_GRASP = 1
        };

        void IsSummonedBy(Unit* /*who*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            events.ScheduleEvent(EVENT_ENTANGLING_GRASP, 1500);
        }

        void EnterEvadeMode()
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENTANGLING_GRASP:
                    {
                        if (me->HasUnitState(UNIT_STATE_MOVING))
                        {
                            events.RescheduleEvent(EVENT_ENTANGLING_GRASP, 1000);
                            break;
                        }
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                        me->Relocate(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                        DoCast(SPELL_ENTANGLING_GRASP);
                        events.CancelEvent(EVENT_ENTANGLING_GRASP);
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
        return new npc_tott_faceless_sapperAI(creature);
    }
};

class npc_tott_blight_beast : public CreatureScript
{
public:
    npc_tott_blight_beast() : CreatureScript("npc_tott_blight_beast")
    {
    }

    struct npc_tott_blight_beastAI : public ScriptedAI
    {
        npc_tott_blight_beastAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_AURA_OF_DREAD     = 83971
        };

        enum eventId
        {
            EVENT_SEARCH_PLAYER     = 1,
            EVENT_CAST_AURA
        };

        void IsSummonedBy(Unit* /*who*/)
        {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            events.ScheduleEvent(EVENT_SEARCH_PLAYER, 1500);
            events.ScheduleEvent(EVENT_CAST_AURA, 3000);
        }

        void EnterEvadeMode()
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_PLAYER:
                    {
                        if (me->getVictim())
                        {
                            if (Player* player = me->FindNearestPlayer(250.0f, true))
                            {
                                me->Attack(player, true);
                                events.RescheduleEvent(EVENT_SEARCH_PLAYER, 2000);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_SEARCH_PLAYER, 1000);
                        break;
                    }
                    case EVENT_CAST_AURA:
                    {
                        me->AddAura(SPELL_AURA_OF_DREAD, me);
                        events.RescheduleEvent(EVENT_CAST_AURA, 15000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tott_blight_beastAI(creature);
    }
};

void AddSC_throne_of_the_tides()
{
    new npc_lady_nazjar_event();
    new go_tott_defense_system();
    new at_tott_lower_spawn_event();
    new at_tott_tentacle_knockback();
    new at_tott_nazjar_event_informer();
    new at_tott_ulthok_event_informer();
    new at_tott_neptulon_intro();
    new npc_tott_faceless_sapper();
    new npc_tott_blight_beast();
}
