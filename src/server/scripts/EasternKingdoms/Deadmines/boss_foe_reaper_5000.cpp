#include "ScriptPCH.h"
#include "Object.h"
#include "deadmines.h"

enum Spells
{
    SPELL_ENERGIZE              = 89132,
    SPELL_ENERGIZED             = 91733, // triggers -> 89200,
    SPELL_ON_FIRE               = 91737,
    SPELL_COSMETIC_STAND        = 88906,

    // Foe-Reaper-5000
    SPELL_OFFLINE               = 88348,
    SPELL_ONLINE                = 89198,
    SPELL_RED_EYES              = 24263,

    SPELL_REAPER_STRIKE         = 88490,
    SPELL_OVERDRIVE             = 88481,

    SPELL_HARVEST               = 88495,
    SPELL_HARVEST_AURA          = 88497,
    SPELL_HARVEST_SWEEP         = 88521,
    SPELL_SAFETY_REST_OFFLINE   = 88522,
    SPELL_SUMMON_MOLTEN_SLAG    = 91839,
};

enum Phases
{
    PHASE_INTRO     = 0,
    PHASE_BATTLE    = 1,
};

enum Actions
{
    ACTION_ACTIVATE     = 1,
};

enum Events
{
    EVENT_ACTIVATE_1 = 1,
    EVENT_ACTIVATE_2,
    EVENT_OVERDRIVE,
};

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_DEATH               = 1,
    SAY_ANNOUNCE_OVERDRIVE  = 2,
    SAY_OVERDRIVE           = 3,
};

class boss_foe_reaper_5000 : public CreatureScript
{
public:
    boss_foe_reaper_5000() : CreatureScript("boss_foe_reaper_5000") { }

    struct boss_foe_reaper_5000AI : public BossAI
    {
        boss_foe_reaper_5000AI(Creature* creature) : BossAI(creature, DATA_FOE_REAPER_5000)
        {
        }

        void Reset()
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.SetPhase(PHASE_BATTLE);
            events.ScheduleEvent(EVENT_OVERDRIVE, 12000);
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ACTIVATE:
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ACTIVATE_1:
                        DoCastAOE(SPELL_RED_EYES);
                        events.ScheduleEvent(EVENT_ACTIVATE_2, 3000);
                        break;
                    case EVENT_ACTIVATE_2:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveAurasDueToSpell(SPELL_COSMETIC_STAND);
                        break;
                    case EVENT_OVERDRIVE:
                        Talk(SAY_OVERDRIVE);
                        Talk(SAY_ANNOUNCE_OVERDRIVE);
                        DoCastAOE(SPELL_OVERDRIVE);
                        events.ScheduleEvent(EVENT_OVERDRIVE, 53000, 0, PHASE_BATTLE);
                        break;
                    default:
                        break;
                }           
            }
            DoSpellAttackIfReady(SPELL_REAPER_STRIKE);
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_foe_reaper_5000AI (creature);
    }
};

class npc_defias_reaper : public CreatureScript
{
public:
    npc_defias_reaper() : CreatureScript("npc_defias_reaper") { }

    struct npc_defias_reaperAI : public ScriptedAI
    {
        npc_defias_reaperAI(Creature* creature) : ScriptedAI(creature), vehicle(creature->GetVehicleKit())
        {
            instance = creature->GetInstanceScript();
            _status = false;
        }

        InstanceScript* instance;
        bool _status;
        Vehicle* vehicle;

        void Reset()
        {
            me->AddAura(SPELL_COSMETIC_STAND, me);
            me->SetPower(POWER_ENERGY, 100);
            me->SetMaxPower(POWER_ENERGY, 100);
            me->setPowerType(POWER_ENERGY);
            if (_status == true)
            {
                if (!me->HasAura(SPELL_ON_FIRE))
                    me->AddAura(SPELL_ON_FIRE, me);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void PassengerBoarded(Unit* /*passenger*/, int8 SeatId, bool apply)
        {
            me->RemoveAurasDueToSpell(SPELL_COSMETIC_STAND);
        }

        void JustDied(Unit* /*Killer*/)
        {
            if (!me || _status == true)
                return;

            Energizing();
        }

        void Energizing()
        {
            _status = true;
            me->SetHealth(me->GetMaxHealth() * 0.15);
            me->setFaction(35);
            me->AddAura(SPELL_ON_FIRE, me);
            me->CastSpell(me, SPELL_ON_FIRE);
            me->SetInCombatWithZone();

            if (Creature* reaper = me->FindNearestCreature(BOSS_FOE_REAPER_5000, 200.0f))
            {
                me->CastSpell(reaper, SPELL_ENERGIZE);
                reaper->AI()->DoAction(ACTION_ACTIVATE);
            }

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            if (!me || damage <= 0 || _status == true)
                return;

            if (me->GetHealth()-damage <= me->GetMaxHealth() * 0.10)
            {
                damage = 0;
                Energizing();
            }
        }

        void UpdateAI(uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_defias_reaperAI (creature);
    }
};

void AddSC_boss_foe_reaper_5000()
{
    new boss_foe_reaper_5000();
    new npc_defias_reaper();
}
