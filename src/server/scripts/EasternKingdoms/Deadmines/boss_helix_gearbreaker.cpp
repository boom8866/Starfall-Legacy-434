#include "ScriptPCH.h"
#include "deadmines.h"
#include "Vehicle.h"

enum Spells
{
    // Helix
    SPELL_OAFQUARD                  = 90546,

    SPELL_HELIX_RIDE                = 88337,
    SPELL_EMOTE_CHEST_BOMB          = 91572, // Hits the enemy and trigger sthe bomb spells

    SPELL_THROW_BOMB                = 88264,

    // Lumbering Oaf
    SPELL_OAF_GRAB_TARGETING        = 88289,
    SPELL_RIDE_OAF                  = 88278,
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
    SPELL_OAF_CHARGE                = 88288,
    SPELL_OAF_SMASH                 = 88300,
    SPELL_OAF_SMASH_H               = 91568,

    // Sticky Bomb
    SPELL_STICKY_BOMB_EXPLODE       = 88974,
    SPELL_ARMING_VISUAL_YELLOW      = 88315,
    SPELL_ARMING_VISUAL_ORANGE      = 88316,
    SPELL_ARMING_VISUAL_RED         = 88317,
    SPELL_BOMB_ARMED_STATE          = 88319,
    SPELL_CHEST_BOMB                = 88352,
};

const Position OafPos[2] = 
{
    {-289.809f, -527.215f, 49.8021f, 0},
    {-289.587f, -489.575f, 49.9126f, 0},
};

const Position CrewSpawn[] =
{
    {-281.68f, -504.10f, 60.51f, 4.75f},
    {-284.71f, -504.13f, 60.42f, 4.72f},
    {-288.65f, -503.74f, 60.38f, 4.64f},
    {-293.88f, -503.90f, 60.07f, 4.77f},
};

enum HelOaf_Events
{
    // Helix Events
    EVENT_CHEST_BOMB    = 1,
    EVENT_THROW_BOMB    = 2,
    EVENT_NO_OAF        = 3,

    // Oaf Events
    EVENT_OAFQUARD      = 4,
    EVENT_MOVE_TO_POINT = 5,
    EVENT_MOUNT_PLAYER  = 6,
    EVEMT_CHARGE        = 7,
    EVENT_FINISH        = 8,
};

enum Texts
{
    // Helix
    SAY_AGGRO       = 0,
    SAY_THROW_BOMB  = 1,
    SAY_ATTACH_BOMB = 2,
    SAY_OAF_DEAD    = 3,

    // Helix Crew
    SAY_CREW        = 0,

    // Lumbering Oaf
    SAY_OAF_1       = 0,
    SAY_OAF_2       = 1,
};

enum Points
{
    POINT_CHARGE    = 0,
    POINT_CRASH     = 1,
};

class boss_helix_gearbreaker : public CreatureScript
{
public:
    boss_helix_gearbreaker() : CreatureScript("boss_helix_gearbreaker") { }

    struct boss_helix_gearbreakerAI : public BossAI
    {
        boss_helix_gearbreakerAI(Creature* creature) : BossAI(creature, DATA_HELIX), summons(me)
        {
        }

        SummonList summons;
        Creature* oaf;

        void Reset()
        {
            _Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            OafSupport();
            summons.DespawnAll();
            CleanUp();
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            me->SetInCombatWithZone();
            events.ScheduleEvent(EVENT_THROW_BOMB, 3000);
            
            if(IsHeroic())
                SummonCrew();
        }

        void OafSupport()
        {
            oaf = me->GetVehicleCreatureBase();
            if (!oaf)
            {
                oaf = me->FindNearestCreature(NPC_OAF, 30.0f);
                if (oaf && oaf->isAlive())
                {
                    me->CastSpell(oaf, SPELL_RIDE_VEHICLE_HARDCODED);
                }
                else
                {
                    oaf = me->SummonCreature(NPC_OAF, me->GetHomePosition());
                    me->DespawnOrUnsummon();
                }
            }
        }

        void SummonCrew()
        {
            for (uint8 i=0; i<4; ++i)
            {
                me->SummonCreature(NPC_HELIX_CREW, CrewSpawn[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            }
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            CleanUp();
        }

        void CleanUp()
        {
            std::list<Creature*> units;

            GetCreatureListWithEntryInGrid(units, me, NPC_HELIX_CREW, 100.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();
        }

        void JustReachedHome()
        {
            _JustReachedHome();
            instance->SetBossState(DATA_HELIX, FAIL);
        }

        void OafDead()
        {
            events.ScheduleEvent(EVENT_NO_OAF, 100);
            events.ScheduleEvent(EVENT_THROW_BOMB, 3000);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_CHEST_BOMB, 5000);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();

            events.Update(uiDiff);
                
            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_THROW_BOMB:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150, true))
                            me->CastSpell(target, SPELL_THROW_BOMB, TRIGGERED_IGNORE_CASTER_MOUNTED_OR_ON_VEHICLE);
                        events.ScheduleEvent(EVENT_THROW_BOMB, 3000);
                        break;
                    case EVENT_CHEST_BOMB:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150, true))
                        {
                            me->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE_HARDCODED);
                            Talk(SAY_ATTACH_BOMB, target->GetGUID());
                            me->AddAura(SPELL_HELIX_RIDE, target);
                            DoCast(target, SPELL_RIDE_VEHICLE_HARDCODED);
                            me->AddAura(SPELL_CHEST_BOMB, target);                             
                        }
                        events.ScheduleEvent(EVENT_CHEST_BOMB, 11000);
                        break;
                    case EVENT_NO_OAF:
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->RemoveAura(SPELL_OAFQUARD);
                        Talk(SAY_OAF_DEAD);
                        events.RescheduleEvent(EVENT_THROW_BOMB, 3000);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_helix_gearbreakerAI (creature);
    }
};

Position const ChargePos = {-289.598f, -489.288f, 49.815f, 4.693f};

class npc_lumbering_oaf : public CreatureScript
{
public:
    npc_lumbering_oaf() : CreatureScript("npc_lumbering_oaf") { }

    struct npc_lumbering_oafAI : public ScriptedAI
    {
        npc_lumbering_oafAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            _vehicle = me->GetVehicleKit();
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        SummonList summons;
        EventMap events;
        Vehicle* _vehicle;
        Creature* bunny;
        
        void Reset()
        {
            if (!me || !_vehicle)
                return;

            if (Unit* u = _vehicle->GetPassenger(1))
                u->ExitVehicle();

            events.Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            events.ScheduleEvent(EVENT_OAFQUARD, 5000);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_CHARGE:
                    events.ScheduleEvent(EVENT_CHARGE, 3000);
                    break;
                case POINT_CRASH:
                    events.ScheduleEvent(EVENT_FINISH, 1);
                    break;
                default:
                    break;
            }
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* Helix = me->FindNearestCreature(NPC_HELIX_GEARBREAKER, 200, true))
                if (boss_helix_gearbreaker::boss_helix_gearbreakerAI* AI = CAST_AI(boss_helix_gearbreaker::boss_helix_gearbreakerAI, Helix->AI()))
                    AI->OafDead();

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
            summoned->Attack(me->getVictim(), false);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_OAF_CHARGE)
                target->CastSpell(me, SPELL_RIDE_VEHICLE_HARDCODED);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (!me || !_vehicle)
                return;

            events.Update(uiDiff);
                
            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_OAFQUARD:
                        if (bunny = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY_JMF, ChargePos, TEMPSUMMON_TIMED_DESPAWN, 20000))
                        {
                            me->AddThreat(bunny, 200000.0f);
                            me->SetInCombatWith(bunny);
                            bunny->setFaction(18);
                        }
                        me->SetReactState(REACT_PASSIVE);
                        events.ScheduleEvent(EVENT_MOUNT_PLAYER, 500);
                        break;
                    case EVENT_MOUNT_PLAYER:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                            DoCast(target, SPELL_OAF_CHARGE);
                        events.ScheduleEvent(EVENT_MOVE_TO_POINT, 2000);
                        break;
                    case EVENT_MOVE_TO_POINT:
                        me->SetSpeed(MOVE_RUN, 5.0f); 
                        me->GetMotionMaster()->MovePoint(POINT_CHARGE, -289.809f, -527.215f, 49.8021f);
                        Talk(SAY_OAF_1);
                        break;
                    case EVENT_CHARGE:
                        me->GetMotionMaster()->Clear(true);
                        me->GetMotionMaster()->MovePoint(POINT_CRASH, ChargePos);
                        Talk(SAY_OAF_2);
                        break;
                    case EVENT_FINISH:
                        {
                            if (Unit * passenger = me->GetVehicleKit()->GetPassenger(1))
                            {
                                passenger->ExitVehicle();
                                me->Attack(passenger, false);
                            }

                            me->SetInCombatWithZone();
                            DoCastAOE(SPELL_OAF_SMASH);
                            me->SetSpeed(MOVE_RUN, 1.0f);
                            me->SetReactState(REACT_AGGRESSIVE);
                            events.ScheduleEvent(EVENT_OAFQUARD, 17000);
                        }
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lumbering_oafAI(creature);
    }
};

class npc_sticky_bomb : public CreatureScript
{
public:
    npc_sticky_bomb() : CreatureScript("npc_sticky_bomb") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sticky_bombAI (creature);
    }

    struct npc_sticky_bombAI : public ScriptedAI
    {
        npc_sticky_bombAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            instance = pCreature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 Phase;
        uint32 uiTimer;

        void Reset()
        {
            Phase   = 1;
            uiTimer = 500;
            if (!me)
                return;

            DoCast(me, SPELL_CHEST_BOMB);
        }

        void IsSummonedBy(Unit* /*summon*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->setFaction(16);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (uiTimer < uiDiff)
            {
                switch (Phase)
                {
                    case 1:
                        DoCast(me, SPELL_ARMING_VISUAL_YELLOW);
                        uiTimer = 700;
                        break;
                    case 2:
                        DoCast(me, SPELL_ARMING_VISUAL_ORANGE);
                        uiTimer = 600;
                        break;
                    case 3:
                        DoCast(me, SPELL_ARMING_VISUAL_RED);
                        uiTimer = 500;
                        break;
                    case 4:
                        DoCast(me, SPELL_BOMB_ARMED_STATE);
                        uiTimer = 400;
                        break;
                    case 5:
                        DoCast(me, SPELL_STICKY_BOMB_EXPLODE);
                        uiTimer = 300;
                        break;
                    case 6:
                        me->DespawnOrUnsummon(2000);
                        break;
                }

                Phase++;
            }
            else
                uiTimer -= uiDiff;
        }
    };
};

class npc_helix_crew : public CreatureScript
{
public:
    npc_helix_crew() : CreatureScript("npc_helix_crew") { }


    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_helix_crewAI (creature);
    }

    struct npc_helix_crewAI : public ScriptedAI
    {
        npc_helix_crewAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            SetCombatMovement(false);
        }

        uint32 ThrowBombTimer;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        void Reset()
        {
            ThrowBombTimer = 3000;
            DoCast(me, 18373);

            if (Player* victim = me->FindNearestPlayer(80.0f))
            {
                me->Attack(victim, false);    
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (ThrowBombTimer <= diff)
            {
                if (Unit* player = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                {
                    DoCast(player, SPELL_THROW_BOMB);
                    ThrowBombTimer = 5000;
                }
            }
            else ThrowBombTimer-= diff;
        }
    };
};

class spell_dm_chest_bomb : public SpellScriptLoader
{
    public:
        spell_dm_chest_bomb() :  SpellScriptLoader("spell_dm_chest_bomb") { }

        class spell_dm_chest_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dm_chest_bomb_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CHEST_BOMB))
                    return false;
                return true;
            }

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                GetTarget()->CastSpell(GetCaster(), 88250);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dm_chest_bomb_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dm_chest_bomb_AuraScript();
        }
};

void AddSC_boss_helix_gearbreaker()
{
    new npc_lumbering_oaf();
    new boss_helix_gearbreaker();
    new npc_sticky_bomb();
    new npc_helix_crew();
    new spell_dm_chest_bomb();
}
