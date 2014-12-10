
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

enum SpeakerSpells
{
    SPELL_FLAME_RING_VISUAL     = 74632,
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
            if (!UpdateVictim())
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

void AddSC_halls_of_origination()
{
    new go_hoo_lift_console();
    new spell_hoo_transit_device();
    new npc_hoo_sun_touched_servant();
}
