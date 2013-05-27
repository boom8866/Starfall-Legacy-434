#include "vortex_pinnacle.h"
#include "ScriptPCH.h"

enum Spells
{
    SPELL_CIILLING_BREATH           = 88308,
    SPELL_CALL_WINDS_VISUAL         = 88772,
    SPELL_CALL_WINDS_TICKER         = 88244,
    SPELL_SLOW                      = 88286,
    SPELL_SPEEDUP                   = 88282,
    SPELL_TORNADO_AURA              = 88313,
};

enum Events
{
    EVENT_CHILLING_BREATH           = 1,
    EVENT_CALL_WINDS                = 2,
    EVENT_SWITCH_WINDS              = 3,
    EVENT_DEBUFF_CHECKER            = 4,
    EVENT_SUMMON_TRIGGER            = 5,
    EVENT_MOVE_RANDOM               = 6,
};

enum Texts
{
    ANNOUNCE_WIND_CHANGE            = 0,
};

enum Adds
{
    NPC_WIND        = 47305,
    NPC_TORNADO     = 47342,
};

Position const TriggerPos1  = {-1216.225f, 64.027f, 734.175f, 2.730f};
Position const TriggerPos2  = {-1216.225f, 64.027f, 734.175f, 4.234f};
Position const TriggerPos3  = {-1216.225f, 64.027f, 734.175f, 5.911f};

class OrientationCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit OrientationCheck(Unit* _caster) : caster(_caster) { }
        bool operator() (WorldObject* unit)
        {
            if (!unit || !caster)
                return true;
                
                
            float delta = caster->GetOrientation();
            float base = unit->GetOrientation();
            
            if (delta > base)
                delta -= base;
            else
                delta = base - delta;
            
            if (delta > M_PI)
                delta = 2 * M_PI - delta;
            
            if ( delta < M_PI/2)
                return true;
                
            return false;
}
    private:
        Unit* caster;
};

class boss_altairus : public CreatureScript
{
public:
    boss_altairus() : CreatureScript("boss_altairus") { }

    struct boss_altairusAI : public BossAI
    {
        boss_altairusAI(Creature* creature) : BossAI(creature, DATA_ALTAIRUS)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            _Reset();
            instance->SetBossState(DATA_ALTAIRUS, NOT_STARTED);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_DEBUFF_CHECKER, 6000);
            events.ScheduleEvent(EVENT_SUMMON_TRIGGER, 5000);
            events.ScheduleEvent(EVENT_CHILLING_BREATH, 2000);
            events.ScheduleEvent(EVENT_SWITCH_WINDS, 35000);
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
                    case EVENT_DEBUFF_CHECKER:
                    {
                        Map::PlayerList const &PlList = me->GetMap()->GetPlayers();
                        if (PlList.isEmpty())
                            return;
                        for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                            if (Player* player = i->getSource())
                                if (!player->HasAura(SPELL_SPEEDUP))
                                    player->AddAura(SPELL_SLOW, player);
                                else if (player->HasAura(SPELL_SPEEDUP))
                                    player->RemoveAurasDueToSpell(SPELL_SLOW);

                        events.ScheduleEvent(EVENT_DEBUFF_CHECKER, 1000);
                        break;
                    }
                    case EVENT_SUMMON_TRIGGER:
                        me->SummonCreature(NPC_WIND, TriggerPos1, TEMPSUMMON_MANUAL_DESPAWN, 0);
                        break;
                    case EVENT_CHILLING_BREATH:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            me->CastSpell(target, SPELL_CIILLING_BREATH, true);
                        events.ScheduleEvent(EVENT_CHILLING_BREATH, 12000);
                        break;
                    case EVENT_SWITCH_WINDS:
                        Talk(ANNOUNCE_WIND_CHANGE);
                        me->DespawnCreaturesInArea(NPC_WIND, 125.0f);
                        events.ScheduleEvent(EVENT_SWITCH_WINDS, 30000);
                        events.ScheduleEvent(EVENT_CALL_WINDS, 1000);
                        break;
                    case EVENT_CALL_WINDS:
                        switch (urand(0,2))
                        {
                            case 0:
                            {
                                me->SummonCreature(NPC_WIND, TriggerPos1, TEMPSUMMON_MANUAL_DESPAWN, 0);
                                break;
                            }
                            case 1:
                            {
                                me->SummonCreature(NPC_WIND, TriggerPos2, TEMPSUMMON_MANUAL_DESPAWN, 0);
                                break;
                            }
                            case 2:
                            {
                                me->SummonCreature(NPC_WIND, TriggerPos3, TEMPSUMMON_MANUAL_DESPAWN, 0);
                                break;
                            }
                        }
                        //break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_altairusAI (creature);
    }
};

class npc_wind_caster : public CreatureScript
{
public:
    npc_wind_caster() : CreatureScript("npc_wind_caster") {}

    struct npc_wind_casterAI : public ScriptedAI
    {
        npc_wind_casterAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            instance = me->GetInstanceScript();
            summoned = false;
        }

        InstanceScript* instance;
        bool summoned;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (!summoned)
            {
                DoCastAOE(SPELL_CALL_WINDS_VISUAL);
                me->AddAura(SPELL_CALL_WINDS_TICKER, me);
                me->SetReactState(REACT_PASSIVE);
                me->setFaction(16);
                me->SetDisplayId(me->GetCreatureTemplate()->Modelid2);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                summoned = true;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (instance->GetBossState(DATA_ALTAIRUS) == NOT_STARTED)
                me->DespawnOrUnsummon(1);

            if (instance->GetBossState(DATA_ALTAIRUS) == DONE)
                me->DespawnOrUnsummon(1);

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wind_casterAI(creature);
    }
};

class npc_altairus_tornado : public CreatureScript
{
public:
    npc_altairus_tornado() : CreatureScript("npc_altairus_tornado") {}

    struct npc_altairus_tornadoAI : public ScriptedAI
    {
        npc_altairus_tornadoAI(Creature* creature) : ScriptedAI(creature) 
        {
            instance = me->GetInstanceScript();
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid2);
            me->SetPhaseMask(2, true);
            active = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool active;

        void UpdateAI(uint32 diff)
        {
            if (instance->GetBossState(DATA_ALTAIRUS) == IN_PROGRESS)
            {
                if (IsHeroic() && !active)
                {
                    me->SetPhaseMask(1, true);
                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->MoveRandom(15.0f);
                    me->SetWalk(true);
                    events.ScheduleEvent(EVENT_MOVE_RANDOM, 5000);
                    active = true; 
                }
            }

            if (instance->GetBossState(DATA_ALTAIRUS) == NOT_STARTED)
            {
                me->CombatStop(true);
                me->SetPhaseMask(2, true);
                active = false;
                events.Reset();
            }

            if (instance->GetBossState(DATA_ALTAIRUS) == DONE)
            {
                me->CombatStop(true);
                me->SetPhaseMask(2, true);
                active = false;
                events.Reset();
            }

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_RANDOM:
                        me->GetMotionMaster()->MoveRandom(5.0f);
                        events.ScheduleEvent(EVENT_MOVE_RANDOM, 3000);
                        break;
                }
            }   
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_altairus_tornadoAI(creature);
    }
};

class spell_call_winds : public SpellScriptLoader
{
    public:
        spell_call_winds() : SpellScriptLoader("spell_call_winds") { }

        class spell_call_winds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_call_winds_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                std::list<WorldObject*>::iterator it = unitList.begin();
                
                while( it != unitList.end() )
                {
                    if (!GetCaster())
                        return;
                    WorldObject* unit = *it;
                    
                    if (!unit)
                        continue;
                        
                    float delta = GetCaster()->GetOrientation();
                    float base =  unit->GetOrientation();
                
                    if (delta > base)
                        delta -= base;
                    else
                        delta = base - delta;
                    
                    if (delta > M_PI)
                        delta = 2 * M_PI - delta;

                    if ( delta < M_PI/2)
                    
                        it = unitList.erase(it);
                else it++;
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_call_winds_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_call_winds_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_call_winds_SpellScript();
        }
};

void AddSC_boss_altairus()
{
    new boss_altairus();
    new npc_wind_caster();
    new npc_altairus_tornado();
    new spell_call_winds();
}