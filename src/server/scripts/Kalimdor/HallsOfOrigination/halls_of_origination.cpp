
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
#include "halls_of_origination.h"

class go_hoo_lift_console : public GameObjectScript
{
public:
    go_hoo_lift_console() : GameObjectScript("go_hoo_lift_console") { }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action)
    {
            if (sender != GOSSIP_SENDER_MAIN)
                return false;
            if (!player->getAttackers().empty())
                return false;
        switch (action)
        {
            case 200: // Bring to first floor
                if (player->GetPositionZ() > 90.0f)
                    if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 500.0f))
                    {
                        elevator->SetLootState(GO_READY);
                        elevator->UseDoorOrButton(5000);
                    }
                break;
            case 201: // Bring to second floor
                if (player->GetPositionZ() < 90.0f)
                    if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 500.0f))
                    {
                        elevator->SetLootState(GO_READY);
                        elevator->UseDoorOrButton(5000);
                    }
                break;
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {

        if (InstanceScript* instance = go->GetInstanceScript())
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to first floor.", GOSSIP_SENDER_MAIN, 200);
            if (instance->GetBossState(DATA_ANRAPHET) == DONE || instance->GetBossState(DATA_EARTHRAGER_PTAH) == DONE) // if anraphet or ptah is defeated
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to second floor.", GOSSIP_SENDER_MAIN, 201);
        }

        player->SEND_GOSSIP_MENU(go->GetGOInfo()->GetGossipMenuId(), go->GetGUID());
        return true;
    }
};

class spell_hoo_transit_device : public SpellScriptLoader
{
    public:
        spell_hoo_transit_device() : SpellScriptLoader("spell_hoo_transit_device") { }

        class spell_hoo_transit_device_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_hoo_transit_device_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                    if (InstanceScript* instance = caster->GetInstanceScript())
                        if (!caster->isInCombat())
                            if (instance->GetBossState(DATA_TEMPLE_GUARDIAN_ANHUUR) == DONE)
                                return SPELL_CAST_OK;

                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_hoo_transit_device_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_hoo_transit_device_SpellScript();
        }
};

enum ServantSpells
{
    SPELL_SEARING_FLAMES    = 74101,
    SPELL_DISPERSION_1      = 88097,
    SPELL_DISPERSION_2      = 88100,
};

enum ServantEvents
{
    EVENT_DISPERSION_END = 1,
    EVENT_SEARING_FLAMES,
};

class npc_hoo_sun_touched_servant : public CreatureScript
{
public:
    npc_hoo_sun_touched_servant() : CreatureScript("npc_hoo_sun_touched_servant") { }

    struct npc_hoo_sun_touched_servantAI : public ScriptedAI
    {
        npc_hoo_sun_touched_servantAI(Creature* creature) : ScriptedAI(creature)
        {
            _dispersed = false;
        }

        bool _dispersed;
        EventMap events;

        void IsSummonedBy(Unit* /*creator*/)
        {
            if (Player* player = me->FindNearestPlayer(100.0f, true))
                me->AI()->AttackStart(player);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SEARING_FLAMES, urand (1000, 3000));
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            if (damage > me->GetHealth() && me->GetEntry() != NPC_SUN_TOUCHED_SPRITELING)
            {
                damage = 0;

                me->SetHealth(1);
                me->AttackStop();
                events.CancelEvent(EVENT_SEARING_FLAMES);
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MovementExpired();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if (!_dispersed)
                {
                    switch (me->GetEntry())
                    {
                        case NPC_SUN_TOUCHED_SERVANT:
                            DoCast(SPELL_DISPERSION_1);
                            events.ScheduleEvent(EVENT_DISPERSION_END, 3100);
                            break;
                        case NPC_SUN_TOUCHED_SPRITE:
                            DoCast(SPELL_DISPERSION_2);
                            events.ScheduleEvent(EVENT_DISPERSION_END, 3100);
                            break;
                        default:
                            break;
                    }
                    _dispersed = true;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !_dispersed)
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DISPERSION_END:
                        me->Kill(me, false);
                        break;
                    case EVENT_SEARING_FLAMES:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_SEARING_FLAMES);
                        events.ScheduleEvent(EVENT_SEARING_FLAMES, urand(8000, 9000));
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
        return new npc_hoo_sun_touched_servantAI(creature);
    }
};

enum SpeakerSpells
{
    SPELL_FLAME_RING_VISUAL = 74632,
    SPELL_FIRRSTORM         = 73861,
};

enum SpeakerEvents
{
    EVENT_FLAME_RING = 1,
    EVENT_FIRESTORM,
};

enum SpeakerPhases
{
    PHASE_INTRO = 1,
    PHASE_COMBAT = 2,
};

class npc_hoo_sun_touched_speaker : public CreatureScript
{
public:
    npc_hoo_sun_touched_speaker() : CreatureScript("npc_hoo_sun_touched_speaker") { }

    struct npc_hoo_sun_touched_speakerAI : public ScriptedAI
    {
        npc_hoo_sun_touched_speakerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.SetPhase(PHASE_INTRO);
            events.ScheduleEvent(EVENT_FLAME_RING, 3000);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.CancelEvent(EVENT_FLAME_RING);
            events.SetPhase(PHASE_COMBAT);
            events.ScheduleEvent(EVENT_FIRESTORM, 4000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.SetPhase(PHASE_INTRO);
            events.Reset();
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
                    case EVENT_FLAME_RING:
                        DoCast(SPELL_FLAME_RING_VISUAL);
                        events.ScheduleEvent(EVENT_FLAME_RING, 12000);
                        break;
                    case EVENT_FIRESTORM:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_FIRRSTORM);
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
        return new npc_hoo_sun_touched_speakerAI(creature);
    }
};

class spell_hoo_flame_ring_script : public SpellScriptLoader
{
public:
    spell_hoo_flame_ring_script() : SpellScriptLoader("spell_hoo_flame_ring_script") { }

    class spell_hoo_flame_ring_script_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_flame_ring_script_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            std::list<WorldObject*>::iterator it = unitList.begin();

            while (it != unitList.end())
            {
                if (!GetCaster())
                    return;

                WorldObject* unit = *it;

                if (unit->GetEntry() != NPC_SUN_TOUCHED_SERVANT)
                    it = unitList.erase(it);
                else
                    it++;
            }
            Trinity::Containers::RandomResizeList(unitList, 1);
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetHitUnit(), GetSpellInfo()->Effects[EFFECT_0].BasePoints, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_flame_ring_script_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_hoo_flame_ring_script_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_flame_ring_script_SpellScript();
    }
};

class npc_hoo_dustbone_horror : public CreatureScript
{
public:
    npc_hoo_dustbone_horror() : CreatureScript("npc_hoo_dustbone_horror")
    {
    }

    struct npc_hoo_dustbone_horrorAI : public ScriptedAI
    {
        npc_hoo_dustbone_horrorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_SMASH     = 75453
        };

        enum eventId
        {
            EVENT_SUBMERGE          = 1,
            EVENT_MAKE_ATTACKABLE,
            EVENT_CAST_SMASH
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SUBMERGE, 1);
        }

        void EnterCombat(Unit* who)
        {
            me->RemoveFlag(UNIT_FIELD_BYTES_1, 9);
            events.ScheduleEvent(EVENT_MAKE_ATTACKABLE, 6000);
            events.ScheduleEvent(EVENT_CAST_SMASH, 10000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
            events.ScheduleEvent(EVENT_SUBMERGE, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUBMERGE:
                    {
                        if (!me->isInCombat() && !me->IsInEvadeMode() && !me->isMoving())
                        {
                            me->SetFlag(UNIT_FIELD_BYTES_1, 9);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                            me->SetControlled(true, UNIT_STATE_ROOT);
                            events.CancelEvent(EVENT_SUBMERGE);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SUBMERGE, 1000);
                        break;
                    }
                    case EVENT_CAST_SMASH:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SMASH);
                        events.RescheduleEvent(EVENT_CAST_SMASH, urand(10000, 12500));
                        break;
                    }
                    case EVENT_MAKE_ATTACKABLE:
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        events.CancelEvent(EVENT_MAKE_ATTACKABLE);
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_dustbone_horrorAI(creature);
    }
};

class npc_hoo_venomous_skitterer : public CreatureScript
{
public:
    npc_hoo_venomous_skitterer() : CreatureScript("npc_hoo_venomous_skitterer")
    {
    }

    struct npc_hoo_venomous_skittererAI : public ScriptedAI
    {
        npc_hoo_venomous_skittererAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_BLINDING_TOXIN        = 73963,
            SPELL_DEBILITATING_VENOM    = 74121,
            SPELL_SURGE                 = 75158
        };

        enum eventId
        {
            EVENT_SUBMERGE = 1,
            EVENT_MAKE_ATTACKABLE,
            EVENT_BLINDING_TOXIN,
            EVENT_SURGE,
            EVENT_DEBILITATING_VENOM
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SUBMERGE, 1);
        }

        void EnterCombat(Unit* who)
        {
            me->RemoveFlag(UNIT_FIELD_BYTES_1, 9);
            events.ScheduleEvent(EVENT_MAKE_ATTACKABLE, 2000);
            events.ScheduleEvent(EVENT_BLINDING_TOXIN, 10000);
            events.ScheduleEvent(EVENT_SURGE, 7000);
            events.ScheduleEvent(EVENT_DEBILITATING_VENOM, urand(8000, 15000));
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
            events.ScheduleEvent(EVENT_SUBMERGE, 2000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUBMERGE:
                    {
                        if (!me->isInCombat() && !me->IsInEvadeMode() && !me->isMoving())
                        {
                            me->SetFlag(UNIT_FIELD_BYTES_1, 9);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                            me->SetControlled(true, UNIT_STATE_ROOT);
                            events.CancelEvent(EVENT_SUBMERGE);
                            break;
                        }
                        events.RescheduleEvent(EVENT_SUBMERGE, 1000);
                        break;
                    }
                    case EVENT_SURGE:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SURGE);
                        events.RescheduleEvent(EVENT_SURGE, urand(10000, 12500));
                        break;
                    }
                    case EVENT_BLINDING_TOXIN:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_BLINDING_TOXIN);
                        events.RescheduleEvent(EVENT_BLINDING_TOXIN, urand(15000, 20000));
                        break;
                    }
                    case EVENT_DEBILITATING_VENOM:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_DEBILITATING_VENOM);
                        events.RescheduleEvent(EVENT_DEBILITATING_VENOM, urand(5000, 7500));
                        break;
                    }
                    case EVENT_MAKE_ATTACKABLE:
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        events.CancelEvent(EVENT_MAKE_ATTACKABLE);
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_venomous_skittererAI(creature);
    }
};

void AddSC_halls_of_origination()
{
    new go_hoo_lift_console();
    new spell_hoo_transit_device();
    new npc_hoo_sun_touched_servant();
    new npc_hoo_sun_touched_speaker();
    new spell_hoo_flame_ring_script();
    new npc_hoo_dustbone_horror();
    new npc_hoo_venomous_skitterer();
}
