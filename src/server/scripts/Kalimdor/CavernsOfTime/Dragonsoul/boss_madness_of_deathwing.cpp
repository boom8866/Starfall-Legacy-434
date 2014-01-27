
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

enum Texts
{
    // Deathwing
    SAY_AGGRO               = 0,
    SAY_ANNOUNCE_ASSAULT    = 1,
};

enum Spells
{
    // Deathwing
    SPELL_SHARE_HEALTH              = 109547,
    SPELL_ASSAULT_ASPECTS           = 107018,
    SPELL_SUMMON_TAIL               = 106240, // summons mutated corruption
    SPELL_CATACLYSM                 = 106523,
    SPELL_AGONIZING_PAIN            = 106548,

    // Thrall
    SPELL_ASTRAL_RECALL             = 108537,

    // Mutated Corruption
    SPELL_IGNORE_DODGE_PARRY        = 110470,
    SPELL_IMPALE                    = 106400,
    SPELL_CRUSH                     = 109628,
    SPELL_CRUSH_SUMMON              = 106382,
    SPELL_CRUSH_SUMMON_TRIGGERED    = 106384,

    // Carrying Winds
    SPELL_CARRYING_WINDS            = 106673,
    SPELL_CARRYING_WINDS_JUMP       = 106664,

    // Ysera
    SPELL_CONCENTRATION             = 106643,
};

enum Events
{
    EVENT_EMERGE = 1,
    EVENT_SEND_FRAME,
    EVENT_ASSAULT_ASPECT,
    EVENT_CATACLYSM,
    EVENT_SCHEDULE_ATTACK,
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
    SOUND_AGONY_1   = 26348,
};

enum Emotes
{
    EMOTE_FALL_DOWN     = 402,
    EMOTE_FALLEN        = 403,
    EMOTE_BEATEN        = 404,
    EMOTE_TIRED         = 405,
    EMOTE_DESTROY       = 406,
};

enum AnimKits
{
    // Tentacles
    ANIM_KIT_EMERGE_2   = 1703,
    ANIM_KIT_UNK2       = 1716,

    // Deathwing
    ANIM_KIT_EMERGE     = 1792,

    // Corruption
    ANIM_KIT_CRUSH      = 1711,
};

Position const DeathwingPos = {-11903.9f, 11989.1f, -113.204f, 2.16421f};
Position const TailPos      = {-11857.0f, 11795.6f, -73.9549f, 2.23402f};
Position const WingLeft     = {-11941.2f, 12248.9f, 12.1499f, 1.98968f};
Position const WingRight    = {-12097.8f, 12067.4f, 13.4888f, 2.21657f};
Position const ArmLeft      = {-12005.8f, 12190.3f, -6.59399f, 2.1293f};
Position const ArmRight     = {-12065.0f, 12127.2f, -3.2946f, 2.33874f};
Position const ThrallTeleport = {-12128.3f, 12253.8f, 0.0450132f, 5.456824f};

class boss_madness_of_deathwing : public CreatureScript
{
public:
    boss_madness_of_deathwing() : CreatureScript("boss_madness_of_deathwing") { }

    struct boss_madness_of_deathwingAI : public BossAI
    {
        boss_madness_of_deathwingAI(Creature* creature) : BossAI(creature, DATA_MADNESS_OF_DEATHWING)
        {
        }

        Creature* wingLeft;
        Creature* wingRight;
        Creature* armLeft;
        Creature* armRight;
        Creature* currentPlatform;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            me->AttackStop();
        }


        void JustDied(Unit* /*killer*/)
        {
           
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armLeft);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armRight);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingLeft);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingRight);
            _JustDied();
            summons.DespawnAll();
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            if (armLeft->isAlive())
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armLeft);
            if (armRight->isAlive())
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armRight);
            if (wingLeft->isAlive())
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingLeft);
            if (wingRight->isAlive())
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingRight);
            _EnterEvadeMode();
            summons.DespawnAll();
            me->DespawnOrUnsummon(1000);

            if (Creature* thrall = me->FindNearestCreature(NPC_THRALL_MADNESS, 500.0f, true))
                thrall->AI()->DoAction(ACTION_RESET_ENCOUNTER);
        }

        void IsSummonedBy(Unit* summoner)
        {
            TalkToMap(SAY_AGGRO);
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitMovementFlag(UNIT_FLAG_DISABLE_MOVE);
            me->PlayOneShotAnimKit(ANIM_KIT_EMERGE);
            DoZoneInCombat(me, 500.0f);
            DoAction(ACTION_BEGIN_BATTLE);

            events.ScheduleEvent(EVENT_ASSAULT_ASPECT,5000);
            events.ScheduleEvent(EVENT_SEND_FRAME, 15000);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(0);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_WING_TENTACLE:
                case NPC_ARM_TENTACLE_1:
                case NPC_ARM_TENTACLE_2:
                case NPC_TAIL_TENTACLE:
                    summon->IsAIEnabled = true;
                    summons.Summon(summon);
                    break;
                default:
                    break;
            }
        }

        void Clean()
        {
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
        }

        void SelectPlatform(Creature* platform)
        {
            sLog->outError(LOG_FILTER_SQL, "Reached platform selection");
            currentPlatform = platform;
            events.RescheduleEvent(EVENT_SCHEDULE_ATTACK, 500);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_BEGIN_BATTLE:
                    if (wingLeft = me->SummonCreature(NPC_WING_TENTACLE, WingLeft, TEMPSUMMON_MANUAL_DESPAWN))
                        if (wingRight = me->SummonCreature(NPC_WING_TENTACLE, WingRight, TEMPSUMMON_MANUAL_DESPAWN))
                            if (armLeft = me->SummonCreature(NPC_ARM_TENTACLE_2, ArmLeft, TEMPSUMMON_MANUAL_DESPAWN))
                                if (armRight = me->SummonCreature(NPC_ARM_TENTACLE_1, ArmRight, TEMPSUMMON_MANUAL_DESPAWN))
                                    instance->SendEncounterUnit(ENCOUNTER_FRAME_SET_COMBAT_RES_LIMIT, 0, 0);
                    break;
                case ACTION_TENTACLE_KILLED:
                    DoCast(me, SPELL_AGONIZING_PAIN);
                    DoPlaySoundToSet(me, SOUND_AGONY_1);
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
                    case EVENT_ASSAULT_ASPECT:
                        TalkToMap(SAY_ANNOUNCE_ASSAULT);
                        DoCastAOE(SPELL_ASSAULT_ASPECTS);
                        events.ScheduleEvent(EVENT_CATACLYSM, 155000);
                        break;
                    case EVENT_SEND_FRAME:
                        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                        break;
                    case EVENT_SCHEDULE_ATTACK:
                        sLog->outError(LOG_FILTER_SQL, "Reached attack schedulung in boss AI");
                        if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_ARM_TENTACLE_1, 50.0f, true))
                            tentacle->AI()->DoAction(ACTION_SELECT_TENTACLE);
                        else if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_ARM_TENTACLE_2, 40.0f, true))
                            tentacle->AI()->DoAction(ACTION_SELECT_TENTACLE);
                        else if (Creature* tentacle = currentPlatform->FindNearestCreature(NPC_WING_TENTACLE, 40.0f, true))
                            tentacle->AI()->DoAction(ACTION_SELECT_TENTACLE);
                        break;
                    case EVENT_CATACLYSM:
                        DoCastAOE(SPELL_CATACLYSM);
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
                _assaulted = false;
            }

            InstanceScript* instance;
            EventMap events;
            Creature* deathwing;
            bool _assaulted;

            void IsSummonedBy(Unit* summoner)
            {
                deathwing = summoner->ToCreature();
                me->SetReactState(REACT_PASSIVE);
                me->AddUnitMovementFlag(UNIT_FLAG_DISABLE_MOVE);
                me->PlayOneShotAnimKit(ANIM_KIT_UNK2);
                events.ScheduleEvent(EVENT_EMERGE, 1);
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_SELECT_TENTACLE:
                        sLog->outError(LOG_FILTER_SQL, "Tentacle Action triggered");
                        events.ScheduleEvent(EVENT_SUMMON_CORRUPTION, 2000);
                        events.ScheduleEvent(EVENT_SEND_FRAME, 1000);
                        break;
                    default:
                        break;
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                deathwing->AI()->DoAction(ACTION_TENTACLE_KILLED);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SEND_FRAME:
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                            break;
                        case EVENT_EMERGE:
                            me->PlayOneShotAnimKit(ANIM_KIT_EMERGE_2);
                            break;
                        case EVENT_SUMMON_CORRUPTION:
                            if (Creature* target = me->FindNearestCreature(NPC_TAIL_TENTACLE_TARGET, 300.0f))
                                target->CastSpell(target, SPELL_SUMMON_TAIL);
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

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->AddAura(SPELL_IGNORE_DODGE_PARRY, me);
                me->PlayOneShotAnimKit(ANIM_KIT_EMERGE_2);
                if (Player* target = me->FindNearestPlayer(100.0f, true))
                    me->Attack(target, false);
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
                        case EVENT_SEND_FRAME:
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 0);
                            break;
                        case EVENT_CRUSH_SUMMON:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                target->CastSpell(target, SPELL_CRUSH_SUMMON_TRIGGERED, false);
                            events.ScheduleEvent(EVENT_CRUSH, 50);
                            break;
                        case EVENT_CRUSH:
                            if (Creature* target = me->FindNearestCreature(NPC_CRUSH_TARGET, 50.0f, true))
                            {
                                target->DespawnOrUnsummon(3000);
                                me->SetFacingToObject(target);
                                DoCastAOE(SPELL_CRUSH);
                                me->PlayOneShotAnimKit(ANIM_KIT_CRUSH);
                            }
                            events.ScheduleEvent(EVENT_CRUSH_SUMMON, 14000);
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
            if (!creature->FindNearestCreature(BOSS_MADNESS_OF_DEATHWING, 500.0f, true))
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->SummonCreature(BOSS_MADNESS_OF_DEATHWING, DeathwingPos, TEMPSUMMON_MANUAL_DESPAWN);
                creature->AI()->DoAction(ACTION_BEGIN_BATTLE);
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
                case ACTION_BEGIN_BATTLE:
                    DoCastAOE(SPELL_ASTRAL_RECALL);
                    break;
                case ACTION_RESET_ENCOUNTER:
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    me->NearTeleportTo(me->GetHomePosition(), false);
                    me->RemoveAllAuras();
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
                if (Creature* platform = target->FindNearestCreature(NPC_PLATFORM_DUMMY, 40.0f))
                    if (Creature* deathwing = platform->FindNearestCreature(BOSS_MADNESS_OF_DEATHWING, 500.0f))
                    {
                        uint8 counter = 0;
                        Map::PlayerList const& players = deathwing->GetMap()->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        {
                            if (Player* player = itr->getSource())
                            {
                                if (player->isAlive())
                                {
                                    sLog->outError(LOG_FILTER_SQL, "Player %u", player->GetName());
                                    if (target->GetDistance(player) <= 40.0f) // Platform radius
                                        ++counter;
                                    if (counter > (players.getSize() > 1 ? players.getSize()/2-1 : 0))
                                    {
                                        sLog->outError(LOG_FILTER_SQL, "Counted players. Lets trigger selection function");
                                        CAST_AI(boss_madness_of_deathwing::boss_madness_of_deathwingAI, deathwing->AI())->SelectPlatform(platform);
                                    }
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

void AddSC_boss_madness_of_deathwing()
{
    new boss_madness_of_deathwing();
    new boss_tentacle();
    new npc_thrall_madness();
    new npc_ds_mutated_corruption();
    new spell_ds_assault_aspects();
}
