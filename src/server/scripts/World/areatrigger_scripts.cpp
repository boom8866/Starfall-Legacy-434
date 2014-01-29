/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Areatrigger_Scripts
SD%Complete: 100
SDComment: Scripts for areatriggers
SDCategory: Areatrigger
EndScriptData */

/* ContentData
at_coilfang_waterfall           4591
at_legion_teleporter            4560 Teleporter TO Invasion Point: Cataclysm
at_stormwright_shelf            q12741
at_last_rites                   q12019
at_sholazar_waygate             q12548
at_nats_landing                 q11209
at_bring_your_orphan_to         q910 q910 q1800 q1479 q1687 q1558 q10951 q10952
at_brewfest
at_area_52_entrance
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"

/*######
## at_coilfang_waterfall
######*/

enum eCoilfangGOs
{
    GO_COILFANG_WATERFALL   = 184212
};

class AreaTrigger_at_coilfang_waterfall : public AreaTriggerScript
{
    public:

        AreaTrigger_at_coilfang_waterfall()
            : AreaTriggerScript("at_coilfang_waterfall")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (GameObject* go = GetClosestGameObjectWithEntry(player, GO_COILFANG_WATERFALL, 35.0f))
                if (go->getLootState() == GO_READY)
                    go->UseDoorOrButton();

            return false;
        }
};

/*#####
## at_legion_teleporter
#####*/

enum eLegionTeleporter
{
    SPELL_TELE_A_TO         = 37387,
    QUEST_GAINING_ACCESS_A  = 10589,

    SPELL_TELE_H_TO         = 37389,
    QUEST_GAINING_ACCESS_H  = 10604
};

class AreaTrigger_at_legion_teleporter : public AreaTriggerScript
{
    public:

        AreaTrigger_at_legion_teleporter()
            : AreaTriggerScript("at_legion_teleporter")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (player->isAlive() && !player->isInCombat())
            {
                if (player->GetTeam() == ALLIANCE && player->GetQuestRewardStatus(QUEST_GAINING_ACCESS_A))
                {
                    player->CastSpell(player, SPELL_TELE_A_TO, false);
                    return true;
                }

                if (player->GetTeam() == HORDE && player->GetQuestRewardStatus(QUEST_GAINING_ACCESS_H))
                {
                    player->CastSpell(player, SPELL_TELE_H_TO, false);
                    return true;
                }

                return false;
            }
            return false;
        }
};

/*######
## at_stormwright_shelf
######*/

enum eStormwrightShelf
{
    QUEST_STRENGTH_OF_THE_TEMPEST               = 12741,

    SPELL_CREATE_TRUE_POWER_OF_THE_TEMPEST      = 53067
};

class AreaTrigger_at_stormwright_shelf : public AreaTriggerScript
{
    public:

        AreaTrigger_at_stormwright_shelf()
            : AreaTriggerScript("at_stormwright_shelf")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_STRENGTH_OF_THE_TEMPEST) == QUEST_STATUS_INCOMPLETE)
                player->CastSpell(player, SPELL_CREATE_TRUE_POWER_OF_THE_TEMPEST, false);

            return true;
        }
};

/*######
## at_scent_larkorwi
######*/

enum eScentLarkorwi
{
    QUEST_SCENT_OF_LARKORWI                     = 4291,
    NPC_LARKORWI_MATE                           = 9683
};

class AreaTrigger_at_scent_larkorwi : public AreaTriggerScript
{
    public:

        AreaTrigger_at_scent_larkorwi()
            : AreaTriggerScript("at_scent_larkorwi")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_SCENT_OF_LARKORWI) == QUEST_STATUS_INCOMPLETE)
            {
                if (!player->FindNearestCreature(NPC_LARKORWI_MATE, 15))
                    player->SummonCreature(NPC_LARKORWI_MATE, player->GetPositionX()+5, player->GetPositionY(), player->GetPositionZ(), 3.3f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000);
            }

            return false;
        }
};

/*#####
## at_last_rites
#####*/

enum eAtLastRites
{
    QUEST_LAST_RITES                          = 12019,
    QUEST_BREAKING_THROUGH                    = 11898,
};

class AreaTrigger_at_last_rites : public AreaTriggerScript
{
    public:

        AreaTrigger_at_last_rites()
            : AreaTriggerScript("at_last_rites")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!(player->GetQuestStatus(QUEST_LAST_RITES) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_LAST_RITES) == QUEST_STATUS_COMPLETE ||
                player->GetQuestStatus(QUEST_BREAKING_THROUGH) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_BREAKING_THROUGH) == QUEST_STATUS_COMPLETE))
                return false;

            WorldLocation pPosition;

            switch (trigger->id)
            {
                case 5332:
                case 5338:
                    pPosition = WorldLocation(571, 3733.68f, 3563.25f, 290.812f, 3.665192f);
                    break;
                case 5334:
                    pPosition = WorldLocation(571, 3802.38f, 3585.95f, 49.5765f, 0.0f);
                    break;
                case 5340:
                    pPosition = WorldLocation(571, 3687.91f, 3577.28f, 473.342f, 0.0f);
                    break;
                default:
                    return false;
            }

            player->TeleportTo(pPosition);

            return false;
        }
};

/*######
## at_sholazar_waygate
######*/

enum eWaygate
{
    SPELL_SHOLAZAR_TO_UNGORO_TELEPORT           = 52056,
    SPELL_UNGORO_TO_SHOLAZAR_TELEPORT           = 52057,

    AT_SHOLAZAR                                 = 5046,
    AT_UNGORO                                   = 5047,

    QUEST_THE_MAKERS_OVERLOOK                   = 12613,
    QUEST_THE_MAKERS_PERCH                      = 12559,
    QUEST_MEETING_A_GREAT_ONE                   = 13956,
};

class AreaTrigger_at_sholazar_waygate : public AreaTriggerScript
{
    public:

        AreaTrigger_at_sholazar_waygate() : AreaTriggerScript("at_sholazar_waygate") {}

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && (player->GetQuestStatus(QUEST_MEETING_A_GREAT_ONE) != QUEST_STATUS_NONE ||
                (player->GetQuestStatus(QUEST_THE_MAKERS_OVERLOOK) == QUEST_STATUS_REWARDED && player->GetQuestStatus(QUEST_THE_MAKERS_PERCH) == QUEST_STATUS_REWARDED)))
            {
                switch (trigger->id)
                {
                    case AT_SHOLAZAR:
                        player->CastSpell(player, SPELL_SHOLAZAR_TO_UNGORO_TELEPORT, false);
                        break;

                    case AT_UNGORO:
                        player->CastSpell(player, SPELL_UNGORO_TO_SHOLAZAR_TELEPORT, false);
                        break;
                }
            }

            return false;
        }
};

/*######
## at_nats_landing
######*/

enum NatsLanding
{
    QUEST_NATS_BARGAIN = 11209,
    SPELL_FISH_PASTE   = 42644,
    NPC_LURKING_SHARK  = 23928
};

class AreaTrigger_at_nats_landing : public AreaTriggerScript
{
    public:
        AreaTrigger_at_nats_landing() : AreaTriggerScript("at_nats_landing") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (!player->isAlive() || !player->HasAura(SPELL_FISH_PASTE))
                return false;

            if (player->GetQuestStatus(QUEST_NATS_BARGAIN) == QUEST_STATUS_INCOMPLETE)
            {
                if (!player->FindNearestCreature(NPC_LURKING_SHARK, 20.0f))
                {
                    if (Creature* shark = player->SummonCreature(NPC_LURKING_SHARK, -4246.243f, -3922.356f, -7.488f, 5.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
                        shark->AI()->AttackStart(player);

                    return false;
                }
            }
            return true;
        }
};

/*######
## at_brewfest
######*/

enum Brewfest
{
    NPC_TAPPER_SWINDLEKEG       = 24711,
    NPC_IPFELKOFER_IRONKEG      = 24710,

    AT_BREWFEST_DUROTAR         = 4829,
    AT_BREWFEST_DUN_MOROGH      = 4820,

    SAY_WELCOME                 = 4,

    AREATRIGGER_TALK_COOLDOWN   = 5, // in seconds
};

class AreaTrigger_at_brewfest : public AreaTriggerScript
{
    public:
        AreaTrigger_at_brewfest() : AreaTriggerScript("at_brewfest")
        {
            // Initialize for cooldown
            _triggerTimes[AT_BREWFEST_DUROTAR] = _triggerTimes[AT_BREWFEST_DUN_MOROGH] = 0;
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            uint32 triggerId = trigger->id;
            // Second trigger happened too early after first, skip for now
            if (sWorld->GetGameTime() - _triggerTimes[triggerId] < AREATRIGGER_TALK_COOLDOWN)
                return false;

            switch (triggerId)
            {
                case AT_BREWFEST_DUROTAR:
                    if (Creature* tapper = player->FindNearestCreature(NPC_TAPPER_SWINDLEKEG, 20.0f))
                        tapper->AI()->Talk(SAY_WELCOME, player->GetGUID());
                    break;
                case AT_BREWFEST_DUN_MOROGH:
                    if (Creature* ipfelkofer = player->FindNearestCreature(NPC_IPFELKOFER_IRONKEG, 20.0f))
                        ipfelkofer->AI()->Talk(SAY_WELCOME, player->GetGUID());
                    break;
                default:
                    break;
            }

            _triggerTimes[triggerId] = sWorld->GetGameTime();
            return false;
        }

    private:
        std::map<uint32, time_t> _triggerTimes;
};

/*######
## at_area_52_entrance
######*/

enum Area52Entrance
{
    SPELL_A52_NEURALYZER  = 34400,
    NPC_SPOTLIGHT         = 19913,
    SUMMON_COOLDOWN       = 5,

    AT_AREA_52_SOUTH      = 4472,
    AT_AREA_52_NORTH      = 4466,
    AT_AREA_52_WEST       = 4471,
    AT_AREA_52_EAST       = 4422,
};

class AreaTrigger_at_area_52_entrance : public AreaTriggerScript
{
    public:
        AreaTrigger_at_area_52_entrance() : AreaTriggerScript("at_area_52_entrance")
        {
            _triggerTimes[AT_AREA_52_SOUTH] = _triggerTimes[AT_AREA_52_NORTH] = _triggerTimes[AT_AREA_52_WEST] = _triggerTimes[AT_AREA_52_EAST] = 0;
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            float x = 0.0f, y = 0.0f, z = 0.0f;

            if (!player->isAlive())
                return false;

            uint32 triggerId = trigger->id;
            if (sWorld->GetGameTime() - _triggerTimes[trigger->id] < SUMMON_COOLDOWN)
                return false;

            switch (triggerId)
            {
                case AT_AREA_52_EAST:
                    x = 3044.176f;
                    y = 3610.692f;
                    z = 143.61f;
                    break;
                case AT_AREA_52_NORTH:
                    x = 3114.87f;
                    y = 3687.619f;
                    z = 143.62f;
                    break;
                case AT_AREA_52_WEST:
                    x = 3017.79f;
                    y = 3746.806f;
                    z = 144.27f;
                    break;
                case AT_AREA_52_SOUTH:
                    x = 2950.63f;
                    y = 3719.905f;
                    z = 143.33f;
                    break;
            }

            player->SummonCreature(NPC_SPOTLIGHT, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 5000);
            player->AddAura(SPELL_A52_NEURALYZER, player);
            _triggerTimes[trigger->id] = sWorld->GetGameTime();
            return false;
        }

    private:
        std::map<uint32, time_t> _triggerTimes;
};

/*######
 ## at_frostgrips_hollow
 ######*/

enum FrostgripsHollow
{
    QUEST_THE_LONESOME_WATCHER      = 12877,

    NPC_STORMFORGED_MONITOR         = 29862,
    NPC_STORMFORGED_ERADICTOR       = 29861,

    TYPE_WAYPOINT                   = 0,
    DATA_START                      = 0
};

Position const stormforgedMonitorPosition = {6963.95f, 45.65f, 818.71f, 4.948f};
Position const stormforgedEradictorPosition = {6983.18f, 7.15f, 806.33f, 2.228f};

class AreaTrigger_at_frostgrips_hollow : public AreaTriggerScript
{
public:
    AreaTrigger_at_frostgrips_hollow() : AreaTriggerScript("at_frostgrips_hollow")
    {
        stormforgedMonitorGUID = 0;
        stormforgedEradictorGUID = 0;
    }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /* trigger */)
    {
        if (player->GetQuestStatus(QUEST_THE_LONESOME_WATCHER) != QUEST_STATUS_INCOMPLETE)
            return false;

        Creature* stormforgedMonitor = Creature::GetCreature(*player, stormforgedMonitorGUID);
        if (stormforgedMonitor)
            return false;

        Creature* stormforgedEradictor = Creature::GetCreature(*player, stormforgedEradictorGUID);
        if (stormforgedEradictor)
            return false;

        stormforgedMonitor = player->SummonCreature(NPC_STORMFORGED_MONITOR, stormforgedMonitorPosition, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
        if (stormforgedMonitor)
        {
            stormforgedMonitorGUID = stormforgedMonitor->GetGUID();
            stormforgedMonitor->SetWalk(false);
            /// The npc would search an alternative way to get to the last waypoint without this unit state.
            stormforgedMonitor->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            stormforgedMonitor->GetMotionMaster()->MovePath(NPC_STORMFORGED_MONITOR * 100, false);
        }

        stormforgedEradictor = player->SummonCreature(NPC_STORMFORGED_ERADICTOR, stormforgedEradictorPosition, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
        if (stormforgedEradictor)
        {
            stormforgedEradictorGUID = stormforgedEradictor->GetGUID();
            stormforgedEradictor->GetMotionMaster()->MovePath(NPC_STORMFORGED_ERADICTOR * 100, false);
        }

        return true;
    }

private:
    uint64 stormforgedMonitorGUID;
    uint64 stormforgedEradictorGUID;
};

class AreaTrigger_at_raptor_pens : public AreaTriggerScript
{
    public:
        AreaTrigger_at_raptor_pens() : AreaTriggerScript("at_raptor_pens") { }

        enum Id
        {
            NPC_SWIFTCLAW                       = 37989,
            QUEST_YOUNG_AND_VICIOUS             = 24626,
            QUEST_CREDIT_SWIFTCLAW_ESCORTED     = 38002
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive() && player->GetVehicleBase())
            {
                if (player->GetQuestStatus(QUEST_YOUNG_AND_VICIOUS) == QUEST_STATUS_INCOMPLETE)
                {
                    player->KilledMonsterCredit(QUEST_CREDIT_SWIFTCLAW_ESCORTED);
                    player->_ExitVehicle();
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_caravan_scene : public AreaTriggerScript
{
    public:
        Areatrigger_at_caravan_scene() : AreaTriggerScript("at_caravan_scene") { }

        enum Id
        {
            QUEST_INVESTIGATE_THE_WRECKAGE      = 14066
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_INVESTIGATE_THE_WRECKAGE) == QUEST_STATUS_INCOMPLETE)
                    player->CompleteQuest(QUEST_INVESTIGATE_THE_WRECKAGE);
                return true;
            }
            return false;
        }
};

class Areatrigger_at_horatio_laine_1 : public AreaTriggerScript
{
    public:
        Areatrigger_at_horatio_laine_1() : AreaTriggerScript("at_horatio_laine_1") { }

        enum Id
        {
            // Quest
            QUEST_HERO_CALL_WESTFALL_1      = 26378,
            QUEST_HERO_CALL_WESTFALL_2      = 28562,
            QUEST_FURLBROW_DEED             = 184,

            // NPC Entry
            NPC_ENTRY_INVESTIGATOR          = 42309,
            NPC_ENTRY_HORATIO               = 42308,
            NPC_ENTRY_TRANSIENT             = 42383,
            NPC_ENTRY_WEST_PLAIN_DRIFTER    = 42391,
            NPC_ENTRY_ALARM_O_BOT           = 42311,

            // GUID
            NPC_GUID_INVESTIGATOR_1         = 171544,
            NPC_GUID_INVESTIGATOR_2         = 171567,
            NPC_GUID_ALARM_O_BOT            = 171566,

            // Spell
            SPELL_TRIGGER_GOGGLES           = 78935
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_HERO_CALL_WESTFALL_1) == QUEST_STATUS_COMPLETE ||
                    player->GetQuestStatus(QUEST_HERO_CALL_WESTFALL_2) == QUEST_STATUS_COMPLETE ||
                    player->GetQuestStatus(QUEST_FURLBROW_DEED) == QUEST_STATUS_COMPLETE)
                {
                    std::list<Creature*> alarmobot;
                    GetCreatureListWithEntryInGrid(alarmobot, player, NPC_ENTRY_ALARM_O_BOT, 200.0f);
                    if (alarmobot.empty())
                        return false;

                    for (std::list<Creature*>::iterator itr = alarmobot.begin(); itr != alarmobot.end(); ++itr)
                    {
                        if ((*itr)->GetGUIDLow() == NPC_GUID_ALARM_O_BOT && !(*itr)->isAlive())
                            return false;

                        if ((*itr)->GetGUIDLow() == NPC_GUID_ALARM_O_BOT && (*itr)->isAlive())
                            (*itr)->DespawnOrUnsummon(1);
                    }

                    std::list<Creature*> investigators;
                    GetCreatureListWithEntryInGrid(investigators, player, NPC_ENTRY_INVESTIGATOR, 20.0f);
                    if (investigators.empty())
                        return false;

                    for (std::list<Creature*>::iterator itr = investigators.begin(); itr != investigators.end(); ++itr)
                    {
                        if ((*itr)->isAlive())
                        {
                            (*itr)->AI()->EnterEvadeMode();

                            if ((*itr)->GetGUIDLow() == NPC_GUID_INVESTIGATOR_1)
                            {
                                (*itr)->AI()->TalkWithDelay(3000, 0);
                                (*itr)->AI()->TalkWithDelay(9000, 1);
                            }
                            if ((*itr)->GetGUIDLow() == NPC_GUID_INVESTIGATOR_2)
                                (*itr)->AI()->TalkWithDelay(15000, 2);
                        }
                    }
                    if (Creature* horatioLaine = player->FindNearestCreature(NPC_ENTRY_HORATIO, 50.0f, true))
                    {
                        horatioLaine->RemoveAurasDueToSpell(SPELL_TRIGGER_GOGGLES);
                        horatioLaine->SetStandState(UNIT_STAND_STATE_KNEEL);
                        horatioLaine->AI()->Reset();
                        horatioLaine->AI()->EnterEvadeMode();
                        horatioLaine->AI()->TalkWithDelay(20000, 0);
                        horatioLaine->CastWithDelay(22500, horatioLaine, SPELL_TRIGGER_GOGGLES);
                        horatioLaine->AI()->TalkWithDelay(26000, 1);
                        horatioLaine->AI()->TalkWithDelay(32000, 2);
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_thug_scene : public AreaTriggerScript
{
    public:
        Areatrigger_at_thug_scene() : AreaTriggerScript("at_thug_scene") { }

        enum Id
        {
            // Quest
            QUEST_LOU_PARTING_THOUGHTS      = 26232,

            // NPC Entry
            NPC_ENTRY_THUG                 = 42387,

            // GUID
            NPC_GUID_THUG_1                = 171890,
            NPC_GUID_THUG_2                = 171891,
            NPC_GUID_THUG_3                = 171892,

            // Spell
            SPELL_TRIGGER                  = 70290
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_LOU_PARTING_THOUGHTS) == QUEST_STATUS_INCOMPLETE)
                {
                    std::list<Creature*> thugs;
                    GetCreatureListWithEntryInGrid(thugs, player, NPC_ENTRY_THUG, 20.0f);
                    if (thugs.empty())
                        return false;

                    for (std::list<Creature*>::iterator itr = thugs.begin(); itr != thugs.end(); ++itr)
                    {
                        if ((*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            return false;

                        (*itr)->setFaction(15);

                        if (!(*itr)->isAlive())
                        {
                            (*itr)->Respawn(true);
                            (*itr)->AI()->EnterEvadeMode();
                        }

                        (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                        if ((*itr)->isAlive())
                        {
                            if ((*itr)->GetGUIDLow() == NPC_GUID_THUG_1)
                            {
                                (*itr)->AI()->TalkWithDelay(1000, 0);
                                (*itr)->AI()->TalkWithDelay(21000, 4);
                                (*itr)->AI()->TalkWithDelay(26000, 5);
                                (*itr)->AI()->TalkWithDelay(31000, 6);
                                (*itr)->CastWithDelay(31500, (*itr), SPELL_TRIGGER);
                            }
                            if ((*itr)->GetGUIDLow() == NPC_GUID_THUG_2)
                            {
                                (*itr)->AI()->TalkWithDelay(6000, 1);
                                (*itr)->AI()->TalkWithDelay(11000, 2);
                            }
                            if ((*itr)->GetGUIDLow() == NPC_GUID_THUG_3)
                                (*itr)->AI()->TalkWithDelay(16000, 3);
                        }
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_horatio_laine_2 : public AreaTriggerScript
{
    public:
        Areatrigger_at_horatio_laine_2() : AreaTriggerScript("at_horatio_laine_2") { }

        enum Id
        {
            // Quest
            QUEST_LOU_PARTING_THOUGHTS      = 26232,

            // NPC Entry
            NPC_ENTRY_THUG                 = 42387,
            NPC_ENTRY_INVESTIGATOR         = 42559,
            NPC_ENTRY_HORATIO              = 42558,
            NPC_ENTRY_HOMELESS_CITIZEN     = 42384,

            // GUID
            NPC_GUID_INVESTIGATOR_1        = 770856,
            NPC_GUID_INVESTIGATOR_2        = 770853,

            // Spell
            SPELL_TRIGGER_GOGGLES          = 78935
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_LOU_PARTING_THOUGHTS) == QUEST_STATUS_COMPLETE)
                {
                    std::list<Creature*> thugs;
                    GetCreatureListWithEntryInGrid(thugs, player, NPC_ENTRY_THUG, 150.0f);
                    if (thugs.empty())
                        return false;

                    for (std::list<Creature*>::iterator itr = thugs.begin(); itr != thugs.end(); ++itr)
                    {
                        if ((*itr)->isAlive())
                            return false;

                        (*itr)->Respawn(true);
                        (*itr)->AI()->EnterEvadeMode();
                    }

                    std::list<Creature*> investigators;
                    GetCreatureListWithEntryInGrid(investigators, player, NPC_ENTRY_INVESTIGATOR, 20.0f);
                    if (investigators.empty())
                        return false;

                    for (std::list<Creature*>::iterator itr = investigators.begin(); itr != investigators.end(); ++itr)
                    {
                        if ((*itr)->isAlive())
                        {
                            if ((*itr)->GetGUIDLow() == NPC_GUID_INVESTIGATOR_1)
                                (*itr)->AI()->TalkWithDelay(2000, 0);
                            if ((*itr)->GetGUIDLow() == NPC_GUID_INVESTIGATOR_2)
                                (*itr)->AI()->TalkWithDelay(13000, 1);
                        }
                    }
                    if (Creature* horatioLaine = player->FindNearestCreature(NPC_ENTRY_HORATIO, 50.0f, true))
                    {
                        horatioLaine->AI()->TalkWithDelay(18000, 0);
                        horatioLaine->AI()->TalkWithDelay(23000, 1);
                        horatioLaine->AI()->TalkWithDelay(28000, 2);
                        horatioLaine->CastWithDelay(29000, horatioLaine, SPELL_TRIGGER_GOGGLES);
                        horatioLaine->AI()->TalkWithDelay(33000, 3);
                        horatioLaine->AI()->TalkWithDelay(38000, 4);
                    }
                    if (Creature* homelessCitizen = player->FindNearestCreature(NPC_ENTRY_HOMELESS_CITIZEN, 25.0f, true))
                        homelessCitizen->AI()->TalkWithDelay(7000, 8);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_moonbrook_event : public AreaTriggerScript
{
    public:
        Areatrigger_at_moonbrook_event() : AreaTriggerScript("at_moonbrook_event") { }

        enum Id
        {
            // Quest
            QUEST_THE_DAWNING_OF_A_NEW_DAY  = 26297,

            // NPC
            NPC_ENTRY_SHADOWY_FIGURE        = 42680,
            NPC_ENTRY_HOMELESS_CITIZEN      = 42386,

            // Spell
            SPELL_TRIGGER_QUEST_FINISH      = 78935
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_THE_DAWNING_OF_A_NEW_DAY) == QUEST_STATUS_INCOMPLETE)
                {
                    Creature* shadowyFigure = player->FindNearestCreature(NPC_ENTRY_SHADOWY_FIGURE, 50.0f, true);
                    if (shadowyFigure)
                    {
                        if (shadowyFigure->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            return false;

                        shadowyFigure->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        shadowyFigure->AI()->TalkWithDelay(2000, 0);
                        shadowyFigure->AI()->TalkWithDelay(10000, 1);
                        shadowyFigure->AI()->TalkWithDelay(18000, 2);
                        shadowyFigure->AI()->TalkWithDelay(26000, 3);
                        shadowyFigure->AI()->TalkWithDelay(32000, 4);
                        shadowyFigure->AI()->TalkWithDelay(40000, 5);
                        shadowyFigure->AI()->TalkWithDelay(48000, 6);
                        shadowyFigure->AI()->TalkWithDelay(56000, 7);
                        shadowyFigure->CastWithDelay(60000, shadowyFigure, SPELL_TRIGGER_QUEST_FINISH);
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_mortwake_event : public AreaTriggerScript
{
    public:
        Areatrigger_at_mortwake_event() : AreaTriggerScript("at_mortwake_event") { }

        enum Id
        {
            // Quest
            QUEST_SECRETS_OF_THE_TOWER      = 26290,

            // NPC
            NPC_ENTRY_SHADOWY_FIGURE        = 42662,
            NPC_ENTRY_HELIX_GEARBREAKER     = 42655,

            // Spell
            SPELL_TRIGGER_QUEST_FINISH      = 78935,
            SPELL_POTION_OF_SHROUDING       = 79528
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_SECRETS_OF_THE_TOWER) == QUEST_STATUS_INCOMPLETE)
                {
                    Creature* shadowyFigure = player->FindNearestCreature(NPC_ENTRY_SHADOWY_FIGURE, 50.0f, true);
                    Creature* helixGearbreaker = player->FindNearestCreature(NPC_ENTRY_HELIX_GEARBREAKER, 50.0f, true);
                    if (shadowyFigure)
                    {
                        if (!player->HasAura(SPELL_POTION_OF_SHROUDING))
                            return false;

                        if (shadowyFigure->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                            return false;

                        shadowyFigure->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                        shadowyFigure->AI()->TalkWithDelay(7000, 6);
                        shadowyFigure->AI()->TalkWithDelay(16000, 7);
                        shadowyFigure->AI()->TalkWithDelay(25000, 8);
                        shadowyFigure->AI()->TalkWithDelay(31000, 9);
                        shadowyFigure->AI()->TalkWithDelay(41000, 10);
                        shadowyFigure->CastWithDelay(43500, shadowyFigure, SPELL_TRIGGER_QUEST_FINISH);
                    }
                    if (helixGearbreaker)
                    {
                        helixGearbreaker->AI()->TalkWithDelay(2000, 0);
                        helixGearbreaker->AI()->TalkWithDelay(12000, 1);
                        helixGearbreaker->AI()->TalkWithDelay(21000, 2);
                        helixGearbreaker->AI()->TalkWithDelay(36000, 3);
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_addle_stead_event : public AreaTriggerScript
{
    public:
        Areatrigger_at_addle_stead_event() : AreaTriggerScript("at_addle_stead_event") { }

        enum Id
        {
            // Quest
            QUEST_A_CURSE_WE_CANNOT_LIFT    = 26720,

            // NPC
            NPC_ENTRY_LURKING_WORGEN        = 43814,

            // Spell
            SPELL_STUNNING_POUNCE           = 81957
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_A_CURSE_WE_CANNOT_LIFT) == QUEST_STATUS_INCOMPLETE)
                {
                    Creature* lurkingWorgen = player->FindNearestCreature(NPC_ENTRY_LURKING_WORGEN, 100.0f, true);
                    if (!lurkingWorgen)
                        player->SummonCreature(NPC_ENTRY_LURKING_WORGEN, -11025.79f, 251.42f, 32.90f, 3.28f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if (lurkingWorgen)
                        lurkingWorgen->CastWithDelay(3000, player, SPELL_STUNNING_POUNCE, true);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_ruins_of_aboraz : public AreaTriggerScript
{
    public:
        Areatrigger_at_ruins_of_aboraz() : AreaTriggerScript("at_ruins_of_aboraz") { }

        enum Id
        {
            // Quest
            QUEST_BACKDOOR_DEALINGS_H       = 26550,
            QUEST_BACKDOOR_DEALINGS_A       = 26809,
            QUEST_ELIMINATE_THE_OUTCAST_H   = 26551,
            QUEST_ELIMINATE_THE_OUTCAST_A   = 26810,

            // NPC
            NPC_ENTRY_ZANZIL_THE_OUTCAST        = 43245,
            NPC_ENTRY_SHADE_OF_THE_HEXXER       = 43246,
            NPC_ENTRY_TRIGGER_EVENT             = 41200,

            // GameObject
            GO_ENTRY_ZANZIL_PORTAL              = 204372
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_BACKDOOR_DEALINGS_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_BACKDOOR_DEALINGS_A) == QUEST_STATUS_INCOMPLETE)
                {
                    // You should have the vehicle
                    if (!player->GetVehicle())
                        return false;

                    Creature* triggerAlive = player->FindNearestCreature(NPC_ENTRY_TRIGGER_EVENT, 100.0f, true);
                    Creature* triggerDead = player->FindNearestCreature(NPC_ENTRY_TRIGGER_EVENT, 100.0f, false);
                    Creature* zanzil = player->FindNearestCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, 100.0f, true);
                    Creature* hexxer = player->FindNearestCreature(NPC_ENTRY_SHADE_OF_THE_HEXXER, 100.0f, true);

                    // Event is in progress!
                    if (triggerDead && hexxer)
                        return false;

                    // Event is done but trigger is dead -> Respawn
                    if (triggerDead && !hexxer)
                        triggerDead->Respawn(true);

                    // Flag event in progress!
                    if (triggerAlive)
                        triggerAlive->DespawnOrUnsummon(1);

                    player->SummonCreature(NPC_ENTRY_SHADE_OF_THE_HEXXER, -13663.66f, -307.55f, 8.17f, 0.83f, TEMPSUMMON_MANUAL_DESPAWN);
                    player->SummonCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, -13657.80f, -300.60f, 8.17f, 3.96f, TEMPSUMMON_MANUAL_DESPAWN);

                    // Zanzil dialogs
                    if (Creature* zanzil = player->FindNearestCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, 100.0f, true))
                    {
                        zanzil->AI()->TalkWithDelay(15000, 0);
                        zanzil->AI()->TalkWithDelay(21000, 1);
                        zanzil->AI()->TalkWithDelay(39000, 2);
                        zanzil->AI()->TalkWithDelay(57000, 3);
                        zanzil->AI()->TalkWithDelay(63000, 4);

                        // Despawn
                        zanzil->DespawnOrUnsummon(70000);
                    }
                    // Hexxer dialogs
                    if (Creature* hexxer = player->FindNearestCreature(NPC_ENTRY_SHADE_OF_THE_HEXXER, 100.0f, true))
                    {
                        hexxer->AI()->TalkWithDelay(27000, 0);
                        hexxer->AI()->TalkWithDelay(33000, 1);
                        hexxer->AI()->TalkWithDelay(45000, 2);
                        hexxer->AI()->TalkWithDelay(51000, 3);

                        // Despawn
                        hexxer->DespawnOrUnsummon(70000);
                    }
                }
                if (player->GetQuestStatus(QUEST_ELIMINATE_THE_OUTCAST_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_ELIMINATE_THE_OUTCAST_A) == QUEST_STATUS_INCOMPLETE)
                {
                    Creature* zanzil = player->FindNearestCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, 100.0f, true);
                    if (zanzil)
                        return false;

                    player->SummonCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, -13679.94f, -306.29f, 8,14, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    if (Creature* zanzil = player->FindNearestCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, 100.0f, true))
                    {
                        zanzil->setFaction(14);
                        if (player && player->isAlive())
                            zanzil->Attack(player, true);
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_jeklik_zanzil : public AreaTriggerScript
{
    public:
        Areatrigger_at_jeklik_zanzil() : AreaTriggerScript("at_jeklik_zanzil") { }

        enum Id
        {
            // Quest
            QUEST_HIGH_PRIESTESS_JEKLIK_H       = 26553,
            QUEST_HIGH_PRIESTESS_JEKLIK_A       = 26812,

            // NPC
            NPC_ENTRY_ZANZIL_THE_OUTCAST        = 43255,
            NPC_ENTRY_HIGH_PRIESTESS_JEKLIK     = 43257
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_HIGH_PRIESTESS_JEKLIK_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_HIGH_PRIESTESS_JEKLIK_A) == QUEST_STATUS_INCOMPLETE)
                {
                    Creature* jeklik = player->FindNearestCreature(NPC_ENTRY_HIGH_PRIESTESS_JEKLIK, 200, true);
                    Creature* zanzil = player->FindNearestCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, 200, true);
                    if (jeklik || zanzil)
                        return false;

                    player->SummonCreature(NPC_ENTRY_HIGH_PRIESTESS_JEKLIK, -12219.59f, -1464.73f, 131.69f, 1.50f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    player->SummonCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, -12219.22f, -1455.75f, 130.59f, 4.58f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_venoxis_event : public AreaTriggerScript
{
    public:
        Areatrigger_at_venoxis_event() : AreaTriggerScript("at_venoxis_event") { }

        enum Id
        {
            // Quest
            QUEST_HIGH_PRIEST_VENOXIS_H         = 26555,
            QUEST_HIGH_PRIEST_VENOXIS_A         = 26814,

            // NPC
            NPC_ENTRY_ZANZIL_THE_OUTCAST        = 43322,
            NPC_ENTRY_HIGH_PRIEST_VENOXIS       = 43323
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->GetQuestStatus(QUEST_HIGH_PRIEST_VENOXIS_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_HIGH_PRIEST_VENOXIS_A) == QUEST_STATUS_INCOMPLETE)
                {
                    Creature* venoxis = player->FindNearestCreature(NPC_ENTRY_HIGH_PRIEST_VENOXIS, 200, true);
                    Creature* zanzil = player->FindNearestCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, 200, true);
                    if (venoxis || zanzil)
                        return false;

                    player->SummonCreature(NPC_ENTRY_HIGH_PRIEST_VENOXIS, -12028.50f, -1705.92f, 41.97f, 3.67f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000);
                    player->SummonCreature(NPC_ENTRY_ZANZIL_THE_OUTCAST, -12024.13f, -1709.33f, 39.31f, 2.04f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180000);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_ironband_caravan : public AreaTriggerScript
{
    public:
        Areatrigger_at_ironband_caravan() : AreaTriggerScript("at_ironband_caravan") { }

        enum Id
        {
            // Quest
            QUEST_PROTECTING_THE_SHIPMENT         = 309,

            // NPC
            NPC_ENTRY_HULDAR                    = 2057,
            NPC_ENTRY_MIRAN                     = 1379,
            NPC_ENTRY_DARK_IRON_RAIDER          = 2149
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_PROTECTING_THE_SHIPMENT))
                {
                    Creature* huldar = player->FindNearestCreature(NPC_ENTRY_HULDAR, 30.0f, true);
                    Creature* miran = player->FindNearestCreature(NPC_ENTRY_MIRAN, 30.0f, true);
                    if (!huldar || !miran)
                        return false;

                    if (miran->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                        return false;

                    miran->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                    miran->AI()->TalkWithDelay(2500, 0);
                    player->SummonCreature(NPC_ENTRY_DARK_IRON_RAIDER, -5675.15f, -3554.25f, 304.60f, 2.82f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120000);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_ironband_excavation : public AreaTriggerScript
{
    public:
        Areatrigger_at_ironband_excavation() : AreaTriggerScript("at_ironband_excavation") { }

        enum Id
        {
            // Quest
            QUEST_KEEP_YOUR_HANDS_OFF_THE_GOODS = 13650,

            // Credit
            QUEST_CREDIT_UPTURNED_GIANT     = 33485,
            QUEST_CREDIT_BROKEN_TABLET      = 33487,
            QUEST_CREDIT_OVERDRESSED_WOMAN  = 33486
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_KEEP_YOUR_HANDS_OFF_THE_GOODS))
                {
                    switch (trigger->id)
                    {
                        case 5375:  // Upturned Giant
                        {
                            if (Creature* giant = player->FindNearestCreature(QUEST_CREDIT_UPTURNED_GIANT, 15.0f, true))
                                player->KilledMonsterCredit(QUEST_CREDIT_UPTURNED_GIANT);
                            break;
                        }
                        case 5376:  // Overdressed Woman
                        {
                            if (Creature* woman = player->FindNearestCreature(QUEST_CREDIT_OVERDRESSED_WOMAN, 15.0f, true))
                                player->KilledMonsterCredit(QUEST_CREDIT_OVERDRESSED_WOMAN);
                            break;
                        }
                        case 5377: // Broken Tablet
                        {
                            if (Creature* tablet = player->FindNearestCreature(QUEST_CREDIT_BROKEN_TABLET, 15.0f, true))
                                player->KilledMonsterCredit(QUEST_CREDIT_BROKEN_TABLET);
                            break;
                        }
                        default:
                            break;
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_sludge_fields_cage : public AreaTriggerScript
{
    public:
        Areatrigger_at_sludge_fields_cage() : AreaTriggerScript("at_sludge_fields_cage") { }

        enum Id
        {
            // Npc
            NPC_ENTRY_MASTER_APOTHECARY_LYDON = 47900,

            // Quest
            QUEST_LITTLE_GIRL_LOST            = 28206
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_LITTLE_GIRL_LOST))
                {
                    if (Creature* apothecaryLydon = player->FindNearestCreature(NPC_ENTRY_MASTER_APOTHECARY_LYDON, 8.0f, true))
                        apothecaryLydon->AI()->Talk(0);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_purgation_isle : public AreaTriggerScript
{
    public:
        Areatrigger_at_purgation_isle() : AreaTriggerScript("at_purgation_isle") { }

        enum Id
        {
            // Quest
            QUEST_HEROES_OF_THE_HORDE           = 28400,

            // Npc
            NPC_ENTRY_STORMPIKE_BATTLEMASTER    = 48515,

            // Spells
            SPELL_SUMMON_BLOODFANG              = 90209,
            SPELL_SUMMON_VANNDAR                = 90210,
            SPELL_SUMMON_BALINDA                = 90211,
            SPELL_SUMMON_BATTLE_MASTER          = 90206
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_HEROES_OF_THE_HORDE))
                {
                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(player, player, 500.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                    player->VisitNearbyObject(500.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == player))
                        {
                            // Orkus
                            if ((*itr)->ToTempSummon()->GetEntry() == 48503)
                            {
                                // Flag event in progress!!
                                if ((*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC))
                                    return false;

                                // Conversations
                                (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                                (*itr)->ToCreature()->AI()->TalkWithDelay(1000, 0, player->GetGUID());
                                (*itr)->ToCreature()->AI()->TalkWithDelay(7000, 1, player->GetGUID());
                                (*itr)->ToCreature()->AI()->TalkWithDelay(13000, 2, player->GetGUID());
                                (*itr)->ToCreature()->AI()->TalkWithDelay(19000, 3, player->GetGUID());
                                (*itr)->ToCreature()->AI()->TalkWithDelay(25000, 4, player->GetGUID());
                                (*itr)->ToCreature()->AI()->TalkWithDelay(31000, 5, player->GetGUID());
                                (*itr)->ToCreature()->AI()->TalkWithDelay(36000, 6, player->GetGUID());
                                (*itr)->ToCreature()->AI()->SetData(0, 1);
                                (*itr)->ToCreature()->GetMotionMaster()->MovementExpired(true);
                                (*itr)->ToCreature()->GetMotionMaster()->MovePoint(0, -1338.94f, 528.82f, 98.00f);

                                // Summons
                                player->CastSpell(player, SPELL_SUMMON_BLOODFANG, true);
                                player->CastSpell(player, SPELL_SUMMON_BALINDA, true);
                                player->CastSpell(player, SPELL_SUMMON_VANNDAR, true);
                                player->CastSpell(player, SPELL_SUMMON_BATTLE_MASTER, true);
                            }
                        }
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_lakeshire_graveyard : public AreaTriggerScript
{
    public:
        Areatrigger_at_lakeshire_graveyard() : AreaTriggerScript("at_lakeshire_graveyard") { }

        enum Id
        {
            // Quest
            QUEST_TURNING_THE_GNOMECORDER   = 26512,

            // Spell
            SPELL_ENTRY_STATIC_SOUND        = 81769
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_TURNING_THE_GNOMECORDER))
                {
                    player->CompleteQuest(QUEST_TURNING_THE_GNOMECORDER);
                    player->CastSpell(player, SPELL_ENTRY_STATIC_SOUND, true);
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_lakeshire_bridge : public AreaTriggerScript
{
    public:
        Areatrigger_at_lakeshire_bridge() : AreaTriggerScript("at_lakeshire_bridge") { }

        enum Id
        {
            // Quest
            QUEST_SAVING_FOREMAN_OSLOW  = 26520,

            // Npc
            NPC_SUBDUED_CANYON_ETTIN    = 43197,
            NPC_HUGE_BOULDER            = 43196,

            // Npc - Workers
            NPC_WORKER_DIMITRI          = 649,
            NPC_WORKER_ALEX             = 653,
            NPC_WORKER_JESS             = 650,
            NPC_WORKER_MATTHEW          = 652,
            NPC_WORKER_DANIEL           = 651,
            NPC_WORKER_TRENT            = 648,
            NPC_FOREMAN_OSLOW           = 341,

            // Spells
            SPELL_PLAYER_INVISIBILITY   = 60191
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_SAVING_FOREMAN_OSLOW))
                {
                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(player, player, 40.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                    player->VisitNearbyObject(40.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == player))
                        {
                            // Subdued Canyon Ettin
                            if ((*itr)->ToTempSummon()->GetEntry() == NPC_SUBDUED_CANYON_ETTIN)
                            {
                                // Flag event in progress!!
                                if ((*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC))
                                    return false;

                                // Prepare event for each player
                                if (player->GetPhaseMask() == 1)
                                {
                                    player->CastSpell(player, SPELL_PLAYER_INVISIBILITY, true);
                                    (*itr)->CastSpell((*itr), SPELL_PLAYER_INVISIBILITY, true);
                                    player->SetPhaseMask(2, true);
                                    (*itr)->SetPhaseMask(2, true);
                                    (*itr)->SummonCreature(NPC_HUGE_BOULDER, -9274.12f, -2288.60f, 68.15f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
                                    player->SummonCreature(NPC_WORKER_DIMITRI, -9271.15f, -2290.04f, 68.70f, 2.44f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                    player->SummonCreature(NPC_WORKER_ALEX, -9270.94f, -2288.25f, 68.67f, 3.22f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                    player->SummonCreature(NPC_WORKER_JESS, -9273.04f, -2291.46f, 68.46f, 1.95f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                    player->SummonCreature(NPC_WORKER_MATTHEW, -9276.58f, -2286.53f, 67.94f, 5.77f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                    player->SummonCreature(NPC_WORKER_DANIEL, -9277.34f, -2288.40f, 67.92f, 5.95f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                    player->SummonCreature(NPC_WORKER_TRENT, -9277.83f, -2290.25f, 67.89f, 6.16f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                    player->SummonCreature(NPC_FOREMAN_OSLOW, -9273.90f, -2287.72f, 68.25f, 1.69f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(35000);
                                }

                                // Conversations
                                (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                                (*itr)->GetMotionMaster()->MovePoint(1, -9267.15f, -2289.58f, 69.33f);
                                (*itr)->ToCreature()->AI()->TalkWithDelay(5000, 0, player->GetGUID());
                                (*itr)->ToCreature()->AI()->SetData(0, 1);
                                Unit* workerDimitri = player->FindNearestCreature(NPC_WORKER_DIMITRI, 100.0f, true);
                                Unit* workerAlex = player->FindNearestCreature(NPC_WORKER_ALEX, 100.0f, true);
                                Unit* workerJess = player->FindNearestCreature(NPC_WORKER_JESS, 100.0f, true);
                                Unit* workerMatthew = player->FindNearestCreature(NPC_WORKER_MATTHEW, 100.0f, true);
                                Unit* workerDaniel = player->FindNearestCreature(NPC_WORKER_DANIEL, 100.0f, true);
                                Unit* workerTrent = player->FindNearestCreature(NPC_WORKER_TRENT, 100.0f, true);
                                if (workerDimitri && workerAlex && workerJess && workerMatthew && workerDaniel && workerTrent)
                                {
                                    workerAlex->ToCreature()->AI()->TalkWithDelay(13000, 0);
                                    workerMatthew->ToCreature()->AI()->TalkWithDelay(15000, 0);
                                    workerJess->ToCreature()->AI()->TalkWithDelay(16000, 0);
                                    workerAlex->SetStandState(UNIT_STAND_STATE_STAND);
                                    workerMatthew->SetStandState(UNIT_STAND_STATE_STAND);
                                    workerJess->SetStandState(UNIT_STAND_STATE_STAND);
                                    workerDaniel->SetStandState(UNIT_STAND_STATE_STAND);
                                    workerTrent->SetStandState(UNIT_STAND_STATE_STAND);
                                    workerDimitri->SetStandState(UNIT_STAND_STATE_STAND);
                                }
                                (*itr)->ToCreature()->AI()->TalkWithDelay(20000, 2, player->GetGUID());
                            }
                        }
                    }
                }
                return true;
            }
            return false;
        }
};

class Areatrigger_at_render_valley_cave : public AreaTriggerScript
{
    public:
        Areatrigger_at_render_valley_cave() : AreaTriggerScript("at_render_valley_cave") { }

        enum Id
        {
            // Quest
            QUEST_PRISONERS_OF_WAR          = 26646,

            // Npc
            NPC_ENTRY_JORGENSEN             = 43546
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isAlive())
            {
                if (player->IsActiveQuest(QUEST_PRISONERS_OF_WAR))
                {
                    std::list<Unit*> targets;
                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(player, player, 40.0f);
                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                    player->VisitNearbyObject(40.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == player))
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_JORGENSEN)
                            {
                                // Flag event in progress!!
                                if ((*itr)->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC))
                                    return false;

                                (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                                (*itr)->ToCreature()->AI()->Talk(0, player->GetGUID());
                            }
                        }
                    }
                }
                return true;
            }
            return false;
        }
};

void AddSC_areatrigger_scripts()
{
    new AreaTrigger_at_coilfang_waterfall();
    new AreaTrigger_at_legion_teleporter();
    new AreaTrigger_at_stormwright_shelf();
    new AreaTrigger_at_scent_larkorwi();
    new AreaTrigger_at_last_rites();
    new AreaTrigger_at_sholazar_waygate();
    new AreaTrigger_at_nats_landing();
    new AreaTrigger_at_brewfest();
    new AreaTrigger_at_area_52_entrance();
    new AreaTrigger_at_frostgrips_hollow();
    new AreaTrigger_at_raptor_pens();
    new Areatrigger_at_caravan_scene();
    new Areatrigger_at_horatio_laine_1();
    new Areatrigger_at_thug_scene();
    new Areatrigger_at_horatio_laine_2();
    new Areatrigger_at_moonbrook_event();
    new Areatrigger_at_mortwake_event();
    new Areatrigger_at_addle_stead_event();
    new Areatrigger_at_ruins_of_aboraz();
    new Areatrigger_at_jeklik_zanzil();
    new Areatrigger_at_venoxis_event();
    new Areatrigger_at_ironband_excavation();
    new Areatrigger_at_sludge_fields_cage();
    new Areatrigger_at_purgation_isle();
    new Areatrigger_at_lakeshire_graveyard();
    new Areatrigger_at_lakeshire_bridge();
    new Areatrigger_at_render_valley_cave();
}
