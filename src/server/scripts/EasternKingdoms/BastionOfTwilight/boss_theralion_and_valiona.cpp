
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

#define MAX_DAZZLING_DESTRUCTION_CASTS 3

enum Texts
{
    // Theralion
    SAY_THERALION_INTRO_1               = 0,
    SAY_THERALION_INTRO_2               = 1,
    SAY_THERALION_SLAY                  = 2,
    SAY_THERALION_DAZZLING_ANNOUNCE     = 3,
    SAY_THERALION_DAZZLING_DESTRUCTION  = 4,
    SAY_THERALION_ENGULFING_ANNOUNCE    = 5,
    SAY_THERALION_ENGULFING_MAGIC       = 6,
    SAY_THERALION_DEATH                 = 7,

    // Valiona
    SAY_VALIONA_INTRO_1                 = 0,
    SAY_VALIONA_INTRO_2                 = 1,
    SAY_VALIONA_BLACKOUT                = 2,
    SAY_VALIONA_DAZZLING                = 3,
    SAY_VALIONA_DEEP_BREATH_ANNOUNCE    = 4,
    SAY_VALIONA_DEEP_BREATH             = 5,
    SAY_VALIONA_SLAY                    = 6,
    SAY_VALIONA_DEATH                   = 7,
};

enum Spells
{
};

enum Events
{
    // Theralion
    EVENT_FLY_CENTER = 1,
    EVENT_TALK_INTRO_1,
    EVENT_TALK_INTRO_2,

    // Valiona
    EVENT_TAUNT_THERALION,
};

enum Actions
{
    ACTION_TAKEOFF = 1,
    ACTION_LAND,
};

enum Points
{
    POINT_TAKEOFF = 1,
    POINT_LAND,
    POINT_CENTER,
};

enum Phases
{
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

class boss_valiona : public CreatureScript
{
public:
    boss_valiona() : CreatureScript("boss_valiona") { }

    struct boss_valionaAI : public BossAI
    {
        boss_valionaAI(Creature* creature) : BossAI(creature, DATA_THERALION_AND_VALIONA)
        {
            _isOnGround = true;
        }

        bool _isOnGround;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

            if (Creature* theralion = me->FindNearestCreature(BOSS_THERALION, 500.0f, true))
                theralion->AI()->AttackStart(who);

            Talk(SAY_VALIONA_INTRO_1);
            events.ScheduleEvent(EVENT_TAUNT_THERALION, 13000);
            _isOnGround = true;
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
                case ACTION_TAKEOFF:
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    Position pos;
                    pos.Relocate(me);
                    pos.m_positionZ += 16.0f;
                    me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                    _isOnGround = false;
                    break;
                case ACTION_LAND:
                    _isOnGround = true;
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
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TAUNT_THERALION:
                        Talk(SAY_VALIONA_INTRO_2);
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
            _isOnGround = false;
        }

        bool _isOnGround;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TALK_INTRO_1, 5000);
            DoAction(ACTION_TAKEOFF);

            if (Creature* valiona = me->FindNearestCreature(BOSS_VALIONA, 500.0f, true))
                valiona->AI()->AttackStart(who);
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _EnterEvadeMode();
            _DespawnAtEvade();
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
                case ACTION_TAKEOFF:
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->SetCanFly(true);
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
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FLY_CENTER:
                        if (Creature* stalker = me->FindNearestCreature(NPC_THERALION_FLIGHT_STALKER, 500.0f, true))
                        {
                            Position pos;
                            pos.Relocate(stalker);
                            me->GetMotionMaster()->MovePoint(POINT_CENTER, pos);
                        }
                        break;
                    case EVENT_TALK_INTRO_1:
                        Talk(SAY_THERALION_INTRO_1);
                        events.ScheduleEvent(EVENT_TALK_INTRO_2, 13000);
                        break;
                    case EVENT_TALK_INTRO_2:
                        Talk(SAY_THERALION_INTRO_2);
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

void AddSC_boss_theralion_and_valiona()
{
    new boss_valiona();
    new boss_theralion();
}
