
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "grim_batol.h"

enum ScriptTexts
{
    SAY_AGGRO                           = -1810000,
    SAY_DEATH                           = -1810001,
    SAY_SUMMON                          = -1810002,
    SAY_GALE                            = -1810003,
    SAY_SLAY                            = -1810004,
};

enum Spells
{
    // Erudax
    SPELL_ENFEEBLING_BLOW				= 75789,
    SPELL_SHADOW_GALE		        	= 75664,
    SPELL_SHADOW_GALE_TRIGGER_SUMMON    = 75655,

    // (litte hole at the caster, it is a pre visual aura of shadow gale)
    SPELL_SHADOW_GALE_SPEED_TRIGGER		= 75675,
    SPELL_SHADOW_GALE_DEBUFF			= 75694,

    // Spawns 1 (NH - 40600) or 2 (HC - 48844) Faceless
    SPELL_SPAWN_FACELESS				= 75704,
    SPELL_TWILIGHT_PORTAL_VISUAL		= 95716,

    // In this Script is is casted by the Faceless itself
    SPELL_SHIELD_OF_NIGHTMARE			= 75809,

    SPELL_BINDING_SHADOWS				= 79466, // Wowhead is wrong

    // Faceless
    SPELL_UMBRAL_MENDING				= 79467, // Wowhead is wrong
    SPELL_TWILIGHT_CORRUPTION_DOT		= 93613,
    SPELL_TWILIGHT_CORRUPTION_VISUAL	= 75755, //91049,

    // Alexstraszas Eggs
    SPELL_SUMMON_TWILIGHT_HATCHLINGS    = 91058,
};

enum Events
{
    EVENT_ENFEEBLING_BLOW = 1,
    EVENT_SHADOW_GALE,
    EVENT_SUMMON_FACELESS,
    EVENT_REMOVE_TWILIGHT_PORTAL,
    EVENT_SUMMON_ADDS,
    EVENT_CAST_SHIELD_OF_NIGHTMARE_DELAY,
    EVENT_BINDING_SHADOWS,

    EVENT_TRIGGER_GALE_CHECK_PLAYERS,
};

enum Points
{
    POINT_FACELESS_IS_AT_AN_EGG = 1,
    POINT_ERUDAX_USE_SHADOW_GALE,
};

class boss_erudax: public CreatureScript
{
public:
    boss_erudax() : CreatureScript("boss_erudax") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_erudaxAI (creature);
    }

    struct boss_erudaxAI : public BossAI
    {
        boss_erudaxAI(Creature* creature) : BossAI(creature, DATA_ERUDAX)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        Creature* shadowGaleStalker;

        void Reset()
        {
            ResetMinions();

            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            // Fixes wrong behaviour of Erudax if the boss was respawned
            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveChase(me->getVictim());

            //events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, 4000);
            //events.ScheduleEvent(EVENT_BINDING_SHADOWS, 9000);
            events.ScheduleEvent(EVENT_SHADOW_GALE, 1000);
            // DoScriptText(SAY_AGGRO, me);

            _EnterCombat();
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
                case EVENT_ENFEEBLING_BLOW:
                    DoCastVictim(SPELL_ENFEEBLING_BLOW);

                    events.ScheduleEvent(EVENT_SUMMON_ADDS, urand(19000,24000));
                    break;

                case EVENT_SHADOW_GALE:
                    // DoScriptText(SAY_GALE, me);
                    
                    events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, 8000);

                    DoCast(SPELL_SHADOW_GALE_TRIGGER_SUMMON);
                    DoCast(SPELL_SHADOW_GALE);                  
                    break;

                case EVENT_SUMMON_ADDS:
                    // Despawns the Stalker
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveChase(me->getVictim());

                    if ((rand()%2))
                        me->MonsterYell(SAY_SUMMON, LANG_UNIVERSAL, NULL);

                    //Summons Faceless over the Spell
                    if(Unit* facelessPortalStalker = me->FindNearestCreature(NPC_FACELESS_PORTAL_STALKER, 100.f))
                    {
                        facelessPortalStalker->GetAI()->DoCast(facelessPortalStalker,SPELL_TWILIGHT_PORTAL_VISUAL,true);
                        events.ScheduleEvent(EVENT_REMOVE_TWILIGHT_PORTAL, 7000);

                        facelessPortalStalker->GetAI()->DoCast(facelessPortalStalker,SPELL_SPAWN_FACELESS,true);
                    }

                    // DBM says that the Spell has 40s CD
                    events.ScheduleEvent(EVENT_SHADOW_GALE, urand(40000,44000));
                    break;

                case EVENT_REMOVE_TWILIGHT_PORTAL:
                    if(Unit* facelessPortalStalker = me->FindNearestCreature(NPC_FACELESS_PORTAL_STALKER, 100.f))
                        facelessPortalStalker->RemoveAllAuras();
                    break;

                case EVENT_BINDING_SHADOWS:

                    if (Unit* temtarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                        DoCast(temtarget,SPELL_BINDING_SHADOWS);

                    events.ScheduleEvent(EVENT_BINDING_SHADOWS, urand(12000,14000));
                    break;

                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* victim)
        {
            // DoScriptText(SAY_SLAY, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            // DoScriptText(SAY_DEATH, me);
            ResetMinions();

            _JustDied();
        }

        void JustSummoned(Creature* summon)
        {
            summon->SetInCombatWithZone();
        }

        void ResetMinions()
        {
            me->DespawnCreaturesInArea(NPC_FACELESS);
            me->DespawnCreaturesInArea(NPC_TWILIGHT_HATCHLING);

            RespawnEggs();
        }

        void RespawnEggs()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZAS_EGG, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if((*iter)->isDead())
                    (*iter)->Respawn();

                (*iter)->SetHealth(77500);
                (*iter)->SetMaxHealth(77500);
            }
        }

        void HandleShadowGale()
        {
            Creature* controller = me->FindNearestCreature(NPC_SHADOW_GALE_CONTROLLER, 100.f);

                if(!controller)
                    return;

                Position pos;
                controller->GetRandomNearPosition(pos, 25.f);
                
                Creature* trigger = me->SummonCreature(NPC_SHADOW_GALE_TRIGGER, pos, TEMPSUMMON_TIMED_DESPAWN, 17000);

                if(!trigger)
                    return;
            
                trigger->AI()->DoCast(SPELL_SHADOW_GALE_SPEED_TRIGGER);

                DoCast(SPELL_SHADOW_GALE);
        }
    };
};

class mob_faceless : public CreatureScript
{
public:
    mob_faceless() : CreatureScript("mob_faceless") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_facelessAI (creature);
    }

    struct mob_facelessAI : public ScriptedAI
    {
        mob_facelessAI(Creature* creature) : ScriptedAI(creature), target(NULL), isAtAnEgg(false), isCastingUmbraMending (false) {}

        Creature* target;
        Unit* erudax;

        bool isAtAnEgg;
        bool isCastingUmbraMending;

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            target = me->FindNearestCreature(NPC_ALEXSTRASZAS_EGG, 60.f);
            DoZoneInCombat();
            // DoScriptText(SAY_SUMMON, summoner);

            if(me->GetMap()->IsHeroic())
                events.ScheduleEvent(EVENT_CAST_SHIELD_OF_NIGHTMARE_DELAY, 3000);

            if(target != NULL)
            {
                me->GetMotionMaster()->MovePoint(POINT_FACELESS_IS_AT_AN_EGG,target->GetPositionX()-4.0f,target->GetPositionY()-4.0f,target->GetPositionZ());
            }

            me->SetReactState(REACT_PASSIVE); // That the Faceless are not running to Players while running to Eggs
        }

        void UpdateAI(uint32 diff)
        {
            if (target == NULL || !isAtAnEgg || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_SHIELD_OF_NIGHTMARE_DELAY:
                    DoCast(me, SPELL_SHIELD_OF_NIGHTMARE, true);
                    break;

                default:
                    break;
                }
            }

            if(isCastingUmbraMending)
            {	// If the Egg is Death and Umbra Mending was casted go to the next Egg
                target = GetNextEgg();

                if(target != NULL) // Solves Crashes if the Faceless killed all eggs
                    me->GetMotionMaster()->MovePoint(POINT_FACELESS_IS_AT_AN_EGG,target->GetPositionX(),target->GetPositionY(),target->GetPositionZ());

                isAtAnEgg = false;
                isCastingUmbraMending = false;

                return;
            }

            if(target->isDead())
            {
                if(Unit* erudax = me->FindNearestCreature(BOSS_ERUDAX,1000.0f, true))
                    DoCast(erudax, SPELL_UMBRAL_MENDING,false);

                isCastingUmbraMending = true;

                return;
            }

            target->AI()->DoZoneInCombat();

            DoCast(target,SPELL_TWILIGHT_CORRUPTION_DOT,true);
            DoCast(target,SPELL_TWILIGHT_CORRUPTION_VISUAL,true);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                case POINT_FACELESS_IS_AT_AN_EGG:
                    isAtAnEgg = true;
                    break;

                default:
                    break;
                }
            }
        }

        void JustDied(Unit* killer)
        {	// Removes the Dot of the Egg if the Faceless dies
            if(isAtAnEgg && target->isAlive())
                target->RemoveAllAuras();
        }

    private:

        inline Creature* GetNextEgg()
        {
            return me->FindNearestCreature(NPC_ALEXSTRASZAS_EGG,1000.0f, true);
        }
    };
};

class mob_alexstraszas_eggs : public CreatureScript
{
public:
    mob_alexstraszas_eggs() : CreatureScript("mob_alexstraszas_eggs") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_alexstraszas_eggsAI (creature);
    }

    struct mob_alexstraszas_eggsAI : public ScriptedAI
    {
        mob_alexstraszas_eggsAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);

            me->SetReactState(REACT_PASSIVE);
        }

        void JustDied(Unit* killer)
        {	// Summon Twilight Hatchlings
            // Despawn of the Hatchlings is handled by Erudax
            // The behaviour of the hatchlings is handled through SmartAI

            DoCastAOE(SPELL_SUMMON_TWILIGHT_HATCHLINGS, true);
        }

        void JustSummoned(Creature* summon)
        {
            summon->setActive(true);
            summon->AI()->DoZoneInCombat();

            if (GetPlayerAtMinimumRange(0))
                summon->Attack(GetPlayerAtMinimumRange(0), true);
        }
    };
};

class mob_shadow_gale_stalker : public CreatureScript
{
public:
    mob_shadow_gale_stalker() : CreatureScript("mob_shadow_gale_stalker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_shadow_gale_stalkerAI (creature);
    }

    struct mob_shadow_gale_stalkerAI : public ScriptedAI
    {
        mob_shadow_gale_stalkerAI(Creature* creature) : ScriptedAI(creature), VisualEffectCasted(false) {}

        Unit* erudax;
        EventMap events;
        bool VisualEffectCasted;

        void IsSummonedBy(Unit* summoner)
        {
            erudax = summoner;
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
            //DoCastAOE(SPELL_SHADOW_GALE_SPEED_TRIGGER);
        }

        void UpdateAI(uint32 diff)
        {
            if(VisualEffectCasted)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_TRIGGER_GALE_CHECK_PLAYERS:

                        Map::PlayerList const &PlayerList =  me->GetMap()->GetPlayers();

                        if (!PlayerList.isEmpty())
                        {
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                if(me->GetDistance(i->getSource()) >= 3)
                                {
                                    // ToDo Add Debuff and Deal damage
                                    //if(!i->getSource()->HasAura(SPELL_SHADOW_GALE_DEBUFF))
                                      //  me->CastSpell(i->getSource(), SPELL_SHADOW_GALE_DEBUFF, true);
                                }else
                                    i->getSource()->RemoveAura(SPELL_SHADOW_GALE_DEBUFF);
                        }

                        events.ScheduleEvent(EVENT_TRIGGER_GALE_CHECK_PLAYERS, 1000);
                        break;
                    }
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(!VisualEffectCasted)
            {
                VisualEffectCasted = true;
                events.ScheduleEvent(EVENT_TRIGGER_GALE_CHECK_PLAYERS, 1000);
            }
        }
    };
};

class ShadowGaleCheck
{
    public:
        ShadowGaleCheck(WorldObject* obj) : controller(obj) {}

        bool operator() (WorldObject* obj)
        {
            if (obj->GetTypeId() != TYPEID_PLAYER)
                return true;

            if (obj->GetDistance2d(controller) < 3.f)
                return true;

            return false;
        }

    private:
        WorldObject* controller;
};

// 75692

class spell_shadow_gale : public SpellScriptLoader
{
    public:
        spell_shadow_gale() : SpellScriptLoader("spell_shadow_gale") { }

        class spell_shadow_gale_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shadow_gale_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                bool ok = false;

                if(Unit* caster = GetCaster())
                    if(Creature* trigger = caster->FindNearestCreature(NPC_SHADOW_GALE_TRIGGER, 100.f))
                        if(Unit* controller = trigger->ToUnit())
                        {
                            ok = true;
                            unitList.remove_if(ShadowGaleCheck(controller));
                        }

                if(!ok)
                    unitList.clear();
            }

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {

                    Creature* trigger = target->FindNearestCreature(NPC_SHADOW_GALE_TRIGGER, 100.f);

                    if(!trigger)
                        return;

                    if (trigger->GetDistance2d(target) < 3.f)
                    {
                        PreventHitDamage();
                        PreventHitAura();
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_shadow_gale_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_shadow_gale_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_shadow_gale_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHitTarget += SpellEffectFn(spell_shadow_gale_SpellScript::HandleEffectScriptEffect, EFFECT_1, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_shadow_gale_SpellScript();
        }
};

class ShadowGaleTargetSelector
{
public:
    bool operator() (WorldObject* unit)
    {
        return unit->GetEntry() != NPC_SHADOW_GALE_TRIGGER;
    }
};

// 75664

class spell_shadow_gale_target_searcher : public SpellScriptLoader
{
public:
    spell_shadow_gale_target_searcher() : SpellScriptLoader("spell_shadow_gale_target_searcher") { }

    class spell_shadow_gale_target_searcher_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_shadow_gale_target_searcher_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if(ShadowGaleTargetSelector());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_shadow_gale_target_searcher_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_shadow_gale_target_searcher_SpellScript();
    }
};

void AddSC_boss_erudax()
{
    new boss_erudax();
    new mob_faceless();
    new mob_alexstraszas_eggs();
    new mob_shadow_gale_stalker();
    new spell_shadow_gale();
    new spell_shadow_gale_target_searcher();
}
