
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
    SPELL_FACE_RADOM_PLAYER             = 82530,

    ////////////////////////////////////////////
    // STALAKTIT Handling
    SPELL_STALAKTIT_ATTACK              = 80656, //     SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_STALAKTIT                     = 81027, // +-- SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_STALAKTIT_UNK                 = 81035, // +-> SPELL_EFFECT_DUMMY
    SPELL_STALAKTIT_UNK2                = 80654, //     SPELL_EFFECT_PERSISTENT_AREA_AURA (casted from boss triggers)
    SPELL_STALAKTIT_GOB_SUMMON_TRIGGER  = 80643, // +-- SPELL_EFFECT_TRIGGER_MISSILE
    SPELL_STALAKTIT_GOB_SUMMON          = 80647, // +-> SPELL_EFFECT_SUMMON_OBJECT_WILD, SPELL_EFFECT_SCHOOL_DAMAGE
    SPELL_STALAKTIT_TRIGGER_SUMMON_R20  = 81028, //     SPELL_EFFECT_SUMMON (Entry: 43159) - Radius (Id 9)  20,00
    SPELL_STALAKTIT_TRIGGER_SUMMON_R40  = 80650, //     SPELL_EFFECT_SUMMON (Entry: 43159) - Radius (Id 23) 40,00

    ////////////////////////////////////////////
    // Normal Abilities
    SPELL_LAVA_FISSURE                  = 80803, //     SPELL_EFFECT_SUMMON (Entry: 43242)
    SPELL_SAND_BLAST                    = 80807, //     SPELL_EFFECT_SCHOOL_DAMAGE

    SPELL_CRYSTAL_STORM                 = 92265, //     3X SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_CRYSTAL_STORM_UNK             = 92251, //     SPELL_EFFECT_DUMMY
    SPELL_CRYSTAL_STORM_DAMAGE          = 92300, //     SPELL_EFFECT_SCHOOL_DAMAGE (Needs a filter)
};

enum Events
{
    EVENT_LAVA_FISSURE  = 1,
    EVENT_SAND_BLAST    = 2,
    EVENT_STALAKTITS    = 3,
    EVENT_CRYSTAL_STORM = 4
};

enum Points
{
    POINT_TAKEOFF,
    POINT_LAND
};

namespace Slabhide
{
    float const groudZ = 247.2f;

    Position const airPosition = {1283.036621f, 1218.074097f, groudZ + 35.f, 0};

    class CastStalaktits : public BasicEvent
    {
    public:
        CastStalaktits(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            me->UpdatePosition(airPosition, false);
            me->CastSpell(me, SPELL_STALAKTIT_ATTACK);
            return true;
        }

    private:
        Creature* me;
    };

    class MoveLand : public BasicEvent
    {
    public:
        MoveLand(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            Position pos = *me;
            me->GetRandomNearPosition(pos, frand(3.f, 5.f));

            pos.m_orientation = groudZ;

            me->SetDisableGravity(false);
            me->GetMotionMaster()->MoveLand(POINT_LAND, pos);
            return true;
        }

    private:
        Creature* me;
    };
}

using namespace Slabhide;

class boss_slabhide : public CreatureScript
{
public:
    boss_slabhide() : CreatureScript("boss_slabhide") { }

    struct boss_slabhideAI : public BossAI
    {
        boss_slabhideAI(Creature* creature) : BossAI(creature, DATA_SLABHIDE), isIntroDone(true) {}

        bool isIntroDone;

        void Reset()
        {
            if (isIntroDone)
            {
                me->SetDisableGravity(false);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
                me->SetReactState(REACT_AGGRESSIVE);
            }
            else
            {
                me->SetDisableGravity(true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
                me->SetReactState(REACT_PASSIVE);
            }

            DespawnMinions();
            me->m_Events.KillAllEvents(false);
            _Reset();
        }

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_STALAKTITS, 8000);
            _EnterCombat();
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
                case EVENT_LAVA_FISSURE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.f))
                            DoCast(target, SPELL_LAVA_FISSURE);

                        events.ScheduleEvent(EVENT_LAVA_FISSURE, 10000);
                        break;
                    }
                case EVENT_SAND_BLAST:
                    {
                        DoCastVictim(SPELL_SAND_BLAST);

                        events.ScheduleEvent(EVENT_SAND_BLAST, 10000);
                        break;
                    }
                case EVENT_STALAKTITS:
                    {
                        events.DelayEvents(IsHeroic() ? 33000 : 21000);

                        me->SetDisableGravity(true);
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, airPosition);

                        me->m_Events.AddEvent(new CastStalaktits(me), me->m_Events.CalculateTime(3000));
                        me->m_Events.AddEvent(new MoveLand(me), me->m_Events.CalculateTime(13000));

                        if (IsHeroic())
                            events.ScheduleEvent(EVENT_CRYSTAL_STORM, 17000);

                        events.ScheduleEvent(EVENT_STALAKTITS, 65000);
                        break;
                    }
                case EVENT_CRYSTAL_STORM:
                    {
                        DoCast(me, SPELL_CRYSTAL_STORM, true);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void DespawnMinions()
        {
            me->DespawnCreaturesInArea(NPC_LAVA_FISSURE);
            me->DespawnCreaturesInArea(NPC_STALAKTIT_TRIGGER_BOSS);
            
            std::list<GameObject*> stalaktites;
            me->GetGameObjectListWithEntryInGrid(stalaktites, GO_STALAKTIT, 150.f);

            for (std::list<GameObject*>::const_iterator itr = stalaktites.begin(); itr != stalaktites.end(); ++itr)
                (*itr)->Delete();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->m_Events.KillAllEvents(false);
            DespawnMinions();
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_slabhideAI (creature);
    }
};

class npc_stalaktit : public CreatureScript
{
public:
    npc_stalaktit() : CreatureScript("npc_stalaktit") { }

    struct npc_stalaktitAI : public PassiveAI
    {
        npc_stalaktitAI(Creature* creature) : PassiveAI(creature), summonedStalaktit(false), uiStalaktitTimer(3000) {}

        uint32 uiStalaktitTimer;
        bool summonedStalaktit;

        void Reset()
        {
            DoCast(me, SPELL_STALAKTIT_UNK2, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (!summonedStalaktit)
                if (uiStalaktitTimer <= diff)
                {
                    summonedStalaktit = true;

                    me->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), groudZ, 0);
                    me->DestroyForNearbyPlayers();

                    DoCast(SPELL_STALAKTIT_GOB_SUMMON_TRIGGER);
                }
                else
                    uiStalaktitTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stalaktitAI (creature);
    }
};

// 92300 Crystal Storm
class spell_crystal_storm : public SpellScriptLoader
{
public:
    spell_crystal_storm() : SpellScriptLoader("spell_crystal_storm") { }

    class spell_crystal_storm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_crystal_storm_SpellScript);

        class BehindStalaktiteSelector
        {
        public:
            BehindStalaktiteSelector(WorldObject* unit) : caster(unit) {}

            bool operator() (WorldObject* unit)
            {
                return !unit->IsWithinLOSInMap(caster);
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
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_crystal_storm_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_crystal_storm_SpellScript();
    }
};

// 80650 Stalactite
class spell_stalactite : public SpellScriptLoader
{
public:
    spell_stalactite() : SpellScriptLoader("spell_stalactite") {}

    class spell_stalactite_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_stalactite_SpellScript);

        void HandleLaunch(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                Position pos = {caster->GetPositionX() + frand(-20.f, 20.f), caster->GetPositionZ() + frand(-20.f, 20.f), groudZ};
                
                caster->SummonCreature(NPC_STALAKTIT_TRIGGER_BOSS, pos);

                PreventHitDefaultEffect(effIndex);
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_stalactite_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_stalactite_SpellScript();
    }
};

void AddSC_boss_slabhide()
{
    new boss_slabhide();
    new npc_stalaktit();
    new spell_crystal_storm();
    new spell_stalactite();
}
