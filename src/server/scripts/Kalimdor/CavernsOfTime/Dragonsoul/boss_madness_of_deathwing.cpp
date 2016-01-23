
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
#include "dragonsoul.h"
#include "Vehicle.h"

enum Texts
{
    // Deathwing
    SAY_AGGRO                           = 0,
    SAY_ANNOUNCE_ASSAULT_ASPECTS        = 1,
    SAY_ANNOUNCE_ASSAULT_YSERA          = 2,
    SAY_ANNOUNCE_ASSAULT_NOZDORMU       = 3,
    SAY_ANNOUNCE_ASSAULT_KALECGOS       = 4,
    SAY_ANNOUNCE_ASSAULT_ALEXSTRASZA    = 5,
    SAY_ANNOUNCE_CATACLYSM              = 6,
    SAY_ANNOUNCE_ELEMENTIUM_BOLT        = 7,
    SAY_ELEMENTIUM_BOLT                 = 8,
    SAY_PHASE_2                         = 9,
    SAY_ANNOUNCE_PHASE_2                = 10,
    SAY_SLAY                            = 11,

    // Aspects
    SAY_ASSAULTED                       = 0,
    SAY_CATACLYSM                       = 1,

    // Tentacles
    SAY_ANNOUNCE_BLISTERING_TENTACLES   = 0,
};

enum Spells
{
    // Deathwing
    SPELL_SHARE_HEALTH_1            = 109547,
    SPELL_SHARE_HEALTH_2            = 109548,
    SPELL_ASSAULT_ASPECTS           = 107018,
    SPELL_SUMMON_TAIL               = 106240, // summons mutated corruption
    SPELL_CATACLYSM                 = 106523,
    SPELL_AGONIZING_PAIN            = 106548,
    SPELL_TRIGGER_ASPECT_BUFFS      = 106943,
    SPELL_REGENERATIVE_BLOOD        = 105932,
    SPELL_REGENERATIVE_BLOOD_SCRIPT = 105934,
    SPELL_CORRUPTED_BLOOD           = 106834,
    SPELL_CORRUPTED_BLOOD_STACKER   = 106843, // casted by vehicle passenger
    SPELL_TRIGGER_ASPECT_YELL       = 109727,
    SPELL_BERSERK                   = 64238,

    // Deathwing Health Controller
    SPELL_DUMMY_NUKE                = 21912,

    SPELL_ELEMENTIUM_BOLT           = 105651,
    SPELL_ELEMENTIUM_BOLT_TRIGGERED = 105599,

    SPELL_SLUMP                     = 106708,

    // Arms
    SPELL_SUMMON_COSMETIC_TENTACLES = 108970,

    // Tentacles
    SPELL_LIMB_EMERGE_VISUAL        = 107991,
    SPELL_TRIGGER_CONCENTRATION     = 106940,
    SPELL_HEMORRHAGE                = 105863, // deathwing casts 
    SPELL_BURNING_BLOOD             = 105401,
    SPELL_SPAWN_BLISTERING_TENTACLE = 105549,

    // Elementium Meteor
    SPELL_ELEMENTIUM_METEOR         = 106242, // Target Platform
    SPELL_ELEMENTIUM_BLAST          = 109600,

    // Thrall
    SPELL_ASTRAL_RECALL             = 108537,

    // Mutated Corruption
    SPELL_IGNORE_DODGE_PARRY        = 110470,
    SPELL_IMPALE                    = 106400,
    SPELL_CRUSH                     = 109628,
    SPELL_CRUSH_SUMMON_AOE          = 106382,
    SPELL_CRUSH_SUMMON_TRIGGERED    = 106384,

    // Renegerative Blood
    SPELL_DEGENERATIVE_BITE         = 105842,
    SPELL_REGENERATIVE_BLOOD_HEAL   = 105937,

    // Blistering Tentacles
    SPELL_BLISTERING_HEAT           = 105444,

    // Ysera
    SPELL_THE_DREAMER               = 106463,
    SPELL_YSERAS_PRESENCE           = 106456,
    SPELL_EXPOSE_WEAKNESS_YSERA     = 109637,

    // Nozdormu
    SPELL_TIME_ZONE                 = 106919,
    SPELL_NOZDORMUS_PRESENCE        = 105823,
    SPELL_EXPOSE_WEAKNESS_NOZDORMU  = 106600,

    // Kalecgos
    SPELL_SPELLWEAVER               = 106039,
    SPELL_KALECGOS_PRESENCE         = 106026,
    SPELL_EXPOSE_WEAKNESS_KALECGOS  = 106624,

    // Alexstrasza
    SPELL_ALEXSTRASZAS_PRESENCE     = 105825,
    SPELL_EXPOSE_WEAKNESS_ALEXSTRASZA = 106588,
    SPELL_CAUTERIZE                 = 105565,

    // Generic Spells
    SPELL_CONCENTRATION_KALECGOS    = 106644,
    SPELL_CONCENTRATION_YSERA       = 106643,
    SPELL_CONCENTRATION_NOZDORMU    = 106642,
    SPELL_CONCENTRATION_ALEXSTRASZA = 106641,

    SPELL_PRESENCE_OF_THE_DRAGONSOUL = 109247,
    SPELL_CALM_MAELSTROM            = 109480,
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598, 
    SPELL_REDUCE_DODGE_PARRY        = 110470,

    // Jump Pad
    SPELL_CARRYING_WINDS_CAST       = 106673,
    SPELL_CARRYING_WINDS_EFFECT     = 106672,
    SPELL_CARRYING_WINDS_SPEED      = 106664,
};

enum Events
{
    // Deathwing
    EVENT_EMERGE = 1,
    EVENT_ASSAULT_ASPECTS,
    EVENT_ASSAULT_ASPECT,
    EVENT_SEND_FRAME,
    EVENT_SUMMON_MUTATED_CORRUPTION,
    EVENT_CATACLYSM,

    EVENT_SLUMP,
    
    // Tentacles
    EVENT_BURNING_BLOOD,

    // Dragon Aspects
    EVENT_SAY_CATACLYSM,

    // Mutated Corruption
    EVENT_CRUSH_SUMMON,
    EVENT_CRUSH_CAST,
    EVENT_IMPALE,

    // Platform
    EVENT_TRANSMIT_PLAYER_COUNT,

    // Thrall

};

enum Actions
{
    // Deathwing
    ACTION_BEGIN_BATTLE = 1,
    ACTION_RESET_ENCOUNTER,
    ACTION_TENTACLE_KILLED,
    ACTION_COUNT_PLAYER,
    ACTION_PHASE_2,

    // Tentacles
    ACTION_PLATFORM_ENGAGED,

    // Dragon Aspects
    ACTION_ASSAULT_ASPECT,
    ACTION_CONCENTRATE_DEATHWING,
    ACTION_PREPARE_ABILITY,
};

enum Sounds
{
    SOUND_AGONY_1       = 26348,
    SOUND_AGONY_2       = 26349,
};

enum AnimKits
{
    // Deathwing
    ANIM_KIT_EMERGE = 1792,

    // Tentacles
    ANIM_KIT_EMERGE_2   = 1703, // Tail 1 // Both casted at the same time
    ANIM_KIT_EMERGE_3   = 1716, // Tail 2

    // Corruption
    ANIM_KIT_CRUSH      = 1711,
};

enum SpellVisualKits
{
    VISUAL_1 = 22447, // Arm 1 // Wing 1
    VISUAL_2 = 22449, // Arm 2
    VISUAL_3 = 22446, // Win 2
};

Position const DeathwingPos     = {-11903.9f, 11989.1f, -113.204f, 2.16421f };
Position const TailPos          = {-11857.0f, 11795.6f, -73.9549f, 2.23402f };
Position const WingLeftPos      = {-11941.2f, 12248.9f, 12.1499f, 1.98968f  };
Position const WingRightPos     = {-12097.8f, 12067.4f, 13.4888f, 2.21657f  };
Position const ArmLeftPos       = {-12005.8f, 12190.3f, -6.59399f, 2.1293f  };
Position const ArmRightPos      = {-12065.0f, 12127.2f, -3.2946f, 2.33874f  };
Position const ThrallTeleport   = {-12128.3f, 12253.8f, 0.0450132f, 5.456824f};

class AspectEntryCheck
{
public:
    AspectEntryCheck() { }

    bool operator()(WorldObject* object)
    {
        return (object->GetEntry() != NPC_YSERA_MADNESS
            && object->GetEntry() != NPC_NOZDORMU_MADNESS
            && object->GetEntry() != NPC_ALEXSTRASZA_MADNESS
            && object->GetEntry() != NPC_KALECGOS_MADNESS);
    }
};

class ConcentractioDistanceCheck
{
public:
    ConcentractioDistanceCheck(Unit* caster) : caster(caster) { }

    bool operator()(WorldObject* object)
    {
        if (caster->GetDistance2d(object)>= 120.0f)
            return true;

        return false;
    }
private:
    Unit* caster;
};

class TentacleMatchCheck
{
public:
    TentacleMatchCheck(Unit* caster) : caster(caster) { }

    bool operator()(WorldObject* object)
    {
        if (caster->GetEntry() == NPC_WING_TENTACLE
            && (object->GetEntry() == NPC_NOZDORMU_MADNESS
            || object->GetEntry() == NPC_YSERA_MADNESS))
            return true;

        if (caster->GetEntry() == NPC_ARM_TENTACLE_1
            && object->GetEntry() != NPC_YSERA_MADNESS)
            return true;

        if (caster->GetEntry() == NPC_ARM_TENTACLE_2
            && object->GetEntry() != NPC_NOZDORMU_MADNESS)
            return true;

        return false;
    }
private:
    Unit* caster;
};

class boss_madness_of_deathwing : public CreatureScript
{
public:
    boss_madness_of_deathwing() : CreatureScript("boss_madness_of_deathwing") { }

    struct boss_madness_of_deathwingAI : public BossAI
    {
        boss_madness_of_deathwingAI(Creature* creature) : BossAI(creature, DATA_MADNESS_OF_DEATHWING), vehicle(creature->GetVehicleKit())
        {
            _killedTentacles = 0;
            currentPlatform = NULL;
            armRight        = NULL; // Ysera
            armLeft         = NULL; // Nozdormu
            wingRight       = NULL; // Kalecgos
            wingLeft        = NULL; // Alextstrasza
            hpController    = NULL;
        }

        Vehicle* vehicle;
        Creature* wingLeft;
        Creature* wingRight;
        Creature* armLeft;
        Creature* armRight;
        Creature* currentPlatform;
        Creature* hpController;
        uint8 _killedTentacles;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            TalkToMap(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_SET_COMBAT_RES_LIMIT, 0, 0);
            events.ScheduleEvent(EVENT_ASSAULT_ASPECTS, 5000);
            events.ScheduleEvent(EVENT_SEND_FRAME, 16000);


            me->SummonCreature(NPC_WING_TENTACLE, WingLeftPos, TEMPSUMMON_MANUAL_DESPAWN);
            me->SummonCreature(NPC_WING_TENTACLE, WingRightPos, TEMPSUMMON_MANUAL_DESPAWN);
            me->SummonCreature(NPC_ARM_TENTACLE_2, ArmLeftPos, TEMPSUMMON_MANUAL_DESPAWN);
            me->SummonCreature(NPC_ARM_TENTACLE_1, ArmRightPos, TEMPSUMMON_MANUAL_DESPAWN);
            me->SummonCreature(NPC_TAIL_TENTACLE, TailPos, TEMPSUMMON_MANUAL_DESPAWN);
            _EnterCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            ResetTentacles();
        }

        void EnterEvadeMode()
        {
            ResetTentacles();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_MADNESS_OF_DEATHWING, FAIL);
            if (Creature* thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL_MADNESS)))
                thrall->AI()->DoAction(ACTION_RESET_ENCOUNTER);

            _EnterEvadeMode();
            me->DespawnOrUnsummon(100);
        }

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->PlayOneShotAnimKit(ANIM_KIT_EMERGE);
            me->SetInCombatWithZone();
            me->SetHover(false);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void SelectPlatform(Creature* platform, uint8 count)
        {
            uint8 currentAlivePlayers = 0;
            Map::PlayerList const &playerList = me->GetMap()->GetPlayers();
            if (!playerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    if (Player* plr = itr->getSource())
                        if (plr->isAlive())
                            currentAlivePlayers++;
            }

            if (currentAlivePlayers > 0)
            {
                if (count > (currentAlivePlayers / 2))
                {
                    if (platform->FindNearestCreature(NPC_ARM_TENTACLE_1, 70.0f, true))
                        currentPlatform = platform;
                    else if (platform->FindNearestCreature(NPC_ARM_TENTACLE_2, 70.0f, true))
                        currentPlatform = platform;
                    else if (platform->FindNearestCreature(NPC_WING_TENTACLE, 70.0f, true))
                        currentPlatform = platform;
                    else
                        SelectRandomPlatform();
                }
                else
                    SelectRandomPlatform();

                events.ScheduleEvent(EVENT_ASSAULT_ASPECT, 500);
            }
        }

        void SelectRandomPlatform()
        {
            std::list<Creature*> units;
            GetCreatureListWithEntryInGrid(units, me, NPC_ARM_TENTACLE_1, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_ARM_TENTACLE_2, 500.0f);
            GetCreatureListWithEntryInGrid(units, me, NPC_WING_TENTACLE, 500.0f);
            sLog->outError(LOG_FILTER_GENERAL, "called random platform selection function");

            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                if ((*itr)->isDead())
                    units.remove(*itr);

            if (!units.empty())
            {
                if (Unit* tentacle = Trinity::Containers::SelectRandomContainerElement(units))
                    if (Creature* platform = tentacle->FindNearestCreature(NPC_PLATFORM_STALKER, 70.0f, true))
                        currentPlatform = platform;
            }
            else
                me->AI()->EnterEvadeMode(); // because we don't like exploiters
        }

        void ResetTentacles()
        {
            if (armLeft)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armLeft);

            if (armRight)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armRight);

            if (wingLeft)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingLeft);

            if (wingRight)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingRight);

            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_ARM_TENTACLE_1:
                    armRight = summon;
                    summon->CastSpell(summon, SPELL_REDUCE_DODGE_PARRY, true);
                    summon->CastSpell(summon, SPELL_LIMB_EMERGE_VISUAL, false);
                    summon->SendPlaySpellVisualKit(VISUAL_1, 0);
                    summons.Summon(summon);
                    break;
                case NPC_ARM_TENTACLE_2:
                    armLeft = summon;
                    summon->CastSpell(summon, SPELL_REDUCE_DODGE_PARRY, true);
                    summon->CastSpell(summon, SPELL_LIMB_EMERGE_VISUAL, false);
                    summon->SendPlaySpellVisualKit(VISUAL_2, 0);
                    summons.Summon(summon);
                    break;
                case NPC_WING_TENTACLE:
                    if (wingRight == NULL)
                    {
                        wingRight = summon;
                        summon->CastSpell(summon, SPELL_REDUCE_DODGE_PARRY, true);
                        summon->CastSpell(summon, SPELL_LIMB_EMERGE_VISUAL, false);
                        summon->SendPlaySpellVisualKit(VISUAL_1, 0);
                    }
                    else
                    {
                        wingLeft = summon;
                        summon->CastSpell(summon, SPELL_REDUCE_DODGE_PARRY, true);
                        summon->CastSpell(summon, SPELL_LIMB_EMERGE_VISUAL, false);
                        summon->SendPlaySpellVisualKit(VISUAL_3, 0);
                    }
                    summons.Summon(summon);
                    break;
                case NPC_TAIL_TENTACLE:
                    summon->CastSpell(summon, SPELL_REDUCE_DODGE_PARRY, true);
                    summon->PlayOneShotAnimKit(ANIM_KIT_EMERGE_2);
                    summon->PlayOneShotAnimKit(ANIM_KIT_EMERGE_3);
                    summons.Summon(summon);
                    break;
                case BOSS_MADNESS_OF_DEATHWING_HP:
                    hpController = summon;
                    break;
                default:
                    summon->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_HOVER);
                    summons.Summon(summon);
                    break;
            }
        }

        void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
        {
            switch (summon->GetEntry())
            {
                case NPC_ARM_TENTACLE_1:
                    armRight = NULL;
                    break;
                case NPC_ARM_TENTACLE_2:
                    armLeft = NULL;
                    break;
                case NPC_WING_TENTACLE:
                    if (wingLeft && wingLeft->GetGUID() == summon->GetGUID())
                        wingLeft = NULL;
                    else if (wingRight && wingRight->GetGUID() == summon->GetGUID())
                        wingRight = NULL;
                    break;
                case BOSS_MADNESS_OF_DEATHWING_HP:
                    hpController = NULL;
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_TENTACLE_KILLED:
                {
                    _killedTentacles++;
                    events.Reset();
                    uint8 random = urand(0, 1);
                    DoPlaySoundToSet(me, random == 0 ? SOUND_AGONY_1 : SOUND_AGONY_2);
                    if (_killedTentacles < 4)
                        events.ScheduleEvent(EVENT_ASSAULT_ASPECTS, 6500);
                    else
                        DoAction(ACTION_PHASE_2);
                    break;
                }
                case ACTION_PHASE_2:
                    me->CastStop();
                    me->RemoveAurasDueToSpell(SPELL_AGONIZING_PAIN);
                    DoCast(me, SPELL_SLUMP);
                    events.ScheduleEvent(EVENT_SLUMP, 200);
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
            
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ASSAULT_ASPECTS:
                        TalkToMap(SAY_ANNOUNCE_ASSAULT_ASPECTS);
                        DoCast(SPELL_ASSAULT_ASPECTS);
                        break;
                    case EVENT_ASSAULT_ASPECT:
                        if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_ARM_TENTACLE_1, 70.0f, true))
                        {
                            if (armRight && tentacle->GetGUID() == armRight->GetGUID())
                            {
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, armRight, 2);
                                armRight->AI()->DoAction(ACTION_PLATFORM_ENGAGED);
                                TalkToMap(SAY_ANNOUNCE_ASSAULT_YSERA);
                                if (Creature* ysera = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_YSERA_MADNESS)))
                                    ysera->AI()->DoAction(ACTION_ASSAULT_ASPECT);
                            }
                        }
                        else if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_ARM_TENTACLE_2, 70.0f, true))
                        {
                            if (armLeft && tentacle->GetGUID() == armLeft->GetGUID())
                            {
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, armLeft, 2);
                                armLeft->AI()->DoAction(ACTION_PLATFORM_ENGAGED);
                                TalkToMap(SAY_ANNOUNCE_ASSAULT_NOZDORMU);
                                if (Creature* nozdormu = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_NOZDORMU_MADNESS)))
                                    nozdormu->AI()->DoAction(ACTION_ASSAULT_ASPECT);
                            }
                        }
                        else if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_WING_TENTACLE, 70.0f, true))
                        {
                            if (wingRight && tentacle->GetGUID() == wingRight->GetGUID())
                            {
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, wingRight, 2);
                                wingRight->AI()->DoAction(ACTION_PLATFORM_ENGAGED);
                                TalkToMap(SAY_ANNOUNCE_ASSAULT_ALEXSTRASZA);
                                if (Creature* alexstrasza = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ALEXSTRASZA_MADNESS)))
                                    alexstrasza->AI()->DoAction(ACTION_ASSAULT_ASPECT);
                            }
                            else if (wingLeft && tentacle->GetGUID() == wingLeft->GetGUID())
                            {
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, wingLeft, 2);
                                wingLeft->AI()->DoAction(ACTION_PLATFORM_ENGAGED);
                                TalkToMap(SAY_ANNOUNCE_ASSAULT_KALECGOS);
                                if (Creature* kalecgos = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_KALECGOS_MADNESS)))
                                    kalecgos->AI()->DoAction(ACTION_ASSAULT_ASPECT);
                            }
                        }
                        events.ScheduleEvent(EVENT_SUMMON_MUTATED_CORRUPTION, 8000);
                        events.ScheduleEvent(EVENT_CATACLYSM, 105000);
                        break;
                    case EVENT_SEND_FRAME:
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 1);
                        break;
                    case EVENT_SUMMON_MUTATED_CORRUPTION:
                    {
                        std::list<Creature*> units;
                        GetCreatureListWithEntryInGrid(units, currentPlatform, NPC_TAIL_TENTACLE_TARGET, 35.0f);
                        if (Creature* tailTarget = Trinity::Containers::SelectRandomContainerElement(units))
                            tailTarget->CastSpell(me, SPELL_SUMMON_TAIL);
                        break;
                    }
                    case EVENT_CATACLYSM:
                        DoCast(me, SPELL_CATACLYSM);
                        break;
                    case EVENT_SLUMP:
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        TalkToMap(SAY_ANNOUNCE_PHASE_2);
                        TalkToMap(SAY_PHASE_2);

                        if (Creature* alexstrasza = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ALEXSTRASZA_MADNESS)))
                            alexstrasza->CastStop();
                        if (Creature* kalecgos = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_KALECGOS_MADNESS)))
                            kalecgos->CastStop();
                        if (Creature* ysera = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_YSERA_MADNESS)))
                            ysera->CastStop();
                        if (Creature* nozdormu = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_NOZDORMU_MADNESS)))
                            nozdormu->CastStop();
                        if (hpController)
                        {
                            hpController->SetHealth(me->GetHealth());
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, hpController, 1);
                            hpController->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            hpController->CastSpell(me, SPELL_SHARE_HEALTH_2, true);
                            hpController->SetReactState(REACT_AGGRESSIVE);
                            hpController->SetInCombatWithZone();
                        }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_madness_of_deathwingAI(creature);
    }
};

class boss_tentacle : public CreatureScript
{
    public:
        boss_tentacle() : CreatureScript("boss_tentacle") { }

        struct boss_tentacleAI : public ScriptedAI
        {
            boss_tentacleAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = me->GetInstanceScript();
                _blisteringCount = 0;
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            uint8 _blisteringCount;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetInCombatWithZone();
            }

            void JustSummoned(Creature* summon)
            {
                switch (summon->GetEntry())
                {
                    case NPC_BLISTERING_TENTACLE:
                        summon->SetReactState(REACT_PASSIVE);
                        summon->SetInCombatWithZone();
                        summon->CastSpell(summon, SPELL_PRESENCE_OF_THE_DRAGONSOUL, true);
                        summon->CastSpell(summon, SPELL_BLISTERING_HEAT, true);
                        summon->CastWithDelay(50, me, SPELL_RIDE_VEHICLE_HARDCODED, true);
                        summons.Summon(summon);
                        break;
                    default:
                        break;
                }
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                if (me->HealthBelowPct(75) && _blisteringCount == 0)
                {
                    TalkToMap(SAY_ANNOUNCE_BLISTERING_TENTACLES);
                    _blisteringCount++;
                    for (uint8 i = 0; i < 7; i++)
                        DoCast(me, SPELL_SPAWN_BLISTERING_TENTACLE, true);
                    if (Creature* alexstrasza = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ALEXSTRASZA_MADNESS)))
                        if (alexstrasza->HasAura(SPELL_ALEXSTRASZAS_PRESENCE))
                            alexstrasza->AI()->DoCast(alexstrasza, SPELL_CAUTERIZE, true);
                }
                if (me->HealthBelowPct(50) && _blisteringCount == 1)
                {
                    TalkToMap(SAY_ANNOUNCE_BLISTERING_TENTACLES);
                    _blisteringCount++;
                    for (uint8 i = 0; i < 7; i++)
                        DoCast(me, SPELL_SPAWN_BLISTERING_TENTACLE, true);
                    if (Creature* alexstrasza = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ALEXSTRASZA_MADNESS)))
                        if (alexstrasza->HasAura(SPELL_ALEXSTRASZAS_PRESENCE))
                            alexstrasza->AI()->DoCast(alexstrasza, SPELL_CAUTERIZE, true);
                }
                if (me->HealthBelowPct(25) && _blisteringCount == 2)
                {
                    TalkToMap(SAY_ANNOUNCE_BLISTERING_TENTACLES);
                    _blisteringCount++;
                    for (uint8 i = 0; i < 7; i++)
                        DoCast(me, SPELL_SPAWN_BLISTERING_TENTACLE, true);
                    if (Creature* alexstrasza = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ALEXSTRASZA_MADNESS)))
                        if (alexstrasza->HasAura(SPELL_ALEXSTRASZAS_PRESENCE))
                            alexstrasza->AI()->DoCast(alexstrasza, SPELL_CAUTERIZE, true);
                }
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_PLATFORM_ENGAGED:
                        events.ScheduleEvent(EVENT_BURNING_BLOOD, 10000);
                        break;
                    default:
                        break;
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                summons.DespawnAll();
                DoCast(me, SPELL_AGONIZING_PAIN, true);
                DoCast(me, SPELL_TRIGGER_CONCENTRATION, true);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BURNING_BLOOD:
                            DoCast(me, SPELL_BURNING_BLOOD, true);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_tentacleAI(creature);
    }
};

class npc_ds_mutated_corruption : public CreatureScript
{
    public:
        npc_ds_mutated_corruption() : CreatureScript("npc_ds_mutated_corruption") { }

        struct npc_ds_mutated_corruptionAI : public ScriptedAI
        {
            npc_ds_mutated_corruptionAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            EventMap events;
            InstanceScript* instance;

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_CRUSH_SUMMON, 5500);
                events.ScheduleEvent(EVENT_IMPALE, 10500);
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->DespawnOrUnsummon(6000);
            }

            void EnterEvadeMode()
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                me->DespawnOrUnsummon(1000);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                SetCombatMovement(false);
                me->SetInCombatWithZone();
                DoCast(me, SPELL_REDUCE_DODGE_PARRY, true);
                me->PlayOneShotAnimKit(ANIM_KIT_EMERGE_2);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 1);
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
                        case EVENT_CRUSH_SUMMON:
                            DoCast(me, SPELL_CRUSH_SUMMON_AOE, true);
                            events.ScheduleEvent(EVENT_CRUSH_CAST, 500);
                            events.ScheduleEvent(EVENT_CRUSH_SUMMON, 14000);
                            break;
                        case EVENT_CRUSH_CAST:
                            if (Creature* crush = me->FindNearestCreature(NPC_CRUSH_TARGET, 70.0f, true))
                            {
                                me->SetFacingToObject(crush);
                                DoCast(crush, SPELL_CRUSH);
                                me->PlayOneShotAnimKit(ANIM_KIT_CRUSH);
                            }
                            break;
                        case EVENT_IMPALE:
                            DoCastVictim(SPELL_IMPALE);
                            events.ScheduleEvent(EVENT_IMPALE, 35000);
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
        return new npc_ds_mutated_corruptionAI(creature);
    }
};

class npc_thrall_madness : public CreatureScript
{
public:
    npc_thrall_madness() : CreatureScript("npc_thrall_madness")
    {
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (!ObjectAccessor::GetCreature(*creature, instance->GetData64(DATA_MADNESS_OF_DEATHWING)))
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->SummonCreature(BOSS_MADNESS_OF_DEATHWING, DeathwingPos, TEMPSUMMON_MANUAL_DESPAWN);
                creature->AI()->DoCast(SPELL_ASTRAL_RECALL);
            }
        }
        return true;
    }

    struct npc_thrall_madnessAI : public ScriptedAI
    {
        npc_thrall_madnessAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_RESET_ENCOUNTER:
                {
                    Position homePos = me->GetHomePosition();
                    me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation());
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                }
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 0:
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_thrall_madnessAI(creature);
    }
};

class npc_ds_ysera_madness : public CreatureScript
{
public:
    npc_ds_ysera_madness() : CreatureScript("npc_ds_ysera_madness") { }

    struct npc_ds_ysera_madnessAI : public ScriptedAI
    {
        npc_ds_ysera_madnessAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterEvadeMode()
        {
            Reset();
            Position homePos = me->GetHomePosition();
            me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation());
        }

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
            DoCast(me, SPELL_YSERAS_PRESENCE, true);
            DoCast(me, SPELL_THE_DREAMER, true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_ASSAULT_ASPECT:
                    TalkToMap(SAY_ASSAULTED);
                    events.ScheduleEvent(EVENT_SAY_CATACLYSM, 105000);
                    break;
                case ACTION_TENTACLE_KILLED:
                    events.CancelEvent(EVENT_SAY_CATACLYSM);
                    break;
                default:
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
                    case EVENT_SAY_CATACLYSM:
                        TalkToMap(SAY_CATACLYSM);
                        DoCast(me, SPELL_EXPOSE_WEAKNESS_YSERA);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_ysera_madnessAI(creature);
    }
};

class npc_ds_nozdormu_madness : public CreatureScript
{
public:
    npc_ds_nozdormu_madness() : CreatureScript("npc_ds_nozdormu_madness") { }

    struct npc_ds_nozdormu_madnessAI : public ScriptedAI
    {
        npc_ds_nozdormu_madnessAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterEvadeMode()
        {
            Reset();
            Position homePos = me->GetHomePosition();
            me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation());
        }

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
            DoCast(me, SPELL_NOZDORMUS_PRESENCE, true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_ASSAULT_ASPECT:
                TalkToMap(SAY_ASSAULTED);
                events.ScheduleEvent(EVENT_SAY_CATACLYSM, 105000);
                break;
            case ACTION_TENTACLE_KILLED:
                events.CancelEvent(EVENT_SAY_CATACLYSM);
                break;
            default:
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
                case EVENT_SAY_CATACLYSM:
                    TalkToMap(SAY_CATACLYSM);
                    DoCast(me, SPELL_EXPOSE_WEAKNESS_NOZDORMU);
                    break;
                default:
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_nozdormu_madnessAI(creature);
    }
};

class npc_ds_alexstrasza_madness : public CreatureScript
{
public:
    npc_ds_alexstrasza_madness() : CreatureScript("npc_ds_alexstrasza_madness") { }

    struct npc_ds_alexstrasza_madnessAI : public ScriptedAI
    {
        npc_ds_alexstrasza_madnessAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterEvadeMode()
        {
            Reset();
            Position homePos = me->GetHomePosition();
            me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation());
        }

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
            DoCast(me, SPELL_ALEXSTRASZAS_PRESENCE, true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_ASSAULT_ASPECT:
                TalkToMap(SAY_ASSAULTED);
                events.ScheduleEvent(EVENT_SAY_CATACLYSM, 105000);
                break;
            case ACTION_TENTACLE_KILLED:
                events.CancelEvent(EVENT_SAY_CATACLYSM);
                break;
            default:
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
                case EVENT_SAY_CATACLYSM:
                    TalkToMap(SAY_CATACLYSM);
                    DoCast(me, SPELL_EXPOSE_WEAKNESS_ALEXSTRASZA);
                    break;
                default:
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_alexstrasza_madnessAI(creature);
    }
};

class npc_ds_kalecgos_madness : public CreatureScript
{
public:
    npc_ds_kalecgos_madness() : CreatureScript("npc_ds_kalecgos_madness") { }

    struct npc_ds_kalecgos_madnessAI : public ScriptedAI
    {
        npc_ds_kalecgos_madnessAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterEvadeMode()
        {
            Reset();
            Position homePos = me->GetHomePosition();
            me->NearTeleportTo(homePos.GetPositionX(), homePos.GetPositionY(), homePos.GetPositionZ(), homePos.GetOrientation());
        }

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, 4.5f, true);
            DoCast(me, SPELL_KALECGOS_PRESENCE, true);
            DoCast(me, SPELL_SPELLWEAVER, true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_ASSAULT_ASPECT:
                TalkToMap(SAY_ASSAULTED);
                events.ScheduleEvent(EVENT_SAY_CATACLYSM, 105000);
                break;
            case ACTION_TENTACLE_KILLED:
                events.CancelEvent(EVENT_SAY_CATACLYSM);
                break;
            default:
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
                case EVENT_SAY_CATACLYSM:
                    TalkToMap(SAY_CATACLYSM);
                    DoCast(me, SPELL_EXPOSE_WEAKNESS_KALECGOS);
                    break;
                default:
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_kalecgos_madnessAI(creature);
    }
};

class npc_ds_platform : public CreatureScript
{
public:
    npc_ds_platform() : CreatureScript("npc_ds_platform") { }

    struct npc_ds_platformAI : public ScriptedAI
    {
        npc_ds_platformAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            playerCount = 0;
        }

        InstanceScript* instance;
        EventMap events;
        uint8 playerCount;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_COUNT_PLAYER:
                    playerCount++;
                    events.CancelEvent(EVENT_TRANSMIT_PLAYER_COUNT);
                    events.ScheduleEvent(EVENT_TRANSMIT_PLAYER_COUNT, 100);
                    break;
                default:
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
                    case EVENT_TRANSMIT_PLAYER_COUNT:
                        if (Creature* deathwing = me->FindNearestCreature(BOSS_MADNESS_OF_DEATHWING, 500.0f, true))
                            CAST_AI(boss_madness_of_deathwing::boss_madness_of_deathwingAI, deathwing->AI())->SelectPlatform(me, playerCount);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ds_platformAI(creature);
    }
};

class spell_ds_assault_aspects : public SpellScriptLoader
{
public:
    spell_ds_assault_aspects() : SpellScriptLoader("spell_ds_assault_aspects") { }

    class spell_ds_assault_aspects_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_assault_aspects_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Player* target = GetHitPlayer())
                if (Creature* platform = target->FindNearestCreature(NPC_PLATFORM_STALKER, 70.0f))
                    platform->AI()->DoAction(ACTION_COUNT_PLAYER);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ds_assault_aspects_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_assault_aspects_SpellScript();
    }
};

class spell_ds_concentration : public SpellScriptLoader
{
public:
    spell_ds_concentration() : SpellScriptLoader("spell_ds_concentration") { }

    class spell_ds_concentration_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_concentration_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* part = GetHitUnit())
                part->SetHover(true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ds_concentration_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    class spell_ds_concentration_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ds_concentration_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget()->ToUnit())
                target->SetHover(false);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_ds_concentration_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ds_concentration_AuraScript();
    }

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_concentration_SpellScript();
    }
};

class spell_ds_carrying_winds_script : public SpellScriptLoader
{
public:
    spell_ds_carrying_winds_script() : SpellScriptLoader("spell_ds_carrying_winds_script") { }

    class spell_ds_carrying_winds_script_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_carrying_winds_script_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->CastSpell(target, GetSpellInfo()->Effects[EFFECT_0].BasePoints, true);
                target->CastSpell(target, SPELL_CARRYING_WINDS_SPEED, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ds_carrying_winds_script_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_carrying_winds_script_SpellScript();
    }
};

class spell_ds_carrying_winds : public SpellScriptLoader
{
public:
    spell_ds_carrying_winds() : SpellScriptLoader("spell_ds_carrying_winds") { }

    class spell_ds_carrying_winds_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_carrying_winds_SpellScript);

        void SelectJumpTarget(WorldObject*& target)
        {
            if (Unit* caster = GetCaster())
            {
                std::list<Creature*> units;
                GetCreatureListWithEntryInGrid(units, caster, NPC_JUMP_PAD, 55.0f);

                for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); itr++)
                    if (caster->isInFront(*itr))
                    {
                        target = (*itr);
                        break;
                    }
            }
        }

        void Register() override
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_ds_carrying_winds_SpellScript::SelectJumpTarget, EFFECT_0, TARGET_DEST_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ds_carrying_winds_SpellScript();
    }
};

class spell_ds_agonizing_pain : public SpellScriptLoader
{
public:
    spell_ds_agonizing_pain() : SpellScriptLoader("spell_ds_agonizing_pain") { }

    class spell_ds_agonizing_pain_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_agonizing_pain_SpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                SetHitDamage(target->GetMaxHealth() * 0.2f);
        }

        void HandleDamageEffect(SpellEffIndex /*effIndex*/)
        {
            if (Creature* deathwing = GetHitCreature())
                deathwing->AI()->DoAction(ACTION_TENTACLE_KILLED);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ds_agonizing_pain_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_ds_agonizing_pain_SpellScript::HandleDamageEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_agonizing_pain_SpellScript();
    }
};

class spell_ds_crush_summon : public SpellScriptLoader
{
public:
    spell_ds_crush_summon() : SpellScriptLoader("spell_ds_crush_summon") { }

    class spell_ds_crush_summon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_crush_summon_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ds_crush_summon_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_crush_summon_SpellScript();
    }
};

class spell_ds_trigger_concentration : public SpellScriptLoader
{
public:
    spell_ds_trigger_concentration() : SpellScriptLoader("spell_ds_trigger_concentration") { }

    class spell_ds_trigger_concentration_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_trigger_concentration_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            targets.remove_if(AspectEntryCheck());

            if (targets.empty())
                return;

            targets.remove_if(ConcentractioDistanceCheck(GetCaster()));

            if (targets.empty())
                return;

            targets.remove_if(TentacleMatchCheck(GetCaster()));

        }

        void HandleScript1(SpellEffIndex /*effIndex*/)
        {
            if (Creature* target = GetHitCreature())
            {
                target->RemoveAllAuras();
                if (target->GetEntry() == NPC_YSERA_MADNESS)
                    target->CastSpell(target, SPELL_CONCENTRATION_YSERA, false);

                if (target->GetEntry() == NPC_NOZDORMU_MADNESS)
                    target->CastSpell(target, SPELL_CONCENTRATION_NOZDORMU, false);

                if (target->GetEntry() == NPC_KALECGOS_MADNESS)
                    target->CastSpell(target, SPELL_CONCENTRATION_KALECGOS, false);

                if (target->GetEntry() == NPC_ALEXSTRASZA_MADNESS)
                    target->CastSpell(target, SPELL_CONCENTRATION_ALEXSTRASZA, false);

                target->GetMotionMaster()->MovePath((target->GetEntry() * 100), false);
                target->AI()->DoAction(ACTION_TENTACLE_KILLED);
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ds_trigger_concentration_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_ds_trigger_concentration_SpellScript::HandleScript1, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_trigger_concentration_SpellScript();
    }
};

class spell_ds_burning_blood : public SpellScriptLoader
{
public:
    spell_ds_burning_blood() : SpellScriptLoader("spell_ds_burning_blood") { }

    class spell_ds_burning_blood_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ds_burning_blood_SpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                float health = (100.0f - caster->GetHealthPct());
                SetHitDamage(GetHitDamage() * health);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ds_burning_blood_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ds_burning_blood_SpellScript();
    }
};

class at_ds_carrying_winds : public AreaTriggerScript
{
    public:
        at_ds_carrying_winds() : AreaTriggerScript("at_ds_carrying_winds") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (Creature* pad = player->FindNearestCreature(NPC_JUMP_PAD, 20.0f, true))
                pad->CastSpell(player, SPELL_CARRYING_WINDS_CAST, true);
            return true;
        }
};

void AddSC_boss_madness_of_deathwing()
{
    new boss_madness_of_deathwing();
    new boss_tentacle();
    new npc_thrall_madness();
    new npc_ds_ysera_madness();
    new npc_ds_nozdormu_madness();
    new npc_ds_alexstrasza_madness();
    new npc_ds_kalecgos_madness();
    new npc_ds_mutated_corruption();
    new npc_ds_platform();
    new spell_ds_assault_aspects();
    new spell_ds_concentration();
    new spell_ds_carrying_winds_script();
    new spell_ds_carrying_winds();
    new spell_ds_agonizing_pain();
    new spell_ds_crush_summon();
    new spell_ds_trigger_concentration();
    new spell_ds_burning_blood();

    new at_ds_carrying_winds();
}
