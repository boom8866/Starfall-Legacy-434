
#include "ScriptPCH.h"
#include "grim_batol.h"

enum Spells
{
    SPELL_MIGHTY_STOMP                  = 74984,
    SPELL_CAVE_IN                       = 74987,
    SPELL_CAVE_IN_AURA                  = 74990,

    SPELL_PICK_WEAPON                   = 75000,
    SPELL_KNOCK_BACK                    = 88504,
    SPELL_BURNING_DUAL_BLADES           = 74981,

    // Shield Phase
    SPELL_PERSONAL_PHALANX              = 74908,
    SPELL_SHIELD_VISUAL                 = 94588,
    SPELL_FLAMING_SHIELD                = 90819,

    SPELL_PERSONAL_PHALANX_FIXATE_AOE   = 74914,
    SPELL_FIXATE_EFFECT                 = 75071, // Target Fixate Dummy
    SPELL_FLAME_ARROWS_TRIGGER          = 74946,
    

    // Swords Phase
    SPELL_DUAL_BLADES_BUFF              = 74981,
    SPELL_TRASH                         = 47480,
    SPELL_DISORIENTING_ROAR             = 74976,
    SPELL_BURNING_FLAMES                = 90764,

    // Mace Phase
    SPELL_ENCUMBERED                    = 75007,
    SPELL_IMPALING_SLAM                 = 75056,
    SPELL_LAVA_PATCH                    = 90754,
    SPELL_LAVA_PATCH_VISUAL             = 90752,
};

enum Events
{
    // General
    EVENT_PICK_WEAPON = 1,
    EVENT_MIGHTY_STOMP,

    EVENT_PERSONAL_PHALANX,
    EVENT_CLEAR_FACING,
    EVENT_CLEAR_PHALANX,
};

enum Action
{
    ACTION_CHOOSE_MACE = 1,
    ACTION_CHOOSE_SHIELD,
    ACTION_CHOOSE_BLADES,
};

enum Texts
{
    SAY_AGGRO           = 0,
    SAY_SLAY            = 1,
    SAY_SHIELD_ANNOUNCE = 2,
    SAY_SHIELD          = 3,
    SAY_MACE_ANNOUNCE   = 4,
    SAY_MACE            = 5,
    SAY_BLADES_ANNOUNCE = 6,
    SAY_BLADES          = 7,
    SAY_IMPALE          = 8,
    SAY_DEATH           = 9,
};

enum Equipment
{
    EQUIPMENT_ID_SWORD  = 64435,
    EQUIPMENT_ID_MACE   = 49737,
};

class boss_forgemaster_throngus: public CreatureScript
{
public:
    boss_forgemaster_throngus() : CreatureScript("boss_forgemaster_throngus") { }

    struct boss_forgemaster_throngusAI : public BossAI
    {
        boss_forgemaster_throngusAI(Creature* creature) : BossAI(creature, DATA_FORGEMASTER_THRONGUS)
        {
            _mace = false;
            _shield = false;
            _blades = false;
        }

        bool _mace;
        bool _shield;
        bool _blades;

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_MIGHTY_STOMP, 6500);
            events.ScheduleEvent(EVENT_PICK_WEAPON, 10000);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            summons.DespawnAll();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            _mace = false;
            _shield = false;
            _blades = false;
            SetEquipmentSlots(false, 0, 0, 0);
            _DespawnAtEvade();
        }

        void Reset()
        {
            _Reset();
            _mace = false;
            _shield = false;
            _blades = false;
            SetEquipmentSlots(false, 0, 0, 0);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_CAVE_IN_STALKER:
                case NPC_FIXATE_TRIGGER:
                    summons.Summon(summon);
                    break;
                default:
                    break;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CHOOSE_BLADES:
                    //Talk(SAY_BLADES);
                    //Talk(SAY_BLADES_ANNOUNCE);
                    //DoCast(SPELL_BURNING_DUAL_BLADES);
                    //break;
                case ACTION_CHOOSE_MACE:
                    //Talk(SAY_MACE);
                    //Talk(SAY_MACE_ANNOUNCE);
                    //break;
                case ACTION_CHOOSE_SHIELD:
                    me->GetMotionMaster()->Clear();
                    DoCast(SPELL_SHIELD_VISUAL);
                    me->AddAura(SPELL_PERSONAL_PHALANX, me);
                    me->AddAura(SPELL_FLAME_ARROWS_TRIGGER, me);
                    if (IsHeroic())
                        me->CastWithDelay(1200, me, SPELL_FLAMING_SHIELD); // According to sniffs. Dunno what's wrong with Blizz
                    events.ScheduleEvent(EVENT_PERSONAL_PHALANX, 1200);
                    events.ScheduleEvent(EVENT_CLEAR_PHALANX, 30100);
                    Talk(SAY_SHIELD);
                    Talk(SAY_SHIELD_ANNOUNCE);
                    break;
                case EVENT_CLEAR_PHALANX:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED | UNIT_FLAG_PACIFIED);
                    me->RemoveAurasDueToSpell(SPELL_FIXATE_EFFECT);
                    me->RemoveAurasDueToSpell(SPELL_FLAMING_SHIELD);
                    events.CancelEvent(EVENT_PERSONAL_PHALANX);
                    events.CancelEvent(EVENT_CLEAR_FACING);
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
                switch(eventId)
                {
                    case EVENT_MIGHTY_STOMP:
                        DoCastAOE(SPELL_MIGHTY_STOMP);
                        events.ScheduleEvent(EVENT_MIGHTY_STOMP, 49500);
                        break;
                    case EVENT_PICK_WEAPON:
                        DoCastAOE(SPELL_PICK_WEAPON);
                        break;
                    case EVENT_PERSONAL_PHALANX:
                        DoCast(SPELL_PERSONAL_PHALANX_FIXATE_AOE);
                        events.ScheduleEvent(EVENT_PERSONAL_PHALANX, 8550);
                        events.ScheduleEvent(EVENT_CLEAR_FACING, 8400);
                        break;
                    case EVENT_CLEAR_FACING:
                        me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
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
        return new boss_forgemaster_throngusAI (creature);
    }
};

class npc_gb_cave_in : public CreatureScript
{
    public:
        npc_gb_cave_in() : CreatureScript("npc_gb_cave_in") { }

        struct npc_gb_cave_inAI : public ScriptedAI
        {
            npc_gb_cave_inAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->DespawnOrUnsummon(8450);
                DoCastAOE(SPELL_CAVE_IN);
                me->AddAura(SPELL_CAVE_IN_AURA, me);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_cave_inAI(creature);
    }
};

class npc_gb_fixate_trigger : public CreatureScript
{
    public:
        npc_gb_fixate_trigger() : CreatureScript("npc_gb_fixate_trigger") { }

        struct npc_gb_fixate_triggerAI : public ScriptedAI
        {
            npc_gb_fixate_triggerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->DespawnOrUnsummon(8450);
                summoner->ToCreature()->AI()->DoCast(SPELL_FIXATE_EFFECT);
                summoner->SetFacingToObject(me);
                summoner->AddUnitState(UNIT_STATE_CANNOT_TURN);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_fixate_triggerAI(creature);
    }
};

class spell_gb_pick_weapon : public SpellScriptLoader
{
public:
    spell_gb_pick_weapon() : SpellScriptLoader("spell_gb_pick_weapon") { }

    class spell_gb_pick_weapon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_pick_weapon_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                switch (urand(0, 2))
                {
                    case 0: // Mace
                        caster->ToCreature()->AI()->DoAction(ACTION_CHOOSE_MACE);
                        break;
                    case 1: // Shield
                        caster->ToCreature()->AI()->DoAction(ACTION_CHOOSE_SHIELD);
                        break;
                    case 2: // Blades
                        caster->ToCreature()->AI()->DoAction(ACTION_CHOOSE_BLADES);
                        break;
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gb_pick_weapon_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_pick_weapon_SpellScript();
    }
};

class spell_gb_mighty_stomp : public SpellScriptLoader
{
public:
    spell_gb_mighty_stomp() : SpellScriptLoader("spell_gb_mighty_stomp") { }

    class spell_gb_mighty_stomp_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_mighty_stomp_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void HandleHit(SpellEffIndex effIndex)
        {
            PreventHitEffect(effIndex);
            if (Unit* target = GetHitUnit())
                GetCaster()->CastSpell(target, GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_mighty_stomp_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_gb_mighty_stomp_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_mighty_stomp_SpellScript();
    }
};

class spell_gb_fixate_trigger_aoe : public SpellScriptLoader
{
public:
    spell_gb_fixate_trigger_aoe() : SpellScriptLoader("spell_gb_fixate_trigger_aoe") { }

    class spell_gb_fixate_trigger_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_fixate_trigger_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void HandleHit(SpellEffIndex effIndex)
        {
            PreventHitEffect(effIndex);
            if (Unit* target = GetHitUnit())
                GetCaster()->CastSpell(target, GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_fixate_trigger_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_gb_fixate_trigger_aoe_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_fixate_trigger_aoe_SpellScript();
    }
};

class spell_gb_flame_arrows_aoe : public SpellScriptLoader
{
public:
    spell_gb_flame_arrows_aoe() : SpellScriptLoader("spell_gb_flame_arrows_aoe") { }

    class spell_gb_flame_arrows_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_flame_arrows_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 5);
        }

        void HandleHit(SpellEffIndex effIndex)
        {
            PreventHitEffect(effIndex);
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_flame_arrows_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_gb_flame_arrows_aoe_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_flame_arrows_aoe_SpellScript();
    }
};

class spell_gb_flame_arrows : public SpellScriptLoader
{
public:
    spell_gb_flame_arrows() : SpellScriptLoader("spell_gb_flame_arrows") { }

    class spell_gb_flame_arrows_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_flame_arrows_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }
        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_flame_arrows_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_flame_arrows_SpellScript();
    }
};

void AddSC_boss_forgemaster_throngus()
{
    new boss_forgemaster_throngus();
    new npc_gb_cave_in();
    new npc_gb_fixate_trigger();
    new spell_gb_pick_weapon();
    new spell_gb_mighty_stomp();
    new spell_gb_fixate_trigger_aoe();
    new spell_gb_flame_arrows_aoe();
    new spell_gb_flame_arrows();
}
