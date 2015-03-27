
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"
#include "Vehicle.h"

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
    EVENT_UNRELENTING_AGONY         = 8,
    EVENT_ENSLAVE_SPELL_CAST        = 9,
    EVENT_KILL_PLAYER_HC            = 10
};

enum Spells
{
    // Erunak Stonespeaker
    SPELL_EARTH_SHARDS                      = 84931,
    SPELL_EARTH_SHARDS_DUMMY                = 84935,
    SPELL_EMBERSTRIKE                       = 76165,
    SPELL_LAVA_BOLT_N                       = 76171,
    SPELL_LAVA_BOLT_HC                      = 91412,
    SPELL_MAGMA_SPLASH                      = 76170,

    // Mindbender Ghur'sha
    SPELL_MINDBENDER_PLAYER_VEHICLE_AURA    = 76206,
    SPELL_ENSLAVE_N                         = 76207,
    SPELL_ENSLAVE_HC                        = 91413,

    SPELL_ENSLAVE_GROW                      = 76616,
    SPELL_ENSLAVE_FEED                      = 76213,

    SPELL_DUMMY_NUKE                        = 21912,
    SPELL_MIND_FOG                          = 76234,
    SPELL_MIND_FOG_DUMMY_VISUAL             = 76231,
    SPELL_MIND_FOG_DAMAGE                   = 76230,
    SPELL_ABSORB_MAGIC_N                    = 76307,
    SPELL_ABSORB_MAGIC_HC                   = 91492,
    SPELL_ABSORB_MAGIC_HEAL                 = 76308,
    SPELL_UNRELENTING_AGONY                 = 76339,
    SPELL_KNEEL                             = 68442
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
    SAY_RELEASE_ERUNAK,
    SAY_NEW_SLAVE,
    SAY_MIND_FOG,
    SAY_KILL_PLAYER,
    SAY_DEATH
};

enum Actions
{
    ACTION_ERUNAK_RESET
};

bool Enslave;
Unit* EnslavePlayer;

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
            RemoveEncounterFrame();
            RemoveEncounterAuras();
            if (instance->GetBossState(DATA_MINDEBENDER_GHURSHA) == DONE)
            {
                me->setFaction(FACTION_FRIENDLY);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                return;
            }

            if (me->getFaction() == FACTION_FRIENDLY)
                return;

            events.Reset();
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveAurasDueToSpell(SPELL_KNEEL);
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
                ghursha->CastSpell(ghursha, SPELL_ENSLAVE_GROW);

                class AsyncJoin : public BasicEvent
                {
                public:
                    explicit AsyncJoin(uint64 const& _ui_erunak, Creature* _ghursha) : ui_erunak(_ui_erunak), ghursha(_ghursha) {}

                    bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
                    {
                        if (Creature* erunak = ObjectAccessor::GetCreature(*ghursha, ui_erunak))
                        {
                            if (erunak->getFaction() != FACTION_FRIENDLY)
                            {
                                if (!ghursha->IsOnVehicle(erunak))
                                    ghursha->EnterVehicle(erunak, 0);

                                ghursha->m_Events.AddEvent(this, ghursha->m_Events.CalculateTime(1000));
                                return false;
                            }
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
            RemoveEncounterAuras();
            events.ScheduleEvent(EVENT_EARTH_SHARDS, 20000);
            events.ScheduleEvent(EVENT_EMBERSTRIKE, 11000);
            events.ScheduleEvent(EVENT_LAVA_BOLT, 6500);
            events.ScheduleEvent(EVENT_MAGMA_SPLASH, 17000);

            instance->SetBossState(DATA_MINDEBENDER_GHURSHA, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            if (me->getFaction() != FACTION_FRIENDLY)
                return;

            me->AI()->TalkWithDelay(5000, SAY_THANKS);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_KNEEL, false);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->getFaction() == FACTION_FRIENDLY)
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            events.Update(diff);
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EARTH_SHARDS:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_EARTH_SHARDS);
                        events.ScheduleEvent(EVENT_EARTH_SHARDS, 20000);
                        break;
                    }
                    case EVENT_EMBERSTRIKE:
                    {
                        DoCastVictim(SPELL_EMBERSTRIKE);
                        events.ScheduleEvent(EVENT_EMBERSTRIKE, 11000);
                        break;
                    }
                    case EVENT_LAVA_BOLT:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.f, true))
                            DoCast(target, DUNGEON_MODE(SPELL_LAVA_BOLT_N, SPELL_LAVA_BOLT_HC));
                        events.ScheduleEvent(EVENT_LAVA_BOLT, 6500);
                        break;
                    }
                    case EVENT_MAGMA_SPLASH:
                    {
                        DoCast(SPELL_MAGMA_SPLASH);
                        events.ScheduleEvent(EVENT_MAGMA_SPLASH, 17000);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_EARTH_SHARD:
                {
                    me->SetReactState(REACT_PASSIVE);
                    summon->CastSpell(summon, SPELL_EARTH_SHARDS_DUMMY, false);
                    Position pos = *summon;
                    me->MovePositionToFirstCollision(pos, 20.f, 0);
                    summon->GetMotionMaster()->MovePoint(0, pos);
                    summon->DespawnOrUnsummon(7000);
                    break;
                }
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (me->HealthBelowPct(50))
            {
                damage = 0;

                RemoveEncounterFrame();

                me->setFaction(FACTION_FRIENDLY);

                if (Creature* ghursha = me->GetCreature(*me, uiGhursha))
                {
                    ghursha->RemoveAura(SPELL_ENSLAVE_GROW);
                    ghursha->ExitVehicle();
                    ghursha->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    ghursha->SetReactState(REACT_AGGRESSIVE);
                    ghursha->SetInCombatWithZone();
                    ghursha->AI()->Talk(SAY_RELEASE_ERUNAK);
                }

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

        void RemoveEncounterAuras()
        {
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_FEED);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_GROW);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MINDBENDER_PLAYER_VEHICLE_AURA);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_N);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_HC);
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
    boss_mindbender_ghursha() : CreatureScript("boss_mindbender_ghursha"){ }

    struct boss_mindbender_ghurshaAI : public BossAI
    {
        boss_mindbender_ghurshaAI(Creature* creature) : BossAI(creature, DATA_MINDEBENDER_GHURSHA), instance(creature->GetInstanceScript())
        {
            Enslave = false;
            EnslavePlayer = NULL;
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            if (instance->GetBossState(DATA_MINDEBENDER_GHURSHA) == IN_PROGRESS)
            {
                RemoveEncounterFrame();
                events.Reset();

                if (Creature* erunak = me->GetCreature(*me, instance->GetData64(NPC_ERUNAK_STONESPEAKER)))
                {
                    if (erunak->getFaction() == FACTION_FRIENDLY)
                        erunak->AI()->DoAction(ACTION_ERUNAK_RESET);
                }
            }
            RemoveEncounterAuras();
        }

        void EnterCombat(Unit* /*who*/)
        {
            AddEncounterFrame();
            RemoveEncounterAuras();
            events.ScheduleEvent(EVENT_ENSLAVE, 5000);
            events.ScheduleEvent(EVENT_ABSORB_MAGIC, 20000);
            events.ScheduleEvent(EVENT_MIND_FOG, urand(6000, 12000));
            events.ScheduleEvent(EVENT_UNRELENTING_AGONY, 10000);
            me->SetDisableGravity(true);
            me->SetHover(true);
            me->SetCanFly(true);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_MIND_FOG:
                {
                    summon->SetReactState(REACT_PASSIVE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                    summon->CastSpell(summon, SPELL_MIND_FOG_DUMMY_VISUAL, false);
                    summon->CastSpell(summon, SPELL_MIND_FOG_DAMAGE, false);
                    summon->DespawnOrUnsummon(20000);
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (Enslave)
            {
                if (EnslavePlayer && EnslavePlayer != NULL && EnslavePlayer->IsInWorld())
                {
                    if (EnslavePlayer->HealthBelowPct(50))
                    {
                        RemoveEncounterAuras();
                        EnslaveTarget(EnslavePlayer, false);
                    }
                }
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ENSLAVE_SPELL_CAST:
                    {
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            if (EnslavePlayer && EnslavePlayer != NULL && EnslavePlayer->IsInWorld() && EnslavePlayer->GetTypeId() == TYPEID_PLAYER)
                            {
                                switch (EnslavePlayer->getClass())
                                {
                                    case CLASS_DRUID:
                                    {
                                        if (urand(0, 1))
                                            EnslavePlayer->CastSpell(target, 8921, false);
                                        else
                                            EnslavePlayer->CastSpell(me, 774, false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_HUNTER:
                                    {
                                        EnslavePlayer->CastSpell(target, RAND(2643, 1978), false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_MAGE:
                                    {
                                        EnslavePlayer->CastSpell(target, RAND(44614, 30455), false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_WARLOCK:
                                    {
                                        EnslavePlayer->CastSpell(target, RAND(980, 686), true);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_WARRIOR:
                                    {
                                        EnslavePlayer->CastSpell(target, RAND(46924, 845), false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_PALADIN:
                                    {
                                        if (urand(0, 1))
                                            EnslavePlayer->CastSpell(target, 853, false);
                                        else
                                            EnslavePlayer->CastSpell(me, 20473, false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_PRIEST:
                                    {
                                        if (urand(0, 1))
                                            EnslavePlayer->CastSpell(target, 34914, false);
                                        else
                                            EnslavePlayer->CastSpell(me, 139, false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_SHAMAN:
                                    {
                                        if (urand(0, 1))
                                            EnslavePlayer->CastSpell(target, 421, false);
                                        else
                                            EnslavePlayer->CastSpell(me, 61295, false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_ROGUE:
                                    {
                                        EnslavePlayer->CastSpell(target, RAND(16511, 1329), false);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    case CLASS_DEATH_KNIGHT:
                                    {
                                        if (urand(0, 1))
                                            EnslavePlayer->CastSpell(target, 45462, true);
                                        else
                                            EnslavePlayer->CastSpell(target, 49184, true);
                                        events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        break;
                    }
                    case EVENT_ENSLAVE:
                    {
                        // Reschedule if is already controlling
                        if (me->GetVehicleBase())
                        {
                            events.RescheduleEvent(EVENT_ENSLAVE, 3000);
                            break;
                        }

                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        {
                            Talk(SAY_NEW_SLAVE);
                            me->FinishSpell(CURRENT_CHANNELED_SPELL, false);
                            target->CastSpell(target, SPELL_MINDBENDER_PLAYER_VEHICLE_AURA, true);
                            EnslavePlayer = target;
                            EnslaveTarget(target, true);
                            DoCast(target, DUNGEON_MODE(SPELL_ENSLAVE_N, SPELL_ENSLAVE_HC));
                            events.ScheduleEvent(EVENT_KILL_PLAYER_HC, 30000);
                        }
                        break;
                    }
                    case EVENT_ABSORB_MAGIC:
                    {
                        DoCast(me, DUNGEON_MODE(SPELL_ABSORB_MAGIC_N, SPELL_ABSORB_MAGIC_HC));
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
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.f, true))
                            DoCast(target, SPELL_UNRELENTING_AGONY);
                        events.ScheduleEvent(EVENT_UNRELENTING_AGONY, urand(23000, 30000));
                        break;
                    }
                    case EVENT_KILL_PLAYER_HC:
                    {
                        if (Unit* enslavedPlayer = me->GetVehicleBase())
                            me->Kill(enslavedPlayer);
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!Enslave)
                DoMeleeAttackIfReady();
        }

        void EnslaveTarget(Unit* target, bool active)
        {
            if (!target)
                return;

            if (target->GetTypeId() != TYPEID_PLAYER)
                return;

            if (Player* player = target->ToPlayer())
            {
                if (active)
                {
                    Enslave = true;
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_PASSIVE);

                    player->UpdatePvP(true);
                    player->CastSpell(player, SPELL_ENSLAVE_GROW, false);
                    player->CastSpell(player, SPELL_ENSLAVE_FEED, false);

                    events.CancelEvent(EVENT_ENSLAVE);
                    events.CancelEvent(EVENT_ABSORB_MAGIC);
                    events.CancelEvent(EVENT_MIND_FOG);
                    events.ScheduleEvent(EVENT_ENSLAVE_SPELL_CAST, 3000);

                    // Kill player if not freed within 30 seconds in heroic mode
                    if (me->GetMap()->IsHeroic())
                        events.ScheduleEvent(EVENT_KILL_PLAYER_HC, 29000);
                }
                else
                {
                    events.CancelEvent(EVENT_KILL_PLAYER_HC);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->ExitVehicle();
                    player->RemoveAurasDueToSpell(SPELL_ENSLAVE_GROW);
                    player->RemoveAurasDueToSpell(SPELL_ENSLAVE_FEED);
                    player->UpdatePvP(false);
                    EnslavePlayer = NULL;

                    Enslave = false;
                    DoZoneInCombat();
                    events.CancelEvent(EVENT_ENSLAVE_SPELL_CAST);
                    events.ScheduleEvent(EVENT_ENSLAVE, 13000);
                    events.ScheduleEvent(EVENT_ABSORB_MAGIC, 20000);
                    events.ScheduleEvent(EVENT_MIND_FOG, urand(6000,12000));
                    events.ScheduleEvent(EVENT_UNRELENTING_AGONY, 10000);
                }
            }
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_KILL_PLAYER);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);

            if (Creature* erunak = me->GetCreature(*me, instance->GetData64(NPC_ERUNAK_STONESPEAKER)))
                erunak->AI()->TalkWithDelay(7000, SAY_GOODBYE);

            me->DespawnCreaturesInArea(NPC_EARTH_SHARD);
            me->DespawnCreaturesInArea(NPC_MIND_FOG);
            RemoveEncounterFrame();
            RemoveEncounterAuras();
            instance->SetBossState(DATA_MINDEBENDER_GHURSHA, DONE);
            me->SetDisableGravity(false);
            me->SetHover(false);
            me->SetCanFly(false);
        }

        void RemoveEncounterAuras()
        {
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_FEED);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_GROW);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MINDBENDER_PLAYER_VEHICLE_AURA);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_N);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ENSLAVE_HC);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_mindbender_ghurshaAI (creature);
    }
};


// Id: 76307 / 91492
// Name: Absorb Magic
class spell_tott_absorb_magic : public SpellScriptLoader
{
public:
    spell_tott_absorb_magic() : SpellScriptLoader("spell_tott_absorb_magic") {}

    class spell_tott_absorb_magic_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tott_absorb_magic_AuraScript);

        int32 absorb;

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorption amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * caster = GetCaster();
            if (!caster)
                return;

            int32 heal = dmgInfo.GetDamage() * 3;
            caster->CastCustomSpell(caster, SPELL_ABSORB_MAGIC_HEAL, &heal, NULL, NULL, true, NULL, NULL, caster->GetGUID());
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_tott_absorb_magic_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_tott_absorb_magic_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tott_absorb_magic_AuraScript();
    }
};

void AddSC_boss_mindbender_ghursha()
{
    new npc_erunak_stonespeaker();
    new boss_mindbender_ghursha();
    new spell_tott_absorb_magic();
}