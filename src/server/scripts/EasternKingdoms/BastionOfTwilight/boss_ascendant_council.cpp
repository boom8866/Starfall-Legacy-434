
#include "bastion_of_twilight.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_ABILITY = 2,
    SAY_ANNOUNCE_ABILITY = 3,
    SAY_DEATH   = 4,
};

enum Spells
{
    // Feludius
    SPELL_WATER_BOMB            = 82699,
    SPELL_WATER_BOMB_TRIGGERED  = 82700,
    SPELL_WATERLOGGED           = 82762,
    SPELL_HYDRO_LANCE           = 82752,
    SPELL_GLACIATE              = 82746,
    SPELL_FROZEN                = 82772,
    SPELL_HEART_OF_ICE          = 82665,
    SPELL_FROST_IMBUED          = 82666,

    // Ignacious
    SPELL_AEGIS_OF_FLAME        = 82631,
    SPELL_RISING_FLAMES         = 82636,
};

enum Events
{
    // Feludius
    EVENT_WATER_BOMB = 1,
    EVENT_GLACIATE,
    EVENT_HYDRO_LANCE,
    EVENT_HEART_OF_ICE,

    // Ignacious
    EVENT_TALK_INTRO,
    EVENT_AEGIS_OF_FLAME,
    EVENT_RISING_FLAMES,

    // Misc Events
    EVENT_APPLY_IMMUNITY,
};

enum Actions
{
    ACTION_INTRO_1 = 1,
    ACTION_INTRO_2,
    ACTION_INTRO_3,
};

class at_ascendant_council_1 : public AreaTriggerScript
{
public:
    at_ascendant_council_1() : AreaTriggerScript("at_ascendant_council_1") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_1);
        return true;
    }
};

class at_ascendant_council_2 : public AreaTriggerScript
{
public:
    at_ascendant_council_2() : AreaTriggerScript("at_ascendant_council_2") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_2);
        return true;
    }
};

class at_ascendant_council_3 : public AreaTriggerScript
{
public:
    at_ascendant_council_3() : AreaTriggerScript("at_ascendant_council_3") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
            controller->AI()->DoAction(ACTION_INTRO_3);
        return true;
    }
};

class boss_feludius : public CreatureScript
{
public:
    boss_feludius() : CreatureScript("boss_feludius") { }

    struct boss_feludiusAI : public BossAI
    {
        boss_feludiusAI(Creature* creature) : BossAI(creature, DATA_FELUDIUS)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            if (Creature* ignacious = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS)))
                ignacious->AI()->AttackStart(who);

            events.ScheduleEvent(EVENT_WATER_BOMB, 15000); // 33-35 seconds cooldown
            events.ScheduleEvent(EVENT_GLACIATE, 30000);
            events.ScheduleEvent(EVENT_HYDRO_LANCE, urand(6000, 10000));
            events.ScheduleEvent(EVENT_HEART_OF_ICE, 18000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
        }

        void MakeInterruptable(bool apply)
        {
            if (apply)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
            }
            else
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
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
                    case EVENT_WATER_BOMB:
                        for (uint8 i = 0; i < 16; i++)
                        {
                            float distance = frand(2.0f, 50.0f);
                            float ori = frand(0.0f, M_PI * 2);
                            float x = me->GetPositionX() + cos(ori) * distance;
                            float y = me->GetPositionY() + sin(ori) * distance;
                            float z = me->GetPositionZ();
                            me->SummonCreature(NPC_WATER_BOMB, x, y, z, ori, TEMPSUMMON_TIMED_DESPAWN, 15000);
                        }
                        DoCast(me, SPELL_WATER_BOMB);
                        events.ScheduleEvent(EVENT_WATER_BOMB, urand(33000, 35000));
                        break;
                    case EVENT_GLACIATE:
                        Talk(SAY_ANNOUNCE_ABILITY);
                        Talk(SAY_ABILITY);
                        DoCast(me, SPELL_GLACIATE);
                        events.ScheduleEvent(EVENT_GLACIATE, urand(33000, 35000));
                        break;
                    case EVENT_HYDRO_LANCE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            MakeInterruptable(true);
                            DoCast(target, SPELL_HYDRO_LANCE);
                        }
                        events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 1500);
                        events.ScheduleEvent(EVENT_HYDRO_LANCE, 12000);
                        break;
                    case EVENT_APPLY_IMMUNITY:
                        MakeInterruptable(false);
                        break;
                    case EVENT_HEART_OF_ICE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_HEART_OF_ICE);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_feludiusAI(creature);
    }
};

class boss_ignacious : public CreatureScript
{
public:
    boss_ignacious() : CreatureScript("boss_ignacious") { }

    struct boss_ignaciousAI : public BossAI
    {
        boss_ignaciousAI(Creature* creature) : BossAI(creature, DATA_IGNACIOUS)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TALK_INTRO, 4000);
            events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, 31000);
            if (Creature* feludius = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS)))
                feludius->AI()->AttackStart(who);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
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
                    case EVENT_TALK_INTRO:
                        Talk(SAY_AGGRO);
                        break;
                    case EVENT_AEGIS_OF_FLAME:
                        DoCast(me, SPELL_AEGIS_OF_FLAME);
                        events.ScheduleEvent(EVENT_RISING_FLAMES, 1600);
                        break;
                    case EVENT_RISING_FLAMES:
                        DoCast(me, SPELL_RISING_FLAMES);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ignaciousAI(creature);
    }
};

class boss_terrastra : public CreatureScript
{
public:
    boss_terrastra() : CreatureScript("boss_terrastra") { }

    struct boss_terrastraAI : public BossAI
    {
        boss_terrastraAI(Creature* creature) : BossAI(creature, DATA_TERRASTRA)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
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
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_terrastraAI(creature);
    }
};

class boss_arion : public CreatureScript
{
public:
    boss_arion() : CreatureScript("boss_arion") { }

    struct boss_arionAI : public BossAI
    {
        boss_arionAI(Creature* creature) : BossAI(creature, DATA_ARION)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
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
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_arionAI(creature);
    }
};

class npc_ascendant_council_controller : public CreatureScript
{
public:
    npc_ascendant_council_controller() : CreatureScript("npc_ascendant_council_controller") { }

    struct npc_ascendant_council_controllerAI : public ScriptedAI
    {
        npc_ascendant_council_controllerAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
            _intro1Done = false;
            _intro2Done = false;
            _intro3Done = false;
        }

        InstanceScript* instance;
        SummonList summons;
        EventMap events;
        bool _intro1Done;
        bool _intro2Done;
        bool _intro3Done;

        void Reset()
        {
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_INTRO_1:
                if (!_intro1Done)
                {
                    if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                        chogall->AI()->TalkToMap(4);
                    _intro1Done = true;
                }
                break;
            case ACTION_INTRO_2:
                if (!_intro2Done)
                {
                    if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                        chogall->AI()->TalkToMap(5);
                    _intro2Done = true;
                }
                break;
            case ACTION_INTRO_3:
                if (!_intro3Done)
                {
                    if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                        chogall->AI()->TalkToMap(6);
                    _intro3Done = true;
                }
                break;
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
        return new npc_ascendant_council_controllerAI(creature);
    }
};

class spell_ac_water_bomb : public SpellScriptLoader
{
public:
    spell_ac_water_bomb() : SpellScriptLoader("spell_ac_water_bomb") { }

    class spell_ac_water_bomb_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_water_bomb_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_WATER_BOMB_TRIGGERED, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_water_bomb_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_water_bomb_SpellScript();
    }
};

class spell_ac_glaciate : public SpellScriptLoader
{
public:
    spell_ac_glaciate() : SpellScriptLoader("spell_ac_glaciate") { }

    class spell_ac_glaciate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ac_glaciate_SpellScript);

        void HandleDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                {
                    float distance = caster->GetDistance2d(target);
                    if (distance > 1.0f)
                        SetHitDamage(int32(GetHitDamage() - ((caster->GetMap()->Is25ManRaid() ? 10000 : 4000) * distance)));

                    if (GetHitDamage() < 10000)
                        SetHitDamage(10000);
                }
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetHitUnit())
                    if (target->HasAura(SPELL_WATERLOGGED))
                    {
                        target->RemoveAurasDueToSpell(SPELL_WATERLOGGED);
                        caster->CastSpell(target, SPELL_FROZEN, true);
                    }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ac_glaciate_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_ac_glaciate_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ac_glaciate_SpellScript();
    }
};

class spell_ac_heart_of_ice : public SpellScriptLoader
{
public:
    spell_ac_heart_of_ice() : SpellScriptLoader("spell_ac_heart_of_ice") { }

    class spell_ac_heart_of_ice_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ac_heart_of_ice_AuraScript);

        void OnPeriodic(AuraEffect const* aurEff)
        {
            uint64 damage;
            damage = aurEff->GetBaseAmount() * aurEff->GetTickNumber();
            GetEffect(EFFECT_0)->ChangeAmount(damage);
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                target->CastSpell(target, SPELL_FROST_IMBUED, true);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                target->RemoveAurasDueToSpell(SPELL_FROST_IMBUED);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ac_heart_of_ice_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE);
            OnEffectApply += AuraEffectApplyFn(spell_ac_heart_of_ice_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_ac_heart_of_ice_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ac_heart_of_ice_AuraScript();
    }
};

void AddSC_boss_ascendant_council()
{
    new at_ascendant_council_1();
    new at_ascendant_council_2();
    new at_ascendant_council_3();
    new boss_feludius();
    new boss_ignacious();
    new boss_terrastra();
    new boss_arion();
    new npc_ascendant_council_controller();
    new spell_ac_water_bomb();
    new spell_ac_glaciate();
    new spell_ac_heart_of_ice();
}
