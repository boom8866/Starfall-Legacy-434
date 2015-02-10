/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "ObjectAccessor.h"
#include "halls_of_origination.h"

enum Texts
{
    ANRAPHET_SAY_INTRO              = 0,
    ANRAPHET_SAY_AGGRO              = 1,
    ANRAPHET_SAY_OMEGA_STANCE       = 2,
    ANRAPHET_SAY_KILL               = 3,
    ANRAPHET_SAY_DEATH              = 4,

    BRANN_SAY_DOOR_INTRO            = 0,  // Right, let's go! Just need to input the final entry sequence into the door mechanism... and...
    BRANN_SAY_UNLOCK_DOOR           = 1,  // That did the trick! The control room should be right behind this... oh... wow...
    BRANN_SAY_TROGGS                = 2,  // What? This isn't the control room! There's another entire defense mechanism in place, and the blasted Rock Troggs broke into here somehow. Troggs. Why did it have to be Troggs!
    BRANN_SAY_THINK                 = 3,  // Ok, let me think a moment.
    BRANN_SAY_MIRRORS               = 4,  // Mirrors pointing all over the place.
    BRANN_SAY_ELEMENTALS            = 5,  // Four platforms with huge elementals.
    BRANN_SAY_GET_IT                = 6,  // I got it! I saw a tablet that mentioned this chamber. This is the Vault of Lights! Ok, simple enough. I need you adventurers to take out each of the four elementals to trigger the opening sequence for the far door!
    BRANN_1_ELEMENTAL_DEAD          = 7,  // One down!
    BRANN_2_ELEMENTAL_DEAD          = 8,  // Another one down! Just look at those light beams! They seem to be connecting to the far door!
    BRANN_3_ELEMENTAL_DEAD          = 9,  // One more elemental to go! The door is almost open!
    BRANN_4_ELEMENTAL_DEAD          = 10, // That''s it, you''ve done it! The vault door is opening! Now we can... oh, no!
    BRANN_SAY_ANRAPHET_DIED         = 11, // We''ve done it! The control room is breached!
    BRANN_SAY_MOMENT                = 12  // Here we go! Now this should only take a moment...
};

enum Events
{
    EVENT_BRANN_MOVE_INTRO          = 1,
    EVENT_BRANN_UNLOCK_DOOR         = 2,
    EVENT_BRANN_THINK               = 3,
    EVENT_BRANN_SET_ORIENTATION_1   = 4,
    EVENT_BRANN_SET_ORIENTATION_2   = 5,
    EVENT_BRANN_SET_ORIENTATION_3   = 6,
    EVENT_BRANN_SAY_ELEMENTALS      = 7,
    EVENT_BRANN_SAY_GET_IT          = 8,
    EVENT_BRANN_SET_ORIENTATION_4   = 9,
    EVENT_BRANN_OPEN_CONTROL_ROOM   = 10,

    EVENT_ANRAPHET_APPEAR           = 11,
    EVENT_ANRAPHET_ACTIVATE         = 12,
    EVENT_ANRAPHET_DESTROY          = 13,
    EVENT_ANRAPHET_READY            = 14,
    EVENT_ANRAPHET_NEMESIS_STRIKE   = 15,
    EVENT_ANRAPHET_ALPHA_BEAMS      = 16,
    EVENT_ANRAPHET_OMEGA_STANCE     = 17,
    EVENT_ANRAPHET_CRUMBLING_RUIN   = 18,
    EVENT_ANRAPHET_ACTIVATE_OMEGA   = 19,
    EVENT_ANRAPHET_INTRO_DONE       = 20,
};

enum Spells
{
    SPELL_DESTRUCTION_PROTOCOL          = 77437,
    SPELL_ALPHA_BEAMS                   = 76184,
    SPELL_ALPHA_BEAMS_BACK_CAST         = 76912,
    SPELL_CRUMBLING_RUIN                = 75609,
    SPELL_NEMESIS_STRIKE                = 75604,
    SPELL_OMEGA_STANCE_SUMMON           = 77106,
    SPELL_OMEGA_STANCE                  = 75622,
    SPELL_OMEGA_STANCE_SPIDER_TRIGGER   = 77121,
};

enum Phases
{
    PHASE_INTRO         = 1,
    PHASE_COMBAT        = 2,
};

enum Points
{
    POINT_ANRAPHET_ACTIVATE     = 0,
    MAX_BRANN_WAYPOINTS_INTRO   = 17
};

Position const AnraphetActivatePos = {-193.656f, 366.689f, 75.91001f, 3.138207f};

Position const BrannIntroWaypoint[MAX_BRANN_WAYPOINTS_INTRO] =
{
    {-429.583f,  367.019f,  89.79282f, 0.0f},
    {-409.9531f, 367.0469f, 89.81111f, 0.0f},
    {-397.8246f, 366.967f,  86.37722f, 0.0f},
    {-383.7813f, 366.8229f, 82.07919f, 0.0f},
    {-368.2604f, 366.7448f, 77.0984f,  0.0f},
    {-353.6458f, 366.4896f, 75.92504f, 0.0f},
    {-309.0608f, 366.7205f, 75.91345f, 0.0f},
    {-276.3303f, 367.0f,    75.92413f, 0.0f},
    {-246.5104f, 366.6389f, 75.87791f, 0.0f},
    {-202.0417f, 366.7517f, 75.92508f, 0.0f},
    {-187.6024f, 366.7656f, 76.23077f, 0.0f},
    {-155.0938f, 366.783f,  86.45834f, 0.0f},
    {-143.5694f, 366.8177f, 89.73354f, 0.0f},
    {-128.5608f, 366.8629f, 89.74199f, 0.0f},
    {-103.559f,  366.5938f, 89.79725f, 0.0f},
    {-71.58507f, 367.0278f, 89.77069f, 0.0f},
    {-35.04861f, 366.6563f, 89.77447f, 0.0f},
};

class boss_anraphet : public CreatureScript
{
public:
    boss_anraphet() : CreatureScript("boss_anraphet") { }

    struct boss_anraphetAI : public BossAI
    {
        boss_anraphetAI(Creature* creature) : BossAI(creature, DATA_ANRAPHET)
        {
            _introDone = false;
        }

        bool _introDone;

        void Reset()
        {
            _Reset();
            me->SetWalk(false);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_6);
            events.SetPhase(PHASE_INTRO);
            if (instance->GetData(DATA_DEAD_ELEMENTALS) == 4)
                me->SetHomePosition(AnraphetActivatePos);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (_introDone)
            {
                _EnterCombat();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 1);
                Talk(ANRAPHET_SAY_AGGRO);
                events.ScheduleEvent(EVENT_ANRAPHET_NEMESIS_STRIKE, 8000, 0, PHASE_COMBAT);
                events.ScheduleEvent(EVENT_ANRAPHET_ALPHA_BEAMS, 10000, 0, PHASE_COMBAT);
                events.ScheduleEvent(EVENT_ANRAPHET_OMEGA_STANCE, 35000, 0, PHASE_COMBAT);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CRUMBLING_RUIN);
            Talk(ANRAPHET_SAY_DEATH);

            if (Creature* brann = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_BRANN_0_GUID)))
                brann->AI()->DoAction(ACTION_ANRAPHET_DIED);

            summons.DespawnAll();
            me->DespawnCreaturesInArea(NPC_ALPHA_BEAM, 500.0f);
            _JustDied();
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(ANRAPHET_SAY_KILL);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SetBossState(DATA_ANRAPHET, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CRUMBLING_RUIN);
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            me->DespawnCreaturesInArea(NPC_ALPHA_BEAM, 500.0f);
            events.Reset();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_OMEGA_STANCE:
                    Position pos;
                    pos.Relocate(summon);
                    pos.m_positionZ = me->GetPositionZ() + 30.0f;
                    summon->NearTeleportTo(pos, false);
                    break;
                default:
                    break;
            }
            summons.Summon(summon);
        }

        void DoAction(int32 action)
        {
            if (action == ACTION_ANRAPHET_INTRO)
            {
                events.ScheduleEvent(EVENT_ANRAPHET_APPEAR, 10000, 0, PHASE_INTRO);
                me->SetSpeed(MOVE_RUN, 2.0f);
            }
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (point == POINT_ANRAPHET_ACTIVATE)
            {
                events.ScheduleEvent(EVENT_ANRAPHET_ACTIVATE, 1500, 0, PHASE_INTRO);
                me->SetHomePosition(AnraphetActivatePos);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)) && !UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ANRAPHET_APPEAR:
                        me->GetMotionMaster()->MovePoint(POINT_ANRAPHET_ACTIVATE, AnraphetActivatePos);
                        break;
                    case EVENT_ANRAPHET_ACTIVATE:
                        Talk(ANRAPHET_SAY_INTRO);
                        events.ScheduleEvent(EVENT_ANRAPHET_DESTROY, 11000, 0, PHASE_INTRO);
                        return;
                    case EVENT_ANRAPHET_DESTROY:
                        DoCastAOE(SPELL_DESTRUCTION_PROTOCOL);
                        events.ScheduleEvent(EVENT_ANRAPHET_READY, 6000, 0, PHASE_INTRO);
                        events.ScheduleEvent(EVENT_ANRAPHET_INTRO_DONE, 5900, 0, PHASE_INTRO);
                        break;
                    case EVENT_ANRAPHET_INTRO_DONE:
                        _introDone = true;
                        break;
                    case EVENT_ANRAPHET_READY:
                        events.SetPhase(PHASE_COMBAT);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    case EVENT_ANRAPHET_NEMESIS_STRIKE:
                        DoCastVictim(SPELL_NEMESIS_STRIKE);
                        events.ScheduleEvent(EVENT_ANRAPHET_NEMESIS_STRIKE, 21500, 0, PHASE_COMBAT);
                        break;
                    case EVENT_ANRAPHET_ALPHA_BEAMS:
                        DoCast(me, SPELL_ALPHA_BEAMS);
                        events.ScheduleEvent(EVENT_ANRAPHET_CRUMBLING_RUIN, 12500, 0, PHASE_COMBAT);
                        events.ScheduleEvent(EVENT_ANRAPHET_ALPHA_BEAMS, urand(40000, 45000), 0, PHASE_COMBAT);
                        break;
                    case EVENT_ANRAPHET_OMEGA_STANCE:
                        DoCast(me, SPELL_OMEGA_STANCE_SUMMON);
                        DoCast(me, SPELL_OMEGA_STANCE);
                        Talk(ANRAPHET_SAY_OMEGA_STANCE);
                        events.ScheduleEvent(EVENT_ANRAPHET_OMEGA_STANCE, urand(45000, 50000), 0, PHASE_COMBAT);
                        events.ScheduleEvent(EVENT_ANRAPHET_CRUMBLING_RUIN, 13000, 0, PHASE_COMBAT);
                        break;
                    case EVENT_ANRAPHET_CRUMBLING_RUIN:
                        DoCast(me, SPELL_CRUMBLING_RUIN);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetHallsOfOriginationAI<boss_anraphetAI>(creature);
    }
};

class npc_alpha_beam : public CreatureScript
{
    public:
        npc_alpha_beam() : CreatureScript("npc_alpha_beam") { }

        struct npc_alpha_beamAI : public ScriptedAI
        {
            npc_alpha_beamAI(Creature* creature) : ScriptedAI(creature), _instance(creature->GetInstanceScript())
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (Creature* anraphet = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_ANRAPHET_GUID)))
                    anraphet->CastSpell(me, SPELL_ALPHA_BEAMS_BACK_CAST);
            }

            void UpdateAI(uint32 diff)
            {
            }

            private:
                InstanceScript* _instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetHallsOfOriginationAI<npc_alpha_beamAI>(creature);
        }
};

class npc_brann_bronzebeard_anraphet : public CreatureScript
{
    public:
        npc_brann_bronzebeard_anraphet() : CreatureScript("npc_brann_bronzebeard_anraphet") { }

        enum questId
        {
            QUEST_PENETRATING_THEIR_DEFENSE = 28746
        };

        struct npc_brann_bronzebeard_anraphetAI : public CreatureAI
        {
            npc_brann_bronzebeard_anraphetAI(Creature* creature) : CreatureAI(creature), _currentPoint(0), _instance(creature->GetInstanceScript()) { }

            void sGossipSelect(Player* /*player*/, uint32 sender, uint32 action)
            {
                if (_instance->GetBossState(DATA_VAULT_OF_LIGHTS) == DONE)
                    return;

                if (me->GetCreatureTemplate()->GossipMenuId == sender && !action)
                {
                    _instance->SetBossState(DATA_VAULT_OF_LIGHTS, IN_PROGRESS);
                    _currentPoint = 0;
                    events.Reset();
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    me->SetWalk(false);
                    Talk(BRANN_SAY_DOOR_INTRO);
                    events.ScheduleEvent(EVENT_BRANN_UNLOCK_DOOR, 7500);
                }
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_ELEMENTAL_DIED:
                    {
                        uint32 dead = _instance->GetData(DATA_DEAD_ELEMENTALS);
                        Talk(BRANN_1_ELEMENTAL_DEAD + dead - 1);
                        if (dead == 4)
                        {
                            _instance->DoCastSpellOnPlayers(SPELL_VAULT_OF_LIGHTS_CREDIT);
                            if (Creature* anraphet = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_ANRAPHET_GUID)))
                                anraphet->AI()->DoAction(ACTION_ANRAPHET_INTRO);
                        }
                        break;
                    }
                    case ACTION_ANRAPHET_DIED:
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        events.ScheduleEvent(EVENT_BRANN_MOVE_INTRO, 1000);
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
                        case EVENT_BRANN_MOVE_INTRO:
                            if (_currentPoint < MAX_BRANN_WAYPOINTS_INTRO)
                                me->GetMotionMaster()->MovePoint(_currentPoint, BrannIntroWaypoint[_currentPoint]);
                            break;
                        case EVENT_BRANN_UNLOCK_DOOR:
                            Talk(BRANN_SAY_UNLOCK_DOOR);
                            _instance->SetBossState(DATA_VAULT_OF_LIGHTS, DONE);
                            _instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_VAULT_OF_LIGHTS_EVENT);
                            events.ScheduleEvent(EVENT_BRANN_MOVE_INTRO, 3500);
                            break;
                        case EVENT_BRANN_THINK:
                            Talk(BRANN_SAY_THINK);
                            events.ScheduleEvent(EVENT_BRANN_SET_ORIENTATION_1, 6000);
                            break;
                        case EVENT_BRANN_SET_ORIENTATION_1:
                            me->SetFacingTo(5.445427f);
                            Talk(BRANN_SAY_MIRRORS);
                            events.ScheduleEvent(EVENT_BRANN_SET_ORIENTATION_2, 1000);
                            break;
                        case EVENT_BRANN_SET_ORIENTATION_2:
                            me->SetFacingTo(0.6283185f);
                            events.ScheduleEvent(EVENT_BRANN_SET_ORIENTATION_3, 2500);
                            break;
                        case EVENT_BRANN_SET_ORIENTATION_3:
                            me->SetFacingTo(0.01745329f);
                            events.ScheduleEvent(EVENT_BRANN_SAY_ELEMENTALS, 200);
                            break;
                        case EVENT_BRANN_SAY_ELEMENTALS:
                            Talk(BRANN_SAY_ELEMENTALS);
                            events.ScheduleEvent(EVENT_BRANN_SAY_GET_IT, 3500);
                            break;
                        case EVENT_BRANN_SAY_GET_IT:
                            Talk(BRANN_SAY_GET_IT);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            break;
                        case EVENT_BRANN_SET_ORIENTATION_4:
                            me->SetFacingTo(3.141593f);
                            break;
                    }
                }
            }

            void CheckCompletion()
            {
                Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                if (!PlayerList.isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (i->getSource()->GetQuestStatus(QUEST_PENETRATING_THEIR_DEFENSE) == QUEST_STATUS_INCOMPLETE)
                            i->getSource()->CompleteQuest(QUEST_PENETRATING_THEIR_DEFENSE);
                    }
                }
            }

            void MovementInform(uint32 movementType, uint32 pointId)
            {
                if (movementType != POINT_MOTION_TYPE)
                    return;

                _currentPoint = pointId + 1;
                uint32 delay = 1;

                switch (pointId)
                {
                    case 0:
                        Talk(BRANN_SAY_TROGGS);
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        events.ScheduleEvent(EVENT_BRANN_THINK, 15000);
                        return;
                    case 1:
                        Talk(BRANN_SAY_ANRAPHET_DIED);
                        delay = 1000;
                        CheckCompletion();
                        break;
                    case 14:
                        Talk(BRANN_SAY_MOMENT);
                        delay = 2200;
                        break;
                    case 16:
                        events.ScheduleEvent(EVENT_BRANN_SET_ORIENTATION_4, 6000);
                        return;
                    default:
                        break;
                }

                events.ScheduleEvent(EVENT_BRANN_MOVE_INTRO, delay);
            }

        protected:
            EventMap events;
            uint32 _currentPoint;
            InstanceScript* _instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetHallsOfOriginationAI<npc_brann_bronzebeard_anraphetAI>(creature);
        }
};

class spell_anraphet_alpha_beams : public SpellScriptLoader
{
public:
    spell_anraphet_alpha_beams() : SpellScriptLoader("spell_anraphet_alpha_beams") { }

    class spell_anraphet_alpha_beams_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_anraphet_alpha_beams_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_anraphet_alpha_beams_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_anraphet_alpha_beams_SpellScript();
    }
};

class spell_anraphet_omega_stance_summon : public SpellScriptLoader
{
public:
    spell_anraphet_omega_stance_summon() : SpellScriptLoader("spell_anraphet_omega_stance_summon") { }

    class spell_anraphet_omega_stance_summon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_anraphet_omega_stance_summon_SpellScript);

        void ModDestHeight(SpellEffIndex /*effIndex*/)
        {
            Position offset = {0.0f, 0.0f, 30.0f, 0.0f};
            const_cast<WorldLocation*>(GetExplTargetDest())->RelocateOffset(offset);
            GetHitDest()->RelocateOffset(offset);
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_anraphet_omega_stance_summon_SpellScript::ModDestHeight, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_anraphet_omega_stance_summon_SpellScript();
    }
};

class spell_omega_stance_spider_effect : public SpellScriptLoader
{
public:
    spell_omega_stance_spider_effect() : SpellScriptLoader("spell_omega_stance_spider_effect") { }

    class spell_omega_stance_spider_effect_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_omega_stance_spider_effect_SpellScript);

        void SetDestPosition(SpellEffIndex effIndex)
        {
            // Do our own calculations for the destination position.
            /// TODO: Remove this once we find a general rule for WorldObject::MovePosition (this spell shouldn't take the Z change into consideration)
            Unit* caster = GetCaster();
            float angle = float(rand_norm()) * static_cast<float>(2 * M_PI);
            uint32 dist = caster->GetObjectSize() + GetSpellInfo()->Effects[effIndex].CalcRadius(GetCaster()) * (float)rand_norm();

            float x = caster->GetPositionX() + dist * std::cos(angle);
            float y = caster->GetPositionY() + dist * std::sin(angle);
            float z = caster->GetPositionZ();

            const_cast<WorldLocation*>(GetExplTargetDest())->Relocate(x, y, z);
            GetHitDest()->Relocate(x, y, z);
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_omega_stance_spider_effect_SpellScript::SetDestPosition, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_omega_stance_spider_effect_SpellScript();
    }
};

void AddSC_boss_anraphet()
{
    new boss_anraphet();
    new npc_brann_bronzebeard_anraphet();
    new npc_alpha_beam();
    new spell_anraphet_alpha_beams();
    new spell_anraphet_omega_stance_summon();
    new spell_omega_stance_spider_effect();
}
