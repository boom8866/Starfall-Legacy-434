
/*
Author:     NorthStrider
Instance:   Halls of Origination
Boss:       Rajh <The Construct of the Sun>
Complete:   95%
Todo:       - Test the code with 5 players
            - Refix the DoCompleteAchievement function
            - Fix some visual stuff like the movementflag
*/

#include "halls_of_origination.h"

enum Spells
{
    // Rajh
    SPELL_SUN_STRIKE                = 73872,
    SPELL_SOLAR_WINDS_SUMMON        = 74104,
    SPELL_SOLAR_WINDS_VORTEX_SUMMON = 74106,
    SPELL_INFERNO_LEAP_DUMMY        = 87650,
    SPELL_INFERNO_LEAP              = 87653,
    SPELL_INFERNO_LEAP_EXPLOSION    = 87647,
    SPELL_SUMMON_SUN_ORB            = 80352,
    SPELL_BLESSING_OF_THE_SUN       = 76352,
    // Sun Orb
    SPELL_SUN_LEAP                  = 82856,
};

enum Texts
{
    SAY_AGGRO       = 0,
    SAY_ENERGIZE    = 1,
    SAY_SLAY        = 2,
    SAY_DEATH       = 3,
};

enum Events
{
    // Rajh
    EVENT_SUN_STRIKE            = 1,
    EVENT_INFERNO_LEAP          = 2,
    EVENT_BLESSING_OF_THE_SUN   = 3,
    EVENT_SUMMON_SUN_ORB        = 4,
    EVENT_SUMMON_SOLAR_WIND     = 5,
    EVENT_ENERGIZE              = 6,

    // Inferno Leap
    EVENT_LEAP_EXPLOSION        = 7,

    // Solar Wind
    EVENT_MOVE_ARROUND          = 8,
    EVENT_SUMMON_VORTEX         = 9,

    //Sun Orb
    EVENT_LEAP                  = 10,
};

enum Points
{
    POINT_CENTER    = 1,
    POINT_UP        = 2,
    POINT_SUN_EXP   = 3,
};

Position const CenterPos    = {-319.455f, 193.440f, 343.946f, 3.133f};

class boss_rajh : public CreatureScript
{
public:
    boss_rajh() : CreatureScript("boss_rajh") { }

    struct boss_rajhAI : public BossAI
    {
        boss_rajhAI(Creature* creature) : BossAI(creature, DATA_RAJH)
        {
            Achievement = true;
            Energized   = true;
        }

        bool Achievement;
        bool Energized;

        void Reset()
        {
            _Reset();
            Achievement = true;
            Energized   = true;
            me->SetPower(POWER_ENERGY, 100);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            me->SetPower(POWER_ENERGY, 100);
            me->SetWalk(true);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_SUN_STRIKE, 20000);       //sniffed
            events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);     //guessed
            events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 9800);    //sniffed
            events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 5800); //sniffed
        }

        void JustSummoned(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_SOLAR_FIRE:
                    summon->SetReactState(REACT_PASSIVE);
                    break;
                default:
                    break;
            }
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            RemoveGround();
            Reset();
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CENTER:
                    events.ScheduleEvent(EVENT_ENERGIZE, 1);
                    break;
                default:
                    break;
            }
        }

        void RemoveGround()
        {
            me->DespawnCreaturesInArea(NPC_INFERNO_LEAP_DUMMY, 125.0f);
            me->DespawnCreaturesInArea(NPC_SUN_ORB, 125.0f);
            me->DespawnCreaturesInArea(NPC_SOLAR_WIND_VORTEX, 125.0f);
            me->DespawnCreaturesInArea(NPC_SOLAR_WIND, 125.0f);
            me->DespawnCreaturesInArea(NPC_SOLAR_FIRE, 125.0f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->GetPower(POWER_ENERGY) == 0 && Energized)
            {
                me->SetReactState(REACT_PASSIVE);
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(POINT_CENTER, CenterPos);
                events.Reset();
                Energized = false;
            }

            if (me->GetPower(POWER_ENERGY) == 100 && !Energized)
            {
                if (Unit* target = me->FindNearestPlayer(50.0f, true))
                {
                    me->RemoveAurasDueToSpell(SPELL_BLESSING_OF_THE_SUN);
                    me->GetMotionMaster()->Clear();
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->Attack(target, false);
                }

                events.ScheduleEvent(EVENT_SUN_STRIKE, 20000);       //sniffed
                events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);     //guessed
                events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 9800);    //sniffed
                events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 5800); //sniffed
                Energized   = true;
                Achievement = false;
            }

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INFERNO_LEAP:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_INFERNO_LEAP_DUMMY);
                        DoCastAOE(SPELL_INFERNO_LEAP);
                        events.ScheduleEvent(EVENT_INFERNO_LEAP, 35000);
                        break;
                    case EVENT_SUMMON_SUN_ORB:
                        DoCast(SPELL_SUMMON_SUN_ORB);
                        events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 35000);
                        break;
                    case EVENT_SUMMON_SOLAR_WIND:
                        DoCastVictim(SPELL_SOLAR_WINDS_SUMMON);
                        events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 35000);
                        break;
                    case EVENT_SUN_STRIKE:
                        DoCastVictim(SPELL_SUN_STRIKE);
                        events.ScheduleEvent(EVENT_SUN_STRIKE, 35000);
                        break;
                    case EVENT_ENERGIZE:
                        if (!Energized)
                        {
                            Talk(SAY_ENERGIZE);
                            DoCastAOE(SPELL_BLESSING_OF_THE_SUN);
                            me->HandleEmoteCommand(UNIT_STATE_CASTING);
                        }
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (instance)
            {
                Talk(SAY_DEATH);
                instance->SetBossState(DATA_RAJH, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->DoCompleteAchievement(4841);
                RemoveGround();

                if (IsHeroic())
                {
                    instance->DoCompleteAchievement(5065);
                    if (Achievement)
                        instance->DoCompleteAchievement(5295);
                }       
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_rajhAI(creature);
    }
};

class npc_inferno_ground : public CreatureScript
{
public:
    npc_inferno_ground() : CreatureScript("npc_inferno_leap_dummy") { }

    struct npc_inferno_groundAI : public ScriptedAI
    {
        npc_inferno_groundAI(Creature* creature) : ScriptedAI(creature) 
        {
            me->SetReactState(REACT_PASSIVE);
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            me->setFaction(16);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            events.ScheduleEvent(EVENT_LEAP_EXPLOSION, 2500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LEAP_EXPLOSION:
                        DoCastAOE(SPELL_INFERNO_LEAP_EXPLOSION);
                        me->DespawnOrUnsummon(5000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_inferno_groundAI(creature);
    }
};

class npc_solar_wind : public CreatureScript
{
public:
    npc_solar_wind() : CreatureScript("npc_solar_wind") { }

    struct npc_solar_windAI : public ScriptedAI
    {
        npc_solar_windAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            me->SetReactState(REACT_PASSIVE);
            if (me->GetEntry() == NPC_SOLAR_WIND_VORTEX)
            {
                me->setFaction(16);
                me->SetWalk(true);
                events.ScheduleEvent(EVENT_MOVE_ARROUND, 1);
            }
            else if (me->GetEntry() == NPC_SOLAR_WIND)
                events.ScheduleEvent(EVENT_SUMMON_VORTEX, 1000);
            else
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_ARROUND:
                        me->GetMotionMaster()->MoveRandom(50.0f);
                        events.ScheduleEvent(EVENT_MOVE_ARROUND, 10000);
                        break;
                    case EVENT_SUMMON_VORTEX:
                        DoCastAOE(SPELL_SOLAR_WINDS_VORTEX_SUMMON);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_solar_windAI(creature);
    }
};

class npc_sun_orb : public CreatureScript
{
public:
    npc_sun_orb() : CreatureScript("npc_sun_orb") {}

    struct npc_sun_orbAI : public ScriptedAI
    {
        npc_sun_orbAI(Creature* creature) : ScriptedAI(creature) 
        {
            me->SetReactState(REACT_PASSIVE);
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetHover(true);
            me->SetDisableGravity(true);
            me->SetCanFly(true);
            me->GetMotionMaster()->MovePoint(POINT_UP, me->GetPositionX(), me->GetPositionY(), 370.448f, false);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_UP:
                    events.ScheduleEvent(EVENT_LEAP, 5000);
                    break;
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
                    case EVENT_LEAP:
                        if (Unit* target = me->FindNearestPlayer(100.0f, true))
                            DoCast(target, SPELL_SUN_LEAP);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sun_orbAI(creature);
    }
};

void AddSC_boss_rajh()
{
    new boss_rajh();
    new npc_inferno_ground();
    new npc_sun_orb();
    new npc_solar_wind();
}
