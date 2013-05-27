
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"

enum Events
{
    // Erunak
    EVENT_EARTH_SHARDS              = 1,
    EVENT_EMBERSTRIKE               = 2,
    EVENT_LAVA_BOLT                 = 3,
    EVENT_MAGMA_SPLASH              = 4,

    // Ghursha
    EVENT_ENSLAVE                   = 5,
    EVENT_ABSORB_MAGIC              = 6,
    EVENT_MIND_FOG                  = 7,
    EVENT_UNRELENTING_AGONY         = 8
};

enum Spells
{
    // Erunak Stonespeaker
    SPELL_EARTH_SHARDS              = 84931, // SPELL_EFFECT_TRIGGER_MISSILE
    SPELL_EARTH_SHARDS_SUMMON       = 84934, // SPELL_EFFECT_SUMMON: 45469
    SPELL_EARTH_SHARDS_DUMMY        = 84935,
    SPELL_EMBERSTRIKE               = 76165,
    SPELL_LAVA_BOLT                 = 76171,
    SPELL_MAGMA_SPLASH              = 76170,

    // Mindbender Ghur'sha
    SPELL_RIDE_VEHICLE              = 69063,
    SPELL_ENSLAVE                   = 76616, // SPELL_AURA_MOD_SCALE
    SPELL_ENSLAVE_UNK1              = 76207, // SPELL_AURA_CONTROL_VEHICLE, SPELL_AURA_MOD_CHARM, SPELL_AURA_MOD_SCALE
    SPELL_ENSLAVE_UNK2              = 76213, // SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, SPELL_AURA_MOD_HEALING_PCT
    SPELL_ENSLAVE_UNK3              = 84387, // SPELL_AURA_MOD_HEALING_PCT
    SPELL_DUMMY_NUKE                = 21912,
    SPELL_MIND_FOG                  = 76234, // SPELL_EFFECT_SUMMON: 40861
    SPELL_ABSORB_MAGIC              = 76307, // SPELL_AURA_SCHOOL_ABSORB
    SPELL_ABSORB_MAGIC_UNK1         = 76308, // SPELL_EFFECT_HEAL: Self
    SPELL_UNRELENTING_AGONY         = 76339, // SPELL_AURA_PERIODIC_TRIGGER_SPELL: 76341
};

enum Faction
{
    FACTION_FRIENDLY                = 35,
    FACTION_HOSTILE                 = 14
};

enum ErunakTexts
{
    SAY_THANKS,
    SAY_GOODBYE
};

enum GhurshaTexts
{
    SAY_NEW_SLAVE,
    SAY_UNRELENTING_AGONY,
    SAY_MIND_FOG,
    SAY_DEATH
};

enum Actions
{
    ACTION_ERUNAK_RESET,
};

class npc_erunak_stonespeaker : public CreatureScript
{
public:
    npc_erunak_stonespeaker() : CreatureScript("npc_erunak_stonespeaker") { }

    struct npc_erunak_stonespeakerAI : public ScriptedAI
    {
        npc_erunak_stonespeakerAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()), uiGhursha(0) {}

        InstanceScript* instance;
        EventMap events;
        uint64 uiGhursha;

        void Reset()
        {
            if (instance->GetBossState(DATA_MINDEBENDER_GHURSHA) == DONE)
            {
                me->setFaction(FACTION_FRIENDLY);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                return;
            }

            if (me->getFaction() == FACTION_FRIENDLY)
                return;

            events.Reset();
            instance->SetBossState(DATA_MINDEBENDER_GHURSHA, NOT_STARTED);

            me->DespawnCreaturesInArea(NPC_EARTH_SHARD);
            me->DespawnCreaturesInArea(NPC_MIND_FOG);

            if (Creature* ghursha = ObjectAccessor::GetCreature(*me, uiGhursha))
            {
                ghursha->ExitVehicle();
                ghursha->DespawnOrUnsummon();
            }

            me->DespawnCreaturesInArea(BOSS_MINDBENDER_GHURSHA);

            if (Creature* ghursha = me->SummonCreature(BOSS_MINDBENDER_GHURSHA, *me))
            {
                uiGhursha = ghursha->GetGUID();
                ghursha->SetReactState(REACT_PASSIVE);
                ghursha->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                ghursha->CastSpell(ghursha, SPELL_ENSLAVE);

                class AsyncJoin : public BasicEvent
                {
                public:
                    explicit AsyncJoin(uint64 const& _ui_erunak, Creature* _ghursha) : ui_erunak(_ui_erunak), ghursha(_ghursha) {}

                    bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
                    {
                        if (Creature* erunak = ObjectAccessor::GetCreature(*ghursha, ui_erunak))
                            if (erunak->getFaction() != FACTION_FRIENDLY)
                            {
                                if (!ghursha->IsOnVehicle(erunak))
                                    ghursha->EnterVehicle(erunak, 0);

                                ghursha->m_Events.AddEvent(this, ghursha->m_Events.CalculateTime(1000));
                                return false;
                            }
                     
                        return true;
                    }

                private:
                    uint64 const ui_erunak;
                    Creature* ghursha;
                };

                ghursha->m_Events.AddEvent(new AsyncJoin(me->GetGUID(), ghursha), ghursha->m_Events.CalculateTime(200));
            }
        }

        void EnterCombat(Unit* who)
        {
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_EARTH_SHARDS, 20000);
            events.ScheduleEvent(EVENT_EMBERSTRIKE, 11000);
            events.ScheduleEvent(EVENT_LAVA_BOLT, 6500);
            events.ScheduleEvent(EVENT_MAGMA_SPLASH, 17000);

            instance->SetBossState(DATA_MINDEBENDER_GHURSHA, IN_PROGRESS);
        }

        void UpdateAI(uint32 diff)
        {
            /*
            if (me->getFaction() == FACTION_FRIENDLY)
            {
                UpdateVictim();
                return;
            }
            */

            if (me->getFaction() == FACTION_FRIENDLY)
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EARTH_SHARDS:
                        DoCast(SPELL_EARTH_SHARDS);
                        events.ScheduleEvent(EVENT_EARTH_SHARDS, 20000);
                        break;
                    case EVENT_EMBERSTRIKE:
                        DoCastVictim(SPELL_EMBERSTRIKE);
                        events.ScheduleEvent(EVENT_EMBERSTRIKE, 11000);
                        break;
                    case EVENT_LAVA_BOLT:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.f, true))
                            DoCast(target, SPELL_LAVA_BOLT);

                        events.ScheduleEvent(EVENT_LAVA_BOLT, 6500);
                        break;
                    }
                    case EVENT_MAGMA_SPLASH:
                        DoCast(SPELL_MAGMA_SPLASH);
                        events.ScheduleEvent(EVENT_MAGMA_SPLASH, 17000);
                        break;
                }
            }            

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            if (summon->GetEntry() == NPC_EARTH_SHARD)
            {
                Position pos = *summon;
                me->MovePositionToFirstCollision(pos, 20.f, 0);
                summon->GetMotionMaster()->MovePoint(0, pos);
                summon->DespawnOrUnsummon(7000);
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (int32(me->GetHealth() + IsHeroic() ? 100000 : 50000) <= int32(damage))
            {
                damage = 0;

                RemoveEncounterFrame();

                me->setFaction(FACTION_FRIENDLY);

                if (Creature* ghursha = me->GetCreature(*me, uiGhursha))
                {
                    ghursha->RemoveAura(SPELL_ENSLAVE);
                    ghursha->ExitVehicle();
                    ghursha->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    ghursha->SetReactState(REACT_AGGRESSIVE);
                    ghursha->SetInCombatWithZone();
                    ghursha->AI()->Talk(SAY_NEW_SLAVE);
                }

                me->AI()->TalkWithDelay(5000, SAY_THANKS);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetReactState(REACT_PASSIVE);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_KNEEL);
                EnterEvadeMode();
            }
        }

        void DoAction(int32 action)
        {
            if (action == ACTION_ERUNAK_RESET)
            {
                instance->SetBossState(DATA_MINDEBENDER_GHURSHA, NOT_STARTED);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->setFaction(FACTION_HOSTILE);
                me->SetReactState(REACT_AGGRESSIVE);
                Reset();
            }
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new npc_erunak_stonespeakerAI(creature);
    }
};

class boss_mindbender_ghursha : public CreatureScript
{
public:
    boss_mindbender_ghursha() : CreatureScript("boss_mindbender_ghursha") { }

    struct boss_mindbender_ghurshaAI : public ScriptedAI
    {
        boss_mindbender_ghurshaAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            if (instance->GetBossState(DATA_MINDEBENDER_GHURSHA) == IN_PROGRESS)
            {
                RemoveEncounterFrame();
                events.Reset();

                if (Creature* erunak = me->GetCreature(*me, instance->GetData64(NPC_ERUNAK_STONESPEAKER)))
                    if (erunak->getFaction() == FACTION_FRIENDLY)
                        erunak->AI()->DoAction(ACTION_ERUNAK_RESET);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            AddEncounterFrame();

            events.ScheduleEvent(EVENT_ENSLAVE, 13000);
            events.ScheduleEvent(EVENT_ABSORB_MAGIC, 20000);
            events.ScheduleEvent(EVENT_MIND_FOG, urand(6000,12000));
            events.ScheduleEvent(EVENT_UNRELENTING_AGONY, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENSLAVE:
                        // ToDo: Implement that
                        events.ScheduleEvent(EVENT_ENSLAVE, 30000);
                        break;
                    case EVENT_ABSORB_MAGIC:
                    {
                        DoCast(me, SPELL_ABSORB_MAGIC);
                        events.ScheduleEvent(EVENT_ABSORB_MAGIC, 20000);
                        break;
                    }
                    case EVENT_MIND_FOG:
                    {
                        Talk(SAY_MIND_FOG);
                        DoCast(SPELL_MIND_FOG);
                        events.ScheduleEvent(EVENT_MIND_FOG, urand(15000,20000));
                        break;
                    }
                    case EVENT_UNRELENTING_AGONY:
                    {
                        Talk(SAY_UNRELENTING_AGONY);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.f, true))
                            DoCast(target, SPELL_UNRELENTING_AGONY);

                        events.ScheduleEvent(EVENT_UNRELENTING_AGONY, urand(23000, 30000));
                        break;
                    }
                }
            }		

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);

            if (Creature* erunak = me->GetCreature(*me, instance->GetData64(NPC_ERUNAK_STONESPEAKER)))
                erunak->AI()->TalkWithDelay(7000, SAY_GOODBYE);

            me->DespawnCreaturesInArea(NPC_EARTH_SHARD);
            me->DespawnCreaturesInArea(NPC_MIND_FOG);
            RemoveEncounterFrame();
            instance->SetBossState(DATA_MINDEBENDER_GHURSHA, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_mindbender_ghurshaAI (creature);
    }
};

void AddSC_boss_mindbender_ghursha()
{
    new npc_erunak_stonespeaker();
    new boss_mindbender_ghursha();
}
