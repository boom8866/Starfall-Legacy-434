
#include "ScriptPCH.h"
#include "deadmines.h"

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_FROST_FISTS         = 1,
    SAY_FIRE_FISTS          = 2,
    SAY_PREPARE_OVERLOAD_1  = 3,
    SAY_PREPARE_OVERLOAD_2  = 4,
    SAY_ARCANE_POWER        = 5,
    SAY_ANNOUNCE_WALL       = 6,
    SAY_SLAY                = 7,
    SAY_DEATH               = 8,
};

enum Spells
{
    // In both noral and heroic
    SPELL_ARCANE_POWER          = 88009,
    SPELL_FIST_OF_FLAME         = 87859,
    SPELL_FIST_OF_FROST         = 87861,
    SPELL_FROST_BEAM            = 88093,
    SPELL_FIRE_BEAM             = 88072,
    SPELL_BLINK                 = 87925,
    SPELL_TELEPORT              = 88002,

    SPELL_ARCANE_OVERLOAD       = 88185,
    SPELL_ARCANE_OVERLOAD_PRE   = 88183,
    SPELL_ARCANE_OVERLOAD_BOOM  = 90520,
    SPELL_BLOSSOM_TARGETING     = 88140,
    SPELL_FIRE_BLOSSOM_VISUAL   = 88164,
    SPELL_FROST_BLOSSOM_VISUAL  = 88165,
    SPELL_FIRE_BLOSSOM          = 88129,
    SPELL_FROST_BLOSSOM         = 88169,
    SPELL_RIDE_VEHICLE          = 46598,
    SPELL_FIRE_WALL             = 91398,
};

enum Events
{
    EVENT_FIST_OF_ELEMENTAL = 1,
    EVENT_BLINK,
    EVENT_TELEPORT,
    EVENT_TALK_READY_1,
    EVENT_TALK_READY_2,
    EVENT_ARCANE_POWER,
    EVENT_BLOSSOM_TARGETING,
    EVENT_SUMMON_FIREWALL,
    EVENT_DIE,
    EVENT_KILL,
    EVENT_ROTATE,
};

Position const Center = {-193.206f, -442.806f, 53.5931f, 5.5999f};

class boss_glubtok : public CreatureScript
{
public:
    boss_glubtok() : CreatureScript("boss_glubtok") { }

    struct boss_glubtokAI : public BossAI
    {
        boss_glubtokAI(Creature* creature) : BossAI(creature, DATA_GLUBTOK)
        {
            _arcaneOverload = false;
            _encounterDone = false;
        }

        bool _arcaneOverload;
        bool _encounterDone;

        void Reset()
        {
            _Reset();
            _arcaneOverload = false;
            _encounterDone = false;
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_BLINK, 18000);
            _EnterCombat();
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            events.Reset();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, 0.0f);
            me->SetHover(false);
            _arcaneOverload = false;
            RemoveFirewall();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void ArcanePower()
        {
            if (Creature* FireBeam1 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF2, -177.92f, -433.07f, 63.64f, 0, TEMPSUMMON_TIMED_DESPAWN, 8000))
            if (Creature* FireBeam2 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF2, -181.13f, -443.25f, 65.26f, 0, TEMPSUMMON_TIMED_DESPAWN, 8000))
            if (Creature* FireBeam3 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF2, -187.84f, -455.23f, 65.28f, 0, TEMPSUMMON_TIMED_DESPAWN, 8000))
            if (Creature* FrostBeam1 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF2, -200.34f, -455.23f, 65.28f, 0, TEMPSUMMON_TIMED_DESPAWN, 8000))
            if (Creature* FrostBeam2 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF2, -203.55f, -450.39f, 65.20f, 0, TEMPSUMMON_TIMED_DESPAWN, 8000))
            if (Creature* FrostBeam3 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF2, -205.57f, -442.11f, 59.50, 0, TEMPSUMMON_TIMED_DESPAWN, 8000))
            {
                FireBeam1->CastSpell(me, SPELL_FIRE_BEAM, true);
                FireBeam2->CastSpell(me, SPELL_FIRE_BEAM, true);
                FireBeam3->CastSpell(me, SPELL_FIRE_BEAM, true);
                FrostBeam1->CastSpell(me, SPELL_FROST_BEAM, true);
                FrostBeam2->CastSpell(me, SPELL_FROST_BEAM, true);
                FrostBeam3->CastSpell(me, SPELL_FROST_BEAM, true);
            }
            if (!_encounterDone)
                DoCastAOE(SPELL_ARCANE_POWER);
        }

        void CreateFirewall()
        {
            if (Creature* wallCenter = me->SummonCreature(NPC_FIRE_WALL_CENTER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 2.2f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            // A1 Platter
            if (Creature* wallA11 = me->SummonCreature(NPC_FIRE_WALL_1A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA12 = me->SummonCreature(NPC_FIRE_WALL_1A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB11 = me->SummonCreature(NPC_FIRE_WALL_1B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB12 = me->SummonCreature(NPC_FIRE_WALL_1B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC11 = me->SummonCreature(NPC_FIRE_WALL_1C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC12 = me->SummonCreature(NPC_FIRE_WALL_1C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA21 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA22 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA23 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA24 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA25 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA26 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA27 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallA28 = me->SummonCreature(NPC_FIRE_WALL_2A, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB21 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB22 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB23 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB24 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB25 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB26 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB27 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallB28 = me->SummonCreature(NPC_FIRE_WALL_2B, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC21 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC22 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC23 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC24 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC25 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC26 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC27 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wallC28 = me->SummonCreature(NPC_FIRE_WALL_2C, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            {
                wallA11->EnterVehicle(wallCenter, 0);
                wallA12->EnterVehicle(wallCenter, 4);

                wallB11->EnterVehicle(wallCenter, 1);
                wallB12->EnterVehicle(wallCenter, 5);  

                wallC11->EnterVehicle(wallCenter, 2);
                wallC12->EnterVehicle(wallCenter, 3);

                wallA21->EnterVehicle(wallA11, 0);
                wallA22->EnterVehicle(wallA11, 1);
                wallA23->EnterVehicle(wallA11, 4);
                wallA24->EnterVehicle(wallA11, 5);

                wallA25->EnterVehicle(wallA12, 0);
                wallA26->EnterVehicle(wallA12, 1);
                wallA27->EnterVehicle(wallA12, 4);
                wallA28->EnterVehicle(wallA12, 5);

                wallB21->EnterVehicle(wallB11, 0);
                wallB22->EnterVehicle(wallB11, 1);
                wallB23->EnterVehicle(wallB11, 4);
                wallB24->EnterVehicle(wallB11, 5);

                wallB25->EnterVehicle(wallB12, 0);
                wallB26->EnterVehicle(wallB12, 1);
                wallB27->EnterVehicle(wallB12, 4);
                wallB28->EnterVehicle(wallB12, 5);

                wallC21->EnterVehicle(wallC11, 0);
                wallC22->EnterVehicle(wallC11, 1);
                wallC23->EnterVehicle(wallC11, 4);
                wallC24->EnterVehicle(wallC11, 5);

                wallC25->EnterVehicle(wallC12, 0);
                wallC26->EnterVehicle(wallC12, 1);
                wallC27->EnterVehicle(wallC12, 4);
                wallC28->EnterVehicle(wallC12, 5);

            }
        }

        void RemoveFirewall()
        {
            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_CENTER, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_1A, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_1B, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_1C, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_2A, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_2B, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_2C, 500.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon(1);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_IMMUNE_TO_NPC);
            RemoveFirewall(); // Just in case
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(50) && !_arcaneOverload)
            {
                _arcaneOverload = true;
                events.Reset();
                events.ScheduleEvent(EVENT_TELEPORT, 1);
            }
            if (damage >= me->GetHealth() && !_encounterDone)
            {
                _encounterDone = true;
                damage = 0;
                me->SetHealth(1);
                RemoveFirewall();
                Talk(SAY_DEATH);
                ArcanePower();
                DoCastAOE(SPELL_ARCANE_OVERLOAD_PRE);
                events.CancelEvent(EVENT_BLOSSOM_TARGETING);
                events.ScheduleEvent(EVENT_DIE, 6200);
            }

            if (damage >= me->GetHealth())
                damage = 0;

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
                case EVENT_BLINK:
                    DoCastAOE(SPELL_BLINK);
                    me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_IMMUNE_TO_NPC);
                    events.ScheduleEvent(EVENT_FIST_OF_ELEMENTAL, 1000);
                    break;
                case EVENT_FIST_OF_ELEMENTAL:
                    switch (urand(0, 1))
                    {
                    case 0:
                        DoCast(me, SPELL_FIST_OF_FLAME);
                        Talk(SAY_FIRE_FISTS);
                        break;
                    case 1:
                        DoCast(me, SPELL_FIST_OF_FROST);
                        Talk(SAY_FROST_FISTS);
                        break;
                    default:
                        break;
                    }
                    me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_IMMUNE_TO_NPC);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->Attack(me->getVictim(), false);
                    events.RescheduleEvent(EVENT_BLINK, 13500);

                    break;
                case EVENT_TELEPORT:
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_IMMUNE_TO_NPC);
                    DoCastAOE(SPELL_TELEPORT);
                    me->NearTeleportTo(Center);
                    events.ScheduleEvent(EVENT_TALK_READY_1, 3800);
                    break;
                case EVENT_TALK_READY_1:
                    me->SetFacingTo(1.65f);
                    Talk(SAY_PREPARE_OVERLOAD_1);
                    events.ScheduleEvent(EVENT_TALK_READY_2, 2400);
                    if (IsHeroic())
                        CreateFirewall();
                    break;
                case EVENT_TALK_READY_2:
                    Talk(SAY_PREPARE_OVERLOAD_2);
                    events.ScheduleEvent(EVENT_ARCANE_POWER, 2400);
                    break;
                case EVENT_ARCANE_POWER:
                    Talk(SAY_ARCANE_POWER);
                    me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, 1.0f);
                    me->SetHover(true);
                    ArcanePower();
                    if (IsHeroic())
                        events.ScheduleEvent(EVENT_SUMMON_FIREWALL, 4000);

                    events.ScheduleEvent(EVENT_BLOSSOM_TARGETING, 3000);
                    break;
                case EVENT_BLOSSOM_TARGETING:
                    switch (urand(0, 1))
                    {
                        case 0:
                        {
                            std::list<Creature*> FireList;
                            GetCreatureListWithEntryInGrid(FireList, me, NPC_FIRE_BLOSSOM_DUMMY, 200.f);
                            if (!FireList.empty())
                            {
                                Unit* Fire = Trinity::Containers::SelectRandomContainerElement(FireList);
                                DoCast(Fire, SPELL_FIRE_BLOSSOM);
                                Fire->CastSpell(Fire, SPELL_FIRE_BLOSSOM_VISUAL);
                            }
                            break;
                        }
                        case 1:
                        {
                            std::list<Creature*> FrostList;
                            GetCreatureListWithEntryInGrid(FrostList, me, NPC_FROST_BLOSSOM_DUMMY, 200.f);
                            if (!FrostList.empty())
                            {
                                Unit* Frost = Trinity::Containers::SelectRandomContainerElement(FrostList);
                                DoCast(Frost, SPELL_FROST_BLOSSOM);
                                Frost->CastSpell(Frost, SPELL_FROST_BLOSSOM_VISUAL);
                            }
                            break;
                        }
                    }
                    events.ScheduleEvent(EVENT_BLOSSOM_TARGETING, 2500);
                    break;
                case EVENT_SUMMON_FIREWALL:
                    {
                        Talk(SAY_ANNOUNCE_WALL);
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_1A, 500.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_1B, 500.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_1C, 500.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_2A, 500.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_2B, 500.0f);
                        GetCreatureListWithEntryInGrid(units, me, NPC_FIRE_WALL_2C, 500.0f);
                        for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                            (*itr)->AI()->DoCastAOE(SPELL_FIRE_WALL);
                        break;
                    }
                case EVENT_DIE:
                    me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, 0.0f);
                    me->SetHover(false);
                    DoCastAOE(SPELL_ARCANE_OVERLOAD_BOOM);
                    events.ScheduleEvent(EVENT_KILL, 100);
                    break;
                case EVENT_KILL:
                    DoCastAOE(SPELL_ARCANE_OVERLOAD);
                    me->Kill(me, false);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_glubtokAI (pCreature);
    }

};

class npc_dm_firewall_rotator : public CreatureScript
{
public:
    npc_dm_firewall_rotator() : CreatureScript("npc_dm_firewall_rotator")
    {
    }

    struct npc_dm_firewall_rotatorAI : public ScriptedAI
    {
        npc_dm_firewall_rotatorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetOrientation(1.65f);
            me->SetFacingTo(1.65f);
            me->AddUnitState(UNIT_STATE_CANNOT_TURN);
            events.ScheduleEvent(EVENT_ROTATE, 13000);
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ROTATE:
                    float angle = 0.0f;
                    angle = me->GetOrientation() - 0.05f;
                    me->SetOrientation(angle);
                    me->SetFacingTo(angle);
                    me->AddUnitState(UNIT_STATE_CANNOT_TURN);
                    events.ScheduleEvent(EVENT_ROTATE, 300);
                    break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dm_firewall_rotatorAI (creature);
    }
};

void AddSC_boss_glubtok()
{
    new boss_glubtok();
    new npc_dm_firewall_rotator();
}
