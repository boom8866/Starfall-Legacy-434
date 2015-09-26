
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "blackwing_descent.h"

enum Spells
{
    ////////////////////////////////////////////
    // Intro
    SPELL_ROARING_BREATH            = 81573,  //   SPELL_EFFECT_ACTIVATE_OBJECT (on 204276)

    ////////////////////////////////////////////
    // General
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598,
    SPELL_GUARDIAN_TAUNT            = 85667,
    SPELL_TAUNT                     = 37486,
    SPELL_BERSERK                   = 95211,

    ////////////////////////////////////////////
    // Sound Bar
    SPELL_SOUND_BAR                 = 89683,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_SOUND_BAR_PERIODIC        = 88824,  // V SPELL_AURA_PERIODIC_DUMMY
    SPELL_SONAR_INCREASE            = 88827,
    SPELL_SONAR_DECREASE            = 88834,
    SPELL_MODULATION                = 77612,  //   SPELL_EFFECT_ENERGIZE, SPELL_EFFECT_SCHOOL_DAMAGE (TARGET_UNIT_SRC_AREA_ENEMY)

    ////////////////////////////////////////////
    // Ground
    SPELL_DEVASTATION_TRIGGER       = 78898,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_DEVASTATION               = 78868,  // V SPELL_EFFECT_SCHOOL_DAMAGE

    SPELL_VERTIGO                   = 77717,  //   SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, SPELL_AURA_MOD_STUN

    SPELL_SONIC_FLAMES              = 78864,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_SONIC_FLAMES_KILL      = 77782,  // V SPELL_EFFECT_INSTAKILL

    SPELL_SONAR_PULSE               = 77672,  // | SPELL_EFFECT_FORCE_CAST
    // SPELL_SONAR_PULSE_SUMMON     = 77673,  // V SPELL_EFFECT_SUMMON (41546)

    SPELL_SONIC_BREATH              = 78075,  // | SPELL_EFFECT_FORCE_CAST
    // SPELL_SONIC_BREATH_SUMMON    = 78091,  // V SPELL_EFFECT_SUMMON (41879)
    SPELL_SONIC_BREATH_CHANNEL      = 78098,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_SONIC_BREATH_DAMAGE    = 78100,  // V SPELL_EFFECT_SCHOOL_DAMAGE

    SPELL_SEARING_FLAME             = 77840,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_SEARING_FLAME_TRIGGER  = 77966,  // | SPELL_EFFECT_TRIGGER_MISSILE, SPELL_EFFECT_DUMMY
    // SPELL_SEARING_FLAME_MISSILE  = 77967,  // V SPELL_EFFECT_SUMMON (41807)
    SPELL_SEARING_FLAMES_UNK        = 77974,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_SEARING_FLAME_DAMAGE   = 77982,  // V SPELL_EFFECT_SCHOOL_DAMAGE, SPELL_EFFECT_ENERGIZE

    ////////////////////////////////////////////
    // Flying
    SPELL_ROARING_FLAME_BREATH      = 78207,  // | SPELL_EFFECT_FORCE_CAST (initial Cast)
    // SPELL_ROARING_FLAME_BREATH_S = 78213,  // V SPELL_EFFECT_SUMMON (41962)
    SPELL_ROARING_FLAME_VISUAL      = 78024,  //   SPELL_AURA_DUMMY
    SPELL_ROARING_FLAME             = 78018,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_ROARING_FLAME_DAMAGE   = 78023,  // V SPELL_EFFECT_SCHOOL_DAMAGE, SPELL_EFFECT_ENERGIZE
    SPELL_ROARING_FLAME_SUMMON      = 78272,  //   SPELL_EFFECT_SUMMON (42001)

    SPELL_ROARING_FLAME_BREATH_REV  = 78230,  //   SPELL_EFFECT_SCRIPT_EFFECT (78221)
    SPELL_ROARING_FLAME_BREATH_CHAN = 78221,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL (main channel visual spell)
    SPELL_ROARING_FLAME_BREATH_DMG  = 78353,  // V SPELL_EFFECT_SCHOOL_DAMAGE, SPELL_EFFECT_ENERGIZE
    SPELL_ROARING_FLAME_BREATH_PD   = 78354,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_ROARING_FLAME_BREATH_PERI = 78431,  // V SPELL_EFFECT_DUMMY

    // Trace
    // SPELL_BUILDING_SPEED_TRIGGER > SPELL_ROARING_FLAME_BREATH_PD > SPELL_ROARING_FLAME_BREATH_REV >
    // SPELL_AGGRO_CREATOR > SPELL_ROARING_FLAME_SUMMON >> (Triggered SPELL_ROARING_FLAME_BREATH_PERI)

    SPELL_BUILDING_SPEED_TRIGGER    = 78217,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    SPELL_BUILDING_SPEED_EFFECT     = 78218,  // V SPELL_AURA_MOD_INCREASE_SPEED
    SPELL_TRACKING                  = 78092,  //   SPELL_AURA_DUMMY (channeled)
    SPELL_AGGRO_CREATOR             = 63709,  //   SPELL_EFFECT_DUMMY

    SPELL_SONAR_BOMB                = 92557,  // | SPELL_EFFECT_TRIGGER_MISSILE
    // SPELL_SONAR_BOMB_DAMAGE      = 92553,  // V SPELL_EFFECT_SCHOOL_DAMAGE, SPELL_EFFECT_ENERGIZE

    SPELL_SONIC_FIREBALL            = 78030,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_SONIC_FIREBALL_DAMAGE  = 78115,  // V SPELL_EFFECT_SCHOOL_DAMAGE

    ////////////////////////////////////////////
    // Sonar Pulse
    SPELL_SONAR_PULSE_PERIODIC      = 92415,  // | SPELL_AURA_PERIODIC_TRIGGER_SPELL
    // SPELL_SONAR_PULSE_ENERGYZE   = 77675,  // V SPELL_EFFECT_ENERGIZE

    ////////////////////////////////////////////
    // Dwarfen Shield
    SPELL_RESONATING_CLASH          = 77709,  //   SPELL_EFFECT_ENERGIZE, SPELL_EFFECT_SCRIPT_EFFECT, SPELL_AURA_DUMMY
    SPELL_RESONATING_CLASH_UNK      = 77611,  //   SPELL_EFFECT_INTERRUPT_CAST, SPELL_EFFECT_SCRIPT_EFFECT

    SPELL_RESONATING_CLASH_AIR      = 78958,  //   SPELL_EFFECT_SCRIPT_EFFECT
    SPELL_RESONATING_CLASH_DEBUFF   = 78168,  //   SPELL_EFFECT_SCRIPT_EFFECT, SPELL_AURA_DUMMY

    ////////////////////////////////////////////
    // Obnoxious Fiend (Heroic)
    SPELL_SUMMON_IMPS               = 92655,  //   SPELL_EFFECT_SEND_EVENT (27558)

    ////////////////////////////////////////////
    // Nefarian (Heroic)
    SPELL_DESTROY_SHIELD            = 92607,  //   SPELL_EFFECT_INSTAKILL (TARGET_UNIT_SRC_AREA_ENTRY)

    ////////////////////////////////////////////
    // Pre Event
    SPELL_MORPH                     = 81221,
    SPELL_BLIND_WHELP               = 81214,
    SPELL_MEMORY_FOG                = 81178,
    SPELL_POTION_ON_HIP             = 81271
};

enum Events
{
    EVENT_SWITCH_PHASE          = 1,
    EVENT_DEVASTATION           = 2,

    // Ground Phase
    EVENT_MODULATION            = 13,
    EVENT_SONAR_PULSE           = 3,
    EVENT_SONIC_BREATH          = 4,
    EVENT_SONIC_BREATH_CHANNEL  = 5,
    EVENT_SEARING_FLAMES        = 6,

    // Air Phase
    EVENT_ROARING_FLAME_BREATH  = 7,
    EVENT_SONAR_BOMB            = 8,
    EVENT_SONIC_FIREBALL        = 9,

    // Heroic
    EVENT_SUMMON_FIEND          = 11,
    EVENT_DESTROY_SHIELD        = 12,

    // Reverbrating Flame
    EVENT_SUMMON_FLAME          = 14,
    EVENT_CHECK_TARGET          = 15
};

enum Action
{
    ACTION_SONIC_BREATH_CHANNEL
};

enum Say
{
    SAY_AGGRO,
    SAY_ROARING_FLAME_WARNING,
    SAY_SEARING_FLAME,
    SAY_SLAY,
    SAY_AIR_PHASE,
    SAY_DEATH
};

// ToDo: Convert this to Creature Text
enum ScriptTexts
{
    SAY_EVENT                     = -1851029
};

enum Phase
{
    PHASE_GROUND    = 1,
    PHASE_AIR       = 2
};

enum GUIDHolder
{
    GUID_SONIC_BREATH,
    GUID_DEVASTATION_TARGET,
    GUID_ROARING_BREATH_CHANNEL_TARGET,
    MAX_GUIDS
};

namespace Atramedes
{
    float const PositionZ[2] = { 75.4533f, 100.866f };

    Position MakeHeightForPhase(Position pos, Phase const phase) { pos.m_positionZ = PositionZ[phase == PHASE_GROUND ? 0 : 1]; return pos; }

    bool IsOnGround(Position const pos) { return pos.m_positionZ < (PositionZ[0] + 5.f); }

    Player* FindPlayerWithHighestSound(Creature* me)
    {
        std::list<Player*> players = me->GetNearestPlayersList(100.f);

        Player* player = NULL;
        int32 sound = 0;

        for (std::list<Player*>::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            if ((*itr)->GetPower(POWER_ALTERNATE_POWER) >= sound)
            {
                if ((*itr)->isGameMaster())
                    continue;

                sound  = (*itr)->GetPower(POWER_ALTERNATE_POWER);
                player = (*itr);
            }

        return player;
    }
}

using namespace Atramedes;

#define SONAR_PULSE_COUNT RAID_MODE(4, 4, 7, 7)

class boss_atramedes : public CreatureScript
{
public:
    boss_atramedes() : CreatureScript("boss_atramedes") { }

    struct boss_atramedesAI : public BossAI
    {
        boss_atramedesAI(Creature* creature) : BossAI(creature, DATA_ATRAMEDES)
        {
            memset(&GuidCache, 0, sizeof(GuidCache));
        }

        Phase phase;
        uint64 GuidCache[MAX_GUIDS];
        uint8 sonarPulseCount;
        std::set<uint64> devastationTargets;

        void Reset()
        {
            Cleanup();

            memset(&GuidCache, 0, sizeof(GuidCache));
            sonarPulseCount = 0;
            devastationTargets.clear();

            me->RemoveAurasDueToSpell(SPELL_SOUND_BAR);
            me->SetDisableGravity(false);

            if (!IsOnGround(*me))
                me->GetMotionMaster()->MoveLand(0, me->GetHomePosition());

            phase = PHASE_GROUND;
            _Reset();
        }

        void EnterPhase(Phase const newPhase)
        {
            events.CancelEventGroup(PHASE_GROUND);
            events.CancelEventGroup(PHASE_AIR);

            phase = newPhase;

            if (phase == PHASE_GROUND)
            {
                if (Creature* reverbratingFlame = me->GetCreature(*me, GuidCache[GUID_ROARING_BREATH_CHANNEL_TARGET]))
                {
                    reverbratingFlame->RemoveAllAuras();
                    reverbratingFlame->DespawnOrUnsummon();
                    GuidCache[GUID_ROARING_BREATH_CHANNEL_TARGET] = 0;
                    // me->InterruptNonMeleeSpells(false, SPELL_ROARING_FLAME_BREATH_CHAN);
                }

                /*
                if (!IsOnGround(*me))
                    me->GetMotionMaster()->MoveLand(1, MakeHeightForPhase(*me, PHASE_GROUND), 10.f);
                    */

                me->SetDisableGravity(false);

                events.ScheduleEvent(EVENT_MODULATION,     15000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_SONAR_PULSE,    27000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_SONIC_BREATH,   5000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_SEARING_FLAMES, 70000, PHASE_GROUND);
            }
            else
            {
                Talk(SAY_AIR_PHASE);
                me->SetDisableGravity(true);
                me->GetMotionMaster()->MoveTakeoff(1, MakeHeightForPhase(*me, PHASE_AIR));

                events.ScheduleEvent(EVENT_ROARING_FLAME_BREATH, 10000, PHASE_AIR);
                events.ScheduleEvent(EVENT_SONAR_BOMB,           50000, PHASE_AIR);
                events.ScheduleEvent(EVENT_SONIC_FIREBALL,       25000, PHASE_AIR);
            }

            //events.ScheduleEvent(EVENT_SWITCH_PHASE, phase == PHASE_GROUND ? 80000 : 40000, phase);
            events.ScheduleEvent(EVENT_SWITCH_PHASE, phase == PHASE_GROUND ? 3000 : 40000, phase);
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetBossState(DATA_ATRAMEDES, IN_PROGRESS);

            /*
            if (!instance->CheckRequiredBosses(DATA_ATRAMEDES))
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            */

            AddEncounterFrame();

            Talk(SAY_AGGRO);
            DoCast(SPELL_SOUND_BAR);

            // events.ScheduleEvent(EVENT_DEVASTATION, 1000);
            EnterPhase(PHASE_GROUND);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SWITCH_PHASE:
                    EnterPhase(phase == PHASE_GROUND ? PHASE_AIR : PHASE_GROUND);
                    return;
                case EVENT_DEVASTATION:
                    if (!devastationTargets.empty())
                    {
                        if (Player* player = me->GetPlayer(*me, *devastationTargets.begin()))
                            DoCast(player, SPELL_DEVASTATION);

                        devastationTargets.erase(devastationTargets.begin());
                    }
                    events.ScheduleEvent(EVENT_DEVASTATION, 1000);
                    break;

                    // Ground Phase
                case EVENT_MODULATION:
                    DoCast(SPELL_MODULATION);
                    events.ScheduleEvent(EVENT_MODULATION, 20000, PHASE_GROUND);
                    break;
                case EVENT_SONAR_PULSE:
                    sonarPulseCount = 0;
                    DoCast(SPELL_SONAR_PULSE);
                    events.ScheduleEvent(EVENT_SONAR_PULSE, 50000, PHASE_GROUND);
                    break;
                case EVENT_SONIC_BREATH:
                    GuidCache[GUID_SONIC_BREATH] = 0;
                    DoCast(SPELL_SONIC_BREATH);
                    events.ScheduleEvent(EVENT_SONIC_BREATH, 50000, PHASE_GROUND);
                    break;
                case EVENT_SONIC_BREATH_CHANNEL:
                    TalkWithDelay(2000, SAY_SEARING_FLAME);
                    DoCast(SPELL_SONIC_BREATH_CHANNEL);
                    break;
                case EVENT_SEARING_FLAMES:
                    Talk(SAY_ROARING_FLAME_WARNING, me->GetGUID());
                    DoCast(SPELL_SEARING_FLAME);
                    events.ScheduleEvent(EVENT_SONAR_PULSE, 55000, PHASE_GROUND);
                    break;

                    // Air Phase
                case EVENT_ROARING_FLAME_BREATH:
                    me->MonsterSay("Roaring Flame Breath");
                    if (!me->GetCreature(*me, GuidCache[GUID_ROARING_BREATH_CHANNEL_TARGET]))
                        if (Player* target = FindPlayerWithHighestSound(me))
                            DoCast(target, SPELL_ROARING_FLAME_BREATH);

                    events.ScheduleEvent(EVENT_ROARING_FLAME_BREATH, 4000, PHASE_AIR);
                    break;
                case EVENT_SONAR_BOMB:
                    {
                        std::list<Player*> players = me->GetNearestPlayersList(100.f);
                        for (uint8 i = 0; i < RAID_MODE(4, 10, 5, 12); ++i)
                        {
                            if (players.empty())
                                break;

                            std::list<Player*>::const_iterator itr = players.begin();
                            std::advance(itr, urand(0, players.size() - 1));

                            DoCast(*itr, SPELL_SONAR_BOMB, true);
                            players.remove(*itr);
                        }
                    }
                    events.ScheduleEvent(EVENT_SONAR_BOMB, 5000, PHASE_AIR);
                    break;
                case EVENT_SONIC_FIREBALL:
                    // ToDo
                    events.ScheduleEvent(EVENT_SONIC_FIREBALL, 55000, PHASE_AIR);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            if (id == GUID_DEVASTATION_TARGET)
            {
                devastationTargets.insert(guid);
                return;
            }

            if (id < MAX_GUIDS)
                GuidCache[id] = guid;
        }

        uint64 GetGUID(int32 id = 0) const
        {
            if (id >= MAX_GUIDS)
                return 0;

            return GuidCache[id];
        }

        uint32 GetData(uint32 type) const
        {
            /*
            switch (type)
            {
            case DATA_SONAR_PULSE_COUNT:
                return sonarPulseCount < 7 ? ++sonarPulseCount : 0;
            }
            */

            return 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_SONIC_BREATH_CHANNEL:
                events.DelayEvents(1000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_SONIC_BREATH_CHANNEL, 200, PHASE_GROUND);
                break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            Cleanup();
            _JustDied();
        }

        void Cleanup()
        {
            if (Creature* reverbratingFlame = me->GetCreature(*me, GuidCache[GUID_ROARING_BREATH_CHANNEL_TARGET]))
            {
                reverbratingFlame->RemoveAllAuras();
                reverbratingFlame->DespawnOrUnsummon();
                GuidCache[GUID_ROARING_BREATH_CHANNEL_TARGET] = 0;
            }

            me->DespawnCreaturesInArea(NPC_SONAR_PULSE);
            me->DespawnCreaturesInArea(NPC_ROARING_FLAMES);
            me->DespawnCreaturesInArea(NPC_REVERBRATING_FLAME_DAMAGE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_atramedesAI(creature);
    }
};

class npc_tracking_flames : public CreatureScript
{
public:
    npc_tracking_flames() : CreatureScript("npc_tracking_flames") { }

    struct npc_tracking_flamesAI : public ScriptedAI
    {
        npc_tracking_flamesAI(Creature* creature) : ScriptedAI(creature), SonicBreathChannelSent(false) {}

        bool SonicBreathChannelSent;

        void Reset()
        {
            me->DespawnOrUnsummon(17000);
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (SonicBreathChannelSent)
                return;

            SonicBreathChannelSent = true;

            me->GetMotionMaster()->MoveFollow(summoner, 0, 0);

            if (InstanceScript* instance = me->GetInstanceScript())
                if (Creature* atramedes = me->GetCreature(*me, instance->GetData64(BOSS_ATRAMEDES)))
                {
                    atramedes->AI()->SetGUID(me->GetGUID(), GUID_SONIC_BREATH);
                    atramedes->AI()->DoAction(ACTION_SONIC_BREATH_CHANNEL);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tracking_flamesAI (creature);
    }
};

class npc_sonar_pulse : public CreatureScript
{
public:
    npc_sonar_pulse() : CreatureScript("npc_sonar_pulse") { }

    struct npc_sonar_pulseAI : public ScriptedAI
    {
        npc_sonar_pulseAI(Creature* creature) : ScriptedAI(creature), intialized(false) {}

        Position targetPosition;
        bool intialized;

        void Reset()
        {
            me->DespawnOrUnsummon(30000);
        }

        void UpdateAI(uint32 diff)
        {
            if (intialized)
                if (!me->isMoving())
                    me->GetMotionMaster()->MovePoint(0, targetPosition);
                else if (me->GetDistance(targetPosition) < 1.f)
                    me->DespawnOrUnsummon();
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (InstanceScript* instance = me->GetInstanceScript())
                if (Creature* atramedes = me->GetCreature(*me, instance->GetData64(BOSS_ATRAMEDES)))
                {
                    Position pos = *atramedes;
                    atramedes->MovePosition(pos, -20.f, 0);

                    me->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation());
                    me->DestroyForNearbyPlayers();

                    me->SetOrientation(atramedes->GetOrientation());

                    pos = *me;
                    me->MovePosition(pos, 50.f, -0.5f + ((1 / SONAR_PULSE_COUNT) * atramedes->AI()->GetData(DATA_SONAR_PULSE_COUNT)));

                    targetPosition = pos;
                    intialized = true;
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sonar_pulseAI (creature);
    }
};

class npc_reverbrating_flame : public CreatureScript
{
public:
    npc_reverbrating_flame() : CreatureScript("npc_reverbrating_flame") { }

    struct npc_reverbrating_flameAI : public ScriptedAI
    {
        npc_reverbrating_flameAI(Creature* creature) : ScriptedAI(creature), target(0), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;
        EventMap events;
        uint64 target;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_CHECK_TARGET, 2000);
            events.ScheduleEvent(EVENT_SUMMON_FLAME, 4000);
        }

        void ChangeTargetTo(Unit* newTarget)
        {
            if (Player* player = me->GetPlayer(*me, target))
                player->RemoveAurasDueToSpell(SPELL_TRACKING);

            me->RemoveAurasDueToSpell(SPELL_TRACKING);

            DoCast(newTarget, SPELL_TRACKING, true);
            target = newTarget->GetGUID();

            me->RemoveAura(SPELL_BUILDING_SPEED_EFFECT);
            me->GetMotionMaster()->MoveFollow(newTarget, 0, 0);

            if (Creature* atramedes = me->GetCreature(*me, instance->GetData64(BOSS_ATRAMEDES)))
                atramedes->CastSpell(me, SPELL_ROARING_FLAME_BREATH_CHAN);
        }

        void UpdateAI(uint32 diff)
        {
            UpdateVictim();
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SUMMON_FLAME:
                    DoCast(SPELL_ROARING_FLAME_SUMMON);
                    events.ScheduleEvent(EVENT_SUMMON_FLAME, 1200);
                    break;
                case EVENT_CHECK_TARGET:
                    {
                        if (target)
                            if (Player* player = me->GetPlayer(*me, target))
                            {
                                if (player->isDead())
                                    target = 0;
                                else
                                    me->GetMotionMaster()->MoveFollow(player, 0, 0);
                            }
                            else
                                target = 0;

                        if (!target)
                            if (Player* newTarget = FindPlayerWithHighestSound(me))
                                ChangeTargetTo(newTarget);
                    }
                    events.ScheduleEvent(EVENT_CHECK_TARGET, 2000);
                    break;
                }
            }
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (target)
                return;

            Reset();
            ChangeTargetTo(summoner);

            if (Creature* atramedes = me->GetCreature(*me, instance->GetData64(BOSS_ATRAMEDES)))
            {
                atramedes->AI()->SetGUID(me->GetGUID(), GUID_ROARING_BREATH_CHANNEL_TARGET);
                atramedes->CastSpell(me, SPELL_ROARING_FLAME_BREATH_CHAN);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_reverbrating_flameAI (creature);
    }
};

// 88824 Sound Bar
class spell_sonar_bar : public SpellScriptLoader
{
public:
    spell_sonar_bar() : SpellScriptLoader("spell_sonar_bar") {}

    class spell_sonar_bar_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sonar_bar_AuraScript);

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (Unit* target = GetTarget())
                if (target->GetMapId() == MAPID_BLACKWING_DESCENT && target->isInCombat())
                {
                    if (target->GetPower(POWER_ALTERNATE_POWER) >= 100)
                        if (InstanceScript* instance = target->GetInstanceScript())
                            if (Creature* atramedes = target->GetCreature(*target, instance->GetData64(BOSS_ATRAMEDES)))
                                atramedes->AI()->SetGUID(target->GetGUID(), GUID_DEVASTATION_TARGET);

                    return;
                }

            Remove(AURA_REMOVE_BY_DEFAULT);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sonar_bar_AuraScript::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sonar_bar_AuraScript();
    }
};

// 78098 Sonic Breath
class spell_sonic_breath : public SpellScriptLoader
{
public:
    spell_sonic_breath() : SpellScriptLoader("spell_sonic_breath") {}

    class spell_sonic_breath_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sonic_breath_AuraScript);

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (Unit* owner = GetUnitOwner())
                if (Creature* me = owner->ToCreature())
                    if (Creature* target = me->GetCreature(*me, me->AI()->GetGUID(GUID_SONIC_BREATH)))
                        me->SetFacingToObject(target);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sonic_breath_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sonic_breath_AuraScript();
    }
};

uint16 const times[16] =
{
    0, 10000, 10000, 5000, 8000, 1100, 5000, 7500,
    6500, 9000, 4000, 5000, 7000, 7000, 6000, 4000
};

uint16 const adds[8] =
{
    43119, 43128, 43130, 43122, 43127, 43125, 43129, 43126
};

class npc_atramedes_intro_event : public CreatureScript
{
public:
    npc_atramedes_intro_event() : CreatureScript("npc_atramedes_intro_event") { }

    struct npc_atramedes_intro_eventAI : public ScriptedAI
    {
        npc_atramedes_intro_eventAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            maloriak = creature;           
        }

        InstanceScript* instance;
        uint32 timer;
        uint8 eventStep;

        Creature* nefarian;
        Creature* atramedes;
        Creature* maloriak;

        bool eventProcessed;

        void Reset()
        {
            timer = 1000;
            eventStep = 0;
        };

        void UpdateAI(uint32 diff) 
        {
            if (eventStep == 0 || !me->isAlive())
                return;

            if (timer <= diff)
            {
                switch (eventStep)
                {
                    // Nefarian
                case 1:
                    Say(nefarian);
                    break;
                case 3:
                    Say(nefarian);
                    break;
                case 9:
                case 10:
                case 12:
                case 13:
                case 14:
                    Say(nefarian);
                    break;

                    // Maloriak
                case 2:
                case 4:
                case 6:
                case 11:
                case 15:
                    Say(maloriak);
                    break;
                case 5:
                    Say(maloriak);
                    break;
                case 7:
                    DoCast(atramedes, SPELL_MORPH);
                    Say(maloriak);
                    break;
                case 8:
                    maloriak->AddAura(SPELL_BLIND_WHELP, atramedes);
                    Say(maloriak);
                    break;

                    // Both
                case 16:
                    atramedes->DespawnOrUnsummon();
                    nefarian->DespawnOrUnsummon();
                    me->DespawnCreaturesInArea(NPC_MEMORY_FOG, 150.f);
                    me->DespawnCreaturesInArea(NPC_NEFARIUS_THORNE, 150.f);
                    // Despawn self
                    maloriak->DespawnOrUnsummon();
                    break;
                }

                timer = times[eventStep];

                if (eventStep < 16)
                    eventStep++;

            } else timer -= diff;
        }

        void DoAction(int32 action)
        {
            if (eventStep != 0 || !me->isAlive())
                return;

            if (atramedes = me->GetCreature(*me,instance->GetData64(NPC_PRE_ATRAMEDES)))
            {
                eventStep = 1;
                nefarian = me->GetCreature(*me,instance->GetData64(NPC_PRE_NEFARIAN));
                maloriak = me;
            }
        }

        void Say(Creature* cr)
        {
            //DoScriptText(SAY_EVENT - eventStep, cr);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_atramedes_intro_eventAI(creature);
    }
};


class at_atramedes_intro : public AreaTriggerScript
{
public:
    at_atramedes_intro() : AreaTriggerScript("at_atramedes_intro")
    {
        activated = false;
    }

    bool activated;

    bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/)
    {
        if (activated)
            return false;

        if (!player->isGameMaster())
            if (InstanceScript* instance = player->GetInstanceScript())
                if (Creature* stalker = player->GetCreature(*player, instance->GetData64(NPC_PRE_MALORIAK)))
                {
                    activated = true;
                    stalker->AI()->DoAction(0);
                    return true;
                }

         return false;
    }
};

void AddSC_boss_atramedes()
{
    new boss_atramedes();
    new npc_tracking_flames();
    new npc_sonar_pulse();
    new npc_reverbrating_flame();
    new spell_sonar_bar();
    new spell_sonic_breath();
    new npc_atramedes_intro_event();
    new at_atramedes_intro();
}
