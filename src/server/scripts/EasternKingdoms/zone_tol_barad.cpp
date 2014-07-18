
#include "ScriptPCH.h"
#include "BattlefieldMgr.h"
#include "BattlefieldTB.h"
#include "Battlefield.h"
#include "ScriptSystem.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include "Vehicle.h"

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
}
