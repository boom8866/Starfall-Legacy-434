#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

enum actionId
{
    ACTION_CHECK_CHANNELERS     = 1,
    ACTION_WAVES,
    ACTION_START_TIMER
};

enum npcId
{
    NPC_CHOSEN_SEER     = 46952,
    NPC_CHOSEN_WARRIOR  = 46951,
    NPC_TWILIGHT_BRUTE  = 47161,
    NPC_DESTROYER       = 47097,
    NPC_FIRESTARTER     = 47086,
    NPC_ELEMENTALIST    = 47152,
    NPC_FIRELORD        = 47081,
    NPC_EARTH_RAVAGER   = 47150,
    NPC_WIND_BREAKER    = 47151
};

class npc_bot_twilight_phase_twister : public CreatureScript
{
public:
    npc_bot_twilight_phase_twister() : CreatureScript("npc_bot_twilight_phase_twister")
    {
    }

    struct npc_bot_twilight_phase_twisterAI : public ScriptedAI
    {
        npc_bot_twilight_phase_twisterAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum eventId
        {
            EVENT_CHANNEL_ORB   = 1,
            EVENT_SHADOW_BOLT,
            EVENT_CHECK_COMBAT
        };

        enum spellId
        {
            SPELL_SHADOW_BOLT   = 95440,
            SPELL_TWISTED_PHASE = 84737
        };

        enum npcId
        {
            NPC_TWILIGHT_ORB    = 42098
        };

        enum pointId
        {
            POINT_EVADE     = 1
        };

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MovePoint(POINT_EVADE, x, y, z, true);
            events.CancelEvent(EVENT_SHADOW_BOLT);
            events.ScheduleEvent(EVENT_CHANNEL_ORB, 5000);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(4000, 12000));
            events.ScheduleEvent(EVENT_CHECK_COMBAT, 2000);
        }

        void JustReachedHome()
        {
            me->SetFacingTo(o);
        }

        void InitializeAI()
        {
            x = me->GetPositionX();
            y = me->GetPositionY();
            z = me->GetPositionZ();
            o = me->GetOrientation();

            events.ScheduleEvent(EVENT_CHANNEL_ORB, 1000);
        }

        void JustDied(Unit* /*killer*/)
        {
            std::list<Creature*> targets;
            GetCreatureListWithEntryInGrid(targets, me, NPC_TWILIGHT_ORB, 200.0f);
            for (std::list<Creature*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr) && me->GetOwner() && me->GetOwner() == (*itr))
                    (*itr)->AI()->DoAction(ACTION_CHECK_CHANNELERS);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHANNEL_ORB:
                    {
                        if (me->isInCombat() || me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            events.RescheduleEvent(EVENT_CHANNEL_ORB, 2000);
                            break;
                        }

                        if (Creature* twilightOrb = me->FindNearestCreature(NPC_TWILIGHT_ORB, 10.0f, true))
                            me->SetOwnerGUID(twilightOrb->GetGUID());

                        DoCast(SPELL_TWISTED_PHASE);
                        break;
                    }
                    case EVENT_SHADOW_BOLT:
                    {
                        if (me->isInCombat())
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true))
                                DoCast(target, SPELL_SHADOW_BOLT);
                        }
                        events.RescheduleEvent(EVENT_SHADOW_BOLT, urand(4000, 6500));
                        break;
                    }
                    case EVENT_CHECK_COMBAT:
                    {
                        if (!me->getVictim() && me->GetDistance2d(x, y) > 0)
                        {
                            events.CancelEvent(EVENT_CHECK_COMBAT);
                            EnterEvadeMode();
                            break;
                        }
                        events.RescheduleEvent(EVENT_CHECK_COMBAT, 5000);
                        break;
                    }
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        protected:
            float x, y, z, o;
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_twilight_phase_twisterAI(creature);
    }
};

class npc_bot_twilight_orb : public CreatureScript
{
public:
    npc_bot_twilight_orb() : CreatureScript("npc_bot_twilight_orb")
    {
    }

    struct npc_bot_twilight_orbAI : public ScriptedAI
    {
        npc_bot_twilight_orbAI(Creature* creature) : ScriptedAI(creature)
        {
            noChannelersFound = true;
        }

        EventMap events;
        bool noChannelersFound;

        enum eventId
        {
            EVENT_PHASED_BURN       = 1,
            EVENT_CHECK_CHANNELERS
        };

        enum spellId
        {
            SPELL_PHASED_BURN   = 85799
        };

        enum npcId
        {
            NPC_TWILIGHT_CHANNELER  = 45267
        };

        void InitializeAI()
        {
            // Bind it only in Bastion of Twilight
            if (me->GetMapId() != 671)
                return;

            noChannelersFound = true;
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_PHASED_BURN, 2000);
            events.ScheduleEvent(EVENT_CHECK_CHANNELERS, 6000);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            damage = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CHECK_CHANNELERS:
                {
                    events.ScheduleEvent(EVENT_CHECK_CHANNELERS, 1);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_PHASED_BURN:
                    {
                        DoCast(me, SPELL_PHASED_BURN, true);
                        events.RescheduleEvent(EVENT_PHASED_BURN, 10000);
                        break;
                    }
                    case EVENT_CHECK_CHANNELERS:
                    {
                        std::list<Creature*> targets;
                        GetCreatureListWithEntryInGrid(targets, me, NPC_TWILIGHT_CHANNELER, 200.0f);
                        for (std::list<Creature*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->GetOwner() && (*itr)->GetOwner() == me && (*itr)->isAlive())
                            {
                                noChannelersFound = false;
                                break;
                            }
                            else
                                noChannelersFound = true;
                        }

                        if (noChannelersFound == true)
                        {
                            me->CombatStop();
                            me->CastStop();
                            me->AttackStop();
                            me->DespawnOrUnsummon(1000);
                            events.CancelEvent(EVENT_CHECK_CHANNELERS);
                        }
                        else
                            events.RescheduleEvent(EVENT_CHECK_CHANNELERS, 5000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bot_twilight_orbAI(creature);
    }
};

class PhasedBurnCheck
{
public:
    PhasedBurnCheck()
    {
    }

    bool operator()(WorldObject* object)
    {
        return (object->ToCreature());
    }
};

class spell_bot_phased_burn : public SpellScriptLoader
{
public:
    spell_bot_phased_burn() : SpellScriptLoader("spell_bot_phased_burn")
    {
    }

    class spell_bot_phased_burn_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_bot_phased_burn_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(PhasedBurnCheck());

            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_bot_phased_burn_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_bot_phased_burn_SpellScript();
    }
};

class npc_chogall_wave_event : public CreatureScript
{
public:
    npc_chogall_wave_event() : CreatureScript("npc_chogall_wave_event")
    {
    }

    enum eventId
    {
        EVENT_ENABLE_WAVES          = 1,
        EVENT_CHECK_SEER,
        EVENT_MOVE_AWAY_AND_DESPAWN
    };

    struct npc_chogall_wave_eventAI : public ScriptedAI
    {
        npc_chogall_wave_eventAI(Creature* creature) : ScriptedAI(creature)
        {
            alreadyTalked = false;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
        }

        EventMap events;
        bool alreadyTalked;
        float x, y, z;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_WAVES:
                    events.ScheduleEvent(EVENT_ENABLE_WAVES, 4500);
                    break;
                case ACTION_START_TIMER:
                    events.ScheduleEvent(EVENT_CHECK_SEER, 1000);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENABLE_WAVES:
                    {
                        if (!alreadyTalked)
                        {
                            Talk(2);
                            alreadyTalked = true;
                        }
                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 60.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(60.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isAlive() && (*itr)->ToCreature() && !(*itr)->isInCombat() &&
                                (*itr)->ToCreature()->GetEntry() == NPC_CHOSEN_SEER || (*itr)->ToCreature()->GetEntry() == NPC_CHOSEN_WARRIOR)
                            {
                                (*itr)->SetWalk(false);
                                (*itr)->ToCreature()->SetInCombatWithZone();
                            }
                        }
                        events.ScheduleEvent(EVENT_MOVE_AWAY_AND_DESPAWN, 35000);
                        events.CancelEvent(EVENT_ENABLE_WAVES);
                        break;
                    }
                    case EVENT_CHECK_SEER:
                    {
                        std::list<Creature*> targets;
                        GetCreatureListWithEntryInGrid(targets, me, NPC_CHOSEN_SEER, 500.0f);
                        for (std::list<Creature*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr)->isInCombat())
                            {
                                DoAction(ACTION_WAVES);
                                events.CancelEvent(EVENT_CHECK_SEER);
                                break;
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_SEER, 1000);
                        break;
                    }
                    case EVENT_MOVE_AWAY_AND_DESPAWN:
                    {
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(0, -695.72f, -684.51f, 834.68f, false);
                        me->DespawnOrUnsummon(4000);

                        std::list<Unit*> targets;
                        Trinity::AnyUnitInObjectRangeCheck u_check(me, 200.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(200.0f, searcher);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            if ((*itr) && (*itr)->isAlive() && (*itr)->ToCreature() && !(*itr)->isInCombat())
                            {
                                switch ((*itr)->ToCreature()->GetEntry())
                                {
                                    case NPC_DESTROYER:
                                    case NPC_FIRESTARTER:
                                    case NPC_TWILIGHT_BRUTE:
                                    {
                                        if (roll_chance_i(50))
                                        {
                                            (*itr)->SetWalk(false);
                                            (*itr)->ToCreature()->SetInCombatWithZone();
                                        }
                                        break;
                                    }
                                    case NPC_ELEMENTALIST:
                                    case NPC_WIND_BREAKER:
                                    case NPC_FIRELORD:
                                    case NPC_EARTH_RAVAGER:
                                    {
                                        (*itr)->SetWalk(false);
                                        (*itr)->GetMotionMaster()->MovePoint(0, -650.847f+urand(5, 6), -684.92f-urand(3, 5), z);
                                        (*itr)->ToCreature()->SetHomePosition(-650.847f+urand(5, 6), -684.92f-urand(3, 5), z, (*itr)->GetOrientation());
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chogall_wave_eventAI(creature);
    }
};

void AddSC_bastion_of_twilight()
{
    new npc_bot_twilight_phase_twister();
    new npc_bot_twilight_orb();
    new spell_bot_phased_burn();
    new npc_chogall_wave_event();
}
