#include "ScriptPCH.h"
#include "grim_batol.h"

enum Yells
{
    SAY_BOMB            = 0,
    SAY_AGGRO           = 1,
    SAY_SUMMON          = 2,
    SAY_SLAY            = 3,
    SAY_BLITZ_WARNING   = 4,
    SAY_SIEGE_WARNING   = 5,
    SAY_FRENZY          = 6,
};

enum Spells
{
    // General Umbriss
    SPELL_FRENZY                    = 74853,
    SPELL_SUMMON_SIEGE_DUMMY        = 74640,
    SPELL_GROUND_SIEGE              = 74634,
    SPELL_SUMMON_BLITZ_DUMMY        = 74668,
    SPELL_BLITZ                     = 74670,
    SPELL_BLEEDING_WOUND            = 74846,
    SPELL_SUMMON_SKARDYN            = 74859,

    // Malignant Trogg
    SPELL_MODGUDS_MALICE_AURA       = 74699,
    SPELL_MODGUDS_MALICE_AURA_HC    = 90169,
    SPELL_MODGUDS_DISEASE           = 74837,
    SPELL_MODGUDS_MALICE            = 90170,

    // Trogg Dweller
    SPELL_CLAW_PUNCTURE             = 76507,

    // Battered Dragon
    SPELL_ENGULFING_FLAMES          = 74040,
    SPELL_ENGULFING_FLAMES_HC       = 90904,
};

enum Events
{
    // General Umbriss
    EVENT_GROUND_SIEGE = 1,
    EVENT_BLITZ,
    EVENT_BLEEDING_WOUND,
    EVENT_SUMMON_TROGGS,
    EVENT_CHECK_AURA,
    EVENT_ATTACK,

    // Trogg Dweller
    EVENT_CLAW_PUNCTURE,
};

#define ACHIEV_UMBRISS 5297

const Position spawnLocations[4] =
{
    {-721.551697f, -439.109711f, 268.767456f, 0.814808f},
    {-700.411255f, -454.676971f, 268.767395f, 1.388150f},
    {-697.920105f, -435.002228f, 269.147583f, 1.470617f},
    {-711.855103f, -454.673157f, 268.767610f, 1.002312f}
};

class boss_general_umbriss : public CreatureScript
{
public:
    boss_general_umbriss() : CreatureScript("boss_general_umbriss") { }

    struct boss_general_umbrissAI : public BossAI
    {
        boss_general_umbrissAI(Creature* creature) : BossAI(creature, DATA_GENERAL_UMBRISS)
        {
            _frenzied = false;
            _malice = false;
            _assaulted = false;
        }

        bool _frenzied;
        bool _malice;
        bool _assaulted;

        void Reset()
        {
            _Reset();
            _frenzied = false;
            _malice = false;
            _assaulted = false;
            me->ApplySpellImmune(0, IMMUNITY_ID, !IsHeroic() ? SPELL_ENGULFING_FLAMES : SPELL_ENGULFING_FLAMES_HC, true);
        }
 
        void EnterCombat(Unit* /*who*/)
        {                
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_GROUND_SIEGE, 27000);
            events.ScheduleEvent(EVENT_BLITZ, 16000);
            events.ScheduleEvent(EVENT_BLEEDING_WOUND, 11000);
            events.ScheduleEvent(EVENT_SUMMON_TROGGS, 5000);
            events.ScheduleEvent(EVENT_CHECK_AURA, 1000);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            events.Reset();
            summons.DespawnAll();
            _frenzied = false;
            _malice = false;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case 1:
                    if (!_assaulted)
                    {
                        TalkToMap(SAY_BOMB);
                        _assaulted = true;
                    }
                    break;
                default:
                    break;
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPct(30) && !_frenzied)
            {
                Talk(SAY_FRENZY);
                DoCast(me, SPELL_FRENZY);
                _frenzied = true;
            }
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_MALIGNANT_TROGG:
                case NPC_TROGG_DWELLER:
                    summons.Summon(summon);
                    break;
            }
        }

        bool IsTooFarAway()
        {
            Position pos;
            pos.Relocate(me);
            if (me->GetDistance2d(pos.GetPositionX(), pos.GetPositionY()) >= 40.0f)
                return true;

            return false;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || IsTooFarAway())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GROUND_SIEGE:
                        Talk(SAY_SIEGE_WARNING);
                        DoCast(SPELL_SUMMON_SIEGE_DUMMY);
                        events.ScheduleEvent(EVENT_ATTACK, 4200);
                        events.ScheduleEvent(EVENT_GROUND_SIEGE, 23000);
                        break;
                    case EVENT_ATTACK:
                        me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
                        break;
                    case EVENT_BLITZ:
                        DoCastAOE(SPELL_SUMMON_BLITZ_DUMMY);
                        events.ScheduleEvent(EVENT_BLITZ, 23000);
                        break;
                    case EVENT_BLEEDING_WOUND:
                        DoCastVictim(SPELL_BLEEDING_WOUND);
                        events.ScheduleEvent(EVENT_BLEEDING_WOUND, 21000);
                        break;
                    case EVENT_SUMMON_TROGGS:
                    {
                        Talk(SAY_SUMMON);
                        DoCastAOE(SPELL_SUMMON_SKARDYN);

                        for (uint8 i = 0; i < 3; ++i)
                        {
                            if (Creature* dweller = me->SummonCreature(NPC_TROGG_DWELLER, spawnLocations[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000))
                                dweller->SetInCombatWithZone();
                        }

                        if (Creature* trogg = me->SummonCreature(NPC_MALIGNANT_TROGG, spawnLocations[3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000))
                            trogg->SetInCombatWithZone();

                        events.ScheduleEvent(EVENT_SUMMON_TROGGS, 60000);
                        break;
                    }
                    case EVENT_CHECK_AURA:
                        if (!me->HasAura(SPELL_MODGUDS_MALICE))
                            _malice = false;
                        else
                            _malice = true;
                        events.ScheduleEvent(EVENT_CHECK_AURA, 1000);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (_malice && IsHeroic())
                instance->DoCompleteAchievement(ACHIEV_UMBRISS);

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_general_umbrissAI(creature);
    }
};

class npc_gb_malignant_trogg : public CreatureScript
{
    public:
        npc_gb_malignant_trogg() : CreatureScript("npc_gb_malignant_trogg") { }

        struct npc_gb_malignant_troggAI : public ScriptedAI
        {
            npc_gb_malignant_troggAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_CLAW_PUNCTURE, urand(7000, 10000));
                DoCast(SPELL_MODGUDS_MALICE_AURA);
            }

            void JustDied(Unit* /*killer*/)
            {
                DoCastAOE(SPELL_MODGUDS_DISEASE);
                DoCastAOE(SPELL_MODGUDS_MALICE);
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
                        case EVENT_CLAW_PUNCTURE:
                            DoCastVictim(SPELL_CLAW_PUNCTURE);
                            events.ScheduleEvent(EVENT_CLAW_PUNCTURE, urand(9000, 10000));
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
        return new npc_gb_malignant_troggAI(creature);
    }
};

class npc_gb_trogg_dweller : public CreatureScript
{
    public:
        npc_gb_trogg_dweller() : CreatureScript("npc_gb_trogg_dweller") { }

        struct npc_gb_trogg_dwellerAI : public ScriptedAI
        {
            npc_gb_trogg_dwellerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_CLAW_PUNCTURE, urand(7000, 10000));
            }

            void JustDied(Unit* /*killer*/)
            {
                if (me->HasAura(SPELL_MODGUDS_MALICE_AURA) || me->HasAura(SPELL_MODGUDS_MALICE_AURA_HC))
                {
                    DoCastAOE(SPELL_MODGUDS_DISEASE);
                    DoCastAOE(SPELL_MODGUDS_MALICE);
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
                        case EVENT_CLAW_PUNCTURE:
                            DoCastVictim(SPELL_CLAW_PUNCTURE);
                            events.ScheduleEvent(EVENT_CLAW_PUNCTURE, urand(9000, 10000));
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
        return new npc_gb_trogg_dwellerAI(creature);
    }
};

class npc_gb_ground_siege_dummy : public CreatureScript
{
    public:
        npc_gb_ground_siege_dummy() : CreatureScript("npc_gb_ground_siege_dummy") { }

        struct npc_gb_ground_siege_dummyAI : public ScriptedAI
        {
            npc_gb_ground_siege_dummyAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (Creature* umbriss = me->FindNearestCreature(BOSS_GENERAL_UMBRISS, 500.0f, true))
                {
                    umbriss->SetFacingToObject(me);
                    umbriss->AI()->DoCastAOE(SPELL_GROUND_SIEGE);
                    umbriss->AddUnitState(UNIT_STATE_CANNOT_TURN);
                }
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_ground_siege_dummyAI(creature);
    }
};

class spell_gb_blitz_summon : public SpellScriptLoader
{
public:
    spell_gb_blitz_summon() : SpellScriptLoader("spell_gb_blitz_summon") { }

    class spell_gb_blitz_summon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_blitz_summon_SpellScript);

        void HandleLaunch(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* umbriss = caster->FindNearestCreature(BOSS_GENERAL_UMBRISS, 200.0f, true))
                {
                    umbriss->SetFacingToObject(caster);
                    umbriss->AI()->DoCastAOE(SPELL_BLITZ);
                    umbriss->AI()->Talk(SAY_BLITZ_WARNING, caster->GetGUID());
                }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_gb_blitz_summon_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_blitz_summon_SpellScript();
    }
};

class spell_gb_blitz : public SpellScriptLoader
{
public:
    spell_gb_blitz() : SpellScriptLoader("spell_gb_blitz") { }

    class spell_gb_blitz_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_blitz_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_blitz_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_blitz_SpellScript();
    }
};

class spell_gb_siege_summon : public SpellScriptLoader
{
public:
    spell_gb_siege_summon() : SpellScriptLoader("spell_gb_siege_summon") { }

    class spell_gb_siege_summon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_siege_summon_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_siege_summon_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_siege_summon_SpellScript();
    }
};

void AddSC_boss_general_umbriss() 
{
    new boss_general_umbriss();
    new npc_gb_malignant_trogg();
    new npc_gb_trogg_dweller();
    new npc_gb_ground_siege_dummy();
    new spell_gb_blitz_summon();
    new spell_gb_blitz();
    new spell_gb_siege_summon();
}
