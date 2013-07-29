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

class npc_slipstream : public CreatureScript
{
public:
    npc_slipstream() : CreatureScript("npc_slipstream") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->CLOSE_GOSSIP_MENU();
        InstanceScript* instance = creature->GetInstanceScript();

        if(creature->GetDBTableGUIDLow() == 778156)
        {
            if (instance && instance->GetBossState(DATA_GRAND_VIZIER_ERTAN) == DONE)
            {
                Count = 0;
                creature->AddAura(85063, player);
                return true;
            }
            else
                return false;
        }

        if(creature->GetDBTableGUIDLow() == 778186)
        {
            if (instance && instance->GetBossState(DATA_ALTAIRUS) == DONE)
            {
                Count = 3;
                creature->AddAura(85063, player);
                return true;
            }
            else
                return false;
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
                        {
                            caster->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            target->EnterVehicle(caster, 0);
                        }
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

void AddSC_vortex_pinnacle()
{
    new npc_slipstream();
    new spell_slipstream();
}