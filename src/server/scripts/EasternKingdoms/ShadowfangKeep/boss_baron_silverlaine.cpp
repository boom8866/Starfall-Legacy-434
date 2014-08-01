
#include "shadowfang_keep.h"

enum Texts
{
    SAY_AGGRO = 0,
    SAY_DEATH = 1,
    SAY_SLAY  = 2,
};

enum Events
{
    // Baron Silverlaine
    EVENT_VEIL_OF_SHADOW = 1,
    EVENT_CURSED_VEIL,
    EVENT_SUMMON_WORGEN_SPIRIT,

    // Odo the Blindwatcher
    EVENT_HOWLING_RAGE,

    // Wolf Master Nandos
    EVENT_CLAW,

    // Razorclaw the Butcher
    EVENT_SPECTRAL_RUSH,
    EVENT_SPECTRAL_RAVAGING,
    EVENT_BUTCHER_DRAIN,

    // Rethilgore
    EVENT_SOUL_DRAIN,
};

enum Spells
{
    SPELL_VEIL_OF_SHADOWS                           = 23224,
    SPELL_CURSED_VEIL                               = 93956,
    SPELL_SUMMON_WORGEN_SPIRIT                      = 93857,

    SPELL_SUMMON_WORGEN_SPIRIT_NANDOS_DUMMY         = 93896, // Dummy Summon
    SPELL_SUMMON_WORGEN_SPIRIT_NANDOS_SUMMON        = 93899,

    SPELL_SUMMON_WORGEN_SPIRIT_ODO_DUMMY            = 93859, // Dummy Summon
    SPELL_SUMMON_WORGEN_SPIRIT_ODO_SUMMON           = 93899,

    SPELL_SUMMON_WORGEN_SPIRIT_RAZORCLAW_DUMMY      = 93921, // Dummy Summon
    SPELL_SUMMON_WORGEN_SPIRIT_RAZORCLAW_SUMMON     = 93924,
    
    SPELL_SUMMON_WORGEN_SPIRIT_RETHILGORE_DUMMY     = 93925, // Dummy Summon
    SPELL_SUMMON_WORGEN_SPIRIT_RETHILGORE_SUMMON    = 93927,

    // Odo the Blindwatcher
    SPELL_HOWLING_RAGE                              = 93931,
    SPELL_BLINDING_SHADOWS                          = 93952,

    // Wolf Master Nandos
    SPELL_CLAW                                      = 16827,
    SPELL_GHOST_AURA                                = 93853,
    SPELL_SUMMON_LUPINE_SPECTRE                     = 94199,

    // Razorclaw the Butcher
    SPELL_SPECTRAL_RAVAGING                         = 93930,
    SPELL_SPECTRAL_RUSH                             = 93914,
    SPELL_BUTCHER_DRAIN                             = 7485,

    // Rethilgore
    SPELL_SOUL_DRAIN                                = 93863,
};

class boss_baron_silverlaine : public CreatureScript
{
public:
    boss_baron_silverlaine() : CreatureScript("boss_baron_silverlaine") { }

    struct boss_baron_silverlaineAI : public BossAI
    {
        boss_baron_silverlaineAI(Creature* creature) : BossAI(creature, DATA_BARON_SILVERLAINE)
        {
            _worgenCounter = 0;
        }

        uint8 _worgenCounter;

        void Reset()
        {
            _Reset();
            _worgenCounter = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_CURSED_VEIL, 6000);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            DespawnWorgenSpirits();
        }

        void KilledUnit(Unit* target)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            summons.DespawnAll();
            _worgenCounter = 0;
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            DespawnWorgenSpirits();
            events.Reset();
            _DespawnAtEvade();
        }

        void DespawnWorgenSpirits()
        {
            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_WOLF_MASTER_NANDOS, 200.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_ODO_THE_BLINDWATCHER, 200.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_RETHILGORE, 200.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_RAZORCLAW_THE_BUTCHER, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, (*itr));
                (*itr)->DespawnOrUnsummon(200);
            }

            units.empty();
            GetCreatureListWithEntryInGrid(units, me, NPC_NANDOS_DUMMY, 200.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_RAZORCLAW_DUMMY, 200.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_RETHILGORE, 200.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_ODO_DUMMY, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon(1);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_ODO_DUMMY:
                    summon->AddAura(SPELL_SUMMON_WORGEN_SPIRIT_ODO_SUMMON, summon);
                    break;
                case NPC_NANDOS_DUMMY:
                    summon->AddAura(SPELL_SUMMON_WORGEN_SPIRIT_NANDOS_SUMMON, summon);
                    break;
                case NPC_RAZORCLAW_DUMMY:
                    summon->AddAura(SPELL_SUMMON_WORGEN_SPIRIT_RAZORCLAW_SUMMON, summon);
                    break;
                case NPC_RETHILGORE_DUMMY:
                    summon->AddAura(SPELL_SUMMON_WORGEN_SPIRIT_RETHILGORE_SUMMON, summon);
                    break;
                default:
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            switch (IsHeroic())
            {
                case true:
                {
                    if (me->HealthBelowPct(90) && _worgenCounter == 0)
                    {
                        DoCastAOE(SPELL_SUMMON_WORGEN_SPIRIT);
                        _worgenCounter++;
                    }
                    else if (me->HealthBelowPct(60) && _worgenCounter == 1)
                    {
                        DoCastAOE(SPELL_SUMMON_WORGEN_SPIRIT);
                        _worgenCounter++;
                    }
                    else if (me->HealthBelowPct(30) && _worgenCounter == 2)
                    {
                        DoCastAOE(SPELL_SUMMON_WORGEN_SPIRIT);
                        _worgenCounter++;
                    }
                    break;
                }
                case false:
                {
                    if (me->HealthBelowPct(75) && _worgenCounter == 0)
                    {
                        DoCastAOE(SPELL_SUMMON_WORGEN_SPIRIT);
                        _worgenCounter++;
                    }
                    else if (me->HealthBelowPct(35) && _worgenCounter == 1)
                    {
                        DoCastAOE(SPELL_SUMMON_WORGEN_SPIRIT);
                        _worgenCounter++;
                    }
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CURSED_VEIL:
                        DoCastAOE(SPELL_CURSED_VEIL);
                        events.ScheduleEvent(EVENT_CURSED_VEIL, 26500);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_baron_silverlaineAI (creature);
    }
};

class npc_wolf_master_nandos : public CreatureScript
{
public:
    npc_wolf_master_nandos() :  CreatureScript("npc_wolf_master_nandos") { }

    struct npc_wolf_master_nandosAI : public ScriptedAI
    {
        npc_wolf_master_nandosAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_GHOST_AURA, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            DoZoneInCombat();
            events.ScheduleEvent(EVENT_CLAW, 1600);
            for (uint8 i = 0; i < 3; i++);
                DoCastAOE(SPELL_SUMMON_LUPINE_SPECTRE);
        }

        void JustSummoned(Creature* summon)
        {
            summon->AddAura(SPELL_GHOST_AURA, summon);
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->DespawnOrUnsummon(5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CLAW:
                        DoCastVictim(SPELL_CLAW);
                        events.ScheduleEvent(EVENT_CLAW, 3000);
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
        return new npc_wolf_master_nandosAI(creature);
    }
};

class npc_odo_the_blindwatcher : public CreatureScript
{
public:
    npc_odo_the_blindwatcher() :  CreatureScript("npc_odo_the_blindwatcher") { }

    struct npc_odo_the_blindwatcherAI : public ScriptedAI
    {
        npc_odo_the_blindwatcherAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_GHOST_AURA, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            DoZoneInCombat();
            events.ScheduleEvent(EVENT_HOWLING_RAGE, 5500);
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->DespawnOrUnsummon(5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_HOWLING_RAGE:
                        DoCastVictim(SPELL_BLINDING_SHADOWS);
                        DoCastAOE(SPELL_HOWLING_RAGE);
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
        return new npc_odo_the_blindwatcherAI(creature);
    }
};

class npc_razorclaw_the_butcher : public CreatureScript
{
public:
    npc_razorclaw_the_butcher() :  CreatureScript("npc_razorclaw_the_butcher") { }

    struct npc_razorclaw_the_butcherAI : public ScriptedAI
    {
        npc_razorclaw_the_butcherAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
        }

        InstanceScript* instance;
        EventMap events;
        Unit* player;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_GHOST_AURA, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            DoZoneInCombat();
            events.ScheduleEvent(EVENT_SPECTRAL_RUSH, 16000);
            events.ScheduleEvent(EVENT_BUTCHER_DRAIN, 2500);
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->DespawnOrUnsummon(5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPECTRAL_RUSH:
                        if (player = SelectTarget(SELECT_TARGET_FARTHEST, 0, 0, true, 0))
                        {
                            events.ScheduleEvent(EVENT_SPECTRAL_RAVAGING, 500);
                            DoCast(player, SPELL_SPECTRAL_RUSH);
                        }
                        break;
                    case EVENT_SPECTRAL_RAVAGING:
                        DoCast(player, SPELL_SPECTRAL_RAVAGING);
                        break;
                    case EVENT_BUTCHER_DRAIN:
                        DoCastVictim(SPELL_BUTCHER_DRAIN);
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
        return new npc_razorclaw_the_butcherAI(creature);
    }
};

class npc_rethilgore : public CreatureScript
{
public:
    npc_rethilgore() :  CreatureScript("npc_rethilgore") { }

    struct npc_rethilgoreAI : public ScriptedAI
    {
        npc_rethilgoreAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_GHOST_AURA, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            DoZoneInCombat();
            events.ScheduleEvent(EVENT_SOUL_DRAIN, 10000);
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->DespawnOrUnsummon(5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SOUL_DRAIN:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_SOUL_DRAIN);
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
        return new npc_rethilgoreAI(creature);
    }
};

class spell_sfk_summon_worgen_spirit : public SpellScriptLoader
{
public:
    spell_sfk_summon_worgen_spirit() : SpellScriptLoader("spell_sfk_summon_worgen_spirit") { }

    class spell_sfk_summon_worgen_spirit_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sfk_summon_worgen_spirit_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                switch (urand(0, 3))
                {
                    case 0: // Nandos
                        caster->CastSpell((Unit*)NULL, SPELL_SUMMON_WORGEN_SPIRIT_NANDOS_DUMMY, true);
                        break;
                    case 1: // Odo
                        caster->CastSpell((Unit*)NULL, SPELL_SUMMON_WORGEN_SPIRIT_ODO_DUMMY, true);
                        break;
                    case 2: // Razorclaw
                        caster->CastSpell((Unit*)NULL, SPELL_SUMMON_WORGEN_SPIRIT_RAZORCLAW_DUMMY, true);
                        break;
                    case 3: // Rethilgore
                        caster->CastSpell((Unit*)NULL, SPELL_SUMMON_WORGEN_SPIRIT_RETHILGORE_DUMMY, true);
                        break;
                }
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_sfk_summon_worgen_spirit_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sfk_summon_worgen_spirit_SpellScript();
    }
};

void AddSC_boss_baron_silverlaine()
{
    new boss_baron_silverlaine();
    new spell_sfk_summon_worgen_spirit();
    new npc_wolf_master_nandos();
    new npc_odo_the_blindwatcher();
    new npc_razorclaw_the_butcher();
    new npc_rethilgore();
}
