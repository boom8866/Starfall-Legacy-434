
/*
 * Copyright (C) 2011 - 2013 Naios <naios-dev@live.de>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "ScriptedEscortAI.h"
#include "blackwing_descent.h"

enum Spells
{
    // Chimaeron
    SPELL_DOUBLE_ATTACK                 = 88826,
    SPELL_DOUBLE_ATTACK_EFFECT          = 82882,
    SPELL_CAUSTIC_SLIME                 = 82913,
    SPELL_CAUSTIC_SLIME_EFFECT          = 82935,
    SPELL_MASSACRE                      = 82848,
    SPELL_FEUD                          = 88872,
    SPELL_BREAK                         = 82881,

    SPELL_MORTALITY                     = 82934,
    SPELL_MORTALITY_RAID_DEBUFF         = 82890,

    // Bile O Tron
    SPELL_FINKLES_MIXTURE               = 82705,
    SPELL_FINKLES_MIXTURE_VISUAL        = 91106,
    SPELL_SYSTEM_FALURE                 = 88853,
    SPELL_REROUTE_POWER                 = 88861
};

enum Events
{
    EVENT_DOUBLE_ATTACK                 = 1,
    EVENT_CAUSTIC_SLIME                 = 2,
    EVENT_MASSACRE                      = 3,
    EVENT_SYSTEM_FAILURE                = 4,
    EVENT_BREAK                         = 5
};

enum Actions
{
    ACTION_BILE_O_TRON_EVENT_START      = 1,
    ACTION_BILE_O_TRON_SYSTEM_FAILURE   = 2,
    ACTION_BILE_O_TRON_RESET            = 3
};

enum ChimaeronYells
{
    SAY_SNORDS_LOUDLY,
    SAY_PREPARES_HIMSELF
};

enum FinkleYells
{
    SAY_INTRO,
    SAY_POOR_LITTLE_FELLA,
    SAY_O_HE_LOOKS_ANGRY,
    SAY_WELL_DONE
};

enum BileOTronYells
{
    SAY_BILE_STARTS,
    SAY_BILE_OFFLINE,
    SAY_BILE_ONLINE,
    SAY_BILE_POSITIVE_FEEDBACK
};

enum ChimaeronNefarianYells
{
    SAY_CHIMAERON_INTRO,
    SAY_STOP_ATTACKING_YOURSELF,
    SAY_THE_FIGHT_IS_LAME,
    SAY_A_SHAME_TO_LOOSE_THIS_EXPERIMENT
};

namespace Chimaeron
{
    class RemoveGossipFlag : public BasicEvent
    {
    public:
        RemoveGossipFlag(Creature* _finkle) : finkle(_finkle) {}

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            finkle->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            return true;
        }

    private:
        Creature* finkle;
    };

    class HitBileOffline : public BasicEvent
    {
    public:
        HitBileOffline(CreatureAI* _me, Creature* _bile_o_tron) : me(_me), bile_o_tron(_bile_o_tron) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            bile_o_tron->AI()->DoAction(ACTION_BILE_O_TRON_SYSTEM_FAILURE);
            me->DoCast(SPELL_FEUD);
            return true;
        }

    private:
        CreatureAI* me;
        Creature* bile_o_tron;
    };

    class MakeActive : public BasicEvent
    {
    public:
        MakeActive(Creature* _me) : me(_me) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
            return true;
        }

    private:
        Creature* me;
    };
}

using namespace Chimaeron;

class boss_chimaeron : public CreatureScript
{
public:
    boss_chimaeron() : CreatureScript("boss_chimaeron") { }

    struct boss_chimaeronAI: public BossAI
    {
        boss_chimaeronAI(Creature* creature) : BossAI(creature, DATA_CHIMAERON) {}

        uint32 finkleIntroTimer;
        uint32 massacreNovaTimer;
        uint8 massacreCount;

        void Reset()
        {
            me->m_Events.KillAllEvents(false);

            massacreNovaTimer = 5000;
            finkleIntroTimer = 0;
            massacreCount = urand(2, 3);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (Creature* finkle_einhorn = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_FINKLE_EINHORN)))
                finkle_einhorn->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            if (Creature* bile_o_tron = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_BILE_O_TRON)))
                bile_o_tron->AI()->DoAction(ACTION_BILE_O_TRON_RESET);

            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->RemoveAllAuras();

            events.ScheduleEvent(EVENT_MASSACRE, urand(30000,35000));
            events.ScheduleEvent(EVENT_DOUBLE_ATTACK, urand(13000,15000));
            events.ScheduleEvent(EVENT_CAUSTIC_SLIME, urand(8000,9000));
            events.ScheduleEvent(EVENT_BREAK, urand(14000,16000));

            instance->SetBossState(DATA_CHIMAERON, IN_PROGRESS);

            Talk(SAY_SNORDS_LOUDLY, me->GetGUID());

            if (!instance || !instance->CheckRequiredBosses(DATA_CHIMAERON))
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->isInCombat())
            {
                if (finkleIntroTimer <= diff)
                {
                    if (me->FindNearestPlayer(40.f))
                        if (Creature* finkle_einhorn = ObjectAccessor::GetCreature(*me,instance->GetData64(NPC_FINKLE_EINHORN)))
                            if (finkle_einhorn->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                                finkle_einhorn->AI()->Talk(SAY_INTRO);

                    finkleIntroTimer = urand(35000, 45000);
                }
                else
                    finkleIntroTimer -= diff;
            }
            else if (me->HasAura(SPELL_FEUD))
            {
                if (massacreNovaTimer <= diff)
                {
                    if (Player* player = me->FindNearestPlayer(40.f))
                        DoCast(player, SPELL_CAUSTIC_SLIME, true);

                    massacreNovaTimer = 5000;
                }
                else
                    massacreNovaTimer -= diff;

                return;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING) || !UpdateVictim())
                return;

            if (me->GetHealthPct() < 20.f && !me->HasAura(SPELL_MORTALITY))
            {
                if (Creature* finkle_einhorn = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_FINKLE_EINHORN)))
                    finkle_einhorn->AI()->Talk(SAY_O_HE_LOOKS_ANGRY);

                DoCast(SPELL_MORTALITY);
                DoCastAOE(SPELL_MORTALITY_RAID_DEBUFF);

                events.CancelEvent(EVENT_MASSACRE);
                events.CancelEvent(EVENT_BREAK);
                events.CancelEvent(EVENT_CAUSTIC_SLIME);
            }

            events.Update(diff);
            //_DoAggroPulse(diff);

            //CheckCheat(46.f);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {

                case EVENT_MASSACRE:
                    {
                        Talk(SAY_PREPARES_HIMSELF, me->GetGUID());
                        me->AttackStop();
                        DoCast(SPELL_MASSACRE);

                        if (--massacreCount)
                        {
                            me->SetReactState(REACT_PASSIVE);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            me->m_Events.AddEvent(new MakeActive(me), me->m_Events.CalculateTime(7000));

                            me->AttackStop();

                            events.DelayEvents(10000);
                            events.ScheduleEvent(EVENT_MASSACRE, 30000);
                        }
                        else
                        {
                            if (Creature* bile_o_tron = me->GetCreature(*me,instance->GetData64(NPC_BILE_O_TRON)))
                                me->m_Events.AddEvent(new HitBileOffline(this, bile_o_tron), me->m_Events.CalculateTime(7000));

                            massacreNovaTimer = 10000;
                            massacreCount = urand(2, 3);
                            events.DelayEvents(31000);
                            events.ScheduleEvent(EVENT_MASSACRE, 40000);
                        }

                        return;
                    }
                case EVENT_DOUBLE_ATTACK:
                    {
                        DoCast(me, SPELL_DOUBLE_ATTACK);
                        events.ScheduleEvent(EVENT_DOUBLE_ATTACK, urand(13000, 15000));
                        break;
                    }
                case EVENT_CAUSTIC_SLIME:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.f, true))
                            DoCast(target, SPELL_CAUSTIC_SLIME, true);

                        events.ScheduleEvent(EVENT_CAUSTIC_SLIME, urand(16000, 18000));
                        break;
                    }
                case EVENT_BREAK:
                    {
                        DoCastVictim(SPELL_BREAK);
                        events.ScheduleEvent(EVENT_BREAK, 14000);
                        break;
                    }
                }
            }		

            if (!me->HasAura(SPELL_FEUD))
                DoMeleeAttackIfReady();
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (me->HasReactState(REACT_PASSIVE))
            {
                me->SetReactState(REACT_AGGRESSIVE);
                DoZoneInCombat(me);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* bile_o_tron = me->GetCreature(*me,instance->GetData64(NPC_BILE_O_TRON)))
            {
                bile_o_tron->AI()->Talk(SAY_BILE_POSITIVE_FEEDBACK);
                bile_o_tron->DespawnOrUnsummon();
            }

            if (Creature* finkle_einhorn = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_FINKLE_EINHORN)))
                finkle_einhorn->AI()->TalkWithDelay(3000, SAY_WELL_DONE);

            me->m_Events.KillAllEvents(false);

            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_chimaeronAI (creature);
    }
};

class npc_bile_o_tron : public CreatureScript
{
public:
    npc_bile_o_tron() : CreatureScript("npc_bile_o_tron") { }

    struct npc_bile_o_tronAI : public npc_escortAI
    {
        npc_bile_o_tronAI(Creature* creature) : npc_escortAI(creature), uiSystemFailureTimer(0), activated(false), isFailureActive(false), instance(creature->GetInstanceScript()) {}

        InstanceScript* instance;
        uint32 uiSystemFailureTimer;
        bool activated;
        bool isFailureActive;

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!activated)
            {
                if (me->HasAura(SPELL_FINKLES_MIXTURE))
                    me->RemoveAura(SPELL_FINKLES_MIXTURE);

                return;
            }

            if (!me->HasAura(SPELL_SYSTEM_FALURE) && !me->HasAura(SPELL_FINKLES_MIXTURE))
                me->AddAura(SPELL_FINKLES_MIXTURE, me);

            if (uiSystemFailureTimer <= diff && isFailureActive)
            { // Reroute Power
                me->RemoveAura(SPELL_SYSTEM_FALURE);

                SetEscortPaused(false);

                isFailureActive = false;
                DoCast(me, SPELL_FINKLES_MIXTURE_VISUAL,true);
                Talk(SAY_BILE_ONLINE);
            }
            else uiSystemFailureTimer -= diff;
        }

        void WaypointReached(uint32 point) {}

        void DoAction(int32 action)
        {
            switch (action)
            {

            case ACTION_BILE_O_TRON_EVENT_START:
                {
                    if (Creature* finkle_einhorn = ObjectAccessor::GetCreature(*me,instance->GetData64(NPC_FINKLE_EINHORN)))
                        finkle_einhorn->m_Events.AddEvent(new RemoveGossipFlag(finkle_einhorn), finkle_einhorn->m_Events.CalculateTime(4000));

                    Talk(SAY_BILE_STARTS);
                    DoCast(me, SPELL_FINKLES_MIXTURE_VISUAL, true);

                    SetEscortPaused(false);
                    Start(false, false, NULL, NULL, false, true);

                    activated = true;
                    isFailureActive = false;
                    break;
                }
            case ACTION_BILE_O_TRON_SYSTEM_FAILURE:
                {
                    if (!activated)
                        break;

                    Talk(SAY_BILE_OFFLINE);

                    if (Creature* finkle_einhorn = ObjectAccessor::GetCreature(*me,instance->GetData64(NPC_FINKLE_EINHORN)))
                        finkle_einhorn->AI()->TalkWithDelay(3000, SAY_POOR_LITTLE_FELLA);

                    me->RemoveAllAuras();
                    DoCast(me, SPELL_REROUTE_POWER, true);
                    DoCast(me, SPELL_SYSTEM_FALURE, true);
                    isFailureActive = true;
                    uiSystemFailureTimer = 26000;

                    SetEscortPaused(true);
                    break;
                }
            case ACTION_BILE_O_TRON_RESET:
                {
                    SetEscortPaused(true);
                    me->GetMotionMaster()->MoveTargetedHome();
                    uiSystemFailureTimer = 0;
                    activated = false;
                    break;
                }
            }
        }

        void JustReachedHome()
        {
            me->RemoveAllAuras();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bile_o_tronAI (creature);
    }
};

class spell_finkles_mixture : public SpellScriptLoader
{
public:
    spell_finkles_mixture() : SpellScriptLoader("spell_finkles_mixture") { }

    class spell_finkles_mixtureAuraScript : public AuraScript
    {
        PrepareAuraScript(spell_finkles_mixtureAuraScript);

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void HandleOnEffectAbsorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            absorbAmount = 0;

            if (Unit* target = GetTarget())
            {
                if (target->GetHealth() <= dmgInfo.GetDamage() && target->GetHealth() > 10000)
                    absorbAmount = (dmgInfo.GetDamage() - target->GetHealth()) + 1;
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_finkles_mixtureAuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_finkles_mixtureAuraScript::HandleOnEffectAbsorb, EFFECT_1);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_finkles_mixtureAuraScript();
    }
};

void AddSC_boss_chimaeron()
{
    new boss_chimaeron();
    new npc_bile_o_tron();
    new spell_finkles_mixture();
}
