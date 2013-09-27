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

class npc_wounded_deathguard : public CreatureScript
{
public:
    npc_wounded_deathguard() : CreatureScript("npc_wounded_deathguard") { }

    struct npc_wounded_deathguardAI : public ScriptedAI
    {
        npc_wounded_deathguardAI(Creature* creature) : ScriptedAI(creature) {}

        enum Spells
        {
            SPELL_FLASH_HEAL    = 2061
        };

        enum Quests
        {
            QUEST_OF_LIGHT_AND_SHADOWS = 24966
        };

        enum Credits
        {
            QUEST_CREDIT_WOUNDED_DEATHGUARD = 44175
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                switch (spell->Id)
                {
                    case 2061: // Flash Heal
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_OF_LIGHT_AND_SHADOWS) != QUEST_STATUS_COMPLETE)
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WOUNDED_DEATHGUARD);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wounded_deathguardAI (creature);
    }
};

class npc_vile_fin : public CreatureScript
{
public:
    npc_vile_fin() : CreatureScript("npc_vile_fin") { }

    struct npc_vile_finAI : public ScriptedAI
    {
        npc_vile_finAI(Creature* creature) : ScriptedAI(creature) {}
        uint16 checkTimer;

        enum Spells
        {
            SPELL_MURLOC_LEASH    = 73108
        };

        enum Quests
        {
            QUEST_EVER_SO_LONELY = 24966
        };

        enum Credits
        {
            QUEST_CREDIT_VILE_FIN_CAPTURED = 38923,
            QUEST_CREDIT_VILE_FIN_RETURNED = 38887
        };

        void Reset()
        {
            checkTimer = 8000;
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Creature* sedrickCalston = me->FindNearestCreature(38925, 0.5f, true))
                {
                    if (Player* player = me->FindNearestPlayer(5.0f, true))
                    {
                        player->KilledMonsterCredit(QUEST_CREDIT_VILE_FIN_RETURNED);
                        me->AddUnitState(UNIT_STATE_STUNNED);
                        me->DespawnOrUnsummon(6000);
                    }
                    checkTimer = 8000;
                }
            }
            else
                checkTimer -= diff;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (!caster)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                switch (spell->Id)
                {
                    case SPELL_MURLOC_LEASH: // Murloc Leash
                    {
                        // Murloc should be wounded!
                        if (me->GetHealth() == me->GetMaxHealth())
                            return;

                        if (caster->ToPlayer()->GetQuestStatus(QUEST_EVER_SO_LONELY) != QUEST_STATUS_COMPLETE)
                        {
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_VILE_FIN_CAPTURED);
                            me->setFaction(35);
                            me->GetMotionMaster()->MoveFollow(caster, 0.5f, caster->GetOrientation());
                            me->CombatStop(true);
                            me->AttackStop();
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            break;
                        }
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vile_finAI (creature);
    }
};

class npc_sea_cucumber : public CreatureScript
{
public:
    npc_sea_cucumber() : CreatureScript("npc_sea_cucumber") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sea_cucumberAI (creature);
    }

    enum Id
    {
        QUEST_VARIETY_IS_THE_SPICY_OF_DEATH     = 24976,
        SPELL_GATHERING                         = 73123
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->IsActiveQuest(QUEST_VARIETY_IS_THE_SPICY_OF_DEATH))
        {
            player->CastSpell(player, SPELL_GATHERING, false);
            creature->DespawnOrUnsummon(1);
            return true;
        }
        return true;
    }

    struct npc_sea_cucumberAI : public ScriptedAI
    {
        npc_sea_cucumberAI(Creature* creature) : ScriptedAI(creature) {}
    };

};

class npc_vile_fin_tadpole : public CreatureScript
{
public:
    npc_vile_fin_tadpole() : CreatureScript("npc_vile_fin_tadpole") { }

    struct npc_vile_fin_tadpoleAI : public ScriptedAI
    {
        npc_vile_fin_tadpoleAI(Creature* creature) : ScriptedAI(creature) {}
        uint16 checkTimer;

        enum Spells
        {
            SPELL_FRIGHTENED_TADPOLE        = 73133
        };

        enum Quests
        {
            QUEST_PLANT_THE_SEED_OF_FEAR    = 24999
        };

        enum Credits
        {
            QUEST_CREDIT_VILE_FIN_TADPOLE = 38937
        };

        void Reset()
        {
            checkTimer = 2000;
        }

        void UpdateAI(uint32 diff)
        {
            if (UpdateVictim())
                return;

            if (checkTimer <= diff)
            {
                if (Player* player = me->FindNearestPlayer(0.5f, true))
                {
                    if (player->IsActiveQuest(QUEST_PLANT_THE_SEED_OF_FEAR))
                    {
                        player->CastSpell(me, SPELL_FRIGHTENED_TADPOLE, false);
                        me->AddAura(SPELL_FRIGHTENED_TADPOLE, me);
                        if (Aura* aur = me->GetAura(SPELL_FRIGHTENED_TADPOLE))
                        {
                            if (aur->GetStackAmount() > 2)
                            {
                                player->KilledMonsterCredit(QUEST_CREDIT_VILE_FIN_TADPOLE);
                                me->DespawnOrUnsummon(4500);
                            }
                        }
                    }
                }
                checkTimer = 2000;
            }
            else
                checkTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vile_fin_tadpoleAI (creature);
    }
};

class npc_shadow_of_agamand : public CreatureScript
{
public:
    npc_shadow_of_agamand() : CreatureScript("npc_shadow_of_agamand") { }

    struct npc_shadow_of_agamandAI : public ScriptedAI
    {
        npc_shadow_of_agamandAI(Creature* creature) : ScriptedAI(creature) {}
        uint16 checkTimer;

        enum Spells
        {
            SPELL_MIND_FLAY        = 16568
        };

        void Reset()
        {
            if (me->GetReactState() != REACT_AGGRESSIVE)
                me->SetReactState(REACT_AGGRESSIVE);
            checkTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (checkTimer <= diff)
            {
                if (Unit* target = me->SelectNearestPlayer(0.6f))
                    me->CastSpell(target, SPELL_MIND_FLAY, true);
                checkTimer = 3000;
            }
            else
                checkTimer -= diff;
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* malia = me->FindNearestCreature(39117, 0.6f, true))
            {
                malia->AI()->TalkWithDelay(5000, 5);
                malia->DespawnOrUnsummon(8000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadow_of_agamandAI (creature);
    }
};

class npc_veteran_forsaken_trooper : public CreatureScript
{
public:
    npc_veteran_forsaken_trooper() : CreatureScript("npc_veteran_forsaken_trooper") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_veteran_forsaken_trooperAI (creature);
    }

    enum Id
    {
        QUEST_HONOR_THE_DEAD        = 27180,
        ITEM_INSIGNIA               = 60862
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->IsActiveQuest(QUEST_HONOR_THE_DEAD))
        {
            player->AddItem(ITEM_INSIGNIA, 1);
            creature->DespawnOrUnsummon(1);
            return true;
        }
        return true;
    }

    struct npc_veteran_forsaken_trooperAI : public ScriptedAI
    {
        npc_veteran_forsaken_trooperAI(Creature* creature) : ScriptedAI(creature) {}
    };

};

void AddSC_tirisfal_glades()
{
    new npc_darnell();
    new npc_wounded_deathguard();
    new npc_vile_fin();
    new npc_sea_cucumber();
    new npc_vile_fin_tadpole();
    new npc_shadow_of_agamand();
    new npc_veteran_forsaken_trooper();
}
