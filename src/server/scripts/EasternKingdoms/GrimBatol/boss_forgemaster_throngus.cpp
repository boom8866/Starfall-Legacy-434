
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "grim_batol.h"

enum Spells
{
    SPELL_MIGHTY_STOMP          = 74984,
    SPELL_CAVE_IN               = 74987,
    SPELL_CAVE_IN_AURA          = 74990,

    SPELL_PICK_WEAPON           = 75000,
    SPELL_KNOCK_BACK            = 88504,

    SPELL_BURNING_DUAL_BLADES   = 74981,
    SPELL_PERSONAL_PHALANX      = 74908,

    // Shield Phase
    SPELL_SHIELD_VISUAL         = 94588,
    SPELL_FLAMING_SHIELD        = 90819,

    SPELL_FLAMING_ARROW         = 45101,
    SPELL_FLAMING_ARROW_VISUAL  = 74944,

    // Swords Phase
    SPELL_DUAL_BLADES_BUFF      = 74981,
    SPELL_TRASH                 = 47480,
    SPELL_DISORIENTING_ROAR     = 74976,
    SPELL_BURNING_FLAMES        = 90764,

    // Mace Phase
    SPELL_ENCUMBERED            = 75007,
    SPELL_IMPALING_SLAM         = 75056,
    SPELL_LAVA_PATCH            = 90754,
    SPELL_LAVA_PATCH_VISUAL     = 90752,
};

enum Events
{
    // General
    EVENT_PICK_WEAPON = 1,
    EVENT_MIGHTY_STOMP,
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
    EQUIPMENT_ID_SWORD	= 64435,
    EQUIPMENT_ID_MACE	= 49737,
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
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void Reset()
        {
            _Reset();
            _mace = false;
            _shield = false;
            _blades = false;
            SetEquipmentSlots(false, 0, 0, 0);
        }

        void JustSummoned(Creature* /*summon*/)
        {
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CHOOSE_BLADES:
                    Talk(SAY_BLADES);
                    Talk(SAY_BLADES_ANNOUNCE);
                    DoCast(SPELL_BURNING_DUAL_BLADES);

                    break;
                case ACTION_CHOOSE_MACE:
                    Talk(SAY_MACE);
                    Talk(SAY_MACE_ANNOUNCE);
                    break;
                case ACTION_CHOOSE_SHIELD:
                    Talk(SAY_SHIELD);
                    Talk(SAY_SHIELD_ANNOUNCE);
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

            void IsSummonedBy(Unit* summoner)
            {
                me->SetReactState(REACT_PASSIVE);
                me->setFaction(16);
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

void AddSC_boss_forgemaster_throngus()
{
    new boss_forgemaster_throngus();
    new npc_gb_cave_in();
    new spell_gb_pick_weapon();
}
