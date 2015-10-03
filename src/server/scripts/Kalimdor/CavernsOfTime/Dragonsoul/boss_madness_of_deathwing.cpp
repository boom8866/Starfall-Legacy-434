
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
    SAY_AGGRO                       = 0,
    SAY_ANNOUNCE_ASSAULT            = 1,
    SAY_ANNOUNCE_ATTACK_YSERA       = 2,
    SAY_ANNOUNCE_ATTACK_NOZDORMU    = 3,
    SAY_ANNOUNCE_ATTACK_KALECGOS    = 4,
    SAY_ANNOUNCE_ATTACK_ALEXSTRASZA = 5,
    SAY_ANNOUNCE_CATACLYSM          = 6,
    SAY_PHASE_2                     = 7,
    SAY_ANNOUNCE_PHASE_2            = 8,
    SAY_ANNOUNCE_ELEMENTIUM_BOLT    = 9,
    SAY_ELEMENTIUM_BOLT             = 10,
    SAY_SLAY                        = 11,
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
    SPELL_ELEMENTIUM_BOLT           = 105651,
    SPELL_ELEMENTIUM_BOLT_TRIGGERED = 105599,

    // Arms
    SPELL_SUMMON_CPSMETIC_TENTACLES = 108970,

    // Tentacles
    SPELL_LIMB_EMERGE_VISUAL        = 107991,

    // Elementium Meteor
    SPELL_ELEMENTIUM_METEOR         = 106242, // Target Platform
    SPELL_ELEMENTIUM_BLAST          = 109600,

    // Thrall
    SPELL_ASTRAL_RECALL             = 108537,

    // Mutated Corruption
    SPELL_IGNORE_DODGE_PARRY        = 110470,
    SPELL_IMPALE                    = 106400,
    SPELL_CRUSH                     = 109628,
    SPELL_CRUSH_SUMMON              = 106382,
    SPELL_CRUSH_SUMMON_TRIGGERED    = 106384,

    // Ysera
    SPELL_THE_DREAMER               = 106463,
    SPELL_YSERAS_PRESENCE           = 106456,


    // Generic Spells
    SPELL_CONCENTRATION_KALECGOS    = 106644,
    SPELL_CONCENTRATION_YSERA       = 106643,
    SPELL_CONCENTRATION_NOZDORMU    = 106642,
    SPELL_CONCENTRATION_ALEXTRASZA  = 106641,
    SPELL_TRIGGER_ASPECT_BUFFS      = 106943,
    SPELL_CALM_MAELSTROM            = 109480,
    SPELL_RIDE_VEHICLE              = 46598,
    SPELL_REDUCE_DODGE_PARRY        = 110470,

    // Jump Pads
    SPELL_CARRYING_WINDS_CAST       = 106673, // casted by Jump Pad
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
    EVENT_CATACLYSM,
    EVENT_ELEMENTIUM_BOLT,
    EVENT_MOVE_BOLT,
    EVENT_SCHEDULE_ATTACK,
    EVENT_FALL_DOWN,
    EVENT_FALLEN,

    EVENT_SUMMON_CORRUPTION,
    EVENT_CRUSH_SUMMON,
    EVENT_CRUSH,
    EVENT_IMPALE,
};

enum Actions
{
    ACTION_BEGIN_BATTLE = 1,
    ACTION_RESET_ENCOUNTER,
    ACTION_SELECT_TENTACLE,
    ACTION_TENTACLE_KILLED,
    ACTION_COUNT_PLAYER,
};

enum Sounds
{
    SOUND_AGONY_1       = 26348,
    SOUND_AGONY_2       = 26349,

    SOUND_CATACLYSM_1   = 26357,
    SOUND_CATACLYSM_2   = 26358,
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

Position const DeathwingPos = {-11903.9f, 11989.1f, -113.204f, 2.16421f};
Position const TailPos      = {-11857.0f, 11795.6f, -73.9549f, 2.23402f};
Position const WingLeftPos     = {-11941.2f, 12248.9f, 12.1499f, 1.98968f};
Position const WingRightPos    = {-12097.8f, 12067.4f, 13.4888f, 2.21657f};
Position const ArmLeftPos      = {-12005.8f, 12190.3f, -6.59399f, 2.1293f};
Position const ArmRightPos     = {-12065.0f, 12127.2f, -3.2946f, 2.33874f};
Position const ThrallTeleport = {-12128.3f, 12253.8f, 0.0450132f, 5.456824f};

class CarryingWindsDistanceCheck
{
public:
    CarryingWindsDistanceCheck(Unit* caster) : caster(caster) { }

    bool operator()(WorldObject* object)
    {
        return (object->GetDistance2d(caster) <= 10.0f);
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
            _armCounter = 0;
            currentPlatform = NULL;
            armRight = NULL;    // Ysera
            armLeft = NULL;     // Nozdormu
            wingRight = NULL;   // Kalecgos
            wingLeft = NULL;    // Alextstrasza
        }

        Vehicle* vehicle;
        Creature* wingLeft;
        Creature* wingRight;
        Creature* armLeft;
        Creature* armRight;
        Creature* currentPlatform;
        uint8 _armCounter;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            TalkToMap(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_SET_COMBAT_RES_LIMIT, 0, 0);
            events.ScheduleEvent(EVENT_ASSAULT_ASPECTS, 5000);


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
            if (Creature* thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL_MADNESS)))
                thrall->AI()->DoAction(ACTION_RESET_ENCOUNTER);
            _EnterEvadeMode();
            me->DespawnOrUnsummon(100);
        }

        void InitializeAI()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner)
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

        void SelectPlatform(Creature* platform)
        {
            currentPlatform = platform;
            events.ScheduleEvent(EVENT_ASSAULT_ASPECT, 500);
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
                    armRight = summon;
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
                    me->CastSpell(summon, SPELL_SHARE_HEALTH_1, true);
                    summon->CastSpell(me, SPELL_SHARE_HEALTH_2, true);
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
                    if (wingLeft->GetGUID() && wingLeft->GetGUID() == summon->GetGUID())
                        wingLeft = NULL;
                    else if (wingRight->GetGUID() && wingRight->GetGUID() == summon->GetGUID())
                        wingRight = NULL;
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
                case 0:
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
                        TalkToMap(SAY_ANNOUNCE_ASSAULT);
                        DoCast(SPELL_ASSAULT_ASPECTS);
                        break;
                    case EVENT_ASSAULT_ASPECT:
                        if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_ARM_TENTACLE_1, 70.0f, true))
                            if (tentacle->GetGUID() == armRight->GetGUID())
                            {
                                TalkToMap(SAY_ANNOUNCE_ATTACK_YSERA);
                            }
                        else if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_ARM_TENTACLE_2, 70.0f, true))
                            if (tentacle->GetGUID() == armLeft->GetGUID())
                            {
                                TalkToMap(SAY_ANNOUNCE_ATTACK_NOZDORMU);
                            }
                        else if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_WING_TENTACLE, 70.0f, true))
                            if (tentacle->GetGUID() == wingRight->GetGUID())
                            {
                                TalkToMap(SAY_ANNOUNCE_ATTACK_KALECGOS);
                            }
                            else if (tentacle->GetGUID() == wingLeft->GetGUID())
                            {
                                TalkToMap(SAY_ANNOUNCE_ATTACK_ALEXSTRASZA);
                            }
                        break;
                        break;
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
            boss_tentacleAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetInCombatWithZone();
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case 0:
                        break;
                    default:
                        break;
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
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
                events.ScheduleEvent(EVENT_IMPALE, 11000);
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
                me->SetInCombatWithZone();
                me->PlayOneShotAnimKit(ANIM_KIT_EMERGE_2);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
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
                        case 0:
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
            {
                if (Creature* platform = target->FindNearestCreature(NPC_PLATFORM_STALKER, 50.0f))
                    if (Creature* deathwing = platform->FindNearestCreature(BOSS_MADNESS_OF_DEATHWING, 500.0f))
                    {
                        uint8 counter = 0;
                        Map::PlayerList const& players = deathwing->GetMap()->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                            if (Player* player = itr->getSource())
                            {
                                if (player->isAlive())
                                {
                                    sLog->outError(LOG_FILTER_SQL, "Player %u", player->GetName());
                                    if (target->GetDistance(player) <= 50.0f) // Platform radius
                                        ++counter;

                                    if (counter > (players.getSize() > 1 ? players.getSize() / 2 - 1 : 0))
                                    {
                                        sLog->outError(LOG_FILTER_SQL, "Counted players. Lets trigger selection function");
                                        CAST_AI(boss_madness_of_deathwing::boss_madness_of_deathwingAI, deathwing->AI())->SelectPlatform(platform);
                                    }
                                }
                            }
                    }
            }
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
    new npc_ds_mutated_corruption();
    new spell_ds_assault_aspects();
    new spell_ds_concentration();
    new spell_ds_carrying_winds_script();
    new spell_ds_carrying_winds();
    new at_ds_carrying_winds();

}
