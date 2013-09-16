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
SDName: Mulgore
SD%Complete: 100
SDComment: Support for quest: 11129, 861
SDCategory: Mulgore
EndScriptData */

/* ContentData
npc_skorn_whitecloud
npc_kyle_frenzied
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "SpellInfo.h"

/*######
# npc_skorn_whitecloud
######*/

#define GOSSIP_SW "Tell me a story, Skorn."

class npc_skorn_whitecloud : public CreatureScript
{
public:
    npc_skorn_whitecloud() : CreatureScript("npc_skorn_whitecloud") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF)
            player->SEND_GOSSIP_MENU(523, creature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (!player->GetQuestRewardStatus(770))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SW, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(522, creature->GetGUID());

        return true;
    }

};

/*#####
# npc_kyle_frenzied
######*/

enum KyleFrenzied
{
    EMOTE_SEE_LUNCH         = 0,
    EMOTE_EAT_LUNCH         = 1,
    EMOTE_DANCE             = 2,

    SPELL_LUNCH             = 42222,
    NPC_KYLE_FRENZIED       = 23616,
    NPC_KYLE_FRIENDLY       = 23622,
    POINT_ID                = 1
};

class npc_kyle_frenzied : public CreatureScript
{
public:
    npc_kyle_frenzied() : CreatureScript("npc_kyle_frenzied") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_kyle_frenziedAI (creature);
    }

    struct npc_kyle_frenziedAI : public ScriptedAI
    {
        npc_kyle_frenziedAI(Creature* creature) : ScriptedAI(creature) {}

        bool EventActive;
        bool IsMovingToLunch;
        uint64 PlayerGUID;
        uint32 EventTimer;
        uint8 EventPhase;

        void Reset()
        {
            EventActive = false;
            IsMovingToLunch = false;
            PlayerGUID = 0;
            EventTimer = 5000;
            EventPhase = 0;

            if (me->GetEntry() == NPC_KYLE_FRIENDLY)
                me->UpdateEntry(NPC_KYLE_FRENZIED);
        }

        void SpellHit(Unit* Caster, SpellInfo const* Spell)
        {
            if (!me->getVictim() && !EventActive && Spell->Id == SPELL_LUNCH)
            {
                if (Caster->GetTypeId() == TYPEID_PLAYER)
                    PlayerGUID = Caster->GetGUID();

                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
                {
                    me->GetMotionMaster()->MovementExpired();
                    me->GetMotionMaster()->MoveIdle();
                    me->StopMoving();
                }

                EventActive = true;
                Talk(EMOTE_SEE_LUNCH);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_CREATURE_SPECIAL);
            }
        }

        void MovementInform(uint32 Type, uint32 PointId)
        {
            if (Type != POINT_MOTION_TYPE || !EventActive)
                return;

            if (PointId == POINT_ID)
                IsMovingToLunch = false;
        }

        void UpdateAI(uint32 diff)
        {
            if (EventActive)
            {
                if (IsMovingToLunch)
                    return;

                if (EventTimer <= diff)
                {
                    EventTimer = 5000;
                    ++EventPhase;

                    switch (EventPhase)
                    {
                        case 1:
                            if (Unit* unit = Unit::GetUnit(*me, PlayerGUID))
                            {
                                if (GameObject* go = unit->GetGameObject(SPELL_LUNCH))
                                {
                                    IsMovingToLunch = true;
                                    me->GetMotionMaster()->MovePoint(POINT_ID, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ());
                                }
                            }
                            break;
                        case 2:
                            Talk(EMOTE_EAT_LUNCH);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                            break;
                        case 3:
                            if (Player* unit = Unit::GetPlayer(*me, PlayerGUID))
                                unit->TalkedToCreature(me->GetEntry(), me->GetGUID());

                            me->UpdateEntry(NPC_KYLE_FRIENDLY);
                            break;
                        case 4:
                            EventTimer = 30000;
                            Talk(EMOTE_DANCE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DANCESPECIAL);
                            break;
                        case 5:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                            Reset();
                            me->GetMotionMaster()->Clear();
                            break;
                    }
                }
                else
                    EventTimer -= diff;
            }
        }
    };

};

class npc_trough : public CreatureScript
{
public:
    npc_trough() : CreatureScript("npc_trough") { }

    struct npc_troughAI : public ScriptedAI
    {
        npc_troughAI(Creature* creature) : ScriptedAI(creature) {}

        enum Spells
        {
            SPELL_THROW_TORCH = 69228
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (!me->getVictim() && spell->Id == SPELL_THROW_TORCH)
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    switch (me->GetEntry())
                    {
                        case 36727:
                            caster->ToPlayer()->KilledMonsterCredit(36727);
                            me->AddAura(97664, me);
                            me->SetRespawnTime(60);
                            break;
                        case 37155:
                            caster->ToPlayer()->KilledMonsterCredit(37155);
                            me->AddAura(97664, me);
                            me->SetRespawnTime(60);
                            break;
                        case 37156:
                            caster->ToPlayer()->KilledMonsterCredit(37156);
                            me->AddAura(97664, me);
                            me->SetRespawnTime(60);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_troughAI (creature);
    }
};

class npc_chief_hawkwind : public CreatureScript
{
public:
    npc_chief_hawkwind() : CreatureScript("npc_chief_hawkwind") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chief_hawkwindAI (creature);
    }

    enum Id
    {
        QUEST_LAST_RITES_FIRST_RITES = 24861,
        NPC_CHIEF_HAWKWIND           = 2981,
        NPC_GREATMOTHER_HAWKIND      = 2991
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LAST_RITES_FIRST_RITES)
        {
            if (Creature* chiefHawkind = creature->FindNearestCreature(NPC_CHIEF_HAWKWIND, 20.0f))
            {
                chiefHawkind->AI()->TalkWithDelay(2000, 0);
                chiefHawkind->AI()->TalkWithDelay(8000, 1);
                chiefHawkind->AI()->TalkWithDelay(16000, 2);
                chiefHawkind->AI()->TalkWithDelay(28000, 3);
            }
            if (player)
                player->SummonCreature(NPC_GREATMOTHER_HAWKIND, -2904.65f, -254.16f, 59.73f, 3.23f, TEMPSUMMON_MANUAL_DESPAWN)->UnSummon(60000);
        }
        return false;
    }

    struct npc_chief_hawkwindAI : public ScriptedAI
    {
        npc_chief_hawkwindAI(Creature* creature) : ScriptedAI(creature) {}
    };

};

class npc_wounded_brave : public CreatureScript
{
public:
    npc_wounded_brave() : CreatureScript("npc_wounded_brave") { }

    struct npc_wounded_braveAI : public ScriptedAI
    {
        npc_wounded_braveAI(Creature* creature) : ScriptedAI(creature) {}

        enum Spells
        {
            SPELL_FLASH_HEAL    = 2061,
            SPELL_REJUVENATION  = 774
        };

        enum Quests
        {
            QUEST_HEALING_IN_A_FLASH = 27066,
            QUEST_REJUVENATING_TOUCH = 27067
        };

        enum Credits
        {
            QUEST_CREDIT_WOUNDED_BRAVE = 44175
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                switch (spell->Id)
                {
                    case 2061: // Flash Heal
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_HEALING_IN_A_FLASH) != QUEST_STATUS_COMPLETE)
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WOUNDED_BRAVE);
                        break;
                    case 774: // Rejuvenation
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_REJUVENATING_TOUCH) != QUEST_STATUS_COMPLETE)
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WOUNDED_BRAVE);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wounded_braveAI (creature);
    }
};

class npc_agitated_earth_spirit : public CreatureScript
{
public:
    npc_agitated_earth_spirit() : CreatureScript("npc_agitated_earth_spirit") { }

    struct npc_agitated_earth_spiritAI : public ScriptedAI
    {
        npc_agitated_earth_spiritAI(Creature* creature) : ScriptedAI(creature) {}
        uint16 despawnTimer;

        enum Spells
        {
            SPELL_SOOTHE_EARTH_SPIRIT   = 69453
        };

        enum Credits
        {
            QUEST_CREDIT_AGITATED_EARTH_SPIRIT  = 36872
        };

        enum Timers
        {
            SPIRIT_TIMER_DESPAWN = 2000
        };

        void Reset()
        {
            despawnTimer = SPIRIT_TIMER_DESPAWN;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            uint8 randSelect = urand(0, 1);
            if (!caster)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_SOOTHE_EARTH_SPIRIT)
            {
                me->GetMotionMaster()->MoveChase(caster);
                switch (randSelect)
                {
                    case 0:
                        me->setFaction(35);
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_AGITATED_EARTH_SPIRIT);
                        break;
                    case 1:
                        me->setFaction(16);
                        me->AI()->Talk(0);
                        me->Attack(caster, true);
                        break;
                    default:
                        break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (UpdateVictim() || me->getFaction() != 35)
                return;

            if(despawnTimer <= diff)
            {
                me->DespawnOrUnsummon(1000);
                despawnTimer = SPIRIT_TIMER_DESPAWN;
            }
            else
                despawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_agitated_earth_spiritAI (creature);
    }
};

void AddSC_mulgore()
{
    new npc_skorn_whitecloud();
    new npc_kyle_frenzied();
    new npc_trough();
    new npc_chief_hawkwind();
    new npc_wounded_brave();
    new npc_agitated_earth_spirit();
}
