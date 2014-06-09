
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CreatureTextMgr.h"
#include "bastion_of_twilight.h"

enum Texts
{
    // Theralion
    SAY_THERALION_INTRO_1                       = 0,
    SAY_THERALION_INTRO_2                       = 1,
    SAY_THERALION_DAZZLING_DESTRUCTION          = 2,
    SAY_THERALION_DAZZLING_DESTRUCTION_ANNOUNCE = 3,
    SAY_THERALION_ENGULFING_MAGIC_ANNOUNCE      = 4,
    SAY_THERALION_DEEP_BREATH_REACTION          = 5,
    SAY_THERALION_SLAY                          = 6,
    SAY_THERALION_DEATH                         = 7,

    // Valiona
    SAY_VALIONA_INTRO_1                         = 0,
    SAY_VALIONA_INTRO_2                         = 1,
    SAY_VALIONA_BLACKOUT                        = 2, // Never used D:
    SAY_VALIONA_BLACKOUT_ANNOUNCE               = 3,
    SAY_VALIONA_DEEP_BREATH                     = 4,
    SAY_VALIONA_DEEP_BREATH_ANNOUNCE            = 5,
    SAY_VALIONA_SLAY                            = 6,
    SAY_VALIONA_DEATH                           = 7,
};

enum Spells
{
    // Valiona
    SPELL_DEVOURING_FLAMES_DUMMY_AOE        = 86832,
    SPELL_DEVOURING_FLAMES_DAMAGE           = 86844,
    SPELL_DEVOURING_FLAMES_AURA             = 86840, // Target Valiona

    SPELL_BLACKOUT_AOE                      = 86673,
    SPELL_BLACKOUT_AURA                     = 86788,
    SPELL_BLACKOUT_DAMAGE                   = 86825,

    // Theralion
    SPELL_TWILIGHT_BLAST                    = 86369,

    SPELL_DAZZLING_DESTRUCTION_SCRIPT       = 86379, // Target Dazzling Destruction Dummy
    SPELL_DAZZLING_DESTRUCTION_AOE          = 86380,
    SPELL_DAZZLING_DESTRUCTION_DUMMY        = 86408,
    SPELL_DAZZLING_DESTRUCTION_MISSILE      = 86386,
    SPELL_DAZZLING_DESTRUCTION_TRIGGERED    = 86406,
    SPELL_DAZZLING_DESTRUCTION_REALM        = 88436,
    SPELL_TWILIGHT_PROTECTION_BUFF          = 86415,
};

enum Events
{
    // Theralion
    EVENT_THERALION_INTRO_1 = 1,
    EVENT_THERALION_INTRO_2,
    EVENT_TAKEOFF_AT_AGGRO,
    EVENT_FLY_CENTER,
    EVENT_SCHEDULE_TWILIGHT_BLAST,
    EVENT_TWILIGHT_BLAST,
    EVENT_SCHEDULE_DAZZLING_DESTRUCTION,
    EVENT_DAZZLING_DESTRUCTION,
    EVENT_LAND,

    // Valiona
    EVENT_VALIONA_INTRO_1,
    EVENT_VALIONA_INTRO_2,
    EVENT_BLACKOUT,
    EVENT_DEVOURING_FLAMES_TARGETING,
    EVENT_DEVOURING_FLAMES,
    EVENT_CLEAR_DEVOURING_FLAMES,
    EVENT_TWILIGHT_SHIFT,
};

enum Phases
{
    PHASE_INTRO = 1,
    PHASE_BATTLE = 2,
};

enum Actions
{
    ACTION_TAKEOFF = 1,
    ACTION_LAND,
    ACTION_START_THERALION_INTRO,
    ACTION_START_VALIONA_INTRO,
    ACTION_CAST_DEVOURING_FLAMES,
    ACTION_CAST_DAZZLING_DESTRUCTION,
};

enum Points
{
    POINT_TAKEOFF = 1,
    POINT_LAND,
    POINT_CENTER,
};

Position const TwilFlamePos[90] = // 15 per row, 2 rows per side, 3 sides.
{
    // 1-30 for entrance, first breath.
    {-726.185f, -768.217f, 836.6880f},
    {-712.927f, -759.297f, 836.688f},
    {-729.71f, -750.193f, 836.693f},
    {-718.571f, -735.144f, 836.696f},
    {-731.519f, -729.622f, 835.106f},
    {-720.204f, -715.33f, 832.281f},
    {-718.553f, -702.101f, 831.897f},
    {-718.308f, -688.416f, 831.891f},
    {-719.734f, -676.143f, 831.892f},
    {-721.456f, -661.333f, 831.897f},
    {-722.821f, -649.582f, 833.176f},
    {-719.32f, -637.6f, 836.699f},
    {-723.196f, -622.605f, 836.692f},
    {-716.657f, -611.672f, 836.688f},
    {-715.665f, -600.11f, 836.685f},
    {-722.079f, -618.628f, 836.69f},
    {-709.057f, -668.355f, 831.899f},
    {-707.799f, -701.244f, 831.899f},
    {-711.942f, -719.573f, 834.601f},
    {-730.262f, -715.065f, 831.901f},
    {-731.211f, -703.507f, 831.896f},
    {-731.271f, -696.279f, 831.893f},
    {-731.779f, -684.027f, 831.889f},
    {-730.221f, -670.001f, 831.894f},
    {-731.618f, -660.124f, 831.897f},
    {-733.132f, -649.415f, 832.364f},
    {-733.703f, -636.535f, 835.993f},
    {-729.895f, -622.403f, 836.696f},
    {-727.821f, -609.092f, 836.692f},
    {-725.244f, -632.255f, 836.699f},
    // 30-60 for mid
    {-738.228f, -774.297f, 836.687f},
    {-747.187f, -711.44f, 831.897f},
    {-746.532f, -691.806f, 831.891f},
    {-746.461f, -681.971f, 831.89f},
    {-746.909f, -771.366f, 836.687f},
    {-746.978f, -668.307f, 831.893f},
    {-746.207f, -646.622f, 833.052f},
    {-750.661f, -735.852f, 836.699f},
    {-744.774f, -629.426f, 836.697f},
    {-740.922f, -601.492f, 836.688f},
    {-734.556f, -756.46f, 836.693f},
    {-749.818f, -751.318f, 836.694f},
    {-742.449f, -759.696f, 836.692f},
    {-741.821f, -746.749f, 836.698f},
    {-742.275f, -735.698f, 836.699f},
    {-739.995f, -725.004f, 833.588f},
    {-741.421f, -713.62f, 831.898f},
    {-740.577f, -702.188f, 831.893f},
    {-739.815f, -691.874f, 831.891f},
    {-739.103f, -682.223f, 831.89f},
    {-738.46f, -673.514f, 831.893f},
    {-737.876f, -665.608f, 831.896f},
    {-737.234f, -656.916f, 831.899f},
    {-736.475f, -646.637f, 833.048f},
    {-735.778f, -637.195f, 835.802f},
    {-735.17f, -628.958f, 836.697f},
    {-734.6f, -621.244f, 836.695f},
    {-749.068f, -724.66f, 833.581f},
    {-732.867f, -608.092f, 836.691f},
    {-732.764f, -596.374f, 836.687f},
    // 60-90 for exit
    {-766.844f, -614.003f, 836.689f},
    {-751.849f, -608.325f, 836.689f},
    {-755.589f, -627.736f, 836.695f},
    {-765.266f, -635.142f, 836.698f},
    {-755.655f, -640.214f, 835.515f},
    {-763.859f, -648.017f, 834.242f},
    {-774.417f, -650.346f, 835.237f},
    {-767.926f, -656.699f, 832.59f},
    {-756.128f, -657.912f, 831.899f},
    {-749.862f, -670.31f, 831.896f},
    {-759.005f, -666.729f, 831.897f},
    {-768.303f, -664.93f, 831.897f},
    {-767.196f, -675.072f, 831.892f},
    {-754.611f, -678.247f, 831.891f},
    {-754.229f, -690.564f, 831.891f},
    {-760.611f, -683.775f, 831.889f},
    {-774.04f, -682.983f, 831.89f},
    {-781.804f, -686.498f, 831.898f},
    {-770.858f, -691.417f, 831.893f},
    {-761.664f, -694.862f, 831.893f},
    {-752.508f, -699.213f, 831.894f},
    {-760.785f, -706.285f, 831.898f},
    {-771.937f, -701.638f, 831.899f},
    {-770.358f, -714.257f, 833.268f},
    {-756.803f, -721.699f, 833.392f},
    {-773.318f, -730.829f, 836.696f},
    {-756.708f, -737.369f, 836.696f},
    {-756.39f, -753.955f, 836.691f},
    {-759.558f, -765.119f, 836.686f},
    {-768.016f, -756.87f, 836.686f}
};

// 6442
class at_theralion_and_valiona : public AreaTriggerScript
{
public:
    at_theralion_and_valiona() : AreaTriggerScript("at_theralion_and_valiona") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (Creature* valiona = player->FindNearestCreature(BOSS_VALIONA, 500.0f, true))
            valiona->AI()->DoAction(ACTION_START_VALIONA_INTRO);
        sLog->outError(LOG_FILTER_GENERAL, "areatrigger got triggered");
        return true;
    }
};

class boss_valiona : public CreatureScript
{
public:
    boss_valiona() : CreatureScript("boss_valiona") { }

    struct boss_valionaAI : public BossAI
    {
        boss_valionaAI(Creature* creature) : BossAI(creature, DATA_THERALION_AND_VALIONA)
        {
            _isOnGround = true;
            _introDone = false;
        }

        bool _introDone;
        bool _isOnGround;

        void Reset()
        {
            _Reset();
            _isOnGround = true;
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            if (Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                theralion->AI()->AttackStart(who);
            events.ScheduleEvent(EVENT_DEVOURING_FLAMES_TARGETING, 30000);
            events.ScheduleEvent(EVENT_BLACKOUT, 5000);
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetDisableGravity(false);
            me->SetHover(false);
            _isOnGround = true;
            _EnterEvadeMode();
            _DespawnAtEvade();
        }

        void JustSummoned(Creature* /*summon*/)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            if (_isOnGround)
                Talk(SAY_VALIONA_DEATH);
            if (Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                me->Kill(theralion);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if(Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                theralion->SetHealth(theralion->GetHealth() - damage);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_START_VALIONA_INTRO:
                if (!_introDone)
                {
                    events.SetPhase(PHASE_INTRO);
                    if (Creature* chogall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_CHOGALL)))
                        chogall->AI()->TalkToMap(3);

                    events.ScheduleEvent(EVENT_VALIONA_INTRO_1, 8000);
                    if (Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                        theralion->AI()->DoAction(ACTION_START_THERALION_INTRO);
                    _introDone = true;
                }
                break;
            case ACTION_TAKEOFF:
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetHover(true);
                me->SetDisableGravity(true);
                Position pos;
                pos.Relocate(me);
                pos.m_positionZ += 17.0f;
                me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                _isOnGround = false;
                break;
            case ACTION_LAND:
                _isOnGround = true;
                break;
            case ACTION_CAST_DEVOURING_FLAMES:
                events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 1);
                break;
            default:
                break;
            }
        }

        void MovementInform(uint32 /*type*/, uint32 point)
        {
            switch (point)
            {
            case POINT_TAKEOFF:
                events.ScheduleEvent(EVENT_FLY_CENTER, 1);
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
                case EVENT_VALIONA_INTRO_1:
                    Talk(SAY_VALIONA_INTRO_1);
                    events.ScheduleEvent(EVENT_VALIONA_INTRO_2, 13000);
                    break;
                case EVENT_VALIONA_INTRO_2:
                    Talk(SAY_VALIONA_INTRO_2);
                    events.SetPhase(PHASE_BATTLE);
                    break;
                case EVENT_DEVOURING_FLAMES_TARGETING:
                    sLog->outError(LOG_FILTER_GENERAL, "Dummy AOE got casted");
                    DoCastAOE(SPELL_DEVOURING_FLAMES_DUMMY_AOE);
                    events.ScheduleEvent(EVENT_DEVOURING_FLAMES_TARGETING, 40000);
                    break;
                case EVENT_DEVOURING_FLAMES:
                    if (Creature* dummy = me->FindNearestCreature(NPC_DEVOURING_FLAMES_STALKER, 500.0f, true))
                    {
                        me->GetMotionMaster()->Clear();
                        me->SetFacingToObject(dummy);
                        me->AddUnitState(UNIT_STATE_CANNOT_TURN);
                        DoCast(me, SPELL_DEVOURING_FLAMES_AURA);
                        events.ScheduleEvent(EVENT_CLEAR_DEVOURING_FLAMES, 7600);
                    }
                    break;
                case EVENT_CLEAR_DEVOURING_FLAMES:
                    me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
                    me->GetMotionMaster()->MoveChase(me->getVictim());
                    break;
                case EVENT_BLACKOUT:
                    Talk(SAY_VALIONA_BLACKOUT);
                    Talk(SAY_VALIONA_BLACKOUT_ANNOUNCE);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        DoCast(target, SPELL_BLACKOUT_AOE);
                    events.ScheduleEvent(EVENT_BLACKOUT, 40000);
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
        return new boss_valionaAI(creature);
    }
};

class boss_theralion : public CreatureScript
{
public:
    boss_theralion() : CreatureScript("boss_theralion") { }

    struct boss_theralionAI : public BossAI
    {
        boss_theralionAI(Creature* creature) : BossAI(creature, DATA_THERALION_AND_VALIONA)
        {
            _isOnGround = true;
        }

        bool _isOnGround;

        void Reset()
        {
            _Reset();
            _isOnGround = true;
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TAKEOFF_AT_AGGRO, 100);
            events.ScheduleEvent(EVENT_SCHEDULE_DAZZLING_DESTRUCTION, 85000);
            if (Creature* valiona = me->FindNearestCreature(BOSS_VALIONA, 500.0f, true))
                valiona->AI()->AttackStart(who);
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetDisableGravity(false);
            me->SetHover(false);
            _isOnGround = true;
            _EnterEvadeMode();
            _DespawnAtEvade();
        }

        void JustRespawned()
        {
            instance->SetBossState(DATA_THERALION_AND_VALIONA, FAIL);
        }

        void JustSummoned(Creature* /*summon*/)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            if (_isOnGround)
                Talk(SAY_THERALION_DEATH);

            if (Creature* valiona = me->FindNearestCreature(BOSS_VALIONA, 500.0f, true))
                me->Kill(valiona);

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if(Creature* valiona = me->FindNearestCreature(BOSS_VALIONA, 500.0f, true))
                valiona->SetHealth(valiona->GetHealth() - damage);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_START_THERALION_INTRO:
                events.SetPhase(PHASE_INTRO);
                events.ScheduleEvent(EVENT_THERALION_INTRO_1, 14000);
                break;
            case ACTION_TAKEOFF:
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetHover(true);
                me->SetDisableGravity(true);
                Position pos;
                pos.Relocate(me);
                pos.m_positionZ += 17.0f;
                me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                _isOnGround = false;
                break;
            case ACTION_LAND:
                _isOnGround = true;
                break;
            case ACTION_CAST_DAZZLING_DESTRUCTION:
                me->CastStop();
                DoCastAOE(SPELL_DAZZLING_DESTRUCTION_DUMMY);
                break;
            default:
                break;
            }
        }

        void MovementInform(uint32 /*type*/, uint32 point)
        {
            switch (point)
            {
            case POINT_TAKEOFF:
                events.ScheduleEvent(EVENT_FLY_CENTER, 1);
                break;
            case POINT_CENTER:
                events.ScheduleEvent(EVENT_SCHEDULE_TWILIGHT_BLAST, 1);
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
                case EVENT_TAKEOFF_AT_AGGRO:
                    DoAction(ACTION_TAKEOFF);
                    break;
                case EVENT_FLY_CENTER:
                    if (Creature* stalker = me->FindNearestCreature(NPC_THERALION_FLIGHT_STALKER, 500.0f, true))
                    {
                        Position pos;
                        pos.Relocate(stalker);
                        me->GetMotionMaster()->MovePoint(POINT_CENTER, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), false);
                    }
                    break;
                case EVENT_THERALION_INTRO_1:
                    Talk(SAY_THERALION_INTRO_1);
                    events.ScheduleEvent(EVENT_THERALION_INTRO_2, 13000);
                    break;
                case EVENT_THERALION_INTRO_2:
                    Talk(SAY_THERALION_INTRO_2);
                    events.SetPhase(PHASE_BATTLE);
                    break;
                case EVENT_SCHEDULE_TWILIGHT_BLAST:
                    events.ScheduleEvent(EVENT_TWILIGHT_BLAST, 5000);
                    break;
                case EVENT_TWILIGHT_BLAST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        DoCast(target, SPELL_TWILIGHT_BLAST);
                    events.ScheduleEvent(EVENT_TWILIGHT_BLAST, 5000);
                    break;
                case EVENT_SCHEDULE_DAZZLING_DESTRUCTION:
                    me->CastStop();
                    events.CancelEvent(EVENT_SCHEDULE_TWILIGHT_BLAST);
                    DoCastAOE(SPELL_DAZZLING_DESTRUCTION_AOE);
                    events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 4100);
                    break;
                case EVENT_DAZZLING_DESTRUCTION:
                    DoCastAOE(SPELL_DAZZLING_DESTRUCTION_AOE);
                    events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 4100);
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
        return new boss_theralionAI(creature);
    }
};

class npc_tav_devouring_flames_dummy : public CreatureScript
{
public:
    npc_tav_devouring_flames_dummy() : CreatureScript("npc_tav_devouring_flames_dummy") { }

    struct npc_tav_devouring_flames_dummyAI : public ScriptedAI
    {
        npc_tav_devouring_flames_dummyAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (Creature* valiona = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                valiona->AI()->DoAction(ACTION_CAST_DEVOURING_FLAMES);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_devouring_flames_dummyAI(creature);
    }
};

class npc_tav_dazzling_destruction_stalker : public CreatureScript
{
public:
    npc_tav_dazzling_destruction_stalker() : CreatureScript("npc_tav_dazzling_destruction_stalker") { }

    struct npc_tav_dazzling_destruction_stalkerAI : public ScriptedAI
    {
        npc_tav_dazzling_destruction_stalkerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (Creature* theralion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THERALION)))
                theralion->AI()->DoAction(ACTION_CAST_DAZZLING_DESTRUCTION);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_dazzling_destruction_stalkerAI(creature);
    }
};

class spell_tav_devouring_flame_dummy_aoe : public SpellScriptLoader
{
public:
    spell_tav_devouring_flame_dummy_aoe() : SpellScriptLoader("spell_tav_devouring_flame_dummy_aoe") { }

    class spell_tav_devouring_flame_dummy_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_devouring_flame_dummy_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
            targets.clear();
            targets.push_back(target);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_devouring_flame_dummy_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_devouring_flame_dummy_aoe_SpellScript();
    }
};

class spell_tav_devouring_flames : public SpellScriptLoader
{
public:
    spell_tav_devouring_flames() : SpellScriptLoader("spell_tav_devouring_flames") { }

    class spell_tav_devouring_flames_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_devouring_flames_SpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                {
                    float distance = GetCaster()->GetDistance2d(GetHitUnit());
                    uint64 damage = GetEffectValue();
                    uint64 newdamage = 0;

                    if (distance > 1.0f)
                        newdamage = damage - (distance * 2000);
                    else
                        newdamage = damage;

                    SetHitDamage(newdamage);
                }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_tav_devouring_flames_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_devouring_flames_SpellScript();
    }
};

class spell_tav_blackout_aoe : public SpellScriptLoader
{
public:
    spell_tav_blackout_aoe() : SpellScriptLoader("spell_tav_blackout_aoe") { }

    class spell_tav_blackout_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_blackout_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 2); // 2 targets at the same time
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->AddAura(SPELL_BLACKOUT_AURA, target);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_blackout_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_tav_blackout_aoe_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_blackout_aoe_SpellScript();
    }
};

class spell_tav_blackout_aura : public SpellScriptLoader
{
public:
    spell_tav_blackout_aura() : SpellScriptLoader("spell_tav_blackout_aura") { }

    class spell_tav_blackout_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tav_blackout_aura_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetOwner()->ToUnit())
                owner->CastSpell(owner, SPELL_BLACKOUT_DAMAGE, true);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_tav_blackout_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tav_blackout_aura_AuraScript();
    }
};

class spell_tav_dazzling_destruction_aoe : public SpellScriptLoader
{
public:
    spell_tav_dazzling_destruction_aoe() : SpellScriptLoader("spell_tav_dazzling_destruction_aoe") { }

    class spell_tav_dazzling_destruction_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_dazzling_destruction_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
            targets.clear();
            targets.push_back(target);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_dazzling_destruction_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_dazzling_destruction_aoe_SpellScript();
    }
};

class spell_tav_dazzling_destruction_cast : public SpellScriptLoader
{
public:
    spell_tav_dazzling_destruction_cast() : SpellScriptLoader("spell_tav_dazzling_destruction_cast") { }

    class spell_tav_dazzling_destruction_cast_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_dazzling_destruction_cast_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->CastSpell(target, SPELL_DAZZLING_DESTRUCTION_MISSILE, false);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_tav_dazzling_destruction_cast_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_dazzling_destruction_cast_SpellScript();
    }
};

void AddSC_boss_theralion_and_valiona()
{
    new at_theralion_and_valiona();
    new boss_valiona();
    new boss_theralion();
    new npc_tav_devouring_flames_dummy();
    new npc_tav_dazzling_destruction_stalker();
    new spell_tav_devouring_flame_dummy_aoe();
    new spell_tav_devouring_flames();
    new spell_tav_blackout_aoe();
    new spell_tav_blackout_aura();
    new spell_tav_dazzling_destruction_aoe();
    new spell_tav_dazzling_destruction_cast();
}
