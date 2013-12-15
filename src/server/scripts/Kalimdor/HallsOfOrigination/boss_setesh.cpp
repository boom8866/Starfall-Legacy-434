#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "MapManager.h"
#include "halls_of_origination.h"

enum Spells
{
    //Setesh
    SPELL_CHAOS_BOLT                        = 77069,
    SPELL_SUMMON_REIGN_OF_CHAOS             = 77023,
    SPELL_REIGN_OF_CHAOS                    = 77026, // visual + damage trigger
    SPELL_REIGN_OF_CHAOS_DAMAGE             = 77030, // 89872 hc --> dummy effect need condition to setesh  ( effect #1 )
    SPELL_CHAOS_BLAST                       = 76674, // summon spell
    SPELL_CHAOS_BLAST_VISUAL                = 76676, // spliting visual need to condition to entry 41041
    SPELL_CHAOS_BLAST_AURA                  = 76681,
    
    SPELL_SEED_OF_CHAOS                     = 76870,
    SPELL_SUMMON_CHAOS_SEED                 = 76888, // summons entry 41126
    SPELL_SEED_OF_CHAOS_DAMAGE              = 76874,
    SPELL_CHAOS_SEED_CRYSTAL_VISUAL         = 76865, // this could trigger the damage ?
    SPELL_PORTAL_CHANNEL                    = 76784, // need condition to trigger (entry 41055)
    SPELL_NIGHTMARE_PORTAL                  = 76714, // on heroic the portal stays until encounter end, on nhc the portal can be killed
    SPELL_NIGHTMARE_PORTAL_SUMMON_VISUAL    = 77607, // casted on summon

    SPEL_CHAOS_BURN                         = 77128, // casted by chaos blast trigger (entry 41041);
    SPELL_CHAOS_BURN                        = 76684, // area damage. need more research about the spell (fuu fail hordeguides and my brain for forgeting such things)

    //Sentinel
    SPELL_VOID_BARRIER                      = 63710,
    SPELL_CHARGED_FISTS                     = 77238,

    //Seeker
    SPELL_ANTIMAGIC_PRISON                  = 76903,
};

enum Texts
{
    SAY_AGGRO       = 0,
    SAY_EVENT       = 1,
    SAY_SLAY        = 2,
    SAY_DEATH       = 3,
};

enum Events
{
    EVENT_CHAOS_BOLT            = 1,
    EVENT_REIGN_OF_CHAOS        = 2,
    EVENT_CHAOS_BLAST           = 3,
    EVENT_SUMMON_SEED_OF_CHAOS  = 4,
    EVENT_CHAOS_PORTAL          = 5,
    EVENT_SUMMON_PORTAL         = 6,
    EVENT_CHAOS_BLAST_AURA      = 7,
};

enum Points
{
    POINT_PORTAL = 1,
};

class boss_setesh : public CreatureScript
{
    public:
        boss_setesh() : CreatureScript("boss_setesh") { }

        struct boss_seteshAI : public BossAI
        {
            boss_seteshAI(Creature* creature) : BossAI(creature, DATA_SETESH)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;

            void Reset()
            {
                _Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);

                // events.ScheduleEvent(EVENT_CHAOS_BOLT, 6000);       // every 2 seconds
                // events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, 20000);
                // events.ScheduleEvent(EVENT_CHAOS_BLAST, 15000);
                // events.ScheduleEvent(EVENT_SUMMON_SEED_OF_CHAOS, 25000);
                // events.ScheduleEvent(EVENT_CHAOS_PORTAL, 8000);
            }

            void Cleanup()
            {
                me->DespawnCreaturesInArea(NPC_CHAOS_PORTAL, 125.0f);
                me->DespawnCreaturesInArea(NPC_REIGN_OF_CHAOS_STALKER, 125.0f);
                me->DespawnCreaturesInArea(NPC_VOID_SENTINEL, 125.0f);
                me->DespawnCreaturesInArea(NPC_VOID_SEEKER, 125.0f);
                me->DespawnCreaturesInArea(NPC_VOID_WURM, 125.0f);
                me->DespawnCreaturesInArea(NPC_SEED_OF_CHAOS, 125.0f);
                me->DespawnCreaturesInArea(NPC_CHAOS_BLAST, 125.0f);
            }

			void KilledUnit(Unit* killed)
			{
                if (killed->GetTypeId() == TYPEID_PLAYER)
				    Talk(SAY_SLAY);
			}

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case POINT_PORTAL:
                        events.ScheduleEvent(EVENT_SUMMON_PORTAL, 1);
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHAOS_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_CHAOS_BOLT);
                            events.ScheduleEvent(EVENT_CHAOS_BOLT, 2000);
                            break;
                        case EVENT_REIGN_OF_CHAOS:
                            DoCastAOE(SPELL_SUMMON_REIGN_OF_CHAOS);
                            events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, urand(30000, 40000));
                            Talk(SAY_EVENT);
                            break;
                        case EVENT_CHAOS_BLAST:
                            DoCastAOE(SPELL_CHAOS_BLAST);
                            DoCastAOE(SPELL_CHAOS_BLAST_VISUAL);
                            events.ScheduleEvent(EVENT_CHAOS_BLAST, 15000);
                            break;
                        case EVENT_SUMMON_SEED_OF_CHAOS:
                            DoCast(SPELL_SUMMON_CHAOS_SEED);
                            events.ScheduleEvent(EVENT_SUMMON_SEED_OF_CHAOS, 25000);
                            break;
                        case EVENT_CHAOS_PORTAL:
                            me->SetOrientation(urand(0.0f, 3.0f));
                            //me->SetOrientation(MapManager::NormalizeOrientation(me->GetOrientation()));
                            me->GetMotionMaster()->MovePoint(POINT_PORTAL, me->GetPositionX()+cos(me->GetOrientation())*20, me->GetPositionY()+sin(me->GetOrientation())*20, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_CHAOS_PORTAL, 30000);
                            events.RescheduleEvent(EVENT_CHAOS_BOLT, 7000);
                            break;
                        case EVENT_SUMMON_PORTAL:
                        {
                            float x = me->GetPositionX()+cos(me->GetOrientation())*7;
                            float y = me->GetPositionY()+sin(me->GetOrientation())*7;
                            Creature* trigger = me->SummonCreature(NPC_CHAOS_PORTAL, x, y, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                            me->SetFacingToObject(trigger);
                            DoCastAOE(SPELL_PORTAL_CHANNEL);
                            break;
                        }
                        default:
                            break;
                    }
                }
                // setesh isn't tankable so he doesnt attack, just cast his spells on random players / areas
            }

            void JustDied(Unit* /*who*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                Cleanup();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_seteshAI(creature);
        }
};

class mob_seed_of_chaos : public CreatureScript
{
public:
    mob_seed_of_chaos() : CreatureScript("mob_seed_of_chaos") { }

    struct mob_seed_of_chaosAI : public ScriptedAI
    {
        mob_seed_of_chaosAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            me->setFaction(16);
            DoCast(SPELL_SEED_OF_CHAOS);
            me->AddAura(SPELL_CHAOS_SEED_CRYSTAL_VISUAL, me);
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_seed_of_chaosAI(creature);
    }
};

class mob_reign_of_chaos : public CreatureScript
{
public:
    mob_reign_of_chaos() : CreatureScript("mob_reign_of_chaos") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_reign_of_chaosAI(creature);
    }

    struct mob_reign_of_chaosAI : public ScriptedAI
    {
        mob_reign_of_chaosAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            events.Reset();
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoCastAOE(SPELL_REIGN_OF_CHAOS);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->setFaction(16);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
        }

        void UpdateAI(uint32 diff)
        {
        }
    };
};

class mob_chaos_blast : public CreatureScript
{
public:
    mob_chaos_blast() : CreatureScript("mob_chaos_blast") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_chaos_blastAI(creature);
    }

    struct mob_chaos_blastAI : public ScriptedAI
    {
        mob_chaos_blastAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->setFaction(16);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            events.ScheduleEvent(EVENT_CHAOS_BLAST_AURA, 5000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHAOS_BLAST_AURA:
                        DoCastAOE(SPELL_CHAOS_BLAST_AURA);
                        break;
                }
            }
        }
    };
};

class mob_chaos_portal : public CreatureScript
{
public:
    mob_chaos_portal() : CreatureScript("mob_chaos_portal") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_chaos_portalAI(creature);
    }

    struct mob_chaos_portalAI : public ScriptedAI
    {
        mob_chaos_portalAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {
            SetCombatMovement(false);
            instance = creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        SummonList Summons;
        uint32 SummonTimer;

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_VOID_SEEKER:
                case NPC_VOID_SENTINEL:
                case NPC_VOID_WURM:
                    if (Player* target = summon->FindNearestPlayer(200.0f, true))
                        summon->Attack(target, false);
                    summon->SetCorpseDelay(2000);
                    break;
            }
        }

        void Reset()
        {
            SummonTimer = 3000;
            Summons.DespawnAll();
        }

        void Summon(uint8 summon)
        {
            if (summon == 0)
            {
                me->SummonCreature(NPC_VOID_SEEKER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                me->SummonCreature(NPC_VOID_WURM, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
            }
            else
                me->SummonCreature(NPC_VOID_SENTINEL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
        }

        void UpdateAI(uint32 diff)
        {
            if (SummonTimer <= diff)
            {
                uint8 summon = urand(0, 1);
                Summon(summon);
                SummonTimer = 15000;
            }
            else
                SummonTimer -= diff;
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->AddAura(SPELL_NIGHTMARE_PORTAL, me);
            DoCastAOE(SPELL_NIGHTMARE_PORTAL_SUMMON_VISUAL);
            me->SetReactState(REACT_PASSIVE);
            if (IsHeroic())
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
            else
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon();
        }
    };
};

class mob_void_sentinel : public CreatureScript
{
public:
    mob_void_sentinel() : CreatureScript("mob_void_sentinel") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_void_sentinelAI(creature);
    }

    struct mob_void_sentinelAI : public ScriptedAI
    {
        mob_void_sentinelAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        uint32 BarrierTimer;
        uint32 FistTimer;

        void Reset()
        {
            BarrierTimer = 10000;
            FistTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (BarrierTimer <= diff)
            {
                DoCast(SPELL_VOID_BARRIER);
                BarrierTimer = 25000;
            } else BarrierTimer -= diff;

            if (FistTimer <= diff)
            {
                DoCast(SPELL_CHARGED_FISTS);
                FistTimer = 25000;
            } else FistTimer -= diff;
        }

        void JustDied(Unit* /*killer*/)
        {
            // used to despawn corpse immediately
            me->DespawnOrUnsummon();
        }
    };
};

class mob_void_seeker : public CreatureScript
{
public:
    mob_void_seeker() : CreatureScript("mob_void_seeker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_void_seekerAI(creature);
    }

    struct mob_void_seekerAI : public ScriptedAI
    {
        mob_void_seekerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        uint32 PrisonTimer;

        void Reset()
        {
            PrisonTimer = 5000;
        }

         void UpdateAI(uint32 diff)
         {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

            if (PrisonTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                    DoCast(target, SPELL_ANTIMAGIC_PRISON);
                PrisonTimer = 25000;
            } else PrisonTimer -= diff;
        }

        void JustDied(Unit* /*killer*/)
        {
            // used to despawn corpse immediately
            me->DespawnOrUnsummon();
        }
    };
};

void AddSC_boss_setesh()
{
    new boss_setesh();
    new mob_chaos_blast();
    new mob_chaos_portal();
    new mob_seed_of_chaos();
    new mob_reign_of_chaos();
    new mob_void_sentinel();
    new mob_void_seeker();
}
