
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
#include "firelands.h"

enum Spells
{
    SPELL_BALANCE_BAR               = 98226,
    SPELL_RIDE_VEHICLE              = 98843,

    SPELL_OBSIDIAN_ARMOR            = 98632,
    SPELL_CONCUSSIVE_STOMP          = 97282,
    SPELL_CONCUSSIVE_STOMP_TRIGGER  = 102306,
    SPELL_HEATED_VOLCANO            = 98493,

    SPELL_VOLCANIC_BIRTH            = 98010,
    SPELL_VOLCANO_BASE              = 98250,
    SPELL_MOLTEN_ARMOR              = 98255,
    SPELL_EXPLOSION                 = 97719,
    SPELL_MAGMA                     = 98472,
    SPELL_ERRUPTION                 = 98264,
    SPELL_LAVA_STRIKE_TRIGGERED     = 98491,
};

enum Texts
{
    SAY_AGGRO                   = 1,
    SAY_STOMP                   = 2,
    SAY_UNK                     = 3,
    SAY_ANNOUNCE_ARMOR_DAMAGE   = 4,
    SAY_ARMOR_DAMAGE            = 5,
    SAY_MINIONS                 = 6,
    SAY_SLAY                    = 7,
    SAY_ANNOUNCE_MAGMA_POND     = 8,
    SAY_ANNOUNCE_ARMOR_BROKEN   = 9,
    SAY_FINAL_PHASE             = 10,
    SAY_DEATH                   = 11,
};

enum Events
{
    EVENT_BALANCE_MOVEMENT = 1,
    EVENT_CONCUSSIVE_STOMP,
    EVENT_EXPLOSION,
};

enum Actions
{
    ACTION_BALANCE_LEFT = 1,
    ACTION_BALANCE_RIGHT,
    ACTION_ACTIVATE_VOLCANO,
};

enum Phases
{
    PHASE_1     = 1,
    PHASE_2     = 2,
    PHASE_3     = 3,
};

enum ModelIds
{
    MODEL_DEFAULT       = 38414,
    MODEL_DAMAGED_1     = 38669,
    MODEL_DAMAGED_2     = 38676,
    MODEL_MOLTEN        = 38594,
};

class boss_lord_rhyolith : public CreatureScript
{
public:
    boss_lord_rhyolith() : CreatureScript("boss_lord_rhyolith") { }

    struct boss_lord_rhyolithAI : public BossAI
    {
        boss_lord_rhyolithAI(Creature* creature) : BossAI(creature, DATA_LORD_RHYOLITH)
        {
            balance = 0;
        }

        int32 balance;

        void Reset()
        {
            _Reset();
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_NOT_TARGETABLE | UNIT_FLAG2_UNK3 | UNIT_FLAG2_REGENERATE_POWER);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE | UNIT_FLAG_PET_IN_COMBAT | UNIT_FLAG_PLAYER_CONTROLLED);
            me->AddAura(SPELL_OBSIDIAN_ARMOR, me);
            me->SetAuraStack(SPELL_OBSIDIAN_ARMOR, me, 80);
            RemoveFeets();
            balance = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            DoCastAOE(SPELL_BALANCE_BAR);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
            me->AddUnitState(UNIT_STATE_CANNOT_TURN);
            me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+cos(me->GetOrientation())*100, me->GetPositionY()+sin(me->GetOrientation())*100, me->GetPositionZ(), false);

            events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP, 15500, 0, PHASE_1);
            events.ScheduleEvent(EVENT_BALANCE_MOVEMENT, 1000);
          
            if (Creature* footLeft = me->SummonCreature(NPC_LEFT_FOOT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            {
                footLeft->EnterVehicle(me, 0);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, footLeft);
            }

            if (Creature* footRight = me->SummonCreature(NPC_RIGHT_FOOT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
            {
                footRight->EnterVehicle(me, 1);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, footRight);
            }
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_LEFT_FOOT:
                case NPC_RIGHT_FOOT:
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    summon->AddAura(SPELL_OBSIDIAN_ARMOR, summon);
                    summon->SetAuraStack(SPELL_OBSIDIAN_ARMOR, summon, 80);
                    summon->SetDisplayId(summon->GetCreatureTemplate()->Modelid2);
                    summon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_UNK_6);
                    break;
                case NPC_VOLCANO:
                    summon->SetDisplayId(summon->GetCreatureTemplate()->Modelid2);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_CONCUSSIVE_STOMP_TRIGGER)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                    DoCast(target, SPELL_VOLCANIC_BIRTH);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                    DoCast(target, SPELL_VOLCANIC_BIRTH);
                switch (urand(1, 0))
                {
                    case 0:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        DoCast(target, SPELL_VOLCANIC_BIRTH);
                        break;
                    }
                    case 1:
                        break;
                    default:
                        break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BALANCE_BAR);
            RemoveFeets();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BALANCE_BAR);
            RemoveFeets();
            Reset();
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
        }

        void RemoveFeets()
        {
            std::list<Creature*> units;

            GetCreatureListWithEntryInGrid(units, me, NPC_LEFT_FOOT, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();

            GetCreatureListWithEntryInGrid(units, me, NPC_RIGHT_FOOT, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_BALANCE_LEFT:
                    if (balance < 25)
                        balance++;
                    break;
                case ACTION_BALANCE_RIGHT:
                    if (balance > -25)
                        balance--;
                    break;
                default:
                    break;
            }
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
                    case EVENT_CONCUSSIVE_STOMP:
                        Talk(SAY_STOMP);
                        DoCastAOE(SPELL_CONCUSSIVE_STOMP);
                        events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP, 30000);
                        break;
                    case EVENT_BALANCE_MOVEMENT: // Major Movement System controller
                    {
                        Map::PlayerList const& player = me->GetMap()->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = player.begin(); itr != player.end(); ++itr)
                            if (Player* player = itr->getSource())
                                player->SetPower(POWER_ALTERNATE_POWER, 25 + balance);

                        float angle = 0.0f;
                        angle = me->GetOrientation();

                        if (balance < 0)
                            angle += M_PI * balance * 0.005f;
                        else if (balance > 0)
                            angle -= M_PI * balance * -0.005f;

                        me->SetOrientation(angle);
                        me->SetFacingTo(angle);
                        me->AddUnitState(UNIT_STATE_CANNOT_TURN);
                        me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+cos(me->GetOrientation())*100, me->GetPositionY()+sin(me->GetOrientation())*100, me->GetPositionZ() + 0.5f, false);

                        if (balance < 0)
                            balance++;
                        else if (balance > 0)
                            balance--;

                        events.ScheduleEvent(EVENT_BALANCE_MOVEMENT, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }
            if (!(events.IsInPhase(PHASE_1 || PHASE_2)))
                DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_lord_rhyolithAI(creature);
    }
};

class npc_fl_foot : public CreatureScript
{
public:
    npc_fl_foot() : CreatureScript("npc_fl_foot") { }

    struct npc_fl_footAI : public ScriptedAI
    {
        npc_fl_footAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            uint32 lostStacks = (80 - me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount()) / 15;
            switch (me->GetEntry())
            {
                case NPC_RIGHT_FOOT:
                {
                    if (Creature* rhyolith = me->FindNearestCreature(BOSS_LORD_RHYOLITH, 200.0f, true))
                    {
                        if (damage > uint32((10000 * me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount() / 100) * lostStacks))
                            rhyolith->AI()->DoAction(ACTION_BALANCE_RIGHT);
                    }
                    break;
                }
                case NPC_LEFT_FOOT:
                {
                    if (Creature* rhyolith = me->FindNearestCreature(BOSS_LORD_RHYOLITH, 200.0f, true))
                    {
                        if (damage > uint32((10000 * me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount() / 100) * lostStacks))
                            rhyolith->AI()->DoAction(ACTION_BALANCE_LEFT);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_footAI(creature);
    }
};

class npc_fl_volcano : public CreatureScript
{
public:
    npc_fl_volcano() : CreatureScript("npc_fl_volcano") { }

    struct npc_fl_volcanoAI : public ScriptedAI
    {
        npc_fl_volcanoAI(Creature* creature) : ScriptedAI(creature)
        {
            exploded = false;
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->SetReactState(REACT_PASSIVE);
        };

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EXPLOSION:
                        DoCastAOE(SPELL_EXPLOSION);
                        DoCastAOE(SPELL_MAGMA);
                        break;
                    default:
                        break;
                }
            }
        }

        bool exploded;
        EventMap events;
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fl_volcanoAI(creature);
    }
};

void AddSC_boss_lord_rhyolith()
{
    new boss_lord_rhyolith();
    new npc_fl_foot();
    new npc_fl_volcano();
}