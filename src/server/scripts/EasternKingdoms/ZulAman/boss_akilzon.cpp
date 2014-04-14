
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "zulaman.h"
#include "Weather.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_STORM   = 2,
    SAY_EAGLE   = 3,
    SAY_DEATH   = 4,
};

enum Spells
{
    // Akilzon
    SPELL_STATIC_DISRUPTION             = 43622,
    SPELL_GUST_OF_WIND                  = 97319,
    SPELL_CALL_LIGHTNING                = 97299,
    SPELL_DISMISS_RUNE_WEAPON           = 50707,

    SPELL_ELECTRICAL_OVERLOAD_PRIMER    = 44735,

    SPELL_GRIPPED                       = 97318,
    SPELL_ELECTRICAL_STORM              = 43648,
    SPELL_ELECTRICAL_STORM_AREA_AURA    = 44007, // Casted before teleport up
    SPELL_TELEPORT_SELF                 = 44006, // + 10.0f

    // Amani Kidnapper
    SPELL_GRAB_PASSENGER                = 98869,
    SPELL_GRABBED                       = 97318,

    // Soaring Eagle
    SPELL_EAGLE_SWOOP                   = 97301,
};

enum Sounds
{
    SOUND_CRY   = 12196,
};
 // 8 Eagles
enum Events
{
    // Akilzon
    EVENT_STATIC_DISRUPTION = 1,
    EVENT_CALL_LIGHTNING,
    EVENT_GUST_OF_WIND,
    EVENT_SUMMON_SOARING_EAGLE,
    EVENT_ATTACK,

    EVENT_OVERLOAD_PRIMER,
    EVENT_ELECTRICAL_STORM,

    // Amani Kidnapper
    EVENT_GRAB_PLAYER,
    EVENT_FLY_ARROUND,

    // Soaring Eagle
    EVENT_EAGLE_SWOOP,
    EVENT_MOVE_RANDOM,
    EVENT_MOVE_BACK,
    EVENT_AFTER_SPAWN,
};

// 91.7419

class boss_akilzon : public CreatureScript
{
public:
    boss_akilzon() : CreatureScript("boss_akilzon") { }

    struct boss_akilzonAI : public BossAI
    {
        boss_akilzonAI(Creature* creature) : BossAI(creature, DATA_AKILZON)
        {
        }

        Unit* stormTarget;

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_STATIC_DISRUPTION, 16000);
            events.ScheduleEvent(EVENT_CALL_LIGHTNING, 7000);
            //events.ScheduleEvent(EVENT_GUST_OF_WIND, 8000);
            //events.ScheduleEvent(EVENT_SUMMON_SOARING_EAGLE, 10000);
            events.ScheduleEvent(EVENT_OVERLOAD_PRIMER, 46000);
        }

        void JustKilled(Unit* target)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
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
                    case EVENT_STATIC_DISRUPTION:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_STATIC_DISRUPTION);
                        events.ScheduleEvent(EVENT_STATIC_DISRUPTION, 12000);
                        break;
                    case EVENT_CALL_LIGHTNING:
                        DoCastVictim(SPELL_CALL_LIGHTNING);
                        events.ScheduleEvent(EVENT_CALL_LIGHTNING, 15500);
                        break;
                    case EVENT_GUST_OF_WIND:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_GUST_OF_WIND);
                        events.ScheduleEvent(EVENT_GUST_OF_WIND, 24000);
                        break;
                    case EVENT_SUMMON_SOARING_EAGLE:
                        for (uint8 i = 0; i < 8; i++)
                        {
                            float posX = me->GetPositionX() + frand(-20.0f, 20.0f);
                            float posY = me->GetPositionY() + frand(-20.0f, 20.0f);
                            float posZ = 91.7419f;
                            me->SummonCreature(NPC_SOARING_EAGLE, posX, posY, posZ, frand(0.0f, M_PI), TEMPSUMMON_MANUAL_DESPAWN);
                        }
                        break;
                    case EVENT_OVERLOAD_PRIMER:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            stormTarget = target;
                            target->CastSpell(target, SPELL_ELECTRICAL_OVERLOAD_PRIMER);
                            events.ScheduleEvent(EVENT_ELECTRICAL_STORM, 500);
                        }
                        events.ScheduleEvent(EVENT_OVERLOAD_PRIMER, 60000);
                        break;
                    case EVENT_ELECTRICAL_STORM:
                        stormTarget->CastSpell(stormTarget, SPELL_ELECTRICAL_STORM_AREA_AURA);
                        stormTarget->CastSpell(stormTarget, SPELL_TELEPORT_SELF);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        DoCast(stormTarget, SPELL_ELECTRICAL_STORM);
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
        return new boss_akilzonAI(creature);
    }
};

class npc_amani_kidnapper : public CreatureScript
{
public:
    npc_amani_kidnapper() : CreatureScript("npc_amani_kidnapper") { }

    struct npc_amani_kidnapperAI : public ScriptedAI
    {
        npc_amani_kidnapperAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;
        Unit* owner;
        uint8 counter;

        void PassengerBoarded(Unit* /*passenger*/, int8 /*seatId*/, bool /*apply*/)
        {
            me->GetMotionMaster()->MovePoint(1, 357.483f, 1417.802f, 83.971f, false);
            me->ClearInCombat();
            counter = 1;
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    if (counter < 4)
                        counter++;
                    else
                        counter = 1;

                    events.ScheduleEvent(EVENT_FLY_ARROUND, 1);
                    break;
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* summoner)
        {
            owner = summoner;
            events.ScheduleEvent(EVENT_GRAB_PLAYER, 500);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->setFaction(1890);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(3000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GRAB_PLAYER:
                        DoCast(owner, SPELL_GRAB_PASSENGER);
                        break;
                    case EVENT_FLY_ARROUND:
                        if (counter == 1)
                            me->GetMotionMaster()->MovePoint(counter, 357.483f, 1417.802f, 89.971f, false);
                        if (counter == 2)
                            me->GetMotionMaster()->MovePoint(counter, 381.420f, 1426.213f, 85.971f, false);
                        if (counter == 3)
                            me->GetMotionMaster()->MovePoint(counter, 389.606f, 1397.059f, 89.971f, false);
                        if (counter == 4)
                            me->GetMotionMaster()->MovePoint(counter, 367.487f, 1389.132f, 85.971f, false);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_amani_kidnapperAI(creature);
    }
};

class npc_soaring_eagle : public CreatureScript
{
public:
    npc_soaring_eagle() : CreatureScript("npc_soaring_eagle") { }

    struct npc_soaring_eagleAI : public ScriptedAI
    {
        npc_soaring_eagleAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
            me->SetDisableGravity(true);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_EAGLE_SWOOP, urand(3000, 4000));
            events.ScheduleEvent(EVENT_AFTER_SPAWN, 200);
            me->SetSpeed(MOVE_RUN, 4.5f);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(3000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_RANDOM:
                        me->GetMotionMaster()->MoveRandom(8.0f);
                        events.ScheduleEvent(EVENT_MOVE_RANDOM, 1000);
                        break;
                    case EVENT_EAGLE_SWOOP:
                        events.CancelEvent(EVENT_MOVE_RANDOM);
                        me->GetMotionMaster()->Clear();
                        me->PlayDistanceSound(SOUND_CRY);
                        DoZoneInCombat();
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            DoCast(target, SPELL_EAGLE_SWOOP);
                            me->GetMotionMaster()->MoveChase(target, 0.0f, 0.0f);
                        }
                        events.ScheduleEvent(EVENT_MOVE_BACK, 1500);
                        break;
                    case EVENT_MOVE_BACK:
                        me->GetMotionMaster()->MoveTargetedHome();
                        events.ScheduleEvent(EVENT_MOVE_RANDOM, 3000);
                        events.ScheduleEvent(EVENT_EAGLE_SWOOP, urand(9000, 11000));
                        break;
                    case EVENT_AFTER_SPAWN:
                        me->GetMotionMaster()->MoveTargetedHome();
                        events.ScheduleEvent(EVENT_MOVE_RANDOM, 1000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_soaring_eagleAI(creature);
    }
};

class spell_grab_passenger : public SpellScriptLoader
{
public:
    spell_grab_passenger() : SpellScriptLoader("spell_grab_passenger") { }

    class spell_grab_passenger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_grab_passenger_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetCaster(), SPELL_GRABBED);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_grab_passenger_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_grab_passenger_SpellScript();
    }
};

class spell_electrical_storm : public SpellScriptLoader
{
public:
    spell_electrical_storm() : SpellScriptLoader("spell_electrical_storm") { }

    class spell_electrical_storm_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_electrical_storm_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetOwner()->ToUnit())
            {
                target->SetDisableGravity(true);
                target->AddAura(42716, target);
                target->NearTeleportTo(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ() + 10.0f, target->GetOrientation());
                target->ApplySpellImmune(0, IMMUNITY_ID, 97300, true);
            }

        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetOwner()->ToUnit())
            {
                target->SetDisableGravity(false);
                target->RemoveAurasDueToSpell(42716);
                target->ApplySpellImmune(0, IMMUNITY_ID, 97300, false);
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_electrical_storm_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_electrical_storm_AuraScript::OnApply, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_electrical_storm_AuraScript();
    }
};

void AddSC_boss_akilzon()
{
    new boss_akilzon();
    new npc_amani_kidnapper();
    new npc_soaring_eagle();
    new spell_grab_passenger();
    new spell_electrical_storm();
}
