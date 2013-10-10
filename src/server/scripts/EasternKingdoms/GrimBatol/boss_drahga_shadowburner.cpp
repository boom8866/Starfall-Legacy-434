
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "grim_batol.h"
#include "Vehicle.h"

enum Spells
{
    // Drahgas Spells
    SPELL_BURNING_SHADOWBOLT	= 75245,
    SPELL_BURNING_SHADOWBOLT_H	= 90915,

    SPELL_INVOCATION_OF_FLAME	= 75218,

    SPELL_TWILIGHT_PROTECTION	= 76303,

    // Valionas Spells
    SPELL_VALIONAS_FLAME		= 75321,
    SPELL_SHREDDING_SWIPE		= 75271,
    SPELL_SEEPING_TWILIGHT		= 75318, // wowhead says 75317 but this spell gives the visual aura
    SPELL_SEEPING_TWILIGHT_DMG  = 75274,
    SPELL_DEVOURING_FLAMES_H	= 90950,

    SPELL_TWILIGHT_SHIFT		= 75328,

    // Invoked Flame Spirits Spells
    SPELL_FLAMING_FIXATE        = 82850,
    SPELL_SUPERNOVA				= 75238,
    SPELL_SUPERNOVA_H			= 90972,
};

enum Phase
{
    PHASE_CASTER_PHASE	= 1,
    PHASE_DRAGON_PHASE	= 2,
    PHASE_FINAL_PHASE	= 3,

    PHASE_NON			= 4,
};

enum Events
{
    EVENT_BURNING_SHADOWBOLT			= 1,
    EVENT_SUMMON_INVOKED_FLAME_SPIRIT   = 2,

    EVENT_VALIONAS_FLAME                = 3,
    EVENT_SHREDDING_SWIPE               = 4,
    EVENT_SEEPING_TWILIGHT              = 5,
    EVENT_DEVOURING_FLAMES              = 6,

    EVENT_DRAGAH_ENTER_VEHICLE          = 7,
    EVENT_VALIONA_ENTER_GROUNDPHASE     = 8,
};

enum Actions
{
    ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP	= 1,
    ACTION_VALIONA_SHOULD_FLY_AWAY			= 2,

    ACTION_DRAGAH_IS_ON_THE_GROUND			= 3,
};

enum Points
{
    POINT_VALIONA_FLY_IN_THE_AIR	= 1,
    POINT_VALIONA_LAND				= 2,
    POINT_VALIONA_FLY_AWAY			= 3,
    POINT_VALIONA_IS_AWAY			= 4,

    POINT_DRAHGA_GO_TO_THE_LAVA		= 5,
};

enum Waypoints
{
    WP_VALIONA_FLY_TO_FIGHT         = 154944980,
    WP_VALIONA_FLY_AWAY             = 154944981,
};

enum DrahgaYells
{
    SAY_AGGRO,
    SAY_WARNING,
    SAY_SPIRIT,
    SAY_VALIONA,
    SAY_SLAY,
    SAY_INTRO,
    SAY_DEATH,
};

enum ValionaYells
{
    SAY_HELP,
    SAY_FLEE,
    SAY_FLAMEBREATH,
};

Position const position[] =
{
    {-400.613f, -671.578f, 265.896f, 0.102f},	// Drahga Point from who he jump down
    {-378.357f, -665.174f, 236.235f ,0}, // Valiona Spawnposition
    {-442.17f, -702.163f, 279.537f,0}, // Valiona Land/Emote Land Position
    {-469.944733f, -736.380432f, 268.768219f, 3.424006f}, // Cheat Position
};

class boss_drahga_shadowburner : public CreatureScript
{
public:
    boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_drahga_shadowburnerAI (creature);
    }

    struct boss_drahga_shadowburnerAI : public BossAI
    {
        boss_drahga_shadowburnerAI(Creature* creature) : BossAI(creature, DATA_DRAHGA_SHADOWBURNER)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint8 phase;

        Creature* valiona;
        bool introDone;

        void Reset()
        {
            DespawnMinions();
            valiona = NULL;
            introDone = false;

            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            phase = PHASE_NON;

            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            phase = PHASE_CASTER_PHASE;

            Talk(SAY_AGGRO);

            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveChase(me->getVictim());

            events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 4000);
            events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT, 10000);
        }

        void JustDied(Unit* /*victim*/)
        {
            Talk(SAY_DEATH);
            DespawnMinions();

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(SAY_SLAY);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                case POINT_DRAHGA_GO_TO_THE_LAVA:
                    if(valiona)
                    {
                        me->SetSpeed(MOVE_RUN, 1.0f);

                        me->JumpTo(valiona,2);
                        events.ScheduleEvent(EVENT_DRAGAH_ENTER_VEHICLE, 2000);
                    }

                    break;

                default:
                    break;
                }
            }
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
            case ACTION_DRAGAH_IS_ON_THE_GROUND:
                me->ExitVehicle();

                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 4000);
                events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT, 10000);

                break;

            default:
                break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if(Player* player = me->FindNearestPlayer(50.f))
            {
                if(!player->GetVehicleBase())
                {
                    if(!introDone)
                    {
                        introDone = true;
                        Talk(SAY_INTRO);
                    }
                }
            }

            if (!UpdateVictim() || me-> HasUnitState(UNIT_STATE_CASTING))
                return;

            if(phase == PHASE_CASTER_PHASE && !HealthAbovePct(30))
            {
                phase = PHASE_DRAGON_PHASE;
                me->SetSpeed(MOVE_RUN, 1.5f);
                me->SetReactState(REACT_PASSIVE);

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras(); // He should not die when he is jumping down...

                events.RescheduleEvent(EVENT_BURNING_SHADOWBOLT, 14000);
                events.RescheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT, 17000);

                DoCast(me, SPELL_TWILIGHT_PROTECTION, true);

                me->GetMotionMaster()->MovePoint(POINT_DRAHGA_GO_TO_THE_LAVA, position[0]);

                Talk(SAY_VALIONA);

                valiona = me->SummonCreature(NPC_VALIONA, position[1]);
            }

            if(phase == PHASE_DRAGON_PHASE && valiona && !valiona->HealthAbovePct(10))
            {
                me->ExitVehicle();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                phase = PHASE_FINAL_PHASE;

                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->Clear();

                if(Unit* victim = me->getVictim())
                    me->GetMotionMaster()->MoveChase(victim);

                valiona->GetAI()->DoAction(ACTION_VALIONA_SHOULD_FLY_AWAY);
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BURNING_SHADOWBOLT:
                    {
                        if(phase == PHASE_DRAGON_PHASE && valiona)
                        {
                            if(Unit* target = valiona->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                                DoCast(target, SPELL_BURNING_SHADOWBOLT);
                        }else
                        {
                            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                                DoCast(target, SPELL_BURNING_SHADOWBOLT);
                        }

                        events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT,4000);
                        break;
                    }
                case EVENT_SUMMON_INVOKED_FLAME_SPIRIT:
                    {
                        Talk(SAY_WARNING);
                        Talk(SAY_SPIRIT);

                        if(phase == PHASE_DRAGON_PHASE && valiona)
                            valiona->AI()->DoCastAOE(SPELL_INVOCATION_OF_FLAME);
                        else
                            DoCastAOE(SPELL_INVOCATION_OF_FLAME);

                        events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT,16000);
                        break;
                    }
                case EVENT_DRAGAH_ENTER_VEHICLE:
                    {
                        if(valiona)
                        {
                            me->NearTeleportTo(*valiona, false);
                            me->EnterVehicle(valiona, -1);
                            valiona->GetAI()->DoAction(ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP);
                        }

                        break;
                    }
                }
            }

            if(phase != PHASE_DRAGON_PHASE)
                DoMeleeAttackIfReady();
        }

        void DespawnMinions()
        {
            me->DespawnCreaturesInArea(NPC_INVOCATION_OF_FLAME_STALKER);
            me->DespawnCreaturesInArea(NPC_INVOKED_FLAMING_SPIRIT);
            me->DespawnCreaturesInArea(NPC_SEEPING_TWILIGHT_TRIGGER);
            me->DespawnCreaturesInArea(NPC_VALIONA);
        }
    };
};

class mob_valiona_gb : public CreatureScript
{
public:
    mob_valiona_gb() : CreatureScript("mob_valiona_gb") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_valiona_gbAI (creature);
    }

    struct mob_valiona_gbAI : public ScriptedAI
    {
        mob_valiona_gbAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();

            creature->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;
        EventMap events;

        uint8 flyPhase;

        Unit* dragah;

        void Reset()
        {
            events.Reset();
            flyPhase = 1;

            me->SetDisableGravity(true);
        }

        void JustSummoned(Creature* summon)
        {
            summon->setActive(true);

            if(me->isInCombat())
                summon->AI()->DoZoneInCombat();
        }

        void IsSummonedBy(Unit* summoner)
        {
            dragah = summoner;

            if(!dragah)
                me->DespawnOrUnsummon();

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            // me->SetSpeedAll(2.3f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me-> HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            if(flyPhase == 1 && me->GetDistance(position[2]) < 2.f)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                events.ScheduleEvent(EVENT_VALIONAS_FLAME, urand(4000,7000));
                events.ScheduleEvent(EVENT_SHREDDING_SWIPE, urand(10000,13000));

                if(me->GetMap()->IsHeroic())
                    events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(15000,17000));

                me->SetDisableGravity(false);
                me->SetReactState(REACT_AGGRESSIVE);
                // me->SetSpeedAll(1.4f);

                me->SetInCombatWithZone();

                flyPhase = 0;
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_VALIONAS_FLAME:
                    {
                        Talk(SAY_FLAMEBREATH);
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_VALIONAS_FLAME);

                        events.ScheduleEvent(EVENT_VALIONAS_FLAME, urand(15000,25000));
                        break;
                    }

                case EVENT_SHREDDING_SWIPE:
                    {
                        DoCastVictim(SPELL_SHREDDING_SWIPE);

                        events.ScheduleEvent(EVENT_SHREDDING_SWIPE, urand(21000,30000));
                        break;
                    }

                case EVENT_DEVOURING_FLAMES:
                    {
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_DEVOURING_FLAMES_H);

                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(30000,35000));
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
            case ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP:
                DoZoneInCombat();

                Talk(SAY_HELP);

                me->GetMotionMaster()->MovePath(WP_VALIONA_FLY_TO_FIGHT,false);
                me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
                break;

            case ACTION_VALIONA_SHOULD_FLY_AWAY:
                events.Reset();

                Talk(SAY_FLEE);

                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();

                me->SetDisableGravity(true);
                // me->SetSpeedAll(2.3f);

                flyPhase = 5;

                if(Vehicle* vehicle = me->GetVehicleKit())
                    vehicle->RemoveAllPassengers();

                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePath(WP_VALIONA_FLY_AWAY, false);

                me->AddAura(SPELL_TWILIGHT_SHIFT, me);
                me->DespawnOrUnsummon(17000);
                break;

            default:
                break;
            }
        }
    };
};

class mob_invoked_flame_spirit : public CreatureScript
{
public:
    mob_invoked_flame_spirit() : CreatureScript("mob_invoked_flame_spirit") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_invoked_flame_spiritAI (creature);
    }

    struct mob_invoked_flame_spiritAI : public ScriptedAI
    {
        mob_invoked_flame_spiritAI(Creature* creature) : ScriptedAI(creature), target(NULL) {}

        Player* target;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetInCombatWithZone();           

            std::list<Player*> playerList = me->GetNearestPlayersList(200.f, true);
            if(playerList.empty())
                return;

            if(target = SelectRandomContainerElement(playerList))
            {
                DoCast(SPELL_FLAMING_FIXATE);
                me->GetMotionMaster()->MoveChase(target);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if(target && target->IsWithinMeleeRange(me))
            {
                DoCast(SPELL_SUPERNOVA);
                me->DespawnOrUnsummon();
            }
        }
    };
};

void AddSC_boss_drahga_shadowburner()
{
    new boss_drahga_shadowburner();
    new mob_valiona_gb();
    new mob_invoked_flame_spirit();
}