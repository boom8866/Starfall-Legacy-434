
#include "ScriptPCH.h"
#include "BattlefieldMgr.h"
#include "BattlefieldTB.h"
#include "Battlefield.h"
#include "ScriptSystem.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include "Vehicle.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"

enum eTBqueuenpctext
{
    TB_NPCQUEUE_TEXT_H_NOWAR = 110006,
    TB_NPCQUEUE_TEXT_H_QUEUE = 110002,
    TB_NPCQUEUE_TEXT_H_WAR   = 110005,
    TB_NPCQUEUE_TEXT_A_NOWAR = 110003,
    TB_NPCQUEUE_TEXT_A_QUEUE = 110001,
    TB_NPCQUEUE_TEXT_A_WAR   = 110004,
    TB_NPCQUEUE_TEXTOPTION_JOIN = 20087,
};

class npc_tb_spiritguide : public CreatureScript
{
public:
    npc_tb_spiritguide() : CreatureScript("npc_tb_spiritguide") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        Battlefield* BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
        if (BfTB)
        {
            GraveyardVect gy = BfTB->GetGraveyardVector();
            for(uint8 i=0;i<gy.size();i++)
            {
                if(gy[i]->GetControlTeamId()==player->GetTeamId())
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,sObjectMgr->GetTrinityStringForDBCLocale(((BfGraveYardTB*)gy[i])->GetTextId()), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+i);
                }
            }
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->CLOSE_GOSSIP_MENU();

        Battlefield*BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
        if (BfTB)
        {
            GraveyardVect gy = BfTB->GetGraveyardVector();
            for(uint8 i=0;i<gy.size();i++)
            {
                if(uiAction-GOSSIP_ACTION_INFO_DEF==i && gy[i]->GetControlTeamId()==player->GetTeamId())
                {
                    const WorldSafeLocsEntry* ws=sWorldSafeLocsStore.LookupEntry(gy[i]->GetGraveyardId());
                    player->TeleportTo(ws->map_id,ws->x,ws->y,ws->z,0);
                }
            }
        }
        return true;
    }

    struct npc_tb_spiritguideAI : public ScriptedAI
    {
        npc_tb_spiritguideAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 playerGUID;
        uint32 resurrectionTimer;

        void Reset()
        {
            playerGUID = 0;
            resurrectionTimer = 30000;
        }

        void UpdateAI(uint32 diff)
        {
            if (resurrectionTimer <= diff) // Hack temporal
            {
                Battlefield* BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
                if (BfTB)
                {
                    if (Player* player = me->FindNearestPlayer(6.0f, false))
                    {
                        playerGUID = player->GetGUID();
                        if (!player->isAlive() && !player->HasAura(SPELL_WAITING_FOR_RESURRECT))
                            player->CastSpell(player, SPELL_WAITING_FOR_RESURRECT, true);
                    }
                }

                resurrectionTimer = 30000;
            }
            else
                resurrectionTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tb_spiritguideAI(creature);
    }
};

class npc_tol_barad_battlemage : public CreatureScript
{
public:
    npc_tol_barad_battlemage() : CreatureScript("npc_tol_barad_battlemage") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        Battlefield*BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
        if (BfTB)
        {

            if(BfTB->IsWarTime())
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,sObjectMgr->GetTrinityStringForDBCLocale(TB_NPCQUEUE_TEXTOPTION_JOIN), GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF);
                player->SEND_GOSSIP_MENU(BfTB->GetDefenderTeam()?TB_NPCQUEUE_TEXT_H_WAR:TB_NPCQUEUE_TEXT_A_WAR, creature->GetGUID());
            }
            else
            {
                uint32 uiTime=BfTB->GetTimer()/1000;
                player->SendUpdateWorldState(4354,time(NULL)+uiTime);
                if(uiTime<15*MINUTE)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,sObjectMgr->GetTrinityStringForDBCLocale(TB_NPCQUEUE_TEXTOPTION_JOIN), GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF);
                    player->SEND_GOSSIP_MENU(BfTB->GetDefenderTeam()?TB_NPCQUEUE_TEXT_H_QUEUE:TB_NPCQUEUE_TEXT_A_QUEUE, creature->GetGUID());
                }
                else
                {
                    player->SEND_GOSSIP_MENU(BfTB->GetDefenderTeam()?TB_NPCQUEUE_TEXT_H_NOWAR:TB_NPCQUEUE_TEXT_A_NOWAR, creature->GetGUID());
                }
            }
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 /*uiAction*/)
    {
        player->CLOSE_GOSSIP_MENU();

        Battlefield*BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
        if (BfTB)
        {
            if(BfTB->IsWarTime()){
                BfTB->InvitePlayerToWar(player, BfTB->GetGUID());
            }
            else
            {
                uint32 uiTime=BfTB->GetTimer()/1000;
                if(uiTime<15*MINUTE)
                    BfTB->InvitePlayerToQueue(player, BfTB->GetGUID());
            }
        }
        return true;
    }
};

enum Events
{
    EVENT_CHECK_TOWERS = 1,
};

class npc_tb_abandoned_siege_engine : public CreatureScript
{
public:
    npc_tb_abandoned_siege_engine() : CreatureScript("npc_tb_abandoned_siege_engine") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tb_abandoned_siege_engineAI(creature);
    }

    struct npc_tb_abandoned_siege_engineAI : public ScriptedAI
    {
        npc_tb_abandoned_siege_engineAI(Creature* creature) : ScriptedAI(creature),
            _vehicle(me->GetVehicleKit())
        {
            ASSERT(_vehicle);
        }

        void Reset()
        {
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                if (Player* player = me->FindNearestPlayer(1.0f, true))
                    player->ExitVehicle(me);
        }

        void UpdateAI(uint32 diff)
        {
            Battlefield* BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
            if (BfTB)
            {
                if (BfTB->IsWarTime())
                {
                    if (!me->HasAura(95330))
                    {
                        me->CastSpell(me, 95330, true);
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                }
            }
        }

        private:
            Vehicle* _vehicle;
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->CLOSE_GOSSIP_MENU();

        Battlefield* BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
        if (BfTB)
        {
            if (BfTB->GetAttackerTeam() == player->GetTeamId())
            {
                if (!creature->HasAura(84974))
                    player->CastSpell(creature, 84754, true);
            }
        }
        return true;
    }
};

class npc_tb_turret : public CreatureScript
{
public:
    npc_tb_turret() : CreatureScript("npc_tb_turret") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tb_turretAI(creature);
    }

    struct npc_tb_turretAI : public ScriptedAI
    {
        npc_tb_turretAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        uint32 damageTower;

        void Reset()
        {
            damageTower = 100;
        }

        void IsSummonedBy(Unit* who)
        {
            if (me->GetEntry() == 45564)
                me->CastSpell(who, 84754, true);

            Battlefield* BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB);
            if (BfTB)
            {
                if (Player* player = me->FindNearestPlayer(2.0f, true))
                    if (BfTB->GetAttackerTeam() == player->GetTeamId())
                        me->setFaction(player->getFaction());
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (damageTower <= diff)
            {
                if (Creature* creature = me->FindNearestCreature(45561, 200.0f))
                    me->CastSpell(creature, 85123, false);

                damageTower = 2000;
            }
            else
                damageTower -= diff;
        }
    };
};

class npc_tb_turret_target : public CreatureScript
{
public:
    npc_tb_turret_target() : CreatureScript("npc_tb_turret_target") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tb_turret_targetAI(creature);
    }

    struct npc_tb_turret_targetAI : public ScriptedAI
    {
        npc_tb_turret_targetAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        uint32 damageTower;
        uint8 count;
        uint8 turretCount;
        bool IsDamaged;
        bool IsDestroyed;

        void Reset()
        {
            damageTower = 100;
            IsDamaged = false;
            IsDestroyed = false;
            count = 0;
        }

        void UpdateAI(uint32 diff)
        {
            std::list<Creature*> turrets;
            GetCreatureListWithEntryInGrid(turrets, me, 45564, 100.0f);

            std::list<Creature*> sieges;
            GetCreatureListWithEntryInGrid(sieges, me, 45344, 100.0f);

            if (damageTower <= diff)
            {
                if (Battlefield* BfTB = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_TB))
                {
                    if (turrets.empty())
                        return;

                    for (std::list<Creature*>::iterator itr = turrets.begin(); itr != turrets.end(); ++itr)
                    {
                        if ((*itr))
                        {
                            ++count;
                            if (count == 40)
                                IsDamaged = true;

                            if (count == 80)
                                IsDestroyed = true;
                        }
                    }
                }
                damageTower = 2000;
            }
            else
                damageTower -= diff;

            if (IsDamaged)
            {
                if (GameObject* go = me->FindNearestGameObject(204588, 500.0f))
                    go->SetDestructibleState(GO_DESTRUCTIBLE_DAMAGED, NULL, true);

                if (GameObject* go = me->FindNearestGameObject(204589, 500.0f))
                    go->SetDestructibleState(GO_DESTRUCTIBLE_DAMAGED, NULL, true);

                if (GameObject* go = me->FindNearestGameObject(204590, 500.0f))
                    go->SetDestructibleState(GO_DESTRUCTIBLE_DAMAGED, NULL, true);

                IsDamaged = false;
            }

            if (IsDestroyed)
            {
                for (std::list<Creature*>::iterator itr = sieges.begin(); itr != sieges.end(); ++itr)
                    if ((*itr)->HasAura(84974))
                        (*itr)->RemoveAurasDueToSpell(84974);

                for (std::list<Creature*>::iterator itr = turrets.begin(); itr != turrets.end(); ++itr)
                    (*itr)->DespawnOrUnsummon();

                if (GameObject* go = me->FindNearestGameObject(204588, 500.0f))
                    go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED, NULL, true);

                if (GameObject* go = me->FindNearestGameObject(204589, 500.0f))
                    go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED, NULL, true);

                if (GameObject* go = me->FindNearestGameObject(204590, 500.0f))
                    go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED, NULL, true);

                IsDestroyed = false;
            }
        }
    };
};

class npc_tb_tower_range : public CreatureScript
{
public:
    npc_tb_tower_range() : CreatureScript("npc_tb_tower_range") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tb_tower_rangeAI(creature);
    }

    struct npc_tb_tower_rangeAI : public ScriptedAI
    {
        npc_tb_tower_rangeAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        uint32 towerRange;

        void Reset()
        {
            towerRange = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (towerRange <= diff)
            {
                if (Creature* creature = me->FindNearestCreature(45344, 80.0f))
                    creature->CastSpell(creature, 84979, true);

                towerRange = 2000;
            }
            else
                towerRange -= diff;
        }
    };
};

class spell_forgotten_hills_summon : public SpellScriptLoader
{
    public:
        spell_forgotten_hills_summon() : SpellScriptLoader("spell_forgotten_hills_summon") { }

        class spell_forgotten_hills_summon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_forgotten_hills_summon_SpellScript);

            enum npcId
            {
                NPC_ANGERED_SPIRIT      = 47277,
                NPC_RELEASED_SPIRIT     = 47272
            };

            enum goId
            {
                GO_TOMBSTONE    = 206570
            };

            void HandleSummon()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->SummonCreature(NPC_RELEASED_SPIRIT, caster->GetPositionX()-1, caster->GetPositionY()+1, caster->GetPositionZ()+3, caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ANGERED_SPIRIT, caster->GetPositionX()-urand(1,2), caster->GetPositionY()+urand(1,2), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_forgotten_hills_summon_SpellScript::HandleSummon);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_forgotten_hills_summon_SpellScript();
        }
};

class npc_released_spirit : public CreatureScript
{
public:
    npc_released_spirit() : CreatureScript("npc_released_spirit") { }

    struct npc_released_spiritAI : public ScriptedAI
    {
        npc_released_spiritAI(Creature* creature) : ScriptedAI(creature) { }

        enum pointId
        {
            POINT_AWAY  = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            TalkWithDelay(1500, 0, owner->GetGUID());
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->GetMotionMaster()->MovementExpired(false);
            me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 120.0f, 3.0f, 3.0f, POINT_AWAY);
            me->DespawnOrUnsummon(10000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_released_spiritAI(creature);
    }
};

class npc_restless_infantry : public CreatureScript
{
public:
    npc_restless_infantry() : CreatureScript("npc_restless_infantry") { }

    enum eventId
    {
        EVENT_SEARCH_VICTIM         = 1,
        EVENT_SEARCH_ENEMY_PLAYER,
        EVENT_CAST_WHIRLWIND,
        EVENT_CAST_MORTAL_STRIKE,
        EVENT_CAST_THUNDERCLAP,
        EVENT_ENTER_EVADE
    };

    enum npcId
    {
        NPC_RESTLESS_SOLDIER    = 46825
    };

    enum spellId
    {
        SPELL_MORTAL_STRIKE     = 13737,
        SPELL_WHIRLWIND         = 17207,
        SPELL_THUNDERCLAP       = 81140
    };

    struct npc_restless_infantryAI : public ScriptedAI
    {
        npc_restless_infantryAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_VICTIM, 2000);
            events.ScheduleEvent(EVENT_ENTER_EVADE, 6000);

            if (me->GetReactState() != REACT_DEFENSIVE)
                me->SetReactState(REACT_DEFENSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CAST_WHIRLWIND, urand(5000, 8000));
            events.ScheduleEvent(EVENT_CAST_MORTAL_STRIKE, urand(1000, 2500));
            events.ScheduleEvent(EVENT_CAST_THUNDERCLAP, urand(10000, 12500));
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_VICTIM:
                    {
                        events.RescheduleEvent(EVENT_SEARCH_VICTIM, 2000);
                        if (Creature* soldier = me->FindNearestCreature(NPC_RESTLESS_SOLDIER, 25.0f, true))
                            AttackStart(soldier);
                        else
                            events.ScheduleEvent(EVENT_SEARCH_ENEMY_PLAYER, 2000);
                        break;
                    }
                    case EVENT_SEARCH_ENEMY_PLAYER:
                    {
                        events.RescheduleEvent(EVENT_SEARCH_VICTIM, 2000);
                        std::list<Player*> targets;
                        Trinity::AnyPlayerInObjectRangeCheck u_check(me, 25.0f);
                        Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(25.0f, searcher);
                        for (std::list<Player*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr)->GetTeamId() == TEAM_HORDE)
                                continue;
                            AttackStart((*itr));
                        }
                        break;
                    }
                    case EVENT_CAST_WHIRLWIND:
                    {
                        events.RescheduleEvent(EVENT_CAST_WHIRLWIND, 8000);
                        if (me->getVictim())
                            DoCast(SPELL_WHIRLWIND);
                        break;
                    }
                    case EVENT_CAST_MORTAL_STRIKE:
                    {
                        events.RescheduleEvent(EVENT_CAST_MORTAL_STRIKE, 4000);
                        DoCastVictim(SPELL_MORTAL_STRIKE);
                        break;
                    }
                    case EVENT_CAST_THUNDERCLAP:
                    {
                        events.RescheduleEvent(EVENT_CAST_THUNDERCLAP, 10000);
                        DoCastVictim(SPELL_THUNDERCLAP);
                        break;
                    }
                    case EVENT_ENTER_EVADE:
                    {
                        if (!me->getVictim())
                            EnterEvadeMode();
                        else
                            events.RescheduleEvent(EVENT_ENTER_EVADE, 5000);
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
        return new npc_restless_infantryAI(creature);
    }
};

class npc_restless_soldier : public CreatureScript
{
public:
    npc_restless_soldier() : CreatureScript("npc_restless_soldier") { }

    enum eventId
    {
        EVENT_SEARCH_VICTIM         = 1,
        EVENT_SEARCH_ENEMY_PLAYER,
        EVENT_CAST_WHIRLWIND,
        EVENT_CAST_MORTAL_STRIKE,
        EVENT_CAST_THUNDERCLAP,
        EVENT_ENTER_EVADE
    };

    enum npcId
    {
        NPC_RESTLESS_INFANTRY    = 46823
    };

    enum spellId
    {
        SPELL_MORTAL_STRIKE     = 13737,
        SPELL_WHIRLWIND         = 17207,
        SPELL_THUNDERCLAP       = 81140
    };

    struct npc_restless_soldierAI : public ScriptedAI
    {
        npc_restless_soldierAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_SEARCH_VICTIM, 2000);
            events.ScheduleEvent(EVENT_ENTER_EVADE, 6000);
            if (me->GetReactState() != REACT_DEFENSIVE)
                me->SetReactState(REACT_DEFENSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CAST_WHIRLWIND, urand(5000, 8000));
            events.ScheduleEvent(EVENT_CAST_MORTAL_STRIKE, urand(1000, 2500));
            events.ScheduleEvent(EVENT_CAST_THUNDERCLAP, urand(10000, 12500));
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_VICTIM:
                    {
                        events.RescheduleEvent(EVENT_SEARCH_VICTIM, 2000);
                        if (Creature* soldier = me->FindNearestCreature(NPC_RESTLESS_INFANTRY, 25.0f, true))
                            AttackStart(soldier);
                        else
                            events.ScheduleEvent(EVENT_SEARCH_ENEMY_PLAYER, 2000);
                        break;
                    }
                    case EVENT_SEARCH_ENEMY_PLAYER:
                    {
                        events.RescheduleEvent(EVENT_SEARCH_VICTIM, 2000);
                        std::list<Player*> targets;
                        Trinity::AnyPlayerInObjectRangeCheck u_check(me, 25.0f);
                        Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(25.0f, searcher);
                        for (std::list<Player*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr)->GetTeamId() == TEAM_ALLIANCE)
                                continue;
                            AttackStart((*itr));
                        }
                        break;
                    }
                    case EVENT_CAST_WHIRLWIND:
                    {
                        events.RescheduleEvent(EVENT_CAST_WHIRLWIND, 8000);
                        if (me->getVictim())
                            DoCast(SPELL_WHIRLWIND);
                        break;
                    }
                    case EVENT_CAST_MORTAL_STRIKE:
                    {
                        events.RescheduleEvent(EVENT_CAST_MORTAL_STRIKE, 4000);
                        DoCastVictim(SPELL_MORTAL_STRIKE);
                        break;
                    }
                    case EVENT_CAST_THUNDERCLAP:
                    {
                        events.RescheduleEvent(EVENT_CAST_THUNDERCLAP, 10000);
                        DoCastVictim(SPELL_THUNDERCLAP);
                        break;
                    }
                    case EVENT_ENTER_EVADE:
                    {
                        if (!me->getVictim())
                            EnterEvadeMode();
                        else
                            events.RescheduleEvent(EVENT_ENTER_EVADE, 5000);
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
        return new npc_restless_soldierAI(creature);
    }
};

class npc_farson_hold_prisoner : public CreatureScript
{
public:
    npc_farson_hold_prisoner() : CreatureScript("npc_farson_hold_prisoner") { }

    struct npc_farson_hold_prisonerAI : public npc_escortAI
    {
        npc_farson_hold_prisonerAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum questId
        {
            QUEST_WALK_A_MILE_IN_THEIR_SHOES_H  = 28721,
            QUEST_WALK_A_MILE_IN_THEIR_SHOES_A  = 28065
        };

        enum eventId
        {
            EVENT_START_WAYPOINT    = 1,
            EVENT_RESTART_WP
        };

        enum mountId
        {
            MOUNT_HORDE     = 237,
            MOUNT_ALLIANCE  = 23960
        };

        enum questCredit
        {
            QUEST_CREDIT_HORDE      = 96322,
            QUEST_CREDIT_ALLIANCE   = 96323
        };

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 4:
                {
                    me->SetReactState(REACT_DEFENSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    break;
                }
                case 5:
                {
                    SetEscortPaused(true);
                    TalkWithDelay(1000, 1);
                    events.ScheduleEvent(EVENT_RESTART_WP, 7000);
                    break;
                }
                case 9:
                {
                    SetEscortPaused(true);
                    TalkWithDelay(1000, 2);
                    events.ScheduleEvent(EVENT_RESTART_WP, 7000);
                    break;
                }
                case 18:
                {
                    SetEscortPaused(true);
                    TalkWithDelay(1000, 3);
                    events.ScheduleEvent(EVENT_RESTART_WP, 7000);
                    break;
                }
                case 27:
                {
                    SetEscortPaused(true);
                    TalkWithDelay(1000, 4);
                    events.ScheduleEvent(EVENT_RESTART_WP, 5000);
                    break;
                }
                case 29:
                {
                    SetEscortPaused(true);
                    TalkWithDelay(1000, 5);
                    events.ScheduleEvent(EVENT_RESTART_WP, 5000);
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    break;
                }
                case 30:
                {
                    SetEscortPaused(true);
                    events.ScheduleEvent(EVENT_RESTART_WP, 5000);
                    switch (me->GetEntry())
                    {
                        case 48326:     // Horde
                        {
                            me->Mount(MOUNT_HORDE);
                            DoCastAOE(QUEST_CREDIT_HORDE);
                            break;
                        }
                        case 49443:     // Alliance
                        {
                            me->Mount(MOUNT_ALLIANCE);
                            DoCastAOE(QUEST_CREDIT_ALLIANCE);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 5000);
            TalkWithDelay(1000, 0);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(true, true, NULL, NULL, false, false, true);
                    SetDespawnAtFar(false);
                    SetDespawnAtEnd(true);
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
                    case EVENT_RESTART_WP:
                    {
                        events.CancelEvent(EVENT_RESTART_WP);
                        SetEscortPaused(false);
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
        return new npc_farson_hold_prisonerAI(creature);
    }
};

class npc_farson_hold_prisoner_gossip : public CreatureScript
{
public:
    npc_farson_hold_prisoner_gossip() : CreatureScript("npc_farson_hold_prisoner_gossip") { }

    enum questId
    {
        QUEST_WALK_A_MILE_IN_THEIR_SHOES_H  = 28721,
        QUEST_WALK_A_MILE_IN_THEIR_SHOES_A  = 28065
    };

    enum npcId
    {
        NPC_PRISONER_HORDE      = 48326,
        NPC_PRISONER_ALLIANCE   = 49443
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_WALK_A_MILE_IN_THEIR_SHOES_H) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(creature, 90350);
            creature->DespawnOrUnsummon(1);
            return true;
        }
        if (player->GetQuestStatus(QUEST_WALK_A_MILE_IN_THEIR_SHOES_A) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(creature, 90358);
            creature->DespawnOrUnsummon(1);
            return true;
        }
        return true;
    }
};

void AddSC_zone_tol_barad()
{
   new npc_tol_barad_battlemage();
   new npc_tb_spiritguide();
   new npc_tb_abandoned_siege_engine();
   new npc_tb_turret();
   new npc_tb_turret_target();
   new npc_tb_tower_range();
   new spell_forgotten_hills_summon();
   new npc_released_spirit();
   new npc_restless_infantry();
   new npc_restless_soldier();
   new npc_farson_hold_prisoner();
   new npc_farson_hold_prisoner_gossip();
}
