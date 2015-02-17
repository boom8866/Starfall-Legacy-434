
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
#include "Vehicle.h"
#include "WaypointManager.h"
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
##  Working - [The Rebel Lord's Arsenal]
##  Working - [From the Shadows]
##  Working - [Message to Greymane]
##  Working - [Save Krennan Aranas]
##  Working - [Time to Regroup]
##  Working - [Sacrifices]
##  Working - [By Blood and Ash]
##  Working - [Never Surrender, Sometimes Retreat]
##  Working - [Last Stand]
##  Working - [Last Chance at Humanity]
######*/

const uint16 PanickedCitizenRandomEmote[5] =
{
    EMOTE_ONESHOT_COWER,
    EMOTE_ONESHOT_TALK,
    EMOTE_ONESHOT_CRY,
    EMOTE_ONESHOT_BEG,
    EMOTE_ONESHOT_EXCLAMATION
};

enum eAttackedCreatures
{
    NPC_AFFLICTED_GILNEAN            = 50471,
    NPC_RAMPAGING_WORGEN             = 34884,
    NPC_FRENZIED_STALKER             = 35627,
    NPC_NORTHGATE_REBEL              = 41015,
    NPC_GILNEAS_CITY_GUARD_PHASE_4   = 50474,
    NPC_NORTHGATE_REBEL_PHASE_5      = 36057,
    NPC_BLOODFANG_STALKER_PHASE_5    = 35229
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
            uiRandomEmoteTimer = urand(10000, 40000);
        }

        uint32 uiRandomEmoteTimer;

        void UpdateAI(uint32 diff)
        {
            if (uiRandomEmoteTimer <= diff)
            {
                uiRandomEmoteTimer = urand(8000, 15500);
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
    EVENT_SEEK  = 2
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

        void Reset()
        {
            checkPlayer = 2500;
            isMoving = false;
            me->SetPosition(me->GetCreatureData()->posX,me->GetCreatureData()->posY, me->GetCreatureData()->posZ, me->GetCreatureData()->orientation);
            events.ScheduleEvent(EVENT_SPAWN, urand(1000, 3000));
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_PING_GILNEAN_CROW)
            {
                if (!isMoving)
                {
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE , EMOTE_ONESHOT_NONE);
                    me->SetCanFly(true);
                    isMoving = true;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (checkPlayer <= diff)
            {
                if (Player* nearestPlayer = me->FindNearestPlayer(18.0f, true))
                    nearestPlayer->CastSpell(nearestPlayer, SPELL_PING_GILNEAN_CROW, true);
                checkPlayer = 2500;
            }
            else
                checkPlayer -= diff;

            if (!isMoving)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPAWN:
                    {
                        me->GetMotionMaster()->MovePoint(0, (me->GetPositionX() + irand(-15, 15)), (me->GetPositionY() + irand(-15, 15)), (me->GetPositionZ() + irand(5, 15)), false);
                        me->DespawnOrUnsummon(3500);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool isMoving;
        EventMap events;
        uint16 checkPlayer;
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
                if (Player *tar = me->FindNearestPlayer(0.5f,true))
                    if (!(tar->GetExtraFlags() & PLAYER_EXTRA_WATCHING_MOVIE))
                    {
                        Talk(0);
                        uiSayTimer = urand(12000, 18000);
                    }
                    else
                        uiSayTimer = urand(12000, 18000);
            }
            else
                uiSayTimer -= diff;
        }
    };
};

class npc_gilneas_wounded_guard : public CreatureScript
{
public:
    npc_gilneas_wounded_guard() : CreatureScript("npc_gilneas_wounded_guard") { }

    enum eventId
    {
        EVENT_SET_RANDOM_HEALTH     = 1
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_wounded_guardAI (creature);
    }

    struct npc_gilneas_wounded_guardAI : public ScriptedAI
    {
        EventMap events;

        npc_gilneas_wounded_guardAI(Creature *c) : ScriptedAI(c)
        {
            SetCombatMovement(false);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            events.ScheduleEvent(EVENT_SET_RANDOM_HEALTH, 2000);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            switch (spell->Id)
            {
                case 774:   // Rejuvenation
                case 2061:  // Flash Heal
                {
                    caster->ToPlayer()->KilledMonsterCredit(44175, 0);
                    events.RescheduleEvent(EVENT_SET_RANDOM_HEALTH, urand(10000, 25000));
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
                    case EVENT_SET_RANDOM_HEALTH:
                    {
                        me->SetHealth(me->GetMaxHealth() * (frand(0.3f, 0.5f)));
                        events.RescheduleEvent(EVENT_SET_RANDOM_HEALTH, urand(60000, 75000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };
};

class npc_sergeant_cleese : public CreatureScript
{
public:
    npc_sergeant_cleese() : CreatureScript("npc_sergeant_cleese") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sergeant_cleeseAI (creature);
    }

    struct npc_sergeant_cleeseAI : public ScriptedAI
    {
        npc_sergeant_cleeseAI(Creature* creature) : ScriptedAI(creature) {}

        void DamageTaken(Unit* who, uint32& damage)
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_mariam_spellwalker : public CreatureScript
{
public:
    npc_mariam_spellwalker() : CreatureScript("npc_mariam_spellwalker") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mariam_spellwalkerAI (creature);
    }

    struct npc_mariam_spellwalkerAI : public ScriptedAI
    {
        npc_mariam_spellwalkerAI(Creature* creature) : ScriptedAI(creature) {}

        void DamageTaken(Unit* who, uint32& damage)
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->getVictim()->GetEntry() == NPC_BLOODFANG_WORGEN)
                DoSpellAttackIfReady(SPELL_FROSTBOLT_VISUAL_ONLY);
            else
                DoMeleeAttackIfReady();
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

    enum eventId
    {
        EVENT_SEARCH_FOR_GUARDS     = 1
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgenAI (creature);
    }

    struct npc_rampaging_worgenAI : public ScriptedAI
    {
        npc_rampaging_worgenAI(Creature *c) : ScriptedAI(c) {}

        EventMap events;

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

            events.ScheduleEvent(EVENT_SEARCH_FOR_GUARDS, urand(2000,5000));
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
            {
                if (attacker->ToCreature()->GetEntry() == NPC_GILNEAS_CITY_GUARD ||
                    attacker->ToCreature()->GetEntry() == NPC_GILNEAN_ROYAL_GUARD)
                {
                    damage = 0;
                    return;
                }
            }

            Unit* victim = NULL;

            if (victim = me->getVictim())
                me->getThreatManager().modifyThreatPercent(victim, -100);

            AttackStart(attacker);
            me->AddThreat(attacker, 10005000);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (me->GetEntry() == NPC_BLOODFANG_WORGEN)
            {
                switch (spell->Id)
                {
                    case 100:   // Charge
                    case 348:   // Immolate
                    case 2098:  // Eviscerate
                    case 56641: // Steady Shot
                    case 5143:  // Arcane Missile
                    {
                        caster->ToPlayer()->KilledMonsterCredit(44175, 0);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEARCH_FOR_GUARDS:
                    {
                        if (!me->isInCombat())
                        {
                            if (Creature* guard = me->FindNearestCreature(NPC_GILNEAS_CITY_GUARD, 8.5f, true))
                                AttackStart(guard);
                            events.RescheduleEvent(EVENT_SEARCH_FOR_GUARDS, urand(5000, 10000));
                        }
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                DoCast(me, SPELL_ENRAGE);
                enrage = true;
            }

            if (me->getVictim() && me->getVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->getVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

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

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                damage = 0;
        }

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
    NPC_KING_GENN_GREYMANE_QOD        = 35112
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
        {
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

            for (std::list<Psc>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end();)
            {
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

///////////
// Quest The Rebel Lord's Arsenal 14159
///////////
enum qTRLA
{
    QUEST_THE_REBEL_LORD_ARSENAL    = 14159,

    NPC_LORNA_CROWLEY               = 35378,
    NPC_JOSIAH_AVERY_WORGEN         = 35370,

    SPELL_ZONE_SPECIFIC_01          = 59073,
    SPELL_WORGEN_BITE               = 72870,
    SPELL_PULL_TO                   = 67357,// not work
};
bool done;

class npc_josiah_avery_worgen : public CreatureScript
{
public:
    npc_josiah_avery_worgen() : CreatureScript("npc_josiah_avery_worgen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_josiah_avery_worgenAI (creature);
    }

    struct npc_josiah_avery_worgenAI : public ScriptedAI
    {
        npc_josiah_avery_worgenAI(Creature* creature) : ScriptedAI(creature)
        {
            uiEventTimer = 500;
            uiPase = 1;
            uiPlayerGUID = 0;
            me->SetReactState(REACT_PASSIVE);

            if (me->isSummon())
                Event = true;
            else
                Event = false;
        }

        uint64 uiPlayerGUID;
        uint32 uiEventTimer;
        uint8 uiPase;
        bool Event;

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == 7105)
                me->Kill(me);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(3000);
        }

        void UpdateAI(uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f))
                    {
                        switch (uiPase)
                        {
                            case 1:
                            {
                                ++uiPase;
                                uiEventTimer = 1000;
                                if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                                {
                                    float x, y, z;
                                    lorna->GetPosition(x, y, z);
                                    me->CastSpell(player, 91074, false);
                                    player->GetMotionMaster()->MoveJump(x, y, z, 18.0f, 5.0f);
                                    lorna->AI()->Talk(1, player->GetGUID());
                                }
                                break;
                            }
                            case 2:
                            {
                                Event = false;
                                uiEventTimer = 3000;
                                float x, y, z;
                                lorna->GetPosition(x, y, z);
                                me->GetMotionMaster()->MoveJump(x, y, z, 18.0f, 10.0f);
                                lorna->CastSpell(me, 7105, false);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_josiah_avery_human : public CreatureScript
{
public:
    npc_josiah_avery_human() : CreatureScript("npc_josiah_avery_human") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_THE_REBEL_LORD_ARSENAL)
        {
            player->CastSpell(player, SPELL_WORGEN_BITE, true);
            float p_x, p_y;
            player->GetPosition(p_x, p_y);
            float x, y, z, o = creature->GetAngle(p_x, p_y);
            creature->GetPosition(x, y, z);
            player->SaveToDB();

            if (Creature* josiah = player->SummonCreature(NPC_JOSIAH_AVERY_WORGEN, x, y, z, o, TEMPSUMMON_CORPSE_DESPAWN, 10000))
            {
                CAST_AI(npc_josiah_avery_worgen::npc_josiah_avery_worgenAI, josiah->AI())->uiPlayerGUID = player->GetGUID();
                josiah->SetSeerGUID(player->GetGUID());
                creature->DespawnOrUnsummon(1);
            }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_josiah_avery_humanAI (creature);
    }

    struct npc_josiah_avery_humanAI : public ScriptedAI
    {
        npc_josiah_avery_humanAI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomSpeachTimer = urand(5000, 15000);
            me->SetVisible(true);
        }

        uint32 uiRandomSpeachTimer;

        void UpdateAI(uint32 diff)
        {
            if (uiRandomSpeachTimer <= diff)
            {
                uiRandomSpeachTimer = urand(5000, 15000);
                uint8 roll = urand(0, 5);
                Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

                if (PlList.isEmpty())
                    return;

                float z = me->GetPositionZ();
                uint32 uiPhase = me->GetPhaseMask();

                for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                    if (Player* player = i->getSource())
                        if (uiPhase == player->GetPhaseMask())
                            if (me->GetDistance(player) < 35.0f)
                                if (abs(z - player->GetPositionZ()) < 5.0f)
                                    Talk(1);
            }
            else
                uiRandomSpeachTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest From the Shadows 14204
///////////

enum qFS
{
    QUEST_FROM_THE_SHADOWS         = 14204,

    NPC_GILNEAS_MASTIFF            = 35631,

    SPELL_SUMMON_MASTIFF           = 67807,
    SPELL_ATTACK_LURKER            = 67805,
    SPELL_SHADOWSTALKER_STEALTH    = 5916,
    SPELL_UNDYING_FRENZY           = 80515,
};

class npc_lorna_crowley_qfs : public CreatureScript
{
public:
    npc_lorna_crowley_qfs() : CreatureScript("npc_lorna_crowley_qfs") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
        {
            if(player->getClass() == CLASS_HUNTER)
                player->TemporaryUnsummonPet();

            player->CastSpell(player, SPELL_SUMMON_MASTIFF, false);
            creature->AI()->Talk(0);
        }
        return true;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
            if (Unit* charm = Unit::GetCreature(*creature, player->GetMinionGUID()))
                if (charm->GetEntry() == NPC_GILNEAS_MASTIFF)
                    if (Creature* mastiff = charm->ToCreature())
                        mastiff->DespawnOrUnsummon();

        if(player->getClass() == CLASS_HUNTER)
            player->ResummonTemporaryUnsummonedPet();

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lorna_crowley_qfsAI (creature);
    }

    struct npc_lorna_crowley_qfsAI : public ScriptedAI
    {
        npc_lorna_crowley_qfsAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;
        }
    };
};

/*######
# npc_gilnean_mastiff
######*/

class npc_gilnean_mastiff : public CreatureScript
{
public:
    npc_gilnean_mastiff() : CreatureScript("npc_gilnean_mastiff") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilnean_mastiffAI(creature);
    }

    struct npc_gilnean_mastiffAI : public ScriptedAI
    {
        npc_gilnean_mastiffAI(Creature* creature) : ScriptedAI(creature) 
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, 67805, true);
        }

        void Reset()
        {
            me->GetCharmInfo()->InitEmptyActionBar(false);
            me->GetCharmInfo()->SetActionBar(0, SPELL_ATTACK_LURKER, ACT_PASSIVE);
            me->SetReactState(REACT_DEFENSIVE);
            me->GetCharmInfo()->SetIsFollowing(true);
        }

        void UpdateAI(uint32 /*diff*/)
        {
            Player* player = me->GetOwner()->ToPlayer();

            if (player->GetQuestStatus(QUEST_FROM_THE_SHADOWS) == QUEST_STATUS_REWARDED)
                me->DespawnOrUnsummon(1);

            if (!UpdateVictim())
            {
                me->GetCharmInfo()->SetIsFollowing(true);
                me->SetReactState(REACT_DEFENSIVE);
                return;
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) // Otherwise, player is stuck with pet corpse they cannot remove from world
        {
            me->DespawnOrUnsummon(1);
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Reset();
        }
    };
};

class npc_bloodfang_lurker : public CreatureScript
{
public:
    npc_bloodfang_lurker() : CreatureScript("npc_bloodfang_lurker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bloodfang_lurkerAI (creature);
    }

    struct npc_bloodfang_lurkerAI : public ScriptedAI
    {
        npc_bloodfang_lurkerAI(Creature* creature) : ScriptedAI(creature){}

        bool enrage;
        bool frenzy;

        void Reset()
        {
            enrage = false;
            frenzy = false;
            DoCast(SPELL_SHADOWSTALKER_STEALTH);
            me->SetReactState(REACT_PASSIVE);
        }

        void StartAttack(Unit* who)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetInCombatWith(who);
            who->SetInCombatWith(me);
            me->AddThreat(who, 100500);
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (me->HasReactState(REACT_PASSIVE))
                StartAttack(attacker);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_ATTACK_LURKER)
                StartAttack(caster);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!frenzy && me->HealthBelowPct(45))
            {
                frenzy = true;
                DoCast(SPELL_UNDYING_FRENZY);
            }

            if (!enrage && me->HealthBelowPct(30))
            {
                enrage = true;
                DoCast(SPELL_ENRAGE);
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## spell_attack_lurker 67805
######*/
class spell_attack_lurker : public SpellScriptLoader
{
public:
    spell_attack_lurker() : SpellScriptLoader("spell_attack_lurker") { }

    class spell_attack_lurker_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_attack_lurker_SpellScript);

        void HandleDummy()
        {
            Unit* caster = GetCaster();
            if (Creature* target = caster->FindNearestCreature(35463, 30.0f))
            {
                float x,y,z,o;
                target->GetContactPoint(caster, x, y, z, CONTACT_DISTANCE);
                o = caster->GetOrientation();
                float speedXY, speedZ;
                speedZ = 10.0f;
                speedXY = caster->GetExactDist2d(x, y) * 30.0f / speedZ;
                caster->GetMotionMaster()->MoveCharge(x, y, z, speedXY, speedZ);
                target->RemoveAura(5916);
                target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                target->SetReactState(REACT_AGGRESSIVE);
                target->AI()->AttackStart(caster);
                target->AddThreat(caster, 10005000);
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_attack_lurker_SpellScript::HandleDummy);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_attack_lurker_SpellScript();
    }
};

///////////
// Quest Save Krennan Aranas 14293
///////////

enum qSKA
{
    QUEST_SAVE_KRENNAN_ARANAS      = 14293,

    NPC_GENN_HORSE                 = 35905,
    NPC_KRENNAN_ARANAS             = 35753,
    NPC_KRENNAN_ARANAS_SAVE        = 35907,
    NPC_LORD_GOLDFREY              = 35906,
    NPC_QSKA_KILL_CREDIT           = 35753,
    NPC_GUARD_QSKA                 = 35509,
    NPC_WORGEN_QSKA                = 35505,
    NPC_COMMANDEERED_CANNON        = 35914,
    NPC_BLOODFANG_RIPPER_QSKA      = 35916,

    NPC_CROWLEYS_HORSE             = 44428,
    NPC_KING_GENN_GREYMANE_TTR     = 35911,

    SPELL_CANNON_FIRE              = 68235,
    SPELL_SHOOT_QSKA               = 48424,
    SPELL_CANNON_CAMERA            = 93522,
    SPELL_DETECT_QUEST_INVIS       = 49416,
};

const float WorgenSummonPos[13][4]=
{
    {-1715.219f, 1352.839f, 19.8645f, 2.72649f},
    {-1721.182f, 1350.429f, 19.8656f, 2.48614f},
    {-1746.523f, 1361.108f, 19.8681f, 1.85957f},
    {-1724.385f, 1348.462f, 19.6781f, 2.10692f},
    {-1734.542f, 1344.554f, 19.8769f, 1.65637f},
    {-1732.773f, 1367.837f, 19.9010f, 1.10063f},
    {-1744.358f, 1363.382f, 19.8996f, 2.06127f},
    {-1719.358f, 1357.512f, 19.7791f, 2.91488f},
    {-1728.276f, 1353.201f, 19.6823f, 2.25370f},
    {-1726.747f, 1364.599f, 19.9263f, 2.71766f},
    {-1737.693f, 1352.986f, 19.8711f, 1.96818f},
    {-1734.391f, 1359.887f, 19.9064f, 2.48052f},
    {-1730.286f, 1390.384f, 20.7707f, 4.35712f},
};

class npc_saved_aranas : public CreatureScript
{
public:
    npc_saved_aranas() : CreatureScript("npc_saved_aranas") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_saved_aranasAI (creature);
    }

    struct npc_saved_aranasAI : public ScriptedAI
    {
        npc_saved_aranasAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (me->isSummon())
                if (Creature* horse = me->FindNearestCreature(NPC_GREYMANE_HORSE_P4, 20.0f))
                    //Jump onto horse in seat 2
                    DoCast(horse, 84275, true);
                if (Creature* aranas = me->FindNearestCreature(NPC_KRENNAN_ARANAS, 50.0f))
                    aranas->DespawnOrUnsummon();
        }
    };
};

class npc_vehicle_genn_horse : public CreatureScript
{
public:
    npc_vehicle_genn_horse() : CreatureScript("npc_vehicle_genn_horse") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vehicle_genn_horseAI (creature);
    }

    struct npc_vehicle_genn_horseAI : public npc_escortAI
    {
        npc_vehicle_genn_horseAI(Creature* creature) : npc_escortAI(creature)
        {
            AranasIsSave = false;
            PlayerOn     = false;
        }

        bool PlayerOn;
        bool AranasIsSave;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            PlayerOn       = false;
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                PlayerOn = true;
                if (apply)
                {
                    Start(false, true, who->GetGUID());
                    me->SetSpeed(MOVE_WALK, 1.0f, true);
                    me->SetSpeed(MOVE_RUN, 1.3f, true);
                }
            }
            else 
            {
                if (apply)
                {
                    SetEscortPaused(false);
                    AranasIsSave = true;
                    me->SetSpeed(MOVE_WALK, 1.0f, true);
                    me->SetSpeed(MOVE_RUN, 1.3f, true);
                }
                else
                    me->DespawnOrUnsummon(1);
            }
        }

        void WaypointReached(uint32 i)
        {
            Player* player = GetPlayerForEscort();

            switch(i)
            {
                case 1:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                                if (Unit* passenger = vehicle->GetPassenger(0))
                                    if (Player* player = passenger->ToPlayer())
                                        player->SetClientControl(me, 0);
                    }
                    break;
                }
                case 17:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (Creature* aranas = passenger->FindNearestCreature(NPC_KRENNAN_ARANAS, 50.0f))
                            if (Vehicle* vehicle = me->GetVehicleKit())
                                if (Unit* passenger = vehicle->GetPassenger(0))
                                    if (Player* player = passenger->ToPlayer())
                                        aranas->AI()->Talk(0);

                        me->MonsterWhisper("Rescue Krennan Aranas by using your vehicle's ability.", passenger->GetGUID(), true);
                        me->GetMotionMaster()->MoveJump(-1673.04f, 1344.91f, 15.1353f, 25.0f, 15.0f);
                    }
                    break;
                }
                case 40:
                {
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(0))
                        {
                            if (Player* player = passenger->ToPlayer())
                            {
                                std::list<Creature*> lGuards;
                                me->GetCreatureListWithEntryInGrid(lGuards, NPC_GUARD_QSKA, 90.0f);
                                if (!lGuards.empty())
                                    for (std::list<Creature*>::const_iterator itr = lGuards.begin(); itr != lGuards.end(); ++itr)
                                        if ((*itr)->isAlive())
                                            if (Creature* worgen = (*itr)->FindNearestCreature(NPC_WORGEN_QSKA, 90.0f))
                                                (*itr)->CastSpell(worgen, SPELL_SHOOT_QSKA, false);
                            }
                        }
                    }
                    break;
                }
                case 41:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->CombatStop();
                    break;
                }
                case 42:
                {
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            if (Player* player = passenger->ToPlayer())
                            {
                        player->KilledMonsterCredit(NPC_QSKA_KILL_CREDIT, 0);

                        if (Unit* passenger_2 = vehicle->GetPassenger(1))
                            if (Creature* aranas = passenger_2->ToCreature())
                                aranas->AI()->Talk(0);
                            }
                    break;
                }
                case 44:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                        {
                            if (Unit* passenger = vehicle->GetPassenger(0))
                                if (Player* player = passenger->ToPlayer())
                                    player->SetClientControl(me, 1);

                            if (Unit* passenger = vehicle->GetPassenger(1))
                                if (Creature* aranas = passenger->ToCreature())
                                    aranas->DespawnOrUnsummon();

                            vehicle->RemoveAllPassengers();
                        }
                    }
                    me->DespawnOrUnsummon(1);
                    break;
                }
            }
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            Player* player = GetPlayerForEscort();

            if (PlayerOn)
            {
                player->SetClientControl(me, 0);
                PlayerOn = false;
            }
        }
    };
};
/*######
## npc_king_genn_greymane Save Krennan Aranas
######*/
class npc_king_genn_greymane : public CreatureScript
{
public:
    npc_king_genn_greymane() : CreatureScript("npc_king_genn_greymane") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
        {
            float x, y;
            creature->GetNearPoint2D(x, y, 2.0f, player->GetOrientation() + M_PI / 2);

            player->RemoveAurasDueToSpell(59073);

            if (Creature* horse = player->SummonCreature(NPC_GENN_HORSE, x, y, creature->GetPositionZ(), creature->GetOrientation()))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, horse->AI()))
                {
                    escort->AddWaypoint(1, -1799.37f, 1400.21f, 19.8951f);
                    escort->AddWaypoint(2, -1798.23f, 1396.9f, 19.8993f);
                    escort->AddWaypoint(3, -1795.03f, 1388.01f, 19.8898f);
                    escort->AddWaypoint(4, -1790.16f, 1378.7f, 19.8016f);
                    escort->AddWaypoint(5, -1786.41f, 1372.97f, 19.8406f);
                    escort->AddWaypoint(6, -1779.72f, 1364.88f, 19.8131f);
                    escort->AddWaypoint(7, -1774.43f, 1359.87f, 19.7021f);
                    escort->AddWaypoint(8, -1769.0f, 1356.76f, 19.7439f);
                    escort->AddWaypoint(9, -1762.64f, 1356.02f, 19.7979f);
                    escort->AddWaypoint(10, -1758.91f, 1356.08f, 19.8635f);
                    escort->AddWaypoint(11, -1751.95f, 1356.8f, 19.8273f);
                    escort->AddWaypoint(12, -1745.66f, 1357.21f, 19.7993f);
                    escort->AddWaypoint(13, -1738.7f, 1356.64f, 19.7822f);
                    escort->AddWaypoint(14, -1731.79f, 1355.51f, 19.7149f);
                    escort->AddWaypoint(15, -1724.89f, 1354.29f, 19.8661f);
                    escort->AddWaypoint(16, -1718.03f, 1352.93f, 19.7824f);
                    escort->AddWaypoint(17, -1707.68f, 1351.16f, 19.7811f);
                    escort->AddWaypoint(18, -1673.04f, 1344.91f, 15.1353f, 0, true);
                    escort->AddWaypoint(19, -1673.04f, 1344.91f, 15.1353f);
                    escort->AddWaypoint(20, -1669.32f, 1346.55f, 15.1353f);
                    escort->AddWaypoint(21, -1666.45f, 1349.89f, 15.1353f);
                    escort->AddWaypoint(22, -1665.61f, 1353.85f, 15.1353f);
                    escort->AddWaypoint(23, -1666.04f, 1358.01f, 15.1353f);
                    escort->AddWaypoint(24, -1669.79f, 1360.71f, 15.1353f);
                    escort->AddWaypoint(25, -1673.1f, 1362.11f, 15.1353f);
                    escort->AddWaypoint(26, -1677.12f, 1361.57f, 15.1353f);
                    escort->AddWaypoint(27, -1679.9f, 1360.1f, 15.1353f);
                    escort->AddWaypoint(28, -1682.79f, 1357.56f, 15.1353f);
                    escort->AddWaypoint(29, -1682.79f, 1357.56f, 15.1353f);
                    escort->AddWaypoint(30, -1689.07f, 1352.39f, 15.1353f);
                    escort->AddWaypoint(31, -1691.91f, 1351.83f, 15.1353f);
                    escort->AddWaypoint(32, -1703.81f, 1351.82f, 19.7604f);
                    escort->AddWaypoint(33, -1707.26f, 1352.38f, 19.7826f);
                    escort->AddWaypoint(34, -1712.25f, 1353.55f, 19.7826f);
                    escort->AddWaypoint(35, -1718.2f, 1356.51f, 19.7164f);
                    escort->AddWaypoint(36, -1741.5f, 1372.04f, 19.9569f);
                    escort->AddWaypoint(37, -1746.23f, 1375.8f, 19.9817f);
                    escort->AddWaypoint(38, -1751.06f, 1380.53f, 19.8424f);
                    escort->AddWaypoint(39, -1754.97f, 1386.34f, 19.8474f);
                    escort->AddWaypoint(40, -1760.77f, 1394.37f, 19.9282f);
                    escort->AddWaypoint(41, -1765.11f, 1402.07f, 19.8816f);
                    escort->AddWaypoint(42, -1768.24f, 1410.2f, 19.7833f);
                    escort->AddWaypoint(43, -1772.26f, 1420.48f, 19.9029f);
                    escort->AddWaypoint(44, -1776.98f, 1436.13f, 19.632f);
                    player->CastSpell(player, SPELL_DETECT_QUEST_INVIS, false);
                    player->EnterVehicle(horse, 0);
                }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymaneAI (creature);
    }

    struct npc_king_genn_greymaneAI : public ScriptedAI
    {
        npc_king_genn_greymaneAI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomYellTimer = urand(15000, 35000);
        }

        uint32 uiRandomYellTimer;

        void UpdateAI(uint32 diff)
        {
            if (uiRandomYellTimer <= diff)
            {
                uiRandomYellTimer = urand(15000, 35000);
                Talk(1);
            }
            else
                uiRandomYellTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_cannon_camera : public CreatureScript
{
public:
    npc_cannon_camera() : CreatureScript("npc_cannon_camera") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cannon_cameraAI (creature);
    }

    struct npc_cannon_cameraAI : public ScriptedAI
    {
        npc_cannon_cameraAI(Creature* creature) : ScriptedAI(creature)
        {
            uiEventTimer = 1000;
            uiPhase = 0;
            Event = false;
            lSummons.clear();
        }

        std::list<Creature*> lSummons;
        uint32 uiEventTimer;
        uint8 uiPhase;
        bool Event;

        void PassengerBoarded(Unit* /*who*/, int8 /*seatId*/, bool apply)
        {
            if (apply)
                Event = true;
            else
            {
                if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                    cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);

                for (std::list<Creature*>::iterator itr = lSummons.begin(); itr != lSummons.end(); ++itr)
                    if ((*itr)->isAlive())
                        (*itr)->Kill(*itr);

                lSummons.clear();
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (Event)
                if (uiEventTimer <= diff)
                {
                    ++uiPhase;

                    switch (uiPhase)
                    {
                    case 1:
                        uiEventTimer = 1500;

                        for (int i = 0; i < 13; ++i)
                            if (Creature* worgen = me->SummonCreature(NPC_BLOODFANG_RIPPER_QSKA, WorgenSummonPos[i][0], WorgenSummonPos[i][1], WorgenSummonPos[i][2], WorgenSummonPos[i][3]))
                            {
                                lSummons.push_back(worgen);
                                worgen->GetMotionMaster()->MovePoint(0, -1751.874f + irand(-4, 4), 1377.457f + irand(-4, 4), 19.930f);
                            }
                            break;
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        uiEventTimer = 2000;
                        if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                            cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);
                        break;
                    case 9:
                        Event = false;
                        if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                            cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);
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
## npc_lord_godfery_p4_8
######*/
class npc_lord_godfery_p4_8 : public CreatureScript
{
public:
    npc_lord_godfery_p4_8() : CreatureScript("npc_lord_godfery_p4_8") {}

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
        {
            creature->AI()->Talk(0);
            player->RemoveAurasDueToSpell(SPELL_WORGEN_BITE);
            player->RemoveAurasDueToSpell(SPELL_ZONE_SPECIFIC_01);
            player->AddAura(SPELL_INFECTED_BITE, player); // Phase 8 Perfect
            player->CombatStop(true);
        }

        player->SaveToDB();
        return true;
    }
};

///////////
// Quest Time to Regroup 14294
///////////
enum qTR
{
    QUEST_TIME_TO_REGROUP     = 14294,
    NPC_LORD_CROWLEY_QTR      = 35552,
    NPC_PRINCE_LIAM_QTR       = 35551,
};

struct Psc_qtr
{
    uint64 uiPlayerGUID;
    uint32 uiPersonalTimer;
    uint32 uiSpeachId;
};

class npc_king_genn_greymane_qtr : public CreatureScript
{
public:
    npc_king_genn_greymane_qtr() : CreatureScript("npc_king_genn_greymane_qtr") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_TIME_TO_REGROUP)
        {
            creature->AI()->Talk(0);
            Psc_qtr new_psc;
            new_psc.uiSpeachId = 0;
            new_psc.uiPersonalTimer = 7000;
            new_psc.uiPlayerGUID = player->GetGUID();
            CAST_AI(npc_king_genn_greymane_qtrAI, creature->AI())->lPlayerList.push_back(new_psc);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_qtrAI (creature);
    }

    struct npc_king_genn_greymane_qtrAI : public ScriptedAI
    {
        npc_king_genn_greymane_qtrAI(Creature* creature) : ScriptedAI(creature)
        {
            lPlayerList.clear();
        }

        std::list<Psc_qtr> lPlayerList;

        void DeletePlayer(uint64 uiPlayerGUID)
        {
            for (std::list<Psc_qtr>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                if (itr->uiPlayerGUID == uiPlayerGUID)
                    itr = lPlayerList.erase(itr);
                else
                    ++itr;
        }

        void UpdateAI(uint32 diff)
        {
            if (lPlayerList.empty())
                return;

            for (std::list<Psc_qtr>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                if ((*itr).uiPersonalTimer <= diff)
                {
                    ++(*itr).uiSpeachId;

                    if (Player* player = Unit::GetPlayer(*me, (*itr).uiPlayerGUID))
                    {
                        switch ((*itr).uiSpeachId)
                        {
                        case 1:
                            (*itr).uiPersonalTimer = 7000;
                            if (Creature* crowley = me->FindNearestCreature(NPC_LORD_CROWLEY_QTR, 30.0f))
                            {
                                crowley->AI()->Talk(0);
                                crowley->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            }
                            break;
                        case 2:
                            (*itr).uiPersonalTimer = 4000;
                            if (Creature* liam = me->FindNearestCreature(NPC_PRINCE_LIAM_QTR, 30.0f))
                                liam->AI()->Talk(0);
                            break;
                        case 3:
                            (*itr).uiPersonalTimer = 9000;
                            if (Creature* crowley = me->FindNearestCreature(NPC_LORD_CROWLEY_QTR, 30.0f))
                                crowley->AI()->Talk(1);
                            break;
                        case 4:
                            (*itr).uiPersonalTimer = 8000;
                            if (Creature* crowley = me->FindNearestCreature(NPC_LORD_CROWLEY_QTR, 30.0f))
                            {
                                crowley->AI()->Talk(2);
                                crowley->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            }
                            break;
                        case 5:
                            Talk(1);
                            itr = lPlayerList.erase(itr);
                            break;
                        }
                    }
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
// QUEST Sacrifices 14212
///////////

/*######
## npc_lord_darius_crowley_c2 Save Krennan Aranas
######*/
class npc_lord_darius_crowley_c2 : public CreatureScript
{
public:
    npc_lord_darius_crowley_c2() : CreatureScript("npc_lord_darius_crowley_c2") {}

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* /*quest*/)
    {
        if (Creature* horse = player->SummonCreature(44427,-1738.65f, 1650.85f, 20.4799f, 0.892969f))
            player->EnterVehicle(horse, 0);
        return true;
    }
};

class npc_crowley_horse : public CreatureScript
{
public:
    npc_crowley_horse() : CreatureScript("npc_crowley_horse") {}

    struct npc_crowley_horseAI : public npc_escortAI
    {
        npc_crowley_horseAI(Creature* creature) : npc_escortAI(creature) {}

        bool CrowleyOn;
        bool CrowleySpawn;
        bool Run;
        bool PlayerOn;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            CrowleyOn = false;
            CrowleySpawn = false;
            Run = false;
            PlayerOn = false;
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                PlayerOn = true;
                if (apply)
                {
                    Start(false, true, who->GetGUID());
                }
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }

        void WaypointReached(uint32 i)
        {
            Player* player = GetPlayerForEscort();
            Creature *crowley = me->FindNearestCreature(NPC_DARIUS_CROWLEY, 5, true);
            if (!player)
                return;

            if (!crowley)
                return;

            switch(i)
            {
                case 1:
                    crowley->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->GetMotionMaster()->MoveJump(-1714.02f, 1666.37f, 20.57f, 25.0f, 15.0f);
                    break;
                case 4:
                    crowley->AI()->Talk(SAY_CROWLEY_HORSE_1);
                    break;
                case 10:
                    me->GetMotionMaster()->MoveJump(-1571.32f, 1710.58f, 20.49f, 25.0f, 15.0f);
                    break;
                case 11:
                    crowley->AI()->Talk(SAY_CROWLEY_HORSE_2);
                    break;
                case 16:
                    crowley->AI()->Talk(SAY_CROWLEY_HORSE_2);
                    break;
                case 20:
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->getThreatManager().resetAllAggro();
                    player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    player->getThreatManager().resetAllAggro();
                    break;
                case 21:
                    player->SetClientControl(me, 1);
                    player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    player->ExitVehicle();
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Player* player = GetPlayerForEscort())
                player->FailQuest(QUEST_SACRIFICES);
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            if (PlayerOn)
            {
                player->SetClientControl(me, 0);
                PlayerOn = false;
            }

            if (!CrowleySpawn)
            {
                DoCast(SPELL_SUMMON_CROWLEY);
                if (Creature *crowley = me->FindNearestCreature(NPC_DARIUS_CROWLEY, 5, true))
                {
                    CrowleySpawn = true;
                }
            }

            if (CrowleySpawn && !CrowleyOn)
            {
                Creature *crowley = me->FindNearestCreature(NPC_DARIUS_CROWLEY, 5, true);
                if (!crowley)
                    return;

                crowley->CastSpell(me, SPELL_RIDE_HORSE, true);//Mount Crowley in seat 1
                CrowleyOn = true;
            }

            if (!Run)
            {
                me->SetSpeed(MOVE_RUN, CROWLEY_SPEED);
                Run = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crowley_horseAI (creature);
    }
};

///////////
// Quest Last Stand 14222
///////////

enum LastStand14222
{
    SPELL_PLAY_MOVIE            = 93477,
    SPELL_ALTERED_WORGEN_FORM   = 97709,
    SPELL_FORCE_ALTERED_FORM    = 72794,
    SPELL_CURSE_OF_THE_WORGEN   = 68630,
    SPELL_LAST_STAND_COMPLETE_1 = 72788,
    SPELL_LAST_STAND_COMPLETE_2 = 72799,
};

///////////
// Quest Last Chance at Humanity 14375
///////////
enum Quest14375
{
    EVENT_CHECK_PLAYER = 1,
    EVENT_MOVE_KRENNAN,
    EVENT_TALK_KRENNAN,

    EVENT_SUMMON_GODFREY,
    EVENT_MOVE_GODFREY,
    EVENT_TALK_GODFREY,

    EVENT_SUMMON_GREYMANE,
    EVENT_TALK_GREYMANE,
    EVENT_MOVE_GREYMANE,

    QUEST_LAST_STAND                = 14222,
    QUEST_LAST_CHANCE_AT_HUMANITY   = 14375,

    // Krennan
    MUSIC_KRENNAN                   = 23508,

    NPC_LORD_GODFREY_QLS            = 36330,
    NPC_KRENNAN_ARANAS_QLS          = 36331,
    NPC_KING_GENN_GREYMANE_QLS      = 36332,

    ACTION_EVENT_DONE               = 1,
};

Position const Quest14375Pos[]=
{
    {-1815.903f, 2283.854f, 42.4066f}, // Krennan
    {-1844.04f, 2289.634f, 42.4066f},  // Godfrey
    {-1846.708f, 2288.752f, 42.4066f},  // Genn Greymane
};

Position const krennanMovePos = {-1819.53f, 2291.25f, 42.32689f};
Position const godfreyMovePos = {-1823.585f, 2293.542f, 42.03004f};
Position const gennMovePos = {-1821.09f, 2292.597f, 42.23363f};

class npc_lord_darius_crowley_c3 : public CreatureScript
{
public:
    npc_lord_darius_crowley_c3() : CreatureScript("npc_lord_darius_crowley_c3")
    {
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14222)
            player->CastSpell(player, SPELL_PHASE_1024, true);
        return true;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == 14222)
        {
            player->RemoveAurasDueToSpell(SPELL_INFECTED_BITE); // Hideous Bite Wound
            player->CastSpell(player, SPELL_PLAY_MOVIE, true);
            player->CastSpell(player, SPELL_ALTERED_WORGEN_FORM, true);
            //player->CastSpell(player, SPELL_FORCE_ALTERED_FORM, true);
            player->CastSpell(player, SPELL_CURSE_OF_THE_WORGEN, true);
            player->CastSpell(player, SPELL_LAST_STAND_COMPLETE_1, true);
            player->CastSpell(player, SPELL_LAST_STAND_COMPLETE_2, true);
            player->CastSpell(player, SPELL_ALTERED_WORGEN_FORM, true);
            player->SummonCreature(NPC_KRENNAN_ARANAS_QLS, Quest14375Pos[0], TEMPSUMMON_MANUAL_DESPAWN);
        }
        return true;
    }
};

class npc_frenzied_stalker : public CreatureScript
{
public:
    npc_frenzied_stalker() : CreatureScript("npc_frenzied_stalker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frenzied_stalkerAI (creature);
    }

    struct npc_frenzied_stalkerAI : public ScriptedAI
    {
        npc_frenzied_stalkerAI(Creature *c) : ScriptedAI(c)
        {
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                damage = 0;
            else
                me->AddThreat(attacker, 1000);
        }
    };
};

class npc_king_genn_greymane_qls : public CreatureScript
{
public:
    npc_king_genn_greymane_qls() : CreatureScript("npc_king_genn_greymane_qls") { }

    struct npc_king_genn_greymane_qlsAI : public ScriptedAI
    {
        npc_king_genn_greymane_qlsAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;
        uint64 seerGUID;

        void IsSummonedBy(Unit* summoner)
        {
            seerGUID = summoner->ToCreature()->GetSeerGUID();
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->SetSeerGUID(seerGUID);
            me->SetVisible(false);
            me->SetWalk(true);
            me->SetPhaseMask(summoner->GetPhaseMask(), true);
            me->GetMotionMaster()->MovePoint(0, gennMovePos);
            events.ScheduleEvent(EVENT_MOVE_GREYMANE, 9700);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_MOVE_GREYMANE:
                        Talk(0);
                        me->SetFacingTo(1.32645f);
                        events.ScheduleEvent(EVENT_TALK_GREYMANE, 9700);
                        break;
                    case EVENT_TALK_GREYMANE:
                        Talk(1);
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        me->SetFacingTo(5.497787f);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_qlsAI (creature);
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_LAST_CHANCE_AT_HUMANITY)
        {
            player->RemoveAurasDueToSpell(68630);               // Curse of the Worgen
            player->RemoveAurasDueToSpell(68631);               // Curse of the Worgen
            player->RemoveAurasDueToSpell(SPELL_PHASE_1024);    // Quest Zone-Specific 04
            player->SaveToDB();

            if (creature->isSummon())
                if (Unit* summoner = creature->ToTempSummon()->GetSummoner())
                    if (Creature* krennan = summoner->ToCreature())
                        krennan->AI()->DoAction(ACTION_EVENT_DONE);
        }
        return true;
    }
};

class npc_krennan_aranas_qls : public CreatureScript
{
public:
    npc_krennan_aranas_qls() : CreatureScript("npc_krennan_aranas_qls") { }

    struct npc_krennan_aranas_qlsAI : public ScriptedAI
    {
        npc_krennan_aranas_qlsAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
        }

        SummonList summons;
        EventMap events;
        uint64 playerGUID;

        void IsSummonedBy(Unit* summoner)
        {
            playerGUID = summoner->GetGUID();
            me->SetSeerGUID(summoner->GetGUID());
            me->SetVisible(false);
            me->SetWalk(true);
            me->SetPhaseMask(summoner->GetPhaseMask(), true);
            events.ScheduleEvent(EVENT_CHECK_PLAYER, 12000);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void DoAction(int32 action)
        {
            summons.DespawnAll();
            me->DespawnOrUnsummon(1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_CHECK_PLAYER:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                        {
                            if ((!(player->GetExtraFlags() & PLAYER_EXTRA_WATCHING_MOVIE)) && player->IsInWorld())
                            {
                                player->SaveToDB();
                                if (me->GetDistance2d(player) <= 50.0f)
                                    events.ScheduleEvent(EVENT_MOVE_KRENNAN, 2000);
                                else
                                    events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                            }
                            else
                                events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                            break;
                        }
                    case EVENT_MOVE_KRENNAN:
                        me->GetMotionMaster()->MovePoint(0, krennanMovePos);
                        events.ScheduleEvent(EVENT_TALK_KRENNAN, 5200);
                        break;
                    case EVENT_TALK_KRENNAN:
                        Talk(0);
                        events.ScheduleEvent(EVENT_SUMMON_GODFREY, 4700);
                        events.ScheduleEvent(EVENT_SUMMON_GREYMANE, 13500);
                        break;
                    case EVENT_SUMMON_GODFREY:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            if (player->IsInWorld())
                                if (Creature* godfrey = player->SummonCreature(NPC_LORD_GODFREY_QLS, Quest14375Pos[1], TEMPSUMMON_MANUAL_DESPAWN))
                                    JustSummoned(godfrey);
                        break;
                    case EVENT_SUMMON_GREYMANE:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            if (player->IsInWorld())
                                if (Creature* genn = me->SummonCreature(NPC_KING_GENN_GREYMANE_QLS, Quest14375Pos[2], TEMPSUMMON_MANUAL_DESPAWN))
                                    JustSummoned(genn);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_qlsAI (creature);
    }
};

class npc_godfrey_qls : public CreatureScript
{
public:
    npc_godfrey_qls() : CreatureScript("npc_godfrey_qls") { }

    struct npc_godfrey_qlsAI : public ScriptedAI
    {
        npc_godfrey_qlsAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;
        uint64 playerGUID;

        void IsSummonedBy(Unit* summoner)
        {
            playerGUID = summoner->GetGUID();
            me->SetSeerGUID(summoner->GetGUID());
            me->SetVisible(false);
            me->SetWalk(true);
            me->SetPhaseMask(summoner->GetPhaseMask(), true);
            events.ScheduleEvent(EVENT_MOVE_GODFREY, 1300);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_MOVE_GODFREY:
                        me->GetMotionMaster()->MovePoint(0, godfreyMovePos);
                        events.ScheduleEvent(EVENT_TALK_GODFREY, 8400);
                        break;
                    case EVENT_TALK_GODFREY:
                        Talk(0);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_godfrey_qlsAI (creature);
    }
};

// Quest 14348 -- You can't take 'em alone

enum Quest14348
{
    // Horrid Abomination
    SAY_KEG_PLACED                      = 0,
    EVENT_HIT_ME                        = 1,
    QUEST_HORRID_ABOMINATION_CREDIT     = 36233,
    SPELL_TOSS_KEG                      = 69094,
    SPELL_KEG_PLACED                    = 68555,
    SPELL_KILL_ME                       = 68558,
    SPELL_RANDOM_CIRCUMFERENCE_POISON   = 42266,
    SPELL_RANDOM_CIRCUMFERENCE_BONES_1  = 42267,
    SPELL_RANDOM_CIRCUMFERENCE_BONES_2  = 42274,
    SPELL_BLOW_UP_ABOMINATION           = 68560,

    // Liam Greymane
    NPC_LIAM_QUEST_14348                = 36140,
    SPELL_SHOOT_1                       = 68559
};

class npc_horrid_abbomination : public CreatureScript
{
public:
    npc_horrid_abbomination() : CreatureScript("npc_horrid_abomination") { }

    struct npc_horrid_abbominationAI : public ScriptedAI
    {
        npc_horrid_abbominationAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;
        uint64 playerGUID;
        bool _blownUp;

        void Reset()
        {
            _blownUp = false;
            playerGUID = 0;
        }

        void JustRespawned()
        {
            _blownUp = false;
            playerGUID = 0;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            _blownUp = false;
            playerGUID = 0;
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (me->HasAura(SPELL_KEG_PLACED))
            {
                events.ScheduleEvent(EVENT_HIT_ME, 1500);
                Talk(SAY_KEG_PLACED);
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_KEG_PLACED:
                {
                    events.ScheduleEvent(EVENT_HIT_ME, 1500);
                    Talk(SAY_KEG_PLACED);
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    break;
                }
                case SPELL_TOSS_KEG:
                {
                    if (!_blownUp)
                    {
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        playerGUID = caster->GetGUID();
                        me->AI()->AttackStart(caster);
                        _blownUp = true;
                    }
                    break;
                }
                case SPELL_SHOOT_1:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                    {
                        me->RemoveAurasDueToSpell(SPELL_KEG_PLACED);
                        player->KilledMonsterCredit(QUEST_HORRID_ABOMINATION_CREDIT);
                        DoCast(SPELL_BLOW_UP_ABOMINATION);
                        for (uint8 i = 0; i < 11; i++)
                            DoCast(me, SPELL_RANDOM_CIRCUMFERENCE_POISON, true);

                        for (uint8 i = 0; i < 6; i++)
                            DoCast(me, SPELL_RANDOM_CIRCUMFERENCE_BONES_1, true);

                        for (uint8 i = 0; i < 4; i++)
                            DoCast(me, SPELL_RANDOM_CIRCUMFERENCE_BONES_2, true);

                        me->DespawnOrUnsummon(1500);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !_blownUp && !me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_HIT_ME:
                    {
                        if (Creature* liam = me->FindNearestCreature(NPC_LIAM_QUEST_14348, 500.0f, true))
                            liam->CastSpell(me, SPELL_SHOOT_1, true);
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
        return new npc_horrid_abbominationAI (creature);
    }
};

// Quest 14320 - In need of Ingrendients

class go_crate_of_mandrake_essence : public GameObjectScript
{
public:
    go_crate_of_mandrake_essence() : GameObjectScript("go_crate_of_mandrake_essence") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(14320) == QUEST_STATUS_REWARDED)
        {
            player->SendCinematicStart(168);
            player->PlayerTalkClass->SendCloseGossip();
        }
        return false;
    }
};

// Quest 14321 - Invasion

enum Quest14321
{
    SPELL_SUMMON_FORSAKEN_ASSISSIN  = 68492,
    SPELL_BACKSTAB                  = 75360,

    EVENT_BACKSTAB = 1,
};

class npc_slain_watchman : public CreatureScript
{
public:
    npc_slain_watchman() : CreatureScript("npc_slain_watchman") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* /*quest*/)
    {
        player->CastSpell(player, SPELL_SUMMON_FORSAKEN_ASSISSIN, true);
        return true;
    }
};

class npc_forsaken_assassin : public CreatureScript
{
public:
    npc_forsaken_assassin() : CreatureScript("npc_forsaken_assassin") { }

    struct npc_forsaken_assassinAI : public ScriptedAI
    {
        npc_forsaken_assassinAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            me->AI()->AttackStart(summoner);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_BACKSTAB, 4000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim()) 
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_BACKSTAB:
                        DoCastVictim(SPELL_BACKSTAB);
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
        return new npc_forsaken_assassinAI (creature);
    }
};

class npc_forsaken_invader : public CreatureScript
{
public:
    npc_forsaken_invader() : CreatureScript("npc_forsaken_invader") { }

    enum eventId
    {
        EVENT_SEARCH_WATCHMAN   = 1
    };

    enum npcId
    {
        NPC_ENTRY_WATCHMAN  = 36211
    };

    struct npc_forsaken_invaderAI : public ScriptedAI
    {
        npc_forsaken_invaderAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_SEARCH_WATCHMAN, 2000);
        }

        EventMap events;

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (who->ToCreature() && who->GetEntry() == NPC_ENTRY_WATCHMAN)
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SEARCH_WATCHMAN:
                    {
                        if (!me->isInCombat())
                        {
                            if (Creature* watchman = me->FindNearestCreature(NPC_ENTRY_WATCHMAN, 15.5f, true))
                                AttackStart(watchman);
                        }
                        else
                            events.RescheduleEvent(EVENT_SEARCH_WATCHMAN, urand(2000, 5000));
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_forsaken_invaderAI (creature);
    }
};

class npc_duskhaven_watchman : public CreatureScript
{
public:
    npc_duskhaven_watchman() : CreatureScript("npc_duskhaven_watchman") { }

    enum eventId
    {
        EVENT_SEARCH_INVADER        = 1,
        EVENT_SEARCH_FOOTSOLDIER
    };

    enum npcId
    {
        NPC_ENTRY_INVADER       = 34511,
        NPC_ENTRY_FOOTSOLDIER   = 36236
    };

    struct npc_duskhaven_watchmanAI : public ScriptedAI
    {
        npc_duskhaven_watchmanAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_SEARCH_INVADER, 2000);
        }

        EventMap events;

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (who->ToCreature() && (who->GetEntry() == NPC_ENTRY_INVADER || who->GetEntry() == NPC_ENTRY_FOOTSOLDIER))
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SEARCH_INVADER:
                    {
                        if (!me->isInCombat())
                        {
                            if (Creature* invader = me->FindNearestCreature(NPC_ENTRY_INVADER, 15.5f, true))
                                AttackStart(invader);
                        }
                        else
                            events.RescheduleEvent(EVENT_SEARCH_INVADER, urand (2000, 5000));
                        break;
                    }
                    case EVENT_SEARCH_FOOTSOLDIER:
                    {
                        if (!me->isInCombat())
                        {
                            if (Creature* footsoldier = me->FindNearestCreature(NPC_ENTRY_FOOTSOLDIER, 15.5f, true))
                                AttackStart(footsoldier);
                        }
                        else
                            events.RescheduleEvent(EVENT_SEARCH_FOOTSOLDIER, urand (2000, 5000));
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_duskhaven_watchmanAI (creature);
    }
};

class npc_forsaken_footsoldier : public CreatureScript
{
public:
    npc_forsaken_footsoldier() : CreatureScript("npc_forsaken_footsoldier") { }

    enum eventId
    {
        EVENT_SEARCH_WATCHMAN   = 1
    };

    enum npcId
    {
        NPC_ENTRY_WATCHMAN  = 36211
    };

    struct npc_forsaken_footsoldierAI : public ScriptedAI
    {
        npc_forsaken_footsoldierAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_SEARCH_WATCHMAN, 2000);
        }

        EventMap events;

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (who->ToCreature() && who->GetEntry() == NPC_ENTRY_WATCHMAN)
                damage = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SEARCH_WATCHMAN:
                    {
                        if (!me->isInCombat())
                        {
                            if (Creature* watchman = me->FindNearestCreature(NPC_ENTRY_WATCHMAN, 15.5f, true))
                                AttackStart(watchman);
                        }
                        else
                            events.RescheduleEvent(EVENT_SEARCH_WATCHMAN, urand(2000, 5000));
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_forsaken_footsoldierAI (creature);
    }
};

class npc_dh_forsaken_catapult : public CreatureScript
{
public:
    npc_dh_forsaken_catapult() : CreatureScript("npc_dh_forsaken_catapult") { }

    enum eventId
    {
        EVENT_LAUNCH_BOULDER    = 1,
        EVENT_DESPAWN_CATAPULT,
        EVENT_CHECK_PASSENGER
    };

    enum spellId
    {
        SPELL_LAUNCH_BOULDER    = 68591
    };

    enum questId
    {
        QUEST_ENTRY_TWO_BY_SEA  = 14382
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_TWO_BY_SEA) == QUEST_STATUS_INCOMPLETE)
        {
            if (player->GetVehicleBase())
                return true;

            player->EnterVehicle(creature, 0);
            return true;
        }
        return true;
    }

    struct npc_dh_forsaken_catapultAI : public ScriptedAI
    {
        npc_dh_forsaken_catapultAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_LAUNCH_BOULDER, urand(8000, 20000));
            events.ScheduleEvent(EVENT_CHECK_PASSENGER, 5000);
        }

        EventMap events;

        void OnCharmed(bool apply) {}

        void Reset()
        {
            events.ScheduleEvent(EVENT_LAUNCH_BOULDER, urand(8000, 20000));
            events.ScheduleEvent(EVENT_CHECK_PASSENGER, 5000);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->setFaction(1735);
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_LAUNCH_BOULDER:
                    {
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                        {
                            if (passenger->GetTypeId() != TYPEID_PLAYER)
                            {
                                if (!me->HasUnitState(UNIT_STATE_CASTING))
                                {
                                    DoCast(SPELL_LAUNCH_BOULDER);
                                    events.RescheduleEvent(EVENT_LAUNCH_BOULDER, urand(5000, 12000));
                                }
                                else
                                    events.RescheduleEvent(EVENT_LAUNCH_BOULDER, 1000);
                            }
                        }
                        else
                        {
                            events.CancelEvent(EVENT_LAUNCH_BOULDER);
                            events.ScheduleEvent(EVENT_DESPAWN_CATAPULT, 10000);
                        }
                        break;
                    }
                    case EVENT_DESPAWN_CATAPULT:
                    {
                        Unit* passenger1 = me->GetVehicleKit()->GetPassenger(0);
                        Unit* passenger2 = me->GetVehicleKit()->GetPassenger(1);
                        if (!passenger1 && !passenger2)
                            me->DisappearAndDie();
                        else
                            events.RescheduleEvent(EVENT_DESPAWN_CATAPULT, 2000);
                        break;
                    }
                    case EVENT_CHECK_PASSENGER:
                    {
                        Unit* passenger1 = me->GetVehicleKit()->GetPassenger(0);
                        Unit* passenger2 = me->GetVehicleKit()->GetPassenger(1);
                        if (!passenger1 && !passenger2)
                        {
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->setFaction(35);
                            events.CancelEvent(EVENT_CHECK_PASSENGER);
                        }
                        else
                            events.RescheduleEvent(EVENT_CHECK_PASSENGER, 2500);
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
        return new npc_dh_forsaken_catapultAI (creature);
    }
};

class BoulderTargetCheck
{
public:
    BoulderTargetCheck()
    {
    }

    enum npcId
    {
        NPC_CATAPULT_BOULDER_TRIGGER    = 36286
    };

    bool operator()(WorldObject* object)
    {
        return (object->ToPlayer() || (object->ToUnit() && (object->ToUnit()->GetEntry() != NPC_CATAPULT_BOULDER_TRIGGER || object->GetPositionZ() > 3.48f)));
    }
};

class spell_catapult_boulder : public SpellScriptLoader
{
public:
    spell_catapult_boulder() : SpellScriptLoader("spell_catapult_boulder")
    {
    }

    class spell_catapult_boulder_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_catapult_boulder_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(BoulderTargetCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_catapult_boulder_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_catapult_boulder_SpellScript();
    }
};

class npc_dh_james : public CreatureScript
{
public:
    npc_dh_james() : CreatureScript("npc_dh_james") { }

    enum eventId
    {
        EVENT_RUN_AND_DESPAWN   = 1
    };

    enum questId
    {
        QUEST_ENTRY_SAVE_THE_CHILDREN  = 14368
    };

    enum actionId
    {
        ACTION_RUN_AWAY     = 1
    };

    enum pointId
    {
        POINT_AWAY  = 1
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_SAVE_THE_CHILDREN) == QUEST_STATUS_INCOMPLETE)
        {
            player->MonsterSay("Your mother's in the basement next door. Get to her now!", 0);
            creature->GetMotionMaster()->Clear();
            creature->AI()->TalkWithDelay(4000, 0);
            creature->AI()->DoAction(ACTION_RUN_AWAY);
            player->KilledMonsterCredit(creature->GetEntry());
            creature->SetFacingToObject(player);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->SetControlled(true, UNIT_STATE_ROOT);
            return true;
        }
        return true;
    }

    struct npc_dh_jamesAI : public ScriptedAI
    {
        npc_dh_jamesAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetWalk(true);
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_RUN_AWAY:
                {
                    events.ScheduleEvent(EVENT_RUN_AND_DESPAWN, 9000);
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
                switch(eventId)
                {
                    case EVENT_RUN_AND_DESPAWN:
                    {
                        events.CancelEvent(EVENT_RUN_AND_DESPAWN);
                        me->SetWalk(false);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -1907.70f, 2545.77f, 1.82f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_AWAY:
                {
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dh_jamesAI (creature);
    }
};

class npc_dh_ashley : public CreatureScript
{
public:
    npc_dh_ashley() : CreatureScript("npc_dh_ashley") { }

    enum eventId
    {
        EVENT_RUN_AND_DESPAWN   = 1
    };

    enum questId
    {
        QUEST_ENTRY_SAVE_THE_CHILDREN  = 14368
    };

    enum actionId
    {
        ACTION_RUN_AWAY     = 1
    };

    enum pointId
    {
        POINT_AWAY  = 1
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_SAVE_THE_CHILDREN) == QUEST_STATUS_INCOMPLETE)
        {
            player->MonsterSay("Join the others inside the basement next door. Hurry!", 0);
            creature->GetMotionMaster()->Clear();
            creature->AI()->TalkWithDelay(4000, 0);
            creature->AI()->DoAction(ACTION_RUN_AWAY);
            player->KilledMonsterCredit(creature->GetEntry());
            creature->SetFacingToObject(player);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->SetControlled(true, UNIT_STATE_ROOT);
            return true;
        }
        return true;
    }

    struct npc_dh_ashleyAI : public ScriptedAI
    {
        npc_dh_ashleyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetWalk(true);
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_RUN_AWAY:
                {
                    events.ScheduleEvent(EVENT_RUN_AND_DESPAWN, 3500);
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
                switch(eventId)
                {
                    case EVENT_RUN_AND_DESPAWN:
                    {
                        events.CancelEvent(EVENT_RUN_AND_DESPAWN);
                        me->SetWalk(false);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -1940.18f, 2566.21f, 1.39f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_AWAY:
                {
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dh_ashleyAI (creature);
    }
};

class npc_dh_cynthia : public CreatureScript
{
public:
    npc_dh_cynthia() : CreatureScript("npc_dh_cynthia") { }

    enum eventId
    {
        EVENT_RUN_AND_DESPAWN   = 1,
        EVENT_ONESHOT_CRY
    };

    enum questId
    {
        QUEST_ENTRY_SAVE_THE_CHILDREN  = 14368
    };

    enum actionId
    {
        ACTION_RUN_AWAY     = 1
    };

    enum pointId
    {
        POINT_AWAY  = 1
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_SAVE_THE_CHILDREN) == QUEST_STATUS_INCOMPLETE)
        {
            player->MonsterSay("It's not safe here. Go to the Allens' basement.", 0);
            creature->GetMotionMaster()->Clear();
            creature->AI()->TalkWithDelay(4000, 0);
            creature->AI()->DoAction(ACTION_RUN_AWAY);
            player->KilledMonsterCredit(creature->GetEntry());
            creature->SetFacingToObject(player);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->SetControlled(true, UNIT_STATE_ROOT);
            return true;
        }
        return true;
    }

    struct npc_dh_cynthiaAI : public ScriptedAI
    {
        npc_dh_cynthiaAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetWalk(true);
            events.ScheduleEvent(EVENT_ONESHOT_CRY, urand(3000, 7500));
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_RUN_AWAY:
                {
                    events.ScheduleEvent(EVENT_RUN_AND_DESPAWN, 6000);
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
                switch(eventId)
                {
                    case EVENT_RUN_AND_DESPAWN:
                    {
                        events.CancelEvent(EVENT_RUN_AND_DESPAWN);
                        events.CancelEvent(EVENT_ONESHOT_CRY);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        me->SetWalk(false);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -1927.20f, 2520.46f, 1.93f);
                        break;
                    }
                    case EVENT_ONESHOT_CRY:
                    {
                        events.RescheduleEvent(EVENT_ONESHOT_CRY, urand(3000, 6500));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_AWAY:
                {
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dh_cynthiaAI (creature);
    }
};

class spell_load_catapult_boulder : public SpellScriptLoader
{
    public:
        spell_load_catapult_boulder() : SpellScriptLoader("spell_load_catapult_boulder") {}

        class spell_load_catapult_boulder_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_load_catapult_boulder_SpellScript);
            void HandleScript(SpellEffIndex effIndex)
            {
                Spell* baseSpell = GetSpell();
                SpellCastTargets targets = baseSpell->m_targets;
                if (targets.HasTraj())
                {
                    if (Vehicle* vehicle = GetCaster()->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(0))
                        {
                            // use 99 because it is 3d search
                            std::list<WorldObject*> targetList;
                            Trinity::WorldObjectSpellAreaTargetCheck check(99, GetExplTargetDest(), GetCaster(), GetCaster(), GetSpellInfo(), TARGET_CHECK_DEFAULT, NULL);
                            Trinity::WorldObjectListSearcher<Trinity::WorldObjectSpellAreaTargetCheck> searcher(GetCaster(), targetList, check);
                            GetCaster()->GetMap()->VisitAll(GetCaster()->m_positionX, GetCaster()->m_positionY, 99, searcher);
                            float minDist = 99 * 99;
                            Unit* target = NULL;
                            for (std::list<WorldObject*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                            {
                                if (Unit* unit = (*itr)->ToUnit())
                                {
                                    if (unit->GetEntry() == 36283)
                                    {
                                        if (Vehicle* seat = unit->GetVehicleKit())
                                        {
                                            if (!seat->GetPassenger(0))
                                            {
                                                if (Unit* device = seat->GetPassenger(1))
                                                {
                                                    if (!device->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                                                    {
                                                        float dist = unit->GetExactDistSq(targets.GetDstPos());
                                                        if (dist < minDist)
                                                        {
                                                            minDist = dist;
                                                            target = unit;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if (target && target->IsWithinDist2d(targets.GetDstPos(), GetSpellInfo()->Effects[effIndex].CalcRadius() * 2)) // now we use *2 because the location of the seat is not correct
                                passenger->EnterVehicle(target, 0);
                            else
                            {
                                float x, y, z;
                                targets.GetDstPos()->GetPosition(x, y, z);
                                passenger->ExitVehicle();
                                passenger->GetMotionMaster()->MoveJump(x, y, z, targets.GetSpeedXY(), targets.GetSpeedZ());
                                passenger->AddAura(66251, passenger);
                                if (vehicle->GetBase()->ToCreature())
                                    vehicle->GetBase()->ToCreature()->DisappearAndDie();
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_load_catapult_boulder_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_load_catapult_boulder_SpellScript();
        }
};

class spell_call_attack_mastiffs : public SpellScriptLoader
{
public:
    spell_call_attack_mastiffs() : SpellScriptLoader("spell_call_attack_mastiffs") { }

    class spell_call_attack_mastiffs_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_call_attack_mastiffs_SpellScript);

        enum questId
        {
            NPC_ENTRY_DARK_RANGER_THYALA    = 36312
        };

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (Creature* thyala = caster->FindNearestCreature(NPC_ENTRY_DARK_RANGER_THYALA, 20.0f, true))
                        return SPELL_CAST_OK;
                }
            }
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_call_attack_mastiffs_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_call_attack_mastiffs_SpellScript();
    }
};

class npc_mountain_horse : public CreatureScript
{
public:
    npc_mountain_horse() : CreatureScript("npc_mountain_horse") { }

    enum questId
    {
        QUEST_THE_HUNGRY_ETTIN  = 14416
    };

    enum spellId
    {
        SPELL_ROUND_UP_HORSE    = 68908
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_HUNGRY_ETTIN) == QUEST_STATUS_INCOMPLETE)
        {
            player->EnterVehicle(creature, 0);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->GetMotionMaster()->Clear();
            return true;
        }
        return true;
    }

    struct npc_mountain_horseAI : public ScriptedAI
    {
        npc_mountain_horseAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            if (!me->GetVehicleKit()->GetPassenger(0))
                me->GetMotionMaster()->MoveRandom(8.0f);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_ROUND_UP_HORSE:
                {
                    if (me->GetVehicleKit()->GetPassenger(0))
                        break;

                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void PassengerBoarded(Unit* /*passenger*/, int8 /*SeatId*/, bool apply)
        {
            if (!apply)
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetWalk(true);
                me->AI()->EnterEvadeMode();
            }
        }

        void OnCharmed(bool apply) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mountain_horseAI (creature);
    }
};

class npc_mountain_horse_summoned : public CreatureScript
{
public:
    npc_mountain_horse_summoned() : CreatureScript("npc_mountain_horse_summoned")
    {
    }

    enum spellId
    {
        SPELL_HORSE_ROPE    = 68940
    };

    enum npcId
    {
        NPC_ENTRY_LORNA_CROWLEY     = 36457
    };

    enum eventId
    {
        EVENT_CHECK_LORNA   = 1,
        EVENT_CHECK_OWNER
    };

    enum creditId
    {
        QUEST_CREDIT_HORSE  = 36560
    };

    struct npc_mountain_horse_summonedAI : public ScriptedAI
    {
        npc_mountain_horse_summonedAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            me->GetMotionMaster()->MoveFollow(summoner, 6.0f, 0);
            me->CastSpell(summoner, SPELL_HORSE_ROPE, true);
            me->ClearUnitState(UNIT_STATE_CASTING);
            events.ScheduleEvent(EVENT_CHECK_LORNA, 2000);
            events.ScheduleEvent(EVENT_CHECK_OWNER, 2000);
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 2.0f, true);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_LORNA:
                    {
                        if (Creature* lornaCrowley = me->FindNearestCreature(NPC_ENTRY_LORNA_CROWLEY, 8.0f, true))
                        {
                            if (Unit* owner = me->GetCharmerOrOwner())
                            {
                                if (owner->GetTypeId() == TYPEID_PLAYER)
                                    owner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_HORSE);
                            }
                            events.CancelEvent(EVENT_CHECK_LORNA);
                            me->DespawnOrUnsummon(1);
                        }
                        else
                            events.RescheduleEvent(EVENT_CHECK_LORNA, 2000);
                        break;
                    }
                    case EVENT_CHECK_OWNER:
                    {
                        if (Unit* owner = me->GetCharmerOrOwner())
                        {
                            if (!owner->isAlive() || !owner->IsInWorld() || !owner->GetVehicleBase())
                                me->DespawnOrUnsummon(1);

                            events.CancelEvent(EVENT_CHECK_OWNER);
                        }
                        else
                            events.RescheduleEvent(EVENT_CHECK_OWNER, 2000);
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
        return new npc_mountain_horse_summonedAI(creature);
    }
};

class spell_gilneas_test_telescope : public SpellScriptLoader
{
public:
    spell_gilneas_test_telescope() : SpellScriptLoader("spell_gilneas_test_telescope")
    {
    }

    enum musicId
    {
        MUSIC_ENTRY_TELESCOPE   = 23539
    };

    enum cinematicId
    {
        PLAY_CINEMATIC_TELESCOPE    = 167
    };

    class spell_gilneas_test_telescope_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gilneas_test_telescope_SpellScript);

        void StartCinematic()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    caster->PlayDirectSound(MUSIC_ENTRY_TELESCOPE, caster->ToPlayer());
                    caster->ToPlayer()->SendCinematicStart(PLAY_CINEMATIC_TELESCOPE);
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_gilneas_test_telescope_SpellScript::StartCinematic);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gilneas_test_telescope_SpellScript();
    }
};

class npc_stagecoach_carriage_exodus : public CreatureScript
{
public:
    npc_stagecoach_carriage_exodus() : CreatureScript("npc_stagecoach_carriage_exodus")
    {
    }

    enum questId
    {
        QUEST_ENTRY_EXODUS  = 24438
    };

    enum npcId
    {
        NPC_STAGECOACH_HARNESS  = 38755,
        NPC_HARNESS_SUMMONED    = 43336
    };

    enum eventId
    {
        EVENT_BOARD_HARNESS_OWNER   = 1
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_EXODUS) == QUEST_STATUS_COMPLETE)
        {
            if (player->GetVehicleBase())
                return true;

            if (Creature* harness = player->FindNearestCreature(NPC_STAGECOACH_HARNESS, 30.0f, true))
                player->SummonCreature(NPC_HARNESS_SUMMONED, harness->GetPositionX(), harness->GetPositionY(), harness->GetPositionZ(), harness->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(3105)));
            return true;
        }
        return true;
    }

    struct npc_stagecoach_carriage_exodusAI : public ScriptedAI
    {
        npc_stagecoach_carriage_exodusAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(EVENT_BOARD_HARNESS_OWNER, 1);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
        }

        EventMap events;

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BOARD_HARNESS_OWNER:
                    {
                        if (Unit* harness = me->GetVehicleCreatureBase())
                        {
                            if (Unit* harnessOwner = harness->ToTempSummon()->GetSummoner())
                            {
                                if (harnessOwner->isAlive() && harnessOwner->IsInWorld())
                                {
                                    harnessOwner->EnterVehicle(me, 1);
                                    events.CancelEvent(EVENT_BOARD_HARNESS_OWNER);
                                    break;
                                }
                            }
                        }
                        events.CancelEvent(EVENT_BOARD_HARNESS_OWNER);
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
        return new npc_stagecoach_carriage_exodusAI(creature);
    }
};

class npc_stagecoach_harness : public CreatureScript
{
public:
    npc_stagecoach_harness() : CreatureScript("npc_stagecoach_harness")
    {
    }

    struct npc_stagecoach_harnessAI : public npc_escortAI
    {
        npc_stagecoach_harnessAI(Creature* creature) : npc_escortAI(creature)
        {
        }

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum gateId
        {
            GO_FIRST_GATE   = 196401,
            GO_KINGS_GATE   = 196412
        };

        void OnCharmed(bool apply)
        {
        }

        void IsSummonedBy(Unit* owner)
        {
            DoAction(ACTION_START_WP);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(false, true, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(true);
                    if (GameObject* gate = me->FindNearestGameObject(GO_FIRST_GATE, 80.0f))
                        gate->UseDoorOrButton(0, false, me);

                    me->SetWalk(false);
                    me->SetSpeed(MOVE_RUN, 1.34f, true);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 16:    // Open Gate
                {
                    if (GameObject* gate = me->FindNearestGameObject(GO_KINGS_GATE, 80.0f))
                        gate->UseDoorOrButton(0, false, me);
                    break;
                }
                case 24:    // Gwen Armstead - Yell
                {
                    if (Unit* caravan = me->GetVehicleKit()->GetPassenger(2))
                    {
                        if (Unit* lorna = caravan->GetVehicleKit()->GetPassenger(6))
                        {
                            if (lorna->ToCreature())
                                lorna->ToCreature()->AI()->Talk(0);
                        }
                    }
                    break;
                }
                case 30:    // Remove Player from Caravan
                {
                    if (Unit* caravan = me->GetVehicleKit()->GetPassenger(2))
                    {
                        if (Unit* player = caravan->GetVehicleKit()->GetPassenger(1))
                            player->ExitVehicle();
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
        return new npc_stagecoach_harnessAI(creature);
    }
};

void AddSC_gilneas()
{
    // Intro stuffs
    new npc_panicked_citizen_gate();
    new npc_gilneas_city_guard_gate();
    new npc_gilnean_crow();
    new npc_prince_liam_greymane_intro();
    new npc_gilneas_wounded_guard();
    new npc_sergeant_cleese();
    new npc_mariam_spellwalker();

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

    // QUEST - 14159 - The Rebel Lord's Arsenal
    new npc_josiah_avery_worgen();
    new npc_josiah_avery_human();

    // QUEST - 14204 - From the Shadows
    new npc_lorna_crowley_qfs();
    new npc_gilnean_mastiff();
    new npc_bloodfang_lurker();
    new spell_attack_lurker();

    // QUEST - 14293 - Save Krennan Aranas
    new npc_king_genn_greymane();
    new npc_cannon_camera();
    new npc_vehicle_genn_horse();
    new npc_saved_aranas();
    new npc_lord_godfery_p4_8();

    // QUEST - 14294 - Time to Regroup
    new npc_king_genn_greymane_qtr();

    // QUEST - 14212 - Sacrifices
    new npc_lord_darius_crowley_c2();
    new npc_crowley_horse();

    // Quest Last Stand 14222
    new npc_lord_darius_crowley_c3();
    new npc_frenzied_stalker();

    // ----- Chapter 2

    // Quest Last Chance at Humanity 14375
    new npc_king_genn_greymane_qls();
    new npc_krennan_aranas_qls();
    new npc_godfrey_qls();

    // Quest You can't take 'em alon 14348
    new npc_horrid_abbomination();

    // Quest 14320 - In need of Ingrendients
    new go_crate_of_mandrake_essence();

    // Quest 14321 - Invasion
    new npc_slain_watchman();
    new npc_forsaken_assassin();

    new npc_forsaken_invader();
    new npc_duskhaven_watchman();
    new npc_forsaken_footsoldier();
    new npc_dh_forsaken_catapult();
    new spell_catapult_boulder();
    new npc_dh_james();
    new npc_dh_ashley();
    new npc_dh_cynthia();
    new spell_load_catapult_boulder();
    new spell_call_attack_mastiffs();
    new npc_mountain_horse();
    new npc_mountain_horse_summoned();
    new spell_gilneas_test_telescope();
    new npc_stagecoach_carriage_exodus();
    new npc_stagecoach_harness();
}
