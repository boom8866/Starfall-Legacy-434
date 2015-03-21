
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
            case 200: // Bring to base floor
            {
                if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 1000.0f))
                    elevator->SetGoState(GO_STATE_ACTIVE);
                break;
            }
            case 201: // Bring to first floor
            {
                if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 1000.0f))
                    elevator->SetGoState(GO_STATE_READY);
                break;
            }
            case 202: // Bring to 2nd floor
            {
                if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 1000.0f))
                    elevator->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                break;
            }
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (InstanceScript* instance = go->GetInstanceScript())
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to base floor", GOSSIP_SENDER_MAIN, 200);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to first floor.", GOSSIP_SENDER_MAIN, 201);

            // Only if Ptah or Anraphet are dead
            if (instance->GetBossState(DATA_ANRAPHET) == DONE || instance->GetBossState(DATA_EARTHRAGER_PTAH) == DONE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to second floor.", GOSSIP_SENDER_MAIN, 202);
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
                me->StopMoving();
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
            SPELL_SURGE                 = 75158,
            SPELL_EMERGE                = 75764
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
            me->CastWithDelay(500, me, SPELL_EMERGE, true);
            events.ScheduleEvent(EVENT_MAKE_ATTACKABLE, 1500);
            events.ScheduleEvent(EVENT_BLINDING_TOXIN, 10000);
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
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 65.0f, true))
                            DoCast(target, SPELL_SURGE);
                        events.RescheduleEvent(EVENT_SURGE, 25000);
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
                        events.ScheduleEvent(EVENT_SURGE, 2000);
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

class npc_hoo_water_warden : public CreatureScript
{
public:
    npc_hoo_water_warden() : CreatureScript("npc_hoo_water_warden")
    {
    }

    struct npc_hoo_water_wardenAI : public ScriptedAI
    {
        npc_hoo_water_wardenAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_AQUA_BOMB_AURA    = 77349,
            SPELL_WATER_BUBBLE      = 77335,
            SPELL_BUBBLE_BOUND      = 77336
        };

        enum eventId
        {
            EVENT_WATER_BUBBLE  = 1
        };

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(SPELL_AQUA_BOMB_AURA);
            events.ScheduleEvent(EVENT_WATER_BUBBLE, 11000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            me->DespawnCreaturesInArea(NPC_AQUA_BOMB);
            me->DespawnCreaturesInArea(NPC_WATER_BUBBLE);
            if (InstanceScript* instance = me->GetInstanceScript())
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BUBBLE_BOUND);
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnCreaturesInArea(NPC_AQUA_BOMB);
            me->DespawnCreaturesInArea(NPC_WATER_BUBBLE);
            if (InstanceScript* instance = me->GetInstanceScript())
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BUBBLE_BOUND);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_WATER_BUBBLE:
                    {
                        DoCast(SPELL_WATER_BUBBLE);
                        events.RescheduleEvent(EVENT_WATER_BUBBLE, 16000);
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
        return new npc_hoo_water_wardenAI(creature);
    }
};

class PlayerBubbleCheck
{
public:
    PlayerBubbleCheck()
    {
    }

    enum spellId
    {
        SPELL_BUBBLE_BOUND_N    = 77336,
        SPELL_BUBBLE_BOUND_H    = 91158
    };

    bool operator()(WorldObject* object)
    {
        return (object->ToUnit()->HasAura(SPELL_BUBBLE_BOUND_N) || object->ToUnit()->HasAura(SPELL_BUBBLE_BOUND_H));
    }
};

class spell_hoo_water_bubble : public SpellScriptLoader
{
public:
    spell_hoo_water_bubble() : SpellScriptLoader("spell_hoo_water_bubble")
    {
    }

    class spell_hoo_water_bubble_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_water_bubble_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(PlayerBubbleCheck());

            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_water_bubble_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_water_bubble_SpellScript();
    }
};

class npc_hoo_water_bubble : public CreatureScript
{
public:
    npc_hoo_water_bubble() : CreatureScript("npc_hoo_water_bubble")
    {
    }

    struct npc_hoo_water_bubbleAI : public ScriptedAI
    {
        npc_hoo_water_bubbleAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        enum spellId
        {
            SPELL_BUBBLE_BOUND  = 77336
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetHealth(me->GetMaxHealth());
            me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 2, 5.0f, 5.0f, 0);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Player* player = me->FindNearestPlayer(1.0f, true))
                player->RemoveAurasDueToSpell(SPELL_BUBBLE_BOUND);
            me->DespawnOrUnsummon(1000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_water_bubbleAI(creature);
    }
};

class npc_hoo_air_warden : public CreatureScript
{
public:
    npc_hoo_air_warden() : CreatureScript("npc_hoo_air_warden")
    {
    }

    struct npc_hoo_air_wardenAI : public ScriptedAI
    {
        npc_hoo_air_wardenAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_WHIRLING_WINDS    = 77316,
            SPELL_WIND_SHEAR        = 77334
        };

        enum eventId
        {
            EVENT_WHIRLING_WINDS    = 1,
            EVENT_WIND_SHEAR
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_WHIRLING_WINDS, 5000);
            events.ScheduleEvent(EVENT_WIND_SHEAR, 7000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            me->DespawnCreaturesInArea(NPC_WHIRLING_WINDS);
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnCreaturesInArea(NPC_WHIRLING_WINDS);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_WHIRLING_WINDS:
                    {
                        DoCast(me, SPELL_WHIRLING_WINDS, true);
                        events.RescheduleEvent(EVENT_WHIRLING_WINDS, 10000);
                        break;
                    }
                    case EVENT_WIND_SHEAR:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_BOTTOMAGGRO, 0, 60.0f, true))
                            DoCast(target, SPELL_WIND_SHEAR);
                        events.RescheduleEvent(EVENT_WIND_SHEAR, 14000);
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
        return new npc_hoo_air_wardenAI(creature);
    }
};

class npc_hoo_whirling_winds : public CreatureScript
{
public:
    npc_hoo_whirling_winds() : CreatureScript("npc_hoo_whirling_winds")
    {
    }

    struct npc_hoo_whirling_windsAI : public ScriptedAI
    {
        npc_hoo_whirling_windsAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_WHIRLING_WIND_AURA    = 77321
        };

        enum eventId
        {
            EVENT_FOLLOW_PLAYER     = 1
        };

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetWalk(true);
            me->SetSpeed(MOVE_WALK, 0.5f, true);
            me->SetSpeed(MOVE_RUN, 0.5f, true);
            DoCast(me, SPELL_WHIRLING_WIND_AURA, true);
            events.ScheduleEvent(EVENT_FOLLOW_PLAYER, 100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FOLLOW_PLAYER:
                    {
                        if (me->isMoving())
                        {
                            events.RescheduleEvent(EVENT_FOLLOW_PLAYER, 1000);
                            break;
                        }

                        me->GetMotionMaster()->MovementExpired();
                        if (Player* target = me->FindNearestPlayer(125.0f, true))
                            me->GetMotionMaster()->MoveChase(target, 0.0f, 0.0f);
                        events.RescheduleEvent(EVENT_FOLLOW_PLAYER, 2000);
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
        return new npc_hoo_whirling_windsAI(creature);
    }
};

class npc_hoo_flame_warden : public CreatureScript
{
public:
    npc_hoo_flame_warden() : CreatureScript("npc_hoo_flame_warden")
    {
    }

    struct npc_hoo_flame_wardenAI : public ScriptedAI
    {
        npc_hoo_flame_wardenAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_LAVA_ERUPTION     = 77273,
            SPELL_RAGING_INFERNO    = 77241
        };

        enum eventId
        {
            EVENT_LAVA_ERUPTION     = 1,
            EVENT_RAGING_INFERNO
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_LAVA_ERUPTION, 2000);
            events.ScheduleEvent(EVENT_RAGING_INFERNO, 6000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            events.Reset();
        }

        void JustDied(Unit* /*killer*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RAGING_INFERNO:
                    {
                        DoCast(me, SPELL_RAGING_INFERNO, true);
                        events.RescheduleEvent(EVENT_RAGING_INFERNO, 16000);
                        break;
                    }
                    case EVENT_LAVA_ERUPTION:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 125.0f, true))
                            DoCast(target, SPELL_LAVA_ERUPTION, true);
                        events.RescheduleEvent(EVENT_LAVA_ERUPTION, 10000);
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
        return new npc_hoo_flame_wardenAI(creature);
    }
};

class spell_hoo_lava_eruption : public SpellScriptLoader
{
public:
    spell_hoo_lava_eruption() : SpellScriptLoader("spell_hoo_lava_eruption")
    {
    }

    class spell_hoo_lava_eruption_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_lava_eruption_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_lava_eruption_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_lava_eruption_SpellScript();
    }
};

class npc_hoo_earth_warden : public CreatureScript
{
public:
    npc_hoo_earth_warden() : CreatureScript("npc_hoo_earth_warden")
    {
    }

    struct npc_hoo_earth_wardenAI : public ScriptedAI
    {
        npc_hoo_earth_wardenAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_ROCKWAVE  = 77234,
            SPELL_IMPALE    = 77235
        };

        enum eventId
        {
            EVENT_ROCKWAVE  = 1,
            EVENT_IMPALE
        };

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ROCKWAVE, 7000);
            events.ScheduleEvent(EVENT_IMPALE, 10000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            events.Reset();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ROCKWAVE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 125.0f, true))
                            DoCast(target, SPELL_ROCKWAVE);
                        events.RescheduleEvent(EVENT_ROCKWAVE, 13000);
                        break;
                    }
                    case EVENT_IMPALE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 125.0f, true))
                            DoCast(target, SPELL_IMPALE);
                        events.RescheduleEvent(EVENT_IMPALE, 13000);
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
        return new npc_hoo_earth_wardenAI(creature);
    }
};

class npc_hoo_jeweled_scarab : public CreatureScript
{
public:
    npc_hoo_jeweled_scarab() : CreatureScript("npc_hoo_jeweled_scarab")
    {
    }

    struct npc_hoo_jeweled_scarabAI : public ScriptedAI
    {
        npc_hoo_jeweled_scarabAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_SURGE     = 75158,
            SPELL_SUBMERGE  = 76084,
            SPELL_EMERGE    = 75764
        };

        enum eventId
        {
            EVENT_SUBMERGE          = 1,
            EVENT_MAKE_ATTACKABLE,
            EVENT_SURGE
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SUBMERGE, 1);
        }

        void EnterCombat(Unit* who)
        {
            me->RemoveFlag(UNIT_FIELD_BYTES_1, 9);
            me->CastWithDelay(500, me, SPELL_EMERGE, true);
            events.ScheduleEvent(EVENT_MAKE_ATTACKABLE, 2500);
            events.ScheduleEvent(EVENT_SURGE, 3000);
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
                    case EVENT_MAKE_ATTACKABLE:
                    {
                        me->RemoveFlag(UNIT_FIELD_BYTES_1, 9);
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
        return new npc_hoo_jeweled_scarabAI(creature);
    }
};

class npc_hoo_blistering_scarab : public CreatureScript
{
public:
    npc_hoo_blistering_scarab() : CreatureScript("npc_hoo_blistering_scarab")
    {
    }

    struct npc_hoo_blistering_scarabAI : public ScriptedAI
    {
        npc_hoo_blistering_scarabAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_CORROSIVE_SPRAY   = 74122,
            SPELL_SERRATED_SLASH    = 74542,
            SPELL_SUBMERGE          = 76084,
            SPELL_EMERGE            = 75764
        };

        enum eventId
        {
            EVENT_SUBMERGE          = 1,
            EVENT_MAKE_ATTACKABLE,
            EVENT_CORROSIVE_SPRAY,
            EVENT_SERRATED_SLASH
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SUBMERGE, 1);
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->RemoveFlag(UNIT_FIELD_BYTES_1, 9);
            me->CastWithDelay(500, me, SPELL_EMERGE, true);
            events.ScheduleEvent(EVENT_MAKE_ATTACKABLE, 1500);
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
                    case EVENT_CORROSIVE_SPRAY:
                    {
                        DoCast(SPELL_CORROSIVE_SPRAY);
                        events.RescheduleEvent(EVENT_CORROSIVE_SPRAY, urand(10000, 12500));
                        break;
                    }
                    case EVENT_SERRATED_SLASH:
                    {
                        if (Unit* victim = me->getVictim())
                            DoCast(victim, SPELL_SERRATED_SLASH, true);
                        events.RescheduleEvent(EVENT_SERRATED_SLASH, 10000);
                        break;
                    }
                    case EVENT_MAKE_ATTACKABLE:
                    {
                        DoCast(SPELL_CORROSIVE_SPRAY);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        events.ScheduleEvent(EVENT_CORROSIVE_SPRAY, 5000);
                        events.ScheduleEvent(EVENT_SERRATED_SLASH, 8000);
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
        return new npc_hoo_blistering_scarabAI(creature);
    }
};

class npc_hoo_dustbone_tormentor : public CreatureScript
{
public:
    npc_hoo_dustbone_tormentor() : CreatureScript("npc_hoo_dustbone_tormentor")
    {
    }

    struct npc_hoo_dustbone_tormentorAI : public ScriptedAI
    {
        npc_hoo_dustbone_tormentorAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_CURSE_OF_EXHAUSTION   = 77357,
            SPELL_SHADOW_BOLT           = 77570,
            SPELL_EMERGE                = 75764
        };

        enum eventId
        {
            EVENT_SUBMERGE              = 1,
            EVENT_MAKE_ATTACKABLE,
            EVENT_SHADOWBOLT,
            EVENT_CURSE_OF_EXHAUSTION
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_SUBMERGE, 1);
        }

        void EnterCombat(Unit* who)
        {
            me->RemoveFlag(UNIT_FIELD_BYTES_1, 9);
            DoCast(me, SPELL_EMERGE, true);
            events.ScheduleEvent(EVENT_MAKE_ATTACKABLE, 6000);
            events.ScheduleEvent(EVENT_SHADOWBOLT, 3000);
            events.ScheduleEvent(EVENT_CURSE_OF_EXHAUSTION, 1000);
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
                    case EVENT_SHADOWBOLT:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 35.0f, true))
                            DoCast(target, SPELL_SHADOW_BOLT);
                        events.RescheduleEvent(EVENT_SHADOWBOLT, urand(4500, 6500));
                        break;
                    }
                    case EVENT_CURSE_OF_EXHAUSTION:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 35.0f, true))
                            DoCast(target, SPELL_CURSE_OF_EXHAUSTION);
                        events.RescheduleEvent(EVENT_CURSE_OF_EXHAUSTION, 9000);
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
        return new npc_hoo_dustbone_tormentorAI(creature);
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
    new npc_hoo_water_warden();
    new spell_hoo_water_bubble();
    new npc_hoo_water_bubble();
    new npc_hoo_air_warden();
    new npc_hoo_whirling_winds();
    new npc_hoo_flame_warden();
    new spell_hoo_lava_eruption();
    new npc_hoo_earth_warden();
    new npc_hoo_jeweled_scarab();
    new npc_hoo_blistering_scarab();
    new npc_hoo_dustbone_tormentor();
}
