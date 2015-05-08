/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuras.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

enum Orphans
{
    ORPHAN_ORACLE                           = 33533,
    ORPHAN_WOLVAR                           = 33532,
    ORPHAN_BLOOD_ELF                        = 22817,
    ORPHAN_DRAENEI                          = 22818,
    ORPHAN_HUMAN                            = 14305,
    ORPHAN_ORCISH                           = 14444,
};

enum Texts
{
    TEXT_ORACLE_ORPHAN_1                    = 1,
    TEXT_ORACLE_ORPHAN_2                    = 2,
    TEXT_ORACLE_ORPHAN_3                    = 3,
    TEXT_ORACLE_ORPHAN_4                    = 4,
    TEXT_ORACLE_ORPHAN_5                    = 5,
    TEXT_ORACLE_ORPHAN_6                    = 6,
    TEXT_ORACLE_ORPHAN_7                    = 7,
    TEXT_ORACLE_ORPHAN_8                    = 8,
    TEXT_ORACLE_ORPHAN_9                    = 9,
    TEXT_ORACLE_ORPHAN_10                   = 10,
    TEXT_ORACLE_ORPHAN_11                   = 11,
    TEXT_ORACLE_ORPHAN_12                   = 12,
    TEXT_ORACLE_ORPHAN_13                   = 13,
    TEXT_ORACLE_ORPHAN_14                   = 14,

    TEXT_WOLVAR_ORPHAN_1                    = 1,
    TEXT_WOLVAR_ORPHAN_2                    = 2,
    TEXT_WOLVAR_ORPHAN_3                    = 3,
    TEXT_WOLVAR_ORPHAN_4                    = 4,
    TEXT_WOLVAR_ORPHAN_5                    = 5,
    // 6 - 9 used in Nesingwary script
    TEXT_WOLVAR_ORPHAN_10                   = 10,
    TEXT_WOLVAR_ORPHAN_11                   = 11,
    TEXT_WOLVAR_ORPHAN_12                   = 12,
    TEXT_WOLVAR_ORPHAN_13                   = 13,

    TEXT_WINTERFIN_PLAYMATE_1               = 1,
    TEXT_WINTERFIN_PLAYMATE_2               = 2,

    TEXT_SNOWFALL_GLADE_PLAYMATE_1          = 1,
    TEXT_SNOWFALL_GLADE_PLAYMATE_2          = 2,

    TEXT_SOO_ROO_1                          = 1,
    TEXT_ELDER_KEKEK_1                      = 1,

    TEXT_ALEXSTRASZA_2                      = 2,
    TEXT_KRASUS_8                           = 8,
};

enum Quests
{
    QUEST_PLAYMATE_WOLVAR                   = 13951,
    QUEST_PLAYMATE_ORACLE                   = 13950,
    QUEST_THE_BIGGEST_TREE_EVER             = 13929,
    QUEST_THE_BRONZE_DRAGONSHRINE_ORACLE    = 13933,
    QUEST_THE_BRONZE_DRAGONSHRINE_WOLVAR    = 13934,
    QUEST_MEETING_A_GREAT_ONE               = 13956,
    QUEST_THE_MIGHTY_HEMET_NESINGWARY       = 13957,
    QUEST_DOWN_AT_THE_DOCKS                 = 910,
    QUEST_GATEWAY_TO_THE_FRONTIER           = 911,
    QUEST_BOUGHT_OF_ETERNALS                = 1479,
    QUEST_SPOOKY_LIGHTHOUSE                 = 1687,
    QUEST_STONEWROUGHT_DAM                  = 1558,
    QUEST_DARK_PORTAL_H                     = 10951,
    QUEST_DARK_PORTAL_A                     = 10952,
    QUEST_LORDAERON_THRONE_ROOM             = 1800,
    QUEST_AUCHINDOUN_AND_THE_RING           = 10950,
    QUEST_TIME_TO_VISIT_THE_CAVERNS_H       = 10963,
    QUEST_TIME_TO_VISIT_THE_CAVERNS_A       = 10962,
    QUEST_THE_SEAT_OF_THE_NARUU             = 10956,
    QUEST_CALL_ON_THE_FARSEER               = 10968,
    QUEST_JHEEL_IS_AT_AERIS_LANDING         = 10954,
    QUEST_HCHUU_AND_THE_MUSHROOM_PEOPLE     = 10945,
    QUEST_VISIT_THE_THRONE_OF_ELEMENTS      = 10953,
    QUEST_NOW_WHEN_I_GROW_UP                = 11975,
    QUEST_HOME_OF_THE_BEAR_MEN              = 13930,
    QUEST_THE_DRAGON_QUEEN_ORACLE           = 13954,
    QUEST_THE_DRAGON_QUEEN_WOLVAR           = 13955,
};

enum Areatriggers
{
    AT_DOWN_AT_THE_DOCKS                    = 3551,
    AT_GATEWAY_TO_THE_FRONTIER              = 3549,
    AT_LORDAERON_THRONE_ROOM                = 3547,
    AT_BOUGHT_OF_ETERNALS                   = 3546,
    AT_SPOOKY_LIGHTHOUSE                    = 3552,
    AT_STONEWROUGHT_DAM                     = 3548,
    AT_DARK_PORTAL                          = 4356,

    NPC_CAVERNS_OF_TIME_CW_TRIGGER          = 22872,
    NPC_EXODAR_01_CW_TRIGGER                = 22851,
    NPC_EXODAR_02_CW_TRIGGER                = 22905,
    NPC_AERIS_LANDING_CW_TRIGGER            = 22838,
    NPC_AUCHINDOUN_CW_TRIGGER               = 22831,
    NPC_SPOREGGAR_CW_TRIGGER                = 22829,
    NPC_THRONE_OF_ELEMENTS_CW_TRIGGER       = 22839,
    NPC_SILVERMOON_01_CW_TRIGGER            = 22866,
    NPC_KRASUS                              = 27990,
};

enum Misc
{
    SPELL_SNOWBALL                          = 21343,
    SPELL_ORPHAN_OUT                        = 58818,

    DISPLAY_INVISIBLE                       = 11686,
};

uint64 getOrphanGUID(Player* player, uint32 orphan)
{
    if (Aura* orphanOut = player->GetAura(SPELL_ORPHAN_OUT))
        if (orphanOut->GetCaster() && orphanOut->GetCaster()->GetEntry() == orphan)
            return orphanOut->GetCaster()->GetGUID();

    return 0;
}

/*######
## npc_winterfin_playmate
######*/
class npc_winterfin_playmate : public CreatureScript
{
    public:
        npc_winterfin_playmate() : CreatureScript("npc_winterfin_playmate") {}

        struct npc_winterfin_playmateAI : public ScriptedAI
        {
            npc_winterfin_playmateAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset()
            {
                timer = 0;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_PLAYMATE_ORACLE) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_ORACLE);
                            if (orphanGUID)
                                phase = 1;
                        }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!orphan || !player)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_1);
                            timer = 3000;
                            break;
                        case 2:
                            orphan->SetFacingToObject(me);
                            Talk(TEXT_WINTERFIN_PLAYMATE_1);
                            me->HandleEmoteCommand(EMOTE_STATE_DANCE);
                            timer = 3000;
                            break;
                        case 3:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_2);
                            timer = 3000;
                            break;
                        case 4:
                            Talk(TEXT_WINTERFIN_PLAYMATE_2);
                            timer = 5000;
                            break;
                        case 5:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_3);
                            me->HandleEmoteCommand(EMOTE_STATE_NONE);
                            player->GroupEventHappens(QUEST_PLAYMATE_ORACLE, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

        private:
            uint32 timer;
            int8 phase;
            uint64 playerGUID;
            uint64 orphanGUID;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_winterfin_playmateAI(creature);
        }
};

/*######
## npc_snowfall_glade_playmate
######*/
class npc_snowfall_glade_playmate : public CreatureScript
{
    public:
        npc_snowfall_glade_playmate() : CreatureScript("npc_snowfall_glade_playmate") {}

        struct npc_snowfall_glade_playmateAI : public ScriptedAI
        {
            npc_snowfall_glade_playmateAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset()
            {
                timer = 0;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_PLAYMATE_WOLVAR) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_WOLVAR);
                            if (orphanGUID)
                                phase = 1;
                        }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!orphan || !player)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_1);
                            timer = 5000;
                            break;
                        case 2:
                            orphan->SetFacingToObject(me);
                            Talk(TEXT_SNOWFALL_GLADE_PLAYMATE_1);
                            DoCast(orphan, SPELL_SNOWBALL);
                            timer = 5000;
                            break;
                        case 3:
                            Talk(TEXT_SNOWFALL_GLADE_PLAYMATE_2);
                            timer = 5000;
                            break;
                        case 4:
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_2);
                            orphan->AI()->DoCast(me, SPELL_SNOWBALL);
                            timer = 5000;
                            break;
                        case 5:
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_3);
                            player->GroupEventHappens(QUEST_PLAYMATE_WOLVAR, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

        private:
            uint32 timer;
            int8 phase;
            uint64 playerGUID;
            uint64 orphanGUID;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_snowfall_glade_playmateAI(pCreature);
        }
};

/*######
## npc_the_biggest_tree
######*/
class npc_the_biggest_tree : public CreatureScript
{
    public:
        npc_the_biggest_tree() : CreatureScript("npc_the_biggest_tree") {}

        struct npc_the_biggest_treeAI : public ScriptedAI
        {
            npc_the_biggest_treeAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetDisplayId(DISPLAY_INVISIBLE);
            }

            void Reset()
            {
                timer = 1000;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_THE_BIGGEST_TREE_EVER) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_ORACLE);
                            if (orphanGUID)
                                phase = 1;
                        }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!orphan || !player)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            timer = 2000;
                            break;
                        case 2:
                            orphan->SetFacingToObject(me);
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_4);
                            timer = 5000;
                            break;
                        case 3:
                            player->GroupEventHappens(QUEST_THE_BIGGEST_TREE_EVER, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

        private:
            uint32 timer;
            uint8 phase;
            uint64 playerGUID;
            uint64 orphanGUID;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_the_biggest_treeAI(creature);
        }
};

/*######
## npc_high_oracle_soo_roo
######*/
class npc_high_oracle_soo_roo : public CreatureScript
{
    public:
        npc_high_oracle_soo_roo() : CreatureScript("npc_high_oracle_soo_roo") {}

        struct npc_high_oracle_soo_rooAI : public ScriptedAI
        {
            npc_high_oracle_soo_rooAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset()
            {
                timer = 0;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_THE_BRONZE_DRAGONSHRINE_ORACLE) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_ORACLE);
                            if (orphanGUID)
                                phase = 1;
                        }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!orphan || !player)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_5);
                            timer = 3000;
                            break;
                        case 2:
                            orphan->SetFacingToObject(me);
                            Talk(TEXT_SOO_ROO_1);
                            timer = 6000;
                            break;
                        case 3:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_6);
                            player->GroupEventHappens(QUEST_THE_BRONZE_DRAGONSHRINE_ORACLE, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

        private:
            uint32 timer;
            int8 phase;
            uint64 playerGUID;
            uint64 orphanGUID;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_high_oracle_soo_rooAI(creature);
        }
};

/*######
## npc_elder_kekek
######*/
class npc_elder_kekek : public CreatureScript
{
    public:
        npc_elder_kekek() : CreatureScript("npc_elder_kekek") {}

        struct npc_elder_kekekAI : public ScriptedAI
        {
            npc_elder_kekekAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset()
            {
                timer = 0;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_THE_BRONZE_DRAGONSHRINE_WOLVAR) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_WOLVAR);
                            if (orphanGUID)
                                phase = 1;
                        }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!player || !orphan)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_4);
                            timer = 3000;
                            break;
                        case 2:
                            Talk(TEXT_ELDER_KEKEK_1);
                            timer = 6000;
                            break;
                        case 3:
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_5);
                            player->GroupEventHappens(QUEST_THE_BRONZE_DRAGONSHRINE_WOLVAR, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

        private:
            uint32 timer;
            int8 phase;
            uint64 playerGUID;
            uint64 orphanGUID;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_elder_kekekAI(creature);
        }
};

/*######
## npc_the_etymidian
## TODO: A red crystal as a gift for the great one should be spawned during the event.
######*/
class npc_the_etymidian : public CreatureScript
{
    public:
        npc_the_etymidian() : CreatureScript("npc_the_etymidian") {}

        struct npc_the_etymidianAI : public ScriptedAI
        {
            npc_the_etymidianAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset()
            {
                timer = 0;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_MEETING_A_GREAT_ONE) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_ORACLE);
                            if (orphanGUID)
                                phase = 1;
                        }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!orphan || !player)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_7);
                            timer = 5000;
                            break;
                        case 2:
                            orphan->SetFacingToObject(me);
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_8);
                            timer = 5000;
                            break;
                        case 3:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_9);
                            timer = 5000;
                            break;
                        case 4:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_10);
                            timer = 5000;
                            break;
                        case 5:
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            player->GroupEventHappens(QUEST_MEETING_A_GREAT_ONE, me);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

        private:
            uint32 timer;
            int8 phase;
            uint32 GOtimer;
            uint64 playerGUID;
            uint64 orphanGUID;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_the_etymidianAI(creature);
        }
};

/*######
## npc_cw_alexstrasza_trigger
######*/
class npc_alexstraza_the_lifebinder : public CreatureScript
{
    public:
        npc_alexstraza_the_lifebinder() : CreatureScript("npc_alexstraza_the_lifebinder") {}

        struct npc_alexstraza_the_lifebinderAI : public ScriptedAI
        {
            npc_alexstraza_the_lifebinderAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset()
            {
                timer = 0;
                phase = 0;
                playerGUID = 0;
                orphanGUID = 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                // Existing SmartAI
                if (type == 0)
                {
                    switch (data)
                    {
                        case 1:
                            me->SetOrientation(1.6049f);
                            break;
                        case 2:
                            me->SetOrientation(me->GetHomePosition().GetOrientation());
                            break;
                    }
                }
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!phase && who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                    {
                        if (player->GetQuestStatus(QUEST_THE_DRAGON_QUEEN_ORACLE) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_ORACLE);
                            if (orphanGUID)
                                phase = 1;
                        }
                        else if (player->GetQuestStatus(QUEST_THE_DRAGON_QUEEN_WOLVAR) == QUEST_STATUS_INCOMPLETE)
                        {
                            playerGUID = player->GetGUID();
                            orphanGUID = getOrphanGUID(player, ORPHAN_WOLVAR);
                            if (orphanGUID)
                                phase = 7;
                        }
                    }
            }

            void UpdateAI(uint32 diff)
            {
                if (!phase)
                    return;

                if (timer <= diff)
                {
                    Player* player = Player::GetPlayer(*me, playerGUID);
                    Creature* orphan = Creature::GetCreature(*me, orphanGUID);

                    if (!orphan || !player)
                    {
                        Reset();
                        return;
                    }

                    switch (phase)
                    {
                        case 1:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_11);
                            timer = 5000;
                            break;
                        case 2:
                            orphan->SetFacingToObject(me);
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_12);
                            timer = 5000;
                            break;
                        case 3:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_13);
                            timer = 5000;
                            break;
                        case 4:
                            Talk(TEXT_ALEXSTRASZA_2);
                            me->SetStandState(UNIT_STAND_STATE_KNEEL);
                            me->SetFacingToObject(orphan);
                            timer = 5000;
                            break;
                        case 5:
                            orphan->AI()->Talk(TEXT_ORACLE_ORPHAN_14);
                            timer = 5000;
                            break;
                        case 6:
                            me->SetStandState(UNIT_STAND_STATE_STAND);
                            me->SetOrientation(me->GetHomePosition().GetOrientation());
                            player->GroupEventHappens(QUEST_THE_DRAGON_QUEEN_ORACLE, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                        case 7:
                            orphan->GetMotionMaster()->MovePoint(0, me->GetPositionX() + cos(me->GetOrientation()) * 5, me->GetPositionY() + sin(me->GetOrientation()) * 5, me->GetPositionZ());
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_11);
                            timer = 5000;
                            break;
                        case 8:
                            if (Creature* krasus = me->FindNearestCreature(NPC_KRASUS, 10.0f))
                            {
                                orphan->SetFacingToObject(krasus);
                                krasus->AI()->Talk(TEXT_KRASUS_8);
                            }
                            timer = 5000;
                            break;
                        case 9:
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_12);
                            timer = 5000;
                            break;
                        case 10:
                            orphan->SetFacingToObject(me);
                            Talk(TEXT_ALEXSTRASZA_2);
                            timer = 5000;
                            break;
                        case 11:
                            orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_13);
                            timer = 5000;
                            break;
                        case 12:
                            player->GroupEventHappens(QUEST_THE_DRAGON_QUEEN_WOLVAR, me);
                            orphan->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                            Reset();
                            return;
                    }
                    ++phase;
                }
                else
                    timer -= diff;
            }

            private:
                int8 phase;
                uint32 timer;
                uint64 playerGUID;
                uint64 orphanGUID;
                uint64 alexstraszaGUID;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_alexstraza_the_lifebinderAI(creature);
        }
};

/*######
## at_bring_your_orphan_to
######*/

class at_bring_your_orphan_to : public AreaTriggerScript
{
    public:
        at_bring_your_orphan_to() : AreaTriggerScript("at_bring_your_orphan_to") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->isDead() || !player->HasAura(SPELL_ORPHAN_OUT))
                return false;

            uint32 questId = 0;
            uint32 orphanId = 0;

            switch (trigger->id)
            {
                case AT_DOWN_AT_THE_DOCKS:
                    questId = QUEST_DOWN_AT_THE_DOCKS;
                    orphanId = ORPHAN_ORCISH;
                    break;
                case AT_GATEWAY_TO_THE_FRONTIER:
                    questId = QUEST_GATEWAY_TO_THE_FRONTIER;
                    orphanId = ORPHAN_ORCISH;
                    break;
                case AT_LORDAERON_THRONE_ROOM:
                    questId = QUEST_LORDAERON_THRONE_ROOM;
                    orphanId = ORPHAN_ORCISH;
                    break;
                case AT_BOUGHT_OF_ETERNALS:
                    questId = QUEST_BOUGHT_OF_ETERNALS;
                    orphanId = ORPHAN_HUMAN;
                    break;
                case AT_SPOOKY_LIGHTHOUSE:
                    questId = QUEST_SPOOKY_LIGHTHOUSE;
                    orphanId = ORPHAN_HUMAN;
                    break;
                case AT_STONEWROUGHT_DAM:
                    questId = QUEST_STONEWROUGHT_DAM;
                    orphanId = ORPHAN_HUMAN;
                    break;
                case AT_DARK_PORTAL:
                    questId = player->GetTeam() == ALLIANCE ? QUEST_DARK_PORTAL_A : QUEST_DARK_PORTAL_H;
                    orphanId = player->GetTeam() == ALLIANCE ? ORPHAN_DRAENEI : ORPHAN_BLOOD_ELF;
                    break;
            }

            if (questId && orphanId && getOrphanGUID(player, orphanId) && player->GetQuestStatus(questId) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(questId);

            return true;
        }
};

/*######
## npc_cw_area_trigger
######*/
class npc_cw_area_trigger : public CreatureScript
{
    public:
        npc_cw_area_trigger() : CreatureScript("npc_cw_area_trigger") {}

        struct npc_cw_area_triggerAI : public ScriptedAI
        {
            npc_cw_area_triggerAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetDisplayId(DISPLAY_INVISIBLE);
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (who && me->GetDistance2d(who) < 20.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->HasAura(SPELL_ORPHAN_OUT))
                        {
                            uint32 questId = 0;
                            uint32 orphanId = 0;
                            switch (me->GetEntry())
                            {
                                case NPC_CAVERNS_OF_TIME_CW_TRIGGER:
                                    questId = player->GetTeam() == ALLIANCE ? QUEST_TIME_TO_VISIT_THE_CAVERNS_A : QUEST_TIME_TO_VISIT_THE_CAVERNS_H;
                                    orphanId = player->GetTeam() == ALLIANCE ? ORPHAN_DRAENEI : ORPHAN_BLOOD_ELF;
                                    break;
                                case NPC_EXODAR_01_CW_TRIGGER:
                                    questId = QUEST_THE_SEAT_OF_THE_NARUU;
                                    orphanId = ORPHAN_DRAENEI;
                                    break;
                                case NPC_EXODAR_02_CW_TRIGGER:
                                    questId = QUEST_CALL_ON_THE_FARSEER;
                                    orphanId = ORPHAN_DRAENEI;
                                    break;
                                case NPC_AERIS_LANDING_CW_TRIGGER:
                                    questId = QUEST_JHEEL_IS_AT_AERIS_LANDING;
                                    orphanId = ORPHAN_DRAENEI;
                                    break;
                                case NPC_AUCHINDOUN_CW_TRIGGER:
                                    questId = QUEST_AUCHINDOUN_AND_THE_RING;
                                    orphanId = ORPHAN_DRAENEI;
                                    break;
                                case NPC_SPOREGGAR_CW_TRIGGER:
                                    questId = QUEST_HCHUU_AND_THE_MUSHROOM_PEOPLE;
                                    orphanId = ORPHAN_BLOOD_ELF;
                                    break;
                                case NPC_THRONE_OF_ELEMENTS_CW_TRIGGER:
                                    questId = QUEST_VISIT_THE_THRONE_OF_ELEMENTS;
                                    orphanId = ORPHAN_BLOOD_ELF;
                                    break;
                                case NPC_SILVERMOON_01_CW_TRIGGER:
                                    if (player->GetQuestStatus(QUEST_NOW_WHEN_I_GROW_UP) == QUEST_STATUS_INCOMPLETE && getOrphanGUID(player, ORPHAN_BLOOD_ELF))
                                    {
                                        player->AreaExploredOrEventHappens(QUEST_NOW_WHEN_I_GROW_UP);
                                        if (player->GetQuestStatus(QUEST_NOW_WHEN_I_GROW_UP) == QUEST_STATUS_COMPLETE)
                                            if (Creature* samuro = me->FindNearestCreature(25151, 20.0f))
                                            {
                                                uint32 emote = 0;
                                                switch (urand(1, 5))
                                                {
                                                    case 1:
                                                        emote = EMOTE_ONESHOT_WAVE;
                                                        break;
                                                    case 2:
                                                        emote = EMOTE_ONESHOT_ROAR;
                                                        break;
                                                    case 3:
                                                        emote = EMOTE_ONESHOT_FLEX;
                                                        break;
                                                    case 4:
                                                        emote = EMOTE_ONESHOT_SALUTE;
                                                        break;
                                                    case 5:
                                                        emote = EMOTE_ONESHOT_DANCE;
                                                        break;
                                                }
                                                samuro->HandleEmoteCommand(emote);
                                            }
                                    }
                                    break;
                            }
                            if (questId && orphanId && getOrphanGUID(player, orphanId) && player->GetQuestStatus(questId) == QUEST_STATUS_INCOMPLETE)
                                player->AreaExploredOrEventHappens(questId);
                        }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_cw_area_triggerAI(creature);
        }
};

/*######
## npc_grizzlemaw_cw_trigger
######*/
class npc_grizzlemaw_cw_trigger : public CreatureScript
{
    public:
        npc_grizzlemaw_cw_trigger() : CreatureScript("npc_grizzlemaw_cw_trigger") {}

        struct npc_grizzlemaw_cw_triggerAI : public ScriptedAI
        {
            npc_grizzlemaw_cw_triggerAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetDisplayId(DISPLAY_INVISIBLE);
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (who && who->GetDistance2d(me) < 10.0f)
                    if (Player* player = who->ToPlayer())
                        if (player->GetQuestStatus(QUEST_HOME_OF_THE_BEAR_MEN) == QUEST_STATUS_INCOMPLETE)
                            if (Creature* orphan = Creature::GetCreature(*me, getOrphanGUID(player, ORPHAN_WOLVAR)))
                            {
                                player->AreaExploredOrEventHappens(QUEST_HOME_OF_THE_BEAR_MEN);
                                orphan->AI()->Talk(TEXT_WOLVAR_ORPHAN_10);
                            }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_grizzlemaw_cw_triggerAI(creature);
        }
};

class npc_cw_redhound_twoseater_trigger : public CreatureScript
{
public:
    npc_cw_redhound_twoseater_trigger() : CreatureScript("npc_cw_redhound_twoseater_trigger")
    {
    }

    enum entryId
    {
        QUEST_RIDIN_THE_ROCKETWAY           = 29146,
        SPELL_SUMMON_REDHOUND_TWOSEATER     = 97227,
        NPC_ORCISH_ORPHAN                   = 14444
    };

    bool OnGossipHello(Player* player, Creature* /*creature*/)
    {
        bool checkOrphan = false;
        if (player->GetQuestStatus(QUEST_RIDIN_THE_ROCKETWAY) == QUEST_STATUS_INCOMPLETE)
        {
            // Remove the orphan before
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 15.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(15.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToCreature()->GetEntry() == NPC_ORCISH_ORPHAN && (*itr)->ToTempSummon()->GetSummoner() == player)
                    checkOrphan = true;
            }

            if (checkOrphan == true)
                player->CastSpell(player, SPELL_SUMMON_REDHOUND_TWOSEATER);
        }
        return true;
    }
};

class npc_cw_redhound_twoseater_vehicle : public CreatureScript
{
public:
    npc_cw_redhound_twoseater_vehicle() : CreatureScript("npc_cw_redhound_twoseater_vehicle")
    {
    }

    enum actionId
    {
        ACTION_WP_START     = 1
    };

    enum spellId
    {
        SPELL_ROCKETWAY_CREDIT      = 97376,
        SPELL_ROCKETWAY_TAKEOFF     = 97256,
        SPELL_SPEED_BOOST_IMPROVED  = 81492,
        SPELL_THE_SMOKE             = 73628
    };

    enum eventId
    {
        EVENT_SUMMON_AND_RIDE_ORPHAN    = 1,
        EVENT_RESTART_WP
    };

    enum npcId
    {
        NPC_ORPHAN          = 14444
    };

    struct npc_cw_redhound_twoseater_vehicleAI : public npc_escortAI
    {
        npc_cw_redhound_twoseater_vehicleAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_ROCKETWAY_TAKEOFF, true);
            wpInProgress = false;
            events.ScheduleEvent(EVENT_SUMMON_AND_RIDE_ORPHAN, 500);
        }

        void EnterEvadeMode()
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER)
            {
                if (wpInProgress == false)
                {
                    DoAction(ACTION_WP_START);
                    wpInProgress = true;
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(0);
                    break;
                case 4:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("Yeehaw!", 0);
                    break;
                case 5:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(1);
                    break;
                case 8:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("Oh no...", 0);
                    break;
                case 9:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(2);
                    break;
                case 11:
                    me->CastSpell(me, SPELL_SPEED_BOOST_IMPROVED, true);
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("Noo!", 0);
                    me->SetSpeed(MOVE_FLIGHT, 4.0f, true);
                    me->SetSpeed(MOVE_RUN, 4.0f, true);
                    break;
                case 13:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("Yeah!", 0);
                    break;
                case 14:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(3);
                    break;
                case 18:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                    break;
                case 22:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(4);
                    break;
                case 23:
                    me->SendGravityDisable();
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    break;
                case 26:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(5);
                    break;
                case 27:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("You probably shouldn't...", 0);
                    break;
                case 28:
                    SetEscortPaused(true);
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("Hair!", 0);
                        if (Unit* orphan = vehicle->GetPassenger(1))
                            orphan->ToCreature()->AI()->TalkWithDelay(1000, 6);
                    }
                    me->AddAura(73628, me);
                    events.ScheduleEvent(EVENT_RESTART_WP, 3500);
                    break;
                case 32:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(7);
                    break;
                case 34:
                    SetEscortPaused(true);
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(8);
                    events.ScheduleEvent(EVENT_RESTART_WP, 2500);
                    break;
                case 35:
                    SetEscortPaused(false);
                    events.ScheduleEvent(EVENT_RESTART_WP, 1500);
                    me->RemoveAurasDueToSpell(SPELL_SPEED_BOOST_IMPROVED);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->SetSpeed(MOVE_FLIGHT, 2.2f, true);
                    me->SetSpeed(MOVE_RUN, 2.2f, true);
                    me->RemoveAurasDueToSpell(SPELL_THE_SMOKE);
                    break;
                case 37:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(9);
                    break;
                case 39:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(10);
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            passenger->MonsterSay("''phew''", 0);
                    }
                    break;
                case 40:    // Quest Complete
                    me->CastSpell(me, SPELL_ROCKETWAY_CREDIT, true);
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(1))
                        {
                            passenger->ToCreature()->AI()->Talk(11);
                            passenger->ExitVehicle();
                            passenger->GetMotionMaster()->MoveJump(passenger->GetPositionX(), passenger->GetPositionY(), passenger->GetPositionZ()+3, 1.0f, 45.5f, 100);
                            passenger->ToCreature()->DespawnOrUnsummon(3000);
                        }
                        if (Unit* passenger = vehicle->GetPassenger(0))
                        {
                            passenger->CastSpell(passenger, 46419, true);
                            passenger->MonsterSay("Nooo!", 0);
                            passenger->ExitVehicle();
                            passenger->GetMotionMaster()->MoveJump(passenger->GetPositionX(), passenger->GetPositionY(), passenger->GetPositionZ()+3, 1.0f, 45.5f, 100);
                        }
                    }
                    break;
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
                    me->SetWalk(true);
                    Start(false, true, NULL, NULL, false, true);
                    me->SetSpeed(MOVE_FLIGHT, 2.2f, true);
                    me->SetSpeed(MOVE_RUN, 2.2f, true);
                    SetDespawnAtEnd(true);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_AND_RIDE_ORPHAN:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            // Handle Orphan
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_ORPHAN, 20.0f);
                            if (!creatures.empty())
                            {
                                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                        (*iter)->EnterVehicle(me, 1);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_SUMMON_AND_RIDE_ORPHAN);
                        break;
                    }
                    case EVENT_RESTART_WP:
                    {
                        SetEscortPaused(false);
                        events.CancelEvent(EVENT_RESTART_WP);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool wpInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cw_redhound_twoseater_vehicleAI(creature);
    }
};

class npc_cw_rental_chopper_trigger : public CreatureScript
{
public:
    npc_cw_rental_chopper_trigger() : CreatureScript("npc_cw_rental_chopper_trigger")
    {
    }

    enum entryId
    {
        QUEST_CRUISIN_THE_CHASM         = 29093,
        NPC_HUMAN_ORPHAN                = 14305,
        SPELL_SUMMON_RENTAL_CHOPPER     = 96505
    };

    bool OnGossipHello(Player* player, Creature* /*creature*/)
    {
        bool checkOrphan = false;
        if (player->GetQuestStatus(QUEST_CRUISIN_THE_CHASM) == QUEST_STATUS_INCOMPLETE)
        {
            // Remove the orphan before
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(player, 15.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(15.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToCreature()->GetEntry() == NPC_HUMAN_ORPHAN && (*itr)->ToTempSummon()->GetSummoner() == player)
                    checkOrphan = true;
            }

            if (checkOrphan == true)
                player->CastSpell(player, SPELL_SUMMON_RENTAL_CHOPPER);
        }
        return true;
    }
};

class npc_cw_rental_chopper_vehicle : public CreatureScript
{
public:
    npc_cw_rental_chopper_vehicle() : CreatureScript("npc_cw_rental_chopper_vehicle")
    {
    }

    enum actionId
    {
        ACTION_WP_START     = 1
    };

    enum spellId
    {
        SPELL_ROCKETWAY_CREDIT      = 97376,
        SPELL_ROCKETWAY_TAKEOFF     = 97256,
        SPELL_WHIRLING_VORTEX       = 96665
    };

    enum eventId
    {
        EVENT_SUMMON_AND_RIDE_ORPHAN    = 1,
        EVENT_RESTART_WP
    };

    enum npcId
    {
        NPC_ORPHAN  = 14305
    };

    enum questId
    {
        QUEST_CRUISIN_THE_CHASM     = 29093
    };

    struct npc_cw_rental_chopper_vehicleAI : public npc_escortAI
    {
        npc_cw_rental_chopper_vehicleAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        EventMap events;

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            me->AddUnitState(UNIT_STATE_ROTATING);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_ROCKETWAY_TAKEOFF, true);
            me->SendGravityDisable();
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            wpInProgress = false;
            events.ScheduleEvent(EVENT_SUMMON_AND_RIDE_ORPHAN, 500);
        }

        void EnterEvadeMode()
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply && passenger->GetTypeId() == TYPEID_PLAYER)
            {
                if (wpInProgress == false)
                {
                    DoAction(ACTION_WP_START);
                    wpInProgress = true;
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 6:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(0);
                    break;
                case 8:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(1);
                    break;
                case 13:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(2);
                    break;
                case 15:
                    me->GetMotionMaster()->MoveJump(-10267.06f, 1689.00f, 29.20f, 25.0f, 25.0f, 16);
                    break;
                case 17:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(3);
                    break;
                case 21:
                    me->GetMotionMaster()->MoveJump(-10425.91f, 1840.07f, 28.51f, 25.0f, 25.0f, 22);
                    break;
                case 22:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(4);
                    break;
                case 23:
                    me->GetMotionMaster()->MoveJump(-10454.22f, 1760.43f, -11.17f, 25.0f, 25.0f, 24);
                    break;
                case 24:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(5);
                    break;
                case 29:
                    // JELLY APPEAR!
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(6);
                    break;
                case 31:
                    me->GetMotionMaster()->MoveJump(-10408.86f, 1612.89f, -32.84f, 25.0f, 25.0f, 32);
                    break;
                case 33:
                    // START CYCLONE AND FLY
                    me->SendGravityDisable();
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->CastSpell(me, SPELL_WHIRLING_VORTEX, true);
                    break;
                case 35:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(7);
                    break;
                case 43:
                    // STOP CYCLONE AND FLY!
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(8);
                    me->SendGravityEnable();
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->RemoveAurasDueToSpell(SPELL_WHIRLING_VORTEX);
                    break;
                case 46:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            passenger->ToCreature()->AI()->Talk(9);
                    break;
                case 49:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            if (passenger->GetTypeId() == TYPEID_PLAYER)
                            {
                                passenger->ToPlayer()->CompleteQuest(QUEST_CRUISIN_THE_CHASM);
                                passenger->ExitVehicle();
                            }
                    break;
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
                    me->SetWalk(true);
                    Start(false, true, NULL, NULL, false, false);
                    me->SetSpeed(MOVE_FLIGHT, 2.2f, true);
                    me->SetSpeed(MOVE_RUN, 2.2f, true);
                    SetDespawnAtEnd(true);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_AND_RIDE_ORPHAN:
                    {
                        if (Unit* invoker = me->ToTempSummon()->GetSummoner())
                        {
                            // Handle Orphan
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, me, NPC_ORPHAN, 20.0f);
                            if (!creatures.empty())
                            {
                                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                                {
                                    if ((*iter)->ToTempSummon() && (*iter)->ToTempSummon()->GetSummoner() == invoker)
                                        (*iter)->EnterVehicle(me, 1);
                                }
                            }
                        }
                        events.CancelEvent(EVENT_SUMMON_AND_RIDE_ORPHAN);
                        break;
                    }
                    case EVENT_RESTART_WP:
                    {
                        SetEscortPaused(false);
                        events.CancelEvent(EVENT_RESTART_WP);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool wpInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cw_rental_chopper_vehicleAI(creature);
    }
};

void AddSC_event_childrens_week()
{
    new npc_elder_kekek();
    new npc_high_oracle_soo_roo();
    new npc_winterfin_playmate();
    new npc_snowfall_glade_playmate();
    new npc_the_etymidian();
    new npc_the_biggest_tree();
    new at_bring_your_orphan_to();
    new npc_grizzlemaw_cw_trigger();
    new npc_cw_area_trigger();
    new npc_alexstraza_the_lifebinder();
    new npc_cw_redhound_twoseater_trigger();
    new npc_cw_redhound_twoseater_vehicle();
    new npc_cw_rental_chopper_trigger();
    new npc_cw_rental_chopper_vehicle();
}
