
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "blackwing_descent.h"

// Define to debug a phase
// #define DEBUG_PHASE PHASE_BLACK

enum Spells
{
    // General
    SPELL_BERSERK                   = 64238,
    SPELL_RELEASE_ABBERATIONS       = 77569,
    SPELL_RELEASE_ALL_ABBERATIONS   = 77991,
    SPELL_REMEDY                    = 77912,
    SPELL_ARCANE_STORM              = 77896,

    // Red Phase
    SPELL_THROW_RED_BOTTLE          = 77925,
    SPELL_DRINK_RED_BOTTLE          = 88699,
    SPELL_FIRE_IMBUED               = 78896,

    SPELL_SCORCHING_BLAST           = 77679,
    SPELL_CONSUMING_FLAMES          = 77786,

    // Blue Phase
    SPELL_THROW_BLUE_BOTTLE         = 77932,
    SPELL_DRINK_BLUE_BOTTLE         = 88700,
    SPELL_FROST_IMBUED              = 78895,

    SPELL_BITING_CHILL              = 77760,

    SPELL_FLASH_FREEZE              = 77699,
    SPELL_FLASH_FREEZE_SUMMON       = 77711,
    SPELL_FLASH_FREEZE_VISUAL       = 77712,

    // Green Phase
    SPELL_THROW_GREEN_BOTTLE        = 77937,

    SPELL_CAULDRON_EXPLOSION        = 85172,
    SPELL_CAULDRON_EXPL_PUSH        = 77948,

    SPELL_DEBILITATING_SLIME        = 77602,
    SPELL_DEBILITATING_SLIME_EFFECT = 77615,

    // Black Phase
    SPELL_THROW_BLACK_BOTTLE        = 92831,
    SPELL_DRINK_BLACK_BOTTLE        = 92828,
    SPELL_SHADOW_IMBUED             = 92716,

    SPELL_ENGULFING_DARKNESS        = 92982,

    // Final Phase
    SPELL_DRINK_ALL_BOTTLES         = 95662,

    SPELL_ACID_NOVA                 = 78225,

    SPELL_MAGMA_JET                 = 78194,
    SPELL_MAGMA_JET_EFFECT          = 78095,

    SPELL_ABSOLUTE_ZERO             = 78201,
    SPELL_ABSOLUTE_ZERO_DAMAGE      = 78208,

    // Abberations
    SPELL_GROWTH_CATALYST           = 77987,
    SPELL_DROWNED_STATE             = 77564,

    // Prime Subjects
    SPELL_FIXATE                    = 78618
};

enum Events
{
    // General
    EVENT_NEW_PHASE = 1,
    EVENT_THROW,
    EVENT_UNLOCK_SPELLS,
    EVENT_WAIT_SWITCH_PHASE,
    EVENT_BERSERK,
    EVENT_REMEDY,
    EVENT_ARCANE_STORM,

    // Red Phase
    EVENT_SCORCHING_BLAST,
    EVENT_CONSUMING_FLAMES,

    // Blue Phase
    EVENT_BITING_CHILL,
    EVENT_FLASH_FREEZE,

    // Green Phase
    EVENT_CAULDRON_EXPLODE,
    EVENT_CAULDRON_PUSH_BACK,
    EVENT_RELEASE_ABBERATIONS,

    // Black Phase
    EVENT_SUMMON_VILE_SWILL,
    EVENT_ENGULFING_DARKNESS,

    // Final Phase
    EVENT_DRINK_ALL_BOTTLES,
    EVENT_ACID_NOVA,
    EVENT_MAGMA_JET,
    EVENT_ABSOLUTE_ZERO,

    // Abberations
    EVENT_CHECK_GROWTH_CATALYST,

    // Prime Subject
    EVENT_FIXATE
};

enum Texts
{
    SAY_AGGRO                       = 0,
    SAY_VIAL_WARNING                = 1,
    // SAY_VIAL_WARNING             = 2,
    // SAY_VIAL_WARNING             = 3,
    SAY_VIAL                        = 4,
    // SAY_VIAL                     = 5,
    // SAY_VIAL                     = 6,
    SAY_ABBERATIONS                 = 7,
    SAY_SLAY_OR_ABILITY             = 8,
    SAY_LOW_HP                      = 9,
    SAY_DEATH                       = 10,
};

enum Constants
{
    COUNT_ABBERATIONS_PER_RELEASE   = 3,
    COUNT_MAGMA_JETS                = 9,

    MPOS_ABBERATION                 = 0,
    MPOS_PRIME_SUBJECT              = 18,
    MPOS_CAULDRON                   = 20
};

Position const MaloriakPositions[21] =
{
    {-150.332f, -432.316f, 83.0525f, 5.74213f}, // MPOS_ABBERATION
    {-61.3299f, -425.250f, 83.6979f, 3.80482f},
    {-69.3472f, -417.590f, 104.458f, 3.14159f},
    {-69.1615f, -417.741f, 94.9475f, 3.12414f},
    {-143.809f, -418.507f, 103.945f, 5.11381f},
    {-69.0035f, -417.688f, 85.2381f, 3.10669f},
    {-151.095f, -426.809f, 83.1099f, 0.17453f},
    {-64.0729f, -420.663f, 83.6404f, 3.42085f},
    {-148.835f, -438.078f, 85.2381f, 5.65487f},
    {-61.2656f, -431.288f, 83.4554f, 2.70526f},
    {-144.153f, -418.741f, 85.5198f, 5.58505f},
    {-63.2465f, -437.377f, 103.945f, 2.68781f},
    {-63.1927f, -437.582f, 94.9965f, 2.77507f},
    {-149.401f, -421.208f, 82.8674f, 4.78220f},
    {-143.931f, -418.472f, 94.9965f, 5.20108f},
    {-63.2135f, -437.502f, 85.5198f, 3.15905f},
    {-148.575f, -438.087f, 104.458f, 5.68977f},
    {-149.155f, -438.099f, 94.9475f, 5.67232f},

    {-66.4080f, -426.899f, 97.1776f, 4.18879f}, // MPOS_PRIME_SUBJECT
    {-145.460f, -427.517f, 97.1776f, 0.61086f},

    {-106.150f, -473.517f, 73.4546f, 4.69942f}, // MPOS_CAULDRON
};

float const groundZ = 73.68f;

enum Phases
{
    PHASE_RED,
    PHASE_BLUE,
    PHASE_GREEN,
    PHASE_BLACK,
    PHASE_NON,
    PHASE_FINAL,
};

class boss_maloriak : public CreatureScript
{
public:
    boss_maloriak() : CreatureScript("boss_maloriak") { }

    struct boss_maloriakAI : public BossAI
    {
        boss_maloriakAI(Creature* creature) : BossAI(creature, DATA_MALORIAK) { }

        uint8 phase;
        uint8 lastPhase;
        bool spellsLocked;
        bool wasInBlackPhase;
        uint8 withoutGreenPhase;
        uint8 magmaJetsLeft;
        uint8 abberationsLeft;

        void Reset()
        {
            _Reset();
            DespawnMinions();

            me->SetReactState(REACT_AGGRESSIVE);
            withoutGreenPhase = 0;
            magmaJetsLeft = 0;
            abberationsLeft = 18;
            wasInBlackPhase = true;
            spellsLocked = false;
            UpdatePhase(PHASE_NON);

            for (uint8 i = MPOS_ABBERATION; i < MPOS_PRIME_SUBJECT; i++)
            {
                Creature* abberation = me->SummonCreature(NPC_ABBERATON, MaloriakPositions[i]);
                HandleAbberationStun(abberation, true);
                summons.Summon(abberation);
            }
            for (uint8 i = MPOS_PRIME_SUBJECT; i < MPOS_CAULDRON; i++)
            {
                Creature* primeSubject = me->SummonCreature(NPC_PRIME_SUBJECT, MaloriakPositions[i]);
                HandleAbberationStun(primeSubject, true);
                summons.Summon(primeSubject);
            }

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            RemoveEncounterFrame();
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);

            events.ScheduleEvent(EVENT_NEW_PHASE, urand(10000, 12000));
            events.ScheduleEvent(EVENT_REMEDY, urand(15000, 18000));
            events.ScheduleEvent(EVENT_ARCANE_STORM, urand(7000, 8000));

            events.ScheduleEvent(EVENT_BERSERK, me->GetMap()->IsHeroic() ? 720000 : 420000);

            instance->SetBossState(DATA_MALORIAK, IN_PROGRESS);

            if (!instance || !instance->CheckRequiredBosses(DATA_MALORIAK))
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            AddEncounterFrame();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);
            //_DoAggroPulse(diff);

            if (!spellsLocked && me->GetHealthPct() < 25 && phase != PHASE_FINAL)
            {
                // Enter Final Phase
                uint32 uiBerserker = events.GetNextEventTime(EVENT_BERSERK);
                events.Reset();
                events.ScheduleEvent(EVENT_BERSERK, uiBerserker);

                phase = PHASE_FINAL;
                me->InterruptNonMeleeSpells(true);

                events.ScheduleEvent(EVENT_ACID_NOVA, urand(13000, 16000));
                events.ScheduleEvent(EVENT_MAGMA_JET, urand(6000, 8000));
                events.ScheduleEvent(EVENT_ABSOLUTE_ZERO, urand(3000, 4000));
                events.ScheduleEvent(EVENT_DRINK_ALL_BOTTLES, 5000);

                DoCast(SPELL_RELEASE_ALL_ABBERATIONS);

                Talk(SAY_LOW_HP);
            }

            //CheckCheat(80.f);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // General and Phase Switching
                    case EVENT_NEW_PHASE:
                    {
                        if (IsImbued())
                            events.ScheduleEvent(EVENT_NEW_PHASE, 1000);
                        else
                        {
                            UpdatePhase(urand(PHASE_RED, PHASE_BLUE));
                            spellsLocked = true;
                            events.ScheduleEvent(EVENT_NEW_PHASE, 32000);
                        }
                        break;
                    }
                    case EVENT_THROW:
                    {
                        if (Creature* trigger = me->GetCreature(*me, instance->GetData64(NPC_CAULDRON_TRIGGER)))
                        {
                            switch (phase)
                            {
                                case PHASE_RED:
                                    DoCast(trigger, SPELL_THROW_RED_BOTTLE);
                                    break;

                                case PHASE_BLUE:
                                    DoCast(trigger, SPELL_THROW_BLUE_BOTTLE);
                                    break;

                                case PHASE_GREEN:
                                    DoCast(trigger, SPELL_THROW_GREEN_BOTTLE);
                                    events.ScheduleEvent(EVENT_CAULDRON_PUSH_BACK, 1200);
                                    break;

                                case PHASE_BLACK:
                                    DoCast(trigger, SPELL_THROW_BLACK_BOTTLE);
                                    me->AddAura(SPELL_SHADOW_IMBUED, me);
                                    break;
                            }
                        }

                        if (GameObject* cauldron = me->FindNearestGameObject(GOB_MALORIAKS_CAULDRON, 100.f))
                        {
                            cauldron->SendCustomAnim(phase);
                            me->SetFacingToObject(cauldron);
                        }

                        events.ScheduleEvent(EVENT_WAIT_SWITCH_PHASE, 2000);
                        break;
                    }
                    case EVENT_WAIT_SWITCH_PHASE:
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->GetMotionMaster()->MoveChase(me->getVictim());

                        // Intialize Phase Events
                        switch (phase)
                        {
                            case PHASE_RED:
                                DoCast(SPELL_DRINK_RED_BOTTLE);
                                me->AddAura(SPELL_FIRE_IMBUED, me);
                                events.ScheduleEvent(EVENT_SCORCHING_BLAST, 7000);
                                events.ScheduleEvent(EVENT_CONSUMING_FLAMES, 3000);
                                break;

                            case PHASE_BLUE:
                                DoCast(SPELL_DRINK_BLUE_BOTTLE);
                                me->AddAura(SPELL_FROST_IMBUED, me);
                                events.ScheduleEvent(EVENT_BITING_CHILL, 7000);
                                events.ScheduleEvent(EVENT_FLASH_FREEZE, 9000);
                                break;

                            case PHASE_GREEN:
                                events.ScheduleEvent(EVENT_CAULDRON_EXPLODE, 1500);
                                break;

                            case PHASE_BLACK:
                                DoCast(SPELL_DRINK_BLACK_BOTTLE);
                                me->AddAura(SPELL_SHADOW_IMBUED, me);
                                events.ScheduleEvent(EVENT_SUMMON_VILE_SWILL, urand(4000,6000));
                                events.ScheduleEvent(EVENT_ENGULFING_DARKNESS, 9000);
                                break;
                        }

                        if (phase != PHASE_BLACK)
                        {
                            events.ScheduleEvent(EVENT_RELEASE_ABBERATIONS, urand(12000,17000));
                            Talk(SAY_VIAL + phase);
                        }

                        events.ScheduleEvent(EVENT_UNLOCK_SPELLS, 1500);
                        break;
                    }
                        // Misc
                    case EVENT_UNLOCK_SPELLS:
                        spellsLocked = false;
                        break;
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK, true);
                        break;
                    case EVENT_REMEDY:
                    {
                        if (spellsLocked)
                            events.ScheduleEvent(EVENT_REMEDY, 1500);
                        else
                        {
                            DoCast(me,SPELL_REMEDY);
                            events.ScheduleEvent(EVENT_REMEDY, urand(15000,18000));
                        }
                        break;
                    }
                    case EVENT_ARCANE_STORM:
                    {
                        if (spellsLocked)
                            events.ScheduleEvent(EVENT_ARCANE_STORM, 1500);
                        else
                        {
                            me->AttackStop();
                            DoCastAOE(SPELL_ARCANE_STORM);
                            events.ScheduleEvent(EVENT_ARCANE_STORM, urand(27000,29000));
                        }
                        break;
                    }
                        // Red Phase
                    case EVENT_SCORCHING_BLAST:
                        DoCastAOE(SPELL_SCORCHING_BLAST);
                        events.ScheduleEvent(EVENT_SCORCHING_BLAST, urand(15000, 17000));
                        break;

                    case EVENT_CONSUMING_FLAMES:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_CONSUMING_FLAMES);

                        events.ScheduleEvent(EVENT_CONSUMING_FLAMES, urand(7000, 8500));
                        break;
                    }
                        // Blue Phase
                    case EVENT_BITING_CHILL:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(target, SPELL_BITING_CHILL);

                        events.ScheduleEvent(EVENT_BITING_CHILL, urand(8000, 10000));
                        break;
                    }
                    case EVENT_FLASH_FREEZE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            target->CastSpell(target, SPELL_FLASH_FREEZE_SUMMON, true);

                        events.ScheduleEvent(EVENT_FLASH_FREEZE, urand(11000, 13000));
                        break;
                    }
                        // Green Phase
                    case EVENT_CAULDRON_EXPLODE:
                    {
                        if (Creature* trigger = me->GetCreature(*me, instance->GetData64(NPC_CAULDRON_TRIGGER)))
                        {
                            trigger->CastSpell(trigger, SPELL_DEBILITATING_SLIME);
                            trigger->CastSpell(trigger, SPELL_DEBILITATING_SLIME_EFFECT, true);
                        }
                        break;
                    }
                    case EVENT_CAULDRON_PUSH_BACK:
                    {
                        if (Creature* trigger = me->GetCreature(*me, instance->GetData64(NPC_CAULDRON_TRIGGER)))
                        {
                            trigger->CastSpell(trigger, SPELL_CAULDRON_EXPLOSION);
                            trigger->CastSpell(trigger, SPELL_CAULDRON_EXPL_PUSH);
                        }
                        break;
                    }
                    case EVENT_RELEASE_ABBERATIONS:
                    {
                        if (abberationsLeft > 0)
                            DoCast(SPELL_RELEASE_ABBERATIONS);

                        abberationsLeft -= COUNT_ABBERATIONS_PER_RELEASE;
                        break;
                    }
                        // Black Phase
                    case EVENT_SUMMON_VILE_SWILL:
                        me->SummonCreature(NPC_VILE_SWILL, MaloriakPositions[urand(1,4)]);
                        events.ScheduleEvent(EVENT_SUMMON_VILE_SWILL, urand(4000,5000));
                        break;

                    case EVENT_ENGULFING_DARKNESS:
                        Talk(SAY_SLAY_OR_ABILITY);
                        DoCastAOE(SPELL_ENGULFING_DARKNESS);
                        events.ScheduleEvent(EVENT_ENGULFING_DARKNESS, 16000);
                        break;

                        // Final Phase
                    case EVENT_DRINK_ALL_BOTTLES:
                        DoCast(me, SPELL_DRINK_ALL_BOTTLES);
                        break;
                    case EVENT_ACID_NOVA:
                        DoCastAOE(SPELL_ACID_NOVA);
                        events.ScheduleEvent(EVENT_ACID_NOVA, urand(21000, 23000));
                        break;
                    case EVENT_MAGMA_JET:
                        Talk(SAY_SLAY_OR_ABILITY);
                        magmaJetsLeft = 6;
                        DoCastAOE(SPELL_MAGMA_JET);
                        events.ScheduleEvent(EVENT_MAGMA_JET, urand(12000, 15000));
                        break;
                    case EVENT_ABSOLUTE_ZERO:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            me->SummonCreature(NPC_ABSOLUTE_ZERO, *target, TEMPSUMMON_MANUAL_DESPAWN);

                        events.ScheduleEvent(EVENT_ABSOLUTE_ZERO, urand(7000, 9000));
                        break;
                    }
                }
            }		

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* /*who*/)
        {
            Talk(SAY_SLAY_OR_ABILITY);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            DespawnMinions();

            RemoveEncounterFrame();
            _JustDied();
        }

        void JustSummoned(Creature* summon)
        {
            if (summon->GetEntry() == NPC_MAGMA_JET_CONTROLLER)
            {
                summon->CastSpell(summon, SPELL_MAGMA_JET_EFFECT, true);

                for (uint8 i = 1; i <= COUNT_MAGMA_JETS; ++i)
                {
                    Position pos = *summon;
                    summon->MovePosition(pos, i * 3.5f, 0);
                    if (Creature* magmaJet = me->SummonCreature(NPC_MAGMA_JET, pos, TEMPSUMMON_TIMED_DESPAWN, 70000))
                        magmaJet->CastSpell(magmaJet, SPELL_MAGMA_JET_EFFECT, true);
                }
            }

            BossAI::JustSummoned(summon);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != 1)
                return;

            events.ScheduleEvent(EVENT_THROW, 1000);
        }

        static void HandleAbberationStun(Creature* abberation, bool const apply)
        {
            abberation->SetCanFly(apply);
            abberation->SetDisableGravity(apply);
            abberation->SetHover(apply);
            if (apply)
            {
                abberation->SetReactState(REACT_PASSIVE);
                abberation->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                abberation->CastSpell(abberation, SPELL_DROWNED_STATE, TRIGGERED_FULL_MASK);
            }
            else
            {
                abberation->RemoveAllAuras();
                abberation->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                abberation->SetReactState(REACT_AGGRESSIVE);
            }
        }

    private:
        bool const IsImbued() const
        {
            return me->HasAura(SPELL_FIRE_IMBUED) || me->HasAura(SPELL_FROST_IMBUED) || me->HasAura(SPELL_SHADOW_IMBUED);
        }

        void UpdatePhase(uint8 const newPhase)
        {
            // Cancel current Phase Events
            switch (phase)
            {
                case PHASE_RED:
                    events.CancelEvent(EVENT_SCORCHING_BLAST);
                    events.CancelEvent(EVENT_CONSUMING_FLAMES);
                    break;

                case PHASE_BLUE:
                    events.CancelEvent(EVENT_BITING_CHILL);
                    events.CancelEvent(EVENT_FLASH_FREEZE);
                    break;

                case PHASE_GREEN:
                    events.CancelEvent(EVENT_CAULDRON_EXPLODE);
                    break;

                case PHASE_BLACK:
                    me->RemoveAura(SPELL_SHADOW_IMBUED);
                    events.CancelEvent(EVENT_SUMMON_VILE_SWILL);
                    events.CancelEvent(EVENT_ENGULFING_DARKNESS);
                    break;
            }

            phase = newPhase;

            if (phase == PHASE_NON)
                return;

            // In Heroic Mode every 2. Phase is a Black Phase
            if ((me->GetMap()->IsHeroic()) && (!wasInBlackPhase))
            {
                phase = PHASE_BLACK;
                wasInBlackPhase = true;
            }
            else
            {
                withoutGreenPhase++;
                wasInBlackPhase = false;

                if (lastPhase == phase )
                {
                    if (phase == PHASE_RED)
                        phase = PHASE_BLUE;
                    else if (phase == PHASE_BLUE)
                        phase = PHASE_RED;
                }

                lastPhase = phase;
            }

            // Every 3. Phase is a Green Phase
            if (withoutGreenPhase >= 3)
            {
                if (phase == PHASE_BLACK)
                    wasInBlackPhase = false;

                phase = PHASE_GREEN;
                withoutGreenPhase = 0;
            }

        #ifdef DEBUG_PHASE
            phase = DEBUG_PHASE;
        #endif

            if (phase != PHASE_BLACK)
                Talk(SAY_VIAL_WARNING + phase);

            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();

            me->GetMotionMaster()->MovePoint(1, MaloriakPositions[MPOS_CAULDRON]);
        }

        void DespawnMinions()
        {
            me->DespawnCreaturesInArea(NPC_ABBERATON, 350.f);
            me->DespawnCreaturesInArea(NPC_PRIME_SUBJECT, 350.f);
            me->DespawnCreaturesInArea(NPC_FLASH_FREEZE, 300.f);
            me->DespawnCreaturesInArea(NPC_VILE_SWILL, 300.f);
            me->DespawnCreaturesInArea(NPC_MAGMA_JET, 300.f);
            me->DespawnCreaturesInArea(NPC_MAGMA_JET_CONTROLLER, 300.f);
            me->DespawnCreaturesInArea(NPC_ABSOLUTE_ZERO, 300.f);  
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_maloriakAI (creature);
    }
};

class npc_flash_freeze_maloriak : public CreatureScript
{
public:
    npc_flash_freeze_maloriak() : CreatureScript("npc_flash_freeze_maloriak") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_flash_freeze_maloriakAI (creature);
    }

    struct npc_flash_freeze_maloriakAI : public ScriptedAI
    {
        npc_flash_freeze_maloriakAI(Creature* creature) : ScriptedAI(creature) { }

        Unit* target;
        uint32 timerChecktarget;

        void IsSummonedBy(Unit* summoner)
        {
            target = summoner;
            timerChecktarget = 500;

            if (target)
            {
                me->NearTeleportTo(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation());
                me->AddAura(SPELL_FLASH_FREEZE, target);
            }

            me->AddAura(SPELL_FLASH_FREEZE_VISUAL, me);
        }

        void UpdateAI(uint32 diff)
        {
            if (timerChecktarget <= diff)
            {
                // Check weather the Debuff on Target is Expired
                if (target && !target->HasAura(SPELL_FLASH_FREEZE))
                    me->DespawnOrUnsummon();

                timerChecktarget = 500;

            }
            else
                timerChecktarget -= diff;
        }

        void JustDied(Unit* /*killer*/)
        {
            if (target)
                target->RemoveAura(SPELL_FLASH_FREEZE);

            me->DespawnOrUnsummon();
        }
    };
};

class npc_absolute_zero : public CreatureScript
{
public:
    npc_absolute_zero() : CreatureScript("npc_absolute_zero") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_absolute_zeroAI (creature);
    }

    struct npc_absolute_zeroAI : public ScriptedAI
    {
        npc_absolute_zeroAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 timerExplode;

        void Reset()
        {
            timerExplode = 3000;
            DoCast(me, SPELL_ABSOLUTE_ZERO);
        }

        void UpdateAI(uint32 diff)
        {
            if (timerExplode <= diff)
            {
                if (Player* nearest = me->FindNearestPlayer(2.f,true))
                    if (me->IsWithinMeleeRange(nearest))
                    {
                        DoCastAOE(SPELL_ABSOLUTE_ZERO_DAMAGE);
                        me->DespawnOrUnsummon(600);
                    }

                timerExplode = 400;
            }
            else
                timerExplode -= diff;
        }
    };
};

class npc_abberation : public CreatureScript
{
public:
    npc_abberation() : CreatureScript("npc_abberation") { }

    struct npc_abberationAI : public ScriptedAI
    {
        npc_abberationAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CHECK_GROWTH_CATALYST, 1500);
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
                    case EVENT_CHECK_GROWTH_CATALYST:
                    {
                        if (!me->HasAura(SPELL_DEBILITATING_SLIME_EFFECT) && !me->HasAura(SPELL_GROWTH_CATALYST))
                            DoCast(me, SPELL_GROWTH_CATALYST, true);

                        events.ScheduleEvent(EVENT_CHECK_GROWTH_CATALYST, 1500);
                    }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_abberationAI (creature);
    }
};

class npc_prime_subject : public CreatureScript
{
public:
    npc_prime_subject() : CreatureScript("npc_prime_subject") { }

    struct npc_prime_subjectAI : public ScriptedAI
    {
        npc_prime_subjectAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            events.Reset();
            events.ScheduleEvent(EVENT_FIXATE, 5000);
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
                    case EVENT_FIXATE:
                    {
                        if (Unit* victim = me->getVictim())
                            victim->CastSpell(me, SPELL_FIXATE, true);
                        else
                            events.ScheduleEvent(EVENT_FIXATE, 1000);

                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prime_subjectAI (creature);
    }
};

class AbberationSelector
{
public:
    explicit AbberationSelector(bool const allowPrimeSubjects) : _allowPrimeSubjects(allowPrimeSubjects) {}

    bool operator()(WorldObject* object)
    {
        Creature const* me = object->ToCreature();
        return !me || me->HasReactState(REACT_AGGRESSIVE) || !(me->GetEntry() == NPC_ABBERATON ||
            (_allowPrimeSubjects && me->GetEntry() == NPC_PRIME_SUBJECT));
    }

private:
    bool const _allowPrimeSubjects;
};

class spell_release_abberations : public SpellScriptLoader
{
public:
    spell_release_abberations() : SpellScriptLoader("spell_release_abberations") { }

    class spell_release_abberations_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_release_abberations_SpellScript);

        bool Load()
        {
            releaseAll = (GetSpellInfo()->Id == SPELL_RELEASE_ALL_ABBERATIONS);
            return GetCaster()->GetTypeId() == TYPEID_UNIT && GetCaster()->ToCreature()->GetEntry() == BOSS_MALORIAK;
        }

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if(AbberationSelector(releaseAll));

            if (unitList.size() > 3 && !releaseAll)
                unitList.resize(COUNT_ABBERATIONS_PER_RELEASE);
        }

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Creature* target = GetHitCreature();
            if (!caster || !target)
                return;

            FreeCreature(caster->ToCreature(), target);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_release_abberations_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_release_abberations_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }

    private:
        bool releaseAll;

        void FreeCreature(Creature* caster, Creature* target) const
        {
            bool const isPrimeSubject = target->GetEntry() == NPC_PRIME_SUBJECT;

            boss_maloriak::boss_maloriakAI::HandleAbberationStun(target, false);

            if (GameObject* inkubator = GetNearestGameObjectSafe(target, isPrimeSubject ? GOB_BIG_INKUBATOR : GOB_INKUBATOR))
                inkubator->SetGoState(GO_STATE_ACTIVE);

            Position pos = *target;
            float speed = 23.f;
            if (isPrimeSubject)
            {
                speed = 10.f;
                target->MovePosition(pos, 6.5f, 0);
            }
            else
                caster->GetRandomNearPosition(pos, 25.f);

            target->GetMotionMaster()->MoveJump(pos.GetPositionX(), pos.GetPositionY(), groundZ, speed, speed);
            target->SetInCombatWithZone();
        }

        GameObject* GetNearestGameObjectSafe(Creature* me, uint32 const entry) const
        {
            std::list<GameObject*> gos;
            GetGameObjectListWithEntryInGrid(gos, me, entry, 10.f);
            GameObject* go = nullptr;
            float dist = 100.f;
            for (auto const& itr : gos)
            {
                float const d = me->GetDistance(itr);
                if (d < dist)
                {
                    dist = d;
                    go = itr;
                }
            }
            return go;
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_release_abberations_SpellScript();
    }
};

void AddSC_boss_maloriak()
{
    new boss_maloriak();
    new npc_flash_freeze_maloriak();
    new npc_absolute_zero();
    new npc_abberation();
    new npc_prime_subject();
    new spell_release_abberations();
}
