
#include "vortex_pinnacle.h"
#include "Vehicle.h"

enum Yells
{
    SAY_AGGRO       = 0,
    SAY_FIELD,
    ANNOUNCE_FIELD,
    SAY_DEATH,
    SAY_KILL
};

enum Spells
{
    // Asaad
    SPELL_ENERGY_FIELD_CAST         = 86911,
    SPELL_CHAIN_LIGHTNING           = 87622,
    SPELL_LIGHTNING_STORM_CAST      = 86930,
    SPELL_STATIC_CLING              = 87618,
    SPELL_SUMMON_SKYFALL_STAR       = 96260,
    SPELL_GROUNDING_FIELD_VISUAL    = 87517,
    SPELL_TELEPORT                  = 87328,
    SPELL_SOTS_SUMMON               = 87518,
    SPELL_PRISM_BEAMS               = 87724,
    SPELL_STONE_RUNE_BEAM_B         = 86923
};

enum Events
{
    EVENT_CHAIN_LIGHTNING           = 1,
    EVENT_STATIC_CLING,
    EVENT_UNSTABLE_GROUNDING_FIELD,
    EVENT_LIGHTNING_STORM_CAST,
    EVENT_LIGHTNING_STORM_CAST_END,
    EVENT_SUMMON_SKYFALL_STAR,

    // Npc
    EVENT_SUMMON,
    EVENT_CORNER
};

enum Points
{
    POINT_CORNER    = 1
};

enum Actions
{
    ACTION_TELEPORT_START   = 1
};

float const floorZ = 646.680725f;

class boss_asaad : public CreatureScript
{
public:
    boss_asaad() : CreatureScript("boss_asaad") { }

    struct boss_asaadAI : public BossAI
    {
        boss_asaadAI(Creature* creature) : BossAI(creature, DATA_ASAAD)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 14000);
            events.ScheduleEvent(EVENT_UNSTABLE_GROUNDING_FIELD, 18000);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_STATIC_CLING, 10000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SetBossState(DATA_ASAAD, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_GROUNDING_FIELD_STATIONARY, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_GROUNDING_FIELD_TRIGGER:
                    summons.Summon(summon);
                    break;
                case NPC_SOTS_DUMMY:
                {
                    std::list<Creature*> units;
                    GetCreatureListWithEntryInGrid(units, me, NPC_GROUNDING_FIELD_STATIONARY, 50.0f);
                    for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                        (*itr)->AI()->DoCastAOE(SPELL_STONE_RUNE_BEAM_B);
                    summons.Summon(summon);
                    break;
                }
                default:
                    break;
            }
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            _FinishDungeon();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            Talk(SAY_DEATH);

            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_GROUNDING_FIELD_STATIONARY, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();

            me->DespawnCreaturesInArea(NPC_SKYFALL_STAR_N);
            me->DespawnCreaturesInArea(NPC_SKYFALL_STAR_H);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_KILL);
        }

        void DoAction(int32 action)
        {
            if (action == ACTION_TELEPORT_START)
            {
                me->FinishSpell(CURRENT_CHANNELED_SPELL, false);
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                if (Creature* trigger = me->FindNearestCreature(NPC_GROUNDING_FIELD_TRIGGER, 80.0f, true))
                {
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    Position tele;
                    tele.m_positionX = trigger->GetPositionX();
                    tele.m_positionY = trigger->GetPositionY();
                    tele.m_positionZ = me->GetPositionZ() + 10.0f;
                    tele.m_orientation = (trigger->GetOrientation() + (M_PI/1.1f));

                    uint32 distance = 6;
                    me->StopMoving();
                    me->CastSpell(tele.m_positionX + cos(tele.m_orientation)*distance, tele.m_positionY + sin(tele.m_orientation)*distance, tele.m_positionZ - 4.0f, SPELL_SOTS_SUMMON, true);
                    DoTeleportTo(tele.m_positionX + cos(tele.m_orientation)*distance, tele.m_positionY + sin(tele.m_orientation)*distance, tele.m_positionZ);
                    me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                    me->SendMovementFlagUpdate(false);
                }
                DoCastAOE(SPELL_TELEPORT);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                events.ScheduleEvent(EVENT_LIGHTNING_STORM_CAST, 1000);
            }
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
                    case EVENT_CHAIN_LIGHTNING:
                        me->StopMoving();
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_CHAIN_LIGHTNING);
                        events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 24000);
                        break;
                    case EVENT_SUMMON_SKYFALL_STAR:
                        DoCast(SPELL_SUMMON_SKYFALL_STAR);
                        events.CancelEvent(EVENT_SUMMON_SKYFALL_STAR);
                        break;
                    case EVENT_STATIC_CLING:
                        me->StopMoving();
                        DoCastAOE(SPELL_STATIC_CLING);
                        DoCast(SPELL_SUMMON_SKYFALL_STAR);
                        events.ScheduleEvent(EVENT_STATIC_CLING, 31000);
                        break;
                    case EVENT_UNSTABLE_GROUNDING_FIELD:
                        me->StopMoving();
                        Talk(SAY_FIELD);
                        Talk(ANNOUNCE_FIELD);
                        if (Creature* walker = me->SummonCreature(NPC_GROUNDING_FIELD_TRIGGER, me->GetPositionX()+rand()%10, me->GetPositionY()+rand()%10, me->GetPositionZ()))
                            DoCast(walker, SPELL_ENERGY_FIELD_CAST);
                        events.ScheduleEvent(EVENT_UNSTABLE_GROUNDING_FIELD, 46000);
                        break;
                    case EVENT_LIGHTNING_STORM_CAST:
                        DoCastAOE(SPELL_LIGHTNING_STORM_CAST);
                        events.ScheduleEvent(EVENT_LIGHTNING_STORM_CAST_END, 7000);
                        break;
                    case EVENT_LIGHTNING_STORM_CAST_END:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->DespawnCreaturesInArea(NPC_SOTS_DUMMY);
                        me->DespawnCreaturesInArea(NPC_GROUNDING_FIELD_TRIGGER);
                        me->DespawnCreaturesInArea(NPC_GROUNDING_FIELD_STATIONARY);
                        break;
                }
            }

            // Safety distance check to prevent exit out of area
            if (me->GetDistance2d(-601.47f, 501.97f) > 55)
            {
                events.Reset();
                EnterEvadeMode();
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_asaadAI (creature);
    }
};

class npc_field_walker : public CreatureScript
{
public:
    npc_field_walker() : CreatureScript("npc_field_walker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_field_walkerAI(creature);
    }

    struct npc_field_walkerAI : public ScriptedAI
    {
        npc_field_walkerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            count = 0;
        }

        InstanceScript* instance;
        EventMap events;
        uint8 count;
        uint32 distance;
        Position pos;

        void IsSummonedBy(Unit* creator)
        {
            me->SetReactState(REACT_PASSIVE);
            if (creator->GetEntry() == BOSS_ASAAD)
            {
                me->SetFacingToObject(creator);
                pos.m_positionX = me->GetPositionX();
                pos.m_positionY = me->GetPositionY();
                pos.m_positionZ = me->GetPositionZ();
                events.ScheduleEvent(EVENT_SUMMON, 1000);
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CORNER:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        vehicle->RemoveAllPassengers();
                    ++count;
                    if (count >= 3)
                    {
                        me->DespawnOrUnsummon(1);
                        events.ScheduleEvent(EVENT_LIGHTNING_STORM_CAST, 1);

                        if (Creature* assad = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ASAAD)))
                            assad->AI()->DoAction(ACTION_TELEPORT_START);
                    }
                    else
                        SummonTriggers();
                        events.ScheduleEvent(EVENT_CORNER, 2000);
                    break;
            }
        }

        void SummonTriggers()
        {
            if (Creature* walker = me->SummonCreature(NPC_GROUNDING_FIELD_TRIGGER, me->GetPositionX()+1, me->GetPositionY()+1, me->GetPositionZ()))
                if(Creature* trigger = me->SummonCreature(NPC_GROUNDING_FIELD_STATIONARY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
                    walker->EnterVehicle(me, 0);
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
                if (Creature* trigger = me->FindNearestCreature(NPC_GROUNDING_FIELD_TRIGGER, 10.0f, true))
                    who->CastSpell(trigger, SPELL_GROUNDING_FIELD_VISUAL, TRIGGERED_IGNORE_AURA_INTERRUPT_FLAGS);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON:
                        SummonTriggers();
                        events.ScheduleEvent(EVENT_CORNER, 1000);
                        break;
                    case EVENT_CORNER:
                        switch (count)
                        {
                            case 0:
                                distance = urand(11,13);
                                me->SetOrientation((me->GetOrientation()+(M_PI / 1.5)));
                                me->GetMotionMaster()->MovePoint(POINT_CORNER, me->GetPositionX()+cos(me->GetOrientation())*distance, me->GetPositionY()+sin(me->GetOrientation())*distance, me->GetPositionZ());
                                break;
                            case 1:
                                distance = urand(7,10);
                                me->SetOrientation((me->GetOrientation()+(M_PI / 1.5)));
                                me->GetMotionMaster()->MovePoint(POINT_CORNER, me->GetPositionX()+cos(me->GetOrientation())*distance, me->GetPositionY()+sin(me->GetOrientation())*distance, me->GetPositionZ());
                                break;
                            case 2:
                                me->GetMotionMaster()->MovePoint(POINT_CORNER, pos);
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    };
};

class PositionCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit PositionCheck(Unit* _caster) : caster(_caster) { }
        bool operator()(WorldObject* object)
        {
            if (object->GetTypeId() != TYPEID_PLAYER)
                return true;

            if (object->GetDistance2d(caster) > 4.f)
                return true;

            if (object->ToPlayer()->HasAura(87474) || object->ToPlayer()->HasAura(87726))
                return true;

            return false;
        }

    private:
        Unit* caster;
};

class spell_grounding_field_pulse : public SpellScriptLoader
{
    public:
        spell_grounding_field_pulse() : SpellScriptLoader("spell_grounding_field_pulse") { }

        class spell_grounding_field_pulse_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_grounding_field_pulse_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(PositionCheck(GetCaster()));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_grounding_field_pulse_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_grounding_field_pulse_SpellScript();
        }
};

class spell_supremacy_of_the_storm_damage : public SpellScriptLoader
{
    public:
        spell_supremacy_of_the_storm_damage() : SpellScriptLoader("spell_supremacy_of_the_storm_damage") { }

        class spell_supremacy_of_the_storm_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_supremacy_of_the_storm_damage_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                std::list<WorldObject*>::iterator it = unitList.begin();

                while(it != unitList.end())
                {
                    if (!GetCaster())
                        return;

                    WorldObject* unit = *it;

                    if (unit->ToUnit()->HasAura(87474) || unit->ToUnit()->HasAura(87726))
                        it = unitList.erase(it);
                    else
                        it++;
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_supremacy_of_the_storm_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_supremacy_of_the_storm_damage_SpellScript();
        }
};

class spell_supremacy_of_the_storm_visual : public SpellScriptLoader
{
    public:
        spell_supremacy_of_the_storm_visual() : SpellScriptLoader("spell_supremacy_of_the_storm_visual") { }

        class spell_supremacy_of_the_storm_visual_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_supremacy_of_the_storm_visual_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                Trinity::Containers::RandomResizeList(unitList, 15);

                std::list<WorldObject*>::iterator it = unitList.begin();

                while(it != unitList.end())
                {
                    WorldObject* unit = *it;

                    if (unit->FindNearestCreature(NPC_GROUNDING_FIELD_STATIONARY, 4.0f, true))
                        it = unitList.erase(it);
                    else
                        it++;
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_supremacy_of_the_storm_visual_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_supremacy_of_the_storm_visual_SpellScript();
        }
};

class spell_vp_static_cling : public SpellScriptLoader
{
    public:
        spell_vp_static_cling() : SpellScriptLoader("spell_vp_static_cling") { }

        class spell_vp_static_cling_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_vp_static_cling_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                std::list<WorldObject*>::iterator it = unitList.begin();

                while(it != unitList.end())
                {
                    if (!GetCaster())
                        return;

                    WorldObject* unit = *it;

                    if (unit->ToUnit()->HasUnitMovementFlag(MOVEMENTFLAG_FALLING) || unit->ToUnit()->HasUnitMovementFlag(MOVEMENTFLAG_FALLING_FAR) || unit->ToUnit()->HasUnitMovementFlag(MOVEMENTFLAG_PITCH_UP))
                        it = unitList.erase(it);
                    else
                        it++;
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_vp_static_cling_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_vp_static_cling_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

    SpellScript* GetSpellScript() const
    {
        return new spell_vp_static_cling_SpellScript();
    }
};

void AddSC_boss_asaad()
{
    new boss_asaad();
    new npc_field_walker();
    new spell_grounding_field_pulse();
    new spell_supremacy_of_the_storm_damage();
    new spell_supremacy_of_the_storm_visual();
    new spell_vp_static_cling();
}
