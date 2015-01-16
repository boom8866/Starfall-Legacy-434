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
SDName: Npcs_Special
SD%Complete: 100
SDComment: To be used for special NPCs that are located globally.
SDCategory: NPCs
EndScriptData
*/

/* ContentData
npc_air_force_bots       80%    support for misc (invisible) guard bots in areas where player allowed to fly. Summon guards after a preset time if tagged by spell
npc_lunaclaw_spirit      80%    support for quests 6001/6002 (Body and Heart)
npc_chicken_cluck       100%    support for quest 3861 (Cluck!)
npc_dancing_flames      100%    midsummer event NPC
npc_guardian            100%    guardianAI used to prevent players from accessing off-limits areas. Not in use by SD2
npc_garments_of_quests   80%    NPC's related to all Garments of-quests 5621, 5624, 5625, 5648, 565
npc_injured_patient     100%    patients for triage-quests (6622 and 6624)
npc_doctor              100%    Gustaf Vanhowzen and Gregory Victor, quest 6622 and 6624 (Triage)
npc_mount_vendor        100%    Regular mount vendors all over the world. Display gossip if player doesn't meet the requirements to buy
npc_rogue_trainer        80%    Scripted trainers, so they are able to offer item 17126 for class quest 6681
npc_sayge               100%    Darkmoon event fortune teller, buff player based on answers given
npc_snake_trap_serpents  80%    AI for snakes that summoned by Snake Trap
npc_shadowfiend         100%   restore 5% of owner's mana when shadowfiend die from damage
npc_locksmith            75%    list of keys needs to be confirmed
npc_firework            100%    NPC's summoned by rockets and rocket clusters, for making them cast visual
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ObjectMgr.h"
#include "World.h"
#include "PetAI.h"
#include "PassiveAI.h"
#include "CombatAI.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "SpellAuras.h"
#include "Pet.h"
#include "Transport.h"
#include "MapManager.h"
#include "AchievementMgr.h"
#include "Vehicle.h"

/* Automatic rescheduling if creature is already casting */
#define RESCHEDULE_IF_CASTING if (me->HasUnitState(UNIT_STATE_CASTING)) { events.ScheduleEvent(eventId, 1); break; }

/* Abyssion and Matriarch */
Position const abyssionLandingPos   = {179.46f, -508.27f, 171.84f, 5.33f};
Position const matriarchLandingPos  = {-103.24f, 455.96f, 165.13f, 6.08f};

/*########
# npc_air_force_bots
#########*/

enum SpawnType
{
    SPAWNTYPE_TRIPWIRE_ROOFTOP,                             // no warning, summon Creature at smaller range
    SPAWNTYPE_ALARMBOT,                                     // cast guards mark and summon npc - if player shows up with that buff duration < 5 seconds attack
};

struct SpawnAssociation
{
    uint32 thisCreatureEntry;
    uint32 spawnedCreatureEntry;
    SpawnType spawnType;
};

enum eEnums
{
    SPELL_GUARDS_MARK               = 38067,
    AURA_DURATION_TIME_LEFT         = 5000
};

float const RANGE_TRIPWIRE          = 15.0f;
float const RANGE_GUARDS_MARK       = 50.0f;

SpawnAssociation spawnAssociations[] =
{
    {2614,  15241, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Alliance)
    {2615,  15242, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Horde)
    {21974, 21976, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Area 52)
    {21993, 15242, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Horde - Bat Rider)
    {21996, 15241, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Alliance - Gryphon)
    {21997, 21976, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Goblin - Area 52 - Zeppelin)
    {21999, 15241, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Alliance)
    {22001, 15242, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Horde)
    {22002, 15242, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Ground (Horde)
    {22003, 15241, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Ground (Alliance)
    {22063, 21976, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Goblin - Area 52)
    {22065, 22064, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Ethereal - Stormspire)
    {22066, 22067, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Scryer - Dragonhawk)
    {22068, 22064, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Ethereal - Stormspire)
    {22069, 22064, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Stormspire)
    {22070, 22067, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Scryer)
    {22071, 22067, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Scryer)
    {22078, 22077, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Aldor)
    {22079, 22077, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Aldor - Gryphon)
    {22080, 22077, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Aldor)
    {22086, 22085, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Sporeggar)
    {22087, 22085, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Sporeggar - Spore Bat)
    {22088, 22085, SPAWNTYPE_TRIPWIRE_ROOFTOP},             //Air Force Trip Wire - Rooftop (Sporeggar)
    {22090, 22089, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Toshley's Station - Flying Machine)
    {22124, 22122, SPAWNTYPE_ALARMBOT},                     //Air Force Alarm Bot (Cenarion)
    {22125, 22122, SPAWNTYPE_ALARMBOT},                     //Air Force Guard Post (Cenarion - Stormcrow)
    {22126, 22122, SPAWNTYPE_ALARMBOT}                      //Air Force Trip Wire - Rooftop (Cenarion Expedition)
};

class npc_air_force_bots : public CreatureScript
{
public:
    npc_air_force_bots() : CreatureScript("npc_air_force_bots") { }

    struct npc_air_force_botsAI : public ScriptedAI
    {
        npc_air_force_botsAI(Creature* creature) : ScriptedAI(creature)
        {
            SpawnAssoc = NULL;
            SpawnedGUID = 0;

            // find the correct spawnhandling
            static uint32 entryCount = sizeof(spawnAssociations) / sizeof(SpawnAssociation);

            for (uint8 i = 0; i < entryCount; ++i)
            {
                if (spawnAssociations[i].thisCreatureEntry == creature->GetEntry())
                {
                    SpawnAssoc = &spawnAssociations[i];
                    break;
                }
            }

            if (!SpawnAssoc)
                sLog->outError(LOG_FILTER_SQL, "TCSR: Creature template entry %u has ScriptName npc_air_force_bots, but it's not handled by that script", creature->GetEntry());
            else
            {
                CreatureTemplate const* spawnedTemplate = sObjectMgr->GetCreatureTemplate(SpawnAssoc->spawnedCreatureEntry);

                if (!spawnedTemplate)
                {
                    sLog->outError(LOG_FILTER_SQL, "TCSR: Creature template entry %u does not exist in DB, which is required by npc_air_force_bots", SpawnAssoc->spawnedCreatureEntry);
                    SpawnAssoc = NULL;
                    return;
                }
            }
        }

        SpawnAssociation* SpawnAssoc;
        uint64 SpawnedGUID;

        void Reset() {}

        Creature* SummonGuard()
        {
            Creature* summoned = me->SummonCreature(SpawnAssoc->spawnedCreatureEntry, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

            if (summoned)
                SpawnedGUID = summoned->GetGUID();
            else
            {
                sLog->outError(LOG_FILTER_SQL, "TCSR: npc_air_force_bots: wasn't able to spawn Creature %u", SpawnAssoc->spawnedCreatureEntry);
                SpawnAssoc = NULL;
            }

            return summoned;
        }

        Creature* GetSummonedGuard()
        {
            Creature* creature = Unit::GetCreature(*me, SpawnedGUID);

            if (creature && creature->isAlive())
                return creature;

            return NULL;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!SpawnAssoc)
                return;

            if (me->IsValidAttackTarget(who))
            {
                Player* playerTarget = who->ToPlayer();

                // airforce guards only spawn for players
                if (!playerTarget)
                    return;

                Creature* lastSpawnedGuard = SpawnedGUID == 0 ? NULL : GetSummonedGuard();

                // prevent calling Unit::GetUnit at next MoveInLineOfSight call - speedup
                if (!lastSpawnedGuard)
                    SpawnedGUID = 0;

                switch (SpawnAssoc->spawnType)
                {
                    case SPAWNTYPE_ALARMBOT:
                    {
                        if (!who->IsWithinDistInMap(me, RANGE_GUARDS_MARK))
                            return;

                        Aura* markAura = who->GetAura(SPELL_GUARDS_MARK);
                        if (markAura)
                        {
                            // the target wasn't able to move out of our range within 25 seconds
                            if (!lastSpawnedGuard)
                            {
                                lastSpawnedGuard = SummonGuard();

                                if (!lastSpawnedGuard)
                                    return;
                            }

                            if (markAura->GetDuration() < AURA_DURATION_TIME_LEFT)
                                if (!lastSpawnedGuard->getVictim())
                                    lastSpawnedGuard->AI()->AttackStart(who);
                        }
                        else
                        {
                            if (!lastSpawnedGuard)
                                lastSpawnedGuard = SummonGuard();

                            if (!lastSpawnedGuard)
                                return;

                            lastSpawnedGuard->CastSpell(who, SPELL_GUARDS_MARK, true);
                        }
                        break;
                    }
                    case SPAWNTYPE_TRIPWIRE_ROOFTOP:
                    {
                        if (!who->IsWithinDistInMap(me, RANGE_TRIPWIRE))
                            return;

                        if (!lastSpawnedGuard)
                            lastSpawnedGuard = SummonGuard();

                        if (!lastSpawnedGuard)
                            return;

                        // ROOFTOP only triggers if the player is on the ground
                        if (!playerTarget->IsFlying() && !lastSpawnedGuard->getVictim())
                            lastSpawnedGuard->AI()->AttackStart(who);

                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_air_force_botsAI(creature);
    }
};

/*######
## npc_lunaclaw_spirit
######*/

enum
{
    QUEST_BODY_HEART_A      = 6001,
    QUEST_BODY_HEART_H      = 6002,

    TEXT_ID_DEFAULT         = 4714,
    TEXT_ID_PROGRESS        = 4715
};

#define GOSSIP_ITEM_GRANT   "You have thought well, spirit. I ask you to grant me the strength of your body and the strength of your heart."

class npc_lunaclaw_spirit : public CreatureScript
{
public:
    npc_lunaclaw_spirit() : CreatureScript("npc_lunaclaw_spirit") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_BODY_HEART_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_BODY_HEART_H) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GRANT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(TEXT_ID_DEFAULT, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->SEND_GOSSIP_MENU(TEXT_ID_PROGRESS, creature->GetGUID());
            player->AreaExploredOrEventHappens(player->GetTeam() == ALLIANCE ? QUEST_BODY_HEART_A : QUEST_BODY_HEART_H);
        }
        return true;
    }
};

/*########
# npc_chicken_cluck
#########*/

enum ChickenCluck
{
    EMOTE_HELLO_A       = 0,
    EMOTE_HELLO_H       = 1,
    EMOTE_CLUCK_TEXT    = 2,

    QUEST_CLUCK         = 3861,
    FACTION_FRIENDLY    = 35,
    FACTION_CHICKEN     = 31
};

class npc_chicken_cluck : public CreatureScript
{
public:
    npc_chicken_cluck() : CreatureScript("npc_chicken_cluck") { }

    struct npc_chicken_cluckAI : public ScriptedAI
    {
        npc_chicken_cluckAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 ResetFlagTimer;

        void Reset()
        {
            ResetFlagTimer = 120000;
            me->setFaction(FACTION_CHICKEN);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(uint32 diff)
        {
            // Reset flags after a certain time has passed so that the next player has to start the 'event' again
            if (me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
            {
                if (ResetFlagTimer <= diff)
                {
                    EnterEvadeMode();
                    return;
                }
                else
                    ResetFlagTimer -= diff;
            }

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

        void ReceiveEmote(Player* player, uint32 emote)
        {
            switch (emote)
            {
                case TEXT_EMOTE_CHICKEN:
                    if (player->GetQuestStatus(QUEST_CLUCK) == QUEST_STATUS_NONE && rand() % 30 == 1)
                    {
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        me->setFaction(FACTION_FRIENDLY);
                        Talk(player->GetTeam() == HORDE ? EMOTE_HELLO_H : EMOTE_HELLO_A);
                    }
                    break;
                case TEXT_EMOTE_CHEER:
                    if (player->GetQuestStatus(QUEST_CLUCK) == QUEST_STATUS_COMPLETE)
                    {
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        me->setFaction(FACTION_FRIENDLY);
                        Talk(EMOTE_CLUCK_TEXT);
                    }
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chicken_cluckAI(creature);
    }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_CLUCK)
            CAST_AI(npc_chicken_cluck::npc_chicken_cluckAI, creature->AI())->Reset();

        return true;
    }

    bool OnQuestComplete(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_CLUCK)
            CAST_AI(npc_chicken_cluck::npc_chicken_cluckAI, creature->AI())->Reset();

        return true;
    }
};

/*######
## npc_dancing_flames
######*/

#define SPELL_BRAZIER       45423
#define SPELL_SEDUCTION     47057
#define SPELL_FIERY_AURA    45427

class npc_dancing_flames : public CreatureScript
{
public:
    npc_dancing_flames() : CreatureScript("npc_dancing_flames") { }

    struct npc_dancing_flamesAI : public ScriptedAI
    {
        npc_dancing_flamesAI(Creature* creature) : ScriptedAI(creature) {}

        bool Active;
        uint32 CanIteract;

        void Reset()
        {
            Active = true;
            CanIteract = 3500;
            DoCast(me, SPELL_BRAZIER, true);
            DoCast(me, SPELL_FIERY_AURA, false);
            float x, y, z;
            me->GetPosition(x, y, z);
            me->Relocate(x, y, z + 0.94f);
            me->SetDisableGravity(true);
            me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
            WorldPacket data;                       //send update position to client
            me->BuildHeartBeatMsg(&data);
            me->SendMessageToSet(&data, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (!Active)
            {
                if (CanIteract <= diff)
                {
                    Active = true;
                    CanIteract = 3500;
                    me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
                }
                else
                    CanIteract -= diff;
            }
        }

        void EnterCombat(Unit* /*who*/){}

        void ReceiveEmote(Player* player, uint32 emote)
        {
            if (me->IsWithinLOS(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()) && me->IsWithinDistInMap(player, 30.0f))
            {
                me->SetInFront(player);
                Active = false;

                WorldPacket data;
                me->BuildHeartBeatMsg(&data);
                me->SendMessageToSet(&data, true);
                switch (emote)
                {
                    case TEXT_EMOTE_KISS:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_SHY);
                        break;
                    case TEXT_EMOTE_WAVE:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        break;
                    case TEXT_EMOTE_BOW:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
                        break;
                    case TEXT_EMOTE_JOKE:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                        break;
                    case TEXT_EMOTE_DANCE:
                        if (!player->HasAura(SPELL_SEDUCTION))
                            DoCast(player, SPELL_SEDUCTION, true);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dancing_flamesAI(creature);
    }
};

/*######
## Triage quest
######*/

enum Doctor
{
    SAY_DOC             = 0,

    DOCTOR_ALLIANCE     = 12939,
    DOCTOR_HORDE        = 12920,
    ALLIANCE_COORDS     = 7,
    HORDE_COORDS        = 6
};

struct Location
{
    float x, y, z, o;
};

static Location AllianceCoords[]=
{
    {-3757.38f, -4533.05f, 14.16f, 3.62f},                      // Top-far-right bunk as seen from entrance
    {-3754.36f, -4539.13f, 14.16f, 5.13f},                      // Top-far-left bunk
    {-3749.54f, -4540.25f, 14.28f, 3.34f},                      // Far-right bunk
    {-3742.10f, -4536.85f, 14.28f, 3.64f},                      // Right bunk near entrance
    {-3755.89f, -4529.07f, 14.05f, 0.57f},                      // Far-left bunk
    {-3749.51f, -4527.08f, 14.07f, 5.26f},                      // Mid-left bunk
    {-3746.37f, -4525.35f, 14.16f, 5.22f},                      // Left bunk near entrance
};

//alliance run to where
#define A_RUNTOX -3742.96f
#define A_RUNTOY -4531.52f
#define A_RUNTOZ 11.91f

static Location HordeCoords[]=
{
    {-1013.75f, -3492.59f, 62.62f, 4.34f},                      // Left, Behind
    {-1017.72f, -3490.92f, 62.62f, 4.34f},                      // Right, Behind
    {-1015.77f, -3497.15f, 62.82f, 4.34f},                      // Left, Mid
    {-1019.51f, -3495.49f, 62.82f, 4.34f},                      // Right, Mid
    {-1017.25f, -3500.85f, 62.98f, 4.34f},                      // Left, front
    {-1020.95f, -3499.21f, 62.98f, 4.34f}                       // Right, Front
};

//horde run to where
#define H_RUNTOX -1016.44f
#define H_RUNTOY -3508.48f
#define H_RUNTOZ 62.96f

uint32 const AllianceSoldierId[3] =
{
    12938,                                                  // 12938 Injured Alliance Soldier
    12936,                                                  // 12936 Badly injured Alliance Soldier
    12937                                                   // 12937 Critically injured Alliance Soldier
};

uint32 const HordeSoldierId[3] =
{
    12923,                                                  //12923 Injured Soldier
    12924,                                                  //12924 Badly injured Soldier
    12925                                                   //12925 Critically injured Soldier
};

/*######
## npc_doctor (handles both Gustaf Vanhowzen and Gregory Victor)
######*/
class npc_doctor : public CreatureScript
{
public:
    npc_doctor() : CreatureScript("npc_doctor") {}

    enum Id
    {
        // Skills
        SKILL_ENTRY_FIRST_AID         = 129,

        // Spells
        SPELL_HEAVY_RUNECLOTH_BANDAGE = 18630,
        SPELL_RUNECLOTH_BANDAGE       = 18629,
        SPELL_HEAVY_MAGEWEAVE_BANDAGE = 10841,
        SPELL_EFFECT_LEARN            = 47292
    };

    bool OnGossipSelect(Player* plr, Creature* me, uint32 /*sender*/, uint32 action)
    {
        plr->PlayerTalkClass->SendCloseGossip();
        if (!plr->HasSkill(SKILL_ENTRY_FIRST_AID))
        {
            ChatHandler(plr->GetSession()).PSendSysMessage("Profession required: First Aid");
            return true;
        }
        if (!plr->HasSpell(SPELL_HEAVY_MAGEWEAVE_BANDAGE))
            plr->learnSpell(SPELL_HEAVY_MAGEWEAVE_BANDAGE, false);
        if (!plr->HasSpell(SPELL_RUNECLOTH_BANDAGE))
            plr->learnSpell(SPELL_RUNECLOTH_BANDAGE, false);
        if (!plr->HasSpell(SPELL_HEAVY_RUNECLOTH_BANDAGE))
            plr->learnSpell(SPELL_HEAVY_RUNECLOTH_BANDAGE, false);

        plr->CastSpell(plr, SPELL_EFFECT_LEARN, true);
        return true;
    }

    struct npc_doctorAI : public ScriptedAI
    {
        npc_doctorAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 PlayerGUID;

        uint32 SummonPatientTimer;
        uint32 SummonPatientCount;
        uint32 PatientDiedCount;
        uint32 PatientSavedCount;

        bool Event;

        std::list<uint64> Patients;
        std::vector<Location*> Coordinates;

        void Reset()
        {
            PlayerGUID = 0;

            SummonPatientTimer = 10000;
            SummonPatientCount = 0;
            PatientDiedCount = 0;
            PatientSavedCount = 0;

            Patients.clear();
            Coordinates.clear();

            Event = false;

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void BeginEvent(Player* player)
        {
            PlayerGUID = player->GetGUID();

            SummonPatientTimer = 10000;
            SummonPatientCount = 0;
            PatientDiedCount = 0;
            PatientSavedCount = 0;

            switch (me->GetEntry())
            {
                case DOCTOR_ALLIANCE:
                    for (uint8 i = 0; i < ALLIANCE_COORDS; ++i)
                        Coordinates.push_back(&AllianceCoords[i]);
                    break;
                case DOCTOR_HORDE:
                    for (uint8 i = 0; i < HORDE_COORDS; ++i)
                        Coordinates.push_back(&HordeCoords[i]);
                    break;
            }

            Event = true;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void PatientDied(Location* point)
        {
            Player* player = Unit::GetPlayer(*me, PlayerGUID);
            if (player && ((player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)))
            {
                ++PatientDiedCount;

                if (PatientDiedCount > 5 && Event)
                {
                    if (player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE)
                        player->FailQuest(6624);
                    else if (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)
                        player->FailQuest(6622);

                    Reset();
                    return;
                }

                Coordinates.push_back(point);
            }
            else
                // If no player or player abandon quest in progress
                Reset();
        }

        void PatientSaved(Creature* /*soldier*/, Player* player, Location* point)
        {
            if (player && PlayerGUID == player->GetGUID())
            {
                if ((player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE))
                {
                    ++PatientSavedCount;

                    if (PatientSavedCount == 15)
                    {
                        if (!Patients.empty())
                        {
                            std::list<uint64>::const_iterator itr;
                            for (itr = Patients.begin(); itr != Patients.end(); ++itr)
                            {
                                if (Creature* patient = Unit::GetCreature((*me), *itr))
                                    patient->setDeathState(JUST_DIED);
                            }
                        }

                        if (player->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE)
                            player->AreaExploredOrEventHappens(6624);
                        else if (player->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)
                            player->AreaExploredOrEventHappens(6622);

                        Reset();
                        return;
                    }

                    Coordinates.push_back(point);
                }
            }
        }

        void UpdateAI(uint32 diff);

        void EnterCombat(Unit* /*who*/){}
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if ((quest->GetQuestId() == 6624) || (quest->GetQuestId() == 6622))
            CAST_AI(npc_doctor::npc_doctorAI, creature->AI())->BeginEvent(player);

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_doctorAI(creature);
    }
};

/*#####
## npc_injured_patient (handles all the patients, no matter Horde or Alliance)
#####*/

class npc_injured_patient : public CreatureScript
{
public:
    npc_injured_patient() : CreatureScript("npc_injured_patient") { }

    struct npc_injured_patientAI : public ScriptedAI
    {
        npc_injured_patientAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 DoctorGUID;
        Location* Coord;

        void Reset()
        {
            DoctorGUID = 0;
            Coord = NULL;

            //no select
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            //no regen health
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);

            //to make them lay with face down
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_DEAD);

            uint32 mobId = me->GetEntry();

            switch (mobId)
            {                                                   //lower max health
                case 12923:
                case 12938:                                     //Injured Soldier
                    me->SetHealth(me->CountPctFromMaxHealth(75));
                    break;
                case 12924:
                case 12936:                                     //Badly injured Soldier
                    me->SetHealth(me->CountPctFromMaxHealth(50));
                    break;
                case 12925:
                case 12937:                                     //Critically injured Soldier
                    me->SetHealth(me->CountPctFromMaxHealth(25));
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/){}

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (caster->GetTypeId() == TYPEID_PLAYER && me->isAlive() && spell->Id == 20804)
            {
                if ((CAST_PLR(caster)->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE) || (CAST_PLR(caster)->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE))
                    if (DoctorGUID)
                        if (Creature* doctor = Unit::GetCreature(*me, DoctorGUID))
                            CAST_AI(npc_doctor::npc_doctorAI, doctor->AI())->PatientSaved(me, CAST_PLR(caster), Coord);

                //make not selectable
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                //regen health
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);

                //stand up
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_STAND);

                Talk(SAY_DOC);

                uint32 mobId = me->GetEntry();
                me->SetWalk(false);

                switch (mobId)
                {
                    case 12923:
                    case 12924:
                    case 12925:
                        me->GetMotionMaster()->MovePoint(0, H_RUNTOX, H_RUNTOY, H_RUNTOZ);
                        break;
                    case 12936:
                    case 12937:
                    case 12938:
                        me->GetMotionMaster()->MovePoint(0, A_RUNTOX, A_RUNTOY, A_RUNTOZ);
                        break;
                }
            }
        }

        void UpdateAI(uint32 /*diff*/)
        {
            //lower HP on every world tick makes it a useful counter, not officlone though
            if (me->isAlive() && me->GetHealth() > 6)
                me->ModifyHealth(-5);

            if (me->isAlive() && me->GetHealth() <= 6)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->setDeathState(JUST_DIED);
                me->SetFlag(UNIT_DYNAMIC_FLAGS, 32);

                if (DoctorGUID)
                    if (Creature* doctor = Unit::GetCreature((*me), DoctorGUID))
                        CAST_AI(npc_doctor::npc_doctorAI, doctor->AI())->PatientDied(Coord);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_patientAI(creature);
    }
};

void npc_doctor::npc_doctorAI::UpdateAI(uint32 diff)
{
    if (Event && SummonPatientCount >= 20)
    {
        Reset();
        return;
    }

    if (Event)
    {
        if (SummonPatientTimer <= diff)
        {
            if (Coordinates.empty())
                return;

            std::vector<Location*>::iterator itr = Coordinates.begin() + rand() % Coordinates.size();
            uint32 patientEntry = 0;

            switch (me->GetEntry())
            {
                case DOCTOR_ALLIANCE:
                    patientEntry = AllianceSoldierId[rand() % 3];
                    break;
                case DOCTOR_HORDE:
                    patientEntry = HordeSoldierId[rand() % 3];
                    break;
                default:
                    sLog->outError(LOG_FILTER_TSCR, "Invalid entry for Triage doctor. Please check your database");
                    return;
            }

            if (Location* point = *itr)
            {
                if (Creature* Patient = me->SummonCreature(patientEntry, point->x, point->y, point->z, point->o, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
                {
                    //303, this flag appear to be required for client side item->spell to work (TARGET_SINGLE_FRIEND)
                    Patient->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);

                    Patients.push_back(Patient->GetGUID());
                    CAST_AI(npc_injured_patient::npc_injured_patientAI, Patient->AI())->DoctorGUID = me->GetGUID();
                    CAST_AI(npc_injured_patient::npc_injured_patientAI, Patient->AI())->Coord = point;

                    Coordinates.erase(itr);
                }
            }
            SummonPatientTimer = 10000;
            ++SummonPatientCount;
        }
        else
            SummonPatientTimer -= diff;
    }
}

/*######
## npc_garments_of_quests
######*/

//TODO: get text for each NPC

enum Garments
{
    SPELL_LESSER_HEAL_R2    = 2052,
    SPELL_FORTITUDE_R1      = 1243,

    QUEST_MOON              = 5621,
    QUEST_LIGHT_1           = 5624,
    QUEST_LIGHT_2           = 5625,
    QUEST_SPIRIT            = 5648,
    QUEST_DARKNESS          = 5650,

    ENTRY_SHAYA             = 12429,
    ENTRY_ROBERTS           = 12423,
    ENTRY_DOLF              = 12427,
    ENTRY_KORJA             = 12430,
    ENTRY_DG_KEL            = 12428,

    // used by 12429, 12423, 12427, 12430, 12428, but signed for 12429
    SAY_THANKS              = 0,
    SAY_GOODBYE             = 1,
    SAY_HEALED              = 2,
};

class npc_garments_of_quests : public CreatureScript
{
public:
    npc_garments_of_quests() : CreatureScript("npc_garments_of_quests") { }

    struct npc_garments_of_questsAI : public npc_escortAI
    {
        npc_garments_of_questsAI(Creature* creature) : npc_escortAI(creature)
        {
            Reset();
        }

        uint64 CasterGUID;

        bool IsHealed;
        bool CanRun;

        uint32 RunAwayTimer;

        void Reset()
        {
            CasterGUID = 0;

            IsHealed = false;
            CanRun = false;

            RunAwayTimer = 5000;

            me->SetStandState(UNIT_STAND_STATE_KNEEL);
            // expect database to have RegenHealth=0
            me->SetHealth(me->CountPctFromMaxHealth(70));
        }

        void EnterCombat(Unit* /*who*/) { }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_LESSER_HEAL_R2 || spell->Id == SPELL_FORTITUDE_R1)
            {
                //not while in combat
                if (me->isInCombat())
                    return;

                //nothing to be done now
                if (IsHealed && CanRun)
                    return;

                if (Player* player = caster->ToPlayer())
                {
                    switch (me->GetEntry())
                    {
                        case ENTRY_SHAYA:
                            if (player->GetQuestStatus(QUEST_MOON) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (IsHealed && !CanRun && spell->Id == SPELL_FORTITUDE_R1)
                                {
                                    Talk(SAY_THANKS, caster->GetGUID());
                                    CanRun = true;
                                }
                                else if (!IsHealed && spell->Id == SPELL_LESSER_HEAL_R2)
                                {
                                    CasterGUID = caster->GetGUID();
                                    me->SetStandState(UNIT_STAND_STATE_STAND);
                                    Talk(SAY_HEALED, caster->GetGUID());
                                    IsHealed = true;
                                }
                            }
                            break;
                        case ENTRY_ROBERTS:
                            if (player->GetQuestStatus(QUEST_LIGHT_1) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (IsHealed && !CanRun && spell->Id == SPELL_FORTITUDE_R1)
                                {
                                    Talk(SAY_THANKS, caster->GetGUID());
                                    CanRun = true;
                                }
                                else if (!IsHealed && spell->Id == SPELL_LESSER_HEAL_R2)
                                {
                                    CasterGUID = caster->GetGUID();
                                    me->SetStandState(UNIT_STAND_STATE_STAND);
                                    Talk(SAY_HEALED, caster->GetGUID());
                                    IsHealed = true;
                                }
                            }
                            break;
                        case ENTRY_DOLF:
                            if (player->GetQuestStatus(QUEST_LIGHT_2) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (IsHealed && !CanRun && spell->Id == SPELL_FORTITUDE_R1)
                                {
                                    Talk(SAY_THANKS, caster->GetGUID());
                                    CanRun = true;
                                }
                                else if (!IsHealed && spell->Id == SPELL_LESSER_HEAL_R2)
                                {
                                    CasterGUID = caster->GetGUID();
                                    me->SetStandState(UNIT_STAND_STATE_STAND);
                                    Talk(SAY_HEALED, caster->GetGUID());
                                    IsHealed = true;
                                }
                            }
                            break;
                        case ENTRY_KORJA:
                            if (player->GetQuestStatus(QUEST_SPIRIT) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (IsHealed && !CanRun && spell->Id == SPELL_FORTITUDE_R1)
                                {
                                    Talk(SAY_THANKS, caster->GetGUID());
                                    CanRun = true;
                                }
                                else if (!IsHealed && spell->Id == SPELL_LESSER_HEAL_R2)
                                {
                                    CasterGUID = caster->GetGUID();
                                    me->SetStandState(UNIT_STAND_STATE_STAND);
                                    Talk(SAY_HEALED, caster->GetGUID());
                                    IsHealed = true;
                                }
                            }
                            break;
                        case ENTRY_DG_KEL:
                            if (player->GetQuestStatus(QUEST_DARKNESS) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (IsHealed && !CanRun && spell->Id == SPELL_FORTITUDE_R1)
                                {
                                    Talk(SAY_THANKS, caster->GetGUID());
                                    CanRun = true;
                                }
                                else if (!IsHealed && spell->Id == SPELL_LESSER_HEAL_R2)
                                {
                                    CasterGUID = caster->GetGUID();
                                    me->SetStandState(UNIT_STAND_STATE_STAND);
                                    Talk(SAY_HEALED, caster->GetGUID());
                                    IsHealed = true;
                                }
                            }
                            break;
                    }

                    // give quest credit, not expect any special quest objectives
                    if (CanRun)
                        player->TalkedToCreature(me->GetEntry(), me->GetGUID());
                }
            }
        }

        void WaypointReached(uint32 /*waypointId*/)
        {

        }

        void UpdateAI(uint32 diff)
        {
            if (CanRun && !me->isInCombat())
            {
                if (RunAwayTimer <= diff)
                {
                    if (Unit* unit = Unit::GetUnit(*me, CasterGUID))
                    {
                        switch (me->GetEntry())
                        {
                            case ENTRY_SHAYA:
                                Talk(SAY_GOODBYE, unit->GetGUID());
                                break;
                            case ENTRY_ROBERTS:
                                Talk(SAY_GOODBYE, unit->GetGUID());
                                break;
                            case ENTRY_DOLF:
                                Talk(SAY_GOODBYE, unit->GetGUID());
                                break;
                            case ENTRY_KORJA:
                                Talk(SAY_GOODBYE, unit->GetGUID());
                                break;
                            case ENTRY_DG_KEL:
                                Talk(SAY_GOODBYE, unit->GetGUID());
                                break;
                        }

                        Start(false, true, true);
                    }
                    else
                        EnterEvadeMode();                       //something went wrong

                    RunAwayTimer = 30000;
                }
                else
                    RunAwayTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_garments_of_questsAI(creature);
    }
};

/*######
## npc_guardian
######*/

#define SPELL_DEATHTOUCH                5

class npc_guardian : public CreatureScript
{
public:
    npc_guardian() : CreatureScript("npc_guardian") { }

    struct npc_guardianAI : public ScriptedAI
    {
        npc_guardianAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            if (me->isAttackReady())
            {
                DoCast(me->getVictim(), SPELL_DEATHTOUCH, true);
                me->resetAttackTimer();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_guardianAI(creature);
    }
};

/*######
## npc_mount_vendor
######*/

class npc_mount_vendor : public CreatureScript
{
public:
    npc_mount_vendor() : CreatureScript("npc_mount_vendor") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        bool canBuy = false;
        uint32 vendor = creature->GetEntry();
        uint8 race = player->getRace();

        switch (vendor)
        {
            case 384:                                           //Katie Hunter
            case 1460:                                          //Unger Statforth
            case 2357:                                          //Merideth Carlson
            case 4885:                                          //Gregor MacVince
                if (player->GetReputationRank(72) != REP_EXALTED && race != RACE_HUMAN)
                    player->SEND_GOSSIP_MENU(5855, creature->GetGUID());
                else canBuy = true;
                break;
            case 1261:                                          //Veron Amberstill
                if (player->GetReputationRank(47) != REP_EXALTED && race != RACE_DWARF)
                    player->SEND_GOSSIP_MENU(5856, creature->GetGUID());
                else canBuy = true;
                break;
            case 3362:                                          //Ogunaro Wolfrunner
                if (player->GetReputationRank(76) != REP_EXALTED && race != RACE_ORC)
                    player->SEND_GOSSIP_MENU(5841, creature->GetGUID());
                else canBuy = true;
                break;
            case 3685:                                          //Harb Clawhoof
                if (player->GetReputationRank(81) != REP_EXALTED && race != RACE_TAUREN)
                    player->SEND_GOSSIP_MENU(5843, creature->GetGUID());
                else canBuy = true;
                break;
            case 4730:                                          //Lelanai
                if (player->GetReputationRank(69) != REP_EXALTED && race != RACE_NIGHTELF)
                    player->SEND_GOSSIP_MENU(5844, creature->GetGUID());
                else canBuy = true;
                break;
            case 4731:                                          //Zachariah Post
                if (player->GetReputationRank(68) != REP_EXALTED && race != RACE_UNDEAD_PLAYER)
                    player->SEND_GOSSIP_MENU(5840, creature->GetGUID());
                else canBuy = true;
                break;
            case 7952:                                          //Zjolnir
                if (player->GetReputationRank(530) != REP_EXALTED && race != RACE_TROLL)
                    player->SEND_GOSSIP_MENU(5842, creature->GetGUID());
                else canBuy = true;
                break;
            case 7955:                                          //Milli Featherwhistle
                if (player->GetReputationRank(54) != REP_EXALTED && race != RACE_GNOME)
                    player->SEND_GOSSIP_MENU(5857, creature->GetGUID());
                else canBuy = true;
                break;
            case 16264:                                         //Winaestra
                if (player->GetReputationRank(911) != REP_EXALTED && race != RACE_BLOODELF)
                    player->SEND_GOSSIP_MENU(10305, creature->GetGUID());
                else canBuy = true;
                break;
            case 17584:                                         //Torallius the Pack Handler
                if (player->GetReputationRank(930) != REP_EXALTED && race != RACE_DRAENEI)
                    player->SEND_GOSSIP_MENU(10239, creature->GetGUID());
                else canBuy = true;
                break;
        }

        if (canBuy)
        {
            if (creature->isVendor())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_TRADE)
            player->GetSession()->SendListInventory(creature->GetGUID());

        return true;
    }
};

/*######
## npc_rogue_trainer
######*/

#define GOSSIP_HELLO_ROGUE1 "I wish to unlearn my talents"
#define GOSSIP_HELLO_ROGUE2 "<Take the letter>"
#define GOSSIP_HELLO_ROGUE3 "Purchase a Dual Talent Specialization."

class npc_rogue_trainer : public CreatureScript
{
public:
    npc_rogue_trainer() : CreatureScript("npc_rogue_trainer") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (creature->isTrainer())
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

        if (creature->isCanTrainingAndResetTalentsOf(player))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_HELLO_ROGUE1, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_UNLEARNTALENTS);

        if (player->GetSpecsCount() == 1 && creature->isCanTrainingAndResetTalentsOf(player) && player->getLevel() >= sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_HELLO_ROGUE3, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_LEARNDUALSPEC);

        if (player->getClass() == CLASS_ROGUE && player->getLevel() >= 24 && !player->HasItemCount(17126) && !player->GetQuestRewardStatus(6681))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_ROGUE2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(5996, creature->GetGUID());
        } else
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 21100, false);
                break;
            case GOSSIP_ACTION_TRAIN:
                player->GetSession()->SendTrainerList(creature->GetGUID());
                break;
            case GOSSIP_OPTION_UNLEARNTALENTS:
                player->CLOSE_GOSSIP_MENU();
                player->SendTalentWipeConfirm(creature->GetGUID());
                break;
            case GOSSIP_OPTION_LEARNDUALSPEC:
                if (player->GetSpecsCount() == 1 && !(player->getLevel() < sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL)))
                {
                    if (!player->HasEnoughMoney(uint64(10000000)))
                    {
                        player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
                        player->PlayerTalkClass->SendCloseGossip();
                        break;
                    }
                    else
                    {
                        player->ModifyMoney(int64(-10000000));

                        // Cast spells that teach dual spec
                        // Both are also ImplicitTarget self and must be cast by player
                        player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
                        player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());

                        // Should show another Gossip text with "Congratulations..."
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                }
                break;
        }
        return true;
    }
};

/*######
## npc_sayge
######*/

#define SPELL_DMG       23768                               //dmg
#define SPELL_RES       23769                               //res
#define SPELL_ARM       23767                               //arm
#define SPELL_SPI       23738                               //spi
#define SPELL_INT       23766                               //int
#define SPELL_STM       23737                               //stm
#define SPELL_STR       23735                               //str
#define SPELL_AGI       23736                               //agi
#define SPELL_FORTUNE   23765                               //faire fortune

#define GOSSIP_HELLO_SAYGE  "Yes"
#define GOSSIP_SENDACTION_SAYGE1    "Slay the Man"
#define GOSSIP_SENDACTION_SAYGE2    "Turn him over to liege"
#define GOSSIP_SENDACTION_SAYGE3    "Confiscate the corn"
#define GOSSIP_SENDACTION_SAYGE4    "Let him go and have the corn"
#define GOSSIP_SENDACTION_SAYGE5    "Execute your friend painfully"
#define GOSSIP_SENDACTION_SAYGE6    "Execute your friend painlessly"
#define GOSSIP_SENDACTION_SAYGE7    "Let your friend go"
#define GOSSIP_SENDACTION_SAYGE8    "Confront the diplomat"
#define GOSSIP_SENDACTION_SAYGE9    "Show not so quiet defiance"
#define GOSSIP_SENDACTION_SAYGE10   "Remain quiet"
#define GOSSIP_SENDACTION_SAYGE11   "Speak against your brother openly"
#define GOSSIP_SENDACTION_SAYGE12   "Help your brother in"
#define GOSSIP_SENDACTION_SAYGE13   "Keep your brother out without letting him know"
#define GOSSIP_SENDACTION_SAYGE14   "Take credit, keep gold"
#define GOSSIP_SENDACTION_SAYGE15   "Take credit, share the gold"
#define GOSSIP_SENDACTION_SAYGE16   "Let the knight take credit"
#define GOSSIP_SENDACTION_SAYGE17   "Thanks"

class npc_sayge : public CreatureScript
{
public:
    npc_sayge() : CreatureScript("npc_sayge") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->HasSpellCooldown(SPELL_INT) ||
            player->HasSpellCooldown(SPELL_ARM) ||
            player->HasSpellCooldown(SPELL_DMG) ||
            player->HasSpellCooldown(SPELL_RES) ||
            player->HasSpellCooldown(SPELL_STR) ||
            player->HasSpellCooldown(SPELL_AGI) ||
            player->HasSpellCooldown(SPELL_STM) ||
            player->HasSpellCooldown(SPELL_SPI))
            player->SEND_GOSSIP_MENU(7393, creature->GetGUID());
        else
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_SAYGE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(7339, creature->GetGUID());
        }

        return true;
    }

    void SendAction(Player* player, Creature* creature, uint32 action)
    {
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE1,            GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE2,            GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE3,            GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE4,            GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU(7340, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE5,            GOSSIP_SENDER_MAIN + 1, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE6,            GOSSIP_SENDER_MAIN + 2, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE7,            GOSSIP_SENDER_MAIN + 3, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU(7341, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE8,            GOSSIP_SENDER_MAIN + 4, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE9,            GOSSIP_SENDER_MAIN + 5, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE10,           GOSSIP_SENDER_MAIN + 2, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU(7361, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE11,           GOSSIP_SENDER_MAIN + 6, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE12,           GOSSIP_SENDER_MAIN + 7, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE13,           GOSSIP_SENDER_MAIN + 8, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU(7362, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE14,           GOSSIP_SENDER_MAIN + 5, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE15,           GOSSIP_SENDER_MAIN + 4, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE16,           GOSSIP_SENDER_MAIN + 3, GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU(7363, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SENDACTION_SAYGE17,           GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->SEND_GOSSIP_MENU(7364, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                creature->CastSpell(player, SPELL_FORTUNE, false);
                player->SEND_GOSSIP_MENU(7365, creature->GetGUID());
                break;
        }
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (sender)
        {
            case GOSSIP_SENDER_MAIN:
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 1:
                creature->CastSpell(player, SPELL_DMG, false);
                player->AddSpellCooldown(SPELL_DMG, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 2:
                creature->CastSpell(player, SPELL_RES, false);
                player->AddSpellCooldown(SPELL_RES, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 3:
                creature->CastSpell(player, SPELL_ARM, false);
                player->AddSpellCooldown(SPELL_ARM, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 4:
                creature->CastSpell(player, SPELL_SPI, false);
                player->AddSpellCooldown(SPELL_SPI, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 5:
                creature->CastSpell(player, SPELL_INT, false);
                player->AddSpellCooldown(SPELL_INT, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 6:
                creature->CastSpell(player, SPELL_STM, false);
                player->AddSpellCooldown(SPELL_STM, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 7:
                creature->CastSpell(player, SPELL_STR, false);
                player->AddSpellCooldown(SPELL_STR, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
            case GOSSIP_SENDER_MAIN + 8:
                creature->CastSpell(player, SPELL_AGI, false);
                player->AddSpellCooldown(SPELL_AGI, 0, time(NULL) + 7200);
                SendAction(player, creature, action);
                break;
        }
        return true;
    }
};

class npc_steam_tonk : public CreatureScript
{
public:
    npc_steam_tonk() : CreatureScript("npc_steam_tonk") { }

    struct npc_steam_tonkAI : public ScriptedAI
    {
        npc_steam_tonkAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() {}
        void EnterCombat(Unit* /*who*/) {}

        void OnPossess(bool apply)
        {
            if (apply)
            {
                // Initialize the action bar without the melee attack command
                me->InitCharmInfo();
                me->GetCharmInfo()->InitEmptyActionBar(false);

                me->SetReactState(REACT_PASSIVE);
            }
            else
                me->SetReactState(REACT_AGGRESSIVE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_steam_tonkAI(creature);
    }
};

#define SPELL_TONK_MINE_DETONATE 25099

class npc_tonk_mine : public CreatureScript
{
public:
    npc_tonk_mine() : CreatureScript("npc_tonk_mine") { }

    struct npc_tonk_mineAI : public ScriptedAI
    {
        npc_tonk_mineAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        uint32 ExplosionTimer;

        void Reset()
        {
            ExplosionTimer = 3000;
        }

        void EnterCombat(Unit* /*who*/) {}
        void AttackStart(Unit* /*who*/) {}
        void MoveInLineOfSight(Unit* /*who*/) {}

        void UpdateAI(uint32 diff)
        {
            if (ExplosionTimer <= diff)
            {
                DoCast(me, SPELL_TONK_MINE_DETONATE, true);
                me->setDeathState(DEAD); // unsummon it
            }
            else
                ExplosionTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tonk_mineAI(creature);
    }
};

/*####
## npc_brewfest_reveler
####*/

class npc_brewfest_reveler : public CreatureScript
{
public:
    npc_brewfest_reveler() : CreatureScript("npc_brewfest_reveler") { }

    struct npc_brewfest_revelerAI : public ScriptedAI
    {
        npc_brewfest_revelerAI(Creature* creature) : ScriptedAI(creature) {}
        void ReceiveEmote(Player* player, uint32 emote)
        {
            if (!IsHolidayActive(HOLIDAY_BREWFEST))
                return;

            if (emote == TEXT_EMOTE_DANCE)
                me->CastSpell(player, 41586, false);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brewfest_revelerAI(creature);
    }
};


/*####
## npc_snake_trap_serpents
####*/

#define SPELL_MIND_NUMBING_POISON    25810   //Viper
#define SPELL_DEADLY_POISON          34655   //Venomous Snake
#define SPELL_CRIPPLING_POISON       30981   //Viper

#define VENOMOUS_SNAKE_TIMER 1500
#define VIPER_TIMER 3000

#define C_VIPER 19921

class npc_snake_trap : public CreatureScript
{
public:
    npc_snake_trap() : CreatureScript("npc_snake_trap_serpents") { }

    struct npc_snake_trap_serpentsAI : public ScriptedAI
    {
        npc_snake_trap_serpentsAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 SpellTimer;
        bool IsViper;

        void EnterCombat(Unit* /*who*/) {}

        void Reset()
        {
            SpellTimer = 0;

            CreatureTemplate const* Info = me->GetCreatureTemplate();

            IsViper = Info->Entry == C_VIPER ? true : false;

            me->SetMaxHealth(uint32(107 * (me->getLevel() - 40) * 0.025f));
            //Add delta to make them not all hit the same time
            uint32 delta = (rand() % 7) * 100;
            me->SetBaseAttackTime(BASE_ATTACK, float(Info->BaseAttackTime + delta));

            // Start attacking attacker of owner on first ai update after spawn - move in line of sight may choose better target
            if (!me->getVictim() && me->isSummon())
                if (Unit* Owner = me->ToTempSummon()->GetSummoner())
                    if (Owner->getAttackerForHelper())
                        AttackStart(Owner->getAttackerForHelper());
        }

        //Redefined for random target selection:
        void MoveInLineOfSight(Unit* who)
        {
            if (!me->getVictim() && me->canCreatureAttack(who))
            {
                if (me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                    return;

                float attackRadius = me->GetAttackDistance(who);
                if (me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who))
                {
                    if (!(rand() % 5))
                    {
                        me->setAttackTimer(BASE_ATTACK, (rand() % 10) * 100);
                        SpellTimer = (rand() % 10) * 100;
                        AttackStart(who);
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->getVictim()->HasBreakableByDamageCrowdControlAura(me))
            {
                me->InterruptNonMeleeSpells(false);
                return;
            }

            if (SpellTimer <= diff)
            {
                if (IsViper) //Viper
                {
                    if (urand(0, 2) == 0) //33% chance to cast
                    {
                        uint32 spell;
                        if (urand(0, 1) == 0)
                            spell = SPELL_MIND_NUMBING_POISON;
                        else
                            spell = SPELL_CRIPPLING_POISON;

                        DoCast(me->getVictim(), spell);
                    }

                    SpellTimer = VIPER_TIMER;
                }
                else //Venomous Snake
                {
                    if (urand(0, 2) == 0) //33% chance to cast
                        DoCast(me->getVictim(), SPELL_DEADLY_POISON);
                    SpellTimer = VENOMOUS_SNAKE_TIMER + (rand() % 5) * 100;
                }
            }
            else
                SpellTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_snake_trap_serpentsAI(creature);
    }
};

#define SAY_RANDOM_MOJO0    "Now that's what I call froggy-style!"
#define SAY_RANDOM_MOJO1    "Your lily pad or mine?"
#define SAY_RANDOM_MOJO2    "This won't take long, did it?"
#define SAY_RANDOM_MOJO3    "I thought you'd never ask!"
#define SAY_RANDOM_MOJO4    "I promise not to give you warts..."
#define SAY_RANDOM_MOJO5    "Feelin' a little froggy, are ya?"
#define SAY_RANDOM_MOJO6a   "Listen, "
#define SAY_RANDOM_MOJO6b   ", I know of a little swamp not too far from here...."
#define SAY_RANDOM_MOJO7    "There's just never enough Mojo to go around..."

class mob_mojo : public CreatureScript
{
public:
    mob_mojo() : CreatureScript("mob_mojo") { }

    struct mob_mojoAI : public ScriptedAI
    {
        mob_mojoAI(Creature* creature) : ScriptedAI(creature) {Reset();}
        uint32 hearts;
        uint64 victimGUID;
        void Reset()
        {
            victimGUID = 0;
            hearts = 15000;
            if (Unit* own = me->GetOwner())
                me->GetMotionMaster()->MoveFollow(own, 0, 0);
        }

        void EnterCombat(Unit* /*who*/){}

        void UpdateAI(uint32 diff)
        {
            if (me->HasAura(20372))
            {
                if (hearts <= diff)
                {
                    me->RemoveAurasDueToSpell(20372);
                    hearts = 15000;
                } hearts -= diff;
            }
        }

        void ReceiveEmote(Player* player, uint32 emote)
        {
            me->HandleEmoteCommand(emote);
            Unit* own = me->GetOwner();
            if (!own || own->GetTypeId() != TYPEID_PLAYER || CAST_PLR(own)->GetTeam() != player->GetTeam())
                return;
            if (emote == TEXT_EMOTE_KISS)
            {
                std::string whisp = "";
                switch (rand() % 8)
                {
                    case 0:
                        whisp.append(SAY_RANDOM_MOJO0);
                        break;
                    case 1:
                        whisp.append(SAY_RANDOM_MOJO1);
                        break;
                    case 2:
                        whisp.append(SAY_RANDOM_MOJO2);
                        break;
                    case 3:
                        whisp.append(SAY_RANDOM_MOJO3);
                        break;
                    case 4:
                        whisp.append(SAY_RANDOM_MOJO4);
                        break;
                    case 5:
                        whisp.append(SAY_RANDOM_MOJO5);
                        break;
                    case 6:
                        whisp.append(SAY_RANDOM_MOJO6a);
                        whisp.append(player->GetName());
                        whisp.append(SAY_RANDOM_MOJO6b);
                        break;
                    case 7:
                        whisp.append(SAY_RANDOM_MOJO7);
                        break;
                }

                me->MonsterWhisper(whisp.c_str(), player->GetGUID());
                if (victimGUID)
                    if (Player* victim = Unit::GetPlayer(*me, victimGUID))
                        victim->RemoveAura(43906);//remove polymorph frog thing
                me->AddAura(43906, player);//add polymorph frog thing
                victimGUID = player->GetGUID();
                DoCast(me, 20372, true);//tag.hearts
                me->GetMotionMaster()->MoveFollow(player, 0, 0);
                hearts = 15000;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_mojoAI(creature);
    }
};

class npc_mirror_image : public CreatureScript
{
public:
    npc_mirror_image() : CreatureScript("npc_mirror_image") { }

    struct npc_mirror_imageAI : CasterAI
    {
        npc_mirror_imageAI(Creature* c) : CasterAI(c) {}

        void InitializeAI()
        {
            CasterAI::InitializeAI();
            Unit* owner = me->GetCharmerOrOwner();
            if (!owner)
                return;
            // Inherit Master's Threat List (not yet implemented)
            owner->CastSpell((Unit*)NULL, 58838, true);
            // here mirror image casts on summoner spell (not present in client dbc) 49866
            // here should be auras (not present in client dbc): 35657, 35658, 35659, 35660 selfcasted by mirror images (stats related?)
            // Clone Me!
            owner->CastSpell(me, 45204, false);

            if (owner->ToPlayer() && owner->ToPlayer()->GetSelectedUnit() && me->IsValidAttackTarget(me->GetCharmerOrOwner()->ToPlayer()->GetSelectedUnit()))
                me->AI()->AttackStart(owner->ToPlayer()->GetSelectedUnit());

            targetCheckTimer = 1000;
        }

        void EnterCombat(Unit* who)
        {
            if (spells.empty())
                return;

            for (SpellVct::iterator itr = spells.begin(); itr != spells.end(); ++itr)
            {
                if (AISpellInfo[*itr].condition == AICOND_AGGRO)
                    me->CastSpell(who, *itr, false);
                else if (AISpellInfo[*itr].condition == AICOND_COMBAT)
                {
                    uint32 cooldown = GetAISpellInfo(*itr)->realCooldown;
                    events.ScheduleEvent(*itr, cooldown);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            bool hasCC = false;
            if (me->GetCharmerOrOwnerGUID() && me->getVictim())
                hasCC = me->getVictim()->HasAuraType(SPELL_AURA_MOD_CONFUSE);

            if (hasCC)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    me->CastStop();
                return;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (targetCheckTimer <= diff)
            {
                if (me->GetCharmerOrOwner()->ToPlayer() && me->GetCharmerOrOwner()->ToPlayer()->GetSelectedUnit() && me->IsValidAttackTarget(me->GetCharmerOrOwner()->ToPlayer()->GetSelectedUnit()))
                    me->AI()->AttackStart(me->GetCharmerOrOwner()->ToPlayer()->GetSelectedUnit());
                targetCheckTimer = 1000;
            }
            else
                targetCheckTimer -= diff;

            if (uint32 spellId = events.ExecuteEvent())
            {
                if (hasCC)
                {
                    events.ScheduleEvent(spellId, 500);
                    return;
                }

                DoCast(spellId);
                uint32 casttime = me->GetCurrentSpellCastTime(spellId);
                events.ScheduleEvent(spellId, (casttime ? casttime : 500) + GetAISpellInfo(spellId)->realCooldown);
            }
        }

        // Do not reload Creature templates on evade mode enter - prevent visual lost
        void EnterEvadeMode()
        {
            if (me->IsInEvadeMode() || !me->isAlive())
                return;

            Unit* owner = me->GetCharmerOrOwner();

            me->CombatStop(true);
            if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
            {
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MOTION_SLOT_ACTIVE);
            }
        }

    protected:
        uint16 targetCheckTimer;
    };

    CreatureAI *GetAI(Creature* creature) const
    {
        return new npc_mirror_imageAI(creature);
    }
};

class npc_ebon_gargoyle : public CreatureScript
{
public:
    npc_ebon_gargoyle() : CreatureScript("npc_ebon_gargoyle") { }

    struct npc_ebon_gargoyleAI : CasterAI
    {
        npc_ebon_gargoyleAI(Creature* creature) : CasterAI(creature) {}

        uint32 despawnTimer;

        void InitializeAI()
        {
            CasterAI::InitializeAI();
            uint64 ownerGuid = me->GetOwnerGUID();
            if (!ownerGuid)
                return;
            // Not needed to be despawned now
            despawnTimer = 0;
            // Find victim of Summon Gargoyle spell
            std::list<Unit*> targets;
            Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 30);
            Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(30, searcher);
            for (std::list<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                if ((*iter)->GetAura(49206, ownerGuid))
                {
                    me->Attack((*iter), false);
                    break;
                }
        }

        void JustDied(Unit* /*killer*/)
        {
            // Stop Feeding Gargoyle when it dies
            if (Unit* owner = me->GetOwner())
                owner->RemoveAurasDueToSpell(50514);
        }

        // Fly away when dismissed
        void SpellHit(Unit* source, SpellInfo const* spell)
        {
            if (spell->Id != 50515 || !me->isAlive())
                return;

            Unit* owner = me->GetOwner();

            if (!owner || owner != source)
                return;

            // Stop Fighting
            me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);
            // Sanctuary
            me->CastSpell(me, 54661, true);
            me->SetReactState(REACT_PASSIVE);

            //! HACK: Creature's can't have MOVEMENTFLAG_FLYING
            // Fly Away
            me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY|MOVEMENTFLAG_ASCENDING|MOVEMENTFLAG_FLYING);
            me->SetSpeed(MOVE_FLIGHT, 0.75f, true);
            me->SetSpeed(MOVE_RUN, 0.75f, true);
            float x = me->GetPositionX() + 20 * std::cos(me->GetOrientation());
            float y = me->GetPositionY() + 20 * std::sin(me->GetOrientation());
            float z = me->GetPositionZ() + 40;
            me->GetMotionMaster()->Clear(false);
            me->GetMotionMaster()->MovePoint(0, x, y, z);

            // Despawn as soon as possible
            despawnTimer = 4 * IN_MILLISECONDS;
        }

        void UpdateAI(uint32 diff)
        {
            if (despawnTimer > 0)
            {
                if (despawnTimer > diff)
                    despawnTimer -= diff;
                else
                    me->DespawnOrUnsummon();
                return;
            }
            CasterAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ebon_gargoyleAI(creature);
    }
};

class npc_lightwell : public CreatureScript
{
    public:
        npc_lightwell() : CreatureScript("npc_lightwell") { }

        struct npc_lightwellAI : public PassiveAI
        {
            npc_lightwellAI(Creature* creature) : PassiveAI(creature)
            {
                DoCast(me, 59907, false);
                creature->SetDisplayId(27769);
            }

            void EnterEvadeMode()
            {
                if (!me->isAlive())
                    return;

                me->DeleteThreatList();
                me->CombatStop(true);
                me->ResetPlayerDamageReq();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lightwellAI(creature);
        }
};

enum eTrainingDummy
{
    NPC_ADVANCED_TARGET_DUMMY                  = 2674,
    NPC_TARGET_DUMMY                           = 2673,
    NPC_KILLCREDIT_ORC_CLASSQUESTS             = 44820,
    NPC_KILLCREDIT_GENERAL                     = 44175
};

class npc_training_dummy : public CreatureScript
{
public:
    npc_training_dummy() : CreatureScript("npc_training_dummy") { }

    struct npc_training_dummyAI : ScriptedAI
    {
        npc_training_dummyAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            entry = creature->GetEntry();
        }

        uint32 entry;
        uint32 resetTimer;
        uint32 despawnTimer;

        void Reset()
        {
            me->SetControlled(true, UNIT_STATE_STUNNED);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            resetTimer = 10000;
            despawnTimer = 25000;
        }

        void EnterEvadeMode()
        {
            if (!_EnterEvadeMode())
                return;

            Reset();
        }

        void DamageTaken(Unit* actor, uint32& damage)
        {
            if (actor->GetTypeId() == TYPEID_PLAYER)
            {
                if (actor->ToPlayer()->getClass() == CLASS_PALADIN && actor->HasAura(20154))
                    actor->ToPlayer()->KilledMonsterCredit(44175);
            }

            resetTimer = 10000;
            damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STATE_STUNNED))
                me->SetControlled(true, UNIT_STATE_STUNNED);

            if (entry != NPC_ADVANCED_TARGET_DUMMY && entry != NPC_TARGET_DUMMY)
            {
                if (resetTimer <= diff)
                {
                    EnterEvadeMode();
                    resetTimer = 10000;
                }
                else
                    resetTimer -= diff;
                return;
            }
            else
            {
                if (despawnTimer <= diff)
                    me->DespawnOrUnsummon();
                else
                    despawnTimer -= diff;
            }
        }

        void MoveInLineOfSight(Unit* /*who*/){return;}

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            Player* player = caster->ToPlayer();
            if (!player)
                return;

            switch (spell->Id)
            {
                case 5143:
                case 122:
                case 100:
                case 348:
                case 2098:
                case 73899:
                case 56641:
                case 2061:
                    player->KilledMonsterCredit(NPC_KILLCREDIT_ORC_CLASSQUESTS);
                    player->KilledMonsterCredit(NPC_KILLCREDIT_GENERAL);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_training_dummyAI(creature);
    }
};

/*######
 # npc_shadowfiend
 ######*/

#define GLYPH_OF_SHADOWFIEND_MANA         58227
#define GLYPH_OF_SHADOWFIEND              58228

class npc_shadowfiend: public CreatureScript
{
public:
    npc_shadowfiend() : CreatureScript("npc_shadowfiend") {}

    struct npc_shadowfiendAI: public ScriptedAI
    {
        npc_shadowfiendAI(Creature* creature) : ScriptedAI(creature) {}

        void DamageTaken(Unit* /*killer*/, uint32 &damage)
        {
            if (me->isSummon())
            {
                if (Unit* owner = me->ToTempSummon()->GetSummoner())
                {
                    if (owner->HasAura(GLYPH_OF_SHADOWFIEND))
                    {
                        if (damage >= me->GetHealth())
                            owner->CastSpell(owner, GLYPH_OF_SHADOWFIEND_MANA, true);
                    }
                }
            }
        }

        void UpdateAI(uint32 /*diff*/)
        {
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI (Creature* creature) const
    {
        return new npc_shadowfiendAI(creature);
    }
};

/*######
# npc_fire_elemental
######*/
#define SPELL_FIRENOVA        12470
#define SPELL_FIRESHIELD      13376
#define SPELL_FIREBLAST       57984

class npc_fire_elemental : public CreatureScript
{
public:
    npc_fire_elemental() : CreatureScript("npc_fire_elemental") { }

    struct npc_fire_elementalAI : public ScriptedAI
    {
        npc_fire_elementalAI(Creature* creature) : ScriptedAI(creature) {}

        enum spellId
        {
            SPELL_PASSIVE_PET_AVOIDANCE = 65220
        };

        uint32 FireNova_Timer;
        uint32 FireShield_Timer;
        uint32 FireBlast_Timer;

        void Reset()
        {
            FireNova_Timer = 5000 + rand() % 15000; // 5-20 sec cd
            FireBlast_Timer = 5000 + rand() % 15000; // 5-20 sec cd
            FireShield_Timer = 0;
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (FireShield_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FIRESHIELD);
                FireShield_Timer = 2 * IN_MILLISECONDS;
            }
            else
                FireShield_Timer -= diff;

            if (FireBlast_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FIREBLAST);
                FireBlast_Timer = 5000 + rand() % 15000; // 5-20 sec cd
            }
            else
                FireBlast_Timer -= diff;

            if (FireNova_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FIRENOVA);
                FireNova_Timer = 5000 + rand() % 15000; // 5-20 sec cd
            }
            else
                FireNova_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fire_elementalAI(creature);
    }
};

/*######
# npc_earth_elemental
######*/
#define SPELL_ANGEREDEARTH        36213

class npc_earth_elemental : public CreatureScript
{
public:
    npc_earth_elemental() : CreatureScript("npc_earth_elemental") { }

    struct npc_earth_elementalAI : public ScriptedAI
    {
        npc_earth_elementalAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 AngeredEarth_Timer;

        void Reset()
        {
            AngeredEarth_Timer = 0;
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (AngeredEarth_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_ANGEREDEARTH);
                AngeredEarth_Timer = 5000 + rand() % 15000; // 5-20 sec cd
            }
            else
                AngeredEarth_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_earth_elementalAI(creature);
    }
};

/*######
# npc_wormhole
######*/

#define GOSSIP_ENGINEERING1   "Borean Tundra"
#define GOSSIP_ENGINEERING2   "Howling Fjord"
#define GOSSIP_ENGINEERING3   "Sholazar Basin"
#define GOSSIP_ENGINEERING4   "Icecrown"
#define GOSSIP_ENGINEERING5   "Storm Peaks"
#define GOSSIP_ENGINEERING6   "Underground..."

enum WormholeSpells
{
    SPELL_BOREAN_TUNDRA         = 67834,
    SPELL_SHOLAZAR_BASIN        = 67835,
    SPELL_ICECROWN              = 67836,
    SPELL_STORM_PEAKS           = 67837,
    SPELL_HOWLING_FJORD         = 67838,
    SPELL_UNDERGROUND           = 68081,

    TEXT_WORMHOLE               = 907,

    DATA_SHOW_UNDERGROUND       = 1,
};

class npc_wormhole : public CreatureScript
{
    public:
        npc_wormhole() : CreatureScript("npc_wormhole") {}

        struct npc_wormholeAI : public PassiveAI
        {
            npc_wormholeAI(Creature* creature) : PassiveAI(creature) {}

            void InitializeAI()
            {
                _showUnderground = urand(0, 100) == 0; // Guessed value, it is really rare though
            }

            uint32 GetData(uint32 type) const
            {
                return (type == DATA_SHOW_UNDERGROUND && _showUnderground) ? 1 : 0;
            }

        private:
            bool _showUnderground;
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (creature->isSummon())
            {
                if (player == creature->ToTempSummon()->GetSummoner())
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ENGINEERING1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ENGINEERING2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ENGINEERING3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ENGINEERING4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ENGINEERING5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);

                    if (creature->AI()->GetData(DATA_SHOW_UNDERGROUND))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ENGINEERING6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);

                    player->PlayerTalkClass->SendGossipMenu(TEXT_WORMHOLE, creature->GetGUID());
                }
            }

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1: // Borean Tundra
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player, SPELL_BOREAN_TUNDRA, false);
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2: // Howling Fjord
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player, SPELL_HOWLING_FJORD, false);
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3: // Sholazar Basin
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player, SPELL_SHOLAZAR_BASIN, false);
                    break;
                case GOSSIP_ACTION_INFO_DEF + 4: // Icecrown
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player, SPELL_ICECROWN, false);
                    break;
                case GOSSIP_ACTION_INFO_DEF + 5: // Storm peaks
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player, SPELL_STORM_PEAKS, false);
                    break;
                case GOSSIP_ACTION_INFO_DEF + 6: // Underground
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player, SPELL_UNDERGROUND, false);
                    break;
            }

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_wormholeAI(creature);
        }
};

/*######
## npc_pet_trainer
######*/

enum ePetTrainer
{
    TEXT_ISHUNTER               = 5838,
    TEXT_NOTHUNTER              = 5839,
    TEXT_PETINFO                = 13474,
    TEXT_CONFIRM                = 7722
};

#define GOSSIP_PET1             "How do I train my pet?"
#define GOSSIP_PET2             "I wish to untrain my pet."
#define GOSSIP_PET_CONFIRM      "Yes, please do."

class npc_pet_trainer : public CreatureScript
{
public:
    npc_pet_trainer() : CreatureScript("npc_pet_trainer") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->getClass() == CLASS_HUNTER)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PET1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            if (player->GetPet() && player->GetPet()->getPetType() == HUNTER_PET)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PET2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

            player->PlayerTalkClass->SendGossipMenu(TEXT_ISHUNTER, creature->GetGUID());
            return true;
        }
        player->PlayerTalkClass->SendGossipMenu(TEXT_NOTHUNTER, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->PlayerTalkClass->SendGossipMenu(TEXT_PETINFO, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PET_CONFIRM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->PlayerTalkClass->SendGossipMenu(TEXT_CONFIRM, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                {
                    player->ResetPetTalents();
                    player->CLOSE_GOSSIP_MENU();
                }
                break;
        }
        return true;
    }
};

/*######
## npc_locksmith
######*/

enum eLockSmith
{
    QUEST_HOW_TO_BRAKE_IN_TO_THE_ARCATRAZ = 10704,
    QUEST_DARK_IRON_LEGACY                = 3802,
    QUEST_THE_KEY_TO_SCHOLOMANCE_A        = 5505,
    QUEST_THE_KEY_TO_SCHOLOMANCE_H        = 5511,
    QUEST_HOTTER_THAN_HELL_A              = 10758,
    QUEST_HOTTER_THAN_HELL_H              = 10764,
    QUEST_RETURN_TO_KHAGDAR               = 9837,
    QUEST_CONTAINMENT                     = 13159,
    QUEST_ETERNAL_VIGILANCE               = 11011,
    QUEST_KEY_TO_THE_FOCUSING_IRIS        = 13372,
    QUEST_HC_KEY_TO_THE_FOCUSING_IRIS     = 13375,

    ITEM_ARCATRAZ_KEY                     = 31084,
    ITEM_SHADOWFORGE_KEY                  = 11000,
    ITEM_SKELETON_KEY                     = 13704,
    ITEM_SHATTERED_HALLS_KEY              = 28395,
    ITEM_THE_MASTERS_KEY                  = 24490,
    ITEM_VIOLET_HOLD_KEY                  = 42482,
    ITEM_ESSENCE_INFUSED_MOONSTONE        = 32449,
    ITEM_KEY_TO_THE_FOCUSING_IRIS         = 44582,
    ITEM_HC_KEY_TO_THE_FOCUSING_IRIS      = 44581,

    SPELL_ARCATRAZ_KEY                    = 54881,
    SPELL_SHADOWFORGE_KEY                 = 54882,
    SPELL_SKELETON_KEY                    = 54883,
    SPELL_SHATTERED_HALLS_KEY             = 54884,
    SPELL_THE_MASTERS_KEY                 = 54885,
    SPELL_VIOLET_HOLD_KEY                 = 67253,
    SPELL_ESSENCE_INFUSED_MOONSTONE       = 40173,
};

#define GOSSIP_LOST_ARCATRAZ_KEY                "I've lost my key to the Arcatraz."
#define GOSSIP_LOST_SHADOWFORGE_KEY             "I've lost my key to the Blackrock Depths."
#define GOSSIP_LOST_SKELETON_KEY                "I've lost my key to the Scholomance."
#define GOSSIP_LOST_SHATTERED_HALLS_KEY         "I've lost my key to the Shattered Halls."
#define GOSSIP_LOST_THE_MASTERS_KEY             "I've lost my key to the Karazhan."
#define GOSSIP_LOST_VIOLET_HOLD_KEY             "I've lost my key to the Violet Hold."
#define GOSSIP_LOST_ESSENCE_INFUSED_MOONSTONE   "I've lost my Essence-Infused Moonstone."
#define GOSSIP_LOST_KEY_TO_THE_FOCUSING_IRIS    "I've lost my Key to the Focusing Iris."
#define GOSSIP_LOST_HC_KEY_TO_THE_FOCUSING_IRIS "I've lost my Heroic Key to the Focusing Iris."

class npc_locksmith : public CreatureScript
{
public:
    npc_locksmith() : CreatureScript("npc_locksmith") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        // Arcatraz Key
        if (player->GetQuestRewardStatus(QUEST_HOW_TO_BRAKE_IN_TO_THE_ARCATRAZ) && !player->HasItemCount(ITEM_ARCATRAZ_KEY, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_ARCATRAZ_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        // Shadowforge Key
        if (player->GetQuestRewardStatus(QUEST_DARK_IRON_LEGACY) && !player->HasItemCount(ITEM_SHADOWFORGE_KEY, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_SHADOWFORGE_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        // Skeleton Key
        if ((player->GetQuestRewardStatus(QUEST_THE_KEY_TO_SCHOLOMANCE_A) || player->GetQuestRewardStatus(QUEST_THE_KEY_TO_SCHOLOMANCE_H)) &&
            !player->HasItemCount(ITEM_SKELETON_KEY, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_SKELETON_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        // Shatered Halls Key
        if ((player->GetQuestRewardStatus(QUEST_HOTTER_THAN_HELL_A) || player->GetQuestRewardStatus(QUEST_HOTTER_THAN_HELL_H)) &&
            !player->HasItemCount(ITEM_SHATTERED_HALLS_KEY, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_SHATTERED_HALLS_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

        // Master's Key
        if (player->GetQuestRewardStatus(QUEST_RETURN_TO_KHAGDAR) && !player->HasItemCount(ITEM_THE_MASTERS_KEY, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_THE_MASTERS_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);

        // Violet Hold Key
        if (player->GetQuestRewardStatus(QUEST_CONTAINMENT) && !player->HasItemCount(ITEM_VIOLET_HOLD_KEY, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_VIOLET_HOLD_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);

        // Essence-Infused Moonstone
        if (player->GetQuestRewardStatus(QUEST_ETERNAL_VIGILANCE) && !player->HasItemCount(ITEM_ESSENCE_INFUSED_MOONSTONE, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_ESSENCE_INFUSED_MOONSTONE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);

        // Key to the Focusing Iris
        if (player->GetQuestRewardStatus(QUEST_KEY_TO_THE_FOCUSING_IRIS) && !player->HasItemCount(ITEM_KEY_TO_THE_FOCUSING_IRIS, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_KEY_TO_THE_FOCUSING_IRIS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

        // Heroic Key to the Focusing Iris
        if (player->GetQuestRewardStatus(QUEST_HC_KEY_TO_THE_FOCUSING_IRIS) && !player->HasItemCount(ITEM_HC_KEY_TO_THE_FOCUSING_IRIS, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOST_HC_KEY_TO_THE_FOCUSING_IRIS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_ARCATRAZ_KEY, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_SHADOWFORGE_KEY, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_SKELETON_KEY, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_SHATTERED_HALLS_KEY, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_THE_MASTERS_KEY, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_VIOLET_HOLD_KEY, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_ESSENCE_INFUSED_MOONSTONE, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(ITEM_KEY_TO_THE_FOCUSING_IRIS, 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(ITEM_HC_KEY_TO_THE_FOCUSING_IRIS, 1);
                break;
        }
        return true;
    }
};

/*######
## npc_experience
######*/

#define EXP_COST                100000 //10 00 00 copper (10golds)
#define GOSSIP_TEXT_EXP         14736
#define GOSSIP_XP_OFF           "I no longer wish to gain experience."
#define GOSSIP_XP_ON            "I wish to start gaining experience again."

class npc_experience : public CreatureScript
{
public:
    npc_experience() : CreatureScript("npc_experience") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_XP_OFF, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_XP_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXT_EXP, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        bool noXPGain = player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
        bool doSwitch = false;

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1://xp off
                {
                    if (!noXPGain)//does gain xp
                        doSwitch = true;//switch to don't gain xp
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2://xp on
                {
                    if (noXPGain)//doesn't gain xp
                        doSwitch = true;//switch to gain xp
                }
                break;
        }
        if (doSwitch)
        {
            if (!player->HasEnoughMoney(uint64(EXP_COST)))
                player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
            else if (noXPGain)
            {
                player->ModifyMoney(-int64(EXP_COST));
                player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
            }
            else if (!noXPGain)
            {
                player->ModifyMoney(-EXP_COST);
                player->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
            }
        }
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }
};

enum Fireworks
{
    NPC_OMEN                = 15467,
    NPC_MINION_OF_OMEN      = 15466,
    NPC_FIREWORK_BLUE       = 15879,
    NPC_FIREWORK_GREEN      = 15880,
    NPC_FIREWORK_PURPLE     = 15881,
    NPC_FIREWORK_RED        = 15882,
    NPC_FIREWORK_YELLOW     = 15883,
    NPC_FIREWORK_WHITE      = 15884,
    NPC_FIREWORK_BIG_BLUE   = 15885,
    NPC_FIREWORK_BIG_GREEN  = 15886,
    NPC_FIREWORK_BIG_PURPLE = 15887,
    NPC_FIREWORK_BIG_RED    = 15888,
    NPC_FIREWORK_BIG_YELLOW = 15889,
    NPC_FIREWORK_BIG_WHITE  = 15890,

    NPC_CLUSTER_BLUE        = 15872,
    NPC_CLUSTER_RED         = 15873,
    NPC_CLUSTER_GREEN       = 15874,
    NPC_CLUSTER_PURPLE      = 15875,
    NPC_CLUSTER_WHITE       = 15876,
    NPC_CLUSTER_YELLOW      = 15877,
    NPC_CLUSTER_BIG_BLUE    = 15911,
    NPC_CLUSTER_BIG_GREEN   = 15912,
    NPC_CLUSTER_BIG_PURPLE  = 15913,
    NPC_CLUSTER_BIG_RED     = 15914,
    NPC_CLUSTER_BIG_WHITE   = 15915,
    NPC_CLUSTER_BIG_YELLOW  = 15916,
    NPC_CLUSTER_ELUNE       = 15918,

    GO_FIREWORK_LAUNCHER_1  = 180771,
    GO_FIREWORK_LAUNCHER_2  = 180868,
    GO_FIREWORK_LAUNCHER_3  = 180850,
    GO_CLUSTER_LAUNCHER_1   = 180772,
    GO_CLUSTER_LAUNCHER_2   = 180859,
    GO_CLUSTER_LAUNCHER_3   = 180869,
    GO_CLUSTER_LAUNCHER_4   = 180874,

    SPELL_ROCKET_BLUE       = 26344,
    SPELL_ROCKET_GREEN      = 26345,
    SPELL_ROCKET_PURPLE     = 26346,
    SPELL_ROCKET_RED        = 26347,
    SPELL_ROCKET_WHITE      = 26348,
    SPELL_ROCKET_YELLOW     = 26349,
    SPELL_ROCKET_BIG_BLUE   = 26351,
    SPELL_ROCKET_BIG_GREEN  = 26352,
    SPELL_ROCKET_BIG_PURPLE = 26353,
    SPELL_ROCKET_BIG_RED    = 26354,
    SPELL_ROCKET_BIG_WHITE  = 26355,
    SPELL_ROCKET_BIG_YELLOW = 26356,
    SPELL_LUNAR_FORTUNE     = 26522,

    ANIM_GO_LAUNCH_FIREWORK = 3,
    ZONE_MOONGLADE          = 493,
};

Position omenSummonPos = {7558.993f, -2839.999f, 450.0214f, 4.46f};

class npc_firework : public CreatureScript
{
public:
    npc_firework() : CreatureScript("npc_firework") { }

    struct npc_fireworkAI : public ScriptedAI
    {
        npc_fireworkAI(Creature* creature) : ScriptedAI(creature) {}

        bool isCluster()
        {
            switch (me->GetEntry())
            {
                case NPC_FIREWORK_BLUE:
                case NPC_FIREWORK_GREEN:
                case NPC_FIREWORK_PURPLE:
                case NPC_FIREWORK_RED:
                case NPC_FIREWORK_YELLOW:
                case NPC_FIREWORK_WHITE:
                case NPC_FIREWORK_BIG_BLUE:
                case NPC_FIREWORK_BIG_GREEN:
                case NPC_FIREWORK_BIG_PURPLE:
                case NPC_FIREWORK_BIG_RED:
                case NPC_FIREWORK_BIG_YELLOW:
                case NPC_FIREWORK_BIG_WHITE:
                    return false;
                case NPC_CLUSTER_BLUE:
                case NPC_CLUSTER_GREEN:
                case NPC_CLUSTER_PURPLE:
                case NPC_CLUSTER_RED:
                case NPC_CLUSTER_YELLOW:
                case NPC_CLUSTER_WHITE:
                case NPC_CLUSTER_BIG_BLUE:
                case NPC_CLUSTER_BIG_GREEN:
                case NPC_CLUSTER_BIG_PURPLE:
                case NPC_CLUSTER_BIG_RED:
                case NPC_CLUSTER_BIG_YELLOW:
                case NPC_CLUSTER_BIG_WHITE:
                case NPC_CLUSTER_ELUNE:
                default:
                    return true;
            }
        }

        GameObject* FindNearestLauncher()
        {
            GameObject* launcher = NULL;

            if (isCluster())
            {
                GameObject* launcher1 = GetClosestGameObjectWithEntry(me, GO_CLUSTER_LAUNCHER_1, 0.5f);
                GameObject* launcher2 = GetClosestGameObjectWithEntry(me, GO_CLUSTER_LAUNCHER_2, 0.5f);
                GameObject* launcher3 = GetClosestGameObjectWithEntry(me, GO_CLUSTER_LAUNCHER_3, 0.5f);
                GameObject* launcher4 = GetClosestGameObjectWithEntry(me, GO_CLUSTER_LAUNCHER_4, 0.5f);

                if (launcher1)
                    launcher = launcher1;
                else if (launcher2)
                    launcher = launcher2;
                else if (launcher3)
                    launcher = launcher3;
                else if (launcher4)
                    launcher = launcher4;
            }
            else
            {
                GameObject* launcher1 = GetClosestGameObjectWithEntry(me, GO_FIREWORK_LAUNCHER_1, 0.5f);
                GameObject* launcher2 = GetClosestGameObjectWithEntry(me, GO_FIREWORK_LAUNCHER_2, 0.5f);
                GameObject* launcher3 = GetClosestGameObjectWithEntry(me, GO_FIREWORK_LAUNCHER_3, 0.5f);

                if (launcher1)
                    launcher = launcher1;
                else if (launcher2)
                    launcher = launcher2;
                else if (launcher3)
                    launcher = launcher3;
            }

            return launcher;
        }

        uint32 GetFireworkSpell(uint32 entry)
        {
            switch (entry)
            {
                case NPC_FIREWORK_BLUE:
                    return SPELL_ROCKET_BLUE;
                case NPC_FIREWORK_GREEN:
                    return SPELL_ROCKET_GREEN;
                case NPC_FIREWORK_PURPLE:
                    return SPELL_ROCKET_PURPLE;
                case NPC_FIREWORK_RED:
                    return SPELL_ROCKET_RED;
                case NPC_FIREWORK_YELLOW:
                    return SPELL_ROCKET_YELLOW;
                case NPC_FIREWORK_WHITE:
                    return SPELL_ROCKET_WHITE;
                case NPC_FIREWORK_BIG_BLUE:
                    return SPELL_ROCKET_BIG_BLUE;
                case NPC_FIREWORK_BIG_GREEN:
                    return SPELL_ROCKET_BIG_GREEN;
                case NPC_FIREWORK_BIG_PURPLE:
                    return SPELL_ROCKET_BIG_PURPLE;
                case NPC_FIREWORK_BIG_RED:
                    return SPELL_ROCKET_BIG_RED;
                case NPC_FIREWORK_BIG_YELLOW:
                    return SPELL_ROCKET_BIG_YELLOW;
                case NPC_FIREWORK_BIG_WHITE:
                    return SPELL_ROCKET_BIG_WHITE;
                default:
                    return 0;
            }
        }

        uint32 GetFireworkGameObjectId()
        {
            uint32 spellId = 0;

            switch (me->GetEntry())
            {
                case NPC_CLUSTER_BLUE:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BLUE);
                    break;
                case NPC_CLUSTER_GREEN:
                    spellId = GetFireworkSpell(NPC_FIREWORK_GREEN);
                    break;
                case NPC_CLUSTER_PURPLE:
                    spellId = GetFireworkSpell(NPC_FIREWORK_PURPLE);
                    break;
                case NPC_CLUSTER_RED:
                    spellId = GetFireworkSpell(NPC_FIREWORK_RED);
                    break;
                case NPC_CLUSTER_YELLOW:
                    spellId = GetFireworkSpell(NPC_FIREWORK_YELLOW);
                    break;
                case NPC_CLUSTER_WHITE:
                    spellId = GetFireworkSpell(NPC_FIREWORK_WHITE);
                    break;
                case NPC_CLUSTER_BIG_BLUE:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BIG_BLUE);
                    break;
                case NPC_CLUSTER_BIG_GREEN:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BIG_GREEN);
                    break;
                case NPC_CLUSTER_BIG_PURPLE:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BIG_PURPLE);
                    break;
                case NPC_CLUSTER_BIG_RED:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BIG_RED);
                    break;
                case NPC_CLUSTER_BIG_YELLOW:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BIG_YELLOW);
                    break;
                case NPC_CLUSTER_BIG_WHITE:
                    spellId = GetFireworkSpell(NPC_FIREWORK_BIG_WHITE);
                    break;
                case NPC_CLUSTER_ELUNE:
                    spellId = GetFireworkSpell(urand(NPC_FIREWORK_BLUE, NPC_FIREWORK_WHITE));
                    break;
            }

            const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(spellId);

            if (spellInfo && spellInfo->Effects[0].Effect == SPELL_EFFECT_SUMMON_OBJECT_WILD)
                return spellInfo->Effects[0].MiscValue;

            return 0;
        }

        void Reset()
        {
            if (GameObject* launcher = FindNearestLauncher())
            {
                launcher->SendCustomAnim(ANIM_GO_LAUNCH_FIREWORK);
                me->SetOrientation(launcher->GetOrientation() + M_PI/2);
            }
            else
                return;

            if (isCluster())
            {
                // Check if we are near Elune'ara lake south, if so try to summon Omen or a minion
                if (me->GetZoneId() == ZONE_MOONGLADE)
                {
                    if (!me->FindNearestCreature(NPC_OMEN, 100.0f, false) && me->GetDistance2d(omenSummonPos.GetPositionX(), omenSummonPos.GetPositionY()) <= 100.0f)
                    {
                        switch (urand(0, 9))
                        {
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                                if (Creature* minion = me->SummonCreature(NPC_MINION_OF_OMEN, me->GetPositionX()+frand(-5.0f, 5.0f), me->GetPositionY()+frand(-5.0f, 5.0f), me->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 20000))
                                    minion->AI()->AttackStart(me->SelectNearestPlayer(20.0f));
                                break;
                            case 9:
                                me->SummonCreature(NPC_OMEN, omenSummonPos);
                                break;
                        }
                    }
                }
                if (me->GetEntry() == NPC_CLUSTER_ELUNE)
                    DoCast(SPELL_LUNAR_FORTUNE);

                float displacement = 0.7f;
                for (uint8 i = 0; i < 4; i++)
                    me->SummonGameObject(GetFireworkGameObjectId(), me->GetPositionX() + (i%2 == 0 ? displacement : -displacement), me->GetPositionY() + (i > 1 ? displacement : -displacement), me->GetPositionZ() + 4.0f, me->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 1);
            }
            else
                //me->CastSpell(me, GetFireworkSpell(me->GetEntry()), true);
                me->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), GetFireworkSpell(me->GetEntry()), true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fireworkAI(creature);
    }
};

/*#####
# npc_spring_rabbit
#####*/

enum rabbitSpells
{
    SPELL_SPRING_FLING          = 61875,
    SPELL_SPRING_RABBIT_JUMP    = 61724,
    SPELL_SPRING_RABBIT_WANDER  = 61726,
    SPELL_SUMMON_BABY_BUNNY     = 61727,
    SPELL_SPRING_RABBIT_IN_LOVE = 61728,
    NPC_SPRING_RABBIT           = 32791
};

class npc_spring_rabbit : public CreatureScript
{
public:
    npc_spring_rabbit() : CreatureScript("npc_spring_rabbit") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_spring_rabbitAI(creature);
    }

    struct npc_spring_rabbitAI : public ScriptedAI
    {
        npc_spring_rabbitAI(Creature* creature) : ScriptedAI(creature) { }

        bool inLove;
        uint32 jumpTimer;
        uint32 bunnyTimer;
        uint32 searchTimer;
        uint64 rabbitGUID;

        void Reset()
        {
            inLove = false;
            rabbitGUID = 0;
            jumpTimer = urand(5000, 10000);
            bunnyTimer = urand(10000, 20000);
            searchTimer = urand(5000, 10000);
            if (Unit* owner = me->GetOwner())
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        }

        void EnterCombat(Unit* /*who*/) { }

        void DoAction(int32 /*param*/)
        {
            inLove = true;
            if (Unit* owner = me->GetOwner())
                owner->CastSpell(owner, SPELL_SPRING_FLING, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (inLove)
            {
                if (jumpTimer <= diff)
                {
                    if (Unit* rabbit = Unit::GetUnit(*me, rabbitGUID))
                        DoCast(rabbit, SPELL_SPRING_RABBIT_JUMP);
                    jumpTimer = urand(5000, 10000);
                } else jumpTimer -= diff;

                if (bunnyTimer <= diff)
                {
                    DoCast(SPELL_SUMMON_BABY_BUNNY);
                    bunnyTimer = urand(20000, 40000);
                } else bunnyTimer -= diff;
            }
            else
            {
                if (searchTimer <= diff)
                {
                    if (Creature* rabbit = me->FindNearestCreature(NPC_SPRING_RABBIT, 10.0f))
                    {
                        if (rabbit == me || rabbit->HasAura(SPELL_SPRING_RABBIT_IN_LOVE))
                            return;

                        me->AddAura(SPELL_SPRING_RABBIT_IN_LOVE, me);
                        DoAction(1);
                        rabbit->AddAura(SPELL_SPRING_RABBIT_IN_LOVE, rabbit);
                        rabbit->AI()->DoAction(1);
                        rabbit->CastSpell(rabbit, SPELL_SPRING_RABBIT_JUMP, true);
                        rabbitGUID = rabbit->GetGUID();
                    }
                    searchTimer = urand(5000, 10000);
                } else searchTimer -= diff;
            }
        }
    };
};

/*######
## npc_generic_harpoon_cannon
######*/

class npc_generic_harpoon_cannon : public CreatureScript
{
public:
    npc_generic_harpoon_cannon() : CreatureScript("npc_generic_harpoon_cannon") { }

    struct npc_generic_harpoon_cannonAI : public ScriptedAI
    {
        npc_generic_harpoon_cannonAI(Creature* creature) : ScriptedAI(creature) {}

        void OnCharmed(bool apply) {}

        void Reset()
        {
            if (!me->HasUnitMovementFlag(MOVEMENTFLAG_ROOT))
                me->SetUnitMovementFlags(MOVEMENTFLAG_ROOT);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_generic_harpoon_cannonAI(creature);
    }
};

/*######
## npc_shadowy_apparition
######*/

class npc_shadowy_apparition : public CreatureScript
{
public:
    npc_shadowy_apparition() : CreatureScript("npc_shadowy_apparition") { }

    enum spellId
    {
        SPELL_SHADOWY_APPARITION_CLONE_CASTER        = 87213,
        SPELL_SHADOWY_APPARITION_DEATH_VISUAL        = 87529,
        SPELL_SHADOWY_APPARITION_DAMAGE              = 87532,
        SPELL_SHADOWY_APPARITION_VISUAL              = 87427,
        SPELL_SHADOW_WORD_PAIN                       = 589
    };

    struct npc_shadowy_apparitionAI : public ScriptedAI
    {
        npc_shadowy_apparitionAI(Creature* c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            hit = false;
        }

        uint64 targetGuid;
        bool hit;

        void InitializeAI()
        {
            Unit* owner = me->GetOwner();
            if (!owner)
                return;

            owner->CastSpell(me, SPELL_SHADOWY_APPARITION_CLONE_CASTER);

            if (me->GetCharmInfo())
            {
                me->GetCharmInfo()->SetIsAtStay(true);
                me->GetCharmInfo()->SetIsFollowing(false);
                me->GetCharmInfo()->SetIsReturning(false);
            }
            hit = false;
            me->SetWalk(true);
            me->SetSpeed(MOVE_WALK, 0.75f, true);
        }

        void EnterEvadeMode() {return;}

        void MoveInLineOfSight(Unit* who)
        {
            if (who->IsHostileTo(me) && me->GetDistance(who) <= 1.0f)
            {
                uint64 ownerGuid = 0;
                if (Unit* charmerOwner = me->GetCharmerOrOwner())
                    ownerGuid = charmerOwner->GetGUID();

                if (hit == false)
                {
                    hit = true;
                    me->CastCustomSpell(who, SPELL_SHADOWY_APPARITION_DAMAGE, NULL, NULL, NULL, false, 0, 0, ownerGuid);
                    me->CastSpell(me, SPELL_SHADOWY_APPARITION_DEATH_VISUAL);
                    me->DisappearAndDie();
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                Unit* owner = me->GetCharmerOrOwner();
                if (!owner)
                    return;

                UnitList targets;
                Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(owner, owner, 100.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(owner, targets, u_check);
                owner->VisitNearbyObject(100.0f, searcher);
                for (UnitList::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if (!(*itr)->HasAura(SPELL_SHADOW_WORD_PAIN, owner->GetGUID()))
                        continue;

                    me->Attack((*itr), false);
                    me->AddThreat((*itr), 10000.0f);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveChase((*itr), 1.0f, 0.0f);
                    targetGuid = (*itr)->GetGUID();
                }
            }

            if (Unit* owner = me->GetCharmerOrOwner())
            {
                UnitList targets;
                Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(owner, owner, 100.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(owner, targets, u_check);
                owner->VisitNearbyObject(100.0f, searcher);
                for (UnitList::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if (me->IsWithinDistInMap((*itr), 1.0f))
                    {
                        me->CastSpell((*itr), SPELL_SHADOWY_APPARITION_DAMAGE, false, 0, 0, owner->GetGUID());
                        me->CastSpell(me, SPELL_SHADOWY_APPARITION_VISUAL, false);
                        me->DespawnOrUnsummon();
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowy_apparitionAI(creature);
    }
};

class npc_bloodworm: public CreatureScript
{
public:
    npc_bloodworm () : CreatureScript("npc_bloodworm") { }

    struct npc_bloodwormAI: public ScriptedAI
    {
        npc_bloodwormAI (Creature *c) : ScriptedAI(c)
        {
            alive = true;
            uiDespawnTimer = 19500;
        }

        bool alive;
        uint32 uiDespawnTimer;

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
            // Start attacking attacker of owner on first ai update after spawn - move in line of sight may choose better target
            if (!me->getVictim() && me->isSummon())
            {
                if (Unit* owner = me->ToTempSummon()->GetSummoner())
                {
                    if (owner->getAttackerForHelper())
                    {
                        AttackStart(owner->getAttackerForHelper());
                        me->AddThreat(owner->getAttackerForHelper(), 100.0f);
                    }
                }
            }
        }

        //Redefined for random target selection:
        void MoveInLineOfSight(Unit* who)
        {
            if (!me->getVictim() && me->canCreatureAttack(who))
            {
                if (me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                    return;

                float attackRadius = me->GetAttackDistance(who);
                if (me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who))
                {
                    if (!(rand() % 5))
                    {
                        me->setAttackTimer(BASE_ATTACK, (rand() % 10) * 100);
                        AttackStart(who);
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (uiDespawnTimer <= diff)
            {
                if (me->HasAura(81277) && alive)
                {
                    alive = false;
                    int32 amount = me->GetAura(81277)->GetStackAmount() * 10;
                    me->CastCustomSpell(me,81280,&amount,NULL,NULL,true);
                    me->DisappearAndDie();
                }
            }
            else
                uiDespawnTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI *GetAI (Creature *creature) const
    {
        return new npc_bloodwormAI(creature);
    }
};

class npc_ring_of_frost : public CreatureScript
{
public:
    npc_ring_of_frost() : CreatureScript("npc_ring_of_frost") { }

    enum eventId
    {
        EVENT_FULLY_FORMED = 1,
        EVENT_RECAST
    };

    enum spellId
    {
        SPELL_RING_OF_FROST_TRIGGERED   = 82691
    };

    struct npc_ring_of_frostAI : public ScriptedAI
    {
        npc_ring_of_frostAI(Creature *creature) : ScriptedAI(creature) {}

        EventMap events;

        void InitializeAI()
        {
            ScriptedAI::InitializeAI();
            Unit* owner = me->GetOwner();
            if (!owner || owner->GetTypeId() != TYPEID_PLAYER)
                return;

            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            events.ScheduleEvent(EVENT_FULLY_FORMED, 3000);
            isFormed = false;

            // Remove other ring spawned by the player
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);
            {
                CellCoord pair(Trinity::ComputeCellCoord(x, y));
                Cell cell(pair);
                cell.SetNoCreate();

                Trinity::AllFriendlyCreaturesInGrid check(me);
                Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> searcher(me, templist, check);

                TypeContainerVisitor<Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid>, GridTypeMapContainer> cSearcher(searcher);

                cell.Visit(pair, cSearcher, *(me->GetMap()), *me, me->GetGridActivationRange());

                if (!templist.empty())
                    for (std::list<Creature*>::const_iterator itr = templist.begin(); itr != templist.end(); ++itr)
                        if((*itr)->GetEntry() == me->GetEntry() && ((*itr)->GetOwner() == me->GetOwner() && *itr != me))
                            (*itr)->DisappearAndDie();
                templist.clear();
            }
        }

        void EnterEvadeMode() { return; }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FULLY_FORMED:
                    {
                        if (isFormed == false)
                        {
                            isFormed = true;
                            events.RescheduleEvent(EVENT_FULLY_FORMED, 9000);
                            events.ScheduleEvent(EVENT_RECAST, 1);
                        }
                        else
                        {
                            events.Reset();
                            me->DisappearAndDie();
                        }
                        break;
                    }
                    case EVENT_RECAST:
                    {
                        if (isFormed == true)
                            DoCast(me, SPELL_RING_OF_FROST_TRIGGERED, true);
                        events.RescheduleEvent(EVENT_RECAST, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        protected:
            bool isFormed;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ring_of_frostAI(creature);
    }
};

// Flame Orb
enum FlameOrb
{
    SPELL_FLAME_ORB_DAMAGE          = 86719,
    FLAME_ORB_DISTANCE              = 120,
    TALENT_FIRE_POWER_R1            = 18459,
    TALENT_FIRE_POWER_R2            = 18460,
    TALENT_FIRE_POWER_R3            = 54734,
    SPELL_FIRE_POWER_TRIGGERED      = 83619
};

class npc_flame_orb : public CreatureScript
{
public:
    npc_flame_orb() : CreatureScript("npc_flame_orb") {}

    struct npc_flame_orbAI : public ScriptedAI
    {
        npc_flame_orbAI(Creature *creature) : ScriptedAI(creature)
        {
            x = me->GetPositionX();
            y = me->GetPositionY();
            z = me->GetOwner()->GetPositionZ()+2;
            o = me->GetOrientation();
            me->NearTeleportTo(x, y, z, o, true);
            me->SetDisableGravity(true);
            angle = me->GetOwner()->GetAngle(me);
            newx = me->GetPositionX() + FLAME_ORB_DISTANCE/2 * cos(angle);
            newy = me->GetPositionY() + FLAME_ORB_DISTANCE/2 * sin(angle);
            CombatCheck = false;
        }

        float x, y, z, o, newx, newy, angle;
        bool CombatCheck;
        uint32 DespawnTimer;
        uint32 DespawnCheckTimer;
        uint32 DamageTimer;

        void EnterCombat(Unit* /*target*/)
        {
            me->GetMotionMaster()->MoveCharge(newx, newy, z, 1.14286f);  // Normal speed
            DespawnTimer = 15 * IN_MILLISECONDS;
            CombatCheck = true;
        }

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
            me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
            me->SetReactState(REACT_PASSIVE);
            if (CombatCheck == true)
                DespawnTimer = 15 * IN_MILLISECONDS;
            else
                DespawnTimer = 4 * IN_MILLISECONDS;
            DamageTimer = 1 * IN_MILLISECONDS;
            me->GetMotionMaster()->MovePoint(0, newx, newy, z);
        }

        void UpdateAI(uint32 diff)
        {
            Unit* owner = me->GetOwner();
            if (!me->isInCombat() && CombatCheck == false)
            {
                me->SetSpeed(MOVE_RUN, 0.75f, true);
                me->SetSpeed(MOVE_FLIGHT, 0.75f, true);
            }

            if (DespawnTimer <= diff)
            {
                if (owner)
                {
                    if (owner->HasAura(TALENT_FIRE_POWER_R1) && roll_chance_i(33))
                        DoCast(me, SPELL_FIRE_POWER_TRIGGERED, true);
                    else if (owner->HasAura(TALENT_FIRE_POWER_R2) && roll_chance_i(66))
                        DoCast(me, SPELL_FIRE_POWER_TRIGGERED, true);
                    else if (owner->HasAura(TALENT_FIRE_POWER_R3))
                        DoCast(me, SPELL_FIRE_POWER_TRIGGERED, true);
                }
                me->SetVisible(false);
                me->DisappearAndDie();
            }
            else
                DespawnTimer -= diff;

            if (DamageTimer <= diff)
            {
                if (Unit* target = me->SelectNearestTarget(20))
                    DoCast(target, SPELL_FLAME_ORB_DAMAGE);

                DamageTimer = 1 * IN_MILLISECONDS;
            }
            else
                DamageTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_flame_orbAI(creature);
    }
};

// Frostfire Orb
enum FrostfireOrb
{
    SPELL_FROSTFIRE_ORB_DAMAGE_RANK_1   = 95969,
    SPELL_FROSTFIRE_ORB_DAMAGE_RANK_2   = 84721,
    FROSTFIRE_ORB_DISTANCE              = 120
};

class npc_frostfire_orb : public CreatureScript
{
public:
    npc_frostfire_orb() : CreatureScript("npc_frostfire_orb") {}

    struct npc_frostfire_orbAI : public ScriptedAI
    {
        npc_frostfire_orbAI(Creature* creature) : ScriptedAI(creature)
        {
            x = me->GetPositionX();
            y = me->GetPositionY();
            z = me->GetOwner()->GetPositionZ()+2;
            o = me->GetOrientation();
            me->NearTeleportTo(x, y, z, o, true);
            me->SetDisableGravity(true);
            angle = me->GetOwner()->GetAngle(me);
            newx = me->GetPositionX() + FROSTFIRE_ORB_DISTANCE/2 * cos(angle);
            newy = me->GetPositionY() + FROSTFIRE_ORB_DISTANCE/2 * sin(angle);
            CombatCheck = false;
        }

        float x,y,z,o,newx,newy,angle;
        bool CombatCheck;
        uint32 despawnTimer;
        uint32 despawnCheckTimer;
        uint32 damageTimer;

        void EnterCombat(Unit* /*target*/)
        {
            me->GetMotionMaster()->MoveCharge(newx, newy, z, 1.14286f); // Normal speed
            despawnTimer = 15 * IN_MILLISECONDS;
            CombatCheck = true;
        }

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
            me->SetReactState(REACT_PASSIVE);
            if (CombatCheck == true)
                despawnTimer = 15 * IN_MILLISECONDS;
            else
                despawnTimer = 4 * IN_MILLISECONDS;
            damageTimer = 1 * IN_MILLISECONDS;
            me->GetMotionMaster()->MovePoint(0, newx, newy, z);
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isInCombat() && CombatCheck == false)
            {
                me->SetSpeed(MOVE_RUN, 1, true);
                me->SetSpeed(MOVE_FLIGHT, 1, true);
            }

            if (despawnTimer <= diff)
                me->DisappearAndDie();
            else
                despawnTimer -= diff;

            if (damageTimer <= diff)
            {
                if (Unit* target = me->SelectNearestTarget(20))
                {
                    if (me->GetOwner()->HasAura(84726))
                        DoCast(target, SPELL_FROSTFIRE_ORB_DAMAGE_RANK_1);
                    else
                        DoCast(target, SPELL_FROSTFIRE_ORB_DAMAGE_RANK_2);
                }
                damageTimer = 1 * IN_MILLISECONDS;
            }
            else
                damageTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frostfire_orbAI(creature);
    }
};

class npc_fungal_growth : public CreatureScript
{
public:
    npc_fungal_growth() : CreatureScript("npc_fungal_growth") {}

    struct npc_fungal_growthAI : public ScriptedAI
    {
        npc_fungal_growthAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            // Fungal Growth I
            switch (me->GetEntry())
            {
                case 43497: // Fungal Growth I
                {
                    if (!me->HasAura(81289))
                    {
                        me->CastSpell(me, 81289);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        me->GetMotionMaster()->Clear();
                        return;
                    }
                    break;
                }
                case 43484: // Fungal Growth II
                {
                    if (!me->HasAura(81282))
                    {
                        me->CastSpell(me, 81282);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        me->GetMotionMaster()->Clear();
                        return;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fungal_growthAI(creature);
    }
};

class npc_hand_of_gul_dan : public CreatureScript
{
public:
    npc_hand_of_gul_dan() : CreatureScript("npc_hand_of_gul_dan") {}

    struct npc_hand_of_gul_danAI : public ScriptedAI
    {
        npc_hand_of_gul_danAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            timerEffect = 800;
            timerStun = 6000;
        }

        void IsSummonedBy(Unit* owner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_ATTACKABLE_1);
            me->SetControlled(true, UNIT_STATE_ROOT);
        }

        void UpdateAI(uint32 diff)
        {
            Unit* owner = me->ToTempSummon()->GetSummoner();
            if (!owner)
                return;

            if (timerEffect <= diff)
            {
                // Hand of Gul'Dan effect
                if (!me->HasAura(85526))
                {
                    owner->AddAura(85526, me);
                    timerEffect = 16000;
                }

                // Find all the enemies
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 4.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(4.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && ((*itr)->IsFriendlyTo(owner) || (*itr) == owner) || (*itr) == me)
                        continue;

                    // Aura of Foreboding (Root effect)
                    if (owner->HasAura(89604))
                        owner->AddAura(93974, (*itr));
                    else if (owner->HasAura(89605))
                        owner->AddAura(93987, (*itr));
                }
            }
            else
                timerEffect -= diff;

            if (timerStun <= diff)
            {
                // Find all the enemies
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 4.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(4.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && ((*itr)->IsFriendlyTo(owner) || (*itr) == owner) || (*itr) == me)
                        continue;

                    // Aura of Foreboding (Stun effect)
                    if (owner->HasAura(89604))
                        owner->AddAura(93975, (*itr));
                    else if (owner->HasAura(89605))
                        owner->AddAura(93986, (*itr));
                }
                timerStun = 15000;
            }
            else
                timerStun -= diff;
        }

    protected:
        uint32 timerEffect;
        uint32 timerStun;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hand_of_gul_danAI(creature);
    }
};

class npc_grounding_totem : public CreatureScript
{
public:
    npc_grounding_totem() : CreatureScript("npc_grounding_totem") {}

    struct npc_grounding_totemAI : public ScriptedAI
    {
        npc_grounding_totemAI(Creature* creature) : ScriptedAI(creature) { }

        enum spellId
        {
            SPELL_MAGE_POLYMORPH    = 118,
            SPELL_DK_DEATH_GRIP     = 49560
        };

        void Reset()
        {
            if (Unit* owner = me->GetCharmerOrOwner())
            {
                // Glyph of Grounding Totem
                if (owner->HasAura(55441) && !me->HasAura(89523))
                    me->AddAura(89523, me);
                else
                {
                    if (!me->HasAura(8178))
                        me->AddAura(8178, me);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            me->DisappearAndDie();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_grounding_totemAI(creature);
    }
};

class npc_eye_of_kilrogg : public CreatureScript
{
public:
    npc_eye_of_kilrogg() : CreatureScript("npc_eye_of_kilrogg") {}

    struct npc_eye_of_kilroggAI : public ScriptedAI
    {
        npc_eye_of_kilroggAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            if (Unit* owner = me->GetCharmerOrOwner())
            {
                // Glyph of Eye of Kilrogg
                if (owner->HasAura(58081))
                {
                    if (AreaTableEntry const* area = GetAreaEntryByAreaID(me->GetAreaId()))
                    {
                        if (area->flags & AREA_FLAG_NO_FLY_ZONE)
                            me->SetCanFly(false);
                        else
                            me->SetCanFly(true);
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_eye_of_kilroggAI(creature);
    }
};

enum TentacleMisc
{
    EVENT_MIND_FLAY = 1,
    SPELL_MIND_FLAY = 52586,
};

class npc_tentacle_of_the_old : public CreatureScript
{
public:
    npc_tentacle_of_the_old() : CreatureScript("npc_tentacle_of_the_old") { }

    struct npc_tentacle_of_the_oldAI : public ScriptedAI
    {
        npc_tentacle_of_the_oldAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;
        Unit* player;

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                player = summoner;
                events.ScheduleEvent(EVENT_MIND_FLAY, 500);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MIND_FLAY:
                        DoCast(player->getVictim(), SPELL_MIND_FLAY);
                        events.ScheduleEvent(EVENT_MIND_FLAY, 2000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tentacle_of_the_oldAI(creature);
    }
};

// WARNING: Following script is needed only for areatriggers that actually doesn't work when you walk into zone
class npc_generic_areatrigger : public CreatureScript
{
public:
    npc_generic_areatrigger() : CreatureScript("npc_generic_areatrigger") {}

    struct npc_generic_areatriggerAI : public ScriptedAI
    {
        npc_generic_areatriggerAI(Creature* creature) : ScriptedAI(creature) { }

        enum Id
        {
            // GUID
            AT_ZONE_DREADWATCH_OUTPOST          = 706246, AT_ZONE_GILNEAS_LIBERATION_FRONT_BASE_CAMP  = 706301,
            AT_ZONE_THE_BATTLEFRONT             = 706302, AT_ZONE_FALDIR_COVE                         = 706686,
            AT_ZONE_SLUDGE_FIELDS_1             = 706483, AT_ZONE_LAKESHIRE_BRIDGE                    = 706107,
            AT_ZONE_SCAR_OF_THE_WORLDBREAKER    = 706426, AT_ZONE_NORTHWATCH_HOLD                     = 705737,
            AT_ZONE_NEDLEROCK_SLAG_1            = 830014, AT_ZONE_NEDLEROCK_SLAG_2                    = 830015,

            // Quest
            QUEST_BREAK_IN_COMMUNICATIONS_DREADWATCH_OUTPOST = 27349, QUEST_BREAK_IN_COMMUNICATIONS_RUTSAK_GUARD    = 27350,
            QUEST_ON_HER_MAJESTY_SECRET_SERVICE              = 27594, QUEST_CITIES_IN_DUST                          = 27601,
            QUEST_DEATH_FROM_BELOW                           = 26628, QUEST_BURNSIDE_MUST_FALL                      = 28235,
            QUEST_A_BLIGHT_UPON_THE_LAND                     = 28237, QUEST_TDDC_WHAT_REALLY_HAPPENED               = 27715,

            // Npc
            NPC_ENTRY_LORNA_CROWLEY             = 45997, NPC_ENTRY_LORD_GODFREY              = 45878,
            NPC_ENTRY_LORD_WALDEN               = 45879, NPC_ENTRY_LORD_ASHBURY              = 45880,
            NPC_ENTRY_LADY_SYLVANAS             = 46026, NPC_ENTRY_CROMUSH                   = 46031,
            NPC_ENTRY_ARTHURA                   = 46032, NPC_ENTRY_DASCHLA                   = 46033,
            NPC_ENTRY_AGATHA                    = 46034, NPC_ENTRY_DAGGERSPINE_MARAUDER      = 2775,
            NPC_ENTRY_SHAKES                    = 2610,  NPC_ENTRY_WARDEN_STILLWATER         = 48080,
            NPC_ENTRY_WARDEN_LYADON             = 48020, NPC_ENTRY_WARDEN_MONSTER            = 47834,
            NPC_ENTRY_STONARD_OGRE              = 46765, NPC_ENTRY_MARTEK_HOG                = 46501,
            NPC_ENTRY_RAGEROAR_ROWBOAT          = 38747, NPC_ENTRY_STONETROG_REINFORCEMENT   = 43960,
            NPC_ENTRY_FUNGAL_TERROR             = 43954,

            // Spell
            SPELL_SUMMON_CROWLEY        = 85877, SPELL_SUMMON_BLOODFANG      = 85878,
            SPELL_SUMMON_JOHNNY_LYDON   = 89293, SPELL_CONTROLLER            = 103067
        };

        void Reset()
        {
            actTimer = 8*IN_MILLISECONDS;
            summonTimer = 20*IN_MILLISECONDS;
            ogreTimer = 8*IN_MILLISECONDS;
            boatTimer = 8*IN_MILLISECONDS;
            reinforcementsTimer = 2*IN_MILLISECONDS;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
        }

        void UpdateAI(uint32 diff)
        {
            switch (me->GetGUIDLow())
            {
                case AT_ZONE_NEDLEROCK_SLAG_1:
                {
                    if (reinforcementsTimer <= diff)
                    {
                        if (roll_chance_f(75))
                            me->SummonCreature(NPC_ENTRY_STONETROG_REINFORCEMENT, me->GetPositionX()-(urand(1, 2)), me->GetPositionY()-(urand(1, 2)), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);
                        else
                            me->SummonCreature(NPC_ENTRY_FUNGAL_TERROR, me->GetPositionX()-(urand(1, 2)), me->GetPositionY()-(urand(1, 2)), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);

                        reinforcementsTimer = 3*IN_MILLISECONDS;
                    }
                    else
                        reinforcementsTimer -= diff;
                    break;
                }
                case AT_ZONE_NEDLEROCK_SLAG_2:
                {
                    if (reinforcementsTimer <= diff)
                    {
                        if (roll_chance_f(75))
                            me->SummonCreature(NPC_ENTRY_FUNGAL_TERROR, me->GetPositionX()+(urand(1, 2)), me->GetPositionY()+(urand(1, 2)), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);
                        else
                            me->SummonCreature(NPC_ENTRY_STONETROG_REINFORCEMENT, me->GetPositionX()+(urand(1, 2)), me->GetPositionY()+(urand(1, 2)), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);

                        reinforcementsTimer = 3*IN_MILLISECONDS;
                    }
                    else
                        reinforcementsTimer -= diff;
                    break;
                }
                default:
                    break;
            }
            // Stonard Battle
            if (me->GetMapId() == 0 && me->GetZoneId() == 8 && me->GetAreaId() == 5460)
            {
                if (ogreTimer <= diff)
                {
                    me->SummonCreature(NPC_ENTRY_STONARD_OGRE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                    ogreTimer = 8*IN_MILLISECONDS;
                }
                else
                    ogreTimer -= diff;
            }

            // Nortwatch Hold
            if (me->GetMapId() == 1 && me->GetZoneId() == 4709 && me->GetAreaId() == 4709 && me->GetGUIDLow() == AT_ZONE_NORTHWATCH_HOLD)
            {
                if (boatTimer <= diff)
                {
                    me->SummonCreature(NPC_ENTRY_RAGEROAR_ROWBOAT, -1886.15f, -3798.26f, 0.99f, 3.60f, TEMPSUMMON_TIMED_DESPAWN, 45000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    me->SummonCreature(NPC_ENTRY_RAGEROAR_ROWBOAT, -1893.88f, -3782.64f, 0.99f, 3.60f, TEMPSUMMON_TIMED_DESPAWN, 45000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    me->SummonCreature(NPC_ENTRY_RAGEROAR_ROWBOAT, -1902.75f, -3764.70f, 0.99f, 3.60f, TEMPSUMMON_TIMED_DESPAWN, 45000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                    boatTimer = 8*IN_MILLISECONDS;
                }
                else
                    boatTimer -= diff;
            }

            if (summonTimer <= diff)
            {
                std::list<Unit*> targets;
                Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 250.0f);
                Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(250.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    Player* longfarPlayer = (*itr)->ToPlayer();
                    if (!longfarPlayer)
                        continue;

                    switch (me->GetGUIDLow())
                    {
                        case AT_ZONE_FALDIR_COVE:
                        {
                            if (longfarPlayer->GetQuestStatus(QUEST_DEATH_FROM_BELOW) == QUEST_STATUS_INCOMPLETE)
                            {
                                longfarPlayer->SummonCreature(NPC_ENTRY_DAGGERSPINE_MARAUDER, -2156.57f, -1970.36f, 15.39f, 5.46f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                                longfarPlayer->SummonCreature(NPC_ENTRY_DAGGERSPINE_MARAUDER, -2158.44f, -1972.10f, 15.71f, 5.46f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                                longfarPlayer->SummonCreature(NPC_ENTRY_DAGGERSPINE_MARAUDER, -2154.77f, -1968.69f, 15.45f, 5.46f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                            }
                            if (Creature* shakes = me->FindNearestCreature(NPC_ENTRY_SHAKES, 500.0f, true))
                                shakes->AI()->Talk(1);
                            break;
                        }
                        default:
                            break;
                    }
                }
                summonTimer = 60000;
            }
            else
               summonTimer -= diff;

            if (actTimer <= diff)
            {
                std::list<Unit*> targets;
                Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 50.0f);
                Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(50.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    Player* nearestPlayer = (*itr)->ToPlayer();
                    if (!nearestPlayer)
                        continue;

                    // Exclude GM's
                    if (nearestPlayer->isGameMaster())
                        continue;

                    // Check for correct AreaTrigger using GUID!
                    switch (me->GetGUIDLow())
                    {
                        case AT_ZONE_DREADWATCH_OUTPOST:
                        {
                            if (nearestPlayer->GetQuestStatus(QUEST_BREAK_IN_COMMUNICATIONS_DREADWATCH_OUTPOST) == QUEST_STATUS_INCOMPLETE)
                                nearestPlayer->CompleteQuest(QUEST_BREAK_IN_COMMUNICATIONS_DREADWATCH_OUTPOST);
                            if (nearestPlayer->GetQuestStatus(QUEST_BREAK_IN_COMMUNICATIONS_DREADWATCH_OUTPOST) == QUEST_STATUS_REWARDED)
                            {
                                if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_BREAK_IN_COMMUNICATIONS_RUTSAK_GUARD))
                                {
                                    if (nearestPlayer->IsActiveQuest(QUEST_BREAK_IN_COMMUNICATIONS_RUTSAK_GUARD) || nearestPlayer->GetQuestStatus(QUEST_BREAK_IN_COMMUNICATIONS_RUTSAK_GUARD) == QUEST_STATUS_REWARDED)
                                        return;
                                    else
                                        nearestPlayer->AddQuest(quest, nearestPlayer);
                                }
                            }
                            break;
                        }
                        case AT_ZONE_SCAR_OF_THE_WORLDBREAKER:
                        {
                            if (nearestPlayer->GetQuestStatus(QUEST_TDDC_WHAT_REALLY_HAPPENED) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (nearestPlayer->GetVehicle())
                                {
                                    if (Creature* vehicle = nearestPlayer->GetVehicleCreatureBase())
                                    {
                                        if (vehicle->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                                            return;

                                        vehicle->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                        vehicle->AI()->Talk(5, nearestPlayer->GetGUID());
                                        vehicle->AddAura(87853, vehicle);
                                        vehicle->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY|MOVEMENTFLAG_ASCENDING|MOVEMENTFLAG_FLYING);
                                        nearestPlayer->KilledMonsterCredit(47178);
                                        vehicle->GetMotionMaster()->MoveJump(-6659.61f, -3109.04f, 340.61f, 50.0f, 50.0f);
                                        vehicle->GetMotionMaster()->MovePoint(0, -6659.61f, -3109.04f, 340.61f, true);
                                        vehicle->SetCanFly(true);
                                        vehicle->AddAura(87851, vehicle);
                                    }
                                }
                            }
                            break;
                        }
                        case AT_ZONE_GILNEAS_LIBERATION_FRONT_BASE_CAMP:
                        {
                            if (nearestPlayer->GetQuestStatus(QUEST_ON_HER_MAJESTY_SECRET_SERVICE) == QUEST_STATUS_INCOMPLETE)
                            {
                                if (Creature* lornaCrowley = me->FindNearestCreature(NPC_ENTRY_LORNA_CROWLEY, 50.0f, true))
                                {
                                    // Event in progress!
                                    if (lornaCrowley->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED) || lornaCrowley->isInCombat() || lornaCrowley->GetVehicleBase())
                                        return;

                                    lornaCrowley->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);

                                    std::list<Unit*> targets;
                                    Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(nearestPlayer, nearestPlayer, 80.0f);
                                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(nearestPlayer, targets, u_check);
                                    nearestPlayer->VisitNearbyObject(80.0f, searcher);
                                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                    {
                                        if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == nearestPlayer))
                                        {
                                            switch ((*itr)->ToTempSummon()->GetEntry())
                                            {
                                                case NPC_ENTRY_LORD_GODFREY:
                                                {
                                                    (*itr)->GetMotionMaster()->Clear();
                                                    (*itr)->GetMotionMaster()->MovePoint(0, -802.21f, 1339.69f, 33.87f, true);
                                                    (*itr)->ToCreature()->AI()->TalkWithDelay(7000, 0);
                                                    (*itr)->ToCreature()->AI()->TalkWithDelay(23000, 1);
                                                    (*itr)->ToCreature()->AI()->TalkWithDelay(29000, 2);
                                                    (*itr)->ToCreature()->AI()->TalkWithDelay(35000, 3);
                                                    break;
                                                }
                                                case NPC_ENTRY_LORD_ASHBURY:
                                                {
                                                    (*itr)->GetMotionMaster()->Clear();
                                                    (*itr)->GetMotionMaster()->MovePoint(0, -802.37f, 1328.90f, 33.60f, true);
                                                    break;
                                                }
                                                case NPC_ENTRY_LORD_WALDEN:
                                                {
                                                    (*itr)->GetMotionMaster()->Clear();
                                                    (*itr)->GetMotionMaster()->MovePoint(0, -806.26f, 1343.60f, 33.80f, true);
                                                    break;
                                                }
                                                default:
                                                    return;
                                            }
                                        }
                                    }

                                    lornaCrowley->AI()->TalkWithDelay(1500, 0);
                                    lornaCrowley->AI()->TalkWithDelay(12000, 1);
                                    lornaCrowley->AI()->TalkWithDelay(18000, 2);
                                    lornaCrowley->AI()->TalkWithDelay(41000, 3);
                                    lornaCrowley->AI()->SetData(0, 1);
                                }
                            }
                            break;
                        }
                        case AT_ZONE_THE_BATTLEFRONT:
                        {
                            if (nearestPlayer->GetQuestStatus(QUEST_CITIES_IN_DUST) == QUEST_STATUS_COMPLETE)
                                nearestPlayer->SetPhaseMask(1, true);

                            if (nearestPlayer->GetQuestStatus(QUEST_CITIES_IN_DUST) == QUEST_STATUS_INCOMPLETE)
                            {
                                std::list<Unit*> targets;
                                Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(nearestPlayer, nearestPlayer, 500.0f);
                                Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(nearestPlayer, targets, u_check);
                                nearestPlayer->VisitNearbyObject(500.0f, searcher);
                                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                {
                                    if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == nearestPlayer))
                                    {
                                        switch ((*itr)->ToTempSummon()->GetEntry())
                                        {
                                            case NPC_ENTRY_LADY_SYLVANAS:
                                            case NPC_ENTRY_CROMUSH:
                                            case NPC_ENTRY_AGATHA:
                                            case NPC_ENTRY_ARTHURA:
                                            case NPC_ENTRY_DASCHLA:
                                            {
                                                (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                                                break;
                                            }
                                            default:
                                                break;
                                        }
                                    }
                                }
                                Creature* ladySylvanas = me->FindNearestCreature(NPC_ENTRY_LADY_SYLVANAS, 20.0f, true);
                                Creature* deadSylvanas = me->FindNearestCreature(NPC_ENTRY_LADY_SYLVANAS, 20.0f, false);
                                Creature* cromush = me->FindNearestCreature(NPC_ENTRY_CROMUSH, 20.0f, true);
                                Creature* deadAgatha = me->FindNearestCreature(NPC_ENTRY_AGATHA, 20.0f, false);
                                Creature* deadArthura = me->FindNearestCreature(NPC_ENTRY_ARTHURA, 20.0f, false);
                                Creature* deadDaschla = me->FindNearestCreature(NPC_ENTRY_DASCHLA, 20.0f, false);
                                Creature* agatha = me->FindNearestCreature(NPC_ENTRY_AGATHA, 20.0f, true);
                                Creature* arthura = me->FindNearestCreature(NPC_ENTRY_ARTHURA, 20.0f, true);
                                Creature* daschla = me->FindNearestCreature(NPC_ENTRY_DASCHLA, 20.0f, true);
                                if (!ladySylvanas && !deadSylvanas)
                                    return;

                                if (ladySylvanas && ladySylvanas->GetPhaseMask() == 2)
                                    return;

                                if (cromush && deadAgatha && deadArthura && deadDaschla && deadSylvanas)
                                {
                                    deadSylvanas->Respawn(true);
                                    deadAgatha->Respawn(true);
                                    deadArthura->Respawn(true);
                                    deadDaschla->Respawn(true);
                                    deadAgatha->SetPhaseMask(32768, true);
                                    deadArthura->SetPhaseMask(32768, true);
                                    deadDaschla->SetPhaseMask(32768, true);
                                    cromush->SetPhaseMask(32768, true);
                                    deadSylvanas->SetPhaseMask(32768, true);
                                    deadSylvanas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                    return;
                                }

                                // Event in progress!
                                if (ladySylvanas->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                                    return;

                                if (arthura && daschla && cromush && agatha && ladySylvanas)
                                {
                                    ladySylvanas->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                    ladySylvanas->SetPhaseMask(2, true);
                                    arthura->SetPhaseMask(2, true);
                                    daschla->SetPhaseMask(2, true);
                                    agatha->SetPhaseMask(2, true);
                                    cromush->SetPhaseMask(2, true);
                                    ladySylvanas->CastSpell(ladySylvanas, SPELL_SUMMON_CROWLEY, true);
                                    ladySylvanas->CastSpell(ladySylvanas, SPELL_SUMMON_BLOODFANG, true);
                                    ladySylvanas->AI()->TalkWithDelay(4000, 6);
                                }
                            }
                            break;
                        }
                        case AT_ZONE_LAKESHIRE_BRIDGE:
                        {
                            // Only if phasemask is 2!
                            if (nearestPlayer->GetPhaseMask() == 2)
                            {
                                if (nearestPlayer->GetQuestStatus(26520) == QUEST_STATUS_COMPLETE)
                                    nearestPlayer->SetPhaseMask(1, true);
                            }
                            break;
                        }
                        case AT_ZONE_SLUDGE_FIELDS_1:
                        {
                            // Already in event state
                            if (nearestPlayer->GetPhaseMask() == 32768)
                                return;

                            if (nearestPlayer->GetQuestStatus(QUEST_BURNSIDE_MUST_FALL) == QUEST_STATUS_REWARDED)
                            {
                                if (nearestPlayer->GetQuestStatus(QUEST_A_BLIGHT_UPON_THE_LAND) == QUEST_STATUS_INCOMPLETE)
                                {
                                    Creature* wardenDead = me->FindNearestCreature(NPC_ENTRY_WARDEN_STILLWATER, 200.0f, false);
                                    Creature* monsterAlive = me->FindNearestCreature(NPC_ENTRY_WARDEN_MONSTER, 200.0f, true);
                                    if (wardenDead && !monsterAlive)
                                    {
                                        wardenDead->Respawn();
                                        return;
                                    }
                                }
                                if (Creature* wardenStillwater = me->FindNearestCreature(NPC_ENTRY_WARDEN_STILLWATER, 25.0f, true))
                                {
                                    if (nearestPlayer->IsActiveQuest(QUEST_A_BLIGHT_UPON_THE_LAND))
                                    {
                                        std::list<Unit*> targets;
                                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(nearestPlayer, nearestPlayer, 500.0f);
                                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(nearestPlayer, targets, u_check);
                                        nearestPlayer->VisitNearbyObject(500.0f, searcher);
                                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                        {
                                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == nearestPlayer))
                                            {
                                                switch ((*itr)->ToTempSummon()->GetEntry())
                                                {
                                                    // Johnny and Lyadon
                                                    case 48020:
                                                    case 48021:
                                                    {
                                                        (*itr)->ToTempSummon()->UnSummon();
                                                        break;
                                                    }
                                                    default:
                                                        break;
                                                }
                                            }
                                        }

                                        if (!wardenStillwater->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED) || !wardenStillwater->isInCombat())
                                        {
                                            wardenStillwater->AI()->TalkWithDelay(1000, 0);
                                            wardenStillwater->AI()->TalkWithDelay(4000, 1);
                                            wardenStillwater->AI()->TalkWithDelay(12000, 2);
                                            wardenStillwater->AI()->TalkWithDelay(35500, 3);
                                            wardenStillwater->AI()->TalkWithDelay(41500, 4);
                                            wardenStillwater->AI()->TalkWithDelay(46500, 5);
                                            wardenStillwater->AI()->SetData(0, 1);

                                            if (Creature* lyadon = me->FindNearestCreature(NPC_ENTRY_WARDEN_LYADON, 25.0f, true))
                                            {
                                                lyadon->AI()->TalkWithDelay(18000, 0);
                                                lyadon->AI()->TalkWithDelay(28000, 1);
                                                lyadon->AI()->TalkWithDelay(31500, 2);
                                            }

                                            wardenStillwater->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                            nearestPlayer->SetPhaseMask(32768, true);
                                        }
                                    }
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
                actTimer = 5*IN_MILLISECONDS;
            }
            else
                actTimer -= diff;
        }

        protected:
            uint16 actTimer;
            uint32 summonTimer;
            uint16 ogreTimer;
            uint16 boatTimer;
            uint16 reinforcementsTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_generic_areatriggerAI(creature);
    }
};

class npc_blight_slime : public CreatureScript
{
public:
    npc_blight_slime() : CreatureScript("npc_blight_slime") { }

    struct npc_blight_slimeAI : public ScriptedAI
    {
        npc_blight_slimeAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            QUEST_CREDIT_SLIME = 48290,
            SPELL_DEPLETED     = 89756
        };

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (caster && caster->GetTypeId() == TYPEID_PLAYER && me->isAlive() && spell->Id == SPELL_DEPLETED)
            {
                caster->EnergizeBySpell(caster, SPELL_DEPLETED, 1, POWER_ALTERNATE_POWER);
                caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_SLIME);
                if (Aura* aur = me->GetAura(SPELL_DEPLETED, caster->GetGUID()))
                {
                    if (aur->GetStackAmount() >= 14)
                        me->DespawnOrUnsummon(1);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blight_slimeAI(creature);
    }
};

class npc_danforth : public CreatureScript
{
public:
    npc_danforth() : CreatureScript("npc_danforth") { }

    struct npc_danforthAI : public ScriptedAI
    {
        npc_danforthAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            // Spells
            SPELL_COSMETIC_CHAINS_LEFT     = 84990,
            SPELL_COSMETIC_CHAINS_RIGHT    = 84991,
            SPELL_CHAINS_OF_CRUELTY_R      = 81081,
            SPELL_CHAINS_OF_CRUELTY_L      = 81085,

            // Triggers
            NPC_TRIGGER_DANFORTH_DUMMY     = 43366
        };

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
            me->SetDisableGravity(true);
            me->SetCanFly(true);
            checkChains = 1500;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (!caster || !spell)
                return;

            switch (spell->Id)
            {
                case SPELL_CHAINS_OF_CRUELTY_R:
                case SPELL_CHAINS_OF_CRUELTY_L:
                {
                    me->HandleEmoteCommand(EMOTE_STATE_SPELLEFFECT_HOLD);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (checkChains <= diff)
            {
                if (!me->HasAura(SPELL_CHAINS_OF_CRUELTY_R) && !me->HasAura(SPELL_CHAINS_OF_CRUELTY_L))
                {
                    me->HandleEmoteCommand(EMOTE_STATE_STAND);
                    me->SetDisableGravity(false);
                    me->SetCanFly(false);
                    me->GetMotionMaster()->MoveJump(-8802.40f, -2207.53f, 134.50f, 9.5f, 9.5f);
                    me->RemoveAurasDueToSpell(SPELL_COSMETIC_CHAINS_RIGHT);
                    me->RemoveAurasDueToSpell(SPELL_COSMETIC_CHAINS_LEFT);
                }
                checkChains = 1500;
            }
            else
                checkChains -= diff;
        }

    protected:
        uint16 checkChains;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_danforthAI(creature);
    }
};

enum danforthQuest
{
    QUEST_AND_LAST_BUT_NOT_LEAST_DANFORTH = 26562
};

class npc_danforth_invisible_dummy : public CreatureScript
{
public:
    npc_danforth_invisible_dummy() : CreatureScript("npc_danforth_invisible_dummy") { }

    struct npc_danforth_invisible_dummyAI : public ScriptedAI
    {
        npc_danforth_invisible_dummyAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            // Spells
            SPELL_COSMETIC_CHAINS_LEFT     = 84990,
            SPELL_COSMETIC_CHAINS_RIGHT    = 84991,
            SPELL_CHAINS_OF_CRUELTY_R      = 81081,
            SPELL_CHAINS_OF_CRUELTY_L      = 81085,

            // GUID
            DANFORTH_TRIGGER_R             = 89756,
            DANFORTH_TRIGGER_L             = 89757,

            // NPC
            NPC_ENTRY_DANFORTH             = 43275,
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            chainsTimer = 500;
        }

        void UpdateAI(uint32 diff)
        {
            if (Creature* danforth = me->FindNearestCreature(NPC_ENTRY_DANFORTH, 30.0f, true))
            {
                // Not in water!
                if (danforth->IsInWater())
                    return;

                switch (me->GetGUIDLow())
                {
                    case DANFORTH_TRIGGER_R:
                    {
                        if (chainsTimer <= diff)
                        {
                            if (me->HasAura(SPELL_CHAINS_OF_CRUELTY_R))
                                return;

                            me->CastSpell(danforth, SPELL_COSMETIC_CHAINS_RIGHT, true);
                            danforth->CastSpell(danforth, SPELL_CHAINS_OF_CRUELTY_R, true);
                            chainsTimer = 10000;
                        }
                        else
                            chainsTimer -= diff;
                        break;
                    }
                    case DANFORTH_TRIGGER_L:
                    {
                        if (chainsTimer <= diff)
                        {
                            if (me->HasAura(SPELL_CHAINS_OF_CRUELTY_L))
                                return;

                            me->CastSpell(danforth, SPELL_COSMETIC_CHAINS_LEFT, true);
                            danforth->CastSpell(danforth, SPELL_CHAINS_OF_CRUELTY_L, true);
                            chainsTimer = 10000;
                        }
                        else
                            chainsTimer -= diff;
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        uint16 chainsTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_danforth_invisible_dummyAI(creature);
    }

    bool OnQuestComplete(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_AND_LAST_BUT_NOT_LEAST_DANFORTH)
            creature->Respawn(true);
        return true;
    }
};

enum trotemanQuest
{
    // Quest
    QUEST_RETURN_OF_THE_BRAVO_COMPANY = 26563,

    // Npc
    NPC_ENTRY_MESSNER   = 43300,
    NPC_ENTRY_JORGENSEN = 43305,
    NPC_ENTRY_KRAKAUER  = 43303,
    NPC_ENTRY_DANFORTH  = 43302
};

class npc_colonel_troteman : public CreatureScript
{
public:
    npc_colonel_troteman() : CreatureScript("npc_colonel_troteman") { }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_RETURN_OF_THE_BRAVO_COMPANY)
        {
            if (!player)
                return true;

            std::list<Unit*> targets;
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(player, player, 300.0f);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(300.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToCreature())
                {
                    switch ((*itr)->GetEntry())
                    {
                        case NPC_ENTRY_MESSNER:
                        case NPC_ENTRY_JORGENSEN:
                        case NPC_ENTRY_KRAKAUER:
                        case NPC_ENTRY_DANFORTH:
                        {
                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
        return true;
    }
};

class npc_wild_rat : public CreatureScript
{
public:
    npc_wild_rat() : CreatureScript("npc_wild_rat") { }

    struct npc_wild_ratAI : public ScriptedAI
    {
        npc_wild_ratAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            checkForOrcs = 2000;
            if (!me->HasAura(65960))
                me->AddAura(65960, me);
        }

        void CheckForOrcs()
        {
            Unit* summoner = me->ToTempSummon()->GetSummoner();
            if (!summoner)
                return;

            float posX = me->GetPositionX();
            float posY = me->GetPositionY();
            float posZ = me->GetPositionZ();

            std::list<Unit*> targets;
            Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 8.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(8.0f, searcher);
            for (std::list<Unit*>::const_iterator orc = targets.begin(); orc != targets.end(); ++orc)
            {
                if (!(*orc))
                    continue;

                // Disorient guards!
                if ((*orc)->ToCreature() && !(*orc)->ToCreature()->isPet() && !(*orc)->ToCreature()->isSummon())
                {
                    (*orc)->GetMotionMaster()->MovePoint(0, posX+(urand(1, 5)), posY+(urand(1, 5)), posZ, true);
                    (*orc)->AddAura(65960, (*orc));
                    (*orc)->ToCreature()->AI()->TalkWithDelay(1500, 0);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (checkForOrcs <= diff)
            {
                CheckForOrcs();
                checkForOrcs = 120*IN_MILLISECONDS;
            }
            else
                checkForOrcs -= diff;
        }

    protected:
        uint32 checkForOrcs;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wild_ratAI(creature);
    }
};

enum keeshanId
{
    // Quest
    QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR = 26651,
    QUEST_GRAND_MAGUS_DOANE                 = 26694,
    QUEST_DETONATION                        = 26668,

    // Npc
    NPC_JORGENSEN_2         = 43546,
    NPC_JORGENSEN_EVENT     = 43609,
    NPC_MESSNER_EVENT       = 43610,
    NPC_KEESHAN_EVENT       = 43611,
    NPC_KRAKAUER_EVENT      = 43608,
    NPC_DANFORTH_EVENT      = 43607,

    // Spells
    SPELL_SUMMON_RENDER_CAMERA              = 81607,
    SPELL_PLAYER_INVISIBILITY               = 60191
};

class npc_john_j_keeshan : public CreatureScript
{
public:
    npc_john_j_keeshan() : CreatureScript("npc_john_j_keeshan") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_GRAND_MAGUS_DOANE:
            {
                player->CastSpell(player, SPELL_PLAYER_INVISIBILITY, true);
                player->SetPhaseMask(2, true);
                player->SummonCreature(NPC_JORGENSEN_EVENT, -9627.15f, -3473.84f, 122.02f, 2.30f)->UnSummon(30000);
                player->SummonCreature(NPC_DANFORTH_EVENT, -9630.00f, -3475.26f, 121.95f, 2.11f)->UnSummon(30000);
                player->SummonCreature(NPC_KEESHAN_EVENT, -9633.55f, -3476.19f, 121.95f, 2.14f)->UnSummon(30000);
                player->SummonCreature(NPC_MESSNER_EVENT, -9636.30f, -3477.43f, 122.95f, 1.92f)->UnSummon(30000);
                player->SummonCreature(NPC_KRAKAUER_EVENT, -9639.29f, -3477.90f, 121.95f, 1.58f)->UnSummon(30000);

                if (Creature* keeshan = player->FindNearestCreature(NPC_KEESHAN_EVENT, 50.0f, true))
                {
                    keeshan->GetMotionMaster()->MovePoint(0, -9640.54f, -3468.93f, 120.94f, true);
                    keeshan->AI()->TalkWithDelay(1000, 0);
                    keeshan->AI()->TalkWithDelay(9000, 1);
                }

                if (Creature* danforth = player->FindNearestCreature(NPC_DANFORTH_EVENT, 50.0f, true))
                {
                    danforth->GetMotionMaster()->MovePoint(0, -9635.24f, -3468.85f, 121.13f, true);
                    danforth->AI()->TalkWithDelay(5000, 0);
                    danforth->AI()->TalkWithDelay(12500, 1);
                    danforth->AI()->SetData(0, 1);
                }
                break;
            }
            default:
                break;
        }
        return true;
    }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR:
            {
                std::list<Unit*> targets;
                Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(player, player, 300.0f);
                Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(player, targets, u_check);
                player->VisitNearbyObject(300.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == player))
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_JORGENSEN_2:
                            {
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                break;
            }
            default:
                break;
        }
        return true;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_DETONATION)
        {
            player->CastSpell(player, SPELL_SUMMON_RENDER_CAMERA, true);
            player->TeleportTo(0, -9555.71f, -3045.703f, 120.72f, 3.77f);
        }
        return true;
    }
};

enum hornQuests
{
    // Quest
    QUEST_DARKBLAZE_BROOD_OF_THE_WORLDBREAKER = 26714,

    // Npc
    NPC_ENTRY_DARKBLAZE = 43496
};

class npc_horn_of_summoning : public CreatureScript
{
public:
    npc_horn_of_summoning() : CreatureScript("npc_horn_of_summoning") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_DARKBLAZE_BROOD_OF_THE_WORLDBREAKER)
        {
            player->SummonCreature(NPC_ENTRY_DARKBLAZE, -9516.17f, -2880.37f, 164.92f, 5.20f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
            creature->DespawnOrUnsummon(1);
        }
        return true;
    }
};

class npc_abandoned_bloodwash_trigger : public CreatureScript
{
public:
    npc_abandoned_bloodwash_trigger() : CreatureScript("npc_abandoned_bloodwash_trigger") { }

    struct npc_abandoned_bloodwash_triggerAI : public ScriptedAI
    {
        npc_abandoned_bloodwash_triggerAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            QUEST_ENTRY_THE_FUTURE_OF_THE_ROCKPOOL  = 25707,
            SPELL_THE_FUTURE_OF_THE_ROCKPOOL        = 77549,
            QUEST_CREDIT_ROCKPOOL                   = 41402
        };

        void Reset()
        {
            checkPlayers = 5*IN_MILLISECONDS;
        }

        void QuestComplete()
        {
            std::list<Unit*> targets;
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 500.0f);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(500.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToPlayer())
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_THE_FUTURE_OF_THE_ROCKPOOL) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (!(*itr)->IsInWater() && (*itr)->GetAreaId() != 5096)
                            continue;

                        if ((*itr)->ToPlayer()->GetVehicleBase())
                        {
                            (*itr)->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_ROCKPOOL);
                            (*itr)->ToPlayer()->_ExitVehicle();
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (checkPlayers <= diff)
            {
                QuestComplete();
                checkPlayers = 5*IN_MILLISECONDS;
            }
            else
                checkPlayers -= diff;
        }

    protected:
        uint32 checkPlayers;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_abandoned_bloodwash_triggerAI(creature);
    }
};

class npc_sentinel_start : public CreatureScript
{
public:
    npc_sentinel_start() : CreatureScript("npc_sentinel_start") { }

    enum Id
    {
        // Spells
        SPELL_SENTINEL_DESPAWN          = 86555,
        SPELL_SENTINEL_BEAM             = 86432,

        // Npc
        NPC_ENTRY_SENTINEL_PAWN         = 46395
    };

    struct npc_sentinel_startAI : public ScriptedAI
    {
        npc_sentinel_startAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* /*summoner*/)
        {
            startTimer = 2000;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_SENTINEL_DESPAWN:
                {
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (startTimer <= diff)
            {
                if (Creature* sentinel = me->FindNearestCreature(NPC_ENTRY_SENTINEL_PAWN, 60.0f, true))
                    me->CastWithDelay(1500, sentinel, SPELL_SENTINEL_BEAM, true);
                startTimer = 1210000;
            }
            else
                startTimer -= diff;
        }

        protected:
            uint32 startTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sentinel_startAI(creature);
    }
};

class npc_amakkar : public CreatureScript
{
public:
    npc_amakkar() : CreatureScript("npc_amakkar") { }

    enum Id
    {
        // Spells
        SPELL_RIDE_VEHICLE          = 87782,
        SPELL_KIDNEY_SHOT           = 87608,

        // Quest
        QUEST_ENTRY_AMAKKAR         = 27891
    };

    struct npc_amakkarAI : public ScriptedAI
    {
        npc_amakkarAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                if (summoner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_AMAKKAR) == QUEST_STATUS_INCOMPLETE)
                {
                    summoner->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_amakkarAI(creature);
    }
};

class npc_gargal : public CreatureScript
{
public:
    npc_gargal() : CreatureScript("npc_gargal") { }

    enum Id
    {
        // Spells
        SPELL_RIDE_VEHICLE          = 87782,
        SPELL_SHIELD_WALL           = 87607,
        SPELL_TAUNT                 = 87606,

        // Quest
        QUEST_ENTRY_GARGAL          = 27893
    };

    struct npc_gargalAI : public ScriptedAI
    {
        npc_gargalAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
            timerShieldWall = 2000;
            timerTaunt = 3000;
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                if (summoner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_GARGAL) == QUEST_STATUS_INCOMPLETE)
                {
                    summoner->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    timerShieldWall = 2000;
                    timerTaunt = 3000;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (timerShieldWall <= diff)
            {
                me->CastSpell(me, SPELL_SHIELD_WALL, true);
                timerShieldWall = 6000;
            }
            else
                timerShieldWall -= diff;

            if (timerTaunt <= diff)
            {
                me->CastSpell(me, SPELL_TAUNT, true);
                timerTaunt = 10000;
            }
            else
                timerTaunt -= diff;
        }

    protected:
        uint16 timerShieldWall;
        uint16 timerTaunt;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gargalAI(creature);
    }
};

class npc_jurrix : public CreatureScript
{
public:
    npc_jurrix() : CreatureScript("npc_jurrix") { }

    enum Id
    {
        // Spells
        SPELL_RIDE_VEHICLE          = 87782,
        SPELL_TIME_WARP             = 87596,
        SPELL_FIREBALL              = 87593,

        // Quest
        QUEST_ENTRY_JURRIX          = 27892
    };

    struct npc_jurrixAI : public ScriptedAI
    {
        npc_jurrixAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
            timerFireball = 3000;
            timerTimeWarp = 4000;
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                if (summoner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_JURRIX) == QUEST_STATUS_INCOMPLETE)
                {
                    summoner->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (timerFireball <= diff)
            {
                me->CastSpell(me->getVictim(), SPELL_FIREBALL, true);
                timerFireball = 6000;
            }
            else
                timerFireball -= diff;

            if (timerTimeWarp <= diff)
            {
                me->CastSpell(me, SPELL_TIME_WARP, true);
                timerTimeWarp = 10000;
            }
            else
                timerTimeWarp -= diff;
        }

    protected:
        uint16 timerFireball;
        uint16 timerTimeWarp;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_jurrixAI(creature);
    }
};

// ALLIANCE

class npc_eric : public CreatureScript
{
public:
    npc_eric() : CreatureScript("npc_eric") { }

    enum Id
    {
        // Spells
        SPELL_RIDE_VEHICLE          = 87782,
        SPELL_KIDNEY_SHOT           = 87608,

        // Quest
        QUEST_ENTRY_ERIC            = 27828
    };

    struct npc_ericAI : public ScriptedAI
    {
        npc_ericAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                if (summoner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_ERIC) == QUEST_STATUS_INCOMPLETE)
                {
                    summoner->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ericAI(creature);
    }
};

class npc_baelog : public CreatureScript
{
public:
    npc_baelog() : CreatureScript("npc_baelog") { }

    enum Id
    {
        // Spells
        SPELL_RIDE_VEHICLE          = 87782,
        SPELL_BAELOG_WARCRY         = 87277,

        // Quest
        QUEST_ENTRY_BAELOG          = 27834
    };

    struct npc_baelogAI : public ScriptedAI
    {
        npc_baelogAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
            timerBaelogWarcry = 2000;
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                if (summoner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_BAELOG) == QUEST_STATUS_INCOMPLETE)
                {
                    summoner->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    timerBaelogWarcry = 2000;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (timerBaelogWarcry <= diff)
            {
                me->CastSpell(me, SPELL_BAELOG_WARCRY, true);
                timerBaelogWarcry = 6000;
            }
            else
                timerBaelogWarcry -= diff;
        }

    protected:
        uint16 timerBaelogWarcry;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_baelogAI(creature);
    }
};

class npc_olaf : public CreatureScript
{
public:
    npc_olaf() : CreatureScript("npc_olaf") { }

    enum Id
    {
        // Spells
        SPELL_RIDE_VEHICLE          = 87782,
        SPELL_SHIELD_WALL           = 87607,
        SPELL_TAUNT                 = 87606,

        // Quest
        QUEST_ENTRY_OLAF            = 27835
    };

    struct npc_olafAI : public ScriptedAI
    {
        npc_olafAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_DEFENSIVE);
            timerShieldWall = 2000;
            timerTaunt = 3000;
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                if (summoner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_OLAF) == QUEST_STATUS_INCOMPLETE)
                {
                    summoner->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    timerShieldWall = 2000;
                    timerTaunt = 3000;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (timerShieldWall <= diff)
            {
                me->CastSpell(me, SPELL_SHIELD_WALL, true);
                timerShieldWall = 6000;
            }
            else
                timerShieldWall -= diff;

            if (timerTaunt <= diff)
            {
                me->CastSpell(me, SPELL_TAUNT, true);
                timerTaunt = 10000;
            }
            else
                timerTaunt -= diff;
        }

    protected:
        uint16 timerShieldWall;
        uint16 timerTaunt;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_olafAI(creature);
    }
};

enum Id
{
    QUEST_SHADRA_THE_VENOM_QUEEN_A  = 26532,
    QUEST_SHADRA_THE_VENOM_QUEEN_H  = 26419,

    NPC_ENTRY_SHADRA                = 43007,
    NPC_ENTRY_BODYCHOPPER           = 43016,
    NPC_ENTRY_TALONAXE              = 43215,
    NPC_ENTRY_SPIRITHUNTER          = 43213
};

class npc_wildhammer_lookout : public CreatureScript
{
public:
    npc_wildhammer_lookout() : CreatureScript("npc_wildhammer_lookout") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SHADRA_THE_VENOM_QUEEN_H)
        {
            if (Creature* shadra = creature->FindNearestCreature(NPC_ENTRY_SHADRA, 500.0f, true))
                creature->MonsterWhisper("Shadra is already here, attack her!", player->GetGUID(), true);
            else
            {
                creature->SummonCreature(NPC_ENTRY_SHADRA, -348.93f, -2890.28f, 65.45f, 5.90f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -274.55f, -2905.66f, 85.74f, 2.91f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2911.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2908.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2905.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2913.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            }
        }

        return true;
    }
};

class npc_deathstalker_lookout : public CreatureScript
{
public:
    npc_deathstalker_lookout() : CreatureScript("npc_deathstalker_lookout") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SHADRA_THE_VENOM_QUEEN_H)
        {
            if (Creature* shadra = creature->FindNearestCreature(NPC_ENTRY_SHADRA, 500.0f, true))
                creature->MonsterWhisper("Shadra is already here, attack her!", player->GetGUID(), true);
            else
            {
                creature->SummonCreature(NPC_ENTRY_SHADRA, -348.93f, -2890.28f, 65.45f, 5.90f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -274.55f, -2905.66f, 85.74f, 2.91f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2911.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2908.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2905.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->SummonCreature(NPC_ENTRY_BODYCHOPPER, -273.95f, -2913.24f, 85.28f, 2.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            }
        }

        return true;
    }
};

enum mustangId
{
    QUEST_ENTRY_LEARNING_THE_ROPES  = 27000,
    QUEST_ENTRY_THIS_MEANS_WAR      = 27001,

    SUMMON_HEARTHGLEN_MUSTANG       = 83604
};

class npc_hearthglen_mustang : public CreatureScript
{
public:
    npc_hearthglen_mustang() : CreatureScript("npc_hearthglen_mustang") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();
        if (player->GetQuestStatus(QUEST_ENTRY_LEARNING_THE_ROPES) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_ENTRY_THIS_MEANS_WAR) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, SUMMON_HEARTHGLEN_MUSTANG, true);
        return true;
    }
};

class npc_shadow_prison : public CreatureScript
{
public:
    npc_shadow_prison() : CreatureScript("npc_shadow_prison") { }

    struct npc_shadow_prisonAI : public ScriptedAI
    {
        npc_shadow_prisonAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            NPC_ENTRY_KOLTIRA           = 44452,
            NPC_ENTRY_THASSARIAN        = 44453,

            SPELL_ENTRY_SHADOW_PRISON   = 86780
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            checkTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Player* player = me->FindNearestPlayer(50, true))
                {
                    if (player->HasAura(SPELL_ENTRY_SHADOW_PRISON))
                    {
                        player->SummonCreature(NPC_ENTRY_KOLTIRA, 1292.12f, -1535.79f, 58.67f, 2.79f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(120000);
                        player->SummonCreature(NPC_ENTRY_THASSARIAN, 1293.56f, -1532.99f, 58.67f, 2.73f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(120000);
                        me->DespawnOrUnsummon(1);
                    }
                    checkTimer = 20000;
                }
            }
            else checkTimer -= diff;
        }

    protected:
        uint32 checkTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadow_prisonAI(creature);
    }
};

class npc_enthralled_valkyr : public CreatureScript
{
public:
    npc_enthralled_valkyr() : CreatureScript("npc_enthralled_valkyr") { }

    struct npc_enthralled_valkyrAI : public ScriptedAI
    {
        npc_enthralled_valkyrAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            SPELL_ENTRY_RAISE_FORSAKEN  = 84143,
            NPC_ENTRY_ALLIANCE_LABORER  = 44433,
            NPC_ENTRY_FORSAKEN_LABORER  = 45048,

            QUEST_CREDIT_CONVERTED      = 45089
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            checkTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Creature* allianceLaborer = me->FindNearestCreature(NPC_ENTRY_ALLIANCE_LABORER, 50.0f, false))
                {
                    if (allianceLaborer->getDeathState() == CORPSE)
                    {
                        me->CastSpell(allianceLaborer, SPELL_ENTRY_RAISE_FORSAKEN, true);
                        allianceLaborer->SummonCreature(NPC_ENTRY_FORSAKEN_LABORER, allianceLaborer->GetPositionX(), allianceLaborer->GetPositionY(), allianceLaborer->GetPositionZ(), allianceLaborer->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                        allianceLaborer->DespawnOrUnsummon(2000);
                    }
                }
                checkTimer = 5000;
            }
            else
                checkTimer -= diff;
        }

    protected:
        uint16 checkTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_enthralled_valkyrAI(creature);
    }
};

class npc_summoned_ebon_gargoyle : public CreatureScript
{
public:
    npc_summoned_ebon_gargoyle() : CreatureScript("npc_summoned_ebon_gargoyle") { }

    struct npc_summoned_ebon_gargoyleAI : public ScriptedAI
    {
        npc_summoned_ebon_gargoyleAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            NPC_ENTRY_PROVINCIAL_MINUTEMAN  = 44944,
            SPELL_QUEST_CREDIT_GARGOYLE     = 84289,
            QUEST_ENTRY_THE_FARMERS_MILITIA = 27084
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->setFaction(FACTION_FRIENDLY);
            checkTimer = 500;
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Creature* provincialMinuteman = me->FindNearestCreature(NPC_ENTRY_PROVINCIAL_MINUTEMAN, 30.0f, true))
                {
                    provincialMinuteman->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+10, 8.0f, 8.0f);
                    provincialMinuteman->EnterVehicle(me, 0);
                    provincialMinuteman->CombatStop(true, true);

                    std::list<Unit*> targets;
                    Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(provincialMinuteman, provincialMinuteman, 50.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(provincialMinuteman, targets, u_check);
                    provincialMinuteman->VisitNearbyObject(50.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr)->GetTypeId() == TYPEID_PLAYER && (*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_THE_FARMERS_MILITIA) == QUEST_STATUS_INCOMPLETE)
                            (*itr)->CastSpell((*itr), SPELL_QUEST_CREDIT_GARGOYLE, true);
                    }
                }
                else
                    me->DespawnOrUnsummon(1);

                checkTimer = 10000;
            }
            else
                checkTimer -= diff;
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            me->GetMotionMaster()->MoveJump(me->GetPositionX()+15, me->GetPositionY()+15, me->GetPositionZ()+60, 8.0f, 8.0f);
            me->DespawnOrUnsummon(6000);
            if (passenger->GetTypeId() == TYPEID_UNIT)
                passenger->ToCreature()->DespawnOrUnsummon(6500);
        }

    protected:
        uint16 checkTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_summoned_ebon_gargoyleAI(creature);
    }
};

class npc_enthralled_valkyr_final : public CreatureScript
{
public:
    npc_enthralled_valkyr_final() : CreatureScript("npc_enthralled_valkyr_final") { }

    struct npc_enthralled_valkyr_finalAI : public ScriptedAI
    {
        npc_enthralled_valkyr_finalAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            // Spells
            SPELL_ENTRY_RAISE_FORSAKEN      = 84143,
            SPELL_ENTRY_CALL_TO_ARMS        = 84155,

            // Npc
            NPC_ENTRY_FRIGHTENED_MINUTEMAN  = 45101,
            NPC_ENTRY_FORSAKEN_LABORER      = 45048,
            NPC_ENTRY_FORSAKEN_TROOPER_1    = 45241,
            NPC_ENTRY_FORSAKEN_TROOPER_2    = 45242,
            NPC_ENTRY_FORSAKEN_TROOPER_3    = 45243,

            // Credit
            QUEST_CREDIT_CONVERTED          = 45102
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            checkTimer = 3000;
            trooperCheck = 5000;
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Creature* frightenedMinuteman = me->FindNearestCreature(NPC_ENTRY_FRIGHTENED_MINUTEMAN, 50.0f, false))
                {
                    if (frightenedMinuteman->getDeathState() == CORPSE)
                    {
                        me->CastSpell(frightenedMinuteman, SPELL_ENTRY_RAISE_FORSAKEN, true);
                        frightenedMinuteman->SummonCreature(NPC_ENTRY_FORSAKEN_LABORER, frightenedMinuteman->GetPositionX(), frightenedMinuteman->GetPositionY(), frightenedMinuteman->GetPositionZ(), frightenedMinuteman->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                        frightenedMinuteman->DespawnOrUnsummon(2000);
                        if (me->GetCharmerOrOwner() && me->GetCharmerOrOwner()->ToPlayer())
                            me->GetCharmerOrOwner()->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_CONVERTED);
                    }
                }
                checkTimer = 5000;
            }
            else
                checkTimer -= diff;

            if (trooperCheck <= diff)
            {
                me->CastSpell(me, SPELL_ENTRY_CALL_TO_ARMS, true);
                trooperCheck = 5000;
            }
            else
                trooperCheck -= diff;
        }

    protected:
        uint16 checkTimer;
        uint16 trooperCheck;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_enthralled_valkyr_finalAI(creature);
    }
};

enum heartrazorActions
{
    ACTION_DIED = 1
};

class npc_heartrazor : public CreatureScript
{
public:
    npc_heartrazor() : CreatureScript("npc_heartrazor") { }

    struct npc_heartrazorAI : public ScriptedAI
    {
        npc_heartrazorAI(Creature* creature) : ScriptedAI(creature) {subduerCounter = 0;}

        enum Id
        {
            // Credit
            QUEST_CREDIT_RELEASE_HEARTRAZOR     = 47486,

            // Quest
            QUEST_ENTRY_RELEASE_HEARTRAZOR      = 28088
        };

        void Reset()
        {
            subduerCounter = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DIED:
                {
                    subduerCounter++;
                    if (subduerCounter >= 4)
                    {
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(0, -5117.07f, -1222.02f, 55.06f, false);
                        subduerCounter = 0;
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(150.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            Player* nearestPlayer = (*itr)->ToPlayer();
                            if (!nearestPlayer)
                                continue;

                            if (nearestPlayer->GetQuestStatus(QUEST_ENTRY_RELEASE_HEARTRAZOR) == QUEST_STATUS_INCOMPLETE)
                                nearestPlayer->KilledMonsterCredit(QUEST_CREDIT_RELEASE_HEARTRAZOR);
                        }
                        me->DespawnOrUnsummon(8000);
                    }
                    break;
                }
                default:
                    break;
            }
        }

    private:
        uint8 subduerCounter;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_heartrazorAI(creature);
    }
};

class npc_twilight_subduer : public CreatureScript
{
public:
    npc_twilight_subduer() : CreatureScript("npc_twilight_subduer") { }

    struct npc_twilight_subduerAI : public ScriptedAI
    {
        npc_twilight_subduerAI(Creature* creature) : ScriptedAI(creature) { }

        enum Id
        {
            NPC_ENTRY_HEARTRAZOR    = 47486
        };

        void JustDied(Unit* /*victim*/)
        {
            if (Creature* heartrazor = me->FindNearestCreature(NPC_ENTRY_HEARTRAZOR, 60.0f, true))
                heartrazor->AI()->DoAction(ACTION_DIED);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_subduerAI(creature);
    }
};

enum heartrazorQuest
{
    QUEST_THE_TWILIGHT_SKYMASTER    = 28098,
    SPELL_SUMMON_HEARTRAZOR         = 88591,
    SPELL_SUMMON_HEARTRAZOR_2       = 88592
};

class npc_heartrazor_wp : public CreatureScript
{
public:
    npc_heartrazor_wp() : CreatureScript("npc_heartrazor_wp") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_TWILIGHT_SKYMASTER) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, SPELL_SUMMON_HEARTRAZOR, true);
            return true;
        }
        return false;
    }
};

class npc_heartrazor_wp_return : public CreatureScript
{
public:
    npc_heartrazor_wp_return() : CreatureScript("npc_heartrazor_wp_return") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_TWILIGHT_SKYMASTER) == QUEST_STATUS_COMPLETE)
        {
            player->CastSpell(player, SPELL_SUMMON_HEARTRAZOR_2, true);
            return true;
        }
        return false;
    }
};

class npc_generic_dave_trigger : public CreatureScript
{
public:
    npc_generic_dave_trigger() : CreatureScript("npc_generic_dave_trigger") { }

    struct npc_generic_dave_triggerAI : public ScriptedAI
    {
        npc_generic_dave_triggerAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            // GUID
            GUID_FIRST_ENTRY    = 711056,
            GUID_FIRST_EXIT     = 711095,
            GUID_SECOND_ENTRY   = 711692,
            GUID_SECOND_EXIT    = 711788,
            GUID_THIRD_ENTRY    = NULL,
            GUID_THIRD_EXIT     = NULL,
            GUID_NEMESIS_CR     = 712034,

            // Spells
            SPELL_FIRST_FLAMEGATE_ENTRY     = 76162,
            SPELL_FIRST_FLAMEGATE_EXIT      = 76405,
            SPELL_SECOND_FLAMEGATE_ENTRY    = 75667,
            SPELL_SECOND_FLAMEGATE_EXIT     = 77815,
            SPELL_THIRD_FLAMEGATE_ENTRY     = 77662,
            SPELL_THIRD_FLAMEGATE_EXIT      = 77802,

            // Npc
            NPC_ENTRY_CHILD_OF_TORTOLLA     = 41581
        };

        enum spellId
        {
            SPELL_ARTILLERY_DAMAGE  = 84864,
            SPELL_ARTILLERY_MARKER  = 84841
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_ARTILLERY_DAMAGE:
                {
                    me->RemoveAurasDueToSpell(SPELL_ARTILLERY_MARKER);
                    break;
                }
                default:
                    break;
            }
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            checkTimer = 2000;
        }

        void IsSummonedBy(Unit* owner)
        {
            // Only in Stormwind Keep
            if (owner->GetTypeId() == TYPEID_PLAYER && owner->GetAreaId() == 1519)
                owner->AddAura(60191, me);
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                switch (me->GetGUIDLow())
                {
                    case GUID_FIRST_ENTRY:
                    {
                        if (Player* player = me->FindNearestPlayer(3.5f, true))
                        {
                            player->CastSpell(player, SPELL_FIRST_FLAMEGATE_ENTRY, true);
                            checkTimer = 2000;
                        }
                        if (Player* player = me->FindNearestPlayer(3.5f, false))
                        {
                            player->TeleportTo(1, 5021.25f, -2024.60f, 1148.97f, 4.66f);
                            checkTimer = 2000;
                        }
                        break;
                    }
                    case GUID_FIRST_EXIT:
                    {
                        if (Player* player = me->FindNearestPlayer(3.5f, true))
                        {
                            player->CastSpell(player, SPELL_FIRST_FLAMEGATE_EXIT, true);
                            checkTimer = 2000;
                        }
                        if (Player* player = me->FindNearestPlayer(3.5f, false))
                        {
                            player->TeleportTo(1, 5038.85f, -2044.54f, 1368.10f, 5.32f);
                            checkTimer = 2000;
                        }
                        break;
                    }
                    case GUID_SECOND_ENTRY:
                    {
                        if (Player* player = me->FindNearestPlayer(3.5f, true))
                        {
                            player->CastSpell(player, SPELL_SECOND_FLAMEGATE_ENTRY, true);
                            checkTimer = 2000;
                        }
                        if (Player* player = me->FindNearestPlayer(3.5f, false))
                        {
                            player->TeleportTo(1, 4553.50f, -2575.38f, 829.58f, 0.86f);
                            checkTimer = 2000;
                        }
                        break;
                    }
                    case GUID_SECOND_EXIT:
                    {
                        if (Player* player = me->FindNearestPlayer(3.5f, true))
                        {
                            player->CastSpell(player, SPELL_SECOND_FLAMEGATE_EXIT, true);
                            checkTimer = 2000;
                        }
                        if (Player* player = me->FindNearestPlayer(3.5f, false))
                        {
                            player->TeleportTo(1, 4537.39f, -2577.98f, 1123.78f, 2.30f);
                            checkTimer = 2000;
                        }
                        break;
                    }
                    case GUID_NEMESIS_CR:
                    {
                        if (Creature* tortollaChild = me->FindNearestCreature(NPC_ENTRY_CHILD_OF_TORTOLLA, 8.0f, true))
                        {
                            tortollaChild->AI()->SetData(0, 1);
                            tortollaChild->DespawnOrUnsummon(10000);
                            tortollaChild->SetReactState(REACT_PASSIVE);
                            checkTimer = 2000;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
            else checkTimer -= diff;
        }

    protected:
        uint16 checkTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_generic_dave_triggerAI(creature);
    }
};

class npc_aviana_guardian : public CreatureScript
{
public:
    npc_aviana_guardian() : CreatureScript("npc_aviana_guardian") { }

    enum Id
    {
        // Spells
        SPELL_TWILIGHT_FIRELANCE_EQUIPPED   = 74180,

        // Vehicle
        NPC_AVIANA_GUARDIAN_1               = 40719,

        // Quests
        QUEST_ENTRY_FLIGHT_IN_THE_FIRELANDS = 25523,
        QUEST_ENTRY_WAVE_ONE                = 25525,
        QUEST_ENTRY_WAVE_TWO                = 25544,
        QUEST_ENTRY_EGG_WAVE                = 25560,
        QUEST_ENTRY_VIGILANCE_ON_WINGS      = 29177,

        // Phase
        PHASE_SET_WAVE_TWO                  = 16384
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetVehicleBase())
            return true;

        if (player->HasAura(SPELL_TWILIGHT_FIRELANCE_EQUIPPED))
        {
            if (player->GetQuestStatus(QUEST_ENTRY_WAVE_TWO) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_ENTRY_EGG_WAVE) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_ENTRY_VIGILANCE_ON_WINGS) == QUEST_STATUS_INCOMPLETE)
                player->SetPhaseMask(PHASE_SET_WAVE_TWO, true);

            player->SummonCreature(NPC_AVIANA_GUARDIAN_1, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
            if (player->GetQuestStatus(QUEST_ENTRY_FLIGHT_IN_THE_FIRELANDS) == QUEST_STATUS_INCOMPLETE)
                player->MonsterWhisper("Press Flap to Flap Your Wings!", player->GetGUID(), true);
            return true;
        }
        return true;
    }
};

class npc_climbing_tree_start : public CreatureScript
{
public:
    npc_climbing_tree_start() : CreatureScript("npc_climbing_tree_start") { }

    enum Id
    {
        QUEST_THE_BEARS_UP_THERE    = 25462,
        SPELL_RIDE_VEHICLE_SEAT_1   = 63221,
        SPELL_CLIMBING_TREE_EFFECT  = 75092
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetVehicleKit())
            return false;

        if (player->GetQuestStatus(QUEST_THE_BEARS_UP_THERE) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(creature, SPELL_CLIMBING_TREE_EFFECT, true);
            player->CastSpell(creature, SPELL_RIDE_VEHICLE_SEAT_1, true);
            return true;
        }
        return false;
    }
};

class npc_orb_of_ascension : public CreatureScript
{
public:
    npc_orb_of_ascension() : CreatureScript("npc_orb_of_ascension") { }

    enum IdActions
    {
        ACTION_ANSWERED_YES = 1,
        ACTION_ANSWERED_NO
    };

    enum Id
    {
        QUEST_CREDIT_MENTAL_TRAINING    = 39824,
        SPELL_ANSWER_THE_QUESTION       = 74009,
        QUEST_ENTRY_MENTAL_TRAINING     = 25299,
        SPELL_SELF_EXPLOSION            = 44434
    };

    struct npc_orb_of_ascensionAI : public ScriptedAI
    {
        npc_orb_of_ascensionAI(Creature* creature) : ScriptedAI(creature)
        {
            talkNumber = 0;
            isYesAnswer = false;
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                me->AI()->Talk(0);
                talkNumber = 0;
                isYesAnswer = false;
                me->DespawnOrUnsummon(180000);
                summoner->SetControlled(true, UNIT_STATE_ROOT);
            }
        }

        void DoAction(int32 action)
        {
            Unit* charmer = me->GetCharmerOrOwner();
            if (!charmer || !charmer->ToPlayer())
                return;

            switch (talkNumber)
            {
                case 0: isYesAnswer = false; break;
                case 1: isYesAnswer = true; break;
                case 2: isYesAnswer = true; break;
                case 3: isYesAnswer = false; break;
                case 4: isYesAnswer = true; break;
                case 5: isYesAnswer = false; break;
                case 6: isYesAnswer = false; break;
                case 7: isYesAnswer = true; break;
                case 8: isYesAnswer = true; break;
                case 9: isYesAnswer = false; break;
                default: break;
            }

            switch (action)
            {
                case ACTION_ANSWERED_YES:
                {
                    if (!isYesAnswer)
                    {
                        me->CastSpell(me, SPELL_SELF_EXPLOSION, true);
                        me->Kill(charmer);
                        me->DespawnOrUnsummon(1000);
                    }
                    else
                    {
                        charmer->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_MENTAL_TRAINING);
                        if (talkNumber < 10)
                        {
                            talkNumber++;
                            me->AI()->TalkWithDelay(1000, talkNumber);
                            me->CastWithDelay(1000, charmer, SPELL_ANSWER_THE_QUESTION, true);
                        }
                    }
                    break;
                }
                case ACTION_ANSWERED_NO:
                {
                    if (!isYesAnswer)
                    {
                        charmer->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_MENTAL_TRAINING);
                        if (talkNumber < 10)
                        {
                            talkNumber++;
                            me->AI()->TalkWithDelay(1000, talkNumber);
                            me->CastWithDelay(1000, charmer, SPELL_ANSWER_THE_QUESTION, true);
                        }
                        if (talkNumber == 10)
                        {
                            if (charmer->HasAura(SPELL_ANSWER_THE_QUESTION))
                                charmer->RemoveAurasDueToSpell(SPELL_ANSWER_THE_QUESTION);
                            me->DespawnOrUnsummon(1000);
                        }
                    }
                    else
                    {
                        me->CastSpell(me, SPELL_SELF_EXPLOSION, true);
                        me->Kill(charmer);
                        me->DespawnOrUnsummon(1000);
                    }
                    break;
                }
                default:
                    break;
            }
        }

    private:
        uint8 talkNumber;
        bool isYesAnswer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_orb_of_ascensionAI(creature);
    }
};

class npc_war_guardian_summoner : public CreatureScript
{
public:
    npc_war_guardian_summoner() : CreatureScript("npc_war_guardian_summoner") { }

    enum Id
    {
        QUEST_ENTRY_SPROUT_NO_MORE          = 26791,
        QUEST_ENTRY_FUNGAL_MONSTROSITIES    = 26792,

        SPELL_SUMMON_WAR_GUARDIAN           = 82535,

        QUEST_CREDIT_SUMMON                 = 44126
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if ((player->GetQuestStatus(QUEST_ENTRY_FUNGAL_MONSTROSITIES) != QUEST_STATUS_REWARDED && player->GetQuestStatus(QUEST_ENTRY_FUNGAL_MONSTROSITIES) != QUEST_STATE_NONE) || 
            (player->GetQuestStatus(QUEST_ENTRY_SPROUT_NO_MORE) != QUEST_STATUS_REWARDED && player->GetQuestStatus(QUEST_ENTRY_SPROUT_NO_MORE) != QUEST_STATE_NONE))
        {
            player->KilledMonsterCredit(QUEST_CREDIT_SUMMON);
            player->CastSpell(player, SPELL_SUMMON_WAR_GUARDIAN, true);
            return true;
        }
        return true;
    }
};

class npc_falling_boulder : public CreatureScript
{
public:
    npc_falling_boulder() : CreatureScript("npc_falling_boulder") {}

    struct npc_falling_boulderAI : public ScriptedAI
    {
        npc_falling_boulderAI(Creature* creature) : ScriptedAI(creature)
        {
            startTimer = 1*IN_MILLISECONDS;
        }

        float x, y, z, o;

        enum movePoints
        {
            MOVE_POINT_LAVAGROUND   = 1
        };

        void Reset()
        {
            startTimer = 100;
            me->SetSpeed(MOVE_RUN, 5.0f);
            me->SetSpeed(MOVE_WALK, 5.0f);
            me->GetHomePosition(x, y, z, o);
        }

        void UpdateAI(uint32 diff)
        {
            if (startTimer <= diff)
            {
                me->GetMotionMaster()->MovePoint(MOVE_POINT_LAVAGROUND, me->GetPositionX(), me->GetPositionY(), 683.0f, false);
                respawnTimer = 8*IN_MILLISECONDS;
            }
            else
                startTimer -= diff;

            if (respawnTimer <= diff)
            {
                me->NearTeleportTo(x, y, z, o);
                me->Relocate(x, y, z, o);
            }
            else
                respawnTimer -= diff;
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case MOVE_POINT_LAVAGROUND:
                {
                    me->NearTeleportTo(x, y, z, o);
                    me->Relocate(x, y, z, o);
                    startTimer = 100;
                    break;
                }
                default:
                    break;
            }
        }

        protected:
            uint16 startTimer;
            uint16 respawnTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_falling_boulderAI(creature);
    }
};

class npc_mercurial_ooze : public CreatureScript
{
public:
    npc_mercurial_ooze() : CreatureScript("npc_mercurial_ooze") { }

    struct npc_mercurial_oozeAI : public ScriptedAI
    {
        npc_mercurial_oozeAI(Creature* creature) : ScriptedAI(creature)
        {
            spellId = NULL;
            spellCastTime = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (!caster)
                return;

            if (spell->GetSchoolMask() > SPELL_SCHOOL_MASK_NORMAL)
            {
                spellId = spell->Id;
                spellCastTime = spell->CastTimeMin;
                castTimer = 100;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (castTimer <= diff)
            {
                if (!me->HasUnitState(UNIT_STATE_CASTING) && spellId != NULL && spellCastTime > 0)
                {
                    DoCastVictim(spellId);
                    castTimer = spellCastTime;
                    spellId = NULL;
                }
            }
            else
                castTimer -= diff;

            DoMeleeAttackIfReady();
        }

    protected:
        uint32 spellId;
        uint32 spellCastTime;
        uint32 castTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mercurial_oozeAI(creature);
    }
};

class npc_azil_fragment_event : public CreatureScript
{
public:
    npc_azil_fragment_event() : CreatureScript("npc_azil_fragment_event") { }

    enum Id
    {
        SPELL_AURA_PLAYER_INVISIBILITY  = 60191
    };

    enum movePoints
    {
        POINT_FACE_MILLHOUSE = 1
    };

    struct npc_azil_fragment_eventAI : public ScriptedAI
    {
        npc_azil_fragment_eventAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                summoner->AddAura(SPELL_AURA_PLAYER_INVISIBILITY, me);
                me->SetWalk(true);
                me->GetMotionMaster()->MovePoint(POINT_FACE_MILLHOUSE, 573.28f, -767.50f, 146.71f);
                me->AI()->TalkWithDelay(5000, 0, summoner->GetGUID());
                me->AI()->TalkWithDelay(24000, 1, summoner->GetGUID());
                me->AI()->TalkWithDelay(50000, 2, summoner->GetGUID());
                me->DespawnOrUnsummon(60000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_azil_fragment_eventAI(creature);
    }
};

class npc_millhouse_fragment_event : public CreatureScript
{
public:
    npc_millhouse_fragment_event() : CreatureScript("npc_millhouse_fragment_event") { }

    enum Id
    {
        SPELL_AURA_PLAYER_INVISIBILITY  = 60191
    };

    enum movePoints
    {
        POINT_FACE_MILLHOUSE = 1
    };

    struct npc_millhouse_fragment_eventAI : public ScriptedAI
    {
        npc_millhouse_fragment_eventAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                summoner->AddAura(SPELL_AURA_PLAYER_INVISIBILITY, me);
                me->AI()->TalkWithDelay(18000, 0, summoner->GetGUID());
                me->AI()->TalkWithDelay(32000, 1, summoner->GetGUID());
                me->AI()->TalkWithDelay(39000, 2, summoner->GetGUID());
                me->DespawnOrUnsummon(60000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_millhouse_fragment_eventAI(creature);
    }
};

class npc_stonescale_matriarch : public CreatureScript
{
public:
    npc_stonescale_matriarch() : CreatureScript("npc_stonescale_matriarch") {}

    struct npc_stonescale_matriarchAI : public ScriptedAI
    {
        npc_stonescale_matriarchAI(Creature* creature) : ScriptedAI(creature) {playerCharmer = NULL;}

        EventMap events;

        enum Id
        {
            NPC_ENTRY_TRAP_BUNNY    = 44144,
            SPELL_ENTRY_TRAP_BEAM   = 82576,
            SPELL_ENTRY_TRAP_SNARE  = 82869
        };

        enum bossSpells
        {
            SPELL_SAND_BREATH       = 85802,
            SPELL_STONE_SPIKE       = 83861
        };

        enum pointId
        {
            MATRIARCH_MOVE_FLY_GROUND   = 1,
            MATRIARCH_MOVE_LAND
        };

        enum actionId
        {
            ACTION_FLY_LAND     = 1,
            ACTION_ENABLE_TRAP
        };

        enum actionEvent
        {
            EVENT_SAND_BREATH   = 1,
            EVENT_STONE_SPIKE
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SAND_BREATH, urand(5000, 7500));
            events.ScheduleEvent(EVENT_STONE_SPIKE, 1000);
        }

        void EnableTraps()
        {
            std::list<Creature*> trapTriggers;
            GetCreatureListWithEntryInGrid(trapTriggers, me, NPC_ENTRY_TRAP_BUNNY, 50.0f);
            if (trapTriggers.empty())
                return;

            for (std::list<Creature*>::iterator itr = trapTriggers.begin(); itr != trapTriggers.end(); ++itr)
                (*itr)->CastWithDelay(2000, me, SPELL_ENTRY_TRAP_BEAM, true);
        }

        void DisableTraps()
        {
            std::list<Creature*> trapTriggers;
            GetCreatureListWithEntryInGrid(trapTriggers, me, NPC_ENTRY_TRAP_BUNNY, 50.0f);
            if (trapTriggers.empty())
                return;

            for (std::list<Creature*>::iterator itr = trapTriggers.begin(); itr != trapTriggers.end(); ++itr)
                (*itr)->CastStop();
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->GetMotionMaster()->MovePoint(MATRIARCH_MOVE_FLY_GROUND, -110.49f, 464.81f, 175.40f, false);
            TalkWithDelay(1500, 0, summoner->GetGUID());
            me->SetReactState(REACT_DEFENSIVE);
            playerCharmer = summoner;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FLY_LAND:
                {
                    me->GetMotionMaster()->MoveLand(MATRIARCH_MOVE_LAND, matriarchLandingPos);
                    me->SetHomePosition(matriarchLandingPos);
                    me->Relocate(matriarchLandingPos);
                    me->SetPosition(matriarchLandingPos);
                    break;
                }
                case ACTION_ENABLE_TRAP:
                {
                    EnableTraps();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->AddAura(SPELL_ENTRY_TRAP_SNARE, me);
                    TalkWithDelay(3000, 1, playerCharmer->GetGUID());
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    events.ScheduleEvent(EVENT_SAND_BREATH, urand(5000, 7500));
                    events.ScheduleEvent(EVENT_STONE_SPIKE, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case MATRIARCH_MOVE_FLY_GROUND:
                    me->AI()->DoAction(ACTION_FLY_LAND);
                    break;
                case MATRIARCH_MOVE_LAND:
                    me->AI()->DoAction(ACTION_ENABLE_TRAP);
                    break;
                default:
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            DisableTraps();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SAND_BREATH:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_SAND_BREATH);
                        events.ScheduleEvent(EVENT_SAND_BREATH, urand(5000, 7500));
                        break;
                    case EVENT_STONE_SPIKE:
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_STONE_SPIKE);
                        events.ScheduleEvent(EVENT_STONE_SPIKE, urand(3000, 4500));
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        Unit* playerCharmer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stonescale_matriarchAI(creature);
    }
};

class npc_abyssion_event : public CreatureScript
{
public:
    npc_abyssion_event() : CreatureScript("npc_abyssion_event") {}

    struct npc_abyssion_eventAI : public ScriptedAI
    {
        npc_abyssion_eventAI(Creature* creature) : ScriptedAI(creature) {playerCharmer = NULL;}

        EventMap events;

        enum Id
        {
            NPC_ENTRY_TRAP_BUNNY    = 44144,
            NPC_STORMCALLER_MYLRA   = 44956,
            NPC_EARTHEN_RING_SHAMAN = 44998,
            SPELL_ENTRY_TRAP_BEAM   = 82576,
            SPELL_ENTRY_TRAP_SNARE  = 82869,

            GO_ENTRY_FIRST_FRAGMENT_OF_THE_WORLD_PILLAR     = 204967
        };

        enum bossSpells
        {
            SPELL_RIFT_BARRAGE      = 82878,
            SPELL_SHADOW_NOVA       = 82883,
            SPELL_TWILIGHT_BREATH   = 82876,
            SPELL_TWILIGHT_SHIELD   = 84052
        };

        enum pointId
        {
            ABYSSION_MOVE_FLY_GROUND   = 1,
            ABYSSION_MOVE_LAND
        };

        enum actionId
        {
            ACTION_FLY_LAND     = 1,
            ACTION_ENABLE_TRAP
        };

        enum actionEvent
        {
            EVENT_RIFT_BARRAGE      = 1,
            EVENT_SHADOW_NOVA,
            EVENT_TWILIGHT_BREATH,
            EVENT_TWILIGHT_SHIELD
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_TWILIGHT_BREATH, urand(5000, 12500));
            events.ScheduleEvent(EVENT_RIFT_BARRAGE, urand(3000, 6000));
            events.ScheduleEvent(EVENT_SHADOW_NOVA, 60000);
            events.ScheduleEvent(EVENT_TWILIGHT_SHIELD, 70000);
        }

        void EnableTraps()
        {
            std::list<Creature*> trapTriggers;
            GetCreatureListWithEntryInGrid(trapTriggers, me, NPC_ENTRY_TRAP_BUNNY, 50.0f);
            if (trapTriggers.empty())
                return;

            for (std::list<Creature*>::iterator itr = trapTriggers.begin(); itr != trapTriggers.end(); ++itr)
                (*itr)->CastWithDelay(2000, me, SPELL_ENTRY_TRAP_BEAM, true);
        }

        void DisableTraps()
        {
            std::list<Creature*> trapTriggers;
            GetCreatureListWithEntryInGrid(trapTriggers, me, NPC_ENTRY_TRAP_BUNNY, 50.0f);
            if (trapTriggers.empty())
                return;

            for (std::list<Creature*>::iterator itr = trapTriggers.begin(); itr != trapTriggers.end(); ++itr)
                (*itr)->CastStop();
        }

        void IsSummonedBy(Unit* summoner)
        {
            // Immune to stun and silence
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->GetMotionMaster()->MovePoint(ABYSSION_MOVE_FLY_GROUND, 176.40f, -493.20f, 187.39f, false);
            TalkWithDelay(1500, 0, summoner->GetGUID());
            me->SetReactState(REACT_DEFENSIVE);
            summoner->SummonCreature(NPC_STORMCALLER_MYLRA, 203.64f, -532.59f, 172.24f, 2.32f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
            summoner->SummonCreature(NPC_EARTHEN_RING_SHAMAN, 193.37f, -519.61f, 171.34f, 2.32f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
            summoner->SummonCreature(NPC_EARTHEN_RING_SHAMAN, 184.69f, -525.10f, 171.36f, 1.91f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
            playerCharmer = summoner;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FLY_LAND:
                {
                    me->GetMotionMaster()->MoveLand(ABYSSION_MOVE_LAND, abyssionLandingPos);
                    me->SetHomePosition(abyssionLandingPos);
                    me->Relocate(abyssionLandingPos);
                    me->SetPosition(abyssionLandingPos);
                    break;
                }
                case ACTION_ENABLE_TRAP:
                {
                    EnableTraps();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->AddAura(SPELL_ENTRY_TRAP_SNARE, me);
                    TalkWithDelay(3000, 1, playerCharmer->GetGUID());
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    events.ScheduleEvent(EVENT_TWILIGHT_BREATH, urand(5000, 12500));
                    events.ScheduleEvent(EVENT_RIFT_BARRAGE, urand(3000, 6000));
                    events.ScheduleEvent(EVENT_SHADOW_NOVA, urand(45000, 50000));
                    events.ScheduleEvent(EVENT_TWILIGHT_SHIELD, 70000);
                    if (Creature* stormcallerMylra = me->FindNearestCreature(NPC_STORMCALLER_MYLRA, 100.0f, true))
                    {
                        stormcallerMylra->SetReactState(REACT_AGGRESSIVE);
                        stormcallerMylra->AI()->AttackStart(me);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case ABYSSION_MOVE_FLY_GROUND:
                    me->AI()->DoAction(ACTION_FLY_LAND);
                    break;
                case ABYSSION_MOVE_LAND:
                    me->AI()->DoAction(ACTION_ENABLE_TRAP);
                    break;
                default:
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            DisableTraps();
            me->setFaction(FACTION_FRIENDLY);
            TalkWithDelay(1000, 2, playerCharmer->GetGUID());
            me->SummonGameObject(GO_ENTRY_FIRST_FRAGMENT_OF_THE_WORLD_PILLAR, 185.20f, -502.89f, 171.70f, 0, 0, 0, 0, 1, 120);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TWILIGHT_BREATH:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_TWILIGHT_BREATH);
                        events.ScheduleEvent(EVENT_TWILIGHT_BREATH, urand(3000, 7500));
                        break;
                    case EVENT_RIFT_BARRAGE:
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_RIFT_BARRAGE);
                        events.ScheduleEvent(EVENT_RIFT_BARRAGE, 5000);
                        break;
                    case EVENT_SHADOW_NOVA:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_SHADOW_NOVA);
                        TalkWithDelay(500, 3);
                        events.ScheduleEvent(EVENT_SHADOW_NOVA, urand(45000, 50000));
                        break;
                    case EVENT_TWILIGHT_SHIELD:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_TWILIGHT_SHIELD);
                        events.ScheduleEvent(EVENT_TWILIGHT_SHIELD, 70000);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        Unit* playerCharmer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_abyssion_eventAI(creature);
    }
};

class npc_felsen_the_enduring : public CreatureScript
{
public:
    npc_felsen_the_enduring() : CreatureScript("npc_felsen_the_enduring") { }

    struct npc_felsen_the_enduringAI : public ScriptedAI
    {
        npc_felsen_the_enduringAI(Creature* creature) : ScriptedAI(creature) { }

        enum Id
        {
            QUEST_ENTRY_VIOLENT_GALE    = 26426,
            QUEST_CREDIT_VIOLENT_GALE   = 44281,
            SPELL_VIOLENT_GALE          = 87875
        };

        void Reset()
        {
            creditTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (creditTimer <= diff)
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 20.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(20.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_PLAYER)
                    {
                        if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_VIOLENT_GALE) == QUEST_STATUS_INCOMPLETE ||
                            (*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_VIOLENT_GALE) == QUEST_STATUS_COMPLETE)
                            (*itr)->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_VIOLENT_GALE);
                    }
                }
                me->AI()->Talk(0);
                creditTimer = urand(8000, 12000);
            }
            else
                creditTimer -= diff;
        }

    protected:
        uint32 creditTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_felsen_the_enduringAI(creature);
    }
};

class npc_haethen_kaul : public CreatureScript
{
public:
    npc_haethen_kaul() : CreatureScript("npc_haethen_kaul") {}

    struct npc_haethen_kaulAI : public ScriptedAI
    {
        npc_haethen_kaulAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum bossSpells
        {
            SPELL_AIRBOLT   = 83791,
            SPELL_FIREBOLT  = 83794,
            SPELL_WATERBOLT = 83795,
            SPELL_EARTHBOLT = 83799,
            SPELL_COA       = 18266,
            SPELL_SLOW      = 79880,
            SPELL_FORCE_FLY = 83412
        };

        enum actionId
        {
            ACTION_DISABLE_FIRE_SPELLS  = 1,
            ACTION_DISABLE_AIR_SPELLS,
            ACTION_DISABLE_WATER_SPELLS
        };

        enum actionEvent
        {
            EVENT_CAST_FIREBOLT     = 1,
            EVENT_CAST_AIRBOLT,
            EVENT_CAST_WATERBOLT,
            EVENT_CAST_EARTHBOLT,
            EVENT_CAST_COA,
            EVENT_CAST_SLOW
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_CAST_FIREBOLT, urand(2000, 5000));
            // Immune to stun and silence
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);
            me->SetControlled(false, UNIT_STATE_ROOT);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DISABLE_FIRE_SPELLS:
                {
                    Talk(1);
                    me->CastStop();
                    events.CancelEvent(EVENT_CAST_FIREBOLT);
                    events.ScheduleEvent(EVENT_CAST_AIRBOLT, 6000);
                    break;
                }
                case ACTION_DISABLE_AIR_SPELLS:
                {
                    Talk(2);
                    me->CastStop();
                    events.CancelEvent(EVENT_CAST_AIRBOLT);
                    events.ScheduleEvent(EVENT_CAST_WATERBOLT, 6000);
                    break;
                }
                case ACTION_DISABLE_WATER_SPELLS:
                {
                    Talk(3);
                    me->CastStop();
                    events.CancelEvent(EVENT_CAST_WATERBOLT);
                    events.ScheduleEvent(EVENT_CAST_EARTHBOLT, 8000);
                    events.ScheduleEvent(EVENT_CAST_COA, 5000);
                    events.ScheduleEvent(EVENT_CAST_SLOW, 6500);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_CAST_FIREBOLT, urand(500, 1000));
            me->SetControlled(true, UNIT_STATE_ROOT);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_FIREBOLT:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_FIREBOLT);
                        events.ScheduleEvent(EVENT_CAST_FIREBOLT, urand(3000, 4000));
                        break;
                    case EVENT_CAST_AIRBOLT:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_AIRBOLT);
                        events.ScheduleEvent(EVENT_CAST_AIRBOLT, urand(3000, 4000));
                        break;
                    case EVENT_CAST_WATERBOLT:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_WATERBOLT);
                        events.ScheduleEvent(EVENT_CAST_WATERBOLT, urand(3000, 4000));
                        break;
                    case EVENT_CAST_EARTHBOLT:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_EARTHBOLT);
                        events.ScheduleEvent(EVENT_CAST_EARTHBOLT, urand(3000, 4000));
                        break;
                    case EVENT_CAST_COA:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_COA);
                        events.ScheduleEvent(EVENT_CAST_COA, 16000);
                        break;
                    case EVENT_CAST_SLOW:
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_SLOW);
                        events.ScheduleEvent(EVENT_CAST_SLOW, 10000);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_haethen_kaulAI(creature);
    }
};

class npc_terrath : public CreatureScript
{
public:
    npc_terrath() : CreatureScript("npc_terrath") { }

    enum Id
    {
        QUEST_DONT_STOP_MOVING  = 26656,
        QUEST_CREDIT_DSM        = 46139,
        NPC_OPALESCENT_GUARDIAN = 43591
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_DONT_STOP_MOVING)
            creature->AI()->Talk(0, player->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == 1)
        {
            if (player->GetQuestStatus(QUEST_DONT_STOP_MOVING) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(QUEST_CREDIT_DSM);

            // Check before summon, to prevent infinite spawns
            if (player->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_31))
            {
                player->PlayerTalkClass->SendCloseGossip();
                return false;
            }

            for (int addSummon = 0; addSummon < 5; addSummon++)
                player->SummonCreature(NPC_OPALESCENT_GUARDIAN, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

            player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_31);
            creature->AI()->Talk(1, player->GetGUID());
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }
        return true;
    }
};

class npc_opalescent_guardian : public CreatureScript
{
public:
    npc_opalescent_guardian() : CreatureScript("npc_opalescent_guardian") {}

    struct npc_opalescent_guardianAI : public ScriptedAI
    {
        npc_opalescent_guardianAI(Creature* creature) : ScriptedAI(creature)
        {
            creditTimer = 2000;
            playerCharmer = NULL;
        }

        enum Id
        {
            NPC_ENTRY_OPAL_STONETHROWER     = 43586,
            QUEST_CREDIT_OPAL               = 43597,
            OPAL_STONETHROWER_GUID          = 744312
        };

        void IsSummonedBy(Unit* summoner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC);
            me->GetMotionMaster()->MoveFollow(summoner, 2.0f, 1+frand(1, 50));
            me->SetReactState(REACT_PASSIVE);
            playerCharmer = summoner;
            creditTimer = 2000;
        }

        void UpdateAI(uint32 diff)
        {
            if (creditTimer <= diff)
            {
                if (Creature* opalStonethrower = me->FindNearestCreature(NPC_ENTRY_OPAL_STONETHROWER, 10.0f, true))
                {
                    if (opalStonethrower->GetGUIDLow() == OPAL_STONETHROWER_GUID)
                    {
                        if (playerCharmer->GetTypeId() == TYPEID_PLAYER)
                            playerCharmer->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_OPAL);
                        me->DespawnOrUnsummon(1);
                    }
                }
                creditTimer = 2000;
            }
            else
                creditTimer -= diff;
        }

    protected:
        Unit* playerCharmer;
        uint16 creditTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_opalescent_guardianAI(creature);
    }
};

class npc_stone_drake : public CreatureScript
{
public:
    npc_stone_drake() : CreatureScript("npc_stone_drake") {}

    struct npc_stone_drakeAI : public ScriptedAI
    {
        npc_stone_drakeAI(Creature* creature) : ScriptedAI(creature) {unitVictim = NULL;}

        EventMap events;

        enum bossSpells
        {
            SPELL_RENDING_SWOOP     = 82202,
            SPELL_STONE_BREATH      = 96134,
            SPELL_WING_BUFFET       = 32914
        };

        enum pointId
        {
            DRAKE_MOVE_LAND     = 1,
        };

        enum actionId
        {
            ACTION_LAND = 1
        };

        enum eventId
        {
            EVENT_CAST_RENDING_SWOOP   = 1,
            EVENT_CAST_STONE_BREATH,
            EVENT_CAST_WING_BUFFET,
            EVENT_LANDED
        };

        void Reset()
        {
            victimX = NULL;
            victimY = NULL;
            victimZ = NULL;
            unitVictim = NULL;
            me->SetReactState(REACT_DEFENSIVE);
            me->SetCanFly(true);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->SetHealth(me->GetMaxHealth() / 3);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void EnterCombat(Unit* victim)
        {
            victimX = victim->GetPositionX();
            victimY = victim->GetPositionY();
            victimZ = victim->GetPositionZ();
            unitVictim = victim;
            if (me->IsFlying())
            {
                me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                DoAction(ACTION_LAND);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_LAND:
                {
                    if (unitVictim == NULL)
                        return;

                    Position const moveLand  = {victimX, victimY, victimZ};
                    me->StopMoving();
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                    me->GetMotionMaster()->MoveLand(DRAKE_MOVE_LAND, moveLand);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case DRAKE_MOVE_LAND:
                {
                    events.ScheduleEvent(EVENT_LANDED, 1);
                    break;
                }
                default:
                    break;
            }
        }

        void JustDied(Unit* victim)
        {
            if (victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    victim->ToPlayer()->KilledMonsterCredit(42522);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_WING_BUFFET: // Wing Buffet only on land
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_WING_BUFFET);
                        break;
                    case EVENT_CAST_STONE_BREATH:
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_STONE_BREATH);
                        events.ScheduleEvent(EVENT_CAST_STONE_BREATH, urand(9500, 13500));
                        break;
                    case EVENT_CAST_RENDING_SWOOP:
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_RENDING_SWOOP);
                        events.ScheduleEvent(EVENT_CAST_RENDING_SWOOP, 30000);
                        break;
                    case EVENT_LANDED:
                    {
                        groundX = me->GetPositionX();
                        groundY = me->GetPositionY();
                        groundZ = me->GetPositionZ();
                        Position const moveGround  = {groundX, groundY, groundZ};
                        me->SetHomePosition(moveGround);
                        me->Relocate(moveGround);
                        me->SetPosition(moveGround);
                        me->ClearUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                        me->StopMoving();
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->SetCanFly(false);
                        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        events.ScheduleEvent(EVENT_CAST_WING_BUFFET, 1000);
                        events.ScheduleEvent(EVENT_CAST_STONE_BREATH, urand(9500, 13500));
                        events.ScheduleEvent(EVENT_CAST_RENDING_SWOOP, 30000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        protected:
            Unit* unitVictim;
            float victimX, victimY, victimZ;
            float groundX, groundY, groundZ;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stone_drakeAI(creature);
    }
};

class npc_norsala_escort : public CreatureScript
{
public:
    npc_norsala_escort() : CreatureScript("npc_norsala_escort") { }

    enum Id
    {
        QUEST_ENTRY_WRATH_OF_THE_FUNGALMANCER   = 26583,
        QUEST_ENTRY_GLOP_SON_OF_GLOP            = 28390,
        QUEST_CREDIT_FUNGALMANCER_1             = 43503,
        QUEST_CREDIT_FUNGALMANCER_2             = 43372,
        NPC_ENTRY_FUNGALMANCER_GLOP             = 43372
    };

    enum actionId
    {
        ACTION_WP_START     = 1,
        ACTION_WP_RESTART,
        ACTION_WP_RESTART_2,
        ACTION_WP_FINAL,
        ACTION_ACHIEVEMENT
    };

    enum eventId
    {
        EVENT_CAST_LAVA_BURST       = 1,
        EVENT_CAST_LIGHTNING_BOLT,
        EVENT_CAST_CHAIN_HEAL
    };

    enum spellId
    {
        SPELL_LAVA_BURST        = 79886,
        SPELL_LIGHTNING_BOLT    = 79884,
        SPELL_CHAIN_HEAL        = 72014,
        SPELL_WATER_SHIELD      = 79949
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == 1)
        {
            creature->AI()->Talk(0, player->GetGUID());
            player->PlayerTalkClass->SendCloseGossip();
            player->KilledMonsterCredit(QUEST_CREDIT_FUNGALMANCER_1);
            creature->AI()->DoAction(ACTION_WP_START);
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
            return false;
        }
        return true;
    }

    struct npc_norsala_escortAI : public npc_escortAI
    {
        npc_norsala_escortAI(Creature* creature) : npc_escortAI(creature) {}

        EventMap events;

        class talkDoActionOne : public BasicEvent
        {
            public:
                explicit talkDoActionOne(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* glop = creature->FindNearestCreature(NPC_ENTRY_FUNGALMANCER_GLOP, 50.0f, true))
                    glop->AI()->DoAction(1);
                return true;
            }

            private:
                Creature* creature;
        };

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                {
                    SetEscortPaused(true);
                    Talk(1);
                    me->m_Events.AddEvent(new talkDoActionOne(me), me->m_Events.CalculateTime(6000));
                    break;
                }
                case 8:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    SetEscortPaused(true);
                    DoCast(SPELL_WATER_SHIELD);
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_CAST_LAVA_BURST, urand(4000, 6000));
                    events.ScheduleEvent(EVENT_CAST_LIGHTNING_BOLT, urand(500, 1000));
                    events.ScheduleEvent(EVENT_CAST_CHAIN_HEAL, urand(10000, 15000));
                    if (Creature* glop = me->FindNearestCreature(NPC_ENTRY_FUNGALMANCER_GLOP, 100.0f, true))
                        me->AI()->AttackStartCaster(glop, 20.0f);
                    break;
                }
                case 20:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    SetEscortPaused(true);
                    DoCast(SPELL_WATER_SHIELD);
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_CAST_LAVA_BURST, urand(4000, 6000));
                    events.ScheduleEvent(EVENT_CAST_LIGHTNING_BOLT, urand(500, 1000));
                    events.ScheduleEvent(EVENT_CAST_CHAIN_HEAL, urand(10000, 15000));
                    if (Creature* glop = me->FindNearestCreature(NPC_ENTRY_FUNGALMANCER_GLOP, 100.0f, true))
                        me->AI()->AttackStartCaster(glop, 20.0f);
                    break;
                }
                case 24:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                    me->SetReactState(REACT_AGGRESSIVE);
                    SetEscortPaused(true);
                    if (Creature* glop = me->FindNearestCreature(NPC_ENTRY_FUNGALMANCER_GLOP, 100.0f, true))
                        me->AI()->AttackStartCaster(glop, 20.0f);
                    break;
                }
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_WP_START:
                {
                    Start(true, true, NULL, NULL, false, false, true);
                    break;
                }
                case ACTION_WP_RESTART:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    SetNextWaypoint(2, true, false);
                    SetEscortPaused(false);
                    Talk(2);
                    break;
                }
                case ACTION_WP_RESTART_2:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    events.CancelEvent(EVENT_CAST_CHAIN_HEAL);
                    events.CancelEvent(EVENT_CAST_LAVA_BURST);
                    events.CancelEvent(EVENT_CAST_LIGHTNING_BOLT);
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->CastStop();
                    SetNextWaypoint(10, true, false);
                    SetEscortPaused(false);
                    Talk(3);
                    break;
                }
                case ACTION_WP_FINAL:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_PASSIVE);
                    events.CancelEvent(EVENT_CAST_CHAIN_HEAL);
                    events.CancelEvent(EVENT_CAST_LAVA_BURST);
                    events.CancelEvent(EVENT_CAST_LIGHTNING_BOLT);
                    me->AttackStop();
                    me->CastStop();
                    SetNextWaypoint(21, true, false);
                    SetEscortPaused(false);
                    SetDespawnAtEnd(false);
                    Talk(4);
                    break;
                }
                case ACTION_ACHIEVEMENT:
                {
                    // Achievement: Fungalophobia
                    if (AchievementEntry const* fungalophobia = sAchievementMgr->GetAchievement(5445))
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 50.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToPlayer() && (*itr)->m_damagedByShroom == 0)
                            {
                                if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_WRATH_OF_THE_FUNGALMANCER) == QUEST_STATUS_COMPLETE ||
                                    (*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_GLOP_SON_OF_GLOP) == QUEST_STATUS_COMPLETE)
                                    (*itr)->ToPlayer()->CompletedAchievement(fungalophobia);
                            }
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*victim*/)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (UpdateVictim())
            {
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_LAVA_BURST:
                        {
                            RESCHEDULE_IF_CASTING;
                            DoCastVictim(SPELL_LAVA_BURST);
                            events.ScheduleEvent(EVENT_CAST_LAVA_BURST, urand(4000, 6000));
                            break;
                        }
                        case EVENT_CAST_LIGHTNING_BOLT:
                        {
                            RESCHEDULE_IF_CASTING;
                            DoCastVictim(SPELL_LIGHTNING_BOLT);
                            events.ScheduleEvent(EVENT_CAST_LIGHTNING_BOLT, urand(5000, 8500));
                            break;
                        }
                        case EVENT_CAST_CHAIN_HEAL:
                        {
                            RESCHEDULE_IF_CASTING;
                            DoCast(SPELL_CHAIN_HEAL);
                            events.ScheduleEvent(EVENT_CAST_CHAIN_HEAL, urand(10000, 15000));
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_norsala_escortAI (creature);
    }
};

class npc_glop_escort : public CreatureScript
{
public:
    npc_glop_escort() : CreatureScript("npc_glop_escort") { }

    enum Id
    {
        NPC_ENTRY_EARTHMENDER_NORSALA   = 43503
    };

    enum actionId
    {
        ACTION_WP_START     = 1
    };

    enum spellId
    {
        SPELL_THROW_BOOMSHROOM      = 81320
    };

    enum eventId
    {
        EVENT_CAST_THROW_BOOMSHROOM = 1,
        EVENT_HP_PCT_66,
        EVENT_HP_PCT_33
    };

    struct npc_glop_escortAI : public npc_escortAI
    {
        npc_glop_escortAI(Creature* creature) : npc_escortAI(creature) {}

        EventMap events;

        class talkDoActionTwo : public BasicEvent
        {
            public:
                explicit talkDoActionTwo(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* norsala = creature->FindNearestCreature(NPC_ENTRY_EARTHMENDER_NORSALA, 200.0f, true))
                    norsala->AI()->DoAction(2);
                return true;
            }

            private:
                Creature* creature;
        };

        class restartNextWaypoint : public BasicEvent
        {
            public:
                explicit restartNextWaypoint(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* norsala = creature->FindNearestCreature(NPC_ENTRY_EARTHMENDER_NORSALA, 200.0f, true))
                    norsala->AI()->DoAction(3);
                return true;
            }

            private:
                Creature* creature;
        };

        class restartFinalWaypoint : public BasicEvent
        {
            public:
                explicit restartFinalWaypoint(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* norsala = creature->FindNearestCreature(NPC_ENTRY_EARTHMENDER_NORSALA, 200.0f, true))
                    norsala->AI()->DoAction(4);
                return true;
            }

            private:
                Creature* creature;
        };

        class jumpEvent : public BasicEvent
        {
            public:
                explicit jumpEvent(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                creature->SetReactState(REACT_DEFENSIVE);
                creature->SetControlled(true, UNIT_STATE_ROOT);
                creature->AI()->TalkWithDelay(8000, 3);
                return true;
            }

            private:
                Creature* creature;
        };

        class startOutro : public BasicEvent
        {
            public:
                explicit startOutro(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* norsala = creature->FindNearestCreature(NPC_ENTRY_EARTHMENDER_NORSALA, 200.0f, true))
                {
                    norsala->AI()->TalkWithDelay(5000, 5);
                    norsala->AI()->TalkWithDelay(11000, 6);
                    norsala->AI()->DoAction(5);
                    norsala->DespawnOrUnsummon(20000);
                }
                return true;
            }

            private:
                Creature* creature;
        };

        void JustDied(Unit* /*killer*/)
        {
            me->AI()->Talk(4);
            me->m_Events.AddEvent(new startOutro(me), me->m_Events.CalculateTime(1000));
            me->DespawnOrUnsummon(20000);
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*victim*/)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
            events.ScheduleEvent(EVENT_CAST_THROW_BOOMSHROOM, 3000);
            if (!phaseTwoDone)
            {
                Talk(1);
                events.ScheduleEvent(EVENT_HP_PCT_66, 1000);
            }
            if (phaseTwoDone && !phaseThreeDone)
                events.ScheduleEvent(EVENT_HP_PCT_33, 1000);

            // Immune to stun and silence
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 9:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    SetEscortPaused(true);
                    events.ScheduleEvent(EVENT_CAST_THROW_BOOMSHROOM, 3000);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                case 19:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    SetEscortPaused(true);
                    events.ScheduleEvent(EVENT_CAST_THROW_BOOMSHROOM, 3000);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                case 24:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    me->SetOrientation(3.82f);
                    TalkWithDelay(1000, 3);
                    events.ScheduleEvent(EVENT_CAST_THROW_BOOMSHROOM, 3000);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_WP_START:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                    phaseTwoDone = false;
                    phaseThreeDone = false;
                    me->SetHealth(me->GetMaxHealth());
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                    Start(true, true, NULL, NULL, true, false, true);
                    Talk(0);
                    me->m_Events.AddEvent(new talkDoActionTwo(me), me->m_Events.CalculateTime(5000));
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (UpdateVictim())
            {
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_THROW_BOOMSHROOM:
                        {
                            DoCastVictim(SPELL_THROW_BOOMSHROOM);
                            events.ScheduleEvent(EVENT_CAST_THROW_BOOMSHROOM, 4000);
                            break;
                        }
                        case EVENT_HP_PCT_66:
                        {
                            if (me->GetHealth() > me->GetMaxHealth() * 0.66f && !phaseTwoDone && !phaseThreeDone)
                            {
                                events.ScheduleEvent(EVENT_HP_PCT_66, 1000);
                                return;
                            }

                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                            me->SetHealth(me->GetMaxHealth() * 0.45f);
                            events.ScheduleEvent(EVENT_HP_PCT_33, 1000);
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->CastStop();
                            SetNextWaypoint(9, true, false);
                            SetEscortPaused(false);
                            me->m_Events.AddEvent(new restartNextWaypoint(me), me->m_Events.CalculateTime(3000));
                            TalkWithDelay(8500, 2);
                            events.CancelEvent(EVENT_HP_PCT_66);
                            phaseTwoDone = true;
                            SetDespawnAtEnd(false);
                            break;
                        }
                        case EVENT_HP_PCT_33:
                        {
                            if (me->GetHealth() > me->GetMaxHealth() * 0.33f && phaseTwoDone && !phaseThreeDone)
                            {
                                events.ScheduleEvent(EVENT_HP_PCT_33, 1000);
                                return;
                            }

                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
                            me->SetHealth(me->GetMaxHealth() * 0.20f);
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->CastStop();
                            me->m_Events.AddEvent(new restartFinalWaypoint(me), me->m_Events.CalculateTime(2000));
                            SetNextWaypoint(20, true, false);
                            SetEscortPaused(false);
                            events.CancelEvent(EVENT_HP_PCT_66);
                            events.CancelEvent(EVENT_HP_PCT_33);
                            me->GetMotionMaster()->MoveJump(1538.02f, -524.08f, 169.47f, 30.0f, 8.0f);
                            me->m_Events.AddEvent(new jumpEvent(me), me->m_Events.CalculateTime(3500));
                            events.ScheduleEvent(EVENT_CAST_THROW_BOOMSHROOM, 10000);
                            phaseThreeDone = true;
                            break;
                        }
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        }

        protected:
            bool phaseTwoDone;
            bool phaseThreeDone;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_glop_escortAI (creature);
    }
};

class npc_boomshroom : public CreatureScript
{
public:
    npc_boomshroom() : CreatureScript("npc_boomshroom") {}

    struct npc_boomshroomAI : public ScriptedAI
    {
        npc_boomshroomAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum bossSpells
        {
            SPELL_BOOMSHROOM_EXPLOSION  = 81319
        };

        enum actionEvent
        {
            EVENT_GROWTH    = 1,
            EVENT_EXPLODE
        };

        void IsSummonedBy(Unit* summoner)
        {
            me->setFaction(summoner->getFaction());
            events.ScheduleEvent(EVENT_GROWTH, 3000);
            events.ScheduleEvent(EVENT_EXPLODE, 10000);
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GROWTH:
                    {
                        me->SetObjectScale(me->GetObjectSize()+0.085f);
                        events.ScheduleEvent(EVENT_GROWTH, 3000);
                        break;
                    }
                    case EVENT_EXPLODE:
                    {
                        DoCast(SPELL_BOOMSHROOM_EXPLOSION);
                        me->DespawnOrUnsummon(1000);
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
        return new npc_boomshroomAI(creature);
    }
};

class npc_boulder_platform : public CreatureScript
{
public:
    npc_boulder_platform() : CreatureScript("npc_boulder_platform") {}

    struct npc_boulder_platformAI : public ScriptedAI
    {
        npc_boulder_platformAI(Creature* creature) : ScriptedAI(creature) {playerPassenger = NULL;}

        class startActionDie : public BasicEvent
        {
            public:
                explicit startActionDie(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->AI()->DoAction(3);
                return true;
            }

            private:
                Creature* creature;
        };

        EventMap events;

        enum Id
        {
            NPC_ENTRY_AEOSERA   = 43641
        };

        enum npcSpells
        {
            SPELL_CRYSTALLINE_SURGE     = 84493,
            SPELL_CRYSTALLINE_BARRIER   = 84445,
            SPELL_RIDE_BOULDER          = 84499,
            SPELL_EXPLOSION_VISUAL      = 71495,
            SPELL_ROLLING_VISUAL        = 96831,
            SPELL_BOULDER_VISUAL        = 84355
        };

        enum actionEvent
        {
            ACTION_DAMAGED  = 1,
            ACTION_DIE,
            ACTION_FINISH
        };

        enum eventId
        {
            EVENT_CAST_CRYSTALLINE_SURGE    = 1,
            EVENT_CAST_CRYSTALLINE_BARRIER,
            EVENT_RESET_CAST_TIMERS
        };

        enum pointId
        {
            POINT_AIR       = 1,
            POINT_GROUND,
            POINT_FINISH
        };

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->RemoveAurasDueToSpell(SPELL_ROLLING_VISUAL);
            me->RemoveAurasDueToSpell(SPELL_BOULDER_VISUAL);
            me->CastSpell(me, SPELL_BOULDER_VISUAL, true);
            me->NearTeleportTo(me->GetHomePosition());
            me->Relocate(me->GetHomePosition());
            me->SetPosition(me->GetHomePosition());
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (apply)
            {
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                me->setFaction(passenger->getFaction());
                playerPassenger = passenger;
                if (Creature* aeosera = me->FindNearestCreature(NPC_ENTRY_AEOSERA, 300.0f, true))
                {
                    if (aeosera->isMoving() || aeosera->HasUnitState(UNIT_STATE_CASTING))
                        return;

                    aeosera->AI()->AttackStart(me);
                    aeosera->AI()->DoAction(1);
                }
            }
            else
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                events.ScheduleEvent(EVENT_CAST_CRYSTALLINE_SURGE, urand (3000, 10000));
                events.ScheduleEvent(EVENT_CAST_CRYSTALLINE_BARRIER, urand(3000, 10000));
                events.ScheduleEvent(EVENT_RESET_CAST_TIMERS, 60000);
                playerPassenger = NULL;
            }
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DAMAGED:
                {
                    if (playerPassenger != NULL)
                        TalkWithDelay(1000, 0, playerPassenger->GetGUID());
                    break;
                }
                case ACTION_DIE:
                {
                    me->CastSpell(me, SPELL_EXPLOSION_VISUAL, true);
                    me->AddAura(SPELL_ROLLING_VISUAL, me);
                    me->CastWithDelay(urand(1000, 3000), me, SPELL_EXPLOSION_VISUAL, true);
                    me->CastWithDelay(urand(1000, 4000), me, SPELL_EXPLOSION_VISUAL, true);
                    me->CastWithDelay(urand(1000, 5000), me, SPELL_EXPLOSION_VISUAL, true);
                    me->CastWithDelay(urand(1000, 6000), me, SPELL_EXPLOSION_VISUAL, true);
                    me->GetMotionMaster()->MovePoint(POINT_GROUND, me->GetPositionX(), me->GetPositionY(), 181.05f);
                    me->SetSpeed(MOVE_WALK, 3.0f, true);
                    me->RemoveAurasDueToSpell(SPELL_RIDE_BOULDER);
                    events.CancelEvent(EVENT_CAST_CRYSTALLINE_SURGE);
                    events.CancelEvent(EVENT_CAST_CRYSTALLINE_BARRIER);
                    events.CancelEvent(EVENT_RESET_CAST_TIMERS);
                    me->RemoveAurasDueToSpell(SPELL_CRYSTALLINE_SURGE);
                    me->RemoveAurasDueToSpell(SPELL_CRYSTALLINE_BARRIER);
                    me->CastStop();
                    break;
                }
                case ACTION_FINISH:
                {
                    me->GetMotionMaster()->MovePoint(POINT_FINISH, me->GetPositionX(), me->GetPositionY(), 181.05f);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_GROUND:
                {
                    me->RemoveAurasDueToSpell(SPELL_ROLLING_VISUAL);
                    me->RemoveAurasDueToSpell(SPELL_RIDE_BOULDER);
                    me->NearTeleportTo(me->GetHomePosition());
                    me->Relocate(me->GetHomePosition());
                    me->SetPosition(me->GetHomePosition());
                    break;
                }
                case POINT_FINISH:
                {
                    me->RemoveAurasDueToSpell(SPELL_ROLLING_VISUAL);
                    me->RemoveAurasDueToSpell(SPELL_RIDE_BOULDER);
                    me->RemoveAurasDueToSpell(SPELL_RIDE_BOULDER);
                    me->NearTeleportTo(me->GetHomePosition());
                    me->Relocate(me->GetHomePosition());
                    me->SetPosition(me->GetHomePosition());
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
                    case EVENT_CAST_CRYSTALLINE_SURGE:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_CRYSTALLINE_SURGE);
                        events.ScheduleEvent(EVENT_CAST_CRYSTALLINE_SURGE, urand(5000, 10000));
                        events.CancelEvent(EVENT_CAST_CRYSTALLINE_SURGE);
                        break;
                    }
                    case EVENT_CAST_CRYSTALLINE_BARRIER:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_CRYSTALLINE_BARRIER);
                        events.ScheduleEvent(EVENT_CAST_CRYSTALLINE_BARRIER, urand(5000, 10000));
                        events.CancelEvent(EVENT_CAST_CRYSTALLINE_BARRIER);
                        break;
                    }
                    case EVENT_RESET_CAST_TIMERS:
                    {
                        events.ScheduleEvent(EVENT_CAST_CRYSTALLINE_SURGE, urand(5000, 10000));
                        events.ScheduleEvent(EVENT_CAST_CRYSTALLINE_BARRIER, urand(5000, 10000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerPassenger;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_boulder_platformAI(creature);
    }
};

class npc_aeosera_event : public CreatureScript
{
public:
    npc_aeosera_event() : CreatureScript("npc_aeosera_event") {}

    struct npc_aeosera_eventAI : public ScriptedAI
    {
        npc_aeosera_eventAI(Creature* creature) : ScriptedAI(creature) {playerSummoner = NULL;}

        EventMap events;

        enum Id
        {
            NPC_ENTRY_BOULDER_PLATFORM      = 45191,
            NPC_ENTRY_TERRATH               = 42466,
            QUEST_ENTRY_RESONATING_BLOW     = 26659,
            QUEST_ENTRY_THE_RESTLESS_BROOD  = 28391,
            QUEST_CREDIT_RESONATING_BLOW    = 43641
        };

        enum npcSpells
        {
            SPELL_CAST_SEARING_BREATH   = 84448
        };

        enum actionEvent
        {
            ACTION_ATTRACTED    = 1
        };

        enum eventId
        {
            EVENT_CAST_SEARING_BREATH   = 1,
            EVENT_CHECK_HEALTH,
            EVENT_DISABLE_ACHIEVEMENT
        };

        enum pointId
        {
            POINT_AIR       = 1,
            POINT_BOULDER
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ATTRACTED:
                {
                    if (Unit* victim = me->getVictim())
                    {
                        x = victim->GetPositionX()-frand(1, 5);
                        y = victim->GetPositionY()-frand(1, 5);
                        z = victim->GetPositionZ()+0.5f;

                        me->GetMotionMaster()->MovePoint(POINT_BOULDER, x, y, z, false);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                TalkWithDelay(4000, 0, summoner->GetGUID());
                me->GetMotionMaster()->MovePoint(POINT_AIR, 1931.82f, 1415.75, 281.43f, false);
                playerSummoner = summoner;
            }
            elegibleForAchievement = true;
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 1000);
            events.ScheduleEvent(EVENT_DISABLE_ACHIEVEMENT, 80000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_BOULDER:
                {
                    events.ScheduleEvent(EVENT_CAST_SEARING_BREATH, 5000);
                    break;
                }
                case POINT_AIR:
                {
                    Talk(1, playerSummoner->GetGUID());
                    break;
                }
                default:
                    break;
            }
        }

        void SearchBoulders()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(150.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr))
                {
                    if ((*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() ==  NPC_ENTRY_BOULDER_PLATFORM)
                    {
                        (*itr)->SetSpeed(MOVE_WALK, 2.5f, true);
                        (*itr)->ToCreature()->AI()->DoAction(3);
                        (*itr)->ToCreature()->setFaction(FACTION_FRIENDLY);
                    }
                    if ((*itr)->ToPlayer())
                    {
                        if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_RESONATING_BLOW) == QUEST_STATUS_INCOMPLETE ||
                            (*itr)->ToPlayer()->GetQuestStatus(QUEST_ENTRY_THE_RESTLESS_BROOD) == QUEST_STATUS_INCOMPLETE)
                        {
                            (*itr)->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_RESONATING_BLOW);
                            if (elegibleForAchievement)
                            {
                                // Achievement: My Very Own Broodmother
                                if (AchievementEntry const* broodmother = sAchievementMgr->GetAchievement(5447))
                                    (*itr)->ToPlayer()->CompletedAchievement(broodmother);
                            }
                        }
                    }
                }
            }
            if (Creature* terrath = me->FindNearestCreature(NPC_ENTRY_TERRATH, 150.0f, true))
            {
                terrath->AI()->TalkWithDelay(5000, 3);
                terrath->DespawnOrUnsummon(20000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_SEARING_BREATH:
                    {
                        DoCastVictim(SPELL_CAST_SEARING_BREATH);
                        events.CancelEvent(EVENT_CAST_SEARING_BREATH);
                        break;
                    }
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealth() > 40000)
                        {
                            events.ScheduleEvent(EVENT_CHECK_HEALTH, 1000);
                            break;
                        }

                        events.CancelEvent(EVENT_CHECK_HEALTH);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        me->DespawnOrUnsummon(10000);
                        me->AI()->TalkWithDelay(1000, 2);
                        SearchBoulders();
                        EnterEvadeMode();
                        break;
                    }
                    case EVENT_DISABLE_ACHIEVEMENT:
                    {
                        elegibleForAchievement = false;
                        events.CancelEvent(EVENT_DISABLE_ACHIEVEMENT);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerSummoner;
        float x, y, z;
        bool elegibleForAchievement;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aeosera_eventAI(creature);
    }
};

class npc_zoltrik_drakebane : public CreatureScript
{
public:
    npc_zoltrik_drakebane() : CreatureScript("npc_zoltrik_drakebane") {}

    struct npc_zoltrik_drakebaneAI : public ScriptedAI
    {
        npc_zoltrik_drakebaneAI(Creature* creature) : ScriptedAI(creature)
        {
            phase = 1;
            playerInvoker = NULL;
        }

        EventMap events;

        enum Id
        {
            NPC_ENTRY_TWILIGHT_PYREMAW   = 42824,
            NPC_ENTRY_TERRATH            = 42614,
            NPC_ENTRY_CW_STONE_DRAKE     = 44939,
            PLAY_SOUND_CALL_DRAKE        = 3980
        };

        enum textId
        {
            TALK_0 = 0,
            TALK_1,
            TALK_2
        };

        enum npcSpells
        {
            SPELL_CHOCKING_SMOKE_BOMBS  = 82589,
            SPELL_DRAKE_BANE            = 86717,
            SPELL_SHOOT                 = 84837,
            SPELL_CALL_DRAKE            = 82553,    // Dunno if this will be helpful
            SPELL_RIDE_DRAKE_PLR        = 46598,
            SPELL_JUMP_DRAKES           = 82779
        };

        enum actionEvent
        {
            ACTION_TO_DRAKE   = 1
        };

        enum eventId
        {
            EVENT_CHOCKING_SMOKE_BOMBS  = 1,
            EVENT_DRAKE_BANE,
            EVENT_SHOOT,
            EVENT_CHECK_HEALTH,
            EVENT_CHECK_INVOKER
        };

        enum pointId
        {
            POINT_TO_DRAKE    = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TO_DRAKE:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                    me->CastStop();
                    me->AttackStop();
                    me->StopMoving();
                    me->GetMotionMaster()->MovePoint(POINT_TO_DRAKE, 1478.93f, -168.59f, 55.65f);
                    Talk(1);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_DRAKE:
                {
                    me->PlayDirectSound(PLAY_SOUND_CALL_DRAKE);
                    if (Creature* drake = me->FindNearestCreature(NPC_ENTRY_TWILIGHT_PYREMAW, 20.0f, true))
                    {
                        if (playerInvoker && playerInvoker->IsInWorld() && playerInvoker != NULL)
                        {
                            me->AddThreat(playerInvoker, 100000.0f);
                            me->SetInCombatWith(playerInvoker);
                            me->AI()->AttackStart(playerInvoker);
                            events.ScheduleEvent(EVENT_DRAKE_BANE, urand(3000, 5000));
                            events.ScheduleEvent(EVENT_SHOOT, urand(3500, 4000));
                        }
                        else
                        {
                            TeleportOnStart();
                            EnterEvadeMode();
                            return;
                        }
                        drake->SetReactState(REACT_PASSIVE);
                        drake->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                        me->EnterVehicle(drake, 0);
                        events.ScheduleEvent(EVENT_DRAKE_BANE, urand(20000, 25000));
                        events.ScheduleEvent(EVENT_SHOOT, urand(1500, 3500));
                        me->DespawnOrUnsummon(300000);
                        me->SetSpeed(MOVE_WALK, 2.2f, true);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                        drake->GetMotionMaster()->MovePoint(0, 1457.33f, -187.78f, 52.20f, false);
                        TalkWithDelay(30000, 2);
                        TalkWithDelay(75000, 3);
                        me->SetHomePosition(1498.52f, 498.80f, 420.51f, me->GetOrientation());
                    }
                    if (Creature* terrath = me->FindNearestCreature(NPC_ENTRY_TERRATH, 150.0f, true))
                    {
                        terrath->AI()->TalkWithDelay(5000, 0);
                        if (playerInvoker && playerInvoker != NULL && playerInvoker->IsInWorld())
                        {
                            playerInvoker->SummonCreature(NPC_ENTRY_CW_STONE_DRAKE, 1482.76f, -199.38f, 51.94f, 1.88f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            if (Creature* stoneDrake = me->FindNearestCreature(NPC_ENTRY_CW_STONE_DRAKE, 100.0f, true))
                            {
                                playerInvoker->CastWithDelay(12000, stoneDrake, SPELL_RIDE_DRAKE_PLR, true);
                                stoneDrake->AI()->TalkWithDelay(24500, 0, playerInvoker->GetGUID());
                                if (Creature* drake = me->FindNearestCreature(NPC_ENTRY_TWILIGHT_PYREMAW, 100.0f, true))
                                    stoneDrake->CastWithDelay(32000, drake, SPELL_JUMP_DRAKES, true);
                            }
                        }
                    }
                    phase = 2;
                    break;
                }
                default:
                    break;
            }
        }

        void TeleportOnStart()
        {
            phase = 1;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
            playerInvoker = NULL;
            me->SetHomePosition(1497.82f, -165.34f, 55.99f, 6.19f);
            me->NearTeleportTo(1497.82f, -165.34f, 55.99f, 6.19f);
            EnterEvadeMode();
        }

        void EnterCombat(Unit* who)
        {
            if (phase == 1)
                Talk(TALK_0);

            events.ScheduleEvent(EVENT_DRAKE_BANE, urand(3000, 8000));
            events.ScheduleEvent(EVENT_SHOOT, urand(3500, 8500));
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 1000);
            events.ScheduleEvent(EVENT_CHECK_INVOKER, 5000);
            playerInvoker = who;
        };

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHOCKING_SMOKE_BOMBS:
                    {
                        if (playerInvoker && playerInvoker->IsInWorld() && playerInvoker != NULL)
                            playerInvoker->AddAura(SPELL_CHOCKING_SMOKE_BOMBS, playerInvoker);
                        else
                        {
                            TeleportOnStart();
                            me->AI()->EnterEvadeMode();
                            break;
                        }
                        events.CancelEvent(EVENT_CHOCKING_SMOKE_BOMBS);
                        DoAction(ACTION_TO_DRAKE);
                        break;
                    }
                    case EVENT_DRAKE_BANE:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_DRAKE_BANE);
                        events.ScheduleEvent(EVENT_DRAKE_BANE, urand(3000, 8000));
                        break;
                    }
                    case EVENT_SHOOT:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_SHOOT);
                        events.ScheduleEvent(EVENT_SHOOT, urand(3500, 8500));
                        break;
                    }
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealth() > 70000)
                        {
                            events.ScheduleEvent(EVENT_CHECK_HEALTH, 1000);
                            break;
                        }
                        DoAction(ACTION_TO_DRAKE);
                        break;
                    }
                    case EVENT_CHECK_INVOKER:
                    {
                        if (!playerInvoker)
                        {
                            TeleportOnStart();
                            EnterEvadeMode();
                            break;
                        }
                        events.ScheduleEvent(EVENT_CHECK_INVOKER, 5000);
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        }

        protected:
            uint8 phase;
            Unit* playerInvoker;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_zoltrik_drakebaneAI(creature);
    }
};

class npc_invisible_trigger_one : public CreatureScript
{
public:
    npc_invisible_trigger_one() : CreatureScript("npc_invisible_trigger_one") {}

    struct npc_invisible_trigger_oneAI : public ScriptedAI
    {
        npc_invisible_trigger_oneAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum npcId
        {
            NPC_TWILIGHT_DEFILER        = 44680,
            NPC_TWILIGHT_HERETIC        = 44681,
            NPC_DESECRATED_EARTHRAGER   = 44683
        };

        enum eventId
        {
            EVENT_SUMMON_HERETIC    = 1,
            EVENT_SUMMON_DEFILER,
            EVENT_SUMMON_EARTHRAGER
        };

        void Reset()
        {
            // Only in Chamber of Respite (Deepholm)
            if (me->GetMapId() == 646 && me->GetZoneId() == 5042 && me->GetAreaId() == 5395)
            {
                events.ScheduleEvent(EVENT_SUMMON_HERETIC, urand(25000, 40000));
                events.ScheduleEvent(EVENT_SUMMON_DEFILER, urand(45000, 55000));
                events.ScheduleEvent(EVENT_SUMMON_EARTHRAGER, urand(60000, 90000));
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_HERETIC:
                    {
                        SummonHeretics();
                        events.RescheduleEvent(EVENT_SUMMON_HERETIC, urand(25000, 40000));
                        break;
                    }
                    case EVENT_SUMMON_DEFILER:
                    {
                        SummonDefilers();
                        events.RescheduleEvent(EVENT_SUMMON_DEFILER, urand(45000, 55000));
                        break;
                    }
                    case EVENT_SUMMON_EARTHRAGER:
                    {
                        me->SummonCreature(NPC_DESECRATED_EARTHRAGER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        events.RescheduleEvent(EVENT_SUMMON_EARTHRAGER, urand(60000, 90000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void SummonHeretics()
        {
            me->SummonCreature(NPC_TWILIGHT_HERETIC, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            me->SummonCreature(NPC_TWILIGHT_HERETIC, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            me->SummonCreature(NPC_TWILIGHT_HERETIC, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }

        void SummonDefilers()
        {
            me->SummonCreature(NPC_TWILIGHT_DEFILER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            me->SummonCreature(NPC_TWILIGHT_DEFILER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            me->SummonCreature(NPC_TWILIGHT_DEFILER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_invisible_trigger_oneAI(creature);
    }
};

class npc_earthcaller_torunscar : public CreatureScript
{
public:
    npc_earthcaller_torunscar() : CreatureScript("npc_earthcaller_torunscar") { }

    class eventUnmergeFragments : public BasicEvent
    {
        public:
            explicit eventUnmergeFragments(Creature* creature) : creature(creature) {}

            enum goId
            {
                GO_FIRST_FRAGMENT   = 719181,
                GO_SECOND_FRAGMENT  = 719185,
                GO_THIRD_FRAGMENT   = 719188,

                GO_FRAGMENT_ENTRY   = 204577
            };

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (GameObject* firstFragment = creature->FindNearestGameObject(GO_FRAGMENT_ENTRY, 100.0f))
                {
                    if (firstFragment->GetGUIDLow() == GO_FIRST_FRAGMENT)
                        firstFragment->SetGoState(GO_STATE_READY);
                }
                if (GameObject* secondFragment = creature->FindNearestGameObject(GO_FRAGMENT_ENTRY, 100.0f))
                {
                    if (secondFragment->GetGUIDLow() == GO_SECOND_FRAGMENT)
                        secondFragment->SetGoState(GO_STATE_READY);
                }
                if (GameObject* thirdFragment = creature->FindNearestGameObject(GO_FRAGMENT_ENTRY, 100.0f))
                {
                    if (thirdFragment->GetGUIDLow() == GO_THIRD_FRAGMENT)
                        thirdFragment->SetGoState(GO_STATE_READY);
                }
                return true;
            }

        private:
            Creature* creature;
    };

    enum Id
    {
        QUEST_ENTRY_THE_BINDING     = 26971,
        NPC_HIGH_PRIESTESS_LORTHUNA = 43837,
        NPC_ENTRY_MARUUT            = 43818
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_THE_BINDING)
        {
            Creature* lorthuna = player->FindNearestCreature(NPC_HIGH_PRIESTESS_LORTHUNA, 200.0f, true);
            if (!lorthuna)
            {
                // Respawn if dead!
                if (Creature* maruut = creature->FindNearestCreature(NPC_ENTRY_MARUUT, 85.0f, false))
                    maruut->Respawn();
                player->SummonCreature(NPC_HIGH_PRIESTESS_LORTHUNA, 978.70f, 562.99f, -49.28f, 5.44f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                creature->m_Events.AddEvent(new eventUnmergeFragments(creature), creature->m_Events.CalculateTime(2000));
            }
        }
        return true;
    }

    struct npc_earthcaller_torunscarAI : public ScriptedAI
    {
        npc_earthcaller_torunscarAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_CAST_BEAM, 500);
        }

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_TRIGGER_BEAM  = 28332
        };

        enum eventId
        {
            EVENT_CAST_BEAM     = 1
        };

        enum spellId
        {
            SPELL_WHITE_BEAM    = 40193
        };

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_BEAM:
                    {
                        if (Creature* beamTarget = me->FindNearestCreature(NPC_ENTRY_TRIGGER_BEAM, 100.0f, true))
                            me->CastSpell(beamTarget, SPELL_WHITE_BEAM, true);
                        events.ScheduleEvent(EVENT_CAST_BEAM, 30000);
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
        return new npc_earthcaller_torunscarAI(creature);
    }
};

class npc_high_priestess_lorthuna : public CreatureScript
{
public:
    npc_high_priestess_lorthuna() : CreatureScript("npc_high_priestess_lorthuna") {}

    struct npc_high_priestess_lorthunaAI : public ScriptedAI
    {
        npc_high_priestess_lorthunaAI(Creature* creature) : ScriptedAI(creature)
        {
            unitSummoner = NULL;
        }

        EventMap events;

        enum Id
        {
            NPC_ENTRY_TORUNSCAR         = 43835,
            NPC_ENTRY_MARUUT            = 43818,
            NPC_ENTRY_MAHAAT            = 44830,
            NPC_ENTRY_THERAZANE         = 43802,
            QUEST_THE_BINDING           = 26971
        };

        enum npcSpells
        {
            SPELL_EARTHEN_ASCENSION     = 83593,
            SPELL_EXECUTION             = 83519,
            SPELL_SHADOW_BOLT           = 83596,
            SPELL_SHADOW_BOLT_VOLLEY    = 83597,
            SPELL_SHADOW_STRIDE         = 83599,
            SPELL_SHADOW_FISSURE        = 57579,
            SPELL_TELEPORT_EFFECT       = 52096,
            SPELL_FLYBY_CAMERA          = 83659,
            SPELL_CAMERA_FADE           = 89082
        };

        enum eventId
        {
            EVENT_EARTHEN_ASCENSION     = 1,
            EVENT_SHADOW_BOLT,
            EVENT_SHADOW_BOLT_VOLLEY,
            EVENT_SHADOW_STRIDE,
            EVENT_SHADOW_FISSURE,
            EVENT_CHECK_HEALTH
        };

        enum pointId
        {
            POINT_ENTRANCE  = 1
        };

        enum actionEvent
        {
            ACTION_TALK_0   = 1,
            ACTION_ATTACK,
            ACTION_SWITCH
        };

        class doStartAttack : public BasicEvent
        {
            public:
                explicit doStartAttack(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->AI()->DoAction(ACTION_ATTACK);
                return true;
            }

            private:
                Creature* creature;
        };

        class summonMahatAndTherazane : public BasicEvent
        {
            public:
                explicit summonMahatAndTherazane(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->SummonCreature(NPC_ENTRY_THERAZANE, 971.21f, 523.53f, -49.33f, 0.22f, TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                creature->SummonCreature(NPC_ENTRY_MAHAAT, 974.32f, 508.67f, -49.33f, 0.19f, TEMPSUMMON_TIMED_DESPAWN, 90000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                return true;
            }

            private:
                Creature* creature;
        };

        class eventKillMaruut : public BasicEvent
        {
            public:
                explicit eventKillMaruut(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* maruut = creature->FindNearestCreature(NPC_ENTRY_MARUUT, 10.0f, true))
                {
                    creature->PlayDirectSound(20941);
                    maruut->Kill(maruut, false);
                }
                return true;
            }

            private:
                Creature* creature;
        };

        class eventMergeFragments : public BasicEvent
        {
            public:
                explicit eventMergeFragments(Creature* creature) : creature(creature) {}

            enum goId
            {
                GO_FIRST_FRAGMENT   = 719181,
                GO_SECOND_FRAGMENT  = 719185,
                GO_THIRD_FRAGMENT   = 719188,

                GO_FRAGMENT_ENTRY   = 204577
            };

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (GameObject* firstFragment = creature->FindNearestGameObject(GO_FRAGMENT_ENTRY, 100.0f))
                {
                    if (firstFragment->GetGUIDLow() == GO_FIRST_FRAGMENT)
                        firstFragment->SetGoState(GO_STATE_ACTIVE);
                }
                if (GameObject* secondFragment = creature->FindNearestGameObject(GO_FRAGMENT_ENTRY, 100.0f))
                {
                    if (secondFragment->GetGUIDLow() == GO_SECOND_FRAGMENT)
                        secondFragment->SetGoState(GO_STATE_ACTIVE);
                }
                if (GameObject* thirdFragment = creature->FindNearestGameObject(GO_FRAGMENT_ENTRY, 100.0f))
                {
                    if (thirdFragment->GetGUIDLow() == GO_THIRD_FRAGMENT)
                        thirdFragment->SetGoState(GO_STATE_ACTIVE);
                }
                return true;
            }

            private:
                Creature* creature;
        };

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                unitSummoner = summoner;
                me->CastSpell(me, SPELL_TELEPORT_EFFECT, true);
                me->SetPhaseMask(summoner->GetPhaseMask(), true);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                me->SetWalk(false);
                me->GetMotionMaster()->MovePoint(POINT_ENTRANCE, 995.24f, 524.34f, -49.33f);

                // Immune to stun and silence
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TALK_0:
                {
                    Talk(0);
                    if (Creature* maruut = me->FindNearestCreature(NPC_ENTRY_MARUUT, 15.0f, true))
                    {
                        me->SetOrientation(maruut->GetOrientation());
                        me->CastWithDelay(3000, maruut, SPELL_SHADOW_FISSURE, true);
                        me->m_Events.AddEvent(new eventKillMaruut(me), me->m_Events.CalculateTime(4000));
                    }
                    if (Creature* torunscar = me->FindNearestCreature(NPC_ENTRY_TORUNSCAR, 85.0f, true))
                    {
                        torunscar->AI()->TalkWithDelay(6000, 0);
                        me->m_Events.AddEvent(new doStartAttack(me), me->m_Events.CalculateTime(6500));
                    }
                    break;
                }
                case ACTION_ATTACK:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    if (unitSummoner)
                        AttackStart(unitSummoner);
                    else
                    {
                        if (Player* playerTarget = me->FindNearestPlayer(80.0f, true))
                            AttackStart(playerTarget);
                    }
                    break;
                }
                case ACTION_SWITCH:
                {
                    events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, 1000);
                    events.ScheduleEvent(EVENT_SHADOW_BOLT, 6000);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ENTRANCE:
                {
                    DoAction(ACTION_TALK_0);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 1000);
            events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(3000, 6000));
            events.ScheduleEvent(EVENT_SHADOW_STRIDE, urand(10000, 21000));
            events.ScheduleEvent(EVENT_SHADOW_FISSURE, urand(12500, 21000));
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (spell && spell->Id == SPELL_EARTHEN_ASCENSION)
            {
                DoAction(ACTION_SWITCH);
                me->m_Events.AddEvent(new summonMahatAndTherazane(me), me->m_Events.CalculateTime(6000));
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(2);
            if (Creature* torunscar = me->FindNearestCreature(NPC_ENTRY_TORUNSCAR, 85.0f, true))
            {
                torunscar->AI()->TalkWithDelay(3000, 1);
                torunscar->AI()->TalkWithDelay(5000, 2);
                torunscar->AI()->TalkWithDelay(12000, 3);
            }
            if (Creature* therazane = me->FindNearestCreature(NPC_ENTRY_THERAZANE, 200.0f, true))
                therazane->DespawnOrUnsummon(5000);
            if (Creature* mahaat = me->FindNearestCreature(NPC_ENTRY_MAHAAT, 200.0f, true))
                mahaat->DespawnOrUnsummon(5000);

            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(200.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr))
                {
                    if ((*itr)->GetTypeId() == TYPEID_PLAYER)
                    {
                        if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_BINDING) == QUEST_STATUS_INCOMPLETE)
                            (*itr)->ToPlayer()->CompleteQuest(QUEST_THE_BINDING);
                        if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_BINDING) == QUEST_STATUS_COMPLETE)
                        {
                            (*itr)->CastWithDelay(3000, (*itr), SPELL_CAMERA_FADE);
                            (*itr)->CastWithDelay(4000, (*itr), SPELL_FLYBY_CAMERA, true);
                        }
                    }
                }
            }
            me->m_Events.AddEvent(new eventMergeFragments(me), me->m_Events.CalculateTime(6500));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHADOW_BOLT:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(4000, 6500));
                        break;
                    }
                    case EVENT_SHADOW_STRIDE:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_SHADOW_STRIDE);
                        events.ScheduleEvent(EVENT_SHADOW_STRIDE, urand(25000, 35000));
                        break;
                    }
                    case EVENT_SHADOW_FISSURE:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCastVictim(SPELL_SHADOW_FISSURE);
                        events.ScheduleEvent(EVENT_SHADOW_FISSURE, urand(12500, 21000));
                        break;
                    }
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealthPct() > 50)
                        {
                            events.ScheduleEvent(EVENT_CHECK_HEALTH, 1000);
                            break;
                        }
                        me->SetReactState(REACT_PASSIVE);
                        events.CancelEvent(EVENT_CHECK_HEALTH);
                        events.CancelEvent(EVENT_SHADOW_BOLT);
                        events.CancelEvent(EVENT_SHADOW_STRIDE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_NON_ATTACKABLE);
                        DoStopAttack();
                        me->CastStop();
                        Talk(1);
                        me->CastWithDelay(2500, me, SPELL_EARTHEN_ASCENSION);
                        break;
                    }
                    case EVENT_SHADOW_BOLT_VOLLEY:
                    {
                        DoCast(SPELL_SHADOW_BOLT_VOLLEY);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, 6000);
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        }

    protected:
        Unit* unitSummoner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_high_priestess_lorthunaAI(creature);
    }
};

class npc_young_stone_drake : public CreatureScript
{
public:
    npc_young_stone_drake() : CreatureScript("npc_young_stone_drake") {}

    struct npc_young_stone_drakeAI : public ScriptedAI
    {
        npc_young_stone_drakeAI(Creature* creature) : ScriptedAI(creature) {unitToFollow = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_AEONAXX   = 50062
        };

        enum bossSpells
        {
            SPELL_FIREBALL              = 71928,
            SPELL_DAMAGE_REDUCTION      = 94658
        };

        enum eventId
        {
            EVENT_CAST_FIREBALL             = 1,
            EVENT_CHECK_AEONAXX_DISTANCE
        };

        enum actionId
        {
            ACTION_ATTACK_INVOKER = 1
        };

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetTypeId() == TYPEID_PLAYER)
            {
                me->AddAura(SPELL_DAMAGE_REDUCTION, me);
                me->setFaction(1802);
                if (Creature* aeonaxx = me->FindNearestCreature(NPC_ENTRY_AEONAXX, 1000.0f, true))
                {
                    me->GetMotionMaster()->MoveFollow(aeonaxx, 7.0f, aeonaxx->GetOrientation());
                    unitToFollow = aeonaxx;
                }

                // Immune to stun and silence
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);

                events.ScheduleEvent(EVENT_CAST_FIREBALL, 1000);
                events.ScheduleEvent(EVENT_CHECK_AEONAXX_DISTANCE, 1000);
            }
        }

        void Reset()
        {
            unitToFollow = NULL;
            me->SetReactState(REACT_PASSIVE);
            me->SetCanFly(true);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_FIREBALL:
                    {
                        RESCHEDULE_IF_CASTING
                        if (Player* aeonaxxRider = me->FindNearestPlayer(80.0f, true))
                        {
                            if (aeonaxxRider->GetVehicleBase() && aeonaxxRider->GetVehicleBase()->GetEntry() == NPC_ENTRY_AEONAXX)
                            {
                                DoCast(aeonaxxRider, SPELL_FIREBALL, true);
                                events.ScheduleEvent(EVENT_CAST_FIREBALL, 2000);
                                break;
                            }
                            else
                            {
                                events.ScheduleEvent(EVENT_CAST_FIREBALL, 1000);
                                break;
                            }
                        }
                        else
                            events.ScheduleEvent(EVENT_CAST_FIREBALL, 1000);
                        break;
                    }
                    case EVENT_CHECK_AEONAXX_DISTANCE:
                    {
                        if (unitToFollow == NULL)
                            return;

                        if (me->IsWithinCombatRange(unitToFollow, 0.8f))
                        {
                            me->SetSpeed(MOVE_RUN, unitToFollow->GetSpeed(MOVE_RUN) * 0.90f, true);
                            events.CancelEvent(EVENT_CHECK_AEONAXX_DISTANCE);
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_AEONAXX_DISTANCE, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        protected:
            Unit* unitToFollow;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_young_stone_drakeAI(creature);
    }
};

class npc_aeonaxx : public CreatureScript
{
public:
    npc_aeonaxx() : CreatureScript("npc_aeonaxx") {}

    enum npcSpells
    {
        SPELL_AEONAXX_WHELP_SUMMON  = 94652,
        SPELL_RIDE_AEONAXX          = 46598
    };

    enum actionEvent
    {
        ACTION_TALK_0   = 1,
        ACTION_START_WP
    };

    enum factionID
    {
        FACTION_AEONAXX_HOSTILE     = 1802,
        FACTION_AEONAXX_NEUTRAL     = 31
    };

    enum eventId
    {
        EVENT_SET_VISIBLE   = 1,
        EVENT_SET_INVISIBLE
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->CastSpell(creature, SPELL_RIDE_AEONAXX, true);
        return true;
    }

    struct npc_aeonaxxAI : public npc_escortAI
    {
        npc_aeonaxxAI(Creature* creature) : npc_escortAI(creature)
        {
            unitPassenger = NULL;
            hasPassenger = false;
        }

        EventMap events;

        void Reset()
        {
            // Immune to stun and silence
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_SET_VISIBLE, urand(120000, 300000));
            events.ScheduleEvent(EVENT_SET_INVISIBLE, urand(120000, 300000));
            me->GetMotionMaster()->MoveRandom(20.0f);
            hasPassenger = false;
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (apply)
            {
                me->StopMoving();
                me->SetReactState(REACT_PASSIVE);
                hasPassenger = true;
                passenger->AddAura(SPELL_AEONAXX_WHELP_SUMMON, passenger);
                me->setFaction(FACTION_AEONAXX_HOSTILE);
                Talk(0, passenger->GetGUID());
                unitPassenger = passenger;
                me->SetSpeed(MOVE_RUN, 5.0f, true);
                DoAction(ACTION_START_WP);
                events.CancelEvent(EVENT_SET_VISIBLE);
                events.CancelEvent(EVENT_SET_INVISIBLE);
            }
        }

        void PassengerRemoved(Unit* /*passenger*/, bool /*apply*/)
        {
            me->setFaction(FACTION_AEONAXX_NEUTRAL);
            me->SetSpeed(MOVE_RUN, 2.4f, true);
            me->DespawnOrUnsummon(120000);
            unitPassenger = NULL;
            hasPassenger = false;
        }

        void JustDied(Unit* /*killer*/)
        {
            unitPassenger = NULL;
            hasPassenger = false;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetNextWaypoint(1, true);
                    Start(false, true, NULL, NULL, false, true, false);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 /*waypointId*/) { }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            // Start eventmap only if Aeonaxx is free
            if (hasPassenger == true || !me->isAlive())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SET_INVISIBLE:
                    {
                        me->SetVisible(false);
                        events.ScheduleEvent(EVENT_SET_VISIBLE, urand(120000, 300000));
                        break;
                    }
                    case EVENT_SET_VISIBLE:
                    {
                        me->SetVisible(true);
                        events.ScheduleEvent(EVENT_SET_INVISIBLE, urand(120000, 300000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* unitPassenger;
        float x, y, z, o;
        bool hasPassenger;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aeonaxxAI(creature);
    }
};

class npc_colossal_gyreworm : public CreatureScript
{
public:
    npc_colossal_gyreworm() : CreatureScript("npc_colossal_gyreworm") {}

    enum eventId
    {
        EVENT_CHECK_PLAYER  = 1,
        EVENT_SWITCH_SEAT
    };

    enum actionId
    {
        ACTION_SWITCH_PASSENGER     = 1
    };

    enum spellId
    {
        SPELL_CONSUMPTION           = 95169,
        SPELL_CONSUMPTION_REMOVE    = 95170,
        SPELL_RIDE_SEAT_1           = 46598,
        SPELL_RIDE_SEAT_2           = 63313,
        SPELL_RIDE_SEAT_3           = 63314,
        SPELL_RIDE_SEAT_4           = 63315,
        SPELL_RIDE_SEAT_5           = 63316,
        SPELL_RIDE_SEAT_6           = 63344,
        SPELL_RIDE_SEAT_7           = 63345
    };

    struct npc_colossal_gyrewormAI : public npc_escortAI
    {
        npc_colossal_gyrewormAI(Creature* creature) : npc_escortAI(creature)
        {
            passengerSec = NULL;
        }

        EventMap events;

        void CheckPassengerSeat()
        {
            if (passengerSec != NULL)
            {
                if (!me->HasAura(SPELL_RIDE_SEAT_1))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_1, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_1))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                if (!me->HasAura(SPELL_RIDE_SEAT_2))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_2, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_2))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                if (!me->HasAura(SPELL_RIDE_SEAT_3))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_3, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_3))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                if (!me->HasAura(SPELL_RIDE_SEAT_4))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_4, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_4))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                if (!me->HasAura(SPELL_RIDE_SEAT_5))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_5, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_5))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                if (!me->HasAura(SPELL_RIDE_SEAT_6))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_6, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_6))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                if (!me->HasAura(SPELL_RIDE_SEAT_7))
                {
                    passengerSec->CastSpell(me, SPELL_RIDE_SEAT_7, true);
                    if (!passengerSec->HasAura(SPELL_CONSUMPTION))
                        me->CastSpell(passengerSec, SPELL_CONSUMPTION, passengerSec);
                    if (Aura* rideAura = me->GetAura(SPELL_RIDE_SEAT_7))
                        rideAura->SetDuration(10000);
                    passengerSec = NULL;
                    return;
                }
                return;
            }
        }

        void Reset()
        {
            // Immune to stun and silence
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);
            me->SetReactState(REACT_PASSIVE);
            Start(false, true, NULL, NULL, false, true);
            events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
        }

        void WaypointReached(uint32 /*waypointId*/) { }

        void UpdateAI(uint32 diff)
        {
            if (!me->isAlive())
                return;

            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PLAYER:
                    {
                        if (Player* target = me->FindNearestPlayer(8.5f, true))
                        {
                            // Exclude players already in vehicle and GameMasters
                            if (target->GetVehicleBase() || target->ToPlayer()->isGameMaster()
                                || target->HasAura(SPELL_CONSUMPTION))
                            {
                                events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                                break;
                            }
                            passengerSec = target;
                            CheckPassengerSeat();
                        }
                        events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* passengerSec;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_colossal_gyrewormAI(creature);
    }
};

class npc_warlock_doomguard : public CreatureScript
{
public:
    npc_warlock_doomguard() : CreatureScript("npc_warlock_doomguard") {}

    struct npc_warlock_doomguardAI : public ScriptedAI
    {
        npc_warlock_doomguardAI(Creature* creature) : ScriptedAI(creature) {targetVictim = NULL;}

        EventMap events;

        enum npcSpells
        {
            SPELL_DOOM_BOLT         = 85692,
            SPELL_BANE_OF_DOOM      = 603,
            SPELL_BANE_OF_AGONY     = 980
        };

        enum eventId
        {
            EVENT_CHECK_TARGET_DEBUFF   = 1,
            EVENT_CAST_DOOM_BOLT
        };

        void IsSummonedBy(Unit* summoner)
        {
            events.ScheduleEvent(EVENT_CHECK_TARGET_DEBUFF, 1000);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_TARGET_DEBUFF:
                    {
                        if (!me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            if (Unit* owner = me->GetCharmerOrOwner())
                            {
                                if (Unit* target = owner->getAttackerForHelper())
                                {
                                    if (target->HasAura(SPELL_BANE_OF_AGONY, owner->GetGUID()) || target->HasAura(SPELL_BANE_OF_DOOM, owner->GetGUID()))
                                    {
                                        targetVictim = target;
                                        events.ScheduleEvent(EVENT_CAST_DOOM_BOLT, 1);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_CHECK_TARGET_DEBUFF, 1000);
                        break;
                    }
                    case EVENT_CAST_DOOM_BOLT:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (targetVictim && targetVictim != NULL)
                        {
                            if (Unit* owner = me->GetCharmerOrOwner())
                            {
                                if (!targetVictim->HasAura(SPELL_BANE_OF_AGONY, owner->GetGUID()) && !targetVictim->HasAura(SPELL_BANE_OF_DOOM, owner->GetGUID()))
                                {
                                    targetVictim = NULL;
                                    if (me->isInCombat())
                                    {
                                        DoStopAttack();
                                        EnterEvadeMode();
                                    }
                                }
                                else
                                    DoCast(targetVictim, SPELL_DOOM_BOLT);
                            }
                        }
                        events.ScheduleEvent(EVENT_CAST_DOOM_BOLT, 3500);
                        events.ScheduleEvent(EVENT_CHECK_TARGET_DEBUFF, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        Unit* targetVictim;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_warlock_doomguardAI(creature);
    }
};

class npc_warlock_infernal : public CreatureScript
{
public:
    npc_warlock_infernal() : CreatureScript("npc_warlock_infernal")
    {
    }

    enum spellId
    {
        SPELL_DEMONIC_IMMOLATION_PASSIVE    = 4525,
        SPELL_BANE_OF_DOOM                  = 603,
        SPELL_BANE_OF_AGONY                 = 980,
        SPELL_BANE_OF_HAVOC                 = 80240
    };

    struct npc_warlock_infernalAI : PetAI
    {
        npc_warlock_infernalAI(Creature* creature) : PetAI(creature)
        {
        }

        uint32 checkTimer;

        void InitializeAI()
        {
            me->SetPower(POWER_ENERGY, me->GetMaxPower(POWER_ENERGY));
            me->CastSpell(me, SPELL_DEMONIC_IMMOLATION_PASSIVE, true);
            checkTimer = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Unit* owner = me->GetOwner())
                {
                    Player* player = owner->ToPlayer();
                    if (!player)
                        return;

                    Unit* ownerVictim = isBaned(player->GetSelectedUnit()) ? player->GetSelectedUnit() : NULL;
                    Unit* meVictim = isBaned(me->getVictim()) ? me->getVictim() : NULL;
                    Unit* infernalTarget = ownerVictim ? ownerVictim : meVictim ? meVictim : NULL;

                    if (infernalTarget)
                    {
                        me->Attack(infernalTarget, true);
                        me->GetMotionMaster()->MoveChase(infernalTarget);
                        DoMeleeAttackIfReady();
                    }
                    else
                        dummyGuard();
                }
            }
        }

        bool isBaned(Unit* victim)
        {
            if (Unit* owner = me->GetOwner())
                return victim && (victim->HasAura(SPELL_BANE_OF_DOOM, owner->GetGUID()) || victim->HasAura(SPELL_BANE_OF_AGONY, owner->GetGUID()));
            return false;
        }

        void dummyGuard()
        {
            if (Unit* owner = me->GetOwner())
            {
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST * 2, me->GetFollowAngle());
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_warlock_infernalAI(creature);
    }
};

class npc_force_of_nature : public CreatureScript
{
public:
    npc_force_of_nature() : CreatureScript("npc_force_of_nature") { }

    struct npc_force_of_natureAI : PetAI
    {
        npc_force_of_natureAI(Creature* creature) : PetAI(creature) {}

        void InitializeAI() {}

        void JustDied(Unit* /*killer*/)
        {
            Unit* owner = me->GetOwner();
            if (!owner)
                return;

            // Fungal Growth
            if (AuraEffect* aurEff = owner->GetDummyAuraEffect(SPELLFAMILY_DRUID, 2681, EFFECT_0))
            {
                Position pos;
                me->GetPosition(&pos);

                if (owner->HasAura(78788))  // Fungal Growth Rank 1
                    owner->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 81291, false);
                else if (owner->HasAura(78789)) // Fungal Growth Rank 2
                    owner->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 81283, false);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_force_of_natureAI(creature);
    }
};

class npc_blam_turret : public CreatureScript
{
public:
    npc_blam_turret() : CreatureScript("npc_blam_turret") {}

    struct npc_blam_turretAI : public ScriptedAI
    {
        npc_blam_turretAI(Creature* creature) : ScriptedAI(creature) {eventStarted = false;}

        EventMap events;

        enum npcSpells
        {
            SPELL_SUMMON_WAVE_1     = 87029,
            SPELL_SUMMON_WAVE_2     = 87031
        };

        enum eventId
        {
            EVENT_CHECK_PASSENGER   = 1,
            EVENT_SUMMON_FIRST_WAVE,
            EVENT_SUMMON_SECOND_WAVE,
            EVENT_SUMMON_THIRD_WAVE,
            EVENT_SUMMON_FINAL_WAVE,
            EVENT_STOP_WAVES
        };

        enum creditId
        {
            CREDIT_WAVE_1   = 87073,
            CREDIT_WAVE_2   = 87074,
            CREDIT_WAVE_3   = 87075,
            CREDIT_WAVE_4   = 87076
        };

        void OnCharmed(bool apply) {}

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (apply)
            {
                eventStarted = true;
                events.ScheduleEvent(EVENT_CHECK_PASSENGER, 2000);
                if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    TalkWithDelay(500, 0, passenger->GetGUID());
            }
            else
            {
                eventStarted = false;
                events.Reset();
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PASSENGER:
                    {
                        if (!me->GetVehicleKit()->GetPassenger(0))
                        {
                            events.Reset();
                            break;
                        }
                        else
                        {
                            events.RescheduleEvent(EVENT_CHECK_PASSENGER, 2000);
                            events.ScheduleEvent(EVENT_SUMMON_FIRST_WAVE, 2000);
                        }
                        break;
                    }
                    case EVENT_SUMMON_FIRST_WAVE:
                    {
                        events.CancelEvent(EVENT_SUMMON_FIRST_WAVE);
                        events.ScheduleEvent(EVENT_SUMMON_SECOND_WAVE, 10000);
                        DoCast(me, SPELL_SUMMON_WAVE_1, true);
                        break;
                    }
                    case EVENT_SUMMON_SECOND_WAVE:
                    {
                        events.CancelEvent(EVENT_SUMMON_SECOND_WAVE);
                        events.ScheduleEvent(EVENT_SUMMON_THIRD_WAVE, 10000);
                        DoCast(me, CREDIT_WAVE_1, true);
                        DoCast(me, SPELL_SUMMON_WAVE_2, true);
                        break;
                    }
                    case EVENT_SUMMON_THIRD_WAVE:
                    {
                        events.CancelEvent(EVENT_SUMMON_THIRD_WAVE);
                        events.ScheduleEvent(EVENT_SUMMON_FINAL_WAVE, 10000);
                        DoCast(me, CREDIT_WAVE_2, true);
                        DoCast(me, SPELL_SUMMON_WAVE_1, true);
                        break;
                    }
                    case EVENT_SUMMON_FINAL_WAVE:
                    {
                        events.CancelEvent(EVENT_SUMMON_FINAL_WAVE);
                        events.ScheduleEvent(EVENT_STOP_WAVES, 20000);
                        DoCast(me, CREDIT_WAVE_3, true);
                        DoCast(me, SPELL_SUMMON_WAVE_1, true);
                        DoCast(me, SPELL_SUMMON_WAVE_2, true);
                        break;
                    }
                    case EVENT_STOP_WAVES:
                    {
                        DoCast(me, CREDIT_WAVE_4, true);
                        events.Reset();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool eventStarted;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blam_turretAI(creature);
    }
};

class npc_generic_trigger_lab : public CreatureScript
{
public:
    npc_generic_trigger_lab() : CreatureScript("npc_generic_trigger_lab")
    {
    }

    struct npc_generic_trigger_labAI : public ScriptedAI
    {
        npc_generic_trigger_labAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum questId
        {
            QUEST_TSC_FOLLOWERS_AND_LEADERS     = 28814,
            QUEST_TSC_TWILIGHT_DOCUMENTS        = 28815
        };

        enum eventId
        {
            EVENT_TSC_CHECK_QUEST = 1
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_TSC_CHECK_QUEST, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // The Stonecore
                    case EVENT_TSC_CHECK_QUEST:
                    {
                        Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                        if (!PlayerList.isEmpty())
                        {
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            {
                                if (Quest const* followers = sObjectMgr->GetQuestTemplate(QUEST_TSC_FOLLOWERS_AND_LEADERS))
                                {
                                    if (i->getSource()->CanTakeQuest(followers, false))
                                    {
                                        i->getSource()->AddQuestAndCheckCompletion(followers, i->getSource());
                                        i->getSource()->PlayerTalkClass->SendQuestGiverQuestDetails(followers, i->getSource()->GetGUID(), true);
                                    }
                                }
                            }
                        }
                        if (me->GetMapId() == 725)
                            events.RescheduleEvent(EVENT_TSC_CHECK_QUEST, 3500);
                        else
                            events.CancelEvent(EVENT_TSC_CHECK_QUEST);
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
        return new npc_generic_trigger_labAI(creature);
    }
};

class npc_muddy_tracks : public CreatureScript
{
public:
    npc_muddy_tracks() : CreatureScript("npc_muddy_tracks")
    {
    }

    enum Id
    {
        QUEST_SLUDGE_INVESTIGATION      = 29087,
        CREDIT_SLUDGE_INVESTIGATION     = 52166
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_SLUDGE_INVESTIGATION) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(CREDIT_SLUDGE_INVESTIGATION);
            creature->AI()->Talk(0, player->GetGUID());
            creature->DespawnOrUnsummon(1);
        }
        return true;
    }
};

class npc_flameward_activated : public CreatureScript
{
public:
    npc_flameward_activated() : CreatureScript("npc_flameward_activated")
    {
    }

    struct npc_flameward_activatedAI : public ScriptedAI
    {
        npc_flameward_activatedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_FLAMEWARD_SHIELD  = 75454
        };

        enum eventId
        {
            EVENT_SUMMON_ASHBEARERS     = 1,
            EVENT_STOP_SUMMON
        };

        enum npcId
        {
            NPC_ASHBEARER   = 46925
        };

        void Reset()
        {
            if (!me->HasAura(SPELL_FLAMEWARD_SHIELD))
                DoCast(me, SPELL_FLAMEWARD_SHIELD);
            events.ScheduleEvent(EVENT_SUMMON_ASHBEARERS, 8000);
            events.ScheduleEvent(EVENT_STOP_SUMMON, 60000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_ASHBEARERS:
                    {
                        me->SummonCreature(NPC_ASHBEARER, me->GetPositionX() + urand(8, 15), me->GetPositionY() + urand(8, 15), me->GetPositionZ()+1, me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000);
                        events.RescheduleEvent(EVENT_SUMMON_ASHBEARERS, 10000);
                        break;
                    }
                    case EVENT_STOP_SUMMON:
                    {
                        Talk(0);
                        events.CancelEvent(EVENT_SUMMON_ASHBEARERS);
                        events.CancelEvent(EVENT_STOP_SUMMON);
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
        return new npc_flameward_activatedAI(creature);
    }
};

void AddSC_npcs_special()
{
    new npc_air_force_bots();
    new npc_lunaclaw_spirit();
    new npc_chicken_cluck();
    new npc_dancing_flames();
    new npc_doctor();
    new npc_injured_patient();
    new npc_garments_of_quests();
    new npc_guardian();
    new npc_mount_vendor();
    new npc_rogue_trainer();
    new npc_sayge();
    new npc_steam_tonk();
    new npc_tonk_mine();
    new npc_brewfest_reveler();
    new npc_snake_trap();
    new npc_mirror_image();
    new npc_ebon_gargoyle();
    new npc_lightwell();
    new mob_mojo();
    new npc_training_dummy();
    new npc_shadowfiend();
    new npc_wormhole();
    new npc_pet_trainer();
    new npc_locksmith();
    new npc_experience();
    new npc_fire_elemental();
    new npc_earth_elemental();
    new npc_firework();
    new npc_spring_rabbit();
    new npc_generic_harpoon_cannon();
    new npc_shadowy_apparition();
    new npc_ring_of_frost();
    new npc_flame_orb();
    new npc_frostfire_orb();
    new npc_fungal_growth();
    new npc_hand_of_gul_dan();
    new npc_grounding_totem();
    new npc_eye_of_kilrogg();
    new npc_tentacle_of_the_old();
    new npc_generic_areatrigger();
    new npc_blight_slime();
    new npc_danforth();
    new npc_danforth_invisible_dummy();
    new npc_colonel_troteman();
    new npc_wild_rat();
    new npc_john_j_keeshan();
    new npc_horn_of_summoning();
    new npc_abandoned_bloodwash_trigger();
    new npc_sentinel_start();
    new npc_amakkar();
    new npc_gargal();
    new npc_jurrix();
    new npc_eric();
    new npc_baelog();
    new npc_olaf();
    new npc_wildhammer_lookout();
    new npc_deathstalker_lookout();
    new npc_hearthglen_mustang();
    new npc_shadow_prison();
    new npc_enthralled_valkyr();
    new npc_summoned_ebon_gargoyle();
    new npc_enthralled_valkyr_final();
    new npc_heartrazor();
    new npc_twilight_subduer();
    new npc_heartrazor_wp();
    new npc_heartrazor_wp_return();
    new npc_generic_dave_trigger();
    new npc_aviana_guardian();
    new npc_climbing_tree_start();
    new npc_orb_of_ascension();
    new npc_war_guardian_summoner();
    new npc_falling_boulder();
    new npc_mercurial_ooze();
    new npc_azil_fragment_event();
    new npc_millhouse_fragment_event();
    new npc_stonescale_matriarch();
    new npc_abyssion_event();
    new npc_felsen_the_enduring();
    new npc_haethen_kaul();
    new npc_terrath();
    new npc_opalescent_guardian();
    new npc_stone_drake();
    new npc_norsala_escort();
    new npc_glop_escort();
    new npc_boomshroom();
    new npc_boulder_platform();
    new npc_aeosera_event();
    new npc_zoltrik_drakebane();
    new npc_invisible_trigger_one();
    new npc_earthcaller_torunscar();
    new npc_high_priestess_lorthuna();
    new npc_young_stone_drake();
    new npc_aeonaxx();
    new npc_colossal_gyreworm();
    new npc_warlock_doomguard();
    new npc_warlock_infernal();
    new npc_force_of_nature();
    new npc_blam_turret();
    new npc_generic_trigger_lab();
    new npc_muddy_tracks();
    new npc_flameward_activated();
}
