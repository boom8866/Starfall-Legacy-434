
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "blackwing_descent.h"

enum Events
{
    // Nefarian & Onyxia
    EVENT_RANGE_CHECK = 1, // Triggered by Onyxia
    EVENT_TAIL_LASH,
    EVENT_SHADOWFLAME_BREATH,

    // Nefarian
    // Misc
    EVENT_LAND,

    EVENT_CHECK_PLATFORM,

    // Phase 1 & 3
    EVENT_ELECTRUCUTE,
    EVENT_SHADOW_OF_COWADICE,
    EVENT_HAIL_OF_BONES,

    // Phase 2
    EVENT_SHADOWFLAME_BARRAGE,

    // Phase 3
    EVENT_SHADOWBLAZE,
    EVENT_SHADOWBLAZE_SPARK,

    // Onyxia
    EVENT_SPELL_LIGHTNING_DISCHARGE,
};

enum Spells
{
    // Nefarian
    // Phase 1 & 3
    SPELL_SHADOW_OF_COWADICE        = 79353,
    SPELL_ELECTROCUTE               = 94090, // Triggered at every 10% hp
    SPELL_HAIL_OF_BONES             = 94104, // Spawns 78122

    // Phase 2
    SPELL_MAGMA                     = 81114, // Triggered through the Stalker (WoWhead is wrong)
    SPELL_SHADOWFLAME_BARRAGE       = 94121,

    // Phase 3
    SPELL_SHADOWBLAZE               = 94087, // Ressurects 78122
    SPELL_SHADOWBLAZE_SPARK         = 81031,

    // Onyxia
    SPELL_LIGHTNING_DISCHARGE       = 94113,
    SPELL_ELECTRICAL_OVERLOAD       = 78999, // If she reaches 100% energy

    // Nefarian & Onyxia
    SPELL_CHILDREN_OF_DEATHWING     = 78619,
    SPELL_TAIL_LASH                 = 94128,
    SPELL_SHADOWFLAME_BREATH        = 94124,
    SPELL_ANIMATE_BONES             = 78122, // If you CC some spells

    // Chromatic Prototype
    SPELL_BLAST_NOVA                = 80734, // SmartAI

};

enum Points
{
    POINT_NON,
    POINT_LAND_START,
    POINT_LAND_END,
};

Position const position[] =
{
    {-108.291f, -224.68f, 6.48474f, 42.f},       // Nefarians landing Position I
    {-108.291f, -224.68f, 6.48474f, 3.1285f}	    // Nefarians landing Position II
};

class boss_bd_nefarian : public CreatureScript
{
public:
    boss_bd_nefarian() : CreatureScript("boss_bd_nefarian") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bd_nefarianAI (creature);
    }

    struct boss_bd_nefarianAI : public BossAI
    {
        boss_bd_nefarianAI(Creature* creature) : BossAI(creature, DATA_NEFARIAN)
        {
            //instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint8 phase;
        uint8 electrocuteTrigger;

        uint32 shadowblazeSpark; // Shadowblaze Spark is caster faster every time

        bool isOnGround;

        void Reset()
        {
            _Reset();

            phase = 1;

            me->SetSpeed(MOVE_WALK, 3.0f);

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            shadowblazeSpark = 20000;
        }

        void EnterCombat(Unit* who)
        {		
            _EnterCombat();

            // To Debug Onyxia
            return;

            events.ScheduleEvent(EVENT_CHECK_PLATFORM, 5000);
            events.ScheduleEvent(EVENT_TAIL_LASH, 32000);
            events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, 37000);
            events.ScheduleEvent(EVENT_ELECTRUCUTE, 10000);

            events.ScheduleEvent(EVENT_LAND, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isInCombat() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            CheckPhase();

            events.Update(diff);
            //_DoAggroPulse(diff);           

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // General
                case EVENT_CHECK_PLATFORM:
                    DoCheckPlatform();
                    break;

                    // Ground
                case EVENT_TAIL_LASH:
                    DoCastAOE(SPELL_TAIL_LASH);
                    events.ScheduleEvent(EVENT_TAIL_LASH, 12000);
                    break;
                case EVENT_SHADOWFLAME_BREATH:
                    DoCastVictim(SPELL_SHADOWFLAME_BREATH);
                    events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, 15000);
                    break;
                case EVENT_ELECTRUCUTE:
                    DoCastAOE(SPELL_ELECTROCUTE);
                    events.ScheduleEvent(EVENT_ELECTRUCUTE, 25000);
                    break;
                    // Air
                case EVENT_LAND:
                    me->GetMotionMaster()->MovePoint(POINT_LAND_END, position[1]);
                    break;
                }
            }		

            DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (id)
            {
            /*case POINT_LAND_START:
                
                break;*/
            case POINT_LAND_END:
                me->SetSpeed(MOVE_WALK, 3.0f);
                break;
            }
        }

        void JustDied(Unit* killer)
        {
            DespawnMinions();

            _JustDied();
        }

    private:

        // Despawn System
        inline void DespawnMinions()
        {
            // me->DespawnCreaturesInArea(NPC_ABBERATON);
        }

        // Player Cheating detection
        inline void DoCheckPlatform()
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();

            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if (i->getSource()->GetPositionZ() > 89.f)
                {
                    DoCast(i->getSource(), SPELL_SHADOW_OF_COWADICE);
                    events.ScheduleEvent(EVENT_CHECK_PLATFORM, 5000);

                    return;
                }
        }

        // Phasing System
        inline void CheckPhase()
        {

        }
    };
};

class boss_bd_onyxia : public CreatureScript
{
public:
    boss_bd_onyxia() : CreatureScript("boss_bd_onyxia") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bd_onyxiaAI (creature);
    }

    struct boss_bd_onyxiaAI : public ScriptedAI
    {
        boss_bd_onyxiaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (me->isInCombat() || who->GetPositionZ() > me->GetPositionZ() + 3)
                return;

            if (!who->IsVisible())
                return;

            me->SetInCombatWithZone();
        }

        void EnterCombat(Unit* /*who*/)
        {	
            if (Creature* nefarian = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_NEFARIAN)))
                nefarian->SetInCombatWithZone();

            events.ScheduleEvent(EVENT_RANGE_CHECK, 1500);
            events.ScheduleEvent(EVENT_TAIL_LASH, 12000);
            events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, 15000);
            events.ScheduleEvent(EVENT_SPELL_LIGHTNING_DISCHARGE, 21000);
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

                case EVENT_RANGE_CHECK:
                    if (Creature* nefarian = ObjectAccessor::GetCreature(*me,instance->GetData64(BOSS_NEFARIAN)))
                        if (nefarian->GetDistance(me) < 40.f)
                        {
                            if (!nefarian->HasAura(SPELL_CHILDREN_OF_DEATHWING))
                                nefarian->AddAura(SPELL_CHILDREN_OF_DEATHWING, nefarian);

                            if (!me->HasAura(SPELL_CHILDREN_OF_DEATHWING))
                                me->AddAura(SPELL_CHILDREN_OF_DEATHWING, me);

                        }else
                        {
                            if (nefarian->HasAura(SPELL_CHILDREN_OF_DEATHWING))
                                nefarian->RemoveAura(SPELL_CHILDREN_OF_DEATHWING);

                            if (me->HasAura(SPELL_CHILDREN_OF_DEATHWING))
                                me->RemoveAura(SPELL_CHILDREN_OF_DEATHWING);
                        }

                        events.ScheduleEvent(EVENT_RANGE_CHECK, 1500);
                        break;
                case EVENT_TAIL_LASH:
                    DoCastAOE(SPELL_TAIL_LASH);
                    events.ScheduleEvent(EVENT_TAIL_LASH, 12000);
                    break;
                case EVENT_SHADOWFLAME_BREATH:
                    DoCastVictim(SPELL_SHADOWFLAME_BREATH);
                    events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, 15000);
                    break;
                case EVENT_SPELL_LIGHTNING_DISCHARGE:
                    DoCastAOE(SPELL_LIGHTNING_DISCHARGE);
                    events.ScheduleEvent(EVENT_SPELL_LIGHTNING_DISCHARGE, 21000);
                    break;
                }
            }		

            DoMeleeAttackIfReady();
        }
    };
};

class mob_bd_magma_trigger : public CreatureScript
{
public:
    mob_bd_magma_trigger() : CreatureScript("mob_bd_magma_trigger") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_bd_magma_triggerAI (creature);
    }

    struct mob_bd_magma_triggerAI : public ScriptedAI
    {
        mob_bd_magma_triggerAI(Creature* creature) : ScriptedAI(creature)
        {
            checkTimer = 1500;
            position_Z = creature->GetPositionZ();
        }

        uint32 checkTimer;
        float position_Z;

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();

                if (!PlayerList.isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        if (i->getSource()->GetDistance(me) < 100.f)
                            if (i->getSource()->GetPositionZ() < position_Z)
                            {
                                if (!i->getSource()->HasAura(SPELL_MAGMA))
                                    me->AddAura(SPELL_MAGMA,i->getSource());
                            }else
                                if (i->getSource()->HasAura(SPELL_MAGMA))
                                    i->getSource()->RemoveAura(SPELL_MAGMA);
                }

                checkTimer = 1500;

            } else checkTimer -= diff;
        }
    };
};

class spell_lightning_discharge : public SpellScriptLoader
{
public:
    spell_lightning_discharge() : SpellScriptLoader("spell_lightning_discharge") { }

    class spell_lightning_dischargeSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_lightning_dischargeSpellScript);

        bool Load()
        {
            return true;
        }

        /*

        hals links 77939
        Visual Vorne links 77942
        Visual Vorne rechts 77943
        Visual Hinten rechts 77944
        Visual ganz 78090

        einmal visual mitte links
        94107

        Blitze
        vorne rechts
        .cast back 81435
        hinten rechts
        .cast back 81436

        vorne links
        .cast back 81437

        hinten links
        .cast back 81438

        */
        
        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                caster->CastSpell(caster,78090,true);
             
                for (uint8 side = 0; side <= 3; side++)
                {

                }
            }

                /*if (Unit* target = GetHitUnit())
                {

                }*/

            

            

        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_lightning_dischargeSpellScript::HandleScript,EFFECT_0,SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_lightning_dischargeSpellScript();
    }
};

void AddSC_boss_bd_nefarian()
{
    /*
    new boss_bd_nefarian();
    new boss_bd_onyxia();
    new mob_bd_magma_trigger();
    new spell_lightning_discharge();
    */
}
