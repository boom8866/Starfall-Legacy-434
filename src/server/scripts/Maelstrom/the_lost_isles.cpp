/*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
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

/*TODO:
1) Finish scripting on KTC Train-a-Tron Deluxe (need multiple profession training)
2) Add details in last quest (Captured Goblins that need to fall from the sky in an ice cage)
3) Add a fall with parachute function for stealth fighter pilots
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "Vehicle.h"
#include "Creature.h"
#include "PetAI.h"
#include "PassiveAI.h"
#include "CombatAI.h"
#include "Pet.h"
#include "GameObject.h"
#include "GameObjectAI.h"

/* Automatic rescheduling if creature is already casting */
#define RESCHEDULE_IF_CASTING if (me->HasUnitState(UNIT_STATE_CASTING)) { events.ScheduleEvent(eventId, 1); break; }

class npc_geargrinder_gizmo_intro : public CreatureScript
{
public:
    npc_geargrinder_gizmo_intro() : CreatureScript("npc_geargrinder_gizmo_intro") {}

    enum questId
    {
        QUEST_ENTRY_GOBLIN_ESCAPE_PODS    = 14474
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_GOBLIN_ESCAPE_PODS)
        {
            creature->MonsterSay("Yeah, there's tons of people still trapped in the escape pods, boss. Oh, wait. I guess you're not the boss anymore. Anyways, they're all probably going to drown if you don't get them out.", 0, player->GetGUID());
            return false;
        }
        return true;
    }

    struct npc_geargrinder_gizmo_introAI : public ScriptedAI
    {
        EventMap events;

        npc_geargrinder_gizmo_introAI(Creature* creature) : ScriptedAI(creature)
        {
            eventInProgress = false;
            playerSummoner = NULL;
        }

        enum npcId
        {
            NPC_ENTRY_GEARGRINDER_GIZMO     = 36600,
            NPC_ENTRY_DOC_ZAPNOZZLE         = 36608
        };

        enum questId
        {
            QUEST_ENTRY_GOBLIN_ESCAPE_PODS   = 14474
        };

        enum eventId
        {
            EVENT_CHECK_PLAYER_CINEMATIC    = 1,
            EVENT_CHECK_SUMMONER
        };

        enum actionId
        {
            ACTION_START_PRE_EVENT  = 1,
            ACTION_TALK_0
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void PreparePlayerForEvent()
        {
            if (playerSummoner && playerSummoner != NULL)
            {
                if (playerSummoner->ToPlayer())
                {
                    if (!playerSummoner->ToPlayer()->hasQuest(QUEST_ENTRY_GOBLIN_ESCAPE_PODS))
                        playerSummoner->SummonCreature(NPC_ENTRY_DOC_ZAPNOZZLE, 555.20f, 3271.99f, -0.95f, 3.12f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                }
            }
        }

        void IsSummonedBy(Unit* summoner)
        {
            summoner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            playerSummoner = summoner;
            events.ScheduleEvent(EVENT_CHECK_PLAYER_CINEMATIC, 5000);
            me->SetPhaseMask(8192, true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_PRE_EVENT:
                {
                    events.CancelEvent(EVENT_CHECK_PLAYER_CINEMATIC);
                    if (playerSummoner && playerSummoner != NULL)
                        playerSummoner->SetPhaseMask(8192, true);
                    PreparePlayerForEvent();
                    eventInProgress = true;
                    events.ScheduleEvent(EVENT_CHECK_SUMMONER, 2000);
                    break;
                }
                case ACTION_TALK_0:
                {
                    if (playerSummoner && playerSummoner != NULL)
                        Talk(0, playerSummoner->GetGUID());
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
                    case EVENT_CHECK_PLAYER_CINEMATIC:
                    {
                        if (eventInProgress == true || !playerSummoner)
                        {
                            events.ScheduleEvent(EVENT_CHECK_PLAYER_CINEMATIC, 5000);
                            return;
                        }

                        if (playerSummoner == NULL)
                            return;

                        if (!playerSummoner->ToPlayer())
                        {
                            events.ScheduleEvent(EVENT_CHECK_PLAYER_CINEMATIC, 5000);
                            return;
                        }

                        if (!(playerSummoner->ToPlayer()->GetExtraFlags() & PLAYER_EXTRA_WATCHING_MOVIE))
                            DoAction(ACTION_START_PRE_EVENT);
                        else
                            events.ScheduleEvent(EVENT_CHECK_PLAYER_CINEMATIC, 5000);
                        break;
                    }
                    case EVENT_CHECK_SUMMONER:
                    {
                        if (!playerSummoner || (playerSummoner && !playerSummoner->IsInWorld()))
                            me->DespawnOrUnsummon(1);
                        else
                            events.ScheduleEvent(EVENT_CHECK_SUMMONER, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool eventInProgress;
        Unit* playerSummoner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_geargrinder_gizmo_introAI(creature);
    }
};

class npc_doc_zapnozzle_intro : public CreatureScript
{
public:
    npc_doc_zapnozzle_intro() : CreatureScript("npc_doc_zapnozzle_intro") {}

    enum questId
    {
        QUEST_DONT_GO_INTO_THE_LIGHT   = 14239
    };

    enum spellId
    {
        SPELL_DEFIBRILLATE      = 45872,
        SPELL_FEIGN_DEATH_1     = 58951,
        SPELL_FEIGN_DEATH_2     = 79153,
        SPELL_UNIQUE_PHASING    = 60191
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_DONT_GO_INTO_THE_LIGHT:
            {
                player->SetControlled(false, UNIT_STATE_ROOT);
                player->SetStandState(UNIT_STAND_STATE_STAND);
                player->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
                player->SetPhaseMask(2, true);
                break;
            }
            default:
                break;
        }
        return true;
    }

    struct npc_doc_zapnozzle_introAI : public ScriptedAI
    {
        EventMap events;

        npc_doc_zapnozzle_introAI(Creature* creature) : ScriptedAI(creature)
        {
            enableAI = false;
            playerSummoner = NULL;
        }

        enum npcId
        {
            NPC_ENTRY_GEARGRINDER_GIZMO     = 36600,
            NPC_ENTRY_DOC_ZAPNOZZLE         = 36608
        };

        enum actionId
        {
            ACTION_MOVE_TO_PLAYER   = 1,
            ACTION_ENABLE_AI
        };

        enum eventId
        {
            EVENT_START_TALK        = 1,
            EVENT_CHECK_SUMMONER
        };

        enum pointId
        {
            POINT_TO_PLAYER     = 1,
            POINT_AFTER_JUMP
        };

        class enableGizmo : public BasicEvent
        {
            public:
                explicit enableGizmo(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Creature* gizmo = creature->FindNearestCreature(NPC_ENTRY_GEARGRINDER_GIZMO, 20.0f, true))
                    gizmo->AI()->DoAction(2);
                return true;
            }

        private:
            Creature* creature;
        };

        class enableQuestGiver : public BasicEvent
        {
            public:
                explicit enableQuestGiver(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* summoner)
        {
            summoner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            playerSummoner = summoner;
            me->SetPhaseMask(8192, true);
            DoAction(ACTION_MOVE_TO_PLAYER);
            eventCompleted = false;
            events.ScheduleEvent(EVENT_CHECK_SUMMONER, 2000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_TO_PLAYER:
                {
                    me->GetMotionMaster()->MovePoint(POINT_TO_PLAYER, 539.42f, 3272.23f, -0.95f, true);
                    break;
                }
                case ACTION_ENABLE_AI:
                {
                    enableAI = true;
                    events.ScheduleEvent(EVENT_START_TALK, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_PLAYER:
                {
                    me->GetMotionMaster()->MoveJump(537.44f, 3272.09f, 0.18f, 7.0f, 7.0f, POINT_AFTER_JUMP);
                    break;
                }
                case POINT_AFTER_JUMP:
                {
                    DoAction(ACTION_ENABLE_AI);
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
                    case EVENT_START_TALK:
                    {
                        if (me->GetPhaseMask() != 8192)
                        {
                            events.CancelEvent(EVENT_START_TALK);
                            return;
                        }

                        if (playerSummoner && playerSummoner != NULL && eventCompleted == false)
                        {
                            TalkWithDelay(500, 0, playerSummoner->GetGUID());
                            TalkWithDelay(8000, 1, playerSummoner->GetGUID());
                            me->m_Events.AddEvent(new enableGizmo(me), (me)->m_Events.CalculateTime(15000));
                            TalkWithDelay(21000, 2, playerSummoner->GetGUID());
                            me->CastWithDelay(28000, playerSummoner, SPELL_DEFIBRILLATE);
                            TalkWithDelay(36000, 3, playerSummoner->GetGUID());
                            me->CastWithDelay(41000, playerSummoner, SPELL_DEFIBRILLATE);
                            TalkWithDelay(48000, 4, playerSummoner->GetGUID());
                            me->m_Events.AddEvent(new enableQuestGiver(me), (me)->m_Events.CalculateTime(54000));
                            events.CancelEvent(EVENT_START_TALK);
                            eventCompleted = true;
                        }
                        break;
                    }
                    case EVENT_CHECK_SUMMONER:
                    {
                        if (!playerSummoner || (playerSummoner && !playerSummoner->IsInWorld()))
                            me->DespawnOrUnsummon(1);
                        else
                            events.ScheduleEvent(EVENT_CHECK_SUMMONER, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool enableAI;
        bool eventCompleted;
        Unit* playerSummoner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_doc_zapnozzle_introAI(creature);
    }
};

class go_goblin_escape_pod : public GameObjectScript
{
public:
    go_goblin_escape_pod() : GameObjectScript("go_goblin_escape_pod") { }

    enum questId
    {
        QUEST_ENTRY_GOBLIN_ESCAPE_PODS  = 14474
    };

    enum spellId
    {
        SPELL_GOBLIN_SURVIVOR_SUCCESS   = 66137,
        SPELL_GOBLIN_SURVIVOR_FAILED    = 66138
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_GOBLIN_ESCAPE_PODS) == QUEST_STATUS_INCOMPLETE)
        {
            if (roll_chance_f(50))
                player->CastWithDelay(500, player, SPELL_GOBLIN_SURVIVOR_SUCCESS, true);
            else
                player->CastWithDelay(500, player, SPELL_GOBLIN_SURVIVOR_FAILED, true);
            return false;
        }
        return true;
    }
};

class npc_bomb_throwing_monkey : public CreatureScript
{
public:
    npc_bomb_throwing_monkey() : CreatureScript("npc_bomb_throwing_monkey") {}

    struct npc_bomb_throwing_monkeyAI : public ScriptedAI
    {
        npc_bomb_throwing_monkeyAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum actionId
        {
            ACTION_MOVE_JUMP_UP     = 1,
            ACTION_FALL_ON_GROUND,
            ACTION_DIE_ON_GROUND
        };

        enum pointId
        {
            POINT_TO_AIR        = 1,
            POINT_TO_GROUND
        };

        enum eventId
        {
            EVENT_CAST_MONKEY_BOMB  = 1,
            EVENT_MOVE_FALL,
            EVENT_DIE_AFTER_FALL
        };

        enum spellId
        {
            SPELL_MONKEY_BOMB               = 8858,
            SPELL_NITRO_POTASSIUM_BANANAS   = 67917,
            SPELL_EXPLODING_BANANAS         = 67919
        };

        enum questCredit
        {
            QUEST_CREDIT_MONKEY_BOMBED  = 35760
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_NITRO_POTASSIUM_BANANAS:
                {
                    DoCast(me, SPELL_EXPLODING_BANANAS);
                    if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                        caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_MONKEY_BOMBED);
                    break;
                }
                case SPELL_EXPLODING_BANANAS:
                {
                    DoAction(ACTION_MOVE_JUMP_UP);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CAST_MONKEY_BOMB, urand(3500, 5000));
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_JUMP_UP:
                {
                    groundZ = me->GetPositionZ();
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+75.0f, 25.0f, 25.0f, POINT_TO_AIR);
                    events.CancelEvent(EVENT_CAST_MONKEY_BOMB);
                    events.ScheduleEvent(EVENT_MOVE_FALL, 3500);
                    break;
                }
                case ACTION_FALL_ON_GROUND:
                {
                    me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), groundZ, 25.0f, 25.0f, POINT_TO_GROUND);
                    events.ScheduleEvent(EVENT_DIE_AFTER_FALL, 3000);
                    break;
                }
                case ACTION_DIE_ON_GROUND:
                {
                    me->Kill(me, false);
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
                    case EVENT_CAST_MONKEY_BOMB:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_MONKEY_BOMB);
                        events.RescheduleEvent(EVENT_CAST_MONKEY_BOMB, urand(3500, 5000));
                        break;
                    }
                    case EVENT_MOVE_FALL:
                    {
                        DoAction(ACTION_FALL_ON_GROUND);
                        break;
                    }
                    case EVENT_DIE_AFTER_FALL:
                    {
                        DoAction(ACTION_DIE_ON_GROUND);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        float groundZ;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bomb_throwing_monkeyAI(creature);
    }
};

class spell_ktc_snapflash : public SpellScriptLoader
{
    public:
        spell_ktc_snapflash() : SpellScriptLoader("spell_ktc_snapflash") { }

        class spell_ktc_snapflash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ktc_snapflash_SpellScript);

            enum npcId
            {
                NPC_ENTRY_BUNNY_1   = 37872,
                NPC_ENTRY_BUNNY_2   = 37895,
                NPC_ENTRY_BUNNY_3   = 37896,
                NPC_ENTRY_BUNNY_4   = 37897
            };

            enum spellId
            {
                SPELL_CAMERA_BIND_SIGHT     = 70641,
                SPELL_CAMERA_SCREEN_EFFECT  = 70649
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        Creature* firstBunny = caster->FindNearestCreature(NPC_ENTRY_BUNNY_1, 15.0f, true);
                        Creature* secondBunny = caster->FindNearestCreature(NPC_ENTRY_BUNNY_2, 15.0f, true);
                        Creature* thirdBunny = caster->FindNearestCreature(NPC_ENTRY_BUNNY_3, 15.0f, true);
                        Creature* fourthBunny = caster->FindNearestCreature(NPC_ENTRY_BUNNY_4, 15.0f, true);
                        if (firstBunny)
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_BUNNY_1);
                            firstBunny->CastWithDelay(1000, firstBunny, SPELL_CAMERA_BIND_SIGHT, true);
                            caster->RemoveAurasDueToSpell(70661);
                            return SPELL_CAST_OK;
                        }
                        else if (secondBunny)
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_BUNNY_2);
                            caster->CastWithDelay(1000, firstBunny, SPELL_CAMERA_BIND_SIGHT, true);
                            caster->RemoveAurasDueToSpell(70678);
                            return SPELL_CAST_OK;
                        }
                        else if (thirdBunny)
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_BUNNY_3);
                            thirdBunny->CastWithDelay(1000, firstBunny, SPELL_CAMERA_BIND_SIGHT, true);
                            caster->RemoveAurasDueToSpell(70680);
                            return SPELL_CAST_OK;
                        }
                        else if (fourthBunny)
                        {
                            caster->ToPlayer()->KilledMonsterCredit(NPC_ENTRY_BUNNY_4);
                            fourthBunny->CastWithDelay(1000, firstBunny, SPELL_CAMERA_BIND_SIGHT, true);
                            caster->RemoveAurasDueToSpell(70681);
                            return SPELL_CAST_OK;
                        }
                        else
                            SPELL_FAILED_OUT_OF_RANGE;
                    }
                }
                return SPELL_FAILED_OUT_OF_RANGE;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_ktc_snapflash_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ktc_snapflash_SpellScript();
        }
};

class npc_kilag_gorefang : public CreatureScript
{
public:
    npc_kilag_gorefang() : CreatureScript("npc_kilag_gorefang") { }

    #define GOSSIP_TEXT_ORC "Kilag, I... uh, somhow... er, lost my scout."

    enum questId
    {
        QUEST_ENTRY_INFRARED_INFRADEAD  = 14238,
        QUEST_ENTRY_TO_THE_CLIFFS       = 14240
    };

    enum spellId
    {
        SPELL_SUMMON_ORC_SCOUT  = 68344,
        SPELL_ORC_SCOUT_AURA    = 68338,
        SPELL_TO_THE_CLIFFS     = 68973
    };

    enum npcId
    {
        NPC_ENTRY_ORC_SCOUT     = 36100
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_INFRARED_INFRADEAD && !player->HasAura(SPELL_ORC_SCOUT_AURA))
        {
            creature->AI()->TalkWithDelay(5000, 0, player->GetGUID());
            creature->AI()->Talk(1, player->GetGUID());
            player->CastSpell(player, SPELL_SUMMON_ORC_SCOUT, true);
            return false;
        }

        if (quest->GetQuestId() == QUEST_ENTRY_TO_THE_CLIFFS)
        {
            player->CastSpell(player, SPELL_TO_THE_CLIFFS, true);
            return false;
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (!player->HasAura(SPELL_ORC_SCOUT_AURA))
            {
                player->CastSpell(player, SPELL_SUMMON_ORC_SCOUT, true);
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_INFRARED_INFRADEAD) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ORC, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_INFRARED_INFRADEAD)
        {
            std::list<Unit*> targets;
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(player, player, 200.0f);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(player, targets, u_check);
            player->VisitNearbyObject(200.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == player))
                {
                    if ((*itr)->ToTempSummon()->GetEntry() == 36100)
                        (*itr)->ToTempSummon()->DespawnOrUnsummon(1);
                }
            }
            player->RemoveAurasDueToSpell(SPELL_ORC_SCOUT_AURA);
            return true;
        }
        return false;
    }
};

class npc_thrall_ship_1 : public CreatureScript
{
public:
    npc_thrall_ship_1() : CreatureScript("npc_thrall_ship_1") { }

    enum goId
    {
        GO_ENTRY_ARCANE_CAGE    = 195704
    };

    enum questId
    {
        QUEST_ENTRY_PRECIOUS_CARGO  = 14242
    };

    enum creditId
    {
        QUEST_CREDIT_PRECIOUS_CARGO     = 36145
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_PRECIOUS_CARGO) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(QUEST_CREDIT_PRECIOUS_CARGO);
            if (GameObject* arcaneCage = player->FindNearestGameObject(GO_ENTRY_ARCANE_CAGE, 20.0f))
                arcaneCage->SetGoState(GO_STATE_ACTIVE);
            return true;
        }

        return false;
    }
};

class npc_thrall_lightning_trigger : public CreatureScript
{
public:
    npc_thrall_lightning_trigger() : CreatureScript("npc_thrall_lightning_trigger") {}

    struct npc_thrall_lightning_triggerAI : public ScriptedAI
    {
        npc_thrall_lightning_triggerAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum spellId
        {
            SPELL_THRALL_LIGHTNING_COSMETIC     = 74425
        };

        enum npcId
        {
            NPC_ENTRY_THRALL    = 36161
        };

        enum eventId
        {
            EVENT_ENABLE_THRALL_LIGHTNING   = 1
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_ENABLE_THRALL_LIGHTNING, urand(2000, 8000));
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENABLE_THRALL_LIGHTNING:
                    {
                        RESCHEDULE_IF_CASTING
                        if (Creature* thrall = me->FindNearestCreature(NPC_ENTRY_THRALL, 70.0f, true))
                        {
                            thrall->AI()->DoCast(me, SPELL_THRALL_LIGHTNING_COSMETIC);
                            events.RescheduleEvent(EVENT_ENABLE_THRALL_LIGHTNING, urand(2000, 8000));
                        }
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
        return new npc_thrall_lightning_triggerAI(creature);
    }
};

class npc_cyclone_of_the_elements : public CreatureScript
{
public:
    npc_cyclone_of_the_elements() : CreatureScript("npc_cyclone_of_the_elements") { }

    enum questId
    {
        QUEST_ENTRY_WARCHIEF_REVENGE    = 14243
    };

    enum actionId
    {
        ACTION_WP_START     = 1
    };

    enum eventId
    {
        EVENT_CHECK_QUEST_COMPLETE  = 1
    };

    enum spellId
    {
        SPELL_ENTRY_RIDE_CYCLONE    = 68436
    };

    struct npc_cyclone_of_the_elementsAI : public npc_escortAI
    {
        npc_cyclone_of_the_elementsAI(Creature* creature) : npc_escortAI(creature) {questComplete = false;}

        EventMap events;

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            questComplete = false;
            events.ScheduleEvent(EVENT_CHECK_QUEST_COMPLETE, 3000);
            DoAction(ACTION_WP_START);
        }

        void EnterCombat(Unit* /*who*/) {}

        void EnterEvadeMode() {}

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 12:    // Final Circle WP
                {
                    if (questComplete == false)
                        SetNextWaypoint(1, true);
                    break;
                }
                case 13:    // Return WP
                {
                    me->SetSpeed(MOVE_RUN, 4.5f, true);
                    me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
                    break;
                }
                case 18:    // Finished
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                        owner->SetPhaseMask(393, true);
                    me->RemoveAurasDueToSpell(SPELL_ENTRY_RIDE_CYCLONE);
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
                    Start(true, true, NULL, NULL, false, true);
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
                    case EVENT_CHECK_QUEST_COMPLETE:
                    {
                        if (Unit* owner = me->GetCharmerOrOwner())
                        {
                            if (owner->GetTypeId() == TYPEID_PLAYER)
                            {
                                if (owner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_WARCHIEF_REVENGE) == QUEST_STATUS_COMPLETE)
                                {
                                    events.CancelEvent(EVENT_CHECK_QUEST_COMPLETE);
                                    questComplete = true;
                                }
                                else
                                    events.RescheduleEvent(EVENT_CHECK_QUEST_COMPLETE, 3000);
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool questComplete;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cyclone_of_the_elementsAI (creature);
    }
};

class npc_sassy_rocket : public CreatureScript
{
public:
    npc_sassy_rocket() : CreatureScript("npc_sassy_rocket") { }

    enum questId
    {
        QUEST_ENTRY_UP_UP_AND_AWAY   = 14244
    };

    enum spellId
    {
        SPELL_SUMMON_TRADEPRINCE    = 68815,
        SPELL_UNIQUE_PHASING        = 60191
    };

    enum npcId
    {
        NPC_ENTRY_ORC_SCOUT     = 36100
    };

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_UP_UP_AND_AWAY && !player->HasAura(SPELL_UNIQUE_PHASING))
        {
            player->CastSpell(player, SPELL_SUMMON_TRADEPRINCE, true);
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            return false;
        }
        return true;
    }
};

class npc_sling_rocket_tradeprince : public CreatureScript
{
public:
    npc_sling_rocket_tradeprince() : CreatureScript("npc_sling_rocket_tradeprince") {}

    struct npc_sling_rocket_tradeprinceAI : public ScriptedAI
    {
        npc_sling_rocket_tradeprinceAI(Creature* creature) : ScriptedAI(creature) { }

        enum actionId
        {
            ACTION_MOVE_START    = 1
        };

        enum pointId
        {
            POINT_TO_AIR        = 1
        };

        void OnCharmed(bool /*apply*/) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            DoAction(ACTION_MOVE_START);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_START:
                {
                    me->GetMotionMaster()->MoveJump(961.25f, 2408.24f, 297.73f, 16.5f, 50.0f, POINT_TO_AIR);
                    me->DespawnOrUnsummon(10000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sling_rocket_tradeprinceAI(creature);
    }
};

class npc_sling_rocket_player : public CreatureScript
{
public:
    npc_sling_rocket_player() : CreatureScript("npc_sling_rocket_player") {}

    struct npc_sling_rocket_playerAI : public ScriptedAI
    {
        npc_sling_rocket_playerAI(Creature* creature) : ScriptedAI(creature) { }

        enum actionId
        {
            ACTION_MOVE_START    = 1
        };

        enum pointId
        {
            POINT_TO_AIR        = 1
        };

        enum spellId
        {
            SPELL_IMPACT_EXPLOSION      = 66127,
            SPELL_RIDE_SLING_ROCKET     = 68805,
            SPELL_UNIQUE_PHASING        = 60191
        };

        void OnCharmed(bool /*apply*/) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            DoAction(ACTION_MOVE_START);
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (!apply)
                passenger->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_START:
                {
                    me->GetMotionMaster()->MoveJump(930.70f, 2384.25f, 7.57f, 30.0f, 55.0f, POINT_TO_AIR);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_AIR:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        owner->CastSpell(owner, SPELL_IMPACT_EXPLOSION, true);
                        me->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
                        me->RemoveAurasDueToSpell(SPELL_RIDE_SLING_ROCKET);
                        owner->NearTeleportTo(930.70f, 2384.25f, 7.57f, 4.90f);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sling_rocket_playerAI(creature);
    }
};

class spell_remote_control_fireworks : public SpellScriptLoader
{
    public:
        spell_remote_control_fireworks() : SpellScriptLoader("spell_remote_control_fireworks") { }

        class spell_remote_control_fireworks_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_remote_control_fireworks_SpellScript);

            enum Id
            {
                SPELL_REMOTE_CONTROL_VISUAL     = 74177,
                NPC_ENTRY_WILD_CLUCKER          = 38111,
                QUEST_CREDIT_CLUCKER            = 38117
            };

            class startAction : public BasicEvent
            {
                public:
                    explicit startAction(Creature* creature) : creature(creature) {}

                bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
                {
                    creature->AI()->DoAction(1);
                    return true;
                }

                private:
                    Creature* creature;
            };

            void HandleAddRocket()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* chicken = caster->FindNearestCreature(NPC_ENTRY_WILD_CLUCKER, 5.0f, true))
                    {
                        if (!chicken->HasAura(SPELL_REMOTE_CONTROL_VISUAL))
                        {
                            chicken->AddAura(SPELL_REMOTE_CONTROL_VISUAL, chicken);
                            chicken->m_Events.AddEvent(new startAction(chicken), chicken->m_Events.CalculateTime(2000));
                            if (caster->GetTypeId() == TYPEID_PLAYER)
                                caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_CLUCKER);
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_remote_control_fireworks_SpellScript::HandleAddRocket);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_remote_control_fireworks_SpellScript();
        }
};

class npc_wild_clucker : public CreatureScript
{
public:
    npc_wild_clucker() : CreatureScript("npc_wild_clucker") {}

    struct npc_wild_cluckerAI : public ScriptedAI
    {
        npc_wild_cluckerAI(Creature* creature) : ScriptedAI(creature) { }

        enum actionId
        {
            ACTION_MOVE_START   = 1
        };

        enum pointId
        {
            POINT_TO_HOME   = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_START:
                {
                    me->SetCanFly(true);
                    me->GetMotionMaster()->MoveJump(905.27f, 2334.23f, 4.87f, 7.0f, 15.5f, POINT_TO_HOME);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_HOME:
                {
                    me->DespawnOrUnsummon(1000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wild_cluckerAI(creature);
    }
};

class npc_wild_clucker_egg : public CreatureScript
{
public:
    npc_wild_clucker_egg() : CreatureScript("npc_wild_clucker_egg") {}

    struct npc_wild_clucker_eggAI : public ScriptedAI
    {
        npc_wild_clucker_eggAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum actionId
        {
            ACTION_LURE_RAPTOR  = 1,
            ACTION_DESPAWN
        };

        enum spellId
        {
            SPELL_ENTRY_EGG_VISUAL  = 71355
        };

        enum npcId
        {
            NPC_ENTRY_SPINY_RAPTOR  = 38187
        };

        enum eventId
        {
            EVENT_CHECK_RAPTOR  = 1
        };

        enum pointId
        {
            POINT_TRAP_ZONE     = 1
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.ScheduleEvent(EVENT_CHECK_RAPTOR, 3500);
            raptorLured = false;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_LURE_RAPTOR:
                {
                    if (Creature* spinyRaptor = me->FindNearestCreature(NPC_ENTRY_SPINY_RAPTOR, 80.0f, true))
                    {
                        if (spinyRaptor->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC))
                        {
                            events.RescheduleEvent(EVENT_CHECK_RAPTOR, 2000);
                            return;
                        }

                        spinyRaptor->AI()->DoAction(1);
                        spinyRaptor->GetMotionMaster()->MovePoint(POINT_TRAP_ZONE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), true);
                        events.CancelEvent(EVENT_CHECK_RAPTOR);
                        raptorLured = true;
                    }
                    else
                        events.RescheduleEvent(EVENT_CHECK_RAPTOR, 2000);
                    break;
                }
                case ACTION_DESPAWN:
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
            if (raptorLured == true)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_RAPTOR:
                    {
                        DoAction(ACTION_LURE_RAPTOR);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool raptorLured;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wild_clucker_eggAI(creature);
    }
};

class npc_spiny_raptor : public CreatureScript
{
public:
    npc_spiny_raptor() : CreatureScript("npc_spiny_raptor") {}

    struct npc_spiny_raptorAI : public ScriptedAI
    {
        npc_spiny_raptorAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum actionId
        {
            ACTION_MOVE_TO_TRAP     = 1
        };

        enum eventId
        {
            EVENT_CAST_HEAD_BUTT    = 1
        };

        enum spellId
        {
            SPELL_ENTRY_HEAD_BUTT   = 42320,
            SPELL_SUMMON_GIANT_EGG  = 66726
        };

        enum pointId
        {
            POINT_TRAP_ZONE     = 1
        };

        enum Id
        {
            NPC_ENTRY_EGG_TRAP  = 38195,
            GO_ENTRY_TRAP       = 201972
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_TO_TRAP:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC);
                    me->SetWalk(false);
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CAST_HEAD_BUTT, urand(5000, 8000));
        }

        void EnterEvadeMode()
        {
            events.CancelEvent(EVENT_CAST_HEAD_BUTT);
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
                    case EVENT_CAST_HEAD_BUTT:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_ENTRY_HEAD_BUTT);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TRAP_ZONE:
                {
                    me->setFaction(35);
                    me->CastSpell(me, SPELL_SUMMON_GIANT_EGG, true);
                    if (Creature* eggTrap = me->FindNearestCreature(NPC_ENTRY_EGG_TRAP, 5.0f, true))
                        eggTrap->AI()->DoAction(2);
                    me->Kill(me, false);
                    me->setFaction(14);
                    me->DespawnOrUnsummon(3000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_spiny_raptorAI(creature);
    }
};

class spell_wild_clucker_eggs : public SpellScriptLoader
{
    public:
        spell_wild_clucker_eggs() : SpellScriptLoader("spell_wild_clucker_eggs") { }

        class spell_wild_clucker_eggs_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_wild_clucker_eggs_SpellScript);

            enum goId
            {
                GO_ENTRY_EGG_TRAP   = 201972
            };

            SpellCastResult CheckTrapActive()
            {
                if (Unit* caster = GetCaster())
                {
                    if (GameObject* trap = caster->FindNearestGameObject(GO_ENTRY_EGG_TRAP, 5.0f))
                    {
                        if (trap->GetGoState() == GO_STATE_ACTIVE)
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        else
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_wild_clucker_eggs_SpellScript::CheckTrapActive);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_wild_clucker_eggs_SpellScript();
        }
};

class npc_ace_event_soe : public CreatureScript
{
public:
    npc_ace_event_soe() : CreatureScript("npc_ace_event_soe") { }

    enum actionId
    {
        ACTION_WP_START         = 1,
        ACTION_SUMMON_FACELESS,
        ACTION_RUN_AWAY
    };

    enum eventId
    {
        EVENT_START_WP_AFTER_TALK   = 1,
        EVENT_SUMMON_FACELESS,
        EVENT_RUN_AWAY
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING        = 60191,
        SPELL_GOBLIN_BANNER_AURA    = 72077,
        SPELL_NAGA_HATCHLINGS       = 72073
    };

    enum npcId
    {
        NPC_ENTRY_FACELESS_OF_THE_DEEP  = 38448
    };

    struct npc_ace_event_soeAI : public npc_escortAI
    {
        npc_ace_event_soeAI(Creature* creature) : npc_escortAI(creature) {eventInProgress = false;}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            // Event in progress! Despawn
            if (owner->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED|UNIT_FLAG_NON_ATTACKABLE))
                me->DespawnOrUnsummon(1);

            eventInProgress = true;
            events.ScheduleEvent(EVENT_START_WP_AFTER_TALK, 15000);
            owner->AddAura(SPELL_UNIQUE_PHASING, owner);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED|UNIT_FLAG_NON_ATTACKABLE);
            TalkWithDelay(1000, 0, owner->GetGUID());
            TalkWithDelay(7000, 1, owner->GetGUID());
        }

        void EnterCombat(Unit* /*who*/) {}

        void EnterEvadeMode() {}

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 7: // First yell
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                        Talk(2, owner->GetGUID());
                    break;
                }
                case 8: // Point before Faceless
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        Talk(3, owner->GetGUID());
                        TalkWithDelay(8000, 4, owner->GetGUID());
                        TalkWithDelay(16000, 5, owner->GetGUID());
                        TalkWithDelay(24000, 6, owner->GetGUID());
                        events.ScheduleEvent(EVENT_SUMMON_FACELESS, 31000);
                    }
                    SetEscortPaused(true);
                    break;
                }
                case 9:
                {
                    // Despawn on last WP
                    me->DespawnOrUnsummon(1);
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
                    DoCast(me, SPELL_GOBLIN_BANNER_AURA, true);
                    for (uint8 nagaSummoned = 0; nagaSummoned < 8; nagaSummoned++)
                        DoCast(me, SPELL_NAGA_HATCHLINGS, true);
                    Start(false, true, NULL, NULL, false, true);
                    break;
                }
                case ACTION_SUMMON_FACELESS:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                        owner->SummonCreature(NPC_ENTRY_FACELESS_OF_THE_DEEP, 132.346f, 1938.53f, -2.43f, 6.24f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    break;
                }
                case ACTION_RUN_AWAY:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                        Talk(7, owner->GetGUID());
                    events.ScheduleEvent(EVENT_RUN_AWAY, 4000);
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
                    case EVENT_START_WP_AFTER_TALK:
                    {
                        DoAction(ACTION_WP_START);
                        events.CancelEvent(EVENT_START_WP_AFTER_TALK);
                        break;
                    }
                    case EVENT_SUMMON_FACELESS:
                    {
                        DoAction(ACTION_SUMMON_FACELESS);
                        events.CancelEvent(EVENT_SUMMON_FACELESS);
                        break;
                    }
                    case EVENT_RUN_AWAY:
                    {
                        SetEscortPaused(false);
                        events.CancelEvent(EVENT_RUN_AWAY);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool eventInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ace_event_soeAI (creature);
    }
};

class npc_faceless_soe : public CreatureScript
{
public:
    npc_faceless_soe() : CreatureScript("npc_faceless_soe") {}

    struct npc_faceless_soeAI : public ScriptedAI
    {
        npc_faceless_soeAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_ENTER_COMBAT     = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_BEAM_EFFECT       = 72076,
            SPELL_ABSORPTION_SHIELD = 72055,
            SPELL_SHADOW_CRASH      = 75902,
            SPELL_SHADOW_CRASH_EFF  = 75903,
            SPELL_FREEZE_ANIM       = 72126
        };

        enum npcId
        {
            NPC_ENTRY_ACE   = 38455
        };

        enum eventId
        {
            EVENT_SCARE_ACE     = 1,
            EVENT_BEAM_EFFECT,
            EVENT_SHADOW_CRASH,
            EVENT_TALK_FINAL,
            EVENT_ENTER_COMBAT
        };

        enum pointId
        {
            POINT_TOP_OF_THE_VOID   = 1
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_CRASH, 500);
        }

        void CleanupOwner()
        {
            if (playerOwner && playerOwner != NULL)
            {
                playerOwner->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
                playerOwner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED|UNIT_FLAG_NON_ATTACKABLE);
            }
        }

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon(1000);
            CleanupOwner();
        }

        void JustDied(Unit* /*who*/)
        {
            CleanupOwner();
        }

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(true);
            me->SetDisableGravity(true);
            playerOwner = owner;
            playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->AddAura(SPELL_ABSORPTION_SHIELD, me);
            events.ScheduleEvent(EVENT_BEAM_EFFECT, 100);
            me->GetMotionMaster()->MoveJump(132.34f, 1938.53f, 15.34f, 1.0f, 1.0f, POINT_TOP_OF_THE_VOID);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENTER_COMBAT:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                    if (playerOwner && playerOwner != NULL)
                    {
                        me->SetDisableGravity(false);
                        me->SetWalk(false);
                        playerOwner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED|UNIT_FLAG_NON_ATTACKABLE);
                        DoCast(playerOwner, SPELL_SHADOW_CRASH_EFF, true);
                        me->GetMotionMaster()->MoveJump(playerOwner->GetPositionX(), playerOwner->GetPositionY(), playerOwner->GetPositionZ(), 16.0f, 16.0f, 2);
                        AttackStart(playerOwner);
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
                case POINT_TOP_OF_THE_VOID:
                {
                    if (playerOwner && playerOwner != NULL)
                    {
                        Talk(0, playerOwner->GetGUID());
                        TalkWithDelay(6000, 1, playerOwner->GetGUID());
                        TalkWithDelay(14000, 2, playerOwner->GetGUID());
                        me->RemoveAurasDueToSpell(SPELL_FREEZE_ANIM);
                        events.ScheduleEvent(EVENT_SCARE_ACE, 21000);
                        events.CancelEvent(EVENT_BEAM_EFFECT);
                    }
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
                    case EVENT_BEAM_EFFECT:
                    {
                        DoCast(me, SPELL_BEAM_EFFECT, true);
                        events.ScheduleEvent(EVENT_BEAM_EFFECT, 500);
                        break;
                    }
                    case EVENT_SCARE_ACE:
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            if (Creature* ace = playerOwner->FindNearestCreature(NPC_ENTRY_ACE, 80.0f, true))
                                ace->AI()->DoAction(3);
                        }
                        events.CancelEvent(EVENT_SCARE_ACE);
                        events.ScheduleEvent(EVENT_TALK_FINAL, 7000);
                        break;
                    }
                    case EVENT_TALK_FINAL:
                    {
                        if (playerOwner && playerOwner != NULL)
                            Talk(3, playerOwner->GetGUID());
                        events.CancelEvent(EVENT_TALK_FINAL);
                        events.ScheduleEvent(EVENT_ENTER_COMBAT, 4000);
                        break;
                    }
                    case EVENT_ENTER_COMBAT:
                    {
                        DoAction(ACTION_ENTER_COMBAT);
                        events.CancelEvent(EVENT_ENTER_COMBAT);
                        break;
                    }
                    case EVENT_SHADOW_CRASH:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (playerOwner && playerOwner != NULL)
                            DoCast(playerOwner, SPELL_SHADOW_CRASH_EFF, true);
                        events.RescheduleEvent(EVENT_SHADOW_CRASH, urand(2000, 3500));
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        protected:
            Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_faceless_soeAI(creature);
    }
};

class spell_super_booster_rocket_boots : public SpellScriptLoader
{
    public:
        spell_super_booster_rocket_boots() : SpellScriptLoader("spell_super_booster_rocket_boots") { }

        class spell_super_booster_rocket_boots_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_super_booster_rocket_boots_SpellScript);

            enum Id
            {
                SPELL_SUMMON_ROCKET_BOOTS   = 72889,
                SPELL_MOUNTED_ROCKET_BOOTS  = 72887,
                SPELL_ROCKET_FIRE_TRIGGERED = 72885
            };

            void HandleFire()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_MOUNTED_ROCKET_BOOTS))
                    {
                        caster->RemoveAurasDueToSpell(SPELL_MOUNTED_ROCKET_BOOTS);
                        caster->RemoveAurasDueToSpell(SPELL_ROCKET_FIRE_TRIGGERED);
                        if (caster->GetVehicleBase())
                        {
                            caster->RemoveAurasDueToSpell(SPELL_ROCKET_FIRE_TRIGGERED);
                            caster->ExitVehicle();
                        }
                    }
                    else
                    {
                        caster->CastSpell(caster, SPELL_SUMMON_ROCKET_BOOTS);
                        caster->CastSpell(caster, SPELL_ROCKET_FIRE_TRIGGERED);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_super_booster_rocket_boots_SpellScript::HandleFire);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_super_booster_rocket_boots_SpellScript();
        }
};

class spell_rockin_powder_infused_boots : public SpellScriptLoader
{
    public:
        spell_rockin_powder_infused_boots() : SpellScriptLoader("spell_rockin_powder_infused_boots") { }

        class spell_rockin_powder_infused_boots_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rockin_powder_infused_boots_SpellScript);

            enum npcId
            {
                NPC_ENTRY_COACH_CROSSCHECK  = 38738,
                GUID_COACH_CROSSCHECK       = 832539
            };

            enum spellId
            {
                SPELL_ROCKIN_POWDER_INFUSED = 72971
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->HasAura(SPELL_ROCKIN_POWDER_INFUSED))
                            return SPELL_FAILED_DONT_REPORT;

                        if (Creature* coachCrosscheck = caster->FindNearestCreature(NPC_ENTRY_COACH_CROSSCHECK, 5.0f, true))
                        {
                            if (coachCrosscheck->GetGUIDLow() == GUID_COACH_CROSSCHECK)
                                return SPELL_CAST_OK;
                            else
                                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleDebuff()
            {
                if (Unit* caster = GetCaster())
                    caster->AddAura(SPELL_ROCKIN_POWDER_INFUSED, caster);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_rockin_powder_infused_boots_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_rockin_powder_infused_boots_SpellScript::HandleDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rockin_powder_infused_boots_SpellScript();
        }
};

class npc_flight_bomber_volcano_escape : public CreatureScript
{
public:
    npc_flight_bomber_volcano_escape() : CreatureScript("npc_flight_bomber_volcano_escape") { }

    enum questId
    {
        QUEST_ENTRY_OLD_FRIENDS     = 25023
    };

    enum actionId
    {
        ACTION_WP_START     = 1
    };

    enum eventId
    {
        EVENT_BOMBING_TRIGGER   = 1,
        EVENT_TALK_SASSY,
        EVENT_PLAYER_SWITCH_SEAT
    };

    enum spellId
    {
        SPELL_ENTRY_RIDE_BOMBER = 63314,
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_BOMBER_SMOKING    = 73192,
        SPELL_BOMBER_FIRE       = 73191,
        SPELL_BOMBER_SPEEDUP    = 73203,
        SPELL_BOMBING_TRIGGER   = 73127,
        SPELL_BOMBER_LADDER     = 73149,
        SPELL_BOMBER_RIDE_0     = 73137,
        SPELL_VOLCANIC_SKYBOX   = 90418
    };

    enum npcId
    {
        NPC_ENTRY_SASSY     = 38928
    };

    struct npc_flight_bomber_volcano_escapeAI : public npc_escortAI
    {
        npc_flight_bomber_volcano_escapeAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            DoAction(ACTION_WP_START);
            playerOwner = owner;
            me->SetWalk(false);
        }

        void EnterCombat(Unit* /*who*/) {}

        void EnterEvadeMode() {}

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:     // Speed to Bomber
                {
                    me->CastSpell(me, SPELL_BOMBER_SPEEDUP, true);
                    me->SetSpeed(MOVE_RUN, 4.0f, true);
                    me->SetSpeed(MOVE_WALK, 4.0f, true);
                    me->SetSpeed(MOVE_FLIGHT, 4.0f, true);
                    break;
                }
                case 2:     // On Fire!
                {
                    me->AddAura(SPELL_BOMBER_SMOKING, me);
                    me->AddAura(SPELL_BOMBER_FIRE, me);
                    events.ScheduleEvent(EVENT_BOMBING_TRIGGER, 100);
                    if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 5.0f, true))
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            sassy->AI()->TalkWithDelay(1000, 1, playerOwner->GetGUID());
                            sassy->AI()->TalkWithDelay(4000, 2, playerOwner->GetGUID());
                        }
                    }
                    break;
                }
                case 7:     // Add Volcanic Skybox
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                        me->AddAura(SPELL_VOLCANIC_SKYBOX, owner);
                    break;
                }
                case 9:    // Yeah!
                {
                    if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 5.0f, true))
                    {
                        if (playerOwner && playerOwner != NULL)
                            sassy->AI()->Talk(3, playerOwner->GetGUID());
                    }
                    break;
                }
                case 10:    // Stop Explosion
                {
                    events.CancelEvent(EVENT_BOMBING_TRIGGER);
                    break;
                }
                case 18:    // To the Town
                {
                    if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 5.0f, true))
                    {
                        if (playerOwner && playerOwner != NULL)
                            sassy->AI()->Talk(4, playerOwner->GetGUID());
                    }
                    break;
                }
                case 19:    // Disaster
                {
                    if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 5.0f, true))
                    {
                        if (playerOwner && playerOwner != NULL)
                            sassy->AI()->Talk(5, playerOwner->GetGUID());
                    }
                    break;
                }
                case 22:    // Final
                {
                    if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 20.0f, true))
                    {
                        if (playerOwner && playerOwner != NULL)
                            sassy->AI()->Talk(7, playerOwner->GetGUID());
                    }
                    break;
                }
                case 26:    // Sassy inform you that u need to change seat!
                {
                    if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 5.0f, true))
                    {
                        if (playerOwner && playerOwner != NULL)
                        {
                            sassy->AI()->Talk(6, playerOwner->GetGUID());
                            events.ScheduleEvent(EVENT_PLAYER_SWITCH_SEAT, 4000);
                        }
                    }
                    break;
                }
                case 33:    // Despawn and Exit
                {
                    me->RemoveAllAuras();
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
                    Start(false, true, NULL, NULL, false, true);
                    events.ScheduleEvent(EVENT_TALK_SASSY, 3000);
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
                    case EVENT_BOMBING_TRIGGER:
                    {
                        DoCast(me, SPELL_BOMBING_TRIGGER, true);
                        events.RescheduleEvent(EVENT_BOMBING_TRIGGER, urand(500, 1500));
                        break;
                    }
                    case EVENT_TALK_SASSY:
                    {
                        if (Creature* sassy = me->FindNearestCreature(NPC_ENTRY_SASSY, 5.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL)
                                sassy->AI()->Talk(0, playerOwner->GetGUID());
                        }
                        events.CancelEvent(EVENT_TALK_SASSY);
                        break;
                    }
                    case EVENT_PLAYER_SWITCH_SEAT:
                    {
                        if (Unit* owner = me->GetCharmerOrOwner())
                            owner->CastSpell(me, SPELL_ENTRY_RIDE_BOMBER, true);
                        me->RemoveAurasDueToSpell(SPELL_BOMBER_LADDER);
                        events.CancelEvent(EVENT_PLAYER_SWITCH_SEAT);
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
        return new npc_flight_bomber_volcano_escapeAI (creature);
    }
};

class npc_assistant_greely : public CreatureScript
{
public:
    npc_assistant_greely() : CreatureScript("npc_assistant_greely") {}

    enum spellId
    {
        SPELL_DRINK_KAJA_COLA           = 73605,
    };

    enum npcId
    {
        NPC_ENTRY_MINECART  = 39329
    };

    enum actionId
    {
        ACTION_ENTER_MINECART   = 1
    };

    enum eventId
    {
        EVENT_ENTER_MINECART    = 1
    };

    enum questId
    {
        QUEST_ENTRY_MORALE_BOOST    = 25122,
        QUEST_ENTRY_LATEOTNT        = 25125
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_MORALE_BOOST)
        {
            creature->AI()->TalkWithDelay(500, 1, player->GetGUID());
            return false;
        }

        if (quest->GetQuestId() == QUEST_ENTRY_LATEOTNT)
        {
            creature->AI()->TalkWithDelay(500, 2, player->GetGUID());
            return false;
        }
        return true;
    }

    struct npc_assistant_greelyAI : public ScriptedAI
    {
        npc_assistant_greelyAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() == TYPEID_PLAYER)
            {
                if (owner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_MORALE_BOOST) == QUEST_STATUS_NONE ||
                    owner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_LATEOTNT) == QUEST_STATUS_NONE)
                me->CastWithDelay(1000, me, SPELL_DRINK_KAJA_COLA);
            }
            events.ScheduleEvent(EVENT_ENTER_MINECART, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DRINK_KAJA_COLA:
                {
                    me->AI()->TalkWithDelay(500, 0);
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
                case ACTION_ENTER_MINECART:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_MINECART)
                                me->EnterVehicle(vehicle, 4);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isAlive())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENTER_MINECART:
                    {
                        if (me->GetVehicleBase())
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        else
                        {
                            DoAction(ACTION_ENTER_MINECART);
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        }
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
        return new npc_assistant_greelyAI(creature);
    }
};

class npc_gobber_kaja_cola : public CreatureScript
{
public:
    npc_gobber_kaja_cola() : CreatureScript("npc_gobber_kaja_cola") {}

    enum spellId
    {
        SPELL_DRINK_KAJA_COLA           = 73605,
    };

    enum npcId
    {
        NPC_ENTRY_MINECART  = 39329
    };

    enum actionId
    {
        ACTION_ENTER_MINECART   = 1
    };

    enum eventId
    {
        EVENT_ENTER_MINECART    = 1
    };

    struct npc_gobber_kaja_colaAI : public ScriptedAI
    {
        npc_gobber_kaja_colaAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() == TYPEID_PLAYER)
                me->CastWithDelay(1000, me, SPELL_DRINK_KAJA_COLA);
            events.ScheduleEvent(EVENT_ENTER_MINECART, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DRINK_KAJA_COLA:
                {
                    me->AI()->TalkWithDelay(500, 0);
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
                case ACTION_ENTER_MINECART:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_MINECART)
                                me->EnterVehicle(vehicle, 3);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isAlive())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENTER_MINECART:
                    {
                        if (me->GetVehicleBase())
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        else
                        {
                            DoAction(ACTION_ENTER_MINECART);
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        }
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
        return new npc_gobber_kaja_colaAI(creature);
    }
};

class npc_izzy_kaja_cola : public CreatureScript
{
public:
    npc_izzy_kaja_cola() : CreatureScript("npc_izzy_kaja_cola") {}

    enum spellId
    {
        SPELL_DRINK_KAJA_COLA           = 73605,
    };

    enum npcId
    {
        NPC_ENTRY_MINECART  = 39329
    };

    enum actionId
    {
        ACTION_ENTER_MINECART   = 1
    };

    enum eventId
    {
        EVENT_ENTER_MINECART    = 1
    };

    struct npc_izzy_kaja_colaAI : public ScriptedAI
    {
        npc_izzy_kaja_colaAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() == TYPEID_PLAYER)
                me->CastWithDelay(1000, me, SPELL_DRINK_KAJA_COLA);
            events.ScheduleEvent(EVENT_ENTER_MINECART, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DRINK_KAJA_COLA:
                {
                    me->AI()->TalkWithDelay(500, 0);
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
                case ACTION_ENTER_MINECART:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_MINECART)
                                me->EnterVehicle(vehicle, 2);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isAlive())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENTER_MINECART:
                    {
                        if (me->GetVehicleBase())
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        else
                        {
                            DoAction(ACTION_ENTER_MINECART);
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        }
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
        return new npc_izzy_kaja_colaAI(creature);
    }
};

class npc_ace_kaja_cola : public CreatureScript
{
public:
    npc_ace_kaja_cola() : CreatureScript("npc_ace_kaja_cola") {}

    enum spellId
    {
        SPELL_DRINK_KAJA_COLA           = 73605,
    };

    enum npcId
    {
        NPC_ENTRY_MINECART  = 39329
    };

    enum actionId
    {
        ACTION_ENTER_MINECART   = 1
    };

    enum eventId
    {
        EVENT_ENTER_MINECART    = 1
    };

    struct npc_ace_kaja_colaAI : public ScriptedAI
    {
        npc_ace_kaja_colaAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            if (owner->GetTypeId() == TYPEID_PLAYER)
                me->CastWithDelay(1000, me, SPELL_DRINK_KAJA_COLA);
            events.ScheduleEvent(EVENT_ENTER_MINECART, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DRINK_KAJA_COLA:
                {
                    me->AI()->TalkWithDelay(500, 0);
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
                case ACTION_ENTER_MINECART:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_MINECART)
                                me->EnterVehicle(vehicle, 1);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isAlive())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENTER_MINECART:
                    {
                        if (me->GetVehicleBase())
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        else
                        {
                            DoAction(ACTION_ENTER_MINECART);
                            events.RescheduleEvent(EVENT_ENTER_MINECART, 1000);
                        }
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
        return new npc_ace_kaja_colaAI(creature);
    }
};

class spell_escape_velocity_rockets : public SpellScriptLoader
{
    public:
        spell_escape_velocity_rockets() : SpellScriptLoader("spell_escape_velocity_rockets") { }

        enum spellId
        {
            SPELL_ESCAPE_VELOCITY_ROCKETS   = 73948
        };

        class spell_escape_velocity_rockets_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_escape_velocity_rockets_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ESCAPE_VELOCITY_ROCKETS))
                    return false;
                return true;
            }

            class rocketLaunch : public BasicEvent
            {
                public:
                    explicit rocketLaunch(Creature* creature) : creature(creature) {}

                bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
                {
                    creature->GetMotionMaster()->MovementExpired(false);
                    creature->GetMotionMaster()->MoveJump(creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ()+100, 5.0f, 45.0f, 0);
                    creature->DespawnOrUnsummon(7000);
                    return true;
                }

            private:
                Creature* creature;
            };

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (target->ToCreature())
                        target->m_Events.AddEvent(new rocketLaunch(target->ToCreature()), (target)->m_Events.CalculateTime(3500));
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectRemoveFn(spell_escape_velocity_rockets_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_escape_velocity_rockets_AuraScript();
        }
};

class npc_gallywix_final_event : public CreatureScript
{
public:
    npc_gallywix_final_event() : CreatureScript("npc_gallywix_final_event") {}

    struct npc_gallywix_final_eventAI : public ScriptedAI
    {
        npc_gallywix_final_eventAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum spellId
        {
            SPELL_CALL_A_MEETING        = 81000,
            SPELL_DOWNSIZING            = 74003,
            SPELL_REVENUE_STREAM        = 74005,
            SPELL_UNLOAD_TOXIC_ASSETS   = 74000,
            SPELL_YOU_RE_FIRED          = 74004
        };

        enum eventId
        {
            EVENT_CAST_CALL_A_MEETING       = 1,
            EVENT_CAST_DOWNSIZING,
            EVENT_CAST_REVENUE_STREAM,
            EVENT_CAST_UNLOAD_TOXIC_ASSETS,
            EVENT_CAST_YOU_RE_FIRED,
            EVENT_CHECK_HEALTH
        };

        enum talkId
        {
            COMBAT_TALK_DOWNSIZING  = 0,
            COMBAT_TALK_REVENUE,
            COMBAT_TALK_TOXIC,
            COMBAT_TALK_FIRED,
            AGGRO_TALK,
            OUTRO_TALK_1,
            OUTRO_TALK_2,
            OUTRO_TALK_3,
            OUTRO_TALK_4
        };

        enum actionId
        {
            ACTION_FINISH_EVENT     = 1
        };

        enum npcId
        {
            NPC_ENTRY_THRALL    = 39594
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
            events.ScheduleEvent(EVENT_CAST_DOWNSIZING, 5000);
            events.ScheduleEvent(EVENT_CAST_REVENUE_STREAM, 13000);
            events.ScheduleEvent(EVENT_CAST_UNLOAD_TOXIC_ASSETS, 21000);
            events.ScheduleEvent(EVENT_CAST_YOU_RE_FIRED, 30000);
        }

        void DoCompleteQuest()
        {
            std::list<Unit*> targets;
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 100.0f);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr))
                {
                    if ((*itr)->GetTypeId() != TYPEID_PLAYER)
                        continue;

                    if ((*itr)->isAlive())
                        (*itr)->ToPlayer()->KilledMonsterCredit(me->GetEntry());
                }
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FINISH_EVENT:
                {
                    events.Reset();
                    me->setFaction(35);
                    DoStopAttack();
                    me->CastStop();
                    Talk(OUTRO_TALK_1);
                    TalkWithDelay(10000, OUTRO_TALK_2);
                    TalkWithDelay(20000, OUTRO_TALK_3);
                    if (Creature* thrall = me->FindNearestCreature(NPC_ENTRY_THRALL, 50.0f, true))
                        thrall->AI()->DoAction(1);
                    TalkWithDelay(56000, OUTRO_TALK_4);
                    me->DespawnOrUnsummon(64000);
                    DoCompleteQuest();
                    break;
                }
                default:
                    break;
            }
        }

        void EnterCombat(Unit* victim)
        {
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
            Talk(AGGRO_TALK);
            DoCast(victim, SPELL_CALL_A_MEETING);
            events.ScheduleEvent(EVENT_CAST_DOWNSIZING, 5000);
            events.ScheduleEvent(EVENT_CAST_REVENUE_STREAM, 13000);
            events.ScheduleEvent(EVENT_CAST_UNLOAD_TOXIC_ASSETS, 21000);
            events.ScheduleEvent(EVENT_CAST_YOU_RE_FIRED, 30000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_DOWNSIZING:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 25.0f, false))
                        {
                            DoCast(target, SPELL_DOWNSIZING);
                            Talk(COMBAT_TALK_DOWNSIZING);
                            events.RescheduleEvent(EVENT_CAST_DOWNSIZING, 60000);
                        }
                        break;
                    }
                    case EVENT_CAST_REVENUE_STREAM:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 25.0f, false))
                        {
                            DoCast(target, SPELL_REVENUE_STREAM);
                            Talk(COMBAT_TALK_REVENUE);
                            events.RescheduleEvent(EVENT_CAST_REVENUE_STREAM, 13000);
                        }
                        break;
                    }
                    case EVENT_CAST_UNLOAD_TOXIC_ASSETS:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 25.0f, false))
                        {
                            DoCast(target, SPELL_UNLOAD_TOXIC_ASSETS);
                            Talk(COMBAT_TALK_TOXIC);
                        }
                        events.RescheduleEvent(EVENT_CAST_UNLOAD_TOXIC_ASSETS, 21000);
                        break;
                    }
                    case EVENT_CAST_YOU_RE_FIRED:
                    {
                        RESCHEDULE_IF_CASTING;
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 25.0f, false))
                        {
                            DoCast(SPELL_YOU_RE_FIRED);
                            Talk(COMBAT_TALK_FIRED);
                        }
                        events.RescheduleEvent(EVENT_CAST_YOU_RE_FIRED, 31000);
                        break;
                    }
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealthPct() <= 10)
                            DoAction(ACTION_FINISH_EVENT);
                        else
                            events.RescheduleEvent(EVENT_CHECK_HEALTH, 2000);
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
        return new npc_gallywix_final_eventAI(creature);
    }
};

class npc_thrall_final_event : public CreatureScript
{
public:
    npc_thrall_final_event() : CreatureScript("npc_thrall_final_event") {}

    struct npc_thrall_final_eventAI : public ScriptedAI
    {
        npc_thrall_final_eventAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum spellId
        {
            SPELL_CHAIN_LIGHTNING   = 74019,
            SPELL_LAVA_BURST        = 74020,
            SPELL_THUNDER           = 74021
        };

        enum eventId
        {
            EVENT_CHAIN_LIGHTNING   = 1,
            EVENT_LAVA_BURST,
            EVENT_THUNDER
        };

        enum talkId
        {
            OUTRO_TALK_1    = 0,
            OUTRO_TALK_2,
            OUTRO_TALK_3
        };

        enum actionId
        {
            ACTION_START_TALK = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_TALK:
                {
                    events.Reset();
                    DoStopAttack();
                    me->CastStop();
                    TalkWithDelay(28000, OUTRO_TALK_1);
                    TalkWithDelay(38000, OUTRO_TALK_2);
                    TalkWithDelay(48000, OUTRO_TALK_3);
                    me->DespawnOrUnsummon(64000);
                    break;
                }
                default:
                    break;
            }
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_LAVA_BURST, 1000);
            events.ScheduleEvent(EVENT_THUNDER, 4000);
            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 7500);
        }

        void EnterCombat(Unit* victim)
        {
            events.ScheduleEvent(EVENT_LAVA_BURST, 1000);
            events.ScheduleEvent(EVENT_THUNDER, 4000);
            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 7500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LAVA_BURST:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCastVictim(SPELL_LAVA_BURST);
                        events.RescheduleEvent(EVENT_LAVA_BURST, urand(5000,8000));
                        break;
                    }
                    case EVENT_CHAIN_LIGHTNING:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCastVictim(SPELL_CHAIN_LIGHTNING);
                        events.RescheduleEvent(EVENT_CHAIN_LIGHTNING, urand(9000,12500));
                        break;
                    }
                    case EVENT_THUNDER:
                    {
                        RESCHEDULE_IF_CASTING;
                        DoCast(SPELL_THUNDER);
                        events.RescheduleEvent(EVENT_THUNDER, urand(6000,10000));
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
        return new npc_thrall_final_eventAI(creature);
    }
};

class npc_ultimate_footbomb_uniform : public CreatureScript
{
public:
    npc_ultimate_footbomb_uniform() : CreatureScript("npc_ultimate_footbomb_uniform") { }

    enum questId
    {
        QUEST_ENTRY_FINAL_CONFRONTATION     = 25251
    };

    enum spellId
    {
        SPELL_SUMMON_FOOTBOMB   = 73991
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_FINAL_CONFRONTATION) == QUEST_STATUS_INCOMPLETE && !player->GetVehicleBase())
        {
            player->CastSpell(player, SPELL_SUMMON_FOOTBOMB, true);
            return true;
        }
        return false;
    }
};

class spell_rockin_powder_infused_boots_docks : public SpellScriptLoader
{
    public:
        spell_rockin_powder_infused_boots_docks() : SpellScriptLoader("spell_rockin_powder_infused_boots_docks") { }

        class spell_rockin_powder_infused_boots_docks_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rockin_powder_infused_boots_docks_SpellScript);

            enum spellId
            {
                SPELL_ROCKIN_POWDER_INFUSED = 74028
            };

            void HandleDebuff()
            {
                if (Unit* caster = GetCaster())
                    caster->AddAura(SPELL_ROCKIN_POWDER_INFUSED, caster);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_rockin_powder_infused_boots_docks_SpellScript::HandleDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rockin_powder_infused_boots_docks_SpellScript();
        }
};

class go_gallywix_docks_fireworks : public GameObjectScript
{
    public:
        go_gallywix_docks_fireworks() : GameObjectScript("go_gallywix_docks_fireworks") {}

        enum eventId
        {
            EVENT_DESPAWN_WITH_EFFECT   = 1
        };

        struct go_gallywix_docks_fireworksAI : public GameObjectAI
        {
            EventMap events;

            go_gallywix_docks_fireworksAI(GameObject* go) : GameObjectAI(go)
            {
                events.ScheduleEvent(EVENT_DESPAWN_WITH_EFFECT, urand(2500,15000));
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DESPAWN_WITH_EFFECT:
                        {
                            go->SendObjectDeSpawnAnim(go->GetGUID());
                            events.RescheduleEvent(EVENT_DESPAWN_WITH_EFFECT, urand(5000,21000));
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        };

        GameObjectAI* GetAI(GameObject* go) const
        {
            return new go_gallywix_docks_fireworksAI(go);
        }
};

void AddSC_the_lost_isles()
{
    new npc_geargrinder_gizmo_intro();
    new npc_doc_zapnozzle_intro();
    new go_goblin_escape_pod();
    new npc_bomb_throwing_monkey();
    new spell_ktc_snapflash();
    new npc_kilag_gorefang();
    new npc_thrall_ship_1();
    new npc_thrall_lightning_trigger();
    new npc_cyclone_of_the_elements();
    new npc_sassy_rocket();
    new npc_sling_rocket_tradeprince();
    new npc_sling_rocket_player();
    new spell_remote_control_fireworks();
    new npc_wild_clucker();
    new npc_wild_clucker_egg();
    new npc_spiny_raptor();
    new spell_wild_clucker_eggs();
    new npc_ace_event_soe();
    new npc_faceless_soe();
    new spell_super_booster_rocket_boots();
    new spell_rockin_powder_infused_boots();
    new npc_flight_bomber_volcano_escape();
    new npc_assistant_greely();
    new npc_gobber_kaja_cola();
    new npc_izzy_kaja_cola();
    new npc_ace_kaja_cola();
    new spell_escape_velocity_rockets();
    new npc_gallywix_final_event();
    new npc_thrall_final_event();
    new npc_ultimate_footbomb_uniform();
    new spell_rockin_powder_infused_boots_docks();
    new go_gallywix_docks_fireworks();
}
