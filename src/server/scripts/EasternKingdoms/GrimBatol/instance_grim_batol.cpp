#include "ScriptPCH.h"
#include "grim_batol.h"

enum Events
{
    EVENT_STAIR_SPAWN_1         = 1,
    EVENT_STAIR_SPAWN_2         = 2,
    EVENT_STAIR_SPAWN_3         = 3,
    EVENT_STAIR_SPAWN_4         = 4,
    EVENT_SPAWN_DRAKE           = 5,
    EVENT_REMOVE_REGEN_AURA     = 6,
};

enum Paths
{
    PATH_FLYING_DRAGON_LOW      = 2216300,
    PATH_FLYING_DRAGON_HIGH     = 2216306
};

Position const FlyingDrakeSpawnPosition = {-243.f, -533.f, 277.f, 3.17f};

StairSpawnerData const stairSpawn[4] =
{
    { NPC_TWILIGHT_WYRM_CALLER, NPC_TWILIGHT_FIRE_CATCHER,  7000, 13000, {-532.884583f, -359.447052f, 236.847977f, 4.737158f}, {-533.05481f , -320.859650f, 236.844742f, 1.587710f}, 8500 },
    { NPC_TWILIGHT_WYRM_CALLER, NPC_TWILIGHT_FIRE_CATCHER,  7000, 13000, {-618.461182f, -382.251373f, 236.845947f, 5.216245f}, {-637.835022f, -349.106720f, 236.843689f, 2.109996f}, 8500 },
    { NPC_TROGG_DWELLER,        NPC_TROGG_DWELLER,          7000, 13000, {-618.458679f, -678.244629f, 236.846359f, 1.f      }, {-637.304871f, -711.703796f, 236.844025f, 4.180902f}, 8000 },
    { NPC_TWILIGHT_WYRM_CALLER, NPC_TWILIGHT_EARTHSHAPER,   7000, 13000, {-532.824585f, -701.085449f, 236.84816f , 1.57180f }, {-532.587891f, -739.763062f, 236.846069f, 4.719882f}, 8500 },
};

class instance_grim_batol : public InstanceMapScript
{
public:
    instance_grim_batol() : InstanceMapScript("instance_grim_batol", 670) { }

    struct instance_grim_batol_InstanceMapScript: public InstanceScript
    {
        instance_grim_batol_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        bool isShadowGaleStalkerVisible;

        EventMap events;
        std::set<uint32> pathList;
        std::set<uint64> creatureList;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);

            _umbrissGUID = 0;
            _throngusGUID = 0;
            _drahgaGUID = 0;
            _erudaxGUID = 0;

            isShadowGaleStalkerVisible = false;

            pathList.clear();
            creatureList.clear();

            events.Reset();

            for(uint8 i = EVENT_STAIR_SPAWN_1; i <= EVENT_SPAWN_DRAKE; ++i)
                events.ScheduleEvent(i, urand(1000, 3000));
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_GENERAL_UMBRISS:
                    _umbrissGUID = creature->GetGUID();
                    break;
                case BOSS_FORGEMASTER_THRONGUS:
                    _throngusGUID = creature->GetGUID();
                    break;
                case BOSS_DRAHGA_SHADOWBURNER:
                    _drahgaGUID = creature->GetGUID();
                    break;
                case BOSS_ERUDAX:
                    _erudaxGUID = creature->GetGUID();
                    break;
                case NPC_VALIONA:
                    _valionaGUID = creature->GetGUID();
                    break;
                case NPC_TWILIGHT_DRAKE:
                case NPC_BATTERED_RED_DRAKE:
                case NPC_BATTERED_RED_DRAKE_EVENT:
                    break;
            }

            if (creature->isSummon())
                return;

            creatureList.insert(creature->GetGUID());
        }

        void OnCreatureRemove(Creature* creature)
        {
            std::set<uint64>::const_iterator itr = creatureList.find(creature->GetGUID());
            if(itr != creatureList.end())
                creatureList.erase(itr);
        }

        uint64 GetData64(uint32 type) const
        {
            switch (type)
            {
                case DATA_GENERAL_UMBRISS:
                    return _umbrissGUID;
                    break;
                case DATA_FORGEMASTER_THRONGUS:
                    return _throngusGUID;
                    break;
                case DATA_DRAHGA_SHADOWBURNER:
                    return _drahgaGUID;
                    break;
                case NPC_VALIONA:
                    return _valionaGUID;
                    break;
                case DATA_ERUDAX:
                    return _erudaxGUID;
                    break;
                default:
                    return 0;
            }
            return NULL;
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type == DATA_SHADOW_GALE_STALKER_ACTIVE && (bool(data) != isShadowGaleStalkerVisible))
            {
                isShadowGaleStalkerVisible = bool(data);
                UpdatePhasing();
            }
        }

        uint32 GetData(uint32 type) const
        {
            switch (type)
            {
                case DATA_SHADOW_GALE_STALKER_ACTIVE:
                    return isShadowGaleStalkerVisible;
                default:
                    return 0;
            }
        }

        bool SetBossState(uint32 data, EncounterState state)
        {
            if (!InstanceScript::SetBossState(data, state))
                return false;

            if (data == DATA_FORGEMASTER_THRONGUS && state == DONE)
                UpdatePhasing();

            return true;
        }

        void Update(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_STAIR_SPAWN_1:
                    case EVENT_STAIR_SPAWN_2:
                    case EVENT_STAIR_SPAWN_3:
                    case EVENT_STAIR_SPAWN_4:
                    {
                        Position startPosition = stairSpawn[eventId-1].startPosition;
                        Position endPosition   = stairSpawn[eventId-1].endPosition;

                        if(urand(0, 1))
                            std::swap(startPosition, endPosition);

                        if(Creature* stairCreature = instance->SummonCreature(urand(0, 1) ? stairSpawn[eventId-1].entry0 : stairSpawn[eventId-1].entry1, startPosition, NULL, stairSpawn[eventId-1].duration))
                            stairCreature->GetMotionMaster()->MovePoint(0, endPosition);

                        events.ScheduleEvent(eventId, urand(stairSpawn[eventId-1].timeMin, stairSpawn[eventId-1].timeMax));
                        break;
                    }
                    case EVENT_SPAWN_DRAKE:
                    {
                        if(pathList.size() >= 3)
                            pathList.erase(pathList.begin());

                        std::set<uint32> shadowPathList;
                        for(uint32 i = PATH_FLYING_DRAGON_LOW; i <= PATH_FLYING_DRAGON_HIGH; ++i)
                            if(pathList.find(i) == pathList.end())
                                shadowPathList.insert(i);

                        std::set<uint32>::iterator itr = shadowPathList.begin();
                        std::advance(itr, urand(0, shadowPathList.size()-1));
                        pathList.insert(*itr);

                        if(Creature* flyingDrake = instance->SummonCreature(roll_chance_i(57) ? NPC_TWILIGHT_DRAKE : NPC_BATTERED_RED_DRAKE, FlyingDrakeSpawnPosition, NULL, 172000))
                        {
                            flyingDrake->SetReactState(REACT_PASSIVE);
                            flyingDrake->GetMotionMaster()->MovePath(*itr, false);

                            // Follow Event
                            if(flyingDrake->GetEntry() == NPC_BATTERED_RED_DRAKE && roll_chance_i(30))
                                if(Creature* twilightDrake = flyingDrake->SummonCreature(NPC_TWILIGHT_DRAKE, *flyingDrake, TEMPSUMMON_TIMED_DESPAWN, 170000))
                                {
                                    twilightDrake->SetReactState(REACT_PASSIVE);
                                    twilightDrake->GetMotionMaster()->MoveFollow(flyingDrake, 4.5f, 0);

                                    twilightDrake->AI()->DoAction(ACTION_DRAGON_IS_IN_FOLLOWER_EVENT);
                                    twilightDrake->AI()->SetGUID(flyingDrake->GetGUID());
                                    flyingDrake->AI()->DoAction(ACTION_DRAGON_IS_IN_FOLLOWER_EVENT);
                                    flyingDrake->AI()->SetGUID(twilightDrake->GetGUID());

                                    twilightDrake->CastSpell(twilightDrake, SPELL_TWILIGHT_FLAMES_TRIGGER, true);
                                }
                        }

                        events.ScheduleEvent(EVENT_SPAWN_DRAKE, urand(12000, 19000));
                        break;
                    }
                    case EVENT_REMOVE_REGEN_AURA:
                    {
                        for(std::set<uint64>::const_iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
                            if(Creature* creature = instance->GetCreature(*itr))
                                creature->RemoveAurasDueToSpell(SPELL_NO_HEALTH_REGEN);

                        break;
                    }
                }
            }
        }

        void ProcessEvent(WorldObject* source, uint32 eventId)
        {
            if (eventId == ACTION_START_DRAGON_EVENT)
                if(Creature* creature = source->ToCreature())
                {
                    if(events.GetNextEventTime(EVENT_REMOVE_REGEN_AURA))
                        return;

                    for(std::set<uint64>::const_iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
                        if(Creature* creature = instance->GetCreature(*itr))
                            if(creature->isAlive())
                                creature->AddAura(SPELL_NO_HEALTH_REGEN, creature);

                    std::list<Creature*> creatures;
                    source->GetCreatureListWithEntryInGrid(creatures, NPC_BATTERED_RED_DRAKE_EVENT, 100.f);

                    for(std::list<Creature*>::const_iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                        creature->DespawnOrUnsummon(240000);

                    events.ScheduleEvent(EVENT_REMOVE_REGEN_AURA, 250000);
                }
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "G B " << GetBossSaveData();

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

            if (dataHead1 == 'G' && dataHead2 == 'B')
            {
                for (uint8 i = 0; i < ENCOUNTER_COUNT; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }

            } else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        protected:
            uint64 _umbrissGUID;
            uint64 _throngusGUID;
            uint64 _drahgaGUID;
            uint64 _valionaGUID;
            uint64 _erudaxGUID;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_grim_batol_InstanceMapScript(map);
    }
};

void AddSC_instance_grim_batol()
{
    new instance_grim_batol();
}
