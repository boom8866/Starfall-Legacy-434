/*
* Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "InstanceScript.h"
#include "ScriptPCH.h"
#include "vortex_pinnacle.h"
#include "Vehicle.h"


uint8 Count;
bool active = true;

class npc_slipstream : public CreatureScript
{
public:
    npc_slipstream() : CreatureScript("npc_slipstream") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->CLOSE_GOSSIP_MENU();
        InstanceScript* instance = creature->GetInstanceScript();

        if (creature->GetDBTableGUIDLow() == 778156)
        {
            if (instance && instance->GetBossState(DATA_GRAND_VIZIER_ERTAN) == DONE)
            {
                if (!active)
                    return false;

                Count = 0;
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                creature->AddAura(85063, player);
                active = false;
                return true;
            }
            else
                return true;
        }

        if (creature->GetDBTableGUIDLow() == 778186)
        {
            if (instance && instance->GetBossState(DATA_ALTAIRUS) == DONE)
            {
                if (!active)
                    return true;

                Count = 3;
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                creature->AddAura(85063, player);
                active = false;
                return true;
            }
            else
                return true;
        }

        return false;
    }
};

class spell_slipstream : public SpellScriptLoader
{
public:
    spell_slipstream() : SpellScriptLoader("spell_slipstream") { }

    class spell_slipstream_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_slipstream_AuraScript);

        void HandleEffectApply(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (Unit* caster = GetCaster())
                    if (Vehicle* vehicle = caster->GetVehicleKit())
                        if (vehicle->HasEmptySeat(0))
                            target->EnterVehicle(caster, 0);
                        else
                            return;
            }
        }

        void HandleEffectRemove(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Vehicle* vehicle = caster->GetVehicleKit())
                    if (Unit* passenger = vehicle->GetPassenger(0))
                        if (Player* player = passenger->ToPlayer())
                        {
                            vehicle->RemoveAllPassengers();
                            switch(Count)
                            {
                            case 0:
                                if (Creature* creature = player->SummonCreature(45455,-848.227f, -68.724f, 656.22f, 0, TEMPSUMMON_TIMED_DESPAWN, 2000))
                                {
                                    player->SetFacingToObject(creature);
                                    creature->AddAura(85063, player);
                                    ++ Count;
                                }
                                break;
                            case 1:
                                if (Creature* creature = player->SummonCreature(45455,-844.885f, -205.135f, 662.708f, 0, TEMPSUMMON_TIMED_DESPAWN, 3000))
                                {
                                    player->SetFacingToObject(creature);
                                    creature->AddAura(85063, player);
                                    ++ Count;
                                }
                                break;
                            case 2:
                                player->GetMotionMaster()->MoveJump(-906.08f, -176.514f, 664.505f, 42, 20);
                                caster->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                                active = true;
                                break;
                            case 3: // 2nd part
                                if (Creature* creature = player->SummonCreature(45455,-1138.55f, 178.524f, 711.494f, 0, TEMPSUMMON_TIMED_DESPAWN, 3000))
                                {
                                    player->SetFacingToObject(creature);
                                    creature->AddAura(85063, player);
                                    ++ Count;
                                }
                                break;
                            case 4:
                                if (Creature* creature = player->SummonCreature(45455,-1245.21f, 230.986f, 690.608f, 0, TEMPSUMMON_TIMED_DESPAWN, 3000))
                                {
                                    player->SetFacingToObject(creature);
                                    creature->AddAura(85063, player);
                                    ++ Count;
                                }
                                break;
                            case 5:
                                if (Creature* creature = player->SummonCreature(45455,-1282.07f, 344.856f, 660.987f, 0, TEMPSUMMON_TIMED_DESPAWN, 3000))
                                {
                                    player->SetFacingToObject(creature);
                                    creature->AddAura(85063, player);
                                    ++ Count;
                                }
                                break;
                            case 6:
                                if (Creature* creature = player->SummonCreature(45455, -1229.64f, 412.26f, 641.293f, 0, TEMPSUMMON_TIMED_DESPAWN, 3000))
                                {
                                    player->SetFacingToObject(creature);
                                    creature->AddAura(85063, player);
                                    ++ Count;
                                }
                                break;
                            case 7:
                                player->GetMotionMaster()->MoveJump(-1193.627441f, 472.767853f, 634.782410f, 42, 20);
                                caster->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                                active = true;
                                break;
                            }
                        }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_slipstream_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_slipstream_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_slipstream_AuraScript();
    }
};

class spell_healing_well : public SpellScriptLoader
{
    public:
        spell_healing_well() : SpellScriptLoader("spell_healing_well") { }

        class spell_healing_well_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_healing_well_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->GetTypeId() != TYPEID_UNIT)
                    return;
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_healing_well_AuraScript::OnApply, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_healing_well_AuraScript();
        }
};

// Trash mobs
enum GustSoldierSpells
{
    SPELL_CHARGE        = 87930,
    SPELL_AIR_NOVA      = 87933,
    SPELL_WIND_BLAST    = 87923,
};

enum GustSoldierEvents
{
    EVENT_WIND_BLAST = 1,
    EVENT_CHARGE_PLAYER,
};

class npc_vp_gust_soldier : public CreatureScript
{
public:
    npc_vp_gust_soldier() : CreatureScript("npc_vp_gust_soldier") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_gust_soldierAI(creature);
    }

    struct npc_vp_gust_soldierAI : public ScriptedAI 
    {
        npc_vp_gust_soldierAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_CHARGE_PLAYER, urand(1000,3000));
            events.ScheduleEvent(EVENT_WIND_BLAST, urand(6000,8000));
        }

        void JustDied(Unit* /*killer*/)
        {
            DoCastAOE(SPELL_AIR_NOVA);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHARGE_PLAYER:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_CHARGE, true);
                    break;
                case EVENT_WIND_BLAST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_WIND_BLAST);
                    events.ScheduleEvent(EVENT_WIND_BLAST, urand(10000,14000));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

enum WildVortexSpells
{
    SPELL_WIND_SHOCK            = 88029,
    SPELL_LIGHTNING_BOLT_WIND   = 88032,
    SPELL_CYCLONE               = 88010,
};

enum WildVortexEvents
{
    EVENT_WIND_SHOCK = 1,
    EVENT_LIGHTNING_BOLT_WIND,
    EVENT_CYCLONE,
};

class npc_vp_wild_vortex : public CreatureScript
{
public:
    npc_vp_wild_vortex() : CreatureScript("npc_vp_wild_vortex") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_wild_vortexAI(creature);
    }

    struct npc_vp_wild_vortexAI : public ScriptedAI 
    {
        npc_vp_wild_vortexAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_WIND_SHOCK, urand(1200,10000));
            events.ScheduleEvent(EVENT_LIGHTNING_BOLT_WIND, urand(5000,13000));
            events.ScheduleEvent(EVENT_CYCLONE, urand(15000,18000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_WIND_SHOCK:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_WIND_SHOCK, true);
                    events.ScheduleEvent(EVENT_WIND_SHOCK, urand(3000,12000));
                    break;
                case EVENT_LIGHTNING_BOLT_WIND:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_LIGHTNING_BOLT_WIND, true);
                    events.ScheduleEvent(EVENT_LIGHTNING_BOLT_WIND, urand(8000,15000));
                    break;
                case EVENT_CYCLONE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 20.0f, true))
                        DoCast(target, SPELL_CYCLONE, true);
                    events.ScheduleEvent(EVENT_CYCLONE, urand(17000,20000));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

enum ArmoredMistralSpells
{
    SPELL_GALE_STRIKE       = 88061,
    SPELL_RISING_WINDS      = 88057,
    SPELL_STORM_SURGE       = 88055,
};

enum ArmoredMistralEvents
{
    EVENT_GALE_STRIKE = 1,
    EVENT_RISING_WINDS,
    EVENT_STORM_SURGE,
};

class npc_vp_armored_mistral : public CreatureScript
{
public:
    npc_vp_armored_mistral() : CreatureScript("npc_vp_armored_mistral") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_armored_mistralAI(creature);
    }

    struct npc_vp_armored_mistralAI : public ScriptedAI 
    {
        npc_vp_armored_mistralAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
            me->RemoveAurasDueToSpell(SPELL_RISING_WINDS);
        }

        void EnterCombat(Unit* /*target*/)
        {
            DoCast(me,SPELL_RISING_WINDS, true);

            events.ScheduleEvent(EVENT_GALE_STRIKE, urand(4000,8000));
            events.ScheduleEvent(EVENT_STORM_SURGE, urand(10000,12000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_GALE_STRIKE:
                    DoCast(me, SPELL_GALE_STRIKE, true);
                    events.ScheduleEvent(EVENT_GALE_STRIKE, urand(13000,17000));
                    break;
                case EVENT_STORM_SURGE:
                    if(me->HealthBelowPct(20))
                        DoCast(me, SPELL_STORM_SURGE, true);
                    events.ScheduleEvent(EVENT_STORM_SURGE, urand(2000,3800));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

enum CloudPrinceSpells
{
    SPELL_STARFALL      = 88073,
    SPELL_TYPHOON       = 88075,
};

enum CloudPrinceEvents
{
    EVENT_STARFALL = 1,
    EVENT_TYPHOON,
};

class npc_vp_cloud_prince : public CreatureScript
{
public:
    npc_vp_cloud_prince() : CreatureScript("npc_vp_cloud_prince") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_cloud_princeAI(creature);
    }

    struct npc_vp_cloud_princeAI : public ScriptedAI 
    {
        npc_vp_cloud_princeAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            for(uint8 i = 0; i<= 4; ++i)
                me->SummonCreature(NPC_WHIPPING_WIND, me->GetPositionX()+rand()%4, me->GetPositionY()+rand()%4, me->GetPositionZ());

            events.ScheduleEvent(EVENT_STARFALL, urand(8000,10000));
            events.ScheduleEvent(EVENT_TYPHOON, urand(6000,8000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_STARFALL:
                    DoCast(me, SPELL_STARFALL, true);
                    events.ScheduleEvent(EVENT_STARFALL, urand(8000,10000));
                    break;
                case EVENT_TYPHOON:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_TYPHOON, true);
                    events.ScheduleEvent(EVENT_TYPHOON, urand(6000,8000));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

enum WhippingWindSpells
{
    SPELL_LIGHTNING_BOLT      = 88080,
};

enum WhippingWindEvents
{
    EVENT_LIGHTNING_BOLT = 1,
};

class npc_vp_whipping_wind : public CreatureScript
{
public:
    npc_vp_whipping_wind() : CreatureScript("npc_vp_whipping_wind") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_whipping_windAI(creature);
    }

    struct npc_vp_whipping_windAI : public ScriptedAI 
    {
        npc_vp_whipping_windAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, urand(1000,3000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_LIGHTNING_BOLT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_LIGHTNING_BOLT, true);
                    events.ScheduleEvent(EVENT_LIGHTNING_BOLT, urand(1000,3000));
                    break;
                default:
                    break;
                }
            }
        }
    };
};

enum TurbulentSquallSpells
{
    SPELL_ASPHYXIATE      = 88175,
    SPELL_CLOUDBURST      = 88170,
    SPELL_HURRICANE       = 88171,
};

enum TurbulentSquallEvents
{
    EVENT_ASPHYXIATE = 1,
    EVENT_CLOUDBURST,
    EVENT_HURRICANE,
};

class npc_vp_turbulent_squall : public CreatureScript
{
public:
    npc_vp_turbulent_squall() : CreatureScript("npc_vp_turbulent_squall") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_turbulent_squallAI(creature);
    }

    struct npc_vp_turbulent_squallAI : public ScriptedAI 
    {
        npc_vp_turbulent_squallAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_ASPHYXIATE, urand(3000,3000));
            events.ScheduleEvent(EVENT_CLOUDBURST, urand(15000,20000));
            events.ScheduleEvent(EVENT_HURRICANE, urand(7000,8000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ASPHYXIATE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_ASPHYXIATE, true);
                    events.ScheduleEvent(EVENT_ASPHYXIATE, urand(22000,23000));
                    break;
                case EVENT_CLOUDBURST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_CLOUDBURST, true);
                    events.ScheduleEvent(EVENT_CLOUDBURST, urand(35000,40000));
                    break;
                case EVENT_HURRICANE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_HURRICANE, true);
                    events.ScheduleEvent(EVENT_HURRICANE, urand(12000,13000));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_vp_young_storm_dragon : public CreatureScript
{
public:
    npc_vp_young_storm_dragon() : CreatureScript("npc_vp_young_storm_dragon") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_young_storm_dragonAI(creature);
    }

    struct npc_vp_young_storm_dragonAI : public ScriptedAI 
    {
        npc_vp_young_storm_dragonAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            DoCast(me, SPELL_BRUTAL_STRIKES, true);
            isOnGround = true;
        }

        enum spellId
        {
            SPELL_BRUTAL_STRIKES    = 88192,
            SPELL_CHILLING_BLAST    = 88194,
            SPELL_HEALING_WELL      = 88201
        };

        enum eventId
        {
            EVENT_CHILLING_BLAST        = 1,
            EVENT_TAKEOFF_AFTER_CAST
        };

        enum pointId
        {
            POINT_TAKEOFF   = 1,
            POINT_LAND
        };

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);

            events.Reset();

            if (isOnGround == false)
            {
                isOnGround = true;
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
                me->SetDisableGravity(false);
                me->SetHover(false);
            }
        }

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetDisableGravity(false);
            me->SetHover(false);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
            events.Reset();
            isOnGround = true;
            _EnterEvadeMode();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->SetDisableGravity(false);
            me->SetHover(false);
        }

        void EnterCombat(Unit* /*target*/)
        {
            DoCast(SPELL_HEALING_WELL);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
            events.ScheduleEvent(EVENT_TAKEOFF_AFTER_CAST, 2100);
            events.ScheduleEvent(EVENT_CHILLING_BLAST, urand(4000,8000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHILLING_BLAST:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                            DoCast(target, SPELL_CHILLING_BLAST, true);
                        events.ScheduleEvent(EVENT_CHILLING_BLAST, urand(20000, 24000));
                        break;
                    }
                    case EVENT_TAKEOFF_AFTER_CAST:
                    {
                        me->SetHover(true);
                        me->SetDisableGravity(true);
                        Position pos;
                        pos.Relocate(me);
                        pos.m_positionZ += 2.0f;
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveTakeoff(POINT_TAKEOFF, pos);
                        isOnGround = false;
                        events.CancelEvent(EVENT_TAKEOFF_AFTER_CAST);
                        break;
                    }
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_TAKEOFF:
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
                    break;
                }
                default:
                    break;
            }
        }

        protected:
            Position pos;
            bool isOnGround;
    };
};

enum EmpyreanAssassinSpells
{
    SPELL_LETHARGIC_POISON    = 88182,
    SPELL_VAPOR_FORM          = 88186,
};

enum EmpyreanAssassinEvents
{
    EVENT_LETHARGIC_POISON = 1,
    EVENT_VAPOR_FORM,
};

class npc_vp_empyrean_assassin : public CreatureScript
{
public:
    npc_vp_empyrean_assassin() : CreatureScript("npc_vp_empyrean_assassin") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_empyrean_assassinAI(creature);
    }

    struct npc_vp_empyrean_assassinAI : public ScriptedAI 
    {
        npc_vp_empyrean_assassinAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_LETHARGIC_POISON, urand(5000,6000));
            events.ScheduleEvent(EVENT_VAPOR_FORM, urand(4000,8000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_LETHARGIC_POISON:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_LETHARGIC_POISON, true);
                    events.ScheduleEvent(EVENT_LETHARGIC_POISON, urand(6000,7000));
                    break;
                case EVENT_VAPOR_FORM:
                    DoCast(me, SPELL_VAPOR_FORM, true);
                    events.ScheduleEvent(EVENT_VAPOR_FORM, urand(8000,10000));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

enum ServantofAsaadSpell
{
    SPELL_CRUSADER_STRIKE       = 87771,
    SPELL_DIVINE_STORM          = 58127,
    SPELL_HAND_OF_PROTECTION    = 87772,
};

enum ServantofAsaadEvents
{
    EVENT_CRUSADER_STRIKE = 1,
    EVENT_DIVINE_STORM,
    EVENT_HAND_OF_PROTECTION,
};

class npc_vp_servent_of_asaad : public CreatureScript
{
public:
    npc_vp_servent_of_asaad() : CreatureScript("npc_vp_servent_of_asaad") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_servent_of_asaadAI(creature);
    }

    struct npc_vp_servent_of_asaadAI : public ScriptedAI 
    {
        npc_vp_servent_of_asaadAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_CRUSADER_STRIKE, urand(2000,2000));
            events.ScheduleEvent(EVENT_DIVINE_STORM, urand(5000,5000));
            events.ScheduleEvent(EVENT_HAND_OF_PROTECTION, urand(7000,9000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CRUSADER_STRIKE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_CRUSADER_STRIKE, true);
                    events.ScheduleEvent(EVENT_CRUSADER_STRIKE, urand(3000,5000));
                    break;
                case EVENT_DIVINE_STORM:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_DIVINE_STORM, true);
                    events.ScheduleEvent(EVENT_DIVINE_STORM, urand(9000,12000));
                    break;
                case EVENT_HAND_OF_PROTECTION:
                    if(me->HealthBelowPct(40))
                        DoCast(me, SPELL_HAND_OF_PROTECTION, true);
                    events.ScheduleEvent(EVENT_HAND_OF_PROTECTION, urand(12000,17000));
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

enum MinisterOfAirSpell
{
    SPELL_LIGHTNING_LASH    = 87762,
    SPELL_LIGHTNING_NOVA    = 87768,
};

enum MinisterOfAirEvents
{
    EVENT_LIGHTNING_LASH = 1,
    EVENT_LIGHTNING_NOVA,
};

class npc_vp_minister_air : public CreatureScript
{
public:
    npc_vp_minister_air() : CreatureScript("npc_vp_minister_air") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_minister_airAI(creature);
    }

    struct npc_vp_minister_airAI : public ScriptedAI 
    {
        npc_vp_minister_airAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_LIGHTNING_LASH, urand(11000,14000));
            events.ScheduleEvent(EVENT_LIGHTNING_NOVA, urand(1000,2000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_LIGHTNING_LASH:
                    DoCastAOE(SPELL_LIGHTNING_LASH);
                    events.ScheduleEvent(EVENT_LIGHTNING_LASH, urand(14000,17000));
                case EVENT_LIGHTNING_NOVA:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(target, SPELL_LIGHTNING_NOVA);
                    events.ScheduleEvent(EVENT_LIGHTNING_NOVA, (1000,2000));
                    break;
                default:
                    break;
                }
            }
        }
    };
};

enum TempleAdeptSpell
{
    SPELL_DESPERATE_SPEED   = 87780,
    SPELL_GREATER_HEAL      = 87779,
    SPELL_HOLY_SMITE        = 88959,
};

enum TempleAdeptEvent
{
    EVENT_DESPERATE_SPEED = 1,
    EVENT_GREATER_HEAL,
    EVENT_HOLY_SMITE,
};

class npc_vp_temple_adept : public CreatureScript
{
public:
    npc_vp_temple_adept() : CreatureScript("npc_vp_temple_adept") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_temple_adeptAI(creature);
    }

    struct npc_vp_temple_adeptAI : public ScriptedAI 
    {
        npc_vp_temple_adeptAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_DESPERATE_SPEED, urand(1000,5000));
            events.ScheduleEvent(EVENT_GREATER_HEAL, urand(4000,7000));
            events.ScheduleEvent(EVENT_HOLY_SMITE, urand(1000,4000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DESPERATE_SPEED:
                    DoCast(me, SPELL_DESPERATE_SPEED, true);
                    events.ScheduleEvent(EVENT_DESPERATE_SPEED, urand(15000,18000));
                    break;
                case EVENT_GREATER_HEAL:
                    if (Unit* target = DoSelectLowestHpFriendly(40.0f))
                        if (target->HealthBelowPct(25))
                            DoCast(target, SPELL_GREATER_HEAL, true);
                        else if (me->HealthBelowPct(25))
                            DoCast(me, SPELL_GREATER_HEAL, true);
                        else
                            events.ScheduleEvent(EVENT_GREATER_HEAL, urand(7000,10000));
                    break;
                case EVENT_HOLY_SMITE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_HOLY_SMITE, true);
                    events.ScheduleEvent(EVENT_HOLY_SMITE, urand(5000,8000));
                    break;
                default:
                    break;
                }
            }
        }
    };
};

enum SkyfallStarSpells
{
    SPELL_ARCANE_BARRAGE      = 87854,
};

enum SkyfallStarEvents
{
    EVENT_ARCANE_BARRAGE = 1,
    EVENT_MOVE,
};

class npc_vp_skyfall_star : public CreatureScript
{
public:
    npc_vp_skyfall_star() : CreatureScript("npc_vp_skyfall_star") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_skyfall_starAI(creature);
    }

    struct npc_vp_skyfall_starAI : public ScriptedAI 
    {
        npc_vp_skyfall_starAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            count = 0;
        }

        InstanceScript* instance;
        uint8 count;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void JustDied(Unit* killer)
        {
            ++ count;
            if(count>= 7)
                if (Creature* trigger = me->FindNearestCreature(45981,60.0f, true))
                    trigger->DespawnOrUnsummon(1000);

        }
        void EnterCombat(Unit* /*target*/)
        {
            events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(1000,1000));
            events.ScheduleEvent(EVENT_MOVE, urand(4000,4000));
            me->GetMotionMaster()->MoveRandom(40.0f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ARCANE_BARRAGE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_ARCANE_BARRAGE, true);
                    events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(1000,6000));
                    break;
                case EVENT_MOVE:
                    me->GetMotionMaster()->MoveRandom(40.0f);
                    events.ScheduleEvent(EVENT_MOVE, urand(4000,6000));
                    break;
                default:
                    break;
                }
            }
        }
    };
};

class npc_vp_howling_gale : public CreatureScript
{
public:
    npc_vp_howling_gale() : CreatureScript("npc_vp_howling_gale")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vp_howling_galeAI(creature);
    }

    struct npc_vp_howling_galeAI : public ScriptedAI
    {
        npc_vp_howling_galeAI(Creature* creature) : ScriptedAI(creature)
        {
            alreadyCharged = false;
        }

        enum eventId
        {
            EVENT_ADD_VISUAL        = 1,
            EVENT_CAST_KNOCKBACK,
            EVENT_PAUSE_KNOCKBACK
        };

        enum spellId
        {
            SPELL_HOWLING_GALE_VISUAL_1     = 85136,
            SPELL_HOWLING_GALE_VISUAL_2     = 85137,
            SPELL_HOWLING_GALE_KNOCKBACK    = 85158
        };

        EventMap events;

        void Reset()
        {
            if (alreadyCharged == false)
            {
                me->SetReactState(REACT_PASSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                events.ScheduleEvent(EVENT_ADD_VISUAL, 250);
                alreadyCharged = true;
            }
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if (damage > 0)
            {
                events.ScheduleEvent(EVENT_PAUSE_KNOCKBACK, 10000);
                me->SetHealth(me->GetMaxHealth());
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ADD_VISUAL:
                    {
                        DoCast(SPELL_HOWLING_GALE_VISUAL_1);
                        DoCast(SPELL_HOWLING_GALE_VISUAL_2);
                        events.RescheduleEvent(EVENT_ADD_VISUAL, 250);
                        events.ScheduleEvent(EVENT_CAST_KNOCKBACK, 500);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
                        break;
                    }
                    case EVENT_PAUSE_KNOCKBACK:
                    {
                        events.CancelEvent(EVENT_ADD_VISUAL);
                        events.CancelEvent(EVENT_PAUSE_KNOCKBACK);
                        events.CancelEvent(EVENT_CAST_KNOCKBACK);
                        events.ScheduleEvent(EVENT_ADD_VISUAL, 35000);
                        me->RemoveAurasDueToSpell(SPELL_HOWLING_GALE_VISUAL_1);
                        me->RemoveAurasDueToSpell(SPELL_HOWLING_GALE_VISUAL_2);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
                        _EnterEvadeMode();
                        break;
                    }
                    case EVENT_CAST_KNOCKBACK:
                    {
                        DoCast(SPELL_HOWLING_GALE_KNOCKBACK);
                        events.CancelEvent(EVENT_CAST_KNOCKBACK);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    protected:
        bool alreadyCharged;
    };
};

void AddSC_vortex_pinnacle()
{
    new npc_slipstream();
    new spell_slipstream();
    new spell_healing_well();
    new npc_vp_gust_soldier();
    new npc_vp_wild_vortex();
    new npc_vp_armored_mistral();
    new npc_vp_cloud_prince();
    new npc_vp_whipping_wind();
    new npc_vp_turbulent_squall();
    new npc_vp_young_storm_dragon();
    new npc_vp_empyrean_assassin();
    new npc_vp_servent_of_asaad();
    new npc_vp_minister_air();
    new npc_vp_temple_adept();
    new npc_vp_skyfall_star();
    new npc_vp_howling_gale();
}