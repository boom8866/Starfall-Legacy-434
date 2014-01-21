#include "endtime.h"

enum Spells
{
    SPELL_SANDS_OF_THE_HOURGLASS    = 102668,
    SPELL_TEMPORAL_BLAST            = 102381,
    SPELL_ETERNAL_BREATH            = 102569,
    SPELL_DISTORTION_BOMB           = 101983,
    SPELL_TEMPORAL_SNAPSHOT         = 101592,
    SPELL_TAIL_SWEEP                = 108589,

    SPELL_FADE                      = 107550,
    SPELL_TEMPORAL_SNAPSHOT_SUMMON  = 101592,
};

enum Texts
{
    SAY_INTRO_1     = 1,
    SAY_INTRO_2     = 2,
    SAY_AGGRO       = 3,
    SAY_HOURGLASS_1 = 4,
    SAY_HOURGLASS_2 = 5,
    SAY_HOURGLASS_3 = 6,
    SAY_HOURGLASS_4 = 7,
    SAY_HOURGLASS_5 = 8,
    SAY_SLAY        = 9,
    SAY_DEATH       = 10,
};

enum Actions
{
    ACTION_INTRO_1      = 1,
    ACTION_INTRO_2      = 2,
    ACTION_HOURGLASS    = 3,
};

enum MovePoints
{
    POINT_MOVE_IN   = 1,
    POINT_LAND      = 2,
};

enum Events
{
    EVENT_FINISH_INTRO_1        = 1,
    EVENT_FINISH_INTRO_2        = 2,
    EVENT_TEMPORAL_SNAPSHOT     = 3,
    EVENT_TEMPORAL_BLAST        = 4,
};

Position const LandingPosition = {4181.117f, -420.2193f, 138.3806f};

class boss_murozond : public CreatureScript
{
public:
    boss_murozond() : CreatureScript("boss_murozond") { }

    struct boss_murozondAI : public BossAI
    {
        boss_murozondAI(Creature* creature) : BossAI(creature, DATA_MUROZOND)
        {
            _introDone = false;
            _introCounter = 0;
        }

        bool _introDone;
        uint8 _introCounter;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->DoCastSpellOnPlayers(SPELL_SANDS_OF_THE_HOURGLASS);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_TEMPORAL_SNAPSHOT, 3000);
            events.ScheduleEvent(EVENT_TEMPORAL_BLAST, 15500);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SANDS_OF_THE_HOURGLASS);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SANDS_OF_THE_HOURGLASS);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INTRO_1:
                    _introCounter++;
                    if (_introCounter == 4)
                        Talk(SAY_INTRO_1);
                    else if (_introCounter == 8)
                        DoAction(ACTION_INTRO_2);
                    break;
                case ACTION_INTRO_2:
                    Talk(SAY_INTRO_2);
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_IN, LandingPosition);
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_MOVE_IN:
                    events.ScheduleEvent(EVENT_FINISH_INTRO_1, 1);
                    break;
                case POINT_LAND:
                    events.ScheduleEvent(EVENT_FINISH_INTRO_2, 1);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && _introDone)
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FINISH_INTRO_1:
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ -= 20.0f;
                        me->GetMotionMaster()->MoveLand(POINT_LAND, pos);
                        break;
                    case EVENT_FINISH_INTRO_2:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        pos.Relocate(me);
                        me->SetHomePosition(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), me->GetOrientation());
                        me->SetFacingTo(2.76f);
                        _introDone = true;
                        break;
                    case EVENT_TEMPORAL_SNAPSHOT:
                        DoCastAOE(SPELL_TEMPORAL_SNAPSHOT);
                        break;
                    case EVENT_TEMPORAL_BLAST:
                        DoCastAOE(SPELL_TEMPORAL_BLAST);
                        events.ScheduleEvent(EVENT_TEMPORAL_BLAST, urand(13000, 20000));
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
        return new boss_murozondAI(creature);
    }
};

class npc_infinite_dragon : public CreatureScript
{
    public:
        npc_infinite_dragon() :  CreatureScript("npc_infinite_dragon") { }

        struct npc_infinite_dragonAI : public ScriptedAI
        {
            npc_infinite_dragonAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void EnterCombat(Unit* /*who*/)
            {
            }

            void Reset()
            {
                events.Reset();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* murozond = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MUROZOND)))
                    murozond->AI()->DoAction(ACTION_INTRO_1);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    /*
                    switch (eventId)
                    {
                    }
                    */
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_infinite_dragonAI(creature);
    }
};

void AddSC_boss_murozond()
{
    new boss_murozond();
    new npc_infinite_dragon();
}
