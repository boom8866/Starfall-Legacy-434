#include "vortex_pinnacle.h"

enum Texts
{
    SAY_AGGRO           = 0,
    SAY_SLAY            = 1,
    SAY_DEATH           = 2,
    SAY_ANNOUNCE        = 3,
};

enum Spells
{
    SPELL_SUMMON_TEMPEST        = 86340,
    SPELL_LIGHTING_BOLT         = 86331,
    SPELL_STORMS_EDGE_AURA      = 86295,
    SPELL_STORMS_EDGE_PERIODIC  = 86284,
    SPELL_STORMS_EDGE           = 86309,
    SPELL_CYCLONE_SHIELD_VISUAL = 86267,
    SPELL_LURK                  = 85467,	
    SPELL_TEMPEST_LIGHTING_BOLT = 92776,
};

enum Events
{
    EVENT_LIGHTNING_BOLT    = 9,
    EVENT_SUMMON_TEMPEST    = 10,
    EVENT_SUMMON_STORM      = 11,
    EVENT_STOP              = 12,
    EVENT_PULL_ANNOUNCE     = 13,
    EVENT_STORMS_EDGE       = 14,

    //Tornado system
    EVENT_1     = 1,
    EVENT_2     = 2,
    EVENT_3     = 3,
    EVENT_4     = 4,
    EVENT_5     = 5,
    EVENT_6     = 6,
    EVENT_7     = 7,
    EVENT_8     = 8,
};

enum Actions
{
    ACTION_PULL     = 1,
    ACTION_MOVE_OUT = 2,
};

Position const Point8   = {-695.130f,   4.116f,     635.672f, 3.173f};
Position const Point7   = {-702.408f,   21.482f,    635.674f, 3.923f};
Position const Point6   = {-719.958f,   28.493f,    635.672f, 4.689f};
Position const Point5   = {-737.178f,   21.330f,    635.672f, 5.561f};
Position const Point4   = {-744.433f,   4.024f,     635.672f, 6.260f};
Position const Point3   = {-736.997f,   -13.297f,   635.672f, 0.715f};
Position const Point2   = {-719.625f,   -20.499f,   635.672f, 1.427f};
Position const Point1   = {-702.228f,   -13.440f,   635.672f, 2.338f};

enum Vortexpoints
{
    POINT_1     = 1,
    POINT_2     = 2,
    POINT_3     = 3,
    POINT_4     = 4,
    POINT_5     = 5,
    POINT_6     = 6,
    POINT_7     = 7,
    POINT_8     = 8,
};

class boss_grand_vizier_ertan : public CreatureScript
{
public:
    boss_grand_vizier_ertan() : CreatureScript("boss_grand_vizier_ertan") {}

    struct boss_grand_vizier_ertanAI : public BossAI
    {
        boss_grand_vizier_ertanAI(Creature* creature) : BossAI(creature, DATA_GRAND_VIZIER_ERTAN)
        {
            me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void Reset()
        {
            _Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 3000);
            events.ScheduleEvent(EVENT_SUMMON_STORM, 100);
            events.ScheduleEvent(EVENT_PULL_ANNOUNCE, 24000);
            if(IsHeroic())
                events.ScheduleEvent(EVENT_SUMMON_TEMPEST, 16500);
        }

        void KilledUnit(Unit* killed) 
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*Killer*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->DespawnCreaturesInArea(NPC_LURKING_TEMPEST, 120.0f);
            me->DespawnCreaturesInArea(NPC_CYCLONE_SHIELD, 120.0f);
        }

        void EnterEvadeMode()
        {
            _DespawnAtEvade();
            me->DespawnCreaturesInArea(NPC_LURKING_TEMPEST, 120.0f);
            me->DespawnCreaturesInArea(NPC_CYCLONE_SHIELD, 120.0f);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void PullShield()
        {
            std::list<Creature*> creatures;

            GetCreatureListWithEntryInGrid(creatures, me, NPC_CYCLONE_SHIELD, 150.0f);

            if (creatures.empty())
               return;
                
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->AI()->DoAction(ACTION_PULL);
        }

        void MoveOutShield()
        {
            std::list<Creature*> creatures;

            GetCreatureListWithEntryInGrid(creatures, me, NPC_CYCLONE_SHIELD, 150.0f);

            if (creatures.empty())
               return;
                
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->AI()->DoAction(ACTION_MOVE_OUT);
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
                    case EVENT_LIGHTNING_BOLT:
                        if (!me->HasAura(SPELL_STORMS_EDGE_AURA))
                            DoCastVictim(SPELL_LIGHTING_BOLT);
                        events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 2000);
                        break;
                    case EVENT_SUMMON_STORM:
                        {
                            Creature *t1 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point1, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t2 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point2, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t3 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point3, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t4 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point4, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t5 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point5, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t6 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point6, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t7 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point7, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t8 = me->SummonCreature(NPC_CYCLONE_SHIELD, Point8, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            t1->GetMotionMaster()->MovePoint(POINT_1, Point2);
                            t2->GetMotionMaster()->MovePoint(POINT_2, Point3);
                            t3->GetMotionMaster()->MovePoint(POINT_3, Point4);
                            t4->GetMotionMaster()->MovePoint(POINT_4, Point5);
                            t5->GetMotionMaster()->MovePoint(POINT_5, Point6);
                            t6->GetMotionMaster()->MovePoint(POINT_6, Point7);
                            t7->GetMotionMaster()->MovePoint(POINT_7, Point8);
                            t8->GetMotionMaster()->MovePoint(POINT_8, Point1);
                        }
                        break;
                    case EVENT_PULL_ANNOUNCE:
                        Talk(SAY_ANNOUNCE);
                        events.CancelEvent(EVENT_SUMMON_TEMPEST);
                        events.ScheduleEvent(EVENT_STORMS_EDGE, 6000);
                        events.ScheduleEvent(EVENT_PULL_ANNOUNCE, 31000);
                        PullShield();
                        break;
                    case EVENT_STORMS_EDGE:
                        if (!me->HasAura(SPELL_STORMS_EDGE_AURA))
                        {
                            me->AddAura(SPELL_STORMS_EDGE_AURA, me);
                            me->AddAura(SPELL_CYCLONE_SHIELD_VISUAL, me);
                            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 12000);
                            events.ScheduleEvent(EVENT_STORMS_EDGE, 7000);
                        }
                        else
                        {
                            me->RemoveAurasDueToSpell(SPELL_CYCLONE_SHIELD_VISUAL);
                            me->RemoveAurasDueToSpell(SPELL_STORMS_EDGE_AURA);
                            if (IsHeroic())
                                events.ScheduleEvent(EVENT_SUMMON_TEMPEST, 17000);

                            MoveOutShield();
                        }
                        break;
                    case EVENT_SUMMON_TEMPEST:
                        me->CastStop();
                        DoCastAOE(SPELL_SUMMON_TEMPEST);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new boss_grand_vizier_ertanAI (Creature);
    }
};

Position const Center = {-719.435f, 3.839f, 635.671f};

class npc_cyclone_shield : public CreatureScript
{
public:
    npc_cyclone_shield() : CreatureScript("npc_cyclone_shield"){}

    struct npc_cyclone_shieldAI  : public ScriptedAI
    {
        npc_cyclone_shieldAI (Creature* creature) : ScriptedAI(creature)
        {
            counter = 0;
        }

        EventMap events;
        uint8 counter;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            float posX = me->GetPositionX();
            float posY = me->GetPositionY();
            float posZ = me->GetPositionZ();
            Position const Home = {posX, posY, posZ};
            me->SetHomePosition(Home);
            me->SetWalk(true);
            me->setFaction(16);
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_STORMS_EDGE, 1000);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_PULL:
                    me->GetMotionMaster()->MovePoint(0, Center);
                    events.ScheduleEvent(EVENT_STOP, 6000);
                    events.CancelEvent(EVENT_STORMS_EDGE);
                    break;
                case ACTION_MOVE_OUT:
                    if (counter == 1)
                       events.ScheduleEvent(EVENT_2, 1);
                    else if (counter == 2)
                        events.ScheduleEvent(EVENT_3, 1);
                    else if (counter == 3)
                        events.ScheduleEvent(EVENT_4, 1);
                    else if (counter == 4)
                        events.ScheduleEvent(EVENT_5, 1);
                    else if (counter == 5)
                        events.ScheduleEvent(EVENT_6, 1);
                    else if (counter == 6)
                        events.ScheduleEvent(EVENT_7, 1);
                    else if (counter == 7)
                        events.ScheduleEvent(EVENT_8, 1);
                    else if (counter == 8)
                        events.ScheduleEvent(EVENT_1, 1);

                    events.ScheduleEvent(EVENT_STORMS_EDGE, 10000);
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_1:
                    events.ScheduleEvent(EVENT_1, 1);
                    counter = 1;
                    break;
                case POINT_2:
                    events.ScheduleEvent(EVENT_2, 1);
                    counter = 2;
                    break;
                case POINT_3:
                    events.ScheduleEvent(EVENT_3, 1);
                    counter = 3;
                    break;
                case POINT_4:
                    events.ScheduleEvent(EVENT_4, 1);
                    counter = 4;
                    break;
                case POINT_5:
                    events.ScheduleEvent(EVENT_5, 1);
                    counter = 5;
                    break;
                case POINT_6:
                    events.ScheduleEvent(EVENT_6, 1);
                    counter = 6;
                    break;
                case POINT_7:
                    events.ScheduleEvent(EVENT_7, 1);
                    counter = 7;
                    break;
                case POINT_8:
                    events.ScheduleEvent(EVENT_8, 1);
                    counter = 8;
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
                    case EVENT_STORMS_EDGE:
                        if (Unit* target = me->FindNearestPlayer(5.0f, true))
                            DoCast(target, SPELL_STORMS_EDGE);
                        events.ScheduleEvent(EVENT_STORMS_EDGE, 1000);
                        break;
                    case EVENT_STOP:
                        me->StopMoving();
                        break;
                    case EVENT_1:
                        me->GetMotionMaster()->MovePoint(POINT_2, Point3);
                        break;
                    case EVENT_2:
                        me->GetMotionMaster()->MovePoint(POINT_3, Point4);
                        break;
                    case EVENT_3:
                        me->GetMotionMaster()->MovePoint(POINT_4, Point5);
                        break;
                    case EVENT_4:
                        me->GetMotionMaster()->MovePoint(POINT_5, Point6);
                        break;
                    case EVENT_5:
                        me->GetMotionMaster()->MovePoint(POINT_6, Point7);
                        break;
                    case EVENT_6:
                        me->GetMotionMaster()->MovePoint(POINT_7, Point8);
                        break;
                    case EVENT_7:
                        me->GetMotionMaster()->MovePoint(POINT_8, Point1);
                        break;
                    case EVENT_8:
                        me->GetMotionMaster()->MovePoint(POINT_1, Point2);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new npc_cyclone_shieldAI (Creature);
    }
};

class npc_lurking_tempest : public CreatureScript
{
public:
    npc_lurking_tempest() : CreatureScript("npc_lurking_tempest") { }

    struct npc_lurking_tempestAI : public ScriptedAI
    {
        npc_lurking_tempestAI(Creature *creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            instance = me->GetInstanceScript();
            DoCastAOE(SPELL_LURK);
            if (Unit* Boss = me->FindNearestCreature(BOSS_GRAND_VIZIER_ERTAN, 100.0f))
            {
                BossGUID = Boss->GetGUID();            
                me->SetTarget(BossGUID);
            }
            Boo = urand(1000, 4000);
        }

        InstanceScript* instance;
        uint32 Boo;
        uint64 BossGUID;

        void IsSummonedBy(Unit* summoner)
        {
            me->RemoveAllAuras();
        }

        void UpdateAI(uint32 diff)
        {
            if (Boo <= diff)
            {
                if (Player* target = me->FindNearestPlayer(40.0f))
                    if (target->isInFrontInMap(me, 40.0f))
                        DoCastAOE(SPELL_LURK);
                    else
                    {
                        me->RemoveAurasDueToSpell(SPELL_LURK);
                        DoCast(target, SPELL_TEMPEST_LIGHTING_BOLT); 
                    }
                Boo = urand(1000, 4000);
            }
            else
                Boo -= diff;
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lurking_tempestAI(creature);
    }
};

class spell_storms_edge : public SpellScriptLoader
{
public:
    spell_storms_edge() : SpellScriptLoader("spell_storms_edge") { }

    class spell_storms_edge_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_storms_edge_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_STORMS_EDGE_PERIODIC))
                return false;
            return true;
        }

        void EffectScriptEffect(SpellEffIndex effIndex)
        {
            GetCaster()->CastSpell(GetHitUnit(), SPELL_STORMS_EDGE, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_storms_edge_SpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_storms_edge_SpellScript();
    }
};

void AddSC_boss_grand_vizier_ertan()
{
    new boss_grand_vizier_ertan();
    new npc_cyclone_shield();
    new npc_lurking_tempest();
    new spell_storms_edge();
}