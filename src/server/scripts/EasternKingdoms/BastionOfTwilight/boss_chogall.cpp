
#include "bastion_of_twilight.h"
#include "Vehicle.h"

enum Texts
{
    SAY_INTRO               = 7,
    SAY_AGGRO               = 8,
    SAY_CONVERSION          = 9,
    SAY_ADHERENT            = 10,
    SAY_OLDGOD              = 11,
    SAY_DARKENED            = 12,
    SAY_KILL                = 13,
    SAY_WIPE                = 14,
    SAY_DEATH               = 15,

    // Special
    SAY_CONVERSION_SPECIAL  = 16,
    SAY_ADHERENT_SPECIAL    = 17
};

enum Spells
{
    // Cho'Gall
    SPELL_SIT_THRONE            = 88648,
    SPELL_BOSS_HITTIN_YA        = 73878,
    SPELL_CORRUPTED_BLOOD       = 93104,
    SPELL_CORRUPTED_BLOOD_BAR   = 93103,
    SPELL_FLAMES_ORDERS         = 81171,
    SPELL_SHADOWS_ORDERS        = 87575,
    SPELL_ABSORB_FIRE           = 81196,
    SPELL_ABSORB_SHADOW         = 81566,
    SPELL_CONVERSION            = 91303,
    SPELL_BLAZE                 = 81536,
    SPELL_RIDE_VEHICLE          = 43671,
    SPELL_FLAMING_DESTRUCTION   = 81194,
    SPELL_EMPOWERED_SHADOWS     = 81572,
    SPELL_SUMMON_ADHERENT_T     = 81628,
    SPELL_SUMMON_ADHERENT_L     = 81611,
    SPELL_SUMMON_ADHERENT_R     = 81618,
    SPELL_BERSERK               = 47008,
    SPELL_FURY_OF_CHOGALL       = 82524,
    SPELL_WORSHIPPING           = 91317
};

enum Phases
{
    PHASE_NULL  = 0,
    PHASE_ONE,
    PHASE_TWO
};

enum Events
{
    EVENT_FLAMES_ORDERS      = 1,
    EVENT_SHADOWS_ORDERS,
    EVENT_FURY_OF_CHOGALL,
    EVENT_SUMMON_ADHERENT,
    EVENT_FESTER_BLOOD,
    EVENT_FIRE_POWER,
    EVENT_SHADOW_POWER,
    EVENT_FLAMING_DESTRUCTION,
    EVENT_EMPOWERED_SHADOWS,
    EVENT_CONVERSION,
    EVENT_UNROOT_CHOGALL,
    EVENT_BERSERK
};

enum Actions
{
    ACTION_TALK_INTRO   = 1,
    ACTION_FIRE_POWER,
    ACTION_SHADOW_POWER
};

enum npcId
{
    NPC_FIRE_LORD               = 47017,
    NPC_SHADOW_LORD             = 47016,
    NPC_CORRUPTED_ADHERENT      = 43622,
    NPC_BLOOD_OF_THE_OLD_GOD    = 43707
};

enum portalEvents
{
    EVENT_SUMMON_FLAME_LORD     = 1,
    EVENT_SUMMON_SHADOW_LORD
};

enum portalSpells
{
    SPELL_FIRE_PORTAL_VISUAL    = 81172,
    SPELL_SUMMON_FLAME_LORD     = 87582,
    SPELL_SHADOW_PORTAL_VISUAL  = 81559,
    SPELL_SUMMON_SHADOW_LORD    = 87583
};

enum adherentEvents
{
    EVENT_DEPRAVITY         = 1,
    EVENT_CORRUPTING_CRASH
};

enum adherentSpells
{
    SPELL_SELF_ROOT         = 42716,
    SPELL_DEPRAVITY         = 81713,
    SPELL_CORRUPT_CRASH     = 81685,
    SPELL_SPILLED_VISUAL    = 81771,
    SPELL_SPILLED_POOL      = 81757
};

enum eventsPhaseTwo
{
    EVENT_DEBILITATING_BEAM             = 1,
    EVENT_MELEE_INCREASE_CORRUPTION,
    EVENT_FIXATE
};

enum darkenedCreationSpells
{
    SPELL_DEBILITATING_BEAM     = 82411,
    SPELL_TENTACLE_VISUAL       = 82451
};

enum malformationSpells
{
    SPELL_MALFORMATION_SHADOWBOLT   = 85544
};

enum malformationEvents
{
    EVENT_MALFORMATION_SHADOWBOLT   = 1
};

enum spellSpecials
{
    SPELL_FESTER_BLOOD      = 82299, // Cast by boss -> after 3 sec 82337 with script eff for Festered Blood (82333) which summons Blood of the Old God oozes - npc 43707 (from dead adh).
    SPELL_FESTERING_BLOOD   = 82914, // Living adherents use this - damage spell, triggers 82919 which is actual damage spell needs radius and script eff for applying corruption.
};

class at_chogall_intro : public AreaTriggerScript
{
public:
    at_chogall_intro() : AreaTriggerScript("at_chogall_intro") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* controller = player->FindNearestCreature(BOSS_CHOGALL, 500.0f, true))
            controller->AI()->DoAction(ACTION_TALK_INTRO);
        return true;
    }
};

class boss_chogall : public CreatureScript
{
public:
    boss_chogall() : CreatureScript("boss_chogall") { }

    struct boss_chogallAI: public BossAI
    {
        boss_chogallAI(Creature* creature) : BossAI(creature, DATA_CHOGALL)
        {
            _introDone = false;
        }

        bool _introDone;

        void Reset()
        {
            _Reset();
            DoCast(me, SPELL_SIT_THRONE, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->RemoveAurasDueToSpell(SPELL_SIT_THRONE);
            DoCast(me, SPELL_CORRUPTED_BLOOD);
            DoCast(SPELL_BOSS_HITTIN_YA); // Dunno what's it, but is from sniffs... need more research
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_FLAMES_ORDERS, 5000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_CONVERSION, 10000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_SHADOWS_ORDERS, 15000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_SUMMON_ADHERENT, 68000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_FURY_OF_CHOGALL, 21000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_FESTER_BLOOD, 108000, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_BERSERK, 600000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            if (me->isAlive())
                Talk(SAY_WIPE);
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SetBossState(DATA_CHOGALL, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_BLOOD_BAR);
            me->DespawnCreaturesInArea(NPC_BLAZE);
            me->DespawnCreaturesInArea(NPC_FIRE_PORTAL);
            me->DespawnCreaturesInArea(NPC_SHADOW_PORTAL);
            me->DespawnCreaturesInArea(NPC_FIRE_LORD);
            me->DespawnCreaturesInArea(NPC_SHADOW_LORD);
            me->DespawnCreaturesInArea(NPC_CORRUPTED_ADHERENT);
            summons.DespawnAll();
            events.Reset();
            _DespawnAtEvade();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            events.Reset();
            instance->SetBossState(DATA_CHOGALL, DONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTED_BLOOD_BAR);
        }

        void JustRespawned()
        {
            Reset();
        }

        void JustSummoned(Creature* summon)
        {
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_KILL);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TALK_INTRO:
                    if (!_introDone)
                    {
                        TalkToMap(SAY_INTRO);
                        _introDone = true;
                    }
                    break;
                case ACTION_FIRE_POWER:
                    events.ScheduleEvent(EVENT_FIRE_POWER, 2000, 0, PHASE_ONE);
                    break;
                case ACTION_SHADOW_POWER:
                    events.ScheduleEvent(EVENT_SHADOW_POWER, 2000, 0, PHASE_ONE);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                std::list<Unit*> targets;

                switch (eventId)
                {
                    case EVENT_FLAMES_ORDERS:
                        me->StopMoving();
                        DoCast(SPELL_FLAMES_ORDERS);
                        events.RescheduleEvent(EVENT_FLAMES_ORDERS, 50000, 0, PHASE_ONE);
                        break;
                    case EVENT_SHADOWS_ORDERS:
                        me->StopMoving();
                        DoCast(SPELL_SHADOWS_ORDERS);
                        events.RescheduleEvent(EVENT_SHADOWS_ORDERS, 50000, 0, PHASE_ONE);
                        break;
                    case EVENT_FIRE_POWER:
                        if (Creature* fireLord = me->FindNearestCreature(NPC_FIRE_LORD, 500.0f))
                        {
                            fireLord->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                            fireLord->SetObjectScale(0.1f);
                            fireLord->DespawnOrUnsummon(2500);
                            events.ScheduleEvent(EVENT_FLAMING_DESTRUCTION, 1500, 0, PHASE_ONE);
                        }
                        break;
                    case EVENT_SHADOW_POWER:
                        if (Creature* shadowLord = me->FindNearestCreature(NPC_SHADOW_LORD, 500.0f))
                        {
                            shadowLord->CastSpell(me, SPELL_RIDE_VEHICLE, true);
                            shadowLord->SetObjectScale(0.1f);
                            shadowLord->DespawnOrUnsummon(2500);
                            events.ScheduleEvent(EVENT_EMPOWERED_SHADOWS, 1500, 0, PHASE_ONE);
                        }
                        break;
                    case EVENT_FLAMING_DESTRUCTION:
                        DoCast(me, SPELL_FLAMING_DESTRUCTION, true);
                        break;
                    case EVENT_EMPOWERED_SHADOWS:
                        DoCast(me, SPELL_EMPOWERED_SHADOWS, true);
                        break;
                    case EVENT_CONVERSION:
                        SelectTargetList(targets, NonTankTargetSelector(me), RAID_MODE(1, 2, 2, 4), SELECT_TARGET_RANDOM);
                        if (!targets.empty())
                        {
                            Talk(SAY_CONVERSION_SPECIAL);
                            for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                (*itr)->CastSpell(me, SPELL_WORSHIPPING, true);
                            Talk(SAY_CONVERSION);
                        }
                        events.ScheduleEvent(EVENT_CONVERSION, urand(30000, 35000), PHASE_ONE);
                        break;
                    case EVENT_SUMMON_ADHERENT:
                        me->StopMoving();
                        Talk(SAY_ADHERENT_SPECIAL);
                        me->SetControlled(true, UNIT_STATE_ROOT);
                        DoCast(SPELL_SUMMON_ADHERENT_T);
                        Talk(SAY_ADHERENT);
                        events.ScheduleEvent(EVENT_UNROOT_CHOGALL, 1800, 0, PHASE_ONE);
                        events.RescheduleEvent(EVENT_SUMMON_ADHERENT, 90000, 0, PHASE_ONE);
                        break;
                    case EVENT_UNROOT_CHOGALL:
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        break;
                    case EVENT_BERSERK:
                        DoCast(SPELL_BERSERK);
                        break;
                    case EVENT_FURY_OF_CHOGALL:
                        if (Unit* target = me->getVictim())
                            DoCast(target, SPELL_FURY_OF_CHOGALL);
                        events.ScheduleEvent(EVENT_FURY_OF_CHOGALL, urand(45000, 49000), PHASE_ONE);
                        break;
                    case EVENT_FESTER_BLOOD:
                        me->StopMoving();
                        DoCast(me, SPELL_FESTER_BLOOD);
                        events.ScheduleEvent(EVENT_FESTER_BLOOD, 130000, PHASE_ONE);
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
        return new boss_chogallAI(creature);
    }
};

class npc_bot_fire_portal : public CreatureScript
{
public:
    npc_bot_fire_portal() : CreatureScript("npc_bot_fire_portal") {}

    struct npc_bot_fire_portalAI : public ScriptedAI
    {
        npc_bot_fire_portalAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            DoCast(SPELL_FIRE_PORTAL_VISUAL);
        }

        InstanceScript* instance;
        EventMap events;

        void JustSummoned(Creature* creature)
        {
            if (creature->GetEntry() == NPC_FIRE_LORD)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->AddAura(SPELL_ABSORB_FIRE, creature);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetReactState(REACT_PASSIVE);
                if (Creature* chogall = creature->FindNearestCreature(BOSS_CHOGALL, 500.0f))
                    chogall->AI()->DoAction(ACTION_FIRE_POWER);
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_FLAME_LORD, 5500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_FLAME_LORD:
                    {
                        DoCast(me, SPELL_SUMMON_FLAME_LORD);
                        me->DespawnOrUnsummon(5000);
                        return;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_fire_portalAI(creature);
    }
};

class npc_bot_shadow_portal : public CreatureScript
{
public:
    npc_bot_shadow_portal() : CreatureScript("npc_bot_shadow_portal") {}

    struct npc_bot_shadow_portalAI : public ScriptedAI
    {
        npc_bot_shadow_portalAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            DoCast(SPELL_SHADOW_PORTAL_VISUAL);
        }

        InstanceScript* instance;
        EventMap events;

        void JustSummoned(Creature* creature)
        {
            if (creature->GetEntry() == NPC_SHADOW_LORD)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->AddAura(SPELL_ABSORB_SHADOW, creature);
                creature->SetReactState(REACT_PASSIVE);
                if (Creature* chogall = creature->FindNearestCreature(BOSS_CHOGALL, 500.0f))
                    chogall->AI()->DoAction(ACTION_SHADOW_POWER);
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_SHADOW_LORD, 5500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_SHADOW_LORD:
                    {
                        DoCast(me, SPELL_SUMMON_SHADOW_LORD);
                        me->DespawnOrUnsummon(5000);
                        return;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_shadow_portalAI(creature);
    }
};

class npc_bot_blaze : public CreatureScript
{
public:
    npc_bot_blaze() : CreatureScript("npc_bot_blaze") {}

    struct npc_bot_blazeAI : public ScriptedAI
    {

        npc_bot_blazeAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->AddAura(SPELL_BLAZE, me);
            me->DespawnOrUnsummon(25000);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_blazeAI(creature);
    }
};

class spell_bot_conversion : public SpellScriptLoader
{
public:
    spell_bot_conversion() : SpellScriptLoader("spell_bot_conversion")
    {
    }

    class spell_bot_conversion_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_conversion_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 2);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_bot_conversion_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bot_conversion_SpellScript();
    }
};

class spell_bot_summon_corrupted_adherent : public SpellScriptLoader
{
public:
    spell_bot_summon_corrupted_adherent() : SpellScriptLoader("spell_bot_summon_corrupted_adherent") { }

    class spell_bot_summon_corrupted_adherent_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_summon_corrupted_adherent_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetMap()->IsHeroic() && caster->GetMap()->Is25ManRaid())
                {
                    caster->CastSpell(caster, SPELL_SUMMON_ADHERENT_L, true);
                    caster->CastSpell(caster, SPELL_SUMMON_ADHERENT_R, true);
                }
                else
                {
                    uint8 selectPosition = urand(1, 2);
                    switch (selectPosition)
                    {
                        case 1:
                            caster->CastSpell(caster, SPELL_SUMMON_ADHERENT_L, true);
                            break;
                        case 2:
                            caster->CastSpell(caster, SPELL_SUMMON_ADHERENT_R, true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_summon_corrupted_adherent_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bot_summon_corrupted_adherent_SpellScript();
    }
};

class npc_bot_corrupting_adherent : public CreatureScript
{
public:
    npc_bot_corrupting_adherent() : CreatureScript("npc_bot_corrupting_adherent") {}

    struct npc_bot_corrupting_adherentAI : public ScriptedAI
    {
        npc_bot_corrupting_adherentAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            deathVisual = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool deathVisual;

        void IsSummonedBy(Unit* /*owner*/)
        {
            events.ScheduleEvent(EVENT_DEPRAVITY, urand(3000, 9000));
            events.ScheduleEvent(EVENT_CORRUPTING_CRASH, urand(11000, 17000));
            if (Player* player = me->FindNearestPlayer(500.0f))
                AttackStart(player);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HealthBelowPct(6) && !deathVisual)
            {
                me->RemoveAllAuras();
                DoCast(me, SPELL_SPILLED_VISUAL, true);
                DoCast(me, SPELL_SPILLED_POOL, true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DEAD);
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_DEAD);
                me->SetReactState(REACT_PASSIVE);
                me->SetControlled(true, UNIT_STATE_ROOT);
                deathVisual = true;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING) || deathVisual)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEPRAVITY:
                        DoCast(me, SPELL_DEPRAVITY);
                        events.ScheduleEvent(EVENT_DEPRAVITY, (Is25ManRaid() ? 12000 : 6000));
                        break;
                    case EVENT_CORRUPTING_CRASH:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_CORRUPT_CRASH);
                        events.ScheduleEvent(EVENT_CORRUPTING_CRASH, urand(9500, 16500));
                        break;
                    default:
                        break;
                }
            }

            if (!deathVisual)
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_corrupting_adherentAI(creature);
    }
};

class npc_bot_darkened_creation : public CreatureScript
{
public:
    npc_bot_darkened_creation() : CreatureScript("npc_bot_darkened_creation") {}

    struct npc_bot_darkened_creationAI : public ScriptedAI
    {
        npc_bot_darkened_creationAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->CastSpell(creature, SPELL_TENTACLE_VISUAL, true);
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*owner*/)
        {
            events.ScheduleEvent(EVENT_DEBILITATING_BEAM, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEBILITATING_BEAM:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_DEBILITATING_BEAM);
                        events.ScheduleEvent(EVENT_DEBILITATING_BEAM, 10500);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_darkened_creationAI(creature);
    }
};

class npc_bot_blood_old_god : public CreatureScript
{
public:
    npc_bot_blood_old_god() : CreatureScript("npc_bot_blood_old_god") {}

    struct npc_bot_blood_old_godAI : public ScriptedAI
    {
        npc_bot_blood_old_godAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*owner*/)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                AttackStart(target);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FIXATE, 100);
            events.ScheduleEvent(EVENT_MELEE_INCREASE_CORRUPTION, 2100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FIXATE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {
                            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                            me->SetSpeed(MOVE_WALK, 0.55f, true);
                            me->SetSpeed(MOVE_RUN, 0.55f, true);
                            AttackStart(target);
                            me->AddThreat(target, 5000000.0f);
                        }
                        break;
                    }
                    case EVENT_MELEE_INCREASE_CORRUPTION:
                    {
                        if (Unit* target = me->getVictim())
                            if (me->IsWithinMeleeRange(target))
                                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 10);
                        events.ScheduleEvent(EVENT_MELEE_INCREASE_CORRUPTION, 2000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_blood_old_godAI(creature);
    }
};

class spell_bot_fester_blood : public SpellScriptLoader
{
public:
    spell_bot_fester_blood() : SpellScriptLoader("spell_bot_fester_blood") { }

    class spell_bot_fester_blood_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_fester_blood_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                std::list<Creature*> adherents;
                caster->GetCreatureListWithEntryInGrid(adherents, NPC_CORRUPTED_ADHERENT, 300.0f);
                for (std::list<Creature*>::iterator itr = adherents.begin(); itr != adherents.end(); ++itr)
                {
                    if (!(*itr)->HealthBelowPct(6))
                        (*itr)->CastSpell(*itr, SPELL_FESTERING_BLOOD, true);
                    else
                    {
                        for (int8 i = 0; i < 5; i++)
                            (*itr)->SummonCreature(NPC_BLOOD_OF_THE_OLD_GOD, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), (*itr)->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_fester_blood_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_fester_blood_SpellScript();
    }
};

class spell_bot_depravity : public SpellScriptLoader
{
public:
    spell_bot_depravity() : SpellScriptLoader("spell_bot_depravity") { }

    class spell_bot_depravity_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_depravity_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 10);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_depravity_SpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_depravity_SpellScript();
    }
};

class spell_bot_corrupting_crash : public SpellScriptLoader
{
public:
    spell_bot_corrupting_crash() : SpellScriptLoader("spell_corrupting_crash") { }

    class spell_bot_corrupting_crash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_corrupting_crash_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 10);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_corrupting_crash_SpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_corrupting_crash_SpellScript();
    }
};

class spell_bot_sprayed_corruption : public SpellScriptLoader
{
public:
    spell_bot_sprayed_corruption() : SpellScriptLoader("spell_bot_sprayed_corruption") { }

    class spell_bot_sprayed_corruption_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_sprayed_corruption_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 5);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_sprayed_corruption_SpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_sprayed_corruption_SpellScript();
    }
};

class spell_bot_spilled_blood_of_the_old_god : public SpellScriptLoader
{
public:
    spell_bot_spilled_blood_of_the_old_god() : SpellScriptLoader("spell_bot_spilled_blood_of_the_old_god") { }

    class spell_bot_spilled_blood_of_the_old_god_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_spilled_blood_of_the_old_god_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 5);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_spilled_blood_of_the_old_god_SpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_spilled_blood_of_the_old_god_SpellScript();
    }
};

class spell_bot_debilitating_beam : public SpellScriptLoader
{
public:
    spell_bot_debilitating_beam() : SpellScriptLoader("spell_bot_debilitating_beam") { }

    class spell_bot_debilitating_beam_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_bot_debilitating_beam_AuraScript);

        void PeriodicTick(AuraEffect const* /*aurEff*/)
        {
            if (Unit* target = GetTarget())
                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 2);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_bot_debilitating_beam_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_bot_debilitating_beam_AuraScript();
    }
};

class spell_bot_corruption_old_god : public SpellScriptLoader
{
public:
    spell_bot_corruption_old_god() : SpellScriptLoader("spell_bot_corruption_old_god") { }

    class spell_bot_corruption_old_god_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_corruption_old_god_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (target->GetPower(POWER_ALTERNATE_POWER) > 0)
                    SetHitDamage(int32(GetHitDamage() + (((GetHitDamage() / 100) * 3) * target->GetPower(POWER_ALTERNATE_POWER))));
        }

        void EffectScriptEffect(SpellEffIndex effIndex)
        {
            if (Unit* target = GetHitUnit())
                target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 1);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_corruption_old_god_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_bot_corruption_old_god_SpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_corruption_old_god_SpellScript();
    }
};

class spell_bot_corruption_accelerated : public SpellScriptLoader
{
public:
    spell_bot_corruption_accelerated() : SpellScriptLoader("spell_bot_corruption_accelerated") { }

    class spell_bot_corruption_accelerated_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_corruption_accelerated_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                caster->SetPower(POWER_ALTERNATE_POWER, caster->GetPower(POWER_ALTERNATE_POWER) + 2);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_corruption_accelerated_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_corruption_accelerated_SpellScript();
    }
};

class spell_bot_corruption_sickness : public SpellScriptLoader
{
public:
    spell_bot_corruption_sickness() : SpellScriptLoader("spell_bot_corruption_sickness") { }

    class spell_bot_corruption_sickness_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_corruption_sickness_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;
            return true;
        }

        bool Load()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                caster->SetPower(POWER_ALTERNATE_POWER, caster->GetPower(POWER_ALTERNATE_POWER) + 5);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_bot_corruption_sickness_SpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_bot_corruption_sickness_SpellScript();
    }
};

class npc_bot_malformation_chogall : public CreatureScript
{
public:
    npc_bot_malformation_chogall() : CreatureScript("npc_bot_malformation_chogall") {}

    struct npc_bot_malformation_chogallAI : public ScriptedAI
    {
        npc_bot_malformation_chogallAI(Creature * creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            events.ScheduleEvent(EVENT_MALFORMATION_SHADOWBOLT, 3000);
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MALFORMATION_SHADOWBOLT:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_MALFORMATION_SHADOWBOLT);
                        events.ScheduleEvent(EVENT_MALFORMATION_SHADOWBOLT, urand(7000, 14000));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_malformation_chogallAI(creature);
    }
};

void AddSC_boss_chogall()
{
    new at_chogall_intro();
    new boss_chogall();
    new npc_bot_fire_portal();
    new npc_bot_shadow_portal();
    new npc_bot_blaze();
    new spell_bot_conversion();
    new spell_bot_summon_corrupted_adherent();
    new npc_bot_corrupting_adherent();
    new npc_bot_darkened_creation();
    new npc_bot_blood_old_god();
    new spell_bot_fester_blood();
    new spell_bot_depravity();
    new spell_bot_corrupting_crash();
    new spell_bot_sprayed_corruption();
    new spell_bot_spilled_blood_of_the_old_god();
    new spell_bot_debilitating_beam();
    new spell_bot_corruption_old_god();
    new spell_bot_corruption_accelerated();
    new spell_bot_corruption_sickness();
    new npc_bot_malformation_chogall();
}
