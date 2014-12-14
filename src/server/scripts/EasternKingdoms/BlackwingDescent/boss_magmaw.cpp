
#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "blackwing_descent.h"

enum Spells
{
    // Magmaw
    SPELL_MAGMA_SPIT                = 78359,
    SPELL_MAGMA_SPIT_NO_TARGET      = 78068,
    SPELL_PILLAR_OF_FLAME_AOE       = 77998,
    SPELL_PILLAR_OF_FLAME_MISSILE   = 78010,
    SPELL_LAVA_SPEW                 = 77839,
    SPELL_MANGLE                    = 89773,
    SPELL_MANGLE_DUMMY              = 92047,
    SPELL_MANGLED_DEAD              = 78362,
    SPELL_MANGLE_VEHICLE            = 78360,
    SPELL_SWELTERING_ARMOR          = 78199,
    SPELL_MASSIVE_CRASH             = 88253,
    SPELL_IMPALE_SELF               = 77907,

    SPELL_CONTROL_VEHICLE           = 77901, // Casted on Pincers

    SPELL_LAUNCH_HOOK_1             = 77917,
    SPELL_LAUNCH_HOOK_2             = 77941,

    // Exposed Head of Magmaw
    SPELL_POINT_OF_VULNERABILITY    = 79011, // Increase Damage taken
    SPELL_RIDE_VEHICLE              = 89743,

    SPELL_POINT_OF_VULNERABILITY_2  = 79010, // Share Damage
    SPELL_QUEST_INVIS_5             = 95478, // WTF!

    // Pincers
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
    SPELL_EJECT_PASSENGER           = 77946,
    SPELL_RIDE_VEHICLE_2            = 95727, // eject pincer passenger

    // Pillar of Flame
    SPELL_PILLAR_OF_FLAME_DUMMY     = 78017,
    SPELL_PILLAR_OF_FLAME_SUMMON    = 77973,
    SPELL_PILLAR_OF_FLAME_KNOCKBACK = 77971,

    // Lava Parasite
    SPELL_PARASITIC_INFECTION_1     = 78097,
    SPELL_PARASITIC_INFECTION_2     = 78941,
    SPELL_LAVA_PARASITE_PROC        = 78019,
    SPELL_LAVA_PARASITE             = 78020,

    // Massive Crash
    SPELL_MASSIVE_CRASH_DAMAGE      = 88287,

    // Magmaw Spike Dummy
    SPELL_EJECT_PASSENGERS          = 78643,
    SPELL_CHAIN_VISUAL_1            = 77929,
    SPELL_CHAIN_VISUAL_2            = 77940,

};

enum Events
{
    // Magmaw
    EVENT_MAGMA_SPIT = 1,
    EVENT_PILLAR_OF_FLAME,
    EVENT_LAVA_SPEW,
    EVENT_MANGLE,
    EVENT_MANGLE_DEAD,
    EVENT_SUMMON_CRASH_VISUAL,
    EVENT_MASSIVE_CRASH,
    EVENT_ENABLE_PINCERS,
    EVENT_DISABLE_PINCERS,
    EVENT_ATTACK,
    EVENT_TALK_IMPALE,
    EVENT_FINISH_IMPALE,

    // Nefarian
    EVENT_TALK_AGGRO_1,
    EVENT_TALK_AGGRO_2,
};

enum Actions
{
    ACTION_IMPALE_SELF = 1,
};

enum Texts
{
    // Magmaw
    SAY_ANNOUNCE_PILLAR_OF_FLAME    = 0,
    SAY_ANNOUNCE_MASSIVE_CRASH      = 1,
    SAY_ANNOUNCE_IMPALE             = 2,
    SAY_ANNOUNCE_BREAK_FREE         = 3,
    SAY_ANNOUNCE_MANGLE_TARGET      = 4,

    // Nefarian
    SAY_AGGRO_1                     = 0,
    SAY_AGGRO_2                     = 1,
    SAY_DEATH                       = 2,
};

enum Miscs
{
    // Magmaw
    CRASH_LEFT  = 1,
    CRASH_RIGHT = 2,
};

Position const CrashPos[] =
{
    {-288.59f, -14.8472f, 211.2573f, 3.647738f},  // Left Side
    {-294.736f, -11.4306f, 211.2573f, 4.625123f}, // Right Side
};

Position const CrushVisualLeft[] =
{
    {-337.375f, -43.6615f, 212.0853f, 0.01745329f},
    {-346.3333f, -31.71354f, 211.6433f, 6.161012f},
    {-341.177f, -52.6892f, 212.8323f, 0.1047198f},
    {-333.566f, -33.6076f, 211.4583f, 6.108652f}, 
    {-328.618f, -50.2396f, 211.9823f, 0.3665192f},
    {-350.08f, -60.0764f, 214.0583f, 0.06981317f},
    {-322.295f, -38.5278f, 211.7913f, 6.248279f},
    {-338.257f, -62.4462f, 212.9573f, 0.05235988f},
    {-349.906f, -62.3403f, 215.3523f, 0.01745329f},
    {-328.802f, -24.9653f, 211.3363f, 6.073746f},
    {-321.983f, -54.4618f, 212.1523f, 1.012291f},
    {-328.76f, -62.691f, 212.5793f, 0.9424778f},
    {-317.934f, -29.7604f, 211.3923f, 6.108652f},
    {-314.66f, -44.7049f, 212.7873f, 1.012291f},
    {-334.538f, -71.0017f, 213.4883f, 1.082104f},
    {-344.514f, -73.4253f, 214.1683f, 0.122173f},
    {-351.951f, -84.474f, 214.0223f, 5.864306f},
    {-342.142f, -80.7257f, 214.0403f, 1.134464f},
    {-308.677f, -26.7292f, 211.4183f, 6.230825f},
};

Position const CrushVisualRight[] =
{
    {-311.4653f, -48.59722f, 212.8065f, 1.064651f},
    {-322.063f, -67.8993f, 213.4903f, 1.047198f},
    {-307.519f, -41.3299f, 211.7793f, 1.117011f},
    {-307.531f, -35.4375f, 211.8153f, 1.029744f},
    {-313.043f, -67.6042f, 213.1063f, 0.7330383f},
    {-327.238f, -78.3177f, 213.9843f, 1.047198f},
    {-304.632f, -57.7813f, 212.6513f, 0.9948376f},
    {-301.389f, -48.184f, 212.7253f, 0.5934119f},
    {-319.583f, -79.7934f, 213.5293f, 0.8203048f},
    {-296.743f, -42.9635f, 211.9613f, 0.9948376f},
    {-332.335f, -88.3212f, 213.9923f, 1.047198f},
    {-307.99f, -75.2205f, 214.0263f, 0.6806784f},
    {-294.569f, -56.066f, 213.0713f, 1.064651f},
    {-323.554f, -90.3785f, 214.0273f, 0.7679449f},
    {-295.868f, -67.7691f, 213.6333f, 1.012291f},
    {-313.292f, -87.1059f, 214.1703f, 0.7504916f},
    {-298.063f, -79.6476f, 214.0233f, 1.012291f},
    {-304.181f, -90.1806f, 214.1653f, 1.43117f},
    {-317.28f, -58.316f, 213.0713f, 1.064651f},
};

class boss_magmaw : public CreatureScript
{
public:
    boss_magmaw() : CreatureScript("boss_magmaw") { }

    struct boss_magmawAI : public BossAI
    {
        boss_magmawAI(Creature* creature) : BossAI(creature, DATA_MAGMAW)
        {
            _crashSide = 0;
            _impaled = 0;
        }

        uint8 _crashSide;
        bool _impaled;

        void Reset()
        {
            _Reset();
            SetCombatMovement(false);
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_MAGMA_SPIT, 10000);
            events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000);
            events.ScheduleEvent(EVENT_LAVA_SPEW, 18000);
            events.ScheduleEvent(EVENT_MANGLE, 90000);
            events.ScheduleEvent(EVENT_TALK_AGGRO_1, 3000);
        }

        void JustDied(Unit* killer)
        {
            _JustDied();
            summons.DespawnAll();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            summons.DespawnAll();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            if (Unit* head = me->GetVehicleKit()->GetPassenger(3))
                head->ToCreature()->AI()->EnterEvadeMode();
            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_ALLOW_ENEMY_INTERACT | UNIT_FLAG2_REGENERATE_POWER);
            _crashSide = 0;
            _impaled = false;
            _DespawnAtEvade();
        }

        void JustRespawned()
        {
            me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_EXPOSED_HEAD_OF_MAGMAW:
                case NPC_EXPOSED_HEAD_OF_MAGMAW_2:
                    break;
                default:
                    summons.Summon(summon);
                    break;
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_PILLAR_OF_FLAME_DUMMY:
                    DoCast(SPELL_PILLAR_OF_FLAME_MISSILE);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_PILLAR_OF_FLAME_MISSILE:
                    target->CastSpell(target, SPELL_PILLAR_OF_FLAME_SUMMON);
                    target->CastSpell(target, SPELL_PILLAR_OF_FLAME_KNOCKBACK);
                    target->ToCreature()->DespawnOrUnsummon(2600);
                    break;
                case SPELL_MANGLE:
                    Talk(SAY_ANNOUNCE_MANGLE_TARGET, target->GetGUID());
                    break;
                default:
                    break;
            }
        }

        void PassengerBoarded(Unit* passenger, int8 SeatId, bool apply)
        {
            if (apply)
            {
                switch (SeatId)
                {
                    case 3:
                    case 4:
                        if (!me->HasAura(SPELL_POINT_OF_VULNERABILITY_2, passenger->GetGUID()))
                        {
                            passenger->AddAura(SPELL_POINT_OF_VULNERABILITY_2, me);
                            me->AddAura(SPELL_POINT_OF_VULNERABILITY_2, passenger);
                        }
                        break;
                    default:
                        break;
                }
            }
            else
            {
                float ori = me->GetOrientation();
                float x = me->GetPositionX()+cos(ori)*25;
                float y = me->GetPositionY()+sin(ori)*25;
                float z = me->GetPositionZ()+3.0f;
                Position const ExitPos = {x, y, z};
                passenger->GetMotionMaster()->MoveJump(ExitPos, 18.0f, 15.0f);
            }

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
                    case EVENT_MAGMA_SPIT:
                    {
                        Map::PlayerList const& playerList = me->GetMap()->GetPlayers();

                        if (playerList.isEmpty())
                            return;

                        for (uint8 i = 0; i <= (Is25ManRaid() ? 8 : 3); i++)
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, i))
                            {
                                if (!me->IsWithinDistInMap(me->getVictim(), me->GetFloatValue(UNIT_FIELD_COMBATREACH)))
                                    DoCast(target, SPELL_MAGMA_SPIT_NO_TARGET);
                                else
                                    DoCast(target, SPELL_MAGMA_SPIT);
                            }
                        }
                        events.ScheduleEvent(EVENT_MAGMA_SPIT, 10000);
                        break;
                    }
                    case EVENT_PILLAR_OF_FLAME:
                        Talk(SAY_ANNOUNCE_PILLAR_OF_FLAME);
                        DoCast(SPELL_PILLAR_OF_FLAME_AOE);
                        events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000, 40000);
                        break;
                    case EVENT_LAVA_SPEW:
                        DoCast(SPELL_LAVA_SPEW);
                        events.ScheduleEvent(EVENT_LAVA_SPEW, 22000);
                        break;
                    case EVENT_MANGLE:
                        me->CastStop();
                        if (me->getVictim())
                            if (!me->IsWithinDistInMap(me->getVictim(), me->GetFloatValue(UNIT_FIELD_COMBATREACH)))
                            {
                                DoCast(me->getVictim(), SPELL_MANGLE);
                                me->getVictim()->CastSpell(me->getVictim(), SPELL_SWELTERING_ARMOR, true);
                                DoCast(SPELL_MANGLE_DUMMY);
                                events.ScheduleEvent(EVENT_SUMMON_CRASH_VISUAL, 4000);
                            }
                        switch (urand(0, 7)) // so many cases to provide best possible random cases
                        {
                            case 1: // Left Crash
                            case 3:
                            case 5:
                            case 7:
                                _crashSide = CRASH_LEFT;
                                break;
                            case 0: // Right Crash
                            case 2:
                            case 4:
                            case 6:
                                _crashSide = CRASH_RIGHT;
                                break;
                        }
                        break;
                    case EVENT_MANGLE_DEAD:
                        if (Unit* tank = me->GetVehicleKit()->GetPassenger(2))
                            tank->CastSpell(tank, SPELL_MANGLED_DEAD, true);
                        break;
                    case EVENT_SUMMON_CRASH_VISUAL:
                        switch (_crashSide)
                        {
                            case CRASH_LEFT:
                                for (uint8 i = 0; i < 19; i++)
                                    me->SummonCreature(NPC_ROOM_STALKER, CrushVisualLeft[i], TEMPSUMMON_TIMED_DESPAWN, 6000);
                                break;
                            case CRASH_RIGHT:
                                for (uint8 i = 0; i < 19; i++)
                                    me->SummonCreature(NPC_ROOM_STALKER, CrushVisualRight[i], TEMPSUMMON_TIMED_DESPAWN, 6000);
                                break;
                            default:
                                break;
                        }
                        events.ScheduleEvent(EVENT_MASSIVE_CRASH, 5000);
                        break;
                    case EVENT_MASSIVE_CRASH:
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->CastStop();
                        events.Reset();

                        switch (_crashSide)
                        {
                            case CRASH_LEFT:
                                if (Creature* crashDummy = me->SummonCreature(NPC_MASSIVE_CRASH, CrashPos[0], TEMPSUMMON_TIMED_DESPAWN, 6000))
                                    crashDummy->CastWithDelay(1100, crashDummy, SPELL_MASSIVE_CRASH_DAMAGE);
                                me->SetFacingTo(3.581246f);
                                break;
                            case CRASH_RIGHT:
                                if (Creature* crashDummy = me->SummonCreature(NPC_MASSIVE_CRASH, CrashPos[1], TEMPSUMMON_TIMED_DESPAWN, 6000))
                                    crashDummy->CastWithDelay(1100, crashDummy, SPELL_MASSIVE_CRASH_DAMAGE);
                                me->SetFacingTo(4.625123f);
                                break;
                            default:
                                break;
                        }
                        me->CastWithDelay(100, me, SPELL_MASSIVE_CRASH);
                        events.ScheduleEvent(EVENT_ENABLE_PINCERS, 1000);
                        events.ScheduleEvent(EVENT_MANGLE_DEAD, 20000); // Massive Crash has used 9 seconds so mangled tank got 21 seconds left
                        break;
                    case EVENT_ENABLE_PINCERS:
                        Talk(SAY_ANNOUNCE_MASSIVE_CRASH);
                        if (Unit* pincer1 = me->GetVehicleKit()->GetPassenger(0))
                            if (Unit* pincer2 = me->GetVehicleKit()->GetPassenger(1))
                            {
                                pincer1->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                pincer2->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            }
                        me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_ALLOW_ENEMY_INTERACT | UNIT_FLAG2_REGENERATE_POWER);
                        events.ScheduleEvent(EVENT_DISABLE_PINCERS, 6000);
                        break;
                    case EVENT_DISABLE_PINCERS:
                        if (Unit* pincer1 = me->GetVehicleKit()->GetPassenger(0))
                            if (Unit* pincer2 = me->GetVehicleKit()->GetPassenger(1))
                            {
                                if (!pincer1->GetVehicleKit()->GetPassenger(0))
                                    pincer1->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                if (!pincer2->GetVehicleKit()->GetPassenger(0))
                                    pincer2->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_ALLOW_ENEMY_INTERACT | UNIT_FLAG2_REGENERATE_POWER);
                            }
                        break;
                    case EVENT_TALK_AGGRO_1:
                        if (Creature* nefarian = me->FindNearestCreature(NPC_NEFARIAN_STALKER, 500.0f))
                            nefarian->AI()->TalkToMap(SAY_AGGRO_1);
                        events.ScheduleEvent(EVENT_TALK_AGGRO_2, 12000);
                        break;
                    case EVENT_TALK_AGGRO_2:
                        if (Creature* nefarian = me->FindNearestCreature(NPC_NEFARIAN_STALKER, 500.0f))
                            nefarian->AI()->TalkToMap(SAY_AGGRO_2);
                        break;
                    case EVENT_TALK_IMPALE:
                        Talk(SAY_ANNOUNCE_IMPALE);
                        me->RemoveAurasDueToSpell(SPELL_CHAIN_VISUAL_1);
                        me->RemoveAurasDueToSpell(SPELL_CHAIN_VISUAL_2);
                        if (Unit* tank = me->GetVehicleKit()->GetPassenger(2))
                        {
                            float ori = me->GetOrientation();
                            float x = me->GetPositionX()+cos(ori)*25;
                            float y = me->GetPositionY()+sin(ori)*25;
                            float z = me->GetPositionZ()+3.0f;
                            Position const ExitPos = {x, y, z};
                            tank->ExitVehicle();
                            tank->GetMotionMaster()->MoveJump(ExitPos, 18.0f, 15.0f);
                        }
                        if (Unit* head = me->GetVehicleKit()->GetPassenger(3))
                            head->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_FINISH_IMPALE, 30000);
                        break;
                    case EVENT_FINISH_IMPALE:
                        if (Unit* head = me->GetVehicleKit()->GetPassenger(3))
                            head->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_ATTACK, 2000);

                        break;
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        _impaled = false;
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_IMPALE_SELF:
                    if (!_impaled)
                    {
                        events.Reset();
                        if (Creature* spike = me->FindNearestCreature(NPC_SPIKE_DUMMY, 300.0f, true))
                        {
                            me->SetFacingToObject(spike);
                            me->CastWithDelay(100, me, SPELL_IMPALE_SELF);
                            events.ScheduleEvent(EVENT_TALK_IMPALE, 6000);
                            spike->CastSpell(me, SPELL_EJECT_PASSENGERS);
                            spike->CastSpell(me, SPELL_CHAIN_VISUAL_1);
                            spike->CastSpell(me, SPELL_CHAIN_VISUAL_2);

                            float ori = me->GetOrientation();
                            float x = me->GetPositionX()+cos(ori)*20;
                            float y = me->GetPositionY()+sin(ori)*20;
                            float z = spike->GetPositionZ() + 3.0f;
                            Position const ExitPos = {x, y, z};

                            if (Unit* pincer1 = me->GetVehicleKit()->GetPassenger(0))
                            {
                                pincer1->CastStop();
                                if (Unit* passenger1 = pincer1->GetVehicleKit()->GetPassenger(0))
                                {
                                    passenger1->ExitVehicle();
                                    passenger1->GetMotionMaster()->MoveJump(ExitPos, 18.0f, 15.0f);
                                    pincer1->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                }
                            }

                            if (Unit* pincer2 = me->GetVehicleKit()->GetPassenger(1))
                            {
                                pincer2->CastStop();
                                if (Unit* passenger2 = pincer2->GetVehicleKit()->GetPassenger(0))
                                {
                                    passenger2->ExitVehicle();
                                    passenger2->GetMotionMaster()->MoveJump(ExitPos, 18.0f, 15.0f);
                                    pincer2->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                }
                            }
                            _impaled = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_magmawAI (creature);
    }
};

class npc_exposed_head_of_magmaw : public CreatureScript
{
public:
    npc_exposed_head_of_magmaw() : CreatureScript("npc_exposed_head_of_magmaw") { }

    struct npc_exposed_head_of_magmawAI : public ScriptedAI
    {
        npc_exposed_head_of_magmawAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset()
        {
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_exposed_head_of_magmawAI (creature);
    }
};

class npc_exposed_head_of_magmaw_tank : public CreatureScript
{
public:
    npc_exposed_head_of_magmaw_tank() : CreatureScript("npc_exposed_head_of_magmaw_tank") { }

    struct npc_exposed_head_of_magmaw_tankAI : public ScriptedAI
    {
        npc_exposed_head_of_magmaw_tankAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset()
        {
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_exposed_head_of_magmaw_tankAI (creature);
    }
};

class npc_bwd_magmaws_pincer : public CreatureScript
{
public:
    npc_bwd_magmaws_pincer() : CreatureScript("npc_bwd_magmaws_pincer") { }

    struct npc_bwd_magmaws_pincerAI : public ScriptedAI
    {
        npc_bwd_magmaws_pincerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset()
        {
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_EJECT_PASSENGERS)
                me->GetVehicleKit()->RemoveAllPassengers();
        }

        void PassengerBoarded(Unit* passenger, int8 /*SeatId*/, bool apply)
        {
            if (!apply)
            {
                float ori = me->GetOrientation();
                float x = me->GetPositionX()+cos(ori)*25;
                float y = me->GetPositionY()+sin(ori)*25;
                float z = me->GetPositionZ()+3.0f;
                Position const ExitPos = {x, y, z};
                passenger->GetMotionMaster()->MoveJump(ExitPos, 18.0f, 15.0f);
            }
        }

        void UpdateAI(uint32 diff)
        {
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bwd_magmaws_pincerAI (creature);
    }
};

class npc_bwd_pillar_of_flame : public CreatureScript
{
public:
    npc_bwd_pillar_of_flame() : CreatureScript("npc_bwd_pillar_of_flame") { }

    struct npc_bwd_pillar_of_flameAI : public ScriptedAI
    {
        npc_bwd_pillar_of_flameAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCast(SPELL_PILLAR_OF_FLAME_DUMMY);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bwd_pillar_of_flameAI (creature);
    }
};

class npc_bwd_lava_parasite : public CreatureScript
{
public:
    npc_bwd_lava_parasite() : CreatureScript("npc_bwd_lava_parasite") { }

    struct npc_bwd_lava_parasiteAI : public ScriptedAI
    {
        npc_bwd_lava_parasiteAI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetInCombatWithZone();
            me->AddAura(SPELL_LAVA_PARASITE_PROC, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(3000);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_LAVA_PARASITE:
                    DoCast(target, SPELL_PARASITIC_INFECTION_1);
                    DoCast(target, SPELL_PARASITIC_INFECTION_2);
                    me->DespawnOrUnsummon(100);
                    break;
                default:
                    break;
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
        return new npc_bwd_lava_parasiteAI (creature);
    }
};

class npc_bwd_spike_dummy : public CreatureScript
{
public:
    npc_bwd_spike_dummy() : CreatureScript("npc_bwd_spike_dummy") { }

    struct npc_bwd_spike_dummyAI : public ScriptedAI
    {
        npc_bwd_spike_dummyAI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_LAUNCH_HOOK_1:
                    if (me->HasAura(SPELL_LAUNCH_HOOK_2))
                        if (Creature* magmaw = me->FindNearestCreature(BOSS_MAGMAW, 200.0f, true))
                            magmaw->AI()->DoAction(ACTION_IMPALE_SELF);
                    break;
                case SPELL_LAUNCH_HOOK_2:
                    if (me->HasAura(SPELL_LAUNCH_HOOK_1))
                        if (Creature* magmaw = me->FindNearestCreature(BOSS_MAGMAW, 200.0f, true))
                            magmaw->AI()->DoAction(ACTION_IMPALE_SELF);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bwd_spike_dummyAI (creature);
    }
};

class spell_bwd_pillar_of_flame_aoe : public SpellScriptLoader
{
public:
    spell_bwd_pillar_of_flame_aoe() : SpellScriptLoader("spell_bwd_pillar_of_flame_aoe") { }

    class spell_bwd_pillar_of_flame_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bwd_pillar_of_flame_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            std::list<WorldObject*>::iterator it = targets.begin();

            while (it != targets.end())
            {
                if (!GetCaster())
                    return;

                WorldObject* unit = *it;

                if (!unit)
                    continue;

                if (unit->GetDistance2d(GetCaster()) <= 15.0f)
                    it = targets.erase(it);
                else
                    it++;
            }

            if (targets.size() != 0)
                Trinity::Containers::RandomResizeList(targets, 1);
            else
                targets.push_back(GetCaster()->ToCreature()->AI()->SelectTarget(SELECT_TARGET_NEAREST));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_bwd_pillar_of_flame_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bwd_pillar_of_flame_aoe_SpellScript();
    }
};

class spell_bwd_ride_vehicle : public SpellScriptLoader
{
    public:
        spell_bwd_ride_vehicle() : SpellScriptLoader("spell_bwd_ride_vehicle") { }

        class spell_bwd_ride_vehicle_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bwd_ride_vehicle_SpellScript);

            void RedirectTarget(WorldObject*& target)
            {
                if (Unit* magmaw = target->ToUnit()) // If we have a free pincer, we gonna place the player in it...
                {
                    if (magmaw->GetEntry() == BOSS_MAGMAW)
                    {
                        if (Unit* pincer1 = magmaw->GetVehicleKit()->GetPassenger(0))
                            if (Unit* pincer2 = magmaw->GetVehicleKit()->GetPassenger(1))
                                if (!pincer1->GetVehicleKit()->GetPassenger(0))
                                    target = pincer1;
                                else if (!pincer2->GetVehicleKit()->GetPassenger(0))
                                    target = pincer2;
                                else
                                    target = NULL;
                    }
                    else if (GetCaster()->GetTypeId() != TYPEID_PLAYER) // ... else if the caster is a body part, place it on magmaw
                    {
                        target = NULL;
                        GetCaster()->CastSpell(magmaw, SPELL_RIDE_VEHICLE_HARDCODED, true);
                    }
                }
            }

            void Register()
            {
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_bwd_ride_vehicle_SpellScript::RedirectTarget, EFFECT_0, TARGET_UNIT_TARGET_ANY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bwd_ride_vehicle_SpellScript();
        }
};

void AddSC_boss_magmaw()
{
    new boss_magmaw();
    new npc_exposed_head_of_magmaw();
    new npc_exposed_head_of_magmaw_tank();
    new npc_bwd_magmaws_pincer();
    new npc_bwd_pillar_of_flame();
    new npc_bwd_lava_parasite();
    new npc_bwd_spike_dummy();

    new spell_bwd_pillar_of_flame_aoe();
    new spell_bwd_ride_vehicle();
}
