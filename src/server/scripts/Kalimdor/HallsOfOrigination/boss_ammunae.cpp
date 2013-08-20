#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "halls_of_origination.h"

enum Spells
{
    //Ammunae
    SPELL_WITHER                           = 76043,
    SPELL_CONSUME_LIFE_DAMAGE_EFFECT       = 79767,
    SPELL_CONSUME_LIFE_ENERGIZE_EFFECT     = 75665,
    SPELL_CONSUME_LIFE_POWER_BURN_EFFECT   = 75666,
    SPELL_RAMPANT_GROWTH                   = 75790,   //Only with 100 energy

    //Seeding Pod
    SPELL_ENERGIZE                         = 75657,
    SPELL_ENERGIZING_GROWTH                = 89123,   //Only Hero

    //Bloodpetal
    SPELL_THORN_SLASH                      = 76044,

    //Spore
    SPELL_NOXIOUS_SPORE                    = 75702,
    SPELL_SPORE_CLOUD                      = 75701,
};

enum AmunaeTexts
{
    SAY_AGGRO                = 0,
    SAY_GROWTH               = 1,
    SAY_SLAY                 = 2,
    SAY_DEATH                = 3,
};

enum Events
{
    //Ammunae
    EVENT_WITHER = 1,
    EVENT_CONSUME_LIFE,
    EVENT_RAMPANT_GROWTH,
    EVENT_RAMPANT_GROWTH_SUMMON,
    EVENT_SUMMON_POD,
    EVENT_SUMMON_SPORE,
    EVENT_ENERGY_TICKER,
    EVENT_ENERGY_TICKER_STOP,
    EVENT_COMBAT,

    //Blossom
    EVENT_THORN_SLASH,
    EVENT_EMERGE,
    EVENT_ATTACK,

    //Seedling Pod
    EVENT_ENERGIZE,
};

class boss_ammunae : public CreatureScript
{
    public:
        boss_ammunae() : CreatureScript("boss_ammunae") { }

        struct boss_ammunaeAI : public BossAI
        {
            boss_ammunaeAI(Creature* creature) : BossAI(creature, DATA_AMMUNAE)
            {
                energized = false;
            }

            bool energized;

            void Reset()
            {
                _Reset();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

                me->SetPower(POWER_ENERGY, 0);
                me->DespawnCreaturesInArea(NPC_SEEDING_POD, 125.0f);
                me->DespawnCreaturesInArea(NPC_BLOODPETAL_BLOSSOM, 125.0f);
                me->DespawnCreaturesInArea(NPC_SPORE, 125.0f);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_WITHER, 10000);
                events.ScheduleEvent(EVENT_CONSUME_LIFE, 4000);
                events.ScheduleEvent(EVENT_SUMMON_POD, 3000);
                events.ScheduleEvent(EVENT_RAMPANT_GROWTH, 15000);
                events.ScheduleEvent(EVENT_SUMMON_SPORE, 15000);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void RampartSummon(uint32 entry, float distance)
            {
                std::list<Creature*> CreatureList;
                Trinity::AllCreaturesOfEntryInRange checker(me, entry, distance);
                Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, CreatureList, checker);
                me->VisitNearbyObject(distance, searcher);
                if (CreatureList.empty())
                    return;

                std::list<Creature*>::iterator itr = CreatureList.begin();
                uint32 count = CreatureList.size();
                for (std::list<Creature*>::iterator iter = CreatureList.begin(); iter != CreatureList.end(); ++iter)
                {
                    (*iter)->SummonCreature(NPC_BLOODPETAL_BLOSSOM, (*iter)->GetPositionX(), (*iter)->GetPositionY(), (*iter)->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                    (*iter)->DespawnOrUnsummon(0);
                }
            }

            void DoRampartGrowth()
            {
                Talk(SAY_GROWTH);
                DoCastAOE(SPELL_RAMPANT_GROWTH);
                events.ScheduleEvent(EVENT_RAMPANT_GROWTH_SUMMON, 1500); // Temphack until i found out what's up with this custom spell
            }

            void UpdateAI(uint32 diff)
            {
				events.Update(diff);

                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_WITHER:
                            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_WITHER);
                                events.ScheduleEvent(EVENT_WITHER, 18000);
                            break;
                        case EVENT_CONSUME_LIFE:
                            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                            DoCast(me->getVictim(), SPELL_CONSUME_LIFE_ENERGIZE_EFFECT);
                            DoCast(me->getVictim(), SPELL_CONSUME_LIFE_DAMAGE_EFFECT);
                            events.ScheduleEvent(EVENT_CONSUME_LIFE, 15000);
                            break;
                        case EVENT_RAMPANT_GROWTH:
                            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                            if (me->GetPower(POWER_ENERGY) == me->GetMaxPower(POWER_ENERGY))
                                DoRampartGrowth();
                            events.ScheduleEvent(EVENT_RAMPANT_GROWTH, 10000);
                            break;
                        case EVENT_RAMPANT_GROWTH_SUMMON:
                            RampartSummon(NPC_SEEDING_POD, 200.0f);
                            break;
                        case EVENT_SUMMON_POD:
                            me->SummonCreature(NPC_SEEDING_POD, me->GetPositionX()+rand()%20, me->GetPositionY()+rand()%20, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_SUMMON_POD, 13000);
                            break;
                        case EVENT_SUMMON_SPORE:
                            me->SummonCreature(NPC_SPORE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                            events.ScheduleEvent(EVENT_SUMMON_SPORE, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void JustDied(Unit* /*who*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

                me->DespawnCreaturesInArea(NPC_SEEDING_POD, 125.0f);
                me->DespawnCreaturesInArea(NPC_BLOODPETAL_BLOSSOM, 125.0f);
                me->DespawnCreaturesInArea(NPC_SPORE, 125.0f);
            }

            void EnterEvadeMode()
            {
                _EnterEvadeMode();
                events.Reset();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->DespawnCreaturesInArea(NPC_SEEDING_POD, 125.0f);
                me->DespawnCreaturesInArea(NPC_BLOODPETAL_BLOSSOM, 125.0f);
                me->DespawnCreaturesInArea(NPC_SPORE, 125.0f);
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetPower(POWER_ENERGY, 0);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ammunaeAI(creature);
        }
};

class mob_bloodpetal_blossom : public CreatureScript
{
public:
    mob_bloodpetal_blossom() : CreatureScript("mob_bloodpetal_blossom") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_bloodpetal_blossomAI(creature);
    }

    struct mob_bloodpetal_blossomAI : public ScriptedAI
    {
        mob_bloodpetal_blossomAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* creator)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->AddAura(75768, me);
            me->HandleEmoteCommand(EMOTE_STATE_SUBMERGED);
            events.ScheduleEvent(EVENT_EMERGE, urand(3500, 4500));
        }

        void EnterCombat(Unit*)
        {
            //me->AddAura(75768, me);
            events.Reset();
            events.ScheduleEvent(EVENT_THORN_SLASH, 5000);
        }

        void Reset()
        {
            events.Reset();
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EMERGE:
                        me->HandleEmoteCommand(0);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                        events.ScheduleEvent(EVENT_ATTACK, 3000);
                    case EVENT_ATTACK:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoZoneInCombat();
                        events.ScheduleEvent(EVENT_THORN_SLASH, 5000);
                        break;
                    case EVENT_THORN_SLASH:
                        DoCast(me->getVictim(), SPELL_THORN_SLASH);
                        events.ScheduleEvent(EVENT_THORN_SLASH, 7500);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

class mob_seed_pod : public CreatureScript
{
public:
    mob_seed_pod() : CreatureScript("mob_seed_pod") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_seed_podAI(creature);
    }

    struct mob_seed_podAI : public ScriptedAI
    {
        mob_seed_podAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            instance = (InstanceScript*)creature->GetInstanceScript();
            summoned = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool summoned;

        void IsSummonedBy(Unit* creator)
        {
            if (!summoned)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                events.ScheduleEvent(EVENT_ENERGIZE, 3000);
                me->SetReactState(REACT_PASSIVE);
                me->SetMaxHealth(23247);
                me->SetHealth(me->GetMaxHealth());
                DoCastAOE(75687);
                summoned = true;
            }
        }

        void Energize()
        {
            if (Unit* target = me->FindNearestCreature(BOSS_AMMUNAE, 100))
                if (IsHeroic())
                    DoCast(target, SPELL_ENERGIZE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENERGIZE:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        if (Unit* target = me->FindNearestCreature(BOSS_AMMUNAE, 100))
                            DoCast(target, SPELL_ENERGIZE);
                        me->AddAura(96278, me);
                        events.ScheduleEvent(EVENT_ENERGIZE, 3000);
                        if (IsHeroic())
                            me->AddAura(SPELL_ENERGIZING_GROWTH, me);
                            break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon();
        }
    };
};

class mob_spore : public CreatureScript
{
public:
    mob_spore() : CreatureScript("mob_spore") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_sporeAI(creature);
    }

    struct mob_sporeAI : public ScriptedAI
    {
        mob_sporeAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            summoned = false;
        }

        InstanceScript* instance;
        bool summoned;

        void IsSummonedBy(Unit* creator)
        {
            if (Player* victim = me->FindNearestPlayer(50.0f))
                me->Attack(victim, false);
            me->setFaction(16);
            summoned = true;
            me->SetWalk(true);
        }

        void UpdateAI(uint32 diff)
        {
            DoCast(SPELL_SPORE_CLOUD);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->SetHealth(100);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED | UNIT_FLAG_IMMUNE_TO_PC);
            DoCastAOE(SPELL_SPORE_CLOUD);
            me->DespawnOrUnsummon(5000);
        }
    };
};

void AddSC_boss_ammunae()
{
    new boss_ammunae;
    new mob_bloodpetal_blossom;
    new mob_seed_pod;
    new mob_spore;
}
