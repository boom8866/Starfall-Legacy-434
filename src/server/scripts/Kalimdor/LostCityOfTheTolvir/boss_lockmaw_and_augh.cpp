/*
 * Copyright (C) 2014 NorthStrider
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "lost_city_of_the_tolvir.h"

enum Texts
{
    // Augh Intro
    SAY_AGGRO_INTRO     = 0,
    SAY_ESCAPE_FIGHT    = 1,
};

enum Spells
{
    // Intro Augh
    SPELL_SMOKE_BOMB        = 84768,
};

enum Events
{
    EVENT_SMOKE_BOMB = 1,
    EVENT_INVISIBLE,
};

class boss_lockmaw : public CreatureScript
{
public:
    boss_lockmaw() : CreatureScript("boss_lockmaw") { }

    struct boss_lockmawAI : public BossAI
    {
        boss_lockmawAI(Creature* creature) : BossAI(creature, DATA_LOCKMAW)
        {
        }

        void Reset()
        {
        };

        void EnterCombat(Unit* /*victim*/)
        {
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
        }
    
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_lockmawAI(creature);
    }
};

class npc_lct_augh : public CreatureScript
{
    public:
        npc_lct_augh() :  CreatureScript("npc_lct_augh") { }

        struct npc_lct_aughAI : public ScriptedAI
        {
            npc_lct_aughAI(Creature* creature) : ScriptedAI(creature)
            {
                done = false;
            }

            EventMap events;
            bool done;

            void Reset()
            {
                done = false;
            }

            void EnterCombat(Unit* who)
            {
                Talk(SAY_AGGRO_INTRO);
            }

            void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
            {
                if (me->GetHealthPct() < 50 && !done)
                {
                    Talk(SAY_ESCAPE_FIGHT);
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    events.ScheduleEvent(EVENT_SMOKE_BOMB, 1000);
                    done = true;

                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SMOKE_BOMB:
                            DoCastAOE(SPELL_SMOKE_BOMB);
                            events.ScheduleEvent(EVENT_INVISIBLE, 1100);
                            break;
                        case EVENT_INVISIBLE:
                            me->DeleteThreatList();
                            me->CombatStop();
                            me->DisappearAndDie();
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
            return new npc_lct_aughAI(creature);
        }
};

void AddSC_boss_lockmaw_and_augh()
{
    new boss_lockmaw();
    new npc_lct_augh();
}
