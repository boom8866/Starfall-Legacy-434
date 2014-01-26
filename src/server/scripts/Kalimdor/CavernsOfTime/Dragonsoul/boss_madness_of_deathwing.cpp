
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
    TALK_SAY_AGGRO      = 0,
};

enum Spells
{
    // Deathwing
    SPELL_SHARE_HEALTH      = 109547,

    // Thrall
    SPELL_ASTRAL_RECALL     = 108537,
};

enum Events
{
    EVENT_EMERGE = 1,
};

enum Actions
{
    ACTION_BEGIN_BATTLE = 1,
    ACTION_RESET_ENCOUNTER,
};

enum AnimKits
{
    // Tentacles
    ANIM_KIT_UNK1   = 1703,
    ANIM_KIT_UNK2   = 1716,

    // Deathwing
    ANIM_KIT_EMERGE = 1792,
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

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
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
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armLeft);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, armRight);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingLeft);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, wingRight);
            _EnterEvadeMode();
            summons.DespawnAll();
            me->DespawnOrUnsummon(1000);

            if (Creature* thrall = me->FindNearestCreature(NPC_THRALL_MADNESS, 500.0f, true))
                thrall->AI()->DoAction(ACTION_RESET_ENCOUNTER);
        }

        void IsSummonedBy(Unit* summoner)
        {
            TalkToMap(TALK_SAY_AGGRO);
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitMovementFlag(UNIT_FLAG_DISABLE_MOVE);
            me->PlayOneShotAnimKit(ANIM_KIT_EMERGE);
            DoZoneInCombat(me, 500.0f);
            DoAction(ACTION_BEGIN_BATTLE);
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

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_BEGIN_BATTLE:
                    if (wingLeft = me->SummonCreature(NPC_WING_TENTACLE, WingLeft, TEMPSUMMON_MANUAL_DESPAWN))
                        wingLeft->SetInCombatWithZone();
                    if (wingRight = me->SummonCreature(NPC_WING_TENTACLE, WingRight, TEMPSUMMON_MANUAL_DESPAWN))
                        wingRight->SetInCombatWithZone();
                    if (armLeft = me->SummonCreature(NPC_ARM_TENTACLE_2, ArmLeft, TEMPSUMMON_MANUAL_DESPAWN))
                        armLeft->SetInCombatWithZone();
                    if (armRight = me->SummonCreature(NPC_ARM_TENTACLE_1, ArmRight, TEMPSUMMON_MANUAL_DESPAWN))
                        armRight->SetInCombatWithZone();

                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, armLeft);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, armRight);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, wingLeft);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, wingRight);
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

            void EnterCombat(Unit* /*who*/)
            {
                me->SetReactState(REACT_PASSIVE);
                me->AddUnitMovementFlag(UNIT_FLAG_DISABLE_MOVE);
                me->PlayOneShotAnimKit(ANIM_KIT_UNK2);
                events.ScheduleEvent(EVENT_EMERGE, 1);
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
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_EMERGE:
                            me->PlayOneShotAnimKit(ANIM_KIT_UNK1);
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

void AddSC_boss_madness_of_deathwing()
{
    new boss_madness_of_deathwing();
    new boss_tentacle();
    new npc_thrall_madness();
}
