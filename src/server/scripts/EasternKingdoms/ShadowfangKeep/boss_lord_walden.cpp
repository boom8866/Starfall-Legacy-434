
#include "shadowfang_keep.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_DEATH   = 2,
};

enum Spells
{
    // Lord Walden
    SPELL_ICE_SHARDS                        = 93527,
    SPELL_CONJURE_FROST_MIXTURE             = 93505,
    SPELL_CONJURE_POISONOUS_MIXTURE         = 93697,
    SPELL_CONJURE_MYSTERY_MIXTURE           = 93695,
    SPELL_CONJURE_MYSTERY_MIXTURE_CHANNEL   = 93562,

    // Mystery Toxine
    SPELL_TOXIC_COAGULANT                   = 93572,
    SPELL_TOXIC_COAGULANT_SLOW              = 93617,
    SPELL_TOXIC_CATALYST                    = 93573,
    SPELL_TOXIC_CATALYST_AURA               = 93689,

};

enum Events
{
    EVENT_ICE_SHARDS = 1,
    EVENT_CONJURE_FROST_MIXTURE,
    EVENT_CONJURE_POISONOUS_MIXTURE,
    EVENT_CONJURE_MYSTERY_TOXINE,
    EVENT_ADD_CATALYST,
};

class boss_lord_walden : public CreatureScript
{
public:
    boss_lord_walden() : CreatureScript("boss_lord_walden") { }

    struct boss_lord_waldenAI : public BossAI
    {
        boss_lord_waldenAI(Creature* creature) : BossAI(creature, DATA_LORD_WALDEN)
        {
        }

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();

            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_ICE_SHARDS, 23000);
            events.ScheduleEvent(EVENT_CONJURE_FROST_MIXTURE, 8000);
            events.ScheduleEvent(EVENT_CONJURE_POISONOUS_MIXTURE, 21000);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_CONJURE_MYSTERY_TOXINE, 10500);

        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void KilledUnit(Unit* target)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            summons.DespawnAll();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _DespawnAtEvade();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_MYSTERY_MIXTURE:
                    if (!me->HealthBelowPct(35))
                        summon->CastSpell((Unit*)NULL, SPELL_TOXIC_COAGULANT, true);
                    else
                    {
                        summon->CastSpell((Unit*)NULL, SPELL_TOXIC_CATALYST, true);
                        events.ScheduleEvent(EVENT_ADD_CATALYST, 2000);
                    }
                    summon->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 4.5f, me->GetOrientation());
                    summons.Summon(summon);
                    break;
                default:
                    summons.Summon(summon);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ICE_SHARDS:
                        me->GetMotionMaster()->MovementExpired();
                        DoCastAOE(SPELL_ICE_SHARDS);
                        events.ScheduleEvent(EVENT_ICE_SHARDS, 21500);
                        break;
                    case EVENT_CONJURE_FROST_MIXTURE:
                        me->GetMotionMaster()->MovementExpired();
                        DoCastAOE(SPELL_CONJURE_FROST_MIXTURE);
                        events.ScheduleEvent(EVENT_CONJURE_FROST_MIXTURE, 21500);
                        break;
                    case EVENT_CONJURE_POISONOUS_MIXTURE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_CONJURE_POISONOUS_MIXTURE);
                        events.ScheduleEvent(EVENT_CONJURE_POISONOUS_MIXTURE, 21500);
                        break;
                    case EVENT_CONJURE_MYSTERY_TOXINE:
                        DoCastAOE(SPELL_CONJURE_MYSTERY_MIXTURE);
                        DoCastAOE(SPELL_CONJURE_MYSTERY_MIXTURE_CHANNEL);
                        events.ScheduleEvent(EVENT_CONJURE_MYSTERY_TOXINE, 21500);
                        break;
                    case EVENT_ADD_CATALYST:
                        if (Unit* mixture = me->FindNearestCreature(NPC_MYSTERY_MIXTURE, 20.0f, true))
                            mixture->CastSpell(mixture, SPELL_TOXIC_CATALYST_AURA, false);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_lord_waldenAI (creature);
    }
};

void AddSC_boss_lord_walden()
{
    new boss_lord_walden();
}
