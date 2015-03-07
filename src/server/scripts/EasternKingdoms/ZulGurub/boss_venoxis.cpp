
#include "zulgurub.h"

enum Yells
{
    SAY_AGGRO               = 0,
    SAY_TRANSFORM           = 1,
    SAY_BLOODVENOM          = 2,
    SAY_ANNOUNCE_BLOODVENOM = 3,
    SAY_ANNOUNCE_EXHAUSTED  = 4,
    SAY_SLAY                = 5,
    SAY_DEATH               = 6,
};

enum Spells
{
    // Totems
    SPELL_VENOM_TOTEM_BEAM_LEFT     = 96536,
    SPELL_VENOM_TOTEM_BEAM_RIGHT    = 96537,
    SPELL_VENOM_TOTEM               = 96534,

    // Venoxis
    SPELL_WORD_OF_HETHISS           = 96560,
    SPELL_WHISPERS_OF_HETHIS        = 96466,

    SPELL_TOXIC_LINK                = 96475,

    SPELL_BLESSING_OF_THE_SNAKE_GOD = 96512,
    SPELL_POOL_OF_ACRID_TEARS       = 96515,
    SPELL_BREATH_OF_HETHISS         = 96509,
    SPELL_TRANSFORM_REMOVAL_PRIMER  = 96617,
    SPELL_BLOOD_VENOM               = 96842, // Resize to 3 target
    SPELL_VENOMOUS_WITHDRAWAL       = 96653,

    // Bloodvenom
    SPELL_BLOOD_VENOM_VISUAL        = 97110,
    SPELL_VENOM_TOTAM_BEAM_CENTER   = 97098,
    SPELL_BLOOD_VENOM_TRIGGER       = 97099,

    // Venomous Effusion Stalker
    SPELL_VENOMOUS_EFFUSION_TRIGGER = 96678,

    // Venomous Effusion
    SPELL_VENOMOUS_EFFUSION         = 96681,
};

enum Events
{
    // Venoxis
    EVENT_VENOMOUS_EFFUSION = 1,
    EVENT_RELEASE_TOTEMS,
    EVENT_WHISPERS_OF_HETHISS,

    // Venomous Effusion
    EVENT_CAST_EFFUSION,
};

Position const totemStalkerPos[] =
{
    { -12021.8f, -1688.28f, 43.4524f, 0.558505f }, // Right Side
    { -12011.0f, -1705.97f, 43.4762f, 0.523599f }, // Left Side
};

Position const venomousEffusionStalkerPos[] =
{
    { -12013.51f, -1684.175f, 32.36689f, 2.490533f }, // Right Side
    { -12003.96f, -1698.644f, 32.36689f, 5.730771f }, // Left Side
};

class boss_high_priest_venoxis : public CreatureScript
{
    public:
        boss_high_priest_venoxis() : CreatureScript("boss_high_priest_venoxis") { }

        struct boss_high_priest_venoxisAI : public BossAI
        {
            boss_high_priest_venoxisAI(Creature* creature) : BossAI(creature, DATA_VENOXIS) { }

            void Reset()
            {
                _Reset();
                SpawnTotems();
            }

            Creature* totem1;
            Creature* totem2;

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                Talk(SAY_AGGRO);
                me->HandleEmoteCommand(EMOTE_STATE_NONE);
                me->StopMoving();
                DoCast(me, SPELL_WORD_OF_HETHISS);
                events.ScheduleEvent(EVENT_RELEASE_TOTEMS, 2000);
                events.ScheduleEvent(EVENT_VENOMOUS_EFFUSION, 3000);
                events.ScheduleEvent(EVENT_WHISPERS_OF_HETHISS, 5000);
            }

            void EnterEvadeMode()
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->SetBossState(DATA_VENOXIS, FAIL);
                summons.DespawnAll();
                me->GetMotionMaster()->MoveTargetedHome();
                _EnterEvadeMode();
                _DespawnAtEvade();
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                Talk(SAY_DEATH);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void JustRespawned()
            {
                SpawnTotems();
            }

            void SpawnTotems()
            {
                if (totem1 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY, totemStalkerPos[0], TEMPSUMMON_MANUAL_DESPAWN))
                {
                    totem1->CastSpell(totem1, SPELL_VENOM_TOTEM, true);
                    totem1->CastSpell(me, SPELL_VENOM_TOTEM_BEAM_RIGHT, true);
                }

                if (totem2 = me->SummonCreature(NPC_GENERAL_PURPOSE_BUNNY, totemStalkerPos[1], TEMPSUMMON_MANUAL_DESPAWN))
                {
                    totem2->CastSpell(totem2, SPELL_VENOM_TOTEM, true);
                    totem2->CastSpell(me, SPELL_VENOM_TOTEM_BEAM_LEFT, true);
                }
                me->HandleEmoteCommand(EMOTE_STATE_SPELL_PRECAST);
            }

            void MakeInterruptable(bool apply)
            {
                if (apply)
                {
                    me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                }
                else
                {
                    me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
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
                        case EVENT_RELEASE_TOTEMS:
                            me->RemoveAurasDueToSpell(SPELL_VENOM_TOTEM_BEAM_LEFT);
                            me->RemoveAurasDueToSpell(SPELL_VENOM_TOTEM_BEAM_RIGHT);
                            break;
                        case EVENT_VENOMOUS_EFFUSION:
                            if (Creature* right = me->SummonCreature(NPC_VENOMOUS_EFFUSION_STALKER, venomousEffusionStalkerPos[0], TEMPSUMMON_TIMED_DESPAWN, 21000))
                            {
                                right->SetWalk(true);
                                right->GetMotionMaster()->MovePath(right->GetEntry() * 100, false);
                                totem1->CastSpell(right, SPELL_VENOM_TOTEM_BEAM_RIGHT, true);
                            }
                            if (Creature* left = me->SummonCreature(NPC_VENOMOUS_EFFUSION_STALKER, venomousEffusionStalkerPos[1], TEMPSUMMON_TIMED_DESPAWN, 23000))
                            {
                                left->SetWalk(true);
                                left->GetMotionMaster()->MovePath((left->GetEntry() * 100) + 1, false);
                                totem2->CastSpell(left, SPELL_VENOM_TOTEM_BEAM_LEFT, true);
                            }
                            break;
                        case EVENT_WHISPERS_OF_HETHISS:
                            me->StopMoving();
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                DoCast(target, SPELL_WHISPERS_OF_HETHIS);
                            else
                                DoCastVictim(SPELL_WHISPERS_OF_HETHIS);
                            events.ScheduleEvent(EVENT_WHISPERS_OF_HETHISS, 10500);
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
            return new boss_high_priest_venoxisAI(creature);
        }
};

class npc_venomous_effusion : public CreatureScript
{
public:
    npc_venomous_effusion() : CreatureScript("npc_venomous_effusion") { }

    struct npc_venomous_effusionAI : public ScriptedAI
    {
        npc_venomous_effusionAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 1.0f, me->GetOrientation());
            events.ScheduleEvent(EVENT_CAST_EFFUSION, 100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_EFFUSION:
                        DoCast(me, SPELL_VENOMOUS_EFFUSION);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_venomous_effusionAI(creature);
    }
};

void AddSC_boss_venoxis()
{
    new boss_high_priest_venoxis();
    new npc_venomous_effusion();
}
