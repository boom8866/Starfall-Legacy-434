
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
    SAY_DEATH               = 7,
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
    EVENT_FIST_OF_ELEMENTAL     = 1,
    EVENT_BLINK                 = 2,
    EVENT_TELEPORT              = 3,
    EVENT_TALK_READY_1          = 4,
    EVENT_TALK_READY_2          = 5,
    EVENT_ARCANE_POWER          = 6,
    EVENT_BLOSSOM_TARGETING     = 7,
    EVENT_SUMMON_FIREWALL       = 8,
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
        }

        bool _arcaneOverload;

        void Reset()
        {
            _Reset();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _arcaneOverload = false;
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_BLINK, 18000);
            _EnterCombat();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->GetAI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM));
            if (summon->GetEntry() == NPC_FIRE_WALL_CENTER)
            {
                summon->SetDisableGravity(true);
                summon->SetHover(true);
            }

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
            DoCastAOE(SPELL_ARCANE_POWER);
        }

        void KilledUnit(Unit* unit)
        {
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->CastSpell(me, SPELL_ARCANE_OVERLOAD);
            Talk(SAY_DEATH);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_BLOSSOM_TARGETING)
            {
                switch (urand(0,1))
                {
                    case 0:
                    {
                        DoCast(target, SPELL_FIRE_BLOSSOM);
                        target->CastSpell(target, SPELL_FIRE_BLOSSOM_VISUAL);
                        break;
                    }
                    case 1:
                    {
                        DoCast(target, SPELL_FROST_BLOSSOM);
                        target->CastSpell(target, SPELL_FROST_BLOSSOM_VISUAL);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(50) && !_arcaneOverload)
            {
                _arcaneOverload = true;
                events.Reset();
                events.ScheduleEvent(EVENT_TELEPORT, 1);
            }
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
                        events.ScheduleEvent(EVENT_FIST_OF_ELEMENTAL, 1000);
                        break;
                    case EVENT_FIST_OF_ELEMENTAL:
                        switch (urand(0, 1))
                        {
                            case 0:
                            {
                                DoCast(me, SPELL_FIST_OF_FLAME);
                                Talk(SAY_FIRE_FISTS);
                                break;
                            }
                            case 1:
                            {
                                DoCast(me, SPELL_FIST_OF_FROST);
                                Talk(SAY_FROST_FISTS);
                                break;
                            }
                            default:
                                break;
                        }
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->Attack(me->getVictim(), false);
                        events.RescheduleEvent(EVENT_BLINK, 13500);
                        break;
                    case EVENT_TELEPORT:
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        DoCastAOE(SPELL_TELEPORT);
                        me->NearTeleportTo(Center);
                        events.ScheduleEvent(EVENT_TALK_READY_1, 3800);
                        break;
                    case EVENT_TALK_READY_1:
                        if (Creature* dummy = me->FindNearestCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF, 5.0f))
                            me->SetFacingToObject(dummy);

                        Talk(SAY_PREPARE_OVERLOAD_1);
                        events.ScheduleEvent(EVENT_TALK_READY_2, 2400);
                        break;
                    case EVENT_TALK_READY_2:
                        Talk(SAY_PREPARE_OVERLOAD_2);
                        events.ScheduleEvent(EVENT_ARCANE_POWER, 2400);
                        break;
                    case EVENT_ARCANE_POWER:
                        Talk(SAY_ARCANE_POWER);
                        ArcanePower();
                        if (IsHeroic())
                            events.ScheduleEvent(EVENT_SUMMON_FIREWALL, 4000);

                        events.ScheduleEvent(EVENT_BLOSSOM_TARGETING, 3000);
                        break;
                    case EVENT_BLOSSOM_TARGETING:
                        DoCastAOE(SPELL_BLOSSOM_TARGETING);
                        events.ScheduleEvent(EVENT_BLOSSOM_TARGETING, 2500);
                        break;
                    case EVENT_SUMMON_FIREWALL:
                        Talk(SAY_ANNOUNCE_WALL);
                        if (Creature* wall = me->SummonCreature(NPC_FIRE_WALL_CENTER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                            wall->CastSpell(wall, SPELL_FIRE_WALL);
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

        uint32 TurnTimer;

        void Reset()
        {
            TurnTimer = 100;
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            SetCombatMovement(false);
            /*
            if (Creature* wall1 = me->SummonCreature(NPC_FIRE_WALL_LEFT_1, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+ 5.0f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wall2 = me->SummonCreature(NPC_FIRE_WALL_LEFT_2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+ 5.0f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wall3 = me->SummonCreature(NPC_FIRE_WALL_LEFT_3, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+ 5.0f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wall4 = me->SummonCreature(NPC_FIRE_WALL_RIGHT_1, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+ 5.0f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wall5 = me->SummonCreature(NPC_FIRE_WALL_RIGHT_2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+ 5.0f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            if (Creature* wall6 = me->SummonCreature(NPC_FIRE_WALL_RIGHT_3, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+ 5.0f, 0, TEMPSUMMON_MANUAL_DESPAWN))
            {
                wall1->CastSpell(me, SPELL_RIDE_VEHICLE);
                wall1->AddAura(SPELL_FIRE_WALL, me);
                wall2->CastSpell(me, SPELL_RIDE_VEHICLE);
                wall2->AddAura(SPELL_FIRE_WALL, me);
                wall3->CastSpell(me, SPELL_RIDE_VEHICLE);
                wall3->AddAura(SPELL_FIRE_WALL, me);
                wall4->CastSpell(me, SPELL_RIDE_VEHICLE);
                wall4->AddAura(SPELL_FIRE_WALL, me);
                wall5->CastSpell(me, SPELL_RIDE_VEHICLE);
                wall5->AddAura(SPELL_FIRE_WALL, me);
                wall6->CastSpell(me, SPELL_RIDE_VEHICLE);
                wall6->AddAura(SPELL_FIRE_WALL, me);
            }
            */
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (TurnTimer <= diff)
            {
                me->SetFacingTo(me->GetOrientation()+0.05233f);
                TurnTimer = 100;
            }
            else TurnTimer -= diff;
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
