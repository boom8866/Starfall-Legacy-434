/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "firelands.h"

enum Texts
{
    // Majodomo
    SAY_INTRO_1                 = 0,
    SAY_INTRO_2                 = 1,
    SAY_INTRO_3                 = 2,

    // Alysrazor
    SAY_AGGRO                   = 0,
    SAY_TORNADO                 = 1,
    SAY_ANNOUNCE_HARSH_WINDS    = 2,
    SAY_ANNOUNCE_BURNOUT        = 3,
    SAY_BURNOUT                 = 4,

    // Clawshaper
    SAY_IGNITE                  = 0,

    // Egg Pile
    EMOTE_CRACKING_EGGS         = 0,    // The Molten Eggs begin to crack and splinter!
};

enum Sounds
{
    MUSIC_BATTLE    = 25449,
};

enum Spells
{
    // Alysrazor
    SPELL_EARTHQUAKE_COSMETIC                   = 100582,
    SPELL_SACRIFICE_TO_THE_FLAME                = 100557,
    SPELL_SACRIFICE_TO_THE_FLAME_TRIGGERED      = 100558,
    SPELL_DRUID_DEATH_VISUAL                    = 100564,
    SPELL_TRANSFORM_FANDRAL                     = 100565,
    SPELL_VOLCANO_ERUPTION                      = 98402,
    SPELL_VOLCANO_FIRE_TRIGGERED                = 98463,
    SPELL_VOLCANO_FIRE                          = 98462,

    SPELL_FIREHAWK_COSMETIC                     = 100712,
    SPELL_ZERO_POWER                            = 99905,
    SPELL_REPLACE_ANIM                          = 99595,
    SPELL_ENERGY_FULL                           = 99920,
    SPELL_REMOVE_ROOTS                          = 100561,
    SPELL_RIDE_VEHICLE                          = 46598, // purpose bunny 45979 on alysrazor
    SPELL_RUN_LOOP                              = 99604,

    SPELL_MOLTEN_FEATHER_BAR                    = 101410,
    SPELL_MOLTEN_FEATHER_MULTICANCLEL           = 99933,
    SPELL_MOLTEN_FEATHER_COSMETIC               = 99507,

    SPELL_SUMMON_INCINDIARY_CLOUD               = 99529,
    SPELL_INCINDIARY_CLOUD                      = 99426,

    SPELL_SUMMON_BLAZING_POWER                  = 99528,
    SPELL_BLAZING_POWER                         = 99462,

    SPELL_FIRESTORM                             = 99605,
    SPELL_BLAZING_CLAWS                         = 99843,
    SPELL_MOLTING                               = 99464,

    SPELL_FIERY_VORTEX                          = 99793,
    SPELL_HARSH_WINDS                           = 100640,
    SPELL_FIERY_TORNADO                         = 99817,
    SPELL_REMOVE_WINGS                          = 99932,

    SPELL_BURNOUT                               = 99432,
    SPELL_CLAWSHAPER_TRANSFORM                  = 99923,
    SPELL_IGNITION                              = 99919,
    SPELL_IGNITE                                = 99922,

    // Fire Feather
    SPELL_FIRE_FEATHER                          = 97128,
    SPELL_FIRE_FEATHER_MAGE                     = 98761,
    SPELL_FIRE_FEATHER_WARRIOR                  = 98762,
    SPELL_FIRE_FEATHER_WARLOCK                  = 98764,
    SPELL_FIRE_FEATHER_PRIEST                   = 98765,
    SPELL_FIRE_FEATHER_DRUID                    = 98766,
    SPELL_FIRE_FEATHER_ROGUE                    = 98767,
    SPELL_FIRE_FEATHER_HUNTER                   = 98768,
    SPELL_FIRE_FEATHER_PALADIN                  = 98769,
    SPELL_FIRE_FEATHER_SHAMAN                   = 98770,
    SPELL_FIRE_FEATHER_DK                       = 98771,
    SPELL_WINGS_OF_FLAME                        = 98630,
    SPELL_WINGS_OF_FLAME_FLY_AURA               = 98619 ,

    // Harbinger of Flame
    SPELL_FIRE_IT_UP                            = 100093,
    SPELL_FIEROBLAST_TRASH                      = 100094,
    SPELL_FIEROCLAST_BARRAGE                    = 100095,
    SPELL_FIRE_CHANNELING                       = 100109,

    // Blazing Monstrosity
    SPELL_RIDE_MONSTROSITY                      = 93970,
    SPELL_SHARE_HEALTH_LEFT                     = 101502,
    SPELL_SHARE_HEALTH_RIGHT                    = 101503,
    SPELL_SLEEP_ULTRA_HIGH_PRIORITY             = 99480,
    SPELL_GENERIC_DUMMY_CAST                    = 100088,
    SPELL_LEFT_SIDE_SMACK_L                     = 100076,
    SPELL_RIGHT_SIDE_SMACK_L                    = 100078,
    SPELL_HEAD_BONK_L                           = 100080,
    SPELL_TICKLE_L                              = 100082,
    SPELL_KNOCKBACK_RIGHT                       = 100084,
    SPELL_KNOCKBACK_LEFT                        = 100085,
    SPELL_KNOCKBACK_FORWARD                     = 100086,
    SPELL_KNOCKBACK_BACK                        = 100087,
    SPELL_HEAD_BONK_R                           = 100089,
    SPELL_LEFT_SIDE_SMACK_R                     = 100090,
    SPELL_RIGHT_SIDE_SMACK_R                    = 100091,
    SPELL_TICKLE_R                              = 100092,
    SPELL_MOLTEN_BARRAGE_EFFECT_L               = 100071,
    SPELL_MOLTEN_BARRAGE_LEFT                   = 100072,
    SPELL_MOLTEN_BARRAGE_RIGHT                  = 100073,
    SPELL_MOLTEN_BARRAGE_EFFECT_R               = 100074,
    SPELL_MOLTEN_BARRAGE_VISUAL                 = 100075,
    SPELL_AGGRO_CLOSEST                         = 100462,
    SPELL_INVISIBILITY_AND_STEALTH_DETECTION    = 18950,

    // Egg Pile
    SPELL_SUMMON_SMOULDERING_HATCHLING          = 100096,
    SPELL_MOLTEN_EGG_TRASH_CALL_L               = 100097,
    SPELL_MOLTEN_EGG_TRASH_CALL_R               = 100098,
    SPELL_ALYSRAZOR_COSMETIC_EGG_XPLOSION       = 100099,
};

#define SPELL_SHARE_HEALTH          (me->GetEntry() == NPC_BLAZING_MONSTROSITY_LEFT ? SPELL_SHARE_HEALTH_LEFT : SPELL_SHARE_HEALTH_RIGHT)
#define SPELL_MOLTEN_BARRAGE        (me->GetEntry() == NPC_BLAZING_MONSTROSITY_LEFT ? SPELL_MOLTEN_BARRAGE_LEFT : SPELL_MOLTEN_BARRAGE_RIGHT)
#define SPELL_MOLTEN_BARRAGE_EFFECT (me->GetEntry() == NPC_BLAZING_MONSTROSITY_LEFT ? SPELL_MOLTEN_BARRAGE_EFFECT_L : SPELL_MOLTEN_BARRAGE_EFFECT_R)

enum Events
{
    // Majodomo
    EVENT_TALK_INTRO_1 = 1,
    EVENT_TALK_INTRO_2,
    EVENT_TALK_INTRO_3,
    EVENT_TRANSFORM_FANDRAL,
    EVENT_SACRIFICE_TO_FLAME,
    EVENT_BREAK_VOLCANO,

    // Alysrazor
    EVENT_FIRESTORM,
    EVENT_MOVE_1,
    EVENT_MOVE_2,
    EVENT_MOVE_TO_SKY,
    EVENT_START_CYCLE,
    EVENT_MOVE_CYCLE,
    EVENT_SUMMON_CLOUD,
    EVENT_SUMMON_BLAZING_POWER,
    EVENT_MOVE_TO_SKY_2,

    EVENT_PREPARE_BLAZING_CLAWS,
    EVENT_MOVE_CLAWS_1,
    EVENT_MOVE_CLAWS_2,

    EVENT_PREPARE_TORNADOS,
    EVENT_MOVE_TORNADO,
    EVENT_START_TORNADO_CYCLE,
    EVENT_MOVE_TORNADO_CYCLE,
    EVENT_SUMMON_TORNADOS,

    EVENT_FALL_TO_GROUND,
    EVENT_BREAK_GROUND,
    EVENT_SAY_BURNOUT,
    EVENT_SUMMON_CLAWSHAPER,

    // Clawshaper
    EVENT_MOVE_TO_ALYSRAZOR_1,
    EVENT_MOVE_TO_ALYSRAZOR_2,
    EVENT_IGNITE_ALYSRAZOR,

    // Blazing Monstrosity
    EVENT_START_SPITTING,
    EVENT_CONTINUE_SPITTING,

    // Harbinger of Flame
    EVENT_FIEROBLAST,
    EVENT_FIEROCLAST_BARRAGE,

    // Egg Pile
    EVENT_SUMMON_SMOULDERING_HATCHLING,
};

enum MiscData
{
    MODEL_INVISIBLE_STALKER     = 11686,
    ANIM_KIT_BIRD_WAKE          = 1469,
    ANIM_KIT_BIRD_TURN          = 1473,
};

const Position flightPath1[] =
{
    {-41.45439f,    -229.6401f, 130.2321f},
    {-5.090195f,    -241.5612f, 130.2321f},
    {12.19371f,     -275.704f,  130.2321f},
    {0.2726593f,    -312.0682f, 130.2321f},
    {-33.87016f,    -329.3521f, 130.2321f},
    {-70.23436f,    -317.431f,  130.2321f},
    {-87.51826f,    -283.2882f, 130.2321f},
    {-75.59721f,    -246.924f,  130.2321f},
};

const Position tornadoPath[] =
{
    {-16.67685f, -308.2712f, 85.0f},
    {-1.750713f, -281.5417f, 85.0f},
    {-10.09697f, -252.0867f, 85.0f},
    {-36.82651f, -237.1605f, 85.0f},
    {-66.28154f, -245.5068f, 85.0f},
    {-81.20769f, -272.2363f, 85.0f},
    {-72.86142f, -301.6913f, 85.0f},
    {-46.13188f, -316.6175f, 85.0f},
};

const Position tornadoSummons[] =
{
    {-42.01563f, -275.7413f, 56.08091f}, // 1.134464
    {-41.99479f, -275.8177f, 56.07663f}, // 2.6529
    {-42.11979f, -275.7535f, 56.08372f}, // 4.24115
    {-42.05382f, -275.7535f, 56.17978f}, // 5.77704
    {-42.06771f, -275.7795f, 56.0935f},  // 3.508112
    {-41.87674f, -275.7188f, 56.09025f}, // 1.850049
    {-42.05382f, -275.7535f, 56.09428f}, // 2.687807
    {-42.05382f, -275.6267f, 56.10026f}, // 3.839724
    {-41.90104f, -275.7049f, 56.09167f}, // 0.3839724
    {-42.05382f, -275.8177f, 56.09127f}, // 4.24115
    {-41.99132f, -275.7552f, 56.09221f}, // 4.24115
    {-41.94271f, -275.6528f, 56.09542f}, // 1.134464
    {-42.11806f, -275.6892f, 56.09931f}, // 1.117011
    {-42.01563f, -275.6788f, 56.0966f},  // 5.8294
    {-41.98785f, -275.5625f, 56.11374f}, // 1.780236
    {-42.06597f, -275.7153f, 56.10903f}, // 5.811946
    {-42.06771f, -275.7795f, 56.10612f}, // 4.939282
};

const Position shaperPos[] =
{
    {2.081597f,  -236.901f,  100.2516f},
    {-51.71354f, -333.8142f, 98.13007f},
};

Position const takeoffPos = {90.07118f, -390.4445f, 121.5527f};
Position const tornadoPos = {-41.85764f, -275.2743f, 54.47727f};

class boss_alysrazor : public CreatureScript
{
public:
    boss_alysrazor() : CreatureScript("boss_alysrazor") { }

    struct boss_alysrazorAI : public BossAI
    {
        boss_alysrazorAI(Creature* creature) : BossAI(creature, DATA_ALYSRAZOR)
        {
            _moveCounter = 0;
        }

        uint8 _moveCounter;

        void Reset()
        {
            _Reset();
            _moveCounter = 0;
        }

        void EnterCombat(Unit* /*victim*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            DoCastAOE(SPELL_MOLTEN_FEATHER_BAR);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MOLTEN_FEATHER_BAR);
        }

        void KilledUnit(Unit* killed)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_FIERY_TORNADO:
                    summon->SetSpeed(MOVE_RUN, 4.5f);
                    summon->SetSpeed(MOVE_WALK, 4.5f);
                    summon->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    summons.Summon(summon);
                    break;
                default:
                    summons.Summon(summon);
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case 1:
                    events.ScheduleEvent(EVENT_FIRESTORM, 1);
                    break;
                case 2:
                    events.ScheduleEvent(EVENT_MOVE_1, 1);
                    break;
                case 3:
                    events.ScheduleEvent(EVENT_MOVE_2, 1);
                    break;
                case 4:
                    events.ScheduleEvent(EVENT_MOVE_TO_SKY, 1);
                    break;
                case 5:
                    events.ScheduleEvent(EVENT_START_CYCLE, 1);
                    break;
                case 6:
                    events.ScheduleEvent(EVENT_MOVE_CYCLE, 1);
                    break;
                case 7: // prepare claws
                    events.ScheduleEvent(EVENT_MOVE_CLAWS_1, 1);
                    break;
                case 8:
                    events.ScheduleEvent(EVENT_MOVE_CLAWS_2, 1);
                    break;
                case 9:
                    events.ScheduleEvent(EVENT_MOVE_TO_SKY_2, 1);
                    break;
                case 10:
                    events.ScheduleEvent(EVENT_START_CYCLE, 1);
                    break;
                case 11:
                    events.ScheduleEvent(EVENT_MOVE_TORNADO, 1);
                    break;
                case 12:
                    events.ScheduleEvent(EVENT_START_TORNADO_CYCLE, 1);
                    break;
                case 13:
                    events.ScheduleEvent(EVENT_MOVE_TORNADO_CYCLE, 1);
                    break;
                case 14:
                    events.ScheduleEvent(EVENT_BREAK_GROUND, 1);
                    break;

            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->isInCombat())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FIRESTORM:
                        DoCastAOE(SPELL_FIRESTORM);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);  
                        me->SetSpeed(MOVE_RUN, 2.0f);
                        me->GetMotionMaster()->MovePoint(2, 5.97222f, -310.5f, 79.5106f, false);
                        me->SetInCombatWithZone();
                        SendMusicToPlayers(MUSIC_BATTLE);
                        break;
                    case EVENT_MOVE_1:
                        me->GetMotionMaster()->MovePoint(3, 5.972221f, -310.5f, 65.58199f, false);
                        break;
                    case EVENT_MOVE_2:
                        DoCastAOE(SPELL_BLAZING_CLAWS);
                        DoCastAOE(SPELL_MOLTING);
                        me->GetMotionMaster()->MovePoint(4, -75.5972f, -246.924f, 70.2321f, false);
                        break;
                    case EVENT_MOVE_TO_SKY:
                        me->RemoveAurasDueToSpell(SPELL_MOLTING);
                        me->RemoveAurasDueToSpell(SPELL_BLAZING_CLAWS);
                        me->GetMotionMaster()->MovePoint(5, -75.5972f, -246.924f, 130.2321f, false);
                        break;
                    case EVENT_START_CYCLE:
                        _moveCounter++;
                        me->GetMotionMaster()->MovePoint(6, flightPath1[0]);
                        if (Creature* dummy = me->FindNearestCreature(NPC_PURPOSE_BUNNY, 200.0f))
                            dummy->CastSpell(me, SPELL_RIDE_VEHICLE);
                        events.ScheduleEvent(EVENT_SUMMON_CLOUD, 5000);
                        events.ScheduleEvent(EVENT_SUMMON_BLAZING_POWER, 4000);
                        events.ScheduleEvent(EVENT_PREPARE_BLAZING_CLAWS, 100000);
                        break;
                    case EVENT_MOVE_CYCLE:
                        if (_moveCounter < 8)
                        {
                            me->GetMotionMaster()->MovePoint(6, flightPath1[_moveCounter]);
                            _moveCounter++;
                        }
                        else
                        {
                            me->GetMotionMaster()->MovePoint(6, flightPath1[0]);
                            _moveCounter = 1;
                        }
                        break;
                    case EVENT_SUMMON_CLOUD:
                        if (Creature* dummy = me->FindNearestCreature(NPC_PURPOSE_BUNNY, 10.0f))
                            dummy->AI()->DoCastAOE(SPELL_SUMMON_INCINDIARY_CLOUD);
                        events.ScheduleEvent(EVENT_SUMMON_CLOUD, 3000);
                        break;
                    case EVENT_SUMMON_BLAZING_POWER:
                        if (Creature* dummy = me->FindNearestCreature(NPC_PURPOSE_BUNNY, 10.0f))
                            dummy->AI()->DoCastAOE(SPELL_SUMMON_BLAZING_POWER);
                        events.ScheduleEvent(EVENT_SUMMON_BLAZING_POWER, 3000);
                        break;
                    case EVENT_PREPARE_BLAZING_CLAWS:
                        me->GetMotionMaster()->MovePoint(7, -1.154888f, -323.4388f, 125.3229f, false);
                        break;
                    case EVENT_MOVE_CLAWS_1:
                        _moveCounter = 0;
                        events.CancelEvent(EVENT_SUMMON_BLAZING_POWER);
                        events.CancelEvent(EVENT_SUMMON_CLOUD);
                        if (Creature* timingBunny = me->FindNearestCreature(NPC_TIMING_BUNNY, 300.0f))
                            me->SetFacingToObject(timingBunny);
                        me->GetMotionMaster()->MovePoint(8, -1.154887f, -323.4388f, 66.24384f, false);
                        break;
                    case EVENT_MOVE_CLAWS_2:
                        me->GetMotionMaster()->MovePoint(9, -79.7396f, -252.325f, 70.18871f, false);
                        DoCastAOE(SPELL_BLAZING_CLAWS);
                        DoCastAOE(SPELL_MOLTING);
                        break;
                    case EVENT_MOVE_TO_SKY_2:
                        if (Creature* timingBunny = me->FindNearestCreature(NPC_TIMING_BUNNY, 500.0f))
                            me->SetFacingToObject(timingBunny);
                        me->RemoveAurasDueToSpell(SPELL_MOLTING);
                        me->RemoveAurasDueToSpell(SPELL_BLAZING_CLAWS);
                        me->GetMotionMaster()->MovePoint(10, -79.7396f, -252.325f, 130.1887f, false);
                        events.ScheduleEvent(EVENT_PREPARE_TORNADOS, 41000);
                        break;
                    case EVENT_PREPARE_TORNADOS:
                        _moveCounter = 0;
                        events.CancelEvent(EVENT_SUMMON_BLAZING_POWER);
                        events.CancelEvent(EVENT_SUMMON_CLOUD);
                        events.CancelEvent(EVENT_PREPARE_BLAZING_CLAWS);
                        me->GetMotionMaster()->MovePoint(11, -69.71131f, -241.1671f, 130.1887f, false);
                        break;
                    case EVENT_MOVE_TORNADO:
                        Talk(SAY_TORNADO);
                        me->GetMotionMaster()->MovePoint(12, -41.4792f, -276.889f, 85, false);
                        break;
                    case EVENT_START_TORNADO_CYCLE:
                        Talk(SAY_ANNOUNCE_HARSH_WINDS);
                        DoCastAOE(SPELL_RUN_LOOP);
                        events.ScheduleEvent(EVENT_SUMMON_TORNADOS, 5000);
                        if (Creature* tornado = me->SummonCreature(NPC_FIERY_VORTEX, tornadoPos, TEMPSUMMON_MANUAL_DESPAWN))
                        {
                            tornado->AI()->DoCastAOE(SPELL_FIERY_VORTEX);
                            tornado->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);   
                        }
                        me->GetMotionMaster()->MovePoint(13, tornadoPath[0]);
                        _moveCounter++;
                        events.ScheduleEvent(EVENT_FALL_TO_GROUND, 30000);
                        break;
                    case EVENT_MOVE_TORNADO_CYCLE:
                        if (_moveCounter < 8)
                        {
                            me->GetMotionMaster()->MovePoint(13, tornadoPath[_moveCounter]);
                            _moveCounter++;
                        }
                        else
                        {
                            me->GetMotionMaster()->MovePoint(13, tornadoPath[0]);
                            _moveCounter = 1;
                        }
                        break;
                    case EVENT_SUMMON_TORNADOS:
                        for (uint32 x = 0; x < 17; ++x)
                            if (Creature* tornado = me->SummonCreature(NPC_FIERY_TORNADO, tornadoSummons[x], TEMPSUMMON_MANUAL_DESPAWN))
                                tornado->GetMotionMaster()->MovePath(20161 + x, true);
                        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WINGS_OF_FLAME_FLY_AURA);
                        break;
                    case EVENT_FALL_TO_GROUND:
                        Talk(SAY_ANNOUNCE_BURNOUT);
                        DoCastAOE(SPELL_ZERO_POWER);
                        DoCastAOE(SPELL_BURNOUT);
                        summons.DespawnAll();
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveFall(14);
                        events.ScheduleEvent(EVENT_SAY_BURNOUT, 3000);
                        break;
                    case EVENT_BREAK_GROUND:
                        if (GameObject* ground = me->FindNearestGameObject(GO_MOLTEN_GROUND, 500.0f))
                            ground->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                        break;
                    case EVENT_SAY_BURNOUT:
                        Talk(SAY_BURNOUT);
                        for (uint32 x = 0; x < 2; ++x)
                            if (Creature* shaper = me->SummonCreature(NPC_BLAZING_TALON_CLAWSHAPER, shaperPos[x], TEMPSUMMON_MANUAL_DESPAWN))
                                shaper->SetFacingToObject(me);
                        break;
                    default:
                        break;
                }
            }
        }

    private:
        void SendMusicToPlayers(uint32 musicId) const
        {
            WorldPacket data(SMSG_PLAY_MUSIC, 4);
            data << uint32(musicId);
            data << uint64(me->GetGUID());
            SendPacketToPlayers(&data);
        }

        void SendPacketToPlayers(WorldPacket const* data) const
        {
            Map::PlayerList const& players = me->GetMap()->GetPlayers();
            if (!players.isEmpty())
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    if (Player* player = itr->getSource())
                        player->GetSession()->SendPacket(data);
        }

    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_alysrazorAI(creature);
    }
};

class npc_fl_majodomo_alysrazor : public CreatureScript
{
    public:
        npc_fl_majodomo_alysrazor() :  CreatureScript("npc_fl_majodomo_alysrazor") { }

        struct npc_fl_majodomo_alysrazorAI : public ScriptedAI
        {
            npc_fl_majodomo_alysrazorAI(Creature* creature) : ScriptedAI(creature)
            {
                _started = false;
            }

            bool _started;

            void MoveInLineOfSight(Unit* who)
            {
                if (!_started && me->IsWithinDistInMap(who, 10.0f) && who->GetTypeId() == TYPEID_PLAYER)
                {
                    events.ScheduleEvent(EVENT_TALK_INTRO_1, 1);
                    me->SetFacingToObject(who);
                    _started = true;
                }
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_SACRIFICE_TO_THE_FLAME_TRIGGERED)
                    target->CastSpell(target, SPELL_DRUID_DEATH_VISUAL);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TALK_INTRO_1:
                            Talk(SAY_INTRO_1);
                            events.ScheduleEvent(EVENT_TALK_INTRO_2, 6000);
                            break;
                        case EVENT_TALK_INTRO_2:
                            Talk(SAY_INTRO_2);
                            events.ScheduleEvent(EVENT_SACRIFICE_TO_FLAME, 13000);
                            events.ScheduleEvent(EVENT_TALK_INTRO_3, 15700);
                            break;
                        case EVENT_TALK_INTRO_3:
                            Talk(SAY_INTRO_3);
                            DoCastAOE(SPELL_EARTHQUAKE_COSMETIC);
                            events.ScheduleEvent(EVENT_TRANSFORM_FANDRAL, 3300);
                            break;
                        case EVENT_SACRIFICE_TO_FLAME:
                            DoCastAOE(SPELL_SACRIFICE_TO_THE_FLAME);
                            break;
                        case EVENT_TRANSFORM_FANDRAL:
                            DoCastAOE(SPELL_TRANSFORM_FANDRAL);
                            me->SetSpeed(MOVE_FLIGHT, 11.11f);
                            me->SetDisableGravity(true);
                            me->SetCanFly(true);
                            me->GetMotionMaster()->MovePoint(0, 59.63651f, -361.6911f, 137.7812f, false);
                            me->DespawnOrUnsummon(9300);
                            events.ScheduleEvent(EVENT_BREAK_VOLCANO, 8500);
                            break;
                        case EVENT_BREAK_VOLCANO:
                            if (GameObject* volcano = me->FindNearestGameObject(GO_ALYSRAZOR_VOLCANO, 500.0f))
                                volcano->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                            if (Creature* volcanoDummy = me->FindNearestCreature(NPC_VOLCANO_DUMMY, 500.0f))
                            {
                                std::list<Creature*> units;
                                
                                GetCreatureListWithEntryInGrid(units, volcanoDummy, NPC_VOLCANO_TARGET, 500.0f);
                                for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                                volcanoDummy->CastSpell((*itr), SPELL_VOLCANO_ERUPTION);
                            }
                            if (Creature* alysrazor = me->SummonCreature(BOSS_ALYSRAZOR, 90.07118f, -390.4445f, 21.55273f, 2.408f, TEMPSUMMON_MANUAL_DESPAWN))
                            {
                                alysrazor->SetDisableGravity(true);
                                alysrazor->SetHover(true);
                                alysrazor->SetCanFly(true);
                                alysrazor->AI()->DoCastAOE(SPELL_FIREHAWK_COSMETIC);
                                alysrazor->AI()->DoCastAOE(SPELL_ZERO_POWER);
                                alysrazor->AI()->DoCastAOE(SPELL_REPLACE_ANIM);
                                alysrazor->AI()->DoCastAOE(SPELL_ENERGY_FULL);
                                alysrazor->SetSpeed(MOVE_RUN, 11.11f);
                                alysrazor->GetMotionMaster()->MoveTakeoff(1, takeoffPos);
                            }
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
            return new npc_fl_majodomo_alysrazorAI(creature);
        }
};

class npc_fl_blazing_talon_clawshaper : public CreatureScript
{
    public:
        npc_fl_blazing_talon_clawshaper() :  CreatureScript("npc_fl_blazing_talon_clawshaper") { }

        struct npc_fl_blazing_talon_clawshaperAI : public ScriptedAI
        {
            npc_fl_blazing_talon_clawshaperAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_MOVE_TO_ALYSRAZOR_1, 100);
            }

            void MovementInform(uint32 type, uint32 pointId)
            {
                switch (pointId)
                {
                    case 0:
                        events.ScheduleEvent(EVENT_MOVE_TO_ALYSRAZOR_2, 1);
                        break;
                    case 1:
                        events.ScheduleEvent(EVENT_IGNITE_ALYSRAZOR, 1);
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
                        case EVENT_MOVE_TO_ALYSRAZOR_1:
                            if (Creature* alysrazor = me->FindNearestCreature(BOSS_ALYSRAZOR, 500.0f, true))
                                me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+cos(me->GetOrientation())*me->GetDistance2d(alysrazor), me->GetPositionY()+sin(me->GetOrientation())*me->GetDistance2d(alysrazor), 65.61057f);
                            break;
                        case EVENT_MOVE_TO_ALYSRAZOR_2:
                            DoCastAOE(SPELL_CLAWSHAPER_TRANSFORM);
                            me->GetMotionMaster()->MoveFall(1);
                            break;
                        case EVENT_IGNITE_ALYSRAZOR:
                            Talk(SAY_IGNITE);
                            if (Creature* alysrazor = me->FindNearestCreature(BOSS_ALYSRAZOR, 500.0f, true))
                                DoCast(alysrazor, SPELL_IGNITION);
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
            return new npc_fl_blazing_talon_clawshaperAI(creature);
        }
};

class RespawnEggEvent : public BasicEvent
{
    public:
        explicit RespawnEggEvent(Creature* egg) : _egg(egg) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _egg->RestoreDisplayId();
            return true;
        }

    private:
        Creature* _egg;
};

class MoltenEggCheck
{
    public:
        explicit MoltenEggCheck(Creature* pile) : _eggPile(pile) { }

        bool operator()(Unit* object) const
        {
            if (object->GetEntry() != NPC_MOLTEN_EGG_TRASH)
                return false;

            if (object->GetDisplayId() != object->GetNativeDisplayId())
                return false;

            if (_eggPile->GetDistance2d(object) > 20.0f)
                return false;

            return true;
        }

    private:
        Creature* _eggPile;
};

class TrashRespawnWorker
{
    public:
        void operator()(Creature* creature) const
        {
            switch (creature->GetEntry())
            {
                case NPC_BLAZING_MONSTROSITY_LEFT:
                case NPC_BLAZING_MONSTROSITY_RIGHT:
                case NPC_EGG_PILE:
                case NPC_HARBINGER_OF_FLAME:
                case NPC_MOLTEN_EGG_TRASH:
                    if (!creature->isAlive())
                        creature->Respawn(true);
                    break;
                case NPC_SMOULDERING_HATCHLING:
                    creature->DespawnOrUnsummon();
                    break;
            }
        }
};

static void AlysrazorTrashEvaded(Creature* creature)
{
    TrashRespawnWorker check;
    Trinity::CreatureWorker<TrashRespawnWorker> worker(creature, check);
    creature->VisitNearbyGridObject(SIZE_OF_GRIDS, worker);
}

class npc_harbinger_of_flame : public CreatureScript
{
    public:
        npc_harbinger_of_flame() : CreatureScript("npc_harbinger_of_flame") { }

        struct npc_harbinger_of_flameAI : public ScriptedAI
        {
            npc_harbinger_of_flameAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void EnterCombat(Unit* /*target*/)
            {
                if (Creature* bird = ObjectAccessor::GetCreature(*me, me->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT)))
                    DoZoneInCombat(bird, 200.0f);

                me->InterruptSpell(CURRENT_CHANNELED_SPELL);
                _events.Reset();
                _events.ScheduleEvent(EVENT_FIEROBLAST, 1);
                _events.ScheduleEvent(EVENT_FIEROCLAST_BARRAGE, 6000);
            }

            void JustReachedHome()
            {
                AlysrazorTrashEvaded(me);
            }

            void MoveInLineOfSight(Unit* unit)
            {
                if (me->isInCombat())
                    return;

                if (!unit->isCharmedOwnedByPlayerOrPlayer())
                    return;

                ScriptedAI::MoveInLineOfSight(unit);
            }

            void UpdateAI(uint32 diff)
            {
                if (!me->isInCombat())
                    if (!me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                        if (Creature* fireBird = me->FindNearestCreature((me->GetHomePosition().GetPositionY() > -275.0f ? NPC_BLAZING_MONSTROSITY_LEFT : NPC_BLAZING_MONSTROSITY_RIGHT), 100.0f))
                            DoCast(fireBird, SPELL_FIRE_CHANNELING);

                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FIEROBLAST:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, false, -SPELL_RIDE_MONSTROSITY))
                                DoCast(target, SPELL_FIEROBLAST_TRASH);
                            _events.RescheduleEvent(EVENT_FIEROBLAST, 500);  // cast time is longer, but thanks to UNIT_STATE_CASTING check it won't trigger more often (need this because this creature gets a stacking haste aura)
                            break;
                        case EVENT_FIEROCLAST_BARRAGE:
                            DoCastAOE(SPELL_FIEROCLAST_BARRAGE);
                            _events.ScheduleEvent(EVENT_FIEROCLAST_BARRAGE, urand(9000, 12000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_harbinger_of_flameAI(creature);
        }
};

class npc_blazing_monstrosity : public CreatureScript
{
    public:
        npc_blazing_monstrosity() : CreatureScript("npc_blazing_monstrosity") { }

        struct npc_blazing_monstrosityAI : public PassiveAI
        {
            npc_blazing_monstrosityAI(Creature* creature) : PassiveAI(creature), _summons(creature)
            {
            }

            void EnterEvadeMode()
            {
                _summons.DespawnAll();
                _events.Reset();
                PassiveAI::EnterEvadeMode();
            }

            void JustDied(Unit* /*killer*/)
            {
                _summons.DespawnAll();
                _events.Reset();
            }

            void JustReachedHome()
            {
                AlysrazorTrashEvaded(me);
            }

            void EnterCombat(Unit* /*target*/)
            {
                DoZoneInCombat();
                me->RemoveAurasDueToSpell(SPELL_SLEEP_ULTRA_HIGH_PRIORITY);
                me->PlayOneShotAnimKit(ANIM_KIT_BIRD_WAKE);
                _events.Reset();
                _events.ScheduleEvent(EVENT_START_SPITTING, 6000);
                _events.ScheduleEvent(EVENT_CONTINUE_SPITTING, 9000);
            }

            void PassengerBoarded(Unit* passenger, int8 /*seat*/, bool apply)
            {
                if (!apply)
                    return;

                // Our passenger is another vehicle (boardable by players)
                DoCast(passenger, SPELL_SHARE_HEALTH, true);
                passenger->setFaction(35);
                passenger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                // Hack to relocate vehicle on vehicle so exiting players are not moved under map
                Movement::MoveSplineInit init(passenger);
                init.DisableTransportPathTransformations();
                init.MoveTo(0.6654003f, 0.0f, 1.9815f);
                init.SetFacing(0.0f);
                init.Launch();
            }

            void JustSummoned(Creature* summon)
            {
                _summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                _summons.Despawn(summon);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_SPITTING:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, false, -SPELL_RIDE_MONSTROSITY))
                                DoCast(target, SPELL_MOLTEN_BARRAGE);
                            break;
                        case EVENT_CONTINUE_SPITTING:
                            DoCastAOE(SPELL_MOLTEN_BARRAGE_EFFECT);
                            if (Creature* egg = me->FindNearestCreature(NPC_EGG_PILE, 100.0f))
                                egg->AI()->DoAction(me->GetEntry());
                            break;
                    }
                }
            }

        private:
            SummonList _summons;
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_blazing_monstrosityAI(creature);
        }
};

class npc_molten_barrage : public CreatureScript
{
    public:
        npc_molten_barrage() : CreatureScript("npc_molten_barrage") { }

        struct npc_molten_barrageAI : public NullCreatureAI
        {
            npc_molten_barrageAI(Creature* creature) : NullCreatureAI(creature)
            {
            }

            void AttackStart(Unit* target)
            {
                if (target)
                    me->GetMotionMaster()->MoveFollow(target, 0.0f, 0.0f, MOTION_SLOT_IDLE);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCastAOE(SPELL_AGGRO_CLOSEST, true);
                DoCast(me, SPELL_MOLTEN_BARRAGE_VISUAL);
                DoCast(me, SPELL_INVISIBILITY_AND_STEALTH_DETECTION, true);
            }

            void MovementInform(uint32 movementType, uint32 /*pointId*/)
            {
                if (movementType != EFFECT_MOTION_TYPE)
                    return;

                DoCastAOE(SPELL_AGGRO_CLOSEST);
                me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_molten_barrageAI(creature);
        }
};

class npc_egg_pile : public CreatureScript
{
    public:
        npc_egg_pile() : CreatureScript("npc_egg_pile") { }

        struct npc_egg_pileAI : public CreatureAI
        {
            npc_egg_pileAI(Creature* creature) : CreatureAI(creature)
            {
            }

            void AttackStart(Unit* /*target*/) { }

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
                _events.Reset();
                _callHatchlingSpell = 0;
            }

            void JustDied(Unit* /*killer*/)
            {
                _events.Reset();
                std::list<Creature*> eggs;
                GetCreatureListWithEntryInGrid(eggs, me, NPC_MOLTEN_EGG_TRASH, 20.0f);
                for (std::list<Creature*>::const_iterator itr = eggs.begin(); itr != eggs.end(); ++itr)
                    (*itr)->CastSpell(*itr, SPELL_ALYSRAZOR_COSMETIC_EGG_XPLOSION, TRIGGERED_FULL_MASK);

                DoCast(me, SPELL_ALYSRAZOR_COSMETIC_EGG_XPLOSION, true);
            }

            void JustReachedHome()
            {
                AlysrazorTrashEvaded(me);
            }

            void DoAction(int32 action)
            {
                if (action != NPC_BLAZING_MONSTROSITY_LEFT &&
                    action != NPC_BLAZING_MONSTROSITY_RIGHT)
                    return;

                if (action == NPC_BLAZING_MONSTROSITY_LEFT)
                    Talk(EMOTE_CRACKING_EGGS);

                _callHatchlingSpell = (action == NPC_BLAZING_MONSTROSITY_LEFT) ? SPELL_MOLTEN_EGG_TRASH_CALL_L : SPELL_MOLTEN_EGG_TRASH_CALL_R;
                DoZoneInCombat();
                _events.Reset();
                _events.ScheduleEvent(EVENT_SUMMON_SMOULDERING_HATCHLING, 1);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUMMON_SMOULDERING_HATCHLING:
                        {
                            std::list<Creature*> eggs;
                            MoltenEggCheck check(me);
                            Trinity::CreatureListSearcher<MoltenEggCheck> searcher(me, eggs, check);
                            me->VisitNearbyGridObject(20.0f, searcher);
                            if (!eggs.empty())
                            {
                                Creature* egg = Trinity::Containers::SelectRandomContainerElement(eggs);
                                egg->CastSpell(egg, SPELL_SUMMON_SMOULDERING_HATCHLING, TRIGGERED_FULL_MASK);
                                egg->SetDisplayId(MODEL_INVISIBLE_STALKER);
                                egg->m_Events.AddEvent(new RespawnEggEvent(egg), egg->m_Events.CalculateTime(5000));
                            }

                            if (_callHatchlingSpell)
                                DoCastAOE(_callHatchlingSpell, true);
                            _events.ScheduleEvent(EVENT_SUMMON_SMOULDERING_HATCHLING, urand(6000, 10000));
                            break;
                        }
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap _events;
            uint32 _callHatchlingSpell;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_egg_pileAI(creature);
        }
};

class spell_alysrazor_cosmetic_egg_xplosion : public SpellScriptLoader
{
    public:
        spell_alysrazor_cosmetic_egg_xplosion() : SpellScriptLoader("spell_alysrazor_cosmetic_egg_xplosion") { }

        class spell_alysrazor_cosmetic_egg_xplosion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_alysrazor_cosmetic_egg_xplosion_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sCreatureDisplayInfoStore.LookupEntry(MODEL_INVISIBLE_STALKER))
                    return false;
                return true;
            }

            void HandleExplosion(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                GetHitUnit()->SetDisplayId(MODEL_INVISIBLE_STALKER);
                if (Creature* creature = GetHitCreature())
                    creature->DespawnOrUnsummon(4000);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_alysrazor_cosmetic_egg_xplosion_SpellScript::HandleExplosion, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_alysrazor_cosmetic_egg_xplosion_SpellScript();
        }
};

class spell_alysrazor_turn_monstrosity : public SpellScriptLoader
{
    public:
        spell_alysrazor_turn_monstrosity() : SpellScriptLoader("spell_alysrazor_turn_monstrosity") { }

        class spell_alysrazor_turn_monstrosity_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_alysrazor_turn_monstrosity_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_GENERIC_DUMMY_CAST))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_KNOCKBACK_RIGHT))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_KNOCKBACK_LEFT))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_KNOCKBACK_FORWARD))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_KNOCKBACK_BACK))
                    return false;
                return true;
            }

            void KnockBarrage(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                GetHitUnit()->GetMotionMaster()->MoveIdle();
                if (TempSummon* summ = GetHitUnit()->ToTempSummon())
                    if (Unit* summoner = summ->GetSummoner())
                        GetHitUnit()->CastSpell(summoner, SPELL_GENERIC_DUMMY_CAST, TRIGGERED_FULL_MASK);

                float angle = 0.0f;
                if (Unit* bird = GetCaster()->GetVehicleBase())
                {
                    bird->SetInFront(GetHitUnit());
                    angle = bird->GetOrientation();
                }

                uint32 spellId = 0;
                switch (GetSpellInfo()->Id)
                {
                    case SPELL_RIGHT_SIDE_SMACK_R:
                    case SPELL_RIGHT_SIDE_SMACK_L:
                        spellId = SPELL_KNOCKBACK_RIGHT;
                        angle -= M_PI * 0.5f;
                        break;
                    case SPELL_LEFT_SIDE_SMACK_R:
                    case SPELL_LEFT_SIDE_SMACK_L:
                        spellId = SPELL_KNOCKBACK_LEFT;
                        angle += M_PI * 0.5f;
                        break;
                    case SPELL_HEAD_BONK_R:
                    case SPELL_HEAD_BONK_L:
                        spellId = SPELL_KNOCKBACK_FORWARD;
                        break;
                    case SPELL_TICKLE_R:
                    case SPELL_TICKLE_L:
                        spellId = SPELL_KNOCKBACK_BACK;
                        angle -= M_PI;
                        break;
                }

                // Cannot wait for object update to process facing spline, it's needed in next spell cast
                GetHitUnit()->SetOrientation(angle);
                GetHitUnit()->SetFacingTo(angle);
                GetHitUnit()->AddUnitState(UNIT_STATE_CANNOT_TURN);
                GetHitUnit()->CastSpell(GetHitUnit(), spellId, TRIGGERED_FULL_MASK);
            }

            void TurnBird(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                GetHitUnit()->PlayOneShotAnimKit(ANIM_KIT_BIRD_TURN);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_alysrazor_turn_monstrosity_SpellScript::KnockBarrage, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnEffectHitTarget += SpellEffectFn(spell_alysrazor_turn_monstrosity_SpellScript::TurnBird, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_alysrazor_turn_monstrosity_SpellScript();
        }
};

class spell_alysrazor_aggro_closest : public SpellScriptLoader
{
    public:
        spell_alysrazor_aggro_closest() : SpellScriptLoader("spell_alysrazor_aggro_closest") { }

        class spell_alysrazor_aggro_closest_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_alysrazor_aggro_closest_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_UNIT;
            }

            void HandleEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                float curThreat = GetCaster()->getThreatManager().getThreat(GetHitUnit(), true);
                GetCaster()->getThreatManager().addThreat(GetHitUnit(), -curThreat + 50000.0f / std::min(1.0f, GetCaster()->GetDistance(GetHitUnit())));
            }

            void UpdateThreat()
            {
                GetCaster()->ClearUnitState(UNIT_STATE_CASTING);
                GetCaster()->GetAI()->AttackStart(GetCaster()->ToCreature()->SelectVictim());
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_alysrazor_aggro_closest_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
                AfterCast += SpellCastFn(spell_alysrazor_aggro_closest_SpellScript::UpdateThreat);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_alysrazor_aggro_closest_SpellScript();
        }
};

class spell_alysrazor_fieroblast : public SpellScriptLoader
{
    public:
        spell_alysrazor_fieroblast() : SpellScriptLoader("spell_alysrazor_fieroblast") { }

        class spell_alysrazor_fieroblast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_alysrazor_fieroblast_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_FIRE_IT_UP))
                    return false;
                return true;
            }

            void FireItUp()
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_FIRE_IT_UP, TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_alysrazor_fieroblast_SpellScript::FireItUp);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_alysrazor_fieroblast_SpellScript();
        }
};

class spell_alysrazor_volcanic_eruption : public SpellScriptLoader
{
public:
    spell_alysrazor_volcanic_eruption() : SpellScriptLoader("spell_alysrazor_volcanic_eruption") { }

    class spell_alysrazor_volcanic_eruption_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_alysrazor_volcanic_eruption_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                target->CastSpell(target, SPELL_VOLCANO_FIRE);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_alysrazor_volcanic_eruption_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_alysrazor_volcanic_eruption_SpellScript();
    }
};

class spell_alysrazor_fire_feather : public SpellScriptLoader
{
public:
    spell_alysrazor_fire_feather() : SpellScriptLoader("spell_alysrazor_fire_feather") { }

    class spell_alysrazor_fire_feather_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_alysrazor_fire_feather_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                switch (target->getClass())
                {
                    case CLASS_MAGE:
                        target->AddAura(SPELL_FIRE_FEATHER_MAGE, target);
                        break;
                    case CLASS_WARRIOR:
                        target->AddAura(SPELL_FIRE_FEATHER_WARRIOR, target);
                        break;
                    case CLASS_WARLOCK:
                        target->AddAura(SPELL_FIRE_FEATHER_WARLOCK, target);
                        break;
                    case CLASS_SHAMAN:
                        target->AddAura(SPELL_FIRE_FEATHER_SHAMAN, target);
                        break;
                    case CLASS_ROGUE:
                        target->AddAura(SPELL_FIRE_FEATHER_ROGUE, target);
                        break;
                    case CLASS_DRUID:
                        target->AddAura(SPELL_FIRE_FEATHER_DRUID, target);
                        break;
                    case CLASS_PALADIN:
                        target->AddAura(SPELL_FIRE_FEATHER_PALADIN, target);
                        break;
                    case CLASS_DEATH_KNIGHT:
                        target->AddAura(SPELL_FIRE_FEATHER_DK, target);
                        break;
                }

                if (target->GetPower(POWER_ALTERNATE_POWER) > 2)
                    target->CastSpell(target, SPELL_WINGS_OF_FLAME);
                
                if (Unit* player = GetCaster())
                    if (Creature* feather = player->FindNearestCreature(NPC_MOLTEN_FEATHER, 5.0f))
                        feather->DespawnOrUnsummon(1);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_alysrazor_fire_feather_SpellScript::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_alysrazor_fire_feather_SpellScript();
    }
};


void AddSC_boss_alysrazor()
{
    new boss_alysrazor();
    new npc_fl_majodomo_alysrazor();
    new npc_fl_blazing_talon_clawshaper();
    new npc_harbinger_of_flame();
    new npc_blazing_monstrosity();
    new npc_molten_barrage();
    new npc_egg_pile();
    new spell_alysrazor_cosmetic_egg_xplosion();
    new spell_alysrazor_turn_monstrosity();
    new spell_alysrazor_aggro_closest();
    new spell_alysrazor_fieroblast();
    new spell_alysrazor_volcanic_eruption();
    new spell_alysrazor_fire_feather();
}
