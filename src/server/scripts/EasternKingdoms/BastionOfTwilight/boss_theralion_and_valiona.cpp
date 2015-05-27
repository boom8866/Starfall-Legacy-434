
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
    SAY_VALIONA_BLACKOUT                        = 2,
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
    SPELL_DEVOURING_FLAMES_AURA             = 86840,
    SPELL_BLACKOUT_AOE                      = 86673,
    SPELL_BLACKOUT_AURA                     = 86788,
    SPELL_BLACKOUT_DAMAGE                   = 86825,
    SPELL_TWILIGHT_METEORITE_AOE            = 88518,
    SPELL_TWILIGHT_METEORITE_MISSILE        = 86013,
    SPELL_SPEED_BURST                       = 86077,
    SPELL_DEEP_BREATH_SCRIPT                = 86059,
    SPELL_TWILIGHT_FLAMES_TRIGGER           = 86194,
    SPELL_TWILIGHT_SHIFT                    = 86293,

    SPELL_TWILIGHT_PROTECTION_BUFF          = 86415,
    SPELL_SUMMON_COLLAPSING_PORTAL          = 86289,

    // Theralion
    SPELL_TWILIGHT_BLAST                    = 86369,
    SPELL_DAZZLING_DESTRUCTION_SCRIPT       = 86379, // Target Dazzling Destruction Dummy
    SPELL_DAZZLING_DESTRUCTION_AOE          = 86380,
    SPELL_DAZZLING_DESTRUCTION_DUMMY        = 86408,
    SPELL_DAZZLING_DESTRUCTION_MISSILE      = 86386,
    SPELL_DAZZLING_DESTRUCTION_TRIGGERED    = 86406,
    SPELL_DAZZLING_DESTRUCTION_REALM_DAMAGE = 93063,
    SPELL_ENGULFING_MAGIC_AOE               = 86607,
    SPELL_ENGULFING_MAGIC_PROC              = 86631,
    SPELL_FABULOUS_FLAMES_AOE               = 86495,
    SPELL_FABULOUS_FLAMES_MISSILE           = 86497,

    // Collapsing Twilight Portal
    SPELL_COLLAPSING_TWILIGHT_PORTAL_SCRIPT = 86296,
    SPELL_COLLAPSING_TWILIGHT_PORTAL        = 86291,
    SPELL_TWILIGHT_SHIFT_SCRIPT             = 86293,

    // Unstable Twilight
    SPELL_UNSTABLE_TWILIGHT                 = 86302,
    SPELL_UNSTABLE_TWILIGHT_TRIGGERED       = 86301,
    SPELL_UNSTABLE_TWILIGHT_DAMAGE          = 86305,

    // Twilight Shift
    SPELL_TWILIGHT_SHIFT_1                  = 86202,
    SPELL_TWILIGHT_SHIFT_2                  = 92889,
    SPELL_TWILIGHT_SHIFT_3                  = 92890,
    SPELL_TWILIGHT_SHIFT_4                  = 92891,
    SPELL_TWILIGHT_SHIFT_5                  = 88436,
    SPELL_TWILIGHT_SHIFT_6                  = 92892,
    SPELL_TWILIGHT_SHIFT_7                  = 92893,
    SPELL_TWILIGHT_SHIFT_8                  = 92894,
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
    EVENT_ENGULFING_MAGIC,
    EVENT_FABULOUS_FLAMES,
    EVENT_LAND,
    EVENT_LANDED,
    EVENT_ATTACK,

    // Valiona
    EVENT_VALIONA_INTRO_1,
    EVENT_VALIONA_INTRO_2,
    EVENT_BLACKOUT,
    EVENT_DEVOURING_FLAMES_TARGETING,
    EVENT_DEVOURING_FLAMES,
    EVENT_CLEAR_DEVOURING_FLAMES,
    EVENT_TWILIGHT_SHIFT,
    EVENT_TAKEOFF,
    EVENT_FLY_UP,
    EVENT_TWILIGHT_METEORITE,
    EVENT_SCHEDULE_DEEP_BREATH,
    EVENT_PREPARE_TO_LAND,

    EVENT_MOVE_DEEP_BREATH,
    EVENT_PREPARE_NEXT_BREATH,
    EVENT_CHECK_VALIONA,

    // Generic
    EVENT_SUMMON_COLLAPSING_PORTAL,
    EVENT_ACTIVATE_UNSTABLE_TWILIGHT,
    EVENT_CHECK_PLAYER,
    EVENT_MOVE_RANDOM,
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
    ACTION_RESET_GROUND_EVENTS,
    ACTION_RESET_AIR_EVENTS,
    ACTION_TAKEOFF_2,
};

enum Points
{
    POINT_TAKEOFF = 1,
    POINT_LAND,
    POINT_CENTER,
    POINT_UP,
    POINT_LAND_PREPARE,
    POINT_TAKEOFF_2,
    POINT_DEEP_BREATH_PREPARE,
    POINT_DEEP_BREATH_MOVE,

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

Position const PortalPositions[] =
{
    {-777.6563f, -682.3993f, 832.8972f, 4.747295f},
    {-768.804f, -643.29f, 837.2373f, 4.747295f},
    {-724.913f, -701.007f, 832.899f, 4.729842f},
    {-740.724f, -684.797f, 832.8899f, 4.747295f},
    {-715.116f, -642.521f, 837.0091f, 4.729842f},
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
        return true;
    }
};

class TwilightShiftCheck
{
public:
    TwilightShiftCheck() { }

    bool operator()(WorldObject* object)
    {
        return (object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_1) || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_2)
            || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_3) || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_4)
            || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_5) || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_6)
            || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_7) || object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_8));
    }
};

class NoTwilightShiftCheck
{
public:
    NoTwilightShiftCheck() { }

    bool operator()(WorldObject* object)
    {
        return (!object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_1) && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_2)
            && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_3) && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_4)
            && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_5) && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_6)
            && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_7) && !object->ToUnit()->HasAura(SPELL_TWILIGHT_SHIFT_8));
    }
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
            _breathCounter = 0;
            _preparationRandom = 0;
            _pathSelected = 0;
            _sideLeft = true;
        }

        bool _introDone;
        bool _isOnGround;
        uint8 _breathCounter;
        bool _sideLeft;
        uint8 _pathSelected, _preparationRandom;

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
            events.ScheduleEvent(EVENT_BLACKOUT, 6000);
            events.ScheduleEvent(EVENT_SUMMON_COLLAPSING_PORTAL, 1);
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_THERALION_AND_VALIONA, FAIL);
            instance->DoCastSpellOnPlayers(SPELL_TWILIGHT_SHIFT_SCRIPT);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetDisableGravity(false);
            me->SetHover(false);
            events.Reset();
            summons.DespawnAll();
            _isOnGround = true;
            _breathCounter = 0;
            _EnterEvadeMode();
            _DespawnAtEvade();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (_isOnGround)
                Talk(SAY_VALIONA_DEATH);
            if (Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                me->Kill(theralion);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoCastSpellOnPlayers(SPELL_TWILIGHT_SHIFT_SCRIPT);
            summons.DespawnAll();
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

                    events.ScheduleEvent(EVENT_VALIONA_INTRO_1, 6000);
                    if (Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                        theralion->AI()->DoAction(ACTION_START_THERALION_INTRO);
                    _introDone = true;
                }
                break;
            case ACTION_TAKEOFF:
                me->CastStop();
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_TAKEOFF, 100);
                break;
            case ACTION_LAND:
            {
                if (Creature* theralion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THERALION)))
                    theralion->AI()->DoAction(ACTION_TAKEOFF_2);

                me->SetSpeed(MOVE_RUN, me->GetCreatureTemplate()->speed_run);

                events.CancelEvent(EVENT_TWILIGHT_METEORITE);
                _isOnGround = true;
                Position pos;
                pos.Relocate(me);
                float x = me->GetPositionX();
                float y = me->GetPositionY();
                float z = me->GetPositionZ();
                float ground = me->GetMap()->GetWaterOrGroundLevel(x, y, z, &ground);
                pos.m_positionX = x;
                pos.m_positionY = y;
                pos.m_positionZ = ground;
                me->GetMotionMaster()->MoveLand(POINT_LAND, pos);
                break;
            }
            case ACTION_CAST_DEVOURING_FLAMES:
                events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 1);
                break;
            case ACTION_RESET_GROUND_EVENTS:
                events.CancelEvent(EVENT_DEVOURING_FLAMES_TARGETING);
                events.CancelEvent(EVENT_BLACKOUT);
                break;
            default:
                break;
            }
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (point)
            {
            case POINT_TAKEOFF:
                events.ScheduleEvent(EVENT_FLY_UP, 1);
                events.CancelEvent(EVENT_DEVOURING_FLAMES_TARGETING);
                events.CancelEvent(EVENT_BLACKOUT);
                break;
            case POINT_LAND:
                events.ScheduleEvent(EVENT_LANDED, 1);
                break;
            case POINT_UP:
                events.ScheduleEvent(EVENT_TWILIGHT_METEORITE, 12000);
                events.ScheduleEvent(EVENT_SCHEDULE_DEEP_BREATH, 85000);
                break;
            case POINT_LAND_PREPARE:
                events.ScheduleEvent(EVENT_LAND, 1);
                break;
            case POINT_DEEP_BREATH_PREPARE:
                if (_breathCounter < 3)
                    events.ScheduleEvent(EVENT_MOVE_DEEP_BREATH, 2000);
                break;
            case POINT_DEEP_BREATH_MOVE:
                if (_breathCounter == 0)
                {
                    events.ScheduleEvent(EVENT_PREPARE_NEXT_BREATH, 100);
                    _breathCounter++;
                }
                else if (_breathCounter == 1)
                {
                    events.ScheduleEvent(EVENT_PREPARE_NEXT_BREATH, 100);
                    _breathCounter++;
                }
                else if (_breathCounter == 2)
                {
                    events.ScheduleEvent(EVENT_PREPARE_TO_LAND, 100);
                    _breathCounter = 0;
                }
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
                    DoCastAOE(SPELL_DEVOURING_FLAMES_DUMMY_AOE);
                    events.ScheduleEvent(EVENT_DEVOURING_FLAMES_TARGETING, 40000);
                    break;
                case EVENT_DEVOURING_FLAMES:
                    DoCast(me, SPELL_DEVOURING_FLAMES_AURA);
                    events.ScheduleEvent(EVENT_CLEAR_DEVOURING_FLAMES, 7600);
                    break;
                case EVENT_CLEAR_DEVOURING_FLAMES:
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
                    me->GetMotionMaster()->MoveChase(me->getVictim());
                    break;
                case EVENT_BLACKOUT:
                    Talk(SAY_VALIONA_BLACKOUT_ANNOUNCE);
                    DoCast(SPELL_BLACKOUT_AOE);
                    events.ScheduleEvent(EVENT_BLACKOUT, 45000);
                    break;
                case EVENT_LANDED:
                    me->SetDisableGravity(false);
                    me->SetHover(false);
                    events.ScheduleEvent(EVENT_ATTACK, 1000);
                    break;
                case EVENT_ATTACK:
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_DEVOURING_FLAMES_TARGETING, 30000);
                    events.ScheduleEvent(EVENT_BLACKOUT, 6000);
                    break;
                case EVENT_FLY_UP:
                {
                    Position pos;
                    pos.Relocate(me);
                    float x = me->GetPositionX();
                    float y = me->GetPositionY();
                    if (Creature* stalker = me->FindNearestCreature(NPC_THERALION_FLIGHT_STALKER, 500.0f))
                    {
                        float z = stalker->GetPositionZ();
                        me->GetMotionMaster()->MovePoint(POINT_UP, x, y, z, false);
                    }
                    break;
                }
                case EVENT_TAKEOFF:
                {
                    me->SetHover(true);
                    me->SetDisableGravity(true);
                    Position pos;
                    pos.Relocate(me);
                    pos.m_positionZ += 17.0f;
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                    _isOnGround = false;
                    break;
                 }
                case EVENT_TWILIGHT_METEORITE:
                    DoCast(me, SPELL_TWILIGHT_METEORITE_AOE);
                    events.ScheduleEvent(EVENT_TWILIGHT_METEORITE, 6200);
                    break;
                case EVENT_SCHEDULE_DEEP_BREATH:
                    me->CastStop();
                    if (Creature* theralion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THERALION)))
                        theralion->AI()->DoAction(ACTION_RESET_GROUND_EVENTS);
                    events.CancelEvent(EVENT_TWILIGHT_METEORITE);
                    TalkToMap(SAY_VALIONA_DEEP_BREATH);
                    TalkToMap(SAY_VALIONA_DEEP_BREATH_ANNOUNCE);
                    _preparationRandom = urand(0, 1);
                    if (_preparationRandom == 1)
                        SelectPreparationRightToLeft(urand(1, 3));
                    else
                        SelectPreparationLeftToRight(urand(1, 3));
                    break;
                case EVENT_MOVE_DEEP_BREATH:
                    DoCast(me, SPELL_DEEP_BREATH_SCRIPT);
                    DoCast(me, SPELL_SPEED_BURST);
                    SelectPathForBreath(_pathSelected);
                    break;
                case EVENT_PREPARE_TO_LAND:
                    me->RemoveAurasDueToSpell(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_LAND_PREPARE, -740.937f, -601.679f, 852.031f, false);
                    break;
                case EVENT_LAND:
                    DoAction(ACTION_LAND);
                    break;
                case EVENT_SUMMON_COLLAPSING_PORTAL:
                    if (Creature* portal = me->SummonCreature(NPC_COLLAPSING_TWILIGHT_PORTAL, PortalPositions[urand(0, 4)], TEMPSUMMON_TIMED_DESPAWN, 60000))
                    {
                        portal->SetPhaseMask(2, true);
                        portal->CastSpell(portal, SPELL_COLLAPSING_TWILIGHT_PORTAL, true);
                    }
                    events.ScheduleEvent(EVENT_SUMMON_COLLAPSING_PORTAL, 60000);
                    break;
                case EVENT_PREPARE_NEXT_BREATH:
                    me->RemoveAurasDueToSpell(SPELL_SPEED_BURST);
                    _sideLeft ? SelectPreparationLeftToRight(urand(1, 3)) : SelectPreparationRightToLeft(urand(1, 3));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        // Theralion Side (Left)
        void SelectPreparationLeftToRight(uint8 selected)
        {
            switch (selected)
            {
                case 1:
                    // Theralion Left
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_PREPARE, -757.414f, -767.221f, me->GetPositionZ(), false);
                    _pathSelected = 6;
                    break;
                case 2:
                    // Theralion Center
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_PREPARE, -740.481f, -770.554f, me->GetPositionZ(), false);
                    _pathSelected = 5;
                    break;
                case 3:
                    // Theralion Right
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_PREPARE, -724.299f, -769.867f, me->GetPositionZ(), false);
                    _pathSelected = 4;
                    break;
                default:
                    break;
            }
        }

        // Valiona Side (Right)
        void SelectPreparationRightToLeft(uint8 selected)
        {
            switch (selected)
            {
                case 1:
                    // Valiona Left
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_PREPARE, -725.369f, -600.206f, me->GetPositionZ(), false);
                    _pathSelected = 3;
                    break;
                case 2:
                    // Valiona Center
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_PREPARE, -740.937f, -601.679f, me->GetPositionZ(), false);
                    _pathSelected = 2;
                    break;
                case 3:
                    // Valiona Right
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_PREPARE, -759.226f, -603.424f, me->GetPositionZ(), false);
                    _pathSelected = 1;
                    break;
                default:
                    break;
            }
        }

        // Path Selector (Final)
        void SelectPathForBreath(uint8 pathSelected)
        {
            if (pathSelected >= 4)
                _sideLeft = false;

            if (pathSelected <= 3)
                _sideLeft = true;

            switch (pathSelected)
            {
                case 1:
                {
                    DoCast(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_MOVE, -757.414f, -767.221f, me->GetPositionZ(), false);
                    for (uint16 i = 61; i < 90; i++)
                        me->SummonCreature(NPC_TWILIGHT_FLAME, TwilFlamePos[i].GetPositionX(), TwilFlamePos[i].GetPositionY(), TwilFlamePos[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                    break;
                }
                case 2:
                {
                    DoCast(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_MOVE, -740.481f, -770.554f, me->GetPositionZ(), false);
                    for (uint16 i = 31; i < 61; i++)
                        me->SummonCreature(NPC_TWILIGHT_FLAME, TwilFlamePos[i].GetPositionX(), TwilFlamePos[i].GetPositionY(), TwilFlamePos[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                    break;
                }
                case 3:
                {
                    DoCast(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_MOVE, -724.299f, -769.867f, me->GetPositionZ(), false);
                    for (uint16 i = 1; i < 31; i++)
                        me->SummonCreature(NPC_TWILIGHT_FLAME, TwilFlamePos[i].GetPositionX(), TwilFlamePos[i].GetPositionY(), TwilFlamePos[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                    break;
                }
                case 4:
                    DoCast(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_MOVE, -725.369f, -600.206f, me->GetPositionZ(), false);
                    for (uint16 i = 1; i < 31; i++)
                        me->SummonCreature(NPC_TWILIGHT_FLAME, TwilFlamePos[i].GetPositionX(), TwilFlamePos[i].GetPositionY(), TwilFlamePos[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                    break;
                case 5:
                    DoCast(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_MOVE, -740.937f, -601.679f, me->GetPositionZ(), false);
                    for (uint16 i = 31; i < 61; i++)
                        me->SummonCreature(NPC_TWILIGHT_FLAME, TwilFlamePos[i].GetPositionX(), TwilFlamePos[i].GetPositionY(), TwilFlamePos[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                    break;
                case 6:
                    DoCast(SPELL_SPEED_BURST);
                    me->GetMotionMaster()->MovePoint(POINT_DEEP_BREATH_MOVE, -759.226f, -603.424f, me->GetPositionZ(), false);
                    for (uint16 i = 61; i < 90; i++)
                        me->SummonCreature(NPC_TWILIGHT_FLAME, TwilFlamePos[i].GetPositionX(), TwilFlamePos[i].GetPositionY(), TwilFlamePos[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                    break;
                default:
                    break;
            }
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
            _dazzlingDestructionCasts = 0;
        }

        bool _isOnGround;
        uint8 _dazzlingDestructionCasts;

        void Reset()
        {
            _Reset();
            _isOnGround = true;
            _dazzlingDestructionCasts = 0;
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
            instance->SetBossState(DATA_THERALION_AND_VALIONA, FAIL);
            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetDisableGravity(false);
            me->SetHover(false);
            _isOnGround = true;
            _dazzlingDestructionCasts = 0;
            _EnterEvadeMode();
            _DespawnAtEvade();
        }

        void JustRespawned()
        {
            instance->SetBossState(DATA_THERALION_AND_VALIONA, NOT_STARTED);
        }

        void JustSummoned(Creature* /*summon*/)
        {
        }

        void JustDied(Unit* killer)
        {
            if (_isOnGround)
                Talk(SAY_THERALION_DEATH);

            if (Creature* valiona = me->FindNearestCreature(BOSS_VALIONA, 500.0f, true))
                killer->Kill(valiona);

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
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
                events.ScheduleEvent(EVENT_THERALION_INTRO_1, 12000);
                break;
            case ACTION_TAKEOFF:
                me->CastStop();
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
            {
                events.Reset();
                _isOnGround = true;
                Position pos;
                pos.Relocate(me);
                float x = me->GetPositionX();
                float y = me->GetPositionY();
                float z = me->GetPositionZ();
                float ground = me->GetMap()->GetWaterOrGroundLevel(x, y, z, &ground);
                pos.m_positionX = x;
                pos.m_positionY = y;
                pos.m_positionZ = ground;
                me->GetMotionMaster()->MoveLand(POINT_LAND, pos);
                _dazzlingDestructionCasts = 0;
                break;
            }
            case ACTION_CAST_DAZZLING_DESTRUCTION:
                DoCast(me, SPELL_DAZZLING_DESTRUCTION_DUMMY);
                events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 6700);
                break;
            case ACTION_RESET_AIR_EVENTS:
                events.CancelEvent(EVENT_TWILIGHT_BLAST);
                break;
            case ACTION_RESET_GROUND_EVENTS:
                events.CancelEvent(EVENT_FABULOUS_FLAMES);
                events.CancelEvent(EVENT_ENGULFING_MAGIC);
                break;
            case ACTION_TAKEOFF_2:
                me->CastStop();
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_TAKEOFF, 100);
                events.ScheduleEvent(EVENT_SCHEDULE_DAZZLING_DESTRUCTION, 85000);
                events.ScheduleEvent(EVENT_SCHEDULE_TWILIGHT_BLAST, 1000);
                break;
            default:
                break;
            }
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (point)
            {
            case POINT_TAKEOFF:
                events.ScheduleEvent(EVENT_FLY_CENTER, 1);
                break;
            case POINT_CENTER:
                events.ScheduleEvent(EVENT_SCHEDULE_TWILIGHT_BLAST, 1);
                break;
            case POINT_LAND:
                events.ScheduleEvent(EVENT_LANDED, 1);
                break;
            case POINT_TAKEOFF_2:
                events.ScheduleEvent(EVENT_FLY_UP, 1);
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
                    if (Creature* valiona = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                        valiona->AI()->DoAction(ACTION_RESET_GROUND_EVENTS);
                    Talk(SAY_THERALION_DAZZLING_DESTRUCTION);
                    Talk(SAY_THERALION_DAZZLING_DESTRUCTION_ANNOUNCE);
                    me->CastStop();
                    DoAction(ACTION_RESET_AIR_EVENTS);
                    DoCast(me, SPELL_DAZZLING_DESTRUCTION_AOE);
                    break;
                case EVENT_DAZZLING_DESTRUCTION:
                    if (_dazzlingDestructionCasts != 2)
                    {
                        DoCast(me, SPELL_DAZZLING_DESTRUCTION_AOE);
                        _dazzlingDestructionCasts++;
                    }
                    else
                        events.ScheduleEvent(EVENT_LAND, 1);
                    break;
                case EVENT_LAND:
                    if (Creature* valiona = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                        valiona->AI()->DoAction(ACTION_TAKEOFF);
                    DoAction(ACTION_LAND);
                    break;
                case EVENT_LANDED:
                    me->SetDisableGravity(false);
                    me->SetHover(false);
                    events.ScheduleEvent(EVENT_ATTACK, 1000);
                    break;
                case EVENT_ATTACK:
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_ENGULFING_MAGIC, 10000);
                    events.ScheduleEvent(EVENT_FABULOUS_FLAMES, 15000);
                    break;
                case EVENT_ENGULFING_MAGIC:
                    DoCast(me, SPELL_ENGULFING_MAGIC_AOE);
                    events.ScheduleEvent(EVENT_ENGULFING_MAGIC, 30000);
                    break;
                case EVENT_FABULOUS_FLAMES:
                    DoCast(me, SPELL_FABULOUS_FLAMES_AOE);
                    events.ScheduleEvent(EVENT_FABULOUS_FLAMES, 15000);
                    break;
                case EVENT_TAKEOFF:
                {
                    me->SetHover(true);
                    me->SetDisableGravity(true);
                    Position pos;
                    pos.Relocate(me);
                    pos.m_positionZ += 17.0f;
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF_2, pos);
                    _isOnGround = false;
                    break;
                 }
                case EVENT_FLY_UP:
                {
                    Position pos;
                    pos.Relocate(me);
                    float x = me->GetPositionX();
                    float y = me->GetPositionY();
                    if (Creature* stalker = me->FindNearestCreature(NPC_THERALION_FLIGHT_STALKER, 500.0f))
                    {
                        float z = stalker->GetPositionZ();
                        me->GetMotionMaster()->MovePoint(POINT_UP, x, y, z, false);
                    }
                    break;
                }
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
            {
                valiona->GetMotionMaster()->MovementExpired();
                valiona->AddUnitState(UNIT_STATE_CANNOT_TURN);
                valiona->SetReactState(REACT_PASSIVE);
                valiona->AttackStop();
                valiona->SetFacingToObject(me);
                valiona->AI()->DoAction(ACTION_CAST_DEVOURING_FLAMES);
            }
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

class npc_tav_fabulous_flames_dummy : public CreatureScript
{
public:
    npc_tav_fabulous_flames_dummy() : CreatureScript("npc_tav_fabulous_flames_dummy") { }

    struct npc_tav_fabulous_flames_dummyAI : public ScriptedAI
    {
        npc_tav_fabulous_flames_dummyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_fabulous_flames_dummyAI(creature);
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
            me->DespawnOrUnsummon(6600);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_dazzling_destruction_stalkerAI(creature);
    }
};

class npc_tav_deep_breath_dummy : public CreatureScript
{
public:
    npc_tav_deep_breath_dummy() : CreatureScript("npc_tav_deep_breath_dummy") { }

    struct npc_tav_deep_breath_dummyAI : public ScriptedAI
    {
        npc_tav_deep_breath_dummyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_CHECK_VALIONA, 500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_VALIONA:
                        if (Creature* valiona = me->FindNearestCreature(BOSS_VALIONA, 30.0f, true))
                        {
                            if (!me->HasAura(SPELL_TWILIGHT_FLAMES_TRIGGER))
                            {
                                me->CastSpell(me, SPELL_TWILIGHT_FLAMES_TRIGGER, true);
                                me->DespawnOrUnsummon(10000);
                            }
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_VALIONA, 500);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_deep_breath_dummyAI(creature);
    }
};

class npc_tav_unstable_twilight : public CreatureScript
{
public:
    npc_tav_unstable_twilight() : CreatureScript("npc_tav_unstable_twilight") { }

    struct npc_tav_unstable_twilightAI : public ScriptedAI
    {
        npc_tav_unstable_twilightAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_MOVE_RANDOM, 1);
        }

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_UNSTABLE_TWILIGHT_TRIGGERED)
            {
                DoCastAOE(SPELL_UNSTABLE_TWILIGHT_DAMAGE, true);
                me->RemoveAurasDueToSpell(SPELL_UNSTABLE_TWILIGHT);
                events.ScheduleEvent(EVENT_ACTIVATE_UNSTABLE_TWILIGHT, 5000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ACTIVATE_UNSTABLE_TWILIGHT:
                        DoCastAOE(SPELL_UNSTABLE_TWILIGHT, true);
                        break;
                    case EVENT_MOVE_RANDOM:
                        me->GetMotionMaster()->MoveRandom(10.0f);
                        events.ScheduleEvent(EVENT_MOVE_RANDOM, 1000);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_unstable_twilightAI(creature);
    }
};

class npc_tav_collapsing_twilight_portal : public CreatureScript
{
public:
    npc_tav_collapsing_twilight_portal() : CreatureScript("npc_tav_collapsing_twilight_portal") { }

    struct npc_tav_collapsing_twilight_portalAI : public ScriptedAI
    {
        npc_tav_collapsing_twilight_portalAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tav_collapsing_twilight_portalAI(creature);
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

            targets.remove_if(TwilightShiftCheck());

            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
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

class spell_tav_devouring_flames_aura : public SpellScriptLoader
{
public:
    spell_tav_devouring_flames_aura() : SpellScriptLoader("spell_tav_devouring_flames_aura") { }

    class spell_tav_devouring_flames_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tav_devouring_flames_aura_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetTarget())
                {
                    if (target->GetEntry() == 46588)
                    {
                        float ori = caster->GetOrientation();
                        float dist = caster->GetFloatValue(UNIT_FIELD_COMBATREACH);
                        float x = caster->GetPositionX() + cos(ori) * dist;
                        float y = caster->GetPositionY() + sin(ori) * dist;
                        float z = caster->GetPositionZ();
                        target->NearTeleportTo(x, y, z, ori);
                        caster->SetFacingToObject(target);
                    }
                }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_tav_devouring_flames_aura_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tav_devouring_flames_aura_AuraScript();
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

            targets.remove_if(TwilightShiftCheck());

            if (targets.empty())
                return;

            if (targets.size() >= 2)
                targets.remove_if(VictimCheck(GetCaster()));

            Trinity::Containers::RandomResizeList(targets, 1);
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

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetOwner()->ToUnit())
                owner->CastSpell(owner, SPELL_BLACKOUT_DAMAGE, true);
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_tav_blackout_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB, AURA_EFFECT_HANDLE_REAL);
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

            Trinity::Containers::RandomResizeList(targets, 2);
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

class spell_tav_dazzling_destruction : public SpellScriptLoader
{
public:
    spell_tav_dazzling_destruction() : SpellScriptLoader("spell_tav_dazzling_destruction") { }

    class spell_tav_dazzling_destruction_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_dazzling_destruction_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());
        }

        void HandleScriptRealm(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->CastSpell(target, SPELL_DAZZLING_DESTRUCTION_REALM_DAMAGE, true);
                target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_1].BasePoints, true);
            }
        }

        void HandleScriptBuff(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_2].BasePoints, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_dazzling_destruction_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_tav_dazzling_destruction_SpellScript::HandleScriptRealm, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            OnEffectHitTarget += SpellEffectFn(spell_tav_dazzling_destruction_SpellScript::HandleScriptBuff, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_dazzling_destruction_SpellScript();
    }
};

class spell_tav_dazzling_destruction_realm_damage : public SpellScriptLoader
{
public:
    spell_tav_dazzling_destruction_realm_damage() : SpellScriptLoader("spell_tav_dazzling_destruction_realm_damage") { }

    class spell_tav_dazzling_destruction_realm_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_dazzling_destruction_realm_damage_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(NoTwilightShiftCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_dazzling_destruction_realm_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_dazzling_destruction_realm_damage_SpellScript();
    }
};

class spell_tav_engulfing_magic_aoe : public SpellScriptLoader // should only target spellcasters
{
public:
    spell_tav_engulfing_magic_aoe() : SpellScriptLoader("spell_tav_engulfing_magic_aoe") { }

    class spell_tav_engulfing_magic_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_engulfing_magic_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            std::list<WorldObject*>::iterator it = targets.begin();

            while (it != targets.end())
            {
                if (!GetCaster())
                    return;

                WorldObject* unit = *it;

                if (!unit)
                    continue;

                if (unit->GetTypeId() == TYPEID_PLAYER)
                {
                    switch (unit->ToPlayer()->getClass())
                    {
                        case CLASS_PRIEST:
                        case CLASS_WARLOCK:
                        case CLASS_MAGE:
                            it++;
                            break;
                        case CLASS_ROGUE:
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            it = targets.erase(it);
                            break;
                        case CLASS_DRUID:
                            if (unit->ToPlayer()->HasAura(84735))
                                it = targets.erase(it);
                            else
                                it++;
                            break;
                        case CLASS_SHAMAN:
                            if (unit->ToPlayer()->HasAura(30814))
                                it = targets.erase(it);
                            else
                                it++;
                            break;
                        case CLASS_PALADIN:
                            if (unit->ToPlayer()->HasAura(85102))
                                it = targets.erase(it);
                            else
                                it++;
                            break;
                    }
                }
            }

            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());

            if (targets.empty())
                return;

            if (!GetCaster()->GetMap()->Is25ManRaid())
                Trinity::Containers::RandomResizeList(targets, 1);
            else
                Trinity::Containers::RandomResizeList(targets, 3);
        }

        void CallAction(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->ToCreature()->AI()->Talk(SAY_THERALION_ENGULFING_MAGIC_ANNOUNCE);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_engulfing_magic_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_tav_engulfing_magic_aoe_SpellScript::CallAction, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_engulfing_magic_aoe_SpellScript();
    }
};

class spell_tav_fabulous_flames_aoe : public SpellScriptLoader
{
public:
    spell_tav_fabulous_flames_aoe() : SpellScriptLoader("spell_tav_fabulous_flames_aoe") { }

    class spell_tav_fabulous_flames_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_fabulous_flames_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());

            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->CastSpell(target, SPELL_FABULOUS_FLAMES_MISSILE, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_fabulous_flames_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_tav_fabulous_flames_aoe_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_fabulous_flames_aoe_SpellScript();
    }
};

class spell_tav_fabulous_flames_damage : public SpellScriptLoader
{
public:
    spell_tav_fabulous_flames_damage() : SpellScriptLoader("spell_tav_fabulous_flames_damage") { }

    class spell_tav_fabulous_flames_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_fabulous_flames_damage_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_fabulous_flames_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_fabulous_flames_damage_SpellScript();
    }
};

class spell_tav_twilight_meteorite_aoe : public SpellScriptLoader
{
public:
    spell_tav_twilight_meteorite_aoe() : SpellScriptLoader("spell_tav_twilight_meteorite_aoe") { }

    class spell_tav_twilight_meteorite_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_twilight_meteorite_aoe_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());

            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    caster->CastSpell(target, SPELL_TWILIGHT_METEORITE_MISSILE, false);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_twilight_meteorite_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_meteorite_aoe_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_twilight_meteorite_aoe_SpellScript();
    }
};

class spell_tav_engulfing_magic : public SpellScriptLoader
{
public:
    spell_tav_engulfing_magic() : SpellScriptLoader("spell_tav_engulfing_magic") { }

    class spell_tav_engulfing_magic_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tav_engulfing_magic_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            Unit* caster = eventInfo.GetActor();
            uint64 damage = eventInfo.GetDamageInfo()->GetDamage();
            uint64 heal = eventInfo.GetHealInfo()->GetHeal();

            if (heal == 0 && damage == 0)
                return false;

            caster->CastCustomSpell(SPELL_ENGULFING_MAGIC_PROC, SPELLVALUE_BASE_POINT0, (heal + damage), caster, true, NULL);
            return true;
        }

        void Register()
        {
            DoCheckProc += AuraCheckProcFn(spell_tav_engulfing_magic_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tav_engulfing_magic_AuraScript();
    }
};

class spell_tav_twilight_flames_realm : public SpellScriptLoader
{
public:
    spell_tav_twilight_flames_realm() : SpellScriptLoader("spell_tav_twilight_flames_realm") { }

    class spell_tav_twilight_flames_realm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_twilight_flames_realm_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(NoTwilightShiftCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_twilight_flames_realm_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_twilight_flames_realm_SpellScript();
    }
};

class spell_tav_twilight_flames : public SpellScriptLoader
{
public:
    spell_tav_twilight_flames() : SpellScriptLoader("spell_tav_twilight_flames") { }

    class spell_tav_twilight_flames_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_twilight_flames_SpellScript);

        void FilterFlameTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());
        }

        void HandleHitBuff(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (!target->HasAura(GetSpellInfo()->Effects[EFFECT_2].BasePoints))
                    target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_2].BasePoints, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_twilight_flames_SpellScript::FilterFlameTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_flames_SpellScript::HandleHitBuff, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_twilight_flames_SpellScript();
    }
};

class spell_tav_twilight_shift : public SpellScriptLoader
{
public:
    spell_tav_twilight_shift() : SpellScriptLoader("spell_tav_twilight_shift") { }

    class spell_tav_twilight_shift_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_twilight_shift_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(TwilightShiftCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_twilight_shift_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_twilight_shift_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tav_twilight_shift_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_twilight_shift_SpellScript();
    }
};

class spell_tav_twilight_shift_1 : public SpellScriptLoader
{
public:
    spell_tav_twilight_shift_1() : SpellScriptLoader("spell_tav_twilight_shift_1") { }

    class spell_tav_twilight_shift_1_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_twilight_shift_1_SpellScript);

        void HandleScript1(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(GetSpellInfo()->Effects[EFFECT_0].BasePoints, GetCaster()));
        }

        void HandleScript2(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(GetSpellInfo()->Effects[EFFECT_1].BasePoints, GetCaster()));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_shift_1_SpellScript::HandleScript1, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_shift_1_SpellScript::HandleScript2, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_twilight_shift_1_SpellScript();
    }
};

class spell_tav_twilight_shift_2 : public SpellScriptLoader
{
public:
    spell_tav_twilight_shift_2() : SpellScriptLoader("spell_tav_twilight_shift_2") { }

    class spell_tav_twilight_shift_2_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_tav_twilight_shift_2_SpellScript);

        void HandleScript1(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(GetSpellInfo()->Effects[EFFECT_0].BasePoints, GetCaster()));
        }

        void HandleScript2(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(GetSpellInfo()->Effects[EFFECT_1].BasePoints, GetCaster()));
        }

        void HandleScript3(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(GetSpellInfo()->Effects[EFFECT_2].BasePoints, GetCaster()));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_shift_2_SpellScript::HandleScript1, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_shift_2_SpellScript::HandleScript2, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            OnEffectHitTarget += SpellEffectFn(spell_tav_twilight_shift_2_SpellScript::HandleScript3, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_tav_twilight_shift_2_SpellScript();
    }
};

void AddSC_boss_theralion_and_valiona()
{
    new at_theralion_and_valiona();
    new boss_valiona();
    new boss_theralion();
    new npc_tav_devouring_flames_dummy();
    new npc_tav_fabulous_flames_dummy();
    new npc_tav_dazzling_destruction_stalker();
    new npc_tav_deep_breath_dummy();
    new npc_tav_unstable_twilight();
    new npc_tav_collapsing_twilight_portal();
    new spell_tav_devouring_flame_dummy_aoe();
    new spell_tav_devouring_flames();
    new spell_tav_devouring_flames_aura();
    new spell_tav_blackout_aoe();
    new spell_tav_blackout_aura();
    new spell_tav_dazzling_destruction_aoe();
    new spell_tav_dazzling_destruction_cast();
    new spell_tav_dazzling_destruction();
    new spell_tav_dazzling_destruction_realm_damage();
    new spell_tav_engulfing_magic_aoe();
    new spell_tav_fabulous_flames_aoe();
    new spell_tav_fabulous_flames_damage();
    new spell_tav_twilight_meteorite_aoe();
    new spell_tav_engulfing_magic();
    new spell_tav_twilight_flames_realm();
    new spell_tav_twilight_flames();
    new spell_tav_twilight_shift();
    new spell_tav_twilight_shift_1();
    new spell_tav_twilight_shift_2();
}
