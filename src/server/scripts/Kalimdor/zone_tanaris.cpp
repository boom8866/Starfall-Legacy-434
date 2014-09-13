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
SDName: Tanaris
SD%Complete: 80
SDComment: Quest support: 648, 10277, 10279(Special flight path).
SDCategory: Tanaris
EndScriptData */

/* ContentData
npc_custodian_of_time
npc_steward_of_time
npc_OOX17
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Player.h"
#include "WorldSession.h"
#include "Vehicle.h"

/*######
## mob_aquementas
######*/

enum Aquementas
{
    AGGRO_YELL_AQUE     = 0,

    SPELL_AQUA_JET      = 13586,
    SPELL_FROST_SHOCK   = 15089
};

class mob_aquementas : public CreatureScript
{
public:
    mob_aquementas() : CreatureScript("mob_aquementas") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_aquementasAI (creature);
    }

    struct mob_aquementasAI : public ScriptedAI
    {
        mob_aquementasAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 SendItemTimer;
        uint32 SwitchFactionTimer;
        bool isFriendly;

        uint32 FrostShockTimer;
        uint32 AquaJetTimer;

        void Reset()
        {
            SendItemTimer = 0;
            SwitchFactionTimer = 10000;
            me->setFaction(35);
            isFriendly = true;

            AquaJetTimer = 5000;
            FrostShockTimer = 1000;
        }

        void SendItem(Unit* receiver)
        {
            if (CAST_PLR(receiver)->HasItemCount(11169, 1, false) &&
                CAST_PLR(receiver)->HasItemCount(11172, 11, false) &&
                CAST_PLR(receiver)->HasItemCount(11173, 1, false) &&
                !CAST_PLR(receiver)->HasItemCount(11522, 1, true))
            {
                ItemPosCountVec dest;
                uint8 msg = CAST_PLR(receiver)->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 11522, 1, NULL);
                if (msg == EQUIP_ERR_OK)
                    CAST_PLR(receiver)->StoreNewItem(dest, 11522, 1, true);
            }
        }

        void EnterCombat(Unit* who)
        {
            Talk(AGGRO_YELL_AQUE, who->GetGUID());
        }

        void UpdateAI(uint32 diff)
        {
            if (isFriendly)
            {
                if (SwitchFactionTimer <= diff)
                {
                    me->setFaction(91);
                    isFriendly = false;
                } else SwitchFactionTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (!isFriendly)
            {
                if (SendItemTimer <= diff)
                {
                    if (me->getVictim()->GetTypeId() == TYPEID_PLAYER)
                        SendItem(me->getVictim());
                    SendItemTimer = 5000;
                } else SendItemTimer -= diff;
            }

            if (FrostShockTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FROST_SHOCK);
                FrostShockTimer = 15000;
            } else FrostShockTimer -= diff;

            if (AquaJetTimer <= diff)
            {
                DoCast(me, SPELL_AQUA_JET);
                AquaJetTimer = 15000;
            } else AquaJetTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

/*######
## npc_custodian_of_time
######*/

enum CustodianOfTime
{
    WHISPER_CUSTODIAN_1     = 0,
    WHISPER_CUSTODIAN_2     = 1,
    WHISPER_CUSTODIAN_3     = 2,
    WHISPER_CUSTODIAN_4     = 3,
    WHISPER_CUSTODIAN_5     = 4,
    WHISPER_CUSTODIAN_6     = 5,
    WHISPER_CUSTODIAN_7     = 6,
    WHISPER_CUSTODIAN_8     = 7,
    WHISPER_CUSTODIAN_9     = 8,
    WHISPER_CUSTODIAN_10    = 9,
    WHISPER_CUSTODIAN_11    = 10,
    WHISPER_CUSTODIAN_12    = 11,
    WHISPER_CUSTODIAN_13    = 12,
    WHISPER_CUSTODIAN_14    = 13
};

class npc_custodian_of_time : public CreatureScript
{
public:
    npc_custodian_of_time() : CreatureScript("npc_custodian_of_time") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_custodian_of_timeAI(creature);
    }

    struct npc_custodian_of_timeAI : public npc_escortAI
    {
        npc_custodian_of_timeAI(Creature* creature) : npc_escortAI(creature) {}

        void WaypointReached(uint32 waypointId)
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                    case 0:
                        Talk(WHISPER_CUSTODIAN_1, player->GetGUID());
                        break;
                    case 1:
                        Talk(WHISPER_CUSTODIAN_2, player->GetGUID());
                        break;
                    case 2:
                        Talk(WHISPER_CUSTODIAN_3, player->GetGUID());
                        break;
                    case 3:
                        Talk(WHISPER_CUSTODIAN_4, player->GetGUID());
                        break;
                    case 5:
                        Talk(WHISPER_CUSTODIAN_5, player->GetGUID());
                        break;
                    case 6:
                        Talk(WHISPER_CUSTODIAN_6, player->GetGUID());
                        break;
                    case 7:
                        Talk(WHISPER_CUSTODIAN_7, player->GetGUID());
                        break;
                    case 8:
                        Talk(WHISPER_CUSTODIAN_8, player->GetGUID());
                        break;
                    case 9:
                        Talk(WHISPER_CUSTODIAN_9, player->GetGUID());
                        break;
                    case 10:
                        Talk(WHISPER_CUSTODIAN_4, player->GetGUID());
                        break;
                    case 13:
                        Talk(WHISPER_CUSTODIAN_10, player->GetGUID());
                        break;
                    case 14:
                        Talk(WHISPER_CUSTODIAN_4, player->GetGUID());
                        break;
                    case 16:
                        Talk(WHISPER_CUSTODIAN_11, player->GetGUID());
                        break;
                    case 17:
                        Talk(WHISPER_CUSTODIAN_12, player->GetGUID());
                        break;
                    case 18:
                        Talk(WHISPER_CUSTODIAN_4, player->GetGUID());
                        break;
                    case 22:
                        Talk(WHISPER_CUSTODIAN_13, player->GetGUID());
                        break;
                    case 23:
                        Talk(WHISPER_CUSTODIAN_4, player->GetGUID());
                        break;
                    case 24:
                        Talk(WHISPER_CUSTODIAN_14, player->GetGUID());
                        DoCast(player, 34883);
                        // below here is temporary workaround, to be removed when spell works properly
                        player->AreaExploredOrEventHappens(10277);
                        break;
                }
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
                return;

            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (who->HasAura(34877) && CAST_PLR(who)->GetQuestStatus(10277) == QUEST_STATUS_INCOMPLETE)
                {
                    float Radius = 10.0f;
                    if (me->IsWithinDistInMap(who, Radius))
                    {
                        Start(false, false, who->GetGUID());
                    }
                }
            }
        }

        void EnterCombat(Unit* /*who*/) {}
        void Reset() {}

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };

};

/*######
## npc_steward_of_time
######*/

#define GOSSIP_ITEM_FLIGHT  "Please take me to the master's lair."

class npc_steward_of_time : public CreatureScript
{
public:
    npc_steward_of_time() : CreatureScript("npc_steward_of_time") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == 10279)                      //Quest: To The Master's Lair
            player->CastSpell(player, 34891, true);               //(Flight through Caverns)

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
            player->CastSpell(player, 34891, true);               //(Flight through Caverns)

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(10279) == QUEST_STATUS_INCOMPLETE || player->GetQuestRewardStatus(10279))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(9978, creature->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(9977, creature->GetGUID());

        return true;
    }

};

/*######
## npc_OOX17
######*/

enum Npc00X17
{
    SAY_OOX_START           = 0,
    SAY_OOX_AGGRO           = 1,
    SAY_OOX_AMBUSH          = 2,
    SAY_OOX17_AMBUSH_REPLY  = 0,
    SAY_OOX_END             = 3,

    Q_OOX17                 = 648,
    SPAWN_FIRST             = 7803,
    SPAWN_SECOND_1          = 5617,
    SPAWN_SECOND_2          = 7805
};

class npc_OOX17 : public CreatureScript
{
public:
    npc_OOX17() : CreatureScript("npc_OOX17") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == Q_OOX17)
        {
            creature->setFaction(113);
            creature->SetFullHealth();
            creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            creature->AI()->Talk(SAY_OOX_START);

            if (npc_escortAI* pEscortAI = CAST_AI(npc_OOX17::npc_OOX17AI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_OOX17AI(creature);
    }

    struct npc_OOX17AI : public npc_escortAI
    {
        npc_OOX17AI(Creature* creature) : npc_escortAI(creature) {}

        void WaypointReached(uint32 waypointId)
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                    case 23:
                        me->SummonCreature(SPAWN_FIRST, -8350.96f, -4445.79f, 10.10f, 6.20f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_FIRST, -8355.96f, -4447.79f, 10.10f, 6.27f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_FIRST, -8353.96f, -4442.79f, 10.10f, 6.08f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        Talk(SAY_OOX_AMBUSH);
                        break;
                    case 56:
                        me->SummonCreature(SPAWN_SECOND_1, -7510.07f, -4795.50f, 9.35f, 6.06f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_SECOND_2, -7515.07f, -4797.50f, 9.35f, 6.22f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_SECOND_2, -7518.07f, -4792.50f, 9.35f, 6.22f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        Talk(SAY_OOX_AMBUSH);
                        if (Creature* scoff = me->FindNearestCreature(SPAWN_SECOND_2, 30))
                            scoff->AI()->Talk(SAY_OOX17_AMBUSH_REPLY);
                        break;
                    case 86:
                        Talk(SAY_OOX_END);
                        player->GroupEventHappens(Q_OOX17, me);
                        break;
                }
            }
        }

        void Reset(){}

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_OOX_AGGRO);
        }

        void JustSummoned(Creature* summoned)
        {
            summoned->AI()->AttackStart(me);
        }
    };
};

/*####
# npc_tooga
####*/

enum Tooga
{
    SAY_TOOG_WORRIED            = 0,
    SAY_TOOG_POST_1             = 1,
    SAY_TORT_POST_2             = 0,
    SAY_TOOG_POST_3             = 2,
    SAY_TORT_POST_4             = 1,
    SAY_TOOG_POST_5             = 3,
    SAY_TORT_POST_6             = 2,

    QUEST_TOOGA                 = 1560,
    NPC_TORTA                   = 6015,

    POINT_ID_TO_WATER           = 1,
    FACTION_TOOG_ESCORTEE       = 113
};

Position const ToWaterLoc = {-7032.664551f, -4906.199219f, -1.606446f, 0.0f};

class npc_tooga : public CreatureScript
{
public:
    npc_tooga() : CreatureScript("npc_tooga") { }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_TOOGA)
        {
            if (npc_toogaAI* pToogaAI = CAST_AI(npc_tooga::npc_toogaAI, creature->AI()))
                pToogaAI->StartFollow(player, FACTION_TOOG_ESCORTEE, quest);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_toogaAI(creature);
    }

    struct npc_toogaAI : public FollowerAI
    {
        npc_toogaAI(Creature* creature) : FollowerAI(creature) { }

        uint32 CheckSpeechTimer;
        uint32 PostEventTimer;
        uint32 PhasePostEvent;

        uint64 TortaGUID;

        void Reset()
        {
            CheckSpeechTimer = 2500;
            PostEventTimer = 1000;
            PhasePostEvent = 0;

            TortaGUID = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            FollowerAI::MoveInLineOfSight(who);

            if (!me->getVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE | STATE_FOLLOW_POSTEVENT) && who->GetEntry() == NPC_TORTA)
            {
                if (me->IsWithinDistInMap(who, INTERACTION_DISTANCE))
                {
                    Player* player = GetLeaderForFollower();
                    if (player && player->GetQuestStatus(QUEST_TOOGA) == QUEST_STATUS_INCOMPLETE)
                        player->GroupEventHappens(QUEST_TOOGA, me);

                    TortaGUID = who->GetGUID();
                    SetFollowComplete(true);
                }
            }
        }

        void MovementInform(uint32 MotionType, uint32 PointId)
        {
            FollowerAI::MovementInform(MotionType, PointId);

            if (MotionType != POINT_MOTION_TYPE)
                return;

            if (PointId == POINT_ID_TO_WATER)
                SetFollowComplete();
        }

        void UpdateFollowerAI(uint32 Diff)
        {
            if (!UpdateVictim())
            {
                //we are doing the post-event, or...
                if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                {
                    if (PostEventTimer <= Diff)
                    {
                        PostEventTimer = 5000;

                        Creature* torta = Creature::GetCreature(*me, TortaGUID);
                        if (!torta || !torta->isAlive())
                        {
                            //something happened, so just complete
                            SetFollowComplete();
                            return;
                        }

                        switch (PhasePostEvent)
                        {
                            case 1:
                                Talk(SAY_TOOG_POST_1);
                                break;
                            case 2:
                                torta->AI()->Talk(SAY_TORT_POST_2);
                                break;
                            case 3:
                                Talk(SAY_TOOG_POST_3);
                                break;
                            case 4:
                                torta->AI()->Talk(SAY_TORT_POST_4);
                                break;
                            case 5:
                                Talk(SAY_TOOG_POST_5);
                                break;
                            case 6:
                                torta->AI()->Talk(SAY_TORT_POST_6);
                                me->GetMotionMaster()->MovePoint(POINT_ID_TO_WATER, ToWaterLoc);
                                break;
                        }

                        ++PhasePostEvent;
                    }
                    else
                        PostEventTimer -= Diff;
                }
                //...we are doing regular speech check
                else if (HasFollowState(STATE_FOLLOW_INPROGRESS))
                {
                    if (CheckSpeechTimer <= Diff)
                    {
                        CheckSpeechTimer = 5000;

                        if (urand(0, 9) > 8)
                            Talk(SAY_TOOG_WORRIED);
                    }
                    else
                        CheckSpeechTimer -= Diff;
                }

                return;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class spell_deploy_butcherbot : public SpellScriptLoader
{
    public:
        spell_deploy_butcherbot() : SpellScriptLoader("spell_deploy_butcherbot") { }

        class spell_deploy_butcherbot_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_deploy_butcherbot_SpellScript);

            enum Id
            {
                NPC_GLASSHIDE_BASILISK  = 5419,
                NPC_FIRE_ROC            = 5429,
                NPC_BLISTERPAW_HYENA    = 5426
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* basilisk = caster->FindNearestCreature(NPC_GLASSHIDE_BASILISK, 6.0f, false))
                    {
                        if (basilisk->isAlive() || basilisk->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        else
                            return SPELL_CAST_OK;
                    }
                    else if (Creature* fireRoc = caster->FindNearestCreature(NPC_FIRE_ROC, 6.0f, false))
                    {
                        if (fireRoc->isAlive() || fireRoc->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        else
                            return SPELL_CAST_OK;
                    }
                    else if (Creature* hyena = caster->FindNearestCreature(NPC_BLISTERPAW_HYENA, 6.0f, false))
                    {
                        if (hyena->isAlive() || hyena->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        else
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_deploy_butcherbot_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_deploy_butcherbot_SpellScript();
        }
};

class npc_butcherbot : public CreatureScript
{
public:
   npc_butcherbot() : CreatureScript("npc_butcherbot") {}

    struct npc_butcherbotAI : public ScriptedAI
    {
        npc_butcherbotAI(Creature* creature) : ScriptedAI(creature) {unitOwner = NULL;}

        enum questId
        {
            // Spell
            SPELL_BUTCHERBOT_BUTCHERING     = 74168,

            // Npc
            NPC_GLASSHIDE_BASILISK          = 5419,
            NPC_FIRE_ROC                    = 5429,
            NPC_BLISTERPAW_HYENA            = 5426,

            // Credit
            CREDIT_BASILISK                 = 39702,
            CREDIT_FIRE_ROC                 = 40507,
            CREDIT_HYENA                    = 40509
        };

        enum pointId
        {
            POINT_TO_BUTCHERING     = 1
        };

        class restoreFlags : public BasicEvent
        {
            public:
                explicit restoreFlags(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->SetWalk(true);
            if (Creature* basilisk = owner->FindNearestCreature(NPC_GLASSHIDE_BASILISK, 20.0f, false))
            {
                me->GetMotionMaster()->MovePoint(POINT_TO_BUTCHERING, basilisk->GetPositionX()+2, basilisk->GetPositionY()-2, basilisk->GetPositionZ(), true);
                basilisk->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                // Safety event in case of early despawn of the butcherbot...
                basilisk->m_Events.AddEvent(new restoreFlags(basilisk), (basilisk)->m_Events.CalculateTime(20000));
            }
            else if (Creature* fireRoc = owner->FindNearestCreature(NPC_FIRE_ROC, 20.0f, false))
            {
                me->GetMotionMaster()->MovePoint(POINT_TO_BUTCHERING, fireRoc->GetPositionX()+2, fireRoc->GetPositionY()-2, fireRoc->GetPositionZ(), true);
                fireRoc->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                // Safety event in case of early despawn of the butcherbot...
                fireRoc->m_Events.AddEvent(new restoreFlags(fireRoc), (fireRoc)->m_Events.CalculateTime(20000));
            }
            else if (Creature* hyena = owner->FindNearestCreature(NPC_BLISTERPAW_HYENA, 20.0f, false))
            {
                me->GetMotionMaster()->MovePoint(POINT_TO_BUTCHERING, hyena->GetPositionX()+2, hyena->GetPositionY()-2, hyena->GetPositionZ(), true);
                hyena->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                // Safety event in case of early despawn of the butcherbot...
                hyena->m_Events.AddEvent(new restoreFlags(hyena), (hyena)->m_Events.CalculateTime(20000));
            }

            unitOwner = owner;
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_BUTCHERING:
                {
                    TalkWithDelay(1000, 0);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    if (unitOwner && unitOwner != NULL)
                    {
                        if (Creature* basilisk = me->FindNearestCreature(NPC_GLASSHIDE_BASILISK, 20.0f, false))
                        {
                            if (unitOwner->GetTypeId() == TYPEID_PLAYER)
                                unitOwner->ToPlayer()->KilledMonsterCredit(CREDIT_BASILISK);
                            me->CastWithDelay(500, basilisk, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(1500, basilisk, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(2500, basilisk, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(3500, basilisk, SPELL_BUTCHERBOT_BUTCHERING, true);
                            basilisk->m_Events.AddEvent(new restoreFlags(basilisk), (basilisk)->m_Events.CalculateTime(4250));
                            basilisk->DespawnOrUnsummon(4500);
                            me->DespawnOrUnsummon(4500);
                        }
                        else if (Creature* fireRoc = me->FindNearestCreature(NPC_FIRE_ROC, 20.0f, false))
                        {
                            if (unitOwner->GetTypeId() == TYPEID_PLAYER)
                                unitOwner->ToPlayer()->KilledMonsterCredit(CREDIT_FIRE_ROC);
                            me->CastWithDelay(500, fireRoc, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(1500, fireRoc, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(2500, fireRoc, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(3500, fireRoc, SPELL_BUTCHERBOT_BUTCHERING, true);
                            fireRoc->m_Events.AddEvent(new restoreFlags(fireRoc), (fireRoc)->m_Events.CalculateTime(4250));
                            fireRoc->DespawnOrUnsummon(4500);
                            me->DespawnOrUnsummon(4500);
                        }
                        else if (Creature* hyena = me->FindNearestCreature(NPC_BLISTERPAW_HYENA, 20.0f, false))
                        {
                            if (unitOwner->GetTypeId() == TYPEID_PLAYER)
                                unitOwner->ToPlayer()->KilledMonsterCredit(CREDIT_HYENA);
                            me->CastWithDelay(500, hyena, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(1500, hyena, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(2500, hyena, SPELL_BUTCHERBOT_BUTCHERING, true);
                            me->CastWithDelay(3500, hyena, SPELL_BUTCHERBOT_BUTCHERING, true);
                            hyena->m_Events.AddEvent(new restoreFlags(hyena), (hyena)->m_Events.CalculateTime(4250));
                            hyena->DespawnOrUnsummon(4500);
                            me->DespawnOrUnsummon(4500);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* unitOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_butcherbotAI(creature);
    }
};

class npc_steamwheedle_balloon : public CreatureScript
{
public:
   npc_steamwheedle_balloon() : CreatureScript("npc_steamwheedle_balloon") { }

    enum questId
    {
        QUEST_ENTRY_ROCKET_RESCUE_A     = 25050,
        QUEST_ENTRY_ROCKET_RESCUE_H     = 24910,
        NPC_STEAMWHEEDLE_BALLOON        = 40505,
        SPELL_TEMP_INVISIBILITY         = 3680
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_ROCKET_RESCUE_H) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_ENTRY_ROCKET_RESCUE_A))
        {
            if (!player->GetVehicleBase() && !creature->HasAura(SPELL_TEMP_INVISIBILITY))
            {
                player->SummonCreature(NPC_STEAMWHEEDLE_BALLOON, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                creature->AddAura(SPELL_TEMP_INVISIBILITY, creature);
                return true;
            }
        }
        return true;
    }
};

class npc_steamwheedle_balloon_escort : public CreatureScript
{
public:
    npc_steamwheedle_balloon_escort() : CreatureScript("npc_steamwheedle_balloon_escort") { }

    struct npc_steamwheedle_balloon_escortAI : public npc_escortAI
    {
        npc_steamwheedle_balloon_escortAI(Creature* creature) : npc_escortAI(creature) {playerQuester = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum questId
        {
            QUEST_ENTRY_ROCKET_RESCUE   = 25050
        };

        enum eventId
        {
            EVENT_START_WAYPOINT    = 1
        };

        void OnCharmed(bool apply) {}

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 3: // Enable Abilities
                {
                    if (playerQuester && playerQuester != NULL)
                    {
                        if (Creature* vehicle = playerQuester->GetVehicleCreatureBase())
                            vehicle->AI()->DoAction(2);
                    }
                    break;
                }
                case 16: // Loop WP
                {
                    SetNextWaypoint(3, false);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerQuester = owner;
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 100);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(false, true, NULL, NULL, false, true, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_WAYPOINT:
                    {
                        events.CancelEvent(EVENT_START_WAYPOINT);
                        DoAction(ACTION_START_WP);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerQuester;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_steamwheedle_balloon_escortAI(creature);
    }
};

class npc_balloon_throwing_station : public CreatureScript
{
public:
    npc_balloon_throwing_station() : CreatureScript("npc_balloon_throwing_station") {}

    struct npc_balloon_throwing_stationAI : public ScriptedAI
    {
        npc_balloon_throwing_stationAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER  = 1
        };

        enum actionId
        {
            ACTION_RIDE_INVOKER         = 1,
            ACTION_ENABLE_ABILITIES
        };

        enum spellId
        {
            SPELL_ENABLE_ABILITIES  = 75990
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1500);
            me->SetReactState(REACT_PASSIVE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_RIDE_INVOKER:
                {
                    if (Unit* myOwner = me->ToTempSummon()->GetSummoner())
                    {
                        if (Unit* ownerOwner = myOwner->ToTempSummon()->GetSummoner())
                            ownerOwner->EnterVehicle(me, 0);
                    }
                    break;
                }
                case ACTION_ENABLE_ABILITIES:
                {
                    me->AddAura(SPELL_ENABLE_ABILITIES, me);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        DoAction(ACTION_RIDE_INVOKER);
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
        return new npc_balloon_throwing_stationAI(creature);
    }
};

class spell_emergency_rocket_pack : public SpellScriptLoader
{
    public:
        spell_emergency_rocket_pack() : SpellScriptLoader("spell_emergency_rocket_pack") { }

        class spell_emergency_rocket_pack_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_emergency_rocket_pack_SpellScript);

            enum Id
            {
                SPELL_EMERGENCY_ROCKET_PACK     = 75730
            };

            void HandleReturnToGadgetzan()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(0))
                    {
                        passenger->ExitVehicle();
                        passenger->CastSpell(caster, SPELL_EMERGENCY_ROCKET_PACK, true);
                        passenger->GetMotionMaster()->MoveJump(-7114.65f, -3888.82f, 75.0f, 45.0f, 25.0f, 10);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_emergency_rocket_pack_SpellScript::HandleReturnToGadgetzan);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_emergency_rocket_pack_SpellScript();
        }
};

class npc_wrangled_silithid : public CreatureScript
{
public:
    npc_wrangled_silithid() : CreatureScript("npc_wrangled_silithid") {}

    struct npc_wrangled_silithidAI : public ScriptedAI
    {
        npc_wrangled_silithidAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_CHECK_QUESTGIVER  = 1
        };

        enum spellId
        {
            SPELL_ROPE_BEAM             = 73113,
            SPELL_WRANGLING_A_SILITHID  = 72681
        };

        enum creditId
        {
            CREDIT_A_GREAT_IDEA     = 38742
        };

        enum npcId
        {
            NPC_ZEKE_BOOTSCUFF  = 38706
        };

        void IsSummonedBy(Unit* owner)
        {
            me->CastSpell(owner, SPELL_ROPE_BEAM, true);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MoveFollow(owner, 5.0f, 0);
            me->CastSpell(me, SPELL_WRANGLING_A_SILITHID, true);
            events.ScheduleEvent(EVENT_CHECK_QUESTGIVER, 5000);
            me->ClearUnitState(UNIT_STATE_CASTING);
            playerOwner = owner;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_QUESTGIVER:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Creature* questGiver = me->FindNearestCreature(NPC_ZEKE_BOOTSCUFF, 30.0f))
                            {
                                questGiver->AI()->Talk(0);
                                questGiver->AI()->TalkWithDelay(5000, 1);
                                me->RemoveAurasDueToSpell(SPELL_ROPE_BEAM);
                                if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                {
                                    playerOwner->ToPlayer()->KilledMonsterCredit(CREDIT_A_GREAT_IDEA);
                                    playerOwner->RemoveAurasDueToSpell(SPELL_WRANGLING_A_SILITHID);
                                }
                                me->RemoveAurasDueToSpell(SPELL_WRANGLING_A_SILITHID);
                                me->GetMotionMaster()->MovementExpired(false);
                                me->GetMotionMaster()->MovePoint(0, -8689.42f, -4073.94f, 40.25f, true);
                                me->DespawnOrUnsummon(30000);
                                events.CancelEvent(EVENT_CHECK_QUESTGIVER);
                            }
                            else
                                events.RescheduleEvent(EVENT_CHECK_QUESTGIVER, 2000);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wrangled_silithidAI(creature);
    }
};

class spell_throw_hyena_chunk : public SpellScriptLoader
{
    public:
        spell_throw_hyena_chunk() : SpellScriptLoader("spell_throw_hyena_chunk") { }

        class spell_throw_hyena_chunk_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_throw_hyena_chunk_SpellScript);

            enum Id
            {
                NPC_HAZZALI_SWARMER     = 5451,
                SPELL_SUMMON_WRANGLED   = 72677
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* swarmer = caster->FindNearestCreature(NPC_HAZZALI_SWARMER, 10.0f, true))
                    {
                        caster->CastWithDelay(1000, swarmer, SPELL_SUMMON_WRANGLED, true);
                        swarmer->DespawnOrUnsummon(1000);
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_throw_hyena_chunk_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_throw_hyena_chunk_SpellScript();
        }
};

class spell_detonate_silithid : public SpellScriptLoader
{
    public:
        spell_detonate_silithid() : SpellScriptLoader("spell_detonate_silithid") { }

        class spell_detonate_silithid_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_detonate_silithid_SpellScript);

            enum Id
            {
                NPC_EXPLOSION_BUNNY         = 37522,
                SPELL_EXPLODE_AND_BURN      = 72942,
                CREDIT_HIVE_EXPLODED        = 38996
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* bunny = caster->FindNearestCreature(NPC_EXPLOSION_BUNNY, 10.0f, true))
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleStartExplosion()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 80.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(80.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_EXPLOSION_BUNNY)
                            (*itr)->CastSpell((*itr), SPELL_EXPLODE_AND_BURN, true);
                    }
                    caster->CastSpell(caster, SPELL_EXPLODE_AND_BURN, true);
                    if (Unit* owner = caster->GetCharmerOrOwner())
                    {
                        if (owner->GetTypeId() == TYPEID_PLAYER)
                            owner->ToPlayer()->KilledMonsterCredit(CREDIT_HIVE_EXPLODED);
                    }
                    if (caster->GetTypeId() == TYPEID_UNIT)
                        caster->ToCreature()->DespawnOrUnsummon(5000);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_detonate_silithid_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_detonate_silithid_SpellScript::HandleStartExplosion);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_detonate_silithid_SpellScript();
        }
};

class go_antediluvean_chest : public GameObjectScript
{
public:
    go_antediluvean_chest() : GameObjectScript("go_antediluvean_chest") { }

    enum Id
    {
        QUEST_WHAT_LIES_WITHIN      = 25070,
        NPC_ANTECHAMBER_GUARDIAN    = 39077
    };

    bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_WHAT_LIES_WITHIN)
        {
            Creature* guardian = player->FindNearestCreature(NPC_ANTECHAMBER_GUARDIAN, 200.0f, true);
            if (!guardian)
                player->SummonCreature(NPC_ANTECHAMBER_GUARDIAN, -9801.23f, -2790.20f, 10.39f, 3.17f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            return true;
        }
        return true;
    }
};

class npc_dr_dealwell : public CreatureScript
{
public:
    npc_dr_dealwell() : CreatureScript("npc_dr_dealwell") { }

    enum questId
    {
        QUEST_ENTRY_GRUDGE_MATCH_A  = 25513,
        QUEST_ENTRY_GRUDGE_MATCH_H  = 25591,
        QUEST_ENTRY_SARINEXX        = 25095,
        QUEST_ENTRY_THE_GINORMUS    = 25067,
        QUEST_ENTRY_ZUMONGA         = 25094
    };

    enum npcId
    {
        NPC_MEGS_DREADSHREDDER  = 40542,    // Grudge Match A
        NPC_KELSEY_STEELSPARK   = 40876,    // Grudge Match H

        NPC_SARINEXX            = 39149,    // Sarinexx
        NPC_THE_GINORMUS        = 39075,    // The Ginormus
        NPC_ZUMONGA             = 39148     // Zumonga
    };

    enum eventId
    {
        EVENT_CHECK_ENCOUNTERS  = 1,
        EVENT_RANDOM_YELL
    };

    enum spellId
    {
        SPELL_THUNDERDROME_EVENT_FAIL   = 76082
    };

    enum actionId
    {
        ACTION_ADD_EVENT_CHECK_TIMER    = 1
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_ENTRY_GRUDGE_MATCH_A:
            {
                creature->SummonCreature(NPC_MEGS_DREADSHREDDER, -7140.11f, -3786.13f, 8.97f, 5.98f, TEMPSUMMON_TIMED_DESPAWN, 300000);
                creature->RemoveFlag(UNIT_NPC_FLAGS, 3);
                creature->AI()->Talk(15, player->GetGUID());
                creature->AI()->DoAction(ACTION_ADD_EVENT_CHECK_TIMER);
                return true;
            }
            case QUEST_ENTRY_GRUDGE_MATCH_H:
            {
                creature->SummonCreature(NPC_KELSEY_STEELSPARK, -7140.11f, -3786.13f, 8.97f, 5.98f, TEMPSUMMON_TIMED_DESPAWN, 300000);
                creature->RemoveFlag(UNIT_NPC_FLAGS, 3);
                creature->AI()->Talk(15, player->GetGUID());
                creature->AI()->DoAction(ACTION_ADD_EVENT_CHECK_TIMER);
                return true;
            }
            case QUEST_ENTRY_SARINEXX:
            {
                creature->SummonCreature(NPC_SARINEXX, -7140.11f, -3786.13f, 8.97f, 5.98f, TEMPSUMMON_TIMED_DESPAWN, 300000);
                creature->RemoveFlag(UNIT_NPC_FLAGS, 3);
                creature->AI()->Talk(10);
                creature->AI()->DoAction(ACTION_ADD_EVENT_CHECK_TIMER);
                return true;
            }
            case QUEST_ENTRY_THE_GINORMUS:
            {
                creature->SummonCreature(NPC_THE_GINORMUS, -7140.11f, -3786.13f, 8.97f, 5.98f, TEMPSUMMON_TIMED_DESPAWN, 300000);
                creature->RemoveFlag(UNIT_NPC_FLAGS, 3);
                creature->AI()->Talk(3);
                creature->AI()->DoAction(ACTION_ADD_EVENT_CHECK_TIMER);
                return true;
            }
            case QUEST_ENTRY_ZUMONGA:
            {
                creature->SummonCreature(NPC_ZUMONGA, -7140.11f, -3786.13f, 8.97f, 5.98f, TEMPSUMMON_TIMED_DESPAWN, 300000);
                creature->RemoveFlag(UNIT_NPC_FLAGS, 3);
                creature->AI()->Talk(7);
                creature->AI()->DoAction(ACTION_ADD_EVENT_CHECK_TIMER);
                return true;
            }
            default:
                return true;
        }
        return true;
    }

    struct npc_dr_dealwellAI : public ScriptedAI
    {
        npc_dr_dealwellAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ENCOUNTERS:
                    {
                        Creature* zumonga = me->FindNearestCreature(NPC_ZUMONGA, 200.0f, true);
                        Creature* ginormus = me->FindNearestCreature(NPC_THE_GINORMUS, 200.0f, true);
                        Creature* megs = me->FindNearestCreature(NPC_MEGS_DREADSHREDDER, 200.0f, true);
                        Creature* sarinexx = me->FindNearestCreature(NPC_SARINEXX, 200.0f, true);
                        Creature* kelsey = me->FindNearestCreature(NPC_KELSEY_STEELSPARK, 200.0f, true);
                        if (!kelsey && !sarinexx && !megs && !ginormus && !zumonga)
                        {
                            if (!me->HasFlag(UNIT_NPC_FLAGS, 3))
                                me->SetFlag(UNIT_NPC_FLAGS, 3);
                        }
                        events.RescheduleEvent(EVENT_CHECK_ENCOUNTERS, 5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ADD_EVENT_CHECK_TIMER:
                {
                    events.ScheduleEvent(EVENT_CHECK_ENCOUNTERS, 5000);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dr_dealwellAI(creature);
    }
};

class go_jang_thraze_the_protector : public GameObjectScript
{
public:
    go_jang_thraze_the_protector() : GameObjectScript("go_jang_thraze_the_protector") { }

    enum Id
    {
        NPC_ENTRY_MAZOGA            = 38968,
        QUEST_SECRETS_IN_THE_OASIS  = 25032
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_SECRETS_IN_THE_OASIS) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* mazoga = player->FindNearestCreature(NPC_ENTRY_MAZOGA, 200.0f, true);
            if (!mazoga)
                player->SummonCreature(NPC_ENTRY_MAZOGA, -7467.44f, -2880.99f, 8.69f, 0.04f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return false;
        }
        return true;
    }
};

void AddSC_tanaris()
{
    new npc_custodian_of_time();
    new npc_steward_of_time();
    new npc_OOX17();
    new spell_deploy_butcherbot();
    new npc_butcherbot();
    new npc_steamwheedle_balloon();
    new npc_steamwheedle_balloon_escort();
    new npc_balloon_throwing_station();
    new spell_emergency_rocket_pack();
    new npc_wrangled_silithid();
    new spell_throw_hyena_chunk();
    new spell_detonate_silithid();
    new go_antediluvean_chest();
    new npc_dr_dealwell();
    new go_jang_thraze_the_protector();
}
