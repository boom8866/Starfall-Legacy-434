
#include "shadowfang_keep.h"

enum Spells
{
    // Commander Springvale
    SPELL_MALEFIC_STRIKE            = 93685,
    SPELL_UNHOLY_POWER              = 93686,
    SPELL_UNHOLY_POWER_H            = 93735,
    SPELL_SHIELD_OF_THE_PERFIDIOUS  = 93693,
    SPELL_DESECRATION               = 93687,
    SPELL_DESECRATION_ARM_AURA      = 67803,
    SPELL_DESECRATION_AURA          = 93690,
    SPELL_WORD_OF_SHAME             = 93852,

    // Wailing Guardsman
    SPELL_UNHOLY_EMPOWERMENT        = 93844,
    SPELL_SCREAMS_OF_THE_PAST       = 7074,
    SPELL_MORTAL_STRIKE             = 91801,

    //Tormented Officer
    SPELL_FORSAKEN_ABILITY          = 7054,
    SPELL_FORSAKEN_ABILITY_DAMAGE   = 7038,
    SPELL_FORSAKEN_ABILITY_ARMOR    = 7039,
    SPELL_FORSAKEN_ABILITY_HEAL     = 7041,
    SPELL_FORSAKEN_ABILITY_SPEED    = 7042,
    SPELL_FORSAKEN_ABILITY_HEALTH   = 7040,

    SPELL_SHIELD_WALL               = 91463,
};

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_ADDS    = 1,
    SAY_SLAY    = 2,
    SAY_DEATH   = 3,
};

enum Events
{
    // Commander Springvale
    EVENT_MALEFIC_STRIKE = 1,
    EVENT_SHIELD_OF_THE_PERFIDIOUS,
    EVENT_DESECRATION,
    EVENT_SUMMON_ADDS,
    EVENT_WORD_OF_SHAME,

    // Wailing Guardsman
    EVENT_UNHOLY_EMPOWERMENT,
    EVENT_SCREAMS_OF_THE_PAST,
    EVENT_MORTAL_STRIKE,

    // Tormented Officer
    EVENT_FORSAKEN_ABILITY,
};

Position const OfficerPos = {-229.681f, 2260.03f, 102.84f, 3.45575f};
Position const GuardsmanPos = {-228.33f, 2254.39f, 102.84f, 3.36848f};

Position const SpawnPos[] =
{
    {-235.5069f, 2230.76f, 93.70721f, 0.0f}, // Wailing Guardsman
    {-266.2257f, 2270.207f, 96.51828f, 0.0f}, // Tormented Officer
};

class boss_commander_springvale : public CreatureScript
{
public:
    boss_commander_springvale() : CreatureScript("boss_commander_springvale") { }

    struct boss_commander_springvaleAI : public BossAI
    {
        boss_commander_springvaleAI(Creature* creature) : BossAI(creature, DATA_COMMANDER_SPRINGVALE)
        {
        }

        void Reset()
        {
            _Reset();
            if (IsHeroic())
            {
                me->SummonCreature(NPC_WAILING_GUARDSMAN, GuardsmanPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                me->SummonCreature(NPC_TORMENTED_OFFICER, OfficerPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_MALEFIC_STRIKE, 5000);
            events.ScheduleEvent(EVENT_SHIELD_OF_THE_PERFIDIOUS, 31000);
            events.ScheduleEvent(EVENT_DESECRATION, 9500);
            if (IsHeroic())
            {
                events.ScheduleEvent(EVENT_WORD_OF_SHAME, 16500);
                events.ScheduleEvent(EVENT_SUMMON_ADDS, 41000);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WORD_OF_SHAME);
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
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SetBossState(DATA_COMMANDER_SPRINGVALE, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WORD_OF_SHAME);
            _DespawnAtEvade();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_DESECRATION_STALKER:
                    summon->CastSpell(summon, SPELL_DESECRATION_ARM_AURA);
                    summon->AddAura(SPELL_DESECRATION_AURA, summon);
                    summons.Summon(summon);
                    break;
                case NPC_TORMENTED_OFFICER:
                case NPC_WAILING_GUARDSMAN:
                    if (me->isInCombat())
                        summon->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), true);
                    summons.Summon(summon);
                    break;
                default:
                    summons.Summon(summon);
                    break;
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
                    case EVENT_MALEFIC_STRIKE:
                        if (!me->HasAura(SPELL_SHIELD_OF_THE_PERFIDIOUS))
                            DoCastVictim(SPELL_MALEFIC_STRIKE);
                        events.ScheduleEvent(EVENT_MALEFIC_STRIKE, urand(5000, 6000));
                        break;
                    case EVENT_SHIELD_OF_THE_PERFIDIOUS:
                        if (Unit* target = me->getVictim())
                        {
                            if (Creature* focus = me->SummonCreature(NPC_SHIELD_FOCUS, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 3500))
                            {
                                if (IsHeroic())
                                    me->RemoveAurasDueToSpell(SPELL_UNHOLY_POWER_H);
                                else
                                    me->RemoveAurasDueToSpell(SPELL_UNHOLY_POWER);
                                me->CastSpell(focus, SPELL_SHIELD_OF_THE_PERFIDIOUS, true);
                            }
                        }
                        break;
                    case EVENT_DESECRATION:
                        DoCastAOE(SPELL_DESECRATION);
                        events.ScheduleEvent(EVENT_DESECRATION, 28000);
                        break;
                    case EVENT_SUMMON_ADDS:
                        Talk(SAY_ADDS);
                        me->SummonCreature(NPC_WAILING_GUARDSMAN, SpawnPos[0], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                        me->SummonCreature(NPC_TORMENTED_OFFICER, SpawnPos[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                        events.ScheduleEvent(EVENT_SUMMON_ADDS, 41000);
                        break;
                    case EVENT_WORD_OF_SHAME:
                        if (IsHeroic())
                            me->RemoveAurasDueToSpell(SPELL_UNHOLY_POWER_H);
                        else
                            me->RemoveAurasDueToSpell(SPELL_UNHOLY_POWER);

                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            target->AddAura(SPELL_WORD_OF_SHAME, target);
                        events.ScheduleEvent(EVENT_WORD_OF_SHAME, 15500);
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
        return new boss_commander_springvaleAI (creature);
    }
};

class npc_wailing_guardsman : public CreatureScript
{
public:
    npc_wailing_guardsman() :  CreatureScript("npc_wailing_guardsman") { }

    struct npc_wailing_guardsmanAI : public ScriptedAI
    {
        npc_wailing_guardsmanAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_MORTAL_STRIKE, 11000);
            events.ScheduleEvent(EVENT_SCREAMS_OF_THE_PAST, 14000);
            events.ScheduleEvent(EVENT_UNHOLY_EMPOWERMENT, urand(28000, 30000));
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MORTAL_STRIKE:
                        DoCastVictim(SPELL_MORTAL_STRIKE);
                        events.ScheduleEvent(EVENT_MORTAL_STRIKE, 12000);
                        break;
                    case EVENT_SCREAMS_OF_THE_PAST:
                        DoCastAOE(SPELL_SCREAMS_OF_THE_PAST);
                        break;
                    case EVENT_UNHOLY_EMPOWERMENT:
                        if (Creature* springvale = me->FindNearestCreature(BOSS_COMMANDER_SPRINGVALE, 50.0f, true))
                            DoCast(springvale, SPELL_UNHOLY_EMPOWERMENT);
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
        return new npc_wailing_guardsmanAI(creature);
    }
};

class npc_tormented_officer : public CreatureScript
{
public:
    npc_tormented_officer() :  CreatureScript("npc_tormented_officer") { }

    struct npc_tormented_officerAI : public ScriptedAI
    {
        npc_tormented_officerAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
        {
            _shielded = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool _shielded;

        void EnterCombat(Unit* /*who*/)
        {
            _shielded = false; // Just in case
            events.ScheduleEvent(EVENT_UNHOLY_EMPOWERMENT, urand(28000, 30000));
            events.ScheduleEvent(EVENT_FORSAKEN_ABILITY, 17000);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            if (me->HealthBelowPct(20) && !_shielded)
            {
                DoCast(me, SPELL_SHIELD_WALL);
                _shielded = true;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FORSAKEN_ABILITY:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_FORSAKEN_ABILITY);
                        break;
                    case EVENT_UNHOLY_EMPOWERMENT:
                        if (Creature* springvale = me->FindNearestCreature(BOSS_COMMANDER_SPRINGVALE, 50.0f, true))
                            DoCast(springvale, SPELL_UNHOLY_EMPOWERMENT);
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
        return new npc_tormented_officerAI(creature);
    }
};

class spell_sfk_forsaken_ability : public SpellScriptLoader
{
    public:
        spell_sfk_forsaken_ability() : SpellScriptLoader("spell_sfk_forsaken_ability") { }

        class spell_sfk_forsaken_ability_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sfk_forsaken_ability_AuraScript);

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (Unit* owner = GetOwner()->ToUnit())
                {
                    switch (urand(0, 4))
                    {
                        case 0: // Damage
                            owner->AddAura(SPELL_FORSAKEN_ABILITY_DAMAGE, owner);
                            break;
                        case 1: // Armor
                            owner->AddAura(SPELL_FORSAKEN_ABILITY_ARMOR, owner);
                            break;
                        case 2: // Speed
                            owner->AddAura(SPELL_FORSAKEN_ABILITY_SPEED, owner);
                            break;
                        case 3: // Heal
                            owner->AddAura(SPELL_FORSAKEN_ABILITY_HEAL, owner);
                            break;
                        case 4: // Health
                            owner->AddAura(SPELL_FORSAKEN_ABILITY_HEALTH, owner);
                            break;
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sfk_forsaken_ability_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sfk_forsaken_ability_AuraScript();
        }
};

void AddSC_boss_commander_springvale()
{
    new boss_commander_springvale();
    new npc_wailing_guardsman();
    new npc_tormented_officer();
    new spell_sfk_forsaken_ability();
}
