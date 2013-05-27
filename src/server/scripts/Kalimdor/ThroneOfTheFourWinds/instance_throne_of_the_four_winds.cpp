
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "throne_of_the_four_winds.h"
#include "Group.h"
#include "Vehicle.h"
#include "GameObjectAI.h"

enum Events
{
    EVENT_CONCLAVE_BERSERK          = 1,
    EVENT_CONCLAVE_INTRO            = 2,
    EVENT_CONCLAVE_ENERGY_REGEN     = 3,
    EVENT_CONCLAVE_SYNCH_ENERGY     = 4,
    EVENT_CONCLAVE_OUTFIGHT_CHECK   = 5
};

Position const PortBackPositions[8] =
{
    {-84.748047f, 609.273010f, 199.492737f, 5.44601f},
    {-18.493235f, 609.295593f, 199.491745f, 3.87522f},
    {155.608353f, 779.386658f, 199.492798f, 0.74148f},
    {156.094391f, 844.981018f, 199.490326f, 5.48137f},
    {-14.662740f, 1019.94000f, 199.491318f, 2.33976f},
    {-80.575035f, 1019.81939f, 199.491043f, 0.75719f},
    {-255.09555f, 783.734985f, 199.490784f, 2.36042f},
    {-255.18203f, 849.192383f, 199.490311f, 3.93805f}
};

#define GetConclaveMember(x) instance->GetCreature(uiConclaveOfWind[x])

class instance_throne_of_the_four_winds : public InstanceMapScript
{
public:
    instance_throne_of_the_four_winds() : InstanceMapScript("instance_throne_of_the_four_winds", 754) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_throne_of_the_four_winds_InstanceMapScript(map);
    }

    struct instance_throne_of_the_four_winds_InstanceMapScript: public InstanceScript
    {
        instance_throne_of_the_four_winds_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        EventMap events;
        uint8 introStep;

        uint64 uiConclaveOfWind[CONCLAVE_MEMBERS];
        uint64 uiConclaveOfWindSilenceTriggers[CONCLAVE_MEMBERS];

        uint64 uiAlakir;

        uint64 uiWinddraftMiddle;
        uint64 uiRaidplatform;
        uint64 uiDeijingHealing;
        uint64 uiDeijingFrost;
        uint64 uiDeijingTornado;
        std::map<uint32, uint64> uiWindDrafts;
        std::vector<uint64> uiHurricaneStalkers;

        bool isUmltimateInProgress;
        bool wasUltimateWarningSent;
        bool isConclaveInBerserk;

        void Initialize()
        {
            SetBossNumber(ENCOUNTER_COUNT);

            memset(&uiConclaveOfWind, 0, sizeof(uiConclaveOfWind));
            memset(&uiConclaveOfWindSilenceTriggers, 0, sizeof(uiConclaveOfWind));

            uiAlakir            = 0;

            uiWinddraftMiddle   = 0;
            uiRaidplatform      = 0;
            uiDeijingHealing    = 0;
            uiDeijingFrost      = 0;
            uiDeijingTornado    = 0;

            isUmltimateInProgress   = false;
            wasUltimateWarningSent  = false;
            isConclaveInBerserk     = false;

            uiWindDrafts.clear();
            uiHurricaneStalkers.clear();
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_ANSHAL:
                    uiConclaveOfWind[TYPE_ANSHAL] = creature->GetGUID();
                    creature->SetPower(POWER_MANA, 0);
                    break;
                case BOSS_NEZIR:
                    uiConclaveOfWind[TYPE_NEZIR]  = creature->GetGUID();
                    creature->SetPower(POWER_MANA, 0);
                    break;
                case BOSS_ROHASH:
                    uiConclaveOfWind[TYPE_ROHASH] = creature->GetGUID();
                    creature->SetPower(POWER_MANA, 0);
                    break;
                case BOSS_ALAKIR:
                    uiAlakir = creature->GetGUID();
                    break;
                case NPC_WESTWIND:
                    uiConclaveOfWindSilenceTriggers[TYPE_ANSHAL] = creature->GetGUID();
                    break;
                case NPC_NORTHWIND:
                    uiConclaveOfWindSilenceTriggers[TYPE_NEZIR]  = creature->GetGUID();
                    break;
                case NPC_EASTWIND:
                    uiConclaveOfWindSilenceTriggers[TYPE_ROHASH] = creature->GetGUID();
                    break;
                case NPC_HURRICANE_STALKER:
                    uiHurricaneStalkers.push_back(creature->GetGUID());
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            uint32 const entry = go->GetEntry();
            uint64 const guid = go->GetGUID();

            switch (entry)
            {
                case GOB_WIND_DRAFTEFFECT_CENTER:
                    uiWinddraftMiddle = guid;
                    break;
                case GOB_RAIDPLATFORM:
                    uiRaidplatform = guid;
                    break;
                case GOB_DEIJING_HEALING:
                    uiDeijingHealing = guid;
                    break;
                case GOB_DEIJING_FROST:
                    uiDeijingFrost = guid;
                    break;
                case GOB_DEIJING_TORNADO:
                    uiDeijingTornado = guid;
                    break;
                case GOB_WIND_DRAFTEFFECT_1:
                case GOB_WIND_DRAFTEFFECT_2:
                case GOB_WIND_DRAFTEFFECT_3:
                case GOB_WIND_DRAFTEFFECT_4:
                case GOB_WIND_DRAFTEFFECT_5:
                case GOB_WIND_DRAFTEFFECT_6:
                case GOB_WIND_DRAFTEFFECT_7:
                case GOB_WIND_DRAFTEFFECT_8:
                    if (uiWindDrafts.find(entry) == uiWindDrafts.end())
                        uiWindDrafts.insert(std::make_pair(entry, guid));
                    break;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
                case BOSS_ANSHAL:
                    return uiConclaveOfWind[TYPE_ANSHAL];
                case BOSS_NEZIR:
                    return uiConclaveOfWind[TYPE_NEZIR];
                case BOSS_ROHASH:
                    return uiConclaveOfWind[TYPE_ROHASH];
                case BOSS_ALAKIR:
                    return uiAlakir;
                case NPC_WESTWIND:
                    return uiConclaveOfWindSilenceTriggers[TYPE_ANSHAL];
                case NPC_NORTHWIND:
                    return uiConclaveOfWindSilenceTriggers[TYPE_NEZIR];
                case NPC_EASTWIND:
                    return uiConclaveOfWindSilenceTriggers[TYPE_ROHASH];
                case GOB_DEIJING_HEALING:
                    return uiDeijingHealing;
                case GOB_DEIJING_FROST:
                    return uiDeijingFrost;
                case GOB_DEIJING_TORNADO:
                    return uiDeijingTornado;
                case GOB_WIND_DRAFTEFFECT_1:
                case GOB_WIND_DRAFTEFFECT_2:
                case GOB_WIND_DRAFTEFFECT_3:
                case GOB_WIND_DRAFTEFFECT_4:
                case GOB_WIND_DRAFTEFFECT_5:
                case GOB_WIND_DRAFTEFFECT_6:
                case GOB_WIND_DRAFTEFFECT_7:
                case GOB_WIND_DRAFTEFFECT_8:
                {
                    std::map<uint32, uint64>::const_iterator windDraft = uiWindDrafts.find(identifier);
                    return windDraft != uiWindDrafts.end() ? windDraft->second : 0;
                }
            }
            return 0;
        }

        bool SetBossState(uint32 data, EncounterState state)
        {
            if (data == DATA_CONCLAVE_OF_WIND && state == NOT_STARTED && !AreAllPlayersDead())
                return false;

            if (!InstanceScript::SetBossState(data, state))
                return false;

            switch (data)
            {
                case DATA_CONCLAVE_OF_WIND:
                {
                    switch (state)
                    {
                        case IN_PROGRESS:
                        {
                            DoSendActionToWindDrafts(ACTION_WINDDRAFT_IN_COMBAT);

                            for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                            {
                                if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                                {
                                    conclaveOfWindMember->RemoveAurasDueToSpell(SpellPreCombat[i]);
                                    conclaveOfWindMember->SetPower(POWER_MANA, 0);
                                    conclaveOfWindMember->SetMaxPower(POWER_MANA, 90);

                                    if (i == TYPE_NEZIR)
                                    {
                                        conclaveOfWindMember->AI()->TalkToFar(SAY_CONCLAVE_INTRO, TEXT_RANGE_AREA);
                                        conclaveOfWindMember->AI()->AddEncounterFrame();
                                    }
                                }
                            }

                            introStep = 0;
                            isUmltimateInProgress = false;
                            wasUltimateWarningSent = false;
                            isConclaveInBerserk = false;

                            events.Reset();

                            events.ScheduleEvent(EVENT_CONCLAVE_INTRO, 1500);
                            events.ScheduleEvent(EVENT_CONCLAVE_BERSERK, 600000);
                            events.ScheduleEvent(EVENT_CONCLAVE_ENERGY_REGEN, 1055);
                            events.ScheduleEvent(EVENT_CONCLAVE_OUTFIGHT_CHECK, 3000);
                            events.ScheduleEvent(EVENT_CONCLAVE_SYNCH_ENERGY, 5000);
                            break;
                        }
                        case DONE:
                        {
                            events.Reset();
                            isUmltimateInProgress = false;
                            wasUltimateWarningSent = false;
                            isConclaveInBerserk = false;

                            DoSendActionToWindDrafts(ACTION_WINDDRAFT_OUT_OF_COMBAT);

                            for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                            {
                                if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                                {
                                    conclaveOfWindMember->AI()->RemoveEncounterFrame();

                                    switch (i)
                                    {
                                        case TYPE_ANSHAL:
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_SOOTHING_BREEZE);
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_RAVENOUS_CREEPER_TRIGGER);
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_RAVENOUS_CREEPER);
                                            break;
                                        case TYPE_NEZIR:
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_ICE_PATCH);
                                            break;
                                        case TYPE_ROHASH:
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_HURRICANE);
                                            break;
                                    }

                                    conclaveOfWindMember->InterruptNonMeleeSpells(false);
                                    conclaveOfWindMember->Kill(conclaveOfWindMember);
                                    conclaveOfWindMember->RemoveAllAuras();
                                    conclaveOfWindMember->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    conclaveOfWindMember->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                                }
                            }

                            if (Creature* alakir = instance->GetCreature(uiAlakir))
                            {
                                alakir->CastSpell(alakir, SPELL_ACHIEVEMENT_CONCLAVE, true);
                                alakir->AI()->TalkToFar(SAY_ALAKIR_CONCLAVE_DEFEATED, TEXT_RANGE_AREA);
                            }

                            Map::PlayerList const &PlList = instance->GetPlayers();
                            for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                            {
                                if (i == PlList.begin())
                                {
                                    Group* group = i->getSource()->GetGroup();
                                    Player* groupLeader = NULL;
                                    if (group)
                                        groupLeader = ObjectAccessor::GetPlayer(*i->getSource(), group->GetLeaderGUID());

                                    if (!groupLeader)
                                        groupLeader = i->getSource();

                                    ((InstanceMap*)instance)->PermBindAllPlayers(groupLeader);
                                }

                                i->getSource()->ModifyCurrency(396, 70);
                            }
                            break;
                        }
                        case NOT_STARTED:
                        case FAIL:
                        {
                            isUmltimateInProgress = false;
                            wasUltimateWarningSent = false;
                            isConclaveInBerserk = false;

                            introStep = 0;
                            events.Reset();

                            DoSendActionToWindDrafts(ACTION_WINDDRAFT_OUT_OF_COMBAT);

                            for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                            {
                                if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                                {
                                    conclaveOfWindMember->AI()->EnterEvadeMode();

                                    conclaveOfWindMember->SetPower(POWER_MANA, 0);
                                    conclaveOfWindMember->SetMaxPower(POWER_MANA, 90);
                                    conclaveOfWindMember->AI()->RemoveEncounterFrame();

                                    conclaveOfWindMember->SetReactState(REACT_AGGRESSIVE);
                                    conclaveOfWindMember->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    conclaveOfWindMember->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                                    conclaveOfWindMember->InterruptNonMeleeSpells(false);

                                    conclaveOfWindMember->CastSpell(conclaveOfWindMember, SpellPreCombat[i], true);

                                    switch (i)
                                    {
                                        case TYPE_ANSHAL:
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_SOOTHING_BREEZE);
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_RAVENOUS_CREEPER_TRIGGER);
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_RAVENOUS_CREEPER, 500.f);
                                            break;
                                        case TYPE_NEZIR:
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_ICE_PATCH);
                                            break;
                                        case TYPE_ROHASH:
                                            conclaveOfWindMember->DespawnCreaturesInArea(NPC_HURRICANE);
                                            break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case DATA_ALAKIR:
                {
                    switch (state)
                    {
                        case IN_PROGRESS:
                            break;
                        case DONE:
                        {
                            break;
                        }
                        case NOT_STARTED:
                        case FAIL:
                            break;
                    }
                    break;
                }
            }

            return true;
        }

        void Update(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CONCLAVE_BERSERK:
                    {
                        if (Creature* alakir = instance->GetCreature(uiAlakir))
                            alakir->AI()->TalkToFar(SAY_ALAKIR_CONCLAVE_BERSERK, TEXT_RANGE_AREA);

                        isConclaveInBerserk = true;

                        for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                            if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                                if (conclaveOfWindMember->isAlive() && conclaveOfWindMember->HasReactState(REACT_AGGRESSIVE))
                                    conclaveOfWindMember->CastSpell(conclaveOfWindMember, SPELL_BERSERK);

                        break;
                    }
                    case EVENT_CONCLAVE_INTRO:
                    {
                        switch (introStep)
                        {
                            case 1:
                            {
                                if (Creature* anshal = GetConclaveMember(TYPE_ANSHAL))
                                {
                                    anshal->AI()->TalkToFar(SAY_CONCLAVE_INTRO, TEXT_RANGE_AREA);
                                    anshal->AI()->AddEncounterFrame();
                                }
                                break;
                            }
                            case 2:
                            {
                                if (Creature* rohash = GetConclaveMember(TYPE_ROHASH))
                                {
                                    rohash->AI()->TalkToFar(SAY_CONCLAVE_INTRO, TEXT_RANGE_AREA);
                                    rohash->AI()->AddEncounterFrame();
                                }
                                break;
                            }
                        }

                        if (++introStep <= 2)
                            events.ScheduleEvent(EVENT_CONCLAVE_INTRO, 1500);
                        else
                            introStep = 0;

                        break;
                    }
                    case EVENT_CONCLAVE_ENERGY_REGEN:
                    {
                        for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                        {
                            if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                            {
                                uint32 const currentMana = uint32(conclaveOfWindMember->GetPower(POWER_MANA));

                                if (conclaveOfWindMember->isDead() || conclaveOfWindMember->HasReactState(REACT_PASSIVE) || (currentMana >= uint32(conclaveOfWindMember->GetMaxPower(POWER_MANA))))
                                    continue;

                                conclaveOfWindMember->ModifyPower(POWER_MANA, 1);

                                if (currentMana >= 79 && !wasUltimateWarningSent)
                                {
                                    events.CancelEvent(EVENT_CONCLAVE_SYNCH_ENERGY);

                                    wasUltimateWarningSent = true;
                                    if (Creature* alakir = instance->GetCreature(uiAlakir))
                                       alakir->AI()->TalkToFar(SAY_ALAKIR_CONCLAVE_ULTIMATE, TEXT_RANGE_AREA);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_CONCLAVE_ENERGY_REGEN, 1055);
                        break;
                    }
                    case EVENT_CONCLAVE_SYNCH_ENERGY:
                    {
                        uint32 maxEnergy = 0;

                        // Find maxEnergy
                        for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                        {
                            if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                                if (conclaveOfWindMember->isAlive() && conclaveOfWindMember->HasReactState(REACT_AGGRESSIVE))
                                    if (maxEnergy < uint32(conclaveOfWindMember->GetPower(POWER_MANA)) && 83 >= uint32(conclaveOfWindMember->GetPower(POWER_MANA)))
                                        maxEnergy = uint32(conclaveOfWindMember->GetPower(POWER_MANA));
                        }
                        for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
                        {
                            // Apply maxEnergy
                            if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                                if (conclaveOfWindMember->isAlive() && conclaveOfWindMember->HasReactState(REACT_AGGRESSIVE))
                                    conclaveOfWindMember->SetPower(POWER_MANA, maxEnergy);
                        }
                        events.ScheduleEvent(EVENT_CONCLAVE_SYNCH_ENERGY, urand(5000, 6500));
                        break;
                    }
                    case EVENT_CONCLAVE_OUTFIGHT_CHECK:
                    {
                        if (AreAllPlayersDead())
                            SetBossState(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
                        else
                            events.ScheduleEvent(EVENT_CONCLAVE_OUTFIGHT_CHECK, 3000);

                        break;
                    }
                }
            }
        }

        uint32 GetData(uint32 type) const
        {
            switch (type)
            {
                case DATA_IS_CONCLAVE_IN_BERSERK:
                    return isConclaveInBerserk;
                default:
                    return 0;
            }
            
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_IS_ULTIMATE_IN_PROGRESS:
                {
                    if (isUmltimateInProgress == bool(data))
                        return;

                    isUmltimateInProgress = data;
                    if (!isUmltimateInProgress)
                    {
                        wasUltimateWarningSent = false;
                        events.CancelEvent(EVENT_CONCLAVE_SYNCH_ENERGY);
                        events.ScheduleEvent(EVENT_CONCLAVE_SYNCH_ENERGY, urand(5000, 6500));
                    }

                    DoSendActionToWindDrafts(isUmltimateInProgress ? ACTION_WINDDRAFT_ULTIMATE_BEGIN : ACTION_WINDDRAFT_ULTIMATE_END);
                    break;
                }
                case DATA_HURRICANE_ENDED:
                {
                    for (std::vector<uint64>::const_iterator itr = uiHurricaneStalkers.begin(); itr != uiHurricaneStalkers.end(); ++itr)
                        if (Creature* stalker = instance->GetCreature(*itr))
                            if (Vehicle* vehicle = stalker->GetVehicleKit())
                                vehicle->RemoveAllPassengers();
                    break;
                }
                case DATA_CONCLAVE_MEMBER_FALLEN:
                {
                    switch (data)
                    {
                    case BOSS_ANSHAL:
                    case BOSS_NEZIR:
                    case BOSS_ROHASH:
                        {
                            if (CheckConclaveDone())
                                SetBossState(DATA_CONCLAVE_OF_WIND, DONE);
                            else if (Creature* conclaveMember = instance->GetCreature(uiConclaveOfWind[GetConclaveTypeByEntry(data)]))
                                conclaveMember->AI()->TalkToFar(SAY_CONCLAVE_DEATH_WARNING, TEXT_RANGE_AREA);
                        }
                        break;
                    }
                    break;
                }
            }
        }

        void SetData64(uint32 type, uint64 data)
        {
            switch (type)
            {
                case DATA_PLAYER_HIT_BY_HURRICANE:
                {
                    for (std::vector<uint64>::const_iterator itr = uiHurricaneStalkers.begin(); itr != uiHurricaneStalkers.end(); ++itr)
                    {
                        if (Creature* stalker = instance->GetCreature(*itr))
                            if (Vehicle* vehicle = stalker->GetVehicleKit())
                                for (uint8 seat = 0; seat < 5; ++seat)
                                    if (!vehicle->GetPassenger(seat))
                                        if (Player* player = ObjectAccessor::GetPlayer(*stalker, data))
                                        {
                                            if (!player->GetVehicleBase())
                                            {
                                                if(Aura* aura = player->AddAura(SPELL_SLIPSTREAM, player))
                                                    aura->SetDuration(21000);

                                                player->EnterVehicle(stalker, seat);
                                            }
                                            return;
                                        }
                    }
                    break;
                }
                case DATA_PLAYER_UNDER_MAP:
                {
                    if (Player* player = ObjectAccessor::FindPlayer(data))
                    {
                        if (player->HasAura(SPELL_SLIPSTREAM_VISUAL))
                            break;

                        Position pos = PortBackPositions[0];
                        for (uint8 i = 1; i < ((GetBossState(DATA_CONCLAVE_OF_WIND) == IN_PROGRESS) ? 6 : 8); ++i)
                            if (player->GetDistance(PortBackPositions[i]) < player->GetDistance(pos))
                                pos = PortBackPositions[i];

                        float const dist = player->GetDistance(pos);

                        player->CastSpell(player, SPELL_SLIPSTREAM_VISUAL, true);
                        player->GetMotionMaster()->MoveJump(pos.m_positionX, pos.m_positionY, pos.m_positionZ, dist > 80.f ? 25.f : 10.f, 1.f + (dist > 70.f ? 70.f : dist));
                    }
                    break;
                }
            }
        }

        inline bool CheckConclaveDone()
        {
            for (uint8 i = 0; i < CONCLAVE_MEMBERS; ++i)
            {
                if (Creature* conclaveOfWindMember = GetConclaveMember(i))
                    if (conclaveOfWindMember->isAlive() && conclaveOfWindMember->HasReactState(REACT_AGGRESSIVE))
                        return false;
            }

            return true;
        }

        void DoSendActionToWindDrafts(uint32 action)
        {
            for (std::map<uint32, uint64>::const_iterator itr = uiWindDrafts.begin(); itr != uiWindDrafts.end(); ++itr)
                if (GameObject* windDraft = instance->GetGameObject(itr->second))
                    windDraft->AI()->DoAction(action);
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "T W " << GetBossSaveData();

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

            if (dataHead1 == 'T' && dataHead2 == 'W')
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
    };
};

void AddSC_instance_throne_of_the_four_winds()
{
    new instance_throne_of_the_four_winds();
}
