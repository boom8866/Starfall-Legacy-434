
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
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
#include "ObjectAccessor.h"

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
        EVENT_REMOVE_PASSENGERS
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
                        if (playerOwner && playerOwner != NULL && playerOwner->GetVehicleBase())
                            playerOwner->GetVehicle()->GetPassenger(0)->ChangeSeat(2, true);
                        break;
                    }
                    case EVENT_SWITCH_SEAT:
                    {
                        events.CancelEvent(EVENT_SWITCH_SEAT);
                        if (playerOwner && playerOwner != NULL && playerOwner->GetVehicleBase())
                            playerOwner->GetVehicle()->GetPassenger(2)->ChangeSeat(1, true);

                        me->NearTeleportTo(-8937.54f,-1725.59f, 125.31f, 2.09f);
                        break;
                    }
                    case EVENT_FADE_TO_BLACK:
                    {
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL && playerOwner->GetVehicleBase())
                            playerOwner->GetVehicle()->GetPassenger(1)->ChangeSeat(0, true);
                        break;
                    }
                    case EVENT_SEAT_UNDER_ATTACK:
                    {
                        events.CancelEvent(EVENT_SEAT_UNDER_ATTACK);
                        me->GetMotionMaster()->MovementExpired(false);
                        me->GetMotionMaster()->MoveJump(-8992.04f, -1663.47f, 108.99f, 25.0f, 25.0f, POINT_RIDGE);
                        if (playerOwner && playerOwner != NULL && playerOwner->GetVehicleBase())
                        {
                            playerOwner->CastSpell(playerOwner, SPELL_SUMMON_SKARF, true);
                            playerOwner->GetVehicle()->GetPassenger(0)->ChangeSeat(2, true);
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
                        if (playerOwner && playerOwner != NULL)
                            playerOwner->CastWithDelay(8000, playerOwner, SPELL_FADE_TO_BLACK, true);
                        break;
                    }
                    case EVENT_TELEPORT_CAMERA:
                    {
                        events.CancelEvent(EVENT_TELEPORT_CAMERA);
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL && playerOwner->GetVehicle())
                            playerOwner->GetVehicle()->RemoveAllPassengers();
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
                        if (playerOwner && playerOwner != NULL)
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
                    if (playerOwner && playerOwner != NULL)
                        TalkWithDelay(1000, 0, playerOwner->GetGUID());
                    me->m_Events.AddEvent(new openCage(me), (me)->m_Events.CalculateTime(7500));
                    events.ScheduleEvent(EVENT_EVADE_FROM_CAGE, 8500);
                    break;
                }
                case ACTION_CALL_JAILOR:
                {
                    if (playerOwner && playerOwner != NULL)
                        playerOwner->SummonCreature(NPC_ENTRY_NEFERSET_JAILOR, -11032.55f, -1268.66f, 13.24f, 0.23f, TEMPSUMMON_TIMED_DESPAWN, 300000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
                    break;
                }
                case ACTION_FINAL_TALK:
                {
                    if (playerOwner && playerOwner != NULL)
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
                    if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                    if (playerOwner && playerOwner != NULL)
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

                        if (playerOwner && playerOwner != NULL)
                            TalkWithDelay(5000, 1, playerOwner->GetGUID());

                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 12000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        if (playerOwner && playerOwner != NULL && playerOwner->GetTypeId() == TYPEID_PLAYER)
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
                    if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                            if (playerOwner && playerOwner != NULL)
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
                    if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
                            playerOwner->CastWithDelay(5500, playerOwner, SPELL_FADE_TO_BLACK, true);
                        events.ScheduleEvent(EVENT_QUEST_COMPLETE, 8000);
                        break;
                    }
                    case EVENT_QUEST_COMPLETE:
                    {
                        events.CancelEvent(EVENT_QUEST_COMPLETE);
                        if (playerOwner && playerOwner != NULL)
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
                    if (playerOwner && playerOwner != NULL)
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
                        DoCastAOE(SPELL_SHADOW_BOLT_VOLLEY);
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
        SPELL_COSMETIC_ROPE     = 87926
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
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
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

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
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
        EVENT_CHECK_EGGS
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
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            crocksDead = 0;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            DoAction(ACTION_MOVE_TO_TALK);
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
                        if (targetInvoker && targetInvoker != NULL)
                        {
                            if (targetInvoker->IsVehicle())
                                me->EnterVehicle(targetInvoker, urand(0,8));
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
                            if (playerOwner && playerOwner != NULL)
                                kamses->AI()->TalkWithDelay(1000, 0, playerOwner->GetGUID());
                        }
                        if (Creature* vizier = me->FindNearestCreature(NPC_ENTRY_VIZIER, 50.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL)
                                vizier->AI()->TalkWithDelay(8000, 0, playerOwner->GetGUID());
                        }
                        if (Creature* amet = me->FindNearestCreature(NPC_ENTRY_AMET, 50.0f, true))
                        {
                            if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                    if (playerOwner && playerOwner != NULL)
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
        NPC_WAVES_CONTROLLER    = 48486
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
            player->SummonCreature(NPC_LIGHT_CONTROLLER, -9796.28f, -1730.66f, 60.93f, 0.88f, TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
                        if (playerOwner && playerOwner != NULL)
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
                        if (playerOwner && playerOwner != NULL)
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
                        if (playerOwner && playerOwner != NULL)
                        {
                            events.CancelEvent(EVENT_ORDER_LAUNCH);
                            std::list<Unit*> targets;
                            Trinity::AnyUnitInObjectRangeCheck u_check(playerOwner, 300.0f);
                            Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(playerOwner, targets, u_check);
                            playerOwner->VisitNearbyObject(300.0f, searcher);
                            for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_ENTRY_SUN_RADIANCE)
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
                        if (playerOwner && playerOwner != NULL)
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
            if (playerOwner && playerOwner != NULL)
                playerOwner->AddAura(SPELL_UNIQUE_PHASING, me);
            else
                me->DespawnOrUnsummon(1000);
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
                    if (playerOwner && playerOwner != NULL)
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
}
