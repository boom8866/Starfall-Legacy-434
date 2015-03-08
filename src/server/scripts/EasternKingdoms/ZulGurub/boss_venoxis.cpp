
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "zulgurub.h"

enum Yells
{
    SAY_AGGRO               = 0,
    SAY_TRANSFORM           = 1,
    SAY_BLOODVENOM          = 2,
    SAY_ANNOUNCE_BLOODVENOM = 3,
    SAY_ANNOUNCE_EXHAUSTED  = 4,
    SAY_SLAY                = 5,
    SAY_DEATH               = 6,
};

enum Spells
{
    // Totems
    SPELL_VENOM_TOTEM_BEAM_LEFT     = 96536,
    SPELL_VENOM_TOTEM_BEAM_RIGHT    = 96537,
    SPELL_VENOM_TOTEM               = 96534,

    // Venoxis
    SPELL_WORD_OF_HETHISS           = 96560,
    SPELL_WHISPERS_OF_HETHIS        = 96466,

    SPELL_TOXIC_LINK                = 96475,
    SPELL_TOXIC_LINK_AURA           = 96477,
    SPELL_TOXIC_EXPLOSION           = 96489,

    SPELL_BLESSING_OF_THE_SNAKE_GOD = 96512,
    SPELL_POOL_OF_ACRID_TEARS       = 96515,
    SPELL_BREATH_OF_HETHISS         = 96509,
    SPELL_TRANSFORM_REMOVAL_PRIMER  = 96617,
    SPELL_BLOOD_VENOM               = 96842, // Resize to 3 target
    SPELL_VENOMOUS_WITHDRAWAL       = 96653,

    // Bloodvenom
    SPELL_BLOOD_VENOM_VISUAL        = 97110,
    SPELL_VENOM_TOTAM_BEAM_CENTER   = 97098,
    SPELL_BLOOD_VENOM_TRIGGER       = 97099,

    // Venomous Effusion Stalker
    SPELL_VENOMOUS_EFFUSION_TRIGGER = 96678,

    // Venomous Effusion
    SPELL_VENOMOUS_EFFUSION         = 96681,
};

enum Events
{
    // Venoxis
    EVENT_VENOMOUS_EFFUSION = 1,
    EVENT_RELEASE_TOTEMS,
    EVENT_WHISPERS_OF_HETHISS,
    EVENT_APPLY_IMMUNITY,
    EVENT_TOXIC_LINK,

    // Venomous Effusion
    EVENT_CAST_EFFUSION,
};

Position const totemStalkerPos[] =
{
    { -12021.8f, -1688.28f, 43.4524f, 0.558505f }, // Right Side
    { -12011.0f, -1705.97f, 43.4762f, 0.523599f }, // Left Side
};

Position const venomousEffusionStalkerPos[] =
{
    { -12013.51f, -1684.175f, 32.36689f, 2.490533f }, // Right Side
    { -12003.96f, -1698.644f, 32.36689f, 5.730771f }, // Left Side
};

class VictimCheck
{
public:
    VictimCheck(Unit* caster) : caster(caster) { }

    bool operator()(WorldObject* object)
    {
        return (caster->getVictim() == object->ToUnit());
    }
private:
    Unit* caster;
};

class NoToxicLinkAura
{
public:
    NoToxicLinkAura() { }

    bool operator()(WorldObject* object)
    {
        return (!object->ToUnit()->HasAura(SPELL_TOXIC_LINK_AURA));
    }
};

class boss_high_priest_venoxis : public CreatureScript
{
    public:
        boss_high_priest_venoxis() : CreatureScript("boss_high_priest_venoxis") { }

        struct boss_high_priest_venoxisAI : public BossAI
        {
            boss_high_priest_venoxisAI(Creature* creature) : BossAI(creature, DATA_VENOXIS) { }

            void Reset()
            {
                _Reset();
                SpawnTotems();
            }

            Creature* totem1;
            Creature* totem2;

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                Talk(SAY_AGGRO);
                me->HandleEmoteCommand(EMOTE_STATE_NONE);
                me->StopMoving();
                DoCast(me, SPELL_WORD_OF_HETHISS);
                events.ScheduleEvent(EVENT_RELEASE_TOTEMS, 2000);
                events.ScheduleEvent(EVENT_VENOMOUS_EFFUSION, 3000);
                events.ScheduleEvent(EVENT_WHISPERS_OF_HETHISS, 5000);
                events.ScheduleEvent(EVENT_TOXIC_LINK, 14500);
            }

            void EnterEvadeMode()
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->SetBossState(DATA_VENOXIS, FAIL);
                summons.DespawnAll();
                me->GetMotionMaster()->MoveTargetedHome();
                _EnterEvadeMode();
                _DespawnAtEvade();
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                Talk(SAY_DEATH);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void JustRespawned()
            {
                SpawnTotems();
            }

            void SpawnTotems()
            {
                if (totem1 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY, totemStalkerPos[0], TEMPSUMMON_MANUAL_DESPAWN))
                {
                    totem1->CastSpell(totem1, SPELL_VENOM_TOTEM, true);
                    totem1->CastSpell(me, SPELL_VENOM_TOTEM_BEAM_RIGHT, true);
                }

                if (totem2 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY, totemStalkerPos[1], TEMPSUMMON_MANUAL_DESPAWN))
                {
                    totem2->CastSpell(totem2, SPELL_VENOM_TOTEM, true);
                    totem2->CastSpell(me, SPELL_VENOM_TOTEM_BEAM_LEFT, true);
                }
                me->HandleEmoteCommand(EMOTE_STATE_SPELL_PRECAST);
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
                        case EVENT_RELEASE_TOTEMS:
                            me->RemoveAurasDueToSpell(SPELL_VENOM_TOTEM_BEAM_LEFT);
                            me->RemoveAurasDueToSpell(SPELL_VENOM_TOTEM_BEAM_RIGHT);
                            break;
                        case EVENT_VENOMOUS_EFFUSION:
                            if (Creature* right = me->SummonCreature(NPC_VENOMOUS_EFFUSION_STALKER, venomousEffusionStalkerPos[0], TEMPSUMMON_TIMED_DESPAWN, 21000))
                            {
                                right->SetWalk(true);
                                right->GetMotionMaster()->MovePath(right->GetEntry() * 100, false);
                                totem1->CastSpell(right, SPELL_VENOM_TOTEM_BEAM_RIGHT, true);
                            }
                            if (Creature* left = me->SummonCreature(NPC_VENOMOUS_EFFUSION_STALKER, venomousEffusionStalkerPos[1], TEMPSUMMON_TIMED_DESPAWN, 23000))
                            {
                                left->SetWalk(true);
                                left->GetMotionMaster()->MovePath((left->GetEntry() * 100) + 1, false);
                                totem2->CastSpell(left, SPELL_VENOM_TOTEM_BEAM_LEFT, true);
                            }
                            break;
                        case EVENT_WHISPERS_OF_HETHISS:
                            me->StopMoving();
                            MakeInterruptable(true);
                            events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 8000);
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                DoCast(target, SPELL_WHISPERS_OF_HETHIS);
                            else
                                DoCastVictim(SPELL_WHISPERS_OF_HETHIS);
                            events.ScheduleEvent(EVENT_WHISPERS_OF_HETHISS, 10500);
                            break;
                        case EVENT_APPLY_IMMUNITY:
                            MakeInterruptable(false);
                            break;
                        case EVENT_TOXIC_LINK:
                            DoCast(me, SPELL_TOXIC_LINK);
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
            return new boss_high_priest_venoxisAI(creature);
        }
};

class npc_venomous_effusion : public CreatureScript
{
public:
    npc_venomous_effusion() : CreatureScript("npc_venomous_effusion") { }

    struct npc_venomous_effusionAI : public ScriptedAI
    {
        npc_venomous_effusionAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 1.0f, me->GetOrientation());
            events.ScheduleEvent(EVENT_CAST_EFFUSION, 100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_EFFUSION:
                        DoCast(me, SPELL_VENOMOUS_EFFUSION);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_venomous_effusionAI(creature);
    }
};

class spell_whispers_of_sethiss : public SpellScriptLoader
{
public:
    spell_whispers_of_sethiss() : SpellScriptLoader("spell_whispers_of_sethiss") { }

    class spell_whispers_of_sethiss_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_whispers_of_sethiss_AuraScript);

        void OnPeriodic(AuraEffect const* /*aurEff*/)
        {
            PreventDefaultAction();
            if (Unit* caster = GetCaster())
            {
                std::list<Player*> units = caster->GetNearestPlayersList(150.0f, true);
                for (std::list<Player*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                    if ((*itr)->HasAura(GetSpellInfo()->Id))
                        caster->CastSpell((*itr), GetSpellInfo()->Effects[EFFECT_1].TriggerSpell);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_whispers_of_sethiss_AuraScript::OnPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_whispers_of_sethiss_AuraScript();
    }
};

class spell_toxic_link_aoe : public SpellScriptLoader
{
public:
    spell_toxic_link_aoe() : SpellScriptLoader("spell_toxic_link_aoe") { }

    class spell_toxic_link_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_toxic_link_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(VictimCheck(GetCaster()));

            if (targets.empty())
                return;

            if (targets.size() >= 3)

            Trinity::Containers::RandomResizeList(targets, 2);
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->CastSpell(target, GetSpellInfo()->Effects[EFFECT_0].BasePoints, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_toxic_link_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_toxic_link_aoe_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_toxic_link_aoe_SpellScript();
    }
};

class spell_toxic_link_visual : public SpellScriptLoader
{
public:
    spell_toxic_link_visual() : SpellScriptLoader("spell_toxic_link_visual") { }

    class spell_toxic_link_visual_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_toxic_link_visual_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
            {
                if (Unit* caster = GetCaster())
                {
                    caster->CastSpell(caster, SPELL_TOXIC_EXPLOSION, true);
                    caster->RemoveAurasDueToSpell(SPELL_TOXIC_LINK_AURA);
                }
                return;
            }

            targets.remove_if(NoToxicLinkAura());

            if (targets.empty())
            {
                if (Unit* caster = GetCaster())
                {
                    caster->CastSpell(caster, SPELL_TOXIC_EXPLOSION, true);
                    caster->RemoveAurasDueToSpell(SPELL_TOXIC_LINK_AURA);
                }
                return;
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_toxic_link_visual_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_toxic_link_visual_SpellScript();
    }
};

void AddSC_boss_venoxis()
{
    new boss_high_priest_venoxis();
    new npc_venomous_effusion();
    new spell_whispers_of_sethiss();
    new spell_toxic_link_aoe();
    new spell_toxic_link_visual();
}
