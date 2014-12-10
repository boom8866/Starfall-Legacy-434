#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "MapManager.h"
#include "halls_of_origination.h"

enum Spells
{
    // Setesh
    SPELL_CHAOS_BOLT                    = 89873,
    SPELL_REIGN_OF_CHAOS                = 77023,
    SPELL_REIGN_OF_CHAOS_ROOT           = 77053,
    SPELL_REIGN_OF_CHAOS_SUMMON         = 77024,
    SPELL_REIGN_OF_CHAOS_DUMMY          = 77026,
    SPELL_REIGN_OF_CHAOS_DAMAGE         = 77030,
    SPELL_CHANNEL_CHAOS_PORTAL          = 76784,
    SPELL_NIGHTMARE_PORTAL              = 76714,
    SPELL_CHAOS_PORTAL_SUMMON_VISUAL    = 77607,

    SPELL_CHAOS_BLAST                   = 76674,
    SPELL_CHAOS_BLAST_VISUAL            = 76676,
    SPELL_CHAOS_BLAST_AURA              = 76681,

    SPELL_SUMMON_SEED_OF_CHAOS          = 76888,
    SPELL_SEED_OF_CHAOS_VISUAL          = 76865,
    SPELL_SEED_OF_CHAOS_EXPLOSION       = 76870,

    // Void Sentinel
    SPELL_SHADOW_BARRIER                = 76959,
};

enum Texts
{
    SAY_AGGRO           = 0,
    SAY_SLAY            = 1,
    SAY_DEATH           = 2,
};

enum Events
{
    // Setesh
    EVENT_CHAOS_BOLT = 1,
    EVENT_REIGN_OF_CHAOS,
    EVENT_MOVE_TO_PORTAL,
    EVENT_SUMMON_PORTAL,
    EVENT_CHAOS_BLAST,
    EVENT_SUMMON_SEED_OF_CHAOS,

    // Chaos Portal
    EVENT_ACTIVATE_PORTAL,
    EVENT_SUMMON_WURMS,
    EVENT_SUMMON_SENTINEL,
    EVENT_SUMMON_SEEKER,
    EVENT_SUMMON_RANDOM,

    // Seed of Chaos
    EVENT_EXPLODE,
};

enum Points
{
    POINT_PORTAL = 1,
};

Position const portalPositions[] =
{
    {-484.150f, -18.543f, 343.935f},
    {-520.294f,  14.002f, 343.936f},
    {-492.212f,  25.546f, 343.938f},
    {-480.199f,  8.201f,  343.928f},
};

class boss_setesh : public CreatureScript
{
    public:
        boss_setesh() : CreatureScript("boss_setesh") { }

        struct boss_seteshAI : public BossAI
        {
            boss_seteshAI(Creature* creature) : BossAI(creature, DATA_SETESH)
            {
                _firstPortal = false;
                _secondPortal = false;
                _thirdPortal = false;
                _fourthPortal = false;
                _fifthPortal = false;
            }

            Position portalPos;
            bool _firstPortal, _secondPortal, _thirdPortal, _fourthPortal, _fifthPortal;

            void Reset()
            {
                _Reset();
                SetCombatMovement(false);
                me->SetWalk(true);
                _firstPortal = false;
                _secondPortal = false;
                _thirdPortal = false;
                _fourthPortal = false;
                _fifthPortal = false;
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_CHAOS_BOLT, 1);
                events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, 31000);
                events.ScheduleEvent(EVENT_MOVE_TO_PORTAL, 14000); // First portal always in front of setesh
                events.ScheduleEvent(EVENT_SUMMON_SEED_OF_CHAOS, 23000);
                events.ScheduleEvent(EVENT_CHAOS_BLAST, 23500);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->GetMotionMaster()->MoveTargetedHome();
                SetCombatMovement(false);
                me->SetWalk(true);
                me->SetReactState(REACT_AGGRESSIVE);
                _firstPortal = false;
                _secondPortal = false;
                _thirdPortal = false;
                _fourthPortal = false;
                _fifthPortal = false;
                summons.DespawnAll();
                Cleanup();
            }

            void KilledUnit(Unit* killed)
            {
                if (killed->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                summons.DespawnAll();
                Cleanup();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
            }

            void Cleanup()
            {
                me->DespawnCreaturesInArea(NPC_VOID_SEEKER, 500.0f);
                me->DespawnCreaturesInArea(NPC_VOID_SENTINEL, 500.0f);
                me->DespawnCreaturesInArea(NPC_VOID_WURM, 500.0f);
                me->DespawnCreaturesInArea(NPC_CHAOS_SEED, 500.0f);
                me->DespawnCreaturesInArea(NPC_REIGN_OF_CHAOS_DUMMY, 500.0f);
                me->DespawnCreaturesInArea(NPC_CHAOS_BLAST, 500.0f);
            }

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case POINT_PORTAL:
                        events.ScheduleEvent(EVENT_SUMMON_PORTAL, 1000);
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || !CheckInRoom())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHAOS_BOLT:
                            if (!me->isMoving())
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15.0f, true))
                                    DoCast(target, SPELL_CHAOS_BOLT);
                            }
                            events.ScheduleEvent(EVENT_CHAOS_BOLT, 2000);
                            break;
                        case EVENT_REIGN_OF_CHAOS:
                            me->CastStop();
                            events.RescheduleEvent(EVENT_CHAOS_BOLT, 11000);
                            DoCastAOE(SPELL_REIGN_OF_CHAOS);
                            events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, 32000);
                            break;
                        case EVENT_MOVE_TO_PORTAL:
                            me->CastStop();
                            events.RescheduleEvent(EVENT_CHAOS_BOLT, 11000);
                            if (!_firstPortal)
                            {
                                events.ScheduleEvent(EVENT_SUMMON_PORTAL, 1);
                                _firstPortal = true;
                            }
                            else if (!_secondPortal)
                            {
                                me->GetMotionMaster()->MovePoint(POINT_PORTAL, portalPositions[0]);
                                _secondPortal = true;
                            }
                            else if (!_thirdPortal)
                            {
                                me->GetMotionMaster()->MovePoint(POINT_PORTAL, portalPositions[1]);
                                _thirdPortal = true;
                            }
                            else if (!_fourthPortal)
                            {
                                me->GetMotionMaster()->MovePoint(POINT_PORTAL, portalPositions[2]);
                                _fourthPortal = true;
                            }
                            else if (!_fifthPortal)
                            {
                                me->GetMotionMaster()->MovePoint(POINT_PORTAL, portalPositions[3]);
                                _secondPortal = false;
                                _thirdPortal = false;
                                _fourthPortal = false;
                                _fifthPortal = false;
                            }
                            events.ScheduleEvent(EVENT_MOVE_TO_PORTAL, 32000);
                            break;
                        case EVENT_SUMMON_PORTAL:
                            me->CastStop();
                            if (!_firstPortal)
                            {
                                _firstPortal = true;
                                me->SetFacingTo(1.550f);
                            }
                            if (IsHeroic())
                            {
                                if (Creature* portal = me->SummonCreature(NPC_CHAOS_PORTAL, me->GetPositionX()+cos(me->GetOrientation()) * 15.0f, me->GetPositionY()+sin(me->GetOrientation()) * 15.0f, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN))
                                    DoCastAOE(SPELL_CHANNEL_CHAOS_PORTAL);
                            }
                            else
                                if (Creature* portal = me->SummonCreature(NPC_CHAOS_PORTAL, me->GetPositionX()+cos(me->GetOrientation()) * 15.0f, me->GetPositionY()+sin(me->GetOrientation()) * 15.0f, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 28000))
                                    DoCastAOE(SPELL_CHANNEL_CHAOS_PORTAL);
                            break;
                        case EVENT_CHAOS_BLAST:
                            me->CastStop();
                            events.RescheduleEvent(EVENT_CHAOS_BOLT, 5000);
                            DoCastAOE(SPELL_CHAOS_BLAST);
                            events.ScheduleEvent(EVENT_CHAOS_BLAST, 32000);
                            break;
                        case EVENT_SUMMON_SEED_OF_CHAOS:
                            DoCastAOE(SPELL_SUMMON_SEED_OF_CHAOS);
                            events.ScheduleEvent(EVENT_SUMMON_SEED_OF_CHAOS, 32000);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_seteshAI(creature);
        }
};

class npc_hoo_reign_of_chaos : public CreatureScript
{
public:
    npc_hoo_reign_of_chaos() : CreatureScript("npc_hoo_reign_of_chaos") { }

    struct npc_hoo_reign_of_chaosAI : public ScriptedAI
    {
        npc_hoo_reign_of_chaosAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCast(SPELL_REIGN_OF_CHAOS_DUMMY);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_reign_of_chaosAI(creature);
    }
};

class npc_hoo_chaos_portal : public CreatureScript
{
public:
    npc_hoo_chaos_portal() : CreatureScript("npc_hoo_chaos_portal") { }

    struct npc_hoo_chaos_portalAI : public ScriptedAI
    {
        npc_hoo_chaos_portalAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_ACTIVATE_PORTAL, 1000);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(2000);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_VOID_SENTINEL:
                    summon->AddAura(SPELL_SHADOW_BARRIER, summon);
                    break;
                default:
                    break;
            }
            summon->SetInCombatWithZone();
        }
        
        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ACTIVATE_PORTAL:
                        if (IsHeroic())
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE |UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC);
                        DoCastAOE(SPELL_NIGHTMARE_PORTAL);
                        if (IsHeroic())
                        {
                            events.ScheduleEvent(EVENT_SUMMON_SENTINEL, 1);
                            events.ScheduleEvent(EVENT_SUMMON_WURMS, 6000);
                            events.ScheduleEvent(EVENT_SUMMON_SEEKER, 16000);
                            events.ScheduleEvent(EVENT_SUMMON_RANDOM, 31000);
                        }
                        else
                        {
                            events.ScheduleEvent(EVENT_SUMMON_WURMS, 1);
                            events.ScheduleEvent(EVENT_SUMMON_SEEKER, 12000);
                            events.ScheduleEvent(EVENT_SUMMON_SENTINEL, 27000);
                        }
                        break;
                    case EVENT_SUMMON_SENTINEL:
                        if (Creature* sentinel = me->SummonCreature(NPC_VOID_SENTINEL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                            DoCastAOE(SPELL_CHAOS_PORTAL_SUMMON_VISUAL);
                        break;
                    case EVENT_SUMMON_WURMS:
                        for (uint8 i = 0; i <=1; i++)
                            me->SummonCreature(NPC_VOID_WURM, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
                        break;
                    case EVENT_SUMMON_SEEKER:
                        me->SummonCreature(NPC_VOID_SEEKER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
                        break;
                    case EVENT_SUMMON_RANDOM:
                        switch (urand(0, 1))
                        {
                            case 0:
                                events.ScheduleEvent(EVENT_SUMMON_WURMS, 1);
                                break;
                            case 1:
                                events.ScheduleEvent(EVENT_SUMMON_SEEKER, 1);
                                break;
                        }
                        events.ScheduleEvent(EVENT_SUMMON_RANDOM, 15000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_chaos_portalAI(creature);
    }
};

class npc_hoo_chaos_blast : public CreatureScript
{
public:
    npc_hoo_chaos_blast() : CreatureScript("npc_hoo_chaos_blast") { }

    struct npc_hoo_chaos_blastAI : public ScriptedAI
    {
        npc_hoo_chaos_blastAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_CHAOS_BLAST_VISUAL)
                DoCastAOE(SPELL_CHAOS_BLAST_AURA);
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (Creature* setesh = me->FindNearestCreature(BOSS_SETESH, 500.0f, true))
                setesh->AI()->DoCastAOE(SPELL_CHAOS_BLAST_VISUAL);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_chaos_blastAI(creature);
    }
};

class npc_hoo_chaos_seed : public CreatureScript
{
public:
    npc_hoo_chaos_seed() : CreatureScript("npc_hoo_chaos_seed") { }

    struct npc_hoo_chaos_seedAI : public ScriptedAI
    {
        npc_hoo_chaos_seedAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCastAOE(SPELL_SEED_OF_CHAOS_VISUAL);
            me->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 13.0f, me->GetOrientation());
            me->GetMotionMaster()->MoveFall(1);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case 1:
                    events.ScheduleEvent(EVENT_EXPLODE, 1);
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
                    case EVENT_EXPLODE:
                        DoCastAOE(SPELL_SEED_OF_CHAOS_EXPLOSION);
                        me->RemoveAurasDueToSpell(SPELL_SEED_OF_CHAOS_VISUAL);
                        me->DespawnOrUnsummon(3000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hoo_chaos_seedAI(creature);
    }
};

class spell_hoo_chaos_blast : public SpellScriptLoader
{
public:
    spell_hoo_chaos_blast() : SpellScriptLoader("spell_hoo_chaos_blast") { }

    class spell_hoo_chaos_blast_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_chaos_blast_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if ((*itr)->GetDistance2d(GetCaster()) > 15.0f)
                {
                    targets.clear();
                    targets.push_back(*itr);
                    break;
                }
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_chaos_blast_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_chaos_blast_SpellScript();
    }
};

void AddSC_boss_setesh()
{
    new boss_setesh();
    new npc_hoo_reign_of_chaos();
    new npc_hoo_chaos_portal();
    new npc_hoo_chaos_blast();
    new npc_hoo_chaos_seed();
    new spell_hoo_chaos_blast();
}
