/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2012 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
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

/* ScriptData
SDName: Elwynn_Forest
SD%Complete: 50
SDComment: Quest support: 1786
SDCategory: Elwynn Forest
EndScriptData */

/* ContentData
npc_henze_faulk
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_stormwind_infantry
######*/

enum Northshire
{
    NPC_BLACKROCK_BATTLE_WORG = 49871,
    NPC_STORMWIND_INFANTRY    = 49869,
    NPC_BROTHER_PAXTON        = 951,
/*
    SAY_INFANTRY_NORMAL_1     = "Mir... Mir geht's gut!"
    SAY_INFANTRY_NORMAL_2     = "Macht Euch nuetzlich und heilt mich, Paxton!
    SAY_INFANTRY_NORMAL_3     = "HILFE!
    SAY_INFANTRY_COMBAT_1     = "Ich koennte etwas Heilung gebrauchen, Bruder!"
    SAY_INFANTRY_COMBAT_2     = "Macht Euch nuetzlich und heilt mich, Paxton!"
    SAY_INFANTRY_COMBAT_3     = "HILFE!
    SAY_PAXTON_NORMAL_1       = "UND ICH LEGE EUCH MEINE HAENDE AUF!"
    SAY_PAXTON_NORMAL_2       = "KAEMPFT WEITER, BRUDER!"

    SAY_BLACKROCK_COMBAT_1    = "Orc TOETEN Mensch!
    SAY_BLACKROCK_COMBAT_2    = "Fleht um Euer Leben!

    SAY_ASSASSIN_COMBAT_1     = "Zeit, Euch zu Euren Freunden zu gesellen, mit dem Gesicht im Dreck!
    SAY_ASSASSIN_COMBAT_2     = "Wir brennen hier alles nieder!
*/
    SPELL_SPYING              = 92857,
    SPELL_SNEAKING            = 93046,
    SPELL_SPYGLASS            = 80676,

    SPELL_RENEW               = 93094,
    SPELL_PRAYER_OF_HEALING   = 93091,
    SPELL_FORTITUDE           = 13864,
    SPELL_PENANCE             = 47750,
    SPELL_FLASH_HEAL          = 17843,
};

class npc_stormwind_infantry : public CreatureScript
{
public:
    npc_stormwind_infantry() : CreatureScript("npc_stormwind_infantry") { }

    struct npc_stormwind_infantryAI : public ScriptedAI
    {
        npc_stormwind_infantryAI(Creature* creature) : ScriptedAI(creature)
        {
            me->HandleEmoteCommand(EMOTE_STATE_READY1H);
        }

        EventMap events;

        void EnterCombat(Unit * who)
        {
            me->AddUnitState(UNIT_STATE_ROOT);
            me->HandleEmoteCommand(EMOTE_STATE_READY1H);
        }

        void Reset()
        {
            me->HandleEmoteCommand(EMOTE_STATE_READY1H);
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType /*damageType*/)
        {
            if (target->GetEntry() == NPC_BLACKROCK_BATTLE_WORG)
            {
                damage = 0;
                target->SetHealth(target->GetMaxHealth() * 0.95);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stormwind_infantryAI (creature);
    }
};

/*######
## npc_blackrock_battle_worg
######*/

class npc_blackrock_battle_worg : public CreatureScript
{
public:
    npc_blackrock_battle_worg() : CreatureScript("npc_blackrock_battle_worg") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_battle_worgAI (creature);
    }

    struct npc_blackrock_battle_worgAI : public ScriptedAI
    {
        npc_blackrock_battle_worgAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterEvadeMode()
        {
            me->RemoveAllAuras();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_PASSIVE);
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_BLACKROCK_BATTLE_WORG)
            {
                damage = 0;
                target->SetHealth(target->GetMaxHealth() * 0.95);
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (Creature* guard = me->FindNearestCreature(NPC_STORMWIND_INFANTRY, 6.0f, true))
                {
                    guard->getThreatManager().resetAllAggro();
                    guard->CombatStop(true);
                }

                me->SetReactState(REACT_AGGRESSIVE);
                me->AI()->AttackStart(who);
            }
            else
            {
                if (who->isPet())
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->AI()->AttackStart(who);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                if (Creature* guard = me->FindNearestCreature(NPC_STORMWIND_INFANTRY, 6.0f, true))
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->AI()->AttackStart(guard);
                }
                else
                    return;

            DoMeleeAttackIfReady();
        }
    };
};

enum
{
    SPELL_RENEWEDLIFE           = 93097,
    NPC_INJURED_SOLDIER_DUMMY   = 50378,

    ACTION_HEAL                 = 1,
    EVENT_HEALED_1              = 1,
    EVENT_HEALED_2              = 2,
};

class npc_injured_soldier : public CreatureScript
{
public:
    npc_injured_soldier() : CreatureScript("npc_injured_soldier") { }

    struct npc_injured_soldierAI : public ScriptedAI
    {
        npc_injured_soldierAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;
        Player* owner;

        void Reset()
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_14);
            me->SetFlag(UNIT_FIELD_BYTES_1, 7);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		}
		
		void SpellHit(Unit* /*target*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_RENEWEDLIFE)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_14);
                me->RemoveFlag(UNIT_FIELD_BYTES_1, 7);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoAction(ACTION_HEAL);
                owner = me->FindNearestPlayer(8.0f, true);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_HEAL:
                    events.ScheduleEvent(EVENT_HEALED_1, 2000);
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
                    case EVENT_HEALED_1:
                        if (owner)
                        {
                            switch(urand(0, 3))
                            {
                                case 0:
                                    me->MonsterSay("Ich fuerchte mich vor keinem Uebel! ", 0, NULL);
                                    break;
                                case 1:
                                    me->MonsterSay("Mir... Mir geht's gut!", 0, NULL);
                                    break;
                                case 2:
                                    me->MonsterSay("Danket dem Licht!", 0, NULL);
                                    break;
                                case 3:
                                    me->MonsterSay("Ihr seid $p! Der Held, von dem alle sprechen! Ich danke Euch!", 0, owner->GetGUID());
                                    break;
                                default:
                                    break;
                            }
                            me->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                            owner->KilledMonsterCredit(me->GetEntry(), NULL);
                            events.ScheduleEvent(EVENT_HEALED_2, 2500);
                        }
                        break;
                    case EVENT_HEALED_2:
                        me->GetMotionMaster()->MovePoint(0, -8914.525f, -133.963f, 80.534f);
                        me->DespawnOrUnsummon(8000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_soldierAI (creature);
    }
};

enum HoggerSpells
{
    SPELL_SUMMON_MINIONS    = 87366,
    SPELL_EVIL_SLICE        = 87337,
    SPELL_EAT               = 87351,
    SPELL_UPSET_STOMACH     = 87352,
    SPELL_TELEPORT_VISUAL   = 41232,
};

enum HoggerNpcs
{
    NPC_HOGGER_MINION       = 46932,
    NPC_GENERAL_MARCUS      = 46942,
    NPC_MAGINOR_DUMAS       = 46940,
    NPC_ANDROMATH           = 46941,
    NPC_RAGAMUFFIN          = 46943,
};

enum HoggerEvents
{
    EVENT_SLICE = 1,
    EVENT_MOVE_EAT,
    EVENT_EAT,
    EVENT_MOVE_CAPTURE,
    EVENT_GRAWL,
    EVENT_TALK_GENERAL_1,
};

enum HoggerTexts
{
    // Hogger
    SAY_HELP        = 1,
    SAY_DONT_HURT   = 2,
    SAY_GRAWL       = 3,
    SAY_NO          = 4,
    // General
    SAY_OUTRO_1     = 1,
    SAY_OUTRO_2     = 2,
    SAY_OUTRO_3     = 3,
};

// The elwynn hogger casts random spells until 50% hp. after that
// he is going to heal himself by eating meat and getting stunned
// after completing this. if the moves to his meat he summons 3 minions
// at 1 hp hogger moves to a point and flees for not getting killed.
// after that 46942 appears with 2 mages 46940(l) and 46941(r)
// after the mismount  2 childrens 46943 appear behind the commander
Position const HoggerPos[] = {-10134.947f, 669.700f, 35.802f, 0.0f};

class npc_hogger : public CreatureScript
{
public:
    npc_hogger() : CreatureScript("npc_hogger") { }

    struct npc_hoggerAI : public ScriptedAI
    {
        npc_hoggerAI(Creature* creature) : ScriptedAI(creature)
        {
            finished = false;
        }

        EventMap events;
        bool finished;

        void Reset()
        {
            events.Reset();
            finished = false;
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_SLICE, 8000);
        }

        void JustDied(Unit* /*killer*/)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPctDamaged(1, damage) && !finished)
            {
                if (damage > me->GetHealth())
                {
                    damage = 0;
                    finished = true;
                    me->SetHealth(1);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetWalk(true);
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    events.Reset();
                    me->GetMotionMaster()->MovePoint(1, HoggerPos->GetPositionX(), HoggerPos->GetPositionY(), HoggerPos->GetPositionZ(), false);
                    Talk(SAY_DONT_HURT);
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case 1:
                    events.ScheduleEvent(EVENT_MOVE_CAPTURE, 1000);
                    break;
                default:
                    break;
            }
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
                    case EVENT_SLICE:
                        DoCastVictim(SPELL_EVIL_SLICE);
                        events.ScheduleEvent(EVENT_SLICE, 8000);
                        break;
                    case EVENT_MOVE_CAPTURE:
                    {
                        events.ScheduleEvent(EVENT_GRAWL, 3000);
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_GENERAL_MARCUS, 200.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->SetWalk(true);
                            (*itr)->SetPhaseMask(me->GetPhaseMask(), true);
                            (*itr)->CastSpell((*itr), SPELL_TELEPORT_VISUAL);
                            (*itr)->GetMotionMaster()->MovePoint(0, (*itr)->GetPositionX()+cos((*itr)->GetOrientation())*10, (*itr)->GetPositionY()+sin((*itr)->GetOrientation())*10, (*itr)->GetPositionZ(), false);
                        }
                        GetCreatureListWithEntryInGrid(units, me, NPC_ANDROMATH, 200.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->SetWalk(true);
                            (*itr)->SetPhaseMask(me->GetPhaseMask(), true);
                            (*itr)->CastSpell((*itr), SPELL_TELEPORT_VISUAL);
                            (*itr)->GetMotionMaster()->MovePoint(0, (*itr)->GetPositionX()+cos((*itr)->GetOrientation())*10, (*itr)->GetPositionY()+sin((*itr)->GetOrientation())*10, (*itr)->GetPositionZ(), false);
                        }
                        GetCreatureListWithEntryInGrid(units, me, NPC_MAGINOR_DUMAS, 200.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        {
                            (*itr)->SetWalk(true);
                            (*itr)->SetPhaseMask(me->GetPhaseMask(), true);
                            (*itr)->CastSpell((*itr), SPELL_TELEPORT_VISUAL);
                            (*itr)->GetMotionMaster()->MovePoint(0, (*itr)->GetPositionX()+cos((*itr)->GetOrientation())*10, (*itr)->GetPositionY()+sin((*itr)->GetOrientation())*10, (*itr)->GetPositionZ(), false);
                        }
                        break;
                    }
                    case EVENT_GRAWL:
                        Talk(SAY_GRAWL);
                        events.ScheduleEvent(EVENT_TALK_GENERAL_1, 3000);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            me->DespawnCreaturesInArea(NPC_HOGGER_MINION, 200.0f);
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoggerAI (creature);
    }
};

void AddSC_elwynn_forest()
{
    new npc_stormwind_infantry();
    new npc_blackrock_battle_worg();
    new npc_injured_soldier();
    new npc_hogger();
}