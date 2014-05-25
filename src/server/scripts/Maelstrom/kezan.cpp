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

enum DefiantTrollEnum
{
    DEFFIANT_KILL_CREDIT               = 34830,
    SPELL_LIGHTNING_VISUAL             = 66306,
    SPELL_ENRAGE                       = 45111,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND    = 14069,
    GO_DEPOSIT                         = 195489,
    SAY_WORK                           = 0,
    EVENT_RESET_TROLL                  = 1,
    EVENT_WORK_TROLL                   = 2
};

class npc_defiant_troll : public CreatureScript
{
public:
    npc_defiant_troll() : CreatureScript("npc_defiant_troll") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_defiant_trollAI(creature);
    }

    struct npc_defiant_trollAI : public ScriptedAI
    {
        npc_defiant_trollAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void JustReachedHome()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            switch (urand(0, 2))
            {
                case 0:
                    me->HandleEmoteCommand(412);
                    break;
                case 1:
                    me->HandleEmoteCommand(10);
                    break;
                case 2:
                    me->HandleEmoteCommand(0);
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 /*type*/, uint32 id)
        {
            if (id == 1)
                me->HandleEmoteCommand(EMOTE_STATE_WORK_MINING);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_LIGHTNING_VISUAL && caster->GetTypeId() == TYPEID_PLAYER
                && caster->ToPlayer()->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_INCOMPLETE)
            {
                caster->ToPlayer()->KilledMonsterCredit(DEFFIANT_KILL_CREDIT, me->GetGUID());
                me->RemoveAllAuras();
                TalkWithDelay(1000, SAY_WORK);
                me->SetWalk(false);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                events.ScheduleEvent(EVENT_WORK_TROLL, 3500);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RESET_TROLL:
                    {
                        me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        me->GetMotionMaster()->MoveTargetedHome();
                        break;
                    }
                    case EVENT_WORK_TROLL:
                    {
                        if (GameObject* Deposit = me->FindNearestGameObject(GO_DEPOSIT, 2000))
                            me->GetMotionMaster()->MovePoint(1, Deposit->GetPositionX(), Deposit->GetPositionY(), Deposit->GetPositionZ());
                        events.ScheduleEvent(EVENT_RESET_TROLL, 60000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

enum KezanPartygoer
{
    SPELL_HORS_DOEUVRES_AURA        = 75050,
    SPELL_HORS_DOEUVRES             = 66913,
    SPELL_FIREWORKS_AURA            = 75048,
    SPELL_FIREWORKS                 = 66912,
    SPELL_DANCE_AURA                = 75046,
    SPELL_DANCE                     = 66911,
    SPELL_BUCKET_AURA               = 75044,
    SPELL_BUCKET                    = 66910,
    SPELL_BUBBLY_AURA               = 75042,
    SPELL_BUBBLY                    = 66909,
    SPELL_HAPPY_PARTYGOER           = 66916,
    EVENT_RESET_PARTYGOER           = 10
};

uint32 spellId[5] = {75042, 75044, 75046, 75048, 75050};

class npc_kezan_partygoer : public CreatureScript
{
public:
    npc_kezan_partygoer() : CreatureScript("npc_kezan_partygoer") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_kezan_partygoerAI (creature);
    }

    struct npc_kezan_partygoerAI : public ScriptedAI
    {
        npc_kezan_partygoerAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;
        uint64 playerGUID;

        enum talkId
        {
            TALK_DRINK_NEED         = 0,
            TALK_DRINK_THANKS,
            TALK_EAT_NEED,
            TALK_EAT_THANKS,
            TALK_DRUNK_NEED,
            TALK_DRUNK_THANKS,
            TALK_FIREWORKS_NEED,
            TALK_FIREWORKS_THANKS,
            TALK_DANCE_NEED,
            TALK_DANCE_THANKS
        };

        enum questCredit
        {
            QUEST_CREDIT_PARTYGOER   = 35175
        };

        enum spellParty
        {
            SPELL_PARTYGOER_BUBBLY          = 75042,
            SPELL_PARTYGOER_BUCKET          = 75044,
            SPELL_PARTYGOER_DANCE           = 75046,
            SPELL_PARTYGOER_FIREWORKS       = 75048,
            SPELL_PARTYGOER_HORS_DOEUVRES   = 75050,
            SPELL_PARTYGOER_STUNNED         = 78320
        };

        void Reset()
        {
            me->CastSpell(me, spellId[urand(0, 4)], false);
            events.ScheduleEvent(EVENT_RESET_PARTYGOER, urand(45000, 90000));
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            playerGUID = caster->GetGUID();
            Player* player = Unit::GetPlayer(*me, playerGUID);
            switch (spell->Id)
            {
                case SPELL_PARTYGOER_BUBBLY:
                {
                    if (roll_chance_i(6))
                        Talk(TALK_DRINK_NEED);
                    break;
                }
                case SPELL_PARTYGOER_BUCKET:
                {
                    if (roll_chance_i(6))
                        Talk(TALK_DRUNK_NEED);
                    DoCast(SPELL_PARTYGOER_STUNNED);
                    break;
                }
                case SPELL_PARTYGOER_DANCE:
                {
                    if (roll_chance_i(6))
                        Talk(TALK_DANCE_NEED);
                    break;
                }
                case SPELL_PARTYGOER_FIREWORKS:
                {
                    if (roll_chance_i(6))
                        Talk(TALK_FIREWORKS_NEED);
                    break;
                }
                case SPELL_PARTYGOER_HORS_DOEUVRES:
                {
                    if (roll_chance_i(6))
                        Talk(TALK_EAT_NEED);
                    break;
                }
                default:
                    break;
            }

            if (spell->Id == SPELL_HORS_DOEUVRES && me->HasAura(SPELL_HORS_DOEUVRES_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_HORS_DOEUVRES_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                Talk(TALK_EAT_THANKS);
                player->KilledMonsterCredit(QUEST_CREDIT_PARTYGOER, 0);
                events.ScheduleEvent(EVENT_RESET_PARTYGOER, urand(45000, 90000));
            }
            else if (spell->Id == SPELL_FIREWORKS && me->HasAura(SPELL_FIREWORKS_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_FIREWORKS_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                Talk(TALK_FIREWORKS_THANKS);
                player->KilledMonsterCredit(QUEST_CREDIT_PARTYGOER, 0);
                events.ScheduleEvent(EVENT_RESET_PARTYGOER, urand(45000, 90000));
            }
            else if (spell->Id == SPELL_DANCE && me->HasAura(SPELL_DANCE_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_DANCE_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                Talk(TALK_DANCE_THANKS);
                player->KilledMonsterCredit(QUEST_CREDIT_PARTYGOER, 0);
                events.ScheduleEvent(EVENT_RESET_PARTYGOER, urand(45000, 90000));
            }
            else if (spell->Id == SPELL_BUCKET && me->HasAura(SPELL_BUCKET_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_BUCKET_AURA);
                me->RemoveAurasDueToSpell(SPELL_PARTYGOER_STUNNED);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                Talk(TALK_DRUNK_THANKS);
                player->KilledMonsterCredit(QUEST_CREDIT_PARTYGOER, 0);
                events.ScheduleEvent(EVENT_RESET_PARTYGOER, urand(45000, 90000));
            }
            else if (spell->Id == SPELL_BUBBLY && me->HasAura(SPELL_BUBBLY_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_BUBBLY_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                Talk(TALK_DRINK_THANKS);
                player->KilledMonsterCredit(QUEST_CREDIT_PARTYGOER, 0);
                events.ScheduleEvent(EVENT_RESET_PARTYGOER, urand(45000, 90000));
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RESET_PARTYGOER:
                    {
                        me->RemoveAllAuras();
                        Reset();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };
};

enum KajamiteDeposit
{
    LTKQUEST            = 14124,
    KAJAMITECHUNK       = 195492    //Gameobject
};


class go_kajamitedeposit : public GameObjectScript
{
public:
    go_kajamitedeposit() : GameObjectScript("go_kajamitedeposit") {}

    bool OnGossipHello(Player* player, GameObject* pGO)
    {
        if (player->GetQuestStatus(LTKQUEST) == QUEST_STATUS_INCOMPLETE)
        {
            pGO->SummonGameObject(KAJAMITECHUNK, pGO->GetPositionX(), pGO->GetPositionY(), pGO->GetPositionZ(), 0, 0 ,0 ,0 ,0 ,300);
            pGO->SummonGameObject(KAJAMITECHUNK, pGO->GetPositionX()+1, pGO->GetPositionY()+1, pGO->GetPositionZ(), 0, 0 ,0 ,0 ,0 ,300);
            pGO->SummonGameObject(KAJAMITECHUNK, pGO->GetPositionX()-1, pGO->GetPositionY()-1, pGO->GetPositionZ(), 0, 0 ,0 ,0 ,0 ,300);
            pGO->Delete();
            return false;
        }
        return true;
    }
};

enum greatBankHeist
{
    SPELL_AMAZING_GRAY              = 67526,
    SPELL_BLASTCRACKERS             = 67508,
    SPELL_EAROSCOPE                 = 67524,
    SPELL_INFINIFOLD_LOCKPICK       = 67525,
    SPELL_KAJAMITE_DRILL            = 67522,
    SPELL_TIMER_AURA                = 67502,
    SPELL_CORRECT                   = 67493,
    SPELL_INCORRECT                 = 67494,
    SPELL_CRACKED                   = 67492,
    NPC_BANK_VAULT_KILL_CREDIT      = 35486,

    SAY_START                       = 0,
    SAY_HOWTO                       = 1,
    SAY_WILL_OPEN                   = 2,
    SAY_LUCK                        = 3,
    SAY_KAJAMITE                    = 4,
    SAY_CORRECT                     = 5,
    SAY_AMAZING                     = 6,
    SAY_LOCKPICK                    = 7,
    SAY_BLASTCRACKERS               = 8,
    SAY_EAROSCOPE                   = 9,
    SAY_INCORRECT                   = 10,
    SAY_SUCCESS                     = 11,

    PHASE_INTRO                     = 1,
    PHASE_CRACKING                  = 2,
    EVENT_START                     = 1,
    EVENT_HOWTO                     = 2,
    EVENT_WILL_OPEN                 = 3,
    EVENT_LUCK                      = 4,
    EVENT_QUESTION                  = 5,
    EVENT_CORRECT                   = 6,
    EVENT_INCORRECT                 = 7,
    EVENT_TIMER_ZERO                = 8
};

class npc_first_bank_of_kezan_vault : public CreatureScript
{
public:
    npc_first_bank_of_kezan_vault() : CreatureScript("npc_first_bank_of_kezan_vault") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_first_bank_of_kezan_vaultAI(creature);
    }

    struct npc_first_bank_of_kezan_vaultAI : public CreatureAI
    {
        npc_first_bank_of_kezan_vaultAI(Creature* creature) : CreatureAI(creature) {}

        EventMap events;

        uint32 SpellToClick;
        uint64 passengerGUID;
        bool ReadyToClick;

        void Reset()
        {
            events.SetPhase(PHASE_INTRO);
            me->SetPower(me->getPowerType(), 0);
            ReadyToClick = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_AMAZING_GRAY:
                    CheckClickedSpell(1);
                    break;
                case SPELL_BLASTCRACKERS:
                    CheckClickedSpell(2);
                    break;
                case SPELL_EAROSCOPE:
                    CheckClickedSpell(3);
                    break;
                case SPELL_INFINIFOLD_LOCKPICK:
                    CheckClickedSpell(4);
                    break;
                case SPELL_KAJAMITE_DRILL:
                    CheckClickedSpell(5);
                    break;
                default:
                    break;
            }
        }

        void CheckClickedSpell(uint32 ClickedSpell)
        {
            if (ClickedSpell == SpellToClick && ReadyToClick)
            {
                Talk(SAY_CORRECT);
                events.ScheduleEvent(EVENT_CORRECT, 0, PHASE_CRACKING);
                SpellToClick = 0;
            }
            else if (ClickedSpell != SpellToClick && ReadyToClick)
            {
                Talk(SAY_INCORRECT);
                events.ScheduleEvent(EVENT_INCORRECT, 0, PHASE_CRACKING);
                SpellToClick = 0;
            }
            ReadyToClick = false;
            events.CancelEvent(EVENT_TIMER_ZERO);
            events.RescheduleEvent(EVENT_QUESTION, 1000, PHASE_CRACKING);
        }

        void OnCharmed(bool apply)
        {
            me->NeedChangeAI = false;
            me->IsAIEnabled = true;
        }

        void PassengerBoarded(Unit* passenger, int8 /*seat*/, bool apply)
        {
            Player* player = passenger->ToPlayer();
            events.ScheduleEvent(EVENT_START, 4000, PHASE_INTRO);
            passengerGUID = passenger->GetGUID();
            player->KilledMonsterCredit(NPC_BANK_VAULT_KILL_CREDIT);
            if (!apply)
                me->DespawnOrUnsummon(1);
        }

        void Quest(uint32 quest, Unit* unit)
        {
            switch(quest)
            {
                case 1:
                    Talk(SAY_AMAZING);
                    break;
                case 2:
                    Talk(SAY_BLASTCRACKERS);
                    break;
                case 3:
                    Talk(SAY_EAROSCOPE);
                    break;
                case 4:
                    Talk(SAY_LOCKPICK);
                    break;
                case 5:
                    Talk(SAY_KAJAMITE);
                    break;
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
                    case EVENT_START:
                    {
                        Talk(SAY_START);
                        events.ScheduleEvent(EVENT_HOWTO, 10000, PHASE_INTRO);
                        break;
                    }
                    case EVENT_HOWTO:
                    {
                        Talk(SAY_HOWTO);
                        events.ScheduleEvent(EVENT_WILL_OPEN, 13000, PHASE_INTRO);
                        break;
                    }
                    case EVENT_WILL_OPEN:
                    {
                        Talk(SAY_WILL_OPEN);
                        events.ScheduleEvent(EVENT_LUCK, 13000, PHASE_INTRO);
                        break;
                    }
                    case EVENT_LUCK:
                    {
                        Talk(SAY_LUCK);
                        events.SetPhase(PHASE_CRACKING);
                        events.ScheduleEvent(EVENT_QUESTION, 10000, PHASE_CRACKING);
                        break;
                    }
                    case EVENT_QUESTION:
                    {
                        if (Unit* passenger = sObjectAccessor->GetUnit(*me, passengerGUID))
                        {
                            if (me->GetPower(me->getPowerType()) < 100)
                            {
                                ReadyToClick = true;
                                SpellToClick = urand(1, 5);
                                Quest(SpellToClick, passenger);
                                me->CastSpell(passenger, SPELL_TIMER_AURA, true);
                                events.ScheduleEvent(EVENT_QUESTION, 7000, PHASE_CRACKING);
                                events.ScheduleEvent(EVENT_TIMER_ZERO, 5000, PHASE_CRACKING);
                            }

                            if (me->GetPower(me->getPowerType()) == 100)
                            {
                                me->CastSpell(passenger, SPELL_CRACKED, true);
                                Talk(SAY_SUCCESS);
                                passenger->ExitVehicle();
                            }
                        }
                        break;
                    }
                    case EVENT_CORRECT:
                    {
                        me->CastSpell(me, SPELL_CORRECT);
                        break;
                    }
                    case EVENT_INCORRECT:
                    {
                        // me->CastSpell(me, SPELL_INCORRECT);
                        me->SetPower(me->getPowerType(), (me->GetPower(me->getPowerType()))-10);
                        break;
                    }
                    case EVENT_TIMER_ZERO:
                    {
                        ReadyToClick = false;
                        // me->CastSpell(me, SPELL_INCORRECT);
                        me->SetPower(me->getPowerType(), (me->GetPower(me->getPowerType()))-10);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };
};

const Position gasbotWalk[3] =
{
    {-8424.281f, 1332.938f, 101.783f, 0},
    {-8424.281f, 1340.688f, 102.283f, 0},
    {-8423.809f, 1361.664f, 104.671f, 0}
};

enum q447
{
    QUEST_447                   = 14125,
    SPELL_SUMMON_GASBOT         = 70252,
    SPELL_GASBOT_EXPLOSION      = 70259,
    SPELL_EXPLOSION_FIRE        = 70262,
    SPELL_GASBOT_GAS_STREAM     = 70256,
    SPELL_GENERADOR_VISUAL      = 70226,
    SPELL_ESTUFA_VISUAL         = 70236,
    SPELL_CAMA_VISUAL           = 70250,
    NPC_TARGET_GASBOT           = 37599,
    NPC_GASBOT                  = 37598
};

class npc_gasbot : public CreatureScript
{
public:
    npc_gasbot() : CreatureScript("npc_gasbot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gasbotAI (creature);
    }

    struct npc_gasbotAI : public ScriptedAI
    {
        npc_gasbotAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        bool startFire;
        bool summonTargetGasbot;
        uint8 walkCount;
        uint8 phase;
        uint32 walkTimer;
        uint32 gasbotFire;

        void Reset()
        {
            me->SetPhaseMask(4096, 1);
            walkCount = 0;
            startFire = false;
            walkTimer = 100;
            phase = 0;
            summonTargetGasbot = true;
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->CastSpell(me, SPELL_GASBOT_GAS_STREAM, true);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != walkCount)
                return;

            if (id < 2)
            {
                ++walkCount;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (walkTimer <= diff)
            {
                switch (walkCount)
                {
                    case 0:
                        me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                        break;
                    case 1:
                        break;
                    case 2:
                        startFire = true;
                        break;
                    default:
                        break;
                }

                me->GetMotionMaster()->MovePoint(walkCount, gasbotWalk[walkCount]);

                if (startFire)
                {
                    switch (phase)
                    {
                        case 0:
                        {
                            phase = 1;
                            walkTimer = 10000;
                            break;
                        }
                        case 1:
                        {
                            me->CastSpell(me, SPELL_EXPLOSION_FIRE, true);
                            phase = 2;
                            break;
                        }
                        case 2:
                        {
                            if (Player* player = me->FindNearestPlayer(5000.f, true))
                            {
                                if (player->GetQuestStatus(QUEST_447) == QUEST_STATUS_INCOMPLETE)
                                    player->KilledMonsterCredit(37598, 0);
                            }
                            me->CastSpell(me, SPELL_GASBOT_EXPLOSION, true);
                            startFire = false;
                            phase = false;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else
                walkTimer -= diff;
        }
    };
};

class go_gasbot_control_panel : public GameObjectScript
{
public:
    go_gasbot_control_panel() : GameObjectScript("go_gasbot_control_panel") { }

    enum Id
    {
        NPC_ENTRY_GASBOT    = 37598
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_447) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* gasBot = player->FindNearestCreature(NPC_ENTRY_GASBOT, 200.0f, true))
                return true;

            player->SummonCreature(NPC_GASBOT, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
        }
        return true;
    }
};

class npc_hot_rod : public CreatureScript
{
public:
    npc_hot_rod() : CreatureScript("npc_hot_rod") {}

    struct npc_hot_rodAI : public ScriptedAI
    {
        EventMap events;

        enum actionId
        {
            ACTION_SWITCH_RADIO_ON  = 1
        };

        enum spellId
        {
            SPELL_HONK_HORN     = 66298,
            SPELL_KNOCKBACK     = 66301
        };

        enum musicId
        {
            SEND_PLAY_MUSIC_RADIO_ON    = 23406,
            SEND_PLAY_MUSIC_RADIO_OFF   = 1592
        };

        enum eventId
        {
            EVENT_CAST_KNOCKBACK    = 1,
            EVENT_CHECK_PASSENGER
        };

        npc_hot_rodAI(Creature* creature) : ScriptedAI(creature) {}

        void EnableMusic()
        {
            if (Unit* owner = me->GetCharmerOrOwner())
            {
                if (owner->GetTypeId() == TYPEID_PLAYER)
                {
                    WorldPacket data(SMSG_PLAY_MUSIC, 4);
                    data << uint32(SEND_PLAY_MUSIC_RADIO_ON);
                    data << uint64(owner->GetGUID());
                    owner->ToPlayer()->GetSession()->SendPacket(&data);
                    musicEnabled = true;
                }
            }
        }

        void DisableMusic()
        {
            if (Unit* owner = me->GetCharmerOrOwner())
            {
                if (owner->GetTypeId() == TYPEID_PLAYER)
                {
                    WorldPacket data(SMSG_PLAY_MUSIC, 4);
                    data << uint32(SEND_PLAY_MUSIC_RADIO_OFF);
                    data << uint64(owner->GetGUID());
                    owner->ToPlayer()->GetSession()->SendPacket(&data);
                    musicEnabled = false;
                }
            }
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            musicEnabled = false;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_CAST_KNOCKBACK, 1250);
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (!apply && SeatId == 0)
                DisableMusic();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SWITCH_RADIO_ON:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (owner->GetTypeId() == TYPEID_PLAYER)
                        {
                            if (musicEnabled == false)
                                EnableMusic();
                            else
                                DisableMusic();
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
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_KNOCKBACK:
                    {
                        if (Unit* owner = me->GetCharmerOrOwner())
                        {
                            if (me->isMoving())
                                owner->CastSpell(owner, SPELL_KNOCKBACK);
                        }
                        events.ScheduleEvent(EVENT_CAST_KNOCKBACK, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool musicEnabled;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hot_rodAI(creature);
    }
};

class spell_radio_kezan : public SpellScriptLoader
{
    public:
        spell_radio_kezan() : SpellScriptLoader("spell_radio_kezan") { }

        class spell_radio_kezan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_radio_kezan_SpellScript);

            void HandleRadioSwitch()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        return;

                    caster->ToCreature()->AI()->DoAction(1);
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_radio_kezan_SpellScript::HandleRadioSwitch);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_radio_kezan_SpellScript();
        }
};

class spell_honk_horn : public SpellScriptLoader
{
    public:
        spell_honk_horn() : SpellScriptLoader("spell_honk_horn") { }

        class spell_honk_horn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_honk_horn_SpellScript);

            enum npcId
            {
                NPC_ENTRY_GOBBER    = 34954,
                NPC_ENTRY_IZZY      = 34890,
                NPC_ENTRY_ACE       = 34892,
                NPC_ENTRY_CITIZEN   = 35075
            };

            enum creditId
            {
                CREDIT_GOBBER   = 34958,
                CREDIT_IZZY     = 34959,
                CREDIT_ACE      = 34957
            };

            enum spellId
            {
                SPELL_SUMMON_IZZY       = 66600,
                SPELL_SUMMON_GOBBER     = 66599,
                SPELL_SUMMON_ACE        = 66597,
                SPELL_INVISIBILITY_D1   = 49416,
                SPELL_INVISIBILITY_D2   = 49417,
                SPELL_INVISIBILITY_D3   = 60922
            };

            class eventSetWalk : public BasicEvent
            {
                public:
                    explicit eventSetWalk(Creature* creature) : creature(creature) {}

                bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
                {
                    creature->SetWalk(true);
                    return true;
                }

                private:
                    Creature* creature;
            };

            void HandleSummonAndCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = caster->GetCharmerOrOwner())
                    {
                        if (target->FindNearestCreature(NPC_ENTRY_IZZY, 10.0f, true))
                        {
                            target->ToPlayer()->KilledMonsterCredit(CREDIT_IZZY);
                            target->RemoveAurasDueToSpell(SPELL_INVISIBILITY_D3);
                            target->CastSpell(target, SPELL_SUMMON_IZZY, true);
                            return;
                        }
                        else if (target->FindNearestCreature(NPC_ENTRY_GOBBER, 10.0f, true))
                        {
                            target->ToPlayer()->KilledMonsterCredit(CREDIT_GOBBER);
                            target->RemoveAurasDueToSpell(SPELL_INVISIBILITY_D2);
                            target->CastSpell(target, SPELL_SUMMON_GOBBER, true);
                            return;
                        }
                        else if (target->FindNearestCreature(NPC_ENTRY_ACE, 10.0f, true))
                        {
                            target->ToPlayer()->KilledMonsterCredit(CREDIT_ACE);
                            target->RemoveAurasDueToSpell(SPELL_INVISIBILITY_D1);
                            target->CastSpell(target, SPELL_SUMMON_ACE, true);
                            return;
                        }
                        else
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 8.0f);
                            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                            caster->VisitNearbyObject(8.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature())
                                {
                                    if ((*itr)->ToCreature()->GetEntry() == NPC_ENTRY_CITIZEN && (*itr)->isInFront(caster))
                                    {
                                        (*itr)->ToCreature()->AI()->Talk(0, target->GetGUID());
                                        (*itr)->SetWalk(false);
                                        (*itr)->GetMotionMaster()->MoveFleeing(target, 3000);
                                        (*itr)->m_Events.AddEvent(new eventSetWalk((*itr)->ToCreature()), (*itr)->m_Events.CalculateTime(6000));
                                    }
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_honk_horn_SpellScript::HandleSummonAndCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_honk_horn_SpellScript();
        }
};

class npc_izzy_rwmh : public CreatureScript
{
public:
    npc_izzy_rwmh() : CreatureScript("npc_izzy_rwmh") {}

    struct npc_izzy_rwmhAI : public ScriptedAI
    {
        EventMap events;

        enum actionId
        {
            ACTION_MOUNT_HOT_ROD    = 1
        };

        enum eventId
        {
            EVENT_MOUNT_HOT_ROD     = 1,
            EVENT_CHECK_COMBAT
        };

        enum npcId
        {
            NPC_ENTRY_HOT_ROD   = 34840
        };

        npc_izzy_rwmhAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
            events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
        }

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOUNT_HOT_ROD:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_HOT_ROD)
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
                    case EVENT_MOUNT_HOT_ROD:
                    {
                        if (me->GetVehicleBase())
                            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
                        else
                        {
                            DoAction(ACTION_MOUNT_HOT_ROD);
                            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
                        }
                        break;
                    }
                    case EVENT_CHECK_COMBAT:
                    {
                        if (me->isInCombat() && !me->GetCharmerOrOwner()->isInCombat())
                            EnterEvadeMode();

                        events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
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
        return new npc_izzy_rwmhAI(creature);
    }
};

class npc_gobber_rwmh : public CreatureScript
{
public:
    npc_gobber_rwmh() : CreatureScript("npc_gobber_rwmh") {}

    struct npc_gobber_rwmhAI : public ScriptedAI
    {
        EventMap events;

        enum actionId
        {
            ACTION_MOUNT_HOT_ROD    = 1
        };

        enum eventId
        {
            EVENT_MOUNT_HOT_ROD     = 1,
            EVENT_CHECK_COMBAT
        };

        enum npcId
        {
            NPC_ENTRY_HOT_ROD   = 34840
        };

        npc_gobber_rwmhAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
            events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
        }

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOUNT_HOT_ROD:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_HOT_ROD)
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

            DoMeleeAttackIfReady();

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOUNT_HOT_ROD:
                    {
                        if (me->GetVehicleBase())
                            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
                        else
                        {
                            DoAction(ACTION_MOUNT_HOT_ROD);
                            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
                        }
                        break;
                    }
                    case EVENT_CHECK_COMBAT:
                    {
                        if (me->isInCombat() && !me->GetCharmerOrOwner()->isInCombat())
                            EnterEvadeMode();

                        events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
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
        return new npc_gobber_rwmhAI(creature);
    }
};

class npc_ace_rwmh : public CreatureScript
{
public:
    npc_ace_rwmh() : CreatureScript("npc_ace_rwmh") {}

    struct npc_ace_rwmhAI : public ScriptedAI
    {
        EventMap events;

        enum actionId
        {
            ACTION_MOUNT_HOT_ROD    = 1
        };

        enum eventId
        {
            EVENT_MOUNT_HOT_ROD     = 1,
            EVENT_CHECK_COMBAT
        };

        enum npcId
        {
            NPC_ENTRY_HOT_ROD   = 34840
        };

        npc_ace_rwmhAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
            events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
        }

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOUNT_HOT_ROD:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (Unit* vehicle = owner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_ENTRY_HOT_ROD)
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
                    case EVENT_MOUNT_HOT_ROD:
                    {
                        if (me->GetVehicleBase())
                            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
                        else
                        {
                            DoAction(ACTION_MOUNT_HOT_ROD);
                            events.ScheduleEvent(EVENT_MOUNT_HOT_ROD, 2000);
                        }
                        break;
                    }
                    case EVENT_CHECK_COMBAT:
                    {
                        if (me->isInCombat() && !me->GetCharmerOrOwner()->isInCombat())
                            EnterEvadeMode();

                        events.ScheduleEvent(EVENT_CHECK_COMBAT, 5000);
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
        return new npc_ace_rwmhAI(creature);
    }
};

class spell_despawn_steamwheedle_sharks : public SpellScriptLoader
{
    public:
        spell_despawn_steamwheedle_sharks() : SpellScriptLoader("spell_despawn_steamwheedle_sharks") { }

        class spell_despawn_steamwheedle_sharks_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_despawn_steamwheedle_sharks_SpellScript);

            enum Id
            {
                // Npc
                NPC_ENTRY_STEAMWHEEDLE_SHARK    = 37114,
                SPELL_STEAMWHEEDLE_SHARK_00     = 69971,
                SPELL_STEAMWHEEDLE_SHARK_01     = 69976,
                SPELL_STEAMWHEEDLE_SHARK_02     = 69977,
                SPELL_STEAMWHEEDLE_SHARK_03     = 69978,
                SPELL_STEAMWHEEDLE_SHARK_04     = 69979,
                SPELL_STEAMWHEEDLE_SHARK_05     = 69980,
                SPELL_STEAMWHEEDLE_SHARK_06     = 69981,
                SPELL_STEAMWHEEDLE_SHARK_07     = 69982
            };

            void HandleRemoveSummoned()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(caster, caster, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                        caster->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isSummon() && ((*itr)->ToTempSummon()->GetCharmerOrOwner() == caster))
                            {
                                switch ((*itr)->ToTempSummon()->GetEntry())
                                {
                                    case NPC_ENTRY_STEAMWHEEDLE_SHARK:
                                        ((*itr)->ToTempSummon()->UnSummon());
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_despawn_steamwheedle_sharks_SpellScript::HandleRemoveSummoned);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_despawn_steamwheedle_sharks_SpellScript();
        }
};

class npc_buccaneer_goal : public CreatureScript
{
public:
    npc_buccaneer_goal() : CreatureScript("npc_buccaneer_goal") {}

    struct npc_buccaneer_goalAI : public ScriptedAI
    {
        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_SUMMON_DEATHWING  = 66322,
            SPELL_RIDE_BUCCANEER    = 63313
        };

        enum actionId
        {
            ACTION_SUMMON_DEATHWING     = 1
        };

        enum eventId
        {
            EVENT_PLAY_CHEER    = 1
        };

        enum soundId
        {
            PLAY_SOUND_CHEER    = 17467
        };

        enum questId
        {
            QUEST_ENTRY_FOURTH_AND_GOAL     = 28414
        };

        npc_buccaneer_goalAI(Creature* creature) : ScriptedAI(creature) {playerInvoker = NULL;}

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* summoner)
        {
            playerInvoker = summoner;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            summoner->AddAura(SPELL_UNIQUE_PHASING, summoner);
            summoner->AddAura(SPELL_UNIQUE_PHASING, me);
            summoner->CastSpell(me, SPELL_RIDE_BUCCANEER, true);
            events.ScheduleEvent(EVENT_PLAY_CHEER, 100);
            me->SetReactState(REACT_PASSIVE);
            eventInProgress = false;
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (apply)
                TalkWithDelay(1000, 0, playerInvoker->GetGUID());
            else
                me->DespawnOrUnsummon(1000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_DEATHWING:
                {
                    if (!playerInvoker || playerInvoker == NULL || !playerInvoker->ToPlayer())
                        return;

                    if (eventInProgress)
                        return;

                    if (playerInvoker->ToPlayer()->GetQuestStatus(QUEST_ENTRY_FOURTH_AND_GOAL) == QUEST_STATUS_COMPLETE)
                        return;

                    eventInProgress = true;
                    me->AddUnitState(UNIT_STATE_STUNNED);
                    playerInvoker->CastWithDelay(3000, playerInvoker, SPELL_SUMMON_DEATHWING, true);
                    events.CancelEvent(EVENT_PLAY_CHEER);
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
                    case EVENT_PLAY_CHEER:
                    {
                        if (playerInvoker && playerInvoker != NULL && playerInvoker->ToPlayer())
                            me->PlayDirectSound(PLAY_SOUND_CHEER, playerInvoker->ToPlayer());
                        events.ScheduleEvent(EVENT_PLAY_CHEER, urand (2000, 2500));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerInvoker;
        bool eventInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_buccaneer_goalAI(creature);
    }
};

class spell_kick_footbomb_goal : public SpellScriptLoader
{
    public:
        spell_kick_footbomb_goal() : SpellScriptLoader("spell_kick_footbomb_goal") { }

        class spell_kick_footbomb_goal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_kick_footbomb_goal_SpellScript);

            void HandleSummonAndCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        return;

                    caster->ToCreature()->AI()->DoAction(1);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_kick_footbomb_goal_SpellScript::HandleSummonAndCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_kick_footbomb_goal_SpellScript();
        }
};

class npc_deathwing_goal : public CreatureScript
{
public:
    npc_deathwing_goal() : CreatureScript("npc_deathwing_goal") { }

    struct npc_deathwing_goalAI : public npc_escortAI
    {
        npc_deathwing_goalAI(Creature* creature) : npc_escortAI(creature) {playerInvoker = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_WP_START     = 1
        };

        enum soundId
        {
            DEATHWING_APPEAR_1  = 23227,
            DEATHWING_APPEAR_2  = 23229,
            DEATHWING_APPEAR_3  = 23230,
            PLAY_SOUND_CHEER    = 17466
        };

        enum spellId
        {
            SPELL_DEATHWING_EARTHQUAKE  = 96274
        };

        enum questCredit
        {
            QUEST_CREDIT_FOURTH_AND_GOAL    = 37203
        };

        void IsSummonedBy(Unit* summoner)
        {
            playerInvoker = summoner;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_NON_ATTACKABLE);
            DoAction(ACTION_WP_START);
            summoner->CastSpell(summoner, SPELL_DEATHWING_EARTHQUAKE, true);
            if (summoner && summoner->GetTypeId() == TYPEID_PLAYER)
            {
                summoner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FOURTH_AND_GOAL);
                me->PlayDirectSound(DEATHWING_APPEAR_1, summoner->ToPlayer());
                me->PlayDirectSound(DEATHWING_APPEAR_2, summoner->ToPlayer());
                me->PlayDirectSound(PLAY_SOUND_CHEER, summoner->ToPlayer());
            }
            TalkWithDelay(6000, 0, summoner->GetGUID());
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                {
                    if (playerInvoker && playerInvoker != NULL && playerInvoker->ToPlayer())
                        me->PlayDirectSound(DEATHWING_APPEAR_2, playerInvoker->ToPlayer());
                    break;
                }
                case 4:
                case 5:
                {
                    if (playerInvoker && playerInvoker != NULL && playerInvoker->ToPlayer())
                    {
                        playerInvoker->CastSpell(playerInvoker, SPELL_DEATHWING_EARTHQUAKE, true);
                        me->PlayDirectSound(DEATHWING_APPEAR_3, playerInvoker->ToPlayer());
                        if (playerInvoker->GetVehicle())
                            playerInvoker->GetVehicle()->RemoveAllPassengers();
                    }
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
                    Start(false, true, NULL, NULL, false, false, true);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerInvoker;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_deathwing_goalAI (creature);
    }
};

class npc_buccaneer_roughness : public CreatureScript
{
public:
    npc_buccaneer_roughness() : CreatureScript("npc_buccaneer_roughness") {}

    struct npc_buccaneer_roughnessAI : public ScriptedAI
    {
        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING            = 60191,
            SPELL_STEAMWHEEDLE_SHARK_00     = 69971,
            SPELL_STEAMWHEEDLE_SHARK_01     = 69976,
            SPELL_STEAMWHEEDLE_SHARK_02     = 69977,
            SPELL_STEAMWHEEDLE_SHARK_03     = 69978,
            SPELL_STEAMWHEEDLE_SHARK_04     = 69979,
            SPELL_STEAMWHEEDLE_SHARK_05     = 69980,
            SPELL_STEAMWHEEDLE_SHARK_06     = 69981,
            SPELL_STEAMWHEEDLE_SHARK_07     = 69982
        };

        enum actionId
        {
            ACTION_SUMMON_SHARKS    = 1
        };

        enum eventId
        {
            EVENT_PLAY_CHEER    = 1
        };

        enum soundId
        {
            PLAY_SOUND_CHEER    = 17466
        };

        npc_buccaneer_roughnessAI(Creature* creature) : ScriptedAI(creature) {playerInvoker = NULL;}

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* summoner)
        {
            playerInvoker = summoner;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            summoner->AddAura(SPELL_UNIQUE_PHASING, summoner);
            summoner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_PLAY_CHEER, 500);
            DoAction(ACTION_SUMMON_SHARKS);
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (apply)
                TalkWithDelay(500, 0, playerInvoker->GetGUID());
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_SHARKS:
                {
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_00, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_01, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_02, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_03, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_04, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_05, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_06, true);
                    playerInvoker->CastSpell(playerInvoker, SPELL_STEAMWHEEDLE_SHARK_07, true);
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
                    case EVENT_PLAY_CHEER:
                    {
                        if (playerInvoker && playerInvoker != NULL && playerInvoker->ToPlayer())
                            me->PlayDirectSound(PLAY_SOUND_CHEER, playerInvoker->ToPlayer());
                        events.ScheduleEvent(EVENT_PLAY_CHEER, urand (2000, 2500));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerInvoker;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_buccaneer_roughnessAI(creature);
    }
};

class spell_awesome_party_ensemble : public SpellScriptLoader
{
    public:
        spell_awesome_party_ensemble() : SpellScriptLoader("spell_awesome_party_ensemble") { }

        class spell_awesome_party_ensemble_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_awesome_party_ensemble_SpellScript);

            enum Id
            {
                SPELL_KEYS_TO_THE_HOT_ROD   = 91551,
                NPC_ENTRY_CHIP_ENDALE       = 35054
            };

            void HandleRemoveHotRod()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->RemoveAurasDueToSpell(SPELL_KEYS_TO_THE_HOT_ROD);
                }
            }

            void HandleTalkEmote()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        caster->MonsterWhisper("You're dressed to impress! Use your new powers below to make your party guests happy!", caster->GetGUID(), true);
                        if (Creature* chipEndale = caster->FindNearestCreature(NPC_ENTRY_CHIP_ENDALE, 15.0f, true))
                            chipEndale->AI()->Talk(0, caster->GetGUID());
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_awesome_party_ensemble_SpellScript::HandleRemoveHotRod);
                AfterCast += SpellCastFn(spell_awesome_party_ensemble_SpellScript::HandleTalkEmote);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_awesome_party_ensemble_SpellScript();
        }
};

class npc_frightened_partygoer : public CreatureScript
{
public:
    npc_frightened_partygoer() : CreatureScript("npc_frightened_partygoer") {}

    struct npc_frightened_partygoerAI : public ScriptedAI
    {
        EventMap events;

        enum actionId
        {
            ACTION_SET_FLEEING     = 1
        };

        enum eventId
        {
            EVENT_CHECK_FLEEING_TIME    = 1,
            EVENT_CHECK_HEALTH
        };

        class eventEvade : public BasicEvent
        {
            public:
                explicit eventEvade(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->AI()->Reset();
                creature->AI()->EnterEvadeMode();
                return true;
            }

        private:
            Creature* creature;
        };

        npc_frightened_partygoerAI(Creature* creature) : ScriptedAI(creature) {creatureAttacker = NULL;}

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SET_FLEEING:
                {
                    if (creatureAttacker && creatureAttacker != NULL)
                    {
                        me->AttackStop();
                        me->SetWalk(false);
                        me->GetMotionMaster()->MoveFleeing(creatureAttacker, 6000);
                        me->m_Events.AddEvent(new eventEvade(me), (me)->m_Events.CalculateTime(6100));
                        me->SetHealth(me->GetMaxHealth());
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void Reset()
        {
            creatureAttacker = NULL;
        }

        void EnterCombat(Unit* attacker)
        {
            creatureAttacker = attacker;
            events.ScheduleEvent(EVENT_CHECK_FLEEING_TIME, urand(6000, 8000));
            events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_FLEEING_TIME:
                    {
                        if (me->isInCombat())
                            DoAction(ACTION_SET_FLEEING);
                        else
                            events.ScheduleEvent(EVENT_CHECK_FLEEING_TIME, urand(6000, 8000));
                        break;
                    }
                    case EVENT_CHECK_HEALTH:
                    {
                        if (me->GetHealthPct() < 25)
                            events.ScheduleEvent(EVENT_CHECK_FLEEING_TIME, 1000);
                        events.ScheduleEvent(EVENT_CHECK_HEALTH, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        Unit* creatureAttacker;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frightened_partygoerAI(creature);
    }
};

class spell_hobart_ingenious_cap : public SpellScriptLoader
{
    public:
        spell_hobart_ingenious_cap() : SpellScriptLoader("spell_hobart_ingenious_cap") { }

        class spell_hobart_ingenious_cap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hobart_ingenious_cap_SpellScript);

            enum Id
            {
                NPC_ENTRY_MOOK_DISGUISE     = 48925
            };

            void HandleSummonMook()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        caster->SummonCreature(NPC_ENTRY_MOOK_DISGUISE, caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(64)));
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_hobart_ingenious_cap_SpellScript::HandleSummonMook);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hobart_ingenious_cap_SpellScript();
        }
};

class go_first_bank_of_kezan : public GameObjectScript
{
public:
    go_first_bank_of_kezan() : GameObjectScript("go_first_bank_of_kezan") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetVehicleBase())
            return true;
        return false;
    }
};

void AddSC_kezan()
{
    new npc_defiant_troll();
    new npc_kezan_partygoer();
    new go_kajamitedeposit();
    new npc_first_bank_of_kezan_vault();
    new npc_gasbot();
    new go_gasbot_control_panel();
    new npc_hot_rod();
    new spell_radio_kezan();
    new spell_honk_horn();
    new npc_gobber_rwmh();
    new npc_ace_rwmh();
    new npc_izzy_rwmh();
    new spell_despawn_steamwheedle_sharks();
    new npc_buccaneer_goal();
    new spell_kick_footbomb_goal();
    new npc_deathwing_goal();
    new npc_buccaneer_roughness();
    new spell_awesome_party_ensemble();
    new npc_frightened_partygoer();
    new spell_hobart_ingenious_cap();
    new go_first_bank_of_kezan();
}
