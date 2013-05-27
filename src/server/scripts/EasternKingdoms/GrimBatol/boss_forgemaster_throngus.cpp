
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
    // Misc
    SPELL_MIGHTY_STOMP          = 74984, // Summons Cave in Stalker 40228
    SPELL_PICK_WEAPON           = 75000, // He switches his weapon (DBM Announce)
    SPELL_KNOCK_BACK            = 88504, // Replacement for a server side knockback spell

    // Shield Phase
    SPELL_SHIELD_VISUAL         = 94588,
    SPELL_PERSONAL_PHALANX      = 74908,
    SPELL_FLAMING_SHIELD        = 90819, // Wowhead is wrong

    SPELL_FLAMING_ARROW         = 45101, // Casted by the Archers
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
    EVENT_PICK_WEAPON           = 1,
    EVENT_STOMP                 = 2,
    // Shield Phase
    EVENT_PERSONAL_PHALANX      = 3,
    // Swords Phase
    EVENT_DISORIENTING_ROAR     = 4,
    // Mace Phase
    EVENT_IMPALING_SLAM         = 5,
    // Twilight Archer
    EVENT_ARCHER_SHOOT          = 6,
};

enum Action
{
    ACTION_INTIALIZE_WEAPON,
};

enum Yells
{
    YELL_AGGRO,
    YELL_SWORDS,
    YELL_SWORDS_2,
    YELL_SHIELD,
    YELL_SHIELD_2,
    YELL_MACE,
    YELL_MACE_2,
    YELL_SLAY,
    YELL_DEATH,
};

enum Weapon
{
    WEAPON_NON,
    WEAPON_CHOOSING,
    WEAPON_SHIELD,
    WEAPON_SWORDS,
    WEAPON_MACE,
};

enum Equipment
{
    EQUIPMENT_ID_SWORD	= 64435,
    EQUIPMENT_ID_MACE	= 49737,
};

class MoveHome : public BasicEvent
{
public:
    MoveHome(Unit* _me) : me(_me) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        me->GetMotionMaster()->MoveTargetedHome();
        return true;
    }

private:
    Unit* me;
};

class boss_forgemaster_throngus: public CreatureScript
{
public:
    boss_forgemaster_throngus() : CreatureScript("boss_forgemaster_throngus") { }

    struct boss_forgemaster_throngusAI : public BossAI
    {
        boss_forgemaster_throngusAI(Creature* creature) : BossAI(creature, DATA_FORGEMASTER_THRONGUS) {}

        uint32 currentWaepon;
        uint8 phases [3];

        uint32 uiKickTimer;

        int burningFlamesTimer;

        void EnterCombat(Unit* /*who*/)
        {
            Talk(YELL_AGGRO);
            phases[0] = 0;
            phases[1] = 0;
            phases[2] = 0;
            events.ScheduleEvent(EVENT_STOMP, 10000);
            burningFlamesTimer = 1000;
            _EnterCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(YELL_DEATH);
            me->DespawnCreaturesInArea(NPC_FIRE_PATCH);
            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(YELL_SLAY);
        }

        void Reset()
        {
            currentWaepon = WEAPON_NON;
            me->DespawnCreaturesInArea(NPC_FIRE_PATCH);

            uiKickTimer = 1000;

            SetEquipmentSlots(false, 0, 0,0);

            _Reset();
        }

        void UpdateAI(uint32 diff)
        {
            if(!me->isInCombat())
            {
                if (uiKickTimer <= diff)
                {
                    DoCastAOE(SPELL_KNOCK_BACK, true);

                    uiKickTimer = 1000;
                } else uiKickTimer -= diff;

                return;
            }

            if (!UpdateVictim())
                return;

            if(currentWaepon == WEAPON_NON)
            {
                ResetWeapon();
                currentWaepon = WEAPON_CHOOSING;

                DoCast(SPELL_PICK_WEAPON);
                return;
            }

            if(currentWaepon == WEAPON_CHOOSING)
            {
                // Chooses a new Weapon
                IntializeWeapon();

                events.ScheduleEvent(EVENT_PICK_WEAPON, 30000);
                return;
            }

            if(currentWaepon == WEAPON_SHIELD && me->GetMap()->IsHeroic() && (!me->HasAura(SPELL_FLAMING_SHIELD)))
                DoCast(me, SPELL_FLAMING_SHIELD, true);

            events.Update(diff);

            if(currentWaepon == WEAPON_SWORDS)
                burningFlamesTimer -= diff;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {

                case EVENT_PICK_WEAPON:
                    {
                        // It is only need to set the Weapon to WEAPON_NON to switch the Weapon
                        currentWaepon = WEAPON_NON;
                        break;
                    }

                case EVENT_STOMP:
                    {
                        if(currentWaepon == WEAPON_SHIELD)
                        {
                            // Don't stomp in Shield Phase
                            events.RescheduleEvent(EVENT_STOMP, 4000);
                            continue;
                        }

                        DoCast(SPELL_MIGHTY_STOMP);

                        events.ScheduleEvent(EVENT_STOMP, 11000);
                        break;
                    }
                case EVENT_PERSONAL_PHALANX:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                            DoCast(target, SPELL_PERSONAL_PHALANX);

                        events.ScheduleEvent(EVENT_PERSONAL_PHALANX, 10000);
                        break;
                    }
                case EVENT_IMPALING_SLAM:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                            DoCast(target, SPELL_IMPALING_SLAM);

                        events.ScheduleEvent(EVENT_IMPALING_SLAM, 15000);
                        break;
                    }
                case EVENT_DISORIENTING_ROAR:
                    {
                        // bugged
                        //DoCastAOE(SPELL_DISORIENTING_ROAR);

                        events.ScheduleEvent(EVENT_DISORIENTING_ROAR, 11000);
                        break;
                    }
                case EVENT_ARCHER_SHOOT:
                    {
                        //DoArcherShoot();
                        events.ScheduleEvent(EVENT_ARCHER_SHOOT, 6000);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            if(action == ACTION_INTIALIZE_WEAPON)
            {
                IntializeWeapon();
                events.ScheduleEvent(EVENT_PICK_WEAPON, 30000);
            }
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType)
        {
            if(currentWaepon != WEAPON_SWORDS || !me->GetMap()->IsHeroic())
                return;

            if(damage > 0 && damageType == DIRECT_DAMAGE && burningFlamesTimer <= 0)
            {
                burningFlamesTimer = 1500;

                DoCastVictim(SPELL_BURNING_FLAMES);
                DoCastVictim(SPELL_TRASH);
            }
        }

    private:
        inline void IntializeWeapon()
        { // Intialize next Phase
            // Choose Weapon
            currentWaepon = GetNextPhase();

            // If you want to test a single Phase you can overwrite the rand value here
            // currentWaepon = WEAPON_MACE;

            switch(currentWaepon)
            {
            case WEAPON_SHIELD:
                {
                    SetEquipmentSlots(false, 0, 0,0);
                    DoCast(me, SPELL_SHIELD_VISUAL, true);
                    Talk(YELL_SHIELD);
                    Talk(YELL_SHIELD_2);
                    if(me->GetMap()->IsHeroic())
                        DoCast(me, SPELL_FLAMING_SHIELD, true);

                    events.ScheduleEvent(EVENT_DISORIENTING_ROAR, 5000);
                    events.ScheduleEvent(EVENT_PERSONAL_PHALANX, 1000);
                    break;
                }
            case WEAPON_SWORDS:
                {
                    DoCast(me, SPELL_DUAL_BLADES_BUFF, true);
                    Talk(YELL_SWORDS);
                    Talk(YELL_SWORDS_2);
                    SetEquipmentSlots(false, EQUIPMENT_ID_SWORD, EQUIPMENT_ID_SWORD,0);
                    // Disabled because still buggy
                    // events.ScheduleEvent(EVENT_DISORIENTING_ROAR, 11000);
                    break;
                }
            case WEAPON_MACE:
                {
                    if(me->GetMap()->IsHeroic())
                        DoCast(me, SPELL_LAVA_PATCH, true);

                    Talk(YELL_MACE);
                    Talk(YELL_MACE_2);
                    DoCast(me, SPELL_ENCUMBERED, true);
                    SetEquipmentSlots(false, EQUIPMENT_ID_MACE, 0,0);
                    events.ScheduleEvent(EVENT_IMPALING_SLAM, 7000);
                    break;
                }
            }
        }

        inline void ResetWeapon()
        { // Resets last Phase
            events.CancelEvent(EVENT_DISORIENTING_ROAR);
            events.CancelEvent(EVENT_PERSONAL_PHALANX);
            events.CancelEvent(EVENT_DISORIENTING_ROAR);
            events.CancelEvent(EVENT_IMPALING_SLAM);

            // Remove Auras spezified to the Phases
            // Shield Phase
            me->RemoveAura(SPELL_FLAMING_SHIELD);
            me->RemoveAura(SPELL_PERSONAL_PHALANX);

            // Swords Phase
            me->RemoveAura(SPELL_DUAL_BLADES_BUFF);

            // Mace Phase
            me->RemoveAura(SPELL_LAVA_PATCH);
            me->RemoveAura(SPELL_ENCUMBERED);
        }

        inline uint8 GetNextPhase()
        {	// [100%] Working
            // zit. Wowhead
            // The three weapon phases will switch randomly,
            // but Throngus will always go through all three
            // before he picks the first one again.

            uint8 base[3] = {WEAPON_SHIELD, WEAPON_SWORDS, WEAPON_MACE};

            if (phases[0]==0 && phases[1]==0 && phases[2]==0)
            { // If Throngus was in every phase or the fight has just begun calculate new phase string
                for(uint8 i = 0; i <= 2; i++)
                {
                    while(phases[i] == 0)
                    {
                        uint8 r = urand(0,2);
                        phases[i] = base[r];
                        base[r] = 0;
                    }
                }

                uint8 v = phases[0];
                phases[0] = 0;
                return v;
            }else
            { // If Throngus was still in a Phase, just get next Phase
                for(uint8 i = 0; i <= 2; i++)
                    if(phases[i] != 0)
                    {
                        uint8 v = phases[i];
                        phases[i] = 0;

                        return v;
                    }
            }

            // Should not happend but sure is sure
            return urand(WEAPON_SHIELD, WEAPON_MACE);
        }

        void DoArcherShoot()
        {
            // Feature does make too high Damage

            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_TWILIGHT_ARCHER, 30.f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                {
                    (*iter)->CastSpell(target, SPELL_FLAMING_ARROW_VISUAL, true);
                    (*iter)->CastSpell(target, SPELL_FLAMING_ARROW, true);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_forgemaster_throngusAI (creature);
    }
};

class KnockBackSelector
{
public:
    bool operator() (WorldObject* obj)
    {
        if(Creature* creature = obj->ToCreature())
            return creature->GetEntry() != NPC_TWILIGHT_BEGUILER;

        return true;
    }
};

class spell_knockback_generetic : public SpellScriptLoader
{
public:
    spell_knockback_generetic() : SpellScriptLoader("spell_knockback_generetic") { }

    class spell_knockback_generetic_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_knockback_generetic_SpellScript);

        void OnUnitSelect(std::list<WorldObject*>& targets)
        {
            targets.remove_if(KnockBackSelector());
        }

        void HandleKnockBack(SpellEffIndex effIndex)
        {
            if(Creature* creature = GetHitCreature())
            {
                creature->m_Events.KillAllEvents(false);
                creature->m_Events.AddEvent(new MoveHome(creature), creature->m_Events.CalculateTime(4500));
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_knockback_generetic_SpellScript::OnUnitSelect, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_knockback_generetic_SpellScript::HandleKnockBack, EFFECT_0, SPELL_EFFECT_KNOCK_BACK);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_knockback_generetic_SpellScript();
    }
};

void AddSC_boss_forgemaster_throngus()
{
    new boss_forgemaster_throngus();
    new spell_knockback_generetic();
}
