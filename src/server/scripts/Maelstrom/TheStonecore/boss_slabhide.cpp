
#include "ScriptPCH.h"
#include "the_stonecore.h"

enum Spells
{
    // Intro
    SPELL_FACE_RANDOM_PLAYER_SCRIPT     = 82530,
    SPELL_FACE_RANDOM_PLAYER_TRIGGERED  = 82532,

    SPELL_SUMMON_STALACTITE             = 80650,
    SPELL_STALACTITE_GROUND_VISUAL      = 80654,
    SPELL_STALACTITE_MISSILE            = 80643,

    // Stalactite Gauntlet
    SPELL_STALCTITE_AURA                = 81027,
    SPELL_STALACTITE_DUMMY              = 81035,
    SPELL_STALACTITE_SUMMON             = 81028,

    // Slabhide Encounter
    SPELL_SUMMON_STALACTITE_AURA        = 80656,

    SPELL_LAVA_FISSURE_SUMMON           = 80803,
    SPELL_LAVA_FISSURE_SUMMON_VISUAL    = 80798,
    SPELL_ERUPTION                      = 80800,

    SPELL_CRYSTAL_STORM_AURA            = 92305,
    SPELL_CRYSTAL_STORM_DAMAGE          = 92265,

    SPELL_SAND_BLAST                    = 80807,
};

enum Events
{
    EVENT_LAND_HOME = 1,
    EVENT_LANDED_HOME,
    EVENT_ROAR,
    EVENT_STALACTITE_CRASH,
    EVENT_LAVA_FISSURE,
    EVENT_ERUPTION,
    EVENT_MOVE_CENTER,
    EVENT_TAKEOFF,
    EVENT_LAND,
    EVENT_SUMMON_STALACTITE,
    EVENT_PREPARE_CRYSTAL_STORM,
    EVENT_CRYSTAL_STORM,
    EVENT_CRYSTAL_STORM_AURA,
    EVENT_ATTACK,
    EVENT_SAND_BLAST,
};

enum Points
{
    POINT_TAKEOFF = 1,
    POINT_LAND,
    POINT_CENTER,
    POINT_HOME,
    POINT_LAND_HOME,
};

enum Actions
{
    ACTION_MOVE_TO_ARENA = 1,
};

enum Phases
{
    PHASE_INTRO = 1,
    PHASE_COMBAT,
};

// 6070 - Stalagnite Race

class at_tsc_slabhide_event : public AreaTriggerScript
{
    public:
        at_tsc_slabhide_event() : AreaTriggerScript("at_tsc_slabhide_event") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
                //if (!instance->GetData(DATA_SLABHIDE_PRE_EVENT))
                //{
                    if (Creature* slabhide = ObjectAccessor::GetCreature(*player, instance->GetData64(BOSS_SLABHIDE)))
                        slabhide->AI()->DoAction(ACTION_MOVE_TO_ARENA);
                    //instance->SetData(DATA_SLABHIDE_PRE_EVENT, 1);
                //}
            return true;
        }
};

Position const LandPos = {1282.699f, 1229.770f, 258.404f, 3.822f};
Position const HomePos = {1282.699f, 1229.770f, 247.072f, 3.822f};
Position const TakeoffPos = {1280.73f, 1212.31f, 257.3837f};
Position const CenterPos = {1280.73f, 1212.31f, 247.384f};

class boss_slabhide : public CreatureScript
{
public:
    boss_slabhide() : CreatureScript("boss_slabhide") { }

    struct boss_slabhideAI : public BossAI
    {
        boss_slabhideAI(Creature* creature) : BossAI(creature, DATA_SLABHIDE)
        {
            _gauntletStarted = false;
        }

        bool _gauntletStarted;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_LAVA_FISSURE, 7700);
            events.ScheduleEvent(EVENT_MOVE_CENTER, 12000);
            events.ScheduleEvent(EVENT_SAND_BLAST, 23000);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SetBossState(DATA_SLABHIDE, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_MOVE_TO_ARENA:
                    me->GetMotionMaster()->MovePoint(POINT_HOME, LandPos);
                    me->SetHomePosition(HomePos);
                    events.SetPhase(PHASE_INTRO);
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case POINT_HOME:
                    events.ScheduleEvent(EVENT_LAND_HOME, 1);
                    break;
                case POINT_LAND_HOME:
                    events.ScheduleEvent(EVENT_LANDED_HOME, 1);
                    break;
                case POINT_CENTER:
                    events.ScheduleEvent(EVENT_TAKEOFF, 1);
                    break;
                case POINT_TAKEOFF:
                    events.ScheduleEvent(EVENT_SUMMON_STALACTITE, 1000);
                    break;
                case POINT_LAND:
                    events.ScheduleEvent(EVENT_PREPARE_CRYSTAL_STORM, 1);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                        break;
                    case EVENT_LAND_HOME:
                        me->SetFacingTo(3.822f);
                        me->GetMotionMaster()->MoveLand(POINT_LAND_HOME, HomePos);
                        break;
                    case EVENT_LANDED_HOME:
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        events.ScheduleEvent(EVENT_ROAR, 1000);
                        break;
                    case EVENT_ROAR:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        events.SetPhase(PHASE_COMBAT);
                        events.Reset();
                        break;
                    case EVENT_LAVA_FISSURE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_LAVA_FISSURE_SUMMON);
                        events.ScheduleEvent(EVENT_LAVA_FISSURE, 7000);
                        break;
                    case EVENT_MOVE_CENTER:
                        events.DelayEvents(10000);
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        me->GetMotionMaster()->MovePoint(POINT_CENTER, CenterPos);
                        break;
                    case EVENT_TAKEOFF:
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->SetHover(true);
                        me->AttackStop();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, TakeoffPos);
                        break;
                    case EVENT_SUMMON_STALACTITE:
                        me->Relocate(CenterPos);
                        DoCastAOE(SPELL_SUMMON_STALACTITE_AURA);
                        events.ScheduleEvent(EVENT_LAND, 8200);
                        break;
                    case EVENT_LAND:
                        me->SetCanFly(false);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->GetMotionMaster()->MoveLand(POINT_LAND, CenterPos);
                        events.ScheduleEvent(EVENT_MOVE_CENTER, 50000);
                        break;
                    case EVENT_PREPARE_CRYSTAL_STORM:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (IsHeroic())
                            events.ScheduleEvent(EVENT_CRYSTAL_STORM_AURA, 1000);
                        break;
                    case EVENT_CRYSTAL_STORM_AURA:
                        DoCastAOE(SPELL_CRYSTAL_STORM_AURA);
                        events.ScheduleEvent(EVENT_CRYSTAL_STORM, 15000);
                        break;
                    case EVENT_CRYSTAL_STORM:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoCastAOE(SPELL_CRYSTAL_STORM_DAMAGE);
                        break;
                    case EVENT_SAND_BLAST:
                        DoCastAOE(SPELL_SAND_BLAST);
                        events.ScheduleEvent(EVENT_SAND_BLAST, 11400);
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
        return new boss_slabhideAI (creature);
    }
};

class npc_tsc_stalactit_dummy : public CreatureScript
{
public:
    npc_tsc_stalactit_dummy() : CreatureScript("npc_tsc_stalactit_dummy") { }

    struct npc_tsc_stalactit_dummyAI : public PassiveAI
    {
        npc_tsc_stalactit_dummyAI(Creature* creature) : PassiveAI(creature)
        {
        }

        void Reset()
        {
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_STALACTITE_DUMMY)
                DoCastAOE(SPELL_STALACTITE_SUMMON);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tsc_stalactit_dummyAI (creature);
    }
};

class npc_tsc_stalactit : public CreatureScript
{
public:
    npc_tsc_stalactit() : CreatureScript("npc_tsc_stalactit") { }

    struct npc_tsc_stalactitAI : public PassiveAI
    {
        npc_tsc_stalactitAI(Creature* creature) : PassiveAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCastAOE(SPELL_STALACTITE_GROUND_VISUAL);
            events.ScheduleEvent(EVENT_STALACTITE_CRASH, 3000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_STALACTITE_CRASH:
                        DoCastAOE(SPELL_STALACTITE_MISSILE);
                        me->DespawnOrUnsummon(10000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tsc_stalactitAI (creature);
    }
};

class npc_tsc_lava_fissure : public CreatureScript
{
public:
    npc_tsc_lava_fissure() : CreatureScript("npc_tsc_lava_fissure") { }

    struct npc_tsc_lava_fissureAI : public PassiveAI
    {
        npc_tsc_lava_fissureAI(Creature* creature) : PassiveAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_DISABLE_MOVE);
            DoCastAOE(SPELL_LAVA_FISSURE_SUMMON_VISUAL);
            if (me->GetMap()->IsHeroic())
                events.ScheduleEvent(EVENT_ERUPTION, 3000);
            else
                events.ScheduleEvent(EVENT_ERUPTION, 5000);

        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ERUPTION:
                        DoCastAOE(SPELL_ERUPTION);
                        if (me->GetMap()->IsHeroic())
                            me->DespawnOrUnsummon(30000);
                        else
                            me->DespawnOrUnsummon(10000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tsc_lava_fissureAI (creature);
    }
};

// 92300 Crystal Storm
class spell_tsc_crystal_storm : public SpellScriptLoader
{
public:
    spell_tsc_crystal_storm() : SpellScriptLoader("spell_tsc_crystal_storm") { }

    class spell_tsc_crystal_storm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tsc_crystal_storm_SpellScript);

        class BehindStalaktiteSelector
        {
        public:
            BehindStalaktiteSelector(WorldObject* unit) : caster(unit) {}

            bool operator() (WorldObject* unit)
            {
                if (Unit* target = unit->ToUnit())
                {
                    std::list<GameObject*> blockList;
                    caster->GetGameObjectListWithEntryInGrid(blockList, GO_STALAKTIT, 300.0f);
                    if (!blockList.empty())
                    {
                        for (std::list<GameObject*>::const_iterator itr = blockList.begin(); itr != blockList.end(); ++itr)
                        {
                            if (!(*itr)->IsInvisibleDueToDespawn())
                            {
                                if ((*itr)->IsInBetween(caster, target, 2.0f))
                                    return true;
                            }
                        }
                    }
                }
                return false;
            }

        private:
            WorldObject* caster;
        };

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            if (Unit* caster = GetCaster())
                unitList.remove_if(BehindStalaktiteSelector(caster));
            else
                unitList.clear();
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tsc_crystal_storm_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tsc_crystal_storm_SpellScript();
    }
};

void AddSC_boss_slabhide()
{
    new at_tsc_slabhide_event();
    new boss_slabhide();
    new npc_tsc_stalactit_dummy();
    new npc_tsc_stalactit();
    new npc_tsc_lava_fissure();
    new spell_tsc_crystal_storm();
}
