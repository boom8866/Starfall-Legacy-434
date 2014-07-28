
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
    SPELL_WIND_BURST                = 87770, // 90663 --< too close knockback ??? wtf
    SPELL_SUMMON_ICE_STORM          = 88239,
    SPELL_SUMMON_SQUALL_LINE_1      = 88781, // sw
    SPELL_SUMMON_SQUALL_LINE_2      = 91104, // se
    SPELL_SQUALL_LINE_SCRIPT        = 91129, // hit himself
    SPELL_SQUALL_LINE_TRIGGERED     = 87652, // target sw passengers
    SPELL_ELECTROCUTE_CHANNELED     = 88427,
    SPELL_GUARDIAN_TAUNT            = 85667,
    SPELL_STATIC_SHOCK              = 87873, // Heroic

    SPELL_LIGHTNING_STRIKE_AOE      = 91327,
    SPELL_LIGHTNING_STRIKE_SCRIPT   = 91326, // target lightning strike trigger (48977)

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
    SPELL_SQUALL_LINE_DRAG          = 87855,
    SPELL_SQUALL_LINE_SCRIPT_PLAYER = 87856,

    // Lightning Strike Trigger
    SPELL_LIGHTNING_STRIKE_SUMMON   = 93250,

    // Lightning Strike Heroic Chain
    SPELL_LIGHTNING_STRIKE_HC_AURA  = 93247,
    SPELL_LIGHTNING_STRIKE_CHAIN_VISUAL = 88230,
    SPELL_LIGHTNING_STRIKE_CONE_DAMAGE  = 88214,

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
    EVENT_ELECTROCUTE,
    EVENT_LIGHTNING_STRIKE,

    // Ice Storm Summoner
    EVENT_FACE_TO_ALAKIR,
    EVENT_FACE_TO_WEST,
    EVENT_CHARGE_DUMMY,

    // Ice Storm Ground
    EVENT_CAST_ICE_GROUND,
    EVENT_SUMMON_SQUALL_LINE_1,
    EVENT_SUMMON_SQUALL_LINE_2,

    // Squall Line Vehicle
    EVENT_MOVE_IN_CIRCLE,

    // Squall Line
    EVENT_CLEAR_IMMUNITY,
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
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            me->SetReactState(REACT_AGGRESSIVE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.SetPhase(PHASE_1);
            //events.ScheduleEvent(EVENT_WIND_BURST, urand(25000, 30000));
            //events.ScheduleEvent(EVENT_SUMMON_ICE_STORM, 5000);
            events.ScheduleEvent(EVENT_SUMMON_SQUALL_LINE_1, 10000);
            //events.ScheduleEvent(EVENT_LIGHTNING_STRIKE, 9000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
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
                        if (me->getVictim()->HasAura(SPELL_ELECTROCUTE_CHANNELED))
                            me->CastStop();
                        Talk(SAY_ANNOUNCE_WIND_BURST);
                        Talk(SAY_WIND_BURST);
                        DoCast(SPELL_WIND_BURST);
                        events.ScheduleEvent(EVENT_WIND_BURST, urand(25000, 30000));
                        break;
                    case EVENT_SUMMON_ICE_STORM:
                        if (me->getVictim()->HasAura(SPELL_ELECTROCUTE_CHANNELED))
                            me->CastStop();
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_SUMMON_ICE_STORM);
                        events.ScheduleEvent(EVENT_SUMMON_ICE_STORM, 15500);
                        break;
                    case EVENT_SUMMON_SQUALL_LINE_1:
                        if (me->getVictim()->HasAura(SPELL_ELECTROCUTE_CHANNELED))
                            me->CastStop();
                        Talk(SAY_SQUALL_LINE);
                        DoCast(me, SPELL_SUMMON_SQUALL_LINE_1);
                        events.ScheduleEvent(EVENT_SUMMON_SQUALL_LINE_2, 31000);
                        break;
                    case EVENT_SUMMON_SQUALL_LINE_2:
                        if (me->getVictim()->HasAura(SPELL_ELECTROCUTE_CHANNELED))
                            me->CastStop();
                        Talk(SAY_SQUALL_LINE);
                        DoCast(me, SPELL_SUMMON_SQUALL_LINE_2);
                        events.ScheduleEvent(EVENT_SUMMON_SQUALL_LINE_1, 31000);
                        break;
                    case EVENT_LIGHTNING_STRIKE:
                        if (me->getVictim()->HasAura(SPELL_ELECTROCUTE_CHANNELED))
                            me->CastStop();
                        DoCast(SPELL_LIGHTNING_STRIKE_AOE);
                        break;
                    default:
                        break;
                }
            }

            if (me->getVictim()->IsWithinMeleeRange(me) && me->getVictim()->HasAura(SPELL_ELECTROCUTE_CHANNELED))
               me->getVictim()->RemoveAurasDueToSpell(SPELL_ELECTROCUTE_CHANNELED);
            else if (me->getVictim()->IsWithinMeleeRange(me))
                DoMeleeAttackIfReady();
            else if (!me->HasUnitState(UNIT_STATE_CASTING))
                DoCast(me->getVictim(), SPELL_ELECTROCUTE_CHANNELED, true);
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
                alakir = NULL;
            }

            Unit* alakir;

            void IsSummonedBy(Unit* summoner)
            {
                alakir = summoner;
                events.ScheduleEvent(EVENT_MOVE_IN_CIRCLE, 100);
                me->DespawnOrUnsummon(46000);
                me->AddUnitState(UNIT_STATE_ROAMING);
                switch (me->GetEntry())
                {
                    case NPC_SQUALL_LINE_VEHICLE_SW:
                    {
                        float base = me->GetAngle(summoner);
                        float ori = base - (M_PI / 2);
                        me->NearTeleportTo(summoner->GetPositionX()+cos(base + M_PI)*45, summoner->GetPositionY()+sin(base + M_PI)*45, summoner->GetPositionZ(), ori);
                        if (Creature* passenger1 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger2 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger3 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger4 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger5 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger6 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger7 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        if (Creature* passenger8 = me->SummonCreature(NPC_SQUALL_LINE_SW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                        {
                            passenger1->EnterVehicle(me, 0);
                            passenger2->EnterVehicle(me, 1);
                            passenger3->EnterVehicle(me, 2);
                            passenger4->EnterVehicle(me, 3);
                            passenger5->EnterVehicle(me, 4);
                            passenger6->EnterVehicle(me, 5);
                            passenger7->EnterVehicle(me, 6);
                            passenger8->EnterVehicle(me, 7);

                            passenger1->AddAura(SPELL_SQUALL_LINE, passenger1);
                            passenger2->AddAura(SPELL_SQUALL_LINE, passenger2);
                            passenger3->AddAura(SPELL_SQUALL_LINE, passenger3);
                            passenger4->AddAura(SPELL_SQUALL_LINE, passenger4);
                            passenger5->AddAura(SPELL_SQUALL_LINE, passenger5);
                            passenger6->AddAura(SPELL_SQUALL_LINE, passenger6);
                            passenger7->AddAura(SPELL_SQUALL_LINE, passenger7);
                            passenger8->AddAura(SPELL_SQUALL_LINE, passenger8);

                            switch (urand(0, 4))
                            {
                                case 0: // Inner Tornado wont get active 1
                                    passenger2->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger4->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 1: // Middle Tornado wont get active
                                    passenger1->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger3->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 2: // Outer Tornado wont get active 1
                                    passenger5->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger7->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 3: // Outer Tornado wont get active 2
                                    passenger7->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger8->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 4: // Inner Tornado wont get active 2
                                    passenger6->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger4->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;
                    }
                    case NPC_SQUALL_LINE_VEHICLE_SE:
                    {
                        float base = me->GetAngle(summoner);
                        float ori = base + (M_PI / 2);
                        me->NearTeleportTo(summoner->GetPositionX()+cos(base + M_PI)*45, summoner->GetPositionY()+sin(base + M_PI)*45, summoner->GetPositionZ(), ori);
                        if (Creature* passenger1 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger2 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger3 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger4 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger5 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger6 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger7 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        if (Creature* passenger8 = me->SummonCreature(NPC_SQUALL_LINE_SE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        {
                            passenger1->EnterVehicle(me, 0);
                            passenger2->EnterVehicle(me, 1);
                            passenger3->EnterVehicle(me, 2);
                            passenger4->EnterVehicle(me, 3);
                            passenger5->EnterVehicle(me, 4);
                            passenger6->EnterVehicle(me, 5);
                            passenger7->EnterVehicle(me, 6);
                            passenger8->EnterVehicle(me, 7);

                            passenger1->AddAura(SPELL_SQUALL_LINE, passenger1);
                            passenger2->AddAura(SPELL_SQUALL_LINE, passenger2);
                            passenger3->AddAura(SPELL_SQUALL_LINE, passenger3);
                            passenger4->AddAura(SPELL_SQUALL_LINE, passenger4);
                            passenger5->AddAura(SPELL_SQUALL_LINE, passenger5);
                            passenger6->AddAura(SPELL_SQUALL_LINE, passenger6);
                            passenger7->AddAura(SPELL_SQUALL_LINE, passenger7);
                            passenger8->AddAura(SPELL_SQUALL_LINE, passenger8);

                            switch (urand(0, 4))
                            {
                                case 0: // Inner Tornado wont get active 1
                                    passenger8->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger6->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 1: // Middle Tornado wont get active
                                    passenger1->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger3->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 2: // Outer Tornado wont get active 1
                                    passenger5->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger3->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 3: // Outer Tornado wont get active 2
                                    passenger7->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger5->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
                                case 4: // Inner Tornado wont get active 2
                                    passenger6->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    passenger4->RemoveAurasDueToSpell(SPELL_SQUALL_LINE);
                                    break;
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

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE_IN_CIRCLE:
                        {
                            switch (me->GetEntry())
                            {
                                case NPC_SQUALL_LINE_VEHICLE_SW:
                                {
                                    float base = me->GetAngle(alakir) - 0.1189866f;
                                    me->GetMotionMaster()->MovePoint(0, alakir->GetPositionX()+cos(base + M_PI)*50, alakir->GetPositionY()+sin(base + M_PI)*50, alakir->GetPositionZ(), false);
                                    break;
                                }
                                case NPC_SQUALL_LINE_VEHICLE_SE:
                                {
                                    float base = me->GetAngle(alakir) + 0.1189866f;
                                    me->GetMotionMaster()->MovePoint(0, alakir->GetPositionX()+cos(base + M_PI)*50, alakir->GetPositionY()+sin(base + M_PI)*50, alakir->GetPositionZ(), false);
                                    break;
                                }
                                default:
                                    break;
                            }
                            events.ScheduleEvent(EVENT_MOVE_IN_CIRCLE, 100);
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
            return new npc_totfw_squall_line_vehicleAI(creature);
        }
};

class npc_totfw_squall_line : public CreatureScript
{
    public:
        npc_totfw_squall_line() :  CreatureScript("npc_totfw_squall_line") { }

        struct npc_totfw_squall_lineAI : public ScriptedAI
        {
            npc_totfw_squall_lineAI(Creature* creature) : ScriptedAI(creature)
            {
                lastPlayer = NULL;
            }

            Unit* lastPlayer;

            void OnCharmed(bool apply)
            {
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (target->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_SQUALL_LINE_DRAG && !target->GetVehicleCreatureBase())
                {
                    lastPlayer = target;
                    target->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SQUALL_LINE_DRAG, true);
                    events.ScheduleEvent(EVENT_CLEAR_IMMUNITY, 6000);
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CLEAR_IMMUNITY:
                            if (lastPlayer != NULL)
                                lastPlayer->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SQUALL_LINE_DRAG, false);
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
            return new npc_totfw_squall_lineAI(creature);
        }
};

class npc_totfw_lightning_strike_hc_trigger : public CreatureScript
{
    public:
        npc_totfw_lightning_strike_hc_trigger() :  CreatureScript("npc_totfw_lightning_strike_hc_trigger") { }

        struct npc_totfw_lightning_strike_hc_triggerAI : public ScriptedAI
        {
            npc_totfw_lightning_strike_hc_triggerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* summoner)
            {
                std::list<Player*> playerList = me->GetNearestPlayersList(200.f, true);
                if (!playerList.empty())
                {
                    if (Unit* target = Trinity::Containers::SelectRandomContainerElement(playerList))
                        me->SetFacingToObject(target);
                    DoCast(me, SPELL_LIGHTNING_STRIKE_HC_AURA);
                }
            }

            void UpdateAI(uint32 diff)
            {
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_totfw_lightning_strike_hc_triggerAI(creature);
        }
};

class spell_totfw_squall_line_script : public SpellScriptLoader
{
public:
    spell_totfw_squall_line_script() : SpellScriptLoader("spell_totfw_squall_line_script") { }

    class spell_totfw_squall_line_script_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_totfw_squall_line_script_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* player = GetHitPlayer())
                {
                    if (!player->GetVehicleCreatureBase())
                        if (Creature* alakir = caster->FindNearestCreature(BOSS_ALAKIR, 500.0f, true))
                            player->CastSpell(caster, SPELL_SQUALL_LINE_SCRIPT_PLAYER, false);
                }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_totfw_squall_line_script_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_totfw_squall_line_script_SpellScript();
    }
};

class spell_totfw_electrocute : public SpellScriptLoader
{
    public:
        spell_totfw_electrocute() : SpellScriptLoader("spell_totfw_electrocute") { }

        class spell_totfw_electrocute_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_totfw_electrocute_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                uint64 damage;
                damage = aurEff->GetBaseAmount() * aurEff->GetTickNumber();
                this->GetEffect(EFFECT_0)->ChangeAmount(damage);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_totfw_electrocute_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_totfw_electrocute_AuraScript();
        }
};

class spell_totfw_lightning_strike_aoe : public SpellScriptLoader
{
public:
    spell_totfw_lightning_strike_aoe() : SpellScriptLoader("spell_totfw_lightning_strike_aoe") { }

    class spell_totfw_lightning_strike_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_totfw_lightning_strike_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_totfw_lightning_strike_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_totfw_lightning_strike_aoe_SpellScript();
    }
};

class spell_totfw_lightning_strike_script : public SpellScriptLoader
{
public:
    spell_totfw_lightning_strike_script() : SpellScriptLoader("spell_totfw_lightning_strike_script") { }

    class spell_totfw_lightning_strike_script_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_totfw_lightning_strike_script_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* trigger = caster->FindNearestCreature(NPC_LIGHTNING_STRIKE_TRIGGER, 200.0f, true))
                {
                    trigger->SetFacingToObject(caster);
                    trigger->CastWithDelay(100, trigger, SPELL_LIGHTNING_STRIKE_SUMMON);
                }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_totfw_lightning_strike_script_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_totfw_lightning_strike_script_SpellScript();
    }
};

class spell_totfw_lightning_strike_periodic : public SpellScriptLoader
{
public:
    spell_totfw_lightning_strike_periodic() : SpellScriptLoader("spell_totfw_lightning_strike_periodic") { }

    class spell_totfw_lightning_strike_periodic_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_totfw_lightning_strike_periodic_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                float bordervalue = (((M_PI / 2) / 2) / 2);
                float origin = caster->GetOrientation() - bordervalue;
                float increase = (bordervalue / 6);
                caster->CastSpell(caster, SPELL_LIGHTNING_STRIKE_CONE_DAMAGE, true);
                // 12 Chain casts
                for (uint8 i = 0; i < 12; i++)
                {
                    float ori = origin + (i * increase);
                    caster->CastSpell(caster->GetPositionX()+cos(ori)*60, caster->GetPositionY()+sin(ori)*60, caster->GetPositionZ(), SPELL_LIGHTNING_STRIKE_CHAIN_VISUAL, true);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_totfw_lightning_strike_periodic_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_totfw_lightning_strike_periodic_SpellScript();
    }
};

void AddSC_boss_alakir()
{
    new boss_alakir();
    new npc_totfw_ice_storm_summoner();
    new npc_totfw_ice_storm_ground();
    new npc_totfw_squall_line_vehicle();
    new npc_totfw_squall_line();
    new npc_totfw_lightning_strike_hc_trigger();

    new spell_totfw_squall_line_script();
    new spell_totfw_electrocute();
    new spell_totfw_lightning_strike_aoe();
    new spell_totfw_lightning_strike_script();
    new spell_totfw_lightning_strike_periodic();
}
