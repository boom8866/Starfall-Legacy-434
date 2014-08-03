/*
* Copyright (C) 2012-2013 Reign of Darkness Network <http://reignofdarkness.net/>
*
* Este codigo es de uso exclusivo y privado para la red de gaming
* Reign of Darkness Network esta totalmente prohibida su distribucion y
* uso en proyectos ajenos, si has obtenido o encontrado este codigo
* publicamente envianos un email a administracion@reignofdarkness.net
* indicandonos como y donde has obtenido este codigo
*
* Recuerda, no distribuyas, no compartas y no subas este codigo a ningun
* lugar publico, usa siempre nuestros repositorios Git!
*/

/* Tol Barad Battlefield*/

#include "BattlefieldTB.h"
#include "Battlefield.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "TemporarySummon.h"
#include "WorldSession.h"
#include "SpellAuras.h"

BattlefieldTB::~BattlefieldTB()
{
    for (TbWorkShop::const_iterator itr = WorkShopList.begin(); itr != WorkShopList.end(); ++itr)
        delete *itr;

    for (TbGameObjectBuilding::const_iterator itr = BuildingsInZone.begin(); itr != BuildingsInZone.end(); ++itr)
        delete *itr;
}

bool BattlefieldTB::SetupBattlefield()
{
    InitStalker(70, -1244.58f, 981.233f, 155.426f, 0);
    m_TypeId = BATTLEFIELD_TB;                                                              //View enum BattlefieldTypes
    m_BattleId = BATTLEFIELD_BATTLEID_TB;
    m_ZoneId = BATTLEFIELD_TB_ZONEID;                                                       // Tol Barad
    m_MapId = BATTLEFIELD_TB_MAPID;                                                         // Map X
    m_Guid = MAKE_NEW_GUID((m_BattleId ^ 0x20000), 0, HIGHGUID_BATTLEGROUND);

    m_MaxPlayer = sWorld->getIntConfig(CONFIG_TOLBARAD_PLR_MAX);
    m_IsEnabled = sWorld->getBoolConfig(CONFIG_TOLBARAD_ENABLE);
    m_MinPlayer = sWorld->getIntConfig(CONFIG_TOLBARAD_PLR_MIN);
    m_MinLevel = sWorld->getIntConfig(CONFIG_TOLBARAD_PLR_MIN);
    m_BattleTime = sWorld->getIntConfig(CONFIG_TOLBARAD_BATTLETIME) * MINUTE * IN_MILLISECONDS;
    m_NoWarBattleTime = sWorld->getIntConfig(CONFIG_TOLBARAD_NOBATTLETIME) * MINUTE * IN_MILLISECONDS;
    m_RestartAfterCrash = sWorld->getIntConfig(CONFIG_TOLBARAD_RESTART_AFTER_CRASH) * MINUTE * IN_MILLISECONDS;

    m_TimeForAcceptInvite = 20;
    m_StartGroupingTimer = 15 * MINUTE * IN_MILLISECONDS;
    m_StartGrouping = false;

    KickPosition.Relocate(-592.974f, 1183.929f, 95.631f, 0);
    KickPosition.m_mapId = m_MapId;
    RegisterZone(m_ZoneId);

    m_Data32.resize(BATTLEFIELD_TB_DATA_MAX);

    m_saveTimer = 60000;

    m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] = 0;

    // Init GraveYards
    SetGraveyardNumber(BATTLEFIELD_TB_GY_MAX);

    //Load from db
    if ((sWorld->getWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED) == 0) && (sWorld->getWorldState(WS_TB_HORDE_DEFENCE) == 0) && (sWorld->getWorldState(ClockBTWorldState[0]) == 0))
    {
        sWorld->setWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED, uint64(false));
        sWorld->setWorldState(WS_TB_HORDE_DEFENCE, uint64(urand(0, 1)));
        sWorld->setWorldState(ClockBTWorldState[0], uint64(m_NoWarBattleTime));
    }

    if (sWorld->getWorldState(20012) == 0)
        sWorld->setWorldState(20012, urand(1,3));

    if (sWorld->getWorldState(20011) == 0)
        sWorld->setWorldState(20011, time(NULL) + 86400);

    m_isActive = sWorld->getWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED);
    m_DefenderTeam = (TeamId)sWorld->getWorldState(WS_TB_HORDE_DEFENCE);

    m_Timer = sWorld->getWorldState(ClockBTWorldState[0]);
    if (m_isActive)
    {
        m_isActive = false;
        m_Timer = m_RestartAfterCrash;
    }

    for(uint8 i = 0; i < BATTLEFIELD_TB_GY_MAX; i++)
    {
        BfGraveYardTB* graveyard = new BfGraveYardTB(this);
        if (TBGraveYard[i].startcontrol==TEAM_NEUTRAL)
            //In no war time Gy is control by defender
            graveyard->Initialize(m_DefenderTeam, TBGraveYard[i].gyid);
        else
            graveyard->Initialize(TBGraveYard[i].startcontrol, TBGraveYard[i].gyid);

        graveyard->SetTextId(TBGraveYard[i].textid);
        m_GraveyardList[i] = graveyard;
    }

    for (uint8 i = 0; i < TB_MAX_WORKSHOP; i++)
    {
        BfTBWorkShopData* workshop = new BfTBWorkShopData(this, i);




        //Init:setup variable
        ws->Init(TBWorkShopDataBase[i].worldstate, TBWorkShopDataBase[i].type, TBWorkShopDataBase[i].nameid);
        ws->ChangeControl(GetDefenderTeam(),true);

        //Create Object
        BfCapturePointTB *point = new BfCapturePointTB(this, GetDefenderTeam());

        //Spawn gameobject associate (see in OnGameObjectCreate, of OutdoorPvP for see association)
        point->SetCapturePointData(GetDefenderTeam() == TEAM_ALLIANCE ? TBWorkShopDataBase[i].CapturePoint.entrya : TBWorkShopDataBase[i].CapturePoint.entryh, 732,
            TBWorkShopDataBase[i].CapturePoint.x,
            TBWorkShopDataBase[i].CapturePoint.y,
            TBWorkShopDataBase[i].CapturePoint.z,
            0);
        point->LinkToWorkShop(ws);//Link our point to the capture point (for faction changement)
        AddCapturePoint(point);//Add this capture point to list for update this (view in Update() of OutdoorPvP)

        CapturePoints.insert(point);
        WorkShopList.insert(ws);
        */
    }

    for (uint8 i = 0; i < TB_MAX_DESTROY_MACHINE_NPC; i++)
        if (Creature* creature = SpawnCreature(TBDestroyMachineNPC[i].entrya, TBDestroyMachineNPC[i].x, TBDestroyMachineNPC[i].y, TBDestroyMachineNPC[i].z, TBDestroyMachineNPC[i].o, GetAttackerTeam()))
        {
            HideNpc(creature);
            Vehicles.insert(creature->GetGUID());
            creature->CastSpell(creature, SPELL_VEHICLE_DEFENSE, true);
        }

        //Spawning Buiding
        for (uint8 i = 0; i < TB_MAX_OBJ; i++)
        {
            GameObject* go = SpawnGameObject(TBGameObjectBuillding[i].entry, TBGameObjectBuillding[i].x, TBGameObjectBuillding[i].y, TBGameObjectBuillding[i].z, TBGameObjectBuillding[i].o);
            BfTBGameObjectBuilding* b = new BfTBGameObjectBuilding(this);
            b->Init(go,TBGameObjectBuillding[i].type,TBGameObjectBuillding[i].WorldState,TBGameObjectBuillding[i].nameid);
            b->m_State = BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_INTACT-(GetDefenderTeam()*3);
            BuildingsInZone.insert(b);
        }

        for (uint8 i = 0; i < 4; i++)
            if (Creature* creature = SpawnCreature(QuestGivers[i].entrya, QuestGivers[i].x, QuestGivers[i].y, QuestGivers[i].z, QuestGivers[i].o, TEAM_ALLIANCE))
            {
                HideNpc(creature);
                creature->setFaction(TolBaradFaction[TEAM_ALLIANCE]);
                questgiversA.insert(creature->GetGUID());
            }

            for (uint8 i = 0; i < 4; i++)
                if (Creature* creature = SpawnCreature(QuestGivers[i].entryh, QuestGivers[i].x, QuestGivers[i].y, QuestGivers[i].z, QuestGivers[i].o, TEAM_HORDE))
                {
                    HideNpc(creature);
                    creature->setFaction(TolBaradFaction[TEAM_HORDE]);
                    questgiversH.insert(creature->GetGUID());
                }

                {
                    int i = 0;
                    GuidSet questgivers = (GetDefenderTeam() == TEAM_ALLIANCE ? questgiversA : questgiversH);
                    for (GuidSet::const_iterator itr = questgivers.begin(); itr != questgivers.end(); ++itr)
                    {
                        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                        {
                            if (Creature* creature = unit->ToCreature())
                            {
                                if (!i || i == sWorld->getWorldState(20012))
                                    if (!m_isActive)
                                        ShowNpc(creature, true);
                                i++;
                            }
                        }
                    }
                }

                for (uint8 i = 0; i < 23; i++)
                    if (Creature* creature = SpawnCreature(AllianceSpawnNPC[i].entrya, AllianceSpawnNPC[i].x, AllianceSpawnNPC[i].y, AllianceSpawnNPC[i].z, AllianceSpawnNPC[i].o, TEAM_ALLIANCE))
                    {
                        creature->setFaction(TolBaradFaction[TEAM_ALLIANCE]);
                        npcAlliance.insert(creature->GetGUID());
                    }

                    for (uint8 i = 0; i < 23; i++)
                        if (Creature* creature = SpawnCreature(HordeSpawnNPC[i].entrya, HordeSpawnNPC[i].x, HordeSpawnNPC[i].y, HordeSpawnNPC[i].z, HordeSpawnNPC[i].o, TEAM_HORDE))
                        {
                            creature->setFaction(TolBaradFaction[TEAM_HORDE]);
                            npcHorde.insert(creature->GetGUID());
                        }

                        for (uint8 i = 0; i < 130; i++)
                        {
                            if (Creature* creature = SpawnCreature(TbOldNpcStructure[i].entrya, TbOldNpcStructure[i].x, TbOldNpcStructure[i].y, TbOldNpcStructure[i].z, TbOldNpcStructure[i].o, TEAM_NEUTRAL))
                            {
                                creature->SetRespawnRadius(15.0f);
                                creature->SetDefaultMovementType(RANDOM_MOTION_TYPE);
                                creature->GetMotionMaster()->Initialize();
                                npcOld.insert(creature->GetGUID());
                            }
                        }

                        for (uint8 i = 0; i < 3; i++)
                            if (GameObject* go = SpawnGameObject(TBGameobjectsDoor[i].entrya, TBGameobjectsDoor[i].x, TBGameobjectsDoor[i].y, TBGameobjectsDoor[i].z, TBGameobjectsDoor[i].o))
                            {
                                go->ToGameObject()->SetLootState(GO_READY);
                                go->ToGameObject()->UseDoorOrButton();
                                goDoors.insert(go);
                            }

                            return true;
}

bool BattlefieldTB::Update(uint32 diff)
{
    bool m_return = Battlefield::Update(diff);
    if (m_saveTimer <= diff)
    {
        sWorld->setWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED, m_isActive);
        if (IsWarTime())
        {
            sWorld->setWorldState(WS_TB_ALLIANCE_ATTACK, GetAttackerTeam());
            sWorld->setWorldState(WS_TB_HORDE_ATTACK, GetAttackerTeam());
        }
        else
        {
            sWorld->setWorldState(WS_TB_HORDE_DEFENCE, m_DefenderTeam);
            sWorld->setWorldState(WS_TB_ALLIANCE_DEFENCE, m_DefenderTeam);
        }
        sWorld->setWorldState(ClockBTWorldState[0], m_Timer);
        m_saveTimer = 60 * IN_MILLISECONDS;
    }
    else
        m_saveTimer -= diff;

    // Bad code!!!!!!!!!!!!!!!!
    for (GuidSet::const_iterator itr = m_PlayersIsSpellImu.begin(); itr != m_PlayersIsSpellImu.end(); ++itr)
    {
        if (Player* player = sObjectAccessor->FindPlayer(*itr))
        {
            const WorldSafeLocsEntry* graveyard = GetClosestGraveYard(player);
            if (player->HasAura(SPELL_TB_SPIRITUAL_IMMUNITY))
            {
                if (graveyard)
                {
                    if (player->GetDistance2d(graveyard->x, graveyard->y) > 6.0f)
                    {
                        player->RemoveAurasDueToSpell(SPELL_TB_SPIRITUAL_IMMUNITY);
                        m_PlayersIsSpellImu.erase(player->GetGUID());
                    }
                }
            }
        }
    }

    if (m_isActive)
        if (m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] == 3)
            EndBattle(false);

    return m_return;
}

void BattlefieldTB::OnCreatureCreate(Creature* creature)
{
    // Accessing to db spawned creatures
    switch (creature->GetEntry())
    {
        case BATTLEFIELD_TB_NPC_SPIRIT_HEALER_A:
        case BATTLEFIELD_TB_NPC_SPIRIT_HEALER_H:
        {
            for (uint8 i = 0; i < BATTLEFIELD_TB_GY_MAX; i++)
            {
                TeamId teamId = (creature->GetEntry() == BATTLEFIELD_TB_NPC_SPIRIT_HEALER_A ? TEAM_ALLIANCE : TEAM_HORDE);
                if (BfGraveyard* graveyard = GetGraveyardById(i))
                    graveyard->SetSpirit(creature, teamId);
            }
            break;
        }
    }
}

void BattlefieldTB::OnPlayerLeaveZone(Player* player)
{
    player->RemoveAurasDueToSpell(SPELL_TB_SPIRITUAL_IMMUNITY);
}

void BattlefieldTB::OnPlayerLeaveWar(Player* player)
{
    player->RemoveAurasDueToSpell(SPELL_TB_SPIRITUAL_IMMUNITY);
}

void BattlefieldTB::AddPlayerToResurrectQueue(uint64 npc_guid, uint64 player_guid)
{
    Battlefield::AddPlayerToResurrectQueue(npc_guid, player_guid);
    if (IsWarTime())
    {
        if (Player *player = sObjectAccessor->FindPlayer(player_guid))
        {
            if (!player->HasAura(SPELL_TB_SPIRITUAL_IMMUNITY))
            {
                player->CastSpell(player, SPELL_TB_SPIRITUAL_IMMUNITY, true);
                m_PlayersIsSpellImu.insert(player_guid);

                GraveyardVect gy = GetGraveyardVector();
                    for(uint8 i=0;i<gy.size();i++)
                        gy[i]->AddPlayer(player_guid);

                player->CastSpell(player, SPELL_WAITING_FOR_RESURRECT, true);
            }
        }
    }
}

void BattlefieldTB::OnBattleStart()
{
    m_LastResurectTimer = 30 * IN_MILLISECONDS;
    m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] = 0;
    m_Data32[BATTLEFIELD_TB_DATA_DESTROYED] = 0;

    for (TbGameObjectBuilding::const_iterator itr = BuildingsInZone.begin(); itr != BuildingsInZone.end(); ++itr)
        if ((*itr))
            (*itr)->Rebuild();

    for (TbWorkShop::const_iterator itr = WorkShopList.begin(); itr != WorkShopList.end(); ++itr)
        if ((*itr))
            (*itr)->UpdateWorkshop();

    for (uint8 i = 0; i < BATTLEFIELD_TB_GY_MAX; i++)
    {
        if (i == BATTLEFIELD_TB_GY_BARADIN_HOLD)
            m_GraveyardList[i]->GiveControlTo(GetDefenderTeam());
        else
            m_GraveyardList[i]->GiveControlTo(GetAttackerTeam());
    }

    for (GuidSet::const_iterator itr = npcAlliance.begin(); itr != npcAlliance.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
                HideNpc(creature);

    for (GuidSet::const_iterator itr = npcHorde.begin(); itr != npcHorde.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
                HideNpc(creature);

    for (GuidSet::const_iterator itr = npcOld.begin(); itr != npcOld.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
                HideNpc(creature);

    for (GameobjectSet::const_iterator itr = goDoors.begin(); itr != goDoors.end(); ++itr)
    {
        if (*itr)
        {
            (*itr)->ToGameObject()->SetLootState(GO_READY);
            (*itr)->ToGameObject()->UseDoorOrButton();
        }
    }

    for (GuidSet::const_iterator itr = Vehicles.begin(); itr != Vehicles.end(); ++itr)
    {
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
        {
            if (Creature* creature = unit->ToCreature())
            {
                ShowNpc(creature, false);
                creature->setFaction(TolBaradFaction[GetAttackerTeam()]);
            }
        }
    }

    for (GuidSet::const_iterator itr = questgiversA.begin(); itr != questgiversA.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
                HideNpc(creature);

    for (GuidSet::const_iterator itr = questgiversH.begin(); itr != questgiversH.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
                HideNpc(creature);

    HashMapHolder<Player>::MapType const& plist = sObjectAccessor->GetPlayers();
    for (HashMapHolder<Player>::MapType::const_iterator itr = plist.begin(); itr != plist.end(); ++itr)
    {
        if (Player* player = itr->second)
        {
            SendUpdateWorldState(WS_TB_BATTLE_TIMER_ENABLED, 1);
            SendUpdateWorldState(WS_TB_BATTLE_TIMER, (time(NULL) + GetTimer() / 1000));
            SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS, 0);
            SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS_ENABLED, 1);
            SendUpdateWorldState(WS_TB_HORDE_DEFENCE, 0);
            SendUpdateWorldState(WS_TB_ALLIANCE_DEFENCE, 0);
            SendUpdateWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED, 0);
            SendUpdateWorldState(WS_TB_KEEP_HORDE_DEFENCE, GetDefenderTeam() == TEAM_HORDE ? 1 : 0);
            SendUpdateWorldState(WS_TB_KEEP_ALLIANCE_DEFENCE, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0);
            SendUpdateWorldState(WS_TB_ALLIANCE_ATTACK, GetAttackerTeam() == TEAM_ALLIANCE ? 1 : 0);
            SendUpdateWorldState(WS_TB_HORDE_ATTACK, GetAttackerTeam() == TEAM_HORDE ? 1 : 0);

            switch (GetDefenderTeam())
            {
                case TEAM_ALLIANCE:
                {
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 0);
                    }
                    break;
                }
                case TEAM_HORDE:
                {
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 0);
                    }
                    break;
                }
            }
        }
    }

    //UpdateAllWorldStates();

    for (uint8 team = 0; team < 2; ++team)
    {
        for (GuidSet::const_iterator itr = m_PlayersInWar[team].begin(); itr != m_PlayersInWar[team].end(); ++itr)
        {
            if (Player* player = sObjectAccessor->FindPlayer((*itr)))
            {
                player->RemoveAurasByType(SPELL_AURA_MOUNTED);
                if (player->getClass() == CLASS_DRUID)
                    player->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);
                if (player->GetTeamId() == GetDefenderTeam())
                {
                    uint32 k = urand(0, 3);
                    player->TeleportTo(732, TbDefencerStartPosition[k].m_positionX, TbDefencerStartPosition[k].m_positionY, TbDefencerStartPosition[k].m_positionZ, TbDefencerStartPosition[k].m_orientation);
                    player->CastSpell(player, 88473, true);
                }
                else
                    player->TeleportTo(732, TbDefencerStartPosition[4].m_positionX, TbDefencerStartPosition[4].m_positionY, TbDefencerStartPosition[4].m_positionZ, TbDefencerStartPosition[4].m_orientation);
            }
        }
    }

    SendWarningToAllInZone(BATTLEFIELD_TB_TEXT_START);
}

void BattlefieldTB::UpdateAllWorldStates()
{
    /*HashMapHolder<Player>::MapType const& plist = sObjectAccessor->GetPlayers();
    for (HashMapHolder<Player>::MapType::const_iterator itr = plist.begin(); itr != plist.end(); ++itr)
    {
        if (Player* player = itr->second)
        {
            SendUpdateWorldState(WS_TB_BATTLE_TIMER_ENABLED, 1);
            SendUpdateWorldState(WS_TB_BATTLE_TIMER, (time(NULL) + GetTimer() / 1000));
            SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS, m_Data32[BATTLEFIELD_TB_DATA_CAPTURED]);
            SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS_ENABLED, 1);
            SendUpdateWorldState(WS_TB_HORDE_DEFENCE, 0);
            SendUpdateWorldState(WS_TB_ALLIANCE_DEFENCE, 0);
            SendUpdateWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED, 0);
            SendUpdateWorldState(WS_TB_KEEP_HORDE_DEFENCE, GetDefenderTeam() == TEAM_HORDE ? 1 : 0);
            SendUpdateWorldState(WS_TB_KEEP_ALLIANCE_DEFENCE, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0);
            SendUpdateWorldState(WS_TB_ALLIANCE_ATTACK, GetAttackerTeam() == TEAM_ALLIANCE ? 1 : 0);
            SendUpdateWorldState(WS_TB_HORDE_ATTACK, GetAttackerTeam() == TEAM_HORDE ? 1 : 0);

            switch (GetDefenderTeam())
            {
                case TEAM_ALLIANCE:
                {
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_ALLIANCE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 0);
                    }
                    break;
                }
                case TEAM_HORDE:
                {
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < MAX_CP_DIFF; i++)
                    {
                        if (i == HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 0);
                    }
                    for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                    {
                        if (i == BUILDING_HORDE_DEFENCE)
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 1);
                        else
                            SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 0);
                    }
                    break;
                }
            }
        }
    }*/
}

void BattlefieldTB::OnPlayerJoinWar(Player* player)
{
    player->RemoveAurasDueToSpell(SPELL_VETERAN);
    player->RemoveAurasDueToSpell(SPELL_TB_SPIRITUAL_IMMUNITY);
    player->RemoveAurasDueToSpell(SPELL_TOWER_BONUS);

    if (player->GetZoneId() != m_ZoneId)
        if (player->GetTeamId() == GetDefenderTeam())
        {
            player->TeleportTo(732, -1244.58f, 981.233f, 155.426f, 0);
            player->CastSpell(player, SPELL_SLOW_FALL_TB, true);
        }
        else
            player->TeleportTo(732, -827.212646f, 1187.948608f, 112.81f, 3.092834f);

    if (player->GetTeamId() == GetAttackerTeam())
    {
        player->CastSpell(player, SPELL_VETERAN, true);
        /*if (3-m_Data32[BATTLEFIELD_TB_DATA_DESTROYED]>0)
            player->SetAuraStack(SPELL_TOWER_BONUS, player, 3-m_Data32[BATTLEFIELD_TB_DATA_DESTROYED]);*/
    }
    /*else
    {
        if (m_Data32[BATTLEFIELD_TB_DATA_DESTROYED]>0)
            player->SetAuraStack(SPELL_TOWER_BONUS, player, m_Data32[BATTLEFIELD_TB_DATA_DESTROYED]);
    }*/
}

void BattlefieldTB::OnBattleEnd(bool endbytimer)
{
    if (sWorld->getWorldState(20011) > uint32(time(NULL)))
    {
        if (sWorld->getWorldState(20012) > 2)
            sWorld->setWorldState(20012, 1);
        else
            sWorld->setWorldState(20012, (sWorld->getWorldState(20012) + 1));
        sWorld->setWorldState(20011, time(NULL) + 86400);
    }

    GraveyardVect gy = GetGraveyardVector();
    for(uint8 i=0;i<gy.size();i++)
        gy[i]->Resurrect();

    for (TbGameObjectBuilding::const_iterator itr = BuildingsInZone.begin(); itr != BuildingsInZone.end(); ++itr)
        if ((*itr))
            if (!endbytimer)
                (*itr)->Rebuild();

    for (TbWorkShop::const_iterator itr = WorkShopList.begin(); itr != WorkShopList.end(); ++itr)
        if ((*itr))
            (*itr)->UpdateWorkshop();

    for (BfCapturePointSet::const_iterator itr = CapturePoints.begin(); itr != CapturePoints.end(); ++itr)
        if ((*itr))
            (*itr)->SetTeam(GetDefenderTeam());

    for (BfCapturePointSet::const_iterator itr = CapturePoints.begin(); itr != CapturePoints.end(); ++itr)
        if ((*itr))
            (*itr)->UpdateCapturePointValue();

    for (uint8 i = 0; i < BATTLEFIELD_TB_GY_MAX; i++)
        m_GraveyardList[i]->GiveControlTo(GetDefenderTeam());

    if (GetDefenderTeam() == TEAM_ALLIANCE)
    {
        for (GuidSet::const_iterator itr = npcAlliance.begin(); itr != npcAlliance.end(); ++itr)
            if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                if (Creature* creature = unit->ToCreature())
                    HideNpc(creature);

        for (GuidSet::const_iterator itr = npcHorde.begin(); itr != npcHorde.end(); ++itr)
            if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                if (Creature* creature = unit->ToCreature())
                    ShowNpc(creature, true);
    }
    else if (GetDefenderTeam() == TEAM_HORDE)
    {
        for (GuidSet::const_iterator itr = npcAlliance.begin(); itr != npcAlliance.end(); ++itr)
            if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                if (Creature* creature = unit->ToCreature())
                    ShowNpc(creature, true);

        for (GuidSet::const_iterator itr = npcHorde.begin(); itr != npcHorde.end(); ++itr)
            if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                if (Creature* creature = unit->ToCreature())
                    HideNpc(creature);
    }

    for (GuidSet::const_iterator itr = npcOld.begin(); itr != npcOld.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
                ShowNpc(creature, true);

    for (GameobjectSet::const_iterator itr = goDoors.begin(); itr != goDoors.end(); ++itr)
    {
        if (*itr)
        {
            (*itr)->ToGameObject()->SetLootState(GO_READY);
            (*itr)->ToGameObject()->UseDoorOrButton();
        }
    }

    for (GuidSet::const_iterator itr = Vehicles.begin(); itr != Vehicles.end(); ++itr)
        if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
            if (Creature* creature = unit->ToCreature())
            {
                creature->Kill(creature, false);
                HideNpc(creature);
            }

            for (GuidSet::const_iterator itr = questgiversA.begin(); itr != questgiversA.end(); ++itr)
                if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                    if (Creature* creature = unit->ToCreature())
                        HideNpc(creature);

            for (GuidSet::const_iterator itr = questgiversH.begin(); itr != questgiversH.end(); ++itr)
                if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                    if (Creature* creature = unit->ToCreature())
                        HideNpc(creature);

            {
                int i = 0;
                GuidSet questgivers = GetDefenderTeam() == TEAM_ALLIANCE ? questgiversA : questgiversH;
                for (GuidSet::const_iterator itr = questgivers.begin(); itr != questgivers.end(); ++itr)
                {
                    if (Unit* unit = sObjectAccessor->FindUnit((*itr)))
                    {
                        if (Creature* creature = unit->ToCreature())
                        {
                            if (!i || i == sWorld->getWorldState(20012))
                                ShowNpc(creature, true);
                            i++;
                        }
                    }
                }
            }

            HashMapHolder<Player>::MapType const& plist = sObjectAccessor->GetPlayers();
            for (HashMapHolder<Player>::MapType::const_iterator itr = plist.begin(); itr != plist.end(); ++itr)
            {
                if (Player* player = itr->second)
                {
                    SendUpdateWorldState(WS_TB_BATTLE_TIMER_ENABLED, 0);
                    SendUpdateWorldState(WS_TB_BATTLE_TIMER, 0);
                    SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS, 0);
                    SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS_ENABLED, 0);
                    SendUpdateWorldState(WS_TB_HORDE_DEFENCE, 0);
                    SendUpdateWorldState(WS_TB_ALLIANCE_DEFENCE, 0);
                    SendUpdateWorldState(WS_TB_NEXT_BATTLE_TIMER_ENABLED, 1);
                    SendUpdateWorldState(WS_TB_NEXT_BATTLE_TIMER, (!IsWarTime() ? time(NULL) + (GetTimer() / 1000) : 0));
                    SendUpdateWorldState(WS_TB_KEEP_HORDE_DEFENCE, GetDefenderTeam() == TEAM_HORDE ? 1 : 0);
                    SendUpdateWorldState(WS_TB_KEEP_ALLIANCE_DEFENCE, GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0);
                    SendUpdateWorldState(WS_TB_ALLIANCE_ATTACK, 0);
                    SendUpdateWorldState(WS_TB_HORDE_ATTACK, 0);

                    switch (GetDefenderTeam())
                    {
                        case TEAM_ALLIANCE:
                            for (int i = 0; i < MAX_CP_DIFF; i++)
                            {
                                if (i == ALLIANCE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 0);
                            }
                            for (int i = 0; i < MAX_CP_DIFF; i++)
                            {
                                if (i == ALLIANCE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 0);
                            }
                            for (int i = 0; i < MAX_CP_DIFF; i++)
                            {
                                if (i == ALLIANCE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 0);
                            }
                            for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                            {
                                if (i == BUILDING_ALLIANCE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 0);
                            }
                            for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                            {
                                if (i == BUILDING_ALLIANCE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 0);
                            }
                            for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                            {
                                if (i == BUILDING_ALLIANCE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 0);
                            }
                            break;

                        case TEAM_HORDE:
                            for (int i = 0; i < MAX_CP_DIFF; i++)
                            {
                                if (i == HORDE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_SOUTH_CAPTURE_POINT + i, 0);
                            }
                            for (int i = 0; i < MAX_CP_DIFF; i++)
                            {
                                if (i == HORDE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_EAST_CAPTURE_POINT + i, 0);
                            }
                            for (int i = 0; i < MAX_CP_DIFF; i++)
                            {
                                if (i == HORDE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_WEST_CAPTURE_POINT + i, 0);
                            }
                            for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                            {
                                if (i == BUILDING_HORDE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_EAST_SPIRE + i, 0);
                            }
                            for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                            {
                                if (i == BUILDING_HORDE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_SOUTH_SPIRE + i, 0);
                            }
                            for (int i = 0; i < BUILDING_MAX_DIFF; i++)
                            {
                                if (i == BUILDING_HORDE_DEFENCE)
                                    SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 1);
                                else
                                    SendUpdateWorldState(WS_TB_WEST_SPIRE + i, 0);
                            }
                            break;
                    }
                }
            }

            for (uint8 team = 0; team < 2; ++team)
            {
                for (GuidSet::const_iterator itr = m_PlayersInWar[team].begin(); itr != m_PlayersInWar[team].end(); ++itr)
                {
                    if (Player* player = sObjectAccessor->FindPlayer(*itr))
                    {
                        if (endbytimer)
                        {
                            if (player->GetTeamId() == GetDefenderTeam())
                            {
                                switch (player->GetTeamId())
                                {
                                    case TEAM_ALLIANCE:
                                        player->CastSpell(player, SPELL_TB_VICTORY_REWARD_ALLIANCE, true);
                                        IncrementQuest(player, 28882, true);
                                        break;
                                    case TEAM_HORDE:
                                        player->CastSpell(player, SPELL_TB_VICTORY_REWARD_HORDE, true);
                                        IncrementQuest(player, 28884, true);
                                        break;
                                }
                                if (m_Data32[BATTLEFIELD_TB_DATA_DESTROYED] == 0)
                                    player->CastSpell(player, SPELL_TB_TOL_BARAD_TOWER_DEFENDED, true);
                            }
                            else
                            {
                                switch (player->GetTeamId())
                                {
                                    case TEAM_ALLIANCE:
                                        IncrementQuest(player, 28882, true);
                                        break;
                                    case TEAM_HORDE:
                                        IncrementQuest(player, 28884, true);
                                        break;
                                }
                                player->CastSpell(player, SPELL_TB_LOOSER_REWARD, true);
                                player->RepopAtGraveyard();
                            }
                        }
                        else
                        {
                            if (player->GetTeamId() == GetDefenderTeam() && GetDefenderTeam() == TEAM_ALLIANCE)
                                player->CastSpell(player, SPELL_TB_VICTORY_REWARD_ALLIANCE, true);

                            else if (player->GetTeamId() == GetDefenderTeam() && GetDefenderTeam() == TEAM_HORDE)
                                player->CastSpell(player, SPELL_TB_VICTORY_REWARD_HORDE, true);

                            else
                            {
                                player->CastSpell(player, SPELL_TB_LOOSER_REWARD, true);
                                player->RepopAtGraveyard();
                            }
                        }
                        if (Group* group = player->GetGroup())
                            group->RemoveMember(player->GetGUID());
                    }
                }
                m_PlayersInWar[team].clear();
            }

            m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] = 0;
            m_Data32[BATTLEFIELD_TB_DATA_DESTROYED] = 0;
}

void BattlefieldTB::FillInitialWorldStates(WorldPacket& data)
{
    data << uint32(WS_TB_BATTLE_TIMER_ENABLED) << uint32(IsWarTime() ? 1 : 0);
    data << uint32(WS_TB_BATTLE_TIMER) << uint32(IsWarTime() ? (time(NULL) + GetTimer() / 1000) : 0);
    data << uint32(WS_TB_COUNTER_BUILDINGS) << uint32(m_Data32[BATTLEFIELD_TB_DATA_CAPTURED]);
    data << uint32(WS_TB_COUNTER_BUILDINGS_ENABLED) << uint32(IsWarTime() ? 1 : 0);
    data << uint32(WS_TB_HORDE_DEFENCE) << uint32(0);
    data << uint32(WS_TB_ALLIANCE_DEFENCE) << uint32(0);
    data << uint32(WS_TB_NEXT_BATTLE_TIMER_ENABLED) << uint32(IsWarTime() ? 0 : 1);
    data << uint32(WS_TB_NEXT_BATTLE_TIMER) << uint32(!IsWarTime() ? time(NULL) + (GetTimer() / 1000) : 0);
    data << uint32(WS_TB_ALLIANCE_ATTACK) << uint32(GetAttackerTeam() == TEAM_ALLIANCE ? 1 : 0);
    data << uint32(WS_TB_HORDE_ATTACK) << uint32(GetAttackerTeam() == TEAM_HORDE ? 1 : 0);

    if (!IsWarTime())
        data << uint32(5332) << uint32(time(NULL)+(GetTimer() / 1000));
    else
        data << uint32(5332) << uint32(0);

    data << uint32(WS_TB_KEEP_HORDE_DEFENCE) << uint32(GetDefenderTeam() == TEAM_HORDE ? 1 : 0);
    data << uint32(WS_TB_KEEP_ALLIANCE_DEFENCE) << uint32(GetDefenderTeam() == TEAM_ALLIANCE ? 1 : 0);

    for (TbWorkShop::const_iterator itr = WorkShopList.begin(); itr != WorkShopList.end(); ++itr)
    {
        for (int i = 0; i < MAX_CP_DIFF; i++)
        {
            switch (i)
            {
                case ALLIANCE_DEFENCE:
                    if ((*itr)->m_State == BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_INTACT)
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                    else
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                    break;
                case HORDE_DEFENCE:
                    if ((*itr)->m_State == BATTLEFIELD_TB_OBJECTSTATE_HORDE_INTACT)
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                    else
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                    break;
                case ALLIANCE_ATTACK:
                    if ((*itr)->m_State == BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE || (*itr)->m_State == BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE)
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                    else
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                    break;
                case HORDE_ATTACK:
                    if ((*itr)->m_State == BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE || (*itr)->m_State == BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE)
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                    else
                        data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                    break;
                default:
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
            }
        }
    }

    for (TbGameObjectBuilding::const_iterator itr = BuildingsInZone.begin(); itr != BuildingsInZone.end(); ++itr)
    {
        for (int i = 0; i < BUILDING_MAX_DIFF; i++)
        {
            switch (i)
            {
            case BUILDING_HORDE_DEFENCE:
                if ((*itr)->m_State == (BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_INTACT-TEAM_HORDE*3))
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                else
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                break;
            case BUILDING_HORDE_DEFENCE_DAMAGED:
                if ((*itr)->m_State == (BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_DAMAGE-TEAM_HORDE*3))
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                else
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                break;
            case BUILDING_DESTROYED:
                if ((*itr)->m_State == BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_DESTROY-TEAM_HORDE*3)
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                else
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                break;
            case BUILDING_ALLIANCE_DEFENCE:
                if ((*itr)->m_State == (BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_INTACT-TEAM_ALLIANCE*3))
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                else
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                break;
            case BUILDING_ALLIANCE_DEFENCE_DAMAGED:
                if ((*itr)->m_State == (BATTLEFIELD_TB_OBJECTSTATE_ALLIANCE_DAMAGE-TEAM_ALLIANCE*3))
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(1);
                else
                    data << (uint32)((*itr)->m_WorldState + i) << uint32(0);
                break;
            default:
                data << (uint32)((*itr)->m_WorldState + BUILDING_DESTROYED) << uint32(1);
            }
        }
    }
}

void BattlefieldTB::SendInitWorldStatesTo(Player* player)
{
    WorldPacket data(SMSG_INIT_WORLD_STATES, (4+4+4+2+(BuildingsInZone.size()*8)+(WorkShopList.size()*8)));

    data << uint32(m_MapId);
    data << uint32(m_ZoneId);
    data << uint32(0);
    data << uint16(4+2+4+BuildingsInZone.size()+WorkShopList.size());

    FillInitialWorldStates(data);

    player->GetSession()->SendPacket(&data);
}


void BattlefieldTB::SendInitWorldStatesToAll()
{
    for (uint8 team = 0; team < 2; team++)
        for (GuidSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
            if (Player* player = sObjectAccessor->FindPlayer(*itr))
                SendInitWorldStatesTo(player);
}

void BattlefieldTB::CapturePoint(uint32 team)
{
    if (team == BATTLEFIELD_TB_TEAM_NEUTRAL)
        return;

    if (team == GetDefenderTeam() && m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] > 0)
        m_Data32[BATTLEFIELD_TB_DATA_CAPTURED]--;
    else if (team == GetAttackerTeam())
        m_Data32[BATTLEFIELD_TB_DATA_CAPTURED]++;

    if (m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] < 0)
        m_Data32[BATTLEFIELD_TB_DATA_CAPTURED] = 0;

    SendUpdateWorldState(WS_TB_COUNTER_BUILDINGS, m_Data32[BATTLEFIELD_TB_DATA_CAPTURED]);
}

void BattlefieldTB::OnDestroyed()
{
    for(uint8 team = 0; team < 2; team++)
        for (GuidSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
            if (Player* player = sObjectAccessor->FindPlayer(*itr))
                if (player->GetTeamId() == GetAttackerTeam())
                {
                    player->CastSpell(player, SPELL_TOWER_BONUS, true);
                    player->CastSpell(player, SPELL_TB_TOL_BARAD_TOWER_DESTROYED, true);
                }
}

void BattlefieldTB::OnDamaged()
{
    for (uint8 team = 0; team < 2; team++)
        for (GuidSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
            if (Player* player = sObjectAccessor->FindPlayer(*itr))
                if (player->GetTeamId() == GetAttackerTeam())
                    player->CastSpell(player, SPELL_TB_TOL_BARAD_TOWER_DAMAGED, true);
}

void BattlefieldTB::OnPlayerEnterZone(Player* player)
{
    if (!m_isActive)
    {
        player->RemoveAurasDueToSpell(SPELL_VETERAN);
        player->RemoveAurasDueToSpell(SPELL_TB_SPIRITUAL_IMMUNITY);
        player->RemoveAurasDueToSpell(SPELL_TOWER_BONUS);
    }

    // Send worldstate to player
    SendInitWorldStatesTo(player);
    //UpdateAllWorldStates();
}

void BattlefieldTB::ProcessEvent(WorldObject *obj, uint32 eventId)
{
    if (!obj || !IsWarTime())
        return;

    //if destroy or damage event, search the wall/tower and update worldstate/send warning message
    for (TbGameObjectBuilding::const_iterator itr = BuildingsInZone.begin(); itr != BuildingsInZone.end(); ++itr)
    {
        if (obj->GetEntry()==(*itr)->m_Build->GetEntry())
        {
            if ((*itr)->m_Build->GetGOInfo()->building.damagedEvent==eventId)
                (*itr)->Damaged();

            if ((*itr)->m_Build->GetGOInfo()->building.destroyedEvent==eventId)
                (*itr)->Destroyed();

            break;
        }
    }
}

void BattlefieldTB::OnStartGrouping()
{
    SendWarningToAllInZone(BATTLEFIELD_TB_TEXT_WILL_START);
}

void BattlefieldTB::AddDamagedTower(TeamId team)
{
}

void BattlefieldTB::BrokenWallOrTower(TeamId team)
{
}

void BattlefieldTB::AddBrokenTower(TeamId team)
{
}

void BfCapturePointTB::ChangeTeam(TeamId /*oldTeam*/)
{
    m_WorkShop->ChangeControl(m_team,false);
}

BfCapturePointTB::BfCapturePointTB(BattlefieldTB *bf,TeamId control) : BfCapturePoint(bf)
{
    m_Bf = bf;
    m_team = control;
}

BfGraveYardTB::BfGraveYardTB(BattlefieldTB* battlefield) : BfGraveyard(battlefield)
{
    m_Bf = battlefield;
}
