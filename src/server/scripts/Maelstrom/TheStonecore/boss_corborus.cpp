
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "the_stonecore.h"

enum Spells
{
    ////////////////////////////////////////////
    // Pre-Event
    SPELL_RING_WYRM_CHARGE              = 81237, //     SPELL_EFFECT_CHARGE_DEST
    SPELL_RING_WYRM_KNOCKBACK           = 81235,
    SPELL_DOOR_BRAKE                    = 81232,

    ////////////////////////////////////////////
    // General
    SPELL_CRYSTAL_BARRAGE               = 86881, // +-- SPELL_EFFECT_PERSISTENT_AREA_AURA (SPELL_AURA_PERIODIC_DAMAGE)
    SPELL_CRYSTAL_BARRAGE_UNK           = 81638, // |   SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_CRYSTAL_BARRAGE_UNK1          = 81637, // +-> SPELL_EFFECT_DUMMY
    SPELL_CRYSTAL_BARRAGE_UNK2          = 81634, //     SPELL_EFFECT_SCRIPT_EFFECT
    SPELL_CRYSTAL_BARRAGE_SUMMON        = 92012, //     SPELL_EFFECT_SUMMON (49267)

    SPELL_DAMPENING_WAVE                = 82415, //     SPELL_EFFECT_SCHOOL_DAMAGE

    ////////////////////////////////////////////
    // Submerge Phase
    SPELL_CLEAR_ALL_DEBUFFS             = 34098,
    SPELL_SUBMERGE                      = 81629, // +-- SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_SUMMON_BEETLE                 = 82190, // |   SPELL_EFFECT_FORCE_CAST
    SPELL_SUMMON_BEETLE_EFFECT          = 82188, // +-> SPELL_EFFECT_SUMMON (43917)

    SPELL_TRASHING_CHARGE               = 81839, // +-- SPELL_EFFECT_TELEPORT_UNITS, SPELL_EFFECT_TRIGGER_SPELL
    SPELL_TRASHING_CHARGE_UNK           = 81864, // +-> SPELL_EFFECT_TELEPORT_UNITS, SPELL_EFFECT_DUMMY
    SPELL_TRASHING_CHARGE_UNK1          = 81838, //     SPELL_EFFECT_DUMMY (Seems to be the pre teleport)
    SPELL_TRASHING_CHARGE_JUMP          = 81801, //     SPELL_EFFECT_DUMMY
    SPELL_TRASHING_CHARGE_VISUAL_SUMMON = 81816, //     SPELL_EFFECT_SUMMON (43743)

    ////////////////////////////////////////////
    // Thrashing Charge
    SPELL_TRASHING_CHARGE_KNOCKBACK     = 81828, //     SPELL_EFFECT_SCHOOL_DAMAGE, SPELL_EFFECT_KNOCK_BACK

    ////////////////////////////////////////////
    // Rock Borer
    SPELL_EMERGE                        = 82185, //     SPELL_AURA_DUMMY
};

enum Events
{
    EVENT_CRYSTAL_BARRAGE       = 1,
    EVENT_DAMPENING_WAVE        = 2,
    EVENT_ENTER_SUBMERGE        = 3,
};

Position const homePosition = {1154.55f, 878.843f, 286.f, 3.222f};

namespace Corborus
{
    class HomePositionDistanceSelector
    {
    public:
        bool operator() (Unit* unit)
        {
            return unit->GetDistance(homePosition) > 30.f;
        }
    };

    class HomeTele : public BasicEvent
    {
    public:
        HomeTele(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            me->NearTeleportTo(homePosition);
            return true;
        }

    private:
        Creature* me;
    };

    class CastTrashingCharge : public BasicEvent
    {
    public:
        CastTrashingCharge(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            if (Unit* target = me->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 50.f, true))
                me->CastSpell(target, SPELL_TRASHING_CHARGE_UNK);

            for (uint8 i = 0; i < 4; ++i)
                me->CastCustomSpell(SPELL_TRASHING_CHARGE_VISUAL_SUMMON, SPELLVALUE_RADIUS_MOD, 5*i);

            me->CastSpell(me, SPELL_TRASHING_CHARGE_JUMP);

            me->m_Events.AddEvent(new CastTrashingCharge(me), me->m_Events.CalculateTime(10000));
            return true;
        }

    private:
        Creature* me;
    };

    class CastTrashingChargeKnockback : public BasicEvent
    {
    public:
        CastTrashingChargeKnockback(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            me->CastSpell(me, SPELL_TRASHING_CHARGE_KNOCKBACK, true);
            return true;
        }

    private:
        Creature* me;
    };

    class LeaveSubmergePhase : public BasicEvent
    {
    public:
        LeaveSubmergePhase(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            me->AI()->DoAction(ACTION_CORBORUS_LEAVE_SUBMERGE);
            return true;
        }

    private:
        Creature* me;
    };
}

using namespace Corborus;

class boss_corborus : public CreatureScript
{
public:
    boss_corborus() : CreatureScript("boss_corborus") { }

    struct boss_corborusAI : public BossAI
    {
        boss_corborusAI(Creature* creature) : BossAI(creature, DATA_CORBORUS) {}

        void Reset()
        {
            me->m_Events.KillAllEvents(false);
            DespawnMinions();

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
            me->SetReactState(REACT_AGGRESSIVE);

            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();

            events.ScheduleEvent(EVENT_CRYSTAL_BARRAGE, 13000);
            events.ScheduleEvent(EVENT_DAMPENING_WAVE, 5000);
            events.ScheduleEvent(EVENT_ENTER_SUBMERGE, 28000);

        }

        void UpdateAI(uint32 diff)
        {
            if (!events.Empty())
                events.Update(diff);

            if(me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CRYSTAL_BARRAGE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.f))
                            DoCast(target, SPELL_CRYSTAL_BARRAGE);

                        events.ScheduleEvent(EVENT_CRYSTAL_BARRAGE, urand(25000, 30000));
                        break;
                    }
                case EVENT_DAMPENING_WAVE:
                    {
                        DoCast(me, SPELL_DAMPENING_WAVE);

                        events.ScheduleEvent(EVENT_DAMPENING_WAVE, urand(10000, 20000));
                        break;
                    }
                case EVENT_ENTER_SUBMERGE:
                    {
                        events.Reset();

                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
                        me->RemoveAllAuras();

                        DoCast(SPELL_SUBMERGE);

                        me->m_Events.AddEvent(new CastTrashingCharge(me), me->m_Events.CalculateTime(10000));
                        me->m_Events.AddEvent(new LeaveSubmergePhase(me), me->m_Events.CalculateTime(25000));
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_CORBORUS_DO_INTRO:
                {
                    DoCast(SPELL_RING_WYRM_CHARGE);

                    if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_BROKEN_ROCKDOOR)))
                        go->SetGoState(GO_STATE_ACTIVE);

                    me->SetHomePosition(homePosition);

                    std::list<Creature*> hitCreatures;

                    for (uint8 i = 0; i < 3; ++i)
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, CorborusEventNpcs[i], 150.f);

                        hitCreatures.merge(creatures);
                    }

                    hitCreatures.remove_if(HomePositionDistanceSelector());

                    for (std::list<Creature*>::const_iterator itr = hitCreatures.begin(); itr != hitCreatures.end(); ++itr)
                    {
                        (*itr)->CastSpell((*itr), SPELL_RING_WYRM_KNOCKBACK);
                        (*itr)->DespawnOrUnsummon(urand(10000, 15000));
                        me->Kill((*itr));
                    }

                    me->m_Events.AddEvent(new HomeTele(me), me->m_Events.CalculateTime(1200));
                    break;
                }
            case ACTION_CORBORUS_LEAVE_SUBMERGE:
                {
                    me->m_Events.KillAllEvents(false);

                    me->RemoveAllAuras();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
                    me->SetReactState(REACT_AGGRESSIVE);

                    events.ScheduleEvent(EVENT_CRYSTAL_BARRAGE, 8000);
                    events.ScheduleEvent(EVENT_ENTER_SUBMERGE, 90000);
                    break;
                }
            }
        }

        void JustSummoned(Creature* summon)
        {
            /*
            if (summon->GetEntry() == NPC_TRASHING_CHARGE)
                summon->m_Events.AddEvent(new CastTrashingChargeKnockback(summon), summon->m_Events.CalculateTime(3500));
                */
        }

        void JustDied(Unit* /*killer*/)
        {
            me->m_Events.KillAllEvents(false);
            DespawnMinions();
            _JustDied();
        }

        void DespawnMinions()
        {
            me->DespawnCreaturesInArea(NPC_TRASHING_CHARGE);
            me->DespawnCreaturesInArea(NPC_ROCK_BORER);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_corborusAI (creature);
    }
};

void AddSC_boss_corborus()
{
    new boss_corborus();
}
