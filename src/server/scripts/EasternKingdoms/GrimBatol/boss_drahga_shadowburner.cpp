#include "ScriptPCH.h"
#include "grim_batol.h"
#include "Vehicle.h"

enum Spells
{
    // Drahga
   SPELL_BURNING_SHADOWBOLT         = 75245,
   SPELL_BURNING_SHADOWBOLT_DUMMY   = 75246,
   SPELL_INVOCATION_OF_FLAME_SUMMON = 75218,
   SPELL_TWILIGHT_PROTECTION        = 76303,
   SPELL_RIDE_VEHICLE               = 43671,

   // Invocation of Flame Stalker
   SPELL_INVOCATION_OF_FLAME_AURA   = 75222,
   SPELL_INVOCATION_OF_FLAME_DAMAGE = 75232,

   // Invoked Flaming Spirit
   SPELL_INVOKED_FLAME              = 75235,
   SPELL_FLAMING_FIXATE             = 82850,
   SPELL_QUIETE_SUICIDE             = 3617,

   // Valiona
   SPELL_TWILIGHT_SHIFT             = 75328,
   SPELL_SHREDDING_SWIPE            = 75271,

   SPELL_DEVOURING_FLAMES_AOE       = 90945,
   SPELL_DEVOURING_FLAMES           = 90950,

   // Seeping Twilight Visual
   SPELL_SEEPING_TWILIGHT_VISUAL    = 75318,
   SPELL_SEEPING_TWILIGHT_AURA      = 75274,
};

enum Texts
{
    // Drahga
    SAY_INTRO                           = 0,
    SAY_AGGRO                           = 1,
    SAY_ANNOUNCE_INVOCATION_OF_FLAME    = 2,
    SAY_INVOCATION_OF_FLAME             = 3,
    SAY_VALIONA_INTRO                   = 4,
    SAY_SLAY                            = 5,
    SAY_DEATH                           = 6,

    // Valiona
    SAY_VALIONA_AGGRO                   = 0,
    SAY_ANNOUNCE_DEVOURING_FLAMES       = 1,
    SAY_VALIONA_FLEE                    = 2,
};

enum Events
{
    // Drahga
    EVENT_BURNING_SHADOWBOLT = 1,
    EVENT_INVOCATION_OF_FLAME,
    EVENT_TALK_TO_VALIONA,

    // Valiona
    EVENT_MOVE_INTRO_1,
    EVENT_MOVE_INTRO_2,
    EVENT_MOVE_LAND,
    EVENT_LANDED,
    EVENT_ATTACK,
    EVENT_SHREDDING_SWIPE,
    EVENT_DEVOURING_FLAMES,
    EVENT_DEVOURING_FLAMES_CAST,
    EVENT_CLEAR_CAST,
    EVENT_MOVE_OUT,
    EVENT_DESPAWN,

    // Invoked Flaming Spirit
    EVENT_FOLLOW_PLAYER,
};

enum Phases
{
    PHASE_1 = 1,
    PHASE_2,
};

enum Actions
{
    ACTION_SCHEDULE_EVENTS = 1,
    ACTION_DESPAWN,
    ACTION_VALIONA_OFF,
};

enum Points
{
    POINT_DRAHGA_BORDER = 1,
    POINT_INTRO_1,
    POINT_INTRO_2,
    POINT_LAND,
    POINT_TAKEOFF,
    POINT_FLEE,
};

Position const DrahgaPos = {-402.139f, -668.642f, 266.1214f};
Position const ValionaSummonPos = {-377.974f, -668.2292f, 195.078f, 0.3316126f};

class boss_drahga_shadowburner : public CreatureScript
{
public:
    boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") { }

    struct boss_drahga_shadowburnerAI : public BossAI
    {
        boss_drahga_shadowburnerAI(Creature* creature) : BossAI(creature, DATA_DRAHGA_SHADOWBURNER)
        {
            _introDone = false;
            valiona = NULL;
        }

        Creature* valiona;
        bool _introDone;

        void Reset()
        {
            _Reset();
            _introDone = false;
            valiona = NULL;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.SetPhase(PHASE_1);
            events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 3000);
            events.ScheduleEvent(EVENT_INVOCATION_OF_FLAME, 9500);
        }

        void JustDied(Unit* /*victim*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            events.Reset();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_AGGRESSIVE);
            if (valiona != NULL)
            {
                valiona->AI()->DoAction(ACTION_DESPAWN);
                valiona = NULL;
            }
            _DespawnAtEvade();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_INVOCATION_OF_FLAME_STALKER:
                    summon->CastSpell(summon, SPELL_INVOCATION_OF_FLAME_AURA, true);
                    summon->CastSpell(summon, SPELL_INVOCATION_OF_FLAME_DAMAGE, true);
                    summons.Summon(summon);
                    break;
                default:
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
            if (me->HealthBelowPct(30) && events.IsInPhase(PHASE_1))
            {
                events.Reset();
                events.SetPhase(PHASE_2);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();
                me->AttackStop();
                me->CastStop();
                me->GetMotionMaster()->MovePoint(POINT_DRAHGA_BORDER, DrahgaPos);
                if (valiona = me->SummonCreature(NPC_VALIONA, ValionaSummonPos, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    valiona->SetHover(true);
                    valiona->SetDisableGravity(true);
                }
            }
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (point)
            {
                case POINT_DRAHGA_BORDER:
                    events.ScheduleEvent(EVENT_TALK_TO_VALIONA, 1);
                    break;
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_SCHEDULE_EVENTS:
                    events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 3000);
                    events.ScheduleEvent(EVENT_INVOCATION_OF_FLAME, 9500);
                    break;
                case ACTION_VALIONA_OFF:
                    valiona = NULL;
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
                    case EVENT_BURNING_SHADOWBOLT:
                        DoCast(SPELL_BURNING_SHADOWBOLT);
                        events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 2500);
                        break;
                    case EVENT_INVOCATION_OF_FLAME:
                        Talk(SAY_ANNOUNCE_INVOCATION_OF_FLAME);
                        Talk(SAY_INVOCATION_OF_FLAME);
                        DoCast(SPELL_INVOCATION_OF_FLAME_SUMMON);
                        events.ScheduleEvent(EVENT_INVOCATION_OF_FLAME, 29000);
                        break;
                    case EVENT_TALK_TO_VALIONA:
                        Talk(SAY_VALIONA_INTRO);
                        DoCast(valiona, SPELL_RIDE_VEHICLE);
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_drahga_shadowburnerAI (creature);
    }
};

Position const ValionaPos1 = {-376.5573f, -662.6962f, 263.1957f};
Position const ValionaPos2 = {-438.9549f, -697.1077f, 284.6884f};
Position const LandingPos = {-434.099f, -702.906f, 268.767f};
Position const FleePos = {-364.273f, -646.503f, 286.193f};

class npc_gb_valiona : public CreatureScript
{
public:
    npc_gb_valiona() : CreatureScript("npc_gb_valiona") { }

    struct npc_gb_valionaAI : public ScriptedAI
    {
        npc_gb_valionaAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
            _finished = false;
        }

        InstanceScript* instance;
        EventMap events;
        SummonList summons;
        bool _finished;

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_SEEPING_TWILIGHT:
                    summon->CastSpell(summon, SPELL_SEEPING_TWILIGHT_VISUAL, true);
                    summon->CastSpell(summon, SPELL_SEEPING_TWILIGHT_AURA, true);
                    summons.Summon(summon);
                    break;
            }
        }

        void PassengerBoarded(Unit* /*passenger*/, int8 /*seatId*/, bool /*apply*/)
        {
            events.ScheduleEvent(EVENT_MOVE_INTRO_1, 5000);
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (point)
            {
                case POINT_INTRO_1:
                    events.ScheduleEvent(EVENT_MOVE_INTRO_2, 1);
                    break;
                case POINT_INTRO_2:
                    events.ScheduleEvent(EVENT_MOVE_LAND, 1);
                    break;
                case POINT_LAND:
                    events.ScheduleEvent(EVENT_LANDED, 1);
                    break;
                case POINT_TAKEOFF:
                    events.ScheduleEvent(EVENT_MOVE_OUT, 1);
                    break;
                case POINT_FLEE:
                    events.ScheduleEvent(EVENT_DESPAWN, 1);
                    break;
                default:
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
            if (me->HealthBelowPct(20) && !_finished)
            {
                Talk(SAY_VALIONA_FLEE);
                DoCast(SPELL_TWILIGHT_SHIFT);
                me->AttackStop();
                me->CastStop();
                me->SetReactState(REACT_PASSIVE);
                events.Reset();
                me->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE);
                me->SetHover(true);
                me->SetDisableGravity(true);
                Position pos;
                pos.Relocate(me);
                pos.m_positionZ += 12.0f;
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                if (Creature* drahga = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_DRAHGA_SHADOWBURNER)))
                {
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, drahga);
                    drahga->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    drahga->SetReactState(REACT_AGGRESSIVE);
                    drahga->AI()->DoAction(ACTION_VALIONA_OFF);
                }
                _finished = true;
            }
        }

        void IsSummonedBy(Unit* /*summon*/)
        {
            me->SetHover(true);
            me->SetDisableGravity(true);
            me->SetSpeed(MOVE_FLIGHT, 4.5f);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_INTRO_1:
                        if (me->HasAura(SPELL_RIDE_VEHICLE))
                        {
                            Talk(SAY_VALIONA_AGGRO);
                            me->GetMotionMaster()->MovePoint(POINT_INTRO_1, ValionaPos1);
                        }
                        break;
                    case EVENT_MOVE_INTRO_2:
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_2, ValionaPos2);
                        break;
                    case EVENT_MOVE_LAND:
                        me->GetMotionMaster()->MoveLand(POINT_LAND, LandingPos);
                        break;
                    case EVENT_LANDED:
                        me->SetHover(false);
                        me->SetDisableGravity(false);
                        events.ScheduleEvent(EVENT_ATTACK, 800);
                        break;
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Creature* drahga = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_DRAHGA_SHADOWBURNER)))
                            drahga->AI()->DoAction(ACTION_SCHEDULE_EVENTS);
                        events.ScheduleEvent(EVENT_SHREDDING_SWIPE, 1500);
                        if (IsHeroic())
                            events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 15500);
                        break;
                    case EVENT_SHREDDING_SWIPE:
                        DoCastVictim(SPELL_SHREDDING_SWIPE);
                        events.ScheduleEvent(EVENT_SHREDDING_SWIPE, 25000);
                        break;
                    case EVENT_DEVOURING_FLAMES:
                        DoCast(SPELL_DEVOURING_FLAMES_AOE);
                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES_CAST, 400);
                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 25000);
                        break;
                    case EVENT_DEVOURING_FLAMES_CAST:
                        if (Creature* dummy = me->FindNearestCreature(NPC_DEVOURING_FLAMES, 500.0f, true))
                        {
                            Talk(SAY_ANNOUNCE_DEVOURING_FLAMES);
                            me->SetFacingToObject(dummy);
                            me->AddUnitState(UNIT_STATE_CANNOT_TURN);
                            DoCast(SPELL_DEVOURING_FLAMES);
                            events.ScheduleEvent(EVENT_CLEAR_CAST, 5100);
                        }
                        break;
                    case EVENT_CLEAR_CAST:
                        me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
                        break;
                    case EVENT_MOVE_OUT:
                        me->GetMotionMaster()->MovePoint(POINT_FLEE, FleePos);
                        break;
                    case EVENT_DESPAWN:
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                        me->DespawnOrUnsummon(100);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_DESPAWN:
                    summons.DespawnAll();
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    me->DespawnOrUnsummon(100);
                    break;
                default:
                    break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_valionaAI (creature);
    }
};

class npc_gb_invoked_flaming_spirit : public CreatureScript
{
public:
    npc_gb_invoked_flaming_spirit() : CreatureScript("npc_gb_invoked_flaming_spirit") { }

    struct npc_gb_invoked_flaming_spiritAI : public ScriptedAI
    {
        npc_gb_invoked_flaming_spiritAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(5000);
        }

        void IsSummonedBy(Unit* summoner)
        {
            DoCast(SPELL_INVOKED_FLAME);
            me->SetInCombatWithZone();

            std::list<Player*> playerList = me->GetNearestPlayersList(500.0f, true);
            if (playerList.empty())
                return;

            if (player = Trinity::Containers::SelectRandomContainerElement(playerList))
            {
                me->CastSpell(player, SPELL_FLAMING_FIXATE, false);
                events.ScheduleEvent(EVENT_FOLLOW_PLAYER, 100);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FOLLOW_PLAYER:
                        me->ClearUnitState(UNIT_STATE_CASTING);
                        me->GetMotionMaster()->MoveChase(player);
                        me->Attack(player, true);
                        events.ScheduleEvent(EVENT_FOLLOW_PLAYER, 1000);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        protected:
            Unit* player;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_invoked_flaming_spiritAI (creature);
    }
};

class spell_gb_burning_shadowbolt : public SpellScriptLoader
{
public:
    spell_gb_burning_shadowbolt() : SpellScriptLoader("spell_gb_burning_shadowbolt") { }

    class spell_gb_burning_shadowbolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_burning_shadowbolt_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
            if (Unit* target = Trinity::Containers::SelectRandomContainerElement(targets)->ToUnit()) // A bit cheaty but ok for now
                GetCaster()->CastSpell(target, SPELL_BURNING_SHADOWBOLT_DUMMY, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_burning_shadowbolt_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_burning_shadowbolt_SpellScript();
    }
};

class spell_gb_supernova : public SpellScriptLoader
{
public:
    spell_gb_supernova() : SpellScriptLoader("spell_gb_supernova") { }

    class spell_gb_supernova_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_supernova_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_QUIETE_SUICIDE, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gb_supernova_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_supernova_SpellScript();
    }
};

class spell_gb_devouring_flames_aoe : public SpellScriptLoader
{
public:
    spell_gb_devouring_flames_aoe() : SpellScriptLoader("spell_gb_devouring_flames_aoe") { }

    class spell_gb_devouring_flames_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_devouring_flames_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }


        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_devouring_flames_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_devouring_flames_aoe_SpellScript();
    }
};

class spell_gb_devouring_flames : public SpellScriptLoader
{
    public:
        spell_gb_devouring_flames() :  SpellScriptLoader("spell_gb_devouring_flames") { }

        class spell_gb_devouring_flames_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gb_devouring_flames_AuraScript);

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                if (Creature* valiona = GetOwner()->FindNearestCreature(NPC_VALIONA, 500.0f, true))
                    if (valiona->GetReactState() != REACT_PASSIVE)
                        valiona->CastSpell(GetOwner()->ToUnit(), GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_gb_devouring_flames_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gb_devouring_flames_AuraScript();
        }
};

void AddSC_boss_drahga_shadowburner()
{
    new boss_drahga_shadowburner();
    new npc_gb_valiona();
    new npc_gb_invoked_flaming_spirit();
    new spell_gb_burning_shadowbolt();
    new spell_gb_supernova();
    new spell_gb_devouring_flames_aoe();
    new spell_gb_devouring_flames();
}
