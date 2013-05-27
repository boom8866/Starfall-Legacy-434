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

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_BLACKROCK_BATTLE_WORG)
                target->SetHealth(67);
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
            me->SetReactState(REACT_PASSIVE);
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_STORMWIND_INFANTRY)
                target->SetHealth(119);
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

                me->getThreatManager().resetAllAggro();
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

void AddSC_elwynn_forest()
{
    new npc_stormwind_infantry();
    new npc_blackrock_battle_worg();
    new npc_injured_soldier();
}