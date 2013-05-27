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

#include "ScriptPCH.h"
#include "Creature.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/*
 *  @Npc   : Darnell (49337)
 *  @Quest : Beyond the Graves (25089) & Recruitment (26800)
 *  @Descr : Speak with Deathguard Saltain at Deathknell in Tirisfal Glades.
 */

enum NpcDarnell
{
    SAY_HI,
    SAY_KNOW_THE_WAY,
    SAY_GOOD,
    SAY_HERE_IS_HE,
    SAY_ON_THE_WAY,
    SAY_I_THINK,

    PART_ESCORT_TO_SATAIN,
    PART_PENDING,
    PART_COLLECT_CORPSES,
    PART_WALK_TO_CORPSE,

    POINT_PICK_CORPSE       = 100,

    NPC_DEATHGUARD_SALTAIN  = 1740,
    NPC_SCARLET_CORPSE      = 49340,

    QUEST_BEYOND_THE_GRAVES = 25089,
    QUEST_RECRUITMENT       = 26800,

    SPELL_SUMMON_DARNELL    = 91938,
    SPELL_STUMPED_OVER      = 91935,

    MAX_CORPSE              = 6
};

class npc_darnell : public CreatureScript
{
public:
    npc_darnell() : CreatureScript("npc_darnell") { }

    struct npc_darnellAI : public npc_escortAI
    {
        npc_darnellAI(Creature* creature) : npc_escortAI(creature), part(PART_ESCORT_TO_SATAIN), timer_check(1000), corpse(nullptr), seat(0) {}

        void OnCharmed(bool /*apply*/) {}

        void IsSummonedBy(Unit* summoner)
        {
            if (me->FindNearestCreature(NPC_DEATHGUARD_SALTAIN, 20.f))
            {
                part = PART_COLLECT_CORPSES;
                FollowPlayer();
                TalkWithDelay(3500, SAY_ON_THE_WAY, me->GetOwnerGUID());
                TalkWithDelay(8000, SAY_I_THINK, me->GetOwnerGUID());
            }
            else
            {
                Start(false, true, summoner->GetGUID());
                TalkWithDelay(700, SAY_HI, GetPlayerForEscortGUID());
                TalkWithDelay(3500, SAY_KNOW_THE_WAY, GetPlayerForEscortGUID());
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (part == PART_ESCORT_TO_SATAIN)
                npc_escortAI::UpdateAI(diff);

            if (timer_check <= diff)
            {
                if (part == PART_ESCORT_TO_SATAIN && HasEscortState(STATE_ESCORT_PAUSED))
                {
                    if (IsPlayerInRange())
                        SetEscortPaused(false);
                }
                else if (part == PART_COLLECT_CORPSES)
                {
                    if (!corpse && seat < MAX_CORPSE)
                    {
                        if (corpse = GetNearCorpse())
                        {
                            part = PART_WALK_TO_CORPSE;
                            me->GetMotionMaster()->MovePoint(POINT_PICK_CORPSE, *corpse);
                        }
                    }

                    if (Player* player = ObjectAccessor::GetPlayer(*me, me->GetOwnerGUID()))
                        if (!player->IsActiveQuest(QUEST_RECRUITMENT))
                            if (Vehicle* vehicle = me->GetVehicleKit())
                            {
                                for (uint8 seat = 0; seat < MAX_CORPSE; ++seat)
                                    if (Unit* passenger = vehicle->GetPassenger(seat))
                                        if (Creature* creature = passenger->ToCreature())
                                        {
                                            creature->ExitVehicle();
                                            creature->NearTeleportTo(creature->GetHomePosition());
                                            creature->DespawnOrUnsummon();
                                            creature->SetRespawnDelay(40000);
                                        }

                                me->DespawnOrUnsummon();
                            }
                }

                timer_check = 1000;
            }
            else
                timer_check -= diff;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (part == PART_ESCORT_TO_SATAIN)
                npc_escortAI::MovementInform(type, id);
            else if (type == POINT_MOTION_TYPE && id == POINT_PICK_CORPSE && part == PART_WALK_TO_CORPSE)
            {
                corpse->RemoveAllAuras();
                corpse->CastSpell(corpse, SPELL_STUMPED_OVER, TRIGGERED_FULL_MASK);
                corpse->EnterVehicle(me, seat++);
                corpse = nullptr;
                if (Player* player = ObjectAccessor::GetPlayer(*me, me->GetOwnerGUID()))
                    player->KilledMonsterCredit(NPC_SCARLET_CORPSE);

                FollowPlayer();
                part = PART_COLLECT_CORPSES;
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 6:
                    Talk(SAY_GOOD, GetPlayerForEscortGUID());
                    break;
                case 8:
                    Talk(SAY_HERE_IS_HE, GetPlayerForEscortGUID());
                    part = PART_PENDING;
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(30000);
                    break;
            }

            if (!IsPlayerInRange())
                SetEscortPaused(true);
        }

    private:
        uint8 part;
        uint8 seat;
        uint32 timer_check;
        Creature* corpse;

        bool IsPlayerInRange() const
        {
            Unit* player = me->GetOwner();
            return player && player->GetDistance(me) < 16.f;
        }

        void FollowPlayer()
        {
            if (Unit* player = me->GetOwner())
                me->GetMotionMaster()->MoveFollow(player, 5.f, 220.f);
        }

        Creature* GetNearCorpse()
        {
            class CorpseCheck
            {
            public:
                bool operator()(Creature* creature)
                {
                    return creature->HasAura(SPELL_STUMPED_OVER) || creature->isDead();
                }
            };

            std::list<Creature*> list;
            GetCreatureListWithEntryInGrid(list, me, NPC_SCARLET_CORPSE, 6.f);
            list.remove_if(CorpseCheck());

            return list.empty() ? nullptr : *list.begin();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_darnellAI (creature);
    }
};

void AddSC_tirisfal_glades()
{
    new npc_darnell();
}
