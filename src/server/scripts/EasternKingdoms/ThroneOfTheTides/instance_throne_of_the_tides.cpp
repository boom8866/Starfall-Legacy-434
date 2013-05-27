
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"
#include "AccountMgr.h"

enum Events
{
    EVENT_LOWER_GENERETIC_SPAWN  = 1,
    EVENT_SUMMON_FALLING_ROCKS   = 2,
    EVENT_REMOVE_RIGHT_TENTACLE  = 3,
    EVENT_REMOVE_LEFT_TENTACLE   = 4,
    EVENT_DESPAWN_GOBS           = 5,
};

static DoorData const doorData[] =
{
    {GO_LADY_NAZJAR_DOOR,        DATA_LADY_NAZJAR,         DOOR_TYPE_ROOM,    BOUNDARY_NONE},
    {GO_MINDEBENDER_GHURSA_DOOR, DATA_MINDEBENDER_GHURSHA, DOOR_TYPE_ROOM,    BOUNDARY_NONE},
    {GO_OZUMAT_DOOR,             DATA_MINDEBENDER_GHURSHA, DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {0,                          0,                        DOOR_TYPE_ROOM,    BOUNDARY_NONE}
};

static Position const genereticSpawnPositions[] =
{
    {-435.313629f, 766.568298f, 263.551331f, 0.167633f}, // Lower permanent spawn event start position
    {-352.479797f, 774.599487f, 265.108704f, 2.810498f}, // Lower permanent spawn event end position
};

class instance_throne_of_the_tides : public InstanceMapScript
{
public:
    instance_throne_of_the_tides() : InstanceMapScript("instance_throne_of_the_tides", 643) {}

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_throne_of_the_tides_InstanceMapScript(map);
    }

    struct instance_throne_of_the_tides_InstanceMapScript : public InstanceScript
    {
        instance_throne_of_the_tides_InstanceMapScript(Map* map) : InstanceScript(map) {}

        // Npcs
        uint64 uiLadyNazjar;
        uint64 uiCommanderUlthok;
        uint64 uiErunakStonespeaker;
        uint64 uiMindbenderGhursha;
        uint64 uiOzumat;
        uint64 uiNeptulon;

        uint64 uiNazjarEventDouble;
        uint64 uiTeleporterUpper;
        uint64 uiTeleporterLower;

        std::vector<uint64> uiLadyNazjarCombatVisualTriggers;
        std::vector<uint64> uiShockDefenseTriggers;

        // Gobs
        uint64 uiCorales;
        uint64 uiCommanderUlthokDoor;
        uint64 uiControlSystem;

        uint64 uiTentacleRight;
        uint64 uiTentacleLeft;

        uint64 uiInvisibleDoorRight;
        uint64 uiInvisibleDoorLeft;

        uint64 uiNeptulonsCache;

        EventMap events;

        // Data
        bool dataLowerSpawnDone;
        bool dataNazjarPreEventDone;
        bool dataShockDefenseDone;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);
            LoadDoorData(doorData);

            uiLadyNazjar                = 0;
            uiCommanderUlthok           = 0;
            uiErunakStonespeaker        = 0;
            uiMindbenderGhursha         = 0;
            uiOzumat                    = 0;
            uiNeptulon                  = 0;

            uiNazjarEventDouble         = 0;

            uiTeleporterUpper           = 0;
            uiTeleporterLower           = 0;

            uiLadyNazjarCombatVisualTriggers.clear();
            uiShockDefenseTriggers.clear();

            uiCorales                   = 0;
            uiCommanderUlthokDoor       = 0;
            uiControlSystem             = 0;

            uiTentacleRight             = 0;
            uiTentacleLeft              = 0;

            uiInvisibleDoorRight        = 0;
            uiInvisibleDoorLeft         = 0;

            uiNeptulonsCache             = 0;

            dataLowerSpawnDone          = false;
            dataNazjarPreEventDone      = false;
            dataShockDefenseDone        = false;

            events.Reset();
            events.ScheduleEvent(EVENT_LOWER_GENERETIC_SPAWN, 2000);
            events.ScheduleEvent(EVENT_SUMMON_FALLING_ROCKS, urand(15000, 30000));
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch(creature->GetEntry())
            {
                case BOSS_LADY_NAZJAR:          uiLadyNazjar = creature->GetGUID(); break;
                case BOSS_COMMANDER_ULTHOK:     uiCommanderUlthok = creature->GetGUID(); break;
                case NPC_ERUNAK_STONESPEAKER:   uiErunakStonespeaker = creature->GetGUID(); break;
                case BOSS_MINDBENDER_GHURSHA:   uiMindbenderGhursha = creature->GetGUID(); break;
                case BOSS_OZUMAT:               uiOzumat = creature->GetGUID(); break;
                case NPC_NEPTULON:              uiNeptulon = creature->GetGUID(); break;
                case NPC_NAZJAR_EVENT_DOUBLE:   uiNazjarEventDouble = creature->GetGUID(); break;
                case NPC_NAZJAR_COMBAT_TRIGGER: uiLadyNazjarCombatVisualTriggers.push_back(creature->GetGUID()); break;
                case NPC_SHOCK_DEFENSE_TRIGGER: uiShockDefenseTriggers.push_back(creature->GetGUID()); break;
                case NPC_TELEPORTER_LOWER:
                {
                    if (GetBossState(DATA_LADY_NAZJAR) == DONE)
                    {
                        creature->CastSpell(creature, SPELL_TELEPORTER_ACTIVE, true);
                        creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    }

                    uiTeleporterLower = creature->GetGUID();
                    break;
                }
                case NPC_TELEPORTER_UPPER:
                {
                    if (GetBossState(DATA_LADY_NAZJAR) == DONE)
                    {
                        creature->CastSpell(creature, SPELL_TELEPORTER_ACTIVE, true);
                        creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    }

                    uiTeleporterUpper = creature->GetGUID();
                    break;
                }
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_LADY_NAZJAR_DOOR:
                case GO_MINDEBENDER_GHURSA_DOOR:
                case GO_OZUMAT_DOOR:
                {
                    AddDoor(go, true);
                    break;
                }
                case GO_CONTROL_SYSTEM:
                {
                    uiControlSystem = go->GetGUID();
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                    break;
                }
                case GO_TENTACLE_RIGHT:
                {
                    uiTentacleRight = go->GetGUID();
                    if (dataShockDefenseDone)
                        go->RemoveFromWorld();
                    break;
                }
                case GO_TENTACLE_LEFT:
                {
                    uiTentacleLeft = go->GetGUID();
                    if (dataShockDefenseDone)
                        go->RemoveFromWorld();
                    break;
                }
                case GO_INVISIBLE_DOOR_R:
                {
                    uiInvisibleDoorRight = go->GetGUID();
                    if (dataShockDefenseDone)
                        go->RemoveFromWorld();
                    break;
                }
                case GO_INVISIBLE_DOOR_L:
                {
                    uiInvisibleDoorLeft = go->GetGUID();
                    if (dataShockDefenseDone)
                        go->RemoveFromWorld();
                    break;
                }
                case GO_CORALES:
                {
                    if (GetBossState(DATA_COMMANDER_ULTHOK) == DONE)
                        go->RemoveFromWorld();

                    uiCorales = go->GetGUID();
                    break;
                }
                case GO_NEPTULONS_CACHE_NH:
                case GO_NEPTULONS_CACHE_HC:
                    uiNeptulonsCache = go->GetGUID();
                    break;
                case GO_COMMANDER_ULTHOK_DOOR:
                    uiCommanderUlthokDoor = go->GetGUID();
                    break;
            }
        }

        bool SetBossState(uint32 data, EncounterState state)
        {
            if (!InstanceScript::SetBossState(data, state))
                return false;

            switch (data)
            {
                case DATA_LADY_NAZJAR:
                {
                    switch (state)
                    {
                        case DONE:
                        {
                            if (Creature* teleporter = instance->GetCreature(uiTeleporterLower))
                            {
                                teleporter->CastSpell(teleporter, SPELL_TELEPORTER_ACTIVE, true);
                                teleporter->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            }

                            if (Creature* teleporter = instance->GetCreature(uiTeleporterUpper))
                            {
                                teleporter->CastSpell(teleporter, SPELL_TELEPORTER_ACTIVE, true);
                                teleporter->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            }
                        }
                        case NOT_STARTED:
                        case FAIL:
                        {
                            // Disable Lady Naz'jar Combat Visuals
                            for (std::vector<uint64>::const_iterator itr = uiLadyNazjarCombatVisualTriggers.begin(); itr != uiLadyNazjarCombatVisualTriggers.end(); ++itr)
                                if (Creature* trigger = instance->GetCreature(*itr))
                                    trigger->RemoveAllAuras();

                            break;
                        }
                        case IN_PROGRESS:
                        {
                            // Enable Lady Naz'jar Combat Visuals
                            for (std::vector<uint64>::const_iterator itr = uiLadyNazjarCombatVisualTriggers.begin(); itr != uiLadyNazjarCombatVisualTriggers.end(); ++itr)
                                if (Creature* trigger = instance->GetCreature(*itr))
                                    trigger->CastSpell(trigger, SPELL_LADY_NAZJAR_COMBAT_VISUAL, true);

                            break;
                        }
                    }
                    break;
                }
                case DATA_OZUMAT:
                {
                    if (data == DONE)
                        DoRespawnGameObject(uiNeptulonsCache);

                    break;
                }
            }

            return true;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_EVENT_DONE_LOWER_SPAWN:
                    dataLowerSpawnDone = (bool)data;
                    SaveToDB();
                    break;
                case DATA_EVENT_DONE_NAZJAR_PRE:
                    dataNazjarPreEventDone = (bool)data;
                    SaveToDB();
                    break;
                case DATA_EVENT_DONE_SHOCK_DEFENSE:
                    dataShockDefenseDone = (bool)data;
                    SaveToDB();
                    break;
            }
        }

        uint32 GetData(uint32 type) const
        {
            switch(type)
            {
                case DATA_EVENT_DONE_LOWER_SPAWN:
                    return (uint32)dataLowerSpawnDone;
                case DATA_EVENT_DONE_NAZJAR_PRE:
                    return (uint32)dataNazjarPreEventDone;
                case DATA_EVENT_DONE_SHOCK_DEFENSE:
                    return (uint32)dataShockDefenseDone;
                default:
                    return 0;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch(identifier)
            {
                case BOSS_LADY_NAZJAR:          return uiLadyNazjar;
                case BOSS_COMMANDER_ULTHOK:     return uiCommanderUlthok;
                case NPC_ERUNAK_STONESPEAKER:   return uiErunakStonespeaker;
                case BOSS_MINDBENDER_GHURSHA:   return uiMindbenderGhursha;
                case BOSS_OZUMAT:               return uiOzumat;
                case NPC_NEPTULON:              return uiNeptulon;
                case NPC_NAZJAR_EVENT_DOUBLE:   return uiNazjarEventDouble;
                case GO_COMMANDER_ULTHOK_DOOR:  return uiCommanderUlthokDoor;
                case GO_CORALES:                return uiCorales;
                default:                        return 0;
            }
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "T T " << GetBossSaveData() << dataLowerSpawnDone << ' ' << dataNazjarPreEventDone << ' ' << dataShockDefenseDone << ' ';

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'T' && dataHead2 == 'T')
            {
                for (uint8 i = 0; i < ENCOUNTER_COUNT; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }

                loadStream >> dataLowerSpawnDone;
                loadStream >> dataNazjarPreEventDone;
                loadStream >> dataShockDefenseDone;

            }
            else
                OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void ProcessEvent(WorldObject* /*source*/, uint32 /*eventId*/)
        {
            for (std::vector<uint64>::const_iterator itr = uiShockDefenseTriggers.begin(); itr != uiShockDefenseTriggers.end(); ++itr)
                if (Creature* trigger = instance->GetCreature(*itr))
                    trigger->CastSpell(trigger, SPELL_SHOCK_DEFENSE_BIG, true);

            events.ScheduleEvent(EVENT_REMOVE_LEFT_TENTACLE, 15700);
            events.ScheduleEvent(EVENT_REMOVE_RIGHT_TENTACLE, 21700);
            events.ScheduleEvent(EVENT_DESPAWN_GOBS, 30000);
        }

        void Update(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LOWER_GENERETIC_SPAWN:
                    {
                        if (Creature* creature = instance->SummonCreature(RAND(NPC_NAZJAR_SOLDIER, NPC_ELEMENTAL_GUARD), genereticSpawnPositions[0], NULL, 20000))
                            creature->GetMotionMaster()->MovePoint(0, genereticSpawnPositions[1]);

                        events.ScheduleEvent(EVENT_LOWER_GENERETIC_SPAWN, urand(2000, 10000));
                        break;
                    }
                    case EVENT_SUMMON_FALLING_ROCKS:
                    {
                        Map::PlayerList const& playerList = instance->GetPlayers();

                        for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                        {
                            if (Creature* trigger = itr->getSource()->FindNearestCreature(NPC_WORLD_TRIGGER, 20.f))
                            {
                                trigger->CastSpell(trigger, SPELL_SUMMON_FALLING_ROCKS);
                                break;
                            }
                        }
                        events.ScheduleEvent(EVENT_SUMMON_FALLING_ROCKS, urand(30000, 60000));
                        break;
                    }
                    case EVENT_REMOVE_LEFT_TENTACLE:
                    {
                        if (GameObject* tentacle = instance->GetGameObject(uiTentacleLeft))
                            tentacle->SendObjectDeSpawnAnim(tentacle->GetGUID());
                        break;
                    }
                    case EVENT_REMOVE_RIGHT_TENTACLE:
                    {
                        if (GameObject* tentacle = instance->GetGameObject(uiTentacleRight))
                            tentacle->SendObjectDeSpawnAnim(tentacle->GetGUID());
                        break;
                    }
                    case EVENT_DESPAWN_GOBS:
                    {
                        if (GameObject* tentacle = instance->GetGameObject(uiTentacleRight))
                            tentacle->RemoveFromWorld();
                        if (GameObject* tentacle = instance->GetGameObject(uiTentacleLeft))
                            tentacle->RemoveFromWorld();
                        if (GameObject* door = instance->GetGameObject(uiInvisibleDoorLeft))
                            door->RemoveFromWorld();
                        if (GameObject* door = instance->GetGameObject(uiInvisibleDoorRight))
                            door->RemoveFromWorld();

                        break;
                    }
                }
            }
        }
    };
};

void AddSC_instance_throne_of_the_tides()
{
    new instance_throne_of_the_tides();
}
