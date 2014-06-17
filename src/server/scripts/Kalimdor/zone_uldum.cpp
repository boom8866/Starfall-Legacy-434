
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
}
