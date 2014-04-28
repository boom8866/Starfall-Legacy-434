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
#include "Player.h"
#include "Vehicle.h"
#include "Creature.h"

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
                events.ScheduleEvent(EVENT_WORK_TROLL, 0);
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
                    me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                    me->GetMotionMaster()->MoveTargetedHome();
                    break;
                case EVENT_WORK_TROLL:
                    Talk(SAY_WORK);
                    me->RemoveAllAuras();
                    me->SetWalk(false);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    if (GameObject* Deposit = me->FindNearestGameObject(GO_DEPOSIT, 2000))
                        me->GetMotionMaster()->MovePoint(1, Deposit->GetPositionX(), Deposit->GetPositionY(), Deposit->GetPositionZ());
                    events.ScheduleEvent(EVENT_RESET_TROLL, 120000);
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
    EVENT_RESET_PARTYGOER           = 3
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

        void Reset()
        {
            me->CastSpell(me, spellId[urand(0, 4)], false);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            playerGUID = caster->GetGUID();
            Player* player = Unit::GetPlayer(*me, playerGUID);
            if (spell->Id == SPELL_HORS_DOEUVRES && me->HasAura(SPELL_HORS_DOEUVRES_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_HORS_DOEUVRES_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                player->KilledMonsterCredit(35175, 0);
            }
            else if (spell->Id == SPELL_FIREWORKS && me->HasAura(SPELL_FIREWORKS_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_FIREWORKS_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                player->KilledMonsterCredit(35175, 0);
            }
            else if (spell->Id == SPELL_DANCE && me->HasAura(SPELL_DANCE_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_DANCE_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                player->KilledMonsterCredit(35175, 0);
            }
            else if (spell->Id == SPELL_BUCKET && me->HasAura(SPELL_BUCKET_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_BUCKET_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                player->KilledMonsterCredit(35175, 0);
            }
            else if (spell->Id == SPELL_BUBBLY && me->HasAura(SPELL_BUBBLY_AURA))
            {
                me->RemoveAurasDueToSpell(SPELL_BUBBLY_AURA);
                me->CastSpell(me, SPELL_HAPPY_PARTYGOER, true);
                player->KilledMonsterCredit(35175, 0);
            }
            if (spell->Id == SPELL_HAPPY_PARTYGOER)
                events.ScheduleEvent(EVENT_RESET_PARTYGOER, 30000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RESET_PARTYGOER:
                    me->RemoveAllAuras();
                    Reset();
                    break;
                }
            }
        }
    };
};

enum KajamiteDeposit
{
    LTKQUEST            = 14124,
    KAJAMITECHUNK       = 195492, //Gameobject
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
    EVENT_TIMER_ZERO                = 8,
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
            case SPELL_AMAZING_GRAY: CheckClickedSpell(1);
            case SPELL_BLASTCRACKERS: CheckClickedSpell(2);
            case SPELL_EAROSCOPE: CheckClickedSpell(3);
            case SPELL_INFINIFOLD_LOCKPICK: CheckClickedSpell(4);
            case SPELL_KAJAMITE_DRILL: CheckClickedSpell(5);
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
                    Talk(SAY_START);
                    events.ScheduleEvent(EVENT_HOWTO, 10000, PHASE_INTRO);
                    break;
                case EVENT_HOWTO:
                    Talk(SAY_HOWTO);
                    events.ScheduleEvent(EVENT_WILL_OPEN, 13000, PHASE_INTRO);
                    break;
                case EVENT_WILL_OPEN:
                    Talk(SAY_WILL_OPEN);
                    events.ScheduleEvent(EVENT_LUCK, 13000, PHASE_INTRO);
                    break;
                case EVENT_LUCK:
                    Talk(SAY_LUCK);
                    events.SetPhase(PHASE_CRACKING);
                    events.ScheduleEvent(EVENT_QUESTION, 10000, PHASE_CRACKING);
                    break;
                case EVENT_QUESTION:
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
                case EVENT_CORRECT:
                    me->CastSpell(me, SPELL_CORRECT);
                    break;
                case EVENT_INCORRECT:
                    // me->CastSpell(me, SPELL_INCORRECT);
                    me->SetPower(me->getPowerType(), (me->GetPower(me->getPowerType()))-10);
                    break;
                case EVENT_TIMER_ZERO:
                    ReadyToClick = false;
                    // me->CastSpell(me, SPELL_INCORRECT);
                    me->SetPower(me->getPowerType(), (me->GetPower(me->getPowerType()))-10);
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
    NPC_GASBOT                  = 37598,
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
                }

                me->GetMotionMaster()->MovePoint(walkCount, gasbotWalk[walkCount]);

                if (startFire)
                {
                    switch (phase)
                    {
                    case 0:
                        phase = 1;
                        walkTimer = 10000;
                        break;
                    case 1:
                        me->CastSpell(me, SPELL_EXPLOSION_FIRE, true);
                        phase = 2;
                        break;
                    case 2:
                        if (Player* player = me->FindNearestPlayer(5000.f, true))
                            if (player->GetQuestStatus(QUEST_447) == QUEST_STATUS_INCOMPLETE)
                                player->KilledMonsterCredit(37598, 0);
                        me->CastSpell(me, SPELL_GASBOT_EXPLOSION, true);
                        startFire = false;
                        phase = false;
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

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_447) == QUEST_STATUS_INCOMPLETE)
            go->SummonCreature(NPC_GASBOT, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);

        //player->CastSpell(player, SPELL_SUMMON_GASBOT, true);
        return true;
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
}
