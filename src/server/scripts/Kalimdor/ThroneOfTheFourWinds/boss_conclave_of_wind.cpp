
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "throne_of_the_four_winds.h"

enum Spells
{
    SPELL_GATHER_STRENGHT           = 86307,

    // Anshal
    SPELL_SOOTHING_BREEZE           = 86205,

    SPELL_NURTURE                   = 85422,
    SPELL_NURTURE_SUMMON_TRIGGER    = 85425,
    SPELL_NURTURE_DUMMY_AURA        = 85428,
    SPELL_NURTURE_CREEPER_SUMMON    = 85429,

    SPELL_TOXIC_SPORES              = 86281,

    // Nezir
    SPELL_ICE_PATCH                 = 86122,
    SPELL_ICE_PATCH_VISUAL          = 86107,
    SPELL_ICE_PATCH_AURA            = 86111,

    SPELL_PERMAFROST                = 86082,
    SPELL_WIND_CHILL                = 84645,

    // Rohash
    SPELL_SLICING_GALE              = 86182,
    SPELL_WIND_BLAST                = 86193,
    SPELL_TORNADO                   = 86192,

    SPELL_HURRICANE_VISUAL          = 86134
};

enum Events
{
    // Anshal
    EVENT_SOOTHING_BREEZE           = 1,
    EVENT_NURTURE                   = 2,
    EVENT_TOXIC_SPORES              = 3,

    // Nezir
    EVENT_ICE_PATCH                 = 4,
    EVENT_PERMAFROST                = 5,
    EVENT_WIND_CHILL                = 6,

    // Rohash
    EVENT_TORNADOS                  = 7,
    EVENT_WIND_BLAST                = 8
};

namespace ConclaveOfWind
{
    class PlayerSelector
    {
    public:
        bool operator() (Unit* unit)
        {
            return unit->GetTypeId() != TYPEID_PLAYER;
        }
    };

    void CheckOnPlatform(Creature* me)
    {
        if (!me->isInCombat())
            return;

        if (me->GetDistance(me->GetHomePosition()) > PLATFORM_RADIUS)
        {
            me->AI()->EnterEvadeMode();

            me->getHostileRefManager().deleteReferences();
            me->CombatStop();
            me->DeleteThreatList();

            Position homePos = me->GetHomePosition();
            me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation(), false);
            me->DestroyForNearbyPlayers();

            if (me->GetEntry() == BOSS_ANSHAL || me->GetEntry() == BOSS_NEZIR)
                me->CastSpell(me, SPELL_TELEPORT_VISUAL, true);
        }
    }
}

using namespace ConclaveOfWind;

class boss_conclave_of_wind : public CreatureScript
{
public:
    boss_conclave_of_wind() : CreatureScript("boss_conclave_of_wind") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_conclave_of_windAI (creature);
    }

    struct boss_conclave_of_windAI : public ScriptedAI
    {
        boss_conclave_of_windAI(Creature* creature) : ScriptedAI(creature), platform(creature->GetHomePosition()), instance(creature->GetInstanceScript()) { }

        InstanceScript* instance;
        EventMap events;

        bool isCastingUltimate;
        bool saiOnLowHealth;

        Position const platform;
        float windBlastOrientation;

        void Reset()
        {
            me->InterruptNonMeleeSpells(false);
            instance->SetBossState(DATA_CONCLAVE_OF_WIND, NOT_STARTED);

            events.Reset();

            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);

            if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(UltimateGameobjects[GetConclaveTypeByEntry(me->GetEntry())])))
                go->SetGoState(GO_STATE_READY);

            isCastingUltimate = false;
            saiOnLowHealth    = true;
            windBlastOrientation = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->RemoveAllAuras();
            instance->SetBossState(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);

            if (instance->GetData(DATA_IS_CONCLAVE_IN_BERSERK))
                DoCast(me, SPELL_BERSERK);

            events.Reset();
            switch (me->GetEntry())
            {
                case BOSS_ANSHAL:
                    events.ScheduleEvent(EVENT_SOOTHING_BREEZE, 15000);
                    events.ScheduleEvent(EVENT_NURTURE, urand(23000, 26000));
                    break;
                case BOSS_NEZIR:
                    events.ScheduleEvent(EVENT_ICE_PATCH, 12000);
                    events.ScheduleEvent(EVENT_PERMAFROST, 8000);
                    events.ScheduleEvent(EVENT_WIND_CHILL, 10500);
                    break;
                case BOSS_ROHASH:
                    events.ScheduleEvent(EVENT_TORNADOS, 3000);
                    events.ScheduleEvent(EVENT_WIND_BLAST, 22000);
                    break;
            }
        }

        void DoTeleportToHomePosition()
        {
            if (me->GetEntry() != BOSS_ROHASH)
            {
                Position homePos = me->GetHomePosition();
                me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation(), false);
                DoCast(me, SPELL_TELEPORT_VISUAL, true);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (saiOnLowHealth && me->GetHealthPct() < 15.f)
            {
                saiOnLowHealth = false;
                TalkToFar(SAY_CONCLAVE_LOW_HEALTH, TEXT_RANGE_AREA);
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32(me->GetPower(POWER_MANA)) >= uint32(me->GetMaxPower(POWER_MANA)))
            {
                me->SetPower(POWER_MANA, 0);

                DoTeleportToHomePosition();

                isCastingUltimate = true;
                TalkToFar(SAY_CONCLAVE_FULL_POWER, TEXT_RANGE_AREA);

                instance->SetData(DATA_IS_ULTIMATE_IN_PROGRESS, true);

                if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(UltimateGameobjects[GetConclaveTypeByEntry(me->GetEntry())])))
                    go->SetGoState(GO_STATE_ACTIVE);

                switch (me->GetEntry())
                {
                    case BOSS_ANSHAL:
                        events.CancelEvent(EVENT_TOXIC_SPORES);
                        events.CancelEvent(EVENT_NURTURE);
                        DoCast(SPELL_ZEPHYR_ULTIMATE);
                        return;
                    case BOSS_NEZIR:
                        events.CancelEvent(EVENT_ICE_PATCH);
                        events.CancelEvent(EVENT_PERMAFROST);
                        DoCast(SPELL_SLEET_STORM_ULTIMATE);
                        return;
                    case BOSS_ROHASH:
                        me->DespawnCreaturesInArea(NPC_HURRICANE, 40.f);
                        events.CancelEvent(EVENT_TORNADOS);
                        events.ScheduleEvent(EVENT_TORNADOS, 19000);
                        DoCast(SPELL_HURRICANE_ULTIMATE);
                        return;
                }
            }

            // Informs the instance script that the ultimate is over
            if (isCastingUltimate)
            {
                isCastingUltimate = false;
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(UltimateGameobjects[GetConclaveTypeByEntry(me->GetEntry())])))
                    go->SetGoState(GO_STATE_READY);

                if (me->GetEntry() == BOSS_ROHASH)
                    instance->SetData(DATA_HURRICANE_ENDED, 0);

                instance->SetData(DATA_IS_ULTIMATE_IN_PROGRESS, false);

                switch (me->GetEntry())
                {
                    case BOSS_ANSHAL:
                        events.ScheduleEvent(EVENT_NURTURE, urand(20000, 25000));
                        break;
                    case BOSS_NEZIR:
                        events.ScheduleEvent(EVENT_ICE_PATCH, 8000);
                        events.ScheduleEvent(EVENT_PERMAFROST, 15000);
                        break;
                    case BOSS_ROHASH:
                        break;
                }
            }

            CheckOnPlatform(me);

            if (!UpdateVictim() || me->HasReactState(REACT_PASSIVE))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // Anshal
                    case EVENT_SOOTHING_BREEZE:
                    {
                        std::list<Creature*> targets;
                        me->GetCreatureListWithEntryInGrid(targets, NPC_RAVENOUS_CREEPER, 80.f);
                        DoCast(targets.empty() ? me : SelectRandomContainerElement(targets), SPELL_SOOTHING_BREEZE, true);
                        events.ScheduleEvent(EVENT_SOOTHING_BREEZE, 32500);
                        break;
                    }
                    case EVENT_NURTURE:
                    {
                        TalkToFar(SAY_CONCLAVE_SLAY_OR_ABILITY, TEXT_RANGE_AREA);
                        DoCast(SPELL_NURTURE);
                        events.ScheduleEvent(EVENT_TOXIC_SPORES, urand(21000, 24000));
                        break;
                    }
                    case EVENT_TOXIC_SPORES:
                    {
                        // All Ravenous Creeper cast at the same time toxic spores
                        std::list<Creature*> ravenousCreeper;
                        me->GetCreatureListWithEntryInGrid(ravenousCreeper, NPC_RAVENOUS_CREEPER, 70.f);

                        for (std::list<Creature*>::iterator itr = ravenousCreeper.begin(); itr != ravenousCreeper.end(); ++itr)
                            (*itr)->CastSpell(*itr, SPELL_TOXIC_SPORES);

                        events.ScheduleEvent(EVENT_TOXIC_SPORES, 17000);
                        break;
                    }
                    // Nezir
                    case EVENT_ICE_PATCH:
                    {
                        TalkToFar(SAY_CONCLAVE_SLAY_OR_ABILITY, TEXT_RANGE_AREA);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f, true))
                            DoCast(target, SPELL_ICE_PATCH);
                        events.ScheduleEvent(EVENT_ICE_PATCH, 16000);
                        break;
                    }
                    case EVENT_PERMAFROST:
                    {
                        DoCast(me, SPELL_PERMAFROST);
                        events.ScheduleEvent(EVENT_PERMAFROST, 15000);
                        break;
                    }
                    case EVENT_WIND_CHILL:
                    {
                        DoCastAOE(SPELL_WIND_CHILL);
                        events.ScheduleEvent(EVENT_WIND_CHILL, 10500);
                        break;
                    }
                    // Rohash
                    case EVENT_TORNADOS:
                    {
                        if (!me->FindNearestCreature(NPC_HURRICANE, 30.f))
                            DoCast(me, SPELL_TORNADO);
                        return;
                    }
                    case EVENT_WIND_BLAST:
                    {
                        windBlastOrientation = frand(0, 6) * (static_cast<float>(M_PI) / 3.f);
                        SetOrientationTick(windBlastOrientation, 0);
                        TalkToFar(SAY_CONCLAVE_SLAY_OR_ABILITY, TEXT_RANGE_AREA);
                        DoCast(SPELL_WIND_BLAST);
                        events.ScheduleEvent(EVENT_WIND_BLAST, 60000);
                        return;
                    }
                }
            }

            if (me->GetEntry() == BOSS_ROHASH)
                DoSpellAttackIfReady(SPELL_SLICING_GALE);
            else
                DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_CONCLAVE_RESSURECT:
                {
                    me->SetFullHealth();
                    me->SetPower(POWER_MANA, 0);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    EnterCombat(NULL);
                    me->SetInCombatWithZone();
                    break;
                }
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type == DATA_WIND_BLAST_TICK)
                SetOrientationTick(windBlastOrientation, data);
        }

        void KilledUnit(Unit* /*victim*/)
        {
            TalkToFar(SAY_CONCLAVE_SLAY_OR_ABILITY, TEXT_RANGE_AREA);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_ICE_PATCH:
                case NPC_SOOTHING_BREEZE:
                    summon->DespawnOrUnsummon(urand(37000, 45000));
                    break;
                case NPC_HURRICANE:
                    summon->GetMotionMaster()->MoveRandom(22.f);
                    break;
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (me->GetHealth() <= damage)
            {
                if(me->HasReactState(REACT_PASSIVE))
                    return;

                damage = 0;

                me->InterruptNonMeleeSpells(false);

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                me->SetHealth(1);
                events.Reset();

                if (me->GetEntry() == BOSS_ROHASH)
                    me->DespawnCreaturesInArea(NPC_HURRICANE);

                DoCast(me, SPELL_GATHER_STRENGHT);
                instance->SetData(DATA_CONCLAVE_MEMBER_FALLEN, me->GetEntry());
            }
        }

        void SetOrientationTick(float orientation, uint32 const count)
        {
            orientation += count * (static_cast<float>(M_PI) / 3.f / 6.f);
            orientation = Position::NormalizeOrientation(orientation);
            me->SetOrientation(orientation);
            me->SetFacingTo(orientation);
        }
    };
};

class npc_ravenous_creeper : public CreatureScript
{
public:
    npc_ravenous_creeper() : CreatureScript("npc_ravenous_creeper") { }

    struct npc_ravenous_creeperAI : public ScriptedAI
    {
        npc_ravenous_creeperAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) { }

        uint32 uiInCombatCheck;
        InstanceScript* instance;

        void Reset()
        {
            uiInCombatCheck = 2000;

            if (Creature* anshal = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_ANSHAL)))
                me->SetHomePosition(anshal->GetHomePosition());
        }

        void UpdateAI(uint32 diff)
        {
            if (uiInCombatCheck <= diff)
            {
                CheckOnPlatform(me);

                if (me->HasReactState(REACT_PASSIVE))
                    me->SetReactState(REACT_AGGRESSIVE);

                me->SetInCombatWithZone();

                uiInCombatCheck = 5000;

            }
            else
                uiInCombatCheck -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ravenous_creeperAI (creature);
    }
};

class npc_conclave_platform_checker : public CreatureScript
{
public:
    npc_conclave_platform_checker() : CreatureScript("npc_conclave_platform_checker") { }

    struct npc_conclave_platform_checkerAI : public ScriptedAI
    {
        npc_conclave_platform_checkerAI(Creature* creature) : ScriptedAI(creature), type(GetConclaveTypeByEntry(creature->GetEntry())), windDebuff(SpellWindDebuffs[type]), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;
        uint8 const type;
        uint32 const windDebuff;
        uint32 uiCheckTimer;

        void Reset()
        {
            uiCheckTimer = urand(800, 1400);
        }

        void UpdateAI(uint32 diff)
        {
            if (!windDebuff)
                return;

            if (uiCheckTimer <= diff)
            {
                if (Creature* conclaveMember = me->GetCreature(*me, instance->GetData64(ConclaveMembers[type])))
                {
                    bool const hasAura = conclaveMember->HasAura(windDebuff);

                    if (conclaveMember->isAlive() && conclaveMember->HasReactState(REACT_AGGRESSIVE) && instance->GetBossState(DATA_CONCLAVE_OF_WIND) == IN_PROGRESS)
                    {
                        Player* playerInRange = me->FindNearestPlayer(PLATFORM_RADIUS);
                        if (playerInRange && !conclaveMember->isInCombat())
                        {
                            if (playerInRange->GetDistance(conclaveMember) > PLATFORM_RADIUS)
                                playerInRange = NULL;
                        }

                        if (!hasAura && !playerInRange)
                            conclaveMember->CastSpell(conclaveMember, windDebuff, true);
                        else if (hasAura && playerInRange)
                        {
                            conclaveMember->RemoveAurasDueToSpell(windDebuff);
                            if (!conclaveMember->isInCombat() && !playerInRange->isGameMaster())
                            {
                                conclaveMember->SetInCombatWith(playerInRange);
                                conclaveMember->SetInCombatWithZone();
                                conclaveMember->AddThreat(playerInRange, 1.f);
                                conclaveMember->SetInCombatWith(playerInRange);

                                if (conclaveMember->GetEntry() != BOSS_ROHASH)
                                    conclaveMember->GetMotionMaster()->MoveChase(playerInRange);
                            }
                        }

                    }
                    else if (hasAura)
                        conclaveMember->RemoveAura(windDebuff);
                }

                uiCheckTimer = 800;
            }
            else
                uiCheckTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_conclave_platform_checkerAI (creature);
    }
};

// 85422 Nurture
class spell_nurture : public SpellScriptLoader
{
public:
    spell_nurture() : SpellScriptLoader("spell_nurture") {}

    class spell_nurture_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_nurture_AuraScript);

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                Position pos = caster->GetRandomNearPosition(frand(14.f, 27.f));
                pos.m_positionZ = caster->GetPositionZ();

                caster->SummonCreature(NPC_RAVENOUS_CREEPER_TRIGGER, pos, TEMPSUMMON_TIMED_DESPAWN, 14000);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_nurture_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_nurture_AuraScript();
    }
};

// 85428 Nurture
class spell_nurture_dummy_aura : public SpellScriptLoader
{
public:
    spell_nurture_dummy_aura() : SpellScriptLoader("spell_nurture_dummy_aura") {}

    class spell_nurture_dummy_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_nurture_dummy_aura_AuraScript);

        bool effectExecuted;

        bool Load()
        {
            effectExecuted = false;
            return true;
        }

        void HandleEffectCalcPeriodic(AuraEffect const* /*aurEff*/, bool & isPeriodic, int32 & amplitude)
        {
            isPeriodic = true;
            amplitude = 11000;
        }

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (effectExecuted)
                return;

            if (Unit* caster = GetCaster())
                if (Creature* ravenousCreeper = caster->SummonCreature(NPC_RAVENOUS_CREEPER, *caster, TEMPSUMMON_DEAD_DESPAWN))
                {
                    effectExecuted = true;

                    ravenousCreeper->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                    ravenousCreeper->SetReactState(REACT_PASSIVE);
                }
        }

        void Register()
        {
            DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_nurture_dummy_aura_AuraScript::HandleEffectCalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_nurture_dummy_aura_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_nurture_dummy_aura_AuraScript();
    }
};

// 86498 Hurricane
class spell_hurricane : public SpellScriptLoader
{
public:
    spell_hurricane() : SpellScriptLoader("spell_hurricane") {}

    class spell_hurricane_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hurricane_SpellScript);

        void HandleHitDummy(SpellEffIndex /*effIndex*/)
        {
            if (Player* player = GetHitPlayer())
                if (InstanceScript* instance = player->GetInstanceScript())
                    instance->SetData64(DATA_PLAYER_HIT_BY_HURRICANE, player->GetGUID());
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_hurricane_SpellScript::HandleHitDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hurricane_SpellScript();
    }
};

// 86307 Gather Strength
class spell_gather_strength : public SpellScriptLoader
{
public:
    spell_gather_strength() : SpellScriptLoader("spell_gather_strength") {}

    class spell_gather_strength_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gather_strength_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* me = caster->ToCreature())
                    if (me->HasReactState(REACT_PASSIVE) && me->isAlive())
                        me->AI()->DoAction(ACTION_CONCLAVE_RESSURECT);
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_gather_strength_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gather_strength_SpellScript();
    }
};

// 85576, 85578, 85573 Conclave Debuffs
class spell_conclave_debuff : public SpellScriptLoader
{
public:
    spell_conclave_debuff() : SpellScriptLoader("spell_conclave_debuff") {}

    class spell_conclave_debuff_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_conclave_debuff_AuraScript);

        int32 bp;

        bool Load()
        {
            bp = 0;
            return true;
        }

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (bp < 150000)
                bp += 1500;

            if (WorldObject* owner = GetOwner())
                if (Creature* caster = owner->ToCreature())
                    if (InstanceScript* instance = caster->GetInstanceScript())
                        if (Creature* trigger = caster->GetCreature(*caster, instance->GetData64(ConclaveTriggers[GetConclaveTypeByEntry(caster->GetEntry())])))
                        {
                            switch (GetId())
                            {
                                case SPELL_WITHERING_WINDS_EFFECT:
                                {
                                    trigger->CastCustomSpell(SPELL_WITHERING_WINDS_DAMAGE, SPELLVALUE_BASE_POINT0, bp, trigger);
                                    break;
                                }
                                case SPELL_CHILLING_WINDS_EFFECT:
                                {
                                    trigger->CastCustomSpell(SPELL_CHILLING_WINDS_DAMAGE, SPELLVALUE_BASE_POINT0, bp, trigger);
                                    break;
                                }
                                case SPELL_DEAFING_WINDS_EFFECT:
                                {
                                    trigger->CastCustomSpell(SPELL_DEAFING_WINDS_DAMAGE, SPELLVALUE_BASE_POINT0, bp, trigger);
                                    break;
                                }
                            }
                        }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_conclave_debuff_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_conclave_debuff_AuraScript();
    }
};

// 85480 Wind Blast
class spell_wind_blast : public SpellScriptLoader
{
    public:
        spell_wind_blast() : SpellScriptLoader("spell_wind_blast") { }

        class spell_wind_blast_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_wind_blast_AuraScript);

            bool Load()
            {
                tick = 0;
                return GetCaster()->GetTypeId() == TYPEID_UNIT;
            }

            void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                    caster->ToCreature()->AI()->SetData(DATA_WIND_BLAST_TICK, ++tick);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_wind_blast_AuraScript::HandlePeriodicTick, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }

        private:
            uint32 tick;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_wind_blast_AuraScript();
        }
};

void AddSC_boss_conclave_of_wind()
{
    new boss_conclave_of_wind();
    new npc_ravenous_creeper();
    new npc_conclave_platform_checker();
    new spell_nurture();
    new spell_nurture_dummy_aura();
    new spell_hurricane();
    new spell_gather_strength();
    new spell_conclave_debuff();
    new spell_wind_blast();
}
