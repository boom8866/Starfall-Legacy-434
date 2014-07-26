
#include "throne_of_the_four_winds.h"
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

enum Spells
{
    // Al'Akir
    SPELL_WIND_BURST                = 87770,
    SPELL_SUMMON_ICE_STORM          = 88239,
    SPELL_SUMMON_SQUALL_LINE_1      = 88781, // sw -> 5 passengers
    SPELL_SQUALL_LINE_SCRIPT        = 91129, // hit himself
    SPELL_SQUALL_LINE_TRIGGERED     = 87652, // target sw passengers

    // Ice Storm Summoner
    SPELL_ICE_STORM_AURA            = 87053, // default aura as it seems (periodically summons ground npc's)

    SPELL_ICE_STORM_DUMMY           = 87408, // casted on ice storm trigger (maybe for selection) -> directly after summon spell (trigger casts in summoner sometimes too)
    SPELL_ICE_STORM_CHARGE          = 87103, // charge to the location of the target
    SPELL_ICE_STORM_AREA            = 87406, // targets all ice storm dummys (maybe to find the nearest)
    SPELL_ICE_STORM_GROUND_SUMMON   = 87055,

    // Ice Storm Ground
    SPELL_ICE_STORM_VISUAL          = 87472,
    SPELL_ICE_STORM_GROUND          = 87469, // casted 3 seconds after visual cast

    // Squall Line Vehicle
    SPELL_SQUALL_LINE_VEHICLE_CAST_1 = 88779, // target alakir

    // Squall Lines
    SPELL_RIDE_VEHICLE              = 46598,
    SPELL_SQUALL_LINE               = 87652,
    
};

enum Texts
{
    // Conclave Encounter
    SAY_CONCLAVE_DEFEATED       = 0,
    SAY_CONCLAVE_BERSERK        = 1,
    SAY_CONCLAVE_ULTIMATE       = 2,
    SAY_CONCLAVE_MEMBER_DEAD    = 3,

    // Al'Akir Encounter
    SAY_AGGRO                   = 4,
    SAY_ANNOUNCE_WIND_BURST     = 5,
    SAY_WIND_BURST              = 6,
    SAY_PHASE_2                 = 7,
    SAY_SQUALL_LINE             = 8,
    SAY_PHASE_3                 = 9,
    SAY_SLAY                    = 10,
    SAY_DEATH                   = 11,
};

enum Events
{
    // Al'Akir
    EVENT_WIND_BURST = 1,
    EVENT_SUMMON_ICE_STORM,

    // Ice Storm Summoner
    EVENT_FACE_TO_ALAKIR,
    EVENT_FACE_TO_WEST,
    EVENT_CHARGE_DUMMY,

    // Ice Storm Ground
    EVENT_CAST_ICE_GROUND,
    EVENT_SUMMON_SQUALL_LINE_1,
};

enum Phases
{
    PHASE_1 = 1,
    PHASE_2,
    PHASE_3,
};

enum Actions
{
    ACTION_CONCLAVE_DEFEATED = 1,
};

Position const SlipstreamPos[] =
{
    {-51.0972f, 576.807f, 209.7063f, 1.553343f},
    {-287.604f, 816.51f, 209.7063f, 0.0f},
};

class boss_alakir : public CreatureScript
{
public:
    boss_alakir() : CreatureScript("boss_alakir") { }

    struct boss_alakirAI : public BossAI
    {
        boss_alakirAI(Creature* creature) : BossAI(creature, DATA_ALAKIR)
        {
        }

        void Reset()
        {
            _Reset();
            SetCombatMovement(false);
            me->SetReactState(REACT_PASSIVE);
            if (instance->GetBossState(DATA_CONCLAVE_OF_WIND) == DONE)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC); // seen in sniffs
                for (uint8 i = 0; i < 2; i++)
                    me->SummonCreature(NPC_SLIPSTREAM, SlipstreamPos[i], TEMPSUMMON_MANUAL_DESPAWN);
                //if (GameObject* blockade = me->FindNearestGameObject(GOB_RAIDPLATFORM, 500.0f))
                //    blockade->dyn
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            me->SetReactState(REACT_AGGRESSIVE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_WIND_BURST, urand(25000, 30000));
            events.ScheduleEvent(EVENT_SUMMON_ICE_STORM, 5000);
            events.ScheduleEvent(EVENT_SUMMON_SQUALL_LINE_1, 9000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CONCLAVE_DEFEATED:
                    TalkToMap(SAY_CONCLAVE_DEFEATED);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC); // seen in sniffs
                    for (uint8 i = 0; i < 2; i++)
                        me->SummonCreature(NPC_SLIPSTREAM, SlipstreamPos[i], TEMPSUMMON_MANUAL_DESPAWN);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
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
                    case EVENT_WIND_BURST:
                        Talk(SAY_ANNOUNCE_WIND_BURST);
                        Talk(SAY_WIND_BURST);
                        DoCast(SPELL_WIND_BURST);
                        events.ScheduleEvent(EVENT_WIND_BURST, urand(25000, 30000));
                        break;
                    case EVENT_SUMMON_ICE_STORM:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_SUMMON_ICE_STORM);
                        break;
                    case EVENT_SUMMON_SQUALL_LINE_1:
                        Talk(SAY_SQUALL_LINE);
                        DoCast(SPELL_SUMMON_SQUALL_LINE_1);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_alakirAI(creature);
    }
};

class npc_totfw_ice_storm_summoner : public CreatureScript
{
    public:
        npc_totfw_ice_storm_summoner() :  CreatureScript("npc_totfw_ice_storm_summoner") { }

        struct npc_totfw_ice_storm_summonerAI : public ScriptedAI
        {
            npc_totfw_ice_storm_summonerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCast(SPELL_ICE_STORM_AURA);
                events.ScheduleEvent(EVENT_FACE_TO_ALAKIR, 1);
            }

            void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
            {
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FACE_TO_ALAKIR:
                            me->GetMotionMaster()->Clear();
                            if (Creature* alakir = me->FindNearestCreature(BOSS_ALAKIR, 200.0f, true))
                                me->SetFacingToObject(alakir);
                            events.ScheduleEvent(EVENT_FACE_TO_WEST, 50);
                            break;
                        case EVENT_FACE_TO_WEST:
                        {
                            float base = me->GetOrientation();
                            float ori = base + (M_PI / 2);
                            me->SetFacingTo(ori);
                            events.ScheduleEvent(EVENT_CHARGE_DUMMY, 50);
                            break;
                        }
                        case EVENT_CHARGE_DUMMY:
                        {
                            std::list<Creature*> units;
                            GetCreatureListWithEntryInGrid(units, me, NPC_ICE_STORM_TRIGGER, 45.0f);

                            if (units.empty())
                                break;

                            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                            {
                                if (me->isInFront((*itr)) && (*itr)->GetDistance2d(me->GetPositionX(), me->GetPositionY()) > 3.0f)
                                    me->GetMotionMaster()->MovePoint(0, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), false);
                            }

                            events.ScheduleEvent(EVENT_FACE_TO_ALAKIR, 2500);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_totfw_ice_storm_summonerAI(creature);
        }
};

class npc_totfw_ice_storm_ground : public CreatureScript
{
    public:
        npc_totfw_ice_storm_ground() :  CreatureScript("npc_totfw_ice_storm_ground") { }

        struct npc_totfw_ice_storm_groundAI : public ScriptedAI
        {
            npc_totfw_ice_storm_groundAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCast(SPELL_ICE_STORM_VISUAL);
                events.ScheduleEvent(EVENT_CAST_ICE_GROUND, 3000);
                me->DespawnOrUnsummon(24500); // sniffed
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_ICE_GROUND:
                            DoCast(SPELL_ICE_STORM_GROUND);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_totfw_ice_storm_groundAI(creature);
        }
};

class npc_totfw_squall_line_vehicle : public CreatureScript
{
    public:
        npc_totfw_squall_line_vehicle() :  CreatureScript("npc_totfw_squall_line_vehicle") { }

        struct npc_totfw_squall_line_vehicleAI : public ScriptedAI
        {
            npc_totfw_squall_line_vehicleAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                switch (me->GetEntry())
                {
                    case NPC_SQUALL_LINE_VEHICLE_SW:
                        if (Creature* passenger1 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger2 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger3 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger4 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger5 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger6 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger7 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger8 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        {
                            passenger1->EnterVehicle(me, 0);
                            passenger2->EnterVehicle(me, 1);
                            passenger3->EnterVehicle(me, 2);
                            passenger4->EnterVehicle(me, 3);
                            passenger5->EnterVehicle(me, 4);
                            passenger6->EnterVehicle(me, 5);
                            passenger7->EnterVehicle(me, 6);
                            passenger8->EnterVehicle(me, 7);
                            if (Creature* alakir = me->FindNearestCreature(BOSS_ALAKIR, 10.0f, true))
                                alakir->AI()->DoCast(SPELL_SQUALL_LINE);
                        }
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
                        case EVENT_CAST_ICE_GROUND:
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_totfw_squall_line_vehicleAI(creature);
        }
};

void AddSC_boss_alakir()
{
    new boss_alakir();
    new npc_totfw_ice_storm_summoner();
    new npc_totfw_ice_storm_ground();
    new npc_totfw_squall_line_vehicle();
}
