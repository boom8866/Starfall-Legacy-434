/*
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ScriptPCH.h"
#include "the_stonecore.h"
#include "Vehicle.h"
#include "MoveSplineInit.h"

enum Spells
{
    // High Priestess Azil spells
    SPELL_ENERGY_SHIELD                 = 82858,
    SPELL_CURSE_OF_BLOOD                = 79345,
    SPELL_FORCE_GRIP                    = 79351,
    SPELL_SUMMON_GRAVITY_WELL           = 79340,
    SPELL_EARTH_FURY_ENERGY_SHIELD_N    = 79050,
    SPELL_EARTH_FURY_ENERGY_SHIELD_H    = 92667,

    // Gravity Well
    SPELL_GRAVITY_WELL_VISUAL       = 79245,
    SPELL_GRAVITY_WELL_AURA_DAMAGE  = 79244,
    SPELL_GRAVITY_WELL_AURA_PULL    = 79333,
    SPELL_GRAVITY_WELL_DAMAGE       = 79249,
    SPELL_GRAVITY_WELL_PULL         = 79332,

    // Fury of Earth phase
    SPELL_EARTH_FURY_CASTING_VISUAL = 79002,
    SPELL_SEISMIC_SHARD_SUMMON_1    = 86860,
    SPELL_SEISMIC_SHARD_SUMMON_2    = 86858,
    SPELL_SEISMIC_SHARD_SUMMON_3    = 86856,
    SPELL_SEISMIC_SHARD_VISUAL      = 79009,
    SPELL_SEISMIC_SHARD_PREPARE     = 86862,
    SPELL_SEISMIC_SHARD_TARGETING   = 80511,
    SPELL_SEISMIC_SHARD_LAUNCH      = 79015,
    SPELL_SEISMIC_SHARD_MISSLE      = 79014,
    SPELL_EJECT_ALL_PASSENGERS      = 68576,

    // Add wave spells
    SPELL_SUMMON_WAVE_SOUTH         = 79200,
    SPELL_SUMMON_WAVE_WEST          = 79196,
    SPELL_SUMMON_ADD_SOUTH          = 79193,
    SPELL_SUMMON_ADD_WEST           = 79199,

    // Force Grip
    SPELL_FORCE_GRIP_SCRIPT         = 79354,
    SPELL_FORCE_GRIP_SMASH          = 79359,
    SPELL_FORCE_GRIP_SMASH_SCRIPT   = 79357,
    SPELL_FORCE_GRIP_DAMAGE_N       = 79358,
    SPELL_FORCE_GRIP_DAMAGE_H       = 92664
};

enum Texts
{
    SAY_AGGRO = 0,
    SAY_PHASE_TWO,
    SAY_SLAY,
    SAY_DEATH
};

enum Events
{
    EVENT_INTRO_MOVE = 1,
    EVENT_CURSE_OF_BLOOD,
    EVENT_FORCE_GRIP,
    EVENT_SUMMON_GRAVITY_WELL,
    EVENT_ENERGY_SHIELD,
    EVENT_EARTH_FURY,
    EVENT_SUMMON_WAVE_SOUTH,
    EVENT_SUMMON_WAVE_WEST,
    EVENT_GRAVITY_WELL_AURA_DAMAGE,
    EVENT_GRAVITY_WELL_AURA_PULL,

    // Phase 2: Fury of Earth
    EVENT_EARTH_FURY_FLY_UP,
    EVENT_EARTH_FURY_FLY_ABOVE_PLATFORM,
    EVENT_EARTH_FURY_CHECK_SEAT0,
    EVENT_EARTH_FURY_LAUNCH_SHARD,
    EVENT_EARTH_FURY_FLY_DOWN,
    EVENT_START_ATTACK,

    EVENT_LAUNCH,
    EVENT_SEISMIC_SHARD_MOUNT,

    EVENT_FORCE_GRIP_SMASH,
    EVENT_APPLY_IMMUNITY,

    EVENT_START_TIMED_ACHIEVEMENT,
    EVENT_STOP_TIMED_ACHIEVEMENT
};

enum EventGroups
{
    EVENT_GROUP_PHASE_ONE,
    EVENT_GROUP_ADDS
};

enum Points
{
    POINT_NONE,

    POINT_INTRO_MOVE,
    POINT_FLY_UP,
    POINT_ABOVE_PLATFORM,
    POINT_PLATFORM,
    POINT_GROUND
};

enum actionId
{
    ACTION_HANDLE_ACHIEVEMENT   = 1
};

enum achievementId
{
    ACHIEVEMENT_ENTRY_ROTTEN_TO_THE_CORE    = 5287
};

Position const GroundPos = { 1331.01f, 988.737f, 207.871f };
Position const AbovePlatformPos = { 1338.04f, 962.615f, 214.18f };

class boss_high_priestess_azil : public CreatureScript
{
public:
    boss_high_priestess_azil() : CreatureScript("boss_high_priestess_azil")
    {
    }

    struct boss_high_priestess_azilAI : public BossAI
    {
        boss_high_priestess_azilAI(Creature* creature) : BossAI(creature, DATA_HIGH_PRIESTESS_AZIL), vehicle(creature->GetVehicleKit())
        {
            ASSERT(vehicle);
        }

        Vehicle* vehicle;

        void OnCharmed(bool apply)
        {
        }

        void RemoveAllFollowers()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_DEVOUT_FOLLOWER_N, 600.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if (!(*iter)->ToTempSummon())
                    continue;

                (*iter)->DespawnOrUnsummon(10000);
                (*iter)->AI()->EnterEvadeMode();
            }
        }

        void JustReachedHome()
        {
            instance->SetBossState(DATA_HIGH_PRIESTESS_AZIL, FAIL);
            _JustReachedHome();
        }

        void Reset()
        {
            _Reset();
            RemoveAllFollowers();
            RemoveEncounterFrame();
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*victim*/)
        {
            _EnterCombat();
            AddEncounterFrame();
            DoCast(SPELL_ENERGY_SHIELD);
            Talk(SAY_AGGRO);

            events.ScheduleEvent(EVENT_INTRO_MOVE, 2000);
            events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, 6000, EVENT_GROUP_PHASE_ONE);
            events.ScheduleEvent(EVENT_FORCE_GRIP, urand(8000, 10000), EVENT_GROUP_PHASE_ONE);
            events.ScheduleEvent(EVENT_SUMMON_GRAVITY_WELL, 16000, EVENT_GROUP_PHASE_ONE);
            events.ScheduleEvent(EVENT_ENERGY_SHIELD, urand(35000, 36000));
            events.ScheduleEvent(EVENT_SUMMON_WAVE_SOUTH, 0);
            events.ScheduleEvent(EVENT_SUMMON_WAVE_WEST, 40000);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            countDevoutKills = 0;
            events.ScheduleEvent(EVENT_START_TIMED_ACHIEVEMENT, 1);
        }

        void JustDied(Unit* killer)
        {
            Talk(SAY_DEATH);
            RemoveEncounterFrame();
            _JustDied();
            _FinishDungeon();
            RemoveAllFollowers();
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER && roll_chance_i(75))
                Talk(SAY_SLAY);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE && id != POINT_INTRO_MOVE && type != EFFECT_MOTION_TYPE)
                return;

            switch (id)
            {
                case POINT_INTRO_MOVE:
                    me->RemoveAurasDueToSpell(SPELL_ENERGY_SHIELD);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                case POINT_FLY_UP:
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    events.ScheduleEvent(EVENT_EARTH_FURY_FLY_ABOVE_PLATFORM, 850);
                    break;
                case POINT_ABOVE_PLATFORM:
                    me->SetFacingTo(5.218534f);
                    DoCast(SPELL_EARTH_FURY_CASTING_VISUAL);
                    DoCast(SPELL_SEISMIC_SHARD_SUMMON_1);
                    DoCast(SPELL_SEISMIC_SHARD_SUMMON_2);
                    DoCast(SPELL_SEISMIC_SHARD_SUMMON_3);
                    events.ScheduleEvent(EVENT_EARTH_FURY_CHECK_SEAT0, 6700);
                    break;
                case POINT_GROUND:
                    DoCast(SPELL_EJECT_ALL_PASSENGERS);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->SetReactState(REACT_AGGRESSIVE);
                    // Find more sniffs to correct these timers, this was copied from Reset() void.
                    events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, 6000, EVENT_GROUP_PHASE_ONE);
                    events.ScheduleEvent(EVENT_FORCE_GRIP, urand(8000, 10000), EVENT_GROUP_PHASE_ONE);
                    events.ScheduleEvent(EVENT_SUMMON_GRAVITY_WELL, 7000, EVENT_GROUP_PHASE_ONE);
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

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INTRO_MOVE:
                        me->GetMotionMaster()->MoveJump(GroundPos, 8.5f, 12.5f, POINT_INTRO_MOVE);
                        break;
                    case EVENT_CURSE_OF_BLOOD:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_CURSE_OF_BLOOD);
                        events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, urand(13000, 15000), EVENT_GROUP_PHASE_ONE);
                        break;
                    case EVENT_FORCE_GRIP:
                        me->StopMoving();
                        DoCastVictim(SPELL_FORCE_GRIP);
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                        events.ScheduleEvent(EVENT_APPLY_IMMUNITY, 1500);
                        events.ScheduleEvent(EVENT_CURSE_OF_BLOOD, urand(13000, 15000), EVENT_GROUP_PHASE_ONE);
                        break;
                    case EVENT_APPLY_IMMUNITY:
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                        break;
                    case EVENT_SUMMON_GRAVITY_WELL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_SUMMON_GRAVITY_WELL);
                        events.ScheduleEvent(EVENT_SUMMON_GRAVITY_WELL, urand(8000, 12500), EVENT_GROUP_PHASE_ONE);
                        break;

                    case EVENT_ENERGY_SHIELD:
                        events.CancelEventGroup(EVENT_GROUP_PHASE_ONE);
                        DoCast(SPELL_EARTH_FURY_ENERGY_SHIELD_N);
                        events.ScheduleEvent(EVENT_EARTH_FURY, 0);
                        break;
                    case EVENT_EARTH_FURY:
                        countSeismicShard = 3;
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFacingTo(5.862942f);
                        events.ScheduleEvent(EVENT_EARTH_FURY_FLY_UP, 1600);
                        break;
                    case EVENT_EARTH_FURY_FLY_UP:
                        Talk(SAY_PHASE_TWO);
                        me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 8, 12.5f, 8.0f, POINT_FLY_UP);
                        me->SetReactState(REACT_PASSIVE);
                        events.CancelEvent(EVENT_FORCE_GRIP);
                        events.CancelEvent(EVENT_SUMMON_GRAVITY_WELL);
                        events.CancelEvent(EVENT_CURSE_OF_BLOOD);
                        break;
                    case EVENT_EARTH_FURY_FLY_ABOVE_PLATFORM:
                        me->GetMotionMaster()->MoveJump(AbovePlatformPos, 15.0f, 8.5f, POINT_ABOVE_PLATFORM);
                        break;
                    case EVENT_EARTH_FURY_CHECK_SEAT0:
                    {
                        if (vehicle)
                        {
                            Unit* passenger = vehicle->GetPassenger(0);
                            if (!passenger)
                                DoCast(SPELL_SEISMIC_SHARD_PREPARE);
                        }
                        events.ScheduleEvent(EVENT_EARTH_FURY_LAUNCH_SHARD, 1800);
                        break;
                    }
                    case EVENT_EARTH_FURY_LAUNCH_SHARD:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                        {
                            me->SetFacingToObject(target);
                            DoCast(target, SPELL_SEISMIC_SHARD_TARGETING);
                            DoCast(SPELL_SEISMIC_SHARD_LAUNCH);
                            countSeismicShard -= 1;
                        }
                        events.ScheduleEvent(countSeismicShard > 0 ? EVENT_EARTH_FURY_CHECK_SEAT0 : EVENT_EARTH_FURY_FLY_DOWN, 6000);
                        break;
                    case EVENT_EARTH_FURY_FLY_DOWN:
                        me->RemoveAurasDueToSpell(SPELL_EARTH_FURY_CASTING_VISUAL);
                        me->RemoveAurasDueToSpell(SPELL_EARTH_FURY_ENERGY_SHIELD_N);
                        me->RemoveAurasDueToSpell(SPELL_EARTH_FURY_ENERGY_SHIELD_H);
                        me->SetDisableGravity(false);
                        me->SetHover(false);
                        me->GetMotionMaster()->MoveJump(GroundPos, 12.5f, 12.5f, POINT_GROUND);
                        events.ScheduleEvent(EVENT_ENERGY_SHIELD, urand(45000, 60000));
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    case EVENT_SUMMON_WAVE_SOUTH:
                        if (Creature* worldtrigger = me->FindNearestCreature(NPC_WORLDTRIGGER, 300.0f))
                            worldtrigger->CastSpell(worldtrigger, SPELL_SUMMON_WAVE_SOUTH);
                        events.ScheduleEvent(EVENT_SUMMON_WAVE_SOUTH, 12000);
                        break;
                    case EVENT_SUMMON_WAVE_WEST:
                        if (Creature* worldtrigger = me->FindNearestCreature(NPC_WORLDTRIGGER, 300.0f))
                            worldtrigger->CastSpell(worldtrigger, SPELL_SUMMON_WAVE_WEST);
                        events.ScheduleEvent(EVENT_SUMMON_WAVE_WEST, 20000);
                        break;
                    case EVENT_START_TIMED_ACHIEVEMENT:
                        events.ScheduleEvent(EVENT_STOP_TIMED_ACHIEVEMENT, 10000);
                        events.CancelEvent(EVENT_START_TIMED_ACHIEVEMENT);
                        break;
                    case EVENT_STOP_TIMED_ACHIEVEMENT:
                        if (countDevoutKills >= 60)
                        {
                            if (instance && IsHeroic())
                                instance->DoCompleteAchievement(ACHIEVEMENT_ENTRY_ROTTEN_TO_THE_CORE);
                        }
                        events.CancelEvent(EVENT_STOP_TIMED_ACHIEVEMENT);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_HANDLE_ACHIEVEMENT:
                    countDevoutKills++;
                    break;
                default:
                    break;
            }
        }

    private:
        uint8 countSeismicShard;
        uint8 countDevoutKills;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_high_priestess_azilAI(creature);
    }
};

// 42428 - Devout Follower 
class npc_devout_follower : public CreatureScript
{
public:
    npc_devout_follower() : CreatureScript("npc_devout_follower")
    {
    }

    struct npc_devout_followerAI : public ScriptedAI
    {
        npc_devout_followerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (summoner->GetEntry() != NPC_WORLDTRIGGER)
                return;

            if (Unit* target = me->SelectNearestPlayer(500.0f))
            {
                me->AddThreat(target, 0.0f);
                me->SetInCombatWith(target);
                target->SetInCombatWith(me);
                DoStartMovement(target);
                me->Attack(target, true);
            }
            else
                me->GetMotionMaster()->MovePoint(0, 1320.08f, 997.83f, 208.37f, true);
        }

        void JustDied(Unit* /*victim*/)
        {
            if (Creature* azil = me->FindNearestCreature(BOSS_HIGH_PRIESTESS_AZIL, 300.0f, true))
                if (azil->isInCombat())
                    azil->AI()->DoAction(ACTION_HANDLE_ACHIEVEMENT);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_devout_followerAI(creature);
    }
};

// 42499 - Gravity Well
class npc_gravity_well : public CreatureScript
{
public:
    npc_gravity_well() : CreatureScript("npc_gravity_well")
    {
    }

    struct npc_gravity_wellAI : public ScriptedAI
    {
        npc_gravity_wellAI(Creature* creature) : ScriptedAI(creature)
        {
            DoCast(SPELL_GRAVITY_WELL_VISUAL);
            events.ScheduleEvent(EVENT_GRAVITY_WELL_AURA_DAMAGE, 3200);
            events.ScheduleEvent(EVENT_GRAVITY_WELL_AURA_PULL, 4500);
            if (!me->GetMap()->IsHeroic())
                me->DespawnOrUnsummon(23200);

            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetEntry() != NPC_DEVOUT_FOLLOWER_N && victim->GetEntry() != NPC_DEVOUT_FOLLOWER_H)
                return;

            if (!victim->GetMap()->IsHeroic())
                return;

            me->SetObjectScale(me->GetObjectScale() - 0.25f);
            if (me->GetObjectScale() <= 0.0f)
                me->DespawnOrUnsummon(1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GRAVITY_WELL_AURA_DAMAGE:
                        me->RemoveAurasDueToSpell(SPELL_GRAVITY_WELL_VISUAL);
                        DoCast(SPELL_GRAVITY_WELL_AURA_DAMAGE);
                        break;
                    case EVENT_GRAVITY_WELL_AURA_PULL:
                        DoCast(SPELL_GRAVITY_WELL_AURA_PULL);
                        break;
                    default:
                        break;
                }
            }
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gravity_wellAI(creature);
    }
};

// 42355 - Seismic Shard
class npc_seismic_shard : public CreatureScript
{
public:
    npc_seismic_shard() : CreatureScript("npc_seismic_shard")
    {
    }

    struct npc_seismic_shardAI : public ScriptedAI
    {
        npc_seismic_shardAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetDisableGravity(true);
            me->SetReactState(REACT_PASSIVE);
            me->AddAura(SPELL_SEISMIC_SHARD_VISUAL, me);
            Position pos;
            me->GetPosition(&pos);
            Movement::MoveSplineInit init(me);
            FillPath(pos, init.Path());
            init.SetFly();
            init.Launch();

            events.ScheduleEvent(EVENT_SEISMIC_SHARD_MOUNT, 2400);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SEISMIC_SHARD_MOUNT:
                        if (Creature* highPriestAzil = me->FindNearestCreature(BOSS_HIGH_PRIESTESS_AZIL, 300.0f, true))
                            if (Vehicle* vehicle = highPriestAzil->GetVehicleKit())
                                me->EnterVehicle(highPriestAzil, vehicle->GetNextEmptySeat(0, false)->first);
                        break;
                    default:
                        break;
                }
            }

        }

    private:
        void FillPath(Position const& pos, Movement::PointsArray& path)
        {
            G3D::Vector3 point;

            point.x = pos.GetPositionX();
            point.y = pos.GetPositionY();
            point.z = pos.GetPositionZ();

            point.x -= 1.0f;
            path.push_back(point);

            point.x += 1.0f;
            path.push_back(point);

            point.z += 25.0f;
            path.push_back(point);

            path.push_back(point);
        }

        InstanceScript* instance;
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_seismic_shardAI(creature);
    }
};

// 79200 - Summon Follower
class spell_summon_wave_south : public SpellScriptLoader
{
public:
    spell_summon_wave_south() : SpellScriptLoader("spell_summon_wave_south")
    {
    }

    class spell_summon_wave_south_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_summon_wave_south_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SUMMON_ADD_SOUTH))
                return false;
            return true;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                for (uint8 i = 0; i < 3; i++)
                    caster->CastSpell(caster, SPELL_SUMMON_ADD_SOUTH, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_summon_wave_south_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_summon_wave_south_SpellScript();
    }
};

// 79196 - Summon Follower
class spell_summon_wave_west : public SpellScriptLoader
{
public:
    spell_summon_wave_west() : SpellScriptLoader("spell_summon_wave_west")
    {
    }

    class spell_summon_wave_west_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_summon_wave_west_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SUMMON_ADD_WEST))
                return false;
            return true;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                for (uint8 i = 0; i < 10; i++)
                    caster->CastSpell(caster, SPELL_SUMMON_ADD_WEST, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_summon_wave_west_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_summon_wave_west_SpellScript();
    }
};

// 79251 - Gravity Well (casts damage spell on units within 10 yards)
class PlayerPetOrDevoutFollowerCheck
{
public:
    bool operator()(WorldObject* object) const
    {
        // Valid targets are players, pets and Devout Followers
        if (Creature* creature = object->ToCreature())
            return (!creature->ToPet() && (object->GetEntry() != NPC_DEVOUT_FOLLOWER_N && object->GetEntry() != NPC_DEVOUT_FOLLOWER_H));
        return (!object->ToPlayer());
    }
};

class spell_gravity_well_damage_nearby : public SpellScriptLoader
{
public:
    spell_gravity_well_damage_nearby() : SpellScriptLoader("spell_gravity_well_damage_nearby")
    {
    }

    class spell_gravity_well_damage_nearby_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gravity_well_damage_nearby_SpellScript);

        void SetRadiusMod()
        {
            GetSpell()->SetSpellValue(SPELLVALUE_RADIUS_MOD, int32(GetCaster()->GetObjectScale() * 10000 * 2 / 3));
        }

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            if (unitList.empty())
                return;

            unitList.remove_if(PlayerPetOrDevoutFollowerCheck());
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                    if (target->GetEntry() != BOSS_HIGH_PRIESTESS_AZIL && target->GetEntry() != 49624)
                        caster->CastSpell(target, SPELL_GRAVITY_WELL_DAMAGE, true);
            }
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_gravity_well_damage_nearby_SpellScript::SetRadiusMod);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gravity_well_damage_nearby_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY | TARGET_UNIT_SRC_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_gravity_well_damage_nearby_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gravity_well_damage_nearby_SpellScript();
    }
};

// 79249 - Gravity Well (damage)
class spell_gravity_well_damage : public SpellScriptLoader
{
public:
    spell_gravity_well_damage() : SpellScriptLoader("spell_gravity_well_damage")
    {
    }

    enum npcId
    {
        NPC_HIGH_PRIESTESS_AZIL_N   = 42333,
        NPC_HIGH_PRIESTESS_AZIL_H   = 49624
    };

    class spell_gravity_well_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gravity_well_damage_SpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!target || !caster)
                return;

            float distance = caster->GetDistance2d(target);
            if (target->GetEntry() == NPC_DEVOUT_FOLLOWER_N || target->GetEntry() == NPC_DEVOUT_FOLLOWER_H)
                SetHitDamage(int32(200000 - (1000 * distance))); //need more research on this formula, damage values from sniffs: 189264, 190318, 190478, 196134, 197672, 199735
            else
                SetHitDamage(int32(4000 - (200 * distance)));

            if (target->GetEntry() == NPC_HIGH_PRIESTESS_AZIL_N || target->GetEntry() == NPC_HIGH_PRIESTESS_AZIL_H)
                SetHitDamage(0);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gravity_well_damage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gravity_well_damage_SpellScript();
    }
};

// 79332 - Gravity Well (pull units within 10 yards)
class PulledRecentlyCheck
{

    enum npcId
    {
        NPC_HIGH_PRIESTESS_AZIL_N = 42333,
        NPC_HIGH_PRIESTESS_AZIL_H = 49624
    };

public:
    bool operator()(WorldObject* object) const
    {
        return ((object->ToUnit() && object->ToUnit()->HasAura(SPELL_GRAVITY_WELL_PULL)) || (object->ToCreature() && (object->ToCreature()->GetEntry() == NPC_HIGH_PRIESTESS_AZIL_H || object->ToCreature()->GetEntry() == NPC_HIGH_PRIESTESS_AZIL_N)));
    }
};

class spell_gravity_well_pull : public SpellScriptLoader
{
public:
    spell_gravity_well_pull() : SpellScriptLoader("spell_gravity_well_pull")
    {
    }

    class spell_gravity_well_pull_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gravity_well_pull_SpellScript);

        void SetRadiusMod()
        {
            GetSpell()->SetSpellValue(SPELLVALUE_RADIUS_MOD, int32(GetCaster()->GetObjectScale() * 10000 * 2 / 3));
        }

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            if (unitList.empty())
                return;

            unitList.remove_if(PulledRecentlyCheck());
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_gravity_well_pull_SpellScript::SetRadiusMod);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gravity_well_pull_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gravity_well_pull_SpellScript();
    }
};

// 86862 - Seismic Shard (forces target to cast 86863)
class spell_seismic_shard_prepare : public SpellScriptLoader
{
public:
    spell_seismic_shard_prepare() : SpellScriptLoader("spell_seismic_shard_prepare")
    {
    }

    class spell_seismic_shard_prepare_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_seismic_shard_prepare_SpellScript);

        void SetTarget(WorldObject*& target)
        {
            if (Unit* caster = GetCaster())
                if (Creature* shard = caster->FindNearestCreature(NPC_SEISMIC_SHARD, 100.0f))
                    target = shard;
        }

        void Register()
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_seismic_shard_prepare_SpellScript::SetTarget, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_seismic_shard_prepare_SpellScript();
    }
};

// 86863 - Seismic Shard (moves shard to seat 0)
class spell_seismic_shard_change_seat : public SpellScriptLoader
{
public:
    spell_seismic_shard_change_seat() : SpellScriptLoader("spell_seismic_shard_change_seat")
    {
    }

    class spell_seismic_shard_change_seat_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_seismic_shard_change_seat_SpellScript);

        void SetTarget(WorldObject*& target)
        {
            if (Unit* caster = GetCaster())
                if (Creature* azil = caster->FindNearestCreature(BOSS_HIGH_PRIESTESS_AZIL, 300.0f, true))
                    target = azil;
        }

        void ChangeSeat(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                caster->ExitVehicle();
                if (Unit* target = GetHitUnit())
                    if (target->IsVehicle())
                        caster->EnterVehicle(target, 0);
            }
        }

        void Register()
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_seismic_shard_change_seat_SpellScript::SetTarget, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_seismic_shard_change_seat_SpellScript::ChangeSeat, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_seismic_shard_change_seat_SpellScript();
    }
};

// 79015 - Seismic Shard (launches shard)
class spell_seismic_shard : public SpellScriptLoader
{
public:
    spell_seismic_shard() : SpellScriptLoader("spell_seismic_shard")
    {
    }

    class spell_seismic_shard_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_seismic_shard_SpellScript);

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit* hitUnit = GetHitUnit())
            {
                Creature* target = GetHitUnit()->ToCreature();
                if (!target)
                    return;

                target->ExitVehicle();
                if (DynamicObject* dynamicObject = GetCaster()->GetDynObject(SPELL_SEISMIC_SHARD_TARGETING))
                    target->CastSpell(dynamicObject->GetPositionX(), dynamicObject->GetPositionY(), dynamicObject->GetPositionZ(), SPELL_SEISMIC_SHARD_MISSLE, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_seismic_shard_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_seismic_shard_SpellScript();
    }
};

class spell_tsc_force_grip : public SpellScriptLoader
{
public:
    spell_tsc_force_grip() : SpellScriptLoader("spell_tsc_force_grip")
    {
    }

    class spell_tsc_force_grip_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_tsc_force_grip_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* player = GetOwner()->ToUnit())
                    player->EnterVehicle(caster, 3);
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(3))
                {
                    if (passenger->GetMap()->IsHeroic())
                        passenger->CastWithDelay(250, passenger, SPELL_FORCE_GRIP_DAMAGE_H, true);
                    else
                        passenger->CastWithDelay(250, passenger, SPELL_FORCE_GRIP_DAMAGE_N, true);

                    passenger->ExitVehicle();
                }
                else if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(4))
                {
                    if (passenger->GetMap()->IsHeroic())
                        passenger->CastWithDelay(250, passenger, SPELL_FORCE_GRIP_DAMAGE_H, true);
                    else
                        passenger->CastWithDelay(250, passenger, SPELL_FORCE_GRIP_DAMAGE_N, true);

                    passenger->ExitVehicle();
                }
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_tsc_force_grip_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_tsc_force_grip_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tsc_force_grip_AuraScript();
    }
};

void AddSC_boss_high_priestess_azil()
{
    new boss_high_priestess_azil();
    new npc_devout_follower();
    new npc_gravity_well();
    new npc_seismic_shard();
    new spell_summon_wave_south();
    new spell_summon_wave_west();
    new spell_gravity_well_damage_nearby();
    new spell_gravity_well_damage();
    new spell_gravity_well_pull();
    new spell_seismic_shard_prepare();
    new spell_seismic_shard_change_seat();
    new spell_seismic_shard();
    new spell_tsc_force_grip();
}
