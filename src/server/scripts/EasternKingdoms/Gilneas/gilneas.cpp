/*
* Copyright (C) 2011 - 2013 Madman <https://github.com/oMadMano>
*
* THIS particular file is NOT free software.
* You are not allowed to share or redistribute it.
*/

#include "ScriptPCH.h"
#include "Unit.h"
#include "gilneas.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "ObjectMgr.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "SpellScript.h"
#include "Object.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "Vehicle.h"
#include "Language.h"
#include <math.h>

/*######
##  Quest Ids For Gilneas Part 1
##  
##  Working - [Lockdown!]
##  Working - [All Hell Breaks Loose]
##  Working - [Evacuate the Merchant Square]
##  Working - [Royal Orders]
##  Working - [Seek the Sister]
##  Working - [Flash Heal]
##  Working - [Safety in Numbers]
##  Working - [Old Divisions]
##  Working - [While You're At It]
##  Working - [The Prison Rooftop]
##  Working - [By the Skin of His Teeth]
######*/

const uint16 PanickedCitizenRandomEmote[5] =
{
    EMOTE_ONESHOT_COWER,
    EMOTE_ONESHOT_TALK,
    EMOTE_ONESHOT_CRY,
    EMOTE_ONESHOT_BEG,
    EMOTE_ONESHOT_EXCLAMATION,
};

enum eAttackedCreatures
{
    NPC_AFFLICTED_GILNEAN            = 50471,
    NPC_RAMPAGING_WORGEN             = 34884,
    NPC_FRENZIED_STALKER             = 35627,
    NPC_NORTHGATE_REBEL              = 41015,
    NPC_GILNEAS_CITY_GUARD_PHASE_4   = 50474,
    NPC_NORTHGATE_REBEL_PHASE_5      = 36057,
    NPC_BLOODFANG_STALKER_PHASE_5    = 35229,
};

class npc_panicked_citizen_gate : public CreatureScript
{
public:
    npc_panicked_citizen_gate() : CreatureScript("npc_panicked_citizen_gate") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_panicked_citizen_gateAI (creature);
    }

    struct npc_panicked_citizen_gateAI : public ScriptedAI
    {
        npc_panicked_citizen_gateAI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomEmoteTimer = urand(4000, 8000);
        }

        uint32 uiRandomEmoteTimer;

        void UpdateAI(uint32 diff)
        {
            if (uiRandomEmoteTimer <= diff)
            {
                uiRandomEmoteTimer = urand(2000, 5000);
                uint8 roll = urand(0, 5);
                me->HandleEmoteCommand(PanickedCitizenRandomEmote[roll]);
            }
            else
                uiRandomEmoteTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_gilneas_city_guard_gate : public CreatureScript
{
public:
    npc_gilneas_city_guard_gate() : CreatureScript("npc_gilneas_city_guard_gate") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_gateAI (creature);
    }

    struct npc_gilneas_city_guard_gateAI : public ScriptedAI
    {
        npc_gilneas_city_guard_gateAI(Creature* creature) : ScriptedAI(creature)
        {
            uiEventTimer = urand(10000, 40000);
            uiEventPhase = 0;

            if (me->GetDistance2d(-1430.47f, 1345.55f) < 10.0f)
                Event = true;
            else
                Event = false;
        }

        uint32 uiEventTimer;
        uint8 uiEventPhase;
        bool Event;

        void UpdateAI(uint32 diff)
        {
            if (Event)
                if (uiEventTimer <= diff)
                {
                    switch (uiEventPhase)
                    {
                    case 0:
                        {
                            std::list<Creature*> lCitizen;
                            me->GetCreatureListWithEntryInGrid(lCitizen, 44086, 35.0f);

                            if (!lCitizen.empty())
                            {
                                uint8 roll = urand(0, lCitizen.size() - 1);
                                std::list<Creature*>::iterator itr = lCitizen.begin();
                                std::advance(itr, roll);
                                Creature* citizen = *itr;

                                if (citizen)
                                {
                                    ++uiEventPhase;
                                    uiEventTimer = urand(5000, 10000);
                                    Talk(0);
                                    return;
                                }
                            }

                            uiEventTimer = urand(10000, 40000);
                        }
                        break;
                    case 1:
                        --uiEventPhase;
                        uiEventTimer = urand(10000, 40000);
                        Talk(0);
                        break;
                    }
                }
                else
                    uiEventTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_gilnean_crow
######*/

enum GilneanCrowEvents
{
    EVENT_SPAWN = 1,
    EVENT_SEEK  = 2,
};

class npc_gilnean_crow : public CreatureScript
{
public:
    npc_gilnean_crow() : CreatureScript("npc_gilnean_crow") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilnean_crowAI (creature);
    }

    struct npc_gilnean_crowAI : public ScriptedAI
    {
        npc_gilnean_crowAI(Creature* creature) : ScriptedAI(creature) {}

        bool Move;
        EventMap events;

        void Reset()
        {
            Move = false;
            me->SetPosition(me->GetCreatureData()->posX,me->GetCreatureData()->posY, me->GetCreatureData()->posZ, me->GetCreatureData()->orientation);
            events.ScheduleEvent(EVENT_SPAWN, urand(1000, 3000));
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_PING_GILNEAN_CROW)
            {
                if (!Move)
                {
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE , EMOTE_ONESHOT_NONE);
                    me->SetCanFly(true);
                    Move = true;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!Move)
                return;

            events.Update(diff);

            if ((me->GetPositionZ() - me->GetCreatureData()->posZ) >= 20.0f)
            {
                me->DisappearAndDie();
                me->RemoveCorpse(true);
                Move = false;
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SPAWN:
                    me->GetMotionMaster()->MovePoint(0, (me->GetPositionX() + irand(-15, 15)), (me->GetPositionY() + irand(-15, 15)), (me->GetPositionZ() + irand(5, 15)));
                    events.ScheduleEvent(EVENT_SEEK, urand(3000, 5000));
                    break;
                }
            }
        }
    };
};

/*######
## npc_prince_liam_greymane_intro
######*/

class npc_prince_liam_greymane_intro : public CreatureScript
{
public:
    npc_prince_liam_greymane_intro() : CreatureScript("npc_prince_liam_greymane_intro") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_introAI (creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14078)
            if (Creature* citizen = creature->FindNearestCreature(34851, 20.0f))
                citizen->AI()->Talk(0);

        return true;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* /*quest*/, uint32 /*opt*/)
    {
        player->CLOSE_GOSSIP_MENU();
        player->SaveToDB();
        return true;
    }

    struct npc_prince_liam_greymane_introAI : public ScriptedAI
    {
        npc_prince_liam_greymane_introAI(Creature *c) : ScriptedAI(c) {}

        uint32 uiSayTimer;

        void Reset()
        {
            uiSayTimer = 1000;
        }

        void UpdateAI(uint32 diff)
        {
            if (uiSayTimer <= diff)
            {
                Talk(0);
                uiSayTimer = urand(12000, 18000);
            }
            else
                uiSayTimer -= diff;
        }
    };
};

///////////
// Quest Royal Orders 14099
///////////
class npc_prince_liam_greymane_phase_1 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase_1() : CreatureScript("npc_prince_liam_greymane_phase_1") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase_1AI (creature);
    }

    struct npc_prince_liam_greymane_phase_1AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase_1AI(Creature *c) : ScriptedAI(c)
        {
            SetCombatMovement(false);
            me->m_CombatDistance = 10.0f;
        }

        uint32 uiSayTimer;
        uint32 uiShootTimer;
        bool miss;

        void Reset()
        {
            uiSayTimer = urand(5000, 10000);
            uiShootTimer = 1500;
            miss = false;
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;
                Unit* target = NULL;

                if (target = me->FindNearestCreature(NPC_RAMPAGING_WORGEN, 40.0f))
                    if (target != me->getVictim())
                    {
                        me->getThreatManager().modifyThreatPercent(me->getVictim(), -100);
                        me->CombatStart(target);
                        me->AddThreat(target, 1000);
                    }

                    if (!me->IsWithinMeleeRange(me->getVictim(), 0.0f))
                    {
                        me->Attack(me->getVictim(), false);
                        me->CastSpell(me->getVictim(), SPELL_SHOOT, false);
                    }
                    else
                        me->Attack(me->getVictim(), true);
            }
            else
                uiShootTimer -= diff;

            if (uiSayTimer <= diff)
            {
                uiSayTimer = urand(30000, 120000);
                Talk(0);
            }
            else
                uiSayTimer -= diff;

            if (me->getVictim()->GetTypeId() == TYPEID_UNIT)
                if (me->getVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_rampaging_worgen : public CreatureScript
{
public:
    npc_rampaging_worgen() : CreatureScript("npc_rampaging_worgen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgenAI (creature);
    }

    struct npc_rampaging_worgenAI : public ScriptedAI
    {
        npc_rampaging_worgenAI(Creature *c) : ScriptedAI(c) {}

        uint32 uiEnemyEntry;
        bool enrage;
        bool miss;

        void Reset()
        {
            enrage = false;
            miss = false;

            if (me->GetEntry() == NPC_AFFLICTED_GILNEAN)
                me->m_CombatDistance = 3.0f;
            else
                me->m_CombatDistance = 10.0f;

            switch(me->GetEntry())
            {
            case NPC_RAMPAGING_WORGEN:
                uiEnemyEntry = NPC_GILNEAS_CITY_GUARD;
                break;
            case NPC_BLOODFANG_WORGEN:
                uiEnemyEntry = NPC_GILNEAN_ROYAL_GUARD;
                break;
            case NPC_FRENZIED_STALKER:
                uiEnemyEntry = NPC_NORTHGATE_REBEL;
                break;
            default:
                uiEnemyEntry = 0;
                break;
            }
        }

        void DamageTaken(Unit* attacker, uint32 &/*damage*/)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                return;

            Unit* victim = NULL;

            if (victim = me->getVictim())
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    return;

            if (victim)
                me->getThreatManager().modifyThreatPercent(victim, -100);

            AttackStart(attacker);
            me->AddThreat(attacker, 10005000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                DoCast(me, SPELL_ENRAGE);
                enrage = true;
            }

            if (me->getVictim() && me->getVictim()->GetTypeId() == TYPEID_UNIT)
                if (me->getVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_gilneas_city_guard : public CreatureScript
{
public:
    npc_gilneas_city_guard() : CreatureScript("npc_gilneas_city_guard") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guardAI (creature);
    }

    struct npc_gilneas_city_guardAI : public ScriptedAI
    {
        npc_gilneas_city_guardAI(Creature *c) : ScriptedAI(c)
        {
            SetCombatMovement(false);
            uiEmoteState = me->GetUInt32Value(UNIT_NPC_EMOTESTATE);
        }

        uint32 uiYellTimer;
        uint32 uiEnemyEntry;
        uint32 uiShootTimer;
        uint32 uiEmoteState;
        bool miss;
        bool CanSay;

        void Reset()
        {
            uiYellTimer = urand(25000, 75000);
            uiShootTimer = 1000;
            miss = false;
            CanSay = false;
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, uiEmoteState);

            switch(me->GetEntry())
            {
            case NPC_GILNEAS_CITY_GUARD:
                uiEnemyEntry = NPC_RAMPAGING_WORGEN;
                break;
            case NPC_GILNEAN_ROYAL_GUARD:
                uiEnemyEntry = NPC_BLOODFANG_WORGEN;
                break;
            case NPC_GILNEAS_CITY_GUARD_PHASE_4:
                CanSay = true;
                uiEnemyEntry = NPC_AFFLICTED_GILNEAN;
                break;
            case NPC_NORTHGATE_REBEL_PHASE_5:
                uiEnemyEntry = NPC_BLOODFANG_STALKER_PHASE_5;
                break;
            case NPC_NORTHGATE_REBEL:
                uiEnemyEntry = NPC_FRENZIED_STALKER;
                break;
            default:
                uiEnemyEntry = 0;
                break;
            }

            if (me->GetEntry() == NPC_GILNEAS_CITY_GUARD_PHASE_4)
            {
                me->m_CombatDistance = 3.0f;
                SetCombatMovement(false);
            }
            else
                me->m_CombatDistance = 10.0f;

            if (me->GetDistance2d(-1770.2f, 1343.78f) < 25.0f)
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            if (Unit* target = me->FindNearestCreature(uiEnemyEntry, 40.0f))
                AttackStart(target);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (CanSay)
                if (uiYellTimer <= diff)
                {
                    uiYellTimer = urand(50000, 100000);
                    Talk(0);
                }
                else
                    uiYellTimer -= diff;

            if (me->getVictim()->GetTypeId() == TYPEID_UNIT)
                if (me->getVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 2500;
                Unit* target = NULL;

                if (!me->IsWithinMeleeRange(me->getVictim(), 0.0f))
                    if (uiEnemyEntry)
                        if (target = me->FindNearestCreature(uiEnemyEntry, 40.0f))
                            if (target != me->getVictim())
                            {
                                me->getThreatManager().modifyThreatPercent(me->getVictim(), -100);
                                me->CombatStart(target);
                                me->AddThreat(target, 1000);
                            }

                            if (!me->IsWithinMeleeRange(me->getVictim(), 0.0f))
                            {
                                if (me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                                {
                                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                                    me->ClearUnitState(UNIT_STATE_MELEE_ATTACKING);
                                    me->SendMeleeAttackStop(me->getVictim());
                                }

                                me->CastSpell(me->getVictim(), SPELL_SHOOT, false);
                            }
                            else
                                if (!me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                                {
                                    me->AddUnitState(UNIT_STATE_MELEE_ATTACKING);
                                    me->SendMeleeAttackStart(me->getVictim());
                                }
            }
            else
                uiShootTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Evacuate the Merchant Square 14098
///////////

enum qEMS
{
    NPC_J_CITIZEN                = 34981,
    NPC_CW_WORGEN                = 35660,
    NPC_CW_CITIZEN               = 35836,
    NPC_QEMS_KILL_CREDIT         = 35830,

    SPELL_CW_WORGEN_ENRAGE       = 56646,

    ACTION_JUST_CITIZEN          = 1,
    ACTION_CITIZEN_AND_WORGEN    = 2,
};

class npc_qems_citizen : public CreatureScript
{
public:
    npc_qems_citizen() : CreatureScript("npc_qems_citizen") {}

    struct npc_qems_citizenAI : public npc_escortAI
    {
        npc_qems_citizenAI(Creature *c) : npc_escortAI(c)
        {
            me->SetReactState(REACT_PASSIVE);
            uiEventTimer = 1000;
            pause = false;
        }

        uint32 uiEventTimer;
        bool pause;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
            {
                if (me->isSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                            player->KilledMonsterCredit(NPC_QEMS_KILL_CREDIT, 0);

                SetEscortPaused(true);
                pause = true;

                if (me->GetEntry() == NPC_J_CITIZEN)
                    Talk(0);
                else
                {
                    Talk(0);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_COWER);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (pause)
                if (uiEventTimer <= diff)
                {
                    pause = false;
                    SetEscortPaused(false);
                }
                else
                    uiEventTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_qems_citizenAI(creature);
    }
};

class npc_qems_worgen : public CreatureScript
{
public:
    npc_qems_worgen() : CreatureScript("npc_qems_worgen") {}

    struct npc_qems_worgenAI : public npc_escortAI
    {
        npc_qems_worgenAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            uiPauseTimer = 4000;
            enrage = false;
            pause = true;
        }

        uint32 uiPauseTimer;
        bool pause;
        bool enrage;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                if (me->isSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        AttackStart(summoner);
                    else
                        me->DespawnOrUnsummon();
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (pause)
                if (uiPauseTimer <= diff)
                {
                    pause = false;
                    SetEscortPaused(false);
                }
                else
                    uiPauseTimer -= diff;

            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                DoCast(SPELL_CW_WORGEN_ENRAGE);
                enrage = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_qems_worgenAI(creature);
    }
};

class go_merchant_square_door : public GameObjectScript
{
public:
    go_merchant_square_door() : GameObjectScript("go_merchant_square_door") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        uint8 roll = urand(ACTION_JUST_CITIZEN, ACTION_CITIZEN_AND_WORGEN);

        switch (roll)
        {
        case ACTION_JUST_CITIZEN:
            SummonQuestCreature(NPC_J_CITIZEN, true, go, player);
            break;
        case ACTION_CITIZEN_AND_WORGEN:
            SummonQuestCreature(NPC_CW_CITIZEN, true, go, player);
            SummonQuestCreature(NPC_CW_WORGEN, false, go, player);
            break;
        }

        return false;
    }

    void SummonQuestCreature(uint32 entry, bool IsCitizen, GameObject* go, Player* player)
    {
        if (!player)
            return;

        float x, y;
        go->GetNearPoint2D(x, y, 2.8f, go->GetOrientation() + M_PI * 0.75f);

        if (Creature* creature = player->SummonCreature(entry, x, y, go->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000))
        {
            creature->SetPhaseMask(2, true);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            npc_escortAI* npc_escort = NULL;

            if (IsCitizen)
                npc_escort = CAST_AI(npc_qems_citizen::npc_qems_citizenAI, creature->AI());
            else
                npc_escort = CAST_AI(npc_qems_worgen::npc_qems_worgenAI, creature->AI());

            if (!npc_escort)
                return;

            float x, y, z = creature->GetPositionZ();
            go->GetNearPoint2D(x, y, 1.0f, go->GetOrientation() + M_PI);
            npc_escort->AddWaypoint(0, x, y, z);
            go->GetNearPoint2D(x, y, 3.0f, go->GetOrientation());
            npc_escort->AddWaypoint(1, x, y, z);

            if (IsCitizen)
            {
                float x, y;
                go->GetNearPoint2D(x, y, 10.0f, go->GetOrientation());
                const Position src = {x, y, go->GetPositionZ(), 0};
                Position dst;
                go->GetRandomPoint(src, 5.0f, dst);
                npc_escort->AddWaypoint(2, dst.GetPositionX(), dst.GetPositionY(), z);
            }

            npc_escort->Start(false, true);
            npc_escort->SetDespawnAtEnd(IsCitizen);
            npc_escort->SetEscortPaused(!IsCitizen);
        }
    }
};

///////////
// Quest Old Divisions 14157
///////////

enum eQOD
{
    QUEST_OLD_DIVISIONS               = 14157,

    NPC_LORD_GODFREY_QOD              = 35115,
    NPC_KING_GENN_GREYMANE_QOD        = 35112,
};

struct Psc
{
    uint64 uiPlayerGUID;
    uint32 uiPersonalTimer;
};

class npc_king_genn_greymane_qod : public CreatureScript
{
public:
    npc_king_genn_greymane_qod() : CreatureScript("npc_king_genn_greymane_qod") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_qodAI (creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_OLD_DIVISIONS)
            if (Creature* godfrey = creature->FindNearestCreature(NPC_LORD_GODFREY_QOD, 20.0f))
            {
                player->CLOSE_GOSSIP_MENU();
                godfrey->AI()->Talk(0);
                Psc new_psc;
                new_psc.uiPersonalTimer = 5000;
                new_psc.uiPlayerGUID = player->GetGUID();
                CAST_AI(npc_king_genn_greymane_qodAI, creature->AI())->lPlayerList.push_back(new_psc);
            }

            return true;
    }

    struct npc_king_genn_greymane_qodAI : public ScriptedAI
    {
        npc_king_genn_greymane_qodAI(Creature* creature) : ScriptedAI(creature) {}

        std::list<Psc> lPlayerList;

        void UpdateAI(uint32 diff)
        {
            if (lPlayerList.empty())
                return;

            for (std::list<Psc>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                if ((*itr).uiPersonalTimer <= diff)
                {
                    me->AI()->Talk(1);
                    itr = lPlayerList.erase(itr);
                }
                else
                {
                    (*itr).uiPersonalTimer -= diff;
                    ++itr;
                }
        }
    };
};

///////////
// Quest By the Skin of His Teeth 14154
///////////
static float WorgenPosT1[4][4] =
{
    {-1718.18f,1526.45f,55.9076f,4.74478f},
    {-1718.06f,1515.83f,55.3631f,4.73569f},
    {-1718.02f,1487.10f,57.0588f,4.64537f},
    {-1701.28f,1470.35f,52.2872f,5.55485f},
};

static float WorgenPosT2[8][4] =
{
    {-1634.06f,1486.73f,73.3780f,0.76234f},
    {-1635.34f,1487.13f,72.2655f,0.89272f},
    {-1635.80f,1488.80f,71.0234f,0.79533f},
    {-1630.88f,1483.50f,72.9698f,0.75763f},
    {-1629.91f,1482.39f,71.7020f,0.71836f},
    {-1628.88f,1481.65f,70.6151f,0.69480f},
    {-1633.23f,1484.80f,74.9893f,0.77727f},
    {-1672.09f,1448.92f,52.2870f,0.78175f},
};

enum eQPR
{
    QUEST_BY_THE_SKIN_OF_HIS_TEETH             = 14154,

    NPC_WORGEN_RUNT_FW                         = 35456,
    NPC_WORGEN_RUNT_SW                         = 35188,
    NPC_WORGEN_ALPHA_FW                        = 35170,
    NPC_WORGEN_ALPHA_SW                        = 35167,

    SPELL_HORRIFYING_HOWL                      = 75355,
    SPELL_DEMORALIZING_SHOUT                   = 61044,
    SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST    = 66914,

    TYPE_FIRST_WAVE                            = 0,
    TYPE_SECOND_WAVE                           = 1,

    ACTION_START_EVENTR                        = 3,
};

class npc_worgen_attacker : public CreatureScript
{
public:
    npc_worgen_attacker() : CreatureScript("npc_worgen_attacker") {}

    struct npc_worgen_attackerAI : public npc_escortAI
    {
        npc_worgen_attackerAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            enrage = false;
            uiHorrifyingHowlTimer = 3000;
        }

        bool enrage;
        uint32 uiHorrifyingHowlTimer;

        void StartAttack()
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);

            if (me->isSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    me->CombatStart(summoner);
                    me->AddThreat(summoner, 100500);
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 2)
                if (me->GetEntry() == NPC_WORGEN_ALPHA_SW || NPC_WORGEN_RUNT_SW)
                    StartAttack();

            if (point == 5)
                StartAttack();
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                enrage = true;
                DoCast(SPELL_ENRAGE);
            }

            if (uiHorrifyingHowlTimer <= diff)
            {
                uiHorrifyingHowlTimer = 15000;
                DoCast(SPELL_HORRIFYING_HOWL);
            }
            else
                uiHorrifyingHowlTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_worgen_attackerAI(creature);
    }
};

class npc_lord_darius_crowley : public CreatureScript
{
public:
    npc_lord_darius_crowley() : CreatureScript("npc_lord_darius_crowley") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BY_THE_SKIN_OF_HIS_TEETH)
        {
            creature->CastSpell(player, SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST, true);
            creature->AI()->DoAction(ACTION_START_EVENTR);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_darius_crowleyAI (creature);
    }

    struct npc_lord_darius_crowleyAI : public ScriptedAI
    {
        npc_lord_darius_crowleyAI(Creature* c) : ScriptedAI(c)
        {
            Event = false;
            uiEventTimer = 120000;
            uiSummonTimer = 3000;
            uiDShoutTimer = 15000;
            uiType = TYPE_FIRST_WAVE;
            SetCombatMovement(false);
        }

        uint32 uiDShoutTimer;
        uint32 uiSummonTimer;
        uint32 uiEventTimer;
        uint8 uiType;
        bool Event;

        void DoAction(int32 action)
        {
            if (action == ACTION_START_EVENTR)
            {
                Event = true;
                uiEventTimer = 120000;
            }
        }

        void GetNearPoint2D(float src_x, float src_y, float &dst_x, float &dst_y, float distance2d, float absAngle) const
        {
            dst_x = src_x + distance2d * cos(absAngle);
            dst_y = src_y + distance2d * sin(absAngle);

            Trinity::NormalizeMapCoord(dst_x);
            Trinity::NormalizeMapCoord(dst_y);
        }

        void SummonWorgen(uint32 entry, uint8 id)
        {
            float x, y;
            GetNearPoint2D(WorgenPosT2[id][0], WorgenPosT2[id][1], x, y, 3.0f + rand()%90, WorgenPosT2[id][3]);

            if (Creature* worgen = me->SummonCreature(entry, x, y, WorgenPosT2[id][2] + 2.0f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000))
                if (npc_escortAI* npc_escort = CAST_AI(npc_worgen_attacker::npc_worgen_attackerAI, worgen->AI()))
                {
                    npc_escort->AddWaypoint(0, WorgenPosT2[id][0], WorgenPosT2[id][1], WorgenPosT2[id][2], 0, true);
                    const Position src = {WorgenPosT2[7][0], WorgenPosT2[7][1], WorgenPosT2[7][2], WorgenPosT2[7][3]};
                    Position dst;
                    worgen->GetRandomPoint(src, 5.0f, dst);
                    npc_escort->AddWaypoint(1, dst.GetPositionX(), dst.GetPositionY(), dst.GetPositionZ());
                    npc_escort->AddWaypoint(2, -1679.73f,1442.12f,52.3705f);
                    npc_escort->Start(true, true);
                    npc_escort->SetDespawnAtEnd(false);
                }
        }

        void SummonFirstWave()
        {
            if (Creature* worgen = me->SummonCreature(NPC_WORGEN_ALPHA_FW, WorgenPosT1[0][0], WorgenPosT1[0][1], WorgenPosT1[0][2], WorgenPosT1[0][3], TEMPSUMMON_DEAD_DESPAWN, 500))
                for (int i = 0; i < 2; ++i)
                {
                    float x, y;
                    worgen->GetNearPoint2D(x, y, urand(1, 4), WorgenPosT1[0][3] + M_PI / 2);
                    me->SummonCreature(NPC_WORGEN_RUNT_FW, x, y, WorgenPosT1[0][2], WorgenPosT1[0][3], TEMPSUMMON_DEAD_DESPAWN, 500);
                    worgen->GetNearPoint2D(x, y, urand(1, 5), WorgenPosT1[0][3] - M_PI / 2);
                    me->SummonCreature(NPC_WORGEN_RUNT_FW, x, y, WorgenPosT1[0][2], WorgenPosT1[0][3], TEMPSUMMON_DEAD_DESPAWN, 500);
                }
        }

        void SummonSecondWave()
        {
            SummonWorgen(NPC_WORGEN_ALPHA_SW, 6);

            for (int i = 0; i < 4; ++i)
            {
                uint8 roll = urand(0, 5);
                SummonWorgen(NPC_WORGEN_RUNT_SW, roll);
            }
        }

        void JustSummoned(Creature* summoned)
        {
            if (summoned->GetEntry() == NPC_WORGEN_ALPHA_FW || summoned->GetEntry() == NPC_WORGEN_RUNT_FW)
                if (npc_escortAI* worgen = CAST_AI(npc_worgen_attacker::npc_worgen_attackerAI, summoned->AI()))
                {
                    worgen->AddWaypoint(1, WorgenPosT1[0][0], WorgenPosT1[0][1], WorgenPosT1[0][2]);
                    worgen->AddWaypoint(2, WorgenPosT1[1][0], WorgenPosT1[1][1], WorgenPosT1[1][2]);
                    worgen->AddWaypoint(3, WorgenPosT1[2][0], WorgenPosT1[2][1], WorgenPosT1[2][2], 0, true);
                    worgen->AddWaypoint(4, WorgenPosT1[3][0], WorgenPosT1[3][1], WorgenPosT1[3][2]);
                    worgen->AddWaypoint(5, -1679.73f,1442.12f,52.3705f);
                    worgen->Start(true, true);
                    worgen->SetDespawnAtEnd(false);
                }
        }

        void UpdateAI(uint32 diff)
        {
            if (Event)
            {
                if (uiSummonTimer <= diff)
                {
                    uiSummonTimer = 15000;

                    switch (uiType)
                    {
                    case TYPE_FIRST_WAVE:
                        uiType = TYPE_SECOND_WAVE;
                        SummonFirstWave();
                        break;
                    case TYPE_SECOND_WAVE:
                        uiType = TYPE_FIRST_WAVE;
                        SummonSecondWave();
                        break;
                    }
                }
                else
                    uiSummonTimer -= diff;

                if (uiEventTimer <= diff)
                    Event = false;
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (uiDShoutTimer <= diff)
            {
                uiDShoutTimer = 15000;
                DoCast(SPELL_DEMORALIZING_SHOUT);
            }
            else
                uiDShoutTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_gilneas()
{
    // Intro stuffs
    new npc_panicked_citizen_gate();
    new npc_gilneas_city_guard_gate();
    new npc_gilnean_crow();
    new npc_prince_liam_greymane_intro();

    // QUEST - 14099 - Royal Orders
    new npc_prince_liam_greymane_phase_1();
    new npc_rampaging_worgen();
    new npc_gilneas_city_guard();

    // QUEST - 14098 - Evacuate the Merchant Square
    new npc_qems_citizen();
    new npc_qems_worgen();
    new go_merchant_square_door();

    // Quest - 14157 - Old Divisions
    new npc_king_genn_greymane_qod();

    // QUEST - 14154 - By The Skin of His Teeth
    new npc_worgen_attacker();
    new npc_lord_darius_crowley();
}