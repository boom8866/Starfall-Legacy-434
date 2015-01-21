
#include "Vehicle.h"
#include "firelands.h"

enum Spells
{
    SPELL_BALANCE_BAR               = 98226,
    SPELL_RIDE_VEHICLE              = 98843,

    SPELL_OBSIDIAN_ARMOR            = 98632,
    SPELL_CONCUSSIVE_STOMP          = 97282,
    SPELL_CONCUSSIVE_STOMP_TRIGGER  = 102306,
    SPELL_HEATED_VOLCANO            = 98493,

    SPELL_VOLCANIC_BIRTH            = 98010,
    SPELL_VOLCANO_BASE              = 98250,
    SPELL_MOLTEN_ARMOR              = 98255,
    SPELL_EXPLOSION                 = 97719,
    SPELL_MAGMA                     = 98472,
    SPELL_ERRUPTION                 = 98264,
    SPELL_LAVA_STRIKE_TRIGGERED     = 98491,
};

enum Texts
{
    SAY_AGGRO                   = 0,
    SAY_STOMP                   = 1,

    SAY_UNK                     = 3,
    SAY_ANNOUNCE_ARMOR_DAMAGE   = 4,
    SAY_ARMOR_DAMAGE            = 5,
    SAY_MINIONS                 = 6,
    SAY_SLAY                    = 7,
    SAY_ANNOUNCE_MAGMA_POND     = 8,
    SAY_ANNOUNCE_ARMOR_BROKEN   = 9,
    SAY_FINAL_PHASE             = 10,
    SAY_DEATH                   = 11,
};

enum Events
{
    EVENT_BALANCE_MOVEMENT = 1,
    EVENT_CONCUSSIVE_STOMP,
    EVENT_EXPLOSION,
};

enum Actions
{
    ACTION_BALANCE_LEFT = 1,
    ACTION_BALANCE_RIGHT,
    ACTION_ACTIVATE_VOLCANO,
};

enum Phases
{
    PHASE_1     = 1,
    PHASE_2     = 2,
    PHASE_3     = 3,
};

enum ModelIds
{
    MODEL_DEFAULT       = 38414,
    MODEL_DAMAGED_1     = 38669,
    MODEL_DAMAGED_2     = 38676,
    MODEL_MOLTEN        = 38594,
};

class boss_lord_rhyolith : public CreatureScript
{
public:
    boss_lord_rhyolith() : CreatureScript("boss_lord_rhyolith") { }

    struct boss_lord_rhyolithAI : public BossAI
    {
        boss_lord_rhyolithAI(Creature* creature) : BossAI(creature, DATA_LORD_RHYOLITH)
        {
            balance = 0;
        }

        int32 balance;

        void Reset()
        {
            _Reset();
            SetupFeet();
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_NOT_TARGETABLE | UNIT_FLAG2_UNK3 | UNIT_FLAG2_REGENERATE_POWER);
            // me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE | UNIT_FLAG_PET_IN_COMBAT | UNIT_FLAG_PLAYER_CONTROLLED);
            me->AddAura(SPELL_OBSIDIAN_ARMOR, me);
            me->SetAuraStack(SPELL_OBSIDIAN_ARMOR, me, 80);
            balance = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            DoCastAOE(SPELL_BALANCE_BAR);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            if (Unit* footLeft = me->GetVehicleKit()->GetPassenger(0))
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, footLeft);
            if (Unit* footRight = me->GetVehicleKit()->GetPassenger(1))
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, footRight);

            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
            me->AddUnitState(UNIT_STATE_CANNOT_TURN);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BALANCE_BAR);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (Unit* footLeft = me->GetVehicleKit()->GetPassenger(0))
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, footLeft);
            if (Unit* footRight = me->GetVehicleKit()->GetPassenger(1))
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, footRight);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BALANCE_BAR);
            balance = 0;
            summons.DespawnAll();
            _EnterEvadeMode();
            _DespawnAtEvade();
        }

        void SetupFeet()
        {
            if (Creature* footLeft = me->SummonCreature(NPC_LEFT_FOOT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            {
                //footLeft->EnterVehicle(me, 0);
                footLeft->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                footLeft->AddAura(SPELL_OBSIDIAN_ARMOR, footLeft);
                footLeft->SetAuraStack(SPELL_OBSIDIAN_ARMOR, footLeft, 80);
            }

            if (Creature* footRight = me->SummonCreature(NPC_RIGHT_FOOT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            {
                //footRight->EnterVehicle(me, 1);
                footRight->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                footRight->AddAura(SPELL_OBSIDIAN_ARMOR, footRight);
                footRight->SetAuraStack(SPELL_OBSIDIAN_ARMOR, footRight, 80);
            }
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_LEFT_FOOT:
                case NPC_RIGHT_FOOT:
                    summons.Summon(summon);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_BALANCE_LEFT:
                    if (balance < 25)
                        balance++;
                    break;
                case ACTION_BALANCE_RIGHT:
                    if (balance > -25)
                        balance--;
                    break;
                default:
                    break;
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
                    case EVENT_CONCUSSIVE_STOMP:
                        Talk(SAY_STOMP);
                        DoCastAOE(SPELL_CONCUSSIVE_STOMP);
                        events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP, 30000);
                        break;
                    default:
                        break;
                }
            }
            if (!(events.IsInPhase(PHASE_1)))
                DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_lord_rhyolithAI(creature);
    }
};

class npc_fl_foot : public CreatureScript
{
public:
    npc_fl_foot() : CreatureScript("npc_fl_foot") { }

    struct npc_fl_footAI : public ScriptedAI
    {
        npc_fl_footAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            uint32 lostStacks = (80 - me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount()) / 15;
            switch (me->GetEntry())
            {
                case NPC_RIGHT_FOOT:
                {
                    if (Creature* rhyolith = me->FindNearestCreature(BOSS_LORD_RHYOLITH, 200.0f, true))
                    {
                        if (damage > uint32((10000 * me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount() / 100) * lostStacks))
                            rhyolith->AI()->DoAction(ACTION_BALANCE_RIGHT);
                    }
                    break;
                }
                case NPC_LEFT_FOOT:
                {
                    if (Creature* rhyolith = me->FindNearestCreature(BOSS_LORD_RHYOLITH, 200.0f, true))
                    {
                        if (damage > uint32((10000 * me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount() / 100) * lostStacks))
                            rhyolith->AI()->DoAction(ACTION_BALANCE_LEFT);
                    }
                    break;
                }
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
        return new npc_fl_footAI(creature);
    }
};

class npc_fl_volcano : public CreatureScript
{
public:
    npc_fl_volcano() : CreatureScript("npc_fl_volcano") { }

    struct npc_fl_volcanoAI : public ScriptedAI
    {
        npc_fl_volcanoAI(Creature* creature) : ScriptedAI(creature)
        {
            exploded = false;
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->SetReactState(REACT_PASSIVE);
        };

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EXPLOSION:
                        DoCastAOE(SPELL_EXPLOSION);
                        DoCastAOE(SPELL_MAGMA);
                        break;
                    default:
                        break;
                }
            }
        }

        bool exploded;
        EventMap events;
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_volcanoAI(creature);
    }
};

void AddSC_boss_lord_rhyolith()
{
    new boss_lord_rhyolith();
    new npc_fl_foot();
    new npc_fl_volcano();
}
