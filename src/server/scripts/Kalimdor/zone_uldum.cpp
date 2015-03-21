/*
 * Copyright (C) 2013-2014 StarfallCore
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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Pet.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "Vehicle.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "AchievementMgr.h"


/* Automatic rescheduling if creature is already casting */
#define RESCHEDULE_IF_CASTING if (me->HasUnitState(UNIT_STATE_CASTING)) { events.ScheduleEvent(eventId, 1); break; }

// Quest 28250: Thieving Little Pluckers
class spell_uldum_hammer : public SpellScriptLoader
{
    public:
        spell_uldum_hammer() : SpellScriptLoader("spell_uldum_hammer") { }

        class spell_uldum_hammer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_uldum_hammer_SpellScript);

            void HandleDummy1(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitCreature())
                    {
                        if (target->GetEntry() == 48040 && !target->isDead())
                        {
                            float ori = frand(0.0f, M_PI);
                            caster->Kill(target);
                            target->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX()+cos(ori)*10, caster->GetPositionY()+sin(ori)*10, 10.0f, 5.0f);
                            caster->ToPlayer()->KilledMonsterCredit(48105);
                            target->ToCreature()->DespawnOrUnsummon(7000);
                        }
                    }
            }

            void HandleDummy2(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitCreature())
                    {
                        if (target->GetEntry() == 48041 && !target->isDead())
                        {
                            float ori = frand(0.0f, M_PI);
                            caster->Kill(target);
                            target->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX()+cos(ori)*10, caster->GetPositionY()+sin(ori)*10, 10.0f, 5.0f);
                            caster->ToPlayer()->KilledMonsterCredit(48105);
                            target->ToCreature()->DespawnOrUnsummon(7000);
                        }
                    }
            }

            void HandleDummy3(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitCreature())
                    {
                        if (target->GetEntry() == 48043 && !target->isDead())
                        {
                            float ori = frand(0.0f, M_PI);
                            caster->Kill(target);
                            target->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX()+cos(ori)*10, caster->GetPositionY()+sin(ori)*10, 10.0f, 5.0f);
                            caster->ToPlayer()->KilledMonsterCredit(48105);
                            target->ToCreature()->DespawnOrUnsummon(7000);
                        }
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_uldum_hammer_SpellScript::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnEffectHitTarget += SpellEffectFn(spell_uldum_hammer_SpellScript::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
                OnEffectHitTarget += SpellEffectFn(spell_uldum_hammer_SpellScript::HandleDummy3, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_uldum_hammer_SpellScript();
        }
};

class npc_lady_humps_intro_uldum : public CreatureScript
{
public:
    npc_lady_humps_intro_uldum() : CreatureScript("npc_lady_humps_intro_uldum") { }

    enum questId
    {
        QUEST_ENTRY_EASY_MONEY  = 27003
    };

    enum spellId
    {
        // On Preparation
        SPELL_PLAYER_PREP           = 86750,
        SPELL_INIT_ULDUM_INTRO      = 86748,

        // After Preparation
        SPELL_REVERSE_MIRROR_IMAGE  = 86783,
        SPELL_PLAYER_SUMMON_CAMERA  = 95747,
        SPELL_PING_CAMERA_00        = 86815,
        SPELL_COPY_MAINHAND         = 41054,
        SPELL_COPY_OFFHAND          = 45205,

        // Phasing Final Preparation
        PLAYER_PHASE_INTRO          = 298,
        SPELL_CAMERA_BUNNY_2        = 86792,
        SPELL_PING_CAMERA_01        = 86815,
        SPELL_ULDUM_CAMERA_BUNNY_04 = 86822
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_EASY_MONEY) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, SPELL_PLAYER_PREP, true);
            player->CastWithDelay(1500, player, SPELL_INIT_ULDUM_INTRO, true);
            return true;
        }
        return false;
    }
};

class spell_uldum_intro_preparation : public SpellScriptLoader
{
    public:
        spell_uldum_intro_preparation() : SpellScriptLoader("spell_uldum_intro_preparation") { }

        enum spellId
        {
            // On Preparation
            SPELL_PLAYER_UNIQUE_PHASING = 60191,
            SPELL_SUMMON_CLONED_IMAGE   = 86782,
            SPELL_SUMMON_ADARRAH        = 86751,
            SPELL_SUMMON_CARAVAN        = 86752,
            SPELL_SUMMON_ADARRAH_CAMEL  = 86758,
            SPELL_SUMMON_MACK_CAMEL     = 86757,
            SPELL_SUMMON_SAMIR_CAMEL    = 86756,
            SPELL_SUMMON_BUDD_CAMEL     = 86755,
            SPELL_SUMMON_PACK_MULE      = 86754,
            SPELL_SUMMON_LADY_HUMPS     = 86753,
            SPELL_SUMMON_BEAM_BUNNY     = 86942,
            SPELL_SUMMON_CAMERA_BUNNY   = 86792,

            // After Preparation
            SPELL_REVERSE_MIRROR_IMAGE  = 86783,
            SPELL_PLAYER_SUMMON_CAMERA  = 95747,
            SPELL_PING_CAMERA_00        = 86815,
            SPELL_COPY_MAINHAND         = 41054,
            SPELL_COPY_OFFHAND          = 45205,

            // Phasing Final Preparation
            PLAYER_PHASE_INTRO          = 298,
            SPELL_CAMERA_BUNNY_2        = 86792,
            SPELL_PING_CAMERA_01        = 86815,
            SPELL_ULDUM_CAMERA_BUNNY_04 = 86822
        };

        class spell_uldum_intro_preparation_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_uldum_intro_preparation_SpellScript);

            void OnPreparePlayer()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->AddAura(SPELL_PLAYER_UNIQUE_PHASING, caster);
                    caster->SetPhaseMask(298, true);
                    caster->CastSpell(caster, SPELL_SUMMON_CLONED_IMAGE);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_CAMERA_BUNNY, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_ADARRAH, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_CARAVAN, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_ADARRAH_CAMEL, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_MACK_CAMEL, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_SAMIR_CAMEL, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_BUDD_CAMEL, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_PACK_MULE, true);
                    caster->CastWithDelay(1600, caster, SPELL_SUMMON_LADY_HUMPS, true);
                    caster->CastWithDelay(1600, caster, SPELL_PING_CAMERA_00, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_uldum_intro_preparation_SpellScript::OnPreparePlayer);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_uldum_intro_preparation_SpellScript();
        }
};

class npc_uldum_intro_selfmirror : public CreatureScript
{
public:
    npc_uldum_intro_selfmirror() : CreatureScript("npc_uldum_intro_selfmirror") { }

    enum spellId
    {
        SPELL_CAST_MIRROR_IMAGE_AURA    = 86784,
        SPELL_CAST_COPY_MAINHAND        = 41054,
        SPELL_CAST_COPY_OFFHAND         = 45205,
        SPELL_UNIQUE_PHASING            = 60191,
        SPELL_RIDE_CARAVAN              = 63313
    };

    enum eventId
    {
        EVENT_CHANGE_ORIENTATION    = 1,
        EVENT_MOVE_AND_EMOTE,
        EVENT_MOVE_NEAR_CARAVAN_01,
        EVENT_MOVE_NEAR_CARAVAN_02,
        EVENT_CARAVAN_JUMPON
    };

    enum actionId
    {
        ACTION_SET_ORIENTATION  = 1
    };

    enum pointId
    {
        POINT_ADARRAH           = 1,
        POINT_ADARRAH_CAMEL,
        POINT_NEAR_CARAVAN_01,
        POINT_NEAR_CARAVAN_02
    };

    enum npcId
    {
        NPC_ENTRY_PLAYER_CAMERA     = 46557,
        NPC_ENTRY_CARAVAN           = 46596,
        NPC_ENTRY_LADY_HUMPS        = 46536,
        NPC_ENTRY_ADARRAH_CAMEL     = 46546,
        NPC_ENTRY_MACK_CAMEL        = 46543,
        NPC_ENTRY_BUDD_CAMEL        = 46538,
        NPC_ENTRY_PACK_MULE         = 46537,
        NPC_ENTRY_SAMIR_CAMEL       = 46540
    };

    struct npc_uldum_intro_selfmirrorAI : public ScriptedAI
    {
        npc_uldum_intro_selfmirrorAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            owner->CastSpell(me, SPELL_CAST_MIRROR_IMAGE_AURA, true);
            owner->CastSpell(me, SPELL_CAST_COPY_MAINHAND, true);
            owner->CastSpell(me, SPELL_CAST_COPY_OFFHAND, true);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_CHANGE_ORIENTATION, 4000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHANGE_ORIENTATION:
                    {
                        events.CancelEvent(EVENT_CHANGE_ORIENTATION);
                        me->GetMotionMaster()->MovePoint(POINT_ADARRAH, -8926.66f, -2265.75f, 8.87f);
                        events.ScheduleEvent(EVENT_MOVE_AND_EMOTE, 14500);
                        me->SetOrientation(0.35f);
                        break;
                    }
                    case EVENT_MOVE_AND_EMOTE:
                    {
                        events.CancelEvent(EVENT_MOVE_AND_EMOTE);
                        me->GetMotionMaster()->MovePoint(POINT_ADARRAH_CAMEL, -8928.12f, -2268.30f, 8.87f);
                        me->SetOrientation(3.55f);
                        break;
                    }
                    case EVENT_MOVE_NEAR_CARAVAN_01:
                    {
                        me->SetWalk(false);
                        events.CancelEvent(EVENT_MOVE_NEAR_CARAVAN_01);
                        me->GetMotionMaster()->MovePoint(POINT_NEAR_CARAVAN_01, -8919.12f, -2272.86f, 8.88f);
                        break;
                    }
                    case EVENT_MOVE_NEAR_CARAVAN_02:
                    {
                        events.CancelEvent(EVENT_MOVE_NEAR_CARAVAN_02);
                        me->GetMotionMaster()->MovePoint(POINT_NEAR_CARAVAN_02, -8922.04f, -2286.32f, 8.90f);
                        if (Creature* buddCamel = me->FindNearestCreature(NPC_ENTRY_BUDD_CAMEL, 100.0f, true))
                            buddCamel->AI()->DoAction(1);
                        break;
                    }
                    case EVENT_CARAVAN_JUMPON:
                    {
                        events.CancelEvent(EVENT_CARAVAN_JUMPON);
                        if (Creature* caravan = me->FindNearestCreature(NPC_ENTRY_CARAVAN, 100.0f, true))
                            me->CastSpell(caravan, SPELL_RIDE_CARAVAN);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_ADARRAH_CAMEL:
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                    if (Creature* playerCamera = me->FindNearestCreature(NPC_ENTRY_PLAYER_CAMERA, 100.0f, true))
                        playerCamera->AI()->DoAction(1);
                    events.ScheduleEvent(EVENT_MOVE_NEAR_CARAVAN_01, 3500);
                    break;
                }
                case POINT_NEAR_CARAVAN_01:
                {
                    if (Creature* ladyHumps = me->FindNearestCreature(NPC_ENTRY_LADY_HUMPS, 100.0f, true))
                        ladyHumps->AI()->DoAction(1);
                    if (Creature* uldumCaravan = me->FindNearestCreature(NPC_ENTRY_CARAVAN, 100.0f, true))
                        uldumCaravan->AI()->DoAction(1);
                    if (Creature* adarrahCamel = me->FindNearestCreature(NPC_ENTRY_ADARRAH_CAMEL, 100.0f, true))
                        adarrahCamel->AI()->DoAction(1);
                    if (Creature* mackCamel = me->FindNearestCreature(NPC_ENTRY_MACK_CAMEL, 100.0f, true))
                        mackCamel->AI()->DoAction(1);
                    if (Creature* packMule = me->FindNearestCreature(NPC_ENTRY_PACK_MULE, 100.0f, true))
                        packMule->AI()->DoAction(1);
                    if (Creature* samirCamel = me->FindNearestCreature(NPC_ENTRY_SAMIR_CAMEL, 100.0f, true))
                        samirCamel->AI()->DoAction(1);
                    events.ScheduleEvent(EVENT_MOVE_NEAR_CARAVAN_02, 4000);
                    break;
                }
                case POINT_NEAR_CARAVAN_02:
                {
                    if (Creature* playerCamera = me->FindNearestCreature(NPC_ENTRY_PLAYER_CAMERA, 100.0f, true))
                        playerCamera->AI()->DoAction(2);
                    me->GetMotionMaster()->MovementExpired(false);
                    if (Creature* uldumCaravan = me->FindNearestCreature(NPC_ENTRY_CARAVAN, 100.0f, true))
                        me->GetMotionMaster()->MoveJump(uldumCaravan->GetPositionX(), uldumCaravan->GetPositionY(), uldumCaravan->GetPositionZ(), 10.0f, 10.0f);
                    events.ScheduleEvent(EVENT_CARAVAN_JUMPON, 2000);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_uldum_intro_selfmirrorAI(creature);
    }
};

class npc_uldum_intro_camera01 : public CreatureScript
{
public:
    npc_uldum_intro_camera01() : CreatureScript("npc_uldum_intro_camera01") { }

    enum spellId
    {
        SPELL_RIDE_CAMERA           = 46598,
        SPELL_SWITCH_SEAT_2         = 63313,
        SPELL_FADE_TO_BLACK         = 89404,
        SPELL_SUMMON_SKARF          = 87012
    };

    enum actionId
    {
        ACTION_FOCUS_IMAGE  = 1,
        ACTION_MOVE_TO
    };

    enum pointId
    {
        POINT_TAKE_Z            = 1,
        POINT_BEHIND_CARAVAN,
        POINT_REMOVE_Z,
        POINT_MIDDLE,
        POINT_RIDGE,
        POINT_AMBUSHER
    };

    enum eventId
    {
        EVENT_BEHIND_CARAVAN    = 1,
        EVENT_SWITCH_SEAT,
        EVENT_FADE_TO_BLACK,
        EVENT_UPPER_VISUAL,
        EVENT_RETURN_SEAT,
        EVENT_SEAT_UNDER_ATTACK,
        EVENT_AMBUSHER_CAMERA,
        EVENT_TELEPORT_CAMERA,
        EVENT_REMOVE_PASSENGERS,
        EVENT_CHECK_OWNER
    };

    enum npcId
    {
        NPC_ENTRY_MIRROR_IMAGE      = 46554,
        NPC_ENTRY_ULDUM_CARAVAN     = 46596,
        NPC_ENTRY_PLAYER_CAMERA     = 46557,
        NPC_ENTRY_CARAVAN           = 46596,
        NPC_ENTRY_LADY_HUMPS        = 46536,
        NPC_ENTRY_ADARRAH_CAMEL     = 46546,
        NPC_ENTRY_MACK_CAMEL        = 46543,
        NPC_ENTRY_BUDD_CAMEL        = 46538,
        NPC_ENTRY_PACK_MULE         = 46537,
        NPC_ENTRY_SAMIR_CAMEL       = 46540,
        NPC_ENTRY_SULTAN_OOGAH      = 46680,
        NPC_ENTRY_AMBUSHERS         = 46720
    };

    struct npc_uldum_intro_camera01AI : public ScriptedAI
    {
        npc_uldum_intro_camera01AI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(60191, me);
            me->AddUnitState(UNIT_STATE_ROTATING);
            me->SetFacingToObject(owner);
            owner->EnterVehicle(me, 0);
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FOCUS_IMAGE:
                {
                    me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+6.0f, 3.0f, 3.0f, POINT_TAKE_Z);
                    break;
                }
                case ACTION_MOVE_TO:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MoveJump(-8926.18f, -1747.56f, 80.56f, 5.0f, 20.0f, POINT_MIDDLE);
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
                    case EVENT_CHECK_OWNER:
                    {
                        Unit* owner = me->GetCharmerOrOwner();
                        if (!owner)
                        {
                            events.Reset();
                            me->DespawnOrUnsummon(1);
                        }
                        events.RescheduleEvent(EVENT_CHECK_OWNER, 1000);
                        break;
                    }
                    case EVENT_BEHIND_CARAVAN:
                    {
                        events.CancelEvent(EVENT_BEHIND_CARAVAN);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()-6.0f, 4.0f, 4.0f, POINT_REMOVE_Z);
                        events.ScheduleEvent(EVENT_UPPER_VISUAL, 13000);
                        events.ScheduleEvent(EVENT_FADE_TO_BLACK, 16000);
                        events.ScheduleEvent(EVENT_SWITCH_SEAT, 18000);
                        events.ScheduleEvent(EVENT_RETURN_SEAT, 25000);
                        break;
                    }
                    case EVENT_UPPER_VISUAL:
                    {
                        events.CancelEvent(EVENT_UPPER_VISUAL);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Vehicle* veh = me->GetVehicleKit())
                            {
                                Unit* passenger = veh->GetPassenger(0);
                                if (passenger && passenger != NULL && passenger->IsInWorld())
                                    passenger->ChangeSeat(2, true);
                            }
                        }
                        break;
                    }
                    case EVENT_SWITCH_SEAT:
                    {
                        events.CancelEvent(EVENT_SWITCH_SEAT);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Vehicle* veh = me->GetVehicleKit())
                            {
                                Unit* passenger = veh->GetPassenger(2);
                                if (passenger && passenger != NULL && passenger->IsInWorld())
                                    passenger->ChangeSeat(1, true);
                            }
                        }
                        me->NearTeleportTo(-8937.54f,-1725.59f, 125.31f, 2.09f);
                        break;
                    }
                    case EVENT_FADE_TO_BLACK:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld() && playerOwner->IsInWorld())
                            playerOwner->CastSpell(playerOwner, SPELL_FADE_TO_BLACK, true);

                        if (Creature* ladyHumps = me->FindNearestCreature(NPC_ENTRY_LADY_HUMPS, 100.0f, true))
                            ladyHumps->AI()->DoAction(2);
                        if (Creature* uldumCaravan = me->FindNearestCreature(NPC_ENTRY_CARAVAN, 100.0f, true))
                            uldumCaravan->AI()->DoAction(2);
                        if (Creature* adarrahCamel = me->FindNearestCreature(NPC_ENTRY_ADARRAH_CAMEL, 100.0f, true))
                            adarrahCamel->AI()->DoAction(2);
                        if (Creature* mackCamel = me->FindNearestCreature(NPC_ENTRY_MACK_CAMEL, 100.0f, true))
                            mackCamel->AI()->DoAction(2);
                        if (Creature* packMule = me->FindNearestCreature(NPC_ENTRY_PACK_MULE, 100.0f, true))
                            packMule->AI()->DoAction(2);
                        if (Creature* samirCamel = me->FindNearestCreature(NPC_ENTRY_SAMIR_CAMEL, 100.0f, true))
                            samirCamel->AI()->DoAction(2);
                        if (Creature* buddCamel = me->FindNearestCreature(NPC_ENTRY_BUDD_CAMEL, 100.0f, true))
                            buddCamel->AI()->DoAction(2);
                        break;
                    }
                    case EVENT_RETURN_SEAT:
                    {
                        events.CancelEvent(EVENT_RETURN_SEAT);
                        events.ScheduleEvent(EVENT_SEAT_UNDER_ATTACK, 6000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Vehicle* veh = me->GetVehicleKit())
                            {
                                Unit* passenger = veh->GetPassenger(1);
                                if (passenger && passenger != NULL && passenger->IsInWorld())
                                    passenger->ChangeSeat(0, true);
                            }
                        }
                        break;
                    }
                    case EVENT_SEAT_UNDER_ATTACK:
                    {
                        events.CancelEvent(EVENT_SEAT_UNDER_ATTACK);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8992.04f, -1663.47f, 108.99f, 25.0f, 25.0f, POINT_RIDGE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Vehicle* veh = me->GetVehicleKit())
                            {
                                Unit* passenger = veh->GetPassenger(0);
                                if (passenger && passenger != NULL && passenger->IsInWorld())
                                    passenger->ChangeSeat(2, true);
                            }
                        }
                        events.ScheduleEvent(EVENT_AMBUSHER_CAMERA, 6000);
                        break;
                    }
                    case EVENT_AMBUSHER_CAMERA:
                    {
                        events.CancelEvent(EVENT_AMBUSHER_CAMERA);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8950.93f, -1646.22f, 98.93f, 30.0f, 30.0f, POINT_AMBUSHER);
                        events.ScheduleEvent(EVENT_TELEPORT_CAMERA, 10000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->CastWithDelay(8000, playerOwner, SPELL_FADE_TO_BLACK, true);
                        break;
                    }
                    case EVENT_TELEPORT_CAMERA:
                    {
                        events.CancelEvent(EVENT_TELEPORT_CAMERA);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->AddAura(49416, playerOwner);
                            playerOwner->SummonCreature(NPC_ENTRY_AMBUSHERS, -11004.76f, -1273.58f, 13.81f, 5.07f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_AMBUSHERS, -11009.67f, -1275.45f, 13.90f, 5.07f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        events.ScheduleEvent(EVENT_REMOVE_PASSENGERS, 1000);
                        break;
                    }
                    case EVENT_REMOVE_PASSENGERS:
                    {
                        events.CancelEvent(EVENT_REMOVE_PASSENGERS);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Vehicle* vehicle = me->GetVehicleKit())
                                vehicle->RemoveAllPassengers();
                        }
                        if (Creature* ambushers = me->FindNearestCreature(NPC_ENTRY_AMBUSHERS, 200.0f, true))
                            ambushers->AI()->TalkWithDelay(2000, 1);
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TAKE_Z:
                {
                    me->GetMotionMaster()->MoveJump(-8930.42f, -2307.52f, me->GetPositionZ()+2.0f, 35.0f, 35.0f, POINT_BEHIND_CARAVAN);
                    break;
                }
                case POINT_BEHIND_CARAVAN:
                {
                    me->SetFacingTo(1.33f);
                    events.ScheduleEvent(EVENT_BEHIND_CARAVAN, 3000);
                    break;
                }
                case POINT_AMBUSHER:
                {
                    me->SetFacingTo(4.30f);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_uldum_intro_camera01AI(creature);
    }
};

class npc_adarrah_uldum_intro : public CreatureScript
{
public:
    npc_adarrah_uldum_intro() : CreatureScript("npc_adarrah_uldum_intro") { }

    enum npcId
    {
        NPC_ADARRAH_CAMEL   = 46546
    };

    enum eventId
    {
        EVENT_START_TALK    = 1,
        EVENT_MOVE_TO_CAMEL
    };

    enum pointId
    {
        POINT_TO_PLAYER = 1,
        POINT_TO_CAMEL
    };

    struct npc_adarrah_uldum_introAI : public ScriptedAI
    {
        npc_adarrah_uldum_introAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(60191, me);
            events.ScheduleEvent(EVENT_START_TALK, 2000);
        };

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_TALK:
                    {
                        events.CancelEvent(EVENT_START_TALK);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            Talk(0, playerOwner->GetGUID());
                            me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                            TalkWithDelay(7000, 1, playerOwner->GetGUID());
                            playerOwner->SetOrientation(0.33f);
                            me->GetMotionMaster()->MovePoint(POINT_TO_PLAYER, -8923.89f, -2264.23f, 8.87f);
                            events.ScheduleEvent(EVENT_MOVE_TO_CAMEL, 14000);
                        }
                        break;
                    }
                    case EVENT_MOVE_TO_CAMEL:
                    {
                        me->GetMotionMaster()->MovePoint(POINT_TO_CAMEL, -8937.79f, -2274.36f, 8.88f);
                        events.CancelEvent(EVENT_MOVE_TO_CAMEL);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_PLAYER:
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                    break;
                }
                case POINT_TO_CAMEL:
                {
                    if (Creature* adarrahCamel = me->FindNearestCreature(NPC_ADARRAH_CAMEL, 50.0f))
                        me->EnterVehicle(adarrahCamel, 0);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_adarrah_uldum_introAI(creature);
    }
};

class npc_uldum_caravan_intro : public CreatureScript
{
public:
    npc_uldum_caravan_intro() : CreatureScript("npc_uldum_caravan_intro") { }

    struct npc_uldum_caravan_introAI : public npc_escortAI
    {
        npc_uldum_caravan_introAI(Creature* creature) : npc_escortAI(creature) { }

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_uldum_caravan_introAI(creature);
    }
};

class npc_lady_humps_intro_escort : public CreatureScript
{
public:
    npc_lady_humps_intro_escort() : CreatureScript("npc_lady_humps_intro_escort") { }

    struct npc_lady_humps_intro_escortAI : public npc_escortAI
    {
        npc_lady_humps_intro_escortAI(Creature* creature) : npc_escortAI(creature) { }

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lady_humps_intro_escortAI(creature);
    }
};

class npc_adarrah_camel_intro_escort : public CreatureScript
{
public:
    npc_adarrah_camel_intro_escort() : CreatureScript("npc_adarrah_camel_intro_escort") { }

    struct npc_adarrah_camel_intro_escortAI : public npc_escortAI
    {
        npc_adarrah_camel_intro_escortAI(Creature* creature) : npc_escortAI(creature) { }

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_adarrah_camel_intro_escortAI(creature);
    }
};

class npc_pack_mule_intro_escort : public CreatureScript
{
public:
    npc_pack_mule_intro_escort() : CreatureScript("npc_pack_mule_intro_escort") { }

    struct npc_pack_mule_intro_escortAI : public npc_escortAI
    {
        npc_pack_mule_intro_escortAI(Creature* creature) : npc_escortAI(creature) { }

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pack_mule_intro_escortAI(creature);
    }
};

class npc_budd_camel_intro_escort : public CreatureScript
{
public:
    npc_budd_camel_intro_escort() : CreatureScript("npc_budd_camel_intro_escort") { }

    struct npc_budd_camel_intro_escortAI : public npc_escortAI
    {
        npc_budd_camel_intro_escortAI(Creature* creature) : npc_escortAI(creature) { }

        EventMap events;

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        enum npcId
        {
            NPC_ENTRY_BUDD  = 46520
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    if (Creature* budd = me->FindNearestCreature(NPC_ENTRY_BUDD, 5.0f, true))
                        budd->AI()->TalkWithDelay(2000, 0);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_budd_camel_intro_escortAI(creature);
    }
};

class npc_samir_camel_intro_escort : public CreatureScript
{
public:
    npc_samir_camel_intro_escort() : CreatureScript("npc_samir_camel_intro_escort") { }

    struct npc_samir_camel_intro_escortAI : public npc_escortAI
    {
        npc_samir_camel_intro_escortAI(Creature* creature) : npc_escortAI(creature) { }

        EventMap events;

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        enum spellId
        {
            SPELL_TELEPORT_SAMIR_CAMEL  = 87001
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_samir_camel_intro_escortAI(creature);
    }
};

class npc_mack_camel_intro_escort : public CreatureScript
{
public:
    npc_mack_camel_intro_escort() : CreatureScript("npc_mack_camel_intro_escort") { }

    struct npc_mack_camel_intro_escortAI : public npc_escortAI
    {
        npc_mack_camel_intro_escortAI(Creature* creature) : npc_escortAI(creature) { }

        enum actionId
        {
            ACTION_START_WP = 1,
            ACTION_SPEEDUP
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    SetMaxPlayerDistance(1000);
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(false);
                    break;
                }
                case ACTION_SPEEDUP:
                {
                    SetEscortPaused(true);
                    me->DespawnOrUnsummon(1);
                    break;
                }
                default:
                    break;
            }
        }

        void WaypointReached(uint32 point) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mack_camel_intro_escortAI(creature);
    }
};

class npc_skarf_and_oogah_intro : public CreatureScript
{
public:
    npc_skarf_and_oogah_intro() : CreatureScript("npc_skarf_and_oogah_intro") { }

    struct npc_skarf_and_oogah_introAI : public ScriptedAI
    {
        npc_skarf_and_oogah_introAI(Creature* creature) : ScriptedAI(creature) { }

        enum actionId
        {
            ACTION_JUMP_ON_RIDGE    = 1,
        };

        enum pointId
        {
            POINT_RIDGE         = 1,
            POINT_EXPEDITION,
        };

        enum npcId
        {
            NPC_ENTRY_SULTAN_OOGAH  = 46680,
            NPC_ENTRY_AMBUSHER      = 46720
        };

        void OnCharmed(bool apply) {}

        class toExpedition : public BasicEvent
        {
            public:
                explicit toExpedition(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->GetMotionMaster()->MovementExpired(false);
                creature->GetMotionMaster()->MoveJump(-8980.70f, -1675.42f, 94.45f, 25.0f, 25.0f, POINT_EXPEDITION);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
            DoAction(ACTION_JUMP_ON_RIDGE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_JUMP_ON_RIDGE:
                {
                    me->GetMotionMaster()->MoveJump(-9006.83f, -1652.53f, 107.51f, 25.0f, 25.0f, POINT_RIDGE);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_RIDGE:
                {
                    if (Creature* sultanOogah = me->FindNearestCreature(NPC_ENTRY_SULTAN_OOGAH, 10.0f, true))
                        sultanOogah->AI()->TalkWithDelay(2000, 0);
                    me->m_Events.AddEvent(new toExpedition(me), (me)->m_Events.CalculateTime(4000));
                    break;
                }
                case POINT_EXPEDITION:
                {
                    if (Creature* pigmyAmbusher = me->FindNearestCreature(NPC_ENTRY_AMBUSHER, 50.0f, true))
                        pigmyAmbusher->AI()->TalkWithDelay(3000, 0);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_skarf_and_oogah_introAI(creature);
    }
};

class spell_adarrah_breakout_cage : public SpellScriptLoader
{
    public:
        spell_adarrah_breakout_cage() : SpellScriptLoader("spell_adarrah_breakout_cage") { }

        enum spellId
        {
            SPELL_PLAYER_UNIQUE_PHASING     = 60191,
            SPELL_SUMMON_ADARRAH_BREAKOUT   = 89327
        };

        class spell_adarrah_breakout_cage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_adarrah_breakout_cage_SpellScript);

            void OnPreparePlayer()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->AddAura(SPELL_PLAYER_UNIQUE_PHASING, caster);
                    caster->CastSpell(caster, SPELL_SUMMON_ADARRAH_BREAKOUT, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_adarrah_breakout_cage_SpellScript::OnPreparePlayer);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_adarrah_breakout_cage_SpellScript();
        }
};

class npc_adarrah_breakout : public CreatureScript
{
public:
    npc_adarrah_breakout() : CreatureScript("npc_adarrah_breakout") { }

    struct npc_adarrah_breakoutAI : public ScriptedAI
    {
        npc_adarrah_breakoutAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_EVENT  = 1,
            ACTION_CALL_JAILOR,
            ACTION_FINAL_TALK
        };

        enum pointId
        {
            POINT_OUT_OF_CAGE   = 1
        };

        enum npcId
        {
            NPC_ENTRY_NEFERSET_JAILOR   = 48011
        };

        enum goId
        {
            GO_ENTRY_CAGE   = 206953,
            CAGE_GUID       = 77544
        };

        enum eventId
        {
            EVENT_EVADE_FROM_CAGE   = 1
        };

        class openCage : public BasicEvent
        {
            public:
                explicit openCage(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (GameObject* cage = creature->FindNearestGameObject(GO_ENTRY_CAGE, 50.0f))
                {
                    if (cage->GetGUIDLow() == CAGE_GUID)
                        cage->SetGoState(GO_STATE_ACTIVE);
                }
                return true;
            }

        private:
            Creature* creature;
        };

        class callJailor : public BasicEvent
        {
            public:
                explicit callJailor(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->AI()->DoAction(ACTION_CALL_JAILOR);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(60191, me);
            DoAction(ACTION_START_EVENT);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_EVENT:
                {
                    me->SetFacingTo(4.63f);
                    me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        TalkWithDelay(1000, 0, playerOwner->GetGUID());
                    me->m_Events.AddEvent(new openCage(me), (me)->m_Events.CalculateTime(7500));
                    events.ScheduleEvent(EVENT_EVADE_FROM_CAGE, 8500);
                    break;
                }
                case ACTION_CALL_JAILOR:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_JAILOR, -11032.55f, -1268.66f, 13.24f, 0.23f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    break;
                }
                case ACTION_FINAL_TALK:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        TalkWithDelay(500, 3, playerOwner->GetGUID());
                        TalkWithDelay(7500, 4, playerOwner->GetGUID());
                        playerOwner->RemoveAurasDueToSpell(60191);
                        playerOwner->SetPhaseMask(1, true);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_OUT_OF_CAGE:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        Talk(1, playerOwner->GetGUID());
                        TalkWithDelay(6000, 2, playerOwner->GetGUID());
                        me->m_Events.AddEvent(new callJailor(me), (me)->m_Events.CalculateTime(10000));
                        me->SetFacingTo(3.44f);
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
                    case EVENT_EVADE_FROM_CAGE:
                    {
                        events.CancelEvent(EVENT_EVADE_FROM_CAGE);
                        me->HandleEmoteCommand(EMOTE_STAND_STATE_NONE);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_OUT_OF_CAGE, -10993.44f, -1261.84f, 13.24f, true);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->SetControlled(false, UNIT_STATE_ROOT);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_adarrah_breakoutAI(creature);
    }
};

class npc_neferset_jailor_breakout : public CreatureScript
{
public:
    npc_neferset_jailor_breakout() : CreatureScript("npc_neferset_jailor_breakout") { }

    enum npcId
    {
        NPC_ENTRY_ADARRAH_BREAKOUT  = 48030
    };

    struct npc_neferset_jailor_breakoutAI : public ScriptedAI
    {
        npc_neferset_jailor_breakoutAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(60191, me);
            AttackStart(owner);
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* adarrah = me->FindNearestCreature(NPC_ENTRY_ADARRAH_BREAKOUT, 100.0f, true))
                adarrah->AI()->DoAction(3);
        };

        void UpdateAI(uint32 diff)
        {
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_neferset_jailor_breakoutAI(creature);
    }
};

class go_plant_trap_traitors : public GameObjectScript
{
public:
    go_plant_trap_traitors() : GameObjectScript("go_plant_trap_traitors") { }

    enum questId
    {
        QUEST_ENTRY_TRAITORS    = 27922
    };

    enum spellId
    {
        SPELL_PLAYER_UNIQUE_PHASING     = 60191,
        SPELL_START_CINEMATIC           = 88525,
        SPELL_SUMMON_HIGH_PROPHET       = 88489,
        SPELL_SUMMON_TRAITOR_01         = 88523,
        SPELL_SUMMON_TRAITOR_02         = 88487,
        SPELL_SUMMON_TRAITOR_03         = 88488
    };

    enum npcId
    {
        NPC_ENTRY_NEFERSET_GUARD    = 48263,
        NPC_ENTRY_SIAMAT            = 47285
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_TRAITORS) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(SPELL_PLAYER_UNIQUE_PHASING, player);
            player->SetPhaseMask(2, true);
            player->CastSpell(player, SPELL_SUMMON_HIGH_PROPHET, true);
            player->CastSpell(player, SPELL_SUMMON_TRAITOR_01, true);
            player->CastSpell(player, SPELL_SUMMON_TRAITOR_02, true);
            player->CastSpell(player, SPELL_SUMMON_TRAITOR_03, true);
            player->CastWithDelay(500, player, SPELL_START_CINEMATIC, true);
            return true;
        }
        return true;
    }
};

class npc_siamat_traitors : public CreatureScript
{
public:
    npc_siamat_traitors() : CreatureScript("npc_siamat_traitors") { }

    struct npc_siamat_traitorsAI : public ScriptedAI
    {
        npc_siamat_traitorsAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_EVENT  = 1
        };

        enum npcId
        {
            NPC_ENTRY_RAMKAHEN_TRAITOR_01   = 47449,
            NPC_ENTRY_RAMKAHEN_TRAITOR_02   = 47450,
            NPC_ENTRY_RAMKAHEN_TRAITOR_03   = 47478,
            NPC_ENTRY_CAMERA                = 47473
        };

        enum eventId
        {
            EVENT_CAST_DUMMY     = 1,
            EVENT_QUEST_COMPLETE
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            DoAction(ACTION_START_EVENT);
        }

        enum spellId
        {
            SPELL_UNIQUE_PHASING            = 60191
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_EVENT:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        TalkWithDelay(3000, 0, playerOwner->GetGUID());
                        events.ScheduleEvent(EVENT_CAST_DUMMY, 10000);
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 30000);
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
                    case EVENT_CAST_DUMMY:
                    {
                        events.CancelEvent(EVENT_CAST_DUMMY);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                        if (Creature* traitor01 = me->FindNearestCreature(NPC_ENTRY_RAMKAHEN_TRAITOR_01, 50.0f, true))
                            traitor01->AI()->DoAction(1);
                        if (Creature* traitor02 = me->FindNearestCreature(NPC_ENTRY_RAMKAHEN_TRAITOR_02, 50.0f, true))
                            traitor02->AI()->DoAction(1);
                        if (Creature* traitor03 = me->FindNearestCreature(NPC_ENTRY_RAMKAHEN_TRAITOR_03, 50.0f, true))
                            traitor03->AI()->DoAction(1);

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            TalkWithDelay(5000, 1, playerOwner->GetGUID());

                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 12000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld() && playerOwner->GetTypeId() == TYPEID_PLAYER)
                        {
                            playerOwner->ToPlayer()->KilledMonsterCredit(47466);
                            if (Vehicle* playerCamera = playerOwner->GetVehicle())
                            {
                                playerCamera->RemoveAllPassengers();
                                if (playerCamera->GetBase()->ToCreature())
                                    playerCamera->GetBase()->ToCreature()->DespawnOrUnsummon(1000);
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_siamat_traitorsAI(creature);
    }
};

class npc_ramkahen_traitors : public CreatureScript
{
public:
    npc_ramkahen_traitors() : CreatureScript("npc_ramkahen_traitors") { }

    struct npc_ramkahen_traitorsAI : public ScriptedAI
    {
        npc_ramkahen_traitorsAI(Creature* creature) : ScriptedAI(creature) {}

        enum actionId
        {
            ACTION_CAST_CHANNELING  = 1
        };

        enum npcId
        {
            NPC_ENTRY_HIGH_PROPHET   = 47451
        };

        enum eventId
        {
            EVENT_CAST_DUMMY    = 1
        };

        enum spellId
        {
            SPELL_DUMMY_CHANNEL_TRAITORS    = 88561,
            SPELL_UNIQUE_PHASING            = 60191
        };

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CAST_CHANNELING:
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                    if (Creature* highProphet = me->FindNearestCreature(NPC_ENTRY_HIGH_PROPHET, 50.0f, true))
                        DoCast(highProphet, SPELL_DUMMY_CHANNEL_TRAITORS);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ramkahen_traitorsAI(creature);
    }
};

class npc_prince_nadun_escape : public CreatureScript
{
public:
    npc_prince_nadun_escape() : CreatureScript("npc_prince_nadun_escape") { }

    enum questId
    {
        QUEST_ENTRY_ESCAPE_FROM_THE_LOST_CITY   = 28112
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_SUMMON_CAMERA     = 89074,
        SPELL_INVISIB_DETECT_2  = 49417,
        SPELL_SUMMON_ADARRAH    = 89101,
        SPELL_SUMMON_NADUN      = 89077
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_ESCAPE_FROM_THE_LOST_CITY)
        {
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->RemoveAurasDueToSpell(SPELL_INVISIB_DETECT_2);
            player->CastWithDelay(500, player, SPELL_SUMMON_CAMERA, true);
            player->CastWithDelay(500, player, SPELL_SUMMON_NADUN, true);
            player->CastWithDelay(500, player, SPELL_SUMMON_ADARRAH, true);
            return false;
        }
        return true;
    }
};

class npc_adarrah_mantaur : public CreatureScript
{
public:
   npc_adarrah_mantaur() : CreatureScript("npc_adarrah_mantaur") { }

    struct npc_adarrah_mantaurAI : public ScriptedAI
    {
        npc_adarrah_mantaurAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_WALK    = 1,
            ACTION_ADVANCE
        };

        enum pointId
        {
            POINT_BEHIND_NADUN  = 1,
            POINT_TO_EVASION
        };

        enum npcId
        {
            NPC_ENTRY_LOST_CITY_CAMERA  = 47873,
            NPC_ENTRY_MANTAUR_SAMIR     = 47112,
            NPC_ENTRY_MANTAUR_TANZAR    = 47098,
            NPC_ENTRY_HARKOR            = 46879,
            NPC_ENTRY_MACK              = 46878,
            NPC_ENTRY_BUDD              = 46875,
            NPC_ENTRY_PRINCE_NADUN      = 47896
        };

        enum eventId
        {
            EVENT_INFORM_CAMERA_FACING      = 1,
            EVENT_ADJUST_FACING,
            EVENT_INFORM_CAMERA_TO_EVADE,
            EVENT_TALK_FINAL,
            EVENT_INFORM_NADUN
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_SUMMON_SAMIR      = 89075,
            SPELL_SUMMON_TANZAR     = 89076,
            SPELL_SAMIR_VISUAL      = 88069,
            SPELL_BUDD_VISUAL       = 88070,
            SPELL_MACK_VISUAL       = 88062,
            SPELL_TANZAR_VISUAL     = 88059
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(true);
            DoAction(ACTION_START_WALK);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WALK:
                {
                    events.ScheduleEvent(EVENT_INFORM_CAMERA_FACING, 3000);
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MovePoint(POINT_BEHIND_NADUN, -11000.68f, -1247.46f, 13.24f);
                    break;
                }
                case ACTION_ADVANCE:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MovePoint(POINT_TO_EVASION, -11002.87f, -1262.67f, 13.24f);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        playerOwner->CastSpell(playerOwner, SPELL_SUMMON_SAMIR, true);
                        playerOwner->CastSpell(playerOwner, SPELL_SUMMON_TANZAR, true);
                    }
                    events.ScheduleEvent(EVENT_INFORM_CAMERA_TO_EVADE, 5000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_BEHIND_NADUN:
                {
                    events.ScheduleEvent(EVENT_ADJUST_FACING, 2000);
                    break;
                }
                case POINT_TO_EVASION:
                {
                    if (Creature* mantaurSamir = me->FindNearestCreature(NPC_ENTRY_MANTAUR_SAMIR, 100.0f, true))
                    {
                        me->HandleEmoteCommand(EMOTE_STATE_STEALTH_STAND);
                        me->EnterVehicle(mantaurSamir, 1);
                        mantaurSamir->AddAura(SPELL_SAMIR_VISUAL, mantaurSamir);
                        mantaurSamir->HandleEmoteCommand(EMOTE_STATE_STEALTH_STAND);
                        events.ScheduleEvent(EVENT_TALK_FINAL, 2500);
                    }
                    if (Creature* mantaurTanzar = me->FindNearestCreature(NPC_ENTRY_MANTAUR_TANZAR, 100.0f, true))
                    {
                        mantaurTanzar->AddAura(SPELL_SAMIR_VISUAL, mantaurTanzar);
                        mantaurTanzar->HandleEmoteCommand(EMOTE_STATE_STEALTH_STAND);
                    }
                    if (Creature* harkor = me->FindNearestCreature(NPC_ENTRY_HARKOR, 100.0f, true))
                        harkor->HandleEmoteCommand(EMOTE_STATE_STEALTH_STAND);
                    if (Creature* mack = me->FindNearestCreature(NPC_ENTRY_MACK, 100.0f, true))
                        mack->AddAura(SPELL_MACK_VISUAL, mack);
                    if (Creature* budd = me->FindNearestCreature(NPC_ENTRY_BUDD, 100.0f, true))
                        budd->AddAura(SPELL_BUDD_VISUAL, budd);
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
                    case EVENT_INFORM_CAMERA_FACING:
                    {
                        events.CancelEvent(EVENT_INFORM_CAMERA_FACING);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Creature* camera = playerOwner->FindNearestCreature(NPC_ENTRY_LOST_CITY_CAMERA, 100.0f, true))
                                camera->AI()->DoAction(1);
                        }
                        break;
                    }
                    case EVENT_ADJUST_FACING:
                    {
                        events.CancelEvent(EVENT_ADJUST_FACING);
                        me->SetFacingTo(4.45f);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            TalkWithDelay(2000, 0, playerOwner->GetGUID());
                            TalkWithDelay(8000, 1, playerOwner->GetGUID());
                            TalkWithDelay(16000, 2, playerOwner->GetGUID());
                        }
                        break;
                    }
                    case EVENT_INFORM_CAMERA_TO_EVADE:
                    {
                        events.CancelEvent(EVENT_INFORM_CAMERA_TO_EVADE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Creature* camera = playerOwner->FindNearestCreature(NPC_ENTRY_LOST_CITY_CAMERA, 100.0f, true))
                                camera->AI()->DoAction(2);
                        }
                        break;
                    }
                    case EVENT_TALK_FINAL:
                    {
                        events.CancelEvent(EVENT_TALK_FINAL);
                        if (Creature* budd = me->FindNearestCreature(NPC_ENTRY_BUDD, 100.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            {
                                budd->AI()->Talk(0, playerOwner->GetGUID());
                                TalkWithDelay(4000, 3, playerOwner->GetGUID());
                            }
                        }
                        events.ScheduleEvent(EVENT_INFORM_NADUN, 3000);
                        break;
                    }
                    case EVENT_INFORM_NADUN:
                    {
                        events.CancelEvent(EVENT_INFORM_NADUN);
                        if (Creature* princeNadun = me->FindNearestCreature(NPC_ENTRY_PRINCE_NADUN, 100.0f, true))
                            princeNadun->AI()->DoAction(1);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_adarrah_mantaurAI(creature);
    }
};

class npc_prince_nadun_mantaur : public CreatureScript
{
public:
   npc_prince_nadun_mantaur() : CreatureScript("npc_prince_nadun_mantaur") { }

    struct npc_prince_nadun_mantaurAI : public ScriptedAI
    {
        npc_prince_nadun_mantaurAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_TO_EVASION   = 1
        };

        enum pointId
        {
            POINT_TO_EVASION    = 1
        };

        enum npcId
        {
            NPC_ENTRY_ADARRAH           = 47912,
            NPC_ENTRY_MANTAUR_SAMIR     = 47112,
            NPC_ENTRY_MANTAUR_TANZAR    = 47098,
            NPC_ENTRY_LOST_CITY_CAMERA  = 47873,
        };

        enum eventId
        {
            EVENT_INFORM_ADARRAH_TO_ADVANCE     = 1,
            EVENT_DO_ESCAPE,
            EVENT_DO_ESCAPE_INFORM
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_INFORM_ADARRAH_TO_ADVANCE, 30000);
            TalkWithDelay(3000, 0, owner->GetGUID());
            TalkWithDelay(28000, 1, owner->GetGUID());
            me->SetWalk(true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TO_EVASION:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MovePoint(POINT_TO_EVASION, -11009.50f, -1272.58f, 13.24f);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_EVASION:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        TalkWithDelay(1000, 2, playerOwner->GetGUID());
                    events.ScheduleEvent(EVENT_DO_ESCAPE, 2000);
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
                    case EVENT_INFORM_ADARRAH_TO_ADVANCE:
                    {
                        events.CancelEvent(EVENT_INFORM_ADARRAH_TO_ADVANCE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Creature* adarrah = playerOwner->FindNearestCreature(NPC_ENTRY_ADARRAH, 50.0f, true))
                                adarrah->AI()->DoAction(2);
                        }
                        break;
                    }
                    case EVENT_DO_ESCAPE:
                    {
                        events.CancelEvent(EVENT_DO_ESCAPE);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(10, -10992.20f, -1362.96f, 10.80f);
                        events.ScheduleEvent(EVENT_DO_ESCAPE_INFORM, 2000);
                        break;
                    }
                    case EVENT_DO_ESCAPE_INFORM:
                    {
                        events.CancelEvent(EVENT_DO_ESCAPE_INFORM);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (Creature* mantaurSamir = playerOwner->FindNearestCreature(NPC_ENTRY_MANTAUR_SAMIR, 100.0f, true))
                            {
                                mantaurSamir->GetMotionMaster()->MovementExpired(false);
                                mantaurSamir->SetWalk(false);
                                mantaurSamir->GetMotionMaster()->MovePoint(10, -10992.20f, -1362.96f, 10.80f);
                            }
                            if (Creature* mantaurTanzar = playerOwner->FindNearestCreature(NPC_ENTRY_MANTAUR_TANZAR, 100.0f, true))
                            {
                                mantaurTanzar->GetMotionMaster()->MovementExpired(false);
                                mantaurTanzar->SetWalk(false);
                                mantaurTanzar->GetMotionMaster()->MovePoint(10, -10992.20f, -1362.96f, 10.80f);
                            }
                            if (Creature* eventCamera = playerOwner->FindNearestCreature(NPC_ENTRY_LOST_CITY_CAMERA, 10.0f, true))
                                eventCamera->AI()->DoAction(3);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_nadun_mantaurAI(creature);
    }
};

class npc_mantaur_camera_event : public CreatureScript
{
public:
   npc_mantaur_camera_event() : CreatureScript("npc_mantaur_camera_event") { }

    struct npc_mantaur_camera_eventAI : public ScriptedAI
    {
        npc_mantaur_camera_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_ADJUST_FACING    = 1,
            ACTION_FACING_EVADE,
            ACTION_FINAL_FACING
        };

        enum pointId
        {
            POINT_BEHIND_NADUN  = 1,
            POINT_TO_FINISH
        };

        enum npcId
        {
            NPC_ENTRY_PRINCE_NADUN_SUMMONED     = 47896
        };

        enum eventId
        {
            EVENT_ADJUST_FACING     = 1,
            EVENT_FACING_EVADE,
            EVENT_FINAL_FACING,
            EVENT_RAISE_AND_FINISH,
            EVENT_QUEST_COMPLETE
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_FADE_TO_BLACK     = 93488
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->AddUnitState(UNIT_STATE_ROTATING);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ADJUST_FACING:
                {
                    events.ScheduleEvent(EVENT_ADJUST_FACING, 1000);
                    break;
                }
                case ACTION_FACING_EVADE:
                {
                    events.ScheduleEvent(EVENT_FACING_EVADE, 1000);
                    break;
                }
                case ACTION_FINAL_FACING:
                {
                    events.ScheduleEvent(EVENT_FINAL_FACING, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId) { }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ADJUST_FACING:
                    {
                        events.CancelEvent(EVENT_ADJUST_FACING);
                        me->SetFacingTo(1.375f);
                        break;
                    }
                    case EVENT_FACING_EVADE:
                    {
                        events.CancelEvent(EVENT_FACING_EVADE);
                        me->SetFacingTo(4.57f);
                        break;
                    }
                    case EVENT_FINAL_FACING:
                    {
                        events.CancelEvent(EVENT_FINAL_FACING);
                        me->SetFacingTo(4.76f);
                        events.ScheduleEvent(EVENT_RAISE_AND_FINISH, 2000);
                        break;
                    }
                    case EVENT_RAISE_AND_FINISH:
                    {
                        events.CancelEvent(EVENT_RAISE_AND_FINISH);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-11000.55f, -1315.92f, 40.21f, 5.5f, 5.5f, POINT_TO_FINISH);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->CastWithDelay(5500, playerOwner, SPELL_FADE_TO_BLACK, true);
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 8000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetVehicle())
                                playerOwner->GetVehicle()->RemoveAllPassengers();
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mantaur_camera_eventAI(creature);
    }
};

class spell_draining_venom : public SpellScriptLoader
{
    public:
        spell_draining_venom() : SpellScriptLoader("spell_draining_venom") { }

        class spell_draining_venom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_draining_venom_SpellScript);

            enum Id
            {
                NPC_ENTRY_VENOMBLOOD_SCORPID    = 45859
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* venomScorpid = caster->FindNearestCreature(NPC_ENTRY_VENOMBLOOD_SCORPID, 5.0f, false))
                    {
                        scorpid = venomScorpid;
                        return SPELL_CAST_OK;
                    }
                    else
                    {
                        scorpid = NULL;
                        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleCreditAndDespawn()
            {
                if (Unit* caster = GetCaster())
                {
                    if (scorpid && scorpid != NULL)
                        scorpid->DespawnOrUnsummon(1);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_draining_venom_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_draining_venom_SpellScript::HandleCreditAndDespawn);
            }

        protected:
            Creature* scorpid;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_draining_venom_SpellScript();
        }
};

class npc_orsis_survivor_event : public CreatureScript
{
public:
   npc_orsis_survivor_event() : CreatureScript("npc_orsis_survivor_event") { }

    enum questId
    {
        QUEST_ENTRY_UNDER_THE_CHOCKING_SANDS    = 27519,
        QUEST_CREDIT_ORSIS_RESCUED              = 45715
    };

    enum actionId
    {
        ACTION_START    = 1
    };

    enum pointId
    {
        POINT_TO_GROUND     = 1
    };

    enum eventId
    {
        EVENT_START_JUMP    = 1
    };

    enum spellId
    {
        SPELL_BILLOWING_SMOKE_CLOUD     = 78609
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_UNDER_THE_CHOCKING_SANDS) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(QUEST_CREDIT_ORSIS_RESCUED);
            creature->AI()->DoAction(ACTION_START);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->AI()->TalkWithDelay(2000, 0, player->GetGUID());
            return true;
        }
        return true;
    }

    struct npc_orsis_survivor_eventAI : public ScriptedAI
    {
        npc_orsis_survivor_eventAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void Reset()
        {
            me->SetDisableGravity(true);
            me->SendGravityDisable();
            me->SetCanFly(true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START:
                {
                    events.ScheduleEvent(EVENT_START_JUMP, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_GROUND:
                {
                    me->SetWalk(false);
                    me->DespawnOrUnsummon(8000);
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
                    case EVENT_START_JUMP:
                    {
                        me->SetDisableGravity(false);
                        me->SetCanFly(false);
                        events.CancelEvent(EVENT_START_JUMP);
                        DoCast(me, SPELL_BILLOWING_SMOKE_CLOUD, true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+0.55f, 5.0f, 6.0f, POINT_TO_GROUND);
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
        return new npc_orsis_survivor_eventAI(creature);
    }
};

class npc_post_orsis_camera_event : public CreatureScript
{
public:
   npc_post_orsis_camera_event() : CreatureScript("npc_post_orsis_camera_event") { }

    struct npc_post_orsis_camera_eventAI : public ScriptedAI
    {
        npc_post_orsis_camera_eventAI(Creature* creature) : ScriptedAI(creature) {}

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_SUMMON_NADUN      = 87119,
            SPELL_FADE_TO_BLACK     = 89404
        };

        void IsSummonedBy(Unit* owner)
        {
            owner->AddAura(SPELL_UNIQUE_PHASING, owner);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->CastSpell(owner, SPELL_SUMMON_NADUN, true);
            owner->CastWithDelay(59000, owner, SPELL_FADE_TO_BLACK, true);
            me->DespawnOrUnsummon(60000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_post_orsis_camera_eventAI(creature);
    }
};

class npc_nadun_post_orsis_event : public CreatureScript
{
public:
   npc_nadun_post_orsis_event() : CreatureScript("npc_nadun_post_orsis_event") { }

    struct npc_nadun_post_orsis_eventAI : public ScriptedAI
    {
        npc_nadun_post_orsis_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_MOVING     = 1
        };

        enum pointId
        {
            POINT_TO_CENTER = 1
        };

        enum eventId
        {
            EVENT_START_MOVING  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        enum npcId
        {
            NPC_ENTRY_KING_PHAORIS  = 47684
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->DespawnOrUnsummon(59000);
            DoAction(ACTION_START_MOVING);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_MOVING:
                {
                    events.ScheduleEvent(EVENT_START_MOVING, 2500);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_CENTER:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (Creature* phaoris = me->FindNearestCreature(NPC_ENTRY_KING_PHAORIS, 50.0f, true))
                        {
                            phaoris->AI()->Talk(0, playerOwner->GetGUID());
                            TalkWithDelay(8000, 0, playerOwner->GetGUID());
                            phaoris->AI()->TalkWithDelay(16000, 1, playerOwner->GetGUID());
                            TalkWithDelay(24000, 1, playerOwner->GetGUID());
                            phaoris->AI()->TalkWithDelay(32000, 2, playerOwner->GetGUID());
                            TalkWithDelay(40000, 2, playerOwner->GetGUID());
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
                    case EVENT_START_MOVING:
                    {
                        events.CancelEvent(EVENT_START_MOVING);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TO_CENTER, -9388.86f, -958.86f, 113.76f, true);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_nadun_post_orsis_eventAI(creature);
    }
};

class npc_ramkahen_prisoner_chain : public CreatureScript
{
public:
   npc_ramkahen_prisoner_chain() : CreatureScript("npc_ramkahen_prisoner_chain") { }

    struct npc_ramkahen_prisoner_chainAI : public ScriptedAI
    {
        npc_ramkahen_prisoner_chainAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum eventId
        {
            EVENT_DO_CHAIN_PRISONER     = 1
        };

        enum spellId
        {
            SPELL_CHAIN_RIGHT   = 84991,
            SPELL_CHAIN_LEFT    = 84990
        };

        enum npcId
        {
            NPC_RAMKAHEN_PRISONER   = 46425,
            TRIGGER_GUID_RIGHT      = 735222,
            TRIGGER_GUID_LEFT       = 735221
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_DO_CHAIN_PRISONER, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DO_CHAIN_PRISONER:
                    {
                        events.RescheduleEvent(EVENT_DO_CHAIN_PRISONER, 2000);
                        if (Creature* prisoner = me->FindNearestCreature(NPC_RAMKAHEN_PRISONER, 50.0f, true))
                        {
                            if (prisoner->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED) || prisoner->isInCombat())
                                return;

                            switch (me->GetGUIDLow())
                            {
                                case TRIGGER_GUID_LEFT:
                                {
                                    if (!prisoner->HasAura(SPELL_CHAIN_LEFT))
                                        DoCast(prisoner, SPELL_CHAIN_LEFT, true);
                                    break;
                                }
                                case TRIGGER_GUID_RIGHT:
                                {
                                    if (!prisoner->HasAura(SPELL_CHAIN_RIGHT))
                                        DoCast(prisoner, SPELL_CHAIN_RIGHT, true);
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
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
        return new npc_ramkahen_prisoner_chainAI(creature);
    }
};

class npc_ramkahen_prisoner_event : public CreatureScript
{
public:
    npc_ramkahen_prisoner_event() : CreatureScript("npc_ramkahen_prisoner_event") { }

    enum questId
    {
        QUEST_ENTRY_NEFERSET_PRISON     = 27707
    };

    enum npcId
    {
        NPC_NEFERSET_OVERLORD   = 46441,
        NPC_NEFERSET_ENFORCER   = 46432
    };

    enum eventId
    {
        EVENT_SUMMON_ENFORCER_L         = 1,
        EVENT_SUMMON_ENFORCER_R,
        EVENT_SUMMON_OVERLORD,
        EVENT_CAST_POUND,
        EVENT_CAST_DEMORALIZING_SHOUT,
        EVENT_REMOVE_CHAINS
    };

    enum spellId
    {
        SPELL_DEMORALIZING_SHOUT    = 13730,
        SPELL_POUND                 = 74720,
        SPELL_QUEST_CREDIT          = 86544
    };

    enum actionId
    {
        ACTION_ENABLE_EVENT     = 1,
        ACTION_OUTRO
    };

    #define GOSSIP_TEXT_EVENT "I'm looking for Tahet.  Let's get you out of these chains."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ENTRY_NEFERSET_PRISON) == QUEST_STATUS_INCOMPLETE)
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                creature->AI()->Talk(0, player->GetGUID());
                creature->AI()->DoAction(ACTION_ENABLE_EVENT);
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_NEFERSET_PRISON) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_EVENT, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_ramkahen_prisoner_eventAI : public ScriptedAI
    {
        npc_ramkahen_prisoner_eventAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENABLE_EVENT:
                {
                    events.ScheduleEvent(EVENT_SUMMON_ENFORCER_L, 8000);
                    events.ScheduleEvent(EVENT_SUMMON_ENFORCER_R, 25000);
                    events.ScheduleEvent(EVENT_SUMMON_OVERLORD, 75000);
                    events.ScheduleEvent(EVENT_CAST_DEMORALIZING_SHOUT, 16500);
                    events.ScheduleEvent(EVENT_CAST_POUND, 15000);
                    break;
                }
                case ACTION_OUTRO:
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    TalkWithDelay(2000, 1);
                    TalkWithDelay(10000, 2);
                    TalkWithDelay(18000, 3);
                    events.ScheduleEvent(EVENT_REMOVE_CHAINS, 5000);
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
                    case EVENT_SUMMON_ENFORCER_R:
                    {
                        events.RescheduleEvent(EVENT_SUMMON_ENFORCER_R, 35000);
                        me->SummonCreature(NPC_NEFERSET_ENFORCER, -11087.13f, -1953.41f, 3.89f, 5.50f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    case EVENT_SUMMON_ENFORCER_L:
                    {
                        events.RescheduleEvent(EVENT_SUMMON_ENFORCER_L, 50000);
                        me->SummonCreature(NPC_NEFERSET_ENFORCER, -11090.81f, -1958.48f, 3.89f, 5.50f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    case EVENT_SUMMON_OVERLORD:
                    {
                        events.CancelEvent(EVENT_SUMMON_OVERLORD);
                        events.CancelEvent(EVENT_SUMMON_ENFORCER_L);
                        events.CancelEvent(EVENT_SUMMON_ENFORCER_R);
                        me->SummonCreature(NPC_NEFERSET_OVERLORD, -11104.50, -1939.43f, 2.79f, 5.44f, TEMPSUMMON_DEAD_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    case EVENT_CAST_DEMORALIZING_SHOUT:
                    {
                        events.RescheduleEvent(EVENT_CAST_DEMORALIZING_SHOUT, urand(8000, 15000));
                        if (me->isInCombat())
                            DoCast(SPELL_DEMORALIZING_SHOUT);
                        break;
                    }
                    case EVENT_CAST_POUND:
                    {
                        events.RescheduleEvent(EVENT_CAST_POUND, urand(5000, 8500));
                        if (me->isInCombat())
                            DoCast(SPELL_POUND);
                        break;
                    }
                    case EVENT_REMOVE_CHAINS:
                    {
                        events.CancelEvent(EVENT_REMOVE_CHAINS);
                        DoCastAOE(SPELL_QUEST_CREDIT);
                        me->RemoveAllAuras();
                        me->DespawnOrUnsummon(45000);
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
        return new npc_ramkahen_prisoner_eventAI(creature);
    }
};

class npc_neferset_overlord_event : public CreatureScript
{
public:
    npc_neferset_overlord_event() : CreatureScript("npc_neferset_overlord_event") { }

    enum npcId
    {
        NPC_RAMKAHEN_PRISONER   = 46425
    };

    struct npc_neferset_overlord_eventAI : public ScriptedAI
    {
        npc_neferset_overlord_eventAI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* prisoner = me->FindNearestCreature(NPC_RAMKAHEN_PRISONER, 100.0f, true))
                prisoner->AI()->DoAction(2);
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetWalk(false);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_AGGRESSIVE);
            if (Creature* prisoner = me->FindNearestCreature(NPC_RAMKAHEN_PRISONER, 100.0f, true))
                AttackStart(prisoner);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_neferset_overlord_eventAI(creature);
    }
};

class npc_dark_ritualist_zakahn : public CreatureScript
{
public:
    npc_dark_ritualist_zakahn() : CreatureScript("npc_dark_ritualist_zakahn") { }

    enum eventId
    {
        EVENT_CAST_ZAKAHN_SERPENTS      = 1,
        EVENT_CAST_SHADOW_BOLT_VOLLEY
    };

    enum spellId
    {
        SPELL_ZAKAHN_SERPENTS       = 91614,
        SPELL_SHADOW_BOLT_VOLLEY    = 9081
    };

    struct npc_dark_ritualist_zakahnAI : public ScriptedAI
    {
        npc_dark_ritualist_zakahnAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.CancelEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY);
            events.CancelEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CAST_ZAKAHN_SERPENTS, 12000);
            events.ScheduleEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_ZAKAHN_SERPENTS:
                    {
                        events.RescheduleEvent(EVENT_CAST_ZAKAHN_SERPENTS, 20000);
                        Talk(0);
                        me->CastWithDelay(3000, me, SPELL_ZAKAHN_SERPENTS);
                        break;
                    }
                    case EVENT_CAST_SHADOW_BOLT_VOLLEY:
                    {
                        events.RescheduleEvent(EVENT_CAST_SHADOW_BOLT_VOLLEY, urand(4000,6000));
                        DoCastAOE(SPELL_SHADOW_BOLT_VOLLEY, true);
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
        return new npc_dark_ritualist_zakahnAI(creature);
    }
};

class npc_tahet_pit_of_scales : public CreatureScript
{
public:
    npc_tahet_pit_of_scales() : CreatureScript("npc_tahet_pit_of_scales") { }

    enum eventId
    {
        EVENT_CAST_ROPE     = 1
    };

    enum npcId
    {
        NPC_ENTRY_ROPE_TRIGGER  = 40350,
        NPC_ENTRY_CAIMAS        = 46276
    };

    enum spellId
    {
        SPELL_COSMETIC_ROPE     = 87926,
        SPELL_TAHET_IMPRISONED  = 101422
    };

    enum questId
    {
        QUEST_ENTRY_THE_PIT_OF_SCALES   = 27738
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        Creature* caimas = creature->FindNearestCreature(NPC_ENTRY_CAIMAS, 100.0f, true);
        if (player->GetQuestStatus(QUEST_ENTRY_THE_PIT_OF_SCALES) == QUEST_STATUS_INCOMPLETE)
        {
            creature->SetStandState(UNIT_STAND_STATE_DEAD);
            creature->RemoveAllAuras();
            creature->CastStop();
            if (!caimas)
                player->SummonCreature(NPC_ENTRY_CAIMAS, -11450.20f, -1145.05f, 3.74f, 4.71f, TEMPSUMMON_DEAD_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return true;
        }
        return false;
    }

    struct npc_tahet_pit_of_scalesAI : public ScriptedAI
    {
        npc_tahet_pit_of_scalesAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void InitializeAI()
        {
            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_TAHET_IMPRISONED, true);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_CAST_ROPE, 1000);
        }

        void CheckForTriggers()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 45.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(45.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->ToCreature()->GetEntry() == NPC_ENTRY_ROPE_TRIGGER)
                    {
                        if (!(*itr)->HasAura(SPELL_COSMETIC_ROPE))
                            DoCast((*itr), SPELL_COSMETIC_ROPE, true);
                    }
                }
            }

            eventInProgress = false;
        }


        void UpdateAI(uint32 diff)
        {
            if (me->getStandState() == UNIT_STAND_STATE_DEAD)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_ROPE:
                    {
                        events.CancelEvent(EVENT_CAST_ROPE);
                        CheckForTriggers();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool eventInProgress;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tahet_pit_of_scalesAI(creature);
    }
};

class npc_caimas_the_pit_master : public CreatureScript
{
public:
    npc_caimas_the_pit_master() : CreatureScript("npc_caimas_the_pit_master") { }

    enum actionId
    {
        ACTION_MOVE_TO_TALK     = 1,
        ACTION_INCREASE_COUNT
    };

    enum pointId
    {
        POINT_TO_TALK   = 1,
        POINT_TO_ARENA
    };

    enum eventId
    {
        EVENT_SUMMON_FIRST_CROCK    = 1,
        EVENT_SUMMON_SECOND_CROCK,
        EVENT_JUMP_TO_FIGHT,
        EVENT_START_FIGHT,
        EVENT_CHECK_EGGS,
        EVENT_CHECK_RESTART
    };

    enum npcId
    {
        NPC_ENTRY_GOREBITE  = 46278,
        NPC_ENTRY_THARTEP   = 46280,
        NPC_ENTRY_KAMEN     = 46281,
        NPC_ENTRY_TAHET     = 46496
    };

    enum goId
    {
        GO_ENTRY_CROC_EGGS  = 206112
    };

    enum soundId
    {
        PLAY_SOUND_EGGS_EXPLODE     = 22433
    };

    enum spellId
    {
        SPELL_TAHET_IMPRISONED  = 101422,
        SPELL_TAHET_CREDIT      = 86747,
        SPELL_TINY_TEETH        = 86593
    };

    struct npc_caimas_the_pit_masterAI : public ScriptedAI
    {
        npc_caimas_the_pit_masterAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void JustDied(Unit* /*who*/)
        {
            if (Creature* tahet = me->FindNearestCreature(NPC_ENTRY_TAHET, 200.0f, true))
            {
                tahet->SetStandState(UNIT_STAND_STATE_STAND);
                tahet->RemoveAllAuras();
                tahet->CastStop();
                tahet->CastSpell(tahet, SPELL_TAHET_CREDIT);
                tahet->AI()->Talk(0);
                tahet->DespawnOrUnsummon(15000);
            }
            crocksDead = 0;
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            crocksDead = 0;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            DoAction(ACTION_MOVE_TO_TALK);
            events.ScheduleEvent(EVENT_CHECK_RESTART, 600000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_TO_TALK:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MovePoint(POINT_TO_TALK, -11450.41f, -1166.27f, 3.97f);
                    break;
                }
                case ACTION_INCREASE_COUNT:
                {
                    crocksDead++;
                    if (crocksDead == 1)
                        events.ScheduleEvent(EVENT_SUMMON_SECOND_CROCK, 1000);
                    if (crocksDead >= 3)
                        events.ScheduleEvent(EVENT_JUMP_TO_FIGHT, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_TALK:
                {
                    TalkWithDelay(1000, 0);
                    TalkWithDelay(10000, 1);
                    events.ScheduleEvent(EVENT_SUMMON_FIRST_CROCK, 10000);
                    break;
                }
                case POINT_TO_ARENA:
                {
                    TalkWithDelay(1000, 3);
                    TalkWithDelay(5000, 4);
                    events.ScheduleEvent(EVENT_START_FIGHT, 3000);
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
                    case EVENT_SUMMON_FIRST_CROCK:
                    {
                        events.CancelEvent(EVENT_SUMMON_FIRST_CROCK);
                        me->SummonCreature(NPC_ENTRY_GOREBITE, -11471.95f, -1237.68f, 1.31f, 1.57f, TEMPSUMMON_DEAD_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    case EVENT_SUMMON_SECOND_CROCK:
                    {
                        events.CancelEvent(EVENT_SUMMON_SECOND_CROCK);
                        Talk(2);
                        me->SummonCreature(NPC_ENTRY_KAMEN, -11508.35f, -1153.16f, 1.75f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        me->SummonCreature(NPC_ENTRY_THARTEP, -11395.34f, -1149.69f, 2.37f, 3.18f, TEMPSUMMON_DEAD_DESPAWN, 30000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    case EVENT_JUMP_TO_FIGHT:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-11451.22f, -1180.14f, -2.64f, 10.0f, 10.0f, POINT_TO_ARENA);
                        me->SetHomePosition(-11451.22f, -1180.14f, -2.64f, 4.75f);
                        break;
                    }
                    case EVENT_START_FIGHT:
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        events.ScheduleEvent(EVENT_CHECK_EGGS, 1500);
                        break;
                    }
                    case EVENT_CHECK_EGGS:
                    {
                        if (me->HasAura(SPELL_TINY_TEETH))
                        {
                            events.RescheduleEvent(EVENT_CHECK_EGGS, 1500);
                            return;
                        }

                        if (GameObject* eggs = me->FindNearestGameObject(GO_ENTRY_CROC_EGGS, 3.0f))
                        {
                            if (eggs->GetGoState() == GO_STATE_READY)
                            {
                                eggs->Use(me);
                                me->PlayDirectSound(PLAY_SOUND_EGGS_EXPLODE);
                                events.RescheduleEvent(EVENT_CHECK_EGGS, 10000);
                                return;
                            }
                        }

                        events.RescheduleEvent(EVENT_CHECK_EGGS, 1500);
                        break;
                    }
                    case EVENT_CHECK_RESTART:
                    {
                        events.CancelEvent(EVENT_CHECK_RESTART);
                        me->DespawnCreaturesInArea(NPC_ENTRY_TAHET);
                        me->DespawnCreaturesInArea(NPC_ENTRY_GOREBITE);
                        me->DespawnCreaturesInArea(NPC_ENTRY_THARTEP);
                        me->DespawnCreaturesInArea(NPC_ENTRY_KAMEN);
                        me->DespawnOrUnsummon(1000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

    protected:
        uint8 crocksDead;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_caimas_the_pit_masterAI(creature);
    }
};

class npc_entry_gorebite : public CreatureScript
{
public:
    npc_entry_gorebite() : CreatureScript("npc_entry_gorebite") { }

    enum pointId
    {
        POINT_TO_ARENA   = 1
    };

    enum npcId
    {
        NPC_ENTRY_CAIMAS    = 46276
    };

    struct npc_entry_gorebiteAI : public ScriptedAI
    {
        npc_entry_gorebiteAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetWalk(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MovementExpired(false);
            me->GetMotionMaster()->MovePoint(POINT_TO_ARENA, -11450.77f, -1194.13f, -2.64f);
        }

        void JustDied(Unit* /*victim*/)
        {
            if (Creature* caimas = me->FindNearestCreature(NPC_ENTRY_CAIMAS, 200.0f, true))
                caimas->AI()->DoAction(2);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_ARENA:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_entry_gorebiteAI(creature);
    }
};

class npc_entry_thartep : public CreatureScript
{
public:
    npc_entry_thartep() : CreatureScript("npc_entry_thartep") { }

    enum pointId
    {
        POINT_TO_ARENA   = 1
    };

    enum npcId
    {
        NPC_ENTRY_CAIMAS    = 46276
    };

    struct npc_entry_thartepAI : public ScriptedAI
    {
        npc_entry_thartepAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetWalk(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MovementExpired(false);
            me->GetMotionMaster()->MovePoint(POINT_TO_ARENA, -11439.37f, -1180.78f, -2.64f);
        }

        void JustDied(Unit* /*victim*/)
        {
            if (Creature* caimas = me->FindNearestCreature(NPC_ENTRY_CAIMAS, 200.0f, true))
                caimas->AI()->DoAction(2);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_ARENA:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_entry_thartepAI(creature);
    }
};

class npc_entry_kamen : public CreatureScript
{
public:
    npc_entry_kamen() : CreatureScript("npc_entry_kamen") { }

    enum pointId
    {
        POINT_TO_ARENA   = 1
    };

    enum npcId
    {
        NPC_ENTRY_CAIMAS    = 46276
    };

    struct npc_entry_kamenAI : public ScriptedAI
    {
        npc_entry_kamenAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetWalk(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MovementExpired(false);
            me->GetMotionMaster()->MovePoint(POINT_TO_ARENA, -11460.16f, -1184.37f, -2.64f);
        }

        void JustDied(Unit* /*victim*/)
        {
            if (Creature* caimas = me->FindNearestCreature(NPC_ENTRY_CAIMAS, 200.0f, true))
                caimas->AI()->DoAction(2);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_ARENA:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_entry_kamenAI(creature);
    }
};

class npc_young_crocolisk : public CreatureScript
{
public:
    npc_young_crocolisk() : CreatureScript("npc_young_crocolisk") { }

    enum eventId
    {
        EVENT_JUMP_ON_TARGET    = 1
    };

    struct npc_young_crocoliskAI : public ScriptedAI
    {
        npc_young_crocoliskAI(Creature* creature) : ScriptedAI(creature) {targetInvoker = NULL;}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MoveChase(owner, 1.0f, frand(1.0f, 4.5f));
            events.ScheduleEvent(EVENT_JUMP_ON_TARGET, 100);
            targetInvoker = owner;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_JUMP_ON_TARGET:
                    {
                        events.CancelEvent(EVENT_JUMP_ON_TARGET);
                        if (targetInvoker && targetInvoker != NULL && targetInvoker->IsInWorld())
                        {
                            if (targetInvoker->GetVehicleKit())
                            {
                                if (!targetInvoker->GetVehicleKit()->GetAvailableSeatCount())
                                {
                                    me->DisappearAndDie();
                                    break;
                                }

                                me->GetMotionMaster()->MovementExpired(false);
                                me->EnterVehicle(targetInvoker, urand(0, 7));
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* targetInvoker;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_young_crocoliskAI(creature);
    }
};

class spell_tiny_teeth : public SpellScriptLoader
{
    public:
        spell_tiny_teeth() : SpellScriptLoader("spell_tiny_teeth") { }

        class spell_tiny_teeth_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tiny_teeth_SpellScript);

            enum Id
            {
                NPC_ENTRY_YOUNG_CROCOLISK   = 46279,
                PLAY_SOUND_EGGS_EXPLODE     = 22433
            };

            void HandleSummonCrocolisks()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        caster->MonsterWhisper("Jump to shake off the young crocolisks!", caster->GetGUID(), true);
                        caster->PlayDirectSound(PLAY_SOUND_EGGS_EXPLODE);
                    }

                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()+urand(1,5), caster->GetPositionY()+urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()+urand(1,5), caster->GetPositionY()-urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()-urand(1,5), caster->GetPositionY()-urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()+urand(1,5), caster->GetPositionY()+urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()-urand(1,5), caster->GetPositionY()-urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()+urand(1,5), caster->GetPositionY()+urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()+urand(1,5), caster->GetPositionY()-urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_YOUNG_CROCOLISK, caster->GetPositionX()-urand(1,5), caster->GetPositionY()-urand(1,5), caster->GetPositionZ(), caster->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_tiny_teeth_SpellScript::HandleSummonCrocolisks);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_tiny_teeth_SpellScript();
        }
};

class npc_king_phaoris : public CreatureScript
{
public:
   npc_king_phaoris() : CreatureScript("npc_king_phaoris") { }

    enum questId
    {
        QUEST_THE_HIGH_COUNCIL_DECISION     = 28533
    };

    enum spellId
    {
        SPELL_SUMMON_CAMERA_EVENT   = 91628,
        SPELL_UNIQUE_PHASING        = 60191
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_THE_HIGH_COUNCIL_DECISION)
        {
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->SetPhaseMask(2, true);
            player->CastWithDelay(1000, player, SPELL_SUMMON_CAMERA_EVENT, true);
            return true;
        }
        return true;
    }
};

class npc_high_council_event_camera : public CreatureScript
{
public:
   npc_high_council_event_camera() : CreatureScript("npc_high_council_event_camera") { }

    struct npc_high_council_event_cameraAI : public ScriptedAI
    {
        npc_high_council_event_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_KAMSES    = 49383,
            NPC_ENTRY_VIZIER    = 49175,
            NPC_ENTRY_AMET      = 49172,
            NPC_ENTRY_ENVOY     = 49202,
            NPC_ENTRY_PHAORIS   = 49170
        };

        enum eventId
        {
            EVENT_POINT_KAMSES      = 1,
            EVENT_POINT_VIZIER,
            EVENT_POINT_ENVOY,
            EVENT_POINT_HIGH_PRIEST,
            EVENT_POINT_PHAORIS,
            EVENT_REMOVE_PASSENGER
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_FADE_TO_BLACK         = 93488,
            SPELL_SUMMON_PHAORIS        = 91630,
            SPELL_SUMMON_KAMSES         = 91974,
            SPELL_SUMMON_VIZIER         = 91643,
            SPELL_SUMMON_HIGH_PRIEST    = 91634,
            SPELL_RIDE_CAMERA           = 63314,
            SPELL_CAMERA_CHANNEL        = 88552
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->CastWithDelay(1000, me, SPELL_RIDE_CAMERA, true);
            me->AddUnitState(UNIT_STATE_ROTATING);
            owner->CastWithDelay(1000, owner, SPELL_SUMMON_PHAORIS, true);
            owner->CastWithDelay(1000, owner, SPELL_SUMMON_KAMSES, true);
            owner->CastWithDelay(1000, owner, SPELL_SUMMON_VIZIER, true);
            owner->CastWithDelay(1000, owner, SPELL_SUMMON_HIGH_PRIEST, true);
            events.ScheduleEvent(EVENT_POINT_VIZIER, 15000);
            events.ScheduleEvent(EVENT_POINT_HIGH_PRIEST, 21000);
            events.ScheduleEvent(EVENT_POINT_ENVOY, 39000);
            events.ScheduleEvent(EVENT_POINT_PHAORIS, 59500);
            events.ScheduleEvent(EVENT_REMOVE_PASSENGER, 75000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_POINT_VIZIER:
                    {
                        events.CancelEvent(EVENT_POINT_KAMSES);
                        if (Creature* kamses = me->FindNearestCreature(NPC_ENTRY_KAMSES, 60.0f, true))
                            DoCast(kamses, SPELL_CAMERA_CHANNEL);
                        break;
                    }
                    case EVENT_POINT_HIGH_PRIEST:
                    {
                        events.CancelEvent(EVENT_POINT_HIGH_PRIEST);
                        me->CastStop();
                        if (Creature* amet = me->FindNearestCreature(NPC_ENTRY_AMET, 60.0f, true))
                            DoCast(amet, SPELL_CAMERA_CHANNEL);
                        break;
                    }
                    case EVENT_POINT_ENVOY:
                    {
                        events.CancelEvent(EVENT_POINT_ENVOY);
                        me->CastStop();
                        if (Creature* envoy = me->FindNearestCreature(NPC_ENTRY_ENVOY, 60.0f, true))
                            DoCast(envoy, SPELL_CAMERA_CHANNEL);
                        break;
                    }
                    case EVENT_POINT_PHAORIS:
                    {
                        events.CancelEvent(EVENT_POINT_PHAORIS);
                        me->CastStop();
                        break;
                    }
                    case EVENT_REMOVE_PASSENGER:
                    {
                        events.CancelEvent(EVENT_REMOVE_PASSENGER);
                        me->RemoveAurasDueToSpell(SPELL_RIDE_CAMERA);
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_high_council_event_cameraAI(creature);
    }
};

class npc_king_phaoris_council_event : public CreatureScript
{
public:
   npc_king_phaoris_council_event() : CreatureScript("npc_king_phaoris_council_event") { }

    struct npc_king_phaoris_council_eventAI : public ScriptedAI
    {
        npc_king_phaoris_council_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_KAMSES    = 49383,
            NPC_ENTRY_VIZIER    = 49175,
            NPC_ENTRY_AMET      = 49172
        };

        enum eventId
        {
            EVENT_WORD_TO_OTHERS    = 1,
            EVENT_CALL_ENVOY
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_SUMMON_ENVOY      = 91708
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->AI()->TalkWithDelay(2000, 0, owner->GetGUID());
            events.ScheduleEvent(EVENT_WORD_TO_OTHERS, 7000);
            events.ScheduleEvent(EVENT_CALL_ENVOY, 35500);
            me->AI()->TalkWithDelay(59500, 1, owner->GetGUID());
            me->AI()->TalkWithDelay(64000, 2, owner->GetGUID());
            me->AI()->TalkWithDelay(70000, 3, owner->GetGUID());
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_WORD_TO_OTHERS:
                    {
                        events.CancelEvent(EVENT_WORD_TO_OTHERS);
                        if (Creature* kamses = me->FindNearestCreature(NPC_ENTRY_KAMSES, 50.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                                kamses->AI()->TalkWithDelay(1000, 0, playerOwner->GetGUID());
                        }
                        if (Creature* vizier = me->FindNearestCreature(NPC_ENTRY_VIZIER, 50.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                                vizier->AI()->TalkWithDelay(8000, 0, playerOwner->GetGUID());
                        }
                        if (Creature* amet = me->FindNearestCreature(NPC_ENTRY_AMET, 50.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            {
                                amet->AI()->TalkWithDelay(12000, 0, playerOwner->GetGUID());
                                amet->AI()->TalkWithDelay(20000, 1, playerOwner->GetGUID());
                                amet->AI()->TalkWithDelay(28000, 2, playerOwner->GetGUID());
                            }
                        }
                        break;
                    }
                    case EVENT_CALL_ENVOY:
                    {
                        events.CancelEvent(EVENT_CALL_ENVOY);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ENVOY, true);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_phaoris_council_eventAI(creature);
    }
};

class npc_envoy_council_event : public CreatureScript
{
public:
   npc_envoy_council_event() : CreatureScript("npc_envoy_council_event") { }

    struct npc_envoy_council_eventAI : public ScriptedAI
    {
        npc_envoy_council_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        enum actionId
        {
            ACTION_DO_TALK  = 1
        };

        enum pointId
        {
            POINT_TO_COUNCIL    = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->GetMotionMaster()->MovementExpired(false);
            me->GetMotionMaster()->MovePoint(POINT_TO_COUNCIL, -9387.43f, -962.45f, 113.76f);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DO_TALK:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        me->AI()->TalkWithDelay(1000, 0, playerOwner->GetGUID());
                        me->AI()->TalkWithDelay(9000, 1, playerOwner->GetGUID());
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_COUNCIL:
                {
                    DoAction(ACTION_DO_TALK);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_envoy_council_eventAI(creature);
    }
};

class npc_sun_radiance : public CreatureScript
{
public:
   npc_sun_radiance() : CreatureScript("npc_sun_radiance") { }

    struct npc_sun_radianceAI : public ScriptedAI
    {
        npc_sun_radianceAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        enum pointId
        {
            POINT_TO_UPPER  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_HOLY_RADIANCE_EFFECT  = 90118
        };

        enum questId
        {
            QUEST_ENTRY_THE_DEFENSE_OF_NAHOM    = 28501
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            if (owner->GetTypeId() == TYPEID_PLAYER)
            {
                if (owner->ToPlayer()->GetQuestStatus(QUEST_ENTRY_THE_DEFENSE_OF_NAHOM) == QUEST_STATUS_INCOMPLETE)
                {
                    owner->AddAura(SPELL_UNIQUE_PHASING, me);
                    return;
                }

                me->SetWalk(true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->GetMotionMaster()->MovementExpired(false);
                me->GetMotionMaster()->MoveJump(-9794.49f, -1731.69f, 46.26f, 1.5f, 1.5f, POINT_TO_UPPER);
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
               return;

            switch (pointId)
            {
                case POINT_TO_UPPER:
                {
                    me->CastSpell(me, SPELL_HOLY_RADIANCE_EFFECT, true);
                    me->DespawnOrUnsummon(1000);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sun_radianceAI(creature);
    }
};

class npc_ramkahen_sergeant : public CreatureScript
{
public:
    npc_ramkahen_sergeant() : CreatureScript("npc_ramkahen_sergeant") { }

    enum questId
    {
        QUEST_ENTRY_THE_DEFENSE_OF_NAHOM  = 28501
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING        = 60191,
        SPELL_NAHOM_BATTLE_CAMERA   = 85208
    };

    enum npcId
    {
        NPC_RAMKAHEN_ARCHER     = 45679,
        NPC_RAMKAHEN_CHAMPION   = 45643,
        NPC_CHAMPION_CONTROLLER = 45660,
        NPC_ARCHER_CONTROLLER   = 45680,
        NPC_LIGHT_CONTROLLER    = 48466,
        NPC_WAVES_CONTROLLER    = 48486,
        NPC_SUN_RADIANCE        = 51147
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_THE_DEFENSE_OF_NAHOM) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->SetPhaseMask(180, true);
            player->CastWithDelay(500, player, SPELL_NAHOM_BATTLE_CAMERA, true);

            // Prepare Archers
            player->SummonCreature(NPC_RAMKAHEN_ARCHER, -9768.83f, -1705.43f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_ARCHER, -9771.88f, -1702.68f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_ARCHER, -9774.87f, -1699.70f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_ARCHER, -9771.29f, -1707.67f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_ARCHER, -9774.21f, -1704.90f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_ARCHER, -9777.05f, -1701.86f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

            // Prepare Champions
            player->SummonCreature(NPC_RAMKAHEN_CHAMPION, -9759.74f, -1694.91f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_CHAMPION, -9761.75f, -1692.57f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_CHAMPION, -9763.82f, -1690.30f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_CHAMPION, -9762.34f, -1697.43f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_CHAMPION, -9764.04f, -1695.18f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_RAMKAHEN_CHAMPION, -9766.11f, -1692.51f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

            // Prepare Controllers
            player->SummonCreature(NPC_CHAMPION_CONTROLLER, -9756.54f, -1688.55f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_ARCHER_CONTROLLER, -9756.54f, -1688.55f, 22.33f, 0.75f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_LIGHT_CONTROLLER, -9790.03f, -1724.20f, 64.04f, 0.81f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_SUN_RADIANCE, -9790.03f, -1724.20f, 64.04f, 0.81f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_WAVES_CONTROLLER, -9680.23f, -1614.10f, 15.66f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return true;
        }
        return false;
    }
};

class npc_champions_controller : public CreatureScript
{
public:
   npc_champions_controller() : CreatureScript("npc_champions_controller") { }

    struct npc_champions_controllerAI : public ScriptedAI
    {
        npc_champions_controllerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_RAMKAHEN_CHAMPION     = 45643
        };

        enum eventId
        {
            EVENT_COORDINATE_CHAMPIONS  = 1
        };

        enum actionId
        {
            ACTION_REGROUP  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_COORDINATE_CHAMPIONS, 500);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_REGROUP:
                {
                    events.ScheduleEvent(EVENT_COORDINATE_CHAMPIONS, 100);
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
                    case EVENT_COORDINATE_CHAMPIONS:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            events.CancelEvent(EVENT_COORDINATE_CHAMPIONS);
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->GetEntry() == NPC_ENTRY_RAMKAHEN_CHAMPION &&
                                    (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    (*itr)->SetWalk(false);
                                    (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                                    (*itr)->GetMotionMaster()->MoveFollow(me, frand(0.0f, 3.0f), frand(0, 4.5f));
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_champions_controllerAI(creature);
    }
};

class spell_move_champions : public SpellScriptLoader
{
    public:
        spell_move_champions() : SpellScriptLoader("spell_move_champions") { }

        class spell_move_champions_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_move_champions_SpellScript);

            enum Id
            {
                NPC_ENTRY_CHAMPION_CONTROLLER   = 45660
            };

            void HandleTeleportController()
            {
                WorldLocation const* const position = GetExplTargetDest();

                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 400.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(400.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == caster->GetCharmerOrOwner())
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_CHAMPION_CONTROLLER)
                            {
                                (*itr)->NearTeleportTo(*position);
                                (*itr)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_move_champions_SpellScript::HandleTeleportController);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_move_champions_SpellScript();
        }
};

class spell_flame_arrows : public SpellScriptLoader
{
    public:
        spell_flame_arrows() : SpellScriptLoader("spell_flame_arrows") { }

        class spell_flame_arrows_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_flame_arrows_SpellScript);

            enum Id
            {
                NPC_ENTRY_ARCHER_CONTROLLER   = 45680
            };

            void HandleTeleportController()
            {
                WorldLocation const* const position = GetExplTargetDest();

                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 400.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(400.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == caster->GetCharmerOrOwner())
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_ARCHER_CONTROLLER)
                            {
                                (*itr)->NearTeleportTo(*position);
                                (*itr)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_flame_arrows_SpellScript::HandleTeleportController);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_flame_arrows_SpellScript();
        }
};

class spell_sun_radiance : public SpellScriptLoader
{
    public:
        spell_sun_radiance() : SpellScriptLoader("spell_sun_radiance") { }

        class spell_sun_radiance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sun_radiance_SpellScript);

            enum Id
            {
                NPC_ENTRY_LIGHT_CONTROLLER   = 48466
            };

            void HandleTeleportController()
            {
                WorldLocation const* const position = GetExplTargetDest();

                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 400.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(400.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == caster->GetCharmerOrOwner())
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_LIGHT_CONTROLLER)
                            {
                                (*itr)->NearTeleportTo(*position);
                                (*itr)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_sun_radiance_SpellScript::HandleTeleportController);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sun_radiance_SpellScript();
        }
};

class npc_archers_controller : public CreatureScript
{
public:
   npc_archers_controller() : CreatureScript("npc_archers_controller") { }

    struct npc_archers_controllerAI : public ScriptedAI
    {
        npc_archers_controllerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_RAMKAHEN_ARCHER     = 45679
        };

        enum eventId
        {
            EVENT_ORDER_LAUNCH  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_EXPLOSIVE_ARROWS  = 89805
        };

        enum actionId
        {
            ACTION_START_LAUNCH     = 1
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_LAUNCH:
                {
                    events.ScheduleEvent(EVENT_ORDER_LAUNCH, 1);
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
                    case EVENT_ORDER_LAUNCH:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            events.CancelEvent(EVENT_ORDER_LAUNCH);
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->GetEntry() == NPC_ENTRY_RAMKAHEN_ARCHER &&
                                    (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                    ((*itr)->CastSpell(me, SPELL_EXPLOSIVE_ARROWS, true));
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_archers_controllerAI(creature);
    }
};

class npc_light_controller : public CreatureScript
{
public:
   npc_light_controller() : CreatureScript("npc_light_controller") { }

    struct npc_light_controllerAI : public ScriptedAI
    {
        npc_light_controllerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_SUN_RADIANCE  = 51147
        };

        enum eventId
        {
            EVENT_ORDER_LAUNCH  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_RADIANCE_EFFECT   = 90113
        };

        enum actionId
        {
            ACTION_START_LAUNCH     = 1
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_LAUNCH:
                {
                    events.ScheduleEvent(EVENT_ORDER_LAUNCH, 500);
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
                    case EVENT_ORDER_LAUNCH:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            events.CancelEvent(EVENT_ORDER_LAUNCH);
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                            playerOwner->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_SUN_RADIANCE
                                    && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    (*itr)->ToCreature()->CastSpell(me, SPELL_RADIANCE_EFFECT);
                                    (*itr)->ToCreature()->AddAura(SPELL_RADIANCE_EFFECT, me);
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_light_controllerAI(creature);
    }
};

class npc_waves_controller : public CreatureScript
{
public:
   npc_waves_controller() : CreatureScript("npc_waves_controller") {}

    struct npc_waves_controllerAI : public ScriptedAI
    {
        npc_waves_controllerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_NEFERSET_INFANTRY     = 45543,
            NPC_ENTRY_ENSORCELED_COLOSSUS   = 45586,
            NPC_ENTRY_GREATER_COLOSSUS      = 48490
        };

        enum eventId
        {
            EVENT_SPAWN_WAVES           = 1,
            EVENT_SPAWN_SECONDARY_WAVES,
            EVENT_SPAWN_GIANTS,
            EVENT_SPAWN_FINAL
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_SPAWN_WAVES, 3000);
            events.ScheduleEvent(EVENT_SPAWN_SECONDARY_WAVES, 20000);
            events.ScheduleEvent(EVENT_SPAWN_GIANTS, 30000);
            events.ScheduleEvent(EVENT_SPAWN_FINAL, 180000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPAWN_WAVES:
                    {
                        events.RescheduleEvent(EVENT_SPAWN_WAVES, urand(20000, 25000));
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9673.58f+urand(1,2), -1690.70f+urand(1,2), 13.32f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9671.50f+urand(1,2), -1686.88f+urand(1,2), 13.64f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9669.14f+urand(1,2), -1682.55f+urand(1,2), 13.99f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9666.77f+urand(1,2), -1678.21f+urand(1,2), 14.44f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9663.84f+urand(1,2), -1672.84f+urand(1,2), 15.23f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9660.93f+urand(1,2), -1667.50f+urand(1,2), 16.25f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        break;
                    }
                    case EVENT_SPAWN_SECONDARY_WAVES:
                    {
                        events.RescheduleEvent(EVENT_SPAWN_SECONDARY_WAVES, urand(40000, 60000));
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9733.92f+urand(1,5), -1621.35f+urand(1,5), 14.55f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9741.98f+urand(1,5), -1619.81f+urand(1,5), 14.42f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9750.66f+urand(1,5), -1618.15f+urand(1,5), 14.59f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9761.14f+urand(1,5), -1616.14f+urand(1,5), 15.23f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9769.78f+urand(1,5), -1614.49f+urand(1,5), 15.80f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_INFANTRY, -9777.80f+urand(1,5), -1612.96f+urand(1,5), 16.01f, 6.09f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        break;
                    }
                    case EVENT_SPAWN_GIANTS:
                    {
                        events.RescheduleEvent(EVENT_SPAWN_GIANTS, urand(45000, 65000));
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->SummonCreature(NPC_ENTRY_ENSORCELED_COLOSSUS, -9763.96f, -1605.37f, 17.88f, 4.77f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_ENSORCELED_COLOSSUS, -9687.57f, -1626.97f, 16.42f, 4.38f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_ENSORCELED_COLOSSUS, -9660.93f, -1667.50f, 16.25f, 4.21f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        break;
                    }
                    case EVENT_SPAWN_FINAL:
                    {
                        events.CancelEvent(EVENT_SPAWN_FINAL);
                        events.CancelEvent(EVENT_SPAWN_GIANTS);
                        events.CancelEvent(EVENT_SPAWN_WAVES);
                        events.CancelEvent(EVENT_SPAWN_SECONDARY_WAVES);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->SummonCreature(NPC_ENTRY_GREATER_COLOSSUS, -9745.51f, -1632.39f, 11.99f, 4.61f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_waves_controllerAI(creature);
    }
};

class npc_neferset_wave_attacker : public CreatureScript
{
public:
   npc_neferset_wave_attacker() : CreatureScript("npc_neferset_wave_attacker") { }

    struct npc_neferset_wave_attackerAI : public ScriptedAI
    {
        npc_neferset_wave_attackerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum pointId
        {
            POINT_TO_UP     = 1
        };

        enum npcId
        {
            NPC_ENTRY_NAHOM_CAMERA      = 45670,
            NPC_ENTRY_GREATER_COLOSSUS  = 48490,
            NPC_ENTRY_RAMKAHEN_CHAMP    = 45643
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->MovePoint(POINT_TO_UP, -9757.82f, -1693.80f, 22.25f);
        }

        void JustDied(Unit* /*who*/)
        {
            if (me->GetEntry() == NPC_ENTRY_GREATER_COLOSSUS)
            {
                if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 400.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                    playerOwner->VisitNearbyObject(400.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_NAHOM_CAMERA)
                                (*itr)->ToCreature()->AI()->DoAction(3);
                        }
                    }
                }
            }
            me->DespawnOrUnsummon(5000);
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_neferset_wave_attackerAI(creature);
    }
};

class npc_infantry_and_archer_counter : public CreatureScript
{
public:
   npc_infantry_and_archer_counter() : CreatureScript("npc_infantry_and_archer_counter") { }

    struct npc_infantry_and_archer_counterAI : public ScriptedAI
    {
        npc_infantry_and_archer_counterAI(Creature* creature) : ScriptedAI(creature) {}

        enum npcId
        {
            NPC_ENTRY_CAMERA_CONTROLLER     = 45670,
            NPC_ENTRY_RAMKAHEN_CHAMPION     = 45643
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void JustDied(Unit* /*who*/)
        {
            if (me->GetEntry() == NPC_ENTRY_RAMKAHEN_CHAMPION)
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 400.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                playerOwner->VisitNearbyObject(400.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        if ((*itr)->GetEntry() == NPC_ENTRY_CAMERA_CONTROLLER)
                            (*itr)->ToCreature()->AI()->DoAction(1);
                    }
                }
            }
            me->DespawnOrUnsummon(5000);
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetReactState(REACT_AGGRESSIVE);
        };

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_infantry_and_archer_counterAI(creature);
    }
};

class npc_nahom_battle_camera : public CreatureScript
{
public:
   npc_nahom_battle_camera() : CreatureScript("npc_nahom_battle_camera") {}

    struct npc_nahom_battle_cameraAI : public ScriptedAI
    {
        npc_nahom_battle_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        enum npcId
        {
            NPC_ENTRY_CAMERA_CONTROLLER     = 45670
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_NAHOM_EVENT_FAIL  = 95231,
            SPELL_QUEST_CREDIT      = 91824
        };

        enum actionId
        {
            ACTION_INCREASE_DEADS   = 1,
            ACTION_EVENT_FAILED,
            ACTION_QUEST_COMPLETE
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            unitDead = 0;
            me->SetReactState(REACT_PASSIVE);
            me->AI()->TalkWithDelay(1000, 0, owner->GetGUID());
            me->AI()->TalkWithDelay(15000, 1, owner->GetGUID());
            me->AI()->TalkWithDelay(30000, 2, owner->GetGUID());
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INCREASE_DEADS:
                {
                    unitDead++;
                    if (unitDead >= 6)
                        DoAction(ACTION_EVENT_FAILED);
                    break;
                }
                case ACTION_EVENT_FAILED:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 400.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                        playerOwner->VisitNearbyObject(400.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case 45543:
                                    case 48462:
                                    case 48463:
                                    case 45679:
                                    case 45643:
                                    case 45586:
                                    case 48490:
                                    case 45660:
                                    case 45680:
                                    case 48466:
                                    case 48486:
                                    {
                                        (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        me->RemoveAllAuras();
                    }
                    break;
                }
                case ACTION_QUEST_COMPLETE:
                {
                    DoCast(me, SPELL_QUEST_CREDIT, true);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        uint8 unitDead;
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_nahom_battle_cameraAI(creature);
    }
};

class npc_ramkahen_ranger_captain : public CreatureScript
{
public:
    npc_ramkahen_ranger_captain() : CreatureScript("npc_ramkahen_ranger_captain") { }

    enum questId
    {
        QUEST_ENTRY_SALHET_GAMBIT   = 28486
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191
    };

    enum npcId
    {
        NPC_ENTRY_RAMKAHEN_RANGER   = 49242,
        NPC_ENTRY_RAMKAHEN_CAPTAIN  = 49244,
        NPC_ENTRY_NEFERSET_SCOUT    = 49281
    };

    enum questCredit
    {
        QUEST_CREDIT_GAMBIT     = 49250
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_SALHET_GAMBIT) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->SetPhaseMask(2, true);

            // Prepare Summons
            player->SummonCreature(NPC_ENTRY_RAMKAHEN_CAPTAIN, -10969.29f, -907.32f, 106.72f, 2.18f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_ENTRY_RAMKAHEN_RANGER, -10962.90f, -909.79f, 106.18f, 2.14f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_ENTRY_RAMKAHEN_RANGER, -10967.90f, -915.56f, 106.95f, 2.26f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_ENTRY_RAMKAHEN_RANGER, -10955.40f, -912.38f, 106.18f, 2.16f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            player->SummonCreature(NPC_ENTRY_RAMKAHEN_RANGER, -10966.09f, -922.06f, 107.55f, 2.35f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            return true;
        }
        return false;
    }

    struct npc_ramkahen_ranger_captainAI : public npc_escortAI
    {
        npc_ramkahen_ranger_captainAI(Creature* creature) : npc_escortAI(creature)
        {
            playerOwner = NULL;
            isSummoned = false;
        }

        enum actionId
        {
            ACTION_START_WP = 1
        };

        void Reset()
        {
            if (isSummoned == true)
            {
                if (!me->HasAura(SPELL_UNIQUE_PHASING))
                    me->AddAura(SPELL_UNIQUE_PHASING, me);
                InformRangersToFollow();
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            isSummoned = true;
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            DoAction(ACTION_START_WP);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(true, true, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                default:
                    break;
            }
        }

        void InformRangersToFollow()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(60.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_RAMKAHEN_RANGER)
                    {
                        if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            (*itr)->ToCreature()->AI()->DoAction(1);
                    }
                }
            }
        }

        void InformRangersToDespawn()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(60.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_RAMKAHEN_RANGER)
                    {
                        if ((*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            (*itr)->ToCreature()->DespawnOrUnsummon(5000);
                    }
                }
            }
        }

        void SpawnFirstAttackersWave()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11035.09f, -811.53f, 178.17f, 5.89f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11032.64f, -820.96f, 175.68f, 0.84f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11024.93f, -818.07f, 169.93f, 5.98f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11020.48f, -811.26f, 167.20f, 5.53f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            }
        }

        void SpawnSecondAttackersWave()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11051.38f, -878.94f, 191.94f, 0.28f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11042.59f, -884.48f, 188.76f, 0.49f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11042.05f, -867.41f, 189.22f, 5.46f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11039.55f, -894.45f, 188.02f, 1.92f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11055.67f, -896.75f, 192.91f, 1.08f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            }
        }

        void SpawnThirdAttackersWave()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11150.30f, -899.53f, 262.35f, 0.06f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11135.47f, -877.29f, 261.56f, 4.95f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11148.93f, -884.72f, 262.63f, 5.93f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_SCOUT, -11150.87f, -897.46f, 262.44f, 4.56f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 8: // First Attackers Wave
                {
                    SpawnFirstAttackersWave();
                    break;
                }
                case 12: // Second Attackers Wave
                {
                    SpawnSecondAttackersWave();
                    break;
                }
                case 23: // Third Attackers Wave
                {
                    SpawnThirdAttackersWave();
                    break;
                }
                case 24: // Final
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            playerOwner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GAMBIT);

                        playerOwner->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
                        playerOwner->SetPhaseMask(1, true);
                    }
                    InformRangersToDespawn();
                    me->DespawnOrUnsummon(5000);
                }
                default:
                    InformRangersToFollow();
                    break;
            }
        }

    protected:
        Unit* playerOwner;
        bool isSummoned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ramkahen_ranger_captainAI(creature);
    }
};

class npc_ramkahen_ranger : public CreatureScript
{
public:
   npc_ramkahen_ranger() : CreatureScript("npc_ramkahen_ranger") { }

    struct npc_ramkahen_rangerAI : public ScriptedAI
    {
        npc_ramkahen_rangerAI(Creature* creature) : ScriptedAI(creature)
        {
            isSummoned = false;
        }

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        enum actionId
        {
            ACTION_FOLLOW_AGAIN     = 1
        };

        enum npcId
        {
            NPC_ENTRY_RAMKAHEN_RANGER_CAPTAIN   = 49244
        };

        void Reset()
        {
            if (isSummoned == true)
            {
                if (!me->HasAura(SPELL_UNIQUE_PHASING))
                    me->AddAura(SPELL_UNIQUE_PHASING, me);
            }
        }

        void EnterEvadeMode()
        {
            if (isSummoned == true)
            {
                if (Creature* captain = me->FindNearestCreature(NPC_ENTRY_RAMKAHEN_RANGER_CAPTAIN, 800.0f, true))
                    me->GetMotionMaster()->MoveFollow(captain, 3.5f, frand(0, 2.5f));
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            isSummoned = true;
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetReactState(REACT_AGGRESSIVE);
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FOLLOW_AGAIN:
                {
                    if (isSummoned == true)
                    {
                        if (Creature* captain = me->FindNearestCreature(NPC_ENTRY_RAMKAHEN_RANGER_CAPTAIN, 200.0f, true))
                            me->GetMotionMaster()->MoveFollow(captain, 3.5f, frand(0, 2.5f));
                    }
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
        bool isSummoned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ramkahen_rangerAI(creature);
    }
};

class spell_mech_control_scrambler : public SpellScriptLoader
{
    public:
        spell_mech_control_scrambler() : SpellScriptLoader("spell_mech_control_scrambler") { }

        class spell_mech_control_scrambler_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mech_control_scrambler_SpellScript);

            enum Id
            {
                NPC_ENTRY_TWIZZLEFUX    = 46587
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* twizzleFux = caster->FindNearestCreature(NPC_ENTRY_TWIZZLEFUX, 20.0f, true))
                        return SPELL_CAST_OK;
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_mech_control_scrambler_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mech_control_scrambler_SpellScript();
        }
};

class spell_holographic_projector : public SpellScriptLoader
{
    public:
        spell_holographic_projector() : SpellScriptLoader("spell_holographic_projector") { }

        class spell_holographic_projector_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_holographic_projector_SpellScript);

            enum Id
            {
                NPC_ENTRY_CURSED_ENGINEER       = 46617,
                SPELL_SUMMON_HOLOGRAM           = 84349
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Creature* engineer = caster->FindNearestCreature(NPC_ENTRY_CURSED_ENGINEER, 15.0f, true))
                    {
                        if (caster->GetTypeId() != TYPEID_PLAYER)
                            return SPELL_FAILED_DONT_REPORT;

                        caster->CastSpell(caster, SPELL_SUMMON_HOLOGRAM);
                        caster->ToPlayer()->AddSpellCooldown(SPELL_SUMMON_HOLOGRAM, 0, time(NULL) + 8);
                        return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_holographic_projector_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_holographic_projector_SpellScript();
        }
};

class npc_holographic_image : public CreatureScript
{
public:
   npc_holographic_image() : CreatureScript("npc_holographic_image") { }

    struct npc_holographic_imageAI : public ScriptedAI
    {
        npc_holographic_imageAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_CURSED_ENGINEER   = 46617
        };

        enum actionId
        {
            ACTION_MORPH_TO_HOLO    = 1
        };

        enum morphId
        {
            HOLOGRAM_LASER_CANNON   = 35227,
            HOLOGRAM_EPICUS_MAXIMUS = 35225,
            HOLOGRAM_MECHANOSTRIDER = 35224,
            HOLOGRAM_ROCKET         = 35226,
            HOLOGRAM_DINOSAUR       = 35228,
            HOLOGRAM_UNDEAD         = 35229,
            HOLOGRAM_FEMALE         = 35223
        };

        enum eventId
        {
            EVENT_DISTRACT_ENGINEERS    = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            // Tomb of the Sun King
            if (me->GetAreaId() == 5698)
            {
                selectMorph = urand(1, 7);
                me->SetReactState(REACT_PASSIVE);
                me->setFaction(35);
                DoAction(ACTION_MORPH_TO_HOLO);
                events.ScheduleEvent(EVENT_DISTRACT_ENGINEERS, 1000);
            }
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MORPH_TO_HOLO:
                {
                    switch (selectMorph)
                    {
                        case 1:     // Female
                            me->SetDisplayId(HOLOGRAM_FEMALE);
                            me->HandleEmoteCommand(EMOTE_STATE_DANCE);
                            break;
                        case 2:     // Shark
                            me->SetDisplayId(HOLOGRAM_EPICUS_MAXIMUS);
                            break;
                        case 3:     // Dinosaur
                            me->SetDisplayId(HOLOGRAM_DINOSAUR);
                            break;
                        case 4:     // Undead
                            me->SetDisplayId(HOLOGRAM_UNDEAD);
                            me->HandleEmoteCommand(EMOTE_STATE_DANCE);
                            break;
                        case 5:     // Rocket
                            me->SetDisplayId(HOLOGRAM_ROCKET);
                            break;
                        case 6:     // Laser Cannon
                            me->SetDisplayId(HOLOGRAM_LASER_CANNON);
                            break;
                        case 7:     // Mechanostrider
                            me->SetDisplayId(HOLOGRAM_MECHANOSTRIDER);
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void CheckAndDistract()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 25.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(25.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_CURSED_ENGINEER)
                {
                    (*itr)->SetWalk(false);
                    (*itr)->setFaction(35);
                    (*itr)->CombatStop();
                    (*itr)->GetMotionMaster()->MoveFollow(me, frand(5.5f, 8.5f), frand(0, 4.5f));
                    if (roll_chance_f(25.0f))
                        (*itr)->ToCreature()->AI()->TalkWithDelay(urand(500,2500), 0);
                    (*itr)->ToCreature()->AI()->DoAction(1);
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
                    case EVENT_DISTRACT_ENGINEERS:
                    {
                        events.CancelEvent(EVENT_DISTRACT_ENGINEERS);
                        CheckAndDistract();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        uint8 selectMorph;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_holographic_imageAI(creature);
    }
};

class npc_cursed_engineer : public CreatureScript
{
public:
   npc_cursed_engineer() : CreatureScript("npc_cursed_engineer") { }

    struct npc_cursed_engineerAI : public ScriptedAI
    {
        npc_cursed_engineerAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum actionId
        {
            ACTION_RESTORE_FACTION  = 1
        };

        enum eventId
        {
            EVENT_RESTORE_FACTION   = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_RESTORE_FACTION:
                {
                    events.ScheduleEvent(EVENT_RESTORE_FACTION, 25000);
                    if (roll_chance_f(50.0f))
                        me->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                    else
                        me->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
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
                    case EVENT_RESTORE_FACTION:
                    {
                        events.CancelEvent(EVENT_RESTORE_FACTION);
                        me->GetMotionMaster()->MovementExpired(true);
                        me->SetWalk(true);
                        me->setFaction(16);
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
        return new npc_cursed_engineerAI(creature);
    }
};

class npc_wibson_mainframe : public CreatureScript
{
public:
    npc_wibson_mainframe() : CreatureScript("npc_wibson_mainframe") { }

    enum questId
    {
        QUEST_ENTRY_HACKING_THE_WIBSON  = 27778
    };

    enum spellId
    {
        SPELL_HACKING_VISUAL    = 87032,
        SPELL_HACKING_ANIM      = 87033,
        SPELL_HACKING_FX_01     = 87043,
        SPELL_HACKING_FX_02     = 87048,
        SPELL_HACKING_FX_03     = 87052,
        SPELL_CANCEL_HACKING    = 87072
    };

    enum questCredit
    {
        QUEST_CREDIT_WIBSON     = 47028
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_HACKING_THE_WIBSON) == QUEST_STATUS_INCOMPLETE)
        {
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            player->HandleEmoteCommand(EMOTE_STATE_WORK_MINING);
            player->CastSpell(player, SPELL_HACKING_VISUAL, true);
            player->EnterVehicle(creature, 0);
            creature->CastWithDelay(6000, creature, SPELL_HACKING_FX_01, true);
            creature->CastWithDelay(12000, creature, SPELL_HACKING_FX_02, true);
            creature->CastWithDelay(18000, creature, SPELL_HACKING_FX_03, true);
            return true;
        }
        return true;
    }

    struct npc_wibson_mainframeAI : public ScriptedAI
    {
        npc_wibson_mainframeAI(Creature* creature) : ScriptedAI(creature) {}

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_HACKING_FX_03:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (passenger->GetTypeId() == TYPEID_PLAYER)
                        {
                            passenger->HandleEmoteCommand(EMOTE_STATE_STAND);
                            passenger->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WIBSON);
                            passenger->CastSpell(passenger, SPELL_CANCEL_HACKING, true);
                        }
                    }
                    me->GetVehicleKit()->RemoveAllPassengers();
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wibson_mainframeAI(creature);
    }
};

class spell_salhet_summon_camera : public SpellScriptLoader
{
    public:
        spell_salhet_summon_camera() : SpellScriptLoader("spell_salhet_summon_camera") { }

        class spell_salhet_summon_camera_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_salhet_summon_camera_SpellScript);

            enum Id
            {
                NPC_ENTRY_SALHET_LIONS  = 48168,
                SPELL_UNIQUE_PHASING    = 60191,
                SPELL_LION_CONTROLLER   = 89585
            };

            void HandlePhasing()
            {
                if (Unit* caster = GetCaster())
                {
                    caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                    caster->SetPhaseMask(2, true);
                    caster->CastSpell(caster, SPELL_LION_CONTROLLER, true);
                    caster->SummonCreature(NPC_ENTRY_SALHET_LIONS, -10631.00f, -1055.32f, 135.99f, 1.51f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_SALHET_LIONS, -10620.50f, -1053.64f, 137.01f, 1.44f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_ENTRY_SALHET_LIONS, -10626.29f, -1047.46f, 136.01f, 1.51f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_salhet_summon_camera_SpellScript::HandlePhasing);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_salhet_summon_camera_SpellScript();
        }
};

class npc_lions_controller : public CreatureScript
{
public:
   npc_lions_controller() : CreatureScript("npc_lions_controller") { }

    struct npc_lions_controllerAI : public ScriptedAI
    {
        npc_lions_controllerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_SALHET_LION   = 48168
        };

        enum eventId
        {
            EVENT_COORDINATE_LIONS  = 1
        };

        enum actionId
        {
            ACTION_REGROUP  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_REGROUP:
                {
                    events.ScheduleEvent(EVENT_COORDINATE_LIONS, 100);
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
                    case EVENT_COORDINATE_LIONS:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            events.CancelEvent(EVENT_COORDINATE_LIONS);
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->GetEntry() == NPC_ENTRY_SALHET_LION &&
                                    (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    (*itr)->SetWalk(false);
                                    (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                                    (*itr)->GetMotionMaster()->MoveFollow(me, frand(0.0f, 3.0f), frand(0, 4.5f));
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lions_controllerAI(creature);
    }
};

class spell_lions_move : public SpellScriptLoader
{
    public:
        spell_lions_move() : SpellScriptLoader("spell_lions_move") { }

        class spell_lions_move_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lions_move_SpellScript);

            enum Id
            {
                NPC_ENTRY_LIONS_CONTROLLER  = 48198
            };

            void HandleTeleportController()
            {
                WorldLocation const* const position = GetExplTargetDest();

                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 150.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(150.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == caster->GetCharmerOrOwner())
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_LIONS_CONTROLLER)
                            {
                                (*itr)->NearTeleportTo(*position);
                                (*itr)->ToCreature()->AI()->DoAction(1);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_lions_move_SpellScript::HandleTeleportController);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lions_move_SpellScript();
        }
};

class npc_lions_camera : public CreatureScript
{
public:
   npc_lions_camera() : CreatureScript("npc_lions_camera") {}

    struct npc_lions_cameraAI : public ScriptedAI
    {
        npc_lions_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum npcId
        {
            NPC_ENTRY_CAMERA_CONTROLLER     = 48171,
            NPC_ENTRY_BLOODSNARL_SCAVENGER  = 48209
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_QUEST_CREDIT      = 89608
        };

        enum actionId
        {
            ACTION_INCREASE_DEADS   = 1,
            ACTION_EVENT_FAILED,
            ACTION_QUEST_COMPLETE
        };

        enum eventId
        {
            EVENT_SUMMON_LEFT_WAVE     = 1,
            EVENT_SUMMON_RIGHT_WAVE,
            EVENT_SUMMON_BOTH_WAVES,
            EVENT_REMOVE_ALL_EVENTS
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            unitDead = 0;
            me->SetReactState(REACT_PASSIVE);
            TalkWithDelay(1000, 0, owner->GetGUID());
            TalkWithDelay(12000, 1, owner->GetGUID());
            TalkWithDelay(32500, 2, owner->GetGUID());
            TalkWithDelay(51000, 3, owner->GetGUID());
            events.ScheduleEvent(EVENT_SUMMON_LEFT_WAVE, 12500);
            events.ScheduleEvent(EVENT_SUMMON_RIGHT_WAVE, 32000);
            events.ScheduleEvent(EVENT_SUMMON_BOTH_WAVES, 51500);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INCREASE_DEADS:
                {
                    unitDead++;
                    if (unitDead >= 3)
                        DoAction(ACTION_EVENT_FAILED);
                    break;
                }
                case ACTION_EVENT_FAILED:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 400.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                        playerOwner->VisitNearbyObject(400.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case 48168: // Lions
                                    case 48209: // Hyenas
                                    {
                                        (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        me->RemoveAllAuras();
                    }
                    break;
                }
                case ACTION_QUEST_COMPLETE:
                {
                    DoCast(me, SPELL_QUEST_CREDIT, true);
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
                    case EVENT_SUMMON_LEFT_WAVE:
                    {
                        events.CancelEvent(EVENT_SUMMON_LEFT_WAVE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            // Left Wave
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10675.50f, -1047.35f, 125.66f, 6.19f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10671.73f, -1038.42f, 127.11f, 5.46f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10661.25f, -1041.19f, 128.12f, 4.95f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10667.59f, -1066.49f, 132.59f, 0.30f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10666.03f, -1058.95f, 132.73f, 6.27f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        break;
                    }
                    case EVENT_SUMMON_RIGHT_WAVE:
                    {
                        events.CancelEvent(EVENT_SUMMON_RIGHT_WAVE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            // Right Wave
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10632.02f, -1005.39f, 129.38f, 4.81f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10638.97f, -1011.27f, 130.24f, 5.20f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10613.79f, -1025.08f, 130.72f, 4.02f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10600.16f, -1029.70f, 129.53f, 3.85f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10591.09f, -1036.02f, 130.81f, 3.61f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        break;
                    }
                    case EVENT_SUMMON_BOTH_WAVES:
                    {
                        events.CancelEvent(EVENT_SUMMON_BOTH_WAVES);
                        events.CancelEvent(EVENT_SUMMON_LEFT_WAVE);
                        events.RescheduleEvent(EVENT_SUMMON_BOTH_WAVES, 30000);
                        events.ScheduleEvent(EVENT_REMOVE_ALL_EVENTS, 31000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            // Left Wave
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10675.50f, -1047.35f, 125.66f, 6.19f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10671.73f, -1038.42f, 127.11f, 5.46f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10661.25f, -1041.19f, 128.12f, 4.95f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10667.59f, -1066.49f, 132.59f, 0.30f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10666.03f, -1058.95f, 132.73f, 6.27f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));

                            // Right Wave
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10632.02f, -1005.39f, 129.38f, 4.81f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10638.97f, -1011.27f, 130.24f, 5.20f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10613.79f, -1025.08f, 130.72f, 4.02f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10600.16f, -1029.70f, 129.53f, 3.85f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_ENTRY_BLOODSNARL_SCAVENGER, -10591.09f, -1036.02f, 130.81f, 3.61f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        break;
                    }
                    case EVENT_REMOVE_ALL_EVENTS:
                    {
                        events.Reset();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        uint8 unitDead;
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lions_cameraAI(creature);
    }
};

class npc_lions_counter : public CreatureScript
{
public:
   npc_lions_counter() : CreatureScript("npc_lions_counter") { }

    struct npc_lions_counterAI : public ScriptedAI
    {
        npc_lions_counterAI(Creature* creature) : ScriptedAI(creature) {}

        enum npcId
        {
            NPC_ENTRY_CAMERA_CONTROLLER     = 48171,
            NPC_ENTRY_SALHET_LION           = 46168
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void JustDied(Unit* /*who*/)
        {
            if (me->GetEntry() == NPC_ENTRY_SALHET_LION)
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 400.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                playerOwner->VisitNearbyObject(400.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        if ((*itr)->GetEntry() == NPC_ENTRY_CAMERA_CONTROLLER)
                            (*itr)->ToCreature()->AI()->DoAction(1);
                    }
                }
            }
            me->DespawnOrUnsummon(5000);
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetReactState(REACT_AGGRESSIVE);
        };

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lions_counterAI(creature);
    }
};

class npc_bloodsnarl_scavenger : public CreatureScript
{
public:
   npc_bloodsnarl_scavenger() : CreatureScript("npc_bloodsnarl_scavenger") { }

    struct npc_bloodsnarl_scavengerAI : public ScriptedAI
    {
        npc_bloodsnarl_scavengerAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum pointId
        {
            POINT_TO_UP     = 1
        };

        enum npcId
        {
            NPC_ENTRY_LIONS_CAMERA      = 48171,
            NPC_ENTRY_SALHET_LION       = 48168
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void EnterEvadeMode()
        {
            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->MovePoint(POINT_TO_UP, -10626.41f, -1040.76f, 134.51f);
        }

        void JustDied(Unit* /*who*/)
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 150.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                playerOwner->VisitNearbyObject(150.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT  && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        if ((*itr)->GetEntry() == NPC_ENTRY_LIONS_CAMERA)
                            (*itr)->ToCreature()->AI()->DoAction(3);
                    }
                }
            }
            me->DespawnOrUnsummon(5000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_UP:
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, false))
                        me->Attack(target, true);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bloodsnarl_scavengerAI(creature);
    }
};

class npc_fusion_core_summoned : public CreatureScript
{
public:
   npc_fusion_core_summoned() : CreatureScript("npc_fusion_core_summoned") {}

    struct npc_fusion_core_summonedAI : public ScriptedAI
    {
        npc_fusion_core_summonedAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_GIVE_CREDIT  = 1
        };

        enum spellId
        {
            SPELL_FUSION_CORE_FIRE  = 86427
        };

        enum eventId
        {
            EVENT_SWITCH_SEAT   = 1,
            EVENT_APPLY_AURA,
            EVENT_FUSION_FIRE,
            EVENT_SUMMON_PIVOT,
            EVENT_FIRE_SOUND
        };

        enum animkitId
        {
            ANIMKIT_ID_01   = 981,
            ANIMKIT_ID_02   = 982
        };

        enum pointId
        {
            POINT_GROUND    = 1
        };

        enum npcId
        {
            NPC_ENTRY_SPHERE_PIVOT  = 46360
        };

        enum creditId
        {
            QUEST_CREDIT_GNOMEBLITERATION   = 46394
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            events.ScheduleEvent(EVENT_APPLY_AURA, 100);
            events.ScheduleEvent(EVENT_FUSION_FIRE, 100);
            events.ScheduleEvent(EVENT_FIRE_SOUND, 2000);
            me->PlayDirectSound(22135);
            me->SetHover(true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_GIVE_CREDIT:
                {
                    if (me->GetVehicleKit())
                    {
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
                        {
                            if (passenger && passenger->GetTypeId() == TYPEID_PLAYER)
                                passenger->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GNOMEBLITERATION);
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
                    case EVENT_FIRE_SOUND:
                    {
                        events.RescheduleEvent(EVENT_FIRE_SOUND, 4000);
                        me->PlayDirectSound(22457);
                        break;
                    }
                    case EVENT_SWITCH_SEAT:
                    {
                        events.CancelEvent(EVENT_SWITCH_SEAT);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            passenger->ChangeSeat(1, true);
                        events.ScheduleEvent(EVENT_SUMMON_PIVOT, 1000);
                        break;
                    }
                    case EVENT_APPLY_AURA:
                    {
                        events.CancelEvent(EVENT_APPLY_AURA);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10694.85f, -2317.87f, 93.06f, 20.0f, 45.0f, POINT_GROUND);
                        events.ScheduleEvent(EVENT_SWITCH_SEAT, 2500);
                        break;
                    }
                    case EVENT_FUSION_FIRE:
                    {
                        events.RescheduleEvent(EVENT_FUSION_FIRE, 200);
                        DoCast(me, SPELL_FUSION_CORE_FIRE, true);
                        break;
                    }
                    case EVENT_SUMMON_PIVOT:
                    {
                        events.CancelEvent(EVENT_SUMMON_PIVOT);
                        me->SummonCreature(NPC_ENTRY_SPHERE_PIVOT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_GROUND:
                {
                    if (Unit* owner = me->GetCharmerOrOwner())
                    {
                        if (owner->GetTypeId() == TYPEID_PLAYER)
                            owner->ToPlayer()->SetClientControl(me, 1);
                    }
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fusion_core_summonedAI(creature);
    }
};

class spell_summon_fusion_core : public SpellScriptLoader
{
    public:
        spell_summon_fusion_core() : SpellScriptLoader("spell_summon_fusion_core") { }

        class spell_summon_fusion_core_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_fusion_core_SpellScript);

            enum Id
            {
                NPC_ENTRY_CRAZED_GNOME  = 46384
            };

            void HandlePhasing()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->SetPhaseMask(182, true);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_summon_fusion_core_SpellScript::HandlePhasing);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_fusion_core_SpellScript();
        }
};

class npc_crazed_gnome : public CreatureScript
{
public:
   npc_crazed_gnome() : CreatureScript("npc_crazed_gnome") {}

    struct npc_crazed_gnomeAI : public ScriptedAI
    {
        npc_crazed_gnomeAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_CHECK_PIVOT   = 1,
            EVENT_KILL_SELF
        };

        enum npcId
        {
            NPC_ENTRY_SPHERE_PIVOT  = 46360
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_CHECK_PIVOT, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_PIVOT:
                    {
                        if (me->GetVehicleBase())
                        {
                            events.CancelEvent(EVENT_CHECK_PIVOT);
                            break;
                        }

                        events.RescheduleEvent(EVENT_CHECK_PIVOT, 1000);
                        if (Creature* pivot = me->FindNearestCreature(NPC_ENTRY_SPHERE_PIVOT, 8.0f, true))
                        {
                            me->EnterVehicle(pivot, urand(0, 8));
                            pivot->AI()->DoAction(1);
                            if (roll_chance_f(75.0f))
                                me->PlayDirectSound(22458);
                            me->PlayDirectSound(22456);
                            events.ScheduleEvent(EVENT_KILL_SELF, 3000);
                        }
                        break;
                    }
                    case EVENT_KILL_SELF:
                    {
                        me->Kill(me, false);
                        events.CancelEvent(EVENT_KILL_SELF);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crazed_gnomeAI(creature);
    }
};

class npc_fusion_core_pivot : public CreatureScript
{
public:
   npc_fusion_core_pivot() : CreatureScript("npc_fusion_core_pivot") {}

    struct npc_fusion_core_pivotAI : public ScriptedAI
    {
        npc_fusion_core_pivotAI(Creature* creature) : ScriptedAI(creature) {unitOwner = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_HANDLE_CREDIT    = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            me->EnterVehicle(owner, 0);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            unitOwner = owner;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_HANDLE_CREDIT:
                {
                    if (unitOwner && unitOwner != NULL && unitOwner->IsInWorld())
                    {
                        if (unitOwner->ToCreature())
                            unitOwner->ToCreature()->AI()->DoAction(1);
                    }
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* unitOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fusion_core_pivotAI(creature);
    }
};

class npc_dark_pharaoh_tekahn : public CreatureScript
{
public:
   npc_dark_pharaoh_tekahn() : CreatureScript("npc_dark_pharaoh_tekahn") { }

    struct npc_dark_pharaoh_tekahnAI : public ScriptedAI
    {
        npc_dark_pharaoh_tekahnAI(Creature* creature) : ScriptedAI(creature)
        {
            actionInvoker = NULL;
            playerCamera = NULL;
        }

        EventMap events;

        enum npcId
        {
            NPC_PYRAMID_WATCHER     = 47810,
            NPC_RAMKAHEN_CHAMPION   = 47868,
            NPC_KING_PHAORIS        = 47867
        };

        enum eventId
        {
            EVENT_CAST_SHADOW_BOLT      = 1,
            EVENT_CAST_PACT_OF_DARKNESS,
            EVENT_CAST_DARK_RUNE,
            EVENT_UNLEASH_WATCHERS
        };

        enum spellId
        {
            SPELL_SHADOW_BOLT       = 88886,
            SPELL_PACT_OF_DARKNESS  = 88883,
            SPELL_DARK_RUNE         = 88887,
            SPELL_NEFERSET_CAMERA   = 91956,
            SPELL_FADE_TO_BLACK     = 89404
        };

        enum questId
        {
            QUEST_THE_FALL_OF_NEFERSET_CITY     = 28520
        };

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* who)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            actionInvoker = who;
            events.ScheduleEvent(EVENT_CAST_SHADOW_BOLT, 500);
            events.ScheduleEvent(EVENT_CAST_PACT_OF_DARKNESS, 3600);
            events.ScheduleEvent(EVENT_CAST_DARK_RUNE, 6800);
            events.ScheduleEvent(EVENT_UNLEASH_WATCHERS, 12500);
            Talk(0);
        }

        void JustDied(Unit* /*who*/)
        {
            CheckPlayersForCamera();
            KillWatchers();
            RemoveEventCreatures();
        }

        void CallForWatchersHelp()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 85.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(85.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->GetEntry() == NPC_PYRAMID_WATCHER)
                        (*itr)->ToCreature()->AI()->DoAction(1);
                }
            }
        }

        void CallPhaorisAndChampions()
        {
            me->SummonCreature(NPC_RAMKAHEN_CHAMPION, -11414.40f, -752.53f, 136.59f, 5.57f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            me->SummonCreature(NPC_RAMKAHEN_CHAMPION, -11426.59f, -752.54f, 136.57f, 4.98f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            me->SummonCreature(NPC_KING_PHAORIS, -11426.59f, -752.54f, 136.57f, 4.98f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
        }

        void CheckPlayersForCamera()
        {
            std::list<Player*> targets;
            Trinity::AnyPlayerInObjectRangeCheck u_check(me, 100.0f);
            Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            for (std::list<Player*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr))
                {
                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_FALL_OF_NEFERSET_CITY) == QUEST_STATUS_INCOMPLETE)
                        (*itr)->ToPlayer()->CompleteQuest(QUEST_THE_FALL_OF_NEFERSET_CITY);

                    if ((*itr)->ToPlayer()->GetQuestStatus(QUEST_THE_FALL_OF_NEFERSET_CITY) == QUEST_STATUS_COMPLETE)
                    {
                        (*itr)->SetPhaseMask(180, true);
                        (*itr)->CastSpell((*itr), SPELL_NEFERSET_CAMERA, true);
                        (*itr)->NearTeleportTo(-10709.50f, -758.44f, 91.76f, 3.06f);
                    }
                }
            }
        }

        void KillWatchers()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 85.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(85.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->GetEntry() == NPC_PYRAMID_WATCHER)
                        (*itr)->Kill((*itr), false);
                }
            }
        }

        void RemoveEventCreatures()
        {
            std::list<Unit*> targets;
            Trinity::AnyUnitInObjectRangeCheck u_check(me, 85.0f);
            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(85.0f, searcher);
            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT)
                {
                    if ((*itr)->GetEntry() == NPC_RAMKAHEN_CHAMPION || (*itr)->GetEntry() == NPC_KING_PHAORIS)
                        (*itr)->ToCreature()->DespawnOrUnsummon(1);
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
                    case EVENT_CAST_SHADOW_BOLT:
                    {
                        RESCHEDULE_IF_CASTING
                        if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 50.0f, true))
                            DoCast(target, SPELL_SHADOW_BOLT);
                        events.RescheduleEvent(EVENT_CAST_SHADOW_BOLT, 3100);
                        break;
                    }
                    case EVENT_CAST_PACT_OF_DARKNESS:
                    {
                        RESCHEDULE_IF_CASTING
                        if (Unit* target = me->getVictim())
                        {
                            if (me->IsWithinCombatRange(target, 7.0f))
                                DoCast(SPELL_PACT_OF_DARKNESS);
                        }
                        events.RescheduleEvent(EVENT_CAST_PACT_OF_DARKNESS, 5000);
                        break;
                    }
                    case EVENT_CAST_DARK_RUNE:
                    {
                        RESCHEDULE_IF_CASTING
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, false))
                            DoCast(target, SPELL_DARK_RUNE);
                        events.RescheduleEvent(EVENT_CAST_DARK_RUNE, 6500);
                        break;
                    }
                    case EVENT_UNLEASH_WATCHERS:
                    {
                        CallForWatchersHelp();
                        CallPhaorisAndChampions();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* actionInvoker;
        Player* playerCamera;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_pharaoh_tekahnAI(creature);
    }
};

class npc_pyramid_watcher : public CreatureScript
{
public:
   npc_pyramid_watcher() : CreatureScript("npc_pyramid_watcher") { }

    struct npc_pyramid_watcherAI : public ScriptedAI
    {
        npc_pyramid_watcherAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        enum actionId
        {
            ACTION_ENTER_COMBAT     = 1
        };

        enum eventId
        {
            EVENT_CAST_BURNING_GAZE         = 1,
            EVENT_CAST_BLAZING_ERUPTION,
            EVENT_CAST_BURNING_GAZE_SUMMON
        };

        enum spellId
        {
            SPELL_BURNING_GAZE_SUMMON       = 89001,
            SPELL_BURNING_GAZE              = 89013,
            SPELL_BLAZING_ERUPTION          = 87753,
            SPELL_STATUE                    = 88639
        };

        enum npcId
        {
            NPC_BURNING_GAZE    = 47852
        };

        void Reset()
        {
            events.Reset();
            if (me->HasAura(SPELL_STATUE))
                me->AddAura(SPELL_STATUE, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENTER_COMBAT:
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                    me->RemoveAurasDueToSpell(SPELL_STATUE);
                    events.ScheduleEvent(EVENT_CAST_BLAZING_ERUPTION, urand(1000, 2000));
                    events.ScheduleEvent(EVENT_CAST_BURNING_GAZE_SUMMON, 5000);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_BLAZING_ERUPTION:
                    {
                        RESCHEDULE_IF_CASTING
                        DoCast(SPELL_BLAZING_ERUPTION);
                        events.RescheduleEvent(EVENT_CAST_BLAZING_ERUPTION, urand(8500, 12500));
                        break;
                    }
                    case EVENT_CAST_BURNING_GAZE_SUMMON:
                    {
                        RESCHEDULE_IF_CASTING
                        events.RescheduleEvent(EVENT_CAST_BURNING_GAZE_SUMMON, urand(12000, 18000));
                        me->CastStop();
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 75.0f, false))
                            DoCast(target, SPELL_BURNING_GAZE_SUMMON);
                        events.ScheduleEvent(EVENT_CAST_BURNING_GAZE, 500);
                        break;
                    }
                    case EVENT_CAST_BURNING_GAZE:
                    {
                        RESCHEDULE_IF_CASTING
                        events.CancelEvent(EVENT_CAST_BURNING_GAZE);
                        if (Creature* burningGaze = me->FindNearestCreature(NPC_BURNING_GAZE, 200.0f, true))
                        {
                            burningGaze->SetInCombatWith(me);
                            DoCast(burningGaze, SPELL_BURNING_GAZE);
                        }
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pyramid_watcherAI(creature);
    }
};

class npc_ramkahen_champion_tekahn : public CreatureScript
{
public:
   npc_ramkahen_champion_tekahn() : CreatureScript("npc_ramkahen_champion_tekahn") { }

    struct npc_ramkahen_champion_tekahnAI : public ScriptedAI
    {
        npc_ramkahen_champion_tekahnAI(Creature* creature) : ScriptedAI(creature) { }

        enum npcId
        {
            NPC_PYRAMID_WATCHER     = 47810
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            if (Creature* pyramidWatcher = me->FindNearestCreature(NPC_PYRAMID_WATCHER, 100.0f, true))
                AttackStart(pyramidWatcher);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ramkahen_champion_tekahnAI(creature);
    }
};

class npc_king_phaoris_tekahn : public CreatureScript
{
public:
   npc_king_phaoris_tekahn() : CreatureScript("npc_king_phaoris_tekahn") { }

    struct npc_king_phaoris_tekahnAI : public ScriptedAI
    {
        npc_king_phaoris_tekahnAI(Creature* creature) : ScriptedAI(creature) { }

        enum npcId
        {
            NPC_DARK_PHARAOH_TEKAHN = 47753
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            if (Creature* tekahn = me->FindNearestCreature(NPC_DARK_PHARAOH_TEKAHN, 100.0f, true))
                AttackStart(tekahn);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_phaoris_tekahnAI(creature);
    }
};

class npc_fall_of_neferset_camera : public CreatureScript
{
public:
   npc_fall_of_neferset_camera() : CreatureScript("npc_fall_of_neferset_camera") { }

    struct npc_fall_of_neferset_cameraAI : public ScriptedAI
    {
        npc_fall_of_neferset_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_PREPARE_SUMMONS,
            EVENT_ENABLE_KAMSES,
            EVENT_CHARGE_TO_POINT,
            EVENT_MOVE_ME,
            EVENT_KILL_COLOSSUS
        };

        enum npcId
        {
            NPC_HIGH_COMMANDER_KAMSES   = 49183,
            NPC_IMMORTAL_COLOSSUS       = 48548,
            NPC_RAMKAHEN_LEGIONNAIRE    = 48512,
            NPC_RAMKAHEN_MARKSMAN       = 48514
        };

        enum pointId
        {
            POINT_TO_CHARGE     = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_CHARGE:
                {
                    if (me->GetVehicleKit())
                        me->GetVehicleKit()->RemoveAllPassengers();
                    me->DespawnOrUnsummon(1000);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        events.ScheduleEvent(EVENT_PREPARE_SUMMONS, 100);
                        break;
                    }
                    case EVENT_PREPARE_SUMMONS:
                    {
                        events.CancelEvent(EVENT_PREPARE_SUMMONS);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->SummonCreature(NPC_HIGH_COMMANDER_KAMSES, -10729.54f, -762.54f, 87.89f, 2.98f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_IMMORTAL_COLOSSUS, -10787.54f, -747.59f, 86.78f, 6.15f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_IMMORTAL_COLOSSUS, -10796.20f, -770.73f, 89.17f, 0.04f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_IMMORTAL_COLOSSUS, -10795.23f, -791.09f, 88.17f, 0.16f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10726.53f, -773.23f, 87.15f, 3.05f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10719.80f, -772.06f, 86.62f, 3.05f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10724.26f, -768.88f, 87.33f, 3.00f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10716.24f, -767.90f, 86.84f, 2.92f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10722.28f, -763.34f, 87.76f, 3.00f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10712.55f, -764.96f, 87.02f, 3.04f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10714.85f, -761.58f, 87.66f, 2.92f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10722.84f, -758.76f, 88.06f, 3.00f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10720.88f, -753.88f, 88.19f, 2.92f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_LEGIONNAIRE, -10713.51f, -755.50f, 88.29f, 2.92f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10706.06f, -775.98f, 86.06f, 3.11f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10718.00f, -776.29f, 86.11f, 3.08f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10712.47f, -770.74f, 86.19f, 3.06f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10705.34f, -770.20f, 86.28f, 3.54f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10703.96f, -767.13f, 86.57f, 3.16f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10709.74f, -762.44f, 87.21f, 3.06f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10704.06f, -762.68f, 86.89f, 3.16f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10709.45f, -758.54f, 87.74f, 3.06f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10704.29f, -757.21f, 87.44f, 3.27f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10707.48f, -753.61f, 88.18f, 3.06f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_RAMKAHEN_MARKSMAN, -10711.91f, -751.49f, 88.45f, 3.06f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        events.ScheduleEvent(EVENT_ENABLE_KAMSES, 5000);
                        break;
                    }
                    case EVENT_ENABLE_KAMSES:
                    {
                        events.CancelEvent(EVENT_ENABLE_KAMSES);
                        events.ScheduleEvent(EVENT_KILL_COLOSSUS, urand(4500, 7000));
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToCreature() && (*itr)->ToTempSummon() &&
                                    (*itr)->ToTempSummon()->GetSummoner())
                                {
                                    if ((*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                    {
                                        if ((*itr)->GetEntry() == NPC_HIGH_COMMANDER_KAMSES)
                                        {
                                            (*itr)->ToCreature()->AI()->Talk(0, playerOwner->GetGUID());
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(7000, 1, playerOwner->GetGUID());
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_KILL_COLOSSUS:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToCreature() && (*itr)->ToTempSummon() &&
                                    (*itr)->ToTempSummon()->GetSummoner())
                                {
                                    if ((*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                    {
                                        if ((*itr)->GetEntry() == NPC_IMMORTAL_COLOSSUS)
                                            (*itr)->Kill((*itr), false);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_CHARGE_TO_POINT, 2500);
                        break;
                    }
                    case EVENT_CHARGE_TO_POINT:
                    {
                        events.CancelEvent(EVENT_CHARGE_TO_POINT);
                        events.ScheduleEvent(EVENT_MOVE_ME, 2000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->GetTypeId() == TYPEID_UNIT && (*itr)->ToCreature() && (*itr)->ToTempSummon() &&
                                    (*itr)->ToTempSummon()->GetSummoner())
                                {
                                    if ((*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                    {
                                        if ((*itr)->GetEntry() == NPC_RAMKAHEN_LEGIONNAIRE)
                                        {
                                            (*itr)->SetWalk(false);
                                            (*itr)->GetMotionMaster()->MovePoint(POINT_TO_CHARGE, -10832.35f, -751.32f, 88.68f);
                                            (*itr)->ToCreature()->DespawnOrUnsummon(5000);
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_MOVE_ME:
                    {
                        events.CancelEvent(EVENT_MOVE_ME);
                        me->GetMotionMaster()->MoveJump(-10830.02f, -751.23f, 94.23f, 14.5f, 14.5f, POINT_TO_CHARGE);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fall_of_neferset_cameraAI(creature);
    }
};

class spell_summon_camera_explosionation : public SpellScriptLoader
{
    public:
        spell_summon_camera_explosionation() : SpellScriptLoader("spell_summon_camera_explosionation") { }

        class spell_summon_camera_explosionation_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_camera_explosionation_SpellScript);

            enum Id
            {
                NPC_HARRISON_JONES  = 44860,
                NPC_LADY_HUMPS      = 45121,
                NPC_HARRISON_MULE   = 45140,
                NPC_CASTER_CLONE    = 45144,
                NPC_BRAZIER_VEHICLE = 45135,
                NPC_BRAZIER         = 45136,
                NPC_POWDER_KEG      = 45158,
                NPC_KEG_VEHICLE     = 45159,
                NPC_EXPLOSION_DUMMY = 28960
            };

            enum spellId
            {
                SPELL_UNIQUE_PHASING    = 60191,
                SPELL_SUMMON_PYGMY      = 84291,
                SPELL_SUMMON_CLONE      = 84285,
                SPELL_CLONE_AURA        = 84286
            };

            enum gobjectId
            {
                GO_CHEST_00     = 205245,
                GO_CHEST_01     = 205244
            };

            enum questId
            {
                QUEST_ENTRY_PREMATURE_EXPLOSIONATION    = 27141
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_ENTRY_PREMATURE_EXPLOSIONATION) == QUEST_STATUS_INCOMPLETE)
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_DONT_REPORT;
            }

            void HandlePhasing()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (caster->ToPlayer()->GetQuestStatus(QUEST_ENTRY_PREMATURE_EXPLOSIONATION) != QUEST_STATUS_INCOMPLETE)
                        return;

                    caster->SetPhaseMask(4, true);
                    if (!caster->HasAura(SPELL_UNIQUE_PHASING))
                        caster->AddAura(SPELL_UNIQUE_PHASING, caster);

                    // Prepare Summons
                    caster->SummonCreature(NPC_HARRISON_JONES, -8951.19f, -1545.78f, 94.67f, 1.01f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_HARRISON_MULE, -8945.92f, -1540.59f, 94.67f, 4.43f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_LADY_HUMPS, -8953.90f, -1539.61f, 94.67f, 3.75f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_CASTER_CLONE, -8947.66f, -1544.71f, 94.67f, 0.97f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_BRAZIER, -8946.16f, -1544.67f, 94.45f, 3.17f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_BRAZIER_VEHICLE, -8946.1f, -1544.62f, 94.45f, 3.17f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_POWDER_KEG, -8946.15f, -1546.69f, 94.45f, 1.57f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_KEG_VEHICLE, -8945.83f, -1547.95f, 94.45f, 1.57f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonCreature(NPC_EXPLOSION_DUMMY, -8950.98f, -1550.10f, 94.45f, 1.49f, TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    caster->SummonGameObject(GO_CHEST_00, -8957.11f, -1546.67f, 94.48f, -0.34f, 0, 0, -0.173648f, 0.984808f, 120);
                    caster->SummonGameObject(GO_CHEST_01, -8956.47f, -1553.28f, 94.48f, 0.65f, 0, 0, 0.321439f, 0.94693f, 120);

                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 60.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(60.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_EXPLOSION_DUMMY && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == caster)
                        {
                            if ((*itr)->HasAura(SPELL_UNIQUE_PHASING))
                                (*itr)->AddAura(SPELL_UNIQUE_PHASING, (*itr));
                            (*itr)->SetObjectScale(13.0f);
                        }
                    }

                    if (GameObject* chest00 = caster->FindNearestGameObject(GO_CHEST_00, 50.0f))
                        chest00->SetGoState(GO_STATE_ACTIVE);
                    if (GameObject* chest01 = caster->FindNearestGameObject(GO_CHEST_01, 50.0f))
                        chest01->SetGoState(GO_STATE_ACTIVE);

                    caster->CastWithDelay(1500, caster, SPELL_SUMMON_PYGMY, true);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_summon_camera_explosionation_SpellScript::CheckCast);
                BeforeCast += SpellCastFn(spell_summon_camera_explosionation_SpellScript::HandlePhasing);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_summon_camera_explosionation_SpellScript();
        }
};

class npc_camera_explosionation : public CreatureScript
{
public:
   npc_camera_explosionation() : CreatureScript("npc_camera_explosionation") { }

    struct npc_camera_explosionationAI : public ScriptedAI
    {
        npc_camera_explosionationAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER  = 1,
            EVENT_CHANGE_SEAT,
            EVENT_JUMP_TO_VISUAL,
            EVENT_SEAT_EXPLOSION,
            EVENT_FINAL_SEAT
        };

        enum npcId
        {
            NPC_BRAZIER     = 45136
        };

        enum pointId
        {
            POINT_KEG   = 1,
            POINT_END
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_CAMERA_CHANNELING = 88552
        };

        enum actionId
        {
            ACTION_CAMERA_TO_EXPLOSION  = 1
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 500);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CAMERA_TO_EXPLOSION:
                {
                    events.ScheduleEvent(EVENT_SEAT_EXPLOSION, 500);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        events.ScheduleEvent(EVENT_CHANGE_SEAT, 11000);
                        break;
                    }
                    case EVENT_CHANGE_SEAT:
                    {
                        events.CancelEvent(EVENT_CHANGE_SEAT);
                        events.ScheduleEvent(EVENT_JUMP_TO_VISUAL, 3000);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            passenger->ChangeSeat(1, true);
                        break;
                    }
                    case EVENT_JUMP_TO_VISUAL:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_VISUAL);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
                            passenger->ChangeSeat(2, true);
                        break;
                    }
                    case EVENT_SEAT_EXPLOSION:
                    {
                        events.CancelEvent(EVENT_SEAT_EXPLOSION);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(2))
                            passenger->ChangeSeat(3, true);
                        events.ScheduleEvent(EVENT_FINAL_SEAT, 8000);
                        break;
                    }
                    case EVENT_FINAL_SEAT:
                    {
                        events.CancelEvent(EVENT_FINAL_SEAT);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_camera_explosionationAI(creature);
    }
};

class npc_explosionation_clone : public CreatureScript
{
public:
   npc_explosionation_clone() : CreatureScript("npc_explosionation_clone") { }

    struct npc_explosionation_cloneAI : public ScriptedAI
    {
        npc_explosionation_cloneAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_STAND_UP      = 1,
            EVENT_MOVE_TO_CHEST,
            EVENT_CLOSE_CHEST
        };

        enum pointId
        {
            POINT_TO_CHEST  = 1,
            POINT_IN_CHEST
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_CLONE_AURA        = 84286
        };

        enum gobjectId
        {
            GO_CHEST_00     = 205245
        };

        enum actionId
        {
            ACTION_START_ESCAPE     = 1
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->AddAura(SPELL_CLONE_AURA, me);
            me->SetStandState(UNIT_STAND_STATE_KNEEL);
            events.ScheduleEvent(EVENT_STAND_UP, 8500);
            me->SetWalk(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_CHEST:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MoveJump(-8957.12f, -1546.72f, 94.45f, 4.0f, 4.0f, POINT_IN_CHEST);
                    break;
                }
                case POINT_IN_CHEST:
                {
                    me->SetStandState(UNIT_STAND_STATE_SIT);
                    me->SetFacingTo(1.19f);
                    events.ScheduleEvent(EVENT_CLOSE_CHEST, 2000);
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
                case ACTION_START_ESCAPE:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_CHEST, 12000);
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
                    case EVENT_STAND_UP:
                    {
                        events.CancelEvent(EVENT_STAND_UP);
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        me->SetFacingTo(5.12f);
                        me->HandleEmoteCommand(EMOTE_STATE_COWER);
                        break;
                    }
                    case EVENT_MOVE_TO_CHEST:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_CHEST);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TO_CHEST, -8955.33f, -1547.24f, 94.45f);
                        if (GameObject* chest = me->FindNearestGameObject(GO_CHEST_00, 50.0f))
                            me->SetFacingToObject(chest);
                        break;
                    }
                    case EVENT_CLOSE_CHEST:
                    {
                        events.CancelEvent(EVENT_CLOSE_CHEST);
                        if (GameObject* chest = me->FindNearestGameObject(GO_CHEST_00, 50.0f))
                            chest->SetGoState(GO_STATE_READY);
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_explosionation_cloneAI(creature);
    }
};

class npc_summoned_pygmy : public CreatureScript
{
public:
   npc_summoned_pygmy() : CreatureScript("npc_summoned_pygmy") { }

    struct npc_summoned_pygmyAI : public ScriptedAI
    {
        npc_summoned_pygmyAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_SHOOT_MULE    = 1,
            EVENT_MULE_HITTED
        };

        enum npcId
        {
            NPC_ENTRY_HARRISON_MULE     = 45140,
            NPC_ENTRY_HARRISON_JONES    = 44860,
            NPC_CASTER_CLONE            = 45144,
        };

        enum pointId
        {
            POINT_TO_MULE   = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_COSMETIC_SHOOT    = 94651
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->GetMotionMaster()->MovePoint(POINT_TO_MULE, -8944.61f, -1533.41f, 94.45f);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_MULE:
                {
                    events.ScheduleEvent(EVENT_SHOOT_MULE, 1500);
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
                    case EVENT_SHOOT_MULE:
                    {
                        events.CancelEvent(EVENT_SHOOT_MULE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_HARRISON_MULE &&
                                    (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                    DoCast((*itr), SPELL_COSMETIC_SHOOT);
                            }
                        }
                        events.ScheduleEvent(EVENT_MULE_HITTED, 500);
                        break;
                    }
                    case EVENT_MULE_HITTED:
                    {
                        events.CancelEvent(EVENT_MULE_HITTED);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->ToCreature()->GetEntry())
                                    {
                                        case NPC_ENTRY_HARRISON_MULE:
                                        {
                                            (*itr)->ToCreature()->AI()->DoAction(1);
                                            break;
                                        }
                                        case NPC_ENTRY_HARRISON_JONES:
                                        {
                                            (*itr)->SetStandState(UNIT_STAND_STATE_STAND);
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(2500, 0, playerOwner->GetGUID());
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(7000, 1, playerOwner->GetGUID());
                                            (*itr)->ToCreature()->AI()->DoAction(1);
                                            break;
                                        }
                                        case NPC_CASTER_CLONE:
                                        {
                                            (*itr)->ToCreature()->AI()->DoAction(1);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_summoned_pygmyAI(creature);
    }
};

class npc_harrison_mule : public CreatureScript
{
public:
   npc_harrison_mule() : CreatureScript("npc_harrison_mule") { }

    struct npc_harrison_muleAI : public ScriptedAI
    {
        npc_harrison_muleAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_AWAY     = 1
        };

        enum pointId
        {
            POINT_RUN_AWAY  = 1,
            POINT_RUN
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        enum actionId
        {
            ACTION_HIT_BY_PYGMY     = 1
        };

        enum npcId
        {
            NPC_BRAZIER_VEHICLE = 45135,
            NPC_BRAZIER         = 45136,
            NPC_LADY_HUMPS      = 45121,
            NPC_POWDER_KEG      = 45158,
            NPC_KEG_VEHICLE     = 45159
        };

        enum soundId
        {
            MULE_PLAY_SOUND     = 4066
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 0.90f);
        }

        void FindPassengersForVehicles()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(60.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        switch ((*itr)->ToCreature()->GetEntry())
                        {
                            case NPC_BRAZIER:
                            {
                                std::list<Unit*> targets;
                                Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                                me->VisitNearbyObject(60.0f, searcher);
                                for (std::list<Unit*>::const_iterator itrs = targets.begin(); itrs != targets.end(); ++itrs)
                                {
                                    if ((*itrs) && (*itrs)->ToTempSummon() && (*itrs)->ToTempSummon()->GetSummoner() == playerOwner)
                                    {
                                        switch ((*itrs)->ToCreature()->GetEntry())
                                        {
                                            case NPC_BRAZIER_VEHICLE:
                                            {
                                                (*itr)->EnterVehicle((*itrs), 1);
                                                break;
                                            }
                                            default:
                                                break;
                                        }
                                    }
                                }
                                break;
                            }
                            case NPC_POWDER_KEG:
                            {
                                std::list<Unit*> targets;
                                Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                                me->VisitNearbyObject(60.0f, searcher);
                                for (std::list<Unit*>::const_iterator itrs = targets.begin(); itrs != targets.end(); ++itrs)
                                {
                                    if ((*itrs) && (*itrs)->ToTempSummon() && (*itrs)->ToTempSummon()->GetSummoner() == playerOwner)
                                    {
                                        switch ((*itrs)->ToCreature()->GetEntry())
                                        {
                                            case NPC_KEG_VEHICLE:
                                            {
                                                (*itr)->EnterVehicle((*itrs), 0);
                                                break;
                                            }
                                            default:
                                                break;
                                        }
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_HIT_BY_PYGMY:
                {
                    me->PlayDirectSound(MULE_PLAY_SOUND);
                    events.ScheduleEvent(EVENT_MOVE_AWAY, 1000);
                    me->HandleEmoteCommand(463);
                    FindPassengersForVehicles();
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_RUN_AWAY:
                {
                    me->DespawnOrUnsummon(1);
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
                    case EVENT_MOVE_AWAY:
                    {
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        me->GetMotionMaster()->MovePoint(POINT_RUN_AWAY, -8951.38f, -1519.38f, 94.45f);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->ToCreature()->GetEntry() == NPC_LADY_HUMPS)
                                    {
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_RUN, -8987.58f, -1552.43f, 94.45f);
                                        (*itr)->ToCreature()->DespawnOrUnsummon(5000);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
        Unit* brazierVehicle;
        Unit* kegVehicle;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_muleAI(creature);
    }
};

class npc_harrison_jones_explosionation : public CreatureScript
{
public:
   npc_harrison_jones_explosionation() : CreatureScript("npc_harrison_jones_explosionation") { }

    struct npc_harrison_jones_explosionationAI : public ScriptedAI
    {
        npc_harrison_jones_explosionationAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_CHEST = 1,
            EVENT_CLOSE_CHEST,
            EVENT_INFORM_CAMERA
        };

        enum pointId
        {
            POINT_TO_CHEST  = 1,
            POINT_IN_CHEST
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_EXPLOSION_LARGE   = 82831
        };

        enum gobjectId
        {
            GO_CHEST_01     = 205244
        };

        enum actionId
        {
            ACTION_START_ESCAPE     = 1
        };

        enum npcId
        {
            NPC_EXPLOSIONATION_CAMERA   = 45146,
            NPC_EXPLOSION_TRIGGER       = 28960
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_CHEST:
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MoveJump(-8956.22f, -1553.60f, 94.45f, 4.0f, 4.0f, POINT_IN_CHEST);
                    break;
                }
                case POINT_IN_CHEST:
                {
                    me->SetStandState(UNIT_STAND_STATE_SIT);
                    me->SetFacingTo(1.19f);
                    events.ScheduleEvent(EVENT_CLOSE_CHEST, 2000);
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
                case ACTION_START_ESCAPE:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_CHEST, 13000);
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
                    case EVENT_MOVE_TO_CHEST:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_CHEST);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TO_CHEST, -8955.25f, -1552.21f, 94.45f);
                        if (GameObject* chest = me->FindNearestGameObject(GO_CHEST_01, 50.0f))
                            me->SetFacingToObject(chest);
                        break;
                    }
                    case EVENT_CLOSE_CHEST:
                    {
                        events.CancelEvent(EVENT_CLOSE_CHEST);
                        events.ScheduleEvent(EVENT_INFORM_CAMERA, 2000);
                        if (GameObject* chest = me->FindNearestGameObject(GO_CHEST_01, 50.0f))
                            chest->SetGoState(GO_STATE_READY);
                        break;
                    }
                    case EVENT_INFORM_CAMERA:
                    {
                        events.CancelEvent(EVENT_INFORM_CAMERA);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->ToCreature()->GetEntry())
                                    {
                                        case NPC_EXPLOSIONATION_CAMERA:
                                        {
                                            (*itr)->ToCreature()->AI()->DoAction(1);
                                            break;
                                        }
                                        case NPC_EXPLOSION_TRIGGER:
                                        {
                                            (*itr)->CastWithDelay(2000, (*itr), SPELL_EXPLOSION_LARGE, true);
                                            (*itr)->CastWithDelay(3000, (*itr), SPELL_EXPLOSION_LARGE, true);
                                            (*itr)->CastWithDelay(4000, (*itr), SPELL_EXPLOSION_LARGE, true);
                                            (*itr)->CastWithDelay(5000, (*itr), SPELL_EXPLOSION_LARGE, true);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_jones_explosionationAI(creature);
    }
};

class npc_explosionation_expl_dummy : public CreatureScript
{
public:
   npc_explosionation_expl_dummy() : CreatureScript("npc_explosionation_expl_dummy") { }

    struct npc_explosionation_expl_dummyAI : public ScriptedAI
    {
        npc_explosionation_expl_dummyAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_ENABLE_STARS      = 87397,
            SPELL_SIPHON_STARS      = 87409
        };

        enum actionId
        {
            ACTION_ENABLE_STARS     = 1
        };

        enum eventId
        {
            EVENT_ENABLE_STARS  = 1,
            EVENT_ENABLE_BEAMS,
            EVENT_QUEST_COMPLETE
        };

        void IsSummonedBy(Unit* owner)
        {
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void Reset()
        {
            // Kharthut's Tomb
            if (me->GetAreaId() == 5455)
                events.ScheduleEvent(EVENT_QUEST_COMPLETE, 2000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENABLE_STARS:
                {
                    events.ScheduleEvent(EVENT_ENABLE_STARS, 5000);
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
                    case EVENT_ENABLE_STARS:
                    {
                        events.CancelEvent(EVENT_ENABLE_STARS);
                        DoCast(SPELL_ENABLE_STARS);
                        me->CastWithDelay(urand(500, 1000), me, SPELL_ENABLE_STARS, true);
                        me->CastWithDelay(urand(500, 1500), me, SPELL_ENABLE_STARS, true);
                        me->CastWithDelay(urand(500, 2000), me, SPELL_ENABLE_STARS, true);
                        events.ScheduleEvent(EVENT_ENABLE_BEAMS, 3000);
                        break;
                    }
                    case EVENT_ENABLE_BEAMS:
                    {
                        events.CancelEvent(EVENT_ENABLE_BEAMS);
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(200.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature())
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    // Stars
                                    case 46195:
                                    case 46196:
                                    case 46197:
                                    case 46198:
                                    {
                                        (*itr)->CastSpell(me, SPELL_SIPHON_STARS);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.RescheduleEvent(EVENT_QUEST_COMPLETE, 2000);
                        std::list<Player*> targets;
                        Trinity::AnyPlayerInObjectRangeCheck u_check(me, 50.0f);
                        Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Player*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToPlayer())
                                (*itr)->ToPlayer()->KilledMonsterCredit(47318);
                        }
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
        return new npc_explosionation_expl_dummyAI(creature);
    }
};

class npc_harrison_jones_ots : public CreatureScript
{
public:
    npc_harrison_jones_ots() : CreatureScript("npc_harrison_jones_ots") { }

    enum questId
    {
        QUEST_ENTRY_ON_TO_SOMETHING = 27196
    };

    enum npcId
    {
        NPC_ENTRY_HARRISON_JONES    = 45180
    };

    enum eventId
    {
        EVENT_START_WP      = 1,
        EVENT_FIRST_JUMP,
        EVENT_SECOND_JUMP,
        EVENT_THIRD_JUMP,
        EVENT_FINAL_JUMP,
        EVENT_FACE_AND_TALK
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_QUEST_DETECTION   = 49417
    };

    enum pointId
    {
        POINT_FIRST_JUMP    = 2,
        POINT_SECOND_JUMP,
        POINT_THIRD_JUMP,
        POINT_FINAL_JUMP
    };

    enum creditId
    {
        QUEST_CREDIT_OTS     = 45238
    };

    #define GOSSIP_TEXT_JONES_01 "I'm ready, Doctor Jones!"

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ENTRY_ON_TO_SOMETHING) == QUEST_STATUS_INCOMPLETE)
            {
                player->AddAura(SPELL_UNIQUE_PHASING, player);
                player->SummonCreature(NPC_ENTRY_HARRISON_JONES, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                player->RemoveAurasDueToSpell(SPELL_QUEST_DETECTION);
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_ON_TO_SOMETHING) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JONES_01, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_harrison_jones_otsAI : public npc_escortAI
    {
        npc_harrison_jones_otsAI(Creature* creature) : npc_escortAI(creature)
        {
            playerOwner = NULL;
            isSummoned = false;
        }

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            isSummoned = true;
            TalkWithDelay(2000, 0, owner->GetGUID());
            events.ScheduleEvent(EVENT_START_WP, 3500);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP|UNIT_NPC_FLAG_QUESTGIVER);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_WP:
                    {
                        events.CancelEvent(EVENT_START_WP);
                        Start(false, true, NULL, NULL, false, false, true);
                        SetDespawnAtEnd(false);
                        break;
                    }
                    case EVENT_FIRST_JUMP:
                    {
                        events.CancelEvent(EVENT_FIRST_JUMP);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9148.55f, -1535.73f, 73.88f, 8.0f, 8.0f, POINT_FIRST_JUMP);
                        events.ScheduleEvent(EVENT_SECOND_JUMP, 1500);
                        break;
                    }
                    case EVENT_SECOND_JUMP:
                    {
                        events.CancelEvent(EVENT_SECOND_JUMP);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9145.12f, -1538.69f, 75.02f, 8.0f, 8.0f, POINT_SECOND_JUMP);
                        events.ScheduleEvent(EVENT_FACE_AND_TALK, 1500);
                        break;
                    }
                    case EVENT_FACE_AND_TALK:
                    {
                        events.CancelEvent(EVENT_FACE_AND_TALK);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            me->SetFacingToObject(playerOwner);
                            TalkWithDelay(1000, 2, playerOwner->GetGUID());
                        }
                        events.ScheduleEvent(EVENT_THIRD_JUMP, 6000);
                        break;
                    }
                    case EVENT_THIRD_JUMP:
                    {
                        events.CancelEvent(EVENT_THIRD_JUMP);
                        me->SetFacingTo(5.66f);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9128.91f, -1551.93f, 77.54f, 8.0f, 12.5f, POINT_THIRD_JUMP);
                        events.ScheduleEvent(EVENT_FINAL_JUMP, 2500);
                        break;
                    }
                    case EVENT_FINAL_JUMP:
                    {
                        events.CancelEvent(EVENT_FINAL_JUMP);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9127.91f, -1553.39f, 32.53f, 8.0f, 8.0f, POINT_FINAL_JUMP);
                        me->DespawnOrUnsummon(3500);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                playerOwner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_OTS);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 0: // WP Reached - Set Facing and Talk
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        me->SetFacingToObject(playerOwner);
                        TalkWithDelay(1000, 1, playerOwner->GetGUID());
                        events.ScheduleEvent(EVENT_FIRST_JUMP, 6500);
                    }
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
        bool isSummoned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_jones_otsAI(creature);
    }
};

class areatrigger_quest_tod : public AreaTriggerScript
{
    public:
        areatrigger_quest_tod() : AreaTriggerScript("at_quest_tod") { }

        enum Id
        {
            QUEST_THE_THRILL_OF_DISCOVERY   = 27511,
            AT_NORTHERN_HIEROGLYPHS         = 6288,
            AT_NORTHERN_HIEROGLYPHS_TWO     = 6287,
            AT_SOUTHERN_HIEROGLYPHS         = 6286,
            AT_SOUTHERN_HIEROGLYPHS_TWO     = 6289,
            AT_ANCIENT_MECHANISM            = 6284,
            CREDIT_NORTHERN                 = 45760,
            CREDIT_SOUTHERN                 = 45759,
            CREDIT_ANCIENT                  = 45757
        };

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->GetQuestStatus(QUEST_THE_THRILL_OF_DISCOVERY) == QUEST_STATUS_INCOMPLETE)
            {
                switch (trigger->id)
                {
                    case AT_NORTHERN_HIEROGLYPHS: player->KilledMonsterCredit(CREDIT_NORTHERN); break;
                    case AT_SOUTHERN_HIEROGLYPHS: player->KilledMonsterCredit(CREDIT_SOUTHERN); break;
                    case AT_ANCIENT_MECHANISM: player->KilledMonsterCredit(CREDIT_ANCIENT); break;
                    default: break;
                }
            }
            return false;
        }
};

class spell_sapphire_sight : public SpellScriptLoader
{
    public:
        spell_sapphire_sight() : SpellScriptLoader("spell_sapphire_sight") { }

        class spell_sapphire_sight_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sapphire_sight_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* owner = GetUnitOwner())
                    owner->SetPhaseMask(2, true);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* owner = GetUnitOwner())
                    owner->SetPhaseMask(1, true);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectRemoveFn(spell_sapphire_sight_AuraScript::OnApply, EFFECT_1, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_sapphire_sight_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sapphire_sight_AuraScript();
        }
};

class npc_harrison_jones_cots : public CreatureScript
{
public:
    npc_harrison_jones_cots() : CreatureScript("npc_harrison_jones_cots") { }

    enum questId
    {
        QUEST_ENTRY_BY_THE_LIGHT_OF_THE_STARS   = 27549,
        QUEST_ENTRY_TIPPING_THE_BALANCE         = 27431
    };

    enum spellIdCoTs
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_SUMMON_RIDE_FOOT  = 85296,
        SPELL_SUMMON_RIDE_CALF  = 85300,
        SPELL_SUMMON_RIDE_HAND  = 85302,
        SPELL_SUMMON_RIDE_ARM   = 85304,
        SPELL_SUMMON_RIDE_NECK  = 85306,
        SPELL_SUMMON_RIDE_HEAD  = 85312,
        SPELL_SUMMON_HARRISON   = 85018,
        SPELL_SUMMON_CAMERA     = 85330,
        SPELL_SUMMON_WATCHER_00 = 85019,
        SPELL_SUMMON_WATCHER_01 = 85885,
        SPELL_SUMMON_WATCHER_02 = 85895,
        SPELL_SUMMON_WATCHER_03 = 85907,
        SPELL_SUMMON_CLONE      = 85911
    };

    enum spellIdBtLoTs
    {
        SPELL_SUMMON_HARRISON_01    = 84600
    };

    #define GOSSIP_TEXT_TIPPING "What can I do to help?"

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_BY_THE_LIGHT_OF_THE_STARS)
        {
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->SetPhaseMask(4, true);
            player->CastSpell(player, SPELL_SUMMON_HARRISON_01, true);
            return false;
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ENTRY_TIPPING_THE_BALANCE) == QUEST_STATUS_INCOMPLETE)
            {
                player->AddAura(SPELL_UNIQUE_PHASING, player);
                player->SetPhaseMask(32, true);
                player->CastSpell(player, SPELL_SUMMON_WATCHER_00, true);
                player->CastSpell(player, SPELL_SUMMON_WATCHER_01, true);
                player->CastSpell(player, SPELL_SUMMON_WATCHER_02, true);
                player->CastSpell(player, SPELL_SUMMON_WATCHER_03, true);
                player->CastSpell(player, SPELL_SUMMON_RIDE_FOOT, true);
                player->CastSpell(player, SPELL_SUMMON_RIDE_CALF, true);
                player->CastSpell(player, SPELL_SUMMON_RIDE_HAND, true);
                player->CastSpell(player, SPELL_SUMMON_RIDE_ARM, true);
                player->CastSpell(player, SPELL_SUMMON_RIDE_NECK, true);
                player->CastSpell(player, SPELL_SUMMON_RIDE_HEAD, true);
                player->CastSpell(player, SPELL_SUMMON_HARRISON, true);
                player->CastSpell(player, SPELL_SUMMON_CAMERA, true);
                player->CastSpell(player, SPELL_SUMMON_CLONE, true);
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_TIPPING_THE_BALANCE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TIPPING, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }
};

class npc_harrison_jones_camera_cots : public CreatureScript
{
public:
   npc_harrison_jones_camera_cots() : CreatureScript("npc_harrison_jones_camera_cots") { }

    struct npc_harrison_jones_camera_cotsAI : public ScriptedAI
    {
        npc_harrison_jones_camera_cotsAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_CHANNEL_HARRISON,
            EVENT_JUMP_TO_FEET,
            EVENT_JUMP_AFTER_FEET,
            EVENT_JUMP_TO_HAND,
            EVENT_JUMP_TO_ARM,
            EVENT_JUMP_TO_HEAD,
            EVENT_JUMP_TO_EXT,
            EVENT_SWITCH_SEAT,
            EVENT_STOP_CHANNELING,
            EVENT_CHANNEL_STATUE_01,
            EVENT_CHANNEL_STATUE_02,
            EVENT_CHANNEL_STATUE_03,
            EVENT_CHANNEL_CLONE,
            EVENT_REMOVE_PASSENGERS
        };

        enum npcId
        {
            NPC_ENTRY_HARRISON_JONES    = 45505,
            NPC_ENTRY_NECK              = 45726,
            NPC_ENTRY_STATUE_00         = 45507,
            NPC_ENTRY_STATUE_01         = 46097,
            NPC_ENTRY_STATUE_02         = 46110,
            NPC_ENTRY_STATUE_03         = 46115,
            NPC_ENTRY_CLONE             = 46120
        };

        enum pointId
        {
            POINT_FEET          = 1,
            POINT_AFTER_FEET,
            POINT_TO_HANDS,
            POINT_TO_ARM,
            POINT_TO_HEAD,
            POINT_TO_EXT,
            POINT_STATUE_01,
            POINT_STATUE_02,
            POINT_STATUE_03,
            POINT_MIRROR
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_CAMERA_CHANNELING = 88552
        };

        enum actionId
        {
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 5000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FEET:
                {
                    events.ScheduleEvent(EVENT_JUMP_AFTER_FEET, 2000);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        events.ScheduleEvent(EVENT_CHANNEL_HARRISON, 100);
                        break;
                    }
                    case EVENT_CHANNEL_HARRISON:
                    {
                        events.CancelEvent(EVENT_CHANNEL_HARRISON);
                        events.ScheduleEvent(EVENT_JUMP_TO_FEET, 1000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_HARRISON_JONES)
                                    {
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING);
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_JUMP_TO_FEET:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_FEET);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9143.75f, -1487.83f, -159.73f, 10.0f, 10.0f, POINT_FEET);
                        break;
                    }
                    case EVENT_JUMP_AFTER_FEET:
                    {
                        events.CancelEvent(EVENT_JUMP_AFTER_FEET);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9124.85f, -1468.15f, -147.82f, 10.0f, 10.0f, POINT_AFTER_FEET);
                        events.ScheduleEvent(EVENT_JUMP_TO_HAND, 7000);
                        break;
                    }
                    case EVENT_JUMP_TO_HAND:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_HAND);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9192.24f, -1460.50f, -140.46f, 10.0f, 10.0f, POINT_TO_HANDS);
                        events.ScheduleEvent(EVENT_JUMP_TO_ARM, 6000);
                        break;
                    }
                    case EVENT_JUMP_TO_ARM:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_ARM);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9173.77f, -1453.63f, -120.95f, 10.0f, 10.0f, POINT_TO_ARM);
                        events.ScheduleEvent(EVENT_JUMP_TO_HEAD, 6000);
                        break;
                    }
                    case EVENT_JUMP_TO_HEAD:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_HEAD);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9172.84f, -1450.05f, -108.15f, 10.0f, 10.0f, POINT_TO_HEAD);
                        events.ScheduleEvent(EVENT_STOP_CHANNELING, 16000);
                        break;
                    }
                    case EVENT_STOP_CHANNELING:
                    {
                        events.CancelEvent(EVENT_STOP_CHANNELING);
                        me->CastStop();
                        me->InterruptNonMeleeSpells(true);
                        me->RemoveAurasDueToSpell(SPELL_CAMERA_CHANNELING);
                        events.ScheduleEvent(EVENT_JUMP_TO_EXT, 1000);
                        break;
                    }
                    case EVENT_JUMP_TO_EXT:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_EXT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9152.22f, -1542.07f, -163.49f, 20.0f, 20.0f, POINT_TO_EXT);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_NECK)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_CHANNEL_STATUE_01, 12000);
                        break;
                    }
                    case EVENT_CHANNEL_STATUE_01:
                    {
                        events.CancelEvent(EVENT_CHANNEL_STATUE_01);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_01)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9223.98f, -1581.12f, -130.79f, 20.0f, 20.0f, POINT_STATUE_01);
                        events.ScheduleEvent(EVENT_CHANNEL_STATUE_02, 6000);
                        break;
                    }
                    case EVENT_CHANNEL_STATUE_02:
                    {
                        events.CancelEvent(EVENT_CHANNEL_STATUE_01);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_02)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9152.02f, -1562.15f, -130.79f, 20.0f, 20.0f, POINT_STATUE_02);
                        events.ScheduleEvent(EVENT_CHANNEL_STATUE_03, 6000);
                        break;
                    }
                    case EVENT_CHANNEL_STATUE_03:
                    {
                        events.CancelEvent(EVENT_CHANNEL_STATUE_03);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_03)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9277.71f, -1525.10f, -130.79f, 20.0f, 20.0f, POINT_STATUE_03);
                        events.ScheduleEvent(EVENT_CHANNEL_CLONE, 6000);
                        break;
                    }
                    case EVENT_CHANNEL_CLONE:
                    {
                        events.CancelEvent(EVENT_CHANNEL_CLONE);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_CLONE)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9199.86f, -1568.14f, -162.40f, 30.0f, 30.0f, POINT_MIRROR);
                        events.ScheduleEvent(EVENT_REMOVE_PASSENGERS, 8000);
                        break;
                    }
                    case EVENT_REMOVE_PASSENGERS:
                    {
                        events.CancelEvent(EVENT_REMOVE_PASSENGERS);
                        if (me->GetVehicleKit())
                        {
                            if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            {
                                if (passenger->GetTypeId() == TYPEID_PLAYER)
                                    passenger->ToPlayer()->KilledMonsterCredit(45742);
                            }
                            me->GetVehicleKit()->RemoveAllPassengers();
                        }
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_jones_camera_cotsAI(creature);
    }
};

class npc_harrison_jones_cots_summon : public CreatureScript
{
public:
   npc_harrison_jones_cots_summon() : CreatureScript("npc_harrison_jones_cots_summon") { }

    struct npc_harrison_jones_cots_summonAI : public ScriptedAI
    {
        npc_harrison_jones_cots_summonAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_START         = 1,
            EVENT_JUMP_TO_CALF,
            EVENT_JUMP_TO_HAND,
            EVENT_JUMP_TO_ARM,
            EVENT_JUMP_TO_NECK,
            EVENT_JUMP_TO_HEAD,
            EVENT_TAKE_ROPE,
            EVENT_JUMP_OFF,
            EVENT_KNOCK_STATUE_00,
            EVENT_KNOCK_STATUE_01,
            EVENT_KNOCK_STATUE_02,
            EVENT_KNOCK_STATUE_03
        };

        enum npcId
        {
            NPC_STATUE_FOOT     = 45723,
            NPC_STATUE_CALF     = 45724,
            NPC_STATUE_HAND     = 45722,
            NPC_STATUE_ARM      = 45725,
            NPC_STATUE_NECK     = 45726,
            NPC_STATUE_HEAD     = 45727,
            NPC_ROPE_TRIGGER    = 28960,
            NPC_ENTRY_STATUE_00 = 45507,
            NPC_ENTRY_STATUE_01 = 46097,
            NPC_ENTRY_STATUE_02 = 46110,
            NPC_ENTRY_STATUE_03 = 46115,
            NPC_ENTRY_STATUE_V0 = 45590,
            NPC_ENTRY_STATUE_V1 = 46099,
            NPC_ENTRY_STATUE_V2 = 46111,
            NPC_ENTRY_STATUE_V3 = 46116
        };

        enum pointId
        {
            POINT_FOOT  = 1,
            POINT_OFF
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_HARRISON_ROPE_01  = 85051,
            SPELL_HARRISON_ROPE_02  = 85323,
            SPELL_DUST_BUNNY        = 85346,
            SPELL_CAMERA_CHANNELING = 88552,
            SPELL_FOOT_SOUND        = 87302,
            SPELL_CALF_SOUND        = 87304,
            SPELL_HAND_SOUND        = 87307,
            SPELL_ARM_SOUND         = 87311,
            SPELL_SHOULDER_SOUND    = 87312,
            SPELL_HEAD_SOUND        = 87313,
            SPELL_DUST_STATE        = 84277,
            SPELL_DROWNED           = 87259,
            SPELL_IMPACT_SOUND_02   = 87348,
            SPELL_IMPACT_SOUND_03   = 87349,
            SPELL_IMPACT_SOUND_04   = 87350
        };

        enum actionId
        {
            ACTION_START_EVENT  = 1
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFacingToObject(owner);
            TalkWithDelay(1500, 0, owner->GetGUID());
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_EVENT:
                {
                    events.ScheduleEvent(EVENT_START, 3000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FOOT:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(60.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                if ((*itr)->GetEntry() == NPC_STATUE_FOOT)
                                    me->EnterVehicle((*itr), 0);
                            }
                        }
                    }
                    me->CastWithDelay(1500, me, SPELL_FOOT_SOUND, true);
                    events.ScheduleEvent(EVENT_JUMP_TO_CALF, 3000);
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
                    case EVENT_START:
                    {
                        events.CancelEvent(EVENT_START);
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FOOT, -9150.63f, -1474.53f, -170.90f);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                me->PlayDirectSound(23540, playerOwner->ToPlayer());
                        }
                        break;
                    }
                    case EVENT_JUMP_TO_CALF:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_CALF);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_STATUE_CALF)
                                        me->EnterVehicle((*itr), 0);
                                }
                            }
                        }
                        me->CastWithDelay(1250, me, SPELL_CALF_SOUND, true);
                        events.ScheduleEvent(EVENT_JUMP_TO_HAND, 6000);
                        break;
                    }
                    case EVENT_JUMP_TO_HAND:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_HAND);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_STATUE_HAND)
                                        me->EnterVehicle((*itr), 0);
                                }
                            }
                        }
                        me->CastWithDelay(1500, me, SPELL_HAND_SOUND, true);
                        events.ScheduleEvent(EVENT_JUMP_TO_ARM, 6000);
                        break;
                    }
                    case EVENT_JUMP_TO_ARM:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_ARM);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_STATUE_ARM)
                                        me->EnterVehicle((*itr), 0);
                                }
                            }
                            playerOwner->CastSpell(me, SPELL_DUST_BUNNY, true);
                        }
                        me->CastWithDelay(500, me, SPELL_ARM_SOUND, true);
                        events.ScheduleEvent(EVENT_JUMP_TO_NECK, 6000);
                        break;
                    }
                    case EVENT_JUMP_TO_NECK:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_NECK);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_STATUE_NECK)
                                        me->EnterVehicle((*itr), 0);
                                }
                            }
                        }
                        me->CastWithDelay(1000, me, SPELL_SHOULDER_SOUND, true);
                        events.ScheduleEvent(EVENT_JUMP_TO_HEAD, 6000);
                        break;
                    }
                    case EVENT_JUMP_TO_HEAD:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_HEAD);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 120.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(120.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_STATUE_HEAD)
                                        me->EnterVehicle((*itr), 0);
                                }
                            }
                        }
                        me->CastWithDelay(1000, me, SPELL_HEAD_SOUND, true);
                        events.ScheduleEvent(EVENT_TAKE_ROPE, 2500);
                        break;
                    }
                    case EVENT_TAKE_ROPE:
                    {
                        events.CancelEvent(EVENT_TAKE_ROPE);
                        if (Creature* ropeTrigger = me->FindNearestCreature(NPC_ROPE_TRIGGER, 200.0f, true))
                            me->CastWithDelay(1000, ropeTrigger, SPELL_HARRISON_ROPE_02, true);
                        events.ScheduleEvent(EVENT_JUMP_OFF, 5000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                me->PlayDirectSound(21383, playerOwner->ToPlayer());
                        }
                        break;
                    }
                    case EVENT_JUMP_OFF:
                    {
                        events.CancelEvent(EVENT_JUMP_OFF);
                        if (me->GetVehicleBase())
                        {
                            me->GetVehicleBase()->GetMotionMaster()->MovementExpired(false);
                            me->GetVehicleBase()->GetMotionMaster()->MoveJump(-9162.91f, -1530.07f, -170.90f, 20.0f, 20.0f, POINT_OFF);
                        }
                        events.ScheduleEvent(EVENT_KNOCK_STATUE_00, 6000);
                        events.ScheduleEvent(EVENT_KNOCK_STATUE_01, 12000);
                        events.ScheduleEvent(EVENT_KNOCK_STATUE_02, 16000);
                        events.ScheduleEvent(EVENT_KNOCK_STATUE_03, 21000);
                        break;
                    }
                    case EVENT_KNOCK_STATUE_00:
                    {
                        events.CancelEvent(EVENT_KNOCK_STATUE_00);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_00)
                                    {
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DROWNED);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_IMPACT_SOUND_02);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_IMPACT_SOUND_03);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_IMPACT_SOUND_04);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_KNOCK_STATUE_01:
                    {
                        events.CancelEvent(EVENT_KNOCK_STATUE_01);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_01)
                                    {
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DROWNED);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_IMPACT_SOUND_02);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_IMPACT_SOUND_03);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_IMPACT_SOUND_04);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_KNOCK_STATUE_02:
                    {
                        events.CancelEvent(EVENT_KNOCK_STATUE_02);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_02)
                                    {
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DROWNED);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_IMPACT_SOUND_02);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_IMPACT_SOUND_03);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_IMPACT_SOUND_04);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_KNOCK_STATUE_03:
                    {
                        events.CancelEvent(EVENT_KNOCK_STATUE_03);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_STATUE_03)
                                    {
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DROWNED);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_DUST_STATE);
                                        (*itr)->CastWithDelay(500, (*itr), SPELL_IMPACT_SOUND_02);
                                        (*itr)->CastWithDelay(1000, (*itr), SPELL_IMPACT_SOUND_03);
                                        (*itr)->CastWithDelay(1500, (*itr), SPELL_IMPACT_SOUND_04);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_jones_cots_summonAI(creature);
    }
};

class npc_player_clone_cots : public CreatureScript
{
public:
   npc_player_clone_cots() : CreatureScript("npc_player_clone_cots") { }

    struct npc_player_clone_cotsAI : public ScriptedAI
    {
        npc_player_clone_cotsAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_SET_VISIBLE   = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_MIRROR_AURA       = 85912
        };

        enum actionId
        {
            ACTION_START_EVENT  = 1
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->CastSpell(me, SPELL_MIRROR_AURA);
            events.ScheduleEvent(EVENT_SET_VISIBLE, 15000);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetVisible(false);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SET_VISIBLE:
                    {
                        events.CancelEvent(EVENT_SET_VISIBLE);
                        me->SetVisible(true);
                        me->HandleEmoteCommand(EMOTE_STATE_COWER);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_player_clone_cotsAI(creature);
    }
};

class npc_harrison_jones_btlos : public CreatureScript
{
public:
   npc_harrison_jones_btlos() : CreatureScript("npc_harrison_jones_btlos") { }

    struct npc_harrison_jones_btlosAI : public ScriptedAI
    {
        npc_harrison_jones_btlosAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_LIGHT     = 1,
            EVENT_START_CAMERA
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_SUMMON_STAFF_BUNNY    = 84624,
            SPELL_SUMMON_CAMERA_BUNNY   = 84672,
            SPELL_SUMMON_HARRISON_01    = 84600,
            SPELL_THROW_STAFF           = 84602,
            SPELL_FADE_TO_BLACK         = 93949
        };

        enum pointId
        {
            POINT_LIGHT     = 1
        };

        enum npcId
        {
            NPC_ENTRY_STAFF = 45281
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(true);
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            TalkWithDelay(1500, 0, owner->GetGUID());
            me->SetFacingToObject(owner);
            events.ScheduleEvent(EVENT_MOVE_TO_LIGHT, 5000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LIGHT:
                {
                    events.ScheduleEvent(EVENT_START_CAMERA, 3000);
                    DoCast(SPELL_THROW_STAFF);
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
                    case EVENT_MOVE_TO_LIGHT:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_LIGHT);
                        me->GetMotionMaster()->MovePoint(POINT_LIGHT, -9213.36f, -1553.02f, -169.15f);
                        break;
                    }
                    case EVENT_START_CAMERA:
                    {
                        events.CancelEvent(EVENT_START_CAMERA);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_STAFF_BUNNY, true);
                            playerOwner->CastWithDelay(2000, playerOwner, SPELL_FADE_TO_BLACK, true);
                            playerOwner->CastWithDelay(3000, playerOwner, SPELL_SUMMON_CAMERA_BUNNY, true);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_jones_btlosAI(creature);
    }
};

class npc_camera_bunny_btlos : public CreatureScript
{
public:
   npc_camera_bunny_btlos() : CreatureScript("npc_camera_bunny_btlos") { }

    struct npc_camera_bunny_btlosAI : public ScriptedAI
    {
        npc_camera_bunny_btlosAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_MOVE_TO_LIGHT     = 1,
            EVENT_CHANNEL_STAFF,
            EVENT_MOVE_CIRCLE_1,
            EVENT_MOVE_CIRCLE_2,
            EVENT_MOVE_CIRCLE_3,
            EVENT_MOVE_CIRCLE_4,
            EVENT_MOVE_STATUE,
            EVENT_REMOVE_PASSENGER
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_STAFF_CAMERA_BEAM = 84681,
            SPELL_WATCHER_BEAM      = 84703
        };

        enum pointId
        {
            POINT_LIGHT     = 1,
            POINT_CIRCLE_1,
            POINT_CIRCLE_2,
            POINT_CIRCLE_3,
            POINT_CIRCLE_4,
            POINT_TO_STATUE
        };

        enum npcId
        {
            NPC_ENTRY_STAFF     = 45281,
            NPC_ENTRY_CIRCUIT   = 45319
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(200.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        if ((*itr)->GetEntry() == NPC_ENTRY_STAFF)
                            DoCast((*itr), SPELL_STAFF_CAMERA_BEAM, true);
                    }
                }
            }
            owner->EnterVehicle(me, 0);
            events.ScheduleEvent(EVENT_MOVE_TO_LIGHT, 3000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LIGHT:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                        passenger->ChangeSeat(2, true);
                    events.ScheduleEvent(EVENT_MOVE_CIRCLE_1, 2000);
                    break;
                }
                case POINT_CIRCLE_1:
                {
                    events.ScheduleEvent(EVENT_MOVE_CIRCLE_2, 1);
                    break;
                }
                case POINT_CIRCLE_2:
                {
                    events.ScheduleEvent(EVENT_MOVE_CIRCLE_3, 1);
                    break;
                }
                case POINT_CIRCLE_3:
                {
                    events.ScheduleEvent(EVENT_MOVE_CIRCLE_4, 1);
                    break;
                }
                case POINT_CIRCLE_4:
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                    me->VisitNearbyObject(200.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature())
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_CIRCUIT)
                                (*itr)->CastSpell((*itr), SPELL_WATCHER_BEAM, true);
                        }
                    }
                    events.ScheduleEvent(EVENT_MOVE_STATUE, 8000);
                    break;
                }
                case POINT_TO_STATUE:
                {
                    events.ScheduleEvent(EVENT_REMOVE_PASSENGER, 5000);
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
                    case EVENT_MOVE_TO_LIGHT:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_LIGHT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9205.38f, -1553.47f, -134.54f, 10.0f, 10.0f, POINT_LIGHT);
                        events.ScheduleEvent(EVENT_MOVE_CIRCLE_1, 3000);
                        break;
                    }
                    case EVENT_MOVE_CIRCLE_1:
                    {
                        events.CancelEvent(EVENT_MOVE_CIRCLE_1);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9285.50f, -1585.26f, -137.28f, 8.0f, 8.0f, POINT_CIRCLE_1);
                        break;
                    }
                    case EVENT_MOVE_CIRCLE_2:
                    {
                        events.CancelEvent(EVENT_MOVE_CIRCLE_2);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9290.79f, -1528.14f, -143.03f, 8.0f, 8.0f, POINT_CIRCLE_2);
                        break;
                    }
                    case EVENT_MOVE_CIRCLE_3:
                    {
                        events.CancelEvent(EVENT_MOVE_CIRCLE_3);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9266.45f, -1521.75f, -142.95f, 8.0f, 8.0f, POINT_CIRCLE_3);
                        break;
                    }
                    case EVENT_MOVE_CIRCLE_4:
                    {
                        events.CancelEvent(EVENT_MOVE_CIRCLE_4);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9285.50f, -1585.26f, -137.28f, 8.0f, 8.0f, POINT_CIRCLE_4);
                        break;
                    }
                    case EVENT_MOVE_STATUE:
                    {
                        events.CancelEvent(EVENT_MOVE_STATUE);
                        me->CastStop();
                        me->SetFacingTo(3.83f);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9333.71f, -1624.87f, -122.25f, 20.0f, 20.0f, POINT_TO_STATUE);
                        break;
                    }
                    case EVENT_REMOVE_PASSENGER:
                    {
                        events.CancelEvent(EVENT_REMOVE_PASSENGER);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_camera_bunny_btlosAI(creature);
    }
};

class npc_staff_bunny_btlos : public CreatureScript
{
public:
   npc_staff_bunny_btlos() : CreatureScript("npc_staff_bunny_btlos") { }

    struct npc_staff_bunny_btlosAI : public ScriptedAI
    {
        npc_staff_bunny_btlosAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_STAFF_TRANSFORM   = 84656,
            SPELL_STAFF_IMPACT      = 84639,
            SPELL_LIGHTNING_00      = 81435,
            SPELL_LIGHTNING_01      = 81436,
            SPELL_LIGHTNING_02      = 81437,
            SPELL_LIGHTNING_03      = 81438,
            SPELL_LIGHTNING_IMP     = 84701
        };

        enum eventId
        {
            EVENT_CAST_LIGHTNING    = 1,
            EVENT_STOP_EVENTS
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            me->AddAura(SPELL_STAFF_TRANSFORM, me);
            me->CastWithDelay(2000, me, SPELL_STAFF_IMPACT, true);
            me->CastSpell(me, SPELL_STAFF_IMPACT, true);
            events.ScheduleEvent(EVENT_CAST_LIGHTNING, 5000);
            events.ScheduleEvent(EVENT_STOP_EVENTS, 35000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_LIGHTNING:
                    {
                        events.RescheduleEvent(EVENT_CAST_LIGHTNING, urand(1000, 3500));
                        me->CastWithDelay(urand(500, 1500), me, SPELL_LIGHTNING_00, true);
                        me->CastWithDelay(urand(500, 1500), me, SPELL_LIGHTNING_01, true);
                        me->CastWithDelay(urand(500, 1500), me, SPELL_LIGHTNING_02, true);
                        me->CastWithDelay(urand(500, 1500), me, SPELL_LIGHTNING_03, true);
                        DoCast(me, SPELL_LIGHTNING_IMP, true);
                        break;
                    }
                    case EVENT_STOP_EVENTS:
                    {
                        events.Reset();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_staff_bunny_btlosAI(creature);
    }
};

class npc_uldum_watcher : public CreatureScript
{
public:
   npc_uldum_watcher() : CreatureScript("npc_uldum_watcher") { }

    struct npc_uldum_watcherAI : public ScriptedAI
    {
        npc_uldum_watcherAI(Creature* creature) : ScriptedAI(creature) {}

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_uldum_watcherAI(creature);
    }
};

class spell_orb_of_the_stars : public SpellScriptLoader
{
    public:
        spell_orb_of_the_stars() : SpellScriptLoader("spell_orb_of_the_stars") { }

        class spell_orb_of_the_stars_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_orb_of_the_stars_SpellScript);

            enum spellId
            {
                SPELL_UNIQUE_PHASING    = 60191,
                SPELL_FADE_TO_BLACK     = 89315,
                SPELL_SUMMON_CAMERA     = 86268
            };

            enum gobjectId
            {
            };

            enum questId
            {
                QUEST_ENTRY_DO_THE_HONORS   = 27669
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_ENTRY_DO_THE_HONORS) == QUEST_STATUS_INCOMPLETE)
                        {
                            if (caster->GetAreaId() == 5431)
                                return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void HandleEffects()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (!caster->HasAura(SPELL_UNIQUE_PHASING))
                        caster->AddAura(SPELL_UNIQUE_PHASING, caster);

                    caster->SetPhaseMask(16, true);
                    caster->CastSpell(caster, SPELL_FADE_TO_BLACK, true);
                    caster->CastWithDelay(1500, caster, SPELL_SUMMON_CAMERA, true);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_orb_of_the_stars_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_orb_of_the_stars_SpellScript::HandleEffects);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_orb_of_the_stars_SpellScript();
        }
};

class npc_orb_of_the_stars_camera : public CreatureScript
{
public:
   npc_orb_of_the_stars_camera() : CreatureScript("npc_orb_of_the_stars_camera") { }

    struct npc_orb_of_the_stars_cameraAI : public ScriptedAI
    {
        npc_orb_of_the_stars_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_CAMERA_CHANNELING = 88552,
            SPELL_STAR_POWER        = 87397,
            SPELL_FADE_TO_BLACK     = 89315
        };

        enum eventId
        {
            EVENT_POINT_CENTER      = 1,
            EVENT_TELEPORT_OBELISK,
            EVENT_REMOVE_PASSENGER,
            EVENT_ADJUST_FACING
        };

        enum npcId
        {
            NPC_ENTRY_STAR_CENTER   = 28960
        };

        enum pointId
        {
            POINT_OBELISK   = 10
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->EnterVehicle(me, 2);
            events.ScheduleEvent(EVENT_POINT_CENTER, 1000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_OBELISK:
                {
                    events.ScheduleEvent(EVENT_ADJUST_FACING, 1);
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
                    case EVENT_POINT_CENTER:
                    {
                        events.CancelEvent(EVENT_POINT_CENTER);
                        if (Creature* starCenter = me->FindNearestCreature(NPC_ENTRY_STAR_CENTER, 200.0f, true))
                        {
                            DoCast(starCenter, SPELL_CAMERA_CHANNELING, true);
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                                playerOwner->CastWithDelay(3000, starCenter, SPELL_STAR_POWER, true);
                            starCenter->AI()->DoAction(1);
                        }
                        events.ScheduleEvent(EVENT_TELEPORT_OBELISK, 18000);
                        break;
                    }
                    case EVENT_TELEPORT_OBELISK:
                    {
                        events.CancelEvent(EVENT_TELEPORT_OBELISK);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            me->CastStop();
                            playerOwner->CastSpell(playerOwner, SPELL_FADE_TO_BLACK, true);
                        }
                        me->GetMotionMaster()->MoveJump(-9357.67f, -1635.93f, 237.04f, 60.0f, 60.0f, POINT_OBELISK);
                        events.ScheduleEvent(EVENT_REMOVE_PASSENGER, 15000);
                        break;
                    }
                    case EVENT_ADJUST_FACING:
                    {
                        me->SetFacingTo(0.71f);
                        events.CancelEvent(EVENT_ADJUST_FACING);
                        break;
                    }
                    case EVENT_REMOVE_PASSENGER:
                    {
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        events.CancelEvent(EVENT_REMOVE_PASSENGER);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_orb_of_the_stars_cameraAI(creature);
    }
};

class spell_activate_guardian : public SpellScriptLoader
{
    public:
        spell_activate_guardian() : SpellScriptLoader("spell_activate_guardian") { }

        class spell_activate_guardian_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_activate_guardian_SpellScript);

            enum npcId
            {
                NPC_ENTRY_TITANIC_GUARDIAN  = 47032
            };

            enum spellId
            {
                SPELL_ULDUM_STATUE_ANIM_KIT     = 87617
            };

            void HandleEffects()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Creature* titanicGuardian = caster->FindNearestCreature(NPC_ENTRY_TITANIC_GUARDIAN, 100.0f, true))
                    {
                        if (!titanicGuardian->HasAura(SPELL_ULDUM_STATUE_ANIM_KIT))
                            return;

                        titanicGuardian->RemoveAurasDueToSpell(SPELL_ULDUM_STATUE_ANIM_KIT);
                        titanicGuardian->AI()->AttackStart(caster);
                        titanicGuardian->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        titanicGuardian->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        caster->AddThreat(titanicGuardian, 1.0f);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_activate_guardian_SpellScript::HandleEffects);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_activate_guardian_SpellScript();
        }
};

class npc_titanic_guardian : public CreatureScript
{
public:
   npc_titanic_guardian() : CreatureScript("npc_titanic_guardian") { }

    struct npc_titanic_guardianAI : public ScriptedAI
    {
        npc_titanic_guardianAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum spellId
        {
            SPELL_BLAZING_ERUPTION      = 87753,
            SPELL_BURNING_GAZE          = 87665,
            SPELL_BURNING_GAZE_SUMMON   = 87662,
            SPELL_SUMMON_METEOR         = 87694,
            SPELL_SUMMON_METEOR_TRIGGER = 87709
        };

        enum eventId
        {
            EVENT_BLAZING_ERUPTION  = 1,
            EVENT_BURNING_GAZE,
            EVENT_SUMMON_METEOR,
            EVENT_ENABLE_GAZES,
            EVENT_REMOVE_ROOT
        };

        enum npcId
        {
            NPC_TITANIC_GUARDIAN_METEOR     = 47058,
            NPC_TITANIC_METEOR              = 47065
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_BLAZING_ERUPTION, 1);
            //events.ScheduleEvent(EVENT_BURNING_GAZE, 4000);   // TODO: Find why gazes don't work properly
            events.ScheduleEvent(EVENT_SUMMON_METEOR, 8000);
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            me->DespawnCreaturesInArea(NPC_TITANIC_GUARDIAN_METEOR);
            me->DespawnCreaturesInArea(NPC_TITANIC_METEOR);
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnCreaturesInArea(NPC_TITANIC_GUARDIAN_METEOR);
            me->DespawnCreaturesInArea(NPC_TITANIC_METEOR);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BLAZING_ERUPTION:
                    {
                        RESCHEDULE_IF_CASTING;
                        me->SetControlled(true, UNIT_STATE_ROOT);
                        me->CastStop();
                        DoCast(SPELL_BLAZING_ERUPTION);
                        events.RescheduleEvent(EVENT_BLAZING_ERUPTION, urand(7000, 12000));
                        events.ScheduleEvent(EVENT_REMOVE_ROOT, 3100);
                        break;
                    }
                    case EVENT_REMOVE_ROOT:
                    {
                        events.CancelEvent(EVENT_REMOVE_ROOT);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        break;
                    }
                    /*case EVENT_BURNING_GAZE:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_BURNING_GAZE, urand(8000, 21000));
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_BURNING_GAZE_SUMMON);
                        events.ScheduleEvent(EVENT_ENABLE_GAZES, 200);
                        break;
                    }*/
                    case EVENT_SUMMON_METEOR:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_SUMMON_METEOR, urand(10000, 25000));
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_SUMMON_METEOR);
                        break;
                    }
                    /*case EVENT_ENABLE_GAZES:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.CancelEvent(EVENT_ENABLE_GAZES);
                        DoCast(SPELL_BURNING_GAZE);
                        break;
                    }*/
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_titanic_guardianAI(creature);
    }
};

class npc_titanic_guardian_meteor : public CreatureScript
{
public:
   npc_titanic_guardian_meteor() : CreatureScript("npc_titanic_guardian_meteor") { }

    struct npc_titanic_guardian_meteorAI : public ScriptedAI
    {
        npc_titanic_guardian_meteorAI(Creature* creature) : ScriptedAI(creature) {isReturned = false;}

        EventMap events;

        enum spellId
        {
            SPELL_METEOR_IMPACT     = 87701,
            SPELL_METEOR_GROUND     = 87709,
            SPELL_ADRENALINE_RUSH   = 87657,
            SPELL_LAUNCH_METEOR     = 87747
        };

        enum pointId
        {
            POINT_TARGET    = 1
        };

        enum eventId
        {
            EVENT_LAUNCH_METEOR         = 1,
            EVENT_RETURN_TO_GUARDIAN
        };

        enum npcId
        {
            NPC_ENTRY_TITANIC_GUARDIAN  = 47032
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_LAUNCH_METEOR:
                {
                    me->setFaction(caster->getFaction());
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    events.ScheduleEvent(EVENT_RETURN_TO_GUARDIAN, 500);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->setFaction(14);
            events.ScheduleEvent(EVENT_LAUNCH_METEOR, 100);
            isReturned = false;
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TARGET:
                {
                    if (isReturned == true)
                    {
                        DoCast(me, SPELL_METEOR_IMPACT);
                        me->DespawnOrUnsummon(1500);
                        me->CombatStop();
                        if (Creature* guardian = me->FindNearestCreature(NPC_ENTRY_TITANIC_GUARDIAN, 100.0f, true))
                        {
                            if (me->GetHealthPct() > 5)
                                me->DealDamage(guardian, urand(20000, 35000));
                        }
                        break;
                    }
                    DoCast(me, SPELL_METEOR_IMPACT, true);
                    DoCast(me, SPELL_METEOR_GROUND, true);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    me->SetReactState(REACT_PASSIVE);
                    me->CombatStop();
                    me->setFaction(188);
                    Talk(0);
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
                    case EVENT_LAUNCH_METEOR:
                    {
                        events.CancelEvent(EVENT_LAUNCH_METEOR);
                        if (Unit* target = me->FindNearestPlayer(200.0f, true))
                        {
                            AttackStart(target);
                            me->GetMotionMaster()->MovementExpired(false);
                            me->GetMotionMaster()->MoveJump(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 18.0f, 18.0f, POINT_TARGET);
                        }
                        break;
                    }
                    case EVENT_RETURN_TO_GUARDIAN:
                    {
                        events.CancelEvent(EVENT_RETURN_TO_GUARDIAN);
                        me->GetMotionMaster()->MovementExpired(false);
                        if (Creature* titanicGuardian = me->FindNearestCreature(NPC_ENTRY_TITANIC_GUARDIAN, 300.0f, true))
                            me->GetMotionMaster()->MoveJump(titanicGuardian->GetPositionX(), titanicGuardian->GetPositionY(), titanicGuardian->GetPositionZ()+25, 18.0f, 18.0f, POINT_TARGET);
                        isReturned = true;
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        protected:
            bool isReturned;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_titanic_guardian_meteorAI(creature);
    }
};

class npc_ignition_camera_event : public CreatureScript
{
public:
   npc_ignition_camera_event() : CreatureScript("npc_ignition_camera_event") { }

    struct npc_ignition_camera_eventAI : public ScriptedAI
    {
        npc_ignition_camera_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_FADE_TO_BLACK         = 89315
        };

        enum pointId
        {
            POINT_OUT   = 1,
            POINT_DOWN,
            POINT_OBELISK   = 10
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_MOVE_POINT_OUT,
            EVENT_POINT_DOWN,
            EVENT_TELEPORT_OBELISK,
            EVENT_REMOVE_PASSENGER,
            EVENT_ADJUST_FACING
        };

        enum npcId
        {
            NPC_ENTRY_TITAN_MECHANISM   = 50401,
            NPC_ENTRY_GENERIC_BUNNY     = 28960
        };

        enum goId
        {
            GO_ENTRY_LENS   = 206551
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1500);
            events.ScheduleEvent(EVENT_MOVE_POINT_OUT, 2000);
            if (Creature* titan = me->FindNearestCreature(NPC_ENTRY_TITAN_MECHANISM, 100.0f, true))
                DoCast(titan, SPELL_CAMERA_CHANNELING, true);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_OUT:
                {
                    events.ScheduleEvent(EVENT_POINT_DOWN, 1000);
                    break;
                }
                case POINT_OBELISK:
                {
                    events.ScheduleEvent(EVENT_ADJUST_FACING, 1);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        if (GameObject* lens = me->FindNearestGameObject(GO_ENTRY_LENS, 100.0f))
                            lens->SetGoState(GO_STATE_ACTIVE);
                        break;
                    }
                    case EVENT_MOVE_POINT_OUT:
                    {
                        events.CancelEvent(EVENT_MOVE_POINT_OUT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10472.76f, -413.57f, 301.13f, 18.0f, 18.0f, POINT_OUT);
                        break;
                    }
                    case EVENT_POINT_DOWN:
                    {
                        events.CancelEvent(EVENT_POINT_DOWN);
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(200.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature())
                            {
                                if ((*itr)->GetEntry() == NPC_ENTRY_GENERIC_BUNNY)
                                {
                                    if ((*itr)->GetGUIDLow() == 181972)
                                    {
                                        me->CastStop();
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                    }
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10459.59f, -427.85f, 250.82f, 18.0f, 18.0f, POINT_DOWN);
                        events.ScheduleEvent(EVENT_TELEPORT_OBELISK, 10000);
                        break;
                    }
                    case EVENT_TELEPORT_OBELISK:
                    {
                        events.CancelEvent(EVENT_TELEPORT_OBELISK);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->CastSpell(playerOwner, SPELL_FADE_TO_BLACK, true);
                        me->GetMotionMaster()->MoveJump(-10517.26f, -392.48f, 509.29f, 60.0f, 60.0f, POINT_OBELISK);
                        events.ScheduleEvent(EVENT_REMOVE_PASSENGER, 15000);
                        break;
                    }
                    case EVENT_ADJUST_FACING:
                    {
                        me->SetFacingTo(0.053f);
                        events.CancelEvent(EVENT_ADJUST_FACING);
                        break;
                    }
                    case EVENT_REMOVE_PASSENGER:
                    {
                        events.CancelEvent(EVENT_REMOVE_PASSENGER);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ignition_camera_eventAI(creature);
    }
};

class spell_fire_lpac : public SpellScriptLoader
{
    public:
        spell_fire_lpac() : SpellScriptLoader("spell_fire_lpac") { }

        class spell_fire_lpac_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fire_lpac_SpellScript);

            enum npcId
            {
                NPC_ENTRY_FURIOUS_SPECTER   = 47220
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->GetTypeId() == TYPEID_UNIT)
                        {
                            if (target->GetEntry() == NPC_ENTRY_FURIOUS_SPECTER && target->GetHealthPct() <= 50)
                            {
                                target->ToCreature()->DespawnOrUnsummon(3500);
                                return SPELL_CAST_OK;
                            }
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_fire_lpac_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_fire_lpac_SpellScript();
        }
};

class npc_commander_schnottz : public CreatureScript
{
public:
   npc_commander_schnottz() : CreatureScript("npc_commander_schnottz") { }

    struct npc_commander_schnottzAI : public ScriptedAI
    {
        npc_commander_schnottzAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_SUMMON_GOBBLES    = 88117,
            SPELL_FIRE_GOBBLES      = 88118
        };

        enum pointId
        {
            POINT_TO_NOTES      = 1,
            POINT_TO_RITUAL,
            POINT_WAITING,
            POINT_GOBBER,
            POINT_TO_NOTES_FINAL
        };

        enum eventId
        {
            EVENT_START_EVENT   = 1,
            EVENT_TO_RITUAL,
            EVENT_SPAWN_RITUAL,
            EVENT_TO_WAIT,
            EVENT_FACING_GOBBLES,
            EVENT_BURN_GOBBLES,
            EVENT_DESPERATION,
            EVENT_AGAIN_TO_NOTES,
            EVENT_QUEST_COMPLETE
        };

        enum goId
        {
            GO_RITUAL_RUNE  = 206572,
            GO_WP_IDOL      = 206571
        };

        enum npcId
        {
            NPC_ENTRY_GOBBLES   = 47255
        };

        enum questId
        {
            QUEST_ENTRY_GOBBLER     = 27950
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(true);
            owner->SetPhaseMask(16, true);
            me->SetPhaseMask(16, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            if (!owner->HasAura(SPELL_UNIQUE_PHASING))
                owner->AddAura(SPELL_UNIQUE_PHASING, owner);

            if (!me->HasAura(SPELL_UNIQUE_PHASING))
                me->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_START_EVENT, 1500);
            Talk(0);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TO_NOTES:
                {
                    Talk(1);
                    events.ScheduleEvent(EVENT_TO_RITUAL, 5000);
                    break;
                }
                case POINT_TO_RITUAL:
                {
                    me->HandleEmoteCommand(EMOTE_STATE_LOOT);
                    events.ScheduleEvent(EVENT_SPAWN_RITUAL, 6000);
                    break;
                }
                case POINT_WAITING:
                {
                    events.ScheduleEvent(EVENT_FACING_GOBBLES, 1000);
                    break;
                }
                case POINT_GOBBER:
                {
                    TalkWithDelay(2000, 5);
                    TalkWithDelay(7000, 6);
                    events.ScheduleEvent(EVENT_AGAIN_TO_NOTES, 10000);
                    break;
                }
                case POINT_TO_NOTES_FINAL:
                {
                    Talk(7);
                    TalkWithDelay(6000, 8);
                    TalkWithDelay(12000, 9);
                    TalkWithDelay(18000, 10);
                    TalkWithDelay(24000, 11);
                    events.ScheduleEvent(EVENT_QUEST_COMPLETE, 26000);
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
                    case EVENT_START_EVENT:
                    {
                        events.CancelEvent(EVENT_START_EVENT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TO_NOTES, -10684.25f, 932.30f, 26.25f);
                        break;
                    }
                    case EVENT_TO_RITUAL:
                    {
                        events.CancelEvent(EVENT_TO_RITUAL);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TO_RITUAL, -10689.61f, 925.32f, 26.51f);
                        break;
                    }
                    case EVENT_SPAWN_RITUAL:
                    {
                        events.CancelEvent(EVENT_SPAWN_RITUAL);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->SummonGameObject(GO_RITUAL_RUNE, -10690.7f, 924.967f, 26.636f, -2.93f, 0, 0, -0.994521f, 0.104536f, 300);
                        me->HandleEmoteCommand(EMOTE_STATE_STAND);
                        Talk(2);
                        events.ScheduleEvent(EVENT_TO_WAIT, 2000);
                        me->SetWalk(false);
                        break;
                    }
                    case EVENT_TO_WAIT:
                    {
                        events.CancelEvent(EVENT_TO_WAIT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_WAITING, -10692.40f, 931.02f, 26.58f);
                        break;
                    }
                    case EVENT_FACING_GOBBLES:
                    {
                        me->SetFacingTo(4.98f);
                        DoCast(SPELL_SUMMON_GOBBLES);
                        events.ScheduleEvent(EVENT_BURN_GOBBLES, 8000);
                        break;
                    }
                    case EVENT_BURN_GOBBLES:
                    {
                        events.CancelEvent(EVENT_BURN_GOBBLES);
                        Talk(3);
                        if (Creature* gobbles = me->FindNearestCreature(NPC_ENTRY_GOBBLES, 30.0f, true))
                            me->CastWithDelay(3000, gobbles, SPELL_FIRE_GOBBLES);
                        TalkWithDelay(8000, 4);
                        events.ScheduleEvent(EVENT_DESPERATION, 10000);
                        break;
                    }
                    case EVENT_DESPERATION:
                    {
                        events.CancelEvent(EVENT_DESPERATION);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_GOBBER, -10690.28f, 927.04f, 26.52f);
                        break;
                    }
                    case EVENT_AGAIN_TO_NOTES:
                    {
                        events.CancelEvent(EVENT_AGAIN_TO_NOTES);
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TO_NOTES_FINAL, -10682.79f, 926.52f, 26.23f);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            {
                                playerOwner->ToPlayer()->CompleteQuest(QUEST_ENTRY_GOBBLER);
                                playerOwner->RemoveAurasDueToSpell(SPELL_UNIQUE_PHASING);
                                playerOwner->SetPhaseMask(1, true);
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_commander_schnottzAI(creature);
    }
};

class npc_schnottz_siege_tank : public CreatureScript
{
public:
    npc_schnottz_siege_tank() : CreatureScript("npc_schnottz_siege_tank") { }

    enum questId
    {
        QUEST_ENTRY_BATTLEZONE  = 27990
    };

    enum spellId
    {
        SPELL_SUMMON_DRIVER     = 88874,
        SPELL_SUMMON_SIEGE_TANK = 88870,
        SPELL_QUEST_INVISIB     = 49417
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_BATTLEZONE) == QUEST_STATUS_INCOMPLETE)
        {
            player->RemoveAurasDueToSpell(SPELL_QUEST_INVISIB);
            player->CastSpell(player, SPELL_SUMMON_DRIVER, true);
            player->CastSpell(player, SPELL_SUMMON_SIEGE_TANK, true);
            return true;
        }
        return false;
    }
};

class npc_schnottz_siege_tank_summoned : public CreatureScript
{
public:
    npc_schnottz_siege_tank_summoned() : CreatureScript("npc_schnottz_siege_tank_summoned") { }

    struct npc_schnottz_siege_tank_summonedAI : public npc_escortAI
    {
        npc_schnottz_siege_tank_summonedAI(Creature* creature) : npc_escortAI(creature) {playerQuester = NULL;}

        EventMap events;

        enum actionId
        {
            ACTION_START_WP         = 1,
            ACTION_INCREASE_COUNTER
        };

        enum questId
        {
            QUEST_ENTRY_BATTLEZONE  = 27990
        };

        enum eventId
        {
            EVENT_CHECK_QUEST_COMPLETE  = 1,
            EVENT_START_WAYPOINT,
            EVENT_RETURN_HOME
        };

        void OnCharmed(bool apply) {}

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                {
                    if (isReturning == true)
                    {
                        SetEscortPaused(true);
                        events.ScheduleEvent(EVENT_RETURN_HOME, 2000);
                    }
                    break;
                }
                case 20:
                {
                    SetNextWaypoint(1, true);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerQuester = owner;
            decrepitKilled = 0;
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_CHECK_QUEST_COMPLETE, 5000);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 8000);
            isReturning = false;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(false, true, NULL, NULL, false, true, true);
                    SetDespawnAtEnd(false);
                    break;
                }
                case ACTION_INCREASE_COUNTER:
                {
                    decrepitKilled++;
                    if (playerQuester && playerQuester != NULL)
                    {
                        if (playerQuester->GetTypeId() == TYPEID_PLAYER)
                            playerQuester->ToPlayer()->KilledMonsterCredit(47778);
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
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_QUEST_COMPLETE:
                    {
                        if (playerQuester && playerQuester != NULL)
                        {
                            if (decrepitKilled >= 7)
                            {
                                Talk(0, playerQuester->GetGUID());
                                TalkWithDelay(1000, 1, playerQuester->GetGUID());
                                TalkWithDelay(2000, 2, playerQuester->GetGUID());
                                events.CancelEvent(EVENT_CHECK_QUEST_COMPLETE);
                                events.ScheduleEvent(EVENT_RETURN_HOME, 8000);
                            }
                            else
                                events.RescheduleEvent(EVENT_CHECK_QUEST_COMPLETE, 2000);
                        }
                        break;
                    }
                    case EVENT_START_WAYPOINT:
                    {
                        events.CancelEvent(EVENT_START_WAYPOINT);
                        DoAction(ACTION_START_WP);
                        break;
                    }
                    case EVENT_RETURN_HOME:
                    {
                        events.CancelEvent(EVENT_RETURN_HOME);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerQuester;
        uint8 decrepitKilled;
        bool isReturning;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_schnottz_siege_tank_summonedAI(creature);
    }
};

class npc_schnottz_siege_turret : public CreatureScript
{
public:
    npc_schnottz_siege_turret() : CreatureScript("npc_schnottz_siege_turret") {}

    struct npc_schnottz_siege_turretAI : public ScriptedAI
    {
        npc_schnottz_siege_turretAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum eventId
        {
            EVENT_RIDE_INVOKER  = 1
        };

        enum actionId
        {
            ACTION_RIDE_INVOKER     = 1,
            ACTION_SEND_CREDIT
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1500);
            me->SetReactState(REACT_PASSIVE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_RIDE_INVOKER:
                {
                    if (Unit* myOwner = me->ToTempSummon()->GetSummoner())
                    {
                        if (Unit* ownerOwner = myOwner->ToTempSummon()->GetSummoner())
                            ownerOwner->EnterVehicle(me, 0);
                    }
                    break;
                }
                case ACTION_SEND_CREDIT:
                {
                    if (Unit* myOwner = me->ToTempSummon()->GetSummoner())
                        myOwner->ToCreature()->AI()->DoAction(2);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        DoAction(ACTION_RIDE_INVOKER);
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
        return new npc_schnottz_siege_turretAI(creature);
    }
};

class npc_decrepit_watcher : public CreatureScript
{
public:
    npc_decrepit_watcher() : CreatureScript("npc_decrepit_watcher") {}

    struct npc_decrepit_watcherAI : public ScriptedAI
    {
        npc_decrepit_watcherAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum eventId
        {
            EVENT_CAST_BLAZING_ERUPTION     = 1
        };

        enum spellId
        {
            SPELL_BLAZING_ERUPTION     = 87753
        };

        enum npcId
        {
            NPC_SIEGE_TURRET    = 47744
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CAST_BLAZING_ERUPTION, urand(4000, 12000));
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_CAST_BLAZING_ERUPTION, urand(4000, 6000));
        }

        void JustDied(Unit* who)
        {
            if (who->ToCreature())
            {
                if (who->GetEntry() == NPC_SIEGE_TURRET)
                    who->ToCreature()->AI()->DoAction(2);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_BLAZING_ERUPTION:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_CAST_BLAZING_ERUPTION, 8000);
                        DoCast(SPELL_BLAZING_ERUPTION);
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
        return new npc_decrepit_watcherAI(creature);
    }
};

class npc_commander_schnottz_awake : public CreatureScript
{
public:
    npc_commander_schnottz_awake() : CreatureScript("npc_commander_schnottz_awake") { }

    enum questId
    {
        QUEST_ENTRY_MISSED_ME_BY_ZHAT_MUCH  = 28187
    };

    #define GOSSIP_TEXT_COMMANDER_READY "Alright, let's move."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ENTRY_MISSED_ME_BY_ZHAT_MUCH) == QUEST_STATUS_INCOMPLETE)
            {
                player->RemoveAurasDueToSpell(81742);
                player->SummonCreature(creature->GetEntry(), creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_MISSED_ME_BY_ZHAT_MUCH) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COMMANDER_READY, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_commander_schnottz_awakeAI : public npc_escortAI
    {
        npc_commander_schnottz_awakeAI(Creature* creature) : npc_escortAI(creature) {playerQuester = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_START_WP  = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 6:
                {
                    if (playerQuester && playerQuester != NULL)
                    {
                        if (playerQuester->GetTypeId() == TYPEID_PLAYER)
                            playerQuester->ToPlayer()->KilledMonsterCredit(47957);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerQuester = owner;
            me->SetReactState(REACT_PASSIVE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            owner->AddAura(SPELL_UNIQUE_PHASING, owner);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->RemoveAurasDueToSpell(89196);
            me->SetFacingToObject(owner);
            TalkWithDelay(1500, 0, owner->GetGUID());
            me->SetWalk(true);
            events.ScheduleEvent(EVENT_START_WP, 6000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            npc_escortAI::UpdateAI(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_WP:
                    {
                        events.CancelEvent(EVENT_START_WP);
                        Start(false, false, NULL, NULL, false, false, true);
                        if (playerQuester && playerQuester != NULL)
                        {
                            TalkWithDelay(1000, 1, playerQuester->GetGUID());
                            TalkWithDelay(12000, 2, playerQuester->GetGUID());
                            TalkWithDelay(24000, 3, playerQuester->GetGUID());
                            TalkWithDelay(38000, 4, playerQuester->GetGUID());
                            TalkWithDelay(51000, 5, playerQuester->GetGUID());
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerQuester;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_commander_schnottz_awakeAI(creature);
    }
};

class npc_harrison_jones_tailgunner : public CreatureScript
{
public:
    npc_harrison_jones_tailgunner() : CreatureScript("npc_harrison_jones_tailgunner") { }

    enum questId
    {
        QUEST_ENTRY_TAILGUNNER  = 27905
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_SUMMON_BURLY      = 87675,
        SPELL_SUMMON_HARRISON   = 87673,
        SPELL_SUMMON_CLONE      = 87668,
        SPELL_SUMMON_TROOPER    = 87681,
        SPELL_SUMMON_BOMBER     = 87682,
        SPELL_SUMMON_CAMERA     = 87684,
        SPELL_QUEST_INVISIB     = 49416
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_TAILGUNNER)
        {
            player->RemoveAurasDueToSpell(SPELL_QUEST_INVISIB);
            player->SetPhaseMask(308, true);
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->CastWithDelay(1000, player, SPELL_SUMMON_CAMERA, true);
            player->CastSpell(player, SPELL_SUMMON_BURLY, true);
            player->CastSpell(player, SPELL_SUMMON_HARRISON, true);
            player->CastSpell(player, SPELL_SUMMON_CLONE, true);
            player->CastSpell(player, SPELL_SUMMON_TROOPER, true);
            player->CastSpell(player, SPELL_SUMMON_BOMBER, true);
            return false;
        }
        return true;
    }
};

class npc_tailgunner_camera : public CreatureScript
{
public:
   npc_tailgunner_camera() : CreatureScript("npc_tailgunner_camera") { }

    struct npc_tailgunner_cameraAI : public ScriptedAI
    {
        npc_tailgunner_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_FADE_TO_BLACK         = 89315
        };

        enum pointId
        {
            POINT_FAR           = 1,
            POINT_BLOODY,
            POINT_BLOODY_FINAL,
            POINT_TAKEOFF,
            POINT_TO_TURRET
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_SWITCH_TARGET,
            EVENT_JUMP_TO_POS_1,
            EVENT_FOCUS_BURLY,
            EVENT_MOVE_BLOODY,
            EVENT_MOVE_TAKEOFF,
            EVENT_MOVE_TO_TURRET
        };

        enum npcId
        {
            NPC_ENTRY_PLAYER_CLONE  = 47049,
            NPC_ENTRY_HARRISON      = 47050,
            NPC_ENTRY_BURLY         = 47051,
            NPC_ENTRY_BOMBER        = 47054
        };

        enum actionId
        {
            ACTION_MOVE_BLOODY  = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_BLOODY:
                {
                    events.ScheduleEvent(EVENT_MOVE_BLOODY, 1);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_BLOODY:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                if ((*itr)->GetEntry() == NPC_ENTRY_BOMBER)
                                    (*itr)->ToCreature()->AI()->DoAction(1);
                            }
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->EnterVehicle(me, 0);

                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_HARRISON)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_SWITCH_TARGET, 5000);
                        break;
                    }
                    case EVENT_SWITCH_TARGET:
                    {
                        events.CancelEvent(EVENT_SWITCH_TARGET);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_PLAYER_CLONE)
                                    {
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_JUMP_TO_POS_1, 3000);
                        break;
                    }
                    case EVENT_JUMP_TO_POS_1:
                    {
                        events.CancelEvent(EVENT_JUMP_TO_POS_1);
                        me->GetMotionMaster()->MoveJump(-10369.58f, -278.79f, 337.74f, 10.0f, 10.0f, POINT_FAR);
                        events.ScheduleEvent(EVENT_FOCUS_BURLY, 10000);
                        break;
                    }
                    case EVENT_FOCUS_BURLY:
                    {
                        events.CancelEvent(EVENT_FOCUS_BURLY);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_BURLY)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10376.77f, -274.46f, 338.98f, 8.0f, 8.0f, POINT_BLOODY);
                        break;
                    }
                    case EVENT_MOVE_BLOODY:
                    {
                        events.CancelEvent(EVENT_MOVE_BLOODY);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10387.95f, -267.76f, 340.82f, 10.0f, 10.0f, POINT_BLOODY_FINAL);
                        events.ScheduleEvent(EVENT_MOVE_TAKEOFF, 3500);
                        break;
                    }
                    case EVENT_MOVE_TAKEOFF:
                    {
                        events.CancelEvent(EVENT_MOVE_TAKEOFF);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(100.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_BOMBER)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10450.83f, -198.69f, 345.436f, 12.0f, 12.0f, POINT_TAKEOFF);
                        events.ScheduleEvent(EVENT_MOVE_TO_TURRET, 6000);
                        break;
                    }
                    case EVENT_MOVE_TO_TURRET:
                    {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10530.70f, -297.86f, 343.34f, 18.5f, 18.5f, POINT_TO_TURRET);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tailgunner_cameraAI(creature);
    }
};

class npc_tailgunner_clone : public CreatureScript
{
public:
   npc_tailgunner_clone() : CreatureScript("npc_tailgunner_clone") { }

    struct npc_tailgunner_cloneAI : public ScriptedAI
    {
        npc_tailgunner_cloneAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CLONE_CASTER          = 87671,
            SPELL_BURLY_DAZED           = 87691
        };

        enum pointId
        {
            POINT_TROOPER   = 1,
            POINT_BURLY,
            POINT_TO_PLANE
        };

        enum eventId
        {
            EVENT_FIRST_MOVE    = 1,
            EVENT_BEHIND_BURLY,
            EVENT_DAZE_BURLY,
            EVENT_MOVE_TO_PLANE,
            EVENT_STOLE_WEAPON
        };

        enum npcId
        {
            NPC_ENTRY_BURLY         = 47051,
            NPC_ENTRY_TROOPER       = 47052,
            NPC_ENTRY_HARRISON      = 47050,
            NPC_ENTRY_CAMERA        = 47055
        };

        enum actionId
        {
            ACTION_FIRST_MOVE   = 1
        };

        class moveHarrison : public BasicEvent
        {
            public:
                explicit moveHarrison(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->GetMotionMaster()->MovementExpired(false);
                creature->GetMotionMaster()->MovePoint(1, -10369.49f, -303.01f, 336.59f);
                creature->DespawnOrUnsummon(4000);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->CastSpell(me, SPELL_CLONE_CASTER, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_FIRST_MOVE:
                {
                    events.ScheduleEvent(EVENT_FIRST_MOVE, 500);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            me->PlayDirectSound(23677, playerOwner->ToPlayer());
                    }
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TROOPER:
                {
                    me->SetFacingTo(2.34f);
                    me->HandleEmoteCommand(EMOTE_STATE_LOOT);
                    events.ScheduleEvent(EVENT_STOLE_WEAPON, 2500);
                    break;
                }
                case POINT_BURLY:
                {
                    me->SetFacingTo(0.39f);
                    events.ScheduleEvent(EVENT_DAZE_BURLY, 2000);
                    break;
                }
                case POINT_TO_PLANE:
                {
                    me->DespawnOrUnsummon(1000);
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
                    case EVENT_FIRST_MOVE:
                    {
                        events.CancelEvent(EVENT_FIRST_MOVE);
                        me->SetFacingTo(2.34f);
                        me->GetMotionMaster()->MovePoint(POINT_TROOPER, -10388.88f, -275.22f, 336.67f);
                        break;
                    }
                    case EVENT_STOLE_WEAPON:
                    {
                        events.CancelEvent(EVENT_STOLE_WEAPON);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_TROOPER)
                                        (*itr)->ToCreature()->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 0);
                                }
                            }
                        }
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 31824);
                        events.ScheduleEvent(EVENT_BEHIND_BURLY, 1500);
                        break;
                    }
                    case EVENT_BEHIND_BURLY:
                    {
                        events.CancelEvent(EVENT_BEHIND_BURLY);
                        me->HandleEmoteCommand(EMOTE_STATE_STAND);
                        me->GetMotionMaster()->MovePoint(POINT_BURLY, -10390.66f, -284.33f, 336.67f);
                        break;
                    }
                    case EVENT_DAZE_BURLY:
                    {
                        events.CancelEvent(EVENT_DAZE_BURLY);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_ENTRY_BURLY:
                                        {
                                            (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                                            (*itr)->CastWithDelay(500, (*itr), SPELL_BURLY_DAZED, true);
                                            break;
                                        }
                                        case NPC_ENTRY_HARRISON:
                                        {
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(1500, 0, playerOwner->GetGUID());
                                            (*itr)->m_Events.AddEvent(new moveHarrison((*itr)->ToCreature()), ((*itr))->m_Events.CalculateTime(2500));
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_PLANE, 3000);
                        break;
                    }
                    case EVENT_MOVE_TO_PLANE:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_PLANE);
                        me->GetMotionMaster()->MovePoint(POINT_TO_PLANE, -10389.56f, -311.61f, 336.59f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tailgunner_cloneAI(creature);
    }
};

class npc_tailgunner_bomber : public CreatureScript
{
public:
    npc_tailgunner_bomber() : CreatureScript("npc_tailgunner_bomber") { }

    struct npc_tailgunner_bomberAI : public npc_escortAI
    {
        npc_tailgunner_bomberAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_INFORM_TAILGUNNER_RIDE    = 1,
            EVENT_CALL_FIGHTER,
            EVENT_REMOVE_ALL_PASSENGERS
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum npcId
        {
            NPC_ENTRY_BURLY         = 47051,
            NPC_ENTRY_CAMERA        = 47055,
            NPC_ENTRY_BLOOD_LARGE   = 49414,
            NPC_ENTRY_BLOOD_TINY    = 49415
        };

        enum spellId
        {
            SPELL_BLOOD_EVERYWHERE  = 80701,
            SPELL_CALL_FIGHTER      = 88706
        };

        class onlyBoots : public BasicEvent
        {
            public:
                explicit onlyBoots(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->SetControlled(true, UNIT_STATE_ROOT);
                creature->SetDisplayId(35400);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->DespawnOrUnsummon(20000);
                return true;
            }

        private:
            Creature* creature;
        };

        class poolOfBlood : public BasicEvent
        {
            public:
                explicit poolOfBlood(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                if (Unit* owner = creature->ToTempSummon()->GetSummoner())
                {
                    owner->SummonCreature(NPC_ENTRY_BLOOD_LARGE, -10388.50f, -283.31f, 336.67f, 3.45f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    owner->SummonCreature(NPC_ENTRY_BLOOD_TINY, -10389.79f, -286.48f, 336.67f, 0.94f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    owner->SummonCreature(NPC_ENTRY_BLOOD_TINY, -10390.29f, -284.27f, 336.67f, 0.33f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    owner->SummonCreature(NPC_ENTRY_BLOOD_TINY, -10388.00f, -281.10f, 336.67f, 4.59f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    owner->SummonCreature(NPC_ENTRY_BLOOD_TINY, -10389.00f, -279.53f, 336.67f, 4.90f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                }
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:     // Enable Burly
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_ENTRY_BURLY:
                                    {
                                        (*itr)->SetFacingTo(5.14f);
                                        (*itr)->HandleEmoteCommand(EMOTE_STATE_COWER);
                                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                            (*itr)->PlayDirectSound(14991, playerOwner->ToPlayer());
                                        (*itr)->CastWithDelay(2000, (*itr), SPELL_BLOOD_EVERYWHERE, true);
                                        (*itr)->CastWithDelay(1950, (*itr), SPELL_BLOOD_EVERYWHERE, true);
                                        (*itr)->m_Events.AddEvent(new onlyBoots((*itr)->ToCreature()), ((*itr))->m_Events.CalculateTime(2500));
                                        (*itr)->m_Events.AddEvent(new poolOfBlood((*itr)->ToCreature()), ((*itr))->m_Events.CalculateTime(2600));
                                        break;
                                    }
                                    case NPC_ENTRY_CAMERA:
                                    {
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    me->SetSpeed(MOVE_WALK, 1.75f, true);
                    break;
                }
                case 3:
                {
                    SetRun(true);
                    me->SetSpeed(MOVE_RUN, 2.2f, true);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            me->PlayDirectSound(23678, playerOwner->ToPlayer());
                    }
                    break;
                }
                case 4:
                {
                    me->SetCanFly(true);
                    events.ScheduleEvent(EVENT_INFORM_TAILGUNNER_RIDE, 2000);
                    break;
                }
                case 5:
                {
                    events.ScheduleEvent(EVENT_CALL_FIGHTER, 2000);
                    break;
                }
                case 10:
                {
                    events.CancelEvent(EVENT_CALL_FIGHTER);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            playerOwner->ToPlayer()->KilledMonsterCredit(47054);
                    }
                    break;
                }
                case 11:
                {
                    events.ScheduleEvent(EVENT_REMOVE_ALL_PASSENGERS, 2000);
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
                case ACTION_START_WP:
                {
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
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
                    case EVENT_INFORM_TAILGUNNER_RIDE:
                    {
                        events.CancelEvent(EVENT_INFORM_TAILGUNNER_RIDE);
                        if (Unit* turret = me->GetVehicleKit()->GetPassenger(2))
                        {
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld() && playerOwner->GetVehicleBase())
                                playerOwner->GetVehicleBase()->GetVehicleKit()->RemoveAllPassengers();
                            playerOwner->EnterVehicle(turret, 0);
                        }
                        break;
                    }
                    case EVENT_CALL_FIGHTER:
                    {
                        events.RescheduleEvent(EVENT_CALL_FIGHTER, 6000);
                        DoCast(SPELL_CALL_FIGHTER);
                        break;
                    }
                    case EVENT_REMOVE_ALL_PASSENGERS:
                    {
                        events.CancelEvent(EVENT_REMOVE_ALL_PASSENGERS);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(1500);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tailgunner_bomberAI(creature);
    }
};

class npc_tailgunner_fighter : public CreatureScript
{
public:
   npc_tailgunner_fighter() : CreatureScript("npc_tailgunner_fighter") { }

    struct npc_tailgunner_fighterAI : public ScriptedAI
    {
        npc_tailgunner_fighterAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_MISSILES_TAKEN        = 88650,
            SPELL_CANNON_HIT            = 88661,
            SPELL_CANNON_IMPACT         = 88698,
            SPELL_HOMING_ROCKET         = 93480,
            SPELL_EXPLODE_AND_BURN      = 72942
        };

        enum eventId
        {
            EVENT_FOLLOW_INVOKER    = 1,
            EVENT_RESTORE_SPEED,
            EVENT_HOMING_ROCKET
        };

        enum pointId
        {
            POINT_CRASHED   = 1
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_MISSILES_TAKEN:
                {
                    if (roll_chance_f(35.0f))
                    {
                        events.Reset();
                        me->CastSpell(me, SPELL_EXPLODE_AND_BURN);
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveJump(me->GetPositionX()-2, me->GetPositionY()+10, me->GetPositionZ()-80, 16.5f, 16.5f, POINT_CRASHED);
                        me->DespawnOrUnsummon(10000);
                    }
                    break;
                }
                case SPELL_CANNON_HIT:
                {
                    DoCast(SPELL_CANNON_IMPACT);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_FOLLOW_INVOKER, 1000);
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 10.0f, true);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FOLLOW_INVOKER:
                    {
                        events.CancelEvent(EVENT_FOLLOW_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveFollow(playerOwner, 20.0f, urand(0, 45));
                            events.ScheduleEvent(EVENT_RESTORE_SPEED, 2000);
                        }
                        break;
                    }
                    case EVENT_RESTORE_SPEED:
                    {
                        events.CancelEvent(EVENT_RESTORE_SPEED);
                        if (!playerOwner || playerOwner == NULL || !playerOwner->IsInWorld())
                        {
                            me->DespawnOrUnsummon(1);
                            break;
                        }

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (me->IsWithinCombatRange(playerOwner, 21.0f))
                            {
                                me->SetSpeed(MOVE_RUN, 2.2f, true);
                                events.ScheduleEvent(EVENT_HOMING_ROCKET, 1000);
                            }
                            else
                                events.RescheduleEvent(EVENT_RESTORE_SPEED, 2000);
                        }
                        break;
                    }
                    case EVENT_HOMING_ROCKET:
                    {
                        events.RescheduleEvent(EVENT_HOMING_ROCKET, urand(3000, 6000));
                        DoCast(SPELL_HOMING_ROCKET);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tailgunner_fighterAI(creature);
    }
};

class npc_commander_firing_squad : public CreatureScript
{
public:
    npc_commander_firing_squad() : CreatureScript("npc_commander_firing_squad") { }

    enum questId
    {
        QUEST_ENTRY_FIRING_SQUAD    = 28267
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_SUMMON_COMMANDER  = 93979,
        SPELL_SUMMON_CAMERA     = 93982,
        SPELL_SUMMON_CLONE      = 93976,
        SPELL_SUMMON_EMISSARY_1 = 93980,
        SPELL_SUMMON_EMISSARY_2 = 93981,
        SPELL_SUMMON_HARRISON   = 94010,
        SPELL_SUMMON_SWING_VEH  = 94023,
        SPELL_SUMMON_KNOCK_VEH  = 94031,
        SPELL_FADE_TO_BLACK     = 88629
    };

    #define GOSSIP_TEXT_SQUAD_READY "Uhhh, I suppose I'm ready..."

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ENTRY_FIRING_SQUAD) == QUEST_STATUS_INCOMPLETE)
            {
                player->RemoveAurasDueToSpell(81742);
                player->SetPhaseMask(64, true);
                if (!player->HasAura(SPELL_UNIQUE_PHASING))
                    player->AddAura(SPELL_UNIQUE_PHASING, player);
                player->AddAura(SPELL_FADE_TO_BLACK, player);
                player->CastSpell(player, SPELL_SUMMON_COMMANDER, true);
                player->CastSpell(player, SPELL_SUMMON_CAMERA, true);
                player->CastSpell(player, SPELL_SUMMON_CLONE, true);
                player->CastSpell(player, SPELL_SUMMON_EMISSARY_1, true);
                player->CastSpell(player, SPELL_SUMMON_EMISSARY_2, true);
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_FIRING_SQUAD) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SQUAD_READY, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }
};

class npc_firing_squad_clone : public CreatureScript
{
public:
   npc_firing_squad_clone() : CreatureScript("npc_firing_squad_clone") { }

    struct npc_firing_squad_cloneAI : public npc_escortAI
    {
        npc_firing_squad_cloneAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CLONE_CASTER          = 93996
        };

        enum pointId
        {
        };

        enum eventId
        {
        };

        enum npcId
        {
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->CastSpell(me, SPELL_CLONE_CASTER, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
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
                case 7:
                {
                    me->SetFacingTo(1.01f);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_firing_squad_cloneAI(creature);
    }
};

class npc_firing_squad_camera : public CreatureScript
{
public:
   npc_firing_squad_camera() : CreatureScript("npc_firing_squad_camera") { }

    struct npc_firing_squad_cameraAI : public ScriptedAI
    {
        npc_firing_squad_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_SUMMON_HARRISON       = 94010,
            SPELL_SUMMON_SWING_VEH      = 94023,
            SPELL_SUMMON_KNOCK_VEH      = 94031
        };

        enum pointId
        {
            POINT_POS_1     = 1,
            POINT_POS_2,
            POINT_POS_3,
            POINT_HARRISON
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER  = 1,
            EVENT_SWITCH_TARGET,
            EVENT_MOVE_TO_POS_1,
            EVENT_MOVE_TO_POS_2,
            EVENT_MOVE_TO_POS_3,
            EVENT_SUMMON_HARRISON,
            EVENT_POINT_HARRISON,
            EVENT_QUEST_COMPLETE
        };

        enum npcId
        {
            NPC_ENTRY_COMMANDER     = 49467,
            NPC_ENTRY_HARRISON      = 50652
        };

        enum actionId
        {
            ACTION_MOVE_HARRISON    = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_HARRISON:
                {
                    events.ScheduleEvent(EVENT_SUMMON_HARRISON, 1000);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 6000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_POS_1:
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_POS_2, 1000);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->EnterVehicle(me, 0);

                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_COMMANDER)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_POS_1, 2000);
                        break;
                    }
                    case EVENT_MOVE_TO_POS_1:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_POS_1);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10560.79f, 1043.71f, 42.10f, 2.0f, 2.0f, POINT_POS_1);
                        break;
                    }
                    case EVENT_MOVE_TO_POS_2:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_POS_2);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10538.71f, 1003.09f, 48.97f, 2.0f, 2.0f, POINT_POS_2);
                        events.ScheduleEvent(EVENT_MOVE_TO_POS_3, 7000);
                        break;
                    }
                    case EVENT_MOVE_TO_POS_3:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_POS_3);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10522.08f, 1001.96f, 50.24f, 2.0f, 2.0f, POINT_POS_3);
                        break;
                    }
                    case EVENT_SUMMON_HARRISON:
                    {
                        events.CancelEvent(EVENT_SUMMON_HARRISON);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_HARRISON, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_SWING_VEH, true);
                        }
                        events.ScheduleEvent(EVENT_POINT_HARRISON, 2000);
                        break;
                    }
                    case EVENT_POINT_HARRISON:
                    {
                        events.CancelEvent(EVENT_POINT_HARRISON);
                        me->CastStop();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_HARRISON)
                                    {
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                    }
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10557.34f, 978.11f, 43.19f, 20.0f, 20.0f, POINT_HARRISON);
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 24000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                playerOwner->ToPlayer()->KilledMonsterCredit(48189);
                        }
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_firing_squad_cameraAI(creature);
    }
};

class npc_firing_squad_commander_summon : public CreatureScript
{
public:
    npc_firing_squad_commander_summon() : CreatureScript("npc_firing_squad_commander_summon") { }

    struct npc_firing_squad_commander_summonAI : public npc_escortAI
    {
        npc_firing_squad_commander_summonAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_START_WAYPOINT        = 1,
            EVENT_CLONE_TALK,
            EVENT_INFORM_CAMERA_HARRISON
        };

        enum actionId
        {
            ACTION_START_WP     = 1,
            ACTION_FINALIZE
        };

        enum npcId
        {
            NPC_ENTRY_CLONE         = 50630,
            NPC_ENTRY_EMISSARY_01   = 50642,
            NPC_ENTRY_EMISSARY_02   = 50639,
            NPC_ENTRY_CAMERA        = 50408
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        enum pointId
        {
            POINT_AWAY  = 1
        };

        void InformSquadToMove()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(50.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_ENTRY_CLONE:
                            case NPC_ENTRY_EMISSARY_01:
                            case NPC_ENTRY_EMISSARY_02:
                            {
                                (*itr)->SetWalk(true);
                                (*itr)->ToCreature()->AI()->DoAction(1);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
        }

        void InformCameraHarrison()
        {
            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                std::list<Unit*> targets;
                Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(100.0f, searcher);
                for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                    {
                        switch ((*itr)->GetEntry())
                        {
                            case NPC_ENTRY_CAMERA:
                            {
                                (*itr)->ToCreature()->AI()->DoAction(1);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 6000);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 6:
                {
                    TalkWithDelay(1000, 7);
                    TalkWithDelay(10000, 8);
                    TalkWithDelay(18000, 9);
                    TalkWithDelay(24000, 10);
                    TalkWithDelay(38000, 11);
                    TalkWithDelay(44000, 12);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 67434);
                    events.ScheduleEvent(EVENT_INFORM_CAMERA_HARRISON, 40000);
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
                case ACTION_START_WP:
                {
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
                    InformSquadToMove();
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        TalkWithDelay(2000, 0, playerOwner->GetGUID());
                        TalkWithDelay(10000, 1, playerOwner->GetGUID());
                        TalkWithDelay(18000, 2, playerOwner->GetGUID());
                        TalkWithDelay(26000, 3, playerOwner->GetGUID());
                        TalkWithDelay(33000, 4, playerOwner->GetGUID());
                        TalkWithDelay(41000, 5, playerOwner->GetGUID());
                        TalkWithDelay(52000, 6, playerOwner->GetGUID());
                    }
                    events.ScheduleEvent(EVENT_CLONE_TALK, 30000);
                    break;
                }
                case ACTION_FINALIZE:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        TalkWithDelay(1000, 13, playerOwner->GetGUID());
                    me->SetWalk(false);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(POINT_AWAY, -10602.01f, 977.27f, 34.74f);
                    me->DespawnOrUnsummon(10000);
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
                    case EVENT_CLONE_TALK:
                    {
                        events.CancelEvent(EVENT_CLONE_TALK);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_ENTRY_CLONE:
                                        {
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(1000, 0, playerOwner->GetGUID());
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_INFORM_CAMERA_HARRISON:
                    {
                        events.CancelEvent(EVENT_INFORM_CAMERA_HARRISON);
                        InformCameraHarrison();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_firing_squad_commander_summonAI(creature);
    }
};

class npc_firing_squad_emissary_01 : public CreatureScript
{
public:
    npc_firing_squad_emissary_01() : CreatureScript("npc_firing_squad_emissary_01") { }

    struct npc_firing_squad_emissary_01AI : public npc_escortAI
    {
        npc_firing_squad_emissary_01AI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_START_WAYPOINT    = 1,
            EVENT_TAKEOFF,
            EVENT_TRANSFORM,
            EVENT_MOVE_AWAY
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum npcId
        {
            NPC_ENTRY_CLONE         = 50630
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_DRAGON_SMOKE      = 94004
        };

        enum pointId
        {
            POINT_TAKEOFF   = 7,
            POINT_AWAY
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 7000);
            me->SetDisableGravity(false);
            me->SetCanFly(false);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 6:
                {
                    me->SetFacingTo(1.28f);
                    DoCast(SPELL_DRAGON_SMOKE);
                    events.ScheduleEvent(EVENT_TRANSFORM, 10000);
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
                case ACTION_START_WP:
                {
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
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
                    case EVENT_TAKEOFF:
                    {
                        events.CancelEvent(EVENT_TAKEOFF);
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 30.0f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        events.ScheduleEvent(EVENT_MOVE_AWAY, 2000);
                        break;
                    }
                    case EVENT_TRANSFORM:
                    {
                        events.CancelEvent(EVENT_TRANSFORM);
                        me->SetDisplayId(24139);
                        events.ScheduleEvent(EVENT_TAKEOFF, 7000);
                        TalkWithDelay(3000, 0);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        me->SetWalk(false);
                        me->SetSpeed(MOVE_RUN, 2.2f, true);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -10447.15f, 908.85f, 73.92f);
                        me->DespawnOrUnsummon(30000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_firing_squad_emissary_01AI(creature);
    }
};

class npc_firing_squad_emissary_02 : public CreatureScript
{
public:
    npc_firing_squad_emissary_02() : CreatureScript("npc_firing_squad_emissary_02") { }

    struct npc_firing_squad_emissary_02AI : public npc_escortAI
    {
        npc_firing_squad_emissary_02AI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_START_WAYPOINT    = 1,
            EVENT_TAKEOFF,
            EVENT_DRAGON_FIRE,
            EVENT_TRANSFORM,
            EVENT_MOVE_AWAY
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum npcId
        {
            NPC_ENTRY_CLONE         = 50630
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_DRAGON_SMOKE      = 94004
        };

        enum pointId
        {
            POINT_TAKEOFF   = 7,
            POINT_AWAY
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 7000);
            me->SetDisableGravity(false);
            me->SetCanFly(false);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 6:
                {
                    me->SetFacingTo(0.66f);
                    events.ScheduleEvent(EVENT_DRAGON_FIRE, 7000);
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
                case ACTION_START_WP:
                {
                    Start(false, false, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
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
                    case EVENT_TAKEOFF:
                    {
                        events.CancelEvent(EVENT_TAKEOFF);
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 30.0f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        events.ScheduleEvent(EVENT_MOVE_AWAY, 2000);
                        break;
                    }
                    case EVENT_DRAGON_FIRE:
                    {
                        DoCast(SPELL_DRAGON_SMOKE);
                        events.ScheduleEvent(EVENT_TRANSFORM, 10000);
                        break;
                    }
                    case EVENT_TRANSFORM:
                    {
                        events.CancelEvent(EVENT_TRANSFORM);
                        me->SetDisplayId(24139);
                        events.ScheduleEvent(EVENT_TAKEOFF, 4000);
                        break;
                    }
                    case EVENT_MOVE_AWAY:
                    {
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        me->SetWalk(false);
                        me->SetSpeed(MOVE_RUN, 2.2f, true);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -10422.12f, 947.49f, 95.84f);
                        me->DespawnOrUnsummon(30000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_firing_squad_emissary_02AI(creature);
    }
};

class npc_firing_squad_harrison : public CreatureScript
{
public:
   npc_firing_squad_harrison() : CreatureScript("npc_firing_squad_harrison") { }

    struct npc_firing_squad_harrisonAI : public ScriptedAI
    {
        npc_firing_squad_harrisonAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_ROPE_BEAM             = 63413,
            SPELL_DUST_EXPLOSION        = 94026
        };

        enum pointId
        {
            POINT_SCHNOTTZ  = 1
        };

        enum eventId
        {
            EVENT_JUMP_ROPE             = 1,
            EVENT_INFORM_CAMERA_ROTATE
        };

        enum npcId
        {
            NPC_ENTRY_SWING_VEHICLE     = 51097,
            NPC_ENTRY_COMMANDER         = 49467,
            NPC_ENTRY_CAMERA            = 50408,
            NPC_ENTRY_CLONE             = 50630
        };

        enum actionId
        {
            ACTION_START_EVENT  = 1
        };

        class finalizeSchnottz : public BasicEvent
        {
            public:
                explicit finalizeSchnottz(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->SetFacingTo(0.55f);
                creature->AI()->DoAction(2);
                return true;
            }

        private:
            Creature* creature;
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_EVENT:
                {
                    events.ScheduleEvent(EVENT_JUMP_ROPE, 4000);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_SCHNOTTZ:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(200.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_ENTRY_COMMANDER:
                                    {
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                        (*itr)->GetMotionMaster()->MoveJump(-10548.68f, 976.53f, 40.94f, 12.5f, 12.5f, 10);
                                        (*itr)->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 0);
                                        TalkWithDelay(3000, 0);
                                        events.ScheduleEvent(EVENT_INFORM_CAMERA_ROTATE, 5000);
                                        (*itr)->m_Events.AddEvent(new finalizeSchnottz((*itr)->ToCreature()), ((*itr))->m_Events.CalculateTime(10000));
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    me->CastStop();
                    DoCast(SPELL_DUST_EXPLOSION);
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
                    case EVENT_JUMP_ROPE:
                    {
                        events.CancelEvent(EVENT_JUMP_ROPE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_ENTRY_SWING_VEHICLE:
                                        {
                                            me->CastSpell((*itr), SPELL_ROPE_BEAM);
                                            (*itr)->CastSpell(me, SPELL_ROPE_BEAM);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        me->GetMotionMaster()->MoveJump(-10534.22f, 984.01f, 44.02f, 15.0f, 15.0f, POINT_SCHNOTTZ);
                        break;
                    }
                    case EVENT_INFORM_CAMERA_ROTATE:
                    {
                        events.CancelEvent(EVENT_INFORM_CAMERA_ROTATE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_ENTRY_CAMERA:
                                        {
                                            (*itr)->GetMotionMaster()->MovementExpired(false);
                                            (*itr)->GetMotionMaster()->MoveJump(-10526.51f, 990.83f, 48.27f, 25.0f, 25.0f, 10);
                                            break;
                                        }
                                        case NPC_ENTRY_CLONE:
                                        {
                                            (*itr)->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, 67434);
                                            (*itr)->SetFacingTo(2.48f);
                                            (*itr)->HandleEmoteCommand(EMOTE_STATE_READY1H);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_firing_squad_harrisonAI(creature);
    }
};

class npc_two_tents_caravan : public CreatureScript
{
public:
    npc_two_tents_caravan() : CreatureScript("npc_two_tents_caravan") { }

    struct npc_two_tents_caravanAI : public npc_escortAI
    {
        npc_two_tents_caravanAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_START_WAYPOINT    = 1
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };
        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_START_WAYPOINT, 5000);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 18:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                        {
                            playerOwner->ToPlayer()->KilledMonsterCredit(48431);
                            playerOwner->AddAura(93684, playerOwner);
                        }
                    }
                    if (me->GetVehicleKit())
                        me->GetVehicleKit()->RemoveAllPassengers();

                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        playerOwner->NearTeleportTo(-8935.23f, 611.53f, 151.65f, 5.55f);

                    me->DespawnOrUnsummon(3000);
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
                case ACTION_START_WP:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        playerOwner->EnterVehicle(me, 1);
                    Start(false, true, NULL, NULL, false, false, true);
                    SetDespawnAtEnd(false);
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
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_two_tents_caravanAI(creature);
    }
};

class npc_two_tents_sullah : public CreatureScript
{
public:
    npc_two_tents_sullah() : CreatureScript("npc_two_tents_sullah") { }

    enum questId
    {
        QUEST_ENTRY_TWO_TENTS   = 28274
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_SUMMON_CARAVAN    = 93641,
        SPELL_FADE_TO_BLACK     = 88629
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_TWO_TENTS)
        {
            player->SetPhaseMask(376, true);
            player->CastSpell(player, SPELL_FADE_TO_BLACK, true);
            player->CastSpell(player, SPELL_SUMMON_CARAVAN, true);
            return false;
        }
        return true;
    }

    struct npc_two_tents_sullahAI : public ScriptedAI
    {
        npc_two_tents_sullahAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        void IsSummonedBy(Unit* owner)
        {
            if (owner && owner->ToTempSummon())
            {
                if (Unit* caravanSummoner = owner->ToTempSummon()->GetSummoner())
                {
                    playerOwner = caravanSummoner;
                    caravanSummoner->AddAura(SPELL_UNIQUE_PHASING, me);
                }
            }

            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
            {
                TalkWithDelay(12000, 0, playerOwner->GetGUID());
                TalkWithDelay(20000, 1, playerOwner->GetGUID());
                TalkWithDelay(28000, 2, playerOwner->GetGUID());
                TalkWithDelay(35000, 3, playerOwner->GetGUID());
                TalkWithDelay(48000, 4, playerOwner->GetGUID());
                TalkWithDelay(56000, 5, playerOwner->GetGUID());
                TalkWithDelay(64000, 6, playerOwner->GetGUID());
                TalkWithDelay(70000, 7, playerOwner->GetGUID());
                TalkWithDelay(80000, 8, playerOwner->GetGUID());
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_two_tents_sullahAI(creature);
    }
};

class spell_sullah_camel_harness : public SpellScriptLoader
{
    public:
        spell_sullah_camel_harness() : SpellScriptLoader("spell_sullah_camel_harness") { }

        class spell_sullah_camel_harness_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sullah_camel_harness_SpellScript);

            enum npcId
            {
                NPC_ENTRY_WILD_CAMEL    = 51193
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->GetTypeId() == TYPEID_UNIT)
                        {
                            if (target->GetEntry() == NPC_ENTRY_WILD_CAMEL && target->GetHealthPct() <= 50)
                                return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_sullah_camel_harness_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sullah_camel_harness_SpellScript();
        }
};

class spell_camel_tow_completion : public SpellScriptLoader
{
    public:
        spell_camel_tow_completion() : SpellScriptLoader("spell_camel_tow_completion") { }

        class spell_camel_tow_completion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_camel_tow_completion_SpellScript);

            enum npcId
            {
                NPC_ENTRY_WILD_CAMEL    = 51197
            };

            void HandleDespawnSummons()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnitInObjectRangeCheck u_check(caster, 100.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(100.0f, searcher);
                    for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == caster)
                        {
                            if ((*itr)->GetEntry() == NPC_ENTRY_WILD_CAMEL)
                                (*itr)->ToCreature()->DespawnOrUnsummon(1);
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_camel_tow_completion_SpellScript::HandleDespawnSummons);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_camel_tow_completion_SpellScript();
        }
};

class npc_captured_wild_camel : public CreatureScript
{
public:
    npc_captured_wild_camel() : CreatureScript("npc_captured_wild_camel") { }

    struct npc_captured_wild_camelAI : public ScriptedAI
    {
        npc_captured_wild_camelAI(Creature* creature) : ScriptedAI(creature) {}

        enum spellId
        {
            SPELL_ROPE_BEAM     = 63413
        };

        void IsSummonedBy(Unit* owner)
        {
            me->CastSpell(owner, SPELL_ROPE_BEAM, true);
            me->ClearUnitState(UNIT_STATE_CASTING);
            me->GetMotionMaster()->MoveFollow(owner, 3.0f, frand(0, 4.5f));
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_wild_camelAI(creature);
    }
};

class spell_sullah_pigmy_pen : public SpellScriptLoader
{
    public:
        spell_sullah_pigmy_pen() : SpellScriptLoader("spell_sullah_pigmy_pen") { }

        class spell_sullah_pigmy_pen_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sullah_pigmy_pen_SpellScript);

            enum npcId
            {
                NPC_ENTRY_SAND_PIGMY    = 45190
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->GetTypeId() == TYPEID_UNIT)
                        {
                            if (target->GetEntry() == NPC_ENTRY_SAND_PIGMY && target->GetHealthPct() <= 65)
                                return SPELL_CAST_OK;
                        }
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_sullah_pigmy_pen_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sullah_pigmy_pen_SpellScript();
        }
};

class spell_completion_checks : public SpellScriptLoader
{
    public:
        spell_completion_checks() : SpellScriptLoader("spell_completion_checks") { }

        class spell_completion_checks_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_completion_checks_SpellScript);

            enum questId
            {
                QUEST_MISSING_PIECES        = 28272,
                QUEST_REDUCED_PRODUCTIVITY  = 28271
            };

            enum spellId
            {
                SPELL_UNIQUE_PHASING    = 60191,
                SPELL_FADE_TO_BLACK     = 94053,
                SPELL_SUMMON_CAMERA     = 94052,
                SPELL_SUMMON_OVERSEER   = 94060,
                SPELL_SUMMON_CLONE      = 94055
            };

            void HandleCheckComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Event in progress!
                    if (caster->GetPhaseMask() == 385 || caster->HasAura(SPELL_UNIQUE_PHASING)
                        || caster->HasAura(SPELL_FADE_TO_BLACK) || caster->GetVehicleBase())
                        return;

                    if (caster->ToPlayer()->GetQuestStatus(QUEST_MISSING_PIECES) == QUEST_STATUS_COMPLETE &&
                        caster->ToPlayer()->GetQuestStatus(QUEST_REDUCED_PRODUCTIVITY) == QUEST_STATUS_COMPLETE)
                    {
                        caster->SetPhaseMask(385, true);
                        caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                        caster->AddAura(SPELL_FADE_TO_BLACK, caster);
                        caster->CastSpell(caster, SPELL_SUMMON_OVERSEER, true);
                        caster->CastSpell(caster, SPELL_SUMMON_CLONE, true);
                        caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_completion_checks_SpellScript::HandleCheckComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_completion_checks_SpellScript();
        }
};

class npc_otm_camera_event : public CreatureScript
{
public:
   npc_otm_camera_event() : CreatureScript("npc_otm_camera_event") { }

    struct npc_otm_camera_eventAI : public ScriptedAI
    {
        npc_otm_camera_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_SUMMON_ELITE          = 94071,
            SPELL_SUMMON_MYZERIAN       = 94080
        };

        enum pointId
        {
            POINT_MIRROR    = 1,
            POINT_MURDER,
            POINT_MYZERIAN
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_FOCUS_MIRROR,
            EVENT_MOVE_TO_MURDER,
            EVENT_MOVE_TO_ELITE,
            EVENT_FOCUS_MYZERIAN,
            EVENT_QUEST_COMPLETE
        };

        enum npcId
        {
            NPC_ENTRY_CLONE     = 50629,
            NPC_ENTRY_MURDER    = 50658,
            NPC_ENTRY_OVERSEER  = 50661,
            NPC_ENTRY_CORPSE    = 48488,
            NPC_ENTRY_MYZERIAN  = 50663
        };

        class soundAlarm : public BasicEvent
        {
            public:
                explicit soundAlarm(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->GetMotionMaster()->MovementExpired(false);
                creature->GetMotionMaster()->MovePoint(3, -8843.79f, 14.73f, 141.04f);
                creature->SetFacingTo(1.81f);
                creature->AI()->TalkWithDelay(1500, 0);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->EnterVehicle(me, 2);

                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                            playerOwner->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_CLONE)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->NearTeleportTo(-8743.88f, -60.62f, 175.81f, 0.04f, true);
                        events.ScheduleEvent(EVENT_MOVE_TO_MURDER, 12000);
                        events.ScheduleEvent(EVENT_FOCUS_MIRROR, 1000);
                        break;
                    }
                    case EVENT_FOCUS_MIRROR:
                    {
                        events.CancelEvent(EVENT_FOCUS_MIRROR);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                            playerOwner->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_CLONE)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_MOVE_TO_MURDER:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_MURDER);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8822.72f, -2.03f, 154.45f, 8.0f, 8.0f, POINT_MURDER);
                        if (Creature* murder = me->FindNearestCreature(NPC_ENTRY_MURDER, 300.0f, true))
                        {
                            me->CastStop();
                            me->CastSpell(murder, SPELL_CAMERA_CHANNELING, true);
                        }
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_OVERSEER)
                                    {
                                        (*itr)->SetWalk(true);
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                        (*itr)->GetMotionMaster()->MovePoint(2, -8844.04f, 13.51f, 141.04f);
                                        (*itr)->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                                        (*itr)->m_Events.AddEvent(new soundAlarm((*itr)->ToCreature()), (*itr)->m_Events.CalculateTime(6000));
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_TO_ELITE, 10000);
                        break;
                    }
                    case EVENT_MOVE_TO_ELITE:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_ELITE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_ELITE, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_MYZERIAN, true);
                        }

                        if (Creature* corpse = me->FindNearestCreature(NPC_ENTRY_CORPSE, 500.0f, true))
                        {
                            me->CastStop();
                            me->CastSpell(corpse, SPELL_CAMERA_CHANNELING, true);
                        }
                        events.ScheduleEvent(EVENT_FOCUS_MYZERIAN, 3000);
                        break;
                    }
                    case EVENT_FOCUS_MYZERIAN:
                    {
                        events.CancelEvent(EVENT_FOCUS_MYZERIAN);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8839.94f, 72.39f, 171.45f, 15.0f, 15.0f, POINT_MYZERIAN);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(500.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_MYZERIAN)
                                    {
                                        me->CastStop();
                                        me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 10000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_otm_camera_eventAI(creature);
    }
};

class npc_otm_clone_event : public CreatureScript
{
public:
   npc_otm_clone_event() : CreatureScript("npc_otm_clone_event") { }

    struct npc_otm_clone_eventAI : public ScriptedAI
    {
        npc_otm_clone_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_MIRROR_AURA           = 93996
        };

        enum pointId
        {
            POINT_AWAY  = 1
        };

        enum eventId
        {
            EVENT_MOVE_AWAY     = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 1.2f);
            owner->AddAura(SPELL_MIRROR_AURA, me);
            events.ScheduleEvent(EVENT_MOVE_AWAY, 5000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
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

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_AWAY:
                    {
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -8621.47f, -171.52f, 185.55f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_otm_clone_eventAI(creature);
    }
};

class npc_otm_elite_event : public CreatureScript
{
public:
   npc_otm_elite_event() : CreatureScript("npc_otm_elite_event") { }

    struct npc_otm_elite_eventAI : public ScriptedAI
    {
        npc_otm_elite_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191
        };

        enum pointId
        {
            POINT_AWAY  = 1
        };

        enum eventId
        {
            EVENT_MOVE_AWAY     = 1,
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 1.2f);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_MOVE_AWAY, 1000);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
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

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_AWAY:
                    {
                        events.CancelEvent(EVENT_MOVE_AWAY);
                        me->GetMotionMaster()->MovePoint(POINT_AWAY, -8925.59f+urand(1, 45), 120.62f+urand(1, 45), 141.04f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_otm_elite_eventAI(creature);
    }
};

class npc_otm_myzerian_event : public CreatureScript
{
public:
   npc_otm_myzerian_event() : CreatureScript("npc_otm_myzerian_event") { }

    struct npc_otm_myzerian_eventAI : public ScriptedAI
    {
        npc_otm_myzerian_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_DRAGON_SMOKE          = 94004,
            SPELL_DRAGON_WARD           = 89942
        };

        enum pointId
        {
            POINT_TAKEOFF   = 1,
            POINT_CIRCLE
        };

        enum eventId
        {
            EVENT_TRANSFORM     = 1,
            EVENT_MOVE_CIRCLE
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 1.8f);
            me->AddAura(SPELL_DRAGON_WARD, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_TRANSFORM, 5000);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CIRCLE:
                {
                    me->DespawnOrUnsummon(1);
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
                    case EVENT_TRANSFORM:
                    {
                        events.CancelEvent(EVENT_TRANSFORM);
                        me->SetDisplayId(12869);
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 30.0f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        DoCast(SPELL_DRAGON_SMOKE);
                        events.ScheduleEvent(EVENT_MOVE_CIRCLE, 2000);
                        break;
                    }
                    case EVENT_MOVE_CIRCLE:
                    {
                        events.CancelEvent(EVENT_MOVE_CIRCLE);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_CIRCLE, -8956.01f, 3.65f, 189.53f);
                        me->RemoveAurasDueToSpell(SPELL_DRAGON_SMOKE);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_otm_myzerian_eventAI(creature);
    }
};

class npc_myzerian_sentinel : public CreatureScript
{
public:
    npc_myzerian_sentinel() : CreatureScript("npc_myzerian_sentinel") { }

    struct npc_myzerian_sentinelAI : public npc_escortAI
    {
        npc_myzerian_sentinelAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_BLACK_CLEAVE   = 1,
            EVENT_BLAST_WAVE,
            EVENT_FIRE_SPIT,
            EVENT_RUPTURE_LINE,
            EVENT_TAIL_SWEEP,
            EVENT_SEARCH_INTRUDER
        };

        enum spellId
        {
            SPELL_BLACK_CLEAVE  = 90075,
            SPELL_BLAST_WAVE    = 90073,
            SPELL_FIRE_SPIT     = 90076,
            SPELL_RUPTURE_LINE  = 90078,
            SPELL_TAIL_SWEEP    = 90074
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum pointId
        {
            POINT_LAND  = 20
        };

        void Reset()
        {
            if (!me->isMoving())
                DoAction(ACTION_START_WP);

            me->SetSpeed(MOVE_RUN, 2.0f, true);

            x = NULL;
            y = NULL;
            z = NULL;
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 0:
                    break;
                default:
                    events.ScheduleEvent(EVENT_SEARCH_INTRUDER, 1);
                    break;
            }
        }

        void EnterCombat(Unit* who)
        {
            x = who->GetPositionX();
            y = who->GetPositionY();
            z = who->GetPositionZ();
            Position const moveLand  = {x, y, z};
            me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);

            events.ScheduleEvent(EVENT_FIRE_SPIT, 1);
            events.ScheduleEvent(EVENT_BLACK_CLEAVE, 4000);
            events.ScheduleEvent(EVENT_RUPTURE_LINE, 8000);
            events.ScheduleEvent(EVENT_TAIL_SWEEP, 6000);
            events.ScheduleEvent(EVENT_BLAST_WAVE, 15000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_WP:
                {
                    Start(true, true, NULL, NULL, true, true, true);
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
                    case EVENT_SEARCH_INTRUDER:
                    {
                        events.CancelEvent(EVENT_SEARCH_INTRUDER);
                        if (Player* intruder = me->FindNearestPlayer(85.0f, true))
                            AttackStart(intruder);
                        break;
                    }
                    case EVENT_FIRE_SPIT:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_FIRE_SPIT, urand(6000, 12000));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_FIRE_SPIT);
                        break;
                    }
                    case EVENT_BLACK_CLEAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_BLACK_CLEAVE, urand(4000, 12500));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BLACK_CLEAVE);
                        break;
                    }
                    case EVENT_BLAST_WAVE:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_BLAST_WAVE, urand(5500, 10500));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BLAST_WAVE);
                        break;
                    }
                    case EVENT_TAIL_SWEEP:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_TAIL_SWEEP, urand(16500, 21250));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_TAIL_SWEEP);
                        break;
                    }
                    case EVENT_RUPTURE_LINE:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_RUPTURE_LINE, urand(8500, 9500));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_RUPTURE_LINE);
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
        float x,y,z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_myzerian_sentinelAI(creature);
    }
};

class spell_shroud_of_the_makers : public SpellScriptLoader
{
    public:
        spell_shroud_of_the_makers() : SpellScriptLoader("spell_shroud_of_the_makers") { }

        class spell_shroud_of_the_makers_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shroud_of_the_makers_SpellScript);

            void HandleWarning()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        caster->MonsterWhisper("BEWARE!", caster->GetGUID(), true);
                        caster->MonsterWhisper("Myzerian can see through your disguise!", caster->GetGUID(), true);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_shroud_of_the_makers_SpellScript::HandleWarning);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_shroud_of_the_makers_SpellScript();
        }
};

class spell_completion_check_sec : public SpellScriptLoader
{
    public:
        spell_completion_check_sec() : SpellScriptLoader("spell_completion_check_sec") { }

        class spell_completion_check_sec_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_completion_check_sec_SpellScript);

            enum questId
            {
                QUEST_SHROUD_OF_THE_MAKERS  = 28367
            };

            enum spellId
            {
                SPELL_UNIQUE_PHASING    = 60191,
                SPELL_FADE_TO_BLACK     = 94053,
                SPELL_SUMMON_CAMERA     = 94134,
                SPELL_SUMMON_MYZERIAN   = 94153,
                SPELL_SUMMON_CLONE      = 94055
            };

            void HandleCheckComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Event in progress!
                    if (caster->GetPhaseMask() == 4096 || caster->HasAura(SPELL_UNIQUE_PHASING)
                        || caster->HasAura(SPELL_FADE_TO_BLACK) || caster->GetVehicleBase())
                        return;

                    if (caster->ToPlayer()->GetQuestStatus(QUEST_SHROUD_OF_THE_MAKERS) == QUEST_STATUS_COMPLETE)
                    {
                        caster->SetPhaseMask(4096, true);
                        caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                        caster->AddAura(SPELL_FADE_TO_BLACK, caster);
                        caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                        caster->CastSpell(caster, SPELL_SUMMON_MYZERIAN, true);
                        caster->CastSpell(caster, SPELL_SUMMON_CLONE, true);
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_completion_check_sec_SpellScript::HandleCheckComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_completion_check_sec_SpellScript();
        }
};

class npc_md_camera_event : public CreatureScript
{
public:
   npc_md_camera_event() : CreatureScript("npc_md_camera_event") { }

    struct npc_md_camera_eventAI : public ScriptedAI
    {
        npc_md_camera_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_EXPLOSION_BUNNY_01    = 94156,
            SPELL_EXPLOSION_BUNNY_02    = 94172,
            SPELL_EXPLOSION_BUNNY_03    = 94173,
            SPELL_EXPLOSION_BUNNY_04    = 94175,
            SPELL_EXPLOSION_BUNNY_05    = 94176,
            SPELL_EXPLOSION_BUNNY_06    = 94177,
            SPELL_EXPLOSION_BUNNY_07    = 94178,
            SPELL_EXPLOSION_BUNNY_08    = 94179,
            SPELL_EXPLOSION_BUNNY_09    = 94180
        };

        enum pointId
        {
            POINT_MYZERIAN  = 1
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_FOCUS_MIRROR,
            EVENT_FOCUS_MYZERIAN,
            EVENT_QUEST_COMPLETE
        };

        enum npcId
        {
            NPC_ENTRY_CLONE     = 50629,
            NPC_ENTRY_MYZERIAN  = 50664
        };

        class myzerianDeath : public BasicEvent
        {
            public:
                explicit myzerianDeath(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->Kill(creature, false);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 2);

                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->NearTeleportTo(-8743.88f, -60.62f, 175.81f, 0.04f, true);
                        events.ScheduleEvent(EVENT_FOCUS_MYZERIAN, 12000);
                        events.ScheduleEvent(EVENT_FOCUS_MIRROR, 1000);
                        break;
                    }
                    case EVENT_FOCUS_MIRROR:
                    {
                        events.CancelEvent(EVENT_FOCUS_MIRROR);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                            playerOwner->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_CLONE)
                                        DoCast((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_FOCUS_MYZERIAN:
                    {
                        events.CancelEvent(EVENT_FOCUS_MYZERIAN);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8833.46f, 49.29f, 360.87f, 32.0f, 42.0f, POINT_MYZERIAN);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(500.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_MYZERIAN)
                                    {
                                        me->CastStop();
                                        me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                        (*itr)->SetSpeed(MOVE_RUN, 1.5f, true);
                                        (*itr)->SetWalk(false);
                                        (*itr)->GetMotionMaster()->MovePoint(1, -8901.27f, 56.21f, 166.86f);
                                        (*itr)->m_Events.AddEvent(new myzerianDeath((*itr)->ToCreature()), (*itr)->m_Events.CalculateTime(15000));
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_01, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_02, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_03, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_04, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_05, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_06, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_07, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_08, true);
                                        playerOwner->CastSpell(playerOwner, SPELL_EXPLOSION_BUNNY_09, true);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 30000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_md_camera_eventAI(creature);
    }
};

class npc_md_explosion_bunny : public CreatureScript
{
public:
   npc_md_explosion_bunny() : CreatureScript("npc_md_explosion_bunny") { }

    struct npc_md_explosion_bunnyAI : public ScriptedAI
    {
        npc_md_explosion_bunnyAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_EXPLODE               = 76841
        };

        enum eventId
        {
            EVENT_EXPLODE       = 1,
            EVENT_STOP_EVENTS
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_EXPLODE, 8000);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EXPLODE:
                    {
                        events.ScheduleEvent(EVENT_STOP_EVENTS, 25000);
                        events.RescheduleEvent(EVENT_EXPLODE, 1000);
                        DoCast(SPELL_EXPLODE);
                        break;
                    }
                    case EVENT_STOP_EVENTS:
                    {
                        events.Reset();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_md_explosion_bunnyAI(creature);
    }
};

class spell_schnottz_so_fast_complete : public SpellScriptLoader
{
    public:
        spell_schnottz_so_fast_complete() : SpellScriptLoader("spell_schnottz_so_fast_complete") { }

        class spell_schnottz_so_fast_complete_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_schnottz_so_fast_complete_SpellScript);

            enum questId
            {
                QUEST_SCHNOTTZ_SO_FAST  = 28402
            };

            enum spellId
            {
                SPELL_UNIQUE_PHASING        = 60191,
                SPELL_FADE_TO_BLACK         = 94053,
                SPELL_SUMMON_CAMERA         = 94189
            };

            void HandleCheckComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Event in progress!
                    if (caster->GetPhaseMask() == 4096 || caster->HasAura(SPELL_UNIQUE_PHASING)
                        || caster->HasAura(SPELL_FADE_TO_BLACK) || caster->GetVehicleBase())
                        return;

                    if (caster->ToPlayer()->GetQuestStatus(QUEST_SCHNOTTZ_SO_FAST) == QUEST_STATUS_COMPLETE)
                    {
                        caster->ToPlayer()->AddSpellCooldown(94188, 0, time(NULL) + 300);
                        caster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        caster->SetPhaseMask(4096, true);
                        caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                        caster->AddAura(SPELL_FADE_TO_BLACK, caster);
                        caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_schnottz_so_fast_complete_SpellScript::HandleCheckComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_schnottz_so_fast_complete_SpellScript();
        }
};

class npc_com_camera_event : public CreatureScript
{
public:
   npc_com_camera_event() : CreatureScript("npc_com_camera_event") { }

    struct npc_com_camera_eventAI : public ScriptedAI
    {
        npc_com_camera_eventAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_SUMMON_HARRISON       = 94201
        };

        enum pointId
        {
            POINT_HARRISON  = 1
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_TELEPORT_CAMERA,
            EVENT_CHECK_DUMMY,
            EVENT_FOCUS_HARRISON,
            EVENT_QUEST_COMPLETE
        };

        enum npcId
        {
            NPC_ENTRY_DUMMY     = 48534,
            NPC_ENTRY_HARRISON  = 49462
        };

        class moveHarrison : public BasicEvent
        {
            public:
                explicit moveHarrison(Creature* creature) : creature(creature) {}

            bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
            {
                creature->SetWalk(false);
                creature->GetMotionMaster()->MovePoint(1, -8865.91f, 202.34f, -21.68f);
                creature->DespawnOrUnsummon(12000);
                return true;
            }

        private:
            Creature* creature;
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        events.ScheduleEvent(EVENT_TELEPORT_CAMERA, 2000);
                        break;
                    }
                    case EVENT_TELEPORT_CAMERA:
                    {
                        events.CancelEvent(EVENT_TELEPORT_CAMERA);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->NearTeleportTo(-8863.19f, 203.45f, -8.46f, 0.99f);
                        events.ScheduleEvent(EVENT_CHECK_DUMMY, 1000);
                        break;
                    }
                    case EVENT_CHECK_DUMMY:
                    {
                        events.CancelEvent(EVENT_CHECK_DUMMY);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8802.96f, 266.34f, -12.70f, 9.5f, 9.5f, POINT_HARRISON);

                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(500.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature())
                            {
                                if ((*itr)->GetEntry() == NPC_ENTRY_DUMMY)
                                {
                                    me->CastStop();
                                    me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->CastWithDelay(11000, playerOwner, SPELL_SUMMON_HARRISON, true);

                        events.ScheduleEvent(EVENT_FOCUS_HARRISON, 11500);
                        break;
                    }
                    case EVENT_FOCUS_HARRISON:
                    {
                        events.CancelEvent(EVENT_FOCUS_HARRISON);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(500.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_HARRISON)
                                    {
                                        me->CastStop();
                                        me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                        (*itr)->m_Events.AddEvent(new moveHarrison((*itr)->ToCreature()), (*itr)->m_Events.CalculateTime(3000));
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 13000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_com_camera_eventAI(creature);
    }
};

class npc_harrison_bad_datas : public CreatureScript
{
public:
    npc_harrison_bad_datas() : CreatureScript("npc_harrison_bad_datas") { }

    enum questId
    {
        QUEST_ENTRY_BAD_DATAS = 28403
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_SUMMON_HARRISON   = 90384
    };

    #define GOSSIP_TEXT_JONES_02 "Ready when you are, Doctor Jones!"

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_ENTRY_BAD_DATAS) == QUEST_STATUS_INCOMPLETE)
            {
                player->SetPhaseMask(8192, true);
                player->AddAura(SPELL_UNIQUE_PHASING, player);
                player->CastSpell(player, SPELL_SUMMON_HARRISON, true);
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_BAD_DATAS) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JONES_02, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }
};

class npc_bad_datas_summon : public CreatureScript
{
public:
    npc_bad_datas_summon() : CreatureScript("npc_bad_datas_summon") { }

    struct npc_bad_datas_summonAI : public npc_escortAI
    {
        npc_bad_datas_summonAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_ESCORT_RESTORE_01  = 1,
            EVENT_QUEST_COMPLETE,
            EVENT_ESCORT_RESTORE_02,
            EVENT_JUMP_2,
            EVENT_KNEEL,
            EVENT_PHASE_AND_DESPAWN
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_QUEST_DETECTION   = 94567
        };

        enum actionId
        {
            ACTION_START_WP     = 1
        };

        enum pointId
        {
            POINT_JUMP_1    = 19,
            POINT_JUMP_2
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            DoAction(ACTION_START_WP);
            TalkWithDelay(200, 0, owner->GetGUID());
            me->SetFacingToObject(owner);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        Talk(1, playerOwner->GetGUID());
                    break;
                }
                case 6:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        Talk(2, playerOwner->GetGUID());

                    SetEscortPaused(true);
                    SetRun(false);
                    events.ScheduleEvent(EVENT_ESCORT_RESTORE_01, 5000);
                    me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                    break;
                }
                case 7:
                {
                    events.ScheduleEvent(EVENT_QUEST_COMPLETE, 16000);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        TalkWithDelay(8000, 3, playerOwner->GetGUID());
                        TalkWithDelay(16000, 4, playerOwner->GetGUID());
                        TalkWithDelay(24000, 5, playerOwner->GetGUID());
                    }
                    SetRun(true);
                    SetEscortPaused(true);
                    events.ScheduleEvent(EVENT_ESCORT_RESTORE_02, 30000);
                    me->HandleEmoteCommand(EMOTE_STATE_STAND);
                    break;
                }
                case 17:
                {
                    SetEscortPaused(true);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveJump(-8996.05f, 27.22f, -20.97f, 12.5f, 12.5f, POINT_JUMP_1);
                    events.ScheduleEvent(EVENT_JUMP_2, 4000);
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
                case ACTION_START_WP:
                {
                    Start(false, true, NULL, NULL, true, false, true);
                    SetDespawnAtEnd(false);
                    SetDespawnAtFar(true);
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
                    case EVENT_ESCORT_RESTORE_01:
                    {
                        events.CancelEvent(EVENT_ESCORT_RESTORE_01);
                        SetEscortPaused(false);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                playerOwner->ToPlayer()->KilledMonsterCredit(48547);
                        }
                        break;
                    }
                    case EVENT_ESCORT_RESTORE_02:
                    {
                        events.CancelEvent(EVENT_ESCORT_RESTORE_02);
                        SetEscortPaused(false);
                        break;
                    }
                    case EVENT_JUMP_2:
                    {
                        events.CancelEvent(EVENT_JUMP_2);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8988.87f, 26.18f, -17.95f, 12.5f, 12.5f, POINT_JUMP_2);
                        events.ScheduleEvent(EVENT_KNEEL, 1500);
                        break;
                    }
                    case EVENT_KNEEL:
                    {
                        events.CancelEvent(EVENT_KNEEL);
                        me->SetStandState(UNIT_STAND_STATE_KNEEL);
                        events.ScheduleEvent(EVENT_PHASE_AND_DESPAWN, 2000);
                        break;
                    }
                    case EVENT_PHASE_AND_DESPAWN:
                    {
                        events.CancelEvent(EVENT_PHASE_AND_DESPAWN);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->AddAura(SPELL_QUEST_DETECTION, playerOwner);
                            playerOwner->SetPhaseMask(4497, true);
                        }
                        me->DespawnOrUnsummon(1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bad_datas_summonAI(creature);
    }
};

class npc_lunar_crystal : public CreatureScript
{
public:
   npc_lunar_crystal() : CreatureScript("npc_lunar_crystal") { }

    struct npc_lunar_crystalAI : public ScriptedAI
    {
        npc_lunar_crystalAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        enum spellId
        {
            SPELL_LUNAR_HEART           = 90393,
            SPELL_LUNAR_STRIKE          = 90434
        };

        enum eventId
        {
            EVENT_CAST_BEAM_CHANNEL     = 1
        };

        enum npcId
        {
            NPC_ENTRY_TITANIC_GUARDIAN  = 48437
        };

        void EnterCombat(Unit* who)
        {
            if (Creature* titanicGuardian = me->FindNearestCreature(NPC_ENTRY_TITANIC_GUARDIAN, 100.0f, true))
            {
                titanicGuardian->SetControlled(true, UNIT_STATE_ROOT);
                titanicGuardian->AI()->AttackStart(who);
                titanicGuardian->CastSpell(titanicGuardian, SPELL_LUNAR_STRIKE);
            }
        }

        void Reset()
        {
            if (me->GetReactState() != REACT_DEFENSIVE)
                me->SetReactState(REACT_DEFENSIVE);

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                events.ScheduleEvent(EVENT_CAST_BEAM_CHANNEL, 1000);
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* titanicGuardian = me->FindNearestCreature(NPC_ENTRY_TITANIC_GUARDIAN, 500.0f, true))
                titanicGuardian->AI()->DoAction(1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_BEAM_CHANNEL:
                    {
                        events.CancelEvent(EVENT_CAST_BEAM_CHANNEL);
                        if (!me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            if (Creature* titanicGuardian = me->FindNearestCreature(NPC_ENTRY_TITANIC_GUARDIAN, 200.0f, true))
                                DoCast(titanicGuardian, SPELL_LUNAR_HEART, true);
                        }
                        me->ClearUnitState(UNIT_STATE_CASTING);
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
        return new npc_lunar_crystalAI(creature);
    }
};

class npc_titanic_guardian_crystal : public CreatureScript
{
public:
   npc_titanic_guardian_crystal() : CreatureScript("npc_titanic_guardian_crystal") { }

    struct npc_titanic_guardian_crystalAI : public ScriptedAI
    {
        npc_titanic_guardian_crystalAI(Creature* creature) : ScriptedAI(creature) {crystalDeath = 0;}

        enum spellId
        {
            SPELL_AOE_KILL_CREDIT   = 90646
        };

        enum actionId
        {
            ACTION_INCREASE_COUNTER     = 1
        };

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INCREASE_COUNTER:
                {
                    crystalDeath++;
                    if (crystalDeath >= 3)
                    {
                        DoCastAOE(SPELL_AOE_KILL_CREDIT);
                        me->Kill(me, false);
                        crystalDeath = 0;
                    }
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        int8 crystalDeath;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_titanic_guardian_crystalAI(creature);
    }
};

class spell_ill_do_it_by_hand_init : public SpellScriptLoader
{
    public:
        spell_ill_do_it_by_hand_init() : SpellScriptLoader("spell_ill_do_it_by_hand_init") { }

        class spell_ill_do_it_by_hand_init_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ill_do_it_by_hand_init_SpellScript);

            enum spellId
            {
                SPELL_UNIQUE_PHASING        = 60191,
                SPELL_FADE_TO_BLACK         = 94053,
                SPELL_SUMMON_CAMERA         = 94238,
                SPELL_SUMMON_CLONE          = 94243,
                SPELL_SUMMON_HARRISON       = 94249
            };

            enum npcId
            {
                NPC_CHAMBER_OF_THE_MOON     = 48606
            };

            void HandleCheckComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Event in progress!
                    if (caster->GetPhaseMask() == 16384 || caster->HasAura(SPELL_FADE_TO_BLACK) || caster->GetVehicleBase())
                        return;

                    caster->SetPhaseMask(16384, true);
                    caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                    caster->AddAura(SPELL_FADE_TO_BLACK, caster);
                    caster->CastSpell(caster, SPELL_SUMMON_HARRISON, true);
                    caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_ill_do_it_by_hand_init_SpellScript::HandleCheckComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ill_do_it_by_hand_init_SpellScript();
        }
};

class npc_chamber_moon_camera_final : public CreatureScript
{
public:
   npc_chamber_moon_camera_final() : CreatureScript("npc_chamber_moon_camera_final") { }

    struct npc_chamber_moon_camera_finalAI : public ScriptedAI
    {
        npc_chamber_moon_camera_finalAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_FADE_TO_BLACK         = 88267
        };

        enum pointId
        {
            POINT_UPPER     = 1
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_TELEPORT_CAMERA,
            EVENT_QUEST_COMPLETE
        };

        enum npcId
        {
            NPC_ENTRY_DUMMY     = 48606
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
            me->GetMotionMaster()->MoveJump(-8997.67f, 72.86f, 28.65f, 5.0f, 5.0f, POINT_UPPER);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->EnterVehicle(me, 0);
                            playerOwner->AddAura(94248, playerOwner);
                            playerOwner->CastWithDelay(16000, playerOwner, SPELL_FADE_TO_BLACK, true);
                        }
                        events.ScheduleEvent(EVENT_TELEPORT_CAMERA, 18000);
                        if (Creature* dummy = me->FindNearestCreature(NPC_ENTRY_DUMMY, 200.0f, true))
                            DoCast(dummy, SPELL_CAMERA_CHANNELING, true);
                        break;
                    }
                    case EVENT_TELEPORT_CAMERA:
                    {
                        me->CastStop();
                        events.CancelEvent(EVENT_TELEPORT_CAMERA);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->NearTeleportTo(-8921.04f, -54.95f, 308.35f, 2.63f);
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 10000);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            passenger->ChangeSeat(1, true);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chamber_moon_camera_finalAI(creature);
    }
};

class npc_confiscated_artillery : public CreatureScript
{
public:
    npc_confiscated_artillery() : CreatureScript("npc_confiscated_artillery") { }

    enum questId
    {
        QUEST_ENTRY_FIRE_FROM_THE_SKY           = 28497,
        QUEST_ENTRY_FIRE_FROM_THE_SKY_DAILY     = 28736
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_QUEST_DETECTION   = 94566,
        SPELL_SUMMON_SEAT       = 90800,
        SPELL_FADE_TO_BLACK     = 91102
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ENTRY_FIRE_FROM_THE_SKY) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_ENTRY_FIRE_FROM_THE_SKY_DAILY) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddAura(SPELL_UNIQUE_PHASING, player);
            player->CastSpell(player, SPELL_FADE_TO_BLACK, true);
            player->NearTeleportTo(-8507.00f, -45.32f, 272.48f, 2.74f);
            player->CastSpell(player, SPELL_SUMMON_SEAT, true);
            return true;
        }
        return true;
    }
};

class npc_artillery_seat : public CreatureScript
{
public:
   npc_artillery_seat() : CreatureScript("npc_artillery_seat") { }

    struct npc_artillery_seatAI : public ScriptedAI
    {
        npc_artillery_seatAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_CHECK_ACHIEVEMENT
        };

        enum actionId
        {
            ACTION_ACHIEVEMENT_COUNTER  = 1,
            ACTION_ACHIEVEMENT_CHECK
        };

        void OnCharmed(bool apply) {}

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 1000);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            achievementCounter = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ACHIEVEMENT_COUNTER:
                {
                    achievementCounter++;
                    events.ScheduleEvent(EVENT_CHECK_ACHIEVEMENT, 1500);
                    break;
                }
                case ACTION_ACHIEVEMENT_CHECK:
                {
                    if (achievementCounter >= 10)
                    {
                        if (AchievementEntry const* helpTheBombardier = sAchievementMgr->GetAchievement(5317))
                        {
                            if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            {
                                if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                                    playerOwner->ToPlayer()->CompletedAchievement(helpTheBombardier);
                            }
                        }
                    }
                    else
                        achievementCounter = 0;
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        break;
                    }
                    case EVENT_CHECK_ACHIEVEMENT:
                    {
                        events.CancelEvent(EVENT_CHECK_ACHIEVEMENT);
                        DoAction(ACTION_ACHIEVEMENT_CHECK);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
        uint16 achievementCounter;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_artillery_seatAI(creature);
    }
};

class npc_schnottz_elite_infantryman : public CreatureScript
{
public:
   npc_schnottz_elite_infantryman() : CreatureScript("npc_schnottz_elite_infantryman") { }

    struct npc_schnottz_elite_infantrymanAI : public ScriptedAI
    {
        npc_schnottz_elite_infantrymanAI(Creature* creature) : ScriptedAI(creature) {playerAttacker = NULL;}

        enum npcId
        {
            NPC_ENTRY_ARTILLERY_SEAT    = 48728
        };

        enum creditId
        {
            QUEST_CREDIT_FIRE_FROM_THE_SKY  = 48859
        };

        enum spellId
        {
            SPELL_ARTILLERY_IMPACT  = 91108
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_ARTILLERY_IMPACT:
                {
                    playerAttacker = caster;
                    if (Unit* vehicleOwner = caster->GetVehicleKit()->GetPassenger(0))
                    {
                        caster->ToCreature()->AI()->DoAction(1);
                        if (vehicleOwner->GetTypeId() == TYPEID_PLAYER)
                            vehicleOwner->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_FIRE_FROM_THE_SKY);
                    }
                    me->Kill(me, false);
                    break;
                }
                default:
                    break;
            }
        }

    protected:
        Unit* playerAttacker;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_schnottz_elite_infantrymanAI(creature);
    }
};

class spell_fire_from_the_sky_init : public SpellScriptLoader
{
    public:
        spell_fire_from_the_sky_init() : SpellScriptLoader("spell_fire_from_the_sky_init") { }

        class spell_fire_from_the_sky_init_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fire_from_the_sky_init_SpellScript);

            enum spellId
            {
                SPELL_UNIQUE_PHASING        = 60191,
                SPELL_FADE_TO_BLACK         = 94053,
                SPELL_SUMMON_CAMERA         = 91539
            };

            void HandleCheckComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Event in progress!
                    if (caster->GetPhaseMask() == 16384 || caster->HasAura(SPELL_FADE_TO_BLACK) || caster->GetVehicleBase())
                        return;

                    caster->SetPhaseMask(16384, true);
                    caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                    caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_fire_from_the_sky_init_SpellScript::HandleCheckComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_fire_from_the_sky_init_SpellScript();
        }
};

class npc_fire_from_the_sky_camera : public CreatureScript
{
public:
   npc_fire_from_the_sky_camera() : CreatureScript("npc_fire_from_the_sky_camera") { }

    struct npc_fire_from_the_sky_cameraAI : public npc_escortAI
    {
        npc_fire_from_the_sky_cameraAI(Creature* creature) : npc_escortAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_FADE_TO_BLACK         = 88267,
            SPELL_SUMMON_CLONE          = 91538,
            SPELL_SUMMON_HARRISON       = 91527,
            SPELL_QUEST_VISIBILITY      = 84481
        };

        enum pointId
        {
            POINT_UPPER     = 1
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_TELEPORT_CAMERA,
            EVENT_START_WP,
            EVENT_FOCUS_CLONE,
            EVENT_QUEST_COMPLETE
        };

        enum npcId
        {
            NPC_ENTRY_SMOKE_BUNNY   = 49113,
            NPC_ENTRY_SOLDIER_BURN  = 49115,
            NPC_ENTRY_CLONE         = 49110
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->AddAura(SPELL_QUEST_VISIBILITY, me);
            owner->AddAura(SPELL_QUEST_VISIBILITY, owner);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
                {
                    me->CastStop();
                    break;
                }
                case 2:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        playerOwner->CastSpell(playerOwner, SPELL_SUMMON_CLONE, true);
                        playerOwner->CastSpell(playerOwner, SPELL_SUMMON_HARRISON, true);
                    }
                    events.ScheduleEvent(EVENT_FOCUS_CLONE, 1500);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->EnterVehicle(me, 0);
                            me->GetMotionMaster()->MoveJump(-8556.00f, -102.33f, 222.21f, 85.0f, 15.0f);
                        }
                        events.ScheduleEvent(EVENT_TELEPORT_CAMERA, 5000);
                        break;
                    }
                    case EVENT_TELEPORT_CAMERA:
                    {
                        events.CancelEvent(EVENT_TELEPORT_CAMERA);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        if (Creature* smokeBunny = me->FindNearestCreature(NPC_ENTRY_SMOKE_BUNNY, 100.0f, true))
                            me->CastSpell(smokeBunny, SPELL_CAMERA_CHANNELING, true);
                        events.ScheduleEvent(EVENT_START_WP, 1000);
                        break;
                    }
                    case EVENT_START_WP:
                    {
                        events.CancelEvent(EVENT_START_WP);
                        Start(false, true, NULL, NULL, true, false, true);
                        SetDespawnAtEnd(false);
                        break;
                    }
                    case EVENT_FOCUS_CLONE:
                    {
                        events.CancelEvent(EVENT_FOCUS_CLONE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(500.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_ENTRY_CLONE)
                                    {
                                        me->CastStop();
                                        me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 10000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (me->GetVehicleKit())
                            me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fire_from_the_sky_cameraAI(creature);
    }
};

class npc_harrison_fortune_and_glory : public CreatureScript
{
public:
    npc_harrison_fortune_and_glory() : CreatureScript("npc_harrison_fortune_and_glory") { }

    enum questId
    {
        QUEST_FORTUNE_AND_GLORY     = 27748
    };

    enum spellId
    {
        SPELL_UNIQUE_PHASING    = 60191,
        SPELL_ACTIVATION_BEAM   = 87968,
        SPELL_STONEFORM         = 86985,
        SPELL_QUEST_VISIBILITY  = 94566
    };

    enum entryId
    {
        NPC_COMMANDER_SCHNOTTZ  = 47160,
        NPC_OBSIDIAN_COLOSSUS   = 46646,
        NPC_SCHNOTTZ_RIFLEMAN   = 47067
    };

    enum pointId
    {
        POINT_COMMANDER     = 1,
        POINT_EVADE
    };

    enum goId
    {
        GO_TEMPLE_CRYSTAL   = 206561,
        GO_SPEED_BUFF       = 206566,
        GO_BERSERK_BUFF     = 206564,
        GO_FOOD_BUFF        = 206565
    };

    enum eventId
    {
        EVENT_START_MOVE        = 1,
        EVENT_SUMMON_INFANTRY,
        EVENT_ENABLE_RELIC,
        EVENT_FOLLOW_SCHNOTTZ
    };

    #define GOSSIP_TEXT_JONES_03 "I'm ready. Let's go!"

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 0)
        {
            if (player->GetQuestStatus(QUEST_FORTUNE_AND_GLORY) == QUEST_STATUS_INCOMPLETE)
            {
                player->SetPhaseMask(8192, true);
                player->AddAura(SPELL_UNIQUE_PHASING, player);
                player->RemoveAurasDueToSpell(SPELL_QUEST_VISIBILITY);
                player->SummonCreature(creature->GetEntry(), creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                player->SummonCreature(NPC_COMMANDER_SCHNOTTZ, -8772.67f, 296.97f, 329.29f, 5.42f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                player->SummonCreature(NPC_OBSIDIAN_COLOSSUS, -8738.63f, 263.36f, 329.41f, 5.49f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                player->CLOSE_GOSSIP_MENU();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_FORTUNE_AND_GLORY) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JONES_03, 0, 0);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    struct npc_harrison_fortune_and_gloryAI : public ScriptedAI
    {
        npc_harrison_fortune_and_gloryAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetWalk(false);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            TalkWithDelay(1000, 0, owner->GetGUID());
            events.ScheduleEvent(EVENT_START_MOVE, 2000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_COMMANDER:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(50.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                if ((*itr)->GetEntry() == NPC_COMMANDER_SCHNOTTZ)
                                {
                                    (*itr)->AddAura(SPELL_UNIQUE_PHASING, (*itr));
                                    (*itr)->ToCreature()->AI()->TalkWithDelay(8000, 0, playerOwner->GetGUID());
                                    (*itr)->ToCreature()->AI()->TalkWithDelay(22000, 1, playerOwner->GetGUID());
                                    (*itr)->ToCreature()->AI()->TalkWithDelay(27500, 2, playerOwner->GetGUID());
                                    me->SetFacingToObject((*itr));
                                }
                            }
                        }
                        playerOwner->RemoveAurasDueToSpell(SPELL_QUEST_VISIBILITY);
                        TalkWithDelay(1500, 2, playerOwner->GetGUID());
                        TalkWithDelay(15000, 3, playerOwner->GetGUID());
                    }
                    events.ScheduleEvent(EVENT_SUMMON_INFANTRY, 24500);
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
                    case EVENT_START_MOVE:
                    {
                        events.CancelEvent(EVENT_START_MOVE);
                        me->GetMotionMaster()->MovePoint(POINT_COMMANDER, -8755.26f, 293.53f, 329.23f);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            TalkWithDelay(4000, 1, playerOwner->GetGUID());
                        break;
                    }
                    case EVENT_SUMMON_INFANTRY:
                    {
                        events.CancelEvent(EVENT_SUMMON_INFANTRY);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            for (int i = 0; i < 12; i++)
                                playerOwner->SummonCreature(NPC_SCHNOTTZ_RIFLEMAN, -8803.40f, 328.30f, 346.41f, 5.45f, TEMPSUMMON_TIMED_DESPAWN, 180000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        events.ScheduleEvent(EVENT_ENABLE_RELIC, 3000);
                        break;
                    }
                    case EVENT_ENABLE_RELIC:
                    {
                        events.CancelEvent(EVENT_ENABLE_RELIC);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_COMMANDER_SCHNOTTZ)
                                    {
                                        (*itr)->CastStop();
                                        (*itr)->CastSpell((*itr), SPELL_ACTIVATION_BEAM, true);
                                        (*itr)->SetWalk(false);
                                        (*itr)->GetMotionMaster()->MovePoint(POINT_EVADE, -8808.75f, 333.94f, 346.41f);
                                        (*itr)->ToCreature()->AI()->TalkWithDelay(2000, 3, playerOwner->GetGUID());
                                        (*itr)->ToCreature()->DespawnOrUnsummon(6000);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_FOLLOW_SCHNOTTZ, 2000);
                        break;
                    }
                    case EVENT_FOLLOW_SCHNOTTZ:
                    {
                        events.CancelEvent(EVENT_FOLLOW_SCHNOTTZ);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            TalkWithDelay(3500, 4, playerOwner->GetGUID());
                        me->GetMotionMaster()->MovePoint(POINT_EVADE, -8808.75f, 333.94f, 346.41f);
                        me->DespawnOrUnsummon(6000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_OBSIDIAN_COLOSSUS)
                                    {
                                        (*itr)->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                                        {
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(1000, 0, playerOwner->GetGUID());
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(15000, 1, playerOwner->GetGUID());
                                        }
                                        (*itr)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
                                        (*itr)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                                        (*itr)->SetHealth((*itr)->GetMaxHealth()/2);
                                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                                            (*itr)->ToCreature()->AI()->AttackStart(playerOwner);
                                    }
                                    if ((*itr)->GetEntry() == NPC_SCHNOTTZ_RIFLEMAN)
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_harrison_fortune_and_gloryAI(creature);
    }
};

class npc_schnottz_rifleman_fortune : public CreatureScript
{
public:
   npc_schnottz_rifleman_fortune() : CreatureScript("npc_schnottz_rifleman_fortune") { }

    struct npc_schnottz_rifleman_fortuneAI : public ScriptedAI
    {
        npc_schnottz_rifleman_fortuneAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum pointId
        {
            POINT_CIRCLE    = 1
        };

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191
        };

        enum actionId
        {
            ACTION_ENABLE_AI    = 1
        };

        enum eventId
        {
            EVENT_ENABLE_AI     = 1,
            EVENT_ATTACK,
            EVENT_FLEE
        };

        enum npcId
        {
            NPC_OBSIDIAN_COLOSSUS   = 46646
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
            me->SetWalk(false);
            me->GetMotionMaster()->MovePoint(POINT_CIRCLE, -8766.30f-urand(3, 10), 296.82f-urand(3, 10), 329.21f);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ENABLE_AI:
                {
                    events.ScheduleEvent(EVENT_ENABLE_AI, 1);
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
                    case EVENT_ENABLE_AI:
                    {
                        events.CancelEvent(EVENT_ENABLE_AI);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        events.ScheduleEvent(EVENT_ATTACK, urand(1000, 3500));
                        break;
                    }
                    case EVENT_ATTACK:
                    {
                        events.RescheduleEvent(EVENT_ATTACK, urand(4500, 12000));
                        me->GetMotionMaster()->Clear();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_OBSIDIAN_COLOSSUS)
                                        me->AI()->AttackStart((*itr));
                                }
                            }
                        }
                    }
                    case EVENT_FLEE:
                    {
                        events.RescheduleEvent(EVENT_FLEE, urand(8500, 18500));
                        me->GetMotionMaster()->Clear();
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 50.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(50.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_OBSIDIAN_COLOSSUS)
                                        me->GetMotionMaster()->MoveFleeing((*itr), urand(5000, 6000));
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_schnottz_rifleman_fortuneAI(creature);
    }
};

class npc_obsidian_colossus : public CreatureScript
{
public:
   npc_obsidian_colossus() : CreatureScript("npc_obsidian_colossus") { }

    struct npc_obsidian_colossusAI : public ScriptedAI
    {
        npc_obsidian_colossusAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING    = 60191,
            SPELL_FORCE_PUNCH       = 87988,
            SPELL_SHADOW_STORM      = 87990,
            SPELL_SWEEPING_ATTACK   = 87680,
            SPELL_STONEFORM         = 86985
        };

        enum eventId
        {
            EVENT_FORCE_PUNCH   = 1,
            EVENT_SHADOW_STORM,
            EVENT_SWEEPING_ATTACK
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC|UNIT_FLAG_IMMUNE_TO_PC);
            me->SetWalk(false);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FORCE_PUNCH, 20000);
            events.ScheduleEvent(EVENT_SHADOW_STORM, 8000);
            events.ScheduleEvent(EVENT_SWEEPING_ATTACK, 3000);
            me->RemoveAurasDueToSpell(SPELL_STONEFORM);
        }

        void EnterEvadeMode(){}
        void Reset(){}

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FORCE_PUNCH:
                    {
                        RESCHEDULE_IF_CASTING;
                        events.RescheduleEvent(EVENT_FORCE_PUNCH, urand(17900, 18500));
                        DoCast(SPELL_FORCE_PUNCH);
                        break;
                    }
                    case EVENT_SHADOW_STORM:
                    {
                        events.RescheduleEvent(EVENT_SHADOW_STORM, urand(15800, 18300));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SHADOW_STORM);
                        break;
                    }
                    case EVENT_SWEEPING_ATTACK:
                    {
                        events.RescheduleEvent(EVENT_SWEEPING_ATTACK, urand(12000, 13000));
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SWEEPING_ATTACK);
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
        return new npc_obsidian_colossusAI(creature);
    }
};

class spell_temple_of_uldum_init : public SpellScriptLoader
{
    public:
        spell_temple_of_uldum_init() : SpellScriptLoader("spell_temple_of_uldum_init") { }

        class spell_temple_of_uldum_init_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_temple_of_uldum_init_SpellScript);

            enum spellId
            {
                SPELL_UNIQUE_PHASING        = 60191,
                SPELL_FADE_TO_BLACK         = 94198,
                SPELL_SUMMON_CAMERA         = 94270,
                SPELL_SUMMON_HARRISON       = 94276,
                SPELL_SUMMON_CLONE          = 94273
            };

            void HandleCheckComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Event in progress!
                    if (caster->HasAura(SPELL_FADE_TO_BLACK) || caster->GetVehicleBase())
                        return;

                    caster->SetPhaseMask(8192, true);
                    caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                    caster->AddAura(SPELL_FADE_TO_BLACK, caster);
                    caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                    caster->CastSpell(caster, SPELL_SUMMON_HARRISON, true);
                    caster->CastSpell(caster, SPELL_SUMMON_CLONE, true);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_temple_of_uldum_init_SpellScript::HandleCheckComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_temple_of_uldum_init_SpellScript();
        }
};

class npc_temple_of_uldum_clone : public CreatureScript
{
public:
   npc_temple_of_uldum_clone() : CreatureScript("npc_temple_of_uldum_clone") { }

    struct npc_temple_of_uldum_cloneAI : public ScriptedAI
    {
        npc_temple_of_uldum_cloneAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_MIRROR_AURA           = 93996
        };

        enum pointId
        {
            POINT_TEMPLE    = 1,
            POINT_SHIELD,
            POINT_FRONT_SHIELD
        };

        enum eventId
        {
            EVENT_MOVE_TO_TEMPLE    = 1,
            EVENT_MOVE_TO_SHIELD,
            EVENT_MOVE_FRONT_SHIELD
        };

        enum actionId
        {
            ACTION_SCENE_2  = 1
        };

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TEMPLE:
                {
                    me->DespawnOrUnsummon(1);
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
                case ACTION_SCENE_2:
                {
                    events.ScheduleEvent(EVENT_MOVE_FRONT_SHIELD, 1);
                    break;
                }
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            owner->AddAura(SPELL_MIRROR_AURA, me);
            if (me->GetAreaId() != 5669)
                events.ScheduleEvent(EVENT_MOVE_TO_TEMPLE, 5500);
            else
                events.ScheduleEvent(EVENT_MOVE_TO_SHIELD, 500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_TO_TEMPLE:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_TEMPLE);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_TEMPLE, -9108.06f, 291.41f, 300.59f);
                        break;
                    }
                    case EVENT_MOVE_TO_SHIELD:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_SHIELD);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_SHIELD, -9302.27f, 497.41f, 242.81f);
                        break;
                    }
                    case EVENT_MOVE_FRONT_SHIELD:
                    {
                        events.CancelEvent(EVENT_MOVE_FRONT_SHIELD);
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FRONT_SHIELD, -9302.12f, 483.26f, 242.81f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_cloneAI(creature);
    }
};

class npc_temple_of_uldum_harrison : public CreatureScript
{
public:
   npc_temple_of_uldum_harrison() : CreatureScript("npc_temple_of_uldum_harrison") { }

    struct npc_temple_of_uldum_harrisonAI : public ScriptedAI
    {
        npc_temple_of_uldum_harrisonAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191
        };

        enum pointId
        {
            POINT_TEMPLE    = 1,
            POINT_MECHANISM,
            POINT_COFFER
        };

        enum eventId
        {
            EVENT_MOVE_TO_TEMPLE    = 1,
            EVENT_MOVE_TO_MECHANISM,
            EVENT_STAND_UP
        };

        enum npcId
        {
            NPC_CASTER_CLONE    = 50626,
            NPC_CAMERA          = 50403
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            if (me->GetAreaId() != 5669)
                events.ScheduleEvent(EVENT_MOVE_TO_TEMPLE, 5000);
            else
                events.ScheduleEvent(EVENT_MOVE_TO_MECHANISM, 500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TEMPLE:
                {
                    me->DespawnOrUnsummon(1);
                    break;
                }
                case POINT_MECHANISM:
                {
                    me->SetStandState(UNIT_STAND_STATE_KNEEL);
                    events.ScheduleEvent(EVENT_STAND_UP, 6000);
                    break;
                }
                case POINT_COFFER:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        TalkWithDelay(10000, 1, playerOwner->GetGUID());
                        TalkWithDelay(18000, 2, playerOwner->GetGUID());
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
                    case EVENT_MOVE_TO_TEMPLE:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_TEMPLE);
                        me->GetMotionMaster()->MovePoint(POINT_TEMPLE, -9108.06f, 291.41f, 300.59f);
                        break;
                    }
                    case EVENT_MOVE_TO_MECHANISM:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_MECHANISM);
                        me->GetMotionMaster()->MovePoint(POINT_MECHANISM, -9303.06f, 510.56f, 243.12f);
                        break;
                    }
                    case EVENT_STAND_UP:
                    {
                        events.CancelEvent(EVENT_STAND_UP);
                        me->SetWalk(true);
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        me->GetMotionMaster()->MovePoint(POINT_COFFER, -9297.09f, 483.28f, 242.81f);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            Talk(0, playerOwner->GetGUID());
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_CASTER_CLONE || (*itr)->GetEntry() == NPC_CAMERA)
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_harrisonAI(creature);
    }
};

class npc_temple_of_uldum_camera : public CreatureScript
{
public:
   npc_temple_of_uldum_camera() : CreatureScript("npc_temple_of_uldum_camera") { }

    struct npc_temple_of_uldum_cameraAI : public ScriptedAI
    {
        npc_temple_of_uldum_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_FADE_TO_BLACK         = 94198,
            SPELL_COFFER_VISIBLE        = 94568,
            SPELL_SUMMON_DRAKE_1        = 94333,
            SPELL_SUMMON_DRAKE_2        = 94334,
            SPELL_SUMMON_BALLOON        = 94332,
            SPELL_SUMMON_SCHNOTTZ       = 94395
        };

        enum pointId
        {
            POINT_AIR   = 1,
            POINT_TEMPLE,
            POINT_CENTER,
            POINT_OTHERSIDE,
            POINT_BALLOON,
            POINT_BEHIND,
            POINT_SWITCH
        };

        enum eventId
        {
            EVENT_TARGET_HARRISON   = 1,
            EVENT_RIDE_INVOKER,
            EVENT_FADE_TO_BLACK,
            EVENT_TELEPORT_TO_TEMPLE,
            EVENT_AURA_COFFER,
            EVENT_CENTER_SHIELD,
            EVENT_CHANGE_PHASE,
            EVENT_SUMMON_SCHNOTTZ,
            EVENT_CLOSE_EVENT
        };

        enum npcId
        {
            NPC_HARRISON_JONES      = 49460,
            NPC_CASTER_CLONE        = 50626,
            NPC_COFFER_SHIELD       = 49197,
            NPC_COMMANDER_SCHNOTTZ  = 49466,
            NPC_BALLOON             = 50076,
            NPC_DRAKE_1             = 50077,
            NPC_DRAKE_2             = 50078,
            NPC_BRONZEBEARD         = 49204
        };

        enum actionId
        {
            ACTION_SCENE_2  = 1,
            ACTION_DESPAWN
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_TARGET_HARRISON, 1000);
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SCENE_2:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(200.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                if ((*itr)->GetEntry() == NPC_HARRISON_JONES)
                                    me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                            }
                        }
                    }
                    me->GetMotionMaster()->MoveJump(-9319.98f, 432.15f, 264.15f, 15.0f, 15.0f, POINT_OTHERSIDE);
                    break;
                }
                case ACTION_DESPAWN:
                {
                    events.ScheduleEvent(EVENT_CLOSE_EVENT, 18500);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TEMPLE:
                {
                    events.ScheduleEvent(EVENT_AURA_COFFER, 1);
                    break;
                }
                case POINT_OTHERSIDE:
                {
                    events.ScheduleEvent(EVENT_CHANGE_PHASE, 14000);
                    break;
                }
                case POINT_SWITCH:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                        passenger->ChangeSeat(2, true);
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
                    case EVENT_TARGET_HARRISON:
                    {
                        events.CancelEvent(EVENT_TARGET_HARRISON);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_HARRISON_JONES)
                                        me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                }
                            }
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 365.79f, 10.0f, 12.0f, POINT_AIR);
                        break;
                    }
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        events.ScheduleEvent(EVENT_FADE_TO_BLACK, 10000);
                        break;
                    }
                    case EVENT_FADE_TO_BLACK:
                    {
                        events.CancelEvent(EVENT_FADE_TO_BLACK);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->AddAura(SPELL_FADE_TO_BLACK, playerOwner);
                        events.ScheduleEvent(EVENT_TELEPORT_TO_TEMPLE, 1000);
                        break;
                    }
                    case EVENT_TELEPORT_TO_TEMPLE:
                    {
                        events.CancelEvent(EVENT_TELEPORT_TO_TEMPLE);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9234.21f, 478.54f, 274.98f, 100.0f, 7.0f, POINT_TEMPLE);
                        break;
                    }
                    case EVENT_AURA_COFFER:
                    {
                        events.CancelEvent(EVENT_AURA_COFFER);
                        if (Creature* cofferShield = me->FindNearestCreature(NPC_COFFER_SHIELD, 500.0f, true))
                        {
                            me->CastStop();
                            me->CastSpell(cofferShield, SPELL_CAMERA_CHANNELING, true);
                        }
                        events.ScheduleEvent(EVENT_CENTER_SHIELD, 5000);
                        break;
                    }
                    case EVENT_CENTER_SHIELD:
                    {
                        events.CancelEvent(EVENT_CENTER_SHIELD);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->SummonCreature(NPC_HARRISON_JONES, -9244.19f, 365.22f, 256.79f, 1.84f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                            playerOwner->SummonCreature(NPC_CASTER_CLONE, -9245.60f, 361.06f, 258.74f, 1.84f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9304.78f, 531.50f, 256.40f, 6.0f, 6.0f, POINT_CENTER);
                        break;
                    }
                    case EVENT_CHANGE_PHASE:
                    {
                        events.CancelEvent(EVENT_CHANGE_PHASE);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            {
                                playerOwner->RemoveAurasDueToSpell(SPELL_COFFER_VISIBLE);
                                playerOwner->SetPhaseMask(24576, true);
                            }
                        }
                        events.ScheduleEvent(EVENT_SUMMON_SCHNOTTZ, 8000);
                        break;
                    }
                    case EVENT_SUMMON_SCHNOTTZ:
                    {
                        events.CancelEvent(EVENT_SUMMON_SCHNOTTZ);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_BALLOON, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_SCHNOTTZ, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_DRAKE_1, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_DRAKE_2, true);
                        }
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-9298.63f, 428.25f, 264.88f, 12.5f, 12.5f, POINT_BALLOON);
                        break;
                    }
                    case EVENT_CLOSE_EVENT:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(200.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_HARRISON_JONES:
                                        case NPC_CASTER_CLONE:
                                        case NPC_COMMANDER_SCHNOTTZ:
                                        case NPC_BRONZEBEARD:
                                        case NPC_BALLOON:
                                        case NPC_DRAKE_1:
                                        case NPC_DRAKE_2:
                                        {
                                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(2))
                        {
                            passenger->AddAura(88267, passenger);
                            passenger->ExitVehicle();
                        }
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_cameraAI(creature);
    }
};

class npc_temple_of_uldum_balloon : public CreatureScript
{
public:
   npc_temple_of_uldum_balloon() : CreatureScript("npc_temple_of_uldum_balloon") { }

    struct npc_temple_of_uldum_balloonAI : public ScriptedAI
    {
        npc_temple_of_uldum_balloonAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552
        };

        enum pointId
        {
            POINT_TOP       = 1,
            POINT_COFFER,
            POINT_AWAY
        };

        enum eventId
        {
            EVENT_RIDE_SCHNOTTZ     = 1,
            EVENT_MOVE_UP,
            EVENT_ENABLE_SCHNOTTZ,
            EVENT_MOVE_FORWARD
        };

        enum npcId
        {
            NPC_COMMANDER_SCHNOTTZ  = 49466,
            NPC_CAMERA              = 50403,
            NPC_HARRISON_JONES      = 49460,
            NPC_CASTER_CLONE        = 50626
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_RIDE_SCHNOTTZ, 1500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TOP:
                {
                    events.ScheduleEvent(EVENT_ENABLE_SCHNOTTZ, 1);
                    events.ScheduleEvent(EVENT_MOVE_FORWARD, 1);
                    break;
                }
                case POINT_COFFER:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            passenger->ToCreature()->AI()->TalkWithDelay(1000, 2, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(5000, 3, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(13000, 4, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(21000, 5, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(33000, 6, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(40000, 7, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(47000, 8, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(54000, 9, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->TalkWithDelay(61000, 10, playerOwner->GetGUID());
                            passenger->ToCreature()->AI()->DoAction(2);
                        }
                        passenger->ExitVehicle();
                    }
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 80.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(80.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                switch ((*itr)->GetEntry())
                                {
                                    case NPC_CAMERA:
                                    {
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                        (*itr)->GetMotionMaster()->MoveJump(-9280.18f, 510.64f, 264.88f, 12.5f, 12.5f, 6);
                                        break;
                                    }
                                    case NPC_CASTER_CLONE:
                                    {
                                        (*itr)->SetFacingTo(1.66f);
                                        break;
                                    }
                                    case NPC_HARRISON_JONES:
                                    {
                                        (*itr)->SetFacingTo(1.66f);
                                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                                            (*itr)->ToCreature()->AI()->TalkWithDelay(27000, 3, playerOwner->GetGUID());
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    me->GetMotionMaster()->MovementExpired(false);
                    me->GetMotionMaster()->MoveJump(-9255.41f, 491.74f, 298.28f, 4.5f, 4.5f, POINT_AWAY);
                    break;
                }
                case POINT_AWAY:
                {
                    me->DespawnOrUnsummon(1);
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
                    case EVENT_RIDE_SCHNOTTZ:
                    {
                        events.CancelEvent(EVENT_RIDE_SCHNOTTZ);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(60.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_COMMANDER_SCHNOTTZ)
                                        (*itr)->EnterVehicle(me, 0);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_UP, 1500);
                        break;
                    }
                    case EVENT_MOVE_UP:
                    {
                        events.CancelEvent(EVENT_MOVE_UP);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 248.00f, 8.0f, 3.5f, POINT_TOP);
                        break;
                    }
                    case EVENT_ENABLE_SCHNOTTZ:
                    {
                        events.CancelEvent(EVENT_ENABLE_SCHNOTTZ);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_COMMANDER_SCHNOTTZ)
                                        (*itr)->ToCreature()->AI()->DoAction(1);
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_MOVE_FORWARD:
                    {
                        events.CancelEvent(EVENT_MOVE_FORWARD);
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_COFFER, -9300.19f, 492.92f, 252.00f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_balloonAI(creature);
    }
};

class npc_temple_of_uldum_drake_1 : public CreatureScript
{
public:
   npc_temple_of_uldum_drake_1() : CreatureScript("npc_temple_of_uldum_drake_1") { }

    struct npc_temple_of_uldum_drake_1AI : public ScriptedAI
    {
        npc_temple_of_uldum_drake_1AI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191
        };

        enum pointId
        {
            POINT_TOP       = 1,
            POINT_FORWARD,
            POINT_LAND
        };

        enum eventId
        {
            EVENT_MOVE_UP       = 1,
            EVENT_MOVE_FORWARD,
            EVENT_MOVE_LAND,
            EVENT_FIX_FACING
        };

        enum npcId
        {
            NPC_CAMERA  = 50403
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(true);
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_MOVE_UP, 1500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TOP:
                {
                    events.ScheduleEvent(EVENT_MOVE_FORWARD, 1000);
                    break;
                }
                case POINT_FORWARD:
                {
                    events.ScheduleEvent(EVENT_MOVE_LAND, 1);
                    break;
                }
                case POINT_LAND:
                {
                    events.ScheduleEvent(EVENT_FIX_FACING, 1);
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
                    case EVENT_MOVE_UP:
                    {
                        events.CancelEvent(EVENT_MOVE_UP);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 251.00f, 8.0f, 3.5f, POINT_TOP);
                        break;
                    }
                    case EVENT_MOVE_FORWARD:
                    {
                        events.CancelEvent(EVENT_MOVE_FORWARD);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FORWARD, -9323.89f, 483.69f, me->GetPositionZ()+1);
                        break;
                    }
                    case EVENT_MOVE_LAND:
                    {
                        events.CancelEvent(EVENT_MOVE_LAND);
                        me->SetWalk(false);
                        x = -9330.80f;
                        y = 439.97f;
                        z = 242.87f;
                        Position const moveLand  = {x, y, z};
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        break;
                    }
                    case EVENT_FIX_FACING:
                    {
                        events.CancelEvent(EVENT_FIX_FACING);
                        me->SetFacingTo(0.94f);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_CAMERA)
                                    {
                                        (*itr)->GetMotionMaster()->MovementExpired(false);
                                        (*itr)->GetMotionMaster()->MoveJump(-9326.53f, 466.28f, 253.49f, 15.0f, 15.0f, 7);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
        float x,y,z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_drake_1AI(creature);
    }
};

class npc_temple_of_uldum_drake_2 : public CreatureScript
{
public:
   npc_temple_of_uldum_drake_2() : CreatureScript("npc_temple_of_uldum_drake_2") { }

    struct npc_temple_of_uldum_drake_2AI : public ScriptedAI
    {
        npc_temple_of_uldum_drake_2AI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191
        };

        enum pointId
        {
            POINT_TOP       = 1,
            POINT_FORWARD,
            POINT_LAND
        };

        enum eventId
        {
            EVENT_MOVE_UP       = 1,
            EVENT_MOVE_FORWARD,
            EVENT_MOVE_LAND,
            EVENT_FIX_FACING
        };

        enum npcId
        {
        };

        enum actionId
        {
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(true);
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            events.ScheduleEvent(EVENT_MOVE_UP, 1500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TOP:
                {
                    events.ScheduleEvent(EVENT_MOVE_FORWARD, 1000);
                    break;
                }
                case POINT_FORWARD:
                {
                    events.ScheduleEvent(EVENT_MOVE_LAND, 1);
                    break;
                }
                case POINT_LAND:
                {
                    events.ScheduleEvent(EVENT_FIX_FACING, 1);
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
                    case EVENT_MOVE_UP:
                    {
                        events.CancelEvent(EVENT_MOVE_UP);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 251.00f, 8.0f, 3.5f, POINT_TOP);
                        break;
                    }
                    case EVENT_MOVE_FORWARD:
                    {
                        events.CancelEvent(EVENT_MOVE_FORWARD);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FORWARD, -9283.38f, 490.27f, me->GetPositionZ()+1);
                        break;
                    }
                    case EVENT_MOVE_LAND:
                    {
                        events.CancelEvent(EVENT_MOVE_LAND);
                        me->SetWalk(false);
                        x = -9269.32f;
                        y = 443.19f;
                        z = 243.06f;
                        Position const moveLand  = {x, y, z};
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveLand(POINT_LAND, moveLand);
                        break;
                    }
                    case EVENT_FIX_FACING:
                    {
                        events.CancelEvent(EVENT_FIX_FACING);
                        me->SetFacingTo(1.94f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
        float x,y,z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_drake_2AI(creature);
    }
};

class npc_temple_of_uldum_schnottz : public CreatureScript
{
public:
   npc_temple_of_uldum_schnottz() : CreatureScript("npc_temple_of_uldum_schnottz") { }

    struct npc_temple_of_uldum_schnottzAI : public ScriptedAI
    {
        npc_temple_of_uldum_schnottzAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_CAMERA_CHANNELING     = 88552
        };

        enum pointId
        {
            POINT_FINAL = 10
        };

        enum eventId
        {
            EVENT_CAMERA_ZOOM   = 1,
            EVENT_CANCEL_ZOOM,
            EVENT_MOVE_FINAL,
            EVENT_DIE_MOMENT
        };

        enum npcId
        {
            NPC_CAMERA          = 50403,
            NPC_BEAM_TRIGGER    = 32520
        };

        enum actionId
        {
            ACTION_START_TALK   = 1,
            ACTION_FINAL
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_TALK:
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        TalkWithDelay(3500, 0, playerOwner->GetGUID());
                        TalkWithDelay(9500, 1, playerOwner->GetGUID());
                    }
                    events.ScheduleEvent(EVENT_CAMERA_ZOOM, 500);
                    break;
                }
                case ACTION_FINAL:
                {
                    events.ScheduleEvent(EVENT_MOVE_FINAL, 66000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FINAL:
                {
                    me->SetFacingTo(4.67f);
                    if (playerOwner && playerOwner->IsInWorld() && playerOwner != NULL)
                    {
                        if (playerOwner->GetGUID())
                            TalkWithDelay(2000, 11, playerOwner->GetGUID());
                    }
                    events.ScheduleEvent(EVENT_DIE_MOMENT, 4000);
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
                    case EVENT_CAMERA_ZOOM:
                    {
                        events.CancelEvent(EVENT_CAMERA_ZOOM);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_CAMERA)
                                    {
                                        (*itr)->CastStop();
                                        (*itr)->CastSpell(me, SPELL_CAMERA_CHANNELING, true);
                                        if (Unit* passenger = (*itr)->GetVehicleKit()->GetPassenger(0))
                                            passenger->ChangeSeat(1, true);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_CANCEL_ZOOM, 8000);
                        break;
                    }
                    case EVENT_CANCEL_ZOOM:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_CAMERA)
                                    {
                                        if (Unit* passenger = (*itr)->GetVehicleKit()->GetPassenger(1))
                                            passenger->ChangeSeat(0, true);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_MOVE_FINAL:
                    {
                        events.CancelEvent(EVENT_MOVE_FINAL);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_FINAL, -9299.99f, 498.43f, 242.81f);
                        break;
                    }
                    case EVENT_DIE_MOMENT:
                    {
                        events.CancelEvent(EVENT_DIE_MOMENT);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->SummonCreature(NPC_BEAM_TRIGGER, -9299.99f, 463.72f, 249.61f, 1.50f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_schnottzAI(creature);
    }
};

class npc_temple_of_uldum_beam : public CreatureScript
{
public:
   npc_temple_of_uldum_beam() : CreatureScript("npc_temple_of_uldum_beam") { }

    struct npc_temple_of_uldum_beamAI : public ScriptedAI
    {
        npc_temple_of_uldum_beamAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_UNIQUE_PHASING        = 60191,
            SPELL_ENERGY_BEAM           = 94392,
            SPELL_COFFER_SPARKLE        = 94330,
            SPELL_COFFER_INIT           = 94503,
            SPELL_BEAM_DEATH            = 94426,
            SPELL_SKELETON_SCHNOTTZ     = 94433,
            SPELL_FEIGN_DEATH           = 29266
        };

        enum eventId
        {
            EVENT_CAST_BEAM         = 1,
            EVENT_SPARKLE,
            EVENT_INIT_COFFER,
            EVENT_KILL_ALL,
            EVENT_SUMMON_BRONZEBEARD
        };

        enum npcId
        {
            NPC_DRAKE_1     = 50077,
            NPC_DRAKE_2     = 50078,
            NPC_SCHNOTTZ    = 49466,
            NPC_HARRISON    = 49460,
            NPC_BRONZEBEARD = 49204,
            NPC_CAMERA      = 50403
        };

        void IsSummonedBy(Unit* owner)
        {
            if (me->GetAreaId() == 5669)
            {
                playerOwner = owner;
                owner->AddAura(SPELL_UNIQUE_PHASING, me);
                events.ScheduleEvent(EVENT_CAST_BEAM, 3000);
                events.ScheduleEvent(EVENT_INIT_COFFER, 500);
                events.CancelEvent(EVENT_SPARKLE);
                me->SetObjectScale(1.5f);
            }
        }

        void Reset()
        {
            events.ScheduleEvent(EVENT_SPARKLE, 1000);
            me->SetCanFly(true);
            me->SetDisableGravity(true);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_BEAM:
                    {
                        events.CancelEvent(EVENT_CAST_BEAM);
                        events.CancelEvent(EVENT_INIT_COFFER);
                        me->CastStop();
                        me->GetMotionMaster()->Clear();
                        DoCastAOE(SPELL_ENERGY_BEAM);
                        events.ScheduleEvent(EVENT_KILL_ALL, 5000);
                        break;
                    }
                    case EVENT_SPARKLE:
                    {
                        events.RescheduleEvent(EVENT_SPARKLE, urand(1000, 8000));
                        me->GetMotionMaster()->MoveRandom(8.0f);
                        DoCast(me, SPELL_COFFER_SPARKLE, true);
                        break;
                    }
                    case EVENT_INIT_COFFER:
                    {
                        events.CancelEvent(EVENT_INIT_COFFER);
                        DoCast(SPELL_COFFER_INIT);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_HARRISON:
                                        {
                                            (*itr)->ToCreature()->AI()->Talk(4);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_KILL_ALL:
                    {
                        events.CancelEvent(EVENT_KILL_ALL);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_DRAKE_1:
                                        case NPC_DRAKE_2:
                                        {
                                            (*itr)->AddAura(SPELL_FEIGN_DEATH, (*itr));
                                            break;
                                        }
                                        case NPC_SCHNOTTZ:
                                        {
                                            (*itr)->ToCreature()->AI()->Talk(12);
                                            (*itr)->CastSpell((*itr), SPELL_BEAM_DEATH, true);
                                            (*itr)->CastSpell((*itr), SPELL_SKELETON_SCHNOTTZ, true);
                                            (*itr)->AddAura(SPELL_FEIGN_DEATH, (*itr));
                                            break;
                                        }
                                        case NPC_CAMERA:
                                        {
                                            (*itr)->ToCreature()->AI()->DoAction(2);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_SUMMON_BRONZEBEARD, 2500);
                        break;
                    }
                    case EVENT_SUMMON_BRONZEBEARD:
                    {
                        events.CancelEvent(EVENT_SUMMON_BRONZEBEARD);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->SummonCreature(NPC_BRONZEBEARD, -9308.79f, 449.84f, 242.79f, 1.54f, TEMPSUMMON_TIMED_DESPAWN, 60000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_temple_of_uldum_beamAI(creature);
    }
};

class spell_ping_signal_flare : public SpellScriptLoader
{
    public:
        spell_ping_signal_flare() : SpellScriptLoader("spell_ping_signal_flare") { }

        class spell_ping_signal_flare_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ping_signal_flare_SpellScript);

            enum npcId
            {
                NPC_NORTH_SIGNAL    = 49211,
                NPC_WEST_SIGNAL     = 49215,
                NPC_SOUTH_SIGNAL    = 49216,
                NPC_SIGNAL_FLARE    = 49227
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    Creature* northSignal = caster->FindNearestCreature(NPC_NORTH_SIGNAL, 6.0f, true);
                    Creature* westSignal = caster->FindNearestCreature(NPC_WEST_SIGNAL, 6.0f, true);
                    Creature* southSignal = caster->FindNearestCreature(NPC_SOUTH_SIGNAL, 6.0f, true);
                    Creature* signalFlare = caster->FindNearestCreature(NPC_SIGNAL_FLARE, 6.0f, true);
                    if (northSignal || westSignal || southSignal)
                    {
                        if (!signalFlare || (signalFlare && signalFlare->GetCharmerOrOwner() != caster))
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }


            void HandleQuestCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    Creature* northSignal = caster->FindNearestCreature(NPC_NORTH_SIGNAL, 6.0f, true);
                    Creature* westSignal = caster->FindNearestCreature(NPC_WEST_SIGNAL, 6.0f, true);
                    Creature* southSignal = caster->FindNearestCreature(NPC_SOUTH_SIGNAL, 6.0f, true);
                    if (northSignal)
                    {
                        caster->SummonCreature(NPC_SIGNAL_FLARE, northSignal->GetPositionX(), northSignal->GetPositionY(), northSignal->GetPositionZ(), northSignal->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        caster->ToPlayer()->KilledMonsterCredit(49221);
                    }
                    if (westSignal)
                    {
                        caster->SummonCreature(NPC_SIGNAL_FLARE, westSignal->GetPositionX(), westSignal->GetPositionY(), westSignal->GetPositionZ(), westSignal->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        caster->ToPlayer()->KilledMonsterCredit(49222);
                    }
                    if (southSignal)
                    {
                        caster->SummonCreature(NPC_SIGNAL_FLARE, southSignal->GetPositionX(), southSignal->GetPositionY(), southSignal->GetPositionZ(), southSignal->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                        caster->ToPlayer()->KilledMonsterCredit(49223);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_ping_signal_flare_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_ping_signal_flare_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ping_signal_flare_SpellScript();
        }
};

class spell_three_if_by_air_init : public SpellScriptLoader
{
    public:
        spell_three_if_by_air_init() : SpellScriptLoader("spell_three_if_by_air_init") { }

        class spell_three_if_by_air_init_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_three_if_by_air_init_SpellScript);

            enum spellId
            {
                SPELL_UNIQUE_PHASING    = 60191,
                SPELL_SUMMON_CAMERA     = 94536,
                SPELL_SUMMON_CLONE      = 94537,
                SPELL_SUMMON_CHOPPER    = 94538,
                SPELL_SUMMON_FLARE_01   = 94539,
                SPELL_SUMMON_FLARE_02   = 94540,
                SPELL_SUMMON_FLARE_03   = 94541,
                SPELL_CAST_SIGNAL       = 94544,
                SPELL_FADE_TO_BLACK     = 94053,
                SPELL_DRAKE_VISIB       = 100044
            };

            void HandleQuestComplete()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER || caster->GetVehicleBase() || caster->HasAura(SPELL_FADE_TO_BLACK))
                        return;

                    caster->AddAura(SPELL_UNIQUE_PHASING, caster);
                    caster->CastSpell(caster, SPELL_FADE_TO_BLACK, true);
                    caster->CastSpell(caster, SPELL_SUMMON_CAMERA, true);
                    caster->CastSpell(caster, SPELL_SUMMON_CLONE, true);
                    caster->CastSpell(caster, SPELL_SUMMON_FLARE_01, true);
                    caster->CastSpell(caster, SPELL_SUMMON_FLARE_02, true);
                    caster->CastSpell(caster, SPELL_SUMMON_FLARE_03, true);
                    caster->RemoveAurasDueToSpell(SPELL_DRAKE_VISIB);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_three_if_by_air_init_SpellScript::HandleQuestComplete);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_three_if_by_air_init_SpellScript();
        }
};

class npc_three_if_by_air_camera : public CreatureScript
{
public:
   npc_three_if_by_air_camera() : CreatureScript("npc_three_if_by_air_camera") { }

    struct npc_three_if_by_air_cameraAI : public ScriptedAI
    {
        npc_three_if_by_air_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_SUMMON_CHOPPER        = 94538,
            SPELL_FADE_TO_BLACK         = 94545
        };

        enum pointId
        {
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_SUMMON_CHOPPER,
            EVENT_FOCUS_CHOPPER,
            EVENT_FINISH_QUEST
        };

        enum npcId
        {
            NPC_CASTER_CLONE    = 50625,
            NPC_CHOPPER         = 50686
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->EnterVehicle(me, 0);
                        events.ScheduleEvent(EVENT_SUMMON_CHOPPER, 18000);
                        break;
                    }
                    case EVENT_SUMMON_CHOPPER:
                    {
                        events.CancelEvent(EVENT_SUMMON_CHOPPER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_CHOPPER, true);
                        events.ScheduleEvent(EVENT_FOCUS_CHOPPER, 1000);
                        break;
                    }
                    case EVENT_FOCUS_CHOPPER:
                    {
                        events.CancelEvent(EVENT_FOCUS_CHOPPER);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            passenger->ChangeSeat(1, true);

                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(500.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    if ((*itr)->GetEntry() == NPC_CHOPPER)
                                    {
                                        me->CastStop();
                                        me->CastSpell((*itr), SPELL_CAMERA_CHANNELING, true);
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_FINISH_QUEST, 10000);
                        break;
                    }
                    case EVENT_FINISH_QUEST:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 500.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(500.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_CASTER_CLONE:
                                        case NPC_CHOPPER:
                                        {
                                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
                        {
                            passenger->AddAura(SPELL_FADE_TO_BLACK, passenger);
                            passenger->ExitVehicle();
                        }
                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_three_if_by_air_cameraAI(creature);
    }
};

class npc_three_if_by_air_clone : public CreatureScript
{
public:
   npc_three_if_by_air_clone() : CreatureScript("npc_three_if_by_air_clone") { }

    struct npc_three_if_by_air_cloneAI : public ScriptedAI
    {
        npc_three_if_by_air_cloneAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_MIRROR_AURA   = 93996
        };

        enum pointId
        {
            POINT_WAITING   = 1
        };

        enum eventId
        {
            EVENT_MOVE_TO_WAIT  = 1
        };

        enum npcId
        {
            NPC_SIGNAL_FLARE    = 49227
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(false);
            playerOwner = owner;
            owner->AddAura(SPELL_MIRROR_AURA, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_MOVE_TO_WAIT, 6000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_WAITING:
                {
                    me->SetFacingTo(6.09f);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(100.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                            {
                                if ((*itr)->GetEntry() == NPC_SIGNAL_FLARE)
                                    (*itr)->ToCreature()->AI()->DoAction(1);
                            }
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
                    case EVENT_MOVE_TO_WAIT:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_WAIT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_WAITING, -9287.36f, 475.27f, 242.81f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_three_if_by_air_cloneAI(creature);
    }
};

class npc_three_if_by_air_signal : public CreatureScript
{
public:
   npc_three_if_by_air_signal() : CreatureScript("npc_three_if_by_air_signal") { }

    struct npc_three_if_by_air_signalAI : public ScriptedAI
    {
        npc_three_if_by_air_signalAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_JOCK_SIGNAL   = 94544
        };

        enum eventId
        {
            EVENT_CAST_FLARE    = 1
        };

        enum actionId
        {
            ACTION_SCHEDULE_FLARE   = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SCHEDULE_FLARE:
                {
                    events.ScheduleEvent(EVENT_CAST_FLARE, 2000);
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
                    case EVENT_CAST_FLARE:
                    {
                        events.RescheduleEvent(EVENT_CAST_FLARE, 6000);
                        DoCast(SPELL_JOCK_SIGNAL);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_three_if_by_air_signalAI(creature);
    }
};

class npc_three_if_by_air_chopper : public CreatureScript
{
public:
   npc_three_if_by_air_chopper() : CreatureScript("npc_three_if_by_air_chopper") { }

    struct npc_three_if_by_air_chopperAI : public ScriptedAI
    {
        npc_three_if_by_air_chopperAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum eventId
        {
            EVENT_JOCK_SALUTE   = 1,
            EVENT_MOVE_FORWARD
        };

        enum pointId
        {
            POINT_LAND  = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 2.0f, true);
            events.ScheduleEvent(EVENT_JOCK_SALUTE, 3000);
            events.ScheduleEvent(EVENT_MOVE_FORWARD, 5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_JOCK_SALUTE:
                    {
                        events.CancelEvent(EVENT_JOCK_SALUTE);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            passenger->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                        break;
                    }
                    case EVENT_MOVE_FORWARD:
                    {
                        events.CancelEvent(EVENT_MOVE_FORWARD);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_LAND, -9288.67f, 481.23f, 256.07f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_three_if_by_air_chopperAI(creature);
    }
};

class npc_the_coffer_of_promise_camera : public CreatureScript
{
public:
   npc_the_coffer_of_promise_camera() : CreatureScript("npc_the_coffer_of_promise_camera") { }

    struct npc_the_coffer_of_promise_cameraAI : public ScriptedAI
    {
        npc_the_coffer_of_promise_cameraAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_CAMERA_CHANNELING     = 88552,
            SPELL_FADE_TO_BLACK         = 94545,
            SPELL_SUMMON_BRANN          = 94575,
            SPELL_SUMMON_HARRISON       = 94576,
            SPELL_SUMMON_CLONE          = 94573
        };

        enum pointId
        {
            POINT_FRONT     = 1,
            POINT_RETURN
        };

        enum eventId
        {
            EVENT_RIDE_INVOKER      = 1,
            EVENT_SPAWN_ACTORS,
            EVENT_MOVE_FRONT,
            EVENT_RETURN_SPAWN,
            EVENT_FINISH_QUEST
        };

        enum npcId
        {
            NPC_CASTER_CLONE    = 50623,
            NPC_BRANN           = 49248,
            NPC_HARRISON        = 50651,
            NPC_LASER           = 51231,
            NPC_LASER_TARGET    = 51232
        };

        enum actionId
        {
            ACTION_START_MOVE   = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            playerOwner = owner;
            events.ScheduleEvent(EVENT_RIDE_INVOKER, 500);
            x = NULL;
            y = NULL;
            z = NULL;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_MOVE:
                {
                    events.ScheduleEvent(EVENT_MOVE_FRONT, 5000);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_FRONT:
                {
                    events.ScheduleEvent(EVENT_RETURN_SPAWN, 3000);
                    if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                    {
                        if (playerOwner->GetTypeId() == TYPEID_PLAYER)
                            playerOwner->ToPlayer()->CompleteQuest(28633);
                    }
                    break;
                }
                case POINT_RETURN:
                {
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
                        passenger->ChangeSeat(0, true);
                    events.ScheduleEvent(EVENT_FINISH_QUEST, 5000);
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
                    case EVENT_RIDE_INVOKER:
                    {
                        events.CancelEvent(EVENT_RIDE_INVOKER);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->SetPhaseMask(396, true);
                            playerOwner->AddAura(SPELL_FADE_TO_BLACK, playerOwner);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_CLONE, true);
                            playerOwner->EnterVehicle(me, 0);
                        }
                        events.ScheduleEvent(EVENT_SPAWN_ACTORS, 1000);
                        break;
                    }
                    case EVENT_SPAWN_ACTORS:
                    {
                        events.CancelEvent(EVENT_SPAWN_ACTORS);
                        playerOwner->CastSpell(playerOwner, SPELL_SUMMON_BRANN, true);
                        playerOwner->CastSpell(playerOwner, SPELL_SUMMON_HARRISON, true);
                        break;
                    }
                    case EVENT_MOVE_FRONT:
                    {
                        events.CancelEvent(EVENT_MOVE_FRONT);
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                            passenger->ChangeSeat(1, true);

                        // Save old position
                        x = me->GetPositionX();
                        y = me->GetPositionY();
                        z = me->GetPositionZ();

                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-10782.22f, -346.02f, 17.43f, 2.5f, 2.5f, POINT_FRONT);
                        break;
                    }
                    case EVENT_RETURN_SPAWN:
                    {
                        events.CancelEvent(EVENT_RETURN_SPAWN);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(x, y, z, 2.5f, 2.5f, POINT_RETURN);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_HARRISON:
                                        case NPC_BRANN:
                                        {
                                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_FINISH_QUEST:
                    {
                        if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                        {
                            passenger->AddAura(SPELL_FADE_TO_BLACK, passenger);
                            passenger->ExitVehicle();
                        }
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_CASTER_CLONE:
                                        case NPC_LASER:
                                        case NPC_LASER_TARGET:
                                        {
                                            (*itr)->ToCreature()->DespawnOrUnsummon(1);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }

                        me->DespawnOrUnsummon(5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
        float x,y,z;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_the_coffer_of_promise_cameraAI(creature);
    }
};

class npc_the_coffer_of_promise_clone : public CreatureScript
{
public:
   npc_the_coffer_of_promise_clone() : CreatureScript("npc_the_coffer_of_promise_clone") { }

    struct npc_the_coffer_of_promise_cloneAI : public ScriptedAI
    {
        npc_the_coffer_of_promise_cloneAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_MIRROR_AURA   = 93996
        };

        enum pointId
        {
            POINT_WAITING   = 1
        };

        enum eventId
        {
            EVENT_MOVE_TO_WAIT  = 1
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(true);
            playerOwner = owner;
            owner->AddAura(SPELL_MIRROR_AURA, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_MOVE_TO_WAIT, 5000);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_WAITING:
                {
                    me->SetFacingTo(6.13f);
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
                    case EVENT_MOVE_TO_WAIT:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_WAIT);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_WAITING, -10814.34f, -343.87f, 4.94f);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_the_coffer_of_promise_cloneAI(creature);
    }
};

class npc_the_coffer_of_promise_brann : public CreatureScript
{
public:
   npc_the_coffer_of_promise_brann() : CreatureScript("npc_the_coffer_of_promise_brann") { }

    struct npc_the_coffer_of_promise_brannAI : public ScriptedAI
    {
        npc_the_coffer_of_promise_brannAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_SUMMON_LASER_LEFT     = 94578,
            SPELL_SUMMON_LASER_RIGHT    = 94579,
            SPELL_SUMMON_LASER_TARGET   = 94581,
            SPELL_UNIQUE_PHASING        = 60191
        };

        enum pointId
        {
            POINT_WAITING   = 1
        };

        enum eventId
        {
            EVENT_MOVE_TO_WAIT      = 1,
            EVENT_STAND_AND_SUMMON
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(true);
            playerOwner = owner;
            owner->AddAura(SPELL_UNIQUE_PHASING, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_MOVE_TO_WAIT, 3500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_WAITING:
                {
                    me->SetFacingTo(6.18f);
                    me->SetStandState(UNIT_STAND_STATE_KNEEL);
                    events.ScheduleEvent(EVENT_STAND_AND_SUMMON, 3000);
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
                    case EVENT_MOVE_TO_WAIT:
                    {
                        events.CancelEvent(EVENT_MOVE_TO_WAIT);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                            Talk(0, playerOwner->GetGUID());
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MovePoint(POINT_WAITING, -10809.59f, -343.78f, 5.35f);
                        break;
                    }
                    case EVENT_STAND_AND_SUMMON:
                    {
                        events.CancelEvent(EVENT_STAND_AND_SUMMON);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_LASER_TARGET, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_LASER_LEFT, true);
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_LASER_RIGHT, true);
                        }
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        me->DespawnOrUnsummon(12500);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_the_coffer_of_promise_brannAI(creature);
    }
};

class npc_the_coffer_of_promise_lt : public CreatureScript
{
public:
   npc_the_coffer_of_promise_lt() : CreatureScript("npc_the_coffer_of_promise_lt") { }

    struct npc_the_coffer_of_promise_ltAI : public ScriptedAI
    {
        npc_the_coffer_of_promise_ltAI(Creature* creature) : ScriptedAI(creature) {playerOwner = NULL;}

        EventMap events;

        enum spellId
        {
            SPELL_LASER_BEAM    = 94600
        };

        enum pointId
        {
            POINT_LEFT  = 1,
            POINT_RIGHT
        };

        enum eventId
        {
            EVENT_START_MOVING  = 1,
            EVENT_MOVE_RIGHT,
            EVENT_MOVE_LEFT
        };

        enum npcId
        {
            NPC_LASER_TRIGGER   = 51231,
            NPC_CAMERA          = 50402,
            NPC_HARRISON        = 50651,
            NPC_CASTER_CLONE    = 50623
        };

        void IsSummonedBy(Unit* owner)
        {
            me->SetWalk(true);
            playerOwner = owner;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_START_MOVING, 500);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_LEFT:
                {
                    events.ScheduleEvent(EVENT_MOVE_RIGHT, 1);
                    break;
                }
                case POINT_RIGHT:
                {
                    events.ScheduleEvent(EVENT_MOVE_LEFT, 1);
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
                    case EVENT_START_MOVING:
                    {
                        events.CancelEvent(EVENT_START_MOVING);
                        events.ScheduleEvent(EVENT_MOVE_RIGHT, 1000);
                        if (playerOwner && playerOwner != NULL && playerOwner->IsInWorld())
                        {
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(me, 150.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                            me->VisitNearbyObject(150.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToTempSummon() && (*itr)->ToTempSummon()->GetSummoner() == playerOwner)
                                {
                                    switch ((*itr)->GetEntry())
                                    {
                                        case NPC_LASER_TRIGGER:
                                        {
                                            if ((*itr)->GetEntry() == NPC_LASER_TRIGGER)
                                                (*itr)->CastSpell(me, SPELL_LASER_BEAM, true);
                                            break;
                                        }
                                        case NPC_CAMERA:
                                        {
                                            (*itr)->ToCreature()->AI()->DoAction(1);
                                            break;
                                        }
                                        case NPC_HARRISON:
                                        {
                                            (*itr)->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                                            break;
                                        }
                                        case NPC_CASTER_CLONE:
                                        {
                                            (*itr)->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_MOVE_RIGHT:
                    {
                        events.CancelEvent(EVENT_MOVE_RIGHT);
                        me->GetMotionMaster()->MovePoint(POINT_RIGHT, -10805.43f, -349.38f, 8.31f, true);
                        break;
                    }
                    case EVENT_MOVE_LEFT:
                    {
                        events.CancelEvent(EVENT_MOVE_LEFT);
                        me->GetMotionMaster()->MovePoint(POINT_LEFT, -10804.29f, -339.32f, 8.11f, true);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_the_coffer_of_promise_ltAI(creature);
    }
};

class go_the_coffer_of_promise : public GameObjectScript
{
public:
    go_the_coffer_of_promise() : GameObjectScript("go_the_coffer_of_promise") { }

    enum questId
    {
        QUEST_THE_COFFER_OF_PROMISE    = 28633
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_THE_COFFER_OF_PROMISE) == QUEST_STATUS_COMPLETE)
            return false;
        return true;
    }
};

class go_ud_portal_to_uldum : public GameObjectScript
{
public:
    go_ud_portal_to_uldum() : GameObjectScript("go_ud_portal_to_uldum")
    {
    }

    enum questId
    {
        QUEST_ESCAPE_FROM_THE_LOST_CITY     = 28112
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_ESCAPE_FROM_THE_LOST_CITY) == QUEST_STATUS_REWARDED)
            return false;
        return true;
    }
};

void AddSC_uldum()
{
    new spell_uldum_hammer();
    new npc_lady_humps_intro_uldum();
    new spell_uldum_intro_preparation();
    new npc_uldum_intro_selfmirror();
    new npc_uldum_intro_camera01();
    new npc_adarrah_uldum_intro();
    new npc_uldum_caravan_intro();
    new npc_lady_humps_intro_escort();
    new npc_adarrah_camel_intro_escort();
    new npc_pack_mule_intro_escort();
    new npc_budd_camel_intro_escort();
    new npc_samir_camel_intro_escort();
    new npc_mack_camel_intro_escort();
    new npc_skarf_and_oogah_intro();
    new spell_adarrah_breakout_cage();
    new npc_adarrah_breakout();
    new npc_neferset_jailor_breakout();
    new go_plant_trap_traitors();
    new npc_siamat_traitors();
    new npc_ramkahen_traitors();
    new npc_prince_nadun_escape();
    new npc_adarrah_mantaur();
    new npc_prince_nadun_mantaur();
    new npc_mantaur_camera_event();
    new spell_draining_venom();
    new npc_orsis_survivor_event();
    new npc_post_orsis_camera_event();
    new npc_nadun_post_orsis_event();
    new npc_ramkahen_prisoner_chain();
    new npc_ramkahen_prisoner_event();
    new npc_neferset_overlord_event();
    new npc_dark_ritualist_zakahn();
    new npc_tahet_pit_of_scales();
    new npc_caimas_the_pit_master();
    new npc_entry_gorebite();
    new npc_entry_thartep();
    new npc_entry_kamen();
    new npc_young_crocolisk();
    new spell_tiny_teeth();
    new npc_king_phaoris();
    new npc_high_council_event_camera();
    new npc_king_phaoris_council_event();
    new npc_envoy_council_event();
    new npc_sun_radiance();
    new npc_ramkahen_sergeant();
    new npc_champions_controller();
    new npc_archers_controller();
    new npc_light_controller();
    new spell_move_champions();
    new spell_flame_arrows();
    new spell_sun_radiance();
    new npc_waves_controller();
    new npc_neferset_wave_attacker();
    new npc_infantry_and_archer_counter();
    new npc_nahom_battle_camera();
    new npc_ramkahen_ranger_captain();
    new npc_ramkahen_ranger();
    new spell_mech_control_scrambler();
    new spell_holographic_projector();
    new npc_holographic_image();
    new npc_cursed_engineer();
    new npc_wibson_mainframe();
    new spell_salhet_summon_camera();
    new npc_lions_controller();
    new spell_lions_move();
    new npc_lions_camera();
    new npc_lions_counter();
    new npc_bloodsnarl_scavenger();
    new npc_fusion_core_summoned();
    new spell_summon_fusion_core();
    new npc_crazed_gnome();
    new npc_fusion_core_pivot();
    new npc_dark_pharaoh_tekahn();
    new npc_pyramid_watcher();
    new npc_ramkahen_champion_tekahn();
    new npc_king_phaoris_tekahn();
    new npc_fall_of_neferset_camera();
    new spell_summon_camera_explosionation();
    new npc_camera_explosionation();
    new npc_explosionation_clone();
    new npc_summoned_pygmy();
    new npc_harrison_mule();
    new npc_harrison_jones_explosionation();
    new npc_explosionation_expl_dummy();
    new npc_harrison_jones_ots();
    new areatrigger_quest_tod();
    new spell_sapphire_sight();
    new npc_harrison_jones_cots();
    new npc_harrison_jones_camera_cots();
    new npc_harrison_jones_cots_summon();
    new npc_player_clone_cots();
    new npc_harrison_jones_btlos();
    new npc_camera_bunny_btlos();
    new npc_staff_bunny_btlos();
    new npc_uldum_watcher();
    new spell_orb_of_the_stars();
    new npc_orb_of_the_stars_camera();
    new spell_activate_guardian();
    new npc_titanic_guardian();
    new npc_titanic_guardian_meteor();
    new npc_ignition_camera_event();
    new spell_fire_lpac();
    new npc_commander_schnottz();
    new npc_schnottz_siege_tank();
    new npc_schnottz_siege_tank_summoned();
    new npc_schnottz_siege_turret();
    new npc_decrepit_watcher();
    new npc_commander_schnottz_awake();
    new npc_harrison_jones_tailgunner();
    new npc_tailgunner_clone();
    new npc_tailgunner_camera();
    new npc_tailgunner_bomber();
    new npc_tailgunner_fighter();
    new npc_commander_firing_squad();
    new npc_firing_squad_clone();
    new npc_firing_squad_camera();
    new npc_firing_squad_commander_summon();
    new npc_firing_squad_emissary_01();
    new npc_firing_squad_emissary_02();
    new npc_firing_squad_harrison();
    new npc_two_tents_caravan();
    new npc_two_tents_sullah();
    new spell_sullah_camel_harness();
    new spell_camel_tow_completion();
    new npc_captured_wild_camel();
    new spell_sullah_pigmy_pen();
    new spell_completion_checks();
    new npc_otm_camera_event();
    new npc_otm_clone_event();
    new npc_otm_elite_event();
    new npc_otm_myzerian_event();
    new npc_myzerian_sentinel();
    new spell_shroud_of_the_makers();
    new spell_completion_check_sec();
    new npc_md_camera_event();
    new npc_md_explosion_bunny();
    new spell_schnottz_so_fast_complete();
    new npc_com_camera_event();
    new npc_harrison_bad_datas();
    new npc_bad_datas_summon();
    new npc_lunar_crystal();
    new npc_titanic_guardian_crystal();
    new spell_ill_do_it_by_hand_init();
    new npc_chamber_moon_camera_final();
    new npc_confiscated_artillery();
    new npc_artillery_seat();
    new npc_schnottz_elite_infantryman();
    new spell_fire_from_the_sky_init();
    new npc_fire_from_the_sky_camera();
    new npc_harrison_fortune_and_glory();
    new npc_schnottz_rifleman_fortune();
    new npc_obsidian_colossus();
    new spell_temple_of_uldum_init();
    new npc_temple_of_uldum_clone();
    new npc_temple_of_uldum_harrison();
    new npc_temple_of_uldum_camera();
    new npc_temple_of_uldum_balloon();
    new npc_temple_of_uldum_drake_1();
    new npc_temple_of_uldum_drake_2();
    new npc_temple_of_uldum_schnottz();
    new npc_temple_of_uldum_beam();
    new spell_ping_signal_flare();
    new spell_three_if_by_air_init();
    new npc_three_if_by_air_camera();
    new npc_three_if_by_air_clone();
    new npc_three_if_by_air_signal();
    new npc_three_if_by_air_chopper();
    new npc_the_coffer_of_promise_camera();
    new npc_the_coffer_of_promise_clone();
    new npc_the_coffer_of_promise_brann();
    new npc_the_coffer_of_promise_lt();
    new go_the_coffer_of_promise();
    new go_ud_portal_to_uldum();
}
